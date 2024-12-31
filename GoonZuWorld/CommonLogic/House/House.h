//---------------------------------
// 2003/6/26 ���°�
//---------------------------------
#ifndef _HOUSE_H
#define _HOUSE_H

#include <Directives.h>

#include "..\StructureClass\StructureClass.h"
#include "..\..\Server\Time\MyTime.h"

#include "..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "../../common/Horse/Horse.h"

#include <CommonHeader.h>
#include <PersonInfo.h>

#define MAX_HOUSE_TAB_NUMBER							5

// ������ â��(����) ������ �켱 �ѱ��� 150���� �ø��� ������ ������ ���� ��纯���Ѵ�
#ifdef _KOREA
	#define MAX_HOUSEUNIT_NUMBER							150		// �� ������ ������ ����
#else
	#define MAX_HOUSEUNIT_NUMBER							100		// �� ������ ������ ����
#endif

#define MAX_HOUSEUNIT_HORSENUMBER						5		// �� ������ ���� �־�Ѽ� �ִ� ����
#define MAX_HOUSEUNIT_SUMMONNUMBER						5		// �� ������ ��ȯ���� �־�Ѽ� �ִ� ����
#define MAX_APPLY_PER_HOUSE								50		// ���� ���� ��û���� ��. (�� ������. ) 
#define MAX_RENT_PERIOD_YEAR							2		// �ִ� �Ӵ� ���� ���.

#define LEVELLIMIT_USE_HOUSE							20		// ���� ����� �����ϰ� �ϴ� �ּ� ����.

#define MIN_HOUSE_RENT_FEE								10000	// ���� �Ӵ�� ��������. 	
#define MAX_HOUSE_RENT_FEE								200000	// ���� �Ӵ�� �ְ� ����. 

#define HOUSEUNIT_CREATESTABLE_USEITEMNUM				1		// ������ ���µ�, ���Ǵ� �̿�� ����
#define HOUSEUNIT_CREATESTABLE_NEEDMONEY				1000	// ������ ���µ�, �ʿ��� �� ( * siNPCPriceRate )
#define HOUSEUNIT_CREATEUSEDGOODSBUILDING_USEITEMNUM	2		// ������ ���µ�, ���Ǵ� �̿�� ����

#define MAX_RENT_COUNT									3		// �Ӵ��� �� �ִ� �ִ� ��

class cltTaxPaymentListDlg;

//----------------------------------------
// �Ӵ��û Ŭ���� 
//----------------------------------------
class cltRequestRent{
public:
	SI32 siPersonID;		// �Ӵ� ������� PersonID
	SI32 siVillageUnique;	// ������ ��ġ�� ������ VillageUnique
	SI32 siSlot;			// �Ӵ��� �� ������ ����. 

	cltRequestRent(SI32 personid, SI32 villageunique, SI32 slot)
	{
		siPersonID		= personid;
		siVillageUnique	= villageunique;
		siSlot			= slot;
	}

};

//----------------------------------------
// �ڽ��� â�� ����
//----------------------------------------
class cltMyHouseInfo{
public:
	SI32  m_siIndex;						// â�� �ε���
	TCHAR m_szName[MAX_PLAYER_NAME];		// â�� �̸�
	cltRentContract m_clRentContract;		// ��� ������

	cltMyHouseInfo()
	{
		ZeroMemory(this, sizeof(cltMyHouseInfo));
	}

	cltMyHouseInfo(SI32 siIndex , TCHAR* pszName,cltRentContract* pclRentContract)
	{
		m_siIndex = siIndex;
		_tcscpy(m_szName, pszName);
		m_clRentContract.Set(pclRentContract);
	}

	void Set(const cltMyHouseInfo* pclMyHouseInfo)
	{
		m_siIndex = pclMyHouseInfo->m_siIndex;
		_tcscpy(m_szName, pclMyHouseInfo->m_szName);
		m_clRentContract.Set(&pclMyHouseInfo->m_clRentContract);
	}
};

//------------------------------------
// ��������� ����. 
//------------------------------------
class cltRentApplyer{
public:
	cltSimplePerson	clPerson;
	cltRentContract clContract;

	cltRentApplyer(){}
	
	cltRentApplyer(const cltSimplePerson* pclperson, const cltRentContract* pclcontract)
	{
		clPerson.Set(pclperson);
		clContract.Set(pclcontract);
	}

