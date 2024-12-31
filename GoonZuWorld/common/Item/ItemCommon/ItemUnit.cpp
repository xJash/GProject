//---------------------------------
// 2003/6/9 ���°�
//---------------------------------

#include "cltItem.h"
#include "..\..\Skill\Skill.h"
#include "../../Char/KindInfo/kindinfo.h"

#include "../../../CommonLogic/CommonLogic.h"
#include "../../../CommonLogic/TextMgr/TextMgr.h"

#include "../../Server/Server.h"
#include "../../Server/GachaManager/GachaManager.h"
#include "../../Server/Gacha2Manager/Gacha2Manager.h"

#include "../../../common/Event/event.h"
//#include "../../../common/item/ItemCommon/ItemUnit.h"

//extern cltTextMgr g_pTextMgr;
//extern cltTextMgr g_pHelpMgr;
//extern cltTextMgr g_pStructureMgr;

//class cltItemAvatarNeck;

extern cltCommonLogic*	pclClient;

extern	SI32 skilldata[] =
{
	SKILL_MAKEAXE1,		SCROLL_UNIQUE_FUNCTION_MAKESKILLUPAXE, 0, 
		SKILL_MAKESPEAR1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSPEAR, 0, 
		SKILL_MAKESWORD1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSWORD, 0, 
		SKILL_MAKESTAFF1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSTAFF,  0, 
		SKILL_MAKEBOW1,		SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBOW,  0, 
		SKILL_MAKEGUN1,		SCROLL_UNIQUE_FUNCTION_MAKESKILLUPGUN,  0, 
		SKILL_MAKEARMOUR1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPARMOUR,  0, 
		SKILL_MAKEHELMET1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHELMET,  0, 
		SKILL_MAKEDRESS1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPDRESS,  0, 
		SKILL_MAKEHAT1,		SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHAT,  0, 
		SKILL_MAKESHOES1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSHOES,  0, 
		SKILL_MAKEBELT1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBELT,  0,
		//SKILL_MAKENECK1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPNECK,  0, 
		//cyj �������ۼ� ���� SKILL_MAKERING1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING, 
		//SKILL_USESWORD1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD,  0, 
		//SKILL_USESPEAR1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR, 0, 
		//SKILL_USEAXE1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE, 0, 
		//SKILL_USEBOW1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW, 0, 
		//SKILL_USEGUN1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN,  0, 
		//SKILL_USESTAFF1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF,  0, 
		SKILL_USESWORD1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD,
		SKILL_USESPEAR1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR,
		SKILL_USEAXE1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE,
		SKILL_USEBOW1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW,
		SKILL_USEGUN1,		SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN,
		SKILL_USESTAFF1,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON,	SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF,
		SKILL_ARTIFACT,		SCROLL_UNIQUE_FUNCTION_MAKESKILLUPATIFACT,  0, //��Ƽ��Ʈ 

		0,				0
};

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
extern	SI32 Crystalskilldata[] =
{
		SKILL_SUMMON,				CRYSTALABILITY_SKILL_SUMMON,			0,
		SKILL_FARM,					CRYSTALABILITY_SKILL_FARM,				0,
		SKILL_MINE, 				CRYSTALABILITY_SKILL_MINE,				0,
		SKILL_FISH,					CRYSTALABILITY_SKILL_FISH,				0,
		SKILL_MAKEFOOD,				CRYSTALABILITY_SKILL_MAKEFOOD,			0,
		SKILL_CAPTURE,				CRYSTALABILITY_SKILL_CAPTURE,			0,
		SKILL_HORSETRAINING,		CRYSTALABILITY_SKILL_HORSETRAINING,		0,

		SKILL_MAKEIRON1,			CRYSTALABILITY_SKILL_MAKEIRON1,			0,
		SKILL_MAKETOOL1,			CRYSTALABILITY_SKILL_MAKETOOL1,			0,
		SKILL_MAKEMED,				CRYSTALABILITY_SKILL_MAKEMED,			0,

		SKILL_MAKESWORD1,			CRYSTALABILITY_SKILL_MAKESWORD1, 		0, 
		SKILL_MAKESPEAR1,			CRYSTALABILITY_SKILL_MAKESPEAR1, 		0, 
		SKILL_MAKEAXE1,				CRYSTALABILITY_SKILL_MAKEAXE1,			0, 
		SKILL_MAKESTAFF1,			CRYSTALABILITY_SKILL_MAKESTAFF1,		0, 
		SKILL_MAKEBOW1,				CRYSTALABILITY_SKILL_MAKEBOW1,			0, 
		SKILL_MAKEGUN1,				CRYSTALABILITY_SKILL_MAKEGUN1,			0, 
		SKILL_MAKEARMOUR1,			CRYSTALABILITY_SKILL_MAKEARMOUR1,		0, 
		SKILL_MAKEHELMET1,			CRYSTALABILITY_SKILL_MAKEHELMET1,		0, 		
		SKILL_MAKESHOES1,			CRYSTALABILITY_SKILL_MAKESHOES1,		0, 
		SKILL_MAKEBELT1,			CRYSTALABILITY_SKILL_MAKEBELT1,			0, 

		SKILL_USESWORD1,			CRYSTALABILITY_SKILL_USESWORD1,			0,
		SKILL_USESPEAR1,			CRYSTALABILITY_SKILL_USESPEAR1,			0,
		SKILL_USEAXE1,				CRYSTALABILITY_SKILL_USEAXE1,			0,
		SKILL_USESTAFF1,			CRYSTALABILITY_SKILL_USESTAFF1,			0,
		SKILL_USEBOW1,				CRYSTALABILITY_SKILL_USEBOW1,			0,
		SKILL_USEGUN1,				CRYSTALABILITY_SKILL_USEGUN1,			0,
		SKILL_ARTIFACT,				CRYSTALABILITY_SKILL_ARTIFACT,			0,

		ALL_MAKESKILL_UNIQUE,		CRYSTALABILITY_SKILL_ALLMAKESKILL,		0,
		ALL_WEAPONSKILL_UNIQUE,		CRYSTALABILITY_SKILL_ALLWEAPONSKILL,	0,
		ALL_PRODUCTSKILL_UNIQUE,	CRYSTALABILITY_SKILL_ALLPRODUCTSKILL,	0,
		ALL_ALLSKILL_UNIQUE,		CRYSTALABILITY_SKILL_ALLSKILL,			0,
		ALL_ALLAVATARSKILL_UNIQUE,		CRYSTALABILITY_SKILL_ALLAVATARSKILL,			0,
		
		0, 0, 0
		//SKILL_MAKEDRESS1,			SCROLL_UNIQUE_FUNCTION_MAKESKILLUPDRESS,	0, 
		//SKILL_MAKEHAT1,			SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHAT,		0, 				
		//SKILL_MAKENECK1,			SCROLL_UNIQUE_FUNCTION_MAKESKILLUPNECK,		0, 
		//cyj �������ۼ� ���� SKILL_MAKERING1,	SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING, 
		//SKILL_USESWORD1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD,	0, 
		//SKILL_USESPEAR1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR,	0, 
		//SKILL_USEAXE1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE,		0, 
		//SKILL_USEBOW1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW,		0, 
		//SKILL_USEGUN1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN,		0, 
		//SKILL_USESTAFF1,			SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF,	0, 
};


// ������ �ɼ� �ؽ�Ʈ�� ���Ѵ�. 
bool cltItemOptionInfo::GetText(TCHAR* ptext, SI16 txtSize)
{
	TCHAR temp[256];
	StringCchCopy(ptext, txtSize, TEXT(""));

	for(SI32 i = 0;i < 2;i++)
	{
		UI32 type;
		UI32 para;

		if(i == 0)
		{
			type	= uiType1;
			para	= uiPara1;

		}
		else
		{
			type	= uiType2;
			para	= uiPara2;
		}

		if(type == 0)continue;

		UI32 rate; 
		switch(type)
		{
		case  SCROLL_UNIQUE_FUNCTION_UPHITRATE:
			{
				TCHAR* pText = GetTxtFromMgr(687);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize, temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_UPCRITICAL:	
			{
				TCHAR* pText = GetTxtFromMgr(688);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_POISON:
			{
				TCHAR* pText = GetTxtFromMgr(689);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_ICE:
			{
				TCHAR* pText = GetTxtFromMgr(690);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE:
			{
				TCHAR* pText = GetTxtFromMgr(691);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_DRAIN:
			{
				TCHAR* pText = GetTxtFromMgr(692);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate, '%');
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPAXE:
			{
				TCHAR* pText = GetTxtFromMgr(693);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSPEAR:
			{
				TCHAR* pText = GetTxtFromMgr(694);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSWORD:
			{
				TCHAR* pText = GetTxtFromMgr(695);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);

			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSTAFF:
			{
				TCHAR* pText = GetTxtFromMgr(696);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBOW:
			{
				TCHAR* pText = GetTxtFromMgr(697);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPGUN:
			{
				TCHAR* pText = GetTxtFromMgr(698);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPARMOUR:
			{
				TCHAR* pText = GetTxtFromMgr(699);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHELMET:
			{
				TCHAR* pText = GetTxtFromMgr(700);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPDRESS:
			{
				TCHAR* pText = GetTxtFromMgr(701);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHAT:
			{
				TCHAR* pText = GetTxtFromMgr(702);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSHOES:
			{
				TCHAR* pText = GetTxtFromMgr(703);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBELT:
			{
				TCHAR* pText = GetTxtFromMgr(704);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPNECK:
			{
				TCHAR* pText = GetTxtFromMgr(705);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		/*cyj �������ۼ� ����
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING:
			{
				TCHAR* pText = GetTxtFromMgr(706);
				rate = para / 10;
				sprintf(temp, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		*/
		case SCROLL_UNIQUE_FUNCTION_UPMAXDURABILITY:
			{
				TCHAR* pText = GetTxtFromMgr(707);
//				rate = (float)(para);
				rate = para;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);

			}
			break;				

		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD:
			{
				TCHAR* pText = GetTxtFromMgr(708);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR:
			{
				TCHAR* pText = GetTxtFromMgr(709);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE:
			{
				TCHAR* pText = GetTxtFromMgr(710);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW:
			{
				TCHAR* pText = GetTxtFromMgr(711);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN:
			{
				TCHAR* pText = GetTxtFromMgr(712);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF:
			{
				TCHAR* pText = GetTxtFromMgr(713);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON:
			{
				TCHAR* pText = GetTxtFromMgr(5679);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPATIFACT://��Ƽ��Ʈ.
			{
				TCHAR* pText = GetTxtFromMgr(711);
				rate = para / 10;
				StringCchPrintf(temp, 256, pText, rate);
				StringCchCat(ptext, txtSize,  temp);
			}
			break;
		default:
			MsgBox(TEXT("vdidjf"), TEXT("f38fdsjf:%d"), type);
		}
	}

	if(_tcscmp(ptext, TEXT("")) == 0)
	{
		return false;
	}
	return true;
}


//---------------------------------------
// cltItem
//---------------------------------------

cltItem::cltItem(SI32 siunique)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	uiDateUseDay = siUseDate;

	
}


//cyj  �Ⱓ�� ������
cltItem::cltItem(SI32 siunique, SI32 siUseDate,stElement* element, cltItemWeapon* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemWeapon.Set(pcldata);
	
	uiDateUseDay = siUseDate;

	memcpy(&Element, element, sizeof(stElement));
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate,stElement* element, cltItemArmour* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemArmour.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));
	uiDateUseDay = siUseDate;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate,  cltItemNeck* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemNeck.Set(pcldata);

	uiDateUseDay = siUseDate;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element , cltItemShoes* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemShoes.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));

	uiDateUseDay = siUseDate;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemRing* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemRing.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));

	uiDateUseDay = siUseDate;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemStatusArmour* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemStatusArmour.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));

	uiDateUseDay = siUseDate;
}


cltItem::cltItem(SI32 siunique, SI32 siUseDate, cltItemTool* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemTool.Set(pcldata);

	uiDateUseDay = siUseDate;
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate, cltItemBag* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemBag.Set(pcldata);

	uiDateUseDay = siUseDate;
}


//cyj  ���� ������
/*
cltItem::cltItem(SI32 siunique, cltItemWeapon* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemWeapon.Set(pcldata);
}

cltItem::cltItem(SI32 siunique, cltItemArmour* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemArmour.Set(pcldata);
}


cltItem::cltItem(SI32 siunique, cltItemRing* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemRing.Set(pcldata);
}

cltItem::cltItem(SI32 siunique, cltItemNeck* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemNeck.Set(pcldata);
}

cltItem::cltItem(SI32 siunique, cltItemShoes* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemShoes.Set(pcldata);
}
//cyj  ���� ������ �������

cltItem::cltItem(SI32 siunique, cltItemTool* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemTool.Set(pcldata);
}
*/

cltItem::cltItem(SI32 siunique, cltItemBag* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemBag.Set(pcldata);
}

cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement * element , cltItemMantle* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;


	memcpy(&Element, element, sizeof(stElement));

	clItemMantle.Set(pcldata);

	uiDateUseDay = siUseDate;
}

// �ƹ�Ÿ ����
cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemAvatarMantle* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;


	memcpy(&Element, element, sizeof(stElement));

	clItemAvatarMantle.Set(pcldata);

	uiDateUseDay = siUseDate;
}

// �ƹ�Ÿ ����
cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemAvatarRing* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;


	memcpy(&Element, element, sizeof(stElement));

	clItemAvatarRing.Set(pcldata);

	uiDateUseDay = siUseDate;
}

// �ƹ�Ÿ �����
cltItem::cltItem(SI32 siunique, SI32 siUseDate, cltItemAvatarNeck* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemAvatarNeck.Set(pcldata);

	uiDateUseDay = siUseDate;
}

// �ƹ�Ÿ �Ǻ�
cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemAvatarDress* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemAvatarDress.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));

	uiDateUseDay = siUseDate;
}

// �ƹ�Ÿ ����
cltItem::cltItem(SI32 siunique, SI32 siUseDate, stElement* element, cltItemAvatarHat* pcldata)
{
	ZeroMemory(this, sizeof(cltItem));

	siItemNum = 1;		// �ּ��� �Ѱ��� �ִ�. 

	siUnique = siunique;

	clItemAvatarHat.Set(pcldata);

	memcpy(&Element, element, sizeof(stElement));

	uiDateUseDay = siUseDate;
}

// �������� Ÿ���� ã�´�. 
SI32 cltItem::GetType(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		SI32 type = pclItemManager->pclItemInfo[ref]->siType;
		return type;
	}

	return 0;
}


//�ƹ�Ÿ �������� Ÿ���� ã�´�. 
SI32 cltItem::GetAavatarType(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		SI32 type = pclItemManager->pclItemInfo[ref]->siType;

		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				return type;
				break;
			default : 
				return 0;
				break;
		}				
	}

	return 0;
}

// �������� ����Ÿ���� ã�´�. 
SI32 cltItem::GetAttackType(cltItemManagerCommon* pclItemManager)const
{
	if(pclItemManager == NULL)return 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetAttackType();
	}

	return 0;
}

// �������� �����ֱ⸦  ã�´�. 
SI32 cltItem::GetAttackInterval(cltItemManagerCommon* pclItemManager)const
{
	if(pclItemManager == NULL)return 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetAttackInterval();
	}

	return 0;
}


// �������� ���ݻ�Ÿ��� ã�´�. 
SI32 cltItem::GetAttackRange(cltItemManagerCommon* pclItemManager)const
{
	if(pclItemManager == NULL)return 0;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetAttackRange();
	}

	return 0;
}

// ��⸦ ä���ִ� ������ ã�´�.
SI32 cltItem::GetHungry(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetHungry();
	}

	return 0;
}


// ġ���� �� �� �ִ� ������ ����ũ�� ã�´�. 
SI32 cltItem::GetDisease(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetDisease();
	}

	return 0;
}

