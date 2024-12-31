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

		AUTHMSG_REQUEST_HANAUTH_FRONTAUTH,
		AUTHMSG_REQUEST_HANAUTH_GAMEAUTH,

		//---------------------------------------------------------
		//KHY - 0204 -  �߱� PurpleAuth ���� ���
		AUTHMSG_REQUEST_PORTEAUTH_FRONTAUTH,
		AUTHMSG_REQUEST_PORTEAUTH_GAMEAUTH,

		AUTHMSG_REQUEST_TAIWAN_FRONTAUTH,
		AUTHMSG_REQUEST_TAIWAN_GAMEAUTH,

		AUTHMSG_REQUEST_HANAUTH_GAMERUNAUTH,

		AUTHMSG_REQUEST_GMTOOLAUTH,

		//---------------------------------------------------------
		//KHY - 0617 - �Ϻ� ä�θ� �߰�.
		AUTHMSG_REQUEST_HANGAMEJP_FRONTAUTH,
		AUTHMSG_REQUEST_GAMANIAJP_FRONTAUTH,
		AUTHMSG_REQUEST_GAMEPOTJP_FRONTAUTH,
		AUTHMSG_REQUEST_NDEJP_FRONTAUTH,
		AUTHMSG_REQUEST_NEXONJP_FRONTAUTH,
		//---------------------------------------------------------
		
		// PCK : IOVATION ���� �߰� (2009.02.03)
		AUTHMSG_REQUEST_ENGLISH_FRONTAUTH,

		// [����] USA ���ο� ����.
		AUTHMSG_REQUEST_USA_FRONTAUTH,

		// [����] Europe ����
		AUTHMSG_REQUEST_EUROPE_FRONTAUTH,

		// [��ȣ_NHN->NDOORS] Korea ����
		AUTHMSG_REQUEST_KOREA_FRONTAUTH,


		//---------------------------------------------------------
		AUTHMSG_RESPONSE_FRONTAUTH = 1000,
		AUTHMSG_RESPONSE_GAMEAUTH,
		AUTHMSG_RESPONSE_MASTERAUTH,
		AUTHMSG_RESPONSE_FRONTJOINGAME,
		AUTHMSG_RESPONSE_GAMELOGOUT,
		AUTHMSG_RESPONSE_GAMELOGIN,

		AUTHMSG_RESPONSE_HANAUTH_FRONTAUTH,
		AUTHMSG_RESPONSE_HANAUTH_GAMEAUTH,

		AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH,

		AUTHMSG_RESPONSE_GMTOOLAUTH,

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

//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�.
//-----------------------------------------------------------------------------
// ���� ��û (����Ʈ���� -> ��������) : �Ѱ���, �����Ͼ�, ������, NDE , NEXON
//-----------------------------------------------------------------------------
struct sRequest_HANGAMEJP_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};
struct sRequest_GAMANIAJP_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};
struct sRequest_GAMEPOTJP_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};
struct sRequest_NDEJP_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};
struct sRequest_NEXONJP_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;
	
	TCHAR				userid[ 512 ]; // �ؽ��� ID�� ������ ��Ƽ� �ѱ��.
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};

//---------------------------------------------------------

//-----------------------------------------------------------------------------
// ���� ��û (����Ʈ���� -> ��������) : TAIWAN
//-----------------------------------------------------------------------------
struct sRequest_Taiwan_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				gameaccount[ 30 ];
	TCHAR				onetimepassword[ 40 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// ���� ��û (����Ʈ���� -> ��������) : NHN : HANAUTH
//-----------------------------------------------------------------------------
struct sRequest_HanAuth_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};


//-----------------------------------------------------------------------------
//KHY - 0204 -  �߱� PurpleAuth ���� ���
// ���� ��û (����Ʈ���� -> ��������) : NHN : PorteAuth
//-----------------------------------------------------------------------------
struct sRequest_PorteAuth_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// IOVATION ���� ��û (����Ʈ���� -> ��������)
//-----------------------------------------------------------------------------
struct sRequest_English_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				userIP[ 20 ];
	TCHAR				macaddress[ 20 ];

	TCHAR				Blackbox[ 2048 ];
};


//-----------------------------------------------------------------------------
// [����] USA ���ο� ����.
//-----------------------------------------------------------------------------
struct sRequest_USA_FrontAuth
{
	sPacketHeader		packetHeader;

	UI16				usPacketUnique;
	UI16				usFrontCharID;

	TCHAR				authstring[ 4096 ];

	TCHAR				Blackbox[ 2048 ];
};

//-----------------------------------------------------------------------------
// [����] Europe ����.
//-----------------------------------------------------------------------------
struct sRequest_EUROPE_FrontAuth
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
	// ������ ������ ������ ���� IDC����(1,2), ��������, ���������� ���ڷ� �ȴ�.
	// 20102 ctc �� 1������ 2��° ����
	TCHAR				userServerID[ 20 ];	
	TCHAR				userIP[ 20 ];
};

//-----------------------------------------------------------------------------
// ���� ��û (���Ӽ��� -> ��������) : NHN HANAUTH
//-----------------------------------------------------------------------------
struct sRequest_HanAuth_GameAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siAuthKey;			

	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];

	UI16				usServerAge;
};

//-----------------------------------------------------------------------------
// ���� ��û (���Ӽ��� -> ��������) : �븸
//-----------------------------------------------------------------------------
struct sRequest_Taiwan_GameAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siAuthKey;			

	TCHAR				gameaccount[ 30 ];
	TCHAR				onetinepassword[ 40 ];
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

	// �ؽ� ä�θ��� ���� ID�߰�.
	char			userid[ 20 ];

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

	UI08			m_uiRealAge;			// (�ѱ�) �ֹε�ϻ��� ����

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
	SI32				siPlayingTime;

	UI32				uiIDNo;						// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11
	SI16				siDormancyState;			// �޸� �������� �ƴ���
};

//-----------------------------------------------------------------------------
// �α� �ƿ� ���� (�������� -> ���Ӽ���)
//-----------------------------------------------------------------------------
struct sRequest_GameLogout
{
	sPacketHeader		packetHeader;

	UI32				uiIDNum;	
	TCHAR				szAccountID[ 20 ];
	TCHAR				userServerID[ 20 ];	
	TCHAR				szPlayingCharNmae[ 20 ];
	SI32				siLevel;
	SI32 				siPlayTimeMinute;
	
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

//-----------------------------------------------------------------------------------------------
// ���� ��û(���ӽ��൵�߿� ��������üũ) (���Ӽ��� -> ��������) : NHN HANAUTH (PCK : 2007.09.19)
//-----------------------------------------------------------------------------------------------
struct sRequest_HanAuth_GameRunAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;			

	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];

	UI16				usServerAge;
};

//---------------------------------------------------------------------------------
// ���� ����(���ӽ��൵�߿� ��������üũ) (�������� -> ���Ӽ���) : PCK - 2007.09.19
//---------------------------------------------------------------------------------
struct sResponse_GameRunAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siResult;	// 0 : ��������, 1 : ��������
};

struct sRequest_GMToolAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
};


struct sResponse_GMToolAuth
{
	sPacketHeader		packetHeader;

	UI16				usCharID;
	TCHAR				userid[ 20 ];

	SI32				siMasterLevel;
};


#pragma pack()

#endif

