#ifndef _MSGTYPEITEM_H
#define _MSGTYPEITEM_H

#define ChangeDexStatus	1
#define ChangeHndStatus	2
#define ChangeLukStatus	3
#define ChangeMagStatus	4
#define ChangeStrStatus	5
#define ChangeVitStatus	6

#include "..\Common\Item\ItemCommon\cltItem.h"

#include "../Client/MiniGame/Roulette/RouletteLogic.h"
#include "../Common/Util/Util.h"


//---------------------------------------------------------------
// NPC���� ��û. 
//--------------------------------------------------------------
class cltGameMsgRequest_NPCRepair
{
public:

	SI32	siCharUnique;
	SI16	siPos;			// �κ��� ������ ��ġ. 
	cltItem clItem;			// ���� ��� ������ 

	cltGameMsgRequest_NPCRepair( SI32 CharUnique, SI16 pos, cltItem* pclitem )
	{
		siCharUnique = CharUnique;
		siPos = pos;
		clItem.Set(pclitem);
	}
};

//---------------------------------------------------------------
// NPC���� ���� ��û. 
//--------------------------------------------------------------
class cltGameMsgRequest_NPCRepairPrice
{
public:	
	cltItem clItem;

	cltGameMsgRequest_NPCRepairPrice(cltItem* pclitem)
	{		
		clItem.Set(pclitem);
	}
};

class cltGameMsgResponse_NPCRepairPrice{
public:
	SI16	siItemUnique;
	GMONEY	siRepairePrice;		// ������. 

	cltGameMsgResponse_NPCRepairPrice(SI16 itemunique, GMONEY repairprice)
	{
		siItemUnique	= itemunique;
		siRepairePrice	= repairprice;
	}
};


//---------------------------------------------------------------
// ����ǰ ���� �������� ����ϵ��� �Ѵ�. 
//--------------------------------------------------------------
class cltGameMsgRequest_InvDrop{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgRequest_InvDrop(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};


//*****************************************************************************************
//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ������ �����ϱ� ��Ŷ ����ü. ]
class cltGameMsgRequest_Artifact_Mixture
{
public:
	SI16	m_siEquipItemPos;									// ���յǴ� �������� ��ġ.(������ �ǰ���..)
	cltItem m_clEquipItem;										// ���յǴ� ���Ǵ� ������.

	SI16	m_siCrystalItemPos[MAX_ITEM_ARTIFACT_MIXTURE];		// ���տ� ���Ǵ� �������� ��ġ.
	cltItem m_clCrystalItem[MAX_ITEM_ARTIFACT_MIXTURE];			// ���տ� ���Ǵ� ũ����Ż ������.
	
	cltGameMsgRequest_Artifact_Mixture( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Artifact_Mixture ) );
	}
};

//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���յ� �������� ���� ��Ŷ ����ü. ]
class cltGameMsgResponse_Artifact_Mixture
{
public:
	SI16		m_siEquipItemPos;									// ���յ��� �������� ���� ��ġ.
	cltItem		m_clEquipItem;										// ���յ� ��� ������.

	SI16		m_siCrystalItemPos[MAX_ITEM_ARTIFACT_MIXTURE];		// ���տ� ���� ���� �������� ��ġ �޾Ƽ� �κ����� ����.
	cltItem		m_clCrystalItem[MAX_ITEM_ARTIFACT_MIXTURE];			// ���տ� ���Ǵ� ũ����Ż ������.
	
	cltGameMsgResponse_Artifact_Mixture( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Artifact_Mixture ) );
	}

	cltGameMsgResponse_Artifact_Mixture( SI16		_siEquipItemPos,   cltItem*	_clEquipItem,		
										 SI16*		_siCrystalItemPos, cltItem*	_clCrystalItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Artifact_Mixture ) );

		m_siEquipItemPos = _siEquipItemPos;	
		memcpy(	&m_clEquipItem,		   _clEquipItem,		sizeof( m_clEquipItem )	);
		memcpy(	m_siCrystalItemPos,	   _siCrystalItemPos,	sizeof( m_siCrystalItemPos ) );
		memcpy(	m_clCrystalItem,	   _clCrystalItem,		sizeof( m_clCrystalItem ) );
	}
};

//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ������ ����ü �����ϱ� ��Ŷ ����ü. ]
class cltGameMsgRequest_Artifact_Remove
{
public:
	SI16		m_siEquipItemPos;									// ����ü�� ���ŵǴ� �������� ��ġ.(������ �ǰ���..)
	cltItem		m_clEquipItem;										// ����ü�� ���ŵǴ� ������.

	SI16		m_siCrystalItemPosList[ MAX_CRYSTAL_NUM ];				// ����ü�� ���ſ� ���� �������� ��ġ.(������ �ǰ���..)
	cltItem		m_clCrystalItemList[ MAX_CRYSTAL_NUM ];					// ����ü�� ���ſ� ���� ������.
	
	bool		m_bRemoveSlotIndexList[ MAX_CRYSTAL_NUM ];				// ���ŵǴ� ���� true, false.
	
	cltGameMsgRequest_Artifact_Remove( SI16  _siEquipItemPos,		cltItem* _clEquipItem, 
									   SI16* _siCrystalItemPosList, cltItem* _clCrystalItemList,
									   bool* _bRemoveSlotIndexList )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Artifact_Remove ) );

		m_siEquipItemPos	= _siEquipItemPos;
		memcpy(&m_clEquipItem,  _clEquipItem, sizeof( m_clEquipItem ) );
				
		memcpy(&m_siCrystalItemPosList,  _siCrystalItemPosList, sizeof( m_siCrystalItemPosList ) );
		memcpy(&m_clCrystalItemList,	 _clCrystalItemList,	sizeof( m_clCrystalItemList ) );
		memcpy(m_bRemoveSlotIndexList,	 _bRemoveSlotIndexList, sizeof( m_bRemoveSlotIndexList) );
	}
};

//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ����ü ���ŵ� �������� ���� ��Ŷ ����ü. ]
class cltGameMsgResponse_Artifact_Remove
{
public:
	SI16		m_siEquipItemPos;		// ����ü�� ���ŵ� �������� ���� ��ġ.
	cltItem		m_clEquipItem;			// ����ü�� ���ŵ� ��� ������.

	SI16		m_siCrystalItemPosList[ MAX_CRYSTAL_NUM ];		// ����ü�� ���ſ� ���� �������� ��ġ.
	cltItem		m_clCrystalItemList[ MAX_CRYSTAL_NUM ];			// ����ü�� ���ſ� ���� ������.

	SI16		m_siCreateCrystalItemPos[ MAX_CRYSTAL_NUM ];	// ����ü�� ���ŵ� ������ �������� ��ġ.()
	cltItem		m_clCreateCrystalItem[ MAX_CRYSTAL_NUM ];		// ����ü�� ���ŵ� ������ ������.

	cltGameMsgResponse_Artifact_Remove( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Artifact_Remove ) );
	}

	cltGameMsgResponse_Artifact_Remove( SI16  _siEquipItemPos,			cltItem* _clEquipItem, 
										SI16* _siCrystalItemPosList,	cltItem* _clCrystalItemList,
										SI16* _siCreateCrystalItemPos,  cltItem* _clCreateCrystalItem	)
										
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Artifact_Remove ) );

		m_siEquipItemPos	= _siEquipItemPos;
		memcpy(&m_clEquipItem,  _clEquipItem, sizeof( m_clEquipItem ) );

		memcpy( m_siCrystalItemPosList,  _siCrystalItemPosList, sizeof( m_siCrystalItemPosList ) );
		memcpy( m_clCrystalItemList,	 _clCrystalItemList,	sizeof( m_clCrystalItemList ) );

		memcpy( m_siCreateCrystalItemPos, _siCreateCrystalItemPos, sizeof( m_siCreateCrystalItemPos ) );	
		memcpy( m_clCreateCrystalItem,	  _clCreateCrystalItem,	   sizeof( m_clCreateCrystalItem ) );	
	}
};



//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� ���� ���� ��Ŷ ����ü. ]
class cltGameMsgRequest_Artifact_Slot_Create
{
public:
	SI16		m_siEquipItemPos;					// ������ ���� �� �������� ��ġ.
	cltItem		m_clEquipItem;						// ������ ���� �� ������. 

	SI16		m_siCrystalItemPos;					// ������ ������ �� ����ϴ� �������� ��ġ.
	cltItem		m_clCrystalItem;					// ������ ������ �� ����ϴ� ������. 
	
	cltGameMsgRequest_Artifact_Slot_Create(SI16 _siEquipItemPos, cltItem* _clEquipItem, SI16 _siCrystalItemPos, cltItem* _clCrystalItem)
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Artifact_Slot_Create ) );

		m_siEquipItemPos		= _siEquipItemPos;	
		memcpy(&m_clEquipItem,  _clEquipItem, sizeof( m_clEquipItem ) );		
	
		m_siCrystalItemPos		= _siCrystalItemPos;
		memcpy(&m_clCrystalItem,  _clCrystalItem, sizeof( m_clCrystalItem ) );
	}
};

