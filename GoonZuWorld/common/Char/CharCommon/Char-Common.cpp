#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"
#include "..\..\Server\Server.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
//--------------------------------------
// CommonLogic
//--------------------------------------
#include "MsgType-Person.h"
#include "Feast/Feast.h"
//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"

//-------------------------------------------
//Server
//-------------------------------------------
#include "..\..\Server\Statistics\Statistics.h"

#include "..\..\Client\Music\Music.h"
#include "..\common\NPCManager\NPC.h"

#include "..\..\Bullet\Bullet.h"
#include "Util\Util.h"
#include "..\..\Order\Order.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

#include "Skill\Skill-Manager.h"
#include "Char\CharServer\Char-Server.h"

#include "..\..\CommonLogic\MagicMgr\MagicMgr.h"
#include "../../../CommonLogic/Guild/GuildWar.h"
#include "..\..\..\CommonLogic\MagicMgr\MagicAttribute\MagicAttribute.h"
#include "..\..\CommonLogic\MsgRVal-Define.h"
#include "..\..\Common\SystemNPC\SystemNPC.h"

#include "../../Map/MapManager/MapManager.h"
#include "../../../CommonLogic/CityHall/CityHall.h"

#include "..\..\Client\NInterface\NNewInventory\NNewInventory.h"
#include "../../common/VoteMgr/VoteBaseInfo.h"
#include "../../common/Event/event.h"
#include "../../Server/ServerEvent/ServerEvent_Manager.h"

#include "../../CommonLogic/Marriage/MarriageManager.h"
#include "../../CommonLogic/Marriage/WeddingManager.h"

#include "../../CommonLogic/MsgType-Person.h"

#include "ITZCell.h"

extern cltCommonLogic* pclClient;

//-------------------------------------
// cltCharCommon
//-------------------------------------
cltCharCommon::cltCharCommon()
{
	siAccountStatus = 0;
	siIDNUM = 0;

	pclMap		= NULL;
	

	pclCM		= NULL;
	pclKI		= NULL;
	pclGMCommandKindInfo = NULL;
	pclCI		= new cltPersonInfo();

	//_LEON_GUILD
	//------------------------------------
	// 개인별 길드경험치 누적 관련 임시 변수
	//-----------------------------------
    siExpForMyGuild = 0;		// 길드 탈퇴시 초기화 필요
	//------------------------------------
	// 개인별 길드이익금 누적 관련 임시 변수
	//-----------------------------------
    clProfitForMyGuild.Init();	// 길드 탈퇴시 초기화 필요

	if(pclCI)
	{
		// 파라메타를 연결한다.
		clPB.pclCI				= pclCI;
	}
	
	// 파라메타 박스를 초기화한다. 
	clPB.Init(pclClient->pclItemManager, &(pclCI->clIP), &pclCI->clHealthInfo, pclKI, pclGMCommandKindInfo);


	siCenterX	= 0;
	siCenterY	= 0;

	//-------------------------------------------
	// 현재 명령 초기화 
	//-------------------------------------------
	clCurOrder.Init();

	//-------------------------------------------
	// 다음 명령 초기화. 
	//-------------------------------------------
	ReserveOrder.Init();

	siSubOrder		= 0;
	bBusySwitch		= false;
	
	
	
	//-----------------------------
	// 신분
	//-----------------------------
	siID				= 0;
	CharUnique			= 0;
	clIdentity.Init();
	siChildCharUnique	= 0;
	siSummonIndex		= 0;

	//-----------------------------
	// 수호정령
	//-----------------------------
	siMySoulGuardUnique		= 0;
	clockSoulGuardCoolTime	= 0;

	bGodMode		= false;
	bOneKill		= false;	// 원킬모드
	
	clAddInfo.Init();

	siCurrentAttackType	= 0;

	//-----------------------------
	// 속성들 
	//----------------------------
	Atb	= 0;                            // 객체의 속성 
	DefenceAtb	= 0;

	bActiveNPC = FALSE;

	//-------------------------------
	// 충돌 관련 변수. 
	//-------------------------------
	SelfBlock	= 0;
	Block		= 0;
	SetIDSwitch	= FALSE;

	//----------------------------------
	// 출력과 관계된 변수들 
	//----------------------------------
	Animation				= 0;
	HeroAnimation			= 0;
	bUpdateAnimationSwitch	= false;
	Frame					= 0;

	MaxWaitType		= 0;
	WaitType		= 0;

	//----------------------------
	// 방향 
	//----------------------------
	siDirection		= 0;
	TempDirection	= 0;
	TargetDirection	= 0;

	//------------------------------
	// 공격관련 
	//------------------------------
	dwAttackGiveUpDelay			= 0;
	dwLastAttackClock			= 0;
	dwLastAttackIntervalClock	= 0;
	dwLastMagicClock			= 0;
	dwLastTorpedoClock			= 0;

	ActiveWeapon				= PERSONITEM_WEAPON1;
	ActiveClothes               = PERSONITEM_DRESS;
	ActiveHat                   = PERSONITEM_HAT;

	//---------------------------
	// 이동. 
	//---------------------------
	clMoveInfo.Init();
	siMoveMapIndex	= -1;

	//-----------------------------
	// 장인 정보 
	//-----------------------------
	siReservedTopSkillUnique	= 0;		// 설정 예약되어 있는 탑 기술 


	//---------------------------
	// 농사 
	//---------------------------
	siFarmX	= siFarmY	= 0;

	//---------------------------
	// 채굴
	//---------------------------
	siMineX	= siMineY	= 0;

	
	//----------------------------
	// 애니메이션 
	//---------------------------
	pclCharDraw	= NULL;
	bHitDoneSwitch	= false;

	//------------------------------------
	// 현재 선택된 마법 
	//------------------------------------
	siCurrentMagic			= 0;
	siCurrentMagicCastType	= 0;

	//------------
	// 중독 관련 
	//------------
	siPoisonCharUnique = 0;			// 나를 중독시킨 캐릭터 유니크. 
	dwPoisonLastClock = 0;			// 중독의 지연시간. 
	dwPoisonStartClock = 0;			// 중독 시작시간. 
	siPoisonPower = 0;				// 중독의 강도. 
	dwPoisonCheckClock = 0;

	//-------------
	// 얼음 관련 
	//-------------
	dwIceLastClock = 0;
	dwIceStartClock = 0;

	//-------------
	// 공격력 저하 저주 관련 
	//-------------
	dwCurseAttackStartClock = 0;
	dwCurseAttackLastClock = 0;
	siCurseAttackPower = 0;			// 강도. 

	//-------------
	// CRITICAL 저하 저주 관련 
	//-------------
	dwCurseCriticalStartClock = 0;
	dwCurseCriticalLastClock  = 0;
	siCurseCriticalPower = 0;		// 강도. 

	//------------
	// 몸에 붙는 마법불 관련 
	//------------
	siMagicFireCharUnique = 0;			// 불을 붙인 캐릭터 유니크. 
	dwMagicFireLastClock = 0;			// 불의 지연시간. 
	dwMagicFireStartClock = 0;			// 불 시작시간. 
	siMagicFirePower = 0;				// 불의 강도. 
	dwMagicFireCheckClock = 0;

	//-------------
	// DRAIN 관련 
	//-------------
	bDrainSwitch = false;
	siDrainFrame = 0;
	
	uiStaminaFrame = 0;

	//--------------
	// 피격
	//--------------
	bHitSwitch	= false;		// 피격 중인지 여부. 

	//-------------------
	// 전쟁 
	//-------------------
	siWarEnemyKillNumber	= 0;	// 전쟁에서 처치한 적의수. 
	siWarKilledNumber		= 0;
	siBlackArmyWarMapIndex	= -1;

	//-------------------
	// 흑의군단 전쟁 
	//-------------------
	siBlackWarEnemyKillNumber = 0;
	siBlackWarKilledNumber = 0;
	siBlackWarEnemyKillScore = 0;
	siBlackWarEnemyKillVillageScore = 0;

	//------------------------------------
	// 모후모후 이벤트
	//------------------------------------
//	siMofuMofuEventField	= -1;

	//------------------------------------
	// 운영자 권한 등급. 
	//------------------------------------
	siGameMasterLevel	= 0;

	//------------------------------------
	// 찜
	//------------------------------------
	clJim.Init();

	//------------------------------------
	// 파티 인덱스.
	//------------------------------------
	siPartyIndex	= 0;
	
	//------------------------------------
	// 만들어진 프레임
	//------------------------------------
	dwMakeFrame		= 0;

	//-------------------------------------
	// 선공 방어 여부. 
	//-------------------------------------
	bNoFirstAttackSwitch	= false;
	//-------------------------------------
	// ICE 방어 여부. 
	//-------------------------------------
	bNoIceAttackSwitch		= false;

	//-------------------------------------	
	// [진성] 버프 룰렛 작동중이면 주사위모냥 띄우기. => 2008-6-10
	//-------------------------------------
	bBuffRouletteSwitch		= false;

	//-------------------------------------	
	// [진성] 엘릭서.
	//-------------------------------------
	bElixirSwitch			= false;
	
	//-------------------------------------	
	// [성웅] 현제 PVP 상대방이 있다.
	//-------------------------------------
	siEnemUnique			= 0	;
	//-------------------------------------	
	// [성웅] 현제 PVP 기다리는 시간 
	//-------------------------------------
	siPVPWaitTime			=	0	;
	//-------------------------------------	
	// [성웅] 라쿤이벤트 시작 기다리는 시간
	//-------------------------------------
	siRacoonDodgeWaitTime	=	0	;
	//-------------------------------------	
	// [성웅] 현제 PVP 싸우는 시간
	//-------------------------------------
	siPVPTime				=	0	;
	//-------------------------------------	
	// [성웅] 현제 끝난시간
	//-------------------------------------
    siPVPEndTime			=	0	;
	//-------------------------------------	
	// [성웅] 발렌타인데이 이벤트를 위해 자신이 솔로인지 커플인지 대답한 시간.
	//-------------------------------------
	dwValentineAnswerTime	=	0	;
	//-------------------------------------	
	// [성웅] 현제 PVP 기다리는 시간동안 상대방 ID 기록 
	//-------------------------------------
	siPVPWaitRequestId		=	0	;
	siPVPWaitAcceptId		=	0	;
	//-------------------------------------	
	// [성웅] PVP시작 전 카운트 다운을 한다.
	//-------------------------------------
	bPvpCountDown			=	false	;
	// PVP 결과
	siPVPWin				=	false	;
	siPVPLose				=	false	;
	siPVPDraw				=	false	;
	bPvpLeague				=	false	;

	//-------------------------------------	
	// PVP 리그전 관련
	//-------------------------------------	
	pclPVP_LeagueInfo		= NULL;
	pcltElixir				= NULL;
	pclMarriage				= NULL;
	pclFamily				= NULL;

	pclSoulGuard			= NULL;
	pclCharSkillBookInfo	= NULL;

	//-------------------------------------
	// 하트 이펙트 여부.  ( 클라이언트에서만 유효하게 쓰인다. 서버에선 BUF_LOVEPOWER, BUF_FRIENDSHIP 두개가 중복된 경우이다 )
	//-------------------------------------
	bHeartEffectSwitch		= false;

	siBufTransformKind		= 0;

	//clFriendInfo.Init();
	pclFriendInfo			= NULL;
	// [성웅] 라쿤이벤트 시작 전에 머리위에 카운트 이미지를 그린다
	bRacoonDodgeEventCountDown		=	false	;

	// [지연] 복불복 이벤트 : 그래픽 리소스 출력 : 5초 카운트
	bBBBEvent_5SecCountDownFlag		= false;
	bBBBEvent_StageFailFlag			= false;
	bBBBEvent_StageClearFlag		= false;
	bBBBEvent_TotalStageClearFlag	= false;
	siBBBEvent_TotalStageClearResultImageIndex = 0;

	//--------------------------
	// 배틀로얄 파워업 모드 상태 인지
	//--------------------------
	bBattleRoyalPowerupMode = false;

	//-------------------------------------
	// 사망시 사용되는 변수. 
	//-------------------------------------
	bDyingSwitch	= false;

	//-------------------------------------
	// 개인상점 
	//-------------------------------------
	bPersonalShopSwitch	= false;		// 개인상점이 열려 있는가?
	
	bPremiumPersonalShop = false;

	bRepairShopSwitch	= false;

	//----------------------------
	// 현재 제조중인가 
	//----------------------------
//	siPersonalMakeItemType = 0;


	bPersonalEnchantItemSwitch  = false;

	// 현재 레벨업을 해서 레벨업 동작인가
	bLevelUpDrawSwitch = false;

	//-------------------------------------------------
	// 소환수 및 사용자간 컨트롤 // -1이면 PC자신
	//-----------------------------------------------
	siSelectedCharIndex = -1 ;

	//[진성] 핸드폰 인증 여부.
	bCellularPhoneAuth  = false;
	bIsPromoter			= false;


	//-------------------------------------
	// 캐릭터의 이벤트 정보. 
	//-------------------------------------
	clInnerStatus.Init();

	//----------------------------------
	// 피격관련 
	//---------------------------------
	clBeHitInfo.Init();

	//----------------------------------
	// 세트 아이템 타입 0은 없는 상태
	//---------------------------------
	m_siSetItemType = 0;
	m_siSetItemStep = 0;

	m_siSetItemType2 = 0;
	m_siSetItemStep2 = 0;

	m_siSetItemType3 = 0;
	m_siSetItemStep3 = 0;

	m_siSetItemType4 = 0;
	m_siSetItemStep4 = 0;

	m_siSetItemType5 = 0;
	m_siSetItemStep5 = 0;

	//ChangeEquipAbility = 0;

	//----------------------------------
	// 선거 유세관련 내용
	//---------------------------------
	bIsElectionStump = false;
	StringCchCopy( szCandidate,		Const_Max_Candidate,	TEXT("") );
	StringCchCopy( szMaintenance,	Const_Max_Maintenance,	TEXT("") );

	pclSpaceBoxItem		= NULL;
	pclTreasureBoxItem	= NULL;	

	//-----------------------------
	// 버프마법관련
	//-----------------------------
	m_clMagicBufMgr.Init();

	m_uiDailyQuestionCount = 0;	// 하루 질문 최대 횟수.

	//-------------------------------------	
	// 발렌타인 데이 전쟁 관련 
	//-------------------------------------	
	pclValentineWar = NULL ;

	m_uiWeaponSkillMasterEmblem = 0;


	//  [8/11/2009 종호_GAWIBAWIBO] 연승누적 포인트
	m_siGawiBawiBoCount = 0;

	ZeroMemory(&m_stMuteTime, sizeof(m_stMuteTime));
}

cltCharCommon::~cltCharCommon()
{
	SAFE_DELETE( pclCI					)
	SAFE_DELETE( pclCharDraw			)
	SAFE_DELETE( pclFriendInfo			)
	SAFE_DELETE( pclSpaceBoxItem		)
	SAFE_DELETE( pclTreasureBoxItem 	)
	SAFE_DELETE( pclPVP_LeagueInfo		)
	SAFE_DELETE( pclValentineWar		)
	SAFE_DELETE( pcltElixir				)
	SAFE_DELETE( pclMarriage			)
	SAFE_DELETE( pclFamily				)
	SAFE_DELETE( pclSoulGuard			)
	NK_SAFE_DELETE( pclCharSkillBookInfo )
}


void cltCharCommon::CharInit(SI32 id, SI32 charunique, SI32 childcharunique, SI32 summonindex, SI32 dir,  cltMapCommon* pclmap, 
							 cltIdentity* pclidentityinfo, cltPersonInfo* pclUserCharInfo, cltInnerStatusInfo* pclInnerStatus, SI16 siSoulGuardUnique )
{
	SI32 i;

	//-------------------------------------------
	// 메모리 생성 - 유저만 생성한다.
	//-------------------------------------------
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		if( IsPC(charunique) )
		{
			if(pclFriendInfo		== NULL)	pclFriendInfo			= new cltFriendInfo;
			if(pclSpaceBoxItem		== NULL)	pclSpaceBoxItem			= new cltSpaceBox;
			if(pclTreasureBoxItem	== NULL)	pclTreasureBoxItem		= new cltTreasureBox;
			if(pclPVP_LeagueInfo	== NULL)	pclPVP_LeagueInfo		= new cltPVP_LeagueInfo;
			if(pclValentineWar		== NULL)	pclValentineWar			= new cltValentineWarInfo;
			if(pcltElixir			== NULL)	pcltElixir				= new cltElixir;
			if(pclMarriage			== NULL)	pclMarriage				= new CMarriage;
			if(pclFamily			== NULL)	pclFamily				= new CFamily;	//가족정보
			if(pclSoulGuard			== NULL)	pclSoulGuard			= new cltSoulGuard;
			if(pclCharSkillBookInfo	== NULL)	pclCharSkillBookInfo	= NkNew cltCharSkillBookInfo;
			

			// CharServer에만 있는 변수
            if( ((cltCharServer*)this)->m_pclAgriculture	== NULL)	((cltCharServer*)this)->m_pclAgriculture		= new cltAgriculture;
			if( ((cltCharServer*)this)->m_pclShopRepairData	== NULL)	((cltCharServer*)this)->m_pclShopRepairData		= new cltShopRepairData;

		}
	}
	else if(pclClient->GameMode == GAMEMODE_CLIENT)
	{
		if( IsPC(charunique) )
		{
			if(pclFriendInfo		== NULL)	pclFriendInfo			= new cltFriendInfo;
			if(pclSpaceBoxItem		== NULL)	pclSpaceBoxItem			= new cltSpaceBox;
			if(pclTreasureBoxItem	== NULL)	pclTreasureBoxItem		= new cltTreasureBox;
			if(pclPVP_LeagueInfo	== NULL)	pclPVP_LeagueInfo		= new cltPVP_LeagueInfo;
			if(pclValentineWar		== NULL)	pclValentineWar			= new cltValentineWarInfo;
			if(pcltElixir			== NULL)	pcltElixir				= new cltElixir;
			if(pclMarriage			== NULL)	pclMarriage				= new CMarriage;
			if(pclFamily			== NULL)	pclFamily				= new CFamily;	// 가족정보
			if(pclSoulGuard			== NULL)	pclSoulGuard			= new cltSoulGuard;
			if(pclCharSkillBookInfo	== NULL)	pclCharSkillBookInfo	= NkNew cltCharSkillBookInfo;
		}
	}

	siCenterX		= 0;
	siCenterY		= 0;

	//-------------------------------------------
	// 현재 명령 초기화 
	//-------------------------------------------
	clCurOrder.Init();

	//-------------------------------------------
	// 다음 명령 초기화. 
	//-------------------------------------------
	ReserveOrder.Init();

	siSubOrder	= 0;
	bBusySwitch	= false;

	clMovePointList.Init();

	// 밖에 꺼내져 있는 상태로 되어 있는 소환수는 모두 안으로 집어 넣는다. 
	for( i = 0 ; i < MAX_SUMMON_OWN; ++i)
	{
		cltSummon *pclSummon = pclUserCharInfo->clSummonInfo.GetSummon(i);
		if(pclSummon && pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
		{
			pclSummon->siStatus = SUMMON_STATUS_TAKEIN;
		}
	}

	//-----------------------------
	// 신분 - [진성] 소환수 테이블이 나뉘면서 처음 몬스터나 소환수 세팅을 위해 위치 변경. 2008-8-29
	//-----------------------------
	siID				= id;
	CharUnique			= charunique;
	if(pclidentityinfo)
	{
		clIdentity.Set(pclidentityinfo);
	}
	else
	{
		clIdentity.Init();
	}
	if ( pclPVP_LeagueInfo ) 
	{
		pclPVP_LeagueInfo->Init()	;
	}
	if ( pclValentineWar ) 
	{
		pclValentineWar->Init()	;
	}

	siChildCharUnique	= childcharunique;
	siSummonIndex		= summonindex;

	siMySoulGuardUnique	= siSoulGuardUnique;

	bGodMode		= false;
	bOneKill		= false;	// 원킬모드

	clAddInfo.Init();

	if( (siID > 0 && siID < MAX_CHAR_NUMBER) && (charunique >= 0 && charunique <  MAX_CHAR_NUMBER) )
	{
		CharUniqueInfo[charunique]	=	siID;
	}
	else
	{
		MsgBox(TEXT("fdsf2"), TEXT("Fd2dff:charunique:%d id:%d"), charunique, siID);
	}

	// 중요 데이터를 복사한다. 
	memcpy(pclCI, pclUserCharInfo, sizeof(cltPersonInfo));						//ok

	// 보안코드 추가 - By LEEKH
	if( GetKind() < 0  || GetKind() >= MAX_KINDINFO_NUMBER )			return;

	// 이 캐릭터의 종류에 해당하는 KindInfo 포인터를 얻어온다. 
	//[진성] 소환수 테이블 분리후 캐릭터 kind 포인터 초기화시 몬스터인지 소환수인지 구분하기. 2008-8-29
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		if( clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			pclKI = pclClient->pclKindInfoSet->pclSummonKI[GetKind()];
			pclGMCommandKindInfo = pclClient->pclKindInfoSet->pclGMCommandKindInfo[GetKind()];
		}
		else
		{ 
			pclKI = pclClient->pclKindInfoSet->pclKI[GetKind()];
			pclGMCommandKindInfo = pclClient->pclKindInfoSet->pclGMCommandKindInfo[GetKind()];
		}
	}
	else
	{
		pclKI = pclClient->pclKindInfoSet->pclKI[GetKind()];
	}
	
	// 파라메타 박스를 초기화한다. 
	clPB.Init(pclClient->pclItemManager, &(pclCI->clIP), &pclCI->clHealthInfo, pclKI, pclGMCommandKindInfo);


	// 캐릭터가 활동할 지도를 정해준다. 
	pclMap					= pclmap;

	// 조합형 캐릭터용 관리자를 만든다. 
	if(pclCharDraw == NULL)
	{
		pclCharDraw = new CCharacterDrawing(pclClient->GameMode);
	}
	bHitDoneSwitch	= false;

	//------------------------------------
	// 운영자 권한 등급. 
	//------------------------------------
	siGameMasterLevel	= 0;


	siDirection		=	dir;
	TempDirection	=	dir;
	TargetDirection	=	dir;

	////-----------------------------
	//// 신분
	////-----------------------------
	//siID				= id;
	//CharUnique			= charunique;
	//if(pclidentityinfo)
	//{
	//	clIdentity.Set(pclidentityinfo);
	//}
	//else
	//{
	//	clIdentity.Init();
	//}

	//siChildCharUnique	= childcharunique;
	//siSummonIndex		= summonindex;


	//bGodMode		= false;
	//bOneKill		= false;	// 원킬모드

	//clAddInfo.Init();

	//if( (siID > 0 && siID < MAX_CHAR_NUMBER) && (charunique >= 0 && charunique <  MAX_CHAR_NUMBER) )
	//{
	//	CharUniqueInfo[charunique]	=	siID;
	//}
	//else
	//{
	//	MsgBox(TEXT("fdsf2"), TEXT("Fd2dff:charunique:%d id:%d"), charunique, siID);
	//}


	//----------------------------
	// 공격 대상 
	//----------------------------
	clAttackTarget.Init();
	siCurrentAttackType	= 0;

	//-----------------------------
	// 속성들 
	//----------------------------
	Atb			= pclKI->siAtb;
	DefenceAtb	= pclKI->DefenceAtb;

	//-------------------------------------------------------------
	// 충돌 관련 변수. 
	//------------------------------------------------------------
	Block		=	pclKI->siBlock | BLOCK_SYSTEMNPC;
	SelfBlock	=	BLOCK_CHAR;

	{
		
		cltSystemNPC npcinfo;
		if( pclClient->pclSystemNPCManager->FindSystemNPCInfoFromNPCKind( GetKind(), &npcinfo ) ) {

			SelfBlock |= BLOCK_SYSTEMNPC;
		}

	}


	SetIDSwitch		= false;                            // 유닛을 지도상에 설정했는지 여부를 기억한다.

	//----------------------------------
	// 출력과 관계된 변수들 
	//----------------------------------
	Animation		= 0;					// 어떤 종류의 애니메이션을 수행하는가?
	HeroAnimation	= 0;
	bUpdateAnimationSwitch	= true;		// 애니메이션을 갱신할지여부를 알려준다. 
	Frame			= 0;                		// 현재 어느 단계를 수행하고 있는가?

	// 정지 관련 
	MaxWaitType		= 1;   // 이 유닛이 정지 애니메이션으로 가질 수 있는 애니의 갯수 
	WaitType		= ANITYPE_WAIT0;       // 현재 이 유닛이 취하고 있는 정지 애니 


	//----------------------------
	// 방향 
	//----------------------------
	siDirection				= SOUTH;                     				// 방향 
	TempDirection			= 0;                				// 16방위로 존재하는가?
	TargetDirection			= 0;               				// 목표의 방위 


	//------------------------------
	// 공격관련 
	//------------------------------
	dwAttackGiveUpDelay			= 0;
	dwLastAttackClock			= 0;
	dwLastAttackIntervalClock	= 0;
	dwLastMagicClock			= 0;
	dwLastTorpedoClock			= 0;

	ActiveWeapon				= PERSONITEM_WEAPON1;
	ActiveClothes               = PERSONITEM_DRESS;
	ActiveHat                   = PERSONITEM_HAT;

	//---------------------------
	// 이동. 
	//---------------------------
	clMoveInfo.Init();
	siMoveMapIndex	= -1;

	//-----------------------------
	// 장인 정보 
	//-----------------------------
	siReservedTopSkillUnique	= 0;		// 설정 예약되어 있는 탑 기술 

	//---------------------------
	// 농사 
	//---------------------------
	siFarmX	= siFarmY	= 0;


	//---------------------------
	// 채굴
	//---------------------------
	siMineX	= siMineY	= 0;


	// 무장 상태를 얻어온다. 
	ParametaBoxAction();

	// by LEEKH 2007.12.24 - TRANSFORM
	if( GetKindInfo()->IsAtb(ATB_HERO))
	{
		pclCharDraw->LoadItemCodeData(GetKind(), TEXT("KOR01"), TEXT("KOR01"), TEXT("KOR01"), NULL, NULL, 0, NULL );
	}

	// 서버 클라이언트 각각의 캐릭터 경우에 초기화한다.
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		((cltCharServer*)this)->InitCharServer();
	}
	else
	{
		((cltCharClient*)this)->InitCharClient();
	}


	// 디폴트 애니메이션을 설정한다. 
	Animation			= ANITYPE_WAIT0;
	HeroAnimation		= 0;

	//  캐릭터 이름을 설정한다. 
	if(IsPC(CharUnique) == false)
	{
		if ( GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER")) )
		{
			//[추가 : 황진성 2007. 10. 31 도마돈 이름을 해당 맵의 몬스터 이름으로 세팅.]
			SI32 siKind[50]	= {0, };
			SI32 siCount	= 0;

			cltNPCManagerClient* pclNPCMgr = (cltNPCManagerClient*)pclClient->pclNPCManager;
			if( pclNPCMgr )
			{
				//pclNPCMgr->GetKindMapInx(pclCM->CR[id]->GetMapIndex(), siKind, siKindLevel, 50);
				//////////////////////////////////////////////////////////////////////////////////////////////
				// 해당 맵 인덱스에 있는 몬스터 kind얻어오기
				SI32 siMapIndex = pclCM->CR[id]->GetMapIndex();
				SI32 siIndex	= 0;
				SI32 siId;

				while ( siId = pclClient->pclCM->GetCharOrder(siIndex) )
				{
					siIndex++;
					
					// NPC가 아니면 컨티뉴
					if ( !IsNPC(pclClient->pclCM->CR[siId]->GetCharUnique()) )
					{
						continue;
					}
					
					// 현재 자신의 CharUnique(도마돈)이면 컨티뉴
					if ( pclClient->pclCM->CR[siId]->GetCharUnique() == CharUnique )
					{
						continue;
					}
					
					// 현재 내 맵에 있는 케릭터가 아니라면 컨티뉴
					if ( pclClient->pclCM->CR[siId]->GetMapIndex() != siMapIndex )
					{
						continue;
					}

					siKind[ siCount++ ] = pclClient->pclCM->CR[siId]->GetKind();

					if ( 50 <= siCount )
					{
						break;
					}

				}	// while ( id = pclClient->pclCM->GetCharOrder(siIndex) ) 종료

				//////////////////////////////////////////////////////////////////////////////////////////////
				//[검색 : 황진성 2007. 10. 31 NPC 종류로 NPC의 이름 얻기.]
				if ( siCount > 0 )
				{
					SI32			siRand		= rand() % siCount;
					NTCHARString32	kNPCName	= pclClient->pclKindInfoSet->GetName(siKind[siRand]);
					
					
					if ( kNPCName.IsEmpty() == false )
					{
						SetName( kNPCName );
					}
					else
					{
						SetName( pclKI->GetName() );
					}
				}
				else
				{
					SetName( pclKI->GetName() );				
				}
			}	// if( pclNPCMgr ) 종료
		}	// if ( GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER")) )
		else
		{
			SetName( pclKI->GetName() );
		}
	}

	//------------------------------------
	// 현재 선택된 마법 
	//------------------------------------
	siCurrentMagic			= 0;
	siCurrentMagicCastType	= 0;

	// NPC의 기본마법을 설정한다.(PASSIVE만을 위한것임)
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))
	{
		if(pclKI->siMagic)
		{
			siCurrentMagic		 = pclKI->siMagic;
			stMagicAttributeData *pMagicAttributeData = pclClient->pclMagicManager->GetMagicAttribute( siCurrentMagic );
			if ( pMagicAttributeData )
			{
				siCurrentMagicCastType = pMagicAttributeData->si08MagicCastType;
			}
			
		}
	}

	//------------
	// 중독 관련 
	//------------
	siPoisonCharUnique	= 0;			// 나를 중독시킨 캐릭터 유니크. 
	dwPoisonLastClock	= 0;			// 중독의 지연시간. 
	dwPoisonStartClock	= 0;			// 중독 시작시간. 
	siPoisonPower		= 0;			// 중독의 강도. 
	dwPoisonCheckClock	= 0;

	//-------------
	// 얼음 관련 
	//-------------
	dwIceLastClock	= 0;
	dwIceStartClock = 0;


	//-------------
	// 공격력 저하 저주 관련 
	//-------------
	dwCurseAttackStartClock		= 0;
	dwCurseAttackLastClock		= 0;
	siCurseAttackPower			= 0;	// 강도. 

	//-------------
	// CRITICAL 저하 저주 관련 
	//-------------
	dwCurseCriticalStartClock	= 0;
	dwCurseCriticalLastClock	= 0;
	siCurseCriticalPower		= 0;	// 강도. 

	//-------------
	// DEFENSE 저하 저주 관련 
	//-------------
	dwCurseDefenseStartClock	= 0;
	dwCurseDefenseLastClock		= 0;
	siCurseDefensePower			= 0;	// 강도. 

	//-------------
	// MOVESPEED 저하 저주 관련 
	//-------------
	dwCurseMovespeedStartClock	= 0;
	dwCurseMovespeedLastClock	= 0;
	siCurseMovespeedPower		= 0;	// 강도. 

	//-------------
	// MOVESPEED 증가 버프 관련 
	//-------------
	dwIncreaseMovespeedStartClock	= 0;
	dwIncreaseMovespeedLastClock	= 0;
	siIncreaseMovespeedPower		= 0;	// 강도. 


	//------------
	// 몸에 붙는 마법불 관련 
	//------------
	siMagicFireCharUnique = 0;			// 불을 붙인 캐릭터 유니크. 
	dwMagicFireLastClock = 0;			// 불의 지연시간. 
	dwMagicFireStartClock = 0;			// 불 시작시간. 
	siMagicFirePower = 0;				// 불의 강도. 
	dwMagicFireCheckClock = 0;

	//-------------
	// DRAIN 관련 
	//-------------
	bDrainSwitch = false;
	siDrainFrame = 0;

	uiStaminaFrame = 0;

	//--------------
	// 피격
	//--------------
	bHitSwitch	= false;		// 피격 중인지 여부. 

	//----------------------------------
	// 피격관련 
	//---------------------------------
	clBeHitInfo.Init();

	//-------------------
	// 전쟁 
	//-------------------
	siWarEnemyKillNumber	= 0;	// 전쟁에서 처치한 적의수. 
	siWarKilledNumber		= 0;
	siBlackArmyWarMapIndex	= -1;

	//-------------------
	// 흑의군단 전쟁 
	//-------------------
	siBlackWarEnemyKillNumber = 0;
	siBlackWarKilledNumber = 0;
	siBlackWarEnemyKillScore = 0;
	siBlackWarEnemyKillVillageScore = 0;

	//------------------------------------
	// 찜
	//------------------------------------
	clJim.Init();

	//------------------------------------
	// 파티 인덱스.
	//------------------------------------
	siPartyIndex	= 0;

	//-------------------------------------
	// 선공 방어 여부. 
	//-------------------------------------
	bNoFirstAttackSwitch	= false;
	//-------------------------------------
	// ICE 방어 여부. 
	//-------------------------------------
	bNoIceAttackSwitch		= false;

	//-------------------------------------	
	// [진성] 버프 룰렛 작동중이면 주사위모냥 띄우기. => 2008-6-10
	//-------------------------------------
	bBuffRouletteSwitch		= false;

	//-------------------------------------	
	// [진성] 엘릭서.
	//-------------------------------------
	bElixirSwitch			= false;

	siBufTransformKind		= 0;

	//-------------------------------------	
	// [성웅] 현제 PVP 상대방이 있다.
	//-------------------------------------
	siEnemUnique				= 0	;
	//-------------------------------------	
	// [성웅] 현제 PVP 기다리는 시간 
	//-------------------------------------
	siPVPWaitTime			=	0	;
	//-------------------------------------	
	// [성웅] 현제 끝난시간
	//-------------------------------------
	siPVPEndTime		=	0	;
	//-------------------------------------	
	// [성웅] 라쿤이벤트 시작 기다리는 시간
	//-------------------------------------
	siRacoonDodgeWaitTime	=	0	;
	//-------------------------------------	
	// [성웅] 발렌타인데이 이벤트를 위해 자신이 솔로인지 커플인지 대답한 시간.
	//-------------------------------------
	dwValentineAnswerTime	=	0	;
	//-------------------------------------	
	// [성웅] 현제 PVP 싸우는 시간
	//-------------------------------------
	siPVPTime			=	0	;
	// [성웅] 현제 PVP 기다리는 시간동안 상대방 ID 기록 
	//-------------------------------------
	siPVPWaitRequestId		=	0	;
	siPVPWaitAcceptId		=	0	;
	//-------------------------------------	
	// [성웅] PVP시작 전 카운트 다운을 한다.
	//-------------------------------------
	bPvpCountDown			= false ;
	bPvpLeague				=	false	;
	// PVP 결과
	siPVPWin				=	false	;
	siPVPLose				=	false	;
	siPVPDraw				=	false	;
	//-------------------------------------
	// 사망시 사용되는 변수. 
	//-------------------------------------
	bDyingSwitch			= false;

	//-------------------------------------
	// 개인상점 
	//-------------------------------------
 	bPersonalShopSwitch	= false;		// 개인상점이 열려 있는가?

	bPremiumPersonalShop = false;		// 프리미엄 개인상점인가?

	bRepairShopSwitch	= false;

	//-------------------------------------
	// 제조 상태중
	//-------------------------------------
	siPersonalMakeItemType	= 0;		// 현재 제조중인가?

	// 현재 레벨업을 해서 레벨업 동작인가
	bLevelUpDrawSwitch = false;

	//-------------------------------------------------
	// 소환수 및 사용자간 컨트롤 // -1이면 PC자신
	//-----------------------------------------------
	siSelectedCharIndex = -1 ;

	//[진성] 핸드폰 인증 여부.
	bCellularPhoneAuth  = false;
	bIsPromoter			= false;

	// [성웅] 라쿤이벤트 시작 전에 머리위에 카운트 이미지를 그린다
	bRacoonDodgeEventCountDown	=	false	;

	// [지연] 복불복 이벤트 : 그래픽 리소스 출력
	//bBBBEvent_5SecCountDownFlag		= false;		// 5초start 카운트
	//bBBBEvent_StageFailFlag			= false;		// Lose
	//bBBBEvent_StageClearFlag		= false;		// win
	//bBBBEvent_TotalStageClearFlag	= false;		// 10stage win (제이)
	//siBBBEvent_TotalStageClearResultImageIndex = 0;

	//-------------------------------------
	// 내부 변수들. 
	//-------------------------------------
	clInnerStatus.Set(pclInnerStatus);

	// 설정된 이벤트 정보에 따라 충돌 영역을 재설정한다. 
	SetBlock();


	// 만들어진 프레임을 설정한다. 
	dwMakeFrame = pclClient->GetFrame();

	if(pclClient->GameMode == GAMEMODE_CLIENT)
	{
		((cltCharClient*)this)->SetFileNFont();
	}

	SetInfo();

	//----------------------------------
	// 세트 아이템 타입 0은 없는 상태
	//---------------------------------
	m_siSetItemType = 0;
	m_siSetItemStep = 0;

	m_siSetItemType2 = 0;
	m_siSetItemStep2 = 0;

	m_siSetItemType3 = 0;
	m_siSetItemStep3 = 0;

	m_siSetItemType4 = 0;
	m_siSetItemStep4 = 0;

	m_siSetItemType5 = 0;
	m_siSetItemStep5 = 0;

	//ChangeEquipAbility = 0;

	if(IsPC(GetCharUnique()))
	{
		//[진성] 파티홀. 파티장에서 받은 아이템을 삭제. => 2008. 3. 12
		PartyHallItemRemove(id);

		if( !pclClient->IsCountrySwitch( Switch_Festival_Food ))
		{
			//[진성] 축제음식 아이템 삭제.
			FestivalFoodItemRemove(id);
		}

		//[진성] 네잎크로버가 현재 사용할수 없는 거면 삭제 => 2008-8-14
		if( pclClient->IsCountrySwitch(Switch_FourLeaf))
		{
			NotFourLeafItemRemove(id);
		}
	}

	//----------------------------------
	// 선거 유세관련 내용
	//---------------------------------
	bIsElectionStump = false;
	StringCchCopy( szCandidate,		Const_Max_Candidate,	TEXT("") );
	StringCchCopy( szMaintenance,	Const_Max_Maintenance,	TEXT("") );

	//-----------------------------
	// 버프마법관련
	//-----------------------------
	m_clMagicBufMgr.Init();

	m_uiWeaponSkillMasterEmblem = 0;

	ZeroMemory(&m_stMuteTime, sizeof(m_stMuteTime));
}


