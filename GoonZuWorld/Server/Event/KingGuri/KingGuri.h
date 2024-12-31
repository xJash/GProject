#ifndef _KINGGURI_H_
#define _KINGGURI_H_

#include "../../../common/Event/event.h"

const SI32 MAX_KINGGURI_NUM = 3;
const SI32 MAX_POSITION_NUM = 11;
const SI32 MAX_MESSAGE_SIZE = 256;

const WORD KingGuriEventStartTime[] =
{
		12, 0,
		13, 0,
		18, 40,
		19, 40,
		20, 40,
		21, 40
};

class CKingGuriEvent : public cltEvent
{
public:

	enum
	{
		START = 0,
		ACTION,
		DIE_KINGGURI,
		ITEM,				//[�߰� : Ȳ���� 2007. 11. 14 ��� ������ ���̰� ������ ȹ��.]
		END,
	};

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_KINGGURI_NUM>		m_bKilledKingGuri;
	NSafeTArray<SI32, MAX_KINGGURI_NUM>		m_siKingGuriID;
#else
	/// ��ձ������� �׾���?
	bool m_bKilledKingGuri[MAX_KINGGURI_NUM];
	/// 2������ ��ձ�����ID
	SI32  m_siKingGuriID[MAX_KINGGURI_NUM];
#endif
	/// ���� �����̸�
	TCHAR m_szAreaName[MAX_POSITION_NUM][32];
	/// ���õ� ��ǥ�̸�
	TCHAR m_szSelectedAreaName[MAX_KINGGURI_NUM][32];

#ifdef _SAFE_MEMORY
	NSafeTArray<POINT, MAX_POSITION_NUM>	m_ptPosition;
	NSafeTArray<SI32, MAX_KINGGURI_NUM>		m_siAreaIndex;
#else
	/// �ʱ�ȭ ��ǥ
	POINT m_ptPosition[MAX_POSITION_NUM];

	//[�߰� : Ȳ���� 2007. 11. 13 ��� �������� ���� ������ �ε�����ȣ]
	SI32 m_siAreaIndex[MAX_KINGGURI_NUM];
#endif

	CKingGuriEvent();
	~CKingGuriEvent();

	void Init();
	void Start();
	void Action();
	void End();
	void SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae = NULL );
	void SetDieKingGuri( bool Flag, SI32 KingGuriID, SI32 UserID );

	void MakeKingGuri();
	
	//[�߰� : Ȳ���� 2007. 11. 14 ��� ������ ���Ͱ� �� �׾��°�?]
	bool MonsterAllDie(void);
};

#endif
