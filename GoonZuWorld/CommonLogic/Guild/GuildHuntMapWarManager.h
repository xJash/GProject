#ifndef _GUILDHUNTMAPWARMANAGER_H
#define _GUILDHUNTMAPWARMANAGER_H

#include "../../Common/CommonHeader.h"
#include "../Guild//Guild.h"

#define MAX_GUILDHUNTWAR_MAPNUM		5	// ������� �ִ� ����	-�ѹ��� ������ �ִ� �����Ƚ��
#define GUILDHUNTWAR_GUILDLEV			4	// ����� �ּ� ��� ����
#define MAx_WARP_TIMETABLE_MINUTE		3
#define MAx_ROOF_TIMETABLE_SECOND		2
#define MAX_INMAPPERSONNUM				32
#define GUILDWAR_WINPOINT				50
#define GUILDWAR_LOSEPOINT				10
#define GUILDWAR_DRAWPOINT				20
#define GUILDHUNTMAPGODTIME				10000
enum
{
	GUILDWAR_HOME = 0,
	GUILDWAR_AWAY,
};
// ����� ��û ������ �޼���.
enum
{
	SUCCEED_RWQUEST_LIST	=	0,			// ��û�� ���ڸ��� ����.
	SAMEGUILD_REQUEST_LIST	,			// �̹� ��û �ߴ�.
	WRONGGUILDUNIQUE_REQUEST_LIST	,	// �߸��� ��� ����ũ��.
	FULL_REQUEST_LIST,				// ���������� ����� ����Ʈ�� ��ϵǾ���,
};
// Ȩ��� ���� �ƴ���
enum
{
	NOT_FIND_LIST	=	0,	// ����Ʈ�� ����
	GUILDWAR_HOMEGUILD	,		// Ȩ���
	GUILDWAR_AWAYGUILD	,		// ����� ���
};
enum
{
	EMPTY_MATCHING_LIST	=	0,	// ����Ʈ�� ����
	MAKE_MATCHING_LIST	,		// ��Ī����Ʈ �ϼ�
	GUILDWAR_READY	,			// ������ �غ��Ѵ�.
	GUILDWAR_START	,			// ������ ���� �Ѵ�.
	GUILDWAR_END	,			// ������� �����Ѵ�
	GUILDWAR_END_WAIT	,			// ������� �����Ѵ�
	GUILDWAR_CLEANUP,			// ����� ������ ���ϵ��� �Ѵ�.
};
enum
{
	GUILDWAR_END_WIN	=	0,	// �� �� �� 
	GUILDWAR_END_DRAW,
	GUILDWAR_END_LOSE,
	GUILDWAR_END_WIN_NOWARP,	// �� �� �� 
	GUILDWAR_END_DRAW_NOWARP,
	GUILDWAR_END_LOSE_NOWARP,
	GUILDWAR_END_NORESULT,

};
class cltWarSrarus
{
public:
	cltWarSrarus()
	{ 
		Init();
	}
	~cltWarSrarus()
	{
	}
	void Init()
	{
		siGuildUnique	=	0	;	// �Ҽӱ�� ����ũ
		siPersonID		=	0	;	// �ɸ��� personID
		siKillNum		=	0	;	// ������ ���� ����
		siDieNum		=	0	;	// ���� ����.
	}
	void SetDeata( SI32 GuildUnique,SI32 PersonID, SI32 KillNum, SI32 DieNum)
	{
		siGuildUnique	=	GuildUnique	;	// �Ҽӱ�� ����ũ
		siPersonID		=	PersonID	;	// �ɸ��� personID
		siKillNum		=	KillNum	;	// ������ ���� ����
		siDieNum		=	DieNum	;	// ���� ����.
	}
	void SetGuildUnique( SI32 GuildUnique )
	{
		siGuildUnique	=	GuildUnique	;	// �Ҽӱ�� ����ũ
	}
	void SetGuildPersonID( SI32 PersonID )
	{
		siPersonID		=	PersonID	;	// �ɸ��� personID
	}
	SI32 GetGuildUnique()
	{
		return siGuildUnique	;
	}
	SI32 GetPerosonID()
	{
		return siPersonID	;
	}
	SI32 GetKillPoint()
	{
		return siKillNum;
	}
	SI32 GetiDieNum()
	{
		return siDieNum	;
	}
	void AddKillPoint()
	{
		siKillNum = siKillNum	+	1	;
	}
	void AddDiePoint()
	{
		siDieNum = siDieNum		+	1	;
	}
private:
	SI32 siGuildUnique	;	// �Ҽӱ�� ����ũ
	SI32 siPersonID		;	// �ɸ��� personID
	SI32 siKillNum		;	// ������ ���� ����
	SI32 siDieNum		;	// ���� ����.

};
class cltEndWarSrarus
{
private:
	TCHAR szGuildName[MAX_GUILD_NAME]	;	// �Ҽӱ�� ����ũ
	TCHAR szPlayerName[MAX_PLAYER_NAME]		;	// �ɸ��� personID
	SI32 siKillNum		;	// ������ ���� ����
	SI32 siDieNum		;	// ���� ����.

public:
	cltEndWarSrarus()
	{ 
		Init();
	}
	~cltEndWarSrarus()
	{
	}
	void Init()
	{
		siKillNum		=	0	;	// ������ ���� ����
		siDieNum		=	0	;	// ���� ����.
		MStrCpy(szGuildName,		TEXT(""),		MAX_GUILD_NAME);
		MStrCpy(szPlayerName,		TEXT(""),		MAX_PLAYER_NAME );
	}
	void SetDeata( SI32 GuildUnique,SI32 PersonID, SI32 KillNum, SI32 DieNum)
	{
		siKillNum		=	KillNum	;	// ������ ���� ����
		siDieNum		=	DieNum	;	// ���� ����.
	}
	void SetGuildName( TCHAR* Guildname)
	{
		MStrCpy(szGuildName,Guildname,sizeof(szGuildName));
	}
	void SetPersonName( TCHAR* PlayerName)
	{
		MStrCpy(szPlayerName,PlayerName,sizeof(szPlayerName));
	}
	TCHAR* GetGuildName()
	{
		return szGuildName	;
	}
	TCHAR* GetPlayer()
	{
		return szPlayerName	;
	}
	SI32 GetKillPoint()
	{
		return siKillNum;
	}
	SI32 GetiDieNum()
	{
		return siDieNum	;
	}
	void SetKillPoint( SI32 KillPoint )
	{
		siKillNum = KillPoint	;
	}
	void SetDiePoint( SI32 DiePoint )
	{
		siDieNum = DiePoint	;
	}
};
class cltPoint	// ����� ���� ��� ����Ʈ
{
public:
	SI32 siKillPoint;
	cltPoint()
	{
		init();
	}
	void init()
	{		
		siKillPoint = 0	;
	}
	void SetKillPoint(SI32 sipoint)
	{
		siKillPoint = siKillPoint + sipoint;
	}
};
// ��ŷ ������
class cltGuildHuntMapWarListRankData
{
private:	
public:
	SI32 siGuildUnique	;
	TCHAR szGuildName[MAX_GUILD_NAME];
	SI32 siWin	;
	SI32 siDraw	;
	SI32 siLose	;
	SI32 siBGP	;
	cltGuildHuntMapWarListRankData()
	{
		Init();
	}
	~cltGuildHuntMapWarListRankData()
	{

	}
	void Init()
	{
		siGuildUnique	=	0;
		MStrCpy(szGuildName,		TEXT(""),		MAX_GUILD_NAME);
		siWin			=	0;
		siDraw			=	0;
		siLose			=	0;
		siBGP			=	0;
	}
	void SetGuildUnique(SI32 siUnique)	{ siGuildUnique = siUnique; }
	SI32 GetGuildUnique(){return siGuildUnique; }