//[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� ���� ���� ��Ŷ ����ü. ]
class cltGameMsgResponse_Artifact_Slot_Create
{
public:
	SI16		m_siEquipItemPos;				// ������ ���� �� �������� ��ġ.
	cltItem		m_clEquipItem;					// ������ ���� �� ������. 

	SI16		m_siCrystalItemPos;				// ����� ������ ������ �� ����� �������� ��ġ.
	cltItem		m_clCrystalItem;				// ����� ������ ������ �� ����� ������. 
	
	cltGameMsgResponse_Artifact_Slot_Create( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Artifact_Slot_Create ) );
	}

	cltGameMsgResponse_Artifact_Slot_Create(SI16 _siEquipItemPos, cltItem* _clEquipItem, SI16 _siCrystalItemPos, cltItem* _clCrystalItem)
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Artifact_Slot_Create ) );

		m_siEquipItemPos		= _siEquipItemPos;	
		memcpy(&m_clEquipItem,  _clEquipItem, sizeof( m_clEquipItem ) );		

		m_siCrystalItemPos		= _siCrystalItemPos;
		memcpy(&m_clCrystalItem,  _clCrystalItem, sizeof( m_clCrystalItem ) );
	}
};



//*****************************************************************************************

// [�߰� : Ȳ���� 2008. 2. 28 => ������ ���ظ� �ϴ� NPC�� Ÿ��, enum{} ]
class ItemDisAssemble_NPC_KIND
{
public:
	enum{ NPC_TINTIN, NPC_ATIFACT };
};

//---------------------------------------------------------------
// ����ǰ ���� �������� �����Ѵ�.
//--------------------------------------------------------------
class cltGameMsgRequest_ItemDisAssemble
{
public:
	SI32	siItemPos;
	cltItem clItem;

	SI16	m_siNPCKind;		//[�߰� : Ȳ���� 2008. 2. 28 => �޽����� ���� NPC ����. ���� enum ������ ä���.]
	
	cltGameMsgRequest_ItemDisAssemble(SI32 itempos, cltItem* pclitem, SI16 _siNPCKind = ItemDisAssemble_NPC_KIND::NPC_TINTIN)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
		
		m_siNPCKind = _siNPCKind;
	}
};

class cltGameMsgResponse_ItemDisAssemble{
public:
	SI32	siResult;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEM_PER_WENNYOLD>		clItem;
#else
	cltItem clItem[MAX_ITEM_PER_WENNYOLD];
#endif
	SI16	siWenneyPercent;
	SI16	siResolutionRate;

	SI16	siDurabilityPenalty;	// �������� ���� �г�Ƽ

	SI16	m_siNPCKind;			// [�߰� : Ȳ���� 2008. 2. 28 => �޽����� ���� NPC ����. ���� enum ������ ä���.]
	
	cltGameMsgResponse_ItemDisAssemble(SI32 result, cltItem* pclitem, SI16 wennypercent , SI16 resolutionrate, SI16 durabilityPenalty, SI16 _siNPCKind = ItemDisAssemble_NPC_KIND::NPC_TINTIN)
	{
		siResult			= result;
#ifdef _SAFE_MEMORY
		clItem.MemCpy(pclitem);
#else
		memcpy(clItem, pclitem, sizeof(clItem));
#endif
		siWenneyPercent		= wennypercent;
		siResolutionRate	= resolutionrate;

		siDurabilityPenalty	= durabilityPenalty;

		m_siNPCKind			= _siNPCKind;
	}
};

class cltGameMsgRequest_ItemDisAssemble_List
{
public:
	
	SI16	m_siNPCKind;		// [�߰� : Ȳ���� 2008. 2. 28 => �޽����� ���� NPC ����. ���� enum ������ ä���.]

	cltGameMsgRequest_ItemDisAssemble_List( SI16 _siNPCKind = ItemDisAssemble_NPC_KIND::NPC_TINTIN )
	{
		m_siNPCKind = _siNPCKind;
	}
};

class cltGameMsgResponse_ItemDisAssemble_List{
public:
	SI32	siResult;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEM_PER_WENNYOLD>		clItem;
#else
	cltItem clItem[MAX_ITEM_PER_WENNYOLD];
#endif

	SI16	m_siNPCKind;		// [�߰� : Ȳ���� 2008. 2. 28 => �޽����� ���� NPC ����. ���� enum ������ ä���.]

	cltGameMsgResponse_ItemDisAssemble_List(SI32 result, cltItem* pclitem, SI16 _siNPCKind = ItemDisAssemble_NPC_KIND::NPC_TINTIN)
	{
		siResult = result;
#ifdef _SAFE_MEMORY
		clItem.MemCpy(pclitem);
#else
		memcpy(clItem, pclitem, sizeof(clItem));
#endif

		m_siNPCKind = _siNPCKind;
	}
};

class cltGameMsgRequest_ItemDisAssemble_Recieve{
public:
	SI16				siStgPos;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;

	SI16	m_siNPCKind;		// [�߰� : Ȳ���� 2008. 2. 28 => �޽����� ���� NPC ����. ���� enum ������ ä���.]

	cltGameMsgRequest_ItemDisAssemble_Recieve(SI16 stgpos, cltItem *pclitem, SI16 _siNPCKind = ItemDisAssemble_NPC_KIND::NPC_TINTIN )
	{
		siStgPos = stgpos;
		clItem.Set(pclitem);

		m_siNPCKind = _siNPCKind;
	}
};

class cltGameMsgResponse_ItemDisAssemble_Recieve{
public:
	SI32				siResult;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	cltGameMsgResponse_ItemDisAssemble_Recieve(SI32 result)
	{
		siResult = result;
	}
};

//---------------------------------------------------------------
// ����ǰ ���� ������ ��� �����Ѵ�. 
//--------------------------------------------------------------
class cltGameMsgRequest_Enchant{
public:
	SI16	siFromPos;
	SI16	siFromItemUnique;

	SI16	siToPos;
	cltItem clToItem;

	cltGameMsgRequest_Enchant(SI16 frompos, SI16 sifromunique, SI16 topos, cltItem* pclitem)
	{
		siFromPos			= frompos;
		siFromItemUnique	= sifromunique;

		siToPos				= topos;

		clToItem.Set(pclitem);
	}
};


//---------------------------------------------------------------
// ���� ������ �������� �ݵ��� �Ѵ�. 
//--------------------------------------------------------------
class cltGameMsgRequest_InvPickUp{
public:
	SI16	siItemUnique;
	SI16	siItemIndex;	

	SI16	siMapIndex;
	SI16	siX, siY;

	cltGameMsgRequest_InvPickUp(SI16 itemunique, SI16 itemindex, SI16 mapindex, SI16 x, SI16 y)
	{
		siItemUnique	= itemunique;
		siItemIndex		= itemindex;

		siMapIndex		= mapindex;
		siX				= x;
		siY				= y;
	};
};


//-----------------------------------
// ���� ������ �������� ������ Ŭ���̾�Ʈ�� ������. 
//-----------------------------------
class cltGameMsgResponse_ItemDrop{
public:
	cltCharPos clPos;				// �������� ������ ��ġ. 
	UI16		uiItemUnique;		// �������� ����ũ. 
	UI16		uiItemListIndex;	// �������� ������ ����Ʈ �ε���. 

	cltGameMsgResponse_ItemDrop(cltCharPos* pclpos, UI16 itemunique, UI16 itemlistindex)
	{
		clPos.Set(pclpos);
		uiItemUnique	= itemunique;
		uiItemListIndex	= itemlistindex;
	}
};

//-------------------------------------------
// �κ��丮���� �������� �����. 
//-------------------------------------------
class cltGameMsgRequest_MakeItemInv{
public:
	SI16 siItemUnique;
	SI16 siItemNum;

	SI16 siMaterialCharUnique;		// ���� ������(���� �Ƿ��� )
	SI16 siMakeCharUnique;			// ������ 
	SI32 siShopType;				// ���� Ÿ��

	SI08 siType;

	bool bNPCMake;					// NPC�� ���� �����ϴ°�!
	bool bRequestManufacture	;	// ���� �Ƿ����� �ƴ��� 

	cltGameMsgRequest_MakeItemInv()
	{
		Init();
	}

	cltGameMsgRequest_MakeItemInv(SI16 itemunique, SI16 itemnum, SI16 materialcharunique,SI16 MakeCharUnique, SI32 ShopType, SI08 type, bool npcmake = false ,bool RequestManufacture = false   )
	{
		siItemUnique			= itemunique;
		siItemNum				= itemnum;
		siMaterialCharUnique	= materialcharunique;
		siType					= type;
		bNPCMake				= npcmake;
		bRequestManufacture		= RequestManufacture	;
		siMakeCharUnique		=	MakeCharUnique	;
		siShopType				=	ShopType	;
	}

