//---------------------------------
// 2003/5/17 김태곤
//---------------------------------

// 서버와 클라이언트 등에서 공토응로 사용하는 Define

#ifndef _COMMONHEADER_H
#define _COMMONHEADER_H

#include <windows.h>
#include <stdio.h>
#include <ddraw.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <io.h>
#include <wingdi.h>
#include <math.h>
#include <commctrl.h>
#include <crtdbg.h>


#include "../lib/Directives.h"


#include "../lib/commonutil.h"
#include "../CommonLogic/TextMgr/TextMgr.h"
#include "../../NLib/NDataTypes.h"
#include "../../NLib/NTCHARString.h"
#include "../../NLib/NArray.h"

#include "../../NLib/NProfile.h"
#include "../../NLib/NBitArray.h"

#include "../GMSystem/GMSectionData.h"

#include "../../NLib/NLua.h"

#include "../../NStatistics/NStatistics.h"

#include "../../NLib/NTech/sdk/nkcore/Include/NkCore.h"
#include "../../NLib/NTech/sdk/nkcore/Include/NkVector.h"
#include "../../NLib/NTech/sdk/nkcore/Include/NkRbTreeMap.h"


#if defined(GOONZU)
	#define NKCOMMON_DEBUG_LIB		"../NLib/NTech/sdk/nkcore/lib/debug/NkCommon.lib"
	#define NKCOMMON_RELEASE_LIB	"../NLib/NTech/sdk/nkcore/lib/release/NkCommon.lib"
#else
	#define NKCOMMON_DEBUG_LIB		"../../NLib/NTech/sdk/nkcore/lib/debug/NkCommon.lib"
	#define NKCOMMON_RELEASE_LIB	"../../NLib/NTech/sdk/nkcore/lib/release/NkCommon.lib"
#endif


#ifdef _DEBUG
	#pragma comment(lib, NKCOMMON_DEBUG_LIB)
#else
	#pragma comment(lib, NKCOMMON_RELEASE_LIB)
#endif

class cGMClient;

//KHY - 0318 - NHNChina는 일단 100레벨 제한이다.
#if _NHN_CHINA 
	#define MAX_EXPTABLE_LEVEL					100			// 경험치 테이블의 최고 단계
	#define MAX_CHARACTER_LEVEL					100			// 캐릭터 레벨의 단계. 
#else
	#define MAX_EXPTABLE_LEVEL					120			// 경험치 테이블의 최고 단계
	#define MAX_CHARACTER_LEVEL					120			// 캐릭터 레벨의 단계. 
#endif

#define MAX_GUILD_LEVEL						100			// 길드 레벨의 단계. 
#define MAX_FAME_LEVEL						100			// 명성등급의 단계.

#define MAX_MACROACTION_SAMENAME_COUNT		1000		// 매크로 액션을 받을때 최대 1000개 까지 동일 케릭 네임으로 파일을 저장 할수 있다 .

typedef NSafeTArray< NSafeTArray<SI64, 3>, MAX_EXPTABLE_LEVEL >		ExpTable;
typedef NSafeTArray< NSafeTArray<SI64, 3>, MAX_FAME_LEVEL >			FameExpTable;

#define MAXORG(level)	(25 + (level) / 2)			// 레벨에 따른 기관의 최대 허용 범위. 

//#define NAME  "군주"
//#define TITLE "군주"

#define ITEMUNIQUE(a)			(a)
#define FOUNIQUE(a)				(a)
#define QUESTUNIQUE(a)			(a)

//-------------------------------------------------------------
// 서비스 지역 ( 16진수로 처리해서 조합이 가능하게 한다 )
//-------------------------------------------------------------
const SI32 ConstServiceArea_Invalid		= 0x80000000;

const SI32 ConstServiceArea_None		= 0x00000000;
const SI32 ConstServiceArea_Korea		= 0x00000001;
const SI32 ConstServiceArea_China		= 0x00000002;
const SI32 ConstServiceArea_Japan		= 0x00000004;	
const SI32 ConstServiceArea_English		= 0x00000008;
const SI32 ConstServiceArea_Taiwan		= 0x00000010;
const SI32 ConstServiceArea_USA			= 0x00000020;
const SI32 ConstServiceArea_NHNChina	= 0x00000040;
const SI32 ConstServiceArea_EUROPE		= 0x00000080;
const SI32 ConstServiceArea_DEV			= 0x00000100;

const SI32 ConstServiceArea_All			= 0x7FFFFFFF;

//-------------------------------------------------------------
// 국가 스위치 - Started by LEEKH
//-------------------------------------------------------------
const SI32 ConstSwitch_TextEncryption	= ConstServiceArea_Japan | ConstServiceArea_Taiwan | ConstServiceArea_China | ConstServiceArea_Korea | ConstServiceArea_English | ConstServiceArea_USA | ConstServiceArea_NHNChina | ConstServiceArea_EUROPE;	//KHY - 0809 - 텍스트 리소스 암호화.
const SI32 ConstSwitch_NewLog			= ConstServiceArea_Taiwan | ConstServiceArea_China | ConstServiceArea_Korea | ConstServiceArea_English | ConstServiceArea_USA | ConstServiceArea_Japan | ConstServiceArea_NHNChina | ConstServiceArea_EUROPE;	// ConstServiceArea_All

enum SWITCH_COUNTRY
{
	Switch_First						,
	//==================================================

	Switch_AddCapitalRemove				,
	Switch_ChatBalloonLine				,
	Switch_EncryptTxtData				,
	Switch_SummonEnolveVillageMoney		,
	Switch_EnchantNoSealing				,
	Switch_DateOverItemNoDestroy		,
	Switch_ManufactureRevitalize		,
	Switch_MakePerfectItem				,
	Switch_DoNotFailedMakeItem			,
	Switch_NotScailed					,
	Switch_ShowBuffToolTip				,
	Switch_WENNYDISASSEMBLELEVEL		,
	Switch_WENNYBOXCHECKLEVEL			,
	Switch_Event_Hunt					,
	Switch_Event_MofuMofu				,
	Switch_ToolTipAutoLine				,
	Switch_DisplayLevelInPannel			,
	Switch_LevelUpAction				,
	Switch_NamingQuest					,
	Switch_RecommendPointPerLevel		,
	Switch_MagicNeedDex					,
	Switch_BaekNyeonSam					,
	Switch_FreshManHelpDialog			,
	Switch_DalilyQuestGrayList			,
	Switch_GachaAvatarCorrect			,
	Switch_Help							,
	Switch_EnableGuildWar				,
	Switch_EnableVillageWar				,
	Switch_StatusBug					,
	Switch_GuildstatusBugFix			,
	Switch_reply						,
	Switch_HappyBeanQuest				,
	Switch_Sound						,
	Switch_UseWebPageItemMall			,
	Switch_ArchangelArchdevil			,
	Switch_AuctionEvent					,
	Switch_GameRoomCouponEvent			,
	Switch_ServerListArray				,
	Switch_WENNYBOXDisable				,
	Switch_WENNYDISASSEMBLEAvata		,
	Switch_HorseAbility					,
	Switch_DyingDelay					,
	Switch_DeleteLuckButton				,
	Switch_DeleteHandButton				,
	Switch_GoStopPokerEvent				,
	Switch_AutoHuntingReport			,
	Switch_MaterialBox					,
	Switch_TeacherLevelReward			,
	Switch_KingGuriEvent				,
	Switch_Health						,
	Switch_FieldObjectPreLoad			,
	Switch_ItemmallNotDisassemble		,
	Switch_GodHandItem					,
	Switch_NewHitEffect					,
	Switch_Fairy						,
	Switch_LevelupUpText				,
	Switch_BossWildBoar					,
	Switch_DonateDlg					,
	Switch_Button6HozoDlg				,
	Switch_20levelparty					,
	Switch_Can5Horse					,
	Switch_DropBookBox					,
	Switch_WennyOldMan_CityhallProfitMoney	,
	Switch_HanGameVIPEvent				,
	Switch_NowComEvent					,
	Switch_RepairMoney					,
	Switch_Thanksgiving_day				,
	Switch_LotteryStockRandom			,
	Switch_PreDeleteChar				,
	Switch_ChristmasEvent				,
	Switch_NoCheckMapIndex_Quest		,
	Switch_WarpInHuntMap				,
	Switch_SaveHorseToHouse				,
	Switch_SantaRaccoonEvent 			,
	Switch_SellToForeignMerchant		,
	Switch_LevelUpNotice				,
	Switch_NewYearEvent					,
	Switch_BasicStructureSet			,
	Switch_VillageWarpTower				,
	Switch_RaccoonGoldeggChange			,
	Switch_Transform					,
	Switch_BlackWarReform				,
	Switch_ChangeFullScreen				,
	Switch_UseDefaultIME				,
	Switch_InstanceDungeonTicket		,
	Switch_NONATIALIASED_QUALITY		,
	Switch_PartyMassageimprovement		,
	Switch_SpaceBox						,
	Switch_HINADOLL						,
	Switch_Puchikomi					,
	Switch_Summon_Ability_Reform		,
	Switch_GeneralMeetingSuggest		,
	Switch_Artifact						,
	Switch_FixedPositionFeastEffect		,
	Switch_ChatEditFilter				,
	Switch_AutoMakeItem					,
	Switch_ClickAndDrop					,
	Switch_TutorialVillage				,
	Switch_PartyHall					,
	Switch_PirateShip					,		// [영훈] 해적선 : 파티인던 스위치
	Switch_PCRoom						,		// [강형] PC방 설정 - 테스트 용
	Switch_UseDayPlusRevitalize			,		// [강형] 기간연장의 돌 개선 - 명품과 호품도 기간연장이 가능
	Switch_CharStatusReform				,		// [진성] 캐릭터 정보창 변경. 2008-3-24	Z
	Switch_SpecialPersonShop			,		// [진성] 밀봉 프리미엄 상점. 2008-3-25	
	Switch_HealthAddChange				,		// KHY - 0325 - 헬스 적용 스위치.
	Switch_Event_Monster_Attack			,		// [진성] 마을 이벤트 - 몬스터 습격. 2008-3-26	
	Switch_BigItemModify				,		// [강형] 대박 시스템 개편
	Switch_MakeItemEXP					,		// [강형] 제조 경험치 개편
	Switch_MarketBuyNew					,		// [진성] 아이템 구입창 새로 변경.
	Switch_GongZoArmorPercent			,		// [강형] 백작 - 방어구 제조 퍼센트 추가
	Switch_Izo_TinTinPercent			,		// [강형] 자작 - 아이템 등록 수수료
	Switch_SummonReform					,		// [진성] 캐릭터 정보창 변경. 2008-3-24
	Switch_FishFarmMineChange			,		// [춘기] 채광,농경,낚시 변경. 2008.04.15
	Switch_FindInfo						,		// [성웅] 정보창 검색 기능 
	Switch_BlackArmyTicket				,		// [성웅] 흑의군단 지령서 국가코드 추가
	Switch_NoPayBack					,		// [성웅] 청약철회문자 추가.
	Switch_PopupCheck					,		// [진성] 팝업창 띄우기.
	Switch_Event_Hunt_Reform			,		// [진성] 마을이벤트 키메라 몬스터 레벨 변경.
	Switch_Notice_Separate				,		// [진성] 공지 분리. 2008-6-2
	Switch_Char_Option					,		// [성웅] 케릭터옵션정보저장.( 2008-06-03 채팅창 정보분리 추가 )
	Switch_Hero_Bronze_Statue			,		// [진성] 영웅의 동상 마을 이벤트. => 2008-6-9
	Switch_Summon_Separate				,		// [진성] 소환수 테이블 분리. 2008-6-10
	Switch_Show_MapName					,		// [영훈] 맵 이동시 맵 이름 보여주기 (2008.06.19)
	Switch_Server_Event					,		// [진성] 서버 이벤트 2008-6-20
	Switch_Artifact_Reform				,		// [진성] 아티펙트 개편. => 2008-7-9
	Switch_DestroyDropItem				,		// [성웅] 아이템 Drop시 아이템 파괴
	Switch_ChangeHouseList				,		// [춘기] 창고 인터페이스 개편 (08.07.10)
	Switch_Summon_Market				,		// [진성] 소환수 거래소. => 2008-7-15
	Switch_MarketConditions 			,		// [희영] 시세확인  2008-07-18
	Switch_Summon_EquipSton				,		// [성웅] 소환수 무기 장착석
	Switch_Summon_StaminaCharge			,		// [춘기] 소환수 스태이터스 추가
	Switch_Guild_DestroyOverMOnth		,		// [성웅] 한달이상 미활동 길드 삭제 
	Switch_Postoffice_Group_Message		,		// [진성] 우체국 단체 메시지 보내기. => 2008-8-4
	Switch_Guild_GuildMaster_Change		,		// [성웅] 길드 마스터 위임 시스템
	Switch_QuestInfoDlg_Renewal			,		// [영훈] 퀘스트 알림창 리뉴얼
	Switch_ShowQuestNotice				,		// [영훈] 퀘스트 공지창
	Switch_Homepage_link				,		// [희영] 홈페이지 링크 시스템.
	Switch_FourLeaf						,		// [진성] 군주 임기별 네잎크로버 설정. => 2008-8-14 
	Switch_SummonHouse					,		// [성웅] 소환수 보관 
	Switch_Gacha_Reform					,		// [진성] 가차 개편. 
	Switch_Mykey						,		// [진성] 나만의 메뉴.	=> 2008-9-3
	Switch_HalloweenEvent				,		// [성웅] 할로윈 이벤트
	Switch_MudangPresent				,		// [희영] 선무당의 선물.
	Switch_Trade_Renewal				,		// [영훈] 무역 개편
	Switch_GlobalItemMall_Limit			,		// [강형] 글로벌 아이템 몰 레벨제한
	Switch_EditWordBreak				,		// [성웅] 에디터 다이얼로그 컨트롤 자동 WORDBREAK적용
	Switch_GameTip						,		// [진성] 게임 팁.
	Switch_Helper						,		// [진성] 도우미.
	Switch_Teacher_Reform				,		// [진성] 스승,제자 개편.
	Switch_SystemMarketSell				,		// [진성] 시스템에서 시장에 장비 판매.
	Switch_IKillU						,		// [성웅] 개인간PVP시스템
	Switch_PVP_League					,		// [영훈] PVP 리그
	Switch_Set_Item_Add					,		// [진성] 세트 아이템 추가.
	Switch_Elixir						,		// [진성] 엘릭서.
	Switch_ValenTineWar					,		// [성웅] 발렌타인데이 전쟁 
	Switch_NewMarket					,		// [진성] 통합마켓.
	Switch_ManufactureInfluenceLuck		,		// [영훈] 제조시에 손재주 대신에 행운으로 변경된다
	Switch_MakeFoodHealEXP				,		// [영훈] 음식/약 제조경험치 변경(스위치가 켜져있어도 음식/약이 아니면 기존 경험치 공식으로)
	Switch_WeaponSkill					,		// [영훈] 전투향상술
	Switch_NewGuildHuntMapWar			,		// [성웅] 새로운 길드 사냥터 신청 2009-03-24
	Switch_PeriodItem					,		// [종호] ItemMall관련 정보 뿌려주던곳 => (BUFF & Service 관련) 기간 아이템 정보로 변경  
	Switch_CarryOverGacha				,		// [영훈] 이월 가챠(Switch_Gacha_Reform 스위치 보다 우선 순위로 처리됨)
	Switch_Avatar_artisan				,		// [종호] 아바타 장인 추가
	Switch_TreasureEvent				,		// [성웅] 보물찾기 이벤트
	Switch_WeddingSystem				,		// [영훈] 결혼 시스템
	Switch_ItemExplain2					,		// [종호] 아이템 설명2
	Switch_BalanceCurrency				,		// [종호] 통화량 조절
	Switch_SoulGuard					,		// [영훈] 수호정령
	Switch_We_Are_Family				,		// [성웅] 결혼 시스템
	Switch_GACHA_RAREITEM_CHANGE		,		// [성웅] 가차 레어아이템 변경 
	Switch_Durability			 		,		// [성웅] 내구도 표시 - 중국만 사용 하기 위해서 
	Switch_10MonthEvent_RacoonDodge		,		// [성웅] 라쿤 피하기 이벤트 [ 10월 이벤트 ]
	Switch_NewDurability			 	,		// [강형] 신 내구도 시스템 - 기존 시스템 코드를 활용하여 개발함.
	Switch_BokBulBok					,		// [지연] 복불복 게임. (2009.08.03)
	Switch_GawiBawiBo					,		// [종호] 축제-가위바위보
	Switch_SummonTramsform				,		// [진성] 소환수 변신.
	Switch_Dormancy						,		// [기형] 휴면 계정 시스템.
	Switch_Festival_Food				,		// [진성] 축제 음식.
	Switch_SkillBook					,		// [진성] 스킬북.
	Switch_CharHouse					,		// [영훈] 캐릭터 보관소
	Switch_RaccoonEvent_Change_Goonzu	,		// [성웅] 라쿤이벤트 군주 이벤트로 변경 2009-10
	Switch_BattleRoyal					,		// [기형] 배틀로얄
	Switch_NewYearEvent_2010			,		// [지연] 2010신년이벤트.
	Switch_PartyQuest_PartyMatching		,		// [지연] 초보자 파티 퀘스트 시스템(파티매칭).
	Switch_ValentineDayEvent			,		// [기형] 발렌타인데이이벤트
	Switch_Change_manufacture_request_interface,// [성웅] 제조 의뢰 인터페이스 개선
	Switch_PKHuntMap_Change_Info,				// [성웅] pk 사냥터 사양 변경 
	Switch_Go_RaccoonWorld,						// [성웅] 라쿤월드 이동 변경 
	Switch_LevelLimitBox,						// [성웅] *중국용* 레벨제한 보상 상자 
	//==================================================
	Switch_Last,
	Switch_Count = Switch_Last - 1		,
};

//-------------------------------------------------------------
// 사용언어
//-------------------------------------------------------------
const SI16 ConstLanguage_English	=	1;
const SI16 ConstLanguage_China		=	2;
const SI16 ConstLanguage_Japan		=	3;
const SI16 ConstLanguage_Korea		=	4;
const SI16 ConstLanguage_USA		=	5;

//-------------------------------------------------------------
// 마스터 모드
//-------------------------------------------------------------
const SI32 ConstMaster_Korea		=	1;
const SI32 ConstMaster_Japan		=	2;
const SI32 ConstMaster_Global		=	3;
const SI32 ConstMaster_Taiwan		=	4;
const SI32 ConstMaster_USA			=	5;

//-------------------------------------------------------------
// FPS
//-------------------------------------------------------------
const SI16 ConstFrameRate_Low		=	20;
const SI16 ConstFrameRate_High		=	40;


#define MAX_SERVER_NUMBER						4	// 하나의 어카운트 DB를 통해 서비스 되고 있는 서버의 수. 
													// 서버끼리 각각 다른 siServerUnique 를 가지고 있어야 한다. ex) 1,2,3,4 ..
													// 아이템몰을 통해 아이템을 선물할때 각 서버를 구분한다.

#define NOOBJECT								0
#define OBJECT1									1


#define NEW_SELECTED_DELAY						6
#define MOUSE_OVER_DELAY						1

#define MAX_WAIT_STEP_NUMBER					16	// 캐릭터가 가질 수 있는 최대 정지 모션 프레임의 수 
#define MAX_WAIT_TYPE							2   // 대기시 취하는 애니메이션의 최대 수 .

#define MAX_MOVE_STEP_NUMBER					10	// 캐릭터가 가질 수 있는 최대 이동 모션 프레임의 수 
#define MAX_DYING_STEP_NUMBER					16	// 캐릭터가 가질 수 있는 최대 사망 모션 프레임의 수 
#define  MAX_ATTACK_STEP_NUMBER					16	// 캐릭터가 가질 수 있는 최대 공격 모션 프레임의 수 

#define GAMECOLOR_RED						69
#define GAMECOLOR_YELLOW					70
#define GAMECOLOR_GREEN						68

//============================================================
// DIALOG BOX COLOR 정의 
//============================================================
#define COLOR_DIALOG_YELLOW					RGB(248, 255, 199)
#define COLOR_DIALOG_GREEN					RGB(136, 251, 148)
#define COLOR_DIALOG_RED					RGB(226, 114, 150)
#define COLOR_DIALOG_LIGHTRED				RGB(255, 167, 179)
#define COLOR_DIALOG_BLUE					RGB(15,  167, 240)
#define COLOR_DIALOG_BLACK					RGB( 0, 0, 0 )
#define COLOR_DIALOG_WHITE					RGB(255, 255, 255)
#define COLOR_DIALOG_LIGHTBLUE				RGB(143, 202, 233)
#define COLOR_DIALOG_WHITEBLUE				RGB(238, 238, 255)
#define COLOR_DIALOG_GRAY					RGB(224,213,213)
#define COLOR_DIALOG_DLG_BLUE				RGB(205, 205, 205)
#define COLOR_DIALOG_STATIC_BLUE			RGB(226, 222, 207)
#define COLOR_DIALOG_READONLYTEXT			RGB(170, 110, 95)
//============================================================

