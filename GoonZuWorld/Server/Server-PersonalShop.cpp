//---------------------------------
// 2003/9/18 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "../../Lib/HashTable/HashTable_StringInt.h"
#include "Msg/MsgType-PersonalShop.h"
#include "MsgType-Item.h"
#include "MsgRval-Define.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-PersonalShop.h"
#include "../Server/Minister/MinisterMgr.h"
#include "../Server/Minister/Minister-Hozo.h"
#include "../Client/ninterface/npersonalshopdlg/NPersonalShopDlg.h"
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONALSHOPBANNER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PersonalShopBanner* pclinfo = (cltGameMsgRequest_PersonalShopBanner*)pclMsg->cData;

	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)return ;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	if(pclchar->bPersonalShopSwitch == false)	return ;

	// �Ӹ��� �����͸� ������. 
	cltGameMsgResponse_PersonalShopBanner clinfo(pclinfo->siCharUnique, pclchar->bPersonalShopSwitch, &pclchar->clShopBanner);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONALSHOPBANNER, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���λ���  ������ ��û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONALSHOPDATA(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PersonalShopData* pclinfo = (cltGameMsgRequest_PersonalShopData*)pclMsg->cData;

	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)return ;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	// ���� �ʱ�ȭ�ϰ� �����Ѵ�.
	if(pclchar->bPersonalShopSwitch == false)
	{
		pclchar->clShopData.Init();

		if(pclinfo->bManufacture == FALSE)
		{
			pclchar->clShopData.m_siShopMode = PSHOP_MODE_SELL;
		}
		else
		{
			if(pclinfo->bMaker == TRUE )
			{
				pclchar->clShopData.m_siShopMode = PSHOP_MODE_MAKEITEM_WANT ;
			}
			else
			{
				pclchar->clShopData.m_siShopMode = PSHOP_MODE_MAKEITEM;
			}
		}

		pclchar->clShopData.m_siPersonID = pclchar->pclCI->GetPersonID();
		StringCchCopy(pclchar->clShopData.m_szAccountID, MAX_PLAYER_NAME, pclchar->pclCI->clBI.szAccountID);
	}
	else if(true == pclchar->bPersonalShopSwitch)
	{
		/*if(pclinfo->bManufacture == TRUE)  
		{
			if(pclchar->clShopData.m_siShopMode == PSHOP_MODE_SELL)
			{
				SendServerResponseMsg( 0, SRVAL_PERSONAL_SHOP_MODE_CHANGE_FAIL, 0, 0, chatid );
				return;
			}
		}
		else
		{
			if(pclchar->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM)
			{
				SendServerResponseMsg( 0, SRVAL_PERSONAL_SHOP_MODE_CHANGE_FAIL, 0, 0, chatid );
				return;
			}
		}*/
	}

	// ���� �ü� ������ �����Ѵ�.
	pclchar->clShopData.SetCurrentPrice(pclItemManager);

	// ���λ��� 
	cltGameMsgResponse_PersonalShopData clinfo(pclinfo->siCharUnique, &pclchar->clShopData);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}



