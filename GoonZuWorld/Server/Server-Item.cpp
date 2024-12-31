//---------------------------------
// 2003/6/15 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"


//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "../Server/Statistics/Statistics.h"

#include "../Server/GachaManager/GachaManager.h"
#include "../Server/ArtifactRestoreManager/ArtifactRestoreManager.h"
#include "../Server/ServerBoxItem/ServerBoxItem.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
//���ϸ� ����Ʈ 3
#include "../../../DBManager/GameDBManager_World/DBMsg-DailyQuest3.h"

#include "..\CommonLogic\MsgType-Item.h"
#include "../CommonLogic/Msg/MsgType-DailyQuest3.h"

#include "Util/Util.h"
#include "MsgRval-Define.h"
#include "../Client/minigame/ZooKeeperLogic.h"

#include "../CommonLogic/MagicMgr/MagicBaseInfo.h"
#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../CommonLogic/BoxItemMgr/BoxItemMgr.h"

#include "..\CommonLogic\MsgType-Person.h"
#include "../../common/Char/CharServer/Char-Item.h"

#include "../common/Event/event.h"

#include "../../Common/Util/Util.h"

#include "NDate.h"

#include "../../Common/GameMaster/GameMaster.h"

#include "../../common/Item/ItemCommon/cltItem.h"// [����] ���� ���� ���ڿ��� �������� �ش� 

// NPC���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_NPCREPAIR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NPCRepair* pclinfo = (cltGameMsgRequest_NPCRepair*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclinfo->siPos;
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	//---------------------------------------------
	// �ش� �������� ������ �����ϴ��� Ȯ���Ѵ�. 
	//---------------------------------------------
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;
	cltItem* pclitem = &pclinfo->clItem;
	cltItem* pclorgitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[itempos];
	// �־��� �����۰� ���� ���������� Ȯ���Ѵ�. 
	if(pclitem->IsSame(pclorgitem, false) == false)
	{
		return ;
	}
	if(pclitem->siUnique <= 0)return ;
	// ���� �Ұ����� �������̾ ����.
	if(pclitem->CanRepair(pclItemManager) == false)return ;

	//--------------------------------------------
	// ���� ������ Ȯ���Ѵ�. 
	//--------------------------------------------
	SI32 decdur = MIN_DUR_FOR_REPAIR;

	// ��� ���ؿ� ���� �Ҹ�Ǵ� �������� ���Ѵ�. 
	decdur = GetWasteDurability(30);

	//--------------------------------------------
	// ������ ���Ѵ�. ��Ʈ�������� 2���ɿ� ������ �ü�
	//--------------------------------------------
	SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if(ref <= 0)
		return ;
	GMONEY repairmoney = 0 ;
	if ( pclItemManager->pclItemInfo[ref]->siSetItemIndex > 0 )
	{
		repairmoney = 20000 * pclItemManager->clItemStatistic.siNPCPriceRate / 100 ;
	}
	else
	{
		repairmoney = pclItemManager->GetNPCRepairPrice(pclitem);
	}

	if(repairmoney <= 0)return ;

	cltItem clitem;
	clitem.Set(pclitem);

	if(clitem.Repair(pclItemManager, decdur) == true)
	{
		//--------------------------------------------
		// ���� �ϵ��� DB�Ŵ������� ��û�Ѵ�. 
		//--------------------------------------------
		SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
		if( pclCM->IsValidID(pclinfo->siCharUnique))
		{
			SI32 VillageUnique = pclCM->CR[ pclinfo->siCharUnique ]->GetCurrentVillageUnique();

			sDBRequest_InvRepair clMsg(id, personid, itempos, &clitem, 0, repairmoney, VillageUnique);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		}

		// ��ȭ�� ���� 
		cltMoney clmoney;
		clmoney.Set(repairmoney);
		clCurrencyInfo.clOutputMoney_Repair.Increase(&clmoney);
	}
}

// NPC���� ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_NPCREPAIRPRICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NPCRepairPrice* pclinfo = (cltGameMsgRequest_NPCRepairPrice*)pclMsg->cData;

	if(pclinfo->clItem.siUnique <= 0)return ;

	GMONEY repairprice = pclItemManager->GetNPCRepairPrice(&pclinfo->clItem);

	if(repairprice)
	{
		cltGameMsgResponse_NPCRepairPrice clinfo(pclinfo->clItem.siUnique, repairprice);
		cltMsg clMsg(GAMEMSG_RESPONSE_NPCREPAIRPRICE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}

// WEAPON 1,2 Activate���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_EXCHANGEWEAPON(cltMsg* pclMsg, SI32 id)
{    
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )
	{
		return;
	}

	//[�߰� : Ȳ���� 2008. 1. 21 => ���Ž� ���� ��ü ���ϰ� �������� ����.]
	if ( true == pclchar->clTransFormInfo.bTransFormMode )
	{
		return;	
	}

	// ���� Ȱ�� �߿��� ���� ���� �Ұ�
	switch( pclchar->GetCurrentOrder() )
	{
		case ORDER_FISH:
		case ORDER_FARM:
		case ORDER_MINE:
			return;
	}

	// [����] �������� ���� �ִ� ���⸦ ����Ѵ�.
	SI32 siPrevActiveWeapon = pclchar->pclCI->clCharItem.clItem[pclchar->ActiveWeapon].siUnique;

	// Active ���⸦ Toggle�Ѵ�.
	if ( pclchar->ActiveWeapon == PERSONITEM_WEAPON1 )
	{
		pclchar->ActiveWeapon = PERSONITEM_WEAPON2;
	}
	else
	{
		pclchar->ActiveWeapon = PERSONITEM_WEAPON1;
	}

	// ������ ����� �ΰ� ����ص� ������ �����´�.
	SI32					siTempMagic			= pclchar->GetCurrentMagic();
	stMagicAttributeData*	pMagicAttributeData	= pclMagicManager->GetMagicAttribute( pclchar->siOldWeaponMagic );

	pclchar->SetCurrentMagic( pclchar->siOldWeaponMagic, pMagicAttributeData->si08MagicCastType );
	pclchar->siOldWeaponMagic = siTempMagic;

	// ���� Ÿ���� �޶����� ������ �ִ� ���� ���� ȿ���� ��������
	SI32 siWeaponType1 = pclchar->pclCI->clCharItem.clItem[ PERSONITEM_WEAPON1 ].GetType( pclItemManager );
	SI32 siWeaponType2 = pclchar->pclCI->clCharItem.clItem[ PERSONITEM_WEAPON2 ].GetType( pclItemManager );
	if ( siWeaponType1 != siWeaponType2 )
	{
		pclchar->m_clMagicBufMgr.Init();
	}

	// �Ķ���� ������ ������ �����Ѵ�.
	pclchar->ParametaBoxAction();

	// ����ڿ��Դ� ActiveWeapon�� �ٲ���ٴ°��� �˷��ش�.
	cltGameMsgResponse_ExchageWeapon clinfo(pclchar->ActiveWeapon);
	cltMsg clMsg(GAMEMSG_RESPONSE_EXCHANGEWEAPON, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);


	//----------------------------------------------
	// �̿��鿡�Ե� �˸���. 
	//----------------------------------------------
	pclchar->SendNeighbourMyShapeStatus();
	pclchar->CheckCurrentMagic( siPrevActiveWeapon );
}


// clothes 1,2 Activate���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_EXCHANGECLOTHES(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->CR[id]->ActiveClothes == PERSONITEM_ARMOUR)
	{
		pclCM->CR[id]->ActiveClothes = PERSONITEM_DRESS;
		pclCM->CR[id]->ActiveHat     = PERSONITEM_HAT;

	}
	else
	{
		pclCM->CR[id]->ActiveClothes = PERSONITEM_ARMOUR;
		pclCM->CR[id]->ActiveHat     = PERSONITEM_HELMET;

	}



	// ����ڿ��Դ� ActiveClothes�� �ٲ���ٴ°��� �˷��ش�.
	cltGameMsgResponse_ExchageClothes clinfo(pclCM->CR[id]->ActiveClothes,pclCM->CR[id]->ActiveHat);
	cltMsg clMsg(GAMEMSG_RESPONSE_EXCHANGECLOTHES, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


	//----------------------------------------------
	// �̿��鿡�Ե� �˸���. 
	//----------------------------------------------
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();

}

// ���� ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Enchant* pclinfo = (cltGameMsgRequest_Enchant*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// ������ ���� ����.  - �������� ������� �ʴ´�.
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->SendDBWasteDurability();
	pclchar->SendDBSummonWasteDurability();

	//----------------------
	// fromitem Ȯ��. 
	//----------------------
	SI32 frompos		= pclinfo->siFromPos;
	SI32 fromitemunique	=  pclinfo->siFromItemUnique; 
	if(frompos < 0 || frompos >= MAX_ITEM_PER_PERSON)return ;
	// ������ �ش� �������� �ִ��� Ȯ��. 
	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[frompos];
	if(pclitem->siUnique != fromitemunique)return ;


	//----------------------
	// toitem Ȯ��. 
	//----------------------
	SI32 topos	= pclinfo->siToPos;
	if(topos < 0 || topos >= MAX_ITEM_PER_PERSON)return ;
	pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[topos];

	if(pclitem->IsSame(&pclinfo->clToItem, false) == FALSE)
	{
		return ;
	}

	/*	if ( pclitem->siUnique == 9400 || pclitem->siUnique == 9410 || pclitem->siUnique == 13330 ||
	pclitem->siUnique == 13340 || pclitem->siUnique == 13350 || pclitem->siUnique == 13360 )
	{
	if ( pclitem->clItemArmour.uiSkillUp == 1 )
	pclitem->clItemArmour.uiSkillUp = 2 ;
	}*/

	//---------------------------------
	// From�������� �������� Ȯ���Ѵ�. 
	//---------------------------------
	GMONEY atb = pclItemManager->GetItemAtb(fromitemunique);
	if((atb & ITEMATB_SCROLL) ==0) return ;


	//-------------------------------
	// ToItem �� Obj���� Ȯ���Ѵ�. 
	//-------------------------------
	GMONEY toitematb = pclItemManager->GetItemAtb(pclinfo->clToItem.siUnique);
	if((toitematb & ITEMATB_OBJECT) ==0) return ;


	//-------------------------------
	// �ش� ������ ToItem�� ������ �ִ��� �˻��Ѵ�.
	//-------------------------------
	if(pclItemManager->CanItemAttach(fromitemunique, pclinfo->clToItem.siUnique) == FALSE)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(0, SRVAL_ENCHANTFAILNOTATBMATCH, 0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}


	//------------------------------------------
	// ������ ����Ͽ� ����� ������ ����Ų��.
	//------------------------------------------
	cltItem clitem;
	clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[topos]);

	SI32 enchantrrtn	= 0;
	SI32 para1			= 0;
	SI32 para2			= 0;
	if(pclItemManager->Enchant(&clitem, fromitemunique, &enchantrrtn, &para1 , &para2) == false)
	{
		// ���̻� ���� �Ұ�. 
		if(enchantrrtn == ENCHANT_FAIL_REASON_NOMORE)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, SRVAL_ENCHANTFAILTOOMUCH,  para1/10, para2, pclCM->CR[id]->GetCharUnique());
		}
		else if(enchantrrtn == ENCHANT_FAIL_REASON_NOTATBMATCH) 
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, SRVAL_ENCHANTFAILNOTATBMATCH,  para1/10, para2, pclCM->CR[id]->GetCharUnique());
		}
		else if(enchantrrtn == ENCHANT_FAIL_REASON_NOMOREKIND) 
		{	
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, SRVAL_ENCHANTFAILTOOMUCHKIND,  para1/10, para2, pclCM->CR[id]->GetCharUnique());
		}

		return ;
	}

	//--------------------------------------------------------------
	// ����� ���� ������ ���� ������ ��� DB�� ������ �����Ѵ�. 
	//--------------------------------------------------------------
	sDBRequest_Enchant clMsg(id, personid, frompos, fromitemunique, topos, &clitem);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	// ������ ��� ��踦 ������Ʈ �Ѵ�. 
	pclItemManager->AddUseNum(fromitemunique, 1);

	// ���ο� ��� - ������ ���
	//NStatistics_Add("Item", fromitemunique, "UseNum", 1);

}

// �κ����� ��ǰ�� ���鵵�� �ϴ� �Լ�. 
void cltServer::MakeItemProcess(SI32 id, cltGameMsgRequest_MakeItemInv* pclinfo)
{
	if(pclCM->IsValidID(id) == false)			return;
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}
	// ���� �Ƿ��ڰ� �����Ǿ� �ִµ� ��ȿ���� �ʴٸ� ����. 
	if(pclinfo->siMaterialCharUnique)
	{
		if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == false)
		{
			pclCM->CR[id]->siPersonalMakeItemType = 0;
			// true, false�� �����ش�.
			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		
		
			return ;
		}
	}

	SI32 returnval		= 0;
	SI32 preturnpara1	= 0;
	if(((cltCharServer *)pclCM->CR[id])->CanMakeItem(pclinfo, &returnval, &preturnpara1) == false)
	{
		if(returnval)
		{
			pclCM->CR[id]->siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

			if(pclinfo->siMaterialCharUnique > 0  )	// ���� �Ƿ��ڰ� ������ ���� �Ƿ��� ���� �˷��ش� .
			{

				if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == TRUE)
				{
					if ( pclinfo->siMaterialCharUnique != id ) 
					{
						cltCharServer* pclcharserver = pclCM->GetCharServer(id)	;
						if(pclcharserver	!=NULL )
						{
							SendServerResponseMsg(0, returnval, preturnpara1, 0, pclinfo->siMaterialCharUnique);								
							SendServerResponseMsg(0, returnval, preturnpara1, 0, id);				
						}					
					}
					else
					{
						SendServerResponseMsg(0, returnval, preturnpara1, 0, id);
					}
				}
				else
				{
					SendServerResponseMsg(0, returnval, preturnpara1, 0, id);
				}
			}
			else
			{
				SendServerResponseMsg(0, returnval, preturnpara1, 0, id);
			}

		}
		return;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->siItemUnique);
	if(ref <= 0)
	{

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

		return ;
	}

	//--------------------------------------------
	// ������ ���� ������ �������� ������ �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();		
	
		return ;
	}

	if(pclinfo->siItemUnique <= 0)	
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0; 

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();		

		return ;
	}
	if(pclinfo->siItemNum <= 0)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();		

		return ;
	}

	cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice(pclItemManager, pclinfo->siItemUnique);
	if(pclprice == NULL)	
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();		

		return ;
	}


	// �ð��� ����Ѵ�.
	SI32 productclock = 0;

	// NPC������� ������ 60��
	if( pclinfo->bNPCMake )
	{
		productclock = 60000;
	}
	else
	{
		SI32 skillunique	= pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
		SI32 siGetType		= pclItemManager->pclItemInfo[ref]->siType;

		if ( pclClient->IsCountrySwitch(Switch_MakeFoodHealEXP) && ((ITEMTYPE_FOOD == siGetType) || ((ITEMTYPE_HEAL == siGetType))) )
		{
			productclock = CalcTime_MakeItem_FoodHeal( pclchar, skillunique, pclinfo->siItemUnique, pclinfo->siItemNum );
		}
		else if ( pclClient->IsCountrySwitch(Switch_MakeItemEXP) )
		{
			productclock = CalcTime_MakeItem_New( pclchar, skillunique, pclinfo->siItemUnique, pclinfo->siItemNum );
		}
		else
		{
			productclock = CalcTime_MakeItem( pclchar, skillunique, pclinfo->siItemUnique, pclinfo->siItemNum, pclprice->siPrice );
		}
	}

	//-----------------------------------------
	// ��ȣ���� Ư���ɷ¿� ���� �����ð� ����
	//-----------------------------------------
	if ( (false == pclinfo->bNPCMake) && (IsCountrySwitch(Switch_SoulGuard)) )
	{
		SI32 siMoreThanValue	= max( 0, ((productclock/1000)-1) );
		SI32 siSetClock			= pclchar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_MAKETIME_SHORT, 0, siMoreThanValue );
		if ( 0 < siSetClock )
		{
			// 1�� �������� ���� �����Ƿ� 1000�� �����ش�
			productclock = (siSetClock * 1000);
		}
	}


	// ��� ��� �߰� - ���� �ð� ����
	if( pclchar->bMakeTimeReduce )
	{
		productclock = 1000;	// ������ 1��
	}


/*	else if(pclItemManager->GetItemAtb(pclinfo->siItemUnique) & ITEMATB_OBJECT)
	{
		//  ��������
		//	productclock = min(60000, max(10000,  pclprice->siPrice / 10) );


		SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

		//������ ���� �ʿ� ������ ���� ����� ���Ѵ�.
		SI32 skillRankLimit = ( skillLevelLimit/6 ) + 1;
		if( skillRankLimit > 16 )	skillRankLimit = 15;

		//������ �ʿ䷹�� ��޿� ���� ���۽ð��� ���Ѵ�.
		if( skillRankLimit <= 1 )		productclock = 10000;
		else if (skillRankLimit == 2)	productclock = 15000;
		else if (skillRankLimit == 3)	productclock = 20000;
		else if (skillRankLimit == 4)	productclock = 30000;
		else if (skillRankLimit == 5)	productclock = 45000;
		else if (skillRankLimit == 6)	productclock = 55000;
		else if (skillRankLimit > 6)	productclock = 60000;

		SI32 skillunique = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

		// �ش� ����� ���� ������ ���Ѵ�. 
		SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclchar->pclCI->clCharItem.clItem);
		// ��ų ����� ���Ѵ�
		SI32 skillRank = ( skilllevel/6 ) + 1;
		skillRank = max( 15, skillRank );

		// ��޿� ���� ���۽ð� ����
		if ( skillRank  <= 2 )	{}
		else productclock -= ( skillRank - 2) * 1000;

		productclock = max( 10000, productclock );
	}
	else
	{
		GMONEY data = max(100,  pclprice->siPrice) * pclinfo->siItemNum * 5 / 10;

		productclock = (SI32)(max(10000, min(300000, data) ));
	}*/

	//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id] ;

	//------------------------------------------
	// ���꿡 �ʿ��� ������ �����Ѵ�. 
	//------------------------------------------

	// NPC������ ��� ���� �ʿ����!

	if ( pclinfo->bNPCMake == false )
	{
		DBToolInfo clToolInfo[MAX_TOOL_NUMBER] ;

		SI32 toolindex = 0;

		for(SI32 i = 0;i < MAX_TOOL_NUMBER;i++)
		{
			clToolInfo[i].Init() ;

			SI32 toolunique = pclItemManager->pclItemInfo[ref]->clProductionInfo.clTool[i].siUnique;
			if(toolunique <= 0)continue;

			bool alreadydealswitch = false;
			bool bSealingupFail = false;

			//KHY - 1211 - ���ݻ�ǰ - ���� ����
			if(returnval == SRVAL_RETURN_USE_ALLPURPOSETOOL)
				alreadydealswitch = true;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for(SI32 j = 0;j < MAX_INVITEM_PER_PERSON;j++)
			{
				// �̹� �ʿ��� ������ ã�Ҵٸ� , 
				if(alreadydealswitch)break;

				if(pclchar->pclCI->clCharItem.clItem[PERSONITEM_INV0 + j].siUnique == toolunique)
				{
					// �к����¸� �� ����.
					if ( pclchar->pclCI->clCharItem.clItem[PERSONITEM_INV0 + j].IsSealingUp(pclItemManager) == true )
					{
						bSealingupFail = true;
						continue;					
					}

					bSealingupFail = false;

					clToolInfo[i].siPos	= PERSONITEM_INV0 + j;
					clToolInfo[i].clItem.Set(&pclchar->pclCI->clCharItem.clItem[clToolInfo[i].siPos]);

					/* �Ⱓ���� ����
					// �������� �Ҹ��Ų��.(�ʿ��� �������� ����Ǵ� ������ �ü��� ���� �޶�����.) 
					SI32 requiretooldur = min(100, max(10, (pclprice->siPrice * pclinfo->siItemNum) / 100000));

					if(clToolInfo[i].clItem.GetDurability() > requiretooldur)
					{
					clToolInfo[i].clItem.DecreaseDurability(pclItemManager, requiretooldur);

					// �������� ��� ������ ���� ����ũ�� ����� �Ѵ�. �׷��� DB���� 
					clToolInfo[i].clItem.siUnique	= pclchar->pclCI->clCharItem.clItem[clToolInfo[i].siPos].siUnique;
					}
					else
					{
					SendServerResponseMsg(0, SRVAL_NOTENOUGHTOOLDURABILITY, toolunique, requiretooldur, id);
					return ;
					}
					*/

					toolindex++;

					alreadydealswitch = true;
				}
			}
			if(bSealingupFail)
			{
				SendServerResponseMsg(0, SRVAL_NOTENOUGHTOOLDURABILITY, toolunique, 0, id);

				// true, false�� �����ش�.

				pclCM->CR[id]->siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();		


				return ;
			}
		}

		//������  - ���� ����.
		/*for ( i = 0 ; i < MAX_TOOL_NUMBER ; i ++ )
		{
			if ( clToolInfo[i].clItem.siUnique )
			{
				if( clToolInfo[i].siPos >= 0 && clToolInfo[i].siPos < MAX_ITEM_PER_PERSON )
				{
					pclchar->pclCI->clCharItem.clItem[clToolInfo[i].siPos].Set(&clToolInfo[i].clItem) ;
					pclchar->SetWasteDurUpdateSwitch(clToolInfo[i].siPos, true);

					cltGameMsgResponse_PersonItemInfo clinfo(clToolInfo[i].siPos, PERSONITEMINFO_OPTION_TOOLWASTE, 0, 0, &clToolInfo[i].clItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
		*/
	}

	pclchar->SendDBWasteDurability() ;
	pclchar->SendDBSummonWasteDurability();

	// ĳ���Ϳ��� ���� �޽����� �ð��� �����Ѵ�.
	pclchar->SetReserverMakeItem((DWORD)productclock, pclinfo);

	//-------------------------------------------
	// Ŭ���̾�Ʈ�� ���� �ð��� �뺸�Ѵ�. 
	//-------------------------------------------
	cltGameMsgResponse_MakeItemDelay clinfo((DWORD)productclock);
	cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMDELAY, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	// �̴ϰ����� �� ������ �� ������ �˻��Ѵ�.
	if(pclItemManager->pclItemInfo[ref]->IsSkill_Maked() == true && pclinfo->bNPCMake == false )
	{
		cltGameMsgResponse_IsSkillItem clinfo(1);
		cltMsg clMsg(GAMEMSG_RESPONSE_ISSKILLITEM, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		pclchar->bMakeItemNoMinigame = false ;
		pclchar->bMakeItemMinigameSwitch = false ;
	}
	else
	{
		pclchar->bMakeItemNoMinigame = true ;
		pclchar->bMakeItemMinigameSwitch = false ;
	}
	cltServer* pclserver			= (cltServer*)pclClient;
	
	pclchar->siMonsterCorp = 0 ;
	pclchar->dwStartMiniGameTime = CurrentClock;

	pclchar->bMakeItemSwitch = false ;
}

SI32 cltServer::CalcExp_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice )
{
	SI32 exp = 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);

	// �ش� ����� ���� ������ ���Ѵ�. 
	SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	// ���� ������ �ش��ϴ� ����� ���Ѵ�.
	SI32 skillrank = (skilllevel/6) + 1;
	if( skillrank > 16 )	skillrank = 15;

	SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

	// ���� �Ϸ��� �������� ����� ���Ѵ�.
	SI32 skillRankLimit = ( skillLevelLimit/6 ) + 1;
	if( skillRankLimit > 16 )	skillRankLimit = 15;

	// �����۰� ���� ������� ���� �г�Ƽ ��� ( ����, ���� ����ġ ���� )
	SI32 siskillgap = skillrank - skillRankLimit;
	SI32 siPenalty = 120;
	if ( siskillgap == 1)		siPenalty = 100;
	else if (siskillgap == 2 )	siPenalty = 80;
	else if (siskillgap == 3 )	siPenalty = 20;
	else if (siskillgap == 4 )	siPenalty = 10;
	else if (siskillgap == 5 )	siPenalty = 5;
	else if (siskillgap >= 5 )	siPenalty = 2;

	// �ش� ����� å���� ���� ��ų����
	SI32 skilllevlbybook = pclchar->pclCI->clCharSkill.GetSkillLevel(skillunique);
	// å���� ���� ������濡 ���� �г�Ƽ
	SI32 siPenalty2 = (100 - ( 30 - skilllevlbybook )*3 );

	//--------------------------------------
	// ����ġ�� �����ش�. 
	//--------------------------------------
	if ( (pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT) )
	{
		// �⺻ ����ġ�� ���Ѵ� - ���� ��޿� ���� Ʋ������.
		switch( skillrank )
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:			exp = 450;	break;
		case 6:			exp = 550;	break;
		case 7:			exp = 600;	break;
		case 8:			exp = 600;	break;
		case 9:			exp = 600;	break;
		case 10:		exp = 600;	break;
		case 11:		exp = 600;	break;
		case 12:		exp = 600;	break;
		case 13:		exp = 650;	break;
		case 14:		exp = 700;	break;
		case 15:		exp = 700;	break;
		default:		exp = 0;
		}

		// �г�Ƽ ���
		exp = ( exp * siPenalty * siPenalty2 ) / 10000;

	}
	else
	{
		// ���� ����ġ ���� ���� (������Ʈ�� �ƴҰ��)
		exp	= pclItemManager->GetMakeExpFromItemPrice(siPrice * siNum, pclchar->pclCI->clIP.GetLevel()); 
	}

	return exp;
}

SI32 cltServer::CalcSkillExp_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice )
{
	SI32 skillexp = 0;

	SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);

	// ���� ������ �ش��ϴ� ����� ���Ѵ�.
	SI32 skillrank = (skilllevel/6) + 1;
	if( skillrank > 16 )	skillrank = 15;

	SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

	// ���� �Ϸ��� �������� ����� ���Ѵ�.
	SI32 skillRankLimit = ( skillLevelLimit/6 ) + 1;
	if( skillRankLimit > 16 )	skillRankLimit = 15;

	// �����۰� ���� ������� ���� �г�Ƽ ��� ( ����, ���� ����ġ ���� )
	SI32 siskillgap = skillrank - skillRankLimit;
	SI32 siPenalty = 120;
	if ( siskillgap == 1)		siPenalty = 100;
	else if (siskillgap == 2 )	siPenalty = 80;
	else if (siskillgap == 3 )	siPenalty = 20;
	else if (siskillgap == 4 )	siPenalty = 10;
	else if (siskillgap == 5 )	siPenalty = 5;
	else if (siskillgap >= 5 )	siPenalty = 2;

	// �ش� ����� å���� ���� ��ų����
	SI32 skilllevlbybook = pclchar->pclCI->clCharSkill.GetSkillLevel(skillunique);
	// å���� ���� ������濡 ���� �г�Ƽ
	SI32 siPenalty2 = (100 - ( 30 - skilllevlbybook )*3 );

	// ��޿� ���� �⺻ ����ġ
	if ((pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT) )
	{
		skillexp = 230;
		if ( skillrank > 5 )
		{
			skillexp = 40;
			for ( SI16 i = 1 ; i < skillrank ; i++)
				skillexp += ( i + 2 )* 10;
		}

		// �г�Ƽ ���
		skillexp = ( skillexp * siPenalty * siPenalty2 ) / 10000;
	}
	else
	{
		// ���� ��� ����ġ ����, ������Ʈ�� �ƴҰ��, �Ϻ����ϰ��
		skillexp = pclItemManager->GetMakeSkillExpFromItemPrice(siPrice * siNum, skilllevel); 
	}

	return skillexp;
}

SI32 cltServer::CalcExp_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum )
{
	static REAL32 fStaticBaseExp = 35.0f;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);

	SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	SI32 exp = 0;
	SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;
	REAL32 fPenalty = 0.0f;

	if ( (pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT) )
	{
		exp = fStaticBaseExp * (2.0f + ((skillLevelLimit*skillLevelLimit) * 5.0f / 1000.0f));

		fPenalty = 100.0f - (((skilllevel*10.0f - skillLevelLimit*10.0f)*(skilllevel*10.0f - skillLevelLimit*10.0f)) / 800.0f) ;
		if(fPenalty <= 5.0f)		fPenalty = 5.0f;

		exp = (FLOAT)exp * (fPenalty / 100.0f);
	}
	else
	{
		exp = (fStaticBaseExp * (2.0f + ((skillLevelLimit*skillLevelLimit) * 5.0f / 1000.0f))) * siNum;
		exp = (FLOAT)exp / 500.0f;
	}

	return exp;
}