// ü���� ä���ִ� ������ ã�´�.
SI32 cltItem::GetLife(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetLife();
	}

	return 0;
}

// �������� ä���ִ� ������ ã�´�.
SI32 cltItem::GetMana(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetMana();
	}

	return 0;
}

// ������ ���Ѵ�. 
SI32 cltItem::GetEquipMag(cltItemManagerCommon* pclItemManager,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_STAFF:
			temNum = clItemWeapon.uiMag;
			break;
		case ITEMTYPE_RING:
			temNum = clItemRing.uiMag;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiMag;
			break;
		case ITEMTYPE_DRESS:
		case ITEMTYPE_HAT:
			temNum = clItemStatusArmour.uiMag;
			break;
		case ITEMTYPE_CRYSTAL:
			{	
				//KHY - 20090526 - �ƹ�Ÿ ����ü.
				if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_MAG) ||
					(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_MAG))
				{
					temNum =  clItemCrystal.uiCrystalAbilityNum;
				}
			}
			break;
	}

	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_MAG);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_MAG);
				break;
		}				
	}

	return temNum;
}

// �ٷ��� ���Ѵ�. 
SI32 cltItem::GetEquipStr(cltItemManagerCommon* pclItemManager ,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_RING:
			temNum = clItemRing.uiStr;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiStr;
			break;
		case ITEMTYPE_MANTLE:
			temNum =  clItemMantle.uiStr;
			break;
		//case ITEMTYPE_AVATAR_MANTLE:
		//	temNum = clItemAvatarMantle.uiStr;
		//	break;
		case ITEMTYPE_DRESS:
		case ITEMTYPE_HAT:
			temNum =  clItemStatusArmour.uiStr;
			break;
		case ITEMTYPE_CRYSTAL:
			{	
				//KHY - 20090526 - �ƹ�Ÿ ����ü.
				if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_STR) ||
					(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_STR))
				{
					temNum =  clItemCrystal.uiCrystalAbilityNum;
				}
			}
			break;
	}
	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_STR);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_STR);
				break;
		}		
		
	}
	
	return temNum;
}

// ���߷��� ���Ѵ�. 
SI32 cltItem::GetEquipDex(cltItemManagerCommon* pclItemManager ,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;
	
	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_RING:
			temNum =  clItemRing.uiDex;
			break;
		case ITEMTYPE_MANTLE:
			temNum =  clItemMantle.uiDex;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiDex;
			break;
		//case ITEMTYPE_AVATAR_MANTLE:
		//	temNum = clItemAvatarMantle.uiDex;
		//	break;
		case ITEMTYPE_DRESS:
		case ITEMTYPE_HAT:
			temNum =  clItemStatusArmour.uiDex;
			break;
		case ITEMTYPE_CRYSTAL:
				{	
					//KHY - 20090526 - �ƹ�Ÿ ����ü.
					if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_DEX) ||
						(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_DEX))
					{
						temNum =  clItemCrystal.uiCrystalAbilityNum;
					}
				}
				break;
	}
	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_DEX);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_DEX);
				break;
		}		
		
	}

	return temNum;
}

// ������� ���Ѵ�. 
SI32 cltItem::GetEquipVit(cltItemManagerCommon* pclItemManager ,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_RING:
			temNum = clItemRing.uiVit;
			break;
		case ITEMTYPE_MANTLE:
			temNum = clItemMantle.uiVit;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiVit;
			break;
		//case ITEMTYPE_AVATAR_MANTLE:
		//	temNum = clItemAvatarMantle.uiVit;
		//	break;
		case ITEMTYPE_DRESS:
		case ITEMTYPE_HAT:
			temNum = clItemStatusArmour.uiVit;
			break;
		case ITEMTYPE_CRYSTAL:
				{	
					//KHY - 20090526 - �ƹ�Ÿ ����ü.
					if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_VIT) ||
						(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_VIT))
					{
						temNum =  clItemCrystal.uiCrystalAbilityNum;
					}
				}
				break;
	}
	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_VIT);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_VIT);
				break;
		}		
		
	}

	return temNum;
}

// ���� ���Ѵ�. 
SI32 cltItem::GetEquipLuk(cltItemManagerCommon* pclItemManager ,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------

	switch(type)
	{
		case ITEMTYPE_RING:
			temNum = clItemRing.uiLuk;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiLuk;
			break;
		case ITEMTYPE_HAT:
		case ITEMTYPE_DRESS:
			temNum = clItemStatusArmour.uiLuk;
			break;
		case ITEMTYPE_CRYSTAL:
				{	
					//KHY - 20090526 - �ƹ�Ÿ ����ü.
					if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_LUK) ||
						(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_LUK))
					{
						temNum =  clItemCrystal.uiCrystalAbilityNum;
					}
				}
				break;
	}
	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_LUK);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_LUK);
				break;
		}		
		
	}

	return temNum;
}

// �������� ���Ѵ�. 
SI32 cltItem::GetEquipHnd(cltItemManagerCommon* pclItemManager,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_RING:
			temNum =  clItemRing.uiHnd;
			break;
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiHnd;
			break;
		case ITEMTYPE_HAT:
			
		case ITEMTYPE_DRESS:
			temNum =  clItemStatusArmour.uiHnd;
			break;
		case ITEMTYPE_CRYSTAL:
				{	
					//KHY - 20090526 - �ƹ�Ÿ ����ü.
					if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_HND) ||
						(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_HND))
					{
						temNum =  clItemCrystal.uiCrystalAbilityNum;
					}
				}
				break;
	}

	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_HND);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_HND);
				break;
		}		
		
	}

	return temNum;
}

// ���� ���Ѵ�. 
SI32 cltItem::GetEquipWis(cltItemManagerCommon* pclItemManager,SI32* CrystalPer )
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �� ������ ������ �ɷ� �˻�.
	//---------------------------------------------------------------------------------
	switch(type)
	{
		case ITEMTYPE_AVATAR_RING:
			temNum = clItemAvatarRing.uiWis;
			break;

		case ITEMTYPE_CRYSTAL:
				{	
					//KHY - 20090526 - �ƹ�Ÿ ����ü.
					if((clItemCrystal.uiCrystalAbility == CRYSTALABILITY_STATE_WIS) ||
						(clItemCrystal.uiCrystalAbility == CRYSTALABILITY_AVATAR_STATE_WIS))
					{
						temNum =  clItemCrystal.uiCrystalAbilityNum;
					}
				}
				break;
	}

	//---------------------------------------------------------------------------------
	// �ش�������� ������ �ִ�, ����ü�� �ɷ� �߰�.
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//KHY - 20090526 - �ƹ�Ÿ ����ü.
		switch(type)
		{
			case ITEMTYPE_AVATAR_MANTLE:
			case ITEMTYPE_AVATAR_DRESS:
			case ITEMTYPE_AVATAR_HAT:
			case ITEMTYPE_AVATAR_NECK:
			case ITEMTYPE_AVATAR_RING:
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_AVATAR_STATE_WIS);
				break;
			default : 
				* CrystalPer = GetAllCrystalAbilityNum(CRYSTALABILITY_STATE_WIS);
				break;
		}		
		
	}
	
	return temNum;
}


// �ּ� �������� ���Ѵ�. 
SI32 cltItem::GetMinDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer )
{
	if(siUnique == 0)				return 0;
	
	SI32 type = GetType(pclItemManager);


	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		temNum += clItemWeapon.uiMinDamage;
		break;
	default:
		break;
	}

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK); //���� �ּ� ���ݷ�.
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK); //���� ���ݷ�.
	}

	return temNum;
}


// �ּ� �������� ���Ѵ�. 
SI32 cltItem::GetEnchantDamage(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;
	if( Element.siType % 2 ==0) return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{

	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_TORPEDO:
	case ITEMTYPE_RING:
		return Element.siPower;
		break;
	default:
		return 0;
	}
}


// �ּ� ��æƮ Ÿ���� ���Ѵ�. 
SI32 cltItem::GetEnchantType(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;
//	if(Element.siType % 2 ==0) return 0;

	SI32 type = GetType(pclItemManager);



	switch(type)
	{

	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_TORPEDO:
	//case ITEMTYPE_RING:
	case ITEMTYPE_HELMET:
	//case ITEMTYPE_HAT:		
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
	//case ITEMTYPE_DRESS:
	case ITEMTYPE_SHOES:
	
		return Element.siType;
		break;
	default:
		return 0;
	}
}


// �ִ� �������� ���Ѵ�. 
SI32 cltItem::GetMaxDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		temNum += clItemWeapon.uiMaxDamage;
		break;
	default:
		break;
	}

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK); //���� �ִ� ���ݷ�.
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK); //���� ���ݷ�.
	}

	return temNum;
}

SI32 cltItem::GetAddMagicalDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

// �⺻������ ���� ���㸦 �÷��ִ� ���� ������ ����.
/*
	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
	case ITEMTYPE_RING:
		temNum += clItemWeapon.uiMaxDamage;
		break;
	default:
		break;
	}
*/
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_ATTACK); //���� ���ݷ�
	}
	
	return temNum;
}

SI32 cltItem::GetAddMagicalMinDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �⺻������ ���� ���㸦 �÷��ִ� ���� ������ ����.

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK); // ���� �ּ� ���ݷ�.
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_ATTACK); //���� ���ݷ�
	}
	
	return temNum;
}

