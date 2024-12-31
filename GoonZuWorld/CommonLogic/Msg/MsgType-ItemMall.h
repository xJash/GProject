#ifndef _MSGTYPEITEMMALL_H
#define _MSGTYPEITEMMALL_H

#include "../../common/item/ItemCommon/ItemMallData.h"
#include "../../../DBManager/GameDBManager_world/DBMsg-ItemMall.h"

#define MAX_BILL_PAGGE_URL_LENGTH 1024



//---------------------------------------------------
// ������ ������ �������� ����°�?
//---------------------------------------------------
class cltGameMsgResponse_ItemMallExistence{
public:
	bool	bExistence;

	cltGameMsgResponse_ItemMallExistence(bool existence)
	{
		bExistence = existence ;
	}
};

//---------------------------------------------------
// ������ ������ �� ������ �������� ��û
//---------------------------------------------------
class cltGameMsgRequest_ItemMallItemList{
public:
	SI32		siListPage;

	cltGameMsgRequest_ItemMallItemList(SI32 page)
	{
		siListPage = page;
	}
};

class cltGameMsgResponse_ItemMallItemList{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEMNUM_PER_ITEMMALL>		clItem;
	NSafeTArray<SI32, MAX_ITEMNUM_PER_ITEMMALL>			siItemID;
#else
	cltItem		clItem[MAX_ITEMNUM_PER_ITEMMALL];
	SI32		siItemID[MAX_ITEMNUM_PER_ITEMMALL]; // ������ ��ȣ
#endif
	SI32		siTotalItemNum;
	SI32		siListPage;

	cltGameMsgResponse_ItemMallItemList(cltItem *pclitem,SI32* itemid,SI32 totalitemnum,SI32 page)
	{
		for ( int i = 0 ; i < MAX_ITEMNUM_PER_ITEMMALL ; i ++ )
		{
			clItem[i].Set(&pclitem[i]);
			siItemID[i] = itemid[i] ;
		}

		siTotalItemNum = totalitemnum;
		siListPage = page;
	}
};

//---------------------------------------------------
// ������ ������ �� �κ��丮�� �̵��� ��û
//---------------------------------------------------
class cltGameMsgRequest_ItemMallGetItem{
public:
	SI32		siItemID; // ������ ��ȣ
	SI32		siItemPos; // �������� ��ġ
	cltItem		clItem; // �������� ����

	UI16		uiStr;
	UI16		uiDex;
	UI16		uiMag;
	UI16		uiVit;
	UI16		uiHnd;
	UI16		uiLuk;

	cltGameMsgRequest_ItemMallGetItem(SI32 itemid,SI32 itempos,cltItem *pclitem, UI16 Str = 0, UI16 Dex = 0,
								UI16 Mag = 0, UI16 Vit = 0, UI16 Hnd = 0, UI16 Luk = 0)
	{
		siItemID = itemid;
		siItemPos = itempos ;
		clItem.Set(pclitem);

		uiStr = Str;
		uiDex = Dex;
		uiMag = Mag;
		uiVit = Vit;
		uiHnd = Hnd;
		uiLuk = Luk;

	}
};

class cltGameMsgResponse_ItemMallGetItem{
public:
	SI16		siInvPos;
	cltItem		clItem;

	cltGameMsgResponse_ItemMallGetItem(SI16 pos,cltItem * pclitem)
	{
		siInvPos = pos;
		clItem.Set(pclitem);
	}
};

// �����̵��̿���� �̿��Ͽ� ����� ����â���� �̵��ϱ�
class cltGameMsgRequest_HuntMapWarp
{
public:
	SI32 siMapIndex;
	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.
	SI64 siWMoney;
	// by LEEKH - �̵��ÿ� �� ������ ���°�?
	bool	m_bInMap;

