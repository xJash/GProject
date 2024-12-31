//---------------------------------
// 2005/11/21 SJY
//---------------------------------

#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"

#include "../../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "../../CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"
#include "../../CommonLogic/WorldTraderMgr/WorldTraderManager.h"

#include "../../Client/NInterface/NSetWorldMoneyBuyDlg/NSetWorldMoneyBuyDlg.h"
#include "../../Client/NInterface/NAqTradeWindowDlg/NAqTradeWindowDlg.h"
#include "../../Client/NInterface/NTradeServerDlg/NTradeServerDlg.h"
#include "../../Client/ninterface/NAcuTradeDlg/NAcuTradeDlg_Parent.h"

#include "MsgRval-Define.h"
#include "Msg/MsgType-WorldMoney.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETWORLDMONEY_BUYDLG(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetWorldMoney_BuyDlg* pclinfo = (cltGameMsgResponse_SetWorldMoney_BuyDlg*)pclMsg->cData;

	if ( pclCM->CR[1]->pclCI->clIP.GetLevel() < FATHER_LEVEL )
		return ;

	if ( m_pDialog[NSETWORLDMONEYBUT_DLG] == NULL )
		CreateInterface(NSETWORLDMONEYBUT_DLG);

	if( m_pDialog[ NSETWORLDMONEYBUT_DLG ])
	{
		((CNSetWorldMoneyBuyDlg*)m_pDialog[NSETWORLDMONEYBUT_DLG])->Set(pclinfo->siWorldMoney,pclinfo->siWorldMoneyPrice,pclinfo->siTotalWorldMoney);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DISTRIBUTION_WORLDMONEY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Distrubution_WorldMoney* pclinfo = (cltGameMsgResponse_Distrubution_WorldMoney*)pclMsg->cData ;

	pclCM->CR[1]->pclCI->clIP.SetMoney(pclinfo->siLeftMoney);
	pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

	TCHAR *pTitle = GetTxtFromMgr(6194);
	TCHAR *pText = GetTxtFromMgr(6195);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_TRADELIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldMoney_TradeList* pclinfo = (cltGameMsgResponse_WorldMoney_TradeList*)pclMsg->cData;


	if ( !pclinfo->bEnd )
	{
		for ( SI32 i = 0 ; i < 50 ; i ++ )
			pclDistributionWorldMoney->clTradeList[pclinfo->siPage*50+i].Set(&pclinfo->clInfo[i]);
	}
	else
	{
		for ( SI32 i = 0 ; i < 50 ; i ++ )
			pclDistributionWorldMoney->clTradeList[pclinfo->siPage*50+i].Set(&pclinfo->clInfo[i]);

		// ���� ���� �߰�
		if ( true == IsCountrySwitch(Switch_Trade_Renewal) )
		{
			CNAcuTradeDlg_Parent* pclAcuTradeDlg = (CNAcuTradeDlg_Parent*)m_pDialog[NACUTRADEDLG_PARENT];
			if ( pclAcuTradeDlg )
			{
				pclAcuTradeDlg->Refresh( pclinfo->siAverageWorldMoneyPrice );
			}
		}
		else
		{
			CNAqTradeWindowDlg* pclAqTradeDlg = (CNAqTradeWindowDlg*)m_pDialog[NAQTRADEWINDOW_DLG];
			if ( pclAqTradeDlg )
			{
				pclAqTradeDlg->m_siAverageWorldMoneyPrice = pclinfo->siAverageWorldMoneyPrice;
				pclAqTradeDlg->SetTradeList();
			}
		}
		
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_SELLORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldMoney_SellOrder* pclinfo = (cltGameMsgResponse_WorldMoney_SellOrder*)pclMsg->cData;

	if ( pclinfo->siResult != 1) return ;

	// ĳ���� ���� ����
	pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
	pclCM->CR[1]->pclCI->clWorldMoney.siTradeWorldMoney = pclinfo->siWorldMoney ;
	pclCM->CR[1]->pclCI->clWorldMoney.siTradeWorldMoneyPrice = pclinfo->siPrice ;
	pclCM->CR[1]->pclCI->clIP.SetMoney(pclinfo->siLeftMoney);

	TCHAR *pTitle = GetTxtFromMgr(6196);
	TCHAR *pText = GetTxtFromMgr(6333);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

	if ( m_pDialog[NAQTRADEWINDOW_DLG] == NULL )
		return ;

	cltMsg clMsg2( GAMEMSG_REQUEST_WORLDMONEY_TRADELIST, 0, NULL );
	SendMsgToServer((sPacketHeader*)&clMsg2);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_BUYORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldMoney_BuyOrder* pclinfo = (cltGameMsgResponse_WorldMoney_BuyOrder*)pclMsg->cData;

	if ( pclinfo->siResult != 1) return ;

	// ĳ���� ���� ����
	pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
	pclCM->CR[1]->pclCI->clIP.SetMoney(pclinfo->siLeftMoney);

	TCHAR *pTitle = GetTxtFromMgr(6226);
	TCHAR *pText = GetTxtFromMgr(6227);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText,
		pclinfo->siWorldMoney,pclCM->CR[1]->pclCI->clWorldMoney.GetWorldMoney());

	// ���� ���� �߰�
	if ( true == IsCountrySwitch(Switch_Trade_Renewal) )
	{
		if ( m_pDialog[NACUTRADEDLG_PARENT] == NULL )		return ;
	}
	else
	{
		if ( m_pDialog[NAQTRADEWINDOW_DLG] == NULL )		return ;
	}

	cltMsg clMsg2( GAMEMSG_REQUEST_WORLDMONEY_TRADELIST, 0, NULL );
	SendMsgToServer((sPacketHeader*)&clMsg2);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_CANCELORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldMoney_CancelOrder* pclinfo = (cltGameMsgResponse_WorldMoney_CancelOrder*)pclMsg->cData;

	if ( pclinfo->siResult != 1) return ;

	// ĳ���� ���� ����
	pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
	pclCM->CR[1]->pclCI->clWorldMoney.siTradeWorldMoney = 0 ;
	pclCM->CR[1]->pclCI->clWorldMoney.siTradeWorldMoneyPrice = 0 ;

	TCHAR *pTitle = GetTxtFromMgr(6228);
	TCHAR *pText = GetTxtFromMgr(6229);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText,
		pclCM->CR[1]->pclCI->clWorldMoney.GetWorldMoney());

	// ���� ���� �߰�
	if ( true == IsCountrySwitch(Switch_Trade_Renewal) )
	{
		if ( m_pDialog[NACUTRADEDLG_PARENT] == NULL )		return ;
	}
	else
	{
		if ( m_pDialog[NAQTRADEWINDOW_DLG] == NULL )		return ;
	}


	cltMsg clMsg2( GAMEMSG_REQUEST_WORLDMONEY_TRADELIST, 0, NULL );
	SendMsgToServer((sPacketHeader*)&clMsg2);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDMONEY_SET_CHAR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldMoney_Set_Char* pclinfo = (cltGameMsgResponse_WorldMoney_Set_Char*)pclMsg->cData;


	TCHAR *pTitle = GetTxtFromMgr(2045);
	TCHAR *pText = GetTxtFromMgr(6331);

	if (pTitle && pText)
	{
		m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText,
			pclinfo->szCharName,pclinfo->siWorldMoney,pclinfo->siLeftWorldMoney);
	}

}


