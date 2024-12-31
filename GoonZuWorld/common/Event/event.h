//---------------------------------
// 2004/8/13 ���°�
//---------------------------------
#ifndef _EVENT_H
#define _EVENT_H

#include <Directives.h>

#include "../../NLib/NArray.h"
#include "../../NLib/NUpdateTimer.h"
#include "CommonHeader.h"


template< class DataType >
class NHashTableString;

class cltCharServer;




class cltEvent{
public:
	SI16	siVillageUnique;
	DWORD	dwLeftClock;			// �̺�Ʈ �ܿ��ð�. 
	DWORD	dwStartClock;			// �̺�Ʈ ���� �ð�. 
	DWORD	dwLastInfoClock;		// ���������� �̺�Ʈ ������ �뺸�� �ð�. 
	SI16	siHuntmapIndex;			// �̺�Ʈ npc�� ��Ÿ�� ���� �ε��� 
	
	bool bEventSwitch;			// �̺�Ʈ�� ���������� ����. 

	cltEvent();
	~cltEvent();

	void Init();
};

#define MAX_EVENTTIME_COUNT		1000
#define MAX_HUNTMAP_INDEX		50

enum EVENTTYPE
{
	EVENTTYPE_NONE,
	EVENTTYPE_PERIOD,
	EVENTTYPE_SHOT,	
};

enum
{
	EXEC_NONE,

	EXEC_PERIOD_COLLECTIONITEM,
	EXEC_PERIOD_HUNTITEM,
	EXEC_PERIOD_MAKEEXPBONUS,
	EXEC_PERIOD_HUNTEXPBONUS,

	EXEC_SHOT_GIVEITEM,
	EXEC_SHOT_MASTERNOTICE,
	EXEC_SHOT_MONSTER_APPEAR_IN_VILLAGE,	//[����] ���� ���� �̺�Ʈ - ���� �� ����.			=> 2008-8-7 
	EXEC_SHOT_MONSTER_APPEAR_OUT_VILLAGE,	//[����] ���� ���� �̺�Ʈ - ���� �� ����.			=> 2008-8-7
	EXEC_SHOT_MONSTER_APPEAR_RANDOM_VILLAGE,//[����] ���� ���� �̺�Ʈ - ������ ������ ����.	=> 2008-8-7

	EXEC_SHOT_MONSTER_APPEAR_RANDOM_HUNTMAP,//[����] ���� ���� �̺�Ʈ - ������ ������ ����.	=> 2008-9-17
	EXEC_SHOT_GUILDWAR,						//[����] ��� ����� ���� ����� �Ŵ���. - ����� 20�и��� ����	=>	2009-03-27
	EXEC_SHOT_GIVEMISSION,					//[����] ���ֵ��� �̼��� �ο��Ѵ�.
};


class cltEventTime
{
public:
	TCHAR			m_szEventName[48];
	SI08			m_siEventType;

	TCHAR			m_szParentEventName[48];

	SYSTEMTIME		m_StartTime;
	SYSTEMTIME		m_EndTime;

	bool			m_bEventShoted;
	bool			m_bEventActivated;

	NUpdateTimer	m_kUpdateTimer_Event;

	SI16			m_siEventExecuteType;

	SI16			m_siBonusAmount;
	SI16			m_siItemUnique;
	SI16			m_siItemNum;

	SI16			m_siCharKind;				//[����] �����Ǵ� ĳ���� ����.			=> 2008-8-7
	SI16			m_siCharNum;				//[����] �����Ǵ� ĳ���� ��.			=> 2008-8-7
	SI16			m_siCharLevel;				//[����] �����Ǵ� ĳ���� ����.			=> 2008-8-7
	SI16			m_siCharLife;				//[����] �����Ǵ� ĳ���� �����.		=> 2008-8-7	
	SI16			m_siVillage;				//[����] �����Ǵ� ĳ���� ����.			=> 2008-8-7
	SI16			m_siPosX;					//[����] �����Ǵ� ĳ���� X��ǥ.			=> 2008-8-7
	SI16			m_siPosY;					//[����] �����Ǵ� ĳ���� Y��ǥ.			=> 2008-8-7
	// 0���� �ָ� �������� ������ �ش� ���ε������ָ� �� �ʿ� �����Ű�� ���� �߰�
	SI16			m_siHuntmapIndex;			//[����] �����Ǵ� ��Ʈ���ε���	=> 2008-9-17 

	SI16			m_siTextMgr;

public:
	cltEventTime()
	{
		ZeroMemory(this, sizeof(cltEventTime));
	}

	~cltEventTime()
	{
	}

