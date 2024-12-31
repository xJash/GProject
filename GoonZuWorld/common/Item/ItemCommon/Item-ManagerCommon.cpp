//---------------------------------
// 2003/8/7 ���°�
//---------------------------------
#include <Stdio.h>
#include "cltItem.h"

#include "../../../CommonLogic/CommonLogic.h"

//-----------------------------
// Common
//-----------------------------
#include "../../../common/PersonInfo.h"
#include "../../../common/Char\CharManager\CharManager.h"
#include "../../../common/Skill\Skill-Manager.h"
#include "../../../common/Char\Disease\Disease.h"
#include "../../../common/Util\Util.h"
#include "../../../common/Char\CharCommon\Char-Common.h"
#include "../../../common/DailyQuest3/DailyQuest3Mgr.h"


#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Market.h"

#include "..\Server\Server.h"
#include "..\Server\Minister\MinisterBase.h"
#include "..\Server\Minister\Minister-Izo.h"
#include "..\Server\Minister\MinisterMgr.h"

#include "../Server/GachaManager/GachaManager.h"
#include "../Server/Gacha2Manager/Gacha2Manager.h"


extern cltCommonLogic* pclClient;

SI32 siBigWennyItemList[]=
{
	ITEMUNIQUE(1000),	// �ʽ����Ǹ����[����]
	ITEMUNIQUE(1010),	// �ʽ����Ǹ����[����]
	ITEMUNIQUE(1020)	// �ʽ����Ǹ����[����]
};

SI32 siBigWarItemList[]=
{
	ITEMUNIQUE(5350),	// ���ǼӼ���
	ITEMUNIQUE(5355),	// ���ǼӼ���
	ITEMUNIQUE(5360),	// �ٶ��ǼӼ���
	ITEMUNIQUE(5365)	// ���ǼӼ���
};

SI32 siBigChristmas[]=
{
	ITEMUNIQUE(7150),	// 
	ITEMUNIQUE(7160),	// 
	ITEMUNIQUE(7170)	// 
};


cltItemManagerCommon::cltItemManagerCommon()
{
	SI32 i;

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		pclItemTypeInfo[i] = NULL;
	}

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		pclItemInfo[i] = NULL;
	}


	for(i = 0;i < MAX_ITEM_UNIQUE;i++)
	{
		ItemRef[i] = 0;
	}

	pclItemPrice				= NULL;
	pclItemNewPrice				= NULL;
	pcltSetItemAbilityManager	= NULL;
	pclSkillBookManager			= NULL;
	// [����] ���� ���� ���ڿ��� �������� �ش� 
	pclRewardItemLimitLevelForChina	=	NULL	;
	siItemNum					= 0;
	bCanMakeRareItemSwitch		= true;
	dwLastMakeRareItemClock		= 0;
	m_bcheckcnppricerateswitch = false;

	for(i = 0;i < 9; i++)
	{
		clMarketConditions[i] = NULL;
	}


/*	for ( i = 0 ; i < MAX_INVESTMENT_ITEM_NUMBER ; i ++ )
	{
		stInvestmentLines[i].siInvestmentItemUnique = 0 ;
		stInvestmentLines[i].siInvestmentItemPrice = 0 ;

		stInvestmentLines[i].siMarginalProfit = 0 ;

		for ( j = 0 ; j < MAX_MATERIAL_NUMBER ; j ++ )
		{
			stInvestmentLines[i].siMaterialItemUnique[j] = 0 ;
			stInvestmentLines[i].siMaterialItemNeedNum[j] = 0 ;
			stInvestmentLines[i].siMaterialItemPrice[j] = 0 ;
		}
	}*/

	// ItemInfoAtb ���
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_ITEMMALL"),					ITEMINFOATB_ITEMMALL );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_CANUSEITEM"),				ITEMINFOATB_CANUSEITEM );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_NOTDAILYQUEST"),			ITEMINFOATB_NOTDAILYQUEST );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_NOTWENNYOLDMAN"),			ITEMINFOATB_NOTWENNYOLDMAN );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_NOTTRADE"),					ITEMINFOATB_NOTTRADE );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_FIRSTACTION"),				ITEMINFOATB_FIRSTACTION );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_SPECIAL_JAPAN"),			ITEMINFOATB_SPECIAL_JAPAN );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_SPECIAL_GLOBAL"),			ITEMINFOATB_SPECIAL_GLOBAL );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_SPECIAL_KOREA"),			ITEMINFOATB_SPECIAL_KOREA );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_WENNYOLDMAN_MATERIAL"),		ITEMINFOATB_WENNYOLDMAN_MATERIAL );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_NOTSELL"),					ITEMINFOATB_NOTSELL );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_NOTSHOW_MARKETCONFITIONS"),	ITEMINFOATB_NOTSHOW_MARKETCONFITIONS );

	
	// CANUSEITEM_TYPE ���
	ItemInfoAtbParser.AddAtbInfo( TEXT("CANUSEITEM_TYPE_EAST"),					CANUSEITEM_TYPE_EAST );
	ItemInfoAtbParser.AddAtbInfo( TEXT("CANUSEITEM_TYPE_WEST"),					CANUSEITEM_TYPE_WEST );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_CRYSTAL_SLOT_CREATE"),		ITEMINFOATB_CRYSTAL_SLOT_CREATE );
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_CRYSTAL_REMOVE"),			ITEMINFOATB_CRYSTAL_REMOVE );
	
	//[����] ���� ��ȯ���� ����(���: 1.������ ��� ����.) => 2008-7-15
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_RARE_SUMMONDOLL"),			ITEMINFOATB_RARE_SUMMONDOLL );
	//KHY - 20090526 - �ƹ�Ÿ ����ü.
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_CRYSTAL_AVATAR"),			ITEMINFOATB_CRYSTAL_AVATAR );
	
	//[����] ��ų��
	ItemInfoAtbParser.AddAtbInfo( TEXT("ITEMINFOATB_SKILLBOOK"),				ITEMINFOATB_SKILLBOOK );

	

}

cltItemManagerCommon::~cltItemManagerCommon()
{
	SI32 i ,x;

	if(pclItemPrice)
	{
		delete pclItemPrice;
		pclItemPrice = NULL;
	}

	if( pclItemNewPrice )
	{
		delete pclItemNewPrice;
		pclItemNewPrice = NULL;
	}
		
	if( pcltSetItemAbilityManager )
	{
		delete pcltSetItemAbilityManager;
		pcltSetItemAbilityManager = NULL;
	}

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i])
		{
			delete pclItemInfo[i];
			pclItemInfo[i] = NULL;
		}
	}

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		if(pclItemTypeInfo[i])
		{
			delete pclItemTypeInfo[i];
			pclItemTypeInfo[i] = NULL;
		}
	}

	for(i = 0;i < 9;i++)
	{
		if(clMarketConditions[i])
		{
			for(x = 0;x < MAX_ITEM_UNIQUE;x++)
			{
				if(clMarketConditions[i]->pclMarketConditionsB[x])
				{
					delete clMarketConditions[i]->pclMarketConditionsB[x];
					clMarketConditions[i]->pclMarketConditionsB[x] = NULL;
				}
			}

			delete clMarketConditions[i];
			clMarketConditions[i] = NULL;
		}
	}

	if( pclSkillBookManager )
	{
		delete pclSkillBookManager;
		pclSkillBookManager = NULL;
	}
// [����] ���� ���� ���ڿ��� �������� �ش� 
	if(pclRewardItemLimitLevelForChina)// �߱����� ���� ������
	{
		delete pclRewardItemLimitLevelForChina	;
		pclRewardItemLimitLevelForChina	=	NULL	;
	}
	

	if( pclSetItemManager)
	{
		delete pclSetItemManager;
		pclSetItemManager = NULL;
	}

}
/*
bool cltItemManagerCommon::GetLimitDateItemValue(SI32 unique , SI32* usedate)
{
	if(unique < 0)return false;
	if(unique >= MAX_ITEM_UNIQUE)return false;

	cltServer* pclserver = (cltServer*)pclClient;

	if ( unique > 0 )
	{
		SI32 ref = ItemRef[unique] ;
		if ( ref > 0 )
		{
			SI32 UseDate = pclItemInfo[ref]->siUseDate ;
			if ( UseDate )
				*usedate = pclserver->pclTime->clDate.GetDateVary() + UseDate ;
			else
				*usedate = 0 ;

			if ( *usedate > 0 )
				return true ;
			else return false ;
		}
	}
	
	return false ;
}
*/
void cltItemManagerCommon::Create()
{
	// �������� ��Ʈ�� �̹��� ������ �����Ѵ�. (Ŭ���̾�Ʈ ����) 
	//if ( pclClient->siServiceArea == ConstServiceArea_Korea )
	//{
		SetBitmapImage();
		SetItemImageBigList();	//[����] �ƾ��� ū �̹��� ����. => 2008-9-23
	//}

	// ������ Ÿ���� �����Ѵ�. 
	SetItemType();
	
	// ������ ������ �����Ѵ�. 
	SetItemData();

	// �������� ���� ������ �����Ѵ�. 
	SetItemMaterial();

	pclItemPrice	= new cltItemPrice(this);
	pclItemNewPrice = new cltItemPrice(this);
	
	if( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		//[����] ��Ʈ ������ �ܰ�� �ɷ�ġ ���� �ʱ�ȭ
		pcltSetItemAbilityManager = new cltSetItemAbilityManager;
		pcltSetItemAbilityManager->Init();
	}

	// [����] ��ų��
	pclSkillBookManager = new cltSkillBookManager;
	pclSkillBookManager->Init();
	
	pclSetItemManager = new CSetItemManager;
	pclSetItemManager->LoadSetItemInfo();
	// [����] ���� ���� ���ڿ��� �������� �ش� 
	if ( pclClient->IsCountrySwitch(Switch_LevelLimitBox) ) 
	{
		pclRewardItemLimitLevelForChina = new cltRewardItemForLimitLevel	;
		pclRewardItemLimitLevelForChina->init()	;
	}
#ifdef _DEBUG
	//// ���� �̸��� �����ϴ� �������� �ִ��� �˻��Ѵ�.
	//for( SI32 i=0; i<MAX_ITEMINFO_NUMBER; i++ )
	//{
	//	if( pclItemInfo[i] == NULL )			continue;
	//	
	//	for( SI32 j=0; j<MAX_ITEMINFO_NUMBER; j++ )
	//	{
	//		if( pclItemInfo[j] == NULL )												continue;
	//		if( pclItemInfo[i]->clItem.siUnique == pclItemInfo[j]->clItem.siUnique )	continue;
	//		if( _tcscmp( pclItemInfo[i]->GetName(), pclItemInfo[j]->GetName() ) == 0 )
	//		{
	//			NTCHARString256 kMsg;
	//			kMsg += "����ũ[";
	//			kMsg += SI16ToString(pclItemInfo[i]->clItem.siUnique);
	//			kMsg += "]�� ";
	//			kMsg += "����ũ[";
	//			kMsg += SI16ToString(pclItemInfo[j]->clItem.siUnique);
	//			kMsg += "] �� ";
	//			kMsg += "�̸��� �����ϴ�.";
	//			MessageBox(NULL, kMsg, "ITEMNAME ERROR", MB_OK);
	//		}
	//	}
	//}
#endif
}

// ������Ÿ��, �Ӽ�, �Ҽ�, Ÿ���ڵ�, �̸�
BOOL cltItemManagerCommon::SetItemType(SI32 itemtype, SI64 siatb, SI64 siattach, const TCHAR* typecode, const TCHAR* pname)
{

	if(itemtype < 0 || itemtype >= MAX_ITEMTYPE_NUMBER)
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("SetItemType(SI32 itemtype, SI64 siatb) %d %d"), itemtype, siatb);
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("Error"), buffer, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	if(pclItemTypeInfo[itemtype] == NULL)
	{
		pclItemTypeInfo[itemtype] = new cltItemTypeInfo(itemtype, siatb, siattach, typecode, pname);
		return TRUE;
	}

	return FALSE;
}

// �������� �̸����� �������� ����ũ ���� ���Ѵ�. 
SI32 cltItemManagerCommon::FindUniqueFromName(const TCHAR* pname)
{
	SI32 i;
	
	if( NULL == pname)
		return 0;

	if ( !_tcsicmp(TEXT("NULL"),pname)) return 0;

	for(i = 1;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i])
		{
			if(_tcscmp(pclItemInfo[i]->GetName() , pname) == 0)
			{
				return pclItemInfo[i]->clItem.siUnique;
			}
		}
	}

	return 0;
}

SI08 cltItemManagerCommon::FindMakeAniTypeFromUnique(SI32 siUnique)
{

	if(siUnique == 0)return 0;

	SI08 makeanytype = MAKE_ANI_ARMOR;
	SI32 itemtype = GetItemType(siUnique);

	switch(itemtype)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_NECK:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_HAT:
	case ITEMTYPE_MANTLE:
	case ITEMTYPE_AVATAR_MANTLE:
	case ITEMTYPE_AVATAR_NECK:
	case ITEMTYPE_AVATAR_RING:
	case ITEMTYPE_AVATAR_DRESS:
	case ITEMTYPE_AVATAR_HAT:
	case ITEMTYPE_MINERAL:
		{
			makeanytype = MAKE_ANI_ARMOR;
			// ��					
		}
		break;
	case ITEMTYPE_HEAL:						
		{
			// ��
			makeanytype = MAKE_ANI_HEAL;

		}
		break;
	case ITEMTYPE_FOOD:
	case ITEMTYPE_SEAFOOD:
		{
			makeanytype = MAKE_ANI_FOOD;
		}
		break;
	case ITEMTYPE_CRYSTAL://��Ƽ��Ʈ
		{
			makeanytype = ENCHANT_ANI_WEPONE;
		}
		break;
	case ITEMTYPE_DOLL:
		{
			makeanytype = MAKE_ANI_HEAL;
		}
		break;

	default:
		{
			makeanytype = MAKE_ANI_ARMOR;
		}
		break;
	}

	return makeanytype;
}

SI08 cltItemManagerCommon::FindEnchantAniTypeFromUnique(SI32 siUnique)
{
	if(siUnique == 0)return 0;

	SI08 enchantanitype = ENCHANT_ANI_WEPONE;
	SI32 itemtype = GetItemType(siUnique);

	switch(itemtype)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
		{
			//���� ��þƮ
			enchantanitype = ENCHANT_ANI_WEPONE;				
		}
		break;	

	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_DRESS:
	case ITEMTYPE_NECK:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_HAT:
	case ITEMTYPE_MANTLE:
		{
			//�� ��þƮ
			enchantanitype = ENCHANT_ANI_ARMOR;
		}
		break;
	default:
		{
			enchantanitype = ENCHANT_ANI_WEPONE;
		}
		break;
	}

	return enchantanitype;

}

// �������� Ÿ���̸��� �ٰŷ� ������Ÿ���� ����ũ���� ���Ѵ�.
SI32 cltItemManagerCommon::FindItemTypeUniqueFromTypeName(const TCHAR* itemtypename)
{
	SI32 i;

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		if(pclItemTypeInfo[i])
		{
			if(_tcscmp(pclItemTypeInfo[i]->GetName(), itemtypename) == 0)
			{
				return i;
			}
		}
	}

	return -1;

}

// �������� Ÿ���ڵ带  �ٰŷ� ������Ÿ���� ����ũ���� ���Ѵ�.
SI32 cltItemManagerCommon::FindItemTypeUniqueFromTypeCode(const TCHAR* itemtypeCode)
{
	SI32 i;

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		if(pclItemTypeInfo[i])
		{
			if(_tcscmp(pclItemTypeInfo[i]->szTypeCode, itemtypeCode) == 0)
			{
				return i;
			}
		}
	}

	return -1;

}
// ����߷��� �ϴ� ���������� �ƴ��� ���� �Ѵ�
bool cltItemManagerCommon::IsCanDropItem( SI32 siItemUniuqe ){
	// ������ �� �������� ������ �̸��� �Ἥ �ı� �Ѵ�.
	// �ŷ� �Ұ� �������� �̸��� �Ἥ �ı� �Ѵ�.
	// �� ����� �ƴ� ��쿡�� �׳� �ı��Ѵ�.
	// �̸��� �Ἥ �ı� �Ұ��� false
	// �׳� �ı� �Ұ�� true
	// ���� ������ ����ũ�� �ش� ref �� ���Ѵ�.
	SI32 ref = FindItemRefFromUnique( siItemUniuqe );
	if(ref <= 0)return false; 
	// �ı� �Ǿ� �ϴ� ������					->	���� Ǯ�� ��� ������,�̰� ���� ���� �Ѵ�.
	
	// �ı� �ȵǰ� ��ӵǴ� ������				->	Ʈ����Ʈ ������ ������,
	// �ı� �ȵǰ� ��ӵ� �ȵǾ� �ϴ� ������	->	������ ��Ǯ�� Ʈ���̵� ������ ��� ������, �Ϲ� ��� �������߿� Ʈ���̵� ���� ������

	// ref�� ���� �ش� �������� item�� Ʈ���̵� �Ұ��� �������� �� �� ������� �ʴ´�.
	if( pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE ) )		return false ;
	//// ref�� ���� �ش� �������� item�� �����۸� �������� ��
	//if( pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_ITEMMALL ) )		return false ;
	
	// Ʈ���̵� ������ �������� ��쿡�� ����߸���.
	else																return true ;
}
SI32 cltItemManagerCommon::AddItem(SI32 imageindex, SI32 smallimageindex, TCHAR* name, SI32 sitype, SI32 weight,
								   cltItemSkillInfo* pclskillinfo, cltItemConition* pclcondition, TCHAR* armcode,
								   TCHAR* material, TCHAR* tool,SI32 productunit, SI32 soundtype, cltItem* pclitem,
								   SI32 Grade, SI32 MinNum,cltCrystalItemData *CrystalItemData, bool bNewMarket, bool ImmutableUseDate)
{
	SI32 i;
	if(pclitem->siUnique <= 0)
	{
		MsgBox(TEXT("fsdf"), TEXT("Vsdf:%d"), pclitem->siUnique);
	}


	for(i = 1;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i])continue;
		
#ifdef _DEBUG
		TCHAR szName[64];
		if( _tcscmp( name, "NULL" ) == 0 )
		{
			StringCchPrintf(szName, sizeof(szName), "%s(%d)", "NoItemText", pclitem->siUnique );
			name = szName;
		}
#endif
		pclItemInfo[i] = new cltItemInfo(imageindex, smallimageindex, name, sitype, weight, pclskillinfo,
										 pclcondition, armcode, material, tool, productunit, soundtype, pclitem, Grade, MinNum, CrystalItemData, bNewMarket, ImmutableUseDate);
		
		// Unique���� �ٰŷ� ���� Ref�� ã�´�.
		ItemRef[pclitem->siUnique] = i;
		
		// �������� ������ ������Ų��. 
		siItemNum++;
		
		return i;
	}

	MsgBox(TEXT("Item Num Exceed"), TEXT("Item Num Exceed"));

	return -1;

}

// �������� ������ ��ġ���� Ȯ���Ѵ�. 
bool cltItemManagerCommon::CheckProperItemPos(cltItem* pclItem, SI32 siDragTo, SI32 siKind)
{
	// [����] ��ȯ�� ������� : �Ʒ� �ڵ忡 �ּ�ó�� �Ǿ��ִ°��� ��� �ʿ���� �͵������� ���� ������ ���� ����

	if(pclItem == NULL)return false;

	// �ش� �������� Ÿ���� ���Ѵ�.
	SI32 itemtype = pclItem->GetType(this);
	if(itemtype ==0)return false;

		
	// ���� �Ұ� ǰ���� ���� false 
	SI32 ref = FindItemRefFromUnique(pclItem->siUnique);
	if (ref <= 0) return	false;

	bool bCanEquip = true;

	switch(siDragTo)
	{
	case PERSONITEM_WEAPON1:
	case PERSONITEM_WEAPON2:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;

		bCanEquip = pclItem->IsCorrectPrivateEquip(this, siKind);

		//cyj ����, ���� �����϶� ���� Ȯ��(��ȯ���� �������)
		if (bCanEquip == false)
			return false;

		// ���� �Ӽ��� ���� �������̸� ������.
		if(pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_WEAPON) == TRUE)return true;
		if(itemtype == ITEMTYPE_FISHINGROD)	return true;
		if(itemtype == ITEMTYPE_IRON)		return true;
		
		
		//cyj ȭ�� �� źȯ ���� �����ϵ��� ����
		if(pclItem->IsBulletItem())	return true;

		break;

		/*
	case PERSONITEM_WEAPON1 + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_WEAPON1 + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		// ���� �Ӽ��� ���� �������̸� ������.
		if(pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_WEAPON) == TRUE)return true;
		if(itemtype == ITEMTYPE_FISHINGROD)	return true;
		if(itemtype == ITEMTYPE_IRON)		return true;
		//cyj ȭ�� �� źȯ ���� �����ϵ��� ����
		if(pclItem->IsBulletItem())	return true;
		break;

	case PERSONITEM_WEAPON2 + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_WEAPON2 + PERSONITEM_SUMMON2EQUIP0:
		return false;
		break;
	*/
	case PERSONITEM_HELMET:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;

		bCanEquip = pclItem->IsCorrectPrivateEquip(this, siKind);

		//cyj ����, ���� �����϶� ���� Ȯ��(��ȯ���� �������)
		if (bCanEquip == false)
			return false;

		if(itemtype == ITEMTYPE_HELMET)return true;
		break;

	/*
	case PERSONITEM_HELMET + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_HELMET + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_HELMET)return true;
		break;
	*/

	
	case PERSONITEM_HAT:
	//case PERSONITEM_HAT + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_HAT + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_HAT || itemtype == ITEMTYPE_AVATAR_HAT )return true;
		break;
	
	case PERSONITEM_ARMOUR:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;

		bCanEquip = pclItem->IsCorrectPrivateEquip(this, siKind);

		//cyj ����, ���� �����϶� ���� Ȯ��(��ȯ���� �������)
		if (bCanEquip == false)
			return false;

		if(itemtype == ITEMTYPE_ARMOUR)return true;
		break;

	/*
	case PERSONITEM_ARMOUR + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_ARMOUR + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_ARMOUR)return true;
		break;
	*/
	case PERSONITEM_DRESS:
	//case PERSONITEM_DRESS + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_DRESS + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_DRESS || itemtype == ITEMTYPE_AVATAR_DRESS)return true;
		break;

	case PERSONITEM_NECK:
	//case PERSONITEM_NECK + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_NECK + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_NECK || itemtype == ITEMTYPE_AVATAR_NECK)return true;
		break;

	case PERSONITEM_BELT:
	//case PERSONITEM_BELT + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_BELT + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_BELT)return true;
		break;

	case PERSONITEM_RING1:
	case PERSONITEM_RING2:
	//case PERSONITEM_RING1 + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_RING1 + PERSONITEM_SUMMON2EQUIP0:
	//case PERSONITEM_RING2 + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_RING2 + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_RING || itemtype == ITEMTYPE_AVATAR_RING)return true;
		break;

	case PERSONITEM_SHOES:
	//case PERSONITEM_SHOES + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_SHOES + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_SHOES)return true;
		break;

	case PERSONITEM_MANTLE:
	//case PERSONITEM_MANTLE + PERSONITEM_SUMMON1EQUIP0:
	//case PERSONITEM_MANTLE + PERSONITEM_SUMMON2EQUIP0:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_MANTLE || itemtype == ITEMTYPE_AVATAR_MANTLE )return true; // �ƹ�Ÿ ����
		break;

	case PERSONITEM_BAG:
	case PERSONITEM_BAG_SUB:
		if(pclItemInfo[ref]->bCanEquipSwitch == false)return false;
		if(itemtype == ITEMTYPE_BAG)return true;
		break;

	/*
	case PERSONITEM_BAG + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_BAG + PERSONITEM_SUMMON2EQUIP0:
	case PERSONITEM_BAG_SUB + PERSONITEM_SUMMON1EQUIP0:
	case PERSONITEM_BAG_SUB + PERSONITEM_SUMMON2EQUIP0:
		return false;
		break;
	*/

	default:			// �κ��丮. 
		return true;
		
	}

	return false;
}


// siUnique�������� ���� ��Ÿ��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetAttackRange(SI32 unique)
{
	SI32 ref = FindItemRefFromUnique(unique);
	if(ref > 0)
	{
		return pclItemInfo[ref]->GetAttackRange();
	}

	return 0;
}

// �������� �ü��� �����Ѵ�. 
void cltItemManagerCommon::SetCurrentPrice(SI32 itemunique, GMONEY price, SI32 itemnum, bool bforceswitch)
{
	pclItemPrice->SetPrice(this, itemunique, price, itemnum, bforceswitch);
}

void cltItemManagerCommon::SetCurrentNewPrice(SI32 itemunique, SI64 price, SI32 itemnum, bool bforceswitch)
{
	pclItemNewPrice->SetPrice(this, itemunique, price, itemnum, bforceswitch );
}

// �������� �ü��� ���´�.
cltItemPriceUnit* cltItemManagerCommon::GetCurrentPrice(SI32 itemnunique)
{
	return pclItemPrice->GetPrice(this, itemnunique);
}

cltItemPriceUnit* cltItemManagerCommon::GetCurrentNewPrice(SI32 itemnunique)
{
	return pclItemNewPrice->GetPrice(this, itemnunique);
}


// Unique�� �ٰŷ� Atb�� ���Ѵ�. 
SI64 cltItemManagerCommon::GetItemAtb(SI32 siunique)
{
	if(siunique == 0)return 0;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return 0;

	// �������� Type�� ���Ѵ�. 
	SI32 type = pclItemInfo[ref]->siType;

	// ������ Type�� Atb�� ���Ѵ�. 
	SI64 atb = pclItemTypeInfo[type]->siAtb;

	return atb;

}

SI32 cltItemManagerCommon::GetItemGrade(SI32 ItemUnique)
{
	if(ItemUnique == 0)return 0;
	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(ItemUnique);

	if(ref <= 0)return 0;

	SI32 maxItemGrade = pclItemInfo[ref]->siItemGrade;

	return maxItemGrade;


}

// Unique�� �ٰŷ� Type�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetItemType(SI32 siunique)
{
	if(siunique == 0)return 0;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return 0;

	// �������� Type�� ���Ѵ�. 
	return pclItemInfo[ref]->siType;

}

// Unique�� �ٰŷ� Atb�� ���Ѵ�. 
SI64 cltItemManagerCommon::GetItemAttach(SI32 siunique)
{
	if(siunique == 0)return 0;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return 0;

	// �������� Type�� ���Ѵ�. 
	SI32 type = pclItemInfo[ref]->siType;

	// ������ Type�� Attach�� ���Ѵ�. 
	SI64 adaptattach = pclItemTypeInfo[type]->siAttach;

	return adaptattach;

}

// �ش� Scroll �� �����ۿ� ���ϼ� �ִ��� Ȯ���Ѵ�.
BOOL cltItemManagerCommon::CanItemAttach(SI32 scrollunique, SI32 tounique)
{
	if(scrollunique == 0)	return FALSE;
	if(tounique == 0)		return FALSE;

	// �������� ref�� ���Ѵ�. 
	SI32 scrollref = FindItemRefFromUnique(scrollunique);
	if(scrollref <= 0)return FALSE;
	
	SI32 toref = FindItemRefFromUnique(tounique);
	if(toref <= 0)return FALSE;

	// �������� Type�� ���Ѵ�. 
	SI32 adaptattach = pclItemInfo[scrollref]->siScrollAdaptAttach;

	SI32 type = pclItemInfo[toref]->siType;

	switch(adaptattach)
	{
		case ITEMATTACH_SKILLUPDRESS:
			{
				if(pclItemInfo[toref]->siUpgradeSkillType & UPGRADESKILLTYPE_MAKE)
				{
					/// �ø� �� �ִ� �ѵ��� �־�� ����. 
					if (type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT)
					{
						if(pclItemInfo[toref]->clItem.clItemStatusArmour.uiSkillUp)
						{
							return TRUE;
						}
					}
					else
					{
						if(pclItemInfo[toref]->clItem.clItemArmour.uiSkillUp)
						{
							return TRUE;
						}
					}
				}
			}
			break;
		case ITEMATTACH_USEWEAPONUPDRESS:
			{
				if(pclItemInfo[toref]->siUpgradeSkillType & UPGRADESKILLTYPE_USEWEAPON)
				{
					/// �ø� �� �ִ� �ѵ��� �־�� ����. 
					if (type == ITEMTYPE_DRESS || type == ITEMTYPE_HAT)
					{
						if(pclItemInfo[toref]->clItem.clItemArmour.uiSkillUp)
						{
							return TRUE;
						}
					}
					else
					{
						if(pclItemInfo[toref]->clItem.clItemStatusArmour.uiSkillUp)
						{
							return TRUE;
						}
					}
				}
			}
			break;

		default:
			{
				SI64 typeattach = pclItemTypeInfo[type]->siAttach;

				if(typeattach & adaptattach) return TRUE;
			}
			break;
	}
	

	return FALSE;


}

// unique�� �ٰŷ� �̸��� ���Ѵ�. 
const TCHAR* cltItemManagerCommon::GetName(SI32 siunique)
{
	if(siunique == 0)return NULL;

	// �������� ref�� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return NULL;

	return pclItemInfo[ref]->GetName();
}