	cltGameMsgRequest_HuntMapWarp(SI32 mapindex , SI64 wMoney, bool bInMap = false)
	{
		siMapIndex = mapindex ;
		siWMoney = wMoney;
		m_bInMap = bInMap;
	}
};

// �����̵��̿���� �̿��Ͽ� ���λ������� 
class cltGameMsgRequest_PersonalShopWarp
{
public:
	SI32 siMapIndex;
	SI32 siX;
	SI32 siY;

	cltGameMsgRequest_PersonalShopWarp(SI32 mapindex, SI32 x, SI32 y)
	{
		siMapIndex = mapindex ;
		siX = x;
		siY = y;
	}
};

enum FRIENDWARP_MODE
{
	FRIENDWARP_MODE_NONE,
	FRIENDWARP_MODE_GUILD,
	FRIENDWARP_MODE_FRIEND,
};

// �����̵��̿���� �̿��Ͽ� ģ�����Է� 
class cltGameMsgRequest_FriendWarp
{
public:
	SI32 siPersonID;
	SI16 siMode;	

	cltGameMsgRequest_FriendWarp(SI32 personid, SI16 mode)
	{
		siPersonID = personid ;
		siMode = mode;
	}
};

class cltGameMsgRequest_PartyWarp
{
public:
	TCHAR szName[MAX_PLAYER_NAME];

	cltGameMsgRequest_PartyWarp(TCHAR * name)
	{
		MStrCpy(szName, name, MAX_PLAYER_NAME );
	}
};


// �̸������̿���� �̿��Ͽ� �̸� �����ϱ�
class cltGameMsgRequest_ChangeCharName
{
public:
	TCHAR szName[MAX_PLAYER_NAME];
	bool  m_bUseItem;				// [��ȣ_NHN->NDOORS] �������� �̿��ؼ� ĳ���͸� �����̿��� ���
	SI08  m_siSlotIndex;			// [��ȣ_NHN->NDOORS] ���� ���õ� ĳ������ ���� �ε���


	cltGameMsgRequest_ChangeCharName(TCHAR * name, bool bUseItem)
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_ChangeCharName));

		MStrCpy( szName, name, MAX_PLAYER_NAME );
		m_bUseItem = bUseItem;
	}
};

class cltGameMsgResponse_ChangeCharName
{
public:
	SI32		siResult;
	TCHAR		szName[MAX_PLAYER_NAME];

	bool  m_bUseItem;				// [��ȣ_NHN->NDOORS] �������� �̿��ؼ� ĳ���͸� �����̿��� ���

	cltGameMsgResponse_ChangeCharName(SI32 result,TCHAR * name, bool m_bUseItem = true)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_ChangeCharName));

		siResult = result ;

		MStrCpy(szName, name, MAX_PLAYER_NAME );

		m_bUseItem = m_bUseItem;
	}
};

class cltGameMsgResponse_Change_CharKind
{
public:
	SI32		siResult;

	SI16		siKind;

	cltGameMsgResponse_Change_CharKind(SI32 result,SI16 kind)
	{
		siResult = result ;

		siKind = kind ;
	}
};

class cltGameMsgResponse_NoLimitTicket_Warp
{
public:

	SI32		siType;
	bool		bUsing;
	SI32		siDateVary;


	cltGameMsgResponse_NoLimitTicket_Warp( SI32 Type, bool use , SI32 datevary )
	{
		siType = Type;
		bUsing = use ;
		siDateVary = datevary ;
	}
};
// Ƽ������ �ش� �������� ���� ���󰣴�
class cltGameMsgRequest_WarpTargetWorld
{
public:
	SI32 siItemUnique;

	cltGameMsgRequest_WarpTargetWorld( SI32 ItemUnique )
	{
		siItemUnique = ItemUnique;
	}

};class cltGameMsgResponse_WarpTargetWorld
{
public:

	SI32 siItemUnique	;


	cltGameMsgResponse_WarpTargetWorld( SI32 siItemUnique )
	{
		siItemUnique = siItemUnique;
	}
};

