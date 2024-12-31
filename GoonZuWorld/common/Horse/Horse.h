//---------------------------------
// 2003/8/26 ���°�
//---------------------------------

#ifndef _HORSE_H
#define _HORSE_H

#include <Directives.h>

class cltServer;


// ������ ����. 
#define ANIMAL_MALE				0
#define ANIMAL_FEMALE			1

#define MAX_HORSE_TYPE_INFO		40


// ���� ����ũ�� horse.txt �����Ϳ� ��ġ�Ǿ�� �Ѵ�

#define HORSEUNIQUE_BROWN		1		// ������
#define HORSEUNIQUE_BLACK		2		// �渶
#define HORSEUNIQUE_WHITE		3		// �鸶
#define HORSEUNIQUE_RED			4		// ���丶
#define HORSEUNIQUE_RUDOLF		5		// �絹��
#define HORSEUNIQUE_TIGER		6		// ȣ����   // ȣ����	//KHY - 0911 - ȣ���� �߰�.
#define HORSEUNIQUE_THOUSAND	7		// õ����
#define HORSEUNIQUE_STEEL		8		// ö�⸶
#define HORSEUNIQUE_WOLF		9		// ����		// ������ �Ե��� �����Ǿ��ִ�
#define HORSEUNIQUE_ZEBRA		10		// ��踻
#define HORSEUNIQUE_BEAST		11		// ����ȣ
#define HORSEUNIQUE_FOAL		12		// ������	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
#define HORSEUNIQUE_CAMEL		13		// ��Ÿ
#define HORSEUNIQUE_TIGER2		14		// ����S�� �̺�Ʈ�� ȣ���� //PCK : 08.04.01 �߰�	
#define HORSEUNIQUE_ELEPHANT	15		// �ڳ��� : PCK - 08.06.12
#define HORSEUNIQUE_WHITETIGER	16		// ��ȣ�߰� : PCK - 08.08.14
#define HORSEUNIQUE_MOTORCYCLE	17		// ��������߰� : PCK - 08.09.02
#define HORSEUNIQUE_FIREHATCH	18		// ����ġ�߰� : PCK - 08.12.10
#define HORSEUNIQUE_WHITE_TEST	19		// ü��� �鸶 : �ռ���-2009.03.17
#define HORSEUNIQUE_BAPHOMET	20		// ������Ʈ �߰� : PCK - 2009.07.30
#define HORSEUNIQUE_GRAYWOLF	21		// ȸ�� ���� �߰� : ���� - 2009.08.30
#define HORSEUNIQUE_SASURI		22		// ����� �߰� : ���� - 2009.12.31

#define MAX_BROWN_SPEED		1500
#define MAX_BROWN_STR		3000
#define MAX_BROWN_DEX		3000
#define MAX_BROWN_MAG		3000

#define MAX_HORSE_SPEED		2000	
#define MAX_HORSE_STR		4000	
#define MAX_HORSE_DEX		4000	
#define MAX_HORSE_MAG		4000	

#define MAX_BEAST_SPEED		2000
#define MAX_BEAST_STR		5000
#define MAX_BEAST_DEX		4000
#define MAX_BEAST_MAG		5000

#define MAX_RUDOLF_STR		3500 
#define MAX_RUDOLF_DEX		3500 
#define MAX_RUDOLF_MAG		5000 

#define MAX_REDHORSE_DEX	5000

#define MAX_STEELHORSE_STR	5000

#define MAX_WOLF_SPEED		2000
#define MAX_WOLF_DEX		5500
#define MAX_WOLF_MAG		4500
#define MAX_WOLF_STR		4000

//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
#define MAX_FOAL_SPEED		1400
#define MAX_FOAL_STR		500
#define MAX_FOAL_DEX		500
#define MAX_FOAL_MAG		500

//KHY - 0911 - ȣ���� �߰�.
#define MAX_TIGER_SPEED		2000
#define MAX_TIGER_STR		5500	
#define MAX_TIGER_DEX		5000
#define MAX_TIGER_MAG		4500

//PCK - 08/02/18 - ��Ÿ �߰�.
#define MAX_CAMEL_SPEED		2000
#define MAX_CAMEL_STR		4000
#define MAX_CAMEL_DEX		4000
#define MAX_CAMEL_MAG		8000

//PCK - 08.04.01 - ����S�� �̺�Ʈȣ���� �߰�.
#define MAX_TIGER2_SPEED	2000
#define MAX_TIGER2_STR		5500
#define MAX_TIGER2_DEX		5000
#define MAX_TIGER2_MAG		4500

//PCK - 08.06.12 - �ڳ��� �߰�
#define MAX_ELEPHANT_SPEED	2000
#define MAX_ELEPHANT_STR	8000
#define MAX_ELEPHANT_DEX	4000
#define MAX_ELEPHANT_MAG	4000

