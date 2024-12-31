#pragma once

#include <Stdio.h>
#include "CommonLogic.h"
#include "../StructureClass/StructureClass.h"
#include "../Account/Account.h"
#include "../Client/Inventory/ItemInventoryBaseDefinition.h"
#include "../../Common/Item/ItemCommon/cltitem.h"

extern cltCommonLogic* pclClient;


class cltNewMarket : public cltStructureBasic
{
public:

	cltNewMarket(SI32 sivillageunique) : cltStructureBasic(sivillageunique){}
	~cltNewMarket(){}
};


class cltNewMarketTradeOrder
{
public:
	cltNewMarketTradeOrder() { ZeroMemory( this, sizeof(*this) ); }
	~cltNewMarketTradeOrder(){}

public:
	UI08		GetServerUnique( void )	{ return m_siServerUnique;													}
	GMONEY		GetMoney( void )		{ return m_siPrice;													}
	GMONEY		GetTotalMoney( void )	{ return m_siPrice * m_clItem.siItemNum;							}
	SI16		GetItemUnique( void )	{ return m_clItem.siUnique;											}
	SI16		GetItemNum( void )		{ return m_clItem.siItemNum;										}
	SI32		GetItemType( void )		{ return pclClient->pclItemManager->GetItemType(m_clItem.siUnique);	}
	SI32		GetDateVary( void )		{ return m_siDateVary;												}
	
	UI08		m_siServerUnique;		// ���� ����ũ.
	SI32		m_siOrderIndex;			// �ֹ� ������ �ĺ���
	SI32		m_siPersonID;			// �ֹ��� �� PersonID
	SI32		m_siDateVary;			// �ð� ����.(�ֹ��ð����� ó���ϴ� �ʹ��� �־�.)		
	GMONEY		m_siPrice;				// �ֹ� ���� ����. 
	cltItem		m_clItem;				// ������ ����.
};

class NewMarketTradeOrderManager
{
public:



};