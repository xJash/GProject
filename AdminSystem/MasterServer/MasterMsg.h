#ifndef _MASTERMSG_H
#define _MASTERMSG_H

#include "itzbase.h"
#include "ServerInfo.h"

#define AGENT_LISTEN_PORT		6500

struct MASTER_WORLDINFO
{

	UI16	usWorldID;						// ���� ID
	TCHAR	szWorldName[ 20 ];				// �����
	TCHAR	szOpenDate[ 15 ];				// ���� ���� �ð�
	TCHAR	szShortMessage[ 64 ];			// ª�� �ȳ���	

	SI32	siServerID;						// ���� ID
	TCHAR	szGameServerIP[ 16 ];			// ���� IP
	UI16	usGameServerPort;				// ���� PORT

	TCHAR	szGameDBManagerIP[ 16 ];		// ���� db manager ip
	UI16	usGameDBManagerPort;			// ���� db manager port
};


enum {
	AGENTMSG_REPORT_FILEPATH = 0,
	AGENTMSG_REPORT_SERVERINFO,

	MASTERMSG_REPORT_AGENT_HEARTBEAT,									//
	MASTERMSG_REPORT_MASTER_HEARTBEAT,									// 

	MASTERMSG_REQUEST_GMCLOGIN = 100,
	MASTERMSG_RESPONSE_GMCLOGIN,

	MASTERMSG_REQUEST_SERVERINFO1,										
	MASTERMSG_RESPONSE_SERVERINFO1,

	MASTERMSG_REQUEST_SERVERINFO2,
	MASTERMSG_RESPONSE_SERVERINFO2,										

	MASTERMSG_REPORT_SERVERREFRESHINFO = 110,						// ���� ���� ���� 

	MASTERMSG_COMMAND_SERVER_ON,									// ���� ���� ���

	MASTERMSG_COMMAND_GAMEDBMANAGER_ON,								// GameDBManager ���� ���

	MASTERMSG_COMMAND_ALL_SERVER_ON,								// ��ü GameServer ���� ���
	MASTERMSG_COMMAND_ALL_SERVER_OFF,								// ��ü GameServer���� ��� 

	MASTERMSG_COMMAND_ALL_GAMEDBMANAGER_ON,							// ��ü GameDBManager ���� ���
	MASTERMSG_COMMAND_ALL_GAMEDBMANAGER_OFF,						// ��ü GameDBManager ���� ��� 

	MASTERMSG_COMMAND_MAKEFILE,
	MASTERMSG_COMMAND_MAKEDIRECTORY,
	MASTERMSG_COMMAND_SEND_FILEDATA,

	MASTERMSG_REQUEST_GMCDAYUSERNUM = 200,
	MASTERMSG_RESPONSE_GMCDAYUSERNUM,

	// 10000�� ���Ĵ� ������ ������ ������ �޽��� - ����������Ʈ���� ó�������ʰ� ������ ������ �޼������̴�.
	MASTERMSG_REPORT_FRONTSERVER_HEARTBEAT = 10000,
	MASTERMSG_REPORT_AUTHSERVER_HEARTBEAT,
	MASTERMSG_REPORT_ACCOUNTDBMANAGER_HEARTBEAT,
	MASTERMSG_REPORT_GAMESERVER_HEARTBEAT,
	MASTERMSG_REPORT_GAMEDBMANAGER_HEARTBEAT,
	MASTERMSG_REPORT_GAMEDB_HEARTBEAT,

	MASTERMSG_REQUEST_FRONTSERVERINITINFO,								// ����Ʈ ���� �ʱ�ȭ ���� ��û 
	MASTERMSG_REQUEST_AUTHSERVERINITINFO,								// ���� ���� �ʱ�ȭ ���� ��û
	MASTERMSG_REQUEST_ACCOUNTDBMANAGERINITINFO,							// Account DB Manager �ʱ�ȭ ���� ��û 
	MASTERMSG_REQUEST_GAMESERVERINITINFO,								// ���� ���� �ʱ�ȭ ���� ��û 
	MASTERMSG_REQUEST_GAMEDBMANAGERINITINFO,							// ���� DB Manager �ʱ�ȭ ���� ��û

	MASTERMSG_RESPONSE_FRONTSERVERINITINFO,
	MASTERMSG_RESPONSE_AUTHSERVERINITINFO,
	MASTERMSG_RESPONSE_ACCOUNTDBMANAGERINITINFO,
	MASTERMSG_RESPONSE_GAMESERVERINITINFO,
	MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO,

	MASTERMSG_REQUEST_VERSIONINFO,
	MASTERMSG_RESPONSE_VERSIONINFO,

	MASTERMSG_REQUEST_NEWCHARNUM,
	MASTERMSG_RESPONSE_NEWCHARNUM,

	MASTERMSG_RESPONSE_GMORDER,

	GAMESERVER_SEND_TOOLSLOG_MASTER,		// ��� ��ɾ� ���� ���Ӽ������� �����ͷ� ������.

	MASTERMSG_REQUEST_FRONTSERVERINITINFO_STRING,							// ����Ʈ ���� �ʱ�ȭ ���� ��û < ���ڿ� ���� >
	MASTERMSG_REQUEST_AUTHSERVERINITINFO_STRING,							// ���� ���� �ʱ�ȭ ���� ��û < ���ڿ� ���� >
	MASTERMSG_REQUEST_ACCOUNTDBMANAGERINITINFO_STRING,						// Account DB Manager �ʱ�ȭ ���� ��û < ���ڿ� ���� >
	MASTERMSG_REQUEST_GAMESERVERINITINFO_STRING,							// ���� ���� �ʱ�ȭ ���� ��û < ���ڿ� ���� >
	MASTERMSG_REQUEST_GAMEDBMANAGERINITINFO_STRING,							// ���� DB Manager �ʱ�ȭ ���� ��û < ���ڿ� ���� >

	MASTERMSG_RESPONSE_FRONTSERVERINITINFO_STRING,							// < ���ڿ� ���� >
	MASTERMSG_RESPONSE_AUTHSERVERINITINFO_STRING,							// < ���ڿ� ���� >
	MASTERMSG_RESPONSE_ACCOUNTDBMANAGERINITINFO_STRING,						// < ���ڿ� ���� >
	MASTERMSG_RESPONSE_GAMESERVERINITINFO_STRING,							// < ���ڿ� ���� >
	MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO_STRING,						// < ���ڿ� ���� >

