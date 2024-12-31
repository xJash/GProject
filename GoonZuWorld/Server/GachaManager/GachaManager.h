#ifndef _GACHAMANAGER_H_
#define _GACHAMANAGER_H_

#include <Directives.h>
#include "CommonLogic.h"

#define MAX_SHOW_GACHA_PRODUCT	7
#define	MAX_GACHA_PRODUCT		9

#define GACHA_USE_GOLDKEY		1
#define GACHA_USE_SILVERKEY		2
#define GACHA_USE_BRONZEKEY		3
#define GACHA_USE_KEYPIECE		4
//KHY - 1104 -  ����2 -���� ���� ����.  - ���� ����.
#define GACHA2_USE_KEY1			5
// ���� ���� �߰�
#define CARRYOVER_USE_GOLDKEY	6
#define CARRYOVER_USE_SILVERKEY	7
#define CARRYOVER_USE_BRONZEKEY	8

#define GACHA_MAX_KEYTYPE		3

#define GACHA_MAX_RARELIST		200	//	[����] 2009-12-30 100-> 200���� 

#define MAX_CARRYOVER_PRODUCT	8	// �̿� ��í �ִ� ����

#define TOTAL_GACHA_PRODUCT		9	// ����/�̿� ��í�� ���� ����

#define MAX_CHANGERARE_PRODUCT	12	// ���� ���� ������ ���� ������ �ִ� ����. 12�� 1�� ���� ���� �ϵ��� �ؼ� 12�� 

const SI32 GACHA_GOLDKEY_ITEMUNIQUE			=  ITEMUNIQUE(13604);
const SI32 GACHA_SILVERKEY_ITEMUNIQUE		=  ITEMUNIQUE(13603);
const SI32 GACHA_BRONZEKEY_ITEMUNIQUE		=  ITEMUNIQUE(13602);
const SI32 GACHA_BRONZEKEY_EVENT_ITEMUNIQUE =  ITEMUNIQUE(13622);
const SI32 GACHA_KEYPIECE_ITEMUNIQUE		=  ITEMUNIQUE(13605);
const SI32 GACHA_KEYPIECE_NEED_NUM			=  10;	// 1ȸ�� �Ҹ�Ǵ� �������������� ����

// �̿���ǰ ����Ű
const SI32 CARRYOVER_GOLDKEY_ITEMUNIQUE		=  ITEMUNIQUE(13645);
const SI32 CARRYOVER_SILVERKEY_ITEMUNIQUE	=  ITEMUNIQUE(13644);
const SI32 CARRYOVER_BRONZEKEY_ITEMUNIQUE	=  ITEMUNIQUE(13643);

#define MAX_GACHA_BONUS_VALUE	1000	// ���� ���ʽ� �ִ밪


struct stGachaProduct
{
	SI32 ItemUnique;
	SI32 ItemNum;
	SI32 ItemUseDate;
	SI32 GachaRate;

	stGachaProduct()
	{
		Init();
	}

	void Init()
	{
		memset(this, 0, sizeof(stGachaProduct));
	}

	void Set( stGachaProduct * src )
	{
		memcpy(this,src, sizeof(stGachaProduct));
	}
	bool IsSame( stGachaProduct * src )
	{
		if( ItemUnique == src->ItemUnique && ItemNum == src->ItemNum 
			&& ItemUseDate == src->ItemUseDate && GachaRate == src->GachaRate)
		{
			return true;
		}

		return false;
	}

};
struct stGachaTimePeriod
{
	SI32	Index	;
	SI32	ItemUnique;
	SYSTEMTIME	stStartTime;
	SYSTEMTIME	stEndTime;
	stGachaTimePeriod()
	{
		Init();
	}

	void Init()
	{
		memset(this, 0, sizeof(stGachaTimePeriod));
	}

