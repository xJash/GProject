#ifndef _DBMSGGUILD_H
#define _DBMSGGUILD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "../CommonLogic/Guild/Guild.h"
#include "../CommonLogic/Guild/GuildWar.h"
#include "../CommonLogic/Guild/Guild-Dungeon.h"
#include "../CommonLogic/Guild/GuildHuntMapWarManager.h"

//-----------------------------------------------------
// ��� ������ ��û�Ѵ�.
//-----------------------------------------------------
class sDBRequest_Guild_CreateGuild
{
public:
	sPacketHeader		packetHeader;

	SI32			siPersonID;
	SI32			siCharID;

	SI32			siVillageUnique;		// ���� ��û�� ��尡 ������ �ǹ��� �ִ� ���� ����ũ
	TCHAR			szGuildName[MAX_GUILD_NAME]; // ��� �̸�

	cltDate			clDate; // ��û�� - cltGuildInfo�� clDate�� ����.

	sDBRequest_Guild_CreateGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_CreateGuild));
	}

	sDBRequest_Guild_CreateGuild(SI32 personid,SI32 charid , SI32 villageunique,TCHAR *guildname,cltDate *cldate)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_CreateGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CREATEGUILD;

		siPersonID = personid;
		siCharID = charid;

		siVillageUnique = villageunique;
		MStrCpy(szGuildName,guildname,MAX_GUILD_NAME);

		clDate.Set(cldate);
	}
};

class sDBResponse_Guild_CreateGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID;

	cltGuildInfo		clInfo;				// ������ ����� ����

	sDBResponse_Guild_CreateGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_CreateGuild ) );
	}
};

//-----------------------------------------------------
// ��� ��ü�� ��û�Ѵ�.
//-----------------------------------------------------
class sDBRequest_Guild_DestroyGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID;

	SI32				siGuildUnique; // ��ü�� ����� �ε���

	SI32				siVillageUnique; // ��ü�� ��尡 ���� �ǹ��� �ִ� ���� ����ũ

	SI08				siReason;

	sDBRequest_Guild_DestroyGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_DestroyGuild));
	}

	sDBRequest_Guild_DestroyGuild(SI32 personid,SI32 charid,SI32 guildunique,SI32 villageunique=0, SI32 reason = 0 )
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_DestroyGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_DESTROYGUILD;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = guildunique;

		siVillageUnique = villageunique ;

		siReason = reason;
	}
};

class sDBResponse_Guild_DestroyGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID;

	SI32				siGuildUnique;
	SI32				siVillageUnique;

	SI32				siReason;

	sDBResponse_Guild_DestroyGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_DestroyGuild ) );
	}
};

//-----------------------------------------------------
// ��� ������ ��û�Ѵ�.
//-----------------------------------------------------
class sDBRequest_Guild_JoinGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID;

	cltGuildInfo		clInfo; // ���Կ�û�� ����� ����

	sDBRequest_Guild_JoinGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_JoinGuild));
	}

	sDBRequest_Guild_JoinGuild(SI32 personid,SI32 charid,cltGuildInfo*pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_JoinGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_JOINGUILD;

		siPersonID = personid ;
		siCharID = charid ;

		clInfo.Set(pclinfo);
	}
};

class sDBResponse_Guild_JoinGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID;

	cltGuildInfo		clInfo; // ���Կ�û�� ����� ����

	sDBResponse_Guild_JoinGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_JoinGuild ) );
	}
};

//-----------------------------------------------------
// ��� ������ �㰡,���㸦 �����Ѵ�.
//-----------------------------------------------------
class sDBRequest_Guild_ConfirmJoinGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	bool				bConfirm; // TRUE�� �㰡 , FALSE�� ����

	SI32				siStandingPersonID; // �㰡,����Ǵ� personid

	sDBRequest_Guild_ConfirmJoinGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ConfirmJoinGuild));
	}

	sDBRequest_Guild_ConfirmJoinGuild(SI32 personid,SI32 charid,bool confirm,SI32 standingpersonid)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ConfirmJoinGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CONFIRMJOINGUILD;

		siPersonID = personid ;
		siCharID = charid ;

		bConfirm = confirm ;

		siStandingPersonID = standingpersonid ;
	}
};

class sDBResponse_Guild_ConfirmJoinGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	bool				bConfirm;			// TRUE�� �㰡 , FALSE�� ����

	SI32				siStandingPersonID; // �㰡,����Ǵ� personid

	cltGuildInfo		clInfo; // ����� ����� ����

	sDBResponse_Guild_ConfirmJoinGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ConfirmJoinGuild ) );
	}
};

