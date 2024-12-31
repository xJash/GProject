//---------------------------------
// 2003/12/2 ���°�
//---------------------------------

#include "cltItem.h"
#include "../../char/CharCommon/Char-Common.h"
#include "../../char/KindInfo/kindinfo.h"
#include "../../../common/PrivateTradeOrderMgr/PrivateTradeOrderBaseInfo.h"


//---------------------------------------
// ĳ������ ������ ���� ����. 
//---------------------------------------
void cltPItemInfo::Set(cltPItemInfo* pclitemmanager)
{
	memcpy(this, pclitemmanager, sizeof(cltPItemInfo));	
}

// ��ü�� ���Ը� ���´�. 
SI32 cltPItemInfo::GetTotalWeight(cltItemManagerCommon* pclItemManager)
{
	SI32 i;
	SI32 sum = 0;

	for(i = 0;i < MAX_ITEM_PER_PERSON;i++)
	{
		if(clItem[i].siUnique)
		{
			sum += clItem[i].GetWeight(pclItemManager, TRUE);
		}
	}
	return sum;
}


// ������ Ÿ���� ���Ѵ�. 
SI32 cltPItemInfo::GetWeaponType(cltItemManagerCommon* pclItemManager, SI16 activeweapon)
{
	return clItem[activeweapon].GetType(pclItemManager);
}

/*
// ������ ������ ���Ѵ�. 
SI32 cltPItemInfo::GetEquipMag(cltItemManagerCommon* pclItemManager, SI16 activeweapon)
{
	//return clItem[activeweapon].GetEquipMag(pclItemManager) 
	return clItem[PERSONITEM_RING1].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_RING2].GetEquipMag(pclItemManager)
		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
		+ clItem[PERSONITEM_HELMET].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_ARMOUR].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_WEAPON1].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_NECK].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_BELT].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_SHOES].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_MANTLE].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_HAT].GetEquipMag(pclItemManager)
		+ clItem[PERSONITEM_DRESS].GetEquipMag(pclItemManager);
}

// ������ �ٷ��� ���Ѵ�. 
SI32 cltPItemInfo::GetEquipStr(cltItemManagerCommon* pclItemManager)
{
	return clItem[PERSONITEM_RING1].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_RING2].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_MANTLE].GetEquipStr(pclItemManager)
		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
		+ clItem[PERSONITEM_HELMET].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_ARMOUR].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_WEAPON1].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_NECK].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_BELT].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_SHOES].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_HAT].GetEquipStr(pclItemManager)
		+ clItem[PERSONITEM_DRESS].GetEquipStr(pclItemManager);	
}

// ������ ���߷��� ���Ѵ�. 
SI32 cltPItemInfo::GetEquipDex(cltItemManagerCommon* pclItemManager)
{
	return clItem[PERSONITEM_RING1].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_RING2].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_MANTLE].GetEquipDex(pclItemManager)
		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
		+ clItem[PERSONITEM_HELMET].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_ARMOUR].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_WEAPON1].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_NECK].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_BELT].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_SHOES].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_HAT].GetEquipDex(pclItemManager)
		+ clItem[PERSONITEM_DRESS].GetEquipDex(pclItemManager);		
}

// ������ ������� ���Ѵ�. 
SI32 cltPItemInfo::GetEquipVit(cltItemManagerCommon* pclItemManager)
{
	return clItem[PERSONITEM_RING1].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_RING2].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_MANTLE].GetEquipVit(pclItemManager)
		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
		+ clItem[PERSONITEM_HELMET].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_ARMOUR].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_WEAPON1].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_NECK].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_BELT].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_SHOES].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_HAT].GetEquipVit(pclItemManager)
		+ clItem[PERSONITEM_DRESS].GetEquipVit(pclItemManager);	
}
*/



// ����� �ߵ��� ����� ���Ѵ�.  (�ٰŸ� ���⸸)
SI32 cltPItemInfo::GetEquipPoisonRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon)
{
	// ��ȯ�� ���� ������ ���� ����� �߰� 
	SI32 siTotalRate = 0;

	cltItem* pclitem = (cltItem*)&clItem[activeweapon];
	if(pclitem->siUnique == 0)			return siTotalRate;

	SI64 atb = pclItemManager->GetItemAtb(pclitem->siUnique);
	if((atb & ITEMATB_NEARWEAPON) == 0)	return siTotalRate;

	if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_POISON)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara1;
	}
	if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_POISON)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara2;
	}

	return siTotalRate;
}

