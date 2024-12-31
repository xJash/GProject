#ifndef _MSGTYPEHOUSE_H
#define _MSGTYPEHOUSE_H

#include "House/House.h"

//-------------------------------------------
// â���� �������� �����. 
//-------------------------------------------
class cltGameMsgRequest_MakeItemInStg{
public:
	SI16 siItemUnique;
	SI16 siItemNum;

	SI16 siVillageUnique;
	SI16 siHouseIndex;

	cltGameMsgRequest_MakeItemInStg(SI16 itemunique, SI16 itemnum, SI16 villageunique, SI16 houseindex)
	{
		siItemUnique	= itemunique;
		siItemNum		= itemnum;

		siVillageUnique = villageunique;
		siHouseIndex	= houseindex;
	}

};

//------------------------------------
// ���� â�� �̸� ��
//------------------------------------
class cltGameMsgRequest_ChangeHouseUnitName{
public:
	SI16 m_siVillageUnique;
	SI16 m_siHouseIndex;

	TCHAR m_szHouseName[MAX_PLAYER_NAME];

	cltGameMsgRequest_ChangeHouseUnitName(SI16 villageunique, SI16 houseindex,TCHAR* pszHouseName)
	{
		m_siVillageUnique = villageunique;
		m_siHouseIndex	= houseindex;

		_tcscpy(m_szHouseName,pszHouseName);
	}
};

//------------------------------------
// â�� ������ ����
//------------------------------------
class cltGameMsgResponse_ArrangeHouseItem{
public:
	SI16 m_siVillageUnique;
	SI16 m_siHouseIndex;

	cltGameMsgResponse_ArrangeHouseItem(SI16 villageunique, SI16 houseindex)
	{
		m_siVillageUnique = villageunique;
		m_siHouseIndex	= houseindex;
	}
};

//------------------------------------
// ���� â�� �̸� ����
//------------------------------------
class cltGameMsgResponse_ChangeHouseUnitName{
public:
	SI16 m_siVillageUnique;
	SI16 m_siHouseIndex;

	TCHAR m_szHouseName[MAX_PLAYER_NAME];

	cltGameMsgResponse_ChangeHouseUnitName(SI16 villageunique, SI16 houseindex,TCHAR* pszHouseName)
	{
		m_siVillageUnique = villageunique;
		m_siHouseIndex	= houseindex;

		_tcscpy(m_szHouseName,pszHouseName);
	}
};

//------------------------------------
// ���� ���� ����Ʈ ����Ʈ ����. 
//------------------------------------
class cltGameMsgResponse_MyHouseUnitList{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMyHouseInfo, MAX_RENT_COUNT>		clMyHouseInfo;		
#else
	cltMyHouseInfo	clMyHouseInfo[MAX_RENT_COUNT];						
#endif

};

//------------------------------------
// ���� ����Ʈ ����Ʈ ����. 
//------------------------------------
class cltGameMsgRequest_HouseUnitList{
public:
	SI32 siVillageUnique;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSimplePerson, MAX_HOUSEUNIT_NUMBER>		clPerson;
	NSafeTArray<bool, MAX_HOUSEUNIT_NUMBER>					bSell;		//[����] - �ε��� �ŷ� ��� ���� -  �Ǹ� ���� ������ ���� ���� �߰�.
#else
	cltSimplePerson clPerson[MAX_HOUSEUNIT_NUMBER];						// ������. 
	bool			bSell[MAX_HOUSEUNIT_NUMBER];						// �Ǹ� ���� ������ ���� ���� �߰�.
#endif

	cltGameMsgRequest_HouseUnitList(SI32 villageunique)
	{
		siVillageUnique	= villageunique;
	}
};

//------------------------------------
// ���� ����Ʈ �� ���� ����Ʈ ����. 
//------------------------------------
class cltGameMsgRequest_HouseUnitListDetail{
public:
	SI32 siVillageUnique;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltRentContract, MAX_HOUSEUNIT_NUMBER>		clContract;
#else
	cltRentContract	clContract[MAX_HOUSEUNIT_NUMBER];			// ��� ����. 
#endif

	cltGameMsgRequest_HouseUnitListDetail(SI32 villageunique)
	{
		siVillageUnique	= villageunique;
	}


};


//------------------------------------
// ���� â�� ���� ��û
//------------------------------------
class GameMsgRequest_HouseUnitStgInfo{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	GameMsgRequest_HouseUnitStgInfo(SI32 villageunique, SI32 houseunitslot)
	{
		siVillageUnique = villageunique;
		siHouseUnitSlot	= houseunitslot;
	}
};

//------------------------------------
// ���� â�� ���� ��û ����
//------------------------------------
class GameMsgResponse_HouseUnitStgInfo{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	cltHouseUnitStorageInfo clStgInfo;

	GameMsgResponse_HouseUnitStgInfo(SI32 villageunique, SI32 houseunitslot, cltHouseUnitStorageInfo* pclinfo)
	{
		siVillageUnique = villageunique;
		siHouseUnitSlot	= houseunitslot;
		clStgInfo.Set(pclinfo);

	}

};

