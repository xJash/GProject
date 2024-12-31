//---------------------------------
// 2004/10/20 ���°�
//---------------------------------

//------------------------------
// CommonLogic
//------------------------------
#include "CommonLogic.h"
#include "Village.h"
#include "Cityhall/Cityhall.h"
#include "../CommonLogic/TextMgr/TextMgr.h"
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char/CharServer/Char-Server.h"
#include "Char/CharManager/CharManager.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-structure.h"
#include "NDataLoader.h"

// �ǹ�
#include "../CommonLogic/Cityhall/Cityhall.h"
#include "../CommonLogic/Bank/Bank-Manager.h"
#include "../CommonLogic/Stock/Stock.h"
#include "../CommonLogic/Market/Market.h"
#include "../CommonLogic/House/House.h"
#include "../CommonLogic/Hunt/Hunt.h"
#include "../CommonLogic/PostOffice/PostOffice.h"
#include "../CommonLogic/HorseMarket/HorseMarket.h"
#include "../CommonLogic/RealEstate/RealEstate.h"
#include "../CommonLogic/SummonMarket/SummonMarket.h"
#include "../CommonLogic/Land/Land.h"
#include "../CommonLogic/Feast/Feast.h"
#include "../CommonLogic/SummonHeroMarket/SummonHeroMarket.h"
#include "../CommonLogic/Mine/Mine.h"
#include "../CommonLogic/Guild/Guild.h"

//---------------------------------
// Server
//---------------------------------
#include "Server.h"

extern cltCommonLogic* pclClient;

//------------------------------------------------------------------------------
// cltVillageManager
//------------------------------------------------------------------------------
cltVillageManager::cltVillageManager(SI32 villagemode )
{
	SI32 i;
 
	pclBankManager				= pclClient->pclBankManager;
	pclStockManager				= pclClient->pclStockManager;
	pclCityHallManager			= pclClient->pclCityHallManager;
	pclMarketManager			= pclClient->pclMarketManager;
	pclHouseManager				= pclClient->pclHouseManager;
	pclHuntManager				= pclClient->pclHuntManager;
	pclPostOfficeManager		= pclClient->pclPostOfficeManager;
	pclHorseMarketManager		= pclClient->pclHorseMarketManager;
	pclRealEstateMarketManager	= pclClient->pclRealEstateMarketManager;
	pclSummonMarketManager		= pclClient->pclSummonMarketManager;
	pclLandManager				= pclClient->pclLandManager;
	pclFeastManager				= pclClient->pclFeastManager;
	pclSummonHeroMarketManager	= pclClient->pclSummonHeroMarketManager;
	pclMineManager				= pclClient->pclMineManager;
	pclGuildManager				= pclClient->pclGuildManager;
	pclNewMarketManager			= pclClient->pclNewMarketManager;	//[����] ���ո���.

	siVillageMode = villagemode;

	bCheckVisitLevelSwitch	= false;

	siInstanceProfitVillageunique = 0 ;
	siTempInstanceProfit = 0 ;
	dwLastInstanceProfit = 0 ;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		pclVillageInfo[i] = NULL;
	}

	// �� ������ ���� ���� �ľ��� ������ �ð�. 
	dwLastEnemyNumCountClock	= 0;
	
	
	// �������� ���� ���� �ʱ�ȭ
	ResetDeclareWar();

	//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� �ʱ�ȭ.]
	BlackWarRecordInit();
}

cltVillageManager::~cltVillageManager()
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			delete pclVillageInfo[i];
			pclVillageInfo[i] = NULL;
		}
	}

}

SI32 cltVillageManager::FindVillageUniqueFromName(TCHAR* pname)
{
	SI32 i;

	if(pname == NULL)return -1;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			if(_tcscmp(pname, pclVillageInfo[i]->szName) == 0 )
			{
				return i;
			}
		}
	}

	return -1;
}

BOOL cltVillageManager::IsAggressiveVillage( SI32 village1, SI32 village2 )
{
	if( village1 <= 0 || village1 >= MAX_VILLAGE_NUMBER ||
		village2 <= 0 || village2 >= MAX_VILLAGE_NUMBER ) return FALSE;

	if( siNowWarVillage[ village1 ] == village2 ||
		siNowWarVillage[ village2 ] == village1 ) return TRUE;

	return FALSE;
}


// ���� ������ �����Ѵ�.
BOOL cltVillageManager::DeleteVillage()
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			delete pclVillageInfo[i];
			pclVillageInfo[i] = NULL;
		}
	}
	return TRUE;
}