	void Init()
	{
		siItemUnique			= 0;
		siItemNum				= 0;
		siMaterialCharUnique	= 0;
		siType					= 0;
	}

	void Set(cltGameMsgRequest_MakeItemInv* pclinfo)
	{
		siItemUnique			= pclinfo->siItemUnique;
		siItemNum				= pclinfo->siItemNum;
		siMaterialCharUnique	= pclinfo->siMaterialCharUnique;
		siType					= pclinfo->siType;
		bNPCMake				= pclinfo->bNPCMake;
		bRequestManufacture		= pclinfo->bRequestManufacture	;
		siMakeCharUnique		= pclinfo->siMakeCharUnique	;
		siShopType				= pclinfo->siShopType	;
	}
};
//-------------------------------------------
// ��ǰ ���꿡 �ʿ��� ���� �ð��� �뺸�Ѵ�.
//-------------------------------------------
class cltGameMsgResponse_MakeItemDelay{
public:
	DWORD dwDelayClock;
	cltGameMsgResponse_MakeItemDelay(DWORD delay)
	{
		dwDelayClock = delay;
	}
};

//------------------------------------------
// �Ⱓ ���� �������� ����Ѵ�.
//------------------------------------------
class cltGameMsgRequest_UseDayPlus{
public:
	SI32 siItemUnique;	
	
	SI32 siOrgInx;
	SI32 siEleInx;

	cltGameMsgRequest_UseDayPlus(SI32 itemunique, SI32 orginx , SI32 eleinx)
	{
		siItemUnique = itemunique;
		siOrgInx = orginx;
		siEleInx = eleinx;
	}
};

//-------------------------------------------
// Active Weapon�� ���¸� �뺸
//-------------------------------------------
class cltGameMsgResponse_ExchageWeapon{
public:
	SI16	siActiveWeapon;

	cltGameMsgResponse_ExchageWeapon(SI16 active)
	{
		siActiveWeapon	= active;
	}
};

//-------------------------------------------
// Active Clothes�� ���¸� �뺸
//-------------------------------------------
class cltGameMsgResponse_ExchageClothes{
public:
	SI16	siActiveClothes;
	SI16    siActiveHat;

	cltGameMsgResponse_ExchageClothes(SI16 active_c, SI16 active_h )
	{
		siActiveClothes	= active_c;
		siActiveHat = active_h;

	}
};


class cltGameMsgRequest_UpgradeItem
{
public:
	SI16 siToPos;				// ���׷��̵��� �������� �κ��丮 ��ġ
	SI32 siVillageUnique;		// Ȥ�θ������� �ִ� ������ Index

	cltGameMsgRequest_UpgradeItem( SI16 ToPos, SI32 VillageUnique )
	{
		siToPos = ToPos;
		siVillageUnique = VillageUnique;
	}
};

class cltGameMsgResponse_UpgradeItem
{
public:
	SI16 siFromPos;
	cltItem clFromItem;

	SI16 siToPos;
	cltItem clToItem;

	bool bSuccess;

	cltGameMsgResponse_UpgradeItem( bool Success, SI16 FromPos, cltItem *pclFromItem, SI16 ToPos, cltItem *pclToItem )
	{		
		siFromPos = FromPos;
		clFromItem.Set( pclFromItem );

		siToPos = ToPos;
		clToItem.Set( pclToItem );
		
		bSuccess = Success;
	}
};

class cltGameMsgRequest_PerformanceUpgradeItem
{
public:	
	SI32 siVillageUnique;		// Ȥ�θ������� �ִ� ������ Index

	SI16 siItemPos;				// ���׷��̵��� �������� �κ��丮 ��ġ
	cltItem clItem;

	cltGameMsgRequest_PerformanceUpgradeItem( SI32 VillageUnique,
		SI16 ItemPos, cltItem *pclItem )
	{
		siVillageUnique = VillageUnique;

		siItemPos = ItemPos;
		clItem.Set( pclItem );
	}
};

class cltGameMsgResponse_PerformanceUpgradeItem
{
public:
	SI16 siItemPos;
	cltItem clItem;

	SI16 siScrollItemPos;
	cltItem clScrollItem;
	
	cltGameMsgResponse_PerformanceUpgradeItem( SI16 ItemPos, cltItem *pclItem,
		SI16 ScrollItemPos, cltItem *pclScrollItem
		)
	{
		siItemPos = ItemPos;
		clItem.Set( pclItem );

		siScrollItemPos = ScrollItemPos;
		clScrollItem.Set( pclScrollItem );
	}
};


class cltGameMsgResponse_MakeItemDlg
{
public:
	cltItem clItem;
	SI32 siBaseExp;
	SI32 siSkillUnique;
	SI32 siSkillExp;
	SI32 siMonsterCorp;

	cltGameMsgResponse_MakeItemDlg( cltItem *pclItem, SI32 baseexp, SI32 skillunique,SI32 skillexp,SI32 monstercorp)
	{
		clItem.Set(pclItem);
		siBaseExp = baseexp ;
		siSkillUnique = skillunique ;
		siSkillExp = skillexp ;
		siMonsterCorp = monstercorp ;
	}
};


class cltGameMsgResponse_EnchantItemDlg
{
public:
	cltItem clItem;
	SI32 siSucess;


	cltGameMsgResponse_EnchantItemDlg( cltItem *pclItem, SI32 Sucess)
	{
		clItem.Set(pclItem);	
		siSucess = Sucess;

	}
};

class cltGameMsgResponse_IsSkillItem
{
public:
	SI08		siResult; // ����� 1 �ܿ��� ���� ����

	cltGameMsgResponse_IsSkillItem(SI32 result)
	{
		siResult = result ;
	}
};

class cltGameMsgRequest_MonsterCorp_Score
{
public:
	SI32		siScore;

	cltGameMsgRequest_MonsterCorp_Score(SI32 para)
	{
		siScore = para ;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_MonsterCorp_ComboInfo
//
// Last Modified 	: 2007 / 04 / 05
// Created		 	: �豤��
//
// Function			: [��û] �̴� ���� ���� ����� ���ؼ� ������ �޺������� ������.
//
//***************************************************************************************************
class cltGameMsgRequest_MonsterCorp_ComboInfo
{
private:
	SI32		siComboInfo;
	SI32		siScore;

public:
	cltGameMsgRequest_MonsterCorp_ComboInfo(SI32 ComboInfo, SI32 Score) : siComboInfo(ComboInfo), siScore(Score)
	{
		siComboInfo = ComboInfo;
		siScore = Score;
	}

	SI32 GetComboInfo()
	{
		return siComboInfo;
	}

	SI32 GetScore()
	{
		return siScore;
	}
};

class cltGameMsgRequest_RouletteGame_Info
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<RouletteTable, 5>, 5>		m_stRoulette;
#else
	RouletteTable m_stRoulette[5][5];
#endif

	cltGameMsgRequest_RouletteGame_Info(RouletteTable table[][5])
	{
		for(SI32 y = 0;y<5;++y)
		{
			for (SI32 x = 0;x<5;++x) 
			{
				m_stRoulette[y][x].Set(table[y][x].m_bUserSelect,
									   table[y][x].m_bCpuSelect,
									   table[y][x].m_bResult,
									   table[y][x].m_siX,
									   table[y][x].m_siY,
									   table[y][x].m_siValue);
			}
		}
	}
};

class cltGameMsgResponse_RouletteGame_Result
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, 5>		 m_siRandom;
#else
	SI16 m_siRandom[5];
#endif
	SI16 m_siResult;
	SI16 m_siNumber;
	
	cltGameMsgResponse_RouletteGame_Result(SI16 siRandom[], SI16 siResult, SI16 siNumber)
	{
		for(SI32 i=0;i<5;++i)
			m_siRandom[i] = siRandom[i];
		m_siResult = siResult;
		m_siNumber = siNumber;
	}
};

class cltGameMsgResponse_Premium_Info
{
public:
	SI32		siItemPos;
	cltItem		clItem ;

	bool	bPremium;
	SI32	siPremiumDate;
	SI32	siCombatDate;
	SI32	siMakeItemDate;
	SI32	siBulletDate;
	SI32	siSummonStaminaDate;

	SI08	siType;

	cltGameMsgResponse_Premium_Info(SI32 pos , cltItem* pclitem,bool premium,SI32 premiumdate,SI32 combatdate,SI32 makeitemdate, SI32 bulletdate, SI32 summonstaminadate, SI08 type)
	{
		siItemPos = pos ;
		clItem.Set(pclitem);

		bPremium = premium ;
		siPremiumDate = premiumdate ;
		siCombatDate = combatdate ;
		siMakeItemDate = makeitemdate;
		siBulletDate = bulletdate;
		siSummonStaminaDate = summonstaminadate;

		siType = type ;
	}
};


