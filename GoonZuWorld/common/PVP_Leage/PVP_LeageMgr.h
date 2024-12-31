//////////////////////////////////////////////////////////////////////////
//
// PVP_League
//
//	�̰��� PVP_League �� �Ŵ����� ���
//	������ �ð��� �Ǹ� ����� ����Ʈ���� ��Ī�� ������� �̾� �ͼ�
//	��Ī�� ������� ����忡 �ְ�
//	������ ������� �������� ���� ����� ����Ʈ�� �շ� ��Ų��.
//
//////////////////////////////////////////////////////////////////////////
#ifndef _PVP_LEAGUEMGR_H_
#define _PVP_LEAGUEMGR_H_

#include "../common/CommonHeader.h"
#include "PVP_LeageObj.h"

// [����] QA�� ���� DEBUG�� 16������ ������ QA�� �� ������ ���� �� �ֵ��� ��(���ź��� �����ּ���)
#ifdef _DEBUG
#define MAX_RESERVE_PERSON			16	//�ִ� ���� �ο���
#else
#define MAX_RESERVE_PERSON			500	//�ִ� ���� �ο���
#endif

#define MAX_MATCHING_PERSON			5	//��Ī�� �ִ��� �ο�
#define MAX_PVP_LEAGUE_GRADE_GAB	3	// ��Ī�� ��� �ִ� ��� ������
#define MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	5	// ��Ī�� ��� �ִ� ��� ������
#define MAX_GRADECOUNT				20	// �ִ� ��� ����

enum PVP_LEAGUE_RESERVE_STATUS
{
	PVP_LEAGUE_RESERVE_STATUS_NONE		= 0,
	PVP_LEAGUE_RESERVE_STATUS_POSSIBLE,			// ��Ī����Ʈ�� ������ �� ����
	PVP_LEAGUE_RESERVE_STATUS_READYFORRESPON,	// �ٽ� ����Ʈ�� �������� ������ ��ٸ��� ����
};
enum PVP_LEAGUE_END_RESULT	// ���� ����
{
	PVP_LEAGUE_END_RESULT_DIE		= 0,	//	�׾���
	PVP_LEAGUE_END_RESULT_WARP,				//	�����ߴ�
	PVP_LEAGUE_END_RESULT_LOGOUT,			//	�α׾ƿ��ߴ�.
};
enum PVP_LEAGUE_END_GOAL	// ���� ����
{
	PVP_LEAGUE_END_RESULT_100WIN		= 0,	//	100����
	PVP_LEAGUE_END_RESULT_1000WIN,				//	1000����
	PVP_LEAGUE_END_RESULT_100DRAW,			//	100����
	PVP_LEAGUE_END_RESULT_1000DRAW,			//	1000����
};
enum PVP_LEAGUE_END_GRADE_UPDOWN	// ��� �� �ٿ�
{
	PVP_LEAGUE_END_GRADEUP		= 1,	//	��� ��
	PVP_LEAGUE_END_GRADEDOWN			//	��� �ٿ�
};

enum PVP_LEAGUE_PROGRESS_STATUS	//���� PVP���� ���� ����. 
{
	PVP_LEAGUE_PROGRESS_READY		= 0,	
	PVP_LEAGUE_PROGRESS_BEFORE_1_M,			//	���� 1���� 
	PVP_LEAGUE_PROGRESS_BEFORE_10_S,		//	���� 10����
	PVP_LEAGUE_PROGRESS_ONTIME,				//	������ ���� 5�и���	�����̵�
	PVP_LEAGUE_PROGRESS_AFTER_30_S,			//	����忡 ������ 30�� ���� ����
	PVP_LEAGUE_PROGRESS_END_BATTLE,			//	��������� ���� ������ 3���� ��� ���� �ð�.
	PVP_LEAGUE_PROGRESS_END_ESCAPEGROUND	//	��Ⱑ ������ 30�� ���� ������ ���� 
};

