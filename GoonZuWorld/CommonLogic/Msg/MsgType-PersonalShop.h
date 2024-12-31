#ifndef _MSGTYPEPERSONALSHOP_H
#define _MSGTYPEPERSONALSHOP_H

#include "Char/CharCommon/Char-Common.h"

//-------------------------------------------
// ���λ��� ��� �뺸. 
//-------------------------------------------
class cltGameMsgRequest_PersonalShopBanner{
public:
	SI16 siCharUnique;	
	cltGameMsgRequest_PersonalShopBanner(SI16 charunique)
	{
		siCharUnique = charunique;
	}
};

class cltGameMsgResponse_PersonalShopBanner{
public:
	SI16 siCharUnique;		// �Ӹ����� ����ϴ� ĳ������ ����ũ. 
	SI16 siResult;
	cltShopBannerData clShopBanner;

	cltGameMsgResponse_PersonalShopBanner(SI16 charunique, SI16 result, cltShopBannerData *pbannerdata)
	{
		siCharUnique = charunique;
		siResult     = result;

		clShopBanner.Set(pbannerdata);
	}
};


//-------------------------------------------
// ���λ��� ������ �뺸 
//-------------------------------------------
class cltGameMsgRequest_PersonalShopData{
public:
	SI16 siCharUnique;
	BOOL bManufacture;
	BOOL bMaker	;	// �ڽ��� ���������� �ƴ��� ǥ�� 
	
	cltGameMsgRequest_PersonalShopData(SI16 charunique,BOOL Manufacture, BOOL Maker ) // Manufacture �� ���̸� ������ ���� �Ƿ�
	{
		siCharUnique = charunique;
		bManufacture = Manufacture;
		bMaker = Maker;
	}
};

class cltGameMsgResponse_PersonalShopData{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	cltShopTradeData clShopData;
	
	cltGameMsgResponse_PersonalShopData(SI16 charunique, cltShopTradeData * pshopdata)
	{
		siCharUnique = charunique;
		clShopData.Set(pshopdata);
	}
};

//-------------------------------------------
// ���λ��� ��� ���� ���� 
//-------------------------------------------

class cltGameMsgResponse_UpdatePersonalShopBanner{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
	cltShopBannerData clShopBanner;

	cltGameMsgResponse_UpdatePersonalShopBanner(SI16 charunique, SI16 result, cltShopBannerData * pbannerdata)
	{
		siCharUnique = charunique;
		siResult	 = result;
		clShopBanner.Set(pbannerdata);
	}
};

//-------------------------------------------
// ���λ��� ������ ���� ���� 
//-------------------------------------------

class cltGameMsgResponse_UpdatePersonalShopData{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	cltShopTradeData clShopData;
	SI32 siItemUnique;
	SI32 siItemNum;
	GMONEY siItemCoast;
	
	BOOL bBuyer;


	cltGameMsgResponse_UpdatePersonalShopData(SI16 charunique, cltShopTradeData * pshopdata,SI32 itemunique = 0, SI32 itemnum = 0, GMONEY itemcoast = 0, BOOL buyer = FALSE)
	{
		siCharUnique = charunique;
		clShopData.Set(pshopdata);
		siItemUnique = itemunique;
		siItemNum = itemnum;
		
		siItemCoast = itemcoast;
		bBuyer = buyer;
	}
};


//-------------------------------------------
// ���λ��� ������ ���� 
//-------------------------------------------
class cltGameMsgRequest_StartPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 

	cltShopTradeData clShopData;

	cltGameMsgRequest_StartPersonalShop(SI16 charunique, cltShopTradeData * pshopdata)
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_StartPersonalShop));

		siCharUnique = charunique;
		clShopData.Set(pshopdata);
	}
};

