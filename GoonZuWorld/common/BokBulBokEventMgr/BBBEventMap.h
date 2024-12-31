//===================================================================================================
// ����	 : ���Һ� �̴ϰ���
// ����ġ: Switch_BokBulBok
// ����	 : ���Һ� ���� ������ �޴���.
// �ۼ���: 2009.08.10
// �ۼ���: ������
//===================================================================================================

#ifndef _BBBEVENT_MAP_H_
#define _BBBEVENT_MAP_H_

#include "../../Common/CommonHeader.h"



#define PLAY_MAP_INDEX			97		// ����
#define MAX_MONSTER_COUNT		10

#define MONSTER_TYPE_NORMAL		0		// �Ϲ�/���� ��
#define MONSTER_TYPE_ONEKILL	1		// ��ų��
#define MONSTER_TYPE_KEY		2		// Ű��
#define MONSTER_TYPE_ITEM		3		// ������

#define MAX_ITEMKIND_NUM		4
#define MAX_EVENTMAP_NUM		4
#define MAX_GENMOBKIND_NUM		4
#define MAX_BBBSTAGE_NUM		10


//KIND_KOINOBORYENG
//KIND_KINGPIG
//KIND_RABBITBIG
//KIND_MUSHROOMBOSS


struct _StageInfo
{
	SI16 siOneKillMobCount;
	SI16 siKeyMobCount;
	SI16 siItemMobCount;
};

struct _MapPosition
{
	SI16 posX;
	SI16 posY;
};



class CBBBEventMap
{
public:
	CBBBEventMap(SI16 siMapNumber);
	~CBBBEventMap(void);

	// ����ƽ ����
protected:
	_StageInfo m_aStageInfo[MAX_BBBSTAGE_NUM];			// �������� ���� (����ƽ���� ��ä�� 1���� ����)
	_MapPosition m_aMapPosition[MAX_EVENTMAP_NUM];		// ���� �߽� ��ġ
	SI32 m_aMonsterKind[MAX_GENMOBKIND_NUM];			// ���� ����ũ
	SI32 m_aItemUnique[MAX_ITEMKIND_NUM];				// ��� ���� ������ ����ũ

public:
	SI32 m_siStageStartDelay;				// �������� ���۶� ī��Ʈ �ð� (ī��Ʈ �ð� + ��ŸƮ1��)
	SI32 m_siStageLoseDelay;				// �������� ���� ǥ�� �ð�
	SI32 m_siStageWinDelay;					// �������� �� ǥ�� �ð�
	SI32 m_siStagePlayDelay;				// �������� �÷��� �ð�
	SI32 m_siTotalStageWinDelay;		    // ���� �������� �Ϸ��� �� ǥ�� �ð�
	SI32 m_siItemDropRate;					// �������� ���� ����� Ȯ��

protected:
	// �ʵ带 �̿����� ����� ����
	SI16 m_siMapNumber;
	bool m_bOccupied;						// �� �ʵ尡 ��������� üũ
	SI32 m_siUserID;						// ���� ���̵�
	TCHAR m_szUserName[MAX_PLAYER_NAME];	// ���� �̸�
	DWORD m_dwStageStartTime;				// �� ���������� ���۵� �ð� (15�� ������ ����)
	bool m_bStageStartFlag;					// �������� ���� �÷���
	DWORD m_dwStageEndTime;					// ���������� ���� �ð�
	bool m_bStageEndFlag;					// �������� ����
	bool m_bNeedClearMap;					// ���� Ŭ�����ؾ� �Ѵٰ� �÷��� ����
	bool m_bNeedCreateMonster;				// �ʿ� ���� ������ �� �ʿ䰡 ������
	bool m_bTemporaryOccupied;				// �ӽ÷� ���� �Ǿ� �ֳ�? (���� ó�������� �ʿ� �ӽ� ���� ���� ĳ���� ������ ������°� ���� ����)
	DWORD m_dwTemporaryOccupyCancelTime;	// �ӽ� ���� ���� ���ѽð� (10��)

	// �ʵ��� ���� ����
	SI16 m_siCurrentStage;							// ���� �������� ��������

	SI16 m_aStageMobInfo[MAX_MONSTER_COUNT];		// ���� ���������� ���� ���� ���� (0: �Ϲ�, 1:��ų, 2:Ű, 3:������)
	SI32 m_aGenMosterUnique[MAX_MONSTER_COUNT];		// ���� ���������� �� �� �� ����ũ


public:
	// ���� üũ�� ���� �Լ��� ( set �Լ����� ������ ���������θ� ����ϵ��� ���)
	bool IsAvailable();
	void SetUserID(SI32 siUserID);
	SI32 GetUserID();
	void SetUserName(TCHAR* pszUserName);
	TCHAR* GetUserName();

	void SetCurrentStage(SI16 siCurrentStage);
	SI16 GetCurrentStage();

	void SetTemporaryReserve(SI32 siUserID);
	void ActiveTemporaryReserve(SI32 siUserID);
	void CancelTemporaryReserve(SI32 siUserID);

	// ���� �ֵ� �۾�. �� �Լ��� ���ؼ� �� Ŭ������ ����
	void DoTimeTask();
	void EnterUser(SI32 siUserID, TCHAR* pszUserName);		// ������ ����� �Ż���� �˾ƾ� �Ѵ�.
	void LeaveUser();										// ������ ����� �Ż���� ���ʿ� ����.
	void GameStart();
	void GameFail();
	void GameClear();

	// ���� ó�� �Լ���
protected:
	void _WarpUserToMap(SI16 siMapNumber);
	void _CreateMonster(SI16 siStageNumber);
	void _StartCount();
	void _StartStage(SI16 siStageNumber);
	bool _EndStage();
	void _ClearThisMap();
	void _ClearMonster();

	void _SetupCurrentStageMonsterInfo();
	void _SetKeyMob();
	void _SetOneKillMob();
	void _SetItemMob();
	void _NextStage();
	void _ClearReward();

	void _Load_DropItemKind();				// LFF : Load From File - ���Ͽ��� �������� ����� ������ ������ �ε�
	void _Load_EventMapCenterPosition();	// ���Ͽ��� �̺�Ʈ ���� �߾� �������� �ε�
	void _Load_GenMobKind();				// ���Ͽ��� ���� ���� ������ �ε�
	void _Load_StageMobInfo();				// ���Ͽ��� ���������� �� ����(��ų�� ��, Ű�� ��, ������ ��)�� �ε�
	void _Load_BBBGameInfo();				// ���Һ� ������ �⺻���� �Ӽ� �ε� (�÷��� �ð�, ���� �̹��� ǥ�� �ð�)

	void _Notice_8_StageUser();
};

#endif
