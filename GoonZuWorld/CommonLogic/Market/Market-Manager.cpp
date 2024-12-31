//---------------------------------
// 2003/6/18 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "..\..\Server\Server.h"
#include "../../Client/Client.h"
#include "../../Client/InterfaceMgr/DialogController.h"
#include "../../Client/NStructureDlg/Market/NMarketDlg.h"

#include "..\..\Resource.h"

#include "Market.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Market.h"

//-------------------------------------
// CommonLogic
//-------------------------------------
#include "MsgRval-Define.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "..\..\CommonLogic\Msg\MsgType-Quest.h"

#include "../CityHall/TaxpaymentListDlg.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

//----------------------------------------
// Server
//----------------------------------------
#include "..\..\Server\Statistics\Statistics.h"

//-------------------------------------
// ����
//-------------------------------------
#include "..\Server\Minister\MinisterBase.h"
#include "..\Server\Minister\Minister-Izo.h"
#include "..\Server\Minister\MinisterMgr.h"



extern cltCommonLogic* pclClient;

cltMarketManager::cltMarketManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName ) : cltStructureMngBasic(MAX_MARKET_TAB_NUMBER, pclcm, ranktype, strFileName )
{
	SI32 i, j;
	
	m_hItemImage		= NULL;
	m_hItemMallBitmap	= NULL;

	SellButtonEnableSwitch	= FALSE;

	ImageListConnectedSwitch	= FALSE;

	pclCurrentInvItem			= NULL;
	pclCurrentStgItem			= NULL;

	ShowResponseOrderSiwtch		= TRUE;
	siResponseOrderIndex		= 0;
	CurrentSelectedBuyItemUnique	= 0;


	hUserDlgBuyHwnd				= NULL;

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		pclItemTypeSearch[i]	= NULL;
		pclItemTypeOrder[i]		= NULL;
		siItemTypeOrderIndex[i]	= 0;
	}

	if(gamemode == GAMEMODE_SERVER)
	{
		pclOrderManager	= new cltTradeOrderManager(MAX_MARKET_ORDER_NUMBER);
		
		
		for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
		{
			pclItemTypeSearch[i]	= new SI32[MAX_MARKET_ORDER_NUMBER];
			for(j = 0;j < MAX_MARKET_ORDER_NUMBER;j++)
			{
				pclItemTypeSearch[i][j] = -1;
			}

			pclItemTypeOrder[i]		= new SI32[MAX_MARKET_ORDER_NUMBER];
			for(j = 0;j < MAX_MARKET_ORDER_NUMBER;j++)
			{
				pclItemTypeOrder[i][j]	= -1;
			}
		}
		
	}
	else
	{
		pclOrderManager		= NULL;
	}

	siRefBufferIndex	= 0;

	m_hUserDlgBuyList = NULL ;
	m_siSelectedBuyList = -1 ;
	for ( i = 0 ; i < MAX_RESPONSE_ORDER_NUMBER ; i ++ )
		m_siSelectedBuyIndex[i] = -1 ;

	// ���Ͽ� ��ϵ� �����۵��� �ּҰ��ݰ� �� �������� ��� ������ �����Ѵ�.
	for (i = 0 ; i < MAX_ITEMINFO_NUMBER; i++ )
	{
		m_MinPrice[i]		= MAX_PRICE_IN_MARKET;
		m_MinPriceAmount[i] = -1;
	}
}

cltMarketManager::~cltMarketManager()
{
	SI32 i;

	if(pclOrderManager)
	{
		delete pclOrderManager;
		pclOrderManager = NULL;
	}

	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{
		if(pclItemTypeOrder[i])
		{
			delete[] pclItemTypeOrder[i];
			pclItemTypeOrder[i] = NULL;
		}

		if(pclItemTypeSearch[i])
		{
			delete[] pclItemTypeSearch[i];
			pclItemTypeSearch[i] = NULL;
		}
	}

}

// ���� ȯ�� �λ縻ǥ�� . 
void cltMarketManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1667);
	SetMainExplain(hDlg, pText);
}

