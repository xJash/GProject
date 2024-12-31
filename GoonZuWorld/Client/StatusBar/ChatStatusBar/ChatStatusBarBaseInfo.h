#ifndef _CHATSTATUSBARBASEINFO_H_
#define _CHATSTATUSBARBASEINFO_H_

#include < Directives.h >

#include "..\..\..\Resource.h"
#include "../../../Common/CommonHeader.h"


#define		MAX_CHAT_DATA_RECORD_NUM					150		// 20�� ������ ��ȭ ������ ����ϰ� ����.
#define		MAX_CHAT_DATA_BUFFER_NUM					200		// �ִ� 50���� ���ۿ� ��� �� �� ����.



#define		WM_CHAT_DATA_INPUT							WM_USER+500

#define		CHAT_DATA_SEND								26500
#define		CHAT_DATA_RECV								26501

#define		WHISPER_CHAT_DATA_SEND						26511
#define		WHISPER_CHAT_DATA_RECV						26512

#define		WHISPER_CHAT_REJECT							26520

#define		TOWN_CHAT_DATA_SEND							26530		// ���� ����

#define		RESIDENTSNOTIFY_CHAT_DATA_SEND				26531		// �ֹ� ����

#define		HEAD_CHAT_DATA_SEND							26540		// ���� ä��

#define		RESIDENTS_CHAT_DATA_SEND					26550		// �ֹ� ä��

#define		PARTY_CHAT_DATA_SEND						26560		// ��Ƽ ä��

//#define		ASK_CHAT_DATA_SEND							26570		// �ʺ��ڰ� ����� ����ϴ�...

#define		KINGNOTIFY_CHAT_DATA_SEND					26580		// ��(����)�� ���� �Ҷ�

#define		NEWS_CHAT_DATA_SEND							26590		// �ڸ�â���� ������ ��

// _LEON_GUILD_CHAT
#define		GUILD_CHAT_DATA_SEND						26600		// ��� ��� ä��
//#define		GUILDNOTIFY_CHAT_DATA_SEND					26601		// ��� ��� ����


struct stChatStatusBarData
{
	SI16	si16Msg;
	TCHAR	strChatData[ MAX_CHAT_DATA_LENGTH ];
};

class CChatStatusBar;
//extern	CChatStatusBar	g_ChatStatusBar;

#endif