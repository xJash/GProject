//---------------------------------
// 2003/10/16 ���°�
//---------------------------------
#ifndef _CHARClIENT_H
#define _CHARClIENT_H

#include "Char\CharCommon\Char-Common.h"

#define MAX_RANKMARK_WIDTH		600
#define MAX_RANKMARK_HEIGHT		500
#define MAX_NPCKINDFORRANKMARK  200

#define JEWELEFFECT_RARE1	0x0000001	// ��ǰ����Ʈ
#define JEWELEFFECT_RARE2	0x0000002	// ��ǰ����Ʈ
#define JEWELEFFECT_WATER1	0x0000004	// ��æƮ ����Ʈ ���Ӽ� 1�ܰ�
#define JEWELEFFECT_WATER2	0x0000008	// ��æƮ ����Ʈ ���Ӽ� 2�ܰ�
#define JEWELEFFECT_WATER3	0x0000010	// ��æƮ ����Ʈ ���Ӽ� 3�ܰ�
#define JEWELEFFECT_GROUND1	0x0000020	// ��æƮ ����Ʈ ���Ӽ� 1�ܰ�
#define JEWELEFFECT_GROUND2	0x0000040	// ��æƮ ����Ʈ ���Ӽ� 2�ܰ�
#define JEWELEFFECT_GROUND3	0x0000080	// ��æƮ ����Ʈ ���Ӽ� 3�ܰ�
#define JEWELEFFECT_WIND1	0x0000100	// ��æƮ ����Ʈ �ٶ��Ӽ� 1�ܰ�
#define JEWELEFFECT_WIND2	0x0000200	// ��æƮ ����Ʈ �ٶ��Ӽ� 2�ܰ�
#define JEWELEFFECT_WIND3	0x0000400	// ��æƮ ����Ʈ �ٶ��Ӽ� 3�ܰ�
#define JEWELEFFECT_FIRE1	0x0000800	// ��æƮ ����Ʈ �ҼӼ� 1�ܰ�
#define JEWELEFFECT_FIRE2	0x0001000	// ��æƮ ����Ʈ �ҼӼ� 2�ܰ�
#define JEWELEFFECT_FIRE3	0x0002000	// ��æƮ ����Ʈ �ҼӼ� 3�ܰ�

#define MARRIED_FULLDRESS	0x0004000	// ��ȥ���� ����Ʈ

#define	JEWELEFFECT_GRADE1	2
#define	JEWELEFFECT_GRADE2	7
#define	JEWELEFFECT_GRADE3	10

class CCCDSurfaceMgr;
class CDrawCharName;

class CCharJim;
class CCharPartyEmoticon;

class cltSystemNPC;
//------------------------------------------
// cltCharClient : Client�� 
//------------------------------------------
class cltCharClient	: public cltCharCommon
{
public:

	TSpr*			pImgSpr;
	SI32 			Font;                       													// ��µǴ� �׸��� ����� ��Ʈ ��ȣ 
	SI32			siEffectFont;				// Animation�� �־�� Ư�� ȿ��

	SI32			siShadowAni;				// �ִ϶� ���� ����� ����
	SI32			siShadowFont;				// ������ ��Ʈ

	BOOL 			DrawSwitch;																		// �׷��� ���ΰ� �����ΰ�?
	bool			bDrawReadySwitch;

	SI32 			RealImageXPercent, RealImageYPercent;  											// ���� �̹����� ���� ���η� �� �� %�� ���ϴ°�?
	DWORD			dwDrawFrame;         																// ���������� �׷��� ������ 

	DWORD			dwLastWaitFrame;

	SI16			TransMode;									// ĳ���͸� � ���� ������� �����Ѵ�.
	SI08			AlphaValue;									// ���İ�
	SI32			ImageXsize, ImageYsize;       				// �׼ǽÿ� ���Ǵ� �׸��� ���� ���� ������ 

	SI32 			VibrateY;                    													// ������鸲�� ���� 
	BOOL 			VibrateSwitch;               													// ���� ��鸲�� �ִ°�?

	// ĳ���� ���ð��� 
	bool			bMouseOverSwitch;
	bool 			bNewSelectedSwitch;
	SI32 			NewSelectedDelay;
	SI32			MouseOverDelay;
	SI32			DrawStartX, DrawStartY;      				// �׸��� �׷����� ���� ��ġ 