SI32 cltServer::CalcSkillExp_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum )
{
	SI32 skillexp = 0;

	static REAL32 fStaticBaseExp = 35.0f;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);

	SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;
	REAL32 fPenalty = 0.0f;

	SI32 siItemType = pclItemManager->GetItemType(siItemUnique);
	// ����ü�� OBJECT�� ���� ������ ������.
	if( siItemType == ITEMTYPE_CRYSTAL )
	{
		skillexp = fStaticBaseExp * (1.0f + ((skillLevelLimit*skillLevelLimit) * 5.0f / 1000.0f));

		fPenalty = 100.0f - (((skilllevel*10.0f - skillLevelLimit*10.0f)*(skilllevel*10.0f - skillLevelLimit*10.0f)) / 800.0f) ;
		if(fPenalty <= 5.0f)		fPenalty = 5.0f;

		skillexp = skillexp * (fPenalty / 100.0f);

		skillexp = skillexp * siNum;
		skillexp = skillexp * 0.8;		// ����ġ�� ����Ѵ�.
	}
	else
	{
		// ����ü�� �ƴ� �������� OBJECT�� ���ο� ���� ����ġ�� ����Ѵ�.
		if ( (pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT) )
		{
			skillexp = fStaticBaseExp * (1.0f + ((skillLevelLimit*skillLevelLimit) * 5.0f / 1000.0f));

			fPenalty = 100.0f - (((skilllevel*10.0f - skillLevelLimit*10.0f)*(skilllevel*10.0f - skillLevelLimit*10.0f)) / 800.0f) ;
			if(fPenalty <= 5.0f)		fPenalty = 5.0f;

			skillexp = skillexp * (fPenalty / 100.0f);
		}
		else
		{
			skillexp = (fStaticBaseExp * (1.0f + ((skillLevelLimit*skillLevelLimit) * 5.0f / 1000.0f))) * siNum;
			skillexp = (FLOAT)skillexp / 500.0f;
		}
	}

	return skillexp;
}

SI32 cltServer::CalcExp_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum )
{
	const static REAL32 fBaseExp = 20.0f;

	SI32	siReturnSkillExp	= 0;

	SI32	ref					= pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= ref )
	{
		return 0;
	}

	SI32	siCharLevel			= pclchar->pclCI->clIP.GetLevel();
	SI32	siSkillExpLevel		= pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );
	SI32	siSkillBookLevel	= pclchar->pclCI->clCharSkill.GetSkillLevel( siSkillUnique );
	SI32	siSkillLevelLimit	= pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

	SI32	siPenalty			= (SI32)(((REAL32)siSkillLevelLimit / (REAL32)max(1, (siSkillExpLevel+siSkillBookLevel))) * 100.0f);


	siReturnSkillExp	= (SI32)(fBaseExp * (2.0f + ((siSkillLevelLimit*siSkillLevelLimit) * 5.0f / 1000.0f))) * siNum;
	siReturnSkillExp	= (SI32)(((REAL32)siReturnSkillExp * (REAL32)siPenalty) / 100.0f);

	siReturnSkillExp	= min( (siCharLevel*20), siReturnSkillExp );


	return siReturnSkillExp;


}

SI32 cltServer::CalcSkillExp_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum )
{
	const static REAL32 fBaseExp = 20.0f;

	SI32	siReturnSkillExp	= 0;

	SI32	ref					= pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= ref )
	{
		return 0;
	}

	SI32	siCharLevel			= pclchar->pclCI->clIP.GetLevel();
	SI32	siSkillExpLevel		= pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );
	SI32	siSkillBookLevel	= pclchar->pclCI->clCharSkill.GetSkillLevel( siSkillUnique );
	SI32	siSkillLevelLimit	= pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;
	
	SI32	siPenalty			= (SI32)(((REAL32)siSkillLevelLimit / (REAL32)max(1, (siSkillExpLevel+siSkillBookLevel))) * 100.0f);
	

	siReturnSkillExp	= (SI32)(fBaseExp * (1.0f + ((siSkillLevelLimit*siSkillLevelLimit) * 5.0f / 1000.0f))) * siNum;
	siReturnSkillExp	= (SI32)(((REAL32)siReturnSkillExp * (REAL32)siPenalty) / 100.0f);

	siReturnSkillExp	= min( (siCharLevel*20), siReturnSkillExp );


	return siReturnSkillExp;

}

SI32 cltServer::CalcTime_MakeItem( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum, SI64 siPrice )
{
	SI32 productclock = 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);

	if(pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT)
	{
		SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

		//������ ���� �ʿ� ������ ���� ����� ���Ѵ�.
		SI32 skillRankLimit = ( skillLevelLimit/6 ) + 1;
		if( skillRankLimit > 16 )	skillRankLimit = 15;

		//������ �ʿ䷹�� ��޿� ���� ���۽ð��� ���Ѵ�.
		if( skillRankLimit <= 1 )		productclock = 10000;
		else if (skillRankLimit == 2)	productclock = 15000;
		else if (skillRankLimit == 3)	productclock = 20000;
		else if (skillRankLimit == 4)	productclock = 30000;
		else if (skillRankLimit == 5)	productclock = 45000;
		else if (skillRankLimit == 6)	productclock = 55000;
		else if (skillRankLimit > 6)	productclock = 60000;

		SI32 skillunique = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;

		// �ش� ����� ���� ������ ���Ѵ�. 
		SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);
		// ��ų ����� ���Ѵ�
		SI32 skillRank = ( skilllevel/6 ) + 1;
		skillRank = max( 15, skillRank );

		// ��޿� ���� ���۽ð� ����
		if ( skillRank  <= 2 )	{}
		else productclock -= ( skillRank - 2) * 1000;

		productclock = max( 10000, productclock );
	}
	else
	{
		GMONEY data = max(100,  siPrice) * siNum * 5 / 10;

		productclock = (SI32)(max(10000, min(300000, data) ));
	}

	return productclock;
}

SI32 cltServer::CalcTime_MakeItem_New( cltCharServer* pclchar, SI32 skillunique, SI32 siItemUnique, SI32 siNum )
{
	SI32 productclock = 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);
	SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;
	// �ش� ����� ���� ������ ���Ѵ�. 
	SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	if(pclItemManager->GetItemAtb(siItemUnique) & ITEMATB_OBJECT)
	{
		productclock = (skillLevelLimit * 5.0f) - (skilllevel * 1.0f);
		productclock = max( 10, productclock );
	}
	else
	{
		productclock = ((skillLevelLimit * 100.0f) * ( siNum / 50.0f)) / 1000.0f;

		productclock = max( 10, productclock );
	}

	return productclock * 1000;
}

// [����][����ġ] ����,�� ���� �����ð� ��� �Լ�
SI32 cltServer::CalcTime_MakeItem_FoodHeal( cltCharServer* pclchar, SI32 siSkillUnique, SI32 siItemUnique, SI32 siNum )
{
	SI32 siProductClock = 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( 0 >= ref )
	{
		return 0;
	}

	SI32 siSkillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

	siProductClock = ((siSkillLevelLimit * 100.0f) * ( siNum / 50.0f)) / 1000.0f;
	siProductClock = max( 10, siProductClock );
	siProductClock = min( 300, siProductClock );

	return (siProductClock * 1000); // millisecond�� ��ȯ
}

// �κ����� ��ǰ�� ���鵵�� �ϴ� �Լ�. 
void cltServer::EnchantItemProcess(SI32 id, cltGameMsgRequest_MakeItemInv* pclinfo)
{
	if(bEnchantSwitch == false) return;
	// ���� �Ƿ��ڰ� �����Ǿ� �ִµ� ��ȿ���� �ʴٸ� ����. 
	if(pclinfo->siMaterialCharUnique)
	{
		if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == false)
		{
			// true, false�� �����ش�.

			pclCM->CR[id]->siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

			return ;
		}
	}

	SI32 returnval		= 0;
	SI32 preturnpara1	= 0;
	if(((cltCharServer *)pclCM->CR[id])->CanEnchantItem(pclinfo, &returnval, &preturnpara1) == false)
	{
		if(returnval)
		{
			// true, false�� �����ش�.

			pclCM->CR[id]->siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, returnval, preturnpara1, 0, id);
		}
		return;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->siItemUnique);
	if(ref <= 0)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		return ;
	}

	//--------------------------------------------
	// ������ ���� ������ �������� ������ �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		return ;
	}

	if(pclinfo->siItemUnique <= 0)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		return ;
	}

	if(pclinfo->siItemNum <= 0)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		return ;
	}

	cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice(pclItemManager, pclinfo->siItemUnique);
	if(pclprice == NULL)
	{
		// true, false�� �����ش�.

		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		((cltServer *)pclClient)->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
		return ;
	}


	// �ð��� ����Ѵ�.
	DWORD productclock;

	if(pclItemManager->GetItemAtb(pclinfo->siItemUnique) & ITEMATB_OBJECT)
	{
		//productclock = min(60000, max(10000,  pclprice->siPrice / 10) );
		productclock =10000;
	}
	else
	{
		GMONEY data = max(100,  pclprice->siPrice) * pclinfo->siItemNum * 5 / 10;

		//productclock = max(10000, min(300000, data) );
		productclock =10000;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id] ;

	//------------------------------------------
	// ���꿡 �ʿ��� ������ �����Ѵ�. 
	//------------------------------------------

	/*

	DBToolInfo clToolInfo[MAX_TOOL_NUMBER] ;

	SI32 toolindex = 0;

	for(SI32 i = 0;i < MAX_TOOL_NUMBER;i++)
	{
	clToolInfo[i].Init() ;

	SI32 toolunique = pclItemManager->pclItemInfo[ref]->clProductionInfo.clTool[i].siUnique;
	if(toolunique <= 0)continue;

	bool alreadydealswitch = false;


	//���⿩��
	// �κ����� �ش� ��Ḧ ã�´�. 
	for(SI32 j = 0;j < MAX_INVITEM_PER_PERSON;j++)
	{
	// �̹� �ʿ��� ������ ã�Ҵٸ� , 
	if(alreadydealswitch)continue;

	if(pclchar->pclCI->clCharItem.clItem[PERSONITEM_INV0 + j].siUnique == toolunique)
	{
	// �к����¸� �� ����.
	if ( pclchar->pclCI->clCharItem.clItem[PERSONITEM_INV0 + j].IsSealingUp(pclItemManager) == true )
	{
	SendServerResponseMsg(0, SRVAL_NOTENOUGHTOOLDURABILITY, toolunique, 0, id);
	return ;
	}
	// ��ǰ�̸� �� ����.
	if ( pclItemManager->CheckNotGoodItem(&pclchar->pclCI->clCharItem.clItem[PERSONITEM_INV0 + j]) == false )
	{
	SendServerResponseMsg(0, SRVAL_NOTGOODTOOL, toolunique, 0, id);
	return ;
	}

	clToolInfo[i].siPos	= PERSONITEM_INV0 + j;
	clToolInfo[i].clItem.Set(&pclchar->pclCI->clCharItem.clItem[clToolInfo[i].siPos]);


	toolindex++;

	alreadydealswitch = true;
	}
	}
	}

	for ( i = 0 ; i < MAX_TOOL_NUMBER ; i ++ )
	{
	if ( clToolInfo[i].clItem.siUnique )
	{
	pclchar->pclCI->clCharItem.clItem[clToolInfo[i].siPos].Set(&clToolInfo[i].clItem) ;
	pclchar->SetWasteDurUpdateSwitch(clToolInfo[i].siPos, true);

	cltGameMsgResponse_PersonItemInfo clinfo(clToolInfo[i].siPos, PERSONITEMINFO_OPTION_TOOLWASTE, 0, 0, &clToolInfo[i].clItem, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (char*)&clinfo);
	pclchar->SendNetMsg((char*)&clMsg);
	}
	}

	*/
	pclchar->SendDBWasteDurability();
	pclchar->SendDBSummonWasteDurability();


	// ĳ���Ϳ��� ���� �޽����� �ð��� �����Ѵ�.
	pclchar->SetReserverMakeItem(productclock, pclinfo);

	//-------------------------------------------
	// Ŭ���̾�Ʈ�� ���� �ð��� �뺸�Ѵ�. 
	//-------------------------------------------
	cltGameMsgResponse_MakeItemDelay clinfo(productclock);
	cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMDELAY, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);


	pclchar->bEnchantItemSwitch = true ;  //��æƮ�� �̴ϰ����� ���� �ʴ´� .


	pclchar->siMonsterCorp = 0 ;
	pclchar->dwStartMiniGameTime = 0;
	pclchar->bFinishEnchantItemSwitch = false ;
}

// �κ����� �������� ���� ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_MAKEITEMINV(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id) == false)
		return;

	cltGameMsgRequest_MakeItemInv* pclinfo = (cltGameMsgRequest_MakeItemInv*)pclMsg->cData;

	if( false == pclEventTimeManager->InEventTime(TEXT("Chuseok_Monster_Appear"), &sTime) )
	{
		// [����] �߼� �̺�Ʈ. �����䳢 ����=> 2008-8-12
		if(	pclinfo->siItemUnique == ITEMUNIQUE(23496) ||
			pclinfo->siItemUnique == ITEMUNIQUE(13047) || 
			pclinfo->siItemUnique == ITEMUNIQUE(13048) ||
			pclinfo->siItemUnique == ITEMUNIQUE(23114)	)	
		{
			SendServerResponseMsg( 0, SRVAL_EVENTDAY_OVER_NOT_MAKE_ITEM, ITEMUNIQUE(pclinfo->siItemUnique), 0, pclCM->CR[id]->GetID() );
			return;
		}
	}

	if( false == bEventToggleSwitch[EVENT_TOGGLE_SWITCH_FISHINGEVENT] )
	{
		// [����] ���� �̺�Ʈ �Ⱓ ������ ȭ�ݳ��ô븦 ������ ���ϰ� => 2008-9-5
		if(pclinfo->siItemUnique == ITEMUNIQUE(17160))	
		{
			SendServerResponseMsg( 0, SRVAL_EVENTDAY_OVER_NOT_MAKE_ITEM, ITEMUNIQUE(17160), 0, pclCM->CR[id]->GetID() );
			return;
		}
	}

	pclCM->CR[id]->siPersonalMakeItemType = pclinfo->siType;

	cltGameMsgResponse_MakeItemSwitch clinfo( pclinfo->siType );
	cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//----------------------------------------------
	// �̿��鿡�Ե� �˸���. 
	//----------------------------------------------
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

	MakeItemProcess(id, pclinfo);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMCHANGE(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->CR[id]->siPersonalMakeItemType > 0) return; //������ ������ �̵� �ȵȴ�.
	if( pclCM->CR[id]->bPersonalEnchantItemSwitch == true) return; 
	if(pclCM->CR[id]->pclCI->GetPersonID() <= 0 ) return; // ����Ǿ��� �߸��� �Ŵ�.

	// ������ �̵� ������ Ȯ���Ѵ�. 
	cltMoveItemInfo* pclmoveiteminfo = (cltMoveItemInfo*)pclMsg->cData;

	cltItem* pclFrom = NULL;
	cltItem  clTo;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();


	SI32 slot = -1;

	// �������� �����͸� Ȯ���Ѵ�. 
	if(pclmoveiteminfo->uiTo < 0	|| pclmoveiteminfo->uiTo >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMCHANGE - PersonID = %d, IP =  %s , uiTo = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclmoveiteminfo->uiTo
																	);
		return ;
	}	
	if(pclmoveiteminfo->uiFrom < 0	|| pclmoveiteminfo->uiFrom >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMCHANGE - PersonID = %d, IP =  %s , uiFrom = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclmoveiteminfo->uiFrom
																	);
		return ;
	}	

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �̵� �ȵȴ�.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclmoveiteminfo->uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclmoveiteminfo->uiFrom	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			// �ͼ����� ���λ���
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclmoveiteminfo->uiFrom	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			// �ͼ����� ���λ���
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclmoveiteminfo->uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}
	}

	// ������ ���� ����.  - ������ ���� ����.
	if(pclmoveiteminfo->uiTo < PERSONITEM_INV0 || pclmoveiteminfo->uiFrom < PERSONITEM_INV0)
	{
		pclchar->SendDBWasteDurability();
		pclchar->SendDBSummonWasteDurability();
	}


	//------------------------------------------------
	// ���� ���� ���� ������ �� �κ��� ���� ���� ����.
	//------------------------------------------------
	if(pclCM->CR[id]->HaveHorse() == false)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_HORSE0 && pclmoveiteminfo->uiTo < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY)return ;
	}

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	pclFrom		= &pclCM->CR[id]->pclCI->clCharItem.clItem[pclmoveiteminfo->uiFrom];			

	// �������� ��ȿ�� ���̶��..
	if(pclFrom == NULL || pclFrom->siUnique <=0 ||pclFrom->siItemNum <= 0)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		if(pclFrom == NULL )
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMCHANGE - PersonID = %d, IP =  %s , pclFrom = NULL"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP()
																		);
		}
		else
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMCHANGE - PersonID = %d, IP =  %s , siUnique = %d,  siItemNum = %d"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP(),
																		pclFrom->siUnique ,
																		pclFrom->siItemNum											
																		);
		}
		return ;
	}

	//------------------------------------------------
	// ���� �߿��� �������� ������ �� ����.
	//------------------------------------------------
	if( pclCM->CR[id]->clTransFormInfo.bTransFormMode &&
		pclmoveiteminfo->uiTo >= PERSONITEM_HELMET && pclmoveiteminfo->uiTo < PERSONITEM_HELMET + MAX_SHAPE_ITEM )
	{
		//KHY - 0129 - �������̶�, ȭ��� �Ѿ��� ������ ��������
		switch(pclFrom->siUnique)
		{
			case ITEMUNIQUE(7850) : // ȭ��
			case ITEMUNIQUE(7855) : // �Ѿ�
			case ITEMUNIQUE(13600) : // ���� ȭ��.
			case ITEMUNIQUE(13601) : // ���� �Ѿ�.
				break;
			default:
				// �����߿��� �������� ������ �� �����ϴ�.
				return;
		}
	}

	//------------------------------------------------
	// ���� �߿��� �������� ������ ���� �� �� ����.
	//------------------------------------------------
	if( pclCM->CR[id]->clTransFormInfo.bTransFormMode &&
		pclmoveiteminfo->uiFrom >= PERSONITEM_HELMET && pclmoveiteminfo->uiFrom < PERSONITEM_HELMET + MAX_SHAPE_ITEM )
	{
		//KHY - 0129 - �������̶�, ȭ��� �Ѿ��� ������ ��������
		switch(pclFrom->siUnique)
		{
			case ITEMUNIQUE(7850) : // ȭ��
			case ITEMUNIQUE(7855) : // �Ѿ�
			case ITEMUNIQUE(13600) : // ���� ȭ��.
			case ITEMUNIQUE(13601) : // ���� �Ѿ�.
				break;
			default:
				// �����߿��� �������� ������ ������ �� �����ϴ�.
				return;
		}
	}

	// Ʈ���̵����� ���� �ȵȴ�!
	if ( ((cltCharServer*)pclCM->CR[id])->GetNoMoveItemSwitch(pclmoveiteminfo->uiFrom) != 0 )
	{
		return ;
	}

	//----------------------------------------------------
	// ������ ���� ���� ������ ���� �κ��� ���� ���� ����
	//----------------------------------------------------
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique == 0)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_BAG0 && pclmoveiteminfo->uiTo < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG)return ;
	}
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique == 0)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_BAG1 && pclmoveiteminfo->uiTo < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG)return ;
	}

	//----------------------------------------------------
	// ������ ������ ���� �κ����� �ű� ���� ����.
	//----------------------------------------------------
	if ( pclmoveiteminfo->uiFrom == PERSONITEM_BAG )
	{
		if( pclmoveiteminfo->uiTo >= PERSONITEM_BAG0 && pclmoveiteminfo->uiTo < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			return;
		}

		//----------------------------------------------------
		// ���濡 ������ ��ä�� ������ ���� ��ų���� ����.
		//----------------------------------------------------
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				return;
			}
		}
	}

	//----------------------------------------------------
	// ������ ����2�� ����2 �κ����� �ű� ���� ����. 
	//----------------------------------------------------
	if ( pclmoveiteminfo->uiFrom == PERSONITEM_BAG_SUB )
	{
		if( pclmoveiteminfo->uiTo >= PERSONITEM_BAG1 && pclmoveiteminfo->uiTo < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			return;
		}

		//----------------------------------------------------
		// ����2�� ������ ��ä�� ������ ���� ��ų���� ����.
		//----------------------------------------------------
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				return;
			}
		}
	}

	// �������� ���� �����δ� �̵���ų �� ����. 
	if(pclItemManager->CheckProperItemPos(pclFrom, pclmoveiteminfo->uiTo, pclchar->GetKind()) == FALSE)return ;

	//------------------------------------------
	// �к����� �������� �����Ұ� 
	// �Ⱓ�� ���� �������� �����Ұ� - by LEEKH
	//------------------------------------------
	if((pclmoveiteminfo->uiTo >= 0 && pclmoveiteminfo->uiTo<= 14) || pclmoveiteminfo->uiTo == 82 || pclmoveiteminfo->uiTo== 97)	
	{
		if(pclFrom->IsSealingUp(pclItemManager)) return;

		SI32 useableDay;
		BOOL rVal = GetItemUseAbleDay(pclFrom, &useableDay);
		if(rVal == TRUE && useableDay < 0)		return;
	}

	//------------------------------------------
	// ���� ������ ������Ű���� Ȯ���Ѵ�. 
	//------------------------------------------
	SI32 returnval = 0;
	if(pclCM->CR[id]->CheckEquipCondition(pclItemManager, pclmoveiteminfo->uiTo, pclFrom, &returnval) == false)return ;


	// ����ü ũ����Ż ������ ���� ����.  - 
	if( pclmoveiteminfo->uiFrom < PERSONITEM_INV0)
	{
		pclchar->SendDBCrystalDurability();
		pclchar->SendClientCrystalDurability();
	}

	//-----------------------------------------------
	//DB�޴����� �������� �̵��϶�� ��û�� ������. 
	//-----------------------------------------------
	cltItem clFrom;
	clFrom.Set(pclFrom);

	//-----------------------------------------------
	// To �� �ִ´�. 
	//-----------------------------------------------
	clTo.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclmoveiteminfo->uiTo]);

	//cyj �ű�� �������� ������ MAX_ITEM_PILE_NUMBER�� ������ ���� �������� �ٸ� �κ��丮�� �����ϵ���
	if (DistributePileMoveItem(id, clFrom, pclmoveiteminfo->uiFrom, clTo, pclmoveiteminfo->uiTo) == FALSE)
	{
		bool Canpile = false;
		if(( pclFrom->CanPile(pclItemManager))&&( clTo.CanPile(pclItemManager)))
			Canpile = true;
		
		sDBRequest_MoveItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclmoveiteminfo->uiFrom, &clFrom, Canpile,
									pclmoveiteminfo->uiTo, &clTo);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTITEMINV(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id) == false)
		return;

	cltGameMsgRequest_MakeItemInv* pclinfo = (cltGameMsgRequest_MakeItemInv*)pclMsg->cData;

	pclCM->CR[id]->siPersonalMakeItemType = pclinfo->siType;

	cltGameMsgResponse_MakeItemSwitch clinfo( pclinfo->siType );
	cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//----------------------------------------------
	// �̿��鿡�Ե� �˸���. 
	//----------------------------------------------
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();


	EnchantItemProcess(id, pclinfo);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANT_USEDAYPLUS(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->CR[id]->siPersonalMakeItemType > 0) return; //������ ������ �Ⱓ���� �ȵȴ�.
	if( pclCM->CR[id]->bPersonalEnchantItemSwitch == true) return; 

	cltGameMsgRequest_UseDayPlus * pclinfo = (cltGameMsgRequest_UseDayPlus*)pclMsg->cData;
	
	// ���� ��ȿ�� üũ
	if( pclinfo->siItemUnique <= 0 ) return;
	if( pclinfo->siOrgInx < 0  || pclinfo->siOrgInx >= MAX_ITEM_PER_PERSON) return;
	if( pclinfo->siEleInx < 0  || pclinfo->siEleInx >= MAX_ITEM_PER_PERSON) return;

	if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx].siUnique != pclinfo->siItemUnique ) return;
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siEleInx].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE ) return;

	// �Ⱓ ������ �� �� �ִ� ���������� üũ�Ѵ�.
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx].IsPlusUseDate(pclItemManager) == false)
		return;

	// ���ǰ�̸� ������ �ִ� ���������� üũ
	//if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx].clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5   || pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx].uiDateUseDay <= 0 )

	//KHY - 0313 -  ��ȥ�� �� (�Ⱓ ������ ��) ���ó �þ. 