// �̹����� �ε����� �����´�. 
SI32 cltItemManagerCommon::						GetImage(SI32 siunique)
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref > 0)
	{
		return pclItemInfo[ref]->siImageIndex;
	}

	return 0;
}

// ������ ���� ������ ������Ű���� Ȯ���Ѵ�. 
// 2003.10.23
bool cltItemManagerCommon::CheckCondition(SI32 siitemunique, cltCharCommon* pclchar, SI32* returnval)
{
	SI32 ref = FindItemRefFromUnique(siitemunique);
	if(ref <= 0)return false;

	SI32 totalskilllevel = 0;
	if(pclItemInfo[ref]->clCondition.siSkillKind)
	{
		totalskilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(pclItemInfo[ref]->clCondition.siSkillKind, 0, 0, &pclchar->pclCI->clCharItem.clItem[0], pclchar->GetID());
	}

	// ��ų �ʿ���� ���� ����Ʈ ����� ������ ��ų ������ 10���� ����
	if ( totalskilllevel < 10 )
	{
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_FISHNOSKILL;
		if(pclchar->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			totalskilllevel = 10;
		}
	}

	// ��ȯ���ΰ�� ��ų������ ������ 100����
	if ( IDENTITY_PERSON_SUMMON == pclchar->clIdentity.siIdentity )
	{
		totalskilllevel = 100;
	}
	
	// [����] ������ üũ�� �� ����
	SI32 siHndOrLuk = 0;
	if ( pclClient->IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
	{
		siHndOrLuk = pclchar->clPB.clTotalBA.GetLuk();
	}
	else
	{
		siHndOrLuk = pclchar->clPB.clTotalBA.GetHnd();
	}

	// ��ü�ɷ�ġ�� �������� ���� ���¿��� �ɷ�ġ�� ������ ���� �ʵ��� �Ѵ�. - by LEEKH 2009-03-20
	if( pclchar->clPB.bSetTotalBA == false )
	{
		siHndOrLuk = MAX_SI32;

		return pclItemInfo[ref]->clCondition.Check(pclItemInfo[ref]->siType,
			pclchar->GetKind(),
			pclchar->pclCI->clIP.GetLevel(), 
			MAX_SI32,
			MAX_SI32,
			MAX_SI32,
			MAX_SI32,
			siHndOrLuk,
			totalskilllevel, 
			pclchar->pclCI->clIP.siFameLevel,
			returnval);
	}

	return pclItemInfo[ref]->clCondition.Check(pclItemInfo[ref]->siType,
		pclchar->GetKind(),
		pclchar->pclCI->clIP.GetLevel(), 
		pclchar->clPB.clTotalBA.GetStr(),
		pclchar->clPB.clTotalBA.GetDex(),
		pclchar->clPB.clTotalBA.GetMag(),
		pclchar->clPB.clTotalBA.GetVit(),
		siHndOrLuk,
		totalskilllevel, 
		pclchar->pclCI->clIP.siFameLevel,
		returnval);
}

/*
bool cltItemManagerCommon::CheckCondition(SI32 siitemunique, cltSummon* pclsummon, SI32* returnval,SI32 addstr,SI32 adddex,SI32 addmag)
{
	SI32 ref = FindItemRefFromUnique(siitemunique);
	if(ref <= 0)return false;

	if(pclsummon == NULL)return false;

	//----------------------------------------------
	// �ڰ��� �Ǵ� ��ȯ �������Ը� ���� �� �ִ�.
	//----------------------------------------------
	if(pclsummon->siKind == 0 || pclClient->pclKindInfoSet->pclKI[pclsummon->siKind] == NULL 
		|| pclClient->pclKindInfoSet->pclKI[pclsummon->siKind]->bSummonMall == false)
	{
		*returnval = ITEMEQUIP_FAIL_NOSUMMONHERO;
		return false;
	}

	SI32 limitlevel = 100 ;
#ifdef _DEBUG
	limitlevel = 1 ;
#endif
	if(pclsummon->clIP.GetLevel() < limitlevel )
	{
		*returnval = ITEMEQUIP_FAIL_OUTOFSUMMONLEVEL;
		return false;
	}


	SI32 totalskilllevel = 100;

	return pclItemInfo[ref]->clCondition.Check(pclItemInfo[ref]->siType,
		pclsummon->siKind,
		pclsummon->clIP.GetLevel(), 
		addstr,
		adddex,
		addmag,
		pclsummon->clIP.GetVit(),
		0,
		totalskilllevel, 
		100,		// �� ������ 100���� �������ش�. (��� ���� �� ���� �� �ִ�. ) 
		returnval);

}
*/
// ��ȯ���� �ش� �������� ���� ��������				
bool cltItemManagerCommon::CheckConditionForSummon( IN cltCharCommon* pclChar, IN SI32 siItemUnique, IN cltSummon *pclsummon, IN cltItem* pclItemList, OUT SI32 *psiReturnValue )
{
	if ( (NULL == pclsummon) || (NULL == psiReturnValue) )
	{
		return false;
	}

	if ( pclsummon->siStatus != SUMMON_STATUS_TAKEOUT )
	{
		return false;
	}
	
	SI32 siRef = FindItemRefFromUnique( siItemUnique );
	if ( 0 >= siRef )
	{
		return false;
	}

	SI32 siSummonID = pclChar->GetSummonID();
	if ( false == pclClient->pclCM->IsValidID(siSummonID) )
	{
		return false;
	}

	cltCharCommon* pclSummonChar = (cltCharCommon*)pclClient->pclCM->CR[siSummonID];
	if ( NULL == pclSummonChar )
	{
		return false;
	}

	bool bCheckLimitForLevel	= false;
	//SI32 siSummonLevel			= pclsummon->clIP.GetLevel();
	SI16 siAttackWearStoneNum	= pclsummon->siAttackWearStoneNum;
	SI16 siDefenseWearStoneNum	= pclsummon->siDefenseWearStoneNum;

	// ��񼮿� ���� ���� �˻�� �Ʒ����� �ϰ� ���⿡���� �ܼ��� �ִ��� �������� �˻�
	if ( (0 < siAttackWearStoneNum) || (0 < siDefenseWearStoneNum) )
	{
		bCheckLimitForLevel = true;
	}

	// �������ɷ����� ����
	/*
	// ��񼮰��������� �������� �ʰ�, ��� �����Ҽ����� �ּҷ������� ������ 
	if ( (false == bCheckLimitForLevel) && (SUMMON_EQUIP_LIMITMINLEVEL > siSummonLevel) )
	{
		*psiReturnValue = ITEMEQUIP_FAIL_OUTOFSUMMONLEVEL;
		return false;
	}
	*/

	// ��ȯ�� Kind Info ��������
	cltKindInfo* pclki = NULL;
	cltGMCommandKindInfo* pclGMki = NULL;

	if ( pclClient->IsCountrySwitch(Switch_Summon_Separate) ) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[pclsummon->siKind];
		pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pclsummon->siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[pclsummon->siKind];
		pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pclsummon->siKind];
	}

	if ( NULL == pclki )
	{
		return false;
	}

	if ( NULL == pclGMki)
	{
		return false;
	}

	// ��ȯ�� ��� ����Ÿ�� �˻�
	SI16 siSummonEquipType	= pclki->siSummonEquip;
	SI32 siItemType			= pclItemInfo[siRef]->siType;
	SI32 siNeedLevel		= pclItemInfo[siRef]->clCondition.siLevel;


	// ��� ������ �� ���� ��ȯ�����
	if ( SUMMON_EQUIPTYPE_NONE == siSummonEquipType )
	{
		return false;
	}

	// ������ Ÿ�Կ� ���� ���뿩��
	switch	( siItemType ) 
	{
		// �ٰŸ� �����϶��� ��� ����Ÿ���� �˻��Ѵ�
		case ITEMTYPE_SWORD:
		case ITEMTYPE_SPEAR:
		case ITEMTYPE_AXE:
			{
				if ( SUMMON_EQUIPTYPE_FARDISTANCE != siSummonEquipType )
				{
					*psiReturnValue = ITEMEQUIP_FAIL_WRONGEQUIPTYPE;
					return false;
				}

				else if ( /*(SUMMON_EQUIP_LIMITMINLEVEL > siSummonLevel) && */(siNeedLevel > siAttackWearStoneNum) )
				{
					*psiReturnValue = ITEMEQUIP_FAIL_NOTENOUGHSTONE;
					return false;
				}
			}
			break;

		// ���Ÿ� �����϶��� ��� ����Ÿ���� �˻��Ѵ�
		case ITEMTYPE_BOW:
		case ITEMTYPE_GUN:
		case ITEMTYPE_STAFF:
			{
				if ( SUMMON_EQUIPTYPE_LONGDISTANCE != siSummonEquipType )
				{
					*psiReturnValue = ITEMEQUIP_FAIL_WRONGEQUIPTYPE;
					return false;
				}

				if ( /*(SUMMON_EQUIP_LIMITMINLEVEL > siSummonLevel) && */(siNeedLevel > siAttackWearStoneNum) )
				{
					*psiReturnValue = ITEMEQUIP_FAIL_NOTENOUGHSTONE;
					return false;
				}
			}
			break;

		// ��
		case ITEMTYPE_HELMET:
		case ITEMTYPE_ARMOUR:
		case ITEMTYPE_BELT:
		case ITEMTYPE_SHOES:
		case ITEMTYPE_MANTLE:
			{
				if ( /*(SUMMON_EQUIP_LIMITMINLEVEL > siSummonLevel) && */(siNeedLevel > siDefenseWearStoneNum) )
				{
					*psiReturnValue = ITEMEQUIP_FAIL_NOTENOUGHSTONE;
					return false;
				}
			}
			break;

	}
	
	// �������� ���������� �����Ҽ��ִ��� �˻�
	cltParametaBox	clPB;
	cltPIPInfo		clPIPInfo;

	clPIPInfo.Set( &pclsummon->clIP );
	clPB.Init( pclClient->pclItemManager, &clPIPInfo, NULL, pclki, pclGMki );

	clPB.Action( pclSummonChar, 0, PERSONITEM_WEAPON1, pclItemList, &pclSummonChar->pclCI->clHorseInfo, &pclSummonChar->pclCI->clHealthInfo, &pclSummonChar->pclCI->clCharSkill, &pclSummonChar->clIdentity, siAttackWearStoneNum, siDefenseWearStoneNum, GAMEMODE_CLIENT, true );
	
	return pclItemInfo[siRef]->clCondition.Check(pclItemInfo[siRef]->siType,
		pclsummon->siKind,
		pclsummon->clIP.GetLevel(), 
		clPB.clTotalBA.GetStr(),
		clPB.clTotalBA.GetDex(),
		clPB.clTotalBA.GetMag(),
		pclsummon->clIP.GetVit(),
		0,
		100,		// ��ų������ ������� ������ �� �ִ�
		100,		// �� ������ 100���� �������ش�. (��� ���� �� ���� �� �ִ�. ) 
		psiReturnValue);


}

bool cltItemManagerCommon::IsCanEquipItemPosForSummon( SI32 siEquipPosition, SI32 siItemUnique )
{
	switch ( siEquipPosition ) 
	{
		// ���� ������ ������ ��ġ
		case PERSONITEM_HELMET:		// ����
		case PERSONITEM_ARMOUR:		// ����
		case PERSONITEM_WEAPON1:	// ����1
		case PERSONITEM_BELT:		// ��Ʈ
		case PERSONITEM_SHOES:		// �Ź�
		case PERSONITEM_MANTLE:		// ����
			{
				return true;
			}
			break;

		case PERSONITEM_WEAPON2:	// ����2 ����â�� �Ѿ˰� ȭ�츸
			{
				switch ( siItemUnique )
				{
				case ITEMUNIQUE(7850):	// ȭ��
				case ITEMUNIQUE(7855):	// �Ѿ�
				case ITEMUNIQUE(13600):	// ����ȭ��
				case ITEMUNIQUE(13601):	// ����ȭ��
					{
						return true;
					}
					break;
				}
			}
			break;
	}

	return false;
}

// iconcode�� �ٰŷ� 
SI32 cltItemManagerCommon::FindBitmapIndex(TCHAR* typecode, TCHAR* iconcode)
{
	TCHAR buffer[256];

	StringCchPrintf(buffer, 256, TEXT("Item\\%s\\%s.bmp"), typecode, iconcode);
	return GetBitmapIndexFromBitmapName(buffer);

}


// ������(��)�� ġ���� �� �ִ� ������ �����Ѵ�. 
void cltItemManagerCommon::ConnectDisease( cltDiseaseManager *pcldiseasemanager)
{
	SI32 i = 0;
	
	for ( i = 0; i < MAX_ITEMINFO_NUMBER; ++i )
	{
		if ( pclItemInfo[ i ] )
		{
			if ( _tcscmp( pclItemInfo[ i ]->szDiseaseName, TEXT("") ) != 0
			&&	 _tcscmp( pclItemInfo[ i ]->szDiseaseName, TEXT("NULL") ) != 0)
			{		
				pclItemInfo[ i ]->siDiseaseUnique = pcldiseasemanager->FindUniqueFromName( pclItemInfo[ i ]->szDiseaseName );
			}
		}
	}
	
	return;
}

// ������(��)�� ġ���� �� �ִ� ����Ÿ���� �����Ѵ�. 
void cltItemManagerCommon::ConnectDiseaseType( cltDiseaseManager *pcldiseasemanager)
{
	SI32 i = 0;

	for ( i = 0; i < MAX_ITEMINFO_NUMBER; ++i )
	{
		if ( pclItemInfo[ i ] )
		{
			if ( _tcscmp( pclItemInfo[ i ]->szDiseaseType, TEXT("") ) != 0
				&&	 _tcscmp( pclItemInfo[ i ]->szDiseaseType, TEXT("NULL") ) != 0)
			{	
				// �������� ������ ���̺��� �ش� ������ ���� ����ũ = �������̺��� �����̸�.
				pclItemInfo[ i ]->siDiseaseUnique = pcldiseasemanager->FindUniqueFromDiseaseType( pclItemInfo[ i ]->szDiseaseType );
			}
		}
	}

	return;
}

// ������ �����Ѵ�. 
bool cltItemManagerCommon::Enchant(cltItem* pequipclitem, SI32 scrollunique, SI32* prtnval, SI32* ppara1, SI32* ppara2)
{
	if(scrollunique <= 0)return false;

	// ������ ������ Ȯ���Ѵ�. 
	cltItemInfo* pclscrollinfo = FindItemInfo(scrollunique);
	if(pclscrollinfo == NULL)return false;

	// ������ ����� Ȯ���Ѵ�. 
	SI32 function	= pclscrollinfo->siScrollFunction;
	if(function <= 0)return false;

	SI32 ability	= pclscrollinfo->siScrollAbility;
	if(ability <= 0)return false;

	// �� �������� ������ ��ɿ� �����ϴ°� ?
	if(CanItemAttach(scrollunique, pequipclitem->siUnique)== FALSE)
	{
		*prtnval	= ENCHANT_FAIL_REASON_NOTATBMATCH;
		*ppara1		= pclscrollinfo->siScrollMax;
		*ppara2		= 0;
		return false;
	}

	//==================================================================
	// �ִ� �������� �����ִ� Scroll �̶�� ���� Scroll �ý��ۿ� �������� �ʴ´�.
	//==================================================================
	if(pclscrollinfo->siScrollAdaptAttach == ITEMATTACH_DURABLE)
	{
		UI32 uiMaxDurability = (UI32)pclClient->GetGlobalValue( TEXT("GV_MaxDurability") );
		if(pequipclitem->clItemCommon.clCommonInfo.uiMaxDurability >= (uiMaxDurability/2))
		{
			*prtnval	= ENCHANT_FAIL_REASON_NOMORE;
			*ppara1		= uiMaxDurability/2;
			*ppara2		= 2;		
			return false;
		}

		if ( pequipclitem->GetType(pclClient->pclItemManager) == ITEMTYPE_DRESS ||
			pequipclitem->GetType(pclClient->pclItemManager) == ITEMTYPE_HAT ||
			pequipclitem->GetType(pclClient->pclItemManager) == ITEMTYPE_NECK )
		{
			*prtnval	= ENCHANT_FAIL_REASON_NOTATBMATCH;
			*ppara1		= pclscrollinfo->siScrollMax;
			*ppara2		= 0;
			return false;
		}

		// 11 Bit �����Ͱ� ������ �ִ� �ִ� �������� ���� �ʵ��� �Ѵ�.
		SI32 siMaxDurabe = min(uiMaxDurability, (UI32)(pequipclitem->clItemCommon.clCommonInfo.uiMaxDurability + ability));
		pequipclitem->clItemCommon.clCommonInfo.uiMaxDurability = siMaxDurabe;
		return true;
	}
	//==================================================================

	// �� �������� �������� �����.
	if((SI32)pequipclitem->GetDurability()  <= pclscrollinfo->siScrollDecDuration)return false;
	pequipclitem->DecreaseDurability(this, pclscrollinfo->siScrollDecDuration);

	SI32 siEnchantMax = 0;
	if(pclscrollinfo->siScrollAdaptAttach == ITEMATTACH_SKILLUPDRESS)
	{
		cltItemInfo* pcllinfo = FindItemInfo(pequipclitem->siUnique);
		if(pcllinfo == NULL)return false;
		siEnchantMax = pequipclitem->clItemArmour.uiSkillUp * 10;
		*ppara2		 = 1;
	}
	else if(pclscrollinfo->siScrollAdaptAttach == ITEMATTACH_USEWEAPONUPDRESS)
	{
		cltItemInfo* pcllinfo = FindItemInfo(pequipclitem->siUnique);
		if(pcllinfo == NULL)return false;
		siEnchantMax = pequipclitem->clItemArmour.uiSkillUp * 10;
		*ppara2		 = 1;
	}

	else
	{
		siEnchantMax	= pclscrollinfo->siScrollMax;
		*ppara2		 = 0;
	}

	SI32 temp;
	
	// ���� ����� �̹� �ִٸ� 
	if((SI32)pequipclitem->clItemCommon.clOptionInfo.uiType1 == function)
	{
		temp = pequipclitem->clItemCommon.clOptionInfo.uiPara1;
		temp += ability;

		if(temp > siEnchantMax)
		{
			*prtnval	= ENCHANT_FAIL_REASON_NOMORE;
			*ppara1		= siEnchantMax;
			return false;
		}

		temp = min(1000, temp);

		pequipclitem->clItemCommon.clOptionInfo.uiPara1 = temp;
		
	}
	else if((SI32)pequipclitem->clItemCommon.clOptionInfo.uiType2 == function)
	{
		temp = pequipclitem->clItemCommon.clOptionInfo.uiPara2;
		temp += ability;

		if(temp > siEnchantMax)
		{
			*prtnval	= ENCHANT_FAIL_REASON_NOMORE;
			*ppara1		= siEnchantMax;
			return false;
		}

		temp = min(1000, temp);

		pequipclitem->clItemCommon.clOptionInfo.uiPara2 = temp;
	}
	else if(pequipclitem->clItemCommon.clOptionInfo.uiType1 == 0)
	{
		pequipclitem->clItemCommon.clOptionInfo.uiType1	= function;

		temp = min(1000, ability);

		pequipclitem->clItemCommon.clOptionInfo.uiPara1	= temp;

	}
	else if(pequipclitem->clItemCommon.clOptionInfo.uiType2 == 0)
	{

		pequipclitem->clItemCommon.clOptionInfo.uiType2	= function;

		temp = min(1000, ability);

		pequipclitem->clItemCommon.clOptionInfo.uiPara2	= temp;
	}
	else
	{
		*prtnval	= ENCHANT_FAIL_REASON_NOMOREKIND;
		*ppara1		= siEnchantMax;
		return false;
	}

	return true;
}

// Ư�� ��ǰ�� Ư�� ĳ���Ͱ� ���鶧 ǰ�� ������ ���Ѵ�. 
SI32 cltItemManagerCommon::GetQualityRate(SI32 itemunique, SI32 id, SI32* addlevel)
{
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return 0;

	SI32 qualityrrate = 100;

	//--------------------------------------------
	// ����� ���� ǰ�� ���� ���� 
	//--------------------------------------------
	SI32 needskillunique	= pclItemInfo[ref]->clSkillInfo.siSkill;
	if(needskillunique > 0)
	{
		//-------------------------------------------
		// ������ ���ۿ� �ʿ��� ��ų������ ĳ������ ��Ű������ ���̸� ���Ѵ�.
		//-------------------------------------------
		SI32 skilllevel			= pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0]);
		*addlevel			= max(0, ( skilllevel - pclItemInfo[ref]->clSkillInfo.siSkillLevel));

		//-------------------------------------------
		// �����ֿ� ���� ǰ�� ���� ���� 
		//-------------------------------------------
		SI32 addhnd;

		//-------------------------------------------
		// ���� Ȱ��ȭ ���濡 ���� ������ ���� ���
		//-------------------------------------------
		if(pclClient->IsCountrySwitch(Switch_ManufactureRevitalize))
		{
			if( pclClient->IsCountrySwitch(Switch_HealthAddChange) )
				addhnd =  pclClient->pclCM->CR[id]->clPB.clTotalBA.GetLuk();
			else
				addhnd =  pclClient->pclCM->CR[id]->clPB.clTotalBA.GetHnd();
		}
		else
		{
			if( pclClient->IsCountrySwitch(Switch_HealthAddChange) )
				addhnd =  pclClient->pclCM->CR[id]->clPB.clTotalBA.GetLuk();
			else
			{
				SI32 needhnd	=  pclItemInfo[ref]->clSkillInfo.siHnd;
				addhnd =  max(0, pclClient->pclCM->CR[id]->clPB.clTotalBA.GetHnd() - needhnd);
			}
		}

		if(*addlevel > 8)
		{
			qualityrrate += 25;
		}
		else	
		{
			qualityrrate += ( *addlevel ) * 3;
		}

		// �����ָ� 1000�ڸ����ʹ�!!(���̳��� �����ָ� 1000�ڸ��� �о��ش�. ���߿� 1000�� ������ ���� �˾Ƴ���)
		(*addlevel) += 1000*addhnd;
	}

	return min(125, qualityrrate);
	/*	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return 0;

	SI32 qualityrrate = 100;

	//--------------------------------------------
	// ����� ���� ǰ�� ���� ���� 
	//--------------------------------------------
	SI32 needskillunique	= pclItemInfo[ref]->clSkillInfo.siSkill;
	if(needskillunique > 0)
	{
	SI32 skilllevel			= pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0]);
	*addlevel			= max(0, ( skilllevel - pclItemInfo[ref]->clSkillInfo.siSkillLevel));

	if(addlevel > 35)
	{
	qualityrrate += ( (addlevel - 35) * 5 / 10);
	addlevel = 35;
	}

	if(addlevel > 30)
	{
	qualityrrate += ( (addlevel - 30) * 10 / 10);
	addlevel = 30;
	}

	qualityrrate  += (addlevel * 15 / 10);	// ��ų�� 1.5�ۼ�Ʈ Ȯ���� ���� ���. 			
	}


	//-------------------------------------------
	// �����ֿ� ���� ǰ�� ���� ���� 
	//-------------------------------------------
	SI32 needhnd	=  pclItemInfo[ref]->clSkillInfo.siHnd;
	SI32 addhnd		=  max(0, pclClient->pclCM->CR[id]->clPB.clTotalBA.GetHnd() - needhnd);

	if(addhnd > 150)
	{
	qualityrrate	+= (addhnd - 150) * 2 / 50;
	addhnd		= 150;
	}

	if(addhnd > 100)
	{
	qualityrrate	+= (addhnd - 100) * 5 / 50;
	addhnd		= 100;
	}

	qualityrrate    += (addhnd * 10 / 50);	// �׿� �������� 1/5�� ����� �׻� ���Ĵ�. 

	return min(200, qualityrrate);
	*/
}

// ���� ���ο� ������ ������ ��´�. 
bool cltItemManagerCommon::GetForeignNPCItemInfo(SI32 itemtype, SI32* punique, GMONEY* pprice, SI32* pitemnum)
{
	SI32 i;
	cltItemPriceUnit* pclprice;
	SI32 itemlistnum = 0;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)continue;

		// ���� Ÿ���� �������� ã�´�. 
		if(pclItemInfo[i]->siType != itemtype)continue;
		
		// ���� ���Ῡ���� �ȵȴ�. 
		if(pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique == 0)continue;
		
		pclprice = GetCurrentPrice(pclItemInfo[i]->clItem.siUnique);
		if(pclprice == NULL)continue;

		GMONEY price = pclprice->siPrice;
		if(price <= 10)price = 10;

		cltServer* pclserver = (cltServer*)pclClient;

		if (pclserver->pclMinisterMgr == NULL)
			return FALSE;
		CMinisterIzo* pclminister = (CMinisterIzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_IZO);
		SI32 rate = min(75, max(50, pclminister->m_siPriceValue));

		// ������ ���� �l �ִ� ������ Ȯ���Ѵ�. 
		if(itemlistnum < *pitemnum )
		{
			punique[itemlistnum]		= pclItemInfo[i]->clItem.siUnique;

			if(pclItemTypeInfo[itemtype]->siAtb & ITEMATB_OBJECT)
			{
				// ������ �ü��� 75%
				pprice[itemlistnum]			= max(1,(GMONEY)(((REAL64)price/100)*rate));
			}
			else
			{
				// ������ �ü��� 75%
				pprice[itemlistnum]			= max(1,(GMONEY)(((REAL64)price/100)*rate));

			}
			


			itemlistnum++;
		}
	}

	if(itemlistnum <= 0)return false;

	*pitemnum = itemlistnum;

	return true;
}