	GOONZUMC_REQUEST_SERVERCOMMAND = 12000,									
	GOONZUMC_RESPONSE_SERVERCOMMAND,

	GOONZUMC_REQUEST_MAKEFILE,
	GOONZUMC_REQUEST_MAKEDIRECTORY,
	GOONZUMC_REQUEST_SEND_FILEDATA,

	GOONZUMC_REQUEST_SERVER_ON,
	GOONZUMC_REQUEST_SERVER_OFF,

	GOONZUMC_REQUEST_GAMEDBMANAGER_ON,
	GOONZUMC_REQUEST_GAMEDBMANAGER_OFF,

	GOONZUMC_REQUEST_ALL_SERVER_ON,
	GOONZUMC_REQUEST_ALL_SERVER_OFF,

	GOONZUMC_REQUEST_ALL_GAMEDBMANAGER_ON,
	GOONZUMC_REQUEST_ALL_GAMEDBMANAGER_OFF,

	GOONZUMC_REQUEST_FRONTSERVERON,
	GOONZUMC_REQUEST_FRONTSERVEROFF,

	GOONZUMC_REQUEST_GMORDER,
	
	MASTERMSG_COMMAND_SERVER_OFF,									// ���� ���� ��� 
	MASTERMSG_COMMAND_GAMEDBMANAGER_OFF,							// GameDBManager ���� ��� 

	MASTERMSG_REQUEST_GAMEDBMGR_ERRORQUERY_STRING,		// GameDBManager���� �������� ���� �߻��� �����ϴ� ��Ŷ
	GOONZUMC_RESPONSE_GAMEDBMGR_ERRORQUERY_STRING,		// GoonzuMC�� DBManager������ ���� �ϴ� ��Ŷ

	GOONZUGM_REQUEST_ACCOUNTCHARINFO = 13000,		// GMTOOL ���
	GOONZUGM_RESPONSE_ACCOUNTCHARINFO,

	GOONZUGM_REQUEST_USERCHARINFO ,				// GMTOOL ���
	GOONZUGM_RESPONSE_USERCHARINFO,

	MASTERMSG_REQUEST_GMORDER,				   // ���� ������ GM ��ɾ� ���� ��û
	GOONZUMC_RESPONSE_GMORDER,				   // ���� GM ��ɾ� ��� ����	
	ENDMSG
};

const int MAX_WORLDINFO_NUMBER = 40;

#pragma pack(1)

struct sReportToAgent_Heartbeat
{
	sPacketHeader	packetHeader;
};

struct sReportToMaster_Heartbeat
{
	sPacketHeader	packetHeader;
};

// ������Ʈ�� ���� ������ ������
struct sReportToAgent_ServerInfo
{
	sPacketHeader	packetHeader;

	SI32			siServerID;
	TCHAR			szFilePath[ 128 ];
	TCHAR			szMessage[ 20 ];
};


// ������Ʈ�� ���� ��� �� ���ϸ��� ������
struct sReportToAgent_FilePath
{
	sPacketHeader	packetHeader;

	TCHAR			szFilePath[ 128 ];
	TCHAR			szMessage[ 20 ];
};


// ����Ʈ ���� �ʱ�ȭ ����
struct sRequest_FrontServerInitInfo
{
	sRequest_FrontServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_FRONTSERVERINITINFO;
		packetHeader.usSize = sizeof( sRequest_FrontServerInitInfo );
	}	


	sPacketHeader		packetHeader;
};


#define MAX_MASTER_WORDLDINFO		100

struct sResponse_FrontServerInitInfo
{

	sResponse_FrontServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_FRONTSERVERINITINFO;
		packetHeader.usSize = sizeof( sResponse_FrontServerInitInfo );
	}

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szAuthServerIP[ 16 ];				// �������� IP
	UI16				usAuthServerPort;					// �������� PORT

	UI16				usClientListenPort;				// Ŭ���̾�Ʈ ���� ��� ��Ʈ
	UI16				usGameServerListenPort;			// ���Ӽ��� ���� ��� ��Ʈ

	UI16				count;
	MASTER_WORLDINFO	worldinfo[ MAX_MASTER_WORDLDINFO ];
};

// ����Ʈ ���� �ʱ�ȭ ����
struct sRequest_FrontServerInitInfo_String
{
	sRequest_FrontServerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_REQUEST_FRONTSERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sRequest_FrontServerInitInfo_String );
	}	


	sPacketHeader		packetHeader;
};



struct sResponse_FrontServerInitInfo_String
{

	sResponse_FrontServerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_FRONTSERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sResponse_FrontServerInitInfo_String );
	}

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szMapString[400];

	UI16				count;
	TCHAR				szWorldMapStr[50][400];
};


// ���� ���� ��û
struct sRequest_VersionInfo
{
	sRequest_VersionInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_VERSIONINFO;
		packetHeader.usSize = sizeof( sRequest_VersionInfo );
	}	


	sPacketHeader		packetHeader;
};


// ���� ���� ���� 
struct sResponse_VersionInfo
{ 
	sResponse_VersionInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_VERSIONINFO;
		packetHeader.usSize = sizeof( sResponse_VersionInfo );
	}

	sPacketHeader		packetHeader;

	UI32				count;
	UI32				versioninfo[ 2048 ];
};

// ���� ���� �ʱ�ȭ ����
struct sRequest_AuthServerInitInfo
{

	sRequest_AuthServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_AUTHSERVERINITINFO;
		packetHeader.usSize = sizeof( sRequest_AuthServerInitInfo );
	};

	sPacketHeader		packetHeader;
};

struct sResponse_AuthServerInitInfo
{
	sResponse_AuthServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_AUTHSERVERINITINFO;
		packetHeader.usSize = sizeof( sResponse_AuthServerInitInfo );
	};

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szAccountDBManagerIP[ 16 ];		// account db manager ip
	UI16				usAccountDBManagerPort;			// account db manager port

	UI16				usFrontServerListenPort;		// Front Server Listen Port
	UI16				usGameServerListenPort;			// Game Server Listen Port

	TCHAR				szAccountDBIP[ 20 ];			// account db ip
};