/*	SI32 itemType  = pclItemManager->GetItemType(pclinfo->siItemUnique);

	if((pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx].uiDateUseDay <= 0 )
		||(itemType != ITEMTYPE_HELMET)
		||(itemType != ITEMTYPE_ARMOUR)
		||(itemType != ITEMTYPE_SHOES)
		||(itemType != ITEMTYPE_BELT))
	{		
		return;
	}*/

	// �Ⱓ ���� �������� �ִ��� üũ
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siEleInx].siItemNum <= 0 ) return;


	cltItem clOutput;
	clOutput.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgInx] );
	

	cltItem clMaterial;
	clMaterial.siUnique 	= ENCHANT_USEDAYPLUS_ITEMUNIQUE;
	clMaterial.siItemNum	= 1;
	
	SI32 useableDay = 0;
	BOOL rVal = GetItemUseAbleDay(&clOutput,&useableDay);
	if(rVal == FALSE) return;

	// �Ⱓ�� ���� �������̶�� ���� ���� ������ ��ó�� �����͸� �־��ְ� ���Ⱓ�� 10�Ϸ� �־��ش�.
	if( useableDay < 0 )
	{
		clOutput.uiDateYear = sTime.wYear-2000;
		clOutput.uiDateMonth = sTime.wMonth;
		clOutput.uiDateDay = sTime.wDay;

		clOutput.uiDateUseDay = 10;
	}
	else	// �Ⱓ�� ������ �������̶�� �� + 10 ���ش�
	{
		clOutput.uiDateUseDay += 10;
	}	

	((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclinfo->siOrgInx , pclClient->CurrentClock );
	((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclinfo->siEleInx , pclClient->CurrentClock );

	//KHY - 0723 - �Ⱓ������ �ı� ����.
	if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
	{
		pclClient->sUpViewEffect = 0;
	}

	sDBRequest_EnchantUseDayPlus clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siOrgInx , &clOutput ,pclinfo->siEleInx , &clMaterial );	
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);


}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGEENCHANT(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )					return;	// ID�� ��ȿ���� �˻�
	if ( pclCM->CR[id]->siPersonalMakeItemType > 0)			return; // �������̶�� �ȵȴ�
	if ( pclCM->CR[id]->bPersonalEnchantItemSwitch == true)	return; // ��þƮ���̶�� �ȵȴ�

	cltGameMsgRequest_ChangeEnchant *pclinfo = (cltGameMsgRequest_ChangeEnchant*)pclMsg->cData;
	if ( pclinfo == NULL )									return;

	cltPersonInfo* pclPerson = (cltPersonInfo*)pclCM->CR[id]->pclCI;
	if ( pclPerson == NULL )								return;

	// ��ȿ�� �˻�
	if ( pclinfo->m_siOrgUnique <= 0 )						return;
	if ( pclinfo->m_siOrgIndex < 0  || pclinfo->m_siOrgIndex >= MAX_ITEM_PER_PERSON)	return;
	if ( pclinfo->m_siEleIndex < 0  || pclinfo->m_siEleIndex >= MAX_ITEM_PER_PERSON)	return;

	if ( pclPerson->clCharItem.clItem[ pclinfo->m_siOrgIndex ].siUnique != pclinfo->m_siOrgUnique )	return;
	if ( pclPerson->clCharItem.clItem[ pclinfo->m_siEleIndex ].siUnique != ENCHANT_CHANGE_ELEMENT_ITEMUNIQUE )	return;

	// �Ӽ����� �������� ������ ���ٸ�
	if ( pclPerson->clCharItem.clItem[ pclinfo->m_siEleIndex ].siItemNum <= 0 )			return;

	// ��þƮ Ÿ���� ���ų�(��þƮ�� ���� ����) �����ϰ��� �ϴ� ��þƮ Ÿ�԰� ���ٸ�
	SI32 siEnchantType = pclPerson->clCharItem.clItem[ pclinfo->m_siOrgIndex ].GetEnchantType( pclClient->pclItemManager );
	if ( (siEnchantType <= 0) || (siEnchantType == pclinfo->m_siChangeType) )			return;

	// ��ȯ�����۰� �Ӽ����� ������ ������ �Ѵ�.
	cltItem clChangeItem;
	clChangeItem.Set( &pclPerson->clCharItem.clItem[ pclinfo->m_siOrgIndex ] );
	clChangeItem.Element.siType = pclinfo->m_siChangeType;

	cltItem	clElementItem;
	clElementItem.siUnique 	= ENCHANT_CHANGE_ELEMENT_ITEMUNIQUE;
	clElementItem.siItemNum	= 1;

	// ������ ����� �����Ѵ�
	((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclinfo->m_siOrgIndex , pclClient->CurrentClock );
	((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclinfo->m_siEleIndex , pclClient->CurrentClock );


	// ������ �Ӽ� ���� ��û�� DB�� ����
	sDBRequest_ChangeEnchant clMsg(id, 
		pclPerson->GetPersonID(), 
		pclinfo->m_siOrgIndex, 
		&clChangeItem,
		pclinfo->m_siEleIndex, 
		&clElementItem
	);	

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMOVE(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->CR[id]->siPersonalMakeItemType > 0) return; //������ ������ �̵� �ȵȴ�.
	if( pclCM->CR[id]->bPersonalEnchantItemSwitch == true) return; 
	if(pclCM->CR[id]->pclCI->GetPersonID() <= 0 ) return; // ����Ǿ��� �߸��� �Ŵ�.


	// ������ �̵� ������ Ȯ���Ѵ�. 
	cltMoveItemInfo* pclmoveiteminfo = (cltMoveItemInfo*)pclMsg->cData;

	cltItem* pclFrom = NULL;
	cltItem  clTo;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	SI32 slot = -1;

	// �������� �����͸� Ȯ���Ѵ�. 
	if(pclmoveiteminfo->uiTo < 0	|| pclmoveiteminfo->uiTo >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMMOVE - PersonID = %d, IP =  %s , uiTo = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclmoveiteminfo->uiTo
																	);
		return ;
	}		
	if(pclmoveiteminfo->uiFrom < 0	|| pclmoveiteminfo->uiFrom >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMMOVE - PersonID = %d, IP =  %s , uiFrom = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclmoveiteminfo->uiFrom
																	);
		return ;
	}	

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �̵� �ȵȴ�.
	if( pclchar->bPersonalShopSwitch == true  && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclmoveiteminfo->uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
                if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclmoveiteminfo->uiFrom	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			// �ͼ����� ���λ���
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclmoveiteminfo->uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			if ( (0 < pclchar->clShopData.m_clSpacialItem.siUnique) && (pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclmoveiteminfo->uiFrom) )
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}
	}


	// ������ ���� ����.  - ������ ���� ����.
	if(pclmoveiteminfo->uiTo < PERSONITEM_INV0 || pclmoveiteminfo->uiFrom < PERSONITEM_INV0)
	{
		pclchar->SendDBWasteDurability();
		pclchar->SendDBSummonWasteDurability();
	}

	//------------------------------------------------
	// ���� ���� ���� ������ �� �κ��� ���� ���� ����.
	//------------------------------------------------
	if(pclCM->CR[id]->HaveHorse() == false)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_HORSE0 && pclmoveiteminfo->uiTo < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY)return ;
	}

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	pclFrom		= &pclCM->CR[id]->pclCI->clCharItem.clItem[pclmoveiteminfo->uiFrom];			

	// �������� ��ȿ�� ���̶��..
	if(pclFrom == NULL || pclFrom->siUnique <=0 ||pclFrom->siItemNum <= 0)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		if(pclFrom == NULL )
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMMOVE - PersonID = %d, IP =  %s , pclFrom = NULL"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP()
																		);
		}
		else
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMMOVE - PersonID = %d, IP =  %s , siUnique = %d,  siItemNum = %d"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP(),
																		pclFrom->siUnique ,
																		pclFrom->siItemNum											
																		);
		}
		return ;
	}
	
	//------------------------------------------------
	// ���� �߿��� �������� ������ �� ����.
	//------------------------------------------------
	if( pclCM->CR[id]->clTransFormInfo.bTransFormMode &&
		pclmoveiteminfo->uiTo >= PERSONITEM_HELMET && pclmoveiteminfo->uiTo < PERSONITEM_HELMET + MAX_SHAPE_ITEM )
	{
		//KHY - 0129 - �������̶�, ȭ��� �Ѿ��� ������ ��������
		switch(pclFrom->siUnique)
		{
			case ITEMUNIQUE(7850) : // ȭ��
			case ITEMUNIQUE(7855) : // �Ѿ�
			case ITEMUNIQUE(13600) : // ���� ȭ��.
			case ITEMUNIQUE(13601) : // ���� �Ѿ�.
				break;
			default:
				// �����߿��� �������� ������ �� �����ϴ�.
				return;
		}
	}

	//------------------------------------------------
	// ���� �߿��� �������� ������ ���� �� �� ����.
	//------------------------------------------------
	if( pclCM->CR[id]->clTransFormInfo.bTransFormMode &&
		pclmoveiteminfo->uiFrom >= PERSONITEM_HELMET && pclmoveiteminfo->uiFrom < PERSONITEM_HELMET + MAX_SHAPE_ITEM )
	{
		//KHY - 0129 - �������̶�, ȭ��� �Ѿ��� ������ ��������
		switch(pclFrom->siUnique)
		{
			case ITEMUNIQUE(7850) : // ȭ��
			case ITEMUNIQUE(7855) : // �Ѿ�
			case ITEMUNIQUE(13600) : // ���� ȭ��.
			case ITEMUNIQUE(13601) : // ���� �Ѿ�.
				break;
			default:
				// �����߿��� �������� ������ ������ �� �����ϴ�.
				return;
		}
	}

	// Ʈ���̵����� ���� �ȵȴ�!
	if ( ((cltCharServer*)pclCM->CR[id])->GetNoMoveItemSwitch(pclmoveiteminfo->uiFrom) != 0 )
	{
		return ;
	}

	//----------------------------------------------------
	// ������ ���� ���� ������ ���� �κ��� ���� ���� ����
	//----------------------------------------------------
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique == 0)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_BAG0 && pclmoveiteminfo->uiTo < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG)return ;
	}

	//----------------------------------------------------
	// ����2�� ���� ���� ������ ���� �κ��� ���� ���� ����
	//----------------------------------------------------
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique == 0)
	{
		if(pclmoveiteminfo->uiTo >= PERSONITEM_BAG1 && pclmoveiteminfo->uiTo < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG)return ;
	}

	//----------------------------------------------------
	// ������ ������ ���� �κ����� �ű� ���� ����.
	//----------------------------------------------------
	if ( pclmoveiteminfo->uiFrom == PERSONITEM_BAG )
	{
		if( pclmoveiteminfo->uiTo >= PERSONITEM_BAG0 && pclmoveiteminfo->uiTo < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			return;
		}

		//----------------------------------------------------
		// ���濡 ������ ��ä�� ������ ���� ��ų���� ����.
		//----------------------------------------------------
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				return;
			}
		}
	}


	//----------------------------------------------------
	// ������ ������ ���� �κ����� �ű� ���� ����. (2)
	//----------------------------------------------------
	if ( pclmoveiteminfo->uiFrom == PERSONITEM_BAG_SUB )
	{
		if( pclmoveiteminfo->uiTo >= PERSONITEM_BAG1 && pclmoveiteminfo->uiTo < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			return;
		}

		//----------------------------------------------------
		// ���濡 ������ ��ä�� ������ ���� ��ų���� ����.
		//----------------------------------------------------
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				return;
			}
		}
	}


	//-----------------------------------------------
	// To �� �ִ´�. 
	//-----------------------------------------------
	clTo.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclmoveiteminfo->uiTo]);

	// �̹� ������ ��ǰ�� �ִ� ������ Ȯ���Ѵ�. 
	if(clTo.siUnique)
	{
		// �ٸ� �������̸� ����. 
		if(clTo.siUnique != pclFrom->siUnique)return ;

		// �������� �ʴ� �������� ����. 
		if(clTo.CanPile(pclItemManager) == false)return ;
	}
	// �ű�� ��ǥ�� üũ �Ѵ�.-> ����ũ�� �ִµ� ������ ������ �� ���� ������ 
	if(clTo.siUnique > 0 && clTo.siItemNum <= 0)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMMOVE_clTo - PersonID = %d, IP =  %s , siUnique = %d,  siItemNum = %d"),	
			pclCM->CR[id]->pclCI->GetPersonID(),
			pclCM->CR[id]->GetSession()->GetIP(),
			clTo.siUnique ,
			clTo.siItemNum											
			);
		//return ;
	}

	// �������� ���� �����δ� �̵���ų �� ����. 
	if(pclItemManager->CheckProperItemPos(pclFrom, pclmoveiteminfo->uiTo, pclchar->GetKind()) == FALSE)return ;

	//------------------------------------------
	// ���� ������ ������Ű���� Ȯ���Ѵ�. 
	//------------------------------------------
	SI32 returnval = 0;
	if(pclCM->CR[id]->CheckEquipCondition(pclItemManager, pclmoveiteminfo->uiTo, pclFrom, &returnval) == false)return ;

	//------------------------------------------
	// �к����� �������� �����Ұ� 
	// �Ⱓ�� ���� �������� �����Ұ� - by LEEKH
	//------------------------------------------
	if((pclmoveiteminfo->uiTo >= 0 && pclmoveiteminfo->uiTo<= 14) || pclmoveiteminfo->uiTo == 82 || pclmoveiteminfo->uiTo== 97)
	{
		if(pclFrom->IsSealingUp(pclItemManager)) return;

		SI32 useableDay;
		BOOL rVal = GetItemUseAbleDay(pclFrom, &useableDay);
		if(rVal == TRUE && useableDay < 0)		return;
	}

	//---------------------------------------------------------------------------
	// ������� ����ؾ� ������ �̵��� �����Ѵ�.
	
	// ����ü ũ����Ż ������ ���� ����.  - 
	if( pclmoveiteminfo->uiFrom < PERSONITEM_INV0)
	{
		pclchar->SendDBCrystalDurability();
		pclchar->SendClientCrystalDurability();
	}

	//-----------------------------------------------
	//DB�޴����� �������� �̵��϶�� ��û�� ������. 
	//-----------------------------------------------
	cltItem clitem;
	clitem.Set(pclFrom);

	//cyj �ű�� �������� ������ MAX_ITEM_PILE_NUMBER�� ������ ���� �������� �ٸ� �κ��丮�� �����ϵ���
	if (DistributePileMoveItem(id, clitem, pclmoveiteminfo->uiFrom, clTo, pclmoveiteminfo->uiTo) == FALSE)
	{
		bool Canpile = false;
		if(( pclFrom->CanPile(pclItemManager))&&( clTo.CanPile(pclItemManager)))
			Canpile = true;
		
		sDBRequest_MoveItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclmoveiteminfo->uiFrom, &clitem, Canpile,
									pclmoveiteminfo->uiTo, &clTo);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);


	}
}

void cltServer::UseItemAction(SI32 id, cltItemUseInfo* pcliteuseinfo)
{
	cltItem* pclFrom = NULL;
	cltItem* pclTo	 = NULL;

	SI32 slot = -1;

	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;

	//	--------------------------------------------


	
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// ���������� ������ ��� �Ұ� �Ұ�. 
	if( pclchar->clInnerStatus.IsStatus(INNERSTATUS_PRISON))
	{			
		SendServerResponseMsg(0, SRVAL_CAN_NOT_USE_ITEM_IN_PRISON, 0, 0, id);
		return;
	}
	

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	if(pcliteuseinfo->uiFrom < 0 || pcliteuseinfo->uiFrom >= MAX_ITEM_PER_PERSON)	return;
	pclFrom = &pclCM->CR[id]->pclCI->clCharItem.clItem[pcliteuseinfo->uiFrom];

	// �������� ��ȿ�� ���̶��..
	if(pclFrom == NULL || pclFrom->siUnique ==0)
	{
		return ;
	}

	// Ŭ���̾�Ʈ���� ������ �������� ����ũ�� ������ ������ ����ũ�� �ٸ��� ����, 
	if(pclFrom->siUnique != pcliteuseinfo->siItemUnique)
	{
		return ;
	}


	// �������� ����� �� �ִ� ���̶�� 
	SI32 returnval = 0;
	bool temp = pclCM->CR[id]->CanUseItem(*pclFrom, &returnval,pcliteuseinfo->uiFrom);
	if( temp == true
		&& pclFrom->IsBulletItem() == false )
	{
		if( true == pclchar->bPersonalShopSwitch ||
			true == pclchar->bPremiumPersonalShop )
		{
			for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
			{
				if( pclchar->clShopData.m_clItem[i].siUnique == pclFrom->siUnique  )
				{
					if( pclchar->clShopData.m_clItem[i].siItemNum >= pclFrom->siItemNum )
					{
						SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
						return;
					}
				}
			}
		}

		cltItem clItem;
		clItem.Set(pclFrom);
		clItem.SetItemNum(1);	// �Ѱ��� ����ϰ� �Ѵ�. !!!!!

		//------------------------------------------------
		// ����ġ �Ӽ���  ��ǰ�̶�� ���� ��ġ�Ѵ�. 
		// ��ȣ�� ������ ��쿡�� ���� ó��..!
		//-------------------------------------------------
		SI64 atb = pclItemManager->GetItemAtb(clItem.siUnique);
		if(atb & ITEMATB_FIRSTACTION || pclItemManager->IsItemInfoAtb(clItem.siUnique, ITEMINFOATB_FIRSTACTION) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
			if ( pclchar->UseItem(clItem,pcliteuseinfo->uiFrom) == false ) return ;
			while(pclchar->clItemUseReserveInfo.Push(clItem.siUnique, -clItem.siItemNum, pcliteuseinfo->uiFrom) == false)
			{
				pclchar->ItemUseReserveAction();
			}

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			if(pclFrom->siItemNum == 1)
			{
				pclchar->ItemUseReserveAction();
			}
			// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
			// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
			pclFrom->Decrease(1);

			// Ŭ���̾�Ʈ�� ����� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pcliteuseinfo->uiFrom, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		// �Ϲ� ��ǰ�� DB�� �������� �Ҹ��� ���� ��û�Ѵ�. 
		else
		{
			sDBRequest_UseItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pcliteuseinfo->uiFrom, &clItem,USEITEM_REASON_NONE);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
	}

}
void cltServer::DoMsg_GAMEMSG_REQUEST_USEITEM(cltMsg* pclMsg, SI32 id)
{
	// ������ ��� ������ ��´�. 
	cltItemUseInfo* pcliteuseinfo = (cltItemUseInfo*)pclMsg->cData;

	UseItemAction(id, pcliteuseinfo);

	return ;

}

// ������ �ݱ⿡ ���� ��û ó��. 
void cltServer::DoMsg_GAMEMSG_REQUEST_INVPICKUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_InvPickUp* pclinfo = (cltGameMsgRequest_InvPickUp*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	//-------------------------------------------------
	// �������� ��ȿ���� Ȯ���Ѵ�. 
	//-------------------------------------------------
	if(pclinfo->siItemUnique <=0 || pclinfo->siItemUnique >= MAX_ITEM_UNIQUE)return ;
	if(pclinfo->siItemIndex < 0)return ;

	//-------------------------------------------------
	// �־��� ��ǥ�� ������ �ش� �������� ������ �ִ��� Ȯ���Ѵ�. 
	//-------------------------------------------------
	cItemNode* pitemnode = pclItemList->GetItem(pclinfo->siItemIndex);
	if(pitemnode == NULL)return ;

	if(pitemnode->item.siUnique != pclinfo->siItemUnique)return ;
	if(pitemnode->item.siItemNum	<= 0)return ;
	if(pitemnode->mapIndex		!= pclinfo->siMapIndex)return;
	if(pitemnode->x				!= pclinfo->siX)return;
	if(pitemnode->y				!= pclinfo->siY)return;

	//-------------------------------------------------
	// �κ��� �������� ���� �� �ִ��� Ȯ���Ѵ�. 
	//-------------------------------------------------
	// �ش� �κ��� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
	SI16 sitopos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pitemnode->item, &sitopos,&cltoitem, &rtnvalue) ==  false)
	{
		return ;
	}	

	//-------------------------------------------------
	// ���� �������� �������� �����ϰ� �κ��� �������� �ֵ��� DB�� ��û�Ѵ�. 
	//--------------------------------------------------
	if(pclMapManager->m_world.GetMap(pclinfo->siMapIndex)->DelItem(pitemnode->x, pitemnode->y, pclinfo->siItemIndex) == TRUE)
	{
		if(pclItemList->RemoveItem(pclinfo->siItemIndex) == TRUE)
		{
			// �������� �߰��Ǵ� �ڸ��� �����Ѵ�. 
			pclchar->SetInputItemReserve(sitopos, pclClient->CurrentClock);

			// ����ڿ��� �������� �ִ� �޽����� ����Ѵ�. 
			sDBRequest_InputItemToPerson clMsg(id, personid, sitopos, INPUTITEMPERSON_OPTION_PICKUP, pitemnode->item.CanPile(pclItemManager), &pitemnode->item, pitemnode->siPersonID, pitemnode->item.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			// [�α��߰� : Ȳ���� 2007. 10. 5] // ����ڿ��� �������� ����.
			//// param1 == ������ ��ġ, param2 == ����, param3 == ��ø ��� ����. param4 == �������� �� �����	
			//cltServer * pclserver = (cltServer*)pclClient;
			//pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM, 
			//								0, (cltCharServer*)pclClient->pclCM->CR[id], NULL, personid, 0, 0, &pitemnode->item, 0, 0, 0, 0, 0, 0, 
			//								sitopos, INPUTITEMPERSON_OPTION_PICKUP, pitemnode->item.CanPile(pclItemManager), pitemnode->siPersonID, 0, NULL, NULL);
			//}
		}
	}


}

void cltServer::DoMsg_GAMEMSG_REQUEST_MAKEITEMSWITCH(cltMsg* pclMsg, SI32 id)
{	
	cltGameMsgRequest_MakeItemSwitch* pclinfo = (cltGameMsgRequest_MakeItemSwitch*)pclMsg->cData;

	pclCM->CR[id]->siPersonalMakeItemType = pclinfo->siType;

	// 
	cltGameMsgResponse_MakeItemSwitch clinfo( pclinfo->siType );
	cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//----------------------------------------------
	// �̿��鿡�Ե� �˸���. 
	//----------------------------------------------
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
}


// ������ �帳�� ���� ��û ó��. 
void cltServer::DoMsg_GAMEMSG_REQUEST_INVDROP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_InvDrop* pclinfo = (cltGameMsgRequest_InvDrop*)pclMsg->cData;

	if( pclCM->CR[id]->siPersonalMakeItemType > 0 ) return; //������ ������ �̵� �ȵȴ�.
	if( pclCM->CR[id]->bPersonalEnchantItemSwitch == true) return; 

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;




	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	//---------------------------------------------
	// �ش� �������� ������ �����ϴ��� Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 itempos = pclinfo->siItemPos;

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	// ������ �ش� �������� �ִ��� Ȯ��. 
	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[itempos];

	if(pclitem->IsSame(&pclinfo->clItem, false) == FALSE)
	{
		// ������ �� ��ġ�� �ִ� �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
		cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		return ;
	}


	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �̵� �ȵȴ�.

	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == itempos )
			{
				if( pclchar->clShopData.m_clItem[i].siUnique > 0  )
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
			}
		}
		
		// �ͼ����� ���λ���
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == itempos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}


	// ������ �������� ���� �����ϰ� �ִ� �����ۺ��� ���� ���� ����. 
	if(pclitem->GetItemNum() < pclinfo->clItem.GetItemNum())return ;

	// Ʈ���̵����� ���� �ȵȴ�!
	if ( ((cltCharServer*)pclCM->CR[id])->GetNoMoveItemSwitch(itempos) != 0 )
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return ;
	}

	// SJY DEBUG
	if ( pclitem->siUnique == 8150 ||
		pclitem->siUnique == 14300 ||
		pclitem->siUnique == 14400 ||
		pclitem->siUnique == 14500 ) // �ݰ��� ��� ��
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return;
	}

	//kkm �ŷ��Ұ��������� ���������� ����
	if ( pclItemManager->IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_NOTTRADE) )
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return;
	}

	//cyj �ͼӾ������� ���������� ����
	if ( pclitem->IsBelonging(pclItemManager))
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return;
	}

	// lkh - ��ƼȦ �������� ���� �� ����.
	if( pclitem->clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return;
	}

	//------------------------------------------
	// �ֺ��� �� �ڸ��� ã�´�. 
	//------------------------------------------
	SI32 mapindex	= pclCM->CR[id]->GetMapIndex();
	SI32 x			= pclCM->CR[id]->GetX();
	SI32 y			= pclCM->CR[id]->GetY();

	SI32 targetx, targety;
	if(pclMapManager->FindProperAreaForDrop(mapindex, x, y, &targetx, &targety) == true)
	{
		//------------------------------------------
		//�������� �������� DB�Ŵ������� ��û�Ѵ�. 
		//------------------------------------------
		sDBRequest_DropItem clMsg(id, personid, pclinfo->siItemPos, &pclinfo->clItem, mapindex, targetx, targety);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

}

// �ͼӾ����� �ı� ��û ó��
void cltServer::DoMsg_GAMEMSG_REQUEST_BELONGITEM_DESTROY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_InvDrop* pclinfo = (cltGameMsgRequest_InvDrop*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	//---------------------------------------------
	// �ش� �������� ������ �����ϴ��� Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 itempos = pclinfo->siItemPos;

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	// ������ �ش� �������� �ִ��� Ȯ��. 
	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[itempos];

	if(pclitem->IsSame(&pclinfo->clItem, false) == FALSE)
	{
		// ������ �� ��ġ�� �ִ� �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
		cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		return ;
	}
	// ������ �������� ���� �����ϰ� �ִ� �����ۺ��� ���� ���� ����. 
	if(pclitem->GetItemNum() < pclinfo->clItem.GetItemNum())return ;

	/*	SI32 UseDate;
	if ( pclItemManager->GetLimitDateItemValue( pclitem->siUnique, &UseDate ) ||*/

	// SJY DEBUG
	if ( pclitem->siUnique == 8150 ||
		pclitem->siUnique == 14300 ||
		pclitem->siUnique == 14400 ||
		pclitem->siUnique == 14500 ) // �ݰ��� ��� ��
	{
		SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
		return;
	}

	if ( IsCountrySwitch(Switch_DestroyDropItem) ){
	}
	else{
		//kkm �ŷ��Ұ��������� ���������� ����
		if ( pclItemManager->IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_NOTTRADE) )
		{
			SendServerResponseMsg(0, SRVAL_CANNOTDROPITEM, 0, 0, id );
			return;
		}
	}
	sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),itempos ,&pclinfo->clItem,USEITEM_REASON_BELONGITEM);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);


}

