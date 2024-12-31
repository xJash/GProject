//---------------------------------
// 2003/5/20 ���°�
//---------------------------------

#ifndef _ITEMUNIT_H
#define _ITEMUNIT_H

#include <Windows.h>
#include <Directives.h>

#include "CommonHeader.h"

//-------------------------------
// ������ Ÿ�� ����ũ .
//-------------------------------
#define ITEMTYPE_SWORD			1
#define ITEMTYPE_SPEAR			2
#define ITEMTYPE_STAFF			3
#define ITEMTYPE_AXE			4
#define ITEMTYPE_BOW			5
#define ITEMTYPE_GUN			6
#define ITEMTYPE_CANNON			7
#define ITEMTYPE_ARMOUR			8
#define ITEMTYPE_DRESS			9
#define ITEMTYPE_NECK			10
#define ITEMTYPE_RING			11
#define ITEMTYPE_BELT			12
#define ITEMTYPE_SHOES			13
#define ITEMTYPE_HELMET			14
#define ITEMTYPE_HAT			15
#define ITEMTYPE_FOOD			16
#define ITEMTYPE_SEAFOOD		17
#define ITEMTYPE_HEAL			18
#define ITEMTYPE_BOOK			19
#define ITEMTYPE_MINERAL		20
#define ITEMTYPE_ANIMAL			21
#define ITEMTYPE_TREE			22
#define ITEMTYPE_PAPER			23
#define ITEMTYPE_CLOTH			24
#define ITEMTYPE_SCROLL			25
#define ITEMTYPE_ETC			26
#define ITEMTYPE_IRON			27
#define ITEMTYPE_DISH			28
#define ITEMTYPE_FISHINGROD		29
#define ITEMTYPE_DOLL			30
#define ITEMTYPE_TICKET			31
#define ITEMTYPE_BAG			32
#define ITEMTYPE_MANTLE			33
#define ITEMTYPE_TORPEDO		34


//---------------------------------
//������ Ÿ���� �Ӽ�.
// bit ������ ����. 
//---------------------------------
#define ITEMATB_OBJECT			0x1	// ������ ��ü�� ������ ������ �����ϴ� ���´�.
#define ITEMATB_NOTRADE			0x2	// �ŷ� �Ұ� ǰ��. 
#define ITEMATB_FIRSTACTION		0x4	// ����ġ ������. 
#define ITEMATB_FIRSTWARITEM	0x8	// ����ǰ���� ����ġ�Ǵ� ������ 

#define ITEMATB_WEAPON			0x10	// ������� �Ӽ��� ���´�.
#define ITEMATB_ARMOUR			0x20
#define ITEMATB_UPARMOUR		0x40
#define ITEMATB_NEARWEAPON		0x80
#define ITEMATB_FARWEAPON		0x100
#define ITEMATB_HELMET			0x200
#define ITEMATB_BELT			0x400
#define ITEMATB_RING			0x800
#define ITEMATB_NECK			0x1000
#define ITEMATB_SHOES			0x2000
#define ITEMATB_HAT				0x4000

#define ITEMATB_BOW				0x8000
#define ITEMATB_SWORD			0x10000
#define ITEMATB_GUN				0x20000
#define ITEMATB_SPEAR			0x40000
#define ITEMATB_STAFF			0x80000
#define ITEMATB_AXE				0x100000

#define ITEMATB_HEAL			0x400000
#define ITEMATB_BOOK			0x800000
#define ITEMATB_MINERAL			0x1000000
#define ITEMATB_ANIMAL			0x2000000
#define ITEMATB_CLOTH			0x4000000
#define ITEMATB_SCROLL			0x8000000

#define ITEMATB_ETC				0x10000000
#define ITEMATB_REPAIR			0x20000000
#define ITEMATB_DOLL			0x40000000
#define ITEMATB_TICKET			0x80000000

//---------------------------------
// �� �����ۿ� �����Ǵ� Scroll�� �Ӽ��� ���� ( 0 ~31)
//---------------------------------
#define ITEMATTACH_NULL			(0)			// 
#define ITEMATTACH_DURABLE		(1<<0)		// 
#define ITEMATTACH_WEAPON		(1<<1)		// 
#define ITEMATTACH_ARMOUR		(1<<2)		// 
#define ITEMATTACH_NECK			(1<<3)		// 
#define ITEMATTACH_RING			(1<<4)		// 
#define ITEMATTACH_BELT			(1<<5)		// 
#define ITEMATTACH_SHOES		(1<<6)		// 
#define ITEMATTACH_HELMET		(1<<7)		// 
#define ITEMATTACH_HAT			(1<<8)		// 
#define ITEMATTACH_BAG	 		(1<<9)		// 
#define ITEMATTACH_MANTLE 		(1<<10)		// 
#define ITEMATTACH_DRESS		(1<<11)		// 
#define ITEMATTACH_NEARWEAPON	(1<<12)		// 
#define ITEMATTACH_FARWEAPON	(1<<13)		// 	
#define ITEMATTACH_UPARMOUR		(1<<14)		// 
#define ITEMATTACH_SKILLUPDRESS	(1<<15)		// ������ų ��� �Ǻ��� ���� 
#define ITEMATTACH_USEWEAPONUPDRESS	(1<<16)	// ����� ��� �Ǻ��� ���� 




#define MAX_ITEM_PER_PERSON		105
#define MAX_SHAPE_ITEM			15		// ��񰡴��� ��ǰ�� ��. 	
#define MAX_INVITEM_PER_PERSON	60		// ����� ���� ��� �κ� �հ�. 
#define MAX_ITEM_PER_INVENTORY	20
#define MAX_ITEM_PILE_NUMBER	10000				// �Ѱ��� �����۾ȿ� ��ø�� �� �ִ� �������� ����. 

#define MAX_DURABILITY			1000	// ������ �������� �ִ밪. 
#define FOREVER_DURABILITY		1001	// �������� �Ҹ���� �ʴ� ����. 	


#define EQUIPSET_PERSON				1
#define EQUIPSET_SUMMON1			2
#define EQUIPSET_SUMMON2			3