// ���� ���� �ʱ�ȭ ���� < ���ڿ� ���� >
struct sRequest_AuthServerInitInfo_String
{
	sRequest_AuthServerInitInfo_String()
	{
		packetHeader.usCmd = MASTERMSG_REQUEST_AUTHSERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sRequest_AuthServerInitInfo_String );
	};

	sPacketHeader		packetHeader;
};

struct sResponse_AuthServerInitInfo_String
{
	sResponse_AuthServerInitInfo_String()
	{
		packetHeader.usCmd = MASTERMSG_RESPONSE_AUTHSERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sResponse_AuthServerInitInfo_String );

		siServerID		= 0;
	};

	sPacketHeader		packetHeader;
	SI32				siServerID;

	TCHAR				szMapString[512];
};

// AccountDBManager �ʱ�ȭ ����
struct sRequest_AccountDBManagerInitInfo
{
	sRequest_AccountDBManagerInitInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_ACCOUNTDBMANAGERINITINFO;
		packetHeader.usSize = sizeof( sRequest_AccountDBManagerInitInfo );
	};

	sPacketHeader		packetHeader;

};

struct sResponse_AccountDBManagerInitInfo
{
	sResponse_AccountDBManagerInitInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_ACCOUNTDBMANAGERINITINFO;
		packetHeader.usSize = sizeof( sResponse_AccountDBManagerInitInfo );
	};


	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szAccountDBIP[ 16 ];
	TCHAR				szDatabaseName[ 20 ];			// database name
	TCHAR				szUserID[ 20 ];					// user id
	TCHAR				szUserPW[ 20 ];					// user pw

};

// AccountDBManager �ʱ�ȭ ����
struct sRequest_AccountDBManagerInitInfo_String
{
	sRequest_AccountDBManagerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_REQUEST_ACCOUNTDBMANAGERINITINFO_STRING;
		packetHeader.usSize = sizeof( sRequest_AccountDBManagerInitInfo_String );
	};

	sPacketHeader		packetHeader;

};

struct sResponse_AccountDBManagerInitInfo_String
{
	sResponse_AccountDBManagerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_ACCOUNTDBMANAGERINITINFO_STRING;
		packetHeader.usSize = sizeof( sResponse_AccountDBManagerInitInfo_String );
	};


	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szMapString[512];
};

// ���Ӽ��� �ʱ�ȭ ����
struct sRequest_GameServerInitInfo
{

	sRequest_GameServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_GAMESERVERINITINFO;
		packetHeader.usSize = sizeof( sRequest_GameServerInitInfo );
	};


	sPacketHeader		packetHeader;

};

struct sResponse_GameServerInitInfo
{
	sResponse_GameServerInitInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_GAMESERVERINITINFO;
		packetHeader.usSize = sizeof( sResponse_GameServerInitInfo );
	};

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szFrontServerIP[ 16 ];
	UI16				usFrontServerPort;

	TCHAR				szAuthServerIP[ 16 ];
	UI16				usAuthServerPort;

	TCHAR				szGameDBManagerIP[ 16 ];
	UI16				usGameDBManagerPort;

	UI16				usClientListenPort;
	UI16				usServerUnique;

	SI32				siServerType;
};

// ���Ӽ��� �ʱ�ȭ ����
struct sRequest_GameServerInitInfo_String
{

	sRequest_GameServerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_REQUEST_GAMESERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sRequest_GameServerInitInfo_String );
	};

	sPacketHeader		packetHeader;

};

struct sResponse_GameServerInitInfo_String
{
	sResponse_GameServerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_GAMESERVERINITINFO_STRING;
		packetHeader.usSize = sizeof( sResponse_GameServerInitInfo_String );
	};

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szMapString[1536];
};

// GameDBManager_World �ʱ�ȭ ����
struct sRequest_GameDBManagerInitInfo
{
	sRequest_GameDBManagerInitInfo() {
		packetHeader.usCmd = MASTERMSG_REQUEST_GAMEDBMANAGERINITINFO;
		packetHeader.usSize = sizeof( sRequest_GameDBManagerInitInfo );
	};

	sPacketHeader		packetHeader;
};

struct sResponse_GameDBManagerInitInfo
{
	sResponse_GameDBManagerInitInfo() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO;
		packetHeader.usSize = sizeof( sResponse_GameDBManagerInitInfo );
	};

	sPacketHeader		packetHeader;

	SI32				siServerID;

	UI16				usGameServerListenPort;			// game server listen port

	TCHAR				szGameDBIP[ 16 ];
	TCHAR				szDatabaseName[ 20 ];			// database name
	TCHAR				szUserID[ 20 ];					// user id
	TCHAR				szUserPW[ 20 ];					// user pw

	TCHAR				szLogDBIP[ 16 ];
	TCHAR				szLogDatabaseName[ 20 ];		// log database name
	TCHAR				szLogUserID[ 20 ];				// log user id
	TCHAR				szLogUserPW[ 20 ];				// log user pw
	TCHAR				szLogProcedure[ 40 ];			// log user pw
};

// GameDBManager_World �ʱ�ȭ ����
struct sRequest_GameDBManagerInitInfo_String
{
	sRequest_GameDBManagerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_REQUEST_GAMEDBMANAGERINITINFO_STRING;
		packetHeader.usSize = sizeof( sRequest_GameDBManagerInitInfo_String );
	};

	sPacketHeader		packetHeader;
};

struct sResponse_GameDBManagerInitInfo_String
{
	sResponse_GameDBManagerInitInfo_String() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO_STRING;
		packetHeader.usSize = sizeof( sResponse_GameDBManagerInitInfo_String );
	};

	sPacketHeader		packetHeader;

	SI32				siServerID;

	TCHAR				szMapString[1536];
};


// ��Ʈ��Ʈ
struct sHeartbeat
{
	sPacketHeader				packetHeader;
	DWORD						dwProcessId;
};



// ����Ʈ���� ��Ʈ��Ʈ 
struct sReport_FrontServerHeartbeat : public sHeartbeat
{
	sFrontServerRefreshInfo			refreshInfo;
};