//PCK - 08.08.14 - ��ȣ �߰�
#define MAX_WHITETIGER_SPEED	2000
#define MAX_WHITETIGER_STR		7500
#define MAX_WHITETIGER_DEX		8000
#define MAX_WHITETIGER_MAG		7500

//PCK - 08.09.02 - ������� �߰� 
#define MAX_MOTORCYCLE_SPEED	2000
#define MAX_MOTORCYCLE_STR		7000
#define MAX_MOTORCYCLE_DEX		7000
#define MAX_MOTORCYCLE_MAG		6000

//PCK - 08.12.10 - ����ġ �߰�
#define MAX_FIREHATCH_SPEED		2000
#define MAX_FIREHATCH_STR		6500
#define MAX_FIREHATCH_DEX		7000
#define MAX_FIREHATCH_MAG		6500

//PCK - 09.07.30 - ������Ʈ �߰�
#define MAX_BAPHOMET_SPEED		2000
#define MAX_BAPHOMET_STR		7500
#define MAX_BAPHOMET_DEX		5000
#define MAX_BAPHOMET_MAG		7500

//���� - 09.07.30 - ȸ������ �߰�
#define MAX_GRAYWOLF_SPEED		2000
#define MAX_GRAYWOLF_DEX		5500
#define MAX_GRAYWOLF_MAG		4000
#define MAX_GRAYWOLF_STR		4000

//���� - 09.07.30 - ����� �߰�
#define MAX_SASURI_SPEED		2000
#define MAX_SASURI_DEX			6000
#define MAX_SASURI_MAG			9000
#define MAX_SASURI_STR			6000

//-------------------------------------
// ���� ���� ���. 
//-------------------------------------
#define HORSEACTION_NONE	0
#define HORSEACTION_UPDATE	1
#define HORSEACTION_DIE		200  //KHY - 1001 - ��µ��� 5���� ���� ����. - ���° ���� �״��� �˱����ؼ�// 200 + �������� �ε��������� ��ȯ�ȴ�.
#define HORSEATTION_TICKET	3 // ���ɷ�����̿�Ƕ���
#define HORSEATTION_PREMIUMPARTS	4 // �� �����̾� ���� ������.

//----------------------------------------
// Person�� �����ϴ� ���� ����. 
//---------------------------------------
//KHY - 1001 - ��µ��� 5���� ���� ����. - �� ����.
#define MAX_HORSE_PER_PERSON				5

// ���� �߰� ����
#define MAX_HORSE_ADDSTATUS					10
// ���� �����̾����� �߰� ���� 
#define MAX_HORSE_PREMIUMPARTS				30
// ���� �߰� ���� ���� ����
#define MAX_HORSE_ADDSTATUS_LIMITDATE		360 // 30�� ���� �ð� �� �Ϸ�

//-------------------------------------------
// Ż �Ϳ� ���� ����Ʈ�� �����Ǿ� �ϴ� ���� ��
//-------------------------------------------
#define HORSE_EFFECTHIGHT_NORMAL_SASURI		70		
#define HORSE_EFFECTHIGHT_PVP_SASURI		100

// ���� �԰� �ʹٰ� �ϴ� ä�� �������� ����ũ
const SI32 HorseFood_Vegetable_ItemUnique[] = 
{
	ITEMUNIQUE(3600), // ��
	ITEMUNIQUE(3605), // ��
	ITEMUNIQUE(3610), // �̳���. 
	ITEMUNIQUE(3615), //ǥ�����.
	ITEMUNIQUE(3620), //��� 
	ITEMUNIQUE(3625), // ����
	ITEMUNIQUE(3630), //����
	ITEMUNIQUE(3635), //���� 
	ITEMUNIQUE(3640), //����
	ITEMUNIQUE(3645), //���
	ITEMUNIQUE(3650), // ���� 
	ITEMUNIQUE(3655), // ��
	ITEMUNIQUE(3660), //���� 
	ITEMUNIQUE(3665), //�� 
	ITEMUNIQUE(16000), //�ұ� 
	ITEMUNIQUE(3685)  //��
};

// ���� �԰� �ʹٰ� �ϴ� ���� ���� �������� ����ũ
const SI32 HorseFood_Meat_ItemUnique[] = 
{
	ITEMUNIQUE(3670), // �߰��
	ITEMUNIQUE(3675), // �������
	ITEMUNIQUE(3680), // ����
	ITEMUNIQUE(16100), // �ؾ�
	ITEMUNIQUE(16110), // �ޱ�
	ITEMUNIQUE(16120), // �׾�
	ITEMUNIQUE(16150), // ���
	ITEMUNIQUE(16160), // ����
};