	//------------------------------
	// ����� ���� ��� �ڵ� 
	//------------------------------
	TCHAR		szHelmetCode[32];
	TCHAR		szArmourCode[32];
	TCHAR		szWeaponCode[32];
	TCHAR		szMantleCode[32];
	TCHAR		szHorseCode[32];	

	//-----------------------------
	// �̷� ��� ���� 
	//-----------------------------
	bool			bReverseSwitch;                				// ����� ���� ���ΰ�?

	//-----------------------------
	// ��ο� ����. 8
	//-----------------------------
	SI32 			DarkStep;

	//-----------------------------
	// �̹��� ������ ���� 
	//-----------------------------
	SI32	RealImageStartX, RealImageEndX;        											// ���� �̹����� ���ϴ� ���� ���� ��ǥ 
	SI32	RealImageStartY, RealImageEndY; 
	RECT	RealRect;

protected:
	//------------------------------
	// ������� 
	//------------------------------
	bool			bDyingOperationSwitch;
	bool			bGhostShowSwitch;

public:
	//-----------------------
	// �̵� ���� 
	//-----------------------
	SI32			siRX, siRY;  			// ��Ʈ ������ �̵��ϴ� ĳ������ ���� 
	SI32			MOX, MOY;  				// �̵��� ������ �Ǵ� ���� ��ǥ 
	SI32			MDX, MDY;  				// �̵��� ������ �Ǵ� ���� ��ǥ 


	//------------------------
	// �����, ��� ���� ó��. ( �ٴڿ� �� �׸��� �� )
	//-------------------------
	bool			bBoss;
	CBossEffect		*pclBoss;

	//------------------------
	// Regeneration ����
	//-------------------------
	bool	bRegeneration;					// ���� �Ǿ����� �˷���� �ϴ°�?
	CRegeneration	*pclRegeneration;	// ������ ��Ÿ���� Ŭ����

	//-----------------------------------------
	//�ڱ� ������ Ʈ���� �Ǽ��Ǿ� �ִ��� 
	//-----------------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_HIRED_EVENTNPC_NUM>		siEventNPCKind;
#else
	SI32	siEventNPCKind[MAX_HIRED_EVENTNPC_NUM];//������ �̺�Ʈ ���Ǿ��� Ȯ�� �ؼ� �̰͵� �迭�� Ȯ���غ���.
#endif

	//------------------------
	// ���λ��� ��� 
	//------------------------
	SI16			siShopMode;
	TCHAR			szPersonalShopText[MAX_PERSONAL_SHOP_TEXT_SIZE];
	TCHAR			szPersonalShopTitle[MAX_SHOP_TITLE_LENGTH];

	//------------------------
	// �ǰ� �̹��� ���� 
	//-------------------------
	 bool bHitDrawSwitch;					// �ǰݵǾ����� �˷���� �ϴ°�?
	 CCharCut*	pclCharCut;					// �������� ��Ÿ���� Ŭ����.


	//------------------------
	// ������ �̹��� ���� 
	//-------------------------
//	 bool bLevelUpDrawSwitch;				// �������� �Ǿ����� �˷���� �ϴ°�?
	 CLevelUpEffect	*pclLevelUp;			// �������� ��Ÿ���� Ŭ����.

	 //------------------------
	 // ��Ʈ ����Ʈ ���� 
	 //-------------------------
	 CHeartEffect *pclHeartEffect;

	 //------------------------
	 // ���� Ŭ�ι� ����Ʈ ���� 
	 //-------------------------
	 CFourLeafEffect *pclFourLeafEffect;

	 CCushionEffect	 *pclCushionEffect;
	 CCushionCatEffect	 *pclCushionCatEffect;

	 //------------------------
	 // ��� ��� ����
	 //------------------------
	 SI32 siCushionUnique;

	 //------------------------
	 // MVP �̹��� ���� 
	 //-------------------------
	 bool bMVPEffectDrawSwitch;				// �������� �Ǿ����� �˷���� �ϴ°�?
	 CMVPEffect	*pclMVPEffect;			// �������� ��Ÿ���� Ŭ����.

	 //------------------------
	 // Enchant ����Ʈ ����
	 //-------------------------
	 bool bEnchantEffDrawSwitch;
	 CEnchantEff	*pclEnchantEff;	

	 //------------------------
	 // Quest ����Ʈ ����
	 //-------------------------
	 //bool bQuestEffDrawSwitch;
	 CQuestEff	*pclQuestEff;	

