//---------------------------------
// 2003/9/27 ���°�
//---------------------------------

#ifndef _LETTER_H
#define _LETTER_H

#define MAX_LETTER_SIZE		64
#define MAX_LETTER_NUMBER	10

#define MAX_ACCOUNTLETTER_SIZE	512

#include <Directives.h>

#include <CommonHeader.h>
#include "..\..\Server\Time\MyTime.h"
#include "../../CommonLogic/Guild/Guild.h"
#include "../SystemReward/SystemReward.h"


#define LETTERTYPE_FIRE								1	// ���� ����. 
#define LETTERTYPE_BERANK							2	// �Ӹ� ����. 
#define LETTERTYPE_RECALLHOUSE						3	// ���� ȸ��. 
#define LETTERTYPE_PAYRENTFEE						4	// ���� �Ӵ�� ����
#define LETTERTYPE_STOCKTRADE						5	// �ֽ� �ŷ� ����. 
#define LETTERTYPE_MARKETTRADE						6	// ���ֿ��� ���� �ȸ� �뺸. 
#define LETTERTYPE_MARKETPRICEDOWN					7	// ���ֿ� �÷� ���� ���� ���� ���ϵ�
#define LETTERTYPE_HOUSERECALLWARINING				8	// ���� ȸ�� ���� ���. 
#define LETTERTYPE_RENTHOUSE						9	// ���� ������ ����Ǿ���. 
#define LETTERTYPE_GETDIVIDEND						10	// �ֽ� ����� �޾Ҵ�. 
#define LETTERTYPE_FATHER							11	// ���´� ����/���� 
#define LETTERTYPE_CHILDLEVELUP						12	// ���� ���� ������ ���� ���� 
#define LETTERTYPE_GETSALARY						13	// ����/��� ���η� ���/����� �޿� ���� ����. 
#define LETTERTYPE_MAIL								14	// ������ �����߽��ϴ�.  
#define LETTERTYPE_RECOMMENDER						15	// ��õ�� ��� �Ϸ�
#define LETTERTYPE_RECOMMENDERLEVELUP				16	// ��õ�� ������
#define LETTERTYPE_STOCKLOSS						17  // ���� �й�� �ֽ��� �Ұ� ���ߴ�
#define LETTERTYPE_KINGPAY							18	// ���� ������� ����(��)�� ������ �Ϻθ� ����
#define LETTERTYPE_RESIDENTSHARE					19	// ���� �ֹ� ����
#define LETTERTYPE_HORSEMARKETTRADE					20  // �纹�ÿ��� �� �ȸ� �뺸
#define LETTERTYPE_HORSEMARKETPRICEDOWN				21  // �纹�ÿ� �÷� ���� ���� ������ ���ϵ� 
#define LETTERTYPE_STRUCTUREREPAIRITEM				25	// �ǹ� ������ �ʿ��� �������� ������� �˸�
#define LETTERTYPE_REALESTATEMARKETTRADE			26	// �Ű����� �ε��� �ȸ� �뺸 
#define LETTERTYPE_REALESTATEMARKETPRICEDOWN		27	// �Ű��� �ε��� �ֹ��� ������ ���ϵ�
#define LETTERTYPE_SUMMONMARKETTRADE				28	// �忹������ ��ȯ�� �ȸ� �뺸 
#define LETTERTYPE_SUMMONMARKETPRICEDOWN			29	// �忹������ ��ȯ�� �ֹ��� ������ ���ϵ�
#define LETTERTYPE_RESIDENTOUTDATE					30  // �ֹ� �ڵ� Ż�� (1���̻� ���� ���� ���� �ֹ�)
#define LETTERTYPE_RESULTBIDSTOCK					31  // ���� ���� (���)
#define LETTERTYPE_RENTLAND							34  // ���� ������ ����Ǿ��� 
#define LETTERTYPE_PAYLANDRENTFEE					35	// ���� �Ӵ�� ���� 
#define LETTERTYPE_LANDRECALL						36  // ���� ȸ��
#define LETTERTYPE_LANDRECALLWARNING				37  // ���� ȸ�� ���
#define LETTERTYPE_HOZOANGEL						38	// ��ȣõ�� ����
#define LETTERTYPE_CHIEFOUTWARNING					39	// ����� �ӱ� ������ �˸� 
#define LETTERTYPE_CHIEFOUTDATE						40	// ����� �ӱ� ����
#define LETTERTYPE_GENERALMEETING					41	// ���� �������� �ֽ��� �������� ������ȸ ������.
#define LETTERTYPE_SUMMONHEROMARKETTRADE			42	// �񺯻翡�� ��ȯ���� �ȸ� �뺸 
#define LETTERTYPE_SUMMONHEROMARKETPRICEDOWN		43	// �񺯻翡�� ��ȯ���� �ֹ��� ������ ���ϵ�
#define LETTERTYPE_POSTOFFICE_SENDOK				44	// �������� ���� ��ǰ�̳� ������ ���濡�� ���������� �뺸

#define LETTERTYPE_RENTMINE							45  // ���� ������ ����Ǿ��� 
#define LETTERTYPE_PAYMINERENTFEE					46	// ���� �Ӵ�� ���� 
#define LETTERTYPE_MINERECALL						47  // ���� ȸ��
#define LETTERTYPE_MINERECALLWARNING				48  // ���� ȸ�� ���

#define LETTERTYPE_VILLAGENAME_AND_DATE				49	// �ش� ���� �̸� �� �Ͻ� (��, ���� �Ļ� ��� �� �Ļ��Կ� ����)

#define LETTERTYPE_HYUNGZOPOLICE					51	// ���� ���� ����
#define LETTERTYPE_EXISTENT_SAVEUSERITEM			52	// ���� ���� ���ؼ� DB�� �������� �ִٴ� �޼���
#define LETTERTYPE_STOCKOFFERING_RESULT				53	// �ֽ� ���� ��û ��÷ ��� �뺸

#define ACCOUNT_LETTERTYPE_PRESENT					54	// ���� ���� �޽���

#define ACCOUNT_LETTERTYPE_PRESENTANSWER			55	// ���� ���� �޽���
#define LETTERTYPE_WORLDMONEYTRADERESULT			56	// ���� �Ӵ� �ŷ� ���
#define LETTERTYPE_TRADESERVER_SELL					57	// ���� �ŷ�

#define LETTERTYPE_CHANGERECOMMENDPOINT				58
#define LETTERTYPE_LEVELUPRECOMMANDREWARD			59

#define LETTERTYPE_WORLDMONEY_REDUCE_PRICE			60	// ����

#define LETTERTYPE_LEVELUPRECOMMANDREWARD_FOR_RECOMMENDER			61

#define LETTERTYPE_GUILDJOIN							62			// ��� ���Կ� ���� ��
#define LETTERTYPE_GUILD_CONFIRMCREATEGUILD				63			// ��� ������ ���� ��
#define LETTERTYPE_GUILD_SECONDMASTER					64			// ��� ���Ǽ� �Ӹ� ���� ��
#define LETTERTYPE_GUILD_CHANGEMASTER					65			// ���� ������ ����
#define LETTERTYPE_GUILD_CONFIRMCHANGEVILLAGE			66			// ��� ���� ����
#define LETTERTYPE_GUILD_SUCCESSRESERVE					67			// ����� ����!!
#define	LETTERTYPE_GUILD_DESTROY						68			// ��尡 ��������
#define LETTERTYPE_GUILDDUNGEON_APPLY					69			// ����� ������ ������û
#define LETTERTYPE_GUILDDUNGEON_CHANGEGPMONEY			70			// ����� �����ǿ� ���� GP, MONEY ȹ��
#define LETTERTYPE_GUILDDUNGEON_GETOWNERSHIP			71			// ����� ������ ȹ��
#define LETTERTYPE_RENOUNCEPUPIL						72			// ������ ���ڸ� ¥����.
#define LETTERTYPE_ACCEPTFRIEND_RESULT					73			// ģ������ϱ��� ���
#define LETTERTYPE_TEACHERREWARD_PUPILREWARD			74			// �������� ���� ������ �޼��� ������
#define LETTERTYPE_PVPRESULT							75			// PVP���
#define LETTERTYPE_GUILD_ALERTDESTROY					76			// ��� ��ü ���
#define LETTERTYPE_SYSTEMREWARD_GIVE					77			// ����NPC ���� ���� ����.
#define LETTERTYPE_GUILD_CHANGEMASTER_NOTCONNECT_MONTH	78			// ���� ������ ����
#define LETTERTYPE_INVITE_APPLYRESIDENT					79			// ����ĳ���� ����ĳ���� ������ �ʴ��Ͽ����� ���ֿ��� ����. 
#define	LETTERTYPE_CREATECHARREWARD						80			// �ɸ��� ������ ���� ������ ���� �޽���
#define LETTERTYPE_GUILDDUNGEON_APPLY_NEW				81			// ���ο� ����� ������ ������û
#define LETTERTYPE_WEDDINGCEREMONY_CANCEL				82			// ������ ��ҵ�
#define LETTERTYPE_FAMILY_DEL_FAMILY					83			// �������� ���� �Ǽ̽��ϴ�.
#define LETTERTYPE_FAMILY_LEAVE_FAMILY					84			// �������� ������..
#define LETTERTYPE_FAMILY_ADD_FAMILY					85			// ������ �ڽ��� ��� �Ͽ���._���� ����
#define LETTERTYPE_FAMILY_ADD_FAMILY_TO_ME				86			// ������ �ڽ��� ��� �Ͽ���.-�� ���� 
#define LETTERTYPE_DORMANCY_WARING_EXPIRATION			87			// �޸� ���� ���� ���
#define LETTERTYPE_SKILLBOOK_MAGIC_DEL					88			// ��ų������ ȹ���� ������ ������ �˸�.