class cltGameMsgRequest_HouseCancellationPenaltyMoney
{
public:			
	SI32				siVillageUnique;	// ������ ���� ����ũ. 
	SI32				siHouseIndex;	

	cltGameMsgRequest_HouseCancellationPenaltyMoney(SI32 villageunique, SI32 houseindex) 
	{
		siVillageUnique	= villageunique;
		siHouseIndex	= houseindex;
	}
};


class cltGameMsgResponse_HouseCancellationPenaltyMoney
{
public:
	//SI32				siVillageUnique;	// ������ ���� ����ũ. 
	//SI32				siHouseIndex;	
	GMONEY				siPenaltyMoney;		// ������ �����
	

	cltGameMsgResponse_HouseCancellationPenaltyMoney( SI32 PenaltyMoney) 
	{
	//	siVillageUnique	= villageunique;
	//	siHouseIndex	= houseindex;
		siPenaltyMoney  = PenaltyMoney;
	}
};


class cltGameMsgRequest_HouseCancellation
{
public:

	//whom				
	SI32				siVillageUnique;	// ������ ���� ����ũ. 
	// for what
	SI32				siHouseIndex;	
	//SI32				siPenaltyMoney;

	cltGameMsgRequest_HouseCancellation(SI32 villageunique, SI32 houseindex) //, SI32 PenaltyMoney)
	{
		siVillageUnique	= villageunique;
		siHouseIndex	= houseindex;
		//siPenaltyMoney = PenaltyMoney;
	}
};



class cltGameMsgRequest_HouseUnitStableCreate
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;
	
	SI16 siCreateStableIndex;				// ������ ���⸦ ���ϴ� ���� ��ȣ

	cltGameMsgRequest_HouseUnitStableCreate( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 CreateStableIndex )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;
		siCreateStableIndex = CreateStableIndex;
	}
};

class cltGameMsgResponse_HouseUnitStableCreate
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;
	
	SI16 siCreatedStableIndex;		// ������ ��������
	
	
	//SI32 siLeftPersonMoney;			// ���� ��
	GMONEY siCreatedStableFee;		// ������ ���µ� �� ���
	//cltMoney clHouseMoney;			// ������ ������
	
	//SI16 siItemPos;
	//cltItem clLeftItem;

	cltGameMsgResponse_HouseUnitStableCreate( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 CreatedStableIndex, 
		GMONEY CreatedStableFee )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siCreatedStableIndex = CreatedStableIndex;

		siCreatedStableFee = CreatedStableFee;

		//siItemPos = ItemPos;
		//clLeftItem.Set( pclLeftItem );
	}
};

//------------------------------------
// ���� â�� ���� �־� �޶�� ��û
//------------------------------------
class cltGameMsgRequest_HouseUnitHorseIn
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;
	
	SI16 siHorseIndex;
	SI16 siHorseUnique;
	
	SI16 siStgHorseIndex;	

	cltGameMsgRequest_HouseUnitHorseIn( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 HorseIndex, SI16 HorseUnique, SI16 StgHorseIndex )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siHorseIndex = HorseIndex;
		siHorseUnique = HorseUnique;

		siStgHorseIndex = StgHorseIndex;
	}
};

// �� �޽����� ���ٸ�, ������ �ٴϴ�, �Ǵ� Ÿ�� �ٴϴ� ���� â�� ������ ��.
// ����, Ÿ�� �ٴϴ� �Ǵ� ������ �ٴϴ� ���� ����������...
class cltGameMsgResponse_HouseUnitHorseIn
{
public:
	SI32		siVillageUnique;
	SI32		siHouseUnitSlot;

	SI16		siPersonHorseIndex;		// ����� ������ �ٴѴ� ���� �߿��� ����� �ϴ� Index
	cltHorse	clPersonHorse;			// �������� ���� �ְ�, ������Ե� ���� �ִٸ� �ٲ�(change)

	SI16		siStgHorseIndex;
	cltHorse	clStgHorse;		

	cltGameMsgResponse_HouseUnitHorseIn( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 PersonHorseIndex, cltHorse *pclPersonHorse, SI16 StgHorseIndex, cltHorse *pclStgHorse )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siPersonHorseIndex = PersonHorseIndex;
		if(pclPersonHorse)	clPersonHorse.Set( pclPersonHorse );

		siStgHorseIndex = StgHorseIndex;
		if(pclStgHorse)		clStgHorse.Set( pclStgHorse );
	}
};

//------------------------------------
// ���� â�� ���� ���� �޶�� ��û
//------------------------------------
class cltGameMsgRequest_HouseUnitHorseOut
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siStgHorseIndex;
	SI16 siStgHorseUnique;

	cltGameMsgRequest_HouseUnitHorseOut( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 StgHorseIndex, SI16 StgHorseUnique )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siStgHorseIndex = StgHorseIndex;
		siStgHorseUnique = StgHorseUnique;
	}
};

class cltGameMsgResponse_HouseUnitHorseOut
{
public:
	SI32		siVillageUnique;
	SI32		siHouseUnitSlot;