//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_MakeItemSwitch
//
// Last Modified 	: 2006 / 01 / 06
// Created		 	: �豤��
//
// Function			: ������ �����̹��� �����ֱ� true�� �������� false�� ������
//
//***************************************************************************************************
class cltGameMsgRequest_MakeItemSwitch
{
public:
	SI08 siType;	// 0: ���� ���� 1:���� �� ���� 2:����,��

	cltGameMsgRequest_MakeItemSwitch( SI08 Type )
	{
		siType = Type;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_MakeItemSwitch
//
// Last Modified 	: 2006 / 01 / 06
// Created		 	: �豤��
//
// Function			: ������ �����̹��� �����ֱ� true�� �������� false�� ������
//
//***************************************************************************************************
class cltGameMsgResponse_MakeItemSwitch
{
public:
	SI08 siType;

	cltGameMsgResponse_MakeItemSwitch( SI08 Type )
	{
		siType = Type;
	}
};




//�¾� ������.. ����â���� ���� �ε����� ����� ������ ���� ..  
class cltGameMsgRequest_MakeItem_SelectedIndex
{
public:

	SI32			siMoveInvIndex;
	SI32			siInvSelectedValue;

	cltGameMsgRequest_MakeItem_SelectedIndex( SI32 MoveInvIndex,SI32 InvSelectedValue)
	{
		siMoveInvIndex = MoveInvIndex ;
		siInvSelectedValue = InvSelectedValue ;		
	}
};




//�¾� ��æƮ��.. ����â���� ���� �ε����� ����� ������ ���� ..  
class cltGameMsgRequest_EnchantItem_SelectedIndex
{
public:

	//[��þƮ UI ���� - 2007.12.24 �迵�� ���� : ��þƮ ��� �������� ���� �� �ִ� ������ �迭�� ����]
	SI32			siOrgInvEnchantInx;  
	SI32			siMatInvEnchantInx;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, NOW_ENCHANT_NUMBER>		siElementEnchantInx;
#else
	SI32			siElementEnchantInx[NOW_ENCHANT_NUMBER];
#endif
	SI32			siElementType;


	cltGameMsgRequest_EnchantItem_SelectedIndex( SI32 OrgInvEnchantInx,SI32 MatInvEnchantInx,const SI32* pElementEnchantInx, SI32 ElementType)
	{
		siOrgInvEnchantInx = OrgInvEnchantInx;
		siMatInvEnchantInx = MatInvEnchantInx;
		
		for (SI16 siIndex=0; siIndex<NOW_ENCHANT_NUMBER; siIndex++)
		{
			siElementEnchantInx[siIndex] = *(pElementEnchantInx + siIndex);
		}
		
		siElementType		= ElementType;

	}
};



class  cltGameMsgRequest_Enchant_Switch
{
public:
	bool bEnchantSwitch;


	cltGameMsgRequest_Enchant_Switch( bool EnchantSwitch)
	{	
		bEnchantSwitch  = EnchantSwitch;
	}
};

class  cltGameMsgRequest_Enchant_StartOrEnd
{

public:
	bool bEnchantStart;

	cltGameMsgRequest_Enchant_StartOrEnd( bool EnchantStart)
	{	
		bEnchantStart  = EnchantStart;
	}
};

class cltGameMsgResponse_Enchant_StartOrEnd
{
public:
	bool bEnchantStart;

	cltGameMsgResponse_Enchant_StartOrEnd( bool EnchantStart)
	{
		bEnchantStart = EnchantStart;
	}	
};


class cltGameMsgResponse_EnchantOther
{
public:
	//[��þƮ UI ���� - 2007.12.24 �迵�� ���� : ��þƮ ��� �������� ���� �� �ִ� ������ �迭�� ����]
	cltItem clOrgItem;
	cltItem clMatItem;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, NOW_ENCHANT_NUMBER>		clEleItem;
#else
	cltItem clEleItem[NOW_ENCHANT_NUMBER];
#endif
	SI32	siOrgIndex;
	SI32	siMatIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, NOW_ENCHANT_NUMBER>			siEleIndex;
#else
	SI32	siEleIndex[NOW_ENCHANT_NUMBER];
#endif
	bool	bStartEnchant;
	bool	bUpdateMaterial;

	cltGameMsgResponse_EnchantOther(cltItem* OrgItem,cltItem* MatItem,cltItem* pEleItem,
		SI32 OrgIndex, SI32 MatIndex, SI32* pEleIndex, bool StartEnchant, bool UpdateMaterial )
	{
		clOrgItem.Set(OrgItem);
		clMatItem.Set(MatItem);
		siOrgIndex = OrgIndex;
		siMatIndex = MatIndex;
		bStartEnchant = StartEnchant;
		bUpdateMaterial = UpdateMaterial;

		for (SI16 siIndex=0; siIndex<NOW_ENCHANT_NUMBER; siIndex++)
		{
			clEleItem[siIndex].Init();
			clEleItem[siIndex].Set( &pEleItem[siIndex] );
			siEleIndex[siIndex] = pEleIndex[siIndex];
		}
	}	
};

class cltGameMsgRequest_EnchantOther
{
public:
	//[��þƮ UI ���� - 2007.12.24 �迵�� ���� : ��þƮ ��� �������� ���� �� �ִ� ������ �迭�� ����]
	SI32	siOrgIndex;
	SI32	siMatIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, NOW_ENCHANT_NUMBER>		siEleIndex;
#else
	SI32	siEleIndex[NOW_ENCHANT_NUMBER];
#endif
	SI32	m_siOtherCharUnique;

	cltGameMsgRequest_EnchantOther(	SI32 OrgIndex, SI32 MatIndex, SI32* pEleIndex, SI32 OtherCharUnique )
	{

		siOrgIndex = OrgIndex;
		siMatIndex = MatIndex;
		for (SI16 siIndex=0;siIndex<NOW_ENCHANT_NUMBER; siIndex++)
		{
			siEleIndex[siIndex] = pEleIndex[siIndex];
		}
		m_siOtherCharUnique = OtherCharUnique;
	}	
};

class cltGameMsgResponse_EnchantPrice
{
public:

	SI32 siUnique;
	cltGameMsgResponse_EnchantPrice(SI32 Unique)
	{
		siUnique = Unique ; 		
	}	
};

class cltGameMsgRequest_EnchantPrice
{
public:

	GMONEY	siCurrentPrice;

	cltGameMsgRequest_EnchantPrice(	GMONEY	CurrentPrice )
	{
		siCurrentPrice= CurrentPrice;	
	}	
};

class cltGameMsgResponse_SetItemTypeInfo
{
private:
	SI16	m_siSetItemType;
	SI16	m_siSetItemStep;

	SI16	m_siSetItemType2;
	SI16	m_siSetItemStep2;

	SI16	m_siSetItemType3;
	SI16	m_siSetItemStep3;

	SI16	m_siSetItemType4;
	SI16	m_siSetItemStep4;

	SI16	m_siSetItemType5;
	SI16	m_siSetItemStep5;

public:

	cltGameMsgResponse_SetItemTypeInfo( SI16 SetItemType, SI16 _siSetItemStep, SI16 SetItemType2, SI16 _siSetItemStep2, SI16 SetItemType3, SI16 _siSetItemStep3, SI16 SetItemType4, SI16 _siSetItemStep4, SI16 SetItemType5, SI16 _siSetItemStep5)
	{
		m_siSetItemType = SetItemType; 
		m_siSetItemStep = _siSetItemStep;

		m_siSetItemType2 = SetItemType2; 
		m_siSetItemStep2 = _siSetItemStep2;

		m_siSetItemType3 = SetItemType3; 
		m_siSetItemStep3 = _siSetItemStep3;

		m_siSetItemType4 = SetItemType4; 
		m_siSetItemStep4 = _siSetItemStep4;

		m_siSetItemType5 = SetItemType5; 
		m_siSetItemStep5 = _siSetItemStep5;
	}

	SI16 GetSetItemTypeInfo() 
	{
		return m_siSetItemType;
	}
	SI16 GetSetItemStepInfo() 
	{
		return m_siSetItemStep;
	}
	SI16 GetSetItemTypeInfo2() 
	{
		return m_siSetItemType2;
	}
	SI16 GetSetItemStepInfo2() 
	{
		return m_siSetItemStep2;
	}

	SI16 GetSetItemStepInfo3() 
	{
		return m_siSetItemStep3;
	}

	SI16 GetSetItemStepInfo4() 
	{
		return m_siSetItemStep4;
	}

	SI16 GetSetItemStepInfo5() 
	{
		return m_siSetItemStep5;
	}
};


//[�߰� : Ȳ���� 2008. 1. 29 => ���� ���� ������ ���� S->C]
class cltGameMsgResponse_Space_Box_List
{
public:
	cltSpaceBox		m_SpaceBoxItem;
	cltTreasureBox	m_TreasureBoxItem;

	cltGameMsgResponse_Space_Box_List()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Space_Box_List ) );	
	}

	cltGameMsgResponse_Space_Box_List( cltSpaceBox* _SpaceBoxItem, cltTreasureBox* _TreasureBoxItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Space_Box_List ) );	

		memcpy( &m_SpaceBoxItem,	_SpaceBoxItem,    sizeof( m_SpaceBoxItem ) );
		memcpy( &m_TreasureBoxItem, _TreasureBoxItem, sizeof( m_TreasureBoxItem ) );
	}
};