	void Set( stGachaTimePeriod * src )
	{
		memcpy(this,src, sizeof(stGachaTimePeriod));
	}
	void SetRaredata(SI32 siCount,  SI32 siUnique, SI32 sisYear, SI32 sisMonth, SI32 sisDay, SI32 sisHour, SI32 sisMin, SI32 sieYear, SI32 sieMonth, SI32 sieDay, SI32 sieHour, SI32 sieMin)
	{	
		if ( siCount >= MAX_CHANGERARE_PRODUCT )	return	;
		if ( siCount < 0 )	return	;
		ItemUnique	=	siUnique	;
		
		stStartTime.wYear	=	sisYear	;
		stStartTime.wMonth	=	sisMonth	;
		stStartTime.wDay	=	sisDay	;
		stStartTime.wHour	=	sisHour	;
		stStartTime.wMinute	=	sisMin	;

		stEndTime.wYear		=	sieYear	;
		stEndTime.wMonth	=	sieMonth	;
		stEndTime.wDay		=	sieDay	;
		stEndTime.wHour		=	sieHour	;
		stEndTime.wMinute	=	sieMin	;
	}

};

struct stGachaCarryOverProduct
{
#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<stGachaProduct, MAX_GACHA_PRODUCT>, GACHA_MAX_KEYTYPE>	m_stGachaCarryOver;
#else
	stGachaProduct	m_stGachaCarryOver[GACHA_MAX_KEYTYPE][MAX_GACHA_PRODUCT];
#endif

	stGachaCarryOverProduct()
	{
		Init();
	}

	void Init( void )
	{
	#ifdef _SAFE_MEMORY
		m_stGachaCarryOver.ZeroMem();
	#else
		ZeroMemory( m_stGachaCarryOver, (sizeof(stGachaProduct)*GACHA_MAX_KEYTYPE*MAX_GACHA_PRODUCT) );
	#endif
	}

	void SetGoldKeyItemInfo( SI32 siProductNum, SI32 siItemUnique, SI32 siItemNum, SI32 siItemUseDate, SI32 siGachaRate )
	{
		if ( (0 <= siProductNum) && (MAX_GACHA_PRODUCT > siProductNum) )
		{
			m_stGachaCarryOver[0][siProductNum].ItemUnique	= siItemUnique;
			m_stGachaCarryOver[0][siProductNum].ItemNum		= siItemNum;
			m_stGachaCarryOver[0][siProductNum].ItemUseDate	= siItemUseDate;
			m_stGachaCarryOver[0][siProductNum].GachaRate	= siGachaRate;
		}
	}

	void SetSilverKeyItemInfo( SI32 siProductNum, SI32 siItemUnique, SI32 siItemNum, SI32 siItemUseDate, SI32 siGachaRate )
	{
		if ( (0 <= siProductNum) && (MAX_GACHA_PRODUCT > siProductNum) )
		{
			m_stGachaCarryOver[1][siProductNum].ItemUnique	= siItemUnique;
			m_stGachaCarryOver[1][siProductNum].ItemNum		= siItemNum;
			m_stGachaCarryOver[1][siProductNum].ItemUseDate	= siItemUseDate;
			m_stGachaCarryOver[1][siProductNum].GachaRate	= siGachaRate;
		}
	}

	void SetBronzeKeyItemInfo( SI32 siProductNum, SI32 siItemUnique, SI32 siItemNum, SI32 siItemUseDate, SI32 siGachaRate )
	{
		if ( (0 <= siProductNum) && (MAX_GACHA_PRODUCT > siProductNum) )
		{
			m_stGachaCarryOver[2][siProductNum].ItemUnique	= siItemUnique;
			m_stGachaCarryOver[2][siProductNum].ItemNum		= siItemNum;
			m_stGachaCarryOver[2][siProductNum].ItemUseDate	= siItemUseDate;
			m_stGachaCarryOver[2][siProductNum].GachaRate	= siGachaRate;
		}
	}