	void SetWin(SI32 Win)	{ siWin = Win; }
	SI32 GetWin(){return siWin; }
	void SetDraw(SI32 Draw)	{ siDraw = Draw; }
	SI32 GetDraw(){return siDraw; }
	void SetLose(SI32 Lose)	{ siLose = Lose; }
	SI32 GetLose(){return siLose; }
	void SetBGP(SI32 BGP)	{ siBGP = BGP; }
	SI32 GetBGP(){return siBGP; }
	TCHAR* GetGuildName()
	{
		return szGuildName	;
	}
	void SetGuildName( TCHAR* Guildname)
	{
		MStrCpy(szGuildName,Guildname,sizeof(szGuildName));
	}

};
class cltGuildHuntMapWarListData
{
public:
	SI32 siGuildUnique;

	cltGuildHuntMapWarListData()
	{
		Init();
	}
	~cltGuildHuntMapWarListData()
	{

	}
	void Init()
	{	
		siGuildUnique =	0;	
	}
	void SetGuildUnique(SI32 siUnique)	{ siGuildUnique = siUnique; }
	SI32 GetGuildUnique(){return siGuildUnique; }
	bool IsSameGuild( SI32 siUnique )
	{ 
		if ( siUnique != 0 && siUnique == siGuildUnique )
		{
			return true	;
		}

		return false	;
	}
	bool IsEmpty()
	{
		if ( siGuildUnique == 0 )	return	true	;
		return false;
	}
};
class cltGuildHuntMapWarMatchingData
{
private:
	SI32 siGuidlUnique	;
public:
	cltGuildHuntMapWarMatchingData()
	{
		siGuidlUnique	=	0;

	}
	~cltGuildHuntMapWarMatchingData()
	{

	}
	void Init()
	{
		siGuidlUnique	=	0	;
	}
	void SetGuild(SI32 siGuildUnique )
	{
		siGuidlUnique	=	siGuildUnique	;
	}
	SI32 GetGuildUniqeue()
	{
		return siGuidlUnique	;
	}
	bool IsSameGuild(SI32 GuildUnique )
	{
		bool bresult = false ;
		if(GuildUnique == GetGuildUniqeue() )
		{
			bresult = true	;
		}
		return bresult	;
	}

};
class cltGuildHuntMapWarManager
{
private:
#if _SAFE_MEMORY
	//--------------------------------------------------------------------------------------------------------------------------------------
	NSafeTArray<cltGuildHuntMapWarListData, MAX_GUILD_NUM>		pclGuildList				;	//	����� ��û	����Ʈ
	//--------------------------------------------------------------------------------------------------------------------------------------
	NSafeTArray<cltGuildHuntMapWarMatchingData, MAX_GUILDHUNTWAR_MAPNUM>		pclGuildMatchingListHome	;	//	����� ��Ī	����Ʈ
	NSafeTArray<cltGuildHuntMapWarMatchingData, MAX_GUILDHUNTWAR_MAPNUM>		pclGuildMatchingListAway	;	//	����� ��Ī	����Ʈ