SI32 cltCharCommon::GetX()const{return pclCI->clBI.GetX();}
SI32 cltCharCommon::GetY()const{return pclCI->clBI.GetY();}

void  cltCharCommon::SetX(SI32 x){pclCI->clBI.SetX(x);} 
void  cltCharCommon::SetY(SI32 y){pclCI->clBI.SetY(y);}

// 종류를 돌려준다.
SI32 cltCharCommon::GetKind()const{return pclCI->clBI.GetKind();}
void cltCharCommon::SetKind(SI32 kind){pclCI->clBI.SetKind(kind);}

cltKindInfo* cltCharCommon::GetKindInfo(bool bForDraw /* = false */)	// KindInfo 정보를 돌려준다 - 변신 후에는 변신된 캐릭터의 정보가 반환된다. - by LEEKH 2007.12.24
																		// 외관변경 버프를 위한 변수 추가 - by LEEKH 2008-09-10
{
	cltKindInfo*	retKI = pclKI;

	if(clTransFormInfo.bTransFormMode)
	{
		// PCK : 야시장(음식) 추가로 인한 변신 버프 정리, 가차스피릿 변신상태에서 변신버프가 걸리면 외관은 변신버프를 따라간다.
		if( siBufTransformKind > 0 && bForDraw )
		{
			{
				cltKindInfo*	tempKI = pclClient->pclKindInfoSet->pclKI[siBufTransformKind];
				// 변신캐릭터에 해당 에니메이션이 있는 경우에만 변신캐릭터의 그림 정보를 반환한다.
				if( tempKI->clCharAniManager.FindRefFromAnitype(Animation) > 0 )
					retKI = tempKI;
			}
		}
		else
		{
			if(clTransFormInfo.uiNowTransFormKind >= 0 && clTransFormInfo.uiNowTransFormKind < MAX_KINDINFO_NUMBER)
			{
				if(pclClient->pclKindInfoSet->pclKI[clTransFormInfo.uiNowTransFormKind] != NULL)
					retKI = pclClient->pclKindInfoSet->pclKI[clTransFormInfo.uiNowTransFormKind];
			}
		}

	}
	else
	{
		if( siBufTransformKind > 0 && bForDraw )
		{
			if(pclClient->pclKindInfoSet->IsValidKind(siBufTransformKind))
			{
				cltKindInfo*	tempKI = pclClient->pclKindInfoSet->pclKI[siBufTransformKind];
				// 변신캐릭터에 해당 에니메이션이 있는 경우에만 변신캐릭터의 그림 정보를 반환한다.
				if( tempKI->clCharAniManager.FindRefFromAnitype(Animation) > 0 )
					retKI = tempKI;
			}
		}
	}

	return retKI;
}


// 맵 인덱스를 얻어온다. 
SI32 cltCharCommon::GetMapIndex()const
{
	return pclCI->clBI.GetMapIndex();
}
// 맵 인덱스를 설정한다.  
void cltCharCommon::SetMapIndex(SI32 index)
{
	pclCI->clBI.SetMapIndex(index);
}

// 캐릭터의 이름을 얻어온다. 
const TCHAR* cltCharCommon::GetName()const
{	
	return pclCI->clBI.GetName();
}

void cltCharCommon::SetName(const TCHAR* name)
{ 
	pclCI->clBI.SetName(name);
}

SI32 cltCharCommon::GetMana()
{
/*	if(pclCI->clIP.GetMana() > clPB.GetMaxMana())
	{
		pclCI->clIP.SetMana( clPB.GetMaxMana() );

		return clPB.GetMaxMana();
	}
*/
	return pclCI->clIP.GetMana();
}

void cltCharCommon::SetMana(SI32 mana)
{
	pclCI->clIP.SetMana(mana);
}

SI32 cltCharCommon::DecreaseMana(SI32 mana)
{
	pclCI->clIP.DecreaseMana( max(0, mana) );

	if(GetMana() < 0 )
	{
		pclCI->clIP.SetMana(0);
	}

	return GetMana();
}
SI32 cltCharCommon::IncreaseMana(SI32 mana)
{
	pclCI->clIP.IncreaseMana( mana );

	if(GetMana() > clPB.GetMaxMana())
	{
		pclCI->clIP.SetMana( clPB.GetMaxMana() );
	}
	return GetMana();
}

SI32 cltCharCommon::GetLife()
{
/*	if(pclCI->clIP.GetLife() > clPB.GetMaxLife())
	{
		pclCI->clIP.SetLife( clPB.GetMaxLife() );

		return clPB.GetMaxLife();
	}
*/
	return pclCI->clIP.GetLife();
}
void cltCharCommon::SetLife(SI32 life){pclCI->clIP.SetLife(life);}

SI32 cltCharCommon::IncreaseLife(SI32 life)
{
	pclCI->clIP.IncreaseLife( life );

	if(GetLife() > clPB.GetMaxLife())
	{
		pclCI->clIP.SetLife( clPB.GetMaxLife() );
	}

	return  GetLife();
}
SI32 cltCharCommon::GetWis()const{return pclCI->clIP.GetWis();}

SI32 cltCharCommon::GetStr()const{return pclCI->clIP.GetStr();}

SI32 cltCharCommon::GetDex()const{return pclCI->clIP.GetDex();}

SI32 cltCharCommon::GetVit()const{return pclCI->clIP.GetVit();}
void cltCharCommon::SetVit(SI32 vit){pclCI->clIP.SetVit(vit);}

SI32 cltCharCommon::GetMag()const{return pclCI->clIP.GetMag();}
void cltCharCommon::SetMag(SI32 mag){pclCI->clIP.SetMag(mag);}

SI32 cltCharCommon::GetHnd()const{return pclCI->clIP.GetHnd();}
void cltCharCommon::SetHnd(SI32 hnd){pclCI->clIP.SetHnd(hnd);}

// 내 자신의 경험치를 구한다.(상대가 나를 처치했을 때 얻을 수 있는 경험치. ) 
SI64 cltCharCommon::GetMyExp()const{return pclKI->Exp + (pclCI->clIP.GetLevel()-1) ;}	// SI32->SI64 경험치 오버플로우때문에 수정


//-------------------------------------
// 공격관련. 
//-------------------------------------
void cltCharCommon::GetHitPoint(cltPos* pclpos)
{
	pclpos->siX = siCenterX;
	pclpos->siY = siCenterY;
}

// 공격의 최종 조율된 위치를 알려준다.
void cltCharCommon::DecideAttackPoint(SI32 port, SI32& x, SI32&y)
{
	x	=	siCenterX;
	y	=	siCenterY;
}

// 수행중인 작업의 서브 단계를 얻어온다. 
SI32 cltCharCommon::GetSubOrder(){return siSubOrder;}


//-----------------------------------------
// 수호천사 관련 
//-----------------------------------------
void cltCharCommon::SetAngel(bool mode)
{
	pclCI->clBI.uiAngelSwitch = mode;

	// 클라이언트로 보낸다. 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_ANGEL, mode);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNetMsg((sPacketHeader*)&clMsg);

}

void cltCharCommon::SetPolice(bool mode)
{
	pclCI->clBI.uiPoliceSwitch = mode;

	// 클라이언트로 보낸다. 
	cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_POLICE, mode);
	cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
	SendNetMsg((sPacketHeader*)&clMsg);
}

//--------------------------------------------------------
// 좌표 정보 관련 
//--------------------------------------------------------
// Person이 현재 위치한 마을의 Unique를 구한다. 
SI32 cltCharCommon::GetCurrentVillageUnique()
{
	// 지도의 인덱스를 구한다. 
	SI32 mapindex = GetMapIndex();

	return pclClient->pclMapManager->GetVillageUnique(mapindex);
}


// Person이 현재 위치한 수렵장이 있는 마을의 Unique를 구한다. 
SI32 cltCharCommon::GetHuntVillageUnique()
{
	// 지도의 인덱스를 구한다. 
	SI32 mapindex = GetMapIndex();

	if(mapindex < 200)return 0;
	if(mapindex >= 200 + MAX_VILLAGE_NUMBER)return 0;

	return mapindex - 200;
}

bool cltCharCommon::PreCharAction()
{

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		// 캐릭터 생성 후에 암호화키와 캐릭터 유니크 값을 클라이언트로 보낸다. 
		((cltCharServer*)this)->SecretNCharUniqueSendOperation();

		// 클라이언트로부터 일정 시간 메시지가 오지 않음 자동 로그아웃 시킨다. 
		if(((cltCharServer*)this)->AutoLogOut() == true)
		{
			return true;
		}
	}

	// 피격시의 모습을 보여준다.
	if(BeHitOperation() == true)
	{
		return true;
	}

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		// 적에게 공격받을때의 조치
		((cltCharServer*)this)->BeAttackedAction();
	}

	return false;
}



//---------------------------------------
// Action
//---------------------------------------
BOOL cltCharCommon::Action()
{
	// 서버에서는 캐릭터가 매 프레임 작동하지는 않는다. 
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		DWORD dwdata = (GetID() % CHAR_ACTION_INTERVAL_FRAME);
		if( dwdata != (pclClient->GetFrame() % CHAR_ACTION_INTERVAL_FRAME) )
		{
			return true;
		}

		// NPC일 경우 주변 셀에 플레이어가 있는지 조사하고,
		// 플레이어가 한명도 없다면, Action을 작동 하지 않는다.

		if(( IsNPC(GetCharUnique()) || IsInstanceNPC(GetCharUnique()) ) &&
			clIdentity.siIdentity != IDENTITY_SOULGUARD &&
			clIdentity.siIdentity != IDENTITY_PERSON_SUMMON &&
			((cltCharServer*)this)->siCharMode != CHARMODE_BLACKWAR &&
			((cltCharServer*)this)->pclCI->clIP.GetLife() > 0 )
		{
			ITZCell *pCell = GetCell();

			if( pCell )
			{
				// 주변 셀에 플레이어가 있는가?
				if( !pCell->IsTherePlayerNearCells() )
				{
					// bActiveNPC가 TRUE로 설정되어있었다면, FALSE로 설정하고,
					// ActiveNPCNum을 감소시킨다
					if( bActiveNPC )
					{
						bActiveNPC = FALSE;
						pclCM->pclIDManager->SubActiveNPCNumber();
					}
					return true;
				}
				else
				{
					// bActiveNPC가 FALSE로 설정되어있었다면, TRUE로 설정하고,
					// ActiveNPCNum을 증가시킨다
					if( bActiveNPC == FALSE )
					{
						bActiveNPC = TRUE;
						pclCM->pclIDManager->AddActiveNPCNumber();
					}
				}
			}
		}
		else
		{
			if( bActiveNPC == FALSE )
			{
				bActiveNPC = TRUE;
				pclCM->pclIDManager->AddActiveNPCNumber();
			}
		}
	}

	bool rtnval = PreCharAction();

	if(rtnval)
	{
		return true;
	}

	// 비축된 명령을 수행한다. 
	if(ReserveOrder.siOrder != ORDER_WAIT)
	{
		GetOrderBuffer();
	}


	// 셀관련 작업.
	// 명령을 입력받는  GetOrderBuffer()이후에 처리되어야 한다. 
	CellAction();


	//-------------------------------------
	// 생명력이 떨어지면 죽는 것으로 처리. 
	//-------------------------------------
	if(GetLife() <= 0)
	{
		if(GetCurrentOrder() != ORDER_DIE && GetCurrentOrder() !=ORDER_DEAD) 
		{
			SetCurrentOrder(ORDER_DIE);
		}
	}
	else
	{

		//-------------------------------------
		// 생명력 충전 조치. 
		//-------------------------------------
		if(clPB.siReservedLife)
		{
			if(clPB.siReservedLife  >= pclCM->siIncLifeUnit)
			{
				clPB.siReservedLife	-= pclCM->siIncLifeUnit;
				IncreaseLife(pclCM->siIncLifeUnit);

#ifdef _DEBUG
#ifdef _CHINA
				pclClient->pclLog->FileConfigPrint( "ReservedLife", "Update" );
#endif
#endif
			}
			else
			{
				pclCI->clIP.Life	+= clPB.siReservedLife;
				clPB.siReservedLife	= 0;
#ifdef _DEBUG
#ifdef _CHINA
				pclClient->pclLog->FileConfigPrint( "ReservedLife", "Update" );
#endif
#endif
			}

			// 소환수인 경우, 부모의 정보도 업데이트 한다. 
			SI32 parentid = GetSummonParentID();
			if(pclCM->IsValidID(parentid) && GetSummonIndex() >= 0 && GetSummonIndex() < MAX_SUMMON_OWN)
			{
				pclCM->CR[parentid]->pclCI->clSummonInfo.clSummon[GetSummonIndex()].clIP.SetLife(pclCI->clIP.Life);
			}
		}
	}


	// 각종 변수를 재설정한다.
	bool bcheckswitch = false;
	if(TABS(pclClient->CurrentClock - clCommonSimpleVary.dwLastCheckParametaBoxActionClock) > (int)pclCM->dwParametaBoxActionIntervalClock)
	{
		clCommonSimpleVary.dwLastCheckParametaBoxActionClock = pclClient->CurrentClock;
		bcheckswitch = true;
	}
	if(clCommonSimpleVary.bForceparametaBoxActionSwitch)
	{
		bcheckswitch = true;
	}

	if(bcheckswitch)
	{
		ParametaBoxAction();
	}

	// 한번 강제로 실행한 뒤에 옵션을 풀어준다. - by LEEKH
	if(clCommonSimpleVary.bForceparametaBoxActionSwitch)
	{
		clCommonSimpleVary.bForceparametaBoxActionSwitch = false;
	}

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		((cltCharServer*)this)->CharServerAction();
	}
	else
	{
		((cltCharClient*)this)->CharClientAction();
	}
	switch(GetCurrentOrder())
	{
		//------------------------------
		// 대기 상태 
		//------------------------------
	case ORDER_WAIT:

		DeleteID();
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			((cltCharServer*)this)->OperateWaitServer();
		}
		else
		{
			((cltCharClient*)this)->OperateWaitClient();
		}
		SetID();


		break;

		//------------------------------
		// 현재 행위의 중단.  
		//------------------------------
	case ORDER_STOP:
	case ORDER_FORCESTOP:
	case ORDER_REVIVE:
		DeleteID();

		SetCurrentOrder(ORDER_WAIT);

		SetID();

		break;


		//------------------------------
		// 죽음 동작. 
		//------------------------------
	case ORDER_DIE:

		DeleteID();

		if(Action_Dying()	==	true)
		{
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				SetCurrentOrder(ORDER_DEAD);
			}
		}
		else SetID();

		break;

		//------------------------------
		// 죽음 종결. 
		//------------------------------
	case ORDER_DEAD:

		Dead();

		if( bActiveNPC ) {
			bActiveNPC = FALSE;
			pclCM->pclIDManager->SubActiveNPCNumber();
		}


		return FALSE; 
		break;

		//------------------------------
		// 이동 동작.
		//------------------------------
	case ORDER_MOVE:
		{
			DeleteID();

			// 목적지에 도착 
			if(Move() == MOVERTNVAL_MOVEDONE)
			{
				OrderStop(siID, BY_COMPUTER);
			}

			if(clMoveInfo.siMovePercent==0)
			{
				bBusySwitch	=	false;
			}
			else 
			{
				bBusySwitch	=	true;
			}

			SetID();

		}

		break;
		
	//------------------------------
	// 직선 이동 동작.
	//------------------------------
	case ORDER_STRAIGHTMOVE:

		DeleteID();

		// 목적지에 도착 
		if(Move(true) == MOVERTNVAL_MOVEDONE)
		{
			OrderStop(siID, BY_COMPUTER);
		}
		
		if(clMoveInfo.siMovePercent==0)
		{
			bBusySwitch	=	false;
		}
		else 
		{
			bBusySwitch	=	true;
		}

		SetID();


		break;


	//------------------------------
	// 공격 행위
	//------------------------------
	case ORDER_ATTACK:

		DeleteID();

		switch(Action_Attack()) 
		{
		case -1:	OrderStop(siID, BY_COMPUTER); 			break;
		case -2:	OrderForceStop(siID, BY_COMPUTER); 		break;
		default:											break;
		}
	
		SetID();

		break;

	//------------------------------
	// 마법 구현 행위. 
	//------------------------------
	case ORDER_MAGIC:

		DeleteID();
		Magic();
		SetID();

		break;
		

	case ORDER_FISH:

		DeleteID();
		Fish();
		SetID();

		break;

	case ORDER_FARM:

		DeleteID();
		Farm();
		SetID();

		break;

	case ORDER_MINE:

		DeleteID();
		Mine();
		SetID();

		break;

	case ORDER_SITDOWN:
		{
			SI32 haveCushion = ((cltCharClient*)pclCM->CR[GetID()])->siCushionUnique;
			SI32 SitDownAnytype = ANITYPE_SITDOWN;
			
			if( haveCushion > 0 )
			{
				switch(haveCushion)
				{
					case  ITEMUNIQUE(13628): // 이불1
					case  ITEMUNIQUE(13629): // 이불2
						SitDownAnytype = ANITYPE_SLEEP;
						break;
					case  ITEMUNIQUE(13649): // 잠자는 냐옹이 방석(일본남)
					case  ITEMUNIQUE(13650): // 잠자는 냐옹이 방석(일본여)
					case  ITEMUNIQUE(13647): // 잠자는 냐옹이 방석(서양남)
					case  ITEMUNIQUE(13648): // 잠자는 냐옹이 방석(서양녀)
						SitDownAnytype = ANITYPE_SLEEPCAT;
						break;
					default:
						break;
				}
			}

			DeleteID();		
			SitDown(SitDownAnytype);
			SetID();
		}
		break;

		//------------------------------
		// 공격 행위
		//------------------------------
	case ORDER_ATTACK_CLIENT:

		DeleteID();

		switch(Action_Attack()) 
		{
		case -1:	OrderStop(siID, BY_COMPUTER); 			break;
		case -2:	OrderForceStop(siID, BY_COMPUTER); 		break;
		default:											break;
		}

		SetID();

		break;

	case ORDER_SPECIAL_ACTION:
		{
			if( Action_Special() )
			{
				OrderStop(GetID(), BY_COMPUTER);
			}
		}
		break;

	default:
		{
		    MsgBox(TEXT("CharOrder"), TEXT("No Order kind:%d  order:%d"), GetKind(), GetCurrentOrder());
		}
		break;
		
	}

	// 화면에 찍을 좌표를 구한다. 
	CalculateRealXY();
	AfterCharAction();
	
	return true;



}


