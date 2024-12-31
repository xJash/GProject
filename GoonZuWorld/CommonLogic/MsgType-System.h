#ifndef _MSGTYPESYSTEM_H
#define _MSGTYPESYSTEM_H

#include "../../Common/Ask/Ask.h"
#include "../../Common/Master/Master.h"

#include "../Server/server.h"
#include "../Server/Minister/MinisterBase.h"
#include "../Server/Minister/Minister-Yezo.h"
#include "../Server/Minister/Minister-Hozo.h"
#include "../Server/Minister/Minister-Hyungzo.h"
#include "../Server/Event/KingGuri/KingGuri.h"
#include "../Server/Event/SantaRaccoon/SantaRaccoonEvent.h"

#include "../Server/ServerEvent/ServerEvent_Manager.h"
#include "../Server/ServerEvent/ServerEvent-Quest.h"

#include "../../Common/WhisperChatMgr/WhisperChatBaseDefine.h"
#include "../../Common/WhisperChatMgr/WhisperChatObj.h"

#include "../../CommonLogic/WarRank/WarRank.h"

#include "../../DBManager/GameDBManager_World/DBGameLogMsg.h"

#include "../../Client/ninterface/nchatbardlg/NChatBarDlg.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"

#include "../Server/Event/GoonzuKingGuri/GoonzuKingGuri.h"

//-----------------------------
// PersonID�� �Ӹ� ä�� �����. 
//-----------------------------
class cltGameMsgRequest_MakeSecretChatChannel{
public:
	SI32 siPersonID;
	SI16 siCharUnique;
	TCHAR szCharName[MAX_PLAYER_NAME];
	TCHAR szChatBuffer[256];


	cltGameMsgRequest_MakeSecretChatChannel(SI32 personid, SI16 charunique,TCHAR * name ,TCHAR * buf = NULL )
	{


		siPersonID		= personid;
		siCharUnique	= charunique;
		
		MStrCpy(szCharName,name, MAX_PLAYER_NAME);
		MStrCpy(szChatBuffer, buf, 256 );
	}
};



class cltGameMsgResponse_MakeSecretChatChannel{
public:
	bool	bGameMaster;
	SI16	siCharUnique;
	SI32	siLevel;
	TCHAR	szName[MAX_PLAYER_NAME];
	TCHAR	szAccountID[MAX_PLAYER_NAME];
	TCHAR	szChatBuffer[256];
	
	bool	bHelp;							//[����] �����. 2008-10-13

	cltGameMsgResponse_MakeSecretChatChannel( bool gamemaster, SI16 charunique, SI32 level, TCHAR* pname, TCHAR* accountid, TCHAR* chatbuf, bool _bHelp = false )
	{
		bGameMaster = gamemaster;
		siCharUnique = charunique;
		siLevel = level;
		
		MStrCpy(szName, pname, MAX_PLAYER_NAME );
		MStrCpy( szAccountID, accountid, MAX_PLAYER_NAME );

		if ( chatbuf != NULL )
		{
			MStrCpy(szChatBuffer, chatbuf, 256);
		}
		else
		{
			szChatBuffer[ 0 ] = NULL;
		}

		bHelp = _bHelp;
	}
};
class cltGameMsgRequest_AcceptSecretChatChannel{//[����]
public:
//	SI32 siPersonID;
	SI16 siCharUnique;
	TCHAR szCharName[MAX_PLAYER_NAME];
	bool	bAccept;
	cltGameMsgRequest_AcceptSecretChatChannel(bool Accept, SI16 charunique,TCHAR * name  )
	{
		bAccept = Accept;
		//siPersonID		= personid;
		siCharUnique	= charunique;

		MStrCpy(szCharName,name, MAX_PLAYER_NAME);

	}
};

class cltGameMsgResponse_AcceptSecretChatChannel{ //[����]
public:
	SI16	siCharUnique;
	SI32	siLevel;
	TCHAR	szName[MAX_PLAYER_NAME];
	bool    bAccept;

	cltGameMsgResponse_AcceptSecretChatChannel(bool Accept,SI16 charunique, TCHAR* pname)
	{
		bAccept = Accept;

		siCharUnique = charunique;

		MStrCpy(szName, pname, MAX_PLAYER_NAME );

	}
};


const SI32 RAREITEM_NOTICE_SWITCH_MADE				= 1;
const SI32 RAREITEM_NOTICE_SWITCH_WENNYOLDMAN		= 2;
const SI32 RAREITEM_NOTICE_SWITCH_GACHA				= 3;
const SI32 RARAITEM_NOTICE_SWITCH_SUMMONDOLL		= 4;
const SI32 RARAITEM_NOTICE_SWITCH_HALLOWEENMANTLE	= 5;
const SI32 RARAITEM_NOTICE_SWITCH_CHRISTMASEVENT	= 6;
const SI32 RARAITEM_NOTICE_SWITCH_PVPLEAGUEPRIZE	= 7;
const SI32 RARAITEM_NOTICE_SWITCH_LEVELUPREWARD		= 8;
const SI32 RAREITEM_NOTICE_SWITCH_ENCHANTSUCCESS	= 9;

//------------------------------------------
// ��ǰ ���� �뺸.
//------------------------------------------
class cltGameMsgResponse_RareItemMade{
public:
	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ���� ��� �̸�. 
	SI32	siPersonID;						// ��ǰ �������� PersonID
	cltItem clItem;							// ������� ��ǰ ����. 

	SI32	siRareSwitch;		 		// ��ǰ�� ȹ���� ���.
	SI32	siIncFameExp;					// �� ����ġ������. 

	cltGameMsgResponse_RareItemMade()
	{
		siPersonID = 0;
		//StringCchCopy(szPersonName, MAX_PLAYER_NAME, TEXT(""));
		szPersonName[ 0 ] = NULL;
		siRareSwitch	= 0;
		siIncFameExp	= 0;
	}

	cltGameMsgResponse_RareItemMade(TCHAR* ppersonname, SI32 personid, cltItem* pclitem, SI32 rareswitch, SI32 incfameexp)
	{
		MStrCpy( szPersonName, ppersonname, MAX_PLAYER_NAME );
		siPersonID	= personid;
		clItem.Set(pclitem);
		siRareSwitch	= rareswitch;
		siIncFameExp	= incfameexp;
	}
};

//------------------------------------------
// ��� ����ǰ ȹ�� �뺸.
//------------------------------------------

class cltGameMsgResponse_BigWarItem{
public:
	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ���� ��� �̸�. 
	SI32	siPersonID;						// ��ǰ �������� PersonID
	cltItem clItem;							// ������� ��ǰ ����. 

	SI32	siIncFameExp;					// �� ����ġ������. 
	
	SI16	siReason;						// �� �������� �ް� �� ����. 
	SI16	siPara1;						// �Ķ��Ÿ 1

	cltGameMsgResponse_BigWarItem()
	{
		siPersonID = 0;
		//StringCchCopy(szPersonName, MAX_PLAYER_NAME, TEXT(""));
		szPersonName[ 0 ] = 0;
		siIncFameExp	= 0;
		siReason		= 0;
		siPara1			= 0;
	}

	cltGameMsgResponse_BigWarItem(const TCHAR* ppersonname, SI32 personid, cltItem* pclitem, SI32 incfameexp, SI16 reason, SI16 para1)
	{
		MStrCpy(szPersonName, ppersonname, MAX_PLAYER_NAME );
		siPersonID	= personid;
		clItem.Set(pclitem);
		siIncFameExp	= incfameexp;
		siReason		= reason;	
		siPara1			= para1;
	}
};

//------------------------------------------
// ���丶, �渶, �鸶 �������.
//------------------------------------------
class cltGameMsgResponse_GoodHorse{
public:
	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ���� ��� �̸�. 
	SI32	siPersonID;						// ��ǰ �������� PersonID
	SI16	siHorseUnique;					// ������� ���� ����ũ. 

	SI32	siIncFameExp;					// �� ����ġ������. 

	cltGameMsgResponse_GoodHorse()
	{
		siPersonID = 0;
		StringCchCopy(szPersonName, MAX_PLAYER_NAME,  TEXT(""));
		siHorseUnique	= 0;
		siIncFameExp	= 0;
	}

	cltGameMsgResponse_GoodHorse(TCHAR* ppersonname, SI32 personid, SI16 horseunique, SI32 incfameexp)
	{
		MStrCpy( szPersonName, ppersonname, MAX_PLAYER_NAME );
		siPersonID	= personid;
		siHorseUnique	= horseunique;
		siIncFameExp	= incfameexp;
	}
};
////2�� ��í.
//class cltGameMsgResponse_TanGwangGirl{
//public:
//	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ���� ��� �̸�. 
//	SI32	siPersonID;						// ��ǰ �������� PersonID
//	SI16	siItemUnique;					// ������� ���� ����ũ. 
//
//	SI32	siIncFameExp;					// �� ����ġ������. 
//
//	cltGameMsgResponse_TanGwangGirl()
//	{
//		siPersonID = 0;
//		StringCchCopy(szPersonName, MAX_PLAYER_NAME,  TEXT(""));
//		siItemUnique	= 0;
//		siIncFameExp	= 0;
//	}
//
//	cltGameMsgResponse_TanGwangGirl(TCHAR* ppersonname, SI32 personid, SI16 itemunique, SI32 incfameexp)
//	{
//		MStrCpy( szPersonName, ppersonname, MAX_PLAYER_NAME );
//		siPersonID	= personid;
//		siItemUnique	= itemunique;
//		siIncFameExp	= incfameexp;
//	}
//};

//KHY - 1001 - ��µ��� 5���� ���� ����.
class cltGameMsgResponse_NoAddHorse{
public:
	SI16	siResult;					// �����.

	cltGameMsgResponse_NoAddHorse()
	{
		siResult = 0;
	}

	cltGameMsgResponse_NoAddHorse(SI16	Result)
	{
		siResult = Result;
	}
};

//------------------------------------------
// ���� �ܰ� ��ȯ�� �⿬ 
//------------------------------------------
class cltGameMsgResponse_HighSummon{
public:
	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ���� ��� �̸�. 
	SI32	siPersonID;						// ��ǰ �������� PersonID
	SI16	siSummonKind;					// ������� ��ȯ�� KIND

	SI32	siIncFameExp;					// �� ����ġ������. 

	cltGameMsgResponse_HighSummon()
	{
		siPersonID = 0;
		StringCchCopy(szPersonName, MAX_PLAYER_NAME, TEXT(""));
		siSummonKind	= 0;
		siIncFameExp	= 0;
	}

	cltGameMsgResponse_HighSummon(TCHAR* ppersonname, SI32 personid, SI16 summonkind, SI32 incfameexp)
	{
		MStrCpy( szPersonName, ppersonname, MAX_PLAYER_NAME );
		siPersonID		= personid;
		siSummonKind	= summonkind;
		siIncFameExp	= incfameexp;
	}
};


//------------------------------------------
// ����� ������ �뺸.
//------------------------------------------
class cltGameMsgResponse_UserLevelUp{
public:
	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ������ �����. 
	TCHAR	szFatherName[MAX_PLAYER_NAME];	// ���� �̸�. 
	SI16	siLevel;

	cltGameMsgResponse_UserLevelUp()
	{
		StringCchCopy(szPersonName, MAX_PLAYER_NAME, TEXT(""));
		StringCchCopy(szFatherName, MAX_PLAYER_NAME, TEXT(""));
		siLevel	= 0;
	}

	cltGameMsgResponse_UserLevelUp(TCHAR* ppersonname, TCHAR* pfathername, SI16 level)
	{
		MStrCpy(szPersonName, ppersonname, MAX_PLAYER_NAME );
		MStrCpy(szFatherName, pfathername, MAX_PLAYER_NAME );
		siLevel	= level;
	}
};

//------------------------------------------
// ��� ���� ���/���� ��û 
//------------------------------------------
class cltGameMsgRequest_RegistMaster{
public:
	SI16	siSkillUnique;			// �ش� ���. 

	cltGameMsgRequest_RegistMaster()
	{
		siSkillUnique	= 0;
	}

	cltGameMsgRequest_RegistMaster(SI16 skillunique)
	{
		siSkillUnique	= skillunique;
	}
};


//------------------------------------------
// ��� ���� ����� ��û�Ѵ�.
//------------------------------------------
class cltGameMsgRequest_SkillMasterList{
public:
	SI16	siSkillUnique;

	cltGameMsgRequest_SkillMasterList()
	{
		siSkillUnique	= 0;
	}

	cltGameMsgRequest_SkillMasterList(SI16 skillunique)
	{
		siSkillUnique = skillunique;
	}
};

class cltGameMsgResponse_SkillMasterList{
public:
	SI16			siSkillUnique;
	SI16			siDataNum;			// ������ ����. 
	cltMasterUnitInfo clUnit[MAX_MASTER_PER_SKILL];

	cltGameMsgResponse_SkillMasterList()
	{
		siSkillUnique	= 0;
		siDataNum		= 0;
	}

	cltGameMsgResponse_SkillMasterList(SI16 skillunique)
	{
		siSkillUnique	= skillunique;
		siDataNum		= 0;
	}

	SI32 GetTotalSize()
	{
		return sizeof(SI16) + sizeof(SI16) + sizeof(cltMasterUnitInfo) * siDataNum;
	}
	
	void Add(cltMasterUnitInfo* pclinfo)
	{
		if(siDataNum >= MAX_MASTER_PER_SKILL)return ;

		clUnit[siDataNum].Set(pclinfo);
		siDataNum++;
	}
};

/*

//------------------------------------------
// �α��� ������ ������. 
//------------------------------------------
class cltGameMsgResponse_NoticeLogin{
public:
	SI16	siSize;
	TCHAR	szText[2048];

	cltGameMsgResponse_NoticeLogin()
	{
		siSize	= 0;
		strcpy(szText, TEXT(""));
	}

	cltGameMsgResponse_NoticeLogin(TCHAR* pnotice)
	{
		siSize	= min(2048, lstrlen(pnotice) + 1);
		strncpy(szText, pnotice, 2048-1);
	}

	SI32 GetTotalSize()
	{
		return sizeof(SI32);
		return sizeof(SI32) + siSize;
	}

};
*/

//------------------------------------------
// ��� ������ ���� ���¸� �뺸�Ѵ�.
//------------------------------------------
class cltGameMsgResponse_EnemyCapture{
public:
	SI08	siVillageUnique;
	bool	bCapture;

	cltGameMsgResponse_EnemyCapture()
	{
		siVillageUnique = 0;
		bCapture		= 0;
	}

	cltGameMsgResponse_EnemyCapture(SI08 villageunique, bool bcapture)
	{
		siVillageUnique = villageunique;
		bCapture		= bcapture;
	}

};

//------------------------------------------
// ��� ������ ���� ���¸� �뺸�Ѵ�.
//------------------------------------------
class cltGameMsgResponse_EnemyCaptureAll{
public:
	SI32	siBit[3];

	cltGameMsgResponse_EnemyCaptureAll()
	{
		for(SI32 i = 0;i < 3;i++)
		{
			siBit[i] = 0;
		}
	}

	void Set(bool mode, SI32 villageunique)
	{
		SI32 index	= villageunique / 32;
		if(index >= 3)return ;

		SI32 bit	= villageunique % 32;
		if(mode == true)
		{
			siBit[index] |= (1 << bit);
		}
		else
		{
			SI32 data = (1 << bit);
			if(siBit[index] & data)
			{
				siBit[index] -= data;
			}
		}
	}

};

//------------------------------------------
// Ư�� ������� ������ �����ϵ��� ��û�Ѵ�. 
//------------------------------------------
class cltGameMsgResponse_DelAsk{
public:
	SI16	siPersonID;

	cltGameMsgResponse_DelAsk()
	{
		siPersonID	= 0;
	}
	cltGameMsgResponse_DelAsk(SI32 personid)
	{
		siPersonID	= personid;
	}

};