	void Set(const cltRentApplyer* pclapplyer)
	{
		clPerson.Set(&pclapplyer->clPerson);
		clContract.Set(&pclapplyer->clContract);
	}

	void Set(const cltSimplePerson* pclperson, const cltRentContract* pclcontract)
	{
		clPerson.Set(pclperson);
		clContract.Set(pclcontract);
	}

	void Init()
	{
		clPerson.Init();
		clContract.Init();

	}

};


//-------------------------------------
// �Ӵ� ��� ������ �����ϱ� ���� ��Ŷ. 
//--------------------------------------
class cltRentContractPacket{
public:
	SI32 siVillageUnique;
	cltRentContract clRentContract;

	cltRentContractPacket(SI32 villageunique, const cltRentContract* pclcontract)
	{
		siVillageUnique = villageunique;
		clRentContract.Set(pclcontract);
	}
};


//-----------------------------------------
// ���� ����� ������ ������ ���� ��Ŷ. 
//-----------------------------------------
class cltHouseApplyerPacket{
public:
	SI32			siIndex;
	cltRentApplyer clHouseApplyer;

	cltHouseApplyerPacket(SI32 index, const cltRentApplyer* pclapplyer)
	{
		siIndex = index;
		clHouseApplyer.Set(pclapplyer);
	}
};

//--------------------------------------
// ���������� â�� ����. 
//--------------------------------------
#define MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER	30
class cltHouseUnitStorageInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER>		clItem;
	NSafeTArray<cltHorse, MAX_HOUSEUNIT_HORSENUMBER>			clHorse;
	NSafeTArray<bool, MAX_HOUSEUNIT_HORSENUMBER>				bCreatedHouseUnitStable;

//	NSafeTArray<cltSummon, MAX_HOUSEUNIT_SUMMONNUMBER>			clSummon;
//	NSafeTArray<SI16, MAX_HOUSEUNIT_SUMMONNUMBER>				siHouseUnitSummonBuildingLevel;
#else
	cltItem				clItem[MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER];				// â�� ����� ������ ���� ����. 
	cltHorse			clHorse[ MAX_HOUSEUNIT_HORSENUMBER ];					// â�� �� �ִ� ���� ���� ����
	bool				bCreatedHouseUnitStable[ MAX_HOUSEUNIT_HORSENUMBER ];	// â�� �������� ������� �ִ����� ���� ���� ( �������� ������� �־��, ���� ���� �� �ִ�. )
	
//	cltSummon			clSummon[ MAX_HOUSEUNIT_SUMMONNUMBER ];							// â�� �� �ִ� ��ȯ���� ���� ����
//	SI16				siHouseUnitSummonBuildingLevel[ MAX_HOUSEUNIT_SUMMONNUMBER ];	// ��ȯ�� ���� ����( �ʱⰪ 0 )
#endif
	
	bool				bCreatedHouseUnitUsedGoodsBuilding;						// â�� ������ ������� �ִ����� ���� ����
	
	
	
	cltHouseUnitStorageInfo(){};
#ifdef _SAFE_MEMORY
	void Set(cltHouseUnitStorageInfo* pclinfo)
#else
	void Set(const cltHouseUnitStorageInfo* pclinfo)