// ����� �����Ѽ�Ȯ�� ����� ���Ѵ�.  ( ���Ÿ� ���⸸ )
SI32 cltPItemInfo::GetEquipIceRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon)
{
	// ��ȯ�� ���� ������ ���� ����� �߰� 
	SI32 siTotalRate = 0;

	cltItem* pclitem = (cltItem*)&clItem[activeweapon];
	if(pclitem->siUnique == 0)			return siTotalRate;

	SI64 atb = pclItemManager->GetItemAtb(pclitem->siUnique);
	if((atb & ITEMATB_FARWEAPON) == 0)	return siTotalRate;

	if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_ICE)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara1;
	}
	if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_ICE)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara2;
	}
	
	return siTotalRate;
}


// ����� �����Ѽ�Ȯ�� ����� ���Ѵ�. (�Ÿ�����)
SI32 cltPItemInfo::GetEquipDrainRate(cltItemManagerCommon* pclItemManager,SI16 active)
{

	// ��ȯ�� ���� ������ ���� ����� �߰� 
	SI32 siTotalRate = 0;

	cltItem* pclitem = (cltItem*)&clItem[active];
	if(pclitem->siUnique == 0)		return siTotalRate;

	SI64 atb = pclItemManager->GetItemAtb(pclitem->siUnique);
	if((atb & ITEMATB_SHOES) == 0)	return siTotalRate;

	if( pclitem->clItemCommon.clOptionInfo.uiType1 == SCROLL_UNIQUE_FUNCTION_DRAIN)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara1;
	}
	if( pclitem->clItemCommon.clOptionInfo.uiType2 == SCROLL_UNIQUE_FUNCTION_DRAIN)
	{
		siTotalRate +=pclitem->clItemCommon.clOptionInfo.uiPara2;
	}
	
	return siTotalRate;
}



bool cltPItemInfo::IsBlankInv(cltItemManagerCommon*pclItemManager,SI32 invnum,SI32 invmode)
{
	SI32 index = 0 ;
	SI32 start = 0, end = 0;
	if(invmode == INVMODE_PERSON)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_HORSE)
	{
		start	= PERSONITEM_HORSE0;
		end		= start + MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_BAG)
	{
		start	= PERSONITEM_BAG0;
		end		= start + MAX_ITEM_PER_BAG;
	}
	else if(invmode == INVMODE_BAG_SUB)
	{
		start	= PERSONITEM_BAG1;
		end		= start + MAX_ITEM_PER_BAG;
	}
	else if(invmode == INVMODE_ALL)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_INVITEM_PER_PERSON;
	}
	else
	{
		return false;
	}

	for (SI32 i = start ; i < end ; i ++ )
	{
		if ( clItem[i].siUnique == 0 && clItem[i].siItemNum == 0 )
		{
			index ++ ;
		}
	}

	if ( index >= invnum )
		return true ;

	return false ;
}

// ���־��� Ư���� ���(����ũ�� ������, �ɷ��� �ְ����)���� ���ȴ�. - �ݵ�� �߰��Ǵ� ������ Ÿ�Կ� ���� �߰��� �Ǿ�� �Ѵ�.
bool cltPItemInfo::CanToitemPos(cltItemManagerCommon* pclItemManager, SI32 toItempos )
{
	// ����ü�� ���ؼ��� �˻��Ѵ�.
	if(clItem[toItempos].GetType(pclItemManager) == ITEMTYPE_CRYSTAL)
	{
		if( clItem[toItempos].clItemCrystal.uiCrystalAbility != 0 || clItem[toItempos].clItemCrystal.uiCrystalAbilityNum != 0 )
				return false;
	}

	return true;
}