#define DOUBLE_CLICK_DELAY						300

// 방향 정의 						
#define SOUTH              						1
#define SW                 						2
#define WEST               						4
#define NW										8
#define NORTH               					16
#define NE                  					32
#define EAST                					64
#define SE                  					128 
						
#define SSW										1000						
#define WWS 									1001						
#define WWN 									1002						
#define NNW 									1003						
#define NNE 									1004						
#define EEN 									1005						
#define EES 									1006
#define SSE 									1007


//----------------------------------------------------
//    캐릭터  속성 
//----------------------------------------------------
#define ATB_MOVE							0x00000001		// 움직이는 캐릭터 속성 
#define ATB_HERO							0x00000002		// 조합형캐릭터 속성.  
#define ATB_ATTACK							0x00000004		// 공격 속성
#define ATB_SUMMONSTAMINASTATIC				0x00000008		// 소환수의 스태미너 속성.
#define ATB_WEAKENEMYNOATTACK				0x00000010  	// 약한 적은 공격하지 않는 속성. 
#define ATB_FISH							0x00000020  	// 낚시 가능. 
#define ATB_NOJJIM							0x00000040		// 찜되지 않는 캐릭터. 
//#define ATB_MINRANGE						0x00000080		// 접근전 불가- 사용안하기 때문에 데일리퀘스트2를 위해서 변경
#define ATB_DAILYQUEST2						0x00000080		// 접근전 불가
#define ATB_HORSE							0x00000100		// 말류. 
#define ATB_SYSTEMNPC						0x00000200		// SystemNPC
#define ATB_SELFBOMB						0x00000400		// 자폭기능
#define ATB_WAITSELFBOMB					0x00000800		// 정지시 자폭기능
#define ATB_NONPCLIST						0x00001000		// NPC리스트에 포함되지 않는다. 
#define ATB_COWORK							0x00002000		// 주변 동료들과 협동공격한다. 
#define ATB_MONSTER							0x00004000		// 몬스터
#define ATB_GOD								0x00008000		// 성황신이 될수있는 캐릭터 
#define ATB_DEFAULTGOD						0x00010000		// 성황신중 가장 기본이 되는 캐릭터 
#define ATB_DEFAULTCASTLE					0x00020000		// 성문중 가장 기본이 되는 캐릭터 
#define ATB_DAILYQUEST						0x00040000		// DailyQuest로 가능한 캐릭터
#define ATB_WARMONSTER						0x00080000		// 전쟁중에만 나오는 몬스터 - 몬스터 표시창에 표시 불가
#define ATB_EVENTXBOX						0x00100000		// EVENT 속성을 갖고 있다.
#define ATB_CLONE							0x00200000		// 분신술을 쓰도록 한다.
#define ATB_DEFAULTSUMMON					0x00400000		// 소환수가 될수 있는지 설정한다..
#define ATB_HIREABLE						0x00800000		// 마을에서 고용가능하다. 
#define ATB_BOSS							0x01000000		// 보스급 몬스터이다.
#define ATB_FARM							0x02000000		// 농사짓기가 가능하다. 
#define ATB_DAMAGELIMIT						0x04000000		// 피격시 데미지에 한계가 있다. 
#define ATB_MINE							0x08000000		// 채굴이 가능하다.
#define ATB_NOHEALTHBAR						0x10000000		// 체력바를 안 보여준다.
#define ATB_NOICE							0x20000000		// 어는 확율이 10분의 1로 줄어든다.
#define ATB_TRANSFORM						0x40000000		// [수정 : 황진성 2007. 12. 28 => 변신 ATB]
#define ATB_EVENT							0x80000000		// 이벤트용 몬스터

#define SERVICEAREA_ATB_KOREA				0x00000001		// 한국버전에 사용되는 캐릭터인지
#define SERVICEAREA_ATB_CHINA				0x00000002		// 중국버전에 사용되는 캐릭터인지
#define SERVICEAREA_ATB_JAPAN				0x00000004		// 일본버전에 사용되는 캐릭터인지
#define SERVICEAREA_ATB_ENGLISH				0x00000008		// 영어버전에 사용되는 캐릭터인지
#define SERVICEAREA_ATB_TAIWAN				0x00000010		// 타이완버전에 사용되는 캐릭터인지
#define SERVICEAREA_ATB_USA					0x00000020		// USA버젼에서 사용되는 캐릭터인지
#define SERVICEAREA_ATB_NHNCHINA			0x00000040		// NHN_China버젼에서 사용되는 캐릭터인지
#define SERVICEAREA_ATB_EUROPE				0x00000080		// 유럽버젼에서 사용되는 캐릭터인지


// UI08 이므로 0x00000008까지만 사용 가능
#define GMMODE_ATB_NONE						0		// 일반모드
#define GMMODE_ATB_GMSHOW					1		// 운영자임을 나타내는 모드( [GM] 표시 )
#define GMMODE_ATB_HIDE						2		// 하이드모드
#define GMMODE_ATB_WARMVP					3		// 전쟁 MVP [일반유저도 가능]
#define GMMODE_ATB_BUFF						5		// [추가 : 황진성 2007. 11. 27 운영자 모드이고 주변 캐릭에게 버프 적용]

//------------------------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------------------------
#define TRANSPARENT_MODE_NORMAL					1
#define TRANSPARENT_MODE_OLDTRANS				2
#define TRANSPARENT_MODE_HALFTRANS				3
#define TRANSPARENT_MODE_SCREEN					4
#define TRANSPARENT_MODE_MULTIPLY				5
#define TRANSPARENT_MODE_ADD					6
#define	TRANSPARENT_MODE_ALPHA					7

//------------------------------------------------------------------------------------------------
// 신분 속성 - MAX_KINDINFO_NUMBER 크기가 420->500 밖에 안되기 때문에 단지 카인드만(속성등은같음) 다를경우 리소스에 새롭게 추가하지 않고 해당 카인드에 IDENTITY 값만 따로 지정해서 사용하면 됨.
//------------------------------------------------------------------------------------------------
#define IDENTITY_CASTLE							1			// 신분이 성벽 인지
#define IDENTITY_VILLAGEGOD						2			// 신분이 성황신 인지
#define IDENTITY_VILLAGEGOD_SUMMON				3			// 신분이 마을의 성황신이 소환한 소환수 인지
#define IDENTITY_PERSON_SUMMON					4			// 신분이 개인이 소환한 소환수 인지 
#define IDENTITY_VILLAGEHUNT					5			// 신분이 마들단위 사냥용 몬스터 
#define IDENTITY_BLACKARMY						6			// 흑의군단 몬스터
#define IDENTITY_VILLAGE_KINGMONUMENT			7			// 마을 수호상
#define IDENTITY_BLACKWAR						8			// 흑의군단 몬스터
#define IDENTITY_MOFUMOFUEVENT					9			// 모후모후이벤트 몬스터
#define IDENTITY_INSTANCEMAP					10			// 인스턴스맵 몬스터
#define IDENTITY_MONSTER_ATTACK_EVENT			11			// [진성] 마을 이벤트 - 몬스터 습격 => 2008-3-26
#define IDENTITY_QUEST							12			// 퀘스트용 몬스터
#define IDENTITY_SOULBOUND						13			// 귀속몬스터 (소환된 사람만 공격할수있다)
#define IDENTITY_SOULGUARD						14			// [영훈] 수호정령_090525 : 
#define IDENTITY_TREASURE_EVENT					15			// [성웅] 트레저 이벤트로 생성된 몬스터 2009.07.01
#define IDENTITY_RACOONDODGE_EVENT				16			// [성웅] 6월이벤트 라쿤피하기 이벤으로 생성된 몬스터 2009.08.11
#define IDENTITY_BOKBULBOK_EVENTMONSTER			17			// [지연] 복불복이벤트 : 일반 몬스터 2009.08.23
#define IDENTITY_BOKBULBOK_KEYMONSTER			18			// [지연] 복불복이벤트 : 키 몬스터 2009.08.23
#define IDENTITY_BOKBULBOK_ONEKILLMONSTER		19			// [지연] 복불복이벤트 : 원킬 몬스터 2009.08.23
#define IDENTITY_SOULGUARD_SUMMONPUMKIN			20			// [성웅] 소울가드 펌킨이 소환한 몬스터 2009-8-28
#define IDENTITY_BOKBULBOK_ITEMMONSTER			21			// [지연] 복불복이벤트 : 선물 몬스터
#define IDENTITY_BATTLEROYAL_MONSTER			22			// [기형] 배틀로얄 몬스터
#define IDENTITY_GMCREATE_MONSTER				23			// [춘기] /CMT 명령어로 생성한 몬스터
#define IDENTITY_GMCREATE_MONSTER				23			// [춘기] /CMT 명령어로 생성한 몬스터
#define IDENTITY_GIANTRACCOONRESURRECTEVENT		24			// [진성] 자이언트 라쿤 부활 축제 이벤트. 

//------------------------------------------------------------------------------------------------
// 방어 속성		
//------------------------------------------------------------------------------------------------
#define DEFENCEATB_HUMAN    					1			// 일반 병사 
#define DEFENCEATB_SWORD    					2			// 일반 보병 
#define DEFENCEATB_ARMOUR   					3			// 갑옷 
#define DEFENCEATB_HORSE    					4			// 기병 
#define DEFENCEATB_STONE    					6			// 건물 



//----------------------------------------
// 캐릭터 명령 
//----------------------------------------
#define MAX_ORDER_NUMBER				20

#define ORDER_WAIT    					1
#define ORDER_STOP    					2 
#define ORDER_FORCESTOP    				3					// 클라이언트에 전달되어져야할 강제 STOP	 
#define ORDER_MOVE    					4					// 단순이동 
#define ORDER_ATTACK  					5					// 단순 공격 
#define ORDER_ATTACK_SUMMON				6					// 소환수의 공격.  
#define ORDER_DIE     					7
#define ORDER_DEAD    					8
#define ORDER_MAGIC						9
#define ORDER_REVIVE					10
#define ORDER_STRAIGHTMOVE				11					// 직선이동. 
#define ORDER_FISH						12					// 낚시 하기. 
#define ORDER_FARM						13					// 농사짓기. 
#define ORDER_MAGIC_SUMMON				14					// 소환수의 마법 공격
#define ORDER_MINE						15					// 채굴
#define ORDER_MOVE_SUMMON				16					// 소환수의 이동
#define ORDER_SITDOWN					17					// 앉기
#define ORDER_ATTACK_CLIENT				18					// 단순공격( 판정요청을 클라->서버로 보낸다 )
#define ORDER_SPECIAL_ACTION			19					// 과금 소환펫 - 특수 동작


#define MAX_HORSE_NAME			12	// 말 이름의 길이. 
#define MAX_SUMMON_NAME			12	// 소환수 이름의 길이. 
#define MAX_SOULGUARD_NAME		12	// 수호정령 이름의 길이

#define MAX_SOULGUARD_HOUSE_NUM	10	// 수호정령 보관소 최대 갯수

#define MAX_RENT_FEE			1000000
#define MAX_RENT_PERIOD			9

// 파일 이름 길이 
#define FILE_NAME_SIZE							128

#define NORMAL_TEXT_COLOR	RGB(250, 250, 250)
#define BLANK_TEXT_COLOR	RGB(10, 10, 10)


#define MAX_ORDER_QUE							50

#define MAX_CHAR_NUMBER							20000			// 게임에 등장할 수 있는 최대의 캐릭터 갯수 

#ifdef _CHINA
	#define MAX_PERSON_NUMBER						3000
	#define MAX_NPC_NUMBER							11000	// 건물과 캐릭터 포함함.
	#define MAX_INSTANCE_NPC_NUMBER					5500		// 인스턴스 던전 NPC
#else
	#define MAX_PERSON_NUMBER						3000
	#define MAX_NPC_NUMBER							11000	// 건물과 캐릭터 포함함.
	#define MAX_INSTANCE_NPC_NUMBER					5500		// 인스턴스 던전 NPC
#endif
	
#define MAX_KIND_NUMBER								500		// 총 캐릭터의 종류 갯수 420->500 눈의 여왕 들어가면서 눈의 여왕이 420으로 꽉참
//#define MAX_KIND_PER_PLAYER						10		// 주인공 캐릭터의 종류 갯수(에서 +1임! 10부터 NPC)
#define MAX_SORT_LEVEL								2000

#define MAX_BULLET_NUMBER						1004
#define MAX_SMOKE_NUMBER						1500

#define MAX_PLAYER_NAME							20	// 사용자가 가질 수 있는 최대 이름 크기.
#define MAX_SERVER_NAME							20	// 서버가 가질 수 있는 최대 이름 크기.


#define MAX_CHAR_PER_USER						3	// 한 유저당 가질 수 있는 캐릭터의 수. 
#define MAX_CHAR_HOUSE_PER_USER					12	// 한 유저당 가질 수 있는 캐릭터보관수의 갯수
#define MAX_TOTAL_CHAR_PER_USER					((MAX_CHAR_PER_USER)+(MAX_CHAR_HOUSE_PER_USER))

#define MAX_VILLAGE_NUMBER						100	// 게임에 마을이 몇개나 들어가는가 ?
#define VILLAGE_NONE							0	// 0 번마을( 마을 없음을 의미 ) 	

#define MAX_RESIDENTS_PER_VILLAGE				300 // 한 마을의 최대 주민수

#define MAX_INVEST_NUMBER						100	// 기억해야 하는 마을의 투자자 베스트 10 	

#define	MAX_CONSTRUCTION_NUM					10	// 한 마을에 지을 수 있는 건물의 최대수. 

#define MAX_HEAD_CHAT_TEXT_SIZE					128

#define MAX_CHILDINFO_NUMBER					10	// 제자 정보를 한번에 얻어올 수 있는 최대 수. 

#define WAR_REWARD_VILLAGE_NUMBER				20	// 왜구 전쟁시 20위 마을까지 소팅해서 보상한다. 

#define	MAX_CHAT_DATA_LENGTH					100	// 한글 50 자

#define MAX_PERSONAL_SHOP_TEXT_SIZE				256	// 한글 30자 개인상점 banner 

#define MAX_BLOCKREASON_SIZE					200 // 사용자 블럭시 그 사유의 텍스트 사이즈. 
#define MAX_BLOCKLOG_NUM						10	// 블럭 로그를 가져올때 최대 가져올 수 있는 갯수

#define MAX_SCROLL_SUMMON_PER_KIND				2			// 한종류의 소환수에 바를 수있는 최대 부적수

#define MAX_HORSE_LIFE							3000	// 갈색마 수명
#define MAX_SPECIALHORSE_LIFE					5000	// 특수마 수명
#define MAX_UNLIMITEDHORSE_LIFE					30001	// 수명 없음
//KHY - 0622 - 군주S 초보자용  망아지 추가. - 0820 - 수정.
#define MAX_FOAL_LIFE							1500	//3000	// 망아지 수명
//PCK - 이벤트 용 호랑이 수명
#define MAX_TIGER2_LIFE							300
#define MAX_GRAYWOLF_LIFE						3000	// 회색늑대 수명

#define MAX_USERLIST_NUM						50		// 최대 보낼수 유저 리스트의 숫자[국가별]

#define MAX_FRIEND_GROUPNAME					20

#define MAX_CLIENT_COMMAND_SIZE					128

#define BASIC_ITEMPRICE_DEFAULT					20
//PCK - 백호 수명
#define MAX_WHITETIGER_LIFE						1000
#define MAX_WHITEHORSE_TEST_LIFE				300		// 체험용 백마 : 손성웅-2009.03.17
//-----------------------------------
// 감옥위치 정보 
//-----------------------------------
#define PRISON_MAPINDEX	0
#define PRISON_X		283
#define PRISON_Y		672


// PC인가 ?
#define IsPC(x)			(x > 0 && x < MAX_PERSON_NUMBER)
// InstanceNPC인가?
#define IsInstanceNPC(x)	(x >= (MAX_PERSON_NUMBER ) && x < (MAX_PERSON_NUMBER + MAX_INSTANCE_NPC_NUMBER))
// NPC인가 ?
#define IsNPC(x)		(x >= (MAX_PERSON_NUMBER + MAX_INSTANCE_NPC_NUMBER) && x < MAX_CHAR_NUMBER )

#define NETWORK_SERVER		1
#define NETWORK_CLIENT		2

enum eGameMode{
	GAMEMODE_SERVER	= 1	,
	GAMEMODE_CLIENT		,
	GAMEMODE_MAPEDIT
};

enum eRunMode {
	// 이 순서가 변경되면 안됩니다
	RUNMODE_DEBUG = 1,
	RUNMODE_TEST,
	RUNMODE_BETA,
	RUNMODE_REAL,		// 바꾸지 않고 뒤에 추가한다.

	RUNMODE_INSIDE		// 내부 리얼 테스트용
};

#define BY_PLAYER     0		
#define BY_COMPUTER   1

#define MIN_ITEM_PRICE	20			// 아이템 가격의 최소값(이 이하로는 떨어지지 않는다.) 

#define MAX_MATERIAL_NUMBER	10								// 아이템 재료 종류 최대값
#define MAX_MATERIAL_NUMBER_FOR_DB	MAX_MATERIAL_NUMBER + 2	// 아이템 재료 종류 최대값 Database 용 - 성공기원석용 공간 하나 추가
															//KHY - 1211 - 과금상품 - 만능 도구 - 만능 도구 공간 추가.

#define FATHER_LEVEL	20
#define NEWFATHER_LEVEL 50

#define INIT_LEVEL		10			// 초기화 되는 레벨 

#define INIT_LEVEL_SECOND		30			// 두번째 초기화 되는 레벨 


#define PERSON_SUMMON_ATTACKBONUS_PERCENT 10

//--------------------------
// 신체 기관 
//--------------------------
#define ORG_1			1			// 소화계 
#define ORG_2			2			// 순환계 
#define ORG_3			3			// 호흡계 
#define ORG_4			4			// 신경계 


#define MAX_LEVEL_FOR_BEGINNERMAP	10		// 초보자 사냥터 출입을 위한 최대 레벨 

//----------------------------------------
// 산타작업장 입장 레벨 제한
//----------------------------------------

#define MAX_LEVEL_FOR_SANTAFACTORY_102	30		
#define MAX_LEVEL_FOR_SANTAFACTORY_123	60
#define MAX_LEVEL_FOR_SANTAFACTORY_124	100

//----------------------------------------
// 직급의 타입 
//----------------------------------------
#define MAX_RANKTYPE_NUMBER	20

#define RANKTYPE_CITYHALL				1		// 대행수
#define RANKTYPE_BANK					2		// 전장행수 
#define RANKTYPE_STOCK					3		// 여각행수 
#define RANKTYPE_MARKET					4		// 객주행수
#define RANKTYPE_HOUSE					5		// 시전행수
#define RANKTYPE_HUNT					6		// 수렵장행수 
#define RANKTYPE_POSTOFFICE				7		// 우체국행수
#define RANKTYPE_PORT					8		// 포구행수
#define RANKTYPE_HORSEMARKET			9		// 사복시행수
#define RANKTYPE_REALESTATEMARKET		10		// 거간행수
#define RANKTYPE_SUMMONMARKET			11		// 장예원행수
#define RANKTYPE_SHIPMARKET				12		// 전함사행수 
#define RANKTYPE_LAND					13		// 농장행수  
#define RANKTYPE_FEAST					14		// 내자시행수
#define RANKTYPE_SUMMONHEROMARKET		15		// 비변사행수
#define RANKTYPE_MINE					16		// 광산행수
#define RANKTYPE_GUILD					17		// 상단행수 		
//#define RANKTYPE_NEWMARKET			18		// [진성] 통합마켓 2009-1-5 
#define RANKTYPE_NEWMARKET				18		// [진성] 통합마켓 2009-1-5 

#define CITYHALL_UNIQUE				1		// 관청
#define BANK_UNIQUE					10		// 전장 
#define STOCK_UNIQUE				20		// 여각 
#define MARKET_UNIQUE				40		// 객주
#define HOUSE_UNIQUE				50		// 시전(창고)
#define HUNT_UNIQUE					60		// 수렵장 
#define POSTOFFICE_UNIQUE			70		// 우체국
//#define PORT_UNIQUE					80		// 포구
#define HORSEMARKET_UNIQUE			90		// 사복시
#define REALESTATEMARKET_UNIQUE		100		// 거간
#define SUMMONMARKET_UNIQUE			110		// 장예원
//#define SHIPMARKET_UNIQUE			12		// 전함사 
#define LAND_UNIQUE					130		// 농장  
#define FEAST_UNIQUE				140		// 내자시
#define SUMMONHEROMARKET_UNIQUE		150		// 비변사
#define MINE_UNIQUE					160		// 광산
#define GUILD_UNIQUE				170		// 상단 		
#define NEWMARKET_UNIQUE			180		// [진성] 통합마켓 2009-1-5 




