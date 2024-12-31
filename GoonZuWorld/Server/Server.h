//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _SERVER_H
#define _SERVER_H

#include "..\Client\Client.h"
#include "Rank\Rank.h"

#include "Statistics/MoneyStatistics/MoneyStatistics.h"

#include "GameProtocol\GameProtocol.h"
#include "FrontAuthProcess\FrontAuthProcess.h"
#include "GameDBProcess\LogDBProcess.h"
#include "GameDBProcess\GameDBProcess.h"
#include "GameDBProcess\GameDBProcess2.h"
#include "AgentProcess\AgentProcess.h"
#include "BillProcess\BillProcess.h"
#include "NTradeServerProcess/NTradeServerProcess.h"
#include "../CommonLogic/Guild/GuildWar.h"
#include "../CommonLogic/Guild/Guild-Dungeon.h"
#include "../common/Item/ItemCommon/Item-BookBox.h"
#include "../common/item/ItemCommon/Item-GodHand.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Web.h"
#include "../common/BokBulBokEventMgr/BokBulBokEvent.h"

#include "../CommonLogic/PartyMatchingMgr/Server_PartyMatchingMgr.h"
#include "../CommonLogic/Msg/MsgType-PartyMatching.h"
#include "PartyQuestMgr/PartyQuestMgr_Server.h"

#include "..\Common\Weather\Weather.h"

#include "NMsgShareBuffer.h"
#include "IPToCountry\IPToCountry.h"

#include "Msg/MsgType-Summon.h"

#include "../Client/CheckProcess/CheckProcess.h"

// -HanAuth_Lib
#ifdef USE_HANREPORT
	#ifdef _SERVER
		#include "../HanAuth/HanReportForSvr.h"

		#ifdef _DEBUG
			#pragma comment(lib, "HanReportForSvrD.lib") 
		#else
			#pragma comment(lib, "HanReportForSvr.lib") 
		#endif // _DEBUG
	#endif // _SERVER
#endif // USE_HANREPORT
// -HanAuth_Lib

#ifdef USE_HANIPCHECK
	#ifdef _NHN_CHINA
		#include "../HanAuth/HANIPCHECK_CHI/HanIPCheckForSvr_CHI.h"
		#ifdef _DEBUG
			#pragma comment(lib, "HanIPCheckForSvrD_CHI.lib") 
		#else
			#pragma comment(lib, "HanIPCheckForSvr_CHI.lib")
		#endif
	#else
	#include "../HanAuth/HanIPCheckForSvr.h"
		#ifdef _DEBUG
			#pragma comment(lib, "HanReportForSvrD.lib") 
		#else
			#pragma comment(lib, "HanReportForSvr.lib")
		#endif
	#endif // _NHN_CHINA
#endif // USE_HANREPORT

#ifdef USE_HANXNOTI
	//#ifdef _SERVER
		#include <XDR/XDR.h>
		
		#include <XnotiAppMessage.h>
		#include <XNotiConnectorAPI.h>

		#include <GoonZuGMT.h>
		#include <SHOP.h>		// �� ����

		#ifdef _DEBUG
		#else
			#pragma comment(lib, "XPlatform.lib") 
			#pragma comment(lib, "XStream.lib") 
			#pragma comment(lib, "XSystem.lib") 
			#pragma comment(lib, "Connector.lib") 
			#pragma comment(lib, "Log4XCore.lib") 
			#pragma comment(lib, "Log4XBase.lib") 
			#pragma comment(lib, "XNotiConnector.lib") 
			#pragma comment(lib, "XInNetwork.lib") 
		#endif
	//#endif
#endif // USE_HANXNOTI

#ifdef USE_HAN_BAN_CHECK
	#ifdef _SERVER
		// �Ѱ��� ���� ���� ���
		#include "../HanBanCheckForSvr/HanBanCheckForSvr.h"

		#ifdef _DEBUG
			#pragma comment(lib, "HanBanCheckForSvrD.lib") 
		#else
			#pragma comment(lib, "HanBanCheckForSvr.lib") 
		#endif
	#endif		
#endif

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	#ifdef _SERVER
		#include "../Porte/PorteAuthForSvr.h"	
		using namespace Porte::PorteAuthSystem;
#endif		
#endif // USE_PORTEAUTH

//////////////////////////////////////////////////////////////////////////
// [����] �߱� ���θ���. 
#include "PromoterManager/clPromoterManager.h"
#include "../Promoter/NHNChinaPromoter.h"

#ifdef USE_PROMOTOR_SERVER	
	
	// �������� ���
	#ifdef _DEBUG	
		#ifndef _DBMANAGER
			#pragma comment(lib, "NHNChinaPromoterDllD.lib") 
		#endif
	#else
		#pragma comment(lib, "NHNChinaPromoterDll.lib") 
	#endif

#endif
//////////////////////////////////////////////////////////////////////////
#include "SummonTransformManager/SummonTransformManager.h"

#include "../CommonLogic/BattleRoyal/CBattleRoyalMgr.h"

#include "../Server/Event/ContributionEvent_Common/ContributionEvent_Common.h"
#include "../Server/Event/GiantRaccoon_Resurrect_Event/GiantRaccoonResurrectEvent.h"

#include "MacroReportedMgr/MacroReportedMgr.h"
#include "GZFtpMgr/GZFtpMgr.h"

struct stHanXNoti_Waiting
{
	SI32			m_siIdx;
	HANDLE			m_hWaitingHandle;
};

// KHY - 0901 -  ���� ������ �ڵ����� ����.
#define MAX_SYSTEMBUYTEM_NUM				50

struct SystemBuyItem
{
	SI16			m_siUnique;
	GMONEY			m_gPrice;
};


#define HANXNOTI_MAX_WAITING				16

#define MRS_ERRORCODE_SUCCESS				0
#define MRS_ERRORCODE_FAILED				1

#define MRS_ERRORCODE_INVALID_COMMAND		10
#define MRS_ERRORCODE_INVALID_PARAMETER		11

#define MRS_ERRORCODE_INVALID_CHARNAME		100

#define MRS_ERRORCODE_INVALID_ITEMNAME		200
#define MRS_ERRORCODE_INVALID_ITEMCOUNT		201

#define MRS_ERRORCODE_SYSTEM_TIMEOUT		300
#define MRS_ERRORCODE_SYSTEM_ERROR			301
#define MRS_ERRORCODE_SYSTEM_MSGFULL		302

#define MRS_ERRORCODE_ADDINVENTORYITEMREQ_FAILED	-1
#define MRS_ERRORCODE_DELETEINVENTORYREQ_FAILED		-1

extern NMsgShareBuffer g_msgsharebuffer;

#define WRITE_MEMLOG( a, b, c, d )		g_msgsharebuffer.WriteMsg( a, b, c, d );

#define WRITELOG_DBMSG				100
#define WRITELOG_DBMSG2				101
#define WRITELOG_DBLOG				102
#define WRITELOG_GAMEMSG			110


#define EVENT_NPC_COUNT			5
#define MAX_RANDOM_ROC_COUNT	100	// ���� ��ǥ ������ ���� �ִ��� ���� �ݺ� Ƚ��

// ����� ����
#include "ITZWorld.h"
#include "ServerMap/ServerMap.h"
#include "ItemList\ItemList.h"

class cltLetterHeader;
class cltNoticeManager;
class cltStrInfo;
class HashStringInt;
class HashIntInt;
class CMinisterMgr;
class cltItemMallManager;
class cltMonsterGroupManager;
class CPartyObj;
class cltStockOfferingManager;
class cltIDNumTable;
class GMProtocol;
class CKingGuriEvent;
class CEmpireManager;
class CSantaRaccoon;				//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� Ŭ����.]
class cltRewardMgr;
class cltNewSelectBoxMgr;
class CGawiBawiBoMgr_Server;
class CBattleRoyalMgr;					// ��Ʋ�ξ� �Ŵ���
class cltContributionEvent_Common;
class cltGiantRaccoonResurrectEvent;	// ���̾�Ʈ ���� ��Ȱ


class CGoonzuKingGuriEvent;//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

struct sGameServerRefreshInfo;

#define REPAIR_ERR_NOTSAMEITEM	1	// ���� ��û�� �����۰� ���� �������� �ٸ���. 
#define REPAIR_ERR_SETITEM		2	// ��Ʈ �������� ����� ������ �� ����.

#define MAX_SPECIAL_QUEST_BONUS_BUFFER_SIZE		1000	// ��ι� ����Ʈ �Ϸ��� ���� ������ 
#define MAX_SPECIAL_NEWS_BUFFER_SIZE			1000

//-------------------------------------------
// NPC�� ������ ���� ��Ȳ 
//-------------------------------------------
#define NPCITEMMODE_NONE		0	// ������ ���� ����. 
#define NPCITEMMODE_NORMAL		1	// �Ϲ����� ������ ����. 
#define NPCITEMMODE_HUNT		2	// ������ ���ͷ� ������ ����Ȯ�� ����. 
#define NPCITEMMODE_DOCKDO		3	// ���� ���ͷ� ������ ����Ȯ�� ����
#define NPCITEMMODE_GM			4	// GM�� ����� ���ͷ� ��� ������ ����


//----------------------------------------
// Cash���� ���� 
//----------------------------------------
#define MAX_PUSH_CASH_LIST_NUMBER	(MAX_PERSON_NUMBER)
#define PUSHCASH_REASON_QUEST		1		// ����Ʈ �������� ����. 
#define PUSHCASH_REASON_GAMEMASTER	2		// ��ڱ������� ����. 
#define PUSHCASH_FOREIGNMERCHANTBUY	3		// ������ ���� ������ ����
#define PUSHCASH_REASON_ATTENDANCE	4		// �⼮���� ����. 
#define PUSHCASH_REASON_QUESTEVENT	5		// ����Ʈ �̺�Ʈ�� ����

#define WARLOSS_STOCK				1000	// ���� �й�� �ֽ� �Ұ� ���� 

//----------------------------------------
//cyj ������ȸ, ������ �ڸ����� ����(�д���)
//----------------------------------------
#define GENERALMEETING_NEWS_INTERVAL	10
#define VILLAGEWAR_NEWS_INTERVAL		5

#define BLACKARMY_NEWS_INTERVAL			1		// �ð�����

enum HUNAMAPWARP_MODE
{
	HUNTMAPWARP_MODE_NONE,
	HUNTMAPWARP_MODE_USEMONEY,
	HUNTMAPWARP_MODE_USEITEM,
};

enum DBINITIALIZE_STEP
{
	DBINITIALIZE_STEP_NONE,
	DBINITIALIZE_STEP_1,
	DBINITIALIZE_STEP_2,
};

#define FINDTREASURE_CUTLEVEL	-21	// ����ã�� �̺�Ʈ ���͸� ������ ���� �ִ� ���������� ���� ��������
#define	MAX_TREASUREEVENT_POSITION_NUM	30		// ����ã�� �̺�Ʈ �Ѹʿ� ������ �ִ� �ִ� ��ǥ ����
#define	MAX_TREASUREEVENT_USEMAP_NUM	100		// ����ã�� �̺�Ʈ���� ����� �� �ִ� ����
class cltPushCash{
public:
	UI16 usCharID;
	SI32 siPersonID;
	TCHAR szAccountID[MAX_PLAYER_NAME];
	GMONEY siMoney;
	SI32 siReason;
	SI32 siDay;

	cltPushCash()
	{
		usCharID = 0;
		siPersonID = 0;
		StringCchCopy(szAccountID, MAX_PLAYER_NAME, TEXT(""));
		siMoney = 0;
		siReason = 0;
		siDay = 3;
	}
	void Set(cltPushCash* pclinfo)
	{
		usCharID = pclinfo->usCharID;
		siPersonID	= pclinfo->siPersonID;
		StringCchCopy(szAccountID, MAX_PLAYER_NAME, pclinfo->szAccountID);
		siMoney		= pclinfo->siMoney;
		siReason = pclinfo->siReason;
	}

	void Set( UI16 charid, SI32 personid, TCHAR* szaccountid, GMONEY money, SI32 reason, SI32 day = 3 )
	{
		usCharID = charid;
		siPersonID	= personid;
		StringCchCopy(szAccountID, MAX_PLAYER_NAME, szaccountid);
		siMoney		= money;
		siReason = reason;
		siDay = day;
	}
};


class cltServerStartInfo
{
public:
	SI32	siStockDistributionVillageUnique;		// �ֽ� ���� ���̾��ٸ�, ���� ���̾��� ���� Index

	void Set( cltServerStartInfo *pclServerStartInfo )
	{
		memcpy ( this, pclServerStartInfo, sizeof( cltServerStartInfo ) );
	}
};

struct GMServerInfo
{
	BOOL		bAutoStock;
	BOOL		bAutoWar;
};

class cltCurrencyInfo{
public:
	cltMoney clInputMoney_NPC;				// NPC�� �����ϴ� �ڱ�. 
	cltMoney clInputMoney_Quest;
	cltMoney clInputMoney_War;
	cltMoney clInputMoney_Father;			// ���� �缺�� ���� ���� �ڱ�. 
	cltMoney clInputMoney_Recommender;		// ��õ�ο� ���� ���� �ڱ�. 


	cltMoney clOutputMoney_NPC;				// NPC�� �Ҹ��ϴ� �ڱ�. 
	cltMoney clOutputMoney_Dead;			// ����� ���� �ս� 
	cltMoney clOutputMoney_Repair;			// ������ ���� �Ҹ�. 
	cltMoney clOutputMoney_Stock;			// �ֽ� ���Կ� ���� �ս�. 
	cltMoney clOutputMoney_clMarketTax;		// ���� ���ݿ� ���� ȸ��. 
	cltMoney clOutputMoney_clStockBidTax;	// ���ڼ��� ���� ȸ��. 
	cltMoney clOutputMoney_clVillageWar;	// �������� ���� ���ԵǴ� �ڱ� 
	cltMoney clOutputMoney_NPCPayment;		// ���� �ֹ� ���� �� �޿� 
	cltMoney clOutputMoney_QuestFee;		// ����Ʈ�� ���� ������
	cltMoney clOutputMoney_TradeTax;		// ���� ���ݿ� ���� ȸ��.
	
	cltMoney clTotalBudget;					// ���� 
	cltMoney clReservedBudget;				// �������� 		
	cltMoney clOutputMoney_clNewMarketTax;	// ���ս��� ���ݿ� ���� ȸ��. 


	cltCurrencyInfo()
	{
		Init();
	}

	void Init()
	{
		clInputMoney_NPC.Init();
		clInputMoney_Quest.Init();
		clInputMoney_War.Init();
		clInputMoney_Father.Init();
		clInputMoney_Recommender.Init();

		clOutputMoney_NPC.Init();
		clOutputMoney_Dead.Init();
		clOutputMoney_Repair.Init();
		clOutputMoney_Stock.Init();
		clOutputMoney_clMarketTax.Init();
		clOutputMoney_clStockBidTax.Init();
		clOutputMoney_clVillageWar.Init();
		clOutputMoney_NPCPayment.Init();
		clOutputMoney_QuestFee.Init();
		clOutputMoney_TradeTax.Init();

		clTotalBudget.Init();
		clReservedBudget.Init();
		clOutputMoney_clNewMarketTax.Init();
	}

	void GetTotalInput( cltMoney *pclMoney )
	{
		pclMoney->Init();
		pclMoney->itMoney += clInputMoney_NPC.itMoney;
		pclMoney->itMoney += clInputMoney_Quest.itMoney;
		pclMoney->itMoney += clInputMoney_War.itMoney;
		pclMoney->itMoney += clInputMoney_Father.itMoney;
		pclMoney->itMoney += clInputMoney_Recommender.itMoney;

	}

	void GetTotalOutput( cltMoney *pclMoney )
	{
		pclMoney->Init();
		pclMoney->itMoney += clOutputMoney_NPC.itMoney;
		pclMoney->itMoney += clOutputMoney_Dead.itMoney;
		pclMoney->itMoney += clOutputMoney_Repair.itMoney;
		pclMoney->itMoney += clOutputMoney_Stock.itMoney;
		pclMoney->itMoney += clOutputMoney_clMarketTax.itMoney;
		pclMoney->itMoney += clOutputMoney_clStockBidTax.itMoney;
		pclMoney->itMoney += clOutputMoney_clVillageWar.itMoney;
		pclMoney->itMoney += clOutputMoney_NPCPayment.itMoney;
		pclMoney->itMoney += clOutputMoney_QuestFee.itMoney;
		pclMoney->itMoney += clOutputMoney_TradeTax.itMoney;
		pclMoney->itMoney += clOutputMoney_clNewMarketTax.itMoney;
	}

};
// ���Ӱ� ���� ������ ��ƾ.
class cltTreasure_RocData
{
private:
public:
	SI32 m_siX	;
	SI32 m_siY	;
	cltTreasure_RocData()
	{ ZeroMemory(this, sizeof(cltTreasure_RocData)); };

	~cltTreasure_RocData()
	{ ZeroMemory(this, sizeof(cltTreasure_RocData)); };

	SI32 GetRoc_X(){ return m_siX ;}	;
	SI32 GetRoc_Y(){ return m_siY ;}	;

	void Set_RocX( SI16 siX	){ m_siX = siX ;}	;
	void Set_RocY( SI16 siY	){ m_siX = siY ;}	;
	
	void Set_Roc( SI16 siX	,SI16 siY )
	{ 
		m_siX = siX ;
		m_siY = siY ;
	};
};
class cltTreasure_Roc
{
private:
	cltTreasure_RocData m_RocData[MAX_TREASUREEVENT_POSITION_NUM]	;
public:
	cltTreasure_Roc()
	{ ZeroMemory(this, sizeof(cltTreasure_Roc)); };

	~cltTreasure_Roc()
	{ ZeroMemory(this, sizeof(cltTreasure_Roc)); };

	void SetRoc( SI32 siX, SI32 siY, SI32 siSLot)
	{
		m_RocData[siSLot].Set_Roc(siX,siY)	;
	};
	SI32 GetRocX(SI32 siSLot ){ return m_RocData[siSLot].m_siX	;	}
	SI32 GetRocY(SI32 siSLot ){ return m_RocData[siSLot].m_siY ;	}
};
class cltTreasure_MapInfo
{
private:
	SI32				m_siMapIndex	;	
	SI32				m_RocNum		;	// ��ǥ�� ��� ������ �ֳ�.
	SI32				m_MaxUse_RocNum		;	// ��ǥ�� ��� ������ �ֳ�.
public:
	cltTreasure_Roc*	pclTreasure		;	// X Y ��ǥ

	cltTreasure_MapInfo()
	{ ZeroMemory(this, sizeof(cltTreasure_MapInfo)); };

	~cltTreasure_MapInfo()
	{ ZeroMemory(this, sizeof(cltTreasure_MapInfo)); };

	void MakeRocSlot()
	{ 
		pclTreasure = (cltTreasure_Roc*)malloc( sizeof( cltTreasure_Roc ) )	;
		ZeroMemory( pclTreasure ,sizeof( cltTreasure_Roc ) )	;
	};
	void SetRoc( SI32 siRocX,  SI32 siRocY, SI32 siSlot )
	{ 
		pclTreasure->SetRoc( siRocX , siRocY,siSlot)	;
	}
	void SetMapIndex( SI32 siMapIndex){	m_siMapIndex = siMapIndex	; }	;
	SI32 GetMapIndex(){ return m_siMapIndex ; }	;

	void Set_MaxUse_RocNum(	SI32 siMaxRocNum){	m_MaxUse_RocNum = siMaxRocNum	; }	;
	SI32 Get_MaxUse_RocNum(){	return m_MaxUse_RocNum ; }	;

	void SetRocNum(	SI32 siRocNum){	m_RocNum = siRocNum	; }	;
	SI32 GetRocNum(){	return m_RocNum ; }	;
	
	SI32 GetRoc_X( SI32 siSLot ){ return pclTreasure->GetRocX( siSLot ) ; }	;
	SI32 GetRoc_Y( SI32 siSLot ){ return pclTreasure->GetRocY( siSLot ) ; }	;
};

class clTreasureEvent_Npc_KillCounnt
{
private:
	SI32 m_siMapIndex ;			// ���� ���ε���
	SI32 m_siKillCount ;	// ��������� ���� �ִ� ����
public:
	clTreasureEvent_Npc_KillCounnt()
	{ ZeroMemory(this, sizeof(clTreasureEvent_Npc_KillCounnt)); };
	~clTreasureEvent_Npc_KillCounnt(){};
	SI32 GetMapIndex(){		return m_siMapIndex	;}	;
	void SetMapIndex( SI32 siMapindex ){m_siMapIndex = siMapindex ;};

	SI32 Get_KillCount(){	return m_siKillCount	;}	;
	void Set_KillCount( SI32 siKillCount ){ 
		m_siKillCount = siKillCount ; 
	};
	void AddKillCount()	{	m_siKillCount = m_siKillCount +1	;	}
	void DellKillCount( SI32 siDelKill_Point){	m_siKillCount = m_siKillCount - siDelKill_Point	;	}
};
class clTradeItemInfo
{
public:
	_SYSTEMTIME m_sTime;
	SI64		m_siMoney;
	SI32		m_siCnt;

	clTradeItemInfo()
	{
		ZeroMemory(this, sizeof(clTradeItemInfo));
	}
	void Clear(void)
	{
		ZeroMemory(this, sizeof(clTradeItemInfo));
	}
};




#define KIND_TREASURE_DAEGUM1		377		//���� �������
#define KIND_TREASURE_CATAR1		378		//���� ���Ǿ��
#define KIND_TREASURE_RIFLE1		379		//���� �ų�
#define KIND_TREASURE_DAEGUM2		380		//���ֹ��� �������
#define KIND_TREASURE_CATAR2		381		//���ֹ��� ���Ǿ��
#define KIND_TREASURE_RIFLE2		382		//���ֹ��� �ų�
#define KIND_TREASURE_REDSHABEL		383		//���ֹ��� �������
#define KIND_TREASURE_BLUESHABEL	384		//���ֹ��� ������
#define KIND_BLESSINGJEAN			385		//��ȭ�� ������ ��ȥ
#define KIND_BLESSINGMERIEL			386		//��ȭ�� ������ ��ȥ
#define KIND_BLESSINGCLARA			387		//��ȭ�� ������ ��ȥ
#define KIND_BLESSINGSPARKY			388		//��ȭ�� ������ ��ȥ
#define KIND_CURSEHIRO				389		//������ ����
#define KIND_BLESSINGHIRO			390		//�Ƚ��� ã�� ������ ��ȥ

#define  FAMILY_ADD_CHILDREN_EXP	0.003f	// �������踦 ���� ������� �ڽĵ鿡�� �������� �θ� ����ġ�� ����
#define  MAX_FAMILY_ADD_EXP			10		// �������踦 ���� ����� ���������� ������ �ִ� ����ġ ������ �ִ�


class cltServer : public cltCommonLogic {

// [����] ����, �Լ� ����
public:
	// [�߰� : Ȳ���� 2008. 2. 20 => ��ȯ�� �ɷ�ġ ���������ϴ� �κ��� �Լ��� ��.]
	void Use_Summon_Bonus(cltGameMsgRequest_SummonUseBonusPoint* pclinfo, SI32 id);
	void New_Use_Summon_Bonus(cltGameMsgRequest_SummonUseBonus* pclinfo, SI32 id);

	void	DayLogFileWrite(void);

	//[�߰� : Ȳ���� 2007. 11. 19 ���� ���� ������ �ŷ� ���� ����.]
#ifdef _SAFE_MEMORY
	NSafeTArray<clTradeItemInfo, 6>		clItemInfo;
#else
	clTradeItemInfo clItemInfo[6];
#endif

	//[�߰� : Ȳ���� 2007. 11. 26 �ý��ۿ��� ������ ���忡 �ø� ������ ���Ű��� ���� ����.]
	clTradeItemInfo clSystemBuyItem;

	void StartPersonalSpecialShop(cltMsg* pclMsg, SI32 id);

	bool	SelectBillURL( TCHAR * AccountID, TCHAR * selectURL );
public:
	

	cltGameProtocol*	pclGameProtocol;
	FrontAuthProcess*	pclFrontAuthProcess;
	AgentProcess*		pclAgentProcess;
	BillProcess*		pclBillProcess;
	GameDBProcess*		pclGameDBProcess;
	GameDBProcess2*		pclGameDBProcess2;
	LogDBProcess*		pclLogDBProcess;
	
	NTradeServerProcess*pclNTradeServerProcess;

	GMProtocol*			pclGMProtocol;

	

	cltIDNumTable*		pclIDNumTable;


	bool				bServerNetoworkStartSwitch;	// ������ ��Ʈ��ũ�� ������ �غ�Ǿ����� Ȯ���Ѵ�. 
	bool				bGameTimeRequestSwitch;		// ���� �ð��� ��� �� ���� ��û������ Ȯ���Ѵ�. 
	bool				bGetTimeSwitch;				// DB�κ��� ���� �ð��� �������� Ȯ���Ѵ�. 
	// ���� �ð��� ������ �������� ������ �ൿ�� ���� �ʴ´�. 

	bool				bMapTypeInfoRequestSwitch;	// �� Ÿ���� ��û������ Ȯ���Ѵ�. 
	bool				bGetMapTypeInfoSwitch;		// �� Ÿ�������� �޾����� Ȯ���Ѵ�. 

	bool				bForcePersonalShopSwitch;	// ���μ����� �����Ѵ�.
	bool				bForceVillageWarSwitch;		// ������ ������ �����ϰ� �Ѵ�.
	bool				bForceTimeSwitch;			// �ð��� ����������.
	bool				bAutoWarSwitch;				// �ڵ� ���� ����. 