//------------------------------------------
// ���� ����Ʈ�� ������.  
//------------------------------------------
class cltGameMsgResponse_AskListUnit{
public:
	SI16	siCharUnique;
	SI32	siPersonID;
	TCHAR	szAskPersonName[MAX_PLAYER_NAME];
	TCHAR	szAskText[MAX_ASK_TEXT_SIZE];

	cltGameMsgResponse_AskListUnit()
	{
		void Init();
	}

	cltGameMsgResponse_AskListUnit(SI16 charunique, SI32 personid, TCHAR* ppersonname, TCHAR* asktext)
	{
		siCharUnique	= charunique;
		siPersonID		= personid;
		MStrCpy(szAskPersonName, ppersonname, MAX_PLAYER_NAME );
		MStrCpy(szAskText, asktext, MAX_ASK_TEXT_SIZE );
	}
	void Set(cltGameMsgResponse_AskListUnit* pclinfo)
	{
		siCharUnique	= pclinfo->siCharUnique;
		siPersonID		= pclinfo->siPersonID;
		MStrCpy( szAskPersonName, pclinfo->szAskPersonName, MAX_PLAYER_NAME );
		MStrCpy( szAskText, pclinfo->szAskText, MAX_ASK_TEXT_SIZE );
	}

	void Init()
	{
		siCharUnique	= 0;
		siPersonID		= 0;
	}
};

#define MAX_RESPONSE_ASK_LIST	20
class cltGameMsgResponse_AskList{
public:

	cltGameMsgResponse_AskListUnit clList[MAX_RESPONSE_ASK_LIST];

	cltGameMsgResponse_AskList()
	{
		Init();
	}

	void Init()
	{
		for(SI32 i = 0; i < MAX_RESPONSE_ASK_LIST;i++)
		{
			clList[i].Init();
		}
	}
};

//------------------------------------------
// ��ڰ� ���� �� �Ϳ� ���� ����. 
//------------------------------------------
class cltGameMsgResponse_GMGiveMoney{
public:

	 TCHAR	szPersonName[MAX_PLAYER_NAME];
	 GMONEY	siMoney;

	cltGameMsgResponse_GMGiveMoney(TCHAR* szname, GMONEY money)
	{
		MStrCpy( szPersonName, szname, MAX_PLAYER_NAME );
		siMoney			= money;
	}
};

//------------------------------------------
// ��ǰ ���� ����. 
//------------------------------------------
class cltGameMsgRequest_ProductPrice
{
public:

	SI16	siItemUnique;
	SI32	siDialogID;

	cltGameMsgRequest_ProductPrice( SI16 itemunique, SI32 dialogID = 0 )
	{
		siItemUnique = itemunique;
		siDialogID = dialogID;
	}
};
class cltGameMsgResponse_ProductPrice{
public:

	 SI16	siItemUnique;
	 GMONEY	siPrice;
	 SI32	siDialogID;

	cltGameMsgResponse_ProductPrice(SI16 itemunique, GMONEY price, SI32 dialogID = 0 )
	{
		siItemUnique	= itemunique;
		siPrice			= price;
		siDialogID		= dialogID;
	}
};

//------------------------------------------
// GM�� ����� ĳ���Ϳ� ���� ������ ��û�Ѵ�. 
//------------------------------------------
class cltGameMsgResponse_UserCharInfo
{
public:

	TCHAR			szAccountID[30];
	TCHAR			szPassword[30];
	bool			bConnectSwitch;		// ���� ����. 

    
	cltMoney		clTotalMoney;		// ������
	cltMoney		clBankMoney;		// ����ݾ�

	SI64			siWorldTradeMoney;
	
	cltSummonInfo	clSummonInfo;		// ��ȯ�� ����
	SI32			siVillageUnique;	// ���� ����

	SI32			siPersonID;
	SI16			siCharUnique;		//ĳ���� ����ũ �ѹ�(1~3000).
	SI16			siLevel;
	GMONEY			siMoney;

	SI16			siMapIndex;
	SI16			siX;
	SI16			siY;
	SI08			siGoonzuFriends;
	
	TCHAR			szOtherPersonName1[ MAX_PLAYER_NAME ];
	TCHAR			szOtherPersonName2[ MAX_PLAYER_NAME ];

	TCHAR			szRecommender[MAX_PLAYER_NAME]; // ��õ��
	TCHAR			szFatherName[MAX_PLAYER_NAME]; // ����
	SI16			siStudentLevel;					// ���ڰ� �Ǿ��� ���� ����

	TCHAR			szMakeDate[24];	// ĳ���� ������

	cltUserBlockLog	m_clUserBlockLog[MAX_BLOCKLOG_NUM+1];


//	cltItem clItem[MAX_ITEM_PER_PERSON];

	cltGameMsgResponse_UserCharInfo(TCHAR* szaccountid, TCHAR* password, cltMoney* pclmoney, cltMoney* pclbankmoney, SI64 worldtrademoney,
		bool connectswitch, SI32 personid, SI16 charUnique, SI16 level, GMONEY money, SI16 mapindex, SI16 x, SI16 y,
		SI08 goonzufriends, TCHAR *otherPerson1, TCHAR *otherPerson2,
		cltSummonInfo*	pclsummoninfo, SI32 villageunique, TCHAR* recommender,
		TCHAR *fathername,SI16 studentlevel,TCHAR* makedate, cltUserBlockLog* pclUserBlockLog)
	{
		MStrCpy( szAccountID, szaccountid, MAX_PLAYER_NAME );
		MStrCpy( szPassword, password, MAX_PLAYER_NAME );
		bConnectSwitch	= connectswitch;
		siPersonID		= personid;
		siCharUnique	= charUnique;		
		siLevel			= level;
		siMoney			= money;
		siMapIndex		= mapindex;
		siX				= x;
		siY				= y;
		siGoonzuFriends	= goonzufriends;

		clTotalMoney.Set(pclmoney);

		MStrCpy( szOtherPersonName1, otherPerson1, MAX_PLAYER_NAME );

		MStrCpy( szOtherPersonName2, otherPerson2, MAX_PLAYER_NAME );

		clBankMoney.Set( pclbankmoney );

		siWorldTradeMoney = worldtrademoney;
		
		memcpy( &clSummonInfo, pclsummoninfo, sizeof(cltSummonInfo));

		siVillageUnique = villageunique;

		MStrCpy( szRecommender, recommender, 24 );
		MStrCpy( szFatherName, fathername,MAX_PLAYER_NAME);
		siStudentLevel = studentlevel ;
		MStrCpy( szMakeDate, makedate,24);

		if ( pclUserBlockLog )	memcpy( m_clUserBlockLog, pclUserBlockLog, (sizeof(cltUserBlockLog) * (MAX_BLOCKLOG_NUM+1)) );
	}
};

//=====================================================================================
// �뷮�� Ŀ�� 2���� �и���
//=====================================================================================
class cltGameMsgResponse_UserCharItemInfo
{
public:
	// �κ��丮
	cltItem		m_clItem[MAX_ITEM_PER_PERSON];

	cltGameMsgResponse_UserCharItemInfo()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_UserCharItemInfo) );
	}

	cltGameMsgResponse_UserCharItemInfo( cltItem* pclItemList )
	{
		SI32 siIndex = 0;

		if (pclItemList)
		{
			for ( siIndex=0 ;siIndex<MAX_ITEM_PER_PERSON; ++siIndex )
			{
				m_clItem[siIndex].Set( &pclItemList[siIndex] );
			}
		}
	}
};	// GAMEMSG_RESPONSE_USERCHARITEMINFO

class cltGameMsgResponse_UserCharItemInfo2
{
public:
	// �������� ������
	cltItem		m_clSpaceBox[MAX_ITEM_SPACE_BOX];
	// �������� ������
	cltItem		m_clTreasureBox[MAX_ITEM_TREASURE_BOX];

	cltGameMsgResponse_UserCharItemInfo2()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_UserCharItemInfo2) );
	}

	cltGameMsgResponse_UserCharItemInfo2( cltItem* pclSpaceBox, cltItem* pclTreasureBox )
	{
		SI32 siIndex = 0;

		if ( pclSpaceBox )
		{
			for ( siIndex=0 ;siIndex<MAX_ITEM_SPACE_BOX; ++siIndex )
			{
				m_clSpaceBox[siIndex].Set( &pclSpaceBox[siIndex] );
			}
		}

		if ( pclTreasureBox )
		{
			for ( siIndex=0 ;siIndex<MAX_ITEM_TREASURE_BOX; ++siIndex )
			{
				m_clTreasureBox[siIndex].Set( &pclTreasureBox[siIndex] );
			}
		}
	}
};	// GAMEMSG_RESPONSE_USERCHARITEMINFO2


class cltGameMsgRequest_AccountInfo
{
public:

	TCHAR	szAccountID[ 32 ];

	cltGameMsgRequest_AccountInfo( TCHAR *accountid )
	{
		memcpy( szAccountID, accountid, 32 );
		szAccountID[ 31 ] = NULL;
	}
};


class cltGameMsgResponse_AccountInfo
{
public:
	TCHAR	szAccountID[ 32 ];
	TCHAR	szPersonName1[ MAX_PLAYER_NAME ];
	TCHAR	szPersonName2[ MAX_PLAYER_NAME ];
	TCHAR	szPersonName3[ MAX_PLAYER_NAME ];
	
	cltGameMsgResponse_AccountInfo( TCHAR *accountid, TCHAR *personname1, TCHAR *personname2, TCHAR *personname3 )
	{
		memcpy( szAccountID, accountid, 32 );
		szAccountID[ 31 ] = NULL;

		memcpy( szPersonName1, personname1, MAX_PLAYER_NAME );
		szPersonName1[ MAX_PLAYER_NAME - 1 ] = NULL;

		memcpy( szPersonName2, personname2, MAX_PLAYER_NAME );
		szPersonName2[ MAX_PLAYER_NAME - 1 ] = NULL;

		memcpy( szPersonName3, personname3, MAX_PLAYER_NAME );
		szPersonName3[ MAX_PLAYER_NAME - 1 ] = NULL;

	}
};


//------------------------------------------
// ���� �޽���. 
//------------------------------------------
#define WAR_CMD_BREAK		1		// ���� �߹�. 
#define WAR_CMD_WIN			2		// ���� ����. (�¸�) 
#define WAR_CMD_LOSE		3		// ���� ����. (�й�) 
#define WAR_CMD_GOING		4		// ������. 

#define BLACKWAR_CMD_BREAK		5	// ���Ǳ��� ���� �߹�. 
#define BLACKWAR_CMD_WIN		6	// ���Ǳ��� ���� ����. (�¸�) 
#define BLACKWAR_CMD_LOSE		7	// ���Ǳ��� ���� ����. (�й�) 
#define BLACKWAR_CMD_GOING		8	// ���Ǳ��� ������. 

class cltGameMsgResponse_BlackWar
{
public:

	SI32 siCmd;			

	DWORD uiLeftTime;		// ���� ���� �ð�. 
	SI32 siLeftEnemy;
	SI32 siTotalEnemy;
	SI32 siCasualty;		// �����. 
	SI32 siMapIndex;
	SI32 siX;
	SI32 siY;
	bool bMakeBoss;

	TCHAR szSortPlayerNames[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];
	SI32 siWarScores[MAX_WARRANK_PERSON_PER_MAP];
	
	//[�߰� : Ȳ���� 2008. 1. 21 => ���� ���������ؼ� Ŭ�󿡰� �� ����.]
	TCHAR szSortVillageNames[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];
	SI32 siWarVillageScores[MAX_WARRANK_PERSON_PER_MAP];

	cltGameMsgResponse_BlackWar( SI32 Cmd, DWORD LeftTime, SI32 LeftEnemy, SI32 TotalEnemy, SI32 Casualty, SI32 Mapindex, 
		SI32 X, SI32 Y, bool MakeBoss, TCHAR** PlayerNames, SI32* WarScores, TCHAR** VillageNames, SI32* WarVillageScores )
	{
		siCmd		 = Cmd;

		uiLeftTime	 = LeftTime;
		siLeftEnemy	 = LeftEnemy;
		siTotalEnemy = TotalEnemy;
		siCasualty	 = Casualty;

		siMapIndex	 = Mapindex;
		siX			 = X;
		siY			 = Y;
		bMakeBoss	 = MakeBoss;

		memcpy(szSortPlayerNames, PlayerNames, MAX_PLAYER_NAME * MAX_WARRANK_PERSON_PER_MAP * sizeof(TCHAR));
		memcpy(siWarScores, WarScores, MAX_WARRANK_PERSON_PER_MAP * sizeof(SI32));

		memcpy(szSortVillageNames, VillageNames,	 MAX_PLAYER_NAME * MAX_WARRANK_PERSON_PER_MAP * sizeof(TCHAR));
		memcpy(siWarVillageScores, WarVillageScores, MAX_WARRANK_PERSON_PER_MAP * sizeof(SI32));
	}
};

//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� ��Ŷ.]  
class cltGameMsgResponse_Black_War_Reform_Char_Result
{
public:
	SI32	siCharScore;
	GMONEY	siCharRewardMoney;
	bool	bWin;
	SI32	siRank;
	
	cltGameMsgResponse_Black_War_Reform_Char_Result(SI32	CharScore, GMONEY CharRewardMoney, bool Win, SI32	Rank)
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Black_War_Reform_Char_Result ) );
		
		siCharScore			 =	CharScore;
		siCharRewardMoney	 = 	CharRewardMoney;
		bWin			     =  Win;
		siRank				 =  Rank;
	}
};

//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� ��Ŷ.]  
class cltGameMsgResponse_Black_War_Reform_Village_Result
{
public:
	SI32	siVillageScore;
	SI08	siVillageRank;
	GMONEY	siVillageRewardMoney;
	bool	bWin;

	cltGameMsgResponse_Black_War_Reform_Village_Result(SI32 VillageScore,	SI08 VillageRank, GMONEY VillageRewardMoney, bool	Win)
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Black_War_Reform_Village_Result ) );

		siVillageScore		 =	VillageScore;
		siVillageRank		 =	VillageRank;
		siVillageRewardMoney =	VillageRewardMoney;
		bWin			     =  Win;
	}
};

class cltGameMsgResponse_BlackArmy_War{
public:
	SI16 siCmd;			

	DWORD uiLeftTime;		// ���� ���� �ð�. 
	SI32 siWarLeftMon;		// ���� ���� ����.
	SI32 siWarMapIndex;		// ������ε���

	TCHAR szSortPlayerNames[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];
	SI32 siWarScores[MAX_WARRANK_PERSON_PER_MAP];

	cltGameMsgResponse_BlackArmy_War(SI32 cmd, DWORD lefttime, SI32 warmapindex, SI32 warleftmon, TCHAR** PlayerNames, SI32* WarScores)
	{
		siCmd			= cmd;

		uiLeftTime		= lefttime;
		siWarMapIndex	= warmapindex;
		siWarLeftMon	= warleftmon;

		memcpy(szSortPlayerNames, PlayerNames, MAX_PLAYER_NAME * MAX_WARRANK_PERSON_PER_MAP * sizeof(TCHAR));
		memcpy(siWarScores, WarScores, MAX_WARRANK_PERSON_PER_MAP * sizeof(SI32));

	}
};


//-------------------------------------------
// NPC��ġ ���� ��û. 
//-------------------------------------------
class cltGameMsgRequest_NPCPos{
public:
	SI16 siKind;	

	cltGameMsgRequest_NPCPos(SI16 kind)
	{
		siKind = kind;
	}
};

class cltGameMsgResponse_NPCPos{
public:
	SI16 siKind;	
	SI16 siMapNumber;

	UI08 uiMapIndex[MAX_MAP_NUMBER];