void cltMarketManager::Do_WM_INITDIALOG(SI32 charunique)
{

	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);	

	// �ǹ��� ���� ������ ������ ��û�Ѵ�. 
	SI32 id = 1;
	if(id)
	{
		//-----------------------------------------------------------
		// ĳ���� â�� ���� ����Ʈ�� �������̶�� 
		// ���� ������ ����Ʈ�� �Ϸ�Ǿ����� �˷��ش�.
		//-----------------------------------------------------------
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_STRUCTUREOPEN;
		if(pclClient->pclCM->CR[id]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
			cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

	}

	
	// ���� ��ȭ ���� �ڵ��� �ʱ�ȭ�Ѵ�. 
	hUserDlgBuyHwnd				= NULL;
	
}

// ���ָ� �ż��Ѵ�.
BOOL cltMarketManager::CreateMarket(SI32 siunique)
{
	
	// ���ָ� �����. 
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltMarket(siunique);
		return TRUE;
	}
		
	return FALSE;
}


// Ư���������� ���� ������ �ֹ��� ã�´�. 
bool cltMarketManager::FindLowPriceOrderInfo(SI32 unique, GMONEY* pprice, SI32* pamount)
{
	// ������ �ִ� �����͸� ����ϴ� ������ ���� - by LEEKH 2008-10-09 
	// return pclOrderManager->FindLowPriceOrderInfo(unique, pprice, pamount);

	cltServer* pclserver = (cltServer*)pclClient;
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( pclserver->bCompleteDBInitAll == FALSE )		return false;

	SI32 ref = pclserver->pclItemManager->FindItemRefFromUnique(unique);
	if( ref < 0 || ref >= MAX_ITEMINFO_NUMBER )			return false;
	if(m_MinPriceAmount[ref] < 0)						return false;

	*pprice = m_MinPrice[ref];
	*pamount = m_MinPriceAmount[ref];

	return true;
}

void cltMarketManager::MakeLowPriceOrderInfo()
{
	SI32 i = 0;
	cltServer* pclserver = (cltServer*)pclClient;
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( pclserver->bCompleteDBInitAll == FALSE )		return;

	for(i=0; i<MAX_ITEMINFO_NUMBER; i++)
	{
		// �������� �������� ����� ���� ������ �ʱ�ȭ
		m_MinPrice[i] = MAX_PRICE_IN_MARKET;
		m_MinPriceAmount[i] = -1;
	}

	//---------------------------------------------------------
	// �������� ���� ������ �����Ѵ�.
	cltItem  clItem;
	cltTradeOrder** porder	= pclOrderManager->pclOrderSell;
	for(i = 0;i < pclOrderManager->siMaxOrderNum;i++)
	{
		if(porder[i] == NULL)							continue;

		clItem.Set(&porder[i]->clItemData);
		SI32 ref = pclserver->pclItemManager->FindItemRefFromUnique(clItem.siUnique);
		if( ref < 0 || ref >= MAX_ITEMINFO_NUMBER )		continue;

		if ( porder[i]->siPrice < m_MinPrice[ref] && porder[i]->bBankError == false )
		{
			m_MinPrice[ref]			= porder[i]->siPrice;
			m_MinPriceAmount[ref]	= porder[i]->siAmount;
		}
	}
	//---------------------------------------------------------
}

// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
void cltMarketManager::Action(bool bdaychangedswitch)
{
	static SI32 marketitemindex	= 0;

	SI32		i		  = 0;
	cltServer*	pclserver = (cltServer*)pclClient;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	//----------------------------------------
	// ���� �ֹ� ������ �����Ѵ�. (������ 15%�� ����� ) 
	//----------------------------------------
	if(bdaychangedswitch)
	{
		// ��ü ���� �ֹ��� �˻��Ͽ� ��¥�� ���� �ð� �̻� ����� �ֹ��� ������ �����. 
		// ������ ���̻� ���� �� ���� ��쿡�� �ֹ� ��ü�� �����Ѵ�. (��ǰ��.)
		if(pclserver->pclTime != NULL)
		{
			SI32 curdate = pclserver->pclTime->clDate.GetDateVary();
			
			cltTradeOrder clorder;
			for( i = 0;i < pclOrderManager->siMaxOrderNum;i++)
			{
				clorder.Set(pclOrderManager->pclOrderSell[i]);

				if(clorder.siPersonID <= 0)continue;

				// PCK : ���̱� ���� ������ ����Ѵ�. (�α׿�)
				GMONEY siBeforeMoney = clorder.siPrice;

				if(clorder.siDate + 30 <= curdate)	// 18�Ͽ� �ѹ���
				{
					// ������ ��ȿ�� ���, 
					if( clorder.siPrice )
					{
						CMinisterIzo *pclminister = (CMinisterIzo *)((cltServer*)pclClient)->pclMinisterMgr->GetMinister(MINISTER_IZO);
						SI32 downrate = pclminister->GetMarketDownRate();

						GMONEY cutprice = clorder.siPrice * downrate / 100;
						
						// ������ ��´�. 
						clorder.siPrice -= max(2, cutprice);
						if(clorder.siPrice < 0)clorder.siPrice = 0;
					}
					
					// ��¥�� �����Ѵ�. 
					clorder.siDate	= curdate;

					// ����� �ֹ� ������ DB�� ������. 
					// ������ �� �̻� �������� ������, �����Ѵ�.
					sDBRequest_ReduceOrderPrice clMsg(&clorder, siBeforeMoney);
					pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
				}
			}
		}
	}

	//----------------------------------------------
	// ���� �ֹ��� ������Ʈ �Ѵ�. 
	//----------------------------------------------
	if((pclClient->GetFrame() % 20000) == 0)
	{
		// �ʱ�ȭ. 
		for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
		{
			siItemTypeOrderIndex[i] = 0;
			
			for(SI32 j = 0;j < MAX_MARKET_ORDER_NUMBER;j++)
			{
				pclItemTypeSearch[i][j] = -1;
				pclItemTypeOrder[i][j]	= -1;
			}
		}

		cltItem  clItem;
		cltTradeOrder** porder	= pclOrderManager->pclOrderSell;
		for(i = 0;i < pclOrderManager->siMaxOrderNum;i++)
		{
			if(porder[i] == NULL)							continue;

			SI32 itemunique = porder[i]->clItemData.siUnique;
			if(itemunique <= 0)								continue;
			SetItemTypeOrder(porder[i], 100);
		}
	}
	
	//-----------------------------------------
	// �ڵ� ���Ÿ� �����Ѵ�. 
	//-----------------------------------------
	// [�˻� : Ȳ���� 2007. 10. 17 �ý��ۿ��� ��ǰ ����.]
	if(pclClient->GetFrame() % pclClient->siMarketAutoBuyDelayFrame == 0)		
	{
		// ǰ���� �����Ѵ�. 
		SI16 typelist[] =
		{
			ITEMTYPE_SWORD,
			ITEMTYPE_SPEAR,
			ITEMTYPE_AXE,
			ITEMTYPE_STAFF,
			ITEMTYPE_GUN,
			ITEMTYPE_BOW,
			ITEMTYPE_ARMOUR,
			ITEMTYPE_HELMET,
			ITEMTYPE_DRESS,
			//IT EMTYPE_HAT,
			//ITEMTYPE_RING,
			//ITEMTYPE_NECK,
			ITEMTYPE_BELT,
			ITEMTYPE_DISH,
			ITEMTYPE_IRON,
			//ITEMTYPE_CANNON,
			ITEMTYPE_SHOES,
			ITEMTYPE_FISHINGROD			
		};

		SI32 typenum = sizeof(typelist) / sizeof(SI16);
		
		SI32 itemtype = typelist[ rand() % typenum];

		// ������ ���� �ֹ��� ã�´�. 
		cltTradeOrder* pclorder = GetOrderForSystemBuy(itemtype);
		
		
		if(pclorder)
		{
			// ���� �ֹ��� �ִ´�. 
			cltTradeOrder clorder;

			clorder.Set(pclorder);
			//[������ : Ȳ���� 2007.10.24 �ý����� ���忡 ������ �ø� ��ǰ�� �����ϴ� ���.]
			clorder.siPersonID	= 0;
			clorder.siAmount	= 1;
			
			pclserver->MarketBuyAction(0, 0, &clorder, MARKETTRADE_REASON_EQUIPITEM);

			if ( pclserver->pclStatisticsManager )
			{
				pclserver->pclStatisticsManager->clDailyStatistics.siSystemBuyMoney += clorder.siPrice;
				pclserver->pclStatisticsManager->clDailyStatistics.siSystemBuyNum++; 
			}

			SystemBuyItemStatistics( pclorder->clItemData.siUnique, pclorder->siPrice * clorder.siAmount );

			NStatistics_Add("Item", clorder.clItemData.siUnique,"SystemBuy", clorder.siAmount);
			NStatistics_Add("Item", clorder.clItemData.siUnique,"SystemBuyPrice", pclorder->siPrice);
			NStatistics_Set("Item", clorder.clItemData.siUnique, "Name", pclserver->pclItemManager->GetName(clorder.clItemData.siUnique));
		}
	}

	//-----------------------------------------
	// �ڵ� ���Ÿ� �����Ѵ�. 
	// KHY - 0901 -  ���� ������ �ڵ����� ����.
	if (pclserver->siMarketMoneyItemAutoBuyDelayTime > 0)
	{
		if(pclClient->GetFrame()%pclserver->siMarketMoneyItemAutoBuyDelayTime == 0)		
		{
			// ���� ������ �ڵ����� �ݾ��� �Ѿ��� ��ä ����ȭ���� 0.1%�� ���� ���Ѵ�.
			SI64 siLimitMoney = (SI64)((REAL32)pclserver->siTotalMoney * 0.001f);
			if( pclserver->siMarketMoneyItemMaxpriceNow < siLimitMoney )
			{
				// ǰ���� �����Ѵ�. 
				SI16 count = 0;
				SI16 randSelect = 0;

				// �����Ͱ� �ִ� ���� ������� �Ѵ�.
				for(SI32 i = 0; i <MAX_SYSTEMBUYTEM_NUM ;i++)
				{
					if(pclserver->stSystemBuyItem[i].m_siUnique > 0)
						count++;
				}

				if(count > 0) // ��ϵ� �������� ����.
				{
					randSelect = rand()%count; // ���� ����.

					// ���� ������ ������ �ü��� 80% �����̴�.
					GMONEY gMaxPrice = 0;
					if( pclserver->stSystemBuyItem[randSelect].m_siUnique > 0)
					{
						cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, pclserver->stSystemBuyItem[randSelect].m_siUnique);
						if(pclprice)		gMaxPrice = (GMONEY)(pclprice->fPrice * 0.9f);
					}
					// ������ ���� �ֹ��� ã�´�.  - ���ذ��� ����: �ü��� 90%
					cltTradeOrder* pclorder = NULL;
					if( gMaxPrice > 0 )		pclorder = GetOrderForSystemBuyUnique(pclserver->stSystemBuyItem[randSelect].m_siUnique, gMaxPrice);

					if(pclorder)
					{
						// ���� �ֹ��� �ִ´�. 
						cltTradeOrder clorder;

						clorder.Set(pclorder);
						clorder.siPersonID	= 0;
						clorder.siAmount	= 1;

						// �� �ڽ��� ��� �Ĵ� ������ �ý����� ��°����� Ȯ���ϰ� �Ѵ�.
						//<-------------------------------------------->
						pclserver->MarketBuyAction(0, 0, &clorder, MARKETTRADE_REASON_CASHITEM);  // 0 �� �ý��� �����̴�.

						// ���� ������������ �ؾ߰�����, ���ݾ����۸� �����ϴ°��� �������� �ʾ� ���⼭ �����ش�.
						pclserver->siMarketMoneyItemMaxpriceNow += pclorder->siPrice;

						sDBRequest_SetSystemBuyItemNowMoney clMsg( pclserver->siMarketMoneyItemMaxpriceNow);
						pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

						if ( pclserver->pclStatisticsManager )
						{
							pclserver->pclStatisticsManager->clDailyStatistics.siSystemBuyMoney += clorder.siPrice;
							pclserver->pclStatisticsManager->clDailyStatistics.siSystemBuyNum++; 
						}

						pclClient->pclLog->FilePrint("Config\\SystemBuyItem_CashItem.log", "ItemUnique:%d\tPrice:%I64d",
								pclorder->clItemData.siUnique, pclorder->siPrice );

						SystemBuyItemStatistics( pclorder->clItemData.siUnique, pclorder->siPrice * clorder.siAmount );
					}
				}	
			}
		}
	}
}