	bool				bAutoStockDistriubtionSwitch;	// �ڵ� ���� ����

	DWORD				dwVillageWarTimeMin;
	DWORD				dwVillageWarStartHour,	dwVillageWarStartMin;		// �����ð� ���� 
	DWORD				dwVillageWarFinishHour,	dwVillageWarFinishMin;
	DWORD				dwSpecialNews;
	DWORD				dwGeneralMeetingNewsMin;
	DWORD				dwVillageWarNewsMin;
	DWORD				dwBlackArmyNewsHour;


	bool				bProcessDB_WealthRank_NEED;
	bool				bProcessDB_TotalMoney_NEED;
	bool				bProcessDB_TotalChar_NEED;

	bool				bProcessDB_GetMinister_NEED;

	bool				bProcess_InitCalcCharNum;

	bool				bCalcInvestment; // �輱��(���ڻ�㰡) ����ϱ�

	bool				bProcess_InitGameEvent ;

	bool				bProcessDB_TotalVillageScore_NEED;
	// �ڵ� ��� ����
	bool				bProcessDB_AutoPayDividend_NEED;
	
	// ���� ���������� ������Ʈ �Ǿ����� ����ġ
	bool				bProcess_SetNowVillageWarInfo;
	cltDate				clLastSettedNowVillageWarIinfo;

	// ���������� �������� ������ ������ �ʱ�ȭ �� ��¥�� ���. ��¥�� ����Ǹ� �������� ������ ������ �ʱ�ȭ
	SI32				siLastVillageWarKillNumClearDay;

	cltServerStartInfo	clServerStartInfo;

	bool				bHorseCurrentPriceSet;

	UI08				bGMBonusTimeSwitch;		// GM������� ���ʽ� Ÿ�� ������������ ����ġ
	bool				bIsGMBonusTime;			// GM���ʽ� Ÿ�����ΰ�?
	bool				bIsGMBonusTime2;		// GM���ʽ� Ÿ�����ΰ�?(����)
	
	SI16				siGMBonusTimePercent;	// GM���ʽ� Ÿ���� �������ִ� ���ʽ� �ۼ�Ʈ
	SI16				siGMBonusTime2Percent;	// GM���ʽ� Ÿ���� �������ִ� ���ʽ� �ۼ�Ʈ

	bool				bDoNotAutoBonus;		// �ڵ����ʽ� �ð� ���� ����ġ

	SI16				siHorseTradeCount;
	GMONEY				siHorseCurrentPrice;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_LOWLEVEL_LIST_NUMBER>		siLowLevelCharUnique;
#else
	SI32				siLowLevelCharUnique[MAX_LOWLEVEL_LIST_NUMBER];
#endif
	SI32				siLowLevelCount;


#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, 10>		siTopLevelVillageUnique;
#else
	SI32				siTopLevelVillageUnique[10] ;
#endif

	//KHY - 1113 - ũ�������� �̺�Ʈ - �ʿ� ��ġ�� �̺�Ʈ�� npc ID�� �����Ѵ�.
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, EVENT_NPC_COUNT>		siEventNPCId;
#else
	SI32				siEventNPCId[EVENT_NPC_COUNT];
#endif	

	bool				bAlldayBonus;		//[����] �ڵ����ʽ� �ð� �Ϸ����� ����Ǹ� �� �Ϸ� �� ���� ���ʽ� �ð��� �����ϱ� ���� �߰�.

	SI16				siFourLeafUnique;

	// ���� �ٿ� ������ ���� �ڵ� ��ġ ����
	//======================================================
	// �޽�����
	//======================================================
	// �����޽��� ó�� �Լ�������
	class stServerMsgPtr
	{
	public:
		void (cltServer::*ServerMsgFunc)(cltMsg* pclMsg, SI32 id);
	};

	stServerMsgPtr	*m_pServerMsgPtr;
	bool			*m_pbUseMsg;
	void	ServerMsgNullFunc(cltMsg* pclMsg, SI32 id);
	void	RegisterServerMsgMap();

	// DB�޽��� ó�� �Լ�������
	class stDBMsgPtr
	{
	public:
		void (cltServer::*DBMsgFunc)(sPacketHeader* pPacket);
	};

	stDBMsgPtr *m_pDBMsgPtr;
	void	DBMsgNullFunc(sPacketHeader* pPacket);
	void	RegisterDBMsgMap();
	//======================================================

public:
	SI32			siServerID;						// Server ID

	ItemList*		pclItemList;					// �ٴڿ� ������ �������� ���� ������. 

	// ���� ������.
	cltRankManager* pclRankManager;

	// �ð� ������. 
	cltTime*		pclTime;

	// ���� ������. 
	CWeather*		pclWeather;

	cltStockOfferingManager*	pclStockOfferingManager;

	//------------------------------
	// ���� ������. 
	//------------------------------
	cltNoticeManager*	pclNoticeManager;

	//------------------------------
	// CHAR NAME���� �˻��� ���� HASH TABLE
	//------------------------------
	HashStringInt*		pclHashTable;

	//------------------------------
	// PERSON ID���� �˻��� ���� HASH TABLE
	//------------------------------
	HashIntInt*			pclPersonHashTable;

	//-----------------------------------
	// �����Ǽ�  
	//-----------------------------------
	CMinisterMgr*		pclMinisterMgr;

	cltIPToCountryMgr*	pclIPToCountryMgr;
	cltAccessDenyMgr*	pclAccessDenyMgr;

	//-------------------------------
	// ä�� �Ǽ�
	//-------------------------------
	SI32 siChatCount_Private;
	SI32 siChatCount_General;

	//--------------------------------
	// ����� ���� ������
	//--------------------------------
	cltGuildWarReserveManager*	pclGuildWarReserveManager;
	NSafeTArray<cltGuildWarManager*, GUILDWAR_FIELDNUM>		pclGuildWarManager;
	//--------------------------------
	// ������ ���� ������
	//--------------------------------
	cltGuildDungeonMgr*			pclGuildDungeonMgr;

	//--------------------------------
	// å���� ��� ����
	//--------------------------------
	cltBookBox*			pclBookBox;

	//--------------------------------
	// ���ڵ� ������
	//--------------------------------
	CItemGodHandManager*	pclGodHandManager;

	//-------------------------------
	// ������ ��. 
	//-------------------------------
	SI32 siTodayMaxUserNum;				// ������ �ְ� ����. 
	SI32 siCurUserNum;					// ���� ����. 
	SI32 si1To19UserNum;
	SI32 si20To39UserNum;
	SI32 si40To59UserNum;
	SI32 si60To79UserNum;
	SI32 si80To99UserNum;
	SI32 si100To119UserNum;
	SI32 si120To150UserNum;

	SI32 siTotalNewCharNum;				// ��ü ������ �����ϰ� ĳ���� ���� ���� 
	SI32 siTotalDelCharNum;				// ��ü ������ �����ϰ� ĳ���� ���� ����

	SI32 siServerNewCharNum;			// ���� ������ �����ϰ� ĳ���� ���� ����
	SI32 siServerDelCharNum;			// ���� ������ �����ϰ� ĳ���� ���� ����

	SI32 siNewCharNum;					// ���ο� ĳ���� ���� ����  
	SI32 siDelCharNum;					// ĳ���� ���� ���� 
	SI32 siPCRoomCharNum;				// pc�� ĳ���� ������ ����

	//SI32 siNetmarbleCharNum;			// Netmarble ĳ���� ������ ����

	SI32 siHangameCharNum;				// �Ѱ��� ĳ���� ������ ����.
	SI32 siGamaniaCharNum;				// Gamania ĳ���� ������ ����
	SI32 siGamePotCharNum;				// GamePot ĳ���� ������ ����
	SI32 siNDECharNum;					// NDEĳ���� ������ ����
	SI32 siNEXONCharNum;				// NEXONĳ���� ������ ����

	// [����] USA �̰�.
	SI32 siGlobalNum;					// �۷ι� ������ ��.
	SI32 siNHNNum;						// NHN ������ ��.

	//-------------------------------
	// ���� ��� ������
	//-------------------------------
	SI32 siWndInterfaceNum;				// ���� ������ ����� �� ������â + ������ �������̽� ����� ������
	SI32 siWnd_NewInterfaceNum;			// ���� ������ ����� �� ������â + ���������̽� ����� ������
	SI32 siFullWnd_NewInterfaceNum;		// ���� ������ ����� �� ��üȭ�� + ���������̽� ����� ������


	//-------------------------------
	// �����̾� �ð��� 
	//-------------------------------
	_SYSTEMTIME sTime;
	_SYSTEMTIME	sLastNewsTime;			// ���������� ������ ���� �ð�. 	

	//---------------------------------
	// DB �Ŵ������� ������ ���� �ð�. 
	//---------------------------------
	DWORD dwLastDBClock;

	//--------------------------------
	// ���� �ֽ� �ֹ� ��û. 
	//--------------------------------
	DWORD dwLastStockOrderClock;
	SI32 siLastStockOrderIndex;

	//--------------------------------
	// DB�����ð�. 
	//--------------------------------
	DWORD dwDBLatency;

	//--------------------------------
	// ��ȭ�� 
	//--------------------------------
	cltCurrencyInfo clCurrencyInfo;

	//--------------------------------
	// ���� ���� ���. 
	//--------------------------------
	cltStatisticsManager * pclStatisticsManager;

	cltAddMoneyStatistics*		pclAddMoneyStatistics;
	cltDelMoneyStatistics*		pclDelMoneyStatistics;

	//--------------------------------
	// Server Refresh Info
	//--------------------------------
	sGameServerRefreshInfo				*pRefreshInfo;
	CRITICAL_SECTION					cs_refresh;

	//-----------------------------------
	// �Ķ��Ÿ�� ���� ĳ���� ����Ʈ��. 
	//-----------------------------------
	SI32	siParaCharListIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_CHAR_NUMBER>		siParaCharList;
#else
	SI16	siParaCharList[MAX_CHAR_NUMBER];
#endif

	//-----------------------------------
	// ���� ���� ����
	//-----------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_VILLAGE_NUMBER>	siSlaveVillageNum;
#else
	SI32	siSlaveVillageNum[ MAX_VILLAGE_NUMBER ];
#endif

	//-----------------------------------
	// Ư���� �� ����. 
	//-----------------------------------
	bool bDoubleBonusDaySwitch;

	bool bSpecailDay1Switch;			// ������. 
	bool bSpecailDay2Switch;			// ������. 
	bool bSpecailDay3Switch;			// �����ǳ� . 
	bool bSpecailDay4Switch;			// ���ֿ��±����
	bool bSpecailDay5Switch;			// ũ��������  
	bool bSpecailDay6Switch;			// 3.1��
	bool bSpecailDay7switch;			// �湫�� ź����
	bool bSpecailDay8switch;			// ��̳�
	bool bSpecailDay9switch;			// �ٴ��� ��

	bool bInstanceGate;					// �ν��Ͻ� ���� �Ա� ����?

	bool bRouletteGame;

	bool bAutoPayDividend;				// �ڵ� ��� ����(��� ��ɾ��)

	bool bTradeServer;
	bool bForceStopTradeProcess;

	bool bForceStopVillageWarProcess;	//

	SI16 siTradeServerStartTime; // ���� ���� �ð� ���� �ð�
	SI16 siTradeServerEndTime; // ���� ���� �ð� ������ �ð�

	SI16 siLimitMaxUserNumber;

	SI32 siServiceType;

	// pvp-
	SI32					siLoseItem;
	SI32					siRegenerateLifeValue;
	SI32					siBaenNyeonSamRate;
	SI32					siHandDamageRate;
	SI32					siSwordDamageRate;
	SI32					siSpearDamageRate;
	SI32					siAxeDamageRate;
	SI32					siBowDamageRate;
	SI32					siGunDamageRate;
	SI32					siStaffDamageRate;
	SI32					siPKMapExpRate;
	//����� ���ɿ���
	bool					bGuildWar;	
	// �Ļ� ���� ����
	bool					bBankruptcy;
	SI32					siStartBankruptDateVary;

	NDate					clAttendEventStart;		//�⼮üũ �̺�Ʈ ������
	NDate					clAttendEventEnd;		//�⼮üũ �̺�Ʈ �Ϸ���
	SI32					siAttendCheckMinute;	//�⼮üũ �ð�..( ������ x��)

	SI32					siItemmallRPRate;

	bool					bNoChargeGetItemFromNPC;	// Ŭ��� ���� ��ǰ ȸ�� ������ ����

	CKingGuriEvent*			pclKingGuriEventManager;
	CGoonzuKingGuriEvent*	pclGoonzuKingGuriEventManager;
	CEmpireManager*			pclEmpireManager;

	// �Ű�� ��ũ�� ���� ����
	cltMacroReportedMgr*	m_pclMacroReportedMgr;
	cltGZFtpMgr*			m_pclGZFtpMgr;

	// Ÿ�̸�
	NUpdateTimer			m_clUpdateTimer_Minute;		// 1�� Ÿ�̸�

	CSantaRaccoon*			pclSantaRaccoon;			//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ.]

	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	NDate					clValentineEventStart;		//�߷�Ÿ�ε��� ������
	NDate					clValentineEventEnd;			//�߷�Ÿ�ε��� �Ϸ���
	SI32						siValentineFarm;				//�߷�Ÿ�ε���  - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siValentineMine;				//�߷�Ÿ�ε���  - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siValentineFish;				//�߷�Ÿ�ε���  - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siValentineAttack;			//�߷�Ÿ�ε���  - ��� ������ ������ ȹ�� Ȯ��.
	SI32						siValentineItem;				//�߷�Ÿ�ε���  - ���� ������ ������ ȹ�� Ȯ��.

	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	NDate				clWhiteEventStart;		//ȭ��Ʈ���� ������
	NDate				clWhiteEventEnd;			//ȭ��Ʈ���� �Ϸ���
	SI32						siWhiteFarm;				//ȭ��Ʈ���� - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siWhiteMine;				//ȭ��Ʈ���� - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siWhiteFish;				//ȭ��Ʈ����  - ���� ������ ������ ȹ�� Ȯ��.
	SI32						siWhiteAttack;			//ȭ��Ʈ���� - ��� ������ ������ ȹ�� Ȯ��.
	SI32						siWhiteItem;				//ȭ��Ʈ���� - ���� ������ ������ ȹ�� Ȯ��.

	//KHY - 0530 ���� ���� ��������.
	GMONEY					gForeignMerchantBuyLimit;	// ���� ���� 1�� ���� ���� �ݾ�
	GMONEY					gForeignMerchantNowMoney;	// ���� ���� 1�� ���� �ݾ��� ����.
	SI16					siYesterday;					// ��¥ �񱳿� ����.

	SI32					siNDEScrollRate;			// ���� �̺�Ʈ NDE ���� ��� Ȯ��

	float					fForeignMerchantPercentUP	;	// ���� ���� �������ѱݾ� ������
	float					fForeignMerchantPercentDOWN	;	// ���� ���� �������ѱݾ� ������

	// KHY - 0901 -  ���� ������ �ڵ����� ����.
	SI32					siMarketMoneyItemAutoBuyDelayTime;
	GMONEY					siMarketMoneyItemMaxpriceNow;

	//-------------------------------------
	// ��������� ���ް���
	//-------------------------------------
	cltRewardMgr*			pclRewardMgr;

	//-------------------------------------
	// �ڽ� ������ ����
	//-------------------------------------
	cltNewSelectBoxMgr*		pclNewSelectBoxMgr;
	//cltElixirManager*		m_pclElixirManager;

	bool				bMakeTreasureEventNPC	;// ����ã�� �̺�Ʈ ���� �蹶ġ ���� �������� �ƴ��� �������� �� �ѹ��� �����.
	bool				bReadTreasureEvent_Resource	;// ����ã�� �̺�Ʈ ���� ���ҽ��� �д´�.
	// npc�� ����������� ����ϴ�  ����
	clTreasureEvent_Npc_KillCounnt		pclTreasureEvent_Npc_KillCounnt[ MAX_TREASUREEVENT_USEMAP_NUM ];	// ����ã�� �ʺ��� NPC�� ����� Ƚ��
	cltTreasure_MapInfo					pclTreasureMapInfo[MAX_TREASUREEVENT_USEMAP_NUM]	;
	// ����� X,Y��ǥ ���� �ʺ��� �����Ҷ����� ����� ���Ŵ�. ��� ������ �ִ°� �ƴϰ� �������ִ� ���Ե� �ν��Ͻ��� �����
	SI32								pclTreasureMapUseRoc[MAX_TREASUREEVENT_POSITION_NUM]	;			

	bool	bGachaLock	;					// ���� ��� �Ұ��� , ������ ���� �ʱⰪ�� true
	SI32	siGMChangeGachaRareUnique	;	// GM�� ������ ��������ũ GM�� ���� �ϸ� �̰ɷθ� ���� �ȴ� .�ð��� ������ �����̾ȵ� . 
	bool	bGachaRareitemStartSet	;		// ��í ���� ������ ���� ó�� ���� �ѹ� ���Ѵ� .

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, DBCONNECTION_NUMBER>	siCompleteDBInit;
#else
	SI16 siCompleteDBInit[ DBCONNECTION_NUMBER ];
#endif
	SI16 siCurrentDBInit;

	BOOL bSetVillageLevel;
	BOOL bSetTopLevelVillage;


	// ģ�� - ģ�� ��û�� ����� ������ ������ �ڿ� ������ư�� ������ ��쿡 ����� ���� ID�� �� ����
	TCHAR m_szFriendAccountID[MAX_PLAYER_NAME];

#ifdef _SAFE_MEMORY
	NSafeTArray<SystemBuyItem, MAX_SYSTEMBUYTEM_NUM>	stSystemBuyItem;
#else
	SystemBuyItem		stSystemBuyItem[MAX_SYSTEMBUYTEM_NUM]; // KHY - 0901 -  ���� ������ �ڵ����� ����.
#endif

	SI64	siTotalMoney;				// ����ȭ�� - �Ϸ翡 �ѹ��� ���ŵȴ�.

	//-------------------------------------
	// ��Ʋ�ξ�
	//-------------------------------------
	CBattleRoyalMgr*				m_pclBattleRoyalMgr;
	
	// ������ ��� �̺�Ʈ �⺻����(��θ����ϴ� NPC, ��� ������, ���� )�� cltContributionEvent_Common ���⼭ ����.
	cltContributionEvent_Common		m_clContributionEvent_Common;
	
	// ���̾�Ʈ ���� ��Ȱ �̺�Ʈ(��� �̺�Ʈ). (cltContributionEvent_Common ���)
	cltGiantRaccoonResurrectEvent*	m_pclGiantRaccoonResurrectEvent;

	CPartyQuestMgr_Server*			m_pPartyQuestMgr;

protected:
	//----------------------------------
	// ��ι� ����Ʈ �Ϸ��� ����. 
	//----------------------------------
	SI32 siSpecialQuestBonusBufferIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SPECIAL_QUEST_BONUS_BUFFER_SIZE>	siSpecialQuestBonusBuffer;
#else
	SI32 siSpecialQuestBonusBuffer[MAX_SPECIAL_QUEST_BONUS_BUFFER_SIZE];
#endif

	//----------------------------------
	// ĳ�� ���� ���� ����.
	//----------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<cltPushCash, MAX_PUSH_CASH_LIST_NUMBER>	PushCashList;
#else
	cltPushCash PushCashList[MAX_PUSH_CASH_LIST_NUMBER];
#endif
	SI32 PushCashListIndex;

	//-------------------------------------
	// ���� ��� ����
	//-------------------------------------
	SI32 siSpecialNewsBufferIndex;
	SI32 siSpecialNewsSendIndex;
	TCHAR szNewsTitleBuffer[MAX_SPECIAL_NEWS_BUFFER_SIZE][MAX_NEWS_TITLE_LENGTH];
	TCHAR szNewsNameBuffer[MAX_SPECIAL_NEWS_BUFFER_SIZE][MAX_NEWSPAPER_NAME_LENGTH];
	TCHAR szNewsURLBuffer[MAX_SPECIAL_NEWS_BUFFER_SIZE][MAX_PATH];
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SPECIAL_NEWS_BUFFER_SIZE>	siSpecialNewsKindBuffer;
	NSafeTArray<SI32, MAX_SPECIAL_NEWS_BUFFER_SIZE>	siSpecialSendKindBuffer;
#else
	SI32 siSpecialNewsKindBuffer[MAX_SPECIAL_NEWS_BUFFER_SIZE];
	SI32 siSpecialSendKindBuffer[MAX_SPECIAL_NEWS_BUFFER_SIZE];
#endif

	//-------------------------------------
	// ���μ��� üũ ����
	//-------------------------------------
	cltCheckProcessManager*		pclCheckProcessManager;

	clPromoterManager*			pclPromoterManager;

	CGawiBawiBoMgr_Server*		m_pGawiBawiBoMgr;

	cltSummonTransformManager*	m_pclSummonTransformManager;		//[����] ��ȯ�� ���� �޴���.		

public:
	cltSummonTransformManager*			GetSummonTransformManager( void ) { return m_pclSummonTransformManager; }

	void								blockRefresh() { EnterCriticalSection( &cs_refresh ); };
	void								unblockRefresh() { LeaveCriticalSection( &cs_refresh ); };

	cltServer(TCHAR* appname,HWND hwnd , HINSTANCE hinst, SI32 gamemode, SI32 servicearea, SI32 runmode);
	~cltServer();

	//------------------------------
	// ��� 
	//------------------------------
	void  DrawServerInfo(HDC hdc);  // �׸��� ���� �κ� 

	UI32  m_lastFrame;
	UI32  m_currentFrame;

	BOOL	bZeroStatistics;
	BOOL	bListenOK;
	BOOL	bWriteStatistics;

	UI16	m_uiCompressMinSize;
	CRITICAL_SECTION	m_cs_SendNetMsg;
	BYTE				m_bufComp[ sizeof(cltMsg) ];
	BYTE				m_encBuf[ sizeof(cltMsg) ];

	// �ǹ� ���� ���� 
	void UpdateStrInfoToClient( SI32 id, SI32 strType );

	//----------------------------------------
	// �ʱ�ȭ. 
	//----------------------------------------
	void Init(){};
	void Create();

	BOOL GMOrder( TCHAR *pOrder );
	void RestartTradeServer();

	//----------------------------------------
	// �������
	//----------------------------------------
	SI32 GetGuildWarBattleIndex( SI32 siGuildUnitIndex );

	//--------------------------------------------
	// ���� 
	// Server.cpp
	//--------------------------------------------
	// APEX-
	void SendNetMsg( int id, sPacketHeader* pPacket );
	void KillUser( int id );
	// -APEX

	// -HanAuth_Lib
#ifdef USE_HANRTA
//#ifdef _SERVER
	NUpdateTimer					m_kHanRTA_Timer;
#endif // USE_HANRTA

	// �߱�RTA - USE_CNRTA
#ifdef USE_CNRTA
	//#ifdef _SERVER
	NUpdateTimer					m_kCNRTA_Timer;
#endif // USE_CNRTA

#ifdef USE_HANXNOTI
	XNoti::Connector::THandle		m_pkHanAuth_XNotiConnector;
	TCHAR							m_szMRSServerID[ 50 ];