	NSafeTArray<cltGuildHuntMapWarMatchingData, MAX_GUILDHUNTWAR_MAPNUM>		pclGuildMatchingListHomeTemp	;	//	����� ��Ī	����Ʈ-������ ����� �д�
	NSafeTArray<cltGuildHuntMapWarMatchingData, MAX_GUILDHUNTWAR_MAPNUM>		pclGuildMatchingListAwayTemp	;	//	����� ��Ī	����Ʈ-������ ����� �д�
	//--------------------------------------------------------------------------------------------------------------------------------------
	NSafeTArray<cltPoint, MAX_GUILDHUNTWAR_MAPNUM>								pclKillPointHome			;	//	����� ų ����Ʈ
	NSafeTArray<cltPoint, MAX_GUILDHUNTWAR_MAPNUM>								pclKillPointAway			;	//	����� ų ����Ʈ
	//--------------------------------------------------------------------------------------------------------------------------------------
#else
	//--------------------------------------------------------------------------------------------------------------------------------------
	cltGuildHuntMapWarListData				pclGuildList[MAX_GUILD_NUM]			;		//	����� ��û	����Ʈ
	//--------------------------------------------------------------------------------------------------------------------------------------
	cltGuildHuntMapWarMatchingData			pclGuildMatchingListHome[MAX_GUILDHUNTWAR_MAPNUM]	;		//	����� ��Ī	����Ʈ Ȩ
	cltGuildHuntMapWarMatchingData			pclGuildMatchingListAway[MAX_GUILDHUNTWAR_MAPNUM]	;		//	����� ��Ī	����Ʈ �����

	cltGuildHuntMapWarMatchingData			pclGuildMatchingListHomeTemp[MAX_GUILDHUNTWAR_MAPNUM]	;		//	����� ��Ī	����Ʈ Ȩ-������ ����� �д�.
	cltGuildHuntMapWarMatchingData			pclGuildMatchingListAwayTemp[MAX_GUILDHUNTWAR_MAPNUM]	;		//	����� ��Ī	����Ʈ �����-������ ����� �д�
	//--------------------------------------------------------------------------------------------------------------------------------------
	cltPoint								pclKillPointHome[MAX_GUILDHUNTWAR_MAPNUM]				;		//	ų ����Ʈ
	cltPoint								pclKillPointAway[MAX_GUILDHUNTWAR_MAPNUM]				;
	//--------------------------------------------------------------------------------------------------------------------------------------
#endif
	cltWarSrarus							pclWarStatus_Home[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]	;
	cltWarSrarus							pclWarStatus_Away[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]	;
	cltEndWarSrarus							pclEndWarStatus_Home[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]	;
	cltEndWarSrarus							pclEndWarStatus_Away[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]	;
	clock_t									m_HomePersonDeadClock[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]				;		//	ų ����Ʈ
	clock_t									m_AwayPersonDeadClock[MAX_GUILDHUNTWAR_MAPNUM][MAX_GUILD_MEMBER_NUM]				;

	SI32	siListCount	;					// ����Ʈ�� �ִ� ����� ��
	SI32	siStatus	;					// ���� ���� ����
public:
	cltGuildHuntMapWarManager();
	~cltGuildHuntMapWarManager();
	void init()	;								// ����� ����Ʈ�� �ʱ�ȭ �Ѵ�.

	void SetStatus(SI32 siStatus);				// ���º��� ����
	SI32 GetStatus()	;						// ���� ����Ȯ��

	// ����� ��û ����Ʈ
	SI32 add( SI32 siGuildQunique )	;			// �������û ����Ʈ�� ��带 �߰� �Ѵ�.
	bool Delete( SI32 siGuildQunique )	;		// �������û ����Ʈ�� �ִ� ��带 ���� �Ѵ�.
	bool IsRequest( SI32 siGuildQunique )	;	// �ش� ��� ����ũ�� ��尡 ��û �Ǿ����� Ȯ�� �Ѵ�.
	SI32 GetRequestCount()	;					// ���� ���� ��û�� ����� ������ ������ �´�
	bool IsSameGuild(SI32 siUnique)	;			// �������û ����Ʈ�� ���� ��尡 �ִ��� �˻�.
	void MixList()	;							// ����� ��û ����Ʈ�� ���´�.
	//void ArrangeTempList();						// temp����Ʈ�� �����Ѵ�.
	//void ArrangeGuildList();					// ����� ��û ����Ʈ�� ���� �Ѵ�.
	void MakeMatchingList();					// ��Ī ����Ʈ�� �����.

	//����� ��Ī ����Ʈ
	bool CanMakeMathingList();					// ����� ��Ī����Ʈ�� ����� �ִ��� Ȯ�� �ѵ�.
	void ListClear();							// ����Ʈ�� ��� �����.
	SI32 FindSameGuildUnique(SI32 siGuildUnique );					// ������ ��Ī ����Ʈ���� ���� ��尡 �ִ��� Ȯ�� �Ѵ�.
	bool CopyTempMatchinfList();				// temp����Ʈ�� �ִ°� ������ �ű��.
	void MatchingListClear();					// ��Ī����Ʈ�� ��� �����.
	void TempMatchingListClear();				// ������Ī����Ʈ�� ��� �����.

