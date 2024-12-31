#ifndef _FRONTMSG_H
#define _FRONTMSG_H

#include "itzbase.h"

struct GAMESERVER_BASEINFO
{
	UI16	worldId;						// ���� ID
	TCHAR	worldname[ 20 ];				// �����
	SI32	siServerID;						// ���� ID
	TCHAR	gameserverip[ 16 ];				// ���� IP
	UI16	gameserverport;					// ���� PORT
	TCHAR	opendate[ 15 ];					// ���� ���� �ð�
	TCHAR	shortmessage[ 64 ];				// ª�� �ȳ���
};


struct GAMESERVER_REFRESHINFO
{
	UI16	worldId;						// ���� ID
	UI16	state;							// 0:���Ӱ���
	// 1:��������ο��ʰ�  2:������  3:���¿���
	UI16	currentConnections;				// ������������
};

struct GAMESERVER_GAMESERVERINFO
{
	TCHAR	goonzuname[ 20 ];				// ���� ĳ���� �̸� 
	TCHAR	goonzutext[ 256 ];				// ���� �λ縻 
	SI32	population;						// �鼺��
	SI32	currentPrice;					// �ü�
	SI32	npcrate;						//
	SI32	fixationmoney;					// 
};

struct WORLDINFO
{
	GAMESERVER_BASEINFO			baseinfo;		// �⺻���� ����
	GAMESERVER_REFRESHINFO		refreshinfo;	// �ֱ������� ������Ʈ �Ǵ� ����( 5�� ���� )
	GAMESERVER_GAMESERVERINFO	gameserverinfo;	// ���Ӽ��� ����	
};

enum {
	FRONTMSG_REQUEST_LOGIN = 1, 
	FRONTMSG_REQUEST_NOTICE,
	FRONTMSG_REQUEST_WORLDLIST,
	FRONTMSG_REQUEST_PATCHINFO,
	FRONTMSG_REQUEST_PATCHTEXT,
	FRONTMSG_REQUEST_PATCHTEXT2,
	FRONTMSG_REQUEST_JOINGAME,

	FRONTMSG_HEARTBEAT,

	FRONTMSG_REQUEST_NETMARBLEJP_LOGIN,

	FRONTMSG_REQUEST_PINGTEST,
	FRONTMSG_RESPONSE_PINGTEST,
	
	FRONTMSG_REQUEST_HANAUTH_LOGIN,

	//FRONTMSG_REQUEST_HANGAMEJP_LOGIN,

	FRONTMSG_REQUEST_DIFFHELLMAN_KEY,

	FRONTMSG_REQUEST_TAIWAN_LOGIN,

	//---------------------------------------------------------
	//KHY - 0204 -  �߱� PurpleAuth ���� ���
	FRONTMSG_REQUEST_PORTEAUTH_LOGIN,

	//---------------------------------------------------------
	//KHY - 0617 - �Ϻ� ä�θ� �߰�.	
	FRONTMSG_REQUEST_HANGAMEJP_LOGIN,
	FRONTMSG_REQUEST_GAMANIAJP_LOGIN,
	FRONTMSG_REQUEST_GAMEPOTJP_LOGIN,
	FRONTMSG_REQUEST_NDEJP_LOGIN,
	FRONTMSG_REQUEST_NEXONJP_LOGIN,
	//---------------------------------------------------------

	// PCK : IOVATION ���� �߰� (2009.02.03)
	FRONTMSG_REQUEST_ENGLISH_LOGIN,

	// [����] USA ���ο� ����.
	FRONTMSG_REQUEST_USA_LOGIN,

	// [����] EUROPE ���� �߰�
	FRONTMSG_REQUEST_EUROPE_LOGIN,

	//	[��ȣ_NHN->NDOORS] ���� �߰�
	FRONTMSG_REQUEST_KOREA_LOGIN,

	//---------------------------------------------------------
	FRONTMSG_RESPONSE_LOGIN = 1000,
	FRONTMSG_RESPONSE_NOTICE,
	FRONTMSG_RESPONSE_WORLDLIST,
	FRONTMSG_RESPONSE_PATCHINFO,
	FRONTMSG_RESPONSE_PATCHTEXT,
	FRONTMSG_RESPONSE_PATCHTEXT2,
	FRONTMSG_RESPONSE_JOINGAME,

	FRONTMSG_RESPONSE_NETMARBLEJP_LOGIN,
	FRONTMSG_RESPONSE_DIFFHELLMAN_KEY,