void cltServer::DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ItemDisAssemble* pclinfo = (cltGameMsgRequest_ItemDisAssemble*)pclMsg->cData;

	if (pclClient->pclCM->IsValidID(id) == false)
		return;

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// ���λ����� ���� ������ ������ ������ ���ϵ��� �ߴ�
	if ( (true == pclchar->bPersonalShopSwitch) || 
		 (true == pclchar->bPremiumPersonalShop) )
	{
		return;
	}
		
	// �߰� : Ȳ���� 2008. 2. 28 => ƾƾ�����̸� ƾƾ���� �޽����� DB�� ������.]
	if( ItemDisAssemble_NPC_KIND::NPC_TINTIN == pclinfo->m_siNPCKind )		
	{
		if( pclinfo->siItemPos < PERSONITEM_INV0 || pclinfo->siItemPos >= PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON)
			return;

		if ( pclinfo->clItem.siUnique != pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siUnique )
			return;

		cltItem clItem;
		clItem.Set( &pclchar->pclCI->clCharItem.clItem[ pclinfo->siItemPos ] );

		if (clItem.siUnique <= 0)
			return;

		if( clItem.IsDisassemble(pclClient->pclItemManager) == false)
		{
			SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_CANNOTITEM, 0, 0, id );
			return;
		}

	/*	SI64 itematb = pclItemManager->GetItemAtb( clItem.siUnique );

		SI32 itemtype = pclItemManager->GetItemType( clItem.siUnique );


		if((itematb & ITEMATB_OBJECT) == 0 && pclGachaManager->IsGachaRareItem( clItem.siUnique ) == false )
			return;

		if ( pclItemManager->IsItemInfoAtb( clItem.siUnique, ITEMINFOATB_ITEMMALL) == false )
		{
			if ( pclItemManager->IsItemInfoAtb( clItem.siUnique, ITEMINFOATB_TRADELIST) == false )
			{
				SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_CANNOTITEM, 0, 0, id );
				return;
			}

			
			if( itemtype == ITEMTYPE_NECK || itemtype == ITEMTYPE_MANTLE || itemtype == ITEMTYPE_RING )
				return;
		}

		// tys[06/04/09] - 20 ���� �̻� ��ǰ�� ���� ����,
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( clItem.siUnique );
		SI32 equipLevel = pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel;

		if ( equipLevel <= 20 && pclClient->IsWhereServiceArea(ConstSwitch_WENNYDISASSEMBLELEVEL) )
		{
			return;
		}*/

		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclchar->ItemUseReserveAction();

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclchar->BulletUseReserveAction();

		SI32 wennypercent = GetAverageWithWeenyOldMan();
		//SI16 wennypercentMsg = 0;

		//// ������ �޼��� ����
		//if( wennypercent <= 80 )		wennypercentMsg = WENNY_PERCENT_SMALL;
		//else if ( wennypercent <= 120 )	wennypercentMsg = WENNY_PERCENT_MEDIUM;
		//else wennypercentMsg = WENNY_PERCENT_LARGE;

		cltItem DisAssembleItem[MAX_ITEM_PER_WENNYOLD];
		for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
		{
			DisAssembleItem[i].Init();
		}

		SI16 siWennyResult = 0;
		SI16 siResolutionRate = 0;
		
		
	/*
		//if ( ���ݾ�����? )
		if ( pclItemManager->IsItemInfoAtb( pclinfo->clItem.siUnique,ITEMINFOATB_ITEMMALL) == true )
		{
			//	������ ���Ⱓ�� ���� �ϼ��� ���Ѵ�.
			//  switch( ���� ������ ȯ�� ���� ��ƾ )
			//		case 1 -> ����̳��� ( 10%���� �����ϼ� +1%, �ִ� 30%)
			//		case 2 -> ��ȣ�Ļ��� ( ������ Ȯ�� )
			//		case 3 -> ���� ( 2% ���� )
			siWennyResult = pclItemManager->GetWennyOldItem( &pclinfo->clItem, &siResolutionRate , true );
		}
		//else( �Ϲ� �������̸� )
		else
		{
			//	�Ϲ� ������ ���� �ü��� ����Ѵ�.
			//  switch( �Ϲ� ������ ȯ�� ���� ��ƾ )
			//		case 1 -> ��ȣ�� ����
			//		case 2 -> ���ؾ������� ��� ȯ��
			//					������ ��� ������ ����
			//					������ ��ŭ ������ ��� ȯ��
			//		case 3 -> ��� 200% ȯ��
			siWennyResult = pclItemManager->GetWennyOldItem( &pclinfo->clItem, &siResolutionRate , false );
		}
	*/
		
		siWennyResult = pclItemManager->GetWennyOldItem( &clItem, &siResolutionRate );

		switch( siWennyResult )
		{
		case WENNYMSG_SMALL:
		case WENNYMSG_MEDIUM:
		case WENNYMSG_LARGE:
		case WENNYMSG_DOUBLE:
			{		
				pclClient->pclItemManager->GetWeenyOldManMaterialInfo(siResolutionRate, clItem.siUnique, DisAssembleItem);
			}
			break;
		case WENNYMSG_NECKLACE:
			{
				cltItem clToItem;
				SI32 bigitemunique = pclClient->pclItemManager->GetRandBigWennyItem();
				SI16 brareswitch = 0;
				pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				DisAssembleItem[0].Set(&clToItem);
			}
			break;
		case WENNYMSG_BOX:
			{		
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;
				pclClient->pclItemManager->MakeRandItemUnique( ITEMUNIQUE(13301), &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				clToItem.siItemNum = 1;
				DisAssembleItem[0].Set( &clToItem );
			}
			break;
		case WENNYMSG_NONE:
			{
				// ��(3750)�� �ش�
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;
				pclClient->pclItemManager->MakeRandItemUnique( ITEMUNIQUE(3750), &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				clToItem.siItemNum = 100;
				DisAssembleItem[0].Set( &clToItem );
			}
			break;
		case WENNYMSG_WENNYMATERIAL:
			{
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;

				SI32 siItemTable[] = {
					ITEMUNIQUE(6140),	// ��ȣ����
					ITEMUNIQUE(5380),	// ƼŸ��
					ITEMUNIQUE(7175)	// �ƶ�̵�
				};

				SI32 siRand = rand() % ( sizeof(siItemTable) / sizeof(SI32) );

				pclClient->pclItemManager->MakeRandItemUnique( siItemTable[siRand] , &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);

				// 1~100 �� ������ �������� �ش�.
				clToItem.siItemNum  = rand() % 100 + 1;
				
				DisAssembleItem[0].Set( &clToItem );
			}
			break;
		//case WENNYMSG_FORTUNE_COOKIE:
		//	{
		//		cltItem clToItem;
		//		clToItem.Init();
		//		SI16 brareswitch = 0;

		//		SI32 siItemTable[] = {
		//			ITEMUNIQUE(13062);	// ������Ű ����.	
		//		};

		//		SI32 siItemNum = 1;
		//		
		//		pclClient->pclItemManager->MakeRandItemUnique( siItemTable[siItemNum], &clToItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, 0);
		//	}
		//	break;
		case WENNYMSG_GACHARARE:
			{
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;
				SI32 MakeItemUnique = 0;
				SI32 MakeItemNum = 1;
				SI32 rndVal = rand()%100;

				if( rndVal < 5 )
				{
					MakeItemUnique = ITEMUNIQUE(13604);
					MakeItemNum	= 2;
				}
				else if( rndVal < 20 )
				{
					MakeItemUnique = ITEMUNIQUE(13604);
					MakeItemNum	= 1;
				}
				else if( rndVal < 30 )
				{
					MakeItemUnique = ITEMUNIQUE(13603);
					MakeItemNum	= 2;
				}
				else if( rndVal < 50 )
				{
					MakeItemUnique = ITEMUNIQUE(13603);
					MakeItemNum	= 1;
				}
				else if( rndVal < 70 )
				{
					MakeItemUnique = ITEMUNIQUE(13602);
					MakeItemNum	= 2;
				}
				else 
				{
					MakeItemUnique = ITEMUNIQUE(13602);
					MakeItemNum	= 1;
				}

				pclClient->pclItemManager->MakeRandItemUnique( MakeItemUnique , &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				clToItem.SetItemNum(MakeItemNum);

				DisAssembleItem[0].Set( &clToItem );		

			}
			break;
		//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.	
		case WENNYMSG_VAlENTINEITEM :
			{
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;
				SI32 MakeItemUnique = 0;
				SI32 MakeItemNum = 1;
				SI32 rndVal = rand()%100;

				if( rndVal < 45 )
				{
					MakeItemUnique = ITEMUNIQUE(3916);
					MakeItemNum	= 1;
				}
				else if( rndVal < 50 )
				{
					MakeItemUnique = ITEMUNIQUE(13040);
					MakeItemNum	= 1;
				}
				else if( rndVal < 70 )
				{
					MakeItemUnique = ITEMUNIQUE(2010);
					MakeItemNum	= (rand()%5) +1;
				}
				else if( rndVal < 90 )
				{
					MakeItemUnique = ITEMUNIQUE(2016);
					MakeItemNum	= (rand()%5) +1;
				}
				else if( rndVal < 100 )
				{
					MakeItemUnique = ITEMUNIQUE(3875);
					MakeItemNum	= 1;
				}


				pclClient->pclItemManager->MakeRandItemUnique( MakeItemUnique , &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				clToItem.SetItemNum(MakeItemNum);

				DisAssembleItem[0].Set( &clToItem );		
			}
			break;
		//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
		case WENNYMSG_WHITEITEM :
			{
				cltItem clToItem;
				clToItem.Init();
				SI16 brareswitch = 0;
				SI32 MakeItemUnique = 0;
				SI32 MakeItemNum = 1;
				SI32 rndVal = rand()%100;

				if( rndVal < 55 )
				{
					MakeItemUnique = ITEMUNIQUE(3917); //ĵ�𰡷�.
					MakeItemNum	= 1;
				}
				else if( rndVal < 65 )
				{
					MakeItemUnique = ITEMUNIQUE(13041); //ĵ�� �����.
					MakeItemNum	= 1;
				}
				else if( rndVal < 80 )
				{
					MakeItemUnique = ITEMUNIQUE(5010); //ö����.
					MakeItemNum	= (rand()%5) +1;
				}
				else if( rndVal < 95 )
				{
					MakeItemUnique = ITEMUNIQUE(5075); //��ȸ��.
					MakeItemNum	= (rand()%3) +1;
				}
				else if( rndVal < 100 )
				{
					MakeItemUnique = ITEMUNIQUE(3875); //��������
					MakeItemNum	= 1;
				}


				pclClient->pclItemManager->MakeRandItemUnique( MakeItemUnique , &clToItem, 0, 0, &brareswitch,0,0,0,0,0,0);
				clToItem.SetItemNum(MakeItemNum);

				DisAssembleItem[0].Set( &clToItem );		
			}
			break;		
		// ������
		case  WENNYMSG_REPAIR_DUR:
			{
				cltItem clToItem;
				clToItem.Init();

				SI16 siRareSwitch			= 0;
				SI32 siRepareStoneUnique	= ITEMUNIQUE(8123);

				// ���Ŀ� �⺻�� �Ǵ� ���� ������
				SI32 siSilverMineralUnique	= ITEMUNIQUE(5050);

				pclClient->pclItemManager->MakeRandItemUnique( siRepareStoneUnique, &clToItem, 0, 0, &siRareSwitch, 0,0,0,0,0,0 );

				cltItemPriceUnit*	pclSilverPriceUnit	= pclItemManager->GetCurrentPrice( siSilverMineralUnique );
				cltItemPriceUnit*	pclGetItemPriceUnit	= pclItemManager->GetCurrentPrice( clItem.siUnique );
				GMONEY				gmTempValue			= 0;
				SI16				siCalcItemNum		= 0;

				if ( (NULL != pclSilverPriceUnit) && (NULL != pclGetItemPriceUnit) )
				{
					gmTempValue = pclSilverPriceUnit->siPrice * 40;
					if ( 0 < gmTempValue )
					{
						gmTempValue		= max( 1, min( 1000, (pclGetItemPriceUnit->siPrice / gmTempValue) ) );

						siCalcItemNum	= (SI16)gmTempValue;
					}
					else
					{
						siCalcItemNum = 1;
					}
				}
				else
				{
					siCalcItemNum = 1;
				}

				clToItem.siItemNum = siCalcItemNum;

				DisAssembleItem[0].Set( &clToItem );			}
			break;
		case WENNYMSG_FAILED:
			SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_UNLUCK, 0, 0, id);
			return;
		}

		bool bSuccess = false;

		// �������� ���� ���ް��� ����
		bool	bApplyDurability	= false; // �ų����� ����ġ�� �Ʒ� ����ġ ���� ���� �����϶� �������� ���� �г�Ƽ�� �����Ѵ�
		REAL32	fDurabilityPenalty	= 0;
		SI16	siPenaltyPercent	= 0;

		if ( IsCountrySwitch(Switch_NewDurability) )
		{
			switch ( siWennyResult )
			{
			// ��� 
			case WENNYMSG_SMALL:
			case WENNYMSG_MEDIUM:
			case WENNYMSG_LARGE:
			case WENNYMSG_DOUBLE:
			// ��
			case WENNYMSG_NONE:
			// �������
			case WENNYMSG_WENNYMATERIAL:
			// ������ ������
			case WENNYMSG_REPAIR_DUR:
				{
					bApplyDurability	= true;
					fDurabilityPenalty	= clItem.GetDurabilityPenlty( pclItemManager );
					siPenaltyPercent	= (SI16)(100.0f * fDurabilityPenalty);
				}
				break;
			}
		}
		
		for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
		{
			if (DisAssembleItem[i].siUnique > 0)
			{
				bSuccess = true;
			
				// �������� ���� ���ް��� �г�Ƽ�� ��������
				if ( bApplyDurability )
				{
					DisAssembleItem[i].siItemNum = (SI16)((REAL32)DisAssembleItem[i].siItemNum * fDurabilityPenalty);
				}
				
				if (DisAssembleItem[i].siItemNum <= 0)
				{
					DisAssembleItem[i].siItemNum = 1;
				}	

				if (DisAssembleItem[i].siItemNum > MAX_ITEM_PILE_NUMBER)
				{
					DisAssembleItem[i].siItemNum = MAX_ITEM_PILE_NUMBER;
				}

				// Ȥ�θ�(2ȣ��) ������ ���� ��踦 ����.
				pclItemManager->AddFromTuneNum(DisAssembleItem[i].siUnique, DisAssembleItem[i].siItemNum);

				// ���ο� ��� - Ȥ�θ�(2ȣ��) ������ ���� ��踦 ����.
				NStatistics_Add("Item", DisAssembleItem[i].siUnique, "FromTuneNum", DisAssembleItem[i].siItemNum);
				NStatistics_Set("Item", DisAssembleItem[i].siUnique, "Name", pclItemManager->GetName(DisAssembleItem[i].siUnique));

			}	// if (DisAssembleItem[i].siUnique > 0)
		}	// for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++) ����


		// Ȥ�θ�(2ȣ��) ���� ��踦 ����.
		pclItemManager->AddTuneNum(pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siUnique, pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siItemNum);

		// ���ο� ��� - Ȥ�θ�(2ȣ��) ���� ��踦 ����.
		NStatistics_Add("Item", pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siUnique, "TuneNum", pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siItemNum);
		NStatistics_Set("Item", pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siUnique, "Name", pclItemManager->GetName(pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos].siUnique));

		if (bSuccess)
		{
			cltItem clUseItem;
			clUseItem.Set( &pclchar->pclCI->clCharItem.clItem[pclinfo->siItemPos] );
			clUseItem.siItemNum = 1;

			bool	bCreateSID[MAX_ITEM_PER_WENNYOLD];
			memset(bCreateSID, 0, sizeof(bCreateSID));

			// ��ǰ���� SID ���� ���θ� �����Ѵ�.
			for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
			{
				if(DisAssembleItem[i].siUnique > 0)
					bCreateSID[i] = DisAssembleItem[i].IsCreateSID(pclItemManager);
			}
			
			if( pclClient->IsCountrySwitch( Switch_InstanceDungeonTicket ) )
			{
				//[�߰� : Ȳ���� 2008. 1. 11 �δ� ���� Ƽ�� �ֱ�]
				if((rand()%100) < 10 + pclClient->pclItemManager->FindItemInfo(clUseItem.siUnique)->clCondition.siLevel)
				{
					for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
					{
						if(DisAssembleItem[i].siUnique <= 0)
						{
							DisAssembleItem[i].siUnique  = ITEMUNIQUE(24107);

							DisAssembleItem[i].siItemNum = 1;
							bCreateSID[i]				 =  DisAssembleItem[i].IsCreateSID(pclItemManager);
							break;
						}
					}
				}
			}
			if( pclClient->IsCountrySwitch( Switch_NewYearEvent_2010) ) // 2010�ų��̺�Ʈ (��ȣ��)
			{
				cltServer* pclserver = (cltServer*)pclClient;

				// �ų��̺�Ʈ ����ġ�� �����ְ�, ���� �̺�Ʈ Ÿ���� ���ȿ��� ������Ű ���� ����
				if( true == pclserver->pclEventTimeManager->InEventTime("Fortune_Event", &pclserver->sTime) )
				{
					SI16 sirandvalue = rand() % 10;

					if( sirandvalue == 0)	// ���ؽ� 10% Ȯ���� ���� ����. [2009.12.24]
					{
						// [���� - 2009.10.20 - ������ ���ؽ� ������Ű���� 1�� ����]
						for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
						{
							if ( 0 >= DisAssembleItem[i].siUnique )
							{
								DisAssembleItem[i].siUnique  = ITEMUNIQUE(13062);
								DisAssembleItem[i].siItemNum = 1;
								bCreateSID[i]				 =  DisAssembleItem[i].IsCreateSID(pclItemManager);
								break;
							}
						}

					}
				}
			}
			if (pclClient->IsCountrySwitch( Switch_BlackArmyTicket )) 
			{
				bool bResult = true;
				SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( clItem.siUnique );
				SI32 DailyQuest3Itemrate = pclClient->pclItemManager->pclItemInfo[Ref]->clSkillInfo.siSkillLevel - 10;
				if ( DailyQuest3Itemrate < 1 )						bResult = false;
				if (siResolutionRate > 0 ) {
					if (DailyQuest3Itemrate / siResolutionRate < 1) 
						bResult = false;
				}
				// ������ Ȯ��
				if ( bResult == true) {
					float siRate = siResolutionRate/100;
					if ( max(1,DailyQuest3Itemrate / siRate ) > 1)
					{
						for (SI32 i = 0; i < MAX_ITEM_PER_WENNYOLD; i++)
						{
							if(DisAssembleItem[i].siUnique <= 0)
							{
								DisAssembleItem[i].siUnique  = ITEMUNIQUE(24084);
								DisAssembleItem[i].siItemNum = 1;
								bCreateSID[i]				 =  DisAssembleItem[i].IsCreateSID(pclItemManager);
								break;
							}
						}
					}
				}
			}
			
			sDBRequest_Wennyoldman_SaveInventory clMsg(id, personid, pclinfo->siItemPos, siWennyResult, siResolutionRate, &clUseItem , DisAssembleItem, bCreateSID, siPenaltyPercent );
			// ������ ���� ����
			clMsg.siUsedItemUnique = clMsg.clUseItem.siUnique;
			clMsg.siUsedItemNum = clMsg.clUseItem.siItemNum;
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
		else
		{
			SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_UNLUCK, 0, 0, id);
		}
	}
	// �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ȯ���̸� ��Ƽ��Ʈ ���� �޽����� DB�� ������.]
	else if( ItemDisAssemble_NPC_KIND::NPC_ATIFACT == pclinfo->m_siNPCKind )			
	{
		bool	bCreateSID[MAX_ITEM_PER_WENNYOLD];
		memset(bCreateSID, 0, sizeof(bCreateSID));

		// ȯ���ϴ� �������� ���� ����ü.
		cltItem RestoreItem[ITEM_BY_RESTORE_MAX_NUM];
		sizeof( RestoreItem, sizeof( RestoreItem ) );

		if( false == pclClient->pclItemManager->MakeItembyRestore(&pclinfo->clItem, RestoreItem, pclchar) )
			return;
				
		sDBRequest_Artifact_SaveInventory clMsg(id, personid, pclinfo->siItemPos, 0, 0, &pclinfo->clItem , RestoreItem, bCreateSID );
		
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM_LIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ItemDisAssemble_List* pclinfo = (cltGameMsgRequest_ItemDisAssemble_List*)pclMsg->cData;

	if (pclClient->pclCM->IsValidID(id) == false)
		return;

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;

	if( ItemDisAssemble_NPC_KIND::NPC_TINTIN == pclinfo->m_siNPCKind )
	{
		sDBRequest_Wennyoldman_InventoryList clMsg(id, personid);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else if( ItemDisAssemble_NPC_KIND::NPC_ATIFACT == pclinfo->m_siNPCKind )
	{
		sDBRequest_Artifact_InventoryList clMsg(id, personid);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DISASSEMBLEITEM_RECIEVE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ItemDisAssemble_Recieve* pclinfo = (cltGameMsgRequest_ItemDisAssemble_Recieve*)pclMsg->cData;

	if (pclClient->pclCM->IsValidID(id) == false)
		return;

	if (pclinfo->clItem.siUnique <= 0)
		return;

	if (pclinfo->siStgPos < 0 || pclinfo->siStgPos >= MAX_ITEM_PER_WENNYOLD)
		return;

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	cltItem clItem;
	clItem.Set(&pclinfo->clItem);

	SI16 invpos;
	cltItem cltoitem;
	SI32 rtnvalue;
	bool canpile = pclClient->pclItemManager->CanPile(clItem.siUnique);

	if(pclchar->CanAddInv(INVMODE_ALL, &pclinfo->clItem, &invpos, &cltoitem, &rtnvalue) == false)
	{
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FULLINVEN, 0, 0, id);
		return ;
	}
	
	pclchar->SetInputItemReserve( invpos, CurrentClock );

	// �߰� : Ȳ���� 2008. 2. 28 => ƾƾ���ظ� ƾƾ �̵� �޽����� DB�� ������.]
	if( ItemDisAssemble_NPC_KIND::NPC_TINTIN == pclinfo->m_siNPCKind )
	{
		sDBRequest_Wennyoldman_MoveItemStgToInv clMsg(id, pclinfo->siStgPos, personid, invpos, &clItem, canpile);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	// �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ�̸� ��Ƽ��Ʈ �̵� �޽����� DB�� ������.]
	else if( ItemDisAssemble_NPC_KIND::NPC_ATIFACT == pclinfo->m_siNPCKind )
	{
		sDBRequest_Artifact_MoveItemStgToInv clMsg(id, pclinfo->siStgPos, personid, invpos, &clItem, canpile);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}

//--------------------------------------------
// ���� �Լ�. 
//--------------------------------------------
bool cltServer::Repair(SI32 mastercharunique, SI32 clientcharunique, SI32 clientitempos, cltItem* pclitem, GMONEY repairmoney, SI32* preturnval)
{
	//---------------------------------------------
	// �����ڰ� ��ȿ���� �˻��Ѵ�. 
	//---------------------------------------------
	if(pclCM->IsValidID(mastercharunique) == false)return false;

	//---------------------------------------------
	// �Ƿ��ڰ� ��ȿ���� �˻��Ѵ�.
	//---------------------------------------------
	if(pclCM->IsValidID(clientcharunique) == false)return false;

	//---------------------------------------------
	// �ش� �������� ������ �����ϴ��� Ȯ���Ѵ�. 
	//---------------------------------------------
	if(clientitempos < 0 || clientitempos >= MAX_ITEM_PER_PERSON)return false;
	cltItem* pclorgitem = &pclCM->CR[clientcharunique]->pclCI->clCharItem.clItem[clientitempos];
	// �־��� �����۰� ���� ���������� Ȯ���Ѵ�. 
	if(pclitem->IsSame(pclorgitem, false) == false)
	{
		*preturnval = REPAIR_ERR_NOTSAMEITEM;
		return false;
	}
	if(pclitem->siUnique <= 0)return false;
	// ���� �Ұ����� �������̾ ����.
	if(pclitem->CanRepair(pclItemManager) == false)return false;

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if ( ref <= 0 ) return false ;
	if ( pclItemManager->pclItemInfo[ref]->siSetItemIndex > 0 )
	{
		*preturnval = REPAIR_ERR_NOTSAMEITEM ;
		return false ;
	}

	//--------------------------------------------
	// ���� ������ Ȯ���Ѵ�. 
	//--------------------------------------------
	SI32 decdur = MIN_DUR_FOR_REPAIR;

	// ������ ���꿡 �ʿ��� ��ų�� Ȯ���Ѵ�. 
	SI32 skillunique = pclitem->GetMakeSkill(pclItemManager);
	if(skillunique)
	{
#ifdef _SAFE_MEMORY
		SI32 skilllevel		= pclCM->CR[mastercharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCM->CR[mastercharunique]->pclCI->clCharItem.clItem[0]);
#else
		SI32 skilllevel		= pclCM->CR[mastercharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCM->CR[mastercharunique]->pclCI->clCharItem.clItem);
#endif
		// ��� ���ؿ� ���� �Ҹ�Ǵ� �������� ���Ѵ�. 
		decdur = GetWasteDurability(skilllevel);
	}


	cltItem clitem;
	clitem.Set(pclitem);

	if(clitem.Repair(pclItemManager, decdur) == true)
	{
		//--------------------------------------------
		// ���� �ϵ��� DB�Ŵ������� ��û�Ѵ�. 
		//--------------------------------------------
		SI32 personid		= pclCM->CR[clientcharunique]->pclCI->GetPersonID();
		SI32 repairpersonid = pclCM->CR[mastercharunique]->pclCI->GetPersonID();

		sDBRequest_InvRepair clMsg(clientcharunique, personid, clientitempos, &clitem, repairpersonid, repairmoney, 0);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	}



	return true;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INVREPAIR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_InvRepair* pclinfo = (cltGameMsgRequest_InvRepair*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	// ������ ���� ����. 
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->SendDBWasteDurability();
	pclchar->SendDBSummonWasteDurability();

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclinfo->siItemPos;
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ itempos ];
	SI32 rtnval = 0;
	if(Repair(id, id, itempos, pclitem, 0, &rtnval) == false)
	{
		// ���� �Ƿڵ� �����۰� ���� �������� �ٸ��ٸ�, 
		if(rtnval == REPAIR_ERR_NOTSAMEITEM)
		{
			// ������ �� ��ġ�� �ִ� �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_UPGRADEITEM(cltMsg* pclMsg, SI32 id)
{
	return;
}


void cltServer::DoMsg_GAMEMSG_REQUEST_MAKEITEMINVINDEX(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_MakeItem_SelectedIndex* pclinfo = (cltGameMsgRequest_MakeItem_SelectedIndex*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	if( pclinfo->siMoveInvIndex < 0 || pclinfo->siMoveInvIndex >= 29 )	return;

	pclCM->CR[id]->siInvMakeItemIndex[pclinfo->siMoveInvIndex] = pclinfo->siInvSelectedValue ;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PERFORMANCEUPGRADEITEM(cltMsg* pclMsg, SI32 id)
{
	//if ( pclCM->IsValidID(id) == false )
	//{
	//	return;
	//}
	//
	//cltGameMsgRequest_PerformanceUpgradeItem *pclinfo = (cltGameMsgRequest_PerformanceUpgradeItem*)pclMsg->cData;

	//SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	//if ( FromPersonID < 1 )
	//{
	//	return;
	//}

	//// ���׷��̵��� ������ ��ġ Ȯ��
	//if ( pclinfo->siItemPos < PERSONITEM_INV0 || pclinfo->siItemPos >= MAX_ITEM_PER_PERSON )
	//{
	//	return;
	//}

	///*
	//if( ( pclinfo->siVillageUnique < 1 || pclinfo->siVillageUnique > CUR_VILLAGE_LIMIT ) &&
	//	pclinfo->siVillageUnique != MAPINDEX_PALACE )
	//	return;
	//*/

	//// �������� �����ϴ��� Ȯ��
	//if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique < 1 )
	//{
	//	return;
	//}

	//// ������ ��ġ Ȯ��
	//if ( ! pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].IsSame( &pclinfo->clItem, true ) )
	//{
	//	return;
	//}

	//// ��ø ������ �ȵ�
	//if ( pclinfo->clItem.CanPile( pclItemManager ) )
	//{
	//	return;
	//}

	//cltItem clDestItem;
	//clDestItem.Init();

	//SI32 ScrollUnique, ScrollNum;
	//SI32 returnval = 0;
	//if( ! pclItemManager->GetScrollForTune2( pclinfo->clItem, &ScrollUnique, &ScrollNum, &clDestItem, &returnval ) )
	//{
	//	return;
	//}

	//if ( ScrollUnique < 1 || ScrollNum < 1 )
	//{
	//	return;
	//}

	////---------------------------------------------
	//// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	////---------------------------------------------
	//cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	//pclChar->ItemUseReserveAction();

	////---------------------------------------------
	//// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	////---------------------------------------------
	//pclChar->BulletUseReserveAction();

	//// ������ �ִ��� Ȯ��
	//SI32 ScrollPos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( ScrollUnique );
	//if ( ScrollPos < 0 )
	//{
	//	return;
	//}

	//if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ ScrollPos ].GetItemNum() < ScrollNum )
	//{
	//	return;
	//}

	//// Ȥ�θ� ���� �̿�� Ȯ��
	//SI16 HokburiItemPos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( ITEMUNIQUE(24005) );
	//if ( HokburiItemPos < 0 )
	//{
	//	return;
	//}

	//if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ HokburiItemPos ].GetItemNum() < 1 )
	//{
	//	return;
	//}

	//cltItem clScrollItem;
	//clScrollItem.Init();
	//clScrollItem.siUnique = ScrollUnique;
	//clScrollItem.siItemNum = ScrollNum;

	//sDBRequest_PerformanceUpgradeItem clMsg( id, FromPersonID, pclinfo->siItemPos, &pclinfo->clItem, &clDestItem, ScrollPos, &clScrollItem );
	//pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	//// ��ǰ ��� ��踦 ����.(����)
	//pclItemManager->AddUseNum( ScrollUnique, ScrollNum );   
	//// Ȥ�θ� ���� �̿�� ���
	//cltItem clHokburiItem;
	//clHokburiItem.Init();

	//clHokburiItem.siUnique = ITEMUNIQUE(24005);
	//clHokburiItem.siItemNum = 1;

	//sDBRequest_UseItem clMsg1( id, FromPersonID, HokburiItemPos, &clHokburiItem ,USEITEM_REASON_TICKET);
	//pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg1);

	//// ��ǰ ��� ��踦 ����.(Ȥ�θ������̿��)
	//pclItemManager->AddUseNum( ITEMUNIQUE(24005), 1 );

	//// ���� �̿� ���� �Ǽ� ���. 
	//pclStatisticsManager->clDailyStatistics.siScrollTuneNumber+= ScrollNum;

	return;
}

// �������� �ٴڿ� ����߸���. 
void cltServer::DropItem(SI32 mapindex, SI32 x, SI32 y, cltItem* pclitem, SI32 droppersonid)
{
	//------------------------------------------
	// �������� �����۸���Ʈ�� �߰��Ѵ�. 
	//------------------------------------------
	UI16 index = pclItemList->PushItem(mapindex, x, y, pclitem, droppersonid );
	if(index)
	{
		pclMapManager->m_world.GetMap(mapindex)->AddItem(x, y, index);
	}

	if( mapindex < 0 || mapindex >= MAX_MAP_NUMBER )		return;
	//------------------------------------------
	// ������ �������� ������. 
	//------------------------------------------
	pclMapManager->pclMapArray[mapindex]->SetItemMap(x, y, pclitem->siUnique, index);
}
/*
void cltServer::DoMsg_GAMEMSG_REQUEST_MONSTERCORP_START(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if (pclchar == NULL ) 
		return ;

	pclchar->dwStartMiniGame = CurrentClock;
}*/

void cltServer::DoMsg_GAMEMSG_REQUEST_MONSTERCORP_SCORE(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltGameMsgRequest_MonsterCorp_Score* pclinfo = (cltGameMsgRequest_MonsterCorp_Score*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if (pclchar == NULL ) 
		return ;

	if ( pclchar->bMakeItemNoMinigame || pclchar->bMakeItemSwitch )
	{
		pclchar->siMonsterCorp = 0 ;
		pclchar->dwStartMiniGameTime = 0;
		return ;
	}
    
	if( pclchar->siMonsterCorp == pclinfo->siScore )
	{
		SI32 score = min(10000,max(-10000,pclinfo->siScore));

		// �߱��� �̴ϰ��� ���� �α׸� �����.
		if( ConstServiceArea_China == siServiceArea )
		{
			if( 1000 <= score )
			{
				DWORD totalTime = ( CurrentClock - pclchar->dwStartMiniGameTime ) / 1000;
				pclLog->FileConfigPrint( "MiniGameLog", "Name : [%s], Score : [%d] Time : [%d]", (TCHAR*)pclchar->GetName(), pclinfo->siScore, totalTime );
			}
		}

		pclchar->bMakeItemMinigameSwitch = true ;
		pclchar->siMonsterCorp = score ;
		pclchar->dwStartMiniGameTime = 0;
	}
	else
	{
		pclchar->bMakeItemMinigameSwitch = true ;
		pclchar->siMonsterCorp = 0 ;
		pclchar->dwStartMiniGameTime = 0;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MONSTERCORP_COMBOINFO(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltGameMsgRequest_MonsterCorp_ComboInfo* pclinfo = (cltGameMsgRequest_MonsterCorp_ComboInfo*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if (pclchar == NULL ) 
		return ;

	if( pclinfo->GetScore() == SCORE ||
		pclinfo->GetScore() == PENALTYSCORE )
	{
		pclchar->siMonsterCorp += pclinfo->GetScore() * pclinfo->GetComboInfo();
	}
}

// �ڴ�� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_ROULETTEGAME_INFO(cltMsg* pclMsg,SI32 id)
{
	// �������̸� ����
	if( bRouletteGame )
		return;

	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltGameMsgRequest_RouletteGame_Info* pclinfo = (cltGameMsgRequest_RouletteGame_Info*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if (pclchar == NULL ) return ;

	for(SI32 y = 0;y<5;++y)
	{
		for (SI32 x = 0;x<5;++x) 
		{
			if( pclinfo->m_stRoulette[y][x].m_bCpuSelect == true || pclinfo->m_stRoulette[y][x].m_bResult == true)
				return;

			pclchar->m_stRouletteTable[y][x].Set(pclinfo->m_stRoulette[y][x].m_bUserSelect,
				pclinfo->m_stRoulette[y][x].m_bCpuSelect,
				pclinfo->m_stRoulette[y][x].m_bResult,
				pclinfo->m_stRoulette[y][x].m_siX,
				pclinfo->m_stRoulette[y][x].m_siY,
				pclinfo->m_stRoulette[y][x].m_siValue);	

			if( pclchar->m_stRouletteTable[y][x].m_bUserSelect == true )
				pclchar->m_siBettingCount++;
		}
	}

	pclchar->m_siRandomValue[0] = rand()%25 + 1;

	do
	{
		pclchar->m_siRandomValue[1] = rand()%25 + 1;
	}while( (pclchar->m_siRandomValue[0] != pclchar->m_siRandomValue[1]) == false);

	do
	{
		pclchar->m_siRandomValue[2] = rand()%25 + 1;
	}
	while( (pclchar->m_siRandomValue[0] != pclchar->m_siRandomValue[2] && pclchar->m_siRandomValue[1] != pclchar->m_siRandomValue[2]) == false);

	do
	{
		pclchar->m_siRandomValue[3] = rand()%25 + 1;
	}
	while( (pclchar->m_siRandomValue[0] != pclchar->m_siRandomValue[3] && pclchar->m_siRandomValue[1] != pclchar->m_siRandomValue[3] && pclchar->m_siRandomValue[2] != pclchar->m_siRandomValue[3]) == false);

	do
	{
		pclchar->m_siRandomValue[4] = rand()%25 + 1;
	}
	while( (pclchar->m_siRandomValue[0] != pclchar->m_siRandomValue[4] && pclchar->m_siRandomValue[1] != pclchar->m_siRandomValue[4] && pclchar->m_siRandomValue[2] != pclchar->m_siRandomValue[4] && pclchar->m_siRandomValue[3] != pclchar->m_siRandomValue[4]) == false);

	for(SI32 y = 0;y<5;++y)
	{
		for (SI32 x = 0;x<5;++x) 
		{
			if( pclchar->m_stRouletteTable[y][x].m_siValue  == pclchar->m_siRandomValue[0] )
				pclchar->m_stRouletteTable[y][x].m_bCpuSelect = true;
			else if( pclchar->m_stRouletteTable[y][x].m_siValue  == pclchar->m_siRandomValue[1] )
				pclchar->m_stRouletteTable[y][x].m_bCpuSelect = true;
			else if( pclchar->m_stRouletteTable[y][x].m_siValue  == pclchar->m_siRandomValue[2] )
				pclchar->m_stRouletteTable[y][x].m_bCpuSelect = true;
			else if( pclchar->m_stRouletteTable[y][x].m_siValue  == pclchar->m_siRandomValue[3] )
				pclchar->m_stRouletteTable[y][x].m_bCpuSelect = true;
			else if( pclchar->m_stRouletteTable[y][x].m_siValue  == pclchar->m_siRandomValue[4] )
				pclchar->m_stRouletteTable[y][x].m_bCpuSelect = true;
		}
	}

	pclchar->SetRoulette(true);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ROULETTEGAME_STOP(cltMsg* pclMsg,SI32 id)
{
	// �������̸� ����
	if( bRouletteGame )
		return;

	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if (pclchar == NULL ) return ;

	pclchar->SetRoulette(false);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INV_CANCELLATIONSEALINGUP(cltMsg* pclMsg, SI32 id)
{
 	cltGameMsgRequest_Inv_CancellationSealingUp* pclinfo = (cltGameMsgRequest_Inv_CancellationSealingUp*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	pclchar->SendDBWasteDurability();
	pclchar->SendDBSummonWasteDurability();

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclinfo->siItemPos;
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �к������� �ȵȴ�.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == itempos	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTSEALINGUP_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}

		// �ͼ����� ���λ���
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == itempos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}


	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ itempos ];

	if( NULL == pclitem )
		return;

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if( ref <= 0)
		return;

	SI32 rtnval = 0;
	if(pclitem->IsSealingUp(pclItemManager) )
	{
		pclitem->uiDateYear = sTime.wYear - 2000 ;
		pclitem->uiDateMonth = sTime.wMonth ;
		pclitem->uiDateDay = sTime.wDay ;

		//cyj ����̴� �к� �����Ҷ� ������ ������..
		SI32 type = pclItemManager->GetItemType(pclitem->siUnique);
		if (type == ITEMTYPE_NECK)
		{
			if ( pclitem->siUnique == ITEMUNIQUE(1200))		// ��õ�� �����
			{
				SI32 skillup = (rand() % (TABS(pclitem->clItemNeck.uiMaxSkillPoint - pclitem->clItemNeck.uiSkillPointUp) + 1)) + pclitem->clItemNeck.uiSkillPointUp;
				pclitem->clItemNeck.uiSkillPointUp	= max(pclitem->clItemNeck.uiSkillPointUp, skillup);

				SI32 usedate = (rand() % (TABS(pclitem->clItemNeck.uiMaxUsedate - pclitem->uiDateUseDay) + 1)) + pclitem->uiDateUseDay;

				pclitem->uiDateUseDay = max(pclitem->uiDateUseDay, usedate);

			}
			else
			{
				pclitem->clItemNeck.uiMaxSkillPoint = 5;

				SI32 siRand = rand() % 100 + 1;
				SI32 skillup = 0;
				SI32 useDate = 0;
				if ( siRand <= 20 )	
				{
					skillup = 1;
					useDate = 14;
				}
				else if ( siRand <= 60 ) 
				{
					skillup = 2;
					useDate = 12;
				}
				else if ( siRand <= 85 ) 
				{
					skillup = 3;
					useDate = 10;
				}
				else if ( siRand <= 95 ) 
				{
					skillup = 4;
					useDate = 8;
				}
				else	
				{
					skillup = 5;
					useDate = 7;
				}

				pclitem->clItemNeck.uiSkillPointUp	= skillup;
				if( true == pclItemManager->pclItemInfo[ref]->IsImmutableUseDate() )
					pclitem->uiDateUseDay = pclitem->uiDateUseDay;
				else
					if( ITEMUNIQUE(1190) == pclitem->siUnique ) // �����̾� ����̸� ��¥�� ���ҽ��� ��¥�� �Ѵ�.
					{

					}
					else
					{
						pclitem->uiDateUseDay = useDate + ( rand() % 8 );
					}
				if( skillup >= 4 )
					pclitem->clItemNeck.clCommonInfo.uiRareInfo = RARE2_ITEM_RATE;
			}
		}

		{
			// DB�� �����Ѵ�. �ϴ� ������ �޽����� �����Ѵ�.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		}

		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

// ���ݼ���κ��� �������� �ɷ��� �����Ѵ�.
void cltServer:: DoMsg_GAMEMSG_REQUEST_INV_ChangItemFromNPC(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Inv_ChangItemFormNpc* pclinfo = (cltGameMsgRequest_Inv_ChangItemFormNpc*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	
	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclinfo->siItemPos;
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)return ;

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� ������ �����Ҽ� ����.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == itempos	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTSEALINGUP_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}
		// �ͼ����� ���λ���
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == itempos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}
	cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ itempos ];

	if( NULL == pclitem )
		return;
	// �����ְ� �ƴ� ������ �����ҽÿ��� �ȵȴ�.
	if (pclitem->clItemStatusArmour.uiStr > 0 ||
	pclitem->clItemStatusArmour.uiDex > 0 ||
	pclitem->clItemStatusArmour.uiLuk > 0 ||
	pclitem->clItemStatusArmour.uiMag > 0 ||
	pclitem->clItemStatusArmour.uiVit > 0 
	)
	{
		return;
	}
	// ������������ �ƴϸ� ���´�.
	if (pclClient->pclGachaManager->IsGachaRareItem(pclitem->siUnique ) == false) {
		return ;
	}
	if( pclitem->GetType(pclItemManager) != ITEMTYPE_DRESS && pclitem->GetType(pclItemManager) !=ITEMTYPE_HAT ) return;

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if( ref <= 0)
		return;
	if (pclinfo->uiStatusLater == ChangeStrStatus) {// ������ ������ �����Ұ��
		pclitem->clItemStatusArmour.uiStr = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiDex = 0;
		pclitem->clItemStatusArmour.uiHnd = 0;
		pclitem->clItemStatusArmour.uiLuk = 0;
		pclitem->clItemStatusArmour.uiMag = 0;
		pclitem->clItemStatusArmour.uiVit = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	else if (pclinfo->uiStatusLater == ChangeDexStatus) {// ������ �������� �����Ұ��
		pclitem->clItemStatusArmour.uiDex = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiHnd = 0;
		pclitem->clItemStatusArmour.uiLuk = 0;
		pclitem->clItemStatusArmour.uiMag = 0;
		pclitem->clItemStatusArmour.uiStr = 0;
		pclitem->clItemStatusArmour.uiVit = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	else if (pclinfo->uiStatusLater == ChangeVitStatus) {// ������ ��������� �����Ұ��
		pclitem->clItemStatusArmour.uiVit = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiDex = 0;
		pclitem->clItemStatusArmour.uiHnd = 0;
		pclitem->clItemStatusArmour.uiLuk = 0;
		pclitem->clItemStatusArmour.uiMag = 0;
		pclitem->clItemStatusArmour.uiStr = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	else if (pclinfo->uiStatusLater == ChangeHndStatus) {// ������ ���������� �����Ұ��
		pclitem->clItemStatusArmour.uiHnd = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiDex = 0;
		pclitem->clItemStatusArmour.uiLuk = 0;
		pclitem->clItemStatusArmour.uiMag = 0;
		pclitem->clItemStatusArmour.uiStr = 0;
		pclitem->clItemStatusArmour.uiVit = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	else if (pclinfo->uiStatusLater == ChangeLukStatus) {// ������ ������� �����Ұ��
		pclitem->clItemStatusArmour.uiLuk = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiDex = 0;
		pclitem->clItemStatusArmour.uiHnd = 0;
		pclitem->clItemStatusArmour.uiMag = 0;
		pclitem->clItemStatusArmour.uiStr = 0;
		pclitem->clItemStatusArmour.uiVit = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	else if (pclinfo->uiStatusLater == ChangeMagStatus) {// ������ ���������� �����Ұ��
		pclitem->clItemStatusArmour.uiMag = pclinfo->uiStatusNow;
		pclitem->clItemStatusArmour.uiDex = 0;
		pclitem->clItemStatusArmour.uiHnd = 0;
		pclitem->clItemStatusArmour.uiLuk = 0;
		pclitem->clItemStatusArmour.uiStr = 0;
		pclitem->clItemStatusArmour.uiVit = 0;
		{
			// ���� �ش� ������������ ������.
			sDBRequest_WasteDurability clMsg(id, pclchar->pclCI->GetPersonID(), itempos, pclitem);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			// �������� ������ ������ Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
	// ���ݼ��� ������ ���� ���� �޼����� Ŭ���̾�Ʈ�� ������.
	SendServerResponseMsg( 0, SRVAL_CHANGE_ITEM_FROM_NPC, 0, 0, id ); 

}

BOOL cltServer::GetItemUseAbleDay(cltItem* clItem, SI32* outUseAbleDay) //[����] ������ ���� ���Ⱓ�� outUseAbleDay ������ ��� �������ش�
{
	*outUseAbleDay = 0; // 0������ �ʱ�ȭ

	if(clItem == NULL) return FALSE; // ������ �����Ͱ� �߸��Ǿ��ٸ� ����
	SI32 itemunique = clItem->siUnique ;
	if(itemunique <= 0)return FALSE; // ������ ����ũ�� �߸��Ǿ��ٸ� ����


	if(clItem->IsSealingUp(pclItemManager) == TRUE)
	{
		*outUseAbleDay = clItem->uiDateUseDay;	// �к��� �������̶�� ���Ⱓ ��ȯ
		return TRUE;
	}


	if(clItem->IsHaveUseDay() == TRUE)  // �к� Ǯ�� �Ⱓ�� �������̶�� ���Ⱓ ����ؼ� ��ȯ
	{

		NDate ndate;
		ndate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
		SI32 todaydatevary = ndate.GetDateVary() ;

		ndate.SetDate(clItem->uiDateYear+2000,clItem->uiDateMonth,clItem->uiDateDay);
		SI32 datevary = ndate.GetDateVary() + clItem->uiDateUseDay ;

		// ������ ��� ������ ���� - ����. 
		// ����� ��� ������,  0 �̸� ������ �����, ������ ������� �� ������
		*outUseAbleDay =  datevary - todaydatevary;

		//KHY - 0723 - �Ⱓ������ �ı� ����. Ȥ�� ����.
		if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
		{
			if(*outUseAbleDay < 0)
			{
				pclClient->sUpViewEffect = 1;				
			}

			if(*outUseAbleDay < (-10000))
				*outUseAbleDay = -10000;
		}

		return TRUE;
	}
	else if(clItem->uiDateUseDay == 0 ) // ��¥�� ���� �Ϲ� �������̴�.
		return TRUE;		

	return FALSE ; //  Error ��ƾ. 

}

BOOL cltServer::DistributePileMoveItem(SI32 charid, cltItem clFrom, UI16 uiFrom, cltItem clTo, UI16 uiTo)
{
	SI32 max_pile_number = MAX_ITEM_PILE_NUMBER;
	SI32 total_plie_number;
	BOOL bBulletMove = FALSE;

	// ���â���� ȭ���̳� źȯ �������� ��ø������ DEFAULT_EQUIP_BULLET_NUMBER��
	if ((uiTo == PERSONITEM_WEAPON1 ||  uiTo == PERSONITEM_WEAPON2) && 
		clFrom.IsBulletItem())
	{
		if (pclCM->IsValidID(charid) && pclCM->CR[charid]->pclCI->clBI.bBulletService)
		{
			max_pile_number = UPGRADE_EQUIP_BULLET_NUMBER;
		}
		else
		{
			max_pile_number = DEFAULT_EQUIP_BULLET_NUMBER;
		}

		bBulletMove = TRUE;

		/*
		// ȭ���̳� źȯ������ �����Ҷ� �κ��丮�� ��ĭ�̸� ������ �й踦 ���� siUnique�� ���� ����
		if (bBulletMove)
		{
		if (clTo.siUnique == 0)
		{
		clTo.siUnique = clFrom.siUnique;
		clTo.siItemNum = 0;
		}
		}
		*/
	}

	// ���ʴ� �����ϰų� �Ѿ� �������� ���
	if ( (clFrom.CanPile(pclClient->pclItemManager) == true) && 
		((bBulletMove == TRUE) || (clTo.CanPile(pclClient->pclItemManager) == true))
	)
		
	{
		if (clFrom.siUnique == clTo.siUnique)
		{
			total_plie_number = clFrom.siItemNum + clTo.siItemNum;
		}
		else
			total_plie_number = clFrom.siItemNum;

		//������ ��ǰ���� �ű涧 ������
		if ((uiFrom != uiTo && (clFrom.siUnique == clTo.siUnique || clTo.siUnique == 0 || bBulletMove) && total_plie_number > max_pile_number))
		{
			cltItem tmpFromItem, tmpToItem;
			//SI16 sitopos;
			//SI32 rtnvalue;

			tmpFromItem.Set(&clFrom);
			tmpFromItem.siItemNum = max_pile_number - clTo.siItemNum;

			if ( pclCM->IsValidID(charid) )
			{
				sDBRequest_MoveItem clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(), uiFrom, &tmpFromItem, tmpFromItem.CanPile(pclItemManager),
					uiTo, &clTo);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}

			return TRUE;
		}
	}

	return FALSE;
}



void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTITEMINVINDEX(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_EnchantItem_SelectedIndex* pclinfo = (cltGameMsgRequest_EnchantItem_SelectedIndex*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	pclCM->CR[id]->siOrgInvEnchantInx = pclinfo->siOrgInvEnchantInx;
	pclCM->CR[id]->siMatInvEnchantInx = pclinfo->siMatInvEnchantInx;	

	for ( SI16 siIndex=0; siIndex<NOW_ENCHANT_NUMBER; siIndex++ )
	{
		pclCM->CR[id]->siElementEnchantInx[siIndex] = pclinfo->siElementEnchantInx[siIndex];
	}
	pclCM->CR[id]->siElementType = pclinfo->siElementType;


	return;

}

void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTITEMSWITCH(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Enchant_Switch* pclinfo = (cltGameMsgRequest_Enchant_Switch*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;


	pclCM->CR[id]->bPersonalEnchantItemSwitch = pclinfo->bEnchantSwitch;

	return;

}


void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTITEMSTARTOREND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Enchant_StartOrEnd clinfo(bEnchantSwitch);
	cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTITEMSTARTOREND, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}


void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTOTHERPRICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EnchantPrice* pclinfo = (cltGameMsgResponse_EnchantPrice*)pclMsg->cData;


	if(pclinfo->siUnique <=0 ) return;
	cltItemPriceUnit *CurrentPrice = pclItemManager->GetCurrentPrice(pclinfo->siUnique);
	SI64 sifee = CurrentPrice->siPrice;


	cltGameMsgRequest_EnchantPrice clinfo(sifee);
	cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTOTHERPRICE, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);   

}
void cltServer::DoMsg_GAMEMSG_REQUEST_ENCHANTOTHERSHOW(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_EnchantOther* pclinfo = (cltGameMsgRequest_EnchantOther*)pclMsg->cData;

	SI32 otherid = pclinfo->m_siOtherCharUnique;
	if(pclCM->IsValidID(otherid) == false)		return;

	cltItem clOrgItem;
	cltItem clMatItem;
	cltItem clEleItem[NOW_ENCHANT_NUMBER];

	pclCM->CR[otherid]->siOrgInvEnchantInx  = pclinfo->siOrgIndex;
	pclCM->CR[otherid]->siMatInvEnchantInx = pclinfo->siMatIndex;


	
	for (SI16 siIndex=0; siIndex<NOW_ENCHANT_NUMBER; siIndex++)
	{
		pclCM->CR[otherid]->siElementEnchantInx[siIndex]= pclinfo->siEleIndex[siIndex];
		clEleItem[siIndex].Init();

		if (pclinfo->siEleIndex[siIndex] >= 0 && pclinfo->siEleIndex[siIndex] < MAX_ITEM_PER_PERSON)
			clEleItem[siIndex].Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siEleIndex[siIndex]]);
	}


	if(pclinfo->siOrgIndex >= 0 && pclinfo->siOrgIndex < MAX_ITEM_PER_PERSON)
		clOrgItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siOrgIndex]);

	if(pclinfo->siMatIndex >= 0 && pclinfo->siMatIndex < MAX_ITEM_PER_PERSON)
		clMatItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siMatIndex]);


	//������Ʈ�� ���ÿ� ���� �̵��� �ȵȴ�.
	pclCM->CR[id]->bPersonalEnchantItemSwitch = false;

#ifdef _SAFE_MEMORY
	cltGameMsgResponse_EnchantOther clinfo(&clOrgItem, &clMatItem, clEleItem, pclinfo->siOrgIndex,pclinfo->siMatIndex , &pclinfo->siEleIndex[0], true, false);
#else
	cltGameMsgResponse_EnchantOther clinfo(&clOrgItem, &clMatItem, clEleItem, pclinfo->siOrgIndex,pclinfo->siMatIndex , pclinfo->siEleIndex, true, false);
#endif
	cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTOTHERSHOW, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[otherid]->SendNetMsg((sPacketHeader*)&clMsg);


#ifdef _SAFE_MEMORY
	cltGameMsgResponse_EnchantOther clinfo1(&clOrgItem, &clMatItem, clEleItem, pclinfo->siOrgIndex,pclinfo->siMatIndex , &pclinfo->siEleIndex[0], false, false);
#else
	cltGameMsgResponse_EnchantOther clinfo1(&clOrgItem, &clMatItem, clEleItem, pclinfo->siOrgIndex,pclinfo->siMatIndex , pclinfo->siEleIndex, false, false);
#endif
	cltMsg clMsg1(GAMEMSG_RESPONSE_ENCHANTOTHERSHOW, sizeof(clinfo1), (BYTE*)&clinfo1);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);


	return;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMSPLIT(cltMsg* pclMsg, SI32 id)
{
	// ���ø�!!
	if( pclCM->CR[id]->siPersonalMakeItemType > 0) return; //������ ������ �̵� �ȵȴ�.
	if( pclCM->CR[id]->bPersonalEnchantItemSwitch == true) return; 
	if(pclCM->CR[id]->pclCI->GetPersonID() <= 0 ) return; // ����Ǿ��� �߸��� �Ŵ�.

	cltSplitItemInfo* pclinfo = (cltSplitItemInfo*)pclMsg->cData;


	cltItem* pclFrom = NULL;
	cltItem  clTo;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();


	SI32 slot = -1;

	// �������� �����͸� Ȯ���Ѵ�. 
	if(pclinfo->uiTo < 0	|| pclinfo->uiTo >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMSPLIT - PersonID = %d, IP =  %s , uiTo = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclinfo->uiTo
																	);
		return ;
	}	
	if(pclinfo->uiFrom < 0	|| pclinfo->uiFrom >= MAX_ITEM_PER_PERSON)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMSPLIT - PersonID = %d, IP =  %s , uiFrom = %d"),	
																	pclCM->CR[id]->pclCI->GetPersonID(),
																	pclCM->CR[id]->GetSession()->GetIP(),
																	pclinfo->uiFrom
																	);
		return ;
	}	

	if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->uiTo].siUnique > 0 )
	{
		// �������� ��ġ�� �������� �����Ѵٸ� Ȥ�� ����..����
		return;
	}
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->uiFrom].siItemNum < pclinfo->siCount )
	{
		// �������� ������ ������ ���� �������� ������..(�׷����� ��������..)
		return;
	}

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	pclFrom		= &pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->uiFrom];			

	// �������� ��ȿ�� ���̶��..
	if(pclFrom == NULL || pclFrom->siUnique <=0 ||pclFrom->siItemNum <= 0)
	{
		// ������ Ŭ���̾�Ʈ �� �� ������, �α׸� ��� ����.		
		if(pclFrom == NULL )
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMSPLIT - PersonID = %d, IP =  %s , pclFrom = NULL"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP()
																		);
		}
		else
		{
			pclLog->FilePrint(TEXT("Config\\Server-ItemMoveErr.log"), TEXT("DoMsg_GAMEMSG_REQUEST_ITEMSPLIT - PersonID = %d, IP =  %s , siUnique = %d,  siItemNum = %d"),	
																		pclCM->CR[id]->pclCI->GetPersonID(),
																		pclCM->CR[id]->GetSession()->GetIP(),
																		pclFrom->siUnique ,
																		pclFrom->siItemNum											
																		);
		}
		return ;
	}

	// Ʈ���̵����� ���� �ȵȴ�!
	if ( ((cltCharServer*)pclCM->CR[id])->GetNoMoveItemSwitch(pclinfo->uiFrom) != 0 )
	{
		return ;
	}

	cltItem clFrom;
	clFrom.Set(pclFrom);
	// ������ ������ŭ��!!
	clFrom.siItemNum = pclinfo->siCount;

	//-----------------------------------------------
	// To �� �ִ´�. 
	//-----------------------------------------------
	clTo.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->uiTo]);

	if (DistributePileMoveItem(id, clFrom, pclinfo->uiFrom, clTo, pclinfo->uiTo) == FALSE)		
	{
		bool Canpile = false;
		if(( pclFrom->CanPile(pclItemManager))&&( clTo.CanPile(pclItemManager)))
			Canpile = true;
		
		sDBRequest_MoveItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->uiFrom, &clFrom,Canpile,
			pclinfo->uiTo, &clTo);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
	}
}