void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_SET_SELLORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Set_SellOrder* pclinfo = (cltGameMsgResponse_TradeServer_Set_SellOrder*)pclMsg->cData;

	if ( pclinfo->siResult == 1 )
	{
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
		pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

		pclCM->CR[1]->pclCI->clWorldOrder.Set(pclinfo->clOrder.clitem.siPrice,pclinfo->clOrder.siIndex,pclinfo->clOrder.clitem.siUnique,
			pclinfo->clOrder.clitem.siItemNum,pclinfo->clOrder.clitem.siType,
			pclinfo->clOrder.clitem.siPower,pclinfo->clOrder.clitem.siRank,
			pclinfo->clOrder.clitem.siRareType,
			pclinfo->clOrder.clitem.szItemData);

		//pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].Set(&pclinfo->clOrder);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_CANCEL_SELLORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Cancel_SellOrder* pclinfo = ( cltGameMsgResponse_TradeServer_Cancel_SellOrder*)pclMsg->cData;

	if ( pclinfo->siResult == 1 )
	{
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
		pclCM->CR[1]->pclCI->clWorldOrder.Set(0,0,0,0,0,0,0,0,NULL);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_SET_BUYORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Set_BuyOrder* pclinfo = (cltGameMsgResponse_TradeServer_Set_BuyOrder*)pclMsg->cData;

	if ( pclinfo->siResult == 1 )
	{
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
		pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

		pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].Init();

		if ( ((CNTradeServerBaseDlg*)m_pDialog[NTRADESERVERBASE_DLG]) )
			((CNTradeServerBaseDlg*)m_pDialog[NTRADESERVERBASE_DLG])->m_TradeServerBuy->RefreshOrder();

		//for ( SI32 i = 0 ; i < MAX_TRADESERVER_ORDER ; i ++ )
		//{
		//	if ( pclCM->CR[1]->pclCI->clWorldOrder.siUnique == 0 )
		//	{
		//		pclCM->CR[1]->pclCI->clWorldOrder.siUnique = pclinfo->clOrder.clitem.siUnique ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siIndex = pclinfo->clOrder.siIndex ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siItemNum = pclinfo->clOrder.clitem.siItemNum ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siPower = pclinfo->clOrder.clitem.siPower ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siPrice = pclinfo->clOrder.clitem.siPrice ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siRank = pclinfo->clOrder.clitem.siRank ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siRareType = pclinfo->clOrder.clitem.siRareType ;
		//		pclCM->CR[1]->pclCI->clWorldOrder.siType = pclinfo->clOrder.clitem.siType ;
		//	}
		//}

		const TCHAR* name = pclItemManager->GetName(pclinfo->clLeftItem.siUnique);
		if ( name )
		{
			TCHAR *pTitle = GetTxtFromMgr(6222);
			TCHAR *pText = GetTxtFromMgr(6223);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText,
				name,pclinfo->clOrder.clitem.siItemNum,pclinfo->clOrder.clitem.siPrice);
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_LISTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Get_ListInfo* pclinfo = (cltGameMsgResponse_TradeServer_Get_ListInfo*)pclMsg->cData;

	for ( SI32 i = 0 ; i < MAX_TRADESERVER_GET_LIST ; i ++ )
	{
		pclWorldTraderManager->clOrder[pclinfo->siIndex*MAX_TRADESERVER_GET_LIST+i].Set(&pclinfo->clInfo[i]);
	}

	if ( pclinfo->bEnd )
	{
		CNTradeServerBaseDlg* pDialog = (CNTradeServerBaseDlg*)m_pDialog[NTRADESERVERBASE_DLG];
		if ( pDialog )
		{
			pDialog->m_TradeServerBuy->siItemPrice = pclinfo->siAveragePrice ;
			pDialog->m_TradeServerBuy->siWorldMoneyPrice = pclinfo->siAverageWorldMoney ;
			pDialog->m_TradeServerBuy->m_bWorldTradeTax = pclinfo->bIsWorldTradeTax;
			pDialog->m_TradeServerBuy->m_siSpecialTaxRange = pclinfo->siSpecialTaxRange;
			pDialog->m_TradeServerBuy->m_siSpecialTaxRate = pclinfo->siSpecialTaxRate;

			((CNTradeServerBaseDlg*)m_pDialog[NTRADESERVERBASE_DLG])->m_TradeServerBuy->RefreshOrder();
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_SELLINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Get_SellInfo* pclinfo = (cltGameMsgResponse_TradeServer_Get_SellInfo*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
	pclCM->CR[1]->pclCI->clWorldOrder.Set(0,0,0,0,0,0,0,0,NULL);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_MYINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Get_MyInfo* pclinfo = (cltGameMsgResponse_TradeServer_Get_MyInfo*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clWorldOrder.Set(0,0,0,0,0,0,0,0,NULL);
	if ( pclinfo->clOrder.clitem.siUnique != 0 && pclinfo->clOrder.siPersonID == pclCM->CR[1]->pclCI->GetPersonID() )
	{
		pclCM->CR[1]->pclCI->clWorldOrder.Set(pclinfo->clOrder.clitem.siPrice,pclinfo->clOrder.siIndex,pclinfo->clOrder.clitem.siUnique,
			pclinfo->clOrder.clitem.siItemNum,pclinfo->clOrder.clitem.siType,
			pclinfo->clOrder.clitem.siPower,pclinfo->clOrder.clitem.siRank,
			pclinfo->clOrder.clitem.siRareType,
			pclinfo->clOrder.clitem.szItemData);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_SAVEDACU_LIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Get_SavedACU_List* pclinfo = (cltGameMsgResponse_TradeServer_Get_SavedACU_List*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	// â�� ���������� �׳� ����
	CNAcuTradeDlg_Parent* pclAcuTradeDlg = (CNAcuTradeDlg_Parent*)m_pDialog[NACUTRADEDLG_PARENT];
	if ( NULL == pclAcuTradeDlg )
	{
		return;
	}

	pclAcuTradeDlg->SetWithdrawDialogMemberData( pclinfo->m_siSavedACU, pclinfo->m_clAcuList );

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_TradeServer_Get_Withdraw_Acu* pclinfo = (cltGameMsgResponse_TradeServer_Get_Withdraw_Acu*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// ���� ���� ���� �ִ� ��ť�� ������Ʈ
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclinfo->m_siHoldingAcu );

	// â�� ���������� �׳� ����
	CNAcuTradeDlg_Parent* pclAcuTradeDlg = (CNAcuTradeDlg_Parent*)m_pDialog[NACUTRADEDLG_PARENT];
	if ( NULL == pclAcuTradeDlg )
	{
		return;
	}
	// ���������� ����� ��ť�� ������Ʈ
	pclAcuTradeDlg->SetWithdrawDialogMemberData( pclinfo->m_siLeftSavedAcu );

	// ���̾�α� ���� �ٽ��б�
	pclAcuTradeDlg->Refresh();

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDPASSPORT_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldPassport_Set* pclinfo = (cltGameMsgResponse_WorldPassport_Set*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// �������� ����
	pclchar->pclCI->clWorldPassport.Set( pclinfo->m_szPassportName, pclinfo->m_siIssueDateVary, pclinfo->m_siExpireDateVary );

	// ��ť���� ����
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclinfo->m_siLeftAcu );

	// â�� ���������� �׳� ����
	CNAcuTradeDlg_Parent* pclAcuTradeDlg = (CNAcuTradeDlg_Parent*)m_pDialog[NACUTRADEDLG_PARENT];
	if ( NULL == pclAcuTradeDlg )
	{
		return;
	}

	pclAcuTradeDlg->Refresh();
	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WORLDPASSPORT_EXTEND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WorldPassport_Extend* pclinfo = (cltGameMsgResponse_WorldPassport_Extend*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// �������� ����
	pclchar->pclCI->clWorldPassport.SetExpireDateVary( pclinfo->m_siExpireDateVary );

	// ��ť���� ����
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclinfo->m_siLeftAcu );

	// â�� ���������� �׳� ����
	CNAcuTradeDlg_Parent* pclAcuTradeDlg = (CNAcuTradeDlg_Parent*)m_pDialog[NACUTRADEDLG_PARENT];
	if ( NULL == pclAcuTradeDlg )
	{
		return;
	}

	pclAcuTradeDlg->Refresh();

}
