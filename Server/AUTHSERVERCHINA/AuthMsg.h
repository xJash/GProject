#ifndef _AUTHMSG_H
#define _AUTHMSG_H

#include "itzbase.h"

enum {
		AUTHMSG_REQUEST_FRONTAUTH = 1,
		AUTHMSG_REQUEST_GAMEAUTH,
		AUTHMSG_REQUEST_MASTERAUTH,
		AUTHMSG_REQUEST_FRONTJOINGAME,
		AUTHMSG_REQUEST_GAMELOGOUT,
		AUTHMSG_REQUEST_GAMELOGIN,

		AUTHMSG_RESPONSE_FRONTAUTH = 1000,
		AUTHMSG_RESPONSE_GAMEAUTH,
		AUTHMSG_RESPONSE_MASTERAUTH,
		AUTHMSG_RESPONSE_FRONTJOINGAME,
		AUTHMSG_RESPONSE_GAMELOGOUT,
		AUTHMSG_RESPONSE_GAMELOGIN,

		AUTHMSG_REPORT_GAMEHEARTBEAT = 10000
};

#pragma pack(1)

//-----------------------------------------------------------------------------
// ���� ��û (����Ʈ���� -> ��������)
//-----------------------------------------------------------------------------
struct sRequest_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};


//-----------------------------------------------------------------------------
// ���� ��û (���Ӽ��� -> ��������)
//-----------------------------------------------------------------------------
struct sRequest_GameAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siAuthKey;			
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
};


//-----------------------------------------------------------------------------
// ���� ��û (�����ͼ��� -> ��������)
//-----------------------------------------------------------------------------
struct sRequest_MasterAuth
{
	sPacketHeader		packetHeader;			
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
};


//-----------------------------------------------------------------------------
// ���� ���� (�������� -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sResponse_FrontAuth
{
	sPacketHeader	packetHeader;

	UI16			usResult;				// 0:����   1:����

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	SI32			siAuthKey;

	SI16			siGameMasterLevel;
	
	SI32			siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32			siBlockYear;
	SI32			siBlockMonth;
	SI32			siBlockDay;
	SI32			siBlockHour;
	SI32			siBlockMin;
	TCHAR			szBlockReason[ 30 ];

	bool			bAlreadyMakeCharSwitch;

	TCHAR			szServerName[ 20 ];

	SI32			siAccountStatus;

};



//-----------------------------------------------------------------------------
// ���� ���� (�������� -> ���Ӽ���)
//-----------------------------------------------------------------------------
struct sResponse_GameAuth
{
	sPacketHeader		packetHeader;

	UI32				uiIDNum;	
	SI16				siSex;						// 1 ���� , 0 ���� 				
	UI16				usCharID;				 
	SI16				siGameMasterLevel;

	SI32				siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32				siBlockYear;
	SI32				siBlockMonth;
	SI32				siBlockDay;
	SI32				siBlockHour;
	SI32				siBlockMin;
	TCHAR				szBlockReason[ 30 ];

	SI32				siAccountStatus;
};

//-----------------------------------------------------------------------------
// �α� �ƿ� ���� (�������� -> ���Ӽ���)
//-----------------------------------------------------------------------------
struct sRequest_GameLogout
{
	sPacketHeader		packetHeader;

	UI32				uiIDNum;	
	TCHAR				szAccountID[ 20 ];
};


//-----------------------------------------------------------------------------
// ���� ���� (�������� -> �����ͼ���)
//-----------------------------------------------------------------------------
struct sResponse_MasterAuth
{
	sPacketHeader		packetHeader;

	UI16				usResult;
};


//-----------------------------------------------------------------------------
// ��Ʈ ��Ʈ (���Ӽ��� -> �������� )
//-----------------------------------------------------------------------------
struct sReportToAuth_GameHeartbeat
{
	sPacketHeader		packetHeader;
	
	UI16				serverId;
	UI16				worldId;
};


//-----------------------------------------------------------------------------
// ���� ���� ��û (����Ʈ���� -> ��������)
//-----------------------------------------------------------------------------
struct sRequest_FrontJoinGame
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				userid[ 20 ];
	TCHAR				cookie[ 20 ];
	TCHAR				szIP[ 20 ];
	TCHAR				jumincode[ 8 ];
	TCHAR				userpw[ 20 ];
};

//-----------------------------------------------------------------------------
// ���� ���� ���� (�������� -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sResponse_FrontJoinGame
{
	sPacketHeader		packetHeader;

	SI32				siResult;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

};


#pragma pack()

#endif