//-----------------------------------
// Person�� ������ ��ġ. 
//-----------------------------------
#define PERSONITEM_HELMET		0
#define PERSONITEM_ARMOUR		1
#define PERSONITEM_WEAPON1		2
#define PERSONITEM_NECK			3	
#define PERSONITEM_RING1		4
#define PERSONITEM_RING2		5
#define PERSONITEM_BELT			6
#define PERSONITEM_SHOES		7
#define PERSONITEM_WEAPON2		8		
#define PERSONITEM_MANTLE		9
#define PERSONITEM_BAG			10
#define PERSONITEM_HAT			11
#define PERSONITEM_DRESS		12
#define PERSONITEM_RESERVED0	13
#define PERSONITEM_RESERVED1	14


#define PERSONITEM_INV0			15
#define PERSONITEM_INV1			16
#define PERSONITEM_INV2			17
#define PERSONITEM_INV3			18
#define PERSONITEM_INV4			19
#define PERSONITEM_INV5			20

#define PERSONITEM_HORSE0		35

#define PERSONITEM_BAG0			55

#define PERSONITEM_SUMMON1EQUIP0	75	

#define PERSONITEM_SUMMON2EQUIP0	90



//---------------------------------
// ȿ���� ���� 
//---------------------------------
#define ITEMSOUND_SELECT		1		// ���ý� ȿ����. 
#define ITEMSOUND_USE			2		// ���� ȿ����. 
#define ITEMSOUND_REPAIR		3		// ������ ȿ����. 
#define ITEMSOUND_MAKE			4		// ���۽� ȿ����. 


//--------------------------------
// ������ ���. (������ �ٲ�� �ȵȴ�.)
//--------------------------------
#define SCROLL_UNIQUE_FUNCTION_UPHITRATE			1		// ������ ���߷� ���. 
#define SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE			2		// �� ������ ����. 
#define SCROLL_UNIQUE_FUNCTION_UPCRITICAL			3		// ������ �ʻ�� ��� 
#define SCROLL_UNIQUE_FUNCTION_POISON				4		// �� 
#define SCROLL_UNIQUE_FUNCTION_ICE					5		// ����
#define SCROLL_UNIQUE_FUNCTION_DRAIN				6		// DRAIN
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPAXE		7		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSPEAR		8		// â������ ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSTAFF		9		// ������������ ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSWORD		10		// �������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBOW		11		// Ȱ������ ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPGUN		12		// �������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPARMOUR	13		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHELMET	14		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPDRESS		15		// �Ǻ������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHAT		16		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSHOES		17		// �Ź������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBELT		18		// ��������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPNECK		19		// ����������� ��� 
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING		20		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_UPMAXDURABILITY		21		// �������� �ִ� ������ ��� 

#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD		22		// ������� ��� - Į 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR		23		// ������� ��� - â 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE		24		// ������� ��� - ���� 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW		25		// ������� ��� - Ȱ
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN		26		// ������� ��� - ��  
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF		27		// ������� ��� - ������

//-------------------------------
// �κ���� 
//-------------------------------
#define INVMODE_PERSON					1		// ��� �κ� 
#define INVMODE_HORSE					2		// ��	�κ� 
#define INVMODE_BAG						3		// ���� �κ� 
#define INVMODE_ALL						4		// ���� ��� �κ��� ��� �˻�. 


#define CANADDINV_FAIL_FULL				1		// �κ��� ���ڸ��� ��� �߰��� ��  ����. 


//------------------------------
// ���â�� ��� �Ұ� ����. 
//------------------------------
#define ITEMEQUIP_FAIL_OUTOFSKILL		1
#define ITEMEQUIP_FAIL_OUTOFLEVEL		2
#define ITEMEQUIP_FAIL_OUTOFSTR			3	
#define ITEMEQUIP_FAIL_OUTOFDEX			4
#define ITEMEQUIP_FAIL_OUTOFMAG			5
#define ITEMEQUIP_FAIL_OUTOFVIT			6
#define ITEMEQUIP_FAIL_OUTOFHND			7	
#define ITEMEQUIP_FAIL_FORWOMAN			8
#define ITEMEQUIP_FAIL_FORMAN			9
#define ITEMEQUIP_FAIL_OUTOFFAME		10
#define ITEMEQUIP_FAIL_NOSUMMONHERO		11
#define ITEMEQUIP_FAIL_OUTOFSUMMONLEVEL	12
#define ITEMEQUIP_FAIL_NOEQUIPFORHERO	13	// ��ȯ������ ����ϴ� ���������� �ƴϴ�. 

class cltItemManagerCommon;
class cltItem;
class cltSummonScroll;
//--------------------------------------------
// OldItem
//--------------------------------------------
class cltItemWeaponOld{
public:
	UI32 uiDurability:		10;
	UI32 uiMaxDurability:	10;
	UI32 uiMinDamage:		11;
	UI32 uiMaxDamage:		11;
};

class cltItemArmourOld{
public:
	UI16 uiDurability;
	UI16 uiMaxDurability;

	UI16 uiAC;
};

class cltItemRingOld
{
public:
	UI16 uiDurability;
	UI16 uiMaxDurability;
	UI16 uiAC;
	UI08 uiStr;
	UI08 uiDex;
	UI08 uiVit;
	UI08 uiMag;
};
class cltItemNeckOld{
public:
	UI16 uiDurability;
	UI16 uiMaxDurability;
	
	UI08 uiSkillPointUp;
};
class cltItemShoesOld{
public:
	UI16 uiDurability;
	UI16 uiMaxDurability;
	
	UI16 uiAC;

	UI08 uiMoveSpeed;
};

// �������� ���Ͽ� ũ��. 
#define MAX_ITEM_UNION_BYTE_OLD 16

class cltItemOld{
	public:
		SI16 siUnique;
		SI16 siItemNum;		// �������� ��� �ִ°� ?

	public:
		union
		{
			char			cData8[MAX_ITEM_UNION_BYTE_OLD];
			SI32			siData32[MAX_ITEM_UNION_BYTE_OLD/4];

