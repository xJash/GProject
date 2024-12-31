#include "../Common/CommonHeader.h"
#include "../../../Client/Client.h"

//--------------------------------
// Client
//--------------------------------
//#include "../../Client/ColorTable/ColorTable.h"
#include "../../Client/Music/Music.h"

// ä�� ����. 
#include "../Client/Interface/DrawChat/DrawChatSurface.h"
#include "../Client/Interface/DrawChat/DrawChat.h"

// ĳ���� �̸� ��� ����
#include "../Client/Interface/DrawCharName/DrawCharName.h"

// ����ġ ���� 
#include "../../Client/Effect/ExpCounter/ExpCounter.h"
// ġ�� ���� 
#include "../../Client/Effect/HealCounter/HealCounter.h"

// ����
#include "../../Client/NInterface/NFarmingDlg/NFarmingDlg.h"

//���� ����
#include "../../Client/NInterface/NLetterDlg/NLetterDlg.h"

#include "../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
//#include "../../Client/Interface/PartyDlg/PartyDlg.h"
#include "../../Client/NInterface/NPartyDlg/NPartyDlg.h"

#include "../../Client/InterfaceMgr/InterfaceMgr.h"

#include "CharCriticalEffect/CharCriticalEffect.h"
#include "../../Client/Effect/Emoticon/EmoticonMgr.h"

// ��Ƽ ���� ���� ǥ��
#include "CharPartyEmoticon/CharPartyEmoticon.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Personalshop.h"
//#include "../Client/Interface/PersonalShop/PersonalShopDlg.h"

#include "../../CommonLogic/Msg/MsgType-RacoonDodgeEvent.h"

// ��ƿ ������ ���� �� ǥ��
#include "CharJim/CharJim.h"

//--------------------------------
// Common
//--------------------------------
#include "../Common/Bullet/Bullet.h"
#include "Util/Util.h"
#include "PersonInfo.h"
#include "../CharManager/CharManager.h"

// ��� ���� 
#include "../../Common/Order/Order.h"

//--------------------------------
// CommonLogic
//--------------------------------
#include "../CommonLogic/Msg/MsgType-Quest.h"

extern cltCommonLogic* pclClient;

extern SI32 AttackAtbInfo[];

cltCharClient::cltCharClient() : cltCharCommon()
{

	pImgSpr	= NULL;
	Font	= 0;
	siEffectFont = -1;

	siShadowAni = 0 ;
	siShadowFont = -1 ;

	DrawSwitch			=  TRUE;
	bDrawReadySwitch	=  false;

	RealImageXPercent=RealImageYPercent=100;
	dwDrawFrame			=  0;                         // ������ �׸��� �׸� ������ 
	dwLastWaitFrame		=  0;

	TransMode			=  TRANSPARENT_MODE_NORMAL;

	ImageXsize	= 0;
	ImageYsize	= 0;

	VibrateY		= 0;
	VibrateSwitch	= FALSE;

	bMouseOverSwitch = false;
	bNewSelectedSwitch	= false;
	NewSelectedDelay	= 0;
	MouseOverDelay		= 0;

	DrawStartX	=	DrawStartY	= 0;

	//----------------------------
	// �ִϸ��̼� 
	//---------------------------
	StringCchCopy(szHelmetCode,	32,	TEXT(""));
	StringCchCopy(szArmourCode,	32,	TEXT(""));
	StringCchCopy(szWeaponCode,	32, TEXT(""));
	StringCchCopy(szMantleCode,	32,	TEXT(""));
	StringCchCopy(szHorseCode,	32,	TEXT(""));


	//------------------------------
	// �̷� ��� ���� 
	//-----------------------------
	bReverseSwitch		= FALSE;                				// ����� ���� ���ΰ�?

	//-----------------------------
	// �̹��� ������ ���� 
	//-----------------------------
	RealImageStartX	=	RealImageEndX	= 0;
	RealImageStartY	=	RealImageEndY	= 0; 

	//------------------------------
	// ������� 
	//------------------------------
	bDyingOperationSwitch	= false;
	bGhostShowSwitch		= false;

	//----------------------------
	// �̵� ���� 
	//----------------------------
	siRX	=	siRY	= 0;
	MOX	=	MOY	= 0;
	MDX	=	MDY	= 0;

	//------------------------
	// �����, ��� ���� ó��. ( �ٴڿ� �� �׸��� �� )
	//-------------------------
	bBoss		= false;							// ������� �˷���� �ϴ°�?
	pclBoss		= NULL;

	//------------------------
	// Regeneration ���� 
	//-------------------------
	bRegeneration	 = false;					// ���� �Ǿ����� �˷���� �ϴ°�?
	pclRegeneration = NULL;

	//-----------------------------------------
	//�ڱ� ������ Ʈ���� �Ǽ��Ǿ� �ִ��� 
	//-----------------------------------------
#ifdef _SAFE_MEMORY
	siEventNPCKind.ZeroMem();
#else
	ZeroMemory(siEventNPCKind,sizeof(siEventNPCKind));
#endif

	//------------------------
	// ���λ��� ��� 
	//------------------------
	siShopMode      = 0;
	StringCchCopy(szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
	StringCchCopy(szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));


	//------------------------
	// �ǰ� �̹��� ���� 
	//-------------------------
	bHitDrawSwitch	= false;					// �ǰݵǾ����� �˷���� �ϴ°�?
	pclCharCut		= NULL;

	//------------------------
	// ������ ���� 
	//-------------------------
	bLevelUpDrawSwitch = false;				// �������Ǿ����� �˷���� �ϴ°�?
	pclLevelUp			= NULL;

	//------------------------
	// ��Ʈ ����Ʈ ���� 
	//-------------------------	 
	pclHeartEffect		= NULL;

	//------------------------
	// ���� Ŭ�ι� ����Ʈ ���� 
	//-------------------------	 
	pclFourLeafEffect = NULL;

	//------------------------
	// ��� ����Ʈ ���� 
	//-------------------------	 
	pclCushionEffect = NULL;
	pclCushionCatEffect = NULL;

	siCushionUnique = 0;

	//------------------------
	// MVP����Ʈ ���� 
	//-------------------------
	bMVPEffectDrawSwitch = false;				// �������Ǿ����� �˷���� �ϴ°�?
	pclMVPEffect			= NULL;

	//------------------------
	// Enchant ����Ʈ ����
	//-------------------------	 	
	bEnchantEffDrawSwitch = false;
	pclEnchantEff			= NULL;

	//------------------------
	// Quest ����Ʈ ����
	//-------------------------	 	
	//bQuestEffDrawSwitch = false;
	pclQuestEff			= NULL;


	//------------------------
	// ��ų ������ ���� 
	//-------------------------
	bSkillLevelUpDrawSwitch	= false;		// ��ų �������Ǿ����� �˷���� �ϴ°�?
	pclSkillLevelUp			= NULL;


	//------------------------
	// �̸�Ƽ�� ����
	//-------------------------
	pclEmoticonEff			= NULL;

	//------------------------
	// �߷�Ÿ�� �̸�Ƽ�� ����
	//-------------------------
	m_pclValentineEmoticonEff			= NULL;

	//------------------------
	// ����ġ ǥ�� 
	//------------------------
	pclExpCounter		= NULL;					// ����ġ ǥ��. 

	//------------------------
	// ġ��   ǥ�� 
	//------------------------
	pclHealCounter		= NULL;					// HEAL ǥ�� 

	//------------------------
	// �ʻ�� ǥ�� 
	//------------------------
	pclCriticalEffect	= NULL;					// �ʻ�� ǥ��

	//------------------------
	// ��ƿ ������ ���� �� ǥ��
	//------------------------
	pclJim = NULL;


	//------------------------
	//	��Ƽ ���� ǥ�ø� ���� ��.
	//------------------------
	pclPartyEmoticon = NULL;

	//-----------------------
	// ��ǳ�� ���� 
	//-----------------------
	pclDrawChat = NULL;

	//-----------------------
	// ĳ���� �̸� ��� ����
	//-----------------------
	pclDrawCharName = NULL;

	//---------------------------------
	// ������ ĳ���Ϳ� ���ǽ� �ε���. 
	//--------------------------------
	siHeroSurfaceIndex	= -1;

	//-----------------------------
	// ������ ĳ���� ����.
	//-----------------------------
	siHostID	= 0;
	siSlaveID	= 0;

	//--------------------------
	// ĳ���� �̸� ���� ǥ�� 
	//--------------------------
	dwLastMakeCharNameFrame = 0;
	StringCchCopy(szCharNameInfo, 128, TEXT(""));

	//--------------------------
	// ġ�� ȿ��. 
	//--------------------------
	dwHealClock	= 0;

	//------------------------
	// ��ǰ ���� ȿ��. 
	//------------------------
	bStartMakeItemSwitch	= false;
	dwStartMakeItemClock	= 0;
	dwDelayMakeItemClock	= 0;

	clMyShopData.Init();
	bMyShopStart = FALSE;

	m_RankMarkImgEncBuffer	= NULL;
	m_RankMarkEncHres = 0;
	m_RankMarkEncVres = 0;

	m_siSetItemImgAnimationCounter1 = 0;
	m_siSetItemImgAnimationCounter2 = 0;

	m_siWeddingImgAnimationCounter = 0;

	//--------------------------
	// ��ȣ���� Ư����� ����Ʈ
	//--------------------------
	dwSoulGuardSF_Clock	= 0;
	siSoulGuardSF_Kind		= 0;
}