	FRONTMSG_NOTIFY_MESSAGE = 9000,
	FRONTMSG_NOTIFY_WORLDUPDATE,
	FRONTMSG_NOTIFY_WORLDREFRESHALL,

	FRONTMSG_REPORT_GAMEHEARTBEAT = 10000,
	FRONTMSG_REQUEST_GAMESERVERINFO,
	FRONTMSG_RESPONSE_GAMESERVERINFO,

	FRONTMSG_RESPONSE_PROMOTER_INFO = 11000,

	FRONTMSG_RESPONSE_SECRETKEY = 30000
};

#pragma pack(1)


//-----------------------------------------------------------------------------
// HeartBeat
//-----------------------------------------------------------------------------
struct sResponse_HeartBeat
{
	sPacketHeader		packetHeader;

};

//-----------------------------------------------------------------------------
// ��ȣȭŰ����
//-----------------------------------------------------------------------------
struct sResponse_SecretKey
{
	sPacketHeader		packetHeader;

	UI08				ucTemp1;
	UI08				ucTemp2;
	UI08				ucKey1;
	UI08				ucTemp3;
	UI08				ucKey2;
};

//-----------------------------------------------------------------------------
// ���� ���� ���� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) ��ġŬ���̾�Ʈ 
//-----------------------------------------------------------------------------
struct sRequest_PatchInfo
{

	sPacketHeader		packetHeader;

	UI32				uiCurrentVersion;
};

//-----------------------------------------------------------------------------
// ���� ���� ���� ���� (����Ʈ���� -> Ŭ���̾�Ʈ ) ��ġŬ���̾�Ʈ  
//-----------------------------------------------------------------------------
struct sResponse_PatchInfo
{
	sPacketHeader		packetHeader;

	UI32				uiCount;
	UI32				uiVersionHistory[ 100 ];

	TCHAR				szAddr[ 128 ];						// ��ġ ���� �ּ� 
	TCHAR				szPath[ 128 ];						// ��ġ ���� ���� 
	TCHAR				szID[ 32 ];							// ��ġ ���� ID
	TCHAR				szPW[ 32 ];							// ��ġ ���� PW
	UI16				usPort;								// ��ġ ���� Port

	TCHAR				szAddr_2[ 128 ];						// ��ġ ����2 �ּ� 
	TCHAR				szPath_2[ 128 ];						// ��ġ ����2 ���� 
	TCHAR				szID_2[ 32 ];							// ��ġ ����2 ID
	TCHAR				szPW_2[ 32 ];							// ��ġ ����2 PW
	UI16				usPort_2;								// ��ġ ����2 Port


};


//-----------------------------------------------------------------------------
// ��ġ �ؽ�Ʈ ��û (Ŭ���̾�Ʈ -> ����Ʈ����) ��ġŬ���̾�Ʈ 
//-----------------------------------------------------------------------------
struct sRequest_PatchText
{
	sPacketHeader		packetHeader;
};

//-----------------------------------------------------------------------------
// ��ġ �ؽ�Ʈ ��û2 (Ŭ���̾�Ʈ -> ����Ʈ����) ��ġŬ���̾�Ʈ 
//-----------------------------------------------------------------------------
struct sRequest_PatchText2
{
	sPacketHeader		packetHeader;
};


//-----------------------------------------------------------------------------
// ��ġ �ؽ�Ʈ ���� (����Ʈ���� -> Ŭ���̾�Ʈ ) ��ġŬ���̾�Ʈ  
//-----------------------------------------------------------------------------
struct sResponse_PatchText
{
	sPacketHeader		packetHeader;

	UI16				usTextSize;
	TCHAR				szText[ 25000 ];
};


//-----------------------------------------------------------------------------
// ��ġ �ؽ�Ʈ ���� (����Ʈ���� -> Ŭ���̾�Ʈ ) ��ġŬ���̾�Ʈ  
//-----------------------------------------------------------------------------
struct sResponse_PatchText2
{
	sPacketHeader		packetHeader;

	BOOL				IsLastPacket;

	UI16				usTextSize;
	TCHAR				szText[ 5000 ];
};


//-----------------------------------------------------------------------------
// �ݸ��� �α���(��ȣȭ) ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_NetmarbleJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 100 ];
	TCHAR				userpw[ 100 ];
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// �븸 �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_Taiwan_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				szGameAccount[ 30 ];
	TCHAR				szOneTimePassword[ 40 ];
	TCHAR				macaddress[ 20 ];
};