class cltLetterHeader{
public:
	SI16 siType;
	SI16 siSize;

	cltLetterHeader()
	{
		siType	= 0;
		siSize	= 0;
	}
};

//#if	defined(_CITYHALL_BANKRUPTCY)

	//-------------------------------------------
	// ������/�ð�/Ÿ�� Letter
	// - ���� �Ļ� �溸 �� �Ļ� �˸� ( ���� : �����̸�, �ð� )
	//-------------------------------------------
	class cltLetterMsg_VillageNameAndDate{
	public:
		enum {
			LETTERTYPE_CITYHALLBANKRUPTCY_ALERT = 0,
			LETTERTYPE_CITYHALLBANKRUPTED = 1,
			LETTERTYPE_RETURNSTOCKBIDVILLAGE = 2,

			LETTERTYPE_END,
		};

		cltLetterHeader clHeader;

		SI32			siVillageUnique;			//  ��� ���� �̸� (��, �Ļ� ���� ���� )
		cltDate			clDate;						//  ��� �ð� (��, �Ļ� ���� �ð� Ȥ�� �Ļ���)
		UI08			usType;						// 

		cltLetterMsg_VillageNameAndDate( SI32 villageunique, cltDate* pcldate, UI08 ustype)
		{
			clHeader.siType = LETTERTYPE_VILLAGENAME_AND_DATE;
			clHeader.siSize	= sizeof(cltLetterMsg_VillageNameAndDate);

			siVillageUnique = villageunique;
			clDate.Set( pcldate );
			usType = ustype;
		}
	};

//#endif

//-------------------------------------------
// ��õ�� ����� ������ �ؼ� ��õ�� ����� ���̶� ����ġ �޴°�
//-------------------------------------------
class cltLetterMsg_RecommenderLevelUp
{
public:
	cltLetterHeader clHeader;

	SI16 siIncLevel;						// ��õ�� ����� ���� 
	TCHAR szName[MAX_PLAYER_NAME];
	SI16 siItemUnique;						// ���� ��ǰ ����ũ. 
	SI16 siItemNum;							// ���� ��ǰ ����. 
	SI16 siFameExp;

	cltLetterMsg_RecommenderLevelUp( SI16 IncLevel, TCHAR* pname, SI16 itemunique, SI16 itemnum, SI16 fameexp)
	{
		clHeader.siType = LETTERTYPE_RECOMMENDERLEVELUP;
		clHeader.siSize	= sizeof(cltLetterMsg_RecommenderLevelUp);

		siIncLevel = IncLevel;
		StringCchCopy(szName, MAX_PLAYER_NAME, pname);
		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		siFameExp		= fameexp;
	}
};




//-------------------------------------------
// ��õ�� ���
//-------------------------------------------
class cltLetterMsg_Recommender{
public:
	cltLetterHeader clHeader;

	TCHAR szRecommenderName[MAX_PLAYER_NAME];

	cltLetterMsg_Recommender(TCHAR* pname)
	{
		clHeader.siType = LETTERTYPE_RECOMMENDER;
		clHeader.siSize	= sizeof(cltLetterMsg_Recommender);

		StringCchCopy(szRecommenderName, MAX_PLAYER_NAME, pname);
	}
};

//-------------------------------------------
// ������ ����
//-------------------------------------------
class cltLetterMsg_Mail{
public:
	cltLetterHeader clHeader;

	TCHAR szFromPersonName[MAX_PLAYER_NAME];

	cltLetterMsg_Mail(TCHAR* pname)
	{
		clHeader.siType = LETTERTYPE_MAIL;
		clHeader.siSize	= sizeof(cltLetterMsg_Mail);

		StringCchCopy(szFromPersonName, MAX_PLAYER_NAME, pname);
	}
};

//-------------------------------------------
// ����/��翡 ���� ���� ����. 
//-------------------------------------------
class cltLetterMsg_GetSalary{
public:
	cltLetterHeader clHeader;

	cltSimpleRank	clRank;					// ������. 
	GMONEY			siMoney;				// ���ɾ�.

	cltLetterMsg_GetSalary(cltSimpleRank* pclRank, GMONEY money)
	{
		clHeader.siType = LETTERTYPE_GETSALARY;
		clHeader.siSize	= sizeof(cltLetterMsg_GetSalary);

		clRank.Set(pclRank);
		siMoney	= money;
	}
};

//-------------------------------------------
// ���� ���������� ���� ����� ���� 
//-------------------------------------------
class cltLetterMsg_ChildLevelUp{
public:
	cltLetterHeader clHeader;

	enum { FATHERREWARD = 0, 
		   GRANDFATHERREWARD, 
		   PUPILREWARD };

	SI16 siIncLevel;						// ������ ������ ���� 
	TCHAR szChildName[MAX_PLAYER_NAME];
	GMONEY siMoney;							// �����. 
	SI32 siFameExp;							// �� ����ġ. 
	UI08 uiType;


	cltLetterMsg_ChildLevelUp( SI16 inclevel, TCHAR* pname, GMONEY money, SI32 fameexp, UI08 Type = FATHERREWARD )
	{
		clHeader.siType = LETTERTYPE_CHILDLEVELUP;
		clHeader.siSize	= sizeof(cltLetterMsg_ChildLevelUp);

		siIncLevel	= inclevel;

		StringCchCopy(szChildName, MAX_PLAYER_NAME, pname);

		siMoney		= money;
		siFameExp	= fameexp;
		uiType = Type;
	}
};

//-------------------------------------------
// ���� ���� ���� 
//-------------------------------------------
class cltLetterMsg_Father{
public:
	cltLetterHeader clHeader;

	bool bFatherSwitch;			// ���� �Ӹ�/���� 
	TCHAR szChildName[MAX_PLAYER_NAME];


	cltLetterMsg_Father(bool bfatherswitch, TCHAR* pname)
	{
		clHeader.siType = LETTERTYPE_FATHER;
		clHeader.siSize	= sizeof(cltLetterMsg_Father);

		bFatherSwitch	= bfatherswitch;
		StringCchCopy(szChildName, MAX_PLAYER_NAME, pname);
	}
};

//-------------------------------------------
// �ֽ� ����� ����. 
//-------------------------------------------
class cltLetterMsg_GetDividend{
public:
	cltLetterHeader clHeader;

	SI08 siType;					// 0 : ���� 1: �ֹ�
	SI16 siVillageUnique;			// ��� ���� �ֽ��ΰ�. 
	GMONEY siMoney;					// ��� ���� �ݾ�. 

	cltLetterMsg_GetDividend(SI16 villageunique, GMONEY money, SI08 type = 0)
	{
		clHeader.siType = LETTERTYPE_GETDIVIDEND;
		clHeader.siSize	= sizeof(cltLetterMsg_GetDividend);

		siVillageUnique	= villageunique;
		siMoney			= money;
		siType			= type;
	}
};


//-------------------------------------------
// ���ֿ� �÷� ���� ���ǰ� ���� �뺸. 
//-------------------------------------------
class cltLetterMsg_MarketPriceDown{
public:
	enum
	{
		TYPE_MARKET = 0,
		TYPE_NEWMARKET
	};

	cltLetterHeader clHeader;

	SI16 siItemUnique;			// ��� ��ǰ. 
	SI16 siItemNum;				// �÷� ���� ���� 

	GMONEY siPrice;				// ���ϵ� �ݾ�. 
	UI08 uiType;

	cltLetterMsg_MarketPriceDown(SI16 itemunique, SI16 itemnum, GMONEY price, UI08 type = TYPE_MARKET)
	{
		clHeader.siType = LETTERTYPE_MARKETPRICEDOWN;
		clHeader.siSize	= sizeof(cltLetterMsg_MarketPriceDown);

		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		siPrice			= price;
		uiType			= type;
	}
};

//-------------------------------------------
// ���ֿ��� ���� �ȸ� �뺸. 
//-------------------------------------------
class cltLetterMsg_MarketTrade{
public:
	cltLetterHeader clHeader;

	enum
	{
		TYPE_MARKET = 0,
		TYPE_NEWMARKET
	};

	SI16	siItemUnique;			// ��� ��ǰ. 
	SI16	siItemNum;				// �ŷ�����. 

	GMONEY	siTradeMoney;			// �ŷ� ���. 	
	GMONEY	siFee;					// ���� ������. 
	UI08	uiType;

	cltLetterMsg_MarketTrade(SI16 itemunique, SI16 itemnum, GMONEY trademoney, GMONEY fee, UI08 type = cltLetterMsg_MarketTrade::TYPE_MARKET)
	{
		clHeader.siType = LETTERTYPE_MARKETTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_MarketTrade);

		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		siTradeMoney	= trademoney;
		siFee			= fee;
		uiType			= type;
	}
};