	// ����� ����
	void Action()	;									// �ð��� ���� ������� ���� �Ѵ�.
	void RequestWarpGuildWarMap()	;					// ����� �������� �̵��� �����Ѵ�. ok �Ѵٸ� �̵� ��Ų��	
	void Start();										// ������� ���� ��Ų��.
	void EndGuildWar() ;								// ������� ����
	void EndGuildWarWarp();								// ����� ������ ����
	void EndGuildWar_New() ;							// ������� ���� �ϰ� ������ ������� ���� ��Ų��.
	void SetEnemy_New();								// ������� ������ ���� ���� �Ѵ�.
	void WarpGuildWar_New(SI32 personID );				// ������� �����ϴ� ����� �������� ���� ��Ų��.
	SI32 IsHomeGuildorAwayGuild( SI32 siGuildunique) ;	// �ش� ��尡 Ȩ������� ����� ������� Ȯ�� �Ѵ�.
	SI32 FindWarpMapIndex(SI32 siMyGuildunique)	;		// �����ذ� ����� ����ũ�� ã�´�.
	void CanStartGuildWar()	;							// ���� �ʿ� ������� �����Ҽ� �ִ��� Ȯ��
	void addKillPoint(SI32 siKillerPersonId,SI32 DeathPersonID);	// ������ �׿�����.
	void MapUserList();									// �� �ʺ� ���� ����Ʈ�� �����.
	void SendKill( SI32 siSlot,SI32 KillerID,SI32 DeathID,SI32 HomeAway ); // ���� ��� �˸� ������ ���ڴ� ���� ���� Ȩ���� ���������
	SI32 GetInHuntMapWarPersonNumHome(SI32 slot);					// ��Ī�� �ش� ����� ������� �󸶳� �ʿ� �ִ��� Ȯ�� �Ѵ�
	SI32 GetInHuntMapWarPersonNumAway(SI32 slot);
	void SendResultWarHome(SI32 slot,SI32 siWarResult);				// �ϳ��� ��忡  ���� �޼����� ������.
	void SendResultWarAway(SI32 slot,SI32 siWarResult);
	bool GuildWarRevive( SI32 siPersonID )	;
	void ArrangeList();


	//���� ��������� �Լ���
	void SaveKillinfo( SI32 siMapSlot,SI32 Hone_Away,SI32 siKillerPersonID,SI32 siDiePersonID)	;
	void MakeEndData();													// �������� Ŭ���̾�Ʈ�� ������ �����͸� �����
	bool FindMeInWarStatus(SI32 siMapSlot,SI32 Hone_Away,SI32 siPersonID, SI32* siFindSlot )	; // ���� ���� �� �������ͽ��� �ִ��� ���� �� Ȯ�� �Ѵ�.
	bool FindMatchingList( SI32 GuildUnique );		// ��Ī����Ʈ�� ��� ����ũ�� �ִ��� Ȯ��.

	void DelEnemy(SI32 siHomeGuildUnique , SI32 siAwayGuildUnique )	;// ���� ��带 ���� �Ѵ�.
	void GuildWarptoSafeZone(	SI32 siGuildUnique )	;				// �ش� ��带 ���縮���� �̵� ��Ų��.
	void SendResultToDB(SI32 siGuildUnique, SI32 siResultFlag );		// ���и� ���� ������.
	void ClearStatus()	;												// ���� ������ �ʱ�ȭ �Ѵ�.
	void ClearWarStatus();
	void ClearKillPoint();
	void ClearTargetStatus(SI32 siGuildUnique)	;					// �ش� ����� ������ �ʱ�ȭ �Ѵ�.
	bool IsGod( SI32 personID )	;									// �����ð� üũ
};
#endif