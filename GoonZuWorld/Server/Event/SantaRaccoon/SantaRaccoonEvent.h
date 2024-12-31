#ifndef _SANTARACCOON_H_
#define _SANTARACCOON_H_

#include "../../../common/Event/event.h"

const SI32 MAX_SANTARACCOON_NUM				= 2;
const SI32 MAX_SANTARACCOON_POSITION_NUM	= 11;
const SI32 MAX_SANTARACCOON_MESSAGE_SIZE	= 256;

class CSantaRaccoon : public cltEvent
{
public:

	enum
	{
		START = 0,
		ACTION,
		DIE,
		ITEM,				//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� ���̰� ������ ȹ��.]
		END,
	};

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_SANTARACCOON_NUM>		m_bKilledSantaRaccoon;
	NSafeTArray<SI32, MAX_SANTARACCOON_NUM>		m_siSantaRaccoonID;
#else
	/// ��Ÿ������ �׾���?
	bool m_bKilledSantaRaccoon[MAX_SANTARACCOON_NUM];
	/// 2������ ��ձ�����ID
	SI32  m_siSantaRaccoonID[MAX_SANTARACCOON_NUM];
#endif

	/// ���� �����̸�
	TCHAR m_szAreaName[MAX_SANTARACCOON_POSITION_NUM][32];
	/// ���õ� ��ǥ�̸�
	TCHAR m_szSelectedAreaName[MAX_SANTARACCOON_NUM][32];

#ifdef _SAFE_MEMORY
	NSafeTArray<POINT, MAX_SANTARACCOON_POSITION_NUM>	m_ptPosition;
	NSafeTArray<SI32, MAX_SANTARACCOON_NUM>				m_siAreaIndex;
#else
	/// �ʱ�ȭ ��ǥ
	POINT m_ptPosition[MAX_SANTARACCOON_POSITION_NUM];

	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ������ ���� ������ �ε�����ȣ]
	SI32 m_siAreaIndex[MAX_SANTARACCOON_NUM];
#endif


	CSantaRaccoon();
	~CSantaRaccoon();

	void Init();
	void Start();
	void Action();
	void End();
	void SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae = NULL );
	void SetDieSantaRaccoon( bool Flag, SI32 KingGuriID, SI32 UserID );

	void MakeSantaRaccoon();

	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� ���Ͱ� �� �׾��°�?]
	bool MonsterAllDie(void);
};

#endif