class cltGameMsgResponse_StartPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
							// 0 : ���� 
							//-1 : [���λ����̿��]
	bool bPremium;			// �����̾� ����
	SI08 m_siShopMode;		// ���� ������ ���� ������� 

	cltGameMsgResponse_StartPersonalShop(SI16 charunique, SI16 shopresult,bool premium, SI08 siShopMode)
	{
		siCharUnique = charunique;
		siResult = shopresult;
		bPremium = premium;
		m_siShopMode = siShopMode;
	}

};

//-------------------------------------------
// ���λ��� ���� 
//-------------------------------------------
class cltGameMsgRequest_StopPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	cltGameMsgRequest_StopPersonalShop(SI16 charunique)
	{
		siCharUnique = charunique;
	}
};

class cltGameMsgResponse_StopPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI32 siPersonID;
	SI16 siResult;
	
	cltGameMsgResponse_StopPersonalShop(SI16 charunique, SI32 personid, SI16 result)
	{
		siCharUnique = charunique;
		siPersonID   = personid;
		siResult	 = result;
	}
};


//-------------------------------------------
// ������ ��ǰ���� 
//-------------------------------------------

#define BUYPERSONALSHOP_SUCCESS_BUY			 1	// ���� ����. 
#define BUYPERSONALSHOP_FAIL_UNKNOWN		 0	// ���� ���� 
#define BUYPERSONALSHOP_FAIL_SHOPPERSTATUS  -1	// ���� ���� - ���� ���� ������ �ٲ����.
#define BUYPERSONALSHOP_FAIL_BUYERSTATUS    -2	// ���� ���� - �������� ������ ������ �ִ�.
#define BUYPERSONALSHOP_FAIL_SHOWCASESTATUS -3	// ���� ���� - ������ ��ǰ ������ �ٲ����.
#define BUYPERSONALSHOP_FAIL_BUY_NOITEM		-4	// ���� ���� - ���������� ������ ��� 
#define BUYPERSONALSHOP_FAIL_BUY_NOMONEY	-5	// ���� ���� - �����ڰ�   ���� ��� 
#define BUYPERSONALSHOP_FAIL_BUY_NOINVSPACE	-6	// ���� ���� - �������� �κ��丮�� �����ִ�.


class cltGameMsgRequest_BuyPersonalShop{
public:

	// ���������� ���� 
	SI16			siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI08		    siShopMode;		// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	SI32			siPersonID;

	cltItem			clItem;
	GMONEY			siPrice;
	SI16			siShowcaseIndex;

	cltGameMsgRequest_BuyPersonalShop(SI16 charunique, SI08 shopmode, SI32 personid, cltItem *pitem, GMONEY price, SI16 showcaseindex )
	{
		siCharUnique = charunique;
		siShopMode   = shopmode;
		siPersonID   = personid;
		clItem.Set(pitem);
		siPrice		= price;
		siShowcaseIndex = showcaseindex;
	}
};

class cltGameMsgResponse_BuyPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
	SI32 siitemUnique;
	SI32 siItemNum;
	SI32 siItemCoast;
	cltGameMsgResponse_BuyPersonalShop(SI16 charunique, SI16 shopresult, SI32 itemunique, SI32 itemnum = 0)
	{
		siCharUnique = charunique;
		siResult     = shopresult;
		siitemUnique = itemunique;
		siItemNum    = itemnum;

	}
};

//-------------------------------------------
// ������ ��ǰ�Ǹ� 
//-------------------------------------------
#define SELLPERSONALSHOP_SUCCESS_SELL			 1	// �Ǹ� ����. 
#define SELLPERSONALSHOP_FAIL_UNKNOWN			 0	// �Ǹ� ���� 
#define SELLPERSONALSHOP_FAIL_SHOPPERSTATUS		-1	// �Ǹ� ���� - ���� ���� ������ �ٲ����.
#define SELLPERSONALSHOP_FAIL_SELLERSTATUS		-2	// �Ǹ� ���� - �Ǹ����� ������ ������ �ִ�.
#define SELLPERSONALSHOP_FAIL_SHOWCASESTATUS	-3	// �Ǹ� ���� - ������ ��ǰ ������ �ٲ����.
#define SELLPERSONALSHOP_FAIL_SELL_NOITEM		-4	// �Ǹ� ���� - �Ǹ����� ������ ��� 
#define SELLPERSONALSHOP_FAIL_SELL_NOMONEY		-5	// �Ǹ� ���� - ���������� ���� ��� 
#define SELLPERSONALSHOP_FAIL_SELL_NOINVSPACE	-6	// �Ǹ� ���� - ���������� �κ��丮�� �����ִ�.