	 //------------------------
	 // ��ų ������ �̹��� ����
	 //------------------------
	 bool bSkillLevelUpDrawSwitch;			// ��ų �������� �Ǿ����� �� �Ǿ�����
	 CSkillLevelUpEffect *pclSkillLevelUp;	// ��ų ������ Ŭ����


	 //------------------------
	 // �̸�Ƽ�� �̹��� ����
	 //------------------------
	 CEmoticonEffect* pclEmoticonEff;

	 //------------------------
	 // �߷�Ÿ�� �̸�Ƽ�� �̹��� ����
	 //------------------------
	 CEmoticonEffect* m_pclValentineEmoticonEff;

	 //------------------------
	 // ����ġ ǥ�� 
	 //------------------------
	 CExpCounter*	pclExpCounter;			// ����ġ ǥ��. 

	 //------------------------
	 // ġ��  ǥ�� 
	 //------------------------
	 CHealCounter*	pclHealCounter;			// ġ��  ǥ��. 

	 //------------------------
	 // �ʻ�� ǥ��
	 //------------------------
	 CCharCriticalEffect	*pclCriticalEffect;

	 //------------------------
	 // ��ƿ ������ ���� �� ǥ��
	 //------------------------
	 CCharJim				*pclJim;

	 //------------------------
	 //	��Ƽ ���� ǥ�ø� ���� ��.
	 //------------------------
	 CCharPartyEmoticon		*pclPartyEmoticon;

	 //-----------------------
	 // ��ǳ�� ���� 
	 //-----------------------
	 CDrawChat*	pclDrawChat;
	 
	 //-----------------------
	 // ĳ���� �̸� ��� ����
	 //-----------------------
	 CDrawCharName *pclDrawCharName;

	 //---------------------------------
	 // ������ ĳ���Ϳ� ���ǽ� �ε���. 
	 //--------------------------------
	 SI32 siHeroSurfaceIndex;

	 //-----------------------------
	 // ������ ĳ���� ����.
	 //-----------------------------
	 SI32 siHostID;
	 SI32 siSlaveID;

	 //--------------------------
	 // ĳ���� �̸� ���� ǥ�� 
	 //--------------------------
	 DWORD dwLastMakeCharNameFrame;
	 TCHAR szCharNameInfo[128];

	 //--------------------------
	 // ��⵿���� ���������� �ٲ�ð�
	 //--------------------------
	 clock_t lastWaitAniChanged;

	 //--------------------------
	 // ġ�� ȿ��. 
	 //--------------------------
	 DWORD dwHealClock;

	 //------------------------
	 // ��ǰ ���� ȿ��. 
	 //------------------------
	 bool bStartMakeItemSwitch;
	 DWORD dwStartMakeItemClock;
	 DWORD dwDelayMakeItemClock;

	 // ���� ���� üũ�ϱ� ���ؼ�
	cltShopTradeData	clMyShopData;
	BOOL				bMyShopStart;

	//--------------------------
	// ��ȣ���� Ư����� ����Ʈ
	//--------------------------
	DWORD	dwSoulGuardSF_Clock;
	SI16	siSoulGuardSF_Kind;

	//--------------------------
	 // �̸� �� �׸����� �ε���
	 //--------------------------

	 
	 //TCHAR m_NPCName[MAX_NPCKINDFORRANKMARK][64];
	 //SI32 m_NPCKindIndex[MAX_NPCKINDFORRANKMARK];
	 //SI32 m_NPCImgIndex[MAX_NPCKINDFORRANKMARK];

	RGB16	*m_RankMarkImgEncBuffer;
	SI32     m_RankMarkEncHres;
	SI32     m_RankMarkEncVres;

	SI32	m_siSetItemImgAnimationCounter1;
	SI32	m_siSetItemImgAnimationCounter2;

	SI32	m_siWeddingImgAnimationCounter;
	
	cltCharClient();
	virtual ~cltCharClient();

	void InitCharClient();

	SI32 GetRX() const;
	SI32 GetRY() const;

	//---------------------------------------------------------------
	// ������ ĳ����. 
	//---------------------------------------------------------------
	// �Ķ��Ÿ�� �־��� �����ۿ� ���� Person�� ������ �ٲ��ְ� �Ѵ�.
	bool ChangeArmCode(SI32 itempos, SI32 siunique);
	// �� �ڵ带 �����Ͽ� ��ġ�Ѵ�.
	void ChangeHorseCode( SI32 code,cltDate* cldate = NULL , SI32 ticket = 0);

