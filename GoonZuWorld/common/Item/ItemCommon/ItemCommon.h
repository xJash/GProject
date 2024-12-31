//---------------------------------
// 2003/6/24 ���°�
//---------------------------------
#ifndef _ITEMCOMMON_H
#define _ITEMCOMMON_H

#include "..\..\..\Lib\EtcTool\EtcTool.h"

#define MAX_ITEMINFO_NUMBER		1500
#define MIN_DUR_FOR_REPAIR		60		// ������ �ϱ� ���� �ּ� ������. �� ���Ͽ����� ���� �Ұ�.

#define LOW_DURABILITY_NOTIFY	30		// ������ �������� �˸��� ���� ( ���� 30 ���� )

#define RARELEVEL_1				2		// ȣǰ ���. 	
#define RARELEVEL_2				1		// ��ǰ ���. 
#define RARELEVEL_3				3		// �ű� ���. 
#define RARELEVEL_4				4		// ��ǰ ���. 
#define RARELEVEL_5				5		// ���ǰ ���. 
#define RARELEVEL_6				6		// ��ǰ ���. 

#define NEWYEAR_EFFECT			7		// [�߰� : Ȳ���� 2007. 12. 12 �ų� �̺�Ʈ �Ⱓ���� ���� ������ ��¦!]

#define MARRIED_FULLDRESS_EFFECT	8	// �߰� : ��ȥ���� ����Ʈ

#define MAX_ATTENDANCE_COUNT	100		// 100�ϱ��� ������ ������ �� �ִ�.

// [����] ���ڴ� ���� (2008.06.05)
const SI32 CONST_JOURNALIST_HAT_ITEMUNIQUE = /*ITEMUNIQUE*/(23470);

enum ITEMREPAIR_MODE
{
	ITEMREPAIR_MODE_NONE = 0,

	ITEMREPAIR_MODE_SELF,				// ��������
	ITEMREPAIR_MODE_REQUEST,			// ���� �Ƿ�
	ITEMREPAIR_MODE_REQUEST_PRECESS,	// ���� �Ƿ�ǰ ����
	ITEMREPAIR_MODE_CANCEL,				// ���� �Ƿ��� ���
	ITEMREPAIR_MODE_GROWUP_MAX,			// �ִ� ������ ����
	ITEMREPAIR_MODE_NPC,				// NPC�� ���� ����

	ITEMREPAIR_MODE_MAX
	
};

// ������ ���� ��û �̿��
const SI32 Const_RepairRequestTicket_ItemUnique = /*ITEMUNIQUE*/(24124);


class cltAttendanceReward
{
public:
	SI16	m_siItemUnique;
	SI16	m_siItemNum;
	SI16	m_uiDateUseDay;

public:
	cltAttendanceReward()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

#endif