// 캐릭터의 흔적을 남긴다. 
BOOL cltCharCommon::SetID()
{
	if(pclMap == NULL)return FALSE;

	if(pclKI->IsAtb(ATB_HORSE) == true)
	{
		return TRUE;
	}
	
	pclMap->SetCollMap(GetX(), GetY(), SelfBlock);
	pclMap->SetIDMap(siID, GetX(), GetY());
	 
	SetIDSwitch=TRUE;

	return TRUE;
}


// 캐릭터의 흔적을 없앤다. 
BOOL cltCharCommon::DeleteID()
{
	if(SetIDSwitch == FALSE)return FALSE;

	// 말은 바닥에서 지우지 않는다.
	if(pclKI->IsAtb(ATB_HORSE) == true)return TRUE;

	pclMap->ClearIDMap(GetX(), GetY());
	pclMap->DeleteCharCollMap(GetX(), GetY());
	
	SetIDSwitch=FALSE;

	return TRUE;
}



// 캐릭터가 생성되었음을 알린다. 
void cltCharCommon::SetInfo()
{
	pclClient->pclCM->SetInfo(this);
}

// id가 range범위안에 있는가?
BOOL cltCharCommon::IsInRange(SI32 id, SI32 range)
{

	if(pclCM->IsAlive(id)==FALSE)return FALSE;

	SI32 dx	=	pclCM->CR[id]->GetX();
	SI32 dy	=	pclCM->CR[id]->GetY();

	// 목표까지의 거리 
	SI32 length = max( TABS(dx - GetX()), TABS(dy - GetY())  );

	// 실제 거리 
	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 reallength = length - ((GetKindInfo()->siSize - 1)/ 2) - ((pclCM->CR[id]->GetKindInfo()->siSize - 1) / 2);

	if(reallength <= range)return TRUE;



	return FALSE;
}


//--------------------------------------------------------------------------------------------
// 애니메이션 관련. 
//--------------------------------------------------------------------------------------------
// Hero Animation 코드를 결정한다. 
SI32 cltCharCommon::CalcHeroAnimation()
{
	TCHAR anicode[256] =  TEXT("");


	switch(Animation)
	{
	case ANITYPE_WAIT0:
		if( GetKind() == KIND_HERO3 ||
			GetKind() == KIND_HEROINE3 ||
			GetKind() == KIND_HERO4 ||
			GetKind() == KIND_HEROINE4 )
		{   

			if( bLevelUpDrawSwitch == true )
			{
				StringCchCopy(anicode, 256, TEXT("SPC")); // 레벨업 동작
			}			
			else if( (siPersonalMakeItemType == MAKE_ANI_ARMOR) || (siPersonalMakeItemType == ENCHANT_ANI_WEPONE)|| (siPersonalMakeItemType == ENCHANT_ANI_ARMOR) )
			{			
				StringCchCopy(anicode, 256, TEXT("MAM")); // 무기 ,방어구 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_HEAL)
			{
				StringCchCopy(anicode, 256, TEXT("MHE")); // 약제 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_FOOD) 
			{
				StringCchCopy(anicode, 256, TEXT("MFO")); // 음식 제조동작
			}
			else if ( (bPersonalShopSwitch == true && bPremiumPersonalShop == true) || ( bIsElectionStump == true ) || bRepairShopSwitch == true ) 
			{
				StringCchCopy(anicode, 256, TEXT("SOP")); // 개인상점 동작
			}
			else
			{
				StringCchCopy(anicode, 256, TEXT("WT1")); // 대기동작
			}
		}
		else
		{
				StringCchCopy(anicode, 256, TEXT("WT1")); // 대기동작
		}		
		break;
	case ANITYPE_WAIT1:
		if( GetKind() == KIND_HERO3 ||
			GetKind() == KIND_HEROINE3 ||
			GetKind() == KIND_HERO4 ||
			GetKind() == KIND_HEROINE4 )
		{        
			if( bLevelUpDrawSwitch == true )
			{
				StringCchCopy(anicode, 256, TEXT("SPC")); // 레벨업 동작
			}			
			else if( (siPersonalMakeItemType == MAKE_ANI_ARMOR) || (siPersonalMakeItemType == ENCHANT_ANI_WEPONE)|| (siPersonalMakeItemType == ENCHANT_ANI_ARMOR) )
			{
				StringCchCopy(anicode, 256, TEXT("MAM")); // 무기 ,방어구 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_HEAL)
			{
				StringCchCopy(anicode, 256, TEXT("MHE")); // 약제 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_FOOD) 
			{
				StringCchCopy(anicode, 256, TEXT("MFO")); // 음식 제조동작
			}
			else if ( (bPersonalShopSwitch == true && bPremiumPersonalShop == true) || ( bIsElectionStump == true ) || bRepairShopSwitch == true ) 
			{
				StringCchCopy(anicode, 256, TEXT("SOP")); // 개인상점 동작
			}
			else
			{
				StringCchCopy(anicode, 256, TEXT("WT2")); // 대기동작
			}
		}
		else
		{
			StringCchCopy(anicode, 256, TEXT("WT2")); // 대기동작
		}
		break;
	case ANITYPE_ATTACK:
	case ANITYPE_ATTACK1:
	case ANITYPE_ATTACK2:
		// 장비하고 있는 무기에 따라서 다른 동작을 취한다. 
		switch(clPB.siArmWeaponUnique)
		{
		case ITEMTYPE_SWORD: 
		case ITEMTYPE_STAFF:
		case ITEMTYPE_AXE:
			StringCchCopy(anicode, 256, TEXT("1HS"));
			break;
		case ITEMTYPE_SPEAR: 
			StringCchCopy(anicode, 256, TEXT("2HT"));
			break;
		case ITEMTYPE_BOW:
			StringCchCopy(anicode, 256, TEXT("2HB"));
			break;
		case ITEMTYPE_GUN:
			StringCchCopy(anicode, 256, TEXT("2HG"));
			break;
		default:
			StringCchCopy(anicode, 256, TEXT("1HS"));
			break;
		}
		break;
	case ANITYPE_DYING:
		StringCchCopy(anicode, 256, TEXT("DTH"));
		break;
	case ANITYPE_MOVE:
		StringCchCopy(anicode, 256, TEXT("MOV"));
		break;
	case ANITYPE_HIT:
		StringCchCopy(anicode, 256, TEXT("HIT"));
		break;
	case ANITYPE_FISH:
		StringCchCopy(anicode, 256, TEXT("FSH"));
		break;
	case ANITYPE_SLEEP:

		if( GetKind() == KIND_HERO3 ||
			GetKind() == KIND_HEROINE3 ||
			GetKind() == KIND_HERO4 ||
			GetKind() == KIND_HEROINE4 )
		{        
			if( bLevelUpDrawSwitch == true )
			{
				StringCchCopy(anicode, 256, TEXT("SPC")); // 레벨업 동작
			}			
			else if( (siPersonalMakeItemType == MAKE_ANI_ARMOR) || (siPersonalMakeItemType == ENCHANT_ANI_WEPONE)|| (siPersonalMakeItemType == ENCHANT_ANI_ARMOR) )
			{			
				StringCchCopy(anicode, 256, TEXT("MAM")); // 무기 ,방어구 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_HEAL)
			{
				StringCchCopy(anicode, 256, TEXT("MHE")); // 약제 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_FOOD) 
			{
				StringCchCopy(anicode, 256, TEXT("MFO")); // 음식 제조동작
			}
			else if ( (bPersonalShopSwitch == true && bPremiumPersonalShop == true) || ( bIsElectionStump == true ) || bRepairShopSwitch == true ) 
			{
				StringCchCopy(anicode, 256, TEXT("SOP")); // 개인상점 동작
			}
			else 
			{
				StringCchCopy(anicode, 256, TEXT("SLEP"));
			}
		}
		else
		{
			StringCchCopy(anicode, 256, TEXT("SLEP"));
		}		
		break;
	case ANITYPE_SLEEPCAT:

		if( GetKind() == KIND_HERO3 ||
			GetKind() == KIND_HEROINE3 ||
			GetKind() == KIND_HERO4 ||
			GetKind() == KIND_HEROINE4 )
		{        
			if( bLevelUpDrawSwitch == true )
			{
				StringCchCopy(anicode, 256, TEXT("SPC")); // 레벨업 동작
			}			
			else if( (siPersonalMakeItemType == MAKE_ANI_ARMOR) || (siPersonalMakeItemType == ENCHANT_ANI_WEPONE)|| (siPersonalMakeItemType == ENCHANT_ANI_ARMOR) )
			{			
				StringCchCopy(anicode, 256, TEXT("MAM")); // 무기 ,방어구 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_HEAL)
			{
				StringCchCopy(anicode, 256, TEXT("MHE")); // 약제 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_FOOD) 
			{
				StringCchCopy(anicode, 256, TEXT("MFO")); // 음식 제조동작
			}
			else if ( (bPersonalShopSwitch == true && bPremiumPersonalShop == true) || ( bIsElectionStump == true ) || bRepairShopSwitch == true ) 
			{
				StringCchCopy(anicode, 256, TEXT("SOP")); // 개인상점 동작
			}
			else 
			{
				StringCchCopy(anicode, 256, TEXT("SLEC"));
			}
		}
		else
		{
			StringCchCopy(anicode, 256, TEXT("SLEC"));
		}		
		break;
	case ANITYPE_FARM:
		StringCchCopy(anicode, 256, TEXT("FAM"));
		break;
	case ANITYPE_MINE:
		StringCchCopy(anicode, 256, TEXT("MIN"));
		break;
	case ANITYPE_SITDOWN:

		if( GetKind() == KIND_HERO3 ||
			GetKind() == KIND_HEROINE3 ||
			GetKind() == KIND_HERO4 ||
			GetKind() == KIND_HEROINE4 )
		{        
			if( bLevelUpDrawSwitch == true )
			{
				StringCchCopy(anicode, 256, TEXT("SPC")); // 레벨업 동작
			}			
			else if( (siPersonalMakeItemType == MAKE_ANI_ARMOR) || (siPersonalMakeItemType == ENCHANT_ANI_WEPONE)|| (siPersonalMakeItemType == ENCHANT_ANI_ARMOR) )
			{			
				StringCchCopy(anicode, 256, TEXT("MAM")); // 무기 ,방어구 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_HEAL)
			{
				StringCchCopy(anicode, 256, TEXT("MHE")); // 약제 제조동작
			}
			else if( siPersonalMakeItemType == MAKE_ANI_FOOD) 
			{
				StringCchCopy(anicode, 256, TEXT("MFO")); // 음식 제조동작
			}
			else if ( (bPersonalShopSwitch == true && bPremiumPersonalShop == true) || ( bIsElectionStump == true ) || bRepairShopSwitch == true ) 
			{
				StringCchCopy(anicode, 256, TEXT("SOP")); // 개인상점 동작
			}
			else
			{
				StringCchCopy(anicode, 256, TEXT("SIT"));
			}
		}
		else
		{
			StringCchCopy(anicode, 256, TEXT("SIT"));
		}		
		break;

	default:
		MsgBox(TEXT("mb98usdj"), TEXT("fk8jf:%d"), Animation);
		break;
	}

	//----------------------------------
	// 말을 타고 있는 상태인지 확인한다. 
	//----------------------------------
	//KHY - 1001 - 기승동물 5마리 보유 수정.
	if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false)
	{
		StringCchCat(anicode, 256, TEXT("U"));
	}
	else
	{
		StringCchCat(anicode, 256, TEXT("R"));
	}
	
	if(		_tcscmp(anicode, TEXT("1HSU")) == 0)return HSU1;
	else if(_tcscmp(anicode, TEXT("2HTU")) == 0)return HTU2;
	else if(_tcscmp(anicode, TEXT("2HBU")) == 0)return HBU2;
	else if(_tcscmp(anicode, TEXT("2HGU")) == 0)return HGU2;
	else if(_tcscmp(anicode, TEXT("WT1U")) == 0)return WT1U;
	else if(_tcscmp(anicode, TEXT("WT2U")) == 0)return WT2U;
	else if(_tcscmp(anicode, TEXT("DTHU")) == 0)return DTHU;
	else if(_tcscmp(anicode, TEXT("SPCU")) == 0)return SPCU;
	else if(_tcscmp(anicode, TEXT("MOVU")) == 0)return MOVU;
	else if(_tcscmp(anicode, TEXT("HITU")) == 0)return HITU;
	else if(_tcscmp(anicode, TEXT("1HSR")) == 0)return HSR1;
	else if(_tcscmp(anicode, TEXT("2HTR")) == 0)return HTR2;
	else if(_tcscmp(anicode, TEXT("2HBR")) == 0)return HBR2;
	else if(_tcscmp(anicode, TEXT("2HGR")) == 0)return HGR2;
	else if(_tcscmp(anicode, TEXT("SPCR")) == 0)return SPCR;
	else if(_tcscmp(anicode, TEXT("SPCU")) == 0)return SPCU;
	else if(_tcscmp(anicode, TEXT("WT1R")) == 0)
	{
		return WT1R;
	}
	else if(_tcscmp(anicode, TEXT("WT2R")) == 0)return WT2R;
	else if(_tcscmp(anicode, TEXT("DTHR")) == 0)return DTHR;
	else if(_tcscmp(anicode, TEXT("SPCR")) == 0)return SPCR;
	else if(_tcscmp(anicode, TEXT("MOVR")) == 0)return MOVR;
	else if(_tcscmp(anicode, TEXT("HITR")) == 0)return HITR;
	else if(_tcscmp(anicode, TEXT("FSHU")) == 0 || _tcscmp(anicode, TEXT("FSHR")) == 0 )
	{
		return FSHU;
	}
	else if(_tcscmp(anicode, TEXT("SLEPU")) == 0 || _tcscmp(anicode, TEXT("SLEPR")) == 0 )
	{
		return SLEP;
	}
	else if(_tcscmp(anicode, TEXT("SLECU")) == 0 || _tcscmp(anicode, TEXT("SLECR")) == 0 )
	{
		return SLEC;
	}
	else if(_tcscmp(anicode, TEXT("FAMU")) == 0 || _tcscmp(anicode, TEXT("FAMR")) == 0 )
	{
		return FAMU;
	}
	else if(_tcscmp(anicode, TEXT("MINU")) == 0 || _tcscmp(anicode, TEXT("MINR")) == 0 )
	{
		return MINU;
	}
	else if(_tcscmp(anicode, TEXT("SITU")) == 0 || _tcscmp(anicode, TEXT("SITR")) == 0 )
	{
		return SITU;
	}
	else if(_tcscmp(anicode, TEXT("MAMU")) == 0 ||  _tcscmp(anicode, TEXT("MAMR")) == 0  )
	{
		return MAMU;
	}
	else if(_tcscmp(anicode, TEXT("MHEU")) == 0 ||  _tcscmp(anicode, TEXT("MHER")) == 0  )
	{
		return MHEU;
	}
	else if(_tcscmp(anicode, TEXT("MFOU")) == 0 ||  _tcscmp(anicode, TEXT("MFOR")) == 0  )
	{
		return MFOU ;
	}
	else if(_tcscmp(anicode, TEXT("SOPU")) == 0 ||  _tcscmp(anicode, TEXT("SOPR")) == 0  )
	{
		return SOPU ;
	}			
	else
	{
		MsgBox(TEXT("fdih2d"), TEXT("fd9uj4:[%s]"), anicode);
	}

	return 0;
}

void cltCharCommon::SetAnimation(SI32 ani)
{
	SI32 delay, instant;
	Animation		= ani;
	bool bHero = GetKindInfo(true)->IsAtb(ATB_HERO);

	// by LEEKH 2007.12.24 - TRANSFORM
	if( clTransFormInfo.bTransFormMode == true )
	{
		// 변신인 경우... 변신전 캐릭터의 무기로 에니메이션을 처리한다.- 서버만...
		if( pclClient->GameMode == GAMEMODE_SERVER )
		{
			if( Animation == ANITYPE_ATTACK || Animation == ANITYPE_ATTACK1 || Animation == ANITYPE_ATTACK2 )
			{
				bHero = true;
			}
		}
	}

	if( bHero )
	{
		HeroAnimation	= CalcHeroAnimation();
		
		delay			= pclCharDraw->GetDelayTime(HeroAnimation, GetKind());
		if(Animation == ANITYPE_ATTACK || Animation == ANITYPE_ATTACK1 
		|| Animation == ANITYPE_ATTACK1 || Animation == ANITYPE_MAGIC)
		{
			//KHY - 1001 - 기승동물 5마리 보유 수정.
			//if(pclCI->clHorseInfo.siCurrentHorseIndex >=0)
			if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE)				
			{
				//instant = min(pclCharDraw->GetFrameNum(HeroAnimation)-1, 3);
				//cyj 스태프로 공격시 instant 쫌 늦도록 수정
				if (GetAttackType() == ATTACKTYPE_STAFF || GetAttackType() == ATTACKTYPE_STAFF1 ||
					GetAttackType() == ATTACKTYPE_STAFF2 || GetAttackType() == ATTACKTYPE_BOW || 
					GetAttackType() == ATTACKTYPE_BOW1 || GetAttackType() == ATTACKTYPE_NEW_BOW1 )
				{
					instant = min(pclCharDraw->GetFrameNum(HeroAnimation)-1, 6);
				}
				else
				{
					instant = min(pclCharDraw->GetFrameNum(HeroAnimation)-1, 3);
				}
			}
			else
			{
				instant = min(pclCharDraw->GetFrameNum(HeroAnimation)-1, 4);
			}
		}
		else
		{
			instant	= pclCharDraw->GetFrameNum(HeroAnimation) - 1 ;
		}
	}
	else
	{
		HeroAnimation	= 0;
		
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 aniref		= 0;
		
		if(selectRealAnyType( ))
		{
			if(Animation == ANITYPE_SLEEP)
			{
				HeroAnimation	= SLEP;
			}
			else if(Animation == ANITYPE_SLEEPCAT)
			{
				HeroAnimation	= SLEC;
			}
			
			aniref			= pclKI->clCharAniManager.FindRefFromAnitype(Animation);
			if(aniref == -1)
			{
				MsgBox(TEXT("SetAnimation(SI32 ani, SI32 *panistep)"), TEXT("kind:%d ani:%d"), GetKind(), Animation);
				return ;
			}

			// by LEEKH 2007.12.24 - TRANSFORM
			delay			= pclKI->clCharAniManager.GetDelay(aniref);
			instant			= pclKI->clCharAniManager.GetInstant(aniref);
		}
		else
		{
			aniref			= GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(Animation);
			if(aniref == -1)
			{
				MsgBox(TEXT("SetAnimation(SI32 ani, SI32 *panistep)"), TEXT("kind:%d ani:%d"), GetKind(), Animation);
				return ;
			}

			// by LEEKH 2007.12.24 - TRANSFORM
			delay			= GetKindInfo(true)->clCharAniManager.GetDelay(aniref);
			instant			= GetKindInfo(true)->clCharAniManager.GetInstant(aniref);
		}
	}

	clAniInfo.SetAniDelay(delay);
	clAniInfo.SetAniInstant( instant );

}


BOOL cltCharCommon::DoAnimationDelay(BOOL atb)
{
	SI32	delay;
	SI32	framenumber;

	// by LEEKH 2007.12.24 - TRANSFORM
	if( GetKindInfo(true)->IsAtb(ATB_HERO) )
	{
		framenumber = pclCharDraw->GetFrameNum(HeroAnimation);
	}
	else
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 aniref		= 0;

		if(selectRealAnyType( ))
		{
			aniref	= pclKI->clCharAniManager.FindRefFromAnitype(Animation);
			framenumber = pclKI->clCharAniManager.GetFrameNum(aniref);
		}
		else
		{
			aniref	= GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(Animation);
			framenumber = GetKindInfo(true)->clCharAniManager.GetFrameNum(aniref);
		}
	}
	if(framenumber == 0)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("GetFrameNum() Kind:%d ani:%d"), GetKind(), Animation);
	}


	//===============================================
	// 원래꺼
	//===============================================
	if ( ((cltClient*)pclClient)->GetFrameDelay() == 25 )
	{
		delay		= clAniInfo.siAniDelay * 2;
	}
	else
	{
		delay		= clAniInfo.siAniDelay;
	}

	clAniInfo.IncreaseAniDelayor(1);

	if(clAniInfo.GetAniDelayor() >= delay)
	{
		clAniInfo.SetAniDelayor(0);


		// 한번만 애니메이션 하게 되어 있는 경우, 
		// 프레임이 끝까지 갔다면, 
		// 더이상 애니메이션을 돌리지 않는다. 
		if((atb & ANIATB_ONLYONCE) && clAniInfo.GetAniStep() == (framenumber - 1))
		{
			return TRUE;
		}
		else
		{

			clAniInfo.IncreaseAniStep(1);

			if(framenumber == 0)
			{
				clAniInfo.SetAniStep(0);
			}
			else
			{
				clAniInfo.SetAniStep(clAniInfo.GetAniStep() % framenumber );
			}

			// 오토바이를 타고 있는 경우
			// 대기2, 이동 시에는 캐릭터의 첫번째와 마지막 프레임만 그린다.
			if( pclCI->clHorseInfo.GetCurrentHorseRIDEHORSE() && (HeroAnimation == WT2R || HeroAnimation == MOVR) )
			{
				cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				SI32 siHorseUnique = pclHorse->siHorseUnique;

				if( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM_HORSE) )
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM_HORSE);
					if( pclBuf )		siHorseUnique = pclBuf->siPercent;
				}

				if(siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
				{
					if( clAniInfo.GetAniStep() > 0 )
					{
						clAniInfo.SetAniStep(max(framenumber - 1, 0));
					}
				}
			}
		}

		bUpdateAnimationSwitch = true;

		return TRUE;
	}

	//===============================================



	//===============================================
	// 배틀 방식
	//===============================================
	//delay		= clAniInfo.siAniDelay;

	//// 한번만 애니메이션 하게 되어 있는 경우, 
	//// 프레임이 끝까지 갔다면, 
	//// 더이상 애니메이션을 돌리지 않는다. 
	//if((atb & ANIATB_ONLYONCE) )
	//{
	//	if(clAniInfo.GetAniStep() >= (framenumber - 1))
	//	{
	//		return TRUE;
	//	}
	//}


	//DWORD clockdelay	= TABS(pclClient->CurrentClock - dwAniStartClock);
	//DWORD delayperframe = max(50, delay*50);
	//SI32 frame			= clockdelay / delayperframe;
	//if(frame >= framenumber)
	//{
	//	frame = 0;
	//	clAniInfo.siRetryNum++;	// 반복회수를 구한다. 
	//}

	//SI32 frame2			= min(framenumber-1, frame);

	// 중요장면은 반드시 나오게 한다. 
	// 이전의 anistep을 구한다. 
	//SI32 oldanistep = clAniInfo.GetAniStep();
	//if(oldanistep < clAniInfo.siAniInstant && clAniInfo.siAniInstant < frame2)
	//{
	//	frame2 = clAniInfo.siAniInstant;
	//}

	//clAniInfo.SetAniStep( frame2 );
	//bUpdateAnimationSwitch = true;


	//if(frame2 == 0)
	//{
	//	// 애니메이션 시작 시간을 확보한다. 
	//	if(clockdelay > delayperframe)
	//	{
	//		dwAniStartClock = pclClient->CurrentClock;
	//	}
	//}

	//if(framenumber == 0)
	//{
	//	clAniInfo.SetAniStep(0);
	//}
	//
	//// ANIATB_ONLYONCE속성일때 true를 리턴하는 것은 애니가 완료되었다는 의미이다. 
	//if((atb & ANIATB_ONLYONCE) == 0)
	//{
	//	return TRUE;
	//}

	//===============================================

	return FALSE;
}


// 캐릭터의 방향을 전환한다. 
BOOL cltCharCommon::ChangeDirectionNormal(SHORT destdir)
{
	siDirection=destdir;
	TempDirection=destdir;

	bUpdateAnimationSwitch = true;

	return TRUE;
}

// 캐릭터의 방향을 전환한다. 
BOOL cltCharCommon::ChangeDirection16(SHORT destdir)
{
	SHORT index=0;
	SHORT source_index=0;
	SHORT rotate_dir;
	SHORT dir[]={SOUTH, SSW, SOUTH|WEST, WWS, WEST, WWN, NORTH|WEST, NNW, 
		         NORTH, NNE, NORTH|EAST, EEN, EAST, EES, SOUTH|EAST, SSE };

	if(TempDirection==destdir)
	{
		bBusySwitch  = false;
		return TRUE;
	}


	bBusySwitch = true;

	// 방향을 결정한다. 
	index=0;
	bool roop = true;
	while(roop)
	{
		if(dir[index]==TempDirection)
		{
			source_index=index;
			break;
		}
		index++;
	}

	index=0;
	while(roop)
	{
		if(dir[(source_index+index)%16]==destdir)
		{
			break;
		}
		index++;
	}

	// 반시계 방향으로 회전 
	if(index>=8)
	{
        rotate_dir=FALSE;
	}
	else 
	{
		rotate_dir=TRUE;
	}


	if(rotate_dir==TRUE)
	{
	  TempDirection=dir[(source_index+1)%16];
	}
	else 
	{
		if(source_index-1==-1)
	       TempDirection=dir[15];
		else 
			TempDirection=dir[source_index-1];
	}
	
	if(TempDirection<1000)
	{
		siDirection = TempDirection;
	}
	else
	{

	}

	bUpdateAnimationSwitch = true;

	return FALSE;
}

BOOL cltCharCommon::ChangeDirection(SHORT destdir)
{
   return ChangeDirectionNormal(destdir);
}

//----------------------------------
// 전송 함수. 
//----------------------------------
void cltCharCommon::SendNetMsg(sPacketHeader* pmsg)
{
	if(IsValidConnection()== false)return ;

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		cltServer* pclserver = (cltServer*)pclClient;
		cltMsg* pclMsg = (cltMsg*)pmsg;
		if(pclMsg->GetTotalSize() > sizeof(cltMsg))
		{
			MsgBox(TEXT("SendNetMsg Overflow"), TEXT("cmd:%d size:%d"), pclMsg->clHead.usCmd, pclMsg->GetTotalSize());
			SI32 a = 0;
		}

		UI32 uiCompSize = 0;
		EnterCriticalSection( &pclserver->m_cs_SendNetMsg );
		{
			if( pclserver->m_uiCompressMinSize > 0 && pmsg->usSize >= pclserver->m_uiCompressMinSize )		// 지정된 바이트이상만 압축한다.
			{
				BYTE* pMsg = (BYTE*)pmsg;
				BYTE* pbufComp = pclserver->m_bufComp;
				memcpy(pbufComp, pmsg, sizeof(sPacketHeader));
				uiCompSize = GetSession()->Compress( &pMsg[sizeof(sPacketHeader)],		pmsg->usSize - sizeof(sPacketHeader),			// SOURCE
													 &pbufComp[sizeof(sPacketHeader)],	sizeof(pclserver->m_bufComp) - sizeof(sPacketHeader) );		// COMPRESS BUFFER
				if( uiCompSize > 0 )	
				{
					sPacketHeader* pCompMsg = (sPacketHeader*)pbufComp;
					pCompMsg->usSize = sizeof(sPacketHeader) + uiCompSize;

					// 패킷 명령의 최상위 비트를 세트하면, 패킷이 압축된 것이다.
					pCompMsg->usCmd |= 0x8000;

					GetSendBuffer()->Write( pbufComp );		// 압축된 데이터를 보낸다.
				}
				else
				{
					GetSendBuffer()->Write( (BYTE*)pmsg );	// // 압축에 실패해서 원본을 보낸다 - 속도 최적화
				}
			}
			else
			{
				GetSendBuffer()->Write( (BYTE*)pmsg );		// // 압축에 실패해서 원본을 보낸다 - 속도 최적화
			}
		}
		LeaveCriticalSection( &pclserver->m_cs_SendNetMsg );

		// 클라이언트로 보내진 메시지를 집계한다. 
		((cltServer*)pclClient)->pclStatisticsManager->clDailyStatistics.siSendToClientMsgNumber++;

		//NStatistics_Add("NetMessage", pmsg->usCmd, "SendCount", 1);
		//NStatistics_Add("NetMessage", pmsg->usCmd, "SendSize", pclMsg->clHead.usSize);

#ifdef WRITE_NETMESSAGE_STATISTICS
		//-------------------------------------------
		// 보낸 메시지 개수를 카운트 한다.
		//-------------------------------------------
		if( ((cltServer*)pclClient)->pclGameProtocol != NULL &&
			pmsg->usCmd >= 0 && pmsg->usCmd < GAMEMSG_END )
		{
			((cltServer*)pclClient)->pclGameProtocol->m_clNetMessageStatistics[pmsg->usCmd].m_siSend++;
			((cltServer*)pclClient)->pclGameProtocol->m_clNetMessageStatistics[pmsg->usCmd].m_siSize = pclMsg->clHead.usSize;
		}
#endif
	}
	else
	{
		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->SendMsgToServer(pmsg);
	}
}


// 연결이 되어 있는 Person인지 여부. 
bool cltCharCommon::IsValidConnection()
{
	ITZSession*	pSession = GetSession();

	if(pSession == NULL)return false;

	if(pSession->GetState() != SESSION_STATE_ESTABLISHED)return false;

	return true;


}


//---------------------------------
// 피격
//---------------------------------

// 피격 행위를 취한다. 
bool cltCharCommon::BeHitOperation()
{
	if(bHitSwitch == false)return false;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 aniref = GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(ANITYPE_HIT);
	if(aniref < 0)return false;


	SetAnimation(ANITYPE_HIT);
	bUpdateAnimationSwitch	=	true;

	if(DoAnimationDelay() == TRUE)
	{
		SetHitSwitch(false);

		clMoveInfo.dwLastMoveClock	= pclClient->CurrentClock;
		clMoveInfo.siSparePercent	= 0;
	}

	if( IsPC( GetID() ) )
	{
		switch( GetCurrentOrder() )
		{
		case ORDER_MOVE:
		case ORDER_ATTACK:
		case ORDER_ATTACK_SUMMON:
		case ORDER_MAGIC:
		case ORDER_MAGIC_SUMMON:
		case ORDER_MOVE_SUMMON:
		case ORDER_ATTACK_CLIENT:
			break;
		default:
			OrderForceStop( GetID(), BY_PLAYER );
			break;
		}
	}

	return true;
}

//---------------------------------
// 무게 
//---------------------------------
SI32 cltCharCommon::GetTotalWeight()
{
	return pclCI->clCharItem.GetTotalWeight(pclClient->pclItemManager);
}


//---------------------------------
// 정보 텍스트 
//---------------------------------

// 캐릭터의 정보를 텍스트로 정리해서 받는다.
bool cltCharCommon::GetCharInfoText(TCHAR* buffer)
{
	TCHAR* pmapname = pclClient->pclMapManager->GetMapName(pclMap->siMapIndex);

	if(pmapname == false)return false;

	TCHAR* pText = GetTxtFromMgr(2804);
	StringCchPrintf(buffer, 1024, pText,
		
		GetName(), GetID(), 
		pclCI->GetPersonID(), 
		GetKind(), 
		pmapname,
		GetX(), GetY(), 
		GetCurrentOrder(),
		siSubOrder,
		GetLife(), clPB.GetMaxLife(), GetMana(), clPB.GetMaxMana(), 
		GetAttackType(), GetAttackRange(), clPB.GetTotalMoveSpeed(), 
		clPB.GetTotalMinDamage(), clPB.GetTotalMaxDamage(), clPB.GetTotalAC(), 
		pclCI->clIP.GetLevel(), pclCI->clIP.GetCurExp(), 
		GetStr(), GetDex(), GetMag(), GetVit() ,GetWis());

	return true;

}

//------------------------------------------------
// 소환인형으로 소환수를 생성할수 있는지 검사한다.
//-----------------------------------------------
bool cltCharCommon::CanUseSummonDoll(SI32 itemunique, SI32 *summonkind, SI32 *summonindex, SI32 *preturn)
{
	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;
	
	// 소환수 초기화 
	*summonkind		= 0;
	*summonindex	= -1;

	// 반환값 초기화
	*preturn = CANUSEITEM_ERROR_INVALID;

	// DB와 통신 중이므로 소환수를 생성할 수 없다.
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		if( ((cltCharServer*)this)->bIsNowAddSummonThroughDB )		return false;
	}

	//---------------------------------------------
	// [기형] 배틀로얄맵에 있다면 사용 불가
	//---------------------------------------------
	if( (MAPINDEX_BATTLEROYAL_MABRIUM == GetMapIndex()) 
		|| ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == GetMapIndex()))
	{
		*preturn	= CANUSEITEM_ERROR_BATTLEROYALMAP;
		return false;
	}

	//=========================================================================
	// Level이 되어야 사용할수 있다.
	//=========================================================================
	if(pclCI->clIP.GetLevel() < LIMIT_LEVEL_HATCH_DOLL )
	{
		*preturn	= CANUSEITEM_ERROR_NEEDLEVEL;
		return false;
	}
	
	//=========================================================================
	// DOLL 아이템의 해당 Monter Kind를 소환가능한지 살펴본다.
	//=========================================================================
	pclItemManager->GetItemDollUnique(itemunique);
	SI32 ref = pclItemManager->FindItemRefFromUnique(itemunique);
	if(ref <= 0)
	{
		*preturn	= CANUSEITEM_ERROR_NOUSEABLE;
		return false;
	}
	
	SI32 kind = pclItemManager->pclItemInfo[ref]->siMakeKind;
	if(kind < 0 || kind >= MAX_KINDINFO_NUMBER)
	{
		*preturn	= CANUSEITEM_ERROR_NOUSEABLE;
		return false;
	}
	if(pclClient->pclKindInfoSet->pclKI[kind]->IsAtb(ATB_DEFAULTSUMMON) == FALSE)
	{
		*preturn	= CANUSEITEM_ERROR_NOUSEABLE;
		return false;
	}

	// 국가코드를 가진 소환영웅이라면 자신의 국가코드랑 맞아야 소환할 수 있다.
	if ( pclClient->pclKindInfoSet->pclKI[kind]->siDefaultCountry > 0 &&
		 pclKI->siDefaultCountry != pclClient->pclKindInfoSet->pclKI[kind]->siDefaultCountry )
	{
		*preturn	= CANUSEITEM_ERROR_NOCOUNTRY;
		return false;
	}

	//=========================================================================
	// 지금 소환수가 밖에 나와 있는지 소환수를 갖을 공간은 있는지 검사한다.
	//=========================================================================
	BOOL bIsEmpty = FALSE;
	if ( pclClient->IsCountrySwitch(Switch_SummonHouse) )
	{
		if ( FALSE == pclCI->clSummonInfo.GetEmptySummonIndexInHouse(summonindex) )
		{
			*preturn = CANUSEITEM_ERROR_CANTOVERSLOT;
			return false;
		}

		// 티켓이 없으면 생성할 수 없다.
		if( *summonindex > 2 )
		{
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				cltServer* pclserver = (cltServer*)pclClient;
				if( pclCI->clBI.bSummonExtraSlot == false || pclCI->clBI.siSummonExtraSlotDate <= pclserver->pclTime->clDate.GetDateVary() )
				{
					*preturn = CANUSEITEM_ERROR_TICKETOVERDATE;
					*summonindex = -1;
					pclserver->SendServerResponseMsg(0, SRVAL_SUMMON_FAIL_LOTSOFDATE,  0, 0, GetCharUnique());// 사용기간이 종료 되었습니다.
					return false;
				}
			}
			else if(pclClient->GameMode == GAMEMODE_CLIENT)
			{
				cltClient* pclclient = (cltClient*)pclClient;
				if( pclCI->clBI.bSummonExtraSlot == false || pclCI->clBI.siSummonExtraSlotDate <= pclclient->clClientDate.GetDateVary() )
				{
					*preturn = CANUSEITEM_ERROR_TICKETOVERDATE;
					*summonindex = -1;
					return false;
				}
			}
		}
	}
	else
	{
		if ( FALSE == pclCI->clSummonInfo.GetEmptySummonIndex(summonindex) )
		{
			*preturn = CANUSEITEM_ERROR_SUMMON_NOMORE;
			return false;
		}
	}

	// 소환수의 Kind를 돌려준다.
	*summonkind = kind;
	return true;
}

