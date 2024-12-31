//---------------------------------
// 2004/8/19 ���°�
//---------------------------------
#include "Gogu.h"

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

cltEventGogu::cltEventGogu() :cltEvent()
{
	Init();

}

cltEventGogu::~cltEventGogu()
{
	
}
void cltEventGogu::Init()
{
	cltEvent::Init();

	siMapIndex			= 159;

	siTowerID			= 0;
	siTotalSolNumber	= 0;
	siMonsterLevel		= 1;

	for(SI32 i = 0; i< MAX_GOGU_SOL_KIND;i++)
	{
		siSolKind[i]	= 0;
		siSolNum[i]		= 0;
	}

}

// �̺�Ʈ ����. 
// bwarswitch : ������ ������ �޴°�.. 
// ���� :0 -> �̹� �̺�Ʈ�� �������̴�(�ٸ� ���� Ȥ�� �� ��������) 
//		-1 -> �ֱ� ���� �߿��� �̺�Ʈ�� ������ �� ����.
SI32 cltEventGogu::Start(SI32 sivillageunique, bool bwarswitch)
{
	// �̹� �̺�Ʈ ���̸� ������ �� ����. 
	if(bEventSwitch == true)return 0;

	// �ֱ� ������ ����ؾ� �ϴ� ��쿡�� �ֱ� �����߿��� �̺�Ʈ�� ������ �� ����. 
	if(bwarswitch)
	{
		if(pclClient->pclWarManager->bWarSwitch == true)return -1;	
	}
	
	bEventSwitch = true;

	siVillageUnique = sivillageunique;			// �̺�Ʈ ����� �Ǵ� ����
	dwLeftClock		= 1200000;					// �̺�Ʈ �ܿ� �ð�. 
	dwStartClock	= pclClient->CurrentClock;	// �̺�Ʈ ���� �ð�. 

	AddSol(KIND_CHINASPEARSOL,	6);
	AddSol(KIND_CHINABOWSOL,	6);
	AddSol(KIND_CHINACANNONSOL, 3);




	// ������ ��պ� �����. 
	MakeTower();

	// DB�� ������ �޽����� �����Ѵ�. 
	((cltServer*)pclClient)->pclStatistics->siGoguEventNumber++;

	
	return 1;
}

// �̺�Ʈ ��.
bool cltEventGogu::End()
{
	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� �ߴ��� �� ����. 
	if(bEventSwitch == false)return false;
	

	// ������ ��պ� �����Ѵ�. 
	// ���ʹ� ���ش�. 
	if(pclClient->pclCM->IsAlive(siTowerID) == true )
	{
		if(pclClient->pclCM->CR[siTowerID]->GetKind() == KIND_GWANGGAETOMONUMENT)
		{
			pclClient->pclCM->CR[siTowerID]->DeleteInCell();
			pclClient->pclCM->DeleteChar(siTowerID);
		}
		
	}

	// �̺�Ʈ ���͸� ��� �����Ѵ�. 
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(IsNPC(id) == false)continue;
		
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
		if(pclchar->siCharMode == CHARMODE_GOGUMON)
		{
			pclchar->DeleteInCell();
			if(pclClient->pclCM->DeleteChar(id) == true)
			{
				index--;
			}
		}
	}
	
	bEventSwitch = false;

	return true;

}


