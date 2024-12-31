//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _COMMONLOGIC_H
#define _COMMONLOGIC_H

#define CHANNELINGCODE_NETMARBLEJP 1 //����� ��� ����.

//----------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�.
//----------------------------------------------------------
#define CHANNELINGCODE_NDEJP			-1  // NDE  - ������ ������� �ʴ´�. - ����(0618) NDE �� 0 ���� ���´�.
#define CHANNELINGCODE_HANGAMEJP		2  // �Ѱ��� 
#define CHANNELINGCODE_GAMANIAJP		3  // �����Ͼ�
#define CHANNELINGCODE_GAMEPOTJP		4  // ������
#define CHANNELINGCODE_NEXONJP			5  // ������

//----------------------------------------------------------
#define	MAX_MONSTERDROPITEM_NUM		20	// ���� ����ϴ� �ִ� ������ ����
#define MAX_WORLDTREE_COUNT			2	// ũ���������̺�Ʈ - ����Ʈ�� ����

// ���� Ŭ���̾�Ʈ �����. 
#include <directives.h>
#include "../common/CommonHeader.h"
#include "../Server/Time/MyTime.h"
#include "../Common/Map/TileSet/TileSet.h"
#include "Village/Village.h"
#include "NHashTableString.h"

#include "../Lib/CRC32/CRC32.h"

#ifdef USE_GAME_GUARD_SERVER

#include "../GameGuard/ggsrv25.h"
#pragma comment(lib, "ggsrvlib25.lib")

#endif

#ifdef USE_GAME_GUARD_CLIENT
#ifdef _KOREA
#include "../GameGuard/NPGameLib.h"
#pragma comment(lib, "NPGameLib.lib") 
#endif

//#define NO_GAMEGUARD
#ifdef _TAIWAN
#include "../GameGuard/NPGameLib_MD_DE.h"
#pragma comment(lib, "NPGameLib_MD_DE.lib")
#endif

#endif

// �弳 ���͸�.
#ifdef _IAF_EXPORT
	#include "../IAF/IAF_Export.h"		

	#ifdef _DEBUG
		#pragma comment(lib, "IAFD.lib") 
	#else
		#pragma comment(lib, "IAF.lib") 
	#endif
#endif



// ���� Ÿ�� 
#include "AttackType/AttackType.h"

#include "../Common/Message/Message.h"
#include "../Client/ToolBar/ToolBar.h"
#include "../Common/Map/MapManager/MapManager.h"
//#include "../Common/CharStatus/CharStatus.h"
#include "../Common/Item/ItemServer/Item-ManagerServer.h"
#include "../Common/Item/ItemClient/Item-ManagerClient.h"
#include "../Common/Config/Config.h"
#include "../Common/Item/ItemCommon/NPCItem.h"
#include "../Common/Item/ItemCommon/ItemCommon.h"
#include "../Common/Char/PersonNameManager/PersonNameManager.h"
#include "../CommonLogic/Guild/GuildWar.h"
#include "LogPrint/LogPrint.h"

#include "CountryMgr/CountryManager.h"

#include "../CommonLogic/TextMgr/TextMgr.h"
#include "../common/Map/FieldObject/FieldObject.h"
// �弳 ����
#include "../Client/abusefilter/AbuseFilter.h"

#include "../common/BlackWar/BlackWar.h"
#include "../common/Event/MonsterAttackEvent/MonsterAttack.h"
#include "../Server/HelperManager/HelperManager.h"

#include "../common/PVP_Leage/PVP_LeageMgr.h"
#include "../CommonLogic/Guild//GuildHuntMapWarManager.h"
//#include "../CommonLogic/Guild/GuildHuntMapWarStatMgr.h"
#include "../CommonLogic/BalanceCurrency/BalanceCurrencyMgr.h"

#include "../CommonLogic/SoulGuardMgr/SoulGuardMgr.h"

#include "../common/RacoonDodgeEvent/RacoonDodgeEvent.h"

#include "../common/BokBulBokEventMgr/BokBulBokEvent.h"
#include "../CommonLogic/PartyMatchingMgr/Server_PartyMatchingMgr.h" // ��Ƽ��Ī

#include "../CommonLogic/DormancyAccountSystem/DormancySystem.h"
#include "../CommonLogic/ValentineEvent/ValentineEvent.h"
#include "../common/Reward/RewardItemByProbMgr.h"

#include "..\Common\Char\KindInfo\KindInfo.h"

#include "BoxItemMgr/BoxItemMgr.h"

class cltWarRankManager;
class TSpr;
class cltCursor;
class AttackTarget;
class cltBulletManager;
class cltSmokeManager;
class cltDevTool;
class cltDevServerInfo;
class cltSmallMap;
class cltNPCGroup;
class cltSystemNPCManager;
class CForeignMerchantNPCMgr;
class CTradeMerchantNPCMgr;
class CPrivateTradeOrderMgr;
class CMagicMgr;
class cltSkillManager;
class cltOrderManager;
class cltKindInfoSet;
class cltPersonInfo;
class cltAttackTarget;
class cltKey;
class cltDiseaseManager;
class cltQuestManager;
class cltNPCManagerCommon;
class cltBlackArmyManager;
class cltKoinoboryManager;
class cltSantaRaccoonManager;
class cltKoinoboryFamilyManager;
class CGachaManager;
class CGacha2Manager;
class CArtifactRestoreManager;		//[�߰� : Ȳ���� 2008. 3. 3 => ��Ƽ��Ʈ ȯ�� ������ ����.]
class CFourLeafManager;