// ��ǰ �ü��� �����Ѵ�. 
void cltItemManagerCommon::CalcItemPrice( _SYSTEMTIME sTime)
{
	SI32 i, j;
	static DWORD dwLastLowPriceCheckClock = 0;
	//static bool bcheckcnppricerateswitch = false;
	//cyj �����⵿�� ������ �ü� ������ ����ϵ���
	static bool bFirstCheck = false;
	cltServer *pclserver = (cltServer*)pclClient;
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( pclserver->bCompleteDBInitAll == FALSE )		return;


	if(dwLastLowPriceCheckClock == 0)
	{
		dwLastLowPriceCheckClock = pclClient->CurrentClock;
	}

	// �̵��� �����ֹ� ������ �����Ͽ� �ü��� �����Ѵ�. 
	bool bchecklowpriceswitch = false;
	DWORD checktime = 3600000 ;	// 1�ð� ����. 

#ifdef _DEBUG
	checktime = 60000 ; // 1�� ����
#endif

	if((DWORD)TABS(pclClient->CurrentClock - dwLastLowPriceCheckClock) > checktime)
	{
		dwLastLowPriceCheckClock = pclClient->CurrentClock; 
		bchecklowpriceswitch = true;
	}

	for(i = 1;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i])
		{
			SI32 itemunique = pclItemInfo[i]->clItem.siUnique;
			SI32 type		= pclItemInfo[i]->siType;

			// OBJECT TYPE�� �������� ���ü��� ������� �ü��� ����Ѵ�. - ����̴� �����Ѵ�.
			// ��Ƽ��Ʈ ����ü�� OBJECT TYPE ó�� �ü��� ����Ѵ�.
			if( (pclItemTypeInfo[type]->IsAtb(ITEMATB_OBJECT) == TRUE && type != ITEMTYPE_NECK) ||
				(type == ITEMTYPE_CRYSTAL) )
			{
				// ����� �ü� ������ ��� ���Ѵ�.
				GMONEY sum = 0;
				for(j = 0;j < MAX_MATERIAL_NUMBER;j++)
				{
					SI32 materialunique = pclItemInfo[i]->clProductionInfo.clMaterial[j].siUnique;
					if(materialunique)
					{
						cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, materialunique);
						if(pclprice)
						{
							sum += (pclprice->siPrice * pclItemInfo[i]->clProductionInfo.clMaterial[j].siNeedNum);
						}
					}
				}

				// �����ۿ� ���� ������ �����Ѵ�.
				pclItemPrice->SetPrice(this, itemunique, sum, 100, true);				
			}
			// ������Ʈ ��ǰ�� �ƴ� ���. - ����� ����
			else 
			{
				// �̵��� �����ֹ� ������ �����Ͽ� �ü��� �����Ѵ�. - 1�ð��� �ѹ� ����ȴ�.
				if(bchecklowpriceswitch == true || bFirstCheck == false)
				{
					GMONEY	price; 
					SI32	amount;

					if(pclClient->pclMarketManager->FindLowPriceOrderInfo(itemunique, &price, &amount) == false)	continue;

					cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, itemunique);
					if(pclprice == NULL)continue;

					// ���� ���� ���Ϸδ� �������� �ʴ´�. 
					price = max(MIN_ITEM_PRICE, price);

					// ���� ������ ���� �ü����� ���ٸ�, 
					if(price  > pclprice->siPrice)
					{
						if(pclprice->siPrice > 100)	
						{
							pclprice->fPrice	= pclprice->fPrice * 1.005f;	// 0.5% �����ش�. 
						}
						else 
						{
							pclprice->fPrice	= pclprice->fPrice * 1.1f;		// 10% �����ش�. 
						}

						GMONEY siOldPrice = pclprice->siPrice;		// pricebug�� ���õ� �ڵ�� ���� ���� ���� ��� ��������

						pclprice->siPrice	= (SI64)pclprice->fPrice;

						// ���������� �����غ��� KKM
						if( 5055 == pclprice->siUnique )
						{
							((cltServer*)pclClient)->pclLog->FilePrint( "price1.txt", "%I64d	%f	%I64d", siOldPrice, pclprice->fPrice, pclprice->siPrice );
						}					

						// DB�� �����Ѵ�. 
						const TCHAR* pszItemName = pclClient->pclItemManager->GetName(pclprice->siUnique);
						sDBRequest_SetItemPrice clMsg(pclprice->siUnique, pclprice->siPrice, pclprice->fPrice, pclprice->siItemNum, pszItemName);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
					// ���� ������ ���� �ü����� ���ٸ�, 
					else if(price  < pclprice->siPrice)
					{
						if(price < 1000000 )
						{
							pclprice->fPrice	= pclprice->fPrice * 0.99f;		// 1% �����ش�. 
						}
						else 
						{
							pclprice->fPrice	= pclprice->fPrice * 0.95f;		// 5% �����ش�. 
						}

						GMONEY siOldPrice = pclprice->siPrice;	// pricebug�� ���õ� �ڵ�� ���� ���� ���� ��� ��������

						pclprice->siPrice	= (SI64)pclprice->fPrice;

						// ���������� �����غ��� KKM
						if( 5055 == pclprice->siUnique )
						{
							((cltServer*)pclClient)->pclLog->FilePrint( "price2.txt", "%I64d	%f	%I64d", siOldPrice, pclprice->fPrice, pclprice->siPrice );
						}

						// DB�� �����Ѵ�. 
						const TCHAR* pszItemName = pclClient->pclItemManager->GetName(pclprice->siUnique);
						sDBRequest_SetItemPrice clMsg(pclprice->siUnique, pclprice->siPrice, pclprice->fPrice, pclprice->siItemNum, pszItemName);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
				}
			}
		}
	}

	//----------------------------------------------------
	// ��� ������ ���Ѵ�. (����.) 
	//----------------------------------------------------
	INT64 sum		= 0;
	SI32 itemindex	= 0;
	for( i = 1;i < MAX_ITEMINFO_NUMBER;i++ )
	{
		if(pclItemInfo[i])
		{
			SI32 itemunique = pclItemInfo[i]->clItem.siUnique;

			cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, itemunique);
			if(pclprice == NULL)continue;
			if(pclprice->siPrice < 100)continue;			// �ʹ� �� ��ǰ�� ����
			if(pclprice->siPrice > 200000000)continue;	// �ʹ� ��� ��ǰ�� ����

			sum += pclprice->siPrice;
			itemindex++;
		}
	}
	
	// ���ո����� �ü��� npcrate�� ������ �ְ� �Ѵ�.
	if( pclClient->IsCountrySwitch( Switch_NewMarket ) )
	{
		for( i = 1; i < MAX_ITEMINFO_NUMBER; i++ )
		{
			if(pclItemInfo[i])
			{
				SI32 itemunique = pclItemInfo[i]->clItem.siUnique;

				cltItemPriceUnit* pclprice = pclItemNewPrice->GetPrice(this, itemunique);
				if(pclprice == NULL)				continue;
				if(pclprice->siPrice < 100)			continue;	// �ʹ� �� ��ǰ�� ����
				if(pclprice->siPrice > 200000000)	continue;	// �ʹ� ��� ��ǰ�� ����

				sum += pclprice->siPrice;
				itemindex++;
			}
		}
	}
	
	if(itemindex)
	{
		//clItemStatistic.siItemPriceIndex = sum / itemindex;
		//[����] ���ո��� ���� ���ĺ���.
		clItemStatistic.siItemPriceIndex = (sum / itemindex) * 0.8;
		

		//KHY - NPCRATE Ȯ�� - �ӽ� �ڵ� - �ź� 25�ʿ� ��������, �Ϸ翡 �ѹ��� ����ȴ�.
		if((sTime.wHour == 0)&&(sTime.wMinute == 0)&&(clItemStatistic.bLastNPCPriceRateDaySwitch == true))
		{
			clItemStatistic.bLastNPCPriceRateDaySwitch = false;
		}

	
		// ������ �ü��� �ѹ��� �����ȴ�.
		if((pclClient->GetFrame() > 500 && m_bcheckcnppricerateswitch == false)||(clItemStatistic.bLastNPCPriceRateDaySwitch == false))
		{
			m_bcheckcnppricerateswitch = true;
			bFirstCheck = true;
			clItemStatistic.bLastNPCPriceRateDaySwitch = true;
			
			if(clItemStatistic.siItemPriceIndex		 < 100000)	clItemStatistic.siNPCPriceRate = 100;
			else if(clItemStatistic.siItemPriceIndex < 150000)	clItemStatistic.siNPCPriceRate = 110;
			else if(clItemStatistic.siItemPriceIndex < 200000)	clItemStatistic.siNPCPriceRate = 120;
			else if(clItemStatistic.siItemPriceIndex < 250000)	clItemStatistic.siNPCPriceRate = 130;
			else if(clItemStatistic.siItemPriceIndex < 300000)	clItemStatistic.siNPCPriceRate = 140;
			else if(clItemStatistic.siItemPriceIndex < 350000)	clItemStatistic.siNPCPriceRate = 150;
			else if(clItemStatistic.siItemPriceIndex < 400000)	clItemStatistic.siNPCPriceRate = 160;
			else if(clItemStatistic.siItemPriceIndex < 450000)	clItemStatistic.siNPCPriceRate = 170;
			else if(clItemStatistic.siItemPriceIndex < 500000)	clItemStatistic.siNPCPriceRate = 180;
			else if(clItemStatistic.siItemPriceIndex < 550000)	clItemStatistic.siNPCPriceRate = 190;
			else if(clItemStatistic.siItemPriceIndex < 600000)	clItemStatistic.siNPCPriceRate = 200;
			else if(clItemStatistic.siItemPriceIndex < 650000)	clItemStatistic.siNPCPriceRate = 210;
			else if(clItemStatistic.siItemPriceIndex < 700000)	clItemStatistic.siNPCPriceRate = 220;
			else if(clItemStatistic.siItemPriceIndex < 800000)	clItemStatistic.siNPCPriceRate = 240;
			else if(clItemStatistic.siItemPriceIndex < 900000)	clItemStatistic.siNPCPriceRate = 260;
			else if(clItemStatistic.siItemPriceIndex < 1000000)	clItemStatistic.siNPCPriceRate = 280;
			else if(clItemStatistic.siItemPriceIndex < 1100000)	clItemStatistic.siNPCPriceRate = 300;
			else if(clItemStatistic.siItemPriceIndex < 1200000)	clItemStatistic.siNPCPriceRate = 320;
			else if(clItemStatistic.siItemPriceIndex < 1300000)	clItemStatistic.siNPCPriceRate = 340;
			else if(clItemStatistic.siItemPriceIndex < 1400000)	clItemStatistic.siNPCPriceRate = 360;
			else if(clItemStatistic.siItemPriceIndex < 1500000)	clItemStatistic.siNPCPriceRate = 380;
			else if(clItemStatistic.siItemPriceIndex < 1600000)	clItemStatistic.siNPCPriceRate = 400;
			else if(clItemStatistic.siItemPriceIndex < 1700000)	clItemStatistic.siNPCPriceRate = 420;
			else if(clItemStatistic.siItemPriceIndex < 1800000)	clItemStatistic.siNPCPriceRate = 440;
			else if(clItemStatistic.siItemPriceIndex < 1900000)	clItemStatistic.siNPCPriceRate = 460;
			else if(clItemStatistic.siItemPriceIndex < 2000000)	clItemStatistic.siNPCPriceRate = 480;
			else if(clItemStatistic.siItemPriceIndex < 2100000)	clItemStatistic.siNPCPriceRate = 500;
			else if(clItemStatistic.siItemPriceIndex < 2200000)	clItemStatistic.siNPCPriceRate = 520;
			else if(clItemStatistic.siItemPriceIndex < 2300000)	clItemStatistic.siNPCPriceRate = 540;
			else if(clItemStatistic.siItemPriceIndex < 2400000)	clItemStatistic.siNPCPriceRate = 560;
			else if(clItemStatistic.siItemPriceIndex < 2500000)	clItemStatistic.siNPCPriceRate = 580;
			else if(clItemStatistic.siItemPriceIndex < 2600000)	clItemStatistic.siNPCPriceRate = 600;
			else if(clItemStatistic.siItemPriceIndex < 2700000)	clItemStatistic.siNPCPriceRate = 620;
			else if(clItemStatistic.siItemPriceIndex < 2800000)	clItemStatistic.siNPCPriceRate = 640;
			else if(clItemStatistic.siItemPriceIndex < 2900000)	clItemStatistic.siNPCPriceRate = 660;
			else if(clItemStatistic.siItemPriceIndex < 3000000)	clItemStatistic.siNPCPriceRate = 680;
			else if(clItemStatistic.siItemPriceIndex < 3100000)	clItemStatistic.siNPCPriceRate = 700;
			else if(clItemStatistic.siItemPriceIndex < 3200000)	clItemStatistic.siNPCPriceRate = 720;
			else if(clItemStatistic.siItemPriceIndex < 3300000)	clItemStatistic.siNPCPriceRate = 740;
			else if(clItemStatistic.siItemPriceIndex < 3400000)	clItemStatistic.siNPCPriceRate = 760;
			else if(clItemStatistic.siItemPriceIndex < 3500000)	clItemStatistic.siNPCPriceRate = 780;
			else if(clItemStatistic.siItemPriceIndex < 3600000)	clItemStatistic.siNPCPriceRate = 800;
			else if(clItemStatistic.siItemPriceIndex < 3700000)	clItemStatistic.siNPCPriceRate = 820;
			else if(clItemStatistic.siItemPriceIndex < 3800000)	clItemStatistic.siNPCPriceRate = 840;
			else if(clItemStatistic.siItemPriceIndex < 3900000)	clItemStatistic.siNPCPriceRate = 860;
			else if(clItemStatistic.siItemPriceIndex < 4000000)	clItemStatistic.siNPCPriceRate = 880;
			else if(clItemStatistic.siItemPriceIndex < 4100000)	clItemStatistic.siNPCPriceRate = 900;
			else if(clItemStatistic.siItemPriceIndex < 4200000)	clItemStatistic.siNPCPriceRate = 920;
			else if(clItemStatistic.siItemPriceIndex < 4300000)	clItemStatistic.siNPCPriceRate = 940;
			else if(clItemStatistic.siItemPriceIndex < 4400000)	clItemStatistic.siNPCPriceRate = 960;
			else if(clItemStatistic.siItemPriceIndex < 4500000)	clItemStatistic.siNPCPriceRate = 980;
			else if(clItemStatistic.siItemPriceIndex < 5000000)	clItemStatistic.siNPCPriceRate = 1000;
			else if(clItemStatistic.siItemPriceIndex < 5500000)	clItemStatistic.siNPCPriceRate = 1150;
			else if(clItemStatistic.siItemPriceIndex < 6000000)	clItemStatistic.siNPCPriceRate = 1300;
			else if(clItemStatistic.siItemPriceIndex < 6500000)	clItemStatistic.siNPCPriceRate = 1450;
			else if(clItemStatistic.siItemPriceIndex < 7000000)	clItemStatistic.siNPCPriceRate = 1600;
			else if(clItemStatistic.siItemPriceIndex < 7500000)	clItemStatistic.siNPCPriceRate = 1750;
			else if(clItemStatistic.siItemPriceIndex < 8000000)	clItemStatistic.siNPCPriceRate = 1900;
			else if(clItemStatistic.siItemPriceIndex < 8500000)	clItemStatistic.siNPCPriceRate = 2050;
			else if(clItemStatistic.siItemPriceIndex < 9000000)	clItemStatistic.siNPCPriceRate = 2200;
			else if(clItemStatistic.siItemPriceIndex < 9500000)	clItemStatistic.siNPCPriceRate = 2350;
			else if(clItemStatistic.siItemPriceIndex < 10000000)clItemStatistic.siNPCPriceRate = 2500;

			//else 	clItemStatistic.siNPCPriceRate = 3000;
			else if(clItemStatistic.siItemPriceIndex < 11000000)clItemStatistic.siNPCPriceRate = 3000;
			else if(clItemStatistic.siItemPriceIndex < 12000000)clItemStatistic.siNPCPriceRate = 3500;
			else if(clItemStatistic.siItemPriceIndex < 13000000)clItemStatistic.siNPCPriceRate = 4000;
			else if(clItemStatistic.siItemPriceIndex < 14000000)clItemStatistic.siNPCPriceRate = 4500;
			else if(clItemStatistic.siItemPriceIndex < 15000000)clItemStatistic.siNPCPriceRate = 5000;
			else if(clItemStatistic.siItemPriceIndex < 16000000)clItemStatistic.siNPCPriceRate = 5500;
			else if(clItemStatistic.siItemPriceIndex < 17000000)clItemStatistic.siNPCPriceRate = 6000;
			else if(clItemStatistic.siItemPriceIndex < 18000000)clItemStatistic.siNPCPriceRate = 6500;
			else if(clItemStatistic.siItemPriceIndex < 19000000)clItemStatistic.siNPCPriceRate = 7000;
			else if(clItemStatistic.siItemPriceIndex < 20000000)clItemStatistic.siNPCPriceRate = 7500;
			else if(clItemStatistic.siItemPriceIndex < 23000000)clItemStatistic.siNPCPriceRate = 8500;
			else if(clItemStatistic.siItemPriceIndex < 26000000)clItemStatistic.siNPCPriceRate = 9500;
			else if(clItemStatistic.siItemPriceIndex < 29000000)clItemStatistic.siNPCPriceRate = 10500;
			else if(clItemStatistic.siItemPriceIndex < 32000000)clItemStatistic.siNPCPriceRate = 11500;
			else if(clItemStatistic.siItemPriceIndex < 35000000)clItemStatistic.siNPCPriceRate = 12500;
			else if(clItemStatistic.siItemPriceIndex < 38000000)clItemStatistic.siNPCPriceRate = 13500;
			else if(clItemStatistic.siItemPriceIndex < 41000000)clItemStatistic.siNPCPriceRate = 14500;
			else if(clItemStatistic.siItemPriceIndex < 44000000)clItemStatistic.siNPCPriceRate = 15500;
			else if(clItemStatistic.siItemPriceIndex < 47000000)clItemStatistic.siNPCPriceRate = 16500;
			else if(clItemStatistic.siItemPriceIndex < 50000000)clItemStatistic.siNPCPriceRate = 17500;
			else if(clItemStatistic.siItemPriceIndex < 56000000)clItemStatistic.siNPCPriceRate = 19500;
			else if(clItemStatistic.siItemPriceIndex < 62000000)clItemStatistic.siNPCPriceRate = 21500;
			else if(clItemStatistic.siItemPriceIndex < 68000000)clItemStatistic.siNPCPriceRate = 23500;
			else if(clItemStatistic.siItemPriceIndex < 74000000)clItemStatistic.siNPCPriceRate = 25500;
			else if(clItemStatistic.siItemPriceIndex < 80000000)clItemStatistic.siNPCPriceRate = 27500;
			else if(clItemStatistic.siItemPriceIndex < 86000000)clItemStatistic.siNPCPriceRate = 29500;
			else if(clItemStatistic.siItemPriceIndex < 92000000)clItemStatistic.siNPCPriceRate = 31500;
			else if(clItemStatistic.siItemPriceIndex < 98000000)clItemStatistic.siNPCPriceRate = 33500;
			else if(clItemStatistic.siItemPriceIndex < 100000000)clItemStatistic.siNPCPriceRate = 35500;
			else 	clItemStatistic.siNPCPriceRate = 35500;

			//KHY - NPCRATE Ȯ�� - �ӽ� �ڵ�
			//----------------------------------------------------------------------------------
			if(clItemStatistic.siNPCPriceRate > 3000)
			{
				SI32 temNPCRATE = ReadLastNPCRATE( );

				if(clItemStatistic.siNPCPriceRate > temNPCRATE)
				{
					clItemStatistic.siNPCPriceRate = temNPCRATE +100;

					WriteLastNPCRATE(clItemStatistic.siNPCPriceRate );
				}
			}
			//----------------------------------------------------------------------------------
			
			// ���� ������ �뺸�Ѵ�. 
			((cltServer*)pclClient)->SendServerInfo(0);

			pclClient->pclNPCItemInfo->Create(clItemStatistic.siNPCPriceRate);
		}
	}

	
}

//KHY - NPCRATE Ȯ�� - �ӽ� �ڵ�
//-------------------------------------------------------------------------------------------------------------------
SI32 cltItemManagerCommon::ReadLastNPCRATE()
{
	TCHAR	fileNameBuffer[256]; // ���� ���ϸ�.
	FILE 	*fp = NULL;

	SI32 	siLastNPCRATE = 0; 

	StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\LastNPCRATE.log"));			
	fp = _tfopen( fileNameBuffer , TEXT("rb") );

	if ( fp != NULL )
	{
		TCHAR buffer[1024] = { TEXT('\0') };		

		if( _fgetts(buffer, 1024, fp) != NULL )
		{
			HQDivideByTab(buffer,"%d", &siLastNPCRATE);			
		}
		
		fclose( fp );
	}

	return siLastNPCRATE;
}

void cltItemManagerCommon::WriteLastNPCRATE(SI32 nowLastNpcrate)
{
	TCHAR	fileNameBuffer[256]; // ���� ���ϸ�.
	FILE 	*fp = NULL;

	SI32 	siLastNPCRATE = nowLastNpcrate; 

	StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\LastNPCRATE.log"));			
	fp = _tfopen( fileNameBuffer , TEXT("w") );

	if ( fp != NULL )
	{
		//fwrite(&siLastNPCRATE , sizeof(SI32) , 1 , fp);
		_ftprintf( fp, TEXT("%d"), siLastNPCRATE);

		fclose( fp );
	}
}
//-------------------------------------------------------------------------------------------------------------------

// �������� ������ ���Ѵ�. 
GMONEY cltItemManagerCommon::GetNPCRepairPrice(cltItem* pclitem)
{
	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);
	if(ref <= 0)return 0;

	SI32 type = pclItemInfo[ref]->siType;

	// ���� �Ұ�ǰ�� ���, 
	if((pclItemTypeInfo[type]->siAtb & ITEMATB_REPAIR) == 0)return 0;

	// �ü��� ���´�. 
	cltItemPriceUnit* pclprice = GetCurrentPrice(pclitem->siUnique);
	if(pclprice == NULL)return 0;


	GMONEY repairprice = 0;
	GMONEY price = pclprice->siPrice;


	if(price > 1200000)
	{
		repairprice += ((price - 1200000) / 12);
		price = 1200000;
	}
	if(price > 800000)
	{
		repairprice += ((price - 800000) / 15);
		price = 800000;
	}
	if(price > 400000)
	{
		repairprice += ((price - 400000) / 18);
		price = 400000;
	}

	repairprice += (price / 20);

	// ȣǰ�̳� ��ǰ�� ������ ��δ�. 
	switch(pclitem->clItemCommon.clCommonInfo.uiRareInfo)
	{
	case RARELEVEL_1:	repairprice *= 2;	break;
	case RARELEVEL_2:	repairprice *= 3;	break;
	}

	return max(1, repairprice);


}

// ĳ���� kind�� �ٰŷ� ��ȯ ������ ����ũ�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetItemDollUnique(SI32 kind)
{
	SI32 i;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)continue;

		if(pclItemInfo[i]->siMakeKind == kind)
		{
			return pclItemInfo[i]->clItem.siUnique;
		}
	}

	return 0;
}

// �𺴰� ����Ʈ�� �������� ������ ��ǰ�� ������ ���� Ȯ��. 
bool cltItemManagerCommon::GetDailyQuestRewardInfo(GMONEY money, SI32* pitemunique, SI32* pitemnum, GMONEY* prewardmoney )
{
	SI32 i;
	SI32 itemunique[MAX_ITEMINFO_NUMBER];
	for(i= 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		itemunique[i] = 0;
	}
	SI32 itemindex = 0;
	cltItemPriceUnit* pclprice;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_ANIMAL)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_DOLL)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_BOOK)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_TICKET)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_MANTLE)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_BAG)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_SCROLL)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_SEAFOOD)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_ETC)		continue;

		if(pclItemInfo[i]->siType == ITEMTYPE_CRYSTAL)		continue;//��Ƽ��Ʈ ����ü 
		if(pclItemInfo[i]->siType == ITEMTYPE_COMPOSITIONMATERIAL)		continue;//�ռ����
		if(pclItemInfo[i]->siType == ITEMTYPE_EVENTITEM)		continue;//�̺�Ʈ������
		if(pclItemInfo[i]->siType == ITEMTYPE_BOX)		continue;//�ڽ�������
		if(pclItemInfo[i]->siType == ITEMTYPE_PREMIUM)		continue;

		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_MANTLE)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_DRESS)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_HAT)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_NECK)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_RING)		continue;
        
		// ���ᰡ ���� ��ǰ�̾�� �Ѵ�. 
		if(pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique)continue;

		// ������Ʈ ������ ��ǰ�� �ƴϾ�� �Ѵ�. 
		if(GetItemAtb(pclItemInfo[i]->clItem.siUnique) & ITEMATB_OBJECT)continue;

	
		// �������� �ü� Ȯ�� 
		pclprice = pclItemPrice->GetPrice(this, pclItemInfo[i]->clItem.siUnique);
		if(pclprice == NULL)continue;
		if (pclprice->siPrice < 100 )	continue;
		
		// ������ �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3730))continue;
		// ������ �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3855))continue;

		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_NOTDAILYQUEST)) continue;

		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_ITEMMALL)) continue;

		/*cyj �̺�Ʈ ����������ũ ����
		// ��ι��� �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == 8200)continue;
		// �������� �ƴϾ�� �Ѵ�.
		if(pclItemInfo[i]->clItem.siUnique == 2350)continue;
		*/
	
		itemunique[itemindex] = pclItemInfo[i]->clItem.siUnique;			
		itemindex++;
		
	}

	if(itemindex <= 0)return false;

	// �������� ���� Ȯ��. 
	*pitemunique = itemunique[rand() % itemindex];

	// �������� �ü� Ȯ�� 
	pclprice = pclItemPrice->GetPrice(this, *pitemunique);
	if(pclprice == NULL)return false;

	GMONEY itemprice = pclprice->siPrice * 6;	// �ü����� ���� �������� ����Ѵ�. 

	// �������� ���� Ȯ��. 
	*pitemnum	= (SI32)(min(30, max(1, money / itemprice)));

	*prewardmoney = pclprice->siPrice * (*pitemnum);

	return true;
}
bool cltItemManagerCommon::GetDailyQuest2RewardInfo(GMONEY money, SI32* pitemunique, SI32* pitemnum, GMONEY* prewardmoney )
{
	SI32 i;
	SI32 itemunique[MAX_ITEMINFO_NUMBER];
	cltItemPriceUnit* pclprice;
	for(i= 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		itemunique[i] = 0;
	}
	SI32 itemindex = 0;
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)		
	{
		if(pclItemInfo[i] == NULL)continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_ANIMAL)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_DOLL)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_BOOK)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_TICKET)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_MANTLE)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_BAG)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_SCROLL)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_SEAFOOD)	continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_ETC)		continue;

		if(pclItemInfo[i]->siType == ITEMTYPE_CRYSTAL)					continue;	//	��Ƽ��Ʈ ����ü 
		if(pclItemInfo[i]->siType == ITEMTYPE_COMPOSITIONMATERIAL)		continue;	//	�ռ����
		if(pclItemInfo[i]->siType == ITEMTYPE_EVENTITEM)					continue;	//	�̺�Ʈ������
		if(pclItemInfo[i]->siType == ITEMTYPE_BOX)						continue;	//	�ڽ�������
		if(pclItemInfo[i]->siType == ITEMTYPE_PREMIUM)					continue;	//	�����̾� ������

		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_MANTLE)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_DRESS)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_HAT)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_NECK)		continue;
		if(pclItemInfo[i]->siType == ITEMTYPE_AVATAR_RING)		continue;

		// ���ᰡ ���� ��ǰ�̾�� �Ѵ�. 
		if(pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique)continue;

		// ������Ʈ ������ ��ǰ�� �ƴϾ�� �Ѵ�. 
		if(GetItemAtb(pclItemInfo[i]->clItem.siUnique) & ITEMATB_OBJECT)continue;

		//// �������� �ü� Ȯ�� 
		pclprice = pclItemPrice->GetPrice(this, pclItemInfo[i]->clItem.siUnique);
		if(pclprice == NULL)continue;
		if (pclprice->siPrice < 300 ) continue;//300������ ����

		// ������ �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3730))continue;
		// ������ �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3855))continue;

		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_NOTDAILYQUEST)) continue;

		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_ITEMMALL)) continue;

		itemunique[itemindex] = pclItemInfo[i]->clItem.siUnique;

		itemindex++;

	}

	if(itemindex <= 0)return false;

	// �������� ���� Ȯ��. 
	*pitemunique = itemunique[rand() % itemindex];
	if(rand() % 100 == 45){
		switch(rand()%3) 
		{
		case 0:{
			*pitemunique = ITEMUNIQUE(5380);
			*pitemnum	= 0 ;
			*prewardmoney = 0;
			   }
			   break;
		case 1:
			{
				*pitemunique = ITEMUNIQUE(7175);
				*pitemnum	= 0 ;
				*prewardmoney = 0;
			}
			break;
		case 2:
			{
				*pitemunique = ITEMUNIQUE(6140);
				*pitemnum	= 0 ;
				*prewardmoney = 0;
			}
			break;
		}
	}
	else{
		// �������� ���� Ȯ��. 
		*pitemnum	= 0 ;

		*prewardmoney = 0;
	}
	return true;
}
//���ϸ� ����Ʈ�� �������� ������ �´�.
bool cltItemManagerCommon::GetDailyQuest3KindInfo(SI16* pUnique, SI16* pMakeNum)
{
	SI32 i;
	SI32 itemunique[MAX_ITEMINFO_NUMBER];
	//�ʱ�ȭ.
	for(i= 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		itemunique[i] = 0;
	}
	SI32 itemindex = 0;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		// ������������ NULL�̸� �ȵȴ�.
		if(pclItemInfo[i] == NULL)continue;
		//���� ������ �� �������̸� continue
		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_ITEMMALL)) continue;
		// ���ϸ� ����Ʈ�� �ƴϸ� �ȵȴ�.
		if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_NOTDAILYQUEST)) continue;
		// ������ �ƴϾ�� �Ѵ�. 
		if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3855))continue;
		//���� ��Ʈ �ϰ��� �н�.
		if ( pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE( 685 ) ||	// ������ �䰩
			pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE( 875) ||		// ������ ��Ʈ
			pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE( 785 ) ||		// ������ ����
			pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE( 1700 ) ) {	// ������ �Ź�
				continue;
		}

		//���⳪ �� �� ��쿡�� �ؾ� �ϹǷ�.�ش� Ÿ�� �϶��� ����Ʈ�� �ִ´�.
		if (pclItemInfo[i]->siType == ITEMTYPE_SWORD	||
			pclItemInfo[i]->siType == ITEMTYPE_SPEAR	||
			pclItemInfo[i]->siType == ITEMTYPE_STAFF	||
			pclItemInfo[i]->siType == ITEMTYPE_AXE		||
			pclItemInfo[i]->siType == ITEMTYPE_BOW		||
			pclItemInfo[i]->siType == ITEMTYPE_GUN		||
			pclItemInfo[i]->siType == ITEMTYPE_CANNON	||
			pclItemInfo[i]->siType == ITEMTYPE_ARMOUR	||
			pclItemInfo[i]->siType == ITEMTYPE_BELT		||
			pclItemInfo[i]->siType == ITEMTYPE_SHOES	||
			pclItemInfo[i]->siType == ITEMTYPE_HELMET
			) 
		{
			// ���� �������� ���� �������� ��� ������ ���� ���Ѵ�.
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclItemInfo[i]->clItem.siUnique);
			if (Ref <= 0 ) continue;
			SI32 SkillLevelLimit = pclClient->pclItemManager->pclItemInfo[Ref]->clSkillInfo.siSkillLevel; // ���۱��Lev
			if (SkillLevelLimit <= 20 ) continue;// ���� ��� ������ �ּ� 20�̻�
			// ������ ��� ���� �Ǿ�����. ����������ũ�� �ε����� �ִ´�.
			itemunique[itemindex] = pclItemInfo[i]->clItem.siUnique;
			//�ε��� ����.
			itemindex++;
		}				
	}
	if(itemindex <= 0)return false;
	// �������� �پ��ϰ� ���� �ϹǷ�.
	*pUnique = itemunique[rand() % itemindex];
	
	// ���� �������� ���� �������� ��� ������ ���� ���Ѵ�.
	SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( *pUnique );
	if (Ref <= 0 ) return false;
	SI32 SkillLevelLimit = pclClient->pclItemManager->pclItemInfo[Ref]->clSkillInfo.siSkillLevel; // ���۱��Lev
	if (SkillLevelLimit <= 20 ) return false;// ���� ��� ������ �ּ� 20�̻�

	//10~40�� ���̷� ���´�.
	SI32 randtemp = rand() % MAX_DAILYQUEST3_MAKEITEM_NUM +10;
	SI32 skilltemp = SkillLevelLimit/10;

	*pMakeNum	=randtemp/skilltemp +5 ;
	return true;
}

