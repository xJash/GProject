#ifndef _NPARTY_H_
#define _NPARTY_H_

#include "../../InterfaceMgr/DialogController.h"
#include "..\..\..\Common\PartyMgr\PartyObj.h"
#include "..\..\..\Common\CommonHeader.h"
//#include "../Client/Interface/PartyDlg/PartyDlg.h"

#define MAX_RICHEDIT_OBJ_SIZE							500		// �ִ� 500 Byte�� �����Ϳ� �Ҵ� ��.

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;
class CChatEdit;
class CRadioButton;
class COutLine;

class CLibListMgr;
class cltItem;

#define MAX_MINIMIZE_SLOT 7

enum PARTYQUEST_MESSAGE
{
	PARTYQUEST_MESSAGE_CAN_START,
	PARTYQUEST_MESSAGE_CANNOT_START,
	PARTYQUEST_MESSAGE_FAILED_LESS_USER,
	PARTYQUEST_MESSAGE_FAILED_ADDED_USER,
	PARTYQUEST_MESSAGE_ANSWER_FAILED,
	PARTYQUEST_MESSAGE_TIMEOUT,
};

struct stPartyChatSend
{	
	TCHAR strChatData[ MAX_CHAT_DATA_LENGTH ];

	stPartyChatSend()
	{
		memset( this, 0, sizeof( stPartyChatSend ) );
	}

	stPartyChatSend( TCHAR *ChatData )
	{
		MStrCpy( strChatData, ChatData, MAX_CHAT_DATA_LENGTH );
	}
};

struct stClientPartyUser
{
	bool bPartyStatus;						// ��Ƽ�� ������ ������, �ƴϸ� �� ����Ʈ�� �����̳ĸ� �������� ���ؼ�...
	bool bIsPartyLeader;					// ��Ƽ���̳�, ��Ƽ���̳�	
	SI32 siCharUnique;						// ĳ���� unique ��
	TCHAR strCharName[ MAX_PLAYER_NAME ];	// ĳ���� ��
	SI32 siExp;								// ȹ�� ����ġ
	SI32 siLevel;							// ����
	cltCharPos clCharPos;					// ��ġ (���ε���, ����ǥ)

	void Init()
	{
		bPartyStatus = false;
		bIsPartyLeader = false;
		siCharUnique = 0;		
		memset( strCharName, 0, MAX_PLAYER_NAME );
		siExp = 0;
		siLevel = 0;
		clCharPos.Init();
	}

	void Set( stClientPartyUser *pClientPartyUser )
	{
		memcpy ( this, pClientPartyUser, sizeof( stClientPartyUser ) );
	}
};

class CNPartyDlg : public CDialogController
{
public:

	CNPartyDlg();
	~CNPartyDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNPartyDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNPartyDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();
	void Action();
//	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );

	void EnableButton(CButton* pButton, TCHAR* pText, BOOL Flag = false);	// ��ư Ȱ��ȭ ��Ȱ��ȭ

	void Initialize();
	bool IsPartyStatus();
	bool IsPartyLeader();
	bool IsPartyUser( SI32 CharUnique );

	SI32 GetPartyIndex();

//	void PartyCreate( SI32 PartyIndex );
	void PartyCreateJoin( SI32 PartyIndex, SI32 LeaderPersonID, SI32 LeaderCharUnique, TCHAR *strLeaderChatName, SI32 LeaderLevel, cltCharPos* LeaderCharPos , SI32 MemberPersonID, SI32 MemberCharUnique, TCHAR *strMemberCharName, SI32 MemberLevel, cltCharPos* MemberCharPos );	
	void PartyJoin( SI32 PartyIndex, SI16 UserListIndex,SI16 ItemGetPattern );
	void PartyDelete( SI32 PartyIndex );
	void PartyAddUser( bool PartyLeader, SI32 CharUnique, TCHAR *CharName, SI16 UserListIndex, SI32 Level, cltCharPos* clCharPos );
	void PartyDelUser( SI32 CharUnique, SI16 UserListIndex );
	void PartyForceDelUser( SI32 CharUnique, SI16 UserListIndex );
	void PartyChangeLeader( SI32 CharUnique, SI16 UserListIndex );
	void PartyNotifyExp( SI32 CharUnique, SI16 UserListIndex, SI32 Exp );

	void AddChat( TCHAR *strUserID, TCHAR *strChatData);
	void AddChat( TCHAR *strChatData);
	void AddName( TCHAR *PlayerName);
	void AddText( TCHAR *ChatText);
//	void SetFont( COLORREF Color, DWORD dwMask = CFM_COLOR|CFM_SIZE|CFM_BOLD|CFM_ITALIC|CFM_FACE, DWORD dwEffects=~(CFE_AUTOCOLOR), TCHAR *FontKind=TEXT("����"), SI16 YHeight=RICHEDIT_FONT_HEIGHT );
	void SendPartyChat();