class CPartyMgr;
class cltAskManager;
class cltMasterManager;
class CNMasterInfo;

//class cltSchoolManager;
class cltFatherManager;
class cltHiredNPCPayManager;
class cltIdentity;

class CHuntMapInfo;

class cltItemMallManager;
class cltItemMallButtonManager;

class cltMonsterGroupManager;

// ���ü����� 
class cltCityHallManager;
class cltBankManager;
class cltMarketManager;
class cltHouseManager;
class cltStockManager;
class cltHuntManager;
class cltPostOfficeManager;
class cltHorseMarketManager;
class cltRealEstateMarketManager;
class cltSummonMarketManager;
class cltLandManager;
class cltFeastManager;
class cltSummonHeroMarketManager;
class cltMineManager;
class cltGuildManager;
class cltNewMarket_Manager;

class CStockDistributionMgr;
class CVoteMgr;
class CDailyQuestMgr;
class CDailyQuest2Mgr;
class CDailyQuest3Mgr;
class cltHorseManager;
class cltGameMasterManager;

class CFishingMgr;
class CFarmingMgr;


class cltEventHunting;
class cltMofuMofuEvent;
class CMonsterAttackEvent;

class cltAutoHuntingManager;
class cltVillageStructureSet;

class CForeignMerchantNPCBuyCashItem;

class CNTeacherDlg;
class CNFatherDlg;

class cltGameEvent;

class cltWorldTraderManager; // ��ť �Ŵ���
class cltDistributionWorldMoney; // ��ť ���� �Ŵ���

class CMiningMgr;

class CRPMerchantNPCMgr;
class cltGuildDungeonItem;
class cltEventStructure;
class cltEventTimeManager;

class CBlackWarManager;
class cltNamingQuestManager;

class CVoteStatusMgr;			// [����] ���� ��ǥ

//====================================
// ���� �̺�Ʈ�� Ŭ����
class CNServerRankInfo;				
class CNPersonalRankInfo;
class CNServerEvent_Rank_Record;
class CNServerEvent_Manager;
//====================================

class cltHelperManager;

class CPVP_LeagueMgr;
class cltGuildHuntMapWarManager;// [����] ��� ����� ���� ����� �Ŵ���.
class cltGuildHuntMapWarStatMgr;// [��ȣ] ��� ����� ���� ����� ���� �Ŵ���.

class cltMarriageManager;
class CBalanceCurrencyMgr;		//	[��ȣ]  20090526 ��ȭ�� ���� �Ŵ���

class CRacoonDodgeEventMgr;

class CServer_BBBMgr;		// [����] ���Һ� ���� �޴���
class CDormancySystem;			//	[����] �޸� ���� �ý���
class CRewardItemByProbMgr;		//  [����] Ȯ�� ���� ������ �޴���
class CPartyQuestMgr_Common;	//	[��ȣ] ��Ƽ����Ʈ �Ŵ���;
class CValentineEventMgr;

class CHuntQuestItemMgr;

class CBoxItemMgr;

// ���� ���� ���� 		
enum eGameStatus{
	GS_INITCONNECTFRONTSERVER		= 1	,
	GS_CONNECTFRONTSERVER				, 

	GS_SHOWGOVERNMENT,	

	GS_INITSELECTWORLDLIST,
	GS_SELECTWORLDLIST, 

	GS_INITCONNECTGAMESERVER,
	GS_CONNECTGAMESERVER	,

	GS_INITCHARLIST			, 
	GS_CHARLIST				,

	GS_GAME,
	GS_GAMEDESTROY,
};

// �Ѱ��� �� ���� ���� ������

#define HANREPORT_CLIENT_GAMESTART			"300"

#ifdef _KOREA
	#define HANREPORT_CLIENT_GAMEEND		"301"
#else
	#ifdef _NHN_CHINA
		#define HANREPORT_CLIENT_GAMEEND		"331"
	#else 
		#define HANREPORT_CLIENT_GAMEEND		"900"
	#endif
#endif

#define HANREPORT_CLIENT_INITCOMPLETE		"302"

#define HANREPORT_CLIENT_GAMESTRING_FAILED	"305"

#define HANREPORT_CLIENT_LOGIN_REQUEST		"309"
#define HANREPORT_CLIENT_LOGINOK			"310"
#define HANREPORT_CLIENT_LOGIN_FAILED		"311"
#define HANREPORT_CLIENT_SELECTSERVER		"315"
#define HANREPORT_CLIENT_SELECTCHAR			"320"
#define HANREPORT_CLIENT_MAKECHAR			"325"

#define HANREPORT_CLIENT_LOGINTOGAMESERVER		"330"
#define HANREPORT_CLIENT_LOGOUTFROMGAMESERVER	"331"


#define HANREPORT_SERVER_STARTED			"400"
#define HANREPORT_SERVER_ENDED				"499"