//���ϸ� ����Ʈ 3 ��������� ����.
bool cltItemManagerCommon::GetDailyQuest3RewardInfo( SI32* siRewardExp, SI16 siMakeItemNum, SI16* pRewarditemunique, SI16* pRewarditemnum, SI32 SkillLevelLimit )
{
	cltItemPriceUnit*		pclprice ;// ����������� �ü� - 1000 ������ ������ ����. ��������� ������ ���
	SI32 i					=	0 ;
	SI32 SkillLimitTemp		=	0 ;			// ���� ����ġ ����� ���� ������ ���� ��� ���� ���� Temp ����
	SI32 RewardTemp			=	0 ;			//	���� ���� ����� ���� Temp ����
	SI32 RewardTemp2		=	0 ;			//	���� ���� ����� ���� Temp ���� 2
	SI32 itemunique[MAX_ITEMINFO_NUMBER] ;	// ������ ����ũ�� ������ �迭
	SI32 itemindex			=	0 ;			// ������ �ε��� 
	//SI32 SkillLevelLimit	���� �������� ���� �ʿ佺ų

    // �ƾ��� ����ũ�� ���� �迭�� �ʱ�ȭ ��Ų��.	
	for(i= 0;i < MAX_ITEMINFO_NUMBER;i++)
	{	itemunique[i] = 0;	}
	// ������ �� �������� �����Ѵ�.
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)continue;
		//	����������� �� 3���� ������ �ش�. �׷��Ƿ� �� ���� ���ǹ� ������ ����. �� �ܿ��� pass
		if (pclItemInfo[i]->siType == ITEMTYPE_CLOTH	||
			pclItemInfo[i]->siType == ITEMTYPE_MINERAL	||
			pclItemInfo[i]->siType == ITEMTYPE_TREE) {
				// ���ᰡ ���� ��ǰ�̾�� �Ѵ�. 
				if(pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique)continue ;
				// ������Ʈ ������ ��ǰ�� �ƴϾ�� �Ѵ�. 
				if(GetItemAtb(pclItemInfo[i]->clItem.siUnique) & ITEMATB_OBJECT)continue ;
				// ������ �ƴϾ�� �Ѵ�. 
				if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3730))continue ;
				// ������ �ƴϾ�� �Ѵ�. 
				if(pclItemInfo[i]->clItem.siUnique == ITEMUNIQUE(3855))continue ;
                // ������ ���� ���ϸ� ����Ʈ�� �ƴϸ� �ȵȴ�.
				if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_NOTDAILYQUEST)) continue ;
				// �����۸� �������� ���� ���� �ʴ´�.
				if(pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_ITEMMALL)) continue ;
				// ������ �� �������� �ü��� ������ �´�.
				pclprice = pclItemPrice->GetPrice(this, pclItemInfo[i]->clItem.siUnique) ;
				if(pclprice == NULL)continue ;
				//������ �ü��� 1000�� �̹��� �������� ���� �ʴ´�.
				if (pclprice->siPrice < 1000 ) continue ;
				
				// ������ ��� ���� �Ǿ�����. ����������ũ�� �ε����� �ִ´�.
				itemunique[itemindex] = pclItemInfo[i]->clItem.siUnique ;
				//�ε��� ����.
				itemindex++ ;
		}
		else{
			continue;
		}
	}
	if(itemindex <= 0)return false ;
	// ���� �������� ���� Ȯ�� 
	*pRewarditemunique = itemunique[rand() % itemindex] ;
	//---------------------------------------------------------------------------------------------------------------------------------
	// ����������� �ü� Ȯ�� 
	//---------------------------------------------------------------------------------------------------------------------------------
	pclprice = pclItemPrice->GetPrice(pclClient->pclItemManager, *pRewarditemunique) ;
	if(pclprice == NULL)	return false ;
	// ��������� �ü��� 1000�� �̸��ϰ�� false ����
	if (pclprice->siPrice < 1000 )	return false ;
	//---------------------------------------------------------------------------------------------------------------------------------
	// �������ġ ����
	//---------------------------------------------------------------------------------------------------------------------------------
	SkillLimitTemp = (SkillLevelLimit / 3) ;
	if (SkillLimitTemp <= 0) return false ;
	* siRewardExp = SkillLevelLimit * siMakeItemNum * 300 /100 * SkillLimitTemp ;
	//---------------------------------------------------------------------------------------------------------------------------------
	//��������� ������ ���Ѵ�.
	//---------------------------------------------------------------------------------------------------------------------------------
	RewardTemp = ( pclprice->siPrice * 2 );
	if ( RewardTemp <= 0 ) return false;
	RewardTemp2 = ( *siRewardExp * siMakeItemNum * 7 ) / RewardTemp ;
	*pRewarditemnum = min( 300, max( 1,RewardTemp2 ) ) ;

	return true;
}
// ��ǰ�� ����� ����� ����� ��Ḧ ���ϴ� ����Լ� -����
bool cltItemManagerCommon::GetWeenyOldManMaterialInfo(SI16 resolutionRate, SI32 disassembleItem, cltItem* pDisAssemitem)
{
	SI32 itemIndex = 0 , i = 0, j = 0;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( disassembleItem );
	if ( ref <= 0 ) 
		return false;	

	for( i = 0 ; i < MAX_MATERIAL_NUMBER ; i++)
	{
		// ���� �������� ��ȿ�ؼ��� �ȵȴ�. 
		SI32 materialUnique = pclItemInfo[ ref ]->clProductionInfo.clMaterial[i].siUnique;
		if( materialUnique <= 0 ) continue;

		SI32 materialRef = FindItemRefFromUnique( materialUnique );
		if( materialRef <= 0 ) continue;

		SI32 materialType = pclItemInfo[ materialRef ]->siType;
		// ���ᰡ ������Ʈ �������̶�� �� ��Ḧ ���ؼ� ���سִ´�.
		if( pclItemTypeInfo[ materialType ]->IsAtb( ITEMATB_OBJECT ) == TRUE )
		{
			// ����Լ�
			if( GetWeenyOldManMaterialInfo( resolutionRate , materialUnique , pDisAssemitem ) == false)
			{
				return false;
			}
		}
		else // ���ᰡ �׳� �������̶�� �״�� �߰��� �ش�.
		{
			SI32 giveItemNum = pclItemInfo[ref]->clProductionInfo.clMaterial[i].siNeedNum * resolutionRate / 100;
			if( giveItemNum <= 0 ) continue;

			SI32 emptyIndex = -1;
			
			// ������ �������� �̹� ��Ͽ� �ִٸ� ������ �����ش�.
			for( j = 0; j < MAX_ITEM_PER_WENNYOLD ; j++ )
			{
				if( pDisAssemitem[ j ].siUnique == materialUnique )
				{
					pDisAssemitem[ j ].siItemNum += giveItemNum;
					if( pDisAssemitem[ j ].siItemNum > MAX_ITEM_PILE_NUMBER ) 
					{
						pDisAssemitem[ j ].siItemNum = MAX_ITEM_PILE_NUMBER;
					}
					break;
				}
				else if( pDisAssemitem[ j ].siUnique == 0 )	// �� �ε����� ����� �д�. ���߿� ����ٰ� �������� �ֱ� ����
				{
					if( emptyIndex < 0 )	// �� �ε����� ���� ��ã�� ���¶�� ���� �� �ε����� ����Ų��.
					{
						emptyIndex = j ;
					}
				}
			}

			// for ���� break ���� �׳� �������Դٴ� ���� ���� �������� ��Ͽ� ���� ���ߴٴ� ���̴�.
			if( j >= MAX_ITEM_PER_WENNYOLD )
			{
				// ��Ͽ� ������ ��� ���� �� �ε����� �������� �־��ش�.
				if( emptyIndex >= 0 && emptyIndex < MAX_ITEM_PER_WENNYOLD )
				{
					if( pDisAssemitem[ emptyIndex ].siUnique == 0 )
					{
						pDisAssemitem[ emptyIndex ].siUnique = materialUnique ;
						pDisAssemitem[ emptyIndex ].siItemNum += giveItemNum;

						if( pDisAssemitem[ emptyIndex ].siItemNum > MAX_ITEM_PILE_NUMBER ) 
						{
							pDisAssemitem[ emptyIndex ].siItemNum = MAX_ITEM_PILE_NUMBER;
						}

					}
				}
			}
			
			// ����� �������ִٸ� ���̻� �ٸ� ������ �������� �־��ټ� ����. �׳� �Ѿ��.

		}
	}

	return true;
}

bool cltItemManagerCommon::GetRareItemWithWeenyOld(cltItem *pclitem)
{
	if (pclitem == NULL)
		return false;

	cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, pclitem->siUnique);
	GMONEY itemprice = pclprice->siPrice;
		
	SI32 percent = 0;

	if (IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_ITEMMALL) == true)
	{
		cltServer *pclserver = (cltServer*)pclClient;

		SI32 useableDay = 0;
		BOOL rVal = pclserver->GetItemUseAbleDay(pclitem, &useableDay);
		if(rVal == FALSE) return false;

		percent = 34;

		if (useableDay > 0)
		{
			percent = percent + (useableDay * 2);
		}

		if (percent > 94)
		{
			percent = 94;
		}
        
	}
	else
	{

		if (itemprice >= clItemStatistic.siItemPriceIndex * 15)		percent = 3;
		else if (itemprice < clItemStatistic.siItemPriceIndex * 15)		percent = 2;
		else if (itemprice < clItemStatistic.siItemPriceIndex * 14)		percent = 1;
		else if (itemprice < clItemStatistic.siItemPriceIndex * 13)		percent = 0;

	}

	if (rand() % 100 + 1 <= percent)
		return true;
	else
		return false;

	

}


// ��ȣ�Ŀ��Լ� ������ ���������� ������� ����Ѵ�
SI16 cltItemManagerCommon::GetWennyOldItem( cltItem* pclItem, SI16 *resolutionRate )
{
	cltServer* pclserver = (cltServer*)pclClient;

	// ��í �������̶��

	if( pclserver->pclGachaManager->IsGachaRareItem( pclItem->siUnique ) == true )
	{
		return WENNYMSG_GACHARARE;
	}

	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	if( GetValentineEvent(pclItem->siUnique) == true )
	{
		return WENNYMSG_VAlENTINEITEM;
	}

	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	if( GetWhiteEvent(pclItem->siUnique) == true )
	{
		return WENNYMSG_WHITEITEM;
	}

	// �����۸� �������̶��
	if ( IsItemInfoAtb( pclItem->siUnique , ITEMINFOATB_ITEMMALL ) )
	{
		SI32 useableDay = 0;
		BOOL rVal = pclserver->GetItemUseAbleDay(pclItem, &useableDay);
		//if(rVal == FALSE) 
			//return WENNYMSG_FAILED;

		// ����� ���� Ȯ���� ���Ѵ�.
		SI32 necklaceRate = 10;
		necklaceRate += useableDay;
		necklaceRate = max( 40, necklaceRate );

		SI32 siRand = 0 ;
		siRand = rand()%100 + 1;

		// �븸�� ��� ��ȣ�� ���ڰ� �ȳ����� ������. (PCK - 2007.09.11)
		if (pclClient->IsCountrySwitch(Switch_WENNYBOXDisable))
		{
			if ( siRand <= necklaceRate )
			{
				return WENNYMSG_NECKLACE;
			}
			else if( siRand <= necklaceRate + 2 )
			{
				return WENNYMSG_NONE;
			}
			else
			{
				return WENNYMSG_NONE;
			}
		}
		else
		{
			if ( siRand <= necklaceRate )
			{
				return WENNYMSG_NECKLACE;
			}
			else if( siRand <= necklaceRate + 2 )
			{
				return WENNYMSG_NONE;
			}
			else
			{
				return WENNYMSG_BOX;
			}
		}

	}
	// ��ȣ�� ���� ��Ḧ �ִ� �������̶�� 10% �� Ȯ���� ���� ��Ḧ ��
	else if( IsItemInfoAtb( pclItem->siUnique , ITEMINFOATB_WENNYOLDMAN_MATERIAL ) )
	{
		SI32 siRand = 0 ;
		siRand = rand()%100 ;
		
		if( siRand < 10 )
		{
			return WENNYMSG_WENNYMATERIAL;
		}
	}
	
	// ���� �ش���� �ʴ� �Ϲ����� ���

	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice( pclItem->siUnique );

	GMONEY priceIndex = pclClient->pclItemManager->clItemStatistic.siItemPriceIndex;

	if ( priceIndex == 0  )
		return WENNYMSG_FAILED;

	// 20���� ���� üũ
	SI32 ref = FindItemRefFromUnique( pclItem->siUnique );
	SI32 equiplevel = pclItemInfo[ref]->clCondition.siLevel;

	SI64 siPenalty = (pclprice->siPrice * 100) / priceIndex;
	SI64 rareRate = 0;

	if ( siPenalty < 130 )	rareRate = 1;
	else if ( siPenalty < 140 )	rareRate = 2;
	else if ( siPenalty < 150 )	rareRate = 3;
	else if ( siPenalty < 160 )	rareRate = 4;
	else	rareRate = 5;

	BOOL bEnableWennyMsg_Box = TRUE;
	
	// �븸�� ��� ��ȣ�Ļ��ڰ� �ȳ������� ������ (PCK - 2007.09.11)
	if (pclClient->IsCountrySwitch(Switch_WENNYBOXDisable))
	{
		bEnableWennyMsg_Box = FALSE;
	}

	if(pclClient->IsCountrySwitch(Switch_WENNYBOXCHECKLEVEL))
	{
		// 20���� �̻��� ��� �ڽ� ����..
		if(equiplevel < 20)		bEnableWennyMsg_Box = FALSE;
	}

	SI32 siRand = rand() % 100 + 1;
	if ( siRand <= rareRate )
	{
		*resolutionRate = 200;
		return WENNYMSG_DOUBLE;
	}
	else if( siRand <= rareRate*2 && bEnableWennyMsg_Box)	// 20���� �̻��� ��� �ڽ� ����..
	{
		return WENNYMSG_BOX;
	}
	else
	{
		// ������ ������ �ޱ�
		if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
		{
			SI32 siGetDurRepareStone = rand() % 100; //0 ~ 99
			if ( 5 > siGetDurRepareStone )	// 5%Ȯ���� ����
			{
				return WENNYMSG_REPAIR_DUR;
			}
		}

		SI32 resolutionRand = rand() % 100 + 1;

		if ( resolutionRand <= 5 )			*resolutionRate += 30;
		else if ( resolutionRand <= 20 )	*resolutionRate += 40;
		else if ( resolutionRand <= 40 )	*resolutionRate += 50;
		else if ( resolutionRand <= 70 )	*resolutionRate += 60;
		else if ( resolutionRand <= 90 )	*resolutionRate += 70;
		else								*resolutionRate += 80;

		*resolutionRate += resolutionRand % 10; 

		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			cltServer* pclserver = (cltServer*)pclClient;
			CMinisterIzo* pclminister = (CMinisterIzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_IZO);
			SI32 value = pclminister->GetTinTin();

			*resolutionRate += value;
		}

		if ( *resolutionRate < 50 )			
			return WENNYMSG_SMALL;
		else if ( *resolutionRate < 70 )	
			return WENNYMSG_MEDIUM;
		else 		
			return WENNYMSG_LARGE;
	}
	
}

// �ǹ� ������ �������� ���Ѵ�.
bool cltItemManagerCommon::GetItemForStrRepair(GMONEY strprice, SI32* pitemunique, SI32* pitemnum)
{

	SI32 i;
	SI32 itemunique[MAX_ITEMINFO_NUMBER];
	for(i= 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		itemunique[i] = 0;
	}
	SI32 itemindex = 0;

	/*cyj �ǹ������� �ʿ��� ��� ��ź, ö����, �ݱ������� ����
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemInfo[i] == NULL)continue;
		if(pclItemInfo[i]->siType != ITEMTYPE_IRON
		&& pclItemInfo[i]->siType != ITEMTYPE_MINERAL
		&& pclItemInfo[i]->siType != ITEMTYPE_CLOTH
		&& pclItemInfo[i]->siType != ITEMTYPE_TREE)continue;

		itemunique[itemindex] = pclItemInfo[i]->clItem.siUnique;
		itemindex++;
		
	}

	if(itemindex <= 0)return false;
	*/
	// ��ź (�Ϻ��� ����ũ)
	itemunique[0] = ITEMUNIQUE(5000); //ITEMUNIQUE(5300);
	itemindex++;

	// ö���� (�Ϻ��� ����ũ)
	itemunique[1] = ITEMUNIQUE(5010); //ITEMUNIQUE(5302);
	itemindex++;

	// �ݱ��� (�Ϻ��� ����ũ)
	itemunique[2] = ITEMUNIQUE(5040); //ITEMUNIQUE(5314);
	itemindex++;

	// �������� ���� Ȯ��. 
	*pitemunique = itemunique[rand() % itemindex];

	// �������� �ü� Ȯ�� 
	cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, *pitemunique);
	if(pclprice == NULL)return false;

	
	GMONEY itemprice = max(100, pclprice->siPrice );

	// �ǹ� ������ 0.7%�� �ش��ϴ� �ݾ׾�ġ�� �����Ѵ�. 
	strprice = max(1000, strprice * 7 / 1000);

	// �������� ���� Ȯ��. 
	*pitemnum	= min(100, max(1, strprice / itemprice));

	return true;

}


// Ư�� �������� ���� �����Ѱ� ?
bool cltItemManagerCommon::CanPile(SI32 itemunique)
{
	if(itemunique <= 0)return false;
	if(itemunique >= MAX_ITEM_UNIQUE)return false;
	
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return false;

	// �Ⱓ�� �������� ��ĥ �� ����	- By LEEKH 2007.06.19
	if(pclItemInfo[ref]->clItem.IsHaveUseDay() == TRUE)		return false;

	SI32 type = pclItemInfo[ref]->siType;
	if(type < 0)return false;

	if(pclItemTypeInfo[type] == NULL)return false;

	if(pclItemTypeInfo[type]->IsAtb(ITEMATB_OBJECT) == FALSE)
	{
		return true;
	}

	return false;

}

// ���� �� �ִ� ��ǰ�ΰ� ?(���ᰡ �����ϴ� ��ǰ�ΰ�. ) 
bool cltItemManagerCommon::CanMakableItem(SI32 itemunique)
{
	if(itemunique <= 0)return false;
	if(itemunique >= MAX_ITEM_UNIQUE)return false;

	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return false;

	// ù��° ���ᰡ ���ٸ� ���� �Ұ� ��ǰ. 
	if(pclItemInfo[ref]->clProductionInfo.clMaterial[0].siUnique <= 0)return false;

	return true;
}


// ���ڻ�㰡�� ������ ����Ѵ�.
void cltItemManagerCommon::CalcInvestment(bool bStart)
{
	if ( bStart == false ) return ;

	//----------------------------------------------------------------
	// ������ �ʱ�ȭ �۾�
	for ( SI32 i = 0 ; i < MAX_INVESTMENT_ITEM_NUMBER ; i ++ )
	{
		stInvestmentLines[i].siInvestmentItemUnique = 0 ;
		stInvestmentLines[i].siInvestmentItemPrice = 0 ;

		stInvestmentLines[i].siMarginalProfit = 0 ;

		for ( SI32 r = 0 ; r < MAX_MATERIAL_NUMBER ; r ++ )
		{
			stInvestmentLines[i].siMaterialItemPrice[r] = 0 ;
		}
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	// ��ü �����ۿ� ����...
	for ( i = 0 ; i < MAX_ITEMINFO_NUMBER ; i ++)
	{
		if(pclItemInfo[i] == NULL)						continue;

		// ������ �� ���� �����̸�, ��ŵ
		SI32 currentunique = pclItemInfo[i]->clItem.siUnique ;
		if ( CanMakableItem(currentunique) == false )	continue ;

		// ����� �� �ü��� ���Ѵ�. = ������ �ʿ�ݾ�
		GMONEY siTotalPrice = 0 ;
		for ( SI32 j = 0 ; j < MAX_MATERIAL_NUMBER ; j ++ )
		{
			cltMaterialInfo pclMaterialInfo = pclItemInfo[i]->clProductionInfo.clMaterial[j] ;
			SI32 materialunique = pclMaterialInfo.siUnique ;
			if ( materialunique <= 0 ) continue ;

			cltItemPriceUnit* pclprice = GetCurrentPrice(materialunique) ;
			if ( pclprice == NULL ) continue ;

			GMONEY materialprice = pclprice->siPrice * pclMaterialInfo.siNeedNum ;
			siTotalPrice += materialprice ;
		}

		// �����۽ü� X ���갳�� = �Ǹűݾ�
		GMONEY siCurrentPrice = GetCurrentPrice(currentunique)->siPrice * pclItemInfo[i]->clProductionInfo.siProductUnit ;

		// ������ ���Ѵ�.
		// �Ǹűݾ� - ������ �ʿ�ݾ�
		GMONEY marginalprofit = siCurrentPrice - siTotalPrice ;

		// ������ �ʿ��� �ݾ׺��� �Ǹ� �ݾ��� �� ũ�ٸ�...
		if ( marginalprofit > 0 )
		{
			for ( SI32 k = 0 ; k < MAX_INVESTMENT_ITEM_NUMBER ; k ++ )
			{
				// ����� ���ͺ���, ���� ���� ������ �� ũ�ٸ�...
				if ( stInvestmentLines[k].siMarginalProfit < marginalprofit )
				{
					// ������ ������ ���� ������ �����͸� �ڷ� �̷�� ������ �����.
					// �����ϸ鼭 ������ �����ʹ� ��������.
					for( SI32 loop = MAX_INVESTMENT_ITEM_NUMBER - 2; loop >= k ; loop-- )
						stInvestmentLines[loop+1] = stInvestmentLines[loop];

					stInvestmentLines[k].siInvestmentItemPrice = GetCurrentPrice(currentunique)->siPrice ;
					stInvestmentLines[k].siInvestmentItemUnique = currentunique ;
					stInvestmentLines[k].siMarginalProfit = marginalprofit ;

					// ������ �ü��� �����Ѵ�.
					for ( int l = 0 ; l < MAX_MATERIAL_NUMBER ; l ++ )
					{
						cltMaterialInfo pclMaterialInfo = pclItemInfo[i]->clProductionInfo.clMaterial[l] ;
						SI32 materialunique = pclMaterialInfo.siUnique ;
						if ( materialunique <= 0 ) continue ;

						cltItemPriceUnit* pclprice = GetCurrentPrice(materialunique) ;
						if ( pclprice == NULL ) continue ;

						stInvestmentLines[k].siMaterialItemPrice[l] = pclprice->siPrice ;
					}
					break;
				}
			}
		}
	}
}

// ��� ����ǰ�� �����ϰ� ���´�. 
SI32 cltItemManagerCommon::GetRandBigWarItem()
{
	SI32 bigwaritemnum = sizeof(siBigWarItemList) / sizeof(SI32);

	return siBigWarItemList[rand() % bigwaritemnum];
}
SI32 cltItemManagerCommon::GetRandBigWennyItem()
{
	SI32 bigwennyitemnum = sizeof(siBigWennyItemList) / sizeof(SI32);

	return siBigWennyItemList[rand() % bigwennyitemnum];
}

SI32 cltItemManagerCommon::GetRandBigChristmasItem()
{
	SI32 bigChristmasitemnum = sizeof(siBigChristmas) / sizeof(SI32);

	return siBigChristmas[rand() % bigChristmasitemnum];
}


// Ư�� ��ǰ�� ��� ��ǰ�ΰ�. 
bool cltItemManagerCommon::IsBigWarItem(SI32 itemunique)
{
	SI32 bigwaritemnum = sizeof(siBigWarItemList) / sizeof(SI32);
	
	for(SI32 i = 0;i < bigwaritemnum; i++)
	{
		if(itemunique == siBigWarItemList[i])return true;
	}

	return false;
}

// �����ϰ� �������� �̸��� ���Ѵ�. 
const TCHAR* cltItemManagerCommon::GetRandomItemName()
{
	SI32 i;
	SI16 itemlist[MAX_ITEMINFO_NUMBER];
	SI32 itemindex = 0;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		itemlist[i] = 0;
	}


	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if( pclItemInfo[i] == NULL )
			continue;
		if( false == pclItemInfo[i]->IsItemInfoAtb( ITEMINFOATB_SHOWLIST ) )
			continue;
		if( pclItemInfo[i]->IsItemInfoAtb( ITEMINFOATB_NOTTRADE ) )
			continue;
		if( pclItemInfo[i]->siType == ITEMTYPE_BOOK || 
			pclItemInfo[i]->siType == ITEMTYPE_TICKET )
			continue;		

		itemlist[itemindex] = i;
		itemindex++;
	}

	if(itemindex)
	{
		SI32 index = itemlist[rand() % itemindex];

		return pclItemInfo[ index ]->GetName();
	}

	return NULL;
}


SI32 cltItemManagerCommon::GetCushionUniqueFromCharKind(SI32 charkind)
{
	if( charkind == KIND_HERO3 )
	{
		return ITEMUNIQUE(13610);
	}
	else if( charkind == KIND_HEROINE3  )
	{
		return ITEMUNIQUE(13611);
	}
	else if( charkind == KIND_HERO4  )
	{
		return ITEMUNIQUE(13608);
	}
	else if( charkind == KIND_HEROINE4  )
	{
		return ITEMUNIQUE(13609);
	}

	return -1;
}

//stEnchantNeed cltItemManagerCommon::GetEnchantNeedItem(cltItem cltOrgItem,SI32 siSuccessUpItemNum ,BOOL bUseBlessingStone , BOOL bUseSealingUpIgnore )
void cltItemManagerCommon::GetEnchantNeedItem(cltItem cltOrgItem, stEnchantNeed* pclEnchantNeed, SI32 siSuccessUpItemNum ,BOOL bUseBlessingStone , BOOL bUseSealingUpIgnore )
{
	if( pclEnchantNeed == NULL )			return;

 	stEnchantNeed EnchantNeedItem;	

 	for(SI32 i=0; i< MAX_ENCHANT_NUMBER; i++) //�켱 �ʱ�ȭ ����
	{
		EnchantNeedItem.siElementUnique[i] =0;
		EnchantNeedItem.siElementNum[i] =0;
	}
	EnchantNeedItem.EnchantRate = 0.0f;
	EnchantNeedItem.EnchantDownRate = 0.0f;
	EnchantNeedItem.EnchantFailRate = 0.0f;
	EnchantNeedItem.siNeedSkill =0;

	SI32 siItemGrade = cltOrgItem.Element.siPower;
	SI32 siItemElement = cltOrgItem.Element.siType;

	SI32 siItemType = 0;
	
	if(cltOrgItem.Element.siPower >= 0 && cltOrgItem.Element.siPower < MAX_ENCHANT_GRADE)
		siItemGrade = cltOrgItem.Element.siPower + 1;


	if(siItemGrade <= 1)
	{
		EnchantNeedItem.EnchantRate = 1.00f;
		EnchantNeedItem.EnchantDownRate = 0.0f;
		EnchantNeedItem.EnchantFailRate = 0.0f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1;  
		
	}	
	else if(siItemGrade == 2)
	{
		EnchantNeedItem.EnchantRate = 0.80f;
		EnchantNeedItem.EnchantDownRate = 0.0f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] =cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1;
		
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A  || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ���� 
		}
		
		EnchantNeedItem.siElementNum[1] = 5;
	
		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 5;
		}

	}
	else if(siItemGrade == 3)
	{
		EnchantNeedItem.EnchantRate = 0.60f;
		EnchantNeedItem.EnchantDownRate = 0.10f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] =cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 	
		if(siItemElement == ENCHANT_TYPE_FIRE_A ||  siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����
		}
		
		EnchantNeedItem.siElementNum[1] =5;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 5;
		}

	}

	else if(siItemGrade == 4)
	{
		EnchantNeedItem.EnchantRate = 0.40f;
		EnchantNeedItem.EnchantDownRate = 0.20f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] =cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 	
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		
		EnchantNeedItem.siElementNum[1] = 7 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 7;
		}

	}

	
	else if(siItemGrade == 5)
	{
		EnchantNeedItem.EnchantRate = 0.30f;
		EnchantNeedItem.EnchantDownRate = 0.20f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] = 7 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 7;
		}

	}

	else if(siItemGrade == 6)
	{
		EnchantNeedItem.EnchantRate = 0.20f;
		EnchantNeedItem.EnchantDownRate = 0.20f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] = 10 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 10;
		}

	}

	else if(siItemGrade == 7)
	{
		EnchantNeedItem.EnchantRate = 0.10f;
		EnchantNeedItem.EnchantDownRate = 0.25f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] = 10 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 10;
		}

	}
	else if(siItemGrade == 8)
	{
		EnchantNeedItem.EnchantRate = 0.05f ;
		EnchantNeedItem.EnchantDownRate = 0.25f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] = 15 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 30;
		}

	}
	else if(siItemGrade == 9)
	{
		EnchantNeedItem.EnchantRate =  0.01f;
		EnchantNeedItem.EnchantDownRate = 0.25f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] = 15 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 40;
		}

	}
	else if(siItemGrade == 10)
	{
		EnchantNeedItem.EnchantRate = 0.001f ;
		EnchantNeedItem.EnchantDownRate = 0.30f;
		EnchantNeedItem.EnchantFailRate = 0.05f;
		EnchantNeedItem.siElementUnique[0] = cltOrgItem.siUnique;
		EnchantNeedItem.siElementNum[0] = 1; 
		if(siItemElement == ENCHANT_TYPE_FIRE_A || siItemElement == ENCHANT_TYPE_FIRE_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5350);
		}
		else if(siItemElement == ENCHANT_TYPE_WATER_A || siItemElement == ENCHANT_TYPE_WATER_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5355);
		}
		else if(siItemElement == ENCHANT_TYPE_WIND_A || siItemElement == ENCHANT_TYPE_WIND_D )
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5360);
		}
		else if(siItemElement == ENCHANT_TYPE_GROUND_A || siItemElement == ENCHANT_TYPE_GROUND_D)
		{
			EnchantNeedItem.siElementUnique[1] = ITEMUNIQUE(5365);
		}
		else
		{
			// ����ó�� �ؾ��� �ͼ� �ȵǴ°�
		}
		EnchantNeedItem.siElementNum[1] =  20 ;
		//		EnchantNeedItem.siNeedSkill = 40 ;

		if(bUseBlessingStone)
		{
			EnchantNeedItem.siElementUnique[2] = ITEMUNIQUE(5370);
			EnchantNeedItem.siElementNum[2] = 100;
		}

	}	
	

	if( siSuccessUpItemNum )
	{
		EnchantNeedItem.siElementUnique[3] = ITEMUNIQUE(13606);
		EnchantNeedItem.siElementNum[3] = siSuccessUpItemNum;
		
		REAL32 SuccessUpRate = 0.01f * siSuccessUpItemNum;

        SuccessUpRate = min(0.10f, SuccessUpRate);

		EnchantNeedItem.EnchantRate += SuccessUpRate;

	}
	
	if( bUseSealingUpIgnore )
	{
		EnchantNeedItem.siElementUnique[4] = ITEMUNIQUE(13607);
		EnchantNeedItem.siElementNum[4] = 1;
	}

	if( bUseBlessingStone )
	{
		EnchantNeedItem.EnchantFailRate = 0.0f;
		EnchantNeedItem.EnchantDownRate = 0.0f;
	}

	EnchantNeedItem.siItemGrade = siItemGrade;


	//return EnchantNeedItem;
	memcpy(pclEnchantNeed, &EnchantNeedItem, sizeof(EnchantNeedItem));
}

