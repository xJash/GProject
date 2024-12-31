#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

#include "SummonHeroMarket.h"

#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/msg/MsgType-SummonHeroMarket.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../Server/Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-SummonHeroMarket.h"
#include "..\..\Client\Music\Music.h"

extern cltCommonLogic* pclClient;

//----------------------------------------------
// cltSummonHeroMarket
//----------------------------------------------
cltSummonHeroMarket::cltSummonHeroMarket(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{

}


cltSummonHeroMarket::~cltSummonHeroMarket()
{

}




cltSummonHeroMarketManager::cltSummonHeroMarketManager(cltCharManager* pclcm, SI32 gamemode, SI32 portraitid, TCHAR *strFileName ) : cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, portraitid, strFileName )
{
	m_siSelectList = 0;
	siAddStartIndex = 0;
	siTotalOrderNumber = 0;
	siTotalResponseOrderNumber = 0;

	m_hSummonPortraitBitmap = NULL;
	m_siPortraitSummonKind = 0;

	if(gamemode == GAMEMODE_SERVER)
	{
		pclSummonOrder = new cltSummonOrder[ MAX_SUMMONHEROMARKET_ORDER_NUMBER ];
	}
	else
	{
		pclSummonOrder = NULL;
	}

	siSelectedIndex = -1;
}


cltSummonHeroMarketManager::~cltSummonHeroMarketManager()
{
	if( m_hSummonPortraitBitmap ) {
		DeleteObject(m_hSummonPortraitBitmap);	
		m_hSummonPortraitBitmap = NULL;	
	}
	


	if( pclSummonOrder ) delete [] pclSummonOrder;
}


// ���� ȯ�� �λ縻ǥ��..
void cltSummonHeroMarketManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1852);
	SetMainExplain(hDlg, pText);
}

void cltSummonHeroMarketManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}


// ��ȯ���ŷ��Ҹ� �ż��Ѵ�.
BOOL cltSummonHeroMarketManager::CreateSummonHeroMarket(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltSummonHeroMarket(siunique);
		return TRUE;
	}

	return FALSE;
}

void cltSummonHeroMarketManager::AddOrder( cltSummonOrder *pclOrder )
{
	for( int i = siAddStartIndex; i < MAX_SUMMONHEROMARKET_ORDER_NUMBER; ++i ) {

		if( pclSummonOrder[ i ].siPersonID == 0 ) {

			pclSummonOrder[ i ].Set( pclOrder );
			
			siAddStartIndex = i + 1;
			
			++siTotalOrderNumber;
			
			break;
		}
	}
}

void cltSummonHeroMarketManager::DelOrder( SI32 orderIndex )
{
	int count = 0;

	for( int i = 0; i < MAX_SUMMONMARKET_ORDER_NUMBER; ++i ) {

		if( pclSummonOrder[ i ].siPersonID != 0 ) {
			++count;

			if( pclSummonOrder[ i ].siIndex == orderIndex ) {
				
				pclSummonOrder[ i ].Init();

				if( i < siAddStartIndex ) siAddStartIndex = i;
				--siTotalOrderNumber;

				break;
			}

		}

		if( count >= siTotalOrderNumber ) break;
	}

}

void cltSummonHeroMarketManager::UpdatePrice( int index, cltSummonOrder *pclOrder )
{
	
	if( pclSummonOrder[ index ].siIndex != pclOrder->siIndex ) return;

	if( pclSummonOrder[ index ].clSummon.siSummonID != pclOrder->clSummon.siSummonID ) return;

	pclSummonOrder[ index ].siPrice = pclOrder->siPrice;

	pclSummonOrder[ index ].clDate.Set( &pclOrder->clDate );

}


void cltSummonHeroMarketManager::Action( bool bdaychangedswitch )
{
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	//static SI32 marketitemindex	= 0;
	//---------------------------------------------------
	// ���� �ֹ� ������ �����Ѵ�. (������ 10%�� ����� ) 
	//---------------------------------------------------
	if(bdaychangedswitch)
	{
		// ��ü ���� �ֹ��� �˻��Ͽ� ��¥�� ���� �ð� �̻� ����� �ֹ��� ������ 10%�� �����. 
		// ������ ���̻� ���� �� ���� ��쿡�� �ֹ� ��ü�� �����Ѵ�.(��ǰ��)
		cltServer* pclserver = (cltServer* )pclClient;
		if(pclserver->pclTime != NULL)
		{
			cltSummonOrder clorder;
			SI32 curdate = pclserver->pclTime->clDate.GetDateVary();

			int count = 0;
			for( int i = 0; i < MAX_SUMMONHEROMARKET_ORDER_NUMBER; ++i ) {

				clorder.Set( &pclSummonOrder[ i ] );
				
				if( clorder.siPersonID != 0 ) {
					++count;

					if( curdate - clorder.clDate.GetDateVary() >= 30 ) {
						
						clorder.clDate.Set( &pclserver->pclTime->clDate );
						clorder.siPrice = clorder.siPrice * 9 / 10;

						if( clorder.siPrice < 3000 ) {
							clorder.siPrice = 0;
						}
						
						sDBRequest_ReduceSummonHeroOrderPrice clMsg( i, &clorder);
						pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}

				if( count >= siTotalOrderNumber ) break;
			}
		}
	}

}


void cltSummonHeroMarketManager::AddMyOrder( cltSummonOrder *pclOrder )
{
	for( int i = 0; i < MAX_SUMMONHEROMARKET_ORDER_PER_PERSON; i++ )
	{
		if( clMyOrder[ i ].siPersonID == 0 ) {

			clMyOrder[ i ].Set( pclOrder );
			break;
		}
	}
}

void cltSummonHeroMarketManager::DelMyOrder( SI32 orderIndex )
{
	for( int i = 0; i < MAX_SUMMONHEROMARKET_ORDER_PER_PERSON; i++ )
	{
		if( clMyOrder[ i ].siIndex == orderIndex ) {

			clMyOrder[ i ].Init();
			break;
		}
	}
}