//-----------------------------------------------------------------------------
// �ݸ��� �α���(��ȣȭ) ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sResponse_NetmarbleJP_LogIn
{
	sPacketHeader		packetHeader;

	SI32				siResult;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
};

//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�.



//-----------------------------------------------------------------------------
// �Ѱ��ӷα��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) - ID�ڿ� [~@HG]  
//-----------------------------------------------------------------------------
struct sRequest_HANGAMEJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
//  �����Ͼ� �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) - ID�ڿ� [~@GA]  
//-----------------------------------------------------------------------------
struct sRequest_GAMANIAJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// ������ �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) - ID�ڿ� [~@GP] 
//-----------------------------------------------------------------------------
struct sRequest_GAMEPOTJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// NDE�α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) - * ID�ڿ� [~@ND] ���� ���Ѽ� ������ �Ѵ�..* 
//-----------------------------------------------------------------------------
struct sRequest_NDEJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// �ؽ� �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����) -ID�ȿ� ��Ÿ������ �� ���´�.(�Ľ��� �ڿ� ����)
//-----------------------------------------------------------------------------
struct sRequest_NEXONJP_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 512 ]; // 319 ����, �˳��ϰ�.
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//---------------------------------------------------------

//-----------------------------------------------------------------------------
// �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_LogIn
{
	sPacketHeader		packetHeader;

/*#ifdef _CHINA
	TCHAR				userid[ 40 ];
	TCHAR				userpw[ 40 ];
#else*/
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
//#endif
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// HanAuth �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_HanAuth_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
//KHY - 0204 -  �߱� PurpleAuth ���� ���
// �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_PorteAuth_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				authstring[ 2048 ];  // SIZE_AUTHTICKET �� ���ƾ� �Ѵ�.
	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
//  IOVATION �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_English_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];
	TCHAR				macaddress[ 20 ];

	TCHAR				Blackbox[ 2048 ];
};

//-----------------------------------------------------------------------------
// [����] USA ���ο� ����. 
//-----------------------------------------------------------------------------
struct sRequest_USA_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				authstring[ 4096 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// [����] Europe �α��� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_EUROPE_LogIn
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				userpw[ 20 ];

	TCHAR				macaddress[ 20 ];
};

//-----------------------------------------------------------------------------
// �α��� ���� (����Ʈ���� -> Ŭ���̾�Ʈ)
//-----------------------------------------------------------------------------
struct sResponse_LogIn
{
	sPacketHeader		packetHeader;

	UI16				usResult;											// 0: ���Ӽ���  1:���̵���� 2:�н�������� 3:���������ƴ� 4:������������ 5.DB����
	SI32				siAuthKey;

	// �ؽ� ä�θ��� ���� IDüũ -�ؽ��� DB���� ID�� ��ȯ�Ǿ� ���;� �Ѵ�.
	char			userid[ 20 ];
	
	SI16				siGameMasterLevel;

	SI32				siBlockMode;			// ���� ����. 
	SI32				siBlockYear, siBlockMonth, siBlockDay, siBlockHour, siBlockMinute;
	TCHAR				szBlockReason[30];

	bool				bAlreadyMakeCharSwitch;

	TCHAR				szServerName[20];
	SI32				siAccountStatus;

	UI08				m_uiRealAge;			// �ֹε�ϻ� ����(�����ѱ�����)

};


//-----------------------------------------------------------------------------
// ���� ���� ��û 
//-----------------------------------------------------------------------------
struct sRequest_JoinGame
{
	sPacketHeader		packetHeader;

	TCHAR				userid[ 20 ];
	TCHAR				cookie[ 20 ];
	TCHAR				jumin[ 8 ];
	TCHAR				userpw[ 20 ];


	sRequest_JoinGame()
	{
		memset( this, 0, sizeof( sRequest_JoinGame ) );
	}
};

//-----------------------------------------------------------------------------
// ���� ���� ��û 
//-----------------------------------------------------------------------------
struct sResponse_JoinGame
{
	sPacketHeader		packetHeader;

	SI32				siResult;
};

//-----------------------------------------------------------------------------
// ���� ���� ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_Notice
{
	sPacketHeader		packetHeader;
};


//-----------------------------------------------------------------------------
// ���� ����Ʈ ��û (Ŭ���̾�Ʈ -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sRequest_WorldList
{
	sPacketHeader		packetHeader;

	TCHAR				szAccountID[20];
};



