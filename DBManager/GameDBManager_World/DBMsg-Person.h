#ifndef _DBMSGPERSON_H
#define _DBMSGPERSON_H

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
#include "../../GoonZuWorld/common/Family/Family.h"
#include "../../GoonZuWorld/CommonLogic/DormancyAccountSystem/DormancyInfo.h"

#include "DBMsg-System.h"

//------------------------
// Person�� ��ü ���� 
//------------------------
// Person�� ��ü ����. 
class sDBPersonTotalInfo
{
public:

	cltPBasicInfo			BasicInfo;			// Person�� �⺻ ����. 
	cltPIPInfo				IPInfo;				// Person�� ImportantParameta ����. 
	cltPSkillInfo			SkillInfo;			// Person�� ��� ����. 
	cltPItemInfo			ItemInfo;			// Person�� ������ ����. 

	SI32					siGameMasterLevel;	// ��� ���� ���. (0 : �Ϲ� ����, ) 
	cltSimpleRank			RankInfo;			// Person�� �ź� ����. 
	cltBankAccount			clBankInfo;			// Person�� ��������. 
	cltPStockInfo			clStockInfo;
	//_LEON_GUILD_STOCK
//	cltPGuildStockInfo		clGuildStockInfo;	// Persond�� ��� �ֽ� ����
	cltWorldMoneyAccount	clWorldMoney;		// Person�� ������ȭ(��ť?) ����

	cltPMarketInfo			clMarketInfo;
	cltCharRealEstate		clRealEstateInfo;	// �ε��� ����(����...) 
	cltHealthInfo			clHealthInfo;		// �ǰ� ����. 
	cltPQuestInfo			clQuestInfo;		// ����Ʈ ����.
	cltPersonHorseInfo		clHorseInfo;		// �� ����. 
	cltGuiltyInfo			clGuiltyInfo;		// ���� ���. 
	cltPDailyQuestInfo		clDailyQuestInfo;	// Daily ����Ʈ ����
	cltPDailyQuest2Info		clDailyQuest2Info;	// Daily ����Ʈ ����
	cltPDailyQuest3Info		clDailyQuest3Info;	// Daily ����Ʈ ����
	cltSummonInfo			clSummonInfo;		// ��ȯ�� ���� 
	//cltPLimitDateItemInfo	clLimitDateItemInfo;// �Ⱓ�� ������ ����
	UI16					uiGachaCnt;			// ���� ���� Ƚ��
	cltPersonNaming			clPersonNaming;	
	
	//KHY - 1220 - ���Žý���.
	cltTransFormInfo		clTransFormInfo;

	// [����] ���ǰ��� ����
	cltWorldPassportForDB	clWorldPassportForDB;

	cltElixir_Info			 m_clElixirInfo;			// ������ ����.

	// [����] �޸� ���� ����
	CDormancyInfo			m_clDormancyInfo;

	sDBPersonTotalInfo()
	{
		ZeroMemory(this, sizeof(sDBPersonTotalInfo));
	}
};


//----------------------------------------------------
// Person�� ��ü ������ ���� ���� ��û�ϴ� Ŭ����. (IDNUm�� �ٰŷ�. ) 
//----------------------------------------------------
class sDBRequest_PersonTotalInfoGetByIDNum
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siIDNum;	
	SI32				siIndex;

	TCHAR				szIPAddress[20];		// �������� ip�ּ�. 

	bool				bTiredSystem;
	DWORD				dwPlayingTime;

	bool				bDormancyState;			// �޸� ���� ����.

	sDBRequest_PersonTotalInfoGetByIDNum()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoGetByIDNum));
	}

	sDBRequest_PersonTotalInfoGetByIDNum(SI32 id, SI32 idnum, SI32 index, TCHAR* pip, bool DormancyState, bool TiredSystem = false, DWORD PlayingTime = 0 )
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoGetByIDNum );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFOGETBYIDNUM;
		usCharID			= id;

		siIDNum	= idnum;
		siIndex	= index;

		StringCchCopy(szIPAddress, 20, pip);

		bDormancyState = DormancyState;

		bTiredSystem = TiredSystem;
		dwPlayingTime = PlayingTime;
	}
};

//----------------------------------------------------
// Person�� ������ ������ ���� ���� ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_PersonItemInfoGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	

	sDBRequest_PersonItemInfoGet()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonItemInfoGet));
	}

	sDBRequest_PersonItemInfoGet(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonItemInfoGet );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONITEMINFOGET;
		usCharID			= id;

		siPersonID	= personid;
	}
};

class sDBResponse_PersonItemInfoGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	

	cltPItemInfo		ItemInfo;			// Person�� ������ ����. 

	
	sDBResponse_PersonItemInfoGet()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonItemInfoGet));
	}
};


//----------------------------------------------------
// Person�� ��ü ������ ���� ���� ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_PersonTotalInfoGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;

	sDBRequest_PersonTotalInfoGet()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoGet));
	}

	sDBRequest_PersonTotalInfoGet(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoGet );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFOGET;
		usCharID			= id;

		siPersonID	= personid;
	}
};

class sDBResponse_PersonTotalInfoGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����. (1: ����. 0:����) 
	sDBPersonTotalInfo	clInfo;
	SI32				siHomeVillageUnique;
	bool				bExistentItem;		// ���� ���� ���ؼ� �ý��ۿ��� ȸ���� �������� �ִ°�?
	bool				bTiredSystem;
	DWORD				dwPlayingTime;

	sDBResponse_PersonTotalInfoGet()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonTotalInfoGet));
		
		clInfo.clSummonInfo.Init();
	}
};


//----------------------------------------------------
// Person�� ��ü ������ ������  ���� ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_PersonTotalInfoSet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBPersonTotalInfo	clInfo;

	sDBRequest_PersonTotalInfoSet()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoSet));
	}

	sDBRequest_PersonTotalInfoSet(SI32 id, sDBPersonTotalInfo* pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoSet );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFOSET;
		usCharID			= id;

		clInfo	= *pclinfo;
	}
};

class sDBResponse_PersonTotalInfoSet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����. (1: ����. 0:����) 

	sDBResponse_PersonTotalInfoSet()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonTotalInfoSet));
	}
};


//----------------------------------------------------
// Person�� ��ü ������ ������ ���� ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_PersonTotalInfoDelete
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siIDNum;
	SI32				siIndex;
	SI32				siPersonID;		// ����� personid
	TCHAR				szIdenNum[ 12 ];		// �ֹε�� ��ȣ ���ڸ� 	
	TCHAR				szIP[ 20 ];

	sDBRequest_PersonTotalInfoDelete()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoDelete));
	}

	sDBRequest_PersonTotalInfoDelete(SI32 id, SI32 idnum, SI32 index, SI32 personid, TCHAR* idennum, TCHAR *ip )
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoDelete );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFODELETE;
		usCharID			= id;

		siIDNum	= idnum;

		siIndex	= index;
		siPersonID	= personid;

		StringCchCopy( szIdenNum, 12, idennum );

		memcpy( szIP, ip, 20 );
		szIP[ 19 ] = NULL;
	}
};

class sDBResponse_PersonTotalInfoDelete
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����. 
											//  1: ����. 
											//  0: �Ϲ����� ���� 
											// -1: �ֹε�Ϲ�ȣ���ڸ� ������ 

	cltGuildInfo		clinfo;	// ��尡 �ִ� ĳ���̸� ��� ������ ������Ʈ�Ѵ�.
	cltTradeOrder		clOrder[MAX_MARKET_ORDER_PER_PERSON];			// DB�� ����� �ֹ��� ����. 

	//[�߰� : Ȳ���� 2007. 11. 5 �����ϴ� ĳ������ person id]
	SI32				siPersonID;		// ����� personid


	sDBResponse_PersonTotalInfoDelete()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonTotalInfoDelete));
	}
};

//----------------------------------------------------
// Person�� ��ü ������ ������⸦ ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_PersonTotalInfoPreDelete
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siIDNum;
	SI32				siIndex;
	SI32				siPersonID;		// ����� personid
	TCHAR				szIdenNum[ 12 ];		// �ֹε�� ��ȣ ���ڸ� 	
	TCHAR				szIP[ 20 ];
	SYSTEMTIME			systemTime;
	SI16 predeltype;//1�̸� ���� 0�̸� ���������Ⱓ ����


	sDBRequest_PersonTotalInfoPreDelete()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoDelete));
	}

	sDBRequest_PersonTotalInfoPreDelete(SI32 id, SI32 idnum, SI32 index, SI32 personid, TCHAR* idennum, SYSTEMTIME stTime, TCHAR *ip , SI16 deltype)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoPreDelete );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFOPREDELETE;
		usCharID			= id;

		siIDNum	= idnum;

		siIndex	= index;

		systemTime = stTime;
		siPersonID	= personid;

		StringCchCopy( szIdenNum, 12, idennum );

		memcpy( szIP, ip, 20 );
		szIP[ 19 ] = NULL;
		predeltype = deltype;
	}
};

class sDBResponse_PersonTotalInfoPreDelete
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����. 
	//  1: ����. 
	//  0: �Ϲ����� ���� 
	// -1: �ֹε�Ϲ�ȣ���ڸ� ������ 
	//[�߰� : Ȳ���� 2007. 11. 5 �����ϴ� ĳ������ person id]
	SI32				siPersonID;		// ����� personid

	sDBResponse_PersonTotalInfoPreDelete()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonTotalInfoPreDelete));
	}
};


//-----------------------------------------------------------------
// Person�� ���ʽ� �й� ���� ������ ����ϵ��� ��û�Ѵ�.
//-----------------------------------------------------------------
class sDBRequest_SetBonusInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;			// ����� �Ǵ� PersonID

	cltBasicAbility		clBA;				// �⺻ ����. 
	SI16				siBonus;

	sDBRequest_SetBonusInfo(SI32 id, SI32 personid, cltBasicAbility* pclba, SI16 bonus)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetBonusInfo);
		packetHeader.usCmd = DBMSG_REQUEST_SETBONUSINFO;

		siPersonID		= personid;

		clBA.Set(pclba);
		siBonus			= bonus;
	}
};


class sDBResponse_SetBonusInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	// PCK : �α׿� ��Ŷ �߰�
	cltBasicAbility		cIBA;
	SI32				siPersonID;
	SI16				siBonus;

	sDBResponse_SetBonusInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetBonusInfo));
	}
};

/*-------------------------------------------------------------------
�з�: Person Info
����: Person ������ ���´� [��û]
�ð�: 2003-07-29
-------------------------------------------------------------------*/
class sDBRequest_PersonListInfoGet
{
public:

	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				idnum;

	sDBRequest_PersonListInfoGet(UI16 charid, SI32 siidnum)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonListInfoGet );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONLISTINFOGET;
		usCharID	= charid;
		idnum		= siidnum;
	}

};

class sDBResponse_PersonListInfoGet
{
public:	
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	cltPBasicInfo	personInfo[ MAX_TOTAL_CHAR_PER_USER ];
	//cltItem			personIteminfo[ MAX_CHAR_PER_USER ][ MAX_SHAPE_ITEM ];	
	SI32			siLevel[ MAX_TOTAL_CHAR_PER_USER ];
	SYSTEMTIME		stTime[ MAX_TOTAL_CHAR_PER_USER ];

	sDBResponse_PersonListInfoGet()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonListInfoGet));
	}
};


//-----------------------------------------------------------------
// Person�� Level���� ������ ����ϵ��� ��û�Ѵ�.
//-----------------------------------------------------------------
class sDBRequest_SetLevelInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� PersonID

	SI64				siExp;	// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	SI16				siLevel;
	SI32				siFameExp;
	SI16				siFameLevel;
	SI16				siBonus;
	SI16				siSkillBonus;
	SI32				siPlayTime;

	sDBRequest_SetLevelInfo(SI32 id, SI32 personid, SI64 exp, SI16 level, SI32 fameexp, SI16 famelevel, SI16 bonus, SI16 skillbonus, SI32 PlayTime )// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	{
		packetHeader.usSize = sizeof( sDBRequest_SetLevelInfo);
		packetHeader.usCmd = DBMSG_REQUEST_SETLEVELINFO;

		usCharID		= id;
		siPersonID		= personid;
		siExp			= exp;// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
		siLevel			= level;
		siFameExp		= fameexp;
		siFameLevel		= famelevel;
		siBonus			= bonus;
		siSkillBonus	= skillbonus;
		siPlayTime		= PlayTime;
	}
};


class sDBResponse_SetLevelInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	sDBResponse_SetLevelInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetLevelInfo));
	}
};



//---------------------------------------
// ���� ������� �ű��. 
//--------------------------------------
class sDBRequest_MoveMoney
{
public:
	sPacketHeader		packetHeader;
	SI32				siFromPersonID;						
	SI32				siToPersonID;
	UI16				usCharID;
	SI16				siReason;						// ���� �ű� ����. 
	GMONEY				siMovedMoney;					// �Ű��� �ݾ�

	sDBRequest_MoveMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_MoveMoney));
	}

	sDBRequest_MoveMoney(UI16 charid, SI32 personfromid, SI32 persontoid, SI16 reason, GMONEY movedmoney)
	{
		packetHeader.usSize = sizeof( sDBRequest_MoveMoney );
		packetHeader.usCmd	= DBMSG_REQUEST_MOVEMONEY;

		siFromPersonID	= personfromid;
		siToPersonID	= persontoid;
		usCharID		= charid;
		siReason		= reason;
		siMovedMoney	= movedmoney;
	}
};

class sDBResponse_MoveMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siFromPersonID;						
	GMONEY				siFromPersonMoney;

	SI32				siToPersonID;						
	GMONEY				siToPersonMoney;

	UI16				usCharID;
	SI16				siReason;						// ������ ������ ����. 
	GMONEY				siMovedMoney;					// �Ű��� �ݾ�. 
	
	sDBResponse_MoveMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_MoveMoney));
	}
};

//------------------------------------------
// ��ų�� ���ҽ�Ų��.
//------------------------------------------
#define DECSKILLMODE_LEVEL			1	// �������� ���� ��� ����. 
#define DECSKILLMODE_TICKET			2	// �̿�ǿ� ���� ��� ����
#define DECSKILLMODE_WEAPONSKILL	3	// �̿�ǿ� ���� �������� ��� ����
// ��� ��ü �ʱ�ȭ �̿�� - 2009.11.24 �ռ���
#define DECSKILLMODE_ALLSKILLPOINT	4	// ��� ��ü �ʱ�ȭ 

class sDBRequest_DecreaseSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Who
	SI32				siPersonID;					//  PersonID
	SI32				siSkillIndex;				// �� ��° ��ų�� ������ ���ΰ� ?

	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	UI08				uiDecSkillLevel;			// ���ҽ��Ѿ� �� ��ų ���� 
	UI08				uiIncreaseSkillPoint;		// �ٽ� ��������� ��ų���ʽ� ����Ʈ

	UI08				uiChildSkillList[MAX_CHILD_SKILL_NUM];
	
	SI16				siMode;
	SI16				siItemPos;
	cltItem				clItem;

	
	sDBRequest_DecreaseSkill(SI32 id, SI32 personid, SI32 skillindex, UI08 skillunique, UI08 decskilllevel, UI08 IncreaseSkillPoint, UI08* pcllist, SI16 mode, SI16 pos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_DecreaseSkill );
		packetHeader.usCmd = DBMSG_REQUEST_DECREASESKILL;
		usCharID		= id;

		siPersonID		= personid;
		siSkillIndex	= skillindex;

		uiSkillUnique	= skillunique;
		uiDecSkillLevel	= decskilllevel;
		uiIncreaseSkillPoint = IncreaseSkillPoint;

		for(SI32 i = 0;i < MAX_CHILD_SKILL_NUM;i++)
		{
			uiChildSkillList[i] = pcllist[i];
		}

		siMode		= mode;
		siItemPos	= pos;
		if(pclitem)
		{
			clItem.Set(pclitem);
		}
		else
		{
			clItem.Init();
		}
	}
};

//------------------------------------------
// ��ų�� ���׷��̵� ��Ų��.
//------------------------------------------
class sDBRequest_IncreaseSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Who
	SI32				siPersonID;					// ���� �Ա��� PersonID

	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	UI08				uiIncSkillLevel;			// �������Ѿ� �� ��ų ���� 
	
	UI08				uiMaxSkillLevel;			// ��밡���� �ִ��� ��ų����. 
	UI08				uiDecreaseSkillPoint;		// ���ҵǴ� ��ų ����Ʈ

	//[�߰� : Ȳ���� 2007. 10. 25 	�α׿� �̿�. ����� ������.]
	cltItem				clUseItem;

	sDBRequest_IncreaseSkill(SI32 id, SI32 personid, UI08 skillunique, UI08 incskilllevel, UI08 maxskilllevel, UI08 decreaseskillpoint, cltItem	&UseItem)
	{
		packetHeader.usSize = sizeof( sDBRequest_IncreaseSkill );
		packetHeader.usCmd = DBMSG_REQUEST_INCREASESKILL;
		usCharID		= id;

		siPersonID		= personid;

		uiSkillUnique	= skillunique;
		uiIncSkillLevel	= incskilllevel;
		
		uiMaxSkillLevel	= maxskilllevel;
		uiDecreaseSkillPoint = decreaseskillpoint;
		
		clUseItem.Set(&UseItem);
	}
};
// ��ų �������� �������� �Ǵ� : PCK
#define INCREASESKILL			1	// ��ų����
#define DECREASESKILL			2	// ��ų����

class sDBResponse_IncreaseSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result
	SI32				siResult;			// �����.
	
	// who
	SI32				siPersonID;

	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	UI08				uiSkillLevel;				// ������ ��ų ���� 

	SI32				siSkillBonus;				// ����� ����� ��ų���ʽ� ����Ʈ.

	SI16				siMode;
	SI16				siItemPos;
	cltItem				clItem;

	//[�߰� : Ȳ���� 2007. 10. 25 	�α׿� �̿�. ����� ������.]
	cltItem				clUseItem;

	// PCK : �α׿� ��Ŷ �߰� (��ų���ΰ� �ٿ��ΰ�)
	SI08				siReason;

	sDBResponse_IncreaseSkill()
	{
		ZeroMemory(this, sizeof(sDBResponse_IncreaseSkill));
	}

};

//------------------------------------------
// ��ų�� ���׷��̵� ��Ų��.
//------------------------------------------
class sDBRequest_IncreaseMasterSkill
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;

	// Who
	SI32				siPersonID;					// PersonID

	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	UI08				uiIncSkillLevel;			// �������Ѿ� �� ��ų ���� 
	
	UI08				uiMaxSkillLevel;			// ��밡���� �ִ��� ��ų����. 

	sDBRequest_IncreaseMasterSkill(SI32 id, SI32 personid, UI08 skillunique, UI08 incskilllevel, UI08 maxskilllevel)
	{
		packetHeader.usSize = sizeof( sDBRequest_IncreaseMasterSkill );
		packetHeader.usCmd = DBMSG_REQUEST_INCREASEMASTERSKILL;
		usCharID		= id;

		siPersonID		= personid;

		uiSkillUnique	= skillunique;
		uiIncSkillLevel	= incskilllevel;
		
		uiMaxSkillLevel	= maxskilllevel;

	}
};

class sDBResponse_IncreaseMasterSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result
	SI32				siResult;			// �����.
	
	// who
	SI32				siPersonID;

	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	UI08				uiSkillLevel;				// ������ ��ų ���� 

	sDBResponse_IncreaseMasterSkill()
	{
		ZeroMemory(this, sizeof(sDBResponse_IncreaseMasterSkill));
	}

};

//------------------------------------------
// ������ ��ų�� �����Ѵ�.
//------------------------------------------
class sDBRequest_SetSkillExp
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	// Who
	SI32				siPersonID;					// ���� �Ա��� PersonID
	// what
	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	SI32				siSkillExp;					// ������ ��� ����ġ 

	sDBRequest_SetSkillExp(SI32 id, SI32 personid, UI08 skillunique, SI32 skillexp)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetSkillExp );
		packetHeader.usCmd	= DBMSG_REQUEST_SETSKILLEXP;
		usCharID			= id;

		siPersonID		= personid;

		uiSkillUnique	= skillunique;
		siSkillExp		= skillexp;
	}
};

class sDBResponse_SetSkillExp
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result
	SI32				siResult;			// �����.

	// PCK : �α׿� ��Ŷ �߰�

	SI32				siPersonID;					// ���� �Ա��� PersonID

	UI08				uiSkillUnique;				// ������ ��ų ����ũ. 
	SI32				siSkillExp;					// ������ ��� ����ġ

	sDBResponse_SetSkillExp()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetSkillExp));
	}
};

//--------------------------
// �������� ��ų�� �ø���.
//---------------------------
class sDBRequest_Set_WeaponSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;

	UI08				uiSkillUnique;
	UI08				uiSkillLevel;
	UI08				uiNeedSkillPoint;

	GMONEY				siMoney;

	cltItem				clNeedItem;
	SI16				siNeedItemPos;

	sDBRequest_Set_WeaponSkill(SI32 siCharID, SI32 personID, UI08 siSkillUnique, UI08 siSkillLevel, UI08 uiSkillPoint, GMONEY gmCost, cltItem* pclNeedItem, SI16 siItemPos )
	{
		packetHeader.usSize	= sizeof( sDBRequest_Set_WeaponSkill );
		packetHeader.usCmd	= DBMSG_REQUEST_SET_WEAPONSKILL;
		usCharID			= siCharID;

		siPersonID			= personID;

		uiSkillUnique		= siSkillUnique;
		uiSkillLevel		= siSkillLevel;
		uiNeedSkillPoint	= uiSkillPoint;

		siMoney				= gmCost;

		if ( pclNeedItem )	
		{
			clNeedItem.Set( pclNeedItem );
		}
		siNeedItemPos		= siItemPos;
	}
};

class sDBResponse_Set_WeaponSkill
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;

	SI32				siResult;			// �����.

	UI08				uiSkillUnique;		// ��� ��ų ����ũ
	UI08				uiSkillLevel;		// �������� ����

	SI16				siLeftBonus;		// ���� ��ų ���ʽ�
	UI08				siNeedSkillBonus;	// �α׿�(��ﶧ �Ҹ�� ��ų ����Ʈ)

	GMONEY				siLeftMoney;		// �Ϲ� ��ų���� ���� ��
	GMONEY				siMoney;			// �α׿�(�Ϲ� ��ų���� �Ҹ�� ��)

	cltItem				clLeftItem;			// ���� ��ų���� ���� ������
	SI16				siItemPos;			// ������ ������
	cltItem				clNeedItem;			// �α׿�(���� ��ų���� �Ҹ�� ������)

	sDBResponse_Set_WeaponSkill()
	{
		ZeroMemory(this, sizeof(sDBResponse_Set_WeaponSkill));
	}
};

//-----------------------------------------
// Ÿ�� �ִ� ���� �ε����� �����Ѵ�. 
//KHY - 1001 - ��µ��� 5���� ���� ����.
//-----------------------------------------
class sDBRequest_SetRideHorse
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siIndex;		// �� ��° ���� Ÿ�� �ִ°� ?(-1 �ΰ�� ������ ��������) 
	bool	siCurrentHorseRIDEHORSE;

	sDBRequest_SetRideHorse()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetRideHorse));
	}

	sDBRequest_SetRideHorse(UI16 charid, SI32 personid, SI16 index , bool CurrentHorseRIDEHORSE )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetRideHorse );
		packetHeader.usCmd	= DBMSG_REQUEST_SETRIDEHORSE;

		usCharID	= charid;
		siPersonID	= personid;
		siIndex		= index;
		siCurrentHorseRIDEHORSE = CurrentHorseRIDEHORSE;
	}
};

class sDBResponse_SetRideHorse
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siIndex;		// �� ��° ���� Ÿ�� �ִ°� ?(-1 �ΰ�� ������ ��������) 
	bool	siCurrentHorseRIDEHORSE;


	sDBResponse_SetRideHorse()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetRideHorse));
	}
};


//-----------------------------------------
// ���� �ڵ� �Ա� ����� �����Ѵ�. 
//-----------------------------------------
class sDBRequest_SetAutoFood
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	bool				bAutoFoodSwitch;

	sDBRequest_SetAutoFood()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetAutoFood));
	}

	sDBRequest_SetAutoFood(UI16 charid, SI32 personid, bool bauto)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetAutoFood );
		packetHeader.usCmd	= DBMSG_REQUEST_SETAUTOFOOD;

		usCharID		= charid;
		siPersonID		= personid;
		bAutoFoodSwitch	= bauto;
	}
};

class sDBResponse_SetAutoFood
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	UI16				usCharID;

	SI32				siPersonID;
	bool				bAutoFoodSwitch;

	sDBResponse_SetAutoFood()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetAutoFood));
	}
};



// ���� �ü��� �����Ѵ�.  - Insert �Ǵ� Update
class sDBRequest_SetCurrentHorsePrice
{
public:
	sPacketHeader		packetHeader;

	SI16				siHorseUnique;				// ���� ����( ǰ�� )
	GMONEY				siHorseCurrentPrice;		// ���� ���� �ü�

	sDBRequest_SetCurrentHorsePrice( SI16 HorseUnique, GMONEY HorseCurrentPrice )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetCurrentHorsePrice );
		packetHeader.usCmd	= DBMSG_REQUEST_SETCURRENTHORSEPRICE;
	
		siHorseUnique = HorseUnique;
		siHorseCurrentPrice = HorseCurrentPrice;
	}
};

class sDBResponse_SetCurrentHorsePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// 1 : ����, Other : ����

	SI16				siHorseUnique;				// ���� ����( ǰ�� )
	GMONEY				siHorseCurrentPrice;		// ���� ���� �ü�

	sDBResponse_SetCurrentHorsePrice()
	{
		memset(this, 0, sizeof(sDBResponse_SetCurrentHorsePrice));
	}
};

// ���� �ü��� ���´�.
class sDBRequest_GetCurrentHorsePrice
{
public:
	sPacketHeader		packetHeader;

	SI16				siHorseUnique;				// ���� ����( ǰ�� )	

	sDBRequest_GetCurrentHorsePrice( SI16 HorseUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetCurrentHorsePrice );
		packetHeader.usCmd	= DBMSG_REQUEST_GETCURRENTHORSEPRICE;
	
		siHorseUnique = HorseUnique;
	}
};

class sDBResponse_GetCurrentHorsePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// 1 : ����, Other : ����

	SI16				siHorseUnique;				// ���� ����( ǰ�� )
	GMONEY				siHorseCurrentPrice;		// ���� ���� �ü�

	sDBResponse_GetCurrentHorsePrice()
	{
		memset(this, 0, sizeof(sDBResponse_GetCurrentHorsePrice));
	}
};


//-----------------------------------------
// �� �Ѹ����� ������ �����Ѵ�. 
//-----------------------------------------
#define SETHORSE_REASON_MAKE		1	// �� �űԷ� ����. 
#define SETHORSE_REASON_UPDATE		2	// �� ���� ������Ʈ. 
#define SETHORSE_REASON_FREE		3	// �� Ǯ���ֱ�.
#define SETHORSE_REASON_DIE			4	// �� ���̱� 
#define SETHORSE_REASON_CHANGETYPE	5	// �� ǰ�� ����
#define SETHORSE_REASON_GAMEMASTER	6	// ��� ��ɿ� ����. 
#define SETHORSE_REASON_TICKET		7	// �� �ɷ� ����̿�ǿ� ���ؼ� ��ȭ
#define SETHORSE_REASON_PREMIUM_PARTS		8	// �� �ɷ»�� �����̾� ���� ��뿡 ���� ��ȭ

class sDBRequest_SetHorse
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siReason;		// ���� �����ϴ� ����. 
	SI16				siIndex;		// ��� ���� ������ ������Ʈ �ϴ°�.	

	cltHorse			clHorse;		// ���� ����. 	

	sDBRequest_SetHorse()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetHorse));
	}

	sDBRequest_SetHorse(UI16 charid, SI32 personid, SI16 reason, SI16 index, cltHorse* pclhorse)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetHorse );
		packetHeader.usCmd	= DBMSG_REQUEST_SETHORSE;

		usCharID	= charid;
		siPersonID	= personid;
		siReason	= reason;
		siIndex		= index;

		if(pclhorse)	clHorse.Set(pclhorse);
	}
};

class sDBResponse_SetHorse
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;		// �����.

	UI16				usCharID;
	SI32				siPersonID;
	SI16				siReason;		// ���� �����ϴ� ����.
	SI16				siIndex;		// ��� ���� ������ ������Ʈ �ϴ°�.

	// PCK : �α׿� ��Ŷ�߰�
	cltHorse			cIHorse;

	sDBResponse_SetHorse()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetHorse));
	}
};

//-----------------------------------------
// ���ݾ��� ������Ų��.
//-----------------------------------------
// [����] define���� enum���� ����
enum CHANGE_MONEY_REASON
{
	CHANGE_MONEY_REASON_NOTDEFINED			= 1		// ���ǵ��� ���� ����.
	,CHANGE_MONEY_REASON_QUESTREWARD		// ����Ʈ ���� ���� ����. 
	,CHANGE_MONEY_REASON_DEATH				// ����� ���� ����. 
	,CHANGE_MONEY_REASON_TRADE				// ��ǰ ��ȯ�� ���� ����. 
	,CHANGE_MONEY_REASON_WARWIN				// ���￡�� �¸��Ͽ� ���� ����. 
	,CHANGE_MONEY_REASON_GAMEMASTER			// ��ڿ� ���ؼ� ���� ���޹���. 
	,CHANGE_MONEY_REASON_REPAIRPAY			// ������� ����. 
	,CHANGE_MONEY_REASON_REPAIRGET			// ������� ����.
	//---------------------------------------------------------------------------
	// �߰��� ���� ���ڴ� �������� �׷����ϴ�. �ֱ׷��� ������ ���� �׳� ������
	//---------------------------------------------------------------------------
	,CHANGE_MONEY_REASON_HUNTFEE			= 11		// ������ ����� ����. 
	,CHANGE_MONEY_REASON_HUNTREWARD						// ������ ����� ����. 
	,CHANGE_MONEY_REASON_FATHERREWARD					// ���� �����. 
	,CHANGE_MONEY_REASON_RECOMMENDER					// ��õ�� ����. 
	,CHANGE_MONEY_REASON_USEMARKET						// ���� �̿뿡 ���� ���� ����. 
	,CHANGE_MONEY_REASON_NPCREPAIRPAY					// NPC(�念��) ���� ������� ����. 
	,CHANGE_MONEY_REASON_INVESTMENTINFO					// ���ڻ����(�輱��) ��ȸ��� ����
	,CHANGE_MONEY_REASON_MAKE							// �����Ƿڷ� ������ ����. 
	,CHANGE_MONEY_REASON_FIZATION						// ����ȸ�� ���� ������ ����.
	,CHANGE_MONEY_REASON_BLACKARMYAPPLY					// ���Ǳ��� ���� ������ ����
	,CHANGE_MONEY_REASON_BUYBIDSTOCK					// �ֽ� ���Ժ� ����
	,CHANGE_MONEY_REASON_WORLDTRADEBUY					// ������ ���� ����
	,CHANGE_MONEY_REASON_CRAFTFUND						// ���� ���� ������
	,CHANGE_MONEY_REASON_PUPILREWARD					// ���ڰ� 50������ �Ǿ �ڽ��� ���� �޴´�.
	,CHANGE_MONEY_REASON_GRANDFATHERREWARD				// �� ������ ���ڰ� 50������ �Ǿ ���� ������� �޴´�. 
	,CHANGE_MONEY_REASON_MOFUMOFUEVENT_WARP				// ���ĸ��� �̺�Ʈ �ڵ������� ����
	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
	,CHANGE_MONEY_REASON_MONEY_WARP						// ������ ���� ����
	,CHANGE_MONEY_REASON_WORDSPECIALQUEST				// ������� ����Ʈ �Ϸ�
	,CHANGE_MONEY_REASON_BV_STOCKDIVIDEND				// [����] �ʺ��� ���� : ���� ���
	,CHANGE_MONEY_REASON_BUFF_ROULETTE					// [����] ������ ���� �̺�Ʈ �귿���� ������ ��� ���� => 2008-6-11
	,CHANGE_MONEY_REASON_MARKETCONDITIONS				// [��] �ü�Ȯ������ ����.
	,CHANGE_MONEY_REASON_CHAR_ROULETTE					// [����] �ҷ��� �̺�Ʈ ���� �귿���� ������ ��� ���� => 2008-6-11
	,CHANGE_MONEY_REASON_NEWYEAREVENT_ROULETTE			// [���] �ų��̺�Ʈ ��귿���� ������ ��� ���� => 2008.11.25
	,CHANGE_MONEY_REASON_USENEWMARKET					// ���ս��� �̿�
	,CHANGE_MONEY_REASON_DONATION08_DONATE				// ���ս��� �̿�
	,CHANGE_MONEY_REASON_GAWIBAWIBO_CHARGED_MONEY		//  [8/12/2009 ��ȣ_GAWIBAWIBO] ����-����������
	,CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MONEY		//  [8/12/2009 ��ȣ_GAWIBAWIBO] ����-����������
	,CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MAX_MONEY	//  [8/22/2009 ��ȣ_GAWIBAWIBO] ����-���������� �ְ�ݾ�
	,CHANGE_MONEY_REASON_RACOONDODGE_USEMONEY			//  ���� ���ϱ� �̺�Ʈ�� ���� ��� 
	,CHANGE_MONEY_REASON_RACOONDODGE_REWARD				//  ���� ���ϱ� �̺�Ʈ�� ���� ��� 
	,CHANGE_MONEY_REASON_BOKBULBOK_ENTRANCE_FEE			//	���Һ� �����
	,CHANGE_MONEY_REASON_BOKBULBOK_REWARD				//	���Һ� ����
	,CHANGE_MONEY_REASON_LEVELLIMITBOX_REWARD			// [����] ���� ���� ���ڿ��� �������� �ش� 
	,CHANGE_MONEY_REASON_VALENTINEDAY_BUY_ITEM			// [����] �߷�Ÿ�ε��̿� NPC�� �Ǹ��ϴ� �������� �����Ͽ� �Һ�� �ݾ�

};
/*
#define CHANGE_MONEY_REASON_NOTDEFINED	1	// ���ǵ��� ���� ����.
#define CHANGE_MONEY_REASON_QUESTREWARD	2	// ����Ʈ ���� ���� ����. 
#define CHANGE_MONEY_REASON_DEATH		3	// ����� ���� ����. 
#define CHANGE_MONEY_REASON_TRADE		4	// ��ǰ ��ȯ�� ���� ����. 
#define CHANGE_MONEY_REASON_WARWIN		5	// ���￡�� �¸��Ͽ� ���� ����. 
#define CHANGE_MONEY_REASON_GAMEMASTER	6	// ��ڿ� ���ؼ� ���� ���޹���. 
#define CHANGE_MONEY_REASON_REPAIRPAY	7	// ������� ����. 
#define CHANGE_MONEY_REASON_REPAIRGET	8	// ������� ����.
#define CHANGE_MONEY_REASON_HUNTFEE		11	// ������ ����� ����. 
#define CHANGE_MONEY_REASON_HUNTREWARD	12	// ������ ����� ����. 
#define CHANGE_MONEY_REASON_FATHERREWARD 13	// ���� �����. 
#define CHANGE_MONEY_REASON_RECOMMENDER	 14	// ��õ�� ����. 
#define CHANGE_MONEY_REASON_USEMARKET	15  // ���� �̿뿡 ���� ���� ����. 
#define CHANGE_MONEY_REASON_NPCREPAIRPAY	16	// NPC(�念��) ���� ������� ����. 
#define CHANGE_MONEY_REASON_INVESTMENTINFO	17  // ���ڻ����(�輱��) ��ȸ��� ����
#define CHANGE_MONEY_REASON_MAKE			18  // �����Ƿڷ� ������ ����. 
#define CHANGE_MONEY_REASON_FIZATION		19  // ����ȸ�� ���� ������ ����.
#define CHANGE_MONEY_REASON_BLACKARMYAPPLY	20	// ���Ǳ��� ���� ������ ����
#define CHANGE_MONEY_REASON_BUYBIDSTOCK		21  // �ֽ� ���Ժ� ����
#define CHANGE_MONEY_REASON_WORLDTRADEBUY	22	// ������ ���� ����
#define	CHANGE_MONEY_REASON_CRAFTFUND		23	// ���� ���� ������
#define CHANGE_MONEY_REASON_PUPILREWARD		24	// ���ڰ� 50������ �Ǿ �ڽ��� ���� �޴´�.
#define CHANGE_MONEY_REASON_GRANDFATHERREWARD		25	// �� ������ ���ڰ� 50������ �Ǿ ���� ������� �޴´�. 
#define CHANGE_MONEY_REASON_MOFUMOFUEVENT_WARP		26	// ���ĸ��� �̺�Ʈ �ڵ������� ����
//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
#define CHANGE_MONEY_REASON_MONEY_WARP		27	// ������ ���� ����
#define CHANGE_MONEY_REASON_WORDSPECIALQUEST	28	// ������� ����Ʈ �Ϸ�
*/