// 지도의 최대 개수. 
#define MAX_MAP_NUMBER					400

#define MAX_CLONEMAP_TYPE				10		// // 복사맵(원본) 의 최대 개수
#define CLONEMAP_NUM					10		// 한 타입당 복사맵의 최대 갯수

#define MAX_DUR_FOR_TUNE	200		// 개조에 필요한 최대 내구도(이 수치 이하이어야 한다.) 

//------------------------------------
// 마을 수익 관련 정의 
//------------------------------------
#define VILLAGE_PROFIT_RATE_FOR_MERCHANT	5	// 상인의 거래 결과중 몇 %를 마을 수익으로 집계하는가. 
#define VILLAGE_PROFIT_RATE_FOR_DAILYQUEST	5	// 모병관 퀘스트  결과중 몇 %를 마을 수익으로 집계하는가. 
#define VILLAGE_PROFIT_RATE_FOR_NPCREPAIR	5	// 장영실 수리 결과중 몇 %를 마을 수익으로 집계하는가. 
#define VILLAGE_PROFIT_FOR_WENNYOLDMAN		5000
#define VILLAGE_PROFIT_FOR_FANPRIEST		2000
#define VILLAGE_PROFIT_FOR_PERSONALSHOP     5000
#define VILLAGE_PROFIT_FOR_INVESTMENT		5000 // 투자상담가(봉이 김선달)
#define VILLAGE_PROFIT_RATE_FOR_DAILYQUEST2	5	// 모병관 퀘스트  결과중 몇 %를 마을 수익으로 집계하는가. 

#define MAX_EVENT_NUMBER					8		// 이벤트의 개수. 
#define MIN_LEVEL_FOR_HORSE					15		// 말을 소유하기 위한 최소 레벨 

//--------------------------------
// 지도의 계절 
//--------------------------------
#define SEASON_SPRING		0
#define SEASON_AUTUMN		1
#define SEASON_WINTER		2


//------------------------------
// 마을의 타입 
//------------------------------
#define VILLAGETYPE_SPRING_NORMAL		1
#define VILLAGETYPE_AUTUMN_NORMAL		2
#define VILLAGETYPE_WINTER_NORMAL		3

//------------------------------
// 마을 이벤트 건물 
//------------------------------
#define EVENT_STRUCTURE_TREE				   1
#define EVENT_STRUCTURE_CHRISTMASTREEBASE	  10
#define EVENT_STRUCTURE_NEWYEARTREEBASE		  11
#define EVENT_STRUCTURE_HERO_BRONZE			   2		//[진성] 영웅의 동상. => 2008-6-9
#define EVENT_STRUCTURE_HALLOWEEN			   3		//[성웅] 할로윈 이벤트 잭오랜턴 기본 호박
#define EVENT_STRUCTURE_CHRISTMASTREE		1001
#define EVENT_STRUCTURE__PCAKE				3001
#define EVENT_STRUCTURE__PCHAMPAGNE			3002
#define EVENT_STRUCTURE__PBARBECUE			3003
#define EVENT_STRUCTURE__PGARLAND			3004
#define EVENT_STRUCTURE__PICESTATUE			3005
#define EVENT_PVP_LEAGUE					3006		//[성웅] PVP_League 아이템 획득
#define EVENT_STRUCTURE_WORLDCHRISTMASTREE	4001		// [춘기] 엔펠리스 앞에 세워지는 크리스마스 트리

//------------------------------
// 수렵장 타입 
//------------------------------
#define HUNTTYPE_ALL		1

// 명칭
#define MAX_NAMINGQUEST_INDEX	15
#define MAX_NAMINGQUEST_LEVEL	15

//------------------------------
// 이벤트 타입 -  //KHY - 0906 - 게임방 이벤트 쿠폰.
//------------------------------
#define GAMEROOM_COUPON_EVENT		1
#define AUCTION_COUPON_EVENT		2
#define GOSTOP_POKER_EVENT			4
#define HAN_GAME_VIP_EVENT			5
#define NOW_COM_EVENT				6
#define SUPER_ROOKIE_LEVELUP_EVENT	7


//------------------------------
// [영훈] 출석 관련 이벤트
//------------------------------
enum ATTEND_EVENTTYPE 
{
	ATTEND_EVENTTYPE_NONE			= 0 // 쓰지않음
	,ATTEND_EVENTTYPE_ATTENDANCE	= 1	// 출석체크 이벤트
	,ATTEND_EVENTTYPE_PCROOM			// PC방 네잎클로버 지급
	,ATTEND_EVENTTYPE_SEASON2			// 시즌2 오픈기념 이벤트

	//---------------------------------
	// 새로운 타입은 이 위에 해주세요
	//---------------------------------
	,ATTEND_EVENTTYPE_MAX				// 이벤트 타입은 위
};

