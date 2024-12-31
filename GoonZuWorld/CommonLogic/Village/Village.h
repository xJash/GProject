//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _VILLAGE_H
#define _VILLAGE_H

#define VILLAGEWAR_DECLARE		1
#define VILLAGEWAR_DECLARED		2

#define CUR_VILLAGE_LIMIT	88		// ������ ���� VillageUnique ��� �߰��ϴ°�? - ���� ���������� 

#define CUR_GLOBAL_VILLAGE_LIMIT	42		// ������ ���� VillageUnique ��� �߰��ϴ°�? - ���� ���������� 

#ifdef _JAPAN
	#define NEWMARKET_REPAIR_RANKING	20		// [����] ���ո��� �ǹ� ���������� ���� ����.
#else
	#define NEWMARKET_REPAIR_RANKING	5		// [����] ���ո��� �ǹ� ���������� ���� ����.
#endif

#include <windowsx.h>

#include <Directives.h>
#include "..\..\Server\Rank\Rank.h"
#include "..\..\Common\Construction\Construction.h"

#include "NDate.h"

#include <algorithm>
using std::sort;

class cltStockAccount;
class cltBankManager;
class cltStockManager;
class cltCityHallManager;
class cltMarketManager;
class cltHouseManager;
class cltHuntManager;
class cltPostOfficeManager;
class cltHorseMarketManager;
class cltRealEstateMarketManager;
class cltSummonMarketManager;
class cltLandManager;
class cltFeastManager;
class cltSummonHeroMarketManager;
class cltMineManager;
class cltGuildManager;
//class cltNewMarketManager;
class cltNewMarketManager;

class cltVillageManager;
class cltMapManager;

//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ���� ���� ���� Ŭ���� �߰�.]
class BlackWarVillageScore
{
private:
	SI32	m_siVillageUnique;
	SI32	m_siVillageScore;

public:
	BlackWarVillageScore(){ }
	~BlackWarVillageScore(){ }
	BlackWarVillageScore(SI32 _VillageUnique, SI32 _VillageScore) : m_siVillageUnique(_VillageUnique),
																	m_siVillageScore(_VillageScore)
	{ }

	void SetVillageUnique(SI32 _VillageUnique)	 { m_siVillageUnique = _VillageUnique;	}
	SI32 GetVillageUnique(void)					 { return m_siVillageUnique;			}

	void SetVillageScore(SI32 _VillageScore)	 { m_siVillageScore = _VillageScore;	}
	SI32 GetVillageScore(void)					 { return m_siVillageScore;				}

	void AddVillageScore(SI32 _VillageAddScore) { m_siVillageScore += _VillageAddScore;	}
};

// ���� ���� ���� ������ ������ ���Ҷ� ���.
struct compare_Village_Score
{
	bool operator() ( BlackWarVillageScore& _Value1, BlackWarVillageScore& _Value2)
	{
		return _Value1.GetVillageScore() > _Value2.GetVillageScore();
	}					
};

//------------------------------------
// ����Ǿ�� �� ���� ����. 
//------------------------------------
class cltVillageStockPrice{
public:
	SI32 siVillageUnique;	
	GMONEY siCurrentStockPrice;		// ������ ���� �ְ� 
	GMONEY siOldStockPrice;			// ������ ���� �ְ�. 

	cltVillageStockPrice()
	{
		siVillageUnique		= 0;
		siCurrentStockPrice = 0;
		siOldStockPrice		= 0;
	}

	void Set(cltVillageStockPrice* pprice)
	{
		memcpy(this, pprice, sizeof(cltVillageStockPrice));
	}

};


//--------------------------------------------
// ������ �ٽ� ���� 
// �� �������� DB�� ����ǰ� �ȴ�. 
//-------------------------------------------
class cltVillageVary{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSimplePerson, MAX_RANKTYPE_NUMBER>		clRankPerson;
#else
	cltSimplePerson			clRankPerson[MAX_RANKTYPE_NUMBER];
#endif
	cltVillageStockPrice	clVillageStockPrice;						// ���� �ְ� ����. 
	cltVillageInvestInfo	clInvestInfo;								// ���� ���� ���� 