//[�߰� : Ȳ���� 2007. 12. 11 => �ų� �̺�ư ��ư�� Ŭ���̾�Ʈ���� ���� ����. C->S]
void cltServer::DoMsg_GAMEMSG_REQUEST_NEWYEAR_CLICK(cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltItem clitem;
	ZeroMemory(&clitem, sizeof(clitem));
	clitem.siUnique  = 13316;
	clitem.siItemNum =	  1;
	
	if(siServiceArea == ConstServiceArea_Taiwan)
	{
		clitem.siItemNum = 3;
	}

	InputItem(pclchar, &clitem, INPUTITEMPERSON_OPTION_EVENT);
}

//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ���� ����Ʈ ��� �޽��� ó�� �Լ�. C->S]
void  cltServer::DoMsg_GAMEMSG_REQUEST_SPACE_BOX_LIST(cltMsg* pclMsg,SI32 id)
{
	cltMsg clMsg(GAMEMSG_REQUEST_SPACE_BOX_LIST, 0);
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ����(����) �޽��� ó�� �Լ�. ��� ����.��������.]
void  cltServer::DoMsg_GAMEMSG_REQUEST_TRESURE_BOX_LIST(cltMsg* pclMsg,SI32 id)
{
	cltMsg clMsg(GAMEMSG_REQUEST_TRESURE_BOX_LIST, 0);
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

}

//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���� ����. C->S]
void cltServer::DoMsg_GAMEMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Keep_Box_Move_Item* pclinfo = (cltGameMsgRequest_Keep_Box_Move_Item*)pclMsg->cData;
	
	// Ƽ���� ������ ������ �Ǵ� �ð��� ���ٸ�.
	if( ( false == pclCM->CR[id]->pclCI->clBI.bSpaceBoxPremiumService || 
		  0     == pclCM->CR[id]->pclCI->clBI.siSpaceBoxPremiumServiceDate ) &&		
		  false == pclinfo->m_bGacha)
	{
		SendServerResponseMsg(0, SRVAL_SPACE_BOX_TIME_OVER,  0, 0, pclCM->CR[id]->GetCharUnique()); 
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( NULL == pclchar )			return;
	if( pclchar->GetLife() <= 0)	return;
 
	if ( pclchar->bPremiumPersonalShop == true ) 
	{
		return	;
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. (ó������ ������ ����� �������� �ٽ� ������ �� �ִ�.) 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// ���� �������� ������ �����ϴ��� üũ 
	if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->m_siPos )
	{
		if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
		{
			SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
			return ;
		}
	}

	//----------------------------------------------
	// �κ��� ������ �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
	//----------------------------------------------
	SI32	 frompos	  = pclinfo->m_siPos;
	SI32	 MaxItemCount = 0;
	cltItem* pclitem	  = NULL;

	if( frompos < 0 || frompos >= MAX_ITEM_PER_PERSON )
		return;

	pclitem	= &pclCM->CR[id]->pclCI->clCharItem.clItem[frompos];

	// ��ƼȦ �������� ������ �� ����.
	if( pclitem->clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
		return;

	// ���� ���������� ���Ѵ�. ���� ������ �����Ͽ� ����ũ�θ� ���Ѵ�.
	cltItem clitem1;
	clitem1.Set(&pclinfo->m_KeepItem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(pclitem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)
		return ;

	// ������ �������� Ȯ���Ѵ�. 
	if(pclinfo->m_KeepItem.GetItemNum() > pclitem->GetItemNum())
		return ;
	
	//�Ⱓ�� �������� ��� ���� ���Ⱓ�� �ִ��� Ȯ���Ѵ�.
	SI32 itemunique = pclinfo->m_KeepItem.siUnique ;
	if ( itemunique > 0 )
	{
		if ( pclinfo->m_KeepItem.IsHaveUseDay() )  //[����] ���� ���Ⱓ ���� �˸�
		{
			SI32 useableDay = 0;
			BOOL rVal = GetItemUseAbleDay(&pclinfo->m_KeepItem,&useableDay);
			if(rVal == FALSE) return;

			if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
			{
				//KHY - 0723 - �Ⱓ������ �ı� ����.
				if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
				{
					return;	
				}
				else
				{
					// �Ⱓ�� ���� ���ǰ�� â�� ���� �� ����. - by LEEKH
					if( pclinfo->m_KeepItem.clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
					{
						// �޽��� ���
						return;
					}
					else
					{
						// ������ �������� �����ش�.
						sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),frompos,&pclinfo->m_KeepItem,USEITEM_REASON_DATEOVER);
						pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);


						cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclinfo->m_KeepItem.siUnique, useableDay);
						cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				
					}
					return;
				}
			}
		}
	}

	SI16		siBoxItemPos;
	cltItem     BoxItem;
	SI32		rtnvalue;

	cltItem*     pBoxitem = NULL;
	// ���� �������� ���� �������� Ȯ���Ͽ� �ִ� �������� ���� �ִ� ���� �ش� �����͸� ����.
	if( pclinfo->m_bGacha )
	{
		if(pclCM->CR[id]->pclTreasureBoxItem)	pBoxitem = &pclCM->CR[id]->pclTreasureBoxItem->clItem[0];
	}
	else
	{
		if(pclCM->CR[id]->pclSpaceBoxItem)		pBoxitem = &pclCM->CR[id]->pclSpaceBoxItem->clItem[0];
	}

	if(pBoxitem == NULL)		return;

	if(CanAddInv(pclinfo->m_bGacha, pBoxitem, pclClient->pclItemManager, INVMODE_ALL, &pclinfo->m_KeepItem, NULL, &siBoxItemPos, &BoxItem, &rtnvalue ) == false)
	{
		SendServerResponseMsg(0, SRVAL_SPACE_BOX_INVEN_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
		
		return;
	}  


	sDBRequest_Move_Item clMsg( DBMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM, 
								id, 
								pclCM->CR[id]->pclCI->GetPersonID(), 
								pclinfo->m_siPos, 
								&pclinfo->m_KeepItem, 
								siBoxItemPos, 
								&BoxItem, 
								pclinfo->m_bGacha, 
								pclinfo->m_KeepItem.CanPile( pclItemManager ) );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���� ȸ��. C->S]