///////////////////////////////// 숫자값을 문자열로 취급해서 해당 문자열과 같으면 숫자값을 반환한다////////////////////////////////////
#define COMPARE_TEXT_WITH_VALUE( text, value ) \
{	if ( 0 == _tcscmp(text, #value) )	return value;	}
///////////////////////////////// 숫자값을 문자열로 취급해서 해당 문자열과 같으면 숫자값을 반환한다////////////////////////////////////

// [영훈] 선거 관련
const SI32 Const_Max_Candidate		= 21;		// 군주 후보 지지자 이름
const SI32 Const_Max_Maintenance	= 256;		// 지지 사유

// [영훈] 초보자 마을 - 앙카란
const SI32 Const_Beginner_Village		= 1;	// 초보자 마을 유니크
const SI32 Const_BV_Max_Resident_Level	= 40;	// 초보자 마을에 가입할 수 있는 최대 LV
const SI32 Const_BV_StockDividend_Level	= 30;	// 초보자 마을에 있을때 주주배당을 받는 레벨
const SI32 Const_BV_Max_Resident_Num	= 1500;	// 초보자 마을에 가입할 수 있는 최대 주민 수

const SI32 Const_Attendance_Modulation_Day = 28;	// [영훈] 출석일수는 28일 주기로 0으로 초기화 된다

const SI32 Const_Passport_Issue_Cost_Acu	= 5;	// [영훈] 무역관련 여권 발급비용(ACU)
const SI32 Const_Passport_Extend_Cost_Acu	= 3;	// [영훈] 무역관련 여권 연장비용(ACU)

//----------------------------------------
// [영훈] 이벤트 On/Off변수관련
//----------------------------------------
enum EVENT_TOGGLE_SWITCH
{
	EVENT_TOGGLE_SWITCH_FISHINGEVENT = 0,	// 낚시 이벤트
	EVENT_TOGGLE_SWITCH_SYSTEMBUY,			// 시스템 구매


	//------------------------------------
	// 새로운 값은 이 위로 적어주세요
	//------------------------------------
	EVENT_TOGGLE_SWITCH_MAX
};

//----------------------------------------
// [영훈] PVP_LEAGUE 등급관련(혹시 중간에 늘어날것을 대비해서 각 5씩 증가되는 값을 갖는다)
//----------------------------------------
enum PVP_LEAGUE_GRADE
{
	PVP_LEAGUE_GRADE_NONE	= 0,	// 등급이 없음(PVP 리그전을 하지 않았음)

	PVP_LEAGUE_GRADE_9		= 5,
	PVP_LEAGUE_GRADE_8		= 10,
	PVP_LEAGUE_GRADE_7		= 15,
	PVP_LEAGUE_GRADE_6		= 20,
	PVP_LEAGUE_GRADE_5		= 25,
	PVP_LEAGUE_GRADE_4		= 30,
	PVP_LEAGUE_GRADE_3		= 35,
	PVP_LEAGUE_GRADE_2		= 40,
	PVP_LEAGUE_GRADE_1		= 45,

	PVP_LEAGUE_GRADE_MAX
};

const SI32 Const_PVP_League_Default_Grade = PVP_LEAGUE_GRADE_6;

//------------------------------
// 공격 속성 타입  by tea-yang
//------------------------------
// 홀수는 공격속성, 짝수는 방어속성임
// [영훈] define에서 enum으로 변경
enum ENCHANT_TYPE
{
	 ENCHANT_TYPE_DEFAULT		= 0	// 00 아무속성도 안 붙어있음
	,ENCHANT_TYPE_FIRE_A			// 01 불 공격속성
	,ENCHANT_TYPE_FIRE_D			// 02 불 방어속성
	,ENCHANT_TYPE_WATER_A			// 03 물 공격속성
	,ENCHANT_TYPE_WATER_D			// 04 물 방어속성
	,ENCHANT_TYPE_WIND_A			// 05 바람 공격속성
	,ENCHANT_TYPE_WIND_D			// 06 바람 방어속성
	,ENCHANT_TYPE_GROUND_A			// 07 땅 공격속성
	,ENCHANT_TYPE_GROUND_D			// 08 땅 방어속성
	,ENCHANT_TYPE_FIRE_WATER_A		// 09 불 & 물 공격속성
	,ENCHANT_TYPE_FIRE_WATER_D		// 10 불 & 물 방어속성
	,ENCHANT_TYPE_FIRE_WIND_A		// 11 불 & 바람 공격속성
	,ENCHANT_TYPE_FIRE_WIND_D		// 12 불 & 바람 방어속성
	,ENCHANT_TYPE_FIRE_GROUND_A		// 13 불 & 땅 공격속성
	,ENCHANT_TYPE_FIRE_GROUND_D		// 14 불 & 땅 방어속성
	,ENCHANT_TYPE_WATER_WIND_A		// 15 물 & 바람 공격속성
	,ENCHANT_TYPE_WATER_WIND_D		// 16 물 & 바람 방어속성
	,ENCHANT_TYPE_WATER_GROUND_A	// 17 물 & 땅 공격속성
	,ENCHANT_TYPE_WATER_GROUND_D	// 18 물 & 땅 방어속성
	,ENCHANT_TYPE_WIND_GROUND_A		// 19 바람 & 땅 공격속성
	,ENCHANT_TYPE_WIND_GROUND_D		// 20 바람 & 땅 방어속성
};


//-----------------------------------------------------------------------------
// Data x가 값이 들어있는지 없는지 검사 있으면 true(TRUE) , 없으면 false(FALSE)
//-----------------------------------------------------------------------------
#define DATA_TO_BOOL(x)				(x!=0)?(x>0):false?true:false
#define DATA_TO_TYPE_BOOL(x)		(x!=0)?(x>0):FALSE?TRUE:FALSE

// TradeServer - SJY
#define MAX_TRADESERVER_ORDER		1 // 최대 주문수
#define MAX_LOWLEVEL_LIST_NUMBER	21 // 20미만 레벨 유저

//-----------------------------------------------------------------------------
// 공조가 사용할 정보들

enum
{
	GONGZO_SKILL_START = 1 ,
	//=====================================================
	
	GONGZO_SKILL_NONE  = 0,
	GONGZO_SKILL_SWORD = GONGZO_SKILL_START ,
	GONGZO_SKILL_SPEAR ,
	GONGZO_SKILL_STAFF ,
	GONGZO_SKILL_AXE ,
	GONGZO_SKILL_BOW ,
	GONGZO_SKILL_GUN ,

	GONGZO_SKILL_HELMET,
	GONGZO_SKILL_SHOES,
	GONGZO_SKILL_BELT,
	GONGZO_SKILL_RESERVED1,
	GONGZO_SKILL_ARMOR,
	GONGZO_SKILL_RESERVED2,
	GONGZO_SKILL_RESERVED3,

	//=====================================================
	GONGZO_SKILL_LAST = GONGZO_SKILL_RESERVED3,
	GONGZO_SKILL_TOTAL,
};

struct GongzoMember
{
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, GONGZO_SKILL_TOTAL>		siPriceValue;
	NSafeTArray<SI16, GONGZO_SKILL_TOTAL>		siSkillValue;
#else
	SI16	siPriceValue[GONGZO_SKILL_TOTAL];
	SI16	siSkillValue[GONGZO_SKILL_TOTAL];
#endif

	GMONEY	siCraftFund;
};

#define MAX_INVESTMENT_ITEM_NUMBER	50// 투자상담가가 보여줄 투자 종목 총 갯수

struct InvestmentLines
{
	SI32	siInvestmentItemUnique; // 아이템의 유니크
	GMONEY	siInvestmentItemPrice; // 아이템의 가격

	GMONEY	siMarginalProfit; // 차익

#ifdef _SAFE_MEMORY
	NSafeTArray<GMONEY, MAX_MATERIAL_NUMBER>	siMaterialItemPrice;
#else
	GMONEY	siMaterialItemPrice[MAX_MATERIAL_NUMBER];
#endif
};

//-------------------------------------------
// 돈 
//-------------------------------------------
#define MAX_MONEY	2100000000	// 돈의 최대 단위. 
class cltMoney{
public:
	GMONEY itMoney;

	void Init();

	void Set(cltMoney* pclmoney);
	void Set(SI64 money);
	
	cltMoney Minus(cltMoney* pclmoney);
	cltMoney Plus(cltMoney* pclmoney);
	void Increase(cltMoney* pclmoney);
	void Decrease(cltMoney* pclmoney);

	SI32 GetPercent(cltMoney* pclmoney); // itMoney에서 pclmoney가 차지하는 비율. 
	void Clear();
	bool Empty();
	
	bool Large(cltMoney* pclmoney);
	bool Small(cltMoney* pclmoney);
};


//-------------------------------------------
// 위치 정보 
//-------------------------------------------
class cltPos{
public:
	SI32 siX;
	SI32 siY;

	
	cltPos();
	cltPos(SI32 x, SI32 y);
	void Init();
	void Set(const cltPos* pclpos);
	void Set(SI32 six, SI32 siy);
};

// 워프 정보. 
class cltWarpInfo{
public:
	UI32 uiWarpSwitch:		1;
	UI32 uiMapIndex:		9;
	UI32 uiForceSwitch:		1;		// ㅈ주변자리 검색 없이 바로 그자리로 워프 
	UI32 uiTicketUseSwitch:	1;		// 유료 아이템을 사용한 워프. (특수 효과를 보여줘야 한다) 
	UI32 uiX:				10;
	UI32 uiY:				10; 

	SI16	siGateX, siGateY;	// 게이트 위치. (게이트가 따로 없을때는 -1) 

public:

	
	cltWarpInfo();
	cltWarpInfo(UI32 warpswitch, UI32 mapindex, UI32 forceswitch, UI32 ticketuse, UI32 x, UI32 y, SI16 gatex, SI16 gatey);

	void Set(const cltWarpInfo* pclinfo);
	void Init();

	UI32 GetWarpSwitch() const;
	void SetWarpSwitch(UI32 mode);

	UI32 GetMapIndex() const;
	UI32 GetX() const;
	UI32 GetY() const;

	SI16 GetGateX() const;
	SI16 GetGateY() const;
};


//---------------------------------
// 간단한 Person정보 
//---------------------------------
class cltSimplePerson{
public:
	SI32	siPersonID;
	TCHAR	szName[MAX_PLAYER_NAME];

	cltSimplePerson();
	cltSimplePerson(SI32 personid, const TCHAR* pname);
	
	void Set(const cltSimplePerson* pinfo);
	void Set(SI32 personid, const TCHAR* pname);
	
	void Init();
	
	SI32 GetPersonID() const;
	void SetPersonID(SI32 id);

	const TCHAR* GetName()const;
	void SetName(const TCHAR* pname);
	
};


//-------------------------------
// 캐릭터의 위치 정보 
//-------------------------------
class cltCharPos{
public:
	SI16 siMapIndex;	// 캐릭터의 위치.(지도 인덱스)  
	SI16 siX;			// 캐릭터의 위치 (지도 좌표 ) 
	SI16 siY;			// 캐릭터의 위치 (지도 좌표 ) 
	SI16 siReserved;

public:
	
	cltCharPos();
	cltCharPos(SI32 mapindex, SI32 x, SI32 y);
	
	void Set(const cltCharPos* pclpos);
	void Init();
	
	void SetMapIndex(SI32 index);
	SI32 GetMapIndex() const;

	void SetX(SI32 x);
	SI32 GetX() const;

	void SetY(SI32 y);
	SI32 GetY() const;
	
};


//----------------------------------
// 가장 간단한 형태의 신분 정보 
//----------------------------------
class cltSimpleRank{
public:
	SI08 siType;			// 직급의 타입. 
	SI08 siVillageUnique;	// 마을과 관련된 직급일 경우 해당 마을. 

public:

	
	cltSimpleRank();
	cltSimpleRank(SI32 ranktype, SI32 villageunique);
	cltSimpleRank(cltSimpleRank* pclrank);
	
	void Init();
	
	void Set(SI08 ranktype, SI08 villageunique);
	void Set(const cltSimpleRank* pinfo);
	
	void SetRankType(SI08 type);
	SI32 GetRankType() const;

	void SetVillageUnique(SI08 villageunique);
	SI32 GetVillageUnique() const;

	BOOL IsSame(cltSimpleRank* pclrank) const;
	
};

#define GUILDRANKTYPE_NONE			0		// 길드원 아님 - 초기값
#define GUILDRANKTYPE_MASTER		1		// 길드장
#define GUILDRANKTYPE_MEMBER		2		// 길드원
#define GUILDRANKTYPE_STANDING		3		// 길드 가입 대기자
#define GUILDRANKTYPE_SECONDMASTER	4		// 부길드장
#define GUILD_MAXNAMENUM				13		// 최대길드이름갯수
#define MAX_GUILDRANK				10		// 사냥터길드전 등수

//----------------------------------
// 가장 간단한 형태의 길드 신분 정보 
//----------------------------------
class cltSimpleGuildRank{
public:
	SI08 siType;			// 직급의 타입. 
	SI32 siVillageUnique;	// 길드 소속 마을
	SI32 siGuildUnitIndex;	// 길드 인덱스 
	TCHAR szGuildName[GUILD_MAXNAMENUM];	// 길드 이름
	UI08 uiConfirm;			// 길드 승인 여부
	SI32 siMarkIndex;		// 길드 마크
	SI32 siEnemyGuildUnique; // 적길드 유니크
	SI32 siEmpireUnique;	// 길드가 소속된 제국유니크

public:
	cltSimpleGuildRank();
	cltSimpleGuildRank( SI08 ranktype, SI32 villageunique, SI32 guildunitindex,TCHAR*name ,UI08 confirm,SI32 mark, SI32 enemyguildunique = 0, SI32 EmpireUnique = 0);
	cltSimpleGuildRank( cltSimpleGuildRank* pclrank );
	
	void Init();
	void Set( SI08 ranktype, SI32 villageunique, SI32 guildunitindex ,TCHAR*name,UI08 confirm,SI32 mark, SI32 enemyguildunique = 0, SI32 EmpireUnique = 0);
	void Set(const cltSimpleGuildRank* pclrank);
	
	void SetRankType(SI08 type);
	SI32 GetRankType() const;

	void SetVillageUnique(SI32 villageunique);
	SI32 GetVillageUnique() const;

	void SetGuildUnitIndex(SI32 guildunitindex);
	SI32 GetGuildUnitIndex() const;

	void SetEnemyGuild( SI32 enemyguildunique );
	SI32 GetEnemyGuild() const;

	void SetEmpireUnique( SI32 EmpireUnique );
	SI32 GetEmpireUnique() const;

	BOOL IsSame(cltSimpleGuildRank* pclrank) const;

	bool IsGuildMember();

};

// 명칭 정보.
class cltPersonNaming
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_NAMINGQUEST_INDEX>	m_siLevel;			// 인덱스에 해당하는 네이밍의 레벨.
#else
	SI32 m_siLevel[MAX_NAMINGQUEST_INDEX];			// 인덱스에 해당하는 네이밍의 레벨.
#endif
	SI32 m_siSelectedIndex;							// 현재 선택된 인덱스
	SI32 m_siSelectedLevel;

public:
	cltPersonNaming();
	~cltPersonNaming();

	void Init();

	void Set( cltPersonNaming* pclCharNamingInfo );
};


//KHY - 1220 - 변신시스템.
#define MAX_TRANSFORM_CHAR 16 // 갸차스피릿 맥스수치 14->16으로 늘림.

class cltTransForm
{
public:
	UI16 	uiCanTransFormKind;		// 변신 가능한 캐릭터의 종류.
	SI32	siUseTotalSecond;		// 변신 캐릭터 누적 사용 시간.

	cltTransForm()
	{
		ZeroMemory(this, sizeof(cltTransForm));
	}

	void Set(cltTransForm* pclTransForm)
	{
		if(pclTransForm == NULL)		return;

		uiCanTransFormKind	= pclTransForm->uiCanTransFormKind;
		siUseTotalSecond	= pclTransForm->siUseTotalSecond;
	}	

};

class cltTransFormInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTransForm, MAX_TRANSFORM_CHAR>	clTransForm;
#else
	cltTransForm clTransForm[MAX_TRANSFORM_CHAR]; // 변신 캐릭터별 기본 정보.
#endif

	UI16 	uiNowTransFormKind;	// 마지막(혹은 현재)변신중인 캐릭터의 종류.
	bool 	bTransFormMode;		// 변신 상태 여부. - True = 변신.

	bool 	bTransForm100Effect;	// 변신 100% 이펙트를 그란다.

public:
	cltTransFormInfo();
	void Init();
	void Set(cltTransFormInfo* pclTransFormInfo)
	{
		if(pclTransFormInfo == NULL)		return;

		for(SI16 i=0; i<MAX_TRANSFORM_CHAR; i++)
		{
			clTransForm[i].Set(&pclTransFormInfo->clTransForm[i]);
		}

		uiNowTransFormKind = pclTransFormInfo->uiNowTransFormKind;
		bTransFormMode = pclTransFormInfo->bTransFormMode;
		bTransForm100Effect = pclTransFormInfo->bTransForm100Effect;
	}

	bool SetTransFormChar(UI16 uTransFormChar);				// 변신 캐릭터를 셋팅한다.
	bool SearchTransFormChar(UI16 uTransFormChar);				// 변신 캐릭터를 셋팅한다.	

	SI32 AddTransFormTime(UI16 uiTransformChar, SI32 sAddSecond);		// 변신 캐릭터의 시간을 더 한다. - return = 남은 변신 가능시간.

	bool CanTransForm(UI16 uTransFormChar);					// 변신 가능여부를 확인한다.
	REAL32 GetSynchroTransForm(UI16 uTransFormChar);			// 해당 타입의 캐릭터와의 싱크로율을 계산한다. - return = 싱크로율을 %로 반환한다.
};

//----------------------------------
// 계좌번호 클래스 
//---------------------------------
class cltAccountNum{
public:
	SI32 siVillageUnique;	// 통장이 있는 마을의 유니크. 
	SI32 siAccountNum;		// 계좌번호. 

	cltAccountNum();
	cltAccountNum(SI32 villageunique, SI32 accountnum);
	
	void Init();
	void Set(const cltAccountNum* pclaccountnum);

	// 이 통장 계좌가 유효한가?
	BOOL IsValid();
	bool IsSame(cltAccountNum* pclnum);

	void SetVillageUnique(SI32 villageunique);
	SI32 GetVillageUnique() const;

	void SetAccountNum(SI32 num);
	SI32 GetAccountNum() const;
};

//-------------------------------------
// 신분을 가진 사람의 정보. 
// (대행수, 전장행수, 여각행수 등등...
//-------------------------------------
class cltRankPerson{
public:
	SI32 siVillageUnique;
	cltSimplePerson	clPerson;

	cltRankPerson();
	cltRankPerson(SI32 sivillageunique, const cltSimplePerson* pinfo);

	void Set(const cltRankPerson* pclinfo);
	void Set(SI32 sivillageunique, const cltSimplePerson* pinfo);
	
	void Init(SI32 villageunique);
	
	SI32 GetPersonID() const;
	SI32 GetVillageUnique() const;
	
};


//------------------------------------------
// 서버가 클라이언트로 보내는 리턴값 클래스 
//------------------------------------------
class cltServerResponseValue{
public:
	SI16 siReceiver;
	SI16 siReturnValue;
	SI16 siPara1;
	SI16 siPara2;
	
	cltServerResponseValue();
	cltServerResponseValue(SI16 receiver, SI16 value, SI16 sipara1, SI16 sipara2);	
};

//KHY - 0910 - 클라이언트로 캐릭터형태의 리턴값을 보낸다.
//------------------------------------------
// 서버가 클라이언트로 보내는 리턴값 클래스 
//------------------------------------------
class cltServerResponseCharValue{
public:
	SI16 siReceiver;
	SI16 siReturnValue;
	TCHAR siPara1[100];
	TCHAR siPara2[100];

	
	cltServerResponseCharValue();
	cltServerResponseCharValue(SI16 receiver, SI16 value, TCHAR* sipara1, TCHAR* sipara2);
	
};
//KHY - 0910 - 클라이언트로 캐릭터형태의 리턴값을 보낸다.
//------------------------------------------
// 서버가 클라이언트로 보내는 리턴값 클래스 
//------------------------------------------
class cltServerResponseCharValue2{
public:
	SI16 siReceiver;
	SI16 siReturnValue;
	TCHAR siPara1[100];
	TCHAR siPara2[100];
	TCHAR siPara3[100];


	cltServerResponseCharValue2();
	cltServerResponseCharValue2(SI16 receiver, SI16 value, TCHAR* sipara1, TCHAR* sipara2, TCHAR* sipara3 );

};
//------------------------------------------
// 각종 통계 자료의 백업 파일을 남기기 위한 구조체와 값들 [영진]
//------------------------------------------
#define SERVER_BACKUPFILE_HEADER_VERSION 100

struct stServerBackUpFileHeader
{
	TCHAR szDesc[32];
	SI32  siVersion;	
};


#define MIN_FEE	100
#define MAX_FEE	100000
#define MAX_FEE_RATE	100		// 10%

#define MIN_FEE_RATE_NEWMARKET	 5		//[진성] 통합마켓의 최저 수수료는   5%
#define MAX_FEE_RATE_NEWMARKET	15		//[진성] 통합마켓의 최대 수수료는  15%

//-----------------------------------------
// 수수료 관리 
//-----------------------------------------
class cltFee{
private:
	SI32	siFeeRate;		// 타행 입출금 수수료 (퍼밀) 
	GMONEY	siMinFee;		// 최저 수수료. 
	GMONEY	siMaxFee;		// 최대 수수료. 	
public:

	void Set(cltFee* pclfee,SI32 value = 1000);
	
	// 거래 금액을 근거로 수수료를 계산한다. 
	GMONEY CalcFee(GMONEY money,SI32 value = 1000); // value가 100이면 100분율 계산 , 1000이면 천분율 계산
	BOOL SetFeeRate(SI32 rate,SI32 value = 1000 );  // value가 100이면 100분율 계산 , 1000이면 천분율 계산
	BOOL SetFeeRateNew( SI32 rate, SI32 value = 1000 );		// 5 ~ 10%
	SI32 GetFeeRate() const;
	BOOL SetMinFee(GMONEY fee);
	BOOL SetMinFeeNew(GMONEY fee);
	GMONEY GetMinFee() const;

	BOOL SetMaxFee(GMONEY fee);
	BOOL SetMaxFeeNew(GMONEY fee);
	GMONEY GetMaxFee() const;

	// 현재 수수료가 적절한지 확인한다. 
	BOOL IsValid(SI32 value); // value가 100이면 100분율 계산 , 1000이면 천분율 계산
	
	// 현재 수수료가 적절한지 확인한다. 
	BOOL IsValid();

	BOOL IsValidNew();
};

//-------------------------------------
// 로그인요청 정보 
//-------------------------------------
class cltLogInInfo{
public:
	SI32	siAuthKey;
	TCHAR	szID[MAX_PLAYER_NAME];			// 아이디의 포인터. 
	TCHAR	szPassword[MAX_PLAYER_NAME];	// 암호의 포인터. 
	UI08	uiGameMode;						// 현재 클라이언트 게임 모드 : 0 => 윈도우 창 + 윈도우 인터페이스모드, 
											// 1 => 윈도우 + 새인터페이스 모드, 2 => 전체화면 + 새인터페이스 모드
	
	cltLogInInfo(SI32	authkey, TCHAR* id, TCHAR* password, UI08 gamemode);
	
};


//-------------------------------------
// NHN HANAUTH 로그인요청 정보 
//-------------------------------------
class cltLogIn_HanAuthInfo{
public:
	SI32	siAuthKey;
	TCHAR	szAuthString[2048];				// NHN HANAUTH AuthString
	TCHAR	szID[MAX_PLAYER_NAME];			// 아이디의 포인터. 
	UI08	uiGameMode;						// 현재 클라이언트 게임 모드 : 0 => 윈도우 창 + 윈도우 인터페이스모드, 
	// 1 => 윈도우 + 새인터페이스 모드, 2 => 전체화면 + 새인터페이스 모드

	cltLogIn_HanAuthInfo(SI32 authkey, TCHAR* authstring, TCHAR* id, UI08 gamemode);
};

//-----------------------------------------------------------------------------------------------
// 인증 요청(게임실행도중에 나이제한체크) : NHN HANAUTH (PCK : 2007.09.19)
//-----------------------------------------------------------------------------------------------
struct cltHanAuth_GameRunAuth
{
	TCHAR				authstring[ 2048 ];
	TCHAR				userid[ 20 ];
};

//-------------------------------------
// TAIWAN 로그인요청 정보 
//-------------------------------------
class cltLogIn_TaiwanInfo{
public:
	SI32	siAuthKey;
	TCHAR	szGameAccount[30];				// Game Account
	TCHAR	szOneTimePassword[40];			// One Time Password
	UI08	uiGameMode;						// 현재 클라이언트 게임 모드 : 0 => 윈도우 창 + 윈도우 인터페이스모드, 
	// 1 => 윈도우 + 새인터페이스 모드, 2 => 전체화면 + 새인터페이스 모드

	cltLogIn_TaiwanInfo(SI32 authkey, TCHAR* gameaccount, TCHAR* onetimepassword, UI08 gamemode);
};

//-------------------------------
// 캐릭터에게 주어지는 명령 
//-------------------------------
class cltOrderDataInfo{
public:
	SI08 siOrder;             // 수행해야 할 명령 코드 
	SI08 siHostMode;          // 명령을 내린 주체 (플레이어 또는 컴퓨터 )

	SI32 siPara1;				// 명령에 딸려 가는 파라메타 
	SI16 siPara2;				// 명령에 딸려 가는 파라메타 
	SI16 siPara3;				// 명령에 딸려 가는 파라메타 
	SI16 siPara4;				// 명령에 딸려 가는 파라메타 (PVP때문에 쓴다)

	DWORD	dwPushedTime;		// 생성된 시각

	cltOrderDataInfo();
	cltOrderDataInfo(SI08 order, SI08 hostmode, SI32 para1, SI16 para2, SI16 para3, SI16 para4);
	cltOrderDataInfo(cltOrderDataInfo* pclinfo);
	
	void Init();
	void Make(SI08 order, SI08 hostmode, SI32 para1, SI16 para2, SI16 para3, SI16 para4);
	void Set(cltOrderDataInfo* pclorder);

};

// 명령의 실체 
// 컴퓨터가 실제로 전송하는 명령의 데이터 
class cltOrderData {
public:
    cltOrderDataInfo ODI;

	SI32	CharUnique;					 // 명령을 수행해야 할 캐릭터의 CharUnique
	
	cltOrderData();

	void Make(SI32 order, SI32 charunique, SI32 para1, SI16 para2, SI16 para3, SI16 para4, SI08 hostmode);
	void Make(SI32 charunique, cltOrderDataInfo* pclinfo);
	
};

class cltShapeEquipInfoUnit{
public:
	UI32	uiUnique:	16;  // 32767 까지다.
	UI32	uiRare:		4; // 15 까지다.
	UI32	uiEnchantPower:	4;	// 15 레벨까지 존재 가능
	UI32	uiEnchantType: 4;	// 15가지의 타입이 존재 가능
	UI32	uiReserved:	4;
	
	cltShapeEquipInfoUnit();
	cltShapeEquipInfoUnit(UI32 unique, UI32 rare , UI32 enchanttype , UI32 enchantlevel );
	
	void Init();
	void Set(cltShapeEquipInfoUnit* pclinfo);
	
};
// 외부 장비품 정보.
class cltShapeEquipInfo{
public:
	cltShapeEquipInfoUnit clArmour;
	cltShapeEquipInfoUnit clHelmet;
	cltShapeEquipInfoUnit clMantle;
	cltShapeEquipInfoUnit clWeapon;

	UI32	uiSwordScroll:	1;
	UI32	uiSpearScroll:	1;
	UI32	uiAxeScroll:	1;
	UI32	uiGunScroll:	1;
	UI32	uiBowScroll:	1;
	UI32	uiStaffScroll:	1;
	UI32	uiCannonScroll:	1;

	SI08	siSwordScrollNum;
	SI08	siSpearScrollNum;
	SI08	siAxeScrollNum;
	SI08	siGunScrollNum;
	SI08	siBowScrollNum;
	SI08	siStaffScrollNum;

	SI16	siCompletedSetItemIndex;
	SI16	siCompletedSetItemIndexStep;

	SI16	siCompletedSetItemIndex2;
	SI16	siCompletedSetItemIndexStep2;

	SI16	siCompletedSetItemIndex3;
	SI16	siCompletedSetItemIndexStep3;

	SI16	siCompletedSetItemIndex4;
	SI16	siCompletedSetItemIndexStep4;

	SI16	siCompletedSetItemIndex5;
	SI16	siCompletedSetItemIndexStep5;
	
	cltShapeEquipInfo();
	cltShapeEquipInfo(cltShapeEquipInfoUnit* pclArmour, cltShapeEquipInfoUnit* pclHelmet, cltShapeEquipInfoUnit* pclMantle, cltShapeEquipInfoUnit* pclWeapon,
						bool bsword, bool bspear, bool baxe, bool bgun, bool bbow, bool bstaff, bool bcannon,
						SI08 SwordScrollNum, SI08 SpearScrollNum, SI08 AxeScrollNum,
						SI08 GunScrollNum, SI08 BowScrollNum, SI08 StaffScrollNum,
						SI16 CompletedSetItemIndex,
						SI16 siCompletedSetItemIndexStep,
						SI16 CompletedSetItemIndex2,
						SI16 siCompletedSetItemIndexStep2,
						SI16 CompletedSetItemIndex3,
						SI16 siCompletedSetItemIndexStep3,
						SI16 CompletedSetItemIndex4,
						SI16 siCompletedSetItemIndexStep4,
						SI16 CompletedSetItemIndex5,
						SI16 siCompletedSetItemIndexStep5);
	void Init();
	void Set(cltShapeEquipInfo* pclinfo);
	
};

//
#define CHANGETYPE_POISON					1
#define CHANGETYPE_ICE						2
#define CHANGETYPE_DRAIN					3
#define CHANGETYPE_HEAL						4
#define CHANGETYPE_NOFIRSTATTACK			5	// 선공 방지 효과. 
#define CHANGETYPE_NOICEATTACK				6	// 선공 방지 효과. 
#define CHANGETYPE_CURSEATTACK				7	// 
#define CHANGETYPE_CURSECRITICAL			8
#define CHANGETYPE_CURSEDEFENSE				9	// 
#define CHANGETYPE_CURSEMOVESPEED			10
#define CHANGETYPE_ANGEL					11	// 수호천사 여부 변경. 
#define CHANGETYPE_AUTOFOOD					12	// 자동 말먹이 설정 변경 여부. 
#define CHANGETYPE_TOPSKILLUNIQUE			13	// 최고장인의 기술 
#define CHANGETYPE_MAGICFIRE				14	// 불해치의 마법 공격의 불
#define CHANGETYPE_FROZEN					15	// 얼음성 보스의 얼림 공격
#define CHANGETYPE_POLICE					16	// 포교 여부 변경
#define CHANGETYPE_INCREASEMOVESPEED		17	// 이동속도버프 변경
#define CHANGETYPE_HEARTEFFECT				18	// 하트 이펙트 변경
#define CHANGETYPE_FOURLEAF					19	// 네잎 클로버 이펙트
#define CHANGETYPE_TRANSFORM100EFFECT		20	// 변신 100% 이펙트
#define CHANGETYPE_TRANSFORMBUF				21	// 변신 100% 이펙트
#define CHANGETYPE_EMBLEM					22	// 무기술의 달인 - 엠블렘변경
#define CHANGETYPE_DISPLAYLOVELEVEL			23	// 보여지는 애정도 레벨이 변경되었다
#define CHANGETYPE_TRANSFORM_HORSE			24	// 축제 음식 - 탈것이 변신
#define CHANGETYPE_STUN						25	// 스턴 
#define CHANGETYPE_SUMMONNOFIRSTATTACK		26	// 소환수 선공 방지 효과.
#define CHANGETYPE_NOFIRSTATTACKPREMIUM		27	// 선공 방지 효과 프리미엄
#define CHANGETYPE_POISON_SETITEM_EFFECT	28	// 세트 아이템으로 인한 독효과.

//----------------------------------------
// 캐릭터들의 변경 정보들을 위한 정보
//-----------------------------------------
class cltCharChangeStatusInfo{
public:
	SI32	siChangeType;
	bool	bChangeSwitch;
	SI32	siChageAmount1;
	SI32	siChageAmount2;
	SI32	siChageAmount3;

	cltCharChangeStatusInfo ();
	cltCharChangeStatusInfo (SI32 changetype, bool bswitch, SI32 amount1 = 0, SI32 amount2 =0, SI32 amount3 = 0 );
	
	void Set(cltCharChangeStatusInfo *pclInfo);
	
};

//----------------------------------------
// 캐릭터들의 부가정보들을 위한 정보
//-----------------------------------------
class cltCharAddStatusInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, 2>	siReserved;
#else
	SI16			siReserved[2];
#endif

/*	SI08			siIdentity;
	SI16			siHome;							// 성황신일 경우 자신이 관할하는 마을의 Unique 값
	SI16			siCapa;							// 성황신의 성능지수 

	SI32			siChildCharUnique;				// 소환수를 갖고 있다면 소환수의 Unique
	SI32			siParentCharUnique;				// 자신이 소환수이라면 부모의 Unique
	SI32			siParentPersonID;				// 자신이 소환수이라면 부모의 PersonID : 확실하게 비교하기 위해서리
	SI16			siSummonIndex;					// 자신이 소환수라면 소환수 Index	
*/

	cltCharAddStatusInfo ();

//	cltCharAddStatusInfo (SI08 identity, SI16 home, SI16 capa, SI32 childunique, SI32 parentunique, SI32 parentperson, SI16 summonindex);

	void Init();
	void Set(cltCharAddStatusInfo *pclInfo);
	
};

//------------------------------------
// Event 캐릭터 여부 정보. 
//------------------------------------
class cltEventCharInfo{
public:
	UI32 bEvent1Switch:		1;
	UI32 bEvent2Switch:		1;
	UI32 bEvent3Switch:		1;
	UI32 bEvent4Switch:		1;
	UI32 bEvent5Switch:		1;
	UI32 bEvent6Switch:		1;
	UI32 bEvent7Switch:		1;

	cltEventCharInfo();
	
	void Init();
	void Set(cltEventCharInfo* pclinfo);
	
};

//----------------------------------------
// 캐릭터의 내부 Status 정보 
//-----------------------------------------
#define ENEMYTYPE_ALLPC							0x0001	// 모든 사용자와 적대적. 
#define ENEMYTYPE_ALLNPC						0x0002	// 모든 NPC와 적대적 
#define ENEMYTYPE_VILLAGE						0x0004	// 공성관계 마을과 적대적. 
#define ENEMYTYPE_ONEVILLAGE					0x0008	// 특정 한 마을과만 적대적 (para1에 특정 마을의 유니크 정보) 
#define ENEMYTYPE_GUILDWAR						0x0010	// 길드전 - para1에 싸우는 길드의 유니크
#define ENEMYTYPE_PVP							0x0020	// PVP 캐릭터

#define PVPTYPE_ALL	  0	// 모든 PVP내용 적용
#define PVPTYPE_GREEN 1 // 제한적인 PVP내용 적용

class cltEnemyTypeInfo{
public:
	SI16	siEnemyType;
	SI16	siPara1;

	cltEnemyTypeInfo();
	void Init();
	void Set(cltEnemyTypeInfo* pclinfo);
	void Set(SI16 type, SI16 para1);
	
	bool IsType(SI32 type);
	
};

#define INNERSTATUS_POISON						1
#define INNERSTATUS_ICE							2
#define INNERSTATUS_CURSEATTACK					4
#define INNERSTATUS_CURSECRITICAL				8
#define INNERSTATUS_CLONE						16
#define INNERSTATUS_PRISON						32
#define INNERSTATUS_CURSEDEFENSE				64
#define INNERSTATUS_CURSEMOVESPEED				128
#define INNERSTATUS_MAGICFIRE					256		// 불해치 마법에 당해서 불 붙음
#define INNERSTATUS_FROZEN						512		// 얼음성 보스 마법에 맞아서 얼어버림
#define INNERSTATUS_INCREASEMOVESPEED			1024	// 이동속도 증가 버프
#define INNERSTATUS_STUN						2048	// 스턴
#define INNERSTATUS_POISON_SETITEM_EFFECT		4096	// 세트 아이템으로 생기는 독효과.

