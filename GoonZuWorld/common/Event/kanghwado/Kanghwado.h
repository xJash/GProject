//---------------------------------
// 2005/06/15 �豤��
//---------------------------------
#ifndef _EVENTKANGHWADO_H
#define _EVENTKANGHWADO_H

#include "..\Event.h"

#define MAX_KANGHWADO_SOL_KIND	3
#define MAX_KANGHWADO_SOLSHIP_KIND	1

#define MAX_WESTMOTHERSHIP	3

#define MAX_CANNON_NUM 10

class cltEventKanghwado : public cltEvent{
public:
	cltEventKanghwado();
	~cltEventKanghwado();

	// ��ȭ�� ��ȣ�� ���̵�(����)
	SI32 siTowerID;		
	// ���� �� ���̵�
	SI32 siMotherShipID[MAX_WESTMOTHERSHIP];
	// ���� ���ۼ� ���̵�
	SI32 siTroopShipID[MAX_WESTMOTHERSHIP];
	// ��ȭ���� ���� �����
	SI32 siTotalSolNumber;
	// ��ȭ���� ���� ���������
	SI32 siTotalPatrolSolNumber;
	// ��ȭ���� ���� ���
	SI32 siTotalShipNumber;
	SI32 siTotalMotherShipNumber;
	// ��ȭ���� ����� ����
	SI32 siMonsterLevel;
	// ��ȭ�� ���� �ε���
	SI32 siMapIndex;
	// �ִ�� ���� �����
	SI32 siMaxSolNumber;
	// ����2�� �����ΰ�? ���� �̺�Ʈ�ΰ�?
	bool bWarStart;

	SI32 siSolKind[MAX_KANGHWADO_SOL_KIND];
	SI32 siSolNum[MAX_KANGHWADO_SOL_KIND];

	SI32 siSolShipKind[MAX_KANGHWADO_SOLSHIP_KIND];
	SI32 siSolShipNum[MAX_KANGHWADO_SOLSHIP_KIND];

	// ���ۼ��� ��������� üũ
	bool bMakeTroopShip[MAX_WESTMOTHERSHIP];	
	
	// ���� ������ǥ
	POINT MotherShipPoint[MAX_WESTMOTHERSHIP];

	// ���ۼ��� �����ؾ��� ��ǥ
	POINT TroopShipArrivalPoint[MAX_WESTMOTHERSHIP];

	// ��ȭ���� ���̵�
	SI32 KanghwaCannon[MAX_CANNON_NUM];
	
	void Init();

	// �̺�Ʈ ����. 
	SI32 Start(SI32 villageunique, bool warstart = false);
	// �̺�Ʈ ��.
	bool End();

	bool Action();

	// ��ȭ�� ������� �����.
	void MakeSoldier();

	void MakePatrolSoldier();

	// ��ȭ�� ��ȣ�� �����. 
	void MakeTower();

	// ��ȭ�� ���� �����
	void MakeCannon();

	// ���� �� �����
	void MakeMotherShip();

	// ���� ���ݹ� �����
	void MakeBattleBoat();

	void AddSol(SI32 kind, SI32 num);
	void AddShip(SI32 kind, SI32 num);

	void DelSolAll();
	void DelShipAll();

	//-------------------------------------------
	// �¸��� ������ ��ھ������� �����Ѵ�. 
	//-------------------------------------------
	void RewardWiner();

};

#endif