class CPVP_Leage_List
{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<CPVP_Leage_ListData, MAX_RESERVE_PERSON>			m_clPVP_LeageReserveList	;	//	PVP_League	����Ʈ
#else
	CPVP_Leage_ListData				m_clPVP_LeageReserveList[MAX_RESERVE_PERSON]	;	//	PVP_League	����Ʈ
#endif

public:
	CPVP_Leage_List();
	~CPVP_Leage_List();

	void Init();

	SI32 Add( SI32 siPersonID, SI16 siGrade );	// ���ฮ��Ʈ�� �ѻ���� �߰��Ѵ�
	void Delete( SI32 siPersonID );				// ���ฮ��Ʈ���� Ư�� ����� ����
	SI32 GetPersonIndex( SI32 siPersonID );		// ��ġ�� ã�´�.

	SI32 GetPersonID(SI32 siIndex);				// �迭�� �ε����� PersonID�� ���´�.

	SI32 GetCount();							// ��ü ��� ������ ���´�.
	void ArrangeList();							// ����Ʈ�� ������� �����Ѵ�.
	void DeleteNoPossiblePerson();				// ��Ī�� ������ �ʴ� ������ �����Ѵ�.
	void SetStatus(SI32 siPersonID, SI32 siSatus);	// ������ ���¸� �����Ѵ�.

	SI32 FindMatchPerson(SI32 siPersonID);		// ���� ������ ��븦 ã�´�.

	void SendToAgainReserveQuestion();			// ����Ʈ���� ��Ī�� ���� ���� �����鿡�� �޽����� �����Ѵ�.
};

class CPVP_Leage_MatchingList
{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<CPVP_Leage_MatchingListData, MAX_MATCHING_PERSON>	m_clPVP_LeageMatchingList	;	//	PVP_League	��Ī�� ����Ʈ
#else
	CPVP_Leage_MatchingListData		m_clPVP_LeageMatchingList[MAX_MATCHING_PERSON]	;	//	PVP_League	��Ī�� ����Ʈ
#endif

public:
	CPVP_Leage_MatchingList();
	~CPVP_Leage_MatchingList();

	void Init();

	bool Add( SI32 siSourcePersonID, SI32 siDestPersonID, SI32 siTotalScore );
	bool Delete( SI32 siSourcePersonID, SI32 siDestPersonID );

	SI32 GetIndex( SI32 siSourcePersonID, SI32 siDestPersonID );

	SI32 GetBattlePersonIDHome( SI32 siIndex );
	SI32 GetBattlePersonIDAway( SI32 siIndex );

	SI32 FindPersonID( SI32 siPersonID );
	SI32 FindEnemyPersonID( SI32 siPersonID );

	SI32 GetCount();
	bool IsFull();

	void SortByTotalScore();

	void NoticeSpecialNews();
	void NoticeStartPVP();

	void PVP_League_MatchingLog( void );
};

class CPVP_Leage_EndGameList
{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<CPVP_Leage_EndGameListData, MAX_MATCHING_PERSON>	m_clPVP_Leage_EndGameList	;	// ������ ���ӵ��� �����Ѵ�.
#else
	CPVP_Leage_EndGameListData		m_clPVP_Leage_EndGameList[MAX_MATCHING_PERSON]	;	// ������ ���ӵ��� �����Ѵ�.
#endif

public:
	CPVP_Leage_EndGameList();
	~CPVP_Leage_EndGameList();

	void Init();

	void Add( SI32 WinnerID, SI32 LoserID );
	SI32 FindPersonID( SI32 siPersonID );
	void PVP_LeagueEndWarp();
};


struct cltMapInfo
{
	SI16			m_slot	;
	SI16			m_index	;
	SI16			m_HomeX	;
	SI16			m_HomeY	;
	SI16			m_AwayX	;
	SI16			m_AwayY	;
};

struct cltGradeInfo
{
	SI16			m_Grade	;
	SI16			m_GradeValue	;
	SI16			m_UpWin	;	// ���� ��޿� �ö󰥼� �ִ� ���� �¼�
	SI16			m_DownLose	;	// ���� ������� �������� �ִ� ���� �м�
};