class cltInnerStatusInfo{	
public:
	SI32	siStatus;
	cltEnemyTypeInfo		clEnemyType;		// 적대 관계 정보. 
	cltEventCharInfo		clEventInfo;		// 캐릭터의 이벤트 참여 정보. 
	
	
	SI16	siTopSkillUnique;					// 최고 장인인 기술의 유니크 

	cltInnerStatusInfo();

	cltInnerStatusInfo(SI32 status,	cltEnemyTypeInfo* pclenemytype, 
		cltEventCharInfo* pclevent,
		SI16 topskillunique);
	
	void Set(cltInnerStatusInfo* pclinfo);
	void Init();
	
	bool IsStatus(SI32 status);
	void SetStatus(SI32 status);
	void DelStatus(SI32 status);
	

};

//--------------------------------
// 캐릭터 아이덴티 정보 
//--------------------------------
class cltIdentityCommonInfo{
public:
	SI16	siPara1;
	SI16	siPara2;
	SI32	siPara3;
};

class cltIdentitySummonInfo{
public:
	SI16	siMySummonIndex;
	SI16	siParentCharUnique;
	SI32	siParentPersonID;
};

class cltIdentityVillageGodInfo{
public:
	SI16	siCapa;
};

class cltIdentityVillageHuntInfo{
public:
	SI16	siHome;
	SI16	siPara2;
};

class cltIdentityBlackArmyInfo
{
public:
	SI16	siWarMapIndex;
	SI16	siMapIndex;
};

class cltIdentityVillageKingMonument
{
public:
	SI32	siVillageUnique;	
};

class cltIdentityMofuMofuEvent
{
public:
	SI16	siField;
	SI16	siIndex;
	SI32	siCanAttack;
};

class cltIdentityInstanceMap
{
public:
	SI16	siPara1;
	SI16	siPara2;
	SI32	siScore;
};

class cltIdentityQuestInfo
{
public:
	SI32	m_siEnemyPersonID;
	SI32	m_siEnemyCharID;	// 클라이언트용
};

class cltIdentitySoulBound
{
public:
	SI32	m_siPersonID;		// 귀속자 ID
};

class cltIdentitySoulGuard
{
public:
	SI16	m_siParentCharUnique;
	SI32	m_siParentPersonID;
};

class cltIdentity{
public:
	SI08	siIdentity;

	union
	{
		cltIdentityCommonInfo			clCommonInfo;
		cltIdentitySummonInfo			clSummonInfo;
		cltIdentityVillageGodInfo		clGodInfo;
		cltIdentityVillageHuntInfo		clHuntInfo;
		cltIdentityBlackArmyInfo		clBlackArmyInfo;
		cltIdentityVillageKingMonument	clKingMonument;
		cltIdentityMofuMofuEvent		clMofoMofuEvent;
		cltIdentityInstanceMap			clInstanceMap;
		cltIdentityQuestInfo			clQuestInfo;
		cltIdentitySoulBound			clSoulBound;
		cltIdentitySoulGuard			clSoulGuard;
	};

	cltIdentity();
	cltIdentity(SI08 identity, SI16 para1, SI16 para2, SI32 para3);
	void Init();
	void Set(cltIdentity* pclinfo);
	
	void MakeSummon(SI32 iddentity, SI32 index, SI32 parentcharid, SI32 parentpersonid);	// 소환수를 설정한다. 
	void MakeGod(SI32 iddentity, SI32 capa);												// 성벽, 성황신, 성환신소환수를 설정한다.
	void MakeHunt(SI32 iddentity, SI32 villageunique);										// 불가사리를 설정한다.
	void MakeBlackWar(SI32 iddentity);
	void MakeBlackArmy(SI32 iddentity, SI16 WarMapIndex, SI16 MapIndex);
	void MakeKingMonument(SI32	iddentity, SI32 villageunique);								// 마을 수호상을 설정한다.
	void MakeMofuMofuEvent(SI32 iddentity, SI16 siField, SI16 siIndex, SI32 siCanAttack);
	void MakeInstanceMap(SI32 iddentity, SI32 siScore);
	void MakeMonsterAttackEvent( SI32 iddentity );											//[진성] 마을 이벤트 - 몬스터 습격 => 2008-3-26
	void MakeQuest( SI16 identity, SI32 siEnemyPersonID, SI32 siEnemyCharID );
	void MakeSoulBound( SI16 identity, SI32 siPersonID );									// 귀속 속성 : 불러낸 PersonID만 공격할수있음
	void MakeSoulGuard( SI08 identity, SI16 siParentCharUnique, SI32 siParentPersonID );	// [영훈] 수호정령_090525 : 
	void MakeTreasureEvent( SI32 iddentity );												// [성웅] 트레저 이벤트 
	void MakeRaccoonDodgeEvent( SI32 iddentity );											// [성웅] 라쿤 피하기 이벤트
	void MakeBBBEventMonster( SI32 identity );												// [지연] 복불복 이벤트용 몹
	void MakeSoulGuard_Summon( SI32 identity );												// [성웅] 
	void MakeBattleRoyalMob( SI32 siIdentity);												// [기형] 배틀로얄 몹 
	void MakeGMCreateMonster( SI32 siIdentity);												// [춘기] CMT명령어로 생성한 몬스터
	void MakeGiantRaccoonResurrectEvent( void );											// [진성] 자이언트 라쿤 부활 축제 이벤트 몬스터. 

};

#define MAKECHARTYPE_NPC		0
#define MAKECHARTYPE_PC			1

#define PVP_LEAGUE_MAX_LATEST_MATCH_PERSON 2

class cltPVP_LeagueInfo
{
public:
	SI16	m_siEnemyPersonID	;	// PVP리그전시 적
	SI16	m_siWin	;	// 연승 기록
	SI16	m_siDraw	;	// 연속 무승부 기록
	SI16	m_siLose	;	// 연속 패배 기록
	SI16	m_siStraight_Win	;	// 연승 기록
	SI16	m_siStraight_Draw	;	// 연속 무승부 기록
	SI16	m_siStraight_Lose	;	// 연속 패배 기록
	SI16	m_siGrade	;			// 등급
	SI16	m_siStraight_Win_Grade	;	// 등급상승을 위한 연승 기록 
	SI16	m_siStraight_Lose_Grade	;	// 등급하락을 위한 연패 기록 

	SI16	m_siLatestPersonID[PVP_LEAGUE_MAX_LATEST_MATCH_PERSON];	// 최근 나와 싸운 상대

	SYSTEMTIME	stLastPVPTime	;

public:
	cltPVP_LeagueInfo()		{	Init();											}
	~cltPVP_LeagueInfo()	{}

	void Init( void )		{	ZeroMemory( this, sizeof(cltPVP_LeagueInfo) );	}
	void Set( cltPVP_LeagueInfo* pclLeagueInfo )
	{
		if ( pclLeagueInfo )
		{
			memcpy( this, pclLeagueInfo, sizeof(cltPVP_LeagueInfo) );
		}
	}
};

enum ValentineWarStatus
{
	VALENTINEWAR_NONE	= 0,
	VALENTINEWAR_COUPLE,
	VALENTINEWAR_SOLO
};
class cltValentineWarInfo
{
public:
	SI16	m_siCouple	;		// 커플인지 아닌지 아직 결정 안했는지
	bool	m_bPrize		;		// 상품을 받았는지 받지 않았는지.
	SYSTEMTIME	m_stAnswerTime	;	// 질문에 답볍한 시간

public:
	cltValentineWarInfo()		{	Init();											}
	~cltValentineWarInfo()	{}

	void Init( void )		{	ZeroMemory( this, sizeof(cltValentineWarInfo) );	}
	void Set( cltValentineWarInfo* pclValentineWarInfo )
	{
		if ( pclValentineWarInfo )
		{
			memcpy( this, pclValentineWarInfo, sizeof(cltValentineWarInfo) );
		}
	}
	SI16 GetCouple(){ return m_siCouple ;}
	void SetCouple( SI16 siCouple){ m_siCouple = siCouple;}

	bool GetPrize(){ return m_bPrize ;}
	void SetPrize( bool siPrize){ m_bPrize = siPrize;}

	SYSTEMTIME GetAnswerTime(){ return m_stAnswerTime ;}
	void SetAnswerTime( SYSTEMTIME stAnswerTime){ m_stAnswerTime = stAnswerTime;}
};

//----------------------------------------
// 캐릭터를 만들때 사용하는 정보. 
//-----------------------------------------
class cltMakeCharInfoCommon{
public:
	UI32	uiType:					1;		// NPC용인가 사용자 용인가. 
	UI32    uiMakeCharKind:			16;		// 만들어 져야할 캐릭터 종류. 
	UI32    uiMakeCharUnique:		16;		// 이 메시지의 결과로 만들어져야 할 캐릭터의 CharUnique
	UI32	uiLevel:				8;		// (0~255)
	UI32	uiLife:					20;		// 현재 이 캐릭터의 체력. 
	UI32	uiX:					10;
	UI32	uiY:					10;
	UI32	uiMapIndex:				10;		// 지도 인덱스 (0~2^10 = 1024)
	UI32	uiTotalMoveSpeed:		6;	
	SI08	siHomeVillageUnique;		// 주소지 마을의 유니크. 
	SI16	siJimCharUnique;			// 이 캐릭터를 찜한 캐릭터의 유니크. 
	cltOrderDataInfo	clOrder;		// 캐릭터가 만들어진 후 행해야 할 임무. 		
	cltIdentity			clIdentity;		// 아이덴티 정보. 
	cltInnerStatusInfo	clInnerStatus;	// 캐릭터의 추가정보 (독, 얼음)
	cltMakeCharInfoCommon();
	
	cltMakeCharInfoCommon(UI32 makekind, UI32 makecharunique, SI32 home, UI32 level, 
		UI32 life, UI32 x, UI32 y, UI32 mapindex, UI32 speed, SI16 jimcharunique, 
		cltOrderDataInfo* pclorder,
		cltIdentity* pclidentity, 
		cltInnerStatusInfo* pclinnerstatus);
	
	void Init();
	void Set(cltMakeCharInfoCommon* pclinfo);
	

};

class cltMakeCharInfoUser{
public:

};

//[진성] 버프 발동 방법. => 2008-6-11
enum
{
	BUF_GET_TYPE_NONE				// 기냥...	
	,BUF_GET_TYPE_BUFROULETTE		// 버프 룰렛을 이용함.
	,BUF_GET_TYPE_NEWYEAREVENT		// 신년이벤트 룰렛을 이용함.
	,BUF_GET_TYPE_RUMBLECHERRY		// 럼블체리 아이템을 이용함.
	,BUF_GET_TYPE_FORTUNECOOKIE		// 포춘쿠키 아이템을 이용함.
	,BUF_GET_TYPE_NIGHTMARKET		// 야시장 음식 버프
};

// 버프 종류  - 절대 순서 바뀌면 안됨. DB에 저장되는 값
// 두가지 이상의 효과, 특수 효과일경우엔 새로운 버프 타입 만들기
// 다른 버프와 중복되어 사용됐을때 또 다른 효과가 나타나는 경우 또한 새로운 버프타입 필요
enum
{
	BUF_ATTACKUP = 1,
	BUF_DEFENSEUP,
	BUF_SPEEDUP,
	BUF_MAKEEXPUP,									// 제조보너스 타임과 중첩된다.
	BUF_NOFIRSTATTACK,
	BUF_SUMMONATACUP,
	BUF_LOVEPOWER,
	BUF_FRIENDSHIP,
	BUF_HINAMOCHI,
	BUF_SUCCESS_MANUFACTURE,
	BUF_MOFUMOFU_PERFUME,
	BUF_FOURLEAF,
	BUF_PREMIUMEXPUP,
	BUF_HAPPYBEAN,
	BUF_ATTACKUP30,									//전투력 증가약 30일간[2007.08.30 손성웅]
	BUF_DEFENSEUP30,								//방어력 증가약 30일간[2007.08.30 손성웅]
	BUF_SUPEREXPUP,
	BUF_NOTBONUSTIME_MAKEEXPUP,						// 제조보너스 타임에 중첩되지 않는다.
	BUF_THANKSGIVING_DAY,							
	BUF_FARMINGNMININGFOREVER,						//  채광용 농경용 아이템 

	BUF_STATUE_UP_STR,								//[진성] 힘		+ a	=> 2008-6-18
	BUF_STATUE_UP_DEX,								//[진성] 순발력	+ a	=> 2008-6-18
	BUF_STATUE_UP_MAG,								//[진성] 마력	+ a	=> 2008-6-18			
	BUF_STATUE_UP_VIT,								//[진성] 생명력	+ a	=> 2008-6-18
	BUF_STATUE_UP_HAND,								//[진성] 손재주 + a	=> 2008-6-18
	BUF_EXP_UP,										//[진성] 경험치 + a	=> 2008-6-18	

	BUF_REWARDBONUS,								//[강형] 이관 보상 아이템
	BUF_OLYMPICMEDAL,
	BUF_EVENT_EGGMOONCAKE,							//[진성] 에그월병.	=> 2008-8-14
	BUF_TRANSFORM,									//[강형] 변신버프

	BUF_MENTOR,										//[진성] 스승, 제자 버프.	2008-10-8						
	BUF_PREMIUMMAKEEXPUP,							//[춘기] 제조프리미엄 버프  2008-10-15
	BUF_SPECIALAMPUL_EXPUP300,						//[지연] 전투경험치 300% 중가 버프. 2009-02-26 (스페셜엠플)
	BUF_QUEST_ANTIPOTION,							//[영훈] 아수라의 데미지 30%감소

	BUF_EVENT_FINDTREASURE,							//[성웅] 보물찾기 이벤트
	BUF_QUEST_ATTACK,								//[춘기] 뼈티라노 공격시 30%공격력 증가
	BUF_WATERMELON,									//[춘기] 수박버프 - 아이템 사용시 5%의 확률로 대상에게 준 데미지를 한번 더 주게됨.(추가타 생성)
	BUF_TRANSFORM_HORSE,							//[춘기] 탈것변신버프 (08.09.11)

	BUF_STATUE_UP_WIS,								//[지연] 지혜	+ a	=> 2009-10-22 //2010
	BUF_EVENT_FORTUNE_BAD,							//[지연] 포춘쿠키 - 흉을 표시하기 위한 버프(실제 효과는 없다)

	BUF_CHRISTMASEVENT_SNOWBLESS,					//[춘기] 눈의 축복 버프
	BUF_CHRISTMASEVENT_DECORATION,					//[춘기] 크리스마스 장식 버프
	
	BUF_GIANTRACCOON_RESURRECT_EVENT,				//[진성] 자이언트 라쿤 이벤트 버프.
	BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE,	//[진성] 자이언트 라쿤 이벤트 건물 최초 완성 버프.

	BUF_RESIDENTS_EXPUP_10,				// [지연] 마을 EXP 캡슐 - 사용시 소속된 마을의 주민들에게 경험치 10%증가 효과.
	BUF_RESIDENTS_STRONG,				// [지연] 마을 강화제 - 사용시 소속된 마을의 주민들에게 최종 물리/마법 공격력, 방어력 증가값에 + 10% 효과. 

	BUF_VALENTINEDAY,								// 발렌타인 데이
	
	BUF_END
};

#define MAX_BUF	BUF_END - 1

class stBuf
{
public:
	SI16	siBufType;			//버프의 효과
	SI16	siPercent;			//버프 효과 ( 퍼센트로 증가할때 )
	SI16	siGetType;			//[진성] 버프 타입으로 변수 이름 변경. => 2008-6-11
	SI32	siOverTime;			//버프 종료 시간 ( 게임시간을 분으로 환산 )
	//	bool	bOverlap;			//중첩이 가능한지.					- 삭제 by LEEKH 2008.03.08


	stBuf()
	{
		siBufType		= 0;
		siPercent		= 0;
		siOverTime		= 0;
		siGetType		= 0;
	}

	stBuf(SI16 BufType, SI16 Percent, SI32 OverTime, SI16 _siGetType = 0)
	{
		siBufType	= BufType;
		siPercent	= Percent;
		siOverTime	= OverTime;
		siGetType	= _siGetType;
	}

	void Set(stBuf* pBuf)
	{
		if( pBuf == NULL )		return;

		siBufType	= pBuf->siBufType;
		siPercent	= pBuf->siPercent;
		siGetType	= pBuf->siGetType;
		siOverTime	= pBuf->siOverTime;
	}
};


#define MAX_BUF_COUNT		12

class cltBufInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<stBuf, MAX_BUF_COUNT>		m_stBuf;
#else
	stBuf	m_stBuf[MAX_BUF_COUNT];
#endif

	// 버프의 사용여부를 표시하는 비트배열
	NBitArray<BUF_END>				m_bitBufUse;

	cltBufInfo();

	// 선공방지 버프가 프리미엄인지
	bool m_bNoFirstAttackPreminum;

	void Init();
	void SetBuf( cltBufInfo* pclinfo );
	SI16 FindEmptySlot( SI16 type, bool overlap = false);
	void AddBuf( SI16 index, stBuf buf );
	void DeleteBuf( SI16 index );
	bool CanUseBuf( SI16 type );
	SI32 CalcTotalBufValue( SI16 type, SI32 currentValue );
	bool IsHaveBuf(SI16 type);
	// 버프 타입과 겟타입이 같은것
	bool IsHaveBufWithGetType( SI16 siFindBufType, SI16 siFindGetType );
	// 버프 타입이지만 겟타입이 같은것은 안됨
	bool IsHaveBufExecptGetType( SI16 siFindBufType, SI16 siFindGetType );
	SI32 GetBufPercent(SI16 type);
	SI32 GetBufOvertime(SI16 type);	
	stBuf* GetBuf(SI16 type);
	// [영훈] 현재 siType로 들어온 타입이 있는 슬롯(배열번호)을 찾는다 - 2008.01.23
	SI16 FindBufSlot( SI16 siType );

	// [진성] 버프를 특정하게 얻게된 타입의 슬롯 찾기. 
	SI16 FindBufGetTypeSlot( SI16 GetType );

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};



class cltPVP_LeagueInfo;
class cltValentineWarInfo;

class cltMakeCharInfo : public cltMakeCharInfoCommon{
public:
	//--------------------------------
	// 사용자 전용 정보 
	//--------------------------------
	UI32	uiChildCharUnique:		16;			// 보유한 소환수의 유니크. 
	UI32	uiSummonIndex:			3;			// 현재 소환수의 인덱스. 
	UI32	uiHeadChatSwitch:		1;			// 머릿말이 있는가 ?
	UI32	uiPersonalShopSwitch:	1;			// 개인상점이 있는가?	
	UI32	uiNoFirstAttackSwitch:	1;			// 선공 방어가 설정되어 있는가?
	UI32	uiNoIceAttackSwitch:	1;			// ICE 방어가 설정되어 있는가?
	UI32	uiHeartEffectSwitch:	1;			// 하트 이펙트가 설정 되어 있는가? ( 사랑,우정 버프가 겹치면 생기는 버프 )
	UI32	uiFourLeafSwitch:		1;			// 네잎 클로버 이펙트가 설정 되어 있는가?
	UI32	uiCusionSwitch:			16;			// 쿠션(방석)을 바닥에 깔고있는가.
	UI32	uiSex:					1;			// 성별. 


	UI32	uiHorseUnique1:			8;		// 말의 정보.
	UI32	uiSchoolUnique:			10;		// 학교의 유니크. 
	UI32	uiRequestAddinfo:		1;		// 신분의 설정 추가정보 요청 여부
	UI32	uiTicketWarpSwitch:		1;		// 유료이용권을 사용한 공간이동인가. 
	UI32	uiBestGuild:			1;		// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
	UI32	uiElectionStump:		1;		// [영훈] 선거 유세 중인가
	UI32	uiElixir:				1;		// [진성] 엘릭서 사용중인가.
	UI32	uiRepairShopSwitch:		1;		// [강형] 수리의뢰 중인가.


	SI08	siCurrentShowHorse; //( 0~4 ) 말 5마리의 인덱스.
	SI08	siGameMasterLevel;			// 운영자 권한 단계. 
	SI16	siMapUnique;				// 맵유니크. 

	cltShapeEquipInfo clShapeEquip;
	
	cltSimpleRank		clRank;

	SI32				siAddStatusDate;
	SI32				siStatusTicketNum;

	UI08				uiGMMode;		// 운영자 모드 설정
	bool				bPCRoom;		// pc방 유저인가
	SI08				siMakeAniType;	// 제조 에니메이션 모드 설정
	cltSimpleGuildRank	clGuildRank;	// 길드
	cltPersonNaming		clPersonNaming;
	bool 				siCurrentHorseRIDEHORSE;