//-----------------------------------------------------
// ��� Ż�� ��û�Ѵ�.
//-----------------------------------------------------
class sDBRequest_Guild_LeaveGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	//SI32				siCharID ;

	SI32				siGuildUnique;

	sDBRequest_Guild_LeaveGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_LeaveGuild));
	}

	sDBRequest_Guild_LeaveGuild(SI32 personid,/*SI32 charid,*/SI32 guildunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_LeaveGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_LEAVEGUILD;

		siPersonID = personid ;
		//siCharID = charid ;

		siGuildUnique = guildunique ;
	}
};

class sDBResponse_Guild_LeaveGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clInfo; // ����� ����� ����

	sDBResponse_Guild_LeaveGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_LeaveGuild ) );
	}
};

//-------------------------------------------------------------------
// ��� ������ �̵��� ��û�Ѵ�.(�ٸ� ���� ��� �ǹ��� �̵� ��û)
//-----------------------------------------------------------------------
class sDBRequest_Guild_ChangeVillage
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique;			// �ű� ����� ����ũ
	SI32				siVillageUnique;		// ��尡 �Űܰ� ������ ����ũ
	SI32				siLeaveVillageUnique;	// ������ ��尡 �ִ� ���� ����ũ

	sDBRequest_Guild_ChangeVillage()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeVillage));
	}

	sDBRequest_Guild_ChangeVillage(SI32 personid,SI32 charid,SI32 guildunique,SI32 villageunique,SI32 leavevillageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeVillage );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGEVILLAGE;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = guildunique ;
		siVillageUnique = villageunique ;
		siLeaveVillageUnique = leavevillageunique ;
	}
};

class sDBResponse_Guild_ChangeVillage
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clInfo; // ����� ����� ����

	sDBResponse_Guild_ChangeVillage()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ChangeVillage ) );
	}
};

//-------------------------------------------------------------------
// ����� ������ ��û�Ѵ�.
//-----------------------------------------------------------------------
class sDBRequest_Guild_GetGuildInfo
{
public:
	sPacketHeader		packetHeader;


	sDBRequest_Guild_GetGuildInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_GetGuildInfo));
	}

	sDBRequest_Guild_GetGuildInfo(bool bStart)
	{
		if ( bStart )
		{
			packetHeader.usSize = sizeof( sDBRequest_Guild_GetGuildInfo );
			packetHeader.usCmd	= DBMSG_REQUEST_GUILD_GETGUILDINFO;
		}
	}
};

class sDBResponse_Guild_GetGuildInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siStartPos;

	cltGuildInfo		clInfo[MAX_GUILD_PER_DBLIST];

	sDBResponse_Guild_GetGuildInfo()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_GetGuildInfo ) );
	}
};

//class sDBRequest_Guild_ChangeVillageList
//{
//public:
//	sPacketHeader		packetHeader;
//
//	sDBRequest_Guild_ChangeVillageList()
//	{
//		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeVillageList));
//	}
//
//	sDBRequest_Guild_ChangeVillageList(bool bStart)
//	{
//		if ( bStart )
//		{
//			packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeVillageList );
//			packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGEVILLAGELIST;
//		}
//	}
//};
//
//class sDBResponse_Guild_ChangeVillageList
//{
//public:
//	sPacketHeader		packetHeader;
//
//	SI32				siResult;			// �����.
//
//	cltGuildChangeVillageInfo clInfo[MAX_GUILD_NUM];
//
//
//	sDBResponse_Guild_ChangeVillageList()
//	{
//		memset( this, 0, sizeof( sDBResponse_Guild_ChangeVillageList ) );
//	}
//};


//-------------------------------------------------------------------
// ��� ������ �㰡�Ѵ�.
//-----------------------------------------------------------------------
class sDBRequest_Guild_ConfirmCreateGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siUnique;	// ����� ����ũ
	bool				bConfirm;	// true�� �㰡 , false�� ����

	GMONEY				siMoney;	// ������� - ������û��(�����)�� �����ݿ��� ������. �� ����� ��� ���� ������ ��尳������
	GMONEY				siFee; // �Ӵ�� - �Ŵ� �������� ��

	cltDate				clDate; // ������ - cltGuildInfo�� clDate�� ������Ʈ ��Ų��.

	sDBRequest_Guild_ConfirmCreateGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ConfirmCreateGuild));
	}

	sDBRequest_Guild_ConfirmCreateGuild(SI32 personid,SI32 charid,SI32 unique,bool confirm,GMONEY money,GMONEY fee,cltDate *cldate)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ConfirmCreateGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CONFIRMCREATEGUILD;

		siPersonID = personid ;
		siCharID = charid ;

		siUnique = unique ;
		
		bConfirm = confirm ;

		siMoney = money ;
		siFee = fee;

		clDate.Set(cldate);
	}
};