// �κ��丮�� �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
// onlypileswitch��ø�� ���ȴ�. ���ο� ��ġ�� ���̴°��� �����ȴ�. 
bool cltPItemInfo::CanAddInv(cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve, SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue, SI16* pCheckPos )
{
	SI32 i;
	BOOL pileswitch = FALSE;			// �������� ��ø ��� ����. 
	if(pclitem == NULL)return FALSE;

	if (pclitem->GetItemNum() > MAX_ITEM_PILE_NUMBER)
		return false;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	if( pclitem->CanPile(pclItemManager ) == true)
	{
		pileswitch = TRUE;
	}
	else
	{
		pileswitch = FALSE;
	}

	SI32 start = 0, end = 0, searchrange = 0;
	if(invmode == INVMODE_PERSON)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_ITEM_PER_INVENTORY;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_HORSE)
	{
		start	= PERSONITEM_HORSE0;
		end		= start + MAX_ITEM_PER_INVENTORY;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_BAG)
	{
		start	= PERSONITEM_BAG0;
		end		= start + MAX_ITEM_PER_BAG;
		searchrange = MAX_ITEM_PER_BAG;
	}
	else if(invmode == INVMODE_BAG_SUB)
	{
		start	= PERSONITEM_BAG1;
		end		= start + MAX_ITEM_PER_BAG;
		searchrange = MAX_ITEM_PER_BAG;
	}

	else if(invmode == INVMODE_ALL)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_INVITEM_PER_PERSON;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else
	{
		MsgBox(TEXT("vdfd82"), TEXT("fdvkd:%d"), invmode);
		return false;
	}

	// �̹� ���� �������� �����ϴ��� Ȯ���Ѵ�. 
	// ���� �������� �����ϰ� ��ø�� ������ �ִ� ���� �ȿ� ������ ��ø������ ���δ�. 
	if(pileswitch == TRUE)
	{
		for(i = start;i < end; i++)
		{
			if((clItem[i].siUnique == pclitem->siUnique)&&
				(clItem[i].CanPile(pclItemManager) == true))
			{
				if(clItem[i].GetItemNum() + pclitem->GetItemNum() <= MAX_ITEM_PILE_NUMBER)
				{
					// ���������� ������ ����� ����������� ��ĥ�� �ִ� ���������� �˻��Ѵ�.
					//if(CanToitemPos(pclItemManager, i) == true)
					{
						*pitempos = i;
						pcltoitem->Set(&clItem[i]);
						return true;
					}
				}
			}
		}
	}

	// ���Ӱ� �߰��Ѵ�. 
	for(i = start;i < start + searchrange;i++)
	{
		if(clItem[i].siUnique)continue;
        
		// ����Ǿ� �ִ� �ڸ����, 
		if(pdwreserve && pdwreserve[i])continue;

		bool loop = false;
		if(pCheckPos)
		{
			for(SI16 j = 0; j < 5; ++j)
			{
				if(pCheckPos[j] == i)
				{
					loop = true;
					break;
				}
			}
		}

		if(true == loop)
			continue;
		
		*pitempos = i;
		return true;
	}

	// ��ø�� ���Ǵ� �����, �ű���ġ�� �˻����� �ʴ´�. 
	if(invmode == INVMODE_ALL)
	{
		*prtnvalue = CANADDINV_FAIL_FULL;
		return false;
	}

	// ���Ӱ� �߰��Ѵ�. 
	for(i = (start + searchrange);i < end;i++)
	{
		if(clItem[i].siUnique)continue;
		
		// ����Ǿ� �ִ� �ڸ����, 
		if(pdwreserve && pdwreserve[i])continue;

		bool loop = false;
		if(pCheckPos)
		{
			for(SI16 j = 0; j < 5; ++j)
			{
				if(pCheckPos[j] == i)
				{
					loop = true;
					break;
				}
			}
		}

		if(true == loop)
			continue;
		
		*pitempos = i;
		return true;
	}

	return false;
}