class cltGameMsgRequest_SellPersonalShop{
public:
	// ���������� ���� 
	SI16			siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI08		    siShopMode;		// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	SI32			siPersonID;

	cltItem			clItem;
	GMONEY			siPrice;
	SI16			siShowcaseIndex;	
	SI16			siSellerInventoryRealIndex;

	cltGameMsgRequest_SellPersonalShop(SI16 charunique, SI08 shopmode, SI32 personid, cltItem *pitem, GMONEY price, SI16 showcaseindex, SI16 sellerinvindex )
	{
		siCharUnique = charunique;
		siShopMode   = shopmode;
		siPersonID   = personid;
		clItem.Set(pitem);
		siPrice		= price;
		siShowcaseIndex = showcaseindex;
		siSellerInventoryRealIndex = sellerinvindex;
	}
};

class cltGameMsgResponse_SellPersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
	SI32 siitemUnique;
	SI32 siItemNum;
	SI32 siItemCoast;
	cltGameMsgResponse_SellPersonalShop(SI16 charunique, SI16 shopresult, SI32 itemunique, SI32 itemnum = 0)
	{
		siCharUnique = charunique;
		siResult     = shopresult;
		siitemUnique = itemunique;
		siItemNum    = itemnum;

	}
};


//-------------------------------------------
// ������ ��ǰ���� 
//-------------------------------------------
#define MAKEPERSONALSHOP_SUCCESS_MAKE			 1	// ���� ����. 
#define MAKEPERSONALSHOP_FAIL_UNKNOWN			 0	// ���� ���� 
#define MAKEPERSONALSHOP_FAIL_SHOPPERSTATUS		-1	// ���� ���� - ���� ���� ������ �ٲ����.
#define MAKEPERSONALSHOP_FAIL_MAKERSTATUS		-2	// ���� ���� - ��������  ������ ������ �ִ�.
#define MAKEPERSONALSHOP_FAIL_SHOWCASESTATUS	-3	// ���� ���� - ������ ��ǰ ������ �ٲ����.
#define MAKEPERSONALSHOP_FAIL_MAKE_NOITEM		-4	// ���� ���� - ���������� �Ƿ� ������ ��� 
#define MAKEPERSONALSHOP_FAIL_MAKE_NOMONEY		-5	// ���� ���� - ���������� ���� ��� 
#define MAKEPERSONALSHOP_FAIL_MAKE_NEEDABILITY	-6	// ���� ���� - �������� �ɷ��� �����ϴ�.
#define MAKEPERSONALSHOP_FAIL_NOWMAKINGSTATUS	-7	// ���� ���� - �ٸ������ ������ ���� ���̴�.


class cltGameMsgRequest_MakePersonalShop{
public:

	// ���������� ���� 
	SI16			siCharUnique;	// ���λ����� ����  ĳ������ ����ũ. 
	SI08		    siShopMode;		// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	SI32			siPersonID;

	cltItem			clItem;
	GMONEY			siPrice;
	SI16			siHandPoint;
	SI16			siSkillLevel;
	SI16			siShowcaseIndex;
	
	SI08			siType;

	cltGameMsgRequest_MakePersonalShop(SI16 charunique, SI08 shopmode, SI32 personid, cltItem *pitem, GMONEY price, SI16 handpoint, SI16 skilllevel,SI16 showcaseindex,SI08 type )
	{
		siCharUnique = charunique;
		siShopMode   = shopmode;
		siPersonID   = personid;
		clItem.Set(pitem);
		siPrice		= price;
		siHandPoint  = handpoint;
		siSkillLevel = skilllevel;
		siShowcaseIndex = showcaseindex;

		siType = type;
	}
};

