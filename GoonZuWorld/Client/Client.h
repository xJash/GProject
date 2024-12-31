//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _CLIENT_H
#define _CLIENT_H

#define JEWAN_FRAME_SKIP						// 12�� 10�� �۾� ȿ������ ������ ��ŵ ( ���� )

#include "..\CommonLogic\CommonLogic.h"

#include "UnderMouseObject\UnderMouseObject.h"
#include "Logo\Logo.h"

#include "..\..\Server\FrontServer\FrontMsg.h"
#include "..\..\Server\FrontServer\WorldList.h"
#include "Network\StateBox.h"
#include "GlobalImgFile\GlobalImgFile.h"
#include "Interface\Pannel\Pannel.h"
#include "ITZNetOverlapped.h"
#include "Char\CharClient\Char-Client.h"
#include "Key\Key.h"

#include "DrawLoadingImg\DrawLoadingImg.h"

#include "InterfaceMgr/DialogResource.h"

#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "NUpdateTimer.h"

#ifdef USE_HANAUTH
	#ifndef _SERVER
		// - NHN ACM -
		#include "../HanAuth/HanAuthForClient.h"
		// - NHN ACM -
	#endif
#endif

#ifdef USE_HANREPORT
	#ifdef _SERVER

	#else
		#include "../HanAuth/HanReportForClient.h"

			#ifdef _DEBUG
				#pragma comment(lib, "HanReportForClientD.lib") 
			#else
				#pragma comment(lib, "HanReportForClient.lib") 
			#endif // _DEBUG
	
	#endif // _SERVER
#endif // USE_HANREPORT



// -HanAuth_Lib
//�Ѱ��� ��ǥ ���
#ifdef USE_HANPOLL
	#ifdef _SERVER
	#else
		// �Ѱ��� ���� ���� ���
		#include "../HanPollForClient/HanPollForClient.h"

		#ifdef _DEBUG
			#pragma comment(lib, "HanPollForClientD.lib") 
		#else
			#pragma comment(lib, "HanPollForClient.lib") 
		#endif
	#endif		
#endif


//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	#ifndef _SERVER
		#include "../Porte/PorteAuthForClient.h"
		using namespace Porte::PorteAuthSystem;
	#endif
#endif

#include "../CommonLogic/BattleRoyal/CBattleRoyalClient.h"

//[�߰� : Ȳ���� 2007. 12. 3 �������α׷� �˻� ��� �߰�.]
#include "../Client/AutoMacroMgr/clAutoMacroManager.h"
#include "../Client/CheckProcess/CheckProcess.h"
#include "ItemPeriodMgr/ItemPeriodMgr.h"


class cltMusic;
class CRegistryMgr;
class CDrawSequence;
class CDrawChatSurface;
class CDrawCharNameSurface;


class cltQuitConfirm;
class cltQuitMenu;
class CRememberWindowPosMgr;
class CCCDSurfaceMgr;
class CFocusManager;
class CClickEffect;
class cltGameContract;

class CaptureJPG;
class CFriendLoginDraw;
class CResidentLoginDraw;
class cltMiniHomeUpdates;
class cltPICAManagerCheck;
class cltPopupCheck;
class CVillageWarNotice;
class CNewYearEventNotice;

class CResidenceCheck;
class CVillageNotice;
class CDurability;
class CGameMasterDlg;
class CGameMasterPersonalLogDlg;
class CGMServerInfoDlg;
class CEventNotice;
class CWebEventDlg;
class cltHtmlDlgManager;

class CTradeMerchantDlg;
class CDecreePasswdDlg;
class cltGameMsgResponse_DelUserChar;
class cltGameMsgResponse_PreDelUserChar;
class cltHeroDataBackup;
class CTradeMerchantHorse;
class CTradeMerchantDish;
class cltHelpManager;

class CChatStatusBar;
class cltPCRoomIntro;

class CNPrivateChatDlgMgr;


class CAbuseFilter;

class CTestDlg;
class CDrawLogo;

class cltNVillageDetailInfoManager;

struct stMsgBox;
class CInterfaceMgr;

class CDialogController;
class CControllerMgr;
class CNFarmingDlg;

class CFeastEffectManager;

///////////////////////////////////////////////////////////////////
//// �̴� ���� �߰�
class CMiniGameFactory;
class CMiniGameManager;

class CEmoticonInfo;
class CBeginnerText;
class CLevelUpText;
class CGameTip;

class cltMarkManager;
class CGameClient;

class cltCheckProcess;
class CItemPeriodMgr;
class CGawiBawiBoMgr_Client;
class CClient_BBBMgr;
class CBattleRoyalClient;
//class CSearchDetailDlg;
class CClient_PartyMatchingMgr;
class CPartyQuestMgr_Client;

class	cltGMA;					// GZMacroAnalysis
class	cltGZFtp;


#define MAX_WORLD_NAME_SIZE		128

#define FIND_TREASUREEVENT_QUEST_UNIQUE	31500
#define FIND_TREASUREEVENT_QUEST_UNIQUE_SUB1	31505
#define FIND_TREASUREEVENT_QUEST_UNIQUE_SUB2	31510
#define FIND_TREASUREEVENT_QUEST_UNIQUE_SUB3	31515


enum // �̺�Ʈ ���� 
{
	GAME_ROUND_1	=	0	,
	GAME_ROUND_2,
	GAME_ROUND_3,
	GAME_ROUND_4,
	GAME_ROUND_5,
	GAME_ROUND_6,
	GAME_ROUND_7,
	GAME_ROUND_8,
	GAME_ROUND_9,
	GAME_ROUND_10,
};


extern SI32		g_siContryCode;
extern BOOL		g_bFullScreen;

extern bool bIDPassswordInputSwitch;
extern bool loginswitch;
extern bool noticeswitch;
extern bool worldlistswitch;

//-------------------------------------------
// cltClient
//-------------------------------------------
class cltClient : public cltCommonLogic {
public:
	//[�߰� : Ȳ���� 2007. 12. 3 => Ŭ���̾�Ʈ�� �������α׷����� �۵������� Ȯ������ Ŭ����]
	CAutoMacroManager clAutoMacroManager;


	cltMouseObject clMouseObject;

	SI32	siRX, siRY;				// ��ũ���� RX, RY
	DWORD	m_dwGTick;
	bool	bDropTrySwitch;				// ������ ������ �õ� ���ΰ�.(�̵� �Ұ�) 

	bool	bReceiveServerInfoSwitch;		// ������ �⺻ ���� ���� ����. 

public:

	SI32	siScreenMode;

	SI32	siScreenModeXOffSet;
	SI32	siScreenMode800X600XSize;

	SI32	siScreenModeYOffSet;
	SI32	siScreenMode800X600YSize;

	TCHAR	strTextFontFileName[ MAX_PATH ];

	//-------------------------------------------
	// ���ڽ� ���� ����Ʈ
	//-------------------------------------------
	CFeastEffectManager*	m_pFeastEffectManager;
	//------------------------------------
	// ȭ��ĸ�Ŀ� Class 
	//------------------------------------
	CaptureJPG	*pclCapture;

	//-------------------------------------------
	// ����Ʈ ���� ���� 
	//-------------------------------------------
	SI32 siServiceArea;							// Ŭ���̾�Ʈ�� ó�� �۵��Ҷ� � ���� ������ �ٰŷ� �ϴ°�. 


	//-------------------------------------------
	// ����� ���̵� �н�����. 
	//-------------------------------------------
	TCHAR	szID[FILE_NAME_SIZE];						// ����� ���̵� 
	TCHAR	szPassword[FILE_NAME_SIZE];					// ����� ��й�ȣ.        

	bool	bWindowNotice;								// ������ ������ ����.

	cltLogo*	pclLogo;								// �ΰ� 

	CDrawLoadingImg*	m_pLoadingImg;					// �ε��̹���

	//---------------------------------------------
	// ��Ʈ��ũ ���� 
	//---------------------------------------------

	BYTE									m_encRecvBuf[ 100000 ];  // �������� ���� ��Ŷ ��ȣȭ ���� ����

	// APEX-
	bool									m_bStartApex;
	CRITICAL_SECTION						m_CSSendToGameServer;
	// -APEX

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
#ifndef _SERVER //������ ���ǵǾ� ���� �ʴٸ�.
	TCHAR									m_szPorteAuth_GameInfoString[SIZE_GAMEINFOSTRING];
	TCHAR									m_szPorteAuth_szAuthTICKET[SIZE_AUTHTICKET];
	TCHAR									m_szPorteAuth_szServiceCode[SIZE_GAMEINFOSTRING];	// ���� ���� �޾ƿ;� �Ѵ� .
#endif
#endif // USE_PORTEAUTH
	SI08									m_siPorteAuth_TryCount;  // 3���� �������� �õ��Ѵ�.

#ifdef _USA_NEW_AUTH_
	TCHAR									m_szUSAAuth_String[4096];
#endif


#ifdef USE_HANAUTH
	// -HanAuth
	TCHAR									m_szHanAuth_GameString[SIZE_GAMESTRING];
	TCHAR									m_szHanAuth_AuthString[SIZE_AUTHSTRING];
	// -HanAuth
#endif // USE_HANAUTH
	SI32									m_siHanAuth_ServiceTypeCode;
	TCHAR									m_szHanAuth_UserID[MAX_PLAYER_NAME];
	SI08									m_siHanAuth_TryCount;

	TCHAR									m_szPorteAuth_UserID[13]; // User ID size is 12byte 	// �߱� ���� ���̵�

// -HanAuth_Lib
	void									HanAuth_Lib_HanReportSendPosLog_Client(TCHAR* pszID, TCHAR* value);
// -HanAuth_Lib
	void									HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(SI32 siserverID, TCHAR* pszUserID, TCHAR* pszValue);

	//NUpdateTimer							kHanAuth_UpdateTimer;
//	NUpdateTimer							kHanAuth_UpdateTimer_GameRunAuth;

	ITZSession*								pGameSession;
	ITZSession*								pFrontSession;
	SI32									siAuthKey;							//	Front Server�� ���� ���� ����Ű. 

	UI08									cSecretBuffer[ PACKET_MAX_SIZE ];	// �������� ����� ���� ��ȣȭ�� �����͸� ������ ����. 
	bool									bFrontServerSecretKeySwitch;		// ����Ʈ �����κ��� ��ȣȭŰ �� �޾����� Ȯ���Ѵ�.
	bool									bGameServerSecretKeySwitch;			// ���Ӽ����κ��� ��ȭȭŰ�� �޾����� Ȯ���Ѵ�.��

	BOOL									bLoginRequest;
	DWORD									dwLastLoginTick;
	NUpdateTimer							m_kTimer_WaitGameLogin;


	ITZSessionFactory< cltCharClient >		sf;
	ITZSessionManager						sm;
	ITZNetOverlapped						overlapped;

	cltWorldList							clWorldList;						// ������ ���� ���� ���� ����Ʈ. 
	WORLDINFO								clSelectedWorldInfo;				// ���õ� ���� ����. 

	cltStateBox								clUserState;

	cltGZFtp		*m_pclGZFtp;
	//-------------------------------
	// GZMacroAnalysis
	//-------------------------------
	cltGMA				*m_pclGMA;
	SI32				m_siGMA_ByAdminPersonID;
	BOOL				m_bGMA_ReportedByAdminCommand;

	bool bFrontServerActionSwitch;
	bool bGameServerActionSwitch;

	//--------------------------------------------
	// ��Ŀ�� ���� ����
	//--------------------------------------------
	CFocusManager	*pclFocusManager;

	//--------------------------------------------
	// ������Ʈ�� ���� 
	//--------------------------------------------
	CRegistryMgr*	pclRegistry;

	//--------------------------------------------
	// ����. 
	//--------------------------------------------
	cltToolBar*				pclToolBar;

	//--------------------------------------------
	// ������ ��ġ ���
	//--------------------------------------------
	//CRememberWindowPosMgr	*pclRememberWindowPosMgr;

	//-------------------------------------------
	// �ǳ� 
	//------------------------------------------
	cltPannel*				pclPannel;


	//-------------------------------------------
	// ������ ǥ��
	//------------------------------------------
	CDurability*			pclDurability;

	//CSearchDetailDlg*		m_pSearchDetailDlg;

	//-------------------------------------------
	// ���� �ȳ���
	//------------------------------------------
	CVillageNotice			*pclVillageNotice;

	//-----------------------------------------
	// ���� ��� 
	//-----------------------------------------
	bool	bRepairSwitch;

	//-----------------------------------------
	// �ڸ� ��� 
	//-----------------------------------------
	bool	bPromptSwitch;

	//-----------------------------------------
	// SMALL MAP ���
	//-----------------------------------------
	bool	bSmallMapSwitch;

	//----------------------------------------
	// ���� �ǹ� ���� ���� Ȯ�� ����ġ. 
	//----------------------------------------
	bool bWaitVillageStructureInfoSwitch;

	//----------------------------------------
	// ���ΰ� ĳ���Ͱ� ���ʷ� �����Ǿ����� ���� 
	//----------------------------------------
	//bool	bFirstHeroCharInitSwitch;

	//----------------------------------------
	// ���� ��� ���� 
	//----------------------------------------
	bool bWatchModeSwitch;
	SI32 siWatchModeDetailX;
	SI32 siWatchModeDetailY;

	//----------------------------------------
	// �۾� ���� ���� ����ġ(����, ����)
	//----------------------------------------
	bool bStopDoingSwitch;

	bool bPassFirstOrder; 

public:
	//-----------------------------------
	// Ű �Է�. 
	//-----------------------------------
	cltKeyManager	clKeyManager;

	//----------------------------------------
	// ���ǽ� 
	//----------------------------------------
	LPDIRECTDRAWSURFACE7		lpBackScreen;	// ������ �׷��� ȭ�� ���� ���ǽ�. 


	//----------------------------------------
	// ��� ���� ���� 
	//----------------------------------------
	CDrawSequence* pclDrawSequence;

	cltMusic* pclMusic;