class CPVP_LeagueMgr
{
private:
	CPVP_Leage_List					m_clPVP_LeageReserveList;		   //	PVP_League	����Ʈ
	CPVP_Leage_MatchingList			m_clPVP_LeageMatchingList;		   //	PVP_League	��Ī�� ����Ʈ
	CPVP_Leage_EndGameList			m_clPVP_Leage_EndGameList;		   // ������ ���ӵ��� �����Ѵ�.

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMapInfo, MAX_MATCHING_PERSON>					pclmapinfo;		;	//	PVP_League �� ���� 
	NSafeTArray<cltGradeInfo, MAX_GRADECOUNT>					pclGradeInfo;				;	//	PVP_League ��� ���� 
#else
	cltMapInfo						pclmapinfo[MAX_MATCHING_PERSON]					;	//	PVP_League �� ���� 
	cltGradeInfo						pclGradeInfo[MAX_GRADECOUNT]					;	//	PVP_League ��� ����
#endif

	SI32							m_siBottomPosition;					// ���� ����Ʈ�� ������ ����Ǿ� �ִ°�?

	SYSTEMTIME						stEndTime						;	//���� �ð�
	SI32							m_Battle_Status					;	// ���� PVP���� ���º���.
	SI32							m_siLastGradeIndex				;
	bool							bEndNotice						;
public:
	CPVP_LeagueMgr();
	~CPVP_LeagueMgr();

	void	Init( void );										// ��ü �ʱ�ȭ

	SI32 AddReserveList( SI32 siPersonID, SI16 siGrade );	// ���ฮ��Ʈ�� �ѻ���� �߰��Ѵ�
	void SubReserveList( SI32 siPersonID );					// ���ฮ��Ʈ���� Ư�� ����� ����
	void AgainReserveList( SI32 siPersonID, bool bAnswer );	// �ٽ� ���ฮ��Ʈ�� �������� �����Ѵ�
	void AddEndGameList( SI32 WinnerID, SI32 LoserID );		// ������� ����Ʈ�� �߰� �Ѵ�.

	void MakeMatchingList( void );							// ��Ī ����Ʈ�� �����

	SI32 GetRerserveListCount();

	void Action()	;

	void sendResultDB( SI32 WinnerID, SI32 LoserID )	;
	void sendResultDrawDB( SI32 siFirstPersonID, SI32 siSecondPersonID )	;		
	void End_PVP_Battle_End( SI32 siWinnerPersonID, SI32 siLoserPersonID )	;
	void End_PVP_Battle_Draw( SI32 siFirstPerson, SI32 siSecondPerson )	;
	void Send_PVP_Battle_Result( SI32 siFirstPerson, SI32 siSecondPerson, SI32 siFlag )	;
	//-- ���
	void PVP_LeagueReady();
	void PVP_LeagueStart();
	void PVP_League_Warp_Stage( SI32 siHomePersonID, SI32 siAwayPersonID , SI32 siMapIndex, SI32 siSlot );
	//---��Ͽ� ���� ó��
	void SetAfterPVP_League_Record_Win( SI32 siID )	;	//charID
	void SetAfterPVP_League_Record_Lose( SI32 siID )	;	//charID
	void SetAfterPVP_League_Record_Draw( SI32 siID )	;// charID
	//---���� 
	void AfterPVP_League_Record_Win_Prize( SI32 siID , SI32 siStrightWinCount	)	;
	void AfterPVP_League_Record_Lose_Prize( SI32 siID , SI32 siStrightWinCount	)	;
	void AfterPVP_League_Record_Draw_Prize( SI32 siID , SI32 siStrightWinCount	)	;
	// ��� ��� �ϰ�
	void PVP_League_LevelUp( SI32 siID ,SI32 siStrightWinCountGrade )	;
	void PVP_League_LevelDown( SI32 siID , SI32 siStrightLoseCountGrade )	;

	void PVP_LeagueMapInfo()	;
	void PVP_LeagueGradeInfo()	;