	SI32 FindUserSelectedIndex( TCHAR *CharName );

	void PrintUserNum();

	void ReloadPartyUserList();

	bool PopPartyChatSendData( stPartyChatSend *pPartyChatSend );
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
	void ItemGetPatternButtonEnable(bool bEnable);
	void ChangeItemGetPattern( SI16 ItemGetPattern );
	
	void PartyNotifyItemGet(SI32 CharUnique, cltItem* pclItem);
	void SetPartyUserPos(SI32 CharUnique, cltCharPos* pclCharPos);
	void SetPartyUserLevel(SI32 CharUnique, SI32 Level);
	cltCharPos* GetPartyUserPos(SI16 partyuserindex);
	void Minimi(BOOL bMini);	// �ּ�ȭ ��ƾ. TRUE = �ּ�ȭ ��Ų��. FALSE = �ٽ� �ǵ�����
	BOOL IsMinimi(){	return m_bMini; };
	SI16 GetMinimizedSlot(){return m_siMinimizedSlot;};

		// [����] ������ : �������ȿ����� ��Ƽ�� ���� �� ����.(��ư ����)
	void DoNotLeaveParty();

	bool IsPartyMember( const SI32 siFindCharID );

	void StartPartyQuestMessage(SI32 siMessage);	// ��Ƽ����Ʈ ���۽� �޼��� ����
	void SetInviteCharUnique(SI32 siInviteCharUnique){m_siInviteCharUniqueForPartyQuest = siInviteCharUnique;}

	void UpdatePartyQuestBtn();

	BOOL m_bMini;
	SI16 m_siOldPosX;
	SI16 m_siOldPosY;
	SI16 m_siMinimizedSlot; //[����] �ּ�ȭ ��ư�� ��ġ�Ѱ��� ���� �̴ϸ� �ؿ� [3][2][1]  0�̸� �̴ϰ� �ƴϴ�. 

	bool m_bPartyStatus;			// ��Ƽ���̳�, ��Ƽ���� �ƴϳ�
	bool m_bIsPartyLeader;			// ��Ƽ���̳�, ��Ƽ���̳�

	SI32 m_siPartyIndex;	
 
	COLORREF ColorIndex[6];

	stClientPartyUser m_stClientPartyUser[ MAX_PARTY_USER_NUM ];
	SI16 m_siPartyUserNum;

	SI32 m_siSelectedUserListIndex;
	SI16 m_siItemGetPattern; // ������ ȹ�� ��� ��� ����

	TCHAR *m_strViewData;
	TCHAR *m_strChatData;

	CLibListMgr *m_pChatDataList;

	CStatic*	m_pStatic[3]; // 0: �ο� ǥ��, // 1: ��Ƽä��, //2: ȹ���� ����
	CList*		m_pList;
	CButton*	m_pButton;
	CButton*	m_pMoveButton;
	CEdit*		m_pEdit;  //   ��Ƽ�� ����
	CRadioButton* m_pRadioItemGetPattern[4]; // 0 : ����ȹ��, 1: ��ȯȹ��, 2: ��Ÿȹ��, 3: ����ȹ��
		
	CImageStatic* m_pImageMinimized;
	
	CButton*	m_pButtonMinimize;
	
	COutLine*	m_pOutLine[2];
	
	CChatEdit*  m_pChatEdit; //  ä�� ǥ��

	SI32		m_siInviteCharUniqueForPartyQuest;	// ��Ƽ����Ʈ�� ���Ǵ� �ʴ�������ũ
	CButton*	m_pBtnStartQuest;	// ��Ƽ ����Ʈ ����

	// ��Ƽ��Ī
	bool		m_bIsPartyQuestParty;	// ��Ƽ����Ʈ�� ���� ��Ƽ�ΰ�?				// �Ʒ� �� ���� ó�� ��Ƽ�� ��������� �������� ���� ��Ƽ���� ����� ������ �������� ä����.
	SI32		m_siCategory;		// ��Ƽ��Ī ��Ƽ�ϰ�� ī�װ��� (0 <=) ���� ����
	SI32		m_siMission;		// ��Ƽ��Ī ��Ƽ�ϰ�� �̼ǿ� (0 <=) ���� ����
	void		Set_PartyQuestInfo(bool isPartyQuest, SI32 siCategory, SI32 siMission);
};

#endif