// [����] �������� �������� ����� ����
class cltGameMsgResponse_Use_SpaceBox_Item
{
public:
	SI16	m_siItemPos;
	cltItem	m_clItem;

	cltGameMsgResponse_Use_SpaceBox_Item()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Use_SpaceBox_Item) );
	}

	cltGameMsgResponse_Use_SpaceBox_Item( SI16 siItemPos, cltItem* pclItem )
	{	
		m_siItemPos = siItemPos;
		m_clItem.Set( pclItem );
	}

};

class cltGameMsgResponse_Use_Treasure_Item
{
public:
	SI16	m_siItemPos;
	cltItem	m_clItem;

	cltGameMsgResponse_Use_Treasure_Item()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Use_Treasure_Item) );
	}

	cltGameMsgResponse_Use_Treasure_Item( SI16 siItemPos, cltItem* pclItem )
	{	
		m_siItemPos = siItemPos;
		m_clItem.Set( pclItem );
	}

};

////[�߰� : Ȳ���� 2008. 1. 29 => ���� ����(����) ������ ���� S->C]
//class cltGameMsgResponse_Treasure_Box_List
//{
//private:
//	cltTreasureBox m_TreasureBoxItem;
//
//public:
//
//	cltGameMsgResponse_Treasure_Box_List()
//	{
//		ZeroMemory( this, sizeof( cltGameMsgResponse_Treasure_Box_List ) );	
//	}
//};

//[�߰� : Ȳ���� 2008. 1. 29 => ����, ���� ���� ������ ���� S->C]
class cltGameMsgRequest_Keep_Box_Move_Item
{
public:
	bool		m_bGacha;					// ���������ΰ� �������� �ΰ�?
	SI32		m_siPos;					// �������� ��ġ.
	cltItem		m_KeepItem;					// ���� �� ������.

	cltGameMsgRequest_Keep_Box_Move_Item( bool _bGacha, SI32 _siPos, cltItem* _KeepItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Keep_Box_Move_Item ) );	

		m_bGacha   = _bGacha;
		m_siPos	   = _siPos;
		m_KeepItem.Set( _KeepItem );
	}
};

//[�߰� : Ȳ���� 2008. 1. 29 => ����, ���� ���� ������ ���� S->C]
class cltGameMsgResponse_Keep_Box_Move_Item
{
public:
	bool		m_bGacha;					// ���������ΰ� �������� �ΰ�?
	
	SI16		m_siInvenPos;				// �κ��丮 �������� ��ġ.
	cltItem		m_InvenItem;				// �κ��丮 �� ������.
	
	SI16		m_siKeepPos;				// �������� ��ġ.
	cltItem		m_KeepItem;					// ���� �� ������.

	cltGameMsgResponse_Keep_Box_Move_Item( bool _bGacha, SI16 _siInvenPos, cltItem* _InvenItem, SI16 _siKeepPos, cltItem* _KeepItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Keep_Box_Move_Item ) );	

		m_bGacha   = _bGacha;

		m_siInvenPos = _siInvenPos;	
		m_InvenItem.Set( _InvenItem );

		m_siKeepPos	= _siKeepPos;
		m_KeepItem.Set( _KeepItem );
	}
};


//[�߰� : Ȳ���� 2008. 1. 29 => ����, ���� ���� ������ ȸ�� S->C]
class cltGameMsgRequest_Recovery_Box_Move_Item
{
public:
	bool			m_bGacha;				// ���������ΰ� �������� �ΰ�?
	SI32			m_siPos;				// �������� ��ġ.
	cltItem			m_RecoveryItem;			// ȸ�� �� ������.

	cltGameMsgRequest_Recovery_Box_Move_Item( bool _bGacha, SI32 _siPos, cltItem* _RecoveryItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_Recovery_Box_Move_Item ) );

		m_bGacha	   = _bGacha;		
		m_siPos		   = _siPos;		
		m_RecoveryItem.Set( _RecoveryItem );
	}
};

//[�߰� : Ȳ���� 2008. 1. 29 => ����, ���� ���� ������ ȸ�� S->C]
class cltGameMsgResponse_Recovery_Box_Move_Item
{
public:
	bool		m_bGacha;					// ���������ΰ� �������� �ΰ�?
	
	SI16		m_siInvenPos;				// �κ��丮 �������� ��ġ.
	cltItem		m_InvenItem;				// �κ��丮 ������.

	SI16		m_siRecoveryPos;			// �������� ��ġ.
	cltItem		m_RecoveryItem;				// ȸ�� �� ������.

	cltGameMsgResponse_Recovery_Box_Move_Item( bool _bGacha, SI16 _siInvenPos, cltItem* _InvenItem , SI16 _siRecoveryPos, cltItem* _RecoveryItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Recovery_Box_Move_Item ) );	

		m_bGacha   = _bGacha;
		
		m_siInvenPos = _siInvenPos;	
		m_InvenItem.Set( _InvenItem );
		
		m_siRecoveryPos = _siRecoveryPos;
		m_RecoveryItem.Set( _RecoveryItem );
	}
};

// [����] ��þƮ �Ӽ� ���� ��û - 2008.02.20
class cltGameMsgRequest_ChangeEnchant
{
public:
	SI16	m_siOrgUnique;	// �ٲٰ��� �ϴ� �������� Unique
	SI16	m_siOrgIndex;	// �ٲٰ��� �ϴ� �������� ����ִ� �κ��丮 ��ȣ
	SI16	m_siChangeType;	// �ٲٰ��� �ϴ� ��þƮ �Ӽ�

	SI16	m_siEleIndex;	// ��þƮ ��ȯ �Ӽ� �������� ����ִ� �κ��丮 ��ȣ


	cltGameMsgRequest_ChangeEnchant(SI16 siOrgUnique, SI16 siOrgIndex, SI16 siChangeType, SI16 siEleIndex)
	{
		m_siOrgUnique		= siOrgUnique;
		m_siOrgIndex		= siOrgIndex;
		m_siChangeType		= siChangeType;

		m_siEleIndex		= siEleIndex;
	}
};

class cltGameMsgRequest_OpenBigItemBox
{
public:
	SI16		m_siBoxPos;				// �ڽ� �������� ��ġ.
	cltItem		m_clBoxItem;			// �ڽ� ������.

	SI16		m_siKeyPos;				// Ű �������� ��ġ.
	cltItem		m_clKeyItem;			// Ű ������.

	cltGameMsgRequest_OpenBigItemBox(SI16 siBoxPos, cltItem* pclBoxItem, SI16 siKeyPos, cltItem* pclKeyItem)
	{
		m_siBoxPos	= siBoxPos;	
		if(pclBoxItem)	m_clBoxItem.Set(pclBoxItem);

		m_siKeyPos	= siKeyPos;	
		if(pclKeyItem)	m_clKeyItem.Set(pclKeyItem);
	}
};

//---------------------------------------
// ������� ��ȯ������ �������� �̵��Ǿ�����
//---------------------------------------
class cltGameMsgRequest_SummonPushItem
{
public:

	SI08 m_siSummonIndex;	// ��ȯ�� �ε���
	//From
	UI16 m_uiFrom;			// ��𿡼� �ű�°�.
	//To
	UI16 m_uiTo;			// ���� �ű�°� ?


	cltGameMsgRequest_SummonPushItem()
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_SummonPushItem));
	}

	cltGameMsgRequest_SummonPushItem( SI08 siSummonIndex, UI16 uiFrom, UI16 uiTo )
	{
		m_siSummonIndex	= siSummonIndex;
		m_uiFrom		= uiFrom;
		m_uiTo			= uiTo;
	}

};


//---------------------------------------
// ��ȯ������ ������� �������� �̵��Ǿ�����
//---------------------------------------
class cltGameMsgRequest_SummonPopItem
{
public:

	SI08 m_siSummonIndex;	// ��ȯ�� �ε���
	//From
	UI16 m_uiFrom;			// ��𿡼� �ű�°�.
	//To
	UI16 m_uiTo;			// ���� �ű�°� ?


	cltGameMsgRequest_SummonPopItem()
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_SummonPopItem));
	}

	cltGameMsgRequest_SummonPopItem( SI08 siSummonIndex, UI16 uiFrom, UI16 uiTo )
	{
		m_siSummonIndex	= siSummonIndex;
		m_uiFrom		= uiFrom;
		m_uiTo			= uiTo;
	}

};