//-------------------------------------------
// �纹�ÿ��� �� �ȸ� �뺸. 
//-------------------------------------------
class cltLetterMsg_HorseMarketTrade{
public:
	cltLetterHeader clHeader;

	GMONEY siTradeMoney;			// �ŷ� ���. 	
	GMONEY siFee;					// ���� ������. 

	cltLetterMsg_HorseMarketTrade( GMONEY trademoney, GMONEY fee )
	{
		clHeader.siType = LETTERTYPE_HORSEMARKETTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_HorseMarketTrade);

		siTradeMoney	= trademoney;
		siFee			= fee;
	}
};


//-------------------------------------------
// �纹�ÿ� �÷� ���� �� ���� ���� �뺸. 
//-------------------------------------------
class cltLetterMsg_HorseMarketPriceDown{
public:
	cltLetterHeader clHeader;

	TCHAR	szHorseName[ MAX_HORSE_NAME ];		
	GMONEY	siPrice;								// ���ϵ� �ݾ�. 

	cltLetterMsg_HorseMarketPriceDown( TCHAR *szhorsename, GMONEY price)
	{
		clHeader.siType = LETTERTYPE_HORSEMARKETPRICEDOWN;
		clHeader.siSize	= sizeof( cltLetterMsg_HorseMarketPriceDown );

		StringCchCopy( szHorseName, MAX_HORSE_NAME, szhorsename );
		siPrice = price;
	}
};


//-------------------------------------------
// �ֽ� ó�� ����.����. 
//-------------------------------------------
class cltLetterMsg_StockTrade{
public:
	cltLetterHeader clHeader;

	SI16 siVillageUnique;			// ��� �ֽ�. 
	SI16 siOrderMode;

	SI32 siTradeAmount;				// ó�� ��. 
	SI32 siLeftAmount;				// ���� �ֽ� ��. 
	GMONEY siTradeMoney;				// �ֽ� ó������ ���� �� ȹ�� �ݾ�. 
	GMONEY siFee;						// ���ҵ� ������. 

	cltLetterMsg_StockTrade(SI16 villageunique, SI16 ordermode, SI32 tradeamount, SI32 leftamount, GMONEY trademoney, GMONEY fee)
	{
		clHeader.siType = LETTERTYPE_STOCKTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_StockTrade);

		siVillageUnique = villageunique;
		siOrderMode		= ordermode;

		siTradeAmount	= tradeamount;
		siLeftAmount	= leftamount;
		siTradeMoney	= trademoney;
		siFee			= fee;
	}
};


//-------------------------------------------
// �����Ӵ�� ����  ���� ����. 
//-------------------------------------------
class cltLetterMsg_PayRentFee{
public:
	cltLetterHeader clHeader;

	SI32 siVillageUnique;			// ������ �ִ� ������ ����ũ. 
	SI32 siHouseIndex;				// ���� ������ �ּ�. 
	GMONEY siRentFee;					// �Ӵ��. 
	SI32 siDelayNum;				// ��ü Ƚ��.
	GMONEY siDelayMoney;				// ��ü��. 

	cltLetterMsg_PayRentFee(SI32 villageunique, SI32 houseindex, GMONEY rentfee, SI32 delaynum, GMONEY delaymoney)
	{
		clHeader.siType = LETTERTYPE_PAYRENTFEE;
		clHeader.siSize	= sizeof(cltLetterMsg_PayRentFee);

		siVillageUnique = villageunique;
		siHouseIndex	= houseindex;
		siRentFee		= rentfee;
		siDelayNum		= delaynum;
		siDelayMoney	= delaymoney;
	}
};

//-------------------------------------------
// ����ȸ��  ���� ����. 
//-------------------------------------------
class cltLetterMsg_RecallHouse{
public:
	cltLetterHeader clHeader;

	SI32			siRecallReason;
	SI32			siVillageUnique;
	SI32			siHouseIndex;
	TCHAR			szOwnerName[MAX_PLAYER_NAME];

	cltLetterMsg_RecallHouse(SI32 reason, SI32 villageunique, SI32 houseindex, TCHAR* OwnerName = NULL)
	{
		clHeader.siType = LETTERTYPE_RECALLHOUSE;
		clHeader.siSize	= sizeof(cltLetterMsg_RecallHouse);

		siRecallReason	= reason;
		siVillageUnique	= villageunique;
		siHouseIndex	= houseindex;
		MStrCpy(szOwnerName,OwnerName,MAX_PLAYER_NAME);
	}
};

//-------------------------------------------
// ����ȸ��  �ӹ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_HouseRecallWarning{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siHouseIndex;
	SI16			siLeftMonth;		// ��� ����ñ��� ���� �ð�. (��)


	cltLetterMsg_HouseRecallWarning(SI32 villageunique, SI32 houseindex, SI32 leftmonth)
	{
		clHeader.siType = LETTERTYPE_HOUSERECALLWARINING;
		clHeader.siSize	= sizeof(cltLetterMsg_HouseRecallWarning);

		siVillageUnique	= villageunique;
		siHouseIndex	= houseindex;
		siLeftMonth		= leftmonth;
	}
};

//-------------------------------------------
// ���� ���� ��� ���� ����. 
//-------------------------------------------
class cltLetterMsg_RentHouse{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siHouseIndex;

	cltLetterMsg_RentHouse(SI32 villageunique, SI32 houseindex)
	{
		clHeader.siType = LETTERTYPE_RENTHOUSE;
		clHeader.siSize	= sizeof(cltLetterMsg_RentHouse);

		siVillageUnique	= villageunique;
		siHouseIndex	= houseindex;
	}
};


//-------------------------------------------
// �Ӹ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_BeRank{
public:
	cltLetterHeader clHeader;

	cltSimpleRank clRank;					// �Ӹ�� �ź�. 
	cltDate clDate;							// �Ӹ�� �ð� 

	UI08 uiGrank ;							// ���ֳ� 6���Ǽ� �Ӹ�� ���

	cltLetterMsg_BeRank( cltSimpleRank* pclrank ,cltDate* pcldate, UI08 grank = 0 )
	{
		clHeader.siType = LETTERTYPE_BERANK;
		clHeader.siSize	= sizeof(cltLetterMsg_BeRank);

		clRank.Set(pclrank);
		clDate.Set(pcldate);

		uiGrank = grank ;
	}
};

//-------------------------------------------
// �ذ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_Fire{
public:
	cltLetterHeader clHeader;

	cltSimpleRank clRank;					// �ذ���� �ź�. 
	cltDate clDate;							// �ذ���� �ð� 

	UI08 uiGrank;							// ���ֳ� 6���Ǽ����� ���ӵ� �� ���

	cltLetterMsg_Fire(cltSimpleRank* pclrank ,cltDate* pcldate, UI08 grank = 0 )
	{
		clHeader.siType = LETTERTYPE_FIRE;
		clHeader.siSize	= sizeof(cltLetterMsg_Fire);

		clRank.Set(pclrank);
		clDate.Set(pcldate);

		uiGrank = grank ;
	}
};


//-------------------------------------------
// �ֽ� �Ұ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_StockLoss{
public:
	cltLetterHeader clHeader;

	SI32		siVillageUnique;			// ���� ����ũ
	SI32		siWinVillage;				// �¸� ����
	SI32		siLossPersent;				// �ֽ� �Ұ� ���� 
	SI32		siStockAmount;				// �ֽ� ���� 

	cltLetterMsg_StockLoss( SI32 villageUnique, SI32 winVillage, SI32 lossPersent, SI32 stockAmount )
	{
		clHeader.siType = LETTERTYPE_STOCKLOSS;
		clHeader.siSize = sizeof( cltLetterMsg_StockLoss );

		siVillageUnique = villageUnique;
		siWinVillage = winVillage;
		siLossPersent = lossPersent;
		siStockAmount = stockAmount;
	}

};

//------------------------------------------
// ���� ���ÿ� ���� �ް� �Ǵ� �޿� ���� ����
//------------------------------------------
class cltLetterMsg_GetKingPay
{
public:
	cltLetterHeader clHeader;
	
	SI32			siVillageUnique;			// ��� �ǽ� ���� 
	GMONEY			siKingPay;					// ���� ������� ���� �� 
	GMONEY			siPayPersent;				// ���� ��� ���� ���� 
	
	cltLetterMsg_GetKingPay( SI32 villageUnique, GMONEY kingPay, GMONEY payPersent )
	{
		clHeader.siType = LETTERTYPE_KINGPAY;
		clHeader.siSize = sizeof( cltLetterMsg_GetKingPay );

		siVillageUnique = villageUnique;
		siKingPay = kingPay;
		siPayPersent = payPersent;
	}
};

//------------------------------------------
// ���� �ֹ� ��� �뺸 �޽���
//------------------------------------------
class cltLetterMsg_ResidentShare
{
public:
	cltLetterHeader clHeader;

	SI32			siVillageUnique;			// ��� �ǽ� ���� 
	SI32			siShareType;				// ��� ����
	GMONEY			siShareMoney;				// ���� 