#define _CCSAUTH_STATE_INIT					"410"	// ������ �ʱ�ȭ.
#define _CCSAUTH_STATE_FIRST_AUTH_SENDED	"411"	// ù��° ����.
#define _CCSAUTH_STATE_FIRST_AUTH_CHECK		"412"	// ù��° ���� �˻�.
#define _CCSAUTH_STATE_N_AUTH_SEND			"413"	// N ��° ���� ����.
#define _CCSAUTH_STATE_N_AUTH_CHECK			"414"	// N ��° ���� �˻�.
#define _CCSAUTH_STATE_CLOSE				"415"	// ����.


// ���� ��Ʈ��ũ �޽��� ���� . 
#include "MsgType.h"

/*
typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER    NameBuff [30];

}ASTAT, * PASTAT;*/

class cltCommonLogic;
class cltClient;
class cltServer;

cltCommonLogic*	GetCommonLogic();
cltClient* GetClientClass();
cltServer* GetServerClass();

NHashTableString< int >* GetGlobalHashTableString();


extern cltCommonLogic *pclClient;

#define MAX_SETCHAR_RESERVE_NUMBER		300

//---------------------------
// ������ ����. 
//---------------------------
#define MAX_DEV_TOOL_NUM				10			// ������ ��ȭ������ ����. 
#define DEV_TOOL_CHARINFO				0
#define DEV_TOOL_NPCINFO				1	
#define DEV_TOOL_PROFILEINFO			2
#define DEV_TOOL_SERVERINFO				3
#define DEV_TOOL_INHEREMAPCHAR			4			// ���� ���� �ִ� ���� �ɸ���/NPC�� ���õ� ����������

#ifndef _CHINA
	const SI32 Recommendpoint[120] = {	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										10, 4, 5, 6, 7, 8, 9, 10, 11, 20,
										12, 13, 14, 15, 16, 17, 18, 19, 20, 40,
										21, 22, 23, 24, 25, 26, 27, 28, 29, 60,
										35, 40, 45, 50, 55, 60, 65, 70, 75, 100,
										80, 90, 100, 110, 120, 130, 140, 150, 160, 200,
										120, 130, 140, 150, 160, 170, 180, 190, 200, 300,
										210, 225, 240, 255, 270, 285, 300, 315, 330, 400,
										360, 380, 400, 420, 440, 460, 480, 500, 520, 600,
										540, 560, 580, 600, 620, 640, 660, 680, 700, 800,
										720, 740, 760, 780, 800, 820, 840, 860, 880, 1000,
								   	
};
#else
	const SI32 Recommendpoint[120] = {	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 20,
										11, 12, 13, 14, 15, 16, 17, 18, 19, 30,
										21, 22, 23, 24, 25, 26, 27, 28, 29, 40,
										31, 32, 33, 34, 35, 36, 37, 38, 39, 60,
										41, 42, 43, 44, 45, 46, 47, 48, 49, 80,
										51, 52, 53, 54, 55, 56, 57, 58, 59, 120,
										61, 62, 63, 64, 65, 66, 67, 68, 69, 160,
										71, 72, 73, 74, 75, 76, 77, 78, 79, 200,
										81, 82, 83, 84, 85, 86, 87, 88, 89, 240,
										91, 92, 93, 94, 95, 96, 97, 98, 99, 280,
};    
#endif


// ĳ���� ������ �������� Ŭ���̾�Ʈ�� ���� �� 
// ����� ������ ���� 
// �� Ŭ������ ���� �Է��� �Ŀ� Ŭ���̾�Ʈ�� ������. 
class cltBasicCharUpdateInfo{
public:
	SI16 siCharUnique;
	SI08 siMoveSpeed;
	bool bUrgentMode;
	SI32 siLife;
	SI32 siReservedLife;
	SI32 siMana;
	SI16 siX, siY;
	UI08 uiGMMode;
	bool bPCRoom;
	SI08 siMakeAniType;

	cltBasicCharUpdateInfo(SI16 charunique, SI32 silife, SI32 reservedlife, SI32 mana, SI16 x, SI16 y, SI08 movespeed, bool burgent, UI08 gmmode, bool pcroom, SI08 makeanitype  )
	{
		siCharUnique	= charunique;
		siLife			= silife;
		siReservedLife	= reservedlife;
		siMana			= mana;
		siX				= x;
		siY				= y;
		siMoveSpeed		= movespeed;
		bUrgentMode		= burgent;
		uiGMMode		= gmmode;
		bPCRoom			= pcroom;
		siMakeAniType	= makeanitype;
	};
};

#define MAX_CRCFILECHECK_COUNT	1000

class NCRCFileCheck
{
public:
	NTCHARString128		m_FileName;
	UI32				m_siCRCCode;
	UI32				m_siFileSize;

public:
	NCRCFileCheck()
	{
		m_siCRCCode		= 0;
		m_siFileSize	= 0;
	}

	void Set(NCRCFileCheck* pFileCheck)
	{
		if(pFileCheck == NULL)			return;
        
		m_FileName		= pFileCheck->m_FileName;
		m_siCRCCode		= pFileCheck->m_siCRCCode;
		m_siFileSize	= pFileCheck->m_siFileSize;
	}
};

class NCRCFileCheckManager
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<NCRCFileCheck*, MAX_CRCFILECHECK_COUNT>	m_Files;
#else
	NCRCFileCheck*		m_Files[MAX_CRCFILECHECK_COUNT];