/*
SI32 cltItemManagerCommon::GetGradeItem(cltItem cltOrgItem )
{
	if(cltOrgItem.Element.siPower == 0 )      //0�ܰ�
	{
		return 20;        
	}
	else if(cltOrgItem.Element.siPower == 20 ) //1�ܰ�
	{
		return 30;        
	}
	else if(cltOrgItem.Element.siPower == 30 )  //2�ܰ�
	{
		return 60;        
	}
	else if(cltOrgItem.Element.siPower == 60 )  //3�ܰ�
	{
		return 100;        
	}
	else if(cltOrgItem.Element.siPower == 100 )  //4�ܰ�
	{
		return 150;        
	}
	else if(cltOrgItem.Element.siPower == 150 )  //5�ܰ�
	{
		return 250;        
	}
	else if(cltOrgItem.Element.siPower == 250 )  //6�ܰ�
	{
		return 450;        
	}

	return 0;

}
*/
/*

SI32 cltItemManagerCommon::GetEnchantGrade(SI32 siEnchantDamage)
{
	SI32 siEnchantGrade =0;


	switch(siEnchantDamage)
	{
	case 0:
		siEnchantGrade = 0;
		break;
	case 20:
		siEnchantGrade = 1;
		break;
	case 30:
		siEnchantGrade = 2;
		break;
	case 60:
		siEnchantGrade = 3;
		break;
	case 100:
		siEnchantGrade = 4;
		break;
	case 150:
		siEnchantGrade = 5;
		break;
	case 250:
		siEnchantGrade = 6;
		break;
	case 450:
		siEnchantGrade = 7;
		break;
	default:
		siEnchantGrade = 0;
		break;		
	}

	return siEnchantGrade;
}
*/


SI32 cltItemManagerCommon::GetEnchantDamageFromGrade(SI32 siGrade)
{
	SI32 siEnchantDamage =0;

	switch(siGrade)
	{
	case 0:
		siEnchantDamage = 0;
		break;
	case 1:
		siEnchantDamage = 20;
		break;
	case 2:
		siEnchantDamage = 30;
		break;
	case 3:
		siEnchantDamage = 60;
		break;
	case 4:
		siEnchantDamage = 100;
		break;
	case 5:
		siEnchantDamage = 150;
		break;
	case 6:
		siEnchantDamage = 200;
		break;
	case 7:
		siEnchantDamage = 250;
		break;
	case 8:
		siEnchantDamage = 320;
		break;
	case 9:
		siEnchantDamage = 400;
		break;
	case 10:
		siEnchantDamage = 500;
		break;
	default:
		siEnchantDamage = 0;
		break;		
	}

	return siEnchantDamage;
}

/*
TCHAR* cltItemManagerCommon::GetEnchantTypeName(TCHAR* szEnchantName, SI32 siEnchantType)
{


	switch(siEnchantType)
	{
	case ENCHANT_TYPE_FIRE_A:
		strcpy(szEnchantName, "�Ұ���");
		break;
	case ENCHANT_TYPE_FIRE_D:
		strcpy(szEnchantName, "�ҹ��");
		break;
	case ENCHANT_TYPE_WATER_A:
		strcpy(szEnchantName, "������");
		break;
	case ENCHANT_TYPE_WATER_D:
		strcpy(szEnchantName, "�����");
		break;
	case ENCHANT_TYPE_WIND_A:
		strcpy(szEnchantName, "�ٶ�����");
		break;
	case ENCHANT_TYPE_WIND_D:
		strcpy(szEnchantName, "�ٶ����");
		break;
	case ENCHANT_TYPE_GROUND_A:
		strcpy(szEnchantName, "�����");
		break;
	case ENCHANT_TYPE_GROUND_D:
		strcpy(szEnchantName, "����");
		break;
	default:
		strcpy(szEnchantName, "����");
		break;		
	}

	return szEnchantName;
}
*/
bool cltItemManagerCommon::IsCheckSkill(cltItem clOutputItem, SI32 materialcharunique)
{
	SI32 siItemType = pclClient->pclItemManager->GetItemType(clOutputItem.siUnique);
	bool simakeflag=true;
	cltPItemInfo*  pclmaterialinv = &pclClient->pclCM->CR[materialcharunique]->pclCI->clCharItem;
	stEnchantNeed materialunique1;
	GetEnchantNeedItem(clOutputItem, &materialunique1);

	switch(siItemType)
	{
	case ITEMTYPE_SWORD:	
		{
			SI32 skillunique  = SKILL_MAKESWORD1;

			SI32 level  = pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;
	case ITEMTYPE_SPEAR:
		{
			SI32 skillunique  = SKILL_MAKESPEAR1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;

		}
		break;
	case ITEMTYPE_STAFF:			
		{
			SI32 skillunique  = SKILL_MAKESTAFF1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;

		}
		break;
	case ITEMTYPE_AXE:			
		{
			SI32 skillunique  = SKILL_MAKEAXE1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;

		}
		break;
	case ITEMTYPE_BOW:			
		{
			SI32 skillunique  = SKILL_MAKEBOW1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;

		}
		break;
	case ITEMTYPE_GUN:
		{
			SI32 skillunique  = SKILL_MAKEGUN1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;		
	case ITEMTYPE_ARMOUR:
		{
			SI32 skillunique  = SKILL_MAKEARMOUR1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;	
	case ITEMTYPE_DRESS:
		{
			SI32 skillunique  = SKILL_MAKEDRESS1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;
	case ITEMTYPE_BELT:
		{
			SI32 skillunique  = SKILL_MAKEBELT1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;
	case ITEMTYPE_SHOES:
		{
			SI32 skillunique  = SKILL_MAKESHOES1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;
	case ITEMTYPE_HELMET:
		{
			SI32 skillunique  = SKILL_MAKEHELMET1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;


		}
		break;
	case ITEMTYPE_HAT:
		{
			SI32 skillunique  = SKILL_MAKEHAT1;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;		


		}			
		break;

	case ITEMTYPE_AVATAR_MANTLE:
		{
			SI32 skillunique  = SKILL_MAKEAVATAR_MANTLE;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;

	case ITEMTYPE_AVATAR_NECK:
		{
			SI32 skillunique  = SKILL_MAKEAVATAR_NECK;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;

		
	case ITEMTYPE_AVATAR_HAT:
		{
			SI32 skillunique  = SKILL_MAKEAVATAR_HAT;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;

	case ITEMTYPE_AVATAR_RING:
		{
			SI32 skillunique  = SKILL_MAKEAVATAR_RING;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;
		

	case ITEMTYPE_AVATAR_DRESS:
		{
			SI32 skillunique  = SKILL_MAKEAVATAR_DRESS;
			SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;
		

	case ITEMTYPE_CRYSTAL:	
		{
			SI32 skillunique  = SKILL_ARTIFACT;

			SI32 level  = pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclmaterialinv->clItem[0], 1);
			SI32 MaxLevel = materialunique1.siNeedSkill;
			if(level < MaxLevel) simakeflag = false;
		}
		break;

	}



	return simakeflag;
}



// ��� ������ ǰ���� ����Ʈ�� ��´�. (plist�� �Ҵ��ϰ� ������ �߰����Ŀ� �����Ѵ�.) 
bool cltItemManagerCommon::GetFarmItemList(SI32* pitemnum, SI32** plist)
{
	if( (*plist) != NULL )
		return false;


	*pitemnum	= 14;
	(*plist) = new SI32[*pitemnum];

	(*plist)[0] = ITEMUNIQUE(3600);// �� 
	(*plist)[1] = ITEMUNIQUE(3605);// �� 
	(*plist)[2] = ITEMUNIQUE(3610);// �̳���
	(*plist)[3] = ITEMUNIQUE(3615);// ǥ�����
	(*plist)[4] = ITEMUNIQUE(3620);// ���
	(*plist)[5] = ITEMUNIQUE(3625);// ����
	(*plist)[6] = ITEMUNIQUE(3630);// ����
	(*plist)[7] = ITEMUNIQUE(3635);// ����
	(*plist)[8] = ITEMUNIQUE(3640);// ����
	(*plist)[9] = ITEMUNIQUE(3645);// ���
	(*plist)[10] = ITEMUNIQUE(3650);// ����
	(*plist)[11] = ITEMUNIQUE(3655);// ��
	(*plist)[12] = ITEMUNIQUE(3660);// ����
	(*plist)[13] = ITEMUNIQUE(3665);// ��


	return true;
}

// ���������� ����� ǰ���� ȹ���Ѵ�. 
bool cltItemManagerCommon::GetTraderItem(SI16* pitemunique, SI16* pitemnum, GMONEY* pitemprice)
{
	SI32 i;
	SI32 list[MAX_ITEMINFO_NUMBER];
	SI32 index	= 0;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		list[i]			= 0;
	}

	for(i = 0; i < MAX_ITEMINFO_NUMBER;i++)
	{
		if( pclItemInfo[i] == NULL )
			continue;
		// �ŷ� ������ ��ǰ�̾�� �Ѵ�
		if( pclItemInfo[i]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) )
			continue;	
		// ���� ������ ��ǰ�̾�� �Ѵ�.
		if( 0 == pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique )
			continue;	

		SI32 type = pclItemInfo[i]->siType;

		if(pclItemTypeInfo[type]->IsAtb(ITEMATB_OBJECT) == false)continue;			// ������Ʈ �����̾�� �Ѵ�. 

		cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, pclItemInfo[i]->clItem.siUnique);
		if(pclprice <= 0)continue;
		if(pclprice->siPrice < 10000)continue;										// �ü��� 1���� ������ ��ǰ�� ����.
		if(pclprice->siPrice > 10000000)continue;									// �ü��� 1000���� �̻��� ��ǰ�� ����.


		if(clItemStatistic.siItemTradeStatistic[i] > 100)continue;					// �ŷ� �Ǽ��� 100�� �̻��� ǰ���� ����. 

		// �� �ŷ� �ݾ��� ���Ѵ�. 
		INT64 totaltradeprice = pclprice->siPrice * clItemStatistic.siItemTradeStatistic[i];
		if(totaltradeprice > 100000000)continue;		// �ŷ� �ݾ� �Ը� 1�� �̻��̸� ����. 

		list[index] = i;
		index ++;
	}

	if(index > 0)
	{
		SI32 ref = list[rand() % index];

		*pitemunique	= pclItemInfo[ref]->clItem.siUnique;

		cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, pclItemInfo[ref]->clItem.siUnique);
		*pitemprice		= ((pclprice->siPrice / 10000) + 1) * 10000 * 150 / 100;	// �ü��� 150% 
		if(*pitemprice == 0)*pitemprice = 1000;
		

		*pitemnum		= min(1000, 100000000 / *pitemprice);

		return true;
	}



	return false;

}



// Ư�� �Ӽ��� ���������� �Ӽ��ΰ�. 
bool cltItemManagerCommon::IsItemInfoAtb(SI16 itemunique, SI32 atb)
{
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref > 0)
	{
		if(pclItemInfo[ref]->siItemInfoAtb & atb)
		{
			return true;
		}
	}

	return false;

}

bool cltItemManagerCommon::IsNewMarketTrade(SI16 itemunique)
{
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref > 0)
	{
		return pclItemInfo[ref]->m_bNewMarket;
	}

	return false;
}

// ����� ���ؼ� ���� �� �ִ� ��� ����ġ.  
SI32 cltItemManagerCommon::GetFarmSkillExp(SI32 itemunique)
{
	cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, itemunique);
	if(pclprice == NULL)return 0;

	SI32 skillexp = min(10, max(1, pclprice->siPrice/ 200));
	
	return skillexp;
}

// ä���� ���ؼ� ���� �� �ִ� ��� ����ġ.  
SI32 cltItemManagerCommon::GetMineSkillExp(SI32 itemunique)
{
	cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, itemunique);
	if(pclprice == NULL)return 0;

	SI32 skillexp = min(30, max(1, pclprice->siPrice/ 400));

	return skillexp;
}

// ��ȯ�� �������� ���� ���̶� ����ġ���
bool cltItemManagerCommon::GetSummonFoodInfo(SI32* pitemunique,SI32* pitemnum,SI32* pexp,SI32* pskillexp)
{
	SI32 foodlist[] =
	{
		ITEMUNIQUE(3795),	// �ع���
		ITEMUNIQUE(3800),	// ��ä
		ITEMUNIQUE(3815),	// �ؾ�ſ���
		ITEMUNIQUE(3820),	// �ޱ�ſ���
		ITEMUNIQUE(3825),	// �׾���
		ITEMUNIQUE(2615),	// ������
		ITEMUNIQUE(2620),	// �簣��
		ITEMUNIQUE(2660),	// ��ͺ�����
		ITEMUNIQUE(2665),	// �Ⱕ��
		ITEMUNIQUE(2670)	// ���Ϲ�����
	};

	SI32 index = rand() % 10 ;
	SI32 itemunique = foodlist[index] ;

	if(itemunique > 0)
	{
		*pitemunique	= itemunique;

		cltItemPriceUnit* pclprice = pclItemPrice->GetPrice(this, itemunique);
		SI32 itemnum = 1000 / pclprice->siPrice + 1 ; // 1000�� �ӽ� ����
		itemnum = max(1,itemnum);

		*pitemnum = min(10,itemnum);

		*pexp = max(2,((pclprice->siPrice*itemnum)/1000 )* 2);
		*pskillexp = max(1,*pexp / 2 );

		return true;
	}

	return false ;
}

// ������ ������ ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipMag(cltItem* pclitemlist, SI16 activeweapon)
{
	SI32 siMag = 0;
	SI32 returnval = 0;

	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[activeweapon].GetEquipMag(this ,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true) // ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_RING1].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_RING2].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_HAT].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_DRESS].GetEquipMag(this,&temper);}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_HELMET].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_ARMOUR].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_NECK].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_BELT].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_SHOES].GetEquipMag(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siMag += pclitemlist[PERSONITEM_MANTLE].GetEquipMag(this,&temper);}

	return siMag;
	//return pclitemlist[activeweapon].GetEquipMag(this) 
	//	+ pclitemlist[PERSONITEM_RING1].GetEquipMag(this)
	//	+ pclitemlist[PERSONITEM_RING2].GetEquipMag(this)
	//	+ pclitemlist[PERSONITEM_HAT].GetEquipMag(this)
	//	+ pclitemlist[PERSONITEM_DRESS].GetEquipMag(this);
}
SI32 cltItemManagerCommon::GetEquipMag(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar)
{
	SI32 siMag = 0;
	SI32 temReturnPer = 0;

	siMag = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_MAG ,&temReturnPer);

	// [����] �ƹ�Ÿ ����ü. mag. //KHY - 20090526
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siMag += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_MAG, &temReturnPer);
	//}
	
	siMag += temReturnPer;
	
	return siMag;
}
// ������ �ٷ��� ���Ѵ�.
SI32 cltItemManagerCommon::GetEquipStr(cltItem* pclitemlist , SI16 activeweapon)
{
	SI32 siStr = 0;
	SI32 returnval = 0;

	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
        		siStr += pclitemlist[PERSONITEM_RING1].GetEquipStr(this,&temper);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)	// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siStr += pclitemlist[PERSONITEM_RING2].GetEquipStr(this,&temper);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siStr += pclitemlist[PERSONITEM_MANTLE].GetEquipStr(this,&temper);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siStr += pclitemlist[PERSONITEM_HAT].GetEquipStr(this,&temper);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siStr += pclitemlist[PERSONITEM_DRESS].GetEquipStr(this,&temper);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[PERSONITEM_HELMET].GetEquipStr(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[PERSONITEM_ARMOUR].GetEquipStr(this,&temper);}
	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[activeweapon].GetEquipStr(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[PERSONITEM_NECK].GetEquipStr(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[PERSONITEM_BELT].GetEquipStr(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siStr += pclitemlist[PERSONITEM_SHOES].GetEquipStr(this,&temper);}

	return siStr;
}
// ������ �ٷ��� ���Ѵ�.
SI32 cltItemManagerCommon::GetEquipStr(cltItem* pclitemlist, SI16 activeweapon,cltCharCommon* pclchar )
{
	SI32 siStr = 0;
	SI32 temReturnPer = 0;
	
	siStr  = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_STR, &temReturnPer);

	// [����] �ƹ�Ÿ ����ü. str. //KHY - 20090526
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siStr += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_STR, &temReturnPer);
	//}
	

	siStr += temReturnPer;
	
	return siStr;
}
// ������ ���߷��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipDex(cltItem* pclitemlist ,SI16 activeweapon)
{
	SI32 siDex = 0;
	SI32 returnval = 0;

	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_RING1].GetEquipDex(this,&temper);}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_RING2].GetEquipDex(this,&temper);}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_MANTLE].GetEquipDex(this,&temper);	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_HAT].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_DRESS].GetEquipDex(this,&temper);}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_HELMET].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_ARMOUR].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[activeweapon].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_NECK].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_BELT].GetEquipDex(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siDex += pclitemlist[PERSONITEM_SHOES].GetEquipDex(this,&temper);}

	return siDex;
	//return pclitemlist[PERSONITEM_RING1].GetEquipDex(this)
	//	+ pclitemlist[PERSONITEM_RING2].GetEquipDex(this)
	//	+ pclitemlist[PERSONITEM_MANTLE].GetEquipDex(this)
	//	+ pclitemlist[PERSONITEM_HAT].GetEquipDex(this)
	//	+ pclitemlist[PERSONITEM_DRESS].GetEquipDex(this);
}

// ������ ���߷��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipDex(cltItem* pclitemlist, SI16 activeweapon,cltCharCommon* pclchar )
{
	SI32 siDex = 0;
	SI32 temReturnPer = 0;

	siDex = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_DEX ,&temReturnPer);

	// [����] �ƹ�Ÿ ����ü. dex. //KHY - 20090526
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siDex += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_DEX, &temReturnPer);
	//}

	siDex +=temReturnPer;
	
	return siDex;	
}
// ������ ������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipVit(cltItem* pclitemlist ,SI16 activeweapon)
{
	SI32 siVit = 0;
	SI32 returnval = 0;

	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_RING1].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_RING2].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_MANTLE].GetEquipVit(this,&temper);}	
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_HAT].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_DRESS].GetEquipVit(this,&temper);}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_HELMET].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_ARMOUR].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[activeweapon].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_NECK].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_BELT].GetEquipVit(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siVit += pclitemlist[PERSONITEM_SHOES].GetEquipVit(this,&temper);}

	return siVit;
	//return pclitemlist[PERSONITEM_RING1].GetEquipVit(this)
	//	+ pclitemlist[PERSONITEM_RING2].GetEquipVit(this)
	//	+ pclitemlist[PERSONITEM_MANTLE].GetEquipVit(this)
	//	+ pclitemlist[PERSONITEM_HAT].GetEquipVit(this)
	//	+ pclitemlist[PERSONITEM_DRESS].GetEquipVit(this);

}

// ������ ������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipVit(cltItem* pclitemlist, SI16 activeweapon,cltCharCommon* pclchar)
{
	SI32 siVit = 0;
	SI32 temReturnPer = 0;

	siVit = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_VIT,&temReturnPer);

	// [����] �ƹ�Ÿ ����ü. vit.
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siVit += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_VIT, &temReturnPer);
	//}
	

	siVit  += temReturnPer;

	return siVit;	
}
// ������ ���� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipLuk(cltItem* pclitemlist ,SI16 activeweapon)
{
	SI32 siLuk = 0;
	SI32 returnval = 0;

	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_RING1].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_RING2].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_DRESS].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_HAT].GetEquipLuk(this,&temper);}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_HELMET].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_ARMOUR].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[activeweapon].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_NECK].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_BELT].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_SHOES].GetEquipLuk(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siLuk += pclitemlist[PERSONITEM_MANTLE].GetEquipLuk(this,&temper);}	
	return siLuk;
}

// ������ ���� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipLuk(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar )
{
	SI32 siLuk = 0;
	SI32 temReturnPer = 0;
	
	siLuk = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_LUK,&temReturnPer);

	// [����] �ƹ�Ÿ ����ü. luk.
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siLuk += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_LUK, &temReturnPer);
	//}

	siLuk +=temReturnPer;

	return siLuk;
}
// ������ �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipHnd(cltItem* pclitemlist , SI16 activeweapon)
{
	SI32 siHnd = 0;
	SI32 temper = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_RING1].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)	// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_RING2].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)	// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_DRESS].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true )	// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_HAT].GetEquipHnd(this,&temper);}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_HELMET].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_ARMOUR].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[activeweapon].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_NECK]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_NECK].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_BELT].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_SHOES].GetEquipHnd(this,&temper);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siHnd += pclitemlist[PERSONITEM_MANTLE].GetEquipHnd(this,&temper);}	
	return siHnd;
}


// ������ �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipHnd(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar )
{
	SI32 siHnd = 0;
	SI32 temReturnPer = 0;
	
	siHnd = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_HND,&temReturnPer);

	// [����] �ƹ�Ÿ ����ü. hand.
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siHnd += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_HND, &temReturnPer);
	//}

	siHnd += temReturnPer;

	return siHnd;
}

// ������ �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEquipWis(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar )
{
	SI32 siWis = 0;
	SI32 temReturnPer = 0;
	
	siWis = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_STATE_WIS, &temReturnPer);

	// [����] �ƹ�Ÿ ����ü. vit.
	//if( pclClient->IsCountrySwitch( Switch_Avatar_artisan ) )
	//{
	//	siWis += GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_AVATAR_STATE_WIS, &temReturnPer );
	//}

	siWis += temReturnPer;

	return siWis;
}


// ������ ����Ÿ���� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponAttackType(cltItem* pclitemlist, SI16 activeweapon)
{
	return pclitemlist[activeweapon].GetAttackType(this);
}

// ������ ��Ÿ��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponAttackRange(cltItem* pclitemlist, SI16 activeweapon)
{
	return pclitemlist[activeweapon].GetAttackRange(this);
}

// ������ ���� �ֱ⸦ ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponAttackInterval(cltItem* pclitemlist, SI16 activeweapon)
{
	return pclitemlist[activeweapon].GetAttackInterval(this);
}

// ����� ����  ���Ѵ�. 
SI32 cltItemManagerCommon::GetLuck(cltItem* pclitemlist)
{
	SI32 siLuck = 0;

// �Ⱦ���.
/*
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siLuck += pclitemlist[PERSONITEM_ARMOUR].GetLuck(this);

	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siLuck += pclitemlist[PERSONITEM_HELMET].GetLuck(this);
*/
	if(pclitemlist[PERSONITEM_HAT].siUnique > 0)
	{
		if(IsExpiredDate(&pclitemlist[PERSONITEM_HAT]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
			siLuck += pclitemlist[PERSONITEM_HAT].GetLuck(this);
	}

	if(pclitemlist[PERSONITEM_DRESS].siUnique > 0)
	{
		if(IsExpiredDate(&pclitemlist[PERSONITEM_DRESS]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
			siLuck += pclitemlist[PERSONITEM_DRESS].GetLuck(this);
	}
	return siLuck;

	//SI32 ac = pclitemlist[PERSONITEM_ARMOUR].GetLuck(this) 
	//		+ pclitemlist[PERSONITEM_HELMET].GetLuck(this)
	//		+ pclitemlist[PERSONITEM_HAT].GetLuck(this)
	//		+ pclitemlist[PERSONITEM_DRESS].GetLuck(this);

	//return ac;
}


// ������ AC�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetAC(cltItem* pclitemlist)
{
	SI32		siAC = 0;
	SI32		returnval = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siAC += pclitemlist[PERSONITEM_HELMET].GetAC(this);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true)// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siAC += pclitemlist[PERSONITEM_ARMOUR].GetAC(this);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siAC += pclitemlist[PERSONITEM_SHOES].GetAC(this);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siAC += pclitemlist[PERSONITEM_BELT].GetAC(this);}
	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true )// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
	{siAC += pclitemlist[PERSONITEM_MANTLE].GetAC(this);}
	return siAC;

	// ���� ����, 
	//SI32 helmetac = pclitemlist[PERSONITEM_HELMET].GetAC(this);
	//if(helmetac)
	//{
	//	helmetac += pclitemlist[PERSONITEM_HAT].GetAC(this) / DRESS_ADD_DPOWER_RATE;
	//}
	//else
	//{
	//	helmetac = pclitemlist[PERSONITEM_HAT].GetAC(this);
	//}

	// ���� ����, 
	//SI32 armourac = pclitemlist[PERSONITEM_ARMOUR].GetAC(this);
	//if(armourac)
	//{
	//	armourac += pclitemlist[PERSONITEM_DRESS].GetAC(this) / DRESS_ADD_DPOWER_RATE;
	//}
	//else
	//{
	//	armourac = pclitemlist[PERSONITEM_DRESS].GetAC(this);
	//}


	//SI32 ac = helmetac 
	//		+ armourac
	//		+ pclitemlist[PERSONITEM_SHOES].GetAC(this)
	//		+ pclitemlist[PERSONITEM_BELT].GetAC(this)
	//		+ pclitemlist[PERSONITEM_MANTLE].GetAC(this);

	//return ac;
}
// ������ AC�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetAC(cltItem* pclitemlist, cltCharCommon* pclchar)
{
	SI32		siAC = 0;
	SI32		returnval = 0;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == true &&// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		CheckCondition(pclitemlist[PERSONITEM_HELMET].siUnique, pclchar, &returnval) == true)	//�������� ������ �¾ƾ� �Ѵ�.���� ������ �ݿ��ȵ�[2007.08.06 �ռ���]	
	{
		siAC += pclitemlist[PERSONITEM_HELMET].GetAC(this);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == true &&// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		CheckCondition(pclitemlist[PERSONITEM_ARMOUR].siUnique, pclchar, &returnval) == true)		//�������� ������ �¾ƾ� �Ѵ�.���� ������ �ݿ��ȵ�[2007.08.06 �ռ���]
	{
		siAC += pclitemlist[PERSONITEM_ARMOUR].GetAC(this);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true &&// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		CheckCondition(pclitemlist[PERSONITEM_SHOES].siUnique, pclchar, &returnval) == true)		//�������� ������ �¾ƾ� �Ѵ�.���� ������ �ݿ��ȵ�[2007.08.06 �ռ���]
	{
		siAC += pclitemlist[PERSONITEM_SHOES].GetAC(this);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true &&// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		CheckCondition(pclitemlist[PERSONITEM_BELT].siUnique, pclchar, &returnval) == true)		//�������� ������ �¾ƾ� �Ѵ�.���� ������ �ݿ��ȵ�[2007.08.06 �ռ���]
	{
		siAC += pclitemlist[PERSONITEM_BELT].GetAC(this);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true &&// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		CheckCondition(pclitemlist[PERSONITEM_MANTLE].siUnique, pclchar, &returnval) == true)		//�������� ������ �¾ƾ� �Ѵ�.���� ������ �ݿ��ȵ�[2007.08.06 �ռ���]
	{
		siAC += pclitemlist[PERSONITEM_MANTLE].GetAC(this);
	}

	return siAC;
}


// ��æƮ ���� AC�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEnchantAC(cltItem* pclitemlist,cltCharCommon* pclchar)
{
	SI32 returnval = 0;
	bool bClient = false ;
	if ( pclClient->GameMode == GAMEMODE_CLIENT )
		bClient = true ;

	// ���� �Ӽ� ����, 
	SI32 helmetac = pclitemlist[PERSONITEM_HELMET].GetEnchantAC(this,bClient);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == false  && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_HELMET].siUnique, pclchar, &returnval) == false)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
		helmetac = 0;
	
	if(helmetac)
	{
		helmetac += pclitemlist[PERSONITEM_HAT].GetEnchantAC(this,bClient) / DRESS_ADD_DPOWER_RATE;
	}
	else
	{
		helmetac = pclitemlist[PERSONITEM_HAT].GetEnchantAC(this,bClient);
	}

	// ���� �Ӽ� ����, 
	SI32 armourac = pclitemlist[PERSONITEM_ARMOUR].GetEnchantAC(this,bClient);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == false && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_ARMOUR].siUnique, pclchar, &returnval) == false)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
		armourac = 0;

	if(armourac)
	{
		armourac += pclitemlist[PERSONITEM_DRESS].GetEnchantAC(this,bClient) / DRESS_ADD_DPOWER_RATE;
	}
	else
	{
		armourac = pclitemlist[PERSONITEM_DRESS].GetEnchantAC(this,bClient);
	}

	SI32 ac = helmetac + armourac;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true  && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_SHOES].siUnique, pclchar, &returnval) == true)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
	{
		ac += pclitemlist[PERSONITEM_SHOES].GetEnchantAC(this,bClient);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_BELT].siUnique, pclchar, &returnval) == true)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
	{
		ac += pclitemlist[PERSONITEM_BELT].GetEnchantAC(this,bClient);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_MANTLE].siUnique, pclchar, &returnval) == true)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
	{
		ac += pclitemlist[PERSONITEM_MANTLE].GetEnchantAC(this,bClient);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_RING1].siUnique, pclchar, &returnval) == true)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
	{
		ac += pclitemlist[PERSONITEM_RING1].GetEnchantAC(this,bClient);
	}

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true && // �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		CheckCondition(pclitemlist[PERSONITEM_RING2].siUnique, pclchar, &returnval) == true)//������ ���� ������ �ɷ�x[2007.08.07 �ռ���]
	{
		ac += pclitemlist[PERSONITEM_RING2].GetEnchantAC(this,bClient);
	}

		//+ pclitemlist[PERSONITEM_SHOES].GetEnchantAC(this,bClient)
		//+ pclitemlist[PERSONITEM_BELT].GetEnchantAC(this,bClient)
		//+ pclitemlist[PERSONITEM_MANTLE].GetEnchantAC(this,bClient)
		//+ pclitemlist[PERSONITEM_RING1].GetEnchantAC(this,bClient)
		//+ pclitemlist[PERSONITEM_RING2].GetEnchantAC(this,bClient);

	return ac;
}


