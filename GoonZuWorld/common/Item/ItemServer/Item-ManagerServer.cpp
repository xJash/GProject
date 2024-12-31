//---------------------------------
// 2003/8/7 ���°�
//---------------------------------

#include "Item-ManagerServer.h"
#include "..\Server\Server.h"
#include "../../Server/Minister/MinisterBase.h"
#include "../../Server/Minister/MinisterMgr.h"
#include "../../Server/Minister/Minister-Izo.h"
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharServer\Char-Server.h"

#include "item/ItemCommon/cltSetItem.h"

extern cltCommonLogic* pclClient;

cltItemManagerServer::cltItemManagerServer(SI32 gamemode) : cltItemManagerCommon()
{
	//pclSetItemManager = new CSetItemManager;
	//pclSetItemManager->LoadSetItemInfo();
}

cltItemManagerServer::~cltItemManagerServer()
{
	if( pclSetItemManager)
	{
		delete pclSetItemManager;
		pclSetItemManager = NULL;
	}
}

// KindInfo�� ������ ������ �ٰŷ� ������ �������� �ϳ� �����. 
bool cltItemManagerServer::MakeRandItem(SI32 level, SI32 addrate, cltKindItemProbabilitySet* pclikinditem, cltItem* pclitem)
{
	cltItem clItem;

	// KindInfo�� �ִ� �������� ������ ���´�. 
	SI32 siitemunique, itemnum;
	if(pclikinditem->GetRandDropItem(level, addrate, &siitemunique, &itemnum) == true)
	{
		if(siitemunique == 0)return false;
		
		// �������� Unique������ ���� �����ϰ� �������� �ϳ� �����.
		SI16 brareswitch = 0;
		if(MakeRandItemUnique(siitemunique, pclitem, 0, 0, &brareswitch) == true)
		{
			pclitem->siItemNum	= itemnum;
			return true;
		}
	}


	return false;
}

// ��ü���� ���� ����Ʈ�� ���´�. (����Ʈ�� �����ϰ� ������ ���¿��� ���޵Ǿ�� �Ѵ�.) 
bool cltItemManagerServer::GetDismantleMaterial(cltCharServer* pclchar, cltItem clitem, cltItem* pclitemlist, SI16 *pMakePercent )
{
	if ( pMakePercent == NULL )
	{
		return false;
	}

	// �ش� �������� Ÿ���� ���Ѵ�.
	SI32 itemtype = clitem.GetType(this);
	if(itemtype == 0)return false;

	if(pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_OBJECT) == false)return false;

	// �������� DUR_FOR_DISMANTLE ���Ͽ��� �Ѵ�. 
	if ( pclchar != NULL && pclchar->GetGameMasterLevel() > BASIC_GAMEMASTER_LEVEL )
	{
	}
	else if(clitem.GetDurability() > DUR_FOR_DISMANTLE)
		return false;

	SI32 ref = FindItemRefFromUnique(clitem.siUnique);
	if(ref <= 0)return false;

	// ���� �Ұ� ��ǰ. 
	if(pclItemInfo[ref]->clProductionInfo.clMaterial[0].siUnique == 0)return false;

	// ��ó���� ������ ���´�. 
	//SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_ALCHEMY, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);
	SI32 skilllevel = 0;
	if(skilllevel <= 0)return false;

	/*
	SI16 itemgetrate = 40;

	if(skilllevel > 30)
	{
	itemgetrate += (skilllevel - 30) / 2;
	skilllevel = 30;
	}

	itemgetrate += skilllevel/2;
	*/

	// ���� ȹ����� ���Ѵ�. 
	SI16 itemgetrate = 40 + skilllevel * 2 / 3 + ( skilllevel - 30 ) /2;

	cltServer* pclserver = (cltServer*)pclClient;
	CMinisterIzo* pclminister = (CMinisterIzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_IZO);
	SI32 rate = min(75, max(50, pclminister->m_siPriceValue));
	itemgetrate += ( 75 - rate ) * (-0.5 );

	if ( itemgetrate < 40 )
	{
		itemgetrate = 40;
	}

	if( itemgetrate > 80 )
	{
		itemgetrate = 80;
	}

	*pMakePercent = itemgetrate;

	SI32 index = 0;
	for(SI32 i = 0;i < MAX_MATERIAL_NUMBER;i++)
	{
		// ���� �������� ��ȿ�ؼ��� �ȵȴ�. 
		SI32 itemunique = pclItemInfo[ref]->clProductionInfo.clMaterial[i].siUnique;
		if(itemunique == 0)continue;

		SI32 tempref = FindItemRefFromUnique(itemunique);
		if(ref <= 0)continue;

		// ���ᰡ Object������ �ȵȴ�. 
		SI32 tempitemtype = pclItemInfo[tempref]->siType;
		if(pclItemTypeInfo[tempitemtype]->IsAtb(ITEMATB_OBJECT) == TRUE)continue;

		// ������ �����Ѵ�. 
		SI32 itemnum = pclItemInfo[ref]->clProductionInfo.clMaterial[i].siNeedNum * itemgetrate / 100;
		if(itemnum <= 0)continue;


		pclitemlist[index].Set( &pclItemInfo[tempref]->clItem);
		pclitemlist[index].SetItemNum(itemnum);
		index++;

	}

	if(index)
	{
		return true;
	}

	return false;


}

/*
bool cltItemManagerServer::GetEnchantDamageFromGrade(SI32 siGrade)
{



}*/

