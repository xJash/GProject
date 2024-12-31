#ifndef _RICHEDITCHATMGRDLGBASEINFO_H_
#define _RICHEDITCHATMGRDLGBASEINFO_H_

#include <Directives.h>
#include "..\..\..\Resource.h"
#include <windows.h>

#define MAX_RICHEDIT_CHAT_RECORD_NUM					80		// �ִ� 80���� ä���� �����.
#define MAX_RICHEDIT_OBJ_SIZE							500		// �ִ� 500 Byte�� �����Ϳ� �Ҵ� ��.

#include "..\..\StatusBar\ChatStatusBar\ChatStatusBarBaseInfo.h"

#define MSG_RICHEDIT_CHAT_RECV							12500
#define MSG_RICHEDIT_RESIDENTSCHAT_RECV					12505
#define MSG_RICHEDIT_PARTYCHAT_RECV						12510                 
#define MSG_RICHEDIT_MASTERNOTIFYCHAT_RECV				12515
#define MSG_RICHEDIT_VILLAGENOTIFYCHAT_RECV				12520
#define MSG_RICHEDIT_RESIDENTSNOTIFYCHAT_RECV			12525
#define MSG_RICHEDIT_KINGNOTIFYCHAT_RECV				12530
#define MSG_RICHEDIT_GOODSPRODUCTIONNOTIFYCHAT_RECV		12535
#define MSG_RICHEDIT_GUILDCHAT_RECV						12540
//#define MSG_RICHEDIT_QUIZCHAT_RECV						12535

#define RICHEDIT_BLACK_COLOR				RGB(0,0,0)
#define RICHEDIT_RED_COLOR					RGB(255,0,0)
#define RICHEDIT_GREEN_COLOR				RGB(18,135,51)
#define RICHEDIT_BLUE_COLOR					RGB(0,0,255)
#define RICHEDIT_YELLOW_COLOR				RGB(117,62,14)


// �� ��Ʈ�� ����
enum { TAB_MODE_CHAT = 0, TAB_MODE_RESIDENTSCHAT ,TAB_MODE_GUILDCHAT, TAB_MODE_PARTYCHAT, TAB_MODE_DEAULT};

struct stRichEditChatDataSend
{
	SI16	si16Msg;
	char	strChatData[ MAX_CHAT_DATA_LENGTH ];
};

struct stRichEditChatMgrHeader
{
	SI16 siMsgSize;				// �޽��� ������
	SI16 siMsgKind;				// �Ϲ� ä���̳� �ֹ� ä���̳� ���� ��.
	COLORREF NameColor;			// ����� ���� ( �̸� )
	COLORREF TextColor;			// ����� ���� ( �ؽ�Ʈ )
};

// �Ϲ� ä��
struct stRichEditChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];		// ��ĭ ���� �� ':' �̷� ǥ���ϰ� �ؾ� �Ǳ� ����
	char strChatData[ MAX_CHAT_DATA_LENGTH ];
	
	stRichEditChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_CHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLACK_COLOR;
	}
	stRichEditChatRecv(SI16 kind)
	{
		sHeader.siMsgSize = sizeof( stRichEditChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_CHAT_RECV;

		switch( kind )
		{
		case TAB_MODE_CHAT:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_BLACK_COLOR;
			}
			break;

		case TAB_MODE_RESIDENTSCHAT:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_GREEN_COLOR;
			}
			break;

		case TAB_MODE_GUILDCHAT:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_RED_COLOR;
			}
			break;

		case TAB_MODE_PARTYCHAT:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_YELLOW_COLOR;
			}
			break;

		case TAB_MODE_DEAULT:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_BLACK_COLOR;
			}
			break;

		default:
			{
				sHeader.NameColor = RICHEDIT_BLUE_COLOR;
				sHeader.TextColor = RICHEDIT_BLACK_COLOR;
			}
			break;
		}
	}
};

//��� ä�� 
struct stRichEditGuildChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];		// ��ĭ ���� �� ':' �̷� ǥ���ϰ� �ؾ� �Ǳ� ����
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditGuildChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditGuildChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_GUILDCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_RED_COLOR;
	}

};

//��Ƽ ä�� 
struct stRichEditPartyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];		// ��ĭ ���� �� ':' �̷� ǥ���ϰ� �ؾ� �Ǳ� ����
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditPartyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditPartyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_PARTYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_YELLOW_COLOR;
	}

};
// �ֹ� ä��
struct stRichEditResidentsChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditResidentsChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditResidentsChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_RESIDENTSCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_GREEN_COLOR;
	}
};

// ��� ����
struct stRichEditMasterNotifyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];	
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditMasterNotifyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditMasterNotifyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_MASTERNOTIFYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLUE_COLOR;
	}
};

// ������� ���� ����
struct stRichEditVillageNotifyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];	
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditVillageNotifyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditVillageNotifyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_VILLAGENOTIFYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLUE_COLOR;
	}
};

// ������� �ֹ� ����
struct stRichEditResidentsNotifyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];	
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditResidentsNotifyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditResidentsNotifyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_RESIDENTSNOTIFYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLUE_COLOR;
	}
};

struct stRichEditKingNotifyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];	
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditKingNotifyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditKingNotifyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_KINGNOTIFYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLUE_COLOR;
	}
};

// ��ǰ ���� �� ���� �˸�
struct stRichEditGoodsProductionNotifyChatRecv
{
	stRichEditChatMgrHeader sHeader;
	char strUserID[ MAX_PLAYER_NAME + 10 ];	
	char strChatData[ MAX_CHAT_DATA_LENGTH ];

	stRichEditGoodsProductionNotifyChatRecv()
	{
		sHeader.siMsgSize = sizeof( stRichEditGoodsProductionNotifyChatRecv );
		sHeader.siMsgKind = MSG_RICHEDIT_GOODSPRODUCTIONNOTIFYCHAT_RECV;
		sHeader.NameColor = RICHEDIT_BLUE_COLOR;
		sHeader.TextColor = RICHEDIT_BLUE_COLOR;
	}
};


#endif