#endif
	SI32				m_siCount;
	CCRC32				m_CRC;

	NCRCFileCheckManager()
	{
#ifdef _SAFE_MEMORY
		m_Files.ZeroMem();
#else
		ZeroMemory(m_Files, sizeof(m_Files));
#endif
		m_siCount = 0;
	}

	~NCRCFileCheckManager()
	{
		for(SI32 i=0; i<MAX_CRCFILECHECK_COUNT; i++)
		{
			if( m_Files[i] != NULL )
				delete m_Files[i];
		}
	}

	void Init();
	void AddFile(const TCHAR* pszFileName);
	bool CheckFile(NCRCFileCheck* pCRCFileCheck);

	void RequestCheckFile();
};

template< class DataType >
class NHashTableString;

// �Լ���� define
#define LUA_RegisterCFunction(LUA, FUNC)		LUA.RegistCFunction( FUNC, #FUNC );

//---------------------------------------------
// cltCommonLogic
//---------------------------------------------
class cltCommonLogic : public NkMemory
{
protected:
	// ������ Ŭ���̾�Ʈ�� �������� �����ϴ� ����. 
	HWND				    Hwnd;
	HINSTANCE				hInst;
	TCHAR					AppName[MAX_PATH];

	UI32					uiFrame;				// ������ ����� ����. 

	SI32					siGameStatus;			// ������ ���� ���¸� �˸��� ����. 

	SI32					siFrameDelay;			// �������Ӵ� �ҿ� �ð�. 

	stWeatherData			CurrentWeather;			// ������ ����. 

	//-----------------------------------
	// ������ ����. 
	//-----------------------------------
	SI32	siVersion;


public:
	//----------------------------------
	// ���� ���� 
	//----------------------------------
	SI32					siServiceArea;

	//----------------------------------
	// ���� ���
	//----------------------------------
	SI32					siRunMode;

	//-------------------------------------------
	// ��� ��� ( ���� �� ���� ��� ���� ) 
	//-------------------------------------------
	SI32 siLanguage; 

	//-------------------------------------------
	// � ü�� ���� 
	//-------------------------------------------
	//osvi.dwPlatformId , osvi.dwMajorVersion , osvi.dwMinorVersion ,  osvi.wProductType
	DWORD dwPlatformId;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	BYTE  wProductType;

	//----------------------------------
	// �׽�Ʈ��
	//----------------------------------
	SI32					siMaster;

	// �� ������ �⺻ ����. 
	SI16					siServerUnique;
	TCHAR					szServerID[20];	// CNC, CTC����, ��������, ��������
	TCHAR					szServerName[20];
	bool					bItemMallUseSwitch;
	SI32					siMarketAutoBuyDelayFrame;
	SI32					siHorseMarketAutoBuyDelayFrame;

	// SJY
	SI32					siEventItemDropRate;

	SI32					siMinimumTeacherLevel;
	
	cltMapManager*			pclMapManager;

	cltConfig*				pclConfig;

	//	cltTextMgr*				pclTextMgr;
	//	cltTextMgr*				pclStructureMgr;

	cltDiseaseManager*		pclDiseaseManager;
	cltCharManager*			pclCM;
	cltKindInfoSet*			pclKindInfoSet;

	cltPersonNameManager*		pclPersonNameManager;
	cltNewPersonNameManager*	pclNewPersonNameManager;

	cltSkillManager*		pclSkillManager;
	cltItemManagerCommon*	pclItemManager;

	cltBulletManager*		pclBulletManager;
	cltSmokeManager*		pclSmokeManager;

	cltTileManager*			pclTileManager;				// ������ ����� Ÿ�� ��Ʈ�� ���� ������ �����Ѵ�. 
	cltFieldObjectManager*	pclFieldObjectManager;		// ������ ����� �ʵ� ������Ʈ ��Ʈ�� ���� ������ �����Ѵ�. 

	// ���߿� �ʿ��� ���� ��. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltDevTool*, MAX_DEV_TOOL_NUM>		pclDevTool;
#else
	cltDevTool*			pclDevTool[MAX_DEV_TOOL_NUM];
#endif


	// �� �ü����� ������. 
	cltBankManager*				pclBankManager;
	cltStockManager*			pclStockManager;
	cltCityHallManager*			pclCityHallManager;
	cltMarketManager*			pclMarketManager;
	cltHouseManager*			pclHouseManager;
	cltHuntManager*				pclHuntManager;
	cltPostOfficeManager*		pclPostOfficeManager;
	cltHorseMarketManager*		pclHorseMarketManager;
	cltRealEstateMarketManager*	pclRealEstateMarketManager;
	cltSummonMarketManager*		pclSummonMarketManager;
	cltLandManager*				pclLandManager;
	cltFeastManager*			pclFeastManager;
	cltSummonHeroMarketManager* pclSummonHeroMarketManager;
	cltMineManager*				pclMineManager;
	cltGuildManager*			pclGuildManager;
	//cltNewMarketManager*		pclNewMarketManager;
	cltNewMarketManager*		pclNewMarketManager;


