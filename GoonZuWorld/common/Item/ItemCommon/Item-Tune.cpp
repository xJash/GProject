//---------------------------------
// 2003/8/7 ���°�
//---------------------------------
#include "cltItem.h"
#include "CommonLogic.h"

extern cltCommonLogic* pclClient;

// Ư�� �������� ���������� ������ ����. 
bool cltItemManagerCommon::CanTune(cltItem* pclitem)
{
	if(pclitem == NULL)return false;
	if(pclitem->siUnique <= 0)return false;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	SI32 type = pclitem->GetType(this);
	if(type <= 0)return false;

	SI64 atb = pclClient->pclItemManager->pclItemTypeInfo[type]->siAtb;

	// object Ÿ���̾�� �Ѵ�. 
	if((atb & ITEMATB_OBJECT) == 0)return false;

	// �ִ� �������� MAX_DUR_FOR_TUNE���Ͽ��� �Ѵ�. 
	if(pclitem->clItemCommon.clCommonInfo.uiMaxDurability > MAX_DUR_FOR_TUNE)return false;

	// �к����� �ƴϾ�� �Ѵ�.
	if ( pclitem->IsSealingUp(this) == true )
		return false ;

	// ���ǰ�̸� ����. 
	if(pclitem->clItemCommon.clCommonInfo.uiRareInfo != 0 && pclitem->clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_1)return false;

	SI32 ref = FindItemRefFromUnique(pclitem->siUnique) ;

	if ( ref )
	{
		if ( pclItemInfo[ref]->siSetItemIndex > 0 )
			return false ;
	}
	else return false ;

	return true;
}

// �������� ���������� �����Ѵ�. 
bool cltItemManagerCommon::GetTuneItem(cltItem* pclitem,bool bSuccess,SI32 mode)
{
	if(CanTune(pclitem) == false)return false;

	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);
	if(ref <= 0)return false;
	


	// ���ǰ�̸� ����. 
	if(pclitem->clItemCommon.clCommonInfo.uiRareInfo == 0)
	{
		if( (rand() % 7) && !bSuccess )return false;

		// �������� ȸ�������ش�. 
		pclitem->clItemCommon.clCommonInfo.uiMaxDurability  = pclItemInfo[ref]->clItem.clItemCommon.clCommonInfo.uiMaxDurability;
		pclitem->clItemCommon.clCommonInfo.uiDurability		= pclitem->clItemCommon.clCommonInfo.uiMaxDurability;

		pclitem->clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_1;	// ȣǰ���� ������ش�.  
	}
	// ȣǰ�̸� ����. 
	else if(pclitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1)
	{
		if( (rand() % 10) && !bSuccess )return false;

		// �������� ȸ�������ش�. 
		pclitem->clItemCommon.clCommonInfo.uiMaxDurability  = pclItemInfo[ref]->clItem.clItemCommon.clCommonInfo.uiMaxDurability;
		pclitem->clItemCommon.clCommonInfo.uiDurability		= pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
	
		// ��ǰ���� ������ش�. 
		MakeRareItem(pclitem,mode);


		pclitem->clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_2;	// ��ǰ���� ������ش�.  

	}

	return true;
}


