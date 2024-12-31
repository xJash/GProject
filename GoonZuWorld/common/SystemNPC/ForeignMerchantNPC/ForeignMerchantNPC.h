#ifndef _FOREIGNMERCHANTNPC_H_
#define _FOREIGNMERCHANTNPC_H_

#include <Directives.h>
#include "CommonLogic.h"
#include "../../../../NLib/NArray.h"

#define MAX_FOREIGNMERCHANTNPC_NUM			30			// ���� ������ �� ���ΰ�?
#define MAX_FOREIGNMERCHANTNPC_NAME_LENGTH	64			// ���� ���� �̸� ����
//enum { FOREIGNMERCHANTNPC_KIND_JAPAN = 200, FOREIGNMERCHANTNPC_KIND_CHINESE = 300 };

#define MAX_FOREIGNMERCHANTNPC_BUY_ITEM_TOTAL_PRICE 1000000		// 100���� ��ŭ�� �������� �����Ѵ�.

enum { FOREIGNMERCHANT_HELMET, FOREIGNMERCHANT_ARMOUR, FOREIGNMERCHANT_AXE, FOREIGNMERCHANT_SWORD, FOREIGNMERCHANT_STAFF, FOREIGNMERCHANT_SPEAR, FOREIGNMERCHANT_GUN, FOREIGNMERCHANT_BOW, FOREIGNMERCHANT_SHOES, FOREIGNMERCHANT_BELT, FOREIGNMERCHANT_POTTER, FOREIGNMERCHANT_HARDWARE, FOREIGNMERCHANT_RING, FOREIGNMERCHANT_CLOTHES, FOREIGNMERCHANT_HAT, FOREIGNMERCHANT_NECK, FOREIGNMERCHANT_PAPER, FOREIGNMERCHANT_FISHING, FOREIGNMERCHANT_CANNON, FOREIGNMERCHANT_END };

#define SAVE_TIME_FOREIGNMERCHANTNPC_BUY_INFO_TO_DB		1000	// 1000 �����Ӵ� 1���� ����

enum { FOREIGNMERCHANT_NOT_EXIST = -1, FOREIGNMERCHANT_STOP_STAUS = 0, FOREIGNMERCHANT_BUY_STATUS };

#define MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM	50

struct stForeignMerchantNPCInfo
{
	SI16	siForeignMerchantKind;			// ���� NPC ����
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM>		siBuyItemUniqueList;
	NSafeTArray<GMONEY, MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM>	siBuyItemPriceList;
#else
	SI16	siBuyItemUniqueList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];		// ���� NPC �� �������� �������� ����ũ �� ����Ʈ
	GMONEY	siBuyItemPriceList[ MAX_FOREIGNMERCHANT_BUYITEM_LIST_NUM ];		// ���� NPC �� �����ϴ� �������� ���� ����Ʈ
#endif
	SI16	siBuyItemType;
	SI16	siBuyItemListCount;
};

class CForeignMerchantNPC
{
public:
	CForeignMerchantNPC();
	~CForeignMerchantNPC();

	void Initialize();
	void Destroy();

	SI16 GetStatus();

	SI16 GetForeignMerchantKind();

	void SetKind( SI16 siForeignMerchantKind, SI16 siItemType );
	void Set( SI32 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount );
	void Set( SI16 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount );
	//void Set( SI16 siItemUnique, SI32 siItemAveragePrice, SI32 siBuyItemRestNum, cltDate clDate );		// ����ũ ���� ���� �ü��� DB �� ���� �޾ƿ� �Է���
	stForeignMerchantNPCInfo* GetForeignMerchantNPCInfo();		// ���� ������ ����
	void GetForeignMerchantNPCInfo( stForeignMerchantNPCInfo * );	// ���� ������ ����

	//bool Buy( UI16 uiItemNum );									// �������� ������ ���� �������� ���

	void GetBuyInfoText( TCHAR *pBuffer );

	bool IsAvailable();

	void RefreshPrice();

	/*
	void DecreaseBuyItemNum( UI16 uiDecreaseBuyItemNum );		// �����ϴ� �������� ������ ���δ�.

	void SaveDifferent();										// SAVE_TIME_FOREIGNMERCHANTNPC_BUY_INFO_TO_DB ���� �ٲ�� �ִٸ� ������.

	cltDate *GetDate();

	SI32 GetRestNum();
	*/


private:
	stForeignMerchantNPCInfo	sForeignMerchantNPCInfo;
	
	SI16						m_siForeignMerchantKind;
	SI32						m_siBuyItemTotalNum;				// ���� NPC �� �����ҷ��� �������� �� ����
	SI16						m_siStatus;							// ���� NPC �� �������� �������� �ƴ����� ���� ������ ������ ����.
	bool						m_bAvailable;
	SI32						m_siSaveLastBuyRestNum;				// �ֱٿ� DB�� �����͸� �����ϸ鼭, �ٲﰪ
	SI16						m_siBuyItemType;
	
};


class CForeignMerchantNPCMgr
{
public:
	CForeignMerchantNPCMgr();
	~CForeignMerchantNPCMgr();

	void Initialize();
	void Destroy();

	void Add( SI16 siKind, SI16	siBuyItemType );
	void Set( SI16 siKind, SI32 siBuyItemType, SI32 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount );
	void Set( SI16 siKind, SI32 siBuyItemType, SI16 *psiItemUniqueList, GMONEY *psiItemPriceList, SI32 siListCount );
	//void Set( SI16 siKind, SI16 siBuyItemUnique, SI32 siBuyItemAveragePrice, SI32 siBuyItemRestNum, cltDate	clDate );

	void Action( cltTime *pTime );

	SI16 GetStatus( SI16 siKind );	
	CForeignMerchantNPC *GetForeignMerchantNPC( SI16 siKind );
	stForeignMerchantNPCInfo* GetForeignMerchantNPCInfo( SI16 siKind );

	void GetBuyInfoText( SI16 siKind, TCHAR *pBuffer );

private:
#ifdef _SAFE_MEMORY
	NSafeTArray<CForeignMerchantNPC, MAX_FOREIGNMERCHANTNPC_NUM>		m_ForeignMerchant;
#else
	CForeignMerchantNPC m_ForeignMerchant[ MAX_FOREIGNMERCHANTNPC_NUM ];
#endif
};

#endif