	cltLetterMsg_ResidentShare( SI32 villageUnique, SI32 shareType, GMONEY shareMoney )
	{
		clHeader.siType = LETTERTYPE_RESIDENTSHARE;
		clHeader.siSize = sizeof( cltLetterMsg_ResidentShare );

		siVillageUnique = villageUnique;
		siShareType = shareType;
		siShareMoney = shareMoney;
	}

};

//------------------------------------------
// �ǹ� ������ �ʿ��� �������� ������� �˸���
//------------------------------------------
class cltLetterMsg_StructureRepairItem
{
public:
	cltLetterHeader clHeader;

	SI32			siVillageUnique;		// ���� 
	SI32			siStrType;				// �ǹ� 
	SI16			siItemUnique;			// ������ ����ũ
	SI16			siItemNum;				// ������ ���� 

	cltLetterMsg_StructureRepairItem( SI32 villageUnique, SI32 strType, SI16 itemunique, SI16 itemnum )
	{
		clHeader.siType = LETTERTYPE_STRUCTUREREPAIRITEM;
		clHeader.siSize = sizeof( cltLetterMsg_StructureRepairItem );

		siVillageUnique = villageUnique;
		siStrType = strType;
		siItemUnique = itemunique;
		siItemNum = itemnum;
	}

};

//-------------------------------------------
// �Ű��� �÷� ���� �ε��� �ȸ�
//-------------------------------------------
class cltLetterMsg_RealEstateMarketTrade
{
public:
	cltLetterHeader clHeader;

	SI32 siHouseVillage;		// ���� 
	SI32 siHouseIndex;			// ���� ��ȣ 

	GMONEY siTradeMoney;			// �ŷ� ���. 	
	GMONEY siFee;					// ���� ������. 

	cltLetterMsg_RealEstateMarketTrade( SI32 housevillage, SI32 houseindex, GMONEY trademoney, GMONEY fee )
	{
		clHeader.siType = LETTERTYPE_REALESTATEMARKETTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_RealEstateMarketTrade);

		siHouseVillage	= housevillage;
		siHouseIndex	= houseindex;

		siTradeMoney	= trademoney;
		siFee			= fee;
	}
};

//-------------------------------------------
// �Ű��� �÷� ���� �ε��� �ֹ� ���� ���� �뺸. 
//-------------------------------------------
class cltLetterMsg_RealEstateMarketPriceDown
{
public:
	cltLetterHeader clHeader;

	SI32	siHouseVillage;		// ���� 
	SI32	siHouseIndex;		// ���� ��ȣ 

	GMONEY	siPrice;			// ���ϵ� �ݾ�. 

	cltLetterMsg_RealEstateMarketPriceDown( SI32 housevillage, SI32 houseindex, GMONEY price )
	{
		clHeader.siType = LETTERTYPE_REALESTATEMARKETPRICEDOWN;
		clHeader.siSize	= sizeof( cltLetterMsg_RealEstateMarketPriceDown );

		siHouseVillage = housevillage;
		siHouseIndex = houseindex;

		siPrice = price;
	}
};


//-------------------------------------------
// �忹���� �÷� ���� ��ȯ�� �ȸ�
//-------------------------------------------
class cltLetterMsg_SummonMarketTrade
{
public:
	cltLetterHeader clHeader;

	SI32 siKind;
	TCHAR szName[ MAX_SUMMON_NAME ];
	
	GMONEY siTradeMoney;			// �ŷ� ���. 	
	GMONEY siFee;					// ���� ������. 

	cltLetterMsg_SummonMarketTrade( SI32 kind, TCHAR *name, GMONEY trademoney, GMONEY fee )
	{
		clHeader.siType = LETTERTYPE_SUMMONMARKETTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_SummonMarketTrade);

		siKind = kind;
		if( name ) {
			StringCchCopy( szName, MAX_SUMMON_NAME, name );
		} else {
			szName[ 0 ] = NULL;
		}

		siTradeMoney	= trademoney;
		siFee			= fee;
	}
};

//-------------------------------------------
// �忹���� �÷� ���� ��ȯ�� ���� ���� �뺸. 
//-------------------------------------------
class cltLetterMsg_SummonMarketPriceDown
{
public:
	cltLetterHeader clHeader;

	SI32	siKind;
	TCHAR	szName[ MAX_SUMMON_NAME ];

	GMONEY	siPrice;			// ���ϵ� �ݾ�. 

	cltLetterMsg_SummonMarketPriceDown( SI32 kind, TCHAR *name, GMONEY price )
	{
		clHeader.siType = LETTERTYPE_SUMMONMARKETPRICEDOWN;
		clHeader.siSize	= sizeof( cltLetterMsg_SummonMarketPriceDown );

		siKind = kind;

		if( name ) {
			StringCchCopy( szName, MAX_SUMMON_NAME, name );
		} else {
			szName[ 0 ] = NULL;
		}

		siPrice = price;
	}
};

class cltLetterMsg_ResidentOutDate
{
public:
	cltLetterHeader clHeader;

	SI32	siVillageUnique;

	cltLetterMsg_ResidentOutDate( SI32 villageunique )
	{
		clHeader.siType = LETTERTYPE_RESIDENTOUTDATE;
		clHeader.siSize	= sizeof( cltLetterMsg_ResidentOutDate );

		siVillageUnique = villageunique;
	}
};

class cltLetterMsg_ResultBidStock
{
public:
	cltLetterHeader clHeader;

	BOOL		bSuccessfulBid;				// ���� �Ǿ��°� 

	SI32		siVillageUnique;			// ���� �ֽ� ���� 
	SI32		siStockAmount;				// �� ���� �ֽ� �� 

	cltMoney	clBidMoney;					// �� ���� �ݾ� 
	BOOL		bExceedLimit;				// ���� �ѵ��� �ʰ��Ͽ��°� 


	cltLetterMsg_ResultBidStock( BOOL bsuccessfulbid, SI32 villageunique, SI32 stockamount, cltMoney *pclMoney, BOOL bexceedlimit )
	{
		clHeader.siType = LETTERTYPE_RESULTBIDSTOCK;
		clHeader.siSize = sizeof( cltLetterMsg_ResultBidStock );

		bSuccessfulBid = bsuccessfulbid;
		
		siVillageUnique = villageunique;
		siStockAmount = stockamount;

		clBidMoney.Set( pclMoney );

		bExceedLimit = bexceedlimit;
	};

};

//-------------------------------------------
// ���� ���� ��� ���� ����. 
//-------------------------------------------
class cltLetterMsg_RentLand{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siLandIndex;

	cltLetterMsg_RentLand(SI32 villageunique, SI32 landindex)
	{
		clHeader.siType = LETTERTYPE_RENTLAND;
		clHeader.siSize	= sizeof(cltLetterMsg_RentLand);

		siVillageUnique	= villageunique;
		siLandIndex		= landindex;
	}
};


//-------------------------------------------
// ���� �Ӵ�� ����  ���� ����. 
//-------------------------------------------
class cltLetterMsg_PayLandRentFee{
public:
	cltLetterHeader clHeader;

	SI32 siVillageUnique;			// ������ �ִ� ������ ����ũ. 
	SI32 siLandIndex;				// ���� ������ �ּ�. 
	GMONEY siRentFee;					// �Ӵ��. 
	SI32 siDelayNum;				// ��ü Ƚ��.
	GMONEY siDelayMoney;				// ��ü��. 

	cltLetterMsg_PayLandRentFee(SI32 villageunique, SI32 landindex, GMONEY rentfee, SI32 delaynum, GMONEY delaymoney)
	{
		clHeader.siType = LETTERTYPE_PAYLANDRENTFEE;
		clHeader.siSize	= sizeof(cltLetterMsg_PayLandRentFee);

		siVillageUnique = villageunique;
		siLandIndex		= landindex;
		siRentFee		= rentfee;
		siDelayNum		= delaynum;
		siDelayMoney	= delaymoney;
	}
};

//-------------------------------------------
// ����ȸ��  ���� ����. 
//-------------------------------------------
class cltLetterMsg_LandRecall{
public:
	cltLetterHeader clHeader;

	SI32			siRecallReason;
	SI32			siVillageUnique;
	SI32			siLandIndex;

	cltLetterMsg_LandRecall(SI32 reason, SI32 villageunique, SI32 landindex)
	{
		clHeader.siType = LETTERTYPE_LANDRECALL;
		clHeader.siSize	= sizeof(cltLetterMsg_LandRecall);

		siRecallReason	= reason;
		siVillageUnique	= villageunique;
		siLandIndex	= landindex;
	}
};

//-------------------------------------------
// ����ȸ��  �ӹ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_LandRecallWarning{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siLandIndex;
	SI16			siLeftMonth;		// ��� ����ñ��� ���� �ð�. (��)


	cltLetterMsg_LandRecallWarning(SI32 villageunique, SI32 landindex, SI32 leftmonth)
	{
		clHeader.siType = LETTERTYPE_LANDRECALLWARNING;
		clHeader.siSize	= sizeof(cltLetterMsg_LandRecallWarning);

		siVillageUnique	= villageunique;
		siLandIndex	= landindex;
		siLeftMonth		= leftmonth;
	}
};

