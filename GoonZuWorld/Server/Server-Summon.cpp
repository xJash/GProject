//---------------------------------
//
//---------------------------------

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"

#include "../../Lib/HashTable/HashTable_StringInt.h"

#include "../../Common/Map/MapManager/MapManager.h"
#include "Char/CharManager/CharManager.h"


#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-Summon.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "Statistics/Statistics.h"

#include "Minister/MinisterBase.h"
#include "Minister/Minister-Izo.h"
#include "Minister/MinisterMgr.h"
#include "../common/Event/event.h"
#include "../common/PersonInfo.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONFREE(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	// 
	//---------------------------------------------
	cltGameMsgRequest_SummonFree* pclinfo = (cltGameMsgRequest_SummonFree*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	//--------------------------------
	// ������ ��ȯ���� ���� �����Ѵ�.
	//--------------------------------
	if(pclSummon->siKind == 0) return;
		
	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();
	
	//---------------------------------------------
	// ��� ������ ��ȯ���� Ǯ���� �� ����.
	//---------------------------------------------
	if ( pclchar->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{
		SendServerResponseMsg(0, SRVAL_SUMMON_FREE_FAIL_HAVEITEM, 0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	
	//---------------------------------------------
	// pclinfo->siSummonIndex �� free ���Ѿ��Ѵ�.
	//---------------------------------------------
	// DB�� ��ȯ���� �����Ѵ�.
	pclchar->SendDBSummon(SETSUMMON_REASON_FREE, siSummonIndex);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONNAMECHANGE(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	// 
	//---------------------------------------------
	cltGameMsgRequest_SummonNameChange* pclinfo = (cltGameMsgRequest_SummonNameChange*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;
	
	//--------------------------------
	// ��ȯ���� ���� �����Ѵ�.
	//--------------------------------
	if(pclSummon->siKind == 0) return;
		
	// ��ȯ�� �̸��� �����Ų��.
	MStrCpy(pclSummon->szName, pclinfo->strSummonName, MAX_SUMMON_NAME);

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);
	// DB�� ��ȯ���� �����Ѵ�.
	pclchar->SendDBSummon(SETSUMMON_REASON_UPDATE, siSummonIndex);

	cltGameMsgResponse_SummonNameChange clInfo(pclchar->GetCharUnique(), pclSummon->siSummonID, pclSummon->szName);
	cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONNAMECHANGE, sizeof(clInfo), (BYTE*)&clInfo);
	((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg, true );

	cltSimpleSummon *pclSimpleSummon = pclchar->pclCI->clSummonInfo.GetSimpleSummonFromSummonID(pclSummon->siSummonID);
	SI32 siSlotIndex = pclchar->pclCI->clSummonInfo.GetSummonBaseIndexFromSummonID(pclSummon->siSummonID);
	if(pclSimpleSummon)
	{
		StringCchCopy(pclSimpleSummon->szName, sizeof(pclSimpleSummon->szName), pclSummon->szName);

		cltGameMsgResponse_BaseSummon clInfo(pclchar->GetCharUnique(), siSlotIndex, pclSimpleSummon);
		cltMsg clMsg(GAMEMSG_RESPONSE_BASESUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONREVIVE(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id)  == false)	return;

	//---------------------------------------------
	//
	//---------------------------------------------
	cltGameMsgRequest_SummonRevive* pclinfo = (cltGameMsgRequest_SummonRevive*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);
	
	//---------------------------------------------
	// ��ȯ���� �׾����� ������ ��Ȱ��ų�� ����.
	//---------------------------------------------
	if(pclSummon->siStatus != SUMMON_STATUS_DEAD) return;

	//--------------------------------
	// ��Ȱ��ų ��ȯ���� Kind�� �����Ѵ�.
	//--------------------------------
	SI32 kind = pclSummon->siKind;
	if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return;
	
	//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
	cltKindInfo* pclki = NULL;
	cltGMCommandKindInfo* pclGMki = NULL;

	if(IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclKindInfoSet->pclSummonKI[kind];
		pclGMki = pclKindInfoSet->pclGMCommandKindInfo[kind];
	}
	else
	{
		pclki = pclKindInfoSet->pclKI[kind];
		pclGMki = pclKindInfoSet->pclGMCommandKindInfo[kind];
	}

	if(pclki == NULL)							return;
	if(pclki->siSummonRank <= 0)				return;
	if(pclGMki == NULL)							return;

	//--------------------------------
	// ��Ȱ��Ű������ �غ� ����
	//--------------------------------
	SI32 siSuccess	= 1;
	SI32 siDollPos	= 0;
	SI32 siDollUnique	= 0;
	SI32 siDollNum		= 0;

	if(pclinfo->siReviveType == SUMMON_REVIVE_DOLL)
	{
		siDollUnique= pclItemManager->GetItemDollUnique(kind);
		siDollNum	=  pclSummon->clIP.GetLevel();
		if(siDollUnique <= 0)		return;
		if(siDollNum	<= 0)		return;
		if(pclki->bSummonMall == TRUE)				return; // ��ȯ���� �����۸� ��ȯ�� �ϰ�쿡�� ��Ȱ�Ҽ� ����.
	}
	else if(pclinfo->siReviveType == SUMMON_REVIVE_TICKET)
	{
		siDollUnique			= ITEMUNIQUE(24020);	// ��ȯ����Ȱ�̿��  14060 -> 24020
		siDollNum	=  1;
		if(siDollUnique <= 0)		return;
		if(siDollNum	<= 0)		return;
	}
	else
	{
		return;
	}

	///////////////////////////////////////////////////////
	// ��ȯ���� Ȯ�� 
	siDollPos = pclCM->CR[charid]->pclCI->clCharItem.GetItemPos(siDollUnique);
	
	if(siDollPos < PERSONITEM_INV0 || siDollPos >= MAX_ITEM_PER_PERSON)	
	{
		siDollUnique = ITEMUNIQUE(24130); // ������ ��ȯ��Ȱ�̿���� �����ϰ� ���� �ʴٸ� �̺�Ʈ������ ������ �ִ��� Ȯ��.

		siDollPos = pclCM->CR[charid]->pclCI->clCharItem.GetItemPos(siDollUnique);

		if(siDollPos < PERSONITEM_INV0 || siDollPos >= MAX_ITEM_PER_PERSON)
		{
			siSuccess = -1;
		}
	}
	
	if(siSuccess > 0 && pclCM->CR[id]->pclCI->clCharItem.clItem[siDollPos].siItemNum < siDollNum)	siSuccess = -1;
	//////////////////////////////////////////////////////////////////////////
	
	if(siSuccess > 0)
	{
		// ��ǰ ��� ��踦 ����.
		pclItemManager->AddUseNum(siDollUnique, siDollNum);

		//���ο� ��� - ��ǰ ��� ��踦 ����.
		//NStatistics_Add("Item", siDollUnique, "UseNum", siDollNum);

	    
		
		// ��ȯ����Ȱ�̿���� ����� ���̶��, 
		if(pclinfo->siReviveType == SUMMON_REVIVE_TICKET)
		{
			// ��ȯ�� Ƽ������ �츮�� ����Ʈ���̶��, 
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_REVIVESUMMON);
		}
		else if( pclinfo->siReviveType == SUMMON_REVIVE_DOLL )
		{
			// ��ȯ�� �������� �츮�� ����Ʈ���̶��, 
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_REVIVESUMMONBYDOLL);
		}

		// ��ȯ���� ��ȯ�� ������ Unique�� �ش�.
		SI32 villageunique  = pclCM->CR[charid]->GetCurrentVillageUnique();

		//---------------------------------------------
		// ��ȯ���� ��Ȱ��Ű�� ���� �⺻���� LIFE, MANA�� �����Ѵ�.
		//---------------------------------------------
		cltSummon clSummon;
		clSummon.Set(pclSummon);
		
		cltPIPInfo			clipinfo2;
		clipinfo2.Set(&pclSummon->clIP);
		
		cltItem clDollItem;
		SI16 brareswitch = 0;
		pclClient->pclItemManager->MakeRandItemUnique( siDollUnique, &clDollItem, 0, 0, &brareswitch, 0,0,0,0,0,0);
		clDollItem.SetItemNum(siDollNum);

		cltParametaBox clPB;
		clPB.Init(pclItemManager, &clipinfo2, NULL, pclki, pclGMki);
		clPB.Action(NULL, 0, PERSONITEM_WEAPON1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, GAMEMODE_SERVER, true);
		
		clSummon.clIP.SetLife(clPB.GetMaxLife());	// �⺻���� �͸� �����Ѵ�.( ��� PBBOX �� ����ؼ� Ǯ�� ä�����Ѵ�)
		clSummon.clIP.SetMana(clPB.GetMaxMana());

		if(pclCM->CR[charid]->GetSummonID())	clSummon.siStatus = SUMMON_STATUS_TAKEIN;
		else									clSummon.siStatus = SUMMON_STATUS_TAKEOUT;

		// DB�� ��û�Ѵ�. 
		sDBRequest_SummonRevive clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(), villageunique, siDollPos, siDollUnique, siDollNum, 
									  &clSummon, &clDollItem);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		// ���� ������ �����Ѵ�.
		cltGameMsgResponse_SummonRevive clinfo(pclchar->GetCharUnique(), siSuccess, pclinfo->siSummonID);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONREVIVE , sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	
}
// Base ��ȯ���� slot�� �ִ´�.
void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONSLOTIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SlotIn* pclinfo = (cltGameMsgRequest_SlotIn*)pclMsg->cData;
	// ��ȯ���� �ɸ��� ���� ����
	if(pclCM->IsValidID(id)  == false)						return;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar==NULL)										return;
	cltSummonInfo *pclSummonInfo = &pclchar->pclCI->clSummonInfo ;
	if(pclSummonInfo==NULL)									return;

	// ������ ��ȯ���� ���� �����ִ��� üũ�Ѵ�.
	cltSummon* pclSummon = pclSummonInfo->GetSummonFromSummonID(pclinfo->siSummonID);	
	if(pclSummon)											return;

	// �ϴ� ������ �ʿ� �ϰ��� ���° �ش� ���վ��̵�� � �ε����� �ִ��� �׸��� �� �ε����� ���վ��̵� �´���
	for ( SI08 sislotIndex = 0 ; sislotIndex < MAX_HAVE_SUMMON ; sislotIndex++) {
		// �ش� �ε����� ���� ���̵� ������ ��� Base�� �ε����� �������� �ϴ� ����, SummonId �� ���� ��� �ش� ��ȯ���� ���Կ� �־� �޶�� ������
		 if( pclinfo->siSummonID == pclSummonInfo->clSummonBase[ sislotIndex ].siSummonID )
		 {	
			 if ( sislotIndex > 2 && 
				 pclchar->pclCI->clBI.bSummonExtraSlot == false &&	

				 pclchar->pclCI->clBI.siSummonExtraSlotDate < pclTime->clDate.GetDateVary()) 
			 {
				 // Ŭ���̾�Ʈ�� ����� �˸���. 
				 ((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMON_FAIL_OVERDATE,  0, 0, pclchar->GetCharUnique());
				 return;
			 }
			 else
			 {
				 // base�� ��ȯ���� Slot�� �ִ´�.
				 sDBRequest_SummonSlotIn clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(),pclinfo->siSlotIndex, pclinfo->siSummonID );
				 pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			 }
			
		 }
	}
}
// ������ ��ȯ���� ������.
void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONSLOTOUT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SlotOut* pclinfo = (cltGameMsgRequest_SlotOut*)pclMsg->cData;
	// ��ȯ���� �ɸ��� ���� ����
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar==NULL)										return;
	cltSummonInfo *pclSummonInfo = &pclchar->pclCI->clSummonInfo ;
	if(pclSummonInfo==NULL)									return;

	SI32 SummonId	=	pclinfo->siSummonID;
	SI32 SlotIndex	=	pclinfo->siSummonIndex;

	cltSummon* pclSummon = pclSummonInfo->GetSummon(SlotIndex);
	if(pclSummon == NULL || pclSummon->siSummonID != SummonId)		return;

	SI32 siSummonCharID = pclchar->GetSummonID();

	if( pclCM->IsValidID(siSummonCharID) )
	{
		if( pclCM->IsAlive(siSummonCharID) == FALSE )
		{
			// ���� ��ȯ���� ������ �� ����.
			SendServerResponseMsg(0, SRVAL_SUMMON_FAIL_CANNOTSLOTOUTDEAD, 0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}
	if( pclSummon->siStatus == SUMMON_STATUS_DEAD )
	{
		// ���� ��ȯ���� ������ �� ����.
		SendServerResponseMsg(0, SRVAL_SUMMON_FAIL_CANNOTSLOTOUTDEAD, 0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	pclSummon->siStatus = SUMMON_STATUS_TAKEIN;
	pclchar->SendDBSummon(SETSUMMON_REASON_UPDATE, SlotIndex);

	// �ش� �ε����� �ش� ���վ��̵��� ��ȯ���� �ֳ� Ȯ��
	if( pclSummonInfo->clSummon[ SlotIndex ].siSummonID == SummonId ){
		// ��� �ش� ��ȯ���� summonindex ���� ���޶�� �Ѵ�.
		sDBRequest_SummonSlotOut clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siSummonID ,SlotIndex);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}

// ��ȯ���� ���� �������� �ڴ´�,.
void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONUSETON(cltMsg* pclMsg, SI32 id){
	
	cltGameMsgRequest_SummonEquipston* pclinfo = (cltGameMsgRequest_SummonEquipston*)pclMsg->cData;
	SI16	Weaponitemunique = 0;
	SI16	Armoritemunique	= 0 ;	

	// ��ȯ���� �ɸ��� ���� ����
	if(pclCM->IsValidID(id)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar==NULL)						return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)						return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	// �����ִ� ��ȯ���� �������� ���� �� �ִ�.
	if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)	return;

	if(pclinfo->siStonNum <= 0){
		// ���� ���ٴ� �޼��� �����ش�.
		SendServerResponseMsg(0, SRVAL_SUMMON_FREE_FAIL_STONNUMINCORRECT, 0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	switch(pclinfo->siStonType)
	{
	case STON_WEAPONE:
		{
			if (pclSummon->clIP.GetLevel() < pclSummon->siAttackWearStoneNum + pclinfo->siStonNum)
			{
				// �ִ� ���� �̻����� ���� �Ҽ� �����ϴ�
				SendServerResponseMsg(0, SRVAL_SUMMON_FREE_FAIL_CANNOTOVERUSESTON, 0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}
		}
		break;
	case STON_ARMOR:
		{
			if (pclSummon->clIP.GetLevel() < pclSummon->siDefenseWearStoneNum + pclinfo->siStonNum){
				// �ִ� ���� �̻����� ���� �Ҽ� �����ϴ�
				SendServerResponseMsg(0, SRVAL_SUMMON_FREE_FAIL_CANNOTOVERUSESTON, 0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}
		}
		break;
	}

	SI32 siStoneItemUnique = 0;

	switch(pclinfo->siStonType)
	{
	case STON_WEAPONE:		siStoneItemUnique = ITEMUNIQUE(5414);		break;
	case STON_ARMOR:		siStoneItemUnique = ITEMUNIQUE(5415);		break;
	}

	if( siStoneItemUnique <= 0 )					return;

	for( SI16 invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
	{
		cltItem* pclItem = &pclCM->CR[id]->pclCI->clCharItem.clItem[invennum];
		if(pclItem == NULL)			continue ;
		
		if ( pclItem->siUnique == siStoneItemUnique ) 
		{
			// �������� ã�� ������ �ľ��ؼ� ������ �ִ� �������� �� ���ų� �������� ��ȯ���� �����Ҽ� �ֵ��� �Ѵ�.
			if(pclItem->GetItemNum() >= pclinfo->siStonNum)
			{
				cltItem Useitem;
				Useitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[invennum]);
				Useitem.siItemNum = pclinfo->siStonNum;

				sDBRequest_UseItem useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), invennum, &Useitem, USEITEM_REASON_ENCHANT_MATERIAL);
				pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

				// DB�� ���� ��ȯ���� ���� �Ѵ�
				cltSummon clSummon;
				clSummon.Set(pclSummon);

				switch(pclinfo->siStonType)
				{
				case STON_WEAPONE:		clSummon.siAttackWearStoneNum += pclinfo->siStonNum;		break;
				case STON_ARMOR:		clSummon.siDefenseWearStoneNum += pclinfo->siStonNum;		break;
				}

				// ������ �ϼ��Ǿ����Ƿ� DB�� ��ȯ���� ������
				pclchar->SendDBSummon(SETSUMMON_REASON_SUMMONSTON, siSummonIndex, &clSummon);			
			}
			else
			{
				// ��� ���� ��� ���� �ʴ�.
				SendServerResponseMsg(0, SRVAL_SUMMON_FREE_FAIL_STONNUMNOTENOUGHSTON, 0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}
		}
	}
}

// [�߰� : Ȳ���� 2008. 2. 20 => ���� ��ȯ�� �ɷ�ġ ���������ϴ� �κ��� �Լ��� ��.]
void cltServer::Use_Summon_Bonus(cltGameMsgRequest_SummonUseBonusPoint* pclinfo, SI32 id)
{
	// ���ΰ� ��ȯ���� ���� �־���Ѵ�.
	if(pclCM->IsValidID(id)  == false)			return;

	//---------------------------------------------
	//
	//---------------------------------------------
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;
	//---------------------------------------------
	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	SI32 updatereason = SETSUMMON_REASON_UPDATE ;

	SI32 siSummonID = pclchar->GetSummonID();
	if(pclCM->IsValidID(siSummonID )  == true)
	{
		// ��ȯ�� �ڽ��� ���� �ִ� ������ ���� ���� �ִ� ������ �ٸ��� �ȵȴ�.
		if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex) 
		{
			if ( pclinfo->bStatusInit == false )
			{
				// ĳ���Ͱ� ��� �־���ϰ� ���ʽ��� ���� �־�� �� �� �ִ�.
				if(pclCM->CR[siSummonID]->pclCI->clIP.GetBonus() >0)
				{
					switch(pclinfo->siBonusType)
					{
					case 0:
						pclCM->CR[siSummonID]->pclCI->clIP.IncreaseStr(1);
						pclCM->CR[siSummonID]->pclCI->clIP.DecreaseBonus(1);
						break;
					case 1:
						pclCM->CR[siSummonID]->pclCI->clIP.IncreaseDex(1);
						pclCM->CR[siSummonID]->pclCI->clIP.DecreaseBonus(1);
						break;
					case 2:
						pclCM->CR[siSummonID]->pclCI->clIP.IncreaseMag(1);
						pclCM->CR[siSummonID]->pclCI->clIP.DecreaseBonus(1);
						break;
					case 3:
						pclCM->CR[siSummonID]->pclCI->clIP.IncreaseVit(1);
						pclCM->CR[siSummonID]->pclCI->clIP.DecreaseBonus(1);
						break;
					default:
						return ;
					}
				}
			}
			else
			{
				cltKindInfo* pclki = NULL;
				if( pclSummon->siKind >= 0 && pclSummon->siKind < MAX_KIND_NUMBER )
				{
					//pclki = pclKindInfoSet->pclKI[pclSummon->siKind];
					if(IsCountrySwitch(Switch_Summon_Separate)) 
					{
						pclki = pclKindInfoSet->pclSummonKI[pclSummon->siKind];
					}
					else
					{
						pclki = pclKindInfoSet->pclKI[pclSummon->siKind];
					}
				}

				if(pclki == NULL)							return;

				switch(pclinfo->siBonusType)
				{
				case IDC_BUTTON_STR_INIT:	if(pclCM->CR[siSummonID]->pclCI->clIP.GetStr() <= pclki->clBA.GetStr())return ;	break;
				case IDC_BUTTON_DEX_INIT:	if(pclCM->CR[siSummonID]->pclCI->clIP.GetDex() <= pclki->clBA.GetDex())return ;	break;
				case IDC_BUTTON_INT_INIT:	if(pclCM->CR[siSummonID]->pclCI->clIP.GetMag() <= pclki->clBA.GetMag())return ;	break;
				case IDC_BUTTON_VIT_INIT:	if(pclCM->CR[siSummonID]->pclCI->clIP.GetVit() <= pclki->clBA.GetVit())return ;	break;
				default: return ;
				}

				// ���ºκ��ʱ�ȭ�̿���� �����ϴ��� Ȯ���Ѵ�. 
				//SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(14095);
				SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(ITEMUNIQUE(24035));
				if(itempos < 0)
				{
					return ;
				}

				// ���ºκ��ʱ�ȭ�̿���� �Ҹ��Ѵ�. 
				cltItem clItem;
				clItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[itempos]);
				clItem.SetItemNum(1);

				sDBRequest_UseItem clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), itempos, &clItem,USEITEM_REASON_TICKET);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);


				// ������ ���� ���ʽ��� �ִ´�. 
				switch(pclinfo->siBonusType)
				{
				case IDC_BUTTON_STR_INIT:	
					pclCM->CR[siSummonID]->pclCI->clIP.DecreaseStr(1);
					pclCM->CR[siSummonID]->pclCI->clIP.IncreaseBonus(1);
					break;

				case IDC_BUTTON_DEX_INIT:
					pclCM->CR[siSummonID]->pclCI->clIP.DecreaseDex(1);
					pclCM->CR[siSummonID]->pclCI->clIP.IncreaseBonus(1);
					break;

				case IDC_BUTTON_INT_INIT:
					pclCM->CR[siSummonID]->pclCI->clIP.DecreaseMag(1);
					pclCM->CR[siSummonID]->pclCI->clIP.IncreaseBonus(1);
					break;

				case IDC_BUTTON_VIT_INIT:
					pclCM->CR[siSummonID]->pclCI->clIP.DecreaseVit(1);
					pclCM->CR[siSummonID]->pclCI->clIP.IncreaseBonus(1);
					break;

				default: return ;
				}

				SI32 updatereason = SETSUMMON_REASON_PARTINIT ;
			}
		}
		pclCM->CR[siSummonID]->SetUpdateSwitch(UPDATE_IP,   true, 0);
	}

	// ĳ������ IP�� Ŭ���̾�Ʈ�� ���� �� �ְ� �Ѵ�. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_SUMMON,		true, 0);

	//---------------------------------------------
	// DB�� ��ȯ���� �����Ѵ�.
	//---------------------------------------------
	pclchar->SendDBSummon(updatereason, siSummonIndex);

	// ���� ���� : �ڱ��� 2009.06.19
	// ��ȯ���� �������ͽ��� �Ķ���� ���� ��� �ؼ� �׿� ���� �����Ǵ� ������ �����Ѵ�. 
	// �������� �ֱ������� �����Ͻø�
	// �� �ð� ���� �������ͽ����� ���� ���� �ʾ� ��ġ �ʴ� ��� �߻�
	// ��) �ִ� ü��ġ�� �������� �ʾ� Ŭ���̾�Ʈ�� hp�������� �ʴ´�.
	// ĳ���� �Ŵ����� ��ȯ��
	cltCharServer* pclSummonChar = (cltCharServer*) pclCM->CR[siSummonID];
	if(pclSummonChar != NULL)
		pclSummonChar->ParametaBoxAction();
}