// �κ��丮�� nIndexNum ���� ��ŭ�� �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
// onlypileswitch��ø�� ���ȴ�. ���ο� ��ġ�� ���̴°��� �����ȴ�. 
bool cltPItemInfo::CanAddInvManyItems(cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,  SI32* prtnvalue)
{
	if(pclitem == NULL)return FALSE;

	SI32 i = 0, j = 0 , k = 0;
	BOOL pileswitch = FALSE;			// �������� ��ø ��� ����. 
	BOOL bCanAdd = FALSE;				// ������ �ִ��� ����.
	BOOL bAlreadyAdd = FALSE;			// �̹� ������ �ִ� �ڸ��� üũ�Ǿ� �ִ��� ����.
	SI32 itemPos[MAX_CANADDINV_CHECK_NUM]; // ������ �ִٰ� üũ�� �ڸ� ���迭. 

	SI32 start = 0, end = 0, searchrange = 0;
	if(invmode == INVMODE_PERSON)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_ITEM_PER_INVENTORY;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_HORSE)
	{
		start	= PERSONITEM_HORSE0;
		end		= start + MAX_ITEM_PER_INVENTORY;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else if(invmode == INVMODE_BAG)
	{
		start	= PERSONITEM_BAG0;
		end		= start + MAX_ITEM_PER_BAG;
		searchrange = MAX_ITEM_PER_BAG;
	}
	else if( invmode == INVMODE_BAG_SUB )
	{
		start	= PERSONITEM_BAG1;
		end		= start + MAX_ITEM_PER_BAG;
		searchrange = MAX_ITEM_PER_BAG;
	}
	else if(invmode == INVMODE_ALL)
	{
		start	= PERSONITEM_INV0;
		end		= start + MAX_INVITEM_PER_PERSON;
		searchrange = MAX_ITEM_PER_INVENTORY;
	}
	else
	{
		MsgBox(TEXT("vdfd82"), TEXT("fdvkd:%d"), invmode);
		return false;
	}

	// nIndexNum ���� ��ŭ �ݺ��ϸ� �������� ������ �ִ��� üũ
	for(  j = 0; j < MAX_CANADDINV_CHECK_NUM ; j++ )
	{
		if( pclitem[j].siUnique <= 0 ) continue;

		bCanAdd = FALSE;

		// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
		if( pclitem[j].CanPile(pclItemManager) == true)
		{
			pileswitch = TRUE;
		}
		else
		{
			pileswitch = FALSE;
		}

		// �̹� ���� �������� �����ϴ��� Ȯ���Ѵ�. 
		// ���� �������� �����ϰ� ��ø�� ������ �ִ� ���� �ȿ� ������ ��ø������ ���δ�. 
		if(pileswitch == TRUE)
		{
			for( i = start;i < end; i++)
			{
				if((clItem[i].siUnique ==pclitem[j].siUnique)&&
					(clItem[i].CanPile(pclItemManager) == true))
				{
					//�̹� �� ������ ������ ���̶�� �������� �׳� �Ѿ��. 
					bAlreadyAdd = FALSE;
					for( k = 0; k < MAX_CANADDINV_CHECK_NUM; k++ )
					{			
						if( itemPos[k] == i )
						{
							bAlreadyAdd = TRUE;
							break;
						}
					}
					if( bAlreadyAdd == TRUE)
						continue;

					if(clItem[i].GetItemNum() + pclitem[j].GetItemNum() <= MAX_ITEM_PILE_NUMBER)
					{
						// ���������� ������ ����� ����������� ��ĥ�� �ִ� ���������� �˻��Ѵ�.
						//if(CanToitemPos(pclItemManager, i) == true)
						{
							itemPos[j] = i;
							bCanAdd = TRUE;
							break;
						}
					}
				}
			}			

			if( bCanAdd == TRUE)
				continue;
		}
		
		// ���Ӱ� �߰��Ѵ�. - by LEEKH 2007.08.21 ������ ũ��� MAX_ITEM_PER_INVENTORY�� �ƴϴ�.
		// �� �����ϴ� CanAddInv �Լ��� ����� ������
		//for(i = start;i < start + MAX_ITEM_PER_INVENTORY;i++)
		for(i = start;i < start + searchrange;i++)
		{
			if(clItem[i].siUnique)continue;

			//�̹� �� ������ ������ ���̶�� �������� �׳� �Ѿ��. 
			bAlreadyAdd = FALSE;
			for( k = 0; k < MAX_CANADDINV_CHECK_NUM; k++ )
			{			
				if( itemPos[k] == i )
				{
					bAlreadyAdd = TRUE;
					break;
				}
			}
			if( bAlreadyAdd == TRUE)
				continue;

			// ����Ǿ� �ִ� �ڸ����, 
			if(pdwreserve && pdwreserve[i])continue;

			itemPos[j] = i;
			bCanAdd = TRUE;
			break;
		}
		if( bCanAdd == TRUE)
			continue;


		// ��ø�� ���Ǵ� �����, �ű���ġ�� �˻����� �ʴ´�. 
		if(invmode == INVMODE_ALL)
		{
			*prtnvalue = CANADDINV_FAIL_FULL;
			return false;
		}

		// ���Ӱ� �߰��Ѵ�. - by LEEKH 2007.08.21 - �� �����ϴ� CanAddInv �Լ��� ����� ������
		//for(i = (start + MAX_ITEM_PER_INVENTORY);i < end;i++)
		for(i = (start + searchrange);i < end;i++)
		{
			if(clItem[i].siUnique)continue;

			//�̹� �� ������ ������ ���̶�� �������� �׳� �Ѿ��. 
			bAlreadyAdd = FALSE;
			for( k = 0; k < MAX_CANADDINV_CHECK_NUM; k++ )
			{			
				if( itemPos[k] == i )
				{
					bAlreadyAdd = TRUE;
					break;
				}
			}
			if( bAlreadyAdd == TRUE)
				continue;

			// ����Ǿ� �ִ� �ڸ����, 
			if(pdwreserve && pdwreserve[i])continue;

			itemPos[j] = i;
			bCanAdd = TRUE;
			break;
		}
		if( bCanAdd == TRUE)
			continue;

		// ������� �׳� ���� ���Դٸ� ������ ���ٴ°��̴�.
		*prtnvalue = CANADDINV_FAIL_FULL;
		return false;
	}
	return true;

}