bool cltEventGogu::Action()
{
	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� ������ �� ����. 
	if(bEventSwitch == false)return false;
	
	// ���� �ֱ�� ���´�. 
	if(pclClient->GetFrame() % 150)return false;
	

	siTotalSolNumber	=	0;
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(IsNPC(id) == false)continue;
		
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
		if(pclchar->siCharMode == CHARMODE_GOGUMON)
		{
			siTotalSolNumber++;
		}
	}
	

	// ���� ������� �ִٸ� ������� ��ġ�Ѵ�. 
	MakeSoldier();

	
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
			pclClient->pclLog->FilePrint("Config\\Gogu.txt", pText, pvillname, siMonsterLevel);
		}

		//-------------------------------------------
		// �¸��� ������ ��ھ������� �����Ѵ�. 
		//-------------------------------------------
		RewardWiner();
		
	}


	if(pclClient->pclCM->IsAlive(siTowerID) == false || pclClient->pclCM->CR[siTowerID]->GetKind() != KIND_GWANGGAETOMONUMENT)
	{
		bloseswitch = true;
		siMonsterLevel =  max(1, (siMonsterLevel - 5));

		char* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			char* pText = GetTxtFromMgr(3678);
			pclClient->pclLog->FilePrint("Config\\Gogu.txt", pText, pvillname, siMonsterLevel);
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
		cltGameMsgResponse_GoguInfo clinfo(siVillageUnique, leftsecond, mode);
		cltMsg clMsg(GAMEMSG_RESPONSE_GOGUINFO, sizeof(clinfo), (char*)&clinfo);
		pclClient->pclCM->SendAllPersonHomeMsg((char*)&clMsg, siVillageUnique);
	}


	return true;
}

// ���� ������� �����.
void cltEventGogu::MakeSoldier()
{
	SI32 i, j, k;

	POINT point[3] = {	42, 114,
						40, 71,
						36, 36};

	POINT center = { 115, 101};
	
	// ������� �ľ��Ѵ�. 200���� �Ѱܼ��� �ȵȴ�. 
	if(siTotalSolNumber >= 200)return ;


	for(i = 0;i < MAX_GOGU_SOL_KIND;i++)
	{
		if(siSolKind[i] == 0)continue;

		// ���͸� ��ġ�Ѵ�. 
		cltServer* pclserver = (cltServer*)pclClient;
		for(j = 0;j < siSolNum[i];j++)
		{
			for(k = 0;k < 3;k++)
			{
				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);
				
				SI32 id = pclserver->SetNPCChar(siSolKind[i], VILLAGE_NONE, NULL, siMonsterLevel, 0, point[k].x, point[k].y, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
				if(id)
				{
					((cltCharServer*)pclClient->pclCM->CR[id])->siCharMode = CHARMODE_GOGUMON;
					OrderMove(id, center.x + 15 - rand() % 30, center.y + 15 - rand() % 30, BY_PLAYER);
				}
			}
		}

	}

}

// �������պ� �����. 
void cltEventGogu::MakeTower()
{
	// ĳ����  ������ �����Ѵ�. 
	SI32 kind = KIND_GWANGGAETOMONUMENT;

	// ĳ���� ���� ��ġ�� �����Ѵ�.
	SI32 x	= 115;
	SI32 y	= 101;

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


void cltEventGogu::AddSol(SI32 kind, SI32 num)
{
	SI32 i;

	for(i = 0;i < MAX_GOGU_SOL_KIND;i++)
	{
		if(siSolKind[i] == 0)
		{
			siSolKind[i]	= kind;
			siSolNum[i]		= num;
			return ;
		}
	}
}

//-------------------------------------------
// �¸��� ������ ��ھ������� �����Ѵ�. 
//-------------------------------------------
void cltEventGogu::	RewardWiner()
{

	// ���� �ֹ��� 1���� ��� ��ǰ�� �ش�. 
	SI16 villagerlist[1000];
	SI32 listindex = 0;
	
	cltServer* pclserver = (cltServer*)pclClient;

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
		if(pclchar->pclCI->clBI.siHomeVillage != siVillageUnique)continue;
		// �̺�Ʈ ������ ��ġ�ϰ� �־�� �Ѵ�. 
		if(pclchar->GetMapIndex() != siMapIndex)continue;

		
		SI32 exp = pclchar->pclCI->clIP.GetLevel()  * (30 + siMonsterLevel / 3);
		pclchar->IncreaseExp(exp);
		
		SI32 fameexp = min(50, max(1, exp / 20));
		pclchar->IncreaseFameExp(fameexp);
		
		cltGameMsgResponse_GoguReward clinfo(exp, fameexp, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_GOGUREWARD, sizeof(clinfo), (char*)&clinfo);
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
				if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_GOGU, &rtnvalue) == false)
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
