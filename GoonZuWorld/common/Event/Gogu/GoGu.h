//---------------------------------
// 2004/8/19 ���°�
//---------------------------------
#ifndef _EVENTGOGU_H
#define _EVENTGOGU_H

#include "..\Event.h"

#define MAX_GOGU_SOL_KIND	3

class cltEventGogu : public cltEvent{
public:
	cltEventGogu();
	~cltEventGogu();

	SI32 siTowerID;			// �������պ� ���̵�
	SI32 siTotalSolNumber;
	SI32 siMonsterLevel;

	SI32 siMapIndex;

	SI32 siSolKind[MAX_GOGU_SOL_KIND];
	SI32 siSolNum[MAX_GOGU_SOL_KIND];

	void Init();

	// �̺�Ʈ ����. 
	SI32 Start(SI32 villageunique, bool bwarswitch);
	// �̺�Ʈ ��.
	bool End();
	
	bool Action();

	// ���� ������� �����.
	void MakeSoldier();
	
	// �������պ� �����. 
	void MakeTower();

	void AddSol(SI32 kind, SI32 num);

	//-------------------------------------------
	// �¸��� ������ ��ھ������� �����Ѵ�. 
	//-------------------------------------------
	void RewardWiner();
	
};

#endif