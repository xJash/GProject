//---------------------------------
// 2005/06/15 �豤��
//---------------------------------
#include "Kanghwado.h"

//--------------------------------
// Common
//--------------------------------
#include "..\..\Char\KindInfo\KindInfo.h"
#include "..\..\Order\Order.h"
#include "..\..\War\War.h"
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

//--------------------------------
// CommonLogic
//--------------------------------
#include "..\..\CommonLogic\CommonLogic.h"
#include "..\..\CommonLogic\MsgType-System.h"
#include "..\..\CommonLogic\MsgRval-Define.h"


//--------------------------------
// Server
//--------------------------------
#include "Server.h"
#include "Statistics\Statistics.h"

#include "..\..\DBManager\GameDBManager\DBMsg-Item.h"

extern cltCommonLogic* pclClient;

cltEventKanghwado::cltEventKanghwado() :cltEvent()
{
	Init();

}

cltEventKanghwado::~cltEventKanghwado()
{

}
void cltEventKanghwado::Init()
{
	cltEvent::Init();

	siMapIndex			= MAPINDEX_KANGHWADO;

	siTowerID			= 0;
	siTotalSolNumber	= 0;
	siTotalPatrolSolNumber = 0;
	siTotalShipNumber	= 0;
	siTotalMotherShipNumber = 0;
	siMonsterLevel		= 1;
	siMaxSolNumber      = 200;
	bWarStart			= false;

	for(SI32 i = 0; i< MAX_KANGHWADO_SOL_KIND;i++)
	{
		siSolKind[i]	= 0;
		siSolNum[i]		= 0;
	}

	for(i = 0; i< MAX_KANGHWADO_SOLSHIP_KIND;i++)
	{
		siSolShipKind[i]	= 0;
		siSolShipNum[i]		= 0;
	}
	
	for( i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		bMakeTroopShip[i] = false;
	}

	// ���� �� ��ǥ ����
	for( i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		MotherShipPoint[i].x = 40 + 50*i;
		MotherShipPoint[i].y = 180;
	}
	for( i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		TroopShipArrivalPoint[i].x = MotherShipPoint[i].x;
		TroopShipArrivalPoint[i].y = 138;
	}
}

// �̺�Ʈ ����. 
// bwarswitch : ������ ������ �޴°�.. 
// ���� :0 -> �̹� �̺�Ʈ�� �������̴�(�ٸ� ���� Ȥ�� �� ��������) 
//		-1 -> �ֱ� ���� �߿��� �̺�Ʈ�� ������ �� ����.
SI32 cltEventKanghwado::Start(SI32 villageunique, bool warstart)
{
	// �̹� �̺�Ʈ ���̸� ������ �� ����. 
	if(bEventSwitch == true)
		return 0;

	bEventSwitch = true;

	siVillageUnique = villageunique;			// �̺�Ʈ ����� �Ǵ� ����
	bWarStart		= warstart;					// true�� ����2�� ���ﶧ��
#ifdef _DEBUG
	dwLeftClock		= 900000;					// �̺�Ʈ �ܿ� �ð�. 
#else
	dwLeftClock		= 900000;	
#endif
	dwStartClock	= pclClient->CurrentClock;	// �̺�Ʈ ���� �ð�. 

	AddSol(KIND_WESTSWORDSOL,	4);
	AddSol(KIND_WESTGUNSOL,	4);
	AddSol(KIND_WESTOFFICER,	2);
	AddShip(KIND_WESTBATTLEBOAT, 2) ;
//	AddSol(KIND_CHINACANNONSOL, 3);

	// ������ ��պ� �����. 
	MakeTower();
	MakeCannon();
	MakeMotherShip();

	// DB�� ������ �޽����� �����Ѵ�. 
	((cltServer*)pclClient)->pclStatistics->siKanghwadoEventNumber++;

	return 1;
}