// �������� ��Ʈ��Ʈ
struct sReport_AuthServerHeartbeat : public sHeartbeat
{
	sAuthServerRefreshInfo			refreshInfo;
};

// AccountDBManager ��Ʈ��Ʈ 
struct sReport_AccountDBManagerHeartbeat : public sHeartbeat
{
	sAccountDBManagerRefreshInfo	refreshInfo;
};

// ���Ӽ��� ��Ʈ��Ʈ
struct sReport_GameServerHeartbeat : public sHeartbeat
{
	sGameServerRefreshInfo			refreshInfo;
};

// GameDBManager_World ��Ʈ��Ʈ 
struct sReport_GameDBManagerHeartbeat : public sHeartbeat
{
	sGameDBManagerRefreshInfo		refreshInfo;
};


// ����� Ŭ���̾�Ʈ �α��� 
struct sRequest_GMCLogin
{
	sRequest_GMCLogin() {
		packetHeader.usCmd = MASTERMSG_REQUEST_GMCLOGIN;
		packetHeader.usSize = sizeof( sRequest_GMCLogin );
	};


	sPacketHeader		packetHeader;

	TCHAR				szID[ 20 ];
	TCHAR				szPW[ 20 ];
};


struct sResponse_GMCLogin
{
	sResponse_GMCLogin() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_GMCLOGIN;
		packetHeader.usSize = sizeof( sResponse_GMCLogin );
	};

	sPacketHeader		packetHeader;

	UI16				usResult;									// 0:����
};

// ����Ʈ����, ��������, AccountDBManager ���� ��û
struct sRequest_ServerInfo1
{

	sRequest_ServerInfo1() {
		packetHeader.usCmd = MASTERMSG_REQUEST_SERVERINFO1;
		packetHeader.usSize = sizeof( sRequest_ServerInfo1 );
	};

	sPacketHeader			packetHeader;
};

struct sResponse_ServerInfo1
{
	sResponse_ServerInfo1() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_SERVERINFO1;
		packetHeader.usSize = sizeof( sResponse_ServerInfo1 );
	};

	sPacketHeader			packetHeader;

	sFrontServerInfo		frontServerInfo;
	sAuthServerInfo			authServerInfo;
	sAccountDBManagerInfo	accountDBManagerInfo;	
	sAccountDBInfo			accountDBInfo;

};

// ���Ӽ���, GameDBManager_World ���� ��û 
struct sRequest_ServerInfo2
{

	sRequest_ServerInfo2() {
		packetHeader.usCmd = MASTERMSG_REQUEST_SERVERINFO2;
		packetHeader.usSize = sizeof( sRequest_ServerInfo2 );
	};

	sPacketHeader		packetHeader;

};


struct sResponse_ServerInfo2
{
	sResponse_ServerInfo2() {
		packetHeader.usCmd = MASTERMSG_RESPONSE_SERVERINFO2;
		packetHeader.usSize = sizeof( sResponse_ServerInfo2 );
	};

	sPacketHeader		packetHeader;

	UI16				usCount;
	sGameWorldInfo		gameWorldInfo[ MAX_WORLDINFO_NUMBER ];

	void SetSize() {
		packetHeader.usSize = sizeof( sPacketHeader ) + 4 + usCount * sizeof( sGameWorldInfo ) + 16;
	}

};


// MasterServer -> Monitor Client 
struct sReport_RefreshServerInfo
{

	sReport_RefreshServerInfo() {
		packetHeader.usCmd = MASTERMSG_REPORT_SERVERREFRESHINFO;
		packetHeader.usSize = sizeof( sReport_RefreshServerInfo );
	}

	sPacketHeader					packetHeader;

	SI32							siMaxUserNum;

	sFrontServerRefreshInfo			frontRefresh;
	sAuthServerRefreshInfo			authRefresh;
	sAccountDBManagerRefreshInfo	accountDBManagerRefresh;

	UI16							usCount;
	sGameServerRefreshInfo			gameRefresh[ MAX_WORLDINFO_NUMBER ];
	sGameDBManagerRefreshInfo		gameDBManagerRefresh[ MAX_WORLDINFO_NUMBER ];

	void SetSize() { packetHeader.usSize = sizeof( sPacketHeader ) + 
		sizeof( SI32 ) +
		sizeof( sFrontServerRefreshInfo ) +
		sizeof( sAuthServerRefreshInfo ) +
		sizeof( sAccountDBManagerRefreshInfo ) +
		(sizeof( sGameServerRefreshInfo ) + 
		sizeof( sGameDBManagerRefreshInfo ) ) * usCount + 16;
	};
};

struct sCommand_ServerOn
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_ServerOn()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_SERVER_ON;
		packetHeader.usSize = sizeof( sCommand_ServerOn );
		siServerID = -1;
		dwProcessId = 0;
	}
};

struct sCommand_ServerOff
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_ServerOff()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_SERVER_OFF;
		packetHeader.usSize = sizeof( sCommand_ServerOff );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_GameDBManagerStart
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] GameDBManager�� �����Ѵ�.
//
//***************************************************************************************************
struct sCommand_GameDBManagerOn
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_GameDBManagerOn()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_GAMEDBMANAGER_ON;
		packetHeader.usSize = sizeof( sCommand_GameDBManagerOn );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_GameDBManagerOff
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] GameDBManager�� ����
//
//***************************************************************************************************
struct sCommand_GameDBManagerOff
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_GameDBManagerOff()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_GAMEDBMANAGER_OFF;
		packetHeader.usSize = sizeof( sCommand_GameDBManagerOff );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_All_ServerOn
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] ��ü GameServer�� �����Ѵ�.
//
//***************************************************************************************************
struct sCommand_All_ServerOn
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_All_ServerOn()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_ALL_SERVER_ON;
		packetHeader.usSize = sizeof( sCommand_All_ServerOn );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_All_ServerOff
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] ��ü GameServer�� ����.
//
//***************************************************************************************************
struct sCommand_All_ServerOff
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_All_ServerOff()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_ALL_SERVER_OFF;
		packetHeader.usSize = sizeof( sCommand_All_ServerOff );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_All_GameDBManagerOn
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] ��ü GameDBManager�� �����Ѵ�.
//
//***************************************************************************************************
struct sCommand_All_GameDBManagerOn
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_All_GameDBManagerOn()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_ALL_GAMEDBMANAGER_ON;
		packetHeader.usSize = sizeof( sCommand_All_GameDBManagerOn );
		siServerID = -1;
		dwProcessId = 0;
	}
};

