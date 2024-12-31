//----------------------------
// ���� 2007/04/13
//----------------------------
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"


#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Gacha.h"

#include "MsgRval-Define.h"

#include "../Server/GachaManager/GachaManager.h"
#include "../CommonLogic/Msg/MsgType-Gacha.h"

#include "../Server/Gacha2Manager/Gacha2Manager.h"
				
void cltServer::DoMsg_GAMEMSG_REQUEST_GACHAPRODUCT_LIST( cltMsg* pclMsg, SI32 id )
{
	//cltGameMsgRequest_GachaProduct_List* pclinfo = (cltGameMsgRequest_GachaProduct_List*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}

	cltItem clGachaProductList[MAX_GACHA_PRODUCT];

	for( SI16 i = 0 ; i < MAX_GACHA_PRODUCT ; i++ )
	{
		clGachaProductList[i].Init();

		clGachaProductList[i].siUnique =	pclGachaManager->m_GachaProduct[0][i].ItemUnique;
		clGachaProductList[i].siItemNum =	pclGachaManager->m_GachaProduct[0][i].ItemNum;
		clGachaProductList[i].uiDateUseDay =	pclGachaManager->m_GachaProduct[0][i].ItemUseDate;
	}
	

	cltGameMsgResponse_GachaProduct_List clinfo(  clGachaProductList , pclchar->pclCI->uiGachaCnt );
	cltMsg clMsg(GAMEMSG_RESPONSE_GACHAPRODUCT_LIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

//KHY - 1104 -  ����2 -���� ���� ����. 
void cltServer::DoMsg_GAMEMSG_REQUEST_GACHA2PRODUCT_LIST( cltMsg* pclMsg, SI32 id )
{
	//cltGameMsgRequest_GachaProduct_List* pclinfo = (cltGameMsgRequest_GachaProduct_List*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}

	cltItem clGachaProductList[MAX_GACHA2_PRODUCT];

	for( SI16 i = 0 ; i < MAX_GACHA2_PRODUCT ; i++ )
	{
		clGachaProductList[i].Init();

		clGachaProductList[i].siUnique =	pclGacha2Manager->m_GachaProduct[0][i].ItemUnique;
		clGachaProductList[i].siItemNum =	pclGacha2Manager->m_GachaProduct[0][i].ItemNum;
		clGachaProductList[i].uiDateUseDay =	pclGacha2Manager->m_GachaProduct[0][i].ItemUseDate;
	}
	

	cltGameMsgResponse_Gacha2Product_List clinfo(  clGachaProductList , pclchar->pclCI->uiGachaCnt );
	cltMsg clMsg(GAMEMSG_RESPONSE_GACHA2PRODUCT_LIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}


// ���� ���� �ʴµ� �ѵ� �׷��� Ȥ�� �𸣴ϱ� ���⵵ �ѹ� ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_GACHABUY( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_GachaBuy* pclinfo = (cltGameMsgRequest_GachaBuy*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	
	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}	

	// �̹� ���� ���̶�� �׳� ������.
	if( pclchar->bNowGachaBuy )
	{
		return;
	}
    
	// �������� ���� �κ� ��ĭ�� Ȯ���Ǿ� �ִ��� üũ
	if( pclchar->IsBlankInv(1,INVMODE_ALL) == false )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return; 
	}



	cltItem clGetItem;
	cltItem clKeyItem;

	// ���� ����, ���� ������ ������ ������� üũ

	if( pclinfo->siUseKeyKind == GACHA_USE_GOLDKEY )
	{
		clKeyItem.siUnique = GACHA_GOLDKEY_ITEMUNIQUE;
		clKeyItem.siItemNum = 1;
	}
	else if( pclinfo->siUseKeyKind == GACHA_USE_SILVERKEY )
	{
		clKeyItem.siUnique = GACHA_SILVERKEY_ITEMUNIQUE;
		clKeyItem.siItemNum = 1;
	}
	else if( pclinfo->siUseKeyKind == GACHA_USE_BRONZEKEY )
	{
		clKeyItem.siItemNum = 1;

		// ������ ����� ��� �̺�Ʈ �����踦 �켱���� ����Ѵ�.
		if( pclchar->pclCI->clCharItem.GetItemNum( GACHA_BRONZEKEY_EVENT_ITEMUNIQUE ) >= clKeyItem.siItemNum )
			clKeyItem.siUnique = GACHA_BRONZEKEY_EVENT_ITEMUNIQUE;
		else
			clKeyItem.siUnique = GACHA_BRONZEKEY_ITEMUNIQUE;
	}
	else if( pclinfo->siUseKeyKind == GACHA_USE_KEYPIECE ) 
	{
		clKeyItem.siUnique = GACHA_KEYPIECE_ITEMUNIQUE;
		clKeyItem.siItemNum = GACHA_KEYPIECE_NEED_NUM;
	}
	else
	{
		return;
	}

	if( pclchar->pclCI->clCharItem.GetItemNum( clKeyItem.siUnique ) < clKeyItem.siItemNum )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
		return; 
	}