class sDBRequest_ChangeMoney
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;						// ����Ʈ �����. 
	UI16				usCharID;
	SI16				siReason;						// ������ ������ ����. 
	GMONEY				siChangedMoney;					// ������ �ݾ�. (+: ����, -:����) 
	TCHAR				strReason[ 128 ];

	sDBRequest_ChangeMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeMoney));
	}

	sDBRequest_ChangeMoney(UI16 charid, SI32 personid, SI16 reason, GMONEY changedmoney, TCHAR *pReason = NULL )
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeMoney );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGEMONEY;

		siPersonID	= personid;
		usCharID	= charid;
		siReason	= reason;
		siChangedMoney = changedmoney;

		if ( pReason )
		{
			MStrCpy( strReason, pReason, 128 );
		}
		else
		{
			strReason[ 0 ] = NULL;
		}
	}
};

class sDBResponse_ChangeMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;						
	UI16				usCharID;
	SI16				siReason;						// ������ ������ ����. 
	GMONEY				siChangedMoney;					// ������ �ݾ�. (+: ����, -:����) 
	GMONEY				siMoney;						// ���� ���� ������. 
	
	SI32				siTargetPersonID;				// �ŷ� �����

	sDBResponse_ChangeMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeMoney));
	}
};

//-----------------------------------------
// ����Ʈ ������ �����Ѵ�.
//-----------------------------------------
class sDBRequest_SetQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;						// ����Ʈ �����. 
	SI16				siQuestType;					// � ������ ����Ʈ�ΰ�?
	cltPersonQuestUnitInfo clQuestInfo;					// �����ؾ��� ����Ʈ ����. 

	sDBRequest_SetQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetQuestInfo));
	}

	sDBRequest_SetQuestInfo(SI32 personid, SI16 questtype, cltPersonQuestUnitInfo* pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetQuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETQUESTINFO;

		siPersonID	= personid;
		siQuestType	= questtype;
		clQuestInfo.Set(pclinfo);
	}
};

class sDBResponse_SetQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	// PCK - �α׿� ��Ŷ
	SI32				siPersonID;
	SI16				siQuestType;
	cltPersonQuestUnitInfo	clQuestInfo;

	sDBResponse_SetQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetQuestInfo));
	}
};

// [����] : ���Һ� - ��������� ����
class sDBRequest_BBB_Set_RewardMoney
{
public:
	sPacketHeader	packetHeader;

	SI64			m_siTotalRewardPriceDeposit;	// ���� ���� �ݾ�

	sDBRequest_BBB_Set_RewardMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_BBB_Set_RewardMoney));
	}

	sDBRequest_BBB_Set_RewardMoney(SI64 siTotalRewardPriceDeposit)
	{
		packetHeader.usSize = sizeof( sDBRequest_BBB_Set_RewardMoney );
		packetHeader.usCmd	= DBMSG_REQUEST_BBB_SET_REWARD_MONEY;

		m_siTotalRewardPriceDeposit = siTotalRewardPriceDeposit;
	}
};

class sDBResponse_BBB_Set_RewardMoney
{
public:
	sPacketHeader	packetHeader;

	SI64	m_siTotalRewardPriceDeposit;	// ���� ���� �ݾ�

	sDBResponse_BBB_Set_RewardMoney()
	{
		ZeroMemory( this, sizeof(sDBResponse_BBB_Set_RewardMoney) );
	}
};

// [����] : ���Һ� - ��������� ���
class sDBRequest_BBB_Get_RewardMoney 
{
public:
	sPacketHeader	packetHeader;

	SI64			m_siTotalRewardPriceWithDraw;	// ���� ���� �ݾ�

	sDBRequest_BBB_Get_RewardMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_BBB_Get_RewardMoney));
	}

	sDBRequest_BBB_Get_RewardMoney(SI64 siTotalRewardPriceWithDraw)
	{
		packetHeader.usSize = sizeof( sDBRequest_BBB_Get_RewardMoney );
		packetHeader.usCmd	= DBMSG_REQUEST_BBB_GET_REWARD_MONEY;

		m_siTotalRewardPriceWithDraw = siTotalRewardPriceWithDraw;
	}
};


// [����] : ���Һ� - ��������� ��� - Response
class sDBResponse_BBB_Get_RewardMoney
{
public:
	sPacketHeader	packetHeader;

	SI64			m_siTotalRewardPriceWithDraw;	// ���� ���� �ݾ�

	sDBResponse_BBB_Get_RewardMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_BBB_Get_RewardMoney));
	}

	sDBResponse_BBB_Get_RewardMoney(SI64 siTotalRewardPriceWithDraw)
	{
		packetHeader.usSize = sizeof( sDBResponse_BBB_Get_RewardMoney );
		packetHeader.usCmd	= DBMSG_RESPONSE_BBB_GET_REWARD_MONEY;

		m_siTotalRewardPriceWithDraw = siTotalRewardPriceWithDraw;
	}
};
//-----------------------------------------
// Ư�� ����Ʈ ������ �����Ѵ�.
//-----------------------------------------
class sDBRequest_SetSpecialQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;						// ����Ʈ �����. 

	cltQuestInfoCommon	clSpecialQuestInfo;
	bool bWordAssemblySwitch[MAX_WORD_ASSEMBLY_CHAR_NUMBER];

	bool bClearWordSpecialQuest;					// �ܾ� ������ �Ϸ��ߴ°�?
	bool bEventClearWordSpecialQuest;				// �̺�Ʈ�Ⱓ���� üũ�ϴ� ���� (����)

	sDBRequest_SetSpecialQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetSpecialQuestInfo));
	}

	sDBRequest_SetSpecialQuestInfo(SI32 personid, cltQuestInfoCommon* pclinfo, bool* pbword,
								   bool clearwordquest=false, bool eventclearwordquest=false) //����
	{
		packetHeader.usSize = sizeof( sDBRequest_SetSpecialQuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETSPECIALQUESTINFO;

		siPersonID	= personid;
		clSpecialQuestInfo.Set(pclinfo);

		for(SI32 i = 0;i < MAX_WORD_ASSEMBLY_CHAR_NUMBER;i++)
		{
			bWordAssemblySwitch[i] = pbword[i];
		}

		bClearWordSpecialQuest = clearwordquest ;
		bEventClearWordSpecialQuest = eventclearwordquest;		//����
		
	}
};

class sDBResponse_SetSpecialQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siPersonID;

	bool				bClearWordSpecialQuest;			// �ܾ� ������ �Ϸ��ߴ°�?
	bool				bEventClearWordSpecialQuest;	// �̺�Ʈ�Ⱓ���� üũ�ϴ� ���� (����)

	SI32				siClearWordSpecialQuestNum;		// ��ι� �ܾ� ���� ������ ��
	SI32				siEventClearWordSpecialQuestNum;// ������� �̺�Ʈ �ܾ� ���� ������ ��.

	// PCK :  �α׿� ��Ŷ �߰�
	cltQuestInfoCommon	clSpecialQuestInfo;
	bool bWordAssemblySwitch[MAX_WORD_ASSEMBLY_CHAR_NUMBER];
	
	sDBResponse_SetSpecialQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetSpecialQuestInfo));
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------
//	�ų��̺�Ʈ - �䱥���ִ� ����Ʈ �߰�.
//---------------------------------------
class sDBRequest_SetRemoveUnluck_QuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					// ����Ʈ �����
	cltQuestInfoCommon	clRemoveUnLuckQuestInfo;

	sDBRequest_SetRemoveUnluck_QuestInfo()
	{
		ZeroMemory( this, sizeof(sDBRequest_SetRemoveUnluck_QuestInfo) );
	}

	sDBRequest_SetRemoveUnluck_QuestInfo(SI32 personid, cltQuestInfoCommon* pclinfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetRemoveUnluck_QuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETREMOVEUNLUCKQUESTINFO;

		siPersonID	= personid;
		clRemoveUnLuckQuestInfo.Set(pclinfo);
	}
};

class sDBResponse_SetRemoveUnluck_QuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32		siPersonID;
	SI32		siresult;		// �����


	sDBResponse_SetRemoveUnluck_QuestInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetRemoveUnluck_QuestInfo) );
	}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// naming - ���̹� ����Ʈ ����
class sDBRequest_SetNamingQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;						// ����Ʈ �����. 
	cltQuestInfoCommon	clNamingQuestInfo;

	sDBRequest_SetNamingQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetNamingQuestInfo));
	}

	sDBRequest_SetNamingQuestInfo(SI32 personid, cltQuestInfoCommon* pclinfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetNamingQuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETNAMINGQUESTINFO;

		siPersonID	= personid;
		clNamingQuestInfo.Set(pclinfo);
	}
};

class sDBResponse_SetNamingQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siPersonID;

	// PCK : �α׿� ��Ŷ �߰�
	cltQuestInfoCommon clNamingQuestInfo;

	sDBResponse_SetNamingQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetNamingQuestInfo));
	}
};

class sDBRequest_SetPersonNamingInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siIndex;
	SI32				siLevel;

	sDBRequest_SetPersonNamingInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetPersonNamingInfo));
	}

	sDBRequest_SetPersonNamingInfo(SI32 personid, SI32 index, SI32 level )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetPersonNamingInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETPERSONNAMINGINFO;

		siPersonID	= personid;
		siIndex = index;
		siLevel = level;
	}
};

class sDBResponse_SetPersonNamingInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siResult;			// �����.
	SI32				siIndex;
	SI32				siLevel;

	sDBResponse_SetPersonNamingInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetPersonNamingInfo));
	}
};

class sDBRequest_SetPersonCurrentNaming
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siSelectedIndex;
	SI32				siSelectedLevel;

	sDBRequest_SetPersonCurrentNaming()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetPersonCurrentNaming));
	}

	sDBRequest_SetPersonCurrentNaming(SI32 personid, SI32 index, SI32 level )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetPersonNamingInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETPERSONCURRENTNAMING;

		siPersonID	= personid;
		siSelectedIndex = index;
		siSelectedLevel = level;
	}
};

class sDBResponse_SetPersonCurrentNaming
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siResult;			// �����.
	SI32				siSelectedIndex;
	SI32				siSelectedLevel;

	sDBResponse_SetPersonCurrentNaming()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetPersonCurrentNaming));
	}
};

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
class sDBRequest_SetHappyBeanQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;						// ����Ʈ �����. 
	cltQuestInfoCommon	clHappyBeanQuestInfo;

	sDBRequest_SetHappyBeanQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetHappyBeanQuestInfo));
	}

	sDBRequest_SetHappyBeanQuestInfo(SI32 personid, cltQuestInfoCommon* pclinfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetHappyBeanQuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETHAPPYBEANQUESTINFO;

		siPersonID	= personid;
		clHappyBeanQuestInfo.Set(pclinfo);
	}
};

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. �̺�Ʈ ���� ������ DB�� ���� ���� ���θ�Ȯ���Ѵ�.
class sDBRequest_SetHappyBeanClearInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siQuestType; // QUEST_TYPE_HAPPYBEAN
	SI32				siQuestState; // QUEST_HAPPYBEAN_STEP_NON, QUEST_HAPPYBEAN_STEP_START, QUEST_HAPPYBEAN_STEP_COMPLETE

	sDBRequest_SetHappyBeanClearInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetHappyBeanClearInfo));
	}

	sDBRequest_SetHappyBeanClearInfo(SI32 personid, SI32 questtype, SI32 QuestState )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetHappyBeanClearInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_GETHAPPYBEANQUESTINFO;

		siPersonID	= personid;
		siQuestType = questtype;
		siQuestState = QuestState;
	}
};

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. �̺�Ʈ ������� ������ DB�� ���� ���� �޾� Ȯ���Ѵ�.
class sDBResponse_GetHappyBeanClearInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siQuestType; // QUEST_TYPE_HAPPYBEAN
	SI32				siQuest_StartCount; //  QUEST_HAPPYBEAN_STEP_START �� ī����. �ʱ�ȭ ��Ű�� ����.
	SI32				siQuest_CompleteCount; //  QUEST_HAPPYBEAN_STEP_COMPLETE �� ī����. 1�Ͽ� �ѹ� �ʱ�ȭ.

//	SI32				siResult;			// �����. 0 = ����Ʈ ����. 1= ����Ʈ ���� �㰡. 2= ����Ʈ �Ϸᰡ ���������� ���� �Ǿ���.


	sDBResponse_GetHappyBeanClearInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetHappyBeanClearInfo));
	}
};

//------------------------------------------------------------------------------
// class : sDBRequest_SetNamingQuestInfo
// desc  : �̼� ����Ʈ ���� ����
//------------------------------------------------------------------------------
class sDBRequest_SetMissionQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;						// ����Ʈ �����. 
	cltMissionQuestInfo	clMissionQuestInfo;

	sDBRequest_SetMissionQuestInfo(SI32 personid, cltMissionQuestInfo* pclinfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetMissionQuestInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETMISSIONQUESTINFO;

		siPersonID	= personid;
		clMissionQuestInfo.Set(pclinfo);
	}
};

class sDBResponse_SetMissionQuestInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siPersonID;

	// LEEKH : �α׿� ��Ŷ �߰�
	cltMissionQuestInfo clMissionQuestInfo;

	sDBResponse_SetMissionQuestInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetMissionQuestInfo));
	}
};

/*-------------------------------------------------------------------
�з�: Person Info
����: Person ���� [��û]
�ð�: 2003-07-29
-------------------------------------------------------------------*/
class sDBRequest_PersonTotalInfoCreate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBPersonTotalInfo	info;

	sDBRequest_PersonTotalInfoCreate()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonTotalInfoCreate));
	}

	sDBRequest_PersonTotalInfoCreate(SI32 id, sDBPersonTotalInfo* pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonTotalInfoCreate );
		packetHeader.usCmd = DBMSG_REQUEST_PERSONTOTALINFOCREATE;
		usCharID	= id;

		info = *pclinfo;
	}
};

