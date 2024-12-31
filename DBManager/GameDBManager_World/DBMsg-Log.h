#ifndef _DBMSGLOG_H
#define _DBMSGLOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

//----------------------------------------------
// Common
//----------------------------------------------
#include "../../GoonZuWorld/Common/CommonHeader.h"
#include "../../GoonZuWorld/Common/PersonInfo.h"

#include "../../GoonZuWorld/Common/Char/CharCommon/Char-Common.h"
#include "../../GoonZuWorld/Common/Char/ParametaBox/ParametaBox.h"
#include "../../GoonZuWorld/Common/Item/ItemCommon/ItemUnit.h"
#include "../../GoonZuWorld/Server/Rank/Rank.h"
#include "../../GoonZuWorld/Common/Skill/Skill.h"
#include "../../GoonZuWorld/Common/Quest/Quest.h"
#include "../../GoonZuWorld/Common/Horse/Horse.h"
#include "../../GoonZuWorld/Common/Char/CharCommon/Char-EconomyInfo.h"
#include "../../GoonZuWorld/Common/SystemReward/SystemReward.h"


#include "../../GoonZuWorld/CommonLogic/Bank/Bank.h"
#include "../../GoonZuWorld/CommonLogic/Guild/Guild.h"

//--------------------------------------------------------------------------------------
//Person�� BasicInfo ������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_BasicInfoByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siClientID;

	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siPAGENum;	

	sDBRequest_BasicInfoByName()
	{
		ZeroMemory(this, sizeof(sDBRequest_BasicInfoByName));
	}

	sDBRequest_BasicInfoByName(SI32 clientid, TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_BasicInfoByName );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_CHARBASICINFO;

		siClientID	= clientid;
		szCharname[0] = '\0';

		if(charname)		strcpy(szCharname, charname);
		siPAGENum = pagenum;

	}
};

class sDBResponse_BasicInfoByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siClientID;

	TCHAR				Charname[MAX_PLAYER_NAME];
	SI32				siPAGENum;
	//�ɸ��� �⺻ ����.
	cltPBasicInfo		BasicInfo;			// Person�� �⺻ ����. 
	cltPIPInfo			clIp;				//�ɸ����� ���� ����
	cltHealthInfo		clHealthInfo;		//�ǰ�����
	cltPStockInfo		clStockInfo;
	cltBankAccount		clBankaccount;
    
	sDBResponse_BasicInfoByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_BasicInfoByName));
	}
};


//--------------------------------------------------------------------------------------
//Person�� ��ų������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_SkillByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siClientID;

	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siPAGENum;	

	sDBRequest_SkillByName()
	{
		ZeroMemory(this, sizeof(sDBRequest_SkillByName));
	}

	sDBRequest_SkillByName(SI32 clientid, TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_SkillByName );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_SKILLINFO;
		siClientID	= clientid;
		szCharname[0] = '\0';
		if(charname)		strcpy(szCharname, charname);
		siPAGENum= pagenum;
	}
};

class sDBResponse_SkillByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;
	SI32				siClientID;
	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siPAGENum;

	cltPSkillInfo			SkillInfo;			// Person�� ��� ����.
	cltPItemInfo			clItemInfo;			// Person�� ������ ����.
	

	sDBResponse_SkillByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_SkillByName));
	}
};

//--------------------------------------------------------------------------------------
//Person�� ���� ������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_AnimalByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siClientID;
	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siPAGENum;	

	sDBRequest_AnimalByName()
	{
		ZeroMemory(this, sizeof(sDBRequest_AnimalByName));
	}

	sDBRequest_AnimalByName(SI32 clientid, TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_AnimalByName );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_ANIMALLINFO;
		siClientID	= clientid;
		szCharname[0] = '\0';
		if(charname)		strcpy(szCharname, charname);
		siPAGENum= pagenum;

	}
};

class sDBResponse_AnimalByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;
	SI32				siClientID;
	TCHAR				Charname[MAX_PLAYER_NAME];
	SI32				siPAGENum;

	cltPersonHorseInfo		clHorseInfo;		// �� ����.

	sDBResponse_AnimalByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_AnimalByName));
	}
};

