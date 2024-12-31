//_____________________________________________________________________
//
// Ȳ���� 2008-3-26
//
// ���� �̺�Ʈ - ���� ����.
//_____________________________________________________________________
#ifndef _MOSTERATTACK_H_
#define _MOSTERATTACK_H_

#include "../../CommonLogic/CommonLogic.h"



#define EVENT_SPECIALREWARD_COUNT		1			// ������ 2�� ���� �̺�Ʈ Ƚ�� (1��°���� 2�� ����, ������ �ƴ� ���� ���°�ΰ� �� ��)


class cltEventTimeManager;






// ���� ����.
class MosterInfo
{
public:
	enum{ 
			DIE,		// ������.
			LIVE		// ��Ҿ�.
		};
public:
	MosterInfo() 
	{  
		Clear();
	}
	void Clear(void)
	{
		ZeroMemory(this, sizeof(MosterInfo));
	}
	bool IsLive(void)
	{
		return m_bMosterLive;
	}
	
	void Live(SI32 _Monsterkind)
	{
		m_siMonsterkind = _Monsterkind; 
		m_bMosterLive   = LIVE;
	}
	void Die(void)
	{
		m_bMosterLive   = DIE;
	}

	void SetMonsterkind(SI32 _siMonsterkind)
	{
		m_siMonsterkind = _siMonsterkind;
	}

	SI32 GetMonsterkind(void)
	{
		return m_siMonsterkind;
	}
	void SetMonsterID(SI32 _siMonsterID)
	{
		m_siMonsterID = _siMonsterID;
	}

	SI32 GetMonsterID(void)
	{
		return m_siMonsterID;
	}

	void SetMapIndex(SI32 _MapIndex)
	{
		m_MapIndex = _MapIndex;
	}

	SI32 GetMapIndex(void)
	{
		return m_MapIndex;
	}
	
private:
	SI32		m_siMonsterkind;	// ���� ����.
	SI32		m_siMonsterID;		// ������ ���� ID.
	bool		m_bMosterLive;		// ���� ��ҳ�? �׾���?
	SI32		m_MapIndex;			// ���� ���� �� �ε���.
};

// ���� �̺�Ʈ Ŭ���� 
class CMonsterAttackEvent
{
public:
	enum{ 
			EVENT_END		  = 0,	
			EVENT_START		  = 1,
			MOSTER_NUM		  = 7,		// �����ϴ� ���� ��.
			RUN_TIME		  = 50,		// ����ð�.
//			REWARD_ITEMUNIQUE = 8113,	// ���� ������ ����ũ.
//			REWARD_ITEMNUM	  = 3,		// �������� �ִ� �������� ����.
		};

public:
	CMonsterAttackEvent();
	~CMonsterAttackEvent();

	bool		IsEvent(void);								// �̺�Ʈ ���ΰ�.
	void		StartEvent(SI32 _siEventVillageUnique);		// �̺�Ʈ ����.
	void		EndEvent(bool b_GiveReward = false);		// �̺�Ʈ ����.
	void		Action(void);								// �׼�.^0^
	void		MonsterDie( SI32 _DieMonsterKind );			// �ش� ���Ͱ� �״�.
		
	SI16		GetEventVillageUnique(void)						{ return m_siEventVillageUnique;				}
	SYSTEMTIME*	GetStartTime(void)								{ return &m_stStartTime;						}	

public:
	void		Clear(void);
	void		CreateMonster(void);						// ���� ����.
	void		DestroyMonster(void);						// ���� ����.
	void		DrawWantedMonster(void);					// Ŭ�󿡼� ���� ���� ���� �׸���.
	
	
	void		EventReward(void);								// ����.
	bool		TimeOver(void);								// �ð��� ������.
	bool		MonsterAllDie(void);						// ���Ͱ� �� �׾��°�.
	void		RandMap(void);								// ������ �����ϰ� �̾��ش�.
	void		SetMonsterKind(void);						// ���� ���� ����.
	void		SendMsg(SI32 _para1, SI32 _para2 = 0);
	bool		NotifyTime(void);								
	void		RemainTime(void);
		
	void		SetEventVillageUnique(SI16 _EventVillageUnique) { m_siEventVillageUnique = _EventVillageUnique;					}	
	void		SetStartTime(SYSTEMTIME* _stStartTime)			{ memcpy(&m_stStartTime, _stStartTime, sizeof(m_stStartTime));	}
	

public:
	bool				m_bEvent;						// �̺�Ʈ ����.
	SYSTEMTIME			m_stStartTime;					// ���۽ð�.
	SYSTEMTIME			m_stEndTime;					// ����ð�.
	SI16				m_siEventVillageUnique;			// �̺�Ʈ ���� ����ũ.

#ifdef _SAFE_MEMORY
	NSafeTArray<MosterInfo, MOSTER_NUM>		m_siMosterInfo;
#else
	MosterInfo			m_siMosterInfo[MOSTER_NUM];		// ���� ����.
#endif

	DWORD				m_dwStartTickCount;
	DWORD				m_dwRemainSecondTime;

	// �̺�Ʈ Ƚ�� ī��Ʈ�� Ƚ�� ���� ���� �Լ���
public:
	//SI16				m_siMonsterAttackEventCount;
	NSafeTArray<SI16, MAX_VILLAGE_NUMBER>		m_arEventCount_EachVillage;
	void				MonsterAttack_EventCount_Increase();
	void				MonsterAttack_EventCount_Reset();
	SI16				MonsterAttack_EventCount_Get();
};

#endif