	cltGameMsgResponse_NPCPos(SI16 kind, SI16 mapnumber, UI08* pmapindex)
	{
		siKind		= kind;
		siMapNumber	= mapnumber;

		for(SI32 i = 0;i < mapnumber;i++)
		{
			uiMapIndex[i] = pmapindex[i];
		}
	}

	SI32 GetTotalSize()
	{
		return sizeof(SI16) + sizeof(SI16) + siMapNumber;
	}
};




//-------------------------------------------
// �Ӹ��� �뺸. 
//-------------------------------------------
class cltGameMsgRequest_HeadChat{
public:
	SI16 siCharUnique;	
	cltGameMsgRequest_HeadChat(SI16 charunique)
	{
		siCharUnique = charunique;
	}
};

//-------------------------------------------
// �Ӹ��� �뺸. 
//-------------------------------------------
class cltGameMsgResponse_HeadChat{
public:
	SI16 siCharUnique;		// �Ӹ����� ����ϴ� ĳ������ ����ũ. 
	SI16 siTextSize;
	TCHAR szText[MAX_HEAD_CHAT_TEXT_SIZE];

	cltGameMsgResponse_HeadChat(SI16 charunique, TCHAR* ptext)
	{
		siCharUnique = charunique;
		memcpy( szText, ptext, MAX_HEAD_CHAT_TEXT_SIZE );
		szText[MAX_HEAD_CHAT_TEXT_SIZE-1] = NULL;

		siTextSize = _tcslen( szText ) + 1;		
	}
	
	SI32 GetTotalSize()
	{
		return sizeof(SI16) + sizeof(SI16) + siTextSize + 1;
	}
};


//-------------------------------------------
// �Ӹ� ä�� ����/���� ���� �뺸. 
//-------------------------------------------
#define SECRETCHAT_FAIL_INVALIDNAME		-1	// �̸� �Һи����� ����. 
#define SECRETCHAT_FAIL					0	// ���� �� ����. 
#define SECRETCHAT_FAIL_NOTUSER			-2  // �ش��ڰ� ������ ����.
#define SECRETCHAT_SUCCESS				1	// ����. 



class cltGameMsgResponse_SecretChatResult{
public:
	SI16 siResult;					// ���� , ����. 
	TCHAR szName[MAX_PLAYER_NAME];	// �Ӹ� ����� �̸�. 
	SI32 siCharUnique;

	cltGameMsgResponse_SecretChatResult(SI16 result, TCHAR* pname,SI32 CharUnique = 0)
	{
		siResult	= result;
		memcpy( szName, pname, MAX_PLAYER_NAME );
		szName[ MAX_PLAYER_NAME - 1 ] = NULL;
		siCharUnique = CharUnique;
	}
};

//------------------------------------------
// �Ӹ� ����. 
//------------------------------------------
#define MAX_SECRET_CHAT_TEXT_LENGTH 100 
class cltGameMsgSecretChat
{
public:
	SI16 siCharUnique;
	TCHAR szCharName[MAX_PLAYER_NAME];
	TCHAR szChatText[MAX_SECRET_CHAT_TEXT_LENGTH];

	cltGameMsgSecretChat( SI16 charunique, TCHAR* name, TCHAR* chattext )
	{
		siCharUnique = charunique;
		MStrCpy( szCharName, name, MAX_PLAYER_NAME ); 
		MStrCpy( szChatText, chattext, MAX_SECRET_CHAT_TEXT_LENGTH ); 
	}
};


//-------------------------------------------
// ����/�ִ� ����� ����. 
//-------------------------------------------
class cltGameMsgResponse_UserNum{
public:
	SI16 siCurUserNum;			// ���� ����� ����. 
	SI16 siMaxUserNum;			// �ִ� ����� ����. 


	bool bDBFailSwitch;			// DB�� ������ �ִ��� ����. 
	
	cltGameMsgResponse_UserNum(SI16 curnum, SI16 maxnum, bool bdb)
	{
		siCurUserNum	= curnum;
		siMaxUserNum	= maxnum;
		bDBFailSwitch	= bdb;
	}
};


//-------------------------------------------
// ��� ���Ƽ ����
//-------------------------------------------
class cltGameMsgResponse_DeathPenalty{
public:
	GMONEY siMoney;
	SI32 siExp;
	SI16 siKilledMode;
	TCHAR szKillMeCharName[MAX_PLAYER_NAME];

	cltGameMsgResponse_DeathPenalty(GMONEY money, SI32 exp, SI16 killmode, TCHAR* pname)
	{
		siMoney			= money;
		siExp			= exp;
		siKilledMode	= killmode;
		MStrCpy( szKillMeCharName, pname, MAX_PLAYER_NAME );
		szKillMeCharName[MAX_PLAYER_NAME-1] = '\0';

	}

};

//-----------------------------------------
//ä�� �޽���. 
//-----------------------------------------
#define CHATMODE_NORMAL		1	// �Ϲ� ä��. 
#define CHATMODE_SECRET		2	// �Ӹ� ä��. 
#define CHATMODE_TOWN		3	// ���� ����. 
#define CHATMODE_HEAD		4	// �Ӹ��� 
#define CHATMODE_HOME		5	// �ֹ� ä��. 
#define CHATMODE_ASK		6	// ����. . 
#define CHATMODE_SYSTEM		8	// �ý����� ����� ä��. 
#define CHATMODE_VILLAGER	9	// �ֹ� ����. (�ֹ� ��ο��� ����. ) 
#define CHATMODE_PARTY		10	// ��Ƽ ä��
#define CHATMODE_KING		11	// ���� ����
#define CHATMODE_NEWSITEM	12	// �ڸ����� ( ������ �ʿ� )
//_LEON_GUILD_CHAT
#define CHATMODE_GUILD		13	// ��� ��� ä��
//#define CHATMODE_GUILDALL	14	// ��� ����

class cltGameMsgRequest_Chat{
public:
	SI16 siDataSize;
	SI16 siChatMode;
	SI32 siSystemTxt;	// �ý��� �޽����� ��� �� txtmgr�� ��ȣ�� ������ �Ѵ�. ������ 0

	TCHAR szChatText[256];

	cltGameMsgRequest_Chat(SI16 chatmode,SI32 systemtxt, TCHAR* chattext)
	{
		StringCchCopy( szChatText, 256, chattext );
	
		siChatMode = chatmode;
		siSystemTxt = systemtxt ;

		siDataSize = sizeof(SI16) + sizeof(SI16) + sizeof(SI32) + _tcslen( szChatText ) + 1;
	}
};

//----------------------------------------------------------------
// ä�� ����. 
//----------------------------------------------------------------

class cltGameMsgResponse_Chat
{
public:
	SI16 siDataSize;
	SI16 siCharUnique;		// ä���� ���� ������� CharUnique
	SI16 PlayerNameLength;
	SI16 siMode;			// ä�� ���. 

	bool bGameMaster;		// ���Ӹ����� ����
	SI32 siSystemTxt;		// �ý��� txt
	SI32 siLevel;			// ����

	TCHAR szChatText[256];

	cltGameMsgResponse_Chat(SI16 charunique, SI16 mode, TCHAR* playername, TCHAR*text,bool GameMaster = false, SI32 level = 0 ,SI32 systemtxt = 0)
	{
		siDataSize = sizeof(SI16) + sizeof(SI16) + sizeof(SI16) + sizeof(SI16) + sizeof( BOOL ) + sizeof( SI32 )+ sizeof( SI32 );

		siCharUnique		= charunique;
		siMode				= mode;

		bGameMaster			= GameMaster;
		siLevel				= level ;
		siSystemTxt			= systemtxt ;


		// �÷��̾� �̸��� ���δ�.
		memcpy( szChatText, playername, MAX_PLAYER_NAME );
		szChatText[ MAX_PLAYER_NAME - 1 ] = NULL;

		PlayerNameLength	= _tcslen( szChatText );

		memcpy( &szChatText[ PlayerNameLength ], text, 100 );
		szChatText[ PlayerNameLength + 100 ] = NULL;

		siDataSize += _tcslen( szChatText ) + 1;
	}
};



//----------------------------------------------------------------
// ������ �Ϲ����� �������� �뺸 
//----------------------------------------------------------------

class cltGameMsgResponse_ServerInfo
{
public:
	
	SI16 siServiceArea;
	SI16 siServerUnique;
	bool bItemMallUseSwitch;

	bool bVillageWarSwitch;		// ������ �ð��� 
	bool bBonusTimeSwitch;		// ���ʽ� Ÿ�� ����. 
	bool bBonus2TimeSwitch;		// ���� ���� ���ʽ� Ÿ�� ����. 
	bool bSpecialQuestBonusTimeSwitch;
	bool bBroadcastSwitch;		// ��������� ����. 
	SI08 siBestVillageLevel;	// �ְ� ���� ���� 
	SI32 siNPCPriceRate;		// NPC ���� ����. 	
	GMONEY siItemPriceIndex;	// ����
	
	bool bEventSwitch[MAX_EVENT_NUMBER];

	SI32 siMinimumTeacherLevel;

	SI16 siServiceAge;			// �ѱ� �Ѱ��ӿ� ���� - ������ ���� ����
	SI08 siEnablePVP;			// PVP�� ������ �����ΰ�? 1: ����, 0: �Ұ���

	bool bAutoUnblockMode;		// AutoUnblock ���� ����

	bool bVoteCampaign;			// ���� �����Ⱓ���� �˸�

	bool bEventToggleSwitch[EVENT_TOGGLE_SWITCH_MAX];	// ���� ������� ����ġ

	cltGameMsgResponse_ServerInfo(SI16 servicearea, SI16 serverunique, bool bitemmall, bool villagewarswitch, 
		bool premiumswitch, bool bbonus2switch, bool bspecialquestbonus, bool bbroadcast, 
		SI08 villagelevel, SI32 npcpricerate, GMONEY ItemPriceIndex, bool* pevent, SI32 MinimumTeacherLevel,
		SI16 serviceage, SI08 enablepvp, bool AutoUnblockMode, bool voteCampaign, bool* pbEventToggleSwitch )
	{
		siServiceArea		= servicearea;
		siServerUnique		= serverunique;
		bItemMallUseSwitch	= bitemmall;
		bVillageWarSwitch	= villagewarswitch;
		bBonusTimeSwitch	= premiumswitch;
		bBonus2TimeSwitch	= bbonus2switch;
		bSpecialQuestBonusTimeSwitch	= bspecialquestbonus;
		bBroadcastSwitch	= bbroadcast;
		siBestVillageLevel	= villagelevel;
		siNPCPriceRate		= npcpricerate;
		siItemPriceIndex	= ItemPriceIndex;

		for(SI32 i = 0;i < MAX_EVENT_NUMBER;i++)
		{
			bEventSwitch[i] = pevent[i];	
		}

		siMinimumTeacherLevel	= MinimumTeacherLevel;

		siServiceAge			= serviceage;
		siEnablePVP				= enablepvp;

		bAutoUnblockMode		= AutoUnblockMode;
		bVoteCampaign			= voteCampaign;

		for ( SI32 siCount=0; siCount<EVENT_TOGGLE_SWITCH_MAX; ++siCount )
		{
			bEventToggleSwitch[siCount] = pbEventToggleSwitch[siCount];
		}
	}
};


//----------------------------------------------------------------
// �������� ���۰� ���Ḧ �˸�
//----------------------------------------------------------------

class cltGameMsgResponse_WarVillage
{
public:
	// ������ �ð��� 
	bool bVillageWarSwitch;

	cltGameMsgResponse_WarVillage(bool villagewarswitch)
	{
		bVillageWarSwitch = villagewarswitch;
	}
};

//----------------------------------------------------------------
// ���ʽ� Ÿ���� ���۰� ���Ḧ �˸�
//----------------------------------------------------------------
#define BONUSTIMEMODE_NORMAL		1		// �Ϲ� ���ʽ� Ÿ��. 
#define BONUSTIMEMODE_MAKE			2		// ����  ���ʽ� Ÿ��. 
#define BONUSTIMEMODE_SPECIALQUEST	3		// ��ι� ���ʽ� Ÿ��. 
class cltGameMsgResponse_BonusTime
{
public:
	SI16 siBonusTimeMode;
	bool bBonusTimeSwitch;

	cltGameMsgResponse_BonusTime(SI16 mode, bool bswitch)
	{
		siBonusTimeMode	= mode;
		bBonusTimeSwitch = bswitch;
	}
};

//----------------------------------------------------------------
// ���� �Ǽ��� ������ ���´�.
//----------------------------------------------------------------
class cltGameMsgResponse_GetByungzoInfo{
public:
	CMinisterBase		MinisterBase;
	SI32				siVillageWarTime;	// ����ð� 

	SI32				siSetTime;				// ���Ｓ���ð�
	SI32				siWarStartTime;			// ������۽ð�
	SI16				siSetWarCount;			// ���Ｓ�� Ƚ��
	SI32				siBlackArmyNum;			// ���� ���� ���� ��

	cltGameMsgResponse_GetByungzoInfo(CMinisterBase *pMinister, SI32 vilagewartime,
								SI32 settime, SI32 warstarttime, SI16 setwarcount, UI32 blackarmynum)
	{
		MinisterBase.Set(pMinister);
		siVillageWarTime = vilagewartime;

		siSetTime = settime;
		siWarStartTime = warstarttime;
		siSetWarCount = setwarcount;
		siBlackArmyNum = blackarmynum;

	}

};

class cltGameMsgResponse_GetYezoInfo{
public:
	CMinisterBase		MinisterBase;
	SI32				siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32				siJapanGunSolNum;	// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32				siJapanCommanderNum;// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32				siJapanPorterNum;	// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32				siWarVillageUnique; // ���ۿֱ��� �ĵ� ���� ����ũ

	cltGameMsgResponse_GetYezoInfo(CMinisterBase *pMinister, SI32 swordsolnum, SI32 gunsolnum, SI32 commandsolnum,SI32 portersolnum,SI32 villageunique)
	{
		MinisterBase.Set(pMinister);
		siJapanSwordSolNum	= swordsolnum;	
		siJapanGunSolNum	= gunsolnum;	
		siJapanCommanderNum	= commandsolnum;
		siJapanPorterNum	= portersolnum;

		siWarVillageUnique	= villageunique;
	}
};

class cltGameMsgResponse_GetHozoInfo{
public:
	CMinisterBase		MinisterBase;
	SI32				siResidentNum;	// �ֹμ� 
	SI32				siMaxShop;		// ���� �� �� ���λ�����

	SI32				siTotalCharNum; // �� �鼺��
	SI32				siCalcTime;		// �� �鼺�� ����� �ð�

	GMONEY				siPrizeMoney; // �����
	SI32				siPrizeSetTime; // ���� �ð�
	GMONEY				siFixationMoney;

	SI32				siNewCharRate;

	// �Ļ� ���� ����
	SI16				siBankruptcyVillageNumber;
	SI32				siSetBankruptcyVillageDate;

	SI16				siTutorialVillageDivideend;

	cltGameMsgResponse_GetHozoInfo(CMinisterBase *pMinister, SI32 residentNum,SI32 maxshop,
									SI32 totalcharnum,SI32 calctime,GMONEY prizemoney,
									SI32 prizesettime,GMONEY fixationmoney,SI32 newcharrate,
									SI16 BankruptcyVillageNumber, SI32 SetBankruptcyVillageDate,
									SI16 TutorialVillageDivideend)
	{
		MinisterBase.Set(pMinister);
		siResidentNum = residentNum;
		siMaxShop = maxshop ;

		siTotalCharNum = totalcharnum;
		siCalcTime = calctime;

		siPrizeMoney = prizemoney ;
		siPrizeSetTime = prizesettime ;
		siFixationMoney = fixationmoney ;

		siNewCharRate = newcharrate ;
		siBankruptcyVillageNumber = BankruptcyVillageNumber;
		siSetBankruptcyVillageDate = SetBankruptcyVillageDate;

		siTutorialVillageDivideend  = TutorialVillageDivideend;
	}
};