// unique���� ������ �߰��Ѵ�. 
BOOL cltVillageManager::AddVillage(SI32 siunique, TCHAR * pname, SI32 villageposx, SI32 villageposy, SI32 mapindex, SI32 season, bool bfarm, bool biron )
{

	if(pname == NULL)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("Not Proper Village Name.(NULL)"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return FALSE;
	}
	
	if(pclVillageInfo[siunique] == NULL)
	{
		pclVillageInfo[siunique] = new cltVillageInfo(this, siVillageMode, siunique, 0,  pname, villageposx, villageposy, mapindex, season, bfarm, biron);
	}
	else
	{
		MsgBox(TEXT("AddVillage()"), TEXT("fd972jf:%d"), siunique);
	}

	return TRUE;
}

// ��� ������ �����Ѵ�. 
void cltVillageManager::DelAllVillage()
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i] == NULL)continue;

		delete pclVillageInfo[i];
		pclVillageInfo[i] = NULL;
	}

}


BOOL cltVillageManager::Action()
{
	SI32 i;
	
	//-------------------------------------------------
	// ���� ���θ� �ľ��Ѵ�. 
	//-------------------------------------------------
	// ���Ӽ����� ���Ѵ�. 
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		// ���� ���ͱ��� �״´�. 10�а���
		if ( TABS(pclClient->CurrentClock - dwLastInstanceProfit ) > 600000 )
		{
			dwLastInstanceProfit = pclClient->CurrentClock ;

			// ���� ���ͱ��� db�� �����Ѵ�.
			if(siTempInstanceProfit)
			{

				sDBRequest_Change_InstanceProfit sendMsg( siTempInstanceProfit,false);
				((cltServer *)pclClient)->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );

				// ������ ���� �ʱ�ȭ �Ѵ�. 
				siTempInstanceProfit = 0;
			}
		}

		if(TABS(pclClient->CurrentClock - dwLastEnemyNumCountClock) > 3000)
		{
			dwLastEnemyNumCountClock = pclClient->CurrentClock; 
			
			for(i = 1;i < MAX_VILLAGE_NUMBER;i++)
			{
				//---------------------------------------
				// ��� ������ ���� ���� �ʱ�ȭ�Ѵ�. 
				//---------------------------------------
				if(pclVillageInfo[i])
				{
					pclVillageInfo[i]->siEnemyNum			= 0;
					pclVillageInfo[i]->siPersonalShopNum	= 0;
				}
			}
			
			
			SI32 id;
			
			SI32 index			   = 0;
			cltCharServer* pclchar = NULL;
			while(id = pclClient->pclCM->GetCharOrder(index))
			{
				index++;
				
				pclchar = (cltCharServer* )pclClient->pclCM->CR[id];
			
				SI32 mapindex = pclchar->GetMapIndex();

				if(mapindex <= 0)continue;
				if(mapindex >= MAX_VILLAGE_NUMBER)continue;

				// �������� ���λ��� ���� �ľ�. 
				if(pclchar->bPersonalShopSwitch)
				{
					if(pclVillageInfo[mapindex])
					{
						pclVillageInfo[mapindex]->siPersonalShopNum++;
					}
				}
			}

		}

		if(pclClient->GetFrame() % 1000 == 0)
		{
			//-----------------------------------------------
			// ������ �湮�� ����  �ٰŷ� ���� ������ ���Ѵ�.
			//-----------------------------------------------
			CalcVisitLevel();
		}

	}
	
	for(i = 1;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			pclVillageInfo[i]->Action();
		}
	}

	return TRUE;
}


// ���� �ְ��� �����Ѵ�. 
void cltVillageManager::SetCurrentStockPrice(SI32 villageunique, GMONEY price)
{
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)	return;

	if(pclVillageInfo[villageunique])
	{
		pclVillageInfo[villageunique]->SetCurrentStockPrice(price);
	}
}


//Person�� villageunique�� �ִ� �������� Ȯ���Ѵ�. 
BOOL cltVillageManager::IsMostBeholder(SI32 villageunique, SI32 personid)
{
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)	return FALSE;

	return pclVillageInfo[villageunique]->IsMostBeholder(personid);
}


// ������ �̸��� ���´�. 
TCHAR* cltVillageManager::GetName(SI32 villageunique)
{
	//if(villageunique <= 0)return NULL;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return NULL;
	if(pclVillageInfo[villageunique] == NULL)return NULL;

	return pclVillageInfo[villageunique]->szName;
}

// ������ �̸��� �ٰŷ� ���ε����� ã�´�. 
SI32 cltVillageManager::GetMapIndexFromName(TCHAR* name)
{
	SI32 villageunique = FindVillageUniqueFromName(name);
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return -1;

	return villageunique;
	//return pclVillageInfo[villageunique]->MapIndex;
}