	cltVillageManager*			pclVillageManager;			// ���� ������ �����ϴ� �����̴�. 
	cltVillageStructureSet*		pclVillageStructureSet;
	cltAttackTypeInfoManager*	pclAttackTypeInfoManager;
	cltSystemNPCManager*		pclSystemNPCManager;
	CForeignMerchantNPCMgr*		pclForeignMerchantNPCMgr;		// ���� ����(û, �Ϻ�) NPC
	CTradeMerchantNPCMgr*		pclTradeMerchantNPCMgr;			// ���� ���� NPC 
	CRPMerchantNPCMgr*			pclRPMerchantNPCMgr;			// ��õ ����Ʈ ��ǰ ������
	CPrivateTradeOrderMgr*		pclPrivateTradeOrderMgr;		// ���ΰ� �ŷ�	
	CMagicMgr*					pclMagicManager;
	cltOrderManager*			pclOrderManager;
	cltQuestManager*			pclQuestManager;

	cltNamingQuestManager*		pclNamingQuestManager;			// ���̹� ����Ʈ

	CBlackWarManager*			pclBlackWarManager;				// ���Ǳ��� �����̺�Ʈ( ���� )
	cltBlackArmyManager*		pclBlackArmyManager;			// ���Ǳ��� �̺�Ʈ �Ŵ���
	cltKoinoboryManager*		pclKoinoboryManager;			// ���̳뺸�� �̺�Ʈ �Ŵ���.
	cltSantaRaccoonManager*		pclSantaRaccoonManager;			// ��Ÿ������ �̺�Ʈ �Ŵ���
	cltKoinoboryFamilyManager*  pclKoinoboryFamilyManager;		// ���̳뺸�� ���� �̺�Ʈ �Ŵ���.

	CGachaManager*				pclGachaManager;				// ��í ���� ������ ��� �޴���
	CGacha2Manager*				pclGacha2Manager;			//KHY - 1104 -  ����2 -���� ���� ����. 

	CArtifactRestoreManager*	pclArtifactRestoreManager;	// [�߰� : Ȳ���� 2008. 3. 4 => ��Ƽ��Ʈ ȯ���� ���Ǵ� ������ ������.]

    CFourLeafManager*			pclFourLeafManager;

	CPartyMgr*					pclPartyMgr;		// ��Ƽ ����
	CStockDistributionMgr*		pclStockDistributionMgr;
	CVoteMgr*					pclVoteMgr;			// ��ǥ
	CDailyQuestMgr*				pclDailyQuestMgr;	// Daily ����Ʈ
	CDailyQuest2Mgr*			pclDailyQuest2Mgr;	// Daily ����Ʈ2
	CDailyQuest3Mgr*			pclDailyQuest3Mgr;	// Daily ����Ʈ3
	CFishingMgr*				pclFishingMgr;		// ����
	CFarmingMgr*				pclFarmingMgr;		// ���
	CForeignMerchantNPCBuyCashItem*	pclForeignMerchantNPCBuyCashItem;	// ĳ�� ������ ����

	CMiningMgr*					pclMiningMgr;

	cltMonsterGroupManager*		pclMonsterGroupManager;

	cltWarRankManager*			pclWarRankManager;
	cltMasterManager*			pclMasterManager;

	//	cltItemMallManager*			pclItemMallManager; // ������ �� �Ŵ���
	//	cltItemMallButtonManager*	pclItemMallButtonManager; // ������ �� ��ư �Ŵ���

	cltAutoHuntingManager*		pclAutoHuntingManager; // �ڵ� ��� üũ �Ŵ���

	// NPC������.
	cltNPCManagerCommon* pclNPCManager;
	cltHiredNPCPayManager *pclHiredNPCPayManager;

	//	cltSchoolManager*		pclSchoolManager;
	cltFatherManager*		pclFatherManager;

	cltHorseManager*		pclHorseManager;

	cltGameMasterManager*   pclGMManager;

	cltEventHunting*		pclEventHunting;

	cltMofuMofuEvent*		pclMofuMofuEvent;

	cltGameEvent*			pclGameEventManager;

	CMonsterAttackEvent*	pclMonsterAttackEvent;

	cltWorldTraderManager*	pclWorldTraderManager;
	cltDistributionWorldMoney* pclDistributionWorldMoney;

	cltCountryManager*		pclCountryManager;		
	// �Ϻ��ǿ��� �������� ���̱� ������ �ϳ� �� ����
	cltCountryManager*		pclCountryManagerJapan;	

	cltGuildDungeonItem*	pclGuildDungeonItemMgr;
	CAbuseFilter			*m_pCAbuseFilter;

	cltEventStructure*		pclEventStructure;

	cltEventTimeManager*	pclEventTimeManager;

	NCRCFileCheckManager*	pclCRCFileCheckManager;		// CRC�ڵ带 �̿��Ͽ� ������ üũ�ϴ� �޴���

	cltDevServerInfo*		pclserverinfoDlg;

	CVoteStatusMgr*			pclVoteStatusMgr;			// [����] ���� ��ǥ���� �޴���

	CNServerEvent_Manager*  pclServerEventManager;		// [����] ���� �̺�Ʈ �޴���. => 2008-6-20

	cltHelperManager*		pclHelperManager;			// [����] ����� => 2008-10-14

	CPVP_LeagueMgr*			pclPVP_LeagueMgr;			// [����] pvp_League

	cltGuildHuntMapWarManager*	pclGuildHuntMapManager ;	// [����] ��� ����� ���� ����� �Ŵ���. 2009-03-27

