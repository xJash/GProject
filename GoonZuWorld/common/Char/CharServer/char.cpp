#include "../Common/CommonHeader.h"
#include "../CommonLogic/CommonLogic.h"
#include "../CommonLogic/Feast/Feast.h"
//--------------------------------------
// Server
//--------------------------------------
#include "../../Server/Server.h"
#include "../../Server/Minister/MinisterMgr.h"
#include "../../Server/Minister/Minister-Hozo.h"
#include "../../Server/Minister/Minister-Goonzu.h"
#include "../../Server/Statistics/Statistics.h"
#include "../../Server/ServerReward/ServerReward.h"
#include "../../PartyMgr/PartyMgr.h"
#include "../../PartyMgr/PartyObj.h"
#include "../CommonLogic/Msg/MsgType-Party.h"
#include "../CommonLogic/Msg/MsgType-Hunt.h"

#include "Char/CharServer/Char-Server.h"
#include "Map/FieldObject/FieldObject.h"

#include "../Common/Bullet/Bullet.h"
#include "Util/Util.h"
#include "../../Order/Order.h"
#include "../CharManager/CharManager.h"

#include "../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-DailyQuest.h"
#include "../../DBManager/GameDBManager_World/DBMsg-DailyQuest2.h"

#include "../../DBManager/GameDBManager_World/DBMsg-DailyQuest3.h"

#include "../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Village.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PostOffice.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Agriculture.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Guild.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../DBManager/GameDBManager_World/DBMsg-SoulGuard.h"

#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/Msg/MsgType-DailyQuest.h"
#include "../CommonLogic/Msg//MsgType-DailyQuest2.h"
#include "../CommonLogic/Msg//MsgType-DailyQuest3.h"
#include "../common/AutoHunting/AutoHunting.h"
#include "../common/Event/Hunting/Hunting.h"

#include "../CommonLogic/Guild/Guild.h"
#include "../CommonLogic/Guild/GuildWar.h"

#include "../CommonLogic/KoinoboryFamily/KoinoboryFamily.h"

#include "../CommonLogic/CityHall/CityHall.h"
#include "../CommonLogic/BlackArmy/BlackArmy.h"

#include "../Common/NPCManager/NPC.h"

#include "../../CommonLogic/MagicMgr/MagicMgr.h"
#include "../../CommonLogic/MsgRval-Define.h."

#include "../../../NLib/NUtil.h"
// NUtil.cpp에 선언된 변수
extern UI64	uiSec; // 시간 계산을 위한 기준 변수


#include "ITZCell.h"
#include "ITZEncrypt.h"
#include "../CommonLogic/MsgType-System.h"
#include <MsgType-Person.h>
#include <MsgType-Item.h>
#include <Msg/MsgType-ItemMall.h>
#include "Msg/MsgType-MofuMofuEvent.h"


#include "../Common/Map/MapManager/MapManager.h"

#include "../../Server/Minister/MinisterMgr.h"
#include "../../Server/Minister/Minister-Hozo.h"
#include "../../Server/Minister/Minister-Gongzo.h"
#include "Msg/MsgType-PersonalShop.h"

#include "../../Server/ServerEvent/ServerEvent-Quest.h"
//------------------------------------
// Common
//------------------------------------
#include "../../Skill/Skill.h"
#include "../../Skill/Skill-Manager.h"
#include "../../common/Item/ItemCommon/cltSetItem.h"

#include "../../Apex/ApexGoonZu.h"

#include "MsgType-Person.h"

extern cltCommonLogic* pclClient;
extern HashStringInt*  pclHashTable;

extern SI32 AttackAtbInfo[];

#ifdef _SAFE_MEMORY
NSafeTArray<SI32, MAX_CHAR_NUMBER>	cltCharCommon::CharUniqueInfo;
#else
SI32	cltCharCommon::CharUniqueInfo[MAX_CHAR_NUMBER];	
#endif


#include "../Client/ninterface/nhuntmapinfodlg/HuntMapInfoDlg.h"

#include "../../CommonLogic/HuntQuestItemMgr/HuntQuestItemMgr.h"

//========================================
// cltCharUpdateInfo
//========================================
cltCharUpdateInfo::cltCharUpdateInfo()
{
	Init();
}

void cltCharUpdateInfo::Init()
{
	bMode	= false;
	siPara1	= 0;

}

//========================================
// cltItemReserveUnitInfo
//========================================
cltItemReserveUnitInfo::cltItemReserveUnitInfo()
{
	Init();
}
void cltItemReserveUnitInfo::Init()
{
	siUnique	= 0;
	siItemNum	= 0;
	siItemPos	= -1;
}
void cltItemReserveUnitInfo::Set(cltItemReserveUnitInfo* pclinfo)
{
	siUnique	= pclinfo->siUnique;
	siItemNum	= pclinfo->siItemNum;
	siItemPos   = pclinfo->siItemPos;
}


//========================================
// cltSummonItemReserveUnitInfo
//========================================
cltSummonItemReserveUnitInfo::cltSummonItemReserveUnitInfo()
{
	Init();

}

cltSummonItemReserveUnitInfo::cltSummonItemReserveUnitInfo( SI08 siSummonIndex, SI16 siItemUnique, SI16 siItemNum, SI16 siItemPos )
{
	m_siSummonIndex	= siSummonIndex;
	m_siItemUnique	= siItemUnique;
	m_siItemNum		= siItemNum;
	m_siItemPos		= siItemPos;

}

void cltSummonItemReserveUnitInfo::Init()
{
	m_siSummonIndex	= -1;
	m_siItemUnique	= 0;
	m_siItemNum		= 0;
	m_siItemPos		= -1;

}

void cltSummonItemReserveUnitInfo::Set( cltSummonItemReserveUnitInfo* pclinfo )
{
	m_siSummonIndex	= pclinfo->m_siSummonIndex;
	m_siItemUnique	= pclinfo->m_siItemUnique;
	m_siItemNum		= pclinfo->m_siItemNum;
	m_siItemPos		= pclinfo->m_siItemPos;

}

//========================================
// cltCharSimpleVary
//========================================
cltCharSimpleVary::cltCharSimpleVary()
{
	Init();
}

void cltCharSimpleVary::Init()
{
	ZeroMemory(this, sizeof(cltCharSimpleVary));
}

//========================================
// cltCharUpdateTimer
//========================================
cltCharUpdateTimer::cltCharUpdateTimer()
{
	m_clTimer[CHAR_UPDATETIMER_TIMEMETERRATE_DB].Init(10 * 60 * 1000);		// 10분
	m_clTimer[CHAR_UPDATETIMER_TIMEMETERRATE_CLIENT].Init(20 * 1000);		// 20초
	m_clTimer[CHAR_UPDATETIMER_TRANSFORMINFO_CLIENT].Init(1* 60 * 1000);	// 1 분
	m_clTimer[CHAR_UPDATETIMER_TRANSFORM_TIME_LIMIT].Init(30 * 1000);		// 30초

	m_clTimer[CHAR_UPDATETIMER_CRYSTALITEM_DB].Init(30* 60 * 1000);			// 30분.
	m_clTimer[CHAR_UPDATETIMER_CRYSTALITEMINFO_CLIENT].Init(5* 60 * 1000);	// 5분.
	m_clTimer[CHAR_UPDATETIMER_TIREDSYSTEM_TIME_LIMIT].Init(20 * 1000);		// 40초
	m_clTimer[CHAR_UPDATETIMER_30SECOND].Init(30 * 1000);					// 30초 타이머
	m_clTimer[CHAR_UPDATETIMER_3SECOND].Init(3 * 1000);						// 3초 타이머

	m_clTimer[CHAR_UPDATETIMER_BUGCHAR_CHECK].Init(10 * 1000);				// 10초 타이머
	
}

void cltCharUpdateTimer::Init()
{
	//========================================================================================
	// 처음부터 켜지는 타이머가 아니면 여기서 Active를 시키지 않고 사용한다.
	//========================================================================================

	m_clTimer[CHAR_UPDATETIMER_TIMEMETERRATE_DB].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_TIMEMETERRATE_CLIENT].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_TRANSFORMINFO_CLIENT].SetActive(true, GetTickCount());

	m_clTimer[CHAR_UPDATETIMER_CRYSTALITEM_DB].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_CRYSTALITEMINFO_CLIENT].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_TIREDSYSTEM_TIME_LIMIT].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_30SECOND].SetActive(true, GetTickCount());
	m_clTimer[CHAR_UPDATETIMER_3SECOND].SetActive(true, GetTickCount());				// 워프용 3초 체크 타이머.

	m_clTimer[CHAR_UPDATETIMER_BUGCHAR_CHECK].SetActive(true, GetTickCount());			// 버그 캐릭터 체크용 타이머.
}


//========================================
// cltCharServer
//========================================
cltCharServer::cltCharServer() : cltCharCommon()
{
	LastReceveFromClientClock	=	0;
	dwLastCheckAutoFoodClock	=	0;

	dwLastGameGuardAuthClock	=	0;
	dwTimerClock				=	0;
	NPCGroup					=	0;


	//--------------------------------
	// Daily Quest Action Clock
	//--------------------------------
	dwDailyQuestClock			=	0;
	dwDailyQuest2Clock			=	0;
	dwDailyQuest3Clock			=	0;

	bSendSecretNCHarUniqueSwitch	= false;

	//--------------------------------
	// 이전 레벨 정보. 
	//--------------------------------
	uiLevelInfoUpdateFrame	= 0;
	clOldLevelInfo.Init();

	clSimpleVary.Init();
	m_clCharUpdateTimer.Init();

	dwLastVisitVillageClock	= 0;

	uiCSAAuth_Count	= 0;
	bWaitGameGuardClientAuth = false;  

	//---------------------------------
	// 마법 지연 시간. 
	//---------------------------------
	siMagicDelay		= 0;

	//---------------------------------
	// 이전에 선택되었던 마법 기억.
	//---------------------------------
	siOldWeaponMagic	= 0;

	//---------------------------------
	// 낚시하는 중이라면, 낚시 아이템
	//---------------------------------
	siFishingBaitItemUnique = 0;
	//-------------------------
	// 자동 낚시
	//-------------------------
	bAutoFishing = false;

	//-------------------------
	// 인첸트 100% 성공 스위치 (운영자일때만)
	//-------------------------
	bSuccessEnchant = false;

	//-------------------------
	// 잡힌 시간 체크
	//-------------------------
	dwPreCatchFishClock	= 0;
	dwSummonFishClock = 0;

	//-------------------------
	// 농사 중이라면,  획득할려는 농사 아이템
	//-------------------------d
	siFarmingItemUnique = 0;

	//-------------------------
	// 농사 임대한 마을( 임시로 )
	//-------------------------
	//siFarmingRentVillageUnique = 0;

	//-------------------------
	// 자동 농사
	//-------------------------
	bAutoFarming = false;

	//-------------------------
	// 농사 획득 아이템 개수
	//-------------------------
	siFarmingItemCount = 0;

	//-------------------------
	// 농사 주기
	//-------------------------
	dwPreGetFarmingItemClock	= 0;
	dwFarmingClock = 0;

	//-------------------------
	// 채굴
	//-------------------------
	siMiningItemUnique = 0;
	//siMiningRentVillageUnique = 0;
	bAutoMining = false;
	dwPreGetMiningItemClock = 0;
	//dwMiningClock = 0;
	//dwStartAgricultureClock = 0;
	//siLeaseLandVillage = 0;
	//uiLeaseLandExpire = 0;

	//-----------------------------
	// 생산활동 정보
	//-----------------------------
	m_pclAgriculture = NULL;

	//-----------------------------
	// 자동 회복 관련 
	//-----------------------------
	dwAutoRecoverLifeClock	= 0;	
	dwAutoRecoverManaClock	= 0;

	//-----------------------------
	// 고양이 쿠션 자동 회복 관련  Cushion
	//-----------------------------	
	dwCusionRecoverLifeClock = 0;		// 마지막으로 자동 회복이 되었던 시간. 
	dwCusionRecoverManaClock = 0;		// 마지막으로 자동 회복이 되었던 시간. 

	// PCK : 잠자는 냐옹이 쿠션 소환수 자동 회복 관련 (09.06.15)
	dwCusionRecoverSummonLifeClock = 0;		// 마지막으로 소환수 자동 회복이 되었던 시간. 
	dwCusionRecoverSummonManaClock = 0;		// 마지막으로 소환수 자동 회복이 되었던 시간.

	//KHY - 1220 - 변신시스템. - 자동회복
	dwTransFormRecoverManaClock = 0;

	// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
	uiBestGuild	= false;					

	clCharWarpInfo.Init();
	siWarpUnique	= 0;

	//----------------------------
	// 사망 관련 
	//---------------------------
	bDeathPenaltySwitch = false;
	bRequestReviveSwitch = false;

	DeathClock			= 0;
	siCharDyingDelay	= 0;

	bReadySwitch		= false;
	bFirstCellOpSwtich	= false;

	pclCharListInfo		= NULL;

	//----------------------------
	// 머릿말 
	//----------------------------
	bHeadChatSwitch		= false;		// 현재 머릿말이 설정되어 있는가?
	StringCchCopy(szHeadChatText, MAX_HEAD_CHAT_TEXT_SIZE, TEXT(""));

	//----------------------------
	// 개인상점 데이터 
	//----------------------------
	clShopData.Init();

	m_pclShopRepairData = NULL;

	//---------------------------
	// 캐릭터 모드  
	//---------------------------
	siCharMode				= 0;
	siCharModePara1			= 0;

	//---------------------------
	// 사망 모드 
	//---------------------------
	siKilledMode			= 0;
	StringCchCopy(szKillMeCharName, MAX_PLAYER_NAME, TEXT(""));

	//-------------------------
	// 제자리에서 대기 
	//-------------------------
	bStaySwitch			= false;	// 한자리에 멈춰서 있는지 여부. 

	//-------------------------
	// 플레이 시간 구하기 
	//-------------------------
	dwStartClock		= 0;
	dwInstantPlayTime	= 0;

	// 시작 시간 저장하기
	ZeroMemory(&sTimeStartTime , sizeof(_SYSTEMTIME) );

	// 로그인 했을때의 레벨
	siLoginedLevel = 0;

	//-------------------------
	// 지휘효과. 
	//-------------------------
	dwGeneralEftSetClock	= 0;

	//-------------------------
	// 채팅 입력 시간 
	//-------------------------
	dwLastChatInputClock	= 0;

	//-------------------------------------
	// 선공 방지 시간. 
	//-------------------------------------
	dwNoFirstAttackClock	= 0;
	//-------------------------------------
	// ICE 방지 시간. 
	//-------------------------------------
	dwNoIceAttackClock		= 0;
	//---------------------------------------
	// 클라이언트가 메시지 보낸 마지막 시간. 
	//---------------------------------------
	dwLastSendServerClock	= 0;

	//-------------------------------------
	// 물건 생산 
	//-------------------------------------
	bMakeItemReserveSwitch	= false;
	bMakeItemMinigameSwitch = false;
	bMakeItemNoMinigame = false ;
	bEnchantItemSwitch = false;
	bMakeItemSwitch = false ;
	bFinishEnchantItemSwitch = false;
	dwMakeItemStartClock	= 0;
	dwMakeItemDelayClock	= 0;
	siMonsterCorp			= 0 ;
	dwStartMiniGameTime = 0;
	pclReservedMakeItemData	= new cltGameMsgRequest_MakeItemInv;

	// [지연] 군주데이미션 : 미션 수행 정보 초기화
	clGoonzuDayMissionInfo.Clear();

	// 박대박 게임
	bRouletteStart = false;
	m_siBettingCount = 0;
	m_siResultCount = 0;
	dwRouletteStartClock = 0;
	dwRouletteDelayClock = 0;
	SI32 x = 0, y = 0;
	for( y = 0 ; y< 5; ++y )
	{
		m_siRandomValue[y] = 0;	// 선택될 랜덤값 0

		for( x = 0; x < 5; ++x )
		{
			m_stRouletteTable[y][x].m_bUserSelect = false;
			m_stRouletteTable[y][x].m_bCpuSelect  = false;
			m_stRouletteTable[y][x].m_bResult     = false;

			m_stRouletteTable[y][x].m_siX = 0;
			m_stRouletteTable[y][x].m_siY = 0;
			m_stRouletteTable[y][x].m_siValue = y*5 + (x + 1);
		}
	}

	//-----------------------------------
	// 종료 희망 여부 변수. 
	//-----------------------------------
	bHopeToQuitSwitch		= false;

	//----------------------------------
	// 일정 시간 경과후 종료 변수 
	//----------------------------------
	bCloseSocketSwitch		= false;
	dwCloseSocketTimer		= 0;


	//---------------------------------
	// 환경 설정
	//---------------------------------
	bWhisperChatReject = false;
	bPrivateTradeReject = false;
	bPartyInviteReject = false;
	bFriendAddReject = false;

	//---------------------------------
	// 현재 위치 충돌 체크 간격. 
	//---------------------------------
	dwLastCheckCollClock	= 0;

	//---------------------------------
	// 분신술 간격 시간 
	//---------------------------------
	dwLastClone = 0;

	//-----------------------------
	// 전송해야할 자막 종류
	//-----------------------------
	siCaptionKind = CAPTIONKIND_NEWSCHAT;

	//-----------------------------
	// 스틸 관련 
	//-----------------------------
	dwStealClock	= 0;
	siStealNum		= 0;			// 스틸한 횟수. 

	//----------------------------
	// 감옥 관련 
	//----------------------------
	dwPrisonClock	= 0;

	//-----------------------------------
	// 퀘스트를 완료하지 않아 레벨업 불가 공지 시각
	//--------------------------------------------
	dwLastLevelUpFailForQuestClock	= 0;

	//-----------------------------------
	// 공격 예약 
	//-----------------------------------
	siReservedAttackTargetID		= 0;

	//-----------------------------------
	// 소환수 처리 
	//-----------------------------------
	bIsEvolving		= false;
	bIsTradeing		= false;

	//------------------------------------
	// WeaponSkill 처리
	//----------------------------------
	bIsWeaponSkillUp = false ;

	//-----------------------------------
	// GameEvent
	//------------------------------------
	bCheckGameEvent = false ;

	//-------------------------------------
	// 무역 거래중이다.
	//-------------------------------------
	bTradeServerUsing = false ;

	//-------------------------------------
	// 버프 아이템을 먹는 중이다. 동시에 먹어서 버프가 사라지는 문제를 해결하기 위한 변수
	//-------------------------------------
	bIsNowAddBufThroughDB = false;

	//-------------------------------------
	// 가차 아이템을 뽑는 중이다. 한번에 여러번 가차를 할수 없게끔 하는 변수
	//-------------------------------------
	bNowGachaBuy = false;

	//-------------------------------------
	// 소환수를 소환중이므로 다음 소환수는 소환시키지 못하게 한다.
	//-------------------------------------
	bIsNowAddSummonThroughDB = false;

	bIsNowAddSoulGuardThroughDB				= false;
	dwLastSoulGuardActionClock				= 0;
	dwLastSoulGuardParentDeadMessageClock	= 0;

	// 그룹 처리
	siGroupUnique = 0 ;
	siGroupMember = 0 ;
	bGroupBossSwitch = FALSE ;


	//---------------------------------
	// 무기 사용술 부적 현황
	//---------------------------------
	bSwordScroll	= false;
	bSpearScroll	= false;
	bAxeScroll		= false;
	bGunScroll		= false;
	bBowScroll		= false;
	bStaffScroll	= false;
	bCannonScroll	= false;

	//---------------------------------
	// 무기 사용술 부적수 현황
	//---------------------------------
	siSwordScrollNum  = 0;
	siSpearScrollNum  = 0;
	siAxeScrollNum    = 0;
	siGunScrollNum    = 0;
	siBowScrollNum    = 0;
	siStaffScrollNum  = 0;

	//--------------------------------------------
	// 생생탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetPremium = false;
	//--------------------------------------------
	// 활성탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetCombat = false;
	//--------------------------------------------
	// 장생탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetMakeItem = false;

	bIsBulletService = false;
	bIsSummonStaminaService = false;

	//--------------------------------------------
	// 캐쉬 아이템 팔기 관련 - 중복 팔기 방지
	//--------------------------------------------
	bIsBuyCashItem = false;

	//--------------------------------------------
	// 아이템 줍고 있다.
	//--------------------------------------------
	bIsPickUpItem = false ;

	//-------------------------------------------------
	// 아이템 몰에서 아이템 받고 있다.
	//-------------------------------------------------
	bIsItemMallGetItem = false;
	//-------------------------------------------------
	// 아이템 몰에서 아이템 사거나 보내고 있다.
	//-------------------------------------------------
	bIsItemMallBuyItem = false;
	//--------------------------------------
	// 복주머니 아이템 사용중
	//--------------------------------------
	bUseBagItem = false;

	//--------------------------------------
	// 영웅 변신 아이템 사용중
	//--------------------------------------
	bUseChangeHeroItem = false ;

	//-------------------------------------
	// 마을 공성전 전적.
	//-------------------------------------
	siVillageWarKillScore = 0;

	// APEX-
	bApexLogin = false;
	// -APEX

	// 피로방지-
	bTiredSystem = false;
	uiTiredState = TIRED_STATUS_NORMAL;
	dwPlayingTime = 0;
	siTiredNotice = 0;
	lastTiredNoticedovertime = 0;

	//	dwStartMiniGame = 0;

#ifdef USE_GAME_GUARD_SERVER
	m_bCCSAuthInit				= false;
	m_siCCSAuthState			= CCSAUTH_STATE_NONE;
	m_dwCCSAuthLastActionTick	= 0;
	m_siCCSAuthCount			= 0;
#endif

	uiIDNo						= 0;
	bMakeTimeReduce				= false;

	siQuestCount				= 0;
	siServerEvent_IndunScore	= 0;

	clSummonBulletUseReserveInfo.Init();

	// 캐릭터 룰렛 결과 저장 변수
	siCharRouletteValue			= 0;
}

cltCharServer::~cltCharServer()
{
	if(pclReservedMakeItemData)
	{
		delete pclReservedMakeItemData;
		pclReservedMakeItemData = NULL;
	}

	if(pclCI)
	{
		delete pclCI;
		pclCI = NULL;
	}

	if(pclCharListInfo)
	{
		delete[] pclCharListInfo;
		pclCharListInfo = NULL;
	}

	if( m_pclAgriculture )
	{
		delete m_pclAgriculture;
		m_pclAgriculture = NULL;
	}

	if( m_pclShopRepairData )
	{
		delete m_pclShopRepairData;
		m_pclShopRepairData = NULL;
	}
}

void cltCharServer::InitCharServer()
{
	SI32 i;

#ifdef USE_GAME_GUARD_SERVER

	//clWarpCSA.Init(this, true, true);

#endif

	LastReceveFromClientClock	=	0;
	dwLastCheckAutoFoodClock	=	0;
	dwLastGameGuardAuthClock	=	0;
	dwTimerClock				=	0;
	NPCGroup					=	-1;

	bSendSecretNCHarUniqueSwitch = false;	

	//--------------------------------
	// Daily Quest Action Clock
	//--------------------------------
	dwDailyQuestClock			= 0;
	dwDailyQuest2Clock			= 0;
	dwDailyQuest3Clock			= 0;

	//---------------------------------
	// 낚시하는 중이라면, 낚시 아이템
	//---------------------------------
	siFishingBaitItemUnique = 0;

	//-------------------------
	// 자동 낚시
	//-------------------------
	bAutoFishing = false;

	//-------------------------
	// 인첸트 100% 성공 스위치 (운영자일때만)
	//-------------------------
	bSuccessEnchant = false;

	//-------------------------
	// 잡힌 시간 체크
	//-------------------------
	dwPreCatchFishClock	= 0;
	dwSummonFishClock = 0;

	//-------------------------
	// 농사 중이라면,  획득할려는 농사 아이템
	//-------------------------
	siFarmingItemUnique = 0;

	//-------------------------
	// 농사 임대한 마을( 임시로 )
	//-------------------------
	//siFarmingRentVillageUnique = 0;

	//-------------------------
	// 자동 농사
	//-------------------------
	bAutoFarming = false;

	//-------------------------
	// 농사 획득 아이템 개수
	//-------------------------
	siFarmingItemCount = 0;

	//-------------------------
	// 농사 주기
	//-------------------------
	dwPreGetFarmingItemClock	= 0;
	siFarmingActionCount = 0;

	//-------------------------
	// 채굴
	//-------------------------
	siMiningItemUnique = 0;
	//siMiningRentVillageUnique = 0;
	bAutoMining = false;
	//siMiningItemCount = 0;
	siMiningActionCount = 0;
	dwPreGetMiningItemClock = 0;


	//dwStartAgricultureClock = 0;

	//siLeaseLandVillage = 0;
	//uiLeaseLandExpire = 0;

	if( m_pclAgriculture )		m_pclAgriculture->Init();


	//--------------------------------
	// 이전 레벨 정보. 
	//--------------------------------
	uiLevelInfoUpdateFrame	= 0;
	clOldLevelInfo.Init();

	clSimpleVary.Init();
	m_clCharUpdateTimer.Init();
	dwLastVisitVillageClock	= pclClient->CurrentClock;

	uiCSAAuth_Count	= 0;
	bWaitGameGuardClientAuth = false;  

	clCharWarpInfo.Init();
	siWarpUnique	= 0;

	// 아직 클라이언트로부터 완료 신호를 받지 못했다. 
	bReadySwitch		= false;
	bFirstCellOpSwtich	= false;

	//-------------------------------------------
	// 메모리 생성 - 유저만 생성한다.
	//-------------------------------------------
	if(IsPC(CharUnique))
	{
		if(pclCharListInfo == NULL)		pclCharListInfo = new cltCharListInfo[MAX_TOTAL_CHAR_PER_USER];
	}

	// 업데이트 정보. 
	for(i = 0;i < MAX_UPDATE_SWITCH;i++)
	{
		clUpdateInfo[i].Init();
	}

	//-----------------------------
	// 자동 회복 관련 
	//-----------------------------
	dwAutoRecoverLifeClock	= pclClient->CurrentClock;
	dwAutoRecoverManaClock	= pclClient->CurrentClock;

	//-----------------------------
	// 자동 회복 관련 
	//-----------------------------
	dwCusionRecoverLifeClock = pclClient->CurrentClock;
	dwCusionRecoverManaClock = pclClient->CurrentClock;

	// PCK : 잠자는 냐옹이 쿠션 소환수 자동 회복 관련 (09.06.15)
	dwCusionRecoverSummonLifeClock = pclClient->CurrentClock;
	dwCusionRecoverSummonManaClock = pclClient->CurrentClock;

	//KHY - 1220 - 변신시스템.
	dwTransFormRecoverManaClock = pclClient->CurrentClock;

	// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
	uiBestGuild	= false;					
	//----------------------------
	// 머릿말 
	//----------------------------
	bHeadChatSwitch		= false;		// 현재 머릿말이 설정되어 있는가?
	StringCchCopy(szHeadChatText, MAX_HEAD_CHAT_TEXT_SIZE, TEXT(""));

	//----------------------------
	// 개인상점 데이터 
	//----------------------------
	clShopData.Init();

	if( m_pclShopRepairData )			m_pclShopRepairData->Init();

	//----------------------------
	// 사망 관련 
	//---------------------------
	bDeathPenaltySwitch = false;
	bRequestReviveSwitch = false;
	DeathClock			= 0;
	siCharDyingDelay	= 0;


	WaitCount			= 0;
	Wait				= 0;
	RepeatNumber		= 0;

	//---------------------------
	// 캐릭터 모드 
	//---------------------------
	siCharMode			= 0;	
	siCharModePara1		= 0;


	//---------------------------
	// 사망 모드 
	//---------------------------
	siKilledMode			= 0;
	StringCchCopy(szKillMeCharName, MAX_PLAYER_NAME, TEXT(""));


	//-------------------------
	// 제자리에서 대기 
	//-------------------------
	bStaySwitch			= false;	// 한자리에 멈춰서 있는지 여부. 

	//-------------------------
	// 플레이 시간 구하기 
	//-------------------------
	dwStartClock		= pclClient->CurrentClock;
	dwInstantPlayTime	= 0;

	sTimeStartTime		= ((cltServer*)pclClient)->sTime;

	//-------------------------
	// 로그인 시점의 레벨
	//-------------------------
	siLoginedLevel = 0;

	//-------------------------
	// 지휘효과. 
	//-------------------------
	dwGeneralEftSetClock	= 0;

	//-------------------------
	// 채팅 입력 시간 
	//-------------------------
	dwLastChatInputClock	= 0;

	//-------------------------------------
	// 선공 방지 시간. 
	//-------------------------------------
	dwNoFirstAttackClock	= 0;
	//-------------------------------------
	// ICE 방지 시간. 
	//-------------------------------------
	dwNoIceAttackClock		= 0;

	//---------------------------------------
	// 클라이언트가 메시지 보낸 마지막 시간. 
	//---------------------------------------
	dwLastSendServerClock	= 0;
	//-------------------------------------
	// 물건 생산 
	//-------------------------------------
	bMakeItemReserveSwitch	= false;
	bMakeItemMinigameSwitch = false;
	bMakeItemNoMinigame = false ;
	bEnchantItemSwitch = false;
	bMakeItemSwitch = false ;
	bFinishEnchantItemSwitch = false;
	dwMakeItemStartClock	= 0;
	dwMakeItemDelayClock	= 0;
	siMonsterCorp			= 0;
	dwStartMiniGameTime = 0;
	pclReservedMakeItemData->Init();

	// [지연] 군주데이미션 : 미션 수행 정보 초기화
	clGoonzuDayMissionInfo.Clear();

	// 박대박 게임
	bRouletteStart = false;
	m_siBettingCount = 0;
	m_siResultCount = 0;
	dwRouletteStartClock = 0;
	dwRouletteDelayClock = 0;
	SI32 x = 0, y = 0;
	for( y = 0 ; y< 5; ++y )
	{
		m_siRandomValue[y] = 0;	// 선택될 랜덤값 0

		for( x = 0; x < 5; ++x )
		{
			m_stRouletteTable[y][x].m_bUserSelect = false;
			m_stRouletteTable[y][x].m_bCpuSelect  = false;
			m_stRouletteTable[y][x].m_bResult     = false;

			m_stRouletteTable[y][x].m_siX = 0;
			m_stRouletteTable[y][x].m_siY = 0;
			m_stRouletteTable[y][x].m_siValue = y*5 + (x + 1);
		}
	}

	//-----------------------------------
	// 종료 희망 여부 변수. 
	//-----------------------------------
	bHopeToQuitSwitch		= false;

	//----------------------------------
	// 일정 시간 경과후 종료 변수 
	//----------------------------------
	bCloseSocketSwitch		= false;
	dwCloseSocketTimer		= 0;


	//---------------------------------
	// 아이템 사용 예약. 
	//---------------------------------
	clItemUseReserveInfo.Init();

	//---------------------------------
	// 환경 설정
	//---------------------------------
	bWhisperChatReject = false;
	bPrivateTradeReject = false;
	bPartyInviteReject = false;
	bFriendAddReject = false;

	//---------------------------------
	// 현재 위치 충돌 체크 간격. 
	//---------------------------------
	dwLastCheckCollClock	= 0;

	//---------------------------------
	// 분신술 간격 시간 : 약간 시간을 땡겨서 일찍 나올수 있도록 한다.
	//---------------------------------
	dwLastClone = pclClient->CurrentClock-25000;

	//-----------------------------
	// 전송해야할 자막 종류
	//-----------------------------
	siCaptionKind = CAPTIONKIND_NEWSCHAT;

	//-----------------------------
	// 스틸 관련 
	//-----------------------------
	dwStealClock	= 0;	
	siStealNum		= 0;			// 스틸한 횟수. 

	//----------------------------
	// 감옥 관련 
	//----------------------------
	dwPrisonClock	= 0;

	//-----------------------------------
	// 퀘스트를 완료하지 않아 레벨업 불가 공지 시각
	//--------------------------------------------
	dwLastLevelUpFailForQuestClock	= 0;

	//-----------------------------------
	// 공격 예약 
	//-----------------------------------
	siReservedAttackTargetID		= 0;

	//-----------------------------------
	// 소환수 처리 
	//-----------------------------------
	bIsEvolving		= false;
	bIsTradeing		= false;

	//------------------------------------
	// WeaponSkill 처리
	//----------------------------------
	bIsWeaponSkillUp = false ;

	//----------------------------------
	// GameEvent
	//----------------------------------
	bCheckGameEvent = false ;

	//-------------------------------------
	// 무역 거래중이다.
	//-------------------------------------
	bTradeServerUsing = false ;

	//-------------------------------------
	// 버프 아이템을 먹는 중이다. 동시에 먹어서 버프가 사라지는 문제를 해결하기 위한 변수
	//-------------------------------------
	bIsNowAddBufThroughDB = false;

	//-------------------------------------
	// 가차 아이템을 뽑는 중이다. 한번에 여러번 가차를 할수 없게끔 하는 변수
	//-------------------------------------
	bNowGachaBuy = false;

	//-------------------------------------
	// 소환수를 소환중이므로 다음 소환수는 소환시키지 못하게 한다.
	//-------------------------------------
	bIsNowAddSummonThroughDB = false;

	bIsNowAddSoulGuardThroughDB				= false;
	dwLastSoulGuardActionClock				= 0;
	dwLastSoulGuardParentDeadMessageClock	= 0;

	// 그룹 처리
	siGroupUnique = 0 ;
	siGroupMember = 0 ;
	bGroupBossSwitch = FALSE ;

	//---------------------------------
	// 무기 사용술 부적 현황
	//---------------------------------
	bSwordScroll	= false;
	bSpearScroll	= false;
	bAxeScroll		= false;
	bGunScroll		= false;
	bBowScroll		= false;
	bStaffScroll	= false;
	bCannonScroll	= false;

	//---------------------------------
	// 무기 사용술 부적수 현황
	//---------------------------------
	siSwordScrollNum  = 0;
	siSpearScrollNum  = 0;
	siAxeScrollNum    = 0;
	siGunScrollNum    = 0;
	siBowScrollNum    = 0;
	siStaffScrollNum  = 0;

	//--------------------------------------------
	// 생생탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetPremium = false;
	//--------------------------------------------
	// 활성탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetCombat = false;
	//--------------------------------------------
	// 장생탕 관련 - 중복해서 사용을 막는다.
	//--------------------------------------------
	bIsSetMakeItem = false;

	bIsBulletService = false;
	bIsSummonStaminaService = false;

	//--------------------------------------------
	// 캐쉬 아이템 팔기 관련 - 중복 팔기 방지
	//--------------------------------------------
	bIsBuyCashItem = false;

	//--------------------------------------------
	// 아이템 줍고 있다.
	//--------------------------------------------
	bIsPickUpItem = false ;

	//-------------------------------------------------
	// 아이템 몰에서 아이템 받고 있다.
	//-------------------------------------------------
	bIsItemMallGetItem = false;
	//-------------------------------------------------
	// 아이템 몰에서 아이템 사거나 보내고 있다.
	//-------------------------------------------------
	bIsItemMallBuyItem = false;
	//--------------------------------------
	// 복주머니 아이템 사용중
	//--------------------------------------
	bUseBagItem = false;

	//--------------------------------------
	// 영웅 변신 아이템 사용중
	//--------------------------------------
	bUseChangeHeroItem = false ;

	//-------------------------------------
	// 마을 공성전 전적.
	//-------------------------------------
	siVillageWarKillScore	= 0;

	bMakeTimeReduce			= false;

	//-------------------------------------
	// 퀘스트용 카운트 증가값
	//-------------------------------------
	siQuestCount			= 0;

	//-------------------------------------
	// 서버 이벤트 인던 점수 증가용
	//-------------------------------------
	siServerEvent_IndunScore	= 0;

	// 캐릭터 룰렛 결과 저장 변수
	siCharRouletteValue			= 0;

	//[지연] : 2010신년이벤트 npc카인드 배열을 초기화
	InitArray_RemoveUnLuckQuestNPC();
}

//-------------------------------------------
// Rank 관리 
//-------------------------------------------
BOOL cltCharServer::SetRank(cltSimpleRank* pclrank)
{
	pclCI->clCharRank.Set(pclrank);
	return  TRUE;
}

//----------------------------------
// 셀관련 작업.
//----------------------------------
//캐릭터가 처음 만들어 졌을때 셀에 등록및 셀의 정보 요청과 같은 임무를 수행한다. 
void cltCharServer::CellAction()
{
	// 사용자 캐릭터인 경우, 
	// 클라이언트가 준비되지 않았으면 처리할 수 없다. 
	if(GetSession())
	{
		if(bReadySwitch == false)return ;
	}

	// 이 캐릭터 일생에 한번만 작동하도록 한다. 
	if(bFirstCellOpSwtich == true)return;
	bFirstCellOpSwtich	= true;

	// 처음 맵에 등장할때 주변에 자신의 정보를 통보하고 주변의 정보를 얻어온다
	pclClient->pclMapManager->m_world.GetMap( GetMapIndex() )->MoveChar( GetX(), GetY(), this, false );

	// 저장된 쪽지가 있다면 요청한다. 
	if(GetSession())
	{
		sDBRequest_PopLetter clMsg(GetID(), pclCI->GetPersonID());
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if(pclClient->siServiceArea == ConstServiceArea_Japan)
		{
			sDBRequest_PopAccountLetter clMsg2( GetID() , pclCI->clBI.szAccountID );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);
		}
	}

}

// 셀 내에서의 정보를 삭제한다. 
void cltCharServer::DeleteInCell()
{
	ITZCell *pCurrentCell = GetCell();
	if( pCurrentCell)
	{

		ITZMap* pCellMap = (ITZMap*)pclClient->pclMapManager->m_world.GetMap(GetMapIndex());

		if(pCellMap)
		{
			// 삭제 메시지를 보낼 셀들을 얻는다 
			pCellMap->SetCellList( pCurrentCell, NULL );

			// 삭제 메시지를 보낸다
			pCellMap->SendPersonLeaveMsgToOthers(this);

			// 셀에서 캐릭터를 삭제한다 
			GetCell()->DelPerson( this );
		}
	}

}

// 찍을 위치를 계산한다. 
void cltCharServer::CalculateRealXY()
{

	SI32 mapcenterx = 0, mapcentery = 0;
	pclMap->GetXYDotFromXYCord(GetX(), GetY(), mapcenterx, mapcentery);

	// 캐릭터의 중심을 구한다
	siCenterX = mapcenterx;

	siCenterY = mapcentery;
}

void cltCharServer::GetBottomPoint(cltPos* pclpos)
{
	pclpos->siX = siCenterX;
	pclpos->siY = siCenterY;
}

// 소환수가 자동 회복을 한다.
void cltCharServer::SummonAutoHeal()
{
	if ( ( pclClient->GetFrame() / CHAR_ACTION_INTERVAL_FRAME ) % 3 != 0 ) return ; // 10frame당 한번만 먹는다.

	SI32 parentid = GetSummonParentID();
	SI32 ItemUnique = ITEMUNIQUE(2675) ; // 칠기탕

	if ( pclCM->IsValidID( parentid ) == FALSE ) return ;
	if ( pclCM->IsAlive( parentid ) == FALSE ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[parentid];
	if ( pclchar == NULL ) return ;

	cltSummonInfo* pclSummonInfo = &pclchar->pclCI->clSummonInfo ;
	if ( pclSummonInfo == NULL ) return ;
	if ( pclSummonInfo->bAutoHeal == false ) return ;

	if ( pclCI->clIP.GetLife() <= 0 ) return ;

	if ( pclchar->pclCI->clCharItem.GetItemNum(ItemUnique) <= 0 )
	{
		ItemUnique = ITEMUNIQUE(2680) ; // 보화탕
	}

	if ( pclchar->pclCI->clCharItem.GetItemNum(ItemUnique) <= 0 )
	{
		ItemUnique = ITEMUNIQUE(2681) ; // 환상의 소환수 회복제

		if ( pclchar->pclCI->clCharItem.GetItemNum(ItemUnique) <= 0 )
			return ;
	}

	SI32 pos = pclchar->pclCI->clCharItem.GetItemPos(ItemUnique);
	if (pos < 0) return ;

	if ( pclSummonInfo->siSelectAutoHeal < 0 || pclSummonInfo->siSelectAutoHeal > 2 ) return ;

	SI32 percent = 30 ;
	switch(pclchar->pclCI->clSummonInfo.siSelectAutoHeal)
	{
	case 0: percent = 30 ; break;
	case 1: percent = 50 ; break;
	case 2: percent = 70 ; break;
	default: return ;
	}

	if ( pclCI->clIP.GetLife() < ( clPB.GetMaxLife() * percent ) / 100 )
	{
		cltItem clitem;
		clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos]);
		clitem.SetItemNum(1);
		pclchar->UseItem(clitem);

		while( pclchar->clItemUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, pos) == false )
		{
			pclchar->ItemUseReserveAction();
		}

		cltItem *pclFrom = &pclchar->pclCI->clCharItem.clItem[ pos ];

		// 클라이언트로 업데이트 된 정보를 보낸다. 
		if( pclFrom->siItemNum == 1 )
		{
			pclchar->ItemUseReserveAction();
		}
		// pclchar->ItemUseReserveAction(); 밑에 있어야 한다. 
		// 그렇지 않으면 인벤에서 물품의 위치를 찾을 수 없다.!
		pclFrom->Decrease(1);

		// 클라이언트로 사용후 정보를 보낸다. 
		cltGameMsgResponse_PersonItemInfo clinfo( pos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// 소환수가 주인을 따라가게 한다. 
void cltCharServer::SummonFollowHost()
{
	SI32 CharParentID = GetSummonParentID();

	if(pclCM->IsValidID(CharParentID)==FALSE)
	{
		// 주인을 잃어버렸따. - 제거해야한다.
		return ;
	}

	if(pclCM->IsAlive(CharParentID) == false)return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[CharParentID];

	if ( pclchar->siSelectedCharIndex == GetSummonIndex() ) return ;

	SI32 length = max( TABS(pclchar->GetX() - GetX()) , TABS(pclchar->GetY() - GetY()) );
	SI32 xvary = 1 - (rand() % 3);
	SI32 yvary = 1 - (rand() % 3);
	SI32 x, y;

	bool bfollowswitch = false;

	//----------------------------------------
	// 소유주의 속도에 맞추어 이동하도록 한다.
	//----------------------------------------
	SI32 siNewSummonSpeed = pclCM->CR[ CharParentID ]->clPB.TotalMoveSpeed;	
	if(clPB.TotalMoveSpeed!= siNewSummonSpeed )
	{
		clPB.TotalMoveSpeed = siNewSummonSpeed;
	}

	// 같은 맵에 있으면 따라가고 다른 맵으로 가면 Warp한다.
	if(GetMapIndex() == pclchar->GetMapIndex())
	{
		if(length >= 12)			// 큰범위가 벌어지면 warp한다.
		{
			if(pclchar->pclMap->FindEmptyAreaForCharLocate(GetKind(), pclchar->GetX()+xvary, pclchar->GetY()+yvary, 20, &x, &y, true) == true)
			{
				cltWarpInfo clinfo(true, pclchar->GetMapIndex(), false, false, x, y, -1, -1);
				clCharWarpInfo.Set(&clinfo);
				Warp();
				bfollowswitch = true;
			}
		}
		else if(length >= 4)	// 일정거리가 벌어지면 따라간다.
		{
			// 정지, 이동 중이거나 거리가 지나치게 확대되어 있다면, 
			if(GetCurrentOrder() == ORDER_WAIT || GetCurrentOrder() == ORDER_MOVE || length >= 8)
			{
				bfollowswitch = true;
				OrderMove(siID, pclchar->GetX() + xvary, pclchar->GetY() + yvary, BY_PLAYER);

				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_MOVE(&clOrderDataInfo, pclchar->GetX() + xvary, pclchar->GetY() + yvary, BY_PLAYER) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					SendNeighbourMsg(&clMsg, true);
				}
			}
		}
	}
	else		// 같은 맵에 있지 않으면 warp한다.
	{
		if(pclchar->pclMap->FindEmptyAreaForCharLocate(GetKind(), pclchar->GetX()+xvary, pclchar->GetY()+yvary, 20, &x, &y, true) == true)
		{
			bool bForceSwitch = false;

			// 바닥에 이벤트 타일이 있는곳으로 캐릭터가 이동했다면, 소환수도 강제이동을 시킨다.
			cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(pclchar->GetMapIndex());
			if(pclmap != NULL)
			{
				SI32 siColl = pclmap->CalcCollInfo(pclchar->GetX(), pclchar->GetY());
				if(siColl & BLOCK_EVENT4 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6)
				{
					bForceSwitch = true;
					x = pclchar->GetX();
					y = pclchar->GetY();
				}
			}

			// 이동
			cltWarpInfo clinfo(true, pclchar->GetMapIndex(), bForceSwitch, false, x, y, -1, -1);
			clCharWarpInfo.Set(&clinfo);
			Warp();
			bfollowswitch = true;
		}
	}

	// 주인을 따라가는 모드가 아니라면. 
	if(bfollowswitch == false)
	{
		// 소환수의 공격속성이 적극적인 공격이어야만 공격을 수행한다.
		cltSummon	*pclSummon = pclchar->pclCI->clSummonInfo.GetSummon( GetSummonIndex() );
		if(pclSummon && pclSummon->siAttackType == SUMMON_ATTACKTYPE_ACTIVE)
		{
			// 주인이 공격중인 캐릭터가 있다면, 공격한다 
			SI16 attackid = pclCM->CR[CharParentID]->clAttackTarget.GetAttackID();
			// 타겟이 생존해 있어야 하며, 
			if(pclCM->IsAlive(attackid))
			{
				// 현재 소환수가 전투중이면 굳이 주인의 적을 공격할 필요는 없다.(비효율적)
				if(GetCurrentOrder() != ORDER_ATTACK)
				{
					// 소환수 자신은 생존해 있어야 하고 현재 공격중인 적과 새로운 적이 일치하지 않아야 한다. 
					if(pclCM->IsAlive(GetID()) == TRUE && clAttackTarget.GetAttackID() != attackid)
					{
						// 서버에서 공격하도록 한다. 
						OrderAttack(GetID(), attackid, BY_PLAYER);

						cltOrderDataInfo clOrderDataInfo;
						if( pclClient->pclOrderManager->MakeOrder_ATTACK(&clOrderDataInfo, attackid, BY_PLAYER) == true)
						{
							cltOrderData clOrderData;
							clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

							cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
							SendNeighbourMsg(&clMsg, true);
						}
					}
				}

			}
		}
	}

}

void cltCharServer::SoulGuardFollowHost( void )
{
	if ( FALSE == pclCM->IsAlive(GetID()) )
	{
		return;
	}

	SI32 siParentCharID = GetSoulGuardParentCharID();
	if ( false == pclCM->IsValidID(siParentCharID) )
	{
		// 주인 아이디가 이상하다 이때는 ??
		if ( 0 < GetLife() )
		{
			SetLife( 0 ); // 생명력을 0으로 만든다
		}
		
		return;
	}

	// 죽었으면 리턴
	if ( FALSE == pclCM->IsAlive(siParentCharID) )
	{
		// 수호정령 체팅 메시지를 보내고
		SendSoulGuardParentDeadMessage();

		return;
	}

	cltCharServer* pclParent = pclCM->GetCharServer( siParentCharID );
	if ( NULL == pclParent )
	{
		return;
	}

	SI32 siParentX		= pclParent->GetX();
	SI32 siParentY		= pclParent->GetY();

	SI32 siXVary		= 1 - (rand() % 3);
	SI32 siYVary		= 1 - (rand() % 3);

	SI32 siParentAddX	= siParentX + siXVary;
	SI32 siParentAddY	= siParentY + siYVary;

	SI32 siLength		= max( TABS(siParentX - GetX()) , TABS(siParentY - GetY()) );

	SI32 siX			= 0;
	SI32 siY			= 0;

	//----------------------------------------
	// 소유주의 속도에 맞추어 이동하도록 한다.
	//----------------------------------------
	SI32 siHostSpeed = pclParent->clPB.TotalMoveSpeed;	
	if ( siHostSpeed != clPB.TotalMoveSpeed )
	{
		clPB.TotalMoveSpeed = siHostSpeed;
	}

	// 같은 맵에 있을 경우
	if ( GetMapIndex() == pclParent->GetMapIndex() )
	{
		// 거리가 너무 멀다면 캐릭터에게 워프시킨다
		if ( 12 <= siLength )
		{
			if ( true == pclParent->pclMap->FindEmptyAreaForCharLocate(GetKind(), siParentAddX, siParentAddY, 20, &siX, &siY, true) == true)
			{
				cltWarpInfo clinfo(true, pclParent->GetMapIndex(), false, false, siX, siY, -1, -1);
				clCharWarpInfo.Set(&clinfo);
				Warp();
			}
		}
		// 일정거리 이상은 그냥 따라간다
		else if ( 2 <= siLength )
		{
			OrderMove( GetID(), siParentAddX, siParentAddY, BY_PLAYER );

			cltOrderDataInfo clOrderDataInfo;
			if( pclClient->pclOrderManager->MakeOrder_MOVE(&clOrderDataInfo, siParentAddX, siParentAddY, BY_PLAYER) == true)
			{
				cltOrderData clOrderData;
				clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

				cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
				SendNeighbourMsg(&clMsg, true);
			}
		}
	}
	// 다른 맵일 경우
	else
	{
		if ( true == pclParent->pclMap->FindEmptyAreaForCharLocate(GetKind(), siParentAddX, siParentAddY, 20, &siX, &siY, true) )
		{
			bool bForceSwitch = false;

			// 바닥에 이벤트 타일이 있는곳으로 캐릭터가 이동했다면
			cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer( pclParent->GetMapIndex() );
			if(pclmap != NULL)
			{
				SI32 siColl = pclmap->CalcCollInfo( siParentX, siParentY );
				if(siColl & BLOCK_EVENT4 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6)
				{
					bForceSwitch = true;
					siX = siParentX;
					siY = siParentY;
				}
			}

			// 이동
			cltWarpInfo clinfo( true, pclParent->GetMapIndex(), bForceSwitch, false, siX, siY, -1, -1 );
			clCharWarpInfo.Set(&clinfo);
			Warp();
		}

	}

}

void cltCharServer::CharServerAction_NPC()
{
	if(GetMana() < clPB.GetMaxMana() && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)
	{
		pclCI->clIP.IncreaseMana(2);
	}


	//=======================================================
	// LIFE TIMER
	//=======================================================
	// 생존 시간이 정해져 있는 캐릭터인 경우, 시간 만료시 사망. 
	if(dwTimerClock)
	{
		SI32 NpcKind = GetKind()	;
		// 30초 후 도마돈 주거.
		SI32 siMonsterLifeTime = 30000;

		if( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER")) )
		{
			siMonsterLifeTime = 30000;	
		}
		// [추가 : 보스 와일드 보어가 죽도록 한다. 황진성 2007. 9. 18]
		else if( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDBOARBOSS")))
		{
			siMonsterLifeTime = 1800000;	
		}
		// [추가 : 추수 감사절 이벤트. 칠면조가 3시간 후에 죽도록 한다. 황진성 2007. 11. 12]
		else if(  NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_TURKEY")))
		{
			siMonsterLifeTime = 10800000;	
		}
		// [설날 이벤트 : 2008.01.10 김영훈 추가 - 카이트라쿤 50분뒤 죽는다]
		else if( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_KITERACCOON")) )
		{
			SYSTEMTIME sTime;
			GetLocalTime( &sTime );

			if ( pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_RaccoonTime"), &sTime ) == true )
			{
				siMonsterLifeTime = 3000000;
			}
		}
		// 골든위크 이벤트 : 보이노리코 패밀리는 50분동안 살아있는다.
		else if( NpcKind == pclClient->pclKoinoboryFamilyManager->GetKoinoboryRedKind() ||
			NpcKind == pclClient->pclKoinoboryFamilyManager->GetKoinoboryBlueKind() ||
			NpcKind == pclClient->pclKoinoboryFamilyManager->GetKoinoboryYellowKind() )
		{
			siMonsterLifeTime = 50 * 60 * 1000;
		}
		// [진성] 추석 이벤트. 달, 우주토끼 30분동안만 살기. => 2008-8-7
		else if (	 NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_MOON"))	
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_COSMOSRABBIT2")))
		{
			siMonsterLifeTime = 30 * 60 * 1000;
		}
		else if( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENPC")) )// 할로윈 이벤트 NPC 나와서 30분이후 사라짐
		{
			siMonsterLifeTime = 30 * 60 * 1000;
		}
		else if ( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_QUESTEMPERORMASTER")) ) // 퀘스트 황재의 영혼(60분후 사라짐)
		{
			siMonsterLifeTime = 3600000; //60 * 60 * 1000;
		}
		// 보물찾기 이벤트 로 나온 엔피씨 1분뒤 죽여 버린다.
		else if ( NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGHIRO")) 
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGJEAN")) 
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGMERIEL"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGCLARA"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGJEAN"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGCLARA"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGMERIEL"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))
			|| NpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))		) 
		{
			siMonsterLifeTime = 10000;
		}
		else
		{
			siMonsterLifeTime = 30000;
		}

		if ( clIdentity.siIdentity == IDENTITY_TREASURE_EVENT )	// 만약 트레저 이벤트 몬스터이고 위의 몬스터가 아닐 경우에는 모두 생존 시간 10분
		{
			if ( NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGHIRO")) 
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGJEAN")) 
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGMERIEL"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGCLARA"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGJEAN"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGCLARA"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGMERIEL"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))
				|| NpcKind != pclClient->GetUniqueFromHash(TEXT("KIND_BLESSINGSPARKY"))	)
			{
				siMonsterLifeTime = 10 * 60 * 1000;	// 10분만 살아 있게 한다.
			}
		}
		else if ( clIdentity.siIdentity == IDENTITY_SOULGUARD_SUMMONPUMKIN )	// 정령이뽑은 소환수 는 20초만 살아 있는다
		{
			siMonsterLifeTime = 20 * 1000;	// 10분만 살아 있게 한다.
		}
		// 라쿤 피하기 이벤트 플레이할떄 아니면 해당 몬스터들을 다 죽여 버리기 위해서 
		else if ( clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT )	// 정령이뽑은 소환수 는 20초만 살아 있는다
		{
			if(pclClient->pclRacoonDodgeEventMgr->GetStep() != EVENTSTEP_PLAY )
			{
				siMonsterLifeTime= 1	;
			}
			else
			{
				siMonsterLifeTime = 1000000 ;	// 바로 죽인다
			}
		}

		
		if(TABS(pclClient->CurrentClock - dwTimerClock) >= siMonsterLifeTime)
		{
			cltGameMsgResponse_IncLife clInfo(GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_TIMEOUT);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
			SendNeighbourMsg(&clMsg, true);

			SetLife(0);
		}
	}

	//=======================================================
	// SELF CLONE
	//=======================================================
	// 스스로 분신하는 놈이라면 시간이 설정되어 있다면 
	if(IsAtb(ATB_CLONE) && clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)
	{
		// 60 초간격으로 분신한다.  (45 ~ 74초 사이에 )
		if(TABS(pclClient->CurrentClock - dwLastClone) >= (45000+rand()%30))
		{

			SI32 siCloneX, siCloneY;
			cltServer* pclserver = (cltServer*)pclClient;
			if(pclMap->FindEmptyAreaForCharLocate(GetKind(), GetX(), GetY(), 20, &siCloneX, &siCloneY, true) == true)
			{
				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

				SI32 level = pclCI->clIP.GetLevel();
				//if ( level <= 0 || level > MAX_LEVEL ) level = 1 ;
				if ( level <= 0 ) level = 1 ;

				SI32 siCloneChar = pclserver->SetNPCChar(GetKind(), pclCI->clBI.siHomeVillage, NULL, level, 0, siCloneX, siCloneY, GetMapIndex(), NPCITEMMODE_NONE, &clinnerstatus );
				if(pclCM->IsValidID(siCloneChar))
				{
					// 복제의 생명시간을 위해 현재의 시간을 설정한다.
					((cltCharServer*)(pclCM->CR[ siCloneChar ]))->dwTimerClock = pclserver->CurrentClock;
					((cltCharServer*)(pclCM->CR[ siCloneChar ]))->clInnerStatus.SetStatus(INNERSTATUS_CLONE);

					dwLastClone = pclClient->CurrentClock;
				}
			}
		}
	}
}

void cltCharServer::CharServerAction_Summon()
{
	cltCharServer* pclParentChar = pclCM->GetCharServer( GetSummonParentID() );
	if( pclParentChar )
	{
		if (TABS(pclClient->GetFrame() - uiStaminaFrame) > 1200)
		{
			SI32 amt = 0;

			if (pclKI->siSummonRank > 0)
			{
				// PCK : ATB_SUMMONSTAMINASTATIC이 있으면 기본 소환수 스태미너감소량을 적용시킨다. (08.07.18)
				cltKindInfo* pclKindInfo = NULL;
				if( pclClient->pclKindInfoSet->IsValidKind(GetKind()) )	{	pclKindInfo = pclClient->pclKindInfoSet->pclSummonKI[GetKind()];	}				

				if (pclKindInfo && pclKindInfo->IsAtb(ATB_SUMMONSTAMINASTATIC) == TRUE)
				{
					amt = SUMMON_DECREASESTAMINA_AMT;
				}
				else
				{
					// 소모되는 스태미너의 양을 구한다.
					amt =  SUMMON_DECREASESTAMINA_AMT - (pclKI->siSummonRank / 5) ;

					// 소모되는 스태미너의 양이 0보다 작아 지면 1로 고정시킨다.
					if(amt <= 0) { amt = 1; }
				}
			}

			if (clPB.pclIP->GetLuk() > amt)
			{
				// cyj 지난 시간만큼 스태미너를 깎아준다 
				// tys 마을 안에 있거나 경복궁 안에 있으면 스태미너 깎지 않음
				// 소환수 스테미너 서비스 이용시 안 줌
				if( pclParentChar->GetCurrentVillageUnique() > 0					|| 
					pclParentChar->GetMapIndex() == MAPINDEX_PALACE					||
					pclParentChar->GetMapIndex() == MAPINDEX_TRADINGPORT			||
					pclParentChar->GetMapIndex() == MAPINDEX_MAINFIELD				||
					pclParentChar->GetMapIndex() == MAPINDEX_PRIVATEMARKETAREA		||	// [영훈] 개인상점지역 : 소환수 스테미너 감소 없음
					pclParentChar->GetMapIndex() == MAPINDEX_PARTYHALL_1			||	// 파티홀 지역에서는 소환수 스테미너 감소 없음
					pclParentChar->GetMapIndex() == MAPINDEX_PARTYHALL_2			||
					pclParentChar->GetMapIndex() == MAPINDEX_PARTYHALL_3			||
					pclParentChar->GetMapIndex() == MAPINDEX_PARTYHALL_4			||
					pclParentChar->GetMapIndex() == MAPINDEX_PARTYHALL_5			||
					pclParentChar->GetMapIndex() == MAPINDEX_FESTIVAL				||
					pclParentChar->pclCI->clBI.bSummonStaminaService				||
					pclParentChar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER )	)
				{
					//if( false == pclParentChar->pclCI->clBI.bSummonStaminaService )
					{
						// [진성] 소환수 변신. 
						if( pclClient->IsCountrySwitch( Switch_SummonTramsform ) ) 
						{
							// 변신을 했다면
							if( pclParentChar->pclCI->clSummonInfo.IsSummonTranform( GetSummonIndex() ) )
							{
								TransformSummonStaminaDown( pclParentChar, amt );
							}
						}
					}
				}
				else
				{
					// [진성] 소환수 변신.
					if( pclClient->IsCountrySwitch( Switch_SummonTramsform ) ) 
					{
						// 변신을 했다면
                        if( pclParentChar->pclCI->clSummonInfo.IsSummonTranform( GetSummonIndex() ) )
						{
							TransformSummonStaminaDown( pclParentChar, amt );

							amt = 0;	// 기본 스테미너는 줄지 않는다.
						}
						else
						{
							TransformSummonStaminaUp( pclParentChar, amt );
						}
					}					
					
					// 기본 스테미너.
					clPB.clTotalBA.SetLuk( clPB.pclIP->DecreaseLuk(amt) );
				}
			}
			else
			{
				clPB.pclIP->SetLuk( 0 );
				clPB.clTotalBA.SetLuk( clPB.pclIP->GetLuk() );

				if( pclParentChar->GetLife() > 0 )
				{
					cltServer *pclserver = (cltServer*)pclClient;

					cltSummon *pclSummon = pclParentChar->pclCI->clSummonInfo.GetSummon(GetSummonIndex());

					pclSummon->siTakeInMinute = pclClient->GetMinuteFromsTime(pclserver->sTime);

					//---------------------------------------------
					// DB에 소환수를 설정한다.
					//---------------------------------------------
					cltSummon clSummon;
					pclParentChar->SendDBSummon(SETSUMMON_REASON_UPDATE, GetSummonIndex());

					clSummon.Set(pclSummon);
					clSummon.siStatus = SUMMON_STATUS_TAKEIN;

					pclParentChar->SendDBSummon(SETSUMMON_REASON_TAKEIN, GetSummonIndex(), &clSummon);

					((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMON_WASTEALLSTAMINA,  0, 0, GetSummonParentID() );

					cltGameMsgResponse_ServerTime clTime(pclserver->sTime);
					cltMsg clMsg(GAMEMSG_RESPONSE_SERVERTIME, sizeof(clTime), (BYTE*)&clTime);

					pclParentChar->SendNetMsg((sPacketHeader*)&clMsg);

				}
			}

			// 소환수라면 업데이트 시켜준다.
			if( pclParentChar->GetLife() > 0 )
			{
				pclParentChar->SetUpdateSwitch(UPDATE_SUMMON, true, 0);
			}

			uiStaminaFrame = pclClient->GetFrame();

		}

		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_CRYSTALITEM_DB].IsTimed(GetTickCount()) ) // 30분.
		{
			SendDBCrystalDurabilityForSummon();
		}

		//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 내구도 client로 저장   - 일단 5분. - 안에서 1% 일때만 계산함으로
		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_CRYSTALITEMINFO_CLIENT].IsTimed(GetTickCount()) ) // 5분.
		{			
			SendClientCrystalDurabilityForSummon();
		}			


	}

}

void cltCharServer::CharServerAction_SoulGuard()
{
	// 1분 간격으로 된다
	if ( TABS(pclClient->CurrentClock-dwLastSoulGuardActionClock) < 60000 )
	{
		return;
	}

	dwLastSoulGuardActionClock = pclClient->CurrentClock;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	SI32 siParentCharID = GetSoulGuardParentCharID();
	if ( false == pclCM->IsValidID(siParentCharID) )
	{
		return;
	}

	// 죽었으면 리턴
	if ( FALSE == pclCM->IsAlive(siParentCharID) )
	{
		return;
	}

	cltCharServer* pclParent = pclCM->GetCharServer( siParentCharID );
	if ( NULL == pclParent )
	{
		return;
	}

	//---------------------------------------------------------------
	// 수명 체크를 통해 수호정령을 없앤다
	//---------------------------------------------------------------

	SI32 siGetLimitDateVary = pclParent->pclSoulGuard->GetLimitDateVary();
	
	// 무한 수명이다 그냥 리턴
	if ( siGetLimitDateVary == MAX_SI32 )
	{
		return;
	}

	// 아직 수명이 남아있다면 그냥 리턴
	if ( siGetLimitDateVary > pclserver->pclTime->clDate.GetDateVary() )
	{
		return;
	}

	///////////////////////////////////////////////////////////////////
	// 수호정령이 죽음
	///////////////////////////////////////////////////////////////////

	// 이미 수호정령 죽는 처리를 했다면 리턴
	if ( SOULGUARD_STATUS_DEAD == pclParent->pclSoulGuard->GetStatus() )
	{
		return;
	}

	// 우선 죽었다고 명시해 주고
	pclParent->pclSoulGuard->SetStatus( SOULGUARD_STATUS_DEAD );

	// 에너지를 0으로 설정해서 죽는 모션이 나타나게 한다
	SetLife( 0 );

	// 이웃들에게 죽는다는 체팅 메시지를 보낸다
	NTCHARString128	strMessage	= GetTxtFromMgr(30248);
	NTCHARString64	strName		= GetTxtFromMgr(30146);

	cltGameMsgResponse_Chat clChat( GetCharUnique(), CHATMODE_NORMAL, strName, strMessage );
	cltMsg clChatMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);
	SendNeighbourMsg(&clChatMsg, true);

	cltGameMsgResponse_IncLife clLifeInfo(GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_TIMEOUT);
	cltMsg clLifeMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clLifeInfo), (BYTE*)&clLifeInfo);
	SendNeighbourMsg(&clLifeMsg, true);

	// DB로 죽었다고 날린다
	sDBRequest_SoulGuard_Dead clMsg( pclParent->pclCI->GetPersonID(), pclParent->pclSoulGuard->GetSoulGuardID(), SOULGUARD_DEAD_MODE_DEAD );
	pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

}


void cltCharServer::CharServerAction_PC()
{

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL ) return ;


	// 1초마다 들어온다.
	if(TABS(pclClient->CurrentClock - clSimpleVary.dwLastCheckCharServerActionPCClock) > 1000)
	{
		clSimpleVary.dwLastCheckCharServerActionPCClock = pclClient->CurrentClock;
		CalcPlayTime();

#ifdef USE_GAME_GUARD_SERVER

		CCSAuthRun();

#endif

		// 30초에 한번씩 버그 캐릭터 체크를 한다
		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_BUGCHAR_CHECK].IsTimed(GetTickCount()) )
		{
			if ( 0 < pclCI->GetPersonID() )	// 캐릭터 선택에 경우 캐릭터는 있지만 PID가 0이다
			{
				if ( (GetID() != pclCM->GetIDFromName((TCHAR*)GetName()))
					|| (GetID() != pclCM->GetIDFromPersonID(pclCI->GetPersonID()))
				)
				{
					if ( false == bCloseSocketSwitch )
					{
						pclserver->pclLog->FilePrint( TEXT("Config\\BugChar.txt"), TEXT("PersonID:%d"), pclCI->GetPersonID() );

						bCloseSocketSwitch = true;
						dwCloseSocketTimer = 5;
					}
				}
			}	// if ( 0 < pclCI->GetPersonID() ) 종료
		}	// if( m_clCharUpdateTimer[CHAR_UPDATETIMER_BUGCHAR_CHECK].IsTimed(GetTickCount()) ) 종료

		// 길드 포인트 적립
		if (TABS(pclClient->CurrentClock - clSimpleVary.dwGuildPointClock) > 3600000 ) // 60분 ( 3600초 )
		{
			if ( pclCI->clBI.clGuildRank.IsGuildMember() == true && clSimpleVary.dwGuildPointClock != 0 )
			{
				cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
				if ( pGuild )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCI->GetPersonID(),1,TYPE_GUILDPOINT_ADD_PLAYTIME,150);
					pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}

			clSimpleVary.dwGuildPointClock = pclClient->CurrentClock;
		}
		// 종량제 시스템 처리 - by LEEKH 2007.12.27
		cltTimeMeterRateInfo * pclTimeMeterRateInfo = &pclCI->clBI.clTimeMeterRateInfo;

		// 시간 처리
		for( SI32 i=0; i < MAX_TIMEMETERRATE; i++ )
		{
			cltTimeMeterRate*	pclTimeMeterRate = &pclTimeMeterRateInfo->m_clTimeMeterRate[i];
			if( pclTimeMeterRate->IsUse() )
			{
				//				if( TABS(pclClient->CurrentClock - pclTimeMeterRate->dwStartedTime) >= 1000 )
				{
					//pclTimeMeterRate->dwStartedTime = pclClient->CurrentClock;

					SI32	siUseClock = TABS(pclClient->CurrentClock - pclTimeMeterRate->dwStartedTime);
					SI32	siUseSecond = siUseClock / 1000;
					SI32	siLeftClock = siUseClock % 1000;

					// 1000으로 나누어 떨어지지 않는 클럭수를 다음 계산에 적용하기 위해 다음과 같이 설정한다.
					pclTimeMeterRate->dwStartedTime = pclClient->CurrentClock - siLeftClock;

					SI32	siUseTime = pclTimeMeterRateInfo->m_siUseTimePerSec * siUseSecond;
					if( pclTimeMeterRate->siLeftTimeSec < siUseTime)		siUseTime = pclTimeMeterRate->siLeftTimeSec;
					if(siUseTime > 0)		pclTimeMeterRate->UseTime( siUseTime );

					// 시간을 모두 소비했으면, DB로 전송한다. 사용을 중지 시킨다.
					if( pclTimeMeterRate->siLeftTimeSec <= 0)
					{
						sDBRequest_TimeMeterRate_UseTime clMsg(GetCharID(), pclCI->GetPersonID(), pclTimeMeterRate->siTimeMeterRateType, pclTimeMeterRate->siUseTimeSec, true );
						pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

						// 변신 시간도 증가시켜 준다.
						if( clTransFormInfo.bTransFormMode )
						{
							// DB에 변신 시간을 추가해준다.
							sDBRequest_Transform_AddTime clMsg1(GetCharID(), pclCI->GetPersonID(), clTransFormInfo.uiNowTransFormKind, pclTimeMeterRate->siUseTimeSec );
							pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);
						}

						pclTimeMeterRateInfo->UseEnd( pclTimeMeterRate->siTimeMeterRateType );

					}

					// 종량제 서비스처리에 따른 부가적인 컨텐츠 정보
					switch(pclTimeMeterRate->siTimeMeterRateType)
					{
					case TIMEMETERRATE_TRANSFORM:		// 변신
						{
							UI16 tKind = clTransFormInfo.uiNowTransFormKind;
							SI32 siBeforeSync = (SI32)clTransFormInfo.GetSynchroTransForm( tKind );
							// 해당 변신의 사용시간을 더한다.
							clTransFormInfo.AddTransFormTime(tKind, siUseTime);
							SI32 siCurSync = (SI32)clTransFormInfo.GetSynchroTransForm( tKind );

							if( siCurSync == 100 &&
								siBeforeSync < siCurSync )
							{
								// 싱크율 100를 달성한 경우 명품 알림창을 띄운다.
								cltItem clItem;		clItem.Init();

								SI32 siItemUnique = GetItemUniqueFromCharKind(clTransFormInfo.uiNowTransFormKind);
								if(siItemUnique > 0)
								{
									SI16 brareswitch = 0;
									if( pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clItem, 0, 0, &brareswitch,0,0,0,0,0,0) == true )
									{
										clItem.SetItemNum(1);
										cltGameMsgResponse_MaxSyncro_Attainment clMaxSyncro( &clItem, clTransFormInfo.uiNowTransFormKind, pclCI->clBI.GetName() );
										cltMsg clMsg( GAMEMSG_RESPONSE_MAXSYNCRO_ATTAINMENT, sizeof(clMaxSyncro), (BYTE*)&clMaxSyncro );
										pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
									}
								}

							}

							// 싱크율이 변경되었으므로, 클라이언트에 한번 전송한다.
							if( siCurSync != siBeforeSync )
							{
								// 클라이언트에 정보를 전송한다.
								cltGameMsgResponse_SetTransForm	clTrasFormInfo( &clTransFormInfo );
								cltMsg clMsg( GAMEMSG_RESPONSE_TRANSFORM, sizeof(cltTransFormInfo), (BYTE*)&clTrasFormInfo );
								SendNetMsg( (sPacketHeader*)&clMsg );			
							}

							// 변신 100% 이펙트를 그려준다.
							if( siCurSync >= 100 )
							{
								cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_TRANSFORM100EFFECT, true);
								cltGameMsgResponse_StatusInfo clinfo(GetID(), &clchangeinfo);
								cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
								SendNeighbourMsg(&clMsg, true);					
							}

							// 종량제 시간이 없으면, 변신을 종료시킨다.
							if( pclTimeMeterRate->siLeftTimeSec <= 0)
							{
								cltCharServer* pclchar = (cltCharServer*)pclCM->CR[GetID()];
								cltItem *pclItemList = pclCM->CR[GetID()]->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
								cltPSkillInfo *pclskillinfo = &pclchar->pclCI->clCharSkill;
								// 변신 종료
								CharTransform( 0 ,pclchar->ActiveWeapon , pclItemList ,pclskillinfo);
							}
						}
						break;
					case TIMEMETERRATE_MOTORCYCLE:		// 오토바이.
						{
							// 리터가 변경되었으므로, 클라이언트에 한번 전송한다.
							// 자체적으로 남은 시간만으로 계산함으로 그럴필요가 없다.

							// 종량제 시간이 없으면, 오토바이에서 내리게 한다.
							if( pclTimeMeterRate->siLeftTimeSec <= 0)
							{
								cltCharServer* pclchar = (cltCharServer*)pclCM->CR[GetID()];
								SI16 showHorseIndex = pclchar->pclCI->clHorseInfo.GetCurrentShowHorseIndex();

								pclchar->UnrideHorse();

								// DB에 말을 탔음을 알린다. 
								sDBRequest_SetRideHorse cldbmsg(GetCharID(), pclCI->GetPersonID(), showHorseIndex , false);
								pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);

							}
						}
						break;
					}
				}
			}
		}

		// 일정 간격으로 DB에 종량제 정보를 전송한다. - by LEEKH 2007.12.27
		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_TIMEMETERRATE_DB].IsTimed(GetTickCount()) )
		{
			for( SI32 i=0; i < MAX_TIMEMETERRATE; i++ )
			{
				cltTimeMeterRate*	pclTimeMeterRate = &pclTimeMeterRateInfo->m_clTimeMeterRate[i];
				if( pclTimeMeterRate->IsUse() )
				{
					bool	bUpdate = false;

					if( pclTimeMeterRate->siLeftTimeSec <= 0)		bUpdate = true;

					if( pclTimeMeterRate->siUseTimeSec > 0)
					{
						// DB 로 사용량을 전송한다.
						sDBRequest_TimeMeterRate_UseTime clMsg(GetCharID(), pclCI->GetPersonID(), pclTimeMeterRate->siTimeMeterRateType, pclTimeMeterRate->siUseTimeSec, bUpdate );
						pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}

					// 종량제 서비스에 따른 컨텐츠 처리
					switch(pclTimeMeterRate->siTimeMeterRateType)
					{
					case TIMEMETERRATE_TRANSFORM:		// 변신
						{
							if( pclTimeMeterRate->siUseTimeSec > 0)
							{
								if( clTransFormInfo.bTransFormMode )
								{
									// DB에 변신 시간을 추가해준다.
									sDBRequest_Transform_AddTime clMsg1(GetCharID(), pclCI->GetPersonID(), clTransFormInfo.uiNowTransFormKind, pclTimeMeterRate->siUseTimeSec );
									pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);
								}
							}
						}
						break;
					}

					// 다음 DB통신을 위해 사용량 초기화
					pclTimeMeterRate->siUseTimeSec = 0;
				}
			}
		}

		// 일정 간격으로 클라이언트에 종량제 정보를 전송한다. - by LEEKH 2007.12.27
		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_TIMEMETERRATE_CLIENT].IsTimed(GetTickCount()) )
		{
			for( SI32 i=0; i < MAX_TIMEMETERRATE; i++ )
			{
				cltTimeMeterRate*	pclTimeMeterRate = &pclTimeMeterRateInfo->m_clTimeMeterRate[i];
				if( pclTimeMeterRate->IsUse() )
				{
					// 클라이언트에 정보를 전송한다.
					cltGameResponse_TimeMeterRate_Update	clTimeMeterRate( pclTimeMeterRate );
					cltMsg clMsg( GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE, sizeof(clTimeMeterRate), (BYTE*)&clTimeMeterRate );
					SendNetMsg( (sPacketHeader*)&clMsg );
				}
			}
		}

		// 일정 간격으로 클라이언트에 변신 정보를 보낸다.
		if( m_clCharUpdateTimer[CHAR_UPDATETIMER_TRANSFORMINFO_CLIENT].IsTimed(GetTickCount()) )
		{
			if(clTransFormInfo.bTransFormMode == true)
			{
				// 클라이언트에 정보를 전송한다.
				cltGameMsgResponse_SetTransForm	clTrasFormInfo( &clTransFormInfo );
				cltMsg clMsg( GAMEMSG_RESPONSE_TRANSFORM, sizeof(cltTransFormInfo), (BYTE*)&clTrasFormInfo );
				SendNetMsg( (sPacketHeader*)&clMsg );			
			}
		}

		// 피로도 시스템  - 클라이언트에 정해진 시간에 따라, 정보를 날린다.
		if(true == bTiredSystem )
		{
			if( m_clCharUpdateTimer[CHAR_UPDATETIMER_TIREDSYSTEM_TIME_LIMIT].IsTimed(GetTickCount()) ) // 20초
			{
				SI16 NowTiredNotice = 0;
				SI32 playMinute = dwPlayingTime / 60;

				switch(playMinute)
				{
				case 60: // 1 시간.
					NowTiredNotice = TIRED_NOTICE_1_HOUR;
					break;
				case 120: // 2 시간.
					NowTiredNotice = TIRED_NOTICE_2_HOUR;
					break;
				case 150: // 2 시간 30분
					NowTiredNotice = TIRED_NOTICE_2_5_HOUR;
					break;
				case 180: // 3 시간.
					{
						uiTiredState = TIRED_STATUS_LITTLE_TIRED;
						NowTiredNotice = TIRED_NOTICE_3_HOUR;
					}
					break;
				case 210: // 3 시간 30분
					NowTiredNotice = TIRED_NOTICE_3_5_HOUR;
					break;
				case 240: // 4 시간.
					NowTiredNotice = TIRED_NOTICE_4_HOUR;
					break;
				case 270: // 4 시간 30분
					NowTiredNotice = TIRED_NOTICE_4_5_HOUR;
					break;
				case 300: // 5 시간.
					{
						uiTiredState = TIRED_STATUS_MUCH_TIRED;
						NowTiredNotice = TIRED_NOTICE_5_HOUR;
					}
					break;
				default :
					{
						// 5시간 이상일 경우에 대한 예외 처리.
						if(playMinute > 300)
						{
							SI32 overtime = (playMinute - 300)%15;
							SI32 dovertime = ((playMinute - 300)/15)+1;

							if((overtime == 0) && (lastTiredNoticedovertime  < dovertime)) // 15분에 한번씩
							{
								uiTiredState = TIRED_STATUS_MUCH_TIRED;
								NowTiredNotice = TIRED_NOTICE_5_OVER_HOUR;

								lastTiredNoticedovertime = dovertime;
							}
						}						
					}
				}

				// 클라이언트에 알려야 할때만 알린다.
				if(((NowTiredNotice > 0) && (NowTiredNotice !=siTiredNotice))||(NowTiredNotice == TIRED_NOTICE_5_OVER_HOUR))
				{
					// 현재 경고값을 저장해 놓는다.
					siTiredNotice = NowTiredNotice;

					cltGameMsgResponse_TiredStateNotice clInfo( uiTiredState, siTiredNotice ,GetName());
					cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS, sizeof(clInfo), (BYTE*)&clInfo );
					SendNetMsg( (sPacketHeader*)&clMsg );
				}			
			}			
		}

		if(TABS(pclClient->CurrentClock - clSimpleVary.dwRealKillClock) > 600000) // 10분 ( 600초 )
		{
			clSimpleVary.dwRealKillClock = pclClient->CurrentClock;

			// 중국은 매크로 방지 몬스터 출현하지 않는다.
			if( clSimpleVary.siCheckMonsterNum >= 80 && pclClient->siServiceArea != ConstServiceArea_China )
			{
				if ( pclClient->pclMapManager->IsEncountMap(GetMapIndex()) &&  GetMapIndex() != MAPINDEX_MOFUMOFULAND )
				{
					SI32 x = GetX();
					SI32 y = GetY();

					SI32 kind = pclClient->GetUniqueFromHash(TEXT("KIND_JOKER"));

					cltInnerStatusInfo clinnerstatus;
					clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);		// 모든 PC와 우호적, 사람과는 적대적. 

					if(pclMap->FindEmptyAreaForCharLocate(kind, GetX() + 2, GetY(), 100, &x, &y, true) )
					{
						// 도마돈은 100레벨로 소환된다.
						SI32 siSummonID = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 100, 0,  x, y, GetMapIndex(), NPCITEMMODE_NORMAL, &clinnerstatus );

						//-------------------------------------------------------------
						// JOKERMONSTER
						//-------------------------------------------------------------
						// 조커 몬스터의 생명시간을 위해 현재의 시간을 설정한다.
						if(pclCM->IsValidID(siSummonID) )
						{
							((cltCharServer*)pclCM->CR[ siSummonID])->dwTimerClock = pclserver->CurrentClock;
						}
						//-------------------------------------------------------------
					}
				}
			}

			SetKillMonsterNum(0);
		}


		//// 할로윈 NPC 생성
		//if(TABS(pclClient->CurrentClock - clSimpleVary.dwRealKillClock) > 60) // 10분 ( 600초 )//1시간마다
		//{
		//	clSimpleVary.dwRealKillClock = pclClient->CurrentClock;
		//	if ( pclClient->pclMapManager->IsEncountMap(GetMapIndex()) &&  GetMapIndex() != MAPINDEX_MOFUMOFULAND )
		//	{
		//		SI32 x = GetX();
		//		SI32 y = GetY();

		//		cltInnerStatusInfo clinnerstatus;
		//		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);		// 모든 PC와 우호적, 사람과는 적대적. 
		//		// 도마돈은 100레벨도 소환된다.
		//		SI32 siSummonID = pclserver->SetNPCChar(pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENPC")), VILLAGE_NONE, NULL, 100, 0,  x+2, y, GetMapIndex(), NPCITEMMODE_NORMAL, &clinnerstatus );

		//		//-------------------------------------------------------------
		//		// JOKERMONSTER
		//		//-------------------------------------------------------------
		//		// 조커 몬스터의 생명시간을 위해 현재의 시간을 설정한다.
		//		if(pclCM->IsValidID(siSummonID) )
		//		{
		//			((cltCharServer*)pclCM->CR[ siSummonID])->dwTimerClock = pclserver->CurrentClock;
		//		}
		//		//-------------------------------------------------------------
		//	}
		//	SetKillMonsterNum(0);
		//}
		//---------------------------------------------
		// 자동 회복 처리 
		//---------------------------------------------
		cltItem* pclitemlist = pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
		SI32 itemtype = pclserver->pclItemManager->GetItemType(pclitemlist[ActiveWeapon].siUnique) ;
		SI32 skilllevel = 0 ;

		DWORD autorecoverlifeclock = 50000 ;
		DWORD autorecovermanaclock = 50000 ;
		/*
		switch ( itemtype )
		{

		case ITEMTYPE_SPEAR:
			{
				skilllevel = pclCI->clCharSkill.GetTotalSkillLevel(SKILL_SPEAR_INCRECMANA, 0, 0, pclitemlist);
				if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
				{
					// SJY DEBUG
					SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW3,skilllevel);
					autorecovermanaclock = autorecovermanaclock -  rate * 1000 ;
				}
			}
			break;

		case ITEMTYPE_AXE:
			{
				skilllevel = pclCI->clCharSkill.GetTotalSkillLevel(SKILL_AXE_INCRECLIFE, 0, 0, pclitemlist);
				if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
				{
					// SJY DEBUG
					SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW3,skilllevel);
					autorecoverlifeclock = autorecoverlifeclock -  rate * 1000 ;
				}
			}
			break;
		}
		*/

			// 버프 마법에 의한 마나 회복속도 증가
			if ( IsPC(GetCharUnique()) )
			{
				SI32 siSubRecoveryManaClock = m_clMagicBufMgr.GetIncMPRecoveryTime( this );
				if ( siSubRecoveryManaClock )
				{
					DWORD dwCalcRecoveryManaClock = (autorecovermanaclock / siSubRecoveryManaClock) * 100;
					autorecovermanaclock = dwCalcRecoveryManaClock;
					pclClient->pclLog->LogPrint( TEXT("마나회복속도 : %d\n"), dwCalcRecoveryManaClock );
				}
			}

			if((DWORD)TABS(pclClient->CurrentClock - dwAutoRecoverLifeClock) > autorecoverlifeclock)
			{
				dwAutoRecoverLifeClock = pclClient->CurrentClock;

				AutoRecoverLife();
			}

			//
			DWORD autocusionrecoverclock  = 5000;

			if( (DWORD)TABS( pclClient->CurrentClock - dwCusionRecoverLifeClock ) > autocusionrecoverclock )
			{
				dwCusionRecoverLifeClock = pclClient->CurrentClock;

				//
				AutoCushionRecoverLife();

			}

			if( (DWORD)TABS(pclClient->CurrentClock - dwAutoRecoverManaClock) > autorecovermanaclock)
			{
				dwAutoRecoverManaClock = pclClient->CurrentClock;

				AutoRecoverMana();
			}

			if( (DWORD)TABS(pclClient->CurrentClock - dwCusionRecoverManaClock) > autocusionrecoverclock )
			{
				dwCusionRecoverManaClock = pclClient->CurrentClock;

				//
				AutoCushionRecoverMana();
			}

			DWORD autocusionOFSclock  = 30000;

			// 기관 회복
			if( (DWORD)TABS(pclClient->CurrentClock - dwCusionRecoverOragansClock) > autocusionOFSclock )
			{
				dwCusionRecoverOragansClock = pclClient->CurrentClock;

				AutoCushionRecoverOragans();
			}
			// 포만감 하락.
			if( (DWORD)TABS(pclClient->CurrentClock - dwCusionFallSatisfiedClock) > autocusionOFSclock )
			{
				dwCusionFallSatisfiedClock = pclClient->CurrentClock;

				AutoCushionFallSatisfied();
			}

			// PCK : 잠자는 냐옹이 쿠션 소환수 자동 회복 관련 (09.06.15)
			if( (DWORD)TABS( pclClient->CurrentClock - dwCusionRecoverSummonLifeClock ) > autocusionrecoverclock )
			{
				dwCusionRecoverSummonLifeClock = pclClient->CurrentClock;

				AutoCushionRecoverSummonLife();
			}

			if( (DWORD)TABS(pclClient->CurrentClock - dwCusionRecoverSummonManaClock) > autocusionrecoverclock )
			{
				dwCusionRecoverSummonManaClock = pclClient->CurrentClock;

				AutoCushionRecoverSummonMana();
			}

			DWORD autoTransformrecoverclock  = 5000;
			//KHY - 1220 - 변신시스템. - 지팡이 싱크로 100% = 마나회복증가.
			if( (DWORD)TABS(pclClient->CurrentClock - dwTransFormRecoverManaClock) > autoTransformrecoverclock )
			{
				dwTransFormRecoverManaClock = pclClient->CurrentClock;

				//
				AutoTransFormRecoverMana();
			}


			// 무한워프 이용권 관련 작업
			if ( pclCI->clBI.bUseNoLimitTicketWarp )
			{
				// 이용기간이 지나면 없애주는 패킷을 db로 날린다.
				if ( pclCI->clBI.siNoLimitTicketWarpDateVary < pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_NoLimitTicket_Warp clMsg( false ,GetID(), pclCI->GetPersonID(), 0, &clitem, 0, NOLIMIT_TICKET );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}

			// 공간상자 티켓 관련작업
			if ( pclCI->clBI.bSpaceBoxPremiumService )
			{
				// 이용기간이 지나면 없애주는 패킷을 db로 날린다.
				if ( pclCI->clBI.siSpaceBoxPremiumServiceDate< pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_NoLimitTicket_Warp clMsg( false ,GetID(), pclCI->GetPersonID(), 0, &clitem, 0, SPACEBOX_TICKET );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
			// 소환수 확장 티켓 관련 작업
			if ( pclCI->clBI.bSummonExtraSlot )
			{
				// 이용기간이 지나면 없애주는 패킷을 db로 날린다.
				if ( pclCI->clBI.bSummonExtraSlot==true && pclCI->clBI.siSummonExtraSlotDate < pclserver->pclTime->clDate.GetDateVary() )
				{
					// 사용기간이 다되면 티켓을 날려버린다.
					cltItem clitem;
					clitem.Init();
					sDBRequest_NoLimitTicket_Warp clMsg( false ,GetID(), pclCI->GetPersonID(), 0, &clitem, 0, SUMMON_SPACE_TICKET );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					// 슬롯으로 집어 넣는다.
					for( SI32 i=MAX_SUMMON_OWN; i<MAX_HAVE_SUMMON; i++)
					{
						cltSimpleSummon* pclSimpleSummon = pclCI->clSummonInfo.GetSummonBase(i);
						SI32 siSummonID = pclSimpleSummon->siSummonID;
						SI32 siSummonIndex = pclCI->clSummonInfo.GetSummonIndexFromSummonID(siSummonID);
						if(siSummonIndex >= 0)
						{
							sDBRequest_SummonSlotOut clMsg(GetCharID(), pclCI->GetPersonID(), siSummonID, siSummonIndex);
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}
					}
				}
			}

			// 프리미엄 서비스 관련
			if ( pclCI->clBI.bPremiumService )
			{
				// 이용기간이 지나면 없애준다.
				if ( pclCI->clBI.siPremiumServiceDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_SetPremium clMsg(GetID(),pclCI->GetPersonID(),false,0,0,0,0,0,&clitem,0,SETPREMIUM_EXP);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
			// 프리미엄 서비스 관련
			if ( pclCI->clBI.bCombatService )
			{
				// 이용기간이 지나면 없애준다.
				if ( pclCI->clBI.siCombatServiceDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_SetPremium clMsg(GetID(),pclCI->GetPersonID(),false,0,0,0,0,0,&clitem,0,SETPREMIUM_COMBAT);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}
			// 제조 프리미엄 서비스 관련
			if ( pclCI->clBI.bMakeItemService )
			{
				// 이용기간이 지나면 없애준다.
				if ( pclCI->clBI.siMakeItemServiceDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_SetPremium clMsg(GetID(),pclCI->GetPersonID(),false,0,0,0,0,0,&clitem,0,SETPREMIUM_MAKEITEM);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}

			// 탄환 프리미엄 서비스 관련
			if ( pclCI->clBI.bBulletService )
			{
				// 이용기간이 지나면 없애준다.
				if ( pclCI->clBI.siBulletServiceDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_SetPremium clMsg(GetID(),pclCI->GetPersonID(),false,0,0,0,0,0,&clitem,0,SETPREMIUM_BULLET);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}

			// 소환수 스태미너 프리미엄 서비스 관련
			if ( pclCI->clBI.bSummonStaminaService )
			{
				// 이용기간이 지나면 없애준다.
				if ( pclCI->clBI.siSummonStaminaServiceDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_SetPremium clMsg(GetID(),pclCI->GetPersonID(),false,0,0,0,0,0,&clitem,0,SETPREMIUM_SUMMONSTIMINA);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}

			// 객주 프리미엄 관련
			if ( pclCI->clBI.bMarKetPremiumService )
			{
				// 이용기간이 지나면 없애주는 패킷을 db로 날린다.
				if ( pclCI->clBI.siMarKetPremiumServiceDate < pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_NoLimitTicket_Warp clMsg( false ,GetID(), pclCI->GetPersonID(), 0, &clitem, 0, MARKET_TICKET );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}

			//[진성] 통합마켓 프리미엄 관련.
			if ( pclCI->clBI.bNewMarketPremiumService )
			{
				// 이용기간이 지나면 없애주는 패킷을 db로 날린다.
				if ( pclCI->clBI.siNewMarketPremiumServiceDate < pclserver->pclTime->clDate.GetDateVary() )
				{
					cltItem clitem;
					clitem.Init();
					sDBRequest_NoLimitTicket_Warp clMsg( false ,GetID(), pclCI->GetPersonID(), 0, &clitem, 0, NewMarket_TICKET );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}

			// 시간이 지난 버프는 해제 한다.
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclCI->clBI.clBufInfo );
			for ( SI16 i=0 ; i < MAX_BUF_COUNT ; i++ )
			{
				if ( clBuf.m_stBuf[i].siBufType == 0 )
					continue;

				if ( ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() > clBuf.m_stBuf[i].siOverTime )
				{
					sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), i, &clBuf.m_stBuf[i]);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


					if( clBuf.m_stBuf[i].siBufType  == BUF_NOFIRSTATTACK		|| 
						clBuf.m_stBuf[i].siBufType  == BUF_HINAMOCHI			|| 
						clBuf.m_stBuf[i].siBufType  == BUF_EVENT_EGGMOONCAKE	|| 
						// 야시장 음식은 제외
						(clBuf.m_stBuf[i].siBufType  == BUF_TRANSFORM && clBuf.m_stBuf[i].siGetType != BUF_GET_TYPE_NIGHTMARKET)
					)
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACK, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}

					if( clBuf.m_stBuf[i].siBufType  == BUF_LOVEPOWER || clBuf.m_stBuf[i].siBufType  == BUF_FRIENDSHIP )
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_HEARTEFFECT, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}
					else if( clBuf.m_stBuf[i].siBufType == BUF_FOURLEAF )
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FOURLEAF, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}

					else if( clBuf.m_stBuf[i].siBufType == BUF_HAPPYBEAN )
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(BUF_HAPPYBEAN, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}
					else if( clBuf.m_stBuf[i].siBufType == BUF_THANKSGIVING_DAY )
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(BUF_THANKSGIVING_DAY, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}
					else if( clBuf.m_stBuf[i].siBufType == BUF_FARMINGNMININGFOREVER )
					{
						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(BUF_FARMINGNMININGFOREVER, false);
						cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						SendNeighbourMsg(&clMsg, true);
					}


				}
			}

			// 광산,농장의 임시 계약 기간이 끝나면
			if ( m_pclAgriculture && m_pclAgriculture->GetCurrentVillageUnique() > 0)
			{
				UI32 uiLeaseExpire = m_pclAgriculture->GetExpireTime( m_pclAgriculture->GetCurrentVillageUnique() );
				if( uiLeaseExpire > 0 && pclClient->GetMinuteFromsTime( ((cltServer*)pclClient)->sTime ) >= uiLeaseExpire )
				{
					// DB로 삭제 요청
					sDBRequest_ExpiredAgricultureLease clMsg( pclCI->GetPersonID(), m_pclAgriculture->GetCurrentVillageUnique(), uiLeaseExpire );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );

					// 서버 정보 설정
					m_pclAgriculture->DeleteAgriculture( m_pclAgriculture->GetCurrentVillageUnique() );
					m_pclAgriculture->EndAgriculture( m_pclAgriculture->GetCurrentVillageUnique() );
				}
			}

			// 감옥 관련 작업. 
			if(clInnerStatus.IsStatus(INNERSTATUS_PRISON))
			{
				// 남은 시간을 계산한다. 
				if(TABS(pclClient->CurrentClock - dwPrisonClock) > 1000)
				{
					dwPrisonClock = pclClient->CurrentClock;

					if(pclCI->clGuiltyInfo.siLeftPrisonSecond)pclCI->clGuiltyInfo.siLeftPrisonSecond--;

					//현재의 수감 정보를 클라이언트에게 통보한다. 
					SetUpdateSwitch(UPDATE_GUILTY, true, 0);

					// 경복궁으로 워프 시킨다. 
					if(pclCI->clGuiltyInfo.siLeftPrisonSecond == 0)
					{
						clInnerStatus.DelStatus(INNERSTATUS_PRISON);
						WarpToSafeZone();

						pclCI->clGuiltyInfo.Init();
						sDBRequest_GuiltyInfoRecord clMsg(GetID(), pclCI->GetPersonID(), &pclCI->clGuiltyInfo);
						pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&clMsg );


					}
				}
			}
			else if(pclCI->clGuiltyInfo.siLeftPrisonSecond)
			{
				SendPrison();
			}

			//-------------------------------------
			// 명성 레벨을 갱신한다. 
			//-------------------------------------
			if(clSimpleVary.bCheckFameLevelSwitch == false && (pclClient->GetFrame() > dwMakeFrame + 200))
			{
				clSimpleVary.bCheckFameLevelSwitch = true;
				IncreaseFameExp(0);
			}

			// 스틸 정보를 정리한다. 
			if(GetStealNum())
			{
				if(TABS(pclClient->CurrentClock - dwStealClock) > 60000)
				{
					dwStealClock	= pclClient->CurrentClock;
					siStealNum--;
				}
			}
			
			// 웨딩 시스템 관련
			if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
			{
				// 결혼 했다면
				if ( TRUE == IsMarried() )
				{
					//============================================
					// 결혼 기념일 아이템 지급 체크
					//============================================
					SI32 siNowDateVary = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary();

					if ( (FALSE == pclMarriage->GetRequestItemGet())					// 아직 요청 하지 않았다면
						&& (TRUE == pclMarriage->IsWeddingAnniversary(siNowDateVary))	// 결혼 기념일 이고 
						&& (FALSE == pclMarriage->IsWeddingItemGet(siNowDateVary))		// 아직 결혼 기념일 아이템을 안받았고
					)
					{
						// 우선 요청 했다고 변경하고
						pclMarriage->SetRequestItemGet( TRUE );

						// 유저에게 결혼 기념일 아이템 받으라고 보낸다
						((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_REQUEST_WEDDING_ITEMGET, 0, 0, GetCharUnique() );
						
					}

					//============================================
					// 애정도 버프 체크
					//============================================
					SI32 siNowHourVary	= pclserver->pclTime->clDate.GetHourVary();
					SI16 siNowLoveLevel = pclMarriage->GetLoveLevel();
					if ( (MARRIAGE_LOVE_LEVEL_01 < siNowLoveLevel) && (0 < pclMarriage->GetLimitHourVary()) )
					{
						SI16 siCalcLoveLevel = pclMarriage->CalcNowLoveLevel( siNowHourVary );
						if ( siCalcLoveLevel != siNowLoveLevel )
						{
							// 게임시간 하루(24시간,현실시간 48분)마다 2단계씩 떨어져야 하니까 24시간을 더해준다
							pclMarriage->SetLimitHourVary( siNowHourVary + 24 );
							pclMarriage->SetLoveLevel( siCalcLoveLevel );

							sDBRequest_Marry_Love_Set clMsg( pclCI->GetPersonID(), pclMarriage->GetUseHourVary(), pclMarriage->GetLimitHourVary(), pclMarriage->GetLoveLevel() );
							pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );

							/*
							// 배우자 캐릭터
							SI32			siMateCharID	= pclClient->pclCM->GetIDFromPersonID( pclMarriage->GetMatePersonID() );
							cltCharServer*	pclMateChar		= pclClient->pclCM->GetCharServer( siMateCharID );
							if ( (pclMateChar) && (pclMateChar->IsMarried()) )
							{
								pclMateChar->pclMarriage->SetLimitDateVary( siNowDateVary + 1 );
								pclMarriage->SetLoveLevel( siCalcLoveLevel );

								sDBRequest_Marry_Love_Set clMsg( pclCI->GetPersonID(), pclMateChar->pclMarriage->GetUseDateVary(), pclMarriage->GetLimitDateVary(), pclMateChar->pclMarriage->GetLoveLevel() );
								pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );
							}
							*/
						}
					}	// if ( (MARRIAGE_LOVE_LEVEL_01 < siNowLoveLevel) && (0 < pclMarriage->GetLimitDateVary()) )
				}
			}


			// 자동 연결 종료 설정중이라면. 
			if(bCloseSocketSwitch)
			{
				if(dwCloseSocketTimer)
				{
					dwCloseSocketTimer --;

					if(dwCloseSocketTimer == 0)
					{
						// apex-
#ifdef _CHINA
						if( 0 < GetID() )
							NoticeApexProxy_UserLogout( GetID(), (char*)pclCI->clBI.szAccountID );
						bApexLogin = false;
#endif
						// -apex

#ifdef USE_GAME_GUARD_SERVER
						CCSAuthClose();
#endif
						bCloseSocketSwitch = false;
						GetSession()->CloseSocket();

						// -- 비정상 캐릭터 종료처리 --

						// 캐릭터 종료 처리
						//Close();
						// 네트워크 연결 종료
						//GetSession()->CloseSocket();
					}
				}
			}

			// 자기 자리가 충돌 지역인지 확인한다. 
			if(bReadySwitch && TABS(pclClient->CurrentClock - dwLastCheckCollClock) > 2000)
			{
				dwLastCheckCollClock = pclClient->CurrentClock;

				if( IsColl(GetX(), GetY()) == true)	//  배를 타고 있는 상태에서는 강제 워프를 시키지 않는다. 
				{
					TCHAR* pText = GetTxtFromMgr(2817);
					if (pclClient->GameMode == GAMEMODE_SERVER)
						pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), pText, 
						pclCI->GetPersonID(), GetName(), GetMapIndex(), GetX(), GetY(), siWarpUnique);

					// 안전지대로 이동. 
					WarpToSafeZone();
				}
			}

			// 말 관련 조치를 취한다.
			if(TABS(pclClient->CurrentClock - clSimpleVary.dwLastHorseActionClock) >= 2000)
			{
				clSimpleVary.dwLastHorseActionClock = pclClient->CurrentClock;

				SI32 horseaction = 0;
				SI32 datevary = pclserver->pclTime->clDate.GetDateVary();

				//KHY - 1001 - 기승동물 5마리 보유 수정. - 모든 말을 검사한다.  - 모든말의 수명을 여기서 검사한다.
				for( int i = 0; i < MAX_HORSE_PER_PERSON; i++) 
				{
					cltHorse* pclhorse_die = pclCI->clHorseInfo.GetHorse(i);

					if(pclhorse_die && pclhorse_die->siHorseUnique )
					{
						// 수명이 다 되었다면 죽인다. 
						SI32 life = pclserver->pclHorseManager->GetLife(pclhorse_die, datevary);
						if(life <= 0)
						{
							// 말을 타고 있다는 정보를 초기화 시켜줘야 한다.
							pclCI->clHorseInfo.siCurrentHorseRIDEHORSE =  false;
							pclhorse_die->Init();
							//KHY - 1001 - 기승동물 5마리 보유 수정. - 몇번째 말이 죽는지 알기위해서// 200 + 죽은말의 인덱스값으로 반환된다.
							horseaction =  (HORSEACTION_DIE + i);		// 사망처리. 
							break;
						}
					}
				}

				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

				if(horseaction < HORSEACTION_DIE )
				{
					if(pclhorse != NULL)
						horseaction = CharHorseAction(pclhorse , true);
				}

				if(horseaction == HORSEACTION_UPDATE)	// 업데이트 처리. 
				{
					if(pclhorse != NULL)
					{
						// DB에 저장한다. 
						UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

						SetUpdateSwitch(UPDATE_HORSE, true, 0);
					}
				}
				else if ( horseaction == HORSEATTION_TICKET ) // 말능력향상이용권때문에
				{
					if(pclhorse != NULL)
					{
						// DB에 저장한다. 
						UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse,
							pclhorse,SETHORSE_REASON_TICKET);

						SetUpdateSwitch(UPDATE_HORSE, true, 0);
					}
				}
				else if ( horseaction == HORSEATTION_PREMIUMPARTS ) // 말능력향상이용권때문에
				{
					if(pclhorse != NULL)
					{
						// DB에 저장한다. 
						UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse,
							pclhorse,SETHORSE_REASON_PREMIUM_PARTS);

						SetUpdateSwitch(UPDATE_HORSE, true, 0);
					}
				}
				//KHY - 1001 - 기승동물 5마리 보유 수정. - 몇번째 말이 죽는지 알기위해서// 200 + 죽은말의 인덱스값으로 반환된다.
				else if(horseaction >= HORSEACTION_DIE)	// 사망처리. 
				{
					SI16 DiehorseIndex = horseaction - 200; //horseaction = 항상 200 이상이다.
					cltHorse* pclhorse_Die = pclCI->clHorseInfo.GetHorse(DiehorseIndex);

					if(pclhorse_Die)
					{
						// DB에 저장한다. 
						UpdateHorseToDB((cltServer*)pclClient, DiehorseIndex, pclhorse_Die, SETHORSE_REASON_DIE);

						SetUpdateSwitch(UPDATE_HORSE, true, 0);
					}
				}

				// 자동말먹이가 설정되어있다면, 
				if(pclCI->clHorseInfo.bAutoFoodSwitch)
				{
					if(TABS(pclClient->CurrentClock - dwLastCheckAutoFoodClock) > 5000)
					{
						dwLastCheckAutoFoodClock = pclClient->CurrentClock;

						SI32 itemunique, itemnum;
						if(pclCI->clHorseInfo.GetNeed(pclhorse, &itemunique, &itemnum))
						{
							AutoHorseFood(itemunique, itemnum);
						}
					}
				}

				if(TABS(pclClient->CurrentClock - clSimpleVary.dwlastCheckHorseSpeedQuestClock) >= 30000)
				{
					clSimpleVary.dwlastCheckHorseSpeedQuestClock = pclClient->CurrentClock;
					DoQuestCheckAndAction(QUEST_CLEAR_COND_HORSESPEED);
				}

			}



			//----------------------------------
			// 초기 보호 조치. 
			//----------------------------------
			if(clSimpleVary.bInitProtectSwitch)
			{
				if(TABS(pclClient->CurrentClock - clSimpleVary.dwInitProtectClock) >= 10000)
				{
					clSimpleVary.bInitProtectSwitch = false;
				}
			}

			if(bReadySwitch)
			{
				// 최고 장인 정보. 
				if(siReservedTopSkillUnique != clInnerStatus.siTopSkillUnique)
				{
					clInnerStatus.siTopSkillUnique = siReservedTopSkillUnique;

					// 클라이언트에 정보를 보낸다. 
					cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_TOPSKILLUNIQUE, true, siReservedTopSkillUnique);
					cltGameMsgResponse_StatusInfo clinfo(GetID(), &clchangeinfo);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
					SendNeighbourMsg(&clMsg, true);
				}

				// 변신 100% 이펙트 정보를 보낸다.
				/*if( clTransFormInfo.bTransFormMode == true )
				{
					SI32 siTransFormSyc = (SI32)clTransFormInfo.GetSynchroTransForm(clTransFormInfo.uiNowTransFormKind);

					if(siTransFormSyc >=100)
					{
						//clTransFormInfo.bTransForm100Effect  = true;

						cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_TRANSFORM100EFFECT, true, siReservedTopSkillUnique);
						cltGameMsgResponse_StatusInfo clinfo(GetID(), &clchangeinfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
						SendNeighbourMsg(&clMsg, true);					
					}
				}
				*/
					if(TABS(pclClient->GetFrame() - uiLevelInfoUpdateFrame) >= 12000)	// 5분.
					{
						uiLevelInfoUpdateFrame = pclClient->GetFrame();

						//---------------------------------
						// 기술 경험치 정보 저장. 
						//---------------------------------
						SendDBSkillExp();	

						//--------------------------------------
						// 예약되어 있는 아이템 사용을 처리한다.
						//--------------------------------------
						ItemUseReserveAction();

						//--------------------------------------
						// 예약되어 있는 탄환 아이템 사용을 처리한다.
						//--------------------------------------
						BulletUseReserveAction();

						//---------------------------------
						// 내구도 정보 저장.  - 아이템 자체 내구도는 사용안한다.
						//---------------------------------
						SendDBWasteDurability();
						SendDBSummonWasteDurability();

						//--------------------------------------
						// 자신의 소환수 정보를 저장 
						//--------------------------------------
						SendDBSummon(SETSUMMON_REASON_UPDATE, MAX_SUMMON_OWN);

						cltLevelInfo cllevelinfo(pclCI->clIP.siExp, pclCI->clIP.siLevel, pclCI->clIP.siBonus, pclCI->clIP.siSkillBonus, pclCI->clIP.siFameExp, pclCI->clIP.siFameLevel);
						if(clOldLevelInfo.IsSame(&cllevelinfo) == false)
						{
							//---------------------------------
							// 레벨 정보 저장 
							//---------------------------------
							SendDBLevelInfo(0, 0);
						}
					}

					//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 내구도 DB저장  - 일단 30분.
					if( m_clCharUpdateTimer[CHAR_UPDATETIMER_CRYSTALITEM_DB].IsTimed(GetTickCount()) ) // 30분.
					{
						SendDBCrystalDurability();
					}

					//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 내구도 client로 저장   - 일단 5분. - 안에서 1% 일때만 계산함으로
					if( m_clCharUpdateTimer[CHAR_UPDATETIMER_CRYSTALITEMINFO_CLIENT].IsTimed(GetTickCount()) ) // 5분.
					{			
						SendClientCrystalDurability();
					}			
			}


			//----------------------------------
			// 미션 퀘스트 시간 지남 처리
			//----------------------------------
			if( pclCI->clQuestInfo.clMissionQuestInfo.siUnique > 0 && pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique > 0 )
			{
				pclCI->clQuestInfo.clMissionQuestInfo.TimeReduce( 1 );		// 1초 삭제

				if( pclCI->clQuestInfo.clMissionQuestInfo.IsTimeLeft() == false )		// 시간 지남
				{
					// 설정된 퀘스트 초기화
					pclCI->clQuestInfo.clMissionQuestInfo.Init();
					pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

					// 미션 퀘스트 정보를 DB에 저장한다.
					sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclCI->GetPersonID(), &pclCI->clQuestInfo.clMissionQuestInfo );
					pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

					// 퀘스트 상태를 DB에 저장한다.
					sDBRequest_SetQuestInfo clQuestInfo(pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
					pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

					// 클라이언트에 퀘스트의 상태를 통보한다. 
					SetUpdateSwitch(UPDATE_QUEST, true, 0);
				}
			}

			//----------------------------------
			// Daily Quest
			//----------------------------------
			if ( pclCI->clDailyQuestInfo.siMonsterKind > 0 )
			{
				// 30초당 한번씩 처리
				if( TABS( pclClient->CurrentClock - dwDailyQuestClock ) >= 30000 )
				{
					dwDailyQuestClock = pclClient->CurrentClock;
					pclCI->clDailyQuestInfo.siLeftTime -= 30;		// 30초 줄여줌.

					if ( pclCI->clDailyQuestInfo.siLeftTime <= 0 )
					{
						// 시간이 넘었으므로 퀘스트 실패
						pclCI->clDailyQuestInfo.siLeftTime = 0;
						cltItem clItem;
						clItem.Init();
						sDBRequest_DailyQuestDel clMsg( pclCI->GetPersonID(), GetID(), 0, 0, &clItem, 1,0, 0, 0 );
						cltServer *pclServer = (cltServer *)pclClient;
						pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
					else
					{
						// 시간안에 퀘스트수행량에 도달했을 경우 -> 완료처리 및 보상 지급
						if ( pclCI->clDailyQuestInfo.siKillMonsterNum >= pclCI->clDailyQuestInfo.siMonsterNum )
						{
							SI32 value = 100;

							cltItem clItem;
							clItem.siUnique = pclCI->clDailyQuestInfo.siRewardItemUnique;
							clItem.siItemNum = ( pclCI->clDailyQuestInfo.siRewardItemNum * value ) / 100;

							cltItem clToItem;
							clToItem.Init();

							SI16 InvPos = -1;
							SI32 rtnvalue;

							// 쓸데없는 이상코드 삭제 - By LEEKH 2008-10-23
							//if( pclCI->clDailyQuestInfo.siQuestTime - pclCI->clDailyQuestInfo.siLeftTime )

							// 돈으로 주는경우
							if ( pclCI->clDailyQuestInfo.bMoneySelected )
							{
								sDBRequest_DailyQuestDel clMsg( pclCI->GetPersonID(), GetID(), true, InvPos, &clItem, 1, ( pclCI->clDailyQuestInfo.siRewardMoney * value ) / 100, pclCI->clDailyQuestInfo.bMoneySelected, pclCI->clDailyQuestInfo.siRewardExp );
								cltServer *pclServer = (cltServer *)pclClient;
								pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

								pclServer->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_DAILYQUEST, (pclCI->clDailyQuestInfo.siRewardMoney * value) / 100);
							}
							else 
							{
								// 보상 아이템 지급
								if ( CanAddInv( INVMODE_PERSON, &clItem, &InvPos, &clToItem, &rtnvalue) )
								{
									sDBRequest_DailyQuestDel clMsg( pclCI->GetPersonID(), GetID(), true, InvPos, &clItem, 1, pclCI->clDailyQuestInfo.siRewardMoney, pclCI->clDailyQuestInfo.bMoneySelected, pclCI->clDailyQuestInfo.siRewardExp );
									cltServer *pclServer = (cltServer *)pclClient;
									pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
								}
								else
								{
									// 인벤 꽉 차서 안되므로... - 퀘스트의 현재 상태를 전송한다.
									cltServer *pclServer = (cltServer *)pclClient;
									pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

									cltGameMsgResponse_DailyQuestChange clinfo( pclCI->clDailyQuestInfo.siLeftTime, pclCI->clDailyQuestInfo.siKillMonsterNum );
									cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTCHANGE, sizeof(clinfo), (BYTE*)&clinfo);
									pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
								}

							}
						}
						else
						{
							// 퀘스트 도달량에 도달하지 못한 경우 현재 상태를 전송
							cltGameMsgResponse_DailyQuestChange clinfo( pclCI->clDailyQuestInfo.siLeftTime, pclCI->clDailyQuestInfo.siKillMonsterNum );
							cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTCHANGE, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}
			}

			//----------------------------------
			// Daily Quest2
			//----------------------------------
			if ( pclCI->clDailyQuest2Info.siMonsterKind > 0 )
			{
				// 30초당 한번씩 처리
				if( TABS( pclClient->CurrentClock - dwDailyQuest2Clock ) >= 30000 )
				{
					dwDailyQuest2Clock = pclClient->CurrentClock;
					pclCI->clDailyQuest2Info.siLeftTime -= 30;		// 30초 줄여줌.

					if ( pclCI->clDailyQuest2Info.siLeftTime <= 0 )
					{
						pclCI->clDailyQuest2Info.siLeftTime = 0;
						cltItem clItem;
						clItem.Init();
						sDBRequest_DailyQuest2Del clMsg( pclCI->GetPersonID(), GetID(), 0, 0, &clItem, 1,0, 0,pclCI->clDailyQuest2Info.bHiddenQuest);
						cltServer *pclServer = (cltServer *)pclClient;
						pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
				else
				{
					if ( pclCI->clDailyQuest2Info.siKillMonsterNum >= pclCI->clDailyQuest2Info.siMonsterNum )
					{

						SI32 value = 100;

						cltItem clItem;
						clItem.siUnique = pclCI->clDailyQuest2Info.siRewardItemUnique;
						clItem.siItemNum = ( pclCI->clDailyQuest2Info.siRewardItemNum * value ) / 100;

						cltItem clToItem;
						clToItem.Init();

						SI16 InvPos = -1;
						SI32 rtnvalue;

						// 쓸데없는 이상코드 삭제 - by LEEKH 2008-10-23
						//if( pclCI->clDailyQuest2Info.siQuestTime - pclCI->clDailyQuest2Info.siLeftTime)
						// 돈으로 주는경우
						if ( pclCI->clDailyQuest2Info.bMoneySelected )
						{
							sDBRequest_DailyQuest2Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos, &clItem, 1, ( pclCI->clDailyQuest2Info.siRewardMoney * value ) / 100, pclCI->clDailyQuest2Info.bMoneySelected, pclCI->clDailyQuest2Info.bHiddenQuest);
							cltServer *pclServer = (cltServer *)pclClient;
							pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
						}
						else 
						{
							if ( pclCI->clDailyQuest2Info.bHiddenQuest == true ) 
							{
								// 금빛 상자
								cltItem clItem2;
								clItem2.siUnique	=	ITEMUNIQUE(13321)	;
								clItem2.siItemNum	=	1	;


								if( CheckItemForEmptyAnyItemSlotByHiddenQuesst(INVMODE_PERSON, &clItem, &clItem2)  )
								{
									if ( CanAddInv( INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
									{
										sDBRequest_DailyQuest2Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos, &clItem, 1, pclCI->clDailyQuest2Info.siRewardMoney, pclCI->clDailyQuest2Info.bMoneySelected, pclCI->clDailyQuest2Info.bHiddenQuest);
										cltServer *pclServer = (cltServer *)pclClient;
										pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
									}
								}
								else
								{
									// 인벤 꽉 차서 안되므로...
									cltServer *pclServer = (cltServer *)pclClient;
									pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

									cltGameMsgResponse_DailyQuest2Change clinfo( pclCI->clDailyQuest2Info.siLeftTime, pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.bHiddenQuest );
									cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST2CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
									pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);

								}
							}
							else
							{
								if ( CanAddInv( INVMODE_PERSON, &clItem, &InvPos, &clToItem, &rtnvalue) )
								{
									sDBRequest_DailyQuest2Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos, &clItem, 1, pclCI->clDailyQuest2Info.siRewardMoney, pclCI->clDailyQuest2Info.bMoneySelected, pclCI->clDailyQuest2Info.bHiddenQuest);
									cltServer *pclServer = (cltServer *)pclClient;
									pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
								}
								else
								{
									// 인벤 꽉 차서 안되므로...
									cltServer *pclServer = (cltServer *)pclClient;
									pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

									cltGameMsgResponse_DailyQuest2Change clinfo( pclCI->clDailyQuest2Info.siLeftTime, pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.bHiddenQuest );
									cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST2CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
									pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
								}
							}
						}
					}
					else
					{
						cltGameMsgResponse_DailyQuest2Change clinfo( pclCI->clDailyQuest2Info.siLeftTime, pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.bHiddenQuest );
						cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST2CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
			//----------------------------------
			// Daily Quest3
			//----------------------------------
			if ( pclCI->clDailyQuest3Info.siItemUnique > 0 &&
				pclCI->clDailyQuest3Info.bHiddenQuest == false ) // 데일리 퀘스트 3일때 히든일 경우에는 시간이 안줄어들도록 합니다.
			{
				// 30초당 한번씩 저장해둠.
				if( TABS( pclClient->CurrentClock - dwDailyQuest3Clock ) >= 30000 )
				{
					dwDailyQuest3Clock = pclClient->CurrentClock;
					pclCI->clDailyQuest3Info.siLeftTime -= 30;		// 30초 줄여줌.

					if ( pclCI->clDailyQuest3Info.siLeftTime <= 0 )
					{
						pclCI->clDailyQuest3Info.siLeftTime = 0;
						cltItem clItem;
						clItem.Init();
						sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), 0, 0,
							pclCI->clDailyQuest3Info.siItemUnique , &clItem, 1,0,pclCI->clDailyQuest3Info.bHiddenQuest);
						cltServer *pclServer = (cltServer *)pclClient;
						pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
					else
					{
						if ( pclCI->clDailyQuest3Info.siMadeItemNum >= pclCI->clDailyQuest3Info.siItemNum)
						{
							SI32 value = 100;

							cltItem clItem;
							clItem.siUnique = pclCI->clDailyQuest3Info.siRewardItemUnique;
							clItem.siItemNum = ( pclCI->clDailyQuest3Info.siRewardItemNum * value ) / 100;

							cltItem clToItem;
							clToItem.Init();

							SI16 InvPos = -1;
							SI32 rtnvalue;

							// 쓸데 없는 이상 코드 삭제 - by LEEKH 2008-10-23
							//if( pclCI->clDailyQuest3Info.siQuestTime - pclCI->clDailyQuest3Info.siLeftTime)
							// 돈으로 주는경우
							if ( pclCI->clDailyQuest3Info.bMoneySelected )
							{
								sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos,
									pclCI->clDailyQuest3Info.siItemUnique ,&clItem, 1, pclCI->clDailyQuest3Info.bMoneySelected, pclCI->clDailyQuest3Info.bHiddenQuest);
								cltServer *pclServer = (cltServer *)pclClient;
								pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
							}
							else 
							{
								if ( pclCI->clDailyQuest3Info.bHiddenQuest == true ) 
								{
									// 금빛 상자
									cltItem clItem2;
									clItem2.siUnique	=	ITEMUNIQUE(13321)	;
									clItem2.siItemNum	=	1	;

									if( CheckItemForEmptyAnyItemSlotByHiddenQuesst(INVMODE_ALL, &clItem, &clItem2)  )
									{
										if ( CanAddInv( INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
										{
											sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos,
												pclCI->clDailyQuest3Info.siItemUnique ,&clItem, 1, pclCI->clDailyQuest3Info.bMoneySelected, pclCI->clDailyQuest3Info.bHiddenQuest);
											cltServer *pclServer = (cltServer *)pclClient;
											pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
										}
									}
									else
									{
										// 인벤 꽉 차서 안되므로...
										cltServer *pclServer = (cltServer *)pclClient;
										pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

										cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum , pclCI->clDailyQuest3Info.bHiddenQuest );
										cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
										pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);

									}
								}
								else
								{
									if ( CanAddInv( INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
									{
										sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos,
											pclCI->clDailyQuest3Info.siItemUnique ,&clItem, 1, pclCI->clDailyQuest3Info.bMoneySelected, pclCI->clDailyQuest3Info.bHiddenQuest);
										cltServer *pclServer = (cltServer *)pclClient;
										pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
									}
									else
									{
										// 인벤 꽉 차서 안되므로...
										cltServer *pclServer = (cltServer *)pclClient;
										pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

										cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum , pclCI->clDailyQuest3Info.bHiddenQuest );
										cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
										pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
									}
								}

							}
						}
						else
						{
							cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum, pclCI->clDailyQuest3Info.bHiddenQuest );
							cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}
			}
			else if( pclCI->clDailyQuest3Info.siItemUnique > 0 && pclCI->clDailyQuest3Info.bHiddenQuest == true )
			{
				if ( pclCI->clDailyQuest3Info.siMadeItemNum >= pclCI->clDailyQuest3Info.siItemNum )
				{
					SI32 value = 100;

					cltItem clItem;
					clItem.siUnique = pclCI->clDailyQuest3Info.siRewardItemUnique;
					clItem.siItemNum = ( pclCI->clDailyQuest3Info.siRewardItemNum * value ) / 100;

					cltItem clToItem;
					clToItem.Init();

					SI16 InvPos = -1;
					SI32 rtnvalue;

					if ( pclCI->clDailyQuest3Info.bHiddenQuest == true ) 
					{
						// 금빛 상자
						cltItem clItem2;
						clItem2.siUnique	=	ITEMUNIQUE(13321)	;
						clItem2.siItemNum	=	1	;

						if( CheckItemForEmptyAnyItemSlotByHiddenQuesst(INVMODE_ALL, &clItem, &clItem2)  )
						{
							if ( CanAddInv( INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
							{
								sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos,
									pclCI->clDailyQuest3Info.siItemUnique ,&clItem, 1, pclCI->clDailyQuest3Info.bMoneySelected, pclCI->clDailyQuest3Info.bHiddenQuest);
								cltServer *pclServer = (cltServer *)pclClient;
								pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
							}
						}
						else
						{
							// 인벤 꽉 차서 안되므로...
							cltServer *pclServer = (cltServer *)pclClient;
							pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

							cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum , pclCI->clDailyQuest3Info.bHiddenQuest );
							cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);

						}
					}
					else
					{
						if ( CanAddInv( INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
						{
							sDBRequest_DailyQuest3Del clMsg( pclCI->GetPersonID(), GetID(), true, InvPos,
								pclCI->clDailyQuest3Info.siItemUnique ,&clItem, 1, pclCI->clDailyQuest3Info.bMoneySelected, pclCI->clDailyQuest3Info.bHiddenQuest);
							cltServer *pclServer = (cltServer *)pclClient;
							pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
						}
						else
						{
							// 인벤 꽉 차서 안되므로...
							cltServer *pclServer = (cltServer *)pclClient;
							pclServer->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, GetCharUnique());

							cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum , pclCI->clDailyQuest3Info.bHiddenQuest );
							cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}


				}
				else
				{
					cltGameMsgResponse_DailyQuest3Change clinfo( pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.siMadeItemNum, pclCI->clDailyQuest3Info.bHiddenQuest );
					cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			for (SI32 i = 0; i < MAX_SUMMON_OWN; i++)
			{
				cltSummon *pSummon = pclCI->clSummonInfo.GetSummon(i);
				if (pSummon != NULL)
				{
					// PCK - ATB_SUMMONSTAMINASTATIC 속성이 없을때 자동회복이 되도록 추가함. (08.07.18)
					bool	bStaminaRecovery = true;
					cltKindInfo* pclKI = NULL;
					if( pclClient->pclKindInfoSet->IsValidKind(pSummon->siKind) )
					{
						if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
						{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[pSummon->siKind];	}
						else
						{	pclKI = pclClient->pclKindInfoSet->pclKI[pSummon->siKind];			}

						if( pclKI != NULL && pclKI->IsAtb(ATB_SUMMONSTAMINASTATIC) == TRUE )
						{
							bStaminaRecovery = false;
						}
					}

					if(bStaminaRecovery)
					{
						SI32 serverminutevary = pclClient->GetMinuteFromsTime(((cltServer*)pclClient)->sTime);

						if (pSummon->clIP.GetLuk() <= 0 && 
							TABS(pSummon->siTakeInMinute - serverminutevary) >= SUMMON_TAKEOUT_DELAY)
						{
							pSummon->siTakeInMinute = serverminutevary;

#ifdef _SAFE_MEMORY
							SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclCI->clCharItem.clItem[0], siID );
#else
							SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, pclCI->clCharItem.clItem, siID );
#endif
							pSummon->clIP.SetLuk( pclClient->GetMaxStaminaValue(summonskill, pSummon->siKind) );

							SetUpdateSwitch(UPDATE_SUMMON, true, 0);
							SendDBSummon(SETSUMMON_REASON_UPDATE, i);
						}
					}
				}
			}


			// 채팅 블록 처리
			if( m_stMuteTime.wYear > 0 )
			{
				SI64 siTimeDiff = TimeOperation(&m_stMuteTime, &pclserver->sTime);

				// 현재시간이 설정된 시간보다 나중이면 해제된다.
				if( siTimeDiff <= 0 )
				{
					ZeroMemory(&m_stMuteTime, sizeof(m_stMuteTime));

					// 마스터가 실행하는 경우에만 CharID를 설정한다.
					sDBRequest_SetMuteTime clMsg(0, pclCI->GetPersonID(), &m_stMuteTime);
					pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
				}
			}
	}

	//---------------------------------
	// 인벤에 물품 추가 예약 정보 갱신 
	//---------------------------------
	if((pclClient->GetFrame() / CHAR_ACTION_INTERVAL_FRAME) % 50 == 0)
	{
		InputItemReserveAction();
	}

	// 물품 생산
	if(bMakeItemReserveSwitch)
	{
		if(TABS(pclClient->CurrentClock - dwMakeItemStartClock) > (int)dwMakeItemDelayClock)
		{
			bMakeItemReserveSwitch = false;
			if ( bMakeItemNoMinigame == true )
			{
				bMakeItemNoMinigame = false ;
				MakeItem(pclReservedMakeItemData);
				bMakeItemSwitch = true ;
			}

			if(bEnchantItemSwitch ==true)
			{
				bEnchantItemSwitch = false ;
				EnchantItem(pclReservedMakeItemData);
				bFinishEnchantItemSwitch = true ;
			}

			//-------------------------------------------
			// 클라이언트로 지연 시간을 통보한다. 
			//-------------------------------------------
			cltGameMsgResponse_MakeItemDelay clinfo(0);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMDELAY, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}


	}
	else if ( bMakeItemMinigameSwitch && !bMakeItemNoMinigame && !bMakeItemSwitch )
	{
		bMakeItemMinigameSwitch = false ;
		MakeItem(pclReservedMakeItemData);
		bMakeItemSwitch = true ;
	}

	/*cyj 박대박게임 삭제
	// 박대박 게임
	if( bRouletteStart )
	{
		if(TABS(pclClient->CurrentClock - dwRouletteStartClock) > (int)dwRouletteDelayClock)
		{
			SI32 TicketPos = -1;
			SI32 TicketNum = 0;

			TicketPos = pclCI->clCharItem.GetItemPos(8200);
			TicketNum = pclCI->clCharItem.GetItemNum(8200);

			if(TicketNum >= m_siBettingCount && TicketPos >= 0)
			{
				// 흥부박을 소비한다.
				//////////////////////////////////////////////////////////////////////////
				cltItem clItem;
				clItem.Init();
				clItem.siUnique = 8200;
				clItem.siItemNum = m_siBettingCount;

				SI32 FromPersonID = pclCI->GetPersonID();

				cltServer* pclserver = (cltServer*)pclClient;
				sDBRequest_UseItem clMsg( GetID(), FromPersonID, TicketPos, &clItem ,USEITEM_REASON_ROULLET);
				pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				//////////////////////////////////////////////////////////////////////////

				CheckRoulette();

				bool bLotto = false;
				bLotto = CheckLottoRoulette();

				SI16 siResult = 0;
				SI16 siNumber = 0;

				SI32 ItemUnique = 8200;	// 흥부박

				if( bLotto )
				{
					siNumber = 100;
					GiveItem(ItemUnique, siNumber, INPUTITEMPERSON_OPTION_ROULETTEGAME,0);
					siResult = 2;

					cltCharServer* pclchar = (cltCharServer*)pclCM->CR[GetID()];
					cltServer* pclserver = (cltServer*)pclClient;

					cltItem clItem;
					// 캐쉬템을 준다
					SI32 itemunique = pclClient->pclItemManager->GetRandBigWarItem();
					//SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
					if(itemunique > 0)
					{
						//clItem.Set(& pclClient->pclItemManager->pclItemInfo[ref]->clItem);
						bool RareSwitch = false;
						if ( pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clItem, 0, &RareSwitch,
							0,0,0,0,0,14 ) )
						{
							SI32 rtnvalue = 0;
							if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_ROULETTEGAME, &rtnvalue) == false)
							{
								// 인벤에 빈자리가 없어서 추가할 수 없다. 
								if(rtnvalue == CANADDINV_FAIL_FULL)
								{
									pclserver->SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
								}

								pclClient->pclLog->FilePrint(TEXT("Config\\RouletteGame.Txt"), TEXT("Lotto User : [%s] / BettingCount : [%d]  / UserGet : [%d]"), pclCM->CR[GetID()]->GetName(), m_siBettingCount, siNumber);
							}	
						}
					}
				}
				else 
				{
					if( m_siResultCount > 0 )
					{
						siNumber = m_siResultCount*3;
						GiveItem(ItemUnique, siNumber, INPUTITEMPERSON_OPTION_ROULETTEGAME,0);
						siResult = 1;

						pclClient->pclLog->FilePrint(TEXT("Config\\RouletteGame.Txt"), TEXT("Normal User : [%s] / BettingCount : [%d] / UserGet : [%d]"), pclCM->CR[GetID()]->GetName(), m_siBettingCount, siNumber);
					}
					else
					{
						pclClient->pclLog->FilePrint(TEXT("Config\\RouletteGame.Txt"), TEXT("Normal User : [%s] / BettingCount : [%d] / UserGet : [%d]"), pclCM->CR[GetID()]->GetName(), m_siBettingCount, siNumber);
					}
				}

				cltGameMsgResponse_RouletteGame_Result clinfo(m_siRandomValue, siResult, siNumber);
				cltMsg clMsg2(GAMEMSG_RESPONSE_ROULETTEGAME_RESULT, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg2);
			}

			bRouletteStart = false;

			m_siBettingCount = 0;
			m_siResultCount = 0;
			dwRouletteStartClock = 0;
			dwRouletteDelayClock = 0;
			SI32 x = 0, y = 0;
			for( y = 0 ; y< 5; ++y )
			{
				m_siRandomValue[y] = 0;	// 선택될 랜덤값 0

				for( x = 0; x < 5; ++x )
				{
					m_stRouletteTable[y][x].m_bUserSelect = false;
					m_stRouletteTable[y][x].m_bCpuSelect  = false;
					m_stRouletteTable[y][x].m_bResult     = false;

					m_stRouletteTable[y][x].m_siX = 0;
					m_stRouletteTable[y][x].m_siY = 0;
					m_stRouletteTable[y][x].m_siValue = y*5 + (x + 1);
				}
			}

		}

	}
	*/
}



// 서버 캐릭터의 행동. 
void cltCharServer::CharServerAction()
{
	// 독, 얼음 등의 서버 캐릭터 처리. 
	if(TABS(pclClient->CurrentClock - clSimpleVary.dwlastCheckCharServerStatusActionClock) > 1000)
	{
		clSimpleVary.dwlastCheckCharServerStatusActionClock = pclClient->CurrentClock;
		CharServerStatusAction();

	}
	// 공간이동 
	if(IsWarpStatus())
	{
		Warp();
	}

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		//[진성] 엘릭서 기간이 넘어 삭제.
		if( pcltElixir && pcltElixir->IsElixir() )
		{
			if( pcltElixir->GetMinuteVary() < ((cltServer*)pclClient)->pclTime->clDate.GetMinuteVary() )
			{
				if(pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( GetID(), pclCI->GetPersonID() );
					((cltServer*)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
				}
			}
		}
	}

	
	if( pclClient->IsCountrySwitch( Switch_SkillBook ) )
	{
		//[진성] 스킬북 마법을 시간이 지나면 삭제한다.
		if( pclCharSkillBookInfo )
		{
			if( pclCharSkillBookInfo->IsTimeOver( this ) )
			{
				ParametaBoxAction();
			}
		}

		if( m_clCharCurseEffect.IsTimeOver( GetID() ) )
		{
			ParametaBoxAction();
		}
	}


	//----------------------------------
	// 마법 지연을 증가시킨다. 
	//----------------------------------
	siMagicDelay += CHAR_ACTION_INTERVAL_FRAME;

	m_clMagicBufMgr.DecFrame( CHAR_ACTION_INTERVAL_FRAME );

	//----------------------------------
	// NPC인 경우 
	//----------------------------------
	if(IsNPC(GetCharUnique()) || IsInstanceNPC(GetCharUnique()))
	{
		//===================================
		// SUMMON : 소환수는 주인을 따라간다.
		//===================================
		if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			if(GetMovePercent() == 0)
			{
				SummonFollowHost();
			}

			SummonAutoHeal();

			CharServerAction_Summon();

		}
		//===================================
		// 수호정령 주인을 따라간다
		//===================================
		else if ( IDENTITY_SOULGUARD == clIdentity.siIdentity )
		{
			if(GetMovePercent() == 0)
			{
				SoulGuardFollowHost();
			}

			CharServerAction_SoulGuard();
		}

		if(TABS(pclClient->CurrentClock - clSimpleVary.dwLastCheckCharServerNPCActionClock) > 3000)
		{
			clSimpleVary.dwLastCheckCharServerNPCActionClock = pclClient->CurrentClock;

			CharServerAction_NPC();
		}
	}
	// 사용자이면, 
	else if( IsPC(GetCharUnique()) )
	{
		CharServerAction_PC();

	}


}

//[추가 : 황진성 2007. 12. 11 신년트리 설치한 마을에 주민 버프효과 주기. 현재 사용안함]
void cltCharServer::NewYearTreeEft(SI32 _VillageUnique)
{
	SI32			id		= 0;
	SI32			index	= 0;
	SI32			Add	    = 0;
	cltCharServer*	pclchar = NULL;

	while(id = pclCM->GetCharOrder(index))
	{
		index++;
		pclchar = (cltCharServer*)pclCM->CR[id];
		if(pclchar->GetSession())
		{
			// 같은 마을 주민이어야 한다. 
			if(pclchar->pclCI->clBI.siHomeVillage == _VillageUnique)
			{
				Add = pclchar->pclCI->clIP.GetLevel() / 10;

				pclchar->clPB.siGeneralAC	  += Add;
				pclchar->clPB.siGeneralDamage += Add;
			}

			// 클라이언트에게 알린다. 
			cltGameMsgResponse_GeneralEft clinfo(pclchar->GetCharUnique(), pclchar->clPB.siGeneralAC, pclchar->clPB.siGeneralDamage);
			cltMsg clMsg(GAMEMSG_RESPONSE_GENERALEFT, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
	}
}


// 지휘 효과를 설정한다. 
void cltCharServer::GeneralEft(bool bacswitch, SI32 acuprate, bool bdamageswitch, SI32 damageuprate , bool alluser)
{
	// 마을 주민이 아니면 작동하지 않는다. 
	if(pclCI->clCharRank.siVillageUnique <= 0 && alluser == false)return ;


	SI32 id;

	SI32 index = 0;
	while(id = pclCM->GetCharOrder(index))
	{
		index++;

		// 자기 자신은 해당되지 않는다. 
		if(id == GetID())continue;


		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if(pclchar->GetSession())
		{

			// 같은 마을 주민이어야 한다. 
			if(pclchar->pclCI->clBI.siHomeVillage == pclCI->clCharRank.siVillageUnique || alluser == true )
			{
				// 같은 지역에 있어야 한다. 
				if(pclchar->GetMapIndex() == GetMapIndex() && max(TABS(pclchar->GetX() - GetX()), TABS(pclchar->GetY() - GetY()))  < 20 )
				{

					bool btempacswitch		= false;
					bool btempdamageswitch	= false;

					//-------------------------------------
					// 방어력 향상 
					// 기존의 지휘효과보다 높아야..
					//-------------------------------------
					if(bacswitch)
					{
						pclchar->clPB.siGeneralAC		= acuprate;
						pclchar->clPB.dwGeneralACClock	= pclClient->CurrentClock;

						// 자신의 레벨이 낮을수록 보너스 수치가 증가한다.					

						if(pclchar->clPB.pclIP->GetLevel() <20)
							pclchar->clPB.siGeneralAC += 30;
						else if(pclchar->clPB.pclIP->GetLevel() <30)
							pclchar->clPB.siGeneralAC += 20;
						else if(pclchar->clPB.pclIP->GetLevel() <40)
							pclchar->clPB.siGeneralAC += 10;

						btempacswitch = true;
					}

					//-------------------------------------
					// 데미지 향상. 
					// 기존의 지휘효과보다 높아야..
					//-------------------------------------
					if(bdamageswitch)
					{
						pclchar->clPB.siGeneralDamage		= damageuprate;
						pclchar->clPB.dwGeneralDamageClock	= pclClient->CurrentClock;

						// 자신의 레벨이 낮을수록 보너스 수치가 증가한다.					

						if(pclchar->clPB.pclIP->GetLevel() <20)
							pclchar->clPB.siGeneralDamage += 30;
						else if(pclchar->clPB.pclIP->GetLevel() <30)
							pclchar->clPB.siGeneralDamage += 20;
						else if(pclchar->clPB.pclIP->GetLevel() <40)
							pclchar->clPB.siGeneralDamage += 10;

						btempdamageswitch = true;
					}

					if(btempacswitch || btempdamageswitch)
					{
						// 클라이언트에게 알린다. 
						cltGameMsgResponse_GeneralEft clinfo(pclchar->GetCharUnique(), pclchar->clPB.siGeneralAC, pclchar->clPB.siGeneralDamage);
						cltMsg clMsg(GAMEMSG_RESPONSE_GENERALEFT, sizeof(clinfo), (BYTE*)&clinfo);
						pclchar->SendNeighbourMsg(&clMsg, true);
					}


				}
			}
		}
	}

}



//------------------------------------
// 공간이동 관련 
//------------------------------------
void cltCharServer::InitWarpInfo()
{
	clCharWarpInfo.Init();
}

void cltCharServer::SetWarpInfo(const cltWarpInfo* pclCharWarpInfo, SI32 warpunique)
{
	clCharWarpInfo.Set(pclCharWarpInfo);
	siWarpUnique	= warpunique;
}

// 특정 마을로 워프하게 한다. 
void cltCharServer::SetWarpToVillage(cltMapManager* pclmapmanager, SI16 villageunique, SI32 warpunique)
{
	SI32 id = GetID();
	//박춘기 - 07.07.24 : 캐릭터가 죽으면 이동하지 않는다.
	if (pclCM->IsAlive(id) == false) return;

	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;


	SI32 maptypeunique	= pclmapmanager->pclMapArray[villageunique]->siMapUnique;
	if(maptypeunique < 0 || maptypeunique >= MAX_MAPTYPE_NUMBER)		return;

	SI32 x				= pclmapmanager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
	SI32 y				= pclmapmanager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

	OrderStop(GetID(), BY_COMPUTER);

	cltWarpInfo clWarpInfo(1, villageunique, false, false, x, y, -1, -1);
	SetWarpInfo(&clWarpInfo, warpunique);
}


bool cltCharServer::IsWarpStatus()
{

	if(clCharWarpInfo.GetWarpSwitch() == false)return false;

	if(clCharWarpInfo.GetGateX() == -1)
	{
	}
	else
	{

		SI32 length = max( TABS(GetX() - clCharWarpInfo.GetGateX()), TABS(GetY() - clCharWarpInfo.GetGateY()) );
		if(length >= 12)
		{
			return false;
		}

	}

	if (clCharWarpInfo.GetWarpSwitch() == 0 )
		return false;
	else return true ;
}
// 공간 이동시킨다. 
BOOL cltCharServer::Warp(bool bwritelog /* = false */)
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 id = GetID();

	//================================================================
	// 배틀로얄
	//================================================================
	CBattleRoyalMgr* pclBattleRoyalMgr = pclserver->m_pclBattleRoyalMgr;
	CBattleRoyal* pclBattleRoyal = NULL;
	SI32 siDstMapIndex = clCharWarpInfo.GetMapIndex();
	if( NULL != pclserver->m_pclBattleRoyalMgr)
	{
		pclBattleRoyal = pclBattleRoyalMgr->GetBattleRoyal(this);
		if( NULL != pclBattleRoyal)
		{
			// 경기장에서 워프 해서 나가기 불가능
			if( (pclBattleRoyal->GetStadiumMapIndex() == GetMapIndex()))
			{
				if(siKilledMode == KILLEDMODE_BATTLEROYAL)
				{
					clCharWarpInfo.uiMapIndex = MAPINDEX_MAINFIELD;
					clCharWarpInfo.uiX = 499;
					clCharWarpInfo.uiY = 258;

					pclCI->clBI.uiGMMode = GMMODE_ATB_NONE;
					pclBattleRoyal->RestorChar(this);
				}
				else
				{
					if( pclBattleRoyal->IsGamingState())
					{
						return FALSE;
					}
					else
					{
						pclCI->clBI.uiGMMode = GMMODE_ATB_NONE;
						pclBattleRoyal->RestorChar(this);
					}

				}
			}

			// 걍제로 말 태우기
			if( pclBattleRoyal->GetStadiumMapIndex() == siDstMapIndex )
			{
				pclBattleRoyal->TakeinHorse(this);
				if(FALSE == pclBattleRoyal->TransformChar(this))
				{
					clCharWarpInfo.uiMapIndex = MAPINDEX_MAINFIELD;
					clCharWarpInfo.uiX = 499;
					clCharWarpInfo.uiY = 258;
				}
			}
		}
	}

	// 지도를 확인한다. 
	if(GetMapIndex() == 0)
	{
		pclCI->clBI.clLastMainMapPos.Set(GetX(), GetY());
	}

	//================================================================
	// 소환수 선택 관련을 초기화한다.
	//================================================================
	siSelectedCharIndex = -1 ;

	//====================================================================================
	// 워프해서 갈 마을에서 개인상점의 최대 갯수를 넘지 못한다.
	//====================================================================================
	if ( bPersonalShopSwitch == true &&  
		pclClient->pclMapManager->pclVillageManager->IsValidVillage(clCharWarpInfo.GetMapIndex()) == true )
	{
		CMinisterHozo *pclminister = (CMinisterHozo *)((cltServer*)pclClient)->pclMinisterMgr->GetMinister(MINISTER_HOZO);
		SI32 siShopNum = pclClient->pclMapManager->pclVillageManager->GetPersonalShopNumber(clCharWarpInfo.GetMapIndex());
		SI08 siShopMode = pclClient->pclMapManager->pclVillageManager->GetPersonalShopNumber(clCharWarpInfo.GetMapIndex());
		if(pclminister  && siShopNum >= pclminister->GetMaxShopNum() )
		{
			bPersonalShopSwitch = false;

			// 설정 정보를 설정한다.
			cltGameMsgResponse_StartPersonalShop clinfo(GetCharUnique(), -4,false, PSHOP_MODE_NONE );
			cltMsg clMsg(GAMEMSG_RESPONSE_STARTPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	//====================================================================================

	cltMapCommon* pclmap	= pclClient->pclMapManager->GetMapPointer(clCharWarpInfo.GetMapIndex());
	if(pclmap == NULL)return FALSE;

	//====================================================================================
	// 개인상점 개설 중 워프해서 갈 지역이 개인상점 불가 지역이라면 개인상점을 강재로 종료한다
	//====================================================================================
	if ( (true == bPersonalShopSwitch) || (true == bPremiumPersonalShop) )
	{
		if ( false == pclClient->pclMapManager->IsCanMarketOpenMap(clCharWarpInfo.GetMapIndex()) )
		{
			SetPersonalShopBanner( NULL );
			SetPersonalShopData( false, NULL );

			// 개인상점이 종료 되었다고 알려줌
			pclserver->SendServerResponseMsg( 0, SRVAL_NOTICE_CLOSE_PERSONALSHOP_BY_WARP, 0, 0, GetCharUnique() );
		}
	}

	SI32 mapindex = -1, x, y;
	if(clCharWarpInfo.uiForceSwitch)
	{
		mapindex	= clCharWarpInfo.GetMapIndex() ;
		x			= clCharWarpInfo.GetX();
		y			= clCharWarpInfo.GetY();
	}
	else
	{

		mapindex = clCharWarpInfo.GetMapIndex() ;

		// 워프 해가야 할 곳의 적절한 빈 곳을 찾는다. 
		if(pclmap->FindEmptyAreaForCharLocate(GetKind(), clCharWarpInfo.GetX(), clCharWarpInfo.GetY(), 30, &x, &y, false) == false)
		{
			TCHAR* pText = GetTxtFromMgr(2818);
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), pText, 
										pclCI->GetPersonID(), GetName(), clCharWarpInfo.GetMapIndex(), clCharWarpInfo.GetX(), clCharWarpInfo.GetY());

			
			// 캐릭터를 경복궁으로 강제 워프시킨다. 
			mapindex = MAPINDEX_PALACE;
			x	= 27;
			y	= 87;
		}
	}

	if(mapindex < 0)
	{
		return FALSE;
	}

	// 유저 입장 제한이 있는 맵이라면..
	SI32 userLimit = pclClient->pclMapManager->GetUserLimit(mapindex);
	if ( IsPC(GetID()) && userLimit > 0 &&
		pclClient->pclMapManager->IsInstanceMap(mapindex) == false )
	{
		if ( pclClient->pclMapManager->GetUserCount(mapindex) >= userLimit )
		{
			// 클론맵이 있는지 확인한다.
			SI32 cloneMapIndex = pclClient->pclMapManager->GetCloneMap( mapindex );
			if ( cloneMapIndex )
			{
				mapindex = cloneMapIndex;
			}
		}
	}

	if( mapindex == MAPINDEX_PALACE )
	{
		if ( pclClient->siServiceArea == ConstServiceArea_China )
		{
			switch( rand() % 3 )
			{
				case 0:	x = 17; y = 87; break;
				case 1:	x = 37; y = 87; break;
				case 2:	x = 27; y = 96; break;
			}
		}
		else
		{
			x = rand()%7 + 24;
			y = rand()%23 + 68;                
		}
	}

	// 이전의 지도상의 캐릭터의 정보를 삭제한다. 
	BOOL boldsetidswitch = SetIDSwitch;
	DeleteID();

	// 캐릭터를 워프시킨다. 
	pclCI->clBI.SetMapIndex(mapindex);
	pclMap	= pclClient->pclMapManager->GetMapPointer( mapindex );
	SetX(x);
	SetY(y);

	// 캐릭터의 현재 지도상 정보를 다시 표시한다.

	if(boldsetidswitch)
	{
		SetID();
	}

	clMoveInfo.siMovePercent	= 0;
	bBusySwitch					= false;

	//====================================================================================
	// 캐릭터를 정지시킨다. 
	OrderStop(GetID(), BY_PLAYER);

	// 머릿말 채팅을 없앤다. 
	SetHeadChat(false, NULL);

	//====================================================================================

	cltOrderDataInfo clOrder;
	clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);

	// 외부 장비.
	cltShapeEquipInfo clequip;
	if(IsPC(GetCharUnique()))
	{
		GetShapeEquipInfo(&clequip);
	}


	UI32 uiRequestAddinfo = 0;
	//if(clIdentity.siIdentity) uiRequestAddinfo = 1; 
	//IDENTITY_CASTLE:
	//IDENTITY_VILLAGEGOD: 
	//IDENTITY_VILLAGEGOD_SUMMON:
	//IDENTITY_PERSON_SUMMON:
	//IDENTITY_VILLAGEHUNT:			
	//KHY - 1001 - 기승동물 5마리 보유 수정.
	// 이 캐릭터에게 지도가 변경되었기 때문에 다시 로그인을 해야 함을 통보한다. 
	SI32 siHorseUnique		= 0;
	SI32 siAddStatusDate	= 0;
	SI32 siTicketNum		= 0;
	// 프리미엄 파츠 장착 여부
	SI32 siPremiumpartsslot1		= 0;
	SI32 sipremiumpartsuniqueslot1	= 0;
	SI32 siPremiumpartsslot2		= 0;
	SI32 sipremiumpartsuniqueslot2	= 0;
	SI32 siPremiumpartsslot3		= 0;
	SI32 sipremiumpartsuniqueslot3	= 0;
	SI32 siPremiumpartsNum			= 0;

	cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclHorse != NULL)
	{
		siHorseUnique				= pclHorse->siHorseUnique;
		siAddStatusDate				= pclHorse->clAddStatusDate.GetDateVary();
		siTicketNum					= pclHorse->siStatusTicketNum;

		siPremiumpartsslot1			= pclHorse->clPremiumPartsDate_Slot1.GetDateVary();
		sipremiumpartsuniqueslot1	= pclHorse->siPremiumUnique_Slot1;

		siPremiumpartsslot2			= pclHorse->clPremiumPartsDate_Slot2.GetDateVary();
		sipremiumpartsuniqueslot2	= pclHorse->siPremiumUnique_Slot2;

		siPremiumpartsslot3			= pclHorse->clPremiumPartsDate_Slot3.GetDateVary();
		sipremiumpartsuniqueslot3	= pclHorse->siPremiumUnique_Slot3;

		siPremiumpartsNum			= pclHorse->siPremiumPartsNum;
	}

	//[진성] 파티홀. 파티장에서 받은 아이템을 삭제. => 2008. 3. 12
	PartyHallItemRemove( id );

	if( !pclClient->IsCountrySwitch( Switch_Festival_Food ) )
	{
		//[진성] 축제음식 아이템 삭제.
		FestivalFoodItemRemove( id );
	}

	//[진성] 네잎크로버가 현재 사용할수 없는 거면 삭제 => 2008-8-14
	if( pclClient->IsCountrySwitch( Switch_FourLeaf ) )
	{
		NotFourLeafItemRemove( id );
	}

	SI32 BufTransformKind = 0;
	if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) )
	{
		stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf( BUF_TRANSFORM );
		if(pclBuf)		BufTransformKind = pclBuf->siPercent;
	}

	/*if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM_HORSE ) )
	{
		stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf( BUF_TRANSFORM_HORSE );
		if(pclBuf)		BufTransformKind = pclBuf->siPercent;
	}*/

	// pvp 중 워프 하면 지는거다. - 변신 워프 제외	
	if ( siWarpUnique != 10000 	&& pclCM->CR[id]->siEnemUnique > 0 && pclCM->CR[id]->GetPVP_LeagueEnemyPersonID() <= 0 ) 
	{
		SI32 siWarpChar	= id;													// 워프한 케릭터 질 케릭터.
		if( pclCM->IsValidID( id ) == false )	return	false;					// 정상 아이디 인지 검사 부터 
		
		SI32 siWarpChaeParentID = pclCM->CR[id]->GetSummonParentID();			// 워프탄 케릭터의 부모 케릭터를 구한다.
		if ( siWarpChaeParentID == 0 ) siWarpChaeParentID = id;					// 만약 워프탄 케릭터가 본케면 그냥 아이디를 쓴다.
		
		cltCharServer* pclWarpChar = pclCM->GetCharServer(siWarpChaeParentID);	
		if(pclWarpChar == NULL)	return false;
		
		SI16 siWinnerCharID = pclWarpChar->siEnemUnique;						// 워프 타서 졌으므로 워프탄 케릭터의 상대방 적은 무조건 이긴 케릭터이다.
		if( pclCM->IsValidID( siWinnerCharID ) == false ) return	false;		// 정상 아이디 인지 검사 부터
		
		cltCharServer* pclWinnerChar = pclCM->GetCharServer(siWinnerCharID);	
		if(pclWinnerChar == NULL) return false;

		// 워프 탓으니까 전투는 끝이다.
		pclWarpChar->siEnemUnique	=	0;		// 각각의 케릭터 들을 초기화 해준다
		pclWinnerChar->siEnemUnique	=	0;
		if( pclClient->IsCountrySwitch( Switch_ValenTineWar ) )
		{
			//발렌타인데이 전쟁 관련 체크, 커플이나 솔로라고 정했고, 아이템을 받지 않았을 경우에만 준다.
			SI32 siCouple  = pclWinnerChar->pclValentineWar->GetCouple();	// 이긴 사람의 커플 여부
			SI32 siLoser   = pclWarpChar->pclValentineWar->GetCouple();		// 진 사람의 커플 여부
			bool bGetPrize = pclWinnerChar->pclValentineWar->GetPrize();	// 이긴사람이 아이템을 받았었는지
			if(  abs(pclWarpChar->pclCI->clIP.GetLevel() - pclWarpChar->pclCI->clIP.GetLevel() ) < 11
				&& siCouple != 0 && siLoser != 0
				&& siCouple != siLoser 
				&& bGetPrize == false )
			{
				SI32 siRewardItemUnique	=	ITEMUNIQUE(2781) ;
				if( siRewardItemUnique ) 
				{
					cltItem clItem;
					SI16 brareswitch = 0;
					if ( pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique,&clItem,0,0,&brareswitch,0,0,0,0,0) == true ) 
					{
						clItem.siItemNum = 1;
						SI32 rtnvalue = 0;
						if(pclWinnerChar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, &rtnvalue))
						{
							// 아이템을 주고 줬다고 셋팅 해준다.
							sDBRequest_Valantine_Get_Prize clMsg( pclWinnerChar->pclCI->GetPersonID(), true );
							pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
						}
						else
						{
							if(rtnvalue == CANADDINV_FAIL_FULL)
							{
								sDBRequest_PostOfficeMasterSendItem clMsg( INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, 0, (TCHAR*)pclWinnerChar->GetName(), &clItem, &pclserver->pclTime->clDate );
								pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
								// 아이템을 주고 줬다고 셋팅 해준다.
								sDBRequest_Valantine_Get_Prize clMsg2( pclWinnerChar->pclCI->GetPersonID(), true );
								pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
							}
						}
					}		
				}
			}
		}
		// 각기 클라이언트로 알려준다.
		{//승리자
			// 개인간 pvp가 끝나면서 각종 중독상태 제거
			pclWinnerChar->DeletePoison();						// 중독 상태를 삭제한다.
			pclWinnerChar->DeletePoisonSetItemEffect();			// 중독 상태를 삭제한다.
			pclWinnerChar->DeleteIce();							// 얼음 상태를 삭제한다.
			pclWinnerChar->DeleteCurseAttack();					// 공격력이 저하 상태를 삭제한다.
			pclWinnerChar->DeleteCurseCritical();				// Critical 확률이 낮아지는 상태를 삭제한다.
			pclWinnerChar->DeleteCurseDefense();				// 방어력이 낮아지는 상태를 삭제한다.
			pclWinnerChar->DeleteCurseMovespeed();				// 이동속도 저하 상태를 삭제한다.
			pclWinnerChar->DeleteMagicFire();					// 불에 타는 상태를 삭제한다.
			pclWinnerChar->DeleteFrozen();						// 보스 얼음 상태를 삭제한다.
		}
		{	// 패배자
			// 개인간 pvp가 끝나면서 각종 중독상태 제거
			pclWarpChar->DeletePoison();						// 중독 상태를 삭제한다.
			pclWarpChar->DeletePoisonSetItemEffect();			// 중독 상태를 삭제한다.
			pclWarpChar->DeleteIce();							// 얼음 상태를 삭제한다.
			pclWarpChar->DeleteCurseAttack();					// 공격력이 저하 상태를 삭제한다.
			pclWarpChar->DeleteCurseCritical();					// Critical 확률이 낮아지는 상태를 삭제한다.
			pclWarpChar->DeleteCurseDefense();					// 방어력이 낮아지는 상태를 삭제한다.
			pclWarpChar->DeleteCurseMovespeed();				// 이동속도 저하 상태를 삭제한다.
			pclWarpChar->DeleteMagicFire();						// 불에 타는 상태를 삭제한다.
			pclWarpChar->DeleteFrozen();						// 보스 얼음 상태를 삭제한다.
		}
		// 승리자
		cltGameMsgResponse_PVP_Request clWinner( END_PVP , WIN_PVP, pclWinnerChar->GetCharUnique(), TEXT("") );	
		cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
		pclWinnerChar->SendNeighbourMsg(&clMsg, true);

		pclWinnerChar->IncQuestPara( QUEST_CLEAR_COND_PVPWIN, 0, 1 );

		// 패배자
		cltGameMsgResponse_PVP_Request clclLoser( END_PVP , LOSE_PVP, pclWarpChar->GetCharUnique(), TEXT("") );
		cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclLoser), (BYTE*)&clclLoser );
		pclWarpChar->SendNeighbourMsg(&clMsg2, true);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 손서웅ㅇ 2008. 10. 29] // 워프로 패배
			// PCK : 수정 - PersonID로 캐릭터이름을 구해서 좀더 보기 쉽게한다. (09.07.31)
			// para1	:	승리자 personID
			// para2	:	패배자 personID

			TCHAR szCharName[100];
			ZeroMemory(szCharName, sizeof(szCharName));
			StringCchPrintf(szCharName, sizeof(szCharName), TEXT("WinnerChar:%s, LoserChar:%s"), pclWinnerChar->GetName(), pclWarpChar->GetName());

			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_END_WARP, 
											0, this, 0 , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclWinnerChar->pclCI->GetPersonID(), 
											pclWarpChar->pclCI->GetPersonID(), 0, 0, 0, szCharName, NULL);
		}
		{
			// 서버에 남긴다.
			TCHAR fileNameBuffer[256];
			//슬롯에 찍을 시간을 텍스트로 완성한다.
			TCHAR		szTime[128];
			TCHAR		szBuffer0[128];
			SYSTEMTIME	stTimeInfo;
			GetLocalTime(&stTimeInfo);
			StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
			StringCchPrintf( szBuffer0, sizeof(szBuffer0), "%s", &szTime ) ;
			StringCchPrintf( fileNameBuffer, sizeof(fileNameBuffer), TEXT("Config\\PVPLog_%04d%02d%02d.log"), 
							 stTimeInfo.wYear, stTimeInfo.wMonth, stTimeInfo.wDay );
			 pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), TEXT(" PVPEND_WARP \tWINOPERSON : \t[%s]\t \t LOSEPERSON2 : \t[%s]\t Time"),
											pclWinnerChar->GetName(), pclWarpChar->GetName(), szBuffer0 );
		}
	}

	// 아래 표시될 애정도 레벨은 두 캐릭터 접속 상태에 따라 아에 안보이게 될수도 있다
	SI16 siDisplayLoveLevel	= 0;
	//BOOL bSameMap			= FALSE;

	SI16 siConnectMode		= MARRIAGE_MATE_CONNECT_MODE_NONE;

	//SI16 siSameMap			= 0;
	SI16 siLoveLevel		= 0; 

	// [영훈] 결혼상태라면 워프시 두 캐릭터가 동일 맵상에 존재 하는지 검사한다
	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		if ( (pclMarriage) && (TRUE == IsMarried()) )
		{
			siLoveLevel	= pclMarriage->GetLoveLevel(); 
			//
			SI32			siMateCharID	= pclClient->pclCM->GetIDFromPersonID( pclMarriage->GetMatePersonID() );
			cltCharServer*	pclMateChar		= pclClient->pclCM->GetCharServer( siMateCharID );

			// 캐릭터가 접속해 있다면 같은 맵에 있는지 검사
			if ( (pclMateChar) && (pclMateChar->IsMarried()) && (pclMateChar->pclMarriage->GetMatePersonID() == pclCI->GetPersonID()) )
			{
				siConnectMode = MARRIAGE_MATE_CONNECT_MODE_CONNECT;

				// 같은 맵에 있다
				if ( GetMapIndex() == pclMateChar->GetMapIndex() )
				{
					siConnectMode = MARRIAGE_MATE_CONNECT_MODE_SAMEMAP;

					// 보여지게될 애정도 레벨은 현재 레벨과 동일
					siDisplayLoveLevel = pclMarriage->GetLoveLevel();
				}

				// 내 캐릭터의 정보는 아래에서 보내주지만
				// 현재 남아있는 캐릭터의 정보는 안보내주기 때문에 그 정보도 함께 보내줘야 한다
				if ( (pclMateChar->pclMarriage) && (pclMateChar->pclMarriage->GetConnectMode() != siConnectMode) )
				{
					pclMateChar->pclMarriage->SetConnectMode( siConnectMode );
					
					cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_DISPLAYLOVELEVEL, false, siDisplayLoveLevel );
					cltGameMsgResponse_StatusInfo	clInfo( pclMateChar->GetCharUnique(), &clChangeInfo );

					cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo );
					pclMateChar->SendNeighbourMsg( &clStatusInfoMsg, false );

					// 배우자에게는 접속 정보와 애정도를 같이 보낸다
					pclserver->SendServerResponseMsg( 0, SRVAL_SET_MARRY_WITHSAMEMAP, siConnectMode, siLoveLevel, pclMateChar->GetCharUnique() );
				}
			}	// if ( pclMateChar )
		}	// if ( (pclMarriage) && (TRUE == IsMarried()) )
	}	// if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )

	cltMakeCharInfo	clMakeCharInfo(GetKind(), 
									CharUnique, 
									pclCI->clIP.GetLevel(), 
									pclCI->clIP.GetLife(), 
									GetX(), 
									GetY(), 
									GetMapIndex(), 
									siChildCharUnique, 
									siSummonIndex, 
									bHeadChatSwitch, // 머릿말이 존재하는가?
									bPersonalShopSwitch,		
									bNoFirstAttackSwitch | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK) | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI) | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) | pclCI->clBI.clBufInfo.IsHaveBufExecptGetType(BUF_TRANSFORM,BUF_GET_TYPE_NIGHTMARKET) ,
									bNoIceAttackSwitch,
									pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) && pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FRIENDSHIP),
									pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FOURLEAF) ,
									pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FARMINGNMININGFOREVER),
									IsHaveCushionItem() ,
									pclCI->clBI.uiSex, 
									&clequip, 
									pclCI->clHorseInfo.siCurrentShowHorse,
									clPB.GetTotalMoveSpeed(),
									clJim.siJimHostCharUnique,
									GetGameMasterLevel(),
									pclClient->pclMapManager->pclMapArray[GetMapIndex()]->siMapUnique,
									siHorseUnique,
									pclCI->clBI.siHomeVillage,
									pclCI->clBI.siSchoolUnique,
									&pclCI->clCharRank, 
									siAddStatusDate,
									siTicketNum,
									&clOrder,
									&clIdentity, 
									&clInnerStatus,
									uiRequestAddinfo,
									clCharWarpInfo.uiTicketUseSwitch,
									pclCI->clBI.uiGMMode,
									pclCI->clBI.bPCRoom,
									siPersonalMakeItemType,
									&pclCI->clBI.clGuildRank,
									&pclCI->clPersonNaming,
									pclCI->clHorseInfo.siCurrentHorseRIDEHORSE,
									clTransFormInfo.uiNowTransFormKind,
									clTransFormInfo.bTransFormMode,
									uiBestGuild,										// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
									bIsElectionStump,
									clTransFormInfo.bTransForm100Effect,
									BufTransformKind,
									siEnemUnique,
									pclValentineWar,
									bElixirSwitch
									,pclPVP_LeagueInfo
									,siPremiumpartsslot1
									,sipremiumpartsuniqueslot1
									,siPremiumpartsslot2
									,sipremiumpartsuniqueslot2
									,siPremiumpartsslot3
									,sipremiumpartsuniqueslot3
									,siPremiumpartsNum
									,m_uiWeaponSkillMasterEmblem
									,siDisplayLoveLevel
									,siMySoulGuardUnique
									,bRepairShopSwitch
									,&pclCI->clBI.clBufInfo);

	cltMsg clMsg(GAMEMSG_RESPONSE_LOGIN, sizeof(clMakeCharInfo), (BYTE*)&clMakeCharInfo);

	SendNetMsg((sPacketHeader*)&clMsg);

	// SameMap 상태가 변경될때만 보내도록 한다
	if ( (pclMarriage) && (TRUE == IsMarried()) && (pclMarriage->GetConnectMode() != siConnectMode) )
	{
		pclMarriage->SetConnectMode( siConnectMode );

		pclserver->SendServerResponseMsg( 0, SRVAL_SET_MARRY_WITHSAMEMAP, siConnectMode, siLoveLevel, GetCharUnique() );
	}
	
	// 클라이언트가 준비될때까지 기다리게 한다. 
	bReadySwitch		= false;
	bFirstCellOpSwtich	= false;

	if(bwritelog)
	{
		// 워프는 빈번하게 일어나므로 꼭 필요한 경우만 로그를 쓰도록 하자.
		SI32 mapunique = pclClient->pclMapManager->GetMapUnique(clCharWarpInfo.GetMapIndex());
		((cltServer*)pclClient)->SendLog_Warp(pclCI->GetPersonID(), mapunique);
	}

	// 워프 정보를 초기화한다. 
	clCharWarpInfo.SetWarpSwitch(0);

	// 주변의 캐릭터들에게 본인이 워프 했음을 알린다. 
	pclClient->pclMapManager->m_world.GetMap( GetMapIndex() )->Warp( GetX(), GetY(), this, clCharWarpInfo.uiTicketUseSwitch );


	if( siPartyIndex > 0)
	{
		CPartyObj* pParty =	pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
		if( pParty ) 
			pParty->NotifyMovePosToPartyMember(GetCharUnique(),x,y,true);
	}

	// [기형] 캐릭터 워프 이동시 위치를 로그에 남긴다.
	SendDB_PosLifeMana();

	if(clCharWarpInfo.GetMapIndex() > 88 && clCharWarpInfo.GetMapIndex() < 300)
	{
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->pclStatisticsManager->clDailyStatistics.siDungeonUserNumber ++;
	}
		
	/*
	else if ( clCharWarpInfo.GetMapIndex() >= MAPINDEX_DAEMADO && clCharWarpInfo.GetMapIndex() < MAPINDEX_DAEMADO + MAX_INSTANCE_MAP_NUMBER )
	{
		cltServer* pclserver = ( cltServer*)pclClient;
		pclserver->pclStatisticsManager->clDailyStatistics.siInstanceDungeonUserNumber ++;
	}*/

		// 마을로 워프해 들어간 것이라면, 
		if(pclClient->pclVillageManager->IsValidVillage( GetMapIndex() ))
		{
			// 마을의 센터 지점을 확보한다. 
			SI32 x = pclClient->pclVillageManager->pclVillageInfo[ GetMapIndex() ]->PosX;
			SI32 y = pclClient->pclVillageManager->pclVillageInfo[ GetMapIndex() ]->PosY;

			if(TABS(pclClient->CurrentClock - dwLastVisitVillageClock) > 300000)
			{
				dwLastVisitVillageClock = pclClient->CurrentClock;
				pclClient->pclVillageManager->pclVillageInfo[ GetMapIndex() ]->IncVisitNum(1);
			}

			pclCI->clBI.clLastMainMapPos.Set(x, y);

			// 해당마을이 주총중인가 ?
			if(pclClient->pclCityHallManager->IsGeneralMeeting( GetMapIndex()))
			{
				TCHAR* pText = GetTxtFromMgr(2819);
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, GetCharUnique(), pText);
			}

			if(pclClient->pclCityHallManager->IsPrepareBankruptcy( GetMapIndex()))
			{
				TCHAR* pText = GetTxtFromMgr(10182);
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, GetCharUnique(), pText);
			}

		}

		// 워프하면 내상태에서 pvp를 뺀다 pvp-
		clInnerStatus.clEnemyType.siEnemyType = ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR;
		
		if( pclClient->pclMapManager->IsInstanceMap( GetMapIndex() ) )
		{
			SI32 siParentMap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
			cltMapCommon* pclParentMap = pclClient->pclMapManager->GetMapPointer( siParentMap );
			if( pclMap != NULL )
			{
				SI16 siMapType = pclClient->pclMapManager->GetInstanceMapType( siParentMap );

				if( pclParentMap->m_siInstanceMapGateIndex >= 0 )
				{
					cltInstanceMapGate	clGates[MAX_INSTANCEMAPGATE_COUNT];

					SI32 siCount = pclClient->pclMapManager->pclInstanceMapGateManager->GetInstanceMapGates( 
						GetMapIndex(), pclParentMap->m_siInstanceMapGateIndex,
						clGates, MAX_INSTANCEMAPGATE_COUNT );

					cltGameMsgResponse_InstanceMap_GateInfo clinfo(clGates, siCount);
					cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTMAP_GATEINFO, clinfo.GetSize(), (BYTE*)&clinfo);
					SendNetMsg((sPacketHeader*)&clMsg);
				}

				switch ( siMapType ) 
				{
				case INSTANCEMAP_TYPE_GUILD:
					{
						cltGameMsgResponse_cInstantsDungeonRunInfo	clInfo(pclserver->CurrentClock - pclParentMap->m_dwInstanceMapStartTime, pclParentMap->m_siInstanceMapScore, pclClient->pclGuildManager->siTopClearPoint, DUNGEONRUN_START, siMapType);
						cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg( (sPacketHeader*)&clMsg );
					}
					break;

				case INSTANCEMAP_TYPE_PARTY:
					{
						DWORD	dwTime			= pclserver->CurrentClock - pclParentMap->m_dwInstanceMapStartTime;
						SI32	siKillCount		= (pclParentMap->m_siMaxMonsterNum - pclParentMap->m_siKillCount);
						SI32	siBonusCount	= 0;

						cltGameMsgResponse_cInstantsDungeonRunInfo	clInfo(dwTime, siKillCount, siBonusCount, DUNGEONRUN_START, siMapType);
						cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg( (sPacketHeader*)&clMsg );
					}
					break;
				}
			}
		}

		return TRUE;
}

// 안전지대로 이동시킨다. 
void cltCharServer::WarpToSafeZone()
{
	// 안전지대로 워프 시킨다. 
	OrderStop(GetID(), BY_COMPUTER);

	//if ( pclClient->siServiceArea == ConstServiceArea_China )
	//{
	//		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
	//		SetWarpInfo(&clWarpInfo, 56);
	//		// 실제로 워프 시킨다. 
	//		Warp();
	//}
	//else
	//{
	//	if ( pclKI->siDefaultCountry == ConstServiceArea_China )
	//	{
	//		cltWarpInfo clWarpInfo(1, MAPINDEX_CHINABORDER, false, false, 17, 19, -1, -1);	// 경복궁 안전지대로 워프. 
	//		SetWarpInfo(&clWarpInfo, 56);
	//		// 실제로 워프 시킨다. 
	//		Warp();
	//	}
	//	else
	//	{
	cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
	SetWarpInfo(&clWarpInfo, 56);
	// 실제로 워프 시킨다. 
	Warp();
	//}
	//}
}


//----------------------------------
// Skill
//----------------------------------
// 스킬을 최초로 연마한다. 
BOOL cltCharServer::DevelopSkill(SI32 skillunique)
{
	// 캐릭터의 스킬을 연마한다. 
	return pclCI->clCharSkill.MakeSkill(skillunique); 
}




bool cltCharServer::IsDeathPenaltyCondition()
{
	// 인스턴스 던전에서는 페널티가 있다.
	if( siKilledMode == KILLEDMODE_INSTANCEMAP )		return true;
	if(siKilledMode > 0)
		return false;

	return true;
}

// 사망에 따른 페널티. 
void cltCharServer::DeathPenalty(SI32 killedmode, TCHAR* szkillername)
{
	if(bDeathPenaltySwitch == true)		return ;

	bDeathPenaltySwitch = true;
	bRequestReviveSwitch = true;

	// 사망 시간을 기록한다. 
	DeathClock = pclClient->CurrentClock;
	// 레벨 20미만에서는 사망에 따른 페널티가 없다. 
	if(pclCI->clIP.GetLevel() < FATHER_LEVEL )	return ;	
	GMONEY changedmoney = 0;
	SI32 changedexp = 0;

	if( pclCI->clIP.GetLevel() >= FATHER_LEVEL )
	{
		if( 0 < GetLife() )
			return;

		if( IsDeathPenaltyCondition() == false )
			return ;

		//  마을사망 패널티 다시 적용
		if( pclClient->pclMapManager->pclVillageManager->IsValidVillage(GetMapIndex()) == true )			return;

		// [영훈] 개인상점지역 : 사망 패널티가 없다
		if ( GetMapIndex() == MAPINDEX_PRIVATEMARKETAREA )			return;

		if( GetMapIndex() == MAPINDEX_PALACE )						return;

		// 보험증서를 가지고 있으면 패널티가 없다
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			cltItem * pclitem = &pclCI->clCharItem.clItem[i];	if( pclitem->siUnique <= 0 ) continue;
			// 보험증서가 있다.
			if(	pclitem->siUnique == ITEMUNIQUE(2731)	&& pclitem->GetItemNum() > 0 )	return	;
		}

		// 현금을 줄여준다. (10%)
		changedmoney = pclCI->clIP.GetMoney()/10;

		// 경험치를 줄여준다.(level * 10)
		changedexp = pclCI->clIP.GetLevel() * 10;
		pclCI->clIP.DecreaseExp( changedexp );

		// 클라이언트로 정보를 보낸다.
		// 경험치 얻었음을 통보한다. 
		{
			cltGameMsgResponse_GetExp clinfo(GetCharUnique(),  -changedexp,  0, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_GETEXP, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}


		// 비정상으로 종료됐을때 두번 처리하지 않게 생명력을 채운다(클라이언트로는 보내지 않는다) -KKM-
		//	pclCI->clIP.SetLife( clPB.GetMaxLife() );
		SendDBLevelInfo(0, 0);

		// 현금을 줄일것을 DB로 요구한다. 
		{
			sDBRequest_ChangeMoney clMsg(GetID(), pclCI->GetPersonID(), CHANGE_MONEY_REASON_DEATH, -changedmoney, szKillMeCharName );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


			// 통화량 조절 
			cltServer* pclserver = (cltServer*)pclClient;
			cltMoney clmoney;
			clmoney.Set(changedmoney);
			pclserver->clCurrencyInfo.clOutputMoney_Dead.Increase(&clmoney);

			pclserver->pclDelMoneyStatistics->Add(DELMONEY_DEATHPANELTY, changedmoney);
		}

		// 길드가 있다면 GP를 깐다
		//{
		//	// 길드가 있다면 GP를 업데이트한다.
		//	if ( pclCI->clBI.clGuildRank.IsGuildMember() == true )
		//	{
		//		cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
		//		if ( pGuild )
		//		{
		//			sDBRequest_Guild_ChangeGuildPoint clMsg(pclCI->clBI.clGuildRank.GetGuildUnitIndex(),pclCI->GetPersonID(),-3,TYPE_GUILDPOINT_REMOVE_DEAD);
		//			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//		}
		//	}
		//}

	}

	if(killedmode == -1)
	{
		killedmode = siKilledMode;
	}

	TCHAR* pkillername = szKillMeCharName;
	if(szkillername)
	{
		pkillername = szkillername;
	}

	cltGameMsgResponse_DeathPenalty clInfo(changedmoney, changedexp, killedmode, pkillername);
	cltMsg clMsg(GAMEMSG_RESPONSE_DEALTHPENALTYINFO, sizeof(clInfo), (BYTE*)&clInfo);
	// 클라이언트로 메시지를 보낸다. 
	SendNetMsg((sPacketHeader*)&clMsg);
}

void cltCharServer::RequestRevive(SI32 id, SI16 DieMoode)
{
	if (bRequestReviveSwitch)
	{
		bRequestReviveSwitch = false;
		cltGameMsgResponse_Revive clInfo(id, 1,DieMoode);
		if( siKilledMode == KILLEDMODE_INSTANCEMAP )
		{
			clInfo.siParam = 1000;
		}
		cltMsg clMsg(GAMEMSG_RESPONSE_REVIVE, sizeof(clInfo), (BYTE*)&clInfo);
		SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltCharServer::Revive()
{

	// 일정 시간이 경과할 때까지 기다린다. 
	//if(TABS(pclClient->CurrentClock - DeathClock ) < 5000)return ;
	DeathClock = pclClient->CurrentClock;

	bool	bWarped = false;

	SI32 villageunique = 0;
	if(siKilledMode == KILLEDMODE_VILLAGEWAR)
	{
		villageunique = pclCI->clBI.siHomeVillage;
	}
	else
	{
		villageunique = GetCurrentVillageUnique();
	}

	if(villageunique <= 0 )
	{
		// 현재 위치한 지도의 부모 지도를 찾는다. 
		SI32 parentmap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
		if(parentmap == 0)
			parentmap = GetMapIndex();

		//cyj 죽은위치가 수렵장일 경우 parentmap이 villageunique 임
		if(pclClient->pclMapManager->IsHuntMap( GetMapIndex() ) == true)
		{
			villageunique = parentmap;
		}
		// by LEEKH 죽은 위치가 인던인 경우 한양으로 보낸다.
		// 일반적으로 이 위치로 오지는 않는다.
		else if ( pclClient->pclMapManager->IsInstanceMap( GetMapIndex() ) == true && 
			siKilledMode != KILLEDMODE_INSTANCEMAP )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
			SetWarpInfo(&clWarpInfo, 56);
			Warp();

			bWarped = true;
		}
		else
		{
			// 부모 마을의 야외지역 좌표를 찾는다. 
			SI32 x, y;
			if( parentmap != 0 && pclClient->pclMapManager->pclGateManager->FindMainFieldPos(parentmap, &x, &y) == true )
			{

			}
			else
			{
				x	= pclCI->clBI.clLastMainMapPos.siX;
				y	= pclCI->clBI.clLastMainMapPos.siY;
			}

			// 가까운 마을을 찾는다.
			villageunique = pclClient->pclVillageManager->FindNearVillage(x, y);
		}
	}

	// 생명력을 채운다. 
	pclCI->clIP.SetLife( clPB.GetMaxLife() );

	// 정지 상태로 만든다.
	SetCurrentOrder( ORDER_REVIVE );

	// 인던에서 죽은 경우
	if( siKilledMode == KILLEDMODE_INSTANCEMAP )
	{
		SI32 siMapIndex		= GetMapIndex();
		SI32 siParentMap	= pclClient->pclMapManager->GetParentMap( siMapIndex );
		SI16 siMapType		= pclClient->pclMapManager->GetInstanceMapType( siParentMap );
		SI32 siSourceMap	= 0;

		if( pclClient->pclMapManager->HaveCloneMap( siParentMap ) == true )
		{
			siSourceMap = siParentMap;
		}
		else
		{
			siSourceMap = pclClient->pclMapManager->GetSourceMap( siParentMap );			
		}

		// [영훈] 해적선 : 해적선 안에서 죽었을 경우 위치를 해적선 시작위치로
		if ( siMapType == INSTANCEMAP_TYPE_PARTY )
		{
			SI32		siWarpX = PIRATESHIP_START_POSITION_X + (rand() % 5);
			SI32		siWarpY = PIRATESHIP_START_POSITION_Y + (rand() % 5);
			cltWarpInfo clWarpPirateShip(1, siParentMap, false, false, siWarpX, siWarpY, -1, -1);

			SetWarpInfo( &clWarpPirateShip, 1024 );
			Warp();

			bWarped = true;
		}
		else if ( siMapType == INSTANCEMAP_TYPE_GUILD )
		{
			for (SI32 i=0; i<MAX_GATE_NUMBER; i++)
			{
				cltGate* pclGate = &pclClient->pclMapManager->pclGateManager->clGate[i];
				if( pclGate != NULL && pclGate->FOUnique > 0 &&	pclGate->DstMapIndex == siSourceMap )
				{
					cltWarpInfo clWarpInfo(1, siParentMap, false, false, pclGate->DstX, pclGate->DstY, -1, -1);
					SetWarpInfo(&clWarpInfo, 56);
					Warp();

					bWarped = true;
				}
			}
		}
		else
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
			SetWarpInfo(&clWarpInfo, 56);
			Warp();

			bWarped = true;
		}

		if( bWarped == false )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
			SetWarpInfo(&clWarpInfo, 56);
			Warp();

			bWarped = true;
		}
	}

	if( siKilledMode == KILLEDMODE_GOTOSAFEZONE )
	{
		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
		SetWarpInfo(&clWarpInfo, 56);

		Warp();

		bWarped = true;
	}

	if( bWarped == false && pclCI->clIP.GetLevel() < INIT_LEVEL  )//랩 10까지는 경복궁에서 살아난다.
	{
		//if ( pclClient->siServiceArea == ConstServiceArea_China )
		//{
		//	cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 자금성 안전지대로 워프. 
		//	SetWarpInfo(&clWarpInfo, 56);
		//}
		//else
		//{
		//	if(pclKI->siDefaultCountry == ConstServiceArea_Korea)
		//	{
		//		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
		//		SetWarpInfo(&clWarpInfo, 56);
		//		// 실제로 워프 시킨다. 
		//	}
		//	else
		//	{
		//cyj cltWarpInfo clWarpInfo(1, MAPINDEX_CHINABORDER, false, false, 17, 19, -1, -1);	// 경복궁 안전지대로 워프. 
		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
		SetWarpInfo(&clWarpInfo, 56);
		// 실제로 워프 시킨다. 

		//}
		//}

		Warp();

		bWarped = true;
	}
	// pvp 사냥타 개선이 들어간후에
	if(pclClient->IsCountrySwitch(Switch_PKHuntMap_Change_Info)	== true )
	{
		if( pclClient->pclMapManager->IsPkMap( GetMapIndex() )== true )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
			SetWarpInfo(&clWarpInfo, 56);

			Warp();

			bWarped = true;
		}
	}
	if( bWarped == false && villageunique > 0 && villageunique < MAX_VILLAGE_NUMBER )
	{

		SI32 mapindex	= pclClient->pclVillageManager->pclVillageInfo[villageunique]->siVillageUnique;

		SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[ mapindex ]->siMapUnique;
		SI32 centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		SI32 centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		OrderStop(siID, BY_COMPUTER);

		cltWarpInfo clWarpInfo(1, mapindex, false, false, centerx, centery, -1, -1);
		SetWarpInfo(&clWarpInfo, 200);

		// 실제로 워프 시킨다. 
		Warp();
	}


	SendDB_PosLifeMana();	

	// 클라이언트에 업데이트 한다. 
	SetUpdateSwitch(UPDATE_IP, true, 0);

	// 캐릭터의 개인상점을 초기화한다.
	SetPersonalShopBanner(NULL);
	SetPersonalShopData(false, NULL);


	// 사망 모드 초기화.ㅣ 
	siKilledMode = 0;
	StringCchCopy(szKillMeCharName, MAX_PLAYER_NAME, TEXT(""));

}

void cltCharServer::Resurrection( bool pvpFlag /* false 가 기본 */)	// 제자리에서 즉시 부활시킨다.
{
	DeathClock = pclClient->CurrentClock;

	SI32 currentMap = GetMapIndex();
	SI32 currentX   = GetX();
	SI32 currentY	= GetY();

	// 생명력을 채운다. 
	pclCI->clIP.SetLife( clPB.GetMaxLife() );

	// 정지 상태로 만든다.
	SetCurrentOrder( ORDER_REVIVE );

	OrderStop(siID, BY_COMPUTER);

	cltWarpInfo clWarpInfo(1, currentMap, pvpFlag, false, currentX, currentY, -1, -1);
	SetWarpInfo(&clWarpInfo, 200);

	// 실제로 워프 시킨다. 
	Warp();

	SendDB_PosLifeMana();	

	// 클라이언트에 업데이트 한다. 
	SetUpdateSwitch(UPDATE_IP, true, 0);

	// 캐릭터의 개인상점을 초기화한다.
	SetPersonalShopBanner(NULL);
	SetPersonalShopData(false, NULL);

	// 사망 모드 초기화.ㅣ 
	siKilledMode = 0;
	StringCchCopy(szKillMeCharName, MAX_PLAYER_NAME, TEXT(""));
}

// 시간 경과에 따른 자동 로그아웃. 
bool cltCharServer::AutoLogOut()
{
	// PC인 경우에만 자동 로그아웃이 작동한다. 
	if(IsPC(GetCharUnique()) == false)return false;

	if(LastReceveFromClientClock == 0)return false;

	// 마지막 메시지를 받은지 3분 이상이 경과했다. 
	if( TABS(pclClient->CurrentClock - LastReceveFromClientClock ) > 3 * 60 * 1000 )
	{
		if(GetSession())
		{
			// apex-
#ifdef _CHINA
			SI32 id = pclCM->GetIDFromCharUnique( GetCharUnique() );
			if( 0 < id )
			{
				NoticeApexProxy_UserLogout( id, (char*)pclCI->clBI.szAccountID );
				bApexLogin = false;
				pclClient->pclLog->FileConfigPrint ("AutoLogOut", "%s", (char*)GetName() );
			}
#endif

#ifdef USE_GAME_GUARD_SERVER
			CCSAuthClose();
#endif
			// -apex
			GetSession()->CloseSocket();
		}
		return true;
	}

	return false;
}


// 캐릭터 생성 후에 암호화키와 캐릭터 유니크 값을 클라이언트로 보낸다. 
void cltCharServer::SecretNCharUniqueSendOperation()
{
	if(bSendSecretNCHarUniqueSwitch == false)return ;
	bSendSecretNCHarUniqueSwitch	= false;

	// 암호화에 사용할 랜덤키를 생성한다. 
	UI08 key1 = (UI08)rand();
	UI08 key2 = (UI08)rand();

	// 암호화키를 설정한다. 
	GetSession()->GetEncrypt()->SetKey( key1, key2 );

	// 암호화키값과 CharUnique값을 클라이언트에게 전달해야 한다. 
	cltGameMsgResponse_ClientCharUnique clInfo(GetCharUnique(), key1, key2, pclClient->GetVersion());
	cltMsg clMsg(GAMEMSG_RESPONSE_CLIENTCHARUNIQUE, sizeof(clInfo), (BYTE*)&clInfo);

	// 클라이언트로 메시지를 보낸다. 
	SendNetMsg((sPacketHeader*)&clMsg);

}

//----------------------------------------------------------
// 클라이언트로의 전송 함수. 
//----------------------------------------------------------
//쪽지를 보낸다. 
void cltCharServer::SendLetterMsg(cltLetterUnit* pclletter)
{
	cltMsg clMsg(GAMEMSG_RESPONSE_LETTER, sizeof(cltLetterUnit), (BYTE*)pclletter);
	SendNetMsg((sPacketHeader*)&clMsg);

}

void cltCharServer::SendAccountLetterMsg(cltAccountLetterUnit* pclletter)
{
	cltMsg clMsg(GAMEMSG_RESPONSE_ACCOUNTLETTER, sizeof(cltAccountLetterUnit), (BYTE*)pclletter);
	SendNetMsg((sPacketHeader*)&clMsg);
}

//-----------------------------------
// 로그인 후 보호 
//-----------------------------------
void cltCharServer::SetInitProtectSwitch()
{
	clSimpleVary.bInitProtectSwitch	= true;
	clSimpleVary.dwInitProtectClock	= pclClient->CurrentClock;
}

bool cltCharServer::GetInitProtectSwitch()
{
	return clSimpleVary.bInitProtectSwitch;
}

// 자동 회복/저하.  기능. 
void cltCharServer::AutoRecoverLife()
{
	SI32 vary = 0;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if(pclCI->clHealthInfo.uiHealthPoint == 100)return ;

	if(pclCI->clHealthInfo.uiHealthPoint > 100)
	{
		vary = pclCI->clHealthInfo.uiHealthPoint - 100;

		// 체력 회복. 
		SI32 life  = min(vary, max(0, clPB.GetMaxLife() - GetLife()) );
		if(life)
		{
			IncreaseLife(life);

			// 사용자인 경우, 클라이언트로 보내준다. 
			if(IsPC(GetCharUnique()))
			{
				cltGameMsgResponse_IncLife clInfo(GetCharUnique(), pclCI->clIP.GetLife(),  life, clPB.siReservedLife, 0, INCLIFE_REASON_HEALTH);
				cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}

}

void cltCharServer::AutoCushionRecoverLife()
{
	SI32 vary = 0;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13628): // 이불1
		case  ITEMUNIQUE(13629): // 이불2 
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary += 40;
			break;
		default:
			vary += 20;
		}
	}

	// 회복할 체력이 없으면 끝낸다.
	if( vary <= 0) return;

	// 체력 회복. 
	SI32 life  = min(vary, max(0, clPB.GetMaxLife() - GetLife()) );
	if(life)
	{
		IncreaseLife(life);

		// 사용자인 경우, 클라이언트로 보내준다. 
		if(IsPC(GetCharUnique()))
		{
			cltGameMsgResponse_IncLife clInfo(GetCharUnique(), pclCI->clIP.GetLife(),  life, clPB.siReservedLife, 0, INCLIFE_REASON_HEALTH);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}

// 자동 회복/저하.  기능. 
void cltCharServer::AutoRecoverMana()
{
	SI32 vary = 0;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if(pclCI->clHealthInfo.uiHealthPoint == 100)return ;

	if(pclCI->clHealthInfo.uiHealthPoint > 100)
	{
		vary = pclCI->clHealthInfo.uiHealthPoint - 100;
		// 마법 회복시간 늘려주는 버프마법이 걸려있을경우 마나 회복량을 무조건 10으로 고정
		if ( (10 > vary) && (0 < m_clMagicBufMgr.GetIncMPRecoveryTime((cltCharCommon*)this)) )
		{
			vary = 10;
		}

		// 마나 회복. 
		SI32 mana = min(vary, clPB.GetMaxMana() - GetMana());

		if(mana)
		{
			IncreaseMana(mana);

			// 사용자인 경우, 클라이언트로 보내준다. 
			if(IsPC(GetCharUnique()))
			{
				cltGameMsgResponse_IncMana clInfo(GetCharUnique(), pclCI->clIP.GetMana(),  mana, INCMANA_REASON_HEALTH);
				cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}

}


void cltCharServer::AutoCushionRecoverMana()
{
	SI32 vary = 0;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13628): // 이불1
		case  ITEMUNIQUE(13629): // 이불2 
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary += 40;
			break;
		default:
			vary += 20;
		}
	}


	// 회복할 마나가 없으면 끝낸다.
	if( vary <= 0) return;


	// 마나 회복. 
	SI32 mana = min(vary, clPB.GetMaxMana() - GetMana());
	if(mana)
	{
		IncreaseMana(mana);

		// 사용자인 경우, 클라이언트로 보내준다. 
		if(IsPC(GetCharUnique()))
		{
			cltGameMsgResponse_IncMana clInfo(GetCharUnique(), pclCI->clIP.GetMana(),  mana, INCMANA_REASON_HEALTH);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}

// PCK : 잠자는 고양이 방석 - 소환수 체력 회복 기능 (09.06.15)
void cltCharServer::AutoCushionRecoverSummonLife()
{
	SI32 vary = 0;
	SI32 siIndex = 0;
	SI32 life = 0;

	SI32 siSummonCharID = GetSummonID();

	cltCharServer* pclSummonChar = pclCM->GetCharServer(siSummonCharID);

	if( NULL == pclSummonChar)	return;

	SI32 siSummonIndex = pclCM->CR[siSummonCharID]->GetSummonIndex();
	cltSummon *pclSummon = pclCI->clSummonInfo.GetSummon(siSummonIndex);

	SI32 siSummonKind = 0;
	SI32 siSummonStatus = 0;

	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary += 10;
			break;
		default:
			vary += 0;
		}
	}

	// 회복할 체력이 없으면 끝낸다.
	if( vary <= 0) return;

	// 체력 회복.
	for(siIndex = 0; siIndex < MAX_SUMMON_OWN; ++siIndex)
	{
		siSummonKind	= pclSummonChar->pclCI->clBI.GetKind();
		siSummonStatus	= pclSummon->siStatus;

		SI32	siSummonMaxLife = pclSummonChar->clPB.GetMaxLife();
		SI32	siSummonNowLife = pclSummonChar->pclCI->clIP.GetLife();

		// 소환수가 활성화 되어 있으면
		if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_TAKEOUT == siSummonStatus) )
		{
			// 죽은 상태라면 회복되지 않는다.
			if(siSummonNowLife <= 0)	return ;
			life  = min(vary, max(0, siSummonMaxLife - siSummonNowLife));
		}	
	}

	if(life)
	{
		pclSummonChar->IncreaseLife(life);

		// 사용자인 경우, 클라이언트로 보내준다. 
		if(IsPC(GetCharUnique()))
		{
			cltGameMsgResponse_IncLife clInfo(pclSummonChar->GetCharUnique(), pclSummonChar->pclCI->clIP.GetLife(),  life, pclSummonChar->clPB.siReservedLife, 0, INCLIFE_REASON_HEALTH);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

// PCK : 잠자는 고양이 방석 - 소환수 마나 회복 기능 (09.06.15)
void cltCharServer::AutoCushionRecoverSummonMana()
{
	SI32 vary = 0;
	SI32 siIndex = 0;
	SI32 mana = 0;

	SI32 siSummonCharID = GetSummonID();

	cltCharServer* pclSummonChar = pclCM->GetCharServer(siSummonCharID);

	if( NULL == pclSummonChar)	return;

	SI32 siSummonIndex = pclCM->CR[siSummonCharID]->GetSummonIndex();
	cltSummon *pclSummon = pclCI->clSummonInfo.GetSummon(siSummonIndex);

	SI32 siSummonKind = 0;
	SI32 siSummonStatus = 0;


	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary += 10;
			break;
		default:
			vary += 0;
		}
	}

	// 회복할 마나가 없으면 끝낸다.
	if( vary <= 0) return;

	// 마나 회복.
	for(siIndex = 0; siIndex < MAX_SUMMON_OWN; ++siIndex)
	{
		siSummonKind	= pclSummonChar->pclCI->clBI.GetKind();
		siSummonStatus	= pclSummon->siStatus;

		SI32	siSummonMaxMana = pclSummonChar->clPB.GetMaxMana();
		SI32	siSummonNowMana = pclSummonChar->pclCI->clIP.GetMana();

		// 소환수가 활성화 되어 있으면
		if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_TAKEOUT == siSummonStatus) )
		{
			// 수정 : MP가 0이여도 소환수 마나는 회복되야 한다. (09.07.24)
			if(siSummonNowMana < 0)	return ;
			mana  = min(vary, max(0, siSummonMaxMana - siSummonNowMana));
		}	
	}

	if(mana)
	{
		pclSummonChar->IncreaseMana(mana);

		// 사용자인 경우, 클라이언트로 보내준다. 
		if(IsPC(GetCharUnique()))
		{
			cltGameMsgResponse_IncMana clInfo(pclSummonChar->GetCharUnique(), pclSummonChar->pclCI->clIP.GetMana(),  mana, INCMANA_REASON_HEALTH);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

// 기관 회복.
void cltCharServer::AutoCushionRecoverOragans()
{
	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();
	SI32 vary = 0;
	bool select = false;

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13628): // 이불1
		case  ITEMUNIQUE(13629): // 이불2
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary = rand()%5+1; // 회복량
			break;
		default:
			vary = 0;
		}
	}

	// 레벨에따라 배고픔수치를 감소시킬지 말지를 결정한다.
	if(vary >0)
	{
		SI32 maxOrg = MAXORG(pclCI->clIP.GetLevel());
		SI16 trueOrg[5] = {0,}; // 0번칸은 쓰지 않는다.
		SI16 temSelectOrg = 0;
		SI16 temprandSelect = 0;
		SI32 randSelect = 0;

		for(SI16 i = 1;i < 5 ;i++)
		{
			SI32 tempOrg = pclCI->clHealthInfo.GetOrg(i);

			if(tempOrg < maxOrg)
			{
				temSelectOrg++;
				trueOrg[temSelectOrg] = i; //1~4번칸에 저장한다.
			}

		}

		// 회복시킬 기관 선택.
		if(temSelectOrg >0)
		{
			temprandSelect = rand()%temSelectOrg+1; // 남은것중에서 랜덤하게 고른다.
			randSelect	= trueOrg[temprandSelect];  // 고른 위치에 저장된 값을 찾는다.

			SI32 nowOrgval = pclCI->clHealthInfo.GetOrg(randSelect); // 현재 기관수치를 구한다.

			// 기관수치는 최대값을 넘을 수 없다.
			if((nowOrgval+vary) > maxOrg)
				vary = maxOrg - nowOrgval;

			switch(randSelect)
			{
			case 1: // 소화기관.
				pclCI->clHealthInfo.IncreaseInnerOrg1(vary);
				break;
			case 2: // 순환기관.
				pclCI->clHealthInfo.IncreaseInnerOrg2(vary);
				break;
			case 3: // 호흡기관.
				pclCI->clHealthInfo.IncreaseInnerOrg3(vary);
				break;
			case 4: // 신경기관.
				pclCI->clHealthInfo.IncreaseInnerOrg4(vary);
				break;
			}

			select= true;
		}
	}

	if( select == true)
	{	
		//클라로 알린다.
		SetUpdateSwitch(UPDATE_HEALTH, true, 0);

		// DB에 저장한다. 
		sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}
}

// 포만감을 하락시킨다.
void cltCharServer::AutoCushionFallSatisfied()
{
	SI32 vary = 0;
	bool select = false;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if( GetCurrentOrder() != ORDER_SITDOWN ) return;

	SI16 haveCushion =  IsHaveCushionItem();

	if( haveCushion > 0 )
	{
		switch(haveCushion)
		{
		case  ITEMUNIQUE(13628): // 이불1
		case  ITEMUNIQUE(13629): // 이불2
		case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
		case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
		case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
		case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
			vary = 1; // 감소량
			break;
		default:
			vary = 0;
		}
	}

	// 레벨에따라 배고픔수치를 감소시킬지 말지를 결정한다.
	if(vary >0)
	{
		SI32 level  = pclCI->clIP.GetLevel();	
		SI16 nowHungry = clPB.clHealth.GetHungry();
		SI16 basicHungry = 30;

		if(level > 30 && level <= 100 )
		{
			basicHungry = level;
		}
		// PCK : 캐릭터 레벨이 100레벨 이상을 넘어가면 배고픔 수치는 100으로 고정한다. (09.07.08)
		else if(level > 100)
		{
			basicHungry = 100;
		}

		if(nowHungry > basicHungry)
			select= true;
	}

	if(select == true)
	{
		// 포만감을 감소시킨다.
		clPB.clHealth.DecreaseHungry(vary);

		//클라로 알린다.
		SetUpdateSwitch(UPDATE_HEALTH, true, 0);

		// DB에 저장한다. 
		sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}
}

//KHY - 1220 - 변신시스템.
void cltCharServer::AutoTransFormRecoverMana()
{
	SI32 vary = 0;

	// 죽은 상태에서는 자동 회복 되지 않는다. 
	if(GetLife() <= 0)return ;

	if( IsCanTransFormRecover() == true  )
	{
		vary += 10;
	}

	// 회복할 마나가 없으면 끝낸다.
	if( vary <= 0) return;


	// 마나 회복. 
	SI32 mana = min(vary, clPB.GetMaxMana() - GetMana());
	if(mana)
	{
		IncreaseMana(mana);

		// 사용자인 경우, 클라이언트로 보내준다. 
		if(IsPC(GetCharUnique()))
		{
			cltGameMsgResponse_IncMana clInfo(GetCharUnique(), pclCI->clIP.GetMana(),  mana, INCMANA_REASON_HEALTH);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}

// 레벨 업에 따른 작업. 
void cltCharServer::LevelUpAction()
{
	cltServer* pclserver = (cltServer*)pclClient;
	TCHAR Nbuffer[512]=TEXT("");

	SI32 PrevLevel = pclCI->clIP.GetLevel();

	if(IsPC(GetCharUnique()))
	{
		// 휴면 계정 아이템이 있을 경우 아이템 업그래이드 ==============================================================================
		CDormancySystem *pclDormancySystem = pclserver->pclDormancySystem;
		if( NULL != pclDormancySystem)
		{
			CDormancyEquipItemRewardServer *pclDormancyServer = (CDormancyEquipItemRewardServer *)pclDormancySystem->GetDormancyEquipItemReward();
			if(NULL != pclDormancyServer)
			{
				pclDormancyServer->UpgradeItemInven(this);
			}
		}
		//==============================================================================================================================
	}

	// 레벨도 올려준다. 
	pclCI->clIP.IncreaseLevel(1);

	// 보너스를 지급한다.
	pclCI->clIP.IncreaseBonus(5);

	// 스킬 보너스를 지급한다. 
	pclCI->clIP.IncreaseSkillBonus(1);

	// 체력을 만땅. 
	SetLife(clPB.GetMaxLife());

	// 마법력을 만땅. 
	SetMana(clPB.GetMaxMana());

	// DB에 정보를 보낸다. 
	SendDBLevelInfo(5, 1);	

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// 로그 작성 - 레벨업 로그
		// param1 == 이전 레벨정보, param2 == 현재 레벨.
		// PCK - 캐릭터만 로그를 기록하게 한다.
		if(IsPC(GetCharUnique()))
		{
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARLEVELUP, 
				0, this, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				PrevLevel, pclCI->clIP.GetLevel(), 0, 0, 0, NULL, NULL);
		}
		// 로그 작성 - 소환수 레벨업 로그
		// param1 == 이전 레벨정보, param2 == 현재 레벨.
		// param3 == 소환수인덱스
		// pszCharParam1 == 소환수이름
		if(IsNPC(GetCharUnique()))
		{
			// 소환수의 플레이어 객체
			cltCharServer* pclPlayerChar = (cltCharServer*) pclCM->GetCharServer(GetSummonParentID());
			if( NULL !=  pclPlayerChar)
			{
				cltSummon *pclSummon = pclPlayerChar->pclCI->clSummonInfo.GetSummon(GetSummonIndex());
				
				TCHAR szSummonName[32] = {0,};
				if (pclSummon != NULL) 
				{
					StringCchCopy(szSummonName, 32, pclSummon->szName);
				}

				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_LEVELUP, 
				0, pclPlayerChar, pclSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				PrevLevel, pclCI->clIP.GetLevel(), GetSummonIndex(), 0, 0, szSummonName, NULL);
			}
		}
	}

	// 길드가 있다면 GP를 업데이트한다.
	if ( pclCI->clBI.clGuildRank.IsGuildMember() == true )
	{
		cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
		if ( pGuild )
		{
			sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCI->GetPersonID(),10,TYPE_GUILDPOINT_ADD_LEVELUP);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			//KHY - 1205 - 유저레벨업 공지
			//if (pclClient->IsWhereServiceArea(ConstSwitch_LevelUpNotice) )
			if (pclClient->IsCountrySwitch(Switch_LevelUpNotice) )
			{
				SI32 siPersonID = pclCI->GetPersonID();
				if(IsPC(GetCharUnique()))
				{
					TCHAR szName[MAX_PLAYER_NAME];
					MStrCpy( szName,GetName(), MAX_PLAYER_NAME );

					cltGameMsgResponse_LevelUpNotice clinfo(szName, pclCI->clIP.GetLevel(), 0 , 0 , 1);
					cltMsg clMsg2(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
					//KHY - 0131 - 길드 멤버 메시지 전달 - 이름으로 검색 - 유니크번호 검사제외!
					pclClient->pclCM->SendAllGuildMemberMsg((sPacketHeader*)&clMsg2,pGuild->siUnique,pGuild->szName);
				}
			}
		}
	}

	// 레벨업에따른 스승제자 보상 물품주기
	//KHY - 0610 - 스승제자 S 추가수정.
	if ( ConstServiceArea_Japan != pclClient->siServiceArea )
	{
		SendDBUpdateTeacherPoint( pclCI->clIP.GetLevel() );
	}

	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{
		// 레벨업을 하면 그에 해당하는 엘릭서 포인트를 증가 시켜준다.
		if( pcltElixir && pcltElixir->IsElixir() ) 
		{
			cltElixir_Info  clElixirInfo;
			clElixirInfo.m_siEndMinuteVary	= pcltElixir->GetMinuteVary();
			clElixirInfo.m_uiMultiple 		= pcltElixir->GetMultiple();
			clElixirInfo.m_siPoint	  		= pcltElixir->GetPoint() + pcltElixir->GetMultiple();
			clElixirInfo.m_siStr	  		= pcltElixir->GetStr();
			clElixirInfo.m_siDex	  		= pcltElixir->GetDex();
			clElixirInfo.m_siVit	  		= pcltElixir->GetVit();
			clElixirInfo.m_siMag	  		= pcltElixir->GetMag();
			clElixirInfo.m_siHnd	  		= pcltElixir->GetHnd();
			clElixirInfo.m_siWis	  		= pcltElixir->GetWis();

			if(pclCI->GetPersonID() > 0)
			{
				sDBRequest_Elixir_Set clMsg( GetID(), pclCI->GetPersonID(), &clElixirInfo );
				((cltServer*)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );	
			}
		}
	}
	
	//[진성] 스승, 제자. 레벨업이 20 이상이고 같은 마을 일때 사제간의 버프를 적용시켜준다.
	SI32 siFatherPersonID = pclCI->clBI.clFatherInfo.clFather.GetPersonID();
	if( 0 < siFatherPersonID )
	{
		if( 20 <= pclCI->clIP.GetLevel() && 49 > pclCI->clIP.GetLevel())	// 나의 레벨 확인.
		{
			// 1레벨 단위로 버프를 준다.
			//if( 0 == pclCI->clIP.GetLevel() % 2 )
			{
				SI32 siFatherID = pclClient->pclCM->GetIDFromPersonID(siFatherPersonID);			
				cltCharServer* pclFatherChar = pclCM->GetCharServer(siFatherID);		// 스승의 접속여부 확인.
				if( pclFatherChar ) 
				{
					// 제자인 나와 스승이 마을이 같다면 버프를 주리라~ㅋㅋ
					if(		(pclCI->clBI.siHomeVillage == pclFatherChar->pclCI->clBI.siHomeVillage) 
						&&	(0 < pclCI->clBI.siHomeVillage && 0 < pclFatherChar->pclCI->clBI.siHomeVillage) )
					{
						SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
						SI16 index   = 0;

						// 제자의 버프.
						if( false == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MENTOR ) )  
						{
							index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_MENTOR, false );

							stBuf addBuf(BUF_MENTOR, 10, usetime);
							AddBufThroughDB( index, &addBuf , false , 0, NULL );
						}

						// 스승의 버프.
						if( false == pclFatherChar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MENTOR ) )  
						{
							index = pclFatherChar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_MENTOR, false );

							stBuf addBuf(BUF_MENTOR, 10, usetime);
							pclFatherChar->AddBufThroughDB( index, &addBuf , false , 0, NULL );

						}
					}
				}
			}
		}
	}

	// 클라이언트로 레벨이 올랐음을 통보한다.  (JAYCEE : 이웃에게도 통보를 한다.)
	cltGameMsgResponse_LevelUp clinfo(GetCharUnique(), pclCI->clIP.GetLevel(), 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUP, sizeof(clinfo), (BYTE*)&clinfo);
	SendNeighbourMsg(&clMsg, true);

	// 마을이 있는경우 레벨업 정보를 DB로 보내서 점수 계산한다
	if(pclCI->clBI.siHomeVillage > 0 && pclCI->clBI.siHomeVillage <= CUR_VILLAGE_LIMIT)
	{
		// PCK : 레벨업 카운트 횟수 추가.
		sDBRequest_VillageJoinLevelUp clMsg(pclCI->GetPersonID(), pclCI->clBI.clVillageScoreInfo.siLevelUpCount, pclCI->clBI.siHomeVillage); 
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		//KHY - 1205 - 유저레벨업 공지
		if (pclClient->IsCountrySwitch(Switch_LevelUpNotice) )
		{
			SI32 siPersonID = pclCI->GetPersonID();
			if(IsPC(GetCharUnique()))
			{
				TCHAR szName[MAX_PLAYER_NAME];
				MStrCpy( szName,GetName(), MAX_PLAYER_NAME );

				cltGameMsgResponse_LevelUpNotice clinfo(szName, pclCI->clIP.GetLevel(), 0 , 0 , 2);
				cltMsg clMsg2(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg2,pclCI->clBI.siHomeVillage);
			}
		}		
	}

	// 클라이언트로 정보를 통보해준다.
	// 사용자 캐릭터인경우에만 통보한다. 소환수도 통보한다 
	if( IsPC(GetCharUnique()) || clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
	{
		SetUpdateSwitch(UPDATE_IP, true, 0);
	}

	// 소환수 레벨업 퀘스트
	SI32 siParentID = GetSummonParentID();
	if(pclCM->IsAlive(siParentID))
	{
		pclCM->CR[siParentID]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SUMMONLEVELUP);
	}

	if ( IsPC(GetCharUnique()) )
	{
		// 레벨업에 따른 보상을 준다. - 아이템
		if ( pclClient->pclEventTimeManager->InEventTime(TEXT("LevelUpReward"), &pclserver->sTime) )
		{
			SI32 siItemUnique[MAX_LEVELUP_REWARD_ITEM];
			SI32 siItemNum[MAX_LEVELUP_REWARD_ITEM];
			SI16 siNotice[MAX_LEVELUP_REWARD_ITEM];

			if(pclCI->clIP.GetLevelUpRewardItem(pclCI->clIP.GetLevel(), siItemUnique, siItemNum, siNotice))
			{
				for(int i=0; i<MAX_LEVELUP_REWARD_ITEM; i++)
				{
					if(siItemUnique[i] <= 0)			continue;
					if(siItemNum[i] <= 0)				continue;

					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(siItemUnique[i]);
					if(ref > 0)
					{
						UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;				
						if ( GIVEITEM_RESULT_NOINVEN == GiveItem(siItemUnique[i], siItemNum[i], INPUTITEMPERSON_OPTION_LEVELUP_REWARD, usedate) )
						{
							// 공간이 없어서 아이템을 지급하지 못함.
							cltItem clInputItem;
							SI16 bRareSwitch = 0;
							pclClient->pclItemManager->MakeRandItemUnique( siItemUnique[i], &clInputItem, 0, 0, &bRareSwitch, 0, 0, 0, 0, 0, usedate );

							clInputItem.siItemNum = siItemNum[i];

							pclserver->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem , NULL ,0  );
						}
					}

					pclserver->SendServerResponseMsg( 0, SRVAL_NOTICE_LEVELUP_REWARD, pclCI->clIP.GetLevel(), siItemUnique[i], GetCharUnique() );

					// 대박 알림창 여부
					if ( 0 < siNotice[i] )
					{
						cltItem	clNoticeItem;
						SI16	bRareSwitch = 0;

						pclClient->pclItemManager->MakeRandItemUnique(siItemUnique[i],&clNoticeItem,0,0,&bRareSwitch);

						cltGameMsgResponse_RareItemMade	clinfo((TCHAR*)(GetName()), pclCI->GetPersonID(), 
							&clNoticeItem,
							RARAITEM_NOTICE_SWITCH_LEVELUPREWARD,
							pclCI->clIP.GetLevel() );

						cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMMADE, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}



		// 일본 이벤트 종료로 인한 코드 제거 - by LEEKH 2007.10.04
		/*if( pclClient->IsWhereServiceArea( ConstSwitch_LevelUpAction ) )
		{
			//KHY - 0807 - 이벤트 발생 시간 조절.
			setLevUpActionStartTime(2007,8,8,16);
			setLevUpActionEndTime(2007,8,16,11);

			_SYSTEMTIME sysNowtime;
			GetLocalTime( &sysNowtime );

			UI32 uNowtime = pclserver->GetMinuteFromsTime(sysNowtime);
			UI32 uStarttime = pclserver->GetMinuteFromsTime(sTimeLevelUpActionStartTime);
			UI32 uEndtime = pclserver->GetMinuteFromsTime(sTimeLevelUpActionEndTime);


			if((uNowtime >= uStarttime)&&(uNowtime<=uEndtime))
			{
				// 레벨업에 따른 보상을 준다. - 아이템
				SI32 siItemUnique[MAX_LEVELUP_REWARD_ITEM];
				SI32 siItemNum[MAX_LEVELUP_REWARD_ITEM];

				if(pclCI->clIP.GetLevelUpRewardItem(pclCI->clIP.GetLevel(), siItemUnique, siItemNum))
				{
					for(int i=0; i<MAX_LEVELUP_REWARD_ITEM; i++)
					{
						if(siItemUnique[i] <= 0)			continue;
						if(siItemNum[i] <= 0)				continue;

						SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(siItemUnique[i]);
						if(ref > 0)
						{
							UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;				
							if(GiveItem(siItemUnique[i], siItemNum[i], INPUTITEMPERSON_OPTION_LEVELUP_REWARD , usedate) == false)
							{
								// 공간이 없어서 아이템을 지급하지 못함.
							}
						}
					}
				}
			}
		}*/

			// 고스톱, 포커 이벤트 - 기간설정
			if (pclClient->IsCountrySwitch(Switch_GoStopPokerEvent) )
			{		
				_SYSTEMTIME sStartEventDay , sEndEventDay;

				ZeroMemory(&sStartEventDay,sizeof(_SYSTEMTIME));
				ZeroMemory(&sEndEventDay,sizeof(_SYSTEMTIME));

				sStartEventDay.wYear = 2006;
				sStartEventDay.wMonth = 9;
				sStartEventDay.wDay = 20;
				sStartEventDay.wHour = 0;
				sStartEventDay.wMinute = 0;

				sEndEventDay.wYear = 2006;
				sEndEventDay.wMonth = 10;
				sEndEventDay.wDay = 19;
				sEndEventDay.wHour = 0;
				sEndEventDay.wMinute = 0;

				SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
				SI32 endEventdatevary = pclClient->GetMinuteFromsTime(sEndEventDay);

				_SYSTEMTIME fTimeDatevary = pclCI->clBI.GetFirstCreatTime(); //최초 계정 생성 시간.

				SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

				if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary) && pclCI->clIP.GetLevel() == 5)
				{
					pclserver->SendLog_SetEventCouponInfo(this, GOSTOP_POKER_EVENT,0);
				}
			}

			//KHY - 1024 - 한게임 VIP 이벤트- 기간설정
			//by LEEKH 2007.10.30 - 기간 변경
			if (pclClient->IsCountrySwitch(Switch_HanGameVIPEvent) )
			{		
				_SYSTEMTIME sStartEventDay , sEndEventDay;

				ZeroMemory(&sStartEventDay,sizeof(_SYSTEMTIME));
				ZeroMemory(&sEndEventDay,sizeof(_SYSTEMTIME));

				sStartEventDay.wYear = 2006;
				sStartEventDay.wMonth = 11;
				sStartEventDay.wDay = 8;
				sStartEventDay.wHour = 0;
				sStartEventDay.wMinute = 0;

				sEndEventDay.wYear = 2006;
				sEndEventDay.wMonth = 11;
				sEndEventDay.wDay = 30;
				sEndEventDay.wHour = 0;
				sEndEventDay.wMinute = 0;

				SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
				SI32 endEventdatevary = pclClient->GetMinuteFromsTime(sEndEventDay);

				_SYSTEMTIME fTimeDatevary = pclCI->clBI.GetFirstCreatTime(); //최초 계정 생성 시간.

				SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

				if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary) && pclCI->clIP.GetLevel() == 5)
				{
					pclserver->SendLog_SetEventCouponInfo(this, HAN_GAME_VIP_EVENT,2); // 2 = 5레벨 달성 이벤트 클리어.
				}
			}


			//KHY - 1025 - 나우콤 이벤트 - 기간설정. -10레벨 달성. - 11렙수정.
			if (pclClient->IsCountrySwitch(Switch_NowComEvent) )
			{
				_SYSTEMTIME sStartEventDay, sEndEventDay;

				ZeroMemory(&sStartEventDay,	sizeof(_SYSTEMTIME));
				ZeroMemory(&sEndEventDay,	sizeof(_SYSTEMTIME));

				sStartEventDay.wYear   = 2006;
				sStartEventDay.wMonth  =   11;
				sStartEventDay.wDay    =    8;
				sStartEventDay.wHour   =    0;
				sStartEventDay.wMinute =    0;

				sEndEventDay.wYear	 = 2006;
				sEndEventDay.wMonth  =   12;
				sEndEventDay.wDay	 =    5;
				sEndEventDay.wHour	 =    0;
				sEndEventDay.wMinute =    0;

				SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
				SI32 endEventdatevary   = pclClient->GetMinuteFromsTime(sEndEventDay);

				_SYSTEMTIME fTimeDatevary   = pclCI->clBI.GetFirstCreatTime(); //최초 계정 생성 시간.
				SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

				if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary) && pclCI->clIP.GetLevel() == 11)
				{
					pclserver->SendLog_SetEventCouponInfo(this, NOW_COM_EVENT, 2); // 2 = 10레벨 달성 이벤트 클리어.
				}
			}

#ifdef USE_PROMOTOR_SERVER
			if( true == bIsPromoter )
			{
				// 클라이언트에 프로모터 정보창과 연결된 작은 버튼을 보여주라는 메시지 전달. (보상을 받을 수 있는 레벨이 있다면)
				if( pclCI->clIP.GetLevel() < pclserver->pclRewardMgr->GetRecommendGiveItemMaxLevel() )
					pclserver->SendServerResponseMsg(0, SRVAL_PROMOTER_CHAR_LEVELUP_MINI_BUTTON, 0, 0, GetCharUnique());
			}
			
			// 중국은 핸드폰 인증이 되야만 아이템과 포인트를 준다.	
			if( /*true == bCellularPhoneAuth &&*/ true == bIsPromoter )
#endif
			{
				// 추천인이 있는지 확인한다. 
				SI32 recommenderpersonid = pclCI->clBI.clRecommenderInfo.siPersonID;
				SI32 recommendPoint		 = pclClient->GetRecommendPointPerLevel( pclCI->clIP.GetLevel() ); //레벨에 따른 추천포인트가 있는지 체크
				if( recommenderpersonid > 0 ) 
				{
					sDBRequest_ChangeRecommendPoint clMsg(  GetID() , pclCI->GetPersonID(), (TCHAR*)GetName(), 
															pclCI->clIP.GetLevel(), recommenderpersonid,  
															recommendPoint, RPGIVE_REASON_LEVELUP	);

					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				// 추천인을 등록해 두었다면 자신에게 아이템 지급
				if ( (0 < recommenderpersonid) && (true == pclClient->pclEventTimeManager->InEventTime(TEXT("RecommendReward"), &pclserver->sTime)) )
				{
					if( pclserver->pclRewardMgr )
					{
						pclserver->pclRewardMgr->GiveRecommendRewardItem( pclCI->GetPersonID(), pclCI->clIP.GetLevel(), true, NULL, bCellularPhoneAuth );
					}
				}
				else
				{
					if( recommenderpersonid > 0 && ( pclCI->clIP.GetLevel() == 40 || pclCI->clIP.GetLevel() == 50  || pclCI->clIP.GetLevel() == 60 || pclCI->clIP.GetLevel() == 70 )) 
					{
						SI32 itemunique = 0; //
						SI32 itemnum = 0;

						switch(pclCI->clIP.GetLevel())
						{
						case 40:	itemunique = ITEMUNIQUE(5055); //ITEMUNIQUE(5320);		
									itemnum = 20;	
									break;
						case 50:	itemunique = ITEMUNIQUE(5045); //ITEMUNIQUE(5316);		
									itemnum = 30;	
									break;
						case 60:	itemunique = ITEMUNIQUE(5017); //ITEMUNIQUE(5306);		
									itemnum = 40;	
									break;
						case 70:	itemunique = ITEMUNIQUE(24000);		
									itemnum = 30; 	
									break;
						}

						SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);

						if(itemunique > 0 && itemnum > 0 && ref > 0)
						{
							UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
							if ( GiveItem(itemunique, itemnum, INPUTITEMPERSON_OPTION_RECOMMEND , usedate) != GIVEITEM_RESULT_SUCCESS )
							{
								// 인벤토리에 직접 못넣으면 역참으로 보낸다.

								cltItem clInputItem;
								SI16 bRareSwitch = 0;
								pclClient->pclItemManager->MakeRandItemUnique(itemunique,&clInputItem,0,0,&bRareSwitch);

								clInputItem.siItemNum = itemnum;

								((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem , NULL ,0  );
							}
							else
							{
								cltLetterMsg_LevelUpREcommandReward clletter( pclCI->clIP.GetLevel(), itemunique , itemnum );
								pclserver->SendLetterMsg(  pclCI->GetPersonID() , (cltLetterHeader*)&clletter );					
							}

							if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
							{
								// [로그추가 : 황진성 2007. 10. 19] // 피추천인 보상.
								// param1 == 아이템 유니크.
								// param2 == 아이템 개수.
								pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_COMMENDER_REWARD, 
																0, this, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
																itemunique, itemnum, 0, 0, 0, NULL, NULL);
							}
						}
					}
				}
			}
#ifdef USE_PROMOTOR_SERVER	
			else if( true == bIsPromoter )
			{
				// 핸드폰 인증이 안되서 줄수 있는 아이템이 있는데 못줄때 메시지를 보낸다.
				if( pclserver->pclRewardMgr->IsGiveRecommendRewardItem( pclCI->GetPersonID(), pclCI->clIP.GetLevel(), true, NULL ) )
				{
					// 중국은 핸드폰 인증이 안되면 해당 메시지를 클라에 준다.
					//pclserver->SendServerResponseMsg(0, SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH, 0, 0, GetCharUnique());
					pclserver->SendServerResponseCharMsg2( 0, SRVAL_RECOMMEND_GIVE_ITEM_FAIL, NULL, NULL, NULL, GetCharUnique() );		

					SI32 recommenderpersonid = pclCI->clBI.clRecommenderInfo.siPersonID;
					if( recommenderpersonid > 0 ) 
					{
						SI32 siID = pclCM->GetIDFromPersonID(recommenderpersonid);
						cltCharServer* pRecommendeeChar = pclCM->GetCharServer( siID );
						if( pRecommendeeChar )
						{
							// 중국은 핸드폰 인증이 안되면 해당 메시지를 클라에 준다.
							//SendServerResponseMsg(0, SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH, 1, 0, pRecommendeeChar->GetCharUnique());

							pclserver->SendServerResponseCharMsg2( 0, SRVAL_RECOMMENDEE_GIVE_ITEM_FAIL, (TCHAR*)GetName(), NULL, NULL, pRecommendeeChar->GetCharUnique() );		
						}
					}
				}
			}
#endif
			//KHY - 0610 - 스승제자 S 추가수정.
			if ( ConstServiceArea_Japan != pclClient->siServiceArea )
			{
				//-------------------------------------
				// 스승이 있는지 확인한다. 
				//-------------------------------------
				if(pclCI->clBI.clFatherInfo.clFather.siPersonID)
				{
					if(pclCI->clIP.GetLevel() == NEWFATHER_LEVEL)
					{
						sDBRequest_PersonSimpleInfo clMsg(GetID(), pclCI->clBI.clFatherInfo.clFather.siPersonID, PERSONSIMPLEINFO_REASON_FATHERREWARD);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}

					if( false == pclCI->clBI.clFatherInfo.bOverTake )
					{
						if( pclCI->clIP.GetLevel() >= NEWFATHER_LEVEL )
						{
							sDBRequest_OverTakeTeacherLevel clMsg(GetID(), pclCI->clBI.clFatherInfo.clFather.siPersonID, pclCI->clIP.GetLevel(), pclCI->GetPersonID() );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}
					}
				}
			}


			if(pclCI->clIP.GetLevel() == FATHER_LEVEL)
			{
				//-------------------------------------
				// 스승이 있는지 확인한다. 
				//-------------------------------------

				if(pclCI->clBI.clFatherInfo.clFather.siPersonID)
				{
					if( ConstServiceArea_Japan == pclClient->siServiceArea )
					{
						sDBRequest_PersonSimpleInfo clMsg(GetID(), pclCI->clBI.clFatherInfo.clFather.siPersonID, PERSONSIMPLEINFO_REASON_FATHERREWARD);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}

					// 길드가 있는지 없는지 모르겠지만 일단 넣고 보자.
					sDBRequest_Guild_ChangeGuildPoint clMsg2(0,pclCI->clBI.clFatherInfo.clFather.siPersonID,1,TYPE_GUILDPOINT_ADD_CHILD);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);
				}


				//중국이 아닌 나라만 신입회원 정착금을 지원 한다 
				if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina))
				{
				}
				else
				{
					//-----------------------------------------------
					// 호조판서가 정한 신입회원 정착 자금을 지급한다.
					//-----------------------------------------------
					// 호조판서에 의한 자금을 구한다. 
					CMinisterHozo* pclminister = (CMinisterHozo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_HOZO);
					GMONEY money = pclminister->GetFizationMoney();

					// 피로방지 시스템 적용
					money = CalcTiredPoint( money );
					if(money)
					{
						// 왕실자산에 여유가 있는지 확인 안한다. 
						CMinisterGoonzu *pclministergoonzu = (CMinisterGoonzu *)pclserver->pclMinisterMgr->GetMinister(MINISTER_GOONZU);
						INT64 budget = pclministergoonzu->GetTotalFinances();
						//if(budget >= money)
						{
							// 왕실자신에서 자금을 소모시킨다.
							pclministergoonzu->RemoveFinances(money);

							sDBRequest_ChangeMoney clMsg(GetID(), pclCI->GetPersonID(), CHANGE_MONEY_REASON_FIZATION, money );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

							pclserver->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_LEVEL20, money);
						}

						if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
						{
							// [로그추가 : 황진성 2007. 9. 3] // 정착금. 
							//pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_???, LOGCOMMAND_INDEX_?????, 
							//									0, this, NULL, 0, money, 0, NULL, 0, 0, 0, 0, 0, 0, 
							//									0, 0, 0, 0, 0, NULL, NULL);*/
						}

					}
				}
			}

			// 초보자 사냥터 제한 레벨 이상이면, 
			if(pclCI->clIP.GetLevel() >= MAX_LEVEL_FOR_BEGINNERMAP)
			{
				// 초보자 사냥터에 있다면, 
				if(GetMapIndex() == MAPINDEX_BEGINNER1 )
				{
					WarpToSafeZone();
				}
			}
			// 파티 플레이 중이라면 파티원들에게 레벨업 알려줌
			if( siPartyIndex > 0)
			{
				CPartyObj* pParty =	pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
				if( pParty ) 
					pParty->NotifyLevelUpToPatryMember( GetCharUnique()  ,pclCI->clIP.GetLevel() );
			}	

			// [영훈] 초보자 마을
			if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
			{
				SI32 siGetPersonID	= pclCI->GetPersonID();
				SI32 siGetCharID	= GetID();
				SI32 siGetLevel		= pclCI->clIP.GetLevel();
				SI32 siGetVillage	= pclCI->clBI.siHomeVillage;


				// 레벨 30이 되었을때 캐릭터가 초보자 마을에 가입되어 있어야 주주배당금을 준다
				if ( (Const_BV_StockDividend_Level == siGetLevel) && (Const_Beginner_Village == siGetVillage) )
				{
					bool bCondition = false;

					// 초보자 마을의 주식이 10주 있는지 찾는다
					for ( SI32 siCount=0; siCount<MAX_STOCK_KIND_IN_ACOUNT; siCount++)
					{
						SI32 siFindVillageUnique	= pclCI->clStock.clInfo.clUnit[siCount].siVillageUnique;
						SI32 siFindStockAmount		= pclCI->clStock.clInfo.clUnit[siCount].siAmount;

						if ( Const_Beginner_Village == siFindVillageUnique )
						{
							if  ( 10 <= siFindStockAmount ) 
							{
								bCondition = true;
							}
							break;
						}
					}

					if ( true == bCondition )
					{
						// 세계금고(왕실자산)
						CMinisterGoonzu	*pclMinisterGoonzu	= (CMinisterGoonzu*)pclserver->pclMinisterMgr->GetMinister(MINISTER_GOONZU);
						// 공작에서 초보자 마을 주주배당금 가져오기
						CMinisterHozo	*pclMinisterHozo	= (CMinisterHozo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_HOZO);

						if ( (pclMinisterGoonzu != NULL) && (pclMinisterHozo != NULL) )
						{
							GMONEY gmBVMoney = (SI32)pclMinisterHozo->GetBeginnerVillageMoney();

							// 세계금고에서 자금을 소모시킨다
							pclMinisterGoonzu->RemoveFinances( gmBVMoney );

							sDBRequest_ChangeMoney clMsg(siGetCharID, siGetPersonID, CHANGE_MONEY_REASON_BV_STOCKDIVIDEND, gmBVMoney );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

							pclserver->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_ANKALANSTOCK30, gmBVMoney);
						}
					}	// if ( true == bCondition ) 종료
				}	// if ( (Const_BV_StockDividend_Level == siGetLevel) && (Const_Beginner_Village == siGetVillage) ) 종료

				// 레벨 40이되면 초보자 마을에서 탈퇴시킨다
				if ( (Const_BV_Max_Resident_Level == siGetLevel) && (Const_Beginner_Village == siGetVillage) )
				{
					sDBRequest_CancelResident clMsg( siGetCharID, siGetPersonID, Const_Beginner_Village, true );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			} // if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) ) 종료

			if ( pclClient->IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();

				if ( pclSE_Quest )
				{
					SI32 siMyLevel	= pclCI->clIP.GetLevel();
					SI32 siAmount	= max( 1, siQuestCount );

					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_LEVELUP, siMyLevel, siAmount );
				}

			}	// ( pclClient->IsCountrySwitch(Switch_Server_Event) ) 종료
	}
}

// 경험치를 올리고 필요한 모든 조치를 취한다. 
bool cltCharServer::IncreaseExp(SI64 exp, SI32 reason)// SI32->SI64 경험치 오버플로우때문에 수정	
{
	if(pclCM->IsAlive(GetID()) == FALSE &&
		reason != GETEXP_REASON_VILLAGEWARKILLSCORE)		return false;

	if(pclCI->clIP.IncreaseExp(exp) == TRUE)// SI32->SI64 경험치 오버플로우때문에 수정	
	{
		LevelUpAction();
		return true;
	}
	else
	{
		// 경험치 얻었음을 통보한다. 
		cltGameMsgResponse_GetExp clinfo(GetCharUnique(),  exp, 0, reason);
		cltMsg clMsg(GAMEMSG_RESPONSE_GETEXP, sizeof(clinfo), (BYTE*)&clinfo);

		// 소환수여서 부모가 있으면 부모한테 전송한다.
		SI32 siParentID = GetSummonParentID();
		if(pclCM->IsAlive(siParentID))
		{
			pclCM->CR[siParentID]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}




	return false;

}

// 명성 경험치를 올리고 필요한 모든 조치를 취한다. 
bool cltCharServer::IncreaseFameExp(SI32 exp, SI32 reason)
{

	cltServer* pclserver = (cltServer*)pclClient;
	TCHAR Nbuffer[512]=TEXT(" ");

	if(pclCI->clIP.IncreaseFameExp(exp) == true)
	{

		if(pclCI->clIP.siFameLevel < 100)
		{
			pclCI->clIP.siFameLevel++;

			// 클라이언트 정보를 업데이트 한다. 
			SetUpdateSwitch(UPDATE_IP, true, 0);

			// DB에 정보를 보낸다. 
			SendDBLevelInfo(0, 0);	

			// 클라이언트로 레벨이 올랐음을 통보한다. (JAYCEE : 이웃에게도 통보를 한다.)
			cltGameMsgResponse_LevelUp clinfo(GetCharUnique(), 0, pclCI->clIP.siFameLevel);
			cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUP, sizeof(clinfo), (BYTE*)&clinfo);
			SendNeighbourMsg(&clMsg, true);

			/*
			SI32 itemunique = 0;
			if(pclCI->clIP.siFameLevel == 10)
			{
				itemunique	= 13095;	// 군주프렌즈모자. 
				pclserver->pclStatisticsManager->clDailyStatistics.siFameLevel10Num++;
			}
			else if(pclCI->clIP.siFameLevel == 20)
			{
				itemunique	= 18100;	// 빨간망토. 
				pclserver->pclStatisticsManager->clDailyStatistics.siFameLevel20Num++;
			}
			else if(pclCI->clIP.siFameLevel == 30)
			{
				itemunique	= 13098;		// 엠씨스퀘어모자
				pclserver->pclStatisticsManager->clDailyStatistics.siFameLevel30Num++;
			}
			else if(pclCI->clIP.siFameLevel == 40)
			{
				itemunique	= 9400;		// 포도대장복
				pclserver->pclStatisticsManager->clDailyStatistics.siFameLevel40Num++;
			}

			if(itemunique)
			{
				cltItem clitem;
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
				if(ref >= 0)
				{
					if(pclClient->pclItemManager->pclItemInfo[ref])
					{
						clitem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
						clitem.siItemNum = 1;

						//인벤에 넣어본다. 
						SI32 rtnvalue = 0;
						if(InputItem(pclClient->pclItemManager, &clitem, INPUTITEMPERSON_OPTION_FAMELEVEL, &rtnvalue) == false)
						{
							// 실패하면 역참으로 보낸다. 
							TCHAR buffer[256];
							TCHAR* pText = GetTxtFromMgr(531);
							TCHAR grade[128]= TEXT(" ") ;
							sprintf(grade,TEXT("%d"),pclCI->clIP.siFameLevel);

							Nsprintf(Nbuffer,pText,TEXT("grade"), grade   ,TEXT("item"),  clitem.GetShortName(pclClient->pclItemManager)  ,NULL);
							//sprintf(buffer, pText, pclCI->clIP.siFameLevel, clitem.GetShortName(pclClient->pclItemManager));
							pclserver->SendPostOfficeItemToPerson((TCHAR*)GetName(), &clitem, buffer);
						}

					}
				}

				if(clitem.siUnique)
				{
					cltGameMsgResponse_FameLevelReward clinfo((TCHAR*)GetName(), pclCI->clIP.siFameLevel, &clitem);
					cltMsg clMsg(GAMEMSG_RESPONSE_FAMELEVELREWARD, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
				}
			}*/

				return true;
		}

	}
	else
	{
		// 경험치 얻었음을 통보한다. 
		cltGameMsgResponse_GetExp clinfo(GetCharUnique(),  0, exp, reason);
		cltMsg clMsg(GAMEMSG_RESPONSE_GETEXP, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);

	}

	return false;

}



// 캐릭터의 머릿말을 설정한다. 
void cltCharServer::SetHeadChat(bool bheadchatswitch, TCHAR* ptext)
{
	bHeadChatSwitch = bheadchatswitch;
	if(ptext)
	{
		MStrCpy( szHeadChatText, ptext, MAX_HEAD_CHAT_TEXT_SIZE );
	}
}

void cltCharServer::SetPersonalShopBanner(cltShopTradeData* pclshopdata)
{
	if(pclshopdata)
	{
		clShopBanner.SetData(pclshopdata);
	}
}

// 캐릭터의 PersonalShop정보를 설정한다.
void cltCharServer::SetPersonalShopData(bool bpersonalshopswitch, cltShopTradeData* pclshopdata)
{
	/*
	SI32			m_siPersonID;
	TCHAR			m_szAccountID[MAX_PLAYER_NAME];
	BOOL			m_ShopMode;			// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	cltItem			m_clItem[ MAX_SHOP_ITEM_NUMBER ];
	SI16			m_siSelectedInventoryPos[ MAX_SHOP_ITEM_NUMBER ];
	SI32			m_siPrice[ MAX_SHOP_ITEM_NUMBER ];*/

		bPersonalShopSwitch = bpersonalshopswitch;

	if( bPersonalShopSwitch == false )
	{
		bPremiumPersonalShop = false;
	}

	if(pclshopdata)
	{
		clShopData.Set(pclshopdata);

		bPremiumPersonalShop = pclshopdata->m_bPremium;
	}
}

void cltCharServer::SetRepairShopData( bool bRepairShopSW, cltShopRepairData* pclRepairData )
{
	bRepairShopSwitch = bRepairShopSW;

	if( bRepairShopSwitch == false )
	{
		if( m_pclShopRepairData )		m_pclShopRepairData->Init();
		return;
	}

	if( m_pclShopRepairData && pclRepairData )
	{
		m_pclShopRepairData->Set( pclRepairData );
	}
}

bool cltCharServer::AfterCharAction()
{

	// 정보가 변경되면 클라이언트에게 통보한다.
	//if(IsPC(GetCharUnique()) == true || clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
	{
		SendChangedDataToClient();
	}

	// 공성전 중에 내가 마을에 들어가 있고
	if(pclClient->bVillageWarSwitch && GetCurrentVillageUnique() > 0 && GetCurrentVillageUnique() < MAX_VILLAGE_NUMBER)
	{
		// 내 주소지와 현재있는 마을과 서로 적대관계일경우 
		if(pclClient->pclVillageManager->IsAggressiveVillage(pclCI->clBI.siHomeVillage, GetCurrentVillageUnique()))
		{
			SI32 siCastleUnique = 0;
			// 성문이 살아 있이으면 마을 밖으로 튕겨낸다.
			if(pclClient->pclVillageManager->IsThereCastle(GetCurrentVillageUnique(), &siCastleUnique))
			{
				if(pclCM->IsAlive(siCastleUnique))
				{

					SI32 dx, dy;
					if(pclClient->pclMapManager->pclMapArray[0]->FindEmptyAreaForCharLocate(GetKind(), 
						pclClient->pclVillageManager->pclVillageInfo[ GetCurrentVillageUnique()]->PosX,
						pclClient->pclVillageManager->pclVillageInfo[ GetCurrentVillageUnique()]->PosY,
						20, 
						&dx, &dy, true) == true)
					{
						cltWarpInfo clWarpInfo(true, 0, false, false, dx, dy, -1, -1);
						SetWarpInfo(&clWarpInfo, 300);
					}
				}
			}
		}
	}

	//cyj 흑의 군대 맵안에 있을경우
	bool bWarpOut = false;
	if (IsPC(siID))
	{
		if ( GetMapIndex() >= BLACKARMY_MAP_STARTINDEX && GetMapIndex() < BLACKARMY_MAP_STARTINDEX + MAX_BLACKARMY_MAP_CNT)
		{
			// 전쟁시간이 아니면 워프 안함
			if ( pclClient->pclBlackArmyManager->bWarSwitch == false)
			{
				bWarpOut = true;
			}
			else 
			{
				if (siBlackArmyWarMapIndex >= 0 && siBlackArmyWarMapIndex < MAX_BLACKARMY_MAP_CNT)
				{
					// 전쟁맵에 배정받았으나 해당 맵이 아닌 맵으로 있을시에는 밖으로
					if (GetMapIndex() != pclClient->pclBlackArmyManager->clWarMap[siBlackArmyWarMapIndex].siMapIndex)
					{
						bWarpOut = true;
					}

					// 전쟁맵에 배정받았으나 해당맵이 전쟁이 끝난경우 밖으로
					if (pclClient->pclBlackArmyManager->clWarMap[siBlackArmyWarMapIndex].bWarDoing == false)
					{
						bWarpOut = true;
					}

				}
				// 전쟁맵에 배정받지 않았으면 밖으로
				else
				{
					bWarpOut = true;
				}
			}

			if (bWarpOut)
			{

				SI32 warmapindex = GetMapIndex() - BLACKARMY_MAP_STARTINDEX;

				if (warmapindex >= 0)
				{
					cltGate* gate = NULL;
					if( BLACKARMY_GATEUNIQUE_START + warmapindex >= 0 && 
						BLACKARMY_GATEUNIQUE_START + warmapindex < MAX_GATE_NUMBER )
					{
						gate = &pclClient->pclMapManager->pclGateManager->clGate[BLACKARMY_GATEUNIQUE_START + warmapindex];
					}

					if(gate)
					{
						cltWarpInfo clWarp(true, gate->SrcMapIndex, false, false, gate->SrcX, gate->SrcY, -1, -1 );
						SetWarpInfo(&clWarp,56);
					}
				}
			}
		}
	}
	return false;
}

// 게임 플레이 시간을 계산한다. 
void cltCharServer::CalcPlayTime()
{
	DWORD playsecond = TABS(pclClient->CurrentClock - dwStartClock) / 1000;
	dwStartClock = pclClient->CurrentClock;
	pclCI->clBI.siPlaySecond += playsecond;
	pclCI->clBI.siPlayEventSecond += playsecond;
	dwPlayingTime += playsecond;

	dwInstantPlayTime += playsecond;

	cltServer* pclserver = (cltServer*)pclClient;

	// 출석체크
#ifdef _DEBUG
	DWORD	attendInterval = 30;			// 접속후 출석 체크 메세지 보내는 시간
#else
	DWORD	attendInterval = pclserver->siAttendCheckMinute * 60;
#endif 

	if ( dwInstantPlayTime > attendInterval )
	{
		NDate Today;
		Today.SetDate( pclserver->sTime.wYear, pclserver->sTime.wMonth, pclserver->sTime.wDay );

		if ( Today.GetDateVary() >= pclserver->clAttendEventStart.GetDateVary() &&
			Today.GetDateVary() <= pclserver->clAttendEventEnd.GetDateVary() )
		{
			// 출석 버튼을 눌렀는데 찍을 필요 없음
			if ( (pclCI->clBI.bAttendToday[ ATTEND_EVENTTYPE_ATTENDANCE ] == false) 
				&& (pclCI->clBI.bIsAttendTime == false)
				)
			{
				cltGameMsgResponse_DemandAttend clInfo( -1,-1, ATTEND_EVENTTYPE_SEASON2, true );
				cltMsg clMsg( GAMEMSG_RESPONSE_DEMANDATTEND, sizeof(clInfo), (BYTE*)&clInfo );
				SendNetMsg( (sPacketHeader*)&clMsg );
			}
			// 출석할 시간이 되었다
			if ( pclCI->clBI.bIsAttendTime == false )
			{
				pclCI->clBI.bIsAttendTime = true;
			}
		}
	}

	// 피로방지- 여기서는 uiTiredState 의 상태변경을 다루지 않고,  CharServer_Action 의 CHAR_UPDATETIMER_TIREDSYSTEM_TIME_LIMIT 부분에서 다룬다.
	/*
	if( true == bTiredSystem )
	{
		if( dwPlayingTime > 60 * 60 * 3 && dwPlayingTime <= 60 * 60 * 5)
		{
			// 변경 되었을경우 클라이언트로 보냄
			if ( uiTiredState != TIRED_STATUS_LITTLE_TIRED )
			{
				cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS , TIRED_STATUS_LITTLE_TIRED );
				SendNetMsg((sPacketHeader*)&clMsg);
				// 정상 수치의 반만 받는다.
				uiTiredState = TIRED_STATUS_LITTLE_TIRED;
			}
		}
		else if( dwPlayingTime > 60 * 60 * 5 )
		{
			if ( uiTiredState != TIRED_STATUS_MUCH_TIRED )
			{
				cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS , TIRED_STATUS_MUCH_TIRED );
				SendNetMsg((sPacketHeader*)&clMsg);
				// 아무것도 받지 못 한다.
				uiTiredState = TIRED_STATUS_MUCH_TIRED;
			}
		}
		else
		{
			if ( uiTiredState != TIRED_STATUS_NORMAL )
			{
				cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS , TIRED_STATUS_NORMAL );
				SendNetMsg((sPacketHeader*)&clMsg);
				uiTiredState = TIRED_STATUS_NORMAL;
			}
		}
	}
	*/
	// 광명 (마을 있는 사람에 대해서 플레이 시간을 구한다)
	if( pclCI->clBI.siHomeVillage > 0 && pclCI->clBI.siHomeVillage <= CUR_VILLAGE_LIMIT)
		pclCI->clBI.clVillageScoreInfo.siPlayTime += playsecond;

}


// 인공지능 치료. 
bool cltCharServer::HealAI()
{
	SI32 magickind = MAGIC_MON_HEAL;
	if(pclKI->siMagic != magickind)return false;

	if(TABS(pclClient->CurrentClock - dwLastMagicClock) < 5000)return false;

	dwLastMagicClock = pclClient->CurrentClock;

	bool bwarswitch = false;


	SI32 id = pclCM->FindDamagedFriend(GetID(), GetMapIndex(), GetX(), GetY(), bwarswitch);
	if(id == 0)return false;

	SI32 returnval = 0;
	if(CanMagic(id, magickind, &returnval) == true)
	{
		bBusySwitch = false;

		pclClient->pclOrderManager->OrderMagic(GetID(), id, magickind, BY_COMPUTER);

		return true;		
	}

	return false;

}



// 클라이언트가 서버로 보낸 마지막 메시지와의 시간 간격을 확인한다. 
bool cltCharServer::CheckLastMsgClock(DWORD interval)
{
	if(TABS(pclClient->CurrentClock - dwLastSendServerClock) < (int)interval)	return true;

	dwLastSendServerClock = pclClient->CurrentClock;

	return false;
}

// 아이템몰의 악의적 데이터 갱신을 체크한다. 1초에 5회 이상의 요청을 방지
bool cltCharServer::CheckItemMallBadRequest()
{
	static SI32 requestCnt = 0;
	static DWORD startedClock = 0;

	if(requestCnt == 0)
	{
		startedClock = pclClient->CurrentClock;
	}	
	else if(requestCnt == 10 )
	{
		if(pclClient->CurrentClock - startedClock  < 1000  )
			return false;
	}

	requestCnt++;
	if(requestCnt > 10)
		requestCnt = 0;

	return true;
}


// 배고프게 만든다. 
void cltCharServer::MakeHunger(SI32 addHunger)
{
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))return ;

	SI32 hunger = max(1, pclCI->clIP.GetLevel() / 8);

	// 제한량 이상의 무게를 지고 다니면 배고픈 정도가 2.5배
	if ( pclClient->siServiceArea != ConstServiceArea_China )
	{
		if(pclCI->clCharItem.GetTotalWeight(pclClient->pclItemManager) >= clPB.GetMaxWeight())
		{
			hunger = hunger * 5 /2;
		}
	}

	hunger = hunger + addHunger;

	clPB.clHealth.DecreaseHungry(hunger);
	SetUpdateSwitch(UPDATE_HEALTH, true, 0);

}

void cltCharServer::SetUpdateSwitch(SI32 updatetype, bool mode, SI32 para1)
{
	if(updatetype < 0 && updatetype >= MAX_UPDATE_SWITCH)		return;

	clUpdateInfo[updatetype].bMode		= mode;
	clUpdateInfo[updatetype].siPara1	= para1;
}

void cltCharServer::SetWasteDurUpdateSwitch(SI32 itemposition, bool mode)
{
	if(itemposition < 0 && itemposition >= MAX_ITEM_PER_PERSON)		return;

	if(mode)
	{
		clSimpleVary.bWasteDurSwitch = true;
	}

	clSimpleVary.WasteDurUpdateSwitch[itemposition] = mode;
}

void cltCharServer::SetSummonWasteDurUpdateSwitch( SI32 SummonIndex, SI32 itemposition, bool mode )
{
	if( SummonIndex < 0 || SummonIndex >= clSimpleVary.bSummonWasteDurSwitch.GetSize() )						return;
	if( itemposition < 0 || itemposition >= clSimpleVary.SummonWasteDurUpdateSwitch[SummonIndex].GetSize() )	return;

	if(mode)
	{
		clSimpleVary.bSummonWasteDurSwitch[SummonIndex] = true;
	}

	clSimpleVary.SummonWasteDurUpdateSwitch[SummonIndex][itemposition] = mode;
}

//KHY - 0227 - 결정체 (크리스탈) 제조 추가. -
//이곳에서 결정체의 내구도를 깍는다 - 공격시, 무기.
void cltCharServer::SetCrystalDurUpdateSwitch(SI32 itemposition, bool mode)
{
	if(itemposition < 0 && itemposition >= MAX_SHAPE_ITEM)		return;

	//if(pclClient->GameMode != GAMEMODE_SERVER)		return;
	//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[GetID()];

	if(mode)
	{
		clSimpleVary.bCrystalDurSwitch = true;
	}

	clSimpleVary.CrystalDurUpdateSwitch[itemposition] = mode;
}

void cltCharServer::SubDecreaseCrystalDur(SI16 ActiveItem,SI16 durvary)
{
	cltItem* pclitem;
	pclitem = (cltItem*)&pclCI->clCharItem.clItem[ActiveItem];

	if(pclitem->siUnique != 0 )
	{
		// 내구도를 소모시킨다.
		if(pclitem->DecreaseCrystalDurability(pclClient->pclItemManager, durvary))
		{
			// 내구도가 소모되었음을 표시해둔다.
			SetCrystalDurUpdateSwitch(ActiveItem, true);
		}
	}
}
void cltCharServer::DecreaseCrystalDurAC(SI16 durvary)
{
	// 무기는 액티부 웨폰만 감소시킨다.
	SubDecreaseCrystalDur(ActiveWeapon,durvary);
}

//이곳에서 결정체의 내구도를 깍는다 - 방어시, 방어구 전부.
void cltCharServer::DecreaseCrystalDurDE(SI16 durvary)
{
	// 방어구는 모두 감소킨다. - 추후 변동사항은 이곳에서 처리한다.
	SubDecreaseCrystalDur(PERSONITEM_HELMET,durvary);
	SubDecreaseCrystalDur(PERSONITEM_ARMOUR,durvary);
	SubDecreaseCrystalDur(PERSONITEM_BELT,durvary);
	SubDecreaseCrystalDur(PERSONITEM_SHOES,durvary);

	// 아바타 결정체는 내구도를 감소 시키지 않는다.
	//SubDecreaseCrystalDur(PERSONITEM_NECK,durvary);
	//SubDecreaseCrystalDur(PERSONITEM_RING1,durvary);
	//SubDecreaseCrystalDur(PERSONITEM_RING2,durvary);
	//SubDecreaseCrystalDur(PERSONITEM_MANTLE,durvary);
	//SubDecreaseCrystalDur(PERSONITEM_HAT,durvary);
	//SubDecreaseCrystalDur(PERSONITEM_DRESS,durvary);
}

void cltCharServer::SubSendClientCrystalDurability(SI16 ActiveItem)
{
	cltItem* pclitem;
	pclitem = (cltItem*)&pclCI->clCharItem.clItem[ActiveItem];

	if(pclitem->siUnique != 0 )
	{
		// 내구도가 1%단위로 변했는지 확인한다.
		if(pclitem->GetDecreaseCrystalDurabilityPer(pclClient->pclItemManager))
		{			
			// 내구도가 소모되었음을 클라이언트로 알린다.
			cltGameMsgResponse_CrystalItemInfo clinfo(ActiveItem , pclitem);
			cltMsg clMsg(GAMEMSG_RESPONSE_CRYSTALITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}


// 변경된 결정체 내구도 정보를 Client로 보낸다.
void cltCharServer::SendClientCrystalDurability( )
{
	/*for(SI16 pos = 0; pos <PERSONITEM_INV0 ; pos++)
	{
		switch(pos)
		{
		case PERSONITEM_HELMET :
		case PERSONITEM_ARMOUR :
		case PERSONITEM_NECK :
		case PERSONITEM_RING1 :
		case PERSONITEM_RING2 :
		case PERSONITEM_BELT :
		case PERSONITEM_SHOES :
		case PERSONITEM_MANTLE :
		case PERSONITEM_HAT :
		case PERSONITEM_DRESS :
			SubSendClientCrystalDurability(pos);
			break;
		}		
	}
	*/
		SubSendClientCrystalDurability(PERSONITEM_HELMET);
	SubSendClientCrystalDurability(PERSONITEM_ARMOUR);
	SubSendClientCrystalDurability(PERSONITEM_BELT);
	SubSendClientCrystalDurability(PERSONITEM_SHOES);

	SubSendClientCrystalDurability(ActiveWeapon);
}

void cltCharServer::SubDecreaseCrystalDurForSummon( SI16 siActiveItem, SI16 siDurvary )
{
	SI32 siParentID = GetSummonParentID();
	if ( FALSE == pclCM->IsValidID(siParentID) )
	{
		return;
	}

	cltCharServer* pclParentChar = (cltCharServer*)pclCM->CR[siParentID];
	if ( NULL == pclParentChar )
	{
		return;
	}

	SI16 siSummonIndex = GetSummonIndex();
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	cltItem* pclitem = pclParentChar->pclCI->clSummonInfo.GetSummonEquipItem( siSummonIndex, siActiveItem );
	if ( NULL == pclitem )
	{
		return;
	}

	if ( 0 < pclitem->siUnique )
	{
		// 내구도를 소모시킨다.
		if ( pclitem->DecreaseCrystalDurability(pclClient->pclItemManager, siDurvary) )
		{
			// 내구도가 소모되었음을 표시해둔다.
			SetCrystalDurUpdateSwitch( siActiveItem, true );
		}
	}

}


void cltCharServer::DecreaseCrystalDurACForSummon( SI16 siDurvary )
{
	// 무기는 액티부 웨폰만 감소시킨다.
	SubDecreaseCrystalDurForSummon( ActiveWeapon, siDurvary );

}

void cltCharServer::DecreaseCrystalDurDEForSummon( SI16 siDurvary )
{
	// 나중에 장착아이템이 추가될수도 있기때문에 장비아이템 전부를 체크한다
	SubDecreaseCrystalDurForSummon( PERSONITEM_HELMET,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_ARMOUR,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_NECK,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_RING1,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_RING2,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_BELT,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_SHOES,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_MANTLE,	siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_HAT,		siDurvary );
	SubDecreaseCrystalDurForSummon( PERSONITEM_DRESS,	siDurvary );
}

void cltCharServer::SendClientCrystalDurabilityForSummon()
{
	SI32 siParentID = GetSummonParentID();
	if ( FALSE == pclCM->IsValidID(siParentID) )
	{
		return;
	}

	cltCharServer* pclParentChar = (cltCharServer*)pclCM->CR[siParentID];
	if ( NULL == pclParentChar )
	{
		return;
	}

	SI16 siSummonIndex = GetSummonIndex();
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	for ( SI32 siPos=0; siPos<MAX_SHAPE_ITEM; ++siPos )
	{
		cltItem* pclItem = pclParentChar->pclCI->clSummonInfo.GetSummonEquipItem( siSummonIndex, siPos );
		if ( (NULL == pclItem) || (0 >= pclItem->siUnique) )
		{
			continue;
		}

		if ( pclItem->GetDecreaseCrystalDurabilityPer(pclClient->pclItemManager) )
		{
			cltGameMsgResponse_SummonChangeItem clInfo( siSummonIndex, siPos, pclItem );
			cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clInfo), (BYTE*)&clInfo );
			pclParentChar->SendNetMsg( (sPacketHeader*)&clMsg );
		}
	}

}

void cltCharServer::SetSkillUpdate(SI32 skillunique, SI32 addskillexp)
{
	//=================================================
	// 범위 검사
	//=================================================
	if(skillunique < 0 || skillunique >= MAX_SKILL_NUMBER) return;

	if( addskillexp < 1 ) return;

	clSimpleVary.SkillUpdateSwitch[skillunique] = true;
	clSimpleVary.bSkillExpUpdateSwitch			= true;

	//=================================================
	// Person 의 Skill 정보 Update전 
	//=================================================
	SI32 oldskilllevel	= pclCI->clCharSkill.GetSkillExpLevel(skillunique);

	pclCI->clCharSkill.clSkill[skillunique].siSkillExp	+= addskillexp;	// 스킬 경험치증가 

	cltGameMsgResponse_OneSkill clInfo(skillunique, &pclCI->clCharSkill.clSkill[skillunique]);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_ONESKILL, sizeof(clInfo), (BYTE*)&clInfo);
	SendNetMsg((sPacketHeader*)&clMsg);

	//=================================================
	// Person 의 Skill 정보 Update 후 
	//=================================================
	SI32 newskilllevel	= pclCI->clCharSkill.GetSkillExpLevel(skillunique);
	if(oldskilllevel < newskilllevel)					// 경험기술 레벨이 올랐다면, 
	{
		cltServer* pclserver = (cltServer*)pclClient;

		SI32 totalskilllevel = pclCI->clCharSkill.clSkill[skillunique].uiLevel + newskilllevel;			
		pclserver->SendServerResponseMsg(0, SRVAL_SETSKILL,  skillunique, totalskilllevel, GetCharUnique());
		// 길드가 있다면
		if ( pclCI->clBI.clGuildRank.IsGuildMember() == true )
		{
			cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
			if ( pGuild )
			{
				sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCI->GetPersonID(),6,TYPE_GUILDPOINT_ADD_SKILLLEVELUP);
				pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}

		//KHY - 1205 - 유저레벨업 공지
		if (pclClient->IsCountrySwitch(Switch_LevelUpNotice) )
		{
			if(IsPC(GetCharUnique()))
			{
				TCHAR szName[MAX_PLAYER_NAME];
				MStrCpy( szName, GetName(), MAX_PLAYER_NAME );

				if (pclCI->clBI.clGuildRank.IsGuildMember() == true ) //길드.
				{
					cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
					if ( pGuild )
					{
						cltGameMsgResponse_LevelUpNotice clinfo(szName, 0, totalskilllevel , skillunique , 1);
						cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
						//KHY - 0131 - 길드 멤버 메시지 전달 - 이름으로 검색 - 유니크번호 검사제외!
						pclClient->pclCM->SendAllGuildMemberMsg((sPacketHeader*)&clMsg,pGuild->siUnique,pGuild->szName);

					}
				}

				if(pclCI->clBI.siHomeVillage > 0 && pclCI->clBI.siHomeVillage <= CUR_VILLAGE_LIMIT) //마을 
				{

					//KHY - 1205 - 유저레벨업 공지
					cltGameMsgResponse_LevelUpNotice clinfo(szName, 0, totalskilllevel , skillunique , 2);
					cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg,pclCI->clBI.siHomeVillage);

				}
			}
		}
		cltSkillInfo* pclskillinfo = pclserver->pclSkillManager->pclSkillInfo[skillunique];
		if ( ( pclskillinfo->siSkillAtb & SKILLATB_LIST) != 0 )
		{
			if( newskilllevel % 5 == 0 )
			{
				SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

				// 장인 육성 지원금 변경
				// 기술레벨*기술레벨*NPCRATE*5+40000;
				CMinisterGongzo *pclminister = (CMinisterGongzo *)pclserver->pclMinisterMgr->GetMinister(MINISTER_GONGZO);
				GMONEY money = newskilllevel * newskilllevel * npcrate * 5 + 40000;

				// 추가 육성 지원금(공조판서가 정함) 
				GMONEY addCraftFund = pclminister->m_stGongzoMember.siCraftFund;
				money = money + ( money * addCraftFund / 100 );

				// 피로방지 시스템 적용
				money = CalcTiredPoint( money );

				if(money)
				{
					// 왕실자산에 여유가 있는지 확인 안한다. 
					CMinisterGoonzu *pclministergoonzu = (CMinisterGoonzu *)pclserver->pclMinisterMgr->GetMinister(MINISTER_GOONZU);
					INT64 budget = pclministergoonzu->GetTotalFinances();
					//if(budget >= money)
					{
						// 왕실자신에서 자금을 소모시킨다. 중국은 막음
						pclministergoonzu->RemoveFinances(money);

						sDBRequest_ChangeMoney clMsg(GetID(), pclCI->GetPersonID(), CHANGE_MONEY_REASON_CRAFTFUND, money );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

						pclserver->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_SKILLMONEY, money);
					}

				}

			}
		}


		// 무기술의 달인 - 엠블렘
		if ( (PERSONITEM_WEAPON1 == ActiveWeapon) || (PERSONITEM_WEAPON2 == ActiveWeapon) )
		{
			SI32 siItemType				= pclCI->clCharItem.GetWeaponType( pclClient->pclItemManager, ActiveWeapon );
			SI32 siWeaponSkillUnique	= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
			UI08 uiGetEmblem			= 0;

			// 현재 사용하는 무기의 스킬만 검사한다
			if ( siWeaponSkillUnique == skillunique )
			{
				uiGetEmblem = pclClient->pclSkillManager->m_clMasterManager.GetEmblemIndex( siItemType, newskilllevel );

				if ( m_uiWeaponSkillMasterEmblem != uiGetEmblem )
				{
					m_uiWeaponSkillMasterEmblem = uiGetEmblem;

					cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_EMBLEM, false, uiGetEmblem );
					cltGameMsgResponse_StatusInfo	clInfo( GetCharUnique(), &clChangeInfo );

					cltMsg clEmblenMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo);
					SendNeighbourMsg( &clEmblenMsg, true );
				}
			}
		}	// 종료	if ( (PERSONITEM_WEAPON1 == ActiveWeapon) || (PERSONITEM_WEAPON2 == ActiveWeapon) ) 
	}

}

BOOL cltCharServer::DoAnimationDelay(BOOL atb)
{
	SI32	delay;
	SI32	framenumber;

	bool	IsHero = GetKindInfo(true)->IsAtb(ATB_HERO);

	// by LEEKH 2007.12.24 - TRANSFORM
	if( clTransFormInfo.bTransFormMode == true )
	{
		// 변신인 경우... 변신전 캐릭터의 무기로 에니메이션을 처리한다.- 서버만...
		if( Animation == ANITYPE_ATTACK || Animation == ANITYPE_ATTACK1 || Animation == ANITYPE_ATTACK2 )
		{
			IsHero = true;
		}
	}

	if( IsHero )
	{
		framenumber = pclCharDraw->GetFrameNum(HeroAnimation);
		delay		= pclCharDraw->GetDelayTime(HeroAnimation, GetKind() );
	}
	else
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 aniref	= GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(Animation);

		if(aniref == -1)
		{			
			return FALSE;
		}

		// by LEEKH 2007.12.24 - TRANSFORM
		framenumber = GetKindInfo(true)->clCharAniManager.GetFrameNum(aniref);
		delay		= GetKindInfo(true)->clCharAniManager.GetDelay(aniref);
	}

	if(framenumber == 0)
	{
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("GetFrameNum() Kind:%d ani:%d"), GetKind(), Animation);
	}


	// 한번만 애니메이션 하게 되어 있는 경우, 
	clAniInfo.dwElapsedClock = min(10000, (pclClient->CurrentClock - clAniInfo.dwAniStartClock));

	SI32 frame = 0;
	if(delay == 0)
	{
		frame = 0;
	}
	else
	{
		DWORD dwdata	= clAniInfo.dwElapsedClock / (delay * 50);
		SI32 sidata		= (SI32)dwdata;
		frame = min(framenumber - 1, sidata);
	}
	// 이전 동작이 마지막 동작이었다면 첫 동작으로 간다. 
	if(clAniInfo.GetAniStep() == (framenumber - 1))
	{
		clAniInfo.SetAniStep(0);
		clAniInfo.dwAniStartClock	= pclClient->CurrentClock;
		clAniInfo.dwElapsedClock	= 0;

		return TRUE;
	}
	else
	{
		SI32 oldframe = clAniInfo.GetAniStep();
		if(oldframe != frame)
		{
			clAniInfo.SetAniStep(frame);

			return TRUE;
		}
	}


	return FALSE;
}


void cltCharServer::CharServerStatusAction()
{

	// 독이 중독되었을때 독이 해제가 된다면 
	if( clInnerStatus.IsStatus(INNERSTATUS_POISON) || clInnerStatus.IsStatus(INNERSTATUS_POISON_SETITEM_EFFECT) )
	{
		// 1초 마다 에너지를 감소시킨다.
		if(TABS(pclClient->CurrentClock - dwPoisonCheckClock) > 2000)
		{
			dwPoisonCheckClock = pclClient->CurrentClock;

			if(GetLife() > 0) 
			{
				cltAttackTarget cltarget(GetID(), &pclCI->clBI.clPos, 10000,0); // 기준변경 - 100%는 10000 이다.
				cltAttackDamageInfo cldamageinfo(ATTACKTYPE_POISONSTATUS, siPoisonPower, 0);
				((cltServer*)pclClient)->HitOperation(siPoisonCharUnique, &cldamageinfo, 1, &cltarget, pclMap);
			}
		}

		if((DWORD)TABS(pclClient->CurrentClock - dwPoisonStartClock) > dwPoisonLastClock)
		{
			SI32 siChangeType = 0;
			// 중독 상태 해독.
			if( clInnerStatus.IsStatus( INNERSTATUS_POISON ) )
			{
				clInnerStatus.DelStatus(INNERSTATUS_POISON);
				siChangeType = CHANGETYPE_POISON;
			}
			else if( clInnerStatus.IsStatus( INNERSTATUS_POISON_SETITEM_EFFECT ) )
			{
				clInnerStatus.DelStatus(INNERSTATUS_POISON_SETITEM_EFFECT);
				siChangeType = CHANGETYPE_POISON_SETITEM_EFFECT;
			}

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo( siChangeType, false );
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	// 얼음공격으로 얼려있을때 해제가된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwIceStartClock) > dwIceLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_ICE);

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_ICE, false);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}

		// PCK : SOULGUARD_ABILITY_NOICE가 있을 경우 추가 (09.07.08)
		if(pclClient->IsCountrySwitch(Switch_SoulGuard))
		{
			SI32 siNoIce = SoulGuardAbilityActivity( SOULGUARD_ABILITY_NOICE );
			if( 0 < siNoIce)
			{
				clInnerStatus.DelStatus(INNERSTATUS_ICE);

				// 이웃에게 통보 
				cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_ICE, false);
				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}	
		}
	}

	// 보스 얼음공격에 당했다가 해제된다면
	if(clInnerStatus.IsStatus(INNERSTATUS_FROZEN))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwFrozenStartClock) > dwFrozenLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_FROZEN);

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FROZEN, false);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}

		// PCK : SOULGUARD_ABILITY_NOICE가 있을 경우 추가 (09.07.08)
		if(pclClient->IsCountrySwitch(Switch_SoulGuard))
		{
			SI32 siNoIce = SoulGuardAbilityActivity( SOULGUARD_ABILITY_NOICE );
			if( 0 < siNoIce)
			{
				clInnerStatus.DelStatus(INNERSTATUS_FROZEN);

				// 이웃에게 통보 
				cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FROZEN, false);
				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}
		}
	}
	// 스턴에 걸려 해지 된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_STUN))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwStunStartClock) > dwStunLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_STUN);

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_STUN, false);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}

		// PCK : SOULGUARD_ABILITY_NOICE가 있을 경우 추가 (09.07.08)
		if(pclClient->IsCountrySwitch(Switch_SoulGuard))
		{
			SI32 siNoIce = SoulGuardAbilityActivity( SOULGUARD_ABILITY_NOICE );
			if( 0 < siNoIce)
			{
				clInnerStatus.DelStatus(INNERSTATUS_STUN);

				// 이웃에게 통보 
				cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_STUN, false);
				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}
		}
	}

	// 공격력 저하로있을때 해제가된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEATTACK))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwCurseAttackStartClock) > dwCurseAttackLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_CURSEATTACK);
			siCurseAttackPower					= 0;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEATTACK, false, GetMana());
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}

	}

	// 크리티컬 저하로있을때 해제가된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSECRITICAL))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwCurseCriticalStartClock) > dwCurseCriticalLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_CURSECRITICAL);
			siCurseCriticalPower				= 0;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSECRITICAL, false, GetMana());
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	// 방어력 저하로있을때 해제가된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEDEFENSE))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwCurseDefenseStartClock) > dwCurseDefenseLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_CURSEDEFENSE);
			siCurseDefensePower				= 0;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEDEFENSE, false, GetMana());
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	// 이동속도 저하로있을때 해제가된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEMOVESPEED))
	{ 
		if((DWORD)TABS(pclClient->CurrentClock - dwCurseMovespeedStartClock) > dwCurseMovespeedLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_CURSEMOVESPEED);
			siCurseMovespeedPower				= 0;
			clPB.GivenMoveSpeed					= 0;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEMOVESPEED, false, GetMana(), 0);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	// 이동속도 증가 버프가 해제 된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED))
	{
		if((DWORD)TABS(pclClient->CurrentClock - dwIncreaseMovespeedStartClock) > dwIncreaseMovespeedLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_INCREASEMOVESPEED);
			siIncreaseMovespeedPower			= 0;
			clPB.GivenMoveSpeed					= 0;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_INCREASEMOVESPEED, false, 0);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);

			// 이동속도 증가 메세지 뿌려줌
			TCHAR* pTitle = GetTxtFromMgr(5614);
			TCHAR *pText = GetTxtFromMgr(6413);
			cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
			cltMsg clMsg2(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
			SendNetMsg((sPacketHeader*)&clMsg2);


		}
	}


	// 독이 중독되었을때 독이 해제가 된다면 
	if(clInnerStatus.IsStatus(INNERSTATUS_MAGICFIRE))
	{
		// 1초 마다 에너지를 감소시킨다.
		if(TABS(pclClient->CurrentClock - dwMagicFireCheckClock) > 2000)
		{
			dwMagicFireCheckClock = pclClient->CurrentClock;

			if(GetLife() > 0) 
			{
				cltAttackTarget cltarget(GetID(), &pclCI->clBI.clPos, 100,0);
				cltAttackDamageInfo cldamageinfo(ATTACKTYPE_MAGICFIRESTATUS, siMagicFirePower, 0);
				((cltServer*)pclClient)->HitOperation(siMagicFireCharUnique, &cldamageinfo, 1, &cltarget, pclMap);

			}
		}

		if((DWORD)TABS(pclClient->CurrentClock - dwMagicFireStartClock) > dwMagicFireLastClock)
		{
			clInnerStatus.DelStatus(INNERSTATUS_MAGICFIRE);

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_MAGICFIRE, false);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	// 순간적으로 설정되는 DRAIN은 유지할 필요가 없다.
	if(bDrainSwitch)
	{
		bDrainSwitch = false;
	}


	//---------------------------------
	// 찜처리 
	//---------------------------------
	if(clJim.siJimHostCharUnique)
	{
		bool bjimloseswitch = false;

		// 찜한 주체 캐릭터가 무효하면 찜은 풀린다. 
		SI32 hostid = pclCM->GetIDFromCharUnique(clJim.siJimHostCharUnique);
		if(pclCM->IsAlive(hostid) == false)
		{
			bjimloseswitch = true;
		}
		// 살아 있어도 서로 정보가 일치하지 않으면, 
		else if(pclCM->CR[hostid]->clJim.siJimSlaveCharUnique != GetCharUnique())
		{
			bjimloseswitch = true;
		}

		// 일정 시간 경과하면 찜은 풀린다. 
		if(TABS(pclClient->GetFrame() - clJim.dwJimFrame) > 140)
		{
			bjimloseswitch = true;
		}

		if(bjimloseswitch == true)
		{
			// 찜이 풀린다. 
			LoseJim();
		}
	}

	//---------------------------------
	// 지휘효과를 부여한다. 
	//----------------------------------
	// 10초에 한번씩 확인한다.
	//[진성] 영주가 살아있을때만 지휘효과 적용. => 2008-5-8
	if(TRUE == pclCM->IsAlive(GetID()) && TABS(pclClient->CurrentClock - dwGeneralEftSetClock) > 10000)
	{
		//[진성] 지휘효과는 해당 캐릭이 살아있을때만 가능하게 변경.
		dwGeneralEftSetClock = pclClient->CurrentClock;

		bool bacswitch		= false;
		SI32 acuprate		= 0;
		bool bdamageswitch	= false;
		SI32 damageuprate	= 0;
		bool balluserswitch = false;

		//[추가 : 황진성 2007. 11. 27 "gmmode" 4번 발동시에 운영자가 주변 캐릭에 군주와 같은 지휘효과를 줌.]
		if((pclCI->clBI.uiGRank == GRANK_KING || pclCI->clBI.uiGMMode == GMMODE_ATB_BUFF))
		{  
			balluserswitch	= true;
			bacswitch		= true;
			acuprate		= min(50, pclCI->clIP.GetLevel() * 35 / 100);
			bdamageswitch	= true;
			damageuprate	= min(50, pclCI->clIP.GetLevel() * 20 / 100);
		}
		else
		{
			if(pclCI->clCharRank.siType == RANKTYPE_CITYHALL)
			{
				bacswitch = true;
				acuprate  = min(50, pclCI->clIP.GetLevel() * 35 / 100);
			}
			else if(pclCI->clCharRank.siType)
			{
				bdamageswitch = true;
				damageuprate  = min(50, pclCI->clIP.GetLevel() * 20 / 100);
			}
		}

		if(bacswitch || bdamageswitch)
		{
			GeneralEft(bacswitch, acuprate, bdamageswitch, damageuprate , balluserswitch );
		}
	}

	//-------------------------------------
	// 선공 방어 행위. 
	//--------------------------------------
	if(bNoFirstAttackSwitch == true)
	{
		if(TABS(pclClient->CurrentClock - dwNoFirstAttackClock) > 60000)
		{
			bNoFirstAttackSwitch = false;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACK, bNoFirstAttackSwitch);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}
	//-------------------------------------
	// ICE 방어 행위. 
	//--------------------------------------
	if(bNoIceAttackSwitch == true)
	{
		if(TABS(pclClient->CurrentClock - dwNoIceAttackClock) > 30000)
		{
			bNoIceAttackSwitch = false;

			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOICEATTACK, bNoIceAttackSwitch);
			cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}
}

// 캐릭터를 얼린다. 
BOOL cltCharServer::SetIce(SI32 damage, DWORD _dwAddClock)
{
	DWORD lastclock  = 2000 + min(10000, damage*100) + _dwAddClock;
	DWORD startclock = pclClient->CurrentClock;

	// ICE가 계속해서 타격을 입힐때 남아있는 사간보다 작은 지연이 오면 
	// 기존의 지연시간을 유지시킨다.
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE))
	{
		DWORD leftclock = pclClient->CurrentClock - dwIceStartClock;
		if(leftclock>lastclock)
		{
			lastclock  = dwIceLastClock;
			startclock = dwIceStartClock;
		}
	}
	clInnerStatus.SetStatus(INNERSTATUS_ICE);
	dwIceLastClock	= lastclock;
	dwIceStartClock	= startclock;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_ICE, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	// 강제로 멈춤 
	OrderForceStop(GetID(), BY_PLAYER);

	return TRUE;

}

// 보스 얼음으로 얼린다.
BOOL cltCharServer::SetFrozen(SI32 damage)
{
	DWORD lastclock  = 2000 + min(10000, damage*100);
	DWORD startclock = pclClient->CurrentClock;

	// ICE가 계속해서 타격을 입힐때 남아있는 사간보다 작은 지연이 오면 
	// 기존의 지연시간을 유지시킨다.
	if(clInnerStatus.IsStatus(INNERSTATUS_FROZEN))
	{
		DWORD leftclock = pclClient->CurrentClock - dwFrozenStartClock;
		if(leftclock>lastclock)
		{
			lastclock  = dwFrozenLastClock;
			startclock = dwFrozenStartClock;
		}
	}
	clInnerStatus.SetStatus(INNERSTATUS_FROZEN);
	dwFrozenLastClock	= lastclock;
	dwFrozenStartClock	= startclock;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FROZEN, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	// 강제로 멈춤 
	OrderForceStop(GetID(), BY_PLAYER);

	return TRUE;

}
// 스턴 효과를 준다
BOOL cltCharServer::SetStun(SI32 value)
{

	DWORD lastclock  =  value*1000;
	DWORD startclock = pclClient->CurrentClock;

	// ICE가 계속해서 타격을 입힐때 남아있는 사간보다 작은 지연이 오면 
	// 기존의 지연시간을 유지시킨다.
	if(clInnerStatus.IsStatus(INNERSTATUS_STUN))
	{
		DWORD leftclock = pclClient->CurrentClock - dwStunLastClock;
		if(leftclock>lastclock)
		{
			lastclock  = dwStunLastClock;
			startclock = dwStunStartClock;
		}
	}
	clInnerStatus.SetStatus(INNERSTATUS_STUN);
	dwStunLastClock	= lastclock;
	dwStunStartClock	= startclock;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_STUN, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	// 강제로 멈춤 
	OrderForceStop(GetID(), BY_PLAYER);

	return TRUE;
}
// 소울가드 - 얼린다
BOOL cltCharServer::SetSoulGuardIce(SI32 value)
{

	DWORD	lastclock  =  value*1000;
	DWORD	startclock = pclClient->CurrentClock;

	// ICE가 계속해서 타격을 입힐때 남아있는 사간보다 작은 지연이 오면 
	// 기존의 지연시간을 유지시킨다.
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE))
	{
		DWORD leftclock = pclClient->CurrentClock - dwStunLastClock;
		if(leftclock>lastclock)
		{
			lastclock  = dwIceLastClock;
			startclock = dwIceStartClock;
		}
	}
	clInnerStatus.SetStatus(INNERSTATUS_ICE);
	dwIceLastClock	= lastclock;
	dwIceStartClock	= startclock;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(INNERSTATUS_ICE, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	// 강제로 멈춤 
	OrderForceStop(GetID(), BY_PLAYER);

	return TRUE;
}

// 불에 태운다.
BOOL cltCharServer::SetMagicFire(SI32 enemy, SI32 damage)
{
	// 불에 의한 공격은 3분지 1만 들어간다.
	damage /= 10;

	clInnerStatus.SetStatus(INNERSTATUS_MAGICFIRE);
	siMagicFireCharUnique	= enemy;			// 나를 태운 캐릭터
	dwMagicFireLastClock	= 20000;			// 불의 지연시간. 
	dwMagicFireStartClock	= pclClient->CurrentClock;		// 불 시작시간. 
	siMagicFirePower		= damage;			// 불의 강도. 
	dwMagicFireCheckClock  = pclClient->CurrentClock;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_MAGICFIRE, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

// 중독을 시킨다. 
BOOL cltCharServer::SetPoison(SI32 poisoner, SI32 damage, DWORD _dwClock )
{
	// POISON에의한 데미지는 damage의 반만 간다.
	damage /= 2;

	clInnerStatus.SetStatus(INNERSTATUS_POISON);
	siPoisonCharUnique	= poisoner;						// 나를 중독시킨 캐릭터 유니크. 
	dwPoisonLastClock	= _dwClock;						// 중독의 지연시간. 
	dwPoisonStartClock	= pclClient->CurrentClock;		// 중독 시작시간. 
	siPoisonPower		= damage;						// 중독의 강도. 
	dwPoisonCheckClock  = pclClient->CurrentClock;		// 현재 시각

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_POISON, true);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

//세트 아이템의 효과로 중독을 시킨다. 
BOOL cltCharServer::SetPoisonSetItemEffect(SI32 poisoner, SI32 damage, DWORD _dwClock )
{
	// POISON에의한 데미지는 damage의 반만 간다.
	damage /= 2;

	clInnerStatus.SetStatus( INNERSTATUS_POISON_SETITEM_EFFECT );
	siPoisonCharUnique	= poisoner;						// 나를 중독시킨 캐릭터 유니크. 
	dwPoisonLastClock	= _dwClock;						// 중독의 지연시간. 
	dwPoisonStartClock	= pclClient->CurrentClock;		// 중독 시작시간. 
	siPoisonPower		= damage;						// 중독의 강도. 
	dwPoisonCheckClock  = pclClient->CurrentClock;		// 현재 시각

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo( CHANGETYPE_POISON_SETITEM_EFFECT, true );
	cltGameMsgResponse_StatusInfo clChangeInfo( GetCharUnique(), &StatusInfo );
	cltMsg clMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo );
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::SetDrain(SI32 damage, SI32 passivedamage, SI32 passivemana)
{
	//======================================
	// 최대 30% 를 넘지 않도록 한다.
	//======================================
	if(passivedamage>30) passivedamage = 30;

	SI32 IncLife = min(damage * passivedamage /100 ,  clPB.GetMaxLife() - GetLife());
	SI32 DecMana = passivemana;
	// mana가 조금이라도 남아 있다면 원하는 mana 보다 작더라도 그 비례대로 에너지를 채워준다.
	if(passivemana && GetMana() &&  GetMana()< passivemana)
	{
		IncLife  = (IncLife * GetMana())/DecMana;
		DecMana  = GetMana();
	}

	// 에너지를 채우게 되면 에너지을 채우고 마나를 깍는다.
	if(IncLife>0 && GetMana() >= DecMana)
	{
		bDrainSwitch = true;		// 별의미는 없지 
		IncreaseLife(IncLife);
		DecreaseMana(DecMana);

		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_DRAIN, true, GetLife(), GetMana(), IncLife);
		cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		SendNeighbourMsg(&clMsg, true);
		return TRUE;
	}

	return FALSE;
}


BOOL cltCharServer::SetCurseAttack(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid)
{
	if( pclCM->IsValidID(enemyid) == FALSE)		return FALSE;
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];

	if(pclenemychar->clInnerStatus.IsStatus(INNERSTATUS_CURSEATTACK) == true) return FALSE;

	SI32 DecMana = passivemana;
	// mana가 조금이라도 남아 있다면 원하는 mana 보다 작더라도 그 비례대로
	if(passivemana && GetMana() &&  GetMana()< passivemana)
	{
		passivedamage	= (passivedamage * GetMana())/DecMana;
		DecMana			= GetMana();
	}

	// 마나를 깍는다.
	if(passivedamage> 0 && GetMana() >= DecMana)
	{
		// 최대 30% 를 넘지 않도록 한다.
		if(passivedamage>30)	passivedamage = 30;

		pclenemychar->clInnerStatus.SetStatus(INNERSTATUS_CURSEATTACK);
		pclenemychar->dwCurseAttackLastClock	= 5000+min(15000, damage*30);	// 공격력 감소의 지연시간. 
		pclenemychar->dwCurseAttackStartClock	= pclClient->CurrentClock;		// 공격력 감소   시작시간. 
		pclenemychar->siCurseAttackPower		= passivedamage;				// 공격력 감소의 강도. 

		DecreaseMana(DecMana);


		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEATTACK, true, GetMana());
		cltGameMsgResponse_StatusInfo clChangeInfo(pclenemychar->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		pclenemychar->SendNeighbourMsg(&clMsg, true);
		return TRUE;
	}
	return FALSE;
}


BOOL cltCharServer::SetCurseCritical(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid)
{
	if( pclCM->IsValidID(enemyid) == FALSE)		return FALSE;
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];

	if(pclenemychar->clInnerStatus.IsStatus(INNERSTATUS_CURSECRITICAL) == true) return FALSE;

	SI32 DecMana = passivemana;
	// mana가 조금이라도 남아 있다면 원하는 mana 보다 작더라도 그 비례대로
	if(passivemana && GetMana() &&  GetMana()< passivemana)
	{
		passivedamage	= (passivedamage * GetMana())/DecMana;
		DecMana			= GetMana();
	}

	// 마나를 깍는다.
	if(passivedamage> 0 && GetMana() >= DecMana)
	{
		// 최대 80% 를 넘지 않도록 한다.
		if(passivedamage>80)	passivedamage = 80;

		pclenemychar->clInnerStatus.SetStatus(INNERSTATUS_CURSECRITICAL);
		pclenemychar->dwCurseCriticalLastClock	= 5000+min(15000, damage*30);	// 크리티컬 감소의 지연시간. 
		pclenemychar->dwCurseCriticalStartClock	= pclClient->CurrentClock;		// 크리티컬 감소   시작시간. 
		pclenemychar->siCurseCriticalPower		= passivedamage;				// 크리티컬 감소의 강도. 

		DecreaseMana(DecMana);

		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSECRITICAL, true, GetMana());
		cltGameMsgResponse_StatusInfo clChangeInfo(pclenemychar->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		pclenemychar->SendNeighbourMsg(&clMsg, true);
		return TRUE;
	}

	return FALSE;

}


BOOL cltCharServer::SetCurseDefense(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid)
{
	if( pclCM->IsValidID(enemyid) == FALSE)		return FALSE;
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];

	if(pclenemychar->clInnerStatus.IsStatus(INNERSTATUS_CURSEDEFENSE) == true) return FALSE;

	SI32 DecMana = passivemana;
	// mana가 조금이라도 남아 있다면 원하는 mana 보다 작더라도 그 비례대로
	if(passivemana && GetMana() &&  GetMana()< passivemana)
	{
		passivedamage	= (passivedamage * GetMana())/DecMana;
		DecMana			= GetMana();
	}

	// 마나를 깍는다.
	if(passivedamage> 0 && GetMana() >= DecMana)
	{
		// 최대 30% 를 넘지 않도록 한다.
		if(passivedamage>30)	passivedamage = 30;

		pclenemychar->clInnerStatus.SetStatus(INNERSTATUS_CURSEDEFENSE);
		pclenemychar->dwCurseDefenseLastClock	= 5000+min(15000, damage*30);	// 공격력 감소의 지연시간. 
		pclenemychar->dwCurseDefenseStartClock	= pclClient->CurrentClock;		// 공격력 감소   시작시간. 
		pclenemychar->siCurseDefensePower		= passivedamage;				// 공격력 감소의 강도. 

		DecreaseMana(DecMana);

		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEDEFENSE, true, GetMana());
		cltGameMsgResponse_StatusInfo clChangeInfo(pclenemychar->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		pclenemychar->SendNeighbourMsg(&clMsg, true);
		return TRUE;
	}
	return FALSE;
}


BOOL cltCharServer::SetCurseMovespeed(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid)
{
	if( pclCM->IsValidID(enemyid) == FALSE)		return FALSE;
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];

	if(pclenemychar->clInnerStatus.IsStatus(INNERSTATUS_CURSEMOVESPEED) == true) return FALSE;

	SI32 DecMana = passivemana;
	// mana가 조금이라도 남아 있다면 원하는 mana 보다 작더라도 그 비례대로
	if(passivemana && GetMana() &&  GetMana()< passivemana)
	{
		passivedamage	= (passivedamage * GetMana())/DecMana;
		DecMana			= GetMana();
	}

	// 마나를 깍는다.
	if(passivedamage> 0 && GetMana() >= DecMana)
	{
		// 최대 50% 를 넘지 않도록 한다.
		if(passivedamage>50)	passivedamage = 50;

		pclenemychar->clInnerStatus.SetStatus(INNERSTATUS_CURSEMOVESPEED);
		pclenemychar->dwCurseMovespeedLastClock	= 5000+min(15000, damage*30);	// 이동속도 감소 지연시간. 
		pclenemychar->dwCurseMovespeedStartClock= pclClient->CurrentClock;		// 이동속도 감소   시작시간. 
		pclenemychar->siCurseMovespeedPower		= passivedamage;				// 이동속도 감소의 강도. 

		DecreaseMana(DecMana);

		SI32 siCurrentSpeed = pclenemychar->clPB.TotalMoveSpeed;
		pclenemychar->clPB.GivenMoveSpeed = max(0, siCurrentSpeed - siCurrentSpeed * passivedamage / 100);
		pclenemychar->clPB.TotalMoveSpeed = pclenemychar->clPB.GivenMoveSpeed;

		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEMOVESPEED, true, GetMana(), pclenemychar->clPB.GivenMoveSpeed);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclenemychar->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		pclenemychar->SendNeighbourMsg(&clMsg, true);
		return TRUE;
	}
	return FALSE;
}

BOOL cltCharServer::DeletePoison()				// 중독 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_POISON);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_POISON, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeletePoisonSetItemEffect()				// 중독 상태를 삭제한다.
{
	clInnerStatus.DelStatus( INNERSTATUS_POISON_SETITEM_EFFECT) ;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo( CHANGETYPE_POISON_SETITEM_EFFECT, false );
	cltGameMsgResponse_StatusInfo clChangeInfo( GetCharUnique(), &StatusInfo );
	cltMsg clMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, PACKET(clChangeInfo) );
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteIce()					// 얼음 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_ICE);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_ICE, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteCurseAttack()			// 공격력이 저하 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_CURSEATTACK);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEATTACK, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteCurseCritical()		// Critical 확률이 낮아지는 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_CURSECRITICAL);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSECRITICAL, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteCurseDefense()		// 방어력이 낮아지는 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_CURSEDEFENSE);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEDEFENSE, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteCurseMovespeed()		// 이동속도 저하 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_CURSEMOVESPEED);

	clPB.GivenMoveSpeed					= 0;

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_CURSEMOVESPEED, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteMagicFire()			// 불에 타는 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_MAGICFIRE);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_MAGICFIRE, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

BOOL cltCharServer::DeleteFrozen()				// 보스 얼음 상태를 삭제한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_FROZEN);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FROZEN, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}
BOOL cltCharServer::DeleteStun()				// 스턴 상태를 해지 한다.
{
	clInnerStatus.DelStatus(INNERSTATUS_STUN);

	// 이웃에게 통보 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_STUN, false);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNeighbourMsg(&clMsg, true);

	return TRUE;
}

//[진성] 디버프 마법 삭제.
BOOL cltCharServer::DeleteCurseEffect()				
{
	m_clCharCurseEffect.Clear();
	m_clCharCurseEffect.SendMsgCurseInfo( GetID() );
	
	return TRUE;
}


//캐릭터가 공격 받았을 때 처리해야할 일들. 
void cltCharServer::BeHitOperate(SI32 attackid)
{
	if(pclCM->IsValidID(attackid) == false)			return;

	cltServer* pclserver			= (cltServer*)pclClient;
	cltCharServer* pclattackchar	= (cltCharServer*)pclCM->CR[attackid];

	//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 타입.
	// 캐릭터가 공격 받았을때, 결정체의 내구도를 감소 시켜준다. 
	if ( IDENTITY_PERSON_SUMMON == clIdentity.siIdentity )
	{
		DecreaseCrystalDurDEForSummon(CRYSTAL_DECREASE_DURABILITY_ACNUM);
	}
	else
	{
		DecreaseCrystalDurDE(CRYSTAL_DECREASE_DURABILITY_ACNUM);
	}

	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		if( pclCM->IsAlive(GetID()) )
		{
			cltCharServer* pclenemychar = pclCM->GetCharServer( attackid );

			bool bDecreaseDur = false;		// 내구도를 차감 시켜야 하는가?

			// 상대방 캐릭터가 몬스터인 경우에만 내구도가 차감된다.
			if( pclenemychar &&
				IsNPC(pclenemychar->GetCharUnique()) &&
				pclenemychar->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )
			{
				bDecreaseDur = true;
			}

			if( bDecreaseDur )
			{
				DecreaseArmourDur( attackid );
			}
		}
		else
		{
			DecreaseEquipDurFromDead( );
		}
	}

	//-----------------------------------------
	// 성황신이나 성문이면 마을이 공격받고 있음을 설정한다. 
	//-----------------------------------------
	switch(clIdentity.siIdentity)			// 성황신
	{
	case IDENTITY_CASTLE:
	case IDENTITY_VILLAGEGOD:
		{
			SI32 villageunique = pclCI->clBI.siHomeVillage;
			if( villageunique >= 0 && villageunique < MAX_VILLAGE_NUMBER &&
				pclserver->pclVillageManager->pclVillageInfo[villageunique] )
			{
				pclserver->pclVillageManager->pclVillageInfo[villageunique]->bAttackedVillage = true;

				//--------------------------------------------------
				//10 번중에 3번만 몬스터를 생성시킨다.
				//--------------------------------------------------
				if(rand()%10 <3)
				{
					SI32 villagecharunique = 0;
					if(pclserver->pclVillageManager->IsThereVillageGod(villageunique, &villagecharunique) == TRUE) 
					{
						SI32 siMapIndex   = pclCM->CR[attackid]->GetMapIndex();
						SI32 siSummonKind = pclCM->CR[villagecharunique]->GetKind();
						SI32 siSummonX    = pclCM->CR[attackid]->GetX();
						SI32 siSummonY    = pclCM->CR[attackid]->GetY(); 

						if(siSummonKind > 0)
						{
							cltOrderDataInfo Order;
							pclClient->pclOrderManager->MakeOrder_ATTACK(&Order, attackid, BY_PLAYER);

							cltIdentity clIdentity;
							clIdentity.MakeGod(IDENTITY_VILLAGEGOD_SUMMON, 15);

							cltInnerStatusInfo clinnerstatus;
							clinnerstatus.clEnemyType.Set(ENEMYTYPE_VILLAGE, 0);

							SI32 siSummonChar = pclserver->SetNPCChar(siSummonKind, villageunique, &clIdentity, 1, 0, siSummonX, siSummonY, siMapIndex, NPCITEMMODE_NONE, &clinnerstatus, &Order);

							if(pclCM->IsValidID(siSummonChar))
							{
								pclCM->CR[ siSummonChar ]->ParametaBoxAction();

								// MAXLIFE, MANA를 계산하여 체력과 마법력을 설정해준다. 
								pclCM->CR[ siSummonChar ]->SetLife(pclCM->CR[ siSummonChar ]->clPB.GetMaxLife());
								pclCM->CR[ siSummonChar ]->SetMana(pclCM->CR[ siSummonChar ]->clPB.GetMaxMana());

								// 소환수의 생명시간을 위해 현재의 시간을 설정한다.
								((cltCharServer*)(pclCM->CR[ siSummonChar ]))->dwTimerClock = pclserver->CurrentClock;
							}
						}
					}
				}
			}
		}
		break;
	case IDENTITY_VILLAGEHUNT: // 키메라라면
		{
			pclserver->pclEventHunting->AddContributor(attackid);
		}
		break;
	default:	break;
	}


	if(pclCM->IsAlive(GetID()))
	{
		// 보스 아이템이 설정된 몬스터라면, 
		if(pclKI->clBossItemInfo.siItemIndex)
		{
			// 임의의 아이템을 찾는다. 

			SI32 itemunique, itemnum;
			if(pclKI->clBossItemInfo.GetRandItem(&itemunique, &itemnum) == true)
			{
				if(itemunique)
				{
					pclClient->pclItemManager->AddWarItemNum(itemunique, itemnum);

					// 공격자가 선박이라면 선장의 아이디를 대신 사용한다. 
					SI32 killerid = attackid;

					if(pclCM->IsValidID(killerid))
					{
						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[killerid];

						//cyj pclchar->GiveItem(itemunique, itemnum, INPUTITEMPERSON_OPTION_WAR,0);
						SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
						if(ref > 0)  //[영진]FindItemRefFromUnique 예외처리
						{
							if(pclClient->pclItemManager->pclItemInfo[ref] != NULL)
							{
								UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
								pclchar->GiveItem(itemunique, itemnum, INPUTITEMPERSON_OPTION_WAR, usedate);
							}
						}
					}
				}
			}
		}

		// 용왕인 경우, 
		if(GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_DRAGONKING")) )
		{
			if(rand() % 1 == 0)
			{
				cltOrderDataInfo Order;
				pclClient->pclOrderManager->MakeOrder_ATTACK(&Order, attackid, BY_PLAYER);

				SI32 siMapIndex   = GetMapIndex();
				SI32 siSummonX    = GetX();
				SI32 siSummonY    = GetY(); 

				SI32 quardid = pclserver->MakeGuardChar(pclClient->GetUniqueFromHash(TEXT("KIND_BOMBDRAGON")), pclCI->clBI.siHomeVillage, siMapIndex, siSummonX, siSummonY, &Order, &clInnerStatus.clEnemyType);
				if(pclCM->IsValidID(quardid))
				{
					// 소환수의 생명시간을 위해 현재의 시간을 설정한다.
					((cltCharServer*)(pclCM->CR[ quardid ]))->dwTimerClock = pclClient->CurrentClock;
				}
			}
		}


		SI16 questid = 0;
		if( IsPC(pclattackchar->GetCharUnique()) )
		{
			questid = attackid;
		}

		if( pclCM->IsValidID(questid) )
		{
			SI32 enemykind = GetKind();
			SI32 killednum = 1;

			// 몬스터를 때리는 퀘스트가 진행중이었나 ?
			((cltCharServer*)pclCM->CR[questid])->IncQuestPara(QUEST_CLEAR_COND_HITMON, enemykind, killednum);
		}
	}
	else
	{
		//-------------------------------------------------------
		// Daily 퀘스트 수행중이었다면 관련 조치를 취한다. (CLONE 캐릭터는 COUNT를 세지 않는다.)
		//-------------------------------------------------------
		SI16 questid = 0;
		if ( clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false && pclCM->IsAlive( attackid ) == TRUE )
		{
			SI32 enemykind = GetKind();

			if( IsPC(pclattackchar->GetCharUnique()) )
			{
				questid = attackid;
			}

			// 소환수 이면, 부모를 퀘스트 대상자로 본다. 
			if(IsNPC(pclattackchar->GetCharUnique()) && pclattackchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				questid = pclattackchar->GetSummonParentID();
			}

			if ( pclCM->IsValidID( questid ) )
			{
				cltCharServer* pclquestchar = (cltCharServer*)pclCM->CR[questid];

				if( pclquestchar && pclquestchar->pclCI->clDailyQuestInfo.siMonsterKind == enemykind )
				{
					if ( 0 < pclquestchar->siQuestCount )	// 운영자 명령어 카운트 적용
					{
						pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum += pclquestchar->siQuestCount;
					}
					else										// 일반 모드 
					{
						++pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum;
					}

					if ( pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum > 30000 )
					{
						pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum = 30000;
					}

					if ( pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum >= pclquestchar->pclCI->clDailyQuestInfo.siMonsterNum )
					{
						SI32 value = 100;

						cltItem clItem;
						clItem.siUnique = pclquestchar->pclCI->clDailyQuestInfo.siRewardItemUnique;
						clItem.siItemNum = ( pclquestchar->pclCI->clDailyQuestInfo.siRewardItemNum * value ) / 100;

						cltItem clToItem;
						clToItem.Init();

						SI16 InvPos = -1;
						SI32 rtnvalue;

						GMONEY money = ( pclquestchar->pclCI->clDailyQuestInfo.siRewardMoney * value ) / 100;
						BOOL selectedmoney = pclquestchar->pclCI->clDailyQuestInfo.bMoneySelected;

						if ( pclquestchar->pclCI->clDailyQuestInfo.bMoneySelected )
						{
							sDBRequest_DailyQuestDel clMsg( pclquestchar->pclCI->GetPersonID(), questid, true, InvPos, &clItem, 1, money, selectedmoney, pclquestchar->pclCI->clDailyQuestInfo.siRewardExp );
							pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

							pclserver->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_DAILYQUEST, money);
						}
						else
						{
							if ( pclquestchar->CanAddInv(INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
							{
								sDBRequest_DailyQuestDel clMsg( pclquestchar->pclCI->GetPersonID(), questid, true, InvPos, &clItem, 1, money, selectedmoney, pclquestchar->pclCI->clDailyQuestInfo.siRewardExp );
								pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
							}
							else
							{
								// 인벤 꽉 차서 안되므로...
								pclserver->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  1, 0, pclquestchar->GetCharUnique());

								// 유저에게 현재 상태 전송
								cltGameMsgResponse_DailyQuestChange clinfo( pclquestchar->pclCI->clDailyQuestInfo.siLeftTime, pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum );
								cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTCHANGE, sizeof(clinfo), (BYTE*)&clinfo);
								pclquestchar->SendNetMsg((sPacketHeader*)&clMsg);					
							}
						}
					}
					else
					{
						// DB 로 업데이트 하지는 않고, 유저에게 바로 알려줌.
						cltGameMsgResponse_DailyQuestChange clinfo( pclquestchar->pclCI->clDailyQuestInfo.siLeftTime, pclquestchar->pclCI->clDailyQuestInfo.siKillMonsterNum );
						cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTCHANGE, sizeof(clinfo), (BYTE*)&clinfo);
						pclquestchar->SendNetMsg((sPacketHeader*)&clMsg);					
					}
				}
			}
		}

		//-------------------------------------------------------
		// Daily2 퀘스트 수행중이었다면 관련 조치를 취한다. (CLONE 캐릭터는 COUNT를 세지 않는다.)
		//-------------------------------------------------------
		if ( clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false && pclCM->IsAlive( attackid ) == TRUE )
		{
			SI32 enemykind = GetKind();

			if( IsPC(pclattackchar->GetCharUnique()) )
			{
				questid = attackid;
			}

			// 소환수 이면, 부모를 퀘스트 대상자로 본다. 
			if(IsNPC(pclattackchar->GetCharUnique()) && pclattackchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				questid = pclattackchar->GetSummonParentID();
			}

			if ( pclCM->IsValidID( questid ) )
			{
				cltCharServer* pclquestchar = (cltCharServer*)pclCM->CR[questid];

				if( pclquestchar && pclquestchar->pclCI->clDailyQuest2Info.siMonsterKind == enemykind )
				{
					if ( 0 < pclquestchar->siQuestCount )	// 운영자 명령어 카운트 적용
					{
						pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum += pclquestchar->siQuestCount;
					}
					else										// 일반 모드 
					{
						++pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum;
					}

					if ( pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum > 30000 )
					{
						pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum = 30000;
					}

					if ( pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum >= pclquestchar->pclCI->clDailyQuest2Info.siMonsterNum )
					{
						SI32 value = 100;

						cltItem clItem;
						clItem.siUnique = pclquestchar->pclCI->clDailyQuest2Info.siRewardItemUnique;
						clItem.siItemNum = ( pclquestchar->pclCI->clDailyQuest2Info.siRewardItemNum * value ) / 100;

						cltItem clToItem;
						clToItem.Init();

						SI16 InvPos = -1;
						SI32 rtnvalue;

						GMONEY money = ( pclquestchar->pclCI->clDailyQuest2Info.siRewardMoney * value ) / 100;
						BOOL selectedmoney = pclquestchar->pclCI->clDailyQuest2Info.bMoneySelected;

						if ( pclquestchar->pclCI->clDailyQuest2Info.bMoneySelected )
						{

							sDBRequest_DailyQuest2Del clMsg( pclquestchar->pclCI->GetPersonID(), questid, true, InvPos, &clItem, 1, money, selectedmoney, pclquestchar->pclCI->clDailyQuest2Info.bHiddenQuest );
							pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}
						else
						{
							if ( pclquestchar->CanAddInv(INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
							{
								sDBRequest_DailyQuest2Del clMsg( pclquestchar->pclCI->GetPersonID(), questid, true, InvPos, &clItem, 1, money, selectedmoney, pclquestchar->pclCI->clDailyQuest2Info.bHiddenQuest );
								pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
							}
							else
							{
								// 인벤 꽉 차서 안되므로...
								pclserver->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  1, 0, pclquestchar->GetCharUnique());

								// 정보 업데이트
								cltGameMsgResponse_DailyQuest2Change clinfo( pclquestchar->pclCI->clDailyQuest2Info.siLeftTime, pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.bHiddenQuest );
								cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST2CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
								pclquestchar->SendNetMsg((sPacketHeader*)&clMsg);					
							}
						}
					}
					else
					{
						// DB 로 업데이트 하지는 않고, 유저에게 바로 알려줌.
						cltGameMsgResponse_DailyQuest2Change clinfo( pclquestchar->pclCI->clDailyQuest2Info.siLeftTime, pclquestchar->pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.bHiddenQuest );
						cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST2CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
						pclquestchar->SendNetMsg((sPacketHeader*)&clMsg);					
					}

				}
			}
		}

		//-------------------------------------------------------
		// 몬스터 처치 퀘스트 수행중이었다면 관련 조치를 취한다. ( CLONE은 해당하지 않는다.)
		//-------------------------------------------------------
		if(clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false && pclCM->IsAlive(attackid) == TRUE)
		{
			if( IsPC(pclattackchar->GetCharUnique()) )
			{
				questid = attackid;
			}

			// 소환수 이면, 부모를 퀘스트 대상자로 본다. 
			if(IsNPC(pclattackchar->GetCharUnique()) && pclattackchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				questid = pclattackchar->GetSummonParentID();

				// 소환수가 몬스터를 처치하는 퀘스트가 진행중이었나 ?
				if(pclCM->IsValidID(questid))
				{
					((cltCharServer*)pclCM->CR[questid])->IncQuestPara(QUEST_CLEAR_COND_SUMMONBATTLE , GetKind(), 1);
				}
			}
		}

		if(questid)
		{
			SI32 enemykind		= GetKind();
			SI32 enemyMapIndex	= GetMapIndex();
			SI32 killednum		= 1;
			SI16 siTemp1		= 0, siTemp2 = 0, siTemp3 = 0, siTemp4 = 0;

			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[questid];
			if ( pclchar == NULL ) return;

			// 운영자 명령어 적용
			if( 0 < pclchar->siQuestCount )
			{
				killednum = pclchar->siQuestCount;
			}

			//KHY - 1113 - 크리스마스 이벤트 - 크리스마스 퀘스트는 특별하다.
			if( pclserver->pclEventTimeManager->InEventTime("ChristmasEvent", &pclserver->sTime) )
			{
				ChristamsEventQuest(&enemykind);
			}

			// 몬스터를 처치하는 퀘스트가 진행중이었나 ?
			pclchar->IncQuestPara(QUEST_CLEAR_COND_KILLMON, enemykind, killednum);

			// 특정 맵에 있는 몬스터를 처치해라
			if ( IsNPC(GetCharUnique()) ) 
			{
				pclchar->IncQuestPara(QUEST_CLEAR_COND_MAPKILLMON, enemyMapIndex, killednum);
			}
			
			// 흑의 군단중 아무나 para2만큼 죽여야하는 퀘스트라면
			if ( pclchar->pclCI->clQuestInfo.IsQuestGoing( QUEST_CLEAR_COND_KILLDARKSOLDIER, &siTemp1, &siTemp2, &siTemp3, &siTemp4 ) == true )
			{
				TCHAR tszBlackArmyName[][64] = {
					// 흑의군단 이벤트 몬스터
					"KIND_NEWRIFLE", "KIND_NEWCATAR", "KIND_NEWDAEGUM", "KIND_YELLOWSHABEL", "KIND_GREENSHABEL", "KIND_REDSHABEL", "KIND_BLUESHABEL"
						// 전쟁 안내원에서 발동하는 흑의 군단에 나오는 몬스터
						,"KIND_DAEGUM", "KIND_CATAR", "KIND_RIFLE", "KIND_BLACKBOSS"
				};
				SI32 siCount = sizeof(tszBlackArmyName)/sizeof(TCHAR)/64;


				for ( SI32 siIndex=0; siIndex<siCount; siIndex++ )
				{
					if ( enemykind == pclserver->GetUniqueFromHash(tszBlackArmyName[siIndex]) )
					{

						pclchar->IncQuestPara(QUEST_CLEAR_COND_KILLDARKSOLDIER, 1, killednum);
						break;
					}
				}
			}

			// [영훈] 여기는 파티를 맺었을때는 작동되지 않도록 막는다
			if ( pclchar->siPartyIndex <= 0 )
			{
				pclchar->IncQuestPara(QUEST_CLEAR_COND_TWOWAYKILLMON , enemykind, killednum);
				pclchar->IncQuestPara(QUEST_CLEAR_COND_TWOWAYKILLMONBONUS , enemykind, killednum);
			}

			// [영훈] 서버 이벤트 퀘스트
			if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest = (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();
				if ( pclSE_Quest )
				{
					SI32 siEnemyLevel = pclCI->clIP.GetLevel();

					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_HUNTKIND, enemykind, killednum );
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_HUNTLEVEL, siEnemyLevel, killednum );
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_HUNTBOSS, enemykind, killednum );
				}
			}

			// 파티퀘스트
			if(pclserver->IsCountrySwitch(Switch_PartyQuest_PartyMatching))
			{
				// 파티에 속한 플레이어만 파티퀘스트 정보를 갱신 합니다.
				if(pclchar->siPartyIndex > 0)
				{
					pclserver->m_pPartyQuestMgr->UpdatePartyQuest(pclchar->GetID() ,pclchar->siPartyIndex, PARTYQUEST_TYPE_HUNTING, enemykind, killednum);
				}
			}
		}
	}
}

SI32 cltCharServer::DecreaseLife(SI32 life)
{
	cltServer* pclserver = (cltServer*)pclClient;

	pclCI->clIP.DecreaseLife(max(0, life));

	if(GetLife() < 0 )
	{
		pclCI->clIP.SetLife(0);
	}

	// 사망시. 
	if(GetLife() <= 0)
	{
		//-------------------------------
		// 죽은 캐릭터의 정보를 저장한다. 
		//-------------------------------
		pclserver->pclKindInfoSet->IncreasePreferenceChar(GetKind(), (pclClient->GetFrame() - dwMakeFrame) * 50 );

		//-----------------------------
		// 사용자가 죽은 것이라면 DB에 기본 정보를 저장한다. 
		//-----------------------------
		if(IsPC(GetCharUnique()))
		{
			// 지도를 확인한다. 
			if(GetMapIndex() == 0)
			{
				pclCI->clBI.clLastMainMapPos.Set(GetX(), GetY());
			}

			SendDB_PosLifeMana();

			//----------------------------------
			// 초보자용 사냥터에서 사망했다면, 
			//----------------------------------
			if(GetMapIndex() == MAPINDEX_BEGINNER1 )
			{
				siKilledMode = KILLEDMODE_BEGINNERMAP;
				StringCchCopy(szKillMeCharName, MAX_PLAYER_NAME, TEXT(""));

			}

		}

	}

	return GetLife();

}

// 이웃에게 내 외양 정보를 통보한다. 
bool cltCharServer::SendNeighbourMyShapeStatus()
{
	SI32 horseunique	= 0;
	cltDate addstatus;
	addstatus.MakeFullDateFromDateVary(0);
	SI32 ticket = 0 ;

	cltDate PremiumpartsDate_Slot1;
	PremiumpartsDate_Slot1.MakeFullDateFromDateVary(0);
	SI32 siPremiumPartsUnique_Slot1 = 0 ;

	cltDate PremiumpartsDate_Slot2;
	PremiumpartsDate_Slot2.MakeFullDateFromDateVary(0);
	SI32 siPremiumPartsUnique_Slot2 = 0 ;

	cltDate PremiumpartsDate_Slot3;
	PremiumpartsDate_Slot3.MakeFullDateFromDateVary(0);
	SI32 siPremiumPartsUnique_Slot3 = 0 ;

	SI32 siPremiumPartsNum = 0 ;
	//SI32 horseindex		= pclCI->clHorseInfo.siCurrentHorseIndex;
	//if(horseindex	 >= 0)
	//KHY - 1001 - 기승동물 5마리 보유 수정.
	if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
		if(pclHorse != NULL)
		{
			horseunique = pclHorse->siHorseUnique;
			addstatus.Set(&pclHorse->clAddStatusDate);
			ticket = pclHorse->siStatusTicketNum ;
		}
	}
	cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
	{
		if(pclHorse != NULL)
		{
			//프리미엄 파츠 
			PremiumpartsDate_Slot1.Set(&pclHorse->clPremiumPartsDate_Slot1);
			siPremiumPartsUnique_Slot1 = pclHorse->siPremiumUnique_Slot1 ;
			PremiumpartsDate_Slot2.Set(&pclHorse->clPremiumPartsDate_Slot2);
			siPremiumPartsUnique_Slot2 = pclHorse->siPremiumUnique_Slot2 ;
			PremiumpartsDate_Slot3.Set(&pclHorse->clPremiumPartsDate_Slot3);
			siPremiumPartsUnique_Slot3 = pclHorse->siPremiumUnique_Slot3 ;

			siPremiumPartsNum = pclHorse->siPremiumPartsNum ;
		}
	}
	// 외부 장비. 
	cltShapeEquipInfo clequip;
	if(IsPC(GetCharUnique()))
	{
		GetShapeEquipInfo(&clequip);
	}

	cltGameMsgResponse_PersonAllShapeInfo clInfo(GetCharUnique(), &clequip, horseunique,&addstatus,ticket);

	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONALLSHAPEINFO, sizeof(clInfo), (BYTE*)&clInfo);
	SendNeighbourMsg(&clMsg, false);

	// 무기술의 달인 엠블렘변경
	if ( (PERSONITEM_WEAPON1 == ActiveWeapon) || (PERSONITEM_WEAPON2 == ActiveWeapon) )
	{
		SI32 siItemType		= pclCI->clCharItem.GetWeaponType( pclClient->pclItemManager, ActiveWeapon );
		SI32 siSkillUnique	= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		UI08 siGetEmblem	= 0;
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel	= pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );
			siGetEmblem	= pclClient->pclSkillManager->m_clMasterManager.GetEmblemIndex( siItemType, siSkillLevel );
		}

		if ( m_uiWeaponSkillMasterEmblem != siGetEmblem )
		{
			m_uiWeaponSkillMasterEmblem = siGetEmblem;

			cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_EMBLEM, false, siGetEmblem );
			cltGameMsgResponse_StatusInfo	clInfo( GetCharUnique(), &clChangeInfo );

			cltMsg clEmblenMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo);
			SendNeighbourMsg( &clEmblenMsg, true );
		}

	}

	return true;
}


bool cltCharServer::SendNeighbourMyMakeItemStatus()
{

	SI08 sitempMakeItemSwitch = siPersonalMakeItemType;

	cltGameMsgResponse_PersonMakeItemSwitch clInfo(GetCharUnique(), sitempMakeItemSwitch);

	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONMAKEITEMSWITCH, sizeof(clInfo), (BYTE*)&clInfo);
	SendNeighbourMsg(&clMsg, true);

	return true;
}

// 서버에서 캐릭터의 공간 이동 관리.
void cltCharServer::CharServerMoveByGate(SI32 x, SI32 y)
{			
	if(clInnerStatus.clEnemyType.IsType(ENEMYTYPE_VILLAGE) == false)return ;

	// 필드에 FieldObject가 존재하는지 확인한다.
	SI32 unique = pclMap->GetFieldObject_Unique(x, y);
	if(unique <= 0)return ;

	SI32 ref	= pclMap->pclFieldObjectManager->FindRefFromUniqueMinus(unique);
	if(ref < 0)return ;

	SI32 type	= pclMap->pclFieldObjectManager->pclInfo[ref]->dwType;

	if(type == FOTYPE_VILLAGE)
	{
		// 마을의 Unique정보를 얻어온다. 
		SI32 villageunique = pclMap->GetFieldObjectPara(x, y);

		if(villageunique > 0 && villageunique < MAX_VILLAGE_NUMBER)
		{
			//  출입하고자 하는 마을의 성문과 적대적인 관계인가 ?
			SI32 castleid = pclClient->pclVillageManager->pclVillageInfo[villageunique]->siCastleCharUnique;
			if(castleid && IsEnemy(castleid) == true)
			{
				// 클라이언트로 서버의 응답값을 보낸다. 
				((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_WAR_CANTENTERENEMYCASTLE,  0, 0, GetCharUnique());
			}
			// 감옥에 갖혀 있다면, 
			else if(clInnerStatus.IsStatus(INNERSTATUS_PRISON))
			{
			}
			else
			{

				// 출입 가능한 곳인지 확인한다. 
				//if(pclClient->pclMapManager->GetLevelLimit(villageunique) <= pclCI->clIP.GetLevel())
				if(pclClient->pclMapManager->IsEnterLevel(villageunique, pclCI->clIP.GetLevel()) == true)
				{
					SI32 mapindex	= pclClient->pclVillageManager->pclVillageInfo[villageunique]->siVillageUnique;

					SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[ mapindex ]->siMapUnique;
					SI32 centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
					SI32 centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

					cltWarpInfo clWarpInfo(1, mapindex, false, false, centerx, centery, x, y);
					SetWarpInfo(&clWarpInfo, 30);

					// 내상태에서 pvp를 뺀다 pvp-
					clInnerStatus.clEnemyType.siEnemyType = ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR;
				}
			}

		}
		else
		{
			MsgBox(TEXT("fdsj8jfd"), TEXT("fdsn83f:%d"), villageunique);
		}
	}
	else if(type == FOTYPE_GATE)
	{

		SI32 gateunique = pclMap->GetFieldObjectPara(x, y);
		if(gateunique <= 0)return ;

		cltGateManager* pclgatemanager = pclClient->pclMapManager->pclGateManager;
		cltInstanceMapGateManager* pclinstancemapgatemanager = pclClient->pclMapManager->pclInstanceMapGateManager;
		cltServer* pclserver = (cltServer*)pclClient;

		bool bwarpfailswitch = false;
		SI32 siSourceMapIndex = GetMapIndex();

		// 출입 가능한 곳인지 확인한다. 
		SI32 mapindex = 0;
		SI32 dx = 0;
		SI32 dy = 0;

		SI32 itemunique = 0;
		SI32 itemnum = 0;


		// 인던이면, 인던 전용 게이트에서 찾는다.
		if( pclClient->pclMapManager->IsInstanceMap( GetMapIndex() ) )
		{
			SI32 siParentMapIndex = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
			cltMapCommon* pclParentMap = pclClient->pclMapManager->GetMapPointer( siParentMapIndex );
			if( pclParentMap == NULL )							return;
			if( pclParentMap->m_siInstanceMapGateIndex < 0)		return;

			cltInstanceMapGate* pclGate = pclinstancemapgatemanager->GetGatebyUnique(gateunique, pclParentMap->m_siInstanceMapGateIndex);
			mapindex	= pclGate->DstMapIndex;
			dx			= pclGate->DstX;
			dy			= pclGate->DstY;

			siSourceMapIndex = pclGate->SrcMapIndex;

			// 정보가 없는 게이트면 처리하지 않는다.
			if( pclGate->siUnique <= 0 )						return;
			if( pclGate->FOUnique <= 0 )						return;
		}
		else
		{
			siSourceMapIndex = pclgatemanager->clGate[gateunique].SrcMapIndex;

			mapindex	= pclgatemanager->clGate[gateunique].DstMapIndex;
			dx			= pclgatemanager->clGate[gateunique].DstX;
			dy			= pclgatemanager->clGate[gateunique].DstY;

			itemunique = pclgatemanager->clGate[gateunique].ItemUnique;
			itemnum	= pclgatemanager->clGate[gateunique].ItemNum;
		}

		if(IsPC(GetCharUnique()))
		{
			// 사람이 이동할 수 있는 곳인가 ?
			if (pclClient->pclMapManager->IsLandMap(mapindex) == false)return ;
		}

		cltCharServer* pclchar = NULL;
		pclchar = this;

		// [영훈] 개인 상점을 연 상태에서 시장을 열 수 있는 지역에서 시장을 열 수 없는 지역으로 이동하는 것이라면 막는다
		if ( (pclClient->pclMapManager->IsCanMarketOpenMap( siSourceMapIndex ) == true)
			&& (pclClient->pclMapManager->IsCanMarketOpenMap( mapindex ) == false) )
		{
			if ( (true == pclchar->bPersonalShopSwitch) || (true == pclchar->bPremiumPersonalShop) )
			{
				((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_FAIL_WARPTO_NOTMARKETOPEN_MAP,  0, 0, GetCharUnique());
				return;
			}

		}

		// 중국만 일단 막는 부분이다 -KKM-
		if( true == pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
		{
			if( true == pclClient->pclMapManager->IsBlockWarp( mapindex ) )
			{
				//	pclserver->SendServerResponseMsg(0, SRVAL_FAIL_FORBID_ENTERMAP, 0, 0, pclchar->GetCharUnique());
				//	return;
			}
		}

		if(pclClient->pclMapManager->IsEnterLevel(mapindex, pclchar->pclCI->clIP.GetLevel()) == false
			&& mapindex != MAPINDEX_BATTLEROYAL_MABRIUM)
		{
			// 해당맵은 레벨 LvX~LvY까지만 들어갈 수 있습니다.
			pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_LEVEL_RANGE, 
				pclClient->pclMapManager->GetMinLevel(mapindex), 
				pclClient->pclMapManager->GetMaxLevel(mapindex),
				pclchar->GetCharUnique());
			return;
		}

		if(itemunique > 0 && itemnum > 0)
		{
			if(pclCI->clCharItem.GetItemNum(itemunique) < itemnum)
			{
				// 해당맵은 XX 아이템 X개가 있어야 들어갈 수 있습니다.
				pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_NOITEM, 
					itemunique, itemnum,
					pclchar->GetCharUnique());
				return;
			}
		}

		SI32 levellimit = pclClient->pclMapManager->GetLevelLimit(mapindex);
		if(levellimit <= pclchar->pclCI->clIP.GetLevel())
		{
			//[기형] 배틀로얄 지역이면
			if( mapindex == MAPINDEX_BATTLEROYAL_MABRIUM )
			{
			
				CBattleRoyalMgr* pclBattleRoyalMgr = ((cltServer*)pclClient)->m_pclBattleRoyalMgr;
				if( NULL != pclBattleRoyalMgr)
				{
					CBattleRoyal* pclBattleRoyal = pclBattleRoyalMgr->GetBattleRoyal(this);
					if(NULL != pclBattleRoyal)
					{
						mapindex = pclBattleRoyal->GetStadiumMapIndex();

						switch(pclBattleRoyal->CanEnter(pclchar))
						{
						case BATTLEROYAL_ENTERERROR_ISOPENED:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTOPEND,  0, 0, pclchar->GetCharUnique());
								break;
							}
						case BATTLEROYAL_ENTERERROR_WASJOINED:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTREJOIN,  0, 0, pclchar->GetCharUnique());
								break;
							}
						case BATTLERPYAL_ENTERERROR_ISMAKING:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTREADYFORMAKING,  0, 0, pclchar->GetCharUnique());
								break;
							}
						case BATTLERPYAL_ENTERERROR_TAKEDOUTSUMMON:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTREADYFORSUMMON,  0, 0, pclchar->GetCharUnique());
								break;
							}
						case BATTLERPYAL_ENTERERROR_FULLEDGAMER:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTREADYFORFULLEDGAMER,  0, 0, pclchar->GetCharUnique());
								break;
							}
						case BATTLERPYAL_ENTERERROR_JOINPARTY:
							{
								bwarpfailswitch = true;
								pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_JOINPARTY,  0, 0, pclchar->GetCharUnique());
								break;
							}
						default:
							{
								break;
							}
						}
					}
					else
					{
						bwarpfailswitch = true;
						pclserver->SendServerResponseMsg(0, SRVAL_BATTLEROYAL_NOTPROPERLEVEL,  0, 0, pclchar->GetCharUnique());
					}
				}
				
			}
			// 초보자지역이면, 
			SI32 minlevel = MAX_LEVEL_FOR_BEGINNERMAP;
			if((mapindex == MAPINDEX_BEGINNER1 )
				&& pclchar->pclCI->clIP.GetLevel() >= minlevel)
			{
				bwarpfailswitch = true;
				// 클라이언트로 서버의 응답값을 보낸다. 
				pclserver->SendServerResponseMsg(0, SRVAL_TOOHIGHLEVEL,  minlevel, 0, pclchar->GetCharUnique());
			}

			//cyj 흑의 군대 게이트일때
			if ( gateunique >= BLACKARMY_GATEUNIQUE_START && gateunique < BLACKARMY_GATEUNIQUE_START + MAX_BLACKARMY_MAP_CNT)
			{ 
				// 전쟁시간이 아니면 워프 안함
				if ( pclClient->pclBlackArmyManager->bWarSwitch == false)
				{
					bwarpfailswitch = true;

					pclserver->SendServerResponseMsg(0, SRVAL_BLACKARMY_NOTWAR,	0, 0, pclchar->GetCharUnique());
				}
				else 
				{
					if (siBlackArmyWarMapIndex >= 0 && siBlackArmyWarMapIndex < MAX_BLACKARMY_MAP_CNT)
					{
						// 전쟁맵에 배정받았으나 해당 맵이 아닌 맵으로 이동시에 워프 안함
						if (gateunique != pclClient->pclBlackArmyManager->clWarMap[siBlackArmyWarMapIndex].siGateUnique)
						{
							bwarpfailswitch = true;

							pclserver->SendServerResponseMsg(0, SRVAL_BLACKARMY_NOTALLOC,	0, 0, pclchar->GetCharUnique());

						}

						// 전쟁맵에 배정받았으나 해당맵이 전쟁이 끝난경우 워프 안함
						if (pclClient->pclBlackArmyManager->clWarMap[siBlackArmyWarMapIndex].bWarDoing == false)
						{
							bwarpfailswitch = true;

							pclserver->SendServerResponseMsg(0, SRVAL_BLACKARMY_NOTWAR,	0, 0, pclchar->GetCharUnique());

						}

					}
					// 전쟁맵에 배정받지 않았으면 워프 안함
					else
					{
						bwarpfailswitch = true;

						pclserver->SendServerResponseMsg(0, SRVAL_BLACKARMY_NOTALLOC,	0, 0, pclchar->GetCharUnique());
					}
				}
			}

			// 인던이 아닌곳에서 인던으로 입장하는 경우에는
			// 입장할 수 있는 인던을 찾는다.
			if( pclClient->pclMapManager->IsInstanceMap( siSourceMapIndex ) == false &&
				pclClient->pclMapManager->IsInstanceMap(mapindex) )
			{
				// 들어갈 수 있는 맵을 찾는다.
				SI32 siCanEnterMapIndex = pclClient->pclMapManager->GetEnterableInstanceMapIndex(mapindex, this);
				if(siCanEnterMapIndex > 0)
				{
					if( pclClient->pclMapManager->EnterInstanceMap(siCanEnterMapIndex, this) )
					{
						// 선택된 맵 인덱스로 교체한다.
						mapindex = siCanEnterMapIndex;
					}
					else
					{
						bwarpfailswitch = true;

						// 클라이언트로 서버의 응답값을 보낸다. 
						cltServer* pclserver = (cltServer*)pclClient;
						pclserver->SendServerResponseMsg(0, SRVAL_FAIL_INSTANTDUNGEON_NO_GUILD,  0, 0, pclchar->GetCharUnique());
						return;
					}
				}
				else
				{
					// 클라이언트로 서버의 응답값을 보낸다. 
					cltServer* pclserver = (cltServer*)pclClient;

					// [추가 : 황진성 2008. 1. 16 => 인던에 입장하려는 내가 길드가 없을때 던질 메시지]
					if(0 == pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex)
					{
						pclserver->SendServerResponseMsg(0, SRVAL_FAIL_INSTANTDUNGEON_MY_NO_GUILD,  0, 0, pclchar->GetCharUnique());
					}		
					else if( siCanEnterMapIndex == 0 )
					{
						pclserver->SendServerResponseMsg(0, SRVAL_FAIL_INSTANTDUNGEON_NO_GUILD,  0, 0, pclchar->GetCharUnique());
					}
					else
					{
						pclserver->SendServerResponseMsg(0, SRVAL_FAIL_INSTANTDUNGEON_OVER_COUNT_GUILD,  0, 0, pclchar->GetCharUnique());
					}
					// 들어갈 수 있는 인던이 없습니다.
					bwarpfailswitch = true;

					return;
				}
			}

			// 수렵장에서 마을로 가는 경우, 
			if (pclClient->pclMapManager->IsHuntMap( siSourceMapIndex ) == true)
			{
				// 마을의 지도 타입을 구한다. 
				SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[mapindex]->siMapUnique;
				if(maptypeunique)
				{
					dx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
					dy = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
				}

			}

			if(bwarpfailswitch == false)
			{
				if(itemunique > 0 && itemnum > 0)
				{
					// 아이템을 사용하여 통과하는 게이트인경우
					if(TakeOutItem(itemunique, itemnum, PERSONITEMINFO_OPTION_NONE) == true)
					{
						cltWarpInfo clWarpInfo(1, mapindex, false, false, dx, dy, x, y);
						SetWarpInfo(&clWarpInfo, 40);

						// 아이템사용을 완벽하게 하기위해 바로 워프를 시킨다.
						// 아이템사용과 함께 워프 로그를 DB에 적는다.
						Warp(true);
					}
					else
					{
						// 해당맵은 XX 아이템 X개가 있어야 들어갈 수 있습니다.
						pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_NOITEM, 
							itemunique, itemnum,
							pclchar->GetCharUnique());
						return;
					}
				}
				else
				{
					// 아이템을 사용하지 않는 맵은 기존 방식으로 워프를 처리한다.
					cltWarpInfo clWarpInfo(1, mapindex, false, false, dx, dy, x, y);
					SetWarpInfo(&clWarpInfo, 40);
				}

				// 내상태에서 pvp를 뺀다 pvp-
				clInnerStatus.clEnemyType.siEnemyType = ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR;
			}
		}
		else
		{
			// 클라이언트로 서버의 응답값을 보낸다. 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendServerResponseMsg(0, SRVAL_NOTENOUGHLEVELTOMAP,  levellimit, 0, pclchar->GetCharUnique());

		}
	}
}



//------------------------------------------
// 캐릭터 생성을 위한 기본 정보 
//------------------------------------------
bool cltCharServer::GetMakeCharInfo(cltMakeCharInfo* pclinfo, bool borderswitch, bool bticketusewarpswitch)
{
	SI32 x, y;
	SI32 attackid;
	SI32 attackcharuniqueid;
	cltOrderDataInfo		clOrder;

	// 사망한 캐릭터면 정보를 확보하지 않는다. 
	//cyj 사망한 캐릭터도 정보 확보 하도록 수정
	if(GetLife() <= 0 && IsAtb(ATB_HERO) == FALSE) return false;

	// 정지 동작만 수용. 
	if(borderswitch == false)
	{
		clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);
	}
	else
	{
		// 현재 수행하고 있는 동작도 전달한다. 
		switch(GetCurrentOrder())
		{
		case ORDER_MOVE:
			if(siMoveMapIndex == GetMapIndex())
			{
				x = clMoveInfo.siDX;
				y = clMoveInfo.siDY;
				pclClient->pclOrderManager->MakeOrder_MOVE(&clOrder, x, y, BY_PLAYER);
			}
			else
			{
				clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);
			}
			break;
		case ORDER_STRAIGHTMOVE:
			if(siMoveMapIndex == GetMapIndex())
			{
				x = clMoveInfo.siDX;
				y = clMoveInfo.siDY;
				pclClient->pclOrderManager->MakeOrder_STRAIGHTMOVE(&clOrder, x, y, BY_PLAYER);
			}
			else
			{
				clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);
			}

			break;

		case ORDER_ATTACK:
			x			= clAttackTarget.clPos.GetX();
			y			= clAttackTarget.clPos.GetY();
			attackid	= clAttackTarget.GetAttackID();
			if(pclCM->IsAlive(attackid))
			{
				attackcharuniqueid	= pclCM->CR[attackid]->GetCharUnique();
			}
			else
			{
				attackcharuniqueid	= 0;
			}

			clOrder.Make(ORDER_ATTACK, BY_PLAYER, (x|(y<<16)), attackcharuniqueid, 0, 0);
			break;
		case ORDER_FISH:
			pclClient->pclOrderManager->MakeOrder_FISH(&clOrder, siDirection, BY_PLAYER);
			break;

		case ORDER_FARM:
			pclClient->pclOrderManager->MakeOrder_FARM(&clOrder, siFarmX, siFarmY, BY_PLAYER);
			break;
		case ORDER_MINE:
			pclClient->pclOrderManager->MakeOrder_MINE(&clOrder, siMineX, siMineY, BY_PLAYER);
			break;
		case ORDER_SITDOWN:
			pclClient->pclOrderManager->MakeOrder_SITDOWN(&clOrder, siDirection, BY_PLAYER );
			break;


		case ORDER_DEAD:
		case ORDER_DIE:
			clOrder.Make(ORDER_DIE, BY_PLAYER, 0, 0, 0, 0);
			break;

		case ORDER_ATTACK_CLIENT:
			x			= clAttackTarget.clPos.GetX();
			y			= clAttackTarget.clPos.GetY();
			attackid	= clAttackTarget.GetAttackID();
			if(pclCM->IsAlive(attackid))
			{
				attackcharuniqueid	= pclCM->CR[attackid]->GetCharUnique();
			}
			else
			{
				attackcharuniqueid	= 0;
			}

			clOrder.Make(ORDER_ATTACK_CLIENT, BY_PLAYER, (x|(y<<16)), attackcharuniqueid, 0, 0);
			break;

		case ORDER_SPECIAL_ACTION:
			{
				clOrder.Make(ORDER_SPECIAL_ACTION, BY_PLAYER, 0, 0, 0, 0);
			}
			break;

		default:
			clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0 );
			break;
		}
	}

	// 외부 장비. 
	cltShapeEquipInfo clequip;
	if(IsPC(GetCharUnique()))
	{
		GetShapeEquipInfo(&clequip);
	}

	// AddInfo를 요구할지 여부. 
	UI32 uiRequestAddinfo = 0;

	SI32 siHorseUnique		= 0;
	SI32 siAddStatusDate	= 0;
	SI32 siTicketNum		= 0;

	// 프리미엄 파츠 장착 여부
	SI32 siPremiumpartsslot1		= 0;
	SI32 sipremiumpartsuniqueslot1	= 0;
	SI32 siPremiumpartsslot2		= 0;
	SI32 sipremiumpartsuniqueslot2	= 0;
	SI32 siPremiumpartsslot3		= 0;
	SI32 sipremiumpartsuniqueslot3	= 0;
	SI32 siPremiumpartsNum		= 0;

	// LEEKH 2007.10.28 - 기승동물 처리 수정
	cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclHorse != NULL)
	{
		siHorseUnique	= pclHorse->siHorseUnique;
		siAddStatusDate	= pclHorse->clAddStatusDate.GetDateVary();
		siTicketNum		= pclHorse->siStatusTicketNum;

		siPremiumpartsslot1		= pclHorse->clPremiumPartsDate_Slot1.GetDateVary();
		sipremiumpartsuniqueslot1		= pclHorse->siPremiumUnique_Slot1;

		siPremiumpartsslot2		= pclHorse->clPremiumPartsDate_Slot2.GetDateVary();
		sipremiumpartsuniqueslot2		= pclHorse->siPremiumUnique_Slot2;

		siPremiumpartsslot3		= pclHorse->clPremiumPartsDate_Slot3.GetDateVary();
		sipremiumpartsuniqueslot3		= pclHorse->siPremiumUnique_Slot3;

		siPremiumpartsNum		= pclHorse->siPremiumPartsNum;

	}

	SI32 BufTransformKind = 0;
	if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) )
	{
		stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf( BUF_TRANSFORM );
		if(pclBuf)			BufTransformKind = pclBuf->siPercent;
	}

	SI16 siDisplayLoveLevel = 0;
	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		if ( (pclMarriage) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclMarriage->GetConnectMode()) )
		{
			siDisplayLoveLevel = pclMarriage->GetLoveLevel();
		}
	}

	//KHY - 1001 - 기승동물 5마리 보유 수정.
	cltMakeCharInfo	clMakeCharInfo(GetKind(), GetCharUnique(), pclCI->clIP.GetLevel(), GetLife(), GetX(), GetY(), GetMapIndex(), 
		siChildCharUnique, 
		siSummonIndex, 
		bHeadChatSwitch,		// 머릿말이 존재하는가?
		bPersonalShopSwitch,
		bNoFirstAttackSwitch | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK) | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI)  | pclCI->clBI.clBufInfo.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) 
		| pclCI->clBI.clBufInfo.IsHaveBufExecptGetType(BUF_TRANSFORM, BUF_GET_TYPE_NIGHTMARKET),	// 선공 방어가 설정되어 있는가. 
		bNoIceAttackSwitch,
		pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) && pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FRIENDSHIP) ,
		pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FOURLEAF) , pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FARMINGNMININGFOREVER),
		IsHaveCushionItem() ,
		pclCI->clBI.uiSex,			// 성별. 
		&clequip,
		pclCI->clHorseInfo.siCurrentShowHorse,
		clPB.GetTotalMoveSpeed(),
		clJim.siJimHostCharUnique, 
		GetGameMasterLevel(), 
		0,
		siHorseUnique,
		pclCI->clBI.siHomeVillage,
		pclCI->clBI.siSchoolUnique,
		&pclCI->clCharRank, 
		siAddStatusDate,
		siTicketNum,
		&clOrder,
		&clIdentity, 
		&clInnerStatus,
		uiRequestAddinfo,
		bticketusewarpswitch,
		pclCI->clBI.uiGMMode,
		pclCI->clBI.bPCRoom,
		siPersonalMakeItemType,
		&pclCI->clBI.clGuildRank,
		&pclCI->clPersonNaming,
		pclCI->clHorseInfo.siCurrentHorseRIDEHORSE,
		clTransFormInfo.uiNowTransFormKind,
		clTransFormInfo.bTransFormMode,
		uiBestGuild,										// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
		bIsElectionStump,
		clTransFormInfo.bTransForm100Effect,
		BufTransformKind,
		siEnemUnique,
		pclValentineWar,
		bElixirSwitch
		,pclPVP_LeagueInfo
		,siPremiumpartsslot1
		,sipremiumpartsuniqueslot1
		,siPremiumpartsslot2
		,sipremiumpartsuniqueslot2
		,siPremiumpartsslot3
		,sipremiumpartsuniqueslot3
		,siPremiumpartsNum
		,m_uiWeaponSkillMasterEmblem
		,siDisplayLoveLevel
		,siMySoulGuardUnique
		,bRepairShopSwitch
		,&pclCI->clBI.clBufInfo
		);

	pclinfo->Set(&clMakeCharInfo);

	return true;
}

// 주인 캐릭터의 포인터를 구한다. 
cltCharServer* cltCharServer::GetHostChar()
{
	// 소환수이면, 주인이 공을 세운 것이다. 
	if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
	{
		if(pclCM->IsValidID(clIdentity.clSummonInfo.siParentCharUnique))
		{
			return (cltCharServer*)(pclCM->CR[clIdentity.clSummonInfo.siParentCharUnique]);
		}
	}

	return this;
}

// 예약되어 있는 공격 명령을 수행한다. 
bool  cltCharServer::DoReservedAttackAction(cltOrderDataInfo* pclorder)
{
	if(siReservedAttackTargetID == 0)return false;

	pclClient->pclOrderManager->MakeOrder_ATTACK(pclorder, siReservedAttackTargetID, BY_PLAYER);

	SetReservedAttackTargetID(0);

	return true;
}

bool  cltCharServer::DoReservedAttackClientAction(cltOrderDataInfo* pclorder)
{
	if(siReservedAttackTargetID == 0)return false;

	pclClient->pclOrderManager->MakeOrder_ATTACK_CLIENT(pclorder, siReservedAttackTargetID, BY_PLAYER);

	SetReservedAttackTargetID(0);

	return true;
}



// 무기 사용술 부적 사용 실태를 체크한다. 
void  cltCharServer::CheckWeaponSkillScroll(cltItemManagerCommon* pclItemManager)
{
	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USESWORD1) == true)
	{
		bSwordScroll = true;
		siSwordScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USESWORD1);
	}
	else
	{
		bSwordScroll = false;
	}

	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USESPEAR1) == true)
	{
		bSpearScroll = true;
		siSpearScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USESPEAR1);
	}
	else
	{
		bSpearScroll = false;
	}

	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USEAXE1) == true)
	{
		bAxeScroll = true;
		siAxeScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USEAXE1);
	}
	else
	{
		bAxeScroll = false;
	}

	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USEGUN1) == true)
	{
		bGunScroll = true;
		siGunScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USEGUN1);
	}
	else
	{
		bGunScroll = false;
	}
	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USEBOW1) == true)
	{
		bBowScroll = true;
		siBowScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USEBOW1);
	}
	else
	{
		bBowScroll = false;
	}
	if(pclCI->clCharItem.UseWeasponSkillScroll(pclItemManager,SKILL_USESTAFF1) == true)
	{
		bStaffScroll = true;
		siStaffScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum(pclItemManager,SKILL_USESTAFF1);
	}
	else
	{
		bStaffScroll = false;
	}

}

// 내 외양 장비 상황을 얻어온다. 
void cltCharServer::GetShapeEquipInfo(cltShapeEquipInfo* pclequip)
{
#ifdef _DEBUG
	//--------------------------------------------------
	// 무기사용술 부적 사용 실태를 체크한다. 
	//--------------------------------------------------
	CheckWeaponSkillScroll( pclClient->pclItemManager);
#endif


	// 갑옷, 의복의 모습을 결정한다. 
	// 투구, 모자의 모습을 결정한다. 
	if((ActiveClothes<0)||(ActiveHat<0))
	{
		return;
	}

	cltItem* pclarmour	= &pclCI->clCharItem.clItem[ ActiveClothes ];
	cltItem* pclhelmet = &pclCI->clCharItem.clItem[ActiveHat];		

	SI32 AvailableClothes = ActiveClothes;
	SI32 AvailableHelmet = ActiveHat;

	cltServer *pclserver = (cltServer*)pclClient;

	//-------------------------------------------------------------------------
	// 기간을 체크하여, 진짜 보여줘야만 하는 위 아래를 만든다.
	// 갑옷, 의복의


	//아바타 아이템일 경우 아이템 유니크를 0 으로 만들지 않는다.
	if(pclarmour->IsHaveUseDay())
	{
		SI32 useableDay = 0;
		BOOL rVal = pclserver->GetItemUseAbleDay(pclarmour,&useableDay);
		
		if(useableDay < 0 && rVal == TRUE ) // 기간이 지난 아이템이면 안그려준다.
		{
			if ( ITEMTYPE_AVATAR_DRESS == pclarmour->GetAavatarType( pclserver->pclItemManager ) )
			{
			}
			else // 아바타 아이템이 아닐경우 수행된다.
			{
				pclarmour->siUnique = 0;
			}
		}
	}

	// 투구, 모자의
	if(pclhelmet->IsHaveUseDay())
	{
		SI32 useableDay = 0;
		BOOL rVal = pclserver->GetItemUseAbleDay(pclhelmet,&useableDay);
		
		if(useableDay < 0 && rVal == TRUE ) // 기간이 지난 아이템이면 안그려준다.
		{
			if ( ITEMTYPE_AVATAR_HAT== pclhelmet->GetAavatarType( pclserver->pclItemManager ) )
			{
			}
			else
			{
				pclhelmet->siUnique = 0;
			}
		}
	}


	if( pclarmour->siUnique == 0 )
	{
		if( AvailableClothes == PERSONITEM_DRESS)
			AvailableClothes = PERSONITEM_ARMOUR;
		else
			AvailableClothes = PERSONITEM_DRESS;     
	}

	if(pclhelmet->siUnique==0)
	{
		if(AvailableHelmet == PERSONITEM_HELMET)
			AvailableHelmet = PERSONITEM_HAT;
		else
			AvailableHelmet = PERSONITEM_HELMET;
	}

	pclhelmet 	= &pclCI->clCharItem.clItem[ AvailableHelmet ];
	pclarmour       = &pclCI->clCharItem.clItem[ AvailableClothes ];	
	//-------------------------------------------------------------------------

	SI32 NowActiveClothesUnique = pclCI->clCharItem.clItem[AvailableClothes].siUnique;		// 현재 보여지는 의목
	SI32 NowActiveHatUnique = pclCI->clCharItem.clItem[AvailableHelmet].siUnique;			// 현재 보여지는 모자


	//[추가 : 황진성 2007. 12. 12 신년 이벤트 이펙트 그리기 아이템들 설정.]
	UI32	RareInfo = pclarmour->clItemCommon.clCommonInfo.uiRareInfo;

	SYSTEMTIME sTime;
	GetLocalTime( &sTime );

	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		// 아이템몰 아이템인가?
		if(pclClient->pclItemManager->IsItemInfoAtb( pclarmour->siUnique, ITEMINFOATB_ITEMMALL ))
		{
			RareInfo = NEWYEAR_EFFECT;
		}
	}


	if ( (NowActiveHatUnique == ITEMUNIQUE(23117) && NowActiveClothesUnique == ITEMUNIQUE(23696))  // 결혼 예식 머리 + 결혼 예식용 턱시도  이거나
		||  (NowActiveHatUnique == ITEMUNIQUE(23118) && NowActiveClothesUnique == ITEMUNIQUE(23698)))     // 결혼용 면사포 +  웨딩용 드레스 일때만.

	{
		// 결혼했을 경우에만 이펙트를 그려준다.
		if(IsMarried())
		{
			RareInfo = MARRIED_FULLDRESS_EFFECT;
		}
	}

	cltShapeEquipInfoUnit clArmour(pclarmour->siUnique, RareInfo, pclarmour->Element.siType, pclarmour->Element.siPower );
	//---------------------------------------------------------------------------------------------------------------
	RareInfo = 0;

	//[추가 : 황진성 2007. 12. 12 신년 이벤트 이펙트 그리기 아이템들 설정.]
	RareInfo = pclhelmet->clItemCommon.clCommonInfo.uiRareInfo;
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		// 아이템몰 아이템인가?
		if(pclClient->pclItemManager->IsItemInfoAtb( pclhelmet->siUnique, ITEMINFOATB_ITEMMALL ))
		{
			RareInfo = NEWYEAR_EFFECT;
		}
	}

	if ( (NowActiveHatUnique == ITEMUNIQUE(23117) && NowActiveClothesUnique == ITEMUNIQUE(23696))  // 결혼 예식 머리 + 결혼 예식용 턱시도  이거나
		||  (NowActiveHatUnique == ITEMUNIQUE(23118) && NowActiveClothesUnique == ITEMUNIQUE(23698)))     // 결혼용 면사포 +  웨딩용 드레스 일때만.
	{
		// 결혼했을 경우에만 이펙트를 그려준다.
		if(IsMarried())
		{
			RareInfo = MARRIED_FULLDRESS_EFFECT;
		}
	}

	cltShapeEquipInfoUnit clHelmet(pclhelmet->siUnique, RareInfo, pclhelmet->Element.siType, pclhelmet->Element.siPower );
	//---------------------------------------------------------------------------------------------------------------
	RareInfo = 0;


	cltShapeEquipInfoUnit clMantle(pclCI->clCharItem.clItem[PERSONITEM_MANTLE].siUnique, pclCI->clCharItem.clItem[PERSONITEM_MANTLE].clItemCommon.clCommonInfo.uiRareInfo
		, pclCI->clCharItem.clItem[PERSONITEM_MANTLE].Element.siType , pclCI->clCharItem.clItem[PERSONITEM_MANTLE].Element.siPower );

	//[추가 : 황진성 2007. 12. 12 신년 이벤트 이펙트 그리기 아이템들 설정.]
	RareInfo = pclCI->clCharItem.clItem[ActiveWeapon].clItemCommon.clCommonInfo.uiRareInfo;
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		SI32	Unique[] = {97, 172, 372, 272, 468, 568};
		SI32	Cnt		 = sizeof(Unique)/ sizeof(SI32);
		for(SI32 i = 0; i < Cnt; ++i)
		{
			if(Unique[i] == pclCI->clCharItem.clItem[ActiveWeapon].siUnique)		
			{
				if(RARELEVEL_6 != pclCI->clCharItem.clItem[ ActiveWeapon ].clItemCommon.clCommonInfo.uiRareInfo)
				{
					RareInfo = NEWYEAR_EFFECT;
				}
			}
		}
	}

	cltShapeEquipInfoUnit clWeapon(pclCI->clCharItem.clItem[ActiveWeapon].siUnique, 
		RareInfo, pclCI->clCharItem.clItem[ActiveWeapon].Element.siType , pclCI->clCharItem.clItem[ActiveWeapon].Element.siPower );

	cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;

#ifdef _SAFE_MEMORY
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		m_siSetItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep , USE_SETITEM_1 );
		m_siSetItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep2, USE_SETITEM_2 );
		m_siSetItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep3, USE_SETITEM_3 );
		m_siSetItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep4, USE_SETITEM_4 );
		m_siSetItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep5, USE_SETITEM_5 );
	}
	else
		m_siSetItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( &pclCI->clCharItem.clItem[0] );
#else
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		m_siSetItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep , USE_SETITEM_1 );
		m_siSetItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep2, USE_SETITEM_2 );
		m_siSetItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep3, USE_SETITEM_3 );
		m_siSetItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep4, USE_SETITEM_4 );
		m_siSetItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( this, &m_siSetItemStep5, USE_SETITEM_5 );
	}
	else
		m_siSetItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( pclCI->clCharItem.clItem );
#endif
	// 세트아이템 정보 셋팅
	cltShapeEquipInfo clinfo(	&clArmour, &clHelmet, &clMantle, &clWeapon,
		bSwordScroll,
		bSpearScroll,
		bAxeScroll,
		bGunScroll,
		bBowScroll,
		bStaffScroll,
		bCannonScroll,
		siSwordScrollNum,
		siSpearScrollNum,
		siAxeScrollNum,
		siGunScrollNum,
		siBowScrollNum,
		siStaffScrollNum,
		m_siSetItemType,
		m_siSetItemStep,
		m_siSetItemType2,
		m_siSetItemStep2,
		m_siSetItemType3,
		m_siSetItemStep3,
		m_siSetItemType4,
		m_siSetItemStep4,
		m_siSetItemType5,
		m_siSetItemStep5		);
	pclequip->Set(&clinfo);

}

void cltCharServer::SetLastKillClock(DWORD clock)
{
	clSimpleVary.dwLastKillClock = clock;
}

void cltCharServer::SetReservedAttackTargetID(SI16 id)
{
	siReservedAttackTargetID = id;
}

//--------------------------------
// Group
//--------------------------------
void cltCharServer::SetNPCGroup(SI32 group)
{
	NPCGroup	= group;
}

SI32 cltCharServer::GetNPCGroup() const
{
	return NPCGroup;
}

void cltCharServer::SetLastReceveFromClientClock(DWORD clock)
{
	LastReceveFromClientClock = clock;
}

bool cltCharServer::CheckSubBigItem()
{
	if (pclCI->clIP.GetLevel() <= 0) 
		return false;

	UI32 usertotalstatus = pclCI->clIP.GetLevel() * 6;
	UI32 luckpercent = pclCI->clIP.GetLuk() * 100 / usertotalstatus;
	UI32 hndpercent = pclCI->clIP.GetHnd() * 100 / usertotalstatus;

	UI32 luckpoint = 0;
	UI32 hndpoint = 0;
	UI32 subpoint = 0;

	if (luckpercent >= 0)
	{
		if (luckpercent < 3)	luckpoint = 6;
		else if (luckpercent < 6)	luckpoint = 12;
		else if (luckpercent < 9)	luckpoint = 18;
		else if (luckpercent < 12)	luckpoint = 24;
		else if (luckpercent < 15)	luckpoint = 30;
		else if (luckpercent < 18)	luckpoint = 36;
		else if (luckpercent < 21)	luckpoint = 42;
		else if (luckpercent < 24)	luckpoint = 48;
		else if (luckpercent < 27)	luckpoint = 54;
		else	luckpoint = 60;
	}

	if (hndpercent >= 0)
	{
		if (hndpercent < 3)	hndpoint = 6;
		else if (hndpercent < 6)	hndpoint = 12;
		else if (hndpercent < 9)	hndpoint = 18;
		else if (hndpercent < 12)	hndpoint = 24;
		else if (hndpercent < 15)	hndpoint = 30;
		else if (hndpercent < 18)	hndpoint = 36;
		else if (hndpercent < 21)	hndpoint = 42;
		else if (hndpercent < 24)	hndpoint = 48;
		else if (hndpercent < 27)	hndpoint = 54;
		else	hndpoint = 60;
	}

	subpoint = (luckpoint * 0.3 + hndpoint * 0.2) + 2;

	UI32 randvalue = rand() % 1000000;
	// 대박아이템 줌
	if (randvalue < subpoint)
	{
		return true;
	}

	return false;

}

bool cltCharServer::IsNowAddBufThroughDB()
{
	return bIsNowAddBufThroughDB;		 
}

bool cltCharServer::AddBufThroughDB(SI16 index, stBuf* pbuf, bool useitem, SI16 itempos, cltItem* pclitem, GMONEY money)
{
	if( IsNowAddBufThroughDB() ) return false;

	sDBRequest_AddBuf clAddbuf( pclCI->GetPersonID(), index, pbuf, useitem, itempos, pclitem, money);
	((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clAddbuf);

	bIsNowAddBufThroughDB = true;	
	return true;
}

bool cltCharServer::AddBufThroughDB_AccumulateEnable(stBuf* pBuf, bool useitem, SI16 itempos, cltItem* pclitem, GMONEY money)
{
	cltServer* pServer = (cltServer*)pclClient;
	if ( NULL == pServer ) return false;
	if ( NULL == pBuf ) return false;

	// 같은 버프가 이미 있는 상황인지 체크
	bool bIsExistBuf = pclCI->clBI.clBufInfo.IsHaveBuf( pBuf->siBufType );		// 같은 버프가 있는지 확인
	SI32 siRemainTime = 0;
	SI16 siIndex = -1;

	// 같은 버프가 있을경우에만 이전에 있던 버프의 남은 시간을 새로 추가할 버프 시간에 더해줌.
	if ( true == bIsExistBuf )
	{
		SI32 siCurrentGameTime = 0;
		siCurrentGameTime = pServer->pclTime->clDate.GetHourVary();

		SI32 siBufOverTime = 0;
		siBufOverTime = pclCI->clBI.clBufInfo.GetBufOvertime( pBuf->siBufType );

		// 버프의 남은 시간을 구한다.
		if ( siCurrentGameTime <= siBufOverTime )
		{
			siRemainTime = siBufOverTime - siCurrentGameTime;
		}

		// 버프가 위치한 인덱스를 얻어온다.
		SI16 siExistBufIndex = 0;
		siExistBufIndex = pclCI->clBI.clBufInfo.FindBufSlot( pBuf->siBufType );

		stBuf* pExistBuf = pclCI->clBI.clBufInfo.GetBuf( pBuf->siBufType );
		if ( NULL != pExistBuf )
		{
			siIndex = siExistBufIndex;		// 해당 자리에 다시 같은 버프가 들어갈거니까 siIndex엔 더해질 버프의 위치를 넣는다.

			// 디비에 버프 지우라고 메세지 보냄
			//stBuf delbuf( pExistBuf->siBufType, 0, 0, 0 );
			//sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), siExistBufIndex, &delbuf );
			//pServer->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
		}
	}
	else
	{
		siIndex = pclCI->clBI.clBufInfo.FindEmptySlot( pBuf->siBufType, false );	// 버프가 들어갈 인덱스를 얻어온다.
	}

	SI32 siUsetime = pBuf->siOverTime;			// 버프의 overtime은 이 함수 호출 전에 계산되어서 넘어와야 한다. (기존 루틴 침범 안함)
	siUsetime += siRemainTime;

	if ( 0 <= siIndex )
	{
		stBuf addbuf( pBuf->siBufType, pBuf->siPercent, siUsetime );
		AddBufThroughDB( siIndex, &addbuf, useitem, itempos, pclitem, money );
	}

	return true;
}

// 특정 유니크의 마을 주민에게 지정한 버프를 준다. (접속해 있는 유저에게만 줌) - 트리거가 특정 유저가 사용한 아이템 일경우에만 이 함수 호출하는게 바람직함.
bool cltCharServer::AddBufToAllTownPerson(SI32 siTownUnique, stBuf* pBuf, SI32 siSkipBuf1, SI32 siSkipBuf2)		// 예외 조건은 일단 두개로 제한. 더 필요하면 ...구문으로 교체
{
	// 1. 예외 조건 체크
	cltServer* pServer = (cltServer*)pclClient;
	if ( NULL == pServer->pclVillageManager ) return false;
	if ( false == pServer->pclVillageManager->IsValidVillage( siTownUnique ) ) return false;
	if ( NULL == pBuf ) return false;

	// 2. 로그인하고 있는 모든 마을 주민에게 버프 지급
	SI32 index = 0;
	SI32 id;
	while ( id = pServer->pclCM->GetCharOrder(index) )		// id가 false 즉, 0이 되면 종료. (GetCharOrder() 함수가 0을 리턴하면 종료)
	{
		index++;

		cltCharServer* pclchar  = (cltCharServer*)pServer->pclCM->CR[id];
		if ( NULL == pclchar ) continue;

		if(pclchar->IsValidConnection() == false) continue;					// 사용자인 컴에게만 전달한다
		if(pclchar->pclCI->clBI.siHomeVillage != siTownUnique) continue;	// 해당 마을 주민에게만 준다.

		// 버프 지급에 대한 예외 처리 (경험치 일 경우 스페셜 앰플 효과가 있으면 경험치 버프 못받게..)
		if ( true == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(siSkipBuf1) ) continue;
		if ( true == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(siSkipBuf2) ) continue;

		// 영주는 따로 주니까 주민 검색하다 영주가 나오면 그냥 스킵
		if ( RANKTYPE_CITYHALL == pclchar->pclCI->clCharRank.siType ) continue;

		AddTownBufThroughDB( pclchar, pBuf );
	}

	return true;
}

bool cltCharServer::AddTownBufThroughDB(cltCharServer* pCharServer, stBuf* pBuf)
{
	cltServer* pServer = (cltServer*)pclClient;
	if ( NULL == pServer ) return false;
	if ( NULL == pCharServer || NULL == pBuf ) return false;

	// 같은 버프가 이미 있는 상황인지 체크
	bool bIsExistBuf = pCharServer->pclCI->clBI.clBufInfo.IsHaveBuf( pBuf->siBufType );		// 같은 버프가 있는지 확인
	SI32 siRemainTime = 0;
	SI16 siIndex = -1;

	// 같은 버프가 있을경우에만 이전에 있던 버프의 남은 시간을 새로 추가할 버프 시간에 더해줌.
	if ( true == bIsExistBuf )
	{
		SI32 siCurrentGameTime = 0;
		siCurrentGameTime = pServer->pclTime->clDate.GetHourVary();

		SI32 siBufOverTime = 0;
		siBufOverTime = pCharServer->pclCI->clBI.clBufInfo.GetBufOvertime( pBuf->siBufType );

		// 버프의 남은 시간을 구한다.
		if ( siCurrentGameTime <= siBufOverTime )
		{
			siRemainTime = siBufOverTime - siCurrentGameTime;
		}

		// 버프가 위치한 인덱스를 얻어온다.
		SI16 siExistBufIndex = 0;
		siExistBufIndex = pCharServer->pclCI->clBI.clBufInfo.FindBufSlot( pBuf->siBufType );

		stBuf* pExistBuf = pCharServer->pclCI->clBI.clBufInfo.GetBuf( pBuf->siBufType );
		if ( NULL != pExistBuf )
		{
			siIndex = siExistBufIndex;

			// 디비에 버프 지우라고 메세지 보냄
			//stBuf delbuf( pExistBuf->siBufType, 0, 0, 0 );
			//sDBRequest_DeleteBuf clMsg( pCharServer->pclCI->GetPersonID(), siExistBufIndex, &delbuf );
			//pServer->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
		}
	}
	else
	{
		siIndex = pCharServer->pclCI->clBI.clBufInfo.FindEmptySlot( pBuf->siBufType, false );	// 버프가 들어갈 인덱스를 얻어온다.
	}

	SI32 siUsetime = pServer->pclTime->clDate.GetHourVary() + 24;			// 디폴트 값은 현실시간 48분간 (게임시간1일).
	siUsetime += siRemainTime;

	if ( 0 <= siIndex )
	{
		stBuf addbuf( pBuf->siBufType, pBuf->siPercent, siUsetime );
		pCharServer->AddBufThroughDB( siIndex, &addbuf, false, 0, NULL );
	}

	return true;
}

SI64 cltCharServer::CalcTiredPoint( SI64 point )
{
	switch( uiTiredState )
	{
	case TIRED_STATUS_LITTLE_TIRED:
		return point >> 1; // 내림으로 계산된다.
	case TIRED_STATUS_MUCH_TIRED:
		return 0;
	default:
		return point;
	}
}
SI32 cltCharServer::CalcTiredPoint( SI32 point )
{
	switch( uiTiredState )
	{
	case TIRED_STATUS_LITTLE_TIRED:
		return point >> 1;
	case TIRED_STATUS_MUCH_TIRED:
		return 0;
	default:
		return point;
	}
}
SI16 cltCharServer::CalcTiredPoint( SI16 point )
{
	switch( uiTiredState )
	{
	case TIRED_STATUS_LITTLE_TIRED:
		return point >> 1;
	case TIRED_STATUS_MUCH_TIRED:
		return 0;
	default:
		return point;
	}
}

bool cltCharServer::CharTransform( SI16 siCharKind  , SI16 ActiveWeapon , cltItem *pclItemList ,cltPSkillInfo *pclskillinfo)
{
	if(siCharKind > 0)
	{
		// 변신 하기
		// 능력치 재설정.
		clTransFormInfo.bTransFormMode = true;	
		clTransFormInfo.uiNowTransFormKind = siCharKind;
	}
	else
	{
		// 변신 해제
		clTransFormInfo.bTransFormMode = false;	
	}

	// 변신은 캐릭터 상태값이 바뀌어야 한다.
	SetParametaBoxAction(true);

	// 워프 - 다시그려주기.
	OrderStop(GetCharID(), BY_COMPUTER);

	// 변신일때는 이벤트 타일이 깔려도 워프 한다.
	cltWarpInfo clWarpInfo(1, GetMapIndex(),true, false, GetX(), GetY(), -1, -1);
	SetWarpInfo(&clWarpInfo, 10000);
	Warp();

	if( siCharKind > 0)
	{
		// 클라이언트로 알리기 - 변신을 하는 경우에만 정보를 업데이트 한다.
		cltGameMsgResponse_SetTransForm clinfo1(&clTransFormInfo);
		cltMsg clMsg1(GAMEMSG_RESPONSE_TRANSFORM, sizeof(clinfo1), (BYTE*)&clinfo1);
		SendNetMsg((sPacketHeader*)&clMsg1);
	}

	return true;
}

//KHY - 1113 - 크리스마스 이벤트 - 대표 kind값으로 변환한다.
void cltCharServer::ChristamsEventQuest(SI32 *Enemykind)
{

	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_YETI"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_YETI_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_YETI_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_YETI"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWELF"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWELF_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWELF_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_SNOWELF"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_TONGUEGIRL"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_TONGUEGIRL_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_TONGUEGIRL_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_TONGUEGIRL"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWMAN"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWMAN_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_SNOWMAN_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_SNOWMAN"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_MARIONETTE_SANTA"));

		return;
	}
	//---------------------------------------------------------------------//
	if(*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA_1"))||
		*Enemykind == pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA_2"))) 
	{
		*Enemykind = pclClient->GetUniqueFromHash(TEXT("KIND_WILDCAT_SANTA"));

		return;
	}
	//---------------------------------------------------------------------//
}

//-----------------------------------------------------------------------------------------------------------------------
// Dec		: 내가 갖고 있는 수호정령의 특수 능력을 발동 시킨다
// Param	: siAbility = 발동 시키고자하는 특수능력
//			  siLessThanValue = 이 값이 0이상일때 이 값보다 특수능력 발동 수치가 적으면 발동되지 않음	
//			  siMoreThanValue = 이 값이 0이상일때 이 값보다 특수능력 발동 수치가 크면 발동되지 않음
// Return	: 특수능력 발동 수치
//-----------------------------------------------------------------------------------------------------------------------
SI32 cltCharServer::SoulGuardAbilityActivity( SI32 siAbility, SI32 siLessThanValue/* =0 */, SI32 siMoreThanValue/* =0  */)
{
	if ( !IsPC(GetCharID()) )
	{
		return 0;
	}

	if ( 0 >= siAbility )
	{
		return 0;
	}

	// 쿨타임 체크
	if(pclClient->CurrentClock > 0)	//현재 시간이 양수라면
	{
		if(clockSoulGuardCoolTime > pclClient->CurrentClock)
			return 0;
	}
	else // 현재 시간이 음수라면
	{
		if(TABS(clockSoulGuardCoolTime) <= TABS(pclClient->CurrentClock))
			return 0;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return 0;
	}

	if ( NULL == pclserver->m_pclSoulGuardMgr )
	{
		return 0;
	}

	if ( FALSE == IsSoulGuardStatusOut() )
	{
		return 0;
	}

	// 친화력이 0이하이면 바로 리턴
	if ( 0 >= pclSoulGuard->GetFellowShip() )
	{
		return 0;
	}

	// 해당 능력을 갖고 있지 않으면 리턴
	if ( FALSE == pclSoulGuard->IsHaveAbility(siAbility) )
	{
		return 0;
	}

	// 위에서 소환된 상태를 검사는 하지만 실제 소환된 캐릭터로 다시한번 검사한다
	cltCharServer* pclMySoulGuard = pclserver->pclCM->GetCharServer( siMySoulGuardUnique );
	if ( NULL == pclMySoulGuard )
	{
		return 0;
	}

	if ( pclCI->GetPersonID() != pclMySoulGuard->clIdentity.clSoulGuard.m_siParentPersonID )
	{
		return 0;
	}

	// 수호정령이 갖고있는 능력 정보를 갖고온다
	cltSoulGuardAbilityUnit* pclGetUnit = pclserver->m_pclSoulGuardMgr->GetAbilityUnit( pclSoulGuard->GetKind(), siAbility );
	if ( NULL == pclGetUnit )
	{
		return 0;
	}

	// 실제 발동값이 이 값보다 적다면 리턴
	if ( (0 < siLessThanValue) &&  (siLessThanValue > pclGetUnit->GetValue()) )
	{
		return 0;
	}

	// 실제 발동값이 이 값보다 크다면 리턴
	if ( (0 < siMoreThanValue) && (siMoreThanValue < pclGetUnit->GetValue()) )
	{
		return 0;
	}

	// 소모되는 친화력보다 더 적은 친화력을 갖고 있다면 가능하지 않음
	if ( pclGetUnit->GetDecFellowShip() > pclSoulGuard->GetFellowShip() )
	{
		return 0;
	}

	// 친화력 사용 확률
	SI32 siRandProbably = (rand() % Const_Max_SoulGuard_ActiveProbably) + 1;
	if ( pclGetUnit->GetProbably() < siRandProbably  )
	{
		return 0;
	}

	// 자 여기까지 왔으니 너는 이제 특수 능력이 사용 가능하다
	SI16 siCalcFellowShip = pclSoulGuard->GetFellowShip() - pclGetUnit->GetDecFellowShip();
	if ( 0 > siCalcFellowShip )
	{
		siCalcFellowShip = 0;
	}

	// 친화력 설정
	pclSoulGuard->SetFellowShip( siCalcFellowShip );

	// 쿨타임을 설정 해주고
	clockSoulGuardCoolTime = (pclserver->CurrentClock + (pclGetUnit->GetCoolTimeSec() * 1000));

	// 능력에 따른 대사를 주위 캐릭터에게 뿌려준다
	SI32 siTextNum = pclserver->m_pclSoulGuardMgr->GetSoulGuardSpeechTextNum( siAbility );
	if ( 0 < siTextNum )
	{
		NTCHARString128 strText = GetTxtFromMgr( siTextNum );

		strText.Replace( TEXT("#mastername#"),	(TCHAR*)GetName() );
		strText.Replace( TEXT("#value#"),		SI16ToString(pclGetUnit->GetValue()) );

		cltGameMsgResponse_Chat clChat( siMySoulGuardUnique, CHATMODE_NORMAL, pclSoulGuard->GetName(), strText );
		cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);

		SendNeighbourMsg( &clMsg, true );
	}

	// 특수모션 발동시킨다
	SI32 siSoulGuardCharID = GetSoulGuardCharID();
	if ( pclCM->IsValidID(siSoulGuardCharID) )
	{
		OrderSpecialAction( siSoulGuardCharID, ANITYPE_SOULGUARDSF, BY_PLAYER );
	}
	
	// DB에도 보내준다
	sDBRequest_SoulGuard_FellowShipSet clMsg( pclCI->GetPersonID(), pclSoulGuard->GetSoulGuardID(), pclSoulGuard->GetFellowShip() );
	pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

	return pclGetUnit->GetValue();

}


void cltCharServer::SendSoulGuardParentDeadMessage( void )
{
	// 30초 간격으로 메시지를 보낸다
	if ( TABS(pclClient->CurrentClock-dwLastSoulGuardParentDeadMessageClock) < 30000 )
	{
		return;
	}

	dwLastSoulGuardParentDeadMessageClock = pclClient->CurrentClock;

	SI32 siTextNum		= 0;
	SI32 siRandValue	= rand() % 4;

	switch ( siRandValue )
	{
	case 0:	{	siTextNum = 30249;	}	break;
	case 1:	{	siTextNum = 30250;	}	break;
	case 2:	{	siTextNum = 30251;	}	break;
	case 3:	{	siTextNum = 30252;	}	break;
	}

	if ( 0 >= siTextNum )
	{
		return;
	}

	NTCHARString128 strMessage	= GetTxtFromMgr( siTextNum );
	NTCHARString64	strName;

	// 이름을 가져온다
	SI32			siParentCharID	= GetSoulGuardParentCharID();
	cltCharServer*	pclParentChar	= pclClient->pclCM->GetCharServer( siParentCharID );
	if ( (pclParentChar) && (pclParentChar->pclSoulGuard) )
	{
		strName = pclParentChar->pclSoulGuard->GetName();
	}
	else
	{
		strName = (TCHAR*)GetName();
	}

	cltGameMsgResponse_Chat clChat( GetCharUnique(), CHATMODE_NORMAL, strName, strMessage );
	cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);
	SendNeighbourMsg(&clMsg, true);
	
}

void cltCharServer::TransformSummon( cltCharManager* _pclCM, cltSummonTransformManager* _pclSummonTransformManager )
{
	//if( false == pclCI->clSummonInfo.IsSummonTranformTickCount() ) return;

	// 현재 소환수의 포인터 얻기.
	cltSummon*	pclCurSummonInfo = pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if( NULL == pclCurSummonInfo ) return;

	// 현재 소환수가 변신가능한 소환수가 있는지 찾는다.
	SI32	siTransformKind		= 0;
	SI32	siTransformAbility  = 0;
	_pclSummonTransformManager->GetTransformSummonInfo( pclCurSummonInfo->siKind, siTransformKind, siTransformAbility );
	if( 0 == siTransformKind ) return;

	// 변신 전의 소환수 정보를 저장하자.B
	cltSummon clPrevSummonInfo;
	clPrevSummonInfo.Set( pclCurSummonInfo );
	if( false == pclCI->clSummonInfo.IsSummonTranform(siSummonIndex) && 0 >= clPrevSummonInfo.clIP.GetLife() ) return;
	if( false == pclCI->clSummonInfo.IsSummonTranform(siSummonIndex) && SUMMON_POSSIBLE_TRANSFORM_TIME > pclCurSummonInfo->m_siTranformStamina ) return;
	

	// 소환한 소환수가 있어야 한다.
	SI32			siTansformSummonIndex	= siSummonIndex;
	cltCharServer*	pclSummon				= pclCM->GetCharServer( GetSummonID() );
	UI32			uiPrevStaminaFrame		= 0;
	if( pclSummon )
	{
		uiPrevStaminaFrame = pclSummon->uiStaminaFrame;

		// 게임에서 소환수를 지운다. 
		cltCharServer* pclCharSummon = _pclCM->GetCharServer( GetSummonID() );
		if( NULL== pclCharSummon ) return;
		pclCharSummon->DeleteInCell();
		if( FALSE == _pclCM->DeleteChar( GetSummonID() ) )
		{
			_pclCM->DeleteChar( pclCharSummon->GetID() );
		}

		// 주인이 갖고 있는 소환수의 정보를 설정한다.
		siChildCharUnique = 0;
		siSummonIndex	  = 0;

		// 주인한테도 정보를 갱신시킨다.
		cltGameMsgResponse_ChangeSummonStatus clInfo( GetID(), siChildCharUnique, siTansformSummonIndex );
		cltMsg clMsg( GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo );

		pclCurSummonInfo = pclCI->clSummonInfo.GetSummon( siTansformSummonIndex );
		if( pclCurSummonInfo )
		{
			cltGameMsgResponse_Summon clInfo( GetCharUnique(), siTansformSummonIndex, pclCurSummonInfo );
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	else
	{
		return;
	}

	//---------------------------------------------
	// 변신할 소환수를 설정하고 생성.
	//---------------------------------------------
	cltSummon	clTranformSummon;
	clTranformSummon.Set( &clPrevSummonInfo );
	clTranformSummon.siKind	= siTransformKind;
	clTranformSummon.clIP.SetStr(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetStr(),  siTransformAbility ) ); 
	clTranformSummon.clIP.SetWis(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetWis(),  siTransformAbility ) ); 
	clTranformSummon.clIP.SetHnd(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetHnd(),  siTransformAbility ) ); 
	clTranformSummon.clIP.SetVit(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetVit(),  siTransformAbility ) ); 
	clTranformSummon.clIP.SetDex(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetDex(),  siTransformAbility ) );  
	clTranformSummon.clIP.SetMag(  CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetMag(),  siTransformAbility ) );  
	clTranformSummon.clIP.SetMana( CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetMana(), siTransformAbility ) ); 
	clTranformSummon.clIP.SetLife( CalcuSummonTransFormAbility( clPrevSummonInfo.clIP.GetLife(), siTransformAbility ) ); 

	// 변신 복귀.
	if( pclCI->clSummonInfo.IsSummonTranform( siTansformSummonIndex ) )
	{	
		pclCI->clSummonInfo.SetSummonTranformIndex( -1 );	
		pclCI->clSummonInfo.SetSummonTranformTickCount();
	}
	// 변신 
	else
	{ 
		pclCI->clSummonInfo.SetSummonTranformIndex( siTansformSummonIndex );
		pclCI->clSummonInfo.SetSummonTranformTickCount();
	}

	SI32			siTransformSummonID	= CreateSummon( &clTranformSummon );
	cltSummon*		pclTranformSummon	= NULL;
	cltCharServer*	pclTransformSummon  = pclCM->GetCharServer( siTransformSummonID );
	if( pclTransformSummon )
	{
		// 소환수 스테미너를 처리하는 프레임 값을 변신전의 값으로 설정해준다.
		pclTransformSummon->uiStaminaFrame = uiPrevStaminaFrame;
		//==========================================
		// 주인이 갖고 있는 소환수의 정보를 설정한다.
		//==========================================
		pclTranformSummon = pclCI->clSummonInfo.GetSummonFromSummonID( clTranformSummon.siSummonID );
		if( pclTranformSummon )
		{
			pclTranformSummon->Set( &clTranformSummon );
			cltGameMsgResponse_Summon clInfo( GetCharUnique(), siTansformSummonIndex, pclTranformSummon );
			cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo );
			SendNetMsg( (sPacketHeader*)&clMsg );
		}

		siChildCharUnique	= siTransformSummonID; 
		siSummonIndex		= siTansformSummonIndex;

		// 변신한 소환수 캐릭의 포인터.
		cltCharServer* pclCharTranformSummon = pclCM->GetCharServer( siTransformSummonID );
		if( NULL == pclCharTranformSummon ) return;
		
		pclCharTranformSummon->ParametaBoxAction();

		// 주인한테도 정보를 갱신시킨다.
		cltGameMsgResponse_ChangeSummonStatus clInfo( GetCharUnique(), siChildCharUnique, siSummonIndex);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
		SendNetMsg((sPacketHeader*)&clMsg);
	}	

	// 움직이는 캐릭터를 사용자로 맞춘다.
	siSelectedCharIndex = -1 ;
}

void cltCharServer::UpDateSummonTransForm( cltSummonTransformManager* _pclSummonTransformManager, cltSummon* _pSummon, SI32 siTansformSummonIndex, cltSummon** _pTransformSummon  )
{
#if defined(_DBMANAGER)
	return;
#else
	static cltSummon clSrcSummon;

	if( NULL == _pSummon ) return;

	*_pTransformSummon = NULL;

	// 변신이 되있는가?
	if( pclCI->clSummonInfo.IsSummonTranform( siTansformSummonIndex ) )
	{
		SI32	siTransformKind		= 0;
		SI32	siTransformAbility	= 0;

		// 변신 전 소환수로 변신시킬 간단한 정보를 얻는다.
		_pclSummonTransformManager->GetTransformSummonInfo( _pSummon->siKind, siTransformKind, siTransformAbility );

		if( siTransformKind )
		{
			clSrcSummon.Set( _pSummon );
			clSrcSummon.siKind = siTransformKind;
			clSrcSummon.clIP.SetStr(  CalcuSummonTransFormAbility( _pSummon->clIP.GetStr(),  siTransformAbility ) ); 
			clSrcSummon.clIP.SetWis(  CalcuSummonTransFormAbility( _pSummon->clIP.GetWis(),  siTransformAbility ) ); 
			clSrcSummon.clIP.SetHnd(  CalcuSummonTransFormAbility( _pSummon->clIP.GetHnd(),  siTransformAbility ) ); 
			clSrcSummon.clIP.SetVit(  CalcuSummonTransFormAbility( _pSummon->clIP.GetVit(),  siTransformAbility ) ); 
			clSrcSummon.clIP.SetDex(  CalcuSummonTransFormAbility( _pSummon->clIP.GetDex(),  siTransformAbility ) );  
			clSrcSummon.clIP.SetMag(  CalcuSummonTransFormAbility( _pSummon->clIP.GetMag(),  siTransformAbility ) );  
			clSrcSummon.clIP.SetMana( CalcuSummonTransFormAbility( _pSummon->clIP.GetMana(), siTransformAbility ) ); 
			clSrcSummon.clIP.SetLife( CalcuSummonTransFormAbility( _pSummon->clIP.GetLife(), siTransformAbility ) ); 
	
			*_pTransformSummon = &clSrcSummon;
		}
	}
#endif
}

SI32 cltCharServer::CalcuSummonTransFormAbility( IN SI32 _siStatus, IN SI32 _siAbility )
{
	if( 10 < _siAbility	) return _siStatus * (_siAbility / 10);
	else				  return _siStatus / _siAbility;
}

void cltCharServer::TransformSummonStaminaUp( cltCharServer* pclParentChar, SI32 amt )
{
	cltSummon* pclSummon = pclParentChar->pclCI->clSummonInfo.GetSummon( pclParentChar->siSummonIndex );
	if( pclSummon ) 
	{
		cltServer* pclServer = (cltServer*)pclClient;
		if( pclServer->GetSummonTransformManager()->IsTransformSummonInfo( pclSummon->siKind ) )
		{
			pclSummon->m_siTranformStamina += amt / 10;

			// 최대치를 넘지 않게 한다.
			if( MAX_SUMMON_TRANSFORM_TIME < pclSummon->m_siTranformStamina )
				pclSummon->m_siTranformStamina = MAX_SUMMON_TRANSFORM_TIME;
		}
	}
}

void cltCharServer::TransformSummonStaminaDown( cltCharServer* pclParentChar, SI32 amt )
{
	// 해당 소환수의 변신 스테미너를 줄여준다.
	cltSummon* pclSummon = pclParentChar->pclCI->clSummonInfo.GetSummon( pclParentChar->siSummonIndex );
	if( pclSummon )
	{
		pclSummon->m_siTranformStamina -= amt;

		if( 0 >= pclSummon->m_siTranformStamina ) 
		{
			cltServer* pclServer = (cltServer*)pclClient;

			pclParentChar->TransformSummon( pclServer->pclCM, pclServer->GetSummonTransformManager() );
			pclSummon->m_siTranformStamina = 0;
		}
	}
}

//[지연] - 2010신년이벤트 관련 : 전달된 확률에 따라 포춘쿠키조각 생성
void cltCharServer::GiveFortuneCookiePiece( SI16 siRate, SI16 siCount )
{
	cltServer* pclserver = (cltServer*)pclClient;

	// 신년이벤트 동안에만 포춘쿠키 조각 지급.
	if( true == pclserver->pclEventTimeManager->InEventTime("Fortune_Event", &pclserver->sTime) )
	{
		if( pclClient->IsCountrySwitch(Switch_NewYearEvent_2010) ) 
		{
			// 정해진 확률에 따라 쿠키조각을 생성할지 말지를 결정
			SI16 siChooseValue = 0;
			siChooseValue = rand() % 1000 + 1;

			if ( siChooseValue <= siRate )
			{
				// 확률에 포함됐다면 유저에게 아이템을 준다.
				//GiveItem( 13062, siCount, 0, 0 );

				pclCM->GiveItem( GetID(), 13062, siCount, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_ADDITIONALITEM_GET, GetID() );
			}	
		}
	}
}

// 사냥을 통한 퀘스트 아이템을 지급 합니다.
void cltCharServer::HuntQuestitem(SI32 siCharID, SI32 siMonsterKind)
{
	cltServer* pServer = (cltServer*)pclClient;

	SI32 siQuestClearCondition	= QUEST_CLEAR_COND_HUNT_ITEM;
	SI16 siQuestType			= 0;
	SI16 siQuestUnique			= 0;
	SI16 siPara1				= 0;
	SI16 siPara2				= 0;

	// 사냥으로 아이템획득 중인 퀘스트를 진행중이라면
	if(pclCI->clQuestInfo.IsQuestGoing(siQuestClearCondition, &siQuestType, &siQuestUnique, &siPara1, &siPara2) == true)
	{
		// 퀘스트아이템 획득 관련 퀘스트를 진행중인지 확인합니다.
		HuntQuestItem_Unit* pData = pclClient->m_pHuntQuestItemMgr->FindQuestItem(siQuestUnique, siMonsterKind);

		if(pData == NULL)
			return;

		SI32 siRandValue = rand()%100 + 1;

		if(siRandValue > pData->m_siRandomRate)
			return;

		cltItem clItem;
		ZeroMemory(&clItem, sizeof(clItem));
		clItem.siUnique  =	pData->m_siItemUnique;		
		clItem.siItemNum =	1;

		SI32 rtnvalue	= 0;

		if(InputItem(pclClient->pclItemManager, &clItem,INPUTITEMPERSON_OPTION_WAR, &rtnvalue) == false)
		{
			// 인벤에 빈자리가 없어서 추가할 수 없다. 
			if(rtnvalue == CANADDINV_FAIL_FULL)
			{
				pServer->SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, GetCharUnique());
			}
		}

		//if(0 < siQuestCount )
		//	siQuestItemNum = siQuestCount;

		//IncQuestPara(QUEST_CLEAR_COND_HUNT_ITEM, pData->m_siItemUnique,	siQuestItemNum );
	}
}