	bool IsCorrectRateSum( void )
	{
		SI32 siGoldRateSum		= 0;
		SI32 siSilverRateSum	= 0;
		SI32 siBronzeRateSum	= 0;

		SI32 siGoldItemCount	= 0;
		SI32 siSilverItemCount	= 0;
		SI32 siBronzeItemCount	= 0;

		for ( SI32 siIndex=0; siIndex<MAX_GACHA_PRODUCT; siIndex++ )
		{
			if ( 0 < m_stGachaCarryOver[0][siIndex].ItemUnique )
			{
				siGoldItemCount++;
				siGoldRateSum += m_stGachaCarryOver[0][siIndex].GachaRate;
			}

			if ( 0 < m_stGachaCarryOver[1][siIndex].ItemUnique )
			{
				siSilverItemCount++;
				siSilverRateSum += m_stGachaCarryOver[1][siIndex].GachaRate;
			}

			if ( 0 < m_stGachaCarryOver[2][siIndex].ItemUnique )
			{
				siBronzeItemCount++;
				siBronzeRateSum += m_stGachaCarryOver[1][siIndex].GachaRate;
			}
		}

		if ( (1000 != siGoldRateSum) || (1000 != siSilverRateSum) || (1000 != siBronzeRateSum) )
		{
			return false;
		}

		if ( (MAX_GACHA_PRODUCT != siGoldItemCount) || (MAX_GACHA_PRODUCT != siSilverItemCount) || (MAX_GACHA_PRODUCT != siBronzeItemCount) )
		{
			return false;
		}

		return true;
	}
};

class CGachaManager
{
public:

	CGachaManager();
	~CGachaManager();

	void Init();	

	// ���� ���� �ý����� ���� ����� �о�´�.
	bool LoadGachaProductDataFromTxt();
	bool LoadCarryOverGachaProductDataFromTxt();
	bool LoadGachaTimePeriodFromTxt();	// ���� �� ���� ���� ������ 

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<stGachaProduct, MAX_GACHA_PRODUCT>, GACHA_MAX_KEYTYPE>		m_GachaProduct;
	NSafeTArray< stGachaCarryOverProduct, MAX_CARRYOVER_PRODUCT >						m_CarryOverProduct;
	NSafeTArray< stGachaTimePeriod, MAX_CHANGERARE_PRODUCT >							m_GacharareTimePeriod;
#else
	stGachaProduct			m_GachaProduct[GACHA_MAX_KEYTYPE][MAX_GACHA_PRODUCT];
	stGachaCarryOverProduct	m_CarryOverProduct[MAX_CARRYOVER_PRODUCT];
	stGachaTimePeriod	m_GacharareTimePeriod[MAX_CHANGERARE_PRODUCT];
#endif

	// ���� �ý��ۿ��� �������־��ų� �������ִ� �����۵��� ����� �о�´�.
	// ��ϵ� �����۵��� �������� ���鶧, �����Ҷ� Ư���� ������ ���Ѵ�.
	bool LoadGachaRareListDataFromTxt();
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, GACHA_MAX_RARELIST>		m_GachaRareList;
#else
	SI32 m_GachaRareList[GACHA_MAX_RARELIST];
#endif

	bool IsGachaRareItem( SI32 ItemUnique );

public:
	SI32 GetCarryOverGachaItemUnique( const SI32 siIndex );

	bool IsPare( const SI32 siIndex, const SI32 siItemUnique );
	void GetGachaProductFromIndex( IN const SI32 siIndex, IN const SI32 siKeyKind, OUT SI32* psiProductList );
	void GetGachaItem( IN const SI32 siIndex, IN const SI32 siKeyKind, IN const SI32 siProductIndex, OUT cltItem* pclGetItem );
	SI32 GetGachaRate( const SI32 siIndex, const SI32 siKeyKind, const SI32 siProductIndex );

	UI08 GetCachaCntAddNum( const SI32 siKeyKind );

private:	

};

#endif