void cltMarketManager::SystemBuyItemStatistics(SI16 siItemUnique, GMONEY gPrice)
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI32	i;
	SI32	siTotalCount[MAX_ITEM_UNIQUE];
	GMONEY	gTotalPrice[MAX_ITEM_UNIQUE];

	for (i=0; i<MAX_ITEM_UNIQUE; i++)
	{
		siTotalCount[i] = -1;
		gTotalPrice[i] = -1;
	}

	TCHAR	szFileName[MAX_PATH];
	StringCchPrintf(szFileName, sizeof(szFileName), "Config\\SystemBuyItemStatistics_%04d%02d%02d.log", pclserver->sTime.wYear, pclserver->sTime.wMonth, pclserver->sTime.wDay);

	// ������ ������ ������ �д´�.    
	FILE* fp = NULL;
	TCHAR	szLine[1024];
	fp = fopen(szFileName, "rt");
	if( fp )
	{
		fgets(szLine, sizeof(szLine), fp);		// �÷��� ���

		while( fgets(szLine, sizeof(szLine), fp) )
		{
			SI32	siUnique = 0;
			TCHAR	szItemName[128];
			SI32	siFileCount;
			SI64	siFilePrice;
			// ����������ũ ������_�̸� ���� �Ѱ���
			_stscanf( szLine, "%d %s %d %I64d", &siUnique, szItemName, &siFileCount, &siFilePrice );
			if( siUnique >= 0 && siUnique < MAX_ITEM_UNIQUE )
			{
				siTotalCount[siUnique]	= siFileCount;
				gTotalPrice[siUnique]	 = siFilePrice;
			}
		}
		fclose(fp);
	}

	// ���ӿ��� ����ϰ� �ִ� �������� �������� Ǯ���ش�.
	for( i=0; i<MAX_ITEM_UNIQUE; i++)
	{
		if( pclserver->pclItemManager->FindItemRefFromUnique( i ) > 0)
		{
			if( siTotalCount[i] < 0 || gTotalPrice[i] < 0 )
			{
				siTotalCount[i] = 0;		gTotalPrice[i] = 0;
			}
		}
	}

	// �� ����
	if( siItemUnique >= 0 && siItemUnique < MAX_ITEM_UNIQUE )
	{
		siTotalCount[siItemUnique]++;
		gTotalPrice[siItemUnique] += gPrice;
	}

	// ������ ���� ����Ѵ�.
	fp = fopen(szFileName, "wt");
	if( fp )
	{
		// �÷��� ���
		fprintf(fp, "ItemUnique\tItemName\tTotalCount\tTotalPrice\n");
		for( i=0; i<MAX_ITEM_UNIQUE; i++ )
		{
			if( siTotalCount[i] < 0 )		continue;

			NTCHARString128 kItemName;
			kItemName = pclserver->pclItemManager->GetName(i);		kItemName.Replace(" ", "_");
			fprintf(fp, "%d\t%s\t%d\t%I64d\n", i, (TCHAR*)kItemName, siTotalCount[i], gTotalPrice[i]);
		}
		fclose(fp);
	}
}