// [�߰� : Ȳ���� 2008. 2. 20 => ���ο� ��ȯ�� �ɷ�ġ ���������ϴ� �κ��� �Լ��� ��.]
void cltServer::New_Use_Summon_Bonus(cltGameMsgRequest_SummonUseBonus* pclinfo, SI32 id)
{
	// ���ΰ� ��ȯ���� ���� �־���Ѵ�.
	if(pclCM->IsValidID(id)  == false)
		return;

	// �޽����� ���� ���� ���ϵ��� ���´�
	if ( pclCM->CR[id]->CheckLastMsgClock(1000) == true )
	{
		return ;
	}

	//---------------------------------------------
	//
	//---------------------------------------------
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique);
	if(pclCM->IsValidID(charid)  == false)
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)
		return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->m_siSummonID);
	if(pclSummon==NULL)
		return;
	//---------------------------------------------

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->m_siSummonID);

	SI32 updatereason = SETSUMMON_REASON_UPDATE ;

	SI32 siSummonID = pclchar->GetSummonID();
	if(pclCM->IsValidID(siSummonID )  == true)
	{
		// ��ȯ�� �ڽ��� ���� �ִ� ������ ���� ���� �ִ� ������ �ٸ��� �ȵȴ�.
		if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex) 
		{
			// ĳ���Ͱ� ��� �־���ϰ� ���ʽ��� ���� �־�� �� �� �ִ�.
			SI32 siSummonBonus = pclCM->CR[siSummonID]->pclCI->clIP.GetBonus();
			if ( (siSummonBonus > 0) && (pclinfo->m_siDecreaseBonus > 0) && (siSummonBonus >= pclinfo->m_siDecreaseBonus) )
			{
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseStr( pclinfo->m_siStr );
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseDex( pclinfo->m_siAgi );
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseMag( pclinfo->m_siWis );
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseVit( pclinfo->m_siVit );
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseWis( pclinfo->m_siWisdom );
				pclCM->CR[siSummonID]->pclCI->clIP.IncreaseHnd( pclinfo->m_sihand);

				pclCM->CR[siSummonID]->pclCI->clIP.DecreaseBonus( pclinfo->m_siDecreaseBonus );
			}
		} 
		pclCM->CR[siSummonID]->SetUpdateSwitch(UPDATE_IP, true, 0);
	}

	// ĳ������ IP�� Ŭ���̾�Ʈ�� ���� �� �ְ� �Ѵ�. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_SUMMON, true, 0);

	//---------------------------------------------
	// DB�� ��ȯ���� �����Ѵ�.
	//---------------------------------------------
	pclchar->SendDBSummon(updatereason, siSummonIndex);

	// ���� ���� : �ڱ��� 2009.06.19
	// ��ȯ���� �������ͽ��� �Ķ���� ���� ��� �ؼ� �׿� ���� �����Ǵ� ������ �����Ѵ�. 
	// �������� �ֱ������� �����Ͻø�
	// �� �ð� ���� �������ͽ����� ���� ���� �ʾ� ��ġ �ʴ� ��� �߻�
	// ��) �ִ� ü��ġ�� �������� �ʾ� Ŭ���̾�Ʈ�� hp�������� �ʴ´�.
	cltCharServer* pclSummonChar = (cltCharServer*)pclCM->CR[siSummonID];
	if(pclSummonChar != NULL)
		pclSummonChar->ParametaBoxAction();
}

