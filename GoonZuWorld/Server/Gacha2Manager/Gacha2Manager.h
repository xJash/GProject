#ifndef _GACHA2MANAGER_H_
#define _GACHA2MANAGER_H_

#include <Directives.h>
#include "CommonLogic.h"

#define MAX_SHOW_GACHA2_PRODUCT 7   // ����  - �ݵ�� MAX_SHOW_GACHA_PRODUCT �� ���ƾ� �Ѵ�.
#define	MAX_GACHA2_PRODUCT 9   // 

//#define GACHA2_USE_KEY1	1
//#define GACHA_USE_SILVERKEY	2
//#define GACHA_USE_BRONZEKEY	3
//#define GACHA_USE_KEYPIECE	4

#define GACHA2_MAX_KEYTYPE	3

#define GACHA2_MAX_RARELIST	100

const SI32 GACHA2_RACCOONKEY_ITEMUNIQUE			=  ITEMUNIQUE(13630); // ���� ����.

//const SI32 GACHA_SILVERKEY_ITEMUNIQUE		=  ITEMUNIQUE(13603);
//const SI32 GACHA_BRONZEKEY_ITEMUNIQUE		=  ITEMUNIQUE(13602);
//const SI32 GACHA_BRONZEKEY_EVENT_ITEMUNIQUE =  ITEMUNIQUE(13622);
//const SI32 GACHA_KEYPIECE_ITEMUNIQUE		=  ITEMUNIQUE(13605);
//const SI32 GACHA_KEYPIECE_NEED_NUM			=  10;	// 1ȸ�� �Ҹ�Ǵ� �������������� ����



struct stGacha2Product
{
	SI32 ItemUnique;
	SI32 ItemNum;
	SI32 ItemUseDate;
	SI32 GachaRate;

	stGacha2Product()
	{
		Init();
	}

	void Init()
	{
		memset(this, 0, sizeof(stGacha2Product));
	}

	void Set( stGacha2Product * src )
	{
		memcpy(this,src, sizeof(stGacha2Product));
	}
	bool IsSame( stGacha2Product * src )
	{
		if( ItemUnique == src->ItemUnique && ItemNum == src->ItemNum 
			&& ItemUseDate == src->ItemUseDate && GachaRate == src->GachaRate)
		{
			return true;
		}

		return false;
	}

};

class CGacha2Manager
{
public:

	CGacha2Manager();
	~CGacha2Manager();

	void Init();	

	// ���� ���� �ý����� ���� ����� �о�´�.
	bool LoadGacha2ProductDataFromTxt();

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<stGacha2Product, MAX_GACHA2_PRODUCT>, GACHA2_MAX_KEYTYPE>		m_GachaProduct;
#else
	stGacha2Product	m_GachaProduct[GACHA2_MAX_KEYTYPE][MAX_GACHA2_PRODUCT];
#endif

	// ���� �ý��ۿ��� �������־��ų� �������ִ� �����۵��� ����� �о�´�.
	// ��ϵ� �����۵��� �������� ���鶧, �����Ҷ� Ư���� ������ ���Ѵ�.
/*	bool LoadGacha2RareListDataFromTxt();
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, GACHA2_MAX_RARELIST>		m_GachaRareList;
#else
	SI32 m_GachaRareList[GACHA2_MAX_RARELIST];
#endif

	bool IsGachaRareItem( SI32 ItemUnique );
*/
private:	

};

#endif