// ������ ������ ã�´�. 
SI32 cltVillageManager::FindRandVillage()
{
	SI32 i;
	SI32 villagelist[MAX_VILLAGE_NUMBER];
	SI32 villagelistindex = 0;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i] == NULL)continue;

		villagelist[villagelistindex] = pclVillageInfo[i]->siVillageUnique;
		villagelistindex++;
	}

	if(villagelistindex)
	{
		return villagelist[rand() % villagelistindex];
	}

	return 0;
}

//====================================
// ��Ȳ�� 
//====================================
// �� ������ ��Ȳ���� �ִ� Life�� ���´�.
SI32 cltVillageManager::GetMaxLifeOfGodInVillage(SI32 villageunique)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 villagegodcharunique;

	if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
	{
		return ((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clPB.GetMaxLife();
	}
	
	return 0;
}
// �� ������ ��Ȳ���� Life�� �����Ѵ�.
BOOL cltVillageManager::SetLifeOfGodInVillage(SI32 villageunique, SI32 life)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 villagegodcharunique;

	if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->SetLife(life);
		return TRUE;
	}

	return FALSE;
}

// �� ������ ��Ȳ���� Mana�� �����Ѵ�.
BOOL cltVillageManager::SetManaOfGodInVillage(SI32 villageunique, SI32 mana)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 villagegodcharunique;

	if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->SetMana(mana);
		return TRUE;

	}

	return FALSE;
}

// �� ������ ��Ȳ���� Capa�� �����Ѵ�.
BOOL cltVillageManager::SetCapaOfGodInVillage(SI32 villageunique, SI32 capa)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 villagegodcharunique;

	if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa = capa;
		return TRUE;
	}

	return FALSE;
}