/*
	SI32 KeyItemPos = pclchar->pclCI->clCharItem.GetItemPos( clKeyItem.siUnique );

	if( KeyItemPos < 0 )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
		return; 
	}
*/
	SI32 KeyItemPos = -1 ;
	
	// �ʿ��� ���� �̻��� �������� �ѽ��Կ� �����ؾ� �Ѵ�
	for(SI16 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(pclchar->pclCI->clCharItem.clItem[i].siUnique == clKeyItem.siUnique)
		{
			if( pclchar->pclCI->clCharItem.clItem[i].siItemNum >=  clKeyItem.siItemNum )
			{
				KeyItemPos = i ;
				break;
			}
		}
	}

	if( KeyItemPos < 0 )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
		return; 
	}
	// ������ �� ��ǰ�� ����� ����.

	// �ְ�� ��ǰ�� ���� Ȯ���� ���� ���ʽ� ����Ʈ	
	SI32 BonusGachaRate = min( pclchar->pclCI->uiGachaCnt , MAX_GACHA_BONUS_VALUE ); 
	bool GetBestProduct = false;

	// ���ʽ� ����Ʈ�� ���� Ȯ�������� �ֱױ� ��ǰ�� �ش�.
 	if( BonusGachaRate )
	{
		// 100ȸ �̻� ������ �ְ� 10%���� �ö󰣴�
		SI32 RandVal1 = TABS(CurrentClock) / 10 % 10;

 		SI32 RandVal = rand()%1000  + RandVal1 * 1000;


		if( BonusGachaRate > RandVal )
		{
			GetBestProduct = true;
			// ��� ����� ù��° ��ǰ�� �ֻ�� ��ǰ�̴�.
			clGetItem.siUnique = pclGachaManager->m_GachaProduct[0][0].ItemUnique;
			clGetItem.siItemNum = pclGachaManager->m_GachaProduct[0][0].ItemNum;
			clGetItem.uiDateUseDay = pclGachaManager->m_GachaProduct[0][0].ItemUseDate;

			pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Bonus\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, clKeyItem.siUnique );
		}

	}
	

	// �Ϲ� ���� ����. 
	if( GetBestProduct == false )
	{
		// ���� �ְ�í Ȯ���� �������� �ٸ�
		SI32 RandVal1 = TABS(CurrentClock) / 10 % 10;

		SI32 RandVal = rand()%100  + RandVal1 * 100;


		SI32 GachaRateSum = 0;
		SI32 GachaKeyIndex = 0;
		//���� �����ۿ� ���� Ȯ������
		if( pclinfo->siUseKeyKind ==  GACHA_USE_GOLDKEY )
		{
			GachaKeyIndex = 0;
		}
		else if( pclinfo->siUseKeyKind ==  GACHA_USE_SILVERKEY )
		{
			GachaKeyIndex = 1;
		}
		else if( pclinfo->siUseKeyKind ==  GACHA_USE_BRONZEKEY )
		{
			GachaKeyIndex = 2;
		}
		else if( pclinfo->siUseKeyKind ==  GACHA_USE_KEYPIECE )
		{
			//[�迵�� ����:2007.11.28 - ���ƾ��� Ȯ���� ������ ������ ���� ����Ͽ����ϴ�(1���� 2�� ����)]
			GachaKeyIndex = 2;
		}
		else
		{
			return;
		}
		// ���� �ְ� ��ǰ�� ù���� ��ǰ!
		for( SI16 i = 0 ; i < MAX_GACHA_PRODUCT ; i++ )
		{
			// �� ǰ���� ��÷ Ȯ���� �ɸ����̶�� 
			if(  GachaRateSum <= RandVal  
				&& RandVal <= GachaRateSum + pclGachaManager->m_GachaProduct[GachaKeyIndex][i].GachaRate  )
			{
				// ù��° ��ǰ�� ��÷�̶�� �ְ� ��ǰ�� ��÷�� ���̴�
				if(  i == 0 ) 
				{
					GetBestProduct = true;
					pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Normal\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, clKeyItem.siUnique );
				}
				
				// ��÷�� ��ǰ�� �������ش�.
				clGetItem.siUnique = pclGachaManager->m_GachaProduct[GachaKeyIndex][i].ItemUnique;
				clGetItem.siItemNum = pclGachaManager->m_GachaProduct[GachaKeyIndex][i].ItemNum;
				clGetItem.uiDateUseDay = pclGachaManager->m_GachaProduct[GachaKeyIndex][i].ItemUseDate;

				break;
			}

			GachaRateSum += pclGachaManager->m_GachaProduct[GachaKeyIndex][i].GachaRate;
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
	

	

	SI16 itempos = 0;
	cltItem cltoitem;
	SI32 rtnvalue = 0;

	if( pclchar->CanAddInv(INVMODE_ALL, &clGetItem, &itempos, &cltoitem, &rtnvalue) == true )
	{
		// DB�� ��í ���� Ȥ�� ���� ���� �Ҹ�� �Բ� ������ ���� �Ƿ�

		pclchar->bNowGachaBuy = true;
		
		//---------------------------------------------
		// ���踦 �Ҹ��ų �ڸ��� �������� �� �ڸ��� �����Ѵ�.
		//---------------------------------------------

		pclchar->SetInputItemReserve(itempos , CurrentClock );
		pclchar->SetInputItemReserve(KeyItemPos , CurrentClock );

		UI08 uiGachaCntAddNum = pclGachaManager->GetCachaCntAddNum( pclinfo->siUseKeyKind );
		
		sDBRequest_GachaBuy clMsg( id , pclchar->pclCI->GetPersonID() , &clKeyItem  , &clGetItem , clGetItem.CanPile(pclItemManager) , KeyItemPos , itempos , pclchar->pclCI->uiGachaCnt , GetBestProduct, uiGachaCntAddNum);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return;		
	}


}

