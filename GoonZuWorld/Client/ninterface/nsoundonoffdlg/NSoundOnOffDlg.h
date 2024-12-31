#pragma once

#include <Directives.h>
#include "..\..\..\Resource.h"

#include "..\..\..\Common\Char\KindInfo\KindInfo.h"
#include <Graphic.h>

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../../Common/Item/ItemCommon/ItemUnit.h"

#include "../../InterfaceMgr/DialogController.h"

class CCheckBox;
class CRadioButton;
class CComboBox;
class CStatic;
class CEdit;
class COutLine;
class CImageStatic;

class CNSoundOnOffDlg : public CDialogController
{
public:
	enum
	{
		MAX_CAPTIONKIND_NUM = 3,

		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_BIG_POS_X = 1024 - 280 + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 100,
		DLG_SMALL_POS_X = 800 - 280 + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 100,
	};

	CNSoundOnOffDlg();
	~CNSoundOnOffDlg();

	void Create();

	static	void CALLBACK StaticNSoundOnOffDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NSoundOnOffDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	bool IsShow();
	void Show();
	void Hide();

	void SetTotalSpendTime( SI32 TotalSpendTime, SI32 EventTime );
	void SendCurrentSettingInfo();

	void SetSoundButton(SI16 selectedbutton );
	void SetBGMButton(SI16 selectedbutton );

	void LoadSoundConfig();
	void WriteSoundConfig();

	void LoadLanguageConfig();
	void WriteLanguageConfig();

	void LoadFpsConfig();
	void WriteFpsConfig( SI16 fps );

	void WriteCountryConfig();

	void SetShowPuchikomiCheckBox(bool bCheck);

	bool IsAloneDraw() { return m_bAloneDraw; }

public:
	bool m_bShow;

	// Previous Storable Setting
	bool m_bEffectSound;				// ȿ���� ���
	bool m_bBackGroudnSound;			// ����� ���
	bool m_bBigDisplayMode;				// 1024x768 : true or 800x600 : false
	bool m_bFullScreenMode;				// Ǯ��ũ�� ��� ���
	bool m_bTmpFullScreenMode;			// �ӽ� Ǯ��ũ�� ��� �÷���
	bool m_bMaxWindowMode;				// �ִ�â ũ�� ��� ���
	bool m_bTmpMaxWindowMode;			// �ӽ� �ִ�â ũ�� ��� �÷���
	bool m_bMiniMapShow;				// �̴ϸ� ����
	
	/*
	leon add - 2005-03-10-10-00
	* m_bPrivateTradeReject => m_pNSoundOnOffDlg�� üũ ���� ������ ���ؼ�.. �߰���
	* m_siSelectCaptionKindIdex => combobox ���� ���õ� ���¸� ���ؼ� �߰���
	*/
	// Extended Storable Settings
	bool m_bRightMouseMentAllow;		// ����� �޴� �����ֱ�
	bool m_bShowCharName;				// ĳ���͵��� �̸� �����ֱ�

	bool m_bWhisperChatReject;			// ��� �ӼӸ� �ź�
	bool m_bPrivateTradeReject;			// ��� �ŷ� �ź�
	
	bool m_bJewelItemNotifyReject;		// ��ǰ �˸� �ź�

	bool m_bPartyInviteNotifyReject;	// ��Ʈ �ʴ� �ź�
	bool m_bFriendAddNotifyReject;		// ģ�� �߰� �ź�

	bool m_bSummonEvolveNotifyReject;	// ��ȯ����ȭ �˸� �ź�
	

	bool m_bNotifyHeadChat;				// ��� ����â �ź�
	bool m_bNotifyMinigame;				// �̴ϰ��� �ź�

	bool m_bChatFixed;					// ä��â ���� ����  -> â��ġ ���� ���� �� ���[����] 
	
	SI16 m_siSelectCaptionKindIdex;		// �ڸ� ���� �ε���

	SI16 m_siSelectedSoundButton;
	SI16 m_siSelectedBGMButton;

	//bool m_bFriendRegisterReject;		// ģ�� ��� �ź�

	bool m_bIsLoadLanguage;			// ó�� 
	bool m_bIsLoadFps;

	bool m_bAloneDraw;	// ��ȥ�ڸ� �׷��ֱ�, npc ���� �����Ѵ�.

	//KHY - 0110 - ä�� ��� ����
	bool m_bChatTabFixed ;			// ä�� ������ ���� -> �Ϲ�, ����, �����.
	SI16 m_siChatTabNowIndex;		// ���� ä�� ��� ����.

	// [����] ��ü��� â �����ֱ� ����
	bool m_bOrganPannelShow;

	bool m_bMykey;					// [����] ������ �޴�.	=> 2008-9-3
	bool m_bGameTip;				// [����] ���� ��.		=> 2008-10-6
	bool m_bHelper;					// [����] �����.		=> 2008-10-7

	bool m_bPVP;					// [����] PVP ��� 
	
	CCheckBox	 *m_pBackgroundCheckBox;
	CCheckBox	 *m_pEffectCheckBox;
	//CCheckBox	 *m_pWindowmodeCheckBox;
	CCheckBox	 *m_pMinimapRejectCheckBox;
	CCheckBox	 *m_pNotifyFriendAddRejectCheckBox;
	CCheckBox	 *m_pNotifyHeadChatCheckBox;
	CCheckBox	 *m_pNotifyJewelItemRejectCheckBox;
	CCheckBox	 *m_pNotifyMiniGameCheckBox;
	CCheckBox	 *m_pNotifySummonEvolveRejectCheckBox;
	CCheckBox	 *m_pPartyInviteRejectCheckBox;
	CCheckBox	 *m_pPrivateTradeRejectCheckBox;

	CCheckBox	 *m_pRightMouseMenuAllowCheckBox;
	CCheckBox	 *m_pWhisperChatRejectCheckBox;
	CCheckBox	 *m_pChatFixedCheckBox;					// ä��â ����
	CCheckBox	 *m_pChatTabFixedCheckBox;				// ä�� ��� ����
	CCheckBox	 *m_pShowCharNameCheckBox;

	CCheckBox	 *m_pShowPuchikomiCheckBox;				// Ǫġ�ڹ� ���� / �����

	CCheckBox	 *m_pShowOrganCheckBox;					// ��ü �������

	CComboBox	 *m_pSelectCaptionKindCombobox;

	CCheckBox	 *m_pMyKeyCheckBox;						// [����] ������ �޴�.	=> 2008-9-3
	CCheckBox	 *m_pGameTipCheckBox;					// [����] ���� ��.		=> 2008-10-6
	CCheckBox	 *m_pHelperCheckBox;					// [����] �����.		=> 2008-10-7

	CCheckBox	 *m_pPVPModeCheckBox;					// [����] PVP�ź� ���

	CEdit		 *m_pTotalSpendTimeEdit;
	CStatic		 *m_pSettingStatic;
	CStatic		 *m_pEffect_BackgroundStatic;
	CStatic		 *m_pGameSettingStatic;
	CStatic		 *m_pCaptionInfoStatic;
	CStatic		 *m_pTotalSpendTimeStatic;

	COutLine	*m_pOutLine_NONAME1	;
	COutLine	*m_pOutLine_NONAME2	;
	COutLine	*m_pOutLine_NONAME4	;

	CCheckBox	*m_pCheckBox_maximization	;

	CImageStatic * m_pEffVolumeButton[5];
	CImageStatic * m_pBGMVolumeButton[5];
	
	CButton	*	m_pSoundMinusButton;
	CButton	*	m_pSoundPlusButton;
	CButton	*	m_pBGMMinusButton;
	CButton	*	m_pBGMPlusButton;

	CStatic*	m_pStaticShowCountry;
	CRadioButton*	m_pRadioShowCountryOn;
	CRadioButton*	m_pRadioShowCountryOff;

	CStatic*	m_pStaticLanguage;
	CComboBox*	m_pComboLanguage;

	CStatic*	m_pStaticFps;
	CComboBox*	m_pComboFps;

	CCheckBox	 *m_pCheckBoxAloneDraw;
};

//#endif