SI32 cltItem::GetAddMagicalMaxDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �⺻������ ���� ���㸦 �÷��ִ� ���� ������ ����.

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK);// ����  �ִ� ���ݷ�
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_ATTACK); //���� ���ݷ�
	}
	
	return temNum;
}

// �ʻ�  - ũ��Ƽ���� ���.
SI32 cltItem::GetCriticalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �⺻������ ���� ���㸦 �÷��ִ� ���� ������ ����.

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_SPECIAL_DEATHBLOW);// ũ��Ƽ�� Ȯ�� ���.
	}
	
	return temNum;
}

SI32 cltItem::GetPhysicalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// �⺻������ ���� ���㸦 �÷��ִ� ���� ������ ����.

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE);// ���� ���߷�.
	}
	
	return temNum;
}

SI32 cltItem::GetMagicalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_HITRATE);// ���� ���߷�.
	}
	
	return temNum;
}

// ��� �ɷ��� ���Ѵ�. 
SI32 cltItem::GetPhysicalAC(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	switch(type)
	{
		case ITEMTYPE_HELMET:
		case ITEMTYPE_BELT:
		case ITEMTYPE_ARMOUR:
			temNum += clItemArmour.uiAC;
			break;

		case ITEMTYPE_BAG:	
			temNum += clItemBag.uiAC;
			break;

		case ITEMTYPE_MANTLE:	
			temNum += clItemMantle.uiAC;
			break;

		case ITEMTYPE_AVATAR_MANTLE:
			temNum += clItemAvatarMantle.uiAC; 
			break;

		case ITEMTYPE_AVATAR_RING:
			temNum += clItemAvatarRing.uiAC; 
			break;

		case ITEMTYPE_SHOES:
			temNum += clItemShoes.uiAC;
			break;
		default:
			break;
	}
	
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE); //���� ����.
	}

	return temNum;	
}

// ��� �ɷ��� ���Ѵ�. 
SI32 cltItem::GetMagicalAC(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;
// ���� ������ ������ �ִ� ���� ����.
/*
	switch(type)
	{
		case ITEMTYPE_HELMET:
		case ITEMTYPE_BELT:
		case ITEMTYPE_ARMOUR:
			temNum += clItemArmour.uiAC;
			break;

		case ITEMTYPE_BAG:	
			temNum += clItemBag.uiAC;
			break;

		case ITEMTYPE_MANTLE:	
			temNum += clItemMantle.uiAC;
			break;

		case ITEMTYPE_SHOES:
			temNum += clItemShoes.uiAC;
			break;
		default:
			break;
	}
*/
	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);
		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE); //���� ����.
	}

	return temNum;	
}

SI32 cltItem::GetPhysicalDodgeRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;


	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE);// ���� ȸ����
	}
	
	return temNum;
}

SI32 cltItem::GetMagicalDodgeRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//SI32 type = GetType(pclItemManager);

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;


	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE);// ����ȸ����
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalHitpoint(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_HITPOINT);// ü��.
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalManapoint(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_MANAPOINT);// ������..
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalWeigt(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_EFFECT_WEIGHT);// ���Է�.
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalFireAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_FIREATTACK);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalWaterAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_WATERATTACK);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalWindAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_WINDATTACK);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalEarthAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_EARTHATTACK);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalFireDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		*CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalWaterDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalWindDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE);
	}
	
	return temNum;
}

SI32 cltItem::GetCrystalEarthDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer)
{
	if(siUnique == 0)return 0;

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	if(siUseCrystalNum>0)
	{
		//UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		* CrystalPer += GetAllCrystalAbilityNum(CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE);
	}
	
	return temNum;
}

// �ּ� �������� �����Ѵ�. 
SI32 cltItem::SetMinDamage(cltItemManagerCommon* pclItemManager, SI32 damage)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
	case ITEMTYPE_RING:

		clItemWeapon.uiMinDamage = damage;
		return clItemWeapon.uiMinDamage;
		break;
	default:
		MsgBox(TEXT("SetMinDamage()"), TEXT("unique:%d type:%d"), siUnique, type); 
		{
			SI32 a = 0;
		}
		return 0;
	}
}

// �ִ� �������� �����Ѵ�. 
SI32 cltItem::SetMaxDamage(cltItemManagerCommon* pclItemManager, SI32 damage)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
	case ITEMTYPE_RING:
		clItemWeapon.uiMaxDamage = damage;
		return clItemWeapon.uiMaxDamage;
		break;

	default:
		MsgBox(TEXT("SetMaxDamage()"), TEXT("unique:%d type:%d"), siUnique, type);
		{
			SI32 a = 0;
		}

		return 0;
	}
}


// ��� �ɷ��� ���Ѵ�. 
SI32 cltItem::GetAC(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_HELMET:
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
		return clItemArmour.uiAC;
		break;

	case ITEMTYPE_HAT:		
	case ITEMTYPE_DRESS:
		return clItemArmour.uiAC;
		break;

	case ITEMTYPE_BAG:	
		return clItemBag.uiAC;
		break;

	case ITEMTYPE_MANTLE:	
		return clItemMantle.uiAC;
		break;

	case ITEMTYPE_AVATAR_MANTLE:
		return clItemAvatarMantle.uiAC;
		break;

	case ITEMTYPE_AVATAR_RING:
		return clItemAvatarRing.uiAC;
		break;

	case ITEMTYPE_SHOES:
		return clItemShoes.uiAC;
		break;


	default:
		MsgBox(TEXT("GetAC()"), TEXT("unique:%d type:%d"), siUnique, type);
		{
			SI32 a = 0;
		}

		return 0;
	}
}


// ��� �ɷ��� ���Ѵ�. 
SI32 cltItem::GetEnchantAC(cltItemManagerCommon* pclItemManager,bool bClient)const
{
	if(siUnique == 0)return 0;
	if(Element.siType % 2 ==1 ) return 0;

	SI32 type = GetType(pclItemManager);


	switch(type)
	{
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:		
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_MANTLE:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_RING:

		{
			return Element.siPower ;

		}
		break;	
	default:
		{
			if ( bClient )
				MsgBox("GetEnchantAC()", "unique:%d type:%d", siUnique, type);

			return 0;
		}
		break;
	}
}

// ��æƮ���� ���ɷ��� ���Ѵ�. 
SI32 cltItem::GetEnchantACFrom(cltItemManagerCommon* pclItemManager,bool bClient, SI32 attacktype)const
{
	if(siUnique == 0)return 0;
	if(attacktype ==0)return 0;
	if(attacktype % 2 ==1) return 0; //Ȧ���� ���ݴɷ��̴�.
	if(attacktype != Element.siType) return 0;

	SI32 type = GetType(pclItemManager);
	SI32 siEnchantDef =0;	

	switch(Element.siPower)
	{
	case 0:
		siEnchantDef = 0;
		break;
	case 1:
		siEnchantDef = 5;
		break;
	case 2:
		siEnchantDef = 6;
		break;
	case 3:
		siEnchantDef = 8;
		break;
	case 4:
		siEnchantDef = 11;
		break;
	case 5:
		siEnchantDef = 15;
		break;
	case 6:
		siEnchantDef = 20;
		break;
	case 7:
		siEnchantDef = 26;
		break; 
	case 8:
		siEnchantDef = 33;
		break; 
	case 9:
		siEnchantDef = 41;
		break; 
	case 10:
		siEnchantDef = 50;
		break; 
	default:
		siEnchantDef = 0;
		break;		
	}



	switch(type)
	{
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:		
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_MANTLE:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_RING:
	case ITEMTYPE_AVATAR_MANTLE:	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_DRESS:		// �ƹ�Ÿ �Ǻ�
	case ITEMTYPE_AVATAR_HAT:		// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_RING:		// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_NECK:		// �ƹ�Ÿ �����
		
		{
			return siEnchantDef ;			
		}
		break;	
	default:
		{
			if ( bClient )
				MsgBox("GetEnchantAC()", "unique:%d type:%d", siUnique, type);

			return 0;
		}
		break;
	}
}

// ��æƮ���� ���ݴɷ��� ���Ѵ�. 
SI32 cltItem::GetEnchantAttFrom(cltItemManagerCommon* pclItemManager,bool bClient, SI32 attacktype)const
{
	if(siUnique == 0)return 0;
	if(attacktype ==0)return 0;
	if(attacktype % 2 ==0) return 0; // ¦���� ���ɷ��̴�.
	if(attacktype != Element.siType) return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD	:
	case ITEMTYPE_SPEAR	:
	case ITEMTYPE_STAFF	:
	case ITEMTYPE_AXE	:
	case ITEMTYPE_BOW	:
	case ITEMTYPE_GUN	:
	case ITEMTYPE_CANNON	:
	case ITEMTYPE_RING:
		{
			return Element.siPower ;

		}
		break;	
	default:
		{
			if ( bClient )
				MsgBox("GetEnchantAC()", "unique:%d type:%d", siUnique, type);

			return 0;
		}
		break;
	}
}


// ��� �ɷ��� �����Ѵ�. 
SI32 cltItem::SetAC(cltItemManagerCommon* pclItemManager, SI32 ac)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_HELMET:
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
		clItemArmour.uiAC = ac;
		return clItemArmour.uiAC;
		break;

	case ITEMTYPE_HAT:		
	case ITEMTYPE_DRESS:
	//	clItemStatusArmour.uiAC = ac;
	//	return clItemStatusArmour.uiAC;
		return 0;
		break;

	case ITEMTYPE_BAG:	
		clItemBag.uiAC = ac;
		return clItemBag.uiAC;
		break;

	case ITEMTYPE_MANTLE:	
		clItemMantle.uiAC	= ac;
		return clItemMantle.uiAC;
		break;

	case ITEMTYPE_AVATAR_MANTLE:
		clItemAvatarMantle.uiAC	= ac;
		return clItemAvatarMantle.uiAC;
		break;

	case ITEMTYPE_SHOES:
		clItemShoes.uiAC	= ac;
		return clItemShoes.uiAC;
		break;

	default:
		MsgBox(TEXT("SetAC()"), TEXT("unique:%d type:%d"), siUnique, type);
		{
			SI32 a = 0;
		}

		return 0;
	}
}


// Ư�� ����� ������ ���� ��� ȿ���� ���Ѵ�. 
SI32 cltItem::GetSkillScrollUp(cltItemManagerCommon* pclItemManager, SI32 skillunique)
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)return 0;

	SI32 index = 0;

	while( skilldata[index*3] )
	{
		if(skillunique == skilldata[index*3])
		{
			UI32 para = 0 ;
			if( clItemCommon.clOptionInfo.uiType1 == (UI32)skilldata[index*3 + 1] ||
				clItemCommon.clOptionInfo.uiType1 == (UI32)skilldata[index*3 + 2])
			{
				//return clItemCommon.clOptionInfo.uiPara1 / 10;
				para += clItemCommon.clOptionInfo.uiPara1 / 10 ;
			}

			if(clItemCommon.clOptionInfo.uiType2 == (UI32)skilldata[index*3 + 1] ||
				clItemCommon.clOptionInfo.uiType2 == (UI32)skilldata[index*3 + 2])
			{
				//return clItemCommon.clOptionInfo.uiPara2 / 10;
				para += clItemCommon.clOptionInfo.uiPara2 / 10 ;
			}

			if ( para > 0 )
			{
				return para ;
			}
		}

		index++;
	}

	return 0;

}