//--------------------------------------------
// ��ȣõ��
//--------------------------------------------
class cltLetterMsg_HozoAngel
{
public:
	cltLetterHeader clHeader;

	SI32		siType ;

	cltDate		clDate;

	cltLetterMsg_HozoAngel(SI32 type,cltDate* pcldate)
	{
		clHeader.siType = LETTERTYPE_HOZOANGEL;
		clHeader.siSize	= sizeof(cltLetterMsg_HozoAngel);

		siType = type ;
		clDate.Set(pcldate);
	}
};

//--------------------------------------------
// ����
//--------------------------------------------
class cltLetterMsg_HyungzoPolice
{
public:
	cltLetterHeader clHeader;

	SI32		siType ;

	cltDate		clDate;

	cltLetterMsg_HyungzoPolice(SI32 type,cltDate* pcldate)
	{
		clHeader.siType = LETTERTYPE_HYUNGZOPOLICE;
		clHeader.siSize	= sizeof(cltLetterMsg_HyungzoPolice);

		siType = type ;
		clDate.Set(pcldate);
	}
};

//-------------------------------------------
// ����Ӵ� �ŷ� ���
//-------------------------------------------
class cltLetterMsg_WorldMoneyTradeResult{
public:
	cltLetterHeader clHeader;

	SI64 siWorldMoney;			// �ŷ��� ��ť��
	SI64 siWorldMoneyPrice;		// �ŷ��� �ݾ�


	cltLetterMsg_WorldMoneyTradeResult(SI64 WorldMoney, SI64 WorldMoneyPrice)
	{
		clHeader.siType = LETTERTYPE_WORLDMONEYTRADERESULT;
		clHeader.siSize	= sizeof(cltLetterMsg_WorldMoneyTradeResult);

		siWorldMoney = WorldMoney;
		siWorldMoneyPrice = WorldMoneyPrice;
	}
};

// ���� �ŷ�
class cltLetterMsg_TradeServerSell
{
public:
	cltLetterHeader clHeader;

	SI16 siItemUnique;			// ��� ��ǰ. 
	SI16 siItemNum;				// �ŷ�����. 

	SI64 siTradeMoney;			// �ŷ� ���. 	

	TCHAR				szBuyerServer[20] ; // �� ����� �ִ� ����
	TCHAR				szBuyerName[20] ; // �� ����� �̸�

	cltLetterMsg_TradeServerSell(SI16 itemunique, SI16 itemnum, SI64 trademoney,TCHAR*buyserver,TCHAR*buyname)
	{
		clHeader.siType = LETTERTYPE_TRADESERVER_SELL;
		clHeader.siSize	= sizeof(cltLetterMsg_TradeServerSell);

		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		siTradeMoney	= trademoney;

		MStrCpy(szBuyerServer,buyserver,20);
		MStrCpy(szBuyerName,buyname,20);
	}

};

class cltLetterMsg_WorldMoneyReducePrice
{
public:
	cltLetterHeader clHeader;

	SI64 siPrice;			
	SI64 siWorldMoney;		
	SI32 siDate;


	cltLetterMsg_WorldMoneyReducePrice( SI64 Price, SI64 WorldMoney, SI32 Date )
	{
		clHeader.siType = LETTERTYPE_WORLDMONEY_REDUCE_PRICE;
		clHeader.siSize	= sizeof(cltLetterMsg_WorldMoneyReducePrice);

		siPrice				= Price;
		siWorldMoney		= WorldMoney;
		siDate				= Date;
	}

};

//--------------------------------------------
// ���� �������� �ֽ��� �������� ���� ������. 
//--------------------------------------------
class cltLetterMsg_GeneralMeeting
{
public:
	cltLetterHeader clHeader;

	SI16		siVillageUnique;

	cltLetterMsg_GeneralMeeting(SI16 villageunique)
	{
		clHeader.siType = LETTERTYPE_GENERALMEETING;
		clHeader.siSize	= sizeof(cltLetterMsg_GeneralMeeting);

		siVillageUnique = villageunique;
	}
};

//-------------------------------------------
// �񺯻翡 �÷� ���� ��ȯ���� �ȸ�
//-------------------------------------------
class cltLetterMsg_SummonHeroMarketTrade
{
public:
	cltLetterHeader clHeader;

	SI32 siKind;
	TCHAR szName[ MAX_SUMMON_NAME ];
	
	GMONEY siTradeMoney;			// �ŷ� ���. 	
	GMONEY siFee;					// ���� ������. 

	cltLetterMsg_SummonHeroMarketTrade( SI32 kind, TCHAR *name, GMONEY trademoney, GMONEY fee )
	{
		clHeader.siType = LETTERTYPE_SUMMONHEROMARKETTRADE;
		clHeader.siSize	= sizeof(cltLetterMsg_SummonHeroMarketTrade);

		siKind = kind;
		if( name ) {
			StringCchCopy( szName, MAX_SUMMON_NAME, name );
		} else {
			szName[ 0 ] = NULL;
		}

		siTradeMoney	= trademoney;
		siFee			= fee;
	}
};

//-------------------------------------------
// �񺯻翡 �÷� ���� ��ȯ���� ���� ���� �뺸. 
//-------------------------------------------
class cltLetterMsg_SummonHeroMarketPriceDown
{
public:
	cltLetterHeader clHeader;

	SI32	siKind;
	TCHAR	szName[ MAX_SUMMON_NAME ];

	GMONEY	siPrice;			// ���ϵ� �ݾ�. 

	cltLetterMsg_SummonHeroMarketPriceDown( SI32 kind, TCHAR *name, GMONEY price )
	{
		clHeader.siType = LETTERTYPE_SUMMONHEROMARKETPRICEDOWN;
		clHeader.siSize	= sizeof( cltLetterMsg_SummonHeroMarketPriceDown );

		siKind = kind;

		if( name ) {
			StringCchCopy( szName, MAX_SUMMON_NAME, name );
		} else {
			szName[ 0 ] = NULL;
		}

		siPrice = price;
	}
};

//-------------------------------------------
// ������ ���� ��ǰ�� �������� �� �뺸
//-------------------------------------------
class cltLetterMsg_PostOfficeSendOk
{
public:
	cltLetterHeader clHeader;
	
	SI16	siType;

	TCHAR	szRecvPersonName[ MAX_PLAYER_NAME ];
	SI16	siItemUnique;
	SI16	siItemNum;
	GMONEY	siMoney;

	cltLetterMsg_PostOfficeSendOk( SI16 type, TCHAR *szName, SI16 itemunique, SI16 itemnum, GMONEY money )
	{
		clHeader.siType = LETTERTYPE_POSTOFFICE_SENDOK;
		clHeader.siSize = sizeof( cltLetterMsg_PostOfficeSendOk );

		siType = type;
		MStrCpy( szRecvPersonName, szName, MAX_PLAYER_NAME );
		siItemUnique = itemunique;
		siItemNum = itemnum;
		siMoney = money;
	}
};

//-------------------------------------------
// ���� ���� ��� ���� ����. 
//-------------------------------------------
class cltLetterMsg_RentMine{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siMineIndex;

	cltLetterMsg_RentMine(SI32 villageunique, SI32 landindex)
	{
		clHeader.siType = LETTERTYPE_RENTMINE;
		clHeader.siSize	= sizeof(cltLetterMsg_RentMine);

		siVillageUnique	= villageunique;
		siMineIndex		= landindex;
	}
};


//-------------------------------------------
// ���� �Ӵ�� ����  ���� ����. 
//-------------------------------------------
class cltLetterMsg_PayMineRentFee{
public:
	cltLetterHeader clHeader;

	SI32 siVillageUnique;			// ������ �ִ� ������ ����ũ. 
	SI32 siMineIndex;				// ���� ������ �ּ�. 
	GMONEY siRentFee;					// �Ӵ��. 
	SI32 siDelayNum;				// ��ü Ƚ��.
	GMONEY siDelayMoney;				// ��ü��. 

	cltLetterMsg_PayMineRentFee(SI32 villageunique, SI32 landindex, GMONEY rentfee, SI32 delaynum, GMONEY delaymoney)
	{
		clHeader.siType = LETTERTYPE_PAYMINERENTFEE;
		clHeader.siSize	= sizeof(cltLetterMsg_PayMineRentFee);

		siVillageUnique = villageunique;
		siMineIndex		= landindex;
		siRentFee		= rentfee;
		siDelayNum		= delaynum;
		siDelayMoney	= delaymoney;
	}
};

//-------------------------------------------
// ����ȸ��  ���� ����. 
//-------------------------------------------
class cltLetterMsg_MineRecall{
public:
	cltLetterHeader clHeader;

	SI32			siRecallReason;
	SI32			siVillageUnique;
	SI32			siMineIndex;

	cltLetterMsg_MineRecall(SI32 reason, SI32 villageunique, SI32 landindex)
	{
		clHeader.siType = LETTERTYPE_MINERECALL;
		clHeader.siSize	= sizeof(cltLetterMsg_MineRecall);

		siRecallReason	= reason;
		siVillageUnique	= villageunique;
		siMineIndex	= landindex;
	}
};

//-------------------------------------------
// ����ȸ��  �ӹ� ���� ����. 
//-------------------------------------------
class cltLetterMsg_MineRecallWarning{
public:
	cltLetterHeader clHeader;