	//---------------------------------------
	// ĳ���͸� ȭ�鿡 �׷��ش�. 
	//---------------------------------------
	//Game Direction�� CDD Direction���� �����Ѵ�.
	SI32 TransDir(SI32 gamedir);

	bool Draw();
	bool DrawHero();
	// DrawHero ������ ��� ��ǰ, ��þƮ ����Ʈ�� üũ�ؼ� ��ȯ�ϴ� �Լ�[����]
	SI32 CheckJewelEffect( UI32 rare , SI32 enchanttype , SI32 enchantpower, bool Flag = false );	
	bool DrawNormal();
	DWORD GetDrawFrame(); 

	BOOL OperateWaitClient();

	// ��� ����. 
	bool Action_Dying();

	void SetFileNFont();

	// ���� ��ǥ�� ����Ѵ�. 
    void CalculateRealXY();

	void NewSelectedAction();

	// ĳ������ �̸��� �����.
	bool MakeCharName(cltCharClient* pclchar);
	void DrawName();

	// �� ǳ���� �׸���. 
	void DrawChatBalloon();
	// �ź� ǥ�ø� �Ѵ�. 
	void DrawRankMark(SI32 font);
	// �ְ� ���� ǥ�ø� �Ѵ�. 
	void DrawMakeMasterMark(SI32 skillunique);
	// GM��ũ�� ǥ���Ѵ�
	void DrawGMMark();

	// [����] ���Һ� �̺�Ʈ : Ű��, ��ų��, ������ �Ӹ����� ���� ����ؼ� �׽�Ʈ ����
	void DrawBBBSpecialIndicator(SI32 siType);

	// ���Һ� Ű���Ϳ� ��ũ ǥ��
	void DrawKeyMonsterMark();
	
	// [�߰� : Ȳ���� 2008. 1. 15 => �ְ���� ��ũ �׷��ֱ�.]
	void DrawBestGuildMark(void);

	// PC�� ��ũ�� �׸���
	void DrawPCRoomMark( void );
	// �����̾� ������ �׸���
	void DrawPremiumPartsEffect(SI32 siHorseUnique ,SI32 siPremiumUnique);
	// �����̾� ���� ǮƩ�׵� ����Ʈ�� �׸���.
	void DrawPremiumPartsFULLEffect(SI32 siHorseUnique);

	// �ʺ��� ���� ȭ��ǥ��.(����, ������, �����, ��������)
	void DrawArrow();
	// �޾ƾ��� ����Ʈ �˸� ǥ��.(����, ������, �����, ��������)
	void DrawQuestion();
	// ������ ����Ʈ �˸� ǥ��.(����, ������, �����, ��������)
	void DrawRedExclamation();
	// �Ϸ�� ����Ʈ �˸� ǥ��.(����, ������, �����, ��������)
	void DrawBlueExclamation();

	// ���Ӱ� ����� ����Ʈ ��ũ �׸��� �Լ�
	void DrawQuestionMark( SI16 siMode );

	//npc �� �̸��� text ���Ͽ��� ���´�
	void NPCMgr();

	BOOL DrawShadow();

	// ����ȿ�� ��� �Լ�.
	BOOL DrawGeneralEft();

	// ���� ��ǥ�� ����Ѵ�. 
    void CalculateDrawStartXY();
	void CalculateDrawStartXYInMapCaptureMode();

	void GetBottomPoint(cltPos* pclpos);

	void SetNewSelectedSwitch(bool mode);
	void SetMouseOverSwitch(bool mode);

    void DecideFont();

	void SetDrawReadySwitch(bool mode);

	//------------------------
	// �ǰ� �̹��� ���� 
	//-------------------------
	void SetHitSwitch(bool mode);
	void SetHitDrawSwitch(bool mode);

	//---------------------------------------
	// ���� ������Ʈ�� ��ġ ���� 
	//---------------------------------------
	// � �� ���� obj ���� �ִ��� ���θ� �˷��ִ� �Լ� (���� ��ǥ)
    BOOL			IsAbsPtInObj(SHORT x, SHORT y, SHORT& length);

	///----------------------------------
	// Session ������ ȣ�� �Լ�. 
	//-----------------------------------
	void Init();
	void Close();