	CConstruction			clStructureInfo;							// �ǹ� ����. 

	SI32					siMasterVillage;							// �ְ�θ� ���� 
	SI32					siParentVillage;							// �θ� ���� 

	SI32					siVillageMark;								// ���� ��ũ �ڵ� 
	
	SI32					siResidentsScore;							// ���� �ֹ� ����
	SI32					siVillageScore;								// ���� ����
	SI32					siTotalVillageScore;						// ���� �� ���� ( siResidentsScore + siVillageScore + siVillageWarScore);
	SI32					siVillageWarKillNumber;						// ���� ���� ������
	SI32					siVillageEventSuccessNumber;				// ���� �̺�Ʈ ����Ƚ��
	SI32					siNewYearEventScore;						// �������� �̺�Ʈ
	//SI32					siVillageWarScore;							// ���� ���������� ��� �Ǵ� ����

	bool					m_bGeneralMeetingSuggest;					//[�߰� : Ȳ���� 2008. 2. 20 => ������ȸ �ߵ� �÷���, ��� ��ɾ�� ���� ����.]

	cltVillageVary()
	{
		siMasterVillage = 0;
		siParentVillage = 0;
		siVillageMark = 0;

		siResidentsScore = 0;
		siVillageScore = 0;
		siTotalVillageScore = 0;		
		siVillageWarKillNumber = 0;
		siVillageEventSuccessNumber = 0;
		siNewYearEventScore =0;

		//siVillageWarScore = 0;
		m_bGeneralMeetingSuggest = 0;
	}
};

//------------------------------------------
// ���� ������ ���� 
//------------------------------------------
class cltVillageInfo{
public:
	cltVillageManager* pclVillageManager;

	SI32 siVillageUnique;	
	DWORD dwAtb;									// �Ӽ��� Ư��. 
	TCHAR szName[MAX_PATH];

	SI32 TitleImageXsize, TitleImageYsize;

	UI08* pTitleBuffer;								// ���� �̸��� ������ ����. 
	UI08* pTitleEncBuffer;

	bool bEnemyCaptureSwitch;						// ������ �̸����� �����ߴ°�. 
	SI16 siEnemyNum;								// ������ ħ���� ���� ���ڸ� ����Ѵ�. 
	SI16 siPersonalShopNum;							// �����ȿ� �ִ� ���� ������ ����. 

	SI32 PosX, PosY;								// �� ������ ���� ������ ��� ��ǥ�� �ִ°� 

	SI16 siWarKillNumber;							// ���￡�� �� ���� �ֹε��� óġ�� ���� ��. 
	SI16 siUserNum;									// �������� ����� ��
	

	DWORD dwLastVillageGodClock;
	DWORD dwLastCastleClock;
	DWORD dwLastAttackedVillageClock;

	SI16 siVillageGodCharUnique;					// ������ ��Ȳ�� ĳ���� Unique
	SI16 siCastleCharUnique;						// ���� ���� ĳ���� ����ũ. 
	SI16 siKingMonumentUnique;							// ���� ��ȣ�� ����ũ

	BOOL bAttackedVillage;

	bool bOsakaWarSwitch;							// ���������� 1000���̻��̸� true

private:	
	SI32 siVisitorNumber;							// �� ������ �湮�� ��. 
	SI32 siVisitLevel;								// �湮�ڼ��� ���� ����. 

public:
	cltVillageVary clVillageVary;					// ���� �Ǿ���� ���� ����. 

	TCHAR	RankAccountID[MAX_RANKTYPE_NUMBER][MAX_PLAYER_NAME];	// ������ �� ����� AccountID