class sDBResponse_Guild_ConfirmCreateGuild
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	bool				bConfirm;			// �������� �ź�����(�������� ������)

	SI32				siGuildUnique;		// ��ҽÿ��� ���
	cltGuildInfo		clInfo;

	GMONEY				siMoney;			// ������� - ������û��(�����)�� �����ݿ��� ������. �� ����� ��� ���� ������ ��尳������
	GMONEY				siFee;				// �Ӵ�� - �Ŵ� �������� ��

	GMONEY				siLeftMoney;		// ����忡�� ���� ��
	cltDate				clDate;				// ��� ������

	SI08				siBeforeConfirm;	// ���� = 0 ,���� = 2
	bool				bState;				// ���� = 1, ���� = 0 ( ���� ���� ���....)


	sDBResponse_Guild_ConfirmCreateGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ConfirmCreateGuild ) );
	}
};

//-------------------------------------------------------------------
// �α������ ���� �� �����Ѵ�.
//-----------------------------------------------------------------------
class sDBRequest_Guild_SetSecondMaster
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siSecondMasterPersonID; // �α������ �� personid

	bool				bSet; // true�� ����, false�� ����. 1��忡�� ���� 1���� �α������ �ִ�.

	sDBRequest_Guild_SetSecondMaster()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_SetSecondMaster));
	}

	sDBRequest_Guild_SetSecondMaster(SI32 personid,SI32 charid,SI32 secondmasterpersonid,bool set)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_SetSecondMaster );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_SETSECONDMASTER;

		siPersonID = personid ;
		siCharID = charid ;

		siSecondMasterPersonID = secondmasterpersonid ;

		bSet = set ;
	}
};

class sDBResponse_Guild_SetSecondMaster
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siSecondMasterPersonID; // �α������ �� personid

	bool				bSet ;

	cltGuildInfo		clInfo;

	sDBResponse_Guild_SetSecondMaster()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_SetSecondMaster ) );
	}
};

//----------------------------------------------------
// ��� �ڱ��� �����Ѵ�.
//---------------------------------------------
class sDBRequest_Guild_GiveGuildMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siGuildUnique;
	SI32				siPersonID;
	SI32				siCharID ;

	GMONEY				siMoney ; // ������ �ݾ�

	sDBRequest_Guild_GiveGuildMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_GiveGuildMoney));
	}

	sDBRequest_Guild_GiveGuildMoney(SI32 guildunique, SI32 personid,SI32 charid,GMONEY money)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_GiveGuildMoney );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_GIVEGUILDMONEY;

		siGuildUnique = guildunique;
		siPersonID = personid ;
		siCharID = charid ;

		siMoney = money ;
	}
};

class sDBResponse_Guild_GiveGuildMoney
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clinfo;

	GMONEY				siMoney ; // ������ �ݾ�
	GMONEY				siLeftMoney ; // �����ϰ� ���� �ݾ�

	sDBResponse_Guild_GiveGuildMoney()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_GiveGuildMoney ) );
	}
};

#define TYPE_GUILDPOINT_ADD_PLAYTIME		1	// �÷���Ÿ��
#define TYPE_GUILDPOINT_ADD_LEVELUP			2	// ������
#define TYPE_GUILDPOINT_ADD_MAKERARE		3	// ��ǰ ����
#define TYPE_GUILDPOINT_ADD_ENCHANT_5		4	// 5�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_ADD_ENCHANT_6		5	// 6�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_ADD_ENCHANT_7		6	// 7�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_ADD_FP				7	// ��õ�� ����Ʈ ȹ��
#define TYPE_GUILDPOINT_ADD_CHILD			8	// 20�����̻� ���� ����
#define TYPE_GUILDPOINT_ADD_SKILLLEVELUP	9	// ��ų ����ġ ������
#define TYPE_GUILDPOINT_ADD_GIVEGUILDMONEY	10	// ��� �ڱ� ����
#define TYPE_GUILDPOINT_REMOVE_DEAD			11	// ��� - ���Ƽ
#define TYPE_GUILDPOINT_GUILDWAR			12	// ����� ����� ����! - ������� ����Ʈ�� �ٲ��� �ʰ� ����� ������ ����ȴ�.
#define TYPE_GUILDPOINT_GUILDDUNGEON		13  // ����� ���������� ���ؼ�
#define TYPE_GUILDPOINT_DAILYQUEST			14	// Daily 
#define TYPE_GUILDPOINT_ADD_ENCHANT_8		15	// 8�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_ADD_ENCHANT_9		16	// 9�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_ADD_ENCHANT_10		17	// 10�ܰ� ��æƮ ����
#define TYPE_GUILDPOINT_DAILYQUEST2			18	// Daily 
//----------------------------------------------------
// ����� GP�� ��ȭ�Ǿ���.
//---------------------------------------------
class sDBRequest_Guild_ChangeGuildPoint
{
public:
	sPacketHeader		packetHeader;