//-----------------------------------------------------------------------------
// ���� ���� ���� (����Ʈ���� -> Ŭ���̾�Ʈ)
//-----------------------------------------------------------------------------
struct sResponse_Notice
{
	sPacketHeader		packetHeader;

	TCHAR				text[ 8000 ];
};


//-----------------------------------------------------------------------------
// ���� ����Ʈ ���� (����Ʈ���� -> Ŭ���̾�Ʈ)
//-----------------------------------------------------------------------------
struct sResponse_WorldList
{
	sPacketHeader			packetHeader;	

	UI16					usCount;
	WORLDINFO				worldinfo[ 1 ];

};

//-----------------------------------------------------------------------------
// ���� ���� ���� �˸� (����Ʈ���� -> Ŭ���̾�Ʈ)
//-----------------------------------------------------------------------------
struct sNotify_WorldRefreshAll
{
	sPacketHeader			packetHeader;	

	UI16					usCount;
	GAMESERVER_REFRESHINFO	refreshinfo[ 1 ];
};


//-----------------------------------------------------------------------------
// �޽��� �˸� (����Ʈ���� -> Ŭ���̾�Ʈ)
//-----------------------------------------------------------------------------
struct sNotify_WorldShortMessage
{
	sPacketHeader			packetHeader;

	UI16					worldId;
	TCHAR					shortmessage[ 64 ];
};


//-----------------------------------------------------------------------------
// ���Ӽ������� ���� (���Ӽ��� -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sReportToFront_GameHeartbeat
{
	sPacketHeader			packetHeader;

	UI16					serverId;
	GAMESERVER_REFRESHINFO	refreshinfo;
};

//-----------------------------------------------------------------------------
// ���Ӽ������� (���Ӽ��� -> ����Ʈ����)
//-----------------------------------------------------------------------------
struct sResponseToFront_GameServerInfo
{
	sPacketHeader				packetHeader;

	UI16						serverId;
	GAMESERVER_GAMESERVERINFO	gameserverinfo;

};

//***************************************************************************************************
//
// Class Name 		: sRequest_PingTest
//
// Last Modified 	: 2007 / 03 / 21
// Created		 	: �豤��
//
// Function			: ��ġŬ���̾�Ʈ�� ���׽�Ʈ�� �Ѵ�.
//
//***************************************************************************************************
struct sRequest_PingTest
{
	sPacketHeader		packetHeader;

	UI08	m_uiIDCType;
	SI32	m_siFrontServerIndex;	
};

//***************************************************************************************************
//
// Class Name 		: sResponse_PingTest
//
//Last Modified 	: 2007 / 03 / 21
// Created		 	: �豤��
//
// Function			: ��ġŬ���̾�Ʈ�� ���׽�Ʈ�� �Ѵ�.
//
//***************************************************************************************************
struct sResponse_PingTest
{
	sPacketHeader		packetHeader;

	UI08	m_uiIDCType;
	SI32	m_siFrontServerIndex;	
};

//***************************************************************************************************
//
// Class Name 		: sRequest_DiffHellManKey
//
// Last Modified 	: 2007 / 07 / 02
// Created		 	: �豤��
//
// Function			: �߱��� ������ ��ȣȭ�� �ѹ� �� �Ѵ�
//
//***************************************************************************************************
struct sRequest_DiffHellManKey
{
	sPacketHeader		packetHeader;

	TCHAR	tempKey[20];
};

//***************************************************************************************************
//
// Class Name 		: sResponse_DiffHellManKey
//
// Last Modified 	: 2007 / 07 / 02
// Created		 	: �豤��
//
// Function			: �߱��� ������ ��ȣȭ�� �ѹ� �� �Ѵ�
//
//***************************************************************************************************
struct sResponse_DiffHellManKey
{
	sPacketHeader		packetHeader;

	TCHAR	tempKey[20];
};


//***************************************************************************************************
//
// Class Name 		: sResponse_Promoter_Info
//
// Last Modified 	: 2009 / 07 / 27
// Created		 	: Ȳ����
//
// Function			: �߱��� ��������Ʈ ��û�ÿ� ���θ��� ������ Ŭ���̾�Ʈ�� ������.
//
//***************************************************************************************************
struct sResponse_Promoter_Info
{
	sPacketHeader		packetHeader;

	TCHAR				m_szPromoterName[20];
	SI32				m_siServerID;
	int					m_ret;
};

#pragma pack()

#endif

