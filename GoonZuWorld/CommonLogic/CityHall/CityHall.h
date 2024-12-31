//---------------------------------
// 2003/6/9 ���°�
//---------------------------------

#ifndef _CITYHALL_H
#define _CITYHALL_H

#include <Stdio.h>
#include "..\StructureClass\StructureClass.h"
#include "..\..\Common\CommonHeader.h"

#include "GeneralMeeting.h"

#define MAX_CITYHALL_TAB_NUMBER			10		// �� ���� 
#define MAX_CITYHALL_CHIEF_TAB_NUMBER	5		// ����� �޴� �� ����
#define MAX_RESIDENT_APPLYER			100		// �� ���� �� �ִ� �ֹε�� ��û�� ����
#define MAX_RESIDENT_NUMBER				100

#define MAX_VILLAGEMARK_NUMBER			107

//#if defined(_CITYHALL_BANKRUPTCY)
#define MAX_BANKRUPT_STOCKHOLDER_NUMBER_TO_BE_NOTIFIED	500		// �Ļ� ������ ���� �ִ� ���ּ�, �������� 1~�ִ�500�����
//#define BANKRUPT_STOCK_PERCENT	3	// �Ļ��� : 3%
//#endif
class cltTime;

class cltCandidate;
class cltCityHallCandidateManager;

class cltTaxPaymentListDlg;
class cltDividendListDlg;

class cltRankCandidate{
public:
	SI32 siRankType;			// �ź��ڵ� 
	TCHAR szStructureName[64];	// �ü� �̸�. 
	TCHAR szRankName[64];		// �ź��̸�  
	SI32 siNeedLevel;			// �Ǳ� ���� �ʿ��� ���� 
	TCHAR szExplain[256];		// ����. 
};

// ���� ���� �� ����
class cltVillageLevelDetailInfo
{
public:
	cltVillageLevelDetailInfo() {
		ZeroMemory( this, sizeof( cltVillageLevelDetailInfo ) );
	}

	~cltVillageLevelDetailInfo() {};

	void		Set( cltVillageLevelDetailInfo *pInfo ) 
	{
		siSlaveVillage = pInfo->siSlaveVillage;
		siResident = pInfo->siResident;
		siVisitorNum = pInfo->siVisitorNum;
		siVillageTotalScore = pInfo->siVillageTotalScore;

	}


	SI32		GetVillageLevel()
	{
		return siSlaveVillage + siResident + siVisitorNum;
	}

	SI16		siSlaveVillage;						// ���� ���� ������ ���� ���� 
	SI16		siResident;							// �ֹ� ���ڿ� ���� ���� 
	SI16		siVisitorNum;						// ���� �湮�� ���ڿ� ���� ����
	SI32		siVillageTotalScore;				// ���� �� ����

};

#define CITYHALL_EVENT_HUNT					1
#define CITYHALL_EVENT_MOFUMOFU				2
#define CITYHALL_EVENT_MONSTER_ATTACK		3	// [����] ���� �̺�Ʈ - ���� ����. 2008-3-26

// ���� �̺�Ʈ 
class cltCityhallEventInfo
{
public:
	cltCityhallEventInfo() { ZeroMemory( this, sizeof( cltCityhallEventInfo ) ); };
	~cltCityhallEventInfo() {};


	int			eventid;
	GMONEY		siEventMoney;
	TCHAR		szEventName[ 32 ];
	TCHAR		szEventExplain[ 512 ];
};


class cltCityhallEventManager
{
public:
	cltCityhallEventManager() { ZeroMemory( this, sizeof( cltCityhallEventManager ) ); };
	~cltCityhallEventManager() {};


#ifdef _SAFE_MEMORY
	NSafeTArray<cltCityhallEventInfo, 20>		clEventInfo;
#else
	cltCityhallEventInfo	clEventInfo[ 20 ];
#endif
	SI32					siEventNum;


	void AddEvent( SI32 eventid, GMONEY money, TCHAR *szEventName, TCHAR *szEventExplain ) {
		clEventInfo[ siEventNum ].eventid = eventid;
		clEventInfo[ siEventNum ].siEventMoney = money;
		
		memcpy( clEventInfo[ siEventNum ].szEventName, szEventName, 32 );
		clEventInfo[ siEventNum ].szEventName[ 31 ] = NULL;

		memcpy( clEventInfo[ siEventNum ].szEventExplain, szEventExplain, 512 );
		clEventInfo[ siEventNum ].szEventExplain[ 511 ] = NULL;

		siEventNum++;
	}