// ��æƮ ���� AC�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEnchantACFrom(cltItem* pclitemlist, SI32 attacktype)
{
	bool bClient = false ;
	if ( pclClient->GameMode == GAMEMODE_CLIENT )
		bClient = true ;

	// ���� �Ӽ� ����, 
	SI32 helmetac = pclitemlist[PERSONITEM_HELMET].GetEnchantACFrom(this,bClient, attacktype);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_HELMET]) == false)		// �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		helmetac = 0;

	if(helmetac)
	{
		helmetac += pclitemlist[PERSONITEM_HAT].GetEnchantACFrom(this,bClient , attacktype) / DRESS_ADD_DPOWER_RATE;
	}
	else
	{
		helmetac = pclitemlist[PERSONITEM_HAT].GetEnchantACFrom(this,bClient, attacktype);
	}


	// ���� �Ӽ� ����, 
	SI32 armourac = pclitemlist[PERSONITEM_ARMOUR].GetEnchantACFrom(this,bClient, attacktype);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_ARMOUR]) == false)		// �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		armourac = 0;

	if(armourac)
	{
		armourac += pclitemlist[PERSONITEM_DRESS].GetEnchantACFrom(this,bClient, attacktype) / DRESS_ADD_DPOWER_RATE;
	}
	else
	{
		armourac = pclitemlist[PERSONITEM_DRESS].GetEnchantACFrom(this,bClient ,attacktype );
	}


	SI32 ac = helmetac + armourac;

	if(IsExpiredDate(&pclitemlist[PERSONITEM_SHOES]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		ac += pclitemlist[PERSONITEM_SHOES].GetEnchantACFrom(this,bClient, attacktype);

	if(IsExpiredDate(&pclitemlist[PERSONITEM_BELT]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		ac += pclitemlist[PERSONITEM_BELT].GetEnchantACFrom(this,bClient, attacktype);

	if(IsExpiredDate(&pclitemlist[PERSONITEM_MANTLE]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		ac += pclitemlist[PERSONITEM_MANTLE].GetEnchantACFrom(this,bClient, attacktype);

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		ac += pclitemlist[PERSONITEM_RING1].GetEnchantACFrom(this,bClient, attacktype);

	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		ac += pclitemlist[PERSONITEM_RING2].GetEnchantACFrom(this,bClient, attacktype);

		//+ pclitemlist[PERSONITEM_SHOES].GetEnchantACFrom(this,bClient, attacktype)
		//+ pclitemlist[PERSONITEM_BELT].GetEnchantACFrom(this,bClient ,attacktype )
		//+ pclitemlist[PERSONITEM_MANTLE].GetEnchantACFrom(this,bClient, attacktype)
		//+ pclitemlist[PERSONITEM_RING1].GetEnchantACFrom(this,bClient, attacktype)
		//+ pclitemlist[PERSONITEM_RING2].GetEnchantACFrom(this,bClient, attacktype);

	return ac;
}

// ��æƮ ���� AC�� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEnchantAttFrom(cltItem* pclitemlist, SI32 attacktype)
{
	bool bClient = false ;
	if ( pclClient->GameMode == GAMEMODE_CLIENT )
		bClient = true ;

	// ��1 �Ӽ� ����, 
	SI32 ring1 = pclitemlist[PERSONITEM_RING1].GetEnchantAttFrom(this,bClient, attacktype);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING1]) == false)		// �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		ring1 = 0;


	// ��2 �Ӽ� ����, 
	SI32 ring2 = pclitemlist[PERSONITEM_RING2].GetEnchantAttFrom(this,bClient, attacktype);
	if(IsExpiredDate(&pclitemlist[PERSONITEM_RING2]) == false)		// �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
		ring2 = 0;

	
	SI32 weapon =0;

	if(bClient)
	{
		SI32 activeweapon = pclClient->pclCM->CR[1]->ActiveWeapon; 
		weapon = pclitemlist[activeweapon].GetEnchantAttFrom(this,bClient, attacktype);
		if(IsExpiredDate(&pclitemlist[activeweapon]) == false)		// �Ⱓ�� ���� �������� ȿ���� �������. - by LEEKH 2007.04.11
			weapon = 0;
	}



	SI32 att = ring1 + ring2 + weapon;

	return att;
}
// ������ �ּ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon)
{
	SI32	siMinDamage = 0;
	SI32	returnval = 0;

	SI32 CrystalMinDamagePer = 0;

	if((IsExpiredDate(&pclitemlist[activeweapon]) == true)&&(pclitemlist[activeweapon].siUnique > 0))		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMinDamage += pclitemlist[activeweapon].GetMinDamage(this ,&CrystalMinDamagePer);
	return siMinDamage;
}
SI32 cltItemManagerCommon::GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar )
{
	SI32	siMinDamage = 0;
	SI32 CrystalMinDamagePer = 0;
	SI32 returnval = 0;

	if((IsExpiredDate(&pclitemlist[activeweapon]) == true)&&(pclitemlist[activeweapon].siUnique > 0)&&
		CheckCondition(pclitemlist[PERSONITEM_HELMET].siUnique, pclchar, &returnval) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMinDamage += pclitemlist[activeweapon].GetMinDamage(this ,&CrystalMinDamagePer);

	return siMinDamage;

}


// ������ �ּ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar  , SI32 * CrystalPer)
{
	SI32	siMinDamage = 0;
	//SI32 CrystalMinDamagePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siMinDamage = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK,CrystalPer);

	//siMinDamage = siMinDamage + (siMinDamage * CrystalMinDamagePer / 100);
		
	return siMinDamage;
	//return pclitemlist[activeweapon].GetMinDamage(this);
}

// ��ȯ����  �ּ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltSummon* pclsummon)
{
	SI32		siMinDamage = 0;

	SI32 CrystalMinDamagePer = 0;

	if( IsExpiredDate(&pclitemlist[activeweapon]) == true )		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMinDamage += pclitemlist[activeweapon].GetMinDamage(this ,&CrystalMinDamagePer);

	return siMinDamage;
	//return pclitemlist[activeweapon].GetMinDamage(this);
}

// ������ ��æƮ Ÿ���� ���Ѵ�. 
SI32 cltItemManagerCommon::GetEnchantWeaponType(cltItem* pclitemlist, SI16 activeweapon)
{
	return pclitemlist[activeweapon].GetEnchantType(this);
}

// ������ �ִ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon)
{
	SI32	siMaxDamage = 0;
	SI32	returnval = 0;

	SI32 CrystalMaxDamagePer = 0;

	if((IsExpiredDate(&pclitemlist[activeweapon]) == true)&&(pclitemlist[activeweapon].siUnique > 0))		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMaxDamage += pclitemlist[activeweapon].GetMaxDamage(this ,&CrystalMaxDamagePer);

	return siMaxDamage;
	//return pclitemlist[activeweapon].GetMaxDamage(this);
}

// ������ �ִ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar )
{
	SI32	siMaxDamage = 0;
	SI32	returnval = 0;

	SI32 CrystalMaxDamagePer = 0;

	if((IsExpiredDate(&pclitemlist[activeweapon]) == true)&&(pclitemlist[activeweapon].siUnique > 0)&&
		CheckCondition(pclitemlist[PERSONITEM_HELMET].siUnique, pclchar, &returnval) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMaxDamage += pclitemlist[activeweapon].GetMaxDamage(this ,&CrystalMaxDamagePer);

	return siMaxDamage;
	//return pclitemlist[activeweapon].GetMaxDamage(this);
}


// ������ �ִ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar , SI32 * CrystalPer)
{
	SI32	siMaxDamage = 0;
	//SI32 CrystalMaxDamagePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siMaxDamage = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK,CrystalPer);

	//siMaxDamage = siMaxDamage + (siMaxDamage * CrystalMaxDamagePer / 100);	

	return siMaxDamage;
}

// ��ȯ���� �ִ� �������� ���Ѵ�. 
SI32 cltItemManagerCommon::GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltSummon* pclsummon )
{
	SI32	siMaxDamage = 0;

	SI32 CrystalMaxDamagePer = 0;

	if(IsExpiredDate(&pclitemlist[activeweapon]) == true)		// ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		siMaxDamage += pclitemlist[activeweapon].GetMaxDamage(this , &CrystalMaxDamagePer);

	return siMaxDamage;
	//return pclitemlist[activeweapon].GetMaxDamage(this);
}

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
// ���� ���ݷ��� ���Ѵ�. - �߰� ũ����Ż. 
SI32 cltItemManagerCommon::GetAddMagicalMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar )
{
	SI32	siMagicalDamage = 0;
	SI32 CrystalMagicalDamagePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siMagicalDamage = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK,&CrystalMagicalDamagePer);
	
	// �������� ���ۼ�Ʈ ����ߴ��� ������. 
	return CrystalMagicalDamagePer;
}


SI32 cltItemManagerCommon::GetAddMagicalMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar )
{
	SI32	siMagicalDamage = 0;
	SI32 CrystalMagicalDamagePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siMagicalDamage = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK,&CrystalMagicalDamagePer);

	// �������� ���ۼ�Ʈ ����ߴ��� ������. 
	return CrystalMagicalDamagePer;
}

SI32 cltItemManagerCommon::GetAddMagicalDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar )
{
	SI32	siMagicalDamage = 0;
	SI32 CrystalMagicalDamagePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siMagicalDamage = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_ATTACK,&CrystalMagicalDamagePer);

	// �������� ���ۼ�Ʈ ����ߴ��� ������. 
	return CrystalMagicalDamagePer;
}

// ������� ��� ����� ���Ѵ�. 
//KHY - 0320 - ��ȸ�� ����. - ���Ⱓ�� �����ְ�, �����ϰ� �ִ� �����ۿ� ���Ͽ� �˻��Ѵ�.
SI32 cltItemManagerCommon::GetUpgradeSkillLevel(cltItem* pclitemlist, SI32 skillunique, SI32 id )
{
	SI32 skilllevel = 0;
	SI32 crySkilllevel = 0;
	SI32 returnval = 0;
	SI32 tempSkilllevel = 0;
	SI16 activeweapon = PERSONITEM_WEAPON1;
	
	if(pclClient->pclCM->IsValidID(id) == true)
		activeweapon = pclClient->pclCM->CR[id ]->ActiveWeapon;
	
	for(int pitempos=0; pitempos <PERSONITEM_INV0 ; pitempos++)
	{
		switch(pitempos)
		{
		// �˻� �������� �߰�, �� ������ �̺κп���  - 
		case PERSONITEM_HELMET:
		case PERSONITEM_ARMOUR:
		case PERSONITEM_NECK:
		case PERSONITEM_RING1:	
		case PERSONITEM_RING2:
		case PERSONITEM_BELT:
		case PERSONITEM_SHOES:
		case PERSONITEM_MANTLE:
		case PERSONITEM_HAT:
		case PERSONITEM_DRESS:
			{
				if(pclitemlist[pitempos].siUnique > 0) // 1 -�� �������� ���� �ϰ� �־�� �Ѵ�.
				{
					if(IsExpiredDate(&pclitemlist[pitempos]) == true) // 2 - ���Ⱓ�� ���� �־�� �Ѵ�. - Ȥ�� ���� �������̰ų�.
					{
						//if(CheckCondition(pclitemlist[pitempos].siUnique, pclchar, &returnval) == true ) // 3 - ���� ������ �����ؾ߸� �Ѵ�.
						{
							////////////////////////////////////////////////////////////////////////////////////////////
							// ��Ÿ ������ ��񿡼� ��ų�� �ö󰡴� ��� ���.
							tempSkilllevel += pclitemlist[pitempos].GetUpgradeSkillLevel(this, skillunique ,false); // ũ����Ż�� ���⼭ ������� �ʴ´�.

							// ����ü�� ��񿡼� ��ų�� �ö󰡴� ��� ���.
							if(pclitemlist[pitempos].siUseCrystalNum>0)
							{
								UI08 uiSkillunique = pclitemlist[pitempos].GetCrystalAbilityFromSkillUnique(skillunique);

								crySkilllevel = pclitemlist[pitempos].GetAllCrystalAbilityNum(uiSkillunique);

								// �� �������� ����ü�� �ö󰡴� ��ų������ ���� ��Ų��.
								skilllevel = skilllevel + crySkilllevel; 
							}							
							//////////////////////////////////////////////////////////////////////////////////////////////////
						}
					}
				}
			}
			break;
		default :
			break;
		}
	}

	//  - activeweapon�� ��¿�� ����. - ���⼭ ���� �˻�.
	if((pclitemlist[activeweapon].siUnique > 0) && // 1 -�� �������� ���� �ϰ� �־�� �Ѵ�.
		(IsExpiredDate(&pclitemlist[activeweapon]) == true)) // 2 - ���Ⱓ�� ���� �־�� �Ѵ�. - Ȥ�� ���� �������̰ų�.
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		// ��Ÿ ������ ��񿡼� ��ų�� �ö󰡴� ��� ���.
		tempSkilllevel += pclitemlist[activeweapon].GetUpgradeSkillLevel(this, skillunique ,false); // ũ����Ż�� ���⼭ ������� �ʴ´�.

		// ����ü�� ��񿡼� ��ų�� �ö󰡴� ��� ���.
		if(pclitemlist[activeweapon].siUseCrystalNum>0)
		{
			UI08 uiSkillunique = pclitemlist[activeweapon].GetCrystalAbilityFromSkillUnique(skillunique);

			crySkilllevel = pclitemlist[activeweapon].GetAllCrystalAbilityNum(uiSkillunique);

			// �� �������� ����ü�� �ö󰡴� ��ų������ ���� ��Ų��.
			skilllevel = skilllevel + crySkilllevel; 
		}							
		//////////////////////////////////////////////////////////////////////////////////////////////////
	}

	// ��Ʈ �����ۿ� ���� ����� ����.
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		switch(skillunique)
		{
			case SKILL_USESWORD1:	
			case SKILL_USESPEAR1:	
			case SKILL_USEBOW1:		
			case SKILL_USEAXE1:	
			case SKILL_USEGUN1:		
			case SKILL_USESTAFF1:		
				{
					if( pclClient->pclCM->CR[id] )
					{
						if( pclClient->pclCM->CR[id]->m_siSetItemType ) 
						{
							tempSkilllevel += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclClient->pclCM->CR[id], SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL, USE_SETITEM_1);
							tempSkilllevel += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclClient->pclCM->CR[id], SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL, USE_SETITEM_2);
							tempSkilllevel += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclClient->pclCM->CR[id], SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL, USE_SETITEM_3);
							tempSkilllevel += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclClient->pclCM->CR[id], SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL, USE_SETITEM_4);
							tempSkilllevel += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclClient->pclCM->CR[id], SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL, USE_SETITEM_5);
						}
					}
				}
				break;
		}
	}

	return (skilllevel + tempSkilllevel);	

}

// ����� �ʻ�� ����� ���Ѵ�.   (���⿡��) 
SI32 cltItemManagerCommon::GetEquipCriticalHitRate(cltItem* pclitemlist, SI16 activeweapon)
{
	SI32 pos;
	SI32 siTotalRate = 0;
	
	for(SI32 i = 0;i < 2;i++)
	{
		if(i == 0)	pos = activeweapon;
		else		pos = PERSONITEM_BELT;

		// ��Ƽ�� ���⿡�� ã�´�. 
		cltItem* pclitem = (cltItem*)&pclitemlist[pos];
		
		if(pclitem->siUnique <= 0)continue;

		if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_UPCRITICAL)
		{
			siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara1;
		}
		if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_UPCRITICAL)
		{
			siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara2;
		}
	}

	return siTotalRate;
}

// ����� �ʻ�� ����� ���Ѵ�. ����ü -   (��� ���.) 
SI32 cltItemManagerCommon::GetEquipCrystalCriticalHitRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalCriticalHitRatePer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_SPECIAL_DEATHBLOW,&CrystalCriticalHitRatePer);

	return CrystalCriticalHitRatePer;
}

// ����� ���߷� ����� ���Ѵ�.  (���⿡��)
SI32 cltItemManagerCommon::GetEquipHitRate(cltItem* pclitemlist, SI16 activeweapon)
{
	SI32 siTotalRate = 0;

	cltItem* pclitem = (cltItem*)&pclitemlist[activeweapon];
	if(pclitem->siUnique == 0)		return siTotalRate;

	if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_UPHITRATE)
	{
		siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara1;
	}
	if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_UPHITRATE)
	{
		siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara2;
	}
	
	return siTotalRate;
}

// ����� ���߷� ����� ���Ѵ�. ����ü. - ����
SI32 cltItemManagerCommon::GetEquipCrystalPhysicalHitRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPhysicalHitRatePer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE,&CrystalPhysicalHitRatePer);

	return CrystalPhysicalHitRatePer;
}

// ����� ���߷� ����� ���Ѵ�. ����ü. - ����.
SI32 cltItemManagerCommon::GetEquipCrystalMagicalHitRate(cltItem* pclitemlist, SI16 activeweapon , cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalMagicalHitRatePer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_HITRATE, &CrystalMagicalHitRatePer);

	return CrystalMagicalHitRatePer;
}

SI32 cltItemManagerCommon::GetEquipCrystalPhysicalDefensiveRate(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar  , SI32 * CrystalPer )
{
	SI32	siDefensive = 0;
	//SI32 CrystalDefensivePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siDefensive = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE,CrystalPer);

	//siDefensive = siDefensive + (siDefensive * CrystalDefensivePer / 100);	

	return siDefensive;
}

SI32 cltItemManagerCommon::GetEquipCrystalMagicalDefensiveRate(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar  , SI32 * CrystalPer)
{
	SI32	siDefensive = 0;
	//SI32 CrystalDefensivePer = 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	siDefensive = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE,CrystalPer);

	//siDefensive = siDefensive + (siDefensive * CrystalDefensivePer / 100);	

	return siDefensive;
}

// ����� ȸ���� ����� ���Ѵ�. ����ü. - ����
SI32 cltItemManagerCommon::GetEquipCrystalPhysicalDodgeRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPhysicalDodgeRatePer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE,&CrystalPhysicalDodgeRatePer);

	return CrystalPhysicalDodgeRatePer;
}

// ����� ȸ���� ����� ���Ѵ�. ����ü. - ����
SI32 cltItemManagerCommon::GetEquipCrystalMagicalDodgeRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalMagicalDodgeRatePer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE,&CrystalMagicalDodgeRatePer);

	return CrystalMagicalDodgeRatePer;
}

// ����� ü�� ����� ���Ѵ�. ����ü.
SI32 cltItemManagerCommon::GetEquipCrystalHitpoint(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalHitpointPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_HITPOINT,&CrystalHitpointPer);

	return CrystalHitpointPer;
}

// ����� ������ ����� ���Ѵ�. ����ü. 
SI32 cltItemManagerCommon::GetEquipCrystalManapoint(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalManapointPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_MANAPOINT,&CrystalManapointPer);

	return CrystalManapointPer;
}

// ����� ���Է� ����� ���Ѵ�. ����ü.
SI32 cltItemManagerCommon::GetEquipCrystalWeigt(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalWeigtPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_EFFECT_WEIGHT,&CrystalWeigtPer);

	return CrystalWeigtPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalFireAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_FIREATTACK,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalWaterAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_WATERATTACK,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalWindAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_WINDATTACK,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalEarthAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_EARTHATTACK,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalFireDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalWaterDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalWindDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE,&CrystalPer);

	return CrystalPer;
}