	cltGlobalImgFile* pclGImg;

	//---------------------------------------
	// �������� ������ ���� �ð�. 
	//---------------------------------------
	DWORD	dwLastReceiveFromServerClock;


	//--------------------------------------
	// ���� ���� �߿��� ������ ������ �ִ°�?
	//---------------------------------------
	bool bLoginWhileServerDownSwitch;

	//--------------------------------------
	// ���������� �����ߴ� ������ ����ΰ�?
	//--------------------------------------
	TCHAR szLastConnectServerName[20];

	//----------------------------------------
	// Ŭ���̾�Ʈ ���� ũ��. 
	// ȭ�� ������� Ŀ�� �ε巯�� ��ũ���� ���������ϴ�. 
	//----------------------------------------
	SI32 siClientScreenXsize;
	SI32 siClientScreenYsize;
	SI32 siClientScreenHalfSize;

	// ȭ�鿡 ���� ������ �ӽ÷� �����ϴ� �� 
	UI08* pScreenMapBuffer;
	LPDIRECTDRAWSURFACE7     lpScreenMapBuffer;

	SHORT	GameMouseX;
	SHORT	GameMouseY;


public:
	SI32 siSelectedOrder;				// ���õ� ��� 
	SI16 siSelectedOrderPara1;			// ���õ� ����� �μ� �Ķ��Ÿ. 
	SI16 siSelectedOrderPara2;			// ���õ� ����� �μ� �Ķ��Ÿ.

public:
	SI32 ObjectTempSelectedSwitch;

	//private: // 05�� 03�� 22�Ͽ� ������ �ٲ�(�ӽ÷�)
public:
	// ĳ���� ���ð��� ���� //
	SI32    MyCharUnique;
	SI32	Char_flag;

	SI32 CurrentCharInfoList;
	// ������ ���� ���� ����� ĳ���͵��� ������ ������ ����.
	cltCharListInfo clCharListInfo[MAX_TOTAL_CHAR_PER_USER];

public:
	SHORT   IDPara1; // �� ���̵� ���� �Ķ��Ÿ 
	SHORT   IDPara2; // �� ���̵� ���� �Ķ��Ÿ 

	cltUnderMouseObject* pclUnderMouseObject;		// ���콺 ������ �ؿ� �ִ� ĳ����. 


	HWND SelectCharDlg;					// ĳ���� ���� ���̾�α� �ڽ� �ڵ�. 
	HWND MakeCharDlg;					// ĳ���� ����� ���̾�α� �ڽ� �ڵ�. 
	HWND SelectWorldListDlg;			// ���� ����Ʈ ���� ���̾�α� �ڽ� �ڵ�. 

	CResidenceCheck				*m_pResidenceCheck; // �ֹε�Ϲ�ȣ ���ڸ� �Է�
	//CSiegeWinDlg				*m_pSiegeWinDlg; // ���� ���� ��� �˸�â

	// �� �̺�Ʈ
//	CEventNotice				*m_pEventNotice; // ���� �̺�Ʈ ���â
//	CWebEventDlg				*m_pWebEventDlg;
//	cltHtmlDlgManager			*m_pHtmlDlgManager;

	// ������ �̺�Ʈ ����
	SI32						m_siSucceedEventType;
	
	// ����, ��Ŀ ����� �̺�Ʈ ���� (PCK - 2008.09.18)
	// 1 = ��Ŀ, 2 = ����
	SI32						m_siGoStopPockerEventType;

	CFriendLoginDraw			*m_pFriendLoginDraw;
	CResidentLoginDraw			*m_pResidentLoginDraw;
	CVillageWarNotice			*m_pVillageWarNotice;
	CNewYearEventNotice			*m_pNewYearEventNotice;

//	CAbuseFilter				*m_pCAbuseFilter;
	//CNFarmingDlg				*m_pNFarmingDlg;

	CDrawLogo					*m_DrawLogo;

	cltDate clClientDate;				// ���� �ð�. 

	_SYSTEMTIME sTime;					// ������ �����ð�

	BOOL ScrollProcSwitch;				// ��ũ�� ����. 
	

	//-------------------------------------
	// �������̽� ����
	//-------------------------------------
	CInterfaceMgr				*m_pInterfaceMgr;
#ifdef _SAFE_MEMORY
	NSafeTArray<CDialogController*, DIALOG_END>		m_pDialog;
#else
	CDialogController			*m_pDialog[ DIALOG_END ];
#endif

	//-------------------------------------
//	cltPCRoomIntro				*m_pPCRoomIntro;

public:

	//-------------------------------------
	// ���� �ֽű� �о����
	//-------------------------------------
//	cltMiniHomeUpdates*	pclMiniHomeUpdates;

	//-------------------------------------
	// �Ѱ��� PICA�Ŵ��� üũ
	//-------------------------------------
	cltPICAManagerCheck*	m_pclPICAManagerCheck;

	//-------------------------------------
	// [����] �˾�â ���� üũ. 2008-5-27
	//-------------------------------------
	cltPopupCheck*			m_pPopupCheck;
	NUpdateTimer			m_kUpdateTimer_PopupCheck;
	
	//-------------------------------------
	// ä�� ��ǳ�� ����. 
	//-------------------------------------
	CDrawChatSurface*	pclDrawChatSurface;

	//-------------------------------------
	// ĳ���� �̸� ��� ����. 
	//-------------------------------------
	CDrawCharNameSurface*	pclDrawCharNameSurface;

	//------------------------------------
	// DB�̻� ����.
	//------------------------------------
	bool bDBFailSwitch;

	//------------------------------------
	// �̵� ǥ��. 
	//------------------------------------
	CClickEffect*	pclClickManager;

	//--------------------------------
	// ���ΰ� ĳ���� ���� ��� ��ġ. 
	//--------------------------------
	bool bReceiveMyCharAllInfoSwitch;		// ���ΰ� ĳ������ ������ �����κ��� ��� �޾Ҵ��� ����. 
	bool bBackUpSwitch;						// ���ΰ� ĳ������ ������ Ŭ���̾�Ʈ���� ���� ��� �޾Ҵ��� ����, 
	cltHeroDataBackup* pclHeroDataBackup;

	//--------------------------------
	// ���� ���. 
	//--------------------------------
//	cltGameContract* pclGameContract;


	//-------------------------------
	// �Ұ��縮 ��� �̺�Ʈ. 
	//-------------------------------
	bool bHuntingEventSwitch;

	//-------------------------------
	// ���ĸ��� ���� �̺�Ʈ ���� ����.
	//-------------------------------
	SI16 siMofuMofuEvent_VilliageUnique;

	//-------------------------------
	// ���� ���� ���  �̺�Ʈ. 
	//-------------------------------
	bool bGoguEventSwitch;

	//-------------------------------
	// ����ī�� �̺�Ʈ 
	//-------------------------------
	bool bOsakaEventSwitch;

	//-------------------------------
	// ��ȭ�� �̺�Ʈ 
	//-------------------------------
	bool bKanghwadoEventSwitch;

	//-------------------------------
	// �������� ������ �����Ǿ������� ����ġ by cyj
	//-------------------------------
	bool bServerNotConnectSwitch;

	//-------------------------------
	// ��Ȱ �޼��� ���� ���� ����ġ by cyj
	//-------------------------------
	bool bReviveRequestSwitch;

	//------------------------------
	// ���������� �̸�Ƽ�� �����ð�..�����ʿ��Ѵ�.
	//------------------------------
	clock_t	LastSendEmoticonClock;

	//-------------------------------
	// ���ǥ��
	//-------------------------------
	NUpdateTimer	m_kTimer_ShowRank_Interval;	// ���� �� 1�ð��� �ѹ��� ȭ�鿡 ���
	NUpdateTimer	m_kTimer_ShowRank_Time;		// 3�ʵ��� ȭ�鿡 ǥ��
	SI08			m_siDrawMode;				// ǥ�� ��ġ 0: ����, 1: �̴ϸ� �Ʒ�

	//-------------------------------
	// ���Ӱ��� ���������� üũ
	//-------------------------------
	NUpdateTimer	m_kTimer_Check_GameGuard_Interval;	// ���� �� 1�ð��� �ѹ��� ȭ�鿡 ���

	//-------------------------------
	// ����� ���� ����
	//-------------------------------
	cltGuildWarClient*	pclGuildWarClient;

	//-------------------------------
	// ���� 
	//-------------------------------
	cltHelpManager*		pclHelpManager;

	// �α��ΰ���â
	bool bLoginNotice;

	CNPrivateChatDlgMgr		*m_pNPrivateChatDlgMgr;

	//---------------------------------
	// �̸�Ƽ��
	//---------------------------------
	CEmoticonInfo		clEmoticonInfo;

	//
	CBeginnerText*		m_pBeginnerText;
	CLevelUpText*		m_pLevelUpText;
	CGameTip*			m_pclGameTip;

	cltMarkManager*		m_pMarkManager;


	//  [7/1/2009 ��ȣ_ITEMPERIOD] �Ⱓ�� ������ �Ŵ���
	CItemPeriodMgr*		m_pItemPeriodMgr;

	//	���� - ����������
	CGawiBawiBoMgr_Client*	m_pGawiBawiBoMgr;

	// [����] - ���Һ� �Ŵ���
	CClient_BBBMgr* m_pClient_BBBMgr;

	// [����] - ��Ʋ�ξ�
	CBattleRoyalClient* m_pclBattleRoyal;

	// [����] - �ʺ��� ��Ƽ ����Ʈ �ý���(��Ƽ��Ī).
	CClient_PartyMatchingMgr* m_pClient_PartyMatchingMgr;

	CPartyQuestMgr_Client*	m_pPartyQuestMgr;

	//---------------------------------
	// ĳ���� ���� �̹��� ���� ������ üũ �ð�
	//---------------------------------
	clock_t				m_CCDLastCheckClock;
	//---------------------------------
	// �ʵ������Ʈ ����
	//---------------------------------
	clock_t				m_DeleteFOLastCheckClock;
	//---------------------------------
	// HeartBeat
	//---------------------------------
	clock_t				m_SentHeartBeatClock;

	//-----------------------
	// �����κ� ��ȣȭ dhm-
	//-----------------------
	CGameClient*		m_pClientDiffHellMan;

	//-----------------------
	// �Ƿι��� �ý���
	//-----------------------
	UI08 uiTiredState;

	//--------------------------
	// �̸� �� �׸����� �ε���
	//--------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray< NTCHARString64, MAX_NPCKINDFORRANKMARK >		m_NPCName;
	NSafeTArray<SI32, MAX_NPCKINDFORRANKMARK>					m_NPCImgIndex;
#else
	TCHAR m_NPCName[MAX_NPCKINDFORRANKMARK][64];
//	SI32 m_NPCKindIndex[MAX_NPCKINDFORRANKMARK];
	SI32 m_NPCImgIndex[MAX_NPCKINDFORRANKMARK];
#endif

	//--------------------------
	// ��ƼŬ���̾�Ʈ üũ
	//--------------------------
	cltCheckProcess*	m_pclCheckProcess;

	BYTE				m_bufCompress[ sizeof(cltMsg) ];	// �������� ����� ���� ��ȣȭ�� �����͸� ������ ����. 

public:


	cltClient( TCHAR* appname, HWND hwnd , HINSTANCE hinst, SI32 gamemode, SI32 defaultservicearea, TCHAR* pszHanAuth_GameString, SI32 runmode);
	virtual ~cltClient() ;

	virtual void Create();
	void CreateBaseInterface();

	void CreateInterface( SI16 DialogID, bool ShowHideMethod = false );
	void DestroyInterface( CControllerMgr *pDialogController );

	void InitMembers();


	//	const unsigned char *GetThunderPalette()const{return ThunderPalette;}

	void SetTitleText();

public:
	//Client.cpp
	// ȭ�� ��� ����.

	void SetFlashWindowNotice( bool bNotice );

	void DrawGovernMentRankMark(SI32 siDrawMode);

	// Ÿ�� ī��Ʈ �ϴ� ȭ���� ���� �ش� .
	void DrawTimeCount(SI32 siTime,LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry);	// siTimeCount�� �Ѵ�.

	// ���带 �����ش�
	void DrawRound(SI32 siRound,LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry);// ���带 �����ش�.


private:

public:

	// Client.cpp
	BOOL InBufferMessageOperation(cltMsg* pclMsg, SI32 id);

	BOOL ModalessDlgProc(MSG* pmsg);

	// ���� �ڽ��� ����Ͽ� ǥ�õǴ� �޽���. 
	void OperateByServerResponseValueGlobal(const cltServerResponseValue* pclreturn);

	// �����κ����� ������� �м��Ͽ� ������ ���� �뺸�Ѵ�. 
	BOOL OperateByServerResponseValue(const cltServerResponseValue* pclreturn);

	//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
	BOOL OperateByServerResponseCharValue(const cltServerResponseCharValue2* pclreturn);

	//----------------------------------------------
	// MyDPID
	//----------------------------------------------
	// dpid�� ��������� Ȯ���Ѵ�.
	BOOL IsUser(SI32 charunique)
	{
		if(MyCharUnique && MyCharUnique == charunique)return TRUE;
		return FALSE;
	}


	// ��� ó�� �Լ�. 
	BOOL OrderOperation(cltOrderData order);
	BOOL OrderAction();
	void SetSiSelectedOrder(SI32 seletedorder) { siSelectedOrder = seletedorder; };

	// �� ������ ���� 
	virtual void MapEditAction(){}


	// ä�� 
	// ������ äƮ �޽����� ������. 
	BOOL SendChatMessage(SI16 chatmode, TCHAR* pmsg,SI32 systemtxt = 0 );

	// DirectX.cpp 
	// ���ӿ� ���� �ȷ�Ʈ�� �ҷ��´�. 
	//	void LoadPalette();
	//	void SetGamePalette(const unsigned char *pal);

	void UpdateScreen(HWND hwnd, LPDIRECTDRAWSURFACE7 pSurface, bool waitrefresh);