	SI16		siStgHorseIndex;	// â���� ���� �߿��� ����� �ϴ� Index
	cltHorse	clStgHorse;

	SI16		siHorseIndex;		// ���� ������ �ٴϴ� ���� �迭 Index( �迭�� ���� ������, ����� 0�� �迭 �ۿ� �� �� )
	cltHorse	clHorse;			// �迭�� �� �� ����
	
	cltGameMsgResponse_HouseUnitHorseOut( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 StgHorseIndex, cltHorse *pclStgHorse, SI16 HorseIndex, cltHorse *pclHorse )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;
		
		siStgHorseIndex = StgHorseIndex;
		clStgHorse.Set( pclStgHorse );

		siHorseIndex = HorseIndex;
		if(pclHorse)	clHorse.Set( pclHorse );
	}
};

//------------------------------------
// ���� â�� �� ���� ���� �˸�
//------------------------------------
class cltGameMsgResponse_HouseUnitHorseInfoSet
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siStgHorseIndex;	
	cltHorse clStgHorse;

	cltGameMsgResponse_HouseUnitHorseInfoSet( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 StgHorseIndex, cltHorse *pclHorse )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siStgHorseIndex = StgHorseIndex;
		if(pclHorse)	clStgHorse.Set( pclHorse );
	}
};

class cltGameMsgResponse_HouseUnitHorseEatFood
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siStgItemIndex;
	cltItem clStgItem;

	cltGameMsgResponse_HouseUnitHorseEatFood( SI32 VillageUnique, SI32 HouseUnitSlot, SI16 StgItemIndex, cltItem *pclItem )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siStgItemIndex = StgItemIndex;
		clStgItem.Set( pclItem );
	}
};

class cltGameMsgRequest_HouseUnitUsedGoodsBuildingCreate
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	cltGameMsgRequest_HouseUnitUsedGoodsBuildingCreate( SI32 VillageUnique, SI32 HouseUnitSlot )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;
	}
	
};

class cltGameMsgResponse_HouseUnitUsedGoodsBuildingCreate
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siItemPos;
	cltItem clLeftItem;

	cltGameMsgResponse_HouseUnitUsedGoodsBuildingCreate( SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 ItemPos, cltItem *pclLeftItem )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siItemPos = ItemPos;
		clLeftItem.Set( pclLeftItem );
	}
};

class cltGameMsgRequest_HouseUnitMakeItemFromUsedGoodsInfo
{
public:
	cltItem		clItem;

	cltGameMsgRequest_HouseUnitMakeItemFromUsedGoodsInfo( cltItem *pclItem )
	{
		clItem.Set( pclItem );
	}
};

class cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_MATERIAL_NUMBER>		clMakeableItem;
#else
	cltItem		clMakeableItem[ MAX_MATERIAL_NUMBER ];
#endif

	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsInfo( cltItem *pclMakeableItem )
	{	
#ifdef _SAFE_MEMORY
		clMakeableItem.MemCpy(pclMakeableItem);
#else
		memcpy( clMakeableItem, pclMakeableItem, sizeof( cltItem ) * MAX_MATERIAL_NUMBER );
#endif
	}
};

class cltGameMsgRequest_HouseUnitMakeItemFromUsedGoods
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siItemPos;
	cltItem clItem;

	cltGameMsgRequest_HouseUnitMakeItemFromUsedGoods( SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 ItemPos, cltItem *pclItem )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siItemPos = ItemPos;
		clItem.Set( pclItem );
	}
};

class cltGameMsgResponse_HouseUnitMakeItemFromUsedGoods
{
public:
	SI32 siVillageUnique;
	SI32 siHouseUnitSlot;

	SI16 siSalvageItemPos;

	// ����� ���� ���� ������
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>			siToHouseUnitStgItemPos;
	NSafeTArray<cltItem, MAX_MATERIAL_NUMBER>		clMakeItem;
#else
	SI16				siToHouseUnitStgItemPos[ MAX_MATERIAL_NUMBER ];
	cltItem				clMakeItem[ MAX_MATERIAL_NUMBER ];
#endif

	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoods( SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 SalvageItemPos,
		SI16 *ToHouseUnitStgItemPos, cltItem *pclMakeItem )
	{
		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siSalvageItemPos = SalvageItemPos;

#ifdef _SAFE_MEMORY
		siToHouseUnitStgItemPos.MemCpy(ToHouseUnitStgItemPos);
		clMakeItem.MemCpy(pclMakeItem);
#else
		memcpy( siToHouseUnitStgItemPos, ToHouseUnitStgItemPos, sizeof( SI16 ) * MAX_MATERIAL_NUMBER );
		memcpy( clMakeItem, pclMakeItem, sizeof( cltItem ) * MAX_MATERIAL_NUMBER );
#endif
	}
};

class cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsNotify
{
public:
	SI32 siCharUnique;
	SI16 siItemUnique;
	SI16 siMakePercent;
	
	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsNotify( SI32 CharUnique, SI16 ItemUnique, SI16 MakePercent )
	{
		siCharUnique = CharUnique;
		siItemUnique = ItemUnique;
		siMakePercent = MakePercent;
	}
};

#endif