BOOL cltVillageManager::AdjustCapaOfGodInVillage(SI32 villageunique, SI32 adjustcapa)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 villagegodcharunique;

	// ��Ȳ���� ����������.
	if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa += adjustcapa;
		if( ((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa < 100 )
			((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa = 100;
		else if(((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa > MAX_CHARACTER_LEVEL * 2 + 100)
			((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.clGodInfo.siCapa = MAX_CHARACTER_LEVEL * 2 + 100;

		cltStrInfo *pStrInfo = ((cltServer*)pclClient)->GetStrInfo( villageunique,RANKTYPE_CITYHALL );

		//��Ȳ���� ����������.�ϴ� ����
		/*pStrInfo->clCityhallStrInfo.siSymbolCapa = pStrInfo->clCityhallStrInfo.siSymbolCapa-2;*/

	}

	return FALSE;
}


// ������ ��Ȳ���� �ٲ۴�. (villageunique ���� villagegodkind �� �������� �̹� �˻��߾�� �Ѵ�.)
BOOL cltVillageManager::ChangeVillageGod(SI32 villageunique, SI32 villagegodkind)
{
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)	return FALSE;

	// �ش� ������ �����ϰ�
	if(pclVillageInfo[villageunique])
	{
		// �ش� ������ ��Ȳ���� �����Ұ�� 
		SI32 villagegodcharunique;
		
		if(IsThereVillageGod(villageunique, &villagegodcharunique) == TRUE)
		{
			// �� �������� ������ �����Ѵ�. 
			pclClient->pclCM->CR[villagegodcharunique]->DeleteInCell();
			pclClient->pclCM->DeleteChar( villagegodcharunique );
			
		}

		cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
		if(pclinfo == NULL)return FALSE;

		//=========================
		//�缳���Ǿ���ϴ� ������
		//=========================
		// ���� ���ο� ��Ȳ���� �����Ѵ�.
		pclinfo->clCityhallStrInfo.siSymbolKind  = villagegodkind;
		pclinfo->clCityhallStrInfo.siSymbolCapa = 100;

		pclinfo->clCityhallStrInfo.siSymbolLife = 0;
		pclinfo->clCityhallStrInfo.siSymbolMana = 0;
		
		// ������ CharUnique ������ �����.
		pclVillageInfo[villageunique]->siVillageGodCharUnique	= 0;

		// ���ο� ��Ȳ���� ������Ų��.
		pclVillageInfo[villageunique]->CreateVillageGod();
		
	}

	return FALSE;
}

// ��� ������ ��Ȳ���� ���¸� �����Ѵ�.
void cltVillageManager::SetAllVillageGodtoDB()
{
	// �ش� ������ �����ϸ� �� ������ ��Ȳ�� ���¸� �����Ѵ�.
	for(int i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			pclVillageInfo[i]->SetVillageGodtoDB();
		}
	}

}



// �ش� ������ VillageGod�� �����ϴ��� 
BOOL cltVillageManager::IsThereVillageGod(SI32 villageunique, SI32 *siGodCharUnique)
{
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)	return FALSE;

	// �ش� ������ �����ϰ�
	if(pclVillageInfo[villageunique])
	{
		// �ش� ������ God Unique ID�� ���´�.
		SI32 villagegodcharunique = pclVillageInfo[villageunique]->siVillageGodCharUnique;
		// �ش� ������ ��Ȳ���� ���� ��ȿ�ϴٸ� �����Ѵ�.
		if(((cltServer*)pclClient)->pclCM->IsValidID(villagegodcharunique) == TRUE )
		{

			// �ش� ������ ������ ���ͼ� ��Ȳ���� �����Ǿ� ������ 
			cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
			if(pclinfo && pclinfo->clCityhallStrInfo.siSymbolKind >0)
			{
				// �ش� �����Ͱ� �ش� ������ VillageGod ���� �˻��Ѵ�.
				if( ((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->clIdentity.siIdentity  == IDENTITY_VILLAGEGOD &&
				    ((cltServer*)pclClient)->pclCM->CR[ villagegodcharunique ]->pclCI->clBI.siHomeVillage	  == villageunique	)
				{
					*siGodCharUnique = villagegodcharunique;
					return TRUE;
				}
			}
		}
	}

	*siGodCharUnique = 0;
	return FALSE;

}
//====================================
// ���� 
//====================================
// �� ������ ������ �ִ� Life�� ���´�.
SI32 cltVillageManager::GetMaxLifeOfCastleInVillage(SI32 villageunique)
{

	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 castlecharunique;

	if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
	{
		return ((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clPB.GetMaxLife();
	}

	return 0;
}
// �� ������ ������ Life�� �����Ѵ�.
BOOL cltVillageManager::SetLifeOfCastleInVillage(SI32 villageunique, SI32 life)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 castlecharunique;

	if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->SetLife(life);
		return TRUE;
	}

	return FALSE;
}


// �� ������ ������ Mana�� �����Ѵ�.
BOOL cltVillageManager::SetManaOfCastleInVillage(SI32 villageunique, SI32 mana)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 castlecharunique;

	if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->SetMana(mana);
		return TRUE;
	}

	return FALSE;
}
// �� ������ ������ Capa�� �����Ѵ�.
BOOL cltVillageManager::SetCapaOfCastleInVillage(SI32 villageunique, SI32 capa)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 castlecharunique;

	if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa = capa;
		return TRUE;
	}
	
	return FALSE;
}

// �� ������ ������ Capa�� �����Ѵ�.
BOOL cltVillageManager::AdjustCapaOfCastleInVillage(SI32 villageunique, SI32 adjustcapa)
{
	// �ش� ������ ��Ȳ���� �����Ұ�� 
	SI32 castlecharunique;

	if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
	{
		((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa += adjustcapa;
		if( ((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa < 100 )
			((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa = 100;
		else if(((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa > MAX_CHARACTER_LEVEL * 2 + 100)
			((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.clGodInfo.siCapa = MAX_CHARACTER_LEVEL * 2 + 100;

		return TRUE;
	}

	return FALSE;
}

// ������ ����  �ٲ۴�. (villageunique ����  castlekind �� �������� �̹� �˻��߾�� �Ѵ�.)
BOOL cltVillageManager::ChangeCastle(SI32 villageunique, SI32 castlekind)
{
	// �ش� ������ �����ϰ�
	if(pclVillageInfo[villageunique])
	{
		// �ش� ������ ��Ȳ���� �����Ұ�� 
		SI32 castlecharunique;
		
		if(IsThereCastle(villageunique, &castlecharunique) == TRUE)
		{
			// �� �������� ������ �����Ѵ�. 
			pclClient->pclCM->CR[castlecharunique]->DeleteInCell();
			pclClient->pclCM->DeleteChar( castlecharunique );
		}

		cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
		if(pclinfo == NULL)return FALSE;

		//=========================
		//�缳���Ǿ���ϴ� ������
		//=========================
		// ���� ���ο� ������ �����Ѵ�.
		pclinfo->clCityhallStrInfo.siCastleKind = castlekind;
		pclinfo->clCityhallStrInfo.siCastleLife = 0;
		pclinfo->clCityhallStrInfo.siCastleMana = 0;
		pclinfo->clCityhallStrInfo.siCastleCapa = 100;
		// ������ CharUnique ������ �����.
		pclVillageInfo[villageunique]->siCastleCharUnique	= 0;

		// ���ο� ������ ������Ų��.
		pclVillageInfo[villageunique]->CreateCastle();
		
	}

	return FALSE;
}


// ��� ������ ���� ���¸� �����Ѵ�.
void cltVillageManager::SetAllCastletoDB()
{
	// �ش� ������ �����ϸ� �� ������ ��Ȳ�� ���¸� �����Ѵ�.
	for(int i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			pclVillageInfo[i]->SetCastletoDB();
		}
	}

}



// �ش� ������ ������ �����ϴ��� 
BOOL cltVillageManager::IsThereCastle(SI32 villageunique, SI32 *siCastleUnique)
{
	// �ش� ������ �����ϰ�
	if(pclVillageInfo[villageunique])
	{
		// �ش� ������ God Unique ID�� ���´�.
		SI32 castlecharunique = pclVillageInfo[villageunique]->siCastleCharUnique;
		// �ش� ������ ��Ȳ���� ���� ��ȿ�ϴٸ� �����Ѵ�.
		if(((cltServer*)pclClient)->pclCM->IsValidID(castlecharunique) == TRUE )
		{
			// �ش� ������ ������ ���ͼ� ��Ȳ���� �����Ǿ� ������ 
			cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
			if(pclinfo && pclinfo->clCityhallStrInfo.siCastleKind >0)
			{
				// �ش� �����Ͱ� �ش� ������ VillageGod ���� �˻��Ѵ�.
				if( ((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->clIdentity.siIdentity == IDENTITY_CASTLE &&
					((cltServer*)pclClient)->pclCM->CR[ castlecharunique ]->pclCI->clBI.siHomeVillage	 == villageunique)
				{
					*siCastleUnique = castlecharunique;
					return TRUE;
				}
			}
		}
	}

	*siCastleUnique = 0;
	return FALSE;

}
//====================================

// �־��� ��ǥ�κ��� ����� ������ ã�´�. 
SI32 cltVillageManager::FindNearVillage(SI32 x, SI32 y)
{
	SI32 villageunique = 0;
	SI32 length;
	SI32 minlength = 10000;
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i] == NULL)continue;

		//if(pclVillageInfo[i]->bEnemyCaptureSwitch)continue;

		length = max( TABS(x - pclVillageInfo[i]->PosX), TABS(y - pclVillageInfo[i]->PosY));
		if(length < minlength)
		{
			minlength = length;
			
			villageunique	= i;
		}
	}

	return villageunique;
}

// ���� ������ �ʱ�ȭ�Ѵ�. 
void cltVillageManager::InitWarKillNumber()
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			pclVillageInfo[i]->siWarKillNumber = 0;
			pclVillageInfo[i]->bOsakaWarSwitch = false;
		}
	}

}

// ���� ������ ��Ʈ�Ѵ�. 
void cltVillageManager::WarKillNumberSort(SI16* psiVillageUnique,  SI16* psiVillageWarKillNumber)
{
	SI32 i;
	SI32 index = 0;
	bool bVillageCheckSwitch[MAX_VILLAGE_NUMBER];

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		bVillageCheckSwitch[i] = false;
	}


	while(index < WAR_REWARD_VILLAGE_NUMBER)		// 20������ ����. 
	{
		SI16 maxnum		= 0;
		SI16 maxunique	= 0;
		
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageInfo[i] == NULL)continue;
			
			if(bVillageCheckSwitch[i] == false && pclVillageInfo[i]->siWarKillNumber > maxnum)
			{
				maxnum		= pclVillageInfo[i]->siWarKillNumber;
				maxunique	= i;
			}
		}
		
		if(maxunique)
		{
			psiVillageUnique[index]			= maxunique;
			psiVillageWarKillNumber[index]	= pclVillageInfo[maxunique]->siWarKillNumber;
			
			bVillageCheckSwitch[maxunique] = true;
		}
		index++;
	}
}

void cltVillageManager::WarOsakaWarpSwitch()
{
	SI32 i;
	
	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i] == NULL)continue;
	
		// ���� ������ 1000���� ũ�� ����ī �� �� �ִ�
		if( pclVillageInfo[i]->siWarKillNumber >= 1000)
			pclVillageInfo[i]->bOsakaWarSwitch = true;
	}
}