	UI16				uiNowTransFormKind;
	bool				bTransFormMode;
	bool				bTransForm100Effect;
	SI16				siBufTransformKind;
	SI16				siBufTransformHorseKind;
	SI16				siEnemyUnique;		// 개인 PVP 적 유니크
	cltValentineWarInfo	clValentineWarInfo	;
	cltPVP_LeagueInfo	clPVP_LeagueInfo;
	// 프리미엄 파츠 정보
	SI32				siPremiumPartsDate_Slot1;
	SI32				siPremiumPartsUnique_Slot1;
	SI32				siPremiumPartsDate_Slot2;
	SI32				siPremiumPartsUnique_Slot2;
	SI32				siPremiumPartsDate_Slot3;
	SI32				siPremiumPartsUnique_Slot3;
	SI32				siPremiumPartsNum;

	UI08				uiWeaponSkillMasterEmblem;	// 무기술의 달인 - 엠블렘

	SI16				siDisplayLoveLevel;			// 남들에게 보여지게될 애정도

	SI16				siSoulGuardUnique;			// 내 수호정령 유니크

	cltBufInfo			m_clBufInfo;				// [진성] 버프정보를 담는다.

	//KHY - 1001 - 기승동물 5마리 보유 수정.
	//SI08 horseindex,
	cltMakeCharInfo();

	cltMakeCharInfo(UI32 					uikind, 
					UI32 					makecharunique, 
					UI32 					level, 
					UI32 					life, 
					UI32 					x, 
					UI32 					y, 
					UI32 					mapindex, 
					UI32 					childcharunique, 
					UI32 					summonindex, 
					UI32 					bheadchatswitch, 
					UI32 					bpersonalshopswitch, 
					UI32 					bnofirstattackswitch,
					UI32 					bnoiceattackswitch,
					UI32 					bhearteffectswitch,
					UI32 					bfourleafswitch,
					UI32 					bfarmminingswitch,//농경 광산 음식
					UI32 					bcushionswitch,
					UI32 					bsex,
					cltShapeEquipInfo*		pclequipinfo, 
					SI08 					CurrentShowHorse, 
					UI32 					totalmovespeed, 
					SI16 					jimcharunique, 
					SI08 					gamemasterlevel, 
					SI16 					mapunique, 
					UI32 					horseunique1, 
					UI32 					homevillageunique, 
					UI32 					schoolunique,
					cltSimpleRank*			pclrank,
					SI32 					addstatusdate,
					SI32 					ticketnum, 
					cltOrderDataInfo*		pclorder,
					cltIdentity*			pclidentity,
					cltInnerStatusInfo* 	pclinnerstatus, 
					UI32 					requestaddinfo,
					UI32 					ticketwarp,
					UI08 					gmmode ,
					bool 					pcroom,
					SI08 					makeanitype,
					cltSimpleGuildRank*		pclguildrank,
					cltPersonNaming*		pclpersonnaming,
					bool 					CurrentHorseRIDEHORSE,
					UI16 					NowTransFormKind,
					bool 					TransFormMode,
					UI32 					uiBestGuild,					// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
					bool 					bIsElectionStump,
					bool 					TransForm100Effect,
					SI16 					siBufTransform,
					SI16 					EnemyUnique,					// 개인 PVP - 적유니크
					cltValentineWarInfo*	pclValentineWarInfo,
					bool					bElixir,
					cltPVP_LeagueInfo*		pclPVP_Leagurinfo,
					SI32 					addPremiumPartsdate_Slot1,
					SI32 					addPremiumPartsUnique_Slot1,
					SI32 					addPremiumPartsdate_Slot2,
					SI32 					addPremiumPartsUnique_Slot2,
					SI32 					addPremiumPartsdate_Slot3,
					SI32 					addPremiumPartsUnique_Slot3,
					SI32 					PremiumPartsNum,
					UI08 					weaponSkillMasterEmblem,
					SI16 					displayLoveLevel,
					SI16 					soulGuardUnique,
					bool 					bRepairShopSW,
					cltBufInfo*				_pclBufInfo
		);					
	
	void Init();
	void Set(cltMakeCharInfoCommon* pclinfo);
	void Set(cltMakeCharInfo* pclinfo);
};

const SI16 MAX_PUPILNUMBER = 10;

class cltPFatherInfo{
public:
	cltSimplePerson	clFather;			// 스승 정보. 
	TCHAR			szAccountID[MAX_PLAYER_NAME];
	SI08			siMyLevelForFather;	// 스승이 선정된 당시의 내 레벨 
	SI08			siFatherChangeNumber;	// 스승을 변경한 횟수. 
	SI32		    siTeacherPoint; // 스승 포인트
	bool		    bOverTake;		// 청출어람 포상을 받았는가?
    
	cltPFatherInfo();
	void Init();
	void Set(cltPFatherInfo* pclinfo);

	void SetTeacherPoint( SI32 TeacherPoint )
	{
		siTeacherPoint = TeacherPoint;
	}
	SI32 GetTeacherPoint()
	{
		return siTeacherPoint;
	}

	void SetOverTake( bool flag )
	{
		bOverTake = flag;
	}
	bool IsOverTake()
	{
		return bOverTake;
	}
};

class cltVillageScoreInfo
{
public:
	// 마을 가입 후 시작한다!!
	SI32		siPlayTime;				// 마을 가입 후 플레이 시간
	SI08		siLevelUpCount;			// 마을 가입 후 레업 횟수
	SI32		siWarKillNum;			// 마을 가입 후 전공수
	SI16		siMakeRareItemCount;	// 마을 가입 후 명품 만든 횟수
	SI16		siMonthlyScore;			// 월별 점수
	SI32		siTotalScore;			// 토탈 점수

	cltVillageScoreInfo()
	{
		Init();
	}

	void Init()
	{
		siPlayTime = 0;				// 마을 가입 후 플레이 시간
		siLevelUpCount= 0;			// 마을 가입 후 레업 횟수
		siWarKillNum= 0;		// 마을 가입 후 전공수
		siMakeRareItemCount= 0;	// 마을 가입 후 명품 만든 횟수
		siMonthlyScore= 0;	// 월별 점수
		siTotalScore= 0;	// 토탈 점수
	}

	void MonthlyInit()
	{
		siPlayTime = 0;
		siLevelUpCount = 0;
		siWarKillNum = 0;
		siMakeRareItemCount = 0;
		siMonthlyScore = 0;
	}

	void Set(cltVillageScoreInfo* pclinfo)
	{
		siPlayTime = pclinfo->siPlayTime;
		siLevelUpCount = pclinfo->siLevelUpCount;
		siWarKillNum = pclinfo->siWarKillNum;
		siMakeRareItemCount = pclinfo->siMakeRareItemCount;
		siMonthlyScore = pclinfo->siMonthlyScore;
	}

};

class CEmpireInfo
{
public:

	SI08	m_siEmpireRank;		// 제국에서 나의 랭크
	SI32	m_siEmpireUnique;   // 나의 제국 유니크
	
public:

	enum
	{
		/// 소속없음
		EMPIRE_NONE = 0,
		/// 제국에 속한 일반인
		EMPIRE_PERSON,
		/// 제국의 맹주
		EMPIRE_EMPEROR,
		/// 제죽의 소맹주( 제국에 속한 마을 대행수 )
		EMPIRE_LITTLE_EMPEROR
	};

	CEmpireInfo() : m_siEmpireRank(0), m_siEmpireUnique(0) {};
	~CEmpireInfo() {}

	void SetEmpireInfo( SI08 RankType, SI32 EmpireUnique )
	{
		m_siEmpireRank = RankType;
		m_siEmpireUnique = EmpireUnique;
	}
	void SetEmpireInfo( CEmpireInfo*  EmpireInfo )
	{
		if( EmpireInfo != NULL )
		{
			m_siEmpireRank = EmpireInfo->GetEmpireRank();
			m_siEmpireUnique = EmpireInfo->GetEmpireUnique();
		}
		else
		{
			m_siEmpireRank = 0;
			m_siEmpireUnique = 0;
		}
	}

	SI08 GetEmpireRank()
	{
		return m_siEmpireRank;
	}

	SI32 GetEmpireUnique()
	{
		return m_siEmpireUnique;
	}
};

//KHY - 1220 - 변신시스템.
//KHY - 1111 - 오토바이 추가.
//시간 종량제  종류  - 절대 순서 바뀌면 안됨. DB에 저장되는 값 - index 이자, type정보 이다.
enum
{
	TIMEMETERRATE_TRANSFORM = 1,
	TIMEMETERRATE_MOTORCYCLE,		
	TIMEMETERRATE_END
};

// 각 종류별 설정
#define TIMEMETERRATE_TRANSFORM_CLIENTTIME	10  //10초에 한번.
#define TIMEMETERRATE_TRANSFORM_DBTIME	60

#define MAX_TIMEMETERRATE	TIMEMETERRATE_END 

/*
struct stTimeMeterRate
{
	SI16	siTimeMeterRateType;			// 시간 종량제 종류.
	SI32	siLeftTime;						// 남은 시간 - 사용가능한
	SI64	siUsedTime;						// 이미 사용한 시간.
	DWORD   dwGoClientTime;					// 클라이언트로 이전에 시간정보를 보낸 시간.	
	DWORD   dwGoDBTime;						// DB로 이전에 시간정보를 보낸 시간.	
};
*/

class cltTimeMeterRate
{
public:
	SI16	siTimeMeterRateType;			// 시간 종량제 종류.
	SI32	siLeftTimeSec;					// 남은 시간 - 사용가능한 (초)

	SI32	siUseTimeSec;					// 사용시간 - 서버에서 계산 (초)
	DWORD	dwStartedTime;					// 사용시작 시각

public:
	cltTimeMeterRate()
	{
		Init();
	}
	~cltTimeMeterRate()
	{
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltTimeMeterRate));
	}

	void Set(cltTimeMeterRate *pTimeMeterRate)
	{
		if(pTimeMeterRate == NULL)					return;
		
		siLeftTimeSec		= pTimeMeterRate->siLeftTimeSec;
		siUseTimeSec		= pTimeMeterRate->siUseTimeSec;
		dwStartedTime		= pTimeMeterRate->dwStartedTime;
	}

	SI32 AddLeftTime(SI32 siAddSec)		{	siLeftTimeSec += siAddSec;								return siLeftTimeSec;		}
	SI64 UseTime(SI32 siUseSec)
	{	
		siLeftTimeSec -= siUseSec;	siUseTimeSec += siUseSec;	
		if(siLeftTimeSec <= 0 )		siLeftTimeSec = 0;	
		return siUseTimeSec;
	}

	bool IsUse()
	{
		if( dwStartedTime > 0 )		return true;
		if( siUseTimeSec > 0 )		return true;

		return false;
	}
};

class cltTimeMeterRateInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTimeMeterRate, MAX_TIMEMETERRATE>	m_clTimeMeterRate;
#else
	cltTimeMeterRate	m_clTimeMeterRate[MAX_TIMEMETERRATE];
#endif

	SI32				m_siUseTimePerSec;

	cltTimeMeterRateInfo();

	void Init();

	void SetTimeMeterRate( cltTimeMeterRateInfo* pclinfo );

	void AddLeftTime( SI16 siTimeMeterType, SI32 siAddTimeSec );
	void UseTime( SI16 siTimeMeterType, SI32 siUseTimeSec );
	SI32 GetLeftTime( SI16 siTimeMeterType );

	bool UseStart( SI16 siTimeMeterType );
	bool UseEnd( SI16 siTimeMeterType );

	//type 와 index는 같다.
	cltTimeMeterRate* GetTimeMeterRate( SI16 siTimeMeterRateType );
};

//------------------------------------
// 신분. 
//------------------------------------
#define GRANK_KING			1		// 군주(왕) 
#define GRANK_MINISTER1		2		// 자작(이조판서) 
#define GRANK_MINISTER2		3		// 공작(호조) 
#define GRANK_MINISTER3		4		// ?(예조)
#define GRANK_MINISTER4		5		// 후작(병조) 
#define GRANK_MINISTER5		6		// 남작(형조) 
#define GRANK_MINISTER6		7		// 백작(공조) 

#define GRANK_MC_WOMAN		100		// 여자 MC
#define GRANK_MC_MAN		101		// 남자 MC

//-----------------------------------
// 가장 기본이  되는 캐릭터 정보. 
//-----------------------------------
class cltPBasicInfo{
public:
	SI32		siIDNum;						// 이 Person이 소속된 IDNum
	TCHAR		szAccountID[MAX_PLAYER_NAME];	// 이 Person이 소속된 계정의 아이디. 	
	UI08		uiIndex;		// 캐릭터 슬롯중 몇 번째 슬롯에 위치하는가 ?
	UI08		uiSex;			// 성별, (남자 1, 여자 0)
	UI16 		uiKind;			// 캐릭터의 종류. 
	SI08		siHomeVillage;	// 주소지. 
	UI08		uiGRank;		// 신분. 
	UI08		uiAngelSwitch;	// 수호천사인지 여부. 
	UI08		uiPoliceSwitch;
	cltCharPos	clPos;	// 캐릭터의 위치 
	SI32		siPlaySecond;	// 플레이한 총 누적 시간(초) 
	SI32		siPlayEventSecond;	// 이벤트 시작후 플레이한 총 누적 시간(초) - tys
	cltPos		clLastMainMapPos;	// 야외지도의 최종 위치. 
	SI16		siSchoolUnique;	// 등록 학교의 유니크. 
	
	// 재산 관련 정보. 
	SI32		siWealthRank;		// 재산순위. 
	cltMoney	clTotalWealthMoney;	// 총 재산액. 
	SI32		siWealthCalcDay;	//	재산액을 계산한 날. 

	cltSimplePerson	clPerson;	// 자신의 정보. 

	// 스승 관련 정보.
	cltPFatherInfo clFatherInfo;

	// 추천인 관련 정보
	cltSimplePerson clRecommenderInfo;	// 추천인 정보
	
	SI16	siVoteKingSelectionIndex;	// 투표한 후보의 번호	
	
	bool	bWennyOldManUpgrade;			// 호품 한 적이 있느냐?

	bool	bNewAccount; // 특정일 이후에 가입한 계정인가?
	bool	bGameEvent; // 현재 진행되고 있는 이벤트를 수행했는가?
	bool	bWinPrizeEvent; // 현재 진행되고 있는 이벤트에 당첨되었는가?

	bool	bUseNoLimitTicketWarp ; // 무한워프 하는가?
	SI32	siNoLimitTicketWarpDateVary ; // 무한워프 기간

	UI08	uiGMMode;	// 운영자 모드 설정 (0 : 노멀모드, 1 : GM모드, 2: 하이드 모드)  [3번일때는 전쟁MVP 모드]
	bool	bPCRoom;
	
	TCHAR	sPCroomGrade;	// PC방등급 G , P , S
	
	TCHAR	szCRMcode[16];

	bool	bQuestEvolve; // 퀘스트 진화를 한적이 있느냐?

	TCHAR	szGreeting[128]; // 인사말

	SI32	siCountryID;
	bool	bShowCountry;
	bool	bShowPuchikomi;

	cltSimpleGuildRank	clGuildRank;	// 가입한 길드가 있는 마을 번호
										// 가입한 길드의 인덱스
										// 가입한 길드의 신분 정보
	bool	bPremiumService;		// 프리미엄 서비스 중인가?
	SI32	siPremiumServiceDate;
	bool	bCombatService;		// 전투 프리미엄 서비스 중인가?
	SI32	siCombatServiceDate;
	bool    bMakeItemService;		
	SI32	siMakeItemServiceDate; //제조 프리미엄 서비스 중인가?
	bool	bBulletService;			// 탄환 프리미엄 서비스중인가.
	SI32	siBulletServiceDate;
	bool	bSummonStaminaService;			// 소환수 스태미너 프리미엄 서비스 중인가?
	SI32	siSummonStaminaServiceDate;

	cltVillageScoreInfo clVillageScoreInfo;	// 주민활동 점수
	cltBufInfo clBufInfo;

	//KHY - 1220 - 시간종량제
	cltTimeMeterRateInfo clTimeMeterRateInfo;

	bool	bReceiveBeginnerWeapon;

	// PVP관련해서 추가 -pvp 이긴횟수, 패배한 횟수, 내가 이긴 최고레벨유저 이름
	SI32	siPVPWinNumber;
	SI32	siPVPLoseNumber;
	TCHAR	szPVPWinHighLevelUserName[MAX_PLAYER_NAME];

	bool	bMarKetPremiumService;
	SI32	siMarKetPremiumServiceDate;

	bool	bNewMarketPremiumService;					// [진성] 통합마켓 프리미엄.
	SI32	siNewMarketPremiumServiceDate;

	//// 공간 상자
	bool	bSpaceBoxPremiumService;
	SI32	siSpaceBoxPremiumServiceDate;
	// PCK : 명칭 레벨 관련 정보
	cltPersonNaming clPersonNamaing;

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, ATTEND_EVENTTYPE_MAX>			bAttendToday;
#else
	bool	bAttendToday[ATTEND_EVENTTYPE_MAX];			// 오늘 이미 출석체크 하였는가
#endif
	bool	bIsAttendTime;								// 출석 도장을 찍을 수 있는 시간이 되었는가?
	bool	bIsCanAttend;								// 출석을 할 수 있는가?
	bool	bIsCanReward;								// 보상을 받을 수 있는가?
	SI32	siAttendanceDays;							// 연속 출석일수. 
	CEmpireInfo clEmpireInfo;		// 나의 제국정보
	//KHY - 0906 - 최초 계정 생성 시간.
	_SYSTEMTIME  siFirstCreatTimeDateVary; // 최초 계정 생성 시간.(DateVary)

	bool	bSummonExtraSlot		;				// 소환수 확장 티켓 사용하였는지 여부
	SI32	siSummonExtraSlotDate	;				// 소환수 확장 티켓 사용날자

	UI08	m_uiRealAge;	// 주민등록 상의 실제 나이가 저장(현재 한국만 적용)
public:

	cltPBasicInfo();
	~cltPBasicInfo();
	
	cltPBasicInfo(TCHAR* paccountid, SI32 idnum, UI08 index, UI08 sex, 
		cltSimplePerson* pclperson, UI08 kind, SI08 homevillage, 
		cltCharPos* pclpos, SI32 playsecond, SI32 playeventsecond, 
		SI16 schoolunique, cltPos* pclmainmappos, cltPFatherInfo* pclfather, 
		cltSimplePerson* pclRecommenderInfo, SI16 VoteKingSelectionIndex, 
		SI32 wealthrank, cltMoney totalmoney, SI32 wealthday, 
		bool wennyoldmanupgrade,bool newaccount, bool gameevent , 
		bool winprizeevent,bool nolimitticketwarp , SI32 warpticketdatevary,
        UI08 gmmode , bool pcroom, TCHAR pcroomgrade , TCHAR * crmcode,
		bool bquestevolve, TCHAR* greeting,	cltSimpleGuildRank* pclguildrank ,
		bool premium,SI32 premiumdate,bool combat,SI32 combatdate,
		bool MakeItem, SI32 MakeItemdate, bool BulletService, 
		SI32 BulletServiceDate,	bool SummonStaminaService, 
		SI32 SummonStaminaServiceDate, cltVillageScoreInfo* pclVillageScoreInfo,
		cltBufInfo* pclBufInfo, bool ReceiveBeginnerWeapon, SI32 WinNumber,
		SI32 LoseNumber, TCHAR * HighLevelUserName, bool MarKetPremiumService, 
		SI32 MarKetPremiumServiceDate, bool* bAttendToday, CEmpireInfo* EmpireInfo, _SYSTEMTIME firstcreatTime,
		bool SpaceBoxPremiumService,SI32 SpaceBoxPremiumServiceDate,bool SummonExtraSlot,SI32	siSummonExtraSlotDate,
		bool NewMarketPremiumService, SI32 NewMarketPremiumServiceDate,
		UI08 uiRealAge

		);
		 
	void Set(cltPBasicInfo* pclinfo);

	void Init();
	
	void SetIndex(SI32 index);
	SI32 GetIndex() const;

	void SetKind(SI32 kind);
	SI32 GetKind() const;

	const cltCharPos* GetPos() const;

	void SetMapIndex(SI32 index);
	SI32 GetMapIndex() const;

	void SetX(SI32 x);
	SI32 GetX() const;

	void SetY(SI32 y);
	SI32 GetY() const;

	void SetName(const TCHAR* pname);
	const TCHAR* GetName() const;

	bool IsQuestEvolve();
	void SetQuestEvolve(bool questevolve);

	//KHY - 0906 - 최초 계정 생성 시간.
	_SYSTEMTIME GetFirstCreatTime(){return siFirstCreatTimeDateVary; }

	void GetGMSectionData(GMSectionData* pkGMSectionData);
	void SendInfofromServer(cGMClient* pGMClient);
	
};