void cltServer::DoMsg_GAMEMSG_REQUEST_USESUMMONBONUS(cltMsg* pclMsg, SI32 id)
{
    if( pclClient->IsCountrySwitch( Switch_SummonTramsform ) )
	{
		cltCharServer* pclChar = pclCM->GetCharServer(id);
		if( NULL == pclChar ) return; 

		// ���� ����ϴ� ��ȯ���� �������̸� ������ �Ұ����ϰ� �Ѵ�.
		if( pclChar->pclCI->clSummonInfo.IsSummonTranform( pclChar->siSummonIndex ) )
		{
			SendServerResponseMsg( 0, SRVAL_RETURN_SUMMON_TRANSFORM_USE_BONUS, 0, 0, id );
			return;
		}
	}
	

	// [�߰� : Ȳ���� 2008. 2. 20 => ��ȯ�� �ɷ�ġ ���� ������.]
	if( true == pclClient->IsCountrySwitch( Switch_Summon_Ability_Reform ) )
	{	
		cltGameMsgRequest_SummonUseBonus* pclinfo = (cltGameMsgRequest_SummonUseBonus*)pclMsg->cData;
		New_Use_Summon_Bonus( pclinfo, id );
	}
	else
	{
		cltGameMsgRequest_SummonUseBonusPoint* pclinfo = (cltGameMsgRequest_SummonUseBonusPoint*)pclMsg->cData;
		Use_Summon_Bonus( pclinfo, id );
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_TAKEINOUT(cltMsg* pclMsg, SI32 id)
{
	// ���ΰ� ��ȯ���� ���� �־���Ѵ�.
	if(pclCM->IsValidID(id)  == false)	return;

	//---------------------------------------------
	//
	//---------------------------------------------
	cltGameMsgRequest_SummonTakeInOut* pclinfo = (cltGameMsgRequest_SummonTakeInOut*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;
	if(pclCM->CR[id]->GetCharUnique() != pclCM->CR[charid]->GetCharUnique())		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclchar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclchar) )
				return;
		}
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	switch(pclinfo->siStatus)
	{
	case SUMMON_STATUS_TAKEOUT:	
		{
			/*if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
			{
				//if( false == pclchar->pclCI->clSummonInfo.IsSummonTranformTickCount() ) return;
			}*/

			//---------------------------------------------
			// ��ȯ���� TAKE IN �����̾���Ѵ�.
			//---------------------------------------------
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEIN) return;

			//---------------------------------------------
			// DB�� ��ȯ���� �����Ѵ�.
			//---------------------------------------------
			cltSummon clSummon;
			clSummon.Set(pclSummon);
			clSummon.siStatus = SUMMON_STATUS_TAKEOUT;
			pclchar->SendDBSummon(SETSUMMON_REASON_TAKEOUT, siSummonIndex, &clSummon);
		}
		break;
	case SUMMON_STATUS_TAKEIN:	
		{
			/*if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
			{
				//if( false == pclchar->pclCI->clSummonInfo.IsSummonTranformTickCount() ) return;
			}*/
			//---------------------------------------------
			// ��ȯ���� ���ͼ� ������� ������ �ȵȴ�.
			//---------------------------------------------
			SI32 siSummonID = pclchar->GetSummonID();

			// �׷� ID�� ���ٸ� 
			if( pclCM->IsValidID(siSummonID) == FALSE )	
			{
				if( pclSummon->siStatus == SUMMON_STATUS_TAKEOUT )
				{
					if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
					{
						// ��ȯ���� ���ŵ��ִ� ���¸� ������ �����Ѵ�.
						if( pclchar->pclCI->clSummonInfo.IsSummonTranform( pclchar->GetSummonIndex() ) )
						{
							pclchar->TransformSummon( pclCM, GetSummonTransformManager() );
							siSummonID = pclchar->GetSummonID();
						}
					}

					if(pclSummon->clIP.GetLife()>0)	pclSummon->siStatus = SUMMON_STATUS_TAKEIN;
					else							pclSummon->siStatus = SUMMON_STATUS_DEAD;

					//==========================================
					// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
					//==========================================
					cltGameMsgResponse_Summon clInfo1(pclchar->GetCharUnique(), siSummonIndex, pclSummon);
					cltMsg clMsg1(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo1), (BYTE*)&clInfo1);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg1);

					// �������׵� ������ ���Ž�Ų��.
					pclchar->siChildCharUnique = 0;
					cltGameMsgResponse_ChangeSummonStatus clInfo2(id, pclchar->siChildCharUnique, siSummonIndex);
					cltMsg clMsg2(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo2), (BYTE*)&clInfo2);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg2);
					return;
				}
			}

			// �׾��ִٸ� TAKEIN�� �ȵȴ�.
			if( pclCM->IsAlive(siSummonID) == FALSE )			return;

			//---------------------------------------------
			// ��ȯ���� TAKE OUT �����̾���Ѵ�.
			//---------------------------------------------
			if( pclSummon->siStatus != SUMMON_STATUS_TAKEOUT )	return;

			//---------------------------------------------
			// DB�� ��ȯ���� �����Ѵ�.
			//---------------------------------------------
			pclchar->SendDBSummon( SETSUMMON_REASON_UPDATE, siSummonIndex );

			cltSummon clSummon;
			clSummon.Set(pclSummon);
			clSummon.siStatus = SUMMON_STATUS_TAKEIN;
			pclchar->SendDBSummon( SETSUMMON_REASON_TAKEIN, siSummonIndex, &clSummon );
		}
		break;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONATTACKCHANGE(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	// 
	//---------------------------------------------
	cltGameMsgRequest_SummonAttackChange* pclinfo = (cltGameMsgRequest_SummonAttackChange*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;
	//---------------------------------------------

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	// ���ݼӼ��� �˻��Ѵ�.
	if(	pclinfo->siAttackType !=  SUMMON_ATTACKTYPE_ACTIVE &&
		pclinfo->siAttackType !=  SUMMON_ATTACKTYPE_AVOID) return;

	// ��ȯ�� ���ݼӼ��� �����Ѵ�.
	if(pclSummon->siAttackType != pclinfo->siAttackType)
	{
		pclSummon->siAttackType = (SI08)pclinfo->siAttackType;
		
		// DB�� ��ȯ���� �����Ѵ�.
		pclchar->SendDBSummon(SETSUMMON_REASON_UPDATE, siSummonIndex);

		// ����Ʈ ������Ʈ
		pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_SUMMONCHANGESTATUS);
		
		cltGameMsgResponse_SummonAttackChange clInfo(pclchar->GetCharUnique(), 1, pclinfo->siSummonID, pclSummon->siAttackType);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONATTACKCHANGE, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}


void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONEVOLVE(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	//
	//---------------------------------------------
	cltGameMsgRequest_SummonEvolve* pclinfo = (cltGameMsgRequest_SummonEvolve*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	//---------------------------------------------
	// �������� �����ϰ� ������ �ȵȴ�
	//---------------------------------------------
	if ( TRUE == pclchar->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{
		return;
	}

	//---------------------------------------------
	// ���� ��ȭ���ε� �� ���� �޽����� ���� ���ư���.
	//---------------------------------------------
	if(pclchar->bIsEvolving == true) return ;

	//---------------------------------------------
	// ���� ������ SUMMON
	//---------------------------------------------
	SI32 siNewKind= pclinfo->siKind;

	//---------------------------------------------
	// ��ȯ���� �������� ������ �����ų�� ����.
	//---------------------------------------------
	SI32 siSummonID = pclchar->GetSummonID();
	if(pclCM->IsValidID(siSummonID)  == FALSE)	return;

	//---------------------------------------------
	// �׾������� ���ư���.
	//---------------------------------------------
	if(pclSummon->clIP.GetLife()<=0)	return;

	//--------------------------------
	// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
	//--------------------------------
	SI32 kind = pclSummon->siKind;
	if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return;

	//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
	cltKindInfo* pclki = NULL;
	if(IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclKindInfoSet->pclSummonKI[kind];
	}
	else
	{
		pclki = pclKindInfoSet->pclKI[kind];
	}

	if(pclki == NULL)							return;
	if(pclki->siSummonRank <= 0)				return;

	//---------------------------------------------
	// ��ȭ LEVEL���� ������ ���ư���. ��ȭ�� ��
	//---------------------------------------------
	if ( pclinfo->siMode == 0 && pclSummon->clIP.GetLevel() < pclki->siEvolveLevel )
		return;

	//--------------------------------
	// ��ȭ���� ��ȯ�� Kind�� �����Ѵ�.
	//--------------------------------
	if(siNewKind <= 0 || siNewKind >= MAX_KIND_NUMBER)	return;
	//cltKindInfo* pclnewki = pclKindInfoSet->pclKI[siNewKind];
	cltKindInfo* pclnewki = NULL;
	if(IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclnewki = pclKindInfoSet->pclSummonKI[siNewKind];
	}
	else
	{
		pclnewki = pclKindInfoSet->pclKI[siNewKind];
	}

	if(pclnewki == NULL)						return;
	if(pclnewki->siSummonRank <= 0)				return;

	//--------------------------------
	// ��ȭ��Ű������ �غ� ����
	//--------------------------------
	SI32 siSuccess		= 1;
	SI32 siTicketPos	= 0;
	SI32 siTicketUnique = ITEMUNIQUE(5370);	// �ູ�ǵ�
	SI32 siTicketNum	= 10;
	bool bItemUse = true ;
	bool bQuestEvolve = false ;
	//--------------------------------
	// ��ȭ���� ��ȯ���� ��ȭ���� 1�ܰ踸 ���̰� ����. 
	//--------------------------------
	switch(pclinfo->siMode)
	{
	case SUMMONEVOLVE_EVOLVE: // ��ȭ
		{
			if(pclnewki->siSummonRank != pclki->siSummonRank + 1)	return;
			if(pclnewki->siSummonRank >  LIMIT_SUMMON_RANK_EVOLVE)	return;
			if(pclnewki->bSummonMall  == TRUE                   )   return; // ������ �� ��ǰ���δ� ��ȭ �ȵ�
			
			siTicketUnique = GetSummonTicketUnique(pclki->siSummonRank);
			siTicketNum	= GetSummonTicketNum(pclki->siSummonRank);		


			SI16 questtype, questunique, para1, para2;
			SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTIONRANK;
			if(pclchar->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
			{
				if ( !pclchar->pclCI->clBI.bQuestEvolve )
				{
					siTicketNum = 0 ;
					bQuestEvolve = true ;
				}
			}

			questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTION;
			if(pclchar->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
			{
				if ( !pclchar->pclCI->clBI.bQuestEvolve )
				{
					siTicketNum = 0 ;
					bQuestEvolve = true ;
				}
			}
		}
		break;
	case SUMMONEVOLVE_DEVOLUTION: // ��ȭ
		{
			if(pclnewki->siSummonRank != pclki->siSummonRank - 1)	return;
			if(pclnewki->bSummonMall  == TRUE                   )   return; // ������ �� ��ǰ���δ� ��ȭ �ȵ�
		}
		break;
	case SUMMONEVOLVE_TRANSFORM: // ��ȯ
		{
			if(pclnewki->siSummonRank != pclki->siSummonRank)	return;
			if(pclnewki->bSummonMall  == TRUE                   )   return; // ������ �� ��ǰ���δ� ��ȭ �ȵ�
		}
		break;
	default:
		return ;
	}

	if ( siTicketNum )
	{
		///////////////////////////////////////////////////////
		// �̿�� Ȯ�� 
		siTicketPos = pclCM->CR[charid]->pclCI->clCharItem.GetItemPos(siTicketUnique);
		if( siTicketPos < PERSONITEM_INV0 || siTicketPos >= MAX_ITEM_PER_PERSON )							siSuccess = -1;
		if(siSuccess > 0 && pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum < siTicketNum)	siSuccess = -1;
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		bItemUse = false ;
	}
	
	//KHY - 0909 - �������� ���� - ��ȯ���� ��ȭ�� �൹�� ���� ����,Ȯ���� ���� ���� ������ �ش�.
	if(pclClient->IsCountrySwitch(Switch_MudangPresent))
	{
		SI32 siMudangPresent = ITEMUNIQUE(13333);	// ���� ��������.
		
		if((siSuccess > 0)&&(siTicketUnique == ITEMUNIQUE(5370))&&(siTicketNum > 0)) // �����̸鼭 �൹�� ����ؾ߸� ����Ѵ�.
		{	
			// - �ټ� ����.
			SI32 numPurse = 0; // �ְԵǴ� ���� ���� �ټ�.
			SI32 selectPursePer = ((siTicketNum * pclnewki->siSummonRank * 2) / 10);
			SI32 randval = (rand()%100)+1;
			
			if(selectPursePer > 100)
			{
				numPurse = selectPursePer/100;  // 100%�� 1���� ������ �ش�.
				selectPursePer = selectPursePer%100; //�������� Ȯ�� ������.
			}

			if(randval <= selectPursePer)
				numPurse += 1;
			/////////////////////////////////////////////////////////////////////
			// - ������ ����. - ���� ��������			
			if(numPurse > 0)
			{
				pclchar->GiveItem( siMudangPresent, numPurse, INPUTITEMPERSON_OPTION_MUDANGPRESENT, 0 );
			}

			// ���� ������ �˸���.
			SendServerResponseMsg(0, SRVAL_SUMMON_ADD_MUDANGPRESENT, siMudangPresent, numPurse, pclchar->GetCharUnique() );	
		}
	}

	if(siSuccess > 0)
	{
		// ��ǰ ��� ��踦 ����.
		pclItemManager->AddUseNum(siTicketUnique, siTicketNum);

		//���ο� ��� - ��ǰ ��� ��踦 ����.
		//NStatistics_Add("Item", siTicketUnique, "UseNum", siTicketNum);

		// ��ȯ���� ��ȯ�� ������ Unique�� �ش�.
		SI32 villageunique  = pclCM->CR[charid]->GetCurrentVillageUnique();

		//====================================================
		// ���� ��ȭ�� ��ȯ���� �����Ѵ�.
		//====================================================
		cltPIPInfoCommon	clipinfo;
		cltPIPInfo			clipinfo2;
		
		//cltKindInfo* pclki = pclKindInfoSet->pclKI[siNewKind];
		cltKindInfo* pclki = NULL;
		cltGMCommandKindInfo* pclGMki = NULL;

		if(IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclKindInfoSet->pclSummonKI[siNewKind];
			pclGMki = pclKindInfoSet->pclGMCommandKindInfo[siNewKind];
		}
		else
		{
			pclki = pclKindInfoSet->pclKI[siNewKind];
			pclGMki = pclKindInfoSet->pclGMCommandKindInfo[siNewKind];
		}
		if(NULL == pclki) 
			return;
		if(NULL == pclGMki)
			return;

		clipinfo.SetBasicAbility(&pclki->clBA);	

		clipinfo2.Set(&clipinfo);
		cltParametaBox clPB;
		clPB.Init(pclItemManager, &clipinfo2, NULL, pclki, pclGMki);
		clPB.Action(NULL, 0, PERSONITEM_WEAPON1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, GAMEMODE_SERVER, true);

		clipinfo.SetLife(clPB.GetMaxLife());	// �⺻���� �͸� �����Ѵ�.( ��� PBBOX �� ����ؼ� Ǯ�� ä�����Ѵ�)
		clipinfo.SetMana(clPB.GetMaxMana());

		//cyj ��ȯ���� Luk�� ���¹̳��̹Ƿ� ���� ���� �־���
#ifdef _SAFE_MEMORY
		SI32 summonskill = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0], id );
#else
		SI32 summonskill = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem, id );
#endif

		clipinfo.SetLuk(pclClient->GetMaxStaminaValue(summonskill, siNewKind) );
		
		// ������ ����ġ�� ������ ��ӹ޴´�.
		clipinfo.siExp	 = pclSummon->clIP.siExp;
		clipinfo.siLevel = pclSummon->clIP.siLevel;
		clipinfo.siBonus = clipinfo.siLevel * 5;
		
		
		cltSummonScroll clscroll(pclki->siSummonScroll[0], 0, pclki->siSummonScroll[1], 0);	

		cltSummonItemInfo clItemInfo;
		clItemInfo.Init();
		// DB�� ��ȯ���� �����Ѵ�.
		cltSummon clSummon(	pclSummon->siSummonID,	
							siNewKind,					
							pclSummon->szName, 
							SUMMON_STATUS_TAKEIN,	
							SUMMON_ATTACKTYPE_AVOID,	
							pclSummon->siIdentity, 
							0,	
							pclSummon->siAttackWearStoneNum,	
							pclSummon->siDefenseWearStoneNum,
							&clipinfo,				
							&clscroll,
							pclSummon->m_siTranformStamina );

		//==================================
		// ��ȭ�̿���� 2�徲�°������´�.
		pclchar->bIsEvolving = true;
		//==================================

		cltItem clTicketItem;
		SI16 brareswitch = 0;
		pclClient->pclItemManager->MakeRandItemUnique( siTicketUnique, &clTicketItem, 0, 0, &brareswitch, 0,0,0,0,0,0);
		clTicketItem.SetItemNum(siTicketNum);

		// DB�� ��û�Ѵ�. 
		sDBRequest_SummonEvolve clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(), villageunique,siTicketPos,
									  siTicketUnique, siTicketNum, &clSummon,bQuestEvolve,bItemUse,pclinfo->siMode, 
									  &clTicketItem, kind);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		// ���� ������ �����Ѵ�.
		cltGameMsgResponse_SummonEvolve clinfo(pclchar->GetCharUnique(), siSuccess, pclinfo->siSummonID, siNewKind,pclinfo->siMode);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONEVOLVE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONSCROLL(cltMsg* pclMsg, SI32 id)
{
	//---------------------------------------------
	//
	//---------------------------------------------
	cltGameMsgRequest_SummonScroll* pclinfo = (cltGameMsgRequest_SummonScroll*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;
	//---------------------------------------------
	
	//---------------------------------------------
	// ���� ��ȭ�� Scroll
	//---------------------------------------------
	SI32 siScrollUnique		= pclinfo->siScrollUnique;
	// �������� �������� Ȯ���Ѵ�. 
	SI64 atb =	pclItemManager->GetItemAtb(siScrollUnique);
	if((atb & ITEMATB_SCROLL) ==0)		return;

	// ������ ������ Ȯ���Ѵ�. 
	cltItemInfo* pclscrollinfo = pclItemManager->FindItemInfo(siScrollUnique);
	if(pclscrollinfo == NULL)			return;

	// ������ ����� Ȯ���Ѵ�. 
	SI32 function	= pclscrollinfo->siScrollFunction;
	if(function <= 0)					return;

	// ������ ���� �ɷ��� ���Ѵ�.
	SI32 siAddScrollPercent = pclscrollinfo->siScrollAbility;
	if(siAddScrollPercent <= 0)			return;

	//---------------------------------------------
	// ��ȯ���� �������� ������ �����ų�� ����.
	//---------------------------------------------
	SI32 siSummonID = pclchar->GetSummonID();
	if(pclCM->IsValidID(siSummonID)  == FALSE)	return;

	//---------------------------------------------
	// �׾������� ���ư���.
	//---------------------------------------------
	if(pclSummon->clIP.GetLife()<=0)	return;


	//---------------------------------------------
	// ��ȭ���Ѻ��� ũ�� ���ư���.
	//---------------------------------------------
	if(pclSummon->clScroll.FindUnique(siScrollUnique) == FALSE)	return;
	SI32 CurrPercent = pclSummon->clScroll.GetPercent(siScrollUnique);
	SI32 siMaxSrollPercent = min(LIMIT_SUMMON_ADD_SCROLL_PERCENT, pclSummon->clIP.GetLevel()*10/2 );
	if(CurrPercent >= siMaxSrollPercent)	return;
	if(CurrPercent + siAddScrollPercent >= siMaxSrollPercent)
	{
		siAddScrollPercent = siMaxSrollPercent - CurrPercent;
	}

	
	//--------------------------------
	// ��ȭ��Ű������ �غ� ����
	//--------------------------------
	SI32 siSuccess		= 1;
	SI32 siScrollPos	= 0;
	SI32 siScrollNum	= 1;
	if(siScrollUnique <= 0 || siScrollNum <= 0)		return;

	///////////////////////////////////////////////////////
	// ���� Ȯ�� 
	siScrollPos = pclCM->CR[charid]->pclCI->clCharItem.GetItemPos(siScrollUnique);
	if( siScrollPos < PERSONITEM_INV0 || siScrollPos >= MAX_ITEM_PER_PERSON )							siSuccess = -1;
	if(siSuccess > 0 && pclCM->CR[id]->pclCI->clCharItem.clItem[siScrollPos].siItemNum < siScrollNum)	siSuccess = -1;
	//////////////////////////////////////////////////////////////////////////
	
	if(siSuccess > 0)
	{
		// ��ǰ ��� ��踦 ����.
		pclItemManager->AddUseNum(siScrollUnique, siScrollNum);

		//���ο� ��� - ��ǰ ��� ��踦 ����.
		//NStatistics_Add("Item", siScrollUnique, "UseNum", siScrollNum);

		pclStatisticsManager->clDailyStatistics.siScrollSummonNumber += siScrollNum;	// ���ó���� �Ѵ�.
 
		// ��ȯ���� ��ȯ�� ������ Unique�� �ش�.
		SI32 villageunique  = pclCM->CR[charid]->GetCurrentVillageUnique();

		//====================================================
		// ���� ��ȭ�� ��ȯ���� �����Ѵ�.
		//====================================================
		//---------------------------------------------
		// ��ȯ���� ��ȭ��Ű������ ������ �����Ѵ�.
		//---------------------------------------------
		cltSummon clSummon;
		clSummon.Set(pclSummon);
		clSummon.clScroll.AddPercent(siScrollUnique, siAddScrollPercent);

		// DB�� ��û�Ѵ�. 
		sDBRequest_SummonScroll clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(), villageunique, siScrollPos, siScrollUnique, siScrollNum, &clSummon);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		
	}
	else
	{
		// ���� ������ �����Ѵ�.
		cltGameMsgResponse_SummonScroll clinfo(pclchar->GetCharUnique(), siSuccess, pclinfo->siSummonID);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONSCROLL, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMON_STATUSINIT(cltMsg* pclMsg,SI32 id)
{
	if(pclCM->IsValidID(id)  == false)	return;

	//---------------------------------------------
	//
	//---------------------------------------------
	cltGameMsgRequest_Summon_StatusInit* pclinfo = (cltGameMsgRequest_Summon_StatusInit*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)	return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	//---------------------------------------------
	// ��ȯ���� �׾� ������ �ȵȴ�.
	//---------------------------------------------
	if(pclSummon->siStatus == SUMMON_STATUS_DEAD) return;

	//---------------------------------------------
	// ��ȯ���� ��� �����ϰ� ������ �ȵȴ�
	//---------------------------------------------
	if ( TRUE == pclchar->pclCI->clSummonInfo.IsHaveEquipItem(siSummonIndex) )
	{
		SendServerResponseMsg(0, SRVAL_SUMMON_STATUSINIT_FAIL_HAVEITEM, 0, 0, pclchar->GetCharUnique() );
		return;
	}

	//--------------------------------
	// �ʱ�ȭ��Ű�� ���� �غ�
	//--------------------------------
	//cyj �����ʱ�ȭ�̿�� ����ũ���� 14090->24030
	//SI32 itemunique = 14090 ;  // �����ʱ�ȭ�̿��
	
	//[����] ĳ���� ���� �ʱ�ȭ �����Ⱓ���� ������ ���. 
	cltItem clitem;
	SI32	pos = 0;
	if(pclClient->pclEventTimeManager->InEventTime("char_ability_init", &sTime) )
	{
		clitem.Init();	
		pos = 0;
	}   
	else
	{
		SI32 itemunique			= ITEMUNIQUE(24030) ;  // �����ʱ�ȭ�̿��
		SI32 siEventItemUnique	= ITEMUNIQUE(24125) ;  // �����ʱ�ȭ�̿��(�̺�Ʈ)

		if (	pclchar->pclCI->clCharItem.GetItemNum(itemunique) <= 0 &&
				pclchar->pclCI->clCharItem.GetItemNum(siEventItemUnique) <= 0)
			return ;

		pos = pclchar->pclCI->clCharItem.GetItemPos(siEventItemUnique);
		if(pos < 0)
		{
			pos = pclchar->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos < 0)
				return;
		}
		
		clitem.Init();	
		clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos]);
		clitem.SetItemNum(1);
	}


	//====================================================
	// �ʱ�ȭ�� ��ȯ���� �����Ѵ�.
	//====================================================
	cltPIPInfoCommon	clipinfo;
	cltPIPInfo			clipinfo2;
	//--------------------------------
	// ��ȯ���� kind�� �����Ѵ�.
	//--------------------------------
	SI32 kind = pclSummon->siKind;
	if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return;
	
	cltKindInfo* pclki = NULL;
	cltGMCommandKindInfo*	pclGMki = NULL;

	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclKindInfoSet->pclSummonKI[kind];
		pclGMki = pclKindInfoSet->pclGMCommandKindInfo[kind];
	}
	else
	{
		pclki = pclKindInfoSet->pclKI[kind];
		pclGMki = pclKindInfoSet->pclGMCommandKindInfo[kind];
	}
	
	if(pclki == NULL)							return;
	if(pclki->siSummonRank <= 0)				return;
	if(pclGMki == NULL)							return;

	clipinfo.SetBasicAbility(&pclki->clBA);	

	clipinfo2.Set(&clipinfo);
	cltParametaBox clPB;
	clPB.Init(pclItemManager, &clipinfo2, NULL, pclki, pclGMki);
	clPB.Action(NULL, 0, PERSONITEM_WEAPON1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, GAMEMODE_SERVER, true);

	clipinfo.SetLife(clPB.GetMaxLife());	// �⺻���� �͸� �����Ѵ�.( ��� PBBOX �� ����ؼ� Ǯ�� ä�����Ѵ�)
	clipinfo.SetMana(clPB.GetMaxMana());

	//cyj ��ȯ���� Luk�� ���¹̳��̹Ƿ� ���� ���� �־���
#ifdef _SAFE_MEMORY
	SI32 summonskill = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0], id );