// ���� ������ �ִ� ����ڸ� ���Ѵ�.
void cltVillageManager::GetCurrentVillageUserNum()
{

	SI32 i;

	//-----------------------------------
	// ������ ���� ����ڼ��� �ʱ�ȭ�Ѵ�. 
	//-----------------------------------
	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i])
		{
			pclVillageInfo[i]->siUserNum = 0;
		}
	}
	
	//-----------------------------------
	// ���� ����ڼ��� �����Ѵ�. 
	//-----------------------------------
	SI32 id;
	
	SI32 index = 0;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;
		
		if(IsPC(pclClient->pclCM->CR[id]->GetCharUnique()) == false)continue;

		SI32 villageunique = pclClient->pclCM->CR[id]->GetCurrentVillageUnique();
		if(villageunique <= 0)continue;
		if(villageunique >= MAX_VILLAGE_NUMBER)continue;
		if(pclVillageInfo[villageunique] == NULL)continue;

		pclVillageInfo[villageunique]->siUserNum++;
	}
}

void cltVillageManager::SetWarResult( SI32 siWinVillage, SI32 siLoseVillage )
{
/*
	int i=0;

	cltVillageVary *pclWinVillVary, *pclLoseVillVary;

	pclWinVillVary = &pclVillageInfo[ siWinVillage ]->clVillageVary;
	pclLoseVillVary = &pclVillageInfo[ siLoseVillage ]->clVillageVary;

	int parent = pclWinVillVary->siParentVillage;

	while( parent ) {

		if( parent == siLoseVillage ) {

			pclWinVillVary->siParentVillage = pclLoseVillVary->siParentVillage;
			pclWinVillVary->siMasterVillage = pclLoseVillVary->siMasterVillage;
		}

		parent = pclVillageInfo[ parent ]->clVillageVary.siParentVillage;

	}

	// �¸��� ������ �й��� ������ �θ� ������ �����Ѵ�
	pclLoseVillVary->siParentVillage = siWinVillage;

	// �й��� ������ �ְ�θ����� �����Ѵ�
	if( pclWinVillVary->siMasterVillage == 0 ) {
		pclLoseVillVary->siMasterVillage = siWinVillage;
	} else {
		pclLoseVillVary->siMasterVillage = pclWinVillVary->siMasterVillage;
	}
*/
}