			cltItemWeaponOld	clItemWeapon;
			cltItemArmourOld	clItemArmour;
			cltItemNeckOld		clItemNeck;
			cltItemShoesOld	clItemShoes;
			cltItemRingOld		clItemRing;
		};

};
//---------------------------------------------------------------------------

// Obj�������� �⺻ ����. (4����Ʈ ) 
class cltItemCommonInfo{
public:
	UI32 uiDurability:		11;			// ���� ������. (0 ~ 2047)
	UI32 uiMaxDurability:	11;			// �ִ� ������. (0 ~ 2047)
	UI32 uiRareInfo:		3;			// ��ǰ���� ����. 
	UI32 uiBrand:			7;			// �귣�� �ĺ���
};

// Obj������ �ɼ� ����. (4����Ʈ) 
class cltItemOptionInfo{
public:
	UI32 uiType1:			6;		// �ɼ��� ����.(0~63)
	UI32 uiPara1:			10;		// �ɼǿ� ���� �Ķ��Ÿ. 
	UI32 uiType2:			6;		// �ɼ��� ����.(0~63)
	UI32 uiPara2:			10;		// �ɼǿ� ���� �Ķ��Ÿ. 
	
	// ������ �ɼ� �ؽ�Ʈ�� ���Ѵ�. 
	bool GetText(char* ptext);
	
};


//---------------------------------------
// ���� �������� ����. 
//---------------------------------------
class cltItemCommon{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;
};

class cltItemWeapon{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32	uiMinDamage:	11;		// �ּ� ���ݷ�. 
	UI32	uiMaxDamage:	11;		// �ִ� ���ݷ�.
	UI32	uiMag:			10;		// ���������� ������ ��� ȿ��. 

	void Init(UI16 dur, UI16 mindmg, UI16 maxdmg, UI16 mag)
	{
		ZeroMemory(this, sizeof(cltItemWeapon));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiMinDamage		= mindmg;
		uiMaxDamage		= maxdmg;
		uiMag			= mag;
	}
	void Set(cltItemWeapon* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemWeapon));
	}
};


class cltItemArmour{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32				uiAC:		12;	// ����. 
	UI32				uiLuck:		12;	// �� 
	UI32				uiSkillUp:	6;	// ��� ���. 


	void Init(UI16 dur, UI16 uiac, UI16 luck, UI16 skillup)
	{
		ZeroMemory(this, sizeof(cltItemArmour));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiAC			= uiac;
		uiLuck			= luck;
		uiSkillUp		= skillup;
	}
	void Set(cltItemArmour* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemArmour));
	}
};

// ���� 
class cltItemBag{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32				uiAC:		10;	// ����. 



	void Init(UI16 dur, UI16 uiac)
	{
		ZeroMemory(this, sizeof(cltItemBag));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiAC			= uiac;
	}
	void Set(cltItemBag* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemBag));
	}
};

// ����. 
class cltItemMantle{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32				uiAC:		10;	// ����. 
	UI32				uiDex:		6;	// ���߷�
	UI32				uiVit:		6;	// ����� 
	UI32				uiStr:		6;	// �ٷ�

	void Init(UI16 dur, UI16 uiac, UI16 str, UI16 dex, UI16 vit)
	{
		ZeroMemory(this, sizeof(cltItemMantle));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiAC			= uiac;
		uiDex			= dex;
		uiVit			= vit;
		uiStr			= str;
	}
	void Set(cltItemMantle* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemMantle));
	}
};

class cltItemRing
{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI08 uiStr;
	UI08 uiDex;
	UI08 uiVit;
	UI08 uiMag;


	void Init( UI16 dur, UI16 uiac, UI08 str, UI08 dex, UI08 vit, UI08 mag )
	{
		ZeroMemory(this, sizeof(cltItemRing));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;
		uiStr			= str;
		uiDex			= dex;
		uiVit			= vit;
		uiMag			= mag;
	}
	void Set(cltItemRing* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemRing));
	}
};


class cltItemNeck{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;
	UI08 uiSkillPointUp;				// ��� ��� ���� . (� ��������� cltItemInfo�� ��� �ִ�.) 

	void Init(UI16 dur, UI08 SkillPointUp)
	{
		ZeroMemory(this, sizeof(cltItemNeck));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiSkillPointUp = SkillPointUp;
	}

	void Set(cltItemNeck* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemNeck));
	}
};

class cltItemShoes{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;
	UI32				uiAC:			10;		// ����. 
	UI32				uiMoveSpeed:	6;		// �̵��ӵ�. 	

	void Init(UI16 dur, UI16 ac, UI08 movespeed)
	{
		ZeroMemory(this, sizeof(cltItemShoes));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiAC			= ac;
		uiMoveSpeed		= movespeed;
	}

	void Set(cltItemShoes* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemShoes));
	}
};

// ���� 
class cltItemTool{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	void Init(UI16 dur)
	{
		ZeroMemory(this, sizeof(cltItemTool));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;
	}
	
	void Set(cltItemTool* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemTool));
	}
};

// �������� ���Ͽ� ũ��. 
#define MAX_ITEM_UNION_BYTE 12

//-------------------------------------------
// �������� ���� �����Ϳ� ���� �������� �Ѵ�. 
//-------------------------------------------
class cltItemData{
public:
	SI16 siUnique;
	SI16 siItemNum;		// �������� ��� �ִ°� ?
	
public:
	union
	{
		char			cData8[MAX_ITEM_UNION_BYTE];
		SI32			siData32[MAX_ITEM_UNION_BYTE/4];
		
		cltItemCommon	clItemCommon;
		cltItemWeapon	clItemWeapon;
		cltItemArmour	clItemArmour;
		cltItemNeck		clItemNeck;
		cltItemShoes	clItemShoes;
		cltItemRing		clItemRing;
		cltItemTool		clItemTool;
		cltItemBag		clItemBag;
		cltItemMantle	clItemMantle;
	};
	