	SI32 siVillageType;								// ������ Ÿ��. 
	SI32 siSeason;									// ���� 
	bool bFarmSwitch;								// ���� ��������  ����. 
	bool bIronSwitch;								// ö���� ��������  ����. 
	bool bUpgradeSwitch;							// ������ ���� ���׷��̵�� ��������
	
	cltVillageInfo(cltVillageManager* pclvillageset, SI32 villagemode, SI32 siunique, DWORD atb, TCHAR* name, SI32 villageposx, SI32 villageposy, SI32 mapindex, SI32 season, bool bfarm, bool biron );
	~cltVillageInfo();

	BOOL  LoadTitle();

	BOOL Action();

	//==========================
	// ��ȣ��
	//==========================
	BOOL CreateVillageKingMonument();

	//==========================
	// ��Ȳ�� 
	//==========================
	// ���� ��Ȳ���� ���¸� DB�� �����ϵ��� �Ѵ�.
	BOOL SetVillageGodtoDB();
	// ��Ȳ���� ���� �����Ѵ�.
	BOOL CreateVillageGod();

	//==========================
	// ���� 
	//==========================
	// ������ ���¸� DB�� �����ϵ��� �Ѵ�.
	BOOL SetCastletoDB();
	// ������ ���� �����Ѵ�.
	BOOL CreateCastle();
	//==========================
	// Ư�� �ü��� ������ �ִ��� ���θ� Ȯ���Ѵ�. 
	BOOL HasStructure(SI32 structureunique);

	// ���� �ְ��� �����Ѵ�. 
	void SetCurrentStockPrice(GMONEY price)
	{
		clVillageVary.clVillageStockPrice.siCurrentStockPrice = price;
	}

	// ���� �ְ��� ���´�. 
	GMONEY GetCurrentStockPrice()const
	{
		return clVillageVary.clVillageStockPrice.siCurrentStockPrice;
	}

	// PersonID�� �ִ� �������� Ȯ���Ѵ�. 
	BOOL IsMostBeholder(SI32 personid);

	// ������ ����Ѵ�.
	void Draw(SI32 dotx, SI32 doty);

public:
	//--------------------------------------------
	// Village-DB.cpp
	//--------------------------------------------
	// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadBankFromDB();
	// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadStockFromDB();
	// DB���� ��� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadCityHallFromDB();
	// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadMarketFromDB();
	// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadHouseFromDB();
	// DB���� ������ ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadHuntFromDB();
	// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�. 
	BOOL LoadPostOfficeFromDB();
	// DB���� �纹�� ������ �о�ͼ� ������Ʈ �Ѵ�.
	BOOL LoadHorseMarketFromDB();
	// �Ű� 
	BOOL LoadRealEstateMarketFromDB();
	// �忹��
	BOOL LoadSummonMarketFromDB();
	// ���� 
	BOOL LoadLandFromDB();
	// ���ڽ� 
	BOOL LoadFeastFromDB();
	// �񺯻� 
	BOOL LoadSummonHeroMarketFromDB();
	// ����
	BOOL LoadMineFromDB();
	// ���
	BOOL LoadGuildFromDB();

	//[����] ���ո���.
	BOOL LoadNewMarketFromDB();	

	void IncVisitNum(SI32 inc)
	{
		siVisitorNumber += inc;
	}
	
	SI32 GetVisitNum()
	{
		return siVisitorNumber;
	}
	void SetVisitLevel(SI32 level)
	{
		siVisitLevel = level;
	}
	SI32 GetVisitLevel()
	{
		return siVisitLevel;
	}

};


