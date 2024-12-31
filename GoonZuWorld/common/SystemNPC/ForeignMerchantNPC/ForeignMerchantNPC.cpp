#include "ForeignMerchantNPC.h"

#include "..\..\Char\kindinfo\kindinfo.h"

#include "..\..\..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-ForeignMerchantNPC.h"

#include "..\..\..\CommonLogic\CommonLogic.h"
extern cltCommonLogic *pclClient;

CForeignMerchantNPC::CForeignMerchantNPC()
{	
	Initialize();
}

CForeignMerchantNPC::~CForeignMerchantNPC()
{
	Destroy();
}

void CForeignMerchantNPC::Initialize()
{
	m_bAvailable = false;

	m_siForeignMerchantKind = -1;

	m_siStatus = FOREIGNMERCHANT_STOP_STAUS;

	m_siBuyItemTotalNum = 0;

	m_siSaveLastBuyRestNum = 0;

	memset( &sForeignMerchantNPCInfo, 0, sizeof( stForeignMerchantNPCInfo ) );

	m_siBuyItemType = -1;

	return;
}

void CForeignMerchantNPC::Destroy()
{
	/*
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if ( m_siStatus == FOREIGNMERCHANT_BUY_STATUS )
		{
			cltServer *pclserver = (cltServer *)pclClient;

			// DB �� ���� NPC �V���� ������.
			sDBRequest_SetForeignMerchantNPCInfo clMsg(m_siForeignMerchantKind, sForeignMerchantNPCInfo.siBuyItemUnique, sForeignMerchantNPCInfo.siBuyItemAveragePrice, sForeignMerchantNPCInfo.siBuyItemRestNum, &sForeignMerchantNPCInfo.clDate );
			
			pclClient->SendDBMsg((sPacketHeader *)&clMsg);	
		}
	}
	*/
}

SI16 CForeignMerchantNPC::GetStatus()
{
	return m_siStatus;
}

SI16 CForeignMerchantNPC::GetForeignMerchantKind()
{
	return m_siForeignMerchantKind;
}


void CForeignMerchantNPC::SetKind( SI16 siForeignMerchantKind, SI16 siBuyItemType )
{
	m_siForeignMerchantKind = siForeignMerchantKind;
	m_siBuyItemType = siBuyItemType;
}

void CForeignMerchantNPC::Set( SI32 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount )
{
	for ( SI32 i = 0; i < siListCount; ++ i )
	{
		sForeignMerchantNPCInfo.siBuyItemUniqueList[ i ] = psiItemUniqueList[ i ];
		sForeignMerchantNPCInfo.siBuyItemPriceList[ i ] = psiItemPriceList[ i ];
	}

	sForeignMerchantNPCInfo.siForeignMerchantKind = m_siForeignMerchantKind;
	sForeignMerchantNPCInfo.siBuyItemType = m_siBuyItemType;
	sForeignMerchantNPCInfo.siBuyItemListCount = siListCount;
	m_siStatus = FOREIGNMERCHANT_BUY_STATUS;

	m_bAvailable = true;		// ���� NPC �� ������ �غ� �Ϸ� �Ǿ���.

	return;
}

void CForeignMerchantNPC::Set( SI16 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount )
{
	for ( SI32 i = 0; i < siListCount; ++ i )
	{
		sForeignMerchantNPCInfo.siBuyItemUniqueList[ i ] = psiItemUniqueList[ i ];
		sForeignMerchantNPCInfo.siBuyItemPriceList[ i ] = psiItemPriceList[ i ];
	}

	sForeignMerchantNPCInfo.siForeignMerchantKind = m_siForeignMerchantKind;
	sForeignMerchantNPCInfo.siBuyItemType = m_siBuyItemType;
	sForeignMerchantNPCInfo.siBuyItemListCount = siListCount;
	m_siStatus = FOREIGNMERCHANT_BUY_STATUS;

	m_bAvailable = true;		// ���� NPC �� ������ �غ� �Ϸ� �Ǿ���.

	return;
}