void cltServer::DoMsg_GAMEMSG_REQUEST_STARTPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	//[����] �к� �����̾�. => 2008-3-25
	if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
	{
		StartPersonalSpecialShop(pclMsg, id);
		return;
	}

	cltGameMsgRequest_StartPersonalShop* pclinfo = (cltGameMsgRequest_StartPersonalShop*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}
		
	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)
	{
		return ;

	}

	// �̹� �����ϰ� �ִٸ� �����ϰ� �ٽ� �����ؾ��Ѵ�.
	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	if ( pclchar == NULL )
	{
		return;
	}

	// ���� �����߿��� �Ұ����ϴ�
	if ( true == pclchar->bIsElectionStump )
	{
		return;
	}

	// [����] ������ �� �� ���� �����̶�� ����
	SI32 siMapIndex = pclchar->GetMapIndex();

	if ( (pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM) &&  (pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT) && (pclMapManager->IsCanMarketOpenMap(siMapIndex) == false) )
	{
		return;
	}

	SI32 siSuccess		= 1;
	SI32 siTicketPos    = 0;
	SI32 siTicketUnique = (pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM || pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT ) ? ITEMUNIQUE(24065) : ITEMUNIQUE(24010);	// ���λ��� �̿��
	SI32 siTicketNum	= 1;

	if(pclinfo->clShopData.m_bPremium == true)
	{
		siTicketUnique = ITEMUNIQUE(24075);
	}

	if(bForcePersonalShopSwitch==false)	  	      {	siSuccess = -2;	} // ���λ��� ���� ���� 
	else if(pclchar->bPersonalShopSwitch == true) {	siSuccess = 0;	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		if(siTicketNum <= 0)		return;

		///////////////////////////////////////////////////////
		// �̿�� Ȯ�� 
		siTicketPos = pclCM->CR[chatid]->pclCI->clCharItem.GetItemPos(siTicketUnique);
		if( siTicketPos < PERSONITEM_INV0 || siTicketPos >= MAX_ITEM_PER_PERSON )								siSuccess = -1;
		if(siSuccess > 0 && pclCM->CR[chatid]->pclCI->clCharItem.clItem[siTicketPos].siItemNum < siTicketNum)	siSuccess = -1;
		//////////////////////////////////////////////////////////////////////////
	}

	// �̿���� �ִµ� �÷��� ItemList�� �ŷ� ��������̸� siSuccess = -3;
	if(siSuccess > 0 && pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM && pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT)
	{
		for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i )
		{
			if(pclinfo->clShopData.m_clItem[i].siUnique)
			{
				SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clShopData.m_clItem[i].siUnique);
				if(ref > 0)	
				{
					// �ŷ����ɹ�ǰ���� �˻��Ѵ�.
					if( pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) ||
						//cyj �ͼӾ������� ����
						pclinfo->clShopData.m_clItem[i].IsBelonging(pclItemManager) ||
						pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(8150)||
						pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14300) ||
						pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14400)||
						pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14500)) // �ݰ��Ǳ�� ��
					{
						siSuccess = -3;
					}

					if(pclClient->IsCountrySwitch(Switch_FourLeaf))
					{
						//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
						if( ITEMUNIQUE(2755) == pclinfo->clShopData.m_clItem[i].siUnique || 
							ITEMUNIQUE(2754) == pclinfo->clShopData.m_clItem[i].siUnique	)	
						{	
							if( pclinfo->clShopData.m_clItem[i].siUnique != siFourLeafUnique )	
							{
								siSuccess = -3;
							}
						}
					}
				}
			}

			// ��ƼȦ���� ���� �������̸� �ŷ��� �Ұ��� �ϴ�.
			if( pclinfo->clShopData.m_clItem[i].clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
				siSuccess = -3;
		}
	}

	// �������� �ִ� ������ ���� ���Ѵ�.
	if(siSuccess > 0 )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclchar->GetMapIndex()) == true )
		{
			CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
			SI32 siShopNum = pclMapManager->pclVillageManager->GetPersonalShopNumber(pclchar->GetMapIndex());
			if(pclminister  && siShopNum >= pclminister->GetMaxShopNum() )
			{
				siSuccess = -4;
			}
		}
	}

	if(siSuccess > 0)
	{
		// �̿���� ����� ������ Unique�� �ش�.
		SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();

		cltItem clTicketItem;
		SI16 brareswitch = 0;
		pclClient->pclItemManager->MakeRandItemUnique( siTicketUnique, &clTicketItem, 0, 0, &brareswitch, 0,0,0,0,0,0);
		clTicketItem.SetItemNum(siTicketNum);

		// DB�� ��û�Ѵ�. 
		sDBRequest_StartPersonalShop clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, siTicketPos, siTicketUnique, siTicketNum, &pclinfo->clShopData, &clTicketItem);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		// ��ǰ ��� ��踦 ����.(���λ��� �̿��)
		pclItemManager->AddUseNum(siTicketUnique, siTicketNum);

		//���ο� ��� - ��ǰ ��� ��踦 ����.
		//NStatistics_Add("Item", siTicketUnique, "UseNum", siTicketNum);


		//==========================================================
		// �̸� ��ʴ� ����� ��ġ �� 
		pclchar->SetPersonalShopBanner(&pclinfo->clShopData);
		pclchar->SetPersonalShopData(false, &pclinfo->clShopData);
		//==========================================================
		// Ȥ�ó� �ؼ��� �ٽ� �ѹ� 
		pclchar->clShopData.m_siPersonID = pclchar->pclCI->GetPersonID();
		StringCchCopy(pclchar->clShopData.m_szAccountID, MAX_PLAYER_NAME, pclchar->pclCI->clBI.szAccountID);
		//==========================================================

		// �����Ƿ� ����Ʈ
		if ( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM )
		{
			pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_MAKEREQUESTSTART);
		}
	}
	else
	{
		// ���� ������ �����Ѵ�.
		// ���� ������ �����Ƿ����� ���� ��� �����Ѱ��� ���� �ϱ� ���ؼ� ��带 �־��ش� .
		cltGameMsgResponse_StartPersonalShop clinfo(pclchar->GetCharUnique(), siSuccess,false, pclinfo->clShopData.m_siShopMode );
		cltMsg clMsg(GAMEMSG_RESPONSE_STARTPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [�α��߰� : Ȳ���� 2007. 9. 3] // ���λ��� ���� ����. 
		//	// param1 == ���λ����� ���п���, param2 == �����̾� ����.
		//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_START, 
		//		0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		//		siSuccess, false, 0, 0, 0, NULL, NULL);
		//}
	}
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOPPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StopPersonalShop* pclinfo = (cltGameMsgRequest_StopPersonalShop*)pclMsg->cData;

	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)return ;

	// �̹� �����ϰ� �ִٸ� �����ϰ� �ٽ� �����ؾ��Ѵ�.
	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	if(pclchar->bPersonalShopSwitch == false)	return ;
	
	// ĳ������ ���λ����� �����Ѵ�. 
	pclchar->SetPersonalShopBanner(NULL); 
	pclchar->SetPersonalShopData(false, NULL);
	pclchar->clShopData.m_siShopMode = PSHOP_MODE_NONE;

	//[����] �к� �����̾� ���� �������� �����߾����� �ʱ�ȭ. => 2008-6-18
	if( pclchar->clShopData.m_siSelectedSpacialInventoryPos > 0 )
	{
		if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
		{
			pclchar->clShopData.m_siSelectedSpacialInventoryPos = 0;
			pclchar->clShopData.m_clSpacialItem.siUnique        = 0;
		}
	}
	
	// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
	cltGameMsgResponse_StopPersonalShop clinfo(pclchar->GetCharUnique(), pclchar->pclCI->GetPersonID(), 1);
	cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNeighbourMsg(&clMsg, true);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2008. 10. 9] // ���λ��� ���� ����.
	//	// param1 == ���.
	//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_END, 
	//						0, (cltCharServer*)pclchar, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	//						1, 0, 0, 0, 0, NULL, NULL);
	//}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BUYPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_BuyPersonalShop* pclinfo = (cltGameMsgRequest_BuyPersonalShop*)pclMsg->cData;
	
	SI32 Shopperid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(Shopperid) == false)return ;
	if(pclCM->IsValidID(id)		   == false)return ;
		
	// ��ǰ�� ��⸦ ���ϴ� ������������ �˻��Ѵ�.
	cltCharServer* pclcharshopper = (cltCharServer* )pclCM->CR[Shopperid];
	cltCharServer* pclcharbuyer   = (cltCharServer* )pclCM->CR[id];
	if ( pclcharshopper == NULL || pclcharbuyer == NULL )	return;

	cltShopTradeData	*pShoperShopData = &pclcharshopper->clShopData;

	SI32 siSuccess = 1;
	//---------------------------------------------
	// ���� ������ ���� �� ������ ���ΰ� ������ ���¸� ���Ѵ�.
	//---------------------------------------------
	if(siSuccess > 0)
	{
		if(pclcharshopper->bPersonalShopSwitch == false)					siSuccess = -1;// ������ �����ϰ� ���� �ʴ�.
		if(pclcharshopper->clShopData.m_siShopMode != pclinfo->siShopMode)	siSuccess = -1;// ������ ��尡 ���� �ٸ���.
		if(pclcharshopper->clShopData.m_siShopMode != PSHOP_MODE_SELL)		siSuccess = -1;// ������ ��尡 SELL�� �ƴϴ�.
		if(pclcharshopper->pclCI->GetPersonID()!= pclinfo->siPersonID)		siSuccess = -1;// PERSON ID �� �ٸ���.
	}

	//---------------------------------------------
	// ���� ������ϴ� ������ �����Ѵ�.
	//---------------------------------------------
	SI32 siShowcaseIndex = 0;
	if(siSuccess > 0)
	{
		if(pclinfo->clItem.siUnique<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum>MAX_ITEM_PILE_NUMBER)					siSuccess = -2;	
		if(pclinfo->siPrice < 1 )											siSuccess = -2;	
		if(pclinfo->siPrice > MAX_PRICE_IN_MARKET )							siSuccess = -2;	

		// showcase index�� Ʋ�ȴ�.
		siShowcaseIndex = pclinfo->siShowcaseIndex;
		if(siShowcaseIndex< 0 || siShowcaseIndex>= MAX_SHOP_ITEM_NUMBER)	siSuccess = -2; 
	}
	//---------------------------------------------
	// ���� ������ϴ� ������ ���������� ShowCase ������ ���Ѵ�.
	//---------------------------------------------
	SI32 siShopperInventoryPos = 0;
	SI32 siShowcaseItemNum = 0;
	if(siSuccess > 0)
	{
		// �������� ��ġ���� ����.
		if(pclinfo->clItem.IsSame( &pShoperShopData->m_clItem[siShowcaseIndex], false )==FALSE )siSuccess = -3;
		// ������ ������ ��ġ���� ���� 
		if(pclinfo->siPrice != pShoperShopData->m_siPrice[siShowcaseIndex])	siSuccess = -3;
		// ���������� ������ �Ҷ� 
		if(pShoperShopData->m_siPrice[siShowcaseIndex] < 1)					siSuccess = -3;
		// ������ �Ǹ� ������ �������Ҷ� 
		siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)											siSuccess = -3;

		// inventory index�� Ʋ�ȴ�.
		siShopperInventoryPos = pShoperShopData->m_siSelectedInventoryPos[siShowcaseIndex];
		if(siShopperInventoryPos <PERSONITEM_INV0 || siShopperInventoryPos>= MAX_ITEM_PER_PERSON)	siSuccess = -3;
	}

	//---------------------------------------------
	// ���� ������ϴ� ������ ���������� Inventory ������ ���Ѵ�.
	//---------------------------------------------
	SI32 siRealBuyItemNum = 0;
	SI32 siInvenItemNum= 0;
	if(siSuccess > 0)
	{
		// �κ��丮 �������� ��ġ���� ����.
		if(pclinfo->clItem.IsSame( &pclcharshopper->pclCI->clCharItem.clItem[siShopperInventoryPos], false )==FALSE )siSuccess = -4;
		
		// ������ �����Ҽ� �ִ� ������ ���Ѵ�.
		// ���� �䱸 ����  > ������ ����  > �κ��丮 ���� => ���� ���� ������ ������ �ȴ�.
		siRealBuyItemNum = pclinfo->clItem.siItemNum;
		SI32 siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)						siSuccess = -4;
		siInvenItemNum= pclcharshopper->pclCI->clCharItem.clItem[siShopperInventoryPos].siItemNum;
		if(siInvenItemNum < 1)							siSuccess = -4;

		// ���� ���� ������ �����Ѵ�.
		if(siRealBuyItemNum > siShowcaseItemNum)siRealBuyItemNum = siShowcaseItemNum;
		if(siRealBuyItemNum > siInvenItemNum )	siRealBuyItemNum = siInvenItemNum;
		if(siRealBuyItemNum <1)							siSuccess = -4;
	}
	//---------------------------------------------
	// �����ڰ� ���� ������ �ּ� ���� �ִ��� Ȯ��
	//---------------------------------------------
	SI64 siTotalPrice = 0; 
	if(siSuccess > 0)
	{
		SI64 TotalBuyerMoney = (SI64)pclCM->CR[id]->pclCI->clIP.GetMoney();
		siTotalPrice         = (SI64)pclinfo->siPrice * (SI64)siRealBuyItemNum ;
		if( siTotalPrice < 1)
		{
			siSuccess = -5;
		}
		else if ( siTotalPrice > TotalBuyerMoney )	
		{
			siSuccess = -5;
		}
		
	}
	
	
	//---------------------------------------------
	// �����ڰ� �������� Ȯ���� ������ �ִ��� Ȯ��
	//---------------------------------------------
	cltItem clBuyItem;
	SI16	siBuyerInventoryPos = -1;
	if(siSuccess > 0)
	{
		clBuyItem.Init();
		clBuyItem.Set( &pclcharshopper->pclCI->clCharItem.clItem[siShopperInventoryPos] );
		clBuyItem.siItemNum = siRealBuyItemNum;
		cltItem clToItem;
		clToItem.Init();

		SI32 rtnvalue;
		// �������� �κ��� ���� �� �ִ��� Ȯ���Ѵ�.
		if ( pclcharbuyer->CanAddInv(INVMODE_ALL, &clBuyItem, &siBuyerInventoryPos, &clToItem, &rtnvalue)==false )
		{
			siSuccess = -6;
		}
	}
	//---------------------------------------------------------------
	// Shopper�� ��ǰ -> Buyer�� BuyerInvPos, Buyer�� �� -> Shopper
	//---------------------------------------------------------------
	// DB Message�� ������.
	if(siSuccess > 0)
	{
		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->ItemUseReserveAction();
		pclcharbuyer->ItemUseReserveAction();
		//---------------------------------------------

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->BulletUseReserveAction();
		pclcharbuyer->BulletUseReserveAction();


		// �ٸ������ ������ ���� ���ϵ����ϴ� ���д�.
		pclcharshopper->clShopData.m_clItem[siShowcaseIndex].siItemNum -= clBuyItem.siItemNum;

		sDBRequest_PersonalShopBuyItem	clMsg(	id,		   pclcharbuyer->pclCI->GetPersonID(), 
												Shopperid, pclcharshopper->pclCI->GetPersonID(),
												siBuyerInventoryPos, siShopperInventoryPos,  
												siShowcaseIndex,  siTotalPrice,
												&clBuyItem, clBuyItem.CanPile(pclItemManager));
	
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else		
	{
		SI32 siFailReason = 0;
		switch(siSuccess)
		{
		case -1: siFailReason = BUYPERSONALSHOP_FAIL_SHOPPERSTATUS; break;// ���Ž��� 
		case -2: siFailReason = BUYPERSONALSHOP_FAIL_BUYERSTATUS;	break;// ���Ž��� 
		case -3: siFailReason = BUYPERSONALSHOP_FAIL_SHOWCASESTATUS;break;// ���Ž��� 
		case -4: siFailReason = BUYPERSONALSHOP_FAIL_BUY_NOITEM;	break;// ���Ž��� 
		case -5: siFailReason = BUYPERSONALSHOP_FAIL_BUY_NOMONEY;   break;// ���Ž��� 
		case -6: siFailReason = BUYPERSONALSHOP_FAIL_BUY_NOINVSPACE;break;// ���Ž��� 
		default: siFailReason = BUYPERSONALSHOP_FAIL_UNKNOWN; break;// ���Ž��� 
		}
		// Client���� siSuccess ���������� �����Ѵ�.
		cltGameMsgResponse_BuyPersonalShop clInfo(id, siFailReason, pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum);
		cltMsg clMsg(GAMEMSG_RESPONSE_BUYPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SELLPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SellPersonalShop* pclinfo = (cltGameMsgRequest_SellPersonalShop*)pclMsg->cData;

	SI32 Shopperid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(Shopperid) == false)return ;
	if(pclCM->IsValidID(id)		   == false)return ;
		
	// ��ǰ�� ��⸦ ���ϴ� ������������ �˻��Ѵ�.
	cltCharServer* pclcharshopper = (cltCharServer* )pclCM->CR[Shopperid];
	cltCharServer* pclcharseller  = (cltCharServer* )pclCM->CR[id];
	if ( pclcharshopper == NULL || pclcharseller == NULL )	return;

	cltShopTradeData	*pShoperShopData = &pclcharshopper->clShopData;

	SI32 siSuccess = 1;
	//---------------------------------------------
	// ���� ������ �ȱ���� ������ ���ΰ� ������ ���¸� ���Ѵ�.
	//---------------------------------------------
	if(siSuccess > 0)
	{
		if(pclcharshopper->bPersonalShopSwitch == false)					siSuccess = -1;// ������ �����ϰ� ���� �ʴ�.
		if(pclcharshopper->clShopData.m_siShopMode != pclinfo->siShopMode)	siSuccess = -1;// ������ ��尡 ���� �ٸ���.
		if(pclcharshopper->clShopData.m_siShopMode != PSHOP_MODE_BUY)		siSuccess = -1;// ������ ��尡 BUY�� �ƴϴ�.
		if(pclcharshopper->pclCI->GetPersonID()!= pclinfo->siPersonID)		siSuccess = -1;// PERSON ID �� �ٸ���.
	}

	//---------------------------------------------
	// ���� �Ȱ��� �ϴ� ������ �����Ѵ�.
	//---------------------------------------------
	SI32 siShowcaseIndex = 0;
	if(siSuccess > 0)
	{
		if(pclinfo->clItem.siUnique <1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum < 1)									siSuccess = -2;	
		if(pclinfo->clItem.siItemNum > MAX_ITEM_PILE_NUMBER)				siSuccess = -2;	
		if(pclinfo->siPrice < 1 )											siSuccess = -2;	
		if(pclinfo->siPrice > MAX_PRICE_IN_MARKET )							siSuccess = -2;	

		// showcase index�� Ʋ�ȴ�.
		siShowcaseIndex = pclinfo->siShowcaseIndex;
		if(siShowcaseIndex< 0 || siShowcaseIndex>= MAX_SHOP_ITEM_NUMBER)	siSuccess = -2; 

		// ���� inventory index�� Ʋ�ȴ�.
		if(pclinfo->siSellerInventoryRealIndex<PERSONITEM_INV0 || pclinfo->siSellerInventoryRealIndex>= MAX_ITEM_PER_PERSON)	siSuccess = -2;
	}
	//---------------------------------------------
	// ���� �Ȱ����ϴ� ������ ���������� ShowCase ������ �޶������� �˻��Ѵ�.
	//---------------------------------------------
	SI32 siSellerInventoryPos = pclinfo->siSellerInventoryRealIndex;
	SI32 siShowcaseItemNum = 0;
	if(siSuccess > 0)
	{
		// �������� ��ġ���� ����.
		if(pclinfo->clItem.siUnique != pShoperShopData->m_clItem[siShowcaseIndex].siUnique)	siSuccess = -3;
		// ������ ������ ��ġ���� ���� 
		if(pclinfo->siPrice != pShoperShopData->m_siPrice[siShowcaseIndex])	siSuccess = -3;
		// ���������� ������ �Ҷ� 
		if(pShoperShopData->m_siPrice[siShowcaseIndex] < 1)					siSuccess = -3;
		// ������ �Ǹ� ������ �������Ҷ� 
		siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)											siSuccess = -3;

		SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clItem.siUnique);
		if(ref > 0)	
		{
			// �ŷ����ɹ�ǰ���� �˻��Ѵ�.
			if( pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) ||
				//cyj �ͼӾ������� ����
				pclinfo->clItem.IsBelonging(pclItemManager) )
			{
				siSuccess = -3;
			}
		}


		// ������ ������ �� �κ��丮 �����۰� �ٸ��� 
		if(pShoperShopData->m_clItem[siShowcaseIndex].siUnique < 1)			siSuccess = -3;

		// �κ��丮 Unique�� ������ showcase�� Unique�� �ٸ� �� 
		if(pclcharseller->pclCI->clCharItem.clItem[siSellerInventoryPos].siUnique !=
			pShoperShopData->m_clItem[siShowcaseIndex].siUnique)			siSuccess = -3;
			
	}
	//---------------------------------------------
	// ���� �Ǹ��ϰ����ϴ� ������ ���������� Showcase ������ ���� �ǸŰ������� �˻��Ѵ�.
	//---------------------------------------------
	SI32 siRealSellItemNum = 0;
	SI32 siInvenItemNum= 0;
	if(siSuccess > 0)
	{
		// ������ �Ǹ� �� �� �ִ� ������ ���Ѵ�.
		// �Ǹ� �䱸 ����  > ������ ���� > ������ ���� �ִ� �� ==> ���� ���� ������ ������ �ȴ�.
		siRealSellItemNum = pclinfo->clItem.siItemNum;
		SI32 siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)						siSuccess = -4;
		siInvenItemNum= pclcharseller->pclCI->clCharItem.clItem[siSellerInventoryPos].siItemNum;
		if(siInvenItemNum < 1)							siSuccess = -4;

		// ���� ���� ������ �����Ѵ�.
		if(siRealSellItemNum > siShowcaseItemNum)	siRealSellItemNum = siShowcaseItemNum;
		if(siRealSellItemNum > siInvenItemNum )		siRealSellItemNum = siInvenItemNum;
		if(siRealSellItemNum < 1 )					siSuccess = -4;
	}

	//---------------------------------------------
	// (��������) �����ڰ� ���� ������ �ּ� ���� �ִ��� Ȯ��
	//---------------------------------------------
	SI64 siTotalPrice = 0; 
	if(siSuccess > 0)
	{
		SI64 TotalShopperMoney = (SI64)pclCM->CR[Shopperid]->pclCI->clIP.GetMoney();
		siTotalPrice           = (SI64)pclinfo->siPrice * (SI64)siRealSellItemNum ;
		// ���� ������ ���� �����ϸ� �ִ� ��ŭ�� �Ǹ��Ѵ�.
		if( siTotalPrice < 1)
		{
			siSuccess = -5;
		}
		else if ( siTotalPrice > TotalShopperMoney )
		{
			siRealSellItemNum = (TotalShopperMoney / pclinfo->siPrice);
		}
		// ���� �����ؼ� 1���� ���������� ������ ���� ���ϸ� 
		if(siRealSellItemNum < 1)	
		{
			siSuccess = -5;
		}
		else
		{
			siTotalPrice    = (SI64)pclinfo->siPrice * (SI64)siRealSellItemNum ;
			// ���� ������ ���� �����ϸ� ������ �ִ°��̴�.
			if(siTotalPrice <1)
			{
				siSuccess = -5;
			}
			else if ( siTotalPrice > TotalShopperMoney )
			{
				siSuccess = -5;
			}
		}
				
	}
	
	//---------------------------------------------
	// �����ڰ� �������� Ȯ���� ������ �ִ��� Ȯ��
	//---------------------------------------------
	cltItem clSellItem;
	SI16	siShopperInventoryPos = -1;
	if(siSuccess > 0)
	{
		clSellItem.Init();
		clSellItem.Set( &pclcharseller->pclCI->clCharItem.clItem[siSellerInventoryPos] );
		clSellItem.siItemNum = siRealSellItemNum;
		cltItem clToItem;
		clToItem.Init();

		SI32 rtnvalue;
		// ���������� �κ��� ���� �� �ִ��� Ȯ���Ѵ�. 
		if ( pclcharshopper->CanAddInv(INVMODE_ALL, &clSellItem, &siShopperInventoryPos, &clToItem, &rtnvalue)==false )
		{
			siSuccess = -6;
		}
	}
	//---------------------------------------------------------------
	// Seller�� SellerInvPos ��ǰ -> Shopper�� ShopperInvPos, Shooper�� �� -> Seller
	//---------------------------------------------------------------
	// DB Message�� ������.
	if(siSuccess > 0)
	{
		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->ItemUseReserveAction();
		pclcharseller->ItemUseReserveAction();
		//---------------------------------------------

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->BulletUseReserveAction();
		pclcharseller->BulletUseReserveAction();

		// �ٸ������ ������ ���� ���ϵ����ϴ� ���д�.
		pclcharshopper->clShopData.m_clItem[siShowcaseIndex].siItemNum -= clSellItem.siItemNum;

		sDBRequest_PersonalShopSellItem	clMsg(	id,		   pclcharseller->pclCI->GetPersonID(), 
												Shopperid, pclcharshopper->pclCI->GetPersonID(),
												siSellerInventoryPos, siShopperInventoryPos,  
												siShowcaseIndex,  siTotalPrice,
												&clSellItem, clSellItem.CanPile(pclItemManager));
	
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else		
	{
		SI32 siFailReason = 0;
		switch(siSuccess)
		{
		case -1: siFailReason = SELLPERSONALSHOP_FAIL_SHOPPERSTATUS;	break;	// ���Ž��� 
		case -2: siFailReason = SELLPERSONALSHOP_FAIL_SELLERSTATUS;		break;	// ���Ž��� 
		case -3: siFailReason = SELLPERSONALSHOP_FAIL_SHOWCASESTATUS;	break;	// ���Ž��� 
		case -4: siFailReason = SELLPERSONALSHOP_FAIL_SELL_NOITEM;		break;	// ���Ž��� 
		case -5: siFailReason = SELLPERSONALSHOP_FAIL_SELL_NOMONEY;		break;	// ���Ž��� 
		case -6: siFailReason = SELLPERSONALSHOP_FAIL_SELL_NOINVSPACE;	break;	// ���Ž��� 
		default: siFailReason = SELLPERSONALSHOP_FAIL_UNKNOWN;			break;	// ���Ž��� 
		}
		// Client���� siSuccess ���������� �����Ѵ�.
		cltGameMsgResponse_SellPersonalShop clInfo(id, siFailReason, pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum);
		cltMsg clMsg(GAMEMSG_RESPONSE_SELLPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		
		// ���� ���� ���и� �شٸ� ���� ��Ų��. 
		if(siFailReason == SELLPERSONALSHOP_FAIL_SELL_NOMONEY ||
		   siFailReason == SELLPERSONALSHOP_FAIL_SELL_NOINVSPACE)
		{
			// ĳ������ ���λ����� �����Ѵ�. 
			pclcharshopper->SetPersonalShopBanner(NULL);
			pclcharshopper->SetPersonalShopData(false, NULL);
			
			// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
			cltGameMsgResponse_StopPersonalShop clinfo(pclcharshopper->GetCharUnique(), pclcharshopper->pclCI->GetPersonID(), 3);
			cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
			pclcharshopper->SendNeighbourMsg(&clMsg, true);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����.
			//	// param1 == ���.
			//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_END, 
			//						0, (cltCharServer*)pclcharshopper, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			//						3, 0, 0, 0, 0, NULL, NULL);
			//}
		}
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SEARCHPERSONALSHOPITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SearchPersonalShopItem* pclinfo = (cltGameMsgRequest_SearchPersonalShopItem*)pclMsg->cData;

	if(pclCM->IsValidID(id)		   == false)return;
	if(pclinfo->siItemUniqueType <1)		return;

	cltSearchShopData	clSearchShopData;
	//-------------------------------------------
	// �˻� �⺻�����͸� �����Ѵ�.
	//-------------------------------------------
	clSearchShopData.m_siShopMode		 = pclinfo->siShopMode;
	clSearchShopData.m_siItemUniqueType  = pclinfo->siItemUniqueType;
	//-------------------------------------------
	// �˻� ������ �ٽ� ������.
	//-------------------------------------------
	clSearchShopData.m_siItemSearchPrice = pclinfo->siMaxPrice;
	
	//-------------------------------------------
	// ����ڸ� �˻��Ͽ� ������ ��´�.
	//-------------------------------------------
	SI32 siCount = 0;
	for ( SI32 i = 0; i < MAX_PERSON_NUMBER && siCount< MAX_SEARCHSHOP_ITEM_NUMBER; ++i )
	{
		if ( pclCM->IsValidID( i ) && IsPC(i))
		{
			cltCharServer* pclchar = (cltCharServer* )pclCM->CR[i];
			// ���� ������ ���� �����鼭 ���� ShopMode��� ��ǰ�� �˻��Ѵ�.
			if(pclchar && pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode == pclinfo->siShopMode)
			{
				for(SI32 j = 0; j < MAX_SHOP_ITEM_NUMBER && siCount< MAX_SEARCHSHOP_ITEM_NUMBER; ++j) 
				{
					// ���� Ÿ���� �������� ������ ���� ������ 
					SI32 siItemUnique = pclchar->clShopData.m_clItem[j].siUnique;
					if( siItemUnique == 0) continue;
					
					if( pclItemManager->GetItemType(siItemUnique) == pclinfo->siItemUniqueType &&
						pclchar->clShopData.m_clItem[j].siItemNum > 0)
						
					{
						if(pclinfo->siShopMode == PSHOP_MODE_BUY)
						{
							// ���� �˻� ������ �������  
							if( pclinfo->siMaxPrice> 0 && 
								pclchar->clShopData.m_siPrice[j] < pclinfo->siMaxPrice) continue;
						}
						else if(pclinfo->siShopMode == PSHOP_MODE_SELL)
						{
							// ������ �˻� ������ ������� 
							if( pclinfo->siMaxPrice> 0 && 
								pclchar->clShopData.m_siPrice[j] > pclinfo->siMaxPrice) continue;
						}
						// ������ �˻� ������ ������� 
						else if(pclinfo->siShopMode == PSHOP_MODE_MAKEITEM)
						{
							if( pclinfo->siMaxPrice> 0 && 
								pclchar->clShopData.m_siPrice[j] < pclinfo->siMaxPrice) continue;
						}
						
						if(siCount<MAX_SEARCHSHOP_ITEM_NUMBER)
						{
							// �������� 
							StringCchCopy(clSearchShopData.m_szName[siCount], MAX_PLAYER_NAME, (TCHAR *)pclchar->GetName());
							clSearchShopData.m_siLevel[siCount]		= pclchar->pclCI->clIP.GetLevel();
							// �������� 
							clSearchShopData.m_siMapIndex[siCount]	= pclchar->GetMapIndex();
							clSearchShopData.m_siMapX[siCount]		= pclchar->GetX();
							clSearchShopData.m_siMapY[siCount]		= pclchar->GetY();
							// ITEM ���� 
							clSearchShopData.m_clItem[siCount].Set(&pclchar->clShopData.m_clItem[j]);
							clSearchShopData.m_siPrice[siCount]		= pclchar->clShopData.m_siPrice[j];
							
							clSearchShopData.m_siHandPoint[siCount]	= pclchar->clShopData.m_siHandPoint;
							clSearchShopData.m_siSkillLevel[siCount]= pclchar->clShopData.m_siSkillLevel;
							
							siCount++;
						}
					}
				}
			}
		}
	}


	cltGameMsgResponse_SearchPersonalShopItem clinfo(TRUE, &clSearchShopData);
	cltMsg clMsg(GAMEMSG_RESPONSE_SEARCHPERSONALSHOPITEM, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MAKEPERSONALSHOP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_MakePersonalShop* pclinfo = (cltGameMsgRequest_MakePersonalShop*)pclMsg->cData;
	
	SI32 Shopperid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(Shopperid) == false)return ;
	if(pclCM->IsValidID(id)		   == false)return ;
		
	// ��ǰ�� �����Ƿ��� ������������ �˻��Ѵ�.
	cltCharServer* pclcharshopper = (cltCharServer* )pclCM->CR[Shopperid];
	cltCharServer* pclcharbuyer   = (cltCharServer* )pclCM->CR[id];
	if ( pclcharshopper == NULL || pclcharbuyer == NULL )	return;

	cltShopTradeData	*pShoperShopData = &pclcharshopper->clShopData;

	SI32 siSuccess = 1;
	//---------------------------------------------
	// ���� ������ �������ֱ���� �� ������ ���ΰ� ������ ���¸� ���Ѵ�.
	//---------------------------------------------
	if(siSuccess > 0)
	{
		if(pclcharshopper->bPersonalShopSwitch == false)					siSuccess = -1;// ������ �����ϰ� ���� �ʴ�.
		if(pclcharshopper->clShopData.m_siShopMode != pclinfo->siShopMode)	siSuccess = -1;// ������ ��尡 ���� �ٸ���.
		if(pclcharshopper->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM)	siSuccess = -1;// ������ ��尡 MAKEITEM�� �ƴϴ�.
		if(pclcharshopper->pclCI->GetPersonID()!= pclinfo->siPersonID)		siSuccess = -1;// PERSON ID �� �ٸ���.
	}

	//---------------------------------------------
	// ���� �����ϰ��� �ϴ� ������ �����Ѵ�.
	//---------------------------------------------
	SI32 siShowcaseIndex = 0;
	if(siSuccess > 0)
	{
		if(pclinfo->clItem.siUnique<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum>MAX_ITEM_PILE_NUMBER)					siSuccess = -2;	
		if(pclinfo->siPrice < 0 )											siSuccess = -2;	
		if(pclinfo->siPrice > MAX_PRICE_IN_MARKET )							siSuccess = -2;	
		if(pclinfo->siHandPoint <0)											siSuccess = -2;	
		if(pclinfo->siSkillLevel<0)											siSuccess = -2;	

		// showcase index�� Ʋ�ȴ�.
		siShowcaseIndex = pclinfo->siShowcaseIndex;
		if(siShowcaseIndex< 0 || siShowcaseIndex>= MAX_SHOP_MAKEITEM_NUMBER)siSuccess = -2; 
	}
	//---------------------------------------------
	// ���� �����ϰ��� �ϴ� ������ ���������� ShowCase ������ ���Ѵ�.
	//---------------------------------------------
	SI32 siShopperInventoryPos = 0;
	SI32 siShowcaseItemNum = 0;
	if(siSuccess > 0)
	{
		// �������� ��ġ���� ����.
		if(pclinfo->clItem.IsSame( &pShoperShopData->m_clItem[siShowcaseIndex], false )==FALSE )siSuccess = -3;
		// ������ �����ᰡ ��ġ���� ������� 
		if(pclinfo->siPrice != pShoperShopData->m_siPrice[siShowcaseIndex])	siSuccess = -3;
		// ���������� ������ �Ҷ� 
		if(pShoperShopData->m_siPrice[siShowcaseIndex] < 0)					siSuccess = -3;
		// ������ �Ǹ� ������ �������Ҷ� 
		siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)											siSuccess = -3;

		if(pclinfo->siHandPoint  != pShoperShopData->m_siHandPoint )		siSuccess = -3;
		if(pclinfo->siSkillLevel != pShoperShopData->m_siSkillLevel )		siSuccess = -3;
	}
	//---------------------------------------------
	// ���� ������ϴ� ������ ���������� Inventory ������ ���Ѵ�.
	//---------------------------------------------
	SI32 siRealBuyItemNum = 0;
	SI32 siInvenItemNum= 0;
	if(siSuccess > 0)
	{
		// ������ �����Ҽ� �ִ� ������ ���Ѵ�.
		// ���� �䱸 ����  > ������ ����  => ���� ���� ������ ������ �ȴ�.
		siRealBuyItemNum = pclinfo->clItem.siItemNum;
		SI32 siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)						siSuccess = -4;

		// ���� ���� ������ �����Ѵ�.
		if(siRealBuyItemNum > siShowcaseItemNum)siRealBuyItemNum = siShowcaseItemNum;
		if(siRealBuyItemNum <1)							siSuccess = -4;
	}

	//---------------------------------------------
	// ���������� �����ᰡ �ִ��� Ȯ�� 
	//---------------------------------------------
	SI64 siTotalPrice = 0; 
	if(siSuccess > 0)
	{
		SI64 TotalBuyerMoney = (SI64)pclcharshopper->pclCI->clIP.GetMoney();
		siTotalPrice         = (SI64)pclinfo->siPrice * (SI64)siRealBuyItemNum;
		if( siTotalPrice < 0)
		{
			siSuccess = -5;
		}
		else if ( siTotalPrice > TotalBuyerMoney )	
		{
			siSuccess = -5;
		}
	}
	
	
	//---------------------------------------------
	// �����ڰ� ���ϴ� �ɷ��� �����ϰ� �ִ��� Ȯ�� 
	//---------------------------------------------
	if(siSuccess > 0)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clItem.siUnique);
		if(ref <= 0)	return;
		
		// ������ �ʿ��� ����� Ȯ���Ѵ�. 
		SI32 skillunique = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
		if(skillunique <= 0)return ;

		// ��� ������ �����ϰų� �����ְ� �����ϸ�, 
		bool bConditionA = pclcharbuyer->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclcharbuyer->pclCI->clCharItem.clItem[0]) < pShoperShopData->m_siSkillLevel;
		bool bConditionB = false;
		if ( IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
		{
			bConditionB = pclcharbuyer->clPB.clTotalBA.GetLuk() < pShoperShopData->m_siHandPoint;
		}
		else
		{
			if ( IsCountrySwitch(Switch_Change_manufacture_request_interface) ) 
			{
				bConditionB = pclcharbuyer->clPB.clTotalBA.GetLuk() < pShoperShopData->m_siHandPoint;
				
			}
			else
			{
				bConditionB = pclcharbuyer->clPB.clTotalBA.GetHnd() < pShoperShopData->m_siHandPoint;
			}
			
		}

		if ( bConditionA || bConditionB )
		{
			siSuccess = -6;
		}
	}
	
	
	//---------------------------------------------------------------
	// Shopper�� ��ǰ -> Buyer�� BuyerInvPos, Buyer�� �� -> Shopper
	//---------------------------------------------------------------
	// DB Message�� ������.
	if(siSuccess > 0)
	{
		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->ItemUseReserveAction();
		pclcharbuyer->ItemUseReserveAction();
		//---------------------------------------------

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclcharshopper->BulletUseReserveAction();
		pclcharbuyer->BulletUseReserveAction();
	
		//---------------------------------------------------------------
		// DO SOMETHING �°� 
		//---------------------------------------------------------------

		cltGameMsgRequest_MakeItemInv clinfo(pclinfo->clItem.siUnique, 
			pclinfo->clItem.siItemNum, 
			pclinfo->siCharUnique,
			pclcharbuyer->GetCharUnique(),
			pclinfo->siShopMode,
			pclinfo->siType); // siTotalPrice


		pclCM->CR[id]->siPersonalMakeItemType = pclinfo->siType;

		cltGameMsgResponse_MakeItemSwitch clinfo2( pclinfo->siType );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();

		MakeItemProcess(id, &clinfo);

	}
	else		
	{
		SI32 siFailReason = 0;
		switch(siSuccess)
		{
		case -1: siFailReason = MAKEPERSONALSHOP_FAIL_SHOPPERSTATUS;  break;// ���۽��� 
		case -2: siFailReason = MAKEPERSONALSHOP_FAIL_MAKERSTATUS;	  break;// ���۽��� 
		case -3: siFailReason = MAKEPERSONALSHOP_FAIL_SHOWCASESTATUS; break;// ���۽��� 
		case -4: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NOITEM;	  break;// ���۽��� 
		case -5: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NOMONEY;   break;// ���۽��� 
		case -6: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NEEDABILITY;break;// ���۽��� 
		default: siFailReason = MAKEPERSONALSHOP_FAIL_UNKNOWN;		  break;// ���۽��� 
		}
		// Client���� siSuccess ���������� �����Ѵ�.
		cltGameMsgResponse_MakePersonalShop clInfo(id, siFailReason, pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum);
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


		pclCM->CR[id]->siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo2( 0 );
		cltMsg clMsg2(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
	}
		


}