	SI16			siVillageUnique;
	SI16			siMineIndex;
	SI16			siLeftMonth;		// ��� ����ñ��� ���� �ð�. (��)


	cltLetterMsg_MineRecallWarning(SI32 villageunique, SI32 landindex, SI32 leftmonth)
	{
		clHeader.siType = LETTERTYPE_MINERECALLWARNING;
		clHeader.siSize	= sizeof(cltLetterMsg_MineRecallWarning);

		siVillageUnique	= villageunique;
		siMineIndex	= landindex;
		siLeftMonth		= leftmonth;
	}
};

//-------------------------------------------
// ���� �������� ���ؼ� �ý��ۿ��� �������� �����ϰ� �ִٴ� �޼��� 
//-------------------------------------------
class cltLetterMsg_Existent_SaveUserItem{
public:
	cltLetterHeader clHeader;

	cltLetterMsg_Existent_SaveUserItem()
	{
		clHeader.siType = LETTERTYPE_EXISTENT_SAVEUSERITEM;
		clHeader.siSize	= sizeof(cltLetterMsg_Existent_SaveUserItem);
	}
};


//-------------------------------------------
// �ֽ� ���� ��÷ ��� �뺸
//-------------------------------------------
class cltLetterMsg_StockOfferingResult
{
public:
	cltLetterHeader clHeader;

	SI32			siType;
	SI32			siVillageUnique;
	SI32			siStockAmount;
	GMONEY			siPrice;


	cltLetterMsg_StockOfferingResult( SI32 type, SI32 villageunique, SI32 stockamount, GMONEY price )
	{
		clHeader.siType = LETTERTYPE_STOCKOFFERING_RESULT;
		clHeader.siSize	= sizeof(cltLetterMsg_StockOfferingResult);

		siType			= type;
		siVillageUnique	= villageunique;
		siStockAmount	= stockamount;
		siPrice			= price;
	}
};


//-------------------------------------------
// ��õ ���� ��� �˸� �뺸.
//-------------------------------------------
class cltLetterMsg_ChangeRecommendPoint{
public:
	cltLetterHeader clHeader;

	TCHAR			szCharName[MAX_PLAYER_NAME];
	SI32			siLevel;
	SI32			siChangedRecommendPoint;	// �߰��� ��õ ����
	SI32			siRecommentPoint;	// ���� ��õ ����
	
	cltLetterMsg_ChangeRecommendPoint( TCHAR * CharName, SI32 Level ,SI32	ChangedRecommendPoint, SI32	RecommentPoint)
	{
		clHeader.siType = LETTERTYPE_CHANGERECOMMENDPOINT;
		clHeader.siSize	= sizeof(cltLetterMsg_ChangeRecommendPoint);
		
		StringCchCopy( szCharName, MAX_PLAYER_NAME, CharName);
		siLevel = Level;	
		siChangedRecommendPoint = ChangedRecommendPoint;
		siRecommentPoint	= RecommentPoint;
	}
};

//-------------------------------------------
// ��õ ���� ������ ���� �˸� �뺸.
//-------------------------------------------
class cltLetterMsg_LevelUpREcommandRewardForRecommender{
public:
	cltLetterHeader clHeader;

	TCHAR			szCharName[MAX_PLAYER_NAME];
	SI32			siLevel;
	SI32			siRewardItemUnique;	// �߰��� ��õ ����
	SI32			siRewardItemNum;	// ���� ��õ ����

	cltLetterMsg_LevelUpREcommandRewardForRecommender( TCHAR * CharName, SI32 Level ,SI32 RewardItemUnique, SI32 RewardItemNum)
	{
		clHeader.siType = LETTERTYPE_LEVELUPRECOMMANDREWARD_FOR_RECOMMENDER;
		clHeader.siSize	= sizeof(cltLetterMsg_LevelUpREcommandRewardForRecommender);

		StringCchCopy( szCharName, MAX_PLAYER_NAME, CharName);
		siLevel = Level;	
		siRewardItemUnique = RewardItemUnique;
		siRewardItemNum	= RewardItemNum;
	}
};



//-------------------------------------------
// ��õ�� ��Ͻ� ������ ����
//-------------------------------------------
class cltLetterMsg_LevelUpREcommandReward{
public:
	cltLetterHeader clHeader;

	SI32			siLevel;
	SI32			siRewardItemUnique;	// �߰��� ��õ ����
	SI32			siRewardItemNum;	// ���� ��õ ����

	cltLetterMsg_LevelUpREcommandReward( SI32 Level , SI32	RewardItemUnique, SI32	RewardItemNum)
	{
		clHeader.siType = LETTERTYPE_LEVELUPRECOMMANDREWARD;
		clHeader.siSize	= sizeof(cltLetterMsg_LevelUpREcommandReward);

		siLevel = Level;	
		siRewardItemUnique = RewardItemUnique;
		siRewardItemNum	= RewardItemNum;
	}
};


//-------------------------------------------
// ��� ���� ����
//-------------------------------------------
class cltLetterMsg_GuildJoin{
public:
	cltLetterHeader clHeader;

	BOOL m_bJoin;

	cltLetterMsg_GuildJoin( BOOL bJoin)
	{
		clHeader.siType = LETTERTYPE_GUILDJOIN;
		clHeader.siSize	= sizeof(cltLetterMsg_GuildJoin);

		m_bJoin = bJoin;
	}
};

//-----------------------------------------------
// ��� ������ ���� ��
//----------------------------------------------
class cltLetterMsg_Guild_ConfirmCreateGuild
{
public:
	cltLetterHeader clHeader;

	BOOL bConfirm;
	GMONEY siMoney;

	cltLetterMsg_Guild_ConfirmCreateGuild(BOOL confirm,GMONEY money)
	{
		clHeader.siType = LETTERTYPE_GUILD_CONFIRMCREATEGUILD;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_ConfirmCreateGuild);

		bConfirm = confirm ;
		siMoney = money ;
	}
};

class cltLetterMsg_Guild_ConfirmChangeVillage
{
public:
	cltLetterHeader clHeader;

	BOOL bConfirm;

	cltLetterMsg_Guild_ConfirmChangeVillage(BOOL confirm)
	{
		clHeader.siType = LETTERTYPE_GUILD_CONFIRMCREATEGUILD;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_ConfirmCreateGuild);

		bConfirm = confirm ;
	}
};

//-----------------------------------------------
// ��� ���Ǽ� �Ӹ� ���� ��
//----------------------------------------------
class cltLetterMsg_Guild_SecondMaster
{
public:
	cltLetterHeader clHeader;

	BOOL bConfirm;

	cltLetterMsg_Guild_SecondMaster(BOOL confirm)
	{
		clHeader.siType = LETTERTYPE_GUILD_SECONDMASTER;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_SecondMaster);

		bConfirm = confirm ;
	}
};
//-----------------------------------------------
// ��� ������ ����
//----------------------------------------------
class cltLetterMsg_Guild_ChangeMaster
{
public:
	cltLetterHeader clHeader;

	cltLetterMsg_Guild_ChangeMaster()
	{
		clHeader.siType = LETTERTYPE_GUILD_CHANGEMASTER;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_ChangeMaster);
	}

};
//-----------------------------------------------
// ��� ������ ����
//----------------------------------------------
class cltLetterMsg_Guild_ChangeMaster_Notconnect_Month
{
public:
	cltLetterHeader clHeader;

	TCHAR			szCharName[MAX_PLAYER_NAME];

	cltLetterMsg_Guild_ChangeMaster_Notconnect_Month( TCHAR* pszCharName )
	{
		clHeader.siType = LETTERTYPE_GUILD_CHANGEMASTER_NOTCONNECT_MONTH;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_ChangeMaster_Notconnect_Month);

		if ( pszCharName )
		{
			StringCchCopy( szCharName, MAX_PLAYER_NAME, pszCharName);
		}
		else
		{
			StringCchCopy( szCharName, MAX_PLAYER_NAME, TEXT("") );
		}
	}

};

//------------------------------------------------
// ��尡 �ı��Ǿ���
//------------------------------------------------
class cltLetterMsg_Guild_Destroy
{
public:
	cltLetterHeader clHeader;
	SI08			siReason;

	cltLetterMsg_Guild_Destroy(SI08 reason)
	{
		clHeader.siType = LETTERTYPE_GUILD_DESTROY;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_Destroy);

		siReason = reason;
	}

};


//------------------------------------------------
// ������� ���� �Ǿ���
//------------------------------------------------
class cltLetterMsg_GuildWar_SuccessReserve
{
public:
	cltLetterHeader clHeader;

	SI32	siFieldIndex;
	SI32	siRoomIndex;
	TCHAR	szHomeGuild[MAX_GUILD_NAME];
	TCHAR	szAwayGuild[MAX_GUILD_NAME];

