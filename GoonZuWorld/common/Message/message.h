#ifndef _MESSAGE_H
#define _MESSAGE_H

#ifdef _CHINA
	#define MAX_MESSAGE_NUMBER     3				// �޽����� ǥ���� �� �ִ� ����. 				
#else
	#define MAX_MESSAGE_NUMBER     10				// �޽����� ǥ���� �� �ִ� ����. 				
#endif 

#define MAX_PERSONAL_MESSAGE_NUMBER     5				// �޽����� ǥ���� �� �ִ� ����. 				

#define MAX_MESSAGE_DELAY      200			    // �޽����� ǥ���ϴ� �ð�. 

#define MAX_MESSAGE_LENGTH		256			    // �� �޽����� �ִ� ����. 
#define MAX_WAR_MSG_SIZE		128 

#include <Directives.h>
#include "../CommonHeader.h"
#include "..\CommonLogic\WarRank\WarRank.h"
#include "..\Quest\Quest.h"

#include <ddraw.h>

class cltClient;
class cltItem;

class cltMessage{
public:
	SI32		MessageIndex;
	SI32		MessageDelay;
	TCHAR		Message[MAX_MESSAGE_NUMBER][MAX_MESSAGE_LENGTH];
#ifdef _SAFE_MEMORY
	NSafeTArray<COLORREF, MAX_MESSAGE_NUMBER>		MessageColor;
	NSafeTArray<COLORREF, MAX_MESSAGE_NUMBER>		MessageShdowColor;
#else
	COLORREF	MessageColor[MAX_MESSAGE_NUMBER];
	COLORREF	MessageShdowColor[MAX_MESSAGE_NUMBER];
#endif

	DWORD		dwLastWarMsgFrame;
	TCHAR		szWarMsg[MAX_WAR_MSG_SIZE];
	TCHAR		szKilledWar[MAX_WAR_MSG_SIZE];
	TCHAR		szKillPoint[MAX_WAR_MSG_SIZE];
	TCHAR		szWarPlayersMsg[MAX_WARRANK_PERSON_PER_MAP][MAX_WAR_MSG_SIZE];
	
	// [�߰� : Ȳ���� 2008. 1. 21 => ���� ���� ���� �̸��� ����.]
	TCHAR		szWarVillageMsg[MAX_WARRANK_PERSON_PER_MAP][MAX_WAR_MSG_SIZE];
	
	// ������ �޽��� 
	TCHAR		szHuntMsg[MAX_MESSAGE_LENGTH];
	bool		bHuntMsgSwitch;
	DWORD		dwLastHuntMsgClock;
	
	// ���� �޽��� 
	TCHAR		szPrisonMsg[MAX_MESSAGE_LENGTH];
	bool		bPrisonMsgSwitch;
	DWORD		dwLastPrisonMsgClock;

	
	// �Ұ��縮 ��� �̺�Ʈ  �޽��� 
	TCHAR		szHuntEventMsg[MAX_MESSAGE_LENGTH];
	bool		bHuntEventMsgSwitch;
	DWORD		dwLastHuntEventMsgClock;

	// ���ĸ��� �̺�Ʈ  �޽��� 
	TCHAR		szMofuMofuEventMsg[MAX_MESSAGE_LENGTH];
	bool		bMofuMofuEventMsgSwitch;
	DWORD		dwLastMofuMofuEventMsgClock;

	// ���� ���� ��� �̺�Ʈ  �޽��� 
	TCHAR		szGoguEventMsg[MAX_MESSAGE_LENGTH];
	bool		bGoguEventMsgSwitch;
	DWORD		dwLastGoguEventMsgClock;

	// ����ī �̺�Ʈ  �޽��� 
	TCHAR		szOsakaEventMsg[MAX_MESSAGE_LENGTH];
	bool		bOsakaEventMsgSwitch;
	DWORD		dwLastOsakaEventMsgClock;

	// ��ȭ��  �޽��� 
	TCHAR		szKanghwadoEventMsg[MAX_MESSAGE_LENGTH];
	bool		bKanghwadoEventMsgSwitch;
	DWORD		dwLastKanghwadoEventMsgClock;