// ������̰� �԰� �ʹٰ� �ϴ� ���� ���� �������� ����ũ
const SI32 HorseFood_Mineral_ItemUnique[] = 
{
/*	
	ITEMUNIQUE(5000), // ��ź
	ITEMUNIQUE(5010), // ö����
	ITEMUNIQUE(5020), // ��������
	ITEMUNIQUE(5040), // �ݱ���
	ITEMUNIQUE(5050), // ������
	ITEMUNIQUE(5065), // ����
	ITEMUNIQUE(5070), // ��Ȳ
	ITEMUNIQUE(5025), // ���
*/
	ITEMUNIQUE(3922), // 
	ITEMUNIQUE(3923), // 
	ITEMUNIQUE(3924), // 
	ITEMUNIQUE(3925)
};

class cltPersonHorseInfo{
public:

	bool	bAutoFoodSwitch;				// �ڵ����� �����̸� �Դ°�. 
	//SI16	siCurrentHorseIndex;			// ���� Ÿ�� �ִ� ���� �ε���. 

	bool	siCurrentHorseRIDEHORSE;			// ���� Ÿ�� �ִ���. True = Ÿ���ִ�. False = ���ȴ�.
	SI16	siCurrentShowHorse;				// ���� ���� �ִ� ���� �ε���. 

protected:
//public:
	//cltHorse clHorse;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHorse, MAX_HORSE_PER_PERSON>		clHorse;
#else
	cltHorse clHorse[MAX_HORSE_PER_PERSON];
#endif

public:
	cltPersonHorseInfo()
	{
		Init();
	}
	void Init()
	{
		bAutoFoodSwitch		= true;
//		siCurrentHorseIndex = -1;
		siCurrentHorseRIDEHORSE = false;
		siCurrentShowHorse	= 0;


		//clHorse.Init();
		for(SI32 i = 0;i < MAX_HORSE_PER_PERSON;i++)
		{
			clHorse[i].Init();
		}
	}

	void Set(cltPersonHorseInfo* pclinfo)
	{
		bAutoFoodSwitch			= pclinfo->bAutoFoodSwitch;
		siCurrentHorseRIDEHORSE = pclinfo->siCurrentHorseRIDEHORSE;
		siCurrentShowHorse		= pclinfo->siCurrentShowHorse;

		//clHorse.Set( &pclinfo->clHorse);
		for(SI32 i = 0;i < MAX_HORSE_PER_PERSON;i++)
		{
			clHorse[i].Set( &pclinfo->clHorse[i]);
		}		
	}

	cltHorse* GetCurrentShowHorse()
	{
		//return &clHorse;
		if(siCurrentShowHorse >= 0 && siCurrentShowHorse < MAX_HORSE_PER_PERSON)
			return &clHorse[ siCurrentShowHorse ];
		else
			return NULL;
	}

	SI32 GetCurrentRideHorseUnique()
	{
		if( siCurrentHorseRIDEHORSE )
		{
			if(siCurrentShowHorse >= 0 && siCurrentShowHorse < MAX_HORSE_PER_PERSON)
				return clHorse[ siCurrentShowHorse ].siHorseUnique;
			else
				return 0;
		}
		return 0;
	}

	void SetCurrentShowHorseIndex(SI16 index)
	{
		if(index < 0)						return;
		if(index >= MAX_HORSE_PER_PERSON)	return;

		siCurrentShowHorse = index;
	}

	SI16 GetCurrentShowHorseIndex()
	{
		return siCurrentShowHorse;
	}

	void SetCurrentHorseRIDEHORSE(bool ridehorse)
	{
		siCurrentHorseRIDEHORSE = ridehorse;
	}

	bool GetCurrentHorseRIDEHORSE()
	{
		return siCurrentHorseRIDEHORSE;
	}

	cltHorse* GetHorse(SI16 index)
	{
		if(index>=0 && index<MAX_HORSE_PER_PERSON)	return &clHorse[index];
		return NULL;
	}


	bool Add(cltHorse* pclhorse, SI32* pindex);
	
	// ���� �ܿ� �䱸������ ���Ѵ�. 
	bool GetNeed(cltHorse* pclhorse, SI32* pneeditemunique, SI32* pneeditemnum);

	// index�� ���� Ż �� �ִ°�?
	bool CanRide(SI32 index, cltDate* pcldate);

	// ���� ���� �� �ִ� �ε����� ã�´�. 
	SI32 FindEmptyHorseIndex();

	// ���� �Ѹ����� ���� �ִ°�. 
	bool HaveHorse()
	{
		//if(clHorse.siHorseUnique)return true;
		for(SI32 i = 0;i < MAX_HORSE_PER_PERSON;i++)
		{
			if(clHorse[i].siHorseUnique)return true;
		}

		return false;
	}

	void SetHorse(SI32 index, cltHorse* pclhorse)
	{
		//clHorse.Set(pclhorse);
		if(index < 0)						return;
		if(index >= MAX_HORSE_PER_PERSON)	return;
		if(pclhorse == NULL)				return;

		clHorse[index].Set(pclhorse);
	}