// ����� ����� ���Ѵ�. 
SI32 cltItem::GetUpgradeSkillLevel(cltItemManagerCommon* pclItemManager, SI32 skillunique  , bool countCrystalAbilityNum)
{
	if(siUnique == 0)return 0;
	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI32 temNum = 0;

	//---------------------------------------------------------
	// ���� ������ ���� ȿ���� ���Ѵ�. - ������ ���� ȿ�� ����. 
	//---------------------------------------------------------
	temNum += GetSkillScrollUp(pclItemManager, skillunique);
	//if(up)return up;

	//--------------------------------------------
	// ������ ��������� ���Ѵ�. 
	//--------------------------------------------
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)return 0;

	// ������ �˻��Ͽ� ����ü�� �ɷ��� �����ش�.
	// ������ �ְ�, ���Կ� ���� ����� �ؾ� �� ��츸. - ��ü ��ų�� ��� �Ҷ��� ����ü�� ���� ���� ��� �ؾ߸� �Ѵ�.
	if((siUseCrystalNum>0) && (countCrystalAbilityNum == true))
	{
		UI08 uiSkillunique = GetCrystalAbilityFromSkillUnique(skillunique);

		temNum += GetAllCrystalAbilityNum(uiSkillunique);
	}


	SI32 type = GetType(pclItemManager);
	// �ƹ�Ÿ ���������� �˻��Ѵ�.
	SI32 siAvatarItem = GetAavatarType(pclItemManager);


	// �ƹ�Ÿ ������������ ���� ã�´�.
	if(siAvatarItem >0) 
	{
		switch(type)
		{
		case ITEMTYPE_AVATAR_NECK:
			{
				if(skillunique == (SI32)clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					temNum += clItemAvatarNeck.uiSkillValue;
				}
				else if(ALL_MAKESKILL_UNIQUE == clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					if( ( skillunique >= SKILL_MAKEARMOUR1 && skillunique <= SKILL_MAKEDRESS1 ) ||skillunique == SKILL_MAKEHAT1 )
						temNum += clItemAvatarNeck.uiSkillValue;			
				}
				else if(ALL_WEAPONSKILL_UNIQUE == clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					if ( skillunique >= SKILL_USESWORD1 && skillunique <= SKILL_USESTAFF1 )
						temNum += clItemAvatarNeck.uiSkillValue;			
				}
				else if(ALL_PRODUCTSKILL_UNIQUE == clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					if( skillunique == SKILL_HORSETRAINING || skillunique == SKILL_FARM ||
						skillunique == SKILL_MINE		 || skillunique == SKILL_FISH ||
						skillunique == SKILL_MAKEIRON1	 || skillunique == SKILL_MAKETOOL1 ||
						skillunique == SKILL_MAKEFOOD || skillunique == SKILL_MAKEMED ||
						skillunique == SKILL_ARTIFACT)
						temNum += clItemAvatarNeck.uiSkillValue;			
				}
				else if(ALL_ALLSKILL_UNIQUE == clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					if( (skillunique >= SKILL_MAKEMED && skillunique < SKILL_SWORD_INCDR)|| 
					      skillunique == SKILL_MAKETOOL1 ||skillunique == SKILL_ARTIFACT  ||
					      (skillunique >= SKILL_MAKEAVATAR_DRESS && skillunique <= SKILL_MAKEAVATAR_NECK))
						temNum += clItemAvatarNeck.uiSkillValue;			
				}
				else if(ALL_ALLAVATARSKILL_UNIQUE == clItemAvatarNeck.uiUpgradeSkillUnique)
				{
					if( skillunique >= SKILL_MAKEAVATAR_DRESS && skillunique <= SKILL_MAKEAVATAR_NECK)
						temNum += clItemAvatarNeck.uiSkillValue;			
				}
			}
			break;
		// �����ϰ�, �Ǻ� �߰� �ɶ��� �Լ��� ������.  - ������ ������.
		/*
		case ITEMTYPE_AVATAR_HAT:		
			{
				if(skillunique == pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique)
					temNum += clItemAvatarHat.uiSkillUp;
			}
		case ITEMTYPE_AVATAR_DRESS:
			{
				if(skillunique == pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique)
					temNum += clItemAvatarDress.uiSkillUp;
			}
			break;
		*/
		}

		return temNum;		
	}
	else if((skillunique == pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique) && (siAvatarItem <= 0))
	{
		switch(type)
		{
		case ITEMTYPE_HELMET:
		case ITEMTYPE_BELT:
		case ITEMTYPE_ARMOUR:
			temNum += clItemArmour.uiSkillUp;
			break;
		case ITEMTYPE_HAT:		
		case ITEMTYPE_DRESS:
			temNum += clItemStatusArmour.uiSkillUp;
			break;
		case ITEMTYPE_NECK:
			temNum += clItemNeck.uiSkillPointUp;
			break;		
		}

		return temNum;
	}
	// �������� ���� �ٸ� �Ͱ� ���� ȿ��
	else if ((pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique == ALL_MAKESKILL_UNIQUE) && (siAvatarItem <= 0) )
	{
		if( ( skillunique >= SKILL_MAKEARMOUR1 && skillunique <= SKILL_MAKEDRESS1 ) ||
			/*skillunique == SKILL_MAKENECK1 ||*/ skillunique == SKILL_MAKEHAT1 )
		{
			switch(type)
			{
			case ITEMTYPE_HAT:
			case ITEMTYPE_DRESS:
				{
					temNum +=  clItemStatusArmour.uiSkillUp;
				}
				break;
			case ITEMTYPE_NECK:
				temNum +=  clItemNeck.uiSkillPointUp;
				break;
			}

			return temNum;			
		}
	}
	// ����������� ���� �ٸ� �Ͱ� ���� ȿ��
	else if ((pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique == ALL_WEAPONSKILL_UNIQUE) && (siAvatarItem <= 0) )
	{
		if ( skillunique >= SKILL_USESWORD1 && skillunique <= SKILL_USESTAFF1 )
		{
			switch(type)
			{	
			case ITEMTYPE_HAT:
			case ITEMTYPE_DRESS:
				{
					temNum += clItemStatusArmour.uiSkillUp;
				}
				break;
			case ITEMTYPE_NECK:
				temNum += clItemNeck.uiSkillPointUp;
				break;
			}
		}

		return temNum;
	}
	// ���������� ���� �ٸ� �Ͱ� ���� ȿ��
	else if ( (pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique == ALL_PRODUCTSKILL_UNIQUE) && (siAvatarItem <= 0) )
	{
		if( skillunique == SKILL_HORSETRAINING || skillunique == SKILL_FARM ||
			skillunique == SKILL_MINE		 || skillunique == SKILL_FISH ||
			skillunique == SKILL_MAKEIRON1	 || skillunique == SKILL_MAKETOOL1 ||
			skillunique == SKILL_MAKEFOOD || skillunique == SKILL_MAKEMED ||
			skillunique == SKILL_ARTIFACT)
		{
			switch(type)
			{
			case ITEMTYPE_HAT:
			case ITEMTYPE_DRESS:
				{
					temNum += clItemStatusArmour.uiSkillUp;
				}
				break;
			case ITEMTYPE_NECK:
				temNum += clItemNeck.uiSkillPointUp;
				break;
			}
		}

		return temNum;

	}
	// ��罺ų
	else if ((pclItemManager->pclItemInfo[ref]->siUpgradeSkillUnique == ALL_ALLSKILL_UNIQUE) && (siAvatarItem <= 0) )
	{
		// ���������� �������� �������� ��� ��ų
		if( (skillunique >= SKILL_MAKEMED && skillunique < SKILL_SWORD_INCDR)|| 
		      skillunique == SKILL_MAKETOOL1 ||skillunique == SKILL_ARTIFACT ||
		      (skillunique >= SKILL_MAKEAVATAR_DRESS && skillunique <= SKILL_MAKEAVATAR_NECK))
		{
			switch(type)
			{
			case ITEMTYPE_HAT:
			case ITEMTYPE_DRESS:
				{
					temNum += clItemStatusArmour.uiSkillUp;
				}
				break;
			case ITEMTYPE_NECK:
				temNum += clItemNeck.uiSkillPointUp;
				break;
			}
		}

		return temNum;

	}

	if(temNum >0 )
		return temNum;
	else
		return 0;
}

// ���� ���Ѵ�. 
SI32 cltItem::GetLuck(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_HELMET:
	case ITEMTYPE_BELT:
	case ITEMTYPE_ARMOUR:
	//case ITEMTYPE_HAT:
	//case ITEMTYPE_DRESS:
		return clItemArmour.uiLuck;
		break;
	default:
		return 0;
	}

//	return 0;
}


//----------------------------------------
// �̵��ӵ� ���� 
//----------------------------------------
SI32 cltItem::GetMoveSpeed(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SHOES:
		return clItemShoes.uiMoveSpeed;
		break;
	default:
		MsgBox(TEXT("fdsmv8jfd"), TEXT("fmcvijsd:%d"), type);
		break;
	}

	return 0;
}

//----------------------------------------
// ������ ����. 
//----------------------------------------
//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü ������ ����.

// �������� ���δ�. 
bool cltItem::DecreaseCrystalDurability(cltItemManagerCommon* pclItemManager, SI16 durvary)
{
	// �������� ���ҵǴ� ���������� Ȯ���Ѵ�. 
	bool reVal = false;

	// �ϴ� ������ �־�� �Ѵ�.
	if(GetUseCrystalNum() >0)
	{
		// �ش� �������� ��� ����ü �������� ���ҽ�Ų��.
		for(int i = 0; i <MAX_CRYSTAL_NUM ; i++ )
		{		
			if(cltItemCrytal[i].GetCrystalType() != 0)
			{
				// �ִ� �������� 0�̸� - �ش� ����ü ������ ����. - �ı�. 
				if(cltItemCrytal[i].GetDurability() <= 0)
				{
					cltItemCrytal[i].Init();
					reVal = true;
				}
				else if(cltItemCrytal[i].GetDurability() > 0)
				{
					SI16 randval = rand()%100;

					if(randval < CRYSTAL_DECREASE_DURABILITY_PRO) //  Ȯ���� ����.
					{
						cltItemCrytal[i].DecDurability(durvary);				
					}
					reVal = true;
				}
			}
		}
	}
	return reVal;
}

// ũ����Ż�� �������� 1%������ �پ�, Client�� ������ �ϴ��� ���θ� �����Ѵ�. - ��� ���Ѵ�.
bool cltItem::GetDecreaseCrystalDurabilityPer(cltItemManagerCommon* pclItemManager)
{
	// �������� ���ҵǴ� ���������� Ȯ���Ѵ�. 
	bool reVal = false;

	// �ϴ� ������ �־�� �Ѵ�.
	if(GetUseCrystalNum() >0)
	{
		return true; // �� �� ������.
	
		/*
		// �ش� �������� ��� ����ü �������� ���ҽ�Ų��.
		for(int i = 0; i <MAX_CRYSTAL_NUM ; i++ )
		{		
			if(cltItemCrytal[i].GetCrystalType() != 0)
			{
				SI16 canDurPer = cltItemCrytal[i].GetDurability()%300; // 300 = 1% �̴�.
				SI16 nowDurPer = (cltItemCrytal[i].GetDurability()*100)/30000; // ���� ������ %.
								
				if(nowDurPer == 100)
				{
					return false; // 100% �϶��� ������ �ʴ´�.
				}
				else if((cltItemCrytal[i].GetDurability() > 29989) && (cltItemCrytal[i].GetDurability() < 30000))
				{
					return true; // 99% �� ���ϴ� �͸� ���ܷ� ó���Ѵ�. - 1���� ������ �Ϸ���.(��ġ�� 5�п� �ѹ��÷� ���´�)				
				}
				else if(canDurPer == 0) // 1% ������ �ٲ���ٸ�.				
				{
					return true; // �ϳ��� ���ߴٸ�, ������ �ش� �������� ��ü ������ �������Ѵ�.
				}
				
			}
		}
		*/
	}
	return reVal;
}
//------------------------------------------------------------------------------


REAL32 cltItem::GetDurabilityPenlty( cltItemManagerCommon* pclItemManager )
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return 0.0f;;
#else
	SI32 siForeverDurability	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	SI32 siGetMaxDurability		= GetMaxDurability();
	if( (siGetMaxDurability == siForeverDurability) || (siGetMaxDurability == siForeverDurability2) )
	{
		return 1.0f;
	}

	if ( NULL == pclItemManager )
	{
		return 0.0f;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if ( 0 >= ref )
	{
		return 0.0f;
	}

	if ( 0 < siGetMaxDurability )
	{
		REAL32 fResourceDurability	= (REAL32)pclItemManager->pclItemInfo[ref]->clItem.GetMaxDurability( pclItemManager );
		REAL32 fMaxDurability		= (REAL32)GetMaxDurability();

		return min( 1.0f, (fMaxDurability/fResourceDurability) );
	}

	return 0.0f;
#endif
}