// ���� ���ϰ� ó�� �Լ�. 
void cltMarketManager::ServerRtnValOperate()
{
	// ���� �����κ��� ���� �޽����� ������ �д�. 
	SI32 returnval = siServerResponseValue;

	cltStructureMngBasic::ServerRtnValOperate();

	switch(returnval)
	{
	case SRVAL_MARKET_SUCCESS_TRADE:
//	case SRVAL_MARKET_FAIL_TRADE_LIEORDER:
		// ������Ʈ �ؾ� �� ������ �߻����� ��. 
		// ������ ��������  �Ǹ� �ֹ� ����Ʈ�� ��û�Ѵ�. 
		cltClient* pclclient = (cltClient*) pclClient;
		if( pclclient->m_pDialog[ NMARKET_DLG ] != NULL && pclclient->m_pDialog[ NMARKET_DLG ]->IsCreate() == true 
			&& ((NMarketUserBuyDlg*)((NMarketDlg*)pclclient->m_pDialog[ NMARKET_DLG ])->m_pUserChildDlg[1]) != NULL )
			((NMarketUserBuyDlg*)((NMarketDlg*)pclclient->m_pDialog[ NMARKET_DLG ])->m_pUserChildDlg[1])->RequestMarketOrderList( CurrentSelectedBuyItemUnique);
		if( pclclient->m_pDialog[ NMARKET_SUB_DLG ] != NULL && pclclient->m_pDialog[ NMARKET_SUB_DLG ]->IsCreate() == true )
			((NMarketUserBuyDlgSub*)pclclient->m_pDialog[ NMARKET_SUB_DLG ])->RequestMarketOrderList( CurrentSelectedBuyItemUnique);

		break;
	}

}