	// Ŭ���̾�Ʈ�� �Ͽ��� FrontServer�� �����ϰ� �����. 
	bool InitConnectToFrontServer();

	// Front Server�� ������ �õ��Ѵ�. 
	SI32 ConnectToFrontServer();

	// ����Ʈ ������ ���� DB����ڸ� ��DB�� �����϶�� ��û�Ѵ�. 
	void RequestJoinGame();

	// PCK : IOVATION ���� 
	bool Registeriovation();

	// Ŭ���̾�Ʈ�� �Ͽ��� GameServer�� �����ϰ� �����. 
	bool InitConnectToGameServer();

	// Game Server �� ������ �õ��Ѵ�. 
	SI32 ConnectToGameServer();

	void GetMacAddress( TCHAR *szAddress , SI16 txtSize );
	void GetMacAddress( SOCKET hSocket, TCHAR *szAddress , SI16 txtSize );

	COLORREF	GetColorByPrice( GMONEY price );
	
	TCHAR* GetServerNameFromUnique(SI16 ServerUnique);

	//----------------------------------------
	// SelectChar 
	// SelectChar.cpp
	//----------------------------------------
	BOOL SelectChar();

	// ĳ���� ���� ���̾�α� ������ ĳ���� �������� slot�� �ش��ϴ� ĳ������ ������ �����ش�. 
	BOOL SetSelectCharInfoText(HWND hDlg, SI32 slot );

	SI32 GetCurrentCharInfoList()
	{
		if ( CurrentCharInfoList < 0 || CurrentCharInfoList > MAX_CHAR_PER_USER ) return -1 ;
		return CurrentCharInfoList ;
	}
	cltCharListInfo* GetCharListInfo(SI32 index)
	{
		if ( index < 0 || index > MAX_TOTAL_CHAR_PER_USER ) return NULL ;
		return &clCharListInfo[index];
	}

	WORD GetPrimaryLanguage( HKL hKeyboardLayout );
	WORD GetSubLanguage( HKL hKeyboardLayout );
	DWORD GetCharSet();
	BOOL IsCorrectOS();

	//--------------------------------------------
	// SelectWorldList
	//--------------------------------------------
	// ������ ���尡  ���õǾ����� Ȯ���Ѵ�. 
	bool SelectWorldList();

	bool CreateSelectWorldListDlg(bool bShowBanner);

	// Draw.cpp
	void  GameDraw();   // �׸��� ���� �κ� 

	bool GameDrawHeroViewOperate();
	bool GameDrawMap();
	bool GamaDrawInterface();
	void GameDrawUpdateScreen();

	// MouseOperation.cpp
	// Ű���� ó���� ������ ��ƾ 
	BOOL GameOverHead();
	// �����󿡼� ���콺�� ��ġ�� �������� üũ�Ѵ�. 
	BOOL GetMouseMode();
	// �޴� �Էµ��� ó���Ѵ�. 
	void OperateMenu();
	BOOL SetMousePos(SI32* psix, SI32* psiy);
	// ���콺 ��ư�� ���� �ڵ� ����� ó���Ѵ�. (���� ���콺 ��ư)
	bool OperateAutoLeftOrder();
	// ���콺 ��ư�� ���� �ڵ� ����� ó���Ѵ�. (������ ���콺 ��ư)
	bool OperateAutoRightOrder();
	bool OperateAutoDoubleLeftOrder();

	void ShowMessageForItemEquipFail( SI32 siFailCode );


	//----------------------------------------
	// Char Information Update
	//----------------------------------------
	BOOL SendCharUpdate(SI32 charunique, bool bmode){return FALSE;}

	//---------------------------------------
	// GameData ���� ���
	//---------------------------------------
	// ������ ���� ������ �ؽ�Ʈ�� �����ؼ� ����Ѵ�.
	void MakeDungeonDataTxt();

	void MakeNPCDataTxt();

	void MakeMonsterDataTxt();

	void MakeMonsterItemDataTxt();

	void MakeItemMakeDataTxt();

	void MakeItemMaterialTxt();

	void MakeMonsterBasicStatusDataTxt();

	//---------------------------------------
	// Ŭ���̾�Ʈ ���� ��ɾ�
	//---------------------------------------
	void ExecFile( TCHAR* pszCommand );

	//----------------------------------------
	// SMall Map
	//----------------------------------------
	// ���� �������� ������� ��ġ�� �����Ѵ�. 
	void SetSmallMapUserPos(cltSmallMap* pclSmallMap);

	
	//---------------------------------------
	// Hero View Operate
	//---------------------------------------
	void HeroViewOperate();

	//---------------------------------------
	// User Char List
	//---------------------------------------

	// ������� ĳ���� ������ ����Ʈ�� �߰��Ѵ�. 
	// �̷��� Ȯ���� ĳ���� ������ ����ڷκ��� ���õ� �� �ִ�.
	BOOL PutCharList(cltCharListInfo* pcharinfo);

	// ĳ���� ������ �����Ѵ�.
	BOOL DeleteCharList(cltGameMsgResponse_DelUserChar* pcharinfo);
	//�ɸ��ͻ��������Ⱓ
	BOOL PreDeleteCharList(cltGameMsgResponse_PreDelUserChar* pcharinfo);


	// ĳ���� ����Ʈ�� 3���� ĳ���� ������ ��� ���Դ��� Ȯ���Ѵ�.
	BOOL IsReadyCharList();

	//------------------------------------------
	// CharStatus
	//------------------------------------------
	BOOL CreateCharStatusDlg();


	//-------------------------------------------
	// Skill
	//-------------------------------------------
	// ��ų ���̾�α� �ڽ��� �����. 
	BOOL CreateSkillDlg(SI32 charunique);

	BOOL CreateStrDlg(SI32 charunique, cltStructureMngBasic* pclmgr, SI32 dlgitem, DLGPROC dlgproc);

	//------------------------------------------
	// Stock
	//------------------------------------------
	// �ְ� ������ ���� �ð����� ȭ�鿡 �����ش�. 
	void ShowStockPrice();


	//------------------------------------------
	// CityHall
	//------------------------------------------
	BOOL CreateCityHallDlg(SI32 charunique);

	//------------------------------------------
	// SetChar
	//-------------------------------------------
	SI32					siSetCharBufferIndex;
	cltMakeCharInfo			cltSetCharBuffer[MAX_SETCHAR_RESERVE_NUMBER];
	// ĳ���͸� ������ �� ���� �� �ֵ��� ���ۿ� �ִ´�. 
	BOOL PushChar(cltMakeCharInfo* pclMsgLogIn);
	BOOL PopChar(cltMakeCharInfo* pclMsgLogIn);
	BOOL SetCharReservedChar();
	// ���� ����� ĳ���Ϳ��� Ư�� ĳ���͸� �����Ѵ�. 
	bool DeleteReservedChar(SI32 charunique);

	//npc �� �̸��� text ���Ͽ��� ���´�
	void NPCMgr();

	
	inline CGawiBawiBoMgr_Client* GetGawiBawiBoMgr()
	{
		if(m_pGawiBawiBoMgr != NULL)
			return m_pGawiBawiBoMgr;
		else
			return NULL;
	}
	
	//-----------------------------------------------
	// ���� ���� 
	//-----------------------------------------------
	BOOL PushEffect(SI32 effect, SI32 x, SI32 y);
	void PopEffect();


	//----------------------------------------------
	// ��ũ�� ���� 
	//----------------------------------------------
	void SetScrollProcSwitch(BOOL mode);
	void ScrollAction();

	//--------------------------------------
	// Action
	//---------------------------------------
	SHORT GameAction();

	BOOL ClientAction1();
	BOOL ClientAction2();

	//----------------------------------------
	// WinSock
	//----------------------------------------
	void InitNetwork();
	void WinSockConnect();
	virtual void WinSockAction();
	// ����ĳ���͸� pclCM�� �����Ѵ�. 
	void  SetSessionChar();

	// ����Ʈ ������ �޽����� ������. 
	BOOL SendFrontServerMsg(sPacketHeader* psendmsg);

	// �޽����� ������ ������. 
	BOOL SendMsgToServer(sPacketHeader* pmsg);
	void FrontServerOperation(sPacketHeader *pPacket);

	bool FrontServerAction();
	bool GameServerAction();

	void NetworkOperation();

	void Init();												// �ʱ�ȭ. 
	TSpr* GetGlobalSpr(SI32 index);								// GlobalImgFile

	//--------------------------------------------
	// ���� ���� ����.
	//--------------------------------------------
	// ���� ���� 
	BOOL CreateToolBar();
	TCHAR* GetToolTip(SI32 idcommand);

	BOOL GetClientSize(RECT* prect);							// ������ ������ ���� �Լ� 

	//-------------------------------------------
	// RX, RY
	//------------------------------------------
	void SetScreenRXY(SI32 rx, SI32 ry)
	{
		siRX	= rx;
		siRY	= ry;
	}

	SI32 GetScreenRX()const {return siRX;}
	SI32 GetScreenRY()const {return siRY;}

	SI32 GetDrawStartX(){return GetScreenRX() + MAP_TILE_XSIZE;}
	SI32 GetDrawStartY(){return GetScreenRY() + MAP_TILE_YSIZE;}


	//-----------------------------------------
	// ���� ��� 
	//-----------------------------------------
	void SetRepairSwitch(bool mode)
	{
		bRepairSwitch = mode;
	}

	bool GetRepairSwitch()const
	{
		return bRepairSwitch;
	}

	//-----------------------------------
	// WM_COMMAND�޽��� ó�� �Լ�. 
	//-----------------------------------
	virtual bool DoMsg_WM_COMMAND(WPARAM wParam);


	//----------------------------------
	// ���� �ӵ� ����. 
	//---------------------------------
	// ������ �ӵ��� �����ϰ� �����. 
	BOOL GameDelay();

	double m_dwNextFrameTick;
	double m_dwDelayTick;

	// ���Ͽ��� Server�� IP�ּҸ� ���´�.
	bool GetServeIPInFile(TCHAR* ip1, SI16 ip1txtSize, TCHAR* ip2, SI16 ip2txtSize);

	//----------------------------------
	// ���丮 ��� �޾ƿ���
	//---------------------------------
	bool GetDirectoryPath( TCHAR *DirectoryPath );

	SI32 GetScreenXSize();
	SI32 GetScreenYSize();
	SI32 GetScreenStatusBarYSize();