	SI32				siGuildUnique; // ��� ����ũ

	SI32				siPersonID;
	SI32				siExp; // �߰��� exp - �ڱ� ������ ��� ���� 2���� ������Ʈ

	SI32				siType; // �߰��ϴ� ����
	SI32				siMax;	// �ִ밪. 0�̸� ������

	sDBRequest_Guild_ChangeGuildPoint()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeGuildPoint));
	}

	sDBRequest_Guild_ChangeGuildPoint(SI32 unique,SI32 personid,SI32 exp,SI32 type,SI32 max = 0 )
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeGuildPoint );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGEGUILDPOINT;

		siGuildUnique = unique ;

		siPersonID = personid ;
		siExp = exp ;

		siType = type ;
		siMax = max ;
	}
};

class sDBResponse_Guild_ChangeGuildPoint
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	cltGuildInfo		clinfo;				// ����� ��� ����

	sDBResponse_Guild_ChangeGuildPoint()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ChangeGuildPoint ) );
	}
};

//-----------------------------------------------
// �ǹ� �����Ḧ �����Ѵ�.
//----------------------------------------------
class sDBRequest_Guild_Give_Fee
{
public:
	   sPacketHeader		packetHeader;

	   SI32					siGuildUnique; // ��� ����ũ
	   GMONEY				siFee;	// ������ - ��� �ڱݿ��� ������.
	   cltDate				clDate;	// ������ ������ �ð�

	   sDBRequest_Guild_Give_Fee()
	   {
		   ZeroMemory(this, sizeof(sDBRequest_Guild_Give_Fee));
	   }

	   sDBRequest_Guild_Give_Fee(SI32 unique,GMONEY fee,cltDate*pcldate)
	   {
		   packetHeader.usSize = sizeof( sDBRequest_Guild_Give_Fee );
		   packetHeader.usCmd	= DBMSG_REQUEST_GUILD_GIVE_FEE;

		   siGuildUnique = unique ;
		   siFee = fee ;
		   clDate.Set(pcldate);
	   }
};

class sDBResponse_Guild_Give_Fee
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	cltGuildInfo		clinfo;				// ����� ��� ����

	GMONEY				siLeftStrMoney;		// ����� �ǹ� �ں���
	
	SI32				siFaultNum;			// ���� ���ڶ� �� �������� ��� ����Ƚ�� - 3��°�� ��� ��ü
	SI32				siGuildUnique;		// ��� ����ũ - ��ü�Ǿ��� ��� cltGuildInfo�� NULL�̹Ƿ� �̶� ���

	sDBResponse_Guild_Give_Fee()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_Give_Fee ) );
	}
};

//-----------------------------------------------
// ��� �ɷ�ġ�� ����Ǿ���.
//----------------------------------------------
class sDBRequest_Guild_ChangeStatus
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique; // ��� ����ũ

	cltGuildStatus		clinfo;

	sDBRequest_Guild_ChangeStatus()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeStatus));
	}

	sDBRequest_Guild_ChangeStatus(SI32 personid,SI32 charid,SI32 unique,cltGuildStatus*pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeStatus );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGESTATUS;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = unique ;

		clinfo.siBonus = pclinfo->siBonus ;
		clinfo.siDex = pclinfo->siDex ;
		clinfo.siHnd = pclinfo->siHnd ;
		clinfo.siLuk = pclinfo->siLuk ;
		clinfo.siMag = pclinfo->siMag ;
		clinfo.siStr = pclinfo->siStr ;
		clinfo.siVit = pclinfo->siVit ;
	}
};

class sDBResponse_Guild_ChangeStatus
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clinfo;				// ����� ��� ����

	sDBResponse_Guild_ChangeStatus()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ChangeStatus ) );
	}
};

//-----------------------------------------------
// ��� �ǹ��� �����ᰡ ����Ǿ���. - ���
//----------------------------------------------
class sDBRequest_Guild_SetStrFeeRate
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siVillageUnique;
	SI32				siFeeRate;

	sDBRequest_Guild_SetStrFeeRate()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_SetStrFeeRate));
	}

	sDBRequest_Guild_SetStrFeeRate(SI32 personid,SI32 charid,SI32 village,SI32 feerate)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_SetStrFeeRate );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_SETSTRFEERATE;

		siPersonID = personid ;
		siCharID = charid ;

		siVillageUnique = village ;
		siFeeRate = feerate ;
	}
};