// �����۸����� ��з��� �Һз��� �������� ��ǰ ����Ʈ�� ��û�Ѵ�.
class cltGameMsgRequest_Get_Sel_PGList
{
public:
	SI32				siMainCategory; // ��з�
	SI32				siSubCategory; // �Һз�

	TCHAR				szType[4] ; // ��ǰ ����

	SI32				siPage ; // �ҷ��� ������

	cltGameMsgRequest_Get_Sel_PGList(SI32 main,SI32 sub,TCHAR* type,SI32 page)
	{
		siMainCategory = main ;
		siSubCategory = sub ;

		MStrCpy(szType,type,4) ;

		siPage = page ;
	}
};

class cltGameMsgResponse_Get_Sel_PGList
{
public:
	SI32				siResult ;		// 1�ܿ��� ����

	SI32				siMainCategory; // ��з�
	SI32				siSubCategory; // �Һз�

	TCHAR				szType[4] ; // ��ǰ ����

	SI32				siPage ; // �ҷ��� ������
	SI32				siMaxPage;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemMallData, MAX_ITEMMALL_LIST_NUM>		clItemData;
#else
	cltItemMallData		clItemData[MAX_ITEMMALL_LIST_NUM]; // ��ǰ ����
#endif

	cltGameMsgResponse_Get_Sel_PGList(SI32 result,SI32 main,SI32 sub,TCHAR* type,SI32 page, SI32 maxpage, cltItemMallData* pclinfo)
	{
		siResult = result ;

		siMainCategory = main ;
		siSubCategory = sub;

		MStrCpy(szType,type,4);

		siPage = page;
		siMaxPage = maxpage;

		for ( SI32 i = 0 ; i < MAX_ITEMMALL_LIST_NUM ; i ++ )
			clItemData[i].Set(&pclinfo[i]);
	}
};

// ������ �������� �� ���� �� �׷� ������ ������ �ҷ��´�.
class cltGameMsgRequest_Get_ItemMall_ItemInfo
{
public:
	SI32				siGroupKey; // �׷�Ű��

	cltGameMsgRequest_Get_ItemMall_ItemInfo(SI32 key)
	{
		siGroupKey = key;
	}
};

class cltGameMsgResponse_Get_ItemMall_ItemInfo
{
public:
	SI32				siResult ;		// 1�ܿ��� ����

#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemMallData, 3>			clItemData;
#else
	cltItemMallData		clItemData[3]; // ����( �Ⱓ���� �����۵� �����̴�. )
#endif

	cltGameMsgResponse_Get_ItemMall_ItemInfo(SI32 result,cltItemMallData* pclinfo)
	{
		siResult = result ;

		for ( SI32 i = 0 ; i < 3 ; i ++ )
			clItemData[i].Set(&pclinfo[i]);
	}
};

// �� ĳ�� ������ �����´�.
class cltGameMsgResponse_Get_MyCash_Info
{
public:
	SI32				siResult;
	SI32				siRealCash; // ĳ�� ���� ( ���� )
	SI32				siBonusCash; // ���ʽ� ĳ�� ���� + �̺�Ʈ ĳ�� ���� + etc

	cltGameMsgResponse_Get_MyCash_Info(SI32 result, SI32 real,SI32 bonus)
	{
		siResult = result;
		siRealCash = real ;
		siBonusCash = bonus ;
	}
};

// ������ ���
class cltGameMsgRequest_ItemMall_Buyitem
{
public:
	SI32				siProductKey ;
	SI32				siProductNum;
	SI32				siProductPrice;
	SI32				siProductEventPrice;	
	TCHAR				szItemName[50];
	TCHAR				szSecondPassWord[9];
	bool				bAgeLimit;				// [����] �ŷ�����. KOR: ����, ENG: ���� => 2008-9-22