// �̺�Ʈ ��.
bool cltEventKanghwado::End()
{
	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� �ߴ��� �� ����. 
	if(bEventSwitch == false)
		return false;


	// ��ȭ�� ��ȣ�� �����Ѵ�. 
	// ���ʹ� ���ش�. 
	if(pclClient->pclCM->IsAlive(siTowerID) == TRUE )
	{
		if(pclClient->pclCM->CR[siTowerID]->GetKind() == KIND_GANGHWAGATE)
		{
			pclClient->pclCM->CR[siTowerID]->DeleteInCell();
			pclClient->pclCM->DeleteChar(siTowerID);
		}
	}

	SI32 i;
	for ( i = 0 ; i < MAX_CANNON_NUM ; ++i )
	{

		if(pclClient->pclCM->IsAlive(KanghwaCannon[i]) == TRUE )
		{
			if(pclClient->pclCM->CR[KanghwaCannon[i]]->GetKind() == KIND_GANGHWACANNON)
			{
				pclClient->pclCM->CR[KanghwaCannon[i]]->DeleteInCell();
				pclClient->pclCM->DeleteChar(KanghwaCannon[i]);
			}

		}
	}
	// �̺�Ʈ ���͸� ��� �����Ѵ�. 
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(IsNPC(id) == false && IsShip(id) == false)continue;

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
		if(pclchar->siCharMode == CHARMODE_KANGHWADOMON_PART1)
		{
			pclchar->DeleteInCell();
			if(pclClient->pclCM->DeleteChar(id) == TRUE)
			{
				index--;
			}
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOMON_PART2)
		{
			pclchar->DeleteInCell();
			if(pclClient->pclCM->DeleteChar(id) == TRUE)
			{
				index--;
			}
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOBATTLESHIP)
		{
			pclchar->DeleteInCell();
			if(pclClient->pclCM->DeleteChar(id) == TRUE)
			{
				index--;
			}
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOMOTHERSHIP)
		{
			pclchar->DeleteInCell();
			if(pclClient->pclCM->DeleteChar(id) == TRUE)
			{
				index--;
			}
		}
	}

	bEventSwitch = false;

	DelSolAll();
	DelShipAll();

	for( i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		bMakeTroopShip[i] = false;
	}

	return true;

}