	// Daily Quest �޽��� 
	TCHAR		szDailyQuestMsg[MAX_MESSAGE_LENGTH];
	bool		bDailyQuestMsgSwitch;
	DWORD		dwLastDailyQuestMsgClock;

	// ���� �ֹ� ä�� �޽���. 
	TCHAR		szVillageChatMsg[MAX_MESSAGE_LENGTH];
	bool		bVillageChatMsgSwitch;
	DWORD		dwLastVillageChatMsgClock;

	// �ν��Ͻ� ���� �޽���
	TCHAR		szInstanceMapMsg[MAX_MESSAGE_LENGTH];
	bool		bInstanceMapMsgSwitch;
	DWORD		dwLastInstanceMapMsgClock;

	// ����Ʈ ���� �޼���
	DWORD		dwCurQuestInfoMsgClock[MAX_QUEST_TYPE];
	TCHAR		szCurQuestInfoMsgBuffer[MAX_QUEST_TYPE][MAX_MESSAGE_LENGTH];
	TCHAR		szQuestPrintBuffer[MAX_QUEST_TYPE][MAX_MESSAGE_LENGTH];
	bool		bQuestClearSwitch[MAX_QUEST_TYPE];
	bool		bCurQuestInfoMsgSwitch;

	//[����] �������� �޽��� ��� ��ġ ���� ���� �߰�. => 2008-6-2
	TCHAR		PersonalMessage[MAX_PERSONAL_MESSAGE_NUMBER][MAX_MESSAGE_LENGTH];
	SI32		PersonalMessageIndex;
	SI32		PersonalMessageDelay;

	//[����] ��Ʋ�ξ� ��� 
	TCHAR		szBattleRoyalGameModeMsg[MAX_MESSAGE_LENGTH];
	bool		bBattleRoyalGameModeMsgSwitch;
	DWORD		dwLastBattleRoyalGameModeMsgClock;

	//	��Ƽ����Ʈ �޼���
	TCHAR		m_szPartyQuestMessage[2][MAX_MESSAGE_LENGTH];	// �Ϸ� �޼����� ���� ������ �޼��� �ΰ����� ���ÿ� �ѷ����� �ֽ��ϴ�.
	bool		m_bPartyQuestGameModeMsgSwitch;
	DWORD		m_dwLastPartyQuestGameModeMsgClock;

	//	Ǯ��ũ�� ���θ� ������ �´�.
	BOOL bFullscreen		;
	
	HFONT		hFont;
	// ��Ʋ�ξ�� ��Ʈ
	HFONT		m_hFontBattleRoyal;

	cltMessage();
	~cltMessage();


	void init();
	void SetMsg(TCHAR* szmessage, SI32 sieffect = 0, COLORREF rgb = RGB(220, 220, 220), COLORREF shadowrgb = RGB(0,0,0));
		//COLORREF rgb = RGB(250, 60, 50), COLORREF shadowrgb = RGB(100,30,30));

	void Scroll();
		
	void Show(cltClient* pclclient, SI32 sistartx, SI32 sistarty, LPDIRECTDRAWSURFACE7 psurface,	SI32 rx, SI32 ry);

	// ���� �ڵ尡 �� ���ڿ��� ����Ѵ�
	void DrawMultyColorText(HDC hdc, SI32 rx , SI32 ry, TCHAR * szmessage , COLORREF shadowrgb );
	
	// 
	SI16 ChangeText( HDC hDC, SI32 nPos , TCHAR * szmessage );

	// ���� �޽����� �����Ѵ�. 
	void SetBlackArmyWarMsg(TCHAR* szmsg, TCHAR** sortplayernames, SI32 *playerscores  );
	void SetWarMsg(TCHAR* szmsg, TCHAR** sortplayernames, SI32 *playerscores, TCHAR** szSortVillageNames, SI32* siWarVillageScores );
	void ClearWarMsg();

	// ���� �޽����� �����ش�. 
	void ShowWarMessage(HDC hdc, SI32 rx, SI32 ry);