class cltGameMsgResponse_GetGoonzuInfo{
public:
	CMinisterBase		MinisterBase;
	
	INT64				iTotalFinances;

	SI16				siLiquidationVillageNumber;

	cltGameMsgResponse_GetGoonzuInfo(CMinisterBase *pMinister,SI64 finances, SI16 LiquidationVillageNumber )
	{
		MinisterBase.Set(pMinister);

		iTotalFinances = finances ;
		siLiquidationVillageNumber = LiquidationVillageNumber;		
	}
};

class cltGameMsgResponse_GetIzoInfo{
public:
	CMinisterBase		MinisterBase;

	SI32				siPriceTime;	// ���� �ð�

	SI32				siPriceInx;		// ��ǰ ��� �ü�
	SI32				siPriceValue;	// ������
	GMONEY				siTotalMoney;	// ����ȭ��
	SI32				siCalcTime;		// ��ȭ�� ����� �ð�
	SI32				siTradeTax;		// ������
	GMONEY				siTradeLimitMoney; // �ŷ� �ּҰ���

	bool				bWorldTradeTax;			// ����_���� ���� ����
	SI32				siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32				siSpecialTaxRate;		// ����_Ư������( 10% ~ 100% )
	SI32				siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI16				siTinTin;				// ƾƾ �߰� ������

	cltGameMsgResponse_GetIzoInfo(CMinisterBase *pMinister, SI32 priceinx,SI32 pricevalue,SI32 pricetime,
								  SI64 money,SI32 calctime, SI32 tradetax,GMONEY tradelimitmoney,
								  bool worldtradetax, SI32 specialtaxrange, SI32 specialtaxrate,
								  SI32 marketdownrate, SI16 tintin )
	{
		MinisterBase.Set(pMinister);
		siPriceInx		= priceinx ;
		siPriceValue	= pricevalue;
		siPriceTime		= pricetime;
		siTotalMoney	= money;
		siCalcTime		= calctime;
		siTradeTax		= tradetax;
		siTradeLimitMoney = tradelimitmoney;

		bWorldTradeTax		= worldtradetax;
		siSpecialTaxRange	= specialtaxrange;
		siSpecialTaxRate	= specialtaxrate;

		siMarketDownRate	= marketdownrate;

		siTinTin			= tintin;
	}
};

class cltGameMsgResponse_GetGongzoInfo{
public:
	CMinisterBase		MinisterBase;

	SI32				siPriceTime;
	SI16				siLeftOverValue;
	SI16				siLeftOverValue_Armor;
	GongzoMember		stGongzoMember;

	cltGameMsgResponse_GetGongzoInfo(CMinisterBase *pMinister,SI32 pricetime,SI16 leftovervalue,GongzoMember *gongzomember, SI16 LeftOverValue_Armor )
	{
		MinisterBase.Set(pMinister);
		siPriceTime = pricetime ;
		siLeftOverValue = leftovervalue ;
		siLeftOverValue_Armor = LeftOverValue_Armor;

		for ( int i = GONGZO_SKILL_START ; i < GONGZO_SKILL_TOTAL ; i ++ )
		{
			stGongzoMember.siPriceValue[i] = gongzomember->siPriceValue[i] ;
			stGongzoMember.siSkillValue[i] = gongzomember->siSkillValue[i] ;
		}
		stGongzoMember.siCraftFund = gongzomember->siCraftFund;
	}
};

class cltGameMsgResponse_GetHyungzoInfo{
public:
	CMinisterBase		MinisterBase;

	SI16				siLimitStealNum;
	SI16				siSuspectTime;
	SI16				siPrisonTime;
	SI16				siPrisonerPenalty;

	HyungzoMember		stHyungzoMember[MAX_PRISON_LIST_NUM];

	cltGameMsgResponse_GetHyungzoInfo(CMinisterBase *pMinister,SI16 limitstealnum,SI16 suspecttime,
									  SI16 prisontime,SI16 prisonerpenalty,HyungzoMember *hyungzomember)
	{
		MinisterBase.Set(pMinister);

		siLimitStealNum		= limitstealnum ;
		siSuspectTime		= suspecttime ;
		siPrisonTime		= prisontime ;
		siPrisonerPenalty	= prisonerpenalty ;

		for ( int i = 0 ; i < MAX_PRISON_LIST_NUM ; i ++ )
		{
			stHyungzoMember[i].siDate = hyungzomember[i].siDate ;
			stHyungzoMember[i].siPrisonSecond = hyungzomember[i].siPrisonSecond ;
			memcpy(stHyungzoMember[i].szCharName,hyungzomember[i].szCharName,MAX_PLAYER_NAME);
			memcpy(stHyungzoMember[i].szPrisonReason,hyungzomember[i].szPrisonReason,MAX_PRISON_REASON_SIZE);
		}
	}
};

//----------------------------------------------------------------
// ���� �Ǽ��� ������ �����Ѵ�.
//----------------------------------------------------------------
class cltGameMsgRequest_SetByungzoInfo{
public:
	TCHAR				szGreeting[256];
	SI32				siVillageWarTime;	// ����ð� 

	SI32				siSetTime;				// ���Ｓ���ð�
	SI32				siWarStartTime;			// ������۽ð�
	SI16				siSetWarCount;			// ���Ｓ�� Ƚ��
	SI32				siBlackArmyNum;			// ���� ���� ���� ��

	cltGameMsgRequest_SetByungzoInfo(TCHAR  *greeting, SI32 vilagewartime,
				SI32 settime, SI32 warstarttime, SI16 setwarcount, SI32 blackarmynum)
	{
		StringCchCopy(szGreeting, 256, greeting);
		siVillageWarTime = vilagewartime;

		siSetTime = settime;
		siWarStartTime = warstarttime;
		siSetWarCount = setwarcount;
		siBlackArmyNum = blackarmynum;

	}
};

class cltGameMsgRequest_SetByungzoInfoVillageWarTime{
public:	
	TCHAR				szGreeting[256];
	SI32				siVillageWarTime;	// ����ð� 

	cltGameMsgRequest_SetByungzoInfoVillageWarTime(TCHAR * greeting,SI32 vilagewartime	)
	{
		StringCchCopy(szGreeting, 256, greeting);
		siVillageWarTime = vilagewartime;
	}
};
 
class cltGameMsgRequest_SetYezoInfo{
public:
	TCHAR				szGreeting[256];
	SI32				siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32				siJapanGunSolNum;	// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32				siJapanCommanderNum;// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32				siJapanPorterNum;	// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32				siWarVillageUnique; // ���ۿֱ��� �ĵ� ���� ����ũ

	cltGameMsgRequest_SetYezoInfo(TCHAR  *greeting, SI32 swordsolnum, SI32 gunsolnum, SI32 commandsolnum,SI32 portersolnum,SI32 villageunique)
	{
		StringCchCopy(szGreeting, 256, greeting);
		siJapanSwordSolNum	= swordsolnum;	
		siJapanGunSolNum	= gunsolnum;	
		siJapanCommanderNum	= commandsolnum;
		siJapanPorterNum	= portersolnum;

		siWarVillageUnique	= villageunique ;
	}
};

class cltGameMsgRequest_SetHozoInfo{
public:
	TCHAR				szGreeting[256];
	SI32				siResidentNum;	// �ֹμ�
	SI32				siMaxShop; // ������ �� ���λ�����

	GMONEY				siPrizeMoney; // �����
	GMONEY				siFixationMoney;

	GMONEY				siTutorialVillageDivideend;	// ��ī�� �ֽ� ����

	cltGameMsgRequest_SetHozoInfo(TCHAR  *greeting, SI32 residentNum,SI32 maxshop,
								  GMONEY prizemoney,GMONEY fixationmoney, GMONEY TutorialVillageDivideend)
	{
		StringCchCopy(szGreeting, 256, greeting);
		siResidentNum = residentNum;
		siMaxShop = maxshop ;

		siPrizeMoney = prizemoney ;
		siFixationMoney = fixationmoney ;

		siTutorialVillageDivideend = TutorialVillageDivideend;  
	}
};

class cltGameMsgRequest_SetGoonzuInfo{
public:
	TCHAR				szGreeting[256];

	cltGameMsgRequest_SetGoonzuInfo(TCHAR  *greeting)
	{
		StringCchCopy(szGreeting, 256, greeting);
	}
};

class cltGameMsgRequest_SetIzoInfo{
public:
	TCHAR				szGreeting[256];
	SI32				siPriceValue;			// ������
	bool				bWorldTradeTax;			// ����_���� ���� ����
	SI32				siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32				siSpecialTaxRate;		// ����_Ư������( 10% ~ 100% )
	SI32				siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI32				siTinTin;				// ƾƾ �߰� ������


	cltGameMsgRequest_SetIzoInfo(TCHAR  *greeting,SI32 pricevalue, bool worldtradetax, 
		SI32 specialtaxrange, SI32 specialtaxrate, SI32 marketdownrate, SI32 tintin)
	{
		StringCchCopy(szGreeting, 256, greeting);
		siPriceValue	= pricevalue;

		bWorldTradeTax		= worldtradetax;
		siSpecialTaxRange	= specialtaxrange;
		siSpecialTaxRate	= specialtaxrate;
		siMarketDownRate	= marketdownrate;
		siTinTin			= tintin;
	}
};

class cltGameMsgRequest_SetGongzoInfo{
public:
	TCHAR				szGreeting[256];

	SI16				siLeftOverValue;
	SI16				siPriceValue[GONGZO_SKILL_TOTAL];
	SI16				siLeftOverValue_Armor;

	GMONEY				siCraftFund;

	cltGameMsgRequest_SetGongzoInfo(TCHAR  *greeting,SI16 leftovervalue,SI16 *pricevalue, GMONEY craftfund, SI32 leftovervalue_armor )
	{
		StringCchCopy(szGreeting, 256, greeting);

		siLeftOverValue = leftovervalue;
		siLeftOverValue_Armor = leftovervalue_armor;

		for ( int i = GONGZO_SKILL_START ; i < GONGZO_SKILL_TOTAL ; i ++ )
		{
			siPriceValue[i] = pricevalue[i] ;
		}
		siCraftFund = craftfund;
	}
};

class cltGameMsgRequest_SetHyungzoInfo{
public:
	TCHAR				szGreeting[256];

	SI16				siLimitStealNum;
	SI16				siSuspectTime;
	SI16				siPrisonTime;
	SI16				siPrisonerPenalty;

	cltGameMsgRequest_SetHyungzoInfo(TCHAR * greeting,SI16 limitstealnum,
									 SI16 suspecttime,SI16 prisontime,SI16 prisonerpenalty)
	{
		StringCchCopy(szGreeting, 256, greeting);

		siLimitStealNum		= limitstealnum ;
		siSuspectTime		= suspecttime ;
		siPrisonTime		= prisontime ;
		siPrisonerPenalty	= prisonerpenalty ;
	}
};

class cltGameMsgRequest_SetHyungzoPrison{
public:
	HyungzoMember			stHyungzoMember;

	cltGameMsgRequest_SetHyungzoPrison(HyungzoMember *hyungzomember)
	{
		memcpy(&stHyungzoMember,hyungzomember,sizeof(HyungzoMember));
	}
};

// �����Ǽ� å�󿡼� ��ȣõ����� �����ϰ� �ҷ����� �Ѵ�.

class cltGameMsgRequest_SetAngelApplyer // ��ȣõ�� ��� ��û
{
public:
	bool	bAdmin ; // true�� ��û , false�� ����

	SI32	siIndex ; // -1 �̸� ��û�ڰ� ���� ��û�� �� , �����Ǽ��� ���ӽ� ���

	cltGameMsgRequest_SetAngelApplyer(bool admin,SI32 index = -1 )
	{
		bAdmin = admin ;

		siIndex = index ;
	}
};

class cltGameMsgResponse_SetAngelApplyer // ��ȣõ�� ��� ��û ����
{
public:
	SI32	siResult ; // 1�̸� ���� , 0�̸� ����

	bool	bAdmin ; // true�� ��û�� ���� ���� , false�� ������ ���� ����
	
	SI32	siIndex ; // -1 �̸� ��û�ڰ� ���� ��û�� �� , �����Ǽ��� ���ӽ� ���

	cltGameMsgResponse_SetAngelApplyer(SI32 result,bool admin,SI32 index = -1 )
	{
		siResult = result ;

		bAdmin = admin;

		siIndex = index ;
	}
};

class cltGameMsgRequest_SetAngel // ��ȣõ�� �Ӹ� �� ����
{
public:
	SI32	siIndex ; // ������ ĳ���� �ε���

	bool	bAdmin ; // true�� �Ӹ� , false�� ����

	cltGameMsgRequest_SetAngel(SI32 index,bool admin)
	{
		siIndex = index ;

		bAdmin = admin ;
	}
};

class cltGameMsgResponse_SetAngel // ��ȣõ�� �Ӹ� �� ����
{
public:
	SI32	siResult ; // 1�̸� ���� , 0�̸� ����

	SI32	siIndex ; // ������ ĳ���� �ε���
	bool	bAdmin ; // true�� �Ӹ� , false�� ����

	cltGameMsgResponse_SetAngel(SI32 result,SI32 index, bool admin)
	{
		siResult = result ;

		siIndex = index ;
		bAdmin = admin;
	}
};

class cltGameMsgResponse_GetAngelList // ��ȣõ�� ��� ��û ����
{
public:
	SI32	siResult;

	HozoAngelList	stHozoAngelList[MAX_HOZO_ANGELLIST];

	cltGameMsgResponse_GetAngelList(SI32 result,HozoAngelList * yezoangellist)
	{
		siResult = result ;

		for ( int i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
		{
			memcpy(stHozoAngelList[i].szAccountID,yezoangellist[i].szAccountID,32);
			memcpy(stHozoAngelList[i].szName,yezoangellist[i].szName,MAX_PLAYER_NAME);

			stHozoAngelList[i].siLevel = yezoangellist[i].siLevel ;
			stHozoAngelList[i].siFameLevel = yezoangellist[i].siFameLevel ;
			
			stHozoAngelList[i].siPersonID = yezoangellist[i].siPersonID ;
		}
	}
};

class cltGameMsgResponse_GetAngelApplyerList // ��ȣõ�� ��û�� ��� ��û ����
{
public:
	SI32	siResult;

	HozoAngelList	stHozoAngelApplyerList[MAX_HOZO_ANGELLIST];

	cltGameMsgResponse_GetAngelApplyerList(SI32 result,HozoAngelList * yezoangelapplyerlist)
	{
		siResult = result ;

		for ( int i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
		{
			memcpy(stHozoAngelApplyerList[i].szAccountID,yezoangelapplyerlist[i].szAccountID,32);
			memcpy(stHozoAngelApplyerList[i].szName,yezoangelapplyerlist[i].szName,MAX_PLAYER_NAME);

			stHozoAngelApplyerList[i].siLevel = yezoangelapplyerlist[i].siLevel ;
			stHozoAngelApplyerList[i].siFameLevel = yezoangelapplyerlist[i].siFameLevel ;

			stHozoAngelApplyerList[i].siPersonID = yezoangelapplyerlist[i].siPersonID ;
		}
	}
};

class cltGameMsgResponse_GetPoliceList
{
public:
	SI32	siResult;

	HyungzoPoliceList	stHyungPoliceList[MAX_HYUNGZO_POLICELIST];

	cltGameMsgResponse_GetPoliceList(SI32 result,HyungzoPoliceList * pHyungzoPoliceList)
	{
		siResult = result ;

		for ( int i = 0 ; i < MAX_HYUNGZO_POLICELIST ; i ++ )
		{
			memcpy(stHyungPoliceList[i].szAccountID,pHyungzoPoliceList[i].szAccountID,32);
			memcpy(stHyungPoliceList[i].szName,pHyungzoPoliceList[i].szName,MAX_PLAYER_NAME);

			stHyungPoliceList[i].siPersonID = pHyungzoPoliceList[i].siPersonID ;
			stHyungPoliceList[i].siLevel = pHyungzoPoliceList[i].siLevel ;
		}
	}
};

class cltGameMsgRequest_SetPolice	// ������ ������ �����Ѵ�
{
public:
	TCHAR szPoliceName[ MAX_PLAYER_NAME ];	// ������ �̸�
	bool bSet;						// true : ���� false : ����
	
