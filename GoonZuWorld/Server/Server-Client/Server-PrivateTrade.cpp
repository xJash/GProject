#include "..\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\CommonLogic\Msg\MsgType-PrivateTrade.h"
#include "..\..\Common\PrivateTradeOrderMgr\PrivateTradeOrderMgr.h"
#include "..\..\Common\PrivateTradeOrderMgr\PrivateTradeOrderObj.h"
#include "Char\CharManager\CharManager.h"


#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "../../CommonLogic/House/House.h"

#include "MsgType-Structure.h"	// ���� �Ļ� ���� �޼��� ó��

//cltGameMsgRequest_PrivateTrade
// 1:1 �ŷ��� ��û�Ѵ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_Accept *pclPrivateTrade = (cltGameMsgRequest_PrivateTrade_Accept *) pclMsg->cData;

	if(pclCM->IsValidID(id) == FALSE)
	{
		return;
	}
    

	// �������� �ʴ� CharUnique ���� ��������.
	if ( pclPrivateTrade->siToPersonCharUnique <= 0 )
	{
		return;
	}
    
	// ��û�� ����� CharUnique ���� �̻���.
	if ( pclCM->CR[id]->GetCharUnique() <= 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTrade->siToPersonCharUnique);
	if(pclCM->IsValidID(toid) == FALSE)
	{
		return;
	}

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;
	

	//�ŷ� �¶� �ź� ��û �޽��� or �ŷ��� �޽���. �ŷ� ����� �� ����� ����(t,f)�� ����  �ٽ� �ǵ��� ���� �޽���
	if( pclPrivateTrade->siTradeMode == PRIVATETRADE_TRADE_MODE_REJECT_ACCEPT || pclPrivateTrade->siTradeMode == PRIVATETRADE_TRADE_MODE_ALREADYTRADE
		|| pclPrivateTrade->siTradeMode == PRIVATE_ENCHANT_MODE_REJECT_ACCEPT || pclPrivateTrade->siTradeMode == PRIVATE_ENCHANT_MODE_ALREADYTRADE	)
	{		
		cltGameMsgResponse_PrivateTrade_Accept clGameMsgResponse_PrivateTrade_Accept( pclCM->CR[id]->GetCharUnique(),  pclPrivateTrade->siTradeMode, 0, (TCHAR*)pclCM->CR[ id ]->GetName(), NULL );
		cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT, sizeof( clGameMsgResponse_PrivateTrade_Accept ), (BYTE*)&clGameMsgResponse_PrivateTrade_Accept );

		pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}	
	// �ŷ� �¶� �޽��� ����
	else if( pclPrivateTrade->siTradeMode == PRIVATE_ENCHANT_MODE_AGREE_ACCEPT )
	{		
		cltGameMsgResponse_PrivateTrade_Accept clGameMsgResponse_PrivateTrade_Accept( pclCM->CR[id]->GetCharUnique(),  pclPrivateTrade->siTradeMode, 0, (TCHAR*)pclCM->CR[ id ]->GetName(), NULL );
		cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT, sizeof( clGameMsgResponse_PrivateTrade_Accept ), (BYTE*)&clGameMsgResponse_PrivateTrade_Accept );

		pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	// ���� 3 �̸������� �ŷ� �ȵ�
	if ( pclCM->CR[id]->pclCI->clIP.GetLevel() < 3 || pclCM->CR[toid]->pclCI->clIP.GetLevel() < 3 )
	{
		return;
	}

	TCHAR *CharName1 = (TCHAR*)pclCM->CR[ id ]->GetName();
	if ( CharName1 == NULL || _tcslen ( CharName1 ) < 1 )
	{
		return;
	}

	TCHAR *CharName2 = (TCHAR*)pclCM->CR[ toid ]->GetName();
	if ( CharName2 == NULL || _tcslen ( CharName2 ) < 1 )
	{
		return;
	}

	SI16 CharLevel1 = pclCM->CR[id]->pclCI->clIP.GetLevel();
	SI16 CharLevel2 = pclCM->CR[toid]->pclCI->clIP.GetLevel();

	TCHAR *AccountID1 = (TCHAR*)pclCM->CR[ id ]->pclCI->clBI.szAccountID;
	if ( AccountID1 == NULL || _tcslen( AccountID1 ) < 1 )
	{
		return;
	}

	TCHAR *AccountID2 = (TCHAR*)pclCM->CR[ toid ]->pclCI->clBI.szAccountID;
	if ( AccountID2 == NULL || _tcslen( AccountID2 ) < 1 )
	{
		return;
	}


	// ������ �ŷ� �ź� ������ ���
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[toid];
	if ( pclChar->bPrivateTradeReject )
	{
		SendServerResponseMsg(0, SRVAL_PRIVATETRADE_REJECT,  0, 0, id);
		return;
	}

	// �ŷ� ��嵵 �ƴϰ�, ��þƮ ��嵵 �ƴ� ��û�� ���� �����
	if ( pclPrivateTrade->siTradeMode != PRIVATETRADE_TRADE_MODE && pclPrivateTrade->siTradeMode != PRIVATETRADE_ENCHANT_MODE )
	{
		return;
	}


	cltGameMsgResponse_PrivateTrade_Accept clGameMsgResponse_PrivateTrade_Accept( pclCM->CR[id]->GetCharUnique(),  pclPrivateTrade->siTradeMode, CharLevel1, CharName1, AccountID1 );
	cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT, sizeof( clGameMsgResponse_PrivateTrade_Accept ), (BYTE*)&clGameMsgResponse_PrivateTrade_Accept );

	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

	return;

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade *pclPrivateTrade = (cltGameMsgRequest_PrivateTrade *) pclMsg->cData;

	// �������� �ʴ� CharUnique ���� ��������.
	if ( pclPrivateTrade->siToPersonCharUnique <= 0 )
	{
		return;
	}

	// ��û�� ����� CharUnique ���� �̻���.
	if ( pclCM->CR[id]->GetCharUnique() <= 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTrade->siToPersonCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	// ������ �ŷ� �ź� ������ ���
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[toid];
	if ( pclChar->bPrivateTradeReject )
	{
		SendServerResponseMsg(0, SRVAL_PRIVATETRADE_REJECT,  0, 0, id);
		return;
	}
	


	// ���� 3 �̸������� �ŷ� �ȵ�
	if ( pclCM->CR[id]->pclCI->clIP.GetLevel() < 3 || pclCM->CR[toid]->pclCI->clIP.GetLevel() < 3 )
	{
		return;
	}

	TCHAR *CharName1 = (TCHAR*)pclCM->CR[ id ]->GetName();
	if ( CharName1 == NULL || _tcslen ( CharName1 ) < 1 )
	{
		return;
	}

	TCHAR *CharName2 = (TCHAR*)pclCM->CR[ toid ]->GetName();
	if ( CharName2 == NULL || _tcslen ( CharName2 ) < 1 )
	{
		return;
	}

	SI16 CharLevel1 = pclCM->CR[id]->pclCI->clIP.GetLevel();
	SI16 CharLevel2 = pclCM->CR[toid]->pclCI->clIP.GetLevel();

	TCHAR *AccountID1 = (TCHAR*)pclCM->CR[ id ]->pclCI->clBI.szAccountID;
	if ( AccountID1 == NULL || _tcslen( AccountID1 ) < 1 )
	{
		return;
	}

	TCHAR *AccountID2 = (TCHAR*)pclCM->CR[ toid ]->pclCI->clBI.szAccountID;
	if ( AccountID2 == NULL || _tcslen( AccountID2 ) < 1 )
	{
		return;
	}

	// �ŷ� ��嵵 �ƴϰ�, ��þƮ ��嵵 �ƴ� ��û�� ���� �����
	if ( pclPrivateTrade->siTradeMode != PRIVATETRADE_TRADE_MODE && pclPrivateTrade->siTradeMode != PRIVATETRADE_ENCHANT_MODE  )
	{
		return;
	}

	SI16 MgrIndex;
	SI16 CountIndex;	

	// �Ŵ����� ���� �Ҵ���� ���� ��� ( �ŷ��� �ʰ��ų�... ��Ÿ �����Ͱ� �� �´´ٰų� �ؼ�... )
	if ( ! pclPrivateTradeOrderMgr->Set( FromPersonID, ToPersonID, &MgrIndex, &CountIndex, pclPrivateTrade->siTradeMode ) )
	{
		return;
	}

	cltGameMsgResponse_PrivateTrade clGameMsgResponse_PrivateTrade( pclPrivateTrade->siToPersonCharUnique, MgrIndex, CountIndex, pclPrivateTrade->siTradeMode, CharLevel2, CharName2, AccountID2 );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE, sizeof( clGameMsgResponse_PrivateTrade ), (BYTE*)&clGameMsgResponse_PrivateTrade );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);


	clGameMsgResponse_PrivateTrade.siOtherCharUnique = pclCM->CR[id]->GetCharUnique();
	MStrCpy( clGameMsgResponse_PrivateTrade.strCharName, CharName1, MAX_PLAYER_NAME );
	MStrCpy( clGameMsgResponse_PrivateTrade.strAccountID, AccountID1, MAX_PLAYER_NAME );
	clGameMsgResponse_PrivateTrade.siOtherCharLevel = CharLevel1;

	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE, sizeof( clGameMsgResponse_PrivateTrade ), (BYTE*)&clGameMsgResponse_PrivateTrade );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);

	return;
}