// �������� �����Ѵ�. 
SI32 cltItem::SetDurability(cltItemManagerCommon* pclItemManager, UI32 dur)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:

		clItemWeapon.clCommonInfo.uiDurability = dur;
		return clItemWeapon.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_BELT:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_ARMOUR:
		clItemArmour.clCommonInfo.uiDurability		= dur;
		return clItemArmour.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_HAT:
	case ITEMTYPE_DRESS:
		clItemStatusArmour.clCommonInfo.uiDurability		= dur;
		return clItemStatusArmour.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_BAG:
		clItemBag.clCommonInfo.uiDurability		= dur;
		return clItemBag.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_MANTLE:
		clItemMantle.clCommonInfo.uiDurability		= dur;
		return clItemMantle.clCommonInfo.uiDurability;
		break;

	// �������� �����Ѵ�
	case ITEMTYPE_AVATAR_MANTLE:
		clItemAvatarMantle.clCommonInfo.uiDurability	= dur;
		return clItemMantle.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_AVATAR_NECK:
		clItemAvatarNeck.clCommonInfo.uiDurability	= dur;
		return clItemAvatarNeck.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_AVATAR_DRESS:
		clItemAvatarDress.clCommonInfo.uiDurability	= dur;
		return clItemAvatarDress.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_AVATAR_HAT:
		clItemAvatarHat.clCommonInfo.uiDurability	= dur;
		return clItemAvatarHat.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_AVATAR_RING:
		clItemAvatarRing.clCommonInfo.uiDurability	= dur;
		return clItemAvatarRing.clCommonInfo.uiDurability;
		break; 



	case ITEMTYPE_SHOES:
		clItemShoes.clCommonInfo.uiDurability		= dur;
		return clItemShoes.clCommonInfo.uiDurability;
		break;
	case ITEMTYPE_RING:
		clItemRing.clCommonInfo.uiDurability		= dur;
		return clItemRing.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_NECK:
		clItemNeck.clCommonInfo.uiDurability		= dur;
		return clItemNeck.clCommonInfo.uiDurability;
		break;

	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
		clItemTool.clCommonInfo.uiDurability		= dur;
		return clItemTool.clCommonInfo.uiDurability;
		break;
	}

	clItemCommon.clCommonInfo.uiMaxDurability = dur;
	return clItemCommon.clCommonInfo.uiMaxDurability;

}


// �ִ� �������� ���Ѵ�. 
SI32 cltItem::GetMaxDurability(cltItemManagerCommon* pclItemManager)const
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		return clItemWeapon.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_BELT:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_ARMOUR:
		return clItemArmour.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_HAT:
	case ITEMTYPE_DRESS:
		return clItemStatusArmour.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_BAG:
		return clItemBag.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_MANTLE:
		return clItemMantle.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_MANTLE:
		return clItemAvatarMantle.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_NECK:
		return clItemAvatarNeck.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_DRESS:
		return clItemAvatarDress.clCommonInfo.uiMaxDurability;
		break;


	case ITEMTYPE_AVATAR_HAT:
		return clItemAvatarHat.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_RING:
		return clItemAvatarRing.clCommonInfo.uiMaxDurability;
		break;
		

	case ITEMTYPE_SHOES:
		return clItemShoes.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_RING:
		return clItemRing.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_NECK:
		return clItemNeck.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
		return clItemTool.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_CRYSTAL:
		return clItemCrystal.clCommonInfo.uiMaxDurability;
		break;
	}

	return clItemCommon.clCommonInfo.uiMaxDurability;
}

// �ִ볻������ �����Ѵ�. 
SI32 cltItem::SetMaxDurability(cltItemManagerCommon* pclItemManager, UI32 dur)
{
	if(siUnique == 0)return 0;

	SI32 type = GetType(pclItemManager);

	switch(type)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
		clItemWeapon.clCommonInfo.uiMaxDurability = dur;
		return clItemWeapon.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_BELT:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_ARMOUR:
		clItemArmour.clCommonInfo.uiMaxDurability		= dur;
		return clItemArmour.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_HAT:
	case ITEMTYPE_DRESS:
		clItemStatusArmour.clCommonInfo.uiMaxDurability		= dur;
		return clItemStatusArmour.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_BAG:
		clItemBag.clCommonInfo.uiMaxDurability		= dur;
		return clItemBag.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_MANTLE:
		clItemMantle.clCommonInfo.uiMaxDurability		= dur;
		return clItemMantle.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_MANTLE:
		clItemAvatarMantle.clCommonInfo.uiMaxDurability	= dur;
		return clItemAvatarMantle.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_NECK:
		clItemAvatarNeck.clCommonInfo.uiMaxDurability	= dur;
		return clItemAvatarNeck.clCommonInfo.uiMaxDurability;
		break;


	case ITEMTYPE_AVATAR_DRESS:
		clItemAvatarDress.clCommonInfo.uiMaxDurability	= dur;
		return clItemAvatarDress.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_HAT:
		clItemAvatarHat.clCommonInfo.uiMaxDurability	= dur;
		return clItemAvatarHat.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_AVATAR_RING:
		clItemAvatarRing.clCommonInfo.uiMaxDurability	= dur;
		return clItemAvatarRing.clCommonInfo.uiMaxDurability;
		break;

	case ITEMTYPE_SHOES:
		clItemShoes.clCommonInfo.uiMaxDurability		= dur;
		return clItemShoes.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_RING:
		clItemRing.clCommonInfo.uiMaxDurability		= dur;
		return clItemRing.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_NECK:
		clItemNeck.clCommonInfo.uiMaxDurability		= dur;
		return clItemNeck.clCommonInfo.uiMaxDurability;
		break;
	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
		clItemTool.clCommonInfo.uiMaxDurability		= dur;
		return clItemTool.clCommonInfo.uiMaxDurability;
		break;
	}

	clItemCommon.clCommonInfo.uiMaxDurability = dur;
	return clItemCommon.clCommonInfo.uiMaxDurability;

}

// �������� ���δ�. 
bool cltItem::DecreaseDurability(cltItemManagerCommon* pclItemManager, SI32 durvary)
{
#ifndef _DBMANAGER

	SI32 type = GetType(pclItemManager);
	if( type <= 0 ) 														return false;

	SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;
	if( (atb & ITEMATB_OBJECT) == 0)										return false;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)															return false;

	SI32 siForeverDurability  = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2 = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	SI32 maxdur = GetMaxDurability();
	if( maxdur == siForeverDurability || maxdur == siForeverDurability2 )	return false;

#ifdef _DEBUG
	SI32 siBefore = GetDurability();
#endif //_DEBUG

	SI32 dur = GetDurability();
	dur -= durvary;
	if( dur < 0 )	dur = 0;

	SetDurability(pclItemManager, dur);

#ifdef _DEBUG
	SI32 siLater = GetDurability();
#endif //_DEBUG

#ifdef _DEBUG
	NTCHARString64 kMsg;
	kMsg += "DecreaseDurability ";
	kMsg += "Unique[";
	kMsg += SI16ToString( siUnique );
	kMsg += "] Before [";
	kMsg += SI32ToString( siBefore );
	kMsg += "] Later [";
	kMsg += SI32ToString( siLater );
	kMsg += "]\n";
	OutputDebugString( kMsg );
#endif //_DEBUG

#endif //_DBMANAGER
	return true;
}




// �������� �� ������ ����� �޾Ҵ��� Ȯ���Ѵ�.
BOOL cltItem::CheckType(cltItemManagerCommon* pclItemManager, SI32 orgtype)
{
	SI32 type = GetType(pclItemManager);

	if(type != orgtype)
	{
		MsgBox(TEXT("cltItem0"), TEXT("unique:%d type:%d"), siUnique, type);
		return FALSE;
	}

	return TRUE;
}

SI32 cltItem::GetImage(cltItemManagerCommon* pclItemManager)
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->siImageIndex;
	}

	return 0;
}

const TCHAR* cltItem::GetShortName(cltItemManagerCommon* pclItemManager)
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetName();
	}

	return NULL;
}

bool cltItem::GetFullName(cltItemManagerCommon* pclItemManager, TCHAR* pname, SI16 txtSize)
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		StringCchCopy(pname, txtSize, pclItemManager->pclItemInfo[ref]->GetName());

		if(clItemCommon.clCommonInfo.uiRareInfo)
		{
			switch(clItemCommon.clCommonInfo.uiRareInfo)
			{
			case  RARELEVEL_1:		// ��ǰ
				{
					TCHAR* pText = GetTxtFromMgr(714);
					StringCchCat(pname, txtSize, pText);
				}break;
			case  RARELEVEL_2:		// ȣǰ
				{
					TCHAR* pText = GetTxtFromMgr(715);
					StringCchCat(pname, txtSize, pText);
				}break;
			case  RARELEVEL_5:		// ���ǰ - by LEEKH 2008-02-04
				{
					TCHAR* pText = GetTxtFromMgr(716);
					StringCchCat(pname, txtSize, pText);
				}break;
			case  RARELEVEL_6:		// ��ǰ
				{
					TCHAR* pText = GetTxtFromMgr(10200);
					StringCchCat(pname, txtSize, pText);
				}break;	
			default:
				{
					// �⺻ ó�� ����. - by LEEKH 2008-02-04
					//TCHAR* pText = GetTxtFromMgr(716);
					//StringCchCat(pname, txtSize, pText);	
				}break;
			}
		}
		return true;

	}

	return false;
}

// �������� �̸��� ������ ���´�. 
bool cltItem::GetFullNameNNum(cltItemManagerCommon* pclItemManager, TCHAR* pname, SI16 txtSize )
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		StringCchCopy(pname, txtSize, pclItemManager->pclItemInfo[ref]->GetName());

		if(clItemCommon.clCommonInfo.uiRareInfo)
		{
			switch(clItemCommon.clCommonInfo.uiRareInfo)
			{
			case  RARELEVEL_1:
				{
					TCHAR* pText = GetTxtFromMgr(714);
					StringCchCat(pname, txtSize, pText);
				}break;
			case  RARELEVEL_2:
				{
					TCHAR* pText = GetTxtFromMgr(715);
					StringCchCat(pname, txtSize, pText);
				}break;
			case  RARELEVEL_6:
				{
					TCHAR* pText = GetTxtFromMgr(10200);
					StringCchCat(pname, txtSize, pText);
				}break;
			default:
				{
					TCHAR* pText = GetTxtFromMgr(716);
					StringCchCat(pname, txtSize, pText);	
				}break;
			}
		}

		TCHAR temp[256];
		TCHAR* pText = GetTxtFromMgr(717);
		StringCchPrintf(temp, 256, pText, siItemNum);
		StringCchCat(pname, txtSize, temp);
		return true;

	}

	return false;
}



TCHAR* cltItem::GetArmCode(cltItemManagerCommon* pclItemManager)
{
	// ����ũ ���� �ٰŷ� �������� Ÿ���� ���Ѵ�. 
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		if(_tcscmp(pclItemManager->pclItemInfo[ref]->szArmCode, TEXT("")) == 0)
		{
			return NULL;
		}
		else
		{
			return pclItemManager->pclItemInfo[ref]->szArmCode;
		}
	}
	return NULL;
}

// �����ۿ��ٰ� �������� ���Ѵ�. 
bool cltItem::Add(cltItemManagerCommon* pclItemManager, cltItem* pclitem)
{
	if(siUnique == 0)
	{
		Set(pclitem);
		return true;
	}
	else 
	{
		if(siUnique != pclitem->siUnique)return false;
		if(siItemNum >= MAX_ITEM_PILE_NUMBER)return false;
		if(CanPile(pclItemManager) == false)return false;

		Increase(pclitem->siItemNum);
		return true;
	}

//	return false;
}

// �������� ���� ������ ���ϴ� �Լ�. 
// numcomp : �������� ���ƾ� �ϴ��� ����. 
BOOL cltItem::IsSame(cltItem* pclitem, bool numcomp)
{
	if( pclitem == NULL )		return FALSE;

	SI32 i = 0;

	if(pclitem->siUnique != siUnique)				return FALSE;
	if(numcomp)
	{
		if(pclitem->siItemNum != siItemNum)			return FALSE;
	}

	for(i = 0;i < MAX_ITEM_UNION_BYTE/4;i++)
	{
		if(pclitem->siData32[i] != siData32[i])		return FALSE;
	}

	//cyj ������ �񱳽� �Ⱓ�� üũ�ϵ��� �߰�
	// �Ⱓ�� üũ�Ѵ�.
	if ( uiDateYear != pclitem->uiDateYear )		return FALSE ;
	if ( uiDateMonth != pclitem->uiDateMonth )		return FALSE ;
	if ( uiDateDay != pclitem->uiDateDay )			return FALSE ;
	if ( uiDateUseDay != pclitem->uiDateUseDay )	return FALSE ;

	//[����] �Ӽ��� üũ�Ѵ�
	if ( Element.siType != pclitem->Element.siType )	return FALSE;
	if ( Element.siPower != pclitem->Element.siPower )  return FALSE;

	//[����] SID ��
	if( siSID != pclitem->siSID )						return FALSE;

	//[����] ũ����Ż ��
	if( siUseCrystalNum != pclitem->siUseCrystalNum )	return FALSE;
	for( i=0; i<MAX_CRYSTAL_NUM; i++ )
	{
		if( cltItemCrytal[i].IsSame( &pclitem->cltItemCrytal[i] ) == FALSE )		return FALSE;
	}

	return TRUE;
}