	cltGameMsgRequest_ItemMall_Buyitem( SI32 key,SI32 num,SI32 price, SI32 EventPrice, TCHAR* itemname, TCHAR* SecondPassWord = NULL )
	{
		siProductKey		= key;
		siProductNum		= num;
		siProductPrice		= price;
		siProductEventPrice = EventPrice;

		szItemName[0]		= '\0';
		szSecondPassWord[0]	= '\0';

		if(itemname)		MStrCpy(szItemName, itemname, sizeof(szItemName));

		if( SecondPassWord )
		{
			//MStrCpy( szSecondPassWord, SecondPassWord, 9 );
			MStrCpy( szSecondPassWord, SecondPassWord,  sizeof(szSecondPassWord) );
		}
		else
		{
			szSecondPassWord[0] = '\0';
		}

		bAgeLimit = 0;
	}

	//[����] �ŷ�����. ������ �߰�. KOR: ����, ENG: ���� => 2008-9-22
	cltGameMsgRequest_ItemMall_Buyitem( SI32 key,SI32 num,SI32 price, SI32 EventPrice, TCHAR* itemname, bool _bAgeLimit )
	{
		siProductKey		= key ;
		siProductNum		= num ;
		siProductPrice		= price ;
		siProductEventPrice	= EventPrice ;

		szItemName[0]		= '\0';
		szSecondPassWord[0]	= '\0';

		if(itemname)		MStrCpy(szItemName, itemname, sizeof(szItemName));

		szSecondPassWord[0] = '\0';

		bAgeLimit = _bAgeLimit;
	}
};

class cltGameMsgResponse_ItemMall_Buyitem
{
public:
	SI32				siResult ;		// 1�ܿ��� ����

	cltItemMallData		clItemData; // �� ������ ����

	SI32				siProductNum;
	SI32				siRealCash; // ĳ�� ���� ( ���� )
	SI32				siBonusCash; // ���ʽ� ĳ�� ���� + �̺�Ʈ ĳ�� ���� + etc

	TCHAR				szCode[50];

	cltGameMsgResponse_ItemMall_Buyitem(SI32 result,cltItemMallData*pclinfo,SI32 num, SI32 realcash, SI32 bonuscash, TCHAR*code)
	{
		siResult = result ;

		clItemData.Set(pclinfo);

		siProductNum = num ;
		siRealCash = realcash;
		siBonusCash = bonuscash;

		MStrCpy(szCode,code,50);
	}
};

// ������ �����ϱ�
class cltGameMsgRequest_ItemMall_Giftitem
{
public:
	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductKey;	// ����ǰ
	SI32				siProductNum;
	SI32				siProductPrice;
	SI32				siProductEventPrice;

	TCHAR				szComment[200];
	TCHAR				szItemName[50];
	
	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
    SI32				siItemImageFont;
	TCHAR				szSecondPassWord[9];

	cltGameMsgRequest_ItemMall_Giftitem(TCHAR*getid,SI32 key,SI32 num,SI32 price, SI32 EventPrice,TCHAR*comment,TCHAR* itemname,SI16 ServerUnique,TCHAR* CharName,SI32 ItemImageFont, TCHAR* SecondPassWord = NULL )
	{
		MStrCpy(szGetAccountID,getid,MAX_PLAYER_NAME);
		siProductKey		= key ;
		siProductNum		= num ;
		siProductPrice		= price ;
		siProductEventPrice = EventPrice ;

		MStrCpy(szComment,comment,200);
		MStrCpy(szItemName,itemname,50);

		siGetServerUnique = ServerUnique;
		MStrCpy( szGetCharName,CharName,MAX_PLAYER_NAME );		

		siItemImageFont = ItemImageFont;

		if( SecondPassWord )
		{
			MStrCpy( szSecondPassWord, SecondPassWord, 9 );
		}
		else
		{
			szSecondPassWord[0] = '\0';
		}

	}
};