	void Init()
	{
		ZeroMemory(this, sizeof(cltItemData));
	}
	void Set(const cltItem* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItemData));
	}
	void Set(const cltItemData* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItemData));
	}
	

};

//---------------------------------------
// ������ ���� ����. 
//---------------------------------------
class cltItem{
	public:
		SI16 siUnique;
		SI16 siItemNum;		// �������� ��� �ִ°� ?

	public:
		union
		{
			char			cData8[MAX_ITEM_UNION_BYTE];
			SI32			siData32[MAX_ITEM_UNION_BYTE/4];

			cltItemCommon	clItemCommon;
			cltItemWeapon	clItemWeapon;
			cltItemArmour	clItemArmour;
			cltItemNeck		clItemNeck;
			cltItemShoes	clItemShoes;
			cltItemRing		clItemRing;
			cltItemTool		clItemTool;
			cltItemBag		clItemBag;
			cltItemMantle	clItemMantle;
		};

	cltItem()
	{
		ZeroMemory(this, sizeof(cltItem));
		
		siItemNum = 0;		

	};
	cltItem(SI32 siUnique);
	cltItem(SI32 siUnique, cltItemWeapon* pcldata);
	cltItem(SI32 siUnique, cltItemArmour* pcldata);
	cltItem(SI32 siUnique, cltItemNeck* pcldata);
	cltItem(SI32 siUnique, cltItemShoes* pcldata);
	cltItem(SI32 siUnique, cltItemRing* pcldata);
	cltItem(SI32 siUnique, cltItemTool* pcldata);
	cltItem(SI32 siUnique, cltItemBag* pcldata);
	cltItem(SI32 siUnique, cltItemMantle* pcldata);

	void Init()
	{
		ZeroMemory(this, sizeof(cltItem));
	}
	void Set(const cltItem* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}
	void Set(const char* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}
	void Set(const cltItemData* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}


	SI32 GetImage(cltItemManagerCommon* pclItemManager);
	const char* GetShortName(cltItemManagerCommon* pclItemManager);
	bool GetFullName(cltItemManagerCommon* pclItemManager, char* pname);
	// �������� �̸��� ������ ���´�. 
	bool GetFullNameNNum(cltItemManagerCommon* pclItemManager, char* pname);
	char* GetArmCode(cltItemManagerCommon* pclItemManager);

	
	// �������� �� ������ ����� �޾Ҵ��� Ȯ���Ѵ�.
	BOOL CheckType(cltItemManagerCommon* pclItemManager, SI32 orgtype);

	// �������� Ÿ���� ã�´�. 
	SI32 GetType(cltItemManagerCommon* pclItemManager)const;
	
	// �������� ���ݻ�Ÿ��� ã�´�. 
	SI32 GetAttackRange(cltItemManagerCommon* pclItemManager)const;

	// �������� ����Ÿ���� ���Ѵ�. 
	SI32 GetAttackType(cltItemManagerCommon* pclItemManager)const;

	// �������� �����ֱ⸦  ã�´�. 
	SI32 GetAttackInterval(cltItemManagerCommon* pclItemManager)const;


	// �ּ� �������� ���Ѵ�. 
	SI32 GetMinDamage(cltItemManagerCommon* pclItemManager)const;
	// �ִ� �������� ���Ѵ�. 
	SI32 GetMaxDamage(cltItemManagerCommon* pclItemManager)const;
	
	// �ּ� �������� �����Ѵ�. 
	SI32 SetMinDamage(cltItemManagerCommon* pclItemManager, SI32 damage);
	// �ִ� �������� �����Ѵ�. 
	SI32 SetMaxDamage(cltItemManagerCommon* pclItemManager, SI32 damage);


	// �ٷ��� ���Ѵ�. 
	SI32 GetEquipStr(cltItemManagerCommon* pclItemManager)const;
	// ���߷��� ���Ѵ�. 
	SI32 GetEquipDex(cltItemManagerCommon* pclItemManager)const;
	// ������� ���Ѵ�. 
	SI32 GetEquipVit(cltItemManagerCommon* pclItemManager)const;
	// ������ ���Ѵ�. 
	SI32 GetEquipMag(cltItemManagerCommon* pclItemManager)const;

	// ���ɷ��� ���Ѵ� 
	SI32 GetAC(cltItemManagerCommon* pclItemManager)const;
	
	// ��� �ɷ��� �����Ѵ�. 
	SI32 SetAC(cltItemManagerCommon* pclItemManager, SI32 ac);

	
	// ���� ���Ѵ� 
	SI32 GetLuck(cltItemManagerCommon* pclItemManager)const;

	// ����� ����� ���Ѵ�. 
	SI32 GetUpgradeSkillLevel(cltItemManagerCommon* pclItemManager, SI32 skillunique);

	// Ư�� ����� ������ ���� ��� ȿ���� ���Ѵ�. 
	SI32 GetSkillScrollUp(cltItemManagerCommon* pclItemManager, SI32 skillunique);




	//----------------------------------------
	// ������ ����. 
	//----------------------------------------
	// �������� ���Ѵ�. 
	SI32 GetDurability()
	{
		return clItemCommon.clCommonInfo.uiDurability;
	}
	// �ִ볻������ ���Ѵ�.
	SI32 GetMaxDurability()
	{
		return clItemCommon.clCommonInfo.uiMaxDurability;
	}
	// ��ǰ/ȣǰ ���θ� ���Ѵ�.
	SI32 GetRareType()
	{
		return clItemCommon.clCommonInfo.uiRareInfo;
	}

	// �������� �����Ѵ�. 
	SI32 SetDurability(cltItemManagerCommon* pclItemManager, UI32 dur);

	// �ִ� �������� ���Ѵ�. 
	SI32 GetMaxDurability(cltItemManagerCommon* pclItemManager)const;
	// �ִ� �������� �����Ѵ�. 
	SI32 SetMaxDurability(cltItemManagerCommon* pclItemManager, UI32 dur);

	// �������� ���δ�. 
	bool DecreaseDurability(cltItemManagerCommon* pclitemmanager, SI32 durvary);