void cltVillageManager::ResetDeclareWar()
{
#ifdef _SAFE_MEMORY
	siDeclareWarVillage.ZeroMem();
	siNowWarVillage.ZeroMem();
	clDeclareWarDate.ZeroMem();
#else
	ZeroMemory( siDeclareWarVillage, sizeof( siDeclareWarVillage ) );
	ZeroMemory( siNowWarVillage, sizeof( siDeclareWarVillage ) );
	ZeroMemory( clDeclareWarDate, sizeof( clDeclareWarDate ) ); 
#endif
}

BOOL cltVillageManager::GetVillageRelation( SI32 village, SI32 slaveVillage )
{

	SI32 parent = pclVillageInfo[ slaveVillage ]->clVillageVary.siParentVillage;

	while( parent ) {
	
		if( village == parent ) return TRUE;

		parent = pclVillageInfo[ parent ]->clVillageVary.siParentVillage;
	}

	return FALSE;
}

// ��ȿ�� ���� ��� �ֽ��� ���� ���� ������ ã�Ƽ� �����Ѵ�. 
SI32 cltVillageManager::FindNoStockVillage()
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageInfo[i] == NULL)continue;

		cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( i);
		if(pclinfo == NULL)continue;
		if(pclinfo->clCityhallStrInfo.usCurStatus != CITYHALL_BEING_NORMAL ) continue ;

		// �ֽ� ���� ���� ���� ������ ���Ѵ�. 
		if(pclinfo->clCityhallStrInfo.siTotalStockAmount == 0)return i;
	}

	return 0;

}

// ������ �ǹ��� �ִ��� ���θ� ��ȯ�Ѵ�
BOOL cltVillageManager::IsThereStructure( SI32 villageunique, SI32 ranktype )
{
	if( pclVillageInfo[ villageunique ] == NULL ) return FALSE;

	return pclVillageInfo[ villageunique ]->clVillageVary.clStructureInfo.IsThereStructure( ranktype );
}

// ������ �ִ� �ǹ��� ��ġ�� ��ȯ�Ѵ�.
bool cltVillageManager::GetPosFromStrUnique(SI32 villageUnique, SI32 strunique, OUT SI32* xpos, OUT SI32* ypos )
{
	if ( pclVillageInfo[ villageUnique ] == NULL ) return false;

	return pclVillageInfo[ villageUnique ]->clVillageVary.clStructureInfo.GetPosFromStrUnique( strunique, xpos, ypos );
}

