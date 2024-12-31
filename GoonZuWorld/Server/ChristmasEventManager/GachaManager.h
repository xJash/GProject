//#ifndef _GACHAMANAGER_H_
//#define _GACHAMANAGER_H_
//
//#include <Directives.h>
//#include "CommonLogic.h"
//
//#define MAX_SHOW_GACHA_PRODUCT 7
//#define	MAX_GACHA_PRODUCT 9
//
//#define GACHA_USE_GOLDKEY	1
//#define GACHA_USE_SILVERKEY	2
//#define GACHA_USE_BRONZEKEY	3
//#define GACHA_USE_KEYPIECE	4
//
//#define GACHA_MAX_KEYTYPE	3
//
//#define GACHA_MAX_RARELIST	100
//
//const SI32 GACHA_GOLDKEY_ITEMUNIQUE =  ITEMUNIQUE(7872);
//const SI32 GACHA_SILVERKEY_ITEMUNIQUE =  ITEMUNIQUE(7870);
//const SI32 GACHA_BRONZEKEY_ITEMUNIQUE =  ITEMUNIQUE(7868);
//const SI32 GACHA_KEYPIECE_ITEMUNIQUE =  ITEMUNIQUE(7875);
//const SI32 GACHA_KEYPIECE_NEED_NUM =  10;	// 1ȸ�� �Ҹ�Ǵ� �������������� ����
//
//
//
//struct stGachaProduct
//{
//	SI32 ItemUnique;
//	SI32 ItemNum;
//	SI32 ItemUseDate;
//	SI32 GachaRate;
//
//	stGachaProduct()
//	{
//		Init();
//	}
//
//	void Init()
//	{
//		memset(this, 0, sizeof(stGachaProduct));
//	}
//
//	void Set( stGachaProduct * src )
//	{
//		memcpy(this,src, sizeof(stGachaProduct));
//	}
//	bool IsSame( stGachaProduct * src )
//	{
//		if( ItemUnique == src->ItemUnique && ItemNum == src->ItemNum 
//			&& ItemUseDate == src->ItemUseDate && GachaRate == src->GachaRate)
//		{
//			return true;
//		}
//
//		return false;
//	}
//
//};
//
//class CGachaManager
//{
//public:
//
//	CGachaManager();
//	~CGachaManager();
//
//	void Init();	
//
//	// ���� ���� �ý����� ���� ����� �о�´�.
//	bool LoadGachaProductDataFromTxt();
//
//	stGachaProduct	m_GachaProduct[GACHA_MAX_KEYTYPE][MAX_GACHA_PRODUCT];
//
//	// ���� �ý��ۿ��� �������־��ų� �������ִ� �����۵��� ����� �о�´�.
//	// ��ϵ� �����۵��� �������� ���鶧, �����Ҷ� Ư���� ������ ���Ѵ�.
//	bool LoadGachaRareListDataFromTxt();
//	SI32 m_GachaRareList[GACHA_MAX_RARELIST];
//
//	bool IsGachaRareItem( SI32 ItemUnique );
//
//private:	
//
//};
//
//#endif