/*
// ����ũ ���� ���� �ü��� DB �� ���� �޾ƿ� �Է���
// ��¥�� �Ķ���� ����??
// �ּ� Ǯ�� ���� SI64�� �������ּ���!
void CForeignMerchantNPC::Set( SI16 siItemUnique, SI32 siItemAveragePrice, SI32 siBuyItemRestNum, cltDate clDate )
{
	if ( siItemUnique < 0 || siItemAveragePrice < 1 )
	{
		return;
	}

	m_siStatus = FOREIGNMERCHANT_BUY_STATUS;

	sForeignMerchantNPCInfo.siForeignMerchantKind = m_siForeignMerchantKind;

	sForeignMerchantNPCInfo.siBuyItemUnique = siItemUnique;
	sForeignMerchantNPCInfo.siBuyItemAveragePrice = siItemAveragePrice;	
	
	sForeignMerchantNPCInfo.siBuyItemRestNum = siBuyItemRestNum;



	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		m_siBuyItemTotalNum = MAX_FOREIGNMERCHANTNPC_BUY_ITEM_TOTAL_PRICE / siItemAveragePrice;

		cltServer *pclserver = (cltServer *)pclClient;	

		cltDate cldate;
		cldate.Set(&pclserver->pclTime->clDate);
		cldate.AddMonth(1);								// ���� �ִ� �ð��� 1����
		
		sForeignMerchantNPCInfo.clDate.Set( &cldate );


		// DB �� ���� NPC �V���� ������.
		sDBRequest_SetForeignMerchantNPCInfo clMsg(m_siForeignMerchantKind, siItemUnique, siItemAveragePrice, siBuyItemRestNum, &sForeignMerchantNPCInfo.clDate );
		
		pclClient->SendDBMsg((sPacketHeader *)&clMsg);	
	}
	else
	{
		sForeignMerchantNPCInfo.clDate.Set( &clDate );
	}



	m_bAvailable = true;		// ���� NPC �� ������ �غ� �Ϸ� �Ǿ���.

	return;
}
*/

// ���� ������ ����
stForeignMerchantNPCInfo* CForeignMerchantNPC::GetForeignMerchantNPCInfo()
{
	return &sForeignMerchantNPCInfo;
}

// ���� ������ ���ͼ� ���������.
void CForeignMerchantNPC::GetForeignMerchantNPCInfo( stForeignMerchantNPCInfo * pstForeignMerchantNPCInfo )
{
	memcpy( pstForeignMerchantNPCInfo, &sForeignMerchantNPCInfo, sizeof( stForeignMerchantNPCInfo ) );
}

/*
// return false �� ���� ���� �������� �־�� ��.
bool CForeignMerchantNPC::Buy( UI16 uiItemNum )
{
	if ( m_siStatus == FOREIGNMERCHANT_STOP_STAUS && uiItemNum < 1 )
	{
		return false;
	}

	sForeignMerchantNPCInfo.siBuyItemRestNum -= uiItemNum;

	if ( sForeignMerchantNPCInfo.siBuyItemRestNum < 1 )
	{
		m_siStatus = FOREIGNMERCHANT_STOP_STAUS;

		m_siBuyItemTotalNum = 0;

		sForeignMerchantNPCInfo.siBuyItemUnique = -1;
		sForeignMerchantNPCInfo.siBuyItemAveragePrice = -1;
		sForeignMerchantNPCInfo.siBuyItemRestNum = 0;

		return false;
	}

	return true;
}
*/

void CForeignMerchantNPC::GetBuyInfoText( TCHAR *pBuffer )
{
	if ( pBuffer == NULL )
	{
		return;
	}
}

bool CForeignMerchantNPC::IsAvailable()
{
	return m_bAvailable;
}

void CForeignMerchantNPC::RefreshPrice()
{
	if ( m_siForeignMerchantKind < 1 )
	{
		return;
	}

	SI32 siUniqueList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];
	GMONEY siPriceList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];
	SI32 siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( m_siBuyItemType, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( siUniqueList, siPriceList, siListCount );
	}

	return;
}

CForeignMerchantNPCMgr::CForeignMerchantNPCMgr()
{
	Initialize();
}

CForeignMerchantNPCMgr::~CForeignMerchantNPCMgr()
{	
	Destroy();
}

void CForeignMerchantNPCMgr::Initialize()
{
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		m_ForeignMerchant[ i ].Initialize();
	}
}

void CForeignMerchantNPCMgr::Destroy()
{
}

void CForeignMerchantNPCMgr::Add( SI16 siKind, SI16 siBuyItemType )
{
	// ������ NPC �� �����Ѵٸ�, �߰��� �ʿ�� �����Ƿ�...
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			return;
		}
	}

	for ( i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == -1 )
		{
			m_ForeignMerchant[ i ].SetKind( siKind, siBuyItemType );
			return;
		}
	}
}