//-------------------------------
// 기본이 되는 능력치. 
//-------------------------------
class cltBasicAbility{
public:
	// 기본 능력치.(사용자가 보너스를 가지고 올리는 능력치.) 
	SI32	siStr;				// 근력	
	SI32	siDex;				// 순발력
	SI32	siVit;				// 생명력 
	SI32	siMag;				// 도력 
	SI32	siHnd;				// 손재주. 
	SI32	siLuk;				// 행운 (2005-12-21 추가 by cyj)
	SI32	siWis;				// KHY - 0325 - 지혜 추가.
	

	cltBasicAbility()
	{
		Init();
	}
	cltBasicAbility(SI32 str, SI32 dex, SI32 vit, SI32 mag, SI32 hnd, SI32 luk  ,SI32 Wis)
		:	siStr(str),		siDex(dex),		siVit(vit),		siMag(mag),		siHnd(hnd),		siLuk(luk),	siWis(Wis)
	{
	}

	~cltBasicAbility()
	{
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltBasicAbility));
	}
	void Set(SI32 str, SI32 dex, SI32 vit, SI32 mag, SI32 hnd, SI32 luk,SI32 Wis);
	void Set(cltBasicAbility* pclinfo);

	SI32 GetWis() const;
	void SetWis(SI32 dat);
	SI32 IncreaseWis(SI32 amount);
	SI32 DecreaseWis(SI32 amount);
	
	SI32 GetStr() const;
	void SetStr(SI32 dat);
	SI32 IncreaseStr(SI32 amount);
	SI32 DecreaseStr(SI32 amount);
	SI32 GetStrDamage( bool Person );

	SI32 GetDex() const;
	void SetDex(SI32 dat);
	SI32 IncreaseDex(SI32 amount);
	SI32 DecreaseDex(SI32 amount);

	SI32 GetVit() const;
	void SetVit(SI32 dat);
	SI32 IncreaseVit(SI32 amount);
	SI32 DecreaseVit(SI32 amount);
	
	SI32 GetMag() const;
	void SetMag(SI32 dat);
	SI32 IncreaseMag(SI32 amount);
	SI32 DecreaseMag(SI32 amount);

	SI32 GetHnd() const;
	void SetHnd(SI32 dat);
	SI32 IncreaseHnd(SI32 amount);
	SI32 DecreaseHnd(SI32 amount);

	SI32 GetLuk() const;
	void SetLuk(SI32 dat);
	SI32 IncreaseLuk(SI32 amount);
	SI32 DecreaseLuk(SI32 amount);

	SI32 GetBattleLevel()
	{
		SI32 battleLevel =(SI32)(( 
			sqrt( (double)((siDex-7)*48 ) ) + 
			sqrt( (double)((siVit-6)*14 ) ) 
			)/2);

		battleLevel = max( 1, battleLevel );

		return battleLevel;
	}

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};

//-----------------------------------------
// 마을 투자자 정보
//-----------------------------------------
class cltInvestInfo{
public:
	cltSimplePerson	clPerson;
	SI32			siStockNum;		// 보유 주식수. 

public:
	
	cltInvestInfo();
	
	void Set(cltInvestInfo* pinfo);
	void Init();
	
	SI32 GetStockNum() const;
	void SetStockNum(SI32 num);

};

class cltVillageInvestInfo{
public:
	SI32 siVillageUnique;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltInvestInfo, MAX_INVEST_NUMBER>	clInvestInfo;
#else
	cltInvestInfo clInvestInfo[MAX_INVEST_NUMBER];
#endif

	cltVillageInvestInfo();

	void Set(cltVillageInvestInfo* pclMayorInfo);
	
};

//--------------------------------------
// 건강 상태
//--------------------------------------
#define HEALTH_ORGAN_TYPE_ORG1			1		// 소화기관
#define HEALTH_ORGAN_TYPE_ORG2			2		// 순환기관
#define HEALTH_ORGAN_TYPE_ORG3			3		// 호흡기관
#define HEALTH_ORGAN_TYPE_ORG4			4		// 신경기관

//--------------------------------
// 건강 클래스. (핵심) 
//--------------------------------
class cltHealthInfo{
public:
	//------------------------
	// 기초 상태 
	//------------------------
	SI16 siHungry		;			// 배고픔.		(0~ 256)	기본은 128	

	//-------------------------
	// 기관 상태 
	//-------------------------
	SI08 siInnerOrg1	;		// 소화계 (-100 ~ 100)
	SI08 siInnerOrg2	;		// 순환계 
	SI08 siInnerOrg3	;		// 호흡계 
	SI08 siInnerOrg4	;		// 신경계 

	//------------------------
	// 질병 상태 
	//------------------------
	UI08 uiOrg1Disease	;		// 소화계 질병.			
	UI08 uiOrg2Disease	;		// 순환계 질병. 
	UI08 uiOrg3Disease	;		// 호흡계 질병. 
	UI08 uiOrg4Disease	;		// 신경계 질병. 

	//-----------------------
	// 종합 건강 지수.
	//-----------------------
	UI08 uiHealthPoint;		// 0 ~ 100	:100이면 능력치를 모두 발휘할 수 있따. 

	cltHealthInfo();

	void Init();
	void Set(cltHealthInfo* pclinfo);
	void IncreaseInnerOrg1(SI32 amount);
	void IncreaseInnerOrg2(SI32 amount);
	void IncreaseInnerOrg3(SI32 amount);
	void IncreaseInnerOrg4(SI32 amount);
	bool DecreaseOrg(SI32 type, SI32 amount, SI32 level, bool forceDec = false);	// 내장 기관을 손상시킨다. 

	SI32 GetOrg(SI32 type);		// 내장 기관의 상태를 얻어온다. 

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};

//-------------------------
// 시간정보를 갖는 클래스 
//-------------------------
class cltDate{
public:
	UI32 uiYear:	8;	// 0 ~255
	UI32 uiMonth:	4;	// 0 ~15
	UI32 uiDay:		6;	// 0 ~63
	UI32 uiHour:	5;	// 0 ~31
	UI32 uiMinute:	6;	// 0 ~63
	UI32 uiReserved:3;	

public:

	/*
	void Set(SI32 year, SI32 month, SI32 day, SI32 hour, SI32 minute);
	void Set(const cltDate* pdate);
	
	BOOL Increase
	Time(bool* pbdaychangedswitch, bool bforcetimeswitch);
	BOOL GetDateText(TCHAR* buffer);		// 시간을 문자열로 만든다. 
	void AddMonth(SI32 month);			// 달을 더한다. 
	SI32 GetDateVary();					// 날짜 변수를 구한다. (SI32 변수 하나로 날짜를 모두 뭉뚱그린다) 
	SI32 GetHourVary();					// 시간 변수를 구한다. 
	void MakeFullDateFromDateVary(SI32 datevary);		// DateVary를 가지고 완전 날짜 정보를 조합한다. 
	
	BOOL IsLaterDayThan( cltDate* pclDate );
	BOOL IsLaterMonthThan( cltDate* pclDate );

	void DiffDate( cltDate *pCurrentDate, cltDate *pOldDate );
	SI32 GetDay();
	*/

	void Set(SI32 year, SI32 month, SI32 day, SI32 hour, SI32 minute)
	{
		uiYear		= year;
		uiMonth		= month;
		uiDay		= day;
		uiHour		= hour;
		uiMinute	= minute;
		uiReserved	= 0;
	}

	void Set(const cltDate* pdate)
	{
		memcpy(this, pdate, sizeof(cltDate));						//ok
	}

	SI32 GetDateVary()
	{
		SI32 vary ;
		vary = (uiDay-1) + (uiMonth-1)*30 + (uiYear*12)*30;

		return vary;
	}


	// 시간 변수를 구한다. 
	SI32 GetHourVary()
	{
		return  GetDateVary() * 24 + uiHour;
	}

	SI32 GetMinuteVary()
	{
		return GetHourVary() * 60 + uiMinute;
	}

	// DateVary를 가지고 완전 날짜 정보를 조합한다. 
	void MakeFullDateFromDateVary(SI32 datevary)
	{
		uiYear  = datevary / (12* 30);
		datevary %= (12* 30);

		uiMonth = datevary / 30 + 1;
		datevary %= 30;

		uiDay		= datevary + 1;
		uiHour		= 0;
		uiMinute	= 0;
	}
	
	// HourVary를 가지고 완전 날짜 정보를 조합한다. KHY - 0606 
	void MakeFullHourFromHourVary(SI32 hourvary)
	{
		uiYear    = hourvary / (12 * 30 * 24);
		hourvary %= (12 * 30 * 24);

		uiMonth   = (hourvary / (30 * 24)) + 1;
		hourvary %= (30 * 24);

		uiDay	  = hourvary / 24 + 1;
		uiHour	  = hourvary - ((hourvary / 24) * 24);
		uiMinute  = 0;
	}

	// MinuteVary를 가지고 완전 날짜 정보를 조합한다. by LEEKH 20008-11-11
	void MakeFullHourFromMinuteVary(SI32 minutevary)
	{
		uiYear    = minutevary / (12 * 30 * 24 * 60);
		minutevary %= (12 * 30 * 24 * 60);

		uiMonth   = (minutevary / (30 * 24 * 60)) + 1;
		minutevary %= (30 * 24 * 60);

		uiDay	  = minutevary / (24 * 60) + 1;
		minutevary %= (24 * 60);

		uiHour	  = minutevary / 60;
		minutevary %= 60;

		uiMinute  = minutevary - ((minutevary / 60) * 60);
	}

	SI32 GetDay()
	{
		return min(30, max(1, uiDay));
	}

	BOOL IsLaterDayThan( cltDate* pclDate )
	{

		UI32 a, b;
		a = uiYear * 10000 + uiMonth * 100 + uiDay;
		b = pclDate->uiYear * 10000 + pclDate->uiMonth * 100 + pclDate->uiDay;

		return ( a > b ); 
	}

	BOOL IsLaterMonthThan( cltDate* pclDate )
	{

		UI32 a, b;
		a = uiYear * 100 + uiMonth;
		b = pclDate->uiYear * 100 + pclDate->uiMonth;

		return ( a > b );
	}


	// 달을 더한다. 
	void AddMonth(SI32 addmonth)
	{
		SI32 month = uiMonth;
		month += addmonth;

		SI32 addyear = ( month - 1 ) / 12;
		if(addyear)
		{
			uiYear += addyear;
			month  = (( month - 1 ) % 12) + 1;
		}

		uiMonth = (UI32)month;
	}

	BOOL IncreaseTime(bool* pbdaychangedswitch, bool bforcetimeswitch)
	{
		// 날짜가 변경되지 않았음을 설정한다. (디폴트. ) 
		*pbdaychangedswitch	= false;

		BOOL updateswitch = FALSE;

		uiMinute ++;

		if(bforcetimeswitch)
		{
			if(uiMinute >= 1)
			{
				uiMinute = 0;
				uiHour++;

				// 일정 시간 간간격으로 TRUE 리턴.
				if(uiHour % 2 ==0)
				{
					updateswitch = TRUE;
				}

				if(uiHour >= 1)
				{
					uiHour=0;
					uiDay++;

					// 날짜가 변경되었음을 설정한다. 
					*pbdaychangedswitch	= true;

					// 날짜가 변경되면 반드시 DB에 저장한다. 
					updateswitch = TRUE;

					if(uiDay > 30)
					{
						uiDay = 1;
						uiMonth++;

						if(uiMonth > 12)
						{
							uiMonth = 1;
							uiYear++;
						}
					}
				}
			}
		}
		else
		{

			if(uiMinute >= 60)
			{
				uiMinute = 0;
				uiHour++;

				// 일정 시간 간간격으로 TRUE 리턴.
				if(uiHour % 2 ==0)
				{
					updateswitch = TRUE;
				}

				if(uiHour >= 24)
				{
					uiHour=0;
					uiDay++;

					// 날짜가 변경되었음을 설정한다. 
					*pbdaychangedswitch	= true;

					// 날짜가 변경되면 반드시 DB에 저장한다. 
					updateswitch = TRUE;

					if(uiDay > 30)
					{
						uiDay = 1;
						uiMonth++;

						if(uiMonth > 12)
						{
							uiMonth = 1;
							uiYear++;
						}
					}
				}
			}
		}

		return updateswitch;
	}

	// 시간을 문자열로 만든다.  // %d년 %d월 %d일 %d시 
	BOOL GetDateText(TCHAR* buffer)
	{
		if(buffer == NULL)return FALSE;

		TCHAR* pText = GetTxtFromMgr(3808);
		StringCchPrintf(buffer, 128, pText, uiYear, uiMonth, uiDay, uiHour);

		return TRUE;
	}

	// 시간을 문자열로 만든다.  // %d년 %d월 %d일
	BOOL GetRealDateText(TCHAR* buffer)
	{
		if(buffer == NULL)return FALSE;

		TCHAR* pText = GetTxtFromMgr(1644);
		StringCchPrintf(buffer, 128, pText, uiYear, uiMonth, uiDay);

		return TRUE;
	}


	void DiffDate( cltDate *pCurrentDate, cltDate *pOldDate )
	{
		int temp;

		ZeroMemory( this, sizeof( cltDate ) );

		// minute
		temp = pCurrentDate->uiMinute - pOldDate->uiMinute;
		if( temp < 0 ) { uiMinute = 60 + temp; temp = -1; }
		else { uiMinute = temp; temp = 0; }

		// Hour
		temp += ( pCurrentDate->uiHour - pOldDate->uiHour );
		if( temp < 0 ) { uiHour = 24 + temp; temp = -1; }
		else { uiHour = temp; temp = 0; }

		// Day
		temp += ( pCurrentDate->uiDay - pOldDate->uiDay );
		if( temp < 0 ) { uiDay = 30 + temp; temp = -1; }
		else { uiDay = temp; temp = 0; }

		// Month
		temp += ( pCurrentDate->uiMonth - pOldDate->uiMonth );
		if( temp < 0 ) { uiMonth = 12 + temp; temp = -1; }
		else { uiMonth = temp; temp = 0; }

		// Year
		temp += ( pCurrentDate->uiYear - pOldDate->uiYear );
		uiYear = temp;
	}

};

//----------------------------------------
// 임대계약 정보 
//----------------------------------------
class cltRentContract{
public:
	GMONEY siRentFee;		// 월 임대료. 
	SI32 siRentPeriod;	// 임대기간. 
	cltDate	clDate;		// 계약일시. 

	void Set(GMONEY fee, SI32 period);
	void Set(GMONEY Fee, SI32 Period, cltDate *pclDate );
	void Set(const cltRentContract* pclcontract);
	
	BOOL IsValid();
	BOOL IsSame(const cltRentContract* pclcontract);
	
	bool IsEnd(cltDate* pcldate);			// 계약이 종료되었는가?
	void Init();
	
	void GetRentInfoText( TCHAR *RentInfoText, SI16 txtSize );

};


//-----------------------------------------------
// 말의 정보 
//-----------------------------------------------
#define HORSE_NEED_FEED			1		// 먹이를 줄 것을 요구. 

#define HORSE_REWARDTYPE_SPEED	1
#define HORSE_REWARDTYPE_STR	2
#define HORSE_REWARDTYPE_DEX	3
#define HORSE_REWARDTYPE_MAG	4

class cltHorse{
public:

	SI16 siHorseUnique;
	TCHAR	szName[MAX_HORSE_NAME];		// 이름 
	cltDate clBirthDate;				// 생일 

	SI08	siSex;						// 성별 
	SI08	siPregnentPeriod;			// 임신기간
	SI16	siLife;						// 수명 

	SI16	siStr;
	SI16	siDex;
	SI16	siMag;
	SI16	siMoveSpeed;

	SI32	siStatusBonus;				// 말 보너스

	cltDate clAddStatusDate;			// 말능력향상이용권 바른 일자
	SI32	siStatusTicketNum;			// 말능력향상이용권 몇장 발랐냐

	//------------------------------
	// 마지막으로 업데이트 한 시간. 
	//------------------------------
	SI32	siLastUpdateSecond;
	
	//---------------------------
	// 말의 요구 조건 관련 
	//---------------------------
	SI32	siLastNeedTime;				// 마지막으로 요구했던 시간. 
	SI32	siDueTime;					// 요구조건 충족의 한계 시간. ( 이 시간까지 요구조건을 충족시키지 못하면 실패) 

	SI16	siNeed;						// 말의 요구조건. 
	SI16	siPara1;		
	SI16	siPara2;
	SI16	siSupply;					// 충족 상황. 
	SI16	siRate;						// 말의 요구를 이해할 확률. 

	//--------------------------
	// 보상 관련 
	//--------------------------
	SI16	siRewardType;
	SI16	siRewardAmount;

	//--------------------------
	// 말튜닝관련 관련 
	//--------------------------
	cltDate clPremiumPartsDate_Slot1	;
	SI32	siPremiumUnique_Slot1		;
	cltDate clPremiumPartsDate_Slot2	;
	SI32	siPremiumUnique_Slot2		;
	cltDate clPremiumPartsDate_Slot3	;
	SI32	siPremiumUnique_Slot3		;
	SI32	siPremiumPartsNum			;
public:

	cltHorse();
	cltHorse(SI16 unique, TCHAR* pname, cltDate* pcldate, SI08 sex, SI16 life, SI08 siPregnentPeriod,
			 SI16 str, SI16 dex, SI16 mag, SI16 movepseed, SI32 curhourvary,SI32 bonus
			 ,cltDate* pclstatusdate , SI32 ticketnum
			 ,cltDate* pclPremiumPartsdate_Slot1,SI32 PremiumUnique_Slot1
			 ,cltDate* pclPremiumPartsdate_Slot2,SI32 PremiumUnique_Slot2
			 ,cltDate* pclPremiumPartsdate_Slot3,SI32 PremiumUnique_Slot3
			 ,SI32 PremiumPartsNum);
	
	void Init();
	void Set(cltHorse* pclhorse);	
	
	SI16 GetRealMoveSpeed();			// 게임에 적용될 실제 이동 속도를 구한다.
	SI32 GetAge(SI32 curday);			// 나이를 구한다. 
	bool IsSame(cltHorse* pclhorse);	// 같은 말인지 여부를 판단한다.
	
	// 프리미엄 파츠 정보를 가지고 온다 
	// 슬롯유니크
	SI32 GetPremiumUnique_Slot1(void);
	SI32 GetPremiumUnique_Slot2(void);
	SI32 GetPremiumUnique_Slot3(void);
	// 슬롯의 날짜
	cltDate GetPremiumPartsDate_Slot1(void);
	cltDate GetPremiumPartsDate_Slot2(void);
	cltDate GetPremiumPartsDate_Slot3(void);
	// 이미 같은 파츠를 장착했는지
	bool HaveSamePremiumParts(SI32 siItemUnique);
	// 빈슬롯을 찾는다.
	SI32 FindEmptyPremiumPartsSLot(void);
	// 프리미엄 파츠를 셋팅
	void SetPremiumParts(cltDate* pclDate,SI32 siUnique );

	SI32 GetPremiumPartsNum(void)	;
	void AddPremiumPartsNum( SI32 siNum)	;
	SI32 GetPremiumPartsNum_Slot1(void)		;
	SI32 GetPremiumPartsNum_Slot2(void)		;
	SI32 GetPremiumPartsNum_Slot3(void)		;

	void SetPremiumPartsUnique_Slot1(SI32 siUnique)		;
	void SetPremiumPartsUnique_Slot2(SI32 siUnique)		;
	void SetPremiumPartsUnique_Slot3(SI32 siUnique)		;
};


//-------------------------------------------------
// cltAttackTarget
//-------------------------------------------------
class cltAttackTarget{
public:
	SI32 			siAttackID;                  // 공격할 대상 아이디 
	cltCharPos		clPos;
	
	SI32			siHitRate;						// 공격 대상에 대한 명중률. 
	SI32			siDodgeRate;					// 공격 대상에 대한 회피률. 

	bool			bPVPHit;					// PVP로 상대를 때리는가?

	cltAttackTarget();
	cltAttackTarget(SI32 attackid, const cltCharPos* pclpos, SI32 hitrate, SI32	DodgeRate,bool PVPHit = false);
	
	void Set(const cltAttackTarget* pcltarget);
	void Set(SI32 attackid, const cltCharPos* pclpos, SI32 hitrate, SI32 DodgeRat, bool PVPHit = false);
	void Init();
	
	void SetAttackID(SI32 id);
	SI32 GetAttackID() const;
	
	void SetDodgeRate(SI32 siDodgeRate);
	SI32 GetDodgeRate(){return siDodgeRate;} 

};

//---------------------------------
// 전과 기록. 
//---------------------------------
#define MAX_PRISON_REASON_SIZE	50
#define MAX_PRISON_SECOND		30
#define MAX_PRISON_LIST_NUM		50 // 형조판서 창에서 보여줄 리스트 총 갯수

struct HyungzoMember
{
	SI32	siDate;										// 수감설정일
	SI32	siPrisonSecond;								// 수감시간
	TCHAR	szCharName[MAX_PLAYER_NAME];				// 수감자
	TCHAR	szPrisonReason[MAX_PRISON_REASON_SIZE];		// 수감이유
};