void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_CANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_Cancel *pclPrivateTradeCancel = (cltGameMsgRequest_PrivateTrade_Cancel*) pclMsg->cData;

	// �������� �ʴ� CharUnique ���� ��������.
	if ( pclPrivateTradeCancel->siOtherCharUnique <= 0 )
	{
		return;
	}

	// ��û�� ����� CharUnique ���� �̻���.
	if ( pclCM->CR[id]->GetCharUnique() <= 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeCancel->siOtherCharUnique);
	if(toid <= 0) 
	{
		pclPrivateTradeOrderMgr->Cancel( FromPersonID, pclPrivateTradeCancel->siPrivateTradeOrderMgrIndex, pclPrivateTradeCancel->siPrivateTradeOrderCountIndex );

		cltGameMsgResponse_PrivateTrade_Cancel clGameMsgResponse_PrivateTrade_Cancel;
		cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL, sizeof( clGameMsgResponse_PrivateTrade_Cancel ), (BYTE*)&clGameMsgResponse_PrivateTrade_Cancel );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return ;
	}

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	pclPrivateTradeOrderMgr->Cancel( FromPersonID, ToPersonID, pclPrivateTradeCancel->siPrivateTradeOrderMgrIndex, pclPrivateTradeCancel->siPrivateTradeOrderCountIndex );

	cltGameMsgResponse_PrivateTrade_Cancel clGameMsgResponse_PrivateTrade_Cancel;

	cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL, sizeof( clGameMsgResponse_PrivateTrade_Cancel ), (BYTE*)&clGameMsgResponse_PrivateTrade_Cancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);


	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_AddItem *pclPrivateTradeAddItem = (cltGameMsgRequest_PrivateTrade_AddItem *) pclMsg->cData;

	// �������� �ʴ� cha r unique �� ��������.
	if ( pclPrivateTradeAddItem->siOtherCharUnique < 1 )
	{
		return;
	}

	// ��û�� ����� CharUnique ���� �̻���.
	if ( pclCM->CR[id]->GetCharUnique() <= 0 )
	{
		return;
	}

	// ���� Ȯ��
	if ( pclPrivateTradeAddItem->siAddItemNum < 1 )
	{
		return;
	}

	// ������ ��ġ Ȯ��
	if( pclPrivateTradeAddItem->siItemPos < PERSONITEM_INV0 || pclPrivateTradeAddItem->siItemPos >= MAX_ITEM_PER_PERSON )
	{
		return;
	}

	// Ʈ���̵����� ���� �ȵȴ�!
	if ( ((cltCharServer*)pclCM->CR[id])->GetNoMoveItemSwitch(pclPrivateTradeAddItem->siItemPos) != 0 )
	{
		return ;
	}

	// ���� �ŷ� �Ŵ����� ���� �Ҵ���� �ε��� ���� ��ȿ���� üũ
	if ( pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex < 1 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeAddItem->siOtherCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	/*
	// ���� �������¿��� �� �޽����� �� ���� ����...
	if ( pclPrivateTradeOrderMgr->IsAcceptStatus( FromPersonID, ToPersonID, pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex ) )
	{
		return;
	}
	*/

	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex );

	cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[pclPrivateTradeAddItem->siItemPos];

	// ������ �ִ°� ���� �� ���� �ø����� �ϸ� ����.
	if ( pclfromitem->siItemNum < pclPrivateTradeAddItem->siAddItemNum )
	{
		return;
	}

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
	if( ((cltCharServer*)pclCM->CR[id])->bPersonalShopSwitch == true && ((cltCharServer*)pclCM->CR[id])->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( ((cltCharServer*)pclCM->CR[id])->clShopData.m_siSelectedInventoryPos[i] == pclPrivateTradeAddItem->siItemPos	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( ((cltCharServer*)pclCM->CR[id])->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}

		// �ͼ����� ���λ���
		if( ((cltCharServer*)pclCM->CR[id])->clShopData.m_siSelectedSpacialInventoryPos == pclPrivateTradeAddItem->siItemPos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( ((cltCharServer*)pclCM->CR[id])->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}



	cltItem clitem1;
	clitem1.Set(pclfromitem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(&pclPrivateTradeAddItem->clItem);
	clitem2.SetItemNum(1);

	if( clitem1.IsSame(&clitem2, false) == FALSE )
	{
		return ;
	}

/*	SI32 NotUsingData;
	if ( pclItemManager->GetLimitDateItemValue( clitem1.siUnique, &NotUsingData ) )
	{
		return;
	}*/

	//cyj ������ ������ �� �Ⱓ�� �����۸� �ȵǵ��� ����
	// �Ⱓ�� �������� �ȵȴ�.
	//if ( clitem1.uiDateUseDay > 0 )
/*	if ( pclItemManager->IsItemInfoAtb(clitem1.siUnique,ITEMINFOATB_ITEMMALL) == true )
	{
		SendServerResponseMsg(0, SRVAL_NOTRADE_ITEM,  0, 0, id);
		return ;
	}*/

	//kkm ITEMINFOATB_NOTTRADE�̸� ���ΰŷ� ǰ�� ���ø����� ����
	if ( pclItemManager->IsItemInfoAtb(clitem1.siUnique,ITEMINFOATB_NOTTRADE) )
	{
		SendServerResponseMsg(0, SRVAL_NOTRADE_ITEM,  0, 0, id);
		return ;
	}

	//cyj �ͼ� �������̸� ���ΰŷ� ǰ�� ���ø����� ����
	if ( clitem1.IsBelonging(pclItemManager))
	{
		SendServerResponseMsg(0, SRVAL_NOTRADE_ITEM,  0, 0, id);
		return ;
	}

	// SJY DEBUG
	if ( clitem1.siUnique == 8150 || clitem1.siUnique == 14300 ||
		 clitem1.siUnique == 14400 || clitem1.siUnique == 14500 ) // �ݰ��� ���
	{
		return ;
	}

	// ��ø�� �Ǵ� �������� ���
	if ( clitem2.CanPile( pclItemManager ) )
	{
		clitem2.SetItemNum( pclPrivateTradeAddItem->siAddItemNum );
	}
	// ��ø�� �ȵǴ� �������� ����ε�, 2�� �̻� Add �ҷ��� ���
	else if ( pclPrivateTradeAddItem->siAddItemNum > 1 )
	{
		return;
	}

	CPrivateTradeOrderObj *pTemp =	pclPrivateTradeOrderMgr->FindTradeOrderObj( pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��þƮ ��� �� ��쿡 ���� ������ �����۸� �÷��� �ϹǷ�...
	if ( pTemp->GetSelcteMode() == PRIVATETRADE_ENCHANT_MODE )
	{
		return;

		/*
		if ( ! clitem2.CanRepair( pclItemManager ) )
		{
			return;
		}
		else
		{
			// �� ��ǰ ��Ͽ� ������ ������ �ö� �ִٸ� �ø� �� ����.
			stTradeData *pTradeData = pTemp->GetEachPersonTradeOrderInfo()->GetTradeData( FromPersonID );
			for ( SI32 i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				// ���� ����� ��쿡�� ��ǰ�� �Ѹ��� �Ѱ��� �ø� �� ����.
				if ( pTradeData->m_clItem[ i ].siUnique > 0 )
				{
					return;
				}
			}

			// ���� ��ǰ ��Ͽ� ������ ������ �ö� �ִٸ� �ø� �� ����.
			pTradeData = pTemp->GetEachPersonTradeOrderInfo()->GetTradeData( ToPersonID );
			for ( i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				// ���� ����� ��쿡�� ��ǰ�� �Ѹ��� �Ѱ��� �ø� �� ����.
				if ( pTradeData->m_clItem[ i ].siUnique > 0 )
				{
					return;
				}
			}
		}*/
	}

	// ��Ͽ� �������� �ְ�, ��Ͽ� ���� index �� �޾ƿ�
	SI16 siAddedIndex = pclPrivateTradeOrderMgr->AddItem
		(
		FromPersonID, 
		ToPersonID, 
		pclPrivateTradeAddItem->siPrivateTradeOrderMgrIndex,
		pclPrivateTradeAddItem->siPrivateTradeOrderCountIndex,
		&clitem2,
		pclPrivateTradeAddItem->siItemPos
		);

	if ( siAddedIndex == -1 )		// ������ ���� �� ���ų�, ��Ÿ ����� ������...
	{
		return;
	}

	// �� �޽����� ���� Ŭ���̾�Ʈ���� 
	// �κ��丮���� �ŷ� ��Ͽ� �ø���ŭ ������ ������ ���� ( ���������� �ִ�. )
	// �׸��� Ŭ���̾�Ʈ�� ��Ͽ� �÷ȴٰ� ��������. 
	// ������ ���� siAddedIndex ���� �־...

	cltGameMsgResponse_PrivateTrade_AddItem clGameMsgResponse_PrivateTradeAddItem( pclCM->CR[id]->GetCharUnique(), siAddedIndex, &clitem2 );
	
	cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_ADDITEM, sizeof( clGameMsgResponse_PrivateTradeAddItem ), (BYTE*)&clGameMsgResponse_PrivateTradeAddItem );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// ���� Ŭ���̾�Ʈ���� ��Ͽ� �ø� �������� �˷���.
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_DELLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_DelList *pclPrivateTradeDelList = (cltGameMsgRequest_PrivateTrade_DelList*) pclMsg->cData;

	if ( pclPrivateTradeDelList->siDelType < PRIVATETRADE_TYPE_MONEY || pclPrivateTradeDelList->siDelType >= PRIVATETRADE_TYPE_END )
	{
		return;
	}

	if ( pclPrivateTradeDelList->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeDelList->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeDelList->siOtherCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelList->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelList->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelList->siPrivateTradeOrderCountIndex );

	/*
	switch ( pclPrivateTradeDelList->siDelType )
	{	
	case PRIVATETRADE_TYPE_ITEM:
		{
			cltItem clitem1;
			
			if ( ! pclPrivateTradeOrderMgr->GetOrderIndexItem
				(
				FromPersonID, 
				ToPersonID, 
				pclPrivateTradeDelList->siParam, 
				pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, 
				pclPrivateTradeDelList->siPrivateTradeOrderCountIndex, 
				&clitem1
				) )
			{
				return;			// �� ��ġ�� �������� �������� �ʴ´�.
			}
		}
		break;	
	default:
		pclPrivateTradeOrderMgr->DelOrderListIndex
			(
			FromPersonID, 
			ToPersonID, 
			pclPrivateTradeDelList->siDelType,
			pclPrivateTradeDelList->siParam,
			pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, 
			pclPrivateTradeDelList->siPrivateTradeOrderCountIndex
		);
		return;
	}
	*/

	if ( ! pclPrivateTradeOrderMgr->DelOrderListIndex
			(
			FromPersonID, 
			ToPersonID, 
			pclPrivateTradeDelList->siDelType,
			pclPrivateTradeDelList->siParam,
			pclPrivateTradeDelList->siPrivateTradeOrderMgrIndex, 
			pclPrivateTradeDelList->siPrivateTradeOrderCountIndex
		) )
	{
		return;
	}

	// ���� �Ǿ����� �뺸�Ѵ�.
	cltGameMsgResponse_PrivateTrade_DelList clGameMsgResponse_PrivateTradeDelList( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeDelList->siDelType, pclPrivateTradeDelList->siParam );
	
	cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_DELLIST, sizeof( clGameMsgResponse_PrivateTradeDelList ), (BYTE*)&clGameMsgResponse_PrivateTradeDelList );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_DELITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_DelItem *pclPrivateTradeDelItem = (cltGameMsgRequest_PrivateTrade_DelItem *) pclMsg->cData;

	if ( pclPrivateTradeDelItem->siDelIndex < 0 )
	{
		return;
	}
	if ( pclPrivateTradeDelItem->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeDelItem->siOtherCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	/*
	// ���� �������¿��� �� �޽����� �� ���� ����...
	if ( pclPrivateTradeOrderMgr->IsAcceptStatus( FromPersonID, ToPersonID, pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex ) )
	{
		return;
	}
	*/

	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex );
	
	
	cltItem clitem1;
	

	if ( ! pclPrivateTradeOrderMgr->GetOrderIndexItem
		(
		FromPersonID, 
		ToPersonID, 
		pclPrivateTradeDelItem->siDelIndex, 
		pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, 
		pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex, 
		&clitem1
		) )
	{
		return;			// �� ��ġ�� �������� �������� �ʴ´�.
	}

	cltItem clitem2;
	clitem2.Set(&pclPrivateTradeDelItem->clItem);

	// �ö� ������ ���ڰ� Ʋ����.
	if ( clitem1.siItemNum != clitem2.siItemNum )
	{
		return;
	}
	
	clitem1.SetItemNum(1);
	clitem2.SetItemNum(1);

	if( clitem1.IsSame(&clitem2, false) == FALSE )
	{
		return ;
	}

	// ����Ʈ���� index���� �����Ѵ�.
	if ( ! pclPrivateTradeOrderMgr->DelOrderIndexItem
		(
		FromPersonID, 
		ToPersonID, 
		pclPrivateTradeDelItem->siDelIndex, 
		pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, 
		pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex
		) )
	{
		return;
	}

	// ���� �Ǿ����� �뺸�Ѵ�.
	cltGameMsgResponse_PrivateTrade_DelItem clGameMsgResponse_PrivateTradeDelItem( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeDelItem->siDelIndex );
	
	cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_DELITEM, sizeof( clGameMsgResponse_PrivateTradeDelItem ), (BYTE*)&clGameMsgResponse_PrivateTradeDelItem );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDPRICE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PrivateTrade_AddPrice *pclPrivateTradeAddPrice = (cltGameMsgRequest_PrivateTrade_AddPrice * )pclMsg->cData;

	if ( pclPrivateTradeAddPrice->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeAddPrice->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeAddPrice->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}

	if ( pclPrivateTradeAddPrice->siPrice < 1 || pclPrivateTradeAddPrice->siPrice > pclClient->GetGlobalValue("GV_PrivateTradeMoneyLimit") )
	{
		return;
	}

	GMONEY FromOriPersonMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();

	if ( FromOriPersonMoney < pclPrivateTradeAddPrice->siPrice )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeAddPrice->siOtherCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;

	/*
	// ���� �������¿��� �� �޽����� �� ���� ����...
	if ( pclPrivateTradeOrderMgr->IsAcceptStatus( FromPersonID, ToPersonID, pclPrivateTradeDelItem->siPrivateTradeOrderMgrIndex, pclPrivateTradeDelItem->siPrivateTradeOrderCountIndex ) )
	{
		return;
	}
	*/

	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeAddPrice->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddPrice->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeAddPrice->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddPrice->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeAddPrice->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddPrice->siPrivateTradeOrderCountIndex );

	// �� �Է��� 1���� ����. ������ â�� ���� �Ŀ� ����
	if ( ! pclPrivateTradeOrderMgr->PrivateTradeSetPrice( FromPersonID, ToPersonID, pclPrivateTradeAddPrice->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddPrice->siPrivateTradeOrderCountIndex, pclPrivateTradeAddPrice->siPrice ) )
	{
		return;
	}
	/*
	clGameMsgResponse_PrivateTrade.siOtherCharUnique = pclPrivateTrade->siToPersonCharUnique;
	
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE, sizeof( clGameMsgResponse_PrivateTrade ), (BYTE*)&clGameMsgResponse_PrivateTrade );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	
	clGameMsgResponse_PrivateTrade.siOtherCharUnique = pclCM->CR[id]->GetCharUnique();

	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE, sizeof( clGameMsgResponse_PrivateTrade ), (BYTE*)&clGameMsgResponse_PrivateTrade );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);
	*/

	cltGameMsgResponse_PrivateTrade_AddPrice clPrivateTradeAddPrice1(  pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddPrice->siPrice );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_ADDPRICE, sizeof( clPrivateTradeAddPrice1 ), (BYTE*)&clPrivateTradeAddPrice1 );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	cltGameMsgResponse_PrivateTrade_AddPrice clPrivateTradeAddPrice2( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddPrice->siPrice );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_ADDPRICE, sizeof( clPrivateTradeAddPrice2 ), (BYTE*)&clPrivateTradeAddPrice2 );	
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDSTOCK( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PrivateTrade_AddStock *pclPrivateTradeAddStock = (cltGameMsgRequest_PrivateTrade_AddStock * )pclMsg->cData;
	
	if ( pclPrivateTradeAddStock->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}

	if ( pclPrivateTradeAddStock->siVillageUnique < 1 || pclVillageManager->pclVillageInfo[pclPrivateTradeAddStock->siVillageUnique] == NULL )
	{
		return;
	}

	if ( pclPrivateTradeAddStock->siStockNum < 1 || pclPrivateTradeAddStock->siStockNum > pclClient->GetGlobalValue("GV_PrivateTradeStockLimit") )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0 ) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeAddStock->siOtherCharUnique);
	if( toid <= 0 ) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if( ToPersonID <= 0 ) return ;
	
	// ���� ��� �� ��쿡 ���� ������ �����۸� �÷��� �ϹǷ�...
	CPrivateTradeOrderObj *pTemp =	pclPrivateTradeOrderMgr->FindTradeOrderObj( pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��þƮ ��忡���� �ֽ� �ŷ� �ȵ�.
	if ( pTemp->GetSelcteMode() == PRIVATETRADE_ENCHANT_MODE )
	{
		return;
	}

	// �ֽ� ������ �̻��� �ŷ��ҷ��� ��.
	if ( pclPrivateTradeAddStock->siStockNum > pclCM->CR[id]->pclCI->clStock.clInfo.GetStockAmount( pclPrivateTradeAddStock->siVillageUnique ) )
	{
		return;
	}

//#if defined(_CITYHALL_BANKRUPTCY)
	// �ش� ������ �Ļ� ������ ���� �ֽ� ���� �ֹ��� �ø� �� ����.
	SI32 targetVillage = pclPrivateTradeAddStock->siVillageUnique;
	cltStrInfo *pTargetStrInfo = GetStrInfo( targetVillage, RANKTYPE_CITYHALL );
	if(pTargetStrInfo == NULL)return ;

	if( pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT )
	{
		// �ֽ� ���� ��� ������ �Ļ�����Դϴ�.. => ���� �ֹ� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( targetVillage,  pTargetStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}
//#endif


	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex );

	
	if ( ! pclPrivateTradeOrderMgr->SetStock( FromPersonID, ToPersonID, pclPrivateTradeAddStock->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddStock->siPrivateTradeOrderCountIndex, pclPrivateTradeAddStock->siVillageUnique, pclPrivateTradeAddStock->siStockNum ) )
	{
		return;
	}
	
	cltGameMsgResponse_PrivateTrade_AddStock clPrivateTradeAddStock1(  pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddStock->siVillageUnique, pclPrivateTradeAddStock->siStockNum );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_ADDSTOCK, sizeof( clPrivateTradeAddStock1 ), (BYTE*)&clPrivateTradeAddStock1 );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	cltGameMsgResponse_PrivateTrade_AddStock clPrivateTradeAddStock2( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddStock->siVillageUnique, pclPrivateTradeAddStock->siStockNum );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_ADDSTOCK, sizeof( clPrivateTradeAddStock2 ), (BYTE*)&clPrivateTradeAddStock2 );	
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);	

	return;
}