	cltCityhallEventInfo *GetEventInfoFromEventID( SI32 id )
	{
		for( int i = 0; i < siEventNum; ++i ) {
			if( clEventInfo[ i ].eventid == id ) {
				return &clEventInfo[ i ];
			}
		}

		return NULL;
	}


};


// ����
/*
class cltCityHallMoneyExplain
{
public:
	HWND m_hDlg;	
	BOOL m_DlgRectInitSwitch;
	RECT m_DlgRect;
	HBITMAP m_hHitBitmap;

	SI32 m_siExplainType;

	cltCityHallMoneyExplain();
	~cltCityHallMoneyExplain();

	bool CreateDlg(HINSTANCE hinst, HWND hwnd);
	static BOOL CALLBACK CityHallMoneyExplainStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK CityHallMoneyExplainProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	SI32 GetCityHallMoneyExplainType(TCHAR* pExplainType);
	void ShowCityHallMoneyExplainHit(HWND hDlg, SI32 siExplainType);

};
*/

// �ֹ� Ŭ���� 
class cltResident
{
public:
	cltSimplePerson		clPerson;			// ��û��
	SI32				siLevel;			// ���� 
	SI32				siGrade;			// �ֹ�����
	cltDate				clDate;				// �ֹε����(���ӽð�)
	cltDate				clLastLoginDate;	// ������ ������(���ӽð�)

	cltResident()
	{
		Init();
	}

	void Init()
	{
		clPerson.Init();
		siGrade = 0;
	}

	void Set( cltSimplePerson *pclPerson, SI32 grade, cltDate *pclDate, cltDate *pclLastLoginDate )
	{
		clPerson.Set( pclPerson );
		siGrade = grade;
		clDate.Set( pclDate );
		clLastLoginDate.Set( pclLastLoginDate );
	}

	void Set( cltResident *pclResident )
	{
		memcpy( this, pclResident, sizeof( cltResident ) );
	}
};


// �ֹ� ��� ��û�� Ŭ���� 
class cltResidentApplyer
{
public:
	cltSimplePerson		clApplyer;			// ��û��
	SI32				siLevel;			// ����
	cltDate				clDate;				// ��û�� 

	cltResidentApplyer()
	{
		Init();
	};

	void Init()
	{
		clApplyer.Init();
		siLevel = 0;
	}

	void Set( cltSimplePerson *pclPerson, SI32 level, cltDate *pclDate ) {
		clApplyer.Set( pclPerson );
		siLevel = level;
		clDate.Set( pclDate );
	}

	void Set( cltResidentApplyer *pclResidentApplyer )
	{
		memcpy( this, pclResidentApplyer, sizeof( cltResidentApplyer ) );
	}

};


//-------------------------------------
// ��� ���� 
//-------------------------------------
class cltCheifInfo
{
public:
	cltCheifInfo() {
		ranktype = 0;
		szID[ 0 ] = NULL;
	}

	int			ranktype;
	TCHAR		szID[ MAX_PLAYER_NAME ];
};

class cltChatMember
{
public:
	int		charid;
	int		personid;

	cltChatMember()
	{
		charid = 0;
		personid = 0;
	}
};

class cltChatMemberManager
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltChatMember, 200>		clChatMember;
#else
	cltChatMember	clChatMember[ 200 ];
#endif

	void AddChatMember( int charid, int personid );
	void DelChatMember( int personid );
	void SendMsg( BYTE* msg );
};


//-------------------------------------------------
// �������� ���.  
//-------------------------------------------------
class cltCityHall: public cltStructureBasic{
private:
	cltCityHallCandidateManager* pclCandidateManager;

public:
	cltCityHall(SI32 sivillageunique);
	~cltCityHall();

#ifdef _SAFE_MEMORY
	NSafeTArray<cltResidentApplyer, MAX_RESIDENT_APPLYER>	clResidentApplyer;
	NSafeTArray<cltResident, MAX_RESIDENT_NUMBER>			clResident;
#else
	cltResidentApplyer	clResidentApplyer[ MAX_RESIDENT_APPLYER ];			// �ֹ� ��� ��û�� 
	cltResident			clResident[ MAX_RESIDENT_NUMBER ];
#endif