class sDBResponse_Guild_SetStrFeeRate
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siVillageUnique;
	SI32				siFeeRate;

	sDBResponse_Guild_SetStrFeeRate()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_SetStrFeeRate ) );
	}
};

//---------------------------------------------
// ��尡 �������� �Ͽ���.
//--------------------------------------------
class sDBRequest_Guild_LevelUP
{
public:
	sPacketHeader		packetHeader;
	SI32				siGuildUnique;

	SI32				siLevel;

	sDBRequest_Guild_LevelUP()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_LevelUP));
	}

	sDBRequest_Guild_LevelUP(SI32 unique,SI32 level)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_LevelUP );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_LEVELUP;

		siGuildUnique = unique ;

		siLevel = level ;
	}
};

class sDBResponse_Guild_LevelUP
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	cltGuildInfo		clinfo;				// ����� ��� ����

	sDBResponse_Guild_LevelUP()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_LevelUP ) );
	}
};

//-----------------------------------------------
// ��� ��ũ�� �����Ͽ���.
//----------------------------------------------
class sDBRequest_Guild_SetMark
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique;
	SI32				siGuildMark;

	sDBRequest_Guild_SetMark()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_SetMark));
	}

	sDBRequest_Guild_SetMark(SI32 personid,SI32 charid,SI32 unique,SI32 mark)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_SetMark );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_SETMARK;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = unique ;
		siGuildMark = mark ;
	}
};

class sDBResponse_Guild_SetMark
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clinfo;

	sDBResponse_Guild_SetMark()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_SetMark ) );
	}
};

//-----------------------------------------------
// �̸��� �����Ͽ���
//----------------------------------------------
class sDBRequest_Guild_ChangeName
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique;
	TCHAR				szName[MAX_GUILD_NAME];

	sDBRequest_Guild_ChangeName()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeName));
	}

	sDBRequest_Guild_ChangeName(SI32 personid,SI32 charid,SI32 unique,TCHAR*pName)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeName );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGENAME;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = unique ;
		MStrCpy(szName,pName,MAX_GUILD_NAME);
	}
};

class sDBResponse_Guild_ChangeName
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clinfo;

	sDBResponse_Guild_ChangeName()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ChangeName ) );
	}
};

//-----------------------------------------------
// ��� ������ ����
//----------------------------------------------
class sDBRequest_Guild_ChangeMaster
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique;
	SI32				siNewPersonID;				// ��� �����͸� �Ѱ��� PersonID

	sDBRequest_Guild_ChangeMaster()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_ChangeMaster));
	}

	sDBRequest_Guild_ChangeMaster(SI32 personid, SI32 charid, SI32 unique, SI32 newpersonid)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_ChangeMaster );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHANGEMASTER;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = unique ;
		siNewPersonID = newpersonid;
	}
};
class sDBResponse_Guild_ChangeMaster
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI32				siCharID ;

	cltGuildInfo		clInfo;
	SI32				siNewPersonID;

	sDBResponse_Guild_ChangeMaster()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_ChangeMaster ) );
	}
};

class sDBRequest_Guild_CloseGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siGuildUnique;

	TCHAR				szGuildName[MAX_GUILD_NAME];

	sDBRequest_Guild_CloseGuild()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_CloseGuild));
	}

	sDBRequest_Guild_CloseGuild(SI32 personid, SI32 guildunique, TCHAR* guildname )
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_CloseGuild );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CLOSEGUILD;

		siPersonID = personid ;
		siGuildUnique = guildunique ;

		StringCchCopy( szGuildName, MAX_GUILD_NAME, guildname );
	}

};

class sDBResponse_Guild_CloseGuild
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siPersonID;
	SI32				siGuildUnique;

	TCHAR				szGuildName[MAX_GUILD_NAME];

	sDBResponse_Guild_CloseGuild()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_CloseGuild ) );
	}
};

class sDBRequest_GuildWar_AddReserve
{
public:
	sPacketHeader	packetHeader;

	SI32			siFieldIndex;
	SI32			siRoomIndex;

	SI32			siHomeGuildUnique;
	SI32			siAwayGUildUnique;

	// PCK : �α׿� ��Ŷ
	SI32			siPersonID;			// ������� ��û�� ���

	sDBRequest_GuildWar_AddReserve()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildWar_AddReserve));
	}

	sDBRequest_GuildWar_AddReserve(SI32 field, SI32 room, SI32 home, SI32 away, SI32 PersonID)
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildWar_AddReserve );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDWAR_ADDRESERVE;

		siFieldIndex = field;
		siRoomIndex = room;

		siHomeGuildUnique = home;
		siAwayGUildUnique = away;

		siPersonID = PersonID;
	}
};