bool cltCharCommon::CanUseSoulGuardItem( SI32 siItemUnique, SI16* psiSoulGuardKind, SI16* psiLife, SI16* psiFellowShip, SI32* pReturn )
{
	if ( (NULL == psiSoulGuardKind) || (NULL == psiLife) || (NULL == psiFellowShip) || (NULL == pReturn) )
	{
		return false;
	}

	// 리턴값 초기화
	*psiSoulGuardKind	= 0;
	*psiLife			= 0;
	*psiFellowShip		= 0;
	*pReturn			= CANUSEITEM_ERROR_INVALID;

	if ( false == pclClient->IsCountrySwitch(Switch_SoulGuard) )
	{
		return false;
	}

	// DB와 통신 중이므로 수호정령을 소환하지 못함
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if( ((cltCharServer*)this)->bIsNowAddSoulGuardThroughDB )
		{
			return false;
		}
	}

	//---------------------------------------------
	// [기형] 배틀로얄맵에 있다면 사용 불가
	//---------------------------------------------
	if( (MAPINDEX_BATTLEROYAL_MABRIUM == GetMapIndex()) 
		|| ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == GetMapIndex()))
	{
		*pReturn	= CANUSEITEM_ERROR_BATTLEROYALMAP;
		return false;
	}


	if ( NULL == pclSoulGuard )
	{
		return false;
	}

	// 이미 수호정령을 갖고 있다면
	if ( FALSE == pclSoulGuard->IsEmpty() )
	{
		// 수호정령 보관소에 넣을수 있는가?
		SI32 siMaxHaveHouseNum = pclSoulGuard->m_clHouse.GetMaxHaveHouseNum();
		if ( 0 < siMaxHaveHouseNum )
		{
			SI32 siHaveCount	= 0;
			SI32 siRealHaveNum	= (siMaxHaveHouseNum>MAX_SOULGUARD_HOUSE_NUM?MAX_SOULGUARD_HOUSE_NUM:siMaxHaveHouseNum);
			for ( SI32 siIndex=0; siIndex<siRealHaveNum; siIndex++ )
			{
				if ( 0 < pclSoulGuard->m_clHouse.GetSoulGuardIDFromIndex(siIndex) )
				{
					siHaveCount++;
				}
			}

			// 갖고 있는것과 갖을수 있는 갯수가 같은면 더이상 갖을수없음
			if ( siRealHaveNum <= siHaveCount )
			{
				*pReturn = CANUSEITEM_ERROR_SOULGUARD_NOMORE;
				return false;
			}

		}
		else 
		{
			*pReturn = CANUSEITEM_ERROR_SOULGUARD_NOMORE;
			return false;
		}
	}

	if ( NULL == pclClient->m_pclSoulGuardMgr )
	{
		return false;
	}

	// 아이템 유니크에 해당하는 수호정령 소환 정보를 가져온다
	cltSoulGuardInfoUnit* pclGetUnit = pclClient->m_pclSoulGuardMgr->GetSoulGuardUnitFromItemUnique( siItemUnique );
	if ( NULL == pclGetUnit )
	{
		return false;
	}

	*psiSoulGuardKind	= pclGetUnit->GetKindUnique();
	*psiLife			= pclGetUnit->GetLife();
	*psiFellowShip		= pclGetUnit->GetFellowShip();

	return true;		
}