cltCharClient::~cltCharClient()
{

	SAFE_DELETE( pclDrawCharName  );
	SAFE_DELETE( pclDrawChat );
	SAFE_DELETE( pclBoss );
	SAFE_DELETE( pclRegeneration );
	SAFE_DELETE( pclCharCut );
	SAFE_DELETE( pclLevelUp );
	SAFE_DELETE( pclHeartEffect );
	SAFE_DELETE( pclFourLeafEffect );
	SAFE_DELETE( pclCushionEffect );
	SAFE_DELETE( pclCushionCatEffect );
	SAFE_DELETE( pclMVPEffect );
	SAFE_DELETE( pclEnchantEff);
	SAFE_DELETE( pclQuestEff );
	SAFE_DELETE( pclEmoticonEff );
	SAFE_DELETE( m_pclValentineEmoticonEff );

	SAFE_DELETE( pclSkillLevelUp );
	SAFE_DELETE( pclHealCounter );
	SAFE_DELETE( pclExpCounter );
	SAFE_DELETE( pclCriticalEffect );
	SAFE_DELETE( pclJim );
	SAFE_DELETE( pclPartyEmoticon );
	SAFE_DELETE( m_RankMarkImgEncBuffer );

}

void cltCharClient::InitCharClient()
{
	cltClient* pclclient = (cltClient*)pclClient;

	// ����� �غ� �Ǿ� ���� �ʴ�. 
	SetDrawReadySwitch(false);

	//----------------------------
	// �ִϸ��̼� 
	//---------------------------
	StringCchCopy(szHelmetCode,	32,	TEXT("KOR01"));
	StringCchCopy(szArmourCode,	32,	TEXT("KOR01"));
	StringCchCopy(szWeaponCode,	32,	TEXT("KOR01"));
	StringCchCopy(szMantleCode,	32,	TEXT(""));
	StringCchCopy(szHorseCode,	32,	TEXT(""));

	//------------------------------
	// ������� 
	//------------------------------
	bDyingOperationSwitch	= false;
	bGhostShowSwitch		= false;

	pImgSpr	= NULL;
	Font	= 0;
	siEffectFont = -1;

	siShadowAni = 0 ;
	siShadowFont = -1 ;

	DrawSwitch=TRUE;
	RealImageXPercent=RealImageYPercent=100;
	dwDrawFrame	= 0;                         // ������ �׸��� �׸� ������ 
	dwLastWaitFrame		=  0;

	//------------------------------
	// �̷� ��� ���� 
	//-----------------------------
	bReverseSwitch		= FALSE;                				// ����� ���� ���ΰ�?

	//-----------------------------
	// �̹��� ������ ���� 
	//-----------------------------
	RealImageStartX	=	RealImageEndX	= 0;
	RealImageStartY	=	RealImageEndY	= 0; 

	//---------------------------------
	// ������ ĳ���Ϳ� ���ǽ� �ε���. 
	//--------------------------------
	siHeroSurfaceIndex	= -1;

	//------------------------
	// �����, ��� ���� ó��. ( �ٴڿ� �� �׸��� �� )
	//-------------------------
	bBoss	= false;							// ������� �˷���� �ϴ°�?
	if(pclBoss)
	{
		delete pclBoss;
		pclBoss = NULL;
	}

	pclBoss	= new CBossEffect( pclClient->GetGlobalSpr(GIMG_BIGBOSS), pclClient->GetGlobalSpr(GIMG_SMALLBOSS) );

	//------------------------
	// Regeneration �̹��� ���� 
	//-------------------------
	bRegeneration	= false;					// �ǰݵǾ����� �˷���� �ϴ°�?
	if(pclRegeneration)
	{
		delete pclRegeneration;
		pclRegeneration = NULL;
	}
	//pclRegeneration = new CRegeneration( pclClient->GetGlobalSpr(GIMG_REGENERATION) );
	pclRegeneration = new CRegeneration( pclClient->GetGlobalSpr(GIMG_BEGINWARP) );

	//-----------------------------------------
	//�ڱ� ������ Ʈ���� �Ǽ��Ǿ� �ִ��� 
	//-----------------------------------------
	//ZeroMemory(siEventNPCKind,sizeof(siEventNPCKind));


	//------------------------
	// ���λ��� ��� 
	//------------------------
	siShopMode      = 0;
	StringCchCopy(szPersonalShopText, MAX_PERSONAL_SHOP_TEXT_SIZE, TEXT(""));
	StringCchCopy(szPersonalShopTitle, MAX_SHOP_TITLE_LENGTH, TEXT(""));
	//------------------------
	// �ǰ� �̹��� ���� 
	//-------------------------
	bHitDrawSwitch	= false;					// �ǰݵǾ����� �˷���� �ϴ°�?
	if(pclCharCut)
	{
		SAFE_DELETE(pclCharCut)
	}
	pclCharCut = new CCharCut();

	//------------------------
	// ������ �̹��� ���� 
	//-------------------------
	bLevelUpDrawSwitch = false;
	if(pclLevelUp)
	{
		SAFE_DELETE(pclLevelUp);		 
	}
	pclLevelUp = new CLevelUpEffect( pclClient->GetGlobalSpr( GIMG_LEVELUP ), pclClient->GetGlobalSpr( GIMG_LEVELUP_EFF ));

	//-----------------------
	// ��Ʈ ����Ʈ ����
	//-----------------------
	if(pclHeartEffect)
	{
		SAFE_DELETE(pclHeartEffect);
	}
	pclHeartEffect = new CHeartEffect( pclClient->GetGlobalSpr( GIMG_HEART_EFFECT ) );

	//------------------------
	// ���� Ŭ�ι� ����Ʈ ���� 
	//-------------------------
	if(pclFourLeafEffect)
	{
		SAFE_DELETE(pclFourLeafEffect);
	}
	pclFourLeafEffect = new CFourLeafEffect( pclClient->GetGlobalSpr( GIMG_FOURLEAF ) );


	// ���
	//KHY - 1109 - ��í����- �������漮�߰�
	siCushionUnique = 0;

	if(pclCushionEffect)
	{
		SAFE_DELETE(pclCushionEffect);
	}
	pclCushionEffect = new CCushionEffect( pclClient->GetGlobalSpr( GIMG_CUSHION_1  ) , pclClient->GetGlobalSpr( GIMG_CUSHION_2 ),
		pclClient->GetGlobalSpr( GIMG_CUSHION_3  ) , pclClient->GetGlobalSpr( GIMG_CUSHION_4 ),
		pclClient->GetGlobalSpr( GIMG_CUSHIOND_1 ) , pclClient->GetGlobalSpr( GIMG_CUSHIOND_2),
		pclClient->GetGlobalSpr( GIMG_CUSHIOND_3 ) , pclClient->GetGlobalSpr( GIMG_CUSHIOND_4));
	if(pclCushionCatEffect)
	{
		SAFE_DELETE(pclCushionCatEffect);
	}									
	pclCushionCatEffect = new CCushionCatEffect( pclClient->GetGlobalSpr( GIMG_CUSHION_CAT_1 ) , pclClient->GetGlobalSpr( GIMG_CUSHION_CAT_2 ),
		pclClient->GetGlobalSpr( GIMG_CUSHION_CAT_3 ) , pclClient->GetGlobalSpr( GIMG_CUSHION_CAT_4 ),
		pclClient->GetGlobalSpr( GIMG_CUSHION_DOG_1 ) , pclClient->GetGlobalSpr( GIMG_CUSHION_DOG_2 ),
		pclClient->GetGlobalSpr( GIMG_CUSHION_DOG_3 ) , pclClient->GetGlobalSpr( GIMG_CUSHION_DOG_4 ));

	//------------------------
	// MVP ����Ʈ ����
	//-------------------------
	bMVPEffectDrawSwitch = false;
	SAFE_DELETE(pclMVPEffect);
	pclMVPEffect= new CMVPEffect( pclClient->GetGlobalSpr( GIMG_MVP_EFFECT ), pclClient->GetGlobalSpr( GIMG_MVP_AROUND_EFFECT ));

	//------------------------
	// Enchant ����Ʈ ����
	//-------------------------
	bEnchantEffDrawSwitch = false;
	SAFE_DELETE(pclEnchantEff);
	pclEnchantEff= new CEnchantEff( pclClient->GetGlobalSpr( GIMG_ENCHANT_EFFECT_HERO_WE ),  pclClient->GetGlobalSpr( GIMG_ENCHANT_EFFECT_HERO_AM ), pclClient->GetGlobalSpr( GIMG_ENCHANT_EFFECT_HEROINE_WE ), pclClient->GetGlobalSpr( GIMG_ENCHANT_EFFECT_HEROINE_AM ));

	//------------------------
	// Quest ����Ʈ ����
	//-------------------------
	//bQuestEffDrawSwitch = false;
	SAFE_DELETE(pclQuestEff);
	pclQuestEff= new CQuestEff( pclClient->GetGlobalSpr( GIMG_QUEST_EFFECT_RECEIVE ),  pclClient->GetGlobalSpr( GIMG_QUEST_EFFECT_CLEAR ));


	//------------------------
	// ��ų ������ �̹��� ���� 
	//-------------------------
	bSkillLevelUpDrawSwitch = false;
	if(pclSkillLevelUp)
	{
		delete pclSkillLevelUp;
		pclSkillLevelUp = NULL;
	}
	pclSkillLevelUp = new CSkillLevelUpEffect( pclClient->GetGlobalSpr( GIMG_SKILLLEVELUP ) , pclClient->GetGlobalSpr( GIMG_SKILLLEVELUP_EFF ) );


	//------------------------
	// �̸�Ƽ�� �̹��� ����
	//------------------------
	if( pclEmoticonEff )
	{
		delete pclEmoticonEff;
		pclEmoticonEff = NULL;
	}

	pclEmoticonEff = new CEmoticonEffect( pclClient->GetGlobalSpr( GIMG_EMOTICON) );

	//------------------------
	// �߷�Ÿ�� �̸�Ƽ�� �̹��� ����
	//------------------------
	if( m_pclValentineEmoticonEff )
	{
		delete m_pclValentineEmoticonEff;
		m_pclValentineEmoticonEff = NULL;
	}

	m_pclValentineEmoticonEff = new CEmoticonEffect( pclClient->GetGlobalSpr( GIMG_VALENTINEEMOTICON) );

	//------------------------
	// ����ġ ǥ�� 
	//------------------------
	if(pclExpCounter)
	{
		delete pclExpCounter;
		pclExpCounter = NULL;
	}
	pclExpCounter		= new CExpCounter;

	//------------------------
	// ġ�� ǥ�� 
	//------------------------
	if(pclHealCounter)
	{
		delete pclHealCounter;
		pclHealCounter = NULL;
	}
	pclHealCounter		= new CHealCounter;

	if ( pclCriticalEffect )
	{
		delete pclCriticalEffect;
		pclCriticalEffect = NULL;
	}

	pclCriticalEffect	= new CCharCriticalEffect( pclClient->GetGlobalSpr( GIMG_CRITICALEFFECT ) );


	//------------------------
	// ��ƿ ������ ���� �� ǥ��
	//------------------------
	if ( pclJim )
	{
		delete pclJim;
		pclJim = NULL;
	}

	pclJim = new CCharJim( pclClient->GetGlobalSpr( GIMG_JIM ) );

	//------------------------
	//	��Ƽ ���� ǥ�ø� ���� ��.
	//------------------------
	if ( pclPartyEmoticon )
	{
		pclPartyEmoticon->Initialize();
	}
	else
	{
		pclPartyEmoticon = new CCharPartyEmoticon();
	}

	//-----------------------
	// �� ǳ�� ���� 
	//-----------------------
	if(pclDrawChat)
	{
		pclDrawChat->Initialize( GetCharUnique() );
	}
	else
	{
		pclDrawChat = new CDrawChat();
		pclDrawChat->Initialize( GetCharUnique() );
	}

	//-----------------------
	// ĳ���� �̸� ��� ����
	//-----------------------
	if ( pclDrawCharName )
	{
		//pclDrawCharName->Initialize();
		delete pclDrawCharName;
		pclDrawCharName = NULL;
		pclDrawCharName	= new CDrawCharName();
	}
	else
	{
		pclDrawCharName	= new CDrawCharName();
	}

	// ���ΰ� ĳ������ ũ��� ������ �ִ�. 
	bool selectKind = false;

	// anytype�� ����, ���ΰ��� ���θ� �˾ƺ��� �Լ��� Ʋ����.
	if(selectRealAnyType( ))
	{
		selectKind = pclKI->IsAtb(ATB_HERO);
	}
	else
	{
		selectKind = GetKindInfo(true)->IsAtb(ATB_HERO);
	}


	if(selectKind)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		TransMode = pclKI->clKIDrawInfo.siTransparentMode;
		AlphaValue = pclKI->clKIDrawInfo.siAlphaValue ;

		ImageXsize = 320;
		ImageYsize = 240;

		// by LEEKH 2007.12.24 - TRANSFORM
		VibrateY		= 0;
		VibrateSwitch	=	pclKI->VibrateSwitch;
	}
	else
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		TransMode = GetKindInfo()->clKIDrawInfo.siTransparentMode;
		AlphaValue = GetKindInfo()->clKIDrawInfo.siAlphaValue ;

		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 ref = GetKindInfo(true)->clCharAniManager.FindFirstAni();
		if(ref <= 0)MsgBox(TEXT("fd9jfd"), TEXT("fd9jf:%s"), GetName());

		// by LEEKH 2007.12.24 - TRANSFORM
		ImageXsize = GetKindInfo(true)->clCharAniManager.GetImageXsize(ref, pclClient->CurrentClock);
		ImageYsize = GetKindInfo(true)->clCharAniManager.GetImageYsize(ref, pclClient->CurrentClock);

		// by LEEKH 2007.12.24 - TRANSFORM
		VibrateY		= 0;
		VibrateSwitch	=	GetKindInfo()->VibrateSwitch;
	}

	if(IsPC(CharUnique))
	{
		SetName(TEXT(""));

		// ���ΰ� ĳ������ ��� 
		if(GetID() == 1)
		{
			// Ŭ���̾�Ʈ�� �غ�Ǿ����� �뺸�Ѵ�. 
			{
				cltMsg clMsg(GAMEMSG_REQUEST_READY, 0, NULL);
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}

			//if(((cltClient*)pclClient)->bFirstHeroCharInitSwitch == false)
			{
				//	((cltClient*)pclClient)->bFirstHeroCharInitSwitch = true;

				// ������ �̸��� ��û�Ѵ�. 
				{
					cltGameMsgRequest_GetName clInfo( CharUnique );
					cltMsg clNormalMsg(GAMEMSG_REQUEST_NAME, sizeof(clInfo), (BYTE*)&clInfo);
					pclclient->SendMsgToServer((sPacketHeader*)&clNormalMsg);
				}

				// ������ �������� ��Ȳ�� ��û�Ѵ�.
				{
					cltMsg clMsg(GAMEMSG_REQUEST_GETVILLAGEINFO, 0);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				}

				//// ������ �� �������� �ִ��� ��û�Ѵ�.
				//{
				//	pclclient->pclCM->CR[1]->pclCI->clItemMall.Init();
				//	cltMsg clMsg(GAMEMSG_REQUEST_ITEMMALLEXISTENCE,0);
				//	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				//}   // ĳ���� ���ýø��� ��û�Ҽ� �ֵ��� client-Login ���� �̻纸�½��ϴ�. [����]

			}
		}
	}

	//-----------------------------
	// ������ ĳ���� ����.
	//-----------------------------
	siHostID		= 0;
	siSlaveID		= 0;

	//--------------------------
	// ĳ���� �̸� ���� ǥ�� 
	//--------------------------
	dwLastMakeCharNameFrame = 0;
	StringCchCopy(szCharNameInfo, 128, TEXT(""));

	//--------------------------
	// ��⵿���� ���������� �ٲ�ð�
	//--------------------------
	lastWaitAniChanged = pclclient->CurrentClock;

	//--------------------------
	// ġ�� ȿ��. 
	//--------------------------
	dwHealClock	= 0;

	//------------------------
	// ��ǰ ���� ȿ��. 
	//------------------------
	bStartMakeItemSwitch	= false;
	dwStartMakeItemClock	= 0;
	dwDelayMakeItemClock	= 0;


	//-------------------------
	// ���� ó���� �Ѵ�.
	//------------------------
	FogAction();

	//--------------------------
	// ��ȣ���� Ư����� ����Ʈ
	//--------------------------
	dwSoulGuardSF_Clock	= 0;
	siSoulGuardSF_Kind		= 0;

}