	cltGameMsgRequest_SetPolice(TCHAR* pName, bool bFlag)
	{
		MStrCpy(szPoliceName, pName, MAX_PLAYER_NAME);
		bSet = bFlag;
	}

};

class cltGameMsgResponse_SetPolice	// ������ ������ �����Ѵ�
{
public:
	SI32 siResult;
	TCHAR szPoliceName[ MAX_PLAYER_NAME ];	// ������ �̸�
	bool bSet;						// true : ���� false : ����

	cltGameMsgResponse_SetPolice(SI32 result, TCHAR* pName, bool bFlag)
	{
		siResult = result;
		MStrCpy(szPoliceName, pName, MAX_PLAYER_NAME);
		bSet = bFlag;
	}
};

class cltGameMsgResponse_GetCriminalList
{
public:
	SI32	siResult;

	HyungzoCriminalList	stHyungzoCriminalList[MAX_HYUNGZO_CRIMINALLIST];

	cltGameMsgResponse_GetCriminalList(SI32 result,HyungzoCriminalList * pHyungzoCriminalList)
	{
		siResult = result ;

		for ( int i = 0 ; i < MAX_HYUNGZO_CRIMINALLIST ; i ++ )
		{
			memcpy(stHyungzoCriminalList[i].szAccountID,pHyungzoCriminalList[i].szAccountID,32);
			memcpy(stHyungzoCriminalList[i].szName, pHyungzoCriminalList[i].szName,MAX_PLAYER_NAME);
			memcpy(stHyungzoCriminalList[i].szReason, pHyungzoCriminalList[i].szReason, MAX_PRISON_REASON_SIZE);

			stHyungzoCriminalList[i].siPersonID = pHyungzoCriminalList[i].siPersonID ;
			stHyungzoCriminalList[i].siTime = pHyungzoCriminalList[i].siTime ;
		}
	}
};

class cltGameMsgRequest_SetCriminal	// ������ ������ �����Ѵ�
{
public:
	TCHAR szCriminalName[ MAX_PLAYER_NAME ];	// ������ �̸�
	TCHAR szCriminalReason[ MAX_PRISON_REASON_SIZE ];	// ������ ����
	bool bSet;						// true : ���� false : ����
	
	cltGameMsgRequest_SetCriminal(TCHAR* pName, TCHAR* pReason, bool bFlag)
	{
		MStrCpy(szCriminalName, pName, MAX_PLAYER_NAME);
		MStrCpy(szCriminalReason, pReason, MAX_PRISON_REASON_SIZE);
		bSet = bFlag;
	}
};

class cltGameMsgResponse_SetCriminal
{
public:
	SI16 siResult;

	cltGameMsgResponse_SetCriminal( SI16 result )
	{
		siResult = result;
	}
};

/*
class cltGameMsgResponse_SetPolice	// ������ ������ �����Ѵ�
{
public:
	SI32 siResult;

	cltGameMsgResponse_SetPolice(SI32 result)
	{
		siResult = result;
	}
};*/

// ������ �̺�Ʈ ������ Ŭ���̾�Ʈ���� ������. 
class cltGameMsgResponse_ServerEventInfo{
public:
	bool bEventSwitch[MAX_EVENT_NUMBER];

	cltGameMsgResponse_ServerEventInfo(bool* pevent)
	{
		SI32 i;

		for(i = 0;i < MAX_EVENT_NUMBER;i++)
		{
			bEventSwitch[i] = pevent[i];
		}
	}
};

class cltGameMsgResponse_GiftNT
{
public:
	TCHAR strGiftName[ 32 ];
	TCHAR strMasterNoticeMsg[ 128 ];
	cltGameMsgResponse_GiftNT( TCHAR *GiftName, TCHAR *MasterNoticeMsg )
	{
		MStrCpy( strGiftName, GiftName, 32 );
		MStrCpy( strMasterNoticeMsg, MasterNoticeMsg, 128 );
	}
};

class cltGameMsgRequest_WhisperChat_Reject
{
public:
	bool bWhisperChatReject;
	cltGameMsgRequest_WhisperChat_Reject( bool WhisperChatReject )
	{
		bWhisperChatReject = WhisperChatReject;
	}
};

class cltGameMsgResponse_WhisperChat_Reject
{
public:
	bool bWhisperChatReject;
	cltGameMsgResponse_WhisperChat_Reject( bool WhisperChatReject )
	{
		bWhisperChatReject = WhisperChatReject;
	}
};

class cltGameMsgRequest_PrivateTrade_Reject
{
public:
	bool bPrivateTradeReject;
	cltGameMsgRequest_PrivateTrade_Reject( bool PrivateTradeReject )
	{
		bPrivateTradeReject = PrivateTradeReject;
	}
};

class cltGameMsgResponse_PrivateTrade_Reject
{
public:
	bool bPrivateTradeReject;
	cltGameMsgResponse_PrivateTrade_Reject( bool PrivateTradeReject )
	{
		bPrivateTradeReject = PrivateTradeReject;
	}
};

class cltGameMsgRequest_PartyInvite_Reject
{
public:
	bool bPartyInviteReject;
	cltGameMsgRequest_PartyInvite_Reject( bool PartyInviteReject )
	{
		bPartyInviteReject = PartyInviteReject;
	}
};

class cltGameMsgRequest_FriendAdd_Reject
{
public:
	bool bFriendAddReject;
	cltGameMsgRequest_FriendAdd_Reject( bool FriendAddReject )
	{
		bFriendAddReject = FriendAddReject;
	}
};

// ���� ���� �˸� �޽���. 
class cltGameMsgResponse_BossAppear
{
public:
	SI16	siBossKind;		// ���� ���� 
	SI32	siLeftSecond;	// �������� ���� �ð�. 