// ������ Ÿ�Ժ� ���ۿ� ���� �ֹ� ������ �߰��Ѵ�. 
bool cltMarketManager::SetItemTypeOrder(cltTradeOrder* pclorder, SI32 orderunique)
{
	if(pclorder == NULL)return false;

	cltItem clitem;
	clitem.Set(&pclorder->clItemData);

	SI32 itemtype = clitem.GetType(pclClient->pclItemManager);

	if(itemtype <= 0)
	{
		return false;
	}

	// �ֹ��� �ε���. 
	SI32 index = pclorder->siIndex;
	if(index < 0)return false;

	// ���� ���� ����. 
	if(pclorder->siPrice == 0)
	{
		SI32 ref = pclItemTypeSearch[itemtype][index];
		if(ref >= 0)
		{
			pclItemTypeSearch[itemtype][index]	= -1;	// ����. 

			pclItemTypeOrder[itemtype][ref]		= 0;

			if(siItemTypeOrderIndex[itemtype] > 0)
			{
				// ������ �ֹ��� �߰��� �ִ´�. 
				SI32 tempindex = pclItemTypeOrder[itemtype][ siItemTypeOrderIndex[itemtype] - 1 ];
				pclItemTypeOrder[itemtype][ref] = tempindex;

				pclItemTypeSearch[itemtype][tempindex]	= ref;
				
				siItemTypeOrderIndex[itemtype]--;
			}
		}
	}
	// �ű� �Ǵ� ������Ʈ. 
	else
	{
		SI32 ref = pclItemTypeSearch[itemtype][index];
		if(ref >= 0)
		{
			pclItemTypeOrder[itemtype][ref] = index;

		}
		else
		{
			pclItemTypeSearch[itemtype][index] = siItemTypeOrderIndex[itemtype];		// �߰� 

			pclItemTypeOrder[itemtype][ siItemTypeOrderIndex[itemtype] ] = index;
			siItemTypeOrderIndex[itemtype]++;	// ������ �Ѱ� ���δ�. 

		}
		
	}

	return true;
}

// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �����ϰ� ����. 
SI16 cltMarketManager::GetRandomOrder(SI32 itemtype )
{
	SI32 searchnum			= siItemTypeOrderIndex[itemtype];
	cltTradeOrder** porder	= pclOrderManager->pclOrderSell;

	if(searchnum <= 0)return 0;

	siRefBufferIndex	=	0;

	for(SI32 i = 0;i < searchnum;i++)
	{
		SI32 ref = pclItemTypeOrder[itemtype][ i ];

		SI32 itemunique = porder[ref]->clItemData.siUnique;

		// ����ó�� ����Ʈ
		switch( itemunique )
		{
		//����
		case ITEMUNIQUE(5350):
		case ITEMUNIQUE(5355):
		case ITEMUNIQUE(5360):
		case ITEMUNIQUE(5365):
		case ITEMUNIQUE(5370):
		case ITEMUNIQUE(5375):
		case ITEMUNIQUE(5380):
		case ITEMUNIQUE(5385):
		case ITEMUNIQUE(5390):
		//����
		case ITEMUNIQUE(7030):
		case ITEMUNIQUE(7070):
		case ITEMUNIQUE(7080):
		case ITEMUNIQUE(7100):
		case ITEMUNIQUE(7175):
		case ITEMUNIQUE(7180):
		case ITEMUNIQUE(7185):
			continue;
		}

		// ���ǰ���� ����Ʈ�� �߰��Ѵ�.
		siRefBuffer[siRefBufferIndex] = ref;
		siRefBufferIndex++;
	}

	if(siRefBufferIndex)
	{
		return porder[ siRefBuffer[rand() % siRefBufferIndex] ]->clItemData.siUnique;
	}

	return 0;

}

// [�˻� : Ȳ���� 2007. 10. 17 �ý��ۿ��� ��ǰ ����.]
// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �ý����� ������ ��ǰ�� �����Ѵ�. 
cltTradeOrder* cltMarketManager::GetOrderForSystemBuy(SI32 itemtype)
{
	SI32 i;

	SI32 searchnum			= siItemTypeOrderIndex[itemtype];
	cltTradeOrder** porder	= pclOrderManager->pclOrderSell;

	if(searchnum <= 0)return 0;

	siRefBufferIndex	=	0;

	for(i = 0;i < searchnum;i++)
	{
		
		SI32 ref = pclItemTypeOrder[itemtype][ i ];
		
		// �ش� ��ǰ�� �ü��� ���Ѵ�. 
		cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, porder[ref]->clItemData.siUnique);
		if(pclprice == NULL)continue;
		if(pclprice->siPrice > 50000000) continue ; // 5õ���� �̻��� ������ �ʴ´�.

		SI64 price = (SI64)pclprice->siPrice * 150 / 100 ;

		// �ü����� �ξ� ��θ� �������� �ʴ´�. 
		if(porder[ref]->siPrice > price)continue;

		// ���ǰ���� ����Ʈ�� �߰��Ѵ�.
		siRefBuffer[siRefBufferIndex] = ref;
		siRefBufferIndex++;
	}

	cltTradeOrder* pclorderrtn = NULL;

	if(siRefBufferIndex)
	{
		return porder[ siRefBuffer[rand() % siRefBufferIndex] ];
	}

	return pclorderrtn;


}


// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �ý����� ������ ��ǰ�� �����Ѵ�. 
cltTradeOrder* cltMarketManager::GetOrderForSystemBuyUnique(SI16 itemUnique , GMONEY gPrice)
{
	cltServer* pclserver = (cltServer*)pclClient;
	cltTradeOrder* pclorderrtn = NULL;

	SI32 ref1=  pclClient->pclItemManager->FindItemRefFromUnique(itemUnique);

	if(ref1 == 0) return pclorderrtn ;
	SI32 itemtype	= pclClient->pclItemManager->pclItemInfo[ref1]->siType;

	SI32 searchnum			= siItemTypeOrderIndex[itemtype];
	cltTradeOrder** porder	= pclOrderManager->pclOrderSell;

	if(searchnum <= 0)return pclorderrtn;

	GMONEY tempPrice = gPrice;
	SI32 selectRef = -1;

	for(SI32 i = 0;i < searchnum;i++)
	{
		SI32 ref = pclItemTypeOrder[itemtype][ i ];

		// �ش� ��ǰ�� �ü��� ���Ѵ�. 
		//cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, porder[ref]->clItemData.siUnique);

		// ���� ����ũ�� �ֹ��� ã�´�.
		if(porder[ref]->clItemData.siUnique ==  itemUnique)
		{
			// ������ �ݾ׺��� �۾ƾ� �Ѵ�.
			if(porder[ref]->siPrice <= gPrice) 
			{
				// ���߿����� ���� �۾ƾ� �Ѵ�.
				if(porder[ref]->siPrice <= tempPrice )
				{
					tempPrice = porder[ref]->siPrice;
					selectRef = ref;
				}
			}
		}
	}

	if(selectRef >= 0)
	{
		return porder[ selectRef];
	}

	return pclorderrtn;


}