class cltGameMsgResponse_ItemMall_Giftitem
{
public:
	SI32				siResult ;		// 1�ܿ��� ����

	TCHAR				szGetCharName[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductKey;	// ����ǰ
	SI32				siProductNum;
	SI32				siProductPrice;
	SI32				siRealCash; // ĳ�� ���� ( ���� )
	SI32				siBonusCash; // ���ʽ� ĳ�� ���� + �̺�Ʈ ĳ�� ���� + etc
		
	TCHAR				szCode[50];
	TCHAR				szItemName[50]; 	
	
	SI32				siHanFailReason;	// [����] hangame �����ֱ⿡ ������ ����. => 2008-7-24
	
	cltGameMsgResponse_ItemMall_Giftitem(SI32 result,TCHAR*getname,SI32 key,SI32 num,SI32 price, SI32 realcash, SI32 bonuscash, TCHAR*code, TCHAR* itemname, SI32 _siHanFailReason)
	{
		siResult = result ;

		MStrCpy(szGetCharName,getname,MAX_PLAYER_NAME);
		siProductKey = key ;
		siProductKey = key ;
		siProductNum = num ;
		siProductPrice = price ;

		siRealCash = realcash;
		siBonusCash = bonuscash;

		MStrCpy(szCode,code,50);
		MStrCpy(szItemName,itemname,50);
		
		siHanFailReason = _siHanFailReason;
	}
};


// ���̵� �˻��ϱ�
class cltGameMsgRequest_Check_AccountID
{
public:
	SI16				siServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME] ; // ���� ���� ������ ĳ���� �̸�


	cltGameMsgRequest_Check_AccountID( SI16 ServerUnique,  TCHAR* GetCharName)
	{
		siServerUnique = ServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME);
	}
};


class cltGameMsgResponse_Check_AccountID
{
public:
	SI32				siResult ;		// 1�̸� ���̵� ����, �������� ���̵� �������� ����
	
	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME] ; // ���� ���� ������ ĳ���� �̸�
    
	TCHAR				szAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� ID
	TCHAR				szAccountName[MAX_PLAYER_NAME] ;	// ���� ���� ��� �̸�


	cltGameMsgResponse_Check_AccountID(SI32 result,  SI16 GetServerUnique,  TCHAR* GetCharName  ,TCHAR* account, TCHAR* name)
	{
		siResult = result ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME);
		MStrCpy(szAccountID,account,MAX_PLAYER_NAME);
		MStrCpy(szAccountName,name,MAX_PLAYER_NAME);
	}
};


class cltGameMsgRequest_BillPage_URL
{
public:

	TCHAR				szAccountID[MAX_PLAYER_NAME] ; // �ڽ��� ���� ID
	TCHAR				szPassWord[FILE_NAME_SIZE] ;	// �ڽ��� ���� PASSWORD

	cltGameMsgRequest_BillPage_URL(TCHAR* account, TCHAR* password)
	{
		MStrCpy(szAccountID,account,MAX_PLAYER_NAME);
		MStrCpy(szPassWord,password,FILE_NAME_SIZE);
	}
};


class cltGameMsgResponse_BillPage_URL
{
public:
	
	TCHAR				szBillPageURL[MAX_BILL_PAGGE_URL_LENGTH];	// ��ȣȭ�� �� ������ URL
		
	cltGameMsgResponse_BillPage_URL(TCHAR* billpageurl)
	{
		MStrCpy(szBillPageURL,billpageurl,MAX_BILL_PAGGE_URL_LENGTH);		
	}
};

class cltGameMsgRequest_LoginPage_URL
{
public:

	TCHAR				szAccountID[MAX_PLAYER_NAME] ; // �ڽ��� ���� ID
	TCHAR				szPassWord[FILE_NAME_SIZE] ;	// �ڽ��� ���� PASSWORD
	TCHAR				szUrl[MAX_PATH];