// Push/Pop�� �ؼ� ��ȯ���� �������� ����Ǿ���
class cltGameMsgResponse_SummonChangeItem
{
public:

	SI08	m_siSummonIndex;	// ��ȯ�� �ε���
	SI16	m_siItemPos;		// ������ ��ġ
	cltItem	m_clItem;			// ������


	cltGameMsgResponse_SummonChangeItem()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_SummonChangeItem));
	}

	cltGameMsgResponse_SummonChangeItem( SI08 siSummonIndex, SI16 siItemPos, cltItem* pclItem )
	{
		m_siSummonIndex	= siSummonIndex;
		m_siItemPos		= siItemPos;
		m_clItem.Set( pclItem );
	}

};

//[����] ȣ�ڻ���. �ڽ����� ���� �������� ����. => 2008-9-16
class cltGameMsgResponse_Amber_Box_List
{
public:
	SI32			m_siItemList[AMBER_BOX_LIST_NUM];
	SI32			m_siListNum;
	SI16			m_siUseItemUnique;						// ���� �������� ����ũ.

public:
	cltGameMsgResponse_Amber_Box_List()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_Amber_Box_List));
	}

	cltGameMsgResponse_Amber_Box_List( const SI32* _psiItemList, SI32 _siListNum, SI16	_siUseItemUnique )
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_Amber_Box_List));

		memcpy( m_siItemList, _psiItemList, sizeof(SI32)*_siListNum );

		m_siListNum			= _siListNum;
		m_siUseItemUnique	= _siUseItemUnique;
	}
};

//[����] ȣ�ڻ���. Ŭ���ϴ� ������ ������ �׸� ����Ʈ. => 2008-9-16
class cltGameMsgResponse_Amber_Box_Select_Item_List
{
public:
	AmberboxSelectItemInfo	m_clAmberboxItemList[3];

public:
	cltGameMsgResponse_Amber_Box_Select_Item_List(AmberboxSelectItemInfo* _clAmberboxItemList)
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Amber_Box_Select_Item_List ) );

		memcpy(m_clAmberboxItemList, _clAmberboxItemList, sizeof(m_clAmberboxItemList));
	}
};

// [����] ȣ�ڻ���. Ŭ���Ͽ� �����ϰ� ������ ������ �߰�. => 2008-9-16
class cltGameMsgRequest_Amber_Box_Select_Item_Add	// response : cltGameMsgResponse_Amber_Box_Select_Item_List
{
public:
	SI16 	m_siSlotIndex;
	SI32		m_clUseItemUnique;
public:
	cltGameMsgRequest_Amber_Box_Select_Item_Add( SI16 _siSlotIndex  , SI32 _clUseItemUnique)
	{
		m_siSlotIndex = _siSlotIndex;
		m_clUseItemUnique = _clUseItemUnique;
	}
};


// [����] ȣ�ڻ���. Ŭ���� ������ ȹ��. => 2008-9-16
class cltGameMsgRequest_Amber_Box_Select_Item_Get	
{
public:
	SI32					m_clUseItemUnique;		// ���Ǵ� ������. 
	
	AmberboxSelectItemInfo	m_clAmberboxItem;		// ������ ������ ����.

public:
	cltGameMsgRequest_Amber_Box_Select_Item_Get( SI32 _clUseItemUnique, AmberboxSelectItemInfo*	_pclAmberboxItem )
	{
		m_clUseItemUnique = _clUseItemUnique;
		
		memcpy( &m_clAmberboxItem, _pclAmberboxItem, sizeof(m_clAmberboxItem) );
	}
};

class cltGameMsgResponse_Amber_Box_Select_Item_Get	
{
public:
	SI16					m_siRemainItemPos;		// ����ϰ� ���� �������� �κ� ��ġ. 
	cltItem					m_clRemainItem;			// ����ϰ� ���� ������ ����.

	SI16					m_siToItemPos;			// ���� �������� �κ� ��ġ. 
	cltItem					m_clToItem;				// ���� ������ ����(���� �������� ������ ������ ����).


public:
	cltGameMsgResponse_Amber_Box_Select_Item_Get( 	SI16 _siRemainItemPos,   cltItem* _pclRemainItem,
													SI16 _siToItemPos,		 cltItem* _pclToItem		)
	{
		m_siRemainItemPos = _siRemainItemPos;
		m_clRemainItem.Set( _pclRemainItem );

		m_siToItemPos	  = _siToItemPos;
		m_clToItem.Set( _pclToItem );
	}
};

// [����] ���ο� ���û��ڿ��� 12���� ���� �ϳ��� �����Ҷ�
class cltGameMsgRequest_NewSelectBox_Select
{
public:
	SI16	m_siBoxItemUnique;
	SI16	m_siSelectIndex;

	cltGameMsgRequest_NewSelectBox_Select( SI16 siBoxItemUnique, SI16 siSelectIndex )
	{
		m_siBoxItemUnique	= siBoxItemUnique;
		m_siSelectIndex		= siSelectIndex;
	}
};	// GAMEMSG_REQUEST_NEWSELECTBOX_SELECT

// [����]
class cltGameMsgResponse_NewSelectBox_Select
{
public:
	SI16	m_siBoxItemUnique;	// ���� ���ð��� ���ϰ��� Ȯ���ϱ� ���ѿ�
	SI16	m_siSelectIndex;
	// �� ���� �����ۿ��� ���� ������ ���
	SI16	m_siItemList[MAX_NEWSELECTBOX_ITEM_LIST];	
	
	cltGameMsgResponse_NewSelectBox_Select( SI16 siBoxItemUnique, SI16 siSelectIndex, SI16* psiItemList )
	{
		m_siBoxItemUnique	= siBoxItemUnique;
		m_siSelectIndex		= siSelectIndex;

		if ( psiItemList )
		{
			memcpy( m_siItemList, psiItemList, sizeof(m_siItemList) );
		}
	}
};	// GAMEMSG_RESPONSE_NEWSELECTBOX_SELECT

// [����] ���ο� ���û��ڿ��� �������� �޴´�
class cltGameMsgRequest_NewSelectBox_GetItem
{
public:
	SI16	m_siBoxItemUnique;
	SI16	m_siSelectIndex;

	cltGameMsgRequest_NewSelectBox_GetItem( SI16 siBoxItemUinque, SI16 siSelectIndex )
	{
		m_siBoxItemUnique	= siBoxItemUinque;
		m_siSelectIndex		= siSelectIndex;
	}
};	// GAMEMSG_REQUEST_NEWSELECTBOX_GETITEM

class cltGameMsgResponse_NewSelectBox_GetItem
{
public:
	cltItem	m_clBoxItem;	// ����ϰ� ���� ���� ������
	SI16	m_siBoxItemPos;	// 

	cltItem	m_clGetItem;	// ���� ������
	SI16	m_siGetItemPos;	//

	cltItem m_clToItem;		// ���� ������ ����������(���� ���� �������� �� �κ��� �ִ� �Ͱ� ��������);

	cltGameMsgResponse_NewSelectBox_GetItem( cltItem* pclBoxItem, SI16 siBoxItemPos, cltItem* pclGetItem, SI16 siGetItemPos, cltItem* pclToItem )
	{
		if ( pclBoxItem )
		{
			m_clBoxItem.Set( pclBoxItem );
		}
		m_siBoxItemPos = siBoxItemPos;

		if ( pclGetItem )
		{
			m_clGetItem.Set( pclGetItem );
		}
		m_siGetItemPos = siGetItemPos;

		if ( pclToItem )
		{
			m_clToItem.Set( pclToItem );
		}
	}

};	// GAMEMSG_RESPONSE_NEWSELECTBOX_GETITEM

//---------------------------------------------------------------
// NPC���� ��û. [����] ���ο� ����
//--------------------------------------------------------------
class cltGameMsgRequest_NewNPCRepair
{
public:
	SI16	m_siPos;			// �κ��� ������ ��ġ. 
	cltItem m_clItem;			// ���� ��� ������ 

	GMONEY	m_money;

	// ���� ��� ������ : ������ + ��Ÿ���
	RepairItemExtraMaterial	m_Material;

	cltGameMsgRequest_NewNPCRepair( SI16 pos, cltItem* pclitem, GMONEY money, RepairItemExtraMaterial& ExtraMaterial )
	{
		m_siPos			= pos;
		m_clItem.Set(pclitem);

		m_money			= money;

		for( SI32 i=0; i<m_Material.GetSize(); i++ )
		{
			m_Material[i].Set( &ExtraMaterial[i] );
		}
	}
};

class cltGameMsgResponse_NewNpcRepair
{
public:
	SI32	m_siResult;

};

//---------------------------------------------------------------
// ������ ���� & ��û [����] ���ο� ����
//--------------------------------------------------------------
class cltGameMsgRequest_NewItemRepair
{
public:
	SI16	m_siPos;			// �κ��� ������ ��ġ. 
	cltItem m_clItem;			// ���� ��� ������ 

	GMONEY	m_money;