	cltGameMsgResponse_BossAppear( SI16 bosskind, SI32 leftsecond)
	{
		siBossKind		= bosskind;
		siLeftSecond	= leftsecond;
	}
};

class cltGameMsgRequest_WhisperChat_Create
{
public:
	TCHAR strOtherCharName[ MAX_PLAYER_NAME ];
	cltGameMsgRequest_WhisperChat_Create( TCHAR *OtherCharName )
	{
		memcpy( strOtherCharName, OtherCharName, MAX_PLAYER_NAME - 1 );
		strOtherCharName [ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};

class cltGameMsgResponse_WhisperChat_Create
{
public:
	SI32 siWhisperChatIndex;
	stWhisperChatMember sWhisperChatMember;
	
	cltGameMsgResponse_WhisperChat_Create( SI32 WhisperChatIndex, stWhisperChatMember *pWhisperChatMember )
	{
		siWhisperChatIndex = WhisperChatIndex;
		sWhisperChatMember.Set( pWhisperChatMember );
	}
};

class cltGameMsgRequest_WhisperChat_Invite
{
public:
	SI32 siWhisperChatIndex;
	TCHAR strInviteCharName[ MAX_PLAYER_NAME ];		// �ʴ��ҷ��� ����� ĳ���͸�
	
	cltGameMsgRequest_WhisperChat_Invite( SI32 WhisperChatIndex, TCHAR *InviteCharName )
	{
		siWhisperChatIndex = WhisperChatIndex;
		memcpy( strInviteCharName, InviteCharName, MAX_PLAYER_NAME - 1 );
		strInviteCharName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};

class cltGameMsgResponse_WhisperChat_Invite
{
public:
	SI32 siWhisperChatIndex;

	cltGameMsgResponse_WhisperChat_Invite( SI32 WhisperChatIndex )
	{
		siWhisperChatIndex = WhisperChatIndex;
	}
};

class cltGameMsgRequest_WhisperChat_UserList
{
public:
	SI32 siWhisperChatIndex;
	
	cltGameMsgRequest_WhisperChat_UserList( SI32 WhisperChatIndex )
	{
		siWhisperChatIndex = WhisperChatIndex;
	}
};

class cltGameMsgResponse_WhisperChat_UserList
{
public:
	SI32 siWhisperChatIndex;

	stWhisperChatMember sWhisperChatMemberList[ MAX_WHISPERCHAT_OBJ_USERNUM ];

	cltGameMsgResponse_WhisperChat_UserList( SI32 WhisperChatIndex, stWhisperChatMember *pWhisperChatMemberList )
	{
		siWhisperChatIndex = WhisperChatIndex;
		memcpy ( sWhisperChatMemberList, pWhisperChatMemberList, sizeof( stWhisperChatMember ) * MAX_WHISPERCHAT_OBJ_USERNUM );
	}
};


class cltGameMsgRequest_WhisperChat_Out
{
public:
	SI32 siWhisperChatIndex;

	cltGameMsgRequest_WhisperChat_Out( SI32 WhisperChatIndex )
	{
		siWhisperChatIndex = WhisperChatIndex;
	}
	
};

class cltGameMsgResponse_WhisperChat_Out
{
public:
	SI32 siWhisperChatIndex;
	SI32 siPersonID;

	cltGameMsgResponse_WhisperChat_Out( SI32 WhisperChatIndex, SI32 PersonID )
	{
		siWhisperChatIndex = WhisperChatIndex;
		siPersonID = PersonID;
	}
};

class cltGameMsgRequest_Personal_Log
{
public:
	SI32				siLogType; // �α��� ����

	TCHAR				szServerName[MAX_DBLOG_SIZE_SERVERNAME]; // ���� �̸�
	TCHAR				szPersonName[MAX_PLAYER_NAME]; // ã�� ĳ������ �̸�

	SI32				siItemUnique;

	TCHAR				szDate[MAX_DBLOG_SIZE_DATE]; // �˻� �ð�
	TCHAR				szStartTime[MAX_DBLOG_SIZE_DATE]; // �˻��� �ð�
	TCHAR				szEndTime[MAX_DBLOG_SIZE_DATE]; // �˻� ���� �ð�

	cltGameMsgRequest_Personal_Log( SI32 logtype,TCHAR * server, TCHAR * person,
		SI32 itemunique,TCHAR * date, TCHAR * start, TCHAR * end)
	{
		siLogType = logtype;
		
		memcpy(szServerName,server,MAX_DBLOG_SIZE_SERVERNAME);
		memcpy(szPersonName,person,MAX_PLAYER_NAME);

		siItemUnique = itemunique ;

		memcpy(szDate,date,MAX_DBLOG_SIZE_DATE);
		memcpy(szStartTime,start,MAX_DBLOG_SIZE_DATE);
		memcpy(szEndTime,end,MAX_DBLOG_SIZE_DATE);
	}
};

class cltGameMsgResponse_Personal_Log
{
public:
	SI32			siResult; // 1�̸� ��� -1�̸� ��
	stLOGData		stLogData[MAX_STLOGDATA_PER_PACKET];

	cltGameMsgResponse_Personal_Log( SI32 Result,stLOGData * logdata )
	{
		siResult = Result ;
		for ( int i = 0 ; i < MAX_STLOGDATA_PER_PACKET ; i ++ )
			stLogData[i].Set(&logdata[i]);
	}
};

//-----------------------------------------
// �Ұ��縮 ��� ����. 
//-----------------------------------------
class cltGameMsgResponse_HuntingInfo
{
public:
	SI16	siVillageUnique;		// �̺�Ʈ ���� ����. 
	SI32	siLeftSecond;			// ���� �ð�. 
	
	SI32	siMode;					// �¸�(1), �й�(-1), ����(0)


	cltGameMsgResponse_HuntingInfo(SI16 villageunique, SI32 leftsecond, SI16 mode)
	{
		siVillageUnique	= villageunique;
		siLeftSecond	= leftsecond;
		siMode			= mode;	
	}
};

//-----------------------------------------
// �Ұ��縮 ��� ���� ����. 
//-----------------------------------------
class cltGameMsgResponse_HuntingReward
{
public:
	SI32	siExp;				// ȹ�� ����ġ. 
	SI32	siFameExp;			// ȹ�� �� ����ġ.
	SI32	siRewardItemUnique;	// ���� ������ ����ũ
	SI32	siRewardItemNum;	// ���� ������ ����

	 cltGameMsgResponse_HuntingReward(SI32 exp, SI32 fameexp, SI32 rewarditemunique = 0, SI32 rewarditemnum = 0)
	{
		siExp				= exp;
		siFameExp			= fameexp;
		siRewardItemUnique	= rewarditemunique;
		siRewardItemNum		= rewarditemnum;
	}
};


//-----------------------------------------
// ���� ���� ��� ����. 
//-----------------------------------------
class cltGameMsgResponse_GoguInfo
{
public:
	SI16	siVillageUnique;		// �̺�Ʈ ���� ����. 
	SI32	siLeftSecond;			// ���� �ð�. 
	
	SI32	siMode;					// �¸�(1), �й�(-1), ����(0)


	cltGameMsgResponse_GoguInfo(SI16 villageunique, SI32 leftsecond, SI16 mode)
	{
		siVillageUnique	= villageunique;
		siLeftSecond	= leftsecond;
		siMode			= mode;	
	}
};

//-----------------------------------------
// ���� ���� ��� ���� 
//-----------------------------------------
class cltGameMsgResponse_GoguReward
{
public:
	SI32	siExp;				// ȹ�� ����ġ. 
	SI32	siFameExp;			// ȹ�� �� ����ġ. 
	GMONEY	siMoney;			// ȹ�� �ڱ� 

	cltGameMsgResponse_GoguReward(SI32 exp, SI32 fameexp, GMONEY money)
	{
		siExp			= exp;
		siFameExp		= fameexp;
		siMoney			= money;
	}
};

//-----------------------------------------
// ����ī�� ���� ����. 
//-----------------------------------------
class cltGameMsgResponse_OsakaInfo
{
public:
	SI32	siMapIndex;
	SI32	siLeftSecond;			// ���� �ð�. 
	SI16	siMode;					// �¸�(1), �й�(-1), ����(0)
	
	cltGameMsgResponse_OsakaInfo(SI32 mapindex, SI32 leftsecond, SI16 mode)
	{
		siMapIndex		= mapindex;
		siLeftSecond	= leftsecond;
		siMode			= mode;	
	}
};

//-----------------------------------------
// ����ī�� ���� ���� 
//-----------------------------------------
class cltGameMsgResponse_OsakaReward
{
public:
	SI32	siExp;				// ȹ�� ����ġ. 
	SI32	siFameExp;			// ȹ�� �� ����ġ. 
	GMONEY	siMoney;			// ȹ�� �ڱ� 

	cltGameMsgResponse_OsakaReward(SI32 exp, SI32 fameexp, GMONEY money)
	{
		siExp			= exp;
		siFameExp		= fameexp;
		siMoney			= money;
	}
};

//-----------------------------------------
// ��ȭ�� ���� ����. 
//-----------------------------------------
class cltGameMsgResponse_KanghwadoInfo
{
public:
	SI32	siVillageUnique;
	SI32	siLeftSecond;			// ���� �ð�. 
	SI16	siMode;					// �¸�(1), �й�(-1), ����(0)


	cltGameMsgResponse_KanghwadoInfo(SI32 villageunique, SI32 leftsecond, SI16 mode)
	{
		siVillageUnique	= villageunique;
		siLeftSecond	= leftsecond;
		siMode			= mode;	
	}
};

//-----------------------------------------
// ��ȭ�� ���� ���� 
//-----------------------------------------
class cltGameMsgResponse_KanghwadoReward
{
public:
	SI32	siExp;				// ȹ�� ����ġ. 
	SI32	siFameExp;			// ȹ�� �� ����ġ. 
	GMONEY	siMoney;			// ȹ�� �ڱ� 

	cltGameMsgResponse_KanghwadoReward(SI32 exp, SI32 fameexp, GMONEY money)
	{
		siExp			= exp;
		siFameExp		= fameexp;
		siMoney			= money;
	}
};

class cltGameMsgRequest_InvestmentGetInfo
{
public:
	SI32		siNPCCharUnique;

	cltGameMsgRequest_InvestmentGetInfo(SI32 npcunique)
	{
		siNPCCharUnique = npcunique ;
	}
};

class cltGameMsgResponse_InvestmentGetInfo
{
public:
	InvestmentLines		stInvestmentLines[MAX_INVESTMENT_ITEM_NUMBER];

	cltGameMsgResponse_InvestmentGetInfo(InvestmentLines *investmentlines)
	{
		for ( SI32 i = 0 ; i < MAX_INVESTMENT_ITEM_NUMBER ; i ++ )
		{
			memcpy(&stInvestmentLines[i],&investmentlines[i],sizeof(InvestmentLines)) ;
		}
	}
};

class cltGameMsgResponse_ItemInfoGet
{
public:
	cltItem		clItem;

	cltGameMsgResponse_ItemInfoGet(cltItem* pclitem)
	{
		clItem.Set(pclitem);
	}
};

class cltGameMsgRequest_AutoHunting
{
public:
	TCHAR	szSuspectName[MAX_PLAYER_NAME]; // ������ �̸�

	cltGameMsgRequest_AutoHunting(TCHAR * suspect)
	{
		MStrCpy(szSuspectName, suspect, MAX_PLAYER_NAME );
	}
};

class cltGameMsgResponse_AutoHunting
{
public:
	SI32	siTimeLimit;
	SI32	siSlot;
	SI16	siPrisonTime;
	SI16	siPrisonerPenalty;

	TCHAR	szRequestTxt[256];

	cltGameMsgResponse_AutoHunting(SI32 timelimit,SI32 slot,
								   SI16 prisontime,SI16 prisonerpenalty,const TCHAR* txt)
	{
		siTimeLimit = timelimit;
		siSlot = slot;
		siPrisonTime = prisontime;
		siPrisonerPenalty = prisonerpenalty;

		StringCchCopy(szRequestTxt, 256, txt);
	}
};

class cltGameMsgRequest_AutoHunting_Ask
{
public:
	SI32		siSlot;

	TCHAR		szAnswer[256];

	cltGameMsgRequest_AutoHunting_Ask(SI32 slot,const TCHAR* txt)
	{
		siSlot = slot;

		StringCchCopy(szAnswer, 256, txt);
	}

};

class cltGameMsgResponse_AutoHunting_Ask
{
public:
	bool		bSuccess;
	SI32		siLeft;
	SI16		siPrisonerPenalty;

	cltGameMsgResponse_AutoHunting_Ask(bool success,SI32 left,SI16 prisonerpenalty)
	{
		bSuccess = success ;

		siLeft = left;
		siPrisonerPenalty = prisonerpenalty ;
	}
};

class cltGameMsgResponse_AutoHunting_TimeUpdate
{
public:
	SI32		siMinusTime;
	SI32		siTotalTime;

	cltGameMsgResponse_AutoHunting_TimeUpdate(SI32 minustime,SI32 totaltime)
	{
		siMinusTime = minustime ;
		siTotalTime = totaltime ;
	}
};

// ��õ�� ������ �޾����� ��ü ����. 
class cltGameMsgResponse_RecommendReward
{
public:

	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ������. 
	SI16	siLevel;						// ���� �󸶰� �Ǿ� ������ �޾Ҵ°�. 
	cltItem clItem;							// ����ǰ ����. 
	SI32	siIncFameExp;
	GMONEY	siMoney;						// ����� (�ս��ڻ꿡�� ����) 

	cltGameMsgResponse_RecommendReward(TCHAR* pname, SI16 level, cltItem* pclitem, SI32 incfameexp, GMONEY money)
	{
		MStrCpy( szPersonName, pname, MAX_PLAYER_NAME );
		siLevel		= level;
		clItem.Set(pclitem);
		siIncFameExp = incfameexp;
		siMoney			= money;	
	}

};

// �� ���� ��� ���� ���� ����. 
class cltGameMsgResponse_FameLevelReward
{
public:

	TCHAR	szPersonName[MAX_PLAYER_NAME];	// ������. 
	SI16	siFameLevel;					// ������ �󸶰� �Ǿ� ������ �޾Ҵ°�. 
	cltItem clItem;							// ����ǰ ����. 

	cltGameMsgResponse_FameLevelReward(TCHAR* pname, SI16 level, cltItem* pclitem)
	{
		MStrCpy( szPersonName, pname, MAX_PLAYER_NAME );
		siFameLevel		= level;
		clItem.Set(pclitem);
	}

};


class cltGameMsgResponse_AnotherAuth
{
public:

	TCHAR		szIP[64] ;
	SYSTEMTIME	stTime;
	BOOL		bNewUser;

	cltGameMsgResponse_AnotherAuth(TCHAR * ip , SYSTEMTIME time, BOOL NewUser)
	{
		bNewUser = NewUser;
		StringCchCopy(szIP, 64, ip);
		memcpy(&stTime,&time,sizeof(SYSTEMTIME));
	}
};

class cltGameMsgResponse_NotGamePotAuth
{
public:

	cltGameMsgResponse_NotGamePotAuth()
	{
	}
};

class cltGameMsgResponse_CannotLogin_Age
{
public:

	cltGameMsgResponse_CannotLogin_Age()
	{
	}
};

class cltGameMsgResponse_CannotLogin_Error
{
public:

	cltGameMsgResponse_CannotLogin_Error()
	{
	}
};

// ���ӽ��൵�߿��� �������� üũ - PCK : 2007.09.19
class cltGameMsgResponse_GameDisconnect_Age
{
public:

	cltGameMsgResponse_GameDisconnect_Age()
	{
	}
};

class cltGameMsgResponse_GetGameMaster_ServerInfo
{
public:
	GMServerInfo		stGMServerInfo;

	cltGameMsgResponse_GetGameMaster_ServerInfo(GMServerInfo* gmserverinfo)
	{
		memcpy(&stGMServerInfo,gmserverinfo,sizeof(GMServerInfo));
	}
};

class cltGameMsgRequest_GetChangedName
{
public:
	SI32		siPage;

	cltGameMsgRequest_GetChangedName(SI32 page)
	{
		siPage = page ;
	}
};

class cltGameMsgResponse_GetChangedName
{
public:
	SI32				siResult;
	SI32				siPage;

	ChangedNameChar		stChangedNameChar[MAX_HOZO_CHANGEDNAME_LIST];

	cltGameMsgResponse_GetChangedName(SI32 result,SI32 page,ChangedNameChar * changednamechar)
	{
		siResult = result;
		siPage = page;

		//memcpy(stChangedNameChar,changednamechar,sizeof(ChangedNameChar) * MAX_HOZO_CHANGEDNAME_LIST );
		for ( int i = 0 ; i < MAX_HOZO_CHANGEDNAME_LIST ; i ++ )
		{
			stChangedNameChar[i].siDate = changednamechar[i].siDate ;

			MStrCpy(stChangedNameChar[i].szOldName, changednamechar[i].szOldName, MAX_PLAYER_NAME );
			MStrCpy(stChangedNameChar[i].szNewName, changednamechar[i].szNewName, MAX_PLAYER_NAME );
		}
	}
};


//------------------------------------------------------------------------
// ���λ��� �����Ƿ� ���� Ŭ���̾�Ʈ�� �뺸 
//------------------------------------------------------------------------
class cltGameMsgResponse_PersonalShopMakeInfo
{
public:
	TCHAR szName[MAX_PLAYER_NAME];
	SI16 siItemUnique;
	SI32 siItemNum;
	GMONEY siFee;
	SI32 siSkillLevel;
	SI32 siHand;

	cltGameMsgResponse_PersonalShopMakeInfo(TCHAR* pname, SI16 itemunique, SI32 itemnum, GMONEY fee, SI32 skilllevel, SI32 hand)
	{
		StringCchCopy(szName, MAX_PLAYER_NAME, pname);
		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		siFee			= fee;
		siSkillLevel	= skilllevel;
		siHand			= hand;
	}
};

//------------------------------------
//�߿��� ������ �޾Ҵ�.
//-------------------------------------
class cltGameMsgResponse_NoticeAdmin
{
public:
	TCHAR szText[256] ;

	cltGameMsgResponse_NoticeAdmin(TCHAR * txt)
	{
		MStrCpy(szText , txt , 256) ;
	}
};

//--------------------------
// �б� �̺�Ʈ
//-----------------------
class cltGameMsgRequest_SetSchoolEvent
{
public:
	SI32 siUnique;
	SI32 siGrade;
	SI32 siClass;

	cltGameMsgRequest_SetSchoolEvent(SI32 _unique , SI32 _grade , SI32 _class)
	{
		siUnique = _unique ;
		siGrade = _grade ;
		siClass = _class ;
	}
};

//--------------------------------
// �ν��Ͻ� ���� ����
//---------------------------------
class cltGameMsgResponse_InstanceMapInfo
{
public:
	SI32 siLeftTime;
	SI32 siLeftMon;

	cltGameMsgResponse_InstanceMapInfo(SI32 lefttime,SI32 leftmon)
	{
		siLeftTime = lefttime ;
		siLeftMon = leftmon ;
	}
};

class cltGameMsgRequest_Goonzu_SetMinister
{
public:
	SI32	siMinisterInx;
	TCHAR	szCharName[MAX_PLAYER_NAME];

	bool	bLeave;

	cltGameMsgRequest_Goonzu_SetMinister(SI32 index,TCHAR* name,bool leave)
	{
		siMinisterInx = index ;
		MStrCpy(szCharName,name,MAX_PLAYER_NAME);

		bLeave = leave ; // true�� ���ӽ�Ű�� , false�� �Ӹ��ϱ�
	}
};

class cltGameMsgResponse_Goonzu_SetMinister
{
public:
	SI32	siResult; // 1�� ���� �������� ����

	SI32	siMinisterInx;
	TCHAR	szCharName[MAX_PLAYER_NAME];

	cltGameMsgResponse_Goonzu_SetMinister(SI32 result,SI32 index , TCHAR* name)
	{
		siResult = result;

		siMinisterInx = index ;
		MStrCpy(szCharName,name,MAX_PLAYER_NAME);
	}
};

class cltGameMsgRequest_Goonzu_SetLiquidation
{
public:
	SI32	siLiquidationVillageNumber;

	cltGameMsgRequest_Goonzu_SetLiquidation( SI32 LiquidationVillageNumber )
	{
		siLiquidationVillageNumber = LiquidationVillageNumber;
	}
};



class cltGameMsgRequest_Goonzu_GetBonusTime
{
public:
	cltGameMsgRequest_Goonzu_GetBonusTime()
	{		
	}
};

class cltGameMsgResponse_Goonzu_GetBonusTime
{
public:
	SI16 siBonusTime;
	SI16 siMakeBonusTime;
	
	bool bChangeAble;

	cltGameMsgResponse_Goonzu_GetBonusTime(SI16 BonusTime , SI16 MakeBonusTime, bool ChangeAble )
	{		
		siBonusTime = BonusTime;
		siMakeBonusTime = MakeBonusTime;
		bChangeAble = ChangeAble;
	}
};

class cltGameMsgRequest_Goonzu_SetBonus
{
public:
	SI16 siBonusTime;	
	SI16 siMakeBonusTime;

	cltGameMsgRequest_Goonzu_SetBonus( SI16 BonusTime , SI16 MakeBonusTime )
	{		
		siBonusTime = BonusTime;
		siMakeBonusTime = MakeBonusTime;
	}
};

class cltGameMsgResponse_Goonzu_SetBonus
{
public:
	cltGameMsgResponse_Goonzu_SetBonus()
	{		
	}
};


class cltGameMsgRequest_BlackArmy_Apply
{
public :
	cltGameMsgRequest_BlackArmy_Apply()
	{
	}
	
};

class cltGameMsgResponse_BlackArmy_Apply
{
public :
	SI32 siResult; 
	SI32 siApplyUnique;

	cltGameMsgResponse_BlackArmy_Apply(SI32 Result, SI32 ApplyUnique)
	{
		siResult = Result;
		siApplyUnique = ApplyUnique;
	}
};

class cltGameMsgRequest_BlackArmy_RankInfo
{
public :
	SI32 siWarMapIndex;

	cltGameMsgRequest_BlackArmy_RankInfo(SI32 warmapindex)
	{
		siWarMapIndex = warmapindex;
	}

};

class cltGameMsgResponse_BlackArmy_RankInfo
{
public :
	SI32 siResult; 
	SI32 siWarMapIndex;
	SI32 siPoints[MAX_WARRANK_PERSON_PER_MAP];
	TCHAR szPlayes[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];

	cltGameMsgResponse_BlackArmy_RankInfo(SI32 warmapindex, SI32 *points, TCHAR **players)
	{
		siWarMapIndex = warmapindex;
		memcpy(siPoints, points, sizeof(SI32) * MAX_WARRANK_PERSON_PER_MAP);
		memcpy(szPlayes, players, sizeof(TCHAR) * MAX_WARRANK_PERSON_PER_MAP * MAX_PLAYER_NAME);
	}
};

class cltGameMsgRequest_BlackArmy_WarpToGate
{
public :
	SI32 siGateUnique;

	cltGameMsgRequest_BlackArmy_WarpToGate(SI32 gateunique)
	{
		siGateUnique = gateunique;
	}

};

class cltGameMsgResponse_BlackArmy_MVPEffect
{
public :
	SI16 siCharUnique;		// MVP�� �� ĳ����

	cltGameMsgResponse_BlackArmy_MVPEffect(SI16 charunique)
	{
		siCharUnique = charunique;
	}
};

class cltGameMsgResponse_ServerTime
{
public :
	_SYSTEMTIME sTime;

	cltGameMsgResponse_ServerTime(_SYSTEMTIME time)
	{
		sTime = time;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_Hit
//
// Last Modified 	: 2007 / 03 / 09
// Created		 	: �豤��
//
// Function			: Ŭ���̾�Ʈ���� Ÿ�ݿ�û�� ������ �Ѵ�.
//
//***************************************************************************************************
class cltGameMsgRequest_Hit
{
public :

	// Ÿ���� �õ��ϴ� ĳ����
	SI32				siCharID;
	// ������ ���� ���
	cltAttackTarget		clAttackTarget;

	cltGameMsgRequest_Hit( SI32 CharID, cltAttackTarget* pAttackTarget ) 
	{
		siCharID = CharID;
		clAttackTarget.Set( pAttackTarget );
	}
	~cltGameMsgRequest_Hit()
	{
	}

	SI32 GetCharID()
	{
		return siCharID;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_SetBullet
//
// Last Modified 	: 2007 / 03 / 09
// Created		 	: �豤��
//
// Function			: Ŭ���̾�Ʈ���� ������ ���Ÿ� ������ ��û�� �Ѵ�.
//
//***************************************************************************************************
class cltGameMsgRequest_SetBullet
{
public :

	// Ÿ���� �õ��ϴ� ĳ����
	SI32				siCharID;
	SI32				siBulletUnique;
	SI32				siMagicKind;
	SI32				siPower;
	cltPos				clTileStartPos;
	cltPos				clDotStartPos;
	cltAttackTarget		clAttackTarget;
	cltPos				clDotDestPos;

	cltGameMsgRequest_SetBullet( SI32  CharID,
		SI32  BulletUnique,
		SI32  MagicKind,
		SI32  Power,
		const cltPos* pTileStartPos, 
		const cltPos* pDotStartPos, 
		const cltAttackTarget* pAttackTarget, 
		const cltPos* pDotDestPos ) 
	{
		siCharID	   = CharID;
		siBulletUnique = BulletUnique;
		siMagicKind	   = MagicKind;
		siPower		   = Power;

		clTileStartPos.Set( pTileStartPos->siX, pTileStartPos->siY );
		clDotStartPos.Set( pDotStartPos->siX, pDotStartPos->siY );
		clAttackTarget.Set( pAttackTarget );
		clDotDestPos.Set( pDotDestPos->siX, pDotDestPos->siY );
	}
};

class cltGameMsgResponse_KingGuriInfo
{
public:

	SI32	siCmd;	// ������ ��Ȳ 0:���� 1: ���� 2:��
	DWORD	dwLeftTime;
	TCHAR	szAreaNmae[MAX_KINGGURI_NUM][32];
	TCHAR	szUserName[MAX_PLAYER_NAME];
	
	/// ���� ��ǥ
	POINT m_ptPosition[MAX_POSITION_NUM];
	
	//[�߰� : Ȳ���� 2007. 11. 13 ��� �������� ���� ������ �ε�����ȣ]
	SI32 m_siAreaIndex[MAX_KINGGURI_NUM];

	//[�߰� : Ȳ���� 2007. 11. 13 ��� �������� ���̰� ���� ������ ������ ���� ����.]
	TCHAR szBuffer[MAX_MESSAGE_SIZE];

	cltGameMsgResponse_KingGuriInfo( SI32 CMD, DWORD LeftTime, TCHAR AreaName[MAX_KINGGURI_NUM][32], TCHAR* UserName, POINT ptPosition[MAX_POSITION_NUM], SI32 siAreaIndex[MAX_KINGGURI_NUM])
	{

		siCmd = CMD;
		dwLeftTime = LeftTime;
		for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
		{
			StringCchCopy( szAreaNmae[i], 32, AreaName[i] );
		}

		if( NULL == UserName)
		{
			StringCchCopy( szUserName, MAX_PLAYER_NAME, "" );
		}
		else
		{
			StringCchCopy( szUserName, MAX_PLAYER_NAME, UserName );
		}
		
		memcpy(m_ptPosition,  ptPosition,  sizeof(m_ptPosition));
		memcpy(m_siAreaIndex, siAreaIndex, sizeof(m_siAreaIndex));

	}

	cltGameMsgResponse_KingGuriInfo( SI32 _CMD, TCHAR _Buffer[MAX_MESSAGE_SIZE])
	{
		siCmd = _CMD;
		StringCchCopy( szBuffer, MAX_MESSAGE_SIZE, _Buffer );
	}
};

//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ �޽��� �߰�.]
class cltGameMsgResponse_SantaRaccoonInfo
{
public:

	SI32	siCmd;	// ������ ��Ȳ 0:���� 1: ���� 2:��
	DWORD	dwLeftTime;
	TCHAR	szAreaNmae[MAX_SANTARACCOON_NUM][32];
	TCHAR	szUserName[MAX_PLAYER_NAME];

	/// ���� ��ǥ
	POINT m_ptPosition[MAX_SANTARACCOON_POSITION_NUM];

	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ������ ���� ������ �ε�����ȣ]
	SI32 m_siAreaIndex[MAX_SANTARACCOON_POSITION_NUM];

	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ������ ���̰� ���� ������ ������ ���� ����.]
	TCHAR szBuffer[MAX_SANTARACCOON_MESSAGE_SIZE];

	cltGameMsgResponse_SantaRaccoonInfo( SI32 CMD, DWORD LeftTime, TCHAR AreaName[MAX_SANTARACCOON_NUM][32], TCHAR* UserName, POINT ptPosition[MAX_SANTARACCOON_POSITION_NUM], SI32 siAreaIndex[MAX_SANTARACCOON_POSITION_NUM])
	{
		siCmd = CMD;
		dwLeftTime = LeftTime;
		for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
		{
			StringCchCopy( szAreaNmae[i], 32, AreaName[i] );
		}

		if( NULL == UserName)
		{
			StringCchCopy( szUserName, MAX_PLAYER_NAME, "" );
		}
		else
		{
			StringCchCopy( szUserName, MAX_PLAYER_NAME, UserName );
		}

		memcpy(m_ptPosition,  ptPosition,  sizeof(m_ptPosition));
		memcpy(m_siAreaIndex, siAreaIndex, sizeof(m_siAreaIndex));

	}

	cltGameMsgResponse_SantaRaccoonInfo( SI32 _CMD, TCHAR _Buffer[MAX_SANTARACCOON_POSITION_NUM])
	{
		siCmd = _CMD;
		StringCchCopy( szBuffer, MAX_SANTARACCOON_POSITION_NUM, _Buffer );
	}
};

class cltGameMsgResponse_KiteRaccoonInfo
{
public:
	SI08	m_siType;						// KITERACCOON_EVENT_START, KITERACCOON_EVENT_KILL, KITERACCOON_EVENT_END 
	SI32	m_siMonsterKind;				// ���� ����ũ
	SI32	m_siItemUnique;					// ������ ����ũ
	
	TCHAR	m_tszUserName[MAX_PLAYER_NAME];	// �ɸ��� �̸�

	
	cltGameMsgResponse_KiteRaccoonInfo( SI08 siType, SI32 siMonsterKind=0, SI32 siItemUnique=0, TCHAR *ptszUserName=NULL )
	{
		m_siType			= siType;
		m_siMonsterKind		= siMonsterKind;
		m_siItemUnique		= siItemUnique;

		ZeroMemory( m_tszUserName, MAX_PLAYER_NAME );

		if ( ptszUserName )
		{
			StringCchCopy( m_tszUserName, MAX_PLAYER_NAME, ptszUserName );
		}
	}

};


class cltGameMsgRequest_FileCRCCheck
{
public:
	SI32			siCount;
	NCRCFileCheck	CheckFileList[MAX_CRCFILECHECK_COUNT];

	cltGameMsgRequest_FileCRCCheck()
	{
		ZeroMemory(this, sizeof(*this));
	}

	SI32 GetSize()
	{
		return sizeof(siCount) + sizeof(NCRCFileCheck) * siCount;
	}
};

class cltGameMsgResponse_FileCRCCheck
{
public:
	SI32	siResult;

	cltGameMsgResponse_FileCRCCheck( SI32 in_siResult )
	{
		siResult = in_siResult;
	}
};


//[����] ���� �̺�Ʈ�� ���õ� ������ Ŭ�� ������ ��û ��Ŷ. => 2008-6-20
class cltGameMsgRequest_Server_Event_Rank_Info
{
public:
	cltGameMsgRequest_Server_Event_Rank_Info()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

//[����] ���� �̺�Ʈ�� ���õ� ������ Ŭ��� ���� ��Ŷ. => 2008-6-19
class cltGameMsgResponse_Server_Event_Rank_Info
{
public:
	CNServerEvent_Rank_Record	m_clServerEvent_Rank_Record;
	SI16						m_ServerEventBufKind;				// ���� �̺�Ʈ ���� ���� ����(0�̸� ����, 0ũ�� �ִ�.)

	cltGameMsgResponse_Server_Event_Rank_Info()
	{	
		ZeroMemory(this, sizeof(*this));
	}
	cltGameMsgResponse_Server_Event_Rank_Info(CNServerEvent_Rank_Record& _clServerEvent_Rank_Record, SI16 _ServerEventBufKind)
	{
		ZeroMemory(this, sizeof(*this));
		memcpy(&m_clServerEvent_Rank_Record, &_clServerEvent_Rank_Record, sizeof(m_clServerEvent_Rank_Record));

		m_ServerEventBufKind = _ServerEventBufKind;
	}
};


//[����] ���� �̺�Ʈ�� ������ŷ ������ ��� Ŭ�� ���� ��Ŷ.(���� ���� ��ü�� ��´�) => 2008-6-19
class cltGameMsgResponse_Server_Event_Server_Info
{
public:
	CNServerRankInfo	m_clServerRankInfo[SERVER_MAX_NUM];
	
	cltGameMsgResponse_Server_Event_Server_Info(CNServerRankInfo& _clServerRankInfo)
	{
		memcpy(&m_clServerRankInfo, &_clServerRankInfo, sizeof(m_clServerRankInfo));
	}
};

//[����] ���� �̺�Ʈ�� ������ŷ ������ ��� Ŭ�� ���� ��Ŷ.(���� ���� ��ü�� ��´�) => 2008-6-19
class cltGameMsgResponse_Server_Event_Daily_Server_Info
{
public:
	CNServerDailyRankInfo	m_clServerDailyRankInfo[SERVER_MAX_NUM];

	cltGameMsgResponse_Server_Event_Daily_Server_Info(CNServerDailyRankInfo& _clServerDailyRankInfo)
	{
		memcpy(&m_clServerDailyRankInfo, &_clServerDailyRankInfo, sizeof(m_clServerDailyRankInfo));
	}
};


//[����] ���� �̺�Ʈ�� ���η�ŷ ������ ��� Ŭ�� ���� ��Ŷ.(���� ���� ��ü�� ��´�) => 2008-6-19
class cltGameMsgResponse_Server_Event_Personal_Info
{
public:
	CNPersonalRankInfo	m_clPersonalRankInfo[SERVER_MAX_NUM];

	cltGameMsgResponse_Server_Event_Personal_Info(CNPersonalRankInfo& _clPersonalRankInfo)
	{
		memcpy(&m_clPersonalRankInfo, &_clPersonalRankInfo, sizeof(m_clPersonalRankInfo));
	}
};

//[����] ���� �̺�Ʈ�� ���η�ŷ ������ ��� Ŭ�� ���� ��Ŷ.(���� ���� ��ü�� ��´�) => 2008-6-19
class cltGameMsgResponse_Server_Event_InstanceMap_Bonus_Figure
{
public:
	SI16	m_siBonusFigure[4];

	cltGameMsgResponse_Server_Event_InstanceMap_Bonus_Figure(SI16*	_psiBonusFigure)
	{
		memcpy(&m_siBonusFigure, _psiBonusFigure, sizeof(m_siBonusFigure));
	}
};

// [����] ���� �̺�Ʈ ����Ʈ ���� ������ ��û��
class cltGameMsgRequest_Server_Event_Quest_Start
{
public:
	cltGameMsgRequest_Server_Event_Quest_Start()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

// [����] ���� �̺�Ʈ ����Ʈ ���� ������ ����
class cltGameMsgResponse_Server_Event_Quest_Start
{
public:
	CNServerEvent_QuestData	m_clQuestData;		// ����Ʈ ����	
	SI16					m_siMaxCharacter;	// �� �̺�Ʈ�� ��� ���ڰ� ����Ʈ�� ���ԵǴ°�?
	SI32					m_siNowAmount;		// ���� ��� �ʿ� ������ ä���°�?
	bool					m_bCharacter[Const_ServerEvent_Max_QuestCharacter];
	
	cltGameMsgResponse_Server_Event_Quest_Start( CNServerEvent_QuestData* pclQuestData, SI16 siMaxCharacter, SI32 siNowAmount, bool bCharacter[] )
	{
		m_clQuestData.SetServerEvent_QuestData( pclQuestData );

		m_siMaxCharacter	= siMaxCharacter;
		m_siNowAmount		= siNowAmount;

		memcpy( m_bCharacter, bCharacter, sizeof(m_bCharacter) );
	}

};

// [����] ���� �̺�Ʈ ����Ʈ�� ����Ǵ� ������ ����
class cltGameMsgResponse_Server_Event_Quest_RunInfo
{
public:
	SI32	m_siLimiteMinute;		// ���� �̺�Ʈ ����Ʈ�� ��� ���Ҵ°�?

	SI32	m_siNowAmount;			// ���� ����Ƚ��

	cltGameMsgResponse_Server_Event_Quest_RunInfo( SI32 siLimitMinute, SI32 siNowAmount )
	{
		m_siLimiteMinute	= siLimitMinute;
		m_siNowAmount		= siNowAmount;
	}
};

// [����] ���� �̺�Ʈ ����Ʈ Ŭ���� ���¸� ����
class cltGameMsgResponse_Server_Event_Quest_ClearStatus
{
public:
	SI16	m_siMessageType;	// ���� �޽����� � ��Ȳ���� �߻��Ǵ� �޽��� �ΰ�? /* SERVEREVENT_MESSAGETYPE */
	SI16	m_siCharacterIndex;	// ����Ʈ�� Ŭ���� �ؼ� ��� ����

	cltGameMsgResponse_Server_Event_Quest_ClearStatus( SI16 siMessageType, SI16 siCharacterIndex=-1 )
	{
		m_siMessageType		= siMessageType;
		m_siCharacterIndex	= siCharacterIndex;
	}
	
};

// [����] ���� �̺�Ʈ ����Ʈ Ŭ���� ���¸� ����
class cltGameMsgResponse_EventTime_Update
{
public:
	TCHAR			m_szEventName[48];
	bool			m_bEventActivated;

	cltGameMsgResponse_EventTime_Update( TCHAR* pszEventName, bool bEventActivated )
	{
		StringCchCopy(m_szEventName, sizeof(m_szEventName), pszEventName);
		m_bEventActivated	= bEventActivated;
	}

};

//-----------------------------------------------------------------------------------------------------
// ************************************���μ��� üũ �������******************************************
//
// �������� Response�� ���� ��� ����Ÿ�� ����̸��� �����ָ�
// Ŭ���̾�Ʈ���� Request�� ���� ���� ��� ������ �ƾ�巹���� �����ش�
// �Ϲ����� 1.Request 2.Response�� �ƴ� 1.Response 2.Request�� ������
//-----------------------------------------------------------------------------------------------------


// [����] ���μ��� üũ ����
class cltGameMsgRequest_CheckProcess
{
public:
	TCHAR	m_szMacAddress[20];	// �� ��巹��
	SI16	m_siProcessCount;	// ��� ����

	cltGameMsgRequest_CheckProcess( void )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_CheckProcess) );
	}

	cltGameMsgRequest_CheckProcess( TCHAR* pszMacAddress, SI16 siProcessCount )
	{
		StringCchCopy( m_szMacAddress, 20, pszMacAddress );
		
		m_siProcessCount = siProcessCount;
	}

};

// [����] ���μ��� üũ ��û
class cltGameMsgResponse_CheckProcess
{
public:
	TCHAR	m_szModuleName[64];	// üũ�Ϸ��� ��� �̸�
	SI16	m_siType;			// üũ Ÿ��

	cltGameMsgResponse_CheckProcess( void )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_CheckProcess) );
	}

	cltGameMsgResponse_CheckProcess( TCHAR* pszModuleName, SI16 siType )
	{
		StringCchCopy( m_szModuleName, 64, pszModuleName );

		m_siType = siType;
	}

};

// [����] ���μ��� üũ �����
class cltGameMsgResponse_CheckProcess_Result
{
public:
	TCHAR	m_szModuleName[64];	// �˻��� ����̸�(��ũ�� �˻綧�� ����)
	SI16	m_siMultiList[20];	// ��ƼŬ���̾�Ʈ ����Ʈ
	SI16	m_siType;			// üũ Ÿ��

	cltGameMsgResponse_CheckProcess_Result( void )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_CheckProcess_Result) );
	}

	cltGameMsgResponse_CheckProcess_Result( TCHAR* pszModuleName, SI16* psiMultiList, SI16 siType )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_CheckProcess_Result) );

		if ( pszModuleName )
		{
			StringCchCopy( m_szModuleName, 64, pszModuleName );
		}

		if ( psiMultiList )
		{
			memcpy( m_siMultiList, psiMultiList, sizeof(m_siMultiList) );
		}

		m_siType = siType;
	}

};

// [����] ���� ����Ʈ ��û. 
class cltGameMsgResponse_Question_List_Get
{
public:
	bool	m_bAleadyAnswer[ SENDMSG_LIST_NUM ];								// �亯�ڰ� �ִ��� ������.
	SI32	m_siQuestionPersonID[ SENDMSG_LIST_NUM ];							// ������ personID
	TCHAR	m_szQuestionTitle[ SENDMSG_LIST_NUM ][ TITLE_LETTER_NUM ];			// ����
	TCHAR	m_szName[ SENDMSG_LIST_NUM ][ MAX_PLAYER_NAME ];

	cltGameMsgResponse_Question_List_Get( SI32* _psiQuestionPersonID, TCHAR** _pszQuestionTitle, TCHAR** _pszName, bool* _pbAleadyAnswer )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Question_List_Get) );

		memcpy(m_siQuestionPersonID, _psiQuestionPersonID,	sizeof(m_siQuestionPersonID));
		memcpy(m_szQuestionTitle,	 _pszQuestionTitle,		sizeof(m_szQuestionTitle)	);
		memcpy(m_szName,			 _pszName,				sizeof(m_szName)			);
		memcpy(m_bAleadyAnswer,		 _pbAleadyAnswer,		sizeof(m_bAleadyAnswer)		);
	}
};