	static bool __stdcall HanXNoti_DoMsg_GMTMessageReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_GMTKickReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_GMTChatBlockReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_GMTCmdReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_GameCharacterListReq(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_AddInventoryItemReq(XStream::Handle stream, void* pAdditionalData, void* pContext);
	static bool __stdcall HanXNoti_DoMsg_DeleteInventoryReq(XStream::Handle stream, void* pAdditionalData, void* pContext);

	CRITICAL_SECTION				m_HanXNoti_CS;
	stHanXNoti_Waiting				m_kHanXNoti_Waitings[HANXNOTI_MAX_WAITING];
	XDR::IMessage*					m_pkHanXNoti_AnsMessages[HANXNOTI_MAX_WAITING];
	SI32 HanXNoti_GetEmptyWaiting(SI32 siIdx);
	void HanXNoti_ClearWaiting(SI32 siArrayIndex);

//#endif
#endif // USE_HANXNOTI

	// -HanAuth_Lib

	// -HanAuth_Lib
	void							HanAuth_Lib_HanReportSendPosLog_Server(TCHAR* pszID, TCHAR* value);
	// -HanAuth_Lib

	NUpdateTimer					m_kUpdateTimer_GameGuard;
	
	// [����] Auto Unblock ���� Ÿ�̸�(���� �⵿�� 5���� ������ �۵�, 1���� �۵���) - 2008.02.21
	NUpdateTimer					m_kUpdateTimer_AutoUnblock;

	// [����] 1�и��� ȣ���ؼ� �������� �߻��Ѵ�.
	NUpdateTimer					m_kUpdateTimer_PVP_League	;

	// [����] ��� ����� ������� ���� �Ѵ�.
	NUpdateTimer					m_kUpdateTimer_GuildHuntMapWar	;

	// [����] 10�и��� ȣ���ؼ� ����� npc ���ڸ�ŭ ���� �Ѵ�
	NUpdateTimer					m_kUpdateTimer_TreasureEvent_Respon_Npc	;// ����ã�� �̺�Ʈ

	// [ ����  ]	1�и��� ȣ�� �Ѵ�. ��¥�� üũ�ؼ� ��í ���� ������ ����ũ�� ���� �Ѵ�.
	NUpdateTimer					m_kUpdateTimer_GachaRareItmeUnique_Timer;
	
	// [����] ���� ���ϱ� �̺�Ʈ 
	NUpdateTimer					m_kUpdateTimer_RacoonDodgeEvent; // ���� ���ϱ� �̺�Ʈ //Switch_10MonthEvent_RacoonDodge

	// ����Ʈ�� ������ ���� ���� 
	GAMESERVER_GAMESERVERINFO	m_gameserverinfo;
	BOOL						m_bGameserverinfo;

	void LoadAutoUnblockFromFile(OUT bool *bAutoUnblockMode, OUT SI32 *siGameVersion);
	void SaveAutoUnblockToFile(IN bool bAutoUnblockMode, IN SI32 siGameVersion );

	// [����] �ʺ��� ���� - ��ī�� : ������ ������ ���ַ� ������ִ� �Լ�
	void BegnnerVillage_SetVillageChief( SI32 siPersonID );
	
	// [����] �߷�Ÿ�� ���� NPC(ī������) ���� �Լ�.
	void ValentineDayNpc( void );


	inline CGawiBawiBoMgr_Server* GetGawiBawiBoMgr()
	{
		if(m_pGawiBawiBoMgr != NULL)
			return m_pGawiBawiBoMgr;
		else
			return NULL;
	}

	//������ �޽��� ó�� �Լ���. 

	// APEX-
	void DoMsg_GAMEMSG_REQUEST_APEXDATA(cltMsg* pclMsg, SI32 id);
	// -APEX

	void DoMsg_GAMEMSG_REQUEST_USERORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HIT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETBULLET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_RIGHTMOUSE_USERLIST_NAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_VILLAGESTRUCT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ALLCHARINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_USEBONUS(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_PERSONNAME_FROMPERSONID(cltMsg* pclMsg,SI32 id);

	// Server-Person.cpp
	// ����Ʈ ���࿡ ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_SETQUESTGOING(cltMsg* pclMsg, SI32 id);
	// ����Ʈ ��ҿ� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_CANCELQUEST(cltMsg* pclMsg, SI32 id);
	// ����Ʈ ���� �뺸. 
	void DoMsg_GAMEMSG_REQUEST_QUESTSTATUS(cltMsg* pclMsg, SI32 id);

	// �̺�Ʈ ����� ��û�Ѵ�.
	void DoMsg_GAMEMSG_REQUEST_PRIZE_GAMEEVENT(cltMsg* pclMsg,SI32 id);
	// �б� �̺�Ʈ
	void DoMsg_GAMEMSG_REQUEST_SETSCHOOLEVENT(cltMsg* pclMsg , SI32 id) ;
	// ������ �ݰ� �̺�Ʈ
	//void DoMsg_GAMEMSG_REQUEST_COUNTATTACK_INFO(cltMsg* pclMsg , SI32 id);
	// ���� õ�� �̺�Ʈ
	void DoMsg_GAMEMSG_REQUEST_EVENTNPC(cltMsg* pclMsg , SI32 id);
	// ĳ���� �λ縻
	void DoMsg_GAMEMSG_REQUEST_SETGREETING(cltMsg* pclMsg , SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETGREETING(cltMsg* pclMsg , SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SITDOWN(cltMsg* pclMsg , SI32 id);

	// Ȩ������ ����.
	void DoMsg_GAMEMSG_REQUEST_GET_HOMEPAGE_URL(cltMsg* pclMsg , SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SET_HOMEPAGE_URL(cltMsg* pclMsg , SI32 id);


	// ��Ȱ�� ������ ���ǿ� ���� ����
	void DoMsg_GAMEMSG_REQUEST_REVIVE(cltMsg* pclMsg , SI32 id);
	void DoMsg_GAMEMSG_REQUEST_RESURRECTION(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GET_WEAPONSKILLCOST(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SET_WEAPONSKILL(cltMsg* pclMsg,SI32 id);


	void DoMsg_GAMEMSG_REQUEST_MYPUCHIKOMIURL(cltMsg* pclMsg, SI32 id);	// �ڽ��� Ǫġ�ڹ� ����
	
	void DoMsg_GAMEMSG_REQUEST_USERPUCHIKOMIURL( cltMsg* pclMsg, SI32 id);

	// ����ã�� �̺�Ʈ - ��ī�� 10���� ���� ����������?
	void DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_USEOKARA(cltMsg* pclMsg , SI32 id);

	//-------------------------------------------------
	// �ӼӸ�
	//-------------------------------------------------
	// Server-System.cpp
	// �ӼӸ� ����.
	void DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_CREATE(cltMsg* pclMsg, SI32 id);
	// �ӼӸ� �ʴ�.
	void DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_INVITE(cltMsg* pclMsg, SI32 id);
	// ���� �ӼӸ� ������ ����Ʈ ������
	void DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_USERLIST(cltMsg* pclMsg, SI32 id);
	// �ӼӸ� ����.
	void DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_OUT(cltMsg* pclMsg, SI32 id);


	// Person�� ��� ������ �������ش�
	void DoMsg_GAMEMSG_REQUEST_DECREASESKILLBONUS(cltMsg* pclMsg, SI32 id);
	// �� Ǯ���ֱ�. 
	void DoMsg_GAMEMSG_REQUEST_HORSEFREE(cltMsg* pclMsg, SI32 id);
	//KHY - 1001 - ��µ��� 5���� ���� ����.// ���ٲ۴�.
	void DoMsg_GAMEMSG_REQUEST_CHANGEHORSE(cltMsg* pclMsg, SI32 id);
	// ���� ���̵� ��û( �̴� Ȩ�������� ������ ���ؼ�.)
	void DoMsg_GAMEMSG_REQUEST_USERID(cltMsg* pclMsg, SI32 id);
	// ���� �÷��� �ð� ��û. 
	void DoMsg_GAMEMSG_REQUEST_PLAYTIME(cltMsg* pclMsg, SI32 id);
	// ĳ������ �߰������� ��û 
	void DoMsg_GAMEMSG_REQUEST_ADDINFO(cltMsg* pclMsg, SI32 id);
	// ĳ������ ���� ������ �ٲپ���.
	void DoMsg_GAMEMSG_REQUEST_CHANGEMAGIC(cltMsg* pclMsg, SI32 id);


	// NPC ��ġ ��û. 
	void DoMsg_GAMEMSG_REQUEST_NPCPOS(cltMsg* pclMsg, SI32 id);	
	// Ŭ���̾�Ʈ�� ��Ʈ��Ʈ ��û. 
	void DoMsg_GAMEMSG_REQUEST_HEARTBEAT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CHAT(cltMsg* pclMsg, SI32 id);
	// �Ӹ� ����. (CharUnique)
	void DoMsg_GAMEMSG_REQUEST_SECRETCHAT(cltMsg* pclMsg, SI32 id);
	// �Ӹ� ä�� �ۼ� ��û(PersonID)
	void DoMsg_GAMEMSG_REQUEST_MAKESECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_ACCEPTSECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id);

	// �Ӹ��� ������ ��û�Ѵ�. 
	void DoMsg_GAMEMSG_REQUEST_HEADCHAT(cltMsg* pclMsg, SI32 id);
	// ���� ����Ʈ ��û 
	void DoMsg_GAMEMSG_REQUEST_ASKLIST(cltMsg* pclMsg, SI32 id);
	// ���� ���� ��û 
	void DoMsg_GAMEMSG_REQUEST_DELASK(cltMsg* pclMsg, SI32 id);
	// ���� ��� ��û. 
	void DoMsg_GAMEMSG_REQUEST_SKILLMASTERLIST(cltMsg* pclMsg, SI32 id);
	// ���� ���/���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_REGISTMASTER(cltMsg* pclMsg, SI32 id);
	// ���� ���� ��� �뺸. 
	void DoMsg_GAMEMSG_REQUEST_HOPETOQUIT(cltMsg* pclMsg, SI32 id);
	// ����Ʈ�� �ǵ��ư��� �뺸
	void DoMsg_GAMEMSG_REQUEST_HOPETOFRONT(cltMsg* pclMsg,SI32 id);
	// �ش� ������ Warp�� ����� 
	void DoMsg_GAMEMSG_REQUEST_WARPVILLAGE(cltMsg* pclMsg, SI32 id);
	// �ֹ��� �ڱ� ������ Warp�� ����� 
	void DoMsg_GAMEMSG_REQUEST_RESIDENTWARPVILLAGE(cltMsg* pclMsg, SI32 id);

	// ���� �Ǽ� 
	void DoMsg_GAMEMSG_REQUEST_GETBYUNGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETGONGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETHYUNGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETHOZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETIZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETYEZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETGOONZUINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SETBYUNGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETBYUNGZOINFO_VILLAGEWARINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETGONGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETHYUNGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETHYUNGZOPRISON(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETHOZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETIZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETYEZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETGOONZUINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GETANGELAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETANGELLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETANGELAPPLYER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETANGEL(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GETCHANGEDNAME(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_AUTOHUNTING(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_AUTOHUNTING_ASK(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SETPOLICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETPOLICELIST(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SETCRIMINAL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETCRIMINALLIST(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GOONZU_SETMINISTER(cltMsg* pclMsg,SI32 id);

	// ���ְ� ���� ���� ����
	void DoMsg_GAMEMSG_REQUEST_GOONZU_SETLIQUIDATION(cltMsg* pclMsg,SI32 id);

	// ���ְ� ���ʽ� Ÿ���� ����
	void DoMsg_GAMEMSG_REQUEST_GOONZU_GETBONUSTIME(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GOONZU_SETBONUSTIME(cltMsg* pclMsg,SI32 id);

	// ȯ�� ����
	void DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_REJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_REJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PARTYINVITE_REJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_FRIENDADD_REJECT(cltMsg* pclMsg, SI32 id);

	// �ɸ��� �ɼǼ���
	void DoMsg_GAMEMSG_REQUEST_CHAR_OPTION(cltMsg* pclMsg, SI32 id);
	
	// �������ͽ� �ʱ�ȭ ��û - �����ʱ�ȭ�̿�� ���
	void DoMsg_GAMEMSG_REQUEST_INITSTATUS(cltMsg* pclMsg, SI32 id);

	// �̸��� ������ ��û�Ѵ�.
	void DoMsg_GAMEMSG_REQUEST_CHANGENAME(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_HUNTMAPWARP(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PERSONALSHOPWARP(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_FRIENDWARP(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PARTYWARP(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_PVPMAPWARP(cltMsg* pclMsg,SI32 id);
	// 30���� �������� ���ۿֱ� ������ ������
	void DoMsg_GAMEMSG_REQUEST_WARJOIN(cltMsg* pclMsg,SI32 id);

	// ��ڰ� ������� �α׸� ��û�Ѵ�.
	void DoMsg_GAMEMSG_REQUEST_PERSONAL_LOG(cltMsg* pclMsg, SI32 id);

	// Server-LogIn.cpp
	void DoMsg_GAMEMSG_REQUEST_MAKENEWCHAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_LOGIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DELUSERCHAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PREDELUSERCHAR(cltMsg* pclMsg, SI32 id);//�ɸ��ͻ��������Ⱓ[����]
	void DoMsg_GAMEMSG_REQUEST_SELECTCHAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HANAUTH_LOGIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TAIWAN_LOGIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HANAUTH_GAMERUNAUTH(cltMsg* pclMsg, SI32 id);
	
	// Ŭ���̾�Ʈ�� �غ�Ǿ���. 
	void DoMsg_GAMEMSG_REQUEST_READY(cltMsg* pclMsg, SI32 id);


	// Server-Item.cpp
	// �������� �ٴڿ� ����߸���. 
	void DropItem(SI32 mapindex, SI32 x, SI32 y, cltItem* pclitem, SI32 droppersonid);

	void DoMsg_GAMEMSG_REQUEST_ITEMMOVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMCHANGE(cltMsg* pclMsg, SI32 id);
	void UseItemAction(SI32 id, cltItemUseInfo* pcliteuseinfo);
	void DoMsg_GAMEMSG_REQUEST_USEITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMSPLIT(cltMsg* pclMsg, SI32 id);

	// �ͼӾ������� �ı��Ұ��� ��û
	void DoMsg_GAMEMSG_REQUEST_BELONGITEM_DESTROY(cltMsg* pclMsg, SI32 id);

	// �����ۺ��� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM_RECIEVE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_INVREPAIR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_INVDROP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ENCHANT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_INVPICKUP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MAKEITEMSWITCH(cltMsg* pclMsg, SI32 id);
	// �κ����� �������� ���� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_MAKEITEMINV(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_REQUEST_ENCHANTITEMINV(cltMsg* pclMsg, SI32 id);

	// ������ �Ⱓ���� ��û.
	void DoMsg_GAMEMSG_REQUEST_ENCHANT_USEDAYPLUS(cltMsg* pclMsg, SI32 id);

	// ������ �Ӽ� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_CHANGEENCHANT(cltMsg* pclMsg, SI32 id);

	// ������Լ� ��ȯ���� ������ �̵� ��û
	void DoMsg_GAMEMSG_REQUEST_SUMMONPUSHITEM(cltMsg* pclMsg, SI32 id);
	// ��ȯ������ ������Է� ������ �̵���û
	void DoMsg_GAMEMSG_REQUEST_SUMMONPOPITEM(cltMsg* pclMsg, SI32 id);

	// NPC���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_NPCREPAIR(cltMsg* pclMsg, SI32 id);
	// NPC���� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_NPCREPAIRPRICE(cltMsg* pclMsg, SI32 id);
	// WEAPON 1,2 Activate���� 
	void DoMsg_GAMEMSG_REQUEST_EXCHANGEWEAPON(cltMsg* pclMsg, SI32 id);

	// ���ݼ���κ��� ������ ������ ��û
	void DoMsg_GAMEMSG_REQUEST_INV_ChangItemFromNPC(cltMsg* pclMsg,SI32 id);

	// �к����� ��û
	void DoMsg_GAMEMSG_REQUEST_INV_CANCELLATIONSEALINGUP(cltMsg* pclMsg,SI32 id);

	// ������ ����â
	void DoMsg_GAMEMSG_REQUEST_MAKEITEMINVINDEX(cltMsg* pclMsg,SI32 id);

	// ��æƮâ 
	void DoMsg_GAMEMSG_REQUEST_ENCHANTITEMINVINDEX(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ENCHANTITEMSTARTOREND(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ENCHANTOTHERSHOW(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ENCHANTOTHERPRICE(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ENCHANTITEMSWITCH(cltMsg* pclMsg,SI32 id);

	// clothes 1,2 Activate���� 
	void DoMsg_GAMEMSG_REQUEST_EXCHANGECLOTHES(cltMsg* pclMsg, SI32 id);


	// ������ ���׷��̵�( �Ϲ� -> ȣǰ -> ��ǰ -> �ű� ) - Ȥ�θ� ���� �̿���� ����ؼ�
	void DoMsg_GAMEMSG_REQUEST_UPGRADEITEM(cltMsg* pclMsg, SI32 id);
	// ������ ���� ���׷��̵�( Ȥ�θ� ���� )
	void DoMsg_GAMEMSG_REQUEST_PERFORMANCEUPGRADEITEM(cltMsg* pclMsg, SI32 id);

	// �̴� ���� : ���� �ֽ�ȸ�縦 �����Ѵ�.
//	void DoMsg_GAMEMSG_REQUEST_MONSTERCORP_START(cltMsg* pclMsg,SI32 id);

	// �̴� ���� : ���� �ֽ�ȸ�� ����
	void DoMsg_GAMEMSG_REQUEST_MONSTERCORP_SCORE(cltMsg* pclMsg,SI32 id);

	// �̴� ���� : ���� �ֽ�ȸ�� �޺�����
	void DoMsg_GAMEMSG_REQUEST_MONSTERCORP_COMBOINFO(cltMsg* pclMsg,SI32 id);

	// �̴� ���� : �ڴ�� ���� ����
	void DoMsg_GAMEMSG_REQUEST_ROULETTEGAME_INFO(cltMsg* pclMsg,SI32 id);

	// �̴� ���� : �ڴ�� ����
	void DoMsg_GAMEMSG_REQUEST_ROULETTEGAME_STOP(cltMsg* pclMsg,SI32 id);

	//Server-Structure.cpp
	void DoMsg_GAMEMSG_REQUEST_REPAIRSTRUCTURE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_CHIEFINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STRINFO(cltMsg* pclMsg, SI32 id);
	// ���� �� �����߿��� Ư�� �ǹ��� ������ ��û
	void DoMsg_GAMEMSG_REQUEST_VILLAGEINFOSTRINFO(cltMsg* pclMsg, SI32 id);
	// ���� ��ũ�� �����Ѵ�
	void DoMsg_GAMEMSG_REQUEST_SETVILLAGEMARK(cltMsg* pclMsg, SI32 id);
	// ���� ������ �����Ѵ�
	void DoMsg_GAMEMSG_REQUEST_SETVILLAGEMAP(cltMsg* pclMsg, SI32 id);
	// ���� ���� ���� ��û 
	void DoMsg_GAMEMSG_REQUEST_GETTAXLIST(cltMsg* pclMsg, SI32 id);
	// ���� ����
	void DoMsg_GAMEMSG_REQUEST_SETTAX(cltMsg* pclMsg, SI32 id);
	// ���� ����
	void DoMsg_GAMEMSG_REQUEST_PAYTAX(cltMsg* pclMsg, SI32 id);

	// ��� ���� ����Ʈ ��û 
	void DoMsg_GAMEMSG_REQUEST_GETDIVIDENDLIST( cltMsg *pclMsg, SI32 id );

	// ��� �ϱ� ��û 
	void DoMsg_GAMEMSG_REQUEST_PAYDIVIDEND( cltMsg *pclMsg, SI32 id );

	// ���� �ֹ� ���
	void DoMsg_GAMEMSG_REQUEST_RESIDENTSHARE( cltMsg *pclMsg, SI32 id );

	// ���� �ֹ�(NPC) ��� ��û
	void DoMsg_GAMEMSG_REQUEST_HIRENPC( cltMsg *pclMsg, SI32 id );

	// ���� �ֹ�(NPC) �޿� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_NPCPAYMENT( cltMsg *pclMsg, SI32 id );


	void DoMsg_GAMEMSG_REQUEST_GETNPCLIST( cltMsg *pclMsg, SI32 id );			// ���� �ֹ�(NPC) ����Ʈ ��û 

	void DoMsg_GAMEMSG_REQUEST_APPLYRESIDENT( cltMsg *pclMsg, SI32 id );		// �ֹ� ��� ��û 
	void DoMsg_GAMEMSG_REQUEST_APPLYRESIDENT2( cltMsg *pclMsg, SI32 id );		// [����] ����, ����. �������� �ʴ�� ���� �ֹε�� ��û.
	void DoMsg_GAMEMSG_REQUEST_CANCELRESIDENT( cltMsg *pclMsg, SI32 id );		// �ֹ� ��� ��� 
	void DoMsg_GAMEMSG_REQUEST_BERESIDENT( cltMsg *pclMsg, SI32 id );			// �ֹ� ��� ��û �㰡
	void DoMsg_GAMEMSG_REQUEST_RESIDENTAPPLYERLIST( cltMsg *pclMsg, SI32 id );	// �ֹ� ��û�� ����Ʈ ��û 
	void DoMsg_GAMEMSG_REQUEST_RESIDENTLIST( cltMsg *pclMsg, SI32 id );			// �ֹ� ����Ʈ ��û 
	void DoMsg_GAMEMSG_REQUEST_RESIDENTINFO( cltMsg *pclMsg, SI32 id );			// �ֹ� ���� ��û 
	void DoMsg_GAMEMSG_REQUEST_SETRESIDENTSCORE( cltMsg *pclMsg, SI32 id );		// �ֹ� ���� �ο� 

	void DoMsg_GAMEMSG_REQUEST_SETSTRUCTUREMESSAGE( cltMsg *pclMsg, SI32 id );	// �ȳ��� ���� 

	void DoMsg_GAMEMSG_REQUEST_VILLAGEBOARD(cltMsg *pclMsg, SI32 id );

	// �������� 
	void DoMsg_GAMEMSG_REQUEST_DECLAREWAR( cltMsg *pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_CANCELDECLAREWAR( cltMsg *pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_SETSYMBOLSTATUS( cltMsg *pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SETCASTLESTATUS( cltMsg *pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_GETVILLAGEINFO( cltMsg *pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_RESIDENTSLIST( cltMsg *pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_GETSTRNOTICE( cltMsg *pclMsg, SI32 id );


	void DoMsg_GAMEMSG_REQUEST_ALLSTRCHIEFINFO( cltMsg *pclMsg, SI32 id );

	// Server-Bank.cpp
	void DoMsg_GAMEMSG_REQUEST_INPUTTOBANK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_OUTPUTFROMBANK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_OUTPUTFROMBANKALLMONEY(cltMsg* pclMsg, SI32 id);	// ������ ��� ���(������ ����)
	void DoMsg_GAMEMSG_REQUEST_SETBANKFEE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CREATEBANKACCOUNT(cltMsg* pclMsg, SI32 id);		// ���¸� �����϶�� ��û.
	void DoMsg_GAMEMSG_REQUEST_CLOSEBANKACCOUNT(cltMsg* pclMsg, SI32 id);		// ���¸� �����϶�� ��û.
	void DoMsg_GAMEMSG_REQUEST_INPUTTOBANKALLMONEY(cltMsg* pclMsg, SI32 id);	// ������ ��� �Ա� 

	// Server-Stock.cpp
	void DoMsg_GAMEMSG_REQUEST_BUYSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SELLSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CANCELSTOCKORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STOCKORDERINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETSTOCKFEE(cltMsg* pclMsg, SI32 id);


	// ���� �ֽ� ��� 
	void DoMsg_GAMEMSG_REQUEST_STOCKBIDVILLAGELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STOCKBIDDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BIDSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CANCELBIDSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STOCKBIDDATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BUYBIDSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MYSTOCKINFO(cltMsg* pclMsg, SI32 id);

	// �ֽ� ����	
	void DoMsg_GAMEMSG_REQUEST_STOCKDISTRIBUTIONORDER(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GETBEGINNERVILLAGESTOCK(cltMsg* pclMsg, SI32 id);


	// tys
	void DoMsg_GAMEMSG_REQUEST_STOCKOFFERINGORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STOCKOFFERINGINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_EXCHANGESTOCK(cltMsg* pclMsg, SI32 id);

	// Server-PostOffice.cpp
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMSG(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVMONEYLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVMSGLIST(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETMONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_DELMSG(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SETFEE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETRECORD(cltMsg* pclMsg, SI32 id);

	//[����] ��ü������ ��ü �޽��� ������. => 2008-8-4
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDITEM_GROUP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY_GROUP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMSG_GROUP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_POSTOFFICE_USER_LIST_GROUP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CHAR_NAME_CHECK(cltMsg* pclMsg, SI32 id);

	//-------------------------------------
	// ���� ���� ���� �� �� ������ ������ ã��
	//-------------------------------------	
	void DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERITEMLIST(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MARKETCONDITIONS(cltMsg* pclMsg, SI32 id);


	// �纹�� 
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_MYACCOUNT(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_OUTHORSE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_SELLHORSE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_BUYHORSE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HORSEMARKET_SETFEE(cltMsg* pclMsg, SI32 id );


	// �Ű�
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_MYORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_SELL(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_BUY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_SETFEE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_DETAILINFO(cltMsg* pclMsg, SI32 id );

	// �忹��
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_MYORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_SELL(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_BUY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_SETFEE(cltMsg* pclMsg, SI32 id );


	// ����
	void DoMsg_GAMEMSG_REQUEST_LAND_CHANGECONTRACT(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_UNITLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_UNITDETAIL(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_RENTAPPLY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_CANCELAPPLY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_APPLYERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_DELAPPLYER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_LAND_RENT(cltMsg* pclMsg, SI32 id );

	// ���ڽ� 
	void DoMsg_GAMEMSG_REQUEST_FEAST_RESERVE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_ADDPRESENTLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_DELPRESENTLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_SETCOST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_STGITEMIN( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_STGITEMOUT( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_GIVEITEM( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FEAST_SENDCHAT( cltMsg* pclMsg, SI32 id );

	//#if defined(_LEON_FEAST_EFFECT)
	void DoMsg_GAMEMSG_REQUEST_FEAST_USEEFFECT( cltMsg* pclMsg, SI32 id );
	//#endif
	
	//[����] ��ƼȦ. 
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_TOTAL_INFO( cltMsg* pclMsg, SI32 id );						// ��Ƽ�� ��ü ����.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_ADD_PRESENT( cltMsg* pclMsg, SI32 id );					// ����� ��Ƽ�忡 ���� �߰�.
	void DoMsg_GAMEMSG_REQUEST_GAMEMSG_REQUEST_PARTYHALL_RESERVATION( cltMsg* pclMsg, SI32 id );	// ��Ƽ�� ���� ��û.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION( cltMsg* pclMsg, SI32 id );			// ���� ��û.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_GET_COSTUME( cltMsg* pclMsg, SI32 id );					// �� ���.	=> 2008. 3. 12
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION_LIST( cltMsg* pclMsg, SI32 id );		// ���� ��û��  ����Ʈ.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_ADD_DECORATION( cltMsg* pclMsg, SI32 id );					// ���ǰ �߰�.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_GIVEITEM( cltMsg* pclMsg, SI32 id );						// ���� �ֱ�.
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_EXIT( cltMsg* pclMsg, SI32 id );								
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_INVITATION( cltMsg* pclMsg, SI32 id );						// ��Ƽ�� �ʴ�.		
	void DoMsg_GAMEMSG_REQUEST_PARTYHALL_USEEFFECT( cltMsg* pclMsg, SI32 id );						// ��Ƽ�� ����.		

	// �񺯻�
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_MYORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_SELL(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_BUY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SUMMONHEROMARKET_SETFEE(cltMsg* pclMsg, SI32 id );

	// ����
	void DoMsg_GAMEMSG_REQUEST_MINE_CHANGECONTRACT(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_UNITLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_UNITDETAIL(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_RENTAPPLY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_CANCELAPPLY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_APPLYERLIST(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_DELAPPLYER(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MINE_RENT(cltMsg* pclMsg, SI32 id );


	// Server-CityHall.cpp
	void DoMsg_GAMEMSG_REQUEST_INVESTLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BECHIEF(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CANDIDATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CANCELCANDIDATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CANDIDATELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DELCANDIDATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_RESIGN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETSTRUCTURELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BUILDSTRUCTURE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_DESTROYSTRUCTURE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_VILLAGENOTICE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_PROFITTOCAPITALFUND( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_STARTEVENT( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_VILLAGELEVELDETAILINFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_CHANGESTRBASEMONEY( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_HIREEVENTNPC( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_DONATEVILLAGEMONEY( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_EVENT_INSERTMATERIAL( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_DONATEMEMBERLIST( cltMsg* pclMsg, SI32 id );

	//Server-Market.cpp
	void DoMsg_GAMEMSG_REQUEST_SELLITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETFROMMARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MARKETORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BUYITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETMARKETFEE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PRODUCTPRICE( cltMsg* pclMsg, SI32 id );

	//Server-House.cpp
	void DoMsg_GAMEMSG_REQUEST_CHANGEHOUSECONTRACT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITLIST_DETAIL(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_REQUEST_HOUSEAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSERENTAPPLY(cltMsg* pclMsg, SI32 id);
	//������� �ؾ�

	void DoMsg_GAMEMSG_REQUEST_HOUSECANCELLATIONPENALTYMONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSECANCELLATION(cltMsg* pclMsg, SI32 id);
	// Ư�� ���������� ���� ��û�� ����Ѵ�. 
	void DoMsg_GAMEMSG_REQUEST_HOUSERENTAPPLYCANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSERENT(cltMsg* pclMsg, SI32 id);
	// �κ����� â��� �������� �̵�. 
	void DoMsg_GAMEMSG_REQUEST_MOVEITEMINVTOSTG(cltMsg* pclMsg, SI32 id);
	// â���� �κ����� ������ �̵�. 
	void DoMsg_GAMEMSG_REQUEST_MOVEITEMSTGTOINV(cltMsg* pclMsg, SI32 id);
	// â�������� ��û. 
	void DoMsg_GAMEMSG_REQUEST_STGINFO(cltMsg* pclMsg, SI32 id);
	// â���� �������� ���� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_MAKEITEM(cltMsg* pclMsg, SI32 id);
	// ���� ���� ����� ����� �����Ѵ�. 
	void DoMsg_GAMEMSG_REQUEST_DELHOUSEAPPLYER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITSTABLECREATE(cltMsg* pclMsg, SI32 id);
	// ������ ���� �־� �޶�� ��û
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITHORSEIN(cltMsg* pclMsg, SI32 id);
	// �������� ���� ���� �޶�� ��û
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITHORSEOUT(cltMsg* pclMsg, SI32 id);	
	// �������� ������ �����϶�� ��û
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITUSEDGOODSBUILDINGCREATE(cltMsg* pclMsg, SI32 id);
	// ������ �������� �̾Ƴ��� ���� ������ ����
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO(cltMsg* pclMsg, SI32 id);
	// ������ �������� �̾Ƴ���� ��û
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODS(cltMsg* pclMsg, SI32 id);
	// â�� �̸� ����
	void DoMsg_GAMEMSG_REQUEST_HOUSEUNITNAMECHANGE(cltMsg* pclMsg, SI32 id);
	// â�� ������ ����
	void DoMsg_GAMEMSG_REQUEST_HOUSEITEMARRANGEMENT(cltMsg* pclMsg, SI32 id);

	//-------------------------------------------------------------
	// ���, �����, ���� ���� ���� ���� ����

	//-------------------------------------------------------------
	// ����
	// Server-Agriculture.cpp
	// �ڵ� ����
	void DoMsg_GAMEMSG_REQUEST_AGRICULTUREAUTOGAIN(cltMsg* pclMsg, SI32 id);


	//-------------------------------------------------------------
	// ���
	// Server-Farming.cpp
	//-------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_FARMINGSTART(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_FARMINGPAYRENTFEE(cltMsg* pclMsg, SI32 id);

	//-------------------------------------------------------------
	// ����
	// Server-Mining.cpp
	//-------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_MININGSTART(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MININGPAYRENTFEE(cltMsg* pclMsg, SI32 id);



	// Server-RealEstate.cpp
	// �ε��� ��� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_EXTENDCONTRACT(cltMsg* pclMsg, SI32 id);


	//Server-NPC.cpp
	void DoMsg_GAMEMSG_REQUEST_SELLNPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BUYNPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NPCSELLITEMINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_INVESTMENTGETINFO(cltMsg* pclMsg, SI32 id);

	// 1:1 �ŷ� ��û
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE(cltMsg* pclMsg, SI32 id);
	// �ŷ� ���.
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_CANCEL(cltMsg* pclMsg, SI32 id);	
	// �ŷ� ��Ͽ� ������ �߰� ��û
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDITEM(cltMsg* pclMsg, SI32 id);
	// �ŷ� ��Ͽ��� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_DELLIST(cltMsg* pclMsg, SI32 id);	
	// �ŷ� ��Ͽ��� ������ ���� ��û
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_DELITEM(cltMsg* pclMsg, SI32 id);	
	// ���� �ŷ�
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDPRICE( cltMsg* pclMsg, SI32 id );
	// �ֽ� �ŷ�
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDSTOCK( cltMsg* pclMsg, SI32 id );
	// ���� �ŷ�
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDHOUSEUNIT( cltMsg* pclMsg, SI32 id );
	// �� �ŷ�
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDHORSE( cltMsg* pclMsg, SI32 id );
	// ���� �ŷ����� �� ����� ���� 
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_MYACCEPT(cltMsg* pclMsg, SI32 id);
	// ���� �ŷ����� �� ����� ���
	void DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_MYCANCEL(cltMsg* pclMsg, SI32 id);




	//------------------------------------------------------------
	// ��Ƽ	
	// ��Ƽ ����
	//void DoMsg_GAMEMSG_REQUEST_PARTY_CREATE( cltMsg* pclMsg, SI32 id );
	// ��Ƽ �ʴ�( ��Ƽ ������ �ȵ� ��Ȳ������ ���� )
	void DoMsg_GAMEMSG_REQUEST_PARTY_CREATEINVITE( cltMsg* pclMsg, SI32 id );
	// ��Ƽ �ʴ� ������ ���Ҷ�( ��Ƽ ������ �ȵ� ��Ȳ������ ���� )
	void DoMsg_GAMEMSG_REQUEST_PARTY_CREATEJOIN( cltMsg* pclMsg, SI32 id );
	// ��Ƽ �ʴ�
	void DoMsg_GAMEMSG_REQUEST_PARTY_INVITE( cltMsg* pclMsg, SI32 id );
	// ��Ƽ �ʴ� ����
	void DoMsg_GAMEMSG_REQUEST_PARTY_INVITEREJECT( cltMsg* pclMsg, SI32 id );
	// ��Ƽ ����
	void DoMsg_GAMEMSG_REQUEST_PARTY_JOIN( cltMsg* pclMsg, SI32 id );
	// ��Ƽ Ż��
	void DoMsg_GAMEMSG_REQUEST_PARTY_LEAVE( cltMsg* pclMsg, SI32 id );
	// ��Ƽ ��������
	void DoMsg_GAMEMSG_REQUEST_PARTY_FORCELEAVE( cltMsg* pclMsg, SI32 id );
	// ��Ƽ ���� ����Ʈ ��û
	void DoMsg_GAMEMSG_REQUEST_PARTY_ALLUSERLIST( cltMsg* pclMsg, SI32 id );	
	// ��Ƽ ������ ȹ�� ��� ����
	void DoMsg_GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN( cltMsg* pclMsg, SI32 id);

	// [����] ��Ƽ��Ī���� �߰��� �޼��� ó�� �Լ���
	void DoMsg_GAMEMSG_REQUEST_PARTY_WANTJOIN( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_PARTY_WANTJOINRESULT( cltMsg* pclMsg, SI32 id );
	//------------------------------------------------------------


	//------------------------------------------------------------
	// ģ��
	void DoMsg_GAMEMSG_REQUEST_FRIENDADD( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_FRIENDDEL( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDADDACCEPT( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_REJECTFRIENDADD( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDMEMO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDMEMOSET( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDCHANGEGROUP( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_FRIENDCHANGEGROUPNAME( cltMsg* pclMsg, SI32 id );
	//------------------------------------------------------------


	//------------------------------------------------------------
	// ��ǥ
	void DoMsg_GAMEMSG_REQUEST_VOTEKINGSELECTION( cltMsg* pclMsg, SI32 id );
	// [����] ���Žý��� : ����Ȱ�� ����
	void DoMsg_GAMEMSG_REQUEST_STARTELECTIONSTUMP( cltMsg* pclMsg, SI32 id );
	// [����] ���Žý��� : ����Ȱ�� ����
	void DoMsg_GAMEMSG_REQUEST_ENDELECTIONSTUMP( cltMsg* pclMsg, SI32 id );
	// [����] ���Žý��� : �ɸ��� ������ �ʱ�ȭ �Ǽ� ���� ������ �ٽ� �����޶�� ��û
	void DoMsg_GAMEMSG_REQUEST_ELECTIONSTUMP( cltMsg* pclMsg, SI32 id );
	// [����] ���Žý��� : ���� ��ǥ�� �������� �̵��϶�
	void DoMsg_GAMEMSG_REQUEST_WARPTOPOLLMAP( cltMsg* pclMsg, SI32 id );
	// [����] ���Žý��� : ���� ��ǥâ�� �����
	void DoMsg_GAMEMSG_REQUEST_VOTEKINGAVAILABLE( cltMsg* pclMsg, SI32 id );
	// [����] �����ý��� : ��ǥ ���� ������ ��û
	void DoMsg_GAMEMSG_REQUEST_STARTVOTESTATUS( cltMsg* pclMsg, SI32 id );
	//------------------------------------------------------------

	//------------------------------------------------------------
	// Daily ����Ʈ
	void DoMsg_GAMEMSG_REQUEST_DAILYQUESTLIST( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuestSelect( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuestSituation( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuestEnd( cltMsg* pclMsg, SI32 id );	
	//------------------------------------------------------------

	//------------------------------------------------------------
	// Dail ����Ʈ2
	void DoMsg_GAMEMSG_REQUEST_DAILYQUEST2LIST( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest2Select( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest2Situation( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest2End( cltMsg* pclMsg, SI32 id );	
	//------------------------------------------------------------
	//------------------------------------------------------------
	// Dail ����Ʈ3
	void DoMsg_GAMEMSG_REQUEST_DAILYQUEST3LIST( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest3Select( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest3Situation( cltMsg* pclMsg, SI32 id );	
	void DoMsg_GAMEMSG_REQUEST_DailyQuest3End( cltMsg* pclMsg, SI32 id );	
	//------------------------------------------------------------

	//-----------------------------------------------------------------------
	// ItemMall
	void DoMsg_GAMEMSG_REQUEST_ITEMMALLEXISTENCE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMMALLITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMMALLGETITEM(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_CHANGE_CHARKIND(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NOLIMITTICKET_WARP(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_WARP_TARGETWORLD(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GET_SEL_PGLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GET_ITEMMALL_ITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GET_MYCASH_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMMALL_BUYITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ITEMMALL_GIFTITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CHECK_ACCOUNTID(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BILLPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_LOGINPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GACHAPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CHANGE_HERO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PRESENT_ANSWER(cltMsg* pclMsg, SI32 id);

	//---------------------------------------
	// ���� ���� 
	//---------------------------------------
	void DoMsg_GAMEMSG_REQUEST_PERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PERSONALSHOPDATA(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_STARTPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_STOPPERSONALSHOP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_BUYPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SELLPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SEARCHPERSONALSHOPITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MAKEPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MAKEPERSONALSHOP_MANUFACTUER(cltMsg* pclMsg, SI32 id);	// �����Ƿ� �������̽� ���� 
	
	//---------------------------------------

	//---------------------------------------
	// ��ȯ�� 
	//---------------------------------------
	void DoMsg_GAMEMSG_REQUEST_SUMMONFREE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONNAMECHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONREVIVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_USESUMMONBONUS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TAKEINOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONATTACKCHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONEVOLVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONSCROLL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMON_STATUSINIT(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMON_SETAUTOHEAL(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SUMMONUSETON(cltMsg* pclMsg, SI32 id);// ��ȯ���� ���� �������� �ڴ´�,.
	void DoMsg_GAMEMSG_REQUEST_SUMMONSLOTIN(cltMsg* pclMsg, SI32 id);// Base�� �ִ� ��ȯ���� Slot���γִ´�.
	void DoMsg_GAMEMSG_REQUEST_SUMMONSLOTOUT(cltMsg* pclMsg, SI32 id);//��ȯ���� Slot���� ������.

	void DoMsg_GAMEMSG_REQUEST_SUMMON_TRANSFORM(cltMsg* pclMsg, SI32 id); //[����] ��ȯ�� ����.
	//---------------------------------------

	// ��õ�� ���
	void DoMsg_GAMEMSG_REQUEST_RECOMMENDPERSON( cltMsg* pclMsg, SI32 id );

	// �ڸ� ���� ����
	void DoMsg_GAMEMSG_REQUEST_CAPTIONKINDCHANGE( cltMsg* pclMsg, SI32 id );

	// ������ �ܱ� ����( û, �Ϻ� ) NPC ���� ��ǰ �Ǹ� �۾�
	void DoMsg_GAMEMSG_REQUEST_SELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id);
	// ������ ���� ���� NPC �� �������� �������� �������� ��û
	void DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTNPCBUYINFO(cltMsg* pclMsg, SI32 id);
	// ������ ���� ���� NPC �� ���� ���� ĳ�� �������� �������� ��û( �������� )
	void DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEMINFO(cltMsg* pclMsg, SI32 id);
	// ������ ���� ���ο��� ĳ�� ������ �Ǹ�
	void DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEM(cltMsg* pclMsg, SI32 id);
	// ������ NPC ���Լ� �ڽ��� ��õ����Ʈ�� �˾ƿ�
	void DoMsg_GAMEMSG_REQUEST_GETRECOMMANDPOINT(cltMsg* pclMsg, SI32 id);
	// ������ NPC���Լ� ��õ����Ʈ�� �������� ������.
	void DoMsg_GAMEMSG_REQUEST_BUYRECOMMANDPRODUCT(cltMsg* pclMsg, SI32 id);
	// ������ ��õ������ ����� ĳ���͵��� ����� ����
	void DoMsg_GAMEMSG_REQUEST_RECOMMANDPOINTLIST(cltMsg* pclMsg, SI32 id);
	// ������ NPC�� ���� ������ ����
	void DoMsg_GAMEMSG_REQUEST_MANUFACTURENPC( cltMsg* pclMsg, SI32 id );
	// �ʺ��� ���� �ޱ�
	void DoMsg_GAMEMSG_REQUEST_RECEIVEBEGINNERITEM( cltMsg* pclMsg, SI32 id );

	// ������ �ܱ����ο� ��ǰ �Ǹ��ϱ� ���� �Ⱓ�� ���� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_PRESELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id);

	// ���� ������ ���� �����ϴ� ������ ��û
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYINFO(cltMsg* pclMsg, SI32 id);
	// ���� ���ο��� ������ ǰ�� �Ǹ�
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMFROMPERSON(cltMsg* pclMsg, SI32 id);
	// ������ ���� �����ϴ� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTHORSEBUYINFO(cltMsg* pclMsg, SI32 id);
	// ������ ���� ����
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYHORSEFROMPERSON(cltMsg* pclMsg, SI32 id);
	// ������ ������ �����ϴ� ������ ��û
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMINFO(cltMsg* pclMsg, SI32 id);
	// ������ ������ ����
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEM(cltMsg* pclMsg, SI32 id);
	// ������ ��ȯ�� ��� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYSUMMONINFO(cltMsg* pclMsg,SI32 id);
	// ������ ��ȯ���� ����
	void DoMsg_GAMEMSG_REQUEST_SUMMONTRADE(cltMsg* pclMsg,SI32 id);
	// ��ȯ���� ĳ���ͷ� ����
	void DoMsg_GAMEMSG_REQUEST_SELECT_SUMMONCHAR(cltMsg* pclMsg,SI32 id);

	//��ũ��
	void DoMsg_GAMEMSG_RESPONSE_RECORD_ACTION( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_RECORD_ACTION_FINISHED( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_GZFTP_PROTOCOL( cltMsg* pclMsg, SI32 id );

	//Server-Auth.cpp
	void DoMsg_AUTHMSG_RESPONSE_GAMEAUTH(sPacketHeader* pPacket);
	void DoMsg_AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH(sPacketHeader* pPacket);
	void DoMsg_AUTHMSG_RESPONSE_GMTOOLAUTH(sPacketHeader* pPacket);
	
	//Server-Bill.cpp
	void DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW(sPacketHeader* pPacket);
	void DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW_WEB(sPacketHeader* pPacket);
	void DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW_GACHA(sPacketHeader* pPacket);

	//Server-Horse.cpp
	// ���� Ÿ��� ��û�� ���� ó��. 
	void DoMsg_GAMEMSG_REQUEST_RIDEHORSE(cltMsg* pclMsg, SI32 id);
	// ������ ������� ��û�� ���� ó��
	void DoMsg_GAMEMSG_REQUEST_UNRIDEHORSE(cltMsg* pclMsg, SI32 id);
	// �� �̸� ����
	void DoMsg_GAMEMSG_REQUEST_HORSENAMECHANGE(cltMsg* pclMsg, SI32 id);
	// �������ʱ�ȭ�̿������ �ʱ�ȭ ��Ų��.
	void DoMsg_GAMEMSG_REQUEST_HORSEINIT(cltMsg* pclMsg, SI32 id);
	// ���ʽ��� �� �ɷ�ġ�� �ø���.
	void DoMsg_GAMEMSG_REQUEST_USEHORSE_BONUS(cltMsg* pclMsg, SI32 id);
	// ���� ǰ���� �����Ѵ�.
	void DoMsg_GAMEMSG_REQUEST_CHANGE_HORSETYPE(cltMsg* pclMsg,SI32 id);
	// ���ɷ�����̿���� �̿��ؼ� �ɷ� ����� ��Ų��.
	void DoMsg_GAMEMSG_REQUEST_HORSE_ADDSTATUS(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_BLACKARMYAPPLY(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BLACKARMY_RANKINFO(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_BLACKARMY_WARPTOGATE(cltMsg* pclMsg,SI32 id);

	//--------------------------------------
	// ������ 
	//--------------------------------------
	// �����忡 ����. 
	void DoMsg_GAMEMSG_REQUEST_ENTERHUNT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTADD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTDEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HUNTMONSTERIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_HUNTMONSTEROUT(cltMsg* pclMsg, SI32 id);

	//---------------------------------------
	// ���� �� ����. 
	//---------------------------------------
	// ���� �� ���� ��û . 
	void DoMsg_GAMEMSG_REQUEST_VILLAGEDETAILINFO(cltMsg* pclMsg, SI32 id);



	//---------------------------------------
	// ���� ��ȸ
	//---------------------------------------
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_SUGGEST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_VOTE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_ACCEPTCANDIDATE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_VOTE_REFRESH(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_PARTICIPATE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHATJOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHATOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHAT(cltMsg* pclMsg, SI32 id);

	// ���� ���� ����
	void DoMsg_GAMEMSG_REQUEST_SETCOUNTRYINFO( cltMsg *pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SETSHOWCOUNTRY( cltMsg *pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_USERLISTBYCOUNTRY( cltMsg *pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ADDCHINESEUSER( cltMsg *pclMsg, SI32 id);

	// �ڽ��� Ǫġ�ڹ� ���� ����
	void DoMsg_GAMEMSG_REQUEST_SETSHOWPUCHIKOMI( cltMsg *pclMsg, SI32 id );

	// Server-WorldMoney.cp
	void DoMsg_GAMEMSG_REQUEST_DISTRIBUTION_WORLDMONEY(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_WORLDMONEY_TRADELIST(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_WORLDMONEY_SELLORDER(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_WORLDMONEY_BUYORDER(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_WORLDMONEY_CANCELORDER(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_SET_SELLORDER(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_CANCEL_SELLORDER(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_SET_BUYORDER(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_LISTINFO(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_MYINFO(cltMsg*pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_SAVEDACU_LIST(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU(cltMsg*pclMsg,SI32 id);

	// WorldPassport( ���� ���� )
	void DoMsg_GAMEMSG_REQUEST_WORLDPASSPORT_SET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_WORLDPASSPORT_EXTEND(cltMsg* pclMsg, SI32 id);


	// 20�̸� ���� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_LOWLEVELLIST( cltMsg*pclMsg,SI32 id );

	void DoMsg_GAMEMSG_REQUEST_SETEMOTICON( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GAME_GUARD_AUTH( cltMsg*  pclMsg , SI32 id );

	// Server-Guild
	void DoMsg_GAMEMSG_REQUEST_GUILD_CREATEGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_DESTROYGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_JOINGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_CONFIRMJOINGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_LEAVEGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_CHANGEVILLAGE( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_GETGUILDLIST( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_GETGUILDINFO( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_CONFIRMCREATEGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_SETSECONDMASTER( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_GIVEGUILDMONEY( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GUILD_SETSTRFEERATE(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_CHANGESTATUS(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_SETMARK(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_CHANGENAME(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_CHANGEMASTER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDWAR_RESERVELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDWAR_APPLYRESERVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_APPLYLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_APPLY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_STATUS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_MEMBERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_GETVILLAGELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDWAR_APPLYTOENEMY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDWAR_CONFIRMAPPLY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILDWAR_RECOMMANDLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GUILD_NOTCONNECTMASTER_CHANGEMASTER(cltMsg* pclMsg, SI32 id);	// �Ѵ��̻� ������� ���� �������� ���������
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_MAPREGISTER(cltMsg* pclMsg, SI32 id);	// ��� ����� ���� �ʵ�� 
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_WARREGISTER(cltMsg* pclMsg, SI32 id);	// ��� ����� ����� ��û
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_REQUEST(cltMsg* pclMsg, SI32 id);	// ��� ����� Request�� ���� ���
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_TOP10(cltMsg* pclMsg, SI32 id);		// �� �ʸ��� ������ top 10	
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_SERVERTIME(cltMsg* pclMsg, SI32 id);	// ��� ����� ���� ��Ȯ�� �����ð��� �޾� �´�.
	void DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_HAVEMAP(cltMsg* pclMsg, SI32 id);	// ��� ����͸� ��û �ߴ����˾ƿ�
		// ����
	void DoMsg_GAMEMSG_REQUEST_GACHAPRODUCT_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GACHABUY(cltMsg* pclMsg, SI32 id);

	// ����2
	void DoMsg_GAMEMSG_REQUEST_GACHA2PRODUCT_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GACHA2BUY(cltMsg* pclMsg, SI32 id);

	// �̿� ����
	void DoMsg_GAMEMSG_REQUEST_CARRYOVER_GACHA_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CARRYOVER_SELECTPRODUCT_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CARRYOVER_GACHABUY(cltMsg* pclMsg, SI32 id);

	// ���ĸ��� �̺�Ʈ
	void DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_ENTERFIELD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_WARP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_NAMINGQUEST_START(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETPERSONCURRENTNAMING(cltMsg* pclMsg, SI32 id);
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	void DoMsg_GAMEMSG_REQUEST_HAPPYBEANQUEST_START(cltMsg* clMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SYSTEMREWARDLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_RECIEVESYSTEMREWARD(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_ATTEND(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_ATTENDREWARDITEM(cltMsg* pclMsg, SI32 id );

	//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
	void DoMsg_GAMEMSG_REQUEST_CHARSERVERRTN(cltMsg* pclMsg, SI32 id );
	
	// ����
	void DoMsg_GAMEMSG_REQUEST_CREATEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_DESTROYEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_INVITEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_JOINEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SECEDEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_EMPIREINFO(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_SETEMPIREMONEY(cltMsg* pclMsg, SI32 id );

	//[�߰� : Ȳ���� 2007. 12. 3 => Ŭ���̾�Ʈ���� ������ �������α׷� �������.]
	void DoMsg_GAMEMSG_REQUEST_AUTOMACRO_ON(cltMsg* pclMsg, SI32 id );
	
	//[�߰� : Ȳ���� 2007. 12. 11 => �ų� �̺�ư ��ư�� Ŭ���̾�Ʈ���� ���� ����. C->S]
	void DoMsg_GAMEMSG_REQUEST_NEWYEAR_CLICK(cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_START(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_CANCEL(cltMsg* pclMsg, SI32 id );
	
	// [����] ����ã�� �̺�Ʈ
	void DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_KILLNPC(cltMsg* pclMsg, SI32 id );
	
	//KHY - 1220 - ���Žý���.
	void DoMsg_GAMEMSG_REQUEST_TRANSFORM(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRANSFORM_END(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRANSFORM_USEITEM(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_OILLING_USEITEM(cltMsg* pclMsg,SI32 id);	
	//[�߰� : Ȳ���� 2008. 1. 9 => �ν���Ʈ����.]
	void DoMsg_GAMEMSG_REQUEST_INSTANTSDUNGEON_STATUS(cltMsg* pclMsg,SI32 id);

	//���� ���� ����Ʈ - 2008.01.08 �ռ���
	void DoMsg_GAMEMSG_REQUEST_HOFLIST(cltMsg* pclMsg,SI32 id);

	//��ŷ ����Ʈ - 2008.01.08 �ռ���
	void DoMsg_GAMEMSG_REQUEST_RAKINGLIST(cltMsg* pclMsg,SI32 id);

//******************************************************************************************
//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ���� �޽��� ó��. C->S]
	
	void DoMsg_GAMEMSG_REQUEST_SPACE_BOX_LIST(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_TRESURE_BOX_LIST(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM(cltMsg* pclMsg,SI32 id);		//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���� ����. C->S]
	void DoMsg_GAMEMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM(cltMsg* pclMsg,SI32 id);	//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���� ȸ��. C->S]

//******************************************************************************************
	//--------------------------------------------------------------
	// �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� �޽���. C -> S
	//--------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_ARTIFACT_MIXTURE(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ARTIFACT_REMOVE(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ARTIFACT_SLOT_CREATE(cltMsg* pclMsg,SI32 id);
	
	void DoMsg_GAMEMSG_REQUEST_OPENBIGITEMBOX(cltMsg* pclMsg,SI32 id);
	
//******************************************************************************************

	// [����] CRC üũ ��û - 2008.02.29
	void DoMsg_GAMEMSG_REQUEST_FILECRCCHECK(cltMsg* pclMsg,SI32 id);
	// [����] ������ : �δ� ���� �������� ���
	void DoMsg_GAMEMSG_REQUEST_PIRATESHIP_ENTERFIELD(cltMsg* pclMsg,SI32 id);
	//KHY - 1113 - ũ�������� �̺�Ʈ - ����� �и� ����.
	void DoMsg_GAMEMSG_REQUEST_CHRISTMASEVET_ENTERFIELD(cltMsg* pclMsg,SI32 id);
	// PCK : 08.06.04 : �������ÿ� ����ð� ���
	void DoMsg_GAMEMSG_REQUEST_FARMINGENDTIME(cltMsg* pclMsg, SI32 id);

	// [����] ������ ���� �̺�Ʈ �����귿 ������ ����ϴ� ��Ŷ. => 2008-6-10
	void DoMsg_GAMEMSG_REQUEST_BUFF_ROULETTE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_BALANCECURRENCY_BUFF(cltMsg* pclMsg, SI32 id);
	
	// [����] ���� �̺�Ʈ ��ŷ ���� ��û. => 2008-6-20
	void DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_RANK_INFO(cltMsg* pclMsg, SI32 id);

	// [����] ���� �̺�Ʈ ���ʽ� �������� �̵� ��û. => 2008-6-24
	void DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_BONUS_STAGE(cltMsg* pclMsg, SI32 id);
	// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_QUEST_START(cltMsg* pclMsg, SI32 id);
	// [����] ���� �̺�Ʈ �δ� �κ� ���� ��û
	void DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_LOBBY_ENTERFIELD(cltMsg* pclMsg, SI32 id);
	// [���] ��ȯ�� ���¹̳� ����
	void DoMsg_GAMEMSG_REQUEST_SUMMON_SPTCHARGE(cltMsg* pclMsg, SI32 id);
	// [����] ��Ƽ Ŭ���̾�Ʈ ���� ����
	void DoMsg_GAMEMSG_REQUEST_CHECKPROCESS(cltMsg* pclMsg,SI32 id);

	//---------------------------------
	//[����] ȣ�ڻ���. => 2008-9-16
	//---------------------------------
	void DoMsg_GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_ADD(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_GET(cltMsg* pclMsg,SI32 id);

	//---------------------------------

	void DoMsg_GAMEMSG_REQUEST_CHAR_ROULETTE(cltMsg* pclMsg,SI32 id);

	void DoMsg_GAMEMSG_REQUEST_VILLAGE_RESIDENT_INVITE(cltMsg* pclMsg,SI32 id);
	
	void DoMsg_GAMEMSG_REQUEST_PVP_FILED(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_UI_INFOGET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_APPLY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_CANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_AGAIN_RESERVE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_QUESTION_LIST_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_QUESTION_CONTENTS_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CHECK_QUESTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ADD_QUESTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ADD_ANSWER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE_RESULT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DEL_QUESTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_DEL_ANSWER(cltMsg* pclMsg, SI32 id);
	
	

	// PVP_League
	void DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE(cltMsg* pclMsg, SI32 id);

	// �ų� �귿
	void DoMsg_GAMEMSG_REQUEST_DIVINATION_ROULETTE(cltMsg* pclMsg,SI32 id);

	//[����] ������.
	void DoMsg_GAMEMSG_REQUEST_ELIXIR_NPC_ITEM_TYPE_LIST_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ELIXIR_NPC_CHANGE_ITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_ELIXIR_SET(cltMsg* pclMsg, SI32 id);

	// [����] �߷�Ÿ�� ���� �ַγ� Ŀ���̳Ĵ� ������ ���� �亯
	void DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_REQUEST(cltMsg* pclMsg, SI32 id);
	// [ ����] �߷�Ÿ�ε����� ������ ������Ʈ �Ѵ�.
	void DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_INFOGET(cltMsg* pclMsg, SI32 id);

	// [����] ���ο� ���û��� ���� ������
	void DoMsg_GAMEMSG_REQUEST_NEWSELECTBOX_SELECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NEWSELECTBOX_GETITEM(cltMsg* pclMsg, SI32 id);

	//=============================================================================================
	// [����] ���ո���.
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_NEWMARKETACCOUNT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NEWMARKETITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NEWSELLITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_GETFROMNEWMARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NEWBUYITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_SETNEWMARKETFEE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_PERSONNAME_SERIALID(cltMsg* pclMsg,SI32 id);
	
	//=============================================================================================
	// [����] ���θ���.
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_PROMOTER_INFO_TOTAL_GET(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_PROMOTER_INFO_GET(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_PROMOTER_URL_GET(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_PROMOTERNPC_GIVE_ITEM_GET(cltMsg* pclMsg, SI32 id );

	// [����] ��ȥ �ý���
	void DoMsg_GAMEMSG_REQUEST_PROPOSE_QUESTION(cltMsg* pclMsg, SI32 id );				// �������� ����
	void DoMsg_GAMEMSG_REQUEST_PROPOSE_ANSWER(cltMsg* pclMsg, SI32 id );				// �������� �亯
	void DoMsg_GAMEMSG_REQUEST_WEDDINGANNIVERSARY_ITEMGET(cltMsg* pclMsg, SI32 id );	// ��ȥ ����� ������ �ޱ� ��û

	void DoMsg_GAMEMSG_REQUEST_WEDDING_RESERVE(cltMsg* pclMsg, SI32 id );				// ��ȥ ���� �ϱ�
	void DoMsg_GAMEMSG_REQUEST_WEDDING_SIMPLELIST_GET(cltMsg* pclMsg, SI32 id );		// ��ȥ ���� ���� ����Ʈ �ޱ�
	void DoMsg_GAMEMSG_REQUEST_WEDDING_QUESTION_ANSWER(cltMsg* pclMsg, SI32 id );		// ��ȥ ���� ������ ���� ���
	void DoMsg_GAMEMSG_REQUEST_WEDDING_LIST_GET(cltMsg* pclMsg, SI32 id );				// ��ȥ ���� ����Ʈ �ޱ�
	void DoMsg_GAMEMSG_REQUEST_WEDDING_HALL_ENTER(cltMsg* pclMsg, SI32 id );			// ��ȥ���� ����
	void DoMsg_GAMEMSG_REQUEST_WEDDING_RESERVE_CANCEL(cltMsg* pclMsg, SI32 id );		// ��ȥ ���� ����ϱ�
	void DoMsg_GAMEMSG_REQUEST_MARRIAGEMATE_WARP(cltMsg* pclMsg, SI32 id );				// ����ڿ��� �����ϱ�

	void DoMsg_GAMEMSG_REQUEST_BALANCECANUSECURRENCY(cltMsg* pclMsg, SI32 id );			// [��ȣ] ��� ���� ��ȭ�� �䱸

	// [����]���� �ý���
	void DoMsg_GAMEMSG_REQUEST_FAMILY_REQUEST_ADD_FAMILY(cltMsg* pclMsg, SI32 id );		// [����] ���� �ý��� - �ڳ� ��� ��û
	void DoMsg_GAMEMSG_REQUEST_FAMILY_ADD_FAMILY(cltMsg* pclMsg, SI32 id );				// [����] ���� �ý��� - �ڳ� ���
	void DoMsg_GAMEMSG_REQUEST_FAMILY_DEL_CHILDREN(cltMsg* pclMsg, SI32 id );			// [����] ���� �ý��� - �ڳ� ���� 
	void DoMsg_GAMEMSG_REQUEST_FAMILY_WARP(cltMsg* pclMsg, SI32 id );						// [����] ���� �ý��� - Ÿ�� �������� ���� 
	void DoMsg_GAMEMSG_REQUEST_FAMILY_PLUS_FAMILYEFFECT(cltMsg* pclMsg, SI32 id );			// [����] ���� �ý��� - �ڳ� ���� 
	void DoMsg_GAMEMSG_REQUEST_FAMILY_CHAT(cltMsg* pclMsg, SI32 id );						// [����] ���� �ý��� - Ÿ�� �������� ���� 

	// [����] ��ȣ����
	void DoMsg_GAMEMSG_REQUEST_SOULGUARD_STATUSINOUT(cltMsg* pclMsg, SI32 id );						// [����] ��ȣ���� : ��ȯ/����
	void DoMsg_GAMEMSG_REQUEST_SOULGUARD_CHANGENAME(cltMsg* pclMsg, SI32 id );						// [����] ��ȣ���� : �̸�����
	void DoMsg_GAMEMSG_REQUEST_SOULGUARD_DEAD(cltMsg* pclMsg, SI32 id );							// [����] ��ȣ���� : ����/Ǯ���ֱ�

	void DoMsg_GAMEMSG_REQUEST_SOULGUARD_HOUSE_CHANGE(cltMsg* pclMsg, SI32 id );					// [����] ĳ���Ϳ� �ִ� ��ȣ���ɰ� �����ҿ� �ִ� ��ȣ������ �¹ٲ۴�
	void DoMsg_GAMEMSG_REQUEST_SOULGUARD_HOUSE_CREATE(cltMsg* pclMsg, SI32 id );					// [����] ��ȣ���ɺ����� ���� �ø�

	// [ ���� ] ���� ���ϱ��̺�Ʈ
	//Switch_10MonthEvent_RacoonDodge
	void DoMsg_GAMEMSG_REQUEST_RACOONDODGEEVENTRESERVATION(cltMsg* pclMsg, SI32 id );				// [����] ���� ���ϱ� �̺�Ʈ ���� ��û 
	void DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_REQUEST_PLAYEVENT(cltMsg* pclMsg, SI32 id );		// [����] ���� ���ϱ� ���� ����
	void DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_OVER5SECOND_START(cltMsg* pclMsg, SI32 id );		// [����] ���� ���ϱ� �̺�Ʈ 5�� ī��Ʈ�ٿ� ���� ����
	void DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_GET_RESERVE_LIST(cltMsg* pclMsg, SI32 id );		// [����] ���� ���ϱ� �̺�Ʈ 5�� ī��Ʈ�ٿ� ���� ����

	void DoMsg_GAMEMSG_REQUEST_PROMOTER_WARP(cltMsg* pclMsg, SI32 id);								// [����] ���θ��Ͱ� ������ ĳ������ ����.
	// [ ���� ] �޸� ���� �ý���
	void DoMsg_GAMEMSG_REQUEST_DORMANCY_TAKEOUTEQUIPITEMINBOX(cltMsg* pclMsg, SI32 id );			// [����] �޸� ���� �ý���
	void DoMsg_GAMEMSG_REQUEST_DORMANCY_BUYPOINTITEM(cltMsg* pclMsg, SI32 id );						// [����] �޸� ���� �ý���

	//  [8/12/2009 ��ȣ_GAWIBAWIBO]	
	void DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_CHARGED_MONEY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_CALCULATE_RESULT(cltMsg* pclMsg, SI32 id );
	//void DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_COUNT(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_REWARD(cltMsg* pclMsg, SI32 id);
	

	// [����] ���Һ�
	void DoMsg_GAMEMSG_REQUEST_BBB_CHECK_PlAY_CONDITION(cltMsg* pclMsg, SI32 id);			// [����] ���� ���� ���� üũ
	void DoMsg_GAMEMSG_REQUEST_BBB_WAITLIST_ANSWER(cltMsg* pclMsg, SI32 id);				// [����] ���Һ� ����ڸ���Ʈ ����
	void DoMsg_GAMEMSG_REQUEST_BBB_WAITLIST_CANCEL(cltMsg* pclMsg, SI32 id);				// [����] ��� ����Ʈ ��� ��û (Ŭ��->����)
	void DoMsg_GAMEMSG_REQUEST_BBB_WARPMAPANSWER(cltMsg* pclMsg, SI32 id);					// [����] 1���� ������� "�����ҷ���?"�� ���� ���� (Ŭ��->����)
	void DoMsg_GAMEMSG_REQUEST_BBB_ALREADYRESERVED(cltMsg* pclMsg, SI32 id);				// [����] �̹� ���������� ����

	// [����] 2010�ų��̺�Ʈ
	void DoMsg_GAMEMSG_REQUEST_2010NEWYEAREVENT_QUESTCANCEL(cltMsg* pclMsg, SI32 id);		// [����] �� ���� �޼���ó��

	void DoMsg_GAMEMSG_REQUEST_NEWNPCREPAIR(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_NEWITEMREPAIR(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_NEWITEMREPAIRREQUESTINFO(cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_REQUEST_FESTIVAL_EVENT_ENTERFIELD_EVENTAREA(cltMsg* pclMsg, SI32 id );		// [����] ���� �̺�Ʈ �������� �̵� ��û

	void DoMsg_GAMEMSG_REQUEST_HALLOWEENSPIRITBOX_OK(cltMsg* pclMsg, SI32 id );		// [��ȣ] �ҷ��� ���Ǹ� �ڽ�

	void DoMsg_GAMEMSG_REQUEST_MONSTERCREATE(cltMsg* pclMsg, SI32 id);				// [���] ���� ������û

	void DoMsg_GAMEMSG_REQUEST_PERSONSLOTNUMCHANGE(cltMsg* pclMsg, SI32 id);		// [����] ĳ���� �����ҿ��� �����´�
	
	void DoMsg_GAMEMSG_REQUEST_EQUIPMENTCREATE(cltMsg* pclMsg, SI32 id);			// [���] ��� ������û

	void DoMsg_GAMEMSG_REQUEST_SKILLBOOK_BUYITEM(cltMsg* pclMsg, SI32 id);			// []
	void DoMsg_GAMEMSG_REQUEST_SKILLBOOK_SUBMAGIC_DEL(cltMsg* pclMsg, SI32 id);		//

	//-------------------------------------------------------------------------------------------------------------------
	//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	//-------------------------------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_RACCOONEVENT_TOGOONZU(cltMsg* pclMsg, SI32 id);		//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	void DoMsg_GAMEMSG_REQUEST_GOONZURACCOONEVENT_SETINFO(cltMsg* pclMsg, SI32 id);		//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

	//=============================================================================================
	// [����] ��Ʋ�ξ�
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_BATTLEROYAL_REMAINEDTIME(cltMsg* pclMsg, SI32 id);	// [����] ��� ���� �ϱ� ���� ���� �ð� 
	void DoMsg_GAMEMSG_REQUEST_BATTLEROYAL_MOVETOSTADIUM(cltMsg* pclMsg, SI32 id);	// [����] ��������� �̵� 

	//=============================================================================================
	// [����] �߷�Ÿ���̺�Ʈ
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_VALENTINEEVENT_GIVE_PRESENT_TONPC(cltMsg* pclMsg, SI32 id);	// [����] NPC���� ���� �ֱ�
	void DoMsg_GAMEMSG_REQUEST_VALENTINEEVENT_ISHOLDING(cltMsg* pclMsg, SI32 id);	// [����] �̺�Ʈ ������

	//---------------------------------------------------------------------------------------------
	// [ ����] �ʺ��� ��Ƽ ����Ʈ �ý��� (��Ƽ��Ī)
	void DoMsg_GAMEMSG_REQUEST_PARTYMATCHING_LEVEL(cltMsg* pclMsg, SI32 id);		// [����] ��������â - ���� ���� ���� üũ ��û.
	void DoMsg_GAMEMSG_REQUEST_APPYLYTOPARTYJOIN( cltMsg* pclMsg, SI32 id);			// [����] ��Ƽ��ȸâ - ��Ƽ ���� ��û ��û.	
	void DoMsg_GAMEMSG_REQUEST_CREATEMYPARTY( cltMsg* pclMsg, SI32 id);				// [����] ��Ƽ��ȸâ - �� ��Ƽ ����� ��û.
	void DoMsg_GAMEMSG_REQUEST_CREATECOMPLETEPARTY( cltMsg* pclMsg, SI32 id);		// [����] ��Ƽ�����â - �ʿ����� �Է� �� ��Ƽ ����ڴٰ� ��û.
	void DoMsg_GAMEMSG_REQUEST_REMOVEPARTYMATCHING( cltMsg* pclMsg, SI32 id );		// [����] ��Ƽ��ȸâ - ���� ����� ��Ƽ��Ī ����
	void DoMsg_GAMEMSG_REQUEST_GETPARTYMEMBERNAMELIST( cltMsg* pclMsg, SI32 id );	// [����] ��Ƽ��ȸâ - ������ ��Ƽ��Ī�� ��Ƽ�� �̸� ���� ��û



	void DoMsg_GAMEMSG_REQUEST_PARTY_QUEST_CHECKSTART( cltMsg* pclMsg, SI32 id);	// [��ȣ] ��Ƽ����Ʈ ���۽� ���� üũ	
	void DoMsg_GAMEMSG_REQUEST_PARTY_QUEST_START( cltMsg* pclMsg, SI32 id);			// [��ȣ] ��Ƽ����Ʈ ����

	//[����] ��� ���� ���.
	void DoMsg_GAMEMSG_REQUEST_CONTRIBUTION_ITEM_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CONTRIBUTION_ITEM_INPUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_CONTRIBUTION_MAKE_NPC(cltMsg* pclMsg, SI32 id);
	
	void DoMsg_GAMEMSG_REQUEST_GIANTRACCOON_RESURRECT_EVENT_ITEM_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_NPOTRACCOON_ITEM_GET(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_SEARCHMANUFACTURE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_REQUEST_GORACCOONWORLD(cltMsg* pclMsg, SI32 id);		//[����] �������� �̵� �ϱ� 
	// [����] ���� ���� ���ڿ��� �������� �ش� 
	void DoMsg_GAMEMSG_REQUEST_OPEN_LEVEL_LIMIT_BOX(cltMsg* pclMsg,SI32 id);	//[����] ���� ���� ���� ���� 

	void DoMsg_GAMEMSG_REQUEST_JustItemUse(cltMsg* pclMsg,SI32 id);	//[����] // �׾��� ���� ���Ȳ�̴� �������� ���δ�

	//[����] �߷�Ÿ�� ���� ���� ������.
	void DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_ITEM_PACKING(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_BUY_ITEM(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_QUESTION(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_ANSWER(cltMsg* pclMsg,SI32 id);
	
	


//---------------------------------------------------------------------------------------------
//
//									Response Function Area
//
//---------------------------------------------------------------------------------------------
	// ServerDB-Guild
	void DoMsg_DBMSG_RESPONSE_GUILD_CREATEGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_DESTROYGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_JOINGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CONFIRMJOINGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_LEAVEGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CHANGEVILLAGE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CHANGEGUILDPOINT(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_GETGUILDINFO(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_SETSECONDMASTER(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_GIVEGUILDMONEY(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_GIVE_FEE(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_CHANGESTATUS(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_SETSTRFEERATE(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_LEVELUP(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_SETMARK(sPacketHeader* pPacket);
	void DOMSG_DBMSG_RESPONSE_GUILD_CHANGENAME(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CHANGEMASTER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CLOSEGUILD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDWAR_ADDRESERVE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDWAR_RESERVELIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_APPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_SAVESTATUS(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_LOADSTATUS(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_TRANSFEROWNERSHIP(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_CHECKDESTROY_MONTH(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILD_NOTCONNECT_GUILDMASTER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_REGLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_GETTOP10(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_RESULT(sPacketHeader* pPacket);
	
//	void DoMsg_DBMSG_RESPONSE_GUILD_CHANGEVILLAGELIST(sPacketHeader* pPacket);
	

	//Server-DB.cpp

	// ���� �ð��� ���´�. 
	// ���� �ð��� ������ �������� ������ �������� �ʴ´�. 
	bool RequestGameTimeFromDB();

	// �� ������ Ÿ���� �ҷ��´�. 
	bool RequestMapTypeFromDB();


	// ������ ���� �۵��� DB�κ��� ���� ���´�. 
	bool InitializeDB1();
	bool InitializeDB2();
	void DoDBMsg( sPacketHeader* pPacket );
	void DoDBMsg2( sPacketHeader* pPacket );
	void DoLogMsg( sPacketHeader* pPacket );

	// Person
	// ���� ��� ��û ��û. 
	void DoMsg_GAMEMSG_REQUEST_APPLYFATHER(cltMsg* pclMsg, SI32 id);
	// ���� ��� ��û�� ��� ��û. 
	void DoMsg_GAMEMSG_REQUEST_FATHERAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	// ���� ����Ʈ ��û 
	void DoMsg_GAMEMSG_REQUEST_UPDATECHILDLIST(cltMsg* pclMsg, SI32 id);	
	// ������ ���ڸ� ¥����
	void DoMsg_GAMEMSG_REQUEST_RENOUNCEPUPIL(cltMsg* pclMsg, SI32 id);	
	// IP�� ������ ���� ��û 
	void DoMsg_GAMEMSG_REQUEST_PERSON_IP(cltMsg* pclMsg, SI32 id);
	// ĳ������ ���� ���� ��û�� ó���Ѵ�. 
	void DoMsg_GAMEMSG_REQUEST_CHANGESTATUSINFO(cltMsg* pclMsg, SI32 id);


	// ���� ����/���� 
	void DoMsg_DBMSG_RESPONSE_SETFATHER(sPacketHeader* pPacket);
	// Person ���� ���� ��û. 
	void DoMsg_DBMSG_RESPONSE_PERSONSIMPLEINFO(sPacketHeader* pPacket);
	// ���� �缺 ������ ����  �뺸. 
	void DoMsg_DBMSG_RESPONSE_INCREASECHILDNUMBER(sPacketHeader* pPacket);
	// ���� ����Ʈ �뺸. 
	void DoMsg_DBMSG_RESPONSE_GETCHILDLIST(sPacketHeader* pPacket);	
	// �������ͽ� �ʱ�ȭ 
	void DoMsg_DBMSG_RESPONSE_INITSTATUS(sPacketHeader* pPacket);
	// �̸� ����
	void DoMsg_DBMSG_RESPONSE_CHANGENAME(sPacketHeader* pPacket);
	// ���� ����
	void DoMsg_DBMSG_RESPONSE_CHANGE_CHARKIND(sPacketHeader* pPacket);

	// ���ݾ��� ����ȴ�. 
	void DoMsg_DBMSG_RESPONSE_CHANGEMONEY(sPacketHeader* pPacket);
	// �ɸ��� ���ӿɼ��� ���� �Ѵ�.
	void DoMsg_DBMSG_RESPONSE_CHAR_OPTION(sPacketHeader* pPacket);
	// �ɸ��� ���ӿɼ��� ������´�
	void DoMsg_DBMSG_RESPONSE_CHAR_GET_OPTION(sPacketHeader* pPacket);	
	// ����ġ��  ����ȴ�. 
	void DoMsg_DBMSG_RESPONSE_CHANGEEXP(sPacketHeader* pPacket);	
	// �� ����ġ�� ����ȴ�.
	void DoMsg_DBMSG_RESPONSE_CHANGEFAMEEXP(sPacketHeader* pPacket);	
	// ���� �ű��.
	void DoMsg_DBMSG_RESPONSE_MOVEMONEY(sPacketHeader* pPacket);	
	// ����Ʈ ����. 
	void DoMsg_DBMSG_RESPONSE_SETQUESTINFO(sPacketHeader* pPacket);
	// ����Ʈ ����. 
	void DoMsg_DBMSG_RESPONSE_SETSPECIALQUESTINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETPERSONNAMINGINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETPERSONCURRENTNAMING(sPacketHeader* pPacket);

	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����Ʈ ���� ���� �� ���� ������ ��� �´�.
	void DoMsg_DBMSG_RESPONSE_GETHAPPYBEANQUESTINFO(sPacketHeader* pPacket);

	//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	void DoMsg_DBMSG_RESPONSE_GETEVENTCOUPONINFO(sPacketHeader* pPacket);
	////�����̺�Ʈ [2007.09.10 �ռ���]
	//void DoMsg_DBMSG_RESPONSE_GETAUCTIONEVENTCOUPONINFO(sPacketHeader* pPacket);

	// ��ġ, �����, ������ ���� ����
	void DoMsg_DBMSG_RESPONSE_SETPOSLIFEMANA(sPacketHeader* pPacket);
	// �ǰ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SETHEALTH(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_PERSONLISTINFOGET(sPacketHeader* pPacket);
	// ���ο� Person�� ����������� �˷��ִ� �޽��� ���ν���.
	void DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOCREATE(sPacketHeader* pPacket);
	// ����ڰ� Person�� ���������� DB�� Person�� ��ü ������ ��û�ϴµ� �̶� ������ ��ü ������ ó���ϴ� �Լ�. 
	void DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOGETBYIDNUM(sPacketHeader* pPacket);

	//cyj ������� ������ ���� �޾ƿ��� �Լ�
	void DoMsg_DBMSG_RESPONSE_PERSONITEMINFOGET(sPacketHeader* pPacket);

	//cyj �������� ������ ���� �޾ƿ��� �Լ�
	void DoMsg_DBMSG_RESPONSE_ITEMMAKERNAME(sPacketHeader* pPacket);

	// ���� - ��õ�� ����Ʈ�� ������Ʈ �Ǿ����� �˸�.
	void DOMSG_DBMSG_RESPONSE_CHANGERECOMMENDPOINT(sPacketHeader* pPacket);
	// ���� - ��õ�� ����Ʈ�� �޾ƿ�.
	void DoMsg_DBMSG_RESPONSE_GETRECOMMANDPOINT(sPacketHeader* pPacket);

	// ���� - �Ⱓ���� �������� �������
	void DoMsg_DBMSG_RESPONSE_ENCHANT_USEDAYPLUS(sPacketHeader* pPacket);

	// [����] ������ ��þƮ �Ӽ� ���� - 2008.02.20
	void DoMsg_DBMSG_RESPONSE_CHANGEENCHANT(sPacketHeader* pPacket);

	// Person���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_PERSONTOTALINFODELETE(sPacketHeader* pPacket);
	// Person���� ��û��⿡ ���� ����. 
	void DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOPREDELETE(sPacketHeader* pPacket);
	// Person ���� �����û�� ���� ����. (���ٸ� ��ġ�� ���� ���� ����.)
	void DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOSET(sPacketHeader* pPacket);
	// Person�� �ֽ� ���� ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_PERSONSTOCKACCOUNTGET(sPacketHeader* pPacket);
	// Person�� ��ų ������ ���δ�. 
	void DoMsg_DBMSG_RESPONSE_INCREASESKILL(sPacketHeader* pPacket);
	// Person�� ��ų ������ �����.
	void DoMsg_DBMSG_RESPONSE_DECREASESKILL(sPacketHeader* pPacket);
	// Person�� �������� ��ų ������ �ø���.
	void DoMsg_DBMSG_RESPONSE_SET_WEAPONSKILL(sPacketHeader* pPacket);
	// Person�� ��ų����ġ�� �����Ѵ�.
	void DoMsg_DBMSG_RESPONSE_SETSKILLEXP(sPacketHeader* pPacket);
	// ��� ��ɾ�� Person�� ��ų�� ���δ�.
	void DoMsg_DBMSG_RESPONSE_INCREASEMASTERSKILL(sPacketHeader* pPacket);
	// Person�� ���� ������ �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_SETLEVELINFO(sPacketHeader* pPacket);
	// Person�� ���� ������ �޾ƿ�
	void DoMsg_DBMSG_RESPONSE_USERID(sPacketHeader* pPacket);	
	// �б����  ��û. 
	//	void DoMsg_GAMEMSG_REQUEST_SETSCHOOL(cltMsg* pclMsg, SI32 id);	
	// ���� ���  ��û. 
	void DoMsg_GAMEMSG_REQUEST_SETFATHER(cltMsg* pclMsg, SI32 id);
	// �������� �б� ����� ����û. 
	void DoMsg_GAMEMSG_REQUEST_SCHOOLUSERNUM(cltMsg* pclMsg, SI32 id);
	// ���� �� ���� ��û. 
	void DoMsg_GAMEMSG_REQUEST_PERSONPRIVATEINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REQUEST_PERSONPRIVATEINFOBYPERSONID(cltMsg* pclMsg, SI32 id);
	// ��õ�� ���
	void DoMsg_DBMSG_RESPONSE_RECOMMENDPERSON(sPacketHeader* pPacket);
	// �� ���� 
	void DoMsg_DBMSG_RESPONSE_SETHORSE(sPacketHeader* pPacket);
	// �� Ÿ�� ������  ���� 
	void DoMsg_DBMSG_RESPONSE_SETRIDEHORSE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETAUTOFOOD(sPacketHeader* pPacket);

	// �� �ü� ����
	void DoMsg_DBMSG_RESPONSE_SETCURRENTHORSEPRICE(sPacketHeader* pPacket);
	// �� �ü� ����
	void DoMsg_DBMSG_RESPONSE_GETCURRENTHORSEPRICE(sPacketHeader* pPacket);
	// �� �̸� ����
	void DoMsg_DBMSG_RESPONSE_HORSENAMECHANGE(sPacketHeader* pPacket);
	// ���� ���� ��� ���� 
	void DoMsg_DBMSG_RESPONSE_GUILTYINFORECORD(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_PRIZE_GAMEEVENT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_COUNTATTACK_INFO(sPacketHeader* pPacket);
	// ĳ���� �λ縻
	void DoMsg_DBMSG_RESPONSE_SETGREETING(sPacketHeader* pPacket);

	// Server&DB-Letter.cpp
	// ������ �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_PUSHLETTER(sPacketHeader* pPacket);
	// ������ ������.
	void DoMsg_DBMSG_RESPONSE_POPLETTER(sPacketHeader* pPacket);

	// ������ �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_PUSHACCOUNTLETTER(sPacketHeader* pPacket);
	// ������ ������.
	void DoMsg_DBMSG_RESPONSE_POPACCOUNTLETTER(sPacketHeader* pPacket);

	//Server&DB-Structure.cpp

	void DoMsg_DBMSG_RESPONSE_REPAIRSTRUCTURE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETSTRREPAIRITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETSTRDURA(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_CHANGESTRDURA(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_CHANGESTRMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_CHANGESTRBASEMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETSTRREPAIRAMOUNT(sPacketHeader* pPacket);

	// �ǹ� ������ �����϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SETSTRINFO(sPacketHeader* pPacket);
	// �ǹ� ������ �������  ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETSTRINFO(sPacketHeader* pPacket);
	// �ǹ� ��������� ���´�.
	void DoMsg_DBMSG_RESPONSE_CHIEFINFO(sPacketHeader* pPacket);

	// �ǹ� ���� ���� ����
	void DoMsg_DBMSG_RESPONSE_SETTAX( sPacketHeader* pPacket );

	// �ǹ� ���� ���� �ϱ� ���� 
	void DoMsg_DBMSG_RESPONSE_PAYTAX( sPacketHeader* pPacket );

	// ��� ���� 
	void DoMsg_DBMSG_RESPONSE_PAYDIVIDEND( sPacketHeader* pPacket );

	// �ڵ���� ���� 
	void DoMsg_DBMSG_RESPONSE_AUTOPAYDIVIDEND( sPacketHeader* pPacket );

	// ������ ���ο� ���� ����
	void DoMsg_DBMSG_RESPONSE_PAYFEE( sPacketHeader* pPacket );

	// ���� NPC ��� ��û�� ���� ����
	void DoMsg_DBMSG_RESPONSE_HIRENPC( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_BUILDSTRUCTURE( sPacketHeader *pPacket );
	void DoMsg_DBMSG_RESPONSE_DESTROYSTRUCTURE( sPacketHeader *pPacket );


	void DoMsg_DBMSG_RESPONSE_MANYRESIDENTOUT( sPacketHeader *pPacket );

	// Server&DB-Bank.cpp
	// ���忡 ���� �Ա��϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_INPUTMONEYTOBANK(sPacketHeader* pPacket);
	// ���忡�� ���� ����϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_OUTPUTMONEYFROMBANK(sPacketHeader* pPacket);
	// ���� ������ ������ �����϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SETBANKFEE(sPacketHeader* pPacket);
	// ���¸� ������ ��. 
	void DoMsg_DBMSG_RESPONSE_CREATEBANKACCOUNT(sPacketHeader* pPacket);
	// ���¸� ������ ��. 
	void DoMsg_DBMSG_RESPONSE_CLOSEBANKACCOUNT(sPacketHeader* pPacket);


	// Server&DB-Stock.cpp
	// �ֽ� �ֹ��� DB�� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETMANYSTOCKORDER(sPacketHeader* pPacket);
	// �ֽ� �ŷ��� ����� ���� ���� ó���Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_TRADESTOCK(sPacketHeader* pPacket);
	// �ֹ� ������ DB�� �߰��϶�� ��û�� ���� ������ ó���Ѵ�.
	void DoMsg_DBMSG_RESPONSE_ORDERSTOCK(sPacketHeader* pPacket);
	// �ֽ� �ֹ��� ����϶�� ��û�� ���� ����
	void DoMsg_DBMSG_RESPONSE_CANCELSTOCKORDER(sPacketHeader* pPacket);
	// �ֽ� ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYSTOCKPRICE(sPacketHeader* pPacket);
	// �ֽ� �ŷ� ������ ������ �����϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SETSTOCKFEE(sPacketHeader* pPacket);
	// ���� �ֽĻ�� 
	void DoMsg_DBMSG_RESPONSE_BUYBIDSTOCK(sPacketHeader* pPacket);
	// �� �ֽ� ����
	void DoMsg_DBMSG_RESPONSE_MYSTOCKINFO(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_GETSTOCKBIDVILLAGELIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETSTOCKBIDVILLAGE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_BIDSTOCK(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETSTOCKBIDDERLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_COMPLETESTOCKBIDVILLAGE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_STOCKDISTRIBUTIONORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MAXSTOCKDISTRIBUTIONNUM(sPacketHeader* pPacket);
	/*
	void DoMsg_DBMSG_RESPONSE_GETSTOCKOFFERINGINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETSTOCKOFFERING(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ENDSTOCKOFFERING(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_STOCKOFFERINGORDER(sPacketHeader* pPacket);
	*/

	//#if defined(_CITYHALL_BANKRUPTCY)
	void DoMsg_DBMSG_RESPONSE_RETURNSTOCKBIDVILLAGE(sPacketHeader* pPacket);	// ���� �Ļ�� ���� ���� ����

	void DoMsg_DBMSG_RESPONSE_NOTIFY_CITYHALL_BANKRUPTCY(sPacketHeader* pPacket);	// ���� �Ļ�� Ư�� ���ֿ��� letter�� �˸� ó��
	//#endif

	// �纹��
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_GETMANYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_ORDERSELL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_MYACCOUNT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_OUTHORSE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_BUYHORSE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HORSEMARKET_SETFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REDUCEHORSEORDERPRICE(sPacketHeader* pPacket);


	// �Ű�
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_GETMANYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_ORDERSELL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_MYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_CANCELORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_DELORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_BUY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_SETFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REDUCEREALESTATEORDERPRICE(sPacketHeader* pPacket);



	// �忹��
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_GETMANYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_ORDERSELL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_MYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_CANCELORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_BUY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONMARKET_SETFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REDUCESUMMONORDERPRICE(sPacketHeader* pPacket);


	// �񺯻�
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_GETMANYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_ORDERSELL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_MYORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_BUY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_SETFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REDUCESUMMONHEROORDERPRICE(sPacketHeader* pPacket);



	// ����
	void DoMsg_DBMSG_RESPONSE_MANYLANDUNIT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_CHANGECONTRACT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_RENTAPPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_CANCELRENTAPPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_APPLYERLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_DELAPPLYER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_RENT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_PAYRENTFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_LAND_RECALL(sPacketHeader* pPacket);

	// ����
	void DoMsg_DBMSG_RESPONSE_MANYMINEUNIT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_CHANGECONTRACT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_RENTAPPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_CANCELRENTAPPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_APPLYERLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_DELAPPLYER(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_RENT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_PAYRENTFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MINE_RECALL(sPacketHeader* pPacket);


	// ���ڽ�
	void DoMsg_DBMSG_RESPONSE_FEAST_RESERVE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_OPEN(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_CLOSE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_SETCOST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_ADDPRESENTLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_DELPRESENTLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_STGITEMIN(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_STGITEMOUT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FEAST_GIVEITEM(sPacketHeader* pPacket);

	//#if defined(_LEON_FEAST_EFFECT)
	void DoMsg_DBMSG_RESPONSE_FEAST_USEEFFECT(sPacketHeader* pPacket);
	//#endif
	//[����] ��ƼȦ.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_CLOSE(sPacketHeader* pPacket);						// ��Ƽ�� ����. 
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_ADD_PRESENT(sPacketHeader* pPacket);				// ��Ƽ�� ���� �߰�.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_RESERVATION(sPacketHeader* pPacket);				// ��Ƽ�� ����.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_ADD_DECORATION(sPacketHeader* pPacket);				// ��Ĺ� �߰�.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_RESERVELIST(sPacketHeader* pPacket);				// ��ƼȦ ���� ���� ����Ʈ.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_DECORATION_LIST(sPacketHeader* pPacket);			// ��ƼȦ ��Ĺ� ����Ʈ.
	void DoMsg_DBMSG_RESPONSE_PARTYHALL_GIVEITEM(sPacketHeader* pPacket);					// ��ƼȦ ��Ĺ� ����Ʈ.
	
	

	// ��ü�� 
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_MASTERSENDITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_SENDITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_SENDMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_SENDMSG(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_RECVITEMLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_RECVMONEYLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_RECVMSGLIST(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_GETITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_GETMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_DELMSG(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_SETFEE(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_POSTOFFICE_GETRECORD(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_CHAR_NAME_CHECK(sPacketHeader* pPacket);		//[����] �����̸����� DB���� ���翩�ο� personID ��� => 2008-8-4
	void DoMsg_DBMSG_RESPONSE_FRIEND_INFO(sPacketHeader* pPacket);			//[����] ģ�� ���� ���. => 2008-8-6
	void DoMsg_DBMSG_RESPONSE_GUILD_INFO(sPacketHeader* pPacket);			//[����] ��� ���� ���. => 2008-8-6
	void DoMsg_DBMSG_RESPONSE_VILLAGE_RESIDENT_INFO(sPacketHeader* pPacket);//[����] �ֹ� ���� ���. => 2008-8-6

	//-------------------------------------
	// ���� ���� ���� �� �� ������ ������ ã��
	//-------------------------------------	
	void DoMsg_DBMSG_RESPONSE_GET_SAVEUSERITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GET_SAVEUSERITEMLIST(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_GET_SAVEUSERHORSE(sPacketHeader* pPacket);

	// ��ȯ�� 
	void DoMsg_DBMSG_RESPONSE_SETSUMMON(sPacketHeader* pPacket);	// ��ȯ�� ���� 
	void DoMsg_DBMSG_RESPONSE_SUMMONREVIVE(sPacketHeader* pPacket);	// ��ȯ�� ��Ȱ 
	void DoMsg_DBMSG_RESPONSE_SUMMONEVOLVE(sPacketHeader* pPacket);	// ��ȯ�� ��ȭ 
	void DoMsg_DBMSG_RESPONSE_SUMMONSCROLL(sPacketHeader* pPacket);	// ��ȯ�� ��ȭ 
	void DoMsg_DBMSG_RESPONSE_SUMMON_STATUSINIT(sPacketHeader* pPacket); // ��ȯ�� ���� �ʱ�ȭ
	void DoMsg_DBMSG_RESPONSE_SUMMON_SETAUTOHEAL(sPacketHeader* pPacket); // ��ȯ�� �ڵ� ȸ�� ����
	void DoMsg_DBMSG_RESPONSE_SUMMONTRADE(sPacketHeader* pPacket); // ��ȯ�� NPC���� �ȱ� ����
	void DoMsg_DBMSG_RESPONSE_SUMMON_SLOTIN(sPacketHeader* pPacket); // ��ȯ���� BAse���� Slot�� �ִ´�.
	void DoMsg_DBMSG_RESPONSE_SUMMON_SLOTOUT(sPacketHeader* pPacket); // Slot�� ��ȯ���� ������,.
	
	

	// Server&DB-Item.cpp
	// �κ����� �������� �����϶�� ��û�� ����. 
	void DoMsg_DBMSG_RESPONSE_MAKEITEMINV(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ENCHANTITEMINV(sPacketHeader* pPacket);
	// �������� Person�� ItemPos�� ������� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_INPUTITEMTOPERSON(sPacketHeader* pPacket);
	// �������� Person�� ItemPos���� ����� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_OUTPUTITEMFROMPERSON(sPacketHeader* pPacket);
	// �������� Person�� �� ��ġ���� �ٸ� ��ġ�� �̵��϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MOVEITEM(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_CHANGEITEM(sPacketHeader* pPacket);
	// �������� Person���� �ٸ� Person���� �ű��� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MOVEITEMPERSON(sPacketHeader* pPacket);
	// �������� ����϶�� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_USEITEM(sPacketHeader* pPacket);
	// ������ ������ �Ҹ� ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_WASTEDURABILITY(sPacketHeader* pPacket);	
	// ������ ������ ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_INVREPAIR(sPacketHeader* pPacket);
	// �������� ������. 
	void DoMsg_DBMSG_RESPONSE_DROPITEM(sPacketHeader* pPacket);
	// ���� ����. . 
	void DoMsg_DBMSG_RESPONSE_ENCHANT(sPacketHeader* pPacket);
	// ������ ����. (�ٸ���) 
	void DoMsg_DBMSG_RESPONSE_SETITEM(sPacketHeader* pPacket);
	// ������ ���׷��̵� ( �Ϲ� -> ȣǰ -> ��ǰ -> �ű� ) - Ȥ�θ� ���� �̿���� ����ؼ�.
	void DoMsg_DBMSG_RESPONSE_UPGRADEITEM(sPacketHeader* pPacket);
	// ������ ���� ��� ( �������� ������ ��� ��Ų��. ������ ���̸鼭, ���� ������ ����ϸ鼭.. )
	void DoMsg_DBMSG_RESPONSE_PERFORMANCEUPGRADEITEM(sPacketHeader* pPacket);

	void DOMSG_DBMSG_RESPONSE_STARTPERSONALSHOP(sPacketHeader* pPacket);	// ���λ����� �����Ѵ�.
	void DOMSG_DBMSG_RESPONSE_PERSONALSHOPBUYITEM(sPacketHeader* pPacket);	// ���λ������� ��ǰ�� �����Ѵ�.
	void DOMSG_DBMSG_RESPONSE_PERSONALSHOPSELLITEM(sPacketHeader* pPacket);	// ���λ����� ��ǰ�� �Ǹ��Ѵ�.

	// �Ⱓ�� ������ ����
	//	void DoMsg_DBMSG_RESPONSE_DELETE_LIMITDATEITEM(sPacketHeader* pPacket);
	//	void DoMsg_DBMSG_RESPONSE_GETLIMITUSEITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETPREMIUM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_EXCHANGEITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_OPENTREASUREBOX(sPacketHeader* pPacket);

	//[����] �������ڿ� �������� �Ⱓ�� ������ ����.
	void DoMsg_DBMSG_RESPONSE_USE_SPACEBOX_ITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_USE_TREASURE_ITEM(sPacketHeader* pPacket);

	// [����] ��ȯ�� ������� : ������� ��ȯ���� �̵��� ������ ���
	void DoMsg_DBMSG_RESPONSE_SUMMONPUSHITEM(sPacketHeader* pPacket);
	// [����] ��ȯ�� ������� : ��ȯ������ ������Է� �̵��� ������ ���
	void DoMsg_DBMSG_RESPONSE_SUMMONPOPITEM(sPacketHeader* pPacket);
	// [����] ��ȯ�� ������� : ��ȯ�� �������� ���°� ����Ǿ���
	void DoMsg_DBMSG_RESPONSE_SUMMONITEM_STATUSCHANGE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_REPAIRITEM(sPacketHeader* pPacket);

	// ������ ( Server&DB-Hunt.cpp )
	void DoMsg_DBMSG_RESPONSE_HUNTMONSTERFIELDLISTADD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTSTORAGEMONSTERIN(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTSTORAGEMONSTEROUT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTMONEYCHANGE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTBASEINFOAPPLY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTSTORAGEDECREASEDOLLITEMNUM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTGETENTERFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTPAYSUCCESSMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_HUNTLEFTMONSTERSTGIN(sPacketHeader* pPacket);


	// ģ��( Server&DB-Friend.cpp )
	void DoMsg_DBMSG_RESPONSE_FRIENDADD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDDEL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDADDLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDDELLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDMEMO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDMEMOSET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDCHANGEGROUP(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDCHANGEGROUPNAME(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FRIENDALLLIST(sPacketHeader* pPacket);

	// ��ǥ( Server&DB-Vote.cpp )	
	void DoMsg_DBMSG_RESPONSE_VOTEINIT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_VOTEKINGSELECTION(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_VOTEKINGAGGREGATE(sPacketHeader* pPacket);

	// Daily Quest( Server&DB-DailyQuest.cpp )	
	void DoMsg_DBMSG_RESPONSE_DAILYQUESTADD( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUESTDEL( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUESTCHANGE( sPacketHeader* pPacket);


	// Server&DB-Market.cpp
	// ���� �ֹ��� DB�� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETMANYMARKETORDER(sPacketHeader* pPacket);
	// �ֹ� ������ DB�� �߰��϶�� ��û�� ���� ������ ó���Ѵ�.
	void DoMsg_DBMSG_RESPONSE_ORDERMARKET(sPacketHeader* pPacket);
	// �ֹ� ���� ���� ��û ����. 
	void DoMsg_DBMSG_RESPONSE_REDUCEORDERPRICE(sPacketHeader* pPacket);
	// ���� �ŷ� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_TRADEMARKET(sPacketHeader* pPacket);
	// ���� ���� ���� ��û��  ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MARKETACCOUNT(sPacketHeader* pPacket);
	// ���� â���� �������� ��������� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETITEMFROMMARKET(sPacketHeader* pPacket);
	// ������ ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYITEMPRICE(sPacketHeader* pPacket);
	// ������ ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SETITEMPRICE(sPacketHeader* pPacket);
	// �ŷ� ������ ���� ��û�� ���� ���� 
	void DoMsg_DBMSG_RESPONSE_SETMARKETFEE(sPacketHeader* pPacket);


	// Server&DB-Cityhall.cpp
	// ���� �����ڸ���Ʈ�� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_INVESTLIST(sPacketHeader* pPacket);
	// ���ĺ� �� ���� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_CANDIDATE(sPacketHeader* pPacket);
	// ���ĺ� ����� ���� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_CANCELCANDIDATE(sPacketHeader* pPacket);
	// ���ĺ��ڰ� Ư�� �ź��� �ǵ��� �� ���� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_BERANK(sPacketHeader* pPacket);
	// Ư�� Person�� �ź� ������ ������� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_RANKINFO(sPacketHeader* pPacket);
	// ���ĺ��� ����� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYCANDIDATEINFO(sPacketHeader* pPacket);
	// �ĺ��� ����� ������ ���� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_DELCANDIDATE(sPacketHeader* pPacket);
	// �ź������� �����Ѵٴ� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_RESIGN(sPacketHeader* pPacket);
	// �ź����� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYRANK(sPacketHeader* pPacket);
	// �ź����� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GET_SYSTEMBUYITEMNOWMONEY(sPacketHeader* pPacket);


	void DoMsg_DBMSG_RESPONSE_PROFITTOCAPITALFUND(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_CHANGECITYHALLPROFITMONEY(sPacketHeader* pPacket);

	// ����ϱ�
	void DoMsg_DBMSG_RESPONSE_DONATEVILLAGEMONEY(sPacketHeader* pPacket);
	// ����� ��Ϻ���
	void DoMsg_DBMSG_RESPONSE_DONATEMEMBERLIST(sPacketHeader* pPacket);

	// ����� �̺�Ʈ ��� �ֱ�
	void DoMsg_DBMSG_RESPONSE_EVENT_INSERTMATERIAL(sPacketHeader* pPacket);
	// ����� �̺�Ʈ ��� ���� ����
	void DoMsg_DBMSG_RESPONSE_EVENT_MATERIALLIST(sPacketHeader* pPacket);
	// ����� �̺�Ʈ �ϼ� ó��
	void DoMsg_DBMSG_RESPONSE_EVENT_MATERIALCOMPLETE(sPacketHeader* pPacket);

	// �ֹ� ��� ��û�� ���� ���� 
	void DoMsg_DBMSG_RESPONSE_APPLYRESIDENT(sPacketHeader* pPacket);

	// �ֹ� ��� ��û�� ����Ʈ ���� 
	void DoMsg_DBMSG_RESPONSE_GETRESIDENTAPPLYERLIST(sPacketHeader* pPacket);

	// �ֹ� ����Ʈ ���� 
	void DoMsg_DBMSG_RESPONSE_GETRESIDENTLIST(sPacketHeader* pPacket);

	// �ֹ� ��� �㰡 ���� 
	void DoMsg_DBMSG_RESPONSE_BERESIDENT(sPacketHeader* pPacket);

	// �ֹ� ��� ��û ��� �� �ֹ� ��� ���� ���� 
	void DoMsg_DBMSG_RESPONSE_CANCELRESIDENT(sPacketHeader* pPacket);

	// �ֹ� �� ���� ���� 
	void DoMsg_DBMSG_RESPONSE_GETRESIDENTINFO(sPacketHeader* pPacket);

	// �ֹ� ���� �ο� ���� 
	void DoMsg_DBMSG_RESPONSE_SETRESIDENTSCORE(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_RESIDENTSHARE( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_SETVILLAGEMARK( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETVILLAGEMAP( sPacketHeader* pPacket );

	// �ν��Ͻ� ���� ���ͱ�
	void DoMsg_DBMSG_RESPONSE_SETINSTANCEPROFIT_VILLAGE(sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_CHANGE_INSTANCEPROFIT(sPacketHeader* pPacket );

	// Server&DB-House.cpp
	// ���� ��� ������ ������ �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_CHANGEHOUSECONTRACT(sPacketHeader* pPacket);
	// ���� ���� ������ ���� ���� ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYHOUSEUNIT(sPacketHeader* pPacket);
	// ���� ����� ��� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETHOUSEAPPLYERLIST(sPacketHeader* pPacket);
	// ���� ��û�� ������ �Ϳ� ���� ����.
	void DoMsg_DBMSG_RESPONSE_HOUSERENTAPPLY(sPacketHeader* pPacket);
	// ���� ��û ��� ��û�� ���� ����.
	void DoMsg_DBMSG_RESPONSE_HOUSERENTAPPLYCANCEL(sPacketHeader* pPacket);
	// �Ӵ� �㰡�� ������ �Ϳ� ���� ����.
	void DoMsg_DBMSG_RESPONSE_HOUSERENT(sPacketHeader* pPacket);
	// �������� �κ����� â��� �ű�°Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MOVEITEMINVTOSTG(sPacketHeader* pPacket);
	// �������� â���� �κ����� �ű�°Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MOVEITEMSTGTOINV(sPacketHeader* pPacket);
	// â���� Ư�� ��ġ�� �ִ� ������ ������ ��û�� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_GETHOUSESTGPOS(sPacketHeader* pPacket);
	// ���� ����ڸ� ��� �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_DELHOUSEAPPLYER(sPacketHeader* pPacket);
	// �Ӵ�Ḧ �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_PAYRENTFEE(sPacketHeader* pPacket);
	// ������ ȸ���Ѵ� 
	void DoMsg_DBMSG_RESPONSE_RECALLHOUSE(sPacketHeader* pPacket);
	// ������ ������ ����
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITSTABLECREATE(sPacketHeader* pPacket);
	// ������ ���� �ִ´�.
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEIN(sPacketHeader* pPacket);
	// �������� ���� ����.
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEOUT(sPacketHeader* pPacket);
	// ������ �� ������ ������Ʈ �Ѵ�.
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEINFOSET(sPacketHeader* pPacket);
	// ������ �ִ� ���� ���̸� �Դ´�.
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEEATFOOD(sPacketHeader* pPacket);
	// ������ ���� ����
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE(sPacketHeader* pPacket);
	// ������ ������ �̾Ƴ�
	void DoMsg_DBMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS(sPacketHeader* pPacket);
	// â�� �̸� ����
	void DoMsg_DBMSG_RESPONSE_CHANGEHOUSEUNITNAME(sPacketHeader* pPacket);

	//----------------------------------------------------------------------
	// ItemMall , Server&DB-ItemMall.cpp
	//---------------------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_ITEMMALLEXISTENCE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALLITEMLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALLGETITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWSCHATADDMISSION(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NOLIMITTICKET_WARP(sPacketHeader* pPacket);
	
	// ��ǥ ���� ���� �ٷ� �̵� �Ѵ� 
	void DoMsg_DBMSG_RESPONSE_WARP_TARGETWORLD(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_GET_SEL_PGLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GET_ITEMMALL_ITEMINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GET_MYCASH_INFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALL_BUYITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALL_GIFTITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_CHECK_ACCOUNTID(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SET_BAGITEM(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SET_CHANGEHERO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALL_BUYITEM_FORXNOTI(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ITEMMALL_GIFTITEM_FORXNOTI(sPacketHeader* pPacket);
	//void DoMsg_DBMSG_RESPONSE_GET_PRESENT_ITEMDATA(sPacketHeader* pPacket);
	//--------------------------------------------------------------------
	// ����, Server&DB-Agriculture.cpp
	//--------------------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_AGRICULTUREGETPRODUCTS(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_AGRICULTUREPAYMONEYFORRENTLAND(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETAGRICULTURELEASEINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_EXPIREDAGRICULTERLEASE(sPacketHeader* pPacket);

	//--------------------------------------------------------------------
	// ����, Server&DB-Fishing.cpp
	//--------------------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_FISHINGGETMARINEPRODUCTS(sPacketHeader* pPacket);




	// Server&DB-NPC.cpp
	// NPC���� �Ǹ��� ���� ��û�ϴ� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_SELLNPC(sPacketHeader* pPacket);
	// NPC���Լ� ������ ���� ��û�ϴ� �Ϳ� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_BUYNPC(sPacketHeader* pPacket);

	// Server&DB-Village.cpp
	// ���� �ǹ� ���� ��û. 
	void DoMsg_DBMSG_RESPONSE_GETSTRUCTUREINFO(sPacketHeader* pPacket);


	//-----------------------------------------------------------
	// ���� ����  ( �������� ����, 
	//-----------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_GETVILLAGEINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DECLAREWAR( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_CANCELDECLAREWAR( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_SETPARENTVILLAGE( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_SETSYMBOLSTATUS( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETCASTLESTATUS( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_SETVILLAGEWARLOSS( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_SETVILLAGELEVEL( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_VILLAGERESIDENTSVISITORSINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ADD_VILLAGE_SCORE(sPacketHeader* pPacket);
	
	
	void DoMsg_DBMSG_RESPONSE_SETVILLAGEWAR_RESULT(sPacketHeader* pPacket);

	//-----------------------------------------------------------
	// ������ȸ
	//-----------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_INFO( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_SUGGEST_CHIEF( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_VOTE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_ACCEPTCANDIDATE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_CLOSE_CHIEF( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_SETVOTERSTATE( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF( sPacketHeader* pPacket );		//[�߰� : Ȳ���� 2008. 2. 21 => ������ȸ �ߵ� ���� ���� ���� ó���Լ� DB->S ]
	void DoMsg_DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF_LIST( sPacketHeader* pPacket );	//[�߰� : Ȳ���� 2008. 4. 11 => ������ȸ �ߵ� ���� ����Ʈ ��� DB->S ]
	//-----------------------------------------------------------
	// �ֽ� ����
	//-----------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_GETSTOCKOFFERINGINFO( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETSTOCKOFFERING( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_ENDSTOCKOFFERING( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_STOCKOFFERINGORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GETSTOCKOFFERINGORDERLIST( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_EXECUTESTOCKOFFERINGORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_RESETSTOCKOFFERINGORDERLIST( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_EXCHANGESTOCK( sPacketHeader* pPacket );
	
	void DoMsg_DBMSG_RESPONSE_GIVESTOCK( sPacketHeader* pPacket );

	//#if defined(_CITYHALL_BANKRUPTCY)
	//-----------------------------------------------------------
	// ��� �Ļ� ����
	//-----------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_CITYHALL_STATE_CHANGED( sPacketHeader* pPacket );

	////������ �Ļ��Ͽ� �ʱ�ȭ �Ѵ�.
	//// �Ļ� �� ���� ���� ���� �ʱ�ȭ�� ���� ���˽� ���۾����� �Ѵ�.
	//void DoMsg_DBMSG_RESPONSE_VILLAGE_INITIALIZATION( sPacketHeader* pPacket );
	//#endif

	// Server&DB-RealEstate.cpp
	// �ε��� ����� �����Ѵ�. 
	void DoMsg_DBMSG_RESPONSE_EXTENDCONTRACT(sPacketHeader* pPacket);

	//---------------------------------------------
	// Server&DB-System.cpp
	//---------------------------------------------
	// ���ӽ��ۿ� ���� ������ ���´�.
	void DoMsg_DBMSG_RESPONSE_STARTGAME(sPacketHeader* pPacket);
	// �ð��� ������� ��û�� ���� ����
	void DoMsg_DBMSG_RESPONSE_GETTIME(sPacketHeader* pPacket);
	// �ð��� �����϶��  ��û�� ���� ����
	void DoMsg_DBMSG_RESPONSE_SETTIME(sPacketHeader* pPacket);

	// Ư�� ���� ���� ����ڿ��� �������� ��ǰ ������
	void DoMsg_DBMSG_RESPONSE_MASTERGIVEITEM(sPacketHeader *pPacket);

	void DoMsg_DBMSG_RESPONSE_GIVEITEM(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_DBSYSTEMINFO(sPacketHeader *pPacket);

	void DoMsg_DBMSG_RESPONSE_DBSTARTINFO(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_DBINITCOMPLETE(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SETFOURLEAF(sPacketHeader *pPacket);
	

	void DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_SAVEINVENTORY(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_MOVEITEMSTGTOINV(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_INVENTORYLIST(sPacketHeader *pPacket);

	// ���� 
	void DoMsg_DBMSG_RESPONSE_GETBYUNGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETGONGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETHYUNGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETHOZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETIZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETYEZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETGOONZUINFO(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_SETBYUNGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETBYUNGZOINFO_VILLAGEWARTIME(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETGONGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETHYUNGZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETHOZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETIZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETYEZOINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETGOONZUINFO(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_SETGOONZUFINANCES(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_GETANGELAPPLYERLIST(sPacketHeader* pPacket); // ��ȣõ�� ��û�� ���
	void DoMsg_DBMSG_RESPONSE_GETANGELLIST(sPacketHeader* pPacket); // ��ȣõ�� ���
	void DoMsg_DBMSG_RESPONSE_SETANGELAPPLYER(sPacketHeader* pPacket); // ��ȣõ�� ��û
	void DoMsg_DBMSG_RESPONSE_SETANGEL(sPacketHeader* pPacket); // ��ȣõ�� �Ӹ�

	void DoMsg_DBMSG_RESPONSE_GETPOLICELIST(sPacketHeader* pPacket);	// ���� ���
	void DoMsg_DBMSG_RESPONSE_SETPOLICE(sPacketHeader* pPacket);		// ���� �Ӹ�

	void DoMsg_DBMSG_RESPONSE_GETCRIMINALLIST(sPacketHeader* pPacket);	// ����� ���
	void DoMsg_DBMSG_RESPONSE_SETCRIMINAL(sPacketHeader* pPacket);		// ����� ���

	void DoMsg_DBMSG_RESPONSE_GETCHANGEDNAME(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_GETDAILYNEWCHAR(sPacketHeader* pPacket);


	void DoMsg_DBMSG_RESPONSE_GETWARRANKINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETWARRANKINFO(sPacketHeader* pPacket);

	// ����� �α��� ���/���� ����. 
	void DoMsg_DBMSG_RESPONSE_BLOCK(sPacketHeader* pPacket);
	// Ư�� ����� �α��� ���/���� ����. 
	void DoMsg_DBMSG_RESPONSE_BLOCKUSER(sPacketHeader* pPacket);
	// ����� ���� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_USERCHARINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_USERCHARITEMINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_USERCHARITEMINFO2(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_ACCOUNTINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ACCOUNTINFOFORHANXNOTI(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_CHARINFOFORHANXNOTI(sPacketHeader* pPacket);
	
	// ��Ÿ�� �뺸. 
	void DoMsg_DBMSG_RESPONSE_MAPTYPEINFO(sPacketHeader* pPacket);
	// ���� �̵� �㰡 �뺸 
	void DoMsg_DBMSG_RESPONSE_WARPVILLAGE(sPacketHeader* pPacket);
	// Ư�� ����ڸ� �������� ������
	void DoMsg_DBMSG_RESPONSE_PRISONUSER(sPacketHeader* pPacket);

	// ���� �ŷ� ��û�� ���� ����.
	void DoMsg_DBMSG_RESPONSE_PRIVATETRADE(sPacketHeader* pPacket);

	// ��ڰ� ������� �α׸� ��û�Ѵ�.
	void DoMsg_DBLOGMSG_RESPONSE_PERSONAL_LOG(sPacketHeader* pPacket);

	// ��ڰ� 6�� �� ���ָ� �Ӹ��ߴ�.
	void DoMsg_DBMSG_RESPONSE_SETMINISTER(sPacketHeader* pPacket);

	// ���ְ� ���� ������ �����ߴ�.
	void DoMsg_DBMSG_RESPONSE_SETLIQUIDATION(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_SETBONUSTIME(sPacketHeader* pPacket);

	// ���� ��ǰ ����

	void DoMsg_DBMSG_RESPONSE_GACHABUY(sPacketHeader* pPacket);


	// Server&DB-NPC.cpp
	// ���� ���� NPC �� ������ DB�� �����Ѵ�.
	void DoMsg_DBMSG_RESPONSE_SETFOREIGNMERCHANTNPCINFO( sPacketHeader* pPacket );
	// ���� ���� NPC �� ������ DB�� ���� �޾ƿ´�.
	void DoMsg_DBMSG_RESPONSE_GETFOREIGNMERCHANTNPCINFO( sPacketHeader* pPacket );
	// ���� ���� NPC �� ĳ�� ������ ����
	void DoMsg_DBMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM( sPacketHeader* pPacket );
	// ��õ ����Ʈ�� ������ ����
	void DoMsg_DBMSG_RESPONSE_BUYRECOMMANDPRODUCT(sPacketHeader* pPacket );
	// �ڽ��� ��õ������ ����� ������� ����� ������
	void DoMsg_DBMSG_RESPONSE_RECOMMANDPOINTLIST(sPacketHeader* pPacket );
	// ���� �Ļ��� �����Ѵ�.
	void DoMsg_DBMSG_RESPONSE_VILLAGEBANKRUPTCY(sPacketHeader* pPacket );


	// Server&DB-TradeMerchant.cpp
	// ���� ���� NCP �� �⺻ ������ DB�� �����Ѵ�.
	void DoMsg_DBMSG_RESPONSE_TRADEMERCHANTSET( sPacketHeader* pPacket );
	// ���� ���ο��� �������� �Ǹ��Ѵ�. ( ���� ���� ���忡���� ���� )
	void DoMsg_DBMSG_RESPONSE_TRADEMERCHANTBUYITEMFROMPERSON( sPacketHeader* pPacket );
	// ���� ������ ���� �����Ѵ�.
	void DoMsg_DBMSG_RESPONSE_TRADEMERCHANTBUYHORSEFROMPERSON( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TRADEMERCHANTBUYITEM( sPacketHeader* pPacket );

	// Server-Web.cpp
	void DoMsg_DBMSG_RESPONSE_NEWS( sPacketHeader* pPacket );

	// ServerDB-WorldMoney
	void DoMsg_DBMSG_RESPONSE_DISTRIBUTION_WORLDMONEY( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_TRADELIST( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_SELLORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_BUYORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_CANCELORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_SETAVERAGEPRICE(sPacketHeader*pPacket);
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_REDUCEPRICE(sPacketHeader*pPacket);
	void DoMsg_DBMSG_RESPONSE_WORLDMONEY_SET_CHAR(sPacketHeader*pPacket);

	void DoMsg_DBMSG_RESPONSE_TRADESERVER_SETORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TRADESERVER_CANCELORDER( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TRADESERVER_BUYITEM( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TRADESERVER_SET_SELLINFO( sPacketHeader* pPacket );

	void DoMsg_DBMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU( sPacketHeader* pPacket );
	
	// WorldPassport
	void DoMsg_DBMSG_RESPONSE_WORLDPASSPORT_SET(sPacketHeader*pPacket);
	void DoMsg_DBMSG_RESPONSE_WORLDPASSPORT_EXTEND(sPacketHeader*pPacket);

	// ���� ���� �Է�
	void DoMsg_DBMSG_RESPONSE_SETCOUNTRY( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETSHOWCOUNTRY( sPacketHeader* pPacket );
	
	// Ǫġ�ڹ� �����ֱ� �Ⱥ����ֱ�
	void DoMsg_DBMSG_RESPONSE_SETSHOWPUCHIKOMI( sPacketHeader* pPacket );

	//fp ���� ��� ��ɾ�
	void DoMsg_DBMSG_RESPONSE_GIVEFP( sPacketHeader* pPacket);

	// ���� �߰�/����
	void DoMsg_DBMSG_RESPONSE_ADDBUF( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DELETEBUF( sPacketHeader* pPacket);

	// ���� ���� ������Ʈ
	void DoMsg_DBMSG_RESPONSE_SETTEACHERPOINT( sPacketHeader* pPacket);
	// ���� ������ ������ ���
	void DoMsg_DBMSG_RESPONSE_GETITEM_FROM_TEACHERPOINT( sPacketHeader* pPacket);
	// ������ ���ڿ��� ���踦 ���´�
	void DoMsg_DBMSG_RESPONSE_RENOUNCEPUPIL( sPacketHeader* pPacket);
	// ���ڰ� ���·����� �߿��ߴ°�?
	void DoMsg_DBMSG_RESPONSE_OVERTAKETEACHERLEVEL( sPacketHeader* pPacket);

	// PVP���
	void DoMsg_DBMSG_RESPONSE_PVPRESULT( sPacketHeader* pPacket);
	
	// ��� �ʱ�ȭ
	void DoMsg_DBMSG_RESPONSE_INITSTATISTICS( sPacketHeader* pPacket );

	// ���ĸ��� �̺�Ʈ
	void DoMsg_DBMSG_RESPONSE_MOFUMOFUEVENT_RESERVE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_MOFUMOFUEVENT_RESERVELIST( sPacketHeader* pPacket );

	// ����NPC
	void DoMsg_DBMSG_RESPONSE_SYSTEMREWARDLIST( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_RECIEVESYSTEMREWARD( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GIVESYSTEMREWARD( sPacketHeader* pPacket );

	// �⼮üũ
	void DoMsg_DBMSG_RESPONSE_ATTEND( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETATTEND( sPacketHeader* pPacket );

	//KHY - 1220 - �ð�������
	//KHY - 1220 - ���Žý���.
	void DoMsg_DBMSG_RESPONSE_TRANSFORM_ADDCHAR( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TIMEMETERRATE_ADDTIME( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_TIMEMETERRATE_USETIME( sPacketHeader* pPacket );	

	void DoMsg_DBMSG_RESPONSE_SET_HOMEPAGE_URL( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_GET_HOMEPAGE_URL( sPacketHeader* pPacket );	

	// ����
	void DoMsg_DBMSG_RESPONSE_CREATEEMPIRE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_DESTROYEMPIRE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_JOINEEMPIRE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SECEDEEMPIRE( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_ALLEMPIREINFO( sPacketHeader* pPacket );
	void DoMsg_DBMSG_RESPONSE_SETEMPIREMONEY( sPacketHeader* pPacket );

	////GMTOOL[�ռ���]
	void DoMsg_DBMSG_RESPONSE_GMTOOL_CHARBASICINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GMTOOL_ANIMALINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GMTOOL_INVENTORYINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GMTOOL_SUMMONINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GMTOOL_SKILLINFO(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GMTOOL_REALESTATEINFO(sPacketHeader* pPacket);

	// [�߰� : Ȳ���� 2007. 12. 7 �������α׷� �޽��� ó�� DB -> S]
	void DoMsg_DBMSG_RESPONSE_AUTOMACRO(sPacketHeader* pPacket);
	
	//���� ���� ����Ʈ
	void DoMsg_DBMSG_RESPONSE_HOFLIST(sPacketHeader* pPacket);
	//��ŷ ����Ʈ 
	void DoMsg_DBMSG_RESPONSE_RANKINGLIST(sPacketHeader* pPacket);

	//******************************************************************************************
	
	//[�߰� : Ȳ���� 2008. 1. 30 => ���� ����(����)�� ����. DB->S]
	void DoMsg_DBMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM(sPacketHeader* pPacket);
	
	//[�߰� : Ȳ���� 2008. 1. 30 => ���� ����(����)�� ȸ��.DB->S]
	void DoMsg_DBMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM(sPacketHeader* pPacket);

	//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ������ ����Ʈ. DB->S]
	void DoMsg_DBMSG_RESPONSE_SPACE_BOX_ITEM_LIST(sPacketHeader* pPacket);
	
	//******************************************************************************************

	//------------------------------------------------------------------------
	//	[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ DB �޽��� ó�� �Լ�.]
	//------------------------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_INVENTORYLIST(sPacketHeader* pPacket); 
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_SAVEINVENTORY(sPacketHeader* pPacket); 
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_MOVEITEMSTGTOINV(sPacketHeader* pPacket); 
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_MIXTURE(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_REMOVE(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_ARTIFACT_SLOT_CREATE(sPacketHeader *pPacket);

	//******************************************************************************************

	// Daily Quest2( Server&DB-DailyQuest2.cpp )	
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST2ADD( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST2DEL( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST2CHANGE( sPacketHeader* pPacket);

	// Daily Quest3( Server&DB-DailyQuest3.cpp )	
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST3ADD( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST3DEL( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_DAILYQUEST3CHANGE( sPacketHeader* pPacket);

	//KHY - 0530 ���� ���� ��������.
	void DoMsg_DBMSG_RESPONSE_GET_FOREIGNMERCHANTBUYLIMIT( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GET_FOREIGNMERCHANTNOWMONEY( sPacketHeader* pPacket);
	
	//[����] ���� �̺�Ʈ �޽��� ó�� (DB->S) => 2008-6-20
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_RANK_INFO(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_SERVER_INFO(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_DAILY_SERVER_INFO(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_SERVER_BUF_KIND(sPacketHeader *pPacket);

	// [����] �����̺�Ʈ ����
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_SET(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_GET(sPacketHeader *pPacket);
	void DoMsg_DBMSG_RESPONSE_SERVER_EVENT_PERSON_SCORE_GET(sPacketHeader *pPacket);

	void DoMsg_DBMSG_RESPONSE_SUMMONUSESTON(sPacketHeader *pPacket);
	
	// PCK : ����� ����Ʈ �Ϸ� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_SETSPECIALQUESTCHANGE(sPacketHeader* pPacket);
	
	// PCK : ���̹� ����Ʈ �Ϸ� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_SETNAMINGQUESTINFO(sPacketHeader* pPacket);

	// PCK : ��� ����� ���� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_CITYHALL_SETINOUTMONEY(sPacketHeader* pPacket);

	// PCK : �����ֹο��� ������ ���� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_GIVEVILLAGEITEM(sPacketHeader* pPacket);

	// PCK : ĳ���� ���ʽ� ��ġ ���º��� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_SETBONUSINFO(sPacketHeader* pPacket);

	//[����] ȣ�ڻ��� => 2008-9-16
	void DoMsg_DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET(sPacketHeader* pPacket);

	// PCK : ���� ������ �÷��̽ð� ���� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_VILLAGEJOINPLAYTIME(sPacketHeader* pPacket);

	// PCK : ���� ������ ������ Ƚ�� (�α׿�)
	void DoMsg_DBMSG_RESPONSE_VILLAGEJOINLEVELUP(sPacketHeader* pPacket);

	// PCK : ���� ������ ������ ���� ����ġ (�α׿�)
	void DoMsg_DBMSG_RESPONSE_VILLAGEJOINMAKEITEM(sPacketHeader* pPacket);

	// [����] PVP ���Ѵ��� ���� ��û ����
	void DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_INFOGET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET(sPacketHeader* pPacket);

	// [����] PVP ���Ѵ��� END ��� ����
	void DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_END( sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE( sPacketHeader* pPacket);
	

	//[����] �����
	void DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_DEL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_SET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_GET(sPacketHeader* pPacket);

	//[����] ä�ú��
	void DoMsg_DBMSG_RESPONSE_SETMUTETIME(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETMUTETIME(sPacketHeader* pPacket);

	// [����] �߷�Ÿ�� ����
	void DoMsg_DBMSG_RESPONSE_VALENTINEWAR_INFO_GET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_VALENTINEWAR_REQUEST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_VALENTINEWAR_GET_PRIZE(sPacketHeader* pPacket);
	
	//[����] ������. 
	void DoMsg_DBMSG_RESPONSE_ELIXIR_SET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_ELIXIR_GET(sPacketHeader* pPacket);

	//[����] ���θ���.
	void DoMsg_DBMSG_RESPONSE_PROMOTER_INFO_GET(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_SETBALANCECANUSECURRENCY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETBALANCECANUSECURRENCY(sPacketHeader* pPacket);
	

	// [����] ���ο� ���û��� ������ �ޱ�
	void DoMsg_DBMSG_RESPONSE_NEWSELECTBOX_ITEM_GET(sPacketHeader* pPacket);

	//=============================================================================================
	// [����] ���ո���.
	//---------------------------------------------------------------------------------------------
	void DoMsg_DBMSG_RESPONSE_NEWORDERMARKET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWTRADEMARKET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWMARKETACCOUNT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWMARKETITEMLIST(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_GETFROMNEWMARKET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SETNEWMARKETFEE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWMARKETRESULT(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWMARKET_SETITEMPRICE(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_NEWMARKET_INCREASEBANKMONEY(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_MANYITEMNEWPRICE(sPacketHeader* pPacket);					// ������ ���� ��û�� ���� ����. 
	void DoMsg_DBMSG_RESPONSE_MANYITEMNEWPRICE_COMPLETED(sPacketHeader* pPacket);		// ������ ���� ��û�� ���� ���� �Ϸ� 
	void DoMsg_DBMSG_RESPONSE_SETITEMNEWPRICE(sPacketHeader* pPacket);					// ������ ���� ����. 
	void DoMsg_DBMSG_RESPONSE_NEWMARKETREDUCEPRICENOTICE(sPacketHeader* pPacket);		// ������ ���� �϶����� ��û 
	
	void DoMsg_DBMSG_RESPONSE_ITEMMAKERNAMENEW(sPacketHeader* pPacket);					// ������ �ø��� ��ȣ�� ������ ���. 

	void DoMsg_DBMSG_RESPONSE_CELLULAR_PHONE_AUTH(sPacketHeader* pPacket);				// [����] �ڵ��� ���� ����.
	
	// [����] ��ȥ �ý���
	void DoMsg_DBMSG_DBMSG_RESPONSE_SET_MARRY(sPacketHeader* pPacket);					//[����] ��ȥ�� �ߴ�
	void DoMsg_DBMSG_RESPONSE_GET_MARRY_INFO(sPacketHeader* pPacket);					//[����] ��ȥ������ ��´�
	void DoMsg_DBMSG_RESPONSE_MARRY_ITEMGET_SET(sPacketHeader* pPacket);				//[����] ��ȥ ����� �����۹ޱ� ������ ����
	void DoMsg_DBMSG_RESPONSE_MARRY_LOVE_SET(sPacketHeader* pPacket);					//[����] ��ȥ ������ ���� ����
	
	void DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE_LIST_GET(sPacketHeader* pPacket);			//[����] ��ȥ�� ��� �ޱ�
	void DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE(sPacketHeader* pPacket);					//[����] ��ȥ�� ���� �ϱ�
	void DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE_CANCEL(sPacketHeader* pPacket);			//[����] ��ȥ�� ���� ���

	// [����]���� �ý���
	void DoMsg_DBMSG_RESPONSE_GET_FAMILYINFO(sPacketHeader* pPacket);					// [����] ���� �ý��� - ���� ������ ��´�
	void DoMsg_DBMSG_RESPONSE_FAMILY_ADD_CHILDREN(sPacketHeader* pPacket);				// [����] ���� �ý��� - �ڽ� �߰�
	void DoMsg_DBMSG_RESPONSE_FAMILY_DEL_CHILDREN(sPacketHeader* pPacket);				// [����] ���� �ý��� - �ڽ� ����
	void DoMsg_DBMSG_RESPONSE_FAMILY_PLUS_ADD_DATE(sPacketHeader* pPacket);				// [����] ���� �ý��� - ����ȿ������
	void DoMsg_DBMSG_RESPONSE_FAMILY__SET_COOKIE_EFFECT(sPacketHeader* pPacket);		// [����] ���� �ý��� - ��Ű ���

	// [����] ��ȣ����
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_CREATE(sPacketHeader* pPacket);					// [����] ��ȣ���� ����
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_GET(sPacketHeader* pPacket);					// [����] ĳ���Ͱ� �����ִ� ��ȣ���� ��������
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_FELLOWSHIP_SET(sPacketHeader* pPacket);			// [����] ĳ���Ͱ� �����ִ� ��ȣ���� ģȭ�� ����
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_CHANGE_NAME(sPacketHeader* pPacket);			// [����] ĳ���Ͱ� �����ִ� ��ȣ���� �̸� ����
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_DEAD(sPacketHeader* pPacket);					// [����] ĳ���Ͱ� �����ִ� ��ȣ���� ����

	void DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_GET(sPacketHeader* pPacket);				// [����] ��ȣ���� ������ ���� ������
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_CHANGE(sPacketHeader* pPacket);			// [����] �����ҿ� �ִ� ��ȣ���ɰ� ĳ���Ϳ� �ִ� ��ȣ������ �±�ȯ��
	void DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_CREATE(sPacketHeader* pPacket);			// [����] ��ȣ���� �����ҿ� ���� ������ �ø�
			
	// [����] �޸� ���� �ý��� 
	void DoMsg_DBMSG_RESPONSE_DORMANCY_POINTITEM_BUY(sPacketHeader* pPacket);			// [����] ����Ʈ�� ������ ����
	void DoMsg_DBMSG_RESPONSE_DORMANCY_POINTINFO_SET(sPacketHeader* pPacket);			// [����] ����Ʈ ���� ���� ����
	void DoMsg_DBMSG_RESPONSE_DORMANCY_STATE_CHANGE(sPacketHeader* pPacket);			// [����] �޸� ���� ���� ����

	// [����] ĳ���� ������
	void DoMsg_DBMSG_RESPONSE_PERSONSLOTNUMCHANGE(sPacketHeader* pPacket);				// [����] ĳ���� �����ҿ��� ĳ���� �������� ���

	// [����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	void DoMsg_DBMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO(sPacketHeader* pPacket);				// [����] �����̺�Ʈ ���� 
	void DoMsg_DBMSG_RESPONSE_GOONZURACCOONEVENT_GETINFO(sPacketHeader* pPacket);				// [����] �����̺�Ʈ ������ �޾� �´� 
	
	// [����] ��ų��.
	void DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGIC_ADD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGIC_DEL(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD(sPacketHeader* pPacket);
	void DoMsg_DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL(sPacketHeader* pPacket);

	// [����] ���Һ�
	void DoMsg_DBMSG_RESPONSE_BBB_SET_REWARDMONEY(sPacketHeader* pPacket);				// [����] ���Һ� - ���� ���� �ݾ� ��û�� ���� ����.
	void DoMsg_DBMSG_RESPONSE_BBB_GET_REWARD_MONEY(sPacketHeader* pPacket);				// 

	// [����] ���ֵ��̹̼� : �̼� �ο� ���ο� ���� ����� ����
	void DoMsg_DBMSG_RESPONSE_GOONZUDAYMISSIONINFO_GET(sPacketHeader* pPacket);

	void DoMsg_DBMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_INPUT(sPacketHeader* pPacket);		// 
	void DoMsg_DBMSG_RESPONSE_CONTRIBUTION_MAKE_NPC(sPacketHeader* pPacket);		// 
	

	
	

	//=============================================================================================
	//#############################################################################################
	// ��� ��Ŷ ó���Լ� �������
	//#############################################################################################
	//=============================================================================================

	
	
	// ���ۿ� �ִ� ���� ������ ������.
	bool PopSpecialNews();

	BOOL InBufferMessageOperation(cltMsg* pclMsg, SI32 id);

	SHORT GameAction();
	// ������ �׼�. 
	BOOL ServerAction();

	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	void SendServerResponseMsg(SI16 receiver, UI16 returnval, SI16 para1, SI16 para2, SI16 charunique);
	//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
	void SendServerResponseCharMsg(SI16 receiver, UI16 returnval, TCHAR* para1, TCHAR* para2, SI16 charunique);
	//���� Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.2->3��
	void SendServerResponseCharMsg2(SI16 receiver, UI16 returnval, TCHAR* para1, TCHAR* para2, TCHAR* para3, SI16 charunique);

	//-------------------------------------------
	// NPC
	//---------------------------------------------

	// NPC�� ����� �����۵� �ش�. 
	SI32 SetNPCChar(SI32 kind, SI16 villageunique, cltIdentity* pclidentity, SI32 level, SI32 life, SI32 x, SI32 y, SI32 mapindex, SI32 itemmode, cltInnerStatusInfo *pInnerStatusInfo, cltOrderDataInfo*pOrder= NULL, cltGMCommandKindInfo* pGMCommandKindinfo = NULL);

	// // ������ ��� NPC�� ��ġ�Ѵ�. 
	BOOL PutNPC();

	// NPCGroup���� �ȿ� �ִ°� ?
	bool IsInNPCGroup(SI32 npcgroup, SI32 mapindex, SI32 x, SI32 y);

	// NPCGroup �� �����͸� ���´�. 
	cltNPCGroup* GetNPCGroupPointer(SI32 npcgroup);



	//----------------------------------------------
	// MyDPID
	//----------------------------------------------
	BOOL IsUser(DPNID dpid){return FALSE;}

	//----------------------------------------
	// Char Information Update
	//----------------------------------------
	BOOL SendCharUpdate(SI32 charunique, bool burgentmode);


	//-----------------------------------------------
	// ��� ��� ���� 
	//-----------------------------------------------
	// ��� ����� ó���Ѵ�. 
	BOOL OperateGameMasterOrder(TCHAR* pstring, SI32 id);


	//-----------------------------------------------
	// ������ �Ⱓ ����
	//-----------------------------------------------
	// ������ �Ⱓ ���� ó��
	BOOL GetItemUseAbleDay(cltItem* clItem, SI32 * outUseAbleDay); // ���Ⱓ�� ���� �������̸� ���� ��ȯ

	//-----------------------------------------------
	// ������ �̵� ����
	//-----------------------------------------------
	// ��ø������ ������ �̵��� ���� ���
	BOOL DistributePileMoveItem(SI32 charid, cltItem clFrom, UI16 uiFrom, cltItem clTo, UI16 uiTo);

	//-----------------------------------------------
	// ���ݰ��� 
	//-----------------------------------------------
	// ������ ���� �Ӽ��� ����Ͽ� ���� ü���� ���Ͻ�Ų��. 
	// �Ķ��Ÿ ����:
	// myid      : ������ �õ��ϴ� ĳ������ ���̵� 
	// attackatb : ���ݼӼ�(main.h�� ���� )
	// range     : ���� ����, �Ϲ������� 1( 1�̸� -1 ~ +1)
	// power     : ���ݷ� 
	// attackid  : Ư���� ���߰� ���� ĳ������ ���̵� 
	// dx, dy    : Ÿ���� �� �������� ��ǥ 

	// ���ϰ�   
	//  0 -> �׻� 0�� ���� 
	BOOL HitOperation(SI32 myid, cltAttackDamageInfo* pcldamageinfo, SHORT range, const cltAttackTarget* pcltarget, cltMapCommon* pclMap);

	// ���ݼӼ�, ���ݷ�, ���ݴ���� ����Ͽ� ���� ���ظ� ����Ѵ�. 
	// PCK : specialattackswitch��  bool���� type���� �����Ѵ�. (0 : �Ϲݰ���, 1 : ġ��Ÿ, 2 : �߰�Ÿ(���ڹ���) 
	bool GetDamage(cltAttackDamageInfo* pcldamageinfo, SI32 myid, SI32 attackid, UI08 specialattackswitch, cltAttackDamageInfo* pclreturndamageinfo);

	//��æƮ by tae-yang
	SI32 GetEnchantDefen(SI32 AttackType, SI32 defenid);

	//===============================================================================
	// ������ ������ �������� ������.
	// specialattackswitch : �ʻ��� �۵� ����.
	// PCK : specialattackswitch��  bool���� type���� �����Ѵ�. (0 : �Ϲݰ���, 1 : ġ��Ÿ, 2 : �߰�Ÿ(���ڹ���)
	BOOL Hit(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo, UI08 specialattackswitch);
	//===============================================================================
	// �������� Ÿ�ݽ� �ΰ� �ɷ��� �����Ų��.
	BOOL AddScrollMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo);
	// ĳ������ STATUS�� �����ϴ� MAGIC OPERATE 
	BOOL ChangeStatusMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo);
	// PASSIVE MAGIC�� �����Ų��. 
	BOOL PassiveMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo);
	//===============================================================================
	// myid�� enemyid�� �������� ���� ����ġ�� ���´�. 	
	SI32 GetExp(SI16 myid, SI16 enemyid, SI16 damage);

	//===============================================================================
	// HIT �Լ��� ����� ó�� �Լ���
	void SpecialDamage( SI32 myid, SI32 enemyid, SI32* psiRealDamage, SI32* psiDisplayDamage );
	void DeadChar_PC( SI32 myid, SI32 enemyid );
	void DeadChar_NPC( SI32 myid, SI32 enemyid );
	bool GiveBigItem( SI32 myid, SI32 enemyid );
	bool GiveSpecialItem( SI32 myid, SI32 enemyid );

	bool GiveBigItem_Event( SI32 myid, SI32 enemyid );

	bool GiveBigItem_New( SI32 myid, SI32 enemyid );
	//===============================================================================

	// ������ ���� ĳ������ ��ġ ���. 
	void MagicPopAction();

	//---------------------------------------------
	// DB
	// DB�� ���õ� �Լ��� ����. 
	//---------------------------------------------

	//---------------------------------------------------------------------
	// cltRank������ DB�� �����Ѵ�. 
	//---------------------------------------------------------------------
	SI32 LoadDB_cltRank(SI32 sipersonid, cltSimpleRank* pclrank);
	SI32 DelDB_cltRank(SI32 sipersonid);

	//-----------------------------
	// ��Ʈ��ũ ����.  
	//----------------------------
	void InitNetwork();
	// Agent���� ���� ������ ���� ��������� ������ �����Ѵ�.
	void SetOtherServer(TCHAR* frontip, SI32 frontport, TCHAR* authip, SI32 authport, TCHAR* dbip, SI32 dbport, SI32 clientlistenport);

	// ����ĳ���͸� pclCM�� �����Ѵ�. 
	void  SetSessionChar();
	bool StartNetwork();

	void NetworkOperation();
	void GameDBAction();

	bool SendDBMsg(SI32 siselect, sPacketHeader *pPacket);

	// Ŭ���̾�Ʈ���� ������ �����ش�. 
	SI32 SendLetterMsg(SI32 personid, cltLetterHeader* pclheader);

	// Ư�� ������ �������� ������ �����ش�.
	SI32 SendAccountLetterMsg(TCHAR* AccountID, cltLetterHeader* pclheader);

	// ��ü �������� �˸� �޽����� ������. 
	bool SendNoticeMsg(SI16 villageunique, SI16 villagerunique, SI16 charunique, TCHAR* msg);

	// Ư�� ����ڿ��� �˸� �޽����� ������. 
	bool SendNoticePersonMsg(SI16 charunique, TCHAR* msg, TCHAR* header= NULL);

	//
	void SetWarResult( SI32 winVillage, SI32 loseVillage );
	void SetVillageWarLoss( SI32 winVillage, SI32 loseVillage );

	void SetVillageLevel();
	void GetSlaveVillageNum();

	// MD5�� ��ȯ�Ҽ� �ִ� ������ ��ȯ�Ѵ�

	//------------------------------------
	// �ð� 
	//------------------------------------
	// DB�� �ð��� �����Ѵ�. 
	void UpdateDBTime(cltDate* pcldate);

	//----------------------------
	// NPC����ϱ�. 
	//----------------------------
	bool Hire(SI32 kind, SI32 slot, SI32 villageunique, bool mode);

	void GetTopLevelVillage( SI32 *villageunique, SI32 *villagelevel );


	void SendPostOfficeItemToPerson( TCHAR *szPersonName, cltItem *pclItem, TCHAR *szMsg, GMONEY money = 0 );
	void SendPostOfficeItemToPerson( SI32 personid, cltItem *pclItem, TCHAR *szMsg, GMONEY money = 0 );

	//--------------------------------------------
	// ���� �Լ�. 
	//--------------------------------------------
	bool Repair(SI32 mastercharunique, SI32 clientcharunique, SI32 clientitempos, cltItem* pclitem, GMONEY repairmoney, SI32* preturnval);

	cltStrInfo* GetStrInfo( SI32 villageUnique, SI32 strType );

	// ȣ������ �����. 
	SI32 MakeGuardChar(SI32 kind, SI16 homevillage, SI32 mapindex, SI32 x, SI32 y, cltOrderDataInfo* pclorder, cltEnemyTypeInfo* pclenemytype);

	// myid��  enemyid�� ������������ ����ġ ��ġ. 
	SI32 ExpOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo);
	
	// ExpOperate�Լ����� ĳ���� ����ġ�� �����ϰ� ��ų����ġ �κи� �ټ� �ֵ��� ���� ����
	SI32 ExpSkillOperate( SI32 siMyID, SI32 siEnemyID, cltAttackDamageInfo* pclDamageInfo );
	// ����ġ ��ġ�� ��ȯ���� ���� ������ ������ �Ѵ�.
	void IncreaseBothExp(SI32 siID, SI32 siExp);

	//myid�� enemyid�� �׿��� ��� �Ǵ� ����ǰ ó��. 
	void PartyWarItemOperate(SI32 myid, SI32 enemyid,CPartyObj* pPartyObj );
	void WarItemOperate(SI32 myid, SI32 enemyid);

	// DB���� �ʱ�ȭ �Ϸ� ����
	BOOL bCompleteDBInitAll;
	//BOOL bCompleteDBInit[ DBCONNECTION_NUMBER ];

	// �̺�Ʈ ����/���� 
	void SetEvent(SI32 index, bool bmode);

	// pc�� �̺�Ʈ
	void PCRoomEventAction();

	// ��ǰ�� ���۵Ǿ����� ��ü ����ڿ��� �˸���. 
	// bselfswitch : ����ڰ� ���� ���� Ȥ�� Ȥ�θ� ������ ����. 
	void SendRareItemMade(SI32 id, cltItem* pclitem, SI32 bselfswitch);

	// ������ ���� ������ Ŭ���̾�Ʈ���� ������. 
	void SendServerInfo(SI32 id);

	// ���� ������ ������ ȹ���Ѵ�. 
	void GetServerInfo();	

	// KHY - 0901 -  ���� ������ �ڵ����� ����.
	void GetServerSystemBuy();	

	// �Ѱ��� ���񽺿� ������ ȹ���Ѵ�.
	void GetHanGameInfo();	

	// �κ����� ��ǰ�� ���鵵�� �ϴ� �Լ�. 
	void MakeItemProcess(SI32 id, cltGameMsgRequest_MakeItemInv* pclinfo);

	SI32 CalcExp_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice );
	SI32 CalcSkillExp_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice );

	SI32 CalcExp_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum );
	SI32 CalcSkillExp_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum );
	
	SI32 CalcExp_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum );
	SI32 CalcSkillExp_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum );

	SI32 CalcTime_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice );
	SI32 CalcTime_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum );
	SI32 CalcTime_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum );

	void EnchantItemProcess(SI32 id, cltGameMsgRequest_MakeItemInv* pclinfo);

	BOOL m_bToSendServerInfoToFront;
	void SendServerInfoToFront();

	// ���ֿ��� ��ǰ ���Կ� ���� ó���� �Ѵ�. 
	void MarketBuyAction(SI16 id, SI16 villageunique, cltTradeOrder* pclOrder, SI16 siReason);

	// Ư�� ĳ���Ϳ��� ��ǰ�� �ִ� ó���� �Ѵ�. 
	void InputItem(cltCharServer* pclchar, cltItem* pclitem, SI32 inputitemreason);

	// ��ι�����Ʈ ���ʽ� Ÿ�� ����ڸ� ���Ѵ�. 
	SI32 PopSpecialQuestBonus();
	// ��ι�����Ʈ ���ʽ� Ÿ�� ����ڸ� ���ۿ� �ִ´�. 
	bool PushSpecialQuestBonus(SI32 personid);

	// ���� ������ ���ۿ� �ִ´�.
	bool PushSpecialNews(TCHAR * szTitle,TCHAR * szName, TCHAR * szURL, SI32 NewsKind = CAPTIONKIND_NEWS , SI32 SendKind = CAPTIONKIND_NEWS );

	// �����ϰ� ���� 1���� �̴´�.
	SI32 GetRandomID();

	//---------------------------------------------------
	// Server-BonusTime.cpp
	//---------------------------------------------------
	// ���� ���ʽ� Ÿ�� �׼�.
	void BattleBonusTimeAction();

	// ���� ���ʽ� Ÿ�� 
	void MakeBonusTimeAction();

	// ��ι� �̺�Ʈ ó��.
	void SpecialQuestAction();

	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	void ValentineEventGiveItemAction();


	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	void WhiteEventGiveItemAction();

	bool PushCash(SI16 charunique, SI32 personid, TCHAR* szaccountid, GMONEY money, SI32 reason, SI32 day = 3 );
	bool PopCash();

	void RefreshHouseUnit();
	void RefreshInvestList();
	void RefreshStock();

	void SendLog_InventoryFull( SI32 personid, SI32 itemunique, SI32 itemnum, SI32 reason );
	void SendLog_GiveQuestItem(SI32 personid,SI32 questtype , SI32 questunique,SI32 itemunique,SI32 itemnum,SI32 ncoin,SI32 usedate,bool success );
	void SendLog_GetQuest(SI32 personid,SI32 questtype , SI32 questunique,bool start);
	void SendLog_Warp(SI32 personid, SI32 mapunique);
	void SendLog_MofuMofuEvent_Start(SI32 villageunique);
	void SendLog_SetHappyBeanClearInfo(cltCharServer* pclchar, SI32 siQuestType, SI32 siQuestState);

	//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	void SendLog_SetEventCouponInfo(cltCharServer* pclchar, SI32 siEventType, SI32 siPara);
	//LEEKH - 2007.10.29 - �Լ� �߰�
	void SendLog_SetEventCouponInfo(TCHAR* pszAccountID, TCHAR* pszCharName, SI32 siPersonID, SI32 siEventType, SI32 siPara);
	
	////�����̺�Ʈ [2007.09.10 �ռ���]
	//void SendLog_SetAUCTIONEventCouponInfo(cltCharServer* pclchar, SI32 siEventType);


	// by LEEKH - 2007.08.21 - ���ο� �α� �ý���
	void SendLog_WriteLogToDB(	SI16 siCommandType, SI16 siCommandIndex, UI08 uiReason, cltCharServer* pclchar, cltSummon* pclSummon, SI32 siTargetPersonID, GMONEY money, GMONEY moneysum, 
								cltItem* pclItem, SI32 siHaveItemCount, SI32 siMonKind, SI16 siNpcKind, SI32 siVillageUnique, SI32 siRPPoint, SI32 siFameExp,
								SI64 siParam1, SI64 siParam2, SI64 siParam3, SI64 siParam4, SI64 siParam5, TCHAR* pszCharParam1, TCHAR* pszCharParam2);

	void SendSet_InstanceProfitVillage(SI32 charid,bool start = false );
	
	void SetTodayVillageWarInfo();

	bool HireEventNPC(SI32 kind, SI32 villageunique, UI16 siSlot, bool mode);

	// ���� �ٿ� ������ ���� ��ġ ����
	////======================================================
	//// �޽�����
	////======================================================
	//// �����޽��� ó�� �Լ�������
	//class stServerMsgPtr
	//{
	//public:
	//	void (cltServer::*ServerMsgFunc)(cltMsg* pclMsg, SI32 id);
	//};

	//stServerMsgPtr *m_pServerMsgPtr;
	//void	ServerMsgNullFunc(cltMsg* pclMsg, SI32 id);
	//void	RegisterServerMsgMap();

	//// DB�޽��� ó�� �Լ�������
	//class stDBMsgPtr
	//{
	//public:
	//	void (cltServer::*DBMsgFunc)(sPacketHeader* pPacket);
	//};

	//stDBMsgPtr *m_pDBMsgPtr;
	//void	DBMsgNullFunc(sPacketHeader* pPacket);
	//void	RegisterDBMsgMap();
	////======================================================

	
	bool	CheckWarp( SI32 ID, SI32 MapIndex, SI32 DestX = -1, SI32 DestY = -1 );

	// pvp-
	SI32	GetPVPWeaponDamage( SI32 RealDamage, SI32 AttackType );

	static bool	NewYearEventDay(void);
	void	NewYearLuckyBox(cltItem& clfromitem);
	void	NewYearButton(void);

	void	NewYearEffect(void);

	//KHY - 0530 ���� ���� ��������.
	bool CanChargingBuyLimit( );
	bool CanChargingSystemBuyItemLimit( );
	void SystemMarketSell( void );
	
	// ���� ���� �� �߷�Ÿ�ε��� �ַγ�? ��� ���´�.
	void	SetValentineDayOnTime(void);
	// ���� 12�� ������ ��޺�ȭ�� ��ε� �ɽ��� �Ѵ�.
	void	ChangePvPWarGradeInfo(void);
	
	bool	IsUseFourLeaf( SI32 siItemUnique, cltCharServer* pclchar );	// ���� ��밡���� ����ũ�ι� �ΰ�?

	NTCHARString<4> GetTradeServer_ServerNation( SI32 ServiceArea );
	SI16	GetTradeServer_CharNation( cltCharServer* pclchar );

	// 12�ð� �Ǹ� �Ϸ絿���� ��� ���ο� ����� ���� �ʱ�ȭ.
	void InitHuntMapWarEnemy();

	// ����ã�� �̺�Ʈ 
	void Read_TreasureEvent_Map_Info()	;		// �� ������ �о� �´�.// ���ε��� ���� �ִ��� ���� npc ����.
	void Write_Kill_NPC_Num( SI32 mapindex )	;	// ���� npc ���
	void Respon_TreasureEvent_Npc()	;			// ���� npc ��ŭ �ٽ� �̺�Ʈ npc ����	
	void Read_TreasureEvent_MapInfo_TheQ()	;	// �� ��ǥ ������ �о� �´�.
	SI32 MakeMapRocSlot( SI32 siMapindexSlot , SI32 MakeNpcNum )	;					//  ���� ��ǥ�� ����� ��ǥ �� ����� ���� .

	// ���� 
	void AddFamily( SI32 siParent_PersonID, SI32 siChildren_PersonID,SYSTEMTIME stFamilyEffectTime)	;	// ���� �������� �߰� �Ѵ�.
	void DelFamily( SI32 siDelTargetPersonID )	;	// ���� �������� ���� �Ѵ�.
	void UpdateFamily( CFamily* pclPamily,SI32 siPersonID )	;//  ���� personID�� �ɸ����� ���� ������ �������� ������������ ������Ʈ ���ش�

	void SetGachaRareItem_Time()	;	//�ش� �Ⱓ�� ���� ���� �ְ� ��ǰ����ũ�� ���� �Ѵ�. 

	void AddMagicAction( SI32 _siID, SI32 _siTargetID, SI32 _siMagicKind, SI32 siDamage );
	void SubMagicAction( SI32 _siID, SI32 _siTargetID, SI32 _siParentMagicKind, SI32 siDamage );

	// â��
	BOOL MOVEITEMINVTOSTG(SI32 siCharId, SI32 siVillageUnique, SI32 siHouseIndex, SI32 siItemPos, cltItem* pclInvenItem, bool bNoMoveNewPos = false);

	// [����] ���ֵ��̹̼� : ��� ����Ǿ� �ִ� ���ֵ��� �̼� ���೻���� �ʱ�ȭ �ϵ��� �ϴ� �Լ�
	void GoonzuDayMissionInfo_Reset();
};
#endif