/*-------------------------------------------------------------------
�з�: Person Info
Person ���� [����]
�ð�: 2003-07-29
-------------------------------------------------------------------*/
class sDBResponse_PersonTotalInfoCreate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	SI32				siMakeNumber;		// �� �������� ĳ���Ͱ� ������ Ƚ��. 

	SI32				siResult;			// �����. (1: ����. 0:����) 

	//KHY - 1024 - �߰� ����.
	TCHAR				szAccountID[MAX_PLAYER_NAME];	// �� Person�� �Ҽӵ� ������ ���̵�. 
	TCHAR 				szName[MAX_PLAYER_NAME];		// ĳ���� ID.
	SI32				siPersonID;						// ĳ���� PersonID

	sDBResponse_PersonTotalInfoCreate()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonTotalInfoCreate));
	}

};

//-----------------------------------------
// �ǰ� ������ �����Ѵ�. 
//-----------------------------------------
class sDBRequest_SetHealth
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	cltHealthInfo		clHealthInfo;

	sDBRequest_SetHealth()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetHealth));
	}

	sDBRequest_SetHealth(SI32 personid, cltHealthInfo* pclhealthinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetHealth );
		packetHeader.usCmd	= DBMSG_REQUEST_SETHEALTH;

		siPersonID	= personid;
		clHealthInfo.Set(pclhealthinfo);
	}
};

class sDBResponse_SetHealth
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	sDBResponse_SetHealth()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetHealth));
	}
};





//-----------------------------------------
// Pos, Life, Mana, PlaySecond�� �����ϵ��� �Ѵ�. 
//-----------------------------------------
class sDBRequest_SetPosLifeMana
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	cltCharPos			clPos;
	SI32				siLife;
	SI32				siMana;
	SI32				siPlaySecond;
	SI32				siPlayEventSecond;
	cltPos				clLastMainMapPos;

	sDBRequest_SetPosLifeMana()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetPosLifeMana));
	}

	sDBRequest_SetPosLifeMana(SI32 personid, cltCharPos* pclpos, SI32 life, SI32 mana, SI32 playsecond, SI32 playeventsecond, cltPos* pcllastmainmappos)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetPosLifeMana );
		packetHeader.usCmd	= DBMSG_REQUEST_SETPOSLIFEMANA;

		siPersonID	= personid;
		clPos.Set(pclpos);
		siLife	= life;
		siMana	= mana;
		siPlaySecond	= playsecond;
		siPlayEventSecond	= playeventsecond;
		clLastMainMapPos.Set(pcllastmainmappos);
	}
};

class sDBResponse_SetPosLifeMana
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	// PCK : �α׿� ���� ��Ŷ �߰�

	SI32				siPersonID;
	cltCharPos			clPos;
	SI32				siLife;
	SI32				siMana;
	SI32				siPlaySecond;
	SI32				siPlayEventSecond;
	cltPos				clLastMainMapPos;

	sDBResponse_SetPosLifeMana()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetPosLifeMana));
	}
};



//-----------------------------------------
// ���� ���� ���̵� �޾ƿ´�.
//-----------------------------------------
class sDBRequest_Userid
{
public:	
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siMyPersonID;
	SI32				siToPersonID;
	TCHAR				szToPersonName[ MAX_PLAYER_NAME ];

	sDBRequest_Userid( UI16 CharID, SI32 MyPersonID, SI32 ToPersonID )
	{
		packetHeader.usSize = sizeof( sDBRequest_Userid );
		packetHeader.usCmd	= DBMSG_REQUEST_USERID;

		usCharID = CharID;
		siMyPersonID = MyPersonID;
		siToPersonID = ToPersonID;

		szToPersonName[ 0 ] = NULL;
	}	

	sDBRequest_Userid( UI16 CharID, SI32 MyPersonID, TCHAR *szname )
	{
		packetHeader.usSize = sizeof( sDBRequest_Userid );
		packetHeader.usCmd	= DBMSG_REQUEST_USERID;

		usCharID = CharID;
		siMyPersonID = MyPersonID;
		siToPersonID = 0;

		memcpy( szToPersonName, szname, MAX_PLAYER_NAME );
		szToPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};

class sDBResponse_Userid
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;	
	SI32				siPersonID;
	SI32				siResult;			// �����.
	TCHAR				strUserID[ 20 ];

	bool				bShowPuchikomi;

	sDBResponse_Userid()
	{
		ZeroMemory(this, sizeof(sDBResponse_Userid));
	}
};

//----------------------------------------
// �б����. 
//----------------------------------------
class sDBRequest_SetSchool
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siSchoolUnique;		// �б��� ����ũ. 

	sDBRequest_SetSchool()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetSchool));
	}

	sDBRequest_SetSchool(UI16 charid, SI32 personid, SI16 schoolunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetSchool );
		packetHeader.usCmd	= DBMSG_REQUEST_SETSCHOOL;

		usCharID		= charid;
		siPersonID		= personid;
		siSchoolUnique	= schoolunique;
	}
};

class sDBResponse_SetSchool
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	sDBResponse_SetSchool()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetSchool));
	}
};



//----------------------------------------
// ���� ���. 
//----------------------------------------
class sDBRequest_SetFather
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	TCHAR				szFatherName[MAX_PLAYER_NAME];
	SI16				siMyLevel;						// ������ ����� ����� �� ���� 

	sDBRequest_SetFather()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetFather));
	}

	sDBRequest_SetFather(UI16 charid, SI32 personid, TCHAR* pfathername, SI16 mylevel)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetFather );
		packetHeader.usCmd	= DBMSG_REQUEST_SETFATHER;

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szFatherName, pfathername, MAX_PLAYER_NAME );

		siMyLevel	= mylevel;
	}
};

class sDBResponse_SetFather
{
public:
	sPacketHeader		packetHeader;
	

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siFatherPersonID;				// ���� ������ ���� ���̵�. 
	SI16				siMyLevel;						// ���� ���� ����� �� ���� 
	TCHAR				szFatherName[MAX_PLAYER_NAME];	// ���� ������ ���� �̸�. 

	SI32				siPrevFatherPersonID;			// ���� ���� ���̵�. (���� ���¿��� ������ ������ ���� ) 
	SI16				siChangedFatherNumber;			// ������ ����� Ƚ��. 
	TCHAR				szAccountID[MAX_PLAYER_NAME];

	sDBResponse_SetFather()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetFather));
	}
};

//----------------------------------------
// Person�� ���� ���� ��û. 
//----------------------------------------
#define PERSONSIMPLEINFO_REASON_FATHERREWARD			1		// ���� ������ ���� ���� ���� ��û. 
#define PERSONSIMPLEINFO_REASON_PROMOTER_INFO			2		// [����] ���θ��� ����.
#define PERSONSIMPLEINFO_REASON_RECOMMEND_INTRODUCE		3		// [����] ��õ���� ����õ�ο��� �λ縻.
#define PERSONSIMPLEINFO_REASON_RECOMMENDEE_INTRODUCE	4		// [����] ����õ���� ��õ�ο��� �λ縻

class sDBRequest_PersonSimpleInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siReason;

	TCHAR				szGetCharInfoName[MAX_PLAYER_NAME];	// [����] ������ ����� �ϴ� ĳ����.
	TCHAR				szCharInfoName[MAX_PLAYER_NAME];	// [����] szGetCharInfoName ��û�� ĳ���� �̸�.

	sDBRequest_PersonSimpleInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonSimpleInfo));
	}

	sDBRequest_PersonSimpleInfo(UI16 charid, SI32 personid, SI16 reason, const TCHAR* pszGetCharInfoName = NULL, const TCHAR* pszCharInfoName = NULL )
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonSimpleInfo);
		packetHeader.usCmd	= DBMSG_REQUEST_PERSONSIMPLEINFO;

		usCharID		= charid;
		siPersonID		= personid;
		siReason		= reason;

		if( pszCharInfoName )
			StringCchCopy( szCharInfoName, sizeof(szCharInfoName), pszCharInfoName );

		if( pszGetCharInfoName )
			StringCchCopy( szGetCharInfoName, sizeof(szGetCharInfoName), pszGetCharInfoName );
	}
};

class sDBResponse_PersonSimpleInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;
	SI16				siReason;
	SI16				siLevel;
	SI32				siGrandPersonID;	// �� ������ ������ PersonID 
	SI16				siCharKind;

	TCHAR				szGetCharInfoName[MAX_PLAYER_NAME];	// [����] ������ ����� �ϴ� ĳ����.
	TCHAR				szCharInfoName[MAX_PLAYER_NAME];	// [����] szGetCharInfoName ��û�� ĳ���� �̸�.

	sDBResponse_PersonSimpleInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonSimpleInfo));
	}
};


//----------------------------------------
// �缺�� ���ڼ��� ���� ���� ��û. 
//----------------------------------------
class sDBRequest_IncreaseChildNumber
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI16				siIncNum;		// �ÿ��� �� ��. 

	sDBRequest_IncreaseChildNumber()
	{
		ZeroMemory(this, sizeof(sDBRequest_IncreaseChildNumber));
	}

	sDBRequest_IncreaseChildNumber(SI32 personid, SI16 incnum)
	{
		packetHeader.usSize = sizeof( sDBRequest_IncreaseChildNumber);
		packetHeader.usCmd	= DBMSG_REQUEST_INCREASECHILDNUMBER;

		siPersonID		= personid;
		siIncNum		= incnum;
	}
};

class sDBResponse_IncreaseChildNumber
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;			// �����.

	SI32				siPersonID;
	SI16				siChildNumber;		// �缺�� ���� ��. 

	sDBResponse_IncreaseChildNumber()
	{
		ZeroMemory(this, sizeof(sDBResponse_IncreaseChildNumber));
	}
};


//----------------------------------------
// ������ ����Ʈ��  ���Ѵ�. 
//----------------------------------------
class sDBRequest_GetChildList
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	sDBRequest_GetChildList()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetChildList));
	}

	sDBRequest_GetChildList(UI16 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetChildList);
		packetHeader.usCmd	= DBMSG_REQUEST_GETCHILDLIST;

		usCharID		= id;
		siPersonID		= personid;
	}
};

class sDBResponse_GetChildList
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	cltChildInfo		clChildInfo[MAX_CHILDINFO_NUMBER];

	sDBResponse_GetChildList()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetChildList));
	}
};

//-----------------------------------------
// ����ġ��  ������Ų��.
//-----------------------------------------
#define CHANGE_EXP_REASON_FATHER	1	// �İ� �������� ����ġ ����. 
#define CHANGE_EXP_REASON_HUNTCHIEF	2	// ������ ������� ����ġ ����. 
class sDBRequest_ChangeExp
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;						// ����Ʈ �����. 
	SI16				siReason;						// ������ ����. 
	SI32				siChangedExp;					// ������ ��ġ (+: ����, -:����) 

	sDBRequest_ChangeExp()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeExp));
	}

	sDBRequest_ChangeExp(SI32 personid, SI16 reason, SI32 changedexp)
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeExp );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGEEXP;

		siPersonID		= personid;
		siReason		= reason;
		siChangedExp	= changedexp;
	}
};

class sDBResponse_ChangeExp
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;						// �����. 
	SI16				siReason;						// ������ ����. 
	SI32				siChangedExp;					// ������ �ݾ�. (+: ����, -:����) 
	SI64				siExp;							// ���� ����ġ ������. // sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	
	sDBResponse_ChangeExp()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeExp));
	}
};


//-----------------------------------------
// �� ����ġ��  ������Ų��.
//-----------------------------------------
#define CHANGE_FAMEEXP_REASON_FATHER		1	// �İ� �������� ����ġ ����. 
#define CHANGE_FAMEEXP_REASON_RECOMMEND		2	// ��õ������ ����ġ ����. 

class sDBRequest_ChangeFameExp
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;						// ����Ʈ �����. 
	SI16				siReason;						// ������ ����. 
	SI32				siChangedFameExp;				// ������ ��ġ (+: ����, -:����) 

	sDBRequest_ChangeFameExp()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeFameExp));
	}

	sDBRequest_ChangeFameExp(SI32 personid, SI16 reason, SI32 changedfameexp)
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeFameExp );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGEFAMEEXP;

		siPersonID			= personid;
		siReason			= reason;
		siChangedFameExp	= changedfameexp;
	}
};

class sDBResponse_ChangeFameExp
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// �����. 
	SI16				siReason;			// ������ ����. 
	SI32				siChangedFameExp;	// ������ �ݾ�. (+: ����, -:����) 
	SI32				siFameExp;			// ���� ����ġ ������. 
	
	sDBResponse_ChangeFameExp()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeFameExp));
	}
};
//-----------------------------------------
// �������ͽ� �ʱ�ȭ ��û 
//-----------------------------------------
#define INITSTATUSMODE_LEVEL_10 			1		// 10 ���� ���޿� ���� �ʱ�ȭ. 
#define INITSTATUSMODE_TICKET				2		// �̿�� ����� �ʱ�ȭ.
#define INITSTATUSMODE_LEVEL_30 			3		// 30 ���� ���޿� ���� �ʱ�ȭ. (�߰���[����])
#define INITSTATUSMODE_CHINA_EVENTTICKET	4
#define INITSTATUSMODE_GMTOOL				5

class sDBRequest_InitStatus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;						// �ʱ�ȭ  �����. 

	SI16				siMode;
	cltItem				clItem;							// ������ �������� ����ũ. 
	SI16				siItemPos;						// ������ ��ǰ�� �ִٸ�,, 

	sDBRequest_InitStatus()
	{
		ZeroMemory(this, sizeof(sDBRequest_InitStatus));
	}

	sDBRequest_InitStatus(UI16 charid, SI32 personid, SI16 mode, SI16 itempos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_InitStatus );
		packetHeader.usCmd	= DBMSG_REQUEST_INITSTATUS;

		usCharID		= charid;
		siPersonID		= personid;
		siMode			= mode;
		siItemPos		= itempos;
		if(pclitem)
		{
			clItem.Set(pclitem);
		}
		else
		{
			clItem.Init();

		}
	}
};

class sDBResponse_InitStatus
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;						// �����. 

	SI16				siMode;
	cltItem				clItem;							// ������ �������� ����ũ. 
	SI16				siItemPos;						// ������ ��ǰ�� �ִٸ�,, 

	// PCK : �α׿� ��Ŷ �߰�
	cltItem				clItem_Log;

	sDBResponse_InitStatus()
	{
		ZeroMemory(this, sizeof(sDBResponse_InitStatus));
	}
};

//-----------------------------------------
// ��õ�� ����
//-----------------------------------------
class sDBRequest_RecommendPerson
{
public:
	sPacketHeader		packetHeader;
	
	TCHAR				strUserName[ MAX_PLAYER_NAME ];
	SI32				siIDNum;
	UI08				uiSlot;

	SI32				siPersonID;

	SI32				siCharID;

	sDBRequest_RecommendPerson( TCHAR *UserName, SI32 IDNum, UI08 slot,SI32 PersonID ,SI32 CharID )
	{
		packetHeader.usSize = sizeof( sDBRequest_RecommendPerson );
		packetHeader.usCmd	= DBMSG_REQUEST_RECOMMENDPERSON;

		MStrCpy( strUserName, UserName, MAX_PLAYER_NAME );

		siIDNum = IDNum ;
		uiSlot = slot ;

		siPersonID = PersonID;

		siCharID = CharID;
	}
};

class sDBResponse_RecommendPerson
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	TCHAR				strRecommenderUserName[ MAX_PLAYER_NAME ];
	TCHAR				strUserName[ MAX_PLAYER_NAME ];
	SI32				siIDNum;
	UI08				uiSlot;

	SI32				siPersonID;

	SI32				siCharID;
	SI32				siRecommendPersonID;
	
	sDBResponse_RecommendPerson()
	{
		ZeroMemory(this, sizeof(sDBResponse_RecommendPerson));
	}
};

class sDBRequest_HorseNameChange
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siHorseIndex;
	TCHAR				strHorseName[ MAX_HORSE_NAME ];

	sDBRequest_HorseNameChange( SI32 CharID, SI32 PersonID, SI16 HorseIndex, TCHAR *HorseName )
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseNameChange );
		packetHeader.usCmd	= DBMSG_REQUEST_HORSENAMECHANGE;

		siCharID = CharID;
		siPersonID = PersonID;

		siHorseIndex = HorseIndex;
		MStrCpy( strHorseName, HorseName, MAX_HORSE_NAME );
		strHorseName[ MAX_HORSE_NAME -1 ] = '\0';
	}	
};

class sDBResponse_HorseNameChange
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siHorseIndex;
	TCHAR				strHorseName[ MAX_HORSE_NAME ];

	sDBResponse_HorseNameChange()
	{
		memset( this, 0, sizeof( sDBResponse_HorseNameChange ) );
	}
};

