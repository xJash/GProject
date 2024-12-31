#ifndef _FISHINGBASEINFO_H_
#define _FISHINGBASEINFO_H_

#define MAX_FISHKIND_NUMBER			100

#include "../CommonHeader.h"
#include "../Agriculture/Agriculture.h"

#define FISHINGROD_ATB_HOOK						0x00000001
#define FISHINGROD_ATB_STAND					0x00000002

#define MAX_BAIT_ITEM_NUMBER					10			// �̳��� �ִ� ����

#define MAX_FISHING_TOOL_NUMBER					10			// ���ÿ� �ʿ��� ������ �ִ� ����.
#define FISHING_TOOL_DURABILITY_DECREASE		5			// 5�� ���� ������ �������� ���δ�.

#define MAX_CREATE_FISH_PLACE_LIST				30			// 30 �������� �����ϰ� �����ȴ�.

enum { FISHING_PLACE_START, FISHING_PLACE_RIVER, FISHING_PLACE_SEASIDE, FISHING_PLACE_NEARSEA, FISHING_PLACE_FARSEA, FISHING_PLACE_END };


enum
{
	FISHING_SKILL_LEVEL_LOW = -5,			// ���� ������ ���Ƽ� ����
	FISHING_TOOL_NOTEXIST,				// ���� ����
	FISHING_TOOL_DURABILITY_TOO_LOW,	// ���� ������ ����
	FISHING_FAIL,						// ���ٰ� ����
	FISHING_GET_SCROLL,					// �ִ� ���� ���� ����.
	FISHING_GET_GOLD,					// �ݱ��� ����
	FISHING_SUCCESS						// ����
};



#endif