bool cltEventKanghwado::Action()
{
	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� ������ �� ����. 
	if(bEventSwitch == false)return false;

	// ���� �ֱ�� ���´�. 
	if(pclClient->GetFrame() % 150)return false;


	siTotalSolNumber	=	0;
	siTotalPatrolSolNumber = 0;
	siTotalShipNumber	=   0;
	siTotalMotherShipNumber = 0;
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(IsNPC(id) == false && IsShip(id) == false )continue;

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
		if(pclchar->siCharMode == CHARMODE_KANGHWADOMON_PART1)
		{
			siTotalSolNumber++;
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOMON_PART2)
		{
			siTotalPatrolSolNumber++;
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOBATTLESHIP)
		{
			siTotalShipNumber++;
		}
		else if(pclchar->siCharMode == CHARMODE_KANGHWADOMOTHERSHIP)
		{
			siTotalMotherShipNumber++;
		}
	}

	SI32 i;
	for(i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		if(pclClient->pclCM->IsAlive(siMotherShipID[i]))
		{
			// ���ۼ��� �� ������� �����Ƿ� ���ۼ� �����
			if(bMakeTroopShip[i] == false)
			{
				// ���͸� ��ġ�Ѵ�. 
				cltServer* pclserver = (cltServer*)pclClient;

				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);		// ��� NPC�� ������, ������� ��ȣ����. 

				SI32 id = pclserver->SetNPCChar(KIND_WESTBOAT, VILLAGE_NONE, NULL, 1, 0, MotherShipPoint[i].x, MotherShipPoint[i].y, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				
				if(id)
				{
					((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_KANGHWADOMON_PART1;
					OrderMove(id, TroopShipArrivalPoint[i].x, TroopShipArrivalPoint[i].y, BY_PLAYER);
					siTroopShipID[i] = id;

					// ���ۼ��� ����� ����
					bMakeTroopShip[i] = true;
				}
			}
		}	
	}

	// ���ۼ��� �ش� ��ǥ�� �����ϸ� ���� ��Ų��!!
	for(i=0; i<MAX_WESTMOTHERSHIP; ++i)
	{
		if(bMakeTroopShip[i])
		{
			if( pclClient->pclCM->CR[siTroopShipID[i]]->GetX() == TroopShipArrivalPoint[i].x &&
				pclClient->pclCM->CR[siTroopShipID[i]]->GetY() == TroopShipArrivalPoint[i].y )
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[siTroopShipID[i]];
				if(pclchar->siCharMode == CHARMODE_KANGHWADOMON_PART1)
				{
					pclchar->DeleteInCell();
					if(pclClient->pclCM->DeleteChar(siTroopShipID[i]) == TRUE)
					{
						bMakeTroopShip[i] = false;
					}
				}
			}
		}
	}

	// ���� ������� �ִٸ� ������� ��ġ�Ѵ�. 
	MakeSoldier();
	MakeBattleBoat();

	// 2�� �����϶� ������ ����
//	if( bWarStart == true )
	MakePatrolSoldier();

	// ���� ����. 
	bool bwinswitch		= false;
	bool bloseswitch	= false;


	// �ð��� �ʰ��Ǹ� �¸� 
	DWORD dwelapsedclock = pclClient->CurrentClock - dwStartClock;

	SI32 leftsecond;
	if(dwLeftClock > dwelapsedclock)
	{
		leftsecond = (dwLeftClock - dwelapsedclock) / 1000 ;
	}
	else
	{
		leftsecond = 0;
	}


	if(dwelapsedclock >= dwLeftClock)
	{
		bwinswitch = true;
		if(siMonsterLevel < 100)siMonsterLevel +=5;

		char* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			char* pText = GetTxtFromMgr(3677);
			pclClient->pclLog->FilePrint("Config\\Kanghwado.txt", pText, pvillname, siMonsterLevel);
		}

		//-------------------------------------------
		// �¸��� ������ ��ھ������� �����Ѵ�. 
		//-------------------------------------------
		RewardWiner();

	}
	else if(siTotalMotherShipNumber == 0)	// ���� ���� �ı��Ǹ�
	{
		bwinswitch = true;
		if(siMonsterLevel < 100)siMonsterLevel +=5;

		char* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			char* pText = GetTxtFromMgr(3677);
			pclClient->pclLog->FilePrint("Config\\Kanghwado.txt", pText, pvillname, siMonsterLevel);
		}

		//-------------------------------------------
		// �¸��� ������ ��ھ������� �����Ѵ�. 
		//-------------------------------------------
		RewardWiner();
	}

	if(pclClient->pclCM->IsAlive(siTowerID) == false || pclClient->pclCM->CR[siTowerID]->GetKind() != KIND_GANGHWAGATE)
	{
		bloseswitch = true;
		siMonsterLevel =  max(1, (siMonsterLevel - 5));

		char* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			char* pText = GetTxtFromMgr(3678);
			pclClient->pclLog->FilePrint("Config\\Kanghwado.txt", pText, pvillname, siMonsterLevel);
		}

	}

	if(bwinswitch || bloseswitch)
	{
		End();
	}


	if(TABS(pclClient->CurrentClock - dwLastInfoClock) > 3000)
	{
		dwLastInfoClock = pclClient->CurrentClock;

		// ���� ��Ȳ�� �̺�Ʈ ����ڵ鿡�� �뺸�Ѵ�.(�ܿ��ð�..) 
		SI32 mode = 0;
		if(bwinswitch)
		{
			mode = 1;
		}
		else if(bloseswitch)
		{
			mode = -1;
		}

		if( bWarStart == true )
		{
			cltGameMsgResponse_KanghwadoInfo clinfo(0, leftsecond, mode);
			cltMsg clMsg(GAMEMSG_RESPONSE_KANGHWADOINFO, sizeof(clinfo), (char*)&clinfo);
			pclClient->pclCM->SendAllPersonMsg((char*)&clMsg);
		}
		else
		{
			cltGameMsgResponse_KanghwadoInfo clinfo(siVillageUnique, leftsecond, mode);
			cltMsg clMsg(GAMEMSG_RESPONSE_KANGHWADOINFO, sizeof(clinfo), (char*)&clinfo);
			pclClient->pclCM->SendAllPersonHomeMsg((char*)&clMsg, siVillageUnique);
		}
	}


	return true;
}