	//----------------------------------------
	// �̵��ӵ� ���� 
	//----------------------------------------
	SI32 GetMoveSpeed(cltItemManagerCommon* pclItemManager)const;


	// �����ۿ��ٰ� �������� ���Ѵ�. 
	bool Add(cltItemManagerCommon* pclItemManager, cltItem* pclitem);

	// �������� ���� ������ ���ϴ� �Լ�. 
	// numcomp : �������� ���ƾ� �ϴ��� ����. 
	BOOL IsSame(const cltItem* pclitem, bool numcomp);

	
	void Set(cltItem* pclitem)
	{
		if(pclitem == NULL)return ;

		memcpy(this, pclitem, sizeof(cltItem));
	}

	// ���Ը� ���Ѵ�.������ ���� ���Ե� �þ��.
	SI32 GetWeight(cltItemManagerCommon* pclItemManager, BOOL mode);

	//----------------------------------------------
	// ������ ���� ����. 
	//----------------------------------------------
	SI16 GetItemNum()const{return siItemNum;}
	void SetItemNum(SI16 itemnum)
	{
		if(itemnum > MAX_ITEM_PILE_NUMBER)
		{
			siItemNum	= MAX_ITEM_PILE_NUMBER;
		}
		else if(itemnum <0)
		{
			siItemNum	= 0;
		}
		else
		{
			siItemNum	= itemnum;
		}
	}

	// �������� ���� ���δ�. 
	SI32 Increase(SI32 amount);
	// �������� ���� ���δ�. 
	SI32 Decrease(SI32 amount);

	// ��ø�� �Ǵ� ���������� Ȯ���Ѵ�. 
	bool CanPile(cltItemManagerCommon* pclItemManager);

	// ������ ������ ���������� Ȯ���Ѵ�. 
	bool CanRepair(cltItemManagerCommon* pclItemManager);
	
	// �� �������� ����µ� �ʿ��� ��ų�� �������� Ȯ���Ѵ�. 
	SI32 GetMakeSkill(cltItemManagerCommon* pclItemManager);
	
	// �� ������ �⺻ ���߷��� ���Ѵ�. 
	SI32 GetDefaultHitRate(cltItemManagerCommon* pclItemManager);


	//--------------
	// ��ǰ��. 
	//-------------
	// ��⸦ ä���ִ� ������ ã�´�.
	SI32 GetHungry(cltItemManagerCommon* pclItemManager)const;

	//-------------
	//���.
	//-------------
	// ü���� ȸ�������ִ� ����. 
	SI32 GetLife(cltItemManagerCommon* pclItemManager)const;
	// �������� ȸ�������ִ� ����. 
	SI32 GetMana(cltItemManagerCommon* pclItemManager)const;
	// ġ���� �� �� �ִ� ������ ����ũ�� ã�´�. 
	SI32 GetDisease(cltItemManagerCommon* pclItemManager)const;


	//---------------
	// å��
	//---------------
	//������Ű�� ��ų�� ����ũ
	SI32 GetSkillUnique(cltItemManagerCommon* pclItemManager)const;
	//����� ���� ����. 
	SI32 GetSkillLevelLimit(cltItemManagerCommon* pclItemManager)const;
	

	// �������� �����Ѵ�. 
	bool Repair(cltItemManagerCommon* pclItemManager, SI32 reducedur);
	

};


//---------------------------------------
// ĳ������ ������ ���� ����. 
//---------------------------------------
class cltPItemInfo{
public:
	cltItem		clItem[MAX_ITEM_PER_PERSON];

	cltPItemInfo(){};
	~cltPItemInfo(){};

	void Set(cltPItemInfo* pclitemmanager);

	void Init()
	{
		SI32 i;

		for(i = 0; i < MAX_ITEM_PER_PERSON;i++)
		{
			clItem[i].Init();
		}
	}

	// ��ü�� ���Ը� ���´�. 
	SI32 GetTotalWeight(cltItemManagerCommon* pclItemManager);

	// ������ Ÿ���� ���Ѵ�. 
	SI32 GetWeaponType(cltItemManagerCommon* pclItemManager, SI16 activeweapon);

	// ������ ��Ÿ��� ���Ѵ�. 
	SI32 GetWeaponAttackRange(cltItemManagerCommon* pclItemManager, SI16 activeweapon);