// ���� �湮�ڼ��� ���� ������ ���Ѵ�. 
void cltVillageManager::CalcVisitLevel()
{

	if(pclClient->GetFrame() < 80000)return ;			// ���� ���� �ʱ⿡�� ���� ������ ������� �ʴ´�. 
	bCheckVisitLevelSwitch	= true;						// ���� �������� ��ȿ�ϴ�. 

	SI32 i;
	SI32 mindata	= 0;
	SI32 village[MAX_VILLAGE_NUMBER];
	SI32 data[MAX_VILLAGE_NUMBER];
	
	ZeroMemory(village, sizeof(SI32) * MAX_VILLAGE_NUMBER);
	ZeroMemory(data,	sizeof(SI32) * MAX_VILLAGE_NUMBER);

	SI32 id			= 0;
	SI32 index		= 0;
	for(i = 0; i < MAX_VILLAGE_NUMBER; i++)
	{
		if(pclVillageInfo[i] == NULL)continue;

		SortAdd(village, data, &mindata, i, pclVillageInfo[i]->GetVisitNum(), MAX_VILLAGE_NUMBER);
	}

	SI16 villageunique	= 0;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		SI16 villageunique = village[i];

		if(pclVillageInfo[villageunique] == NULL)continue;

		pclVillageInfo[ villageunique ]->SetVisitLevel( (MAX_VILLAGE_NUMBER - i) / 10);
	}

}

// ���� �湮�ڼ��� ���� ������ ���Ѵ�. 
bool cltVillageManager::GetVisitLevel(SI32 villageunique, SI32* plevel)
{
	if(bCheckVisitLevelSwitch == false)return false;

	if(pclVillageInfo[villageunique] == NULL)return false;

	*plevel	= pclVillageInfo[villageunique]->GetVisitLevel();
	
	return true;

}

// ���� ���� ���� ���� ������ �ľ��Ѵ�. 
SI32 cltVillageManager::GetPersonalShopNumber(SI32 villageunique)
{

	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return 0;

	if(pclVillageInfo[villageunique] == NULL)return 0;

	return pclVillageInfo[villageunique]->siPersonalShopNum;
}


// ���Ͽ��� �о ������ ������ �ɴ´�. 
BOOL cltVillageManager::LoadVillage(SI32 gamemode, SI32 servicearea)
{
/*
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	switch( pclClient->siServiceArea )
	{
	case ConstServiceArea_Korea :
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoK.txt") );
		break;
	case ConstServiceArea_China :
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoC.txt") );
		break;
	case ConstServiceArea_Japan : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoJ.txt") );
		break;
	case ConstServiceArea_English : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoE.txt") );
		break;
	case ConstServiceArea_Taiwan : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoT.txt") );
		break;
	case ConstServiceArea_USA  : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/VillageInfoU.txt") );
		break;

	}
*/
	TCHAR	datfilename[25];
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // ����
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  // �߱���
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data/VillageInfoG.txt"));
	}

	NDataLoader	dataloader;
	BOOL bLoadFile = FALSE;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datfilename);		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile(datfilename);							
	}
	
	if (!bLoadFile)
	{
		MsgBox(TEXT("Not LoadFromFile VillageInfo"),TEXT("Error"));
		return FALSE;
	}

	TCHAR province[64] = TEXT(""), townname[64] = TEXT("");
	SI32 vunique = 0, posx = 0, posy = 0, mapinx = 0, season = 0, farm = 0, iron = 0;
	bool bFarm, bIron;

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&vunique,4,		
			NDATA_MBSTRING,	province,64,
			NDATA_MBSTRING,	townname,64,
			NDATA_INT32,	&posx, 4,
			NDATA_INT32,	&posy, 4,
			NDATA_INT32,	&mapinx, 4,
			NDATA_INT32,	&season, 4,
			NDATA_INT32,	&farm, 4,
			NDATA_INT32,	&iron,	4,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData() ) 
		{

			if ( province[ 0 ] != NULL)
			{
				bFarm	= DATA_TO_BOOL(farm) ;
				bIron	= DATA_TO_BOOL(iron) ;

				SI32 villimit;
				if(gamemode == GAMEMODE_MAPEDIT)
				{
					villimit = MAX_VILLAGE_NUMBER;
				}
				else
				{
					villimit = CUR_VILLAGE_LIMIT;
				}

				if(vunique <= villimit)
				{
					AddVillage(vunique, townname, posx,  posy, mapinx, season, bFarm, bIron );
				}

				
			}
		}
	}

	return TRUE;
}

BOOL cltVillageManager::IsVillageAtWar(SI32 villageunique)
{
	if( pclClient->bVillageWarSwitch == false )
		return FALSE;

	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)
		return FALSE;
    
	if( siNowWarVillage[ villageunique ]) 
		return TRUE;

	for( SI32 i = 0; i < MAX_VILLAGE_NUMBER; i++ )
	{
		if( siNowWarVillage[i] == villageunique )
			return TRUE;
	}


	return FALSE;	
}