//***************************************************************************************************
//
// Class Name 		: sCommand_All_GameDBManagerOff
//
// Last Modified 	: 2007 / 03 / 26
// Created		 	: �豤��
//
// Function			: [��û] ��ü GameDBManager�� ����
//
//***************************************************************************************************
struct sCommand_All_GameDBManagerOff
{
	sPacketHeader					packetHeader;

	SI32							siServerID;
	DWORD							dwProcessId;

	sCommand_All_GameDBManagerOff()
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_ALL_GAMEDBMANAGER_OFF;
		packetHeader.usSize = sizeof( sCommand_All_GameDBManagerOff );
		siServerID = -1;
		dwProcessId = 0;
	}
};

struct sRequest_ServerCommand
{
	sPacketHeader					packetHeader;

	SI32							siWorldID;
	TCHAR							szCommand[ 128 ];

	sRequest_ServerCommand( SI32 worldid, TCHAR *szCmd ) {

		packetHeader.usCmd = GOONZUMC_REQUEST_SERVERCOMMAND;
		packetHeader.usSize = sizeof( sRequest_ServerCommand );

		siWorldID = worldid;
		StringCchCopy( szCommand, 128, szCmd );
	}

};

struct sRequest_GMCDAYUSERNUM 
{
	sPacketHeader					packetHeader;

	SI32							siYear;
	SI32							siMonth;
	SI32							siDay;

	SI32							siLayer;

	sRequest_GMCDAYUSERNUM( SI32 year,SI32 month,SI32 day, SI32 layer ){

		packetHeader.usCmd = MASTERMSG_REQUEST_GMCDAYUSERNUM;
		packetHeader.usSize = sizeof(sRequest_GMCDAYUSERNUM);

		siYear = year;
		siMonth = month;
		siDay = day;

		siLayer = layer;
	}
};

struct sResponse_GMCDAYUSERNUM 
{
	sPacketHeader					packetHeader;

	SI32							siResult;

	SI32							siYear;
	SI32							siMonth;
	SI32							siDay;

	SI32							siLayer;

	SI32							siUserNum[ 288 ];

	sResponse_GMCDAYUSERNUM()
	{
		packetHeader.usCmd = MASTERMSG_RESPONSE_GMCDAYUSERNUM;
		packetHeader.usSize = sizeof( sResponse_GMCDAYUSERNUM );
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMCServerOn
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ������ ���Ӽ����� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMCServerOn
{
	sPacketHeader				packetHeader;

	SI32						siServerID;

	sRequest_GMCServerOn( SI32 serverid ) 
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_SERVER_ON;
		packetHeader.usSize = sizeof( sRequest_GMCServerOn );

		siServerID = serverid;
	}

};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMCServerOff
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ������ ���Ӽ����� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMCServerOff
{
	sPacketHeader				packetHeader;

	SI32						siServerID;

	sRequest_GMCServerOff( SI32 serverid ) 
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_SERVER_OFF;
		packetHeader.usSize = sizeof( sRequest_GMCServerOff );

		siServerID = serverid;
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMCGameDBManagerOn
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ������ ����DB�� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMCGameDBManagerOn
{
	sPacketHeader				packetHeader;

	SI32						siServerID;

	sRequest_GMCGameDBManagerOn( SI32 serverid )
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_GAMEDBMANAGER_ON;
		packetHeader.usSize = sizeof( sRequest_GMCServerOn );

		siServerID = serverid;
	}

};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMCGameDBManagerOff
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ������ ����DB�� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMCGameDBManagerOff
{
	sPacketHeader				packetHeader;

	SI32						siServerID;

	sRequest_GMCGameDBManagerOff( SI32 serverid ) {
		packetHeader.usCmd = GOONZUMC_REQUEST_GAMEDBMANAGER_OFF;
		packetHeader.usSize = sizeof( sRequest_GMCGameDBManagerOff );

		siServerID = serverid;
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_AllServerOn
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ��� ���Ӽ����� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMC_AllServerOn
{
	sPacketHeader				packetHeader;

	sRequest_GMC_AllServerOn() 
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_ALL_SERVER_ON;
		packetHeader.usSize = sizeof( sRequest_GMC_AllServerOn );
	}

};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_AllServerOff
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ������ ���Ӽ����� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMC_AllServerOff
{
	sPacketHeader				packetHeader;

	sRequest_GMC_AllServerOff() 
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_ALL_SERVER_OFF;
		packetHeader.usSize = sizeof( sRequest_GMC_AllServerOff );
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_AllGameDBManagerOn
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ��ü ����DB�� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMC_AllGameDBManagerOn
{
	sPacketHeader				packetHeader;

	sRequest_GMC_AllGameDBManagerOn()
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_ALL_GAMEDBMANAGER_ON;
		packetHeader.usSize = sizeof( sRequest_GMC_AllGameDBManagerOn );
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMCGameDBManagerOff
//
// Last Modified 	: 2007 / 03 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ��ü ����DB�� �����Ѵ�.
//
//***************************************************************************************************
struct sRequest_GMC_AllGameDBManagerOff
{
	sPacketHeader				packetHeader;

	sRequest_GMC_AllGameDBManagerOff() 
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_ALL_GAMEDBMANAGER_OFF;
		packetHeader.usSize = sizeof( sRequest_GMC_AllGameDBManagerOff );
	}
};

struct sRequest_GMCFrontServerOn
{
	sPacketHeader				packetHeader;

	sRequest_GMCFrontServerOn()
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_FRONTSERVERON;
		packetHeader.usSize = sizeof( sRequest_GMCFrontServerOn );
	}
};

struct sRequest_GMCFrontServerOff
{
	sPacketHeader				packetHeader;

	sRequest_GMCFrontServerOff()
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_FRONTSERVEROFF;
		packetHeader.usSize = sizeof( sRequest_GMCFrontServerOff );
	}
};


// ������ ������ ���� ��ü ������ ĳ���� ���� �� ���� ���� ������ 
struct sResponse_NewCharNum
{
	sPacketHeader				packetHeader;