// [����] ���� ����Ʈ ��û. 
class cltGameMsgRequest_Add_Question
{
public:
	TCHAR	m_szQuestionTitle[ TITLE_LETTER_NUM ];					// ����
	TCHAR	m_szQuestionContents[ CONTENTS_LETTER_NUM ];			// ����.

	cltGameMsgRequest_Add_Question( TCHAR* _pszQuestionTitle, TCHAR* _pszQuestionContents )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Add_Question) );

		memcpy(m_szQuestionTitle,	 _pszQuestionTitle,		sizeof(m_szQuestionTitle)	);
		memcpy(m_szQuestionContents, _pszQuestionContents,	sizeof(m_szQuestionContents));
	}
};

// [����] �亯�� ���.
class cltGameMsgRequest_Add_Answer
{
public:
	SI32	m_siQuestionPersonID;

	cltGameMsgRequest_Add_Answer( SI32 _siQuestionPersonID )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Add_Answer) );

		m_siQuestionPersonID = _siQuestionPersonID;
	}
};

class cltGameMsgResponse_Add_Answer
{
public:
	TCHAR	m_szName[MAX_PLAYER_NAME];
	TCHAR	m_szQuestionTitle[ TITLE_LETTER_NUM ];					// ����
	SI32	m_siQuestionPersonID;									// ������ personID
	
	cltGameMsgResponse_Add_Answer( const TCHAR* _pszName, TCHAR* _pszQuestionTitle, SI32 _siQuestionPersonID )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Add_Answer) );

		memcpy(m_szName,			_pszName,			sizeof(m_szName)		 );
		memcpy(m_szQuestionTitle,	_pszQuestionTitle,	sizeof(m_szQuestionTitle));
		
		m_siQuestionPersonID = _siQuestionPersonID;
	}
};

// [����] �亯�Ϸ�.
class cltGameMsgRequest_Add_Answer_Complete
{
public:
	SI32	m_siQuestionPersonID;									// ������ personID
    TCHAR	m_szQuestionTitle[ TITLE_LETTER_NUM ];					// ����
	TCHAR	m_szQuestionContents[ CONTENTS_LETTER_NUM ];			// ����.


	cltGameMsgRequest_Add_Answer_Complete( SI32 _siQuestionPersonID, TCHAR* _pszQuestionTitle, TCHAR* _pszQuestionContents )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Add_Answer_Complete) );

		m_siQuestionPersonID = _siQuestionPersonID;
		memcpy(m_szQuestionTitle,	 _pszQuestionTitle,		sizeof(m_szQuestionTitle)	);
		memcpy(m_szQuestionContents, _pszQuestionContents,	sizeof(m_szQuestionContents));
	}
};

// [����] �Ϸ�� �亯 �����ڿ��� �����ֱ�.
class cltGameMsgResponse_Add_Answer_Complete
{
public:
	SI32	m_siAnswerPersonID;										// �亯�� personID.
	TCHAR	m_szAnswerCharName[ CONTENTS_LETTER_NUM ];				// �亯�� �̸�.
	TCHAR	m_szQuestionTitle[ TITLE_LETTER_NUM ];					// ����.
	TCHAR	m_szQuestionContents[ CONTENTS_LETTER_NUM ];			// ����.
	
	cltGameMsgResponse_Add_Answer_Complete( SI32 _siAnswerPersonID, TCHAR* _szAnswerCharName, TCHAR* _pszQuestionTitle, TCHAR* _pszQuestionContents )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Add_Answer_Complete) );

		m_siAnswerPersonID = _siAnswerPersonID;
		memcpy(m_szAnswerCharName,	 _szAnswerCharName,		sizeof(m_szAnswerCharName)	);
		memcpy(m_szQuestionTitle,	 _pszQuestionTitle,		sizeof(m_szQuestionTitle)	);
		memcpy(m_szQuestionContents, _pszQuestionContents,	sizeof(m_szQuestionContents));
	}
};


// [����] �亯�Ϸ�.
class cltGameMsgRequest_Add_Answer_Complete_Result
{
public:
	bool	m_bResult;											// true : ���� , false : �Ҹ���

	SI32	m_siAnswerCharPersonID;									// �亯�� personID
	
	cltGameMsgRequest_Add_Answer_Complete_Result( bool	_bResult, SI32 _siAnswerCharPersonID )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Add_Answer_Complete_Result) );

		m_bResult		       = _bResult;
		m_siAnswerCharPersonID = _siAnswerCharPersonID;
	}
};

// [����] �Ϸ�� �亯 �����ڿ��� �����ֱ�.
class cltGameMsgResponse_Add_Answer_Complete_Result
{
public:
	bool	m_bResult;											// true : ���� , false : �Ҹ���
	
	SI32	m_siItemUnique;										// ���� ������ ����ũ.
	SI16	m_siItemNum;										// ������ ����.

	TCHAR	m_szQuestionCharName[ TITLE_LETTER_NUM ];			// ������ �̸�
		
	cltGameMsgResponse_Add_Answer_Complete_Result( bool _bResult, SI32 _siItemUnique, SI16 _siItemNum, TCHAR* _szQuestionCharName )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Add_Answer_Complete_Result) );
		
		m_bResult	   = _bResult;
		m_siItemUnique = _siItemUnique;	
		m_siItemNum	   = _siItemNum;	

		memcpy(m_szQuestionCharName, _szQuestionCharName,	sizeof(m_szQuestionCharName));
		

	}
};



// [����] ���� ���� ��û. 
class cltGameMsgRequest_Question_Contents_Get
{
public:
	SI32	m_siPersonID;

	cltGameMsgRequest_Question_Contents_Get( SI32	_siPersonID )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Question_Contents_Get) );

		m_siPersonID = _siPersonID;
	}
};

// [����] ���� ���� �ֱ�. 
class cltGameMsgResponse_Question_Contents_Get
{
public:
	TCHAR	m_szQuestionContents[ CONTENTS_LETTER_NUM ];			// ����.
	
	cltGameMsgResponse_Question_Contents_Get( TCHAR* _pszQuestionContents )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Question_Contents_Get) );

		memcpy(m_szQuestionContents, _pszQuestionContents,	sizeof(m_szQuestionContents));
	}
};


class cltGameResponse_SetMute
{
public:
    NTCHARStringName		m_kCharName;
	SYSTEMTIME				m_stMuteTime;
	bool					m_bMaster;

	cltGameResponse_SetMute( const TCHAR* pszCharName, SYSTEMTIME* pstMuteTime, bool bMaster)
	{
		m_kCharName		= pszCharName;
		memcpy(&m_stMuteTime, pstMuteTime, sizeof(m_stMuteTime));

		m_bMaster		= bMaster;
	}
};

class cltGameResponse_MuteList
{
public:
	NTCHARStringName	m_szPersonNames[100];		// ä�ú�� ����
	SI16				m_siCount;

	cltGameResponse_MuteList( )
	{
		ZeroMemory( this, sizeof(cltGameResponse_MuteList) );
	}
};


//[����] ������ ������ Ÿ�Ժ� ����Ʈ ���� ��û.
class cltGameMsgRequest_Elixir_Npc_Item_Type_List_Get
{
public:
	SI32	m_siItemType;

	cltGameMsgRequest_Elixir_Npc_Item_Type_List_Get( SI32 _siItemType )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Elixir_Npc_Item_Type_List_Get) );

		m_siItemType = _siItemType;
	}
};

#define ELIXIR_LIST_NUM	48
class cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get
{
public:
	SI32	m_siItemUnique[ELIXIR_LIST_NUM];
	SI32	m_siWaterNum[ELIXIR_LIST_NUM];

	cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get) );
	}

	cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get( SI32*	_psiItemUnique, SI32* _psiWaterNum )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get) );
		
		memcpy(m_siItemUnique,	_psiItemUnique, sizeof(m_siItemUnique));
		memcpy(m_siWaterNum,	_psiWaterNum,	sizeof(m_siWaterNum));
	}
};


// ����ϴ� ���� �������� ����ũ.
class cltGameMsgRequest_Elixir_Npc_Change_Item
{
public:
	SI32	m_siItemUnique;
	SI32	m_siItemPos;

	cltGameMsgRequest_Elixir_Npc_Change_Item( SI32 _siItemUnique, SI32	_siItemPos )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Elixir_Npc_Change_Item) );

		m_siItemUnique  = _siItemUnique;
		m_siItemPos		= _siItemPos;
	}
};

//[����] ������ ��� ����.
class cltGameMsgRequest_Elixir_Set
{
public:
	SI32				m_siElixirItemUnique;	// ����ϴ� ������ �������� ����ũ.
	SI32				m_siElixirItemPos;		// ����ϴ� ������ �������� �κ� ��ġ.
	
	SI32				m_siWaterItemUnique;	// ����ϴ� ������ ��� �������� ����ũ.
	SI32				m_siWaterItemPos;		// ����ϴ� ������ ��� �������� �κ� ��ġ.
	
	SI32				m_siWaterItemNum;		// ����ϴ� ������ ��� �������� ����.

	cltElixir_Info		m_pcltElixirInfo;		// ������ ������ �������ͽ� ����.

	bool				m_bElixirStart;			// �������� ó�� ����ϴ°�.	
	
	cltGameMsgRequest_Elixir_Set( cltElixir* _pclElixir )
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Elixir_Set) );
		
		m_pcltElixirInfo.m_siEndMinuteVary	= _pclElixir->GetMinuteVary();
		m_pcltElixirInfo.m_uiMultiple 		= _pclElixir->GetMultiple();
		m_pcltElixirInfo.m_siPoint	  		= _pclElixir->GetPoint();
		m_pcltElixirInfo.m_siStr	  		= _pclElixir->GetStr();
		m_pcltElixirInfo.m_siDex	  		= _pclElixir->GetDex();
		m_pcltElixirInfo.m_siVit	  		= _pclElixir->GetVit();
		m_pcltElixirInfo.m_siMag	  		= _pclElixir->GetMag();
		m_pcltElixirInfo.m_siHnd	  		= _pclElixir->GetHnd();
		m_pcltElixirInfo.m_siWis	  		= _pclElixir->GetWis();
	}
		
	cltGameMsgRequest_Elixir_Set(	cltElixir_Info*	_pcltElixirInfo,
									SI32 			_siElixirItemPos	= 0, 
									SI32 			_siElixirItemUnique	= 0,
									SI32 			_siWaterItemPos		= 0,  
									SI32 			_siWaterItemUnique	= 0,
									SI32 			_siWaterItemNum		= 0,									
									bool			_bElixirStart		= false		)
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Elixir_Set) );

		_pcltElixirInfo ? memcpy( &m_pcltElixirInfo, _pcltElixirInfo, sizeof(m_pcltElixirInfo) ) : 0;

		m_siElixirItemPos    = _siElixirItemPos;   		
		m_siElixirItemUnique = _siElixirItemUnique;	

		m_siWaterItemPos    = _siWaterItemPos;   		
		m_siWaterItemUnique = _siWaterItemUnique;	

		m_siWaterItemNum	= _siWaterItemNum;

		m_bElixirStart = _bElixirStart;
	}
};

class cltGameMsgResponse_Elixir_Set
{
public:
	SI32				m_siCharUnique;
	cltElixir_Info		m_pcltElixirInfo;

	cltGameMsgResponse_Elixir_Set( SI32	_siCharUnique, cltElixir_Info* _pcltElixirInfo )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Elixir_Set) );

		m_siCharUnique = _siCharUnique;
		memcpy( &m_pcltElixirInfo, _pcltElixirInfo, sizeof(m_pcltElixirInfo) );
	}
};




//	[��ȣ_BALANCECURRENCY] ��밡����ȭ�� ���� Server -> Client
class cltGameMsgResponse_BalanceCanUseCurrency
{
public:
	GMONEY	m_siCanUseMoney;
	bool	m_bNeedShowMSG;	// ������밡�� �ݾ��� Ŭ���̾�Ʈ���� �����ٰ��ΰ�

	cltGameMsgResponse_BalanceCanUseCurrency(GMONEY siCanUseMoney, bool bNeedShowMSG = false)
	{
		ZeroMemory(this, sizeof(*this));

		m_siCanUseMoney = siCanUseMoney;
		m_bNeedShowMSG  = bNeedShowMSG;
	}
};
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
// ������ ���� �Ѵ� .
class cltGameMsgRequest_SetRaccoonEventToGoonzu
{
public:
	cGoonzuRaccoonEventData	m_GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT];

	cltGameMsgRequest_SetRaccoonEventToGoonzu(cGoonzuRaccoonEventData* pGoonzuRaccoonEventData)
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_SetRaccoonEventToGoonzu) );

		memcpy(m_GoonzuRaccoonEventData,	pGoonzuRaccoonEventData,	sizeof(m_GoonzuRaccoonEventData));
	}
};
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
class cltGameMsgResponse_SetRaccoonEventToGoonzu{
public:
	cGoonzuRaccoonEventData	m_GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT];

	cltGameMsgResponse_SetRaccoonEventToGoonzu(cGoonzuRaccoonEventData* pGoonzuRaccoonEventData)
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_SetRaccoonEventToGoonzu) );

		memcpy(m_GoonzuRaccoonEventData,	pGoonzuRaccoonEventData,	sizeof(m_GoonzuRaccoonEventData));
	}
};
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
// ���̾�α׸� ���鼭 ������ ������´� .
class cltGameMsgRequest_GoonzuRaccoonEventInfo
{
public:
	SI32 m_siPersonID	;
	cltGameMsgRequest_GoonzuRaccoonEventInfo()
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_GoonzuRaccoonEventInfo) );
	}
	cltGameMsgRequest_GoonzuRaccoonEventInfo(SI32 siPersonID)
	{

		m_siPersonID	=	siPersonID	;
	}
};
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
class cltGameMsgResponse_GoonzuRaccoonEventInfo
{
public:
	cGoonzuRaccoonEventData	m_GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT];

	cltGameMsgResponse_GoonzuRaccoonEventInfo(cGoonzuRaccoonEventData* pGoonzuRaccoonEventData)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_GoonzuRaccoonEventInfo) );

		memcpy(m_GoonzuRaccoonEventData,	pGoonzuRaccoonEventData,	sizeof(m_GoonzuRaccoonEventData));
	}
};
//[����] ������� �̵� 
class cltGameMsgRequest_GoRaccoonWorld
{
public:
	SI32 m_siPersonID	;
	cltGameMsgRequest_GoRaccoonWorld()
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_GoRaccoonWorld) );
	}
	cltGameMsgRequest_GoRaccoonWorld(SI32 siPersonID)
	{

		m_siPersonID	=	siPersonID	;
	}
};
//[����] ������� �̵� 
class cltGameMsgResponse_GoRaccoonWorld
{
public:
	SI32	m_siResult;

	cltGameMsgResponse_GoRaccoonWorld( SI32 siResult)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_GoRaccoonWorld) );
		m_siResult	=	siResult	;
	}
};


#endif