BOOL cltItem::IsBulletItem()//�Ѿ˾���������
//���� �Ѿ� ���� �����ϵ��� �߰� [����]
{
	if (siUnique == ITEMUNIQUE(7850) || siUnique == ITEMUNIQUE(7855) 
		|| siUnique == ITEMUNIQUE(13600) || siUnique == ITEMUNIQUE(13601)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

// �������� ���� ���δ�. 
SI32 cltItem::Increase(SI32 amount)
{

	if(siItemNum + amount > MAX_ITEM_PILE_NUMBER)
	{
		siItemNum  = MAX_ITEM_PILE_NUMBER;
	}
	else
	{
		siItemNum += amount;
	}

	return siItemNum;
}

// �������� ���� ���δ�. 
SI32 cltItem::Decrease(SI32 amount)
{
	if(siItemNum < amount)return siItemNum;

	siItemNum -= amount;

	if(siItemNum == 0)
	{
		Init();
	}
	if (amount == 0)return siItemNum;

	return siItemNum;
}

// ���Ը� ���Ѵ�.������ ���� ���Ե� �þ��.
SI32 cltItem::GetWeight(cltItemManagerCommon* pclItemManager, BOOL mode)
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		// ������ŭ ���Ը� Ȯ���Ѵ�.
		if(mode == TRUE)
		{
			return (pclItemManager->pclItemInfo[ref]->siWeight * siItemNum);
		}
		// �Ѱ��� ���Ը� ���´�.
		else
		{
			return pclItemManager->pclItemInfo[ref]->siWeight;
		}

	}
	else
		return 0;

}


//������Ű�� ��ų�� ����ũ
SI32 cltItem::GetSkillUnique(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetSkillUnique();
	}

	return 0;
}

//����� ���� ����. 
SI32 cltItem::GetSkillLevelLimit(cltItemManagerCommon* pclItemManager)const
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->GetSkillLevelLimit();
	}

	return 0;
}


// ��ø�� �Ǵ� ���������� Ȯ���Ѵ�. 
bool cltItem::CanPile(cltItemManagerCommon* pclItemManager)
{
	if(pclItemManager == NULL)		return false;

	// �Ⱓ�� �������� ��ĥ �� ����	- By LEEKH 2007.06.19
	if(IsHaveUseDay() == TRUE)				return false;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	SI32 type = GetType(pclItemManager);
	if(type)
	{
		// ��Ƽ��Ʈ �������� ������ - ����ü�� �ɷ��� ������ �ִ� ������
		if( type == ITEMTYPE_CRYSTAL )
		{
			if( clItemCrystal.uiCrystalAbility != 0 || clItemCrystal.uiCrystalAbilityNum != 0 )
				return false;
		}

		SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;

		// ITEMATB_OBJECT�� �ƴϸ� ��ø�� ����Ѵ�. 

		if((atb & ITEMATB_OBJECT) == 0)
		{
			return true;
		}
	}

	return false;
}

// ������ ������ ���������� Ȯ���Ѵ�.
bool cltItem::CanRepair(cltItemManagerCommon* pclItemManager)
{
	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	SI32 type = GetType(pclItemManager);
	if(type)
	{
		SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;

		if((atb & ITEMATB_REPAIR))
		{
			return true;
		}
	}

	return false;
}

// �� �������� ����µ� �ʿ��� ��ų�� �������� Ȯ���Ѵ�. 
SI32 cltItem::GetMakeSkill(cltItemManagerCommon* pclItemManager)
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
	}

	return 0;

}

// �� ������ �⺻ ���߷��� ���Ѵ�. 
SI32 cltItem::GetDefaultHitRate(cltItemManagerCommon* pclItemManager)
{
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref > 0)
	{
		return pclItemManager->pclItemInfo[ref]->siDefaultHitRate;
	}

	return 0;

}

// �������� �����Ѵ�. 
bool cltItem::Repair(cltItemManagerCommon* pclItemManager, SI32 reducedur)
{
	// ���� �Ұ����� �������̾ ����.
	if(CanRepair(pclItemManager) == false)return false;

	// �������� ���� ���� ���¿����� ���� �Ұ�. 
	SI32 curdur = GetDurability();
	SI32 maxdur	= GetMaxDurability(pclItemManager);

	if(curdur >= maxdur)return false;

	maxdur -= reducedur; // -> ��ų�� ���� ������ ���Ұ� �پ���. 
	if(maxdur <= 0)
	{
		// ���� �Ұ�. 
		return false;
	}

	SetMaxDurability(pclItemManager, maxdur);
	SetDurability(pclItemManager, maxdur);

	return true;

}

//=============================================================================
//  @Name   IsSealingUp()
//! @brief  �������� ���εǾ��ִ��� üũ�Ѵ�.
//=============================================================================
bool cltItem::IsSealingUp(cltItemManagerCommon* pclItemManager)
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return false;
#else
//================================================================
	SI32 type = GetType(pclItemManager);
	if(type)
	{
		SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;
		if( (atb & ITEMATB_OBJECT) == 0)return false;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)return false;

	if ( ref )
	{
		SI32 atb = pclItemManager->pclItemInfo[ref]->siItemInfoAtb ;

		if (pclClient->IsCountrySwitch(Switch_NotScailed))
		{	
			//30���� ���� �������� ���� �ȵǾ ����.[2007.07.23]
			SI32 slv = pclItemManager->pclItemInfo[ref]->clCondition.siLevel;
			SI32 eq = pclItemManager->pclItemInfo[ref]->clCondition.siStr;
			if (slv !=NULL && slv < 30 ) {
				return false;
			}
		}

		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
		// ����ü�� ���� �ȵǾ ����.
		if(type == ITEMTYPE_CRYSTAL)
			return false;
		
		//if( ITEMTYPE_BAG != pclItemManager->pclItemInfo[ref]->siType )
		//{
		//	if( (atb & ITEMINFOATB_ITEMMALL) != 0)
		//		return false;
		//}
	}

	if ( uiDateYear == 0 && uiDateMonth == 0 && uiDateDay == 0 )
	{
		return true ;
	}
	else return false ;

//================================================================
#endif
//================================================================
}

//=============================================================================
//  @Name   IsBelonging()
//! @brief  ������ �ͼ� ���θ� üũ�Ѵ�.
//=============================================================================
bool cltItem::IsBelonging(cltItemManagerCommon* pclItemManager)
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return false;
#else
//================================================================

	SI32 siGetItemType = GetType(pclItemManager);
	if ( siGetItemType )
	{
		SI64 siGetATB = pclItemManager->pclItemTypeInfo[siGetItemType]->siAtb;
		if ( (siGetATB & ITEMATB_OBJECT) == 0 )
		{
			return false;
		}
	}

	SI32 siGetRef = pclItemManager->FindItemRefFromUnique(siUnique);
	if ( siGetRef <= 0 )
	{
		return false;
	}

	// ������ ���� �ִ� ���������� ������ �ƴϸ� ������ �ͼ��� �ƴ�
	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		SI32 siForeverDurability	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
		SI32 siForeverDurability2	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

		SI32 siGetMaxDurability		= GetMaxDurability();
		if( (siGetMaxDurability != siForeverDurability) && (siGetMaxDurability != siForeverDurability2) )
		{
			return false;
		}
	}

/*	if ( ref )
	{
		SI32 atb = pclItemManager->pclItemInfo[ref]->siItemInfoAtb ;
        if( (atb & ITEMINFOATB_ITEMMALL) != 0){
			return false;
		}
	}
*/
	//cyj ��¥�� �־ �к� Ǯ�� �ͼ�~~!
	//if ( uiDateYear > 0 && uiDateMonth > 0 && uiDateDay > 0 && uiDateUseDay == 0 )
	if ( uiDateYear > 0 && uiDateMonth > 0 && uiDateDay > 0 )
	{

		return true ;
	}
	 
	return false ;
//================================================================
#endif
//================================================================
}

//=============================================================================
//  @Name   IsDisassemble()
//! @brief  ��ȣ�Ŀ��� ���� �����Ѱ�?
//=============================================================================
bool cltItem::IsDisassemble(cltItemManagerCommon* pclItemManager)
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return false;
#else
//================================================================
	
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)																				return false;

	//=============================================================================
	// ���� �ȵǴ� ����
	// tys[06/04/09] - 20 ���� �̻� ��ǰ�� ���� ���� - ���� �ɼ� ���
	SI32 equipLevel = pclItemManager->pclItemInfo[ref]->clCondition.siLevel;
	if ( equipLevel <= 20 && pclClient->IsCountrySwitch(Switch_WENNYDISASSEMBLELEVEL) )	return false;

	SI32 itemtype = pclItemManager->GetItemType(siUnique);
	if ( pclItemManager->IsItemInfoAtb(siUnique, ITEMINFOATB_ITEMMALL) )
	{
		if ( pclClient->IsCountrySwitch( Switch_ItemmallNotDisassemble) )
		{
			return false;
		}
	}
	else
	{
		if ( itemtype == ITEMTYPE_NECK )							
			return false;
		if ( itemtype == ITEMTYPE_MANTLE )													
			return false;
		if ( itemtype == ITEMTYPE_RING )													
			return false;
		if ( pclItemManager->IsItemInfoAtb(siUnique, ITEMINFOATB_NOTTRADE) )		
			return false;

		if (itemtype == ITEMTYPE_AVATAR_MANTLE)
			return false;
		if (itemtype == ITEMTYPE_AVATAR_DRESS)
			return false;
		if (itemtype == ITEMTYPE_AVATAR_HAT)
			return false;
		if (itemtype == ITEMTYPE_AVATAR_NECK)
			return false;
		if (itemtype == ITEMTYPE_AVATAR_RING)
			return false;
	}

	// �븸������ �ƹ�Ÿ��ǰ�� ��ȣ�� ���ص��� �ʵ��� �� (PCK - 2007.09.11)
	// [����] ��í �Ǻ��� ���ذ� �� (2008.06.20)
	if ( (pclItemManager->IsItemInfoAtb(siUnique, ITEMINFOATB_ITEMMALL) == true) && (false == pclClient->pclGachaManager->IsGachaRareItem( siUnique )) )
	{
		if(pclClient->IsCountrySwitch(Switch_WENNYDISASSEMBLEAvata))
		{
			if (itemtype == ITEMTYPE_DRESS)													return false;
			if (itemtype == ITEMTYPE_HAT)													return false;
			if (itemtype == ITEMTYPE_MANTLE)												return false;
		}
	}

	// ȭ����
	if(siUnique == ITEMUNIQUE(13600))														return false;
	// �Ű���
	if(siUnique == ITEMUNIQUE(13601))														return false;

	// [����] Ȳ�� ���ô� => 2008-8-12
	if(siUnique == ITEMUNIQUE(17160))														return false;
	
	cltServer* pclserver = (cltServer*)pclClient;
	if( false == pclClient->pclEventTimeManager->InEventTime(TEXT("Chuseok_Monster_Appear"), &pclserver->sTime) )
	{
		// [����] �߼� �̺�Ʈ. �����䳢 ����=> 2008-8-12
		if(siUnique == ITEMUNIQUE(23496))													return false;

		if(siUnique == ITEMUNIQUE(13047))													return false;
		if(siUnique == ITEMUNIQUE(13048))													return false;
		if(siUnique == ITEMUNIQUE(23114))													return false;
	}

	// ����ü ���� - ��а�.
	if ( itemtype == ITEMTYPE_CRYSTAL )							
		return false;

	// ��ƼȦ���� ���� �������� ���ص��� �ʴ´�.
	if ( clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )	return false;
	//=============================================================================

	//=============================================================================
	// ���� �Ǵ� ����

	SI32 type = GetType(pclItemManager);
	if( type )
	{
		SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;
		if( atb & ITEMATB_OBJECT )
		{
			SI32 slv = pclItemManager->pclItemInfo[ref]->clCondition.siLevel;
			if( pclClient->IsCountrySwitch(Switch_NotScailed) && (slv > 0 && slv < 30) )		return true;
		}
	}

	//----------------------------------------------------------------------------
	// �ͼӹ�ǰ�� ���� ����
	if( IsBelonging( pclItemManager )  == true )											return true;
	// ������ ��
	if( pclItemManager->IsItemInfoAtb(siUnique,ITEMINFOATB_ITEMMALL)  == true )
	{
		// �������� �ʴ� ���� ������ ���� ���� - ������ ��
		if( CanPile(pclClient->pclItemManager) == false )									return true;
		// ���� ������ ���� ����
	}
	//----------------------------------------------------------------------------

	if( pclClient->pclGachaManager->IsGachaRareItem( siUnique ) )						return true;
	//----------------------------------------------------------------------------
	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	switch(siUnique)
	{
		//KHY - 0220 - �߷�Ÿ�� ī�� ���ظ�� ����.
	case ITEMUNIQUE(13006): // Vī�� 
	case ITEMUNIQUE(13007): // Aī��.
	case ITEMUNIQUE(13008): // Lī��.
	case ITEMUNIQUE(13009): // N1ī��
	case ITEMUNIQUE(13010): // E1ī��
	case ITEMUNIQUE(13011): // Tī��
	case ITEMUNIQUE(13012): // Iī��.
	case ITEMUNIQUE(13013): // E2ī�� 
	case ITEMUNIQUE(13014): // N2ī��
		//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	case ITEMUNIQUE(13016): // Wī�� 
	case ITEMUNIQUE(13017): // Hī�� 
	case ITEMUNIQUE(13018): // Iī�� 
	case ITEMUNIQUE(13019): // Tī�� 
	case ITEMUNIQUE(13020): // Eī�� 		
		return true;
		break;
	}
	//----------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	// �������� ���� �ϴ��� Ȯ�� �Ѵ� 
	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		if( IsSealingUp( pclItemManager )  == false )	// ���εǾ� ���� �ʰ� 
		{
			// �������� ���� �ϸ� �����ش� 
			SI32 siDurability = GetDurability()	;
			SI32 siMAXDurability = GetMaxDurability()	;

			if(  siDurability > 0 && siMAXDurability > 0 )
			{
				return true	;
			}
		}
	}
	
	//----------------------------------------------------------------------------



	//=============================================================================

	return false;