BOOL cltCharClient::OperateWaitClient()
{
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE) == false || clInnerStatus.IsStatus(INNERSTATUS_FROZEN) == false || clInnerStatus.IsStatus(INNERSTATUS_STUN) == false )
	{
		// ������ ������ �ִ� ĳ���ʹ� ��ġ�� ������ �ʴ´�.
		// ���ۿ� ������� ������ �ִϸ� ���� ������ �ȵȴ�.
		SetAnimation(WaitType);
		// �ִϸ��̼��� ������Ʈ �Ǹ�, 
		if(DoAnimationDelay() == TRUE)
		{
			// ���� �̹����� �����ִ� ���̶��, 
			if(clAniInfo.GetAniStep() == 0 )//&& clAniInfo.siRetryNum > 0 )
			{
				BOOL bRideMotorcycle = FALSE;
				SI32 siHorseUnique = 0;
				if( pclCI->clHorseInfo.GetCurrentHorseRIDEHORSE() )
				{
					cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
					if(pclHorse && pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
					{
						bRideMotorcycle = TRUE;
					}

					siHorseUnique = pclHorse->siHorseUnique;
				}

				if( GetKindInfo(true)->IsAtb(ATB_HERO) == false )		bRideMotorcycle = false;

				if(bRideMotorcycle)
				{
					WaitType = ANITYPE_WAIT0;
					SetAnimation(WaitType);
					DoAnimationDelay();
				}
				else
				{
					if(WaitType == ANITYPE_WAIT0)
					{
						// ���� 2���� �ִ��� Ȯ���Ѵ�. 
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 aniref			= GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(ANITYPE_WAIT1);

						//cyj �ؿ� �ڵ忡�� �������� Ȧ���� �����Ҷ��� ��� ������ �ȹٲ�Ƿ� ����
						//if((pclClient->GetFrame() % 10 == 0) && aniref >= 0)
						SI32 siRand = 0;

						// ������� ��� ������ ����� ���� �ִ� ��ó�� �������� WAIT0�� ���δ�.
						if( siHorseUnique == HORSEUNIQUE_SASURI)
						{
							siRand = 1000;
						}
						else
						{
							siRand = (rand()%7 + 3)*1000;
						}

						if( (TABS( pclClient->CurrentClock - lastWaitAniChanged ) > siRand) && aniref >= 0 )
						{
							lastWaitAniChanged = pclClient->CurrentClock;						dwLastMakeCharNameFrame = pclClient->GetFrame();

							WaitType = ANITYPE_WAIT1;
							SetAnimation(WaitType);
							DoAnimationDelay();
						}
					}
					else
					{
						WaitType = ANITYPE_WAIT0;
						SetAnimation(WaitType);
						DoAnimationDelay();
					}
				}
			}
		}
	}

	// ��縦 ȥ�� �����δ�. 
	if((SI32)pclClient->GetFrame() % 400 == (GetID() % 400))
	{
		if ( pclKI->pclWarChatInfo )
		{
			if (  GetMapIndex() != pclKI->pclWarChatInfo->siMapindex )
			{
				TCHAR* ptext = NULL ;

				ptext = pclKI->GetWarRandChatWinText(GetMapIndex());

				if(ptext)
				{
					cltClient* pclclient = (cltClient*)pclClient;
					pclDrawChat->Set(pclclient->pclDrawChatSurface, ptext, false, NPC_CHATTING);
				}
			}
			else
			{
				TCHAR* ptext = pclKI->GetRandChatText() ;

				if(ptext)
				{
					cltClient* pclclient = (cltClient*)pclClient;
					pclDrawChat->Set(pclclient->pclDrawChatSurface, ptext, false, NPC_CHATTING);
				}
			}
		}
		else
		{
			TCHAR* ptext = pclKI->GetRandChatText() ;

			if(ptext)
			{
				cltClient* pclclient = (cltClient*)pclClient;
				pclDrawChat->Set(pclclient->pclDrawChatSurface, ptext, false, NPC_CHATTING);
			}
		}
	}

	// ���� ĳ���Ͱ� �ִ� ���, 
	if(siHostID)
	{
		if(pclCM->IsAlive(siHostID))
		{
			cltCharClient* pclchar = (cltCharClient*)pclCM->CR[siHostID];
			SI32 length = max( TABS(pclchar->GetX() - GetX()) , TABS(pclchar->GetY() - GetY()) );

			if(length >= 3)
			{
				SI32 xvary = 1 - (rand() % 3);
				SI32 yvary = 1 - (rand() % 3);

				OrderMove(GetID(), pclchar->GetX() + xvary, pclchar->GetY() + yvary, BY_COMPUTER);
			}
		}
	}

	// �����ÿ��� �ٻܰ� ����.
	bBusySwitch = false;


	return TRUE;
}