	cltGuildHuntMapWarStatMgr*	m_pclGuildHuntMapWarStatMgr;	//[��ȣ]����ͼ������(Random) �����

	CRacoonDodgeEventMgr*	pclRacoonDodgeEventMgr;				//[����] ���� ���ϱ� �̺�Ʈ //Switch_10MonthEvent_RacoonDodge

	CDormancySystem*		pclDormancySystem;			// [����] �޸� ���� �ý���

	CValentineEventMgr*		m_pclValentineEventMgr; // [����] �߷�Ÿ�� �̺�Ʈ

	CServer_BBBMgr*			m_pServer_BBBMgr;		// [����] ���Һ� �̺�Ʈ �޴���

	CServer_PartyMatchingMgr*	m_pServer_PartyMatchingMgr;		// [����] ��Ƽ��Ī �Ŵ���

	TCHAR	SavePath[256];								// ���� ������ ��ġ�� ��� 

	CRewardItemByProbMgr*	m_pclRewardItemByProbMgr;	// Ȯ�� ���� ������ �Ŵ���

	CHuntQuestItemMgr*		m_pHuntQuestItemMgr;

	// �޽��� ����
	cltMessage* pclMessage;

	SI32 GameMode;							// �� ������ � �����ΰ� ?(����, Ŭ���̾�Ʈ, �ʿ����͵�.. ) 
	// GAMEMODE_SERVER
	// GAMEMODE_CLIENT
	// GAM DE_MAPEDIT


	//--------------------------------------------
	// Ŀ������
	//--------------------------------------------
	cltCursor*		pclCursor;


	//------------------------------------
	// ���ӿ� ���Ǵ� �ð躯�� 
	//------------------------------------
	DWORD StartClock, CurrentClock;

	//----------------------------------
	//	NPC�� ������ ����. 
	//----------------------------------
	cltNPCItemInfo* pclNPCItemInfo;

	//---------------------------------
	// ���� ���. 
	//---------------------------------
	CLogPrint* pclLog;

	NHashTableString< int >*	pclHashTableString;
	NHashTableString< SI64 >*	pclHashTableGlobalValue;

	//
	cltMarriageManager*			m_pclMarriageMgr;

	CBalanceCurrencyMgr*		m_pclBalanceCurrencyMgr;	//	��ȭ�� ���� �Ŵ���

	cltSoulGuardMgr*			m_pclSoulGuardMgr;

	//---------------------------------
	// ���ڷ� ������ ���� �޴���
	//---------------------------------
	CBoxItemMgr*				m_pclBoxItemMgr;

	//---------------------------------
	// ������ Ŭ���̾�Ʈ�� �����ؾ��� ����. 
	//---------------------------------
	bool	bVillageWarSwitch;		// ������ ������ �ð����� ���� 
	bool	bBonusTimeSwitch;		// ����ġ�� 2��� �ִ� �����̾� Ÿ���ΰ�������. 
	bool	bBonus2TimeSwitch;		// ���� ����ġ�� 2��� �ִ� �����̾� Ÿ���ΰ�������. 
	bool	bSpecialQuestBonusTimeSwitch;
	bool	bBroadcastSwitch;		// ��������� ����. 
	SI08	siBestVillageLevel;		// �ְ� ���� ���� 
	bool	bBonusTimeGoonzu;		// ���� ���ʽ� Ÿ�� ����


	//---------------------------------------------------------------------------------
	bool	bTimeCount	;		// TimeSet���� ���õ� �ð��� Ÿ�� ī��Ʈ�� ���� �Ѵ� .
	float	siTimeSet	;
	SI32	siRoundCount	;	// ������ ���� 
	DWORD	dwWriteSetTime	;	// Ÿ�� �� �� �ð� ��� 1�ʾ� ���� ���ؼ� 
	

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_EVENT_NUMBER>		bEventSwitch;
#else
	bool	bEventSwitch[MAX_EVENT_NUMBER];		
#endif
	bool	bEnchantSwitch;

	SI16	siServiceAge;		// ������ ���� ���� ����
	SI08	siEnablePVP;		// PVP���� ����

	SI16 sUpViewEffect; //KHY - 0723 - �Ⱓ������ �ı� ����. �Ⱓ ���� ǥ��. 0= ����. 1 = �Ⱓ���� ������.

	// [����] Auto Unblock - 2008.02.21
	bool	bAutoUnblock;

	// [����] ���� �����Ⱓ���� �˸�
	bool	bVoteCampaign;

	// [����] �̺�Ʈ�� On/Off�ϴ� ����ġ(EVENT_TOGGLE_SWITCH�� ���ο� �����ڸ� �߰��ϸ� �ٸ� �͵� ����)
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, EVENT_TOGGLE_SWITCH_MAX>	bEventToggleSwitch;
#else
	bool				bEventToggleSwitch[EVENT_TOGGLE_SWITCH_MAX];
#endif

	NBitArray<Switch_Last>		m_bitArray_SwitchContry;

	bool LoadSwichCountry();
	SI32 ConvertSwitchCountryToIndex(TCHAR* pszSwitch);
	bool IsCountrySwitch( SI32 siSwitchCountry );

#ifdef _SAFE_MEMORY
	NSafeTArray<cltAttendanceReward*, MAX_ATTENDANCE_COUNT>		m_pclAttendanceReward;
#else
	cltAttendanceReward*	m_pclAttendanceReward[MAX_ATTENDANCE_COUNT];
#endif