	//-------------------------------------------
	//�̵� ���� �Լ�.(CharClient-Move.cpp)
	//-------------------------------------------
	void CalculateRXY();
	void SetMoveStandardPos(SI32 mox, SI32 moy, SI32 mdx, SI32 mdy);
	//���� ��ǥ�� ���� ��ǥ���� ����� �� ������ ���Ѵ�. 
    void GetMoveRatio(SI32 startx, SI32 starty, SI32 endx, SI32 endy, SI32 movepercent, SI32& rx, SI32& ry);

	//--------------------------------
	// �����, ��� ���� ó��. ( �ٴڿ� �� �׸��� �� )
	//--------------------------------
	void CharBossAction();

	//--------------------------------
	// Regeneration ���� ó��. 
	//--------------------------------
	void CharRegenerationAction();
	void SetCharRegeneration();

	//--------------------------------
	// ���� ���� ó��. 
	//--------------------------------
	void CharCutAction();
	void SetCharCut(SI32 mode);

	//--------------------------------
	// ������ ���� ó��. 
	//--------------------------------
	void SetLevelUp();

	//--------------------------------
	// MVP ����Ʈ ���� ó��
	//--------------------------------
	void SetMVPEffect();

	//--------------------------------
	// Enchant ����Ʈ ���� ó��
	//--------------------------------
	void SetEnchantEffect(SI08 AniType);

	//--------------------------------
	// Quest ����Ʈ ���� ó��
	//--------------------------------
	void SetQuestEffectReceive();
	void SetQuestEffectClear();

	//--------------------------------
	// ��ų ������ ���� ó��. 
	//--------------------------------
	void SetSkillLevelUp();

	//--------------------------------
	// �̸�Ƽ�� ���� ó��.
	//--------------------------------
	void SetEmoticon( SI16 index );

	//--------------------------------
	// �߷�Ÿ�� �̸�Ƽ�� ���� ó��.
	//--------------------------------
	void SetValentineEmoticon( SI16 index );

	//----------------------------
	// Ŭ���̾�Ʈ ĳ������ ����. 
	//----------------------------
	void CharClientAction();

	//-----------------------------------
	// �� ���� 
	//-----------------------------------
	bool RideHorse();		// ���� ź��. 
	bool UnrideHorse();		// ������ ������.
	
	void DeleteOperation();	// ������ �ʿ��� ��ġ�� ���Ѵ�. 
	void DeleteSlave();		// �����ڸ� �����Ѵ�. 

	bool AfterCharAction();
	void SetJimShow();		// �������� ���� ȭ�鿡 ǥ���ϰų� ǥ������ �ʴ´�. 
	
	//-----------------------------------
	// ��ǰ ����. 
	//-----------------------------------
	bool SetMakeDelayDraw(DWORD delayclock);
	void DrawMakeDelay(LPDIRECTDRAWSURFACE7 lpSurface, SI32 rx, SI32 ry);		// ��ǰ ���� ������ ǥ���Ѵ�. 
	
	
	void DrawHealthBar();		// Health Bar�� �׷��ش�.
	void DrawKingEffect();		// King Effect�� �׷��ش�.
	void DrawGodEffect();		// ��Ȳ�� Effect�� �׷��ش�.
	void DrawSummonEffect();	// ��ȯ�� Effect�� �׷��ش�.
	void DrawLoveEffect();		// �ٴڿ� ��Ʈ Effect�� �׷��ش�.
	void DrawGachaSummonEffect();	// ��ȯ�� Effect�� �׷��ش�.

	//KHY - 1220 - ���Žý���. - //�ش� ���� ĳ���� ��ũ�� 100%�̸�.
	void DrawTransformSyc100Effect();

	void FogAction();			// ���� ó���� �Ѵ�. 
	
	void DoQuestCheckAndAction(SI32 questclearcond);		// ĳ���Ͱ� �����ϰ� �ִ� ����Ʈ�� �����Ͽ� �����Ų��. 
	void MakeRankMarkEncBuffer();
	
	void DrawGate(SI32 id);		// ����ī ���� �Ҳ�
	bool NewYearEventDay(void);

	// ����Ʈ �ο� �̹����� ���� �´�
	SI16 GetQuestDisplayMark( cltSystemNPC* pclSystemNPCInfo );

	bool IsBlankInv(SI32 invnum, SI32 invmode);

};



#endif 