	// ������ �ּ� �������� ���Ѵ�. 
	SI32 GetWeaponMinDamage(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	// ������ �ִ� �������� ���Ѵ�. 
	SI32 GetWeaponMaxDamage(cltItemManagerCommon* pclItemManager, SI16 activeweapon);

	// ������ �ٷ��� ���Ѵ�. 
	SI32 GetEquipStr(cltItemManagerCommon* pclItemManager);
	// ������ ���߷��� ���Ѵ�. 
	SI32 GetEquipDex(cltItemManagerCommon* pclItemManager);
	// ������ ������� ���Ѵ�. 
	SI32 GetEquipVit(cltItemManagerCommon* pclItemManager);
	// ������ ������ ���Ѵ�. 
	SI32 GetEquipMag(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	
	
	//=====================================
	// ������ ���߷� ����� ���Ѵ�. 
	SI32 GetEquipHitRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	// ������ �ʻ�� ����� ���Ѵ�. 
	SI32 GetEquipCriticalHitRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	// ����� ������ ���Ҹ� ���Ѵ�. 
	SI32 GetDamageReduceRate(cltItemManagerCommon* pclItemManager);
	//=====================================
	// �� ������ �ߵ��� ����� ���Ѵ�. 
	SI32 GetEquipPoisonRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	// �� ������ �����Ѽ�Ȯ�� ����� ���Ѵ�. 
	SI32 GetEquipIceRate(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	// �Ź��� �����Ȯ�� ����� ���Ѵ�. (�Ÿ��� ������ �����Ǿ� �ִ�)
	SI32 GetEquipDrainRate(cltItemManagerCommon* pclItemManager,SI16 active = PERSONITEM_SHOES );
	//=====================================
	
	// ������ AC�� ���Ѵ�. 
	SI32 GetAC(cltItemManagerCommon* pclItemManager);
	
	// ������ ���� ���Ѵ�. 
	SI32 GetLuck(cltItemManagerCommon* pclItemManager);
	
	// �Ź��� �̵��ӵ��� ���Ѵ�. 
	SI32 GetMoveSpeed(cltItemManagerCommon* pclItemManager);
	
	// ������� ��� ����� ���Ѵ�. 
	SI32 GetUpgradeSkillLevel(cltItemManagerCommon* pclItemManager, SI32 skillunique);
	
	// ������ ���� Ÿ���� ���Ѵ�. 
	SI32 GetWeaponAttackType(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	
	// ������ ���� �ֱ⸦ ���Ѵ�. 
	SI32 GetWeaponAttackInterval(cltItemManagerCommon* pclItemManager, SI16 activeweapon);
	
	// �κ��丮�� �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
	bool CanAddInv(cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,
		SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue);
	
	// �κ��丮�� �������� �߰��Ѵ�. 
	bool AddInv(cltItemManagerCommon* pclItemManager, cltItem* pclitem);
	
	// �κ��丮 �������߿��� �ϳ��� �����ϰ� ���´�. 
	bool RobInv(SI32* pitempos, cltItem* pclitem);
	
	bool IsSame(cltPItemInfo* pcliteminfo,  bool numcomp );
	
	// �־��� �����۰� ��Ȯ�ϰ� ��ġ�ϴ� �������� ã�Ƽ� �� ��ġ�� �����Ѵ�. 
	SI32 FindItemInv(cltItem* pclitem, bool numcomp);

	// �־��� �����۰� ��Ȯ�ϰ� ��ġ�ϴ� �������� ã�Ƽ� �� ��ġ�� �����Ѵ�. 
	SI32 FindItemInv(SI32 itemunique);

	
	// unique�� �������� ��� ���� �ִ°� ?
	SI32  GetItemNum(SI32 itemunique);
	
	// unique�� �������� �κ��� �����ϴ°� ?
	SI32  GetItemPos(SI32 itemunique);
	SI32  GetItemTotalPos(SI32 itemunique);

	// Ư�� �����۵��� �� �κ��� �� �� �ִ°�. 
	// �� �� �ִٸ� ��� ��ġ�� �� �� �ִ°��� ���س���. 
	bool CanInputItemList(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32 itemlistnum, SI16* pclpos);
	
	// Ư�� �������� ���ǰ�� ���Ǿ� �ִ°� ?
	bool HaveInEquip(SI32 itemunique);
	
	// ��� ���ǰ�� ���������� ���Ǿ� �ִ°� ?
	bool IsAllProperEquip(cltItemManagerCommon* pclItemManager, SI16* punique, SI16* ppos);
	
	// ���� ��ǰ�� ������ �ִ°�?
	bool IsHorseHaveItem();
	
	// ���濡  ��ǰ�� ������ �ִ°�?
	bool IsBagHaveItem();

	// ���� ��� ������ ����� ���� �ִ°� ?
	// skill : SKILL_USESWORD1 ...
	bool UseWeasponSkillScroll(cltItemManagerCommon* pclItemManager,SI32 skill);
	UI32 UseWeasponSkillScrollNum(cltItemManagerCommon* pclItemManager,SI32 skill);


	cltItem* GetEquipSet(SI32 equipset)
	{
		switch(equipset)
		{
		case EQUIPSET_PERSON:	return &clItem[0];
		case EQUIPSET_SUMMON1:	return &clItem[PERSONITEM_SUMMON1EQUIP0];
		case EQUIPSET_SUMMON2:	return &clItem[PERSONITEM_SUMMON2EQUIP0];
		}

		MessageBox(NULL, "vefs2", "vefsw", MB_OK);
		return &clItem[0];
	}
	
};

//---------------------------------------------------
// �Ⱓ�� �ͼ� ������ ����
//---------------------------------------------------
#define MAX_ITEMNUM_PER_LIMITDATEITEM	5


class cltPLimitDateItemInfo
{
public:
	SI32		siItemUnique[MAX_ITEMNUM_PER_LIMITDATEITEM];
	SI32		siItemLimitDate[MAX_ITEMNUM_PER_LIMITDATEITEM];

public:
	cltPLimitDateItemInfo(){};
	~cltPLimitDateItemInfo(){};

	void Set(cltPLimitDateItemInfo * pcllimitdateiteminfo)
	{
		memcpy ( this, pcllimitdateiteminfo, sizeof( cltPLimitDateItemInfo ));
	}

	void Set(SI32* itemunique,SI32* limitdate)
	{
		for ( SI32 i = 0 ; i < MAX_ITEMNUM_PER_LIMITDATEITEM ; i ++ )
		{
			siItemUnique[i] = itemunique[i] ;
			siItemLimitDate[i] = limitdate[i] ;
		}
	}

	bool Delete(SI32 itemunique)
	{
		for ( SI32 i = 0 ; i < MAX_ITEMNUM_PER_LIMITDATEITEM ; i ++ )
		{
			if ( siItemUnique[i] == itemunique )
			{
				siItemUnique[i] = 0 ;
				siItemLimitDate[i] = 0 ;
				return true ;
			}
		}

		return false ;
	}

	bool Add(SI32 itemunique,SI32 limitdate)
	{
		for ( SI32 i = 0 ; i < MAX_ITEMNUM_PER_LIMITDATEITEM ; i ++ )
		{
			if ( siItemUnique[i] == 0 )
			{
				siItemUnique[i] = itemunique ;
				siItemLimitDate[i] = limitdate ;
				return true ;
			}
		}

		return false ;
	}

};

//----------------------------------------------------
// ������ �� ������ ����
//----------------------------------------------------
#define MAX_ITEMNUM_PER_ITEMMALL	8 // ������ �������� �ִ� ������ ����

class cltPItemMallItemInfo
{
public:
	cltPItemMallItemInfo(){};
	~cltPItemMallItemInfo(){};
	
	void Set(cltPItemMallItemInfo * pclitemmall)
	{
		memcpy ( this, pclitemmall, sizeof( cltPItemMallItemInfo ));
	}
	
	void Set( cltItem * pclitemmallitem ,SI32 *itemid,SI32 total,SI32 page,bool existence)
	{
		memcpy ( clItem, pclitemmallitem, sizeof( cltItem ) * MAX_ITEMNUM_PER_ITEMMALL );
		memcpy ( siItemID, itemid, sizeof( SI32 ) * MAX_ITEMNUM_PER_ITEMMALL );
		
		siTotalItemNum = total;
		siListPage = page;
		
		bItemExistence = existence ;
	}
	
	void SetItem(cltItem * pclitemmallitem)
	{
		memcpy ( clItem, pclitemmallitem, sizeof( cltItem ) * MAX_ITEMNUM_PER_ITEMMALL );
	}
	cltItem GetItem(SI32 pos)
	{
		cltItem pclitem ;
		pclitem.Init();
		if ( pos < 0 || pos >= MAX_ITEMNUM_PER_ITEMMALL ) return pclitem ;
		return clItem[pos];
	}
	
	void SetItemID(SI32 * itemid)
	{
		memcpy ( siItemID, itemid, sizeof( SI32 ) * MAX_ITEMNUM_PER_ITEMMALL );
	}
	SI32 GetItemID(SI32 pos)
	{
		SI32 itemid = 0 ;
		if ( pos < 0 || pos >= MAX_ITEMNUM_PER_ITEMMALL ) return itemid ;
		return siItemID[pos];
	}
	
	void SetTotalItemNum(SI32 total)
	{
		siTotalItemNum = total;
	}
	SI32 GetTotalItemNum()
	{
		return siTotalItemNum ;
	}
	
	void SetListPage(SI32 page)
	{
		siListPage = page;
	}
	SI32 GetListPage()
	{
		return siListPage ;
	}
	
	void SetExistence(bool existence)
	{
		bItemExistence = existence ;
	}
	bool GetExistence()
	{
		return bItemExistence ;
	}
	
	void Init()
	{
		for(SI32 i = 0; i < MAX_ITEMNUM_PER_ITEMMALL;i++)
		{
			clItem[i].Init();
		}
		
		SetTotalItemNum(0);
		SetListPage(0);
		
		SetExistence(false);
	}
	
private:
	cltItem		clItem[MAX_ITEMNUM_PER_ITEMMALL];
	SI32		siItemID[MAX_ITEMNUM_PER_ITEMMALL];
	
	SI32		siTotalItemNum; // �� ������ ����
	SI32		siListPage; // ���� ���õ� ����Ʈ�� ������ �� 1~
	
	bool		bItemExistence; // �� �������� �ִ��� ������
	
};

//-------------------------------------------------
// �� ������ ���
//-------------------------------------------------
#define MAX_SHIP_WEAPON_STG_TYPE_CANNON_ITEM_NUMBER			5		// ���� �Ǵ� ��� ���� �ִ��
#define MAX_SHIP_WEAPON_STG_TYPE_GUN_ITEM_NUMBER			5		// �� �Ǵ� Ȱ�� ���� �ִ��
#define MAX_SHIP_TRANSPORT_STG_ITEM_NUMBER					10		// �� �� â���� ���� �� �ִ� ������ �ִ� ����

#define MAX_SHIP_TRANSPORT_STG_ITEM_CONSUME					10		// ��ĭ�� �������� �Ҹ��ϴ� �ִ� ����.

enum { SHIP_STG_KIND_WEAPON_TYPE_CANNON, SHIP_STG_KIND_WEAPON_TYPE_GUN, SHIP_STG_KIND_TRANSPORT };	// ������ ��ĭ�̳� ����

class cltPShipStgItemInfo
{
public:
	cltItem clWeaponStgTypeCannonItem[ MAX_SHIP_WEAPON_STG_TYPE_CANNON_ITEM_NUMBER ];
	cltItem clWeaponStgTypeGunItem[ MAX_SHIP_WEAPON_STG_TYPE_GUN_ITEM_NUMBER ];
	cltItem clTransportStgItem[ MAX_SHIP_TRANSPORT_STG_ITEM_NUMBER ];
	
	cltPShipStgItemInfo()
	{
		Init();
	}
	
	void Init()
	{
		memset( this, 0, sizeof( cltPShipStgItemInfo ) );
	}
	
	bool IsHaveItem()
	{
		SI16 i = 0;

		for ( i = 0; i < MAX_SHIP_WEAPON_STG_TYPE_CANNON_ITEM_NUMBER; ++i )
		{
			if ( clWeaponStgTypeCannonItem[ i ].siUnique > 0 )
			{
				return true;
			}
		}

		for ( i = 0; i < MAX_SHIP_WEAPON_STG_TYPE_GUN_ITEM_NUMBER; ++i )
		{
			if ( clWeaponStgTypeGunItem[ i ].siUnique > 0 )
			{
				return true;
			}
		}

		for ( i = 0; i < MAX_SHIP_TRANSPORT_STG_ITEM_NUMBER; ++i )
		{
			if ( clTransportStgItem[ i ].siUnique > 0 )
			{
				return true;
			}
		}

		return false;
	}
	
	void Set( cltPShipStgItemInfo *pShipStgItemInfo )
	{
		memcpy( this, pShipStgItemInfo, sizeof( cltPShipStgItemInfo ) );
	}
	
	void Set( cltItem *pclWeaponStgTypeCannonItemList, cltItem *pclWeaponStgTypeGunItemList, cltItem *pclTransportStgItemList )
	{		
		memcpy ( clWeaponStgTypeCannonItem, pclWeaponStgTypeCannonItemList, sizeof( cltItem ) * MAX_SHIP_WEAPON_STG_TYPE_CANNON_ITEM_NUMBER );
		memcpy ( clWeaponStgTypeGunItem, pclWeaponStgTypeGunItemList, sizeof( cltItem ) * MAX_SHIP_WEAPON_STG_TYPE_GUN_ITEM_NUMBER );
		memcpy ( clTransportStgItem, pclTransportStgItemList, sizeof( cltItem ) * MAX_SHIP_TRANSPORT_STG_ITEM_NUMBER );
	}
	
	SI16 GetAddItemPos( SI08 StgKind, bool PileSwitch, SI16 *pItemPos, cltItem *pclItem );
	bool CanMove( SI08 StgKind, bool PileSwitch, SI16 ItemPos, cltItem *pclItem );
	SI16 GetShipEmptyPos( SI08 StgKind );	
	SI16 GetShipItemPos( SI08 StgKind, SI32 ItemUnique );	
	bool SetItem( SI08 StgKind, SI16 ItemPos, cltItem *pclItem );	
	void TransportStgItemConsume( SI16 *ItemPosList, cltItem *pclItemList );
		
	SI32 GetStgTotalWeight( cltItemManagerCommon* pclItemManager, SI08 StgKind );	
	SI32 GetStgWeaponWeight( cltItemManagerCommon* pclItemManager );
};

//-------------------------------------------------
// ������ ����� �����۵� ���� 
//-------------------------------------------------
class cltPShipItemInfo{
public:
	cltPShipStgItemInfo clShipStgItemInfo[ MAX_SHIP_PER_PERSON ];
	
	cltPShipItemInfo()
	{
		Init();
	}
	
	void Init()
	{
		memset( this, 0, sizeof( cltPShipItemInfo ) );
	}
	
	void Init( SI16 Ref )
	{
		clShipStgItemInfo[ Ref ].Init();
	}
	
	~cltPShipItemInfo(){};
	
	void Set( cltPShipItemInfo *pclShipItemInfo )
	{
		memcpy( this, pclShipItemInfo, sizeof( cltPShipItemInfo ) );
	}
	
	void Set( SI16 ShipRef, cltItem *pclWeaponStgTypeCannonItemList, cltItem *pclWeaponStgTypeGunItemList, cltItem *pclTransportStgItemList )
	{
		clShipStgItemInfo[ ShipRef ].Set( pclWeaponStgTypeCannonItemList, pclWeaponStgTypeGunItemList, pclTransportStgItemList );
	}
	
	bool SetItem( SI16 ShipRef, SI08 StgKind, SI16 ItemPos, cltItem *pclItem );
	SI16 GetAddItemPos( SI16 ShipRef, SI08 StgKind, bool PileSwitch, SI16 *pItemPos, cltItem *pclItem );	
	bool CanMove( SI16 ShipRef, SI08 StgKind, bool PileSwitch, SI16 ItemPos, cltItem *pclItem );	
	void TransportStgItemConsume( SI16 ShipRef, SI16 *ItemPosList, cltItem *pclItemList );	
	SI16 GetShipItemPos( SI16 ShipRef, SI08 StgKind, SI16 ItemUnique );
};

// cltItemOld������ cltItem������ �ٲ��ش�.
inline bool ConvertItemToitem2(cltItemOld* pclitem, cltItem* pclitem2)
{

	pclitem2->Init();
	
	SI32 unique = pclitem->siUnique;

	pclitem2->siUnique	= pclitem->siUnique;
	pclitem2->siItemNum	= pclitem->siItemNum;

	// �����. 
	if(unique <= 599)
	{
		pclitem2->clItemWeapon.clCommonInfo.uiMaxDurability		= pclitem->clItemWeapon.uiMaxDurability;
		pclitem2->clItemWeapon.clCommonInfo.uiDurability		= pclitem->clItemWeapon.uiDurability;
		pclitem2->clItemWeapon.uiMinDamage						= pclitem->clItemWeapon.uiMinDamage;
		pclitem2->clItemWeapon.uiMaxDamage						= pclitem->clItemWeapon.uiMaxDamage;
	}
	// ����. 
	else if(unique <= 999)
	{
		pclitem2->clItemArmour.clCommonInfo.uiMaxDurability	= pclitem->clItemArmour.uiMaxDurability;
		pclitem2->clItemArmour.clCommonInfo.uiDurability	= pclitem->clItemArmour.uiDurability;
		pclitem2->clItemArmour.uiAC							= pclitem->clItemArmour.uiAC;
	}
	// ����̷�. 
	else if(unique <= 1499)
	{
		pclitem2->clItemNeck.clCommonInfo.uiMaxDurability	= pclitem->clItemNeck.uiMaxDurability;
		pclitem2->clItemNeck.clCommonInfo.uiDurability	= pclitem->clItemNeck.uiDurability;
		pclitem2->clItemNeck.uiSkillPointUp				= pclitem->clItemNeck.uiSkillPointUp;
	}
	// �Ź߷�. 
	else if(unique <= 1999)
	{
		pclitem2->clItemShoes.clCommonInfo.uiMaxDurability	= pclitem->clItemShoes.uiMaxDurability;
		pclitem2->clItemShoes.clCommonInfo.uiDurability	= pclitem->clItemShoes.uiDurability;
		pclitem2->clItemShoes.uiAC			= pclitem->clItemShoes.uiAC;
		pclitem2->clItemShoes.uiMoveSpeed	= pclitem->clItemShoes.uiMoveSpeed;
	}
	// ������ .
	else if(unique >= 7500 && unique < 8000)
	{
		pclitem2->clItemRing.clCommonInfo.uiMaxDurability	= pclitem->clItemRing.uiMaxDurability;
		pclitem2->clItemRing.clCommonInfo.uiDurability		= pclitem->clItemRing.uiDurability;
		pclitem2->clItemRing.uiStr							= pclitem->clItemRing.uiStr;
		pclitem2->clItemRing.uiDex							= pclitem->clItemRing.uiDex;
		pclitem2->clItemRing.uiVit							= pclitem->clItemRing.uiVit;
		pclitem2->clItemRing.uiMag							= pclitem->clItemRing.uiMag;
	}
	// ��Ÿ ��� ������. . 
	else 
	{
	}

	return true;
}

#endif