void CForeignMerchantNPCMgr::Set( SI16 siKind, SI32 siBuyItemType, SI32 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount )
{
	// ������ NPC �� �����Ѵٸ�, �߰��� �ʿ�� �����Ƿ�...
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			m_ForeignMerchant[ i ].Set( psiItemUniqueList, psiItemPriceList, siListCount );			
			return;
		}
	}
	
	// ������ NPC�� �������� �ʴ´ٸ�, �߰��ϰ� ���� ����� ������...
	for ( i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == -1 )
		{	
			m_ForeignMerchant[ i ].SetKind( siKind, siBuyItemType );
			m_ForeignMerchant[ i ].Set( psiItemUniqueList, psiItemPriceList, siListCount );
			return;
		}
	}

//#ifdef _DEBUG
	pclClient->pclLog->FilePrint(TEXT("ForeignMerchantLog.txt"), TEXT("Set( SI16 siKind, SI32 siBuyItemType, SI32 *psiItemUniqueList, SI32 *psiItemPriceList, SI32 siListCount )���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );		
//#endif
	
	return;
}

void CForeignMerchantNPCMgr::Set( SI16 siKind, SI32 siBuyItemType, SI16 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount )
{
	// ������ NPC �� �����Ѵٸ�, �߰��� �ʿ�� �����Ƿ�...
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			m_ForeignMerchant[ i ].Set( psiItemUniqueList, psiItemPriceList, siListCount );
			return;
		}
	}
	
	// ������ NPC�� �������� �ʴ´ٸ�, �߰��ϰ� ���� ����� ������...
	for ( i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == -1 )
		{	
			m_ForeignMerchant[ i ].SetKind( siKind, siBuyItemType );
			m_ForeignMerchant[ i ].Set( psiItemUniqueList, psiItemPriceList, siListCount );
			return;
		}
	}

//#ifdef _DEBUG
	if (pclClient->GameMode == GAMEMODE_SERVER)
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("Set( SI16 siKind, SI32 siBuyItemType, SI16 *psiItemUniqueList, SI32 *psiItemPriceList, SI32 siListCount )���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );			
//#endif
	
	return;
}


/*
void CForeignMerchantNPCMgr::Set( SI16 siKind, SI16 siBuyItemUnique, SI32 siBuyItemAveragePrice, SI32 siBuyItemRestNum, cltDate	clDate )
{
	// ������ NPC �� �����Ѵٸ�, �߰��� �ʿ�� �����Ƿ�...
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			m_ForeignMerchant[ i ].Set( siBuyItemUnique, siBuyItemAveragePrice, siBuyItemRestNum, clDate );			
			return;
		}
	}
	
	// ������ NPC�� �������� �ʴ´ٸ�, �߰��ϰ� ���� ����� ������...
	for ( i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == -1 )
		{	
			m_ForeignMerchant[ i ].SetKind( siKind );
			m_ForeignMerchant[ i ].Set( siBuyItemUnique, siBuyItemAveragePrice, siBuyItemRestNum, clDate );
			return;
		}
	}

#ifdef _DEBUG
	pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("���� ���� ���� ã��?"), TEXT("���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );
#endif
	
	return;
}
*/

