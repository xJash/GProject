//---------------------------------
// 2004/12/23 ���ؿ�
//---------------------------------

#ifndef _MONSTERGROUPMANAGER_H
#define _MONSTERGROUPMANAGER_H

class cltIDManager;
class cltCharCommon;
class cltItem;

#include "CommonHeader.h"

#define MAX_MONSTER_GROUP_NUM			100		// ���� �� �ִ� �׷� ��

#define MAX_MONSTER_NUM_PER_GROUP		5		// �׷� �� �ִ� ���� ��

#define MAX_MONSTER_KIND_PER_GROUP		5		// �׷� �� �ִ� ���� ���� ��

class cltKindInfoPerGroup{
public:
	SI32		siKind;			// ����
	SI32		siValue;		// ����
	SI32		siLevel;		// ����

	void Init();
};

// �׷� ���� ����
class cltInitInfoPerGroup{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltKindInfoPerGroup, MAX_MONSTER_KIND_PER_GROUP>		pclKindInfoPerGroup;
#else
	cltKindInfoPerGroup			pclKindInfoPerGroup[MAX_MONSTER_KIND_PER_GROUP];
#endif

	SI32						siMapIndex;		// ������ �� �ε���
	SI32						siCenterX;		// ������ ���� ��ǥ x
	SI32						siCenterY;		// ������ ���� ��ǥ y
	SI32						siRadius;		// ������ ��ġ ����
	bool						bMapBoss;		// ���� ���� �׷��̳� �ƴϳ�

	void Init();
	bool BeingKindInfo(SI32 index);
};

// ���� �׷� ����
class cltMonsterGroupInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_MONSTER_NUM_PER_GROUP>		siCharUnique;
#else
	SI32						siCharUnique[MAX_MONSTER_NUM_PER_GROUP];
#endif
	SI32						siBossUnique;
	bool						bMapBoss;				// ���� ���� �׷��̳� �ƴϳ�
	bool						bSetMapBossGroup;		// ���� ���� �׷��̸� �������� �����߳� �� �߳�

	void Init();
};

class cltMonsterGroupManager{
public:
	cltMonsterGroupManager();
	~cltMonsterGroupManager();

#ifdef _SAFE_MEMORY
	NSafeTArray<cltInitInfoPerGroup, MAX_MONSTER_GROUP_NUM>		pclInitInfo;
	NSafeTArray<cltMonsterGroupInfo, MAX_MONSTER_GROUP_NUM>		pclMonsterGroup;
#else
	cltInitInfoPerGroup		pclInitInfo[MAX_MONSTER_GROUP_NUM]; // 1~MAX_MONSTER_GROUP_NUM - 1
	cltMonsterGroupInfo		pclMonsterGroup[MAX_MONSTER_GROUP_NUM]; // 1~MAX_MONSTER_GROUP_NUM - 1
#endif

public:
	void Action();

	bool BeingGroup(SI32 index);
	bool BeingInitGroup(SI32 index);
	bool IsMapBossGroup(SI32 index);

	void MakeGroup(SI32 index);
	void SetBoss(SI32 index);

	void MakeMapBossGroup(SI32 index);

	void DeleteMember(SI32 index,SI32 unique,BOOL bBoss );

	SI32 GetBossID(SI32 index);

	bool FindBattleMember(SI32 * targetID,SI32 index,BOOL bBoss);
	void MemberAttack(SI32 targetID,SI32 index);

	bool SetInitFromFile(SI32 index , SI32 mapindex,SI32 centerx,SI32 centery ,SI32 radius,
						 SI32* kind,SI32* level,SI32* value );

};

#endif