void cltCharClient::GetBottomPoint(cltPos* pclpos)
{
	pclpos->siX = siCenterX;
	pclpos->siY = siCenterY + (RealImageEndY-RealImageStartY)/2;
}

// ���� ��ġ�� ����Ѵ�. 
void cltCharClient::CalculateRealXY()
{

	int   FlyVibrateData[MAX_FLY_VIBRATE] = {0, 1, 2, 3, 4, 3, 2, 1};

	SHORT x=GetX();
	SHORT y=GetY();

	//��鸲�� �ִ´�. 
	if(VibrateSwitch==TRUE)
	{
		VibrateY=FlyVibrateData[((pclClient->GetFrame() + siID)/4)%MAX_FLY_VIBRATE];
	}

	SI32 mapcenterx = 0, mapcentery = 0;
	pclMap->GetXYDotFromXYCord(GetX(), GetY(), mapcenterx, mapcentery);

	// ĳ������ �߽��� ���Ѵ�
	siCenterX=mapcenterx + siRX;

	SI32 mapcenterx2 = 0, mapcentery2 = 0;
	pclMap->GetXYDotFromXYCord(x, y, mapcenterx2, mapcentery2);

	siCenterY=mapcentery+5 + siRY-(RealImageEndY-RealImageStartY)/2;

	RealRect.left=  mapcenterx2 + siRX-(RealImageEndX-RealImageStartX)/2;
	RealRect.right= RealRect.left + (RealImageEndX-RealImageStartX);
	RealRect.bottom=mapcentery2 + siRY+20;//pclKI->clKIDrawInfo.siBottomIndent;
	RealRect.top=   RealRect.bottom-(RealImageEndY-RealImageStartY); 
}

void cltCharClient::NewSelectedAction()
{
	if(bNewSelectedSwitch == true)
	{
		//if(pclClient->GetFrame() % 2 ==0)
		if((pclClient->CurrentClock / 50) % 2 ==0)
		{
			if(NewSelectedDelay>0)
			{
				NewSelectedDelay--;
			}
			else
			{
				SetNewSelectedSwitch(false);
			}
		}
	}


	if(bMouseOverSwitch == true )
	{
		//if(pclClient->GetFrame() % 2 ==0)
		if((pclClient->CurrentClock / 50) % 2 ==0)
		{
			if(MouseOverDelay>0)
			{
				MouseOverDelay--;					
			}
			else
			{
				SetMouseOverSwitch(false);
			}
		}		
	}

}

void cltCharClient::SetNewSelectedSwitch(bool mode)
{

	switch(mode)
	{
	case true:
		bNewSelectedSwitch	=	true;
		NewSelectedDelay	=	NEW_SELECTED_DELAY;
		break;
	case false:
		bNewSelectedSwitch	=	false;
		break;
	}
}

void cltCharClient::SetMouseOverSwitch(bool mode)
{	
	switch(mode)
	{
	case true:
		{
			if( bNewSelectedSwitch == false ) // �����̴� ���� �ƴ϶��
			{
				bMouseOverSwitch = true;	// ��� �㿸�� �����Բ� 
				MouseOverDelay = MOUSE_OVER_DELAY;
			}
			else
				bMouseOverSwitch = false;
		}
		break;
	case false:
		{
			bMouseOverSwitch = false;
		}
		break;
	}
}

// � �� ���� obj ���� �ִ��� ���θ� �˷��ִ� �Լ� (���� ��ǥ)
// length: �߽ɰ��� �Ÿ� 
BOOL cltCharClient::IsAbsPtInObj(SHORT x, SHORT y, SHORT& length)
{

	if(RealRect.left <x && x<RealRect.right
		&& RealRect.top  <y && y<RealRect.bottom)
	{
		length=max(TABS(siCenterX-x),TABS(siCenterY-y));
		return TRUE;
	}

	return FALSE;
}