#endif
	{
		SI32 i;

		for( i = 0; i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++i )
		{
			clItem[i].Set( &pclinfo->clItem[i] );
		}

		for ( i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
		{
			clHorse[i].Set( (cltHorse*)&pclinfo->clHorse[i] );
			bCreatedHouseUnitStable[i] = pclinfo->bCreatedHouseUnitStable[i];
		}

		/*for ( i = 0; i < MAX_HOUSEUNIT_SUMMONNUMBER; ++i )
		{
			clSummon[i].Set( (cltSummon *)&pclinfo->clSummon[i] );
			siHouseUnitSummonBuildingLevel[i] = pclinfo->siHouseUnitSummonBuildingLevel[i];
		}*/
		

		bCreatedHouseUnitUsedGoodsBuilding = pclinfo->bCreatedHouseUnitUsedGoodsBuilding;
	}

	void Init()
	{
		SI32 i;

		for(i = 0;i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER;i++)
		{
			clItem[i].Init();
		}

		for ( i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
		{
			clHorse[ i ].Init();
			bCreatedHouseUnitStable[ i ] = false;
		}

		/*for ( i = 0; i < MAX_HOUSEUNIT_SUMMONNUMBER; ++i )
		{
			clSummon[ i ].Init();			
			siHouseUnitSummonBuildingLevel[ i ] = 0;
		}*/

		bCreatedHouseUnitUsedGoodsBuilding = false;
	}

	BOOL IsItemRemaind() // �����ȿ� �������� �����ֳ� üũ
	{
		SI32 i;
		for(i = 0; i< MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; i++ )
		{
			if(clItem[i].siUnique > 0)
				return TRUE;
		}
		return FALSE;		
	}
	BOOL IsHorseRemaind()
	{
		SI32 i;
		for ( i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
		{
			if(clHorse[ i ].siHorseUnique > 0)
				return TRUE;
		}
		return FALSE;
	}

	BOOL IsSummonRemaind()
	{
		/*SI32 i;
		for ( i = 0; i < MAX_HOUSEUNIT_SUMMONNUMBER; ++i )
		{
			if(clSummon[ i ].siUnique > 0)
				return TRUE;
		}*/
		return FALSE;
	}
	// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
	bool CanAddStg(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos);

	// �������� â�� �ִ´�.
	void SetItemStg(SI32 stgpos, cltItem* pclitem)
	{
		clItem[stgpos].Set(pclitem);
	}

	// â�� �������� �����͸� ���Ѵ�. 
	cltItem* GetStgItemPointer(SI32 stgpos)
	{
		return &clItem[stgpos];
	}
	
	// â�� �ִ� �������� ��ġ�� ���Ѵ�.
	SI16 GetStgExistItemPos( SI16 ItemUnique, SI16 ItemNum );

	// ���� �߰��� �� �ִ��� Ȯ���Ѵ�.
	bool CanAddHorse( SI16 *pHorsePos );
	
	// ���� �� ��ġ�� �ִ��� üũ�Ѵ�.
	bool IsHorseExist( SI16 HorsePos );

	// ���� â�� �ִ´�.
	bool SetHorseStg( SI16 HorsePos, cltHorse *pclHorse )
	{
		if ( bCreatedHouseUnitStable[ HorsePos ] )
		{
			clHorse[ HorsePos ].Set( pclHorse );
			return true;
		}

		return false;
	}

	// â�� ���� �����͸� ���Ѵ�. 
	cltHorse* GetStgHorsePointer( SI32 HorsePos )
	{
		return &clHorse[ HorsePos ];
	}
	
};

// ���� ������ �Ѱ� ������ ����. 
#define STGITEMINFO_OPTION_NONE		0	// �ƹ��� �ɼ��� ����. 
#define STGITEMINFO_OPTION_SHOW		1	// ȭ�鿡 ������ ǥ�����ش�.

class cltHouseUnitStgItemInfo{
public:
	SI16 siVillageUnique;
	SI16 siHouseUnitSlot;
	SI08 siIndex;

	SI16 siOption;
	SI16 siChangedNum;

	SI32 siExp;					// ��ǰ ���꿡 ���� ����ġ.

	cltItem clItem;

	cltHouseUnitStgItemInfo(SI16 villageunique, SI16 houseunitslot, SI08 index, SI16 option, SI16 changednum, SI32 exp, cltItem* pclitem)
	{
		siVillageUnique	= villageunique;
		siHouseUnitSlot	= houseunitslot;
		siIndex			= index;

		siOption		= option;
		siChangedNum	= changednum;

		siExp			= exp;
		clItem.Set(pclitem);

	}
};

//--------------------------------------
// ��������Ʈ 
//--------------------------------------
class cltHouseUnit {
public:
	TCHAR			m_szName[MAX_PLAYER_NAME];					// â�� �̸�
	cltSimplePerson clPerson;										// ������. 
	cltRentContract	clContract;										// ü��Ǿ� �ִ� �Ӵ����� ����.
	bool	bSell;													// [����-09.05.25] �Ǹ������� üũ.

	cltHouseUnitStorageInfo clStorageInfo;							// â�� ����.	

	cltHouseUnit(){}
	~cltHouseUnit(){}

#ifdef _SAFE_MEMORY
	void Set(cltHouseUnit* punit)
#else
	void Set(const cltHouseUnit* punit)
#endif
	{
		if(punit == NULL)return ;

		clPerson.Set(&punit->clPerson);
		clContract.Set(&punit->clContract);
		clStorageInfo.Set(&punit->clStorageInfo);
		bSell = punit->bSell;
		StringCchCopy(m_szName , MAX_PLAYER_NAME, punit->m_szName);
	}

	void Init()
	{
		clPerson.Init();
		clContract.Init();
		clStorageInfo.Init();
		bSell = false;
	}

	SI32 GetItemNum()
	{
		int ret = 0;

		for( int i = 0; i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; i++ )
		{
			if( clStorageInfo.clItem[ i ].siUnique != 0 ) ret++;
		}

		return ret;
	}

	SI32 GetStableNum()
	{

		int ret = 0;

		for( int i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
		{
			if( clStorageInfo.bCreatedHouseUnitStable[ i ] == TRUE ) ret++;
		}

		return ret;
	}

	SI32 GetHorseNum()
	{
		int ret = 0;
		for( int i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
		{
			if( clStorageInfo.clHorse[ i ].siHorseUnique ) ret++;
		}

		return ret;
	}

};

//--------------------------------------
// �� �������� �����ϴ� ������ü 
//--------------------------------------
class cltHouse : public cltStructureBasic{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHouseUnit, MAX_HOUSEUNIT_NUMBER>		clUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_HOUSE>	clApply;
#else
	cltHouseUnit	clUnit[MAX_HOUSEUNIT_NUMBER];

	cltRentApplyer	clApply[MAX_APPLY_PER_HOUSE];
#endif

	cltHouse(SI32 sivillageunique);
	~cltHouse();

	// ������ ��������� �����Ѵ�. 
	BOOL SetRentContract(const cltRentContract* pclcontract )
	{
		clStrInfo.clHouseStrInfo.clRentContract.Set(pclcontract);
		return TRUE;
	}

	void SetHouseUnit(SI32 index, cltHouseUnit* pclunit)
	{
		if(index < 0 || index >= MAX_HOUSEUNIT_NUMBER)
		{
			SI32 a = 0;
			return ;
		}

		clUnit[index].Set(pclunit);
	}

	cltHouseUnit* GetHouseUnit(SI32 index)
	{
		return &clUnit[index];
	}

	void SetHouseApplyer(SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract)
	{
		clApply[index].Set(pclapplyer, pclcontract);
	}
	cltRentApplyer* GetHouseApplyer(SI32 index)
	{
		return &clApply[index];
	}

	// ��� ���� ����ڸ� �����Ѵ�.
	void InitHouseApplyer()
	{
		for(SI32 i = 0;i< MAX_APPLY_PER_HOUSE;i++)
		{
			clApply[i].Init();
		}

	}

	//PersonID�� ������ ������� ������ ���Ѵ�. 
	cltRentApplyer* GetHouseApplyerFromPersonID(SI32 personid);

	// ���� ����������� Ȯ���Ѵ�. 
	BOOL IsSameContract(const cltRentContract* pclcontract);

	// ���� �ĺ��ڷ� ��û�Ѵ�. 
	BOOL AddApplyer(const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract );

	// ���� ��û�ڸ� �����Ѵ�. 
	BOOL DeleteApplyer(SI32 personid);

	// �������� ���θ� Ȯ���Ѵ�. 
	BOOL IsEmpty(SI32 slot);

	// �������� ������ ����Ѵ�.
	BOOL SetRent(SI32 slot, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract);

	// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
	bool IsHouseHost(SI32 personid, SI32 houseunitslot);

	// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
	bool CanAddStg(SI32 houseunitslot, cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos);

	// �������� â�� �ִ´�.
	void SetItemStg(SI32 houseunitslot, SI32 stgpos, cltItem* pclitem);

	// â�� �������� �����͸� ���Ѵ�. 
	cltItem* GetStgItemPointer(SI32 houseunitslot, SI32 stgpos);

	// â���� �����͸� ���Ѵ�. 
	cltHouseUnitStorageInfo* GetStgPointer(SI32 houseunitslot)
	{
		return &clUnit[houseunitslot].clStorageInfo;
	}

	// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
	void GetRentFee();

	
};



//--------------------------------------
// ���� ������. 
//--------------------------------------
class cltHouseManager : public cltStructureMngBasic{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHouseUnit, MAX_HOUSEUNIT_NUMBER>		clClientUnit;
	NSafeTArray<cltRentApplyer, MAX_APPLY_PER_HOUSE>	clClientApplyer;
#else
	cltHouseUnit	clClientUnit[MAX_HOUSEUNIT_NUMBER];
	cltRentApplyer	clClientApplyer[MAX_APPLY_PER_HOUSE];
#endif

	BOOL	UpdateRentContractShowSwitch;				// ��� ������ ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	bool	bUpdateHouseUnitListShowChiefSwitch;		// ��������Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. (�����.) 
	bool	bUpdateHouseUnitListShowSwitch;				// ��������Ʈ�� ȭ�鿡 ������Ʈ �ϵ��� �Ѵ�. 
	BOOL	UpdateHouseVarySwitch;						// ���� ������ ������Ʈ �ǵ��� �Ѵ�. 
	BOOL	UpdateHouseApplyerListShowSwitch;			// ���� ����� ����Ʈ�� ȭ�鿡 ������ �� �ֵ��� �Ѵ�. 


	SI32 CurrentSelectedHouseUnitSlot;
	SI32 CurrentSelectedApplyerSlot;

	SI32 siSelectedHouseUnitNumber;						// ���õ� ���������ǹ�ȣ. 

	HIMAGELIST	hImageList;


	cltHouseManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltHouseManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	// ������ �ż��Ѵ�.
	SI32 CreateHouse(SI32 siunique);

	// Ư�� ������ ��������� �����Ѵ�. 
	BOOL SetRentContract(SI32 villageunique, const cltRentContract* pclcontract);
	
	// Ư�� ���������� Ư�� ���� ������ ���´�.
	cltHouseUnit* GetHouseUnit(SI32 villageunique, SI32 houseunitslot );

	// Ư�� ������ ������ ��������� �־��� ������ǰ� �������� Ȯ���Ѵ�.
	BOOL IsSameContract(SI32 sivillageunique, const cltRentContract*pclcontract);

	// ������û�ڸ� ����Ѵ�. 
	BOOL AddApplyer(SI32 sivillageunique, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract );

	// ���� ��û�ڸ� �����Ѵ�. 
	BOOL DeleteApplyer(SI32 sivillageunique, SI32 personid);

	// ���õ� ���� ����Ʈ�� ������ �����ش�. 
	BOOL ShowSelectedHouseUnitExplain(HWND hDlg, SI32 index);

	// �������� ���θ� Ȯ���Ѵ�. 
	BOOL IsEmpty(SI32 sivillageunique, SI32 slot);

	//PersonID�� ������ ������� ������ ���Ѵ�. 
	cltRentApplyer* GetHouseApplyerFromPersonID(SI32 sivillageunique, SI32 personid);

	// �������� ������ ����Ѵ�.
	BOOL SetRent(SI32 sivillageunique, SI32 slot, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract, const TCHAR* pszHouseName = NULL);
	
	// ������ ȸ���Ѵ�. 
	void RecallHouse(SI32 villageunique, SI32 houseindex);
	
	// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
	bool IsHouseHost(SI32 personid, SI32 villageunique, SI32 houseunitslot);

	// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
	bool CanAddStg(SI32 villageunique, SI32 houseunitslot, cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos);

	// �������� â�� �ִ´�.
	void SetItemStg(SI32 villageunique, SI32 houseunitslot, SI32 stgpos, cltItem* pclitem);
	
	// â�� �������� �����͸� ���Ѵ�. 
	cltItem* GetStgItemPointer(SI32 villageunique, SI32 houseunitslot, SI32 stgpos);

	// â���� �����͸� ���Ѵ�. 
	cltHouseUnitStorageInfo* GetStgPointer(SI32 villageunique, SI32 houseunitslot);
	
	// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
	void Action(cltTime* pcltime, clock_t CurrentClock);
	
	// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
	void RequestHouseUnitList();
	// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
	void RequestHouseUnitListDetail();
	
	// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
	void RequestHouseRentApplyerList();

	// ���� ���ϰ� ó�� �Լ�. 
	void ServerRtnValOperate();


	// ��� ������ �����ش�. 
	BOOL ShowRentContract(HWND hDlg);
	// ���� ����Ʈ ������ �����ش�. 
	BOOL ShowHouseUnitListInChief(HWND hDlg);
	// ���� ���� ������� ����Ʈ�� �����ش�. 
	BOOL ShowHouseApplyerListInChief(HWND hDlg);

	//��� ������ �����ش�. 
	BOOL ShowRentContractInUser(HWND hDlg);

	// ��������Ʈ�� �����.
	BOOL MakeHouseUnitList(HWND hDlg);

	// ��������Ʈ�� �����ش�. 
	BOOL ShowHouseUnitList(HWND hDlg);

};

#endif