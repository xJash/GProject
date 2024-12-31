#ifndef _MSGTYPEGACHA_H
#define _MSGTYPEGACHA_H

#include "../../server/GachaManager/GachaManager.h"
#include "../../server/Gacha2Manager/Gacha2Manager.h"

#include "../../../DBManager/GameDBManager_world/DBMsg-ItemMall.h"



// �����۸����� ��з��� �Һз��� �������� ��ǰ ����Ʈ�� ��û�Ѵ�.
class cltGameMsgRequest_GachaProduct_List
{
public:


	cltGameMsgRequest_GachaProduct_List()
	{
		
	}
};

class cltGameMsgResponse_GachaProduct_List
{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_GACHA_PRODUCT>		clItem;	//[����] ���� ����. �迭 ���� ����. 2008-8-29
#else
	cltItem	clItem[MAX_GACHA_PRODUCT]; // ��ǰ ����
#endif
	
	UI16 uiGachaCnt;

	cltGameMsgResponse_GachaProduct_List(cltItem * pclItem , UI16 GachaCnt)
	{
		
		for ( SI16 i = 0 ; i < MAX_GACHA_PRODUCT ; i ++ )
		{
			clItem[i].Set(&pclItem[i]);
		}

		uiGachaCnt = GachaCnt;
	}
};

class cltGameMsgRequest_GachaBuy
{
public:

	SI32 siUseKeyKind;

	cltGameMsgRequest_GachaBuy( SI32 UseKeyKind )
	{
		siUseKeyKind = UseKeyKind;
	}
};


class cltGameMsgResponse_GachaBuy
{
public:

	bool bBestProduct;
	cltItem clGetItem;
	UI16 uiGachaCnt;

	cltGameMsgResponse_GachaBuy( bool BestProduct , cltItem * GetItem , UI16 GachaCnt)
	{
        bBestProduct = BestProduct;
		clGetItem.Set(GetItem);
		uiGachaCnt = GachaCnt;
	}
};


// MAX_GACHA2_PRODUCT ���� �ٸ� �� �������� �ϳ��� ����� �ش�.
class cltGameMsgResponse_Gacha2Product_List
{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_GACHA2_PRODUCT>		clItem;	//[����] ���� ����. �迭 ���� ����. 2008-8-29
#else
	cltItem	clItem[MAX_GACHA2_PRODUCT]; // ��ǰ ����
#endif
	
	UI16 uiGachaCnt;

	cltGameMsgResponse_Gacha2Product_List(cltItem * pclItem , UI16 GachaCnt)
	{
		
		for ( SI16 i = 0 ; i < MAX_GACHA2_PRODUCT ; i ++ )
		{
			clItem[i].Set(&pclItem[i]);
		}

		uiGachaCnt = GachaCnt;
	}
};


class cltGameMsgResponse_CarryOver_Gacha_list
{
public:
	SI32	m_siTotalGachaList[TOTAL_GACHA_PRODUCT];

	UI16	m_uiGachaCnt;


	cltGameMsgResponse_CarryOver_Gacha_list( SI32* psiTotalGachaList, UI16 uiGachaCnt )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_CarryOver_Gacha_list) );

		memcpy( m_siTotalGachaList, psiTotalGachaList, sizeof(m_siTotalGachaList) );

		m_uiGachaCnt = uiGachaCnt;
	}
};

class cltGameMsgRequest_CarryOver_SelectProduct_List
{
public:

	SI32 m_siSelectIndex;
	SI32 m_siSelectUnique;

	SI32 m_siSelectKeyKind;

	cltGameMsgRequest_CarryOver_SelectProduct_List( SI32 siSelectIndex, SI32 siSelectUnique, SI32 siSelectKeyKind )
	{
		m_siSelectIndex		= siSelectIndex;
		m_siSelectUnique	= siSelectUnique;

		m_siSelectKeyKind	= siSelectKeyKind;
	}
};

class cltGameMsgResponse_CarryOver_SelectProduct_List
{
public:
	SI32 m_siProductList[MAX_GACHA_PRODUCT];

	cltGameMsgResponse_CarryOver_SelectProduct_List( SI32* psiProductList )
	{
		if ( psiProductList )
		{
			memcpy( m_siProductList, psiProductList, sizeof(m_siProductList) );
		}
	}
};

class cltGameMsgRequest_CarryOver_GachaBuy
{
public:
	SI32 m_siSelectIndex;
	SI32 m_siSelectUnique;

	SI32 m_siKeyKind;
	
	cltGameMsgRequest_CarryOver_GachaBuy( SI32 siSelectIndex, SI32 siSelectUnique, SI32 siKeyKind )
	{
		m_siSelectIndex		= siSelectIndex;
		m_siSelectUnique	= siSelectUnique;

		m_siKeyKind			= siKeyKind;
	}
};




#endif
