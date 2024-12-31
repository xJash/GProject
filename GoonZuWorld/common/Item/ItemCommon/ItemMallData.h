
#ifndef _ITEMMALLDATA_H
#define _ITEMMALLDATA_H

#include <Directives.h>

#define MAX_ITEMMALL_TAB	2

#define ITEMMALL_WEBPAGE_WIDTH		420
#define ITEMMALL_WEBPAGE_HEIGHT		490

#define ITEMMALL_BUTTON_WIDTH		74
#define ITEMMALL_BUTTON_HEIGHT		74

#define SCROLLBAR_SIZE				16+2

//#define MAX_ITEMMALL_NUM			18

#define ITEMALL_CHARACTER_MENU			10  // ĳ���� ġ�� �޴�
#define ITEMALL_CHARACTER_SUBJECT1		11	// ��Ʈ
#define ITEMALL_CHARACTER_SUBJECT2		12	// ����
#define ITEMALL_CHARACTER_SUBJECT3		13	// �Ǻ�
#define ITEMALL_CHARACTER_SUBJECT4		14	// ����
#define ITEMALL_CHARACTER_SUBJECT5		15	// �Ǽ��縮

#define ITEMALL_POWER_MENU				20	// �Ŀ� �޴�
#define ITEMALL_POWER_SUBJECT1			21	// �����̾�
#define ITEMALL_POWER_SUBJECT2			22	// �ʱ�ȭ
#define ITEMALL_POWER_SUBJECT3			23	// �̵�
#define ITEMALL_POWER_SUBJECT4			24	// �̿��

#define ITEMALL_SUMMONHORSE_MENU		30	//				��ȯ/��
#define ITEMALL_SUMMONHORSE_SUBJECT1	31	//				��ȯ����  -> ����
#define ITEMALL_SUMMONHORSE_SUBJECT2	32	//				��ȯ��������  -> ��������
#define ITEMALL_SUMMONHORSE_SUBJECT3	33	//				���� X
#define ITEMALL_SUMMONHORSE_SUBJECT4	34	//				�������� X

#define ITEMALL_MATERIALFOOD_MENU		40  // ���/����
#define ITEMALL_MATERIALFOOD_SUBJECT1	41	// ��
#define ITEMALL_MATERIALFOOD_SUBJECT2	42	// ����
#define ITEMALL_MATERIALFOOD_SUBJECT3	43	// ���
#define ITEMALL_MATERIALFOOD_SUBJECT4	44	// å


#define ITEMALL_BEGINNER_MENU			50	// �ʺ���
#define ITEMALL_BEGINNER_SUBJECT1		51	// ��Ʈ
#define ITEMALL_BEGINNER_SUBJECT2		52	// �������
#define ITEMALL_BEGINNER_SUBJECT3		53	// �̿��

#define ITEMALL_SILVERCOIN_MENU			60	// ����
#define ITEMALL_SILVERCOIN_SUBJECT1		61	// ���� �޴� �θ���.

#include "../common/Item/ItemCommon/ItemUnit.h"
#include "../DBManager/GameDBManager_world/DBMsg-ItemMall.h"

class cltItemMallData{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEMMALL_SET_NUM>		clItem;
#else
	cltItem clItem[MAX_ITEMMALL_SET_NUM]; // �� ��ǰ�� ���� �������� ����
#endif

	SI32 siPrice;				// �� ��ǰ�� ����
	SI32 siEventPrice;			// �� ��ǰ�� Event ����

	SI32 siProductKey;			// Product Key
	SI32 siGroupKey;			// Group Key

	SI32 siImageFont;

	TCHAR szName[128] ;
	TCHAR szExplain[256] ;
	TCHAR szExplain2[256] ;		// [��ȣ] ��ǰ�� ���� ����2

	bool bGift;					// true�� ��������

	bool bOnlyBuySilverCoin;	// �������θ� ���Ű� �����ϴ�
	bool bAgeLimit;				// �ŷ�����. KOR: ����

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_ITEMMALL_SET_NUM>		siLimitLevel;
#else
	SI16 siLimitLevel[MAX_ITEMMALL_SET_NUM];		// ������ �� �ŷ�����. For English
#endif

	void Init()
	{
		for ( SI32 i = 0 ; i < MAX_ITEMMALL_SET_NUM ; i ++ )
		{
			clItem[i].Init();
			siLimitLevel[i] = 0;
		}

		siPrice				= 0;
		siEventPrice		= 0;

		siProductKey		= 0 ;
		siGroupKey			= 0 ;
		
		siImageFont			= 0 ;

		szName[0]			= '\0';
		szExplain[0]		= '\0';
		szExplain2[0]		= '\0';

		bGift				= true ;

		bOnlyBuySilverCoin	= false;
		bAgeLimit			= false;	
	}

	void Set(cltItemMallData* pclinfo)
	{
		for ( SI32 i = 0 ; i < MAX_ITEMMALL_SET_NUM ; i ++ )
		{
			clItem[i].Set(&pclinfo->clItem[i]);
			siLimitLevel[i] = pclinfo->siLimitLevel[i];
		}

		siPrice			= pclinfo->siPrice ;
		siEventPrice	= pclinfo->siEventPrice ;

		siProductKey	= pclinfo->siProductKey ;
		siGroupKey		= pclinfo->siGroupKey ;

		siImageFont		= pclinfo->siImageFont ;

		MStrCpy(szName,		pclinfo->szName,	128);
		MStrCpy(szExplain,	pclinfo->szExplain,	256);
		MStrCpy(szExplain2,	pclinfo->szExplain2,256);

		bGift				= pclinfo->bGift ;

		bOnlyBuySilverCoin = pclinfo->bOnlyBuySilverCoin;
		bAgeLimit		   = pclinfo->bAgeLimit;
	}

};

#endif // _ITEMMALLDATA_H