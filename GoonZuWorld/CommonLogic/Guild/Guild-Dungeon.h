#pragma once

#include <Directives.h>

#include "CommonHeader.h"
#include "../../CommonLogic/Guild/Guild.h"
#include "../../CommonLogic/Guild/Guild-Dungeon.h"

class cltGuildDungeonUnit
{
public:
	SI32	m_siMapIndex;			//�ʵ� �ε���
	SI32	m_siGuildUnique;		//�������� ������ �ִ� ����ε���
	SI32	m_siExp;				//������ ����ġ(�Ϸ絿��, ������ DB�� ������ ����)
	GMONEY	m_siMoney;				//������ ��(�Ϸ絿��, ������ DB�� ������ ����)

public:
	cltGuildDungeonUnit(){ Init(); }
	~cltGuildDungeonUnit(){}

	void Init()
	{
		m_siMapIndex = 0;
		m_siExp = 0;
		m_siMoney = 0;
		m_siGuildUnique = 0;
	}

	void AddExp( SI32 exp )			{ m_siExp += exp; }
	void AddMoney( GMONEY money )	{ m_siMoney += money; }

	SI32 GetMapIndex()	{ return m_siMapIndex; }
	void SetMapIndex( SI32 mapindex )	{ m_siMapIndex = mapindex; }

	SI32 GetGuildUnique()	{ return m_siGuildUnique;}
	void SetGuildUnique(SI32 guildunique) { m_siGuildUnique = guildunique; }

	SI32 GetExp()			{ return m_siExp; }
	void SetExp(SI32 exp )	{ m_siExp = exp; }

	GMONEY GetMoney()		{ return m_siMoney; }
	void SetMoney(GMONEY money)	{ m_siMoney = money; }

};



#define MAX_GUILDDUNGEON 30
#define MAX_GUILDDUNGEONAPPLY	50		// �Ѱ��� ����Ϳ� �ִ� ��û���� ����

#define GUILDDUNGEON_GIVEGPRATIO		0.03f
#define GUILDDUNGEON_GIVEMONEYRATIO		0.03f

// PCK : �߱�, ������ �ں���, GP ���� �ۼ�Ʈ�� 0.03%�� �ǵ��� �Ѵ�. (09.04.14)
#define GUILDDUNGEON_GIVEGPRATIO_EXCEPTION			0.0003f
#define GUILDDUNGEON_GIVEMONEYRATIO_EXCEPTION		0.0003f

inline GMONEY Calc_GiveMoney(GMONEY x)	{ return (GMONEY)(x * GUILDDUNGEON_GIVEMONEYRATIO); }
inline SI32 Calc_GiveGP(SI32 x)		{ return (SI32)(x * GUILDDUNGEON_GIVEGPRATIO); }

// PCK : �߱�, ������ �ں���, GP ���� �ۼ�Ʈ�� 0.03%�� �ǵ��� �Ѵ�. (09.04.14)
inline GMONEY Calc_GiveMoney_Exception(GMONEY x)	{ return (GMONEY)(x * GUILDDUNGEON_GIVEMONEYRATIO_EXCEPTION); }
inline SI32 Calc_GiveGP_Exception(SI32 x)		{ return (SI32)(x * GUILDDUNGEON_GIVEGPRATIO_EXCEPTION); }

class cltGuildDungeonMgr
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltGuildDungeonUnit, MAX_GUILDDUNGEON>	m_clUnit;
#else
	cltGuildDungeonUnit	m_clUnit[MAX_GUILDDUNGEON];
#endif
	clock_t	m_UpdateDBClock;		// DB�� ���� �ð����� ����;
	WORD	m_SendDBDay;


public:
	cltGuildDungeonMgr();
	~cltGuildDungeonMgr();

	void SetDungeon();

	void SetStatus( SI32 mapindex, SI32 guildunque, SI32 exp, GMONEY money );

	void AddExp( SI32 mapindex, SI32 exp );
	void AddMoney( SI32 mapindex, GMONEY money );

	SI32 GetExp( SI32 mapindex );
	GMONEY GetMoney( SI32 mapindex );

	SI32 GetMapIndex( SI32 guildunique );

	bool CanApplyGuildDungeon( SI32 mapindex );

	void Action();

	void UpdateDB();			// DB�� ����Ȳ�� ������Ʈ �Ѵ�.(1�и���)
	void LoadFromDB();			// DB�� ����� ������ �ҷ��´�.(�������۽�)
	void MoveProcess();			// ȹ�� ����ġ, �� �й� �� ������ �����۾�
};



// ������ ������ ����
class cltGuildDungeonStatus
{
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_GUILDDUNGEON>		m_siMapIndex;
	NSafeTArray<SI32, MAX_GUILDDUNGEON>		m_siGuildUnique;
	NSafeTArray<SI32, MAX_GUILDDUNGEON>		m_siExp;
	NSafeTArray<SI32, MAX_GUILDDUNGEON>		m_siMoney;
#else
	SI32	m_siMapIndex[MAX_GUILDDUNGEON];
	SI32	m_siGuildUnique[MAX_GUILDDUNGEON];
	SI32	m_siExp[MAX_GUILDDUNGEON];
	SI32	m_siMoney[MAX_GUILDDUNGEON];
#endif
};