//-----------------------------------------
// DB�� ���� ������ �����ϱ� ���ؼ�.
//-----------------------------------------
class sDBRequest_GuiltyInfoRecord
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
	cltGuiltyInfo		clGuiltyInfo;

	sDBRequest_GuiltyInfoRecord( SI32 CharID, SI32 PersonID, cltGuiltyInfo *pclguiltyinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_GuiltyInfoRecord );
		packetHeader.usCmd	= DBMSG_REQUEST_GUILTYINFORECORD;

		siCharID = CharID;
		siPersonID = PersonID;

		clGuiltyInfo.Set(pclguiltyinfo);
	}
	
};

class sDBResponse_GuiltyInfoRecord
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	// PCK : �α׿� ��Ŷ �߰�
	cltGuiltyInfo		cIGuiltyInfo;

	sDBResponse_GuiltyInfoRecord()
	{
		memset( this, 0, sizeof( sDBResponse_GuiltyInfoRecord ) );
	}
};

//-----------------------------------------
// DB�� �α׾ƿ� ������ �����ϱ� ���ؼ�.
//-----------------------------------------
class sDBRequest_LogOutRecord
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siPersonID;						// ����Ʈ �����. 
	TCHAR				szIP[64];
	UI08				uiNormalQuitSwitch;

	sDBRequest_LogOutRecord( SI32 PersonID, TCHAR* IP, bool NormalQuitSwitch )
	{
		packetHeader.usSize = sizeof( sDBRequest_LogOutRecord );
		packetHeader.usCmd	= DBMSG_REQUEST_LOGOUTRECORD;
		siPersonID = PersonID;
		memcpy( szIP, IP, 64 );
		szIP[ 63 ] = NULL;

		if ( NormalQuitSwitch )
		{
			uiNormalQuitSwitch = 1;
		}
		else
		{
			uiNormalQuitSwitch = 0;
		}
	}
};

//--------------------------------------------------
// DB�� �̸� ������ ��û�Ѵ�.
//-------------------------------------------------
class sDBRequest_ChangeName
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;		// �̸� ������ �����
	SI32				siCharID;		// �α��ν� ĳ���͸��� ����� ����ʿ��� ĳ���� id

	TCHAR				szName[MAX_PLAYER_NAME];

	SI16				siPos;
	cltItem				clitem;

	bool				m_bUseItem;	// [��ȣ_NHN->NDOORS] �������� �̿��ؼ� ĳ���͸� �����ϴ� ���

	sDBRequest_ChangeName(SI32 personid,TCHAR * name,SI32 pos ,cltItem* pclItem, bool bUseItem)
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeName));

		packetHeader.usSize = sizeof( sDBRequest_ChangeName );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGENAME;

		siPersonID = personid ;

		MStrCpy( szName, name, MAX_PLAYER_NAME );

		siPos = pos ;
		clitem.Set(pclItem);

		m_bUseItem = bUseItem;
	}
};


#define CHANGENAME_REASON_SPECIALCHAR_CHANGENAME	1  //[��ȣ] ĳ���͸��� Ư������ �ΰ�� ĳ���͸� ����

class sDBResponse_ChangeName
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siPersonID;		// �̸� ������ �����
	SI32				siCharID;		// �α��ν� ĳ���͸��� ����� ����ʿ��� ĳ���� id

	TCHAR				szName[MAX_PLAYER_NAME];
	TCHAR				szOldName[MAX_PLAYER_NAME];

	SI16				siPos;
	cltItem				clitem;

	// PCK - �α׿�
	cltItem				clitem_Log;

	bool				m_bUseItem;	// [��ȣ_NHN->NDOORS] �α��ν� ĳ���͸� �����ϴ� ���

	sDBResponse_ChangeName()
	{
		memset( this, 0, sizeof( sDBResponse_ChangeName ) );
	}
};

class sDBRequest_Change_CharKind
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;

	SI16				siKind;

	SI16				siPos;
	cltItem				clitem;

	sDBRequest_Change_CharKind(SI32 personid,SI16 kind,SI32 pos ,cltItem* pclItem)
	{
		packetHeader.usSize = sizeof( sDBRequest_Change_CharKind );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGE_CHARKIND;

		siPersonID = personid ;

		siKind = kind ;

		siPos = pos ;
		clitem.Set(pclItem);
	}
};

class sDBResponse_Change_CharKind
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siPersonID;

	SI16				siKind;

	SI16				siPos;
	cltItem				clitem;

	// PCK - �α׿� ��Ŷ
	cltItem				clitem_Log;

	sDBResponse_Change_CharKind()
	{
		memset( this, 0, sizeof( sDBResponse_Change_CharKind ) );
	}
};

class sDBRequest_SetMinister
{
public:
	sPacketHeader		packetHeader;

	SI16				siMinister;
	
	SI32				siPersonID;

	TCHAR				szName[MAX_PLAYER_NAME];

	bool				bMaster;
	SI32				siSetMinisterTime;

	sDBRequest_SetMinister(SI16 minister,SI32 personid,TCHAR * name,bool master,SI32 time)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetMinister );
		packetHeader.usCmd	= DBMSG_REQUEST_SETMINISTER;

		siMinister = minister ;

		siPersonID = personid ;

		MStrCpy( szName, name, MAX_PLAYER_NAME );
		szName[MAX_PLAYER_NAME - 1] = '\0';

		bMaster = master ;
		siSetMinisterTime = time ;
	}
};

class sDBResponse_SetMinister
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI16				siMinister;

	SI32				siPersonID;

	SI32				siTempPersonId;
	SI32				siMinisterPersonId;

	sDBResponse_SetMinister()
	{
		memset( this, 0, sizeof( sDBResponse_SetMinister ) );
	}
};

// ��ȣ(ȣ��)�� ���� ���� ����
class sDBRequest_SetLiquidation
{
public:
	sPacketHeader		packetHeader;

	SI32	siPersonID;

	SI16	siLiquidationVillageNumber;
	SI32	siSetLiquidationVillageDate;

	sDBRequest_SetLiquidation( SI32 personid, SI16 LiquidationVillageNumber, SI32 SetLiquidationVillageDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetLiquidation );
		packetHeader.usCmd	= DBMSG_REQUEST_SETLIQUIDATION;

		siPersonID = personid;
		siLiquidationVillageNumber = LiquidationVillageNumber;
		siSetLiquidationVillageDate = SetLiquidationVillageDate;
	}
};

class sDBResponse_SetLiquidation
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;

	sDBResponse_SetLiquidation()
	{
		memset( this, 0, sizeof( sDBResponse_SetLiquidation ) );
	}
};

// ���ְ� ���ʽ� Ÿ���� ����
class sDBRequest_Goonzu_SetBonusTime
{
public:
	sPacketHeader		packetHeader;

	SI32	siPersonID;

	SI16	siBonusTime;
	SI16	siMakeBonusTime;
	
	SI16    siChangedBonusTimeYear;
	SI16    siChangedBonusTimeMonth;
	SI16    siChangedBonusTimeDay;


	sDBRequest_Goonzu_SetBonusTime( SI32 personid, SI16 BonusTime , SI16 MakeBonusTime , SI16 ChangedBonusTimeYear , SI16 ChangedBonusTimeMonth, SI16 ChangedBonusTimeDay )
	{
		packetHeader.usSize = sizeof( sDBRequest_Goonzu_SetBonusTime );
		packetHeader.usCmd	= DBMSG_REQUEST_GOONZU_SETBONUSTIME;

		siPersonID = personid;
		
		siBonusTime = BonusTime;
		siMakeBonusTime = MakeBonusTime;

		siChangedBonusTimeYear = ChangedBonusTimeYear;
		siChangedBonusTimeMonth = ChangedBonusTimeMonth;
		siChangedBonusTimeDay = ChangedBonusTimeDay;
	}
};


class sDBResponse_Goonzu_SetBonusTime
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;

	//[�߰� : Ȳ���� 2007. 11. 7 �α׿� �̿�. ���ֱ��� ���ʽ� Ÿ��(1�ð�)]
	SI16				siBonusTime;
	SI16				siMakeBonusTime;

	sDBResponse_Goonzu_SetBonusTime()
	{
		memset( this, 0, sizeof( sDBResponse_Goonzu_SetBonusTime ) );
	}
};

class sDBRequest_Prize_GameEvent
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	UI16				usCharID;

	UI08				bGameEvent;
	bool				bWinPrizeEvent;

	sDBRequest_Prize_GameEvent(SI32 personid,UI16 charid,UI08 gameevent , bool winprizeevent )
	{
		packetHeader.usSize = sizeof( sDBRequest_Prize_GameEvent );
		packetHeader.usCmd	= DBMSG_REQUEST_PRIZE_GAMEEVENT;

		siPersonID = personid ;
		usCharID = charid ;

		bGameEvent = gameevent ;
		bWinPrizeEvent = winprizeevent ;
	}
};

class sDBResponse_Prize_GameEvent
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;
	UI16				usCharID;

	bool				bGameEvent;
	bool				bWinPrizeEvent;

	sDBResponse_Prize_GameEvent()
	{
		memset( this, 0, sizeof( sDBResponse_Prize_GameEvent ) );
	}
};

class sDBRequest_CountAttack_Info
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	UI16				usCharID;

	cltItem				clitem;
	SI16				siItemPos;

	sDBRequest_CountAttack_Info(SI32 personid,UI16 charid,cltItem *pclitem,SI16 pos)
	{
		packetHeader.usSize = sizeof( sDBRequest_CountAttack_Info );
		packetHeader.usCmd	= DBMSG_REQUEST_COUNTATTACK_INFO;

		siPersonID = personid ;
		usCharID = charid ;

		clitem.Set(pclitem);
		siItemPos = pos ;
	}

};

class sDBResponse_CountAttack_Info
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siPersonID;
	UI16				usCharID;

	cltItem				clitem;
	SI16				siItemPos;

	SI32				siFlagNum;
	SI32				siBeforeNum;

	sDBResponse_CountAttack_Info()
	{
		memset( this, 0, sizeof( sDBResponse_CountAttack_Info ) );
	}
};

// �λ縻 ���� 
class sDBRequest_SetGreeting
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
		
	TCHAR				szText[ 128 ];

	sDBRequest_SetGreeting(SI32 charid, SI32 personid, TCHAR* pText)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetGreeting );
		packetHeader.usCmd	= DBMSG_REQUEST_SETGREETING;

		siCharID   = charid;
		siPersonID = personid;
		MStrCpy(szText, pText, 128);
	}
	
};

// �λ縻 ����
class sDBResponse_SetGreeting
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;
		
	TCHAR				szText[ 128 ];

	sDBResponse_SetGreeting()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetGreeting ) );
	}
};

// �λ縻 ������
class sDBRequest_GetGreeting
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
		
	SI32				siParam;

	TCHAR				szPersonName[ MAX_PLAYER_NAME ];

	sDBRequest_GetGreeting(SI32 charid, SI32 personid, SI32 paramid, TCHAR* personname)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetGreeting );
		packetHeader.usCmd	= DBMSG_REQUEST_GETGREETING;

		siCharID   = charid;
		siPersonID = personid;
		siParam    = paramid;
		MStrCpy(szPersonName, personname, MAX_PLAYER_NAME);
	}

};

// �λ縻 ������
class sDBResponse_GetGreeting
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;
		
	SI32				siParam;

	TCHAR				szText[ 128 ];

	TCHAR				szPersonName[ MAX_PLAYER_NAME ];

	sDBResponse_GetGreeting()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetGreeting ) );
	}
};

// Ȩ������ URL ������
class sDBRequest_Get_HomePageURL
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	sDBRequest_Get_HomePageURL(SI32 charid, SI32 personid, TCHAR* personname)
	{
		packetHeader.usSize = sizeof( sDBRequest_Get_HomePageURL );
		packetHeader.usCmd	= DBMSG_REQUEST_GET_HOMEPAGE_URL;

		siCharID   = charid;
		siPersonID = personid;
	}

};

// Ȩ������ URL ������
class sDBResponse_Get_HomePageURL
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;
		
	TCHAR				szText[ 128 ];

	sDBResponse_Get_HomePageURL()
	{
		ZeroMemory( this, sizeof( sDBResponse_Get_HomePageURL ) );
	}
};

// Ȩ������ URL �����ϱ�
class sDBRequest_Set_HomePageURL
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
		
	TCHAR				szText[ 128 ];

	sDBRequest_Set_HomePageURL(SI32 charid, SI32 personid, TCHAR* pText)
	{
		packetHeader.usSize = sizeof( sDBRequest_Set_HomePageURL );
		packetHeader.usCmd	= DBMSG_REQUEST_SET_HOMEPAGE_URL;

		siCharID   = charid;
		siPersonID = personid;
		MStrCpy( szText, pText, sizeof(szText) );
	}
	
};

// Ȩ������ URL �����ϱ�
class sDBResponse_Set_HomePageURL
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;
		
	TCHAR				szText[ 128 ];

	sDBResponse_Set_HomePageURL()
	{
		ZeroMemory( this, sizeof( sDBResponse_Set_HomePageURL ) );
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////
class sDBRequest_GetItemMakerNameNew
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siSerialID;

	SI32				siDupSerialID; // DB�ʿ��� �ش� �ø����� ��ã���� 0���� �����ϱ� ������ ���� ��û�� �ø��� ��ȣ�� ���⼭ ���� �ִ´�


	sDBRequest_GetItemMakerNameNew( SI32 charid, SI32 SerialID )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetItemMakerNameNew );
		packetHeader.usCmd	= DBMSG_REQUEST_ITEMMAKERNAMENEW;

		siCharID		= charid;
		siSerialID		= SerialID;
		siDupSerialID	= SerialID;
	}
};

class sDBResponse_GetItemMakerNameNew
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siSerialID;
	SI32				siDupSerialID;
	SI16				siServerUnique;

	TCHAR				szName[ MAX_PLAYER_NAME ];


	sDBResponse_GetItemMakerNameNew()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetItemMakerNameNew));
	}

};

class sDBRequest_GetItemMakerName
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;


	sDBRequest_GetItemMakerName( SI32 charid, SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetItemMakerName );
		packetHeader.usCmd	= DBMSG_REQUEST_ITEMMAKERNAME;

		siCharID   = charid;
		siPersonID = personid;
	}

};

class sDBResponse_GetItemMakerName
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	char				szName[ MAX_PLAYER_NAME ];


	sDBResponse_GetItemMakerName()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetItemMakerName));
	}

};

enum
{
	RPGIVE_REASON_LEVELUP = 1,
	RPGIVE_REASON_ITEMMALL
};
class sDBRequest_ChangeRecommendPoint
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;						// �������. 	
	TCHAR				szCharName[MAX_PLAYER_NAME];	// ��������̸�.

	SI32				siRecommendPersonID;			// �޴»��.

	SI32				siLevel;
	SI32				siChangedRecommentPoint;		// ������ ��ġ (+: ����, -:����) 

	SI32				siReason;

	sDBRequest_ChangeRecommendPoint()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeRecommendPoint));
	}

	sDBRequest_ChangeRecommendPoint( SI32 CharID, SI32 PersonID  , TCHAR * CharName, SI32 level , SI32 RecommendPersonID, SI32 ChangedRecommentPoint, SI32 Reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeRecommendPoint );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGERECOMMENDPOINT;
		
        StringCchCopy(szCharName,MAX_PLAYER_NAME, CharName);
		siLevel				= level;
		siCharID			= CharID;
		siPersonID			= PersonID;		
		siChangedRecommentPoint	= ChangedRecommentPoint; 
		siRecommendPersonID	= RecommendPersonID;
		siReason			= Reason;
	}
};

class sDBResponse_ChangeRecommendPoint
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;						// �������. 	

	SI32				siResult;					// �����.
	
	TCHAR				szCharName[MAX_PLAYER_NAME];// ��������̸�

	SI32				siRecommendPersonID;// �޴»��.

	SI32				siChangedRecommendPoint;	// ������ �ݾ�. (+: ����, -:����) 

	SI32				siLevel;
	SI32				siRecommendPoint;			// ���� ����ġ ������. 

	// PCK - �α׿� ��Ŷ�߰�
	SI32				siReason;

	sDBResponse_ChangeRecommendPoint()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeRecommendPoint));
	}
};


class sDBRequest_GetRecommendPoint
{
public:
	sPacketHeader		packetHeader;
	SI32				siCharID;
	SI32				siPersonID;						// �����. 	

	sDBRequest_GetRecommendPoint()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetRecommendPoint));
	}

	sDBRequest_GetRecommendPoint(SI32 charid	,SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetRecommendPoint );
		packetHeader.usCmd	= DBMSG_REQUEST_GETRECOMMENDPOINT;

		siCharID			= charid;
		siPersonID			= personid;
	}
};


class sDBResponse_GetRecommendPoint
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	
	SI32				siCharID;
	SI32				siPersonID;			// �����. 
	SI32				siRecommendPoint;			// ��õ ����Ʈ

	sDBResponse_GetRecommendPoint()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetRecommendPoint));
	}
};