class cltVillageManager 
{
public:
	cltBankManager*								pclBankManager;
	cltStockManager*							pclStockManager;
	cltCityHallManager*							pclCityHallManager;
	cltMarketManager*							pclMarketManager;
	cltHouseManager*							pclHouseManager;
	cltHuntManager*								pclHuntManager;
	cltPostOfficeManager*						pclPostOfficeManager;
	cltHorseMarketManager*						pclHorseMarketManager;
	cltRealEstateMarketManager* 				pclRealEstateMarketManager;
	cltSummonMarketManager*						pclSummonMarketManager;
	cltLandManager*								pclLandManager;
	cltFeastManager*							pclFeastManager;
	cltSummonHeroMarketManager*					pclSummonHeroMarketManager;
	cltMineManager*								pclMineManager;
	cltGuildManager*							pclGuildManager;
	//cltNewMarketManager*						pclNewMarketManager;
	cltNewMarketManager*						pclNewMarketManager;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_VILLAGE_NUMBER>		siDeclareWarVillage;						// �������� ������ ����� ����.  
	NSafeTArray<SI32, MAX_VILLAGE_NUMBER>		siNowWarVillage;							// ���� ������ ���� ����. ���� ������ 

	NSafeTArray<NDate, MAX_VILLAGE_NUMBER>		clDeclareWarDate;							// �������� ������ �ð�,�ð�
#else
	SI32										siDeclareWarVillage[ MAX_VILLAGE_NUMBER ];	// �������� ������ ����� ����.  
	SI32										siNowWarVillage[ MAX_VILLAGE_NUMBER ];		// ���� ������ ���� ����. ���� ������ 

	NDate										clDeclareWarDate[ MAX_VILLAGE_NUMBER ];		// �������� ������ �ð�,�ð�
//	cltDate										clLastWarLoseDate[ MAX_VILLAGE_NUMBER ];	// ���������� ���������� �й��� �ð�. �����ϰ� ���������� ��ȣ�ϴ� �뵵�� ����.
#endif

	SI32 siVillageMode;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltVillageInfo*, MAX_VILLAGE_NUMBER>	pclVillageInfo;
#else
	cltVillageInfo* pclVillageInfo[MAX_VILLAGE_NUMBER];
#endif

	DWORD		dwLastEnemyNumCountClock;			// �� ������ ���� ���� �ľ��� ������ �ð�. 


	bool		bCheckVisitLevelSwitch;				// ���� �湮�� ���� ��ȿ�Ѱ� ?

	SI32		siInstanceProfitVillageunique;		// �ν��Ͻ� ���� ���ͱ� ���� ����
	SI64		siTempInstanceProfit;				// �ν��Ͻ� ���� ���ͱ�
	DWORD		dwLastInstanceProfit;				// ���������� �ν��Ͻ� ���ͱ� �� �ð�

#ifdef _SAFE_MEMORY
	NSafeTArray<BlackWarVillageScore, MAX_VILLAGE_NUMBER>		cBlackWarVillageScore;
#else
	BlackWarVillageScore	cBlackWarVillageScore[MAX_VILLAGE_NUMBER];			//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� �ߵ��� �������� ����. ���� �ֹ��� ������ ������ �������.]
#endif

	cltVillageManager(SI32 villagemode);

	~cltVillageManager();

	// unique���� ������ �߰��Ѵ�. 
	BOOL AddVillage(SI32 siunique, TCHAR * pname, SI32 villageposx, SI32 villageposy, SI32 mapindex, SI32 season, bool bfarm, bool biron );

	// ���� ������ �����Ѵ�.
	BOOL DeleteVillage();

	BOOL IsAggressiveVillage( SI32 village1, SI32 village2 );

	SI32 FindVillageUniqueFromName(TCHAR* name);

	BOOL Action();

	// ���� �ְ��� �����Ѵ�. 
	void SetCurrentStockPrice(SI32 villageunique, GMONEY price);
	
	// ������ �̸��� ���´�. 
	TCHAR* GetName(SI32 villageunique);
	
	// ������ �̸��� �ٰŷ� ���ε����� ã�´�. 
	SI32 GetMapIndexFromName(TCHAR* name);

	// ������ ������ ã�´�. 
	SI32 FindRandVillage();