//--------------------------------------------------------------------------------------
//Person�� �κ��丮 ������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_InventoryByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siClientID;
	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siPAGENum;	

	sDBRequest_InventoryByName()
	{
		ZeroMemory(this, sizeof(sDBRequest_InventoryByName));
	}

	sDBRequest_InventoryByName(SI32 clientid,TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_InventoryByName );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_INVENTORYINFO;
		siClientID	= clientid;
		szCharname[0] = '\0';
		if(charname)		strcpy(szCharname, charname);

		siPAGENum= pagenum;

	}
};

class sDBResponse_InventoryByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;
	SI32				siClientID;
	TCHAR				Charname[MAX_PLAYER_NAME];
	SI32				siPAGENum;

	cltPItemInfo			clItemInfo;			// Person�� ������ ����.

	sDBResponse_InventoryByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_InventoryByName));
	}
};

//--------------------------------------------------------------------------------------
//Person�� �ε��� ������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_RealestateByNAme
{
public:
	sPacketHeader		packetHeader;
	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siClientID;
	SI32				siPAGENum;	

	sDBRequest_RealestateByNAme()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealestateByNAme));
	}

	sDBRequest_RealestateByNAme(SI32 clientid,TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_RealestateByNAme );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_REALESTATEINFO;
		siClientID	= clientid;
		szCharname[0] = '\0';
		if(charname)		strcpy(szCharname, charname);
		siPAGENum= pagenum;

	}
};

class sDBResponse_RealestateByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;
	TCHAR				Charname[MAX_PLAYER_NAME];
	SI32				siClientID;
	SI32				siPAGENum;

	cltCharRealEstate		clRealEstateInfo;	// �ε��� ����(����...) 

	sDBResponse_RealestateByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealestateByName));
	}
};

//--------------------------------------------------------------------------------------
//Person�� ��ȯ�� ������ ��û�ϴ� �κ�
//--------------------------------------------------------------------------------------
class sDBRequest_SummonByName
{
public:
	sPacketHeader		packetHeader;
	TCHAR				szCharname[MAX_PLAYER_NAME];
	SI32				siClientID;
	SI32				siPAGENum;	

	sDBRequest_SummonByName()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonByName));
	}

	sDBRequest_SummonByName(SI32 clientid,TCHAR* charname, SI32 pagenum)
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonByName );
		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_SUMMONINFO;
		siClientID	= clientid;
		szCharname[0] = '\0';
		if(charname)		strcpy(szCharname, charname);
		siPAGENum= pagenum;

	}
};

class sDBResponse_SummonByName
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;
	TCHAR				Charname[MAX_PLAYER_NAME];
	SI32				siClientID;
	SI32				siPAGENum;

	cltSummonInfo			clSummonInfo;		// ��ȯ�� ���� 

	sDBResponse_SummonByName()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonByName));
	}
};

////--------------------------------------------------------------------------------------
////Person�� �ŷ� ������ ��û�ϴ� �κ�
////--------------------------------------------------------------------------------------
//class sDBRequest_TradingByIDNum
//{
//public:
//	sPacketHeader		packetHeader;
//	UI16				usCharID;
//	SI32				siIDNum;	
//
//	sDBRequest_TradingByIDNum()
//	{
//		ZeroMemory(this, sizeof(sDBRequest_TradingByIDNum));
//	}
//
//	sDBRequest_TradingByIDNum(SI32 id, SI32 idnum)
//	{
//		packetHeader.usSize = sizeof( sDBRequest_TradingByIDNum );
//		packetHeader.usCmd = DBMSG_REQUEST_GMTOOL_TRADINGINFO;
//		usCharID			= id;
//		siIDNum	= idnum;
//
//	}
//};
//
//class sDBResponse_TradingByIDNum
//{
//public:
//	sPacketHeader		packetHeader;
//	UI16				usCharID;
//	SI32				siPersonID;
//	//�ɸ��� �⺻ ����.
//	cltPBasicInfo		BasicInfo;			// Person�� �⺻ ����. 
//	cltInvestInfo		InvestInfo;			// Person�� �ֽ� ����.
//
//	sDBResponse_TradingByIDNum()
//	{
//		ZeroMemory(this, sizeof(sDBResponse_TradingByIDNum));
//	}
//};
#endif