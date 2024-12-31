#ifndef _NCHATBARDLG_H_
#define _NCHATBARDLG_H_

#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"



#define MSG_CHAT_RECV							12500
#define MSG_RESIDENTSCHAT_RECV					12505
#define MSG_PARTYCHAT_RECV						12510 
#define MSG_MASTERNOTIFYCHAT_RECV				12515
#define MSG_VILLAGENOTIFYCHAT_RECV				12520
#define MSG_RESIDENTSNOTIFYCHAT_RECV			12525
#define MSG_KINGNOTIFYCHAT_RECV					12530
#define MSG_GOODSPRODUCTIONNOTIFYCHAT_RECV		12535
#define MSG_GUILDCHAT_RECV						12540


#define MAX_TABBUTTON	7

#define MAX_CHAT_HISTORY_NUM	100	// ����� �ڽ��� �Է��ߴ� ä�� �������� �ִ� ����
#define MAX_REPEAT_LIMIT_NUM		5	// ���� ���� �ݺ��Ҽ� �ִ� Ƚ��

enum {
	BUTTON_ID_NORMAL, //�Ϲ�ä��
	BUTTON_ID_VILLAGE, //����
	BUTTON_ID_GUILD, // ���
	BUTTON_ID_PARTY, // ��Ƽ
	BUTTON_ID_HEAD,  // ����
	BUTTON_ID_NEWSITEM, // �ڸ�����
	BUTTON_ID_GOONZU,	// ���� ����
};

enum {
	CHATEDIT_CLOSE,
	CHATEDIT_OPEN_5LINES,
	CHATEDIT_OPEN_10LINES,
	CHATEDIT_OPEN_MAX	
};
struct stChatHistoryData
{
	//SI16 DataSize;
	TCHAR strChatData[ CHATEDIT_CHATDATA_LENGTH ];

	stChatHistoryData()
	{
		Init();
	}

	stChatHistoryData( stChatHistoryData *pChatHistoryData )
	{
		Set( pChatHistoryData );
	}

	stChatHistoryData( TCHAR * pChatData )
	{
		Init();

		StringCchCopy(strChatData,CHATEDIT_CHATDATA_LENGTH,pChatData);
	}

	void Init()
	{
		memset( this, 0, sizeof( stChatHistoryData ) );
	}

	void Set( stChatHistoryData *pChatHistoryData )
	{
		memcpy( this, pChatHistoryData, sizeof( stChatHistoryData ) );
	}
};




class CButton;
class CChatEdit;
class CEdit;
//class CImageButton;
class CChatTabButton;
class CChatStatusBarBuffer;
struct stChatStatusBarData;

class CNChatBarDlg : public CDialogController
{
public:
	CNChatBarDlg();
	~CNChatBarDlg();

	void Create();
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY );

	static void CALLBACK StaticCallBackDialogBar( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogBar( UINT nEvent, int nControlID, CControllerObj* pControl );
	void Action();
	void setChatstatus(UI32 Index );					// ���� � ê�� �������� �����صд�.
	void DelChatstatus(UI32 Index );					// ���� � ê�� ������ ������ �����.
	BOOL CheckChatstatus( SI32 ChatKind  );				// ���� � ê�� ������ ������ �����..
	void CSaveChatstatus();							// ���� � ê�� ������ ������ �����..
	BOOL CLevelupskillupNoticeChatstatus( SI16 messagetype );			// ���� � ê�� ������ ������ �����..
private:
    
	CChatEdit	*m_pChatEdit;
	CEdit		*m_pInputEdit;
	CButton		*m_pOpenButton;
	CButton		*m_pEmoticonButton;
	CButton		*m_pIMEButton;
	CButton		*m_pChatSetButton;

	CChatTabButton		*m_pTabButton[MAX_TABBUTTON];
	SI16 m_siSelectedButton;

	bool m_bSetGoonzu;


	//---------------------------------------------------------------
	// ä�� ����
	//---------------------------------------------------------------
public:
	void CharacterLogin();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void ChatDataSend();
	void Push( SI16 ChatDataKind, TCHAR *ChatText );
	bool Pop( stChatStatusBarData * pChatStatusBarData );
	void SetInputEditBoxFocus();

	void SmallShow();
	void BigShow();

	bool CheckData( TCHAR *PlayerName, TCHAR *ChatText);

	void ChatRecv( TCHAR *PlayerName, TCHAR *ChatText, bool bGameMaster = false, SI32 Kind = 0 );
	void MasterNotifyChatRecv( TCHAR *PlayerName, TCHAR *ChatText );
	void VillageNotifyChatRecv( TCHAR *PlayerName, TCHAR *ChatText );
	void ResidentsNotifyChatRecv( TCHAR *PlayerName, TCHAR *ChatText );
	void KingNotifyChatRecv( TCHAR *PlayerName, TCHAR *ChatText );
	void GoodsProductionNotifyChatRecv( TCHAR *PlayerName, TCHAR *ChatText );
	void ItemGetChatRecv( TCHAR* itemname, SI16 itemCnt, GMONEY price  );
	void LevelUpNoticeChatRecv( TCHAR* charname, SI32 level, SI32 skilllevel,SI32 skilltype ,SI16 messagetype);

	void SetOpenedChatDlg( SI16 OpenSize );
	void ChatMessage(SI16 chatmode, SI32 systemtxt, TCHAR* pmsg);       //client �� �ִ� �޼��� �ڽ� ó���� ���ؼ� 

	SI32 CompareKey(TCHAR *data, SI32 type);
	BOOL IsInputFocus();
	void SetSelectButton(SI16 TabButtonIndex);
	void MoveTabButtonToRight();	// ��Ű�� ������ ä���� ������ ���������� ��ĭ �ű��.
	void MoveTabButtonToLeft();	// ��Ű�� ������ ä���� ������ ���������� ��ĭ �ű��.
	void InsertChatHistory(TCHAR *ChatData);
	void GetChatHistoryPre();
	void GetChatHistoryNext();
	//KHY - 0110 - ä�� ��� ����
	SI16 GetChatTabIndex();
	bool GetFirstCreate();
	void SetFirstCreate(bool bFirst);

private:
	//KHY - 0110 - ä�� ��� ����
	bool m_bFirstCreate; 		//������ ������ ä��â�� �б� ���� ����.

	TCHAR		*m_strChatData;
	CChatStatusBarBuffer	*m_pChatBarBuffer;
	
	deque< stChatHistoryData > m_ChatHistoryDeque;
	deque< stChatHistoryData >::iterator m_ChatHistoryDequeItr;

	SI16		m_OpendsiSize;
	SI16		m_siRepeatCnt;
	//bool		m_bOpened;
	// ���� üũ.
	//NBitArray <CHTFILLTER_END>				m_bitChatstatus;

};	

#endif	//_NCHATBARDLG_H_