	void Set_PVP_League_Status(	SI32 siBattle_Status	)	{ m_Battle_Status = siBattle_Status ;};	// PVP ���� ���¸� �����Ѵ�.
	SI32 Get_PVP_League_Status(){	return m_Battle_Status	;	}	;	// PVP ���� ���¸� ������ �´�.
	void Init_PVP_League_Status(){ m_Battle_Status = PVP_LEAGUE_PROGRESS_READY	; }	;	// PVP ���� ���¸� �ʱ�ȭ �Ѵ�

	SYSTEMTIME GetEndTiem(){	return stEndTime	;	}	;
	////==����
	void PVP_LeagueEndWarp()	;
	void PVP_Battle_HaveItemMessage( SI32 siPersonID, SI32 siItemUnique )	;
	void PVP_Battle_Step_Draw( void )		;
	void PVP_Battle_Step_Game( void );
	void PVP_League_Before1m();
	void PVP_League_GiveItem( SI32 siID, SI32 siItemUnique,bool bSpecial );
	void PVP_League_MatchingLog()	;	// ��Ī����Ʈ�� �α׸� ���´�.
	void LogWinLose( SI32 siWinnerPeronID, SI32 siLoserPersonID )	;		// ���зα׸� ���´�
	void LogDraw( SI32 siDrawPersonId1 , SI32 siDrawPersonId )	;			// ��� �α׸� ���´�.
	void LogGoal( SI32 siPersonID , SI32 siGoalFlag )	;					// ��ǥ�޼� �α׸� ���´�.
	void LogReserve( SI32 siPersonID )					;					// ���ฮ��Ʈ�������� �α� ���´�.
	void LogGradeUpDown( SI32 siPersonID,SI32 siBeforeGrade, SI32 siAfterGrade, SI32 UpDownFlag )	;
	//== ��Ī ����Ʈ�� �ִ��� Ȯ�� �ϰ� 
	bool InMatchingList( SI32 siPersonID)	;			// ��Ī����Ʈ�� �ش� �۽��� �ִ��� Ȯ��
	bool InEndGameList( SI32 siPersonID)	;			// EndgameList�� �ִ��� Ȯ�� �Ѵ�.
	// ������ ã�� ����
	SI32 GetEnemyPersonID( SI32 siPersonID)	;			// ��Ī����Ʈ���� ���� ���� �������� Ȯ��
	// �ش� �ɸ��Ͱ� PVP���� �ʿ� �ִ��� Ȯ��.
	bool Is_MatchingListPeron_TruePosition( SI32 siPersonID )	; // �ش� �ɸ��Ͱ� ��Ī ����Ʈ�� �����Ҷ� ���� �����ǿ� �ִ� ���� Ȯ��.
	SI32 GetMyGradeFromGradeValue(SI32 siGradeValue )	;
	SI32 ChangeGrade( SI32 GradeNow, SI32 WinLoseCount, SI32 siUpDown );

private:
	// ���ฮ��Ʈ���� ��Ī���� �ʴ� ����鿡�� �ٽ� ������ �Ұ����� ����� ��Ŷ�� �����ִ� �Լ�
	void	SendToAgainReserveQuestion( void );

	// Ư������忡 ����ϴ� ����� �ڸ������ �˷��ش�
	void	NoticeSpecialNews( void );	

	// ��� �ڿ� ��Ⱑ ���۵ȴٰ� �˸�.
	void	NoticeStartPVP( void );

	// ��ó�� ���Ѵ��� ��Ⱑ ��ÿ� ���۵ȴٰ� �˸�
	void	NoticeStartTime( void );
	// ��ó�� ���Ѵ��� ��Ⱑ ������ �ð�.
	void	NoticeEndTime( void );

public:
	// ��Ī Ư���� ã��ÿ� ���� ������ ���� �Լ�
	static SI32	GetTotalScore( SI32 siSourcePersonID, SI32 siDestPersonID );
	// ��Ī�� �� ��ް� ��ȿ�� �������� �ִ� ������� �˻��Ѵ�
	static bool	CheckTheGrade( SI16 siSourceGrade, SI16 siDestGrade, SI32* psiGradeGab );
	// ���� ��Ī�� �� �� �ִ� ������� �˻��Ѵ�
	static bool	IsValidPerson( SI32 siSourcePersonID, SI32 siDestPersonID );
};
#endif