	cltLetterMsg_GuildWar_SuccessReserve( SI32 fieldindex, SI32 roomindex, TCHAR* homeguild, TCHAR* awayguild)
	{
		clHeader.siType = LETTERTYPE_GUILD_SUCCESSRESERVE;
		clHeader.siSize = sizeof(cltLetterMsg_GuildWar_SuccessReserve);

		siFieldIndex = fieldindex;
		siRoomIndex = roomindex;
		StringCchCopy( szHomeGuild, MAX_GUILD_NAME, homeguild );
		StringCchCopy( szAwayGuild, MAX_GUILD_NAME, awayguild );
	}
};
//------------------------------------------------
// ���ο� ��� ����� ���� ��� ����� ��û ����
//------------------------------------------------
class cltLetterMsg_GuildDungeon_Apply_New
{
public:
	cltLetterHeader	clHeader;

	SI32	siMapIndex;

	cltLetterMsg_GuildDungeon_Apply_New( SI32 mapindex )
	{
		clHeader.siType = LETTERTYPE_GUILDDUNGEON_APPLY_NEW;
		clHeader.siSize = sizeof(cltLetterMsg_GuildDungeon_Apply_New);

		siMapIndex = mapindex;
	}
};
//------------------------------------------------
// ��� ����� ������ ���� ��û����
//------------------------------------------------
class cltLetterMsg_GuildDungeon_Apply
{
public:
	cltLetterHeader	clHeader;

	SI32	siMapIndex;

	cltLetterMsg_GuildDungeon_Apply( SI32 mapindex )
	{
		clHeader.siType = LETTERTYPE_GUILDDUNGEON_APPLY;
		clHeader.siSize = sizeof(cltLetterMsg_GuildDungeon_Apply);

		siMapIndex = mapindex;
	}
};
//-------------------------------------------------
// ����� �����ǿ� ���� GP, Money ȹ��
//-------------------------------------------------
class cltLetterMsg_GuildDungeon_ChangeGPMoney
{
public:
	cltLetterHeader clHeader;

	SI32	siAddGP;
	GMONEY	siAddMoney;
	SI32	siItemUnique;
	SI32	siItemNum;

	cltLetterMsg_GuildDungeon_ChangeGPMoney( SI32 gp, GMONEY money, SI32 itemunique, SI32 itemnum )
	{
		clHeader.siType = LETTERTYPE_GUILDDUNGEON_CHANGEGPMONEY;
		clHeader.siSize = sizeof(cltLetterMsg_GuildDungeon_ChangeGPMoney);

		siAddGP = gp;
		siAddMoney = money;

		siItemUnique = itemunique;
		siItemNum = itemnum;
	}
};
//-------------------------------------------------
// ����� ������ȹ��
//-------------------------------------------------
class cltLetterMsg_GuildDungeon_GetOwnerShip
{
public:
	cltLetterHeader clHeader;
	SI32			siMapIndex;

	cltLetterMsg_GuildDungeon_GetOwnerShip( SI32 mapindex )
	{
		clHeader.siType = LETTERTYPE_GUILDDUNGEON_GETOWNERSHIP;
		clHeader.siSize = sizeof(cltLetterMsg_GuildDungeon_GetOwnerShip);

		siMapIndex = mapindex;
	}
};

class cltLetterMsg_RenouncePupil
{
public:
	cltLetterHeader clHeader;
	TCHAR	szTeacherName[MAX_PLAYER_NAME];
    
	cltLetterMsg_RenouncePupil( TCHAR* pTeacherName )
	{
		clHeader.siType = LETTERTYPE_RENOUNCEPUPIL;
		clHeader.siSize = sizeof(cltLetterMsg_RenouncePupil);

		MStrCpy( szTeacherName, pTeacherName, MAX_PLAYER_NAME );
	}
};

class cltLetterMsg_AcceptFriend_Result
{
public:
	cltLetterHeader clHeader;
	enum { ACCEPTFRIEND = 0, REJECTFRIEND };
	UI08	uiType;
	TCHAR	szPersonName[MAX_PLAYER_NAME];

	cltLetterMsg_AcceptFriend_Result( UI08 Type, TCHAR* pPersonName )
	{
		clHeader.siType = LETTERTYPE_ACCEPTFRIEND_RESULT;
		clHeader.siSize = sizeof(cltLetterMsg_AcceptFriend_Result);

		uiType = Type;
		MStrCpy( szPersonName, pPersonName, MAX_PLAYER_NAME );
	}
};

class cltLetterMsg_TeacherReward_PupilReward
{
public:
	cltLetterHeader clHeader;
	enum { TEACHER = 0, PUPIL };
	UI08	uiType;
	UI08	uiTiredState;
	TCHAR   szPersonName[MAX_PLAYER_NAME];
	SI32	siLevel;
	SI32	siItemUnique;
	SI32	siItemNum;
	
	cltLetterMsg_TeacherReward_PupilReward( UI08 Type, UI08 TiredState, TCHAR* pPersonName, SI32 Level, SI32	ItemUnique, SI32 ItemNum )
	{
		clHeader.siType = LETTERTYPE_TEACHERREWARD_PUPILREWARD;
		clHeader.siSize = sizeof(cltLetterMsg_TeacherReward_PupilReward);

		uiType = Type;
		uiTiredState = TiredState;
		MStrCpy( szPersonName, pPersonName, MAX_PLAYER_NAME );
		siLevel = Level;
		siItemUnique = ItemUnique;
        siItemNum = ItemNum;
	}
};

class cltLetterMsg_PVPResult
{
public:
	cltLetterHeader clHeader;

	enum { WIN = 0, LOSE, VILLAGE, GUILD };
	bool	bWin;
	UI08	uiType;
	TCHAR	szWinUserName[MAX_PLAYER_NAME];
	TCHAR   szLoseUserName[MAX_PLAYER_NAME];
	// ���ѱ� ������ �̸�
	bool	bDestroyItem;
	SI16	siItemUnique;
	
	cltLetterMsg_PVPResult( bool Win, UI08 Type, TCHAR* WinUserName, TCHAR* LoseUserName, bool	DestroyItem, SI16 ItemUnique )
	{
		clHeader.siType = LETTERTYPE_PVPRESULT;
		clHeader.siSize = sizeof(cltLetterMsg_PVPResult);

		bWin = Win;
		uiType = Type;
		MStrCpy( szWinUserName, WinUserName, MAX_PLAYER_NAME );
		MStrCpy( szLoseUserName, LoseUserName, MAX_PLAYER_NAME );
		bDestroyItem = DestroyItem;
		siItemUnique = ItemUnique;
	}
};

class cltLetterMsg_Guild_AlertDestroy
{
public:
	cltLetterHeader clHeader;

	cltLetterMsg_Guild_AlertDestroy()
	{
		clHeader.siType = LETTERTYPE_GUILD_ALERTDESTROY;
		clHeader.siSize = sizeof(cltLetterMsg_Guild_AlertDestroy);
	}
};


class cltLetterMsg_GiveSystemReward
{
public:

	cltLetterHeader clHeader;

	cltSystemRewardInfo clInfo;

	cltLetterMsg_GiveSystemReward( cltSystemRewardInfo* pclinfo )
	{
		clHeader.siType = LETTERTYPE_SYSTEMREWARD_GIVE;
		clHeader.siSize = sizeof(cltLetterMsg_GiveSystemReward);

		clInfo.Set( pclinfo );
	}
};


class cltLetterUnit{
public:

	union{
		BYTE cData[MAX_LETTER_SIZE];
		SI32 siData[MAX_LETTER_SIZE/4];
	};
	


	cltLetterUnit()
	{
		ZeroMemory(cData, MAX_LETTER_SIZE);
	}

	cltLetterUnit(cltLetterHeader* pdata)
	{
		if(pdata->siSize > MAX_LETTER_SIZE)
		{
			TCHAR buffer[256];
			StringCchPrintf(buffer, 256, TEXT("Exceed: size:%d type:%d"), pdata->siSize, pdata->siType);
			MessageBox(NULL, TEXT("cltLetterUnit"), buffer, MB_OK|MB_TOPMOST);
		}
		else
		{
			memcpy(cData, (BYTE*)pdata, pdata->siSize);										//ok
		}

	}

	void Set(cltLetterUnit* pclletter)
	{
		memcpy(cData, pclletter->cData, MAX_LETTER_SIZE);
	}
	
	bool GetText(TCHAR* buffer, SI16 txtSize );
	
};





class cltLetter{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltLetterUnit, MAX_LETTER_NUMBER>		clLetterUnit;
#else
	cltLetterUnit clLetterUnit[MAX_LETTER_NUMBER];
#endif

	cltLetter(){}
	~cltLetter(){}
};

//////////////////////////////////////////////////////////////////////////
// ������ ��������� ����
//////////////////////////////////////////////////////////////////////////




class cltAccountLetterUnit{
public:

	union{
		BYTE cData[MAX_ACCOUNTLETTER_SIZE];
		SI32 siData[MAX_ACCOUNTLETTER_SIZE/4];
	};



	cltAccountLetterUnit()
	{
		ZeroMemory(cData, MAX_ACCOUNTLETTER_SIZE);
	}

	cltAccountLetterUnit(cltLetterHeader* pdata)
	{
		if(pdata->siSize > MAX_ACCOUNTLETTER_SIZE)
		{


#ifdef _DEBUG
			TCHAR buffer[256];
			StringCchPrintf(buffer, 256, TEXT("Exceed: size:%d type:%d"), pdata->siSize, pdata->siType);
			MessageBox(NULL, TEXT("cltLetterUnit"), buffer, MB_OK|MB_TOPMOST);
#endif
		}
		else


		{
			memcpy(cData, (BYTE*)pdata, pdata->siSize);										//ok
		}

	}

	void Set(cltAccountLetterUnit* pclletter)
	{
		memcpy(cData, pclletter->cData, MAX_ACCOUNTLETTER_SIZE);
	}

	bool GetText(TCHAR* buffer, SI16 txtSize );

};





class cltAccountLetter{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltAccountLetterUnit, MAX_LETTER_NUMBER>		clLetterUnit;
#else
	cltAccountLetterUnit clLetterUnit[MAX_LETTER_NUMBER];
#endif

	cltAccountLetter(){}
	~cltAccountLetter(){}
};


//-------------------------------------------
// ������ �޾Ҵٰ� �˷��ִ� �޽���
//-------------------------------------------

class cltLetterMsg_Present
{
public:

	cltLetterHeader clHeader;

	SI16 siFromServerUnique;
    TCHAR szFromPlayerName[MAX_PLAYER_NAME];
	
	TCHAR szComment[200];
	TCHAR szItemName[50];
	SI32  siItemNum;
	
	SI32 siItemImageFont;
	
	TCHAR szFromPlayerAccount[MAX_PLAYER_NAME];

	cltLetterMsg_Present( SI16 FromServerUnique,TCHAR * FromPlayerName, TCHAR * Comment, 
		TCHAR * ItemName, SI32 ItemNum , SI32 ItemImageFont , TCHAR * FromPlayerAccount )
	{
		clHeader.siType = ACCOUNT_LETTERTYPE_PRESENT;
		clHeader.siSize	= sizeof(cltLetterMsg_Present);	

		siFromServerUnique = FromServerUnique;
		MStrCpy(szFromPlayerName,FromPlayerName,MAX_PLAYER_NAME);
		MStrCpy(szComment,Comment,200);
		MStrCpy(szItemName,ItemName,50);
		siItemNum = ItemNum;
		siItemImageFont = ItemImageFont; 
		MStrCpy(szFromPlayerAccount, FromPlayerAccount, MAX_PLAYER_NAME );
	}
};


class cltLetterMsg_PresentAnswer
{
public:

	cltLetterHeader clHeader;

	SI16 siFromServerUnique;
	TCHAR szFromPlayerName[MAX_PLAYER_NAME];
	TCHAR szComment[200];

	cltLetterMsg_PresentAnswer( SI16 FromServerUnique, TCHAR * FromPlayerName, TCHAR * Comment)
	{
		clHeader.siType = ACCOUNT_LETTERTYPE_PRESENTANSWER;
		clHeader.siSize	= sizeof(cltLetterMsg_PresentAnswer);	

		siFromServerUnique = FromServerUnique;
		MStrCpy(szFromPlayerName,FromPlayerName,MAX_PLAYER_NAME);
		MStrCpy(szComment,Comment,200);
	}
};

class cltLetterMsg_Invite_Applyresident
{
public:
	cltLetterHeader clHeader;

	TCHAR			szMentorName[MAX_PLAYER_NAME];
	TCHAR			szDiscipleName[MAX_PLAYER_NAME];

	cltLetterMsg_Invite_Applyresident( TCHAR* pMentorName, TCHAR* pDiscipleName)
	{
		clHeader.siType = LETTERTYPE_INVITE_APPLYRESIDENT;
		clHeader.siSize	= sizeof(cltLetterMsg_Invite_Applyresident);	
	
		memcpy(szMentorName,   pMentorName,   sizeof(szMentorName));
		memcpy(szDiscipleName, pDiscipleName, sizeof(szDiscipleName));
	}
};

//-------------------------------------------
// ĳ���� �������� ��������� ����
//-------------------------------------------
class cltLetterMsg_CreateCharReward
{
public:
	cltLetterHeader clHeader;

	cltLetterMsg_CreateCharReward( void )
	{
		clHeader.siType = LETTERTYPE_CREATECHARREWARD;
		clHeader.siSize	= sizeof(cltLetterMsg_CreateCharReward);
	}
};

//-------------------------------------------
// ĳ���� �������� ��������� ����
//-------------------------------------------
class cltLetterMsg_WeddingCeremony_Cancel
{
public:
	cltLetterHeader	clHeader;

	cltLetterMsg_WeddingCeremony_Cancel( void )
	{
		clHeader.siType = LETTERTYPE_WEDDINGCEREMONY_CANCEL;
		clHeader.siSize	= sizeof(cltLetterMsg_WeddingCeremony_Cancel);
	}
};

//-------------------------------------------
// �������� Ż�� ���ߴ�.
//-------------------------------------------
class cltLetterMsg_DelLetter
{
public:
	cltLetterHeader	clHeader;

	cltLetterMsg_DelLetter( void )
	{
		clHeader.siType = LETTERTYPE_FAMILY_DEL_FAMILY;
		clHeader.siSize	= sizeof(cltLetterMsg_DelLetter);
	}
};
//-------------------------------------------
// ������ ������.
//-------------------------------------------
class cltLetterMsg_LeaveFamilyLetter
{
public:
	cltLetterHeader	clHeader;

	TCHAR			szName[MAX_PLAYER_NAME];

	cltLetterMsg_LeaveFamilyLetter( TCHAR* pName )
	{
		clHeader.siType = LETTERTYPE_FAMILY_LEAVE_FAMILY;
		clHeader.siSize	= sizeof(cltLetterMsg_LeaveFamilyLetter);
		memcpy(szName,   pName,   sizeof(szName));	// ���� ��� �̸�
	}
};
//-------------------------------------------
// �ش� �ɸ��Ͱ� ������ ��� �Ǿ���.-���� �����鿡�� ������
//-------------------------------------------
class cltLetterMsg_ADDFamilyLetter_ToFamily
{
public:
	cltLetterHeader	clHeader;

	TCHAR			szParentName_1[MAX_PLAYER_NAME];
	TCHAR			szParentName_2[MAX_PLAYER_NAME];
	TCHAR			szAddCharName[MAX_PLAYER_NAME];

	cltLetterMsg_ADDFamilyLetter_ToFamily( TCHAR* pParentName_1,TCHAR* pParentName_2,TCHAR* pAddCharName )
	{
		clHeader.siType = LETTERTYPE_FAMILY_ADD_FAMILY;
		clHeader.siSize	= sizeof(cltLetterMsg_ADDFamilyLetter_ToFamily);
		memcpy(szParentName_1,   pParentName_1,   sizeof(szParentName_1));	// ���� ��� �̸�
		memcpy(szParentName_2,   pParentName_2,   sizeof(szParentName_2));	// ���� ��� �̸�
		memcpy(szAddCharName,   pAddCharName,   sizeof(szAddCharName));	// ���� ��� �̸�
	}
};
//-------------------------------------------
// �ش� �ɸ��Ͱ� ������ ��� �Ǿ���.-�ڱ� �ڽſ��� ������
//-------------------------------------------
class cltLetterMsg_ADDFamilyLetter_ToFamily_To_Me
{
public:
	cltLetterHeader	clHeader;

	TCHAR			szParentName_1[MAX_PLAYER_NAME];
	TCHAR			szParentName_2[MAX_PLAYER_NAME];
	TCHAR			szAddCharName[MAX_PLAYER_NAME];

	cltLetterMsg_ADDFamilyLetter_ToFamily_To_Me( TCHAR* pParentName_1,TCHAR* pParentName_2,TCHAR* pAddCharName )
	{
		clHeader.siType = LETTERTYPE_FAMILY_ADD_FAMILY_TO_ME;
		clHeader.siSize	= sizeof(cltLetterMsg_ADDFamilyLetter_ToFamily_To_Me);
		memcpy(szParentName_1,   pParentName_1,   sizeof(szParentName_1));	// ���� ��� �̸�
		memcpy(szParentName_2,   pParentName_2,   sizeof(szParentName_2));	// ���� ��� �̸�
		memcpy(szAddCharName,   pAddCharName,   sizeof(szAddCharName));	// ���� ��� �̸�
	}
};
//-------------------------------------------
// �޸� ���� ���� ���
//-------------------------------------------
class cltLetterMsg_DormancyWaringExpiration
{
public:
	cltLetterHeader clHeader;

	SI16 m_siDate;			// ���� �Ⱓ(���� : ��)

	cltLetterMsg_DormancyWaringExpiration( SI16 siDate)
	{
		clHeader.siType = LETTERTYPE_DORMANCY_WARING_EXPIRATION;
		clHeader.siSize	= sizeof(cltLetterMsg_DormancyWaringExpiration);

		m_siDate = siDate;
	}
};

// ��ų�� ���õ� ���� ���� �˸�.
class cltLetterMsg_SkillBookMagicDel
{
public:
	cltLetterHeader clHeader;

	SI32			m_siMagicKind;

	cltLetterMsg_SkillBookMagicDel( SI32 _siMagicKind )
	{
		clHeader.siType = LETTERTYPE_SKILLBOOK_MAGIC_DEL;
		clHeader.siSize	= sizeof(cltLetterMsg_SkillBookMagicDel);

		m_siMagicKind = _siMagicKind;
	}
};


#endif