//------------------------------------------------
// 아이템 관련 
//-----------------------------------------------
// 아이템을 사용할수 있는 것인지 확인한다. 
bool cltCharCommon::CanUseItem(cltItem clitem, SI32* preturn, SI32 siPos)
{

	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;
	
	//=================================
	// return 초기화
	//=================================
	*preturn = CANUSEITEM_ERROR_INVALID;

	// 아이템이 유효하지 않으면 사용할 수 없다. 
	if(clitem.siUnique == 0)
	{
		return false;
	}
	
	// 아이템을 사용하는 자가 죽었으면 사용할 수 없다. 
	if(pclCI->clIP.GetLife() <= 0)	// 축복받은 부활약이 아니고 죽었을때 
	{
		*preturn	= CANUSEITEM_ERROR_DEADCHAR;
		return false;
	}

	SI32 itemunique = clitem.siUnique;
	SI32 ref		= pclItemManager->FindItemRefFromUnique(itemunique);
	if(ref <= 0)
	{
		*preturn	= CANUSEITEM_ERROR_INVALID;
		return false;
	}

	SI32 itemtype	= pclItemManager->pclItemInfo[ref]->siType;
	SI64 itematb	= pclItemManager->pclItemTypeInfo[itemtype]->siAtb;
	
	// 사용속성이 아니면 실패.
	if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_CANUSEITEM) == false)	// 흥부박. 
	{
		*preturn	= CANUSEITEM_ERROR_NOUSEABLE;
		return false;
	}
	
	switch(itemtype)
	{
	case ITEMTYPE_DOLL:
		{

			SI32 siKind = 0, siSummonIndex = 0;
			// 해당 소환인형으로 소환수를 생성할수 있는지를 검사한다.
			return CanUseSummonDoll(itemunique, &siKind, &siSummonIndex, preturn);
		
		}
		break;

	case ITEMTYPE_FOOD:
	case ITEMTYPE_SEAFOOD:
		{
			// 변신 아이템
			if( itemunique == ITEMUNIQUE(3934) || itemunique == ITEMUNIQUE(3931) 
				|| itemunique == ITEMUNIQUE(3930) || itemunique == ITEMUNIQUE(3929)
				|| itemunique == ITEMUNIQUE(3932)|| itemunique == ITEMUNIQUE(3933))
			{
				//---------------------------------------------
				// [기형] 배틀로얄맵에 있다면 사용 불가
				//---------------------------------------------
				if( (MAPINDEX_BATTLEROYAL_MABRIUM == GetMapIndex()) 
					|| ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == GetMapIndex()))
				{
					*preturn	= CANUSEITEM_ERROR_BATTLEROYALMAP;
					return false;
				}
			}

			//cyj 극상초코 사용중이면 사용불가
			if( itemunique == ITEMUNIQUE(3860) || itemunique == ITEMUNIQUE(3865) || itemunique == ITEMUNIQUE(3870) )
			{
				if ( pclCI->clBI.bPremiumService )
				{
					*preturn = CANUSEITEM_ERROR_NOMOREUSE;
					return false ;
				}
			}
			//cyj 떡갈나무 찰떡, 제조 만쥬 이면 사용불가
			else if( itemunique == ITEMUNIQUE(3875) || itemunique == ITEMUNIQUE(3880))
			{
				if ( pclCI->clBI.bMakeItemService )
				{
					*preturn = CANUSEITEM_ERROR_NOMOREUSE;
					return false ;
				} // if ( pclCI->clBI.bMakeItemService )

				if ( pclCI->clBI.clBufInfo.CanUseBuf(BUF_MAKEEXPUP) == false )
				{
					*preturn = CANUSEITEM_ERROR_NOMOREUSE;
					return false ;
				}
			}
			// 장인의 초쿄
			else if( itemunique == ITEMUNIQUE(3903) )
			{
				if ( pclCI->clBI.bMakeItemService )
				{
					*preturn = CANUSEITEM_ERROR_NOMOREUSE;
					return false ;
				}

				if ( pclCI->clBI.clBufInfo.CanUseBuf(BUF_NOTBONUSTIME_MAKEEXPUP) == false )
				{
					*preturn = CANUSEITEM_ERROR_NOMOREUSE;
					return false ;
				}
			}
			// 수호정령 친화력 상승제
			else if( ITEMUNIQUE(3928) == itemunique )
			{
				if ( NULL == pclSoulGuard )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}

				if ( FALSE == IsSoulGuardStatusOut() )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}

				if ( Const_Max_SoulGuard_FellowShip <= pclSoulGuard->GetFellowShip() )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}
			}
			// 말용음식인데 말이 없으면 실패. 
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 1)
			{
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

				// 말이 없으면 사용할 수 없다. 
				if(pclhorse == NULL || pclhorse->siHorseUnique <= 0 || pclhorse->siHorseUnique == 9 )
				{
					*preturn	= CANUSEITEM_ERROR_NOHORSE;
					return false;
				}
			}
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 2)
			{
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

				// 말이 없으면 사용할 수 없다. 
				if( pclhorse == NULL || pclhorse->siHorseUnique != 9 )
				{
					*preturn	= CANUSEITEM_ERROR_NOHORSE;
					return false;
				}
			}
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 3)
			{
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

				// 말이 없으면 사용할 수 없다. 
				if(pclhorse == NULL || pclhorse->siHorseUnique <= 0 )
				{
					*preturn	= CANUSEITEM_ERROR_NOHORSE;
					return false;
				}
			}
			else if ( pclItemManager->pclItemInfo[ref]->bFishingBaitSwitch == true )
			{
				// 근처에 낚시할 곳이 없다면 사용할 수 없다.				
				SI32 dir = 0;
				if(IsFishArea(GetX(), GetY(), &dir) == false)
				{
					*preturn	= CANUSEITEM_ERROR_NOPROPERFISHAREA;
					return false;
				}
			}			
			//-----------------------------------
			// 사용제한 확인. 
			//-----------------------------------
			SI32 returnval = 0;
			if( pclItemManager->CheckCondition(itemunique, this, &returnval) == false )
			{
				*preturn	= CANUSEITEM_ERROR_NOTFITCOND;
				return false;
			}
		}
		break;
	case ITEMTYPE_ANIMAL:
		{
			//---------------------------------------------
			// [기형] 배틀로얄맵에 있다면 사용 불가
			//---------------------------------------------
			if( (MAPINDEX_BATTLEROYAL_MABRIUM == GetMapIndex()) 
				|| ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == GetMapIndex()))
			{
				*preturn	= CANUSEITEM_ERROR_BATTLEROYALMAP;
				return false;
			}

			//KHY - 1001 - 기승동물 5마리 보유 수정.
			//if(!(pclClient->IsWhereServiceArea(ConstSwitch_Can5Horse)))
			if(!(pclClient->IsCountrySwitch(Switch_Can5Horse)))
			{
				if(pclCI->clHorseInfo.HaveHorse()== true) //말이 한마리라도 있으면, 더이상 만들수 없다. - 미적용국가를위해
					return false;
			}
			if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE)				
			{
				*preturn	= CANUSEITEM_ERROR_RIDEHORSEUSEITEM; 	// 말에 올라탄 상태에서 아이템을 사용했다.
				return false;
			}
			// 이미 말이 있는 상태에서는 사용불가. 
			if(pclCI->clHorseInfo.FindEmptyHorseIndex() < 0)
			{
				//KHY - 1001 - 기승동물 5마리 보유 수정.
				*preturn	= CANUSEITEM_ERROR_OVERMAXHORSE; //최대값 이상의 말을 만들수 없다.
				return false;
			}

			//-----------------------------------
			// 사용제한 확인. 
			//-----------------------------------
			SI32 retunval = 0;
			if( pclItemManager->CheckCondition(itemunique, this, &retunval) == false )
			{
				*preturn	= CANUSEITEM_ERROR_NOTFITCOND;
				return false;
			}
		}
		break;
	case ITEMTYPE_TICKET:
	case ITEMTYPE_ETC:
		{			
			//	[종호][수정] 녹색보이노리코(8114) 도 소환알과 마찬가지로 사용위치 제약 
			// PCK : 수수께끼 소환알 1,2, 녹색보이노리코, 보물찾기이벤트 몬스터 소환알에 최대 NPC갯수가 넘어가면 사용하지 못하도록 수정함(09.07.02)
			if ( (ITEMUNIQUE( 7860 ) == clitem.siUnique) || (ITEMUNIQUE( 7865 ) == clitem.siUnique) || (ITEMUNIQUE( 8114 ) == clitem.siUnique) || (ITEMUNIQUE( 13057 ) == clitem.siUnique) )	// 소환알	
			{
				if ( ((GetMapIndex() == MAPINDEX_BEGINNER1) 
					|| (GetMapIndex() == MAPINDEX_PALACE) 
					|| (GetMapIndex() == MAPINDEX_MOFUMOFULAND)
					|| (GetMapIndex() == Const_MapIndex_PollMap)
					|| (GetMapIndex() == MAPINDEX_PRIVATEMARKETAREA)
					|| (GetMapIndex() == MAPINDEX_WEDDINGHALL)
					|| (GetMapIndex() == MAPINDEX_FESTIVAL)		// 복불복 이벤트 맵에서 소환알 사용하지 못하도록 제약.
					|| (GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM )
					|| (GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM ))
					|| (pclClient->pclCM->pclIDManager->GetNPCCharNumber() > MAX_NPC_NUMBER - 1000)
				)
				{
					*preturn	= CANUSEITEM_ERROR_NOUSE_THISPLACE;

					return false;
				}
			}
			// 애정도 올리기 (분홍장미), (장미꽃다발)
			else if ( (ITEMUNIQUE(8119) == clitem.siUnique) || (ITEMUNIQUE(8120) == clitem.siUnique) )
			{
				if ( NULL == pclMarriage )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}
				
				// 결혼 안했다면
				if ( FALSE == pclMarriage->IsMarried() )
				{
					*preturn = CANUSEITEM_ERROR_NOTMARRIED;
					return false;
				}
				
				/*
				// 이미 최고 애정도라면
				if ( MARRIAGE_LOVE_LEVEL_10 <= pclMarriage->GetLoveLevel() )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}
				*/

				// 상대방이 같은맵에 접속해 있지 않다면
				if ( MARRIAGE_MATE_CONNECT_MODE_SAMEMAP != pclMarriage->GetConnectMode() )
				{
					*preturn = CANUSEITEM_ERROR_CANNOT_SAMEMAP;
					return false;
				}

				// 그냥 장미 일때만 시간 검사를 한다
				if ( ITEMUNIQUE(8119) == clitem.siUnique )
				{
					// 사용 가능 시간 체크
					cltDate clCanUseTime;

					if ( GAMEMODE_CLIENT == pclClient->GameMode )		clCanUseTime.Set( &((cltClient*)pclClient)->clClientDate );
					else if ( GAMEMODE_SERVER == pclClient->GameMode )	clCanUseTime.Set( &((cltServer*)pclClient)->pclTime->clDate );

					// +10 은 현실 시간으로 20분
					if ( (0 < pclMarriage->GetUseHourVary()) && ((pclMarriage->GetUseHourVary() +10) > clCanUseTime.GetHourVary()) )
					{
						*preturn = CANUSEITEM_ERROR_CAN_NOT_USETIME;
						return false;
					}
				}
			}
			else if( itemunique == ITEMUNIQUE(8122) )	//간식용 쿠키
			{
				if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
				{
					// 사용 가능 시간 체크
					cltDate clCanUseTime;
					if ( GAMEMODE_CLIENT == pclClient->GameMode )		clCanUseTime.Set( &((cltClient*)pclClient)->clClientDate );
					else if ( GAMEMODE_SERVER == pclClient->GameMode )	clCanUseTime.Set( &((cltServer*)pclClient)->pclTime->clDate );
					// +10 은 현실 시간으로 20분
					if( pclFamily != NULL )
					{
						SI32 siPersonID = pclCI->GetPersonID();
						if (siPersonID < 0) return false;
						SI32 siParent_PeronID_First = 0	;
						SI32 siParent_PeronID_Second = 0	;
						siParent_PeronID_First = pclFamily->GetParent_1()	;
						siParent_PeronID_Second = pclFamily->GetParent_2()	;
						if ( siParent_PeronID_First <= 0 ||  siParent_PeronID_Second <= 0 )	return	false	;
						SI32 siMyClass = 0	;
						siMyClass = pclFamily->GetMyClass_InFamily();
						if(siMyClass != MYCLASS_IN_FAMILY_CHILDREN)	return false;
                        SI32 siDatevary =	0	;
						siDatevary = pclFamily->GetMyCookie_Limitime( siPersonID )		;
						
						if ( 0 < siDatevary )
						{
							SI32 siHourvary = clCanUseTime.GetHourVary()	;
							if ( siDatevary >  siHourvary )
							{
								*preturn = CANUSEITEM_ERROR_CANNOT_USE_COOKIE_NO_OVER_TIME;
								return false;
							}							
						}
					}
					else
					{
						return false;
					}
				}				
			}
			// PCK : 잃어버린 세계 퀘스트 - 일부 아이템은 사용하지 못하게 한다.
			else if(clitem.siUnique == ITEMUNIQUE(8115) || clitem.siUnique == ITEMUNIQUE(8116))
			{
				*preturn = CANUSEITEM_ERROR_NOUSEABLE;
				return false ;
			}
			// PCK : 정찰변신약은 퀘스트 수행시에만 사용할수있다.
			else if(clitem.siUnique == ITEMUNIQUE(8117) )
			{
				SI16 siMonsterKind = (SI16)pclClient->GetUniqueFromHash( TEXT("KIND_TRICERAMONS") );
				if ( 0 >= siMonsterKind )
				{
					*preturn = CANUSEITEM_ERROR_NOUSEABLE;
					return false ;
				}
				
				if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS, siMonsterKind) )
				{
					*preturn = CANUSEITEM_ERROR_NOUSEABLE;
					return false ;
				}
			}
			// [춘기] 공격방어제는 퀘스트 수행시에만 사용할수있다
			else if(clitem.siUnique == ITEMUNIQUE(8118) )
			{
				SI16 siMonsterKind = (SI16)pclClient->GetUniqueFromHash( TEXT("KIND_BONETYRANNO") );
				if ( 0 >= siMonsterKind )
				{
					*preturn = CANUSEITEM_ERROR_NOUSEABLE;
					return false ;
				}

				if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMON, siMonsterKind) )
				{
					*preturn = CANUSEITEM_ERROR_NOUSEABLE;
					return false ;
				}
			}
			// PCK : 아이템 타입 ETC로 이동(09.06.17)
			else if(clitem.siUnique == ITEMUNIQUE(8121))
			{
				SI16 siMonsterKind = (SI16)pclClient->GetUniqueFromHash( TEXT("KIND_QUESTEMPERORMASTER") );
				if ( 0 >= siMonsterKind )
				{
					*preturn = CANUSEITEM_ERROR_INVALID;
					return false;
				}

				if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMON, siMonsterKind) )
				{
					*preturn = CANUSEITEM_ERROR_NOTFITCOND;
					return false;
				}
			}

			else if(clitem.siUnique == ITEMUNIQUE(8150))	// 마력 제어기 사용시
			{
				// 마력 제어기는 특정 좌표에서만 사용 가능 합니다.
				SI32 siPosX = 84;
				SI32 siPosY = 9;
                
				if(GetMapIndex() != MAPINDEX_LABYRINTH_1 || GetX() != siPosX || GetY() != siPosY)
				{
					*preturn = CANUSEITEM_ERROR_NOTFITCOND;
					return false ;
				}
			}
		}
		break;
	case ITEMTYPE_HEAL:
		{
				// 배틀로얄 - 약사용 불가 모드
				if( pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltServer* pclServer = (cltServer*)pclClient;
					CBattleRoyalMgr* pclBattleRoyalMgr = pclServer->m_pclBattleRoyalMgr;
					if( NULL != pclBattleRoyalMgr)
					{
						CBattleRoyal* pclBattleRoyal = pclBattleRoyalMgr->GetBattleRoyal((cltCharServer*)this);
						if( NULL != pclBattleRoyal)
						{
							if(!pclBattleRoyal->CanUseHealItem() && pclBattleRoyal->IsExistStadium((cltCharServer*)this) && pclBattleRoyal->IsGamingState())
							{
								*preturn = CANUSEITEM_ERROR_BATTLEROYALMAP;
								return false;

							}
						}
					}
				}

				// 프리미엄 효과가 있다면
				if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUM )
				{
					if ( pclCI->clBI.bPremiumService )
					{
						*preturn = CANUSEITEM_ERROR_NOMOREUSE;
						return false ;
					}
				}
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_COMBAT )
				{
					if ( pclCI->clBI.bCombatService )
					{
						*preturn = CANUSEITEM_ERROR_NOMOREUSE;
						return false ;
					}
				}
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_BULLET )
				{
					if ( pclCI->clBI.bBulletService)
					{
						*preturn = CANUSEITEM_ERROR_NOMOREUSE;
						return false ;
					}
				}
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUMMONSTAMINA )
				{
					if ( pclCI->clBI.bSummonStaminaService)
					{
						*preturn = CANUSEITEM_ERROR_NOMOREUSE;
						return false ;
					}
				}
				// 설사제는 배가 터질것 같을 때 만 사용가능하다.
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_DIGESTIVE )
				{		
	
 					if ( ( clPB.clHealth.GetHungryStatus( pclCI->clIP.GetLevel()) & (HEALTH_STATUS_HUNGRY_1 | HEALTH_STATUS_HUNGRY_2 | HEALTH_STATUS_HUNGRY_3 ) ) == FALSE)
					{
						
						*preturn = CANUSEITEM_ERROR_NOMORE_DIGEST;
						return false ;
					}
				}
				// 만능약은 상태가 안좋을 때 만 사용가능하다.
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ALLDESEASE )
				{	
					cltCurDisease clCurdisease;					
					if(clPB.clHealth.GetCurDisease(&clCurdisease) == false)
					{
						*preturn = CANUSEITEM_ERROR_NOMORE_DESEASE;
						return false ;
					}
				}
				// 부활약은 죽어있을때 사용하기때문에 일반적으로 소모시킬수 없다.
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESURRECTION )
				{	
					*preturn = CANUSEITEM_ERROR_NOUSEABLE;
					return false ;
				}
				// [영훈] 안티포션은 퀘스트 수행시에만 사용할수있다
				else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_QUEST_ANTIPOTION )
				{
					SI16 siMonsterKind = (SI16)pclClient->GetUniqueFromHash( TEXT("KIND_GREATWALLASURA") );
					if ( 0 >= siMonsterKind )
					{
						*preturn = CANUSEITEM_ERROR_NOUSEABLE;
						return false ;
					}
					
					if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMON, siMonsterKind) )
					{
						*preturn = CANUSEITEM_ERROR_NOUSEABLE;
						return false ;
					}
				}

				cltHorse * pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse()	;//현제 타고 있는 말을 가지고 온다
				if ( pclHorse != NULL )
				{
					if(pclHorse->GetPremiumPartsNum() > 0)
					{
						// 프리미엄 파츠 아이템을 사용 중이면 부스터필 사용 불가한다.
						switch ( clitem.siUnique )
						{
						case ITEMUNIQUE(2740):
						case ITEMUNIQUE(2742):
							{
								*preturn	= CANUSEITEM_ERROR_CANNOTUSEPREMIUMITEM;
								return false	;
							}
							break;
						}

					}
				}
		}
		break;
	case ITEMTYPE_BOOK:
		{
			//[진성] 스킬북.
			if( pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SKILLBOOK ) )
			{
				// 보조 마법에만 적용.
				if( pclItemManager->pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( clitem.siUnique ) )
				{
    				SI32 skillunique = clitem.GetSkillUnique( pclItemManager );
					if( pclCharSkillBookInfo->IsFullSubMagic( skillunique ) ) 
					{
						*preturn = CANUSEITEM_ERROR_SKILL_BOOK_SUB_MAGIC_FULL;
						return false;
					}
				
					SI32 skilllevel  = pclCI->clCharSkill.GetTotalSkillLevel( skillunique, 0, 0 );
					SI32 skilllimit  = clitem.GetSkillLevelLimit(pclItemManager);
					if( skilllevel < skilllimit )
					{
						TCHAR szSkillname[128] = "";
						pclClient->pclSkillManager->GetSkillName( skillunique, szSkillname );

						NTCHARString256 szExplain = GetTxtFromMgr(30519);
						szExplain.Replace( "#skillname#", szSkillname );

						cltClient* pclclient = (cltClient*)pclClient;
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), szExplain );

						*preturn = CANUSEITEM_ERROR_SKILL_BOOK;
						return false;
					}
				}
				else
				{
					SI32 siSkillUnique = 0;
					switch( GetAttackType() )
					{
						case ATTACKTYPE_SWORD:		siSkillUnique = SKILL_USESWORD1;	break;
						case ATTACKTYPE_SPEAR:		siSkillUnique = SKILL_USESPEAR1;	break;
						case ATTACKTYPE_AXE:		siSkillUnique = SKILL_USEAXE1;		break;
						case ATTACKTYPE_STAFF:		siSkillUnique = SKILL_USESTAFF1;	break;
						case ATTACKTYPE_STAFF1:		siSkillUnique = SKILL_USESTAFF1;	break;
						case ATTACKTYPE_STAFF2:		siSkillUnique = SKILL_USESTAFF1;	break;
						case ATTACKTYPE_NEW_STAFF2:	siSkillUnique = SKILL_USESTAFF1;	break;
						case ATTACKTYPE_BOW:		siSkillUnique = SKILL_USEBOW1;		break;
						case ATTACKTYPE_BOW1:		siSkillUnique = SKILL_USEBOW1;		break;
						case ATTACKTYPE_NEW_BOW1:	siSkillUnique = SKILL_USEBOW1;		break;
						case ATTACKTYPE_GUN:		siSkillUnique = SKILL_USEGUN1;		break;
						case ATTACKTYPE_GUN1:		siSkillUnique = SKILL_USEGUN1;		break;
						case ATTACKTYPE_NEW_GUN1:	siSkillUnique = SKILL_USEGUN1;		break;
					}
					if(0 >= siSkillUnique ) return false;

					SI32 skilllevel  = pclCI->clCharSkill.GetTotalSkillLevel( siSkillUnique, 0, 0 );
					SI32 skilllimit  = clitem.GetSkillLevelLimit(pclItemManager);
					if( skilllevel < skilllimit )
					{
						TCHAR szSkillname[128] = "";
						pclClient->pclSkillManager->GetSkillName( siSkillUnique, szSkillname );

						NTCHARString256 szExplain = GetTxtFromMgr(30518);
						szExplain.Replace( "#skillname#", szSkillname );

						cltClient* pclclient = (cltClient*)pclClient;
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), szExplain );

						*preturn = CANUSEITEM_ERROR_SKILL_BOOK;
						return false;
					}
				}
			}
			else
			{
				SI32 skillunique = clitem.GetSkillUnique(pclItemManager);
				SI32 skilllevel  = pclCI->clCharSkill.GetSkillLevel(skillunique);

				//-----------------------------------
				// 기술 점수가 남아 있어야 사용가능. 
				// 제조활성화 추가 : 제조스킬이면 스킬보너스포인트가 0이라도 올릴수 있다. - by PCK : 2007.08.09
				//-----------------------------------
				//if( pclClient->IsWhereServiceArea(ConstSwitch_ManufactureRevitalize) )		// 제조활성화
				if( pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) )		// 제조활성화
				{
					if( pclCI->clIP.GetSkillBonus() <= 0 && pclClient->pclSkillManager->IsManufactureSkill(skillunique) == false )
					{
						*preturn	= CANUSEITEM_ERROR_NOSKILLPOINT;
						return false;
					}
				}
				else
				{
					if( pclCI->clIP.GetSkillBonus() <= 0 )
					{
						*preturn	= CANUSEITEM_ERROR_NOSKILLPOINT;
						return false;
					}
				}

				//-----------------------------------
				// 사용제한 확인. 
				//-----------------------------------
				SI32 retunval = 0;
				if( pclItemManager->CheckCondition(itemunique, this, &retunval) == false )
				{
					*preturn	= CANUSEITEM_ERROR_NOTFITCOND;
					return false;
				}

				//----------------------------------
				// 이미 개발된 기술이 최고 수준이어서는 안된다. 
				//----------------------------------
				// 스킬의 최대 수치를 구한다. 
				SI32 maxskilllevel	= pclClient->pclSkillManager->GetMaxLevel(skillunique);
				if(skilllevel >= maxskilllevel)
				{
					*preturn	= CANUSEITEM_ERROR_ALREADYMAXSKILL;
					return false;
				}

				//-----------------------------------
				// 부모 기술이 개발되어 있어야 한다. 
				//-----------------------------------
				if(pclClient->pclSkillManager->GetParentSkillRef(skillunique) )
				{
					if(pclCI->clCharSkill.GetParentSkillLevel(skillunique, NULL) == 0)
					{
						*preturn	= CANUSEITEM_ERROR_NEEDPARENTSKILL;
						return false;
					}
				}

				//-----------------------------------
				// 기술 상승에 제한이 있는 것이라면, 
				//-----------------------------------
				SI32 skilllimit = clitem.GetSkillLevelLimit(pclItemManager);
				if(skilllimit)
				{
					// 현재 해당 기술의 레벨이 제한에 걸리면 실패. 
					if(skilllevel >= skilllimit)
					{
						*preturn	= CANUSEITEM_ERROR_LIMITSKILLLEVEL;
						return false;
					}
				}
			}
		}
		break;
	case ITEMTYPE_CRYSTAL://아티팩트 결정체
		{
			return false;
		}break;
	case ITEMTYPE_COMPOSITIONMATERIAL://아티팩트 합성재료
		{
			return false;
		}break;
	case ITEMTYPE_EVENTITEM://이벤트 아이템
		{
			bool bCanUse = false;
			if(clitem.siUnique == ITEMUNIQUE(13025))	{		bCanUse = true;		}		// 요술램프		
			if(clitem.siUnique == ITEMUNIQUE(13042))	{		bCanUse = true;		}		// 폭죽		
			//KHY - 1113 - 크리스마스 이벤트 -
			if(clitem.siUnique == ITEMUNIQUE(13002))	// 크리스마스 양말	 - 이벤트기간만 사용가능 삭제.
			{			
				/*
				SYSTEMTIME	CurTime;
				if		( pclClient->GameMode == GAMEMODE_SERVER )	{	memcpy(&CurTime, &((cltServer*)pclClient)->sTime, sizeof(CurTime));		}
				else if	( pclClient->GameMode == GAMEMODE_CLIENT )	{	memcpy(&CurTime, &((cltClient*)pclClient)->sTime, sizeof(CurTime));		}
				
				if( pclClient->pclEventTimeManager->InEventTime("ChristmasEvent", &CurTime) )
				{
					bCanUse = true;
				}
				*/
				bCanUse = true;
			}

			if(clitem.siUnique == ITEMUNIQUE(13063))	{		bCanUse = true;		}		// 포춘쿠키
			if(clitem.siUnique == ITEMUNIQUE(13005))	{		bCanUse = true;		}		// 황금알		
			if(clitem.siUnique == ITEMUNIQUE(13028))	{		bCanUse = true;		}		// 황금라쿤알		
			if(clitem.siUnique == ITEMUNIQUE(13021))	{		bCanUse = true;		}		// 장미 상자	
			if(clitem.siUnique == ITEMUNIQUE(13015))	{		bCanUse = true;		}		// 장미 상자	
			if(clitem.siUnique == ITEMUNIQUE(13329))	{		bCanUse = true;		}		// 복 주머니	04.21 유니크변경	
			if(clitem.siUnique == ITEMUNIQUE(13043))	{		bCanUse = true;		}		// [진성] 서버 이벤트. NDE 뱃지 소모. => 2008-6-18
			if( false == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_OLYMPICMEDAL )	&&
				clitem.siUnique == ITEMUNIQUE(13044))	{		bCanUse = true;		}		// 금메달
			if(	false == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_OLYMPICMEDAL )	&&
				clitem.siUnique == ITEMUNIQUE(13045))	{		bCanUse = true;		}		// 금메달
			if(	false == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_OLYMPICMEDAL )	&&
				clitem.siUnique == ITEMUNIQUE(13046))	{		bCanUse = true;		}		// 금메달
			if(clitem.siUnique == ITEMUNIQUE(13047))	{		bCanUse = true;		}		//[진성] 추석 이벤트. 추석월병 사용. => 2008-8-8 
			if(clitem.siUnique == ITEMUNIQUE(13048))	{		bCanUse = true;		}		//[진성] 추석 이벤트. 추석월병 사용. => 2008-8-8 
			if(clitem.siUnique == ITEMUNIQUE(13057))	{		bCanUse = true;		}		//[성웅] 보물찾기
			if(clitem.siUnique == ITEMUNIQUE(13059))	{		bCanUse = true;		}		//[춘기] 크리스마스 이벤트 - 눈결정
			if(clitem.siUnique == ITEMUNIQUE(13061))	{		bCanUse = true;		}		//[춘기] 크리스마스 이벤트 - 크리스마스 장식
			if(clitem.siUnique == ITEMUNIQUE(13064))	{		bCanUse = true;		}		//[춘기] 크리스마스 이벤트 - 크리스마스 장식

			if(clitem.siUnique == ITEMUNIQUE(13058))	
			{

				if( pclCI->clQuestInfo.IsAllClear( pclClient->pclQuestManager, QUEST_TYPE_HUNTINGGROUND03)==true	)
				{
					bCanUse = true;
				}		
				else
				{
					*preturn	= CANUSEITEM_ERROR_NOT_ENOUGH_GET_TREASUR;
					// 안되 받을수 없다.
				}
			}		//[성웅] 보물찾기			
			if(clitem.siUnique == ITEMUNIQUE(13050))
			{
				if ( pclClient->IsCountrySwitch(Switch_HalloweenEvent) )
				{
					SYSTEMTIME	CurTime;
					if		( pclClient->GameMode == GAMEMODE_SERVER )	{	memcpy(&CurTime, &((cltServer*)pclClient)->sTime, sizeof(CurTime));		}
					else if	( pclClient->GameMode == GAMEMODE_CLIENT )	{	memcpy(&CurTime, &((cltClient*)pclClient)->sTime, sizeof(CurTime));		}
					
					if( pclClient->pclEventTimeManager->InEventTime("HalloweenEvent", &CurTime) )
					{
						bCanUse = true;
					}
				}
			}
			//[진성] 에그월병 중복 사용 불가.
			if(itemunique == ITEMUNIQUE(13048))
			{
				SI16 index	 = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_EGGMOONCAKE, false );

				if ( index < 0 )
				{
					bCanUse = false;
				}
			}
			//보물찾기 이벤트 엄한마을에서 사용 불가
			if(clitem.siUnique == ITEMUNIQUE(13057))
			{
				if ( (GetMapIndex() == MAPINDEX_BEGINNER1) 
					|| (GetMapIndex() == MAPINDEX_PALACE) 
					|| (GetMapIndex() == MAPINDEX_MOFUMOFULAND)
					|| (GetMapIndex() == Const_MapIndex_PollMap)
					|| (GetMapIndex() == MAPINDEX_PRIVATEMARKETAREA)
					|| (GetMapIndex() == MAPINDEX_WEDDINGHALL)
					)
				{
					*preturn	= CANUSEITEM_ERROR_NOUSE_THISPLACE;

					bCanUse = false;
				}
			}
			
			// [춘기] 크리스마스 이벤트 - 눈결정 (중복사용불가)
			if(clitem.siUnique == ITEMUNIQUE(13059))
			{
				SI16 index	 = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_CHRISTMASEVENT_SNOWBLESS, false );

				if ( index < 0 )
				{
					bCanUse = false;
				}
			}
			
			// [춘기] 크리스마스 이벤트 - 크리스마스 장식 (중복사용불가)
			if(clitem.siUnique == ITEMUNIQUE(13061))
			{
				SI16 index	 = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_CHRISTMASEVENT_DECORATION, false );

				if ( index < 0 )
				{
					bCanUse = false;
				}
			}

			return bCanUse;
		}break;
	case ITEMTYPE_BOX://박스 아이템
		{
			if ( GAMEMODE_CLIENT == pclClient->GameMode )
			{
				CDormancySystem *pclDormancySystem = pclClient->pclDormancySystem;
				if( NULL != pclDormancySystem)
				{
					CDormancyEquipItemRewardClient *pclDormancyClient = (CDormancyEquipItemRewardClient *)pclDormancySystem->GetDormancyEquipItemReward();
					if( NULL != pclDormancyClient)
					{
						// 아이템 선택
						pclDormancyClient->UseBox(clitem.siUnique , siPos);
					}
				}
			}

			return true;
		}break;
	case ITEMTYPE_PREMIUM://프리미엄아이템.
		{
			//여기에서 프리미엄 아이템을 사용 할수 있는지 체크 한다.
			//아이템을 사용할수 없는경우
			//1. 같은 파츠를 사용중이다.
			// 프리미엄 파츠중 이미 같은 파츠를 사용중이다.
			// 위의 조건에 걸리지 않으면 사용할수 있다.

			// [영훈] 수호정령_090525 : 수호정령 아이템으로 소환할수있는지 검사
			if ( ITEMUNIQUE(13646) == clitem.siUnique || ITEMUNIQUE(13651) == clitem.siUnique || ITEMUNIQUE(13655) == clitem.siUnique || ITEMUNIQUE(13654) == clitem.siUnique|| ITEMUNIQUE(13659) == clitem.siUnique || ITEMUNIQUE(13658) == clitem.siUnique )
			{
				SI16 siTempKind = 0;
				SI16 siTempLife = 0;
				SI16 siTempShip	= 0;

				return CanUseSoulGuardItem( clitem.siUnique, &siTempKind, &siTempLife, &siTempShip, preturn );
			}

			if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false)	return false ;
			cltHorse * pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse()	;//현제 타고 있는 말을 가지고 온다
			if (pclHorse !=NULL )
			{
				// 
				SI32 siPremiumUnique_SLot1 = pclHorse->GetPremiumUnique_Slot1()	;
				SI32 siPremiumUnique_SLot2 = pclHorse->GetPremiumUnique_Slot2()	;
				SI32 siPremiumUnique_SLot3 = pclHorse->GetPremiumUnique_Slot3()	;
				if( clitem.siUnique == siPremiumUnique_SLot1 
					|| clitem.siUnique == siPremiumUnique_SLot2
					|| clitem.siUnique == siPremiumUnique_SLot3 )
				{
					// 이미 사용한 아이템입니다.
					*preturn	= CANUSEITEM_ERROR_BEFOREUSE_SAMEITEM;
					return false;
				}
				// 부스터필 사용 중이면 사용 불가
				if ( pclHorse->siStatusTicketNum > 0 )
				{
					*preturn	= CANUSEITEM_ERROR_CANNOTUSEPREMIUMITEM;
					return false	;
				}
				if( pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE )
				{
					switch ( clitem.siUnique  )
					{
					case ITEMUNIQUE(13638):
					case ITEMUNIQUE(13639):
					case ITEMUNIQUE(13640):
						{
							// 사용할수 없는 타임의 아이템입니다
							*preturn	= CANUSEITEM_ERROR_CANNOTUSETYPEGORSE_SAMEITEM;
							return false	;
						}
						break;
					}
				}
				else
				{
					switch ( clitem.siUnique  )
					{
					case ITEMUNIQUE(13635 ):
					case ITEMUNIQUE(13636 ):
					case ITEMUNIQUE(13637 ):
						{
							// 사용할수 없는 타임의 아이템입니다
							*preturn	= CANUSEITEM_ERROR_CANNOTUSETYPEGORSE_SAMEITEM;
							return false	;
						}
					}

				}
			}
			
			return true;
		}break;

	case ITEMTYPE_QUEST:
		{
			//switch ( clitem.siUnique )
			//{
			//case ITEMUNIQUE(8121):
			//	{
			//		SI16 siMonsterKind = (SI16)pclClient->GetUniqueFromHash( TEXT("KIND_QUESTEMPERORMASTER") );
			//		if ( 0 >= siMonsterKind )
			//		{
			//			*preturn = CANUSEITEM_ERROR_INVALID;
			//			return false;
			//		}

			//		if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMON, siMonsterKind) )
			//		{
			//			*preturn = CANUSEITEM_ERROR_NOTFITCOND;
			//			return false;
			//		}

			//		return true;
			//	}
			//	break;
			//}
		}
		break;
	}

	
	return true;
}

bool cltCharCommon::CanRepairItem( cltItem* pclitem )
{
	if( pclitem == NULL	)										return false;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclitem->siUnique );
	if( ref <= 0 )												return false;

	cltItemInfo* pclItemInfo = pclClient->pclItemManager->pclItemInfo[ref];
	SI32 siSkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( pclItemInfo->clSkillInfo.siSkill, 0, 0, &pclCI->clCharItem.clItem[0], siID );

	// 스킬레벨이 부족해서 수리할 수 없다.
	if( pclItemInfo->clSkillInfo.siSkillLevel > siSkillLevel )
	{
		return false;
	}

	return true;
}

//---------------------------
// 장비 
//---------------------------
bool cltCharCommon::CheckEquipCondition(cltItemManagerCommon* pclItemManager, SI32 pos, cltItem* pclitem, SI32* preturnval)
{
	SI32 siParentID	= GetSummonParentID();
	

	// [영훈] 소환수일때는 무조건 True
	if ( pclCM->IsValidID(siParentID) )
	{
		return true;
	}

	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		
		// [강형] 내구도 체크
		if ( (PERSONITEM_HELMET <= pos) 
			&& (pos < PERSONITEM_INV0)
			&& (pclitem->IsBulletItem() == false) // 발사체 아이템이 아닐경우
			&& (pclitem->GetDurability() <= 0)
		)
		{
			return false;
		}
	}

	// 무기 사용술이 연마되어 있는지 확인한다.
	if(pos == PERSONITEM_WEAPON1 || pos == PERSONITEM_WEAPON2)
	{	
		SI32 type			= pclitem->GetType(pclItemManager);
		SI32 returnskillval	= 0;


		if(pclCI->clCharSkill.ChcekUseWeaponSkill(type, pclitem, &returnskillval) == false)return false;

		//cyj 탄환류 아이템일때 장착창에 다른아이템이 있으면 장착 불가
		if(pclitem->IsBulletItem() && pclCI->clCharItem.clItem[pos].siUnique != 0 && pclCI->clCharItem.clItem[pos].siUnique != pclitem->siUnique)
			return false;
	}
	
	if ( pos == PERSONITEM_HELMET )
	{
		if ( pclitem->GetType(pclItemManager) == ITEMTYPE_HAT ) return false ;
	}

	if ( pos == PERSONITEM_ARMOUR )
	{
		if ( pclitem->GetType(pclItemManager) == ITEMTYPE_DRESS ) return false ;
	}

	if ( (0 <= pos) && (PERSONITEM_INV0 > pos) ) //( pos < PERSONITEM_INV0 || pos >= MAX_ITEM_PER_PERSON )
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
		if(ref <= 0)return false;
		if(pclItemManager->pclItemInfo[ref] == NULL)return false;

		
		// 사용자 비교. 
		if(pos < PERSONITEM_INV0)
		{
			if(pclItemManager->CheckCondition(pclitem->siUnique, this, preturnval) == false)return false;

			// 기자여야 하는 경우, 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 1)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && GetGameMasterLevel() != 1)
				{
					return false;
				}
			}
			// 왕 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 2)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && pclCI->clBI.uiGRank != 1)
				{
					return false;
				}
				
			}
			// 6조 판서 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 3)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) 
					&& pclCI->clBI.uiGRank != GRANK_MINISTER1
					&& pclCI->clBI.uiGRank != GRANK_MINISTER2
					&& pclCI->clBI.uiGRank != GRANK_MINISTER3
					&& pclCI->clBI.uiGRank != GRANK_MINISTER4
					&& pclCI->clBI.uiGRank != GRANK_MINISTER5
					&& pclCI->clBI.uiGRank != GRANK_MINISTER6)
				{
					return false;
				}
			}
			// 방송인이어야 하는 경우, 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 4)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && GetGameMasterLevel() != 2)
				{
					return false;
				}
			}
			// 수호천사여야 하는 경우, 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 5)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && pclCI->clBI.uiAngelSwitch == 0)
				{
					return false;
				}
			}
			// 방송인도우미여야 하는 경우
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 6)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && GetGameMasterLevel() != 3)
				{
					return false;
				}
			}
			// 포교
			if(pclItemManager->pclItemInfo[ref]->siNeedRank == 7)
			{
				if(GetGameMasterLevel() != (BASIC_GAMEMASTER_LEVEL+1) && pclCI->clBI.uiPoliceSwitch == 0)
				{
					return false;
				}
			}
		}
		/*
		// 소환일때 비교. 
		else if ( true == bSummon )
		{
			SI32 siSummonIndex = GetSummonIndex();
			// 신분상의 제한이 있는 장비는 장착할 수 없다. 
			if(pclItemManager->pclItemInfo[ref]->siNeedRank)return false;

			cltSummon* pclsummon = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSummon( siSummonIndex );
			if ( NULL == pclsummon )
			{
				return false;
			}

			SI16 siAttackWearStoneNum	= pclsummon->siAttackWearStoneNum;
			SI16 siDefenseWearStoneNum	= pclsummon->siDefenseWearStoneNum;

			SI32 siSummonKind = pclsummon->siKind;
			if ( false == pclClient->pclKindInfoSet->IsValidKind( siSummonKind ) )
			{
				return false;
			}

			cltKindInfo* pclki = NULL;
			if ( pclClient->IsCountrySwitch(Switch_Summon_Separate) ) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[siSummonKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[siSummonKind];
			}

			if ( NULL == pclki )
			{
				return false;
			}
			
			// 장비 장착 타입이 아니라면 
			if ( SUMMON_EQUIPTYPE_NONE == pclki->siSummonEquip )
			{
				return false;
			}

			
			cltParametaBox clPB;
			cltPIPInfo	clipinfo2;
			clipinfo2.Set(&pclsummon->clIP);
			clPB.Init(pclClient->pclItemManager, &clipinfo2, NULL, pclki);

			bool bmosterhero = false;

			cltItem* pclitemlist = pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex );
			if ( NULL == pclitemlist )
			{
				return false;
			}

			clPB.Action(this, 0, PERSONITEM_WEAPON1, pclitemlist, NULL, NULL, NULL, NULL, siAttackWearStoneNum, siDefenseWearStoneNum, GAMEMODE_CLIENT, true, bmosterhero);
			
		}
		*/
	}

	return true;
}

void cltCharCommon::SetHitSwitch(bool mode)
{
	bHitSwitch  = mode;

	if(mode == true)
	{
		// 피격 동작이 있은 캐릭터야 한다. 
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 aniref			= GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(ANITYPE_HIT);
		if(aniref < 0)return ;

		
		// 애니메이션 정보 초기화. 
		clAniInfo.Init1();

		clAniInfo.dwAniStartClock	= pclClient->CurrentClock;
		clAniInfo.dwElapsedClock	= 0;
	}

}

//----------------------------------------
// 죽는 행위 
//----------------------------------------
bool cltCharCommon::Action_Dying()
{
	//--------------------------------
	// 다른 명령은 받아 들이지 않는다. 
	//--------------------------------
	bBusySwitch = true;

	//-----------------------------
	// 사망시 한번만 이루어져야 할 행위 
	//-----------------------------
	if(bDyingSwitch == false)
	{
		bDyingSwitch = true;

		// by LEEKH 2007.12.24 - TRANSFORM
		if(GetKindInfo()->IsAtb(ATB_SELFBOMB))
		{
			
			cltPos cltilestartpos(GetX(), GetY());
			cltPos cldotstartpos(siCenterX, siCenterY);
			
			cltAttackTarget cltarget;
			cltarget.Set(&clAttackTarget);
			cltarget.siHitRate	= 100;
			
			cltarget.clPos.SetMapIndex(GetMapIndex());
			cltarget.clPos.SetX(GetX());		// 타격의 목표치가 자신의 위치여야 한다. 
			cltarget.clPos.SetY(GetY());

			SI32 sibombeffect = BULLETKIND_SELFBOMB ;
			//if ( GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BOMBWHALE")) )
			//	sibombeffect = BULLETKIND_SELFBOMBWHALE ;

			SI32 bulletid = pclClient->pclBulletManager->SetBullet(pclMap, sibombeffect, 0, 
				siID, GetApower() * 2,
				&cltilestartpos,
				&cldotstartpos, 
				&cltarget,
				&cldotstartpos);
		}
		
	}

    return FALSE;
}