// ���� �ŷ�
void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDHOUSEUNIT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PrivateTrade_AddHouseUnit *pclPrivateTradeAddHouseUnit = (cltGameMsgRequest_PrivateTrade_AddHouseUnit *)pclMsg->cData;

	if ( pclPrivateTradeAddHouseUnit->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}
	
	// ���� ��� �⺻ ���� ������ ������Ű�� ���ϸ� ����. 
	if( pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE)
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0 ) return;


	//-------------------------------------------------------------
	// �� ������ ������ �´��� Ȯ�� ��.
	if( pclHouseManager->IsHouseHost( FromPersonID, pclPrivateTradeAddHouseUnit->siHouseVillageUnique, pclPrivateTradeAddHouseUnit->siHouseUnitSlot ) == false )
	{
		return;
	}

	cltHouse* pclhouse = (cltHouse*)pclHouseManager->pclStruct[ pclPrivateTradeAddHouseUnit->siHouseVillageUnique ];

	cltRealEstateUnit* pRealEstateUnit = NULL;
	if( pclhouse != NULL )
	{
		pRealEstateUnit = pclCM->CR[id]->pclCI->clRealEstate.Find( pclPrivateTradeAddHouseUnit->siHouseVillageUnique, REALESTATE_TYPE_HOUSE,pclPrivateTradeAddHouseUnit->siHouseUnitSlot );

		if ( pRealEstateUnit == NULL )
		{
			return;
		}
	}
				
	//-------------------------------------------------------------
	
	SI32 toid = pclCM->GetIDFromCharUnique( pclPrivateTradeAddHouseUnit->siOtherCharUnique );
	if( toid <= 0 ) return;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if( ToPersonID <= 0 ) return;
	

	// ���� ��� �⺻ ���� ������ ������Ű�� ���ϸ� ����. 
	if( pclCM->CR[toid]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE)
	{
		SendServerResponseMsg(0, SRVAL_PRIVATETRADE_HOUSEUNIT_LEVEL_LIMIT,  0, 0, id);
		return;
	}

	// ���� ��� �� ��쿡 ���� ������ �����۸� �÷��� �ϹǷ�...
	CPrivateTradeOrderObj *pTemp =	pclPrivateTradeOrderMgr->FindTradeOrderObj( pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��þƮ ��忡���� ���� �ŷ� �ȵ�.
	if ( pTemp->GetSelcteMode() == PRIVATETRADE_ENCHANT_MODE )
	{
		return;
	}


	// ������ �ŷ� �Ұ����� ���� �ִ��� üũ
	cltHouseUnitStorageInfo *  pclHouseUnit = pclHouseManager->GetStgPointer(pclPrivateTradeAddHouseUnit->siHouseVillageUnique, pclPrivateTradeAddHouseUnit->siHouseUnitSlot);
	if( pclHouseUnit == NULL ) return;

	for ( SI16 i = 0; i < MAX_HOUSEUNIT_HORSENUMBER ; i ++ )
	{

		//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.   //KHY - 0911 - ȣ���� �߰�.
		// PCK : ��Ÿ�߰� (08.03.06)
		// PCK : �̺�Ʈ�� ȣ���� �߰� (08.04.01)
		// PCK : �ڳ��� �߰� (08.06.12)
		// PCK : ��ȣ �߰� (08.08.14)
		// PCK : ������� �߰� (08.09.02)
		// PCK : ����ġ �߰� (08.12.10)
		// ü��� �鸶 : �ռ���-2009.03.17
		// PCK : ������Ʈ �߰�(09.07.30)
		switch ( pclHouseUnit->clHorse[i].siHorseUnique )
		{
			case HORSEUNIQUE_WOLF:
			case HORSEUNIQUE_FOAL:
			case HORSEUNIQUE_TIGER:
			case HORSEUNIQUE_CAMEL:
			case HORSEUNIQUE_TIGER2:
			case HORSEUNIQUE_ELEPHANT:
			case HORSEUNIQUE_WHITETIGER:
			case HORSEUNIQUE_MOTORCYCLE:
			case HORSEUNIQUE_FIREHATCH:
			case HORSEUNIQUE_WHITE_TEST:
			case HORSEUNIQUE_BAPHOMET:
			case HORSEUNIQUE_GRAYWOLF:
			case HORSEUNIQUE_SASURI:
				{
					SendServerResponseMsg(0, SRVAL_PRIVATETRADe_HORSE_CANNOTTRADE,  0, 0, id);
					return;
				}
				break;
		}	// switch ( pclHouseUnit->clHorse[i].siHorseUnique ) ����
	}	// for ( SI16 i = 0; i < MAX_HOUSEUNIT_HORSENUMBER ; i ++ ) ����


	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex );

	
	if ( ! pclPrivateTradeOrderMgr->SetHouseUnit( FromPersonID, ToPersonID, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHouseUnit->siPrivateTradeOrderCountIndex, pclPrivateTradeAddHouseUnit->siHouseVillageUnique, pclPrivateTradeAddHouseUnit->siHouseUnitSlot ) )
	{
		return;
	}

	cltGameMsgResponse_PrivateTrade_AddHouseUnit clPrivateTradeAddHouseUnit1( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddHouseUnit->siHouseVillageUnique, pclPrivateTradeAddHouseUnit->siHouseUnitSlot, &pRealEstateUnit->clContract );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_ADDHOUSEUNIT, sizeof( clPrivateTradeAddHouseUnit1 ), (BYTE*)&clPrivateTradeAddHouseUnit1 );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	cltGameMsgResponse_PrivateTrade_AddHouseUnit clPrivateTradeAddHouseUnit2( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddHouseUnit->siHouseVillageUnique, pclPrivateTradeAddHouseUnit->siHouseUnitSlot, &pRealEstateUnit->clContract );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_ADDHOUSEUNIT, sizeof( clPrivateTradeAddHouseUnit2 ), (BYTE*)&clPrivateTradeAddHouseUnit2 );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);

	return;
}