	// ���� ��� ������ : ������ + ��Ÿ���
	RepairItemExtraMaterial	m_Material;

	SI16	m_siType;			// 1:��������, 2:������û, 3:�Ƿڼ���, 4:������û ���
	SI32	m_siItemPersonID;
    
	cltGameMsgRequest_NewItemRepair( SI16 pos, cltItem* pclitem, GMONEY money, RepairItemExtraMaterial& ExtraMaterial, SI32 siItemPersonID, SI16 siType )
	{
		m_siPos			= pos;
		m_clItem.Set(pclitem);

		m_money			= money;

		for( SI32 i=0; i<m_Material.GetSize(); i++ )
		{
			m_Material[i].Set( &ExtraMaterial[i] );
		}

		m_siItemPersonID= siItemPersonID;
		m_siType		= siType;
	}
};

class cltGameMsgResponse_NewItemRepair
{
public:
	SI32	m_siResult;
	SI32	m_siItemCharUnique;

	cltItem m_clItem;			// ���� ��� ������ 

	SI16	m_siType;			// 1:��������, 2:������û, 3:�Ƿڼ���, 4:������û ���

	cltGameMsgResponse_NewItemRepair( SI32 siResult, SI32 siCharUnique, cltItem* pclitem, SI16 siType )
	{
		m_siResult			= siResult;

		m_siItemCharUnique	= siCharUnique;
		m_clItem.Set( pclitem );
		m_siType			= siType;
	}
};

//---------------------------------------------------------------
// ������ �������� ��û
//--------------------------------------------------------------
#define NEWITEMREPAIR_INFO_BANNER		0x0001
#define NEWITEMREPAIR_INFO_ITEM			0x0002

class cltGameMsgRequest_NewItemRepairRequestInfo
{
public:
	SI32	m_siCharUnique;		// ������ ��û�� ĳ���� ����ũ

	SI16	m_siType;			// 0x01:������� ���� ��û, 0x02:���������� ��û

	cltGameMsgRequest_NewItemRepairRequestInfo(SI32 siCharUnique, SI32 siType)
	{
		m_siCharUnique		= siCharUnique;
		m_siType			= siType;
	}
};

class cltGameMsgResponse_NewItemRepairRequestInfo
{
public:
	SI32	m_siItemPersonID;	// �������� ������ �ִ� ĳ������ PersonID
	SI32	m_siItemCharUnique;	// �������� ������ �ִ� ĳ������ CharUnique

	SI16	m_siPos;			// �κ��� ������ ��ġ. 
	cltItem m_clItem;			// ���� ��� ������ 

	GMONEY	m_money;

	// ���� ��� ������ : ������ + ��Ÿ���
	RepairItemExtraMaterial	m_Material;

	SI16	m_siType;			// 0x0001:������� ���� ��û, 0x0002:���������� ��û

	cltGameMsgResponse_NewItemRepairRequestInfo( SI32 siItemPersonID, SI32 siItemCharUnique, SI16 pos, cltItem* pclitem, GMONEY money, RepairItemExtraMaterial& ExtraMaterial, SI32 siType )
	{
		m_siItemPersonID	= siItemPersonID;
		m_siItemCharUnique	= siItemCharUnique;

		m_siPos			= pos;
		m_clItem.Set(pclitem);

		m_money			= money;

		for( SI32 i=0; i<m_Material.GetSize(); i++ )
		{
			m_Material[i].Set( &ExtraMaterial[i] );
		}

		m_siType			= siType;
	}
};

class cltGameMsgRequest_EquipmentCreate
{
public:
	SI32		m_siWeaponUnique;
	SI32		m_siHelmetUnique;
	SI32		m_siArmorUnique;
	SI32		m_siBeltUnique;
	SI32		m_siShoeUnique;
	SI32		m_siNeckUnique;
	SI32		m_siRingUnique;
	SI32		m_siMantleUnique;

	SI32		m_siWeaponPower1;
	SI32		m_siWeaponPower2;
	SI32		m_siWeaponPower3;
	SI32		m_siWeaponPower4;

	SI32		m_siHelmetPower1;
	SI32		m_siHelmetPower2;
	SI32		m_siHelmetPower3;
	SI32		m_siHelmetPower4;

	SI32		m_siArmorPower1;
	SI32		m_siArmorPower2;
	SI32		m_siArmorPower3;
	SI32		m_siArmorPower4;

	SI32		m_siBeltPower1;
	SI32		m_siBeltPower2;
	SI32		m_siBeltPower3;
	SI32		m_siBeltPower4;

	SI32		m_siShoePower1;
	SI32		m_siShoePower2;
	SI32		m_siShoePower3;
	SI32		m_siShoePower4;

	SI32		m_siMantlePower1;
	SI32		m_siMantlePower2;
	SI32		m_siMantlePower3;
	SI32		m_siMantlePower4;

	SI32		m_siNeckLacePower1;
	SI32		m_siNeckLacePower2;
	SI32		m_siNeckLacePower3;
	SI32		m_siNeckLacePower4;

	SI32		m_siRingPower1;
	SI32		m_siRingPower2;
	SI32		m_siRingPower3;
	SI32		m_siRingPower4;

	SI32		m_siWeaponProPerty;
	SI32		m_siHelmetProPerty;
	SI32		m_siArmorProPerty;
	SI32		m_siBeltProPerty;
	SI32		m_siShoeProPerty;

	SI32		m_siWeaponEnchant;
	SI32		m_siHelmetEhchant;
	SI32		m_siArmorEnchant;
	SI32		m_siBeltEnchat;
	SI32		m_siShoeEnchant;

	SI32		m_siWeaponSlot;
	SI32		m_siHelmetSlot;
	SI32		m_siArmorSlot;
	SI32		m_siBeltSlot;
	SI32		m_siShoeSlot;

	cltGameMsgRequest_EquipmentCreate (SI32 siWeaponUnique, SI32 siHelmetUnique, SI32 siArmorUnique, SI32 siBeltUnique, SI32 siShoeUnique, SI32 siNeckUnique, SI32 siRingUnique, SI32 siMantleUnique,
									   SI32 siWeaponPower1, SI32 siWeaponPower2, SI32 siWeaponPower3, SI32 siWeaponPower4, SI32 siHelmetPower1, SI32 siHelmetPower2, SI32 siHelmetPower3, SI32 siHelmetPower4,
									   SI32 siArmorPower1, SI32 siArmorPower2, SI32 siArmorPower3, SI32 siArmorPower4, SI32 siBeltPower1, SI32 siBeltPower2, SI32 siBeltPower3, SI32 siBeltPower4,
									   SI32 siShoePower1, SI32 siShoePower2, SI32 siShoePower3, SI32 siShoePower4, SI32 siMantlePower1, SI32 siMantlePower2, SI32 siMantlePower3, SI32 siMantlePower4,
									   SI32 siNeckLacePower1, SI32 siNeckLacePower2, SI32 siNeckLacePower3, SI32 siNeckLacePower4, SI32 siRingPower1, SI32 siRingPower2, SI32 siRingPower3, SI32 siRingPower4,
									   SI32 siWeaponProPerty, SI32 siHelmetProPerty, SI32 siArmorProPerty, SI32 siBeltProPerty, SI32 siShoeProPerty,
									   SI32 siWeaponEnchant, SI32 siHelmetEhchant, SI32 siArmorEnchant, SI32 siBeltEnchat, SI32 siShoeEnchant,
									   SI32 siWeaponSlot, SI32 siHelmetSlot, SI32 siArmorSlot, SI32 siBeltSlot, SI32 siShoeSlot)
	{
		m_siWeaponUnique = siWeaponUnique;
		m_siHelmetUnique = siHelmetUnique;
		m_siArmorUnique = siArmorUnique;
		m_siBeltUnique = siBeltUnique;
		m_siShoeUnique = siShoeUnique;
		m_siNeckUnique = siNeckUnique;
		m_siRingUnique = siRingUnique;
		m_siMantleUnique = siMantleUnique;

		m_siWeaponPower1 = siWeaponPower1;
		m_siWeaponPower2 = siWeaponPower2;
		m_siWeaponPower3 = siWeaponPower3;
		m_siWeaponPower4 = siWeaponPower4;

		m_siHelmetPower1 = siHelmetPower1;
		m_siHelmetPower2 = siHelmetPower2;
		m_siHelmetPower3 = siHelmetPower3;
		m_siHelmetPower4 = siHelmetPower4;

		m_siArmorPower1 = siArmorPower1;
		m_siArmorPower2 = siArmorPower2;
		m_siArmorPower3 = siArmorPower3;
		m_siArmorPower4 = siArmorPower4;

		m_siBeltPower1 = siBeltPower1;
		m_siBeltPower2 = siBeltPower2;
		m_siBeltPower3 = siBeltPower3;
		m_siBeltPower4 = siBeltPower4;

		m_siShoePower1 = siShoePower1;
		m_siShoePower2 = siShoePower2;
		m_siShoePower3 = siShoePower3;
		m_siShoePower4 = siShoePower4;

		m_siMantlePower1 = siMantlePower1;
		m_siMantlePower2 = siMantlePower2;
		m_siMantlePower3 = siMantlePower3;
		m_siMantlePower4 = siMantlePower4;

		m_siNeckLacePower1 = siNeckLacePower1;
		m_siNeckLacePower2 = siNeckLacePower2;
		m_siNeckLacePower3 = siNeckLacePower3;
		m_siNeckLacePower4 = siNeckLacePower4;

		m_siRingPower1 = siRingPower1;
		m_siRingPower2 = siRingPower2;
		m_siRingPower3 = siRingPower3;
		m_siRingPower4 = siRingPower4;

		m_siWeaponProPerty = siWeaponProPerty;
		m_siHelmetProPerty = siHelmetProPerty;
		m_siArmorProPerty = siArmorProPerty;
		m_siBeltProPerty = siBeltProPerty;
		m_siShoeProPerty = siShoeProPerty;

		m_siWeaponEnchant = siWeaponEnchant;
		m_siHelmetEhchant = siHelmetEhchant;
		m_siArmorEnchant = siArmorEnchant;
		m_siBeltEnchat = siBeltEnchat;
		m_siShoeEnchant = siShoeEnchant;

		m_siWeaponSlot = siWeaponSlot;
		m_siHelmetSlot = siHelmetSlot;
		m_siArmorSlot = siArmorSlot;
		m_siBeltSlot = siBeltSlot;
		m_siShoeSlot = siShoeSlot;
	}
};