void cltServer::DoMsg_GAMEMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Recovery_Box_Move_Item* pclinfo = (cltGameMsgRequest_Recovery_Box_Move_Item*)pclMsg->cData;
	
	//----------------------------------------------
	// �κ��� ������ �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
	//----------------------------------------------
	SI32	 frompos	  = pclinfo->m_siPos;
	SI32	 MaxItemCount = 0;
	cltItem* pclitem	  = NULL;

	if( frompos < 0 || frompos >= MAX_ITEM_PER_PERSON )		return;

	
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( NULL == pclchar )			return;
	if( pclchar->GetLife() <= 0)	return;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. (ó������ ������ ����� �������� �ٽ� ������ �� �ִ�.) 
	//---------------------------------------------
	pclchar->ItemUseReserveAction(); 

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// ���� �������� ���� �������� Ȯ���Ͽ� �ִ� �������� ���� �ִ� ���� �ش� �����͸� ����.
	if( pclinfo->m_bGacha )
	{
		MaxItemCount = MAX_ITEM_TREASURE_BOX;

		if(pclCM->CR[id]->pclTreasureBoxItem)	pclitem	= &pclCM->CR[id]->pclTreasureBoxItem->clItem[frompos];
	}
	else
	{
		MaxItemCount = MAX_ITEM_SPACE_BOX;

		if(pclCM->CR[id]->pclSpaceBoxItem)		pclitem	= &pclCM->CR[id]->pclSpaceBoxItem->clItem[frompos];
	}
	if(pclitem == NULL)							return;	

	if(frompos < 0 || frompos >= MaxItemCount)	return;


	// ���� ���������� ���Ѵ�. ���� ������ �����Ͽ� ����ũ�θ� ���Ѵ�.
	cltItem clitem1;
	clitem1.Set(&pclinfo->m_RecoveryItem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(pclitem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)return ;

	// ������ �������� Ȯ���Ѵ�. 
	if(pclinfo->m_RecoveryItem.GetItemNum() > pclitem->GetItemNum())return ;

	//�Ⱓ�� �������� ��� ���� ���Ⱓ�� �ִ��� Ȯ���Ѵ�.
	SI32 itemunique = pclinfo->m_RecoveryItem.siUnique ;
	if ( itemunique > 0 )
	{
		if ( pclinfo->m_RecoveryItem.IsHaveUseDay() )  //[����] ���� ���Ⱓ ���� �˸�
		{
			SI32 useableDay = 0;
			BOOL rVal = GetItemUseAbleDay(&pclinfo->m_RecoveryItem,&useableDay);
			if(rVal == FALSE) return;

			if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
			{
				//KHY - 0723 - �Ⱓ������ �ı� ����.
				if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
				{
					return;	
				}
				else
				{
					// �Ⱓ�� ���� ���ǰ�� �������ڿ��� ���� �ְ��Ѵ�.
					if( pclinfo->m_RecoveryItem.clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
					{
						//
						//return;
					}
					else
					{
						// ������ �������� �����ش�.
						/*sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),frompos,&pclinfo->m_RecoveryItem,USEITEM_REASON_DATEOVER);
						pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);*/

						sDBRequest_Use_SpaceBox_Item useitem(id,pclCM->CR[id]->pclCI->GetPersonID(), frompos, &pclinfo->m_RecoveryItem, USEITEM_REASON_DATEOVER);
						pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);


						cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclinfo->m_RecoveryItem.siUnique, useableDay);
						cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				
						return;
					}
				}
			}
		}
	}

	SI16		InvenItemPos;
	cltItem		InvenItem;
	SI32		rtnvalue;
	
	//cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	if(false == pclchar->CanAddInv(INVMODE_ALL, &pclinfo->m_RecoveryItem, &InvenItemPos, &InvenItem, &rtnvalue))
	{
		SendServerResponseMsg(0, SRVAL_SPACE_BOX_INVEN_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());

		return; 
	}

	sDBRequest_Move_Item clMsg( DBMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM, 
								id, 
								pclCM->CR[id]->pclCI->GetPersonID(), 
								InvenItemPos, 
								&InvenItem, 
								pclinfo->m_siPos, 
								&pclinfo->m_RecoveryItem, 
								pclinfo->m_bGacha, 
								pclinfo->m_RecoveryItem.CanPile( pclItemManager ) );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

// [�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� �޽���. C->S ]
void cltServer::DoMsg_GAMEMSG_REQUEST_ARTIFACT_MIXTURE(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Artifact_Mixture* pclinfo = (cltGameMsgRequest_Artifact_Mixture*)pclMsg->cData;

	// ������ ������ ���������� �˻�.
	BOOL bResult= pclClient->pclItemManager->CanCrystalMixtureData( &pclinfo->m_clEquipItem, pclinfo->m_clCrystalItem ,pclinfo->m_siEquipItemPos);
	switch( bResult )
	{
		case cltItemManagerCommon::NO_ITEM_UNIQUE:	
		case cltItemManagerCommon::NO_SLOT_ITEM:
		case cltItemManagerCommon::NO_USED_SLOT:
		case cltItemManagerCommon::NO_CRYSTAL:		
		case cltItemManagerCommon::ALREADY_USE_SLOT:	
		case cltItemManagerCommon::SAME_CRYSTAL:
		case cltItemManagerCommon::LIMIT_CRYSTAL_ABILITY:		return; 
	}

	// ������ �ƴϸ� ������ ����~
	if(cltItemManagerCommon::POSSIBLE != bResult)
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_ARTIFACT, 0, 0, id ); 
		return; 
	}

	cltCrystalItem* pEquipCristalInfo	= NULL;
	cltItem*		pCristalItemInfo	= NULL;			

	for(SI32 Count = 0; Count < pclinfo->m_clEquipItem.siUseCrystalNum; ++Count )
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü. - �ɷ��� ��ø���� �־�� �Ѵ�.
		if(( pclinfo->m_clCrystalItem[Count].siUnique > 0 ) 
			&&( pclClient->pclItemManager->IsItemInfoAtb(pclinfo->m_clCrystalItem[Count].siUnique,ITEMINFOATB_CRYSTAL_AVATAR) == true))
		{
			pEquipCristalInfo	= &pclinfo->m_clEquipItem.cltItemCrytal[Count];	
			pCristalItemInfo	= &pclinfo->m_clCrystalItem[Count];

			// �ƹ�Ÿ ����ü��  - �ɷ�ġ�� ���ƾ� �ϸ�, �������� �������, �ɷ�ġ�� ��ø�Ǿ�� �Ѵ�.
			if((pEquipCristalInfo->siCrystalType == 0 )
			 ||(pEquipCristalInfo->siCrystalType == pCristalItemInfo->siUnique))
			{
				pEquipCristalInfo->siCrystalType	   = pCristalItemInfo->siUnique;				 // Crystal Unique

				// �������� ���������, ���� �������� �־�� ������.
				pEquipCristalInfo->siDurability		   = pCristalItemInfo->GetCrystalMaxDurability(); 
				pEquipCristalInfo->siMaxDurability     = pCristalItemInfo->GetCrystalMaxDurability();

				// �������� Ÿ�԰� ����ü�� �ɷ¿� ���� �ִ밪�� �ٸ���.
				SI32 maxAvatarCrystalAbility = pclClient->pclItemManager->GetMaxAbatarCrystalAbilityNum(pclinfo->m_clEquipItem.GetType(pclItemManager) , pCristalItemInfo->GetCrystalAbility());

				// 0 �̶�� �߸��� ����ü��.
				if(maxAvatarCrystalAbility > 0)
				{
					pEquipCristalInfo->uiCrystalAbility    = pCristalItemInfo->GetCrystalAbility();
					pEquipCristalInfo->uiCrystalAbilityNum += pCristalItemInfo->GetCrystalAbilityNum(); //����.

					// Ŭ���̾�Ʈ���� �˻��ؼ� ����������.
					if(pEquipCristalInfo->uiCrystalAbilityNum > maxAvatarCrystalAbility)
					{
						pEquipCristalInfo->uiCrystalAbilityNum = maxAvatarCrystalAbility;
						return;
					}					
				}
				else
					return;
				
			}
		}		
		//KHY - 0805 - ��Ʈ�彺 ����. - ����ü�� �ְ�, �� �ɷ��� ���� ������ ���� ��쿡�� ������ش�.
		else if(( pclinfo->m_clCrystalItem[Count].siUnique > 0 ) &&( pclinfo->m_clCrystalItem[Count].clItemCrystal.GetCrystalAblilty() == 0 ))
		{
			pclClient->pclItemManager->MakeCrystal(&pclinfo->m_clCrystalItem[Count],0);

			pEquipCristalInfo	= &pclinfo->m_clEquipItem.cltItemCrytal[Count];	
			pCristalItemInfo	= &pclinfo->m_clCrystalItem[Count];
			
			pEquipCristalInfo->siCrystalType	   = pCristalItemInfo->siUnique;				 // Crystal Unique
			pEquipCristalInfo->siDurability		   = pCristalItemInfo->GetCrystalMaxDurability(); 
			pEquipCristalInfo->siMaxDurability     = pCristalItemInfo->GetCrystalMaxDurability();
			pEquipCristalInfo->uiCrystalAbility    = pCristalItemInfo->GetCrystalAbility();
			pEquipCristalInfo->uiCrystalAbilityNum = pCristalItemInfo->GetCrystalAbilityNum();
		}
		else if( pclinfo->m_clCrystalItem[Count].siUnique > 0)
		{
			pEquipCristalInfo	= &pclinfo->m_clEquipItem.cltItemCrytal[Count];	
			pCristalItemInfo	= &pclinfo->m_clCrystalItem[Count];
			
			pEquipCristalInfo->siCrystalType	   = pCristalItemInfo->siUnique;				 // Crystal Unique
		
			// �ɷ�ġ�� �پ��ִ� ����ü �ϰ�� �κ��丮 ���� ��ȣ�� ��ȿ���� üũ�Ѵ�
			if ( (PERSONITEM_INV0 <= pclinfo->m_siCrystalItemPos[Count]) && (MAX_ITEM_PER_PERSON > pclinfo->m_siCrystalItemPos[Count]) )
			{
				pEquipCristalInfo->siDurability		= pCristalItemInfo->GetCrystalMaxDurability();
			}

			pEquipCristalInfo->siMaxDurability		= pCristalItemInfo->GetCrystalMaxDurability();
			pEquipCristalInfo->uiCrystalAbility		= pCristalItemInfo->GetCrystalAbility();
			pEquipCristalInfo->uiCrystalAbilityNum	= pCristalItemInfo->GetCrystalAbilityNum();

			// ������ ��ġ�� 0 �� ���( �̹� ���յ� ����ü)�� ���� �ʱ�ȭ �����ش�.
			if(pclinfo->m_siCrystalItemPos[Count] == 0)
				pclinfo->m_clCrystalItem[Count].Init();
		}
		else
		{
			pclinfo->m_clCrystalItem[Count].Init();
		}
	}
	
	sDBRequest_Artifact_Mixture clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(),  pclinfo->m_siEquipItemPos,		&pclinfo->m_clEquipItem,
																			     pclinfo->m_siCrystalItemPos,    pclinfo->m_clCrystalItem );

	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

// [�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� �޽���. C->S ]
void cltServer::DoMsg_GAMEMSG_REQUEST_ARTIFACT_REMOVE(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Artifact_Remove* pclinfo = (cltGameMsgRequest_Artifact_Remove*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	
	// ������ �ִ� �������ΰ�.
	BOOL bResult = pclClient->pclItemManager->CanCrystalRemoveData( &pclinfo->m_clEquipItem, pclinfo->m_bRemoveSlotIndexList, pclinfo->m_clCrystalItemList );
	switch( bResult )	
	{
		case cltItemManagerCommon::NO_ITEM_UNIQUE:
		case cltItemManagerCommon::NO_SLOT_ITEM:
		case cltItemManagerCommon::NO_CRYSTAL_SLOT:
		case cltItemManagerCommon::NO_REMOVE_CRYSTAL:	return;
	}

	// ������ �ƴϸ� ������ ����~
	if(cltItemManagerCommon::POSSIBLE != bResult)
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_ARTIFACT, 0, 0, id );
		return; 
	}

	SI16	clCreateCrystalPos[ MAX_CRYSTAL_NUM ];
	ZeroMemory( clCreateCrystalPos, sizeof( clCreateCrystalPos ) );

	cltItem clCreateCrystal[ MAX_CRYSTAL_NUM ];
	ZeroMemory( clCreateCrystal,	   sizeof( clCreateCrystal ) );

	SI32 DeleteItemPos[MAX_CRYSTAL_NUM];
	ZeroMemory(DeleteItemPos, sizeof(DeleteItemPos));

	SI32 ItemUnique		 = 0; 
	SI32 SaveItemSlotNum = 0;
	SI16 brareswitch	 = 0;
	SI16 NewDurability	 = 0;
	
	// ������ �ִ�ġ�� ������ 30000 �̴�.
	const SI16 ConstCrystalDurability = 30000;
	SI32 CreateSlotCount = 0;
	
	for( SI32 Count = 0; Count < MAX_CRYSTAL_NUM; ++Count )
	{
		//KHY - 0805 - ��Ʈ�彺 ����.
		if(pclinfo->m_clCrystalItemList[Count].siUnique == ITEMUNIQUE(1803)) // ������ ����ü ���.
		{
			if( true == pclinfo->m_bRemoveSlotIndexList[Count] )
			{
				ItemUnique = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetCrystalType();
				if( 0 < ItemUnique )
				{
					if( false == pclItemManager->MakeRandItemUnique( ItemUnique, &clCreateCrystal[ SaveItemSlotNum ], 0, 0, &brareswitch ) ) 
					{
						continue;		
					}
								
					// ���ο� ������ ����. ���� ���������� �ִ� �������� 10%�� ���� �������� ������ �ִ� �������� �����Ѵ�.
					NewDurability = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetMaxDurability() - ( ConstCrystalDurability / 10 );
					if( 3000 > NewDurability	)
					{
						// 3000�� ����ü ���Ž� �����Ǵ� ������ ���� ������.
						NewDurability = 3000;
					}
					clCreateCrystal[ SaveItemSlotNum ].clItemCrystal.SetMaxDurability(NewDurability);
					clCreateCrystal[ SaveItemSlotNum ].clItemCrystal.uiCrystalAbility    = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetCrystalAblilty();
					clCreateCrystal[ SaveItemSlotNum ].clItemCrystal.uiCrystalAbilityNum = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetCrystalAbilityNum();
					
					//  ������ ����ü�� ����ϸ�,����ü�� �����Ѵ�. - �κ� ��ġ ����.
					SI16 invpos;
					cltItem cltoitem;
					SI32 rtnvalue;
					
					if(pclchar->CanAddInv(INVMODE_ALL, &clCreateCrystal[ SaveItemSlotNum ], &invpos, &cltoitem, &rtnvalue) == false)
					{
						((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_CANNOTINPUTTOINV, 0, 0, id);
							return ;
					}
					else				
					{
						// �ϳ����� ����� �� �� �ִ�.  - ��ġ���� ��Ⱑ �ָ��ؼ�.	
						clCreateCrystalPos[CreateSlotCount] = invpos;
						++CreateSlotCount;							
						/*
						// �̹� ���õ� �κ����� ���� �ִ��� �˻��Ѵ�.
						bool check = true;
						for(SI32 x = 0; x < MAX_CRYSTAL_NUM ;x++)
						{
							if(clCreateCrystalPos[x] == invpos)
								check = false;
						}

						if(check == true)
						{
							clCreateCrystalPos[CreateSlotCount] = invpos;
							++CreateSlotCount;							
						}
						*/
					}

					++SaveItemSlotNum;	// ���� ���Կ� �����ϰ�...
				}
				
				ZeroMemory(&pclinfo->m_clEquipItem.cltItemCrytal[Count], sizeof(pclinfo->m_clEquipItem.cltItemCrytal[Count]));
			}
		}
		else if(pclinfo->m_clCrystalItemList[Count].siUnique == ITEMUNIQUE(1804)) // ������ ����ü ���.
		{
			if( true == pclinfo->m_bRemoveSlotIndexList[Count] )
			{
				ItemUnique = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetCrystalType();
				if( 0 < ItemUnique )
				{
					if(pclinfo->m_clEquipItem.cltItemCrytal[Count].GetMaxDurability() <= 1500) // ������ 5 ���϶��, 
					{
						SendServerResponseMsg( 0, SRVAL_FAIL_ARTIFACT, 0, 0, id );
						return; 
					}
						
					// ���ο� ������ ����. ���� ���������� �ִ� �������� 5%�� ���� �������� ������ �ִ� �������� �����Ѵ�.
					NewDurability = pclinfo->m_clEquipItem.cltItemCrytal[Count].GetMaxDurability() - ( ConstCrystalDurability / 20 );

					pclinfo->m_clEquipItem.cltItemCrytal[Count].SetMaxDurability(NewDurability);
					pclinfo->m_clEquipItem.cltItemCrytal[Count].SetDurability(NewDurability);					
				}
			}
		}
	}


	sDBRequest_Artifact_Remove clMsg(  id,  
									   pclCM->CR[id]->pclCI->GetPersonID(), 
									   pclinfo->m_siEquipItemPos, 
									  &pclinfo->m_clEquipItem,
									   pclinfo->m_siCrystalItemPosList,
									   pclinfo->m_clCrystalItemList,
									   clCreateCrystalPos, 
									   clCreateCrystal							);	
	
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );   
}