class sDBRequest_SetCountry
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCountryID;

	sDBRequest_SetCountry()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetCountry));
	}
	sDBRequest_SetCountry( SI32 personid, SI32 countryid )
	{
		packetHeader.usSize = sizeof(sDBRequest_SetCountry);
		packetHeader.usCmd	= DBMSG_REQUEST_SETCOUNTRY;

		siPersonID = personid;
		siCountryID = countryid;
	}
};

class sDBResponse_SetCountry
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;
	SI32				siCountryID;

	sDBResponse_SetCountry()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetCountry));
	}
};

class sDBRequest_SetShowCountry
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	bool				bShowCountry;

	sDBRequest_SetShowCountry()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetShowCountry));
	}
	sDBRequest_SetShowCountry( SI32 personid, bool showcountry )
	{
		packetHeader.usSize = sizeof(sDBRequest_SetShowCountry);
		packetHeader.usCmd	= DBMSG_REQUEST_SETSHOWCOUNTRY;

		siPersonID = personid;
		bShowCountry = showcountry;
	}
};

class sDBResponse_SetShowCountry
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;
	bool				bShowCountry;

	sDBResponse_SetShowCountry()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetShowCountry));
	}
};


class sDBRequest_SetShowPuchikomi
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	bool				bShowPuchikomi;

	sDBRequest_SetShowPuchikomi()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetShowPuchikomi));
	}
	sDBRequest_SetShowPuchikomi( SI32 personid, bool showpuchikomi )
	{
		packetHeader.usSize = sizeof(sDBRequest_SetShowPuchikomi);
		packetHeader.usCmd	= DBMSG_REQUEST_SETSHOWPUCHIKOMI;

		siPersonID = personid;
		bShowPuchikomi = showpuchikomi;
	}
};

class sDBResponse_SetShowPuchikomi
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;
	bool				bShowPuchikomi;

	sDBResponse_SetShowPuchikomi()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetShowPuchikomi));
	}
};

enum
{
	RPGIVE_REASON_FROMGM = 1
};
class sDBRequest_GiveFP
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siRecommendPoint;

	SI16				siReason;

	sDBRequest_GiveFP( SI32 personid, SI32	RecommendPoint, SI16 Reason )
	{
		packetHeader.usSize = sizeof(sDBRequest_GiveFP);
		packetHeader.usCmd	= DBMSG_REQUEST_GIVEFP;

		siPersonID = personid;
		siRecommendPoint = RecommendPoint;
		siReason = Reason;
	}
};

class sDBResponse_GiveFP
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siPersonID;

	SI32				siRecommendPoint;			// ���� ����Ʈ ������. 

	// PCK - �α׿� ��Ŷ �߰�
	SI16				siReason;

	sDBResponse_GiveFP()
	{
		ZeroMemory(this, sizeof(sDBResponse_GiveFP));
	}
};

class sDBRequest_AddBuf
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID; 

	SI16			siIndex;
	stBuf			m_stBuf;

	bool			bUseItem;
	SI16			siItemPos;		// �������� ����� ��ġ.
	cltItem			clItem;			// Person�� ����� ������ ����. 

	GMONEY			money;

	sDBRequest_AddBuf( SI32 personid, SI16 index, stBuf*  pbuf, bool useitem = false, SI16 itempos = 0, cltItem* pclitem = NULL, GMONEY _money = 0)
	{
		packetHeader.usSize = sizeof(sDBRequest_AddBuf);
		packetHeader.usCmd	= DBMSG_REQUEST_ADDBUF;

		siPersonID = personid;
		siIndex = index;
		m_stBuf.siBufType = pbuf->siBufType;
		m_stBuf.siPercent = pbuf->siPercent;
		//m_stBuf.siAdd = pbuf->siAdd;
		m_stBuf.siOverTime = pbuf->siOverTime;
		//m_stBuf.bOverlap = pbuf->bOverlap;

		m_stBuf.siGetType = pbuf->siGetType;

		bUseItem = useitem;
		siItemPos = itempos;
		if(pclitem)
		{
			clItem.Set(pclitem);
		}
		else
		{
			clItem.Init();
		}

		money = _money;
	}

};

class sDBResponse_AddBuf
{
public:
	sPacketHeader	packetHeader;
	
	SI32			siResult;
	SI32			siPersonID; 

	SI16			siIndex;

	stBuf			m_stBuf;

	bool			bUseItem;
	SI16			siItemPos;		// �������� ����� ��ġ.
	cltItem			clItem;			// Person�� ����� ������ ����. 
	cltItem			clUsedItem;			// ���� ������. 

	GMONEY			money;

	sDBResponse_AddBuf()
	{
		ZeroMemory( this, sizeof(sDBResponse_AddBuf) );
	}

};

class sDBRequest_DeleteBuf
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	SI16			siIndex;

	stBuf			m_stBuf;		// �����Ǵ� ������ ����	- For LOG

	sDBRequest_DeleteBuf( SI32 personid, SI16 index, stBuf* pBuf )
	//sDBRequest_DeleteBuf( SI32 personid, SI16 index)
	{
		packetHeader.usSize = sizeof(sDBRequest_AddBuf);
		packetHeader.usCmd	= DBMSG_REQUEST_DELETEBUF;

		siPersonID = personid;
		siIndex = index;

		m_stBuf.Set(pBuf);
	}
};

class sDBResponse_DeleteBuf
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siPersonID;
	SI16			siIndex;

	stBuf			m_stBuf;		// �����Ǵ� ������ ����	- For LOG

	sDBResponse_DeleteBuf()
	{
		ZeroMemory( this, sizeof(sDBResponse_DeleteBuf) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_SetTeacherPoint
//
// Last Modified 	: 2207 / 02 / 22
// Created		 	: �豤��
//
// Function			: [��û]���������� �����Ѵ�.
//
//***************************************************************************************************
class sDBRequest_SetTeacherPoint
{
public:
	sPacketHeader	packetHeader;

	// ���������� ������ ID
	SI32			siTeacherPersonID;
	// �������ų� ���� ����
	SI32			siAddPoint;

	sDBRequest_SetTeacherPoint( SI32 TeacherPersonID, SI32 AddPoint )
	{
		packetHeader.usSize = sizeof(sDBRequest_SetTeacherPoint);
		packetHeader.usCmd	= DBMSG_REQUEST_SETTEACHERPOINT;

		siTeacherPersonID = TeacherPersonID;
		siAddPoint = AddPoint;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_SetTeacherPoint
//
// Last Modified 	: 2207 / 02 / 22
// Created		 	: �豤��
//
// Function			: [����]���������� �����Ѵ�.(������ �������̸� Ŭ��� ���� �������ش�.)
//
//***************************************************************************************************
class sDBResponse_SetTeacherPoint
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siTeacherPersonID;
	SI32			siTotalTeacherPoint;

	sDBResponse_SetTeacherPoint()
	{
		ZeroMemory( this, sizeof(sDBResponse_SetTeacherPoint) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_GetItem_From_TeacherPoint
//
// Last Modified 	: 2207 / 02 / 22
// Created		 	: �豤��
//
// Function			: [��û]���������� �������� ��´�.
//
//***************************************************************************************************
class sDBRequest_GetItem_From_TeacherPoint
{
public:
	sPacketHeader	packetHeader;

	SI32			siCharID;
	// ���������� ������ ID
	SI32			siTeacherPersonID;
	// �������ų� ���� ����
	SI32			siAddPoint;

	sDBRequest_GetItem_From_TeacherPoint( SI32 CharID, SI32 TeacherPersonID, SI32 AddPoint )
	{
		packetHeader.usSize = sizeof(sDBRequest_GetItem_From_TeacherPoint);
		packetHeader.usCmd	= DBMSG_REQUEST_GETITEM_FROM_TEACHERPOINT;

		siCharID = CharID;
		siTeacherPersonID = TeacherPersonID;
		siAddPoint = AddPoint;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_GetItem_From_TeacherPoint
//
// Last Modified 	: 2207 / 02 / 22
// Created		 	: �豤��
//
// Function			: [����]���������� �������� ��´�.
//
//***************************************************************************************************
class sDBResponse_GetItem_From_TeacherPoint
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siCharID;
	SI32			siAddPoint;

	sDBResponse_GetItem_From_TeacherPoint()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetItem_From_TeacherPoint) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_RenouncePupil
//
// Last Modified 	: 2007 / 02 / 22
// Created		 	: 
//
// Function			: [��û]������ ���ڿ��� ���踦 ���´�.
//
//***************************************************************************************************
class sDBRequest_RenouncePupil
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPupilPersonID;
	
	sDBRequest_RenouncePupil( SI32 CharID, SI32 PupilPersonID )
	{
		packetHeader.usSize = sizeof( sDBRequest_RenouncePupil );
		packetHeader.usCmd	= DBMSG_REQUEST_RENOUNCEPUPIL;

		siCharID		= CharID;
		siPupilPersonID	= PupilPersonID;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_RenouncePupil
//
// Last Modified 	: 2207 / 02 / 22
// Created		 	: �豤��
//
// Function			: [����]������ ���ڿ��� ���踦 ���´�.
//
//***************************************************************************************************
class sDBResponse_RenouncePupil
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siCharID;
	SI32			siPupilPersonID;

	sDBResponse_RenouncePupil()
	{
		ZeroMemory( this, sizeof(sDBResponse_RenouncePupil) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_OverTakeTeacherLevel
//
// Last Modified 	: 2207 / 02 / 27
// Created		 	: �豤��
//
// Function			: [��û]���ڰ� ���·����� ������Ҵ°�?
//
//***************************************************************************************************
class sDBRequest_OverTakeTeacherLevel
{
public:
	sPacketHeader	packetHeader;

	SI32			siCharID;
	// ���� �� ���� PersonID
	SI32			siTeacherPersonID;
	// ������ �� ���� ����
	SI32			siMyLevel;
	// ���� Person|D
	SI32			siPupilPersonID;

	sDBRequest_OverTakeTeacherLevel( SI32 CharID, SI32 TeacherPersonID, SI32 MyLevel, SI32 PupilPersonID )
	{
		packetHeader.usSize = sizeof(sDBRequest_OverTakeTeacherLevel);
		packetHeader.usCmd	= DBMSG_REQUEST_OVERTAKETEACHERLEVEL;

		siCharID = CharID;
		siTeacherPersonID = TeacherPersonID;
		siMyLevel = MyLevel;
		siPupilPersonID = PupilPersonID;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_OverTakeTeacherLevel
//
// Last Modified 	: 2207 / 02 / 27
// Created		 	: �豤��
//
// Function			: [����]���ڰ� ���·����� ������Ҵ°�?
//
//***************************************************************************************************
class sDBResponse_OverTakeTeacherLevel
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			siCharID;
	TCHAR			szTeacherName[MAX_PLAYER_NAME];

	sDBResponse_OverTakeTeacherLevel()
	{
		ZeroMemory( this, sizeof(sDBResponse_OverTakeTeacherLevel) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_PVPResult
//
// Last Modified 	: 2007 / 06 / 25
// Created		 	: �豤��
//
// Function			: [��û]PVP����� DB�� ������.
//
//***************************************************************************************************
class sDBRequest_PVPResult
{
public:
	sPacketHeader	packetHeader;

	SI32			siWinCharID;
	SI32			siLoseCharID;

	SI32			siWinPersonID;
	SI32			siLosePersonID;

	TCHAR			szWinUserName[MAX_PLAYER_NAME];
	TCHAR			szLoseUserName[MAX_PLAYER_NAME];

	sDBRequest_PVPResult( SI32 WinCharID, SI32 LoseCharID, SI32 WinPersonID, SI32 LosePersonID,
		                  TCHAR* WinUserName, TCHAR* LoseUserName )
	{
		packetHeader.usSize = sizeof(sDBRequest_PVPResult);
		packetHeader.usCmd	= DBMSG_REQUEST_PVPRESULT;

		siWinCharID = WinCharID;
		siLoseCharID = LoseCharID;

		siWinPersonID = WinPersonID;
		siLosePersonID = LosePersonID;

		MStrCpy( szWinUserName, WinUserName, MAX_PLAYER_NAME );
		MStrCpy( szLoseUserName, LoseUserName, MAX_PLAYER_NAME );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_PVPResult
//
// Last Modified 	: 2007 / 06 / 25
// Created		 	: �豤��
//
// Function			: [����]PVP����� �޴´�.
//
//***************************************************************************************************
class sDBResponse_PVPResult
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;

	SI32			siWinCharID;
	TCHAR			szPVPWinHighLevelUserName[MAX_PLAYER_NAME];

	SI32			siLoseCharID;

	TCHAR			szWinUserName[MAX_PLAYER_NAME];
	TCHAR			szLoseUserName[MAX_PLAYER_NAME];

	sDBResponse_PVPResult()
	{
		ZeroMemory( this, sizeof(sDBResponse_PVPResult) );
	}
};

//--------------------------------------------------------
// �����Ǿ��� ������ ���� ������ �ֵ��� ����
//--------------------------------------------------------
#define GIVEREWARD_ACCOUNT	1
#define GIVEREWARD_SERVER	2
#define GIVEREWARD_CHAR		3


class sDBRequest_SystemRewardList
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			usCharID;
	SYSTEMTIME		servertime;
	SI32			m_siCurPage;

	sDBRequest_SystemRewardList( SI32 PersonID, UI16 CharID, SYSTEMTIME ServerTime, SI32 siCurPage )
	{
		packetHeader.usSize = sizeof(sDBRequest_SystemRewardList);
		packetHeader.usCmd	= DBMSG_REQUEST_SYSTEMREWARDLIST;

		siPersonID = PersonID;
		usCharID = CharID;
		servertime = ServerTime;
		m_siCurPage = siCurPage;
	}		
};

class sDBResponse_SystemRewardList
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;

	SI32			siPersonID;
	UI16			usCharID;

	SI32			m_siCurPage;
	SI32			m_siMaxPage;

	cltSystemRewardInfo	clInfo[MAX_SYSTEMREWARD_LIST];


	sDBResponse_SystemRewardList()
	{
		ZeroMemory( this, sizeof(sDBResponse_SystemRewardList) );
	}
};

class sDBRequest_RecieveSystemReward
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			usCharID;

	SI32			siIndex;

	SI16			siItemPos;
	bool			bPileSwitch;	// ��ø ��� ����. 	
	bool			bCreateSID;		// SID ���� ����

	sDBRequest_RecieveSystemReward( SI32 PersonID, UI16 CharID, SI32 Index, SI32 ItemPos, bool PileSwitch, bool CreateSID )
	{
		packetHeader.usSize = sizeof(sDBRequest_RecieveSystemReward);
		packetHeader.usCmd	= DBMSG_REQUEST_RECIEVESYSTEMREWARD;

		siPersonID = PersonID;
		usCharID = CharID;
		siIndex = Index;
		siItemPos = ItemPos;
		bPileSwitch = PileSwitch;
		bCreateSID = CreateSID;
	}
};

class sDBResponse_RecieveSystemReward
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;

	SI32			siPersonID;
	UI16			usCharID;

	cltSystemRewardInfo	clInfo;

	SI16			siItemPos;			// ���� �������� �κ��丮�� ��ġ
	cltItem			clItem;				// ���� ������ ����

	GMONEY			siMoney;			// ���� �Ŀ� ��ȭ�� ��

	sDBResponse_RecieveSystemReward()
	{
		ZeroMemory( this, sizeof(sDBResponse_RecieveSystemReward) );
	}
};

class sDBRequest_GiveSystemReward
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			usCharID;
	SI32			siType;	// GIVEREWARD_ACCOUNT, GIVEREWARD_SERVER, GIVEREWARD_CHAR
	cltSystemRewardInfo	clInfo;


	sDBRequest_GiveSystemReward( SI32 RewardType, SI32 PersonID, UI16 CharID, cltSystemRewardInfo* pclinfo )
	{
		packetHeader.usSize = sizeof(sDBRequest_GiveSystemReward);
		packetHeader.usCmd	= DBMSG_REQUEST_GIVESYSTEMREWARD;

		siPersonID = PersonID;
		usCharID = CharID;
		siType = RewardType;

		clInfo.Set( pclinfo );
	}
};

class sDBResponse_GiveSystemReward
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;

	SI32			siPersonID;
	UI16			usCharID;

	cltSystemRewardInfo	clInfo;

	sDBResponse_GiveSystemReward()
	{
		ZeroMemory( this, sizeof(sDBResponse_GiveSystemReward) );
	}
};

// �⼮ üũ �ϱ�
class sDBRequest_Attend
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			usCharID;

	NDate			clEventStartDay;
	NDate			clEventEndDay;

	SI08			siType;

	sDBRequest_Attend( SI32 PersonID, UI16 CharID, 
						NDate* pclStartDay, NDate* pclEndDay, SI08 siAttendType )
	{
		packetHeader.usSize = sizeof(sDBRequest_Attend);
		packetHeader.usCmd	= DBMSG_REQUEST_ATTEND;

		siPersonID = PersonID;
		usCharID = CharID;

		clEventStartDay.Set( pclStartDay );
		clEventEndDay.Set( pclEndDay );

		siType = siAttendType;
	}
};

class sDBResponse_Attend
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			usCharID;

	SI32			siResult;
	SI32			siAttendanceDay;		// �� �⼮�ϼ�

	SI32			siRewardDay;			// �� ������� �ϼ�

	SI08			siType;					// �̺�Ʈ Ÿ�� 1=�⼮, 2=PC�����Ŭ�ι�����, 3=����2�⼮�̺�Ʈ

	sDBResponse_Attend()
	{
		ZeroMemory( this, sizeof(sDBResponse_Attend) );
	}
};

// [����] ���� ��¥�� �⼮�� �ߴٰ� ������
class sDBRequest_SetAttend
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			uiCharID;

	NDate			kAttendDay;	// �⼮�ϴ� ��¥
	
	SI08			siType;		// �⼮ Ÿ��(ATTEND_EVENTTYPE ���� �ϳ� ����)

	sDBRequest_SetAttend( SI32 PersonID, UI16 CharID, NDate* pkAttendDay,  SI08 siAttendType )
	{
		packetHeader.usSize		= sizeof(sDBRequest_SetAttend);
		packetHeader.usCmd		= DBMSG_REQUEST_SETATTEND;

		siPersonID				= PersonID;
		uiCharID				= CharID;

		kAttendDay.Set( pkAttendDay );
		
		siType					= siAttendType;
	}
};

class sDBResponse_SetAttend
{
public:
	sPacketHeader	packetHeader;

	SI32			siPersonID;
	UI16			uiCharID;

	SI32			siResult;

	SI08			siType;					// �̺�Ʈ Ÿ�� 1=�⼮, 2=PC�����Ŭ�ι�����, 3=����2�⼮�̺�Ʈ

	sDBResponse_SetAttend()
	{
		ZeroMemory( this, sizeof(sDBResponse_SetAttend) );
	}
};
//KHY - 0906 -�ش������ �ش��̺�Ʈ Ÿ�Կ� ���� ������ �߱޿��θ� ��û�Ѵ�.
/*
class sDBRequest_GetEventCouponInfo
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siEventType;

	sDBRequest_GetEventCouponInfo( SI32 personid, SI32 evettype)
	{
		packetHeader.usSize = sizeof(sDBRequest_GetEventCouponInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETEVENTCOUPONINFO;

		siPersonID = personid;
		siEventType = evettype;
	}
};
*/
class sDBResponse_GetEventCouponInfo
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siEventType;
//	SI32 siEventCount;
	SI32	siResult; // 0 = ����. 1 = ����.


	//NOW_COM_EVENT (6) 	:   siResult = 1  //�ű� ĳ���� ù ����. - ����.
	//						    siResult = 2  //10���� �޼� �̺�Ʈ Ŭ����. - ����.
	//						    siResult = 3  //������ ������. = ���ڰ� �Ǿ���. - ����.
	// siPara ���� �״�� ������ �ּ���.

	sDBResponse_GetEventCouponInfo()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetEventCouponInfo) );		
	}
};

class sDBResponse_GetAUCTIONEventCouponInfo
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siEventType;
	//	SI32 siEventCount;
	SI32	siResult; // 0 = ����. 1 ~6���� ��������.

	sDBResponse_GetAUCTIONEventCouponInfo()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetAUCTIONEventCouponInfo) );		
	}
};
////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------
// class : sDBRequest_TimeMeterRate_AddTime
// desc  : ������ �ý����� ���ð��� �����Ѵ�.
//-----------------------------------------------------------
class sDBRequest_TimeMeterRate_AddTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI16				siTimeMeterRateType;
	SI32				siAddTime;

	cltItem				clItem;
	SI16				siItemPos;

	sDBRequest_TimeMeterRate_AddTime(UI16 charid, SI32 personid, SI16 timemeterratetype, SI32 addtime ,cltItem* pclItem, SI16 itempos)
	{
		packetHeader.usSize = sizeof( sDBRequest_TimeMeterRate_AddTime );
		packetHeader.usCmd	= DBMSG_REQUEST_TIMEMETERRATE_ADDTIME;

		uiCharID		= charid;
		siPersonID		= personid;

		siTimeMeterRateType = timemeterratetype;
		siAddTime			= addtime;

		if(pclItem)		clItem.Set(pclItem);
		siItemPos		= itempos;
	}
};

