//---------------------------------
// 2007/4/16 �̰���
//---------------------------------
#ifndef _MOFUMOFU_H
#define _MOFUMOFU_H

#include "..\Event.h"
#include "../NLib/NUpdateTimer.h"

#define MOFUMOFUEVENT_MAPINDEX	0

#define MOFUMOFUEVENT_SENDMSG_MIN			5				// 5�� ������ �޽����� �����Ѵ�.
#define MOFUMOFUEVENT_ENABLE_ENTER_TIME_MS	5 * 60 * 1000	// 5�� �ں��� ���� ����
#define MOFUMOFUEVENT_MAKE_ENEMY_TIME_MS	4 * 60 * 1000	// 4�� �ڿ� ���� ��ȯ
#define MOFUMOFUEVENT_DEFAULT_TIME_MS		50 * 60 * 1000	// 50�� ���� �̺�Ʈ�� �����Ѵ�.

#define MOFUMOFUEVENT_MAXKINGENEMY_COUNT	1				// ��ü ��ƾ� �� ŷ(����) ���� ��
#ifdef _DEBUG
	#define MOFUMOFUEVENT_MAXENEMY_COUNT	90
#else
	#define MOFUMOFUEVENT_MAXENEMY_COUNT	1800			// ��ü ��ƾ� �� ���� ��
#endif


#define MOFUMOFUEVENT_FIELD_MAXENEMY_COUNT		50			// �� ������ �ִ�� ��ȯ�Ǵ� ���ĸ��� ��
#define MOFUMOFUEVENT_FIELD_MAMAMOFUMOFU_INDEX	50 + 10		// �� ������ �������� �ε���
#define MOFUMOFUEVENT_FIELD_MAXSPWAN_COUNT		5			// �� ������ ��ȯ�Ǵ� ���� ��
#define MOFUMOFUEVENT_FIELD_SPWAN_ENEMY_COUNT	10			// �� ������ ���Ͱ� ��ȯ�Ǵ� ��
#define MOFUMOFUEVENT_FIELD_MIN_ENEMY_COUNT		4			// ���� ���Ͱ� ��ȯ�� ����

#define MOFUMOFUEVENT_MAXFIELD_COUNT		3				// ���ĸ����̺�Ʈ ������ �����ʵ� ��

#define	MOFUMOFUEVENT_ROOMNUM				24				// 1�ð� �������� ����

#define KIND_MAMARACCOON					170				// ����������
#define KIND_MAGICALRACCOON					171				// �����ñ�����
#define KIND_RACCOONLORD					172				// ������ε�
#define KIND_RACCOONTOWER					173				// ������Ÿ��
#define KIND_ZORRORACCOON					174				// ���α�����

//---------------------------------
// ���ĸ��Ĵ��� �̺�Ʈ ����
//---------------------------------
class cltMofuMofuEventReserveUnit
{
public:
	SYSTEMTIME	m_ReserveHour;
	SI32		m_siVillageUnique;

public:
	cltMofuMofuEventReserveUnit()
	{
		Init();
	}
	~cltMofuMofuEventReserveUnit()
	{
	}

	void Init()
	{
		ZeroMemory(&m_ReserveHour, sizeof(m_ReserveHour));
		m_siVillageUnique	= 0;
	}

	void Set(SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siVillageUnique)
	{
		m_ReserveHour.wYear		= siYear;
		m_ReserveHour.wMonth	= siMonth;
		m_ReserveHour.wDay		= siDay;
		m_ReserveHour.wHour		= siHour;

		m_siVillageUnique	= siVillageUnique;
	}

	void Set(cltMofuMofuEventReserveUnit* pUnit)
	{
		if(pUnit == NULL)				return;

		memcpy(&m_ReserveHour, &(pUnit->m_ReserveHour), sizeof(m_ReserveHour));
		m_siVillageUnique	= pUnit->m_siVillageUnique;
	}
};

//---------------------------------
// ���ĸ��Ĵ��� �̺�Ʈ Ŭ����
//---------------------------------
class cltMofuMofuField
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MOFUMOFUEVENT_FIELD_MAXENEMY_COUNT>		m_siEnemyID;
#else
	SI32	m_siEnemyID[MOFUMOFUEVENT_FIELD_MAXENEMY_COUNT];
#endif
	SI32	m_siCount;
	SI32	m_siCreateCount;
	SI32	m_siKilledCount;
	SI32	m_siMamaMofuMofuID;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MOFUMOFUEVENT_FIELD_MAXSPWAN_COUNT>		m_siSpwanX;
	NSafeTArray<SI16, MOFUMOFUEVENT_FIELD_MAXSPWAN_COUNT>		m_siSpwanY;
#else
	SI16	m_siSpwanX[MOFUMOFUEVENT_FIELD_MAXSPWAN_COUNT];
	SI16	m_siSpwanY[MOFUMOFUEVENT_FIELD_MAXSPWAN_COUNT];