	//-----------------------------------------
	// ��Ȳ�� 
	//-----------------------------------------
	// �� ������ ��Ȳ���� �ִ� Life�� ���´�.
	SI32 GetMaxLifeOfGodInVillage(SI32 villageunique);
	// �� ������ ��Ȳ���� Life�� �����Ѵ�.
	BOOL SetLifeOfGodInVillage(SI32 villageunique, SI32 life);
	// �� ������ ��Ȳ���� Mana�� �����Ѵ�.
	BOOL SetManaOfGodInVillage(SI32 villageunique, SI32 mana);
	// �� ������ ��Ȳ���� Capa�� �����Ѵ�.
	BOOL SetCapaOfGodInVillage(SI32 villageunique, SI32 capa);

	// �� ������ ��Ȳ���� Capa�� �����Ѵ�.
	BOOL AdjustCapaOfGodInVillage(SI32 villageunique, SI32 capa);

	// ������ ��Ȳ���� �ٲ۴�. (villageunique ���� villagegodkind �� �������� �̹� �˻��߾�� �Ѵ�.)
	BOOL ChangeVillageGod(SI32 villageunique, SI32 villagegodkind);
	// ��� ������ ��Ȳ���� ���¸� �����Ѵ�.
	void SetAllVillageGodtoDB();

	// �ش� ������ VillageGod�� �����ϴ��� 
	BOOL IsThereVillageGod(SI32 villageunique,SI32 *siGodCharUnique);

	//-----------------------------------------
	// ���� 
	//-----------------------------------------
	// �� ������ ������ �ִ� Life�� ���´�.
	SI32 GetMaxLifeOfCastleInVillage(SI32 villageunique);
	// �� ������ ������ Life�� �����Ѵ�.
	BOOL SetLifeOfCastleInVillage(SI32 villageunique, SI32 life);
	// �� ������ ������ Mana�� �����Ѵ�.
	BOOL SetManaOfCastleInVillage(SI32 villageunique, SI32 mana);
	// �� ������ ������ Capa�� �����Ѵ�.
	BOOL SetCapaOfCastleInVillage(SI32 villageunique, SI32 capa);

	// �� ������ ������ Capa�� �����Ѵ�.
	BOOL AdjustCapaOfCastleInVillage(SI32 villageunique, SI32 adjustcapa);

	// ������ ����  �ٲ۴�. (villageunique ����  castlekind �� �������� �̹� �˻��߾�� �Ѵ�.)
	BOOL ChangeCastle(SI32 villageunique, SI32 castlekind);

	// ��� ������ ���� ���¸� �����Ѵ�.
	void SetAllCastletoDB();
	
	// �ش� ������ Castle�� �����ϴ��� 
	BOOL IsThereCastle(SI32 villageunique, SI32 *siCastleUnique);
	//-----------------------------------------

public:
	//-----------------------------------------
	// Ŭ���� �ܺο��� ����ϴ� ��� �Լ� 
	//-----------------------------------------

	//Person�� villageunique�� �ִ� �������� Ȯ���Ѵ�. 
	BOOL IsMostBeholder(SI32 villageunique, SI32 personid);

	// �־��� ��ǥ�κ��� ����� ������ ã�´�. 
	SI32 FindNearVillage(SI32 x, SI32 y);
	
	// ���� ������ �ʱ�ȭ�Ѵ�. 
	void InitWarKillNumber();

	// ���� ������ ��Ʈ�Ѵ�. 
	void WarKillNumberSort(SI16* psiVillageUnique,  SI16* psiVillageWarKillNumber);
	void WarOsakaWarpSwitch();

	// ���� ������ �ִ� ����ڸ� ���Ѵ�.
	void GetCurrentVillageUserNum();

	// ������ ���� ����� �����Ѵ� 
	void SetWarResult( SI32 siWinVillage, SI32 siLoseVillage );

	// 
	BOOL GetVillageRelation( SI32 village, SI32 slaveVillage );