class sDBResponse_TimeMeterRate_AddTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI32				siResult;

	SI32				siLeftTime;

	cltItem				clLeftItem;		// �κ��丮 ����

	SI16				siTimeMeterRateType;	// For Log
	SI32				siAddTime;				// For Log

	cltItem				clItem; // For Log
	SI16				siItemPos; // For Log

	sDBResponse_TimeMeterRate_AddTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_TimeMeterRate_AddTime));
	}
};

//-----------------------------------------------------------
// class : sDBRequest_TimeMeterRate_AddTime
// desc  : ������ �ý����� ���ð��� �����Ѵ�.
//-----------------------------------------------------------
class sDBRequest_TimeMeterRate_UseTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI16				siTimeMeterRateType;
	SI32				siUseTime;
	bool				bUpdate;		// DB������ ������ ������ ���ΰ�?

	sDBRequest_TimeMeterRate_UseTime(UI16 charid, SI32 personid, SI16 timemeterratetype, SI32 usetime, bool update )
	{
		packetHeader.usSize = sizeof( sDBRequest_TimeMeterRate_UseTime );
		packetHeader.usCmd	= DBMSG_REQUEST_TIMEMETERRATE_USETIME;

		uiCharID		= charid;
		siPersonID		= personid;

		siTimeMeterRateType = timemeterratetype;
		siUseTime			= usetime;
		bUpdate				= update;
	}
};

class sDBResponse_TimeMeterRate_UseTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI32				siResult;

	SI32				siLeftTime;

	SI16				siTimeMeterRateType;// For Log
	SI32				siUseTime;			// For Log
	bool				bUpdate;			// DB������ ������ ������ ���ΰ�?

	sDBResponse_TimeMeterRate_UseTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_TimeMeterRate_UseTime));
	}
};

//-----------------------------------------------------------
// class : sDBRequest_Transform_AddChar
// desc  : ���Ű��� ĳ���͸� ����Ѵ�.
//-----------------------------------------------------------
class sDBRequest_Transform_AddChar
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI16				siCharKind;

	cltItem				clItem;
	SI16				siItemPos;

	SI16				siTimeMeterRateType; // �ð� ���� Ÿ��. - TIMEMETERRATE_TRANSFORM  �� �����̴�.
	SI32				siAddTime; 			  // 3�ð�  - 10800�� �����̴�.

	sDBRequest_Transform_AddChar(UI16 charid, SI32 personid, SI16 charkind, cltItem* pclItem, SI16 itempos,
											SI16	 TimeMeterRateType, SI32 AddTime)
	{
		packetHeader.usSize = sizeof( sDBRequest_Transform_AddChar );
		packetHeader.usCmd	= DBMSG_REQUEST_TRANSFORM_ADDCHAR;

		uiCharID		= charid;
		siPersonID		= personid;

		siCharKind		= charkind;

		if(pclItem)		clItem.Set(pclItem);
		siItemPos		= itempos;

		siTimeMeterRateType = TimeMeterRateType;
		siAddTime = AddTime;
	}
};


class sDBResponse_Transform_AddChar
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI32				siResult;

	cltItem				clLeftItem;		// �κ��丮 ����

	SI16				siCharKind;		
	cltItem				clItem;			// For Log
	SI16				siItemPos;		// For Log

	SI16				siTimeMeterRateType;
	SI32				siAddTime;
	
	sDBResponse_Transform_AddChar()
	{
		ZeroMemory(this, sizeof(sDBResponse_Transform_AddChar));
	}
};

//-----------------------------------------------------------
// class : sDBRequest_TimeMeterRate_AddTime
// desc  : ���� ĳ���� ���ð��� ������Ų��.
//-----------------------------------------------------------
class sDBRequest_Transform_AddTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI16				siCharKind;
	SI32				siAddTime;

	sDBRequest_Transform_AddTime(UI16 charid, SI32 personid, SI16 charkind, SI32 addtime)
	{
		packetHeader.usSize = sizeof( sDBRequest_Transform_AddTime );
		packetHeader.usCmd	= DBMSG_REQUEST_TRANSFORM_ADDTIME;

		uiCharID		= charid;
		siPersonID		= personid;

		siCharKind		= charkind;
		siAddTime		= addtime;
	}
};

class sDBResponse_Transform_AddTime
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI32				siResult;

	SI16				siCharKind;
	SI32				siTotalTime;

	SI32				siAddTime;		// For Log

	sDBResponse_Transform_AddTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_Transform_AddTime));
	}
};

//-----------------------------------------------------------
// class : sDBRequest_SetTransForm
// desc  : ���� ���� ���
//-----------------------------------------------------------
//KHY - 1220 - ���Žý���.
class sDBRequest_TransForm_Set
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	UI16 	uiNowTransFormKind;	// ������(Ȥ�� ����)�������� ĳ������ ����.
	bool 	bTransFormMode;		// ���� ���� ����. - True = ����

	sDBRequest_TransForm_Set(UI16 charid, SI32 personid, UI16 NowTransFormKind, bool TransFormMode)
	{
		packetHeader.usSize = sizeof( sDBRequest_TransForm_Set );
		packetHeader.usCmd	= DBMSG_REQUEST_TRANSFORM_SET;

		uiCharID   = charid;
		siPersonID = personid;

		uiNowTransFormKind = NowTransFormKind;
		bTransFormMode = TransFormMode;
	}
};

class sDBResponse_TransForm_Set
{
public:
	sPacketHeader		packetHeader;

	UI16				uiCharID;
	SI32				siPersonID;

	SI32				siResult;

	sDBResponse_TransForm_Set()
	{
		ZeroMemory(this, sizeof(sDBResponse_TransForm_Set));
	}
};
// �ɸ��� �ɼ�
class sDBRequest_Char_Option
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;						// �ʱ�ȭ  �����. 

	cltPCharOptionInfo		clPCharOptioninfo;

	sDBRequest_Char_Option()
	{
		ZeroMemory(this, sizeof(sDBRequest_Char_Option));
	}

	sDBRequest_Char_Option(UI16 charid, SI32 personid, cltPCharOptionInfo CharOptioninfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_Char_Option );
		packetHeader.usCmd	= DBMSG_REQUEST_CHAR_OPTION;
		usCharID = charid ;
		siPersonID = personid ;


		clPCharOptioninfo.Set(&CharOptioninfo);
	}
};

class sDBResponse_Char_Option
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;		// �����.
	UI16				usCharID;
	SI32				siPersonID;		// �����. 

	cltPCharOptionInfo		clPCharOptioninfo;

	sDBResponse_Char_Option()
	{
		ZeroMemory(this, sizeof(sDBResponse_Char_Option));
	}
};
// ���� �ɼ� ������ ��û�Ѵ�.
class sDBRequest_Char_Get_Option
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
	SI08				siLogin;		// 1: �α���, 0: ��Ÿ


	sDBRequest_Char_Get_Option( SI32 CharID, SI32 PersonID, SI08 Login )
	{
		packetHeader.usSize = sizeof( sDBRequest_Char_Get_Option );
		packetHeader.usCmd	= DBMSG_REQUEST_CHAR_GET_OPTION;

		siCharID	= CharID;
		siPersonID	= PersonID;

		siLogin		= Login;
	}
};
// ���� �ɼ� ������ �����Ѵ�.
class sDBResponse_Char_Get_Option
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;		// �����.
	SI32				siCharID;		
	SI32				siPersonID;

	cltPCharOptionInfo		clPCharOptioninfo;

	sDBResponse_Char_Get_Option()
	{
		ZeroMemory( this,sizeof( sDBResponse_Char_Get_Option ) );
	}
};

class sDBRequest_Question_Daily_Count_Set
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;		
	SI32				m_siPersonID;			

	UI08				m_DailyCount;

	sDBRequest_Question_Daily_Count_Set( SI32 _siCharID, SI32 _siPersonID, UI08 _DailyCount )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Question_Daily_Count_Set );
		m_packetHeader.usCmd	= DBMSG_REQUEST_QUESTION_DAILY_COUNT_SET;
		
		m_siCharID		= _siCharID;	
		m_siPersonID	= _siPersonID;
		m_DailyCount	= _DailyCount;
	}
};

class sDBResponse_Question_Daily_Count_Set
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;		
	SI32				m_siPersonID;			

	UI08				m_DailyCount;

	sDBResponse_Question_Daily_Count_Set( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

class sDBRequest_Question_Daily_Count_Get
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;		
	SI32				m_siPersonID;			

	sDBRequest_Question_Daily_Count_Get(  SI32 _siCharID, SI32 _siPersonID )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Question_Daily_Count_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_QUESTION_DAILY_COUNT_GET;

		m_siCharID		= _siCharID;	
		m_siPersonID	= _siPersonID;
	}
};

class sDBResponse_Question_Daily_Count_Get
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;		
	SI32				m_siPersonID;			

	UI08				m_DailyCount;

	sDBResponse_Question_Daily_Count_Get( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] 
class sDBRequest_Question_Daily_Count_Del
{
public:
	sPacketHeader		m_packetHeader;
	
	sDBRequest_Question_Daily_Count_Del( void )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Question_Daily_Count_Del );
		m_packetHeader.usCmd	= DBMSG_REQUEST_QUESTION_DAILY_COUNT_DEL;
	}
};

//[����] ����� ���� ���. 
class sDBResponse_Question_Daily_Count_Del
{
public:
	sPacketHeader		m_packetHeader;
	
	sDBResponse_Question_Daily_Count_Del( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};
//--------------------------------------------------
// �߷�Ÿ�� ���� ������ ���� ������ �־�� �ϴ� ����
//--------------------------------------------------
class sDBRequest_Valantine_Info_Get
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	sDBRequest_Valantine_Info_Get( )
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Info_Get) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Valantine_Info_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_VALANTINE_INFO_GET;
	}

	sDBRequest_Valantine_Info_Get( SI32 siPersonID )
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Info_Get) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Valantine_Info_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_VALANTINE_INFO_GET;

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_Valantine_Info_Get
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;
	cltValentineWarInfo	m_clValantineWarInfo;

	sDBResponse_Valantine_Info_Get( )
	{
		ZeroMemory( this, sizeof(sDBResponse_Valantine_Info_Get) );
	}
};
//// �̻��
//enum ValentineWarStatus
//{
//	VALENTINEWAR_NONE	= 0,
//	VALENTINEWAR_COUPLE,
//	VALENTINEWAR_SOLO
//};
//--------------------------------------------------
// �߷�Ÿ�� ���� ���� �ַ����� Ŀ������ �����Ѱ��� ������ ���� �Ѵ�.
//--------------------------------------------------
class sDBRequest_Valantine_Request
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;
	cltValentineWarInfo clValentineWarInfo;


	sDBRequest_Valantine_Request( )
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Request) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Valantine_Request );
		m_packetHeader.usCmd	= DBMSG_REQUEST_VALANTINE_REQUEST;
	}

	sDBRequest_Valantine_Request( SI32 siPersonID, cltValentineWarInfo ValentineWarinfo)
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Request) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Valantine_Request );
		m_packetHeader.usCmd	= DBMSG_REQUEST_VALANTINE_REQUEST;

		m_siPersonID			= siPersonID	;
		clValentineWarInfo	= ValentineWarinfo;
	}
};

class sDBResponse_Valantine_Request
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;
	SI32				m_siPersonID;
	cltValentineWarInfo clValentineWarInfo;


	sDBResponse_Valantine_Request( )
	{
		ZeroMemory( this, sizeof(sDBResponse_Valantine_Request) );
	}
};
// ������ ���� ��ǰ�� �޾Ҵ�.
class sDBRequest_Valantine_Get_Prize
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;
	bool			bGetPrize	;
	
	sDBRequest_Valantine_Get_Prize( )
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Get_Prize) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Valantine_Get_Prize );
		m_packetHeader.usCmd	= DBMSG_REQUEST_VALANTINE_GET_PRIZE;
	}

	sDBRequest_Valantine_Get_Prize( SI32 siPersonID, bool Getprize)
	{
		ZeroMemory( this, sizeof(sDBRequest_Valantine_Get_Prize) );

		m_packetHeader.usSize	=	sizeof( sDBRequest_Valantine_Get_Prize );
		m_packetHeader.usCmd	=	DBMSG_REQUEST_VALANTINE_GET_PRIZE;
		m_siPersonID			=	siPersonID	;
		bGetPrize				=	Getprize	;
	}
};

class sDBResponse_Valantine_Get_Prize
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID	;
	SI32				siResule		;
	bool				bGetPrize	;

	sDBResponse_Valantine_Get_Prize( )
	{
		ZeroMemory( this, sizeof(sDBResponse_Valantine_Get_Prize) );
	}
};


// [����] �ڵ��� ���� Ȯ��.
class sDBRequest_Get_Cellular_Phone_Auth
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;
	SI32			m_siCharID;		

	sDBRequest_Get_Cellular_Phone_Auth( SI32 _siCharID, SI32 _siPersonID )
	{
		ZeroMemory( this, sizeof( sDBRequest_Get_Cellular_Phone_Auth ) );

		m_packetHeader.usSize = sizeof(sDBRequest_Get_Cellular_Phone_Auth);
		m_packetHeader.usCmd  = DBMSG_REQUEST_CELLULAR_PHONE_AUTH;
		
		m_siCharID			  = _siCharID;	
		m_siPersonID		  = _siPersonID;
	}
};

