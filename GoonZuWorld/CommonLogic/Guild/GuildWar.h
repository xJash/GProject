#pragma once


#include "guild.h"
#include "../../common/map/map.h"

#define GUILDWAR_FIELDNUM			5	// ����� �ʵ� 195~199	->	���� ����� �ʵ�� ������Ű�� ���ο� ��������� ����Ѵ�
#define GUILDWAR_FIELDNUM_OLD		3	// ����� �ʵ� 369~371 -> �Ϲ� ������� 3���� ��� �Ǹ鼭 ����� ���� �ű��.
#define	GUILDWAR_ROOMNUM			48				// 30�� �������� �Ϸ�����ο���
#define	GUILDWAR_MAXCOUNT			3				// �Ϸ翡 �Ҽ��ִ� ������ִ� Ƚ��

#define	GUILDWAR_MINLEVEL			4				// ����� �Ҽ� �ִ� �ּ� ����

#define GUILDWARFIELD_INDEX			195				// ����� �ʵ� 195~199	->	���� ����� �ʵ�� ������Ű�� ���ο� ��������� ����Ѵ�
#define GUILDWARFIELD_INDEX_OLD		369				// ����� �ʵ� 369~371 -> �Ϲ� ������� 3���� ��� �Ǹ鼭 ����� ���� �ű��.

#define GUILDWAR_TIME				10				// ���� ���� �ð�
#define GUILDHUNTWAR_TIME			15				// ����� ���� ���� �ð�

#define GUILDWAR_GODTIME			10000			// ����� �����ð�
#define GUILDWAR_MAX_APPLYCOUNT		3				// ���� ��û ���� Ƚ��


#define GUILDWAR_RESERVE_SUCCESS						0x000001	// ���� �ð��� �̹� ������ �ߴ�
#define GUILDWAR_RESERVE_FAIL_ALREADYRESERVE			0x000002	// ���� �ð��� �̹� ������ �ߴ�
#define GUILDWAR_RESERVE_FAIL_ENEMY_ALREADYRESERVE		0x000004	// ���� �ð��� �̹� ������ �ߴ�
#define GUILDWAR_RESERVE_FAIL_ENEMY_OVERTIME			0x000008	// ���� �ð��� �̹� ������ �ߴ�

const SI32 Const_HomePos[] = {
	15, 25,
	17, 23,
	21, 35,
	24, 33
};
const SI32 Const_AwayPos[] = {
	23, 17,
	25, 15,
	33, 24,
	35, 21,
};

const inline SI32 GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( SI32 mapindex )	// ������
{
	return mapindex - GUILDWARFIELD_INDEX_OLD;	// ���ο� ������� ���鼭 ������ �õ尡 �Ǽ� �����Ѵ�.
}
const inline SI32 GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( SI32 mapindex )	// ������
{
	return mapindex - GUILDWARFIELD_INDEX;	// ���ο� ������� ���鼭 ������ �õ尡 �Ǽ� �����Ѵ�.
}
const inline SI32 GetHuntmapGuildWarFieldIndexFromMapIndex( SI32 mapindex )// ���� ������ĺ��� ����� �� Ȯ��.
{
	return mapindex - GUILDWARFIELD_INDEX; 
}

