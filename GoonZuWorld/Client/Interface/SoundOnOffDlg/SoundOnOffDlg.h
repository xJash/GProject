#ifndef _SOUNDONOFFDLG_H_
#define _SOUNDONOFFDLG_H_

#include <Directives.h>
#include "..\..\..\Resource.h"

#include "..\..\..\Common\Char\KindInfo\KindInfo.h"
#include <Graphic.h>

class CSoundOnOffDlg
{
public:
	enum 
	{
		MAX_CAPTIONKIND_NUM = 3,
	};

	CSoundOnOffDlg();
	~CSoundOnOffDlg();

	void Create( HINSTANCE hInst, HWND hWnd );

	static	BOOL CALLBACK StaticSoundOnOffDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );
	BOOL	CALLBACK SoundOnOffDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );
	
	bool IsShow();
	void Show();
	void Hide();

	void SetTotalSpendTime( SI32 TotalSpendTime );
	void SendCurrentSettingInfo();

	void LoadSoundConfig();
	void WriteSoundConfig();

public:
	HWND m_hDlg;
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
	
	// Extended Storable Settings
	bool m_bRightMouseMentAllow;		// ����� �޴� �����ֱ�
	bool m_bShowCharName;				// 

	bool m_bWhisperChatReject;			// ��� �ӼӸ� �ź�
	bool m_bPrivateTradeReject;			// ��� �ŷ� �ź�
	
	bool m_bJewelItemNotifyReject;		// ��ǰ �˸� �ź�

	bool m_bPartyInviteNotifyReject;	// ��Ʈ �ʴ� �ź�
	bool m_bFriendAddNotifyReject;		// ģ�� �߰� �ź�

	bool m_bSummonEvolveNotifyReject;	// ��ȯ����ȭ �˸� �ź�

	bool m_bNotifyHeadChat;				// ��� ����â �ź�
	bool m_bNotifyMinigame;				// �̴ϰ��� �ź�

	bool m_bChatFixed;					// ä��â ���� ���� -> â��ġ ��� ���� [����]

	//KHY - 0110 - ä�� ��� ����
	bool m_bChatTabFixed;					// ä�� ������ ���� -> �Ϲ�, ����, �����.
	SI16 m_siChatTabNowIndex;				// ���� ä�� ��� ����.
	
	SI16 m_siSelectCaptionKindIdex;		// �ڸ� ���� �ε���

	SI32 m_siSelectedBGMButton;
	SI32 m_siSelectedSoundButton;



	//bool m_bFriendRegisterReject;		// ģ�� ��� �ź�

	bool m_bAloneDraw;
	
};

extern CSoundOnOffDlg g_SoundOnOffDlg;



#endif