	bool SetActivated(bool bActivated, bool bSendAllChar = false);
};

class cltEventTimeManager
{
protected:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltEventTime*, MAX_EVENTTIME_COUNT>		m_pEventTimes;
#else
	cltEventTime*				m_pEventTimes[MAX_EVENTTIME_COUNT];
#endif
	SI32						m_siCount;

	NUpdateTimer				m_kUpdateTimer_Action;

	NHashTableString< int >*	pclHashTableString;	

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_NPC_NUMBER>		siMonsterID;
#else
	SI16						siMonsterID[MAX_NPC_NUMBER];		// [����] ���� ������ ���̵�. 2008-8-27
#endif

	// ����������� ��� ���� ���ؼ� ��Ʈ���������Ͽ��� ���ε����� ������ͼ� �־�Ѱ�
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_HUNTMAP_INDEX>		m_HuntmapIndexByResource;
#else
	SI16			m_HuntmapIndexByResource[ MAX_HUNTMAP_INDEX ];	//[����] HuntMapInfo.txt���� �о��  ��Ʈ���ε���	=> 2008-9-17 
#endif
	SI16						eventmapindex	;					// �̺�Ʈ ���� �о� ������ ���ε��� 

public:
	enum KITERACCOON_EVENT
	{
		KITERACCOON_EVENT_NONE = 0 
		,KITERACCOON_EVENT_START	// ī��Ʈ���� �̺�Ʈ ����
		,KITERACCOON_EVENT_KILL		// ī��Ʈ������ �������� ����
		,KITERACCOON_EVENT_END		// ī��Ʈ���� �̺�Ʈ ����
	};

	cltEventTimeManager();
	~cltEventTimeManager();

	void Init();

	SI32 ConvertEventExecuteTypeStringToEnum(TCHAR* pszEventExecuteType);

	void LoadEventTimePeriod();
	void LoadEventTimeWeek();
	void LoadEventTimeShot();
	void LoadHuntmapInfo();

	bool AddEventByTime( TCHAR* pszEventName, SI16 siSYear, SI16 siSMonth, SI16 siSDay, SI16 siSHour, SI16 siSMinute,
		SI16 siEYear, SI16 siEMonth, SI16 siEDay, SI16 siEHour, SI16 siEMinute, bool Activated);

	bool AddEventByWeek( TCHAR* pszEventName, SI16 siSWeek, SI16 siSHour, SI16 siSMinute, SI16 siEWeek, SI16 siEHour, SI16 siEMinute, bool Activated );

	bool AddShotEvent( TCHAR* pszEventName, SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI16 siMinute, bool Activated , TCHAR* pszParentName = NULL);

	bool InEventTime( TCHAR* pszEventName, SYSTEMTIME* pCurTime );
	SI08 GetEventType( TCHAR* pszEventName );

	void Action();

	bool EventAction( cltEventTime* pclEventTime );

	void SendEventMsg( SI16 siType, SI32 siCharID=0, SI32 siPara1=0, SI32 siPara2=0 );

	bool EventPeriod_CollectionItem( cltEventTime* pclEventTime );
	bool EventPeriod_HuntItem( cltEventTime* pclEventTime );
	bool EventPeriod_MakeExpBonus( cltEventTime* pclEventTime );
	bool EventPeriod_HuntExpBonus( cltEventTime* pclEventTime );

	bool EventAction_GiveItem( cltEventTime* pclEventTime );
	bool EventAction_MasterNotice( cltEventTime* pclEventTime );
	bool EventAction_MonsterAppear( SI16 siType, cltEventTime* pclEventTime );			// [����] �߼� �̺�Ʈ ���� ����.			 => 2008-8-7
	bool EventAction_MonsterAppearNotice( SI16 siType, cltEventTime* pclEventTime );	// [����] �߼� �̺�Ʈ ���� ���� ��ġ ����. => 2008-8-27
	void EventAction_GoonzuDay_GiveMission( cltEventTime* pEventTime );					// [����] ���ֵ��̹̼Ǻο�

	cltEventTime* GetEvent( TCHAR* pszEventName );
	void SetEventMapIndex( SI16 sieventmapindex );
	SI16 GetEventMapIndex();
	bool IsEventStartTiem( TCHAR* pszEventName, SYSTEMTIME* stTime);
	bool IsEventEndTiem( TCHAR* pszEventName, SYSTEMTIME* stTime );
	bool IsEventStartTiemOverMinute( TCHAR* pszEventName,SYSTEMTIME* pCurTime , SI32 siOvertime ) ;// overtime ��ŭ �������� Ȯ��(��)

	void GiveMission(cltCharServer* pChar);
};


#endif