	// ��� ������ �������� ���¸� �ʱ�ȭ�Ѵ�
	void ResetDeclareWar();

	
	// ������ Ÿ���� ���Ѵ�. 
	SI32 GetVillateType(SI32 villageunique)
	{
		if(pclVillageInfo[villageunique] == NULL)return false;

		return pclVillageInfo[villageunique]->siVillageType;
	}
	
	// ��ȿ�� �����ΰ�?
	bool IsValidVillage(SI32 villageunique)
	{
		if(villageunique <= 0)return false;
		if(villageunique >= MAX_VILLAGE_NUMBER)return false;

		if(pclVillageInfo[villageunique] == NULL)return false;

		return true;
	}
	
	BOOL IsThereStructure( SI32 villageunique, SI32 ranktype );
	

	// ��ȿ�� ���� ��� �ֽ��� ���� ���� ������ ã�Ƽ� �����Ѵ�. 
	SI32 FindNoStockVillage();

	
	// ���� �湮�ڼ��� ���� ������ ���Ѵ�. 
	void CalcVisitLevel();
	// ���� �湮�ڼ��� ���� ������ ���Ѵ�. 
	bool GetVisitLevel(SI32 villageunique, SI32* plevel);

	// ���� ���� ���� ���� ������ �ľ��Ѵ�. 
	SI32 GetPersonalShopNumber(SI32 villageunique);

	// ��� ������ �����Ѵ�. 
	void DelAllVillage();

	BOOL LoadVillage(SI32 gamemode, SI32 servicearea);
	
	// �ش� ������ ���������� üũ
	BOOL IsVillageAtWar(SI32 villageunique);
	
	// �ش縶���� �������� ������ ���ؿ�
	SI32 GetVillageRank( SI32 villageunique );

	BOOL AdjustAllStrDurInVillage( SI32 villageunique, SI32 adjustDur, SI32 lowest);

	bool GetPosFromStrUnique(SI32 villageUnique, SI32 strunqiue, OUT SI32* xpos, OUT SI32* ypos );

	void FindLowTotalVillageScore( SI32* VillageUnique );

	//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ��� ���� �ʱ�ȭ.]
	void BlackWarRecordInit(void)
	{
#ifdef _SAFE_MEMORY
		cBlackWarVillageScore.ZeroMem();
#else
		ZeroMemory( cBlackWarVillageScore, sizeof( cBlackWarVillageScore ) );
#endif
		for(int Count = 0; Count < MAX_VILLAGE_NUMBER; ++Count)
		{
			cBlackWarVillageScore[Count].SetVillageUnique( Count + 1 );
		}
	}
	//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ������ ���� ���� ����.]
	void BlackWarScoreAdd(SI32 _VillageUnique, SI32 _AddScore)
	{
		if( _VillageUnique <= 0 || _VillageUnique >= MAX_VILLAGE_NUMBER)
			return;
	
		for(int Count = 0; Count < MAX_VILLAGE_NUMBER; ++Count)
		{
			if( cBlackWarVillageScore[Count].GetVillageUnique() == _VillageUnique )
			{
				cBlackWarVillageScore[Count].AddVillageScore(_AddScore);
				break;
			}
		}  
		
		sort( &cBlackWarVillageScore[0], &cBlackWarVillageScore[MAX_VILLAGE_NUMBER-1], compare_Village_Score() );
	}
	//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� ������ ���� ���� ���.]
	SI16 GetBlackWarVillageScore(SI32 _VillageUnique)
	{
		if( _VillageUnique <= 0 || _VillageUnique >= MAX_VILLAGE_NUMBER)
			return 0;

		for(int Count = 0; Count < MAX_VILLAGE_NUMBER; ++Count)
		{
			if( cBlackWarVillageScore[Count].GetVillageUnique() == _VillageUnique )
			{
				return 	cBlackWarVillageScore[Count].GetVillageScore();			
			}
		}

		return 0;
	}
};

#endif