class cltGameMsgResponse_EquipmentCreate
{
public:
	SI32	m_siResult;

};

class cltGameMsgRequest_SkillBook_BuyItem
{
public:	
	SI32		m_siGrade;
	cltItem		m_clBuyItem;
	cltItem		m_clUseItem;
	SI32		m_siInvenPos;
	GMONEY		m_siUseMoney;

	cltGameMsgRequest_SkillBook_BuyItem( SI32 _siGrade, cltItem* _pclBuyItem, cltItem* _pclUseItem, SI32 _siInvenPos, GMONEY	_siUseMoney )
	{
		ZeroMemory( this, sizeof(*this) );

		m_siGrade	 = _siGrade;
		m_clBuyItem.Set( _pclBuyItem );
		m_clUseItem.Set( _pclUseItem );
		m_siInvenPos = _siInvenPos;
		m_siUseMoney = _siUseMoney;
	}
};

class cltGameMsgResponse_SkillBook_BuyItem
{
public:
	cltGameMsgResponse_SkillBook_BuyItem( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}

};

class cltGameMsgResponse_SkillBook_MagicInfo_Get
{
public:
	cltGameMsgResponse_SkillBook_MagicInfo_Get() 
	{
		ZeroMemory( this, sizeof(*this) );
	}
	~cltGameMsgResponse_SkillBook_MagicInfo_Get()
	{

	}

	SI08					m_iIndex[SKILLBOOK_MAGIC_NUM];
	cltSkillBookMagic		m_clAddSkillBookMagic[SKILLBOOK_MAGIC_NUM];
	cltSkillBookSubMagic	m_clAddSkillBookSubMagic[MAX_SKILLBOOK_SUBMAGIC_NUM];
};

class cltGameMsgResponse_SkillBook_Magic_Add
{
public:
	cltGameMsgResponse_SkillBook_Magic_Add( cltSkillBookMagic* _pclAddSkillBookMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( &m_clAddSkillBookMagic, _pclAddSkillBookMagic, sizeof(m_clAddSkillBookMagic) );
	}
	
	SI08				m_iIndex;
	cltSkillBookMagic	m_clAddSkillBookMagic;
};

class cltGameMsgRequest_SkillBook_Magic_Del
{
public:
	cltGameMsgRequest_SkillBook_Magic_Del( SI08	_iIndex, cltSkillBookMagic* _pclAddSkillBookMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		m_iIndex = _iIndex;
		m_clAddSkillBookMagic.Set( _pclAddSkillBookMagic );
	}

	SI08				m_iIndex;
	cltSkillBookMagic	m_clAddSkillBookMagic;
};

class cltGameMsgResponse_SkillBook_Magic_Del
{
public:
	cltGameMsgResponse_SkillBook_Magic_Del( SI08 _iIndex )
	{
		ZeroMemory( this, sizeof(*this) );

		m_iIndex = _iIndex;
	}

	SI08				m_iIndex;
};


class cltGameMsgResponse_SkillBook_SubMagic_Add
{
public:
	cltGameMsgResponse_SkillBook_SubMagic_Add( cltSkillBookSubMagic* _pclAddSkillBookSubMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( &m_clAddSkillBookSubMagic, _pclAddSkillBookSubMagic, sizeof(m_clAddSkillBookSubMagic) );
	}

	cltSkillBookSubMagic m_clAddSkillBookSubMagic;
};

class cltGameMsgRequest_SkillBook_SubMagic_Del
{
public:
	cltGameMsgRequest_SkillBook_SubMagic_Del( cltSkillBookSubMagic* _pclAddSkillBookSubMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( &m_clAddSkillBookSubMagic, _pclAddSkillBookSubMagic, sizeof(m_clAddSkillBookSubMagic) );
	}

	cltSkillBookSubMagic m_clAddSkillBookSubMagic;
};

class cltGameMsgResponse_SkillBook_SubMagic_Del
{
public:
	cltGameMsgResponse_SkillBook_SubMagic_Del( cltSkillBookSubMagic* _pclAddSkillBookSubMagic )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( &m_clAddSkillBookSubMagic, _pclAddSkillBookSubMagic, sizeof(m_clAddSkillBookSubMagic) );
	}

	cltSkillBookSubMagic m_clAddSkillBookSubMagic;
};


//////////////////////////////////////////////////////////////////////////
//[����] : 2010�ų��̺�Ʈ - �ų��̺�Ʈ�� ���� �޼��� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////

// � : ���� ��� ����� Ŭ�� �뺸�ϱ� ���� Ŭ����
class cltGameMsgResponse_2010NewYear_FortuneResult
{
public:
	SI32 m_siPersonID;
	NTCHARString128 m_strUserName;

	SI16 m_siFortuneQuality;		// ���/��/��/��Ű (��Ű ������ ����Ƽ�� 100�� �־ Ŭ�� ����)
	SI32 m_siFortuneTextUnique;		// ���/��/�信 ���� � �޼����� ����ũ
	SI32 m_siBuffNameUnique;		// �� �϶� ���� �̷ο� ������ �̸� ����ũ

	SI16 m_siQuestClearCondition;	// �� �϶� ���� ����Ʈ�� Ŭ���� ����
	SI32 m_siQuestPara1;			// ����Ʈ �Ķ���� 1
	SI32 m_siQuestPara2;			// ����Ʈ �Ķ���� 2

public:
	cltGameMsgResponse_2010NewYear_FortuneResult(SI32 siPersonID, SI16 siFortuneQuality, SI32 siFortuneTextUnique, SI32 siBuffNameUnique, SI16 siQuestClearCondition, SI32 siQuestPara1, SI32 siQuestPara2, TCHAR* pUserName = NULL)
	{
		ZeroMemory( this, sizeof(*this) );

		m_siPersonID = siPersonID;

		m_siFortuneQuality = siFortuneQuality;
		m_siFortuneTextUnique = siFortuneTextUnique;
		m_siBuffNameUnique = siBuffNameUnique;

		m_siQuestClearCondition = siQuestClearCondition;
		m_siQuestPara1 = siQuestPara1;
		m_siQuestPara2 = siQuestPara2;

		m_strUserName = pUserName;
	}
};
// [����] ���� ���� ���ڿ��� �������� �ش� 
class cltGameMsgRequest_UseLimitLevleBox
{
public:
	SI16 m_siOpenItemBox	;	
	cltGameMsgRequest_UseLimitLevleBox()
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_UseLimitLevleBox));
	}

	cltGameMsgRequest_UseLimitLevleBox( SI16 siOpenItemBox )
	{
		m_siOpenItemBox	= siOpenItemBox;
	}

};
//[����] // �׾��� ���� ���Ȳ�̴� �������� ���δ� 
class cltGameMsgRequest_UseJustUseItem
{
public:
	SI16 m_siitempos	;	// ����� �������� ������ 
	SI32 m_siitemunique	;	// ����� ������ ����ũ 	
	SI32 m_siitemnum	;	// ����� �������� ���� 
	cltGameMsgRequest_UseJustUseItem()
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_UseJustUseItem));
	}

	cltGameMsgRequest_UseJustUseItem( SI32 siitemunique, SI16 siitempos, SI32 siitemnum  )
	{
		m_siitemunique	= siitemunique;		
		m_siitemnum	= siitemnum;
		m_siitempos	= siitempos;

	}

};
#endif