SI32 cltCharCommon::GetSummonID()
{
	// 나의 소환수 ID
	SI32 siSummonID = pclCM->GetIDFromCharUnique(siChildCharUnique);	

	if(pclCM->IsValidID(siSummonID)  == TRUE)
	{
		if(pclCM->CR[siSummonID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			if( (GetCharUnique()      == pclCM->CR[siSummonID]->clIdentity.clSummonInfo.siParentCharUnique) &&
				(pclCI->GetPersonID() == pclCM->CR[siSummonID]->clIdentity.clSummonInfo.siParentPersonID) )
			{
				return siSummonID;
			}
		}
	}

	return 0;
}


SI32 cltCharCommon::GetSummonParentID()
{

	if(clIdentity.siIdentity ==IDENTITY_PERSON_SUMMON )
	{
		SI32 siParentID = pclCM->GetIDFromCharUnique(clIdentity.clSummonInfo.siParentCharUnique);	
		
		if(pclCM->IsValidID(siParentID) == TRUE && IsPC(siParentID)==TRUE)
		{
			if( GetCharUnique()            == pclCM->CR[siParentID]->siChildCharUnique &&
				clIdentity.clSummonInfo.siParentPersonID == pclCM->CR[siParentID]->pclCI->GetPersonID() ) 
			{
				return siParentID;
			}
		}
	}

	return 0;
}


SI32 cltCharCommon::GetSummonIndex()
{
	if(clIdentity.siIdentity ==IDENTITY_PERSON_SUMMON )
	{
		return clIdentity.clSummonInfo.siMySummonIndex;
	}
	return 0;
	
}

SI32 cltCharCommon::GetSoulGuardCharID()
{
	SI32 siSoulGuardCharID = pclCM->GetIDFromCharUnique( siMySoulGuardUnique );
	if ( false == pclCM->IsValidID(siSoulGuardCharID) )
	{
		return 0;
	}

	cltCharCommon* pclSoulGuardChar = pclCM->CR[siSoulGuardCharID];
	if ( NULL == pclSoulGuardChar )
	{
		return 0;
	}

	if ( IDENTITY_SOULGUARD != pclSoulGuardChar->clIdentity.siIdentity )
	{
		return 0;
	}

	if ( GetCharUnique() != pclSoulGuardChar->clIdentity.clSoulGuard.m_siParentCharUnique )
	{
		return 0;
	}

	if ( pclCI->GetPersonID() == pclSoulGuardChar->clIdentity.clSoulGuard.m_siParentPersonID )
	{
		return siSoulGuardCharID;
	}

	return 0;
}

// [영훈] 수호정령_090525 : 수호정령의 부모 CharID를 갖고 온다
SI32 cltCharCommon::GetSoulGuardParentCharID( void )
{
	if ( IDENTITY_SOULGUARD != clIdentity.siIdentity )
	{
		return 0;
	}

	SI32 siParentCharID = pclCM->GetIDFromCharUnique( clIdentity.clSoulGuard.m_siParentCharUnique );
	if ( (false == pclCM->IsValidID(siParentCharID)) || (false == IsPC(siParentCharID)) )
	{
		return 0;
	}

	cltCharCommon* pclParent = pclCM->CR[siParentCharID];
	if ( NULL == pclParent )
	{
		return 0;
	}
	
	// 부모에 설정되어있는 캐릭터 유니크와 비교한다
	if ( GetCharUnique() != pclParent->siMySoulGuardUnique )
	{
		return 0;
	}

	// 내 부모 정보와 가져온 부모 퍼슨아이디가 맞는지 비교
	if ( pclParent->pclCI->GetPersonID() == clIdentity.clSoulGuard.m_siParentPersonID )
	{
		return siParentCharID;
	}
	
	return 0;

}

//KHY - 1109 - 가챠레어- 강아지방석추가
SI32 cltCharCommon::IsHaveCushionItem()
{
	SI16 cushionType[MAX_CUSHION_NUM] = {0,}; // 각방석의 종류. - 0:고양이 방석. 1:강아지 방석.  2:이불. 3:잠자는 냐옹이

	SI32	 returnItemUnique = 0; // 선정된 아이템 유니크.
	
	switch(GetKind())
	{
		case KIND_HERO3: // 일본남.
			{
				 cushionType[0] = ITEMUNIQUE(13610);
				 cushionType[1] = ITEMUNIQUE(13617);
				 cushionType[2] = ITEMUNIQUE(13629);
				 cushionType[3] = ITEMUNIQUE(13649);
			}
			break;
		case KIND_HEROINE3: // 일본여.
			{
				 cushionType[0] = ITEMUNIQUE(13611);
				 cushionType[1] = ITEMUNIQUE(13619);
				 cushionType[2] = ITEMUNIQUE(13628);
				 cushionType[3] = ITEMUNIQUE(13650);
			}
			break;
		case KIND_HERO4: // 서양남
			{
				 cushionType[0] = ITEMUNIQUE(13608);
				 cushionType[1] = ITEMUNIQUE(13618);
				 cushionType[2] = ITEMUNIQUE(13629);
				 cushionType[3] = ITEMUNIQUE(13647);
			}
			break;
		case KIND_HEROINE4: // 서양여.
			{
				 cushionType[0] = ITEMUNIQUE(13609);
				 cushionType[1] = ITEMUNIQUE(13620);
				 cushionType[2] = ITEMUNIQUE(13628);
				 cushionType[3] = ITEMUNIQUE(13648);
			}
			break;
	}

	// 위치를 찾아 가장 작은 값을 리턴한다.(0이 아닌)
	// 숫자가 작아야 앞선것이다.
	SI16 temCushionPose1 = 0;
	SI16 temCushionPoseOld = 10000; // 불가능한 위치.

	for(SI16 x = 0; x < MAX_CUSHION_NUM ;x++)
	{
		if(cushionType[x] > 0) // 등록된 방석 종류만.
		{
			temCushionPose1 = pclCI->clCharItem.FindItemInv(cushionType[x]);

			if( temCushionPose1 > 0) // 가지고 있다면.
			{
				if(temCushionPose1 < temCushionPoseOld) // 가장 작은 값을 찾는다.
				{
					temCushionPoseOld = temCushionPose1; 
					returnItemUnique =  cushionType[x];
				}
			}
		}		
	}		

	if(returnItemUnique >0)
		return returnItemUnique;
	else
		return 0;
}

//KHY - 1220 - 변신시스템.
bool cltCharCommon::IsCanTransFormRecover()
{		
	if(clTransFormInfo.bTransFormMode == true)
	{
		if(clPB.siTransFormSyc >= 100) // 싱크로 100% 보너스.
		{
			switch(clPB.siAttackType)
			{ 
				case ATTACKTYPE_STAFF:
				case ATTACKTYPE_STAFF1:
				case ATTACKTYPE_STAFF2:
				case ATTACKTYPE_NEW_STAFF2:
					return true;
							break;
			}
		}
	}

	return false;
}

bool cltCharCommon::CanTransFormAttackType(SI32 siCharKind)
{
	if( siCharKind < 0 || siCharKind >= MAX_KIND_NUMBER )			return false;

	SI32	siAttackType = pclClient->pclKindInfoSet->pclKI[siCharKind]->clDefaultWeaponInfo.GetAttackType();
	SI32	siCharAttackType = GetAttackType();

	bool	bCanTranform = false;

	//KHY - 0124 - 가챠레어- 닌자 변신 아이템.
	// 아마도 - 새로운 변신 캐릭터가 추가될때, 공격 속성을 지정해 주어야 할것이다.

	switch(siAttackType)
	{
	case ATTACKTYPE_SWORD:		// 온달 , 일지매( 여 ) , 고양이 근거리 
		{
			switch(siCharAttackType)
			{
			case ATTACKTYPE_SWORD:
			case ATTACKTYPE_SPEAR:
			case ATTACKTYPE_AXE:
				{
					bCanTranform = true;
				}
				break;
			}
		}
		break;
	case ATTACKTYPE_CHRISTMASRANGE:
	case ATTACKTYPE_FIGHTINGMENRANGE:	// 거너스피릿
	case ATTACKTYPE_HALLOWEENGHOST:
	case ATTACKTYPE_MOONBLADE:		// 평강공주
	case ATTACKTYPE_NINJAMAN:		// 일지매( 남 )
	case ATTACKTYPE_CATRANGE:		// 고양이( 원거리 )
	case ATTACKTYPE_FAIRYRANGE:		// 요정스피릿(여)
	case ATTACKTYPE_SNOWQUEEN:		// 가챠 - 12월 스피릿 상자	눈의 여왕 사스콰치
		{
			switch(siCharAttackType)
			{
			case ATTACKTYPE_STAFF:
			case ATTACKTYPE_BOW:
			//case ATTACKTYPE_BOW1:
			//case ATTACKTYPE_NEW_BOW1:
			case ATTACKTYPE_GUN:
			//case ATTACKTYPE_GUN1:
			case ATTACKTYPE_NEW_GUN1:
			case ATTACKTYPE_STAFF1:
			//case ATTACKTYPE_STAFF2:
			//case ATTACKTYPE_NEW_STAFF2:
				{
					bCanTranform = true;
				}
				break;
			}
		}
		break;
	}

	return bCanTranform;
}


SI32 cltCharCommon::GetItemUniqueFromCharKind(SI32 siCharKind)
{
	if( siCharKind == pclClient->GetUniqueFromHash("KIND_ONDAL") )
	{
		return ITEMUNIQUE(13612);
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_PYEONGGANG") )
	{
		return ITEMUNIQUE(13613);
	}
	//KHY - 0124 - 가챠레어- 닌자 변신 아이템.
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_NINJAMAN") ) // 닌자 남  - 원
	{
		return ITEMUNIQUE(13615);
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_NINJAGIRL") ) //  닌자  여  - 근거리
	{
		return ITEMUNIQUE(13616 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_CATRANGE") ) // 고양이 변신  - 원거리.
	{
		return ITEMUNIQUE(13623);
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_CATMELEE") ) // 고양이 변신  - 근거리.
	{
		return ITEMUNIQUE(13624 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN") ) // 할로윈 변신  - 근거리.
	{
		return ITEMUNIQUE( 13626 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST") )  // 할로윈 변신  - 원거리
	{
		return ITEMUNIQUE( 13627 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE") )  // 크리스마스 근거리변신
	{
		return ITEMUNIQUE( 13633 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE") )  // 크리스마스 원거리변신 - 진저브래드맨
	{
		return ITEMUNIQUE( 13632 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE") )	// 검사스피릿(여) - 근거리
	{
		return ITEMUNIQUE( 13641 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE") )	// 거너스피릿(남) - 원거리
	{
		return ITEMUNIQUE( 13642 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_FAIRYMELEE") )	//  요정스피릿(남) - 근거리 (임시:검사스피릿(여) - 근거리)
	{
		return ITEMUNIQUE( 13652 );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_FAIRYRANGE") )	// 요정스피릿(여) - 근거리 (임시:거너스피릿(남) - 원거리)
	{
		return ITEMUNIQUE( 13653 );
	}
	// 가챠 - 12월 스피릿 상자	눈의 여왕 사스콰치
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_ICERANGE") )		//  눈의 여왕	-	( 원거리)
	{
		return ITEMUNIQUE( 13657  );
	}
	else if( siCharKind == pclClient->GetUniqueFromHash("KIND_ICEMELEE") )	// 서스콰치	-	(근거리)
	{
		return ITEMUNIQUE( 13656  );
	}
	return 0;
}

SI32 cltCharCommon::GetCharKindFromItemUnique(SI32 siItemUnique)
{
	if( siItemUnique == ITEMUNIQUE(13612) )
	{
		return pclClient->GetUniqueFromHash("KIND_ONDAL");
	}
	else if( siItemUnique == ITEMUNIQUE(13613) )
	{
		return pclClient->GetUniqueFromHash("KIND_PYEONGGANG");
	}
	//KHY - 0124 - 가챠레어- 닌자 변신 아이템.
	else if( siItemUnique == ITEMUNIQUE(13615) )
	{
		return pclClient->GetUniqueFromHash("KIND_NINJAMAN");
	}
	else if( siItemUnique == ITEMUNIQUE(13616) )
	{
		return pclClient->GetUniqueFromHash("KIND_NINJAGIRL");
	}
	else if( siItemUnique == ITEMUNIQUE(13623) ) // 고양이 변신  - 원거리.
	{
		return pclClient->GetUniqueFromHash("KIND_CATRANGE");
	}
	else if( siItemUnique == ITEMUNIQUE(13624) ) // 고양이 변신  - 근거리.
	{
		return pclClient->GetUniqueFromHash("KIND_CATMELEE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13626 ) )  // [진성] 호박상자. 할로윈 변신  - 근거리.
	{
		return pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN");
	}
	else if( siItemUnique == ITEMUNIQUE( 13627 ) )  // [진성] 호박상자. 할로윈 변신  - 원거리
	{
		return pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST");
	}
	else if( siItemUnique == ITEMUNIQUE( 13633 ) )  // 크리스마스 근거리변신
	{
		return pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13632 ) )  // 크리스마스 원거리변신 - 진저브래드맨
	{
		return pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13641 ) ) // 검사스피릿(여) - 근거리
	{
		return pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13642 ) )  // 거너스피릿(남) - 원거리
	{
		return pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE");
	}

	// 요정 스피릿 추가 - 그래픽 미적용 검사/거너 스피릿으로 대체.
	else if( siItemUnique == ITEMUNIQUE( 13652 ) ) // 요정 스피릿(남) - 근거리 (임시:검사스피릿(여) - 근거리)
	{
		return pclClient->GetUniqueFromHash("KIND_FAIRYMELEE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13653 ) )  // 요정 스피릿(여) - 원거리 (임시:거너스피릿(남) - 원거리)
	{
		return pclClient->GetUniqueFromHash("KIND_FAIRYRANGE");
	}
	// 가챠 - 12월 스피릿 상자	눈의 여왕 사스콰치
	else if( siItemUnique == ITEMUNIQUE( 13657  ) )	// 눈의 여왕	-	원거리
	{
		return pclClient->GetUniqueFromHash("KIND_ICERANGE");
	}
	else if( siItemUnique == ITEMUNIQUE( 13656  ) )  // 사스콰치	-	근거리
	{
		return pclClient->GetUniqueFromHash("KIND_ICEMELEE");
	}
	return 0;
}

// 농경을 통해서 얻을 수 있는 작물의 확률. 
SI32 cltCharCommon::GetFarmRate(SI32 farmskilllevel )
{
	//cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, itemunique);
	//if(pclprice == NULL)return 0;

	//
	//SI32 delay = min(10000, max(1000, pclprice->siPrice)) * (100 - farmskilllevel) / 100;
	//delay = max(100, delay);		// 최소 10초는 유지. 
	//delay *= 60;

	//return delay;
	
	SI32 rate = 10;
	rate += farmskilllevel;

	return rate;

}

// 채광을 통해서 얻을 수 있는 광물의 확률. 
SI32 cltCharCommon::GetMineRate(SI32 mineskilllevel)
{
	SI32 rate = 10;
	rate += mineskilllevel;

	return rate;
}

void cltCharCommon::ParametaBoxAction()
{
	bool		bmonsterhero			= false; // 몬스터에서 소환영웅으로 진화한것인지 여부, 
	cltItem*	pclitemlist				= NULL;
	SI16		siAttackWearStoneNum	= 0;
	SI16		siDefenseWearStonenum	= 0;
	SI32		parentid				= GetSummonParentID();
	
	// 소환수 일때
	if ( pclCM->IsValidID(parentid) )
	{
		cltSummon *pclSummon = pclCM->CR[parentid]->pclCI->clSummonInfo.GetSummon( GetSummonIndex() );
		if(pclSummon)
		{
			// 소환수의 장비 목록을 갖고 온다
			pclitemlist = pclCM->CR[parentid]->pclCI->clSummonInfo.GetSummonEquipItemList( GetSummonIndex() );

			// 장비 착용석 갯수를 갖고 온다
			siAttackWearStoneNum	= pclSummon->siAttackWearStoneNum;
			siDefenseWearStonenum	= pclSummon->siDefenseWearStoneNum;
		}

	}
	// 사람일때
	else if( IsPC(GetCharUnique()) )
	{
		pclitemlist = pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
	}

	//------------------------------------
	// 적절한 장비셋의 포인터를 구한다. 
	//------------------------------------
	bool bNpc = false ;
	if ( IsInstanceNPC(GetCharUnique()) || IsNPC(GetCharUnique()) )
		bNpc = true ;

	clPB.Action(this, 
				pclCI->GetPersonID(), 
				ActiveWeapon, 
				pclitemlist, 
				&pclCI->clHorseInfo, 
				&pclCI->clHealthInfo,
				&pclCI->clCharSkill,
				&clIdentity, 
				siAttackWearStoneNum,
				siDefenseWearStonenum,
				pclClient->GameMode, 
				bNpc, 
				bmonsterhero);


	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		//------------------------------------------------
		// Mana가 최대값을 초과하는 경우 최대값으로 재조정. 
		//-------------------------------------------------
		if(GetMana() > clPB.GetMaxMana())
		{
			//SetMana(clPB.GetMaxMana());
		}

/*		if(GetLife() > clPB.GetMaxLife())
		{
			SetLife(clPB.GetMaxLife());
		}		
*/
	}

}

// 최고 장인 등록 여부를 갱신한다. 
void cltCharCommon::ChangeTopSkillUnique(SI32 skillunique)
{
	if(skillunique == clInnerStatus.siTopSkillUnique)return ;

	siReservedTopSkillUnique = skillunique;

}

SI32 cltCharCommon::GetCharUnique() const
{
	return CharUnique;
}

void cltCharCommon::SetCharUnique(SI32 unique)
{
	CharUnique = unique;
}

void cltCharCommon::SetCurrentOrder(SI32 order)
{
	clCurOrder.siOrder = order;
}

SI32 cltCharCommon::GetCurrentOrder()const
{
	return clCurOrder.siOrder;
}

void cltCharCommon::SetID(SI32 id)
{
	siID	= id;
}

SI32 cltCharCommon::GetID() const
{
	return siID;
}

SI32 cltCharCommon::GetCenterX() const
{
	return siCenterX;
}

SI32 cltCharCommon::GetCenterY() const
{
	return siCenterY;
}

SI32 cltCharCommon::GetAttackRange() const
{
	return clPB.GetAttackRange();
}

SI32 cltCharCommon::GetAttackType()
{
	return clPB.GetAttackType();
}

SI32 cltCharCommon::GetMaxWeight()
{
	return clPB.GetMaxWeight();
}

BOOL cltCharCommon::IsSameMap(const cltMapCommon* pclmap)
{
	if(pclMap == pclmap)return TRUE;
	return FALSE;
}

// SBS사용자인가. 
bool cltCharCommon::IsSBS()
{
	if(pclCI->clBI.szAccountID[0] =='s'
		&& pclCI->clBI.szAccountID[1] =='_')
	{
		return true;
	}

	return false;

}

BOOL cltCharCommon::IsAtb(SI32 atb)
{			
	if( Atb & atb )		return TRUE;
	return FALSE;
}

// 모든 조건이 충족되어야 
BOOL cltCharCommon::IsAtbAnd(SI32 atb)
{			
	if((Atb&atb)==atb)return TRUE;
	return FALSE;
}

BOOL cltCharCommon::IsDefenceAtb(SI32 atb)
{	
	if(DefenceAtb==atb)return TRUE;	
	return FALSE; 
};

SI32 cltCharCommon::GetApower()
{
	return clPB.CalcApower();
}

int	cltCharCommon::GetMovePercent()
{
	return clMoveInfo.siMovePercent;
}

void cltCharCommon::MoveInit()
{
	clMovePointList.Init();

	clMoveInfo.siMovePercent	= 0;
}

SI32 cltCharCommon::GetGameMasterLevel()
{
	return siGameMasterLevel;
}

void cltCharCommon::SetGameMasterLevel(SI32 level)
{
	siGameMasterLevel	=	level;
}

SI32 cltCharCommon::GetRareItemRate(SI32 where)
{
	if ( where < 0 || where >= 4 ) return 0 ;
	return siRareItemRate[where];
}

void cltCharCommon::SetRareItemRate(SI32 attack,SI32 mag,SI32 skill,SI32 dur)
{
	siRareItemRate[0] = attack;
	siRareItemRate[1] = mag;
	siRareItemRate[2] = skill;
	siRareItemRate[3] = dur;
}

bool cltCharCommon::GetWennyOldManSuccess()
{
	return bWennyOldMan;
}

SI32 cltCharCommon::GetWennyOldManMode()
{
	return siWennyOldMan;
}

void cltCharCommon::SetWennyOldMan(bool success,SI32 mode)
{
	bWennyOldMan = success ;
	siWennyOldMan = mode ;
}

void cltCharCommon::SetCurrentMagic(SI32 magic, SI08 siCastType)
{
	siCurrentMagic			= magic;
	siCurrentMagicCastType	= siCastType;
}

SI32 cltCharCommon::GetCurrentMagic()
{
	return siCurrentMagic;
}

SI08 cltCharCommon::GetCurrentMagicCastType()
{
	return siCurrentMagicCastType;
}

void cltCharCommon::SetParametaBoxAction(bool mode)
{
	clCommonSimpleVary.bForceparametaBoxActionSwitch = mode;
}

void cltCharCommon::SetpclCM(cltCharManager* pclcm)
{
	pclCM = pclcm;
}

// 캐릭터가 워프를 할 수 있는가?
bool cltCharCommon::CanWarpFrom()
{
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		cltServer* pclserver = (cltServer*)pclClient;
		// 감옥에서는 워프 할 수 없다.
		if( clInnerStatus.IsStatus(INNERSTATUS_PRISON))
		{
			pclserver->SendServerResponseMsg(0, SRVAL_CAN_NOT_WARP_IN_PRISON, 0, 0, GetCharID());
			return false;
		}

		// 소속된 마을에 귀환탑이 세워져 있는지의 여부 체크
		//cltStrInfo* pclinfo = pclClient->pclVillageManager->pclCityHallManager->GetStrInfo(pclCI->clBI.siHomeVillage );
		//if( pclinfo != NULL )
		//{
		//	for (SI32 i = 0; i < MAX_HIRED_EVENTNPC_NUM; i++ )
		//	{
		//		// 귀환탑이 세워져 있지 않으면
		//		if(pclClient->GetUniqueFromHash(TEXT("KIND_RETURNTOWER")) != pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind)
		//		{
		//			// 세워져 있지 않을 경우, 마을에 귀환탑이 설치 되어야 워프 가능하다는 메세지.
		//			pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_RETURNTOWER, 0, 0, GetCharID()); 
		//			return false;
		//		}
		//	}		
		//}	

		// 3초 타이머 체크
		if( true == ((cltCharServer*)this)->m_clCharUpdateTimer[CHAR_UPDATETIMER_3SECOND].IsActivated())	// 타이머가 켜져 있으면
		{
			// 타이머가 켜진뒤로 3초가 지나지 않았으면
			if( false == ((cltCharServer*)this)->m_clCharUpdateTimer[CHAR_UPDATETIMER_3SECOND].IsTimed(GetTickCount()) )
			{
				// 순간이동은 3초에 한번만 가능하다는 메세지
				pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_LIMITTIME, 0, 0, GetCharID());
				return false;
			}
		}

		// 예식중인 사람이 예식장에 나가면 경고 메시지를 뿌려준다(단순 경고 용이다)
		if ( TRUE == pclserver->IsCountrySwitch(Switch_WeddingSystem) )
		{
			if ( (MAPINDEX_WEDDINGHALL == GetMapIndex()) && (IsMarried()) && (pclserver->m_pclMarriageMgr) )
			{
				cltWeddingReserveUnit* pclUnit = pclserver->m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtrFromNowTime();
				if ( (pclUnit) && (pclUnit->IsReserved()) )
				{
					if ( (pclCI->GetPersonID() == pclUnit->m_siMate1_PersonID ) || ( pclCI->GetPersonID() == pclUnit->m_siMate2_PersonID ) )
					{
						pclserver->SendServerResponseMsg(0, SRVAL_WEDDING_HALL_OUT_NOTICE, 0, 0, GetCharID());
					}
				}
			}
		}

	}

	else
	{
		cltClient* pclclient = (cltClient*)pclClient;

		if( clInnerStatus.IsStatus(INNERSTATUS_PRISON))
		{
			TCHAR* pTitle = GetTxtFromMgr(836);
			TCHAR* pText = GetTxtFromMgr(6034);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);

			return false;
		}
	}

	// 운영자 맵에서는 운영자만이 나갈 수 있다.
	if ( GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL && GetMapIndex() == MAPINDEX_MASTERWORLD )
		return false;

	SI32 siCharID = GetCharID();

	// 위 조건을 모두 통과하면 워프를 할 수 있다.
	return true;
}

// 해당 맵으로 워프해서 들어갈 수 있는가?
bool cltCharCommon::CanWarpTo( SI32 siToMapIndex )
{
	// 영자나라의 개인상점으로는 운영자가 아니면 들어갈 수 없다.
	if ( GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL && siToMapIndex == MAPINDEX_MASTERWORLD )		return false;

	// 서버 전용 처리
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		cltServer* pclserver = (cltServer*)pclClient;

		//[진성] 서버 이벤트에 나타나는 맵들은 모두 워프로 이동 불가능하게 한다.
		if(pclClient->IsCountrySwitch(Switch_Server_Event))
		{
			// 서버 이벤트 우승으로 생기는 맵은 워프로 이동이 불가능하게 한다.
			if(true ==  pclClient->pclServerEventManager->IsEventMap(siToMapIndex))
				return false;
		}

		//서버 리턴 메시지 : 이 맵은 워프가 금지되어있습니다
		if( pclClient->pclMapManager->IsBlockWarp( siToMapIndex ) == true )
		{		
			pclserver->SendServerResponseMsg(0,SRVAL_FAIL_WARP_BLOCKWARP,0,0, GetCharID());
			return false;
		}

		// 초보자 던젼은 초보자가 아니면 들어갈 수 없다.
		if ( siToMapIndex == MAPINDEX_BEGINNER1 && pclCI->clIP.GetLevel() > 10 )
		{
			pclserver->SendServerResponseMsg(0, SRVAL_TOOHIGHLEVEL,  MAX_LEVEL_FOR_BEGINNERMAP, 0, GetCharUnique());
			return false;
		}
		if ( siToMapIndex == MAPINDEX_FESTIVAL ) 
		{
			pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_RACCOONWORLD, 0, 0, GetCharUnique() );
			return false ;	
		}	// 해당 지역은 워프로 못들어간다 티켓으로 들어가는거 뺴면 

		// [종호_NHN->NDOORS] 연령별 구분
		// PK서비스를 하지 않으면 PK맵으로 워프해서 들어갈 수 없다.

		if(pclClient->siServiceArea == ConstServiceArea_Korea)
		{
			SI32 siCharID = GetCharID();

			if(pclserver->pclCM->IsValidID(siCharID) == false)
				return false;
			
			if(pclClient->pclCM->CR[siCharID]->pclCI->clBI.m_uiRealAge < 18 && pclClient->pclMapManager->IsPkMap( siToMapIndex ))
			{
				pclserver->SendServerResponseMsg(0,SRVAL_FAIL_WARP_BLOCKWARP,0,0, GetCharID());
				return false;
			}
		}
		else
		{
			if( pclClient->siEnablePVP == 0 &&	pclClient->pclMapManager->IsPkMap( siToMapIndex ) )
			{
				pclserver->SendServerResponseMsg(0,SRVAL_FAIL_WARP_BLOCKWARP,0,0, GetCharID());
				return false;
			}
		}

		// 레벨제한 때문에 들어갈 수 없다.
		if(pclClient->pclMapManager->IsEnterLevel(siToMapIndex, pclCI->clIP.GetLevel()) == false)
		{
			// 해당맵은 레벨 LvX~LvY까지만 들어갈 수 있습니다.
			pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_LEVEL_RANGE, 
				pclClient->pclMapManager->GetMinLevel(siToMapIndex), 
				pclClient->pclMapManager->GetMaxLevel(siToMapIndex),
				GetCharUnique());
			return false;
		}

		// [영훈] 개인 상점을 연 상태에서 시장을 열 수 있는 지역에서 시장을 열 수 없는 지역으로 이동하는 것이라면 막는다
		if ( (pclClient->pclMapManager->IsCanMarketOpenMap( GetMapIndex() ) == true)
			&& (pclClient->pclMapManager->IsCanMarketOpenMap( siToMapIndex ) == false) )
		{
			SI32 siCharID = GetCharID();

			if ( pclserver->pclCM->IsValidID( siCharID ) == true )
			{
				if ( (pclserver->pclCM->CR[siCharID]->bPersonalShopSwitch == true)
					|| (pclserver->pclCM->CR[siCharID]->bPremiumPersonalShop == true)
					)
				{
					pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_WARPTO_NOTMARKETOPEN_MAP, 0, 0, siCharID );
					return false;
				}
			}
		}

		//================================================================
		// 배틀로얄
		//================================================================
		CBattleRoyalMgr* pclBattleRoyalMgr = pclserver->m_pclBattleRoyalMgr;
		CBattleRoyal* pclBattleRoyal = NULL;
		cltCharServer* pclCharServer = (cltCharServer*)this;
		if( NULL != pclserver->m_pclBattleRoyalMgr)
		{
			// 외부에서 경기장으로 워프하기 불가능
			if( ( MAPINDEX_BATTLEROYAL_MABRIUM == siToMapIndex) || ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == siToMapIndex) )
			{
				return false;
			}

			pclBattleRoyal = pclBattleRoyalMgr->GetBattleRoyal(pclCharServer);
			if(NULL != pclBattleRoyal)
			{
				if( (MAPINDEX_BATTLEROYAL_MABRIUM == GetMapIndex()) || ( MAPINDEX_BATTLEROYAL_GRANDMABRIUM == GetMapIndex()))
				{
					if(pclBattleRoyal->IsGamingState())
						return false;
				}
			}			
		}
		if(siToMapIndex	==	MAPINDEX_FESTIVAL)
		{
			pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_GORACCOONWORLD_WARP, 0, 0,  GetCharID() );
			return false;
		}

		//[진성] 파티장으로는 이동 불가능.
		/*if( true == pclClient->pclFeastManager->IsPartyHallMap(siToMapIndex) )
		{
			return false;
		}*/

		if(pclClient->IsCountrySwitch( Switch_PKHuntMap_Change_Info ))
		{
			if ( pclClient->pclMapManager->IsPkMap(siToMapIndex))
			{
				pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_GORACCOONWORLD_WARP, 0, 0,  GetCharID() );	// 해당지역으로는 워프 할수 없습니다.
				return false	;	// pk 지역은 워프 불가능 
			}
		}
	}

	// 인던일때 워프가 맵 타입에 따라 다름
	if( pclClient->pclMapManager->IsInstanceMap(siToMapIndex) )
	{
		if(pclClient->pclMapManager->IsInstanceMap(GetMapIndex()) == false)
		{
			return false;
		}
		
		switch ( pclClient->pclMapManager->GetInstanceMapType(siToMapIndex) ) 
		{
			// 길드맵은 인던 안에서만 워프가 가능하다.
			case INSTANCEMAP_TYPE_GUILD:
				{
					SI32 siTartgetParentMap		= pclClient->pclMapManager->GetParentMap( siToMapIndex );
					SI32 siSrcParentMap			= pclClient->pclMapManager->GetParentMap( GetMapIndex() );

					// 같은 맵이 아니라면 워프가 불가능 하다.
					if( siSrcParentMap != siTartgetParentMap )			return false;
				}
				break;
			
			//  파티맵에서는 워프불가능
			case INSTANCEMAP_TYPE_PARTY:
				{
					return false;
				}
				break;
			
			// 서버 이벤트 멥에서는 워프불가능
			case INSTANCEMAP_TYPE_SERVER:
				{
					return false;
				}
				break;
		}
	}
	return true;
}

// 공짜 워프를 사용할 수 있는가?
bool cltCharCommon::CanFreeWarp( SI32 siDestMapIndex )
{	
	//-------------------------------------------------------------------
	// 기본 체크
	//-------------------------------------------------------------------

	// 기간제 워프 티켓 체크
	if (pclCI->clBI.bUseNoLimitTicketWarp == true)
		return true;

	// 기간제 워프 티켓 유효기간 체크
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if( pclCI->clBI.siNoLimitTicketWarpDateVary > 0 && 
			pclCI->clBI.siNoLimitTicketWarpDateVary < ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() )
			return false;
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if( pclCI->clBI.siNoLimitTicketWarpDateVary > 0 && 
			pclCI->clBI.siNoLimitTicketWarpDateVary < ((cltClient*)pclClient)->clClientDate.GetDateVary() )
			return true;
	}

	// 포교이면 워프가 공짜
	if ( pclCI->clBI.uiPoliceSwitch == 1 )
	{
		if(pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE(23490))
		{
			if( pclClient->GameMode == GAMEMODE_SERVER )
			{
				//((cltCharServer*)this)->DecreaseEquipDur(PERSONITEM_HAT, 5);
			}
			return true;
		}
	}

	// 수호천사이면 워프가 공짜
	if ( pclCI->clBI.uiAngelSwitch == 1 )
	{
		if( pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE(23485))
		{
			if( pclClient->GameMode == GAMEMODE_SERVER )
			{
				//((cltCharServer*)this)->DecreaseEquipDur(PERSONITEM_HAT, 5);
			}
			return true;
		}
	}


	// 군주이면 워프가 공짜
	if ( pclCI->clBI.uiGRank == GRANK_KING )
	{
		if( pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23500) ||
			pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23505) )
		{
			return true;
		}
	}

	// 대신이면 워프가 공짜
	if ( pclCI->clBI.uiGRank == GRANK_MINISTER1 ||
		 pclCI->clBI.uiGRank == GRANK_MINISTER2 ||
		 pclCI->clBI.uiGRank == GRANK_MINISTER3 ||
		 pclCI->clBI.uiGRank == GRANK_MINISTER4 ||
		 pclCI->clBI.uiGRank == GRANK_MINISTER5 ||
		 pclCI->clBI.uiGRank == GRANK_MINISTER6 )
	{				
		if(	pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23510) )		
		{
			return true;
		}
	}

	// 버프중에 사랑버프와 우정버프가 동시에 걸려있으면, 워프 공짜
	if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) && pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP ) )
	{
		return true;
	}

	// PC방 프리미엄 서비스 - 워프 공짜
	if ( pclCI->clBI.bPCRoom == true )
	{
		return true;
	}

	//[추가 : 황진성 2008. 1. 15 => 최강길드는 워프가 꽁짜~]
	if(1 == uiBestGuild)
	{
		return true;
	}
	// 쿠션이 있고, 않아 있는 경우 -> 한양만 공짜 워프 가능
	if( IsHaveCushionItem() > 0 && GetCurrentOrder() == ORDER_SITDOWN )
	{
		if( siDestMapIndex == MAPINDEX_PALACE )
		{
			// 목적지가 한양이면, 공짜워프 가능
			return true;
		}
	}

	// [영훈] 엔펠리스 이동하기 퀘스트 수행시 공짜 워프
	SI32 siQuestClearCond	= QUEST_CLEAR_COND_WARPTOPALACE;
	SI16 siQuestType		= 0;
	SI16 siQuestUnique		= 0;
	SI16 siPara1			= 0;
	SI16 siPara2			= 0;


	if ( pclCI->clQuestInfo.IsQuestGoing(siQuestClearCond, &siQuestType, &siQuestUnique, &siPara1, &siPara2) == true )
	{
		if ( siDestMapIndex == MAPINDEX_PALACE ) 
		{
			// 한양으로 갈때는 퀘스트를 깨버리고 보낸다.
			DoQuestCheckAndAction( siQuestClearCond );
			return true;
		}
		
	}

	// [영훈] 기자단 모자 : 기자단이면 워프가 공짜 (2008. 06 .05)
	if ( CONST_JOURNALIST_HAT_ITEMUNIQUE == pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique )
	{
		return true;
	}

	// 이벤트 워프 공짜 기능 - 자신이 속한 마을로 공짜로 워프 가능
	// 클라이언트와 서버의 체크하는 코드가 틀리다.
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		cltStrInfo* pclinfo = pclClient->pclVillageManager->pclCityHallManager->GetStrInfo( pclCI->clBI.siHomeVillage );
		if( pclinfo != NULL )
		{
			for (SI32 i = 0; i <MAX_HIRED_EVENTNPC_NUM; i++)
			{
				if( pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))    == pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind ||
					//pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")) == pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind ||
					pclClient->GetUniqueFromHash(TEXT("KIND_RETURNTOWER")) == pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind )	
				{
					// 자신이 속한 마을로 공짜로 워프 가능
					if( pclCI->clBI.siHomeVillage == siDestMapIndex )
					{
						return true;
					}
				}
			}
		}
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		cltCharClient* pclcharclient = (cltCharClient*)this;
		
		for (SI32 i = 0; i <MAX_HIRED_EVENTNPC_NUM; i++)
		{
			if( pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))    == pclcharclient->siEventNPCKind[i] ||
				//pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")) == pclcharclient->siEventNPCKind[i] ||
				pclClient->GetUniqueFromHash(TEXT("KIND_RETURNTOWER")) == pclcharclient->siEventNPCKind[i] )	
			{
				// 자신이 속한 마을로 공짜로 워프 가능
				if( pclCI->clBI.siHomeVillage == siDestMapIndex )
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool cltCharCommon::CanWarpToChar( SI32 siCharID )
{
	if( pclClient->GameMode != GAMEMODE_SERVER)			return false;
	if( pclClient->pclCM->IsValidID(siCharID) == false)	return false;

	cltServer* pclserver = (cltServer*)pclClient;
	cltCharServer* pclcharTo = (cltCharServer*)pclClient->pclCM->CR[siCharID];

	// 죽은 캐릭터한테는 워프 할 수 없다.
	if ( pclClient->pclCM->IsAlive(siCharID) == false )		return false;

	if ( pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar)== true )	// 변경후 
	{
		if ( IsGuildWarMap_Use_New_GuildWar( pclCM->CR[siCharID]->GetMapIndex() )  )
		{
			BOOL				bInBattle = FALSE;
			cltGuildWarManager*	pclGuildWarManager = NULL;

			if ( pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar)== true )	// 변경후 
			{
				// 상대방이 참여중인 길드전쟁 정보를 찾는다.
				for(SI32 i=0; i<GUILDWAR_FIELDNUM_OLD; i++)
				{
					if(i >= GUILDWAR_FIELDNUM_OLD) continue	;
					if( pclserver->pclGuildWarManager[i]->m_siAwayGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
						pclserver->pclGuildWarManager[i]->m_siHomeGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
					{
						pclGuildWarManager = pclserver->pclGuildWarManager[i];
					}
				}
			}
			else	// 변경전 
			{
				// 상대방이 참여중인 길드전쟁 정보를 찾는다.
				for(SI32 i=0; i<GUILDWAR_FIELDNUM; i++)
				{
					if(i >= GUILDWAR_FIELDNUM) continue	;
					if( pclserver->pclGuildWarManager[i]->m_siAwayGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
						pclserver->pclGuildWarManager[i]->m_siHomeGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
					{
						pclGuildWarManager = pclserver->pclGuildWarManager[i];
					}
				}
			}

			// 길드전쟁에 우리 길드가 참여중인가?
			if ( pclGuildWarManager != NULL &&
				( pclGuildWarManager->m_siAwayGuildUnique == pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
				pclGuildWarManager->m_siHomeGuildUnique == pclCI->clBI.clGuildRank.GetGuildUnitIndex()) )
			{
				bInBattle = TRUE;
			}

			// 전쟁에 참여중인 길드원이 아니므로 전장에 들어갈 수 없다.
			if (bInBattle == FALSE)
			{
				return false;
			}
		}


	}
	else
	{
		if ( IsGuildWarMap_Not_Use_New_GuildWar( pclCM->CR[siCharID]->GetMapIndex() )  )
		{
			BOOL				bInBattle = FALSE;
			cltGuildWarManager*	pclGuildWarManager = NULL;

			if ( pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar)== true )	// 변경후 
			{
				// 상대방이 참여중인 길드전쟁 정보를 찾는다.
				for(SI32 i=0; i<GUILDWAR_FIELDNUM_OLD; i++)
				{
					if(i >= GUILDWAR_FIELDNUM_OLD) continue	;
					if( pclserver->pclGuildWarManager[i]->m_siAwayGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
						pclserver->pclGuildWarManager[i]->m_siHomeGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
					{
						pclGuildWarManager = pclserver->pclGuildWarManager[i];
					}
				}
			}
			else	// 변경전 
			{
				// 상대방이 참여중인 길드전쟁 정보를 찾는다.
				for(SI32 i=0; i<GUILDWAR_FIELDNUM; i++)
				{
					if(i >= GUILDWAR_FIELDNUM) continue	;
					if( pclserver->pclGuildWarManager[i]->m_siAwayGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
						pclserver->pclGuildWarManager[i]->m_siHomeGuildUnique == pclcharTo->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
					{
						pclGuildWarManager = pclserver->pclGuildWarManager[i];
					}
				}
			}

			// 길드전쟁에 우리 길드가 참여중인가?
			if ( pclGuildWarManager != NULL &&
				( pclGuildWarManager->m_siAwayGuildUnique == pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
				pclGuildWarManager->m_siHomeGuildUnique == pclCI->clBI.clGuildRank.GetGuildUnitIndex()) )
			{
				bInBattle = TRUE;
			}

			// 전쟁에 참여중인 길드원이 아니므로 전장에 들어갈 수 없다.
			if (bInBattle == FALSE)
			{
				return false;
			}
		}


	}
	// 새로운 길드전 에 참여 중인가
	if ( IsGuildWarMap_NEW( pclCM->CR[siCharID]->GetMapIndex() )  )	// 상대방이 길드전맵에 있다.
	{
		if ( pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar) == true )	// 새 길드전이 들어가야 이루틴을 탄다.
		{
			BOOL				bInBattle = FALSE;
			cltGuildWarManager*	pclGuildWarManager = NULL;

			SI32 siMyGuildindex = pclCI->clBI.clGuildRank.GetGuildUnitIndex()	;
			if(GUILDWAR_HOMEGUILD == pclserver->pclGuildHuntMapManager->IsHomeGuildorAwayGuild(  siMyGuildindex )  ||
				GUILDWAR_AWAYGUILD == pclserver->pclGuildHuntMapManager->IsHomeGuildorAwayGuild( siMyGuildindex ) )// 홈길드로 참여중이다
			{
				bInBattle = TRUE;
			}
			// 전쟁에 참여중인 길드원이 아니므로 전장에 들어갈 수 없다.
			if (bInBattle == FALSE)
			{
				return false;
			}

		}
	}

	// 공성전 중에는 상대마을 캐릭터에게 워프 할 수 없다.
	if( pclClient->bVillageWarSwitch == true )
	{
		if(pclClient->pclVillageManager->IsAggressiveVillage(pclCI->clBI.siHomeVillage, pclcharTo->pclCI->clBI.siHomeVillage) == TRUE)
		{
			return false;
		}
	}

	// 타겟이 인스턴스 던젼에 있는 경우
	if( pclClient->pclMapManager->IsInstanceMap(pclcharTo->GetMapIndex()) == true )
	{
		// 캐릭터가 인스턴스 던젼에 있어야 워프가 가능하다.
		if( pclClient->pclMapManager->IsInstanceMap( GetMapIndex() ) == false )		return false;
		
		SI32 siTartgetParentMap = pclClient->pclMapManager->GetParentMap( pclcharTo->GetMapIndex() );
		SI32 siSrcParentMap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );

		// 같은 맵이 아니라면 워프가 불가능 하다.
		if( siSrcParentMap != siTartgetParentMap )			return false;
	}

	// 레벨제한 때문에 들어갈 수 없다.
	if(pclClient->pclMapManager->IsEnterLevel(pclcharTo->GetMapIndex(), pclCI->clIP.GetLevel()) == false)
	{
		// 해당맵은 레벨 LvX~LvY까지만 들어갈 수 있습니다.
		pclserver->SendServerResponseMsg(0, SRVAL_FAIL_WARP_LEVEL_RANGE, 
											pclClient->pclMapManager->GetMinLevel(pclcharTo->GetMapIndex()), 
											pclClient->pclMapManager->GetMaxLevel(pclcharTo->GetMapIndex()),
											GetCharUnique());
		return false;
	}

	return true;
}


void cltCharCommon::PartyHallItemRemove( SI32 id )
{
	// 이 코드는 서버에서만 실행 가능
	if ( GAMEMODE_SERVER != pclClient->GameMode )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;

	//[진성] 파티홀. 파티장에서 받은 아이템 모조리 제거. => 2008. 3. 12
	UI32 GetItemReason	= 0;
	SI32 InvenCount		= 0;

	// 캐릭터 장착창 + 인벤토리에 있는 아이템 제거
	for(InvenCount = 0; InvenCount < MAX_ITEM_PER_PERSON; ++InvenCount)	
	{
		GetItemReason = pclCI->clCharItem.clItem[InvenCount].clItemCommon.clCommonInfo.uiGetItemReason;
		if( cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM == GetItemReason )
		{
			// 아이템 제거.  
			sDBRequest_UseItem useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclCI->clCharItem.clItem[InvenCount], USEITEM_REASON_PATYHALL);
			pclserver->pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
		}
	}

    // 공간상자에 들어있는 아이템도 제거	
	//cltSpaceBox* pclSpaceBoxitem = &pclCI->clSpaceBoxItem;
	cltSpaceBox* pclSpaceBoxitem = pclSpaceBoxItem;
	if(pclSpaceBoxitem)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_SPACE_BOX; ++InvenCount)	
		{
			GetItemReason = pclSpaceBoxitem->clItem[InvenCount].clItemCommon.clCommonInfo.uiGetItemReason;
			if( cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM == GetItemReason )
			{
				// 아이템 제거.  
				sDBRequest_Use_SpaceBox_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclSpaceBoxitem->clItem[InvenCount], USEITEM_REASON_DATEOVER);
				pclserver->pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
			}
		}
	}
}