void cltServer::StartPersonalSpecialShop(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StartPersonalShop* pclinfo = (cltGameMsgRequest_StartPersonalShop*)pclMsg->cData;

	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)return ;

	// �̹� �����ϰ� �ִٸ� �����ϰ� �ٽ� �����ؾ��Ѵ�.
	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	if ( pclchar == NULL )
	{
		return;
	}

	// ���� �����߿��� �Ұ����ϴ�
	if ( true == pclchar->bIsElectionStump )
	{
		return;
	}

	// �ǰ� 0, �׾��ٸ� �ŷ� �Ұ�.
	if ( false == pclCM->IsAlive(chatid))	return;
	

	// [����] ������ �� �� ���� �����̶�� ����
	SI32 siMapIndex = pclchar->GetMapIndex();

	if ( (pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM) && (pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT) &&  (pclMapManager->IsCanMarketOpenMap(siMapIndex) == false) )
	{
		return;
	}

	SI32 siSuccess		= 1;
	SI32 siTicketPos    = 0;
	SI32 siTicketUnique = (pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM
		||pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT) ? ITEMUNIQUE(24065) : ITEMUNIQUE(24010);	// ���λ��� �̿��
	SI32 siTicketNum	= 1;

	bool Special_Premiun = false;

	if(pclinfo->clShopData.m_bPremium == true)
	{
		if(pclClient->IsCountrySwitch(Switch_FourLeaf))
		{
			//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
			if( ITEMUNIQUE(2755) == pclinfo->clShopData.m_clItem[1].siUnique || 
				ITEMUNIQUE(2754) == pclinfo->clShopData.m_clItem[1].siUnique	)	
			{	
				if( pclinfo->clShopData.m_clItem[1].siUnique != siFourLeafUnique )	
				{
					siSuccess = -3;
				}
			}
		}

		// �к� �����̾��̸�.
		if( CNPersonalShopDlg::SPECIAL_PREMIUN_TICKET_UNIQUE == pclinfo->clShopData.m_clItem[0].siUnique )
		{
			Special_Premiun = true;

			//�ͼ����� Ƽ�� �������� ��´�.(���߿� ����ϱ� ���� �׸��� �̾������� �̿��� �ٸ� ���� ���ϰ� �Ϸ���.)
			pclinfo->clShopData.m_clSpacialItem.Set(&pclinfo->clShopData.m_clItem[0]);
			pclinfo->clShopData.m_siSelectedSpacialInventoryPos = pclinfo->clShopData.m_siSelectedInventoryPos[0];

			siTicketUnique = ITEMUNIQUE(CNPersonalShopDlg::SPECIAL_PREMIUN_TICKET_UNIQUE);
			cltItem TempItem; 
		    TempItem.Set( &pclinfo->clShopData.m_clItem[1] );
#ifdef _SAFE_MEMORY
			pclinfo->clShopData.m_clItem.ZeroMem();
#else
			ZeroMemory(pclinfo->clShopData.m_clItem, sizeof(pclinfo->clShopData.m_clItem));
#endif
			pclinfo->clShopData.m_clItem[0].Set( &TempItem );

			pclinfo->clShopData.m_siSelectedInventoryPos[0] = pclinfo->clShopData.m_siSelectedInventoryPos[1];
			pclinfo->clShopData.m_siPrice[0]				= pclinfo->clShopData.m_siPrice[1];
			pclinfo->clShopData.m_siCurrentPrice[0]			= pclinfo->clShopData.m_siCurrentPrice[1];
		}
		else
		{
			siTicketUnique = ITEMUNIQUE(24075);
		}
		
	}

	if(bForcePersonalShopSwitch==false)	  	      {	siSuccess = -2;	} // ���λ��� ���� ���� 
	else if(pclchar->bPersonalShopSwitch == true) {	siSuccess = 0;	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		if(siTicketNum <= 0)		return;

		///////////////////////////////////////////////////////
		// �̿�� Ȯ�� 
		siTicketPos = pclCM->CR[chatid]->pclCI->clCharItem.GetItemPos(siTicketUnique);
		if( siTicketPos < PERSONITEM_INV0 || siTicketPos >= MAX_ITEM_PER_PERSON )								
			siSuccess = -1;
		if(siSuccess > 0 && pclCM->CR[chatid]->pclCI->clCharItem.clItem[siTicketPos].siItemNum < siTicketNum)	
			siSuccess = -1;
		//////////////////////////////////////////////////////////////////////////
	}
	
	// �к� �����̾��� �ƴϸ� �ŷ� ���� �������� �˻��Ѵ�.
	if( false == Special_Premiun )
	{
		// �̿���� �ִµ� �÷��� ItemList�� �ŷ� ��������̸� siSuccess = -3;
		if(siSuccess > 0 && pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM && pclinfo->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT )
		{
			for(SI32 i = 0; i <MAX_SHOP_ITEM_NUMBER; ++i )
			{
				if(pclinfo->clShopData.m_clItem[i].siUnique)
				{
					SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clShopData.m_clItem[i].siUnique);
					if(ref > 0)	
					{
						// �ŷ����ɹ�ǰ���� �˻��Ѵ�.
						if( pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) ||
							//cyj �ͼӾ������� ����
							pclinfo->clShopData.m_clItem[i].IsBelonging(pclItemManager)		||
							pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(8150)	||
							pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14300)	||
							pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14400)	||
							pclinfo->clShopData.m_clItem[i].siUnique == ITEMUNIQUE(14500)) // �ݰ��Ǳ�� ��
						{
							siSuccess = -3;
						}
					}
					if(pclClient->IsCountrySwitch(Switch_FourLeaf))
					{
						//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
						if( ITEMUNIQUE(2755) == pclinfo->clShopData.m_clItem[i].siUnique || 
							ITEMUNIQUE(2754) == pclinfo->clShopData.m_clItem[i].siUnique	)	
						{	
							if( pclinfo->clShopData.m_clItem[i].siUnique != siFourLeafUnique )	
							{
								siSuccess = -3;
							}
						}
					}
				}
			}
		}
	}

	// �������� �ִ� ������ ���� ���Ѵ�.
	if(siSuccess > 0 )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclchar->GetMapIndex()) == true )
		{
			CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
			SI32 siShopNum = pclMapManager->pclVillageManager->GetPersonalShopNumber(pclchar->GetMapIndex());
			if(pclminister  && siShopNum >= pclminister->GetMaxShopNum() )
			{
				siSuccess = -4;
			}
		}
	}

	if(siSuccess > 0)
	{
		// �̿���� ����� ������ Unique�� �ش�.
		SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();

		cltItem clTicketItem;
		SI16 brareswitch = 0;
		pclClient->pclItemManager->MakeRandItemUnique( siTicketUnique, &clTicketItem, 0, 0, &brareswitch, 0,0,0,0,0,0);
		clTicketItem.SetItemNum(siTicketNum);

		// �ͼ����� �̿�� ������
		if(true == Special_Premiun)    
		{
			// ����ϴ� �ͼ����� �̿�� �������� ������ 0��
			siTicketNum = 0;
		}

		// DB�� ��û�Ѵ�. 
		sDBRequest_StartPersonalShop clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, siTicketPos, siTicketUnique, siTicketNum, &pclinfo->clShopData, &clTicketItem);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		
		// ��ǰ ��� ��踦 ����.(���λ��� �̿��)
		pclItemManager->AddUseNum(siTicketUnique, siTicketNum);
		
		//���ο� ��� - ��ǰ(���λ��� �̿��) ��� ��踦 ����.
		//NStatistics_Add("Item", siTicketUnique, "UseNum", siTicketNum);

		//==========================================================
		// �̸� ��ʴ� ����� ��ġ �� 
		pclchar->SetPersonalShopBanner(&pclinfo->clShopData);
		pclchar->SetPersonalShopData(false, &pclinfo->clShopData);
		//==========================================================
		// Ȥ�ó� �ؼ��� �ٽ� �ѹ� 
		pclchar->clShopData.m_siPersonID = pclchar->pclCI->GetPersonID();
		StringCchCopy(pclchar->clShopData.m_szAccountID, MAX_PLAYER_NAME, pclchar->pclCI->clBI.szAccountID);

		pclchar->clShopData.m_clSpacialItem.Set(&pclinfo->clShopData.m_clSpacialItem);						
		pclchar->clShopData.m_siSelectedSpacialInventoryPos = pclinfo->clShopData.m_siSelectedSpacialInventoryPos;
		//==========================================================

		// �����Ƿ� ����Ʈ
		if ( pclinfo->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM )
		{
			pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_MAKEREQUESTSTART);
		}
	}
	else
	{
		// ���� ������ �����Ѵ�.
		cltGameMsgResponse_StartPersonalShop clinfo(pclchar->GetCharUnique(), siSuccess, false,PSHOP_MODE_NONE);	// ������� ���з� ���� ���� 
		cltMsg clMsg(GAMEMSG_RESPONSE_STARTPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [�α��߰� : Ȳ���� 2007. 9. 3] // ���λ��� ���� ����. 
		//	// param1 == ���λ����� ���п���, param2 == �����̾� ����.
		//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_START, 
		//		0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		//		siSuccess, false, 0, 0, 0, NULL, NULL);
		//}
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_MAKEPERSONALSHOP_MANUFACTUER(cltMsg* pclMsg, SI32 id)
{
	// ���⿡�� ���� ������ ������ - ������ Ŭ���� ����� ���Ḧ ���� ��� 
	cltGameMsgRequest_MakePersonalShop_Manufactuer* pclinfo = (cltGameMsgRequest_MakePersonalShop_Manufactuer*)pclMsg->cData;

	SI32 Shopperid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(Shopperid) == false)return ;
	if(pclCM->IsValidID(id)		   == false)return ;

	// ��ǰ�� �����Ƿ��� ������������ �˻��Ѵ�.
	cltCharServer* pclmanufacture = (cltCharServer* )pclCM->CR[Shopperid];	// ->  ������ 
	cltCharServer* pclBuyer   = (cltCharServer* )pclCM->CR[id];			// -> ���� ���� ��� 
	if ( pclmanufacture == NULL || pclBuyer == NULL )	return;

	cltShopTradeData	*pShoperShopData = &pclmanufacture->clShopData;

	SI32 siSuccess = 1;
	//---------------------------------------------
	// ���� ������ �������ֱ���� �� ������ ���ΰ� ������ ���¸� ���Ѵ�.
	//---------------------------------------------
	if(siSuccess > 0)
	{
		if(pclmanufacture->bPersonalShopSwitch == false)							siSuccess = -1;// ������ �����ϰ� ���� �ʴ�.
		if(pclmanufacture->clShopData.m_siShopMode != pclinfo->siShopMode)			siSuccess = -1;// ������ ��尡 ���� �ٸ���.
		if(pclmanufacture->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT)		siSuccess = -1;// ������ ��尡 PSHOP_MODE_MAKEITEM_WANT�� �ƴϴ�.
		if(pclmanufacture->pclCI->GetPersonID()!= pclinfo->siPersonID)				siSuccess = -1;// PERSON ID �� �ٸ���.
		if(pclmanufacture->siPersonalMakeItemType > 0  )							siSuccess = -7;// ���� �������̴�.
	}

	//---------------------------------------------
	// ���� �����ϰ��� �ϴ� ������ �����Ѵ�.
	//---------------------------------------------
	SI32 siShowcaseIndex = 0;
	if(siSuccess > 0)
	{
		if(pclinfo->clItem.siUnique<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum<1)										siSuccess = -2;	
		if(pclinfo->clItem.siItemNum>MAX_ITEM_PILE_NUMBER)					siSuccess = -2;	
		if(pclinfo->siPrice < 0 )											siSuccess = -2;	
		if(pclinfo->siPrice > MAX_PRICE_IN_MARKET )							siSuccess = -2;	
		if(pclinfo->siHandPoint <0)											siSuccess = -2;	
		if(pclinfo->siSkillLevel<0)											siSuccess = -2;	

		// showcase index�� Ʋ�ȴ�.
		siShowcaseIndex = pclinfo->siShowcaseIndex;
		if(siShowcaseIndex< 0 || siShowcaseIndex>= MAX_SHOP_MAKEITEM_NUMBER)siSuccess = -2; 
	}
	//---------------------------------------------
	// ���� �����ϰ��� �ϴ� ������ ���������� ShowCase ������ ���Ѵ�.
	//---------------------------------------------
	SI32 siShopperInventoryPos = 0;
	SI32 siShowcaseItemNum = 0;
	if(siSuccess > 0)
	{
		// �������� ��ġ���� ����.
		if(pclinfo->clItem.IsSame( &pShoperShopData->m_clItem[siShowcaseIndex], false )==FALSE )siSuccess = -3;
		// ������ �����ᰡ ��ġ���� ������� 
		if(pclinfo->siPrice != pShoperShopData->m_siPrice[siShowcaseIndex])	siSuccess = -3;
		// ���������� ������ �Ҷ� 
		if(pShoperShopData->m_siPrice[siShowcaseIndex] < 0)					siSuccess = -3;
		// ������ �Ǹ� ������ �������Ҷ� 
		siShowcaseItemNum = pShoperShopData->m_clItem[siShowcaseIndex].siItemNum;
		if(siShowcaseItemNum < 1)											siSuccess = -3;

		if(pclinfo->siHandPoint  != pShoperShopData->m_siHandPoint )		siSuccess = -3;
		if(pclinfo->siSkillLevel != pShoperShopData->m_siSkillLevel )		siSuccess = -3;
	}
	//---------------------------------------------
	// �����Ƿڸ� �һ���� ���� �ֳ� Ȯ��
	//---------------------------------------------
	SI64 siTotalPrice = 0; 
	if(siSuccess > 0)
	{
		SI64 TotalBuyerMoney = (SI64)pclBuyer->pclCI->clIP.GetMoney();
		siTotalPrice         = (SI64)pclinfo->siPrice * (SI64)pclinfo->clItem.siItemNum;
		if( siTotalPrice < 0)
		{
			siSuccess = -5;
		}
		else if ( siTotalPrice > TotalBuyerMoney )	
		{
			siSuccess = -5;
		}
	}
	//---------------------------------------------------------------
	// Shopper�� ��ǰ -> Buyer�� BuyerInvPos, Buyer�� �� -> Shopper
	//---------------------------------------------------------------
	// DB Message�� ������.
	if(siSuccess > 0)
	{
		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclmanufacture->ItemUseReserveAction();
		pclBuyer->ItemUseReserveAction();
		//---------------------------------------------

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		pclmanufacture->BulletUseReserveAction();
		pclBuyer->BulletUseReserveAction();

		//---------------------------------------------------------------
		// DO SOMETHING �°� 
		//---------------------------------------------------------------

		cltGameMsgRequest_MakeItemInv clinfo(pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum,
			pclBuyer->GetCharUnique(),
			pclmanufacture->GetCharUnique(),
			pclinfo->siShopMode,
			pclinfo->siType,false,true); // siTotalPrice
		pclmanufacture->siPersonalMakeItemType = pclinfo->siType;

		cltGameMsgResponse_MakeItemSwitch clinfo2( pclinfo->siType );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclmanufacture->SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		pclmanufacture->SendNeighbourMyMakeItemStatus();
		MakeItemProcess(pclmanufacture->GetID() , &clinfo);
	}
	else		
	{
		SI32 siFailReason = 0;
		switch(siSuccess)
		{
		case -1: siFailReason = MAKEPERSONALSHOP_FAIL_SHOPPERSTATUS;  break;// ���۽��� 
		case -2: siFailReason = MAKEPERSONALSHOP_FAIL_MAKERSTATUS;	  break;// ���۽��� 
		case -3: siFailReason = MAKEPERSONALSHOP_FAIL_SHOWCASESTATUS; break;// ���۽��� 
		case -4: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NOITEM;	  break;// ���۽��� 
		case -5: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NOMONEY;   break;// ���۽��� 
		case -6: siFailReason = MAKEPERSONALSHOP_FAIL_MAKE_NEEDABILITY;break;// ���۽���
		case -7: siFailReason = MAKEPERSONALSHOP_FAIL_NOWMAKINGSTATUS;break;// ���۽���
		default: siFailReason = MAKEPERSONALSHOP_FAIL_UNKNOWN;		  break;// ���۽��� 
		}
		//���� ���۽� 
		// ��忡 ���� ���� �ٸ� ������� �Ѵ� 
		// ������ �����Ƿ��� ���
		// �ٸ� ��쿡�� ��� ���ο��� ������ 

		if(pclinfo->siShopMode == PSHOP_MODE_MAKEITEM_WANT)
		{
			// Client���� siSuccess ���������� �����Ѵ�.
			cltGameMsgResponse_MakePersonalShop clInfo(id, siFailReason, pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


			pclCM->CR[id]->siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo2( 0 );
			cltMsg clMsg2(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
		}
		else
		{
			// Client���� siSuccess ���������� �����Ѵ�.
			cltGameMsgResponse_MakePersonalShop clInfo(id, siFailReason, pclinfo->clItem.siUnique, pclinfo->clItem.siItemNum);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


			pclCM->CR[id]->siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo2( 0 );
			cltMsg clMsg2(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
		}
		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyMakeItemStatus();
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_SEARCHMANUFACTURE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SearchManufacture* pclinfo = (cltGameMsgRequest_SearchManufacture*)pclMsg->cData;

	if(pclCM->IsValidID(id)		   == false)return;
	if(pclinfo->siItemUniqueType <1)		return;

	cltSearchShopData	clSearchShopData;
	//-------------------------------------------
	// �˻� �⺻�����͸� �����Ѵ�.
	//-------------------------------------------
	clSearchShopData.m_siShopMode		 = pclinfo->siShopMode;
	clSearchShopData.m_siItemUniqueType  = pclinfo->siItemUniqueType;
	//-------------------------------------------
	// ����ڸ� �˻��Ͽ� ������ ��´�.
	//-------------------------------------------
	SI32 siCount = 0;
	for ( SI32 i = 0; i < MAX_PERSON_NUMBER && siCount< MAX_SEARCHSHOP_ITEM_NUMBER; ++i )
	{
		if ( pclCM->IsValidID( i ) && IsPC(i))
		{
			cltCharServer* pclchar = (cltCharServer* )pclCM->CR[i];
			// ���� ������ ���� �����鼭 ���� ShopMode��� ��ǰ�� �˻��Ѵ�.
			if(pclchar && pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode == pclinfo->siShopMode)
			{
				for(SI32 j = 0; j < MAX_SHOP_ITEM_NUMBER && siCount< MAX_SEARCHSHOP_ITEM_NUMBER; ++j) 
				{
					// ���� Ÿ���� �������� ������ ���� ������ 
					SI32 siItemUnique = pclchar->clShopData.m_clItem[j].siUnique;
					if( siItemUnique == 0) continue;

					if( pclItemManager->GetItemType(siItemUnique) == pclinfo->siItemUniqueType &&
						pclchar->clShopData.m_clItem[j].siItemNum > 0)

					{
						if(siCount<MAX_SEARCHSHOP_ITEM_NUMBER)
						{
							// �������� 
							StringCchCopy(clSearchShopData.m_szName[siCount], MAX_PLAYER_NAME, (TCHAR *)pclchar->GetName());
							clSearchShopData.m_siLevel[siCount]		= pclchar->pclCI->clIP.GetLevel();
							// �������� 
							clSearchShopData.m_siMapIndex[siCount]	= pclchar->GetMapIndex();
							clSearchShopData.m_siMapX[siCount]		= pclchar->GetX();
							clSearchShopData.m_siMapY[siCount]		= pclchar->GetY();
							// ITEM ���� 
							clSearchShopData.m_clItem[siCount].Set(&pclchar->clShopData.m_clItem[j]);
							clSearchShopData.m_siPrice[siCount]		= pclchar->clShopData.m_siPrice[j];

							clSearchShopData.m_siHandPoint[siCount]	= pclchar->clShopData.m_siHandPoint;
							clSearchShopData.m_siSkillLevel[siCount]= pclchar->clShopData.m_siSkillLevel;
							siCount++;
						}
					}
				}
			}
		}
	}
	cltGameMsgResponse_SearchManufacture clinfo(TRUE, &clSearchShopData);
	cltMsg clMsg(GAMEMSG_RESPONSE_SEARCHMANUFACTURE, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