// �κ��丮�� �������� �߰��Ѵ�. 
bool cltPItemInfo::AddInv(cltItemManagerCommon* pclItemManager, cltItem* pclitem)
{
	SI16 itempos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(CanAddInv(pclItemManager, INVMODE_ALL, pclitem, NULL, &itempos, &cltoitem, &rtnvalue) == true)
	{
		clItem[itempos].Add(pclItemManager, pclitem);
		return true;
	}

	return false;

}


// �κ��丮 �������߿��� �ϳ��� �����ϰ� ���´�. 
bool cltPItemInfo::RobInv(SI32* pitempos, cltItem* pclitem)
{
	SI32 i;

	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_ITEM_PER_INVENTORY;i++)
	{
		if(clItem[i].siUnique)
		{
			*pitempos = i;
			pclitem->Set(&clItem[i]);
			//KHY - 0706 - �Ⱓ�� �������� ��� �Ⱓ�� �־��ش�.
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
			pclitem->uiDateUseDay = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			
			return true;
		}
	}

	return false;
}


bool cltPItemInfo::IsSame(cltPItemInfo* pcliteminfo, bool numcomp )
{
	SI32 i;

	if(pcliteminfo ==  NULL)return FALSE;

	for(i = 0;i < MAX_ITEM_PER_PERSON;i++)
	{
		if(clItem[i].IsSame(&pcliteminfo->clItem[i], numcomp) == FALSE)return false;
	}

	return true;
}


// �־��� �����۰� ��Ȯ�ϰ� ��ġ�ϴ� �������� ã�Ƽ� �� �����͸� �����Ѵ�. 
SI32 cltPItemInfo::FindItemInv(cltItem* pclitem, bool numcomp)
{
	SI32 i;

	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(clItem[i].siUnique)
		{
			if(clItem[i].IsSame(pclitem, numcomp) == TRUE)
			{
				return i;
			}
		}
	}

	return -1;
}

// �־��� �����۰� ��Ȯ�ϰ� ��ġ�ϴ� �������� ã�Ƽ� �� ��ġ�� �����Ѵ�. 
SI32 cltPItemInfo::FindItemInv(SI32 itemunique)
{
	SI32 i;

	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(clItem[i].siUnique)
		{
			if(clItem[i].siUnique == itemunique)
			{
				return i;
			}
		}
	}

	return -1;
}