	// ���� ������ ǥ���Ѵ�. 
	void ShowWarKill(LPDIRECTDRAWSURFACE7 surface, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ������ ȹ�� �޽���. 
	//----------------------------------------------

	void SetGetItemMsg(TCHAR* itemName, cltItem * pclItem,GMONEY price);
	
	//----------------------------------------------
	// ������ �޽���. 
	//----------------------------------------------
	void SetHuntMsg(TCHAR* szmessage);
	// ������ �޽����� �����ش�. 
	void ShowHuntMessage(HDC hdc, SI32 rx, SI32 ry);



	//----------------------------------------------
	// ����Ʈ ���� �޽���
	//----------------------------------------------
	void ShowCurQuestInfo(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ���� �޽���. 
	//----------------------------------------------
	void SetPrisonMsg(TCHAR* szmessage);
	// ���� �޽����� �����ش�. 
	bool ShowPrisonMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// �Ұ��縮 ��� �̺�Ʈ �޽���. 
	//----------------------------------------------
	void SetHuntEventMsg(SI32 leftsecond);
	// �Ұ��縮 ��� �̺�Ʈ �޽����� �����ش�. 
	void ShowHuntEventMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ���ĸ��� �̺�Ʈ �޽���. 
	//----------------------------------------------
	void SetMofuMofuEventMsg(SI32 leftsecond, SI32 siMaMaMofuMofu, SI32 siKilledMofuMofu, SI32 siTotalMofuMofu);
	// ���ĸ��� ��� �̺�Ʈ �޽����� �����ش�. 
	void ShowMofuMofuEventMessage(HDC hdc, SI32 rx, SI32 ry);
	
	//----------------------------------------------
	// ���� ���� ��� �̺�Ʈ �޽���. 
	//----------------------------------------------
	void SetGoguEventMsg(SI32 leftsecond);
	// ���� ���� ���  �̺�Ʈ �޽����� �����ش�. 
	void ShowGoguEventMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ����ī�� �̺�Ʈ �޽���. 
	//----------------------------------------------
	void SetOsakaEventMsg(SI32 leftsecond);
	// ����ī��  �̺�Ʈ �޽����� �����ش�. 
	void ShowOsakaEventMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ��ȭ�� �̺�Ʈ �޽���. 
	//----------------------------------------------
	void SetKanghwadoEventMsg(SI32 leftsecond);
	// ��ȭ��  �̺�Ʈ �޽����� �����ش�. 
	void ShowKanghwadoEventMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// ������ �޽���. 
	//----------------------------------------------
	void SetDailyQuestMsg(TCHAR* szmessage);
	// ������ �޽����� �����ش�. 
	void ShowDailyQuestMessage(HDC hdc, SI32 rx, SI32 ry);

	//----------------------------------------------
	// �ֹ� ä�� �޽���. 
	//----------------------------------------------
	void SetVillageChatMsg(TCHAR* szmessage);
	// ������ �޽����� �����ش�. 
	void ShowVillageChatMessage(HDC hdc, SI32 rx, SI32 ry);

	//-----------------------------------------------
	// �ν��Ͻ� ���� �޽���
	//----------------------------------------------
	void SetInstanceMapMsg(TCHAR* szmessage);
	void ShowInstanceMapMsg(HDC hdc, SI32 rx, SI32 ry);

	//[����] �������� �޽��� ��� ��ġ ���� �߰�. => 2008-6-2
	void ShowPersonalMsg(HDC hdc, SI32 rx, SI32 ry);
	void SetPersonalMsg(TCHAR* szmessage);
	void PersonalScroll();

	//-----------------------------------------------
	// ��Ʋ�ξ� ���� ���
	//----------------------------------------------
	void SetBattleRoyalGameModeMsg(TCHAR* pszMessage);
	// ��Ʋ�ξ� ���� ��� �޽����� �����ش�. 
	void ShowBattleRoyalGameModeMessage(HDC hdc, SI32 rx, SI32 ry);

	// ��Ƽ����Ʈ ���õ� �޼����� ����մϴ�. 
	void ShowPartyQuestMsg(HDC hdc, SI32 rx, SI32 ry);
	void SetPartyQuestGameModeMsg(TCHAR* pszMessage, bool bClear);


};



#endif
