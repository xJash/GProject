//---------------------------------
// 2004/6/23 ���°�
//---------------------------------

#include "..\Client.h"
#include "..\Music\Music.h"
#include "..\CommonLogic\MsgType.h"

#include "..\CommonLogic\Msg\MsgType-Hunt.h"
#include "..\CommonLogic\Hunt\Hunt.h"

#include "../NStructureDlg/NewMarket/NNewMarketDlg.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_MARKETORDER(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = (cltTradeOrder*)pclMsg->cData;
	
	int count = 0;

	// ���� �ֹ��� ���ֿ��� �����Ѵ�.
	for(SI32 i = 0;i < MARKET_ORDER_SEND_UNIT;i++)
	{
		if(pclorder[i].siPrice)
		{
			pclMarketManager->PutResponseOrder(&pclorder[i]);
			count++;
		}
	}

	if( count == 0 ) {
		pclMarketManager->bResponseEmptyOrder = TRUE;
	}
	

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SELL_NEWMARKET(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BUY_NEWMARKET(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RECALL_NEWMARKET(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWMARKETACCOUNT(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_NewMarketAccount* pclinfo = (cltGameMsgResponse_NewMarketAccount*)pclMsg->cData;


	if( m_pDialog[ NNEWMARKET_DLG ] )
	{
		((NNewMarketUserSellDlg*)((NNewMarketDlg*)m_pDialog[ NNEWMARKET_DLG ])->m_pUserChildDlg[0])->SetNewMarketAccount( pclinfo );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWMARKETITEMLIST(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_NewMarketItemList* pclinfo = (cltGameMsgResponse_NewMarketItemList*)pclMsg->cData;

	if( m_pDialog[ NNEWMARKET_SUB_DLG ] )
	{
		if( cltGameMsgRequest_NewMarketItemList::TYPE_NORMAL_LIST == pclinfo->uiType )
			((NNewMarketUserBuyDlgSub*)m_pDialog[ NNEWMARKET_SUB_DLG ])->SetItemList( pclinfo );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETFROMNEWMARKET(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = (cltTradeOrder*)pclMsg->cData;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWSELLITEM(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = (cltTradeOrder*)pclMsg->cData;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWBUYITEM(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = (cltTradeOrder*)pclMsg->cData;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETNEWMARKETFEE(cltMsg* pclMsg, SI32 id)
{
	// ���� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = (cltTradeOrder*)pclMsg->cData;
}