	cltGameMsgRequest_LoginPage_URL(TCHAR* account, TCHAR* password, TCHAR* url)
	{
		MStrCpy(szAccountID,account,MAX_PLAYER_NAME);
		MStrCpy(szPassWord,password,FILE_NAME_SIZE);
		MStrCpy(szUrl, url, MAX_PATH);
	}
};


class cltGameMsgResponse_LoginPage_URL
{
public:

	TCHAR				szLoginPageURL[MAX_BILL_PAGGE_URL_LENGTH];	// ��ȣȭ�� ����
	TCHAR				szUrl[MAX_PATH];

	cltGameMsgResponse_LoginPage_URL(TCHAR* loginpageurl, TCHAR* url)
	{
		MStrCpy(szLoginPageURL, loginpageurl,MAX_BILL_PAGGE_URL_LENGTH);		
		MStrCpy(szUrl, url, MAX_PATH);
	}
};


class cltGameMsgRequest_GachaPage_URL
{
public:

	TCHAR				szAccountID[MAX_PLAYER_NAME] ; // �ڽ��� ���� ID
	TCHAR				szPassWord[FILE_NAME_SIZE] ;	// �ڽ��� ���� PASSWORD

	cltGameMsgRequest_GachaPage_URL(TCHAR* account, TCHAR* password)
	{
		MStrCpy(szAccountID,account,MAX_PLAYER_NAME);
		MStrCpy(szPassWord,password,FILE_NAME_SIZE);
	}
};


class cltGameMsgResponse_GachaPage_URL
{
public:

	TCHAR				szGachaPageURL[MAX_BILL_PAGGE_URL_LENGTH];	// ��ȣȭ��  ������ URL

	cltGameMsgResponse_GachaPage_URL(TCHAR* gachapageurl)
	{
		MStrCpy(szGachaPageURL,gachapageurl,MAX_BILL_PAGGE_URL_LENGTH);		
	}
};


// ������ �� �ִ� ���� ���� ����
class cltGameMsgResponse_Set_ChangeHero
{
public:
	SI16			siPos;
	cltItem			clitem;

	SI32			siCode;

	cltGameMsgResponse_Set_ChangeHero(SI16 pos,cltItem*pclitem,SI32 code)
	{
		siPos = pos ;
		clitem.Set(pclitem);

		siCode = code ;
	}
};

// �������� ����
class cltGameMsgRequest_Change_Hero
{
public:
	SI32			siCharKind; // ������ ����
	bool			bChange; // ���� �ƴϸ� ����

	cltGameMsgRequest_Change_Hero(SI32 kind,bool change)
	{
		siCharKind = kind ;
		bChange = change ;
	}
};

class cltGameMsgRequest_Present_Asnwer
{
public:
	SI16			siToServerUnique;
	TCHAR			szToCharName[MAX_PLAYER_NAME];
	TCHAR			szToAccountName[MAX_PLAYER_NAME];
	TCHAR			szComment[200];
	cltGameMsgRequest_Present_Asnwer(SI16 ToServerUnique, TCHAR * ToCharName, TCHAR * ToAccountName , TCHAR * Comment )
	{
		siToServerUnique = ToServerUnique;
		MStrCpy(szToCharName,ToCharName,MAX_PLAYER_NAME);
		MStrCpy(szToAccountName,ToAccountName,MAX_PLAYER_NAME);
		MStrCpy(szComment,Comment,200);
	}

};

//[����] ���θ��Ͱ� ������ ĳ������ �̵�.
class cltGameMsgRequest_PromoterWarp
{
public:
	TCHAR	m_szName[MAX_PLAYER_NAME];

	cltGameMsgRequest_PromoterWarp( TCHAR*	_pszName )
	{
		ZeroMemory( this, sizeof(*this) );

		if( _pszName )
			StringCchCopy( m_szName, sizeof(m_szName), _pszName );
	}
};

#endif