	SI32						siCount;

	SI32						siServerID[ 50 ];
	SI32						siNewCharNum[ 50 ];
	SI32						siDelCharNum[ 50 ];

};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMOrder
//
// Last Modified 	: 2009 / 07 / 02 
// Created		 	: �ڱ���
//
// Function			: [��û] GM��ɾ Ư�� ���� ������ ��û�Ѵ�.
//
//***************************************************************************************************

struct sRequest_GMOrder
{
	sPacketHeader				packetHeader;

	TCHAR						order[ 256 ];

	UI32						uiCharID;			// ��û�� ���̵�

	SI32						siWorldId;				// ���� ���� ���̵�	

	sRequest_GMOrder( TCHAR*str, UI32 uiCharID_Para, SI32 siWorldId_Para)
	{
		packetHeader.usCmd = MASTERMSG_REQUEST_GMORDER;
		packetHeader.usSize = sizeof( sRequest_GMOrder );

		memcpy( order, str, 256 );
		order[ 255 ] = NULL;

		uiCharID = uiCharID_Para;

		siWorldId = siWorldId_Para;
	}
};
//***************************************************************************************************
//
// Class Name 		: sResponse_GMOrder
//
// Last Modified 	: 2009 / 07 / 02 
// Created		 	: �ڱ���
//
// Function			: [����] Ư�� ���� �������� GM��ɾ ���� �� �� ����� �����ش�.
//
//***************************************************************************************************

struct sResponse_GMOrder
{
	sPacketHeader				packetHeader;

	TCHAR						order[ 256 ];

	UI32						uiCharID;			// ��û�� ���̵�

	BOOL						isSuccess;			// ���� ���� ����

	SI32						siWorldId;				// ���� ���� ���̵�	

	sResponse_GMOrder( TCHAR*str, UI32 uiCharID_Para, BOOL isSuccess_Para , SI32 siWorldId_Para)
	{
		packetHeader.usCmd = MASTERMSG_RESPONSE_GMORDER;
		packetHeader.usSize = sizeof( sResponse_GMOrder );

		memcpy( order, str, 256 );
		order[ 255 ] = NULL;

		uiCharID = uiCharID_Para;

		isSuccess = isSuccess_Para;

		siWorldId = siWorldId_Para;
	}
};


//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_GMOrder
//
// Last Modified 	: 2009 / 07 / 02 
// Created		 	: �ڱ���
//
// Function			: [��û] GM��ɾ� ������ ��û�Ѵ�.
//
//***************************************************************************************************

struct sRequest_GMC_GMOrder
{
	sPacketHeader				packetHeader;

	TCHAR						order[ 256 ];

	SI32						siWorldId;		// ���� ���� ���̵�	

	sRequest_GMC_GMOrder( TCHAR *str ,SI32 siWorldId_Para)
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_GMORDER;
		packetHeader.usSize = sizeof( sRequest_GMC_GMOrder );

		memcpy( order, str, 256 );
		order[ 255 ] = NULL;

		siWorldId = siWorldId_Para;
	}
};

//***************************************************************************************************
//
// Class Name 		: sResponse_GMC_GMOrder
//
// Last Modified 	: 2009 / 07 / 02 
// Created		 	: �ڱ���
//
// Function			: [����] GM��ɾ��� ���� ����� �˷��ش�.
//
//***************************************************************************************************

#define GMORDER_RESULT_FAIL 0
#define GMORDER_RESULT_SUCCESS 1
#define GMORDER_RESULT_DENY 2
struct sResponse_GMC_GMOrder
{
	sPacketHeader				packetHeader;

	TCHAR						order[ 256 ];

	SI32						siWorldId;				// ���� ���� ���̵�	
	TCHAR						szRequestID[20];		// ��û�� ���̵�
	TCHAR						szRequestIP[20];		// ��û�� ������
	TCHAR						szRequestTime[20];		// ��û �ð�
	
	SI32						siResult;			    // ��� ��

	sResponse_GMC_GMOrder( TCHAR *str,SI32 siWorldId_Para,TCHAR* pszRequestID_Para,TCHAR* pszRequestIP_Para,TCHAR* pszRequestTime_Para, SI32 siResult_Para )
	{
		packetHeader.usCmd = GOONZUMC_RESPONSE_GMORDER;
		packetHeader.usSize = sizeof( sResponse_GMC_GMOrder );

		memcpy( order, str, 256 );
		order[ 255 ] = NULL;

		siWorldId = siWorldId_Para;

		memcpy( szRequestID, pszRequestID_Para, 20 );
		szRequestID[ 19 ] = NULL;

		memcpy( szRequestIP, pszRequestIP_Para, 20 );
		szRequestIP[ 19 ] = NULL;

		memcpy( szRequestTime, pszRequestTime_Para, 20 );
		szRequestTime[ 19 ] = NULL;

		siResult = siResult_Para;
	}
};



//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_MakeFile
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [��û] ������ ��ġ�� ������ �� ������ǻ�� ������ �����.
//						     ����͸� -> ������ ����
//
//***************************************************************************************************
struct sRequest_GMC_MakeFile
{
	sPacketHeader				packetHeader;

	TCHAR						m_szFileName[ MAX_PATH ];

	sRequest_GMC_MakeFile( TCHAR *str )
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_MAKEFILE;
		packetHeader.usSize = sizeof( sRequest_GMC_MakeFile );

		_tcsncpy( m_szFileName, str, MAX_PATH );
	}

	TCHAR* GetFileName()
	{
		return m_szFileName;
	}
};

//***************************************************************************************************
//
// Class Name 		: sResponse_GMC_MakeFile
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [����] ������ ��ġ�� ������ �� ������ǻ�� ������ �����.
//                           ������ ���� -> ���� ������Ʈ
//
//***************************************************************************************************
struct sResponse_GMC_MakeFile
{
	sPacketHeader				packetHeader;

	TCHAR						m_szFileName[ MAX_PATH ];

	sResponse_GMC_MakeFile( TCHAR *str )
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_MAKEFILE;
		packetHeader.usSize = sizeof( sResponse_GMC_MakeFile );