// unique�� �������� ��� ���� �ִ°� ?
SI32  cltPItemInfo::GetItemNum(SI32 itemunique)
{
	SI32 i;
	SI32 haveitemnum = 0;
	
	if(itemunique <= 0)return 0;

	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(clItem[i].siUnique == itemunique)
		{
			haveitemnum += clItem[i].siItemNum;
		}
	}

	return haveitemnum;
}

// ���â�ȿ� unique�� �������� ��� ���� �ִ°�?
SI32 cltPItemInfo::GetItemNumInEquip(SI32 itemunique)
{
	SI32 i;
	SI32 haveitemnum = 0;

	if(itemunique <= 0)return 0;

	for(i = 0;i < PERSONITEM_INV0; i++)
	{
		if(clItem[i].siUnique == itemunique)
		{
			haveitemnum += clItem[i].siItemNum;
		}
	}

	return haveitemnum;
}

// unique�� �������� �κ��� �����ϴ°� ?
SI32  cltPItemInfo::GetItemPos(SI32 itemunique)
{
	SI32 i;
	
	if(itemunique <= 0)return 0;

	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(clItem[i].siUnique == itemunique)
		{
			return i;
		}
	}

	return -1;
}

// unique�� �������� �κ��� �����ϴ°� ?
SI32  cltPItemInfo::GetItemTotalPos(SI32 itemunique)
{
	SI32 i;

	if(itemunique <= 0)return 0;

	for( i = 0;i < MAX_ITEM_PER_PERSON ; i++ )
	{
		if(clItem[i].siUnique == itemunique)
		{
			return i;
		}
	}

	return -1;
}

// ���â�ȿ� unique�� �������� ��ġ ����
SI32  cltPItemInfo::GetItemPosInEquip(SI32 itemunique)
{
	SI32 i;

	if(itemunique <= 0)return 0;

	for( i = 0;i < PERSONITEM_INV0 ; i++ )
	{
		if(clItem[i].siUnique == itemunique)
		{
			return i;
		}
	}

	return -1;
}


// Ư�� �����۵��� �� �κ��� �� �� �ִ°�. 
// �� �� �ִٸ� ��� ��ġ�� �� �� �ִ°��� ���س���. 
bool cltPItemInfo::CanInputItemList(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32 itemlistnum, SI16* pclpos)
{

	SI32 i;
	cltItem clitem;
	SI32 rtnvalue;

	SI16 checkPos[MAX_PRIVATETRADEORDER_ITEM_NUM] = {0, 0, 0, 0, 0};

	for(i = 0; i < itemlistnum;i++)
	{
		if(pclitem[i].siUnique<= 0)continue;

		if(CanAddInv(pclItemManager, INVMODE_ALL, &pclitem[i], NULL, &pclpos[i], &clitem, &rtnvalue, checkPos ) == false)
		{
			return false;
		}
		checkPos[i] = *(&pclpos[i]);
	}

	return true;

}

// Ư�� �������� ���ǰ�� ���Ǿ� �ִ°� ?
bool cltPItemInfo::HaveInEquip(SI32 itemunique)
{
	SI32 i;

	for(i = 0;i < PERSONITEM_INV0;i++)
	{
		if(clItem[i].siUnique && clItem[i].siUnique == itemunique)
		{
			return true;
		}
	}

	return false;
}

// ��� ���ǰ�� ���������� ���Ǿ� �ִ°� ?
bool cltPItemInfo::IsAllProperEquip(cltItemManagerCommon* pclItemManager, SI16* punique, SI16* ppos, SI32 siKind)
{

	SI32 i;

	for(i = 0;i < PERSONITEM_INV0;i++)
	{
		if(clItem[i].siUnique <= 0)continue;

		if(pclItemManager->CheckProperItemPos(&clItem[i], i, siKind) == FALSE)
		{
			*punique	= clItem[i].siUnique;
			*ppos		= i;
			return false;
		}
	}

	return true;
}

