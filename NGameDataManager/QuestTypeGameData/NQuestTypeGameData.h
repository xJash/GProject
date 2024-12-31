//=============================================================================
//
//=============================================================================
#ifndef _NQUESTGAMEDATA_H_
#define _NQUESTGAMEDATA_H_

#include "../../NetworkLib/ITZNetLib/itzbase.h"

//---------------------------------
// ����Ʈ Ÿ�� 
//---------------------------------
#define MAX_QUEST_TYPE				20
#define QUEST_TYPE_SPECIAL			0	// ����� ����Ʈ. 
#define QUEST_TYPE_BATTLE1			1	// ���� ����. (�����������)
#define QUEST_TYPE_MAKEHEAL1		2	// ���� ������
#define QUEST_TYPE_MAKESWORD1		3	// ���� ��������
#define QUEST_TYPE_MAKEBOW1			4	// ���� Ȱ������
#define QUEST_TYPE_MAKEHELMET1		5	// ���� ����������
#define QUEST_TYPE_BEGINNER3		6	// ����ȣ ����Ʈ 
#define QUEST_TYPE_MAKESPEAR1		7	// ���� â������
#define QUEST_TYPE_MAKEARMOUR1		8	// ���� ������
#define QUEST_TYPE_MAKEAX1			9	// ���� ������
#define QUEST_TYPE_MAKEGUN1			10	// �� ������
#define QUEST_TYPE_MAKESTAFF1		11	// ������ ������
#define QUEST_TYPE_MAKEBELT1		12	// ��� ������
#define QUEST_TYPE_MAKESHOES1		13	// �Ź� ������
#define QUEST_TYPE_BEGINNER2		14	// ���� ����Ʈ 
#define QUEST_TYPE_BATTLE2			15	// ���� ����Ʈ
#define QUEST_TYPE_BASIC1			16	// ���� ���. (����� ����Ʈ)
#define QUEST_TYPE_BEGINNER4		17	// ���˼�����Ʈ
#define QUEST_TYPE_MAKEBEGINNER1	18	//�ʺ��ڸ� ���� ���� ����Ʈ
#define QUEST_TYPE_BEGINNER5		19	// ��������Ʈ(���� ����)

#define MAX_QUEST_PER_TYPE_NUMBER	32	// �ϳ��� ����Ʈ Ÿ�Դ� �ִ� ����Ʈ ��. 

class NQuestTypeGameData
{
public:
	SI32		m_siQuestType;
	TCHAR		m_szQuestName[128];
	SI32		m_siQuestUnique[MAX_QUEST_PER_TYPE_NUMBER];

public:
	NQuestTypeGameData()
	{
		m_siQuestType		= -1;
		m_szQuestName[0]	= '\0';
		memset(m_siQuestUnique, 0, sizeof(m_siQuestUnique));
	}

	~NQuestTypeGameData()
	{
	}

	void Set()
	{

	}
};

#endif