#else
	SI32 summonskill = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem, id );
#endif

	clipinfo.SetLuk(pclClient->GetMaxStaminaValue(summonskill, kind));

	// ������ ����ġ�� ������ ��ӹ޴´�.
	clipinfo.siExp	 = pclSummon->clIP.siExp;
	clipinfo.siLevel = pclSummon->clIP.siLevel;
	clipinfo.siBonus = clipinfo.siLevel * 5;

	cltSummonScroll clscroll;
	clscroll.Set(&pclSummon->clScroll);

	cltSummonItemInfo clItemInfo;
	clItemInfo.Init();

	cltSummon clSummon(	pclSummon->siSummonID,
						kind,
						pclSummon->szName,
						SUMMON_STATUS_TAKEIN,
						SUMMON_ATTACKTYPE_AVOID,	
						pclSummon->siIdentity, 
						0, 
						pclSummon->siAttackWearStoneNum, 
						pclSummon->siDefenseWearStoneNum, 
						&clipinfo,
						&clscroll,
						pclSummon->m_siTranformStamina	);

	sDBRequest_Summon_StatusInit clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(), pos,&clitem , &clSummon);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMON_SETAUTOHEAL(cltMsg* pclMsg,SI32 id)
{
	if(pclCM->IsValidID(id)  == false)	return;

	cltGameMsgRequest_Summon_SetAutoHeal* pclinfo = (cltGameMsgRequest_Summon_SetAutoHeal*)pclMsg->cData;
	SI32 charid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(charid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	if(pclchar==NULL)	return;

	cltSummonInfo *pclSummonInfo = &pclchar->pclCI->clSummonInfo ;
	if(pclSummonInfo==NULL)	return;

	if ( pclinfo->siSelectAutoHeal < 0 || pclinfo->siSelectAutoHeal > 2 ) return ;

	sDBRequest_Summon_SetAutoHeal clMsg(charid, pclCM->CR[charid]->pclCI->GetPersonID(),pclinfo->siSelectAutoHeal,pclinfo->bAutoHeal);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYSUMMONINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_TradeMerchantBuySummonInfo * pclinfo = (cltGameMsgRequest_TradeMerchantBuySummonInfo *)pclMsg->cData;

	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	// ��ȯ�� ���� Ȯ��
	if ( ! pclCM->CR[id]->pclCI->clSummonInfo.HaveSummon() )
	{
		return;
	}

	SI32 siMySummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	// ��ȯ���� ��ȯ�Ǿ� �ִ��� Ȯ��
	SI32 siSummonID = pclCM->CR[id]->GetSummonID() ;
	if ( pclCM->IsValidID(siSummonID) == false ) return ;
	SI32 siSummonIndex = pclCM->CR[siSummonID]->GetSummonIndex() ;
	if ( siMySummonIndex != siSummonIndex ) return ; // �ȷ��� ���� �´°�?
	cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if ( pclSummon == NULL ) return ; // ��ȯ�� ������ �־�� �Ѵ�.
	if ( pclSummon->siStatus != SUMMON_STATUS_TAKEOUT ) return ; // �����־�� �Ѵ�
	if ( pclSummon->clIP.GetLife() <= 0 ) return ; // �׾����� �ȵȴ�.
	if ( pclSummon->siKind <= 0 || pclSummon->siKind >= MAX_KINDINFO_NUMBER) return;
	if ( pclKindInfoSet->pclKI[pclSummon->siKind]->bSummonMall == TRUE ) return ; // ��ȯ������ �� ���.

	SI32 siSummonUnitRank = pclKindInfoSet->pclKI[pclSummon->siKind]->siSummonRank;

	SI32 siUseTicketNumber = 0;
	if(siSummonUnitRank < 9)	// ��ȭ�̿�� 1�徲�� ��ȯ����
	{
		siUseTicketNumber = siSummonUnitRank - 1;
	}
	else if(siSummonUnitRank < 17)	// ��ȭ�̿�� 2�徲�� ��ȯ����
	{
		siUseTicketNumber = (2 * (siSummonUnitRank - 8)) + 7;
	}
	else if(siSummonUnitRank < 25)	// ��ȭ�̿�� 3�徲�� ��ȯ����
	{
		siUseTicketNumber = (3 * (siSummonUnitRank - 16)) + 23;
	}
	else if(siSummonUnitRank < 40)	// ��ȭ�̿�� 4�徲�� ��ȯ����
	{
		siUseTicketNumber = (4 * (siSummonUnitRank - 24)) + 47;
	}
	else if(siSummonUnitRank >= 40)	// ��ȭ�̿�� 5�徲�� ��ȯ����
	{
		siUseTicketNumber = (5 * (siSummonUnitRank - 39)) + 107;
	}
	else return ;

	CMinisterIzo* pclMinister = (CMinisterIzo*)pclMinisterMgr->GetMinister( MINISTER_IZO );
	if ( pclMinister == NULL ) return;

	SI64 siTicketPrice =  pclItemManager->clItemStatistic.siNPCPriceRate * 10000;
	SI64 siSelectSummonPrice = siUseTicketNumber * siTicketPrice * pclMinister->m_siPriceValue / 100 ;

	cltGameMsgResponse_TradeMerchantBuySummonInfo clGameMsgResponse_TradeMerchantBuySummonInfo( pclinfo->siSummonID, siSelectSummonPrice );
	cltMsg clMsg( GAMEMSG_RESPONSE_TRADEMERCHANTBUYSUMMONINFO,  sizeof( clGameMsgResponse_TradeMerchantBuySummonInfo ), (BYTE*)&clGameMsgResponse_TradeMerchantBuySummonInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONTRADE(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuySummon * pclinfo = (cltGameMsgRequest_TradeMerchantBuySummon*)pclMsg->cData;

	
	// ��ȯ�� ���� Ȯ��
	if ( ! pclCM->CR[id]->pclCI->clSummonInfo.HaveSummon() )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	// ��ȯ�� �Ǹ����̶�� ����
	if(pclchar->bIsTradeing == true)
		return;

	SI32 siMySummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	// ��ȯ���� ��ȯ�Ǿ� �ִ��� Ȯ��
	SI32 siSummonID = pclCM->CR[id]->GetSummonID() ;
	if ( pclCM->IsValidID(siSummonID) == false ) return ;
	SI32 siSummonIndex = pclCM->CR[siSummonID]->GetSummonIndex() ;
	if ( siMySummonIndex != siSummonIndex ) return ; // �ȷ��� ���� �´°�?
	cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if ( pclSummon == NULL ) return ; // ��ȯ�� ������ �־�� �Ѵ�.
	if ( pclSummon->siStatus != SUMMON_STATUS_TAKEOUT ) return ; // �����־�� �Ѵ�
	if ( pclSummon->clIP.GetLife() <= 0 ) return ; // �׾����� �ȵȴ�.
	if ( pclSummon->siKind <= 0 || pclSummon->siKind >= MAX_KINDINFO_NUMBER) return;
	if ( pclKindInfoSet->pclKI[pclSummon->siKind]->bSummonMall == TRUE ) return ; // ��ȯ������ �� ���.

	SI32 siSummonUnitRank = pclKindInfoSet->pclKI[pclSummon->siKind]->siSummonRank;

	SI32 siUseTicketNumber = 0;
	if(siSummonUnitRank < 9)	// ��ȭ�̿�� 1�徲�� ��ȯ����
	{
		siUseTicketNumber = siSummonUnitRank - 1;
	}
	else if(siSummonUnitRank < 17)	// ��ȭ�̿�� 2�徲�� ��ȯ����
	{
		siUseTicketNumber = (2 * (siSummonUnitRank - 8)) + 7;
	}
	else if(siSummonUnitRank < 25)	// ��ȭ�̿�� 3�徲�� ��ȯ����
	{
		siUseTicketNumber = (3 * (siSummonUnitRank - 16)) + 23;
	}
	else if(siSummonUnitRank < 40)	// ��ȭ�̿�� 4�徲�� ��ȯ����
	{
		siUseTicketNumber = (4 * (siSummonUnitRank - 24)) + 47;
	}
	else if(siSummonUnitRank >= 40)	// ��ȭ�̿�� 5�徲�� ��ȯ����
	{
		siUseTicketNumber = (5 * (siSummonUnitRank - 39)) + 107;
	}
	else return ;

	CMinisterIzo* pclMinister = (CMinisterIzo*)pclMinisterMgr->GetMinister( MINISTER_IZO );
	if ( pclMinister == NULL ) return;

	SI64 siTicketPrice =  pclItemManager->clItemStatistic.siNPCPriceRate * 10000;
	SI64 siSelectSummonPrice = siUseTicketNumber * siTicketPrice * pclMinister->m_siPriceValue / 100 ;

	cltSummon clSummon;
	clSummon.Set(pclSummon);

	pclchar->bIsTradeing = true;

	sDBRequest_SummonTrade clMsg(id,PersonID,&clSummon,siSelectSummonPrice) ;
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SELECT_SUMMONCHAR(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsAlive( id ) == FALSE )
	{
		return;
	}

	SI32 mapindex = pclCM->CR[id]->GetMapIndex() ;

	if ( pclMapManager->IsInstanceMap(mapindex) == false )
	{
		return ;
	}

	cltGameMsgRequest_Select_SummonChar* pclinfo = (cltGameMsgRequest_Select_SummonChar*)pclMsg->cData;

	pclCM->CR[id]->siSelectedCharIndex = pclinfo->siSelectIndex ;

	SI32 summonid = pclCM->CR[id]->GetSummonID() ;

	if ( pclCM->IsAlive(summonid) == false && pclCM->CR[id]->siSelectedCharIndex != -1 )
	{
		pclCM->CR[id]->siSelectedCharIndex = -1 ;
	}
	else if ( pclCM->IsAlive(summonid) && pclCM->CR[summonid]->GetSummonIndex() != pclCM->CR[id]->siSelectedCharIndex )
	{
		pclCM->CR[id]->siSelectedCharIndex = -1 ;
	}

	cltGameMsgResponse_Select_SummonChar clinfo(pclCM->CR[id]->siSelectedCharIndex);
	cltMsg clMsg( GAMEMSG_RESPONSE_SELECT_SUMMONCHAR,  sizeof( clinfo ), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMON_SPTCHARGE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Summon_ChargeStamina* pclinfo = (cltGameMsgRequest_Summon_ChargeStamina*)pclMsg->cData;

	if(pclCM->IsValidID(id)  == false)	return;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar==NULL)							return;

	cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclinfo->siSummonID);
	if(pclSummon==NULL)							return;

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclinfo->siSummonID);

	//--------------------------------
	// ��ȯ���� kind�� �����Ѵ�.
	//--------------------------------
	SI32 kind = pclSummon->siKind;
	if( pclKindInfoSet->IsValidKind(kind)  == FALSE)	return;

	// ��ȯ���� �׾� ������ ����
	if(pclSummon->siStatus == SUMMON_STATUS_DEAD) return;
	
	// ��ȯ���� ���¹̳ʰ� 0�� �ƴϸ� ����
	if(pclSummon->clIP.GetLuk() > 0)			return;

	// ������������ �κ��� ������ ����
	SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(ITEMUNIQUE(13625));
	if(itempos < 0)	return;

	cltSummon clSummon;
	clSummon.Set(pclSummon);

	SI32 summonskill = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[0], id );
	clSummon.clIP.SetLuk( pclClient->GetMaxStaminaValue(summonskill, kind));

	// ���� �������� ����Ѵ�.
	cltItem	clItem;
	clItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[itempos]);
	clItem.SetItemNum(1);

	sDBRequest_UseItem clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), itempos, &clItem, USEITEM_REASON_NONE);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclchar->SendDBSummon(SETSUMMON_REASON_CHARGESTAMINA, siSummonIndex, &clSummon);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMON_TRANSFORM(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( NULL == pclchar ) return;

	//cltGameMsgRequest_Summon_Transform* pclinfo = (cltGameMsgRequest_Summon_Transform*)pclMsg->cData;

	pclchar->TransformSummon( pclCM, m_pclSummonTransformManager );
}