//[진성] 네잎크로버가 현재 사용할수 없는 거면 삭제 => 2008-8-14
void cltCharCommon::NotFourLeafItemRemove( SI32 id )
{
	// 이 코드는 서버에서만 실행 가능
	if ( GAMEMODE_SERVER != pclClient->GameMode )
	{
		return;
	}
	cltServer* pclserver = (cltServer*)pclClient;

	UI32 GetItemReason	= 0;
	SI32 InvenCount		= 0;

	// 캐릭터 장착창 + 인벤토리에 있는 아이템 제거
	for(InvenCount = 0; InvenCount < MAX_ITEM_PER_PERSON; ++InvenCount)	
	{
		if( ITEMUNIQUE(2755) == pclCI->clCharItem.clItem[InvenCount].siUnique || 
			ITEMUNIQUE(2754) == pclCI->clCharItem.clItem[InvenCount].siUnique	)	
		{	
			if( pclCI->clCharItem.clItem[InvenCount].siUnique != pclserver->siFourLeafUnique )	
			{
				// 아이템 제거.  
				sDBRequest_UseItem useitem(GetCharID(), pclCI->GetPersonID(), InvenCount, &pclCI->clCharItem.clItem[InvenCount], USEITEM_REASON_PATYHALL);
				pclserver->pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
			}
		}
	}

	// 공간상자에 들어있는 아이템도 제거	
	//cltSpaceBox* pclSpaceBoxitem = &pclCI->clSpaceBoxItem;
	cltSpaceBox* pclSpaceBoxitem = pclSpaceBoxItem;
	if(pclSpaceBoxitem)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_SPACE_BOX; ++InvenCount)	
		{
			if( ITEMUNIQUE(2755) == pclSpaceBoxitem->clItem[InvenCount].siUnique || 
				ITEMUNIQUE(2754) == pclSpaceBoxitem->clItem[InvenCount].siUnique	)	
			{	
				if( pclSpaceBoxitem->clItem[InvenCount].siUnique != pclserver->siFourLeafUnique )	
				{
					// 아이템 제거.  
					sDBRequest_Use_SpaceBox_Item useitem(GetCharID(), pclCI->GetPersonID(), InvenCount, &pclSpaceBoxitem->clItem[InvenCount], USEITEM_REASON_DATEOVER);
					pclserver->pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
				}
			}
		}
	}
}

//[진성] 축제 음식 제거
void cltCharCommon::FestivalFoodItemRemove( SI32 id )
{
	cltServer* pclserver = (cltServer*)pclClient;
	// 캐릭터 장착창 + 인벤토리에 있는 아이템 제거
	for( SI32 InvenCount = 0; InvenCount < MAX_ITEM_PER_PERSON; ++InvenCount )	
	{
		if( ITEMUNIQUE(3934) == pclCI->clCharItem.clItem[InvenCount].siUnique || 
			ITEMUNIQUE(3931) == pclCI->clCharItem.clItem[InvenCount].siUnique ||
			ITEMUNIQUE(3930) == pclCI->clCharItem.clItem[InvenCount].siUnique ||
			ITEMUNIQUE(3929) == pclCI->clCharItem.clItem[InvenCount].siUnique ||
			ITEMUNIQUE(3932) == pclCI->clCharItem.clItem[InvenCount].siUnique ||
			ITEMUNIQUE(3933) == pclCI->clCharItem.clItem[InvenCount].siUnique 	)	
		{	
			if( pclCI->clCharItem.clItem[InvenCount].siUnique != pclserver->siFourLeafUnique )	
			{
				// 아이템 제거.  
				sDBRequest_UseItem useitem( GetCharID(), pclCI->GetPersonID(), InvenCount, &pclCI->clCharItem.clItem[InvenCount], USEITEM_REASON_FESTIVAL_FOOD );
				pclserver->pclGameDBProcess->SendMsg( DBSELECT_BASE, (sPacketHeader *)&useitem );
			}
		}
	}
}

//==================================================
// cltShopTradeData
//==================================================
cltShopTradeData::cltShopTradeData()
{
	memset( this, 0, sizeof( cltShopTradeData ) );
}

void cltShopTradeData::Init()
{
	memset( this, 0, sizeof( cltShopTradeData ) );
}

void cltShopTradeData::InitData()
{
#ifdef _SAFE_MEMORY
	m_clItem.ZeroMem();					
	m_siSelectedInventoryPos.ZeroMem();	
	m_siPrice.ZeroMem();					
	m_siCurrentPrice.ZeroMem();			
#else
	memset( m_clItem,					0,	sizeof(m_clItem)				);
	memset( m_siSelectedInventoryPos,	0,	sizeof(m_siSelectedInventoryPos));
	memset( m_siPrice,					0,	sizeof(m_siPrice)				);
	memset( m_siCurrentPrice,			0,	sizeof(m_siCurrentPrice)		);
#endif
	memset( m_szShopTitle,				0,	sizeof(m_szShopTitle)			);
	m_siHandPoint  = 0;
	m_siSkillLevel = 0;
	m_bPremium = false;
}

void cltShopTradeData::Set(cltShopTradeData *pclData)
{
	m_siShopMode		= pclData->m_siShopMode;
	m_siPersonID		= pclData->m_siPersonID;
	MStrCpy(m_szAccountID, pclData->m_szAccountID,MAX_PLAYER_NAME);
	MStrCpy(m_szShopTitle, pclData->m_szShopTitle,MAX_SHOP_TITLE_LENGTH);
	for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
	{
		m_clItem[i].Set(&pclData->m_clItem[i]);
		m_siSelectedInventoryPos[i]= pclData->m_siSelectedInventoryPos[i];
		m_siPrice[i]		= pclData->m_siPrice[i];
		m_siCurrentPrice[i] = pclData->m_siCurrentPrice[i];
	}
	m_siHandPoint  = pclData->m_siHandPoint;
	m_siSkillLevel = pclData->m_siSkillLevel;
	m_bPremium	= pclData->m_bPremium;

	m_clSpacialItem.Set(&pclData->m_clSpacialItem);									// 이건 이용권 아이템이 등록된다.
	m_siSelectedSpacialInventoryPos = pclData->m_siSelectedSpacialInventoryPos;					// 위치도 등록된다.
}

void cltShopTradeData::SetCurrentPrice(cltItemManagerCommon *pclitemmanager)
{
#ifdef _SAFE_MEMORY
	m_siCurrentPrice.ZeroMem();
#else
	memset( m_siCurrentPrice,		  0, sizeof(m_siCurrentPrice));
#endif
	//-------------------------------------------
	// 현재 시세를 설정한다.
	//-------------------------------------------
	for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
	{
		if(m_clItem[i].siUnique)
		{
			cltItemPriceUnit* pclprice = pclitemmanager->GetCurrentPrice(m_clItem[i].siUnique);
			if(pclprice) m_siCurrentPrice[i] = pclprice->siPrice;
		}
	}
}

//==================================================
// cltShopBannerData
//==================================================
cltShopBannerData::cltShopBannerData()
{
	memset( this, 0, sizeof( cltShopBannerData ) );
}

void cltShopBannerData::Init()
{
	memset( this, 0, sizeof( cltShopBannerData ) );
}

void cltShopBannerData::Set(cltShopBannerData *pclBanner)
{
	memcpy(this, pclBanner, sizeof(cltShopBannerData));							//ok
}

void cltShopBannerData::SetData(cltShopTradeData *pclData)
{
	m_siShopMode = pclData->m_siShopMode;
	for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i)
	{
		if(pclData->m_clItem[i].siItemNum > 0)
		{
			m_siUnique[i] = pclData->m_clItem[i].siUnique;
			m_siPrice[i]  = pclData->m_siPrice[i];
		}
		else
		{
			m_siUnique[i] = 0;
			m_siPrice[i]  = 0;
		}
	}
	MStrCpy(m_szShpoTitle,pclData->m_szShopTitle,MAX_SHOP_TITLE_LENGTH);
	m_siHandPoint = pclData->m_siHandPoint; 
	m_siSkillLevel= pclData->m_siSkillLevel;
	m_bPremium = pclData->m_bPremium;
}

void cltShopBannerData::MakeBannerText(cltItemManagerCommon* pclItemManager, TCHAR *ptext,TCHAR *pShopTitle)
{
	TCHAR szExplain[MAX_EXPLAIN_LENTH];

	StringCchCopy(szExplain, MAX_EXPLAIN_LENTH, TEXT(""));

	if(m_bPremium == true)
	{
		if( NULL != pShopTitle )
		{
			StringCchCopy(pShopTitle,MAX_SHOP_TITLE_LENGTH,m_szShpoTitle);
		}
	}

	TCHAR* pText = GetTxtFromMgr(3323);

	if(m_siShopMode == PSHOP_MODE_BUY)		
	{
		pText = GetTxtFromMgr(3323);
		StringCchCat(szExplain, MAX_EXPLAIN_LENTH, pText);				
	}

	else if(m_siShopMode == PSHOP_MODE_SELL)
	{
		pText = GetTxtFromMgr(3324);
		StringCchCat(szExplain, MAX_EXPLAIN_LENTH, pText);		
	}
	else if(m_siShopMode == PSHOP_MODE_MAKEITEM)	
	{
		pText = GetTxtFromMgr(3809);
		StringCchCat(szExplain, MAX_EXPLAIN_LENTH, pText);		
	}
	else if(m_siShopMode == PSHOP_MODE_MAKEITEM_WANT)	//Switch_Change_manufacture_request_interface	[성웅] 제조 의뢰 인터페이스 개선
	{
		pText = GetTxtFromMgr(40829);
		StringCchCat(szExplain, MAX_EXPLAIN_LENTH, pText);		
	}


	TCHAR szMoney[256];
	TCHAR buffer[256];
	SI32 siCount = 0;
	if( m_siShopMode == PSHOP_MODE_BUY ||
		m_siShopMode == PSHOP_MODE_SELL)
	{
		for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if(m_siUnique[i])
			{
				TCHAR *pName = (TCHAR *)pclItemManager->GetName(m_siUnique[i]);

				if(pName)
				{
					
						StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("\r\n"));						
				

					TCHAR* pText = GetTxtFromMgr(611);
					g_JYLibFunction.SetNumTxt(m_siPrice[i], szMoney, 256, pText);
					g_JYLibFunction.SetNumUnit(m_siPrice[i], buffer, 256, pText);
					size_t buffersize, szMoneysize;
					StringCchLength(buffer, 256, &buffersize);
					StringCchLength(szMoney, 256, &szMoneysize);

					// Japan이 아닐경우 무조건 단위 출력안함
					if(buffersize < szMoneysize || 
						pclClient->siServiceArea != ConstServiceArea_Japan)	
					{
						StringCchCopy(szMoney, 256, buffer);
					}
					
					TCHAR namebuffer[256] = TEXT("");
					StringCchCopy( namebuffer, 256, pName);

					if ( pclClient->IsWhereServiceArea(ConstServiceArea_English | ConstServiceArea_EUROPE) )
					{
						// 너무 길면 이상하게 나오므로.. 15자 이상은 잘라준다.
						size_t nameSize = 0;
						StringCchLength(namebuffer, 256, &nameSize);
						if (  nameSize > 14 )
						{
							for( SI16 j=13; j<(int)nameSize ; j++ )
							{
								if ( j < 15 ) namebuffer[j]=TEXT('.');
								else
									namebuffer[j] = 0;
							}

						}
					}
					/*
                    if( pclClient->siServiceArea == ConstServiceArea_Japan)
					{
						// 일본도 너무 길면 짤리므로 5자 이상은  잘라준다.
						size_t siStringLen = 0;
							
						StringCchLength(namebuffer,256, &siStringLen );
						
						if( siStringLen > 5 )
						{
							TCHAR tempbuffer[256] = {'\0',};
							StringCchCopyN( tempbuffer ,256,namebuffer,5);
							StringCchCat(tempbuffer,256,TEXT(".."));  
							StringCchCopy(namebuffer,256,tempbuffer);
						}

					}*/

					StringCchPrintf(buffer, 256, TEXT("%s:%s"), namebuffer, szMoney);
					StringCchCat(szExplain, MAX_EXPLAIN_LENTH, buffer);
					siCount++;
				}
			}
		}
	}
	else if(m_siShopMode == PSHOP_MODE_MAKEITEM)
	{
		for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if(m_siUnique[i])
			{
				TCHAR *pName = (TCHAR *)pclItemManager->GetName(m_siUnique[i]);
				if(pName)
				{
					if(siCount==0)	StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("\r\n"));
					else
					{
						if ( pclClient->IsWhereServiceArea(ConstServiceArea_English | ConstServiceArea_EUROPE) ) 
						{
							StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("\r\n"));
						}
						else
						{
							StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("/"));
						}
					}
					TCHAR* pText = GetTxtFromMgr(611);
					g_JYLibFunction.SetNumTxt(m_siPrice[i], szMoney, 256, pText);
					g_JYLibFunction.SetNumUnit(m_siPrice[i], buffer, 256, pText);
					if(_tcslen(buffer)<_tcslen(szMoney)|| 
						pclClient->siServiceArea != ConstServiceArea_Japan)	
						StringCchCopy(szMoney, 256, buffer);


					{
						TCHAR* pText = NULL;
						if ( pclClient->IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
						{
							pText = GetTxtFromMgr(9864);
						}
						else
						{
							if ( pclClient->IsCountrySwitch(Switch_Change_manufacture_request_interface) )
							{
								pText = GetTxtFromMgr(9864);
							}
							else
							{
								pText = GetTxtFromMgr(3512);
							}
						}

						StringCchPrintf(buffer, 256, pText, 
							pName, szMoney, m_siSkillLevel ,m_siHandPoint);
						StringCchCat(szExplain, MAX_EXPLAIN_LENTH, buffer);
						siCount++;
					}
				}
			}
		}
	}


	//Switch_Change_manufacture_request_interface	[성웅] 제조 의뢰 인터페이스 개선
	else if(m_siShopMode == PSHOP_MODE_MAKEITEM_WANT)
	{
		for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if(m_siUnique[i])
			{
				TCHAR *pName = (TCHAR *)pclItemManager->GetName(m_siUnique[i]);
				if(pName)
				{
					if(siCount==0)	StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("\r\n"));
					else
					{
						if ( pclClient->IsWhereServiceArea(ConstServiceArea_English | ConstServiceArea_EUROPE) ) 
						{
							StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("\r\n"));
						}
						else
						{
							StringCchCat(szExplain, MAX_EXPLAIN_LENTH, TEXT("/"));
						}
					}
					TCHAR* pText = GetTxtFromMgr(611);
					g_JYLibFunction.SetNumTxt(m_siPrice[i], szMoney, 256, pText);
					g_JYLibFunction.SetNumUnit(m_siPrice[i], buffer, 256, pText);
					if(_tcslen(buffer)<_tcslen(szMoney)|| 
						pclClient->siServiceArea != ConstServiceArea_Japan)	
						StringCchCopy(szMoney, 256, buffer);


					{
						TCHAR* pText = NULL;
						if ( pclClient->IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
						{
							pText = GetTxtFromMgr(9864);
						}
						else
						{
							if ( pclClient->IsCountrySwitch(Switch_Change_manufacture_request_interface) )
							{
								pText = GetTxtFromMgr(9864);
							}
							else
							{
								pText = GetTxtFromMgr(3512);
							}
						}

						StringCchPrintf(buffer, 256, pText, 
							pName, szMoney, m_siSkillLevel ,m_siHandPoint);
						StringCchCat(szExplain, MAX_EXPLAIN_LENTH, buffer);
						siCount++;
					}
				}
			}
		}
	}


	
	MStrCpy( ptext, szExplain, MAX_PERSONAL_SHOP_TEXT_SIZE );
}