// ���� ��ǰ�� ������ �ִ°�?
bool cltPItemInfo::IsHorseHaveItem()
{
	SI32 i;

	for(i = PERSONITEM_HORSE0;i < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY;i++)
	{
		if(clItem[i].siUnique)return true;
	}

	return false;
}

// ���濡  ��ǰ�� ������ �ִ°�?
bool cltPItemInfo::IsBagHaveItem()
{
	SI32 i;

	for(i = PERSONITEM_BAG0;i < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG;i++)
	{
		if(clItem[i].siUnique)return true;
	}

	return false;
}


// ���� ��� ������ ����� ���� �ִ°� ?
// skill : SKILL_USESWORD1 ...
bool cltPItemInfo::UseWeasponSkillScroll(cltItemManagerCommon* pclItemManager,SI32 skill)
{

	SI32 up = clItem[PERSONITEM_HELMET].GetSkillScrollUp(pclItemManager, skill)
			+ clItem[PERSONITEM_HAT].GetSkillScrollUp(pclItemManager, skill)
			+ clItem[PERSONITEM_DRESS].GetSkillScrollUp(pclItemManager, skill)
			+ clItem[PERSONITEM_ARMOUR].GetSkillScrollUp(pclItemManager, skill);

	if(up)return true;

	return false;
}

UI32 cltPItemInfo::UseWeasponSkillScrollNum(cltItemManagerCommon* pclItemManager,SI32 skill)
{

	UI32 up = clItem[PERSONITEM_HELMET].GetSkillScrollUp(pclItemManager, skill)
		+ clItem[PERSONITEM_HAT].GetSkillScrollUp(pclItemManager, skill)
		+ clItem[PERSONITEM_DRESS].GetSkillScrollUp(pclItemManager, skill)
		+ clItem[PERSONITEM_ARMOUR].GetSkillScrollUp(pclItemManager, skill);

	return up;
}

bool cltPItemInfo::IsHaveMaterialItem( cltItemManagerCommon* pclItemManager, SI32 siItemUnique, SI32 siAmount )
{
	if ( NULL == pclItemManager )
	{
		return false;
	}

	SI32 siReference = pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= siReference )
	{
		return false;
	}

	cltItemInfo* pclMaterialInfo = (cltItemInfo*)pclItemManager->pclItemInfo[ siReference ];
	if ( pclMaterialInfo == NULL )
	{
		return false;
	}

	SI32 siMaterialUnique[MAX_MATERIAL_NUMBER]	= {0, };
	SI32 siMaterialAmount[MAX_MATERIAL_NUMBER]	= {0, };
	SI32 siDoNotHaveCount						= 0;

	// �ش�������� �ʿ��� ���������� ���ؿ´�
	for ( SI32 siIndex=0; siIndex<MAX_MATERIAL_NUMBER; ++siIndex )
	{
		SI32 siGetUnique	= pclMaterialInfo->clProductionInfo.clMaterial[ siIndex ].siUnique;
		SI32 siGetAmount	= pclMaterialInfo->clProductionInfo.clMaterial[ siIndex ].siNeedNum;
		bool bSearchResult	= false;


		if ( (0 >= siGetUnique) || (0 >= siGetAmount) )
		{
			// �� ������ MAX_MATERIAL_NUMBER �̻��϶��� ���������� ���� ���̹Ƿ� �̰Ͷ��� false�� �����Ѵ�
			++siDoNotHaveCount;
			continue;
		}
		
		if ( 0 < siAmount )
		{
			siGetAmount = siGetAmount * siAmount;
		}

		// ���� �� �κ��丮�� ��� �������� �ִ��� �˻�
		for ( SI32 siPos=MAX_SHAPE_ITEM; siPos<MAX_ITEM_PER_PERSON; ++siPos )
		{
			if ( (clItem[siPos].siUnique == siGetUnique) && (clItem[siPos].siItemNum >= siGetAmount) )
			{
				bSearchResult = true;
				break;
			}
		}
		
		// �������� ���ų� ������ ��������ʴٸ� 
		if ( false == bSearchResult )
		{
			return false;
		}
	}

	if ( MAX_MATERIAL_NUMBER <= siDoNotHaveCount )
	{
		return false;
	}

	return true;

}



