//---------------------------------
// 2003/6/26 ���°�
//---------------------------------

#include <Stdio.h>

#include "House.h"
#include "..\..\Common\Item\ItemCommon\cltItem.h"
#include "..\CityHall\TaxPaymentListDlg.h"

//--------------------------------------------------------
// cltHouseUnitStorageInfo
//--------------------------------------------------------
// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
bool cltHouseUnitStorageInfo::CanAddStg(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos)
{
	SI32 i;
	BOOL pileswitch = FALSE;			// �������� ��ø ��� ����. 
	if(pclitem == NULL)return FALSE;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	if(pclitem->CanPile(pclItemManager ) == true)
	{
		pileswitch = TRUE;
	}
	else
	{
		pileswitch = FALSE;
	}

	// �̹� ���� �������� �����ϴ��� Ȯ���Ѵ�. 
	// ���� �������� �����ϰ� ��ø�� ������ �ִ� ���� �ȿ� ������ ��ø������ ���δ�. 
	SI32 siItemCount = 0;
	if(pileswitch == TRUE)
	{
		for(i = 0;i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER;i++)
		{
			if( clItem[i].siItemNum == MAX_ITEM_PILE_NUMBER )
				continue;

			siItemCount = clItem[i].siItemNum + pclitem->siItemNum;
			if (clItem[i].siUnique == pclitem->siUnique && siItemCount > MAX_ITEM_PILE_NUMBER)
			{
				pclitem->siItemNum = pclitem->siItemNum - (siItemCount - MAX_ITEM_PILE_NUMBER);
			}

			if(clItem[i].siUnique == pclitem->siUnique && (clItem[i].siItemNum + pclitem->siItemNum <= MAX_ITEM_PILE_NUMBER))
			{
				//[����] 2010.1.26 â��ȿ� �ɷ� ũ����Ż�� �� �ɷ� ũ����Ż�� ����� �κ��� �̴ɷ� ũ����Ż�� â�� �ȿ� �������� �� ���
				// ������ �̴ɷ�ũ����Ż�� ��ø���� �ʴ� �κ��� �����մϴ�.
				if(ITEMTYPE_CRYSTAL == pclitem->GetType(pclItemManager))
				{
					if( true == clItem[i].CanPile(pclItemManager) && true == pclitem->CanPile(pclItemManager))
					{
						*pitempos = i;
						return true;
					}
				}
				else
				{
					*pitempos = i;
					return true;
				}
			}
		}
	}

	// ���Ӱ� �߰��Ѵ�. 
	for(i = 0;i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER;i++)
	{
		if(clItem[i].siUnique == 0)
		{
			*pitempos = i;
			return true;
		}
	}

	return false;
}

// â�� �ִ� �������� ��ġ�� ���Ѵ�.
SI16 cltHouseUnitStorageInfo::GetStgExistItemPos( SI16 ItemUnique, SI16 ItemNum )
{
	if ( ItemUnique < 1 )
	{
		return -1;
	}

	for( SI16 i = 0;i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++i )
	{
		if( clItem[i].siUnique > 0 &&
			clItem[i].siUnique == ItemUnique &&
			clItem[i].siItemNum >= ItemNum )
		{
			return i;
		}
	}
	
	return -1;
}

// â��  ���� �߰��� �� �ִ��� Ȯ���Ѵ�. 
bool cltHouseUnitStorageInfo::CanAddHorse( SI16 *pHorsePos )
{
	for ( SI16 i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
	{
		// �������� �־�� �ϰ�, ������ �ȿ� ���� ����� ������...
		if ( bCreatedHouseUnitStable[ i ] == true && clHorse[ i ].siHorseUnique == 0 )
		{
			*pHorsePos = i;

			return true;
		}
	}	
	
	return false;
}

bool cltHouseUnitStorageInfo::IsHorseExist( SI16 HorsePos )
{
	if ( bCreatedHouseUnitStable[ HorsePos ] == true && clHorse[ HorsePos ].siHorseUnique > 0 )
	{
		return true;
	}

	return false;
}

//--------------------------------------------------------
// cltHouse
//--------------------------------------------------------
cltHouse::cltHouse(SI32 sivillageunique): cltStructureBasic(sivillageunique)
{
	
}

cltHouse::~cltHouse() 
{
}

// ���� ����������� Ȯ���Ѵ�. 
BOOL cltHouse::IsSameContract(const cltRentContract* pclcontract)
{
	if(clStrInfo.clHouseStrInfo.clRentContract.IsSame(pclcontract) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

// ���� �ĺ��ڷ� ��û�Ѵ�. 
BOOL cltHouse::AddApplyer(const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_HOUSE;i++)
	{
		if(clApply[i].clPerson.GetPersonID() == 0)
		{
			clApply[i].Set(pclapplyer, pclcontract);
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��û�ڸ� �����Ѵ�. 
BOOL cltHouse::DeleteApplyer(SI32 personid)
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_HOUSE;i++)
	{
		if(clApply[i].clPerson.GetPersonID() == personid)
		{
			clApply[i].Init();
			return TRUE;
		}
	}

	return FALSE;
}

// �������� ���θ� Ȯ���Ѵ�. 
BOOL cltHouse::IsEmpty(SI32 slot)
{
	if(clUnit[slot].clPerson.GetPersonID() ) return FALSE;

	return TRUE;
}

//PersonID�� ������ ������� ������ ���Ѵ�. 
cltRentApplyer* cltHouse::GetHouseApplyerFromPersonID(SI32 personid)
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_HOUSE;i++)
	{
		if(clApply[i].clPerson.GetPersonID() == personid)
		{
			
			return &clApply[i];
		}
	}
	return NULL;
}

// �������� ������ ����Ѵ�.
BOOL cltHouse::SetRent(SI32 slot, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract)
{
	clUnit[slot].clPerson.Set(pclapplyer);
	clUnit[slot].clContract.Set(pclcontract);

	return TRUE;
}

// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
bool cltHouse::IsHouseHost(SI32 personid, SI32 houseunitslot)
{
	if(personid == 0)return false;
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return false;

	if(clUnit[houseunitslot].clPerson.GetPersonID() == personid)return true;

	return false;
}

// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
bool cltHouse::CanAddStg(SI32 houseunitslot, cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos)
{
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return false;

	return clUnit[houseunitslot].clStorageInfo.CanAddStg(pclItemManager, pclitem, pitempos);
}

// �������� â�� �ִ´�.
void cltHouse::SetItemStg(SI32 houseunitslot, SI32 stgpos, cltItem* pclitem)
{
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return ;

	clUnit[houseunitslot].clStorageInfo.SetItemStg(stgpos, pclitem);
}


// â�� �������� �����͸� ���Ѵ�. 
cltItem* cltHouse::GetStgItemPointer(SI32 houseunitslot, SI32 stgpos)
{
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return NULL;

	return clUnit[houseunitslot].clStorageInfo.GetStgItemPointer(stgpos);

}

// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
void cltHouse::GetRentFee()
{
	SI32 i;

	// ���� ������ �˻��Ͽ� �Ӵ�Ḧ ¡���Ѵ�. 
	for(i = 0;i < MAX_HOUSEUNIT_NUMBER;i++)
	{
		// �Ӵ밡 �Ǿ� �ִ� ���Ǹ� �˻��Ѵ�.
		SI32 personid = clUnit[i].clPerson.GetPersonID();
		if( personid <= 0)continue;

		// ������ Ȯ���Ѵ�. 
		GMONEY fee = clUnit[i].clContract.siRentFee;



	}
}