cltNewMarketManager::cltNewMarketManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, char *strFileName ) : cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, ranktype, strFileName )
{
	bUpdateItemPrice = false;
	bUpdateItemReducePrice = false;

	pclTaxPaymentDlg = new cltTaxPaymentListDlg;

	m_bSetFee = true;	// ������ ���� ����.
}


cltNewMarketManager::~cltNewMarketManager()
{
	if( pclTaxPaymentDlg ) delete pclTaxPaymentDlg;
}

BOOL cltNewMarketManager::CreateNewMarket(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltNewMarket(siunique);
		return TRUE;
	}

	return FALSE;
}

// ���� ȯ�� �λ縻ǥ��..
void cltNewMarketManager::GreetingMsg(HWND hDlg)
{
	char* pText = GetTxtFromMgr(5652);
	SetMainExplain(hDlg, pText);
}

void cltNewMarketManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);

	// �ǹ��� ���� ������ ������ ��û�Ѵ�. 
	SI32 id = 1;
	if(id)
	{
		//-----------------------------------------------------------
		// ĳ���� â�� ���� ����Ʈ�� �������̶�� 
		// ���� ������ ����Ʈ�� �Ϸ�Ǿ����� �˷��ش�.
		//-----------------------------------------------------------
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_STRUCTUREOPEN;
		if(pclClient->pclCM->CR[id]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
			cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

	}
}

// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
void cltNewMarketManager::Action(cltTime* pcltime, clock_t CurrentClock)
{
	if(pcltime == NULL)return ;

	CommonAction( pcltime );

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;
	cltServer * pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL ) return ;

	static SI32 wPrevHour = -1;
	if( wPrevHour != pclserver->sTime.wHour )
	{
		wPrevHour = pclserver->sTime.wHour;

		// ������ �ü� ������Ʈ�� ���ǽð� 1�ð����� ������Ʈ
		sDBRequest_ManyItemNewPrice clMsg( 0, &pclserver->sTime );
		pclClient->SendDBMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
	}

	if( TABS( CurrentClock - dwUpdateTime ) > 60 * 1000 )
	{
		sDBRequest_NewMarketResult clMsg( pclserver->siServerUnique );
		pclClient->SendDBMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
		dwUpdateTime = CurrentClock;
	}

	// �����϶��� ��ħ 6�ÿ� �ѹ�
	if( 6 == pclserver->sTime.wHour && 5 > pclserver->sTime.wMinute )
	{
		if( false == bUpdateItemReducePrice )
		{
			sDBRequest_NewMarketReducePriceNotice clMsg( pclserver->siServerUnique, &pclserver->sTime );
			pclClient->SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
		
			 pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NEWMARKET, LOGCOMMAND_INDEX_NEWMARKET_REDUCEPRICE, 
											0,	0, 	NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclserver->siServerUnique, 0, 0, 0, 0, 0, NULL	);

			 m_bSetFee			    = true;	// ������ ���� ����.
			 bUpdateItemReducePrice = true;
		}
	}
	else
		bUpdateItemReducePrice = false;
	
	return;
}

void cltNewMarketManager::ServerRtnValOperate()
{
	// ���� �����κ��� ���� �޽����� ������ �д�. 
	SI32 returnval = siServerResponseValue;

	cltStructureMngBasic::ServerRtnValOperate();
}