//---------------------------------
// 2003/5/27 ���°�
//---------------------------------

#include "..\CommonLogic\CommonLogic.h"
#include "Village.h"

// �ǹ�
#include "..\CommonLogic\Cityhall\Cityhall.h"
#include "..\CommonLogic\Bank\Bank-Manager.h"
#include "..\CommonLogic\Stock\Stock.h"
#include "..\CommonLogic\Market\Market.h"
#include "..\CommonLogic\House\House.h"
#include "..\CommonLogic\Hunt\Hunt.h"
#include "..\CommonLogic\PostOffice\PostOffice.h"
#include "..\CommonLogic\HorseMarket\HorseMarket.h"
#include "..\CommonLogic\RealEstate\RealEstate.h"
#include "..\CommonLogic\SummonMarket\SummonMarket.h"
#include "..\CommonLogic\Land\Land.h"
#include "..\CommonLogic\Feast\Feast.h"
#include "..\CommonLogic\SummonHeroMarket\SummonHeroMarket.h"
#include "..\CommonLogic\Mine\Mine.h"
#include "..\CommonLogic\Guild\Guild.h"

extern cltCommonLogic* pclClient;

// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
// �� �Լ��� Ŭ���̾�Ʈ, ���� ���� ���� ���� �ʱ�ȭ�� �ѹ��� �����ϰ� �ȴ�. 
BOOL cltVillageInfo::LoadBankFromDB()
{
	// ������ �����. 
	pclVillageManager->pclBankManager->CreateBank(siVillageUnique);

	return TRUE;
}


// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
BOOL cltVillageInfo::LoadStockFromDB()
{
	// ������ �����
	pclVillageManager->pclStockManager->CreateStock(siVillageUnique);
	return TRUE;
}

// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
BOOL cltVillageInfo::LoadMarketFromDB()
{
	// ���ָ� �����. 
	pclVillageManager->pclMarketManager->CreateMarket(siVillageUnique);
	
	return TRUE;
}

BOOL cltVillageInfo::LoadNewMarketFromDB()
{
	//[����] ���ո����� �����. 
	//pclVillageManager->pclNewMarketManager->CreateNewMarket(siVillageUnique);
	
	pclVillageManager->pclNewMarketManager->CreateNewMarket(siVillageUnique);

	return TRUE;
}

// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
BOOL cltVillageInfo::LoadHouseFromDB()
{
	// ������  �����. 
	pclVillageManager->pclHouseManager->CreateHouse(siVillageUnique);
	
	return TRUE;
}



// DB���� ��� ������ �о�ͼ� ������Ʈ �Ѵ�. 
BOOL cltVillageInfo::LoadCityHallFromDB()
{
	// ����� �����. 
	pclVillageManager->pclCityHallManager->CreateCityHall(siVillageUnique);

	return TRUE;
}

// DB���� ������ ������ �о�ͼ� ������Ʈ �Ѵ�. 
BOOL cltVillageInfo::LoadHuntFromDB()
{
	// �������� �����. 
	pclVillageManager->pclHuntManager->CreateHunt(siVillageUnique);
	
	return TRUE;
}

// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�.
BOOL cltVillageInfo::LoadPostOfficeFromDB()
{
	// ������ �����. 
	pclVillageManager->pclPostOfficeManager->CreatePostOffice(siVillageUnique);
	
	return TRUE;
}

// DB���� �纹�� ������ �о�ͼ� ������Ʈ �Ѵ�.
BOOL cltVillageInfo::LoadHorseMarketFromDB()
{
	// �纹�ø� �����. 
	pclVillageManager->pclHorseMarketManager->CreateHorseMarket( siVillageUnique );

	return TRUE;
}

BOOL cltVillageInfo::LoadRealEstateMarketFromDB()
{
	pclVillageManager->pclRealEstateMarketManager->CreateRealEstateMarket( siVillageUnique );

	return TRUE;
}

BOOL cltVillageInfo::LoadSummonMarketFromDB()
{
	pclVillageManager->pclSummonMarketManager->CreateSummonMarket( siVillageUnique );

	return TRUE;
}


BOOL cltVillageInfo::LoadLandFromDB()
{
	pclVillageManager->pclLandManager->CreateLand( siVillageUnique );

	return TRUE;
}

BOOL cltVillageInfo::LoadFeastFromDB()
{
	pclVillageManager->pclFeastManager->CreateFeast( siVillageUnique );

	return TRUE;
}


BOOL cltVillageInfo::LoadSummonHeroMarketFromDB()
{
	pclVillageManager->pclSummonHeroMarketManager->CreateSummonHeroMarket( siVillageUnique );

	return TRUE;
}

BOOL cltVillageInfo::LoadMineFromDB()
{
	pclVillageManager->pclMineManager->CreateMine( siVillageUnique );

	return TRUE;
}

BOOL cltVillageInfo::LoadGuildFromDB()
{
	pclVillageManager->pclGuildManager->CreateGuild( siVillageUnique );

	return TRUE;
}