// �� �ŷ�
void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_ADDHORSE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PrivateTrade_AddHorse *pclPrivateTradeAddHorse = (cltGameMsgRequest_PrivateTrade_AddHorse * )pclMsg->cData;
	
	if ( pclPrivateTradeAddHorse->siOtherCharUnique < 1 )
	{
		return;
	}

	if ( pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex < 1 || pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex < 0 )
	{
		return;
	}

	if ( pclPrivateTradeAddHorse->siHorseIndex < 0 || pclPrivateTradeAddHorse->siHorseIndex >= MAX_HORSE_PER_PERSON )
	{
		return;
	}
	
	// ���� �ִ� ���� �ִ��� ������ üũ
	cltHorse *pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if ( pclHorse == NULL )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clHorseInfo.siCurrentShowHorse != pclPrivateTradeAddHorse->siHorseIndex )
	{
		return;
	}

	// �ŷ� �Ұ����� ���̸� �ŷ� ���Ѵٰ� �˷��� //KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.  //KHY - 0911 - ȣ���� �߰�.
	// PCK : ��Ÿ�߰� (08.03.06)
	// PCK : �̺�Ʈ�� ȣ���� �߰� (08.04.01)
	// PCK : �ڳ��� �߰� (08.06.12)
	// PCK : ��ȣ �߰� (08.08.14)
	// PCK : ������� �߰� (08.09.02)
	// PCK : ����ġ �߰� (08.12.10)
	// ü��� �鸶 : �ռ���-2009.03.17
	// PCK : ������Ʈ �߰�(09.07.30)
	switch ( pclHorse->siHorseUnique )
	{
		case HORSEUNIQUE_WOLF:
		case HORSEUNIQUE_FOAL:
		case HORSEUNIQUE_TIGER:
		case HORSEUNIQUE_CAMEL:
		case HORSEUNIQUE_TIGER2:
		case HORSEUNIQUE_ELEPHANT:
		case HORSEUNIQUE_WHITETIGER:
		case HORSEUNIQUE_MOTORCYCLE:
		case HORSEUNIQUE_FIREHATCH:
		case HORSEUNIQUE_WHITE_TEST:
		case HORSEUNIQUE_BAPHOMET:
		case HORSEUNIQUE_GRAYWOLF:
		case HORSEUNIQUE_SASURI:
			{
				SendServerResponseMsg(0, SRVAL_PRIVATETRADe_HORSE_CANNOTTRADE,  0, 0, id);
				return;
			}
			break;
	}	// switch ( pclHorse->siHorseUnique ) ����


	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0 ) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeAddHorse->siOtherCharUnique);
	if( toid <= 0 ) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if( ToPersonID <= 0 ) return ;


	// �� ����� ������ MIN_LEVEL_FOR_HORSE �̻��̾�߸��� �ŷ��� ������
	if ( pclCM->CR[id]->pclCI->clIP.GetLevel() < MIN_LEVEL_FOR_HORSE || pclCM->CR[toid]->pclCI->clIP.GetLevel() < MIN_LEVEL_FOR_HORSE )
	{
		return;
	}
	
	// ���� ��� �� ��쿡 ���� ������ �����۸� �÷��� �ϹǷ�...
	CPrivateTradeOrderObj *pTemp =	pclPrivateTradeOrderMgr->FindTradeOrderObj( pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��þƮ ��忡���� �� �ŷ� �ȵ�.
	if ( pTemp->GetSelcteMode() == PRIVATETRADE_ENCHANT_MODE )
	{
		return;
	}

	cltGameMsgResponse_PrivateTrade_OtherCancel clPrivateTrade_OtherCancel(1);

	cltMsg clMsg3( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPrivateTrade_OtherCancel ), (BYTE*)&clPrivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg3);

	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel(1);

	cltMsg clMsg4( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex );

	if ( ! pclPrivateTradeOrderMgr->SetHorse( FromPersonID, ToPersonID, pclPrivateTradeAddHorse->siPrivateTradeOrderMgrIndex, pclPrivateTradeAddHorse->siPrivateTradeOrderCountIndex, pclPrivateTradeAddHorse->siHorseIndex, pclHorse ) )
	{
		return;
	}

	cltGameMsgResponse_PrivateTrade_AddHorse clPrivateTradeAddHorse1(  pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddHorse->siHorseIndex, pclHorse );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_ADDHORSE, sizeof( clPrivateTradeAddHorse1 ), (BYTE*)&clPrivateTradeAddHorse1 );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	cltGameMsgResponse_PrivateTrade_AddHorse clPrivateTradeAddHorse2( pclCM->CR[id]->GetCharUnique(), pclPrivateTradeAddHorse->siHorseIndex, pclHorse );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_ADDHORSE, sizeof( clPrivateTradeAddHorse2 ), (BYTE*)&clPrivateTradeAddHorse2 );	
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);
	
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_MYACCEPT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_MyAccept *pclPrivateTradeMyAccept = (cltGameMsgRequest_PrivateTrade_MyAccept *) pclMsg->cData;
	
	if ( pclPrivateTradeMyAccept->siOtherCharUnique < 1 )
	{
		return;
	}
	
	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1 )  return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeMyAccept->siOtherCharUnique);
	if( toid < 1 || pclCM->IsValidID(toid) == FALSE )
	{
		return;
	}

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID < 1) return ;

	if ( pclCM->CR[id]->GetCharUnique() < 1 )
	{
		return;
	}

	///////////////////////////////////////////////////////////////
	// 60 ������(3��)���� �� ����� ��ΰ� Accept �Ѵٸ� �� �� �ŷ� ��ҽ��� ����.
	// ���� 60 �����ӳ��� ������ �Ͼ�� �����Ƿ�....
	if ( ! pclPrivateTradeOrderMgr->IsAvailableAccept( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex ) )
	{
		pclPrivateTradeOrderMgr->Cancel( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );

		cltGameMsgResponse_PrivateTrade_Cancel clGameMsgResponse_PrivateTrade_Cancel;

		cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL, sizeof( clGameMsgResponse_PrivateTrade_Cancel ), (BYTE*)&clGameMsgResponse_PrivateTrade_Cancel );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

		return;
	}
	///////////////////////////////////////////////////////////////

	if ( ! pclPrivateTradeOrderMgr->IsSameAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, pclPrivateTradeMyAccept->siAcceptCounter ) )
	{
		return;
	}	