inline const bool IsGuildWarMap_Use_New_GuildWar( SI32 mapindex )	/// ����� ������� �̰ſ��� ���� ����
{
	if( mapindex >= MAPINDEX_GUILDWARFIELD_OLD && mapindex < MAPINDEX_GUILDWARFIELD_OLD + GUILDWAR_FIELDNUM_OLD )
	{
		return true;
	}
	else
	{
		return false;
	}

}
inline const bool IsGuildWarMap_Not_Use_New_GuildWar( SI32 mapindex )	/// ������� ���� ������� �̰ſ��� ���� ����
{
	if( mapindex >= MAPINDEX_GUILDWARFIELD && mapindex < MAPINDEX_GUILDWARFIELD + GUILDWAR_FIELDNUM )
	{
		return true;
	}
	else
	{
		return false;
	}

}
inline const bool IsGuildWarMap_NEW( SI32 mapindex )	// ���ο� ������� �̰ɷ� ������ Ȯ��.
{
	if( mapindex >= MAPINDEX_GUILDWARFIELD && mapindex < MAPINDEX_GUILDWARFIELD + GUILDWAR_FIELDNUM )
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ����� ���� ����
//---------------------------------------------------------------
// cltGuildWarReserveUnit
//---------------------------------------------------------------
class cltGuildWarReserveUnit
{
public:
	SI32		m_siRoomIndex;
	SI32		m_siHomeGuildUnique;
	TCHAR		m_szHomeGuildName[MAX_GUILD_NAME];
	SI32		m_siAwayGuildUnique;
	TCHAR		m_szAwayGuildName[MAX_GUILD_NAME];

	bool		m_bWarStart;

	cltGuildWarReserveUnit(){ Init(); }
	~cltGuildWarReserveUnit(){}

	void Init()
	{
		m_siRoomIndex = 0;
		m_siHomeGuildUnique = 0;
		m_siAwayGuildUnique = 0;
		StringCchCopy( m_szHomeGuildName, MAX_GUILD_NAME, TEXT("") );
		StringCchCopy( m_szAwayGuildName, MAX_GUILD_NAME, TEXT("") );
		m_bWarStart = false;
	}

	void Set( SI32 roomindex, SI32 homeguildunique, TCHAR* homeguildname, SI32 awayguildunique, TCHAR* awayguildname );
	void Set( cltGuildWarReserveUnit* pUnit );

	void WarStart( SI32 fieldindex );

	bool IsStartWar()	{ return m_bWarStart; };		// ���۵Ǿ��ִ°�
	bool IsReady();										// ���� ���۵� �غ� ���ִ°�
};


enum{
	GUILDWAR_APPLY_SUCCESS = 1,
	GUILDWAR_APPLY_FAILED_ALREADY_HOME,	// �츮 ��尡 ���� �̹� �����߰ų� ����Ǿ��ִ�
	GUILDWAR_APPLY_FAILED_ALREADY_AWAY,	// ��� ��尡 ���� �̹� �����߰ų� ����Ǿ��ִ�
	GUILDWAR_APPLY_FAILED_FAULTNAME,	// �׷� �̸��� ���� ����.
	GUILDWAR_APPLY_FAILED_MYGUILD,		// �ڽ��� ��忡 ��û�Ϸ��� �ߴ�
	GUILDWAR_APPLY_FAILED_ALREADYAPPLY,	// �̹� ���� ��û����
	GUILDWAR_APPLY_FAILED_LOWLEVEL,		// ������ ���Ƽ� �Ұ�
	GUILDWAR_APPLY_FAILED_COUNTOVER,	// ��ûȽ��(3ȸ) �ʰ�
	GUILDWAR_APPLY_FAILED_UNKNOWN		// �ٸ� ������ ���ؼ�
};

//---------------------------------------------------------------------
// cltGuildWarReserveManager
//---------------------------------------------------------------------
class cltGuildWarReserveManager
{
public:
	NSafeTArray< NSafeTArray<cltGuildWarReserveUnit, GUILDWAR_ROOMNUM>, GUILDWAR_FIELDNUM>	m_clUnit;	// �ٲ�� ������ ���ؼ� ��ü ������ ������ �ʴ´�.

	SI16					m_siToday;			// ���� ��¥�� ����Ѵ�.

	cltGuildWarReserveManager();
	~cltGuildWarReserveManager();

	void Init();
	void Set( cltGuildWarReserveManager* pclinfo );

	// ����
	void ServerAction();
	// ���� ��û�Ѵ�.
	SI32 ApplyReserve( SI32 fieldindex, SI32 roomindex, SI32 homeguild, SI32 awayguild);

	// ���� ���� �Ѵ�.
	bool ReserveRoom( SI32 fieldindex, SI32 roomindex, SI32 homeguild, SI32 awayguild);
	bool IsReservedRoom( SI32 fieldindex, SI32 roomindex );
	SI32 CanReserveRoom( SI32 siFieldIndex, SI32 siRoomIndex , SI32 siMyGuildUnique , SI32 siEnemyGuildUnique );
};


//---------------------------------------------------------------------
// cltGuildWarManager
//---------------------------------------------------------------------
class cltGuildWarManager
{
public:
	// ������ ���۵ɶ� �ܺο��� ������ �־�� �ϴ� ������
	SI32		m_siHomeGuildUnique;				// ���1 ����ũ
	TCHAR		m_szHomeGuildName[MAX_GUILD_NAME];	// ���1 �̸�

	SI32		m_siAwayGuildUnique;				// ���2 ����ũ
	TCHAR		m_szAwayGuildName[MAX_GUILD_NAME];	// ���2 �̸�

	NSafeTArray<SI32, MAX_GUILD_MEMBER_NUM>		m_siHomePersonID;
	NSafeTArray<SI32, MAX_GUILD_MEMBER_NUM>		m_siAwayPersonID;

	NSafeTArray<SI16, MAX_GUILD_MEMBER_NUM>		m_siHomePersonDrinkPutionCnt;
	NSafeTArray<SI16, MAX_GUILD_MEMBER_NUM>		m_siAwayPersonDrinkPutionCnt;

	NSafeTArray<clock_t, MAX_GUILD_MEMBER_NUM>	m_HomePersonDeadClock;
	NSafeTArray<clock_t, MAX_GUILD_MEMBER_NUM>	m_AwayPersonDeadClock;

	bool		m_bStartedWar;						// ���� ���������� ����
	bool		m_bCheckTenSecond;					// �����ϰ� ���� �� �������� üũ �÷���

	clock_t		m_WarStartClock;

	SI32		m_siHomeGuildKill;					// ���1 ���μ���
	SI32		m_siAwayGuildKill;

	bool		m_bEndWar;
	clock_t		m_WarEndClock;

	cltGuildWarManager();
	~cltGuildWarManager();

	// �����ϰ� �����ִ� �Լ�. ������ ���۵ɶ� ȣ�����ְ� ������ �����ؾ��Ѵ�.
	void Init();

	// ������ ��� ���õ� ���¿��� ȣ���� �ִ� �Լ�. �������� ���������� ���þȵǾ������� �ٷ� ������.
	bool StartGame();

	// �ܺο��� ���� ����� �߰��Ҷ� ȣ�����ش�.
	bool AddMember(SI32 personID, SI32 guildUnique );

	// ���� ����� ������ ȣ���� �ش�.
	bool RemoveMember(SI32 personID);

	// ��� ������ �����Ҽ� �ִ��� ����
	bool CanAttack(SI32 myGuildUnique, SI32 targetGuildUnique);

	// TODO : char-item ������ ������� ������ ������ �� �Լ��� ȣ������
	bool DrinkPotion(SI32 personID);

	// ������ �Դµ� ������ �д�.
	bool CanDrinkPotion(SI32 personID);

	// ��������� �׾��� ��� ���� ó���� ���ش�.
	bool GuildWarDie(SI32 personID);
	
	void Action();	        

	// ��������� ������ ���� ���� ���� ó�����ִ� �Լ�. �������� ���� �ʱ�ȭ���ش�.
	void GuildWarEnd();

	// ���� ���ڸ� �÷��ش�.
	void AddKillPoint( SI32 personId );

	// ���� ������ 10�ʰ� ������ ������ ��ġ�� ������.
	void WarpByEnd();

	// ���� ����� �����Ѵ�.
	void SetEnemy();

	// �������� 
	bool IsGod( SI32 personID );
};

class cltGuildWarClient
{
public:
	bool	m_bGuildWarSwitch;
	TCHAR	m_szHomeGuildName[MAX_GUILD_NAME];
	TCHAR	m_szAwayGuildName[MAX_GUILD_NAME];
	SI32	m_siHomeGuildPoint;
	SI32	m_siAwayGuildPoint;

	SI16	m_siHomeGuildMarkIndex;
	SI16	m_siAwayGuildMarkIndex;

	clock_t	m_noticeClock;
	SI32	m_bDrawFlag;

	clock_t m_endClock;

	cltGuildWarClient();
	void	Init();
	bool	IsStartGuildWar()				{ return m_bGuildWarSwitch; };			// ������� �������ΰ�
	void	StartGuildWar( TCHAR* homename, TCHAR* awayname, SI16 homemark, SI16 awaymark );
	void	EndGuildWar( SI32 recvGP );
	void	SetHomeKillPoint( SI32 point )	{ m_siHomeGuildPoint = point; };
	void	SetAwayKillPoint( SI32 point )	{ m_siAwayGuildPoint = point; };
	SI32	GetHomeKillPoint()				{ return m_siHomeGuildPoint; };
	SI32	GetAwayKillPoint()				{ return m_siAwayGuildPoint; };
	void	DrawStatus(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry);
};


