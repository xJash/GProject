//---------------------------------
// 2004/8/13 ���°�
//---------------------------------
#ifndef _EVENTHUNTING_H
#define _EVENTHUNTING_H

#include "..\Event.h"

#include <set>

#define EVENT_GOONZUDAY_PLAY_COUNT		1		// ���� ���̽� ������ �̺�Ʈ Ƚ��.


class cltEventTimeManager;


class cltEventHunting : public cltEvent{
public:

	SI16	siMonsterID;			// ������ ���̵�. 
	SI16	siMonsterLevel;			// ������ ���� ���� 

	cltEventHunting();
	~cltEventHunting();

	void Init();

	// �Ұ��縮 ��� �̺�Ʈ�� �����Ѵ�. 
	bool Start(SI32 sivillageunique, SI32 cost = 0);
	// �Ұ��縮 ��� �̺�Ʈ�� �����Ѵ�. 
	void End();

	// �Ұ��縮 ��� �̺�Ʈ ����. 
	bool Action();

	// ��ɰ��� �����. 
	void MakeMonster();

	// �� �Ѵ�� ģ���.
	void AddContributor(SI32 AttackerID);

private:
	std::set<SI32> _Contributors;
	SI32	siCost;

	// �̺�Ʈ Ƚ�� ī��Ʈ�� Ƚ �� ���� ���� �Լ���
public:
	//SI16	siHuntingEventcount;
	NSafeTArray<SI16, MAX_VILLAGE_NUMBER>		m_arEventCount_EachVillage;
	void	HuntingEventCount_Increase();
	void	HuntingEventCount_Reset();
	SI16	HuntingEvnetCount_Get();

	bool	IsMosterHit(SI32 siCharID, SI64 siExp, SI32 siRewardItemUnique = 0, SI32 siRewardItemNum = 0);

};


#endif