		_tcsncpy( m_szFileName, str, MAX_PATH );
	}

	TCHAR* GetFileName()
	{
		return m_szFileName;
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_MakeDirectory
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [��û] ������ ����� ������ ������ ������ش�.
//                           ����͸� -> ������ ����
//
//***************************************************************************************************
struct sRequest_GMC_MakeDirectory
{
	sPacketHeader				packetHeader;

	TCHAR						m_szDirectoryName[ MAX_PATH ];

	sRequest_GMC_MakeDirectory( TCHAR *str )
	{
		packetHeader.usCmd = GOONZUMC_REQUEST_MAKEDIRECTORY;
		packetHeader.usSize = sizeof( sRequest_GMC_MakeDirectory );

		_tcsncpy( m_szDirectoryName, str, MAX_PATH );
	}

	TCHAR* GetDirectoryName()
	{
		return m_szDirectoryName;
	}
};

//***************************************************************************************************
//
// Class Name 		: sResponse_GMC_MakeDirectory
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [����] ������ ����� ������ ������ ������ش�.
//                           ������ ���� -> ���� ������Ʈ
//
//***************************************************************************************************
struct sResponse_GMC_MakeDirectory
{
	sPacketHeader				packetHeader;

	TCHAR						m_szDirectoryName[ MAX_PATH ];

	sResponse_GMC_MakeDirectory( TCHAR *str )
	{
		packetHeader.usCmd = MASTERMSG_COMMAND_MAKEDIRECTORY;
		packetHeader.usSize = sizeof( sResponse_GMC_MakeDirectory );

		_tcsncpy( m_szDirectoryName, str, MAX_PATH );
	}

	TCHAR* GetDirectoryName()
	{
		return m_szDirectoryName;
	}
};

const int MAX_SEND_BYPE = 1000;
//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_SendFileData
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [��û] ������ ����� ������ ���� ������ ������.
//
//***************************************************************************************************
class sRequest_GMC_SendFileData
{
public:
	sPacketHeader		packetHeader;

	SI32				m_siSendCount;
	SI32				m_siReadData;
	TCHAR				m_szFileName[ MAX_PATH ];
	TCHAR				m_cData[MAX_SEND_BYPE];

	sRequest_GMC_SendFileData( SI32 SendCount, SI32 ReadData, TCHAR* pFileName, TCHAR* pData ) 
	{
		packetHeader.usSize = sizeof( sRequest_GMC_SendFileData );
		packetHeader.usCmd = GOONZUMC_REQUEST_SEND_FILEDATA;

		m_siSendCount = SendCount;
		m_siReadData = ReadData;
		m_szFileName[0] = '\0';
		_tcsncpy( m_szFileName, pFileName, MAX_PATH );
		m_cData[0] = '\0';
		memcpy( m_cData, pData, MAX_SEND_BYPE);
	}
};

//***************************************************************************************************
//
// Class Name 		: sResponse_GMC_SendFileData
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [��û] ������ ����� ������ ���� ������ ������.
//
//***************************************************************************************************
class sResponse_GMC_SendFileData
{
public:
	sPacketHeader		packetHeader;

	SI32				m_siSendCount;
	SI32				m_siReadData;
	TCHAR				m_szFileName[ MAX_PATH ];
	TCHAR				m_cData[MAX_SEND_BYPE];

	sResponse_GMC_SendFileData( SI32 SendCount, SI32 ReadData, TCHAR* pFileName, TCHAR* pData ) 
	{
		packetHeader.usSize = sizeof( sResponse_GMC_SendFileData );
		packetHeader.usCmd = MASTERMSG_COMMAND_SEND_FILEDATA;

		m_siSendCount = SendCount;
		m_siReadData = ReadData;
		m_szFileName[0] = '\0';
		_tcsncpy( m_szFileName, pFileName, MAX_PATH );
		m_cData[0] = '\0';
		memcpy( m_cData, pData, MAX_SEND_BYPE);
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_SendFileData
//
// Last Modified 	: 2007 / 03 / 11
// Created		 	: �豤��
//
// Function			: [��û] ������ ����� ������ ���� ������ ������.
//
//***************************************************************************************************
struct sRequest_Send_ToolsLog_MasterServer
{
	sPacketHeader		packetHeader;

	TCHAR szServerName[10];
	TCHAR szCommand[50];		// ������ ���
	TCHAR szAccountID[20];	// ����
	TCHAR szCharName[20];	// ĳ���� �̸�
	TCHAR szLog[256];		// ���� ����

	sRequest_Send_ToolsLog_MasterServer( TCHAR* ServerName, TCHAR* Command, TCHAR* AccountID, TCHAR* CharName, TCHAR* Log )
	{
		packetHeader.usSize = sizeof( sRequest_Send_ToolsLog_MasterServer );
		packetHeader.usCmd	= GAMESERVER_SEND_TOOLSLOG_MASTER;

		memcpy( szServerName, ServerName, 10);
		szServerName[9] = NULL;
		memcpy( szCommand,	  Command, 50);
		szCommand[49] = NULL;
		memcpy( szAccountID, AccountID, 20);
		szAccountID[19] = NULL;
		memcpy( szCharName,  CharName, 20);
		szCharName[19] = NULL;
		memcpy( szLog,		  Log, 256);
		szLog[255] = NULL;
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_UserCharInfo
//
// Last Modified 	: 2007 / 07 / 03
// Created		 	: �̰���
//
// Function			: [��û] ������ ��� ĳ���� �̸��� ��û�Ѵ�.
//
//***************************************************************************************************
class sRequest_GMC_AccountCharInfo
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siCharID;			// ĳ���͹�ȣ - MasterServer���� �����Ѵ�.
	TCHAR				m_szAccountID[20];	// ����ID

	sRequest_GMC_AccountCharInfo(SI32 siServerID, TCHAR* pszAccountID)
	{
		m_packetHeader.usSize	= sizeof( sRequest_GMC_AccountCharInfo );
		m_packetHeader.usCmd	= GOONZUGM_REQUEST_ACCOUNTCHARINFO;
		m_siCharID				= 0;

		m_szAccountID[0] = '\0';
		if(pszAccountID)		_tcsncpy(m_szAccountID, pszAccountID, sizeof(m_szAccountID));
	}
};

class sResponse_GMC_AccountCharInfo
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siCharID;			// ĳ���͹�ȣ - MasterServer���� �����Ѵ�.

	TCHAR				m_szAccountID[20];	// ����ID
	TCHAR				m_szServerName[32];	// ������

	TCHAR				m_szCharName1[20];	// ĳ����1
	TCHAR				m_szCharName2[20];	// ĳ����2
	TCHAR				m_szCharName3[20];	// ĳ����3

	sResponse_GMC_AccountCharInfo()
	{
		m_packetHeader.usSize = sizeof( sResponse_GMC_AccountCharInfo );
		m_packetHeader.usCmd	= GOONZUGM_RESPONSE_ACCOUNTCHARINFO;

		m_szCharName1[0] = '\0';
		m_szCharName2[0] = '\0';
		m_szCharName3[0] = '\0';
	}
};


//***************************************************************************************************
//
// Class Name 		: sRequest_GMC_UserCharInfo
//
// Last Modified 	: 2007 / 07 / 03
// Created		 	: �̰���
//
// Function			: [��û] ĳ���������� ��û�Ѵ�.
//
//***************************************************************************************************
class sRequest_GMC_UserCharInfo
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siCharID;			// ĳ���͹�ȣ - MasterServer���� �����Ѵ�.

	SI32				m_siServerID;
	TCHAR				m_szCharName[20];	// ĳ���� �̸�

	sRequest_GMC_UserCharInfo(SI32 siServerID, TCHAR* pszCharName)
	{
		m_packetHeader.usSize	= sizeof( sRequest_GMC_UserCharInfo );
		m_packetHeader.usCmd	= GOONZUGM_REQUEST_USERCHARINFO;
		m_siCharID				= 0;

		m_siServerID = siServerID;

		m_szCharName[0] = '\0';
		if(pszCharName)		_tcsncpy(m_szCharName, pszCharName, sizeof(m_szCharName));
	}
};

class sResponse_GMC_UserCharInfo
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siCharID;			// ĳ���͹�ȣ - MasterServer���� �����Ѵ�.

	TCHAR				m_szAccountID[30];
	TCHAR				m_szPassword[30];
	bool				m_bConnectSwitch;		// ���� ����. 

	SI64 				m_clTotalMoney;		// ������
	SI64 				m_clBankMoney;		// ����ݾ�

	SI64				m_siWorldTradeMoney;

	//cltSummonInfo		m_clSummonInfo;		// ��ȯ�� ����
	SI32				m_siVillageUnique;	// ���� ����
	UI08				m_uiWarnMode;		// ���(��� ����)

	UI08				m_uiBlockMode;
	TCHAR				m_szBlockReason[200] ;

	SI32				m_siPersonID;
	SI16				m_siLevel;
	SI64				m_siMoney;

	SI16				m_siMapIndex;
	SI16				m_siX;
	SI16				m_siY;
	SI08				m_siGoonzuFriends;

	//TCHAR				m_szOtherPersonName1[ MAX_PLAYER_NAME ];
	//TCHAR				m_szOtherPersonName2[ MAX_PLAYER_NAME ];
	TCHAR				m_szBlockStartDate[24];
	TCHAR				m_szBlockEndDate[24];

	TCHAR				m_szRecommender[20];		// ��õ��
	TCHAR				m_szFatherName[20];			// ����
	SI16				m_siStudentLevel;			// ���ڰ� �Ǿ��� ���� ����

	TCHAR				m_szMakeDate[24];			// ĳ���� ������

	//cltItem clItem[MAX_ITEM_PER_PERSON];
	SI16	m_siItemUnique[110];
	SI16	m_siItemCount[110];


	sResponse_GMC_UserCharInfo()
	{
		ZeroMemory(this, sizeof(sResponse_GMC_UserCharInfo));

		m_packetHeader.usSize = sizeof( sResponse_GMC_UserCharInfo );
		m_packetHeader.usCmd	= GOONZUGM_RESPONSE_USERCHARINFO;
	}
};

//***************************************************************************************************
//
// Class Name 		: sRequest_GameDBMgr_ErroyQuery_String
//
// Last Modified 	: 2009 / 03 / 30
// Created		 	: �̰���
//
// Function			: [GAMEDBMGR->MASTERSERVER] ���������� �߻������� �����Ѵ�.
//
//***************************************************************************************************
class sRequest_GameDBMgr_ErroyQuery_String
{
public:
	sPacketHeader		m_packetHeader;

	TCHAR				m_szMapString[1024];

	sRequest_GameDBMgr_ErroyQuery_String( TCHAR* pszMapStr )
	{
		ZeroMemory(this, sizeof(sRequest_GameDBMgr_ErroyQuery_String));

		m_packetHeader.usSize = sizeof( sRequest_GameDBMgr_ErroyQuery_String );
		m_packetHeader.usCmd	= MASTERMSG_REQUEST_GAMEDBMGR_ERRORQUERY_STRING;

		StringCchCopy( m_szMapString, sizeof(m_szMapString), pszMapStr );
	}
};

//***************************************************************************************************
//
// Class Name 		: sResponse_GameDBMgr_ErrorQuery_String
//
// Last Modified 	: 2009 / 03 / 30
// Created		 	: �̰���
//
// Function			: [MASTERSERVER->GOONZUMC] �������� ������ �����Ѵ�.
//
//***************************************************************************************************
class sResponse_GameDBMgr_ErrorQuery_String
{
public:
	sPacketHeader		m_packetHeader;

	TCHAR				m_szMapString[1024];

	sResponse_GameDBMgr_ErrorQuery_String( TCHAR* pszMapStr )
	{
		ZeroMemory(this, sizeof(sResponse_GameDBMgr_ErrorQuery_String));

		m_packetHeader.usSize = sizeof( sResponse_GameDBMgr_ErrorQuery_String );
		m_packetHeader.usCmd	= GOONZUMC_RESPONSE_GAMEDBMGR_ERRORQUERY_STRING;

		StringCchCopy( m_szMapString, sizeof(m_szMapString), pszMapStr );
	}
};

#pragma pack()

#endif