	cltVillageLevelDetailInfo	clLevelInfo;
	cltGeneralMeetingInfo		clGeneralMeetingInfo;

	cltChatMemberManager		clChatMemberManager;

	BOOL	bPrepareBankruptcy;

	void SetResidentApplyer( SI32 index, cltResidentApplyer *pclResidentApplyer )
	{
		clResidentApplyer[ index ].Set( pclResidentApplyer );
	}

	cltResidentApplyer* GetResidentApplyer( SI32 index )
	{
		return &clResidentApplyer[ index ];
	}


	void SetResident( SI32 index, cltResident *pclResident )
	{
		clResident[ index ].Set( pclResident );
	}


	// ��� �ֹε�Ͻ�û�ڸ� �����Ѵ�.
	void InitResidentApplyer()
	{
		for( SI32 i = 0; i < MAX_RESIDENT_APPLYER; i++ )
		{
			clResidentApplyer[ i ].Init();
		}

	}

	// ��� �ֹ��� �����Ѵ� 
	void InitResident()
	{
		for( SI32 i = 0; i < MAX_RESIDENT_NUMBER; i++ )
		{
			clResident[ i ].Init();
		}
	}

	void SetSymbol( SI16 symbolKind, SI32 symbolLife, SI32 symbolMana, SI16 symbolCapa );	// �ɺ�(��ȣ��) ���� ���� 
	void SetSymbolLife( SI32 symbolLife );													// �ɺ�(��ȣ��) ü�� ����
	void SetSymbolMana( SI32 symbolMana );													// �ɺ�(��ȣ��) Mana ���� 
	void SetSymbolCapa( SI16 symbolCapa );													// �ɺ�(��ȣ��) ���� ����

	void SetCastle( SI16 castleKind, SI32 castleLife, SI32 castleMana, SI16 castleCapa );	// ĳ�� ���� ���� 
	void SetCastleLife( SI32 castleLife );													// ĳ�� ü�� ����
	void SetCastleMana( SI32 castleMana );													// ĳ�� Mana ���� 
	void SetCastleCapa( SI16 castleCapa );													// ĳ�� ���� ����	

	BOOL AddApplyer( cltResidentApplyer *pclApplyer );
	BOOL DeleteApplyer( SI32 personid );

	// Chief �ĺ��� ����Ѵ�. 
	BOOL SetCandidate(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclcandidate);
	// �ĺ� ����� ����Ѵ�. 
	BOOL DeleteCandidate(SI32 personid);
	// Ư�� �ź��� �ĺ� ����� ��� ����Ѵ�. 
	BOOL DeleteCandidate(cltSimpleRank* pclrank);

	cltSimplePerson* GetCandidateInfoFromPersonID(SI32 ranktype, SI32 personid, SI32* pindex);
	// ���ĺ����� ���ڸ� ���Ѵ�. 
	SI32 GetCandidateNum(SI32 ranktype);

	cltSimplePerson* GetCandidateInfoFromRef(SI32 ranktype, SI32 ref);

};

//--------------------------------------------------
// ��ܰ�����. 
//--------------------------------------------------
class cltCityHallManager : public cltStructureMngBasic{
public:
	cltCityHallCandidateManager* pclClientCandidateManager;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltResidentApplyer, MAX_RESIDENT_APPLYER>		clResidentApplyer;
	NSafeTArray<cltResident, MAX_RESIDENT_NUMBER>				clResident;
#else
	cltResidentApplyer	clResidentApplyer[ MAX_RESIDENT_APPLYER ];			// �ֹ� ��� ��û�� 
	cltResident			clResident[ MAX_RESIDENT_NUMBER ];
#endif
	
	cltResident			clClientResidentInfo;

	cltVillageLevelDetailInfo	clClientLevelInfo;
	cltGeneralMeetingInfo		clGeneralMeetingInfo;

	cltCityhallEventManager		clEventManager;
	SI32						siSelectedIndex;

	BOOL UpdateInOutMoneySwitch;

	BOOL UpdateWarTreeSwitch;

	BOOL UpdateResidentApplyerSwitch;
	BOOL UpdateResidentListSwitch;
	
	BOOL UpdateResidentInfoSwitch;
	BOOL bResidentInfoValid;

	BOOL UpdateInvestSwitch;
	BOOL UpdateMayorCandidateSwitch;
	BOOL UpdateChiefCandidateSwitch;

	BOOL UpdateLevelInfoSwitch;

	cltCityHallManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltCityHallManager();

	BOOL bChiefInfo;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltCheifInfo, MAX_RANKTYPE_NUMBER>	clChiefInfo;
#else
	cltCheifInfo clChiefInfo[ MAX_RANKTYPE_NUMBER ];
#endif

	virtual void OnTimer();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	// �����  �ż��Ѵ�.
	BOOL CreateCityHall(SI32 siunique);

	// 
	void Update();

	void UpdateResidentApplyerList( SI32 personid );

	// �ü� ���� ����Ʈ�� �ʱ�ȭ�Ѵ�
	void InitStructList( HWND hDlg );

	// �ź� ���� ����Ʈ�� �ʱ�ȭ�Ѵ� 
	void InitRankList( HWND hDlg );

	// ������ ����Ʈ�� �ʱ�ȭ�Ѵ� 
	void InitInvestList( HWND hDlg );

	// ������ ����Ʈ�� �����ش�. 
	BOOL ShowInvestList(HWND hDlg);
	
	// ������� �����ش�. 
	BOOL ShowMayor(HWND hDlg);

	// Chief	�ĺ��� ����Ѵ�. 
	BOOL SetCandidate(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclcandidate);

	// �ĺ� ����� ����Ѵ�. (��� ��å����..) 
	BOOL DeleteCandidate(SI32 villageunique, SI32 personid);

	// Ư�� �ź��� ��� �ĺ� ����� ����Ѵ�.
	BOOL DeleteCandidate(cltSimpleRank* pclrank);

	void Action(cltTime* pcltime);

	// '��'�� Ÿ���� �����Ѵ�. 
	void SetCandidateCombo(HWND hDlg);

	// ���õ� ���ڿ��� �ٰŷ� ������ ������ �����ش�. 
	void SetRankCandidateHelp(const TCHAR* szSelText);

	// ���õ� RankType�� �Ǳ� ���� �ʿ��� ������ ���Ѵ�.
	SI32 GetNeedLevelFromRankType(SI32 ranktype);

	// ���õ� ���ڿ�(�ü���)�� �ٰŷ� ������ �ź��ڵ带 ���´�.
	SI32 GetRankTypeFromStructureName(const TCHAR* szSelText);

	// ���õ� ���ڿ�(�źи�)�� �ٰŷ� ������ �ź��ڵ带 ���´�.
	SI32 GetRankTypeFromRankName( const TCHAR* szSelText );

	BOOL IsGeneralMeeting( SI32 villageunique );

	BOOL IsPrepareBankruptcy( SI32 villageunique );

//#if defined(_CITYHALL_BANKRUPTCY)
	// ����� �Ļ� ���¸� ����
	UI08 GetCityHallState( SI32 villageunique );
	// �Ļ��� �� ������ ��� ��Ұ� �ʱ�ȭ �Ǿ��°�
    BOOL IsInitialized( SI32 villageunique );

	// ��� ���� ������ ����Ѵ�. 
	void WriteAllCityHallState();

	// ��û �Ļ���� Ȥ�� �����Ⱑ ������ DeadLine ������ ��´�.
	cltDate GetCityHallBankruptcyDetailInfo( cltCityhallStrInfo* pstrinfo );
//#endif


	//----------------------------------------
	// CityHall-ChiefDlgProc.cpp
	//----------------------------------------
	
	// �ü����� �޺��� �߰��Ѵ�.
	BOOL ShowStructure(HWND hDlg);

	void ShowVillageMark( HWND hDlg );
	void ShowMyVillMark( HWND hDlg );

	void ShowChiefDate( HWND hDlg );
	BOOL bRecvChiefInfo;

	SI32	m_siVillageMarkIndex;
	SI32	m_siMyVillMarkIndex;
	// ���� ���� ���� ����
	SI32	m_siVillageMapIndex;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, 100>		m_siVillageMapUnique;
#else
	SI32	m_siVillageMapUnique[ 100 ];
#endif
	SI32	m_siVillageMapNumber;

	void	ShowVillageMap( HWND hDlg );


	void	InitVoteList( HWND hDlg );
	
	void	ShowMeetingInfo( HWND hDlg );
	void	ShowVoterList( HWND hDlg );

	void	ShowLeftTime( HWND hDlg );
	
	BOOL	bUpdateGeneralMeetingInfo;
	BOOL	bRequestGeneralMeetingInfo;
};

#endif