// ���� ������� �����.
void cltEventKanghwado::MakeSoldier()
{
	// ������� �ľ��Ѵ�. 200���� �Ѱܼ��� �ȵȴ�. ������ ������� ��������
	if(siTotalSolNumber >= siMaxSolNumber)return ;

	SI32 i, j, k;

	POINT point[3] = {	40, 110,
						90, 110,
						140, 110,
					};

	POINT center = { 88, 43};

	for(i = 0;i < MAX_KANGHWADO_SOL_KIND;i++)
	{
		if(siSolKind[i] == 0)continue;

		// ���͸� ��ġ�Ѵ�. 
		cltServer* pclserver = (cltServer*)pclClient;
		for(j = 0;j < siSolNum[i];j++)
		{
			for(k = 0;k < 3;k++)
			{
			//	if( pclClient->pclCM->IsAlive(siMotherShipID[k]) == false )
			//		continue;

				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

				SI32 id = pclserver->SetNPCChar(siSolKind[i], VILLAGE_NONE, NULL, siMonsterLevel, 0, point[k].x, point[k].y, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				if(id)
				{
					((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_KANGHWADOMON_PART1;
					OrderMove(id, center.x + 15 - rand() % 30, center.y - rand() % 5, BY_PLAYER);
				}
			}
		}

	}

}

// ���� �������� �����
void cltEventKanghwado::MakePatrolSoldier()
{
	// ������� �ľ��Ѵ�. 200���� �Ѱܼ��� �ȵȴ�. 
	if(siTotalPatrolSolNumber >= 100)
		return ;

	SI32 kind = KIND_WESTPATROLSOL;
	SI32 i, j, k;

	POINT center = { 88, 37};

	// ���͸� ��ġ�Ѵ�. 
	cltServer* pclserver = (cltServer*)pclClient;
	for(i = 0;i < 10;i++)
	{
		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

		SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, siMonsterLevel, 0, 10 + rand()%160, 10 + rand()%15, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if(id)
		{
			((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_KANGHWADOMON_PART2;
		}
	}
}

// ���� ������� �����.
void cltEventKanghwado::MakeBattleBoat()
{
	// ������ 60���� ����
	if(siTotalShipNumber >= 60)return ;

	SI32 i, j, k;

	for(i = 0;i < MAX_KANGHWADO_SOLSHIP_KIND;i++)
	{
		if(siSolShipKind[i] == 0)continue;

		// ���͸� ��ġ�Ѵ�. 
		cltServer* pclserver = (cltServer*)pclClient;
		for(j = 0;j < siSolShipNum[i];j++)
		{
			for(k = 0;k < 3;k++)
			{
				//	if( pclClient->pclCM->IsAlive(siMotherShipID[k]) == false )
				//		continue;

				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

				SI32 id = 0;
				if( k == 0)	// �� �տ��� ������ ����!!
					id = pclserver->SetNPCChar(siSolShipKind[i], VILLAGE_NONE, NULL, siMonsterLevel, 0, MotherShipPoint[k].x, MotherShipPoint[k].y - 5 - rand()%10, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				else if( k == 1) // �� ���ʿ��� ������ ����!!
					id = pclserver->SetNPCChar(siSolShipKind[i], VILLAGE_NONE, NULL, siMonsterLevel, 0, MotherShipPoint[k].x - 5 - rand()%10, MotherShipPoint[k].y - 5 + rand()%5, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				else if( k == 2) // �� �����ʿ��� ������ ����!!
					id = pclserver->SetNPCChar(siSolShipKind[i], VILLAGE_NONE, NULL, siMonsterLevel, 0, MotherShipPoint[k].x + 5 + rand()%10, MotherShipPoint[k].y - 5 + rand()%5, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				
				if(id)
				{
					((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_KANGHWADOBATTLESHIP;
				}
				
			}
		}

	}

}

// ���� �踦 �����.
void cltEventKanghwado::MakeMotherShip()
{
	SI32 i;
	SI32 kind = KIND_WESTMOTHERSHIP;

	// �踦 ��ġ�Ѵ�. 
	cltServer* pclserver = (cltServer*)pclClient;
	
	for(i = 0;i < MAX_WESTMOTHERSHIP;++i)
	{
		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

		SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, siMonsterLevel, 0, MotherShipPoint[i].x, MotherShipPoint[i].y, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if(id)
		{
			((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_KANGHWADOMOTHERSHIP;
			siMotherShipID[i] = id;
		}
	}
}

// ��ȭ�� ������ �����. 
void cltEventKanghwado::MakeTower()
{
	// ĳ����  ������ �����Ѵ�. 
	SI32 kind = KIND_GANGHWAGATE;

	// ĳ���� ���� ��ġ�� �����Ѵ�.
	SI32 x	= 88;
	SI32 y	= 37;

	// ���͸� ��ġ�Ѵ�. 
	cltServer* pclserver = (cltServer*)pclClient;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);		// ��� NPC�� ������, ������� ��ȣ����. 

	SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 1, 0, x, y, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
	if(id)
	{
		siTowerID	= id;	// ������ ���̵� Ȯ���Ѵ�.
	}
}

void cltEventKanghwado::MakeCannon()
{
	SI32 kind = KIND_GANGHWACANNON;

	// ���͸� ��ġ�Ѵ�. 
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 CannonX1[3]=
	{
		33, 36, 39
	};

	SI32 CannonX2[4]=
	{
		85, 88, 91, 94
	};

	SI32 CannonX3[3]=
	{
		122, 125, 128
	};
	
	SI32 i;
	for(i=0;i<3;++i)
	{
		cltInnerStatusInfo clinnerstatus;	
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);		// ��� PC�� ��ȣ��, ������� ������. 

		SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 1, 0, CannonX1[i] , 45, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if(id)
		{
			KanghwaCannon[i]	= id;	// ������ ���̵� Ȯ���Ѵ�.
		}
	}

	for(i=0;i<4;++i)
	{
		cltInnerStatusInfo clinnerstatus;	
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);		// ��� PC�� ��ȣ��, ������� ������. 

		SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 1, 0, CannonX2[i] , 55, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if(id)
		{
			KanghwaCannon[i + 3]	= id;	// ������ ���̵� Ȯ���Ѵ�.
		}
	}

	for(i=0;i<3;++i)
	{
		cltInnerStatusInfo clinnerstatus;	
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);		// ��� PC�� ��ȣ��, ������� ������. 

		SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 1, 0, CannonX3[i] , 45, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if(id)
		{
			KanghwaCannon[i + 7]	= id;	// ������ ���̵� Ȯ���Ѵ�.
		}
	}
}


void cltEventKanghwado::AddSol(SI32 kind, SI32 num)
{
	SI32 i;

	for(i = 0;i < MAX_KANGHWADO_SOL_KIND;i++)
	{
		if(siSolKind[i] == 0)
		{
			siSolKind[i]	= kind;
			siSolNum[i]		= num;
			return ;
		}
	}
}

void cltEventKanghwado::AddShip(SI32 kind, SI32 num)
{
	SI32 i;

	for(i = 0;i < MAX_KANGHWADO_SOLSHIP_KIND;i++)
	{
		if(siSolShipKind[i] == 0)
		{
			siSolShipKind[i]	= kind;
			siSolShipNum[i]		= num;
			return ;
		}
	}
}

//-------------------------------------------
// �¸��� ������ ��ھ������� �����Ѵ�. 
//-------------------------------------------
void cltEventKanghwado::	RewardWiner()
{
	cltServer* pclserver = (cltServer*)pclClient;

	// ���� �ֹ��� 1���� ��� ��ǰ�� �ش�. 
	SI16 villagerlist[1000];
	SI32 listindex = 0;

	

	// ���� �ð��� ����Ͽ� ����ġ�� �ش�. 
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		cltCharServer* pclchar  = (cltCharServer*)pclClient->pclCM->CR[id];
		// ������� �Ŀ��Ը� �����Ѵ�. 
		if(pclchar->IsValidConnection() == false)continue;
		// �ش� ���� �ֹο��Ը� �ش�.
		if(bWarStart == false)
			if(pclchar->pclCI->clBI.siHomeVillage != siVillageUnique)continue;
		// �̺�Ʈ ������ ��ġ�ϰ� �־�� �Ѵ�. 
		if(pclchar->GetMapIndex() != siMapIndex)continue;


		SI32 exp = pclchar->pclCI->clIP.GetLevel()  * (30 + siMonsterLevel / 3);
		pclchar->IncreaseExp(exp);

		SI32 fameexp = min(50, max(1, exp / 20));
		pclchar->IncreaseFameExp(fameexp);

		cltGameMsgResponse_KanghwadoReward clinfo(exp, fameexp, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_KANGHWADOREWARD, sizeof(clinfo), (char*)&clinfo);
		pclchar->SendNetMsg((char*)&clMsg);

		// ���� �ֹ� ����Ʈ�� �ۼ��Ѵ�. (��� ��ǰ�� �ֱ� ���ؼ� )
		villagerlist[listindex] = id;

		if(listindex < (1000-1))
		{
			listindex++;
		}
	}

	if(listindex)
	{
		id = villagerlist[rand() % listindex];
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

		cltItem clItem;
		SI32 itemunique = pclClient->pclItemManager->GetRandBigWarItem();
		//SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
		if(itemunique > 0)
		{
			//clItem.Set( &pclClient->pclItemManager->pclItemInfo[ref]->clItem);
			bool RareSwitch = false;
			if ( pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, &RareSwitch,
				0,0,0,0,0,14 ) == true )
			{
				SI32 rtnvalue = 0;
				if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_KANGHWADO, &rtnvalue) == false)
				{
					// �κ��� ���ڸ��� ��� �߰��� �� ����. 
					if(rtnvalue == CANADDINV_FAIL_FULL)
					{
						((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
					}
				}
			}
		}
	}


	// �ٴڿ� �ݱ��� �����Ѵ�. 
	cltItem clItem;
	bool brareswitch ;

	if(pclserver->pclItemManager->MakeRandItemUnique( 5045, &clItem, 0, &brareswitch) )
	{
		clItem.SetItemNum(1) ;

		SI32 index = 0;
		SI32 totalindex = 0;
		while(index < 100 && totalindex < 1000)
		{
			SI32 x = rand() % pclserver->pclMapManager->pclMapArray[siMapIndex]->GetXsize();
			SI32 y = rand() % pclserver->pclMapManager->pclMapArray[siMapIndex]->GetYsize();

			SI32 targetx, targety;
			if(pclserver->pclMapManager->FindProperAreaForDrop(siMapIndex, x, y, &targetx, &targety) == true)
			{
				index++;
				pclserver->DropItem(siMapIndex, targetx, targety, &clItem, 0);
			}
			totalindex++;
		}
	}
}

void cltEventKanghwado::DelSolAll()
{
	for ( SI32 i = 0 ; i < MAX_KANGHWADO_SOL_KIND ; i ++ )
	{
		if ( siSolKind[i] != 0 )
		{
			siSolKind[i] = 0 ;
			siSolNum[i] = 0 ;
		}
	}
}

void cltEventKanghwado::DelShipAll()
{
	for ( SI32 i = 0 ; i < MAX_KANGHWADO_SOLSHIP_KIND ; i ++ )
	{
		if ( siSolShipKind[i] != 0 )
		{
			siSolShipKind[i] = 0 ;
			siSolShipNum[i] = 0 ;
		}
	}
}