class sDBResponse_Get_Cellular_Phone_Auth
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	SI32			m_siPersonID;
	SI32			m_siCharID;		
	
	bool			m_bIsCellularPhoneAuth;
	SI32			m_siRecommendPersonID;
	TCHAR			m_szRecommendPersonName[MAX_PLAYER_NAME];
	bool			m_bFirstCharCreate;
	
	sDBResponse_Get_Cellular_Phone_Auth()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

// [����] ��ȥ�� �Ѵ�
class sDBRequest_Set_Marry
{
public:
	sPacketHeader	m_packetHeader;

	// ûȥ�ѻ��
	SI32			m_siSourcePersonID;
	SI16			m_siSourceItemPos;
	cltItem			m_clSourceItem;
	// ûȥ ���� ���
	SI32			m_siDestPersonID;
	SI16			m_siDestItemPos;
	cltItem			m_clDestItem;
		
	// ������
	SI16			m_siLoveLevel;
	// ��ȥ��
	SI32			m_siWeddingDateVary;

	sDBRequest_Set_Marry( 
		SI32 siSourcePersonID,	cltItem*	pclSourceItem,		SI16 siSourceItemPos,
		SI32 siDestPersonID,	cltItem*	pclDestItem,		SI16 siDestItemPos,
		SI16 siLoveLevel,		SI32		siWeddingDateVary
	)
	{
		// �ʱ�ȭ
		ZeroMemory( this, sizeof(sDBRequest_Set_Marry) );

		// ��Ŷ ����
		m_packetHeader.usSize	= sizeof(sDBRequest_Set_Marry);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SET_MARRY;

		// ���� ������ ����
		m_siSourcePersonID		= siSourcePersonID;
		if ( pclSourceItem )
		{
			m_siSourceItemPos	= siSourceItemPos;
			m_clSourceItem.Set( pclSourceItem );
		}

		m_siDestPersonID		= siDestPersonID;
		if ( pclDestItem )
		{
			m_siDestItemPos		= siDestItemPos;
			m_clDestItem.Set( pclDestItem );
		}
		m_siLoveLevel			= siLoveLevel;

		m_siWeddingDateVary		= siWeddingDateVary;	
	}
};

// [����] ��ȥ�� �Ѵ� ����
class sDBResponse_Set_Marry
{
public:
	sPacketHeader	m_packetHeader;

	// ���
	SI32			m_siResult;

	// ûȥ�ѻ��
	SI32			m_siSourcePersonID;
	TCHAR			m_szSourceName[MAX_PLAYER_NAME];
	SI16			m_siSourceItemPos;
	cltItem			m_clSourceItem;

	// ûȥ ���� ���
	SI32			m_siDestPersonID;
	TCHAR			m_szDestName[MAX_PLAYER_NAME];
	SI16			m_siDestItemPos;
	cltItem			m_clDestItem;

	// ������
	SI16			m_siLoveLevel;

	// ��ȥ��
	SI32			m_siWeddingDateVary;	// (���ַ�)

	sDBResponse_Set_Marry( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Set_Marry) );
	}
};	// DBMSG_RESPONSE_SET_MARRY

// [����] ��ȥ ������ ��û�Ѵ�
class sDBRequest_Get_Marry_Info
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;	// ��û�� ���

	sDBRequest_Get_Marry_Info( SI32 siPersonID )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_GET_MARRY_INFO;
		m_packetHeader.usSize	= sizeof( sDBRequest_Get_Marry_Info );

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_Get_Marry_Info
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;			// ��û�� ���

	SI32			m_siMatePersonID;		// ����� PersonID
	TCHAR			m_szMateName[MAX_PLAYER_NAME];

	SI32			m_siWeddingDateVary;	// ��ȥ�����(���ַ�)
	SI32			m_siItemGetDateVary;	// ��ȥ����� ������ ���� ��(���ַ�)

	SI32			m_siLimitDateVary;		// ������ ������ ������ �ð�(���ַ�)
	SI32			m_siUseDateVary;		// ������ ������ ����� �ð�(���ַ�)
	SI16			m_siLoveLevel;			// ���� ������

	sDBResponse_Get_Marry_Info( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Get_Marry_Info) );
	}

};	// DBMSG_RESPONSE_GET_MARRY_INFO

// [����] ��ȥ����� ������ ���� �� ���� ��û
class sDBRequest_Marry_ItemGet_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;			// ��û�� ���
	SI32			m_siItemGetDateVary;	// ������ ���� ��(���ַ�)

	sDBRequest_Marry_ItemGet_Set( SI32 siPersonID, SI32 siItemGetDateVary )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_MARRY_ITEMGET_SET;
		m_packetHeader.usSize	= sizeof( sDBRequest_Marry_ItemGet_Set );

		m_siPersonID			= siPersonID;		
		m_siItemGetDateVary		= siItemGetDateVary;
	}
};

class sDBResponse_Marry_ItemGet_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;			// ��û�� ���
	SI32			m_siItemGetDateVary;	// ������ ���� ��(���ַ�)

	sDBResponse_Marry_ItemGet_Set( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Marry_ItemGet_Set) );
	}
};	// DBMSG_RESPONSE_MARRY_ITEMGET_SET

// [����] ��ȥ ������ ���� ����
class sDBRequest_Marry_Love_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;		// ��û�� ���

	SI32			m_siUseHourVary;	// ����� �ð�
	SI32			m_siLimitHourVary;	// ���ѽð�

	SI16			m_siLoveLevel;		// ������

	sDBRequest_Marry_Love_Set( SI32 siPersonID, SI32 siUseHourVary, SI32 siLimitHourVary, SI16 siLoveLevel )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_MARRY_LOVE_SET;
		m_packetHeader.usSize	= sizeof(sDBRequest_Marry_Love_Set);

		m_siPersonID			= siPersonID;		

		m_siUseHourVary			= siUseHourVary;	
		m_siLimitHourVary		= siLimitHourVary;	

		m_siLoveLevel			= siLoveLevel;		
	}
};

class sDBResponse_Marry_Love_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;		// ��û�� ���

	SI32			m_siUseHourVary;	// ����� �ð�
	SI32			m_siLimitHourVary;	// ���ѽð�

	SI16			m_siLoveLevel;		// ������

	sDBResponse_Marry_Love_Set( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Marry_Love_Set) );
	}
};
// [����] ���� ������ ��û�Ѵ�.
class sDBRequest_Get_FamilyInfo
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;	// ��û�� ���

	sDBRequest_Get_FamilyInfo( SI32 siPersonID )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_GET_FAMILYINFO;
		m_packetHeader.usSize	= sizeof( sDBRequest_Get_FamilyInfo );

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_Get_FamilyInfo
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;			// ��û�� ���
	CFamily			m_cFamily	;			// ���� ���� ����
	sDBResponse_Get_FamilyInfo( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Get_FamilyInfo) );
	}

};
// [����] ��Ű ���
class sDBRequest_Set_My_CookeEffect
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID		;	// ��û�� ���
	SI32			m_siEndDateVary		;	// ��Ű ��� ���� �ð�
	SI32			m_siUseLimitDateVary;	// ��Ű������ѽð�
	SI32			m_siCookieLevel		;	// ��û�� ���

	sDBRequest_Set_My_CookeEffect( SI32 siPersonID, SI32 siEndDateVary, SI32 siUseLimitDateVary,SI32 siCookieLevel )
	{

		m_packetHeader.usCmd	= DBMSG_REQUEST_FAMILY_SET_COOKIE_EFFECT;
		m_packetHeader.usSize	= sizeof( sDBRequest_Set_My_CookeEffect );

		m_siPersonID			=	siPersonID;
		m_siEndDateVary			=	siEndDateVary;
		m_siUseLimitDateVary	=	siUseLimitDateVary;
		m_siCookieLevel			=	siCookieLevel;
	}
};

class sDBResponse_Set_My_CookeEffect
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;			// ��û�� ���
	CFamily			m_cFamily	;			// ���� ���� ����
	sDBResponse_Set_My_CookeEffect( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_Set_My_CookeEffect) );
	}
};

//[����] ĳ���� �����ҿ��� ĳ���͸� �����´�
class sDBRequest_PersonSlotNumChange
{
public:
	sPacketHeader	m_packetHeader;
	UI16			m_uiCharID;

	SI08			m_siFromIndex;	// ���⿡��(��ȿ������ 3~14)
	SI08			m_siToIndex;	// ����� �̵�(��ȿ������ 0~2)

	SI32			m_siPersonID;

	sDBRequest_PersonSlotNumChange( UI16 uiCharID, SI08 siFromIndex, SI08 siToIndex, SI32 siPersonID )
	{
		
		m_packetHeader.usCmd	= DBMSG_REQUEST_PERSONSLOTNUMCHANGE;
		m_packetHeader.usSize	= sizeof( sDBRequest_PersonSlotNumChange );

		m_uiCharID				= uiCharID;

		m_siFromIndex			= siFromIndex;
		m_siToIndex				= siToIndex;

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_PersonSlotNumChange
{
public:
	sPacketHeader	m_packetHeader;
	UI16			m_uiCharID;

	SI32			m_siResult;

	sDBResponse_PersonSlotNumChange( void )
	{
		ZeroMemory( this, sizeof(sDBResponse_PersonSlotNumChange) );
	}
};


//[����] ��ų�� ���� �߰�.
class sDBRequest_SkillBook_MagicInfo_Get
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;	

	sDBRequest_SkillBook_MagicInfo_Get( UI16 _usCharID, SI32 _siPersonID )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_SKILLBOOK_MAGICINFO_GET;
		m_packetHeader.usSize	= sizeof(sDBRequest_SkillBook_MagicInfo_Get);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;
	}

	~sDBRequest_SkillBook_MagicInfo_Get()
	{

	}
};

//[����] ��ų�� ���� �߰�.
class sDBResponse_SkillBook_MagicInfo_Get
{
public:
	sPacketHeader			m_packetHeader;
	SI32					m_siResult;			// �����.
	UI16					m_usCharID;
	SI32					m_siPersonID;	

	SI08					m_iIndex[SKILLBOOK_MAGIC_NUM];
	cltSkillBookMagic		m_clAddSkillBookMagic[SKILLBOOK_MAGIC_NUM];
	cltSkillBookSubMagic	m_clAddSkillBookSubMagic[MAX_SKILLBOOK_SUBMAGIC_NUM];

	sDBResponse_SkillBook_MagicInfo_Get( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};


//[����] ��ų�� ���� �߰�.
class sDBRequest_SkillBook_Magic_Add
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;				

	SI08				m_iIndex;
	cltSkillBookMagic	m_clAddSkillBookMagic;

	sDBRequest_SkillBook_Magic_Add( UI16 _usCharID, SI32 _siPersonID, SI08 _iIndex, cltSkillBookMagic* _pclAddSkillBookMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_SKILLBOOK_MAGIC_ADD;
		m_packetHeader.usSize	= sizeof(sDBRequest_SkillBook_Magic_Add);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;

		m_iIndex				= _iIndex;
		memcpy( &m_clAddSkillBookMagic, _pclAddSkillBookMagic, sizeof(m_clAddSkillBookMagic) );
	}
};

class sDBResponse_SkillBook_Magic_Add
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;			// �����.

	UI16				m_usCharID;
	SI32				m_siPersonID;				

	SI08				m_iIndex;
	cltSkillBookMagic	m_clAddSkillBookMagic;

	sDBResponse_SkillBook_Magic_Add( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ��ų�� ����.
class sDBRequest_SkillBook_Magic_Del
{
public:
	sPacketHeader			m_packetHeader;
	UI16					m_usCharID;
	SI32					m_siPersonID;				
	
	SI08					m_iIndex;
	cltSkillBookMagic		m_clAddSkillBookMagic;

	sDBRequest_SkillBook_Magic_Del( UI16 _usCharID, SI32 _siPersonID, SI08 _iIndex, cltSkillBookMagic* _pclAddSkillBookMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_SKILLBOOK_MAGIC_DEL;
		m_packetHeader.usSize	= sizeof(sDBRequest_SkillBook_Magic_Del);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;

		m_iIndex				= _iIndex;
		m_clAddSkillBookMagic.Set( _pclAddSkillBookMagic );
	}
};

class sDBResponse_SkillBook_Magic_Del
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;			// �����.

	UI16				m_usCharID;
	SI32				m_siPersonID;				

	SI08				m_iIndex;
	cltSkillBookMagic	m_clAddSkillBookMagic;

	sDBResponse_SkillBook_Magic_Del( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ��ų�� �������� �߰�.
class sDBRequest_SkillBook_SubMagic_Add
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;				

	cltSkillBookSubMagic	m_clAddSkillBookSubMagic;

	sDBRequest_SkillBook_SubMagic_Add( UI16 _usCharID, SI32 _siPersonID, cltSkillBookSubMagic* _pclAddSkillBookSubMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_SKILLBOOK_SUBMAGIC_ADD;
		m_packetHeader.usSize	= sizeof(sDBRequest_SkillBook_SubMagic_Add);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;

		memcpy( &m_clAddSkillBookSubMagic, _pclAddSkillBookSubMagic, sizeof(m_clAddSkillBookSubMagic) );
	}
};

class sDBResponse_SkillBook_SubMagic_Add
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;			// �����.

	UI16				m_usCharID;
	SI32				m_siPersonID;				

	cltSkillBookSubMagic	m_clAddSkillBookSubMagic;

	sDBResponse_SkillBook_SubMagic_Add( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ��ų�� �������� �߰�.
class sDBRequest_SkillBook_SubMagic_Del
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;				

	cltSkillBookSubMagic	m_clAddSkillBookSubMagic;
	bool					m_bTimeOver;

	sDBRequest_SkillBook_SubMagic_Del( UI16 _usCharID, SI32 _siPersonID, cltSkillBookSubMagic* _pclAddSkillBookSubMagic, bool _bTimeOver )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_SKILLBOOK_SUBMAGIC_DEL;
		m_packetHeader.usSize	= sizeof(sDBRequest_SkillBook_SubMagic_Del);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;

		memcpy( &m_clAddSkillBookSubMagic, _pclAddSkillBookSubMagic, sizeof(m_clAddSkillBookSubMagic) );
		m_bTimeOver = _bTimeOver;
	}
};

class sDBResponse_SkillBook_SubMagic_Del
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;			// �����.

	UI16				m_usCharID;
	SI32				m_siPersonID;				

	cltSkillBookSubMagic	m_clAddSkillBookSubMagic;
	bool					m_bTimeOver;

	sDBResponse_SkillBook_SubMagic_Del( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

// (REQUEST) [����] ���ֵ��̹̼� : ���ֵ��� �̼��� �޾����� ��� �����ϱ� ��û
class sDBRequest_GoonzuDayMissionInfo_Set
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SYSTEMTIME			m_MissionGetTime;

	//UI16 uiYear;			
	//UI08 uiMonth;			
	//UI08 uiDate;			
	SI16 siCount;			// �̼� ī��Ʈ

	sDBRequest_GoonzuDayMissionInfo_Set(UI16 _usCharID, SI32 _siPersonID, UI16 _uiYear, UI08 _uiMonth, UI08 _uiDate, SI16 _siCount)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_GOONZUDAYMISSIONINFO_SET;
		m_packetHeader.usSize	= sizeof(sDBRequest_GoonzuDayMissionInfo_Set);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;

		//
		m_MissionGetTime.wYear = _uiYear;
		m_MissionGetTime.wMonth = _uiMonth;
		m_MissionGetTime.wDay = _uiDate;
		siCount = _siCount;
	}
};


class sDBResponse_GoonzuDayMissionInfo_Set
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SYSTEMTIME			m_MissionGetTime;
		
	SI16 siCount;			// �̼� ī��Ʈ

	sDBResponse_GoonzuDayMissionInfo_Set()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

// (REQUEST) [����] ���ֵ��̹̼� : ���ֵ��� �̼��� �������� �ִ��� ��� �����
class sDBRequest_GoonzuDayMissionInfo_Get
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	sDBRequest_GoonzuDayMissionInfo_Get(UI16 _usCharID, SI32 _siPersonID)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_GOONZUDAYMISSIONINFO_GET;
		m_packetHeader.usSize	= sizeof(sDBRequest_GoonzuDayMissionInfo_Get);

		m_siPersonID			= _siPersonID;
		m_usCharID				= _usCharID;
	}
};

// (RESPONSE) [����] ���ֵ��̹̼� : ���ֵ��� �̼��� �������� �ִ����� ���� ����� ����
class sDBResponse_GoonzuDayMissionInfo_Get
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SYSTEMTIME			m_MissionGetTime;

	//UI16 uiYear;			
	//UI08 uiMonth;			
	//UI08 uiDate;			
	SI16 siCount;			// �̼� ī��Ʈ

	sDBResponse_GoonzuDayMissionInfo_Get()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

#endif