SI32 cltItemManagerCommon::GetEquipCrystalEarthDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar)
{
	SI32 siRatePer = 0;
	SI32 CrystalPer = 0;

	siRatePer = GetCountEquipPersonitemAbility(pclitemlist,activeweapon,pclchar , CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE,&CrystalPer);

	return CrystalPer;
}
// ����ü Ÿ���� ������ ����. - abilityType
// �⺻���� �˻�� ��� ���� ���⼭ ó���Ѵ�.
//KHY - 20090526 - �ƹ�Ÿ ����ü �߰�.
SI32 cltItemManagerCommon::GetCountEquipPersonitemAbility(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar  ,UI08 abilityType , SI32 *ReturnValPer)
{
	SI32	returnval = 0;
	SI32 temReturnVal = 0;
	
	SI32 siAppendCrystalPoint		= 0;	// ��ø ������ ����ü ����Ʈ
	SI32 siCantAppendCrystalPoion	= 0;	// ��ø �Ұ����� ����ü ����Ʈ
											

	SI32 oldTemReturnVal = 0; // �ɷ���ø �Ұ��� ����ü ���, ���� ���� ���� ������ ���Ѵ�.
	SI32 oldReturnValPer= 0;  // �ɷ���ø �Ұ��� ����ü ���, ���� ���� ���� ������ ���Ѵ�.


	// �ɷ�ġ�� ������ �ʿ��� ��� - temReturnVal += , ReturnValPer  ���� ���� �ѱ�� ������Ŵ

	// �ɷ���ø�� �ȵǰ� ���� ���� ū���ϳ� ����� - oldTemReturnVal = , &oldReturnValPer ������ ���� ���Ͽ� ū ������ ����, ����


	for(int pitempos=0; pitempos <PERSONITEM_INV0 ; pitempos++)
	{
		// [����] ���ο� ������ �ý���
		bool bCanUseWithDurability = true;
		if( pclClient->IsCountrySwitch( Switch_NewDurability) )
		{
			SI16 siDurability = pclitemlist[pitempos].GetDurability();
			if( siDurability <= 0 )
				bCanUseWithDurability = false;
		}

		switch(pitempos)
		{
			// �˻� �������� �߰�, �� ������ �̺κп���  - 
			case PERSONITEM_HELMET:
			case PERSONITEM_ARMOUR:
			case PERSONITEM_BELT:
			case PERSONITEM_SHOES:
				{
					// �ƹ�Ÿ ����ü�� ��� �ü� �������� �˻��� �ʿ䵵 ����.
					if(IsAbatarCrystalItem(abilityType) == true)
						continue;
					
					if(pclitemlist[pitempos].siUnique > 0) // 1 -�� �������� ���� �ϰ� �־�� �Ѵ�.
					{
						// [����] �������� ���� �־�� �Ѵ�.
						if(IsExpiredDate(&pclitemlist[pitempos]) == true && bCanUseWithDurability ) // 2 - ���Ⱓ�� ���� �־�� �Ѵ�. - Ȥ�� ���� �������̰ų�.
						{
							if(CheckCondition(pclitemlist[pitempos].siUnique, pclchar, &returnval) == true ) // 3 - ���� ������ �����ؾ߸� �Ѵ�.
							{
								switch(abilityType) // ũ����Ż�� �ɷ� �ε����� ���� ���. - Ÿ�Կ� ���� �Լ��� �ٸ���. 
								{
									// ///////////////////////////////////////////////////
									//   oldTemReturnVal =  : �� ������ �߿��� ���� ū �ɷ� ��ġ �ϳ��� ����. =  �ɷ� ��ø : �Ұ�.
									//   temReturnVal +=     : �� ������ �� �ɷ� ��ġ�� ��� �����Ͼ� ���Ѵ�.	 =  �ɷ� ��ø : ����.						
									//////////// - ���� - ////////////////////////////////// - ��� ��ø ����.
									case CRYSTALABILITY_STATE_STR:
										 temReturnVal += pclitemlist[pitempos].GetEquipStr(this, &oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_DEX:
										 temReturnVal += pclitemlist[pitempos].GetEquipDex(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_MAG:
										 temReturnVal += pclitemlist[pitempos].GetEquipMag(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_VIT:
										 temReturnVal += pclitemlist[pitempos].GetEquipVit(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_LUK:
										 temReturnVal += pclitemlist[pitempos].GetEquipLuk(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_HND:
										 temReturnVal += pclitemlist[pitempos].GetEquipHnd(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_STATE_WIS:
										 temReturnVal += pclitemlist[pitempos].GetEquipWis(this,&oldReturnValPer); 
										break;
																		
									//////////// -ȿ��  - //////////////////////////////////
									case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK:			// ���� �ּ� ���ݷ�.
										oldTemReturnVal = pclitemlist[pitempos].GetMinDamage(this , &oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK:		// ���� �ִ� ���ݷ�.
										oldTemReturnVal =  pclitemlist[pitempos].GetMaxDamage(this, &oldReturnValPer);
										break;										
									case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK:			 // ���� �ּ� ���ݷ�
										oldTemReturnVal =  pclitemlist[pitempos].GetAddMagicalMinDamage(this, &oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK:			 // ���� �ִ� ���ݷ�
										oldTemReturnVal =  pclitemlist[pitempos].GetAddMagicalMaxDamage(this, &oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE:			// ���� ���߷�
										oldTemReturnVal =  pclitemlist[pitempos].GetPhysicalHitRate(this, &oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE:				// ���� ���߷�
										oldTemReturnVal =  pclitemlist[pitempos].GetMagicalHitRate(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE:			// ���� ȸ����
										oldTemReturnVal = pclitemlist[pitempos].GetPhysicalDodgeRate(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE:			// ���� ȸ����
										oldTemReturnVal = pclitemlist[pitempos].GetMagicalDodgeRate(this,&oldReturnValPer);
										break;										
									case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE:		// ���� ����� - ��ø
										temReturnVal += pclitemlist[pitempos].GetPhysicalAC(this ,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE:		// ���� �����
										oldTemReturnVal =  pclitemlist[pitempos].GetMagicalAC(this ,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_HITPOINT:						// ü�·�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalHitpoint(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_MANAPOINT:					// ������
										oldTemReturnVal =  pclitemlist[pitempos].GetCrystalManapoint(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_EFFECT_WEIGHT:						// ���Է�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalWeigt(this,&oldReturnValPer);
										break;
								///////////////////- �Ӽ� - //////////////////////////////////////////////////////////////	
									case CRYSTALABILITY_ATTRIBUTE_FIREATTACK:				// �� �Ӽ� ���ݷ�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalFireAttack(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_WATERATTACK:				// �� �Ӽ� ���ݷ�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalWaterAttack(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_WINDATTACK:				// �ٶ� �Ӽ� ���ݷ�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalWindAttack(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK:				// �� �Ӽ� ���ݷ�
										oldTemReturnVal = pclitemlist[pitempos].GetCrystalEarthAttack(this,&oldReturnValPer);
										break;

									case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE:				 // �� �Ӽ� ����
										oldTemReturnVal =  pclitemlist[pitempos].GetCrystalFireDeffence(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE:			 // �� �Ӽ� ����
										oldTemReturnVal =  pclitemlist[pitempos].GetCrystalWaterDeffence(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE:				// �ٶ� �Ӽ� ����
										oldTemReturnVal =  pclitemlist[pitempos].GetCrystalWindDeffence(this,&oldReturnValPer);
										break;
									case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE:			// �� �Ӽ� ����
										oldTemReturnVal =  pclitemlist[pitempos].GetCrystalEarthDeffence(this,&oldReturnValPer);
										break;
								///////////////////- Ư�� �ɷ� - //////////////////////////////////////////////////////////////	
									case CRYSTALABILITY_SPECIAL_DEATHBLOW:					// �ʻ�. - ũ��Ƽ�� �� ���.
										oldTemReturnVal =  pclitemlist[pitempos].GetCriticalHitRate(this,&oldReturnValPer);
										break;

									default :
										break;
								}							
							}
						}
					}
					break;
				}
			case PERSONITEM_NECK:
			case PERSONITEM_RING1:	
			case PERSONITEM_RING2:
			case PERSONITEM_MANTLE:
			case PERSONITEM_HAT:
			case PERSONITEM_DRESS:
				{
					if(pclitemlist[pitempos].siUnique > 0) // 1 -�� �������� ���� �ϰ� �־�� �Ѵ�.
					{
						// [����] �������� ���� �־�� �Ѵ�.
						if(IsExpiredDate(&pclitemlist[pitempos]) == true && bCanUseWithDurability ) // 2 - ���Ⱓ�� ���� �־�� �Ѵ�. - Ȥ�� ���� �������̰ų�.
						{
							if(CheckCondition(pclitemlist[pitempos].siUnique, pclchar, &returnval) == true ) // 3 - ���� ������ �����ؾ߸� �Ѵ�.
							{
								switch(abilityType) // ũ����Ż�� �ɷ� �ε����� ���� ���. - Ÿ�Կ� ���� �Լ��� �ٸ���. 
								{
									// ///////////////////////////////////////////////////
									//   oldTemReturnVal =  : �� ������ �߿��� ���� ū �ɷ� ��ġ �ϳ��� ����. =  �ɷ� ��ø : �Ұ�.
									//   temReturnVal +=     : �� ������ �� �ɷ� ��ġ�� ��� �����Ͼ� ���Ѵ�.	 =  �ɷ� ��ø : ����.						
									//////////// - ���� - ////////////////////////////////// - ��� ��ø ����.
						
									// ���� �ɷµ� ��� �� �� �־�� �Ѵ�.
									case CRYSTALABILITY_STATE_STR:
										temReturnVal += pclitemlist[pitempos].GetEquipStr(this, &siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_DEX:
										temReturnVal += pclitemlist[pitempos].GetEquipDex(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_MAG:
										temReturnVal += pclitemlist[pitempos].GetEquipMag(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_VIT:
										temReturnVal += pclitemlist[pitempos].GetEquipVit(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_LUK:
										temReturnVal += pclitemlist[pitempos].GetEquipLuk(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_HND:
										temReturnVal += pclitemlist[pitempos].GetEquipHnd(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_STATE_WIS:
										temReturnVal += pclitemlist[pitempos].GetEquipWis(this,&siAppendCrystalPoint); 
										break;

									// [����] �ƹ�Ÿ ����ü. �ɷ�ġ �߰�.
									case CRYSTALABILITY_AVATAR_STATE_STR:
										temReturnVal += pclitemlist[pitempos].GetEquipStr(this, &siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_DEX:
										temReturnVal += pclitemlist[pitempos].GetEquipDex(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_MAG:
										temReturnVal += pclitemlist[pitempos].GetEquipMag(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_VIT:
										temReturnVal += pclitemlist[pitempos].GetEquipVit(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_LUK:
										temReturnVal += pclitemlist[pitempos].GetEquipLuk(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_HND:
										temReturnVal += pclitemlist[pitempos].GetEquipHnd(this,&siAppendCrystalPoint);
										break;
									case CRYSTALABILITY_AVATAR_STATE_WIS:
										temReturnVal += pclitemlist[pitempos].GetEquipWis(this,&siAppendCrystalPoint); 
										break;									
									//////////// -ȿ��  - //////////////////////////////////////////////////////
									case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE:		// ���� ����� - ��ø
										temReturnVal += pclitemlist[pitempos].GetPhysicalAC(this ,&siAppendCrystalPoint);
										break;

									////////////- �Ӽ� - ///////////////////////////////////////////////////////	
									default :
										break;
								}							
							}
						}
					}
				}
				break;
			default :
				break;
		}
		
		//// �ƹ�Ÿ ������ �̶��.
		//if(pclitemlist[pitempos].GetAavatarType(this) > 0)
		//{
		//	temReturnVal += oldTemReturnVal;
		//	oldTemReturnVal = 0;

		//	*ReturnValPer += oldReturnValPer;
		//	oldReturnValPer = 0;				
		//}
		//else 
		//{
		//	//�ƹ�Ÿ �������� �ƴ϶��.
		//	if(oldTemReturnVal > temReturnVal)
		//	{
		//		temReturnVal = oldTemReturnVal;
		//		oldTemReturnVal = 0;
		//	}

		//	if(oldReturnValPer > *ReturnValPer)
		//	{
		//		*ReturnValPer = oldReturnValPer;
		//		oldReturnValPer = 0;
		//	}
		//}

		


		if(oldTemReturnVal > temReturnVal)
		{
			temReturnVal = oldTemReturnVal;
			oldTemReturnVal = 0;
		}

		if(oldReturnValPer > siCantAppendCrystalPoion)
		{
			siCantAppendCrystalPoion = oldReturnValPer;
			oldReturnValPer = 0;
		}
		
		*ReturnValPer += siAppendCrystalPoint;		
		siAppendCrystalPoint = 0;

	}

	// ������Ű�� �ʱ����� �ʱ�ȭ
	oldTemReturnVal = 0;
	oldReturnValPer = 0;

	siAppendCrystalPoint = 0;

	// [����] ���ο� ������ �ý���
	bool bCanUseWithDurability = true;
	if( pclClient->IsCountrySwitch( Switch_NewDurability) )
	{
		SI16 siDurability = pclitemlist[activeweapon].GetDurability();
		if( siDurability <= 0 )
			bCanUseWithDurability = false;
	}

	//  - activeweapon�� ��¿�� ����. - ���⼭ ���� �˻�.
	if(       IsExpiredDate(&pclitemlist[activeweapon]) == true  &&						  // ���Ⱓ�� �����־�� �Ѵ�. - by LEEKH 2007.04.12
		bCanUseWithDurability															// [����] ���ο� ������ �ý���
		&&CheckCondition(pclitemlist[activeweapon].siUnique, pclchar, &returnval) == true //�������� ����������̶�� [2007.08.07 �ռ���]
		&&(pclitemlist[activeweapon].siUnique > 0))									  // activeweapon�� ���� �ϰ� �־�� �Ѵ�. 								  
	{
		switch(abilityType) // ũ����Ż�� �ɷ� �ε����� ���� ���. - Ÿ�Կ� ���� �Լ��� �ٸ���. 
		{
			// ///////////////////////////////////////////////////
			//   oldTemReturnVal =  : �� ������ �߿��� ���� ū �ɷ� ��ġ �ϳ��� ����. =  �ɷ� ��ø : �Ұ�.
			//   temReturnVal +=     : �� ������ �� �ɷ� ��ġ�� ��� �����Ͼ� ���Ѵ�.	 =  �ɷ� ��ø : ����.						
			//////////// - ���� - ////////////////////////////////// - ��� ��ø ����.
			case CRYSTALABILITY_STATE_STR:
				 temReturnVal += pclitemlist[activeweapon].GetEquipStr(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_DEX:
				 temReturnVal +=pclitemlist[activeweapon].GetEquipDex(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_MAG:
				 temReturnVal +=pclitemlist[activeweapon].GetEquipMag(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_VIT:
				 temReturnVal += pclitemlist[activeweapon].GetEquipVit(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_LUK:
				 temReturnVal += pclitemlist[activeweapon].GetEquipLuk(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_HND:
				 temReturnVal += pclitemlist[activeweapon].GetEquipHnd(this,&oldReturnValPer); 
				break;
			case CRYSTALABILITY_STATE_WIS:
				 temReturnVal += pclitemlist[activeweapon].GetEquipWis(this,&oldReturnValPer); 
				break;
			//////////////////////////////////////////////////////////////////////////
			// [����] �ƹ�Ÿ ����ü. �ɷ�ġ �߰�.
			case CRYSTALABILITY_AVATAR_STATE_STR:
				temReturnVal += pclitemlist[activeweapon].GetEquipStr(this, &siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_DEX:
				temReturnVal += pclitemlist[activeweapon].GetEquipDex(this,&siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_MAG:
				temReturnVal += pclitemlist[activeweapon].GetEquipMag(this,&siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_VIT:
				temReturnVal += pclitemlist[activeweapon].GetEquipVit(this,&siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_LUK:
				temReturnVal += pclitemlist[activeweapon].GetEquipLuk(this,&siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_HND:
				temReturnVal += pclitemlist[activeweapon].GetEquipHnd(this,&siAppendCrystalPoint);
				break;
			case CRYSTALABILITY_AVATAR_STATE_WIS:
				temReturnVal += pclitemlist[activeweapon].GetEquipWis(this,&siAppendCrystalPoint); 
				break;
			//////////////////////////////////////////////////////////////////////////
			
			//////////// -ȿ��  - //////////////////////////////////
			case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK:			// ���� �ּ� ���ݷ�.
				oldTemReturnVal = pclitemlist[activeweapon].GetMinDamage(this , &oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK:		// ���� �ִ� ���ݷ�.
				oldTemReturnVal =  pclitemlist[activeweapon].GetMaxDamage(this, &oldReturnValPer);
				break;										
			//case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK:				 // ���� ���ݷ�
			//	oldTemReturnVal = pclitemlist[activeweapon].GetAddMagicalDamage(this, &oldReturnValPer);
			//	break;
			case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK:			 // ���� �ּ� ���ݷ�
				oldTemReturnVal =  pclitemlist[activeweapon].GetAddMagicalMinDamage(this, &oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK:			 // ���� �ִ� ���ݷ�
				oldTemReturnVal =  pclitemlist[activeweapon].GetAddMagicalMaxDamage(this, &oldReturnValPer);
				break;

			case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE:			// ���� ���߷�
				oldTemReturnVal =  pclitemlist[activeweapon].GetPhysicalHitRate(this, &oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE:				// ���� ���߷�
				oldTemReturnVal = pclitemlist[activeweapon].GetMagicalHitRate(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE:			// ���� ȸ����
				oldTemReturnVal =  pclitemlist[activeweapon].GetPhysicalDodgeRate(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE:			// ���� ȸ����
				oldTemReturnVal = pclitemlist[activeweapon].GetMagicalDodgeRate(this,&oldReturnValPer);
				break;										
			case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE:		// ���� ����� - ��ø
				temReturnVal += pclitemlist[activeweapon].GetPhysicalAC(this ,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE:		// ���� �����
				oldTemReturnVal = pclitemlist[activeweapon].GetMagicalAC(this ,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_HITPOINT:						// ü�·�
				oldTemReturnVal =  pclitemlist[activeweapon].GetCrystalHitpoint(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_MANAPOINT:					// ������
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalManapoint(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_EFFECT_WEIGHT:						// ���Է�
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalWeigt(this,&oldReturnValPer);
				break;
		///////////////////- �Ӽ� - //////////////////////////////////////////////////////////////	
			case CRYSTALABILITY_ATTRIBUTE_FIREATTACK:				// �� �Ӽ� ���ݷ�
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalFireAttack(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_WATERATTACK:				// �� �Ӽ� ���ݷ�
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalWaterAttack(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_WINDATTACK:				// �ٶ� �Ӽ� ���ݷ�
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalWindAttack(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK:				// �� �Ӽ� ���ݷ�
				oldTemReturnVal = pclitemlist[activeweapon].GetCrystalEarthAttack(this,&oldReturnValPer);
				break;

			case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE:				 // �� �Ӽ� ����
				oldTemReturnVal =  pclitemlist[activeweapon].GetCrystalFireDeffence(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE:			 // �� �Ӽ� ����
				oldTemReturnVal =  pclitemlist[activeweapon].GetCrystalWaterDeffence(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE:				// �ٶ� �Ӽ� ����
				oldTemReturnVal =  pclitemlist[activeweapon].GetCrystalWindDeffence(this,&oldReturnValPer);
				break;
			case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE:			// �� �Ӽ� ����
				oldTemReturnVal =  pclitemlist[activeweapon].GetCrystalEarthDeffence(this,&oldReturnValPer);
				break;
		///////////////////- Ư�� �ɷ� - //////////////////////////////////////////////////////////////	
			case CRYSTALABILITY_SPECIAL_DEATHBLOW:					// �ʻ�. - ũ��Ƽ�� �� ���.
				oldTemReturnVal =  pclitemlist[activeweapon].GetCriticalHitRate(this,&oldReturnValPer);
				break;
			default :
				break;
		}				

	}


	//// �ƹ�Ÿ ������ �̶��.
	//if(pclitemlist[activeweapon].GetAavatarType(this) > 0)
	//{
	//	temReturnVal += oldTemReturnVal;
	//	oldTemReturnVal = 0;

	//	*ReturnValPer += oldReturnValPer;
	//	oldReturnValPer = 0;				
	//}
	//else 
	//{
	//	if(oldTemReturnVal > temReturnVal)
	//	{
	//		temReturnVal = oldTemReturnVal;
	//		oldTemReturnVal = 0;
	//	}

	//	if(oldReturnValPer > *ReturnValPer)
	//	{
	//		*ReturnValPer = oldReturnValPer;
	//		oldReturnValPer = 0;
	//	}
	//}


	if(oldTemReturnVal > temReturnVal)
	{
		temReturnVal = oldTemReturnVal;
		oldTemReturnVal = 0;
	}

	if(oldReturnValPer > siCantAppendCrystalPoion)
	{
		siCantAppendCrystalPoion = oldReturnValPer;
		oldReturnValPer = 0;
	}

	*ReturnValPer += siAppendCrystalPoint;		
	*ReturnValPer += siCantAppendCrystalPoion;	

	siAppendCrystalPoint = 0;

	return temReturnVal;

}


// ����� ������ ���Ҹ� ���Ѵ�. 
SI32 cltItemManagerCommon::GetDamageReduceRate(cltItem* pclitemlist)
{
	SI32 i;
	SI32 item = 0;
	// ��ȯ�� ���� ������ ���� ����� �߰� 
	SI32 siTotalRate = 0;

	for(i = 0;i < 6;i++)
	{
		if(i == 0)
		{
			item = PERSONITEM_HELMET;
		}
		else if(i == 1)
		{
			item = PERSONITEM_HAT;
		}
		else if(i == 2)
		{
			item = PERSONITEM_ARMOUR;
		}
		else if(i == 3)
		{
			item = PERSONITEM_DRESS;
		}
		else if(i == 4)
		{
			item = PERSONITEM_BELT;
		}
		else
		{
			item = PERSONITEM_SHOES;
		}

		cltItem* pclitem = (cltItem*)&pclitemlist[item];

		// �� �������� �����Ѵ�. 
		if(pclitem->siUnique == 0)	continue;
		
		SI64 atb = GetItemAtb(pclitem->siUnique);
		if((atb & ITEMATB_ARMOUR) == 0)	return siTotalRate;
		
		if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE)
		{
			siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara1;
		}
		if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE)
		{
			siTotalRate += pclitem->clItemCommon.clOptionInfo.uiPara2;
		}
	}
	
	return siTotalRate;
}

// �Ź��� �̵��ӵ��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetMoveSpeed(cltItem* pclitemlist)
{
	SI32 movespeed = pclitemlist[PERSONITEM_SHOES].GetMoveSpeed(this);
	return movespeed;
}
// �Ź��� �̵��ӵ��� ���Ѵ�. 
SI32 cltItemManagerCommon::GetMoveSpeed(cltItem* pclitemlist, cltCharCommon* pclchar)
{	
	SI32 returnval = 0;
	SI32 movespeed = pclitemlist[PERSONITEM_SHOES].GetMoveSpeed(this);

	if (CheckCondition(pclitemlist[PERSONITEM_SHOES].siUnique, pclchar, &returnval) == false)
	{
		movespeed = 0;
		return movespeed;
	}
	else
	{
		return movespeed;
	}
	
}

// ������ �̹��� ������ ���´�.
bool cltItemManagerCommon::GetItemGImageFileIndexAndFont( SI32 ItemUnique, SI32 *pGlobalImageIndex, SI32 *pGlobalImageFont )
{
	if ( ItemUnique < 1 || pGlobalImageIndex == NULL || pGlobalImageFont == NULL )
	{
		return false;
	}

	SI32 Data[]=
	{
			GIMG_ITEMIMG01, 200,
			GIMG_ITEMIMG02, 191,
			GIMG_ITEMIMG03, 210,
			GIMG_ITEMIMG04, 210,
			GIMG_ITEMIMG05, 200,
			GIMG_ITEMIMG06, 200,
			GIMG_ITEMIMG07, 200,
			GIMG_ITEMIMG08, 200,
			-1
	};

	//SI32 Data[]=
	//{
	//	GIMG_ITEMIMG01, 40,
	//		GIMG_ITEMIMG02, 40,
	//		GIMG_ITEMIMG03, 40,
	//		GIMG_ITEMIMG04, 40,
	//		GIMG_ITEMIMG05, 40,
	//		GIMG_ITEMIMG06, 40,
	//		GIMG_ITEMIMG07, 40,
	//		GIMG_ITEMIMG08, 40,
	//		GIMG_ITEMIMG09, 40,
	//		GIMG_ITEMIMG10, 31,
	//		GIMG_ITEMIMG11, 40,
	//		GIMG_ITEMIMG12, 40,
	//		GIMG_ITEMIMG13, 40,
	//		GIMG_ITEMIMG14, 40,
	//		GIMG_ITEMIMG15, 40,
	//		GIMG_ITEMIMG16, 40,
	//		GIMG_ITEMIMG17, 40,
	//		GIMG_ITEMIMG18, 40,
	//		GIMG_ITEMIMG19, 40,
	//		GIMG_ITEMIMG20, 40,
	//		-1
	//};


	cltItemInfo* pcliteminfo = FindItemInfo( ItemUnique );

	if ( pcliteminfo == NULL )
	{
		return false;
	}

	SI16 Counter = 0;
	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageIndexFont = 0;
	SI32 AccumulationImageCounter = 0;

	bool loop = true;
	while( loop )
	{
		if ( Data[ Counter * 2 ] != -1 )
		{
			if ( AccumulationImageCounter + Data[ Counter * 2 + 1 ] - 1 >=  pcliteminfo->siImageIndex )
			{
				GlobalImageIndex = Data[ Counter * 2 ];
				GlobalImageIndexFont = pcliteminfo->siImageIndex - AccumulationImageCounter;
				
				*pGlobalImageIndex = GlobalImageIndex;
				*pGlobalImageFont = GlobalImageIndexFont;

				return true;
			}
			else
			{
				AccumulationImageCounter += Data[ Counter * 2 + 1 ];
				++Counter;
			}
		}
		else
		{
			break;
		}
	}

	return false;
}

#define SETITEM_ARRAY1_NUM		8
SI32 SetItemArray1[ SETITEM_ARRAY1_NUM ] = 
{
	PERSONITEM_HELMET,
	PERSONITEM_ARMOUR,
	PERSONITEM_NECK,
	PERSONITEM_BELT,
	PERSONITEM_SHOES,
	PERSONITEM_MANTLE,
	PERSONITEM_RING1,
	PERSONITEM_RING2
};

SI32 cltItemManagerCommon::GetCompletedSetItemIndex( cltItem* pclItemList )
{
	if ( pclItemList == NULL )
	{
		return 0;
	}

	if ( pclItemList[ SetItemArray1[ 0 ] ].siUnique > 0 &&
		pclItemList[ SetItemArray1[ 1 ] ].siUnique > 0 &&
		pclItemList[ SetItemArray1[ 2 ] ].siUnique > 0 &&
		pclItemList[ SetItemArray1[ 3 ] ].siUnique > 0 &&
		pclItemList[ SetItemArray1[ 4 ] ].siUnique > 0 &&
		pclItemList[ SetItemArray1[ 5 ] ].siUnique > 0 &&
		( pclItemList[ SetItemArray1[ 6 ] ].siUnique > 0 || pclItemList[ SetItemArray1[ 7 ] ].siUnique > 0 )
		)
	{
		SI32 Ref = 0;
		bool NotEnoughCondition = false;

		// SetItemArray1 Check
		for ( SI16 i = 0; i < SETITEM_ARRAY1_NUM - 2; ++i )
		{
			if ( pclItemList[ SetItemArray1[ i ] ].siUnique > 0 )
			{
				Ref = FindItemRefFromUnique( pclItemList[ SetItemArray1[ i ] ].siUnique );
				if ( Ref > 0 )
				{
					if ( pclItemInfo[ Ref ]->siSetItemIndex != 1 )
					{
						NotEnoughCondition = true;
					}
				}
				else
				{
					NotEnoughCondition = true;
				}
			}
			else
			{
				NotEnoughCondition = true;
			}
		}

		if ( ! NotEnoughCondition )
		{
			Ref = FindItemRefFromUnique( pclItemList[ SetItemArray1[ 6 ] ].siUnique );
			if ( Ref > 0 )
			{
				if ( pclItemInfo[ Ref ]->siSetItemIndex == 1 )
				{
					return 1;
				}
			}

			Ref = FindItemRefFromUnique( pclItemList[ SetItemArray1[ 7 ] ].siUnique );
			if ( Ref > 0 )
			{
				if ( pclItemInfo[ Ref ]->siSetItemIndex == 1 )
				{
					return 1;
				}
			}
		}
	}
	
	return 0;
}
bool cltItemManagerCommon::CheckCanPutonItem(SI32 unique )
{
	SI32 sitype = GetItemType( unique );

	switch(sitype)
	{
	case  ITEMTYPE_SWORD:
	case  ITEMTYPE_SPEAR:
	case  ITEMTYPE_STAFF:
	case  ITEMTYPE_AXE:
	case  ITEMTYPE_BOW:
	case  ITEMTYPE_GUN:
	case  ITEMTYPE_CANNON:
	case  ITEMTYPE_ARMOUR:
	case  ITEMTYPE_BELT:
	case  ITEMTYPE_SHOES:
	case  ITEMTYPE_HELMET:
	//case  ITEMTYPE_DRESS:
	//case  ITEMTYPE_HAT:
	//case  ITEMTYPE_RING:
		return true;
	default:
		return false;
	}				
}

//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
bool cltItemManagerCommon::GetValentineEvent(SI32 siUnique)
{
	switch(siUnique)
	{
		case  ITEMUNIQUE(13006): //Vī��
		case  ITEMUNIQUE(13007): //Aī��.
		case  ITEMUNIQUE(13008): //L ī��.
		case  ITEMUNIQUE(13009): //E1ī��
		case  ITEMUNIQUE(13010): //N1ī��
		case  ITEMUNIQUE(13011): //Tī��
		case  ITEMUNIQUE(13012): //I ī��
		case  ITEMUNIQUE(13014): //E2ī�� 
		case  ITEMUNIQUE(13013): //N2ī��
			return true;
		default:
			return false;
	}				
}

//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
bool cltItemManagerCommon::GetWhiteEvent(SI32 siUnique)
{
	switch(siUnique)
	{
		case  ITEMUNIQUE(13016): //Wī��
		case  ITEMUNIQUE(13017): //Hī��.
		case  ITEMUNIQUE(13018): //I ī��.
		case  ITEMUNIQUE(13019): //Tī��
		case  ITEMUNIQUE(13020): //Eī��
			return true;
		default:
			return false;
	}				
}
bool cltItemManagerCommon::IsExpiredDate(cltItem* pclitem)
{
	SI32		useableDay	= 0;
	
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		cltServer*	pclserver = (cltServer*)pclClient;		
		if(pclserver == NULL)			return false;
		
		BOOL bRet = pclserver->GetItemUseAbleDay(pclitem, &useableDay);
		if(bRet == TRUE && useableDay >= 0)				return true;
		//if(bRet == TRUE && useableDay < 0)				return true;
	}
	else if (pclClient->GameMode == GAMEMODE_CLIENT)
	{
		cltClient*	pclclient = (cltClient*)pclClient;
		if(pclclient == NULL)			return false;

		BOOL bRet = pclclient->GetItemUseAbleDay(pclitem, &useableDay);
		if(bRet == TRUE && useableDay >= 0)				return true;
		//if(bRet == TRUE && useableDay < 0)				return true;
	}

	return false;
}

//bool cltItemManagerCommon::UsedSlotItem(SI32 siUnique)
//{
//	if( siUnique == 0 )
//		return 0;
//
//	bool bResult = false;
//
//	SI32 itemtype	 = GetItemType(siUnique);
//
//	switch(itemtype)
//	{
//		case ITEMTYPE_SWORD:				// ��
//		case ITEMTYPE_SPEAR:				// â
//		case ITEMTYPE_STAFF:				// ������
//		case ITEMTYPE_AXE:					// ����
//		case ITEMTYPE_BOW:					// Ȱ
//		case ITEMTYPE_GUN:					// ��
//		case ITEMTYPE_ARMOUR:				// ����
//		case ITEMTYPE_BELT:					// �㸮��
//		case ITEMTYPE_SHOES:				// �Ź�
//		case ITEMTYPE_HELMET:				// ����
//
//		// [����] �ƹ�Ÿ ����ü. �ƹ�Ÿ �������� ����ü ���� ���� �߰�.
//		case ITEMTYPE_NECK:					// �����
//		case ITEMTYPE_RING:					// ����
//		case ITEMTYPE_HAT:					// ����
//		case ITEMTYPE_DRESS:				// �Ǻ�
//		case ITEMTYPE_MANTLE:				// ����
//		//case ITEMTYPE_CANNON:				// ����
//			{
//				bResult = true; 
//			}
//			break;			
//	}
//
//	// ���ܷ� Ÿ���� �ƴѵ� ����ũ�� ����Ǵ� �������� �������� ���� ����.
//	if( false == bResult )
//	{
//		const SI32 UsedSlotItem[]    = { 1,  };
//			  SI32 UsedSlotItemCount = sizeof(UsedSlotItem) / sizeof(SI32);
//
//		for( SI32 Count = 0; Count < UsedSlotItemCount; ++Count )
//		{
//			if(UsedSlotItem[Count] == siUnique)
//			{
//				bResult = true;
//			}
//		}
//	}
//	
//	return bResult;
//}


//KHY - 20090526 - �ƹ�Ÿ ����ü.
bool cltItemManagerCommon::IsCrystalAbatarItem( SI32 siItemType )
{
	bool bResult = false;
	
	switch(siItemType)
	{
		case ITEMTYPE_AVATAR_MANTLE:	// �ƹ�Ÿ ����
		case ITEMTYPE_AVATAR_DRESS:		// �ƹ�Ÿ �Ǻ�
		case ITEMTYPE_AVATAR_HAT:		// �ƹ�Ÿ ����
		case ITEMTYPE_AVATAR_NECK:		// �ƹ�Ÿ �����
		case ITEMTYPE_AVATAR_RING:		// �ƹ�Ÿ ����
			{
				bResult = true;
			}
			break;
		default:
				bResult = false;
			break;
	}
	
	return bResult;
}

bool cltItemManagerCommon::IsAbatarCrystalItem( UI08 uiCrystalAbility )
{
	bool bResult = false;
	
	switch(uiCrystalAbility)
	{
		case CRYSTALABILITY_AVATAR_STATE_STR:
		case CRYSTALABILITY_AVATAR_STATE_DEX:
		case CRYSTALABILITY_AVATAR_STATE_MAG:	
		case CRYSTALABILITY_AVATAR_STATE_VIT:
		case CRYSTALABILITY_AVATAR_STATE_LUK:
		case CRYSTALABILITY_AVATAR_STATE_HND:
		case CRYSTALABILITY_AVATAR_STATE_WIS:	
		case CRYSTALABILITY_AVATAR_ALLMAKESKILL:
		case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:
		case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:	
			{
				bResult = true;
			}
			break;
		default:
				bResult = false;
			break;
	}
	
	return bResult;
}

//KHY - 20090526 - �ƹ�Ÿ ����ü.
SI32 cltItemManagerCommon::GetMaxAbatarCrystalAbilityNum(SI32 siItemType , UI08 uiCrystalAbility)
{
	SI32 maxAvatarCrystalAbility = 0;
	// �ƹ�Ÿ ����ü  - ���� ���ǵ�.
	switch(siItemType) // ����ü�� ������ �����ۿ� ����.
	{
		case ITEMTYPE_AVATAR_DRESS:
		case ITEMTYPE_AVATAR_HAT:
			{
				// ��ų�� ���� �ִ� ���� Ʋ����.
				switch(uiCrystalAbility)
				{
					case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:
					case CRYSTALABILITY_AVATAR_ALLMAKESKILL:
						maxAvatarCrystalAbility= 5;
						break;
					case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:
						maxAvatarCrystalAbility= 0;
						break;
					default: // ���� �������ͽ� ����ü - ���� �ٸ� ��ų ����ü�� ����� �߰��� �ٲپ���� �Ѵ�.
						maxAvatarCrystalAbility= 10;
						break;									
				}
			}
			break;
		case ITEMTYPE_AVATAR_MANTLE:
		case ITEMTYPE_AVATAR_RING:
			{
				// ��ų�� ���� �ִ� ���� Ʋ����.
				switch(uiCrystalAbility)
				{
					case CRYSTALABILITY_AVATAR_STATE_STR:
					case CRYSTALABILITY_AVATAR_STATE_DEX:
					case CRYSTALABILITY_AVATAR_STATE_MAG:
					case CRYSTALABILITY_AVATAR_STATE_VIT:
					case CRYSTALABILITY_AVATAR_STATE_LUK:
					case CRYSTALABILITY_AVATAR_STATE_HND:
					case CRYSTALABILITY_AVATAR_STATE_WIS:
						maxAvatarCrystalAbility= 10;
						break;									

					default:
						maxAvatarCrystalAbility= 0;
						break;									
				}
			}
			break;
		case ITEMTYPE_AVATAR_NECK:
			{
				// ��ų�� ���� �ִ� ���� Ʋ����.
				switch(uiCrystalAbility)
				{
					case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:
					case CRYSTALABILITY_AVATAR_ALLMAKESKILL:
					case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:
						maxAvatarCrystalAbility= 3;
						break;
					default: 
						maxAvatarCrystalAbility= 0;
						break;									
				}
			}
			break;
	}

	return maxAvatarCrystalAbility;
}


SI32 cltItemManagerCommon::UsedSlotItem(SI32 siUnique)
{
	if( siUnique == 0 )	return SLOTITEMTYPE_NONE;

	SI32 bResult = SLOTITEMTYPE_NONE;

	// [����] �޸� ��� ���������� Ȯ�� 
	if( NULL == pclClient)
	{
		return SLOTITEMTYPE_NONE;
	}

	CDormancySystem *pclDormancySystem = pclClient->pclDormancySystem;
	if( NULL != pclDormancySystem)
	{
		CDormancyEquipItemRewardClient *pclDormancyClient = (CDormancyEquipItemRewardClient *)pclDormancySystem->GetDormancyEquipItemReward();
		if( NULL != pclDormancyClient)
		{
			if( TRUE == pclDormancyClient->IsDormancyEquipItem(siUnique))
			{
				return SLOTITEMTYPE_DORMANCY;
			}
		}
	}

	SI32 itemtype	 = GetItemType(siUnique);

	switch(itemtype)
	{
	case ITEMTYPE_SWORD:				// ��
	case ITEMTYPE_SPEAR:				// â
	case ITEMTYPE_STAFF:				// ������
	case ITEMTYPE_AXE:					// ����
	case ITEMTYPE_BOW:					// Ȱ
	case ITEMTYPE_GUN:					// ��
	case ITEMTYPE_ARMOUR:				// ����
	case ITEMTYPE_BELT:					// �㸮��
	case ITEMTYPE_SHOES:				// �Ź�
	case ITEMTYPE_HELMET:				// ����
		{
			bResult = SLOTITEMTYPE_WEAPON;
		}
		break;

	//case ITEMTYPE_NECK:				// �����
	//case ITEMTYPE_RING:				// ����
	//case ITEMTYPE_HAT:				// ����
	//case ITEMTYPE_DRESS:				// �Ǻ�
	//case ITEMTYPE_MANTLE:				// ����
	//case ITEMTYPE_CANNON:				// ����

	case ITEMTYPE_AVATAR_MANTLE:	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_DRESS:		// �ƹ�Ÿ �Ǻ�
	case ITEMTYPE_AVATAR_HAT:		// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_NECK:		// �ƹ�Ÿ �����
	case ITEMTYPE_AVATAR_RING:		// �ƹ�Ÿ ����
		{
			bResult = SLOTITEMTYPE_AVATAR;
		}
		break;			
	}

	// ���ܷ� Ÿ���� �ƴѵ� ����ũ�� ����Ǵ� �������� �������� ���� ����.
	if( SLOTITEMTYPE_NONE == bResult )
	{
		const SI32 UsedSlotItem[]    = { 1,  };
		SI32 UsedSlotItemCount = sizeof(UsedSlotItem) / sizeof(SI32);

		for( SI32 Count = 0; Count < UsedSlotItemCount; ++Count )
		{
			if(UsedSlotItem[Count] == siUnique)
			{
				bResult = SLOTITEMTYPE_WEAPON;
			}
		}
	}

	return bResult;
}

// [�߰� : Ȳ���� 2008. 2. 29 => ����ü ������ ������ ����Ÿ �ΰ�?.]
BOOL cltItemManagerCommon::CanCrystalMixtureData( cltItem* _EquipItem, cltItem* _CrystalItem, SI16 _EquipItemPos)
{
	// �⺻ �˻�.
	// ---------------------------------------------------------------------------------
	if( 0 >= _EquipItem->siUnique )
	{
		return NO_ITEM_UNIQUE;
	}
	
	// ������ �ִ� ������������ �˻��Ѵ�.
	if( SLOTITEMTYPE_NONE == UsedSlotItem( _EquipItem->siUnique ) )
	{
		return NO_SLOT_ITEM;
	}

	// �����ۿ� ������ ������ ������ �ִ��� �˻�.
	//KHY - 0805 - ��Ʈ�彺 ����.
	//if( false == _EquipItem->EmptyCrystalSlot() )
	//{
	//	return NO_USED_SLOT;
	//}

	// �����忡 ��ġ�� �������� ������ �� ����.
	if( _EquipItemPos < PERSONITEM_INV0 )
		return NO_SLOT_ITEM;


	bool EmptySlot = true;
	for( SI32 Count = 0; Count < MAX_CRYSTAL_NUM; ++Count )
	{
		if( 0 < _CrystalItem[Count].siUnique && 0 < _CrystalItem[Count].siItemNum )
		{
			EmptySlot = false;

			// �����Ϸ��� �������� ����ü�� �ƴϴ�.
			if( ITEMTYPE_CRYSTAL != _CrystalItem[Count].GetType( this ) )
			{
				return NO_CRYSTAL;
			}
			else
			{
				// ��� ����ü�� �����Ϸ��� ���Կ� �̹� ����ü�� �ִ�. 
				//KHY - 0805 - ��Ʈ�彺 ����.
				//if(0 < _EquipItem->cltItemCrytal[Count].GetCrystalType())
				//{
				//	return ALREADY_USE_SLOT;
				//}
			}
		}
	}

	if( true == EmptySlot )
	{
		return ALL_EMPTY_CRYSTAL;
	}
	//------------------------------------------------------------------------------------
	
	//KHY - 20090526 - �ƹ�Ÿ ����ü.

	// ����ü ���� �ƹ�Ÿ ����ü �� ���.
	for( SI32 CrystalCount1 = 0; CrystalCount1 < _EquipItem->siUseCrystalNum; ++CrystalCount1 )
	{		
		if( IsAbatarCrystalItem( _CrystalItem[CrystalCount1].GetCrystalAbility())) // �ɷ����� �����Ѵ�.
		{
			if( IsCrystalAbatarItem( _EquipItem->GetType( this )) == false) // �ƹ�Ÿ �������� �ƴ϶��.
				return NO_CRYSTAL; // �ϴ���  - �����Ϸ��� �����۰� ����ü�� ���� �ʴ�.

		}
	}
	
	// EquipItem ���� �ƹ�Ÿ �� ���. 
	if( IsCrystalAbatarItem( _EquipItem->GetType( this ))) // �ƹ�Ÿ Ÿ���� ������ �� ���.
	{
		for( SI32 EquipCount = 0; EquipCount < _EquipItem->siUseCrystalNum; ++EquipCount )
		{
			for( SI32 CrystalCount = 0; CrystalCount < _EquipItem->siUseCrystalNum; ++CrystalCount )
			{		
				if( 0 < _EquipItem->cltItemCrytal[ EquipCount ].GetCrystalType() &&
					0 < _CrystalItem[CrystalCount].siUnique )
				{
					if( _EquipItem->cltItemCrytal[ EquipCount ].GetCrystalAblilty() == _CrystalItem[CrystalCount].GetCrystalAbility()) 
					{
						if(EquipCount == CrystalCount)
							continue; // ��� �ƹ�Ÿ ����ü�� ������ �����ϴ�.
						else
							return SAME_CRYSTAL; // �ٸ� ��ġ�� ���� �ɷ��� �ִٸ� �Ұ��ϴ�.
					}
				}
			}
		}
		
		//�Ѳ����� �ߺ����յǴ� ���� �������ؼ�, �� �ƹ�Ÿ ����ü���� Ÿ���� ���� �˻��ؾ� �Ѵ�.
		for(SI16 aCrystalCount1 = 0; aCrystalCount1 < _EquipItem->siUseCrystalNum ; ++aCrystalCount1)
		{
			// �ش� �������� ������쿡��, 
			if(0 < _CrystalItem[aCrystalCount1].siUnique )
			{
				for(SI16 aCrystalCount2 = 0; aCrystalCount2 < _EquipItem->siUseCrystalNum ; ++aCrystalCount2)
				{
					// �ش� �������� �ְ�, ���� ������ �ƴϾ�� �Ѵ�. 
					if((0 < _CrystalItem[aCrystalCount2].siUnique) &&(aCrystalCount1 != aCrystalCount2))
					{
						if( _CrystalItem[aCrystalCount1].GetCrystalAbility() == _CrystalItem[aCrystalCount2].GetCrystalAbility()) 
							return SAME_CRYSTAL; // �����ɷ�ġ�� ����ü �ΰ��� ���ÿ� ���� �� ����.
					}
				}
			}
		}
		// ����ü�� ��� ������ ������ �ɷ��� ������ �ִ��� �˻�. - �̹� �˻��ߴ�.
		/*for( SI32 CrystalCount = 0; CrystalCount < _EquipItem->siUseCrystalNum; ++CrystalCount )
		{		
			if( 0 < _CrystalItem[CrystalCount].siUnique )
			{
				if(false == IsMixtureAbilityType(_EquipItem, _CrystalItem[CrystalCount].GetCrystalAbility()))
				{
					return LIMIT_CRYSTAL_ABILITY;
				}
			}
		}
		*/
	}
	// �ߺ��Ǵ� ����ü�� ������ �������� �ʰ�.
	/*for( SI32 EquipCount = 0; EquipCount < _EquipItem->siUseCrystalNum; ++EquipCount )
	{
		for( SI32 CrystalCount = 0; CrystalCount < _EquipItem->siUseCrystalNum; ++CrystalCount )
		{		
			if( 0 < _EquipItem->cltItemCrytal[ EquipCount ].GetCrystalType() &&
				0 < _CrystalItem[CrystalCount].siUnique )
			{
				if( _EquipItem->cltItemCrytal[ EquipCount ].GetCrystalAblilty() == _CrystalItem[CrystalCount].GetCrystalAbility()) 
				{
					// �Ʒ� �ɷ��� �ߺ��� �����ϴ�.
					switch(_CrystalItem[CrystalCount].GetCrystalAbility())
					{
						case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK:
						case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK:
						case CRYSTALABILITY_ATTRIBUTE_FIREATTACK:	
						case CRYSTALABILITY_ATTRIBUTE_WATERATTACK:
						case CRYSTALABILITY_ATTRIBUTE_WINDATTACK:	
						case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK:		
						case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK:	 
						case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK:	
						case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK:	
						case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK:	continue;
					}
					return SAME_CRYSTAL;
				}
			}
		}
	}
	*/

	// ����ü�� ��� ������ ������ �ɷ��� ������ �ִ��� �˻�.
	/*for( SI32 CrystalCount = 0; CrystalCount < _EquipItem->siUseCrystalNum; ++CrystalCount )
	{		
		if( 0 < _CrystalItem[CrystalCount].siUnique )
		{
			if(false == IsMixtureAbilityType(_EquipItem, _CrystalItem[CrystalCount].GetCrystalAbility()))
			{
				return LIMIT_CRYSTAL_ABILITY;
			}
		}
	}
	*/

	return POSSIBLE;
}

// [�߰� : Ȳ���� 2008. 2. 30 => ����ü ���Ű� ������ ����Ÿ �ΰ�?.]
BOOL cltItemManagerCommon::CanCrystalRemoveData( cltItem* _EquipItem, bool* _RemoveSlot, cltItem* _CrystalItem )
{
	if( 0 >= _EquipItem->siUnique )
	{
		return NO_ITEM_UNIQUE;
	}

	// ������ �ִ� ������������ �˻��Ѵ�.
	if( SLOTITEMTYPE_NONE == UsedSlotItem( _EquipItem->siUnique ) )
	{
		return NO_SLOT_ITEM;
	}

	//
	SI32 RemoveCrystalNum = 0;
	for( SI32 Count = 0; Count < _EquipItem->siUseCrystalNum; ++Count )
	{
		if(true == _RemoveSlot[Count])
			++RemoveCrystalNum;
	}
	if(0 == RemoveCrystalNum)
		return NO_CRYSTAL_SLOT;


	for( SI32 Count = 0; Count < _EquipItem->siUseCrystalNum; ++Count )
	{
		if( true == _RemoveSlot[ Count ] )
		{
			if( 0 >= _EquipItem->cltItemCrytal[ Count ].siCrystalType )
			{
				return NO_CRYSTAL_SLOT;	// ���Կ� ������ ����ü�� ����.
			}
		}
	}

	SI32 RemoveCrystalCount = 0;
	for( SI32 Count = 0; Count < _EquipItem->siUseCrystalNum; ++Count )
	{
		if( 0 < _CrystalItem[Count].siUnique && 0 < _CrystalItem[Count].siItemNum )
		{
			if(  _CrystalItem[Count].siUnique == ITEMUNIQUE(1803)) // ������ ����ü.
			{
				++RemoveCrystalCount;
			}	
			else if(  _CrystalItem[Count].siUnique == ITEMUNIQUE(1804)) // ������ ����ü.
			{
				if( true == _RemoveSlot[ Count ] )
				{
					if(_EquipItem->cltItemCrytal[Count].GetMaxDurability() <=1500)
						return NO_LOW_DURABILITY;
				}				
				++RemoveCrystalCount;			
			}
		}
	}

	if( 0 == RemoveCrystalCount )
	{
		return NO_REMOVE_CRYSTAL;
	}

	return POSSIBLE;
}

// [�߰� : Ȳ���� 2008. 2. 2 => ����ü�� ���� ������ ������ ����Ÿ �ΰ�?.]
BOOL cltItemManagerCommon::CanCrystalSlotCreateData( cltItem* _EquipItem, cltItem* _CrystalItem )
{
	if( 0 >= _EquipItem->siUnique || 0 >= _CrystalItem->siUnique )
	{
		return NO_ITEM_UNIQUE;
	}
	
	// ������ �ִ� ������������ �˻��Ѵ�.
	if( SLOTITEMTYPE_NONE == UsedSlotItem( _EquipItem->siUnique ) )
	{
		return NO_SLOT_ITEM;
	}

	// ��� ������ �������ִٸ�
	if( MAX_CRYSTAL_NUM <= _EquipItem->GetUseCrystalNum() )
	{
		return FULL_CRYSTAL_SLOT;
	}

	SI32 ref	= pclClient->pclItemManager->FindItemRefFromUnique( _CrystalItem->siUnique );

	SI32 siType = pclClient->pclItemManager->pclItemInfo[ ref ]->siType; 

	// ����ü�� �ƴϸ� ����.
	if( ITEMTYPE_CRYSTAL != siType )
	{
		return NO_CRYSTAL;
	}


	return POSSIBLE;
}


bool cltItemManagerCommon::IsMixtureAbilityType(cltItem* pclEquipItem, SI32 CristalItemAbilytype)
{
	enum{ ATTACK_EQUIP, DEFENCE_EQUIP, AVATAR_EQUIP};

	BOOL Crystal_TYPE = -1; 
	switch(CristalItemAbilytype)
	{
		// ��
		case CRYSTALABILITY_STATE_STR:
		case CRYSTALABILITY_STATE_DEX:			
		case CRYSTALABILITY_STATE_MAG:			
		case CRYSTALABILITY_STATE_VIT:			
		case CRYSTALABILITY_STATE_LUK:			
		case CRYSTALABILITY_STATE_HND:	
		case CRYSTALABILITY_STATE_WIS:
		case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE:
		case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE:
		case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE:
		case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE:	
		case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE:
		case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE:
		case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE:	
		case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE:
		case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE:	
		case CRYSTALABILITY_EFFECT_HITPOINT:
		case CRYSTALABILITY_EFFECT_MANAPOINT:
		case CRYSTALABILITY_EFFECT_WEIGHT:	
		case CRYSTALABILITY_SKILL_SUMMON:	
		case CRYSTALABILITY_SKILL_FARM:
		case CRYSTALABILITY_SKILL_MINE:
		case CRYSTALABILITY_SKILL_FISH:
		case CRYSTALABILITY_SKILL_MAKEFOOD:
		case CRYSTALABILITY_SKILL_CAPTURE:
		case CRYSTALABILITY_SKILL_HORSETRAINING:
		case CRYSTALABILITY_SKILL_MAKEIRON1:
		case CRYSTALABILITY_SKILL_MAKETOOL1:	
		case CRYSTALABILITY_SKILL_MAKEMED:
		case CRYSTALABILITY_SKILL_MAKESWORD1:
		case CRYSTALABILITY_SKILL_MAKESPEAR1:
		case CRYSTALABILITY_SKILL_MAKEAXE1:
		case CRYSTALABILITY_SKILL_MAKESTAFF1:	
		case CRYSTALABILITY_SKILL_MAKEBOW1:	
		case CRYSTALABILITY_SKILL_MAKEGUN1:	
		case CRYSTALABILITY_SKILL_MAKEARMOUR1:
		case CRYSTALABILITY_SKILL_MAKEHELMET1:
		case CRYSTALABILITY_SKILL_MAKESHOES1:	
		case CRYSTALABILITY_SKILL_MAKEBELT1:
		case CRYSTALABILITY_SKILL_ARTIFACT:			
		case CRYSTALABILITY_SKILL_USESWORD1:
		case CRYSTALABILITY_SKILL_USESPEAR1:	
		case CRYSTALABILITY_SKILL_USEAXE1:	
		case CRYSTALABILITY_SKILL_USESTAFF1:	
		case CRYSTALABILITY_SKILL_USEBOW1:	
		case CRYSTALABILITY_SKILL_USEGUN1:					Crystal_TYPE = DEFENCE_EQUIP; break;

			//����
		case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK:
		case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK:
		case CRYSTALABILITY_ATTRIBUTE_FIREATTACK:	
		case CRYSTALABILITY_ATTRIBUTE_WATERATTACK:
		case CRYSTALABILITY_ATTRIBUTE_WINDATTACK:	
		case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK:	
		case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK:	
		case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK:	
		case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK:	
		case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK:		Crystal_TYPE = ATTACK_EQUIP; break;

		// �ƹ�Ÿ
		case CRYSTALABILITY_AVATAR_STATE_STR:	
		case CRYSTALABILITY_AVATAR_STATE_DEX:	
		case CRYSTALABILITY_AVATAR_STATE_MAG:	
		case CRYSTALABILITY_AVATAR_STATE_VIT:	
		case CRYSTALABILITY_AVATAR_STATE_LUK:	
		case CRYSTALABILITY_AVATAR_STATE_HND:		
		case CRYSTALABILITY_AVATAR_STATE_WIS:	
		case CRYSTALABILITY_AVATAR_ALLMAKESKILL:	
		case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:	
		case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:		Crystal_TYPE = AVATAR_EQUIP; break;		
	}

	//BOOL Equip_TYPE = -1;
	BOOL Equip_TYPE = -1;
	SI32 eTYPE = pclEquipItem->GetType(pclClient->pclItemManager);

	switch(eTYPE)
	{
		case ITEMTYPE_AVATAR_MANTLE : 
		case ITEMTYPE_AVATAR_DRESS : 
		case ITEMTYPE_AVATAR_HAT : 
		case ITEMTYPE_AVATAR_NECK : 
		case ITEMTYPE_AVATAR_RING : 
			Equip_TYPE = AVATAR_EQUIP;
			break;
	}

	// ������ �����ۿ� ����ü�� �ɷ��� ����Ǹ�.
	if(Equip_TYPE == Crystal_TYPE)
		return true;
	// ���Ӽ��� ������ ����.
	else if(-1 == Crystal_TYPE)
		return true;
	else
		return false;
	
	// ATB�� �̿��ؼ� �� �� �ʿ䰡 ����.
	/*if( pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_WEAPON) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_BOW	  ) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_SWORD ) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_GUN	  ) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_SPEAR ) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_STAFF ) ||
		pclClient->pclItemManager->pclItemTypeInfo[pclEquipItem->GetType(pclClient->pclItemManager)]->IsAtb(ITEMATB_AXE	  )		)
	{
		Equip_TYPE = ATTACK_EQUIP;
	}
	else
	{
		Equip_TYPE = DEFENCE_EQUIP;
	}

	// ������ �����ۿ� ����ü�� �ɷ��� ����Ǹ�.
	if(Equip_TYPE == Crystal_TYPE)
		return true;

	// ���Ӽ��� ������ ����.
	else if(-1 == Crystal_TYPE)
		return true;

	else
		return false;
	*/

}
// [����] �����۸��� �� ���ϳ��Ӱ� �̹��� �ε����� ������ �ɴϴ�.
void cltItemManagerCommon::GetItemImageItemmallFileName( SI32 siFromDBImgIndex, TCHAR* FileName, SI32 siLen,  SI32* ImageIndex )
{
	SI32 siFileIndex	=	0				;
	*ImageIndex = siFromDBImgIndex % MAX_ITEM_ITEMMALLIMAGE_NUM	;// �̰� ����� �̹��� �ε���
	// ���� �ε��� �ѹ�.
	siFileIndex = siFromDBImgIndex / MAX_ITEM_ITEMMALLIMAGE_NUM ;
	StringCchPrintf( FileName, siLen , TEXT("NInterface/Image/ImageC_80x80_00_00%d.SPR"), siFileIndex );
	if ( 0 > siFileIndex )
	{
		*ImageIndex = 0	;
		StringCchPrintf( FileName, siLen , TEXT("NInterface/Image/ImageC_80x80_00_000.SPR"));

	}
}
// [����] �����۸��� �� ���ϳ��Ӱ� �̹��� �ε����� ������ �ɴϴ�.
void  cltItemManagerCommon::GetItemNameItemmallFileName( SI32 siFromDBImgIndex, TCHAR* FileName, SI32 siLen,  SI32* ImageIndex )
{
	SI32 siFileIndex	=	0				;
	*ImageIndex = siFromDBImgIndex % MAX_ITEM_ITEMMALLIMAGE_NUM	;// �̰� ����� �̹��� �ε���
	// ���� �ε��� �ѹ�.
	siFileIndex = siFromDBImgIndex / MAX_ITEM_ITEMMALLIMAGE_NUM ;
	StringCchPrintf( FileName, siLen , TEXT("NInterface/Image/Image_90x20_00_00%d.SPR"), siFileIndex );
	if ( 0 > siFileIndex )
	{
		*ImageIndex = 0	;
		StringCchPrintf( FileName, siLen , TEXT("NInterface/Image/Image_90x20_00_000.SPR"));

	}
}

bool cltItemManagerCommon::CanRepairItem( cltItem* pclitem )
{
	if( pclitem == NULL )						return false;

	//-------------------------------------------------------------------------------------------------------
	// ������ Ÿ�Կ� ���� ����
	//-------------------------------------------------------------------------------------------------------
	switch ( pclitem->GetType(this) )
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_NECK:
	case ITEMTYPE_AVATAR_MANTLE:
	case ITEMTYPE_AVATAR_DRESS:
	case ITEMTYPE_AVATAR_HAT:		
	case ITEMTYPE_AVATAR_NECK:	
	case ITEMTYPE_AVATAR_RING:
	case ITEMTYPE_MANTLE:
		{
			// ���� �ִ� Ÿ���� ���� �����ϴ�
		}
		break;
	default:
		{	// �׿� Ÿ���� ���� �Ұ���
			return false;
		}
	}
	//-------------------------------------------------------------------------------------------------------


	SI32 siMaxDurability		= (SI32)pclClient->GetGlobalValue( TEXT("GV_MaxDurability") );
	SI32 siForeverDurability	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	//-------------------------------------------------------------------------------------------------------
	// �������� ������ �� ���� ������
	//-------------------------------------------------------------------------------------------------------
	SI32 dur	= pclitem->GetDurability();
	SI32 maxdur = pclitem->GetMaxDurability();

	if( dur    == siForeverDurability )			return false;
	if( dur    == siForeverDurability2 )		return false;
	if( maxdur == siForeverDurability )			return false;
	if( maxdur == siForeverDurability2 )		return false;

	if( dur == maxdur )							return false;
	//-------------------------------------------------------------------------------------------------------

	return true;
}

bool cltItemManagerCommon::IsRepairStone( cltItem* pclitem )
{
	if( pclitem == NULL )									return false;

	//-------------------------------------------------------------------------------------------------------
	// �������̴�.
	if( pclitem->siUnique == ITEMUNIQUE(8123) )				return true;
	//-------------------------------------------------------------------------------------------------------

	return false;
}

bool cltItemManagerCommon::IsRepairStone( SI32 siItemUnique )
{
	if ( ITEMUNIQUE(8123) == siItemUnique )
	{
		return true;
	}

	return false;
}



bool cltItemManagerCommon::IsRepairExtraMaterial( cltItem* pclitem )
{
	if( pclitem == NULL )									return false;

	//-------------------------------------------------------------------------------------------------------
	if( pclitem->siUnique == ITEMUNIQUE(5370) )				return true;
	//-------------------------------------------------------------------------------------------------------

	return false;
}

SI16 cltItemManagerCommon::NeedRepairStoneNum( cltItem* pclitem )
{
	if( pclitem == NULL )									return 0;
	SI32 ref = FindItemRefFromUnique( pclitem->siUnique );
	if( ref <= 0 )											return 0;

	SI16 siNeedNum = max( 1, pclItemInfo[ref]->clSkillInfo.siSkillLevel / 5 );

	return siNeedNum;
}

SI16 cltItemManagerCommon::NeedBlessingStoneNum( cltItem* pclitem, SI32 BlessingStoneUnique )
{
	if( pclitem == NULL )									return 0;
	SI32 ref = FindItemRefFromUnique( pclitem->siUnique );
	if( ref <= 0 )											return 0;

	SI16 siNeedNum = 0;

	switch( BlessingStoneUnique )
	{
	case ITEMUNIQUE(5370):
		{
			REAL32 fConstantA = 2.0;
			if(		 pclitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 )	{		fConstantA = 5.0f;		}
			else if( pclitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )	{		fConstantA = 4.0f;		}
			else if( pclitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )	{		fConstantA = 2.5f;		}

			SI16 siNeedNum = max( 1, fConstantA * (pclItemInfo[ref]->clSkillInfo.siSkillLevel / 10.0f) );

			return siNeedNum;
		}
		break;
	}

	return siNeedNum;
}

GMONEY cltItemManagerCommon::RepairPrice( cltItem* pclitem )
{
	GMONEY moneyRet = 0;

	if( pclitem == NULL )										return moneyRet;
	SI32 ref = FindItemRefFromUnique( pclitem->siUnique );
	if( ref <= 0 )												return moneyRet;

	if( CanRepairItem( pclitem) == false )						return moneyRet;

	SI32 maxdur = pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
	SI32 dur = pclitem->clItemCommon.clCommonInfo.uiDurability;

	moneyRet = pclItemInfo[ref]->clSkillInfo.siSkillLevel * (maxdur - dur) * (clItemStatistic.siNPCPriceRate / 20);

	return moneyRet;
}

bool cltItemManagerCommon::CanMaxRepairItem( cltItem* pclitem )
{
	if( pclitem == NULL )																	return false;

	//-------------------------------------------------------------------------------------------------------
	// ������ Ÿ�Կ� ���� ����
	//-------------------------------------------------------------------------------------------------------
	switch ( pclitem->GetType(this) )
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_NECK:
	case ITEMTYPE_AVATAR_MANTLE:
	case ITEMTYPE_AVATAR_DRESS:
	case ITEMTYPE_AVATAR_HAT:		
	case ITEMTYPE_AVATAR_NECK:	
	case ITEMTYPE_AVATAR_RING:
	case ITEMTYPE_MANTLE:
		{
			// ���� �ִ� Ÿ���� ���� �����ϴ�
		}
		break;
	default:
		{	// �׿� Ÿ���� ���� �Ұ���
			return false;
		}
	}
	//-------------------------------------------------------------------------------------------------------


	UI32 uiMaxDurability		= (UI32)pclClient->GetGlobalValue( TEXT("GV_MaxDurability") );
	UI32 uiForeverDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	UI32 uiForeverDurability2	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	//-------------------------------------------------------------------------------------------------------
	// �ִ� �������� ������ �� ���� ������
	//-------------------------------------------------------------------------------------------------------
	if( pclitem->clItemCommon.clCommonInfo.uiDurability    == uiForeverDurability )			return false;
	if( pclitem->clItemCommon.clCommonInfo.uiDurability    == uiForeverDurability2 )		return false;
	if( pclitem->clItemCommon.clCommonInfo.uiMaxDurability == uiForeverDurability )			return false;
	if( pclitem->clItemCommon.clCommonInfo.uiMaxDurability == uiForeverDurability2 )		return false;
	if( pclitem->clItemCommon.clCommonInfo.uiMaxDurability == uiMaxDurability)				return false;

	return true;
}

bool cltItemManagerCommon::IsMaxRepairStone( cltItem* pclitem )
{
	if( pclitem == NULL )									return false;

	//-------------------------------------------------------------------------------------------------------
	if( pclitem->siUnique == ITEMUNIQUE(5418) )				return true;
	//-------------------------------------------------------------------------------------------------------

	return false;

}

bool cltItemManagerCommon::IsMaxRepairStone( SI32 siItemUnique )
{
	if ( ITEMUNIQUE(5418) == siItemUnique )
	{
		return true;
	}

	return false;
}