//#if defined(_CITYHALL_BANKRUPTCY)
	// �ش� ������ �Ļ� ������ ���� �ֽ� �ŸŸ� �� �� ����.

	SI32 tmpPerson1StockVillageUnique = 0;
	SI32 tmpPerson1StockNum = 0;

	SI32 tmpPerson2StockVillageUnique = 0;
	SI32 tmpPerson2StockNum = 0;

	if ( ! pclPrivateTradeOrderMgr->GetStockInfo( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &tmpPerson1StockVillageUnique, &tmpPerson1StockNum, &tmpPerson2StockVillageUnique, &tmpPerson2StockNum ) )
	{
		pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_STOCK_INFO_DIFFERENT );
		return;
	}

	// [����] �ʺ��� ���� : ���ΰ� �ʺ��� ���� �ֽ� �ŷ� ���ϰ� ����
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( (Const_Beginner_Village == tmpPerson1StockVillageUnique) || (Const_Beginner_Village == tmpPerson2StockVillageUnique) )
		{
			pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_STOCK_INFO_DIFFERENT );
			return;
		}
	}

	// tmpPerson2StockVillageUnique : ����� �ֽ� ���� ��ȣ
	SI32 targetVillage = tmpPerson2StockVillageUnique;
	cltStrInfo *pTargetStrInfo = GetStrInfo( targetVillage, RANKTYPE_CITYHALL );

	if(pTargetStrInfo != NULL)
	{
		if( pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT )
		{
			// �ֽ� ���� ��� ������ �Ļ�����Դϴ�.. => ���� �ֹ� ���� => �˸�
			cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( targetVillage,  pTargetStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE );
			cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			return;
		}
	}