void CForeignMerchantNPCMgr::Action( cltTime *pTime )
{
	if ( pTime == NULL )					// ����� pTime == NULL �� ��찡 �ͼ�...
	{
		return;
	}

	if(  pTime->clDate.uiYear == 0 && pTime->clDate.uiMonth == 0 && pTime->clDate.uiDay == 0 && pTime->clDate.uiHour == 0 )			// �������� ���� �ð�
	{
		return;
	}
	
	if(pclClient->GetFrame() % 100 ) return ;

	/*
	// �������� ���� ��¥�� ��ȿ�� �ð�(pTime->clDate.uiYear >= 1)�� ��� �׸��� DB�� ���� ������ ���� �����

	if ( ++m_siSaveDelayCount > SAVE_TIME_FOREIGNMERCHANTNPC_BUY_INFO_TO_DB )
	{
		for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
		{
			m_ForeignMerchant[ i ].SaveDifferent();
		}

		m_siSaveDelayCount = 0;
	}
	*/
		
	//������ ���� �����̰ų�, �ֹ��� ���� ���¸� �ֹ��� �����, �ֹ��� �ִٸ� �׳� ����
	
	SI32 siUniqueList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];
	GMONEY siPriceList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];
	SI32 siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_HELMET, ITEMTYPE_HELMET );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_HELMET, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_HELMET, ITEMTYPE_HELMET, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_ARMOUR, ITEMTYPE_ARMOUR );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_ARMOUR, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_ARMOUR, ITEMTYPE_ARMOUR, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_AXE, ITEMTYPE_AXE );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_AXE, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_AXE, ITEMTYPE_AXE, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_SWORD, ITEMTYPE_SWORD );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_SWORD, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_SWORD, ITEMTYPE_SWORD, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_STAFF, ITEMTYPE_STAFF );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_STAFF, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_STAFF, ITEMTYPE_STAFF, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_SPEAR, ITEMTYPE_SPEAR );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_SPEAR, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_SPEAR, ITEMTYPE_SPEAR, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_GUN, ITEMTYPE_GUN );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_GUN, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_GUN, ITEMTYPE_GUN, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_BOW, ITEMTYPE_BOW );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_BOW, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_BOW, ITEMTYPE_BOW, siUniqueList, siPriceList, siListCount );
	}
		
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_SHOES, ITEMTYPE_SHOES );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_SHOES, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_SHOES, ITEMTYPE_SHOES, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_BELT, ITEMTYPE_BELT );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_BELT, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_BELT, ITEMTYPE_BELT, siUniqueList, siPriceList, siListCount );
	}
		
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_POTTER, ITEMTYPE_DISH );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_DISH, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_POTTER, ITEMTYPE_DISH, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_HARDWARE, ITEMTYPE_IRON );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_IRON, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_HARDWARE, ITEMTYPE_IRON, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_RING, ITEMTYPE_RING );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_RING, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_RING, ITEMTYPE_RING, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_CLOTHES, ITEMTYPE_DRESS );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_DRESS, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_CLOTHES, ITEMTYPE_DRESS, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_HAT, ITEMTYPE_HAT );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_HAT, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_HAT, ITEMTYPE_HAT, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_NECK, ITEMTYPE_NECK );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_NECK, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_NECK, ITEMTYPE_NECK, siUniqueList, siPriceList, siListCount );
	}
	
	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_PAPER, ITEMTYPE_PAPER );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_PAPER, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_PAPER, ITEMTYPE_PAPER, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_FISHING, ITEMTYPE_FISHINGROD );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_FISHINGROD, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_FISHING, ITEMTYPE_FISHINGROD, siUniqueList, siPriceList, siListCount );
	}

	siListCount = MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM;
	
	Add ( FOREIGNMERCHANT_CANNON, ITEMTYPE_CANNON );
	
	if ( pclClient->pclItemManager->GetForeignNPCItemInfo( ITEMTYPE_CANNON, siUniqueList, siPriceList, &siListCount ) == true )
	{
		Set( FOREIGNMERCHANT_CANNON, ITEMTYPE_CANNON, siUniqueList, siPriceList, siListCount );
	}

	

	return;
}

SI16 CForeignMerchantNPCMgr::GetStatus( SI16 siKind )
{
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			return m_ForeignMerchant[ i ].GetStatus();
		}
	}

	return FOREIGNMERCHANT_NOT_EXIST;
}

CForeignMerchantNPC *CForeignMerchantNPCMgr::GetForeignMerchantNPC( SI16 siKind )
{
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			return &m_ForeignMerchant[ i ];
		}
	}

//#ifdef _DEBUG
	if (pclClient->GameMode == GAMEMODE_SERVER)
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("GetForeignMerchantNPC���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );
//#endif
	return NULL;
}

stForeignMerchantNPCInfo* CForeignMerchantNPCMgr::GetForeignMerchantNPCInfo( SI16 siKind )
{
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			return m_ForeignMerchant[ i ].GetForeignMerchantNPCInfo();
		}
	}

//#ifdef _DEBUG
	if (pclClient->GameMode == GAMEMODE_SERVER)
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("GetForeignMerchantNPCInfo���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );	
//#endif
	return NULL;
}

void CForeignMerchantNPCMgr::GetBuyInfoText( SI16 siKind, TCHAR *pBuffer )
{
	for ( int i = 0; i < MAX_FOREIGNMERCHANTNPC_NUM; ++i )
	{
		if ( m_ForeignMerchant[ i ].GetForeignMerchantKind() == siKind )
		{
			m_ForeignMerchant[ i ].GetBuyInfoText( pBuffer );
			return;
		}
	}

//#ifdef _DEBUG
	if (pclClient->GameMode == GAMEMODE_SERVER)
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("GetBuyInfoText���� ���� ��ȣ �Դ�. ���ι�ȣ = %d"), siKind );		
//#endif

	return;
}