class cltGuiltyInfo{
public:
	SI32	siTotalPrisonSecond;			// 총 수감시간. 
	SI32	siLeftPrisonSecond;			// 남은 수감시간. 
	TCHAR	szPrisonReason[MAX_PRISON_REASON_SIZE];
	SI32	siTotalPrisonNum;

	cltGuiltyInfo();
	
	void Init();
	void Set(cltGuiltyInfo* pclinfo);
	void SetTotalPrisonSecond(SI32 second);
	void SetLeftPrisonSecond(SI32 second);
	void SetPrisonReason(TCHAR * reason);
	void SetPrisonNumber(SI32 num);
	
};

//----------------------------------------------
// 수렵장 저장 정보 
//----------------------------------------------
class cltHuntStg{
public:
	SI16 siItemUnique;
	SI16 siItemNum;

	void Set(cltHuntStg* pclstg);
	
};

class cltHuntLineUp{
public:
	SI16 siLineUpKind;		// 전선에 배치된 몬스터 종류
	SI16 siLineUpKindNum;	// 전선에 배치된 몬스터 수량
	SI16 siLineUpKindLevel; // 전선에 배치된 몬스터 레벨

	void Set(cltHuntLineUp* pclinfo);

};

#define MAX_FEAST_PRESENT_NUMBER							10
#define MAX_FEAST_STG_NUMBER								10

// 내자시 창고 정보
class cltFeastStg 
{
public:
	SI16 siItemUnique;
	SI16 siItemNum;
	
	void Set( cltFeastStg* pclstg );

};


//-----------------------------------------
// 스승 등록 신청자 정보. 
//-----------------------------------------
#define MAX_FATHER_APPLYER_LIST_NUMBER	50

class cltFatherApplyerInfo{
public:
	SI16 siCharUnique;
	SI32 siPersonID;
	SI16 siLevel;
	SI16 siFameLevel;
	bool bAngelSwitch;					// 수호천사인지 여부. 
	TCHAR szAccountID[MAX_PLAYER_NAME];
	//NTCHARString<MAX_PLAYER_NAME>	szAccountID;
	TCHAR szName[MAX_PLAYER_NAME];
	//NTCHARString<MAX_PLAYER_NAME>	szName;

	cltFatherApplyerInfo();
	cltFatherApplyerInfo(SI16 charunique, SI32 personid, TCHAR* pname, TCHAR* paccountid, SI16 level, SI16 famelevel, bool bangel);

	void Init();
	void Set(cltFatherApplyerInfo* pclinfo);

};

//-------------------------------------
// 제자 1인의 정보. 
//-------------------------------------
class cltChildInfo{
public:
	cltSimplePerson clPerson;
	SI16			siLevel;
	TCHAR			szAccountID[MAX_PLAYER_NAME];

	
	cltChildInfo();
	cltChildInfo(cltSimplePerson* pclperson, SI16 level,TCHAR * accountID);
	void Init();
	void Set(cltChildInfo* pclchild);
	
};

//------------------------------
// Person친구 정보. 
//------------------------------
#define FRIEND_GROUP_UNKNOWN	0
#define FRIEND_GROUP_1			1
#define FRIEND_GROUP_2			2
#define FRIEND_GROUP_3			3
#define FRIEND_GROUP_4			4

#define MAX_FRIEND_GROUP					5		// 0번은 그룹없음 그룹
#define	MAX_FRIEND_NUMBER					100

#define MAX_FRIEND_NOTESIZE					201		// 50자 까지 메모 가능
class cltPFriendInfo{
public:
	TCHAR szGroupName[MAX_FRIEND_GROUP][MAX_FRIEND_GROUPNAME];
#ifdef _SAFE_MEMORY
	NSafeTArray<SI08, MAX_FRIEND_NUMBER>				siGroupID;
	NSafeTArray<cltSimplePerson, MAX_FRIEND_NUMBER>		clFriend;
#else
	SI08 siGroupID[ MAX_FRIEND_NUMBER ];
	cltSimplePerson clFriend[MAX_FRIEND_NUMBER];
#endif
	TCHAR szAccountID[MAX_FRIEND_NUMBER][MAX_PLAYER_NAME];

	void Set(cltPFriendInfo* pclinfo);
};

class cltFriendInfo : public cltPFriendInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_FRIEND_NUMBER>		siCharID;
	NSafeTArray<bool, MAX_FRIEND_NUMBER>		bConnectStatus;
#else
	SI32 siCharID[ MAX_FRIEND_NUMBER ];
	bool bConnectStatus[ MAX_FRIEND_NUMBER ];
#endif
//	TCHAR szAccountID[ MAX_FRIEND_NUMBER ][MAX_PLAYER_NAME];

	void Init();
	void Init( SI16 Index );
	
	void Set( SI16 Index, SI08 GroupID, SI32 PersonID, SI32 CharID, TCHAR *CharName, bool ConnectStatus ,TCHAR *AccountID);
	void Set( SI16 Index, SI08 GroupID, SI32 CharID, bool ConnectStatus ,TCHAR * AccountID);
	void Set( cltPFriendInfo *pclInfo );
	void Set( cltFriendInfo *pclInfo );
	
	SI16 GetFriendNum();

};
// 케릭터 옵션 정보
// [ 추가 ] PVP < 2008-10-9 >
//====================================
// cltPDailyQuestInfo
//====================================
class cltPCharOptionInfo
{
	public:
		bool bChatSetNormal		;
		bool bChatSetVillage	;
		bool bChatSetGuild		;
		bool bChatSetParty		;
		bool bChatSetSystem		;
		bool bPvpMode			;	//PVP를 거절 할 것인가.

	cltPCharOptionInfo();
	void Init()	;
	void Set( bool ChatSetNormal,bool ChatSetVillage,bool ChatSetGuild, bool ChatSetParty,bool ChatSetSystem, bool pvpmode )	;
	void Set( cltPCharOptionInfo *pclInfo )	;
	void SetChatSetNormal( bool ChatSetNormal )	;
	void SetChatSetVillage( bool ChatSetVillage )	;
	void SetChatSetGuild( bool ChatSetGuild )	;
	void SetChatSetParty( bool ChatSetParty )	;
	void SetChatSetSystem( bool ChatSetSystem )	;
	void SetPVPMode( bool pvpmode )	;
	bool GetPVPMode()	;
	
};

class cltPDailyQuestInfo
{
public:
	SI16 siMonsterKind;
	SI16 siMonsterNum;

	SI16 siRewardItemUnique;
	SI16 siRewardItemNum;
	GMONEY siRewardMoney;
	SI32 siRewardExp;

	GMONEY siFee;
	SI32 siQuestTime;	// 총 시간
	SI32 siLeftTime;    // 남은 시간

	SI16 siKillMonsterNum;

	BOOL bMoneySelected;

	cltPDailyQuestInfo();

	void Init();
	void Set( SI16 MonsterKind, SI16 MonsterNum, SI16 RewardItemUnique, SI16 RewardItemNum, GMONEY RewardMoney, SI32 RewardExp, GMONEY Fee, SI32 QuestTiem, SI32 LeftTime, SI16 KillMonsterNum, BOOL MoneySelected );
	void Set( cltPDailyQuestInfo *pclInfo );
	BOOL IsSame(cltPDailyQuestInfo *pclInfo );
};
//데일리 퀘스트 2 
class cltPDailyQuest2Info
{
public:
	SI16 siMonsterKind;
	SI16 siMonsterNum;

	SI16 siRewardItemUnique;
	SI16 siRewardItemNum;
	GMONEY siRewardMoney;
	SI32 siRewardExp;

	GMONEY siFee;
	SI32 siQuestTime;	// 총 시간
	SI32 siLeftTime;    // 남은 시간

	SI16 siKillMonsterNum;

	BOOL bMoneySelected;

	bool bHiddenQuest;

	cltPDailyQuest2Info();

	void Init();
	void Set( SI16 MonsterKind, SI16 MonsterNum, SI16 RewardItemUnique, SI16 RewardItemNum, GMONEY RewardMoney, SI32 RewardExp, GMONEY Fee, SI32 QuestTime, SI32 LeftTime, SI16 KillMonsterNum, BOOL MoneySelected, bool HiddenQuest );
	void Set( cltPDailyQuest2Info *pclInfo );
	BOOL IsSame(cltPDailyQuest2Info *pclInfo );
};
//데일리 퀘스트 3 
class cltPDailyQuest3Info
{
public:
	SI32 siItemUnique;
	SI32 siItemNum;

	SI32 siRewardItemUnique;
	SI32 siRewardItemNum;
	SI32 siRewardExp;

	GMONEY siFee;
	SI32 siQuestTime;	// 총 시간
	SI32 siLeftTime;    // 남은 시간

	SI16 siMadeItemNum;

	BOOL bMoneySelected;

	bool bHiddenQuest;

	cltPDailyQuest3Info();

	void Init();
	void Set( SI32 ItemQnique, SI32 ItemNum, SI32 RewardItemUnique, SI32 RewardItemNum,SI32 RewardExp, GMONEY Fee, SI32 QuestTiem, SI32 LeftTime, SI16 MakedItemNum, BOOL MoneySelected, bool HiddenQuest);
	void Set( cltPDailyQuest3Info *pclInfo );
	BOOL IsSame(cltPDailyQuest3Info *pclInfo );
};

//--------------------------------------
// 재료
//--------------------------------------
class cltMaterialInfo {
public:
	SI32	siUnique;		// 재료의 유니크. 
	SI32	siNeedNum;		// 재료의 필요 개수. 

	cltMaterialInfo();
	cltMaterialInfo(SI32 unique, SI32 itemnum);

	void Set(cltMaterialInfo* pclmaterial);
	void Set(SI32 unique, SI32 itemnum);

};

//--------------------------------------
// 도구
//--------------------------------------
class cltToolInfo {
public:
	SI32	siUnique;		// 도구의 유니크. 

	cltToolInfo();
	cltToolInfo(SI32 unique);
	void Set(cltToolInfo* pcltool);
	void Set(SI32 unique);
	
};

inline void NTraceF(TCHAR* pszFormat, ...)
{
	TCHAR	szBuf[2048];
	va_list	ar;

	va_start(ar, pszFormat);

	wvsprintf(szBuf, pszFormat, ar);
	OutputDebugString(szBuf);

	va_end(ar);
}

//--------------------------------------
// PVP 무한대전 정보
//--------------------------------------
const SI32 Const_PVP_League_Latest_Max	= 5;	// 최신 경기 목록 최대 갯수
const SI32 Const_PVP_League_Top_Max		= 10;	// 상위 유저 목록 최대 갯수

enum PVPLEAGUE_RESULT
{
	PVPLEAGUE_RESULT_NONE	= 0,
	PVPLEAGUE_RESULT_WIN,
	PVPLEAGUE_RESULT_LOSE,
	PVPLEAGUE_RESULT_DRAW,
	PVPLEAGUE_RESULT_LOGOUT,
};

class cltPVP_League_OtherUserInfo
{
public:
	SI16	siLevel;
	SI08	siGrade;
	SI08	siResult; // PVPLEAGUE_RESULT

	SI32	siWin;
	SI32	siLose;
	SI32	siDraw;

	TCHAR	szName[MAX_PLAYER_NAME];
	
	cltPVP_League_OtherUserInfo()
	{
		ZeroMemory( this, sizeof(cltPVP_League_OtherUserInfo) );
	}

	~cltPVP_League_OtherUserInfo()
	{
	}

	void Set( cltPVP_League_OtherUserInfo* pclParam )
	{
		if ( pclParam )
		{
			memcpy( this, pclParam, sizeof(cltPVP_League_OtherUserInfo) );
		}
	}
};

//[진성] 엘릭서.
class cltElixir
{
public:
	enum { 
			LIMIT_MULTIPLE =   3,		// 엘릭서 배수 제한.
			WATER_MILTIPLE =  10,		// 엘릭서 사용시 물약 개수에 적용되는 배수.
		};


public:
	cltElixir() { ZeroMemory( this, sizeof(*this) );	}
	~cltElixir(){										}

public:
	SI16 		GetPoint( void )						{ return m_siPoint;						}
	void 		SetPoint( SI16 _siPoint)				{ m_siPoint = _siPoint; 				}

	SI16 		GetStr( void )							{ return m_siStr;						}
	void 		SetStr( SI16 _siStr)					{ m_siStr = _siStr; 					}

	SI16 		GetDex( void )							{ return m_siDex;						}
	void 		SetDex( SI16 _siDex)					{ m_siDex = _siDex; 					}

	SI16 		GetVit( void )							{ return m_siVit;						}
	void 		SetVit( SI16 _siVit)					{ m_siVit = _siVit; 					}

	SI16 		GetMag( void )							{ return m_siMag;						}
	void 		SetMag( SI16 _siMag)					{ m_siMag = _siMag; 					}

	SI16 		GetHnd( void )							{ return m_siHnd;						}
	void 		SetHnd( SI16 _siHnd)					{ m_siHnd = _siHnd; 					}

	SI16 		GetWis( void )							{ return m_siWis;						}
	void 		SetWis( SI16 _siWis)					{ m_siWis = _siWis; 					}

	cltDate*	GetEndDate( void )						{ return &m_clEndDate;					}
	SI32		GetMinuteVary( void )					{ return m_clEndDate.GetMinuteVary();	}
	void		SetEndMinuteVary( SI32 _siEndDateVary )	{ m_clEndDate.MakeFullHourFromMinuteVary( _siEndDateVary );		}

	UI08		GetMultiple( void )						{ return m_siMultiple;					}
	void		SetMultiple( UI08 _siMultiple)			{ m_siMultiple = _siMultiple;			}	

	SI16		GetTotalPoint( void )					{ return m_siPoint + m_siStr + m_siDex + m_siVit + m_siMag + m_siHnd + m_siWis; }

public:
	enum{ TYPE_STR, TYPE_DEX, TYPE_MAG, TYPE_VIT, TYPE_WIS, TYPE_HND, TYPE_POINT };

	bool IsElixir( void )
	{
		if( 0 < GetMultiple() && LIMIT_MULTIPLE >= GetMultiple() )	return true;

		return false;
	}
	
	SI16* GetTypePointer( SI32 _Type )
	{
		switch( _Type )
		{
			case TYPE_STR:		return &m_siStr; 
			case TYPE_DEX:		return &m_siDex; 
			case TYPE_VIT:		return &m_siVit; 
			case TYPE_MAG:		return &m_siMag; 
			case TYPE_HND:		return &m_siHnd; 
			case TYPE_WIS:		return &m_siWis; 
			
			default: return NULL;
		}
	}
	bool Calculation( SI32 _Type, SI32 _Value, cltElixir* _pclPrevElixir = NULL )
	{
		SI16* pType = GetTypePointer( _Type );
		if( NULL == pType )	return false;

		if( _pclPrevElixir ) 
		{
			SI16* pPrevType = _pclPrevElixir->GetTypePointer( _Type );

			if( 0 < _Value )	_Value = min( m_siPoint, _Value );
			else				_Value = max( *pPrevType - *pType, _Value );

			if( *pPrevType				   > *pType	   + _Value ) return false;
			if( _pclPrevElixir->GetPoint() < m_siPoint - _Value ) return false;
		}

		if( 0 > *pType	  + _Value ) return false;
		if( 0 > m_siPoint - _Value ) return false;

		*pType		+= _Value;
		m_siPoint	-= _Value;

		return true;
	}

private:
	cltDate	m_clEndDate;			// 엘릭서 사용이 끝나는 시간.
	UI08	m_siMultiple;			// 엘릭서 사용 배수. 

	SI16	m_siPoint;				// 포인트.
	SI16	m_siStr;				// 근력	
	SI16	m_siDex;				// 순발력
	SI16	m_siVit;				// 생명력 
	SI16	m_siMag;				// 도력 
	SI16	m_siHnd;				// 손재주. 
	SI16	m_siWis;				// 지혜 추가.
};
// 서버랑 둘다 써야 하는 데이터라 여기에 올리는 강수
#define MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT	3	// 한 라쿤이벤트에서 선택할수 있는 최대한의 필드콤보박스 인덱스 갯수
#define MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT	3	// 하루가능한 자이언트 라쿤의 횟수 3회 
#define MAX_MONSTER_NUM_GOONZURACCOONEVENT	3		// 최대 생성 몬스터 3마리
#define MAX_HOUR_GOONZURACCOONEVENT	23				// 하루는 24시간 이지만 0시부터 ~23시까지 시간을 표기 한다 표기시간은 23시까지기때문에 24시는 00 시 
class RocData
{
public:
	/*void SetRoc(TCHAR* pMapname, SI32 siX, SI32 siY)
	{ 
		SetMapName(pMapname)	;
		SetX(siX);
		SetY(siY);
	}*/
	void SetRoc(SI32 siMapIndex, SI32 siX, SI32 siY)
	{ 
		SetMapindex(siMapIndex)	;	// 작은풀숲 등의 맵인덱스는 없다. 그렇기 때문에 해당 맵이름을 보여주기위해서 맵인덱스에 텍스트매니저 번호를 넣는다.
		SetX(siX);
		SetY(siY);
	}
	/*void SetMapName(TCHAR* szMapName)
	{ 
		MStrCpy(m_szMapName, szMapName, sizeof(m_szMapName));
	}*/
	void SetMapindex(SI32 siMapindex){ m_siMapIndex = siMapindex; }
	void SetX(SI32 siX){ m_siX = siX;}
	void SetY(SI32 siY){ m_siY = siY;}

	//TCHAR* GetMapName(){return m_szMapName; }
	SI32 GetMapIndex(){return m_siMapIndex	;}
	SI32 GetX(){ return m_siX; }
	SI32 GetY(){ return m_siY; }
	//TCHAR m_szMapName[50];
	SI32 m_siMapIndex	;
	SI32 m_siX	;
	SI32 m_siY	;
};
class cGoonzuRaccoonEventData
{
public:
	void init()
	{ 
		m_siTime = 0 ;
		m_siMakeMonsterNum = 0 ;
		m_RocData[0].SetRoc(0,0,0)	;
		m_RocData[1].SetRoc(0,0,0)	;
		m_RocData[2].SetRoc(0,0,0)	;
	};
	void SetTime( SI32 siTime){ m_siTime = siTime ;}
	void SetMakeMonsterNum(SI32 siNum){ m_siMakeMonsterNum = siNum ;}
	/*void SetMapName( SI32 siArrayIndex, TCHAR* szMapname)
	{
		m_RocData[siArrayIndex].SetMapName( szMapname );
	}*/
	void SetMapIndex( SI32 siArrayIndex, SI32 siMapIndex)
	{
		m_RocData[siArrayIndex].SetMapindex( siMapIndex );
	}
	void SetMapRocX( SI32 siArrayIndex, SI32 siX)
	{
		m_RocData[siArrayIndex].SetX(siX);
	}
	void SetMapRocY( SI32 siArrayIndex, SI32 siY)
	{
		m_RocData[siArrayIndex].SetY( siY );
	}
	
	SI32 GetTime(){ return m_siTime ; }
	SI32 GetMonsterNum(){ return m_siMakeMonsterNum ; }
	/*TCHAR* GetRocName( SI32 ArrayIndex)
	{
		if ( ArrayIndex >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ) return	0	;
		return m_RocData[ArrayIndex].GetMapName()	;
	}*/
	SI32 GetRocIndex( SI32 ArrayIndex)
	{
		if ( ArrayIndex >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ) return	0	;
		return m_RocData[ArrayIndex].GetMapIndex()	;
	}
	SI32 GetRocX( SI32 ArrayIndex)
	{
		if ( ArrayIndex >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ) return	0	;
		return m_RocData[ArrayIndex].GetX();
	}
	SI32 GetRocY( SI32 ArrayIndex)
	{
		if ( ArrayIndex >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ) return	0	;
		return m_RocData[ArrayIndex].GetY();
	}
	SI32 m_siTime	;			// 만들 시간
	SI32 m_siMakeMonsterNum	;	// 해당 시간에 만들어낼 대왕구리덱 숫자
	RocData m_RocData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT]	;	// 만들어낼 맵좌표 데이터 
};


// 유저의 블럭 로그관련 정보
class cltUserBlockLog
{
public:
	UI08	m_uiWarnMode;							// 경고모드
	UI08	m_uiBlockMode;							// 블럭모드
	TCHAR	m_szBlockReason[MAX_BLOCKREASON_SIZE];	// 블럭사유
	TCHAR	m_szStartDate[24];						// 시작일
	TCHAR	m_szEndDate[24];						// 종료일

public:
	cltUserBlockLog( void )		{	ZeroMemory(this, sizeof(*this));	}
	~cltUserBlockLog( void )	{}
	
	void Init( void )			{	ZeroMemory(this, sizeof(*this));	}

};

#endif