	NLua					m_clLua;
	
	// [���] ũ�������� �̺�Ʈ - �ʿ� ��ġ�Ǵ� ����Ʈ�� ID
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_WORLDTREE_COUNT>		siWorldTreeID;
#else
	SI32	siWorldTreeID[MAX_WORLDTREE_COUNT];
#endif

	// [���] ũ�������� �̺�Ʈ - Ʈ���� �Ǽ��Ǿ����� ����
	bool	bWorldTreeConstruct;
	DWORD	dwWorldTreeCreateClock;

public:
	//--------------------------
	// Virtual Methods
	//--------------------------
	virtual void InitNetwork(){};
	virtual TSpr* GetGlobalSpr(SI32 index){return NULL;}
	virtual bool SendDBMsg(SI32 siselect, sPacketHeader *pPacket){return false;}
	virtual	TCHAR* GetToolTip(SI32 idcommand){return NULL;}
	virtual void SetStatusBarText(TCHAR* text, SI32 index){};
	virtual SI32 GetScreenRX()const {return 0;}
	virtual SI32 GetScreenRY()const {return 0;}
	virtual bool DoMsg_WM_COMMAND(WPARAM wParam){return false;}
	virtual void ClientWinMain(){}
	virtual void PushKey(cltKey* pclkey){}
	virtual BOOL SendMsgToServer(sPacketHeader* pmsg){return FALSE;}

	cltCommonLogic( TCHAR* appname, HWND hwnd , HINSTANCE hinst, SI32 gamemode, SI32 servicearea, SI32 runmode );
	virtual ~cltCommonLogic();

	void MainInit();

	HWND GetHwnd()const{return Hwnd;}
	void SetHwnd(HWND hwnd){Hwnd = hwnd;}

	HINSTANCE GetInstance()const{return hInst;}
	void SetInstance(HINSTANCE hinst){hInst = hinst;}

	void SetFrame(UI32 frame){uiFrame =  frame;}
	UI32 GetFrame()const{return uiFrame;}
	void IncreaseFrame(){uiFrame ++;}

	//----------------------------------------
	// �ʱ�ȭ. 
	//----------------------------------------
	virtual void Init(){};
	virtual void Create();

	//--------------------------------------------
	// ��޸��� ��ȭ���� ó�� ���� 
	//--------------------------------------------
	BOOL ModalessDlgProc(MSG* pmsg);

	//-------------------------------------------
	// ���� ���� 
	//-------------------------------------------
	SI32 GetFrameDelay()const{ return siFrameDelay;}
	void SetFrameDelay(SI32 delay){siFrameDelay = delay;}

	//--------------------------------------------
	// ���콺 ���� ���� 
	//--------------------------------------------
	virtual BOOL GameOverHead(){return FALSE;};

	//---------------------------------------------
	// ĳ���� ���� ����. 
	//---------------------------------------------
	virtual BOOL IsUser(SI32 charunique){return FALSE;}			


	//---------------------------------------------
	// 
	//---------------------------------------------
	SI32 GetGameStatus()const{return siGameStatus;}
	void SetGameStatus(SI32 sistatus){ InterlockedExchange( (LPLONG)&siGameStatus, sistatus ); };

	//---------------------------------------------
	// SavePath �� Reg ó�� 
	//---------------------------------------------
	const TCHAR* GetSavePath()const{return SavePath;}

	//---------------------------------------------
	// ��Ʈ��ũ ���� 
	// CommonLogic-Network.cpp
	//---------------------------------------------
	virtual void NetworkOperation(){}
	virtual void  SetSessionChar() = 0;

	virtual BOOL InBufferMessageOperation(cltMsg* pclMsg, SI32 id){return FALSE;}

	//-----------------------------------------------
	// ĳ���� ó�� 
	// SetChar.cpp
	//-----------------------------------------------
	// ���� �⺻�� �Ǵ� ĳ���͸� �����Ѵ�. 
	bool MakeSimpleChar(SI32 id, SI32 charunique);

	// �Ϲ� ĳ���͸� �����Ѵ�. 
	SI32 SetChar(SI32 id, cltMakeCharInfo* pclmakecharinfo, cltGMCommandKindInfo* pclGMCommandKindInfo = NULL );

	// �Ϲ� ĳ���͸� �����Ѵ�. 
	SI32 SetChar1(SI32 id, SI32 charunique, SI32 childcharunique, SI32 summonindex, cltIdentity* pclidentityinfo, cltPersonInfo* pclUserCharInfo, cltInnerStatusInfo* pclInnerStatus, SI16 mySoulGuardUnique);

	//----------------------------------------------
	// ��� ó�� 
	// CommonLogic-order.cpp
	//----------------------------------------------
	// �÷��̾��� ����� �����Ѵ�. 
	BOOL LetOrder(cltOrderData *porder,SI32 id = 0);