//==================================================
// cltShopRepairData
//==================================================
cltShopRepairData::cltShopRepairData()
{
	memset( this, 0, sizeof( cltShopRepairData ) );
}

void cltShopRepairData::Init()
{
	memset( this, 0, sizeof( cltShopRepairData ) );
}

void cltShopRepairData::InitData()
{
	m_siPersonID			= 0;
	m_szAccountID[0]		= '\0';

	m_clRepairItem.Init();
	m_siRepairItemPos		= 0;
	m_siPrice				= 0;

	for( SI32 i=0; i<m_kMaterial.GetSize(); i++ )
	{
		m_kMaterial[i].Init();
	}
}

void cltShopRepairData::Set(cltShopRepairData *pclData)
{
	m_siPersonID			= pclData->m_siPersonID;
	StringCchCopy( m_szAccountID, sizeof(m_szAccountID), pclData->m_szAccountID );

	m_clRepairItem.Set( &pclData->m_clRepairItem );
	m_siRepairItemPos		= pclData->m_siRepairItemPos;
	m_siPrice				= pclData->m_siPrice;

	for( SI32 i=0; i<m_kMaterial.GetSize(); i++ )
	{
		m_kMaterial[i].Set( &pclData->m_kMaterial[i] );
	}
}

bool cltShopRepairData::ExistItem( SI16 siPos, cltItem* pclitem )
{
	if( pclitem == NULL )						return false;
	// Rapair Item Check
	if( m_siRepairItemPos == siPos &&
		m_clRepairItem.siUnique == pclitem->siUnique )
	{
		return true;
	}

	for( SI32 i=0; i<m_kMaterial.GetSize(); i++ )
	{
		if( m_kMaterial[i].siStgPos == siPos &&
			m_kMaterial[i].siItemUnique == pclitem->siUnique )
		{
			return true;
		}
	}

	return false;
}

//==================================================
// cltSearchShopData
//==================================================
cltSearchShopData::cltSearchShopData()
{
	memset( this, 0, sizeof( cltSearchShopData ) );
}

void cltSearchShopData::Init()
{
	memset( this, 0, sizeof( cltSearchShopData ) );
}

void cltSearchShopData::CopyGeneralData(cltSearchShopData *pclData)
{
	m_siShopMode  = pclData->m_siShopMode;
	m_siItemUniqueType  = pclData->m_siItemUniqueType;
	m_siItemSearchPrice = pclData->m_siItemSearchPrice;
}

void cltSearchShopData::CopyData(SI32 index1, SI32 index2, cltSearchShopData *pclData)
{
	if(pclData == NULL)		return;
	if(index1 < 0 || index1 >= MAX_SEARCHSHOP_ITEM_NUMBER)		return;
	if(index2 < 0 || index2 >= MAX_SEARCHSHOP_ITEM_NUMBER)		return;

	MStrCpy(m_szName[index1], pclData->m_szName[index2], MAX_PLAYER_NAME);
	m_siLevel[index1]		= pclData->m_siLevel[index2];
	m_siMapIndex[index1]	= pclData->m_siMapIndex[index2];
	m_siMapX[index1]		= pclData->m_siMapX[index2];
	m_siMapY[index1]		= pclData->m_siMapY[index2];

	m_clItem[index1].Set(&pclData->m_clItem[index2]);
	m_siPrice[index1]		= pclData->m_siPrice[index2];

	m_siHandPoint[index1]	= pclData->m_siHandPoint[index2];
	m_siSkillLevel[index1]	= pclData->m_siSkillLevel[index2];
}

void cltSearchShopData::ClearData(SI32 index1)
{
	if(index1 < 0 || index1 >= MAX_SEARCHSHOP_ITEM_NUMBER)		return;

	StringCchCopy(m_szName[index1], MAX_PLAYER_NAME, TEXT(""));
	m_siLevel[index1]		= 0;
	m_siMapIndex[index1]	= 0;
	m_siMapX[index1]		= 0;
	m_siMapY[index1]		= 0;

	m_clItem[index1].Init();
	m_siPrice[index1]		= 0;
	m_siHandPoint[index1]	= 0;
	m_siSkillLevel[index1]	= 0;

}

void cltSearchShopData::MoveData(SI32 index1, SI32 index2, cltSearchShopData *pclData)
{
	CopyData(index1, index2, pclData);
	pclData->ClearData(index2);
}

void cltSearchShopData::Set(cltSearchShopData *pclData)
{
	CopyGeneralData(pclData);

	for(SI32 i = 0; i < MAX_SEARCHSHOP_ITEM_NUMBER; ++i)
	{
		CopyData(i, i, pclData);
	}
}

//==================================================
// cltBeHitInfo
//==================================================
cltBeHitInfo::cltBeHitInfo()
{
	Init();
}

void cltBeHitInfo::Init()
{
	bBeAttackedSwitch	= false;
	siAttackerID			= 0;
}

void cltBeHitInfo::Set(bool bhitswitch, SI16 attackerid)
{
	bBeAttackedSwitch	= bhitswitch;
	siAttackerID		= attackerid;
}

//==================================================
// cltJim
//==================================================
cltJim::cltJim()
{
	Init();
}

void cltJim::Init()
{
	siJimHostCharUnique		= 0;
	siJimSlaveCharUnique	= 0;
	dwJimFrame				= 0;
	dwNewJimFrame			= 0;
}

// 찜하다. 
bool cltJim::SetJim(SI32 slavecharunique)
{
	if(siJimSlaveCharUnique)return false;

	siJimSlaveCharUnique	= slavecharunique;

	return true;
}

// 찜 되다. 
bool cltJim::SetBeJimed(SI32 hostcharunique, DWORD frame)
{
	// 찜을 한 캐릭터가 있고 그것이 지금 주어진 캐릭터와 다르다면 
	if(siJimHostCharUnique && siJimHostCharUnique != hostcharunique)return false;

	// 기존의 찜 주인과 서로 다른 찜이라면.. 
	if(siJimHostCharUnique == 0)
	{
		dwNewJimFrame = frame;
	}

	siJimHostCharUnique		= hostcharunique;
	dwJimFrame				= frame;

	return true;
}

//==================================================
// cltCharListInfo
//==================================================
cltCharListInfo::cltCharListInfo()
{
}

void cltCharListInfo::Init()
{
	ZeroMemory(this, sizeof(cltCharListInfo));

	clBI.Init();
	clIP.Init();
}
void cltCharListInfo::Set(cltCharListInfo* pclinfo)
{
	clBI.Set(&pclinfo->clBI);
	clIP.Set(&pclinfo->clIP);

	/*
	for(SI32 i = 0; i < MAX_SHAPE_ITEM; ++i)
	{
		clCharItem[i].Set(&pclinfo->clCharItem[i]);
	}
	*/
}

//==================================================
// cltMovePointList
//==================================================
cltMovePointList::cltMovePointList()
{
	siPointNum = 0;
}

void cltMovePointList::Init()
{
	siPointNum = 0;
}

bool cltMovePointList::AddPos(SI32 six, SI32 siy)
{
	if(siPointNum < 0 || siPointNum >= MAX_CHAR_MOVE_POINT)return false;

	clPos[siPointNum].Set(six, siy);
	siPointNum++;

	return true;
}

// 첫번째 지점에 도착했는가?
bool cltMovePointList::IsArrive(SI32 six, SI32 siy)
{
	if(siPointNum <= 0)return false;

	if(clPos[siPointNum-1].siX == six && clPos[siPointNum-1].siY == siy)return true;

	return false;
}

// 첫번째 경유지 도착처리.
void cltMovePointList::Arrive()
{
	if(siPointNum <= 0)return ;

	clPos[siPointNum-1].Init();

	siPointNum--;
}

//==================================================
// cltCharMoveInfo
//==================================================
cltCharMoveInfo::cltCharMoveInfo()
{
	Init();
}

void cltCharMoveInfo::Init()
{
	siDX			= 0;
	siDY			= 0;
	siMovePercent	= 0;
	siSparePercent	= 0;	// 자투리 %
	siNX			= 0;
	siNY			= 0;
	siStepWidth		= 0;
	dwLastMoveClock	= 0;
}


// 이동 %를 증가시킨다. 
SI32 cltCharMoveInfo::IncMovePercent(SI32 movespeed)
{
	if(siMovePercent < 0)
	{
		siMovePercent += movespeed;
		siMovePercent	= min(100, siMovePercent);
		if(siMovePercent > 0)
		{
			siSparePercent = siMovePercent;
			siMovePercent = 0;
		}
	}
	else
	{
		siMovePercent += movespeed;
		if(siMovePercent > 100)
		{
			siSparePercent = siMovePercent - 100;
			siMovePercent = 100;
		}
	}

	return siMovePercent;
}

//==================================================
// cltCharCommonSimpleVary
//==================================================
cltCharCommonSimpleVary::cltCharCommonSimpleVary()
{
	ZeroMemory(this, sizeof(cltCharCommonSimpleVary));
}

// 특정 애니메이션의 경우, 본래 캐릭터의 pk가 필요하기도 하다. (단순히 그리기만 하기 위해서)
// 변화해야 하는 에니메이션 타입데 대한 리턴만 한다.
bool cltCharCommon::selectRealAnyType( )
{
	bool select  = false;
	
	switch(Animation)
	{
		case ANITYPE_SLEEP:
		case ANITYPE_SLEEPCAT:
			select  = true;
			break;
	}

	return select;
}

SI16 cltCharCommon::GetPVP_LeagueEnemyPersonID( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siEnemyPersonID;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueEnemyPersonID( SI16 siEnemyID )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siEnemyPersonID = siEnemyID;
	}
}



SI16 cltCharCommon::GetPVP_League_Win( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siWin;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_League_Win( SI16 siWin )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siWin = siWin;
	}
}

void cltCharCommon::IncPVP_League_Win( SI16 siWin )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siWin += siWin;
	}
}

SI16 cltCharCommon::GetPVP_League_Draw( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siDraw;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_League_Draw( SI16 siDraw )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siDraw = siDraw;
	}
}

void cltCharCommon::IncPVP_League_Draw( SI16 siDraw )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siDraw += siDraw;
	}
}
SI16 cltCharCommon::GetPVP_League_Lose( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siLose;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_League_Lose( SI16 siLose )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siLose = siLose;
	}
}

void cltCharCommon::IncPVP_League_Lose( SI16 siLose )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siLose += siLose;
	}
}

SI16 cltCharCommon::GetPVP_LeagueStraight_Win( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siStraight_Win;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueStraight_Win( SI16 siWin )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Win = siWin;
	}
}

void cltCharCommon::IncPVP_LeagueStraight_Win( SI16 siWin )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Win += siWin;
	}
}

SI16 cltCharCommon::GetPVP_LeagueStraight_Draw( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siStraight_Draw;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueStraight_Draw( SI16 siDraw )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Draw = siDraw;
	}
}

void cltCharCommon::IncPVP_LeagueStraight_Draw( SI16 siDraw )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Draw += siDraw;
	}
}



SI16 cltCharCommon::GetPVP_LeagueGrade( void )
{
	SI16 siReturnValue = PVP_LEAGUE_GRADE_NONE;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siGrade;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueGrade( SI16 siGrade )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siGrade = siGrade;
	}
}

bool cltCharCommon::IsPVP_LeagueLatestPersonID( SI32 siDestPersonID )
{
	if ( pclPVP_LeagueInfo )
	{
		for ( SI32 siIndex=0; siIndex<PVP_LEAGUE_MAX_LATEST_MATCH_PERSON; ++siIndex )
		{
			if ( pclPVP_LeagueInfo->m_siLatestPersonID[siIndex] == siDestPersonID )
			{
				return true;
			}
		}
	}

	return false;
}

void cltCharCommon::PushPVP_LeagueLatestPersonID( SI32 siDestPersonID )
{
	if ( NULL == pclPVP_LeagueInfo )
	{
		return;
	}

	const SI32 siLastIndex = (PVP_LEAGUE_MAX_LATEST_MATCH_PERSON - 1);

	// 맨 하위 인덱스에까지 값이 차 있다면 앞으로 한칸씩 값을 이동한다
	if ( 0 <= pclPVP_LeagueInfo->m_siLatestPersonID[siLastIndex] )
	{
		for ( SI32 siIndex=0; siIndex<siLastIndex; ++siIndex )
		{
			SI32 siNextIndex = siIndex+1;
			if ( PVP_LEAGUE_MAX_LATEST_MATCH_PERSON <= siNextIndex )
			{
				break;
			}

			pclPVP_LeagueInfo->m_siLatestPersonID[siIndex]		= pclPVP_LeagueInfo->m_siLatestPersonID[siNextIndex];
			pclPVP_LeagueInfo->m_siLatestPersonID[siNextIndex]	= 0;
		}
	}

	// 빈칸에 값만 넣어주면 된다
	for ( SI32 siPushIndex=0; siPushIndex<PVP_LEAGUE_MAX_LATEST_MATCH_PERSON; ++siPushIndex )
	{
		if ( 0 >= pclPVP_LeagueInfo->m_siLatestPersonID[siPushIndex] )
		{
			pclPVP_LeagueInfo->m_siLatestPersonID[siPushIndex] = siDestPersonID;
		}
	}

}


SI16 cltCharCommon::GetPVP_LeagueStraight_Lose( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siStraight_Lose;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueStraight_Lose( SI16 siLose )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Lose = siLose;
	}
}

SI16 cltCharCommon::GetPVP_LeagueStraight_Win_Grade( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siStraight_Win_Grade;
	}

	return siReturnValue;
}
void cltCharCommon::SetPVP_LeagueStraight_Win_Grade( SI16 siWin )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Win_Grade = siWin;
	}
}
SI16 cltCharCommon::GetPVP_LeagueStraight_Lose_Grade( void )
{
	SI16 siReturnValue = 0;

	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->m_siStraight_Lose_Grade;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueStraight_Lose_Grade( SI16 siLose )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->m_siStraight_Lose_Grade = siLose;
	}
}
SYSTEMTIME cltCharCommon::GetPVP_LeagueEndBAttleTime( void )
{
	SYSTEMTIME siReturnValue	;
	ZeroMemory( &siReturnValue, sizeof(siReturnValue))	;
	if ( pclPVP_LeagueInfo )
	{
		siReturnValue = pclPVP_LeagueInfo->stLastPVPTime;
	}

	return siReturnValue;
}

void cltCharCommon::SetPVP_LeagueEndBAttleTime( SYSTEMTIME stEndTiem )
{
	if ( pclPVP_LeagueInfo )
	{
		pclPVP_LeagueInfo->stLastPVPTime = stEndTiem;
	}
}

BOOL cltCharCommon::IsMarried( void )
{
	if ( pclMarriage )
	{
		return pclMarriage->IsMarried();
	}

	return FALSE;
}
void cltCharCommon::SetProposePersonID( SI32 siProposePersonID )
{
	if ( pclMarriage )
	{
		pclMarriage->SetMatePersonID( siProposePersonID );
	}
}

SI32 cltCharCommon::GetProposePersonID( void )
{
	if ( pclMarriage )
	{
		return pclMarriage->GetMatePersonID();
	}

	return 0;
}
SI32 cltCharCommon::GetMyFamilyClass( void )	// 가족정보
{
	if ( pclFamily )
	{
		return pclFamily->GetMyClass_InFamily()	;
	}

	return MYCLASS_IN_FAMILY_NONE;
}

BOOL cltCharCommon::IsSoulGuardStatusOut()
{
	if ( false == IsPC(GetCharUnique()) )
	{
		return FALSE;
	}

	if ( NULL == pclSoulGuard )
	{
		return FALSE;
	}

	if ( TRUE == pclSoulGuard->IsEmpty() )
	{
		return FALSE;
	}

	SI32 siSoulGuardID = pclCM->GetIDFromCharUnique(siMySoulGuardUnique);	
	if ( FALSE == pclCM->IsValidID(siSoulGuardID) )
	{
		return FALSE;
	}

	if ( pclSoulGuard->GetStatus() == SOULGUARD_STATUS_OUT )
	{
		return TRUE;
	}

	return FALSE;
}

bool operator==( const cltSkillBookSubMagic& _LValue, cltSkillBookSubMagic& _RValue )
{
	// 부모가 같고 마법이 있다면 같은것으로 본다. 왜냐? 부모 마법은 하나의 보조 마법만 갖는다.
	if(	_LValue.GetParentMagicKind() == _RValue.GetParentMagicKind() 
		&& 0						 <  _RValue.GetMagicKind()	) 
	{
		return true;
	}

	return false;
}
void cltCharSkillBookInfo::Clear( void )
{
	for( SI32 siCount = 0; siCount < SKILLBOOK_MAGIC_NUM; ++siCount )
		m_clSkillBookMagic[siCount].Clear();

	m_clSkillBookSubMagicList.RemoveAll();
}

bool cltCharSkillBookInfo::IsSkillBookMagic( void ) 
{
	for( SI32 siCount = 0; siCount < SKILLBOOK_MAGIC_NUM; ++siCount )
	{
		if(		0 < m_clSkillBookMagic[siCount].GetMagicKind() 
			&&	0 < m_clSkillBookMagic[siCount].GetSkillUnique() ) 
			return true;	
	}
		
	

	return false;
}

void cltCharSkillBookInfo::SetSkillBookMagic( IN SI32 _siIndex, cltSkillBookMagic* _pclAddSkillBookMagic )
{
	if( 0 > _siIndex || SKILLBOOK_MAGIC_NUM <= _siIndex )											 return;
	if( 0 >= _pclAddSkillBookMagic->GetMagicKind() || 0 >= _pclAddSkillBookMagic->GetSkillUnique() ) return;

	m_clSkillBookMagic[_siIndex].Set( _pclAddSkillBookMagic );
}

void cltCharSkillBookInfo::AddSkillBookMagic( IN SI32 _siAttackType, cltSkillBookMagic* _pclAddSkillBookMagic )
{
	SI32 siIndex = 	GetIndexFromAttackType( _siAttackType );
	if( 0 > siIndex ) return;
	
	m_clSkillBookMagic[siIndex].Set( _pclAddSkillBookMagic );
}

cltSkillBookMagic* cltCharSkillBookInfo::GetSkillBookMagicIndex( IN SI32 _siIndex )
{
	return &m_clSkillBookMagic[_siIndex];
} 

void cltCharSkillBookInfo::DelSkillBookMagic( IN SI32 _siIndex )
{
	m_clSkillBookMagic[_siIndex].Clear();
} 

void cltCharSkillBookInfo::AddSkillBookSubMagic( cltSkillBookSubMagic _clAddSkillBookSubMagic )
{
	NkListPos ListPos = m_clSkillBookSubMagicList.FindPos( _clAddSkillBookSubMagic );
	m_clSkillBookSubMagicList.Remove( ListPos );
			
	m_clSkillBookSubMagicList.PushBack( _clAddSkillBookSubMagic );
}

cltSkillBookSubMagic* cltCharSkillBookInfo::FindSkillBookSubMagicFromParentMagic( SI32 _siParentMagic )
{
	cltSkillBookSubMagic clAddSkillBookSubMagic( 0, _siParentMagic, 0 );
	NkListPos pListPos = m_clSkillBookSubMagicList.FindPos( clAddSkillBookSubMagic );
	if( NULL == pListPos ) return NULL;
	
	static cltSkillBookSubMagic* pclSkillBookSubMagic;
	
	pclSkillBookSubMagic = m_clSkillBookSubMagicList.GetDataPtr( pListPos );

	return pclSkillBookSubMagic;
}

stMagicAttributeData* cltCharSkillBookInfo::FindMagicAttributeDataFromParentMagic( IN SI32 _siParentMagic, OUT SI32& _siSubMagicKind )
{
	_siSubMagicKind = 0;
	
	cltSkillBookSubMagic* pclSkillBookSubMagic = FindSkillBookSubMagicFromParentMagic( _siParentMagic );
	if( NULL == pclSkillBookSubMagic ) return NULL;

	stMagicAttributeData* psSubMagicData	   = pclClient->pclMagicManager->GetMagicAttribute( pclSkillBookSubMagic->GetMagicKind() ); 
	if( NULL == psSubMagicData ) return NULL;

	_siSubMagicKind = pclSkillBookSubMagic->GetMagicKind();

	return psSubMagicData;
}


void cltCharSkillBookInfo::DelSkillBookSubMagic( const cltSkillBookSubMagic _clAddSkillBookSubMagic )
{
	NkListPos ListPos = m_clSkillBookSubMagicList.FindPos( _clAddSkillBookSubMagic );
	m_clSkillBookSubMagicList.Remove( ListPos );
}

SI32 cltCharSkillBookInfo::GetIndexFromAttackType( IN SI32 _siAttackType )
{
	SI32 siIndex = -1;
	switch( _siAttackType )
	{
	case ATTACKTYPE_SWORD:		siIndex = 0;	break;
	case ATTACKTYPE_SPEAR:		siIndex = 1;	break;
	case ATTACKTYPE_AXE:		siIndex = 2;	break;
	case ATTACKTYPE_STAFF:		siIndex = 3;	break;
	case ATTACKTYPE_STAFF1:		siIndex = 3;	break;
	case ATTACKTYPE_STAFF2:		siIndex = 3;	break;
	case ATTACKTYPE_NEW_STAFF2:	siIndex = 3;	break;
	case ATTACKTYPE_BOW:		siIndex = 4;	break;
	case ATTACKTYPE_BOW1:		siIndex = 4;	break;
	case ATTACKTYPE_NEW_BOW1:	siIndex = 4;	break;
	case ATTACKTYPE_GUN:		siIndex = 5;	break;
	case ATTACKTYPE_GUN1:		siIndex = 5;	break;
	case ATTACKTYPE_NEW_GUN1:	siIndex = 5;	break;
	}

	return siIndex;
}

cltSkillBookMagic*	cltCharSkillBookInfo::GetSkillBookMagic( IN SI32 _siAttackType )			
{	
	SI32 siIndex = 	GetIndexFromAttackType( _siAttackType );
	if( 0 > siIndex ) return NULL;

	return &m_clSkillBookMagic[siIndex];			
}	

NkList<cltSkillBookSubMagic>*	cltCharSkillBookInfo::GetSkillBookSubMagicList( void )	
{	
	return &m_clSkillBookSubMagicList;	
}

bool cltCharSkillBookInfo::IsTimeOver( cltCharServer* _pclChar )
{
	cltServer* pclserver = (cltServer*)pclClient;
	bool bAction = false;
	for( SI32 siCount = 0; siCount < SKILLBOOK_MAGIC_NUM; ++siCount )
	{
		if( m_clSkillBookMagic[siCount].IsTimeOver( &pclserver->sTime ) )
		{
			sDBRequest_SkillBook_Magic_Del	clMsg( _pclChar->GetID(), _pclChar->pclCI->GetPersonID(), siCount, &m_clSkillBookMagic[siCount] );
			pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);	

			bAction = true;
		}
	}
	

	NkListPos				ListPos = m_clSkillBookSubMagicList.GetFrontPos();
	cltSkillBookSubMagic*	pclSkillBookSubMagic;
	while( ListPos )
	{
		pclSkillBookSubMagic = &((NkListNode<cltSkillBookSubMagic>*)ListPos)->GetData();
		if( pclSkillBookSubMagic->IsTimeOver( &pclserver->sTime ) )
		{
			sDBRequest_SkillBook_SubMagic_Del	clMsg( _pclChar->GetID(), _pclChar->pclCI->GetPersonID(), pclSkillBookSubMagic, true );
			pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);	

			bAction = true;
		}

		ListPos = ((NkListNode<cltSkillBookMagic>*)ListPos)->GetNext();
	}

	return bAction;
}

bool cltCharSkillBookInfo::IsFullSubMagic( IN SI32 _siSkillunique )
{
	int						siCount = 0;
	NkListPos				ListPos = m_clSkillBookSubMagicList.GetFrontPos();
	cltSkillBookSubMagic*	pclSkillBookSubMagic;
	while( ListPos )
	{
		pclSkillBookSubMagic = &((NkListNode<cltSkillBookSubMagic>*)ListPos)->GetData();
		if( _siSkillunique == pclSkillBookSubMagic->GetSkillUnique() )
		{
			++siCount;
		}

		ListPos = ((NkListNode<cltSkillBookMagic>*)ListPos)->GetNext();
	}

	return 3 <= siCount ? true : false;
}

void cltCharCurseEffect::SendMsgCurseInfo( SI32 _siTargetID )
{
	cltCharServer* pclTargetChar = pclClient->pclCM->GetCharServer( _siTargetID );
	if( NULL == pclTargetChar ) return;

	cltGameMsgResponse_CurseInfo clCurseInfo( pclTargetChar->GetCharUnique(), &pclTargetChar->m_clCharCurseEffect );
	cltMsg clMsg( GAMEMSG_RESPONSE_CURSEINFO, sizeof(clCurseInfo), (BYTE*)&clCurseInfo );
	pclTargetChar->SendNeighbourMsg(&clMsg, true);
}