	void Init(SI32 index)
	{
		if(index < 0)						return;
		if(index >= MAX_HORSE_PER_PERSON)	return;

		//clHorse.Init();
		clHorse[index].Init();
	}

};

class cltHorseTypeInfo{
public:
	SI32 siUnique;
	TCHAR szCode[64];
	TCHAR szSpecies[64];
	SI32 siKind;			// ĳ���ͷμ��� kind

	SI32 siServiceArea;
	bool bNotTrade;

	cltHorseTypeInfo(SI32 unique, TCHAR* pcode, TCHAR* pspecies, SI32 kind, SI32 ServiceArea, bool NotTrade);
	~cltHorseTypeInfo();

};

class cltHorseManager{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHorseTypeInfo*, MAX_HORSE_TYPE_INFO>		pclHorseTypeInfo;
#else
	cltHorseTypeInfo* pclHorseTypeInfo[MAX_HORSE_TYPE_INFO];
#endif

	cltHorseManager();
	~cltHorseManager();

	
	// ���� Ÿ���� �߰��Ѵ�. 
	bool AddHorseType(SI32 unique, TCHAR* pcode, TCHAR* pspecies, SI32 kind, SI32 ServiceArea, bool NotTrade);

	// ���� ���� ������ �ؽ�Ʈ�� ��� �����Ѵ�. 
	bool GetText(cltHorse* pclhorse, TCHAR* ptext, SI16 txtSize);

	// �� ǰ�� ���ڿ��� ����ũ ���� ��´�
	SI32 GetHorseUniqueFromString( TCHAR *szSpecies );
	
	// ���� ����ũ�� �ٰŷ� ���� �̸��� ���Ѵ�. 
	TCHAR* GetHorseName(SI32 horseunique);
	
	SI32 GetFullStr(SI32 unique);
	SI32 GetFullDex(SI32 unique);
	SI32 GetFullMag(SI32 unique);
	SI32 GetFullSpeed(SI32 unique);
	SI32 GetFullLife(SI32 unique);

	// ���� ����(��)�� ���Ѵ�. 
	SI32 GetLife(cltHorse* pclhorse, SI32 curday);
	void SetLife(cltHorse* pclhorse, SI32 curday, SI32 life);


	SI32 Action(cltServer* pclserver, cltHorse* pclhorse, SI32 skilllevel, SI32 datevary, bool bselfswitch, SI32* prewardamount);

	// �䱸������ �������״��� Ȯ���Ѵ�.
	SI32 CheckNeed(cltHorse* pclhorse);

	// ������ �����Ѵ�. 
	bool Reward(cltHorse* pclhorse, SI32 rate, bool bselfswitch, SI32* prewardamount);

	// ���� �䱸������ �����. 
	bool MakeHorseNeed(SI32 npcpricerate, SI32 skilllevel, cltHorse* pclhorse, SI32 duetime, cltDate* pcldate);

	// ���� �Ա� ���ϴ� ������ ����ũ�� ������ ���´�. 
	bool GetHorseFoodNeed(cltHorse* pclhorse, SI32* pitemunique, SI32* pitemnum);

	// ������ ���̸� �ش�.
	bool GiveFood(cltHorse* pclhorse, cltItem* pclitem);

	// ���� �䱸 ������ �ؽ�Ʈ�� ���´�. 
	bool GetNeedText(cltHorse* pclhorse, TCHAR* ptext, SI16 txtSize );

	// ���� �߰� ������ ���ѳ��ڸ� �ؽ�Ʈ�� ���´�.
	void GetAddStatusLimitDateText(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize);
	void GetAddStatusLimitDateText(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize, SI32 TextMgrIndex);

	// �����̾� ����������1�� ���ѳ��ڸ� �ؽ�Ʈ�� ��� �´�.
	void GetPremiumPartsDateText_Slot1(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize);
	// �����̾� ����������2�� ���ѳ��ڸ� �ؽ�Ʈ�� ��� �´�.
	void GetPremiumPartsDateText_Slot2(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize);
	// �����̾� ����������3�� ���ѳ��ڸ� �ؽ�Ʈ�� ��� �´�.
	void GetPremiumPartsDateText_Slot3(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize);

	// ���� �߰� ������ ���� ��¥�� ���ؿ´�.
	SI32 GetAddStatusLimitDateVary(cltHorse* pclhorse);
	// �� �����̾� ������ ���ѳ�¥�� ���ؿ´�
	SI32 GetPremiumPArtsDateVary_Slot1(cltHorse* pclhorse);
	SI32 GetPremiumPArtsDateVary_Slot2(cltHorse* pclhorse);
	SI32 GetPremiumPArtsDateVary_Slot3(cltHorse* pclhorse);
};

#endif