class sDBResponse_GuildWar_AddReserve
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	// [�߰� : Ȳ���� 2007. 11. 7 �α׿� �̿�. ����� ����]
	SI32			siFieldIndex;
	SI32			siRoomIndex;

	SI32			siHomeGuildUnique;
	SI32			siAwayGUildUnique;

	// PCK : �α׿� ��Ŷ
	SI32			siPersonID;			// ������� ��û�� ���

	sDBResponse_GuildWar_AddReserve()
	{
		memset( this, 0, sizeof( sDBResponse_GuildWar_AddReserve ) );
	}
};

class sDBRequest_GuildWar_ReserveList
{
public:
	sPacketHeader	packetHeader;

	SI32			siFieldIndex;

	sDBRequest_GuildWar_ReserveList()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildWar_ReserveList));
	}

	sDBRequest_GuildWar_ReserveList(SI32 field)
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildWar_ReserveList );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDWAR_RESERVELIST;

		siFieldIndex = field;
	}
};

class sDBResponse_GuildWar_ReserveList
{
public:
	sPacketHeader	packetHeader;

	SI32					siResult;

	SI32					siFieldIndex;
	cltGuildWarReserveUnit	clUnit[GUILDWAR_ROOMNUM];

	sDBResponse_GuildWar_ReserveList()
	{
		memset( this, 0, sizeof( sDBResponse_GuildWar_ReserveList ) );
	}
};
/*=====================================================================
 ��� ����� ��û�� ���ο������ �ƴ����� Ÿ������ �����Ѵ�.
//=====================================================================*/
enum
{
	MESSAGETYPE_OLD	=	0,
	MESSAGETYPE_NEW,
};
class sDBRequest_GuildDungeon_Apply
{
public:
	sPacketHeader	packetHeader;

	SI32			siGuildUnique;
	SI32			siMapIndex;

	SI32			siCharID;
	SI32			siType	;	// �� ��� ����� ��û�� ���ο������, ������ ������.

	sDBRequest_GuildDungeon_Apply()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildDungeon_Apply));
	}

	sDBRequest_GuildDungeon_Apply(SI32 guildUnique, SI32 mapIndex, SI32 charID, SI32 Type )
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildDungeon_Apply );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDDUNGEON_APPLY;

		siGuildUnique = guildUnique;
		siMapIndex = mapIndex;
		siCharID = charID;
		siType	=	Type	;
	}
};

class sDBResponse_GuildDungeon_Apply
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siGuildUnique;
	SI32			siMapIndex;

	cltGuildInfo	clGuildInfo;

	SI32			siCharID;
	SI32			siType	;


	sDBResponse_GuildDungeon_Apply()
	{
		memset( this, 0, sizeof( sDBResponse_GuildDungeon_Apply ) );
	}
};

class sDBRequest_GuildDungeon_SaveStatus
{
public:
	sPacketHeader	packetHeader;

	SI32			siMapIndex;
	SI32			siExp;
	GMONEY			siMoney;

	sDBRequest_GuildDungeon_SaveStatus()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildDungeon_SaveStatus));
	}

	sDBRequest_GuildDungeon_SaveStatus(SI32 mapindex, SI32 exp, GMONEY money )
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildDungeon_SaveStatus );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDDUNGEON_SAVESTATUS;

		siMapIndex = mapindex;
		siExp = exp;
		siMoney = money;
	}
};
class sDBResponse_GuildDungeon_SaveStatus
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;

	sDBResponse_GuildDungeon_SaveStatus()
	{
		memset( this, 0, sizeof( sDBResponse_GuildDungeon_SaveStatus ) );
	}
};


class sDBRequest_GuildDungeon_LoadStatus
{
public:
	sPacketHeader	packetHeader;

	SI32			siMapIndex;

	sDBRequest_GuildDungeon_LoadStatus()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildDungeon_LoadStatus));
	}

	sDBRequest_GuildDungeon_LoadStatus(SI32 mapindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildDungeon_LoadStatus );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDDUNGEON_LOADSTATUS;

		siMapIndex = mapindex;
	}
};

class sDBResponse_GuildDungeon_LoadStatus
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siMapIndex;
	SI32			siGuildUnique;
	SI32			siExp;
	GMONEY			siMoney;

	sDBResponse_GuildDungeon_LoadStatus()
	{
		ZeroMemory(this, sizeof(sDBResponse_GuildDungeon_LoadStatus) );
	}
};


// ��� ������ ����

class sDBRequest_GuildDungeon_TransferOwnership
{
public:
	sPacketHeader	packetHeader;

	float			fGPRatio;			
	float			fMoneyRatio;

	sDBRequest_GuildDungeon_TransferOwnership(float gpratio, float moneyratio )
	{
		packetHeader.usSize = sizeof( sDBRequest_GuildDungeon_TransferOwnership );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILDDUNGEON_TRANSFEROWNERSHIP;

		fGPRatio = gpratio;
		fMoneyRatio = moneyratio;
	}
};

class cltGuildDungeon_ChangedGPMoney
{
public:
	SI32 siGuildUnique;
	SI32 siAddExp;
	SI32 siExp;
	GMONEY siAddMoney;
	GMONEY siMoney;
};
class cltGuildDungeon_NewOwnership
{
public:
	SI32 siMapindex;
	SI32 siGuildUnique;
};

class sDBResponse_GuildDungeon_TransferOwnership
{
public:
	sPacketHeader	packetHeader;

	SI32							siResult;
	cltGuildDungeon_ChangedGPMoney	clChangedGuildInfo[MAX_GUILDDUNGEON];
	cltGuildDungeon_NewOwnership	clNewOwnerInfo[MAX_GUILDDUNGEON];

	sDBResponse_GuildDungeon_TransferOwnership()
	{
		ZeroMemory( this, sizeof(sDBResponse_GuildDungeon_TransferOwnership) );
	}
};
//----------------------------------------------------------------------------
// ��Ȱ�� ��� ��ü ( 1�޿� �ѹ� ��Ȱ�� ��� ����)
//----------------------------------------------------------------------------
// ��Ȱ�� ��带 ã�� �����޶�� ���� �޼����� ������.
#define OVER30DAYSNOTINTOGAME	30

class sDBRequest_Guild_CheckDestroy_Month
{
public:
	sPacketHeader		packetHeader;

	SYSTEMTIME			stLastConnectTime;		// �� �� ���ķ� ������ ���ٸ� ������.

	sDBRequest_Guild_CheckDestroy_Month()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_CheckDestroy_Month));
	}

	sDBRequest_Guild_CheckDestroy_Month( SYSTEMTIME* stTime )
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_CheckDestroy_Month );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_CHECKDESTROY_MONTH;

		memcpy(&stLastConnectTime, stTime, sizeof(stLastConnectTime));
	}
};

// ��Ȱ�� ��� ���� ������ �޴´�.
class sDBResponse_Guild_CheckDestroy_Month
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	cltGuildInfo		clInfo[MAX_GUILD_PER_DBLIST];	// ������ ��� ������ �޴´�.

	sDBResponse_Guild_CheckDestroy_Month()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_CheckDestroy_Month ) );
	}
};

//-----------------------------------------------
// �Ѵ޵��� ���Ӿ��� ��� ������ ����
//----------------------------------------------
class sDBRequest_Guild_NotConnect_ChangeMaster
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID ;

	SI32				siGuildUnique;
	SYSTEMTIME			stLastConnectTime;		// ������ ���� ������(��¥ ���ķ� ������ ���ٸ� ����)

	sDBRequest_Guild_NotConnect_ChangeMaster()
	{
		ZeroMemory(this, sizeof(sDBRequest_Guild_NotConnect_ChangeMaster));
	}

	sDBRequest_Guild_NotConnect_ChangeMaster(SI32 personid, SI32 charid, SI32 unique, SYSTEMTIME* pstTime)
	{
		packetHeader.usSize = sizeof( sDBRequest_Guild_NotConnect_ChangeMaster );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILD_NOTCONNECT_CHANGEMASTER;

		siPersonID = personid ;
		siCharID = charid ;

		siGuildUnique = unique ;
		memcpy(&stLastConnectTime, pstTime, sizeof(SYSTEMTIME));
	}
};

class sDBResponse_Guild_NotConnect_ChangeMaster
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.
	SI32				siPersonID;
	SI32				siCharID ;
	
	SI32				siNewPersonID;
	TCHAR				szNewPersonName[MAX_PERSON_NUMBER];

	cltGuildInfo		clInfo;

	sDBResponse_Guild_NotConnect_ChangeMaster()
	{
		memset( this, 0, sizeof( sDBResponse_Guild_NotConnect_ChangeMaster ) );
	}
};
enum
{
	AddList	=	0,
	DelList,
};
// ���� ����� ��û ����Ʈ�� ���� �Ѵ�.
class sDBRequest_GuildHuntMapWar_SaveRegList
{
public:
	sPacketHeader	packetHeader;
	SI32			siGuildUnique	;	//������ ��� ����ũ
	SI32			siType			;	// �߰����� ��������.