//================================================================
#endif
//================================================================
}

//=============================================================================
//  @Name   IsPlusUseDate()
//! @brief  �Ⱓ������ �����Ѱ�?
//=============================================================================
bool cltItem::IsPlusUseDate(cltItemManagerCommon* pclItemManager)
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return false;
#else
//================================================================
	
	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if(ref <= 0)																				return false;

	//=============================================================================
	// �Ⱓ������ ������ ������ �߰��Ѵ�.
	//=============================================================================

	if(pclClient->IsCountrySwitch(Switch_UseDayPlusRevitalize))
	{
		SI32 itemType = pclItemManager->GetItemType(siUnique);

		// ���ǰ�̰�,
		if( itemType == ITEMTYPE_HELMET || 
			itemType == ITEMTYPE_ARMOUR ||
			itemType == ITEMTYPE_SHOES	||
			itemType == ITEMTYPE_BELT	||
			itemType == ITEMTYPE_SWORD	||
			itemType == ITEMTYPE_SPEAR	||
			itemType == ITEMTYPE_AXE	||
			itemType == ITEMTYPE_BOW	||
			itemType == ITEMTYPE_GUN	||
			itemType == ITEMTYPE_STAFF ||

			itemType == ITEMTYPE_AVATAR_MANTLE ||
			itemType == ITEMTYPE_AVATAR_DRESS ||
			itemType == ITEMTYPE_AVATAR_HAT ||
			itemType == ITEMTYPE_AVATAR_NECK ||
			itemType == ITEMTYPE_AVATAR_RING 

			)
		{
			// [����] �޸� �����̶�� �Ⱓ ���� �� �� ����.
			if( NULL != pclClient->pclDormancySystem)
			{
				CDormancyEquipItemReward *pclDormancyEquipItem = (CDormancyEquipItemReward *)pclClient->pclDormancySystem->GetDormancyEquipItemReward();

				if( NULL != pclDormancyEquipItem)
				{
					if( TRUE == pclDormancyEquipItem->IsDormancyEquipItem(siUnique))
					{
						return false;
					}
				}
			}

			// �Ⱓ�� �����ϸ�, �Ⱓ�� ������ �� �ִ�.
			if(uiDateUseDay > 0)
				return true;
		}
	}
	else
	{
		// ���Ⱓ�� �����ϴ� ���ǰ�� �Ⱓ ������ �����ϴ�.
		if( clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 && uiDateUseDay > 0 )
		{
			return true;
		}
	}

	//=============================================================================

	return false;

//================================================================
#endif
//================================================================
}

bool cltItem::IsCorrectPrivateEquip(cltItemManagerCommon* pclItemManager, SI32 siKind)
{
	SI32 type = GetType(pclItemManager);

	if (IsBulletItem() == TRUE)
		return TRUE;

	if(type)
	{
		SI64 atb = pclItemManager->pclItemTypeInfo[type]->siAtb;
		if( (atb & ITEMATB_OBJECT) == 0)return false;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if ( ref > 0 )
	{
		SI32 atb = pclItemManager->pclItemInfo[ref]->siItemInfoAtb ;

		if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST) == true)
		{
			if (siKind != 0 && siKind != KIND_HERO3 && siKind != KIND_HEROINE3)
				return false;
		}

		if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_WEST) == true)
		{
			if (siKind != 0 && siKind != KIND_HERO4 && siKind != KIND_HEROINE4)
				return false;
		}

		return true;

	}
	else
	{
		return false;
	}


}

bool cltItem::IsCreateSID(cltItemManagerCommon* pclItemManager)
{
//================================================================
// DBMANAGER �ΰ��� ������� �ʴ´�.
//================================================================
#ifdef _DBMANAGER
	return false;
#else
//================================================================
	if( siUnique <= 0 )													return false;

	SI32 ref = pclItemManager->FindItemRefFromUnique(siUnique);
	if( ref <= 0 )														return false;

	// SID �ʿ�
	if( CanPile(pclItemManager)	== false )								return true;

//================================================================
#endif
//================================================================
	return false;
}


//[�߰� : Ȳ���� 2008. 1. 31 => cltTreasureBox, cltSpaceBox ���� ����� ������ ������ ã��.]
bool CanAddInv( bool BoxKind, cltItem* clItem, cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,
				SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue, SI16* pCheckPos )
{
	SI32 i;
	BOOL pileswitch = FALSE;			// �������� ��ø ��� ����. 
	if(pclitem == NULL)return FALSE;

	if (pclitem->GetItemNum() > MAX_ITEM_PILE_NUMBER)
		return false;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	if( pclitem->CanPile(pclItemManager ) == true)
	{
		pileswitch = TRUE;
	}
	else
	{
		pileswitch = FALSE;
	}

	//KHY - 0805 - ��Ʈ�彺 ����.
	// ����ü�� ��� Ư���� ����Ѵ�. -> old = ��ġ�� �ȵȴ�. new = ���ľ� �Ѵ�.
		

	SI32 end = 0, searchrange = 0;
	
	if( true == BoxKind)
	{
		end = MAX_ITEM_TREASURE_BOX;
	}
	else
	{
		end = MAX_ITEM_SPACE_BOX;
	}


	// �̹� ���� �������� �����ϴ��� Ȯ���Ѵ�. 
	// ���� �������� �����ϰ� ��ø�� ������ �ִ� ���� �ȿ� ������ ��ø������ ���δ�. 
	if(pileswitch == TRUE)
	{
		for(i = 0; i < end; i++)
		{
			if((clItem[i].siUnique == pclitem->siUnique) &&
				(clItem[i].CanPile(pclItemManager) == true))
			{
				if(clItem[i].GetItemNum() + pclitem->GetItemNum() <= MAX_ITEM_PILE_NUMBER)
				{
					*pitempos = i;
					pcltoitem->Set(&clItem[i]);
					return true;
				}
			}
		}
	}

	// ���Ӱ� �߰��Ѵ�. 
	for(i = 0; i < end; i++)
	{
		if(clItem[i].siUnique)continue;

		// ����Ǿ� �ִ� �ڸ����, 
		if(pdwreserve && pdwreserve[i])continue;

		bool loop = false;
		if(pCheckPos)
		{
			for(SI16 j = 0; j < 5; ++j)
			{
				if(pCheckPos[j] == i)
				{
					loop = true;
					break;
				}
			}
		}

		if(true == loop)
			continue;

		*pitempos = i;
		return true;
	}

	return false;
}

SI16 GetBoxItemCount(bool BoxKind, cltItem* pclItem, SI16 siArrayCount)
{
	if(pclItem == NULL)
		return 0;

	SI32 end = 0;
	if( true == BoxKind)
	{
		end = MAX_ITEM_TREASURE_BOX;
	}
	else
	{
		end = MAX_ITEM_SPACE_BOX;
	}

	if(end != siArrayCount)
	{
		return 0;
	}

	SI16 ItemCount = 0;
	
	for(int  i = 0; i < end; i++)
	{
		if( pclItem[i].siUnique )
		{
			++ItemCount;
			continue;
		}
	}

	return ItemCount;
}

// ����ü �ɷ¿� ���� �ɷ� ��ġ�� ã�´�. - ���� ū ���� �����Ѵ�.
SI32 cltItem::GetAllCrystalAbilityNum(UI08 CrystalAbility)
{
	SI32 temAbNum = 0;
	SI32 returnAbNum = 0;

	bool bCount = false;
	
	for(SI16 i = 0; i < MAX_CRYSTAL_NUM; i++)
	{
		// �ƹ�Ÿ �������� ��罺ų�� ���, Ư���� ó���ؾ� �Ѵ�. 
		switch(cltItemCrytal[i].uiCrystalAbility)
		{
			case CRYSTALABILITY_SKILL_ALLMAKESKILL :  // ��� ������ 
			case CRYSTALABILITY_AVATAR_ALLMAKESKILL :
				{
					switch(CrystalAbility)
					{
						case CRYSTALABILITY_SKILL_MAKESWORD1 :
						case CRYSTALABILITY_SKILL_MAKESPEAR1 :
						case CRYSTALABILITY_SKILL_MAKEAXE1 :
						case CRYSTALABILITY_SKILL_MAKESTAFF1 :
						case CRYSTALABILITY_SKILL_MAKEBOW1 :
						case CRYSTALABILITY_SKILL_MAKEGUN1 :
						case CRYSTALABILITY_SKILL_MAKEARMOUR1 :
						case CRYSTALABILITY_SKILL_MAKEHELMET1 :
						case CRYSTALABILITY_SKILL_MAKESHOES1 :
						case CRYSTALABILITY_SKILL_MAKEBELT1 :
							bCount = true;
							break;				
					}
				}
				break;
			case CRYSTALABILITY_SKILL_ALLWEAPONSKILL :  // ��� ����� 
			case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL :
				{
					switch(CrystalAbility)
					{
						case CRYSTALABILITY_SKILL_USESWORD1 :
						case CRYSTALABILITY_SKILL_USESPEAR1 :
						case CRYSTALABILITY_SKILL_USEAXE1 :
						case CRYSTALABILITY_SKILL_USESTAFF1 :
						case CRYSTALABILITY_SKILL_USEBOW1 :
						case CRYSTALABILITY_SKILL_USEGUN1 :
							bCount = true;
							break;				
					}
				}
				break;			break;
			case CRYSTALABILITY_SKILL_ALLPRODUCTSKILL :  // ��� ����� 
			case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL :
				{
					switch(CrystalAbility)
					{
						case CRYSTALABILITY_SKILL_HORSETRAINING :
						case CRYSTALABILITY_SKILL_FARM :
						case CRYSTALABILITY_SKILL_MINE :
						case CRYSTALABILITY_SKILL_FISH :
						case CRYSTALABILITY_SKILL_MAKEIRON1 :
						case CRYSTALABILITY_SKILL_MAKETOOL1 :
						case CRYSTALABILITY_SKILL_MAKEFOOD :
						case CRYSTALABILITY_SKILL_MAKEMED :
						case CRYSTALABILITY_SKILL_ARTIFACT :
							bCount = true;
							break;				
					}
				}
				break;
			case CRYSTALABILITY_SKILL_ALLAVATARSKILL :  // ��� �ƹ�Ÿ ��ų 
			case CRYSTALABILITY_AVATAR_SKILL_ALLAVATARSKILL :
				{
					switch(CrystalAbility)
					{
						case SKILL_MAKEAVATAR_DRESS :
						case SKILL_MAKEAVATAR_HAT :
						case SKILL_MAKEAVATAR_MANTLE :
						case SKILL_MAKEAVATAR_RING :
						case SKILL_MAKEAVATAR_NECK :
							bCount = true;
							break;				
					}
				}
				break;
			default:
				{
					if(cltItemCrytal[i].uiCrystalAbility == CrystalAbility)  // ��Ÿ �� ��ų 
						bCount = true;

				}
				break;
		}

		if(bCount)
		{
			bCount = false;

			temAbNum = (SI32)cltItemCrytal[i].uiCrystalAbilityNum;

			if(temAbNum > returnAbNum)  // ���� ū ����.
				returnAbNum = temAbNum;
		}
	}

	return returnAbNum;
}