	//---------------------------------------------
	// DevCharInfo
	//---------------------------------------------
	virtual BOOL CreateDevCharInfoDlg();
	static BOOL CALLBACK StaticDevCharInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//---------------------------------------------
	// DevNPCInfo
	//---------------------------------------------
	virtual BOOL CreateDevNPCInfoDlg();
	static BOOL CALLBACK StaticDevNPCInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//---------------------------------------------
	// DevProfileInfo
	//---------------------------------------------
	virtual BOOL CreateDevProfileInfoDlg();
	static BOOL CALLBACK StaticDevProfileDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//---------------------------------------------
	// DevServerInfo
	//---------------------------------------------
	virtual BOOL CreateDevServerInfoDlg();
	static BOOL CALLBACK StaticDevServerDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//---------------------------------------------
	// DevInHereMapChar
	//---------------------------------------------
	virtual BOOL CreateDevInHereMapCharDlg();
	static BOOL CALLBACK StaticDevInHereMapCharDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


	//-------------------------------------------
	// About ���� 
	//-------------------------------------------
	BOOL About();
	static BOOL CALLBACK StaticAboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


	//----------------------------------------
	// Char Information Update
	//----------------------------------------
	virtual BOOL SendCharUpdate(SI32 charunique, bool bmode){return FALSE;};

	//------------------------------------------------------
	// Village ���� 
	//------------------------------------------------------
	void Village();


	// �α��� ��ο� ����( goonzu, sbs ) url ������
	void GetGoonZuUrl( TCHAR *url, TCHAR *szID );						// ���� Ȩ������ 
	void GetMyCZUrl( TCHAR *url, TCHAR *szID );						// ���� ���� 
	void GetCharCZUrl( TCHAR *url, TCHAR *szMyID, TCHAR *szID );		// ���� ���� 

	void GetCZProfileUrl( TCHAR *url, TCHAR *szID );
	void GetCZDarakUrl( TCHAR *url, TCHAR *szID );
	void GetCZIntroUrl( TCHAR *url, TCHAR *szID );

	void GetSubSiteUrl(TCHAR * url,TCHAR *szSubPath,TCHAR *szID );		// ��Ÿ ���� ����Ʈ ���� - ������ �� ��
	void GetHelpSiteUrl(TCHAR * url,TCHAR *szID);

	void GetCPasswdUrl(TCHAR *url,TCHAR *szID);						// ��й�ȣ ���� ������

	// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
	//	TCHAR * GetTxtFromMgr(SI32 index , bool bStructure = false );


	//-----------------------------------------------
	// ���� ���� 
	//-----------------------------------------------
	virtual BOOL PushEffect(SI32 effect, SI32 x, SI32 y){return FALSE;}


	//-----------------------------------------------
	// �ʱ�ȭ 
	//-----------------------------------------------
	// ���� ������ ��ƾ�� ����ִ� �Լ� 
	// ���ϰ�: 0 -> normal
	SHORT GameProcess();
	virtual SHORT GameAction() { return 0; }

	bool IsChangeFileExist();
	void ChangeFile();

	//-----------------------------------
	// ������ ����. 
	//-----------------------------------
	SI32 GetVersion()
	{
		/*
		WIN32_FIND_DATA	wfd;

		HANDLE hSrch = FindFirstFile( TEXT("GoonZuRun1.exe"), &wfd );

		if ( hSrch != INVALID_HANDLE_VALUE )
		{
		if ( DeleteFile(  TEXT("Patch.exe") ) == TRUE )
		{
		rename( TEXT("GoonZuRun1.exe"), TEXT("Patch.exe") );
		CopyFile( TEXT("Patch.exe"), TEXT("GoonZuRun.exe"), FALSE );
		}
		else
		{
		DeleteFile(  TEXT("GoonZuRun.exe") );
		rename( TEXT("GoonZuRun1.exe"), TEXT("GoonZuRun.exe") );
		}

		FindClose( hSrch );
		}
		*/

		return siVersion;
	}
	void SetMasterArea();			// master.dat ���� �б�

	cltNPCGroup* GetNPCGroupPointer(SI32 npcgroup);

	SI32 GetUniqueFromHash( TCHAR* pText );
	UI32 GetMinuteFromsTime( _SYSTEMTIME time );
	_SYSTEMTIME GetTimeFromsMinute( UI32 datevary );
	cltDate SysteTimeToCltTime( _SYSTEMTIME time );

	SI32 GetMaxStaminaValue(SI32 summonskill, SI32 summonkind);
	SI32 GetSummonAttackBonus(SI32 summonskill);
	SI32 GetSummonDefBonus(SI32 summonskill);

	//----------------------------------------------
	//TradeServer
	//----------------------------------------------
	void GetServerNameFromNation(char*code,SI16 index,char*name);
	bool GetNationCode( OUT char* pszNationCode, IN SI32 siSize );	// ���� ���� ���� �ڵ�(����3����)�� �����´�

	//---------------------------------------------
	//Recommand Point
	//---------------------------------------------
	SI32 GetRecommendPointPerLevel(SI32 level);

	//---------------------------------------------
	bool IsWhereServiceArea( SI32 ServiceArea );

	bool GetItemByAttendanceDay( SI32 AttendenceDay, cltItem* pclItem );
	bool SetItemByAttendanceDay( SI16 siAttendenceDay, SI16 siItemUnique, SI16 siItemNum, UI16 uiDateUseDay );

	bool LoadGlobalValue();
	SI64 GetGlobalValue(TCHAR* pszGlobalValue);

	//----------------------------------------------
	// Lua ����
	//----------------------------------------------
	bool InitLua();

	SI32 GetTextColumn();
};


#endif