//#endif

	
	cltGameMsgResponse_PrivateTrade_MyAccept clGameMsgResponse_PrivateTrade_MyAccept( 1 );
	
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_MYACCEPT, sizeof( clGameMsgResponse_PrivateTrade_MyAccept ), (BYTE*)&clGameMsgResponse_PrivateTrade_MyAccept );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
	

	cltGameMsgResponse_PrivateTrade_OtherAccept clPrivateTrade_OtherAccept(1);
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERACCEPT, sizeof( clPrivateTrade_OtherAccept ), (BYTE*)&clPrivateTrade_OtherAccept );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2); 

	pclPrivateTradeOrderMgr->SetMyAccept( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );

	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );
	

	// ��� �����ߴ� �����
	if ( pclPrivateTradeOrderMgr->IsAllAccept( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex ) )
	{
		CPrivateTradeOrderObj *pTemp =	pclPrivateTradeOrderMgr->FindTradeOrderObj( pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );

		if ( pTemp == NULL )
		{
			return;
		}

		if ( pTemp->GetSelcteMode() == PRIVATETRADE_TRADE_MODE )
		{	
			// ���濡�� �ٸ�ŭ �κ��丮�� �� ������ �ִ��� üũ
			cltItem clPerson1ItemList[ MAX_PRIVATETRADEORDER_ITEM_NUM ]; // 1�� ����
			memset( clPerson1ItemList, 0, sizeof( cltItem ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
			
			cltItem clPerson2ItemList[ MAX_PRIVATETRADEORDER_ITEM_NUM ]; // 2�� ����
			memset( clPerson2ItemList, 0, sizeof( cltItem ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

			SI16	siPerson1ItemInventoryPosList[  MAX_PRIVATETRADEORDER_ITEM_NUM ]; // 1�� ����
			memset( siPerson1ItemInventoryPosList, 0, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

			SI16	siPerson2ItemInventoryPosList[  MAX_PRIVATETRADEORDER_ITEM_NUM ]; // 1�� ����
			memset( siPerson2ItemInventoryPosList, 0, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

			if ( ! pclPrivateTradeOrderMgr->GetOrderItemList( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, clPerson1ItemList, clPerson2ItemList, siPerson1ItemInventoryPosList, siPerson2ItemInventoryPosList ) )
			{
				return;
			}

			// ������ ���� : MAX_PRIVATETRADEORDER_ITEM_NUM
			SI16 Person2ItemPos[MAX_PRIVATETRADEORDER_ITEM_NUM];
			memset( Person2ItemPos, 0, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

			if(pclCM->CR[toid]->pclCI->clCharItem.CanInputItemList(pclItemManager, clPerson1ItemList, MAX_PRIVATETRADEORDER_ITEM_NUM, Person2ItemPos) == true)
			{
			}
			else
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_PERSON_INVENTORY_FULL );
				return;			// �κ��丮�� �߰� �ȵ�.
			}

			bool bPerson2PileSwitch[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
			memset( bPerson2PileSwitch, 0, sizeof( bool ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
			
			for ( SI32 k = 0; k < MAX_PRIVATETRADEORDER_ITEM_NUM; ++k )//��ø�Ǵ� ������ Ȯ��.
			{
				if ( clPerson1ItemList[ k ].CanPile( pclItemManager ) )
				{
					bPerson2PileSwitch[ k ] = true;
				}
				else
				{
					bPerson2PileSwitch[ k ] = false;
				}
			}
			

			SI16 Person1ItemPos[MAX_PRIVATETRADEORDER_ITEM_NUM];
			memset( Person1ItemPos, 0, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

			if(pclCM->CR[id]->pclCI->clCharItem.CanInputItemList(pclItemManager, clPerson2ItemList, MAX_PRIVATETRADEORDER_ITEM_NUM, Person1ItemPos) == true)
			{
			}
			else
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_PERSON_INVENTORY_FULL );
				return;			// �κ��丮�� �߰� �ȵ�.
			}

			bool bPerson1PileSwitch[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
			memset( bPerson1PileSwitch, 0, sizeof( bool ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
			
			for ( int k = 0; k < MAX_PRIVATETRADEORDER_ITEM_NUM; ++k )
			{
				if ( clPerson2ItemList[ k ].CanPile( pclItemManager ) )
				{
					bPerson1PileSwitch[ k ] = true;
				}
				else
				{
					bPerson1PileSwitch[ k ] = false;
				}
			}


			//////////////////////////////////////////////////////////////////////////
			// �ֽ� �ŷ� Ȯ��
			// �ֽ��� �ŷ� �Ǵ� ���� ���� �ƴ��� �ٽ� �ѹ� Ȯ�� ( Ȥ�ó� �ŷ� �߿� �������� �Ȱų� �ȷ��� ���� �����Ƿ�... )
			if ( ! pclPrivateTradeOrderMgr->IsAvailableStock( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, id, toid ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_STOCK_INFO_DIFFERENT );
				return;
			}

			SI32 Person1StockVillageUnique = 0;
			SI32 Person1StockNum = 0;

			SI32 Person2StockVillageUnique = 0;
			SI32 Person2StockNum = 0;

			if ( ! pclPrivateTradeOrderMgr->GetStockInfo( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &Person1StockVillageUnique, &Person1StockNum, &Person2StockVillageUnique, &Person2StockNum ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_STOCK_INFO_DIFFERENT );
				return;
			}
			//////////////////////////////////////////////////////////////////////////


			//////////////////////////////////////////////////////////////////////////
			// ���� �ŷ� Ȯ��
			SI32 HouseVillageUnique1 = 0;
			SI32 HouseUnitSlot1 = 0;

			SI32 HouseVillageUnique2 = 0;
			SI32 HouseUnitSlot2 = 0;

			if ( ! pclPrivateTradeOrderMgr->GetHouseUnitInfo( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &HouseVillageUnique1, &HouseUnitSlot1,  &HouseVillageUnique2, &HouseUnitSlot2 ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HOUSEUNIT_INFO_DIFFERENT );
				return;
			}

			if ( HouseVillageUnique1 > 0 )
			{
				//-------------------------------------------------------------
				// �� ������ ������ �´��� �ٽ� Ȯ�� ��.
				if( pclHouseManager->IsHouseHost( FromPersonID, HouseVillageUnique1, HouseUnitSlot1 ) == false )
				{
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HOUSEUNIT_INFO_DIFFERENT );
					return;
				}
				//-------------------------------------------------------------
			}

			if ( HouseVillageUnique2 > 0 )
			{
				//-------------------------------------------------------------
				// �� ������ ������ �´��� �ٽ� Ȯ�� ��.
				if( pclHouseManager->IsHouseHost( ToPersonID, HouseVillageUnique2, HouseUnitSlot2 ) == false )
				{
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HOUSEUNIT_INFO_DIFFERENT );
					return;
				}
				//-------------------------------------------------------------
			}
			//////////////////////////////////////////////////////////////////////////
			


			//////////////////////////////////////////////////////////////////////////			
			// �� �ŷ� Ȯ��
			// ���� �ŷ� �Ǵ� ���� ���� �ƴ��� �ٽ� �ѹ� Ȯ��( Ȥ�ó� �߰��� ���� �� ���� ����� ��찡 ���� �� �����Ƿ�.. )
			SI16 siPerson1HorseIndex = -1;
			SI16 siPerson2HorseIndex = -1;

			SI16 siEmpty1HorseIndex = -1;
			SI16 siEmpty2HorseIndex = -1;
			
			
			if ( ! pclPrivateTradeOrderMgr->GetHorseInfo( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &siPerson1HorseIndex, &siPerson2HorseIndex ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_INFO_DIFFERENT );
				return;
			}

			if ( ! pclPrivateTradeOrderMgr->IsAvailableHorse( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, id, toid ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_INFO_DIFFERENT );
				return;
			}

			if ( siPerson1HorseIndex != -1 )
			{
				// FromPersonID ( id ) �� �� �κ��� ��� �ִ��� üũ
				// �� �κ��丮�� �������� �ִ��� Ȯ��				
				if ( pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() == true )
				{
					// �� �κ��� ��� ���� �����Ƿ�, �ŷ� �Ҽ� ���ٴ� ���� �޽��� �����鼭 �ŷ� ��� ��Ŵ
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_INVENTORY_NOTEMPTY );
					return;
				}
				
				// ������ ���� ���� �� �ִ��� üũ
				siEmpty2HorseIndex = pclCM->CR[toid]->pclCI->clHorseInfo.FindEmptyHorseIndex();
				if ( siEmpty2HorseIndex < 0 )
				{
					// ������ �� �߰� �Ұ�
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_NOTEMPTY );
					return;
				}
			}

			if ( siPerson2HorseIndex != -1 )
			{
				// ToPersonID ( toid )�� �� �κ��� ��� �ִ��� üũ
				if ( pclCM->CR[toid]->pclCI->clCharItem.IsHorseHaveItem() == true )
				{
					// �� �κ��� ��� ���� �����Ƿ�, �ŷ� �Ҽ� ���ٴ� ���� �޽��� �����鼭 �ŷ� ��� ��Ŵ
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_INVENTORY_NOTEMPTY );
					return;
				}

				// ������ ���� ���� �� �ִ��� üũ
				siEmpty1HorseIndex = pclCM->CR[id]->pclCI->clHorseInfo.FindEmptyHorseIndex();
				if ( siEmpty1HorseIndex < 0 )
				{
					// ������ �� �߰� �Ұ�
					pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_HORSE_NOTEMPTY );
					return;
				}
			}

			if ( siPerson1HorseIndex != -1 && siPerson2HorseIndex != -1 )
			{
				cltHorse *pPerson1Horse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
				if ( pPerson1Horse == NULL )
				{
					return;
				}

				cltHorse *pPerson2Horse = pclCM->CR[toid]->pclCI->clHorseInfo.GetCurrentShowHorse();
				if ( pPerson2Horse == NULL )
				{
					return;
				}

				if ( pPerson1Horse->szName == NULL || pPerson2Horse->szName == NULL )
				{
					return;
				}
				
				if ( _tcscmp( pPerson1Horse->szName, pPerson2Horse->szName ) == 0 )
				{
					// �̸��� ���ٸ� �ŷ��� ������ ���� ���� ����
					pclPrivateTradeOrderMgr->Cancel( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );
					
					cltGameMsgResponse_PrivateTrade_Cancel clGameMsgResponse_PrivateTrade_Cancel;
					cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL, sizeof( clGameMsgResponse_PrivateTrade_Cancel ), (BYTE*)&clGameMsgResponse_PrivateTrade_Cancel );
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

					SendServerResponseMsg(0, SRVAL_PRIVATETRADE_HORSE_NAME_SAME,  0, 0, id);
					SendServerResponseMsg(0, SRVAL_PRIVATETRADE_HORSE_NAME_SAME,  0, 0, toid);
					
					return;
				}
			}
			//////////////////////////////////////////////////////////////////////////

			
			// ���� ���� �شٸ� �ִ� �� �̻� ���� ������ �ִ���...
			GMONEY Person1Money = pclCM->CR[id]->pclCI->clIP.GetMoney();
			GMONEY Person2Money = pclCM->CR[toid]->pclCI->clIP.GetMoney();

			if ( ! pclPrivateTradeOrderMgr->IsAvailableMoney( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, Person1Money, Person2Money ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_MONEY_INSUFFICIENCY );				
				return;		// ���� ���ڶ�.
			}

			GMONEY siTradePerson1Money = pclPrivateTradeOrderMgr->GetPersonMoney( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );
			GMONEY siTradePerson2Money = pclPrivateTradeOrderMgr->GetPersonMoney( ToPersonID, FromPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );

			// �������� ������ üũ
			for ( SI32 i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				cltItem clItem;
				
				// i ��° ��ġ�� �������� �ִ���...
				if ( pclPrivateTradeOrderMgr->GetOrderIndexItem( FromPersonID, ToPersonID, i, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &clItem ) )
				{
					SI32 siInventoryPos = pclPrivateTradeOrderMgr->GetOrderIndexItemInventoryPos( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, i );

					if ( siInventoryPos < PERSONITEM_INV0 )
					{
						return;
					}

					cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ siInventoryPos ];

					if ( ! clItem.IsSame( pclfromitem, false ) )			// �������� ��ġ���� ����.
					{
						pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_ITEM_INFO_DIFFERENT );
						return;
					}
				}
			}

			for ( int i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				cltItem clItem;
				
				// i ��° ��ġ�� �������� �ִ���...
				if ( pclPrivateTradeOrderMgr->GetOrderIndexItem( ToPersonID, FromPersonID, i, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &clItem ) )
				{
					SI32 siInventoryPos = pclPrivateTradeOrderMgr->GetOrderIndexItemInventoryPos( ToPersonID, FromPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, i );

					if ( siInventoryPos < PERSONITEM_INV0 )
					{						
						return;
					}

					cltItem* pclfromitem = &pclCM->CR[toid]->pclCI->clCharItem.clItem[ siInventoryPos ];

					if ( ! clItem.IsSame( pclfromitem, false ) )			// �������� ��ġ���� ����.
					{
						pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_ITEM_INFO_DIFFERENT );
						return;
					}
				}
			}
			
			// �ŷ� �ֹ��� ����� ������ ����� ó���Ѵ�. 
			((cltCharServer*)pclCM->CR[id])->ItemUseReserveAction();
			((cltCharServer*)pclCM->CR[toid])->ItemUseReserveAction();

			//---------------------------------------------
			// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
			//---------------------------------------------
			((cltCharServer*)pclCM->CR[id])->BulletUseReserveAction();
			((cltCharServer*)pclCM->CR[toid])->BulletUseReserveAction();

			// DB �� �ŷ� ��û
			sDBRequest_PrivateTrade clMsg
				(
				FromPersonID, 
				pclCM->CR[id]->GetCharUnique(),
				siTradePerson1Money,
				clPerson1ItemList,
				siPerson1ItemInventoryPosList,
				Person2ItemPos,
				bPerson2PileSwitch,
				Person1StockVillageUnique,
				Person1StockNum,
				HouseVillageUnique1,
				HouseUnitSlot1,
				siPerson1HorseIndex,
				siEmpty1HorseIndex,

				ToPersonID, 
				pclCM->CR[toid]->GetCharUnique(),
				siTradePerson2Money,
				clPerson2ItemList,
				siPerson2ItemInventoryPosList,
				Person1ItemPos,
				bPerson1PileSwitch,
				Person2StockVillageUnique,
				Person2StockNum,
				HouseVillageUnique2,
				HouseUnitSlot2,
				siPerson2HorseIndex,
				siEmpty2HorseIndex
				);
			
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
		else
		{
			// ���� ���� �شٸ� �ִ� �� �̻� ���� ������ �ִ���...
			GMONEY Person1Money = pclCM->CR[id]->pclCI->clIP.GetMoney();
			GMONEY Person2Money = pclCM->CR[toid]->pclCI->clIP.GetMoney();

			if ( ! pclPrivateTradeOrderMgr->IsAvailableMoney( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, Person1Money, Person2Money ) )
			{
				pclPrivateTradeOrderMgr->PrivateTradeCancel( FromPersonID, ToPersonID, id, toid, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, SRVAL_PRIVATETRADE_MONEY_INSUFFICIENCY );
				return;		// ���� ���ڶ�.
			}

			GMONEY siTradePerson1Money = pclPrivateTradeOrderMgr->GetPersonMoney( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );
			GMONEY siTradePerson2Money = pclPrivateTradeOrderMgr->GetPersonMoney( ToPersonID, FromPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex );

			SI16 ItemCount = 0;
			SI32 RepairCharUnique = 0;		// �����ҷ��� ����� CharUnique
			SI32 MyCharUnique = 0;			// ������ �ñ���� ����� CharUnique;
			SI32 RepairItemInventoryPos = 0;

			GMONEY RepairPrice = 0;

			cltItem clRepairItem;
			clRepairItem.Init();
			
			// �������� ������ üũ
			for ( SI32 i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				cltItem clItem;
				
				// i ��° ��ġ�� �������� �ִ���...
				if ( pclPrivateTradeOrderMgr->GetOrderIndexItem( FromPersonID, ToPersonID, i, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &clItem ) )
				{
					SI32 siInventoryPos = pclPrivateTradeOrderMgr->GetOrderIndexItemInventoryPos( FromPersonID, ToPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, i );

					if ( siInventoryPos < PERSONITEM_INV0 )
					{
						return;
					}

					cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ siInventoryPos ];

					if ( ! clItem.IsSame( pclfromitem, false ) )			// �������� ��ġ���� ����.
					{
						return;
					}

					if ( ! clItem.CanRepair( pclItemManager ) )
					{
						return;
					}
					
					++ItemCount;

					// ���� ��忡���� �ŷ� ��ǰ�� 1���� �����Ƿ�...
					if ( ItemCount > 1 )
					{
						return;
					}

					RepairItemInventoryPos = siInventoryPos;
					clRepairItem.Set( &clItem );

					// ���� �ҷ��� ������ ĳ���� unique ��
					RepairCharUnique = pclCM->CR[toid]->GetCharUnique();
					MyCharUnique = pclCM->CR[id]->GetCharUnique();
					RepairPrice = siTradePerson1Money;
				}
			}

			for (int i = 0; i < MAX_PRIVATETRADEORDER_ITEM_NUM; ++i )
			{
				cltItem clItem;
				
				// i ��° ��ġ�� �������� �ִ���...
				if ( pclPrivateTradeOrderMgr->GetOrderIndexItem( ToPersonID, FromPersonID, i, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, &clItem ) )
				{
					SI32 siInventoryPos = pclPrivateTradeOrderMgr->GetOrderIndexItemInventoryPos( ToPersonID, FromPersonID, pclPrivateTradeMyAccept->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyAccept->siPrivateTradeOrderCountIndex, i );

					if ( siInventoryPos < PERSONITEM_INV0 )
					{
						return;
					}

					cltItem* pclfromitem = &pclCM->CR[toid]->pclCI->clCharItem.clItem[ siInventoryPos ];

					if ( ! clItem.IsSame( pclfromitem, false ) )			// �������� ��ġ���� ����.
					{
						return;
					}

					if ( ! clItem.CanRepair( pclItemManager ) )
					{
						return;
					}

					++ItemCount;

					// ���� ��忡���� �ŷ� ��ǰ�� 1���� �����Ƿ�...
					if ( ItemCount > 1 )
					{
						return;
					}

					RepairItemInventoryPos = siInventoryPos;
					
					clRepairItem.Set( &clItem );

					RepairCharUnique = pclCM->CR[id]->GetCharUnique();
					MyCharUnique = pclCM->CR[toid]->GetCharUnique();
					RepairPrice = siTradePerson2Money;
				}
			}


			//--------- ���⼭���� ���� �ŷ�
			SI32 rtnval = 0;
			if( Repair( RepairCharUnique, MyCharUnique, RepairItemInventoryPos, &clRepairItem, RepairPrice, &rtnval ) == false )
			{
				return;
			}
			else		// ���� ����
			{
				cltRentContract Temp1, Temp2;
				Temp1.Init();
				Temp2.Init();

				cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( 1, 0, 0, 0, 0, 0, 0, &Temp1, 0, 0, -1, pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse() );
				cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ), (BYTE*)&clPrivateTradeEnd );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd1( 1, 0, 0, 0, 0, 0, 0, &Temp2, 0, 0, -1, pclCM->CR[toid]->pclCI->clHorseInfo.GetCurrentShowHorse() );
				cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd1 ), (BYTE*)&clPrivateTradeEnd1 );
				pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg1);

				pclPrivateTradeOrderMgr->Cancel( FromPersonID );
				pclPrivateTradeOrderMgr->Cancel( ToPersonID );
			}
		}
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_MYCANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PrivateTrade_MyCancel *pclPrivateTradeMyCancel = (cltGameMsgRequest_PrivateTrade_MyCancel *) pclMsg->cData;

	if ( pclPrivateTradeMyCancel->siOtherCharUnique < 1 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID <= 0) return ;

	SI32 toid = pclCM->GetIDFromCharUnique(pclPrivateTradeMyCancel->siOtherCharUnique);
	if(toid <= 0) return ;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID <= 0) return ;


	cltGameMsgResponse_PrivateTrade_MyCancel clPrivateTrade_MyCancel( 1 );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL, sizeof( clPrivateTrade_MyCancel ), (BYTE*)&clPrivateTrade_MyCancel );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	
	cltGameMsgResponse_PrivateTrade_OtherCancel clPRivateTrade_OtherCancel( 1 );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL, sizeof( clPRivateTrade_OtherCancel ), (BYTE*)&clPRivateTrade_OtherCancel );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg2);

	pclPrivateTradeOrderMgr->SetMyCancel( FromPersonID, ToPersonID, pclPrivateTradeMyCancel->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyCancel->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->SetMyCancel( ToPersonID, FromPersonID, pclPrivateTradeMyCancel->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyCancel->siPrivateTradeOrderCountIndex );
	pclPrivateTradeOrderMgr->IncreaseAcceptCounter( FromPersonID, ToPersonID, pclPrivateTradeMyCancel->siPrivateTradeOrderMgrIndex, pclPrivateTradeMyCancel->siPrivateTradeOrderCountIndex );

	return;
}