// �ش� ��ų ����ũ�� ���� ����ü �ɷ����� ��ȯ�Ѵ�.
SI32 cltItem::GetCrystalAbilityFromSkillUnique(SI32 skillunique)
{
	SI32 index = 0;

	while( Crystalskilldata[index*3] )
	{
		if(skillunique == Crystalskilldata[index*3])
		{		
			if( Crystalskilldata[index*3 + 1] !=0)
				return (SI32)Crystalskilldata[index*3 + 1];
		}

		index++;
	}

	return 0;
}


SI32 cltItem::GetCrystalGrade()
{
	switch ( siUnique )
	{
		case ITEMUNIQUE(1805):	// ������ü[F]
		case ITEMUNIQUE(1807):	// ���������ü[F]
		case ITEMUNIQUE(1809):	// �ڼ�������ü[F]
		case ITEMUNIQUE(1811):	// ���̾ư���ü[F]
		case ITEMUNIQUE(1813):	// ���ְ���ü[F]
		case ITEMUNIQUE(1815):	// �����̾����ü[F]
			{
				return CRYSTAL_GRADE_F;
			}
			break;

		case ITEMUNIQUE(1817):	// ������ü[E]
		case ITEMUNIQUE(1819):	// ���������ü[E]
		case ITEMUNIQUE(1821):	// �ڼ�������ü[E]
		case ITEMUNIQUE(1823):	// ���̾ư���ü[E]
		case ITEMUNIQUE(1825):	// ���ְ���ü[E]
		case ITEMUNIQUE(1827):	// �����̾����ü[E]
			{
				return CRYSTAL_GRADE_E;
			}
			break;

		case ITEMUNIQUE(1829):	// ������ü[D]
		case ITEMUNIQUE(1831):	// ���������ü[D]
		case ITEMUNIQUE(1833):	// �ڼ�������ü[D]
		case ITEMUNIQUE(1835):	// ���̾ư���ü[D]
		case ITEMUNIQUE(1837):	// ���ְ���ü[D]
		case ITEMUNIQUE(1839):	// �����̾����ü[D]
			{
				return CRYSTAL_GRADE_D;
			}
			break;

		case ITEMUNIQUE(1841):	// ������ü[C]
		case ITEMUNIQUE(1843):	// ���������ü[C]
		case ITEMUNIQUE(1845):	// �ڼ�������ü[C]
		case ITEMUNIQUE(1847):	// ���̾ư���ü[C]
		case ITEMUNIQUE(1849):	// ���ְ���ü[C]
		case ITEMUNIQUE(1851):	// �����̾����ü[C]
			{
				return CRYSTAL_GRADE_C;
			}
			break;

		case ITEMUNIQUE(1853):	// ������ü[B]
		case ITEMUNIQUE(1855):	// ���������ü[B]
		case ITEMUNIQUE(1857):	// �ڼ�������ü[B]
		case ITEMUNIQUE(1859):	// ���̾ư���ü[B]
		case ITEMUNIQUE(1861):	// ���ְ���ü[B]
		case ITEMUNIQUE(1863):	// �����̾����ü[B]
			{
				return CRYSTAL_GRADE_B;
			}
			break;

		case ITEMUNIQUE(1865):	// ������ü[A]
		case ITEMUNIQUE(1867):	// ���������ü[A]
		case ITEMUNIQUE(1869):	// �ڼ�������ü[A]
		case ITEMUNIQUE(1871):	// ���̾ư���ü[A]
		case ITEMUNIQUE(1873):	// ���ְ���ü[A]
		case ITEMUNIQUE(1875):	// �����̾����ü[A]
			{
				return CRYSTAL_GRADE_A;
			}
			break;

		case ITEMUNIQUE(1877):	// ������ü[S1]
		case ITEMUNIQUE(1879):	// ���������ü[S1]
		case ITEMUNIQUE(1881):	// �ڼ�������ü[S1]
		case ITEMUNIQUE(1883):	// ���̾ư���ü[S1]
		case ITEMUNIQUE(1885):	// ���ְ���ü[S1]
		case ITEMUNIQUE(1887):	// �����̾����ü[S1]
			{
				return CRYSTAL_GRADE_S1;
			}
			break;

		case ITEMUNIQUE(1889):	// ������ü[S2]
		case ITEMUNIQUE(1891):	// ���������ü[S2]
		case ITEMUNIQUE(1893):	// �ڼ�������ü[S2]
		case ITEMUNIQUE(1895):	// ���̾ư���ü[S2]
		case ITEMUNIQUE(1897):	// ���ְ���ü[S2]
		case ITEMUNIQUE(1899):	// �����̾����ü[S2]
			{
				return CRYSTAL_GRADE_S2;
			}
			break;

	}

	return CRYSTAL_GRADE_NONE;
}

bool cltItem::IsWeapon(cltItemManagerCommon* pclItemManager)
{
	if ( NULL == pclItemManager )
	{
		return false;
	}

	SI32 siType = GetType( pclItemManager );

	switch ( siType )
	{
		case ITEMTYPE_SWORD:
		case ITEMTYPE_SPEAR:
		case ITEMTYPE_AXE:
		case ITEMTYPE_BOW:
		case ITEMTYPE_GUN:
		case ITEMTYPE_STAFF:
			{
				return true;
			}
			break;
	}

	return false;
}

SI16 cltItem::GetEquipLevel( cltItemManagerCommon* pclItemManager )
{
	if ( NULL == pclItemManager )
	{
		return 0;
	}

	SI32 siRef = pclItemManager->FindItemRefFromUnique( siUnique );
	if ( 0 >= siRef )
	{
		return 0 ;
	}

	return pclItemManager->pclItemInfo[siRef]->clCondition.siLevel;

}

void cltItem::GetGMSectionData(GMSectionData* pkGMSectionData)
{
	if( pkGMSectionData == NULL )			return;

}

bool cltItem::CancellationSealingUp( SYSTEMTIME sTime )
{
	// ���Ⱓ�� ���°��� �к������� �ʿ����
	if ( 0 >= uiDateUseDay )
	{
		return false;
	}

	// ���� ��¥�� �����°��� 2000�����̸� ����
	if ( 2000 >= sTime.wYear )
	{
		return false;
	}

	// ���� ��¥�� �������ش�
	uiDateYear	= (UI08)(sTime.wYear - 2000);
	uiDateMonth	= (UI08)sTime.wMonth;
	uiDateDay	= (UI08)sTime.wDay;

	return true;
}

// �����, ������, ����� ���� ��ų���� �ϳ��� �������ش�.
SI32 cltItem::SelectUseBaseSkillTypeToAvatar(UI32 uiBaseSkillType)
{
	//================================================================
	// DBMANAGER �ΰ��� ������� �ʴ´�.
	//================================================================
#ifdef _DBMANAGER
	return false;
#else
	//================================================================

	//	[��ȣ] �����Ҽ� �ִ� ��ų�� �ߺз� ��ųŸ�Ե��� �Ѱ����� ��ų�� �ݴϴ�.
	//	��ųŸ�Ժ��� ���ԵǴ� ��ų ������ ��ų�Ŵ����� �߰��ϴ� ���� �ϵ��ڵ��� ���� ���� �� �����ϴ�.

	UI32 returnDivideSkillType = 0;
	UI32 uiDetailSelectValue = 0;

	switch(uiBaseSkillType)
	{
	case SKILLTYPE_R_USEWEAPON:		
		{
			uiDetailSelectValue = rand() % 6;	//	������� �� 6����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_USESWORD1;	break;	//	�˼�
			case 1:	returnDivideSkillType = SKILL_USESPEAR1;	break;	//	â��
			case 2:	returnDivideSkillType = SKILL_USEAXE1;	break;	//	������
			case 3:	returnDivideSkillType = SKILL_USESTAFF1;	break;	//	�����̼�
			case 4:	returnDivideSkillType = SKILL_USEBOW1;	break;	//	Ȱ��
			case 5:	returnDivideSkillType = SKILL_USEGUN1;	break;	//	�Ѽ�
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_MAKEWEAPON:		
		{
			uiDetailSelectValue = rand() % 6;		//	�������ۼ��� �� 6����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_MAKESWORD1;	break;	//	�����ۼ�
			case 1:	returnDivideSkillType = SKILL_MAKESPEAR1;	break;	//	â���ۼ�
			case 2:	returnDivideSkillType = SKILL_MAKEAXE1;	break;	//	�������ۼ�
			case 3:	returnDivideSkillType = SKILL_MAKESTAFF1;	break;	//	���������ۼ�
			case 4:	returnDivideSkillType = SKILL_MAKEBOW1;	break;	//	Ȱ���ۼ�
			case 5:	returnDivideSkillType = SKILL_MAKEGUN1;	break;	//	�����ۼ�
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_ARMOR:		
		{
			uiDetailSelectValue = rand() % 4;		//	�����ۼ��� �� 4����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_MAKEARMOUR1;	break;	//	�������ۼ�
			case 1:	returnDivideSkillType = SKILL_MAKEHELMET1;	break;	//	�������ۼ�
			case 2:	returnDivideSkillType = SKILL_MAKEBELT1;		break;	//	��Ʈ���ۼ�
			case 3:	returnDivideSkillType = SKILL_MAKESHOES1;		break;	//	�Ź����ۼ�
			default:
				false;
				break;
			}
		}

		break;

	case SKILLTYPE_R_MAKEHARVEST:	
		{
			if (pclClient->IsCountrySwitch(Switch_Artifact))
				uiDetailSelectValue = rand() % 5;		//	����ü ����ġ�� ���� �ִٸ� �������ۼ��� �� 5����
			else
				uiDetailSelectValue = rand() % 4;		//	����ü ����ġ�� �����ִٸ� 4����

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_MAKEMED;		break;	//	��������
			case 1:	returnDivideSkillType = SKILL_MAKEFOOD;		break;	//	�丮������
			case 2:	returnDivideSkillType = SKILL_MAKEIRON1;		break;	//	ö�����ۼ�
			case 3:	returnDivideSkillType = SKILL_MAKETOOL1;		break;	//	���굵�����ۼ�
			case 4:	returnDivideSkillType = SKILL_ARTIFACT;		break;	//	����ü���ۼ�
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_HARVEST:		
		{
			uiDetailSelectValue = rand() % 3;		//	�������� �� 3����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_FISH;		break;	//	��ȹ��
			case 1:	returnDivideSkillType = SKILL_FARM;		break;	//	����
			case 2:	returnDivideSkillType = SKILL_MINE;		break;	//	ä����	
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_MAKECLOTH:		
		{
			uiDetailSelectValue = rand() % 3;		//	��ܼ��� �� 3����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_MAKEAVATAR_DRESS;		break;	//	�Ǻ����ۼ�
			case 1:	returnDivideSkillType = SKILL_MAKEAVATAR_HAT;			break;	//	�������ۼ�
			case 2:	returnDivideSkillType = SKILL_MAKEAVATAR_MANTLE;		break;	//	�������ۼ�	 
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_MAKEACCESSARY:	
		{
			uiDetailSelectValue = rand() % 2;		//	�׼��������ۼ��� �� 2����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_MAKEAVATAR_RING;		break;	//	�������ۼ�
			case 1:	returnDivideSkillType = SKILL_MAKEAVATAR_NECK;		break;	//	��������ۼ�
			default:
				false;
				break;
			}
		}
		break;

	case SKILLTYPE_R_ETC:				
		{
			uiDetailSelectValue = rand() % 3;		//	��Ÿ����� �� 3����		

			switch(uiDetailSelectValue)
			{
			case 0:	returnDivideSkillType = SKILL_CAPTURE;			break;	//	��ȯ��
			case 1:	returnDivideSkillType = SKILL_SUMMON;				break;	//	��ȹ��
			case 2:	returnDivideSkillType = SKILL_HORSETRAINING;		break;	//	�����ü�
			default:
				false;
				break;
			}
		}
		break;
	}	

	return returnDivideSkillType;

#endif
}


void cltItemAvatarRing::SetQualityRate( SI32 siQualityRate )
{
	if(siQualityRate > 0)
	{
		if(uiAC > 0)
			uiAC		= max(1, uiAC * siQualityRate / 100 );

		if(uiStr > 0)
			uiStr		= max(1, uiStr * siQualityRate / 100 );

		if(uiDex > 0)
			uiDex		= max(1, uiDex * siQualityRate / 100 );

		if(uiVit > 0)
			uiVit		= max(1, uiVit * siQualityRate / 100 );

		if(uiMag > 0)
			uiMag		= max(1, uiMag * siQualityRate / 100 );

		if(uiWis > 0)		
			uiWis		= max(1, uiWis * siQualityRate / 100 );

		if(uiLuk > 0)		
			uiLuk		= max(1, uiLuk * siQualityRate / 100 );

		if(uiHnd > 0)		
			uiHnd		= max(1, uiHnd * siQualityRate / 100 );
	}
}
	