	sDBRequest_GuildHuntMapWar_SaveRegList()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildHuntMapWar_SaveRegList));
	}

	sDBRequest_GuildHuntMapWar_SaveRegList(SI32 GuildUnique,SI32 Type)
	{
		packetHeader.usSize =	sizeof( sDBRequest_GuildHuntMapWar_SaveRegList );
		packetHeader.usCmd	=	DBMSG_REQUEST_GUILDHUNTMAPWAR_REGLIST ;
		siGuildUnique		=	GuildUnique	;
		siType				=	Type		;
	}
};
class sDBResponse_GuildHuntMapWar_SaveRegList
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult		;
	SI32			siGuildUnique	;
	SI32			siType			;
	sDBResponse_GuildHuntMapWar_SaveRegList()
	{
		memset( this, 0, sizeof( sDBResponse_GuildHuntMapWar_SaveRegList ) );
	}
};
// ���� ����� ��û ����Ʈ�� ������ �´�. ���� ó���� ���� �ѹ� ȣ�� �Ѵ�.
class sDBRequest_GuildHuntMapWar_SaveRegListGet
{
public:
	sPacketHeader	packetHeader;
	sDBRequest_GuildHuntMapWar_SaveRegListGet()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildHuntMapWar_SaveRegListGet));
		packetHeader.usSize =	sizeof( sDBRequest_GuildHuntMapWar_SaveRegListGet );
		packetHeader.usCmd	=	DBMSG_REQUEST_GUILDHUNTMAPWAR_GET_REGLIST ;
	}
};
class sDBResponse_GuildHuntMapWar_SaveRegListGet
{
public:
	sPacketHeader	packetHeader;
	cltGuildHuntMapWarListData	m_GuildList[MAX_GUILD_NUM];

	sDBResponse_GuildHuntMapWar_SaveRegListGet()
	{
		memset( this, 0, sizeof( sDBResponse_GuildHuntMapWar_SaveRegListGet ) );
	}
};
// �ش� ���� ���BGP���� 10������ �޴´�.
class sDBRequest_GuildHuntMapWar_Rank_Get
{
public:
	sPacketHeader	packetHeader;
	SI32			siMapIndex	;
	SI32			siPersonID	;
	sDBRequest_GuildHuntMapWar_Rank_Get()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildHuntMapWar_Rank_Get));
	}

	sDBRequest_GuildHuntMapWar_Rank_Get(SI32 Mapindex,SI32 PersonID)
	{
		packetHeader.usSize =	sizeof( sDBRequest_GuildHuntMapWar_Rank_Get );
		packetHeader.usCmd	=	DBMSG_REQUEST_GUILDHUNTMAPWAR_RANK_GET ;
		siMapIndex			=	Mapindex;
		siPersonID			=	PersonID	;

		siMapIndex = Mapindex	;

	}
};
class sDBResponse_GuildHuntMapWar_Rank_Get
{
public:
	sPacketHeader	packetHeader;
	SI32			siPersonID;
	cltGuildHuntMapWarListRankData	m_GuildList[MAX_GUILDHUNTWAR_RANK_NUM];

	sDBResponse_GuildHuntMapWar_Rank_Get()
	{
		memset( this, 0, sizeof( sDBResponse_GuildHuntMapWar_Rank_Get ) );
	}
};
class sDBRequest_GuildHuntMapWar_Result
{
public:
	sPacketHeader	packetHeader;
	SI32			siGuildUnique	;	// ��� ����ũ
	SI32			siWinLoseFlag	;	// �¹��� ����
	SI32			siBGP	;			// ȹ�� BGP
	sDBRequest_GuildHuntMapWar_Result()
	{
		ZeroMemory(this, sizeof(sDBRequest_GuildHuntMapWar_Result));
	}

	sDBRequest_GuildHuntMapWar_Result(SI32 guildunique ,SI32  winloseflag,SI32 bgp )
	{
		packetHeader.usSize =	sizeof( sDBRequest_GuildHuntMapWar_Result );
		packetHeader.usCmd	=	DBMSG_REQUEST_GUILDHUNTMAPWAR_RESULT ;
		siGuildUnique = guildunique	;
		siWinLoseFlag = winloseflag;
		siBGP			= bgp	;

	}
};
class sDBResponse_GuildHuntMapWar_Result
{
public:
	sPacketHeader	packetHeader;
	SI32			siResult;
	SI32			siGuildunique	;
	SI32			siBGP	;
	sDBResponse_GuildHuntMapWar_Result()
	{
		memset( this, 0, sizeof( sDBResponse_GuildHuntMapWar_Result ) );
	}
};

#endif
