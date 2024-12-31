#ifndef _BLACKWAR_
#define _BLACKWAR_

#include "../../CommonLogic/CommonLogic.h"

#define MAX_BLACKWAR_UNIT			10

const SI32 REWARD_ITEMUNIQUE[] = { 5090, 5100, 5056, 5200, 5057, 5010, 5050, 5075, 5017, 
5065, 5080, 5030, 5070, 5000, 5040, 5060, 5020, 5025 };

const SI32 REWARD_ITEMUNIQUE_PERCENT[] = { 12, 12, 11, 11, 10, 7, 7, 6, 3,
3,   3,  3,  2,  2, 2, 2, 2, 1 };

//***************************************************************************************************
//
// Class Name 		: CBlackWarUnit
//
// Last Modified 	: 2007 / 04 / 11
// Created		 	: �豤��
//
// Function			: ���Ǳ��� ���� ����
//
//***************************************************************************************************
class CBlackWarUnit
{
public:

	SI32 m_siKind;
	SI32 m_siNum;			// ���� �ֺ��� ���ð͵�
	SI32 m_siRate;
	SI32 m_siBasicLevel;
	SI32 m_siRandLevel;
	SI32 m_siCurNum;

public:

	CBlackWarUnit() : m_siKind(0), m_siNum(0), m_siRate(0), m_siBasicLevel(0), m_siRandLevel(0), m_siCurNum(0)
	{
	};

	CBlackWarUnit(SI32 Kind, SI32 Num, SI32 Rate, SI32 CurNum, SI32 Basic, SI32 Rand) :
	m_siKind(Kind), m_siNum(Num), m_siRate(Rate), m_siCurNum(CurNum), m_siBasicLevel(Basic), m_siRandLevel(Rand)
	{
	};

	void Init()
	{
		m_siKind		= 0;
		m_siNum			= 0;
		m_siRate		= 0;
		m_siBasicLevel	= 0;
		m_siRandLevel	= 0;
		m_siCurNum		= 0;
	}

	SI32 GetKind() { return m_siKind;}
	SI32 GetNum() { return m_siNum;}
	SI32 GetRate() { return m_siRate;}
	SI32 GetBasicLevel() { return m_siBasicLevel;}
	SI32 GetRandLevel() { return m_siRandLevel;}
	SI32 GetCurNum() { return m_siCurNum;}
};

//***************************************************************************************************
//
// Class Name 		: CBlackWarManager
//
// Last Modified 	: 2007 / 04 / 11
// Created		 	: �豤��
//
// Function			: ���Ǳ��� �Ŵ���
//
//***************************************************************************************************
class CBlackWarManager
{
private:

#ifdef _SAFE_MEMORY
	NSafeTArray<CBlackWarUnit, MAX_BLACKWAR_UNIT>		m_clBlackWarUnit;
#else
	CBlackWarUnit m_clBlackWarUnit[MAX_BLACKWAR_UNIT];
#endif

	// ���� ������ �������ΰ�?
	bool	m_bBlackWarSwitch;	

	// ��ü �����. 
	SI32	m_siTotalUnitNumber;		

	// ���� �����. 
	SI32	m_siCurUnitNumber;		

	// ������� ������� ��. 
	SI32	m_siMadeNumber;			

	// ����Ʈ�� �� ���� �ִ°�?
	SI32	m_siAddUnitNumber;		

	// ����� ����. 
	SI32	m_siCasualtyNumber;		

	// ���� �ð�. (ms) 
	DWORD	m_dwLeftTimeClock;	

	// ������ �ð�
	DWORD	m_dwBlackWarStartClock;

	// ���� ���� ����.
	SI32	m_siLeftUnitNumber;		

	bool	m_bDieBossSwitch;
	bool	m_bMakeBossSwitch;
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, 4>							m_bMakeMiddleBossSwitch;
	NSafeTArray<SI32, MAX_WARRANK_PERSON_PER_MAP>	m_siRewardCharID;
#else
	bool	m_bMakeMiddleBossSwitch[4];

	SI32	m_siRewardCharID[MAX_WARRANK_PERSON_PER_MAP];
#endif


	// ���￡�� �̰�°�?
	bool	m_bWinSwith;

	// ������ ������ �ð�
	SI32	m_siStartHour;

	SI32	m_siKillBlackUnitNumber;

	// ������ ���� �ð�
	DWORD	m_dwBlackWarEndClock;
	// ������ ���￡�� MVP PersonID
	SI32	m_siMVPPersonID;

	//------------
	// ��� 
	//------------
	bool	m_bDrawSwitch;
	SI32	m_siDrawCmdFont;
	DWORD   m_dwDrawStartClock;

public:

	CBlackWarManager();
	~CBlackWarManager();

	void Init();

	// ������ ��ȹ�Ѵ�. 
	bool MakeWar( DWORD ClocK, SI32 StartHour );
	// ���� ���ָ� �߰��Ѵ�. 
	void AddBlackWarUnit( SI32 Kind, SI32 UnitNumber );

	// ������ ���� ���´�
	void WarEnd();

	// ���� �׼� (����) 
	void Action();

	void SendWarMsg( SI32 Cmd, SI32 Mapindex, SI32 X, SI32 Y, bool MakeBoss );

	void BlackWarReward( bool Flag );

	void SetDraw(SI32 Cmd);
	// ��Ȳ�� ǥ���Ѵ�. (Ŭ���̾�Ʈ) 
	void Draw( LPDIRECTDRAWSURFACE7 lpsurface, SI32 Rx, SI32 Ry );

	void SetBlackWar( bool Flag )
	{
		m_bBlackWarSwitch = Flag;
	}
	bool IsBlackWar()
	{
		return m_bBlackWarSwitch;
	}

	void SetDieBoss( bool Flag )
	{
		m_bDieBossSwitch = Flag;
	}

	void SetLeftTime( DWORD LeftClock )
	{
		m_dwLeftTimeClock = LeftClock;
	}

	bool IsWinSwitch()
	{
		return m_bWinSwith;
	}

	void SetStartHour( SI32 StartHour )
	{
		m_siStartHour = StartHour;
	}

	SI32 GetStartHour()
	{
		return m_siStartHour;
	}

	void IncreaseKillBlackUnitNumber()
	{
		m_siKillBlackUnitNumber++;
	}

	bool IsMVPPersonID( SI32 PersonID )
	{
	//	return m_siMVPPersonID == PersonID ? true : false;
		if( m_siMVPPersonID == PersonID )
		{
			return true;
		}
		else
			return false;
	}
	//[����] ���� ������ ���� ���� ǥ���ϰ� ��Ŷ�� ���� ��. => 2008-4-10
	void VillageRecordList(void);
};

#endif