SI32 cltVillageManager::GetVillageRank( SI32 villageunique )
{
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)
		return 0;
	
	SI32 siTotalVillageScore		= pclVillageInfo[villageunique]->clVillageVary.siTotalVillageScore;
	SI32 siCompareTotalVillageScore = 0;
	SI32 VillaeRank = 1;

	for( SI32 i = 0; i < MAX_VILLAGE_NUMBER; i++)
	{
		if(  i == villageunique ) continue;
		if( pclVillageInfo[i] == NULL) continue;

		siCompareTotalVillageScore = pclVillageInfo[i]->clVillageVary.siTotalVillageScore;

		if( siTotalVillageScore < siCompareTotalVillageScore )
		{
			VillaeRank++;
		}

	}


	return VillaeRank;

}

BOOL cltVillageManager::AdjustAllStrDurInVillage( SI32 villageunique, SI32 adjustDur,SI32 lowest = 0)
{
	 
	cltStrInfo* pclStrinfo = NULL;

	// ������ �ִٸ�
					
	pclStrinfo = 	pclBankManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}
		
		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_BANK, TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}


	// ������ �ִٸ�
	pclStrinfo = 	pclStockManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}

		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_STOCK, TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}


	// ������ �ִٸ�
	pclStrinfo = 	pclMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_MARKET, TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//��������  �ִٸ�
	pclStrinfo = 	pclHuntManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_HUNT,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//���� �ִٸ�
	pclStrinfo = 	pclHouseManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_HOUSE,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//��û �ִٸ�
	pclStrinfo = 	pclCityHallManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_CITYHALL,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//��ü�� �ִٸ�
	pclStrinfo = 	pclPostOfficeManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_POSTOFFICE,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//�纹�� �ִٸ�
	pclStrinfo = 	pclHorseMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_HORSEMARKET,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//�����ִٸ�
	pclStrinfo = 	pclRealEstateMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_REALESTATEMARKET,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	//��ȯ���ŷ��� �ִٸ�
	pclStrinfo = 	pclSummonMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}

		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_SUMMONMARKET,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = 	pclLandManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_LAND,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = 	pclFeastManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_FEAST,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = 	pclSummonHeroMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_SUMMONHEROMARKET,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = 	pclMineManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{		
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_MINE,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = 	pclGuildManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{		
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_GUILD,TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}

	// �ִٸ�
	pclStrinfo = pclNewMarketManager->GetStrInfo(villageunique);

	if( pclStrinfo != NULL )
	{		
		SI32 TempDur = adjustDur;

		if( pclStrinfo->clCommonInfo.siStrDura + TempDur < lowest )
		{
			TempDur = lowest - pclStrinfo->clCommonInfo.siStrDura;
		}


		sDBRequest_ChangeStrDura sendMsg( villageunique, RANKTYPE_NEWMARKET, TempDur );
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );
	}


	return TRUE;
}

void cltVillageManager::FindLowTotalVillageScore( SI32* VillageUnique )
{
	SI32 totalVillageScore[MAX_VILLAGE_NUMBER] = { 0, };
	SI32 villageUnique[MAX_VILLAGE_NUMBER] = { 0, };

	SI32 i;
	SI32 index = 0;

	SI32 tempbuf[ MAX_VILLAGE_NUMBER ];

	for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		tempbuf[ i ] = i;

		if( pclVillageInfo[i] == NULL )
			continue;
		
		totalVillageScore[i] = pclVillageInfo[i]->clVillageVary.siTotalVillageScore;
	}

	for( SI32 vill = 0; vill < MAX_VILLAGE_NUMBER - 1; vill++ )
	{
		if( pclVillageInfo[vill] == NULL )
			continue;

		for(i = vill + 1; i < MAX_VILLAGE_NUMBER; i++)
		{
			if( pclVillageInfo[i] == NULL )
				continue;

			int cmpindex1 = tempbuf[ vill ];
			int cmpindex2 = tempbuf[ i ];

			if(totalVillageScore[cmpindex1] > totalVillageScore[cmpindex2])
			{
				int temp = tempbuf[ vill ];
				tempbuf[ vill ] = tempbuf[ i ];
				tempbuf[ i ] = temp;
			}
		}
	}

	for(i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		if( pclVillageInfo[ tempbuf[i] ]== NULL)
			continue;
		villageUnique[ index ] = tempbuf[ i ];
		index++;
	}

	for( i = 0; i < 5; ++i )
	{
		VillageUnique[i] = villageUnique[i];
	}
}