///----------------------------------
// Session ������ ȣ�� �Լ�. 
//-----------------------------------
void cltCharClient::Init()
{
	ITZPerson::Init();

	//pclClient->MakeSimpleChar(m_uiCharID, 0);
}

// Logout�� ȣ��Ǵ� �Լ�. 
void cltCharClient::Close()
{
	ITZPerson::Close();

	//cyj ���� �������� ĳ�� ���� ������ ����
	//pclClient->pclCM->DeleteChar( GetID() );
}
//----------------------------
// Ŭ���̾�Ʈ ĳ������ ����. 
//----------------------------
void cltCharClient::CharClientAction()
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( siPVPWaitTime > 0 )
	{
		if (TABS(pclClient->CurrentClock - siPVPWaitTime) >= 7000)// �������� 6�ʰ� ������ 
		{
			// ��ٸ��� �ð��� �� �������Ƿ� ��ŸƮ ������.
			cltGameMsgRequest_PVP_Request clinfo ( START_PVP , pclclient->pclCM->CR[1]->pclCI->GetPersonID() );
			cltMsg clMsg(GAMEMSG_REQUEST_PVP_FILED, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			siPVPWaitTime = 0	;
		}
	}
	if ( siPVPTime > 0 )
	{
		if (TABS(pclClient->CurrentClock - siPVPTime) >= (1000*60)*3)// 3���� ������ Draw
		{	
			if ( pclclient->pclCM->CR[1]->GetPVP_LeagueEnemyPersonID() <= 0 ) // PVP���װ� �ƴ� ���� Ŭ���̾�Ʈ���� ������
			{
				cltGameMsgRequest_PVP_Request clinfo ( DRAW_PVP , pclclient->pclCM->CR[1]->siEnemUnique );
				cltMsg clMsg(GAMEMSG_REQUEST_PVP_FILED, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				siPVPTime = 0	;
			}
		}
	}
	if ( siRacoonDodgeWaitTime > 0 )//Switch_10MonthEvent_RacoonDodge
	{
		if (TABS(pclClient->CurrentClock - siRacoonDodgeWaitTime) >= 7000)// �������� 6�ʰ� ������ 
		{
			// ��ٸ��� �ð��� �� �������Ƿ� ��ŸƮ ������.
			cltGameMsgRequest_RacoonDodgeEveent_StartGame clinfo (pclclient->pclCM->CR[1]->pclCI->GetPersonID() );
			cltMsg clMsg(GAMEMSG_REQUEST_RACOONDODGE_EVENT_OVER5SECOND_START, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			siRacoonDodgeWaitTime = 0	;
		}
	}
	// Regenertaion ���� ó��
	CharRegenerationAction();

	// ���� ���� ó��. 
	CharCutAction();

	// �ź� ǥ�� ó��. 
	CharBossAction();

	if( pclLevelUp )
	{
		pclLevelUp->Action();
	}

	if( pclHeartEffect )
	{
		pclHeartEffect->Action( bHeartEffectSwitch );
	}

	if( pclFourLeafEffect )
	{
		pclFourLeafEffect->Action( bFourLeafSwitch );
	}

	// ��� ���� ���� - by LEEKH 2007.11.13
	SI32 siCushion = 0;

	if(GetCurrentOrder() == ORDER_SITDOWN)
		siCushion = siCushionUnique;
	else
		siCushion = 0;

	//KHY - 1109 - ��í����- �������漮�߰�
	if( pclCushionEffect )
	{
		pclCushionEffect->Action( siCushion, GetKind() , siDirection );
	}
	if( pclCushionCatEffect )
	{
		pclCushionCatEffect->Action( siCushion, GetKind() );
	}
	/*
	if( pclCushionEffect )
	{	
	pclCushionEffect->Action( 
	(GetCurrentOrder() == ORDER_SITDOWN)
	&& bHaveCushion
	, GetKind() , siDirection );
	}
	if( pclCushionCatEffect )
	{
	pclCushionCatEffect->Action( (GetCurrentOrder() == ORDER_SITDOWN)
	&& bHaveCushion
	, GetKind() );
	}
	*/
	if( pclMVPEffect )
	{
		pclMVPEffect->Action();
	}

	if( pclEnchantEff)
	{
		pclEnchantEff->Action();
	}

	if( pclQuestEff)
	{
		pclQuestEff->Action();
	}

	if( pclSkillLevelUp )
	{
		pclSkillLevelUp->Action();
	}

	if( pclEmoticonEff )
	{
		pclEmoticonEff->Action();
	}

	if( m_pclValentineEmoticonEff )
	{
		m_pclValentineEmoticonEff->Action();
	}

	if(pclExpCounter)
	{
		pclExpCounter->Action();
	}

	if(pclHealCounter)
	{
		pclHealCounter->Action();
	}

	if ( pclJim )
	{
		pclJim->Action();
	}

	if(pclDrawChat)
	{
		pclDrawChat->Action();

		if ( bPersonalShopSwitch == true && pclDrawChat->IsDrawStatus() == false )
		{
			if(bPremiumPersonalShop == true)
			{				
				pclDrawChat->Set(((cltClient*)pclClient)->pclDrawChatSurface, szPersonalShopText, true, PERSONALSHOP_BANNER_PREMIUM, siShopMode,szPersonalShopTitle);
			}
			else
			{
				pclDrawChat->Set(((cltClient*)pclClient)->pclDrawChatSurface, szPersonalShopText, true, PERSONALSHOP_BANNER, siShopMode);
			}
		}
		else if( (bIsElectionStump == true) && (pclDrawChat->IsDrawStatus() == false) )
		{
			pclDrawChat->Set(((cltClient*)pclClient)->pclDrawChatSurface, szMaintenance, true, ELECTIONSTUMP, PSHOP_MODE_SELL, szCandidate);
		}
		else if ( bRepairShopSwitch == true )
		{
		}

	}


	if ( pclCriticalEffect )
	{
		pclCriticalEffect->Action();
	}

	// ���콺�� ĳ���͸� �������� ����� ��ġ.
	NewSelectedAction();

	// ���� �����Ѵٸ� ���� �뵿�ϰ� �Ѵ�. 
	if(IsPC(GetCharUnique()))
	{
		m_clMagicBufMgr.DecFrame( 0 );

		cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

		// �������� ��ȿ�ϴٸ�, 
		if(pclCM->IsValidID(siSlaveID) == false)
		{

			// ���� Ÿ�� �ִ� ���� �ƴϾ�� �Ѵ�. 
			//			if(pclCI->clHorseInfo.siCurrentHorseIndex != 0)
			if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false) // siCurrentHorseRIDEHORSE == false
			{
				if(pclhorse != NULL && pclhorse->siHorseUnique > 0 && pclhorse->siHorseUnique < MAX_HORSE_TYPE_INFO)
				{
					SI32 id		= pclCM->pclIDManager->GetID(0);
					SI32 charunique		= 0;

					// horseunique�� ������ ������ kind�� ã�´�. 
					SI32 horsekind = pclClient->pclHorseManager->pclHorseTypeInfo[pclhorse->siHorseUnique]->siKind;

					// ���� InnerStatus �� �ʿ����.
					cltInnerStatusInfo	clEmptyInnerStatus;

					cltBufInfo clBufInfo;
					clBufInfo.Init();
					cltMakeCharInfo clinfo(horsekind, charunique, 1, 0, GetX(), GetY(), GetMapIndex(),
						0, 
						0, 
						false, 
						false,
						false, 
						false, 
						false,
						false,
						false,
						false,
						0, 
						NULL, 
						pclCI->clHorseInfo.siCurrentShowHorse, 
						0,
						0, 0, 0, 							
						0, 
						0, 0, 
						NULL,0,0,
						NULL, 
						NULL, 
						&clEmptyInnerStatus,
						false, 
						false,
						0,
						false,
						0,
						NULL,
						NULL,
						pclCI->clHorseInfo.siCurrentHorseRIDEHORSE,
						0,
						false,
						false,	// [�߰� : Ȳ���� 2008. 1. 14 => �ڽ��� ��尡 �ְ��ΰ�.]
						false,
						false,
						0,
						0,
						NULL,
						false
						,NULL
						,0
						,0
						,0
						,0
						,0
						,0
						,0
						,0
						,0
						,0
						,false
						,&clBufInfo
						);
					siSlaveID = pclClient->SetChar(id, &clinfo);
					if(pclCM->IsValidID(siSlaveID))
					{
						cltCharClient* pclchar = (cltCharClient*)pclCM->CR[ siSlaveID ] ;
						pclchar->siHostID = GetID();
					}

				}
			}
		}
		// �������� ��ȿ�ϴٸ�, 
		else
		{
			cltCharClient* pclchar = NULL;
			if( pclCM->IsValidID(siSlaveID) )
			{
				pclchar = (cltCharClient*)pclCM->CR[ siSlaveID ];
			}
			if(pclchar)
			{
				// �������� ������ �ϴ��� ����, 
				bool bdelhorseswitch = false;

				//�� ���� Ÿ�� �ִ� ���̶�� �������� �����Ѵ�. 
				if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE)
				{
					bdelhorseswitch = true;
				}
				// ���� ��������̶�� �����Ѵ�. 
				if(pclhorse->siHorseUnique == 0)
				{
					bdelhorseswitch = true;
				}

				if(bdelhorseswitch)
				{
					if(pclchar->siHostID == GetID())
					{
						pclCM->DeleteChar(siSlaveID);
						siSlaveID = 0;
					}
				}

				// �������� ȣ��Ʈ�� �� ���̵� ��ġ���� ������ �������� �������� �ƴϴ�. 
				if(pclchar->siHostID != GetID())
				{
					siSlaveID = 0;
				}
			}
		}

		//-----------------------------------
		// Ư�� �ӹ� ���� 
		//-----------------------------------
		if(GetID() == 1 && (pclClient->GetFrame() % 100) == 0)
		{
			SI32 questtype	= QUEST_TYPE_SPECIAL;
			SI32 questunique = pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique;
			if(questunique)
			{
				cltQuestInfoCommon* pclinfo = &pclCI->clQuestInfo.clSpecialQuestInfo;
				if(pclinfo)
				{
					// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
					if(IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
					{
						cltGameMsgRequest_QuestGoing clInfo(questtype, questunique, QUEST_STEP_CLEAR);
						cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}

			questtype	= QUEST_TYPE_NAMING;
			questunique = pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique;
			if(questunique)
			{
				cltQuestInfoCommon* pclinfo = &pclCI->clQuestInfo.clNamingQuestInfo;
				if(pclinfo)
				{
					// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
					if(IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
					{
						cltGameMsgRequest_QuestGoing clInfo(questtype, questunique, QUEST_STEP_CLEAR);
						cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
			questtype	= QUEST_TYPE_HAPPYBEAN;
			questunique = pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique;
			if(questunique)
			{
				cltQuestInfoCommon* pclinfo = &pclCI->clQuestInfo.clHappyBeanQuestInfo;
				if(pclinfo)
				{
					// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
					if(IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
					{
						cltGameMsgRequest_QuestGoing clInfo(questtype, questunique, QUEST_STEP_CLEAR);
						cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}

			// �̼� ����Ʈ �߰� - by LEEKH 2008-09-18
			questtype	= QUEST_TYPE_MISSION1;
			questunique = pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique;
			if(questunique)
			{
				cltQuestInfoCommon* pclinfo = &pclCI->clQuestInfo.clMissionQuestInfo;
				if(pclinfo)
				{
					// ����Ʈ �Ϸ� ������ ������Ű���� Ȯ���Ѵ�. 
					if(IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
					{
						cltGameMsgRequest_QuestGoing clInfo(questtype, questunique, QUEST_STEP_CLEAR);
						cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
						SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}

		// ���� �˻�
		if ( pclCM->CR[1]->GetCurrentOrder() == ORDER_FARM )
		{
			CNFarmingDlg* FarmDlg = (CNFarmingDlg*)pclclient->m_pDialog[NFARMING_DLG] ;
			if ( FarmDlg == NULL )							
			{        
				pclclient->CreateInterface( NFARMING_DLG );
			}
		}
	}

	if( bMyShopStart )
	{
		SI64 siTotalPrice = 0;
		SI32 i;
		for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
		{
			if(clMyShopData.m_clItem[i].siUnique > 0)
				siTotalPrice += (clMyShopData.m_clItem[i].siItemNum * (SI64)clMyShopData.m_siPrice[i]);
		}

		// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
		SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

		if ( BuyerMoney  < siTotalPrice )
		{
			TCHAR* pTitle = GetTxtFromMgr(5118);
			TCHAR* pText = GetTxtFromMgr(5119);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);

			cltGameMsgRequest_StopPersonalShop clshopdata( pclClient->pclCM->CR[1]->GetCharUnique());
			cltMsg clMsg( GAMEMSG_REQUEST_STOPPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
			cltClient *pclclient = ( cltClient * )pclClient;
			pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

			if(pclclient->m_pDialog[ NPERSONALSHOP_DLG ])			
				pclclient->m_pDialog[ NPERSONALSHOP_DLG ]->DeleteDialog();

			clMyShopData.Init();
			bMyShopStart = FALSE;
		}
	}

	// [����] 2009.09.02 �����̾� ���� ���� ������ Ȱ��ȭ ���¶�� ��ȯ���� ���¸� ���� ���·� �ٲ��ּ��� �Ѵ�.
	SI32 siSummonID = GetSummonID();
	cltCharClient *pclSummon = pclCM->GetCharClient(siSummonID);
	if( NULL != pclSummon)
	{
		if( pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum)
		{
			pclSummon->bNoFirstAttackSwitch = true;
		}
	}
}



// ���� ź��. 
bool cltCharClient::RideHorse()
{
	if(cltCharCommon::RideHorse()== false)return false;

	// Ÿ�� �� ���� ������ ���� �ʿ��� �̹����� �ε��Ѵ�. 
	cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclhorse == NULL)			return false;

	// PCK : �������� �ػ����� ������ Ż���� �����ϰ� �ϳ��� �̹����� �ٲ��. (09.08.11)
	if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM_HORSE))
	{
		SI32 siTransFormHorseUnique = pclCI->clBI.clBufInfo.GetBufPercent(BUF_TRANSFORM_HORSE);
		ChangeHorseCode(siTransFormHorseUnique);
	}
	else
	{
		ChangeHorseCode( pclhorse->siHorseUnique );
	}

	return true;
}

// ������ ������.
bool cltCharClient::UnrideHorse()
{
	if(cltCharCommon::UnrideHorse()== false)return false;

	// Ÿ�� �� ���� ������ ���� �ʿ��� �̹����� �ε��Ѵ�.

	ChangeHorseCode( 0 );

	return true;
}

// ������ �ʿ��� ��ġ�� ���Ѵ�. 
void cltCharClient::DeleteOperation()
{
	// �����ڸ� �����Ѵ�. 
	DeleteSlave();
}

// �����ڸ� �����Ѵ�. 
void cltCharClient::DeleteSlave()
{

	// ������ ĳ���͸� �����Ѵ�. 
	if(siSlaveID)
	{
		if(pclCM->IsAlive( siSlaveID )  == TRUE)
		{
			pclCM->DeleteChar( siSlaveID );
			siSlaveID	= 0;
		}
	}
}

bool cltCharClient::AfterCharAction()
{
	// ��� �غ� �Ǿ��ִ�.
	SetDrawReadySwitch(true);

	return false;
}


// �������� ���� ȭ�鿡 ǥ���ϰų� ǥ������ �ʴ´�. 
void cltCharClient::SetJimShow()
{
	if(pclJim == NULL)return ;

	if(clJim.siJimHostCharUnique)
	{
		bool bhostjimswitch = false;

		SI32 jimcharunique = clJim.siJimHostCharUnique;
		if(pclClient->IsUser(jimcharunique))
		{
			bhostjimswitch = true;
		}

		SI32 id = pclCM->GetIDFromCharUnique(jimcharunique);
		if(pclCM->IsValidID(id))
		{
			if(pclCM->CR[id]->GetSummonParentID() == 1)
			{
				bhostjimswitch = true;
			}
		}

		//cyh ��Ƽ���϶��� ��ǥ�� �ȳ������� ����
		cltClient *pclclient = (cltClient*)pclClient;
		if(pclclient->m_pDialog[ NPARTY_DLG ])
			if (((CNPartyDlg*)pclclient->m_pDialog[ NPARTY_DLG ])->IsPartyUser(jimcharunique))
				bhostjimswitch = true;

		if(bhostjimswitch == true)
		{
			pclJim->Set(true, true);
		}
		else
		{
			pclJim->Set(true, false);
		}
	}
	else
	{
		pclJim->Set(false, true);
	}

}


// ĳ���Ͱ� �����ϰ� �ִ� ����Ʈ�� �����Ͽ� �����Ų��. 
void cltCharClient::DoQuestCheckAndAction(SI32 questclearcond)
{
	SI16 questtype, questunique, para1, para2;
	if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
	{
		cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
		cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
	}


}

void FogOp(cltMapClient* pclmap, SI32 index, SI32 charx, SI32 chary);

// ���� ó���� �Ѵ�. 
void cltCharClient::FogAction()
{
	cltClient* pclclient = (cltClient*)pclClient;

	SI32 charunique = GetCharUnique() ;

	BOOL TempCheck = FALSE;
	if(pclclient->m_pDialog[ NPARTY_DLG ])
		TempCheck = ((CNPartyDlg*)pclclient->m_pDialog[ NPARTY_DLG ])->IsPartyUser(charunique);

	if ( GetID() == 1 || GetID() == pclCM->CR[1]->GetSummonID() || TempCheck == TRUE )
	{
		cltMapClient* pclmap = (cltMapClient*)pclMap;

		SI32 fogindex = 0;
		FogOp(pclmap, fogindex, GetX(), GetY());
	}
}


void cltCharClient::MakeRankMarkEncBuffer()
{
	if ( m_RankMarkImgEncBuffer )
	{
		delete [] m_RankMarkImgEncBuffer;
		m_RankMarkImgEncBuffer = NULL;
	}

	SI32 NpcKindKey = -1;


	if ( pclKI->clKIDrawInfo.siHeadNameFont > -1 )
	{
		NpcKindKey = pclKI->clKIDrawInfo.siHeadNameFont;   //npc ��ȣ

	}
	else if( clIdentity.siIdentity == IDENTITY_VILLAGEGOD )
	{
		NpcKindKey = 43;
	}

	//���Ⱑ �´µ� ��ȯ�� flag
	else if(clIdentity.siIdentity ==IDENTITY_PERSON_SUMMON )
	{
		//if (!pclKI->bSummonMall )
		NpcKindKey = 44;
		//else
		//	NpcKindKey = 56;

	}
	else
	{
		SI32 ItemUnique = 0;

		if ( pclCI->clCharItem.clItem[ PERSONITEM_HAT ].siUnique == 0 )
		{
			ItemUnique = clPB.clShapeEquip.clHelmet.uiUnique;
		}
		else
		{
			ItemUnique = pclCI->clCharItem.clItem[ PERSONITEM_HAT ].siUnique;
		}


		if ( ItemUnique )
		{
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( ItemUnique );

			if ( Ref > 0 )
			{
				switch( pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank )
				{
				case 1:
					NpcKindKey = 0;
					break;
				case 4:
					NpcKindKey = 42;
					break;
				case 5:
					NpcKindKey = 54;
					break;
				case 6:
					NpcKindKey = 57;
					break;
				case 7:
					NpcKindKey = 62;
					break;
				default:
					NpcKindKey = -1;
					break;
				}
			}
		}
		else
		{
			NpcKindKey = -1;
		}

		// [����] ���ڴ� ���� (2008. 06 .05)
		if ( CONST_JOURNALIST_HAT_ITEMUNIQUE == ItemUnique )
		{
			NpcKindKey = 0;
		}

	}	


	if ( NpcKindKey < 0 )
	{
		return;
	}




	//NPCMgr();    //npc �� �ε����� �̹��� ������ �ҷ��´�.

	cltClient* pclclient = (cltClient*)pclClient;

	m_RankMarkEncHres = 0;
	m_RankMarkEncVres = 0;
	int flag_key=pclclient->m_NPCImgIndex[NpcKindKey]-1;        //npc ���� �÷��� (0, 1, 2)


	LPDIRECTDRAWSURFACE7 lpSurface = NULL;
	//cltTSpr RankMarkImage;
	TSpr RankMarkImage;

	if ( g_graphics.CreateSurface16( &lpSurface, MAX_RANKMARK_WIDTH, MAX_RANKMARK_HEIGHT, TRUE, RGB16_TRANS ) == FALSE )
	{
		MsgBox( TEXT("CreateOffScreen Error, MakeRankMarkEncBuffer()"), TEXT("sdfsd") );
	}

	// �޸� �����ڵ� - by LEEKH
	if(lpSurface == NULL)				return;

	g_graphics.ClearSurface( lpSurface, RGB16_TRANS );


	//-------------------------------------------------
	// ��� �̹��� ��� �κ�
	//-------------------------------------------------


	TCHAR szName[256]=TEXT(" ");
	StringCchCopy(szName, 256, pclclient->m_NPCName[NpcKindKey]);

	//if( lpSurface->GetDC(&hdc) == DD_OK)

	SIZE size = { 0, 0 };
	HDC hdc;

	//  npc �̸��� ���ǽ��� ����. 
	if(lpSurface->GetDC(&hdc)== DD_OK)
	{
		HFONT hFont;
		//if( pclClient->IsWhereServiceArea( ConstSwitch_NONATIALIASED_QUALITY ) ){
		if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
			hFont = CreateFont( 11, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, pclclient->m_pInterfaceMgr->GetFontKind() );
		}
		else {
			hFont = CreateFont( 11, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, 0, 0, pclclient->m_pInterfaceMgr->GetFontKind() );
		}


		HFONT hOldFont = NULL;

		hOldFont = (HFONT)SelectObject( hdc, hFont );

		GetTextExtentPoint32(hdc, szName, _tcslen(szName), &size);

		SelectObject( hdc, hOldFont );

		if ( hFont )
		{
			DeleteObject( hFont );
			hFont = NULL;
		}

		lpSurface->ReleaseDC( hdc );
	}

	if(size.cx && size.cy )//�̸����� FLAG
	{
		// npc �̹����� ���ۿ� �ִ´�. 


		GP.LoadSprFromFile( TEXT("NInterface/Image/Image_48x18_00_000.SPR")  ,&RankMarkImage );	//�׸������� �ҷ� ����

		if (RankMarkImage.GetXSize() == 0)//�׸����� ����� 0 �̸� ����
			return;
		SI32 xnum = size.cx / RankMarkImage.GetXSize()  +  ( ( size.cx % RankMarkImage.GetXSize() ) ? 1:0 );
		m_RankMarkEncHres	= ( xnum + 2 ) * RankMarkImage.GetXSize();
		m_RankMarkEncVres	= RankMarkImage.GetYSize();

		m_RankMarkImgEncBuffer = new RGB16[ MAX_RANKMARK_WIDTH * MAX_RANKMARK_HEIGHT * 2 ];


		if( GP.LockSurface( lpSurface ) )
		{
			GP.PutSpr( &RankMarkImage, 0, 0, 0 + (flag_key*3) );

			for(SI32 i =0 ;i < xnum  ;i++)
			{
				GP.PutSpr( &RankMarkImage, RankMarkImage.GetXSize() +i * RankMarkImage.GetXSize(), 0 , ( 1+(flag_key*3) ));
			}

			GP.PutSpr( &RankMarkImage, RankMarkImage.GetXSize() + xnum * RankMarkImage.GetXSize(), 0 , ( 2+(flag_key*3) ));

			GP.UnlockSurface( lpSurface );
		}				

		//-------------------------------------------------
		// ��Ʈ �̹��� ��� �κ�
		//-------------------------------------------------

		// npc �̸��� ����Ѵ�. 
		if( lpSurface->GetDC(&hdc)== DD_OK)//flag �� ���� ���� �ø���.

		{
			HFONT hFont;

			if ( pclclient->siServiceArea == ConstServiceArea_Japan)
			{
				//if( pclClient->IsWhereServiceArea( ConstSwitch_NONATIALIASED_QUALITY ) ){
				if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
					hFont = CreateFont( 11, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("����") );
				}
				else {
					hFont = CreateFont( 11, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("����") );
				}


			}
			else
			{
				//if( pclClient->IsWhereServiceArea( ConstSwitch_NONATIALIASED_QUALITY ) ){
				if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
					hFont = CreateFont( 13, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("Tahoma") );
				}
				else {
					hFont = CreateFont( 13, 0, 0, 0, 0, 0, 0, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("Tahoma") );
				}

			}

			HFONT hOldFont = NULL;

			hOldFont = (HFONT)SelectObject( hdc, hFont );

			SetTextColor(hdc,COLOR_DIALOG_BLACK);


			SetBkMode(hdc, TRANSPARENT );
			//SetFont();

			TextOut(
				hdc, 
				RankMarkImage.GetXSize(), 
				( m_RankMarkEncVres - size.cy ) / 2 + 2, 
				szName, lstrlen(szName) );

			SelectObject( hdc, hOldFont );

			if ( hFont )
			{
				DeleteObject( hFont );
				hFont = NULL;
			}

			lpSurface->ReleaseDC( hdc );
		}


		if ( GP.LockSurface( lpSurface ) == TRUE )
		{
			int size;
			// �޸� ���� �ڵ� �߰�
			if ( m_RankMarkEncHres > MAX_RANKMARK_WIDTH )		m_RankMarkEncHres = MAX_RANKMARK_WIDTH;
			if ( m_RankMarkEncVres > MAX_RANKMARK_HEIGHT )		m_RankMarkEncVres = MAX_RANKMARK_HEIGHT;

			if(m_RankMarkImgEncBuffer)
			{
				g_graphics.EncodeXpr( (RGB16*)m_RankMarkImgEncBuffer, 
					//MAX_RANKMARK_WIDTH,
					//MAX_RANKMARK_HEIGHT,
					m_RankMarkEncHres, m_RankMarkEncVres,
					RGB16_TRANS,
					&size );
			}

			GP.UnlockSurface( lpSurface );
		}
	}

	if( lpSurface )
	{
		lpSurface->Release();
		lpSurface = NULL;
	}



	return;
}



void cltCharClient::NPCMgr( )
{
	// �Ⱦ��ϴ�!! ���� ��� cltClient�� �̵�.

	//TCHAR buffer[1024] = TEXT("");
	//FILE* fp= NULL;

	//if( pclClient->siServiceArea ==  ConstServiceArea_Korea )	// �ѱ�
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrK.txt"), TEXT("rt"));
	//}
	//else if( pclClient->siServiceArea ==  ConstServiceArea_English )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrE.txt"), TEXT("rt"));
	//}
	//else if(pclClient->siServiceArea ==  ConstServiceArea_China )
	//{
	//       fp = _tfopen(TEXT("TextMgr\\NPCMgrC.txt"), TEXT("rt"));
	//}
	//else if(pclClient->siServiceArea ==  ConstServiceArea_Japan )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrJ.txt"), TEXT("rt"));
	//}
	//else if( pclClient->siServiceArea ==  ConstServiceArea_Taiwan )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrT.txt"), TEXT("rt"));
	//}
	//else if( pclClient->siServiceArea ==  ConstServiceArea_USA )
	//{
	//	fp = _tfopen(TEXT("TextMgr\\NPCMgrU.txt"), TEXT("rt"));
	//}


	//if(fp == NULL)
	//{
	//	MsgBox(TEXT("fileError"), TEXT("not NPCMgrtextFile"));
	//	return ;
	//}

	//// ���Ǿ� �ؽ�Ʈ�� 4���� �ּ����� �����Ѵ�.
	//for(SI32 i = 0;i < 4;i++)
	//	_fgetts(buffer, 1024, fp);

	//for ( i = 0 ; i < MAX_NPCKINDFORRANKMARK ; i ++ )
	//{
	//	StringCchCopy(m_NPCName[i], 64, TEXT(""));
	//	m_NPCImgIndex[i]=0;		
	//}


	//i = 0 ;

	//while( _fgetts(buffer, 1024, fp) != NULL)
	//{
	//	if ( i >= MAX_NPCKINDFORRANKMARK ) break ;
	//	
	//	TCHAR * szindex;
	//	TCHAR * szname;
	//	TCHAR * szkind;

	//	szname = _tcstok(buffer, TEXT("\t"));
	//	szkind = _tcstok(NULL,TEXT("\r\n"));

	//	if ( !szname || !szkind ) break ;
	//	{

	//		szindex= _tcstok(szname,TEXT(":"));
	//		szname =_tcstok(NULL,TEXT(" ") );
	//		StringCchCopy(m_NPCName[i], 64, szname);
	//	}
	//	m_NPCImgIndex[i] = _tstoi(szkind);
	//	i ++ ;
	//}

	//fclose(fp);	
}

SI32 cltCharClient::GetRX() const 
{
	return siRX;
}

SI32 cltCharClient::GetRY() const 
{
	return siRY;
}

DWORD cltCharClient::GetDrawFrame()
{
	return dwDrawFrame;
}

void cltCharClient::SetDrawReadySwitch(bool mode)
{
	bDrawReadySwitch = mode;
}

//------------------------
// �ǰ� �̹��� ���� 
//-------------------------
void cltCharClient::SetHitSwitch(bool mode)
{
	cltCharCommon::SetHitSwitch(mode);

	// �ǰ� �̹��� ����ϰ� �ϱ�.
	SetHitDrawSwitch(mode);
}


void cltCharClient::SetHitDrawSwitch(bool mode)
{
	bHitDrawSwitch = mode;
}

//--------------------------------
// �����, ��� ���� ó��. ( �ٴڿ� �� �׸��� �� )
//--------------------------------
void cltCharClient::CharBossAction()
{
	if( pclBoss )
	{
		pclBoss->Action();
	}
}


//--------------------------------
// Regeneration ���� ó��. 
//--------------------------------
void cltCharClient::CharRegenerationAction()
{
	if(pclRegeneration)
	{
		pclRegeneration->Action();
	}
}

void cltCharClient::SetCharRegeneration()
{
	if(pclRegeneration)
	{
		pclRegeneration->Set();
	}
}

//--------------------------------
// ���� ���� ó��. 
//--------------------------------
void cltCharClient::CharCutAction()
{
	if(pclCharCut)
	{
		pclCharCut->Action();
	}
}

void cltCharClient::SetCharCut(SI32 mode)
{
	if(pclCharCut)
	{
		pclCharCut->SetAction(mode);
	}
}

//--------------------------------
// ������ ���� ó��. 
//--------------------------------
void cltCharClient::SetLevelUp()
{
	if( pclLevelUp )
	{
		pclLevelUp->Set();
	}

	// ĳ���͸� ������ �������� ����

	bLevelUpDrawSwitch = true;
	clAniInfo.SetAniStep(0);

}

//--------------------------------
// MVP ����Ʈ ���� ó��
//--------------------------------
void cltCharClient::SetMVPEffect()
{
	if( pclMVPEffect )
	{
		pclMVPEffect->Set();
	}
}


//--------------------------------
// Enchant ����Ʈ ���� ó��
//--------------------------------
void cltCharClient::SetEnchantEffect(SI08 AniType)
{
	if( pclEnchantEff )
	{	
		if( 0 == AniType)
		{
			pclEnchantEff->Set(ENCHANT_EFFECT_NONE);
		}

		if( KIND_HERO3 == GetKind() || KIND_HERO4 == GetKind()  )
		{
			if( ENCHANT_ANI_ARMOR == AniType)
			{
				pclEnchantEff->Set(ENCHANT_EFFECT_HERO_AMOR);
			}
			else if(ENCHANT_ANI_WEPONE == AniType)
			{
				pclEnchantEff->Set(ENCHANT_EFFECT_HERO_WEPONE);
			}
		}
		else if( KIND_HEROINE3 == GetKind() || KIND_HEROINE4 == GetKind() )
		{
			if( ENCHANT_ANI_ARMOR == AniType)
			{
				pclEnchantEff->Set(ENCHANT_EFFECT_HEROINE_AMOR);
			}
			else if(ENCHANT_ANI_WEPONE == AniType)
			{
				pclEnchantEff->Set(ENCHANT_EFFECT_HEROINE_WEPONE);
			}
		}
	}
}

//--------------------------------
// Quest ����Ʈ ���� ó��
//--------------------------------
void cltCharClient::SetQuestEffectReceive()
{
	if( pclQuestEff)
	{
		pclQuestEff->SetReceive();
	}
}

void cltCharClient::SetQuestEffectClear()
{
	if( pclQuestEff)
	{
		pclQuestEff->SetClear();
	}
}

//--------------------------------
// ��ų ������ ���� ó��. 
//--------------------------------
void cltCharClient::SetSkillLevelUp()
{
	if( pclSkillLevelUp )
	{
		pclSkillLevelUp->Set();
	}

	bLevelUpDrawSwitch = true;
	clAniInfo.SetAniStep(0);
}

//--------------------------------
// �̸�Ƽ�� ���� ó��
//--------------------------------
void cltCharClient::SetEmoticon( SI16 index )
{
	if ( pclEmoticonEff )
	{
		pclEmoticonEff->Set( index );
	}
}

//--------------------------------
// �߷�Ÿ�� �̸�Ƽ�� ���� ó��
//--------------------------------
void cltCharClient::SetValentineEmoticon( SI16 index )
{
	if ( m_pclValentineEmoticonEff )
	{
		m_pclValentineEmoticonEff->Set( index );
	}
}

bool cltCharClient::IsBlankInv(SI32 invnum,SI32 invmode)
{
	// ALL����̸� ��ü�� �ϳ� �ϳ� üũ�Ѵ�.
	if(invmode == INVMODE_ALL)
	{
		bool	ret;

		// ��� �κ��丮 �˻�
		ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_PERSON);
		if(ret)			return ret;
		// �� �κ��丮 �˻�
		if(HaveHorse() == true)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_HORSE);
			if(ret)			return ret;
		}
		// ����1 �κ��丮 �˻�
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique > 0)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_BAG);
			if(ret)			return ret;
		}
		// ����2 �κ��丮 �˻�
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique > 0)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_BAG_SUB);
			if(ret)			return ret;
		}

		// INVMODE_ALL ���� ���⼭ ������.
		return ret;
	}

	return pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager,invnum,invmode);
}