	void SetMsgBox( stMsgBox *pMsgBox, BYTE *pData, SI16 DataLen );
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );


	//---------------------------------------
	// CLient-WinMain.cpp
	//--------------------------------------
	// WInMain�ȿ����� Ŭ���̾�Ʈ ���. 
	void ClientWinMain();

	void GsInitConnectFrontServer();
	void GsConnectFrontServer();
	void GsInitCharList();

	void GsInitConnectGameServer();
	void GsConnectGameServer();

	void GsCharList();
	void GsGame();
	void GsQuit();
	void GsInitSelectWorldList();
	void GsSelectWorldList();

	void GsShowGovernment();

	// APEX-
	void DoMsg_GAMEMSG_RESPONSE_APEXDATA(cltMsg* pclMsg, SI32 id);
	// -APEX

	void ShowHelpWindow( TCHAR* szFileName );

	//------------------------------------------------
	// Client-Person.cpp
	//------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_INCLIFE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_INCMANA(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_REPONSE_INCHUNGRY(cltMsg* pclMsg, SI32 id);	// ���� ����� ���� ������ ����. 
	void DoMsg_GAMEMSG_RESPONSE_HIT(cltMsg* pclMsg, SI32 id);		// �¾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_GETEXP(cltMsg* pclMsg, SI32 id);		// ����ġ�� ������� ó��
	void DoMsg_GAMEMSG_RESPONSE_SPECIALQUESTREWARD(cltMsg* pclMsg, SI32 id);		// Ư�� �ӹ� �ϼ��Ŀ� ����� ������ �뺸����. 
	void DoMsg_GAMEMSG_RESPONSE_SPECIALQUESTMADE(cltMsg* pclMsg, SI32 id);		// Ư�� �ӹ� �����Ǿ����� �뺸����. 
	void DoMsg_GAMEMSG_RESPONSE_QUESTUSERINFO(cltMsg* pclMsg, SI32 id);			// Ư�� ������ ����Ʈ ������ ���´�. 
	void DoMsg_GAMEMSG_RESPONSE_HORSENAMECHANGE(cltMsg* pclMsg, SI32 id);		// �� �̸� �����ϱ�. 
	void DoMsg_GAMEMSG_RESPONSE_CLEAR_SPECIALWORD(cltMsg* pclMsg, SI32 id);		// �ܾ� ���� �ϼ� ���� ���´�.
	void DoMsg_GAMEMSG_RESPONSE_SETPERSONNAMINGINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETPPERSONCURRENTNAMING(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_PRIZE_GAMEEVENT(cltMsg* pclMsg, SI32 id);		// �̺�Ʈ ����� ���´�.
	//void DoMsg_GAMEMSG_RESPONSE_COUNTATTACK_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_EVENTNPC(cltMsg* pclMsg, SI32 id);				// �ܺ� �̺�Ʈ õ��
	void DoMsg_GAMEMSG_RESPONSE_GETGREETING(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GET_WEAPONSKILLCOST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SET_WEAPONSKILL(cltMsg* pclMsg, SI32 id);

	//--------------------------------------------------------
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	void DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_NO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_OK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_REWARD(cltMsg* pclMsg, SI32 id);
	//--------------------------------------------------------

	// [����] ���ֵ��� �̼� �Ϸῡ ���� ������ �˸�
	void DoMsg_GAMEMSG_RESPONSE_GOONZUDAYMISSION_CLEARREWARD(cltMsg* pclMsg, SI32 id);

	// �̼�����Ʈ �������� ����.
	void DoMsg_GAMEMSG_RESPONSE_MISSIONQUEST_START(cltMsg* pclMsg, SI32 id);		

	//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	void DoMsg_GAMEMSG_RESPONSE_EVENTCOUPON(cltMsg* pclMsg, SI32 id);
	//�����̺�Ʈ ���� [2007.09.10 �ռ���]
	void DoMsg_GAMEMSG_RESPONSE_AUCTIONEVENTCOUPON(cltMsg* pclMsg, SI32 id);

	//--------------------------------------------------------
	
	//--------------------------------------------------------
	// ĳ������ Ư�� ���� 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_QUEST(cltMsg* pclMsg, SI32 id);		// Person�� ����Ʈ ���� ��ü�� �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_PERSON_HORSE(cltMsg* pclMsg, SI32 id);		// Person�� �� ���� ��ü�� �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_PERSON_IP(cltMsg* pclMsg, SI32 id);			// Person�� IP������ �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_ALLITEM(cltMsg* pclMsg, SI32 id);		// ��� ��ǰ ������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_SKILL(cltMsg* pclMsg, SI32 id);		// ��� ��� ������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_ONESKILL(cltMsg* pclMsg, SI32 id);	// �Ѱ��� ��� ������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_HEALTH(cltMsg* pclMsg, SI32 id);		// �ǰ� ������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_STOCKORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PEERSON_MARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PERSON_STOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PERSON_BANK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PERSON_WORLDMONEY(cltMsg*pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_PERSONITEMINFO(cltMsg* pclMsg, SI32 id);		// Ư�� ������ �Ѱ��� ������ �޴´�. 

	void DoMsg_GAMEMSG_RESPONSE_PERSONENCHANTITEMINFO(cltMsg* pclMsg, SI32 id);	//

	void DoMsg_GAMEMSG_RESPONSE_CHARUPDATE(cltMsg* pclMsg, SI32 id);			// ĳ���� �⺻ ������ ������Ʈ �Ѵ�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_GUILTY(cltMsg* pclMsg, SI32 id);		// Person�� �� ������ �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_CHANGESTATUSINFO(cltMsg* pclMsg, SI32 id);	// ĳ������ ���� ���� ������ ���� 
	void DoMsg_GAMEMSG_RESPONSE_PERSON_INNERSTATUS(cltMsg* pclMsg, SI32 id);	// InnerStatus�� �����Ѵ�.

	void DoMsg_GAMEMSG_RESPONSE_PERSONNAME_FROMPERSONID(cltMsg* pclMsg, SI32 id);	// PersonID�� ������ Person �̸��� �޾ƿ�
	void DoMsg_GAMEMSG_RESPONSE_RIGHTMOUSE_USERLIST_NAME(cltMsg* pclMsg, SI32 id);  // ���콺 ������ Ű�� �������� �˾��Ǵ� ���� ����Ʈ�� �ʿ��� �̸��� ���´�.
	void DoMsg_GAMEMSG_RESPONSE_TIRED_STATUS(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_DONATEVILLAGEMONEY(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_DONATEMEMBERLIST(cltMsg* pclMsg, SI32 id );

	//--------------------------------------------------------


	void DoMsg_GAMEMSG_RESPONSE_WARPEFFECT(cltMsg* pclMsg, SI32 id);			// ����������� �̿��Ͽ� ���� ������ �˸���. 
	void DoMsg_GAMEMSG_RESPONSE_HORSEFREE(cltMsg* pclMsg, SI32 id);			// Person�� ���� Ǯ���ش�.
	//KHY - 1001 - ��µ��� 5���� ���� ����.
	void DoMsg_GAMEMSG_RESPONSE_CHANGEHORSE(cltMsg* pclMsg, SI32 id);			// Person�� ���� �ٲ۴�.
	void DoMsg_GAMEMSG_RESPONSE_ALLCHARINFO(cltMsg* pclMsg, SI32 id);		// Person�� ��� ������ �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_ALLCHARINFOONE(cltMsg* pclMsg, SI32 id);	// Person�� ����1�� �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_ALLCHARINFOTWO(cltMsg* pclMsg, SI32 id);	// Person�� ����2�� �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_CHANGEMONEY(cltMsg* pclMsg, SI32 id);		// Person�� ������ ������ �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_USERID(cltMsg* pclMsg, SI32 id);				// Person�� ���� ������ �޴´�.(�̴�Ȩ������ ������)
	void DoMsg_GAMEMSG_RESPONSE_WARKILL(cltMsg* pclMsg, SI32 id);			// ������ �뺸 �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_JIM(cltMsg* pclMsg, SI32 id);				// Person�� �� ������ �뺸�޴´�.
	void DoMsg_GAMEMSG_RESPONSE_HOMEVILLAGE(cltMsg* pclMsg, SI32 id);		// Person�� �ּ��� ������ �뺸�޴´�.
	//	void DoMsg_GAMEMSG_RESPONSE_SCHOOL(cltMsg* pclMsg, SI32 id);			// Person�� �б� ������ �޴´�. 
	//	void DoMsg_GAMEMSG_RESPONSE_SCHOOLUSERNUM(cltMsg* pclMsg, SI32 id);	// �б� ����� ���� �뺸 ����.
	void DoMsg_GAMEMSG_RESPONSE_PLAYTIME(cltMsg* pclMsg, SI32 id);			// Person�� �÷��� �ð��� ���Ѵ�. 
	void DoMsg_GAMEMSG_RESPONSE_GENERALEFT(cltMsg* pclMsg, SI32 id);			// ����ȿ���� ��´�. 
	void DoMsg_GAMEMSG_RESPONSE_MAKEITEMDELAY(cltMsg* pclMsg, SI32 id);		// ��ǰ ���꿡 �ʿ��� ���� �ð��� ���´�.
	void DoMsg_GAMEMSG_RESPONSE_ROULETTEGAME_RESULT(cltMsg* pclMsg, SI32 id);// �ڴ�� ���� ����� ��´�
	void DoMsg_GAMEMSG_RESPONSE_QUESTEFFECT(cltMsg* pclMsg, SI32 id);		// ����Ʈ ����Ʈ �޽���
	void DoMsg_GAMEMSG_RESPONSE_SETFATHER(cltMsg* pclMsg, SI32 id);			// ���´� ����. 
	void DoMsg_GAMEMSG_RESPONSE_SETSHOWPUCHIKOMI(cltMsg* pclMsg, SI32 id);			// Ǫġ�ڹ� ����.
	void DoMsg_GAMEMSG_RESPONSE_PERSONPRIVATEINFO(cltMsg* pclMsg, SI32 id);	// ����� �������� �뺸.
	void DoMsg_GAMEMSG_RESPONSE_CHILDINFO(cltMsg* pclMsg, SI32 id);			// ����  ���� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_FATHERAPPLYERLIST(cltMsg* pclMsg, SI32 id);	// ���� ��û�� ���� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_UPDATECHILDLIST(cltMsg* pclMsg, SI32 id);	// ���� ����Ʈ ���� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_RENOUNCEPUPIL(cltMsg* pclMsg, SI32 id);		// ������ ���ڸ� ¥�� ���� �뺸
	void DoMsg_GAMEMSG_RESPONSE_OVERTAKETEACHERLEVEL(cltMsg* pclMsg, SI32 id);	// ���ڰ� ���·����� ������Ҵ�
	void DoMsg_GAMEMSG_RESPONSE_REQUEST_SETFATHER(cltMsg* pclMsg, SI32 id);			// ���´� ����. 
	void DoMsg_GAMEMSG_RESPONSE_PVPRESULT(cltMsg* pclMsg, SI32 id);			// ���´� ����. DoMsg_GAMEMSG_RESPONSE_PVPRESULT

	void DoMsg_GAMEMSG_RESPONSE_STOCKBIDVILLAGELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STOCKBIDDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CANCEL_STOCKORDER(cltMsg* pclMsg, SI32 id);  // �ż��ֹ� ���

	void DoMsg_GAMEMSG_RESPONSE_PERSONALLSHAPEINFO(cltMsg* pclMsg, SI32 id);	// PERSON�� ���������� �뺸����
	void DoMsg_GAMEMSG_RESPONSE_ADDINFO(cltMsg* pclMsg, SI32 id);			// ĳ������ �߰������� ���� 
	void DoMsg_GAMEMSG_RESPONSE_CHANGESUMMONSTATUS(cltMsg* pclMsg, SI32 id);	// ���� ���� ��ȯ���� ������ ����Ǿ���.


	void DoMsg_GAMEMSG_RESPONSE_CHANGEMAGIC(cltMsg* pclMsg, SI32 id);		// ĳ������ MAGIC�� ����ȴ�.
	void DoMsg_GAMEMSG_RESPONSE_EVENTINFO(cltMsg* pclMsg, SI32 id);			// ĳ������ �̺�Ʈ ������ �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_NEIGHBOURHORSE(cltMsg* pclMsg, SI32 id);		// Person�� �� ������ �޾Ƽ� ������Ʈ. (�̿��� �� ����) 
	void DoMsg_GAMEMSG_RESPONSE_WINWARPRIZE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_STOCKDISTRIBUTIONSET(cltMsg* pclMsg, SI32 id);	// �ֽ� ���� �˸�
	void DoMsg_GAMEMSG_RESPONSE_STOCKDISTRIBUTIONORDER(cltMsg* pclMsg, SI32 id);	// �ֽ� ���� ���� ���

	// NPC��� 
	void DoMsg_GAMEMSG_RESPONSE_HIRENPC(cltMsg* pclMsg, SI32 id);			
	void DoMsg_GAMEMSG_RESPONSE_NPCPAYMENT(cltMsg* pclMsg, SI32 id);
	
	void DoMsg_DoMsg_GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC(cltMsg* pclMsg, SI32 id );
		
	// Client-SystemNPC.cpp
	void DoMsg_GAMEMSG_RESPONSE_SELLNPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BUYNPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NPCSELLITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRESELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_INVESTMENTGETINFO(cltMsg* pclMsg, SI32 id);

	// ���� ���� NPC ( û, �Ϻ� )
	void DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTNPCBUYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM(cltMsg* pclMsg, SI32 id);


	// ��õ ����Ʈ ���� NPC
	void DoMsg_GAMEMSG_RESPONSE_GETRECOMMANDPOINT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BUYRECOMMANDPRODUCT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECOMMANDPOINTLIST(cltMsg* pclMsg, SI32 id);


	// ���� �̺�Ʈ NPC
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC(cltMsg* pclMsg, SI32 id);

	// ���� ���� NPC
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEMFROMPERSON(cltMsg* pclMsg, SI32 id);

	// ������ �� ����
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTHORSEBUYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYHORSEFROMPERSON(cltMsg* pclMsg, SI32 id);

	// ������ �������� �����ϴ� ����
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEM(cltMsg* pclMsg, SI32 id);


	//--------------------------------------------------------------------
	// ���� �ŷ�
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_DELLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_DELITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDPRICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDSTOCK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDHOUSEUNIT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_MYACCEPT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_OTHERACCEPT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_END(cltMsg* pclMsg, SI32 id);
	//--------------------------------------------------------------------



	//--------------------------------------------------------------------
	// ��Ƽ �ý���
	//void DoMsg_GAMEMSG_RESPONSE_PARTY_CREATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_CREATEINVITE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_CREATEJOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_INVITE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_INVITEREJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_JOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_DELETE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_ADDUSER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_DELUSER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_FORCEDELUSER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_CHANGELEADER(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYEXP(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_PARTY_CHANGEITEMGETPATTERN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYITEMGET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_PARTYUSERPOS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYLEVELUP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_PARTY_WANTJOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTY_WANTJOINRESULT(cltMsg* pclMsg, SI32 id);
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// ģ��
	void DoMsg_GAMEMSG_RESPONSE_FRIENDADD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDADDACCEPT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDDEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDLOGIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDLOGOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDMEMO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FRIENDMEMOSET(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_FRIENDCHANGEGROUP(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_FRIENDCHANGEGROUPNAME(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_FRIENDALLLIST(cltMsg* pclMsg, SI32 id );	
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// ��ǥ
	void DoMsg_GAMEMSG_RESPONSE_VOTEKINGAVAILABLE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VOTEKINGSELECTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VOTEKINGAGGREGATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STARTELECTIONSTUMP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ENDELECTIONSTUMP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_STARTVOTESTATUS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VOTESTATUS(cltMsg* pclMsg, SI32 id);
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// Daily Quest
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUESTLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUESTSELECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUESTSITUATION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUESTCHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUESTEND(cltMsg* pclMsg, SI32 id);	
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// Daily Quest2
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST2LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST2SELECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST2SITUATION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST2CHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST2END(cltMsg* pclMsg, SI32 id);	
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// Daily Quest3
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST3LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST3SELECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST3SITUATION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST3CHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DAILYQUEST3END(cltMsg* pclMsg, SI32 id);	
	//--------------------------------------------------------------------
	//--------------------------------------------------------------------
	// ItemMall
	void DoMsg_GAMEMSG_RESPONSE_ITEMMALLEXISTENCE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ITEMMALLITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ITEMMALLGETITEM(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_NOLIMITTICKET_WARP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_GET_SEL_PGLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GET_ITEMMALL_ITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GET_MYCASH_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ITEMMALL_BUYITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ITEMMALL_GIFTITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHECK_ACCOUNTID(cltMsg* pclMsg, SI32 id);
	void DoMag_GAMEMSG_RESPONSE_BILLPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMag_GAMEMSG_RESPONSE_LOGINPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMsa_GAMEMSG_RESPONSE_GACHAPAGE_URL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SET_CHANGEHERO(cltMsg* pclMsg, SI32 id);

	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// ���λ��� 
	void DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPDATA(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STARTPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STOPPERSONALSHOP(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_UPDATEPERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BUYPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SELLPERSONALSHOP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SEARCHPERSONALSHOPITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MAKEPERSONALSHOP(cltMsg* pclMsg, SI32 id);

	//--------------------------------------------------------------------
	// ��ȯ�� 
	//--------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SUMMONFREE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONNAMECHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONREVIVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONATTACKCHANGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONEVOLVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONSCROLL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMON_SETAUTOHEAL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADEMERCHANTBUYSUMMONINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONTRADE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SELECT_SUMMONCHAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SELECT_SUMMONUSESTON(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BASESUMMONINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONSLOTIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONSLOTOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMON_TRANSFORM(cltMsg* pclMsg, SI32 id);	//[����] ��ȯ�� ����.
	
	//---------------------------------------------------------------------
	// �ź� ���ĺ��� ������ ����. 
	void DoMsg_GAMEMSG_RESPONSE_CANDIDATELIST(cltMsg* pclMsg, SI32 id);

	//---------------------------------------------------------------------


	// Client-Stock.cpp
	void DoMsg_GAMEMSG_RESPONSE_STOCKORDERINFO(cltMsg* pclMsg, SI32 id);
	// ������ �÷��� ����, ���� �ֹ��� ���� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_STOCKTRADEINFO(cltMsg* pclMsg, SI32 id);


	//--------------------------------------
	// ����
	//--------------------------------------
	// Client-House.cpp
	void DoMsg_GAMEMSG_RESPONSE_MYHOUSEUNITLIST(cltMsg* pclMsg, SI32 id);			// ������ �⺻������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITLIST(cltMsg* pclMsg, SI32 id);			// ������ �⺻������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITLIST_DETAIL(cltMsg* pclMsg, SI32 id);	// ������ �������� �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_HOUSECANCELLATIONPENALTYMONEY(cltMsg* pclMsg, SI32 id);	// �ؾ��ϴµ� �󸶸� �����ؾ� �ϴ��� ������ �޴´�.


	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE(cltMsg* pclMsg, SI32 id);	// ���� ����
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO(cltMsg* pclMsg, SI32 id);	// �� ��ü ���� �ޱ�
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS(cltMsg* pclMsg, SI32 id);		// �� ��ü
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSNOTIFY(cltMsg* pclMsg, SI32 id);	// �� ��ü �Ǿ����� ���� ����鿡�� �˸�
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEIN(cltMsg* pclMsg, SI32 id);		// ������� ���� ������ �ִ´�. 
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITNAMECHANGE(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// ���, ���, ���� ���� ���
	//--------------------------------------
	// Client-Agriculture.cpp
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTUREAUTOGAIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTSNOTIFY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTUREPAYRENTFEE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTURESTART(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTUREFORNOTRENTMAN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AGRICULTURELEASELEFTTIME(cltMsg* pclMsg, SI32 id);



	//--------------------------------------
	// ����
	//--------------------------------------
	// Client-Fishing.cpp
	void DoMsg_GAMEMSG_RESPONSE_FISHINGSTART(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTSNOTIFY(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// ���
	//--------------------------------------
	// Client-Farming.cpp
	void DoMsg_GAMEMSG_RESPONSE_FARMINGGETPRODUCTS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FARMINGGETPRODUCTSNOTIFY(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// ä��
	//--------------------------------------
	// Client-Mining.cpp
	void DoMsg_GAMEMSG_RESPONSE_MININGGETPRODUCTS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MININGGETPRODUCTSNOTIFY(cltMsg* pclMsg, SI32 id);




	void DoMsg_GAMEMSG_RESPONSE_POSTOFFICE_RECVITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_POSTOFFICE_RECVMONEYLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_POSTOFFICE_RECVMSGLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_POSTOFFICE_GETRECORD(cltMsg* pclMsg, SI32 id);

	//[����] ��ü �޽��� ������. => 2008-8-4
	void DoMsg_GAMEMSG_RESPONSE_POSTOFFICE_USER_LIST_GROUP(cltMsg* pclMsg , SI32 id);	//[����] ��ü �޽��� ������. ��ü�� ���� ��������Ʈ�� ����. => 2008-8-4 
	void DoMsg_GAMEMSG_RESPONSE_CHAR_NAME_CHECK(cltMsg* pclMsg , SI32 id);				//[����] ��ü �޽��� ������. ��ü�� ���� ����Ʈ�� �߰��� 1���� ������ ����. => 2008-8-4 

	//--------------------------------------
	// ������ ������ǰ�� ã�´�
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_GET_SAVEUSERITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GET_SAVEUSERITEMLIST(cltMsg* pclMsg, SI32 id);


	void DoMsg_GAMEMSG_RESPONSE_LIST_DELETEALL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LIST_DELITEM(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// [��] �ü�Ȯ�� 2008-07-18
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_MARKETCONDITIONS(cltMsg* pclMsg, SI32 id);


	//--------------------------------------
	// ������ 
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTADD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HUNTMONSTEROUT(cltMsg* pclMsg, SI32 id);
	// ������ ��庥Ƽ���� ���Ѵ�. 
	void DoMsg_GAMEMSG_RESPONSE_HUNTADDRATE(cltMsg* pclMsg, SI32 id);


	//-------------------------------------
	// ���� 
	//-------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_MARKETORDER(cltMsg* pclMsg, SI32 id);



	//--------------------------------------
	// �纹��
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_HORSEMARKET_OUTHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HORSEMARKET_MYACCOUNT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HORSEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HORSEMARKET_SELLHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HORSEMARKET_BUYHORSE(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// �Ű� 
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_MYORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_SELL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_BUY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATEMARKET_DETAILINFO(cltMsg* pclMsg, SI32 id);


	//--------------------------------------
	// �忹��
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SUMMONMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONMARKET_MYORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONMARKET_SELL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONMARKET_BUY(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// �񺯻�
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONHEROMARKET_MYORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONHEROMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONHEROMARKET_SELL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SUMMONHEROMARKET_BUY(cltMsg* pclMsg, SI32 id);


	//--------------------------------------
	// ����
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_LAND_UNITLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LAND_UNITDETAIL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LAND_APPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LAND_RENT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LAND_DELAPPLYER(cltMsg* pclMsg, SI32 id);


	//--------------------------------------
	// ����
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_MINE_UNITLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MINE_UNITDETAIL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MINE_APPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MINE_RENT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MINE_DELAPPLYER(cltMsg* pclMsg, SI32 id);

	//--------------------------------------
	// ���ڽ�
	//--------------------------------------
	//#if defined(_LEON_FEAST_EFFECT)
	void DoMsg_GAMEMSG_RESPONSE_FEAST_USEEFFECT(cltMsg* pclMsg, SI32 id); // ��������Ʈ ����ϱ�
	//#endif
	//[����] ��ƼȦ.
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_TOTAL_INFO(cltMsg* pclMsg, SI32 id);									// ��Ƽ�� ��ü ����.	=> 2008. 3. 15
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_RESERVATION(cltMsg* pclMsg, SI32 id);									// ��Ƽ�� ����.			=> 2008. 3. 15
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_ADD_PRESENT(cltMsg* pclMsg, SI32 id);									// ��Ƽ�� ���� ���.	=> 2008. 3. 15
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_GET_COSTUME(cltMsg* pclMsg, SI32 id);				
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION_LIST(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_ADD_DECORATION(cltMsg* pclMsg, SI32 id);			
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_GIVEITEM(cltMsg* pclMsg, SI32 id);									// �����ֱ�.
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_USEEFFECT(cltMsg* pclMsg, SI32 id);									// ����.
	
	void DoMsg_GAMEMSG_RESPONSE_PARTYHALL_DECORATION_LIST(cltMsg* pclMsg, SI32 id);								// ��Ĺ� ����Ʈ �ֱ�.



	//--------------------------------------
	// ������ȸ
	//--------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_SUGGEST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_VOTE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_ACCEPTCANDIDATE(cltMsg* pclMsg, SI32 id);


	void DoMsg_GAMEMSG_NOTICE_GENERALMEETING(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_SETVILLAGEUPGRADE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_STOCKOFFERINGINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_EXCHANGESTOCK(cltMsg* pclMsg, SI32 id);

	//---------------------------------------
	// �ý��� 
	//---------------------------------------
	// Client-System.cpp
	void DoMsg_GAMEMSG_RESPONSE_USERNUM(cltMsg* pclMsg, SI32 id);			// ���� ���� �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_SECRETCHATRESULT(cltMsg* pclMsg, SI32 id);	// �Ӹ� ä�� ����� �޴´�. 
	void DoMsg_GAMEMSG_RESPONSE_CHAT(cltMsg* pclMsg, SI32 id);				// ä�� ������ �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_HEADCHAT(cltMsg* pclMsg, SI32 id);			// �Ӹ����� ������ �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id);	// ä�� ä�� ���� ������ �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_ACCEPTSECRETCHATCHANNEL(cltMsg* pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NPCPOS(cltMsg* pclMsg, SI32 id);				// NPC��ġ�� �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_USERCHARINFO(cltMsg* pclMsg, SI32 id);		// ����� ���� ����. 
	void DoMsg_GAMEMSG_RESPONSE_USERCHARITEMINFO(cltMsg* pclMsg, SI32 id);	// ����� ������ ����. 
	void DoMsg_GAMEMSG_RESPONSE_USERCHARITEMINFO2(cltMsg* pclMsg, SI32 id);	// ����� ������ ����. 
	void DoMsg_GAMEMSG_RESPONSE_ACCOUNTINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRODUCTPRICE(cltMsg* pclMsg, SI32 id);		// ��ǰ ���� ���� ó��. 
	void DoMsg_GAMEMSG_RESPONSE_GMGIVEMONEY(cltMsg* pclMsg, SI32 id);		// ����� �� �ֱ� ó�� 
	void DoMsg_GAMEMSG_RESPONSE_NEWS(cltMsg* pclMsg, SI32 id);				// ���� ó��. 
	void DoMsg_GAMEMSG_RESPONSE_ASKLIST(cltMsg* pclMsg, SI32 id);			// ���� ����Ʈ ó��. 
	void DoMsg_GAMEMSG_RESPONSE_ENEMYCAPTURE(cltMsg* pclMsg, SI32 id);		// ���� ���� ���� 
	void DoMsg_GAMEMSG_RESPONSE_ENEMYCAPTUREALL(cltMsg* pclMsg, SI32 id);	// ���� ��� ���� ���� 
	void DoMsg_GAMEMSG_RESPONSE_NOTICELOGIN(cltMsg* pclMsg, SI32 id);		// �α��� ����.
	void DoMsg_GAMEMSG_RESPONSE_SKILLMASTERLIST(cltMsg* pclMsg, SI32 id);	// ���� ��� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEDETAILINFO(cltMsg* pclMsg, SI32 id);	// ���� �� ���� �뺸.  
	void DoMsg_GAMEMSG_RESPONSE_RAREITEMMADE(cltMsg* pclMsg, SI32 id);		// ��ǰ ���� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_RECOMMENDREWARD(cltMsg* pclMsg, SI32 id);	// ��õ�� ���� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_FAMELEVELREWARD(cltMsg* pclMsg, SI32 id);	// ������ ���� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_BIGWARITEM(cltMsg* pclMsg, SI32 id);			// ��� ����ǰ ���� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_GOODHORSE(cltMsg* pclMsg, SI32 id);			// �� ���� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_NOADDHORSE(cltMsg* pclMsg, SI32 id);			// ���߰� ���� �뺸.
	void DoMsg_GAMEMSG_RESPONSE_HIGHSUMMON(cltMsg* pclMsg, SI32 id);			// ���� ��ũ�� ��ȯ�� ���� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_HOPETOQUIT(cltMsg* pclMsg, SI32 id);			// �α׾ƿ� ����� ���� ����
	void DoMsg_GAMEMSG_RESPONSE_HOPETOFRONT(cltMsg* pclMsg, SI32 id);		// ����Ʈ�� �ǵ��ư���

	void DoMsg_GAMEMSG_RESPONSE_VILLAGEGENERALMEETING(cltMsg* pclMsg, SI32 id);		//[�߰� : Ȳ���� 2008. 2. 21 => ���� ������ȸ �ߵ� ���� ���� �뺸.]
	

	void DoMsg_GAMEMSG_RESPONSE_USERLEVELUP(cltMsg* pclMsg, SI32 id);		// �ٸ� ����� ���������� �뺸 
	void DoMsg_GAMEMSG_RESPONSE_SERVERINFO(cltMsg* pclMsg, SI32 id);			// ���������� �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_WARVILLAGE(cltMsg* pclMsg, SI32 id);			// �������� ���۰� ���Ḧ �˸���.
	void DoMsg_GAMEMSG_RESPONSE_BONUSTIME(cltMsg* pclMsg, SI32 id);			// ���ʽ� Ÿ����  ���۰� ���Ḧ �˸���.
	void DoMsg_GAMEMSG_RESPONSE_SETGAMEDELAY(cltMsg* pclMsg, SI32 id);		// ������ ���� �ӵ��� ���ؿ´�. 
	void DoMsg_GAMEMSG_RESPONSE_LETTER(cltMsg* pclMsg, SI32 id);				// ������ �޾Ҵ�. 
	void DoMsg_GAMEMSG_RESPONSE_ACCOUNTLETTER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY(cltMsg* pclMsg, SI32 id); // ������ �������� 3�� �̸����� �뺸 �޾Ҵ�.
	void DoMsg_GAMEMSG_RESPONSE_HUNTINGINFO(cltMsg* pclMsg, SI32 id);		// �Ұ��縮 ��� �̺�Ʈ ����. 
	void DoMsg_GAMEMSG_RESPONSE_HUNTINGREWARD(cltMsg* pclMsg, SI32 id);		// �Ұ��縮 ��� ������ ���� 
	void DoMsg_GAMEMSG_RESPONSE_GOGUINFO(cltMsg* pclMsg, SI32 id);			// ���� ���� ��� �̺�Ʈ ����. 
	void DoMsg_GAMEMSG_RESPONSE_GOGUREWARD(cltMsg* pclMsg, SI32 id);			// ���� ���� ���  ������ ���� 
	void DoMsg_GAMEMSG_RESPONSE_OSAKAINFO(cltMsg* pclMsg, SI32 id);			// ����ī�� ����. 
	void DoMsg_GAMEMSG_RESPONSE_OSAKAREWARD(cltMsg* pclMsg, SI32 id);		// ����ī�� ���� 
	void DoMsg_GAMEMSG_RESPONSE_KANGHWADOINFO(cltMsg* pclMsg, SI32 id);		// ��ȭ�� ����. 
	void DoMsg_GAMEMSG_RESPONSE_KANGHWADOREWARD(cltMsg* pclMsg, SI32 id);	// ��ȭ�� ���� 

	// �����Ǽ� 
	void DoMsg_GAMEMSG_RESPONSE_GETBYUNGZOINFO(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_GETGONGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETHYUNGZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETHOZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETIZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETYEZOINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETGOONZUINFO(cltMsg* pclMsg, SI32 id);
	
	void DoMsg_GAMEMSG_RESPONSE_GOONZU_GETBONUSTIME(cltMsg* pclMsg, SI32 id);	// ���ְ� ������ ���� ���ʽ� Ÿ�� ����

	void DoMsg_GAMEMSG_RESPONSE_GETANGELAPPLYERLIST(cltMsg* pclMsg, SI32 id); // ��ȣõ�� ��û�� ��� ��û
	void DoMsg_GAMEMSG_RESPONSE_GETANGELLIST(cltMsg* pclMsg, SI32 id); // ��ȣõ�� ��� ��û
	void DoMsg_GAMEMSG_RESPONSE_SETANGELAPPLYER(cltMsg* pclMsg, SI32 id); // ��ȣõ�� ��� ��û
	void DoMsg_GAMEMSG_RESPONSE_SETANGEL(cltMsg* pclMsg, SI32 id); // ��ȣõ�� �Ӹ� ��û

	void DoMsg_GAMEMSG_RESPONSE_GETPOLICELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETPOLICE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_GETCRIMINALLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETCRIMINAL(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_GETCHANGEDNAME(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING_ASK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING_TIMEUPDATE(cltMsg* pclMsg, SI32 id);


	void DoMsg_GAMEMSG_RESPONSE_ENCHANTITEMSTARTOREND(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ENCHANTOTHERSHOW(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ENCHANTOTHERPRICE(cltMsg* pclMsg, SI32 id);


	void DoMsg_GAMEMSG_RESPONSE_SERVEREVENTINFO(cltMsg* pclMsg, SI32 id);	// ������ �̺�Ʈ ������ �����Ѵ�. 
	void DoMsg_GAMEMSG_RESPONSE_BOSSAPPEAR(cltMsg* pclMsg, SI32 id);			// ���� ���� ������ �˷��ش�. 
	void DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPMAKEINFO(cltMsg* pclMsg, SI32 id);	// ���� ���� �����Ƿ� ������ ����Ѵ�. 
	void DoMsg_GAMEMSG_RESPONSE_LEVELUP(cltMsg* pclMsg, SI32 id);			// Ư�� ������� ������ �ö����� �˸���. 
	void DoMsg_GAMEMSG_RESPONSE_LEVELUPNOTICE(cltMsg* pclMsg, SI32 id); //KHY - 1205 
	void DoMsg_GAMEMSG_RESPONSE_PERSONAL_LOG(cltMsg* pclMsg, SI32 id);		// ��ڰ� ������� �α׸� ��û�Ѵ�.
	void DoMsg_GAMEMSG_RESPONSE_NOTICEADMIN(cltMsg* pclMsg, SI32 id);		// �߿�����Ѵ�
	void DoMsg_GAMEMSG_RESPONSE_INSTANCEMAPINFO(cltMsg* pclMsg, SI32 id);

	//	void DoMsg_GAMEMSG_RESPONSE_ITEMINFOGET(cltMsg* pclMsg, SI32 id);	// �������� ������ ���´�. ����ũ �� ���̳ʸ���

	// Client-LogIn.cpp
	void DoMsg_GAMEMSG_RESPONSE_LOGIN(cltMsg* pclMsg, SI32 id);			// �α���. 
	void DoMsg_GAMEMSG_RESPONSE_LOGINMANY(cltMsg* pclMsg, SI32 id);		// �α���. (���� ĳ����. ) 
	void DoMsg_GAMEMSG_RESPONSE_LOGOUT(cltMsg* pclMsg, SI32 id);			// �α׾ƿ�.  

	void DoMsg_GAMEMSG_RESPONSE_RECOMMENDPERSON(cltMsg* pclMsg, SI32 id);	// ��õ�� ����
	void DoMsg_GAMEMSG_RESPONSE_RECOMMENDPERSONAVAILABLE(cltMsg* pclMsg, SI32 id);	// ��õ�� ��õ ����

	void DoMsg_GAMEMSG_RESPONSE_BLACKARMYAPPLY(cltMsg* pclMsg, SI32 id);	// ���Ǳ��� �̺�Ʈ ��û
	void DoMsg_GAMEMSG_RESPONSE_BLACKARMYWAR(cltMsg* pclMsg, SI32 id);	// ���Ǳ��� �̺�Ʈ ��û

	void DoMsg_GAMEMSG_RESPONSE_BLACKARMY_RANKINFO(cltMsg* pclMsg, SI32 id);	// ���Ǳ��� �̺�Ʈ ��û

	void DoMsg_GAMEMSG_RESPONSE_BLACKARMY_MVPEFFECT(cltMsg* pclMsg, SI32 id);	// ���Ǳ��� �̺�Ʈ ��û

	void DoMsg_GAMEMSG_RESPONSE_BLACKWAR(cltMsg* pclMsg, SI32 id);	// ���Ǳ��� ��ü�̺�Ʈ

	void DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM(cltMsg* pclMsg, SI32 id);	// PersonID�� ������ Person �̸��� �޾ƿ�
	void DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM_LIST(cltMsg* pclMsg, SI32 id);	// PersonID�� ������ Person �̸��� �޾ƿ�
	void DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM_RECIEVE(cltMsg* pclMsg, SI32 id);	// PersonID�� ������ Person �̸��� �޾ƿ�
	void DoMsg_GAMEMSG_RESPONSE_OPENTREASUREBOX(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_KINGGURIINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SANTARACCOONINFO(cltMsg* pclMsg, SI32 id);		//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ �޽���.]
	void DoMsg_GAMEMSG_RESPONSE_KITERACCOONINFO(cltMsg* pclMsg, SI32 id);		// [����] 2008.01.13 ���� �̺�Ʈ ī��Ʈ ���� �޽���
	void DoMsg_GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX(cltMsg* pclMsg, SI32 id);	// [����] ���� ���ڸ� �������� ����������� ���Դ�
	

	//------------------------------------------------
	// Item
	//------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_NPCREPAIRPRICE(cltMsg* pclMsg, SI32 id);			// NPC���� ���� ����. 
	void DoMsg_GAMEMSG_RESPONSE_MAKEITEMSWITCH(cltMsg* pclMsg, SI32 id);			// �������ϸ��̼��� �����ϰ� ������.
	void DoMsg_GAMEMSG_RESPONSE_EXCHANGEWEAPON(cltMsg* pclMsg, SI32 id);			// Weapon�� Active ���¸� �ٲ۴�.
	void DoMsg_GAMEMSG_RESPONSE_EXCHANGECLOTHES(cltMsg* pclMsg, SI32 id);			// Clothes �� Active ���¸� �ٲ۴�

	void DoMsg_GAMEMSG_RESPONSE_UPGRADEITEM(cltMsg* pclMsg, SI32 id);				// ������ ���׷��̵忡 ���� ����( �Ϲ� -> ȣǰ -> ��ǰ -> �ű� )  - Ȥ�θ� ���� �̿���� ����ؼ�.
	void DoMsg_GAMEMSG_RESPONSE_PERFORMANCEUPGRADEITEM(cltMsg* pclMsg, SI32 id);	// ������ ���� ��� ��Ŵ ( ���� ������ )

	void DoMsg_GAMEMSG_RESPONSE_ENCHANTITEMDLG(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PERSONMAKEITEMSWITCH(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MAKEITEMDLG(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ISSKILLITEM(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_PREMIUM_INFO(cltMsg* pclMsg, SI32 id);				// �����̾� ������ �޴�.

	void DoMsg_GAMEMSG_RESPONSE_CRYSTALITEMINFO(cltMsg* pclMsg, SI32 id);			// ����ü ������ ������Ʈ �Ѵ�.( �ϴ� ��������)

	void DoMsg_GAMEMSG_RESPONSE_SUMMONCHANGEITEM(cltMsg* pclMsg, SI32 id);			// [����] ��ȯ�� ������� : ��ȯ�� ��� ����Ǿ���

	//------------------------------------------------
	// �ǹ�����
	//------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEINFOSTRINFO(cltMsg* pclMsg, SI32 id);	// ���� �� ������ �ǹ� ���� �뺸. 


	//------------------------------------------------
	// ��ǰ �ֱ� (XBOX, ������, �ý� ��� )
	//------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_GIFTNT(cltMsg* pclMsg, SI32 id);

	//#if defined(_CITYHALL_BANKRUPTCY)
	//------------------------------------------------
	// ���� �������� ���� ���� ����
	//------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE(cltMsg* pclMsg, SI32 id);
	//#endif

	//cyj �޼��� �ڵ鷯 �߰�
	void DoMsg_GAMEMSG_RESPONSE_USERORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CLIENTCHARUNIQUE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NOTICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHARLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DELUSERCHAR(cltMsg* pclMsg, SI32 id);//�ɸ��ͻ���
	void DoMsg_GAMEMSG_RESPONSE_PREDELUSERCHAR(cltMsg* pclMsg, SI32 id);//�ɸ��ͻ��������Ⱓ
	void DoMsg_GAMEMSG_RESPONSE_MAKENEWCHAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGESTRUCT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BUILDSTRUCTURE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DESTROYSTRUCTURE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGENOTICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGELEVELDETAILINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RANK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REALESTATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STRINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETTAXLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETDIVIDENDLIST(cltMsg* pclMsg, SI32 id);
	//void DoMsg_GAMEMSG_RESPONSE_HIRENPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RESIDENTAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RESIDENTLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RESIDENTINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_UPDATERESIDENTAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ALLSTRCHIEFINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STOCKPRICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETVILLAGEINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETNOWVILLAGEWARINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETVILLAGEMARK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RESIDENTSLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RESIDENTLOGIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DECLAREWAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CANCELDECLAREWAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETSYMBOLSTATUS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETCASTLESTATUS(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEWARRESULT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEWARRESULT_FOR_VILLAGEMEMBER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETSTRNOTICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ENDVILLAGEWAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_INVESTLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHIEFINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REPAIRSTRUCTURE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGEBOARD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_EVENT_INSERTMATERIAL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_EVENT_MATERIALLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_EVENT_MATERIALCOMPLETE(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_EVENT_COMPLETEBUILD(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_SERVERRTN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NOTICE_QUEST(cltMsg* pclMsg, SI32 id);

	//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
	void DoMsg_GAMEMSG_RESPONSE_CHARSERVERRTN(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_DATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_LOWPRICESTOCKORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HOUSEAPPLYERLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STGITEMINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_STGINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITSTABLECREATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEINFOSET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEEATFOOD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WEATHER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GAMEMASTERLEVEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RIDEHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_UNRIDEHORSE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DELHOUSEAPPLYER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MARKETSELLINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DEALTHPENALTYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_REVIVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ITEMDROP(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WHISPERCHAT_REJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_REJECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ANOTHERAUTH(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NOTGAMEPOTAUTH(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHANGE_CHARNAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHANGE_CHARKIND(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CANNOTLOGIN_AGE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CANNOTLOGIN_ERROR(cltMsg* pclMsg, SI32 id);	
	void DoMsg_GAMEMSG_RESPONSE_GAMEDISCONNECT_AGE(cltMsg* pclMsg, SI32 id);	// �����߿� �������� üũ�� (PCK - 2007.09.19)
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETINGLETTER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_PARTICIPATE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_CHAT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_CHATJOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GENERALMEETING_CHATOUT(cltMsg* pclMsg, SI32 id);

	//Client-WorldMoney
	void DoMsg_GAMEMSG_RESPONSE_SETWORLDMONEY_BUYDLG(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DISTRIBUTION_WORLDMONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_TRADELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_SELLORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_BUYORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_CANCELORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_SET_CHAR(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_SET_SELLORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_CANCEL_SELLORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_SET_BUYORDER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_LISTINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_SELLINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_MYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_SAVEDACU_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU(cltMsg* pclMsg, SI32 id);

	// WorldPassport( ���� ���� )
	void DoMsg_GAMEMSG_RESPONSE_WORLDPASSPORT_SET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WORLDPASSPORT_EXTEND(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_COUNTRYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_USERLISTBYCOUNTRY(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_SERVERTIME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NOTICECOUNTRYUSERMAKE(cltMsg* pclMsg, SI32 id);

	// 20�̸� ���� ���� �뺸. 
	void DoMsg_GAMEMSG_RESPONSE_LOWLEVELLIST(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_ADDBUF(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DELETEBUF( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SETTEACHERPOINT( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_SETITEMTYPEINFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SETEMOTICON( cltMsg* pclMsg, SI32 id );

	void DoMSg_GAMEMSG_RESPONSE_GAME_GUARD_AUTH( cltMsg * pclMsg , SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_MYPUCHIKOMIURL( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_USERPUCHIKOMIURL( cltMsg* pclMsg, SI32 id );
	// Guild
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CREATEGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_DESTROYGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_JOINGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CONFIRMJOINGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_LEAVEGUILD( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CHANGEVILLAGE( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_GETGUILDLIST( cltMsg*pclMsg,SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_GETGUILDINFO(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_SETSECONDMASTER(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_GIVEGUILDMONEY(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_SETSTRFEERATE(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CHANGESTATUS(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_SETMARK(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CHANGENAME(cltMsg*pclMsg,SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILD_CHANGEMASTER( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_RESERVELIST( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_APPLYRESERVE( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_APPLYTOENEMY( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_START( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDHUNTMAPGUILDWAR_START( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDHUNTMAPGUILDWAR_ADDKILLPOINT( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDHUNTMAPGUILDWAR_MAPUSERLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_END( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_KILLPOINT( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDDUNGEON_APPLYLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDDUNGEON_STATUS( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_MEMBERLIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILD_GETVILLAGELIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDWAR_RECOMMANDLIST( cltMsg* pclMsg, SI32 id );
	//void DoMsg_GAMEMSG_RESPONSE_GUILD_CLOSEGUILD( cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GACHAPRODUCT_LIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GACHABUY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GACHA2PRODUCT_LIST( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_CARRYOVER_GACHA_LIST( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_CARRYOVER_SELECTPRODUCT_LIST( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_RESERVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_RESERVELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_START(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_END(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_SETINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_INFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_MOFUMOFUEVENT_MAMAMOFUMOFU(cltMsg* pclMsg, SI32 id);

	// [����] ���� �̺�Ʈ - ���� ����
	void DoMsg_GAMEMSG_RESPONSE_MONSTER_ATTACK_START(cltMsg* pclMsg, SI32 id);
	// [����] ���� �̺�Ʈ - ���� ���� - ���� ������ ���� �뺸��
	void DoMsg_GAMEMSG_RESPONSE_MONSTER_ATTACK_REWARD(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_SYSTEMREWARDLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECIEVESYSTEMREWARD(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_DEMANDATTEND(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_ATTEND(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_CREATEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_DESTROYEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_INVITEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_JOINEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SECEDEEMPIRE(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_UPDATEEMPIREINFO(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_EMPIREINFO(cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SETEMPIREMONEY(cltMsg* pclMsg, SI32 id );
	
	
	void DoMsg_GAMEMSG_RESPONSE_AUTOMACRO_CHECK(cltMsg* pclMsg, SI32 id );		//[�߰� : 2007. 12. 3 => 4���������α׷� ���� Ŭ���̾�Ʈ �޽��� �߰�.]
	void DoMsg_GAMEMSG_RESPONSE_AUTOMACRO_ON_OTHER(cltMsg* pclMsg, SI32 id);	//[�߰� : Ȳ���� 2007. 12. 10 => �������α׷� �߰� ���� �޽���.]

	void DoMsg_GAMEMSG_RESPONSE_NEWYEAR_BTN(cltMsg* pclMsg, SI32 id);			//[�߰� : Ȳ���� 2007. 12. 11 => �ų� ��ư �߿��� �޽��� ó��.]

	void DoMsg_GAMEMSG_RESPONSE_TRANSFORM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_TRANSFORMINFO(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_MAXSYNCRO_ATTAINMENT(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_TRANSFORM_LIMIT_TIME(cltMsg* pclMsg, SI32 id);		//[�߰� : Ȳ���� 2008. 1. 9 => ������ �ð��� 30�ʰ� �ȵǼ� ���� ���� �޽��� ����.]	

	void DoMsg_GAMEMSG_RESPONSE_CREATEBANKACCOUNT_CANCEL(cltMsg* pclMsg, SI32 id);	//[�߰� : Ȳ���� 2008. 1. 9 => ���� �������� 0�̾ ���¸���� ���� �޽��� ����.]	
	
	//----------------------------------------------------------------------------------
	//	�߰� : Ȳ���� 2008. 1. 9 => �ν���Ʈ����.
	//----------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_STATUS(cltMsg* pclMsg, SI32 id);		//[�߰� : Ȳ���� 2008. 1. 10 => �δ� ���� ���� ����.]	

	void DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS(cltMsg* pclMsg, SI32 id);	//[�߰� : Ȳ���� 2008. 1. 10 => �δ� ���� ���� ����.]	

	void DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_REWARD(cltMsg* pclMsg, SI32 id);		//[�߰� : Ȳ���� 2008. 1. 11 => �δ� ���� ����.]	
	
	void DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_TOP_CHANGE(cltMsg* pclMsg, SI32 id);	//[�߰� : Ȳ���� 2008. 1. 17 => �δ� �ְ� ���� ���� �˸�.]	
	//--------------------------------------------------------------------------------------
	//���� ���� 
	//--------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_HOFList(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RakingList(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_INSTANTMAP_GATEINFO(cltMsg* pclMsg, SI32 id);

	//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� �޽���.]  
	void DoMsg_GAMEMSG_RESPONSE_BLACK_WAR_REFORM_CHAR_RESULT(cltMsg* pclMsg, SI32 id);
	
	//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� �޽���.]  
	void DoMsg_GAMEMSG_RESPONSE_BLACK_WAR_REFORM_VILLAGE_RESULT(cltMsg* pclMsg, SI32 id);

	//*******************************************************************************************
	//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ���� �޽���. S->C]
	void DoMsg_GAMEMSG_RESPONSE_SPACE_BOX_LIST( cltMsg* pclMsg, SI32 id );
	
	//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ����(����) �޽���. S->C]
	void DoMsg_GAMEMSG_RESPONSE_TRESURE_BOX_LIST( cltMsg* pclMsg, SI32 id );

	//[�߰� : Ȳ���� 2008. 1. 30 =>  ���� ���� ���� �޽���. S->C]
	void DoMsg_GAMEMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM( cltMsg* pclMsg, SI32 id );

	//[�߰� : Ȳ���� 2008. 1. 30 =>  ���� ���� ȸ�� �޽��� ó��. S->C]
	void DoMsg_GAMEMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM( cltMsg* pclMsg, SI32 id );

	// [����] �������� ������ ��� �߰�
	void DoMsg_GAMEMSG_RESPONSE_USE_SPACEBOX_ITEM( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_USE_TREASURE_ITEM( cltMsg* pclMsg, SI32 id );
	//*******************************************************************************************	
	
	//[�߰� : Ȳ���� 2008. 2. 28 =>  ��Ƽ��Ʈ �޽��� ó��. S->C]
	void DoMsg_GAMEMSG_RESPONSE_ARTIFACT_MIXTURE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ARTIFACT_REMOVE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ARTIFACT_SLOT_CREATE( cltMsg* pclMsg, SI32 id );
	//*******************************************************************************************	
	
	// [����] CRCüũ���� �������� üũ �޽����� ������� ��Ŷ�� �������
	void DoMsg_GAMEMSG_RESPONSE_FILECRCCHECK( cltMsg* pclMsg, SI32 id );
	// [����] ������ : Ŭ���� ���ʽ��� �������� ȹ���ߴٴ� �޽���
	void DoMsg_GAMEMSG_RESPONSE_INSTANTDUNGEON_PARTY_CLEAR( cltMsg* pclMsg, SI32 id );
	// [����] ������ : �������� ��Ÿ���ٴ� �޽���
	void DoMsg_GAMEMSG_RESPONSE_PIRATESHIP_APPEAR( cltMsg* pclMsg, SI32 id );
	
	//[����] �ǰ������� ���� ��Ų��. => 2008-4-6
	void DoMsg_GAMEMSG_RESPONSE_HEALTH_CHANGE( cltMsg* pclMsg, SI32 id );

	//-----------------------------------------------------------------------
	// �ɸ��� �ɼ� ����
	//---------------	---------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_CHAR_OPTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CHAR_GET_OPTION(cltMsg* pclMsg, SI32 id );	

	// [����] ������ ���� �̺�Ʈ �����귿 ������ Ŭ�� ó��. => 2008-6-10
	void DoMsg_GAMEMSG_RESPONSE_BUFF_ROULETTE( cltMsg* pclMsg, SI32 id );

	//	[��ȣ_BALANCECURRENCY] ���� ��Ŷ
	void DoMsg_GAMEMSG_RESPONSE_BALANCECURRENCY_BUFF( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_SET_HOMEPAGE_URL( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GET_HOMEPAGE_URL( cltMsg* pclMsg, SI32 id );

	// [����] ���� �̺�Ʈ ó�� �Լ�. (S->C) => 2008-6-19 
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_RANK_INFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_SERVER_INFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_DAILY_EVENT_SERVER_INFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEMAP_BONUS_FIGURE( cltMsg* pclMsg, SI32 id );

	// [����] ���� �̺�Ʈ ����Ʈ ���� �Լ�
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_START( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_RUNINFO( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEDUNGEON_RUNINFO( cltMsg* pclMsg, SI32 id );

	// [����] 2�� ��í ������ ź���ҳ�
	/*void DoMsg_GAMEMSG_RESPONSE_TANWANGGIRL(cltMsg* pclMsg, SI32 id);*/
	
	// [���] ��ȯ�� ���¹̳� ����
	void DoMsg_GAMEMSG_RESPONSE_SUMMON_STPCHARGE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_REQUEST_EVENTTIME_UPDATE( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_CHECKPROCESS( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_CHECKPROCESS_RESULT( cltMsg* pclMsg, SI32 id );

	//[����] ȣ�ڻ��� => 2008-9-16
	void DoMsg_GAMEMSG_RESPONSE_AMBER_BOX_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_CHAR_ROULETTE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VILLAGE_RESIDENT_INVITE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_PVP_FILED(cltMsg* pclMsg, SI32 id);// NEW PVP - �ռ��� 2008.10.08
	void DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_INFOGET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE(cltMsg* pclMsg, SI32 id);
	
	void DoMsg_GAMEMSG_RESPONSE_HELP_ME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HELP_ME_OK(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_HELP_CHAT_MSG(cltMsg* pclMsg, SI32 id);
	
	//[����] ����� => 2008-11-05
	void DoMsg_GAMEMSG_RESPONSE_QUESTION_LIST_GET( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_QUESTION_CONTENTS_GET( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE_RESULT( cltMsg* pclMsg, SI32 id );

	void DoMsg_GAMEMSG_RESPONSE_SETMUTE( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_MUTELIST( cltMsg* pclMsg, SI32 id );

	//[���] �ų� �귿
	void DoMsg_GAMEMSG_RESPONSE_DIVINATION_ROULETTE( cltMsg* pclMsg, SI32 id );

	//[����] ������ npc���� Ÿ�Ժ� �������� ������ ����Ʈ�� �޴´�.
	void DoMsg_GAMEMSG_RESPONSE_ELIXIR_NPC_ITEM_TYPE_LIST_GET( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_ELIXIR_SET( cltMsg* pclMsg, SI32 id );

	//�߷�Ÿ�� ���� ���� ����
	void DoMsg_GAMEMSG_RESPONSE_VALENTINE_INFO_GET(cltMsg* pclMsg, SI32 id);
	//�߷�Ÿ�� ���� ���� Ŀ������
	void DoMsg_GAMEMSG_RESPONSE_VALENTINE_REQUEST(cltMsg* pclMsg, SI32 id);
	// ������ �Ǿ���� �� �� Ŀ���̳�? �ַγ� ����ƺ��ƿ� ����
	void DoMsg_GAMEMSG_RESPONSE_VALENTINE_RUSOLO_COUPLE_ONTIME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINE_OPENDLG(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINE_PRIZEGET(cltMsg* pclMsg, SI32 id);

	// [����] ���ο� ���û��� �������� �޾Ҵ�
	void DoMsg_GAMEMSG_RESPONSE_NEWSELECTBOX_SELECT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWSELECTBOX_GETITEM(cltMsg* pclMsg, SI32 id);

	
	//=============================================================================================
	// [����] ���ո���.
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SELL_NEWMARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BUY_NEWMARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECALL_NEWMARKET(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_NEWMARKETACCOUNT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWMARKETITEMLIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GETFROMNEWMARKET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWSELLITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWBUYITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SETNEWMARKETFEE(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_PERSONNAME_SERIALID(cltMsg* pclMsg, SI32 id);		// SerialID�� ������ Person �̸��� �޾ƿ�

	//=============================================================================================
	// [����] ���� ȹ���� ����
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_Request_Warp(cltMsg* pclMsg, SI32 id);	// ������� ����� ���� ���θ� ���� ����.
	void DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_Top10( cltMsg* pclMsg, SI32 id );		// // ������� ����� �ʺ� ž10
	void DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_END( cltMsg* pclMsg, SI32 id);
	
	void DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_TIEM( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_HaveMap( cltMsg* pclMsg, SI32 id );
	void DoMsg_GAMEMSG_RESPONSE_GUILDHUNTMAPGUILDWAR_SENDMATCHINGRESULT( cltMsg* pclMsg, SI32 id );

	
	
	//=============================================================================================
	// [����] ���θ���
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_PROMOTERNPC_GIVE_ITEM_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PROMOTER_INFO_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PROMOTER_URL_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PROMOTER_SET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECOMMEND_INTRODUCE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECOMMENDEE_INTRODUCE(cltMsg* pclMsg, SI32 id);	

	//=============================================================================================
	// [����] ��ȥ �ý���
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_PROPOSE_QUESTION(cltMsg* pclMsg, SI32 id);	// �������� ����
	void DoMsg_GAMEMSG_RESPONSE_SET_MARRY(cltMsg* pclMsg, SI32 id);			// ��ȥ�ߴ�
	void DoMsg_GAMEMSG_RESPONSE_GET_MARRY_INFO(cltMsg* pclMsg, SI32 id);	// ��ȥ���� ���� �ޱ�
	void DoMsg_GAMEMSG_RESPONSE_MARRY_ITEMGET_SET(cltMsg* pclMsg, SI32 id);	// ��ȥ����� ������ ���� ��¥ ����
	void DoMsg_GAMEMSG_RESPONSE_MARRY_LOVE_SET(cltMsg* pclMsg, SI32 id);	// ��ȥ ������ ���� ����

	void DoMsg_GAMEMSG_RESPONSE_WEDDING_RESERVE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WEDDING_SIMPLELIST_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WEDDING_LIST_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_WEDDING_RESERVE_CANCEL(cltMsg* pclMsg, SI32 id);


	//	[��ȣ] ��ȭ�� ���� - ��밡�� �ݾ� ����
	void DoMsg_GAMEMSG_RESPONSE_BALANCECANUSECURRENCY(cltMsg* pclMsg, SI32 id);
	//	[��ȣ] GM�� ��û�� ��� ���� ��ȭ��
	void DoMsg_GAMEMSG_RESPONSE_GETBALANCECANUSECURRENCY(cltMsg* pclMsg, SI32 id);
	
	//=============================================================================================
	void DoMsg_GAMEMSG_RESPONSE_FAMILY_REQUEST_ADD_CHILDRENN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GET_FAMILYINFO(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FAMILY_UPDATE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_FAMILY_CHAT(cltMsg* pclMsg, SI32 id);


	//=============================================================================================
	// [����] ��ȣ ����
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_FELLOWSHIPSET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_CHANGENAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_DEAD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_GET(cltMsg* pclMsg, SI32 id);

	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_HOUSE_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SOULGUARD_HOUSE_CREATE(cltMsg* pclMsg, SI32 id);


	//=============================================================================================
	// [����] ���� ���ϱ� �̺�Ʈ //Switch_10MonthEvent_RacoonDodge
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_RESERVATION(cltMsg* pclMsg, SI32 id);			// ���࿡ ���� �亯-> ���� ������ٰ� ����Ʈ�� �����ִ°���.���� ������� �۾� ����. �߰� �ؾ���
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_WAIT5SECOND(cltMsg* pclMsg, SI32 id);			// 5�� ī��Ʈ �ض�
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_REQUEST_PLAYEVENT(cltMsg* pclMsg, SI32 id);			// ���� �Ǿ���. ���� �Ҳ���?
	
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_30SECOND(cltMsg* pclMsg, SI32 id);			// 30�� ī��Ʈ 
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_ROUNDCOUNT(cltMsg* pclMsg, SI32 id);			// ȭ�鿡 �ش� ���带 �����ش�.
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_30SECOND_CLEAR(cltMsg* pclMsg, SI32 id);			// 30�� ī��Ʈ  ���� 
	void DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR(cltMsg* pclMsg, SI32 id);			// ȭ�鿡 �ش� ���� ���� 

	//=============================================================================================
	// [����] �޸� ���� �ý���
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_DORMANCY_TAKEOUTEQUIPITEMINBOX(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_DORMANCY_REFRESHPOINTINFO(cltMsg* pclMsg, SI32 id);
	
	//  [8/12/2009 ��ȣ_GAWIBAWIBO] 
	void DoMsg_GAMEMSG_RESPONSE_GAWIBAWIBO_CHARGED_MONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GAWIBAWIBO_CALCULATE_RESULT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GAWIBAWIBO_NOTICE_RESULT(cltMsg* pclMsg, SI32 id);
	//void DoMsg_GAMEMSG_RESPONSE_GAWIBAWIBO_COUNT(cltMsg* pclMsg, SI32 id);

	//=============================================================================================
	// [����] ���Һ� ����
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_BOKBULBOK_CHECK_ENTERMAP_ENABLE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BOKBULBOK_CHECK_WAITLIST_ENABLE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BOKBULBOK_CHECK_ENTRYREQUEST_FAIL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_WAITLIST_ANSWER(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_WAITLIST_CANCEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_STAGESTART(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_STAGEFAIL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_WARPMAPQUESTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_NOTENOUGHMONEY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_STAGECLEAR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_GM_SHOWMONSTERTYPE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_10CLEARNOTICE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BBB_ALREADYRESERVED(cltMsg* pclMsg, SI32 id);
	
	//=============================================================================================
	// [����] ���ο� ������ �ý���
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_NEWNPCREPAIR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWITEMREPAIR(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_NEWITEMREPAIRREQUESTINFO(cltMsg* pclMsg, SI32 id);
	//-------------------------------------------------------------------------------------------------------------------
	//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	//-------------------------------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE__RACCOONEVENT_TOGOONZU(cltMsg* pclMsg, SI32 id);//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	void DoMsg_GAMEMSG_RESPONSE__GOONZURACCOONEVENT_SETINFO(cltMsg* pclMsg, SI32 id);//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

	
	//-------------------------------------------------------------------------------------------------------------------
	//[����] ��ų��
	//-------------------------------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_SET(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_DEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CURSEINFO(cltMsg* pclMsg, SI32 id);
	

	//=============================================================================================
	// [����] ��Ʋ�ξ�
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_NOTICERESULT(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_REMAINEDTIME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_STARTGAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_ENDGAME(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_POWERUPMODE(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_BATTLEROYAL_OPENSTADIUM(cltMsg* pclMsg, SI32 id);

	//=============================================================================================
	// [����] �߷�Ÿ�ε��� �̺�Ʈ
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_BUF(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_CHANGEBUF(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_START(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_END(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_GIVE_PRESENT_TONPC(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEEVENT_ISHOLDING(cltMsg* pclMsg, SI32 id);

	// [����] 2010�ų��̺�Ʈ
	//---------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_FORTUNERESULT(cltMsg* pclMsg, SI32 id);			// ���� ��� ���� ���� (����->Ŭ��)

	// [����] ���ֵ��� - �̺�Ʈ ���������� ������ �̼ǿ� ���� ���� �뺸
	void DoMsg_GAMEMSG_RESPONSE_GOONZUDAYMISSION( cltMsg* pclMsg, SI32 id );

	//-------------------------------------------------------------------------------------------------------------------
	// [����] ��ũ�� ���� ���� �м�
	//-------------------------------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_REQUEST_RECORD_ACTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_RECORD_ACTION_FINISHED(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_GZFTP_PROTOCOL(cltMsg* pclMsg, SI32 id);
	
	//-------------------------------------------------------------------------------------------------------------------
	// [����] ��Ƽ��Ī Ŭ���� ���� ��Ŷ ó�� �Լ���
	//-------------------------------------------------------------------------------------------------------------------
	void DoMsg_GAMEMSG_RESPONSE_PARTYMATCHING_LEVEL(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_APPLYTOPARTYJOIN(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CREATEMYPARTY(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CREATECOMPLETEPARTY(cltMsg* pclMsg, SI32 id); 
	void DoMsg_GAMEMSG_RESPONSE_GETPARTYMEMBERNAMELIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION(cltMsg* pclMsg, SI32 id);

	// [��ȣ] ��Ƽ����Ʈ
	void DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART(cltMsg* pclMsg, SI32 id); 
	void DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_START(cltMsg* pclMsg, SI32 id); 
	void DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_UPDATE(cltMsg* pclMsg, SI32 id); 
	void DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_GIVEUP(cltMsg* pclMsg, SI32 id);
	
	


	// [����] ��� ���� ���� ���.
	void DoMsg_GAMEMSG_RESPONSE_CONTRIBUTION_ITEM_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_CONTRIBUTION_INPUT_ITEM_LIST(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_GIANTRACCOON_RESURRECT_EVENT_START(cltMsg* pclMsg, SI32 id);

	//[����] �����Ƿ� ã�� 
	void DoMsg_GAMEMSG_RESPONSE_SEARCHMANUFACTURE(cltMsg* pclMsg, SI32 id);

	//[����] �߷�Ÿ�ε���. 
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_ITEM_PACKING(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_BUY_ITEM(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_QUESTION(cltMsg* pclMsg, SI32 id);
	void DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_ANSWER(cltMsg* pclMsg, SI32 id);
	

	
	
	//---------------------------
	// Key�Է�. 
	//---------------------------
	void PushKey(cltKey* pclkey)
	{
		clKeyManager.Push(pclkey);
	}

	void HorseStatusShow(TCHAR* pnormaltext);		// ���� �Ҹ� ������ ǥ���Ѵ�. 
	void HorseStatusHide();		// ���� �Ҹ� ������ ǥ�ø� �����Ѵ�.

	bool RequestSecretChatByPersonID(SI32 personid,TCHAR * buf = NULL );		// personid���� �Ӹ��� ��û�Ѵ�. 
	bool RequestSecretChatByCharUnique(SI32 charunique,TCHAR * buf = NULL );	// charunique���� �Ӹ��� ��û�Ѵ�. 
	bool RequestSecretChatByCharName(TCHAR * szName,TCHAR * buf = NULL );	// ĳ���� �̸��� �ٰŷ� �Ӹ��� ��û�Ѵ�.

	// ��� ������ �����Ѵ�. 
	void PlayBackgroundMusic(SI32 mapindex);

	// �ʵ��� �ֺ� ��ġ ������ �����´�.
	void GetNearMapInfo(SI32 mapindex,SI32 x,SI32 y,TCHAR * buf, SI16 txtSize );
	bool GetDirectionStr(SI32 sx, SI32 sy, SI32 dx, SI32 dy, TCHAR *szText, SI16 txtSize);


	// ���� �̵��� ���ʿ��� �������̽��� �����. 
	void DestroyNeedlessInterface();

	// ����� ������ �˻�. 
	void CheckuserEquipDur();

	//-----------------------------------------------
	// ������ �Ⱓ ����
	//-----------------------------------------------
	// ������ �Ⱓ ���� ó��
	BOOL GetItemUseAbleDay(cltItem* clItem, SI32 * outUseAbleDay); // ���Ⱓ�� ���� �������̸� ���� ��ȯ

	// ��� �׸� �׸���
	void DrawInitBack();

	// ���ΰ��� ���� Ÿ�ų� ������ �Ѵ�. 
	void RideOrUnrideHorse();

	// Ŭ���̾�Ʈ���� ���� ������ �����ϰ� ������ ��ġ�� ���Ѵ�. 
	void SetServiceArea(SI32 area);

	SI32 GetScreenMouseX();
	SI32 GetScreenMouseY();

	// ���콺�� �����϶��� ó��. 
	void MouseMoveAction(SI32 x, SI32 y);

	void ChangeTextFont( TCHAR *FileName, TCHAR *FontKind );

	//------------------------------------------
	// ���� ���� 
	//------------------------------------------
	void InitFogNode();
	// Ÿ�� ��� �ӵ� ����� ���� ����ũ ���� ȹ��
	void GetTileImgMask();

	BOOL CreateDirectDraw();

	// ��� �ӵ� ����� ���� Ÿ�� ����Ʈ. 
	SI32 TileMaskTransArray[MAP_TILE_YSIZE];
	SI32 TileMaskImgArray[MAP_TILE_YSIZE];

	bool GetFameLevelName( SI16 FameLevel, TCHAR *FameLevelName );

	//======================================================
	// �޽�����
	//======================================================
	// Ŭ���̾�Ʈ�޽��� ó�� �Լ�������
	class stClientMsgPtr
	{
	public:
		void (cltClient::*ClientMsgFunc)(cltMsg* pclMsg, SI32 id);
	};

	stClientMsgPtr *m_pClientMsgPtr;
	void	ClientMsgNullFunc(cltMsg* pclMsg, SI32 id);
	void	RegisterClientMsgMap();

	//------------------------------------------
	// ���� ���� 
	//------------------------------------------
	bool IsEnterGate( SI32 gateunique );

	SI16 GetLanguageFromFile();
	SI16 GetFpsFromFile();

	void SendEmoticon( SI16 index );

	//------------------------------------------
	// �ൿ�� ������ �ð��ΰ� ( second ���� �ൿ�� ��� )
	// �������� �������ӿ� ����.. ����..
	//------------------------------------------
	bool CanActionBySecond( SI32 second );

	bool IsOpenInterface( SI32 index );

	//[����] �����귿�� ���ư��� ���̸� �ش� ������ �귿�� �����Ŀ� �׸���. => 2008-6-17
	bool IsBuffRouletteAction(SI16 _siBuffKind);
};

#include <vector>
#include <mmsystem.h>
#include <winbase.h>

struct XPerformanceGuard
{
	XPerformanceGuard( const char *szName, int nLimit ) : m_szName( szName )
	{   
		m_nStartTime    = timeGetTime();            // �ڵ� ���� �ð� ����
		m_nTimeLimit    = m_nStartTime + nLimit;
		m_nEndTime      = 0;
	}

	~XPerformanceGuard()
	{
		m_nEndTime = timeGetTime();

		// ����� �ð��� ���ġ�� �ʰ��ߴٸ� �����ս� ��� ���
		if( m_nEndTime > m_nTimeLimit ) printPerformanceWarning();
	}

	void Profile( const char *szName )
	{
		m_vResult.push_back( _TAG( szName, timeGetTime() ) );
	}

protected:

	void oprint( const char *str, ... )
	{
		char szBuf[1024];
		va_list va;
		va_start( va, str );
		_vsnprintf( szBuf, sizeof(szBuf), str, va );
		va_end( va );
		OutputDebugString( szBuf );
	}

	// ������ ���� �ð��� ���
	void printPerformanceWarning()
	{
		int nTmp = m_nStartTime;
		char szBar[29] = "============================";
		memcpy( szBar, m_szName, strlen(m_szName) > sizeof(szBar)-1 ? sizeof(szBar)-1 : strlen(m_szName) );
		if( strlen(m_szName) < sizeof(szBar)-1 ) szBar[strlen(m_szName)] = ' ';
		oprint( "\n== PERFOMANCE CAUTION : %s\n", szBar );
		for( size_t i = 0; i < m_vResult.size(); ++i ) 
		{
			oprint( "%3d. %-25s : %d ms\n", i, m_vResult[i].szName, m_vResult[i].nTime - nTmp );
			nTmp = m_vResult[i].nTime;
		}
		oprint( "     %-25s : %d ms\n", "TOTAL", m_nEndTime - m_nStartTime );
		oprint( "====================================================\n\n" );
	}

	struct _TAG
	{
		_TAG( const char *name, int t ) : szName( name ), nTime( t )    {}

		const char *    szName;
		int             nTime;
	};

	const char*         m_szName;
	int                 m_nStartTime;
	int                 m_nEndTime;
	int                 m_nTimeLimit;
	int                 m_nTM;
	std::vector< _TAG >   m_vResult;
};

#define XPG_SET( x,y )  XPerformanceGuard   ___x_performance_guard( x,y )
#define XPG_DO( x )     ___x_performance_guard.Profile( x )

#endif