class cltGameMsgResponse_MakePersonalShop{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
	SI32 siitemUnique;
	SI32 siItemNum;
	cltGameMsgResponse_MakePersonalShop(SI16 charunique, SI16 shopresult, SI32 itemunique, SI32 itemnum)
	{
		siCharUnique = charunique;
		siResult     = shopresult;
		siitemUnique = itemunique;
		siItemNum    = itemnum;
	}
};

class cltGameMsgRequest_MakePersonalShop_Manufactuer{
public:

	// ���������� ���� 
	SI16			siCharUnique;	// ���λ����� ����  ĳ������ ����ũ. 
	SI08		    siShopMode;		// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	SI32			siPersonID;

	cltItem			clItem;
	GMONEY			siPrice;
	SI16			siHandPoint;
	SI16			siSkillLevel;
	SI16			siShowcaseIndex;

	SI08			siType;

	cltGameMsgRequest_MakePersonalShop_Manufactuer(SI16 charunique, SI08 shopmode, SI32 personid, cltItem *pitem, GMONEY price, SI16 handpoint, SI16 skilllevel,SI16 showcaseindex,SI08 type )
	{
		siCharUnique = charunique;
		siShopMode   = shopmode;
		siPersonID   = personid;
		clItem.Set(pitem);
		siPrice		= price;
		siHandPoint  = handpoint;
		siSkillLevel = skilllevel;
		siShowcaseIndex = showcaseindex;

		siType = type;
	}
};

class cltGameMsgResponse_MakePersonalShop_Manufacture{
public:
	SI16 siCharUnique;		// ���λ����� ����  ĳ������ ����ũ. 
	SI16 siResult;			// ���λ����� ���п��� 
	SI32 siitemUnique;
	SI32 siItemNum;
	cltGameMsgResponse_MakePersonalShop_Manufacture(SI16 charunique, SI16 shopresult, SI32 itemunique, SI32 itemnum)
	{
		siCharUnique = charunique;
		siResult     = shopresult;
		siitemUnique = itemunique;
		siItemNum    = itemnum;
	}
};

//-------------------------------------------
// ���� �˻� 
//-------------------------------------------
class cltGameMsgRequest_SearchPersonalShopItem{
public:
	SI32 siShopMode;
	SI32 siItemUniqueType;		// �˻� ��ǰ Unique
	GMONEY siMaxPrice;			// ���������� ��ǰ �˻� 
	cltGameMsgRequest_SearchPersonalShopItem(SI32 shopmode, SI32 itemuniquetype, GMONEY maxprice)
	{
		siShopMode   = shopmode;
		siItemUniqueType = itemuniquetype;
		siMaxPrice   = maxprice;
	}
};

class cltGameMsgResponse_SearchPersonalShopItem{
public:
	SI16 siResult;
	cltSearchShopData	clSearchShopData;
	
	cltGameMsgResponse_SearchPersonalShopItem(SI16 result, cltSearchShopData *psearchshopdata)
	{
		siResult	 = result;
		clSearchShopData.Set(psearchshopdata);
	}
};

class cltGameMsgRequest_SearchManufacture{
public:
	SI32 siShopMode;
	SI32 siItemUniqueType;		// �˻� ��ǰ Unique
	cltGameMsgRequest_SearchManufacture(SI32 shopmode, SI32 itemuniquetype)
	{
		siShopMode   = shopmode;
		siItemUniqueType = itemuniquetype;
	}
};

class cltGameMsgResponse_SearchManufacture{
public:
	SI16 siResult;
	cltSearchShopData	clSearchShopData;

	cltGameMsgResponse_SearchManufacture(SI16 result, cltSearchShopData *psearchshopdata)
	{
		siResult	 = result;
		clSearchShopData.Set(psearchshopdata);
	}
};


#endif