// [�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���Ի��� �޽���. C->S ]
void cltServer::DoMsg_GAMEMSG_REQUEST_ARTIFACT_SLOT_CREATE(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Artifact_Slot_Create* pclinfo = (cltGameMsgRequest_Artifact_Slot_Create*)pclMsg->cData;

	// ������ ��ġ ���� ����.
	if( pclinfo->m_siCrystalItemPos < 0 || pclinfo->m_siCrystalItemPos >= MAX_ITEM_PER_PERSON || 
	 	pclinfo->m_siEquipItemPos   < 0 || pclinfo->m_siEquipItemPos   >= MAX_ITEM_PER_PERSON	) 
	{
		return ;
	}

	BOOL bResult = pclClient->pclItemManager->CanCrystalSlotCreateData( &pclinfo->m_clEquipItem, &pclinfo->m_clCrystalItem );
	switch( bResult )	
	{
		case cltItemManagerCommon::NO_ITEM_UNIQUE:
		case cltItemManagerCommon::NO_SLOT_ITEM:
		case cltItemManagerCommon::USE_CRYSTAL_SLOT:
		case cltItemManagerCommon::NO_CRYSTAL:			return; 
	}

	// ������ �ƴϸ� ������ ����~
	if(cltItemManagerCommon::POSSIBLE != bResult)
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_ARTIFACT, 0, 0, id );
		return; 
	}

	SI32	ref			  = pclItemManager->FindItemRefFromUnique(pclinfo->m_clEquipItem.siUnique);	
	if(0 >= ref)
		return;

	SI32 siLevel		= pclItemManager->pclItemInfo[ref]->clCondition.siLevel;
	SI32 oldCrystalNum	= pclinfo->m_clEquipItem.GetUseCrystalNum(); // ���� ������ �ִ�, ���Լ�.
	SI32 temCrystalNum	= 0;
	cltItem clOldItem;	clOldItem.Set(&pclinfo->m_clEquipItem);

	if(pclinfo->m_clCrystalItem.siUnique == ITEMUNIQUE(1801)) //���� ����ü
	{	
		SI32 temnum = 0;
		if((siLevel >= 1)&&(siLevel <= 29))
		{
			temCrystalNum = 1;
			
			// ������Ų��.
			temnum = pclinfo->m_clEquipItem.siUseCrystalNum + temCrystalNum;
			temCrystalNum = min(2, temnum);
		}
		else if((siLevel >= 30)&&(siLevel <= 59))
		{
			temCrystalNum = 1 + rand()%2;

			// ������Ų��.
			temnum = pclinfo->m_clEquipItem.siUseCrystalNum + temCrystalNum;
			temCrystalNum = min(3, temnum);
		}
		else if((siLevel >= 60)&&(siLevel <= 89))
		{
			temCrystalNum = 1 + rand()%3;

			// ������Ų��.
			temnum = pclinfo->m_clEquipItem.siUseCrystalNum + temCrystalNum;
			temCrystalNum = min(4, temnum);
		}
		else if(siLevel >= 90)
		{
			temCrystalNum = 1 + rand()%4;

			// ������Ų��.
			temnum = pclinfo->m_clEquipItem.siUseCrystalNum + temCrystalNum;
			temCrystalNum = min(5, temnum);
		}

		pclinfo->m_clEquipItem.siUseCrystalNum = temCrystalNum;
	}
	else if(pclinfo->m_clCrystalItem.siUnique == ITEMUNIQUE(1802)) // ���� ����ü[S]
	{
		if((siLevel >= 1)&&(siLevel <= 29))
		{
			temCrystalNum =  oldCrystalNum + rand()%2;
			temCrystalNum = min(2, temCrystalNum);
		}
		else if((siLevel >= 30)&&(siLevel <= 59))
		{
			temCrystalNum = oldCrystalNum + rand()%3;
			temCrystalNum = min(3, temCrystalNum);
		}
		else if((siLevel >= 60)&&(siLevel <= 89))
		{
			temCrystalNum = oldCrystalNum + rand()%4;
			temCrystalNum = min(4, temCrystalNum);
		}
		else if(siLevel >= 90)
		{
			temCrystalNum = oldCrystalNum + rand()%5;
			temCrystalNum = min(5, temCrystalNum);
		}

		// ������Ű�� �ʴ´�.
		pclinfo->m_clEquipItem.siUseCrystalNum =  temCrystalNum;
	}
	
	// ���Կ� �ִ� ��� ����ü�� ���������.
	ZeroMemory(&pclinfo->m_clEquipItem.cltItemCrytal, sizeof(pclinfo->m_clEquipItem.cltItemCrytal));
			
	sDBRequest_Artifact_Slot_Create clMsg(	id, 
											pclCM->CR[id]->pclCI->GetPersonID(),
											pclinfo->m_siEquipItemPos,
										   &pclinfo->m_clEquipItem,
											pclinfo->m_siCrystalItemPos,
										   &pclinfo->m_clCrystalItem,
										   &clOldItem		);

	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_OPENBIGITEMBOX(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_OpenBigItemBox* pclinfo = (cltGameMsgRequest_OpenBigItemBox*)pclMsg->cData;

	const SI32 siMax_Item_Count = 100;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltItem clOutPutItem;
	clOutPutItem.Init();
	SI16 brareswitch = 0;

	cltUniqueRange* pGrade = NULL;
	SI32 siGradeCount = 0;

	// ���� ������ ����
	if ( pclinfo->m_clKeyItem.siUnique == ITEMUNIQUE(8113) )		
	{
		pGrade = (cltUniqueRange*)ItemUnique_8113_Grade;		siGradeCount = sizeof(ItemUnique_8113_Grade) / sizeof(cltUniqueRange);
	}
	else if	( pclinfo->m_clKeyItem.siUnique == ITEMUNIQUE(13621) )
	{
		pGrade = (cltUniqueRange*)ItemUnique_13621_Grade;	siGradeCount = sizeof(ItemUnique_13621_Grade) / sizeof(cltUniqueRange);	
	}

	if( pGrade == NULL || siGradeCount <= 0)			
		return;

	SI32 siGrade = GetUniqueWithRange( pGrade, siGradeCount, 100);

	//----------------------------------------------------------------------------------------------------
	// 1 ��� ������ ����
	//----------------------------------------------------------------------------------------------------
	cltValuesRange BigItemBox_1_Grade[siMax_Item_Count] = 
	{
		// �ۼ�Ʈ,		����ũ,			����,			�Ⱓ.
		{   5,		5350,				1,				0 }	
		,{   5,		5355,				1,				0 }	
		,{   5,		5360,				1,				0 }	
		,{   5,		5365,				1,				0 }	
		,{   5,		5370,				1,				0 }
		,{   5,		5410,				1,				0 }	
		,{   5,		2757,				1,				0 }
		,{   5,		5400,				1,				0 }
		,{   4,		3890,				1,				0 }	
		,{   4,		3899,				1,				0 }	
		,{   3,		5600,				1,				0 }	
		,{  10,		24111,				1,				0 }	
		,{   3,		2740,				1,				0 }	
		,{   5,		24040,				1,				0 }	
		,{   5,		24094,				1,				0 }	
		,{   1,		15900,				1,			   30 }	
		,{   1,		13621,				1,				0 }	
		,{   1,		24098,				1,				0 }	
		,{   1,		2760,				1,				0 }	
		,{   1,		5710,				1,				0 }	
		,{   1,		5715,				1,				0 }	
		,{   1,		5412,				1,				0 }	
		,{   0,		   0,				0,				0 }	
	};
	SI32 BigItemBox_1_Grade_Count = 0;
	for(SI32 i=0; i<siMax_Item_Count; i++)
	{
		if( BigItemBox_1_Grade[i].siPercent <= 0 )			break;
		BigItemBox_1_Grade_Count++;
	}

	if( IsCountrySwitch( Switch_Artifact ) )
	{
		//,{   9,		2756,				1,				0 }	
		//,{   8,		2710,				1,				0 }	
		//,{   1,		1803,				1,				0 }	
		//,{   1,		1801,				1,				0 }	

		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(9, 2756, 1, 0);		BigItemBox_1_Grade_Count++;
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(8, 2710, 1, 0);		BigItemBox_1_Grade_Count++;
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(1,	1803, 1, 0);		BigItemBox_1_Grade_Count++;
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(1,	1801, 1, 0);		BigItemBox_1_Grade_Count++;
		// ������ üũ ����
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(0,	   0, 0, 0);		BigItemBox_1_Grade_Count++;
	}
	else
	{
		//,{  10,		2756,				1,				0 }	
		//,{   9,		2710,				1,				0 }	
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set(10, 2756, 1, 0);		BigItemBox_1_Grade_Count++;
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set( 9, 2710, 1, 0);		BigItemBox_1_Grade_Count++;
		// ������ üũ ����
		BigItemBox_1_Grade[BigItemBox_1_Grade_Count].Set( 0,	0, 0, 0);		BigItemBox_1_Grade_Count++;
	}
	//----------------------------------------------------------------------------------------------------
	// 1 ��� ������ ���� �������
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// 2 ��� ������ ����
	//----------------------------------------------------------------------------------------------------
	// "��ڻ���"���� ������ ������ ����ũ 
	cltValuesRange  BigItemBox_2_Grade[siMax_Item_Count] = 
	{
		// �ۼ�Ʈ,		����ũ,			����,			�Ⱓ.
		{   20,		3895,				1,				0 }	
		,{   19,		3901,				1,				0 }	
		,{	  1,		13605,				1,				0 } // ��íŰ����
		,{   10,		15910,				1,				7 }	
		,{   10,		13621,				1,				0 }	
		,{   50,		2715,				1,				0 }
		,{   50,		2720,				1,				0 }	
		,{   40,		3880,				1,				0 }
		,{  200,		24082,				1,				0 }
		,{   20,		5380,				1,				0 }	
		,{   20,		7175,				1,				0 }	
		,{   20,		6140,				1,				0 }	
		,{   70,		2672,				1,				0 }	
		,{   70,		2705,				1,				0 }	
		,{   50,		3855,				1,				0 }	
		,{  100,		24075,				1,				0 }	
		,{   50,		2781,				1,				0 }	
		,{   50,		2782,				1,				0 }	
		,{   50,		2635,				1,				0 }	
		,{   50,		24020,				1,				0 }	
		,{   50,		2730,				1,				0 }	
	};

	SI32 BigItemBox_2_Grade_Count = 0;
	for ( SI32 siIndex=0; siIndex<siMax_Item_Count; siIndex++ )
	{
		if( BigItemBox_2_Grade[siIndex].siPercent <= 0 )
		{
			break;
		}
		BigItemBox_2_Grade_Count++;
	}

	// ��Ÿ���� �ǸŽ� ��Ÿ�������� �������� ��
	if ( pclEventTimeManager->InEventTime(TEXT("SantaBoxPiece"), &sTime) )
	{
		BigItemBox_2_Grade[BigItemBox_2_Grade_Count++].Set(1, 8124, 1, 0);	// ��Ÿ���� ����
	}

	// ���� ���� ���� ����ũ
	if ( pclEventTimeManager->InEventTime(TEXT("RandomBoxPiece"), &sTime) )
	{
		SI32 siRandomBoxPieceUnique = (SI32)GetGlobalValue( TEXT("GV_RandomBoxPieceUnique") );
		if ( 0 < siRandomBoxPieceUnique )
		{
			BigItemBox_2_Grade[BigItemBox_2_Grade_Count++].Set(1, siRandomBoxPieceUnique, 1, 0);	// ��Ÿ���� ����
		}
	}

	// ### ������ 0,0,0,0 �� �������� �Ѵ� ���ο���� �߰��� �߰��ϰ� �ʹٸ� ������ �Ѵ� ###
	BigItemBox_2_Grade[BigItemBox_2_Grade_Count].Set( 0,0,0,0 );
	//----------------------------------------------------------------------------------------------------
	// 2 ��� ������ ���� �������
	//----------------------------------------------------------------------------------------------------

	cltValuesRange* pValues = NULL;
	switch(siGrade)
	{
	case 1:		pValues = GetValues(BigItemBox_1_Grade);																	break;
	case 2:		pValues = GetValues(BigItemBox_2_Grade);																	break;
	case 3:		pValues = GetValuesWithRange(BigItemBox_3_Grade, sizeof(BigItemBox_3_Grade)/sizeof(cltValuesRange), 100);	break;
	}
	if( pValues == NULL )
		return;

	SI32 siItemUnique	= pValues->siPara1;
	SI32 siItemNum		= pValues->siPara2;
	SI32 usedate		= 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siItemUnique);
	if( ref < 0 )				return;

	if( pValues->siPara3 > 0 )
		usedate = pValues->siPara3;
	else
		usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

	if( pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate ) == false )
		return;

	//---------------------------------------------------------
	// ��ڻ��ڿ��� ������ ��ǰ�� �ٽ� �к���Ų��.
	clOutPutItem.uiDateYear	 = 0;
	clOutPutItem.uiDateMonth = 0;
	clOutPutItem.uiDateDay	 = 0;
	//---------------------------------------------------------

	clOutPutItem.SetItemNum(siItemNum);

	// �κ��丮 �� ���� üũ
	if( pclchar->IsBlankInv(1,INVMODE_ALL) == false )
	{
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 1, 0, pclchar->GetID());
		return;
	}

	cltItem cltoitem;
	SI16	invpos;

	// ������ ����
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &clOutPutItem, &invpos, &cltoitem, &rtnvalue) == false)
	{
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, pclchar->GetID());
		return;
	}
	else
	{
		if(invpos >= PERSONITEM_INV0 && invpos < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON)
		{
			pclchar->SetInputItemReserve( invpos , pclClient->CurrentClock );
		}
		else
		{
			return;
		}
	}

	// ����� 1��޸� �α׸� ��´�.
	if(siGrade == 1)
		pclClient->pclLog->FilePrint(TEXT("Config\\BigItemBoxGet.Txt"), 
					TEXT("RareItem(Grade:%d) Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d] / Use Key Unique : \t[%d]"), 
					siGrade, pclCM->CR[id]->GetName(), clOutPutItem.siUnique, clOutPutItem.siItemNum, pclinfo->m_clKeyItem.siUnique );

	sDBRequest_OpenTreasureBox clMsg( pclchar->pclCI->GetPersonID(), pclinfo->m_siBoxPos, &pclinfo->m_clBoxItem, pclinfo->m_siKeyPos, &pclinfo->m_clKeyItem, invpos, &clOutPutItem, pclItemManager->CanPile(clOutPutItem.siUnique), clOutPutItem.IsCreateSID(pclItemManager), false );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONPUSHITEM(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	// �⺻���� �����˻�
	//---------------------------------------------
	// �����ÿ��� �̵� �Ұ�
	if ( 0 < pclCM->CR[id]->siPersonalMakeItemType)
	{
		return;
	}

	// ��þƮ�ÿ��� �̵� �Ұ�
	if ( true == pclCM->CR[id]->bPersonalEnchantItemSwitch )
	{
		return; 
	}

	cltGameMsgRequest_SummonPushItem* pclSummonMoveItemInfo = (cltGameMsgRequest_SummonPushItem*)pclMsg->cData;
	if ( NULL == pclSummonMoveItemInfo )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( NULL == pclchar )
	{
		return;
	}

	//---------------------------------------------
	// ���־��� ���� ����
	//---------------------------------------------
	SI32		siPersonID		= pclchar->pclCI->GetPersonID();
	SI32		siSummonIndex	= pclSummonMoveItemInfo->m_siSummonIndex;
	UI16		uiFrom			= pclSummonMoveItemInfo->m_uiFrom;
	UI16		uiTo			= pclSummonMoveItemInfo->m_uiTo;

	cltItem*	pclFrom			= NULL;
	cltItem		clTo;

	// �߸��� ��ȯ�� ��ȣ�� ��������
	if ( (0 >siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	cltSummon* pclsummon = (cltSummon*)pclchar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if ( NULL == pclsummon )
	{
		return;
	}
	
	// ��ȯ�� ���°� �ƴ϶�� 
	if ( pclsummon->siStatus != SUMMON_STATUS_TAKEOUT )
	{
		return;
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();


	//---------------------------------------------
	// ������ ���� �˻�
	//---------------------------------------------

	// ��ȯ�� �κ� �˻�
	if ( (0 > uiTo)					|| (MAX_SHAPE_ITEM <= uiTo)			)	return;
	// ��� �κ� �˻�( ������� ���°��̱� ������ ��� ĭ�� ���Ե��� �ʴ´� )
	if ( (MAX_SHAPE_ITEM > uiFrom)	|| (MAX_ITEM_PER_PERSON <= uiFrom)	)	return;
	

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �̵� �ȵȴ�.
	if( pclchar->bPersonalShopSwitch == true  && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == uiFrom	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			// �ͼ����� ���λ���
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == uiTo	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}
	}	// if( pclchar->bPersonalShopSwitch == true  && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL) ����

	//--------------------------------------------
	//Ʈ���̵����� ���� �ȵȴ�!
	//--------------------------------------------
	if ( 0 != pclchar->GetNoMoveItemSwitch( uiFrom ) )
	{
		return;
	}

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	pclFrom = &pclchar->pclCI->clCharItem.clItem[uiFrom];
	
	// �������� ��ȿ�� ���̶��..
	if ( (NULL == pclFrom) || (0 >= pclFrom->siUnique) )
	{
		return;
	}

	//-----------------------------------------------
	// To �� �ִ´�. 
	//-----------------------------------------------
	if ( NULL == pclchar->pclCI->clSummonInfo.GetSummonEquipItem( siSummonIndex, uiTo ) )
	{
		return;
	}
	clTo.Set( pclchar->pclCI->clSummonInfo.GetSummonEquipItem(siSummonIndex, uiTo) );


	//------------------------------------------
	// ���� ������ ������Ű���� Ȯ���Ѵ�. 
	//------------------------------------------
	// ���� ������ �����ġ���� �˻�
	if ( false == pclItemManager->IsCanEquipItemPosForSummon( uiTo, pclFrom->siUnique ) )
	{
		return;
	}

	// �������� ���� �����δ� �̵���ų �� ����. 
	if ( false == pclItemManager->CheckProperItemPos(pclFrom, uiTo, pclsummon->siKind) )
	{
		return ;
	}

	SI32 siSummonID = pclchar->GetSummonID();
	if ( false == pclCM->IsValidID(siSummonID) )
	{
		return;
	}

	cltCharCommon* pclSummonChar = pclCM->CR[ siSummonID ];
	if ( NULL == pclSummonChar )
	{
		return;
	}

	// �ش� �������� ������ �� �ִ� �ɷ��� �ִ��� �˻�	
	SI32		siDummy		= 0;
	cltItem*	pclItemList = pclchar->pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex );
	if ( NULL == pclItemList )
	{
		return;
	}

	if ( false == pclItemManager->CheckConditionForSummon( pclCM->CR[id], pclFrom->siUnique, pclsummon, pclItemList, &siDummy) )
	{
		return;
	}


	//------------------------------------------
	// �к����� �������� �����Ұ� 
	//------------------------------------------
	if ( true == pclFrom->IsSealingUp(pclItemManager) )
	{
		return;
	}
	// �Ⱓ�� ���� �������� �����Ұ� - by LEEKH	
	SI32 siUseableDay;
	BOOL rVal			= GetItemUseAbleDay( pclFrom, &siUseableDay );
	
	if ( (TRUE == rVal) && (0 > siUseableDay) )
	{
		return;
	}

	cltItem clitem;
	clitem.Set(pclFrom);


	//-----------------------------------------------
	// �߻�ü �������϶� ���� ����
	//-----------------------------------------------
	if ( (TRUE == clitem.IsBulletItem()) && ( (clTo.siUnique == clitem.siUnique) || (DEFAULT_EQUIP_BULLET_NUMBER < clitem.siItemNum) ) )
	{
		if ( DEFAULT_EQUIP_BULLET_NUMBER < (clTo.siItemNum + clitem.siItemNum) )
		{
			clitem.siItemNum = (DEFAULT_EQUIP_BULLET_NUMBER - clTo.siItemNum);
		}
	}

	if ( 0 >= clitem.siItemNum )
	{
		return;
	}

	sDBRequest_SummonPushItem clMsg( id, siPersonID, pclsummon->siSummonID, uiFrom, &clitem, pclFrom->CanPile(pclItemManager), uiTo, &clTo );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONPOPITEM(cltMsg* pclMsg, SI32 id)
{
	// ����� �ش�ȴ�
	if ( false == IsPC(id) )
	{
		return;
	}

	// �����ÿ��� �̵� �Ұ�
	if ( 0 < pclCM->CR[id]->siPersonalMakeItemType)
	{
		return;
	}

	// ��þƮ�ÿ��� �̵� �Ұ�
	if ( true == pclCM->CR[id]->bPersonalEnchantItemSwitch )
	{
		return; 
	}

	cltGameMsgRequest_SummonPopItem* pclSummonPopItemInfo = (cltGameMsgRequest_SummonPopItem*)pclMsg->cData;
	if ( NULL == pclSummonPopItemInfo )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( NULL == pclchar )
	{
		return;
	}

	SI32		siPersonID		= pclchar->pclCI->GetPersonID();
	SI32		siSummonIndex	= pclSummonPopItemInfo->m_siSummonIndex;
	UI16		uiFrom			= pclSummonPopItemInfo->m_uiFrom;
	UI16		uiTo			= pclSummonPopItemInfo->m_uiTo;

	cltItem*	pclFrom			= NULL;
	cltItem		clTo;

	// �߸��� ��ȯ�� ��ȣ�� ��������
	if ( (0 >siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	cltSummon*	pclsummon = pclchar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if(pclsummon == NULL)			return;

	if ( pclsummon->siStatus != SUMMON_STATUS_TAKEOUT )
	{
		return;
	}
	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();


	// ��ȯ������ ������Է� �̵��� ���
	if ( (0 > uiTo)		|| (MAX_ITEM_PER_PERSON <= uiTo)	)	return;
	if ( (0 > uiFrom)	|| (MAX_SHAPE_ITEM <= uiFrom)		)	return;

	//------------------------------------------------
	// ���� ���� ���� ������ �� �κ��� ���� ���� ����.
	//------------------------------------------------
	if ( pclchar->HaveHorse() == false )
	{
		if ( (uiTo >= PERSONITEM_HORSE0) && (uiTo < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY) )	return;
	}

	//----------------------------------------------------
	// ������ ���� ���� ������ ���� �κ��� ���� ���� ����
	//----------------------------------------------------
	if ( 0 >= pclchar->pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique )
	{
		if ( (uiTo >= PERSONITEM_BAG0) && (uiTo < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG) )	return;
	}

	//----------------------------------------------------
	// ����2�� ���� ���� ������ ���� �κ��� ���� ���� ����
	//----------------------------------------------------
	if ( 0 >= pclchar->pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique )
	{
		if ( (uiTo >= PERSONITEM_BAG1) && (uiTo < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG) )	return;
	}

	//--------------------------------------------
	//From�� �������� ���Ѵ�.
	//--------------------------------------------
	pclFrom	= &pclchar->pclCI->clSummonInfo.clItemInfo[ siSummonIndex ].clEquipItem[ uiFrom ];

	// �������� ��ȿ�� ���̶��..
	if ( (NULL == pclFrom) || (0 >= pclFrom->siUnique) )
	{
		return;
	}

	//-----------------------------------------------
	// To �� �ִ´�. 
	//-----------------------------------------------
	clTo.Set( &pclchar->pclCI->clCharItem.clItem[uiTo] );
	if ( 0 < clTo.siUnique )
	{
		return;
	}


	//-----------------------------------------------
	//DB�޴����� �������� �̵��϶�� ��û�� ������. 
	//-----------------------------------------------
	cltItem clitem;
	clitem.Set(pclFrom);

	sDBRequest_SummonPopItem clMsg( id, siPersonID, pclsummon->siSummonID, uiFrom, &clitem, pclFrom->CanPile(pclItemManager), uiTo, &clTo );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_ADD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Amber_Box_Select_Item_Add* pclInfo = (cltGameMsgRequest_Amber_Box_Select_Item_Add*)pclMsg->cData;
	if( NULL == pclInfo )	return;
	
	cltCharServer* pclchar = pclClient->pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	if( 0 > pclInfo->m_siSlotIndex || AMBER_BOX_SELECT_ITEM_LIST_NUM <= pclInfo->m_siSlotIndex ) return;

	// ȣ�ڻ��ڷ��� �ƴϸ� ����
	if ( (NULL == m_pclBoxItemMgr) || (FALSE == m_pclBoxItemMgr->IsAmberBoxItem(pclInfo->m_clUseItemUnique)) )
	{
		return;
	}

	// �����ϰ� �������� �����´�
	CBoxItemUnit* pclGetBoxItemUnit = m_pclBoxItemMgr->GetRandItemFromUnique( pclInfo->m_clUseItemUnique );
	if ( NULL == pclGetBoxItemUnit )
	{
		return;
	}
	
	AmberboxSelectItemInfo	clAmberboxItemList;
	clAmberboxItemList.m_siItemUnique = pclGetBoxItemUnit->GetItemUnique();
	clAmberboxItemList.m_siItemNum    =	pclGetBoxItemUnit->GetItemNum();
	clAmberboxItemList.m_siSlot		  = pclInfo->m_siSlotIndex;
	
	sDBRequest_Amber_Box_Select_Item_Add clMsg(id, pclchar->pclCI->GetPersonID(), &clAmberboxItemList, pclInfo->m_clUseItemUnique);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Amber_Box_Select_Item_Get* pclInfo = (cltGameMsgRequest_Amber_Box_Select_Item_Get*)pclMsg->cData;
	if( NULL == pclInfo )	return;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	if( 0 > pclInfo->m_clAmberboxItem.m_siSlot || AMBER_BOX_SELECT_ITEM_LIST_NUM <= pclInfo->m_clAmberboxItem.m_siSlot ) return;

	// ���Ǵ� �������� ���. �� �ܿ��� �� ����.
	if ( (NULL == m_pclBoxItemMgr) || (FALSE == m_pclBoxItemMgr->IsAmberBoxItem(pclInfo->m_clUseItemUnique)) )
	{
		return;
	}

	SI16 siUseItemPos = pclchar->pclCI->clCharItem.FindItemInv( pclInfo->m_clUseItemUnique );
	if( 0 >= siUseItemPos)	return;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	cltItem clUseItem;
	clUseItem.Set(&pclchar->pclCI->clCharItem.clItem[siUseItemPos]);
	clUseItem.SetItemNum(1);

	// ��� ������ ����.
	SI16 brareswitch = 0;
	SI32 ItemUnique  = pclInfo->m_clAmberboxItem.m_siItemUnique;
	if( 0 >= ItemUnique )	return;

	SI32 ref = pclItemManager->FindItemRefFromUnique( ItemUnique );
	if( 0 >= ref )			return;

	SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

	cltItem clGetItem;	// ���� ������
	clGetItem.Init(); 

	if( false == pclItemManager->MakeRandItemUnique( ItemUnique, &clGetItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) )
		return ;

	// �� �к��Ѵ�.
	clGetItem.uiDateYear = 0;
	clGetItem.uiDateMonth = 0;
	clGetItem.uiDateDay = 0;

	if( 0 >= pclInfo->m_clAmberboxItem.m_siItemNum || 10000 < pclInfo->m_clAmberboxItem.m_siItemNum) return;

	clGetItem.SetItemNum( pclInfo->m_clAmberboxItem.m_siItemNum );

	// �������� ��� ���õ� ������ ����.
	SI16 siGetItemPos = 0;
	SI32 siRtnvalue   = 0;
	cltItem clToItem;	
	clToItem.Init();

	if( false == pclchar->CanAddInv(INVMODE_ALL, &clGetItem, &siGetItemPos, &clToItem, &siRtnvalue) )
	{ 
		SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 100, 0, id); 
		return;	
	}

	bool bCanPile = true;
	// ��ø�� �Ұ����� �������� �䷸�� ����.
	if(false == clGetItem.CanPile(pclClient->pclItemManager))
	{
		bCanPile = false; 
		//cltItem	clItem;
		//clItem.Set(&clGetItem);
		//clItem.SetItemNum(1);

		//for(SI32 Count = 0; Count < clGetItem.siItemNum; ++Count)
		//	//pclchar->GiveItem( ItemUnique, 1, INPUTITEMPERSON_OPTION_AMBERBOX, usedate );
		//	InputItem( pclchar, &clItem, INPUTITEMPERSON_OPTION_AMBERBOX );
	}


	sDBRequest_Amber_Box_Select_Item_Get clMsg( id, pclchar->pclCI->GetPersonID(), pclInfo->m_clAmberboxItem.m_siSlot, 
												siUseItemPos,					&clUseItem,
												bCanPile ? siGetItemPos : -1,   &clGetItem,	bCanPile );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWSELECTBOX_SELECT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NewSelectBox_Select* pclInfo = (cltGameMsgRequest_NewSelectBox_Select*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	SI16 siSelectIndex = pclInfo->m_siSelectIndex;
	if ( (0 >= siSelectIndex) || (MAX_NEWSELECTBOX_SELECTINDEX < siSelectIndex) )
	{
		return;
	}

	if ( NULL == pclNewSelectBoxMgr )
	{
		return;
	}

	SI16 siBoxItemUnique = pclInfo->m_siBoxItemUnique;
	switch ( siBoxItemUnique )
	{
		case ITEMUNIQUE(13340):
			{
				// ������ ���� �ε��� ���� �������� �޾ƿ;� ������ �ٽ��ѹ� �����ϰ� �����ϰ� �Ѵ� (��纯�� �׳� ������ ������ �ε�����)
				// siSelectIndex = (rand() % MAX_NEWSELECTBOX_SELECTINDEX) + 1; 
			}
			break;
		default:	{	return;	}
	}

	// �̰��� ���� �ε����� ���� ���� ������ ����� �޾ƿ´�
	//-------------------------------------------------------------------------------------
	// ���� �ѿ��� ���̳� ������ ����Ǵ� ���� ���� �ε����� 1�̴�
	// ������ ������������ 0���� ����Ǿ� �ֱ⶧���� -1�� ���ִ� ���̴�
	// �����ϵ������ּ���
	//-------------------------------------------------------------------------------------
	SI16 siRealSelectIndex	= (siSelectIndex-1); 
	SI16 siItemList[MAX_NEWSELECTBOX_ITEM_LIST] = { 0, };
	if ( false == pclNewSelectBoxMgr->GetItemListFromIndex(siRealSelectIndex, siItemList) )
	{
		return;
	}
	
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// �κ��� �������� ���� ���·� ��ư�� �������� �ֱ� ������ �ϴ� �˻�
	SI32 siBoxItemPos = pclchar->pclCI->clCharItem.FindItemInv( siBoxItemUnique );
	if ( PERSONITEM_INV0 > siBoxItemPos )
	{
		return;
	}

	// ������ ���� �κ��� ���ٸ� ���� ��ü�� �������� �ʴ´�
	if ( false == pclchar->IsBlankInv(1, INVMODE_ALL) )
	{
		return;
	}

	// Ŭ���̾�Ʈ ������ �����ϰ��� ������ ���� ������ ����
	pclchar->m_siNewSelectBoxValue = siSelectIndex;

	cltGameMsgResponse_NewSelectBox_Select clInfo( siBoxItemUnique, siSelectIndex, siItemList );
	cltMsg clMsg( GAMEMSG_RESPONSE_NEWSELECTBOX_SELECT, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWSELECTBOX_GETITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NewSelectBox_GetItem* pclInfo = (cltGameMsgRequest_NewSelectBox_GetItem*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( NULL == pclNewSelectBoxMgr )
	{
		return;
	}

	SI16 siSelectIndex = pclInfo->m_siSelectIndex;
	if ( (0 >= siSelectIndex) || (MAX_NEWSELECTBOX_SELECTINDEX < siSelectIndex) )
	{
		return;
	}

	// ó���� �����ߴ� ���� �ٸ��ٸ�
	if ( pclchar->m_siNewSelectBoxValue != siSelectIndex )
	{
		return;
	}
	
	SI16 siBoxItemUnique = pclInfo->m_siBoxItemUnique;
	switch ( siBoxItemUnique )
	{
		case ITEMUNIQUE(13340):
			{
			}
			break;
		default:	{	return;	}
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	//-----------------------------------------------------------------------
	// �̰��� siSelectIndex���� ���� ���� �������� ���� ���� �ҽ��� �����
	//-----------------------------------------------------------------------
	SI16 siRealSelectIndex	= (siSelectIndex-1); 
	cltBoxItem clGetBoxItem;
	if ( false == pclNewSelectBoxMgr->GetRandItemFromIndex(siRealSelectIndex, &clGetBoxItem) )
	{
		return;
	}

	SI16 siGetItemUnique	= clGetBoxItem.GetItemUnique();
	SI16 siGetItemNum		= clGetBoxItem.GetItemNum();
	SI32 siGetItemUseDate	= clGetBoxItem.GetUseDate();
	SI16 siGetItemNotice	= clGetBoxItem.GetCanNotice();

	//-----------------------------------------------------------------------
	// ���� ������ ���� ������
	//-----------------------------------------------------------------------
	SI16 siBoxItemPos = pclchar->pclCI->clCharItem.FindItemInv( siBoxItemUnique );
	if ( PERSONITEM_INV0 > siBoxItemPos )
	{
		return;
	}
	
	cltItem clBoxItem;
	clBoxItem.Set( &pclchar->pclCI->clCharItem.clItem[siBoxItemPos] );
	clBoxItem.SetItemNum( 1 );	// 1���� �Ҹ�ȴ�

	//-----------------------------------------------------------------------
	// �޴� ������ �����
	//-----------------------------------------------------------------------
	SI32 siRef = pclItemManager->FindItemRefFromUnique( siGetItemUnique );
	if ( 0 >= siRef )
	{
		return;
	}
	SI32 siUseDate = pclItemManager->pclItemInfo[siRef]->clItem.uiDateUseDay;
	if ( 0 < siGetItemUseDate )
	{
		siUseDate = siGetItemUseDate;
	}
	
	cltItem clGetItem;
	clGetItem.Init();

	SI16 siRareSwitch = 0;
	if ( false == pclItemManager->MakeRandItemUnique(siGetItemUnique, &clGetItem, 0, 0, &siRareSwitch, 0, 0, 0, 0, 0, siUseDate) )
	{
		return;
	}

	clGetItem.SetItemNum( siGetItemNum );

	// �ٽ� �к� ���ش�
	clGetItem.uiDateYear	= 0;
	clGetItem.uiDateMonth	= 0;
	clGetItem.uiDateDay		= 0;

	//-----------------------------------------------------------------------
	// �������� ���� ���� �� �ִ��� �˻�
	//-----------------------------------------------------------------------
	SI16	siGetItemPos	= 0;
	SI32	siReturn		= 0;
	cltItem	clToItem;
	clToItem.Init();

	if( false == pclchar->CanAddInv(INVMODE_ALL, &clGetItem, &siGetItemPos, &clToItem, &siReturn) )
	{ 
		// �������� ���� �� ���ٴ� �޽����� ���⿡ �ִ´�
		return;
	}
	
	bool bGetItemCanPile = clGetItem.CanPile( pclItemManager );
	
	//-----------------------------------------------------------------------
	// DB�� ������
	//-----------------------------------------------------------------------
	sDBRequest_NewSelectBox_Item_Get clMsg( pclchar->pclCI->GetPersonID(), id, siSelectIndex,
										&clBoxItem, siBoxItemPos,
										&clGetItem,	siGetItemPos, bGetItemCanPile, siGetItemNotice );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWNPCREPAIR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NewNPCRepair* pclInfo = (cltGameMsgRequest_NewNPCRepair*)pclMsg->cData;
	if ( NULL == pclInfo )											return;

	if( pclCM->IsValidID(id) == false )								return;
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )											return;

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclInfo->m_siPos;
	if( itempos < 0 || itempos >= MAX_ITEM_PER_PERSON )				return;

	cltItem beforeitem;
	cltItem* pclitem = &pclInfo->m_clItem;
	cltItem* pclorgitem = &pclchar->pclCI->clCharItem.clItem[itempos];
	if( pclitem->siUnique <= 0 || pclitem->siItemNum <= 0 )			return;
	if( pclorgitem->siUnique <= 0 || pclorgitem->siItemNum <= 0 )	return;

	beforeitem.Set( pclitem );
	// �־��� �����۰� ���� ���������� Ȯ���Ѵ�. 
	if( pclitem->IsSame(pclorgitem, false) == false )				return;

	// ���� �Ұ����� �������̾ ����.
	if( pclItemManager->CanRepairItem(pclitem) == false )			return;

	GMONEY price = pclItemManager->RepairPrice( pclitem );
	if( price != pclInfo->m_money )
	{
		// ������ �ùٸ��� �ʽ��ϴ�.
		return;
	}

	RepairItemExtraMaterial		kMaterial;
	// ������ üũ
	SI32 stonepos = pclInfo->m_Material[0].siStgPos;
	if( stonepos < 0 || stonepos >= MAX_ITEM_PER_PERSON )			return;
	cltItem* pclstoneitem = &pclchar->pclCI->clCharItem.clItem[stonepos];
	if( pclstoneitem->siUnique <= 0 || pclstoneitem->siItemNum <= 0 )	return;
	if( pclItemManager->IsRepairStone(pclstoneitem) == false )		return;
	if( pclstoneitem->siItemNum < pclItemManager->NeedRepairStoneNum(pclitem) )	
	{
		// ������ ���� ����
		return;
	}
	kMaterial[0].Set( &pclInfo->m_Material[0] );
	kMaterial[0].siUseItemNum = pclItemManager->NeedRepairStoneNum(pclitem);

	SI32 maxdur = pclitem->GetMaxDurability( pclItemManager );
	SI32 curdur = pclitem->GetDurability( );
	SI32 decmaxdur = GetGlobalValue( "GV_Decrease_MaxDurability" );

	// �ູ�� �� üũ
	bool bHasBlessingStone = false;
	for( SI32 i=1; i<pclInfo->m_Material.GetSize(); i++ )
	{
		SI32 siBlessingStoneNum = pclItemManager->NeedBlessingStoneNum( pclitem, ITEMUNIQUE(pclInfo->m_Material[i].siItemUnique) );
		if( siBlessingStoneNum > 0 && siBlessingStoneNum <= pclInfo->m_Material[i].siUseItemNum )
		{
			kMaterial[i].Set( &pclInfo->m_Material[i] );
			kMaterial[i].siUseItemNum = siBlessingStoneNum;

			bHasBlessingStone = true;
		}
	}

	// �����ϴ� �ִ볻������ ���� �ִ� ���������� ũ�ų� �������� ������ �ູ�� ���� �־�� �Ѵ�
	if ( (decmaxdur >= maxdur) && (false == bHasBlessingStone) )
	{
		return;
	}

	// �ູ�� ���� �ֱ� ������ �ִ� �������� �������� �ʴ´�.
	if( bHasBlessingStone )			decmaxdur = 0;

	// ���ο� �ִ� ������ �� ����
	SI32 newmaxdur = maxdur - decmaxdur;
	if( newmaxdur <= 0 )
	{
		newmaxdur = 0;
	}

	pclitem->SetMaxDurability( pclItemManager, newmaxdur );
	pclitem->SetDurability( pclItemManager, pclitem->GetMaxDurability( pclItemManager ) );

	sDBRequest_RepairItem clRepairItem( id, pclchar->pclCI->GetPersonID(), itempos, &beforeitem, pclitem, kMaterial, pclInfo->m_money, 0, ITEMREPAIR_MODE_NPC );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clRepairItem);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWITEMREPAIR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NewItemRepair* pclInfo = (cltGameMsgRequest_NewItemRepair*)pclMsg->cData;
	if ( NULL == pclInfo )											return;

	if( pclCM->IsValidID(id) == false )								return;
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )											return;

	SI32 siItemCharID = pclCM->GetIDFromPersonID( pclInfo->m_siItemPersonID );
	cltCharServer* pclitemchar = pclCM->GetCharServer( siItemCharID );
	if( pclitemchar == NULL )										return;

	pclchar->ItemUseReserveAction();
	pclchar->BulletUseReserveAction();

	pclitemchar->ItemUseReserveAction();
	pclitemchar->BulletUseReserveAction();

	// ������û ��Ҵ� ���� ó���ϰ� ������.
	switch( pclInfo->m_siType )
	{
	case ITEMREPAIR_MODE_CANCEL:		// ������û ���
		{
			pclchar->SetRepairShopData( false, NULL );

			cltGameMsgResponse_NewItemRepair clResult( 1, pclitemchar->GetCharUnique(), &pclInfo->m_clItem, pclInfo->m_siType );
			cltMsg clNetMsg1( GAMEMSG_RESPONSE_NEWITEMREPAIR, sizeof(clResult), (BYTE*)&clResult );
			pclchar->SendNeighbourMsg( &clNetMsg1, true );
			return;
		}
		break;
	}		

	// ��ȿ�� ������ ������ ��ġ�� ���� ����. 
	SI32 itempos = pclInfo->m_siPos;
	if( itempos < 0 || itempos >= MAX_ITEM_PER_PERSON )				return;

	cltItem beforeitem;
	cltItem* pclitem = &pclInfo->m_clItem;
	cltItem* pclorgitem = &pclitemchar->pclCI->clCharItem.clItem[itempos];
	if( pclitem->siUnique <= 0 || pclitem->siItemNum <= 0 )			return;
	if( pclorgitem->siUnique <= 0 || pclorgitem->siItemNum <= 0 )	return;

	beforeitem.Set( pclitem );
	// �־��� �����۰� ���� ���������� Ȯ���Ѵ�. 
	if( pclitem->IsSame(pclorgitem, false) == false )				return;

	// ������ üũ
	SI32 stonepos = pclInfo->m_Material[0].siStgPos;
	if( stonepos < 0 || stonepos >= MAX_ITEM_PER_PERSON )			return;
	cltItem* pclstoneitem = &pclitemchar->pclCI->clCharItem.clItem[stonepos];
	if( pclstoneitem->siUnique <= 0 || pclstoneitem->siItemNum <= 0 )	return;

	// �ִ� �ݾ��� GV_Repair_MaxRequestMoney�� ���� ���� ����
	GMONEY gLimitePrice = pclClient->GetGlobalValue( TEXT("GV_Repair_MaxRequestMoney") );
	if ( gLimitePrice < pclInfo->m_money )
	{
		return;
	}

	RepairItemExtraMaterial		kMaterial;
	kMaterial[0].Set( &pclInfo->m_Material[0] );

	SI32 maxdur = pclitem->GetMaxDurability( pclItemManager );
	SI32 curdur = pclitem->GetDurability( );
	SI32 decmaxdur = GetGlobalValue( "GV_Decrease_MaxDurability" );

	// �ִ� ������ ȸ���� ���
	if ( ITEMREPAIR_MODE_GROWUP_MAX == pclInfo->m_siType )
	{
		if ( false == pclItemManager->CanMaxRepairItem(pclitem) )						return;
		if ( false == pclItemManager->IsMaxRepairStone(pclstoneitem) )					return;
		if ( 0 >= pclstoneitem->siItemNum )												return;

		kMaterial[0].siUseItemNum = 1;
	}
	else
	{
		// ���� �Ұ����� �������̾ ����.
		if( pclItemManager->CanRepairItem(pclitem) == false )							return;
		// ������ �� �ִ°�? - ���� �����ϴ� ��쿡�� üũ�Ѵ�.
		if( pclInfo->m_siType == 1 && pclitemchar->CanRepairItem( pclitem ) == false )	return;
		if( pclItemManager->IsRepairStone(pclstoneitem) == false )						return;
		if( pclstoneitem->siItemNum < pclItemManager->NeedRepairStoneNum(pclitem) )		return;

		kMaterial[0].siUseItemNum = pclItemManager->NeedRepairStoneNum(pclitem);

		

		// �ູ�� �� üũ
		bool bHasBlessingStone = false;
		for( SI32 i=1; i<pclInfo->m_Material.GetSize(); i++ )
		{
			SI32 siBlessingStoneNum = pclItemManager->NeedBlessingStoneNum( pclitem, ITEMUNIQUE(pclInfo->m_Material[i].siItemUnique) );
			if( siBlessingStoneNum > 0 && siBlessingStoneNum <= pclInfo->m_Material[i].siUseItemNum )
			{
				kMaterial[i].Set( &pclInfo->m_Material[i] );
				kMaterial[i].siUseItemNum = siBlessingStoneNum;

				bHasBlessingStone = true;
			}
		}

		// ������ ������ �ִ� �������� GV_Decrease_MaxDurability���� ���ٸ� �ູ�� �� ���̴� ���� �ȵ�
		switch ( pclInfo->m_siType )
		{
		case ITEMREPAIR_MODE_SELF:
		case ITEMREPAIR_MODE_REQUEST_PRECESS:
			{
				if ( (decmaxdur >= maxdur) && (false == bHasBlessingStone) )
				{
					return;
				}
			}
			break;
		}

		// �ູ�� ���� �ֱ� ������ �ִ� �������� �������� �ʴ´�.
		if( bHasBlessingStone )			decmaxdur = 0;
	}

	switch( pclInfo->m_siType )
	{
	case ITEMREPAIR_MODE_SELF:		// ���� ����
		{
			// ������ ȸ���ϰ��
			SI32 newmaxdur = maxdur - decmaxdur;
			if( newmaxdur <= 0 )
			{
				newmaxdur = 0;
			}
			pclitem->SetMaxDurability( pclItemManager, newmaxdur );
			pclitem->SetDurability( pclItemManager, pclitem->GetMaxDurability( pclItemManager ) );

			sDBRequest_RepairItem clRepairItem( id, pclitemchar->pclCI->GetPersonID(), itempos, &beforeitem, pclitem, kMaterial, pclInfo->m_money, 0, pclInfo->m_siType );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clRepairItem);
		}
		break;

	case ITEMREPAIR_MODE_REQUEST:		// ���� ��û
		{
			// �̿�� Ƽ��
			SI32 siRepairRequestTicketUnique	= Const_RepairRequestTicket_ItemUnique;
			SI16 siRepairRequestTicketNum		= 1;

			SI32 siRepairRequestTicketPos		= pclchar->pclCI->clCharItem.GetItemPos( siRepairRequestTicketUnique );
			if ( (PERSONITEM_INV0 > siRepairRequestTicketPos) || ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) <= siRepairRequestTicketPos) )
			{
				SendServerResponseMsg( 0, SRVAL_REPAIR_REQUEST_FAIL, 0, 0, id );
				return;
			}
			
			cltItem clRepairRequestTicket;
			
			clRepairRequestTicket.Set( &pclchar->pclCI->clCharItem.clItem[siRepairRequestTicketPos] );
			clRepairRequestTicket.SetItemNum( 1 );
			
			// Ƽ�� ������ ��� �ǵ��� �Ѵ�
			sDBRequest_UseItem stPacket_UseItem( id, pclchar->pclCI->GetPersonID(), siRepairRequestTicketPos, &clRepairRequestTicket, USEITEM_REASON_NONE );
			pclGameDBProcess->SendMsg(DBSELECT_BASE, (sPacketHeader *)&stPacket_UseItem);
			
			cltShopRepairData clShopRepairData;

			clShopRepairData.m_siPersonID = pclchar->pclCI->GetPersonID();			
			StringCchCopy(clShopRepairData.m_szAccountID, sizeof(clShopRepairData.m_szAccountID), pclchar->pclCI->clBI.szAccountID );

			clShopRepairData.m_siRepairItemPos	= itempos;
			clShopRepairData.m_clRepairItem.Set( pclitem );

			clShopRepairData.m_siPrice			= pclInfo->m_money;
			for( SI32 i=0; i<pclInfo->m_Material.GetSize(); i++ )
			{
				clShopRepairData.m_kMaterial[i].Set( &pclInfo->m_Material[i] );
			}
			pclchar->SetRepairShopData( true, &clShopRepairData );

			cltGameMsgResponse_NewItemRepair clResult( 1, pclchar->GetCharUnique(), &pclInfo->m_clItem, pclInfo->m_siType );
			cltMsg clNetMsg1( GAMEMSG_RESPONSE_NEWITEMREPAIR, sizeof(clResult), (BYTE*)&clResult );
			pclchar->SendNetMsg( (sPacketHeader*)&clNetMsg1 );

			cltGameMsgResponse_NewItemRepairRequestInfo clMsgBanner(pclchar->pclCI->GetPersonID(), pclchar->GetCharUnique(), 
				pclchar->m_pclShopRepairData->m_siRepairItemPos,
				&pclchar->m_pclShopRepairData->m_clRepairItem,
				pclchar->m_pclShopRepairData->m_siPrice,
				pclchar->m_pclShopRepairData->m_kMaterial,
				NEWITEMREPAIR_INFO_BANNER );		// ��������� �ֺ� ĳ���Ϳ��� ������

			cltMsg clNetMsg2( GAMEMSG_RESPONSE_NEWITEMREPAIRREQUESTINFO, sizeof(clMsgBanner), (BYTE*)&clMsgBanner );
			pclchar->SendNeighbourMsg( &clNetMsg2, true );

			cltGameMsgResponse_NewItemRepairRequestInfo clMsgInfo(	pclchar->pclCI->GetPersonID(), pclchar->GetCharUnique(), 
				pclchar->m_pclShopRepairData->m_siRepairItemPos,
				&pclchar->m_pclShopRepairData->m_clRepairItem,
				pclchar->m_pclShopRepairData->m_siPrice,
				pclchar->m_pclShopRepairData->m_kMaterial,
				NEWITEMREPAIR_INFO_ITEM );		// ���������� ������ ������.
			cltMsg clNetMsg3( GAMEMSG_RESPONSE_NEWITEMREPAIRREQUESTINFO, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
			pclchar->SendNetMsg( (sPacketHeader*)&clNetMsg3 );
		}
		break;
	case ITEMREPAIR_MODE_REQUEST_PRECESS:		// �Ƿڼ���
		{
			// ���ο� �ִ� ������ �� ����
			SI32 newmaxdur = maxdur - decmaxdur;
			if( newmaxdur <= 0 )
			{
				newmaxdur = 0;
			}
			pclitem->SetMaxDurability( pclItemManager, newmaxdur );
			pclitem->SetDurability( pclItemManager, pclitem->GetMaxDurability( pclItemManager ) );

			sDBRequest_RepairItem clRepairItem( id, pclitemchar->pclCI->GetPersonID(), itempos, &beforeitem, pclitem, kMaterial, pclInfo->m_money, pclchar->pclCI->GetPersonID(), pclInfo->m_siType );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clRepairItem);
		}
		break;

	case ITEMREPAIR_MODE_CANCEL:		// ���� ��û ��Ҵ� ������ ���� ó���ߴ�.
		{
		}
		break;

	case ITEMREPAIR_MODE_GROWUP_MAX:// �ִ� ������ ȸ���� ���
		{
			SI32 siGV_Repair_MaxDurability	= (SI32)GetGlobalValue( TEXT("GV_Repair_MaxDurability") );
			SI32 siGV_MaxDurability			= (SI32)GetGlobalValue( TEXT("GV_MaxDurability") );
			SI32 siNewMaxDur				= pclitem->GetMaxDurability( pclItemManager ) + siGV_Repair_MaxDurability; 

			if ( siGV_MaxDurability < siNewMaxDur )
			{
				siNewMaxDur = siGV_MaxDurability;
			}

			pclitem->SetMaxDurability( pclItemManager, siNewMaxDur );

			sDBRequest_RepairItem clRepairItem( id, pclitemchar->pclCI->GetPersonID(), itempos, &beforeitem, pclitem, kMaterial, pclInfo->m_money, 0, pclInfo->m_siType );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clRepairItem);

		}
		break;

	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWITEMREPAIRREQUESTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NewItemRepairRequestInfo* pclInfo = (cltGameMsgRequest_NewItemRepairRequestInfo*)pclMsg->cData;
	if ( NULL == pclInfo )											return;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )											return;

	SI32 siCharID_Request = pclCM->GetIDFromCharUnique( pclInfo->m_siCharUnique );
	cltCharServer* pclchar_request = pclCM->GetCharServer( siCharID_Request );
	if( pclchar_request == NULL )									return;

	if( pclchar_request->m_pclShopRepairData == NULL )				return;
	if( pclchar_request->bRepairShopSwitch == false )				return;

	cltGameMsgResponse_NewItemRepairRequestInfo clMsg( pclchar_request->pclCI->GetPersonID(), pclchar_request->GetCharUnique(), 
		                                               pclchar_request->m_pclShopRepairData->m_siRepairItemPos,
													   &pclchar_request->m_pclShopRepairData->m_clRepairItem,
													   pclchar_request->m_pclShopRepairData->m_siPrice,
													   pclchar_request->m_pclShopRepairData->m_kMaterial,
													   pclInfo->m_siType );
	cltMsg clNetMsg( GAMEMSG_RESPONSE_NEWITEMREPAIRREQUESTINFO, sizeof(clMsg), (BYTE*)&clMsg );
	pclchar->SendNetMsg( (sPacketHeader*)&clNetMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EQUIPMENTCREATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_EquipmentCreate* pclinfo = (cltGameMsgRequest_EquipmentCreate*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if(pclchar == NULL)	return;

	SI32 GMref = pclGMManager->FindUniqueFromOrder(TEXT("seq"));
	SI32 gamemasterlevel = pclchar->GetGameMasterLevel();

	if(GMref < 1 || GMref >= MAX_GMINFO_NUMBER)	return;

	// ��� ������ ������ ���� ���Ѵ�.
	if(gamemasterlevel < pclGMManager->pclGMInfo[GMref]->siNeedGMLevel)	return;

	SI32 ref = 0;
	UI16 usedate = 0;

	// �����
	if(pclinfo->m_siWeaponUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siWeaponPower1, pclinfo->m_siWeaponPower2, pclinfo->m_siWeaponPower3, pclinfo->m_siWeaponPower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siWeaponUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siWeaponUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID(), 0, 0, 
			            pclinfo->m_siWeaponProPerty, pclinfo->m_siWeaponEnchant, pclinfo->m_siWeaponSlot );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], ItemProPerty : [%d], ItemEnchant: [%d], ItemSlot : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siWeaponUnique, pclinfo->m_siWeaponProPerty, pclinfo->m_siWeaponEnchant, pclinfo->m_siWeaponSlot, pclinfo->m_siWeaponPower1, pclinfo->m_siWeaponPower2, pclinfo->m_siWeaponPower3, pclinfo->m_siWeaponPower4);
	}

	// ����
	if(pclinfo->m_siHelmetUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siHelmetPower1, pclinfo->m_siHelmetPower2, pclinfo->m_siHelmetPower3, pclinfo->m_siHelmetPower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siHelmetUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siHelmetUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID(), 0, 0, 
			            pclinfo->m_siHelmetProPerty, pclinfo->m_siHelmetEhchant, pclinfo->m_siHelmetSlot );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], ItemProPerty : [%d], ItemEnchant: [%d], ItemSlot : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siHelmetUnique, pclinfo->m_siHelmetProPerty, pclinfo->m_siHelmetEhchant, pclinfo->m_siHelmetSlot, pclinfo->m_siHelmetPower1, pclinfo->m_siHelmetPower2, pclinfo->m_siHelmetPower3, pclinfo->m_siHelmetPower4);
	}

	// ����
	if(pclinfo->m_siArmorUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siArmorPower1, pclinfo->m_siArmorPower2, pclinfo->m_siArmorPower3, pclinfo->m_siArmorPower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siArmorUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siArmorUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID(), 0, 0, 
			            pclinfo->m_siArmorProPerty, pclinfo->m_siArmorEnchant, pclinfo->m_siArmorSlot );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], ItemProPerty : [%d], ItemEnchant: [%d], ItemSlot : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siArmorUnique, pclinfo->m_siArmorProPerty, pclinfo->m_siArmorEnchant, pclinfo->m_siArmorSlot, pclinfo->m_siArmorPower1, pclinfo->m_siArmorPower2, pclinfo->m_siArmorPower3, pclinfo->m_siArmorPower4);
	}

	// �㸮��
	if(pclinfo->m_siBeltUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siBeltPower1, pclinfo->m_siBeltPower2, pclinfo->m_siBeltPower3, pclinfo->m_siBeltPower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siBeltUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siBeltUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID(), 0, 0, 
			            pclinfo->m_siBeltProPerty, pclinfo->m_siBeltEnchat, pclinfo->m_siBeltSlot );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], ItemProPerty : [%d], ItemEnchant: [%d], ItemSlot : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siBeltUnique, pclinfo->m_siBeltProPerty, pclinfo->m_siBeltEnchat, pclinfo->m_siBeltSlot, pclinfo->m_siBeltPower1, pclinfo->m_siBeltPower2, pclinfo->m_siBeltPower3, pclinfo->m_siBeltPower4);
	}

	// �Ź�
	if(pclinfo->m_siShoeUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siShoePower1, pclinfo->m_siShoePower2, pclinfo->m_siShoePower3, pclinfo->m_siShoePower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siShoeUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siShoeUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID(), 0, 0, 
			            pclinfo->m_siShoeProPerty, pclinfo->m_siShoeEnchant, pclinfo->m_siShoeSlot );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], ItemProPerty : [%d], ItemEnchant: [%d], ItemSlot : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siShoeUnique, pclinfo->m_siShoeProPerty, pclinfo->m_siShoeEnchant, pclinfo->m_siShoeSlot, pclinfo->m_siShoePower1, pclinfo->m_siShoePower2, pclinfo->m_siShoePower3, pclinfo->m_siShoePower4);
	}

	// ����
	if(pclinfo->m_siMantleUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siMantlePower1, pclinfo->m_siMantlePower2, pclinfo->m_siMantlePower3, pclinfo->m_siMantlePower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siMantleUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siMantleUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID() );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siMantleUnique, pclinfo->m_siMantlePower1, pclinfo->m_siMantlePower2, pclinfo->m_siMantlePower3, pclinfo->m_siMantlePower4);
	}

	// �����
	if(pclinfo->m_siNeckUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siNeckLacePower1, pclinfo->m_siNeckLacePower2, pclinfo->m_siNeckLacePower3, pclinfo->m_siNeckLacePower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siNeckUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siNeckUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID() );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siNeckUnique, pclinfo->m_siNeckLacePower1, pclinfo->m_siNeckLacePower2, pclinfo->m_siNeckLacePower3, pclinfo->m_siNeckLacePower4);
	}

	// ����
	if(pclinfo->m_siRingUnique > 0)
	{
		pclchar->SetRareItemRate(0, 0, 0, 0);
		pclchar->SetRareItemRate(pclinfo->m_siRingPower1, pclinfo->m_siRingPower2, pclinfo->m_siRingPower3, pclinfo->m_siRingPower4);
		ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_siRingUnique);
		if (ref <= 0)	return;
		usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		pclCM->GiveItem(id, pclinfo->m_siRingUnique, 1, GIVEITEM_MODE_SEQGMCOMMAND, INPUTITEMPERSON_OPTION_SEQGMCOMMAND,usedate, pclchar->GetID() );

		// ��ڸ�ɾ� �α׿� �����.
		pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use seq : ItemUnique : [%d], RareItemRate : [%d] [%d] [%d] [%d]"), 
			pclCM->CR[id]->GetName(), pclinfo->m_siRingUnique, pclinfo->m_siRingPower1, pclinfo->m_siRingPower2, pclinfo->m_siRingPower3, pclinfo->m_siRingPower4);
	}	
}
// [����] ���� ���� ���ڿ��� �������� �ش� 
void cltServer::DoMsg_GAMEMSG_REQUEST_OPEN_LEVEL_LIMIT_BOX(cltMsg* pclMsg, SI32 id)
{
	if ( pclClient->IsCountrySwitch(Switch_LevelLimitBox) == false)		return	;

	cltGameMsgRequest_UseLimitLevleBox* pclInfo = (cltGameMsgRequest_UseLimitLevleBox*)pclMsg->cData;
	if ( NULL == pclInfo )											return;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )											return;

	SI32 siUse_Box_Item_Unique	=	0	;
	SI32 siUse_Box_OpenLevel	=	0	;
	SI32 siUse_Box_Total_itemnum	=	0	;	// �ִ� ���� ���� ������ �ִ� �������� �� ����


	siUse_Box_Item_Unique = pclInfo->m_siOpenItemBox	;	// ����� ������ ���� 
	if ( siUse_Box_Item_Unique <= 0 )	return	;
	if(pclClient->pclItemManager->pclRewardItemLimitLevelForChina == NULL )	return	;
	if( pclItemManager->pclRewardItemLimitLevelForChina->IsRewardBox_Unique(siUse_Box_Item_Unique )	== false )		return	;
	siUse_Box_OpenLevel = pclItemManager->pclRewardItemLimitLevelForChina->GetOpenLevel( siUse_Box_Item_Unique )	;
	if ( siUse_Box_OpenLevel < 0 )	return	;
	if(pclchar->pclCI->clIP.siLevel	<	siUse_Box_OpenLevel)	// ���� ���� ���ϸ� ���� �Ѵ� 
	{
		SendServerResponseMsg(0, SRVAL_FAIL_OPEN_LEVELLIMTBOX_NOT_OVER_LEVEL, siUse_Box_OpenLevel, 0, id); 
		// ���� �ִ·����� �ȵƴ�
		return	;
	}
	siUse_Box_Total_itemnum	=	pclItemManager->pclRewardItemLimitLevelForChina->GetTotalItemNum(siUse_Box_Item_Unique)	;
	if ( siUse_Box_Total_itemnum < 0 )	return	;
	if( false == pclchar->IsBlankInv(siUse_Box_Total_itemnum,INVMODE_ALL )	)		
	{
		SendServerResponseMsg(0, SRVAL_FAIL_OPEN_LEVELLIMTBOX_NOT_NOT_ENOUGH_INV, siUse_Box_Total_itemnum, 0, id); 
		// �κ��丮�� ������� ���� �ϴ� .
		return	;
	}
	// �ش� ������ ������ �ֳ� �˻� �Ѵ� 
	SI32 siitempos = pclchar->pclCI->clCharItem.GetItemPos( siUse_Box_Item_Unique )	;
	if ( siitempos <= 0 )	return	;

	BoxData RewardIteminfo	;
	ZeroMemory(&RewardIteminfo,sizeof(BoxData))	;
	
	for ( SI32 siindex = 0 ; siindex < MAX_REWARDITEMBOX_NUM ; siindex++ ) 
	{
		if( pclItemManager->pclRewardItemLimitLevelForChina->GetBoxUnique(siindex) ==  siUse_Box_Item_Unique )
		{
			memcpy(&RewardIteminfo,&pclItemManager->pclRewardItemLimitLevelForChina->m_RewardITemBoxLinmitLevel_ForNHNChina[siindex],sizeof(BoxData));
        }
	}
	if ( RewardIteminfo.siBoxitemunique <= 0 ) return	;
	//���� ������ ����Ѵ�. 
	cltItem clitem;
	SI32 pos	=	0	;	
	SI32 Boxref = pclClient->pclItemManager->FindItemRefFromUnique(siUse_Box_Item_Unique);
	if(Boxref > 0)	// �ڽ��� ��� �Ѵ� 
	{
		clitem.Set(&pclClient->pclItemManager->pclItemInfo[Boxref]->clItem);
		clitem.siItemNum = 1;
		pos = pclchar->pclCI->clCharItem.FindItemInv(&clitem, false);
		if(pos >= 0)
		{
			sDBRequest_UseItem clMsg(id, pclchar->pclCI->GetPersonID(), pos, &clitem,USEITEM_REASON_NONE);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
	}
	// ���� �ش�
	sDBRequest_ChangeMoney clMsg(id, pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_LEVELLIMITBOX_REWARD, RewardIteminfo.gRewardMoney);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	// ������� ��� �ϰ� �� �������� �ش�
	if(RewardIteminfo.siRewardItemUnique_1	> 0 && RewardIteminfo.siRewardItemNum_1 > 0 )
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(RewardIteminfo.siRewardItemUnique_1);
		if (ref > 0)
		{
			UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			// �������� �ش�
			pclCM->GiveItem(id, RewardIteminfo.siRewardItemUnique_1, RewardIteminfo.siRewardItemNum_1, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_LIMITLEVELBOX,usedate, 0 );
		}		

	}
	if(RewardIteminfo.siRewardItemUnique_2	> 0 && RewardIteminfo.siRewardItemNum_2 > 0 )
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(RewardIteminfo.siRewardItemUnique_2);
		if (ref > 0)
		{
			UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			// �������� �ش�
			pclCM->GiveItem(id, RewardIteminfo.siRewardItemUnique_2, RewardIteminfo.siRewardItemNum_2, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_LIMITLEVELBOX,usedate, 0 );
		}
	}
	if(RewardIteminfo.siRewardItemUnique_3	> 0 && RewardIteminfo.siRewardItemNum_3 > 0 )
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(RewardIteminfo.siRewardItemUnique_3);
		if (ref > 0)
		{
			UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			// �������� �ش�
			pclCM->GiveItem(id, RewardIteminfo.siRewardItemUnique_3, RewardIteminfo.siRewardItemNum_3, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_LIMITLEVELBOX,usedate, 0 );
		}		
	}
	if(RewardIteminfo.siRewardItemUnique_4	> 0 && RewardIteminfo.siRewardItemNum_4 > 0)
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(RewardIteminfo.siRewardItemUnique_4);
		if (ref > 0)
		{
			UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			// �������� �ش�
			pclCM->GiveItem(id, RewardIteminfo.siRewardItemUnique_4, RewardIteminfo.siRewardItemNum_4, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_LIMITLEVELBOX,usedate, 0 );
		}
	}
	if(RewardIteminfo.siRewardItemUnique_5	> 0 && RewardIteminfo.siRewardItemNum_5 > 0 )
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(RewardIteminfo.siRewardItemUnique_5);
		if (ref > 0)
		{
			UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
			// �������� �ش�
			pclCM->GiveItem(id, RewardIteminfo.siRewardItemUnique_5, RewardIteminfo.siRewardItemNum_5, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_LIMITLEVELBOX,usedate, 0 );
		}
	}
}
//[����] // �׾��� ���� ���Ȳ�̴� �������� ���δ�
void cltServer::DoMsg_GAMEMSG_REQUEST_JustItemUse(cltMsg* pclMsg, SI32 id)
{

	//**�ذ��ϸ� ���� �������׾����� �ູ���� ��Ȱ�� ����� ���� ���� ���Դϴ� **//
	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;

	//	--------------------------------------------

	cltGameMsgRequest_UseJustUseItem* pclInfo = (cltGameMsgRequest_UseJustUseItem*)pclMsg->cData;
	if ( NULL == pclInfo )											return;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )											return;
	SI32 itemunique = pclInfo->m_siitemunique;								if( itemunique <= 0 )	return;	// ���� ���� ������ ����ũ ���� Ȯ��
	SI32 ref		= pclItemManager->FindItemRefFromUnique(itemunique);	if(ref <= 0)			return	;
	
	SI32 itemtype	= pclItemManager->pclItemInfo[ref]->siType;
	SI64 itematb	= pclItemManager->pclItemTypeInfo[itemtype]->siAtb;		if ( itematb == ITEMATB_OBJECT )	return	;// ������Ʈ�� ����Ҽ����� 
	SI32 pos = pclInfo->m_siitempos	;

	SI32 sihaveItempos = pclchar->pclCI->clCharItem.GetItemPos( itemunique )	;
	// �ش� ��ġ�� �������� �ִ°� ?
	if(pos	!= sihaveItempos)	return	;

	cltItem clItem;
	clItem.Set( &pclchar->pclCI->clCharItem.clItem[ pos ] );
	clItem.SetItemNum(pclInfo->m_siitemnum);

	sDBRequest_UseItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pos, &clItem,USEITEM_REASON_NONE);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}