//KHY - 1104 -  ����2 -���� ���� ����. 
void cltServer::DoMsg_GAMEMSG_REQUEST_GACHA2BUY( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_GachaBuy* pclinfo = (cltGameMsgRequest_GachaBuy*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	
	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}
	// �̹� ���� ���̶�� �׳� ������.
	if( pclchar->bNowGachaBuy )
	{
		return;
	}

	// �������� ���� �κ� ��ĭ�� Ȯ���Ǿ� �ִ��� üũ
	if( pclchar->IsBlankInv(1,INVMODE_ALL) == false )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return; 
	}



	cltItem clGetItem;
	cltItem clKeyItem;

	// ����2 ���� ������� üũ

	//KHY - 1104 -  ����2 -���� ���� ����. 
	if( pclinfo->siUseKeyKind == GACHA2_USE_KEY1)
	{
		clKeyItem.siUnique = GACHA2_RACCOONKEY_ITEMUNIQUE;
		clKeyItem.siItemNum = 1;
	}
	else
	{
		return;
	}

	if( pclchar->pclCI->clCharItem.GetItemNum( clKeyItem.siUnique ) < clKeyItem.siItemNum )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
		return; 
	}

	SI32 KeyItemPos = -1 ;
	
	// �ʿ��� ���� �̻��� �������� �ѽ��Կ� �����ؾ� �Ѵ�
	for(SI16 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(pclchar->pclCI->clCharItem.clItem[i].siUnique == clKeyItem.siUnique)
		{
			if( pclchar->pclCI->clCharItem.clItem[i].siItemNum >=  clKeyItem.siItemNum )
			{
				KeyItemPos = i ;
				break;
			}
		}
	}

	if( KeyItemPos < 0 )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
		return; 
	}
	// ������ �� ��ǰ�� ����� ����.

	// �ְ�� ��ǰ�� ���� Ȯ���� ���� ���ʽ� ����Ʈ	
	SI32 BonusGachaRate = min( pclchar->pclCI->uiGachaCnt , MAX_GACHA_BONUS_VALUE ); 
	bool GetBestProduct = false;

	// ���ʽ� ����Ʈ�� ���� Ȯ�������� �ֱױ� ��ǰ�� �ش�.
 	if( BonusGachaRate )
	{
		// 100ȸ �̻� ������ �ְ� 10%���� �ö󰣴�
		SI32 RandVal1 = TABS(CurrentClock) / 10 % 10;

 		SI32 RandVal = rand()%1000  + RandVal1 * 1000;


		if( BonusGachaRate > RandVal )
		{
			GetBestProduct = true;
			// ��� ����� ù��° ��ǰ�� �ֻ�� ��ǰ�̴�.
			clGetItem.siUnique = pclGacha2Manager->m_GachaProduct[0][0].ItemUnique;
			clGetItem.siItemNum = pclGacha2Manager->m_GachaProduct[0][0].ItemNum;
			clGetItem.uiDateUseDay = pclGacha2Manager->m_GachaProduct[0][0].ItemUseDate;

			pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Bonus\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, clKeyItem.siUnique );
		}

	}
	

	// �Ϲ� ���� ����. 
	if( GetBestProduct == false )
	{
		// ���� �ְ�í Ȯ���� �������� �ٸ�
		SI32 RandVal1 = TABS(CurrentClock) / 10 % 10;

		SI32 RandVal = rand()%100  + RandVal1 * 100;


		SI32 GachaRateSum = 0;
		SI32 GachaKeyIndex = 0;

		//���� �����ۿ� ���� Ȯ������
		if( pclinfo->siUseKeyKind ==  GACHA2_USE_KEY1 )
		{
			//KHY - 1104 -  ����2 -���� ���� ����.  - ù��° �ε���
			GachaKeyIndex = 0;
		}
		else
		{
			return;
		}

		for( SI16 i = 0 ; i < MAX_GACHA2_PRODUCT ; i++ )
		{
			// �� ǰ���� ��÷ Ȯ���� �ɸ����̶�� 
			if(  GachaRateSum <= RandVal  
				&& RandVal <= GachaRateSum + pclGacha2Manager->m_GachaProduct[GachaKeyIndex][i].GachaRate  )
			{
				// ù��° ��ǰ�� ��÷�̶�� �ְ� ��ǰ�� ��÷�� ���̴�
				if(  i == 0 ) 
				{
					GetBestProduct = true;

					pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Normal\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, clKeyItem.siUnique );
				}
				
				// ��÷�� ��ǰ�� �������ش�.
				clGetItem.siUnique = pclGacha2Manager->m_GachaProduct[GachaKeyIndex][i].ItemUnique;
				clGetItem.siItemNum = pclGacha2Manager->m_GachaProduct[GachaKeyIndex][i].ItemNum;
				clGetItem.uiDateUseDay = pclGacha2Manager->m_GachaProduct[GachaKeyIndex][i].ItemUseDate;

				break;
			}

			GachaRateSum += pclGacha2Manager->m_GachaProduct[GachaKeyIndex][i].GachaRate;
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
	
	SI16 itempos = 0;
	cltItem cltoitem;
	SI32 rtnvalue = 0;

	if( pclchar->CanAddInv(INVMODE_ALL, &clGetItem, &itempos, &cltoitem, &rtnvalue) == true )
	{
		// DB�� ��í ���� Ȥ�� ���� ���� �Ҹ�� �Բ� ������ ���� �Ƿ�

		pclchar->bNowGachaBuy = true;
		
		//---------------------------------------------
		// ���踦 �Ҹ��ų �ڸ��� �������� �� �ڸ��� �����Ѵ�.
		//---------------------------------------------

		pclchar->SetInputItemReserve(itempos , CurrentClock );
		pclchar->SetInputItemReserve(KeyItemPos , CurrentClock );

		UI08 uiGachaCntAddNum = pclGachaManager->GetCachaCntAddNum( pclinfo->siUseKeyKind );
		
		sDBRequest_GachaBuy clMsg( id , pclchar->pclCI->GetPersonID() , &clKeyItem  , &clGetItem , clGetItem.CanPile(pclItemManager) , KeyItemPos , itempos , pclchar->pclCI->uiGachaCnt , GetBestProduct, uiGachaCntAddNum);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return;		
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CARRYOVER_GACHA_LIST(cltMsg* pclMsg, SI32 id)
{
	if ( false == IsCountrySwitch(Switch_CarryOverGacha) )
	{
		return;
	}
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}
	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}

	SI32 siTotalProductUnique[ TOTAL_GACHA_PRODUCT ];

	ZeroMemory( siTotalProductUnique, sizeof(siTotalProductUnique) );
	
	// �̴��� ��í
	siTotalProductUnique[0] = pclGachaManager->m_GachaProduct[0][0].ItemUnique;

	// �̿� ��í
	for ( SI32 siIndex=0; siIndex<MAX_CARRYOVER_PRODUCT; siIndex++ )
	{
		siTotalProductUnique[siIndex + 1] = pclGachaManager->GetCarryOverGachaItemUnique( siIndex );
	}
	

	cltGameMsgResponse_CarryOver_Gacha_list clinfo( siTotalProductUnique, pclchar->pclCI->uiGachaCnt );
	cltMsg clMsg( GAMEMSG_RESPONSE_CARRYOVER_GACHA_LIST, sizeof(clinfo), (BYTE*)&clinfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CARRYOVER_SELECTPRODUCT_LIST(cltMsg* pclMsg, SI32 id)
{
	if ( false == IsCountrySwitch(Switch_CarryOverGacha) )
	{
		return;
	}

	cltGameMsgRequest_CarryOver_SelectProduct_List* pclInfo = (cltGameMsgRequest_CarryOver_SelectProduct_List*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}

	if ( false == pclGachaManager->IsPare(pclInfo->m_siSelectIndex, pclInfo->m_siSelectUnique) )
	{
		return;
	}

	// ���õ� ��í�� ��ǰ ����Ʈ�� ����´�
	SI32 siProductList[MAX_GACHA_PRODUCT];

	pclGachaManager->GetGachaProductFromIndex( pclInfo->m_siSelectIndex, pclInfo->m_siSelectKeyKind, siProductList );

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_CarryOver_SelectProduct_List clinfo( siProductList );
	cltMsg clMsg( GAMEMSG_RESPONSE_CARRYOVER_SELECTPRODUCT_LIST, sizeof(clinfo), (BYTE*)&clinfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

//���� ��ư �����鿩�⼭ ��ǰ�� �ش�.
void cltServer::DoMsg_GAMEMSG_REQUEST_CARRYOVER_GACHABUY(cltMsg* pclMsg, SI32 id)
{
	if ( false == IsCountrySwitch(Switch_CarryOverGacha) )
	{
		return;
	}
	cltGameMsgRequest_CarryOver_GachaBuy* pclInfo = (cltGameMsgRequest_CarryOver_GachaBuy*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) && bGachaLock == true	 )	// ������� ���� ���� ���� üũ �Ѵ�. ��� ���Ҷ��� �޼����� �ִ´� .
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_LOCK, 0, 0, pclchar->GetID());
		return	;
	}


	// �⺻������ ���� ������
	SI32 siSelectIndex	= pclInfo->m_siSelectIndex;
	SI32 siKeyKind		= pclInfo->m_siKeyKind;

	// ������ �ε����� �ְ� �������� �ٸ��ٸ� �߸��Ȱ�
	if ( false == pclGachaManager->IsPare(siSelectIndex, pclInfo->m_siSelectUnique) )
	{
		if( true == IsCountrySwitch(Switch_GACHA_RAREITEM_CHANGE) )
		{	
			SendServerResponseMsg(0, SRVAL_GACHA_NOTCORRECT_ITEM, 0, 0, pclchar->GetID());	// ��í �ְ� �������� �ٸ��� �޼����� �����ش�.
		}

		return;
	}

	// �̹� ���� ���̶�� �׳� ������.
	if ( true == pclchar->bNowGachaBuy )
	{
		return;
	}

	// �������� ���� �κ� ��ĭ�� Ȯ���Ǿ� �ִ��� üũ
	if ( false == pclchar->IsBlankInv(1,INVMODE_ALL) )
	{
		SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return; 
	}

	// Ű �������� �ִ��� �˻��Ѵ�
	SI32 siKeyItemUnique	= 0;
	SI32 siKeyItemNum		= 1;

	switch ( siKeyKind )
	{
	case GACHA_USE_GOLDKEY:			{	siKeyItemUnique = GACHA_GOLDKEY_ITEMUNIQUE;			}	break;
	case GACHA_USE_SILVERKEY:		{	siKeyItemUnique = GACHA_SILVERKEY_ITEMUNIQUE;		}	break;
	case GACHA_USE_BRONZEKEY:	// ������ ���� ��� �̺�Ʈ ������ ���� üũ�غ���
		{	
			if ( pclchar->pclCI->clCharItem.GetItemNum(GACHA_BRONZEKEY_EVENT_ITEMUNIQUE) >= siKeyItemNum )
			{
				siKeyItemUnique = GACHA_BRONZEKEY_EVENT_ITEMUNIQUE;
			}
			else
			{
				siKeyItemUnique = GACHA_BRONZEKEY_ITEMUNIQUE;		
			}
		}	
		break;
	case CARRYOVER_USE_GOLDKEY:		{	siKeyItemUnique = CARRYOVER_GOLDKEY_ITEMUNIQUE;		}	break;
	case CARRYOVER_USE_SILVERKEY:	{	siKeyItemUnique = CARRYOVER_SILVERKEY_ITEMUNIQUE;	}	break;
	case CARRYOVER_USE_BRONZEKEY:	{	siKeyItemUnique = CARRYOVER_BRONZEKEY_ITEMUNIQUE;	}	break;
	default:
		{
			return;
		}
		break;
	}

	if ( pclchar->pclCI->clCharItem.GetItemNum(siKeyItemUnique) < siKeyItemNum )
	{
		SendServerResponseMsg( 0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID() );
		return; 
	}

	// Ű �������� �κ��丮 ��ġ�� ���´�
	SI32 siKeyItemPos = -1;

	for ( SI32 siPosition=PERSONITEM_INV0; siPosition<(PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON); siPosition++ )
	{
		if ( siKeyItemUnique == pclchar->pclCI->clCharItem.clItem[siPosition].siUnique )
		{
			if ( siKeyItemNum <= pclchar->pclCI->clCharItem.clItem[siPosition].siItemNum )
			{
				siKeyItemPos = siPosition;
				break;
			}
		}
	}

	if ( 0 > siKeyItemPos )
	{
		SendServerResponseMsg( 0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID() );
		return; 
	}

	// ��í�� ������ ��� ����
	cltItem clGetItem;

	// ��í �õ� Ƚ���� ���� �ְ�� ��ǰ ���
	SI32 siBonusGachaRate	= min( pclchar->pclCI->uiGachaCnt, MAX_GACHA_BONUS_VALUE );
	bool bGetBestProduct	= false;
	
	if ( 0 < siBonusGachaRate )
	{
		// 100ȸ �̻� ������ �ְ� 10%���� �ö󰣴�
		SI32 siTempVal = TABS(CurrentClock) / 10 % 10;		// (0~9)
		SI32 siRandVal = rand() % 1000 + siTempVal * 1000;	// (0~9999)

		if ( siBonusGachaRate > siRandVal )
		{
			bGetBestProduct = true;
			pclGachaManager->GetGachaItem( siSelectIndex, siKeyKind, 0, &clGetItem );

			pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Bonus\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, siKeyItemUnique );
		}
	}

	// �Ϲ� ��í ����
	if ( false == bGetBestProduct )
	{
		// ���� �ְ�í Ȯ���� �������� �ٸ�
		SI32 siTempVal = TABS(CurrentClock) / 10 % 10;		// (0~9)
		SI32 siRandVal = rand() % 100 + siTempVal * 100;	// (0~999)

		SI32 siGachaRateSum = 0;
		SI32 siNowGachaRate	= 0;
		for ( SI32 siProductIndex=0; siProductIndex<MAX_GACHA_PRODUCT; siProductIndex++ )
		{
			siNowGachaRate = pclGachaManager->GetGachaRate( siSelectIndex, siKeyKind, siProductIndex );

			if ( (siGachaRateSum <= siRandVal) && (siRandVal <= (siGachaRateSum+siNowGachaRate)) )
			{
				if ( 0 == siProductIndex )
				{
					bGetBestProduct = true;

					pclLog->FilePrint( TEXT("Config\\GachaBestItem.txt"), TEXT("Get From Normal\tBonusCount:%d\tKeyUnique:%d"), pclchar->pclCI->uiGachaCnt, siKeyItemUnique );
				}

				pclGachaManager->GetGachaItem( siSelectIndex, siKeyKind, siProductIndex, &clGetItem );
				break;
			}

			siGachaRateSum += siNowGachaRate;
		}
	}

	//---------------------------------------------
	// �������� �� �޾� ������� �׳� ����
	//---------------------------------------------
	if ( (0 >= clGetItem.siUnique) || (0 >= clGetItem.siItemNum) )
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

	SI16	siGetItemPos	= 0;
	cltItem	clToItem;

	SI32	siReturnValue	= 0;

	if ( true == pclchar->CanAddInv(INVMODE_ALL, &clGetItem, &siGetItemPos, &clToItem, &siReturnValue) )
	{
		// ��í ��ǰ �ޱ����̶�� �����ϰ�
		pclchar->bNowGachaBuy = true;

		// ��í Ű �Ҹ��ų ������ ����
		cltItem clKeyItem;

		clKeyItem.Init();
		clKeyItem.siUnique	= siKeyItemUnique;
		clKeyItem.siItemNum	= siKeyItemNum;

		// ���� ������ �ڸ��� ���� ������ �ڸ��� ����
		pclchar->SetInputItemReserve( siGetItemPos,	CurrentClock );
		pclchar->SetInputItemReserve( siKeyItemPos,	CurrentClock );

		UI08 uiGachaCntAddNum = pclGachaManager->GetCachaCntAddNum( siKeyKind );

		sDBRequest_GachaBuy clMsg( id, pclchar->pclCI->GetPersonID(), &clKeyItem, &clGetItem, clGetItem.CanPile(pclItemManager), siKeyItemPos, siGetItemPos, pclchar->pclCI->uiGachaCnt, bGetBestProduct, uiGachaCntAddNum );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		SendServerResponseMsg( 0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID() );
		return;		
	}

}