// ���ǰ ���� ����� ���� ���� �䱸 ������ ���Ѵ�. 
bool cltItemManagerCommon::GetScrollForTune2(cltItem clitem, SI32* pscrollunique, SI32* pscrollnum, cltItem* pcldestitem, SI32* preturnval)
{
	SI32 ref = FindItemRefFromUnique(clitem.siUnique);
	if(ref <= 0)return false;

	if ( pclItemInfo[ref]->siSetItemIndex > 0 )
		return false ;

	// ������Ʈ �����̾�� �Ѵ�. 
	SI32 itemtype = pclItemInfo[ref]->siType;
	if(pclItemTypeInfo[itemtype]->siAtb & ITEMATB_OBJECT)
	{
	}
	else
	{
		*preturnval	= 0;
		return false;
	}

	pcldestitem->Set(&clitem);
	pcldestitem->DecreaseDurability(this, 40);
	if(pcldestitem->GetDurability() == 0)
	{
		*preturnval	= 0;
		return false;
	}

	// ������ �䱸 ����� 10��. 
	*pscrollnum		= 10;


	bool bweaponswitch = false;
	bool barmourswitch = false;
	switch(pclItemInfo[ref]->siType)
	{
	case ITEMTYPE_SWORD:	
		*pscrollunique	= ITEMUNIQUE(8845); // �����ۺ���. 
		bweaponswitch = true;
		break;
	case ITEMTYPE_SPEAR:
		*pscrollunique	= ITEMUNIQUE(8835); // â���ۺ���. 
		bweaponswitch = true;
		break;
	case ITEMTYPE_AXE:
		*pscrollunique	= ITEMUNIQUE(8830); // �������ۺ���. 
		bweaponswitch = true;
		break;
	case ITEMTYPE_STAFF:
		*pscrollunique	= ITEMUNIQUE(8850); // ���������ۺ���. 
		bweaponswitch = true;
		break;

	case ITEMTYPE_BOW:
		*pscrollunique	= ITEMUNIQUE(8840); // Ȱ���ۺ���. 
		bweaponswitch = true;
		break;

	case ITEMTYPE_GUN:
		*pscrollunique	= ITEMUNIQUE(8855); // �����ۺ���. 
		bweaponswitch = true;
		break;

	case ITEMTYPE_BELT:
		*pscrollunique	= ITEMUNIQUE(8875); // ������ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_HELMET:
		*pscrollunique	= ITEMUNIQUE(8590); // �������ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_HAT:
		*pscrollunique	= ITEMUNIQUE(8610); // �������ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_ARMOUR:
		*pscrollunique	= ITEMUNIQUE(8580); // �������ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_DRESS:
		*pscrollunique	= ITEMUNIQUE(8600); // �Ǻ����ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_SHOES:
		*pscrollunique	= ITEMUNIQUE(8620); // �Ź����ۺ���. 
		barmourswitch = true;
		break;

/*	case ITEMTYPE_NECK:
		*pscrollunique	= ITEMUNIQUE(8640); //  ��������ۺ���. 
		barmourswitch = true;
		break;

	case ITEMTYPE_RING:
		*pscrollunique	= ITEMUNIQUE(8650); // �������ۺ���. 
		barmourswitch = true;
		break;
*/

	}

	if(bweaponswitch)
	{
		// �������� ��ǰ�� ������ ���Ѵ�. 
// ���� �ý����� ���� ������� �ʴ´�.
/*		SI32 orgmindamage = pclItemInfo[ref]->clItem.GetMinDamage(this);
		SI32 orgmaxdamage = pclItemInfo[ref]->clItem.GetMaxDamage(this);

		// �ּ� �������� �������� ��ǰ���� SCROLL_TUNE_MAX_RATE���̻��̴�.
		if(pcldestitem->GetMinDamage(this) > (orgmindamage*SCROLL_TUNE_MAX_RATE) )
		{
			*preturnval	= SCROLLTUNE_ERR_MINDAMAGE;
			return false;
		}
		// �ִ� �������� �������� ��ǰ���� SCROLL_TUNE_MAX_RATE���̻��̴�.
		if(pcldestitem->GetMaxDamage(this) > (orgmaxdamage*SCROLL_TUNE_MAX_RATE) )
		{
			*preturnval	= SCROLLTUNE_ERR_MAXDAMAGE;
			return false;
		}


		pcldestitem->SetMinDamage(this, pcldestitem->GetMinDamage(this) + 2);
		pcldestitem->SetMaxDamage(this, pcldestitem->GetMaxDamage(this) + 2);
		return true;
*/
	}

	if(barmourswitch)
	{
		SI32 orgac = pclItemInfo[ref]->clItem.GetAC(this);

		// AC�� �������� ��ǰ���� SCROLL_TUNE_MAX_RATE���̻��̴�.
		if(pcldestitem->GetAC(this) > (orgac*SCROLL_TUNE_MAX_RATE) )
		{
			*preturnval	= SCROLLTUNE_ERR_AC;
			return false;
		}

		pcldestitem->SetAC(this, pcldestitem->GetAC(this) + 4);
		return true;
	}

	return false;
}