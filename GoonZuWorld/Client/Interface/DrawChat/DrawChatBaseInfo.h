#ifndef _DRAWCHATBASEINFO_H_
#define _DRAWCHATBASEINFO_H_

//#include <Graphic.h>

#include "..\..\StatusBar\ChatStatusBar\ChatStatusBarBaseInfo.h"
#include "..\..\FontManager\FontManager.h"

#define		MAX_CHAT_SURFACE_WIDTH			172				// ä�� ���� ũ��
#define		MAX_CHAT_SURFACE_HEIGHT			200				// ä�� ���� ũ��

#define		MAX_SHOPBANNER_TITLE_WIDTH		172				// ���� Ÿ��Ʋ ��� ���� ũ��
#define		MAX_SHOPBANNER_TITLE_HEIGHT		35				// ���� Ÿ��Ʋ ��� ���� ũ��

#define		CHAT_FONT_HEIGHT_SIZE			13				// ä�� ��Ʈ ���� ũ�� 

#define		DRAW_CHAT_IMAGE_NUM				10				// ä�� ��濡 ���Ǵ� �̹����� ���� ����

#define		AVERAGE_LINE_CHAR_NUM			14				// ���ٿ� ǥ���ϴ� ��� ���ڼ� ( byte ������ ) ���� �� : +-5

#define		CHAT_DELAY_TIME					150				// ä���� ȭ�鿡 ��Ÿ���� ������

enum { 
	LEFTTOP_IMAGE_SPR, 
	CENTERTOP_IMAGE_SPR, 
	RIGHTTOP_IMAGE_SPR, 
	LEFTCENTER_IMAGE_SPR, 
	CENTER_IMAGE_SPR, 
	RIGHTCENTER_IMAGE_SPR, 
	LEFTBOTTOM_IMAGE_SPR, 
	CENTERBOTTOM_IMAGE_SPR, 
	RIGHTBOTTOM_IMAGE_SPR, 
	TAIL_IMAGE_SPR 
};

enum { 
	USER_CHATTING, 
	ADVERTISE_CHATTING, 
	PRODUCTION_CHATTING, 
	NPC_CHATTING, 
	PERSONALSHOP_BANNER, 
	PERSONALSHOP_BANNER_PREMIUM,
	ELECTIONSTUMP
};


#endif