#endif

	SI16	m_siFieldIndex;

	SI16	m_siInPosX;
	SI16	m_siInPosY;

	SI16	m_siOutPosX;
	SI16	m_siOutPosY;
public:
	cltMofuMofuField()
	{
		Init();
	}

	~cltMofuMofuField()
	{
	}

	void Init()
	{
#ifdef _SAFE_MEMORY
		m_siSpwanX.ZeroMem();
		m_siSpwanY.ZeroMem();
#else
		memset(m_siSpwanX, 0, sizeof(m_siSpwanX));
		memset(m_siSpwanY, 0, sizeof(m_siSpwanY));
#endif

		m_siInPosX	= 0;
		m_siInPosY	= 0;

		m_siOutPosX	= 0;
		m_siOutPosY	= 0;

		ReInit();
	}

	void ReInit()
	{
#ifdef _SAFE_MEMORY
		m_siEnemyID.ZeroMem();
#else
		memset(m_siEnemyID, 0, sizeof(m_siEnemyID));
#endif
		m_siCount			= 0;
		m_siMamaMofuMofuID	= 0;

		m_siCreateCount		= 0;
		m_siKilledCount		= 0;
	}

	SI32 CreateEnemy();					// 40 ���� ����
	SI32 CreateMamaMofuMofu();			// �������ĸ��� ����
	BOOL KilledEnemy(SI32 siIndex, SI32 siEnemyID);

	BOOL CanAttackMaMaMofuMofu();
};

//---------------------------------
// ���ĸ��Ĵ��� �̺�Ʈ Ŭ����
//---------------------------------
class cltMofuMofuEvent : public cltEvent
{
protected:
	SI32				m_siKingMofuMofuID;			// ���� �������ĸ���

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMofuMofuEventReserveUnit, MOFUMOFUEVENT_ROOMNUM>		m_clUnit;
	NSafeTArray<cltMofuMofuField, MOFUMOFUEVENT_MAXFIELD_COUNT>			m_clField;
#else
	cltMofuMofuEventReserveUnit		m_clUnit[MOFUMOFUEVENT_ROOMNUM];
	cltMofuMofuField				m_clField[MOFUMOFUEVENT_MAXFIELD_COUNT];
#endif

	NUpdateTimer		m_UpdateTimer;
	NUpdateTimer		m_EnableEnterTimer;
	NUpdateTimer		m_CreateEnemyTimer;
	NUpdateTimer		m_EventTimer;

	BOOL				m_bEnterField;
	BOOL				m_bCreateFirstEnemy;
	SI32				m_siLastSendMsgMinute;

	SI32				m_siKingMofuMofuKilledCount;
	SI32				m_siMofuMofuKilledCount;

	SI16				m_siHour;			// ������ �ð��� ����Ѵ�.


public:
	cltMofuMofuEvent();
	~cltMofuMofuEvent();

	// ���ĸ��� �̺�Ʈ �ʱ�ȭ �۾�
	BOOL Init();

	// ���ĸ��� �̺�Ʈ �� �ʱ�ȭ �۾�
	BOOL ReInit();

	// ���ĸ��� �̺�Ʈ�� �����Ѵ�. 
	BOOL Start(SI16 siRoomIndex, SI32 VillageUnique);

	// ���ĸ��� �̺�Ʈ�� ����. - ���� �������ĸ��ĸ� ����� ��� or �ð��� �� �Ǿ��� ���
	void End();

	// ���ĸ��� �̺�Ʈ ����. 
	BOOL Action();

	// ���� ����?
	BOOL CanReserveRoom(SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siVillageUnique);
	// ����
	BOOL ReserveRoom(SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siVillageUnique);
	// ����
	BOOL SetRoom(SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siVillageUnique);
	// �� ���
	cltMofuMofuEventReserveUnit *GetRoom(SI32 siRoomIndex);
	// ���ȣ ���
	SI32 GetRoomIndex(SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour);

	// ���� �̺�Ʈ�� �����ϰ� �ִ� ����
	SI32 GetCurrentEventVillage();

	// �ʵ忡 ������ �����Ѱ�?
	BOOL CanEnterField()				{		return m_bEnterField;		}

	// ���� �����ð��� �̿��Ͽ� RoomIndex�� �����´�.
	SI32 GetRoomIndexFromServerTime();

	BOOL KilledEnemy(SI16 siFieldIndex, SI16 siIndex, SI32 siEnemeyID);

	cltMofuMofuField* GetField(SI32 siIndex)
	{
		if(siIndex < 0 || siIndex > MOFUMOFUEVENT_MAXFIELD_COUNT)		return NULL;
		return &m_clField[siIndex];
	}

	static	SI16 m_siMaxEnemyCount;

};

#endif