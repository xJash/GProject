//---------------------------------
// 2003/5/17 김태곤
//---------------------------------

#ifndef _CLTITEM_H
#define _CLTITEM_H

#include "ItemCommon.h"
#include "ItemUnit.h"

#include "../../NLib/NDataLoader.h"
#include "../../NLib/NArray.h"
#include "../../../common/Char/PersonNameManager/PersonNameManager.h"
#include "../../../common/Item/ItemCommon/cltSetItem.h"
//-------------------------------------------
// TradeServer
//-------------------------------------------
#define MAX_TRADESERVER_OBJECT_RANK		500 // 무역 서버 최대 등급 수

//---------------------------------
// 2007/5/16 김희영
//---------------------------------
#define MAKE_BY_MUNIN 1  // 0 = out, 1 = in
#define MAX_ITEMGRADE 10
#define ENCHANT_WRITE_TIME 300000 // 5min
//---------------------------------

#define MAX_ITEM_ITEMMALLIMAGE_NUM		250		// 아이템 몰에 사용할 한파일에 최대 들어가는 이미지 숫자

//---------------------------------
// 소환수 아이템관련
//---------------------------------
#define SUMMON_EQUIP_LIMITMINLEVEL 90	// 소환수가 아이템을 장착하기 위해 필요한 최소레벨


// 무역시 참고할 등급의 폭
const SI32 siTradeServerObejectRank[MAX_TRADESERVER_OBJECT_RANK] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
190, 191, 192, 193, 194, 195, 196, 197, 198, 199,

200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
230, 231, 232, 233, 234, 235, 236, 237, 238, 239,	  
240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
250, 251, 252, 253, 254, 255, 256, 257, 258, 259,
260, 261, 262, 263, 264, 265, 266, 267, 268, 269,
270, 271, 272, 273, 274, 275, 276, 277, 278, 279,
280, 281, 282, 283, 284, 285, 286, 287, 288, 289,
290, 291, 292, 293, 294, 295, 296, 297, 298, 299,

300, 301, 302, 303, 304, 305, 306, 307, 308, 309,
310, 311, 312, 313, 314, 315, 316, 317, 318, 319,
320, 321, 322, 323, 324, 225, 326, 327, 328, 329,
330, 331, 332, 333, 334, 335, 336, 337, 338, 339,	  
340, 341, 342, 343, 344, 345, 346, 347, 348, 349,
350, 351, 352, 353, 354, 355, 356, 357, 358, 359,
360, 361, 362, 363, 364, 365, 366, 367, 368, 369,
370, 371, 372, 373, 374, 375, 376, 377, 378, 379,
380, 381, 382, 383, 384, 385, 386, 387, 388, 389,
390, 391, 392, 393, 394, 395, 396, 397, 398, 399,

400, 401, 402, 403, 404, 405, 406, 407, 408, 409,
410, 411, 412, 413, 414, 415, 416, 417, 418, 419,
420, 421, 422, 423, 424, 425, 426, 427, 428, 429,
430, 431, 432, 433, 434, 435, 436, 437, 438, 439,	  
440, 441, 442, 443, 444, 445, 446, 447, 448, 449,
450, 451, 452, 453, 454, 455, 456, 457, 458, 459,
460, 461, 462, 463, 464, 465, 466, 467, 468, 469,
470, 471, 472, 473, 474, 475, 476, 477, 478, 479,
480, 481, 482, 483, 484, 485, 486, 487, 488, 489,
490, 491, 492, 493, 494, 495, 496, 497, 498, 499,

500, 501, 502, 503, 504, 505, 506, 507, 508, 509,
510, 511, 512, 513, 514, 515, 516, 517, 518, 519,
520, 521, 522, 523, 524, 525, 526, 527, 528, 529,
530, 531, 532, 533, 534, 535, 536, 537, 538, 539,	  
540, 541, 542, 543, 544, 545, 546, 547, 548, 549,
550, 551, 552, 553, 554, 555, 556, 557, 558, 549,
560, 561, 562, 563, 564, 565, 566, 567, 568, 569,
570, 571, 572, 573, 574, 575, 576, 577, 578, 579,
580, 581, 582, 583, 584, 585, 586, 587, 588, 589,
590, 591, 592, 593, 594, 595, 596, 597, 598, 599,
};

#define MAX_ITEMTYPE_NUMBER		46	//아티팩트 추가하면서 아이템 타입을 하나 늘렸음36->37. 아이템 카테고리 정리하면서 42로 늘림 37->42, 아바타장인타입 추가하면서 46로 늘림. 42->46.
#define MAX_ITEM_NAME_LENGTH	60
#define MAX_TOOL_NUMBER			5

#define DRESS_ADD_DPOWER_RATE	1	// 갑옷이 있는 상태에서는 의복의 방어력은 1/1만큼만 적용된다.  ( 일본판에선 무시되고 있다는셈이다)

#define MAX_ITEM_UNIQUE			30000

//---------------------------------
// 효과음을 위한 아이템 분류 
//---------------------------------
#define ITEMSOUND_BOOK					1
#define ITEMSOUND_BOW					2
#define ITEMSOUND_CLOTH					3
#define ITEMSOUND_FOOD					4
#define ITEMSOUND_HEAL					5
#define ITEMSOUND_HELMET				6
#define ITEMSOUND_SWORD					7
#define ITEMSOUND_MEAT					8
#define ITEMSOUND_NOODLE				9
#define ITEMSOUND_SOUP					10
#define ITEMSOUND_VEGETABLE				11
#define ITEMSOUND_AXE					12
#define ITEMSOUND_BELT					13
#define ITEMSOUND_ETC					14
#define ITEMSOUND_GUN					15
#define ITEMSOUND_NECK					16
#define ITEMSOUND_SHOES					17
#define ITEMSOUND_STAFF					18
#define ITEMSOUND_TICKET				19
#define ITEMSOUND_CERAMIC				20
#define ITEMSOUND_SMELLHEAL				21 // 악취탕
#define ITEMSOUND_UNFREEZEHEAL			22 // 진무탕

#define CANMAKE_ERROR_NOMATERIAL		1
#define CANMAKE_ERROR_NOTOOL			2
#define CANMAKE_ERROR_USE_PERSONSHOP	3	// 개인상점(판매)에 아이템이 올라가서 제조를 할 수 없다
//KHY - 1211 - 과금상품 - 만능 도구
#define CANMAKE_USE_ALLPURPOSETOOL		4    //만능 도구함을 사용 했다.



#define HEALEFT_NOFIRSTATTACK			1
#define HEALEFT_UNFREEZE				2
#define HEALEFT_PREMIUM					3	// 경험치 프리미엄
#define HEALEFT_COMBAT					4	// 전투 프리미엄
#define HEALEFT_DIGESTIVE				5   // 배부름 감소
#define HEALEFT_ALLDESEASE				6   // 질병 해제
#define HEALEFT_FAME					7	// 명성 증가
#define HEALEFT_BULLET					8	// 탄환 프리미엄
#define HEALEFT_HEROSTAMINA				9	// 주인공 스태미너 증가
#define HEALEFT_SUMMONSTAMINA			10	// 소환수 스태미너 프리미엄
#define HEALEFT_NOFIRSTATTACK_PREMIUM	11	// 프리미엄 선공 방지약
#define HEALEFT_RESURRECTION			12	// 부활 약
#define HEALEFT_SUMMONATACUP			13	// 소환수 공격력,방어력 증가 20% 약
#define HEALEFT_HEROATTACKUP			14	// 주인공 공격력 증가 20% 약
#define HEALEFT_HERODEFENSEUP			15	// 주인공 방어력 증가 20% 약
#define HEALEFT_LOVEPOWER				16	// 주인공 전투,제조 경험치 50% 증가, 소환수 스테미너제 효과, 소환수 공격력 20% 증가
#define HEALEFT_FRIENDSHIP				17	// 주인공 전투,제조 경험치 20% 증가, 공격력, 방어력 20% 증가
#define HEALEFT_HORSEWINGS				18	// 말능력 향상 이용권
#define HEALEFT_SUCCESS_MANUFACTURE		19	// 제조 실패 보장
#define HEALEFT_MOFUMOFU_PERFUME		20	// 모후모후 향수
#define HEALEFT_FOURLEAF				21	// 네잎 클로버
#define HEALEFT_PREMIUMEXPUP			22	// 특제 파나의성장비약
#define HEALEFT_ADDEXP					23	// 백년
#define HEALEFT_MARKETPREMIUM			24	// 마켓 프리미엄
#define HEALEFT_HAPPYBEAN				25	// 해피빈 이벤트 해피타임 [2007.08.22 손성웅].
#define HEALEFT_HEROATTACKUP30			26	// 전투력 증강약 30일간 [2007.08 30 손성웅]
#define HEALEFT_HERODEFENSEUP30			27	// 방어력 증가약 30일간[2007.08.30 손성웅]
#define HEALEFT_SUPEREXPUP				28	// 열혈 EXP 캡슐 7일 30일 [2007. 09.18 손성웅]
#define HEALEFT_BLACKCACAORANDOM		29	// KHY - 0115 발렌타인데이 이벤트. - 블랙카카오.
#define HEALEFT_CANDYRANDOM				30	// KHY - 0218 화이트데이 이벤트. - 화이트 캔디.
#define HEALEFT_REWARDBONUS				31	// 강형 - 이관 보상 아이템 - 전투, 제조 경험치 200%, 아이템 획득 2배
#define HEALEFT_PREMIUMMAKEEXPUP		32	// 춘기 - 제조 프리미엄 아이템 - 30일간 제조 경험치 200% 상승
#define HEALEFT_SPECIALAMPUL			33	// 지연 - 스페셜 엠플 - 48분간 300% 전투 경험치 획득.
#define HEALEFT_QUEST_ANTIPOTION		34	// 영훈 - 퀘스트 진행시 아수라에게 받는 데미지를 30%갂는다
#define HEALEFT_ANTIDOTES				35	// 지연 - 해독약 - 모든 중독 상태에서 해독한다.
#define HEALEFT_TRANSFORM_SYNCRO_UP		36	// [진성] 싱크로 증가제.
#define HEALEFT_QUEST_ATTACK			37  // [춘기] 퀘스트 진행시 뼈티라노에게 30%의 공격력 증가를 가한다.
#define HEALEFT_SUMMONNOFIRSTATTACK		38	// [기형] 소환수 선공 방지
#define HEALEFT_RESIDENTS_EXPUP_10		39	// [지연] 마을 EXP 캡슐 - 사용시 사용자가 소속된 마을의 주민들에게 경험치 10% 증가 효과.
#define HEALEFT_RESIDENTS_STRONG		40  // [지연] 마을 강화제 - 사용시 사용자가 소속된 마을의 주민들에게 물리/마법 공격력, 방어력 +10% 증가 효과.

#define MAX_SCROLL_EFFECT				500	// 부적은 최대 50%까지만 부착 가능.

// 부적 부착 실패 원인. 
#define ENCHANT_FAIL_REASON_NOMORE		1		// 부적을 더이상 붙일 수 없다. 
#define ENCHANT_FAIL_REASON_NOTATBMATCH	2		// Attribute에 적합하지 않는 부적 
#define ENCHANT_FAIL_REASON_NOMOREKIND  3		// 부적은 2종류이상 붙일수 없다.

#define DUR_FOR_DISMANTLE	400		// 해체에 필요한 최대 내구도(이 수치 이하여야 해체를 할 수 있다. )  


//----------------------------------------
// 부적과 혹부리영감을 사용하여 개조할 수 있는 최대 비율. (기본 성능의 이 배수 만큼만 가능) 
//----------------------------------------
#define SCROLL_TUNE_MAX_RATE			2

//----------------------------------------
// 부적과 혹부리 영감을 사용한 개조 실패 이유 .
//----------------------------------------
#define SCROLLTUNE_ERR_MINDAMAGE		1
#define SCROLLTUNE_ERR_MAXDAMAGE		2
#define SCROLLTUNE_ERR_AC				3

//----------------------------------------
// 속성 인첸트 성공 실패 결과.
//----------------------------------------

const SI32 ENCHANT_SUCCESS		= 1;
const SI32 ENCHANT_FAIL			= 0;
const SI32 ENCHANT_DOWNGRADE	= -1;
const SI32 ENCHANT_BROKEN		= -2;

const SI32 ENCHANT_USEDAYPLUS	= 100;
const SI32 ENCHANT_USEDAYPLUS_ITEMUNIQUE		= ITEMUNIQUE(5400);
//----------------------------------------
// [영훈] 인첸트 속성 변경 아이템
//----------------------------------------
const SI32 ENCHANT_CHANGE		= 110;
const SI32 ENCHANT_CHANGE_ELEMENT_ITEMUNIQUE	= ITEMUNIQUE(5413);

//----------------------------------------
// [영훈] 아티펙트 아이템 등급
//----------------------------------------
enum CRYSTAL_GRADE
{
	CRYSTAL_GRADE_NONE	= 0	//등급이 없음(크리스탈 아이템이 아님)

	,CRYSTAL_GRADE_F
	,CRYSTAL_GRADE_E
	,CRYSTAL_GRADE_D
	,CRYSTAL_GRADE_C
	,CRYSTAL_GRADE_B
	,CRYSTAL_GRADE_A
	,CRYSTAL_GRADE_S1
	,CRYSTAL_GRADE_S2

	//---------------------------------------
	// 새로운 등급은 위에 추가해 주세요
	//---------------------------------------
	,CRYSTAL_GRADE_MAX
};


class cltKindItemProbabilitySet;
class cltPSkillInfo;
class cltItemPrice;
class cltNPCItemInfo;
class cltSkillManager;
class cltDiseaseManager;
class cltItemPriceUnit;
class cltBasicAbility;
class cltCharCommon;
class cltSummon;
class DBMaterialInfo;

class cltSetItemAbility;			//[진성] 세트 아이템 능력 정보.
class cltSetItemAbilityManager;		//[진성] 세트 아이템 능력 정보 메니져.
class CSetItemManager;
class cltSkillBookManager;
// [성웅] 레벨 보상 상자에서 아이템을 준다 
class cltRewardItemForLimitLevel;	// 중국레벨 보상 아이템 

//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 타입.
class cltCrystalItemData{
public:
	SI32 siCrystalType;
	SI16 siMinValue;
	SI16 siMaxValue;
	SI32 siTypeRate;	

	void Set(cltCrystalItemData* pclcon)
	{
		if(pclcon == NULL)				return;

		siCrystalType		= pclcon->siCrystalType;
		siMinValue			= pclcon->siMinValue;
		siMaxValue			= pclcon->siMaxValue;
		siTypeRate			= pclcon->siTypeRate;
	}
};
////합성재료 아이템 데이터
//class cltCompositionManterialItemData{
//public:
//	SI32 siCompositionManterialType;
//	SI32 siPara;
//	SI32 siTypeRate;	
//
//	void Set(cltCompositionManterialItemData* pclcon)
//	{
//		siCompositionManterialType			= pclcon->siCompositionManterialType;
//		siPara								= pclcon->siPara;
//		siTypeRate							= pclcon->siTypeRate;
//	}
//};

//--------------------------------------
// 아이템 장착 제한. // 2003.10.23
//--------------------------------------
class cltItemConition{
public:
	SI32 siLevel;
	SI32 siStr;
	SI32 siDex;
	SI32 siMag;
	SI32 siVit;
	SI32 siHnd;
	
	SI32 siSkillKind;			// 사용 스킬의 종류
	SI32 siSkillPoint;			// 사용 스킬의 포인트 
	
	bool bForMan;				// 남성용 여부. 
	bool bForWoman;				// 여성용 여부.
	SI16 siGrownUp;				// 성인 전용 아이템 - 군주 스페셜에서 사용
	
	SI16 siFameLevel;			// 명성등급 제한. 

	SI16 siBaseSkillType;		// [지연] 아바타 목걸이 : 베이스 스킬 타입


	cltItemConition()
	{
		siLevel = 0;
		siStr	= 0;
		siDex	= 0;
		siMag	= 0;
		siVit	= 0;
		siHnd	= 0;

		siSkillKind = 0;
		siSkillPoint = 0;

		bForMan		= true;
		bForWoman	= true;
		siGrownUp	= 0;

		siFameLevel	= 0;

		siBaseSkillType = 0;
	}

	cltItemConition(SI32 level, SI32 str, SI32 dex, SI32 mag, SI32 Vit, SI32 Hnd, SI32 SkillKind, SI32 SkillPoint, bool bforman, bool bforwoman, SI16 grownup ,SI16 famelevel, SI32 baseSkillType = 0 )
	{
		siLevel			= level;
		siStr			= str;
		siDex			= dex;
		siMag			= mag;
		siVit			= Vit;
		siHnd			= Hnd;
		siSkillKind		= SkillKind;
		siSkillPoint	= SkillPoint;

		bForMan			= bforman;
		bForWoman		= bforwoman;
		siGrownUp		= grownup;

		siFameLevel		= famelevel;

		siBaseSkillType = baseSkillType;		// [지연] 아바타 목걸이의 베이스 스킬 타입 저장

	}

	void Set(cltItemConition* pclcon)
	{
		siLevel			= pclcon->siLevel;
		siStr			= pclcon->siStr;
		siDex			= pclcon->siDex;
		siMag			= pclcon->siMag;
		siVit			= pclcon->siVit;
		siHnd			= pclcon->siHnd;
		siSkillKind		= pclcon->siSkillKind;
		siSkillPoint	= pclcon->siSkillPoint;

		bForMan			= pclcon->bForMan;
		bForWoman		= pclcon->bForWoman;
		siGrownUp		= pclcon->siGrownUp;
		
		siFameLevel		= pclcon->siFameLevel;

		siBaseSkillType = pclcon->siBaseSkillType;

	}

	// 조건에 부합하는지 확인한다. 
	bool Check(SI32 itemtype, SI32 kind, SI32 level, 
		SI32 str, SI32 dex, SI32 mag, SI32 vit, SI32 hnd, SI32 skillpoint, SI32 famelevel, 
		SI32* returnval);
	
	// 조건의 문자열을 얻어온다. 
	bool GetText( TCHAR* text, SI16 txtSize, TCHAR *SkillName, SI32 SkillKind );
	
	// 조건에 부합하는지 확인된 문자열을 얻어온다. ( 색상 스크립트 정보( ex - <C05>  </C>) 가 포함된다 )
	bool GetCheckedText(  TCHAR* text, SI16 txtSize, TCHAR *SkillName, SI32 SkillKind, cltCharCommon * pclchar  );

};

//--------------------------------------
// 아이템 생산에 필요한 스킬 정보. 
//--------------------------------------
class cltItemSkillInfo{
public:
	SI32 siSkill;			// 필요한 기술. 
	SI32 siSkillLevel;		// 필요한 기술의 최저 레벨 
	SI32 siMakePbt;			// 기본 생산 가능성(퍼밀) 
	SI32 siIncPbt;			// 레벨 1당 증가 생산 가능성 (퍼밀) 
	
	SI32 siHnd;				// 아이템 생산에 필요한 손재주 
	SI32 siMag;				// 아이템 생산에 필요한 도력. 
	

	cltItemSkillInfo()
	{
		siSkill			= 0;
		siSkillLevel	= 0;
		siMakePbt		= 0;
		siIncPbt		= 0;

		siHnd			= 0;
		siMag			= 0;
	}
	cltItemSkillInfo(SI32 skill, SI32 level, SI32 makepbt, SI32 incpbt, SI32 hnd, SI32 mag)
	{
		siSkill			= skill;
		siSkillLevel	= level;
		siMakePbt		= makepbt;
		siIncPbt		= incpbt;

		siHnd			= hnd;
		siMag			= mag;
	}
	void Set(cltItemSkillInfo* pclinfo)
	{
		siSkill			= pclinfo->siSkill;
		siSkillLevel	= pclinfo->siSkillLevel;
		siMakePbt		= pclinfo->siMakePbt;
		siIncPbt		= pclinfo->siIncPbt;
		siHnd			= pclinfo->siHnd;
		siMag			= pclinfo->siMag;
	}
};


//---------------------------------------
class cltSplitItemInfo{
public:
	UI16 uiFrom;		
	UI16 uiTo;
	SI32 siCount;		// 분할할 갯수..

	cltSplitItemInfo()
	{
		ZeroMemory(this, sizeof(cltSplitItemInfo));
	}
	cltSplitItemInfo(UI16 uifrom, UI16 uito, SI32 sicount)
	{
		uiFrom		= uifrom;
		uiTo		= uito;
		siCount		= sicount;
	}
};

//---------------------------------------
// 아이템 이동 정보. 
//---------------------------------------
class cltMoveItemInfo{
public:
	//From
	UI16 uiFrom;					// 어디에서 옮기는가.

	//To
	UI16 uiTo;						// 어디로 옮기는가 ?

	cltMoveItemInfo()
	{
		ZeroMemory(this, sizeof(cltMoveItemInfo));
	}

	cltMoveItemInfo(UI16 uifrom, UI16 uito)
	{
		uiFrom		= uifrom;
		uiTo		= uito;
	}

};


//-------------------------------------
// 아이템을 사용 정보 
//-------------------------------------
class cltItemUseInfo{
public:
	// 사용할 아이템의 위치. 
	UI16 uiFrom;					// 어디에서 옮기는가.

	SI32 siItemUnique;				// 사용할 아이템의 유니크. 

	cltItemUseInfo()
	{
		ZeroMemory(this, sizeof(cltItemUseInfo));
	}

	cltItemUseInfo(UI16 uifrom, SI32 iteunique)
	{
		uiFrom			= uifrom;
		siItemUnique	= iteunique;
	}
};

//---------------------------------------
// 아이템 타입 정보. 
//---------------------------------------	
#define MAX_ITEMTYPE_NAME_LENGTH 128
class cltItemTypeInfo{
public:
	SI32 siUnique;
	SI64 siAtb;
	SI64 siAttach;
	TCHAR szName[MAX_ITEMTYPE_NAME_LENGTH];
	TCHAR szTypeCode[MAX_ITEMTYPE_NAME_LENGTH];

	cltItemTypeInfo(SI32 siunique, SI64 siatb, SI64 siattach, const TCHAR* typecode, const TCHAR* pname);
	~cltItemTypeInfo();

	BOOL IsAtb(SI64 atb)const;
	BOOL IsAttach(SI64 atc)const;

	const TCHAR* GetName()const{return szName;}

};


//---------------------------------------
// 아이템 생산 정보. 
//---------------------------------------
class cltItemproductionInfo{
public:
	SI32			siProductUnit;							// 생산의 단위 개수. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltMaterialInfo, MAX_MATERIAL_NUMBER>	clMaterial;
	NSafeTArray<cltToolInfo, MAX_TOOL_NUMBER>			clTool;
#else
	cltMaterialInfo clMaterial[MAX_MATERIAL_NUMBER];		//아이템의 재료. 
	cltToolInfo		clTool[MAX_TOOL_NUMBER];
#endif

	cltItemproductionInfo(){}

	bool AddMaterial(cltMaterialInfo* pclmaterial)
	{
		SI32 i;
		for(i = 0;i < MAX_MATERIAL_NUMBER;i++)
		{
			if(clMaterial[i].siUnique == 0)
			{
				clMaterial[i].Set(pclmaterial);
				return true;
			}
		}

		return false;
	}

	bool AddTool(cltToolInfo* pcltool)
	{
		SI32 i;

		for(i = 0;i < MAX_TOOL_NUMBER;i++)
		{
			if(clTool[i].siUnique == 0)
			{
				clTool[i].Set(pcltool);
				return true;
			}
		}

		return false;
	}

	SI32 GetToolCount()
	{
		SI32 siRet = 0;
		for(SI32 i = 0;i < MAX_TOOL_NUMBER;i++)
		{
			if(clTool[i].siUnique > 0)
			{
				siRet++;
			}
		}
		return siRet;
	}
};

//---------------------------------------
// 아이템 Unique별 정보. 
//---------------------------------------
#define ADAPT_MAN		1	// 사람에게 적용되는 아이템. 
#define ADAPT_SUMMON	2	// 소환수에게 적용되는 아이템. 


//--------------------------------------
// ItemInfoAtb
//--------------------------------------
#define ITEMINFOATB_FARMTOOL			 			0x1			// 농경용 도구. 
#define ITEMINFOATB_MINETOOL			 			0x2			// 광업용 도구. 
#define ITEMINFOATB_CANUSEITEM			 			0x4			// 사용가능한 물품인가. 
#define ITEMINFOATB_SHOWLIST			 			0x8
#define ITEMINFOATB_TRADELIST			 			0x10		// 현재 소스에서 안 씀
#define ITEMINFOATB_ITEMMALL			 			0x20		// 아이템몰에서 판매하는 상품이다. 
#define ITEMINFOATB_NOTDAILYQUEST		 			0x40		// 쿠마(모병관) 퀘스트에 안나오는 물품
#define ITEMINFOATB_NOTWENNYOLDMAN		 			0x80		// 2호식(혹부리) 에 안나오는 물품
#define ITEMINFOATB_NOTTRADE			 			0x100		// 거래안되는 물품( 땅에도 버릴 수 없다 )
#define CANUSEITEM_TYPE_EAST			 			0x200		// 동양캐릭만 가능
#define CANUSEITEM_TYPE_WEST			 			0x400		// 서양캐릭만 가능
#define ITEMINFOATB_TYPE_QUESTITEM		 			0x800		// 퀘스트 아이템 
#define ITEMINFOATB_FIRSTACTION			 			0x1000		// 별도의 선조치 아이템
#define ITEMINFOATB_SPECIAL_JAPAN		 			0x2000		// 일본 특산품
#define ITEMINFOATB_SPECIAL_GLOBAL		 			0x4000		// 글로벌 특산품
#define ITEMINFOATB_SPECIAL_KOREA		 			0x8000		// 한국 특산품
#define ITEMINFOATB_WENNYOLDMAN_MATERIAL 			0x10000		// 2호식(이호식, 혹부리) 분해시 전용 재료를 반환해주는 아이템
#define ITEMINFOATB_NOTSELL				 			0x20000		// NPC에게 팔 수 없다
#define ITEMINFOATB_PARTYHALL_SYMBOL	 			0x40000		//[진성] 파티홀. 장식품 아이템. => 2008. 3. 12
#define ITEMINFOATB_PARTYHALL_PRESENT	 			0x80000		//[진성] 파티홀. 선물.			=> 2008. 3. 12
#define ITEMINFOATB_CRYSTAL_REMOVE		 			0x100000	//[진성] 아티펙트 관련. 분리용 결정체 ITEMINFOATB_ => 2008-4-2  
#define ITEMINFOATB_CRYSTAL_SLOT_CREATE	 			0x200000	//[진성] 아티펙트 관련. 생성용 결정체 ITEMINFOATB_ => 2008-4-2  
#define ITEMINFOATB_RARE_SUMMONDOLL		 			0x400000	//[진성] 레어 소환인형 설정(사용: 1.수련장 등록 금지.) => 2008-7-15
#define ITEMINFOATB_NOTSHOW_MARKETCONFITIONS		0x800000	// 시세확인용  - 설정된 아이템은 시세확인에서 제외된다.
#define ITEMINFOATB_CRYSTAL_AVATAR					0x1000000	//[희영] 아바타 결정체 //KHY - 20090526 - 아바타 결정체.
#define ITEMINFOATB_SKILLBOOK						0x2000000	//[진성] 스킬 능력을 부여할 아이템.

class cltItemInfo{
	public:
		SI32	siType;
		SI32	siImageIndex;				// 장비창에 표시되는 큰 이미지의 인덱스.
		SI32	siSmallImageIndex;			// 땅위에 표시되는 작은 이미지의 인덱스. 
		SI32	siWeight;					// 아이템의 무게. 같은 유니크의 아이템은 무게가 모두 같다. 
		SI32	siSoundType;				// 효과음 연주를 위한 아이템 유형. 
		
		SI32	siItemGrade;				

		SI32	siItemInfoAtb;	
		cltItemSkillInfo	clSkillInfo;	// 생산에 필요한 기술 정보. 
		cltItemConition		clCondition;	// 장착에 필요한 조건. 

		SI32	siSetItemIndex;

		TCHAR szArmCode[24];				// 장착 상태의 코드 문자열 

	private:
		TCHAR	szName[MAX_ITEM_NAME_LENGTH];
		BOOL	m_bDormancy;				// 휴면계정 보상아이템 인지
	public:

		SI32 siNeedRank;		// 특정 신분 요구 조건( 기자 등..) 

		SI32 siDecDur;			// 내구도 감소 정도. 

		SI32 siUpgradeSkillUnique;		// 이 아이템이 향상 시켜주는 SKill 의 unique 값
		SI32 siUpgradeSkillType;		// 이 아이템이 향상 시켜주는 기술의 타입. 

		SI32 siExplainUnique;			// 설명 텍스트 유니크. 
		
		SI32 siAdapt;					// 아이템의 적용 대상. 
		
		bool bCanEquipSwitch;			// 장착 가능한 물품인가. 	
		
		// 무기류인 경우 
		SI32 siAttackRange;
		SI32 siDefaultHitRate;			// 기본 명중률(계산ㅇ 의한 명중률에 더해준다. 
		SI32 siAttackType;
		DWORD dwAttackInterval;			// 공격과 공격 사이의 시간(ms)

		// 음식류인 경우 
		SI32 siHungry;

		SI32 siHorseFoodSwitch;		// 말 먹이

		bool bFishingBaitSwitch;	// 낚시 미끼
		SI32 siOrg1Penalty;			// Org1(소화기관) 페널티. 
		SI32 siOrg2Penalty;			// Org2(순환기관) 페널티. 
		SI32 siOrg3Penalty;			// Org3(호흡기관) 페널티. 
		SI32 siOrg4Penalty;			// Org4(신경기관) 페널티. 

		// 약품류인 경우, 
		SI32 siLife;
		SI32 siMana;
		SI32 siDiseaseUnique;		// 질병 코드. 
		TCHAR szDiseaseName[128];	// 치료할 수 있는 질병의 이름. 
		TCHAR szDiseaseType[128];	// 치료할 수 있는 질병 타입의 이름. 
		SI32 siHealEft;				// 약의 효능. 

		// 책류인 경우, 
		SI32 siSkillUnique;
		SI32 siSkillLevelLimit;

		//---------------------
		// 부적인 경우 
		//---------------------
		SI32 siScrollAdaptAttach;	// 어떤 속성의 물품에 적용되는가?
		SI32 siScrollFunction;		// 부적의 기능. 
		SI32 siScrollAbility;		// 주문의 기능정도. 
		SI32 siScrollDecDuration;	// 소모 내구도. 
		SI32 siScrollMax;			// 능력의 최대 범위. 	
		
		//--------------------
		// 소환 인형인 경우, 
		//--------------------
		SI32 siMakeKind;			// 이 소환ㅇ 인형을 사용하면 어떤 몬이 소환되는가. 

		//-------------------
		// 가방인 경우 
		//-------------------
		SI32 BagUseItemType;		// 가방에 들어가는 아이템의 종류. 
		

		//-------------------
		// 어구인 경우, 
		//-------------------
		SI32 siFishClassification;

		//-------------------------------------------------------------------
		// 무역 서버에 올라가냐 안 올라가냐,올라간다면 최소 단위수는 뭐냐
		//-------------------------------------------------------------------
		SI32 siTradeServerMinNum; // 0이면 안 올라가는 거다

		//-------------------------------------------------------------------
		// 아이템 사용날짜가 랜덤하게 되지 않는것은 true
		//-------------------------------------------------------------------
		bool bImmutableUseDate;

		//-------------------------------------------------------------------
		//[진성] 통합마켓에 올라가냐.
		//-------------------------------------------------------------------
		bool m_bNewMarket; // 0이면 안 올라가는 거다

		//KHY - 0227 - 결정체 (크리스탈) 제조 추가. 
#ifdef _SAFE_MEMORY
		NSafeTArray<cltCrystalItemData, MAX_CAN_CRYSTALABILITY_NUM>		CrystalData;
#else
		cltCrystalItemData CrystalData[MAX_CAN_CRYSTALABILITY_NUM];
#endif

	public:
		TCHAR*			pszMaterialText; 
		TCHAR*			pszToolText;

		cltItemproductionInfo	clProductionInfo;	// 아이템 생산 정보. 

		cltItem clItem;

		cltItemInfo(SI32 imageindex, SI32 smallimageindex, TCHAR* name, SI32 sitype, SI32 weight,
					cltItemSkillInfo* pclskillinfo,cltItemConition* pclcondition, TCHAR* armcode, TCHAR* material,
					TCHAR* tool, SI32 productunit, SI32 soundtype, cltItem* pclItem ,SI32 Grade, SI32 TradeServerMinNum, cltCrystalItemData* CrystalItemData, bool bNewMarket, bool ImmutableUseDate = false);


		~cltItemInfo();

		const TCHAR* GetName()const{return szName;}
		void SetName(const TCHAR* pname)
		{
			MStrCpy(szName, pname, MAX_ITEM_NAME_LENGTH );
		}

		TCHAR* GetArmCode();

		// 재료를 분석한다. 
		bool AnalyzeMaterial(cltItemManagerCommon* pclItemManager);
			//도구를 분석한다. 
		bool AnalyzeTool(cltItemManagerCommon* pclItemManager);

		// 기술을 근거로 물품을 만들수 있는가 ?
		bool CanMake_Skill(cltPSkillInfo* pclskill, cltPItemInfo* pclcharitem, cltBasicAbility* pclBA);
		bool IsSkill_Maked();

		// 주어진  재료를 근거로 물품을 생산할 수 있는가?
		bool CanMake(SI32 materialnum,  cltItem* pclmaterialitem, cltItem* pclitem, SI32* producnum, SI32* preturnval, SI32* preturnpara1, bool bonlymaterialcheckswitch, BOOL bTutorialMake = FALSE,BOOL bUseQuestItem = FALSE ,cltMaterialInfo* clTutorialMaterial = NULL);

		// 주어진  재료를 근거로 물품을 생산할 수 있는가? 위치도 확인한다.
		bool CanMakeForServer(SI32 materialnum,  cltItem* pclmaterialitem, cltItem* pclitem, SI32* producnum, SI32* preturnval, SI32* preturnpara1, bool bonlymaterialcheckswitch, SI32* materialindex  , cltItem* pPersonShopItem, bool Check, BOOL bTutorialMake = FALSE,BOOL bUseQuestItem = FALSE ,cltMaterialInfo* clTutorialMaterial = NULL);


		const TCHAR* GetArmCode()const{return szArmCode;}

		// 최종 생산 확률을 구한다. 
		float GetTotalMakePbt(SI32 skilllevel);

		// 특정 속성이 아이템인포 속성인가. 
		bool IsItemInfoAtb(SI32 atb)
		{
			if(siItemInfoAtb & atb)return true;
			return false;
		}
		void DelItemInfoAtb(SI32 atb)
		{
			if(siItemInfoAtb & atb)
				siItemInfoAtb -= atb;
		}
		void AddItemInfoAtb(SI32 atb)
		{
			siItemInfoAtb |= atb;
		}
		
		bool IsThereMaterialAndTool(SI32 siUnique, SI32 *siCount)
		{
			
			for(SI32 i = 0; i < MAX_MATERIAL_NUMBER;i++)
			{
				SI32 unique = clProductionInfo.clMaterial[i].siUnique;
				SI32 num	= clProductionInfo.clMaterial[i].siNeedNum;
				
				if(unique <= 0)continue;
				if(num    <= 0)continue;

				if(siUnique == unique)
				{
					*siCount = num;
					return true;
				}
			}

			for(i = 0; i < MAX_TOOL_NUMBER;i++)
			{
				SI32 unique = clProductionInfo.clTool[i].siUnique;
			
				if(unique <= 0)continue;
				if(siUnique == unique)
				{
					*siCount = 0;
					return true;
				}
			}

			return false;
		}

		void SetDormancy(BOOL bDormancy)
		{
			m_bDormancy = bDormancy;
		}
		BOOL IsDormancy()
		{
			return m_bDormancy;
		}


		//------------------------------------------
		// 무기류인 경우, 
		//------------------------------------------
		void SetAttackRange(SI32 range){siAttackRange = range;}
		SI32 GetAttackRange()const{return siAttackRange;}

		void SetAttackInterval(DWORD interval){dwAttackInterval = interval;}
		DWORD GetAttackInterval(){return dwAttackInterval;}

		void SetAttackType(SI32 type){siAttackType = type;}
		SI32 GetAttackType()const{return siAttackType;}

		//------------------------------------------
		// 음식류인 경우, 
		//------------------------------------------
		void SetHungry(SI32 amount){siHungry = amount;}
		SI32 GetHungry()const{return siHungry;}

		//-----------------------------------------
		// 약품류인 경우, 
		//-----------------------------------------
		void SetLife(SI32 life){siLife = life;}
		SI32 GetLife()const{return siLife;}
		void SetDiseaseName(TCHAR* pname){StringCchCopy(szDiseaseName, 128, pname);}
		void SetDiseaseType(TCHAR* pDiseaseType){StringCchCopy(szDiseaseType, 128, pDiseaseType);}
		SI32 GetDisease()const{ return siDiseaseUnique;}

		void SetMana(SI32 mana){siMana = mana;}
		SI32 GetMana()const{return siMana;}

		//--------------------------------------
		// 책류인 경우, 
		//--------------------------------------
		void SetSkillUnique(SI32 unique){siSkillUnique = unique;}
		SI32 GetSkillUnique()const{return siSkillUnique;}
		void SetSkillLevelLimit(SI32 limit){siSkillLevelLimit = limit;}
		SI32 GetSkillLevelLimit()const{return siSkillLevelLimit ;}

		//--------------------------------------
		// 부적인 경우, 
		//--------------------------------------
		void SetScrollAdaptAttach(SI32 atc){siScrollAdaptAttach = atc;}
		void SetScrollFunction(SI32 function){siScrollFunction = function;}
		void SetScrollAbility(SI32 ability){siScrollAbility = ability;}
		void SetScrollDecDuration(SI32 dur){siScrollDecDuration = dur;}

		//--------------------------------------
		// 세트 아이템 처리
		//--------------------------------------
		void SetSetItemIndex( SI32 SetItemIndex ) {	siSetItemIndex = SetItemIndex; }
		SI16 GetSetItemIndex() { return siSetItemIndex; }

		bool IsImmutableUseDate()
		{
			return bImmutableUseDate;
		}


};

// 물품 통계 클래스. 
class cltItemStatistic{
public:

	GMONEY			siItemPriceIndex;		// 물가지수. 
	SI32			siNPCPriceRate;			// NPC의 거래 금 비율. 
	bool 		bLastNPCPriceRateDaySwitch;

#ifdef _SAFE_MEMORY
	// 아이템 거래량 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemTradeStatistic;
	// 아이템 사용량 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemUseStatistic;
	// 아이템 제작 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemMakeStatistic;

	// 아이템 분해(이호식) 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemTuneStatistic;
	// 아이템 분해(이호식)으로 나온 아이템 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemFromTuneStatistic;

	// 아이템 전리품 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemMonStatistic;
	// 아이템 장비 통계. 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemEquipStatistic;
	// 퀘스트 공급 물품 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemQuestStatistic;
	// 아이템몰 공급 물품 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemMallStatistic;
	// 생산술에 의한 아이템 물품 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemProductionStatistic;
	// 서버무역 아이템 물품 수입 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemWorldTradeIncomeStatistic;
	// 서버무역 아이템 물품 수출 통계 
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siItemWorldTradeExportStatistic;
	// 명나라 상인에 의한 거래
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siForeignMerchantStatistics;
	// 책상자에서 나온 아이템 통계
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siBookBoxStatistics;

	//[진성] 엘릭서 통계
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siElixirStatistics;
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siMagicalNostrumStatistics;

	//[진성] 아이템 등록, 아이템 거래, 아이템 시세.
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siNewMarketItemTradeStatistic;
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siNewMarketItemOrderStatistic;
	NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>		siNewMarketItemRateStatistic;
#else
	// 아이템 거래량 통계 
	SI32			siItemTradeStatistic[MAX_ITEMINFO_NUMBER];
	// 아이템 사용량 통계 
	SI32			siItemUseStatistic[MAX_ITEMINFO_NUMBER];
	// 아이템 제작 통계 
	SI32			siItemMakeStatistic[MAX_ITEMINFO_NUMBER];

	// 아이템 분해(이호식) 통계 
	SI32			siItemTuneStatistic[MAX_ITEMINFO_NUMBER];
	// 아이템 분해(이호식)으로 나온 아이템 통계 
	SI32			siItemFromTuneStatistic[MAX_ITEMINFO_NUMBER];

	// 아이템 전리품 통계 
	SI32			siItemMonStatistic[MAX_ITEMINFO_NUMBER];
	// 아이템 장비 통계. 
	SI32			siItemEquipStatistic[MAX_ITEMINFO_NUMBER];
	// 퀘스트 공급 물품 통계 
	SI32			siItemQuestStatistic[MAX_ITEMINFO_NUMBER];
	// 아이템몰 공급 물품 통계 
	SI32			siItemMallStatistic[MAX_ITEMINFO_NUMBER];
	// 생산술에 의한 아이템 물품 통계 
	SI32			siItemProductionStatistic[MAX_ITEMINFO_NUMBER];
	// 서버무역 아이템 물품 수입 통계 
	SI32			siItemWorldTradeIncomeStatistic[MAX_ITEMINFO_NUMBER];
	// 서버무역 아이템 물품 수출 통계 
	SI32			siItemWorldTradeExportStatistic[MAX_ITEMINFO_NUMBER];
	// 명나라 상인에 의한 거래
	SI32			siForeignMerchantStatistics[MAX_ITEMINFO_NUMBER];
	// 책상자에서 나온 아이템 통계
	SI32			siBookBoxStatistics[MAX_ITEMINFO_NUMBER];

	// 엘릭서
	SI32			siElixirStatistics[MAX_ITEMINFO_NUMBER];
	SI32			siMagicalNostrumStatistics[MAX_ITEMINFO_NUMBER];

	//[진성] 아이템 등록, 아이템 거래, 아이템 시세.
	SI32			siNewMarketItemTradeStatistic[MAX_ITEMINFO_NUMBER];
	SI32			siNewMarketItemOrderStatistic[MAX_ITEMINFO_NUMBER];
	SI32			siNewMarketItemRateStatistic[MAX_ITEMINFO_NUMBER];

#endif
	cltItemStatistic()
	{
		siItemPriceIndex	= 0;
		siNPCPriceRate		= 0;

		bLastNPCPriceRateDaySwitch = false;
			
		InitStatistic();
	}

	~cltItemStatistic()
	{
	}
	
    void InitStatistic() // 통계용 데이터만 초기화 한다.
	{
		// 아이템 통계 
		for(SI32 i = 0;i < MAX_ITEMINFO_NUMBER;i++)
		{
			siItemTradeStatistic[i] = 0;
			siItemUseStatistic[i]	= 0;
			siItemMakeStatistic[i]	= 0;
			siItemTuneStatistic[i]	= 0;
			siItemFromTuneStatistic[i]	= 0;
			siItemMonStatistic[i]	= 0;
			siItemEquipStatistic[i]	= 0;
			siItemQuestStatistic[i]	= 0;
			siItemMallStatistic[i]	= 0;
			siItemProductionStatistic[i] = 0;
			siItemWorldTradeIncomeStatistic[i] = 0;
			siItemWorldTradeExportStatistic[i] = 0;
			siForeignMerchantStatistics[i] = 0;
			siBookBoxStatistics[i] = 0;

		}
	}

};
class clMarketConditionsBasic{
public:
	SI16 		siItemUnique;					// 아에템 유니크.
	GMONEY		siItemMarketConditions;		// 시세.

	clMarketConditionsBasic()
	{
		ZeroMemory(this, sizeof(clMarketConditionsBasic));
	}

	~clMarketConditionsBasic()
	{
	}	
};

class clItemMarketConditions{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<clMarketConditionsBasic * , MAX_ITEM_UNIQUE> pclMarketConditionsB;
#else
	clMarketConditionsBasic * pclMarketConditionsB[MAX_ITEM_UNIQUE];
#endif

	_SYSTEMTIME		sTimeMarketConditions;

	clItemMarketConditions()
	{
		ZeroMemory(this, sizeof(clItemMarketConditions));
	}

	~clItemMarketConditions()
	{
	}
	

};




// 인챈트 통계 클래스. 
//MAX_ITEMGRADE
#ifdef MAKE_BY_MUNIN //2007-05-16, 06-05
class cltItemEnchantStatistic{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siGradeSucess;
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siGradeFail;
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siGradeDownGrade;
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siGradeBroken;

	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siEnchantMaterial_EM_F; //Fire Stone
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siEnchantMaterial_EM_WT; //Water Stone
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siEnchantMaterial_EM_WD; //Wind Stone
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siEnchantMaterial_EM_L;//Land Stone
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, MAX_ITEMGRADE>		siEnchantMaterial_BS; //Blessing Stone
#else
	SI32			siGradeSucess[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER];
	SI32			siGradeFail[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER];
	SI32			siGradeDownGrade[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER];
	SI32			siGradeBroken[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER];
	
	SI32			siEnchantMaterial_EM_F[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER]; //Fire Stone
	SI32			siEnchantMaterial_EM_WT[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER]; //Water Stone
	SI32			siEnchantMaterial_EM_WD[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER]; //Wind Stone
	SI32			siEnchantMaterial_EM_L[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER];//Land Stone
	SI32			siEnchantMaterial_BS[MAX_ITEMGRADE][MAX_ITEMINFO_NUMBER]; //Blessing Stone
#endif		
	

	cltItemEnchantStatistic()
	{
		InitEnchantStatistic();
	}

	void InitEnchantStatistic()
	{
		for(SI32 j = 0 ; j < MAX_ITEMGRADE; j++ )
		{
			// 인챈트 아이템 통계 
			for(SI32 i = 0;i < MAX_ITEMINFO_NUMBER;i++)
			{
				siGradeSucess[j][i] = 0;
				siGradeFail[j][i] = 0;	
				siGradeDownGrade[j][i] = 0;
				siGradeBroken[j][i] = 0;

				siEnchantMaterial_EM_F[j][i] = 0;
				siEnchantMaterial_EM_WT[j][i] = 0;
				siEnchantMaterial_EM_WD[j][i] = 0;
				siEnchantMaterial_EM_L[j][i] = 0;
				siEnchantMaterial_BS[j][i] = 0;				
			}
		}
	}

	~cltItemEnchantStatistic()
	{
	}
};
#else

class cltItemEnchantStatistic{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, 7>		siGradeSucess;
	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, 7>		siGradeFail;

	NSafeTArray< NSafeTArray<SI32, MAX_ITEMINFO_NUMBER>, 5>		siEnchantMaterial;
#else
	SI32			siGradeSucess[7][MAX_ITEMINFO_NUMBER];
	SI32			siGradeFail[7][MAX_ITEMINFO_NUMBER];

    SI32			siEnchantMaterial[5][MAX_ITEMINFO_NUMBER];
#endif

	cltItemEnchantStatistic()
	{
		for(SI32 j = 0 ; j < 7; j++ )
		{
			// 인챈트 아이템 통계 
			for(SI32 i = 0;i < MAX_ITEMINFO_NUMBER;i++)
			{
				siGradeSucess[j][i] = 0;
				siGradeFail[j][i] = 0;	
				
				if( j < 5 )
					siEnchantMaterial[j][i] = 0;

			}
		}
	}

	~cltItemEnchantStatistic()
	{
	}
};
#endif


//-------------------------------------
// 아이템 관리자. 
//-------------------------------------
#define RARE1_ITEM_RATE	200		// 호품
#define RARE2_ITEM_RATE	260		// 명품
#define RARE3_ITEM_RATE	150		// 고급품

class cltItemManagerCommon
{
public:
	// 서버 클라이언트 공용 부분 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemTypeInfo*, MAX_ITEMTYPE_NUMBER>	pclItemTypeInfo;
	NSafeTArray<cltItemInfo*, MAX_ITEMINFO_NUMBER>		pclItemInfo;
#else
	cltItemTypeInfo* pclItemTypeInfo[MAX_ITEMTYPE_NUMBER];
	cltItemInfo* pclItemInfo[MAX_ITEMINFO_NUMBER];
#endif
	cltItemPrice* pclItemPrice;
	cltItemPrice* pclItemNewPrice;
	
	//[진성] 세트 아이템의 능력치 정보.
	cltSetItemAbilityManager*	pcltSetItemAbilityManager;
	CSetItemManager*			pclSetItemManager;

	cltSkillBookManager*		pclSkillBookManager;
	// [성웅] 레벨 보상 상자에서 아이템을 준다 
	cltRewardItemForLimitLevel*	pclRewardItemLimitLevelForChina	;	// 중국레벨 보상 아이템

	// 물품 통계 정보. 
	cltItemStatistic clItemStatistic;
	bool m_bcheckcnppricerateswitch;	// 무수리 시세는 한번만 결정된다. 

	cltItemEnchantStatistic clItemEnchantStatistic;

	// [희영] 시세확인 2008-07-18 - 8일치를 저장한다.
#ifdef _SAFE_MEMORY
	NSafeTArray<clItemMarketConditions  *, 9> clMarketConditions;
#else
	clItemMarketConditions * clMarketConditions[9];
#endif

	NDataAtbParser  ItemInfoAtbParser;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_ITEM_UNIQUE>		ItemRef;
#else
	// ItemUnique를 근거로 수비게 Ref를 찾기 위한 변수. 
	SI16	ItemRef[MAX_ITEM_UNIQUE];
#endif
	
	// 아이템의 개수. (총 몇종의 아이템이 게임에 있는가 ?) 
	SI32	siItemNum;		
	
	bool bCanMakeRareItemSwitch;	// 명품을 만들 수 있는 모드인가. 
	DWORD dwLastMakeRareItemClock;	// 마지막으로 명품을 만든 시간. 

	//---------------------------------
	// 투자상담가의 변수
	//---------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<InvestmentLines, MAX_INVESTMENT_ITEM_NUMBER>	stInvestmentLines;
#else
	InvestmentLines stInvestmentLines[MAX_INVESTMENT_ITEM_NUMBER];
#endif

	//-----------------------------
	// TradeServer
	//-------------------------------
//	SI32		siTradeServerObejectRank[MAX_TRADESERVER_OBJECT_RANK]; // 무역시 참고할 등급의 폭


	//KHY - NPCRATE 확대 - 임시 코드
	SI32 ReadLastNPCRATE();
	void WriteLastNPCRATE(SI32 nowLastNpcrate);
public:

	virtual BOOL IsDialogMessage(MSG* pmsg){return FALSE;}
	virtual bool MakeRandItem(SI32 level, SI32 addrate, cltKindItemProbabilitySet* pclikinditem, cltItem* pclitem){return false;}
	virtual SI32 GetBitmapIndexFromBitmapName(TCHAR* bitmapname){return 0;}
	virtual BOOL GetExplain(cltItem* pclitem, TCHAR* ptext, bool numswitch = true, bool basicswitch = false, bool bcolorswitch = false, SI32 siKind = 0, bool bweightswitch = true ){return FALSE;}
	virtual BOOL GetProductionExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, TCHAR* ptext){return FALSE;}
	virtual void SetItemImageBigList(){};
	virtual void SetBitmapImage(){};
	virtual TCHAR* GetBitMapImageFileNamePointer(SI32 index){return NULL;}
	virtual HBITMAP MakeDDBFromDIB(HDC hdc, SI32 imageindex){return NULL;}
	virtual HBITMAP MakeDDBFromDIB(HDC hdc, TCHAR* path){return NULL;}
	virtual SI32 GetBitmapIndexFromFileName(const TCHAR* filename){return -1;}
	virtual void PushEffect(SI32 effect){}
	virtual void PlaySound(SI32 itemunique, SI32 type){};
    
	cltItemManagerCommon();
	virtual ~cltItemManagerCommon();

	void Create();

	BOOL SetItemType(SI32 siunique, SI64 siatb, SI64 siattach, const TCHAR* typecode, const TCHAR* pname);

	//-----------------------------------------------
	// cltItem-SetItemData.cpp
	//------------------------------------------------
	void SetItemData();
	// 아이템을 생산하기 위한 재료와 도구등을 설정한다. 
	void SetItemMaterial();

	void SetItemType();

	// 음식 아이템을 추가한다. 
	void AddFoodItem(TCHAR* datfilename);
	
	// 수산물아이템을 추가한다. 
	void AddSeaFoodItem(TCHAR* datfilename);


	// 약 아이템을 추가한다. 
	void AddHealItem(TCHAR* datfilename);
	// 칼 아이템을 추가한다. 
	void AddSwordItem(TCHAR* datfilename);
	// 창 아이템을 추가한다. 
	void AddSpearItem(TCHAR* datfilename);
	// 지팡이 아이템을 추가한다. 
	void AddStaffItem(TCHAR* datfilename);
	// 도끼 아이템을 추가한다. 
	void AddAxeItem(TCHAR* datfilename);
	// 활 아이템을 추가한다. 
	void AddBowItem(TCHAR* datfilename);
	// chd 아이템을 추가한다. 
	void AddGunItem(TCHAR* datfilename);
	// 갑옷 아이템을 추가한다. 
	void AddArmourItem(TCHAR* datfilename);
	// 의복 아이템을 추가한다. 
	void AddDressItem(TCHAR* datfilename);
	// 투구 아이템을 추가한다. 
	void AddHelmetItem(TCHAR* datfilename);
	// 요대 아이템을 추가한다. 
	void AddBeltItem(TCHAR* datfilename);
	// 목걸이 아이템을 추가한다. 
	void AddNeckItem(TCHAR* datfilename);
	// 신발 아이템을 추가한다. 
	void AddShoesItem(TCHAR* datfilename);
	// 책 아이템을 추가한다. 
	void AddBookItem(TCHAR* datfilename);
	// 동물 아이템을 추가한다. 
	void AddAnimalItem(TCHAR* datfilename);
	// 기타 아이템을 추가한다. 
	void AddEtcItem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	// 일반 아이템을 추가한다. 
	void AddItem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	// 반지 아이템을 추가한다. 
	void AddRingItem(TCHAR* datfilename);
	// 부적 아이템을 추가한다. 
	void AddScrollItem(TCHAR* datfilename);
	// 철물  아이템을 추가한다. 
	void AddIronItem(TCHAR* datfilename);
	// 도기  아이템을 추가한다. 
	void AddDishItem(TCHAR* datfilename);
	// 어구  아이템을 추가한다. 
	void AddFishingRodItem(TCHAR* datfilename);
	// 소환인형 아이템을 추가한다. 
	void AddDollItem(TCHAR* datfilename);
	// 모자 아이템을 추가한다. 
	void AddHatItem(TCHAR* datfilename);
	// 표아이템을 추가한다. 
	void AddTicketItem(TCHAR* datfilename);
	// 가방 아이템을 추가한다.
	void AddBagItem(TCHAR* datfilename);
	// 망토 아이템을 추가한다.
	void AddMantleItem(TCHAR* datfilename);

	// [지연] 아바타 망토 아이템을 추가한다.
	void AddAvatarMantleItem(TCHAR* datfilename);
	// [지연] 아바타 의복 아이템을 추가한다.
	void AddAvatarDressItem(TCHAR* datfilename);
	// [지연] 아바타 모자 아이템을 추가한다.
	void AddAvatarHatItem(TCHAR* datfilename);
	// [지연] 아바타 목걸이 아이템을 추가한다.
	void AddAvatarNeckItem(TCHAR* datfilename);
	// [지연] 아바타 반지 아이템을 추가한다.
	void AddAvatarRingItem(TCHAR* datfilename);

	// 문구 아이템을 추가한다. 
	void AddPaperItem(TCHAR* datfilename);
	// 대포 아이템을 추가한다. 
	void AddCannonItem(TCHAR* datfilename);
	// 어뢰 아이템을 추가한다. 
	void AddTorpedoItem(TCHAR* datfilename);
	// 결정체 아이템을 추가한다. 
	void AddCrystalItem(TCHAR* datfilename);
	//합성 재료 아이템을 추가한다
	void AddCompositionManterial(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//이벤트 아이템을 추가한다
	void AddEventitem(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//상자 아이템을 추가한다
	void AddBox(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//프리미엄 아이템을 추가한다
	void AddPremium(TCHAR* datfilename, TCHAR* pname, SI32 itemtype);
	//광석 아이템을 추가한다
	void AddMineralItem(TCHAR* datfilename);
    	
	void AddQuestItem(TCHAR* datfilename);
	//----------------------------------------
	// TradeServer
	//---------------------------------------
	void AddTradeServerRank(TCHAR *filename);
	SI16 GetTradeServerObjectRank(cltItem*pclitem); // 이 물품의 등급을 정한다.
	BOOL MakeTradeServerObjectForRank(cltItem*pclitem,SI16 unique,SI16 num ,SI16 rank,SI08 rare,SI16 type,SI16 power); // 무역을 받은 아이템을 만든다.
	
	// 아이템(약)과 치료할 수 있는 질병을 연결한다. 
	void ConnectDisease( cltDiseaseManager *pcldiseasemanager);

	// 아이템(약)과 치료할 수 있는 질병타입을 연결한다. 
	void ConnectDiseaseType( cltDiseaseManager *pcldiseasemanager);

	SI32 FindItemRefFromUnique(SI32 unique)
	{
		if(unique < 0)return 0;
		if(unique >= MAX_ITEM_UNIQUE)return 0;
		
		return ItemRef[unique];
	}

//	bool GetLimitDateItemValue(SI32 unique , SI32* usedate) ;

	// 아이템의 유니크를 근거로 아이템의 정보 포인터를 구한다.
	cltItemInfo* FindItemInfo(SI32 unique)
	{
		if(unique < 0)return 0;
		if(unique >= MAX_ITEM_UNIQUE)return 0;

		SI32 ref = FindItemRefFromUnique(unique);
		if(ref <= 0)return NULL;

		return pclItemInfo[ref];

	}

	// 아이템의 이름으로 아이템의 유니크 값을 구한다. 
	SI32 FindUniqueFromName(const TCHAR* pname);

	SI08 FindMakeAniTypeFromUnique(SI32 siUnique);
	SI08 FindEnchantAniTypeFromUnique(SI32 siUnique);

	SI32 FindRefFromStaticIndex(SI32*  pindex)
	{
		if(*pindex < 0)
		{
			*pindex	= 0;
			return 0;
		}
		if(*pindex >= MAX_ITEMINFO_NUMBER)
		{
			*pindex	= 0;
			return 0;
		}

		for(SI32 i = *pindex; i < MAX_ITEMINFO_NUMBER;i++)
		{
			if(pclItemInfo[i])
			{
				*pindex	= (i+1);
				return i;
			}
		}

		*pindex = 0;
		return 0;
	}

	// 아이템의 타입이름을 근거로 아이템타입의 유니크값을 구한다.
	SI32 FindItemTypeUniqueFromTypeName(const TCHAR* itemtypename);
	// 아이템의 타입코드를  근거로 아이템타입의 유니크값을 구한다.
	SI32 FindItemTypeUniqueFromTypeCode(const TCHAR* itemtypeCode);
	bool IsCanDropItem( SI32 siItemUniuqe);


	SI32 AddItem(SI32 imageindex, SI32 smallimageindex, TCHAR* name, SI32 sitype, SI32 weight,
				 cltItemSkillInfo* pclskillinfo, cltItemConition* pclcondition,
				 TCHAR* armcode, TCHAR* material, TCHAR* tool, SI32 productunit,
				 SI32 soundtype, cltItem* pclitem , SI32 Grade, SI32 MinNum, cltCrystalItemData *CrystalItemData, bool bSuperMaket, bool ImmutableUseDate = false);

	// 아이템의 적절한 위치인지 확인한다. 
	bool CheckProperItemPos(cltItem* pclItem, SI32 siDragFrom, SI32 siKind = 0);

	// siUnique아이템의 공격 사거리를 구한다. 
	SI32 GetAttackRange(SI32 siUnique);

	// 아이템의 시세를 설정한다. 
	void SetCurrentPrice(SI32 itemunique, GMONEY price, SI32 itemnum, bool bforceswitch = false);
	void SetCurrentNewPrice( SI32 itemunique, SI64 price, SI32 itemnum, bool bforceswitch = false );
	
	// 아이템의 시세를 얻어온다.
	cltItemPriceUnit* GetCurrentPrice(SI32 itemnunique);
	cltItemPriceUnit* GetCurrentNewPrice(SI32 itemnunique);
	
	SI32 GetItemGrade(SI32 ItemUnique);

	// Unique를 근거로 Atb를 구한다. 
	SI64 GetItemAtb(SI32 unique);
	
	//유니크를 근거로 타입을 구한다. 
	SI32 GetItemType(SI32 unique);

	// Unique를 근거로 Attach를 구한다. 
	SI64 GetItemAttach(SI32 unique);
	
	// 해당 Scroll 이 아이템에 붙일수 있는지 확인한다.
	BOOL CanItemAttach(SI32 scrollunique, SI32 tounique);

	// unique를 근거로 이름을 구한다. 
	const TCHAR* GetName(SI32 unique);
	
	// 이미지의 인덱스를 가져온다. 
	SI32 GetImage(SI32 siunique);

	// 아이템 장착 조건을 충족시키는지 확인한다. (사용자용) 
	bool CheckCondition(SI32 siitemunique, cltCharCommon* pclchar, SI32* returnval);
	// 아이템 장착 조건을 충족시키는지 확인한다. (소환수용) 
	//bool CheckCondition(SI32 siitemunique, cltSummon* pclsummon, SI32* returnval,SI32 addstr , SI32 adddex,SI32 addmag);
	// 소환수 아이템 장착 조건을 충족시키는지 확인한다
	bool CheckConditionForSummon( IN cltCharCommon* pclChar, IN SI32 siItemUnique, IN cltSummon *pclsummon, IN cltItem* pclItemList, OUT SI32 *psiReturnValue );
	// 소환수가 장착가능한 장비위치인지(소환수는 사람과 달리 아에 착용할수없는 장비 위치가 있다)
	bool IsCanEquipItemPosForSummon( SI32 siEquipPosition, SI32 siItemUnique );


	// iconcode를 근거로 
	SI32 FindBitmapIndex(TCHAR* typecode, TCHAR* iconcode);

	// 부적을 부착한다. 
	bool Enchant(cltItem* pclitem, SI32 scrollunique, SI32* prtnval, SI32* ppara1, SI32* ppara2);

	// 특정 물품을 특정 캐릭터가 만들때 품질 지수를 구한다. 
	SI32 GetQualityRate(SI32 itemunique, SI32 id, SI32* addlevel);
	
	// 교역 상인용 아이템 정보를 얻는다. 
	bool GetForeignNPCItemInfo(SI32 itemtype, SI32* punique, GMONEY* pprice, SI32* pitemnum);

	// 물품 시세를 조정한다. 
	void CalcItemPrice( _SYSTEMTIME sTime);
	
	// 아이템의 구리비를 구한다. 
	GMONEY GetNPCRepairPrice(cltItem* pclitem);

	// 캐릭터 kind를 근거로 소환 인형의 유니크를 구한다. 
	SI32 GetItemDollUnique(SI32 kind);

	// 매일 퀘스트의 보상으로 지급할 물품의 종류와 수량 확인. 
	bool GetDailyQuestRewardInfo(GMONEY money, SI32* pitemunique, SI32* pitemnum, GMONEY* prewardmoney );

	// 매일 퀘스트2의 보상으로 지급할 물품의 종류와 수량 확인. 
	//bool GetDailyQuest2RewardInfo( SI32* pitemunique, SI32* pitemnum, GMONEY* prewardmoney );
	bool GetDailyQuest2RewardInfo(GMONEY money, SI32* pitemunique, SI32* pitemnum, GMONEY* prewardmoney );

	//---------------------------------------------------------------------------------------------------
	// 데일리 퀘스트3 리스트 아이템 정보
	bool GetDailyQuest3KindInfo(SI16* pItemUnique,SI16* pMakeNum);
	// 매일 퀘스트3의 보상으로 지급할 물품의 종류와 수량 확인.
	bool GetDailyQuest3RewardInfo( SI32* siRewardExp, SI16 siMakeItemNum, SI16* pitemunique, SI16* pitemnum, SI32 SkillLevelLimit );
	//----------------------------------------------------------------------------------------------------
	// 혹부리(이호식)의 아이템 분해로 지급할 물품의 종류와 수량 확인. 
	bool GetWeenyOldManMaterialInfo(SI16 resolutionRate, SI32 disassembleItem, cltItem* pDisAssemitem);

	bool GetRareItemWithWeenyOld(cltItem *pclitem);

	SI16 GetWennyOldItem( cltItem* pclItem, SI16 *resolutionRate );

	// 건물 수리용 아이템을 구한다.
	bool GetItemForStrRepair(GMONEY strprice, SI32* pitemunique, SI32* pitemnum);
	
	//-------------------------------------
	// 아이템 통계 관련 
	//-------------------------------------
	//일정 주기마다 업데이트 되며 통계 기록에 관한 작업을 한다. 
	void WriteStatisticAction(_SYSTEMTIME sTime);
	//통계를 기록한다. 
	void WriteStatistic(TCHAR * filename );

	void WriteStatisticBackUp( TCHAR * filename, _SYSTEMTIME sTime );
	void ReadStatisticBackUp( TCHAR * filename, _SYSTEMTIME sTime );
    
	// 아이템 거래 통계를 낸다. 
	void AddTradeNum(SI32 itemunique, SI32 itemnum);
	// 아이템 사용 통계를 낸다. 
	void AddUseNum(SI32 itemunique, SI32 itemnum);
	// 아이템 제작 통계를 낸다. 
	void AddMakeNum(SI32 itemunique, SI32 itemnum);
	// 아이템 분해(이호식) 통계를 낸다. 
	void AddTuneNum(SI32 itemunique, SI32 itemnum);
	// 아이템 분해(이호식)으로 나온 아이템 통계를 낸다. 
	void AddFromTuneNum(SI32 itemunique, SI32 itemnum);
	// 전리품 아이템 통계를 낸다. 
	void AddWarItemNum(SI32 itemunique, SI32 itemnum);
	// 장비품의 통계를 낸다. 
	void AddEquipItemNum(SI32 itemunique, SI32 itemnum);
	// 퀘스트 공급 물품의 통계를 낸다. 
	void AddQuestItemNum(SI32 itemunique, SI32 itemnum);
	// 아이템몰에서 공급 물품의 통계를 낸다. 
	void AddMallItemNum(SI32 itemunique, SI32 itemnum);
	// 생산술에 의한 공급 물품의 통계를 낸다.
	void AddProductionItemNum(SI32 itemunique, SI32 itemnum);
	// 서버무역에 의한 수입물품의 통계를 낸다.
	void AddWorldTradeIncomeItemNum(SI32 itemunique, SI32 itemnum);
	// 서버무역에 의한 수출물품의 통계를 낸다.
	void AddWorldTradeExportItemNum(SI32 itemunique, SI32 itemnum);
	// 명나라 상인에 의해 사들여진 물품의 통계를 낸다.
	void AddForeignMerchantItemNum(SI32 itemunique, SI32 itemnum);
	// 책상자에 의해 나온 물품의 통계를 낸다.
	void AddBookBoxItemNum(SI32 itemunique, SI32 itemnum);

	// 엘릭서
	void AddElixirNum(SI32 itemunique, SI32 itemnum);
	void AddMagicalNostrumNum(SI32 itemunique, SI32 itemnum);


	//----------------------------------------------
	// 인챈트 통계 관련
	//----------------------------------------------

#if  MAKE_BY_MUNIN //2007-05-21
	void WriteEnchantStatisticAction(bool backUpEnchantDataLoaded  , _SYSTEMTIME sTime);
	void WriteEnchantStatistic( _SYSTEMTIME sTime );
	void AddEnchantNum(SI32 itemunique, SI32 ItemGrade, DBMaterialInfo* pclinfo,  SI32 sucess);
	void WriteEnchantStatisticBackUp( TCHAR * filename, _SYSTEMTIME sTime );
	void ReadEnchantStatisticBackUp( TCHAR * filename, _SYSTEMTIME sTime );
#else
	void WriteEnchantStatistic();
	void AddEnchantNum(SI32 itemunique, SI32 ItemGrade, DBMaterialInfo* pclinfo,  bool sucess);
#endif

	//------------------------------------
	// 개조 관련.
	//------------------------------------
	// 특정 아이템이 개조가능한 것인지 여부. 
	bool CanTune(cltItem* pclitem);

	// 개조후의 아이템으로 변경한다. 
	bool GetTuneItem(cltItem* pclitem,bool bSuccess = false,SI32 mode = 0 );

	// 장비품 성능 향상을 위한 부적 요구 정보를 구한다. 
	bool GetScrollForTune2(cltItem clitem, SI32* pscrollunique, SI32* pscrollnum, cltItem* pcldestitem, SI32* preturnval);

	//---------------------------------------------
	// 물품 생산 
	//---------------------------------------------

	//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 결정체 타입.
	void MakeCrystal(cltItem* pclitem, SI32 qualityrate);

	// 공격력을 부여한다. 
	void MakeApower(cltItem* pclitem, SI32 qualityrate);
	// 방어력을 부여한다. 
	void MakeDpower(cltItem* pclitem, SI32 qualityrate);
	
	// 물품의 내구도를 만든다. 
	void MakeDur(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforceswitch,SI32 durrate = 0,SI32 monstercorp = 0 );
	// 물품의 기간을 만든다.
	void MakeDate(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforceswitch,SI32 durrate = 0,SI32 monstercorp = 0 );

	// 아바타 물품의 기간을 만든다.
	void MakeAvatarDate(SI16* pbrareswitch, SI32 orgqualityrate, SI32 addlevel, cltItem* pclitem, bool bforceswitch,SI32 durrate = 0,SI32 monstercorp = 0 );

	// 고급품의 기간을 얻어온다. (랜덤)
	SI32 GetHighItemDate();

	// 물품의 기간을 확인한다.
	bool IsExpiredDate(cltItem* pclitem);


	// [추가 : 황진성 2008. 3. 3 => 아이템의 환원.]
	bool MakeItembyRestore( cltItem* pclEquipItem, cltItem* pclRestoreItem, cltCharCommon* pclchar );

	// 아이템의 Unique정보를 토대로 랜덤하게 아이템을 하나 만든다.
	bool MakeRandItemUnique(SI32 siunique, cltItem* pclitem,
		SI32 qualityrate, SI32 addlevel, SI16* pbrareswitch,
		SI32 attackrate = 0 ,SI32 magrate = 0 ,SI32 skillrate = 0, SI32 durrate = 0,
		SI32 monstercorp = 0 ,SI32 usedate = 0, SI32 enchanttype = 0, SI32 enchantlevel = 0, SI32 slotnum = 0, bool bSEQCreate = false);

	// 빈 아이템을 생성한다.
	bool MakeDefaultItem(SI32 siunique, SI32 itemnum, cltItem* pclitem);
	
	// 주어진 재료를 근거로 생산 가능한 아이템의 리스트를 작성해서 리턴한다. 
	// 얻어온 리스트는 사용후 삭제해 주어야 한다. 
	bool FindMakeableItem(cltPSkillInfo* pclskill, cltPItemInfo* pclcharitem, cltBasicAbility* pclBA, SI32 materialnum, cltItem pclmaterialitem[], SI32* pmakeableitemnum, SI32** ppitemlist, bool bonlymaterialcheckswitch);

	// 물품을 명품으로 만들어준다. 
	bool MakeRareItem(cltItem* pclitem,SI32 mode = 0);
	
	// 생산된 물품의 가격을 근거로 경험치를 구한다. 
	SI32 GetMakeExpFromItemPrice(GMONEY totalprice, SI32 level);

	// 생산된 물품의 가격을 근거로 경험치를 구한다. 
	SI32 GetMakeSkillExpFromItemPrice(GMONEY totalprice, SI32 skilllevel);

	// 특정 아이템이 누적 가능한가 ?
	bool CanPile(SI32 itemunique);
	
	// 만들 수 있는 물품인가 ?(원료가 존재하는 물품인가. ) 
	bool CanMakableItem(SI32 itemunique);

	// 투자상담가의 종목을 계산한다.
	void CalcInvestment(bool bStart);

	// 대박 전리품을 랜덤하게 얻어온다. 
	SI32 GetRandBigWarItem();
	// 대박 전리품을 랜덤하게 얻어온다. - 이호식
	SI32 GetRandBigWennyItem();
	// 대박 전리품을 랜덤하게 얻어온다. - 크리스마스
	SI32 GetRandBigChristmasItem();

	// 특정 물품이 대박 물품인가. 
	bool IsBigWarItem(SI32 itemunique);

	// 랜덤하게 아이템의 이름을 구한다. 
	const TCHAR* GetRandomItemName();
	//------------------------------------------------

	// 케릭터에 맞는 전용 쿠션 아이템을 알아온다.

	SI32 GetCushionUniqueFromCharKind(SI32 charkind);


	//------------------------------------------------
	//            인챈트  by tae-yang
	//------------------------------------------------
//	stEnchantNeed GetEnchantNeedItem(cltItem cltOrgItem, SI32 siSuccessUpItemNum = 0, BOOL bUseBlessingStone = FALSE, BOOL bUseSealingUpIgnore = FALSE );
	void GetEnchantNeedItem(cltItem cltOrgItem, stEnchantNeed* pclEnchantNeed, SI32 siSuccessUpItemNum = 0, BOOL bUseBlessingStone = FALSE, BOOL bUseSealingUpIgnore = FALSE );
	//SI32 GetGradeItem(cltItem cltOrgItem);
	//SI32 GetEnchantGrade(SI32 siEnchantDamage);
	//TCHAR* GetEnchantTypeName(TCHAR* szEnchantName, SI32 siEnchantType);
	SI32 GetEnchantDamageFromGrade(SI32 siGrade);


	// 농사 가능한 품목의 리스트를 얻는다. (plist를 할당하고 정보를 추가한후에 리턴한다.) 
	bool GetFarmItemList(SI32* pitemnum, SI32** plist);
	
	// 무역상인이 취급할 품목을 획득한다. 
	bool GetTraderItem(SI16* pitemunique, SI16* pitemnum, GMONEY* pitemprice);

	// 특정 속성이 아이템인포 속성인가. 
	bool IsItemInfoAtb(SI16 itemunique, SI32 atb);
	
	// 통합마켓에서 거래가 가능한가?
	bool IsNewMarketTrade(SI16 itemunique);

	// 농경을 통해서 얻을 수 있는 기술 경험치.  
	SI32 GetFarmSkillExp(SI32 itemunique);

	// 채광을 통해서 얻을 수 있는 기술 경험치.  
	SI32 GetMineSkillExp(SI32 itemunique);

	// 소환수 시전에서 먹을 먹이랑 경험치등등
	bool GetSummonFoodInfo(SI32* pitemunique,SI32* pitemnum,SI32* pexp,SI32* pskillexp);
	// 무장의 도력을 구한다. 
	SI32 GetEquipMag(cltItem* pclitemlist, SI16 activeweapon);
	// 무장의 도력을 구한다. 
	SI32 GetEquipMag(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar);
	// 무장의 근력을 구한다. 
	SI32 GetEquipStr(cltItem* pclitemlist , SI16 activeweapon);
	// 무장의 근력을 구한다. 
	SI32 GetEquipStr(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	// 무장의 순발력을 구한다. 
	SI32 GetEquipDex(cltItem* pclitemlist ,SI16 activeweapon);
	// 무장의 순발력을 구한다. 
	SI32 GetEquipDex(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	// 무장의 생명력을 구한다. 
	SI32 GetEquipVit(cltItem* pclitemlist ,SI16 activeweapon);
	// 무장의 생명력을 구한다. 
	SI32 GetEquipVit(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	// 무장의 운을 구한다. 
	SI32 GetEquipLuk(cltItem* pclitemlist ,SI16 activeweapon);
	// 무장의 운을 구한다. 
	SI32 GetEquipLuk(cltItem* pclitemlist, SI16 activeweapon,cltCharCommon* pclchar);
	// 무장의 손재주을 구한다. 
	SI32 GetEquipHnd(cltItem* pclitemlist ,SI16 activeweapon);
	// 무장의 손재주을 구한다. 
	SI32 GetEquipHnd(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	// 지혜를 구한다.
	SI32 GetEquipWis(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);

	// 무장의 공격타입을 구한다. 
	SI32 GetWeaponAttackType(cltItem* pclitemlist, SI16 activeweapon);
	// 무장의 사거리를 구한다. 
	SI32 GetWeaponAttackRange(cltItem* pclitemlist, SI16 activeweapon);
	// 무장의 공격 주기를 구한다. 
	SI32 GetWeaponAttackInterval(cltItem* pclitemlist, SI16 activeweapon);
	// 장비의 운을  구한다. 
	SI32 GetLuck(cltItem* pclitemlist);
	// 무장의 AC를 구한다. 
	SI32 GetAC(cltItem* pclitemlist);
	// 무장의 AC를 구한다. 
	SI32 GetAC(cltItem* pclitemlist, cltCharCommon* pclchar);

	// 인챈트의 AC 를 구한다 by tae-yang
	SI32 GetEnchantAC(cltItem* pclitemlist,cltCharCommon* pclchar );
	// 인챈트의 AC 를 구한다. server-attack.cpp 에서 계산하기 위해 
	SI32 GetEnchantACFrom(cltItem* pclitemlist, SI32 attacktype = ENCHANT_TYPE_DEFAULT);	
	// 인챈트의 Attack Damage 를 구한다. server-attack.cpp 에서 계산하기 위해 
	SI32 GetEnchantAttFrom(cltItem* pclitemlist, SI32 attacktype = ENCHANT_TYPE_DEFAULT);	

	// 무장의 최소 데미지를 구한다. 
	SI32 GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon);
	SI32 GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar);
	// 소환수의 최소 데미지를 구한다. 
	SI32 GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltSummon* pclsummon );
	// 무장의 최대 데미지를 구한다. 
	SI32 GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon);
	SI32 GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar);
	//소환수의 최대 대미지를 구한다.
	SI32 GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltSummon* pclsummon);

	// 무장의 인챈트 데미지를 구한다. by tae-yang
	//SI32 GetEnchantWeaponDamage(cltItem* pclitemlist, SI16 activeweapon);
	// 무장의 인챈트 타입을 구한다. 
	SI32 GetEnchantWeaponType(cltItem* pclitemlist, SI16 activeweapon);

	bool IsCheckSkill(cltItem clOutputItem, SI32 materialcharunique);

	// 장비에의한 기술 향상을 구한다. 
	SI32 GetUpgradeSkillLevel(cltItem* pclitemlist, SI32 skillunique, SI32 id = 0);
	// 장비의 필살률 향상을 구한다.   (무기에만) 
	SI32 GetEquipCriticalHitRate(cltItem* pclitemlist, SI16 activeweapon);
	// 장비의 명중률 향상을 구한다.  (무기에만)
	SI32 GetEquipHitRate(cltItem* pclitemlist, SI16 activeweapon);
	// 장비의 데미지 감소를 구한다. 
	SI32 GetDamageReduceRate(cltItem* pclitemlist);
	// 신발의 이동속도를 구한다. 
	SI32 GetMoveSpeed(cltItem* pclitemlist);
	// 신발의 이동속도를 구한다. 
	SI32 GetMoveSpeed(cltItem* pclitemlist, cltCharCommon* pclchar);

	// 아이템 이미지 정보를 얻어온다.
	bool GetItemGImageFileIndexAndFont( SI32 ItemUnique, SI32 *pGlobalImageIndex, SI32 *pGlobalImageFont );
	
	void GetItemImageItemmallFileName( SI32 siFromDBImgIndex, TCHAR* FileName, SI32 siLen , SI32* ImageIndex);		// [성웅] 아이템몰에 쓸 파일네임과 이미지 인덱스를 가지고 옵니다.
	void GetItemNameItemmallFileName( SI32 siFromDBImgIndex, TCHAR* FileName, SI32 siLen , SI32* ImageIndex);		// [성웅] 아이템몰에 쓸 파일네임과 이미지 인덱스를 가지고 옵니다.

	SI32 GetCompletedSetItemIndex( cltItem* pclitemlist );

	bool CheckCanPutonItem( SI32 unique );

	//KHY - 0115 발렌타인데이 이벤트. - 이벤트 아이템인지 찾는다.
	bool GetValentineEvent(SI32 siUnique);

	bool GetWhiteEvent(SI32 siUnique);

	//////////////////////////////////////////////////////////////////////////
	//KHY - 20090525 - 아바타 결정체. 아바타 결정체가  적용가능한  아이템인가.
	bool IsCrystalAbatarItem( SI32 siItemType );	
	bool IsAbatarCrystalItem( UI08 uiCrystalAbility );

	// 아바타의 종류에 따른, 능력치의 MAX 값을 구한다.
	SI32 GetMaxAbatarCrystalAbilityNum(SI32 siItemType , UI08 uiCrystalAbility);
	//////////////////////////////////////////////////////////////////////////
	
	enum SLOTITEMTYPE{	SLOTITEMTYPE_NONE, SLOTITEMTYPE_WEAPON, SLOTITEMTYPE_AVATAR, SLOTITEMTYPE_DORMANCY };
	
	// [추가 : 황진성 2008. 2. 29 => 슬롯을 사용하는 아이템인가.]
	SI32 UsedSlotItem(SI32 siUnique);		
	//////////////////////////////////////////////////////////////////////////
	// [지연 090507] - 아바타아이템타입인지 아닌지 비교.
	//enum ITEMTYPECOMPARE{	ITEMTYPE_AVATAR, ITEMTYPE_ETC 	};

	//-------------------------------------------------------------------------------------------------------------------
	//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 장비에 의한 향상분을 구한다. - 여기서 장비 구분 및 계산.
	SI32 GetCountEquipPersonitemAbility(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar  ,UI08 abilityType ,SI32 *ReturnValPer);

	//KHY - 0227 - 결정체 (크리스탈) 제조 추가. - 장비에 의한 마법력 향상분을 구한다.	
	// 무장의 최소 데미지를 구한다. 
	SI32 GetWeaponMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar , SI32 * CrystalPer);
	// 무장의 최대 데미지를 구한다. 
	SI32 GetWeaponMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar, SI32 * CrystalPer);

	SI32 GetAddMagicalDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar );
	SI32 GetAddMagicalMinDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar );
	SI32 GetAddMagicalMaxDamage(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar );

	SI32 GetEquipCrystalPhysicalHitRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalMagicalHitRate(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar);

	SI32 GetEquipCrystalPhysicalDefensiveRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar , SI32 * CrystalPer);
	SI32 GetEquipCrystalMagicalDefensiveRate(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar , SI32 * CrystalPer);

	SI32 GetEquipCrystalPhysicalDodgeRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalMagicalDodgeRate(cltItem* pclitemlist, SI16 activeweapon, cltCharCommon* pclchar);

	SI32 GetEquipCrystalHitpoint(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalManapoint(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalWeigt(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);


	SI32 GetEquipCrystalFireAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalWaterAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalWindAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalEarthAttack(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalFireDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalWaterDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalWindDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);
	SI32 GetEquipCrystalEarthDeffence(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar);

	SI32 GetEquipCrystalCriticalHitRate(cltItem* pclitemlist, SI16 activeweapon ,cltCharCommon* pclchar );

	bool CanRepairItem( cltItem* pclitem );
	bool IsRepairStone( cltItem* pclitem );
	bool IsRepairStone( SI32 siItemUnique );
	bool IsRepairExtraMaterial( cltItem* pclitem );
	GMONEY RepairPrice( cltItem* pclitem );

	bool CanMaxRepairItem( cltItem* pclitem );
	bool IsMaxRepairStone( cltItem* pclitem );
	bool IsMaxRepairStone( SI32 siItemUnique );
	
	SI16 NeedRepairStoneNum( cltItem* pclitem );
	SI16 NeedBlessingStoneNum( cltItem* pclitem, SI32 BlessingStoneUnique );
	//-------------------------------------------------------------------------------------------------------------------

	
	//아래 CanMixtureData()의 리턴 값들.
	enum
	{ 
		NO_ITEM_UNIQUE,					//													"장비나 결정체를 등록한 후 다시 시도해 주세요."
		NO_SLOT_ITEM,					// 슬롯이 있는 아이템이다.							"잘못된 아이템이 등록되 있습니다. 아이템을 확인해 주세요."
		NO_USED_SLOT,					// 사용 가능한 슬롯이 없다.							"장비의 결정체 슬롯을 모두 사용중입니다."					
		NO_CRYSTAL,						// 결합하고자 하는 아이템이 결정체가 아니다.		"잘못된 아이템이 등록되 있습니다. 아이템을 확인해 주세요."
		ALL_EMPTY_CRYSTAL,				// 결합하고자 결정체가 없다.						"잘못된 아이템이 등록되 있습니다. 아이템을 확인해 주세요."
		NO_REMOVE_CRYSTAL,				// 결정체 제거 아이템이 아니다.						"잘못된 아이템이 등록되 있습니다. 아이템을 확인해 주세요."
		NO_CRYSTAL_SLOT,				// 슬롯에 결정체가 없다.							"제거 하고자 하는 슬롯에 결정체가 존재하지 않습니다. 장비 다시 등록하여 시도해 주세요"
		USE_CRYSTAL_SLOT,				// 슬롯이 다 사용 중이다.							"모든 결정체 슬롯을 사용 중입니다."
		FULL_CRYSTAL_SLOT,  			// 슬롯이 모두 생성되있다.							"최대 슬롯이생성되어 있는 아이템입니다."
		ALREADY_USE_SLOT,				// 이미 사용중인 슬롯.								"이미 사용중인 슬롯 입니다."
		ALREADY_USED_INVEN_ITEM,		// 이미 자신의 인젠에서 사용중인 아이템.			"이미 결정체 슬롯에 추가된 아이템입니다. 다른 결정체를 등록하세요."
		SAME_CRYSTAL,					// 같은 결정체를 이미 가지고 있다.					"이미 같은 효과의 결정체가 있습니다. 다른 효과의 결정체를 등록하세요."
		LIMIT_LEVEL,					// 결정체를 조합할 장비가 레벨이 부족하다.			"장비가 레벨이 부족하여 결정체를 조합 할 수 없습니다."
		LIMIT_CRYSTAL_ABILITY,			// 결정체가 장비에 조합이 불가능한 능력을 지녔을때.	"이 결정체의 능력은 해당 장비에 조합이 불가능한 능력입니다."
		NO_RESTORE_ITEM,				// 환원할 수 없는 아이템.							"환원할 수 없는 아이템입니다."
		NO_RESTORE_ITEM_REGISTER,		// 환원할 아이템이 등록 안됨.						"환원할 아이템을 등록한 이후 다시 시도해 주세요."
		ALREADY_RESULT_RESTORE_ITEM,	// 환원한 아이템이 있어 수령해라.					"환원 결과 창에 있는 아이템을 수령한 후 다시 시도해 주세요."
		DIFFERENT_CRYSTAL,
		POSSIBLE,						// 결합 가능함.	
		NO_LOW_DURABILITY,			// 리차지 아이템으로, 내구도를 충전시킬 수 없다.(5이하)	"결정체의 최대 내구도가 낮아 내구도를 충전시킬 수 없습니다."
	};
	// [추가 : 황진성 2008. 2. 29 => 결정체 조합이 가능한 데이타 인가?.]
	BOOL CanCrystalMixtureData( cltItem* _EquipItem, cltItem* _CrystalItem , SI16 _EquipItemPos);		

	// [추가 : 황진성 2008. 2. 30 => 결정체 제거가 가능한 데이타 인가?.]
	BOOL CanCrystalRemoveData( cltItem* _EquipItem, bool* _RemoveSlot, cltItem* _CrystalItem);

	// [추가 : 황진성 2008. 2. 2 => 결정체로 슬롯 생성이 가능한 데이타 인가?.]
	BOOL CanCrystalSlotCreateData( cltItem* _EquipItem, cltItem* _CrystalItem );

	// [추가 : 황진성 2008. 2. 29 => 결정체가 장비에 조합이 가능한 능력인가?]
	bool IsMixtureAbilityType(cltItem* pclEquipItem, SI32 CristalItemAbilytype);
};


class cltItemPriceUnit{
public:
	SI16	siUnique;
	SI16	siItemNum;				// 대상이 되는 아이템의 개수. 
	GMONEY	siPrice;				// 거래된 가격. 
	REAL64	fPrice;					// 정밀가격. 
	GMONEY	siMarketOrderPrice;		// 객주 가격. 	
	
	cltItemPriceUnit()
	{
		siUnique			= 0;
		siPrice				= 0;
		fPrice				= 0.0f;
		siItemNum			= 0;
		siMarketOrderPrice	= 0;
	}
};

//------------------------------------------------
// 아이템 가격을 유지하는 클래스 
//------------------------------------------------
class cltItemPrice{
private:

public:
	cltItemManagerCommon*	pclItemManager;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemPriceUnit, MAX_ITEMINFO_NUMBER>	clUnit;
#else
	cltItemPriceUnit clUnit[MAX_ITEMINFO_NUMBER];
#endif

	cltItemPrice(cltItemManagerCommon* pclitemmanager);
	~cltItemPrice();


	// 아이템의 가격을 설정한다.
	void SetPrice(cltItemManagerCommon* pclitemmanager, SI32 unique, GMONEY price, SI32 itemnum, bool bforceswitch);
	// 아이템의 가격을 구한다. 
	cltItemPriceUnit* GetPrice(cltItemManagerCommon* pclitemmanager,SI32 unique);


	// 객주 주문가격을 설정한다. 
	void SetMarketOrderPrice(cltItemManagerCommon* pclitemmanager, SI32 unique, GMONEY price);

	// 객주 주문가격을 얻어온다. 
	GMONEY GetMarketOrderPrice(SI32 unique);

	
	// 특정 물품의 시세를 알려준다.(NPC용)
	GMONEY GetPriceSellToNPC(cltItemManagerCommon* pclitemmanager, SI32 unique);
};

//[진성] 호박상자에 렌덤하게 오픈된 아아템정보.
class AmberboxSelectItemInfo
{
public:
	UI08	m_siSlot;
	SI16	m_siItemNum;
	SI16	m_siItemUnique;

	AmberboxSelectItemInfo()
	{
		ZeroMemory(this, sizeof(AmberboxSelectItemInfo));
	}
};

//	[종호] 세트아이템 이펙트 단계
enum SETITEM_EFFECT_STEP
{
	SETITEM_EFFECT_NONE = 0,		//	nothing
	SETITEM_EFFECT_BASE_AURA,		//	바닥에 깔리는 타원형 이펙트
	SETITEM_EFFECT_SMALL_WIND,		//	작은 회오리
	SETITEM_EFFECT_LARGE_WIND,		//	큰 회오리
	SETITEM_EFFECT_END,
};

enum SETITEM_ABILITY_TYPE
{
	SETITEM_ABILITY_TYPE_EFFECT,						// 이펙트
	SETITEM_ABILITY_TYPE_ATTACK,						// 공격력 ( 데미지 ).
	SETITEM_ABILITY_TYPE_DEFENSIVE,						// 방어력.
	SETITEM_ABILITY_TYPE_STR,							// 힘
	SETITEM_ABILITY_TYPE_DEX,							// 순발력.
	SETITEM_ABILITY_TYPE_VIT,							// 생명력.
	SETITEM_ABILITY_TYPE_MAG,							// 마력.
	SETITEM_ABILITY_TYPE_HAND,							// 손재주.
	SETITEM_ABILITY_TYPE_LUK,							// 행운.
	SETITEM_ABILITY_TYPE_WIS,							// 지혜.
	SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE,		// 불 속성방어력..
	SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE,		// 물 속성방어력..
	SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE,		// 바람 속성방어력..
	SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE,		// 땅 속성방어력..
	SETITEM_ABILITY_TYPE_DRAIN_SUCCESS_PERCENT,			// 데미지로 에너지 뽑아내기 확률.
	SETITEM_ABILITY_TYPE_DRAIN,							// 데미지로 에너지 뽑아내기.
	SETITEM_ABILITY_TYPE_HIT_RATE,						// 명중률
	SETITEM_ABILITY_TYPE_WEAPON_USE_SKILL,				// 무기 사용술
	SETITEM_ABILITY_TYPE_HP,							// HP 증가
	SETITEM_ABILITY_TYPE_MP,							// MP 증가
	SETITEM_ABILITY_TYPE_CRITICAL,						// 크리티컬 증가 확률
	SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK,		// 공격시 상대를 얼려버리는 확률
	SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK,	// [지연] 공격시 상대를 중독시킬 확률
	SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK,			// 내가 얼음 공격을 당할 때 어는 확률
	SETITEM_ABILITY_TYPE_MAGIC_ATTACK,					// 마법 공격력 ( 데미지 ).
	SETITEM_ABILITY_TYPE_MAGIC_DEFENCE,					// [지연] 마법 방어력 ( 방어력 ).
	SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK,				// 선공방지
	SETITEM_ABILITY_TYPE_NATURE,						// 물리 속성 방어
	SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK,			// 불   속성 공격..
	SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK,			// 물   속성 공격력..
	SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK,			// 바람 속성 공격력..
	SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK,			// 땅   속성 공격력..
};

enum USE_SETITEM_NUM	// 사용 가능한 세트 아이템 개수.
{
	USE_SETITEM_1 = 1,
	USE_SETITEM_2,
	USE_SETITEM_3,
	USE_SETITEM_4,
	USE_SETITEM_5,
};

// [진성] 세트 아이템 능력치 정보.
class cltSetItemAbility
{
public:
	SI32	m_siEffect;					// 이펙트
	SI32	m_siAttack;					// 공격력 데미지.
	SI32	m_siDefensive;				// 방어력.
	SI32	m_siStr;					// 근력.	
	SI32	m_siDex;					// 순발력
	SI32	m_siVit;					// 생명력 
	SI32	m_siMag;					// 도력. 
	SI32	m_siHnd;					// 손재주. 
	SI32	m_siLuk;					// 행운. 
	SI32	m_siWis;					// 지혜. 
	SI32	m_siFireEnchantDefensive;	// 불   속성 방어력.
	SI32	m_siWaterEnchantDefensive;	// 물   속성 방어력.
	SI32	m_siWindEnchantDefensive;	// 바람 속성 방어력.
	SI32	m_siLandEnchantDefensive;	// 땅   속성 방어력.
	SI32	m_siDrainSuccessPercent;	// 데미지로 에너지 뽑아내기 확률.
	SI32	m_siDrain;					// 데미지로 에너지 뽑아내기.
	SI32	m_siHitRate;				// 명중률
	SI32	m_siWeaponUseSkill;			// 무기 사용술
	SI32	m_siHP;						// hp 변경
	SI32	m_siMP;						// mp 변경
	SI32	m_siCritical;				// 크리티컬
	SI32	m_siIceMagicTargetAttack;	// 공격시 상대를 얼려버리는 확률
	SI32	m_siPoisonMagicTargetAttack;// [지연] 공격시 상대를 중독 시킬 확률
	SI32	m_siIceMagicGetAttack;		// 내가 얼음 공격을 당할 때 어는 확률
	SI32	m_siMagicAttack;			// 마법 데미지
	SI32	m_siMagicDefence;			// [지연] 마법 방어력 (맞을때 데미지 10% 감소 즉, 마법 방어력 10% 증가)
	SI32	m_siNoFirstAttack;			// 선공방지
	SI32	m_siNature;					// 물리 속성 방어력.
	SI32	m_siFireEnchantAttack;		// 불   속성 공격력.
	SI32	m_siWaterEnchantAttack;		// 물   속성 공격력.
	SI32	m_siWindEnchantAttack;		// 바람 속성 공격력.
	SI32	m_siLandEnchantAttack;		// 땅   속성 공격력.

	

public:
	cltSetItemAbility()		{	ZeroMemory( this, sizeof(*this) );	}
	~cltSetItemAbility()	{	;									}

};

// [진성] 세트 아이템 능력치 정보 메니져.

enum
{
	VAMPIRE_SETITEM = 1,
	XMAS_SETITEM,
	GIRL_SULBIM_SETITEM,
	BOY_SULBIM_SETITEM,
	HALLOWEEN1_SETITEM,
	HALLOWEEN2_SETITEM,
	HALLOWEEN3_SETITEM,
	HALLOWEEN4_SETITEM,

	FROZEN_SETITEM_STEP,
	FLAME_SETITEM_STEP,
	DEMON_SETITEM_STEP,
	ABEL_SETITEM_STEP,
	BLACKKNIGHT_SETITEM_STEP,
	DEVIL_MAN,
	DEVIL_WOMAN,

	SETITEM_NUM
};

enum
{
	TWO_STEP = 2,
	THREE_STEP,
	FOUR_STEP,
	FIVE_STEP,
	SIX_STEP,
	SEVEN_STEP,

	MAX_STEP_NUM = 6	// 단계 수.
};


class cltSetItemAbilityManager
{
private:
	cltSetItemAbility	m_clSetItemAbility[ SETITEM_NUM ][ MAX_STEP_NUM ];

public:
	cltSetItemAbilityManager();
	~cltSetItemAbilityManager();

	void				Init( void );
	void				FileLoad( void );
	cltSetItemAbility*	GetSetItemAbility( SI16 _SetItemType );
	cltSetItemAbility*  GetSetItemAbilityData( cltCharCommon* _pclchar, SI32 _UseSetItem );
	SI32				GetSetItemAbilityValue( cltCharCommon* _pclchar, SI16 _siAbilityType, SI32 _UseSetItem );

	SI32				GetSetItemE( cltCharCommon* _pclchar, SI32 _UseSetItem );
	SI32				GetSetItemEffet( cltCharCommon* _pclchar, SI32 _UseSetItem );
	SI32				GetSetItemHumanEffect( cltCharCommon* _pclchar, SI32 _UseSetItem );
};

//-----------------------------------------
//  물품 생산에 필요한 재료 정보. 
//-----------------------------------------
class DBMaterialInfo{
public:
	SI16 siStgPos;		// 창고내 위치. 
	SI32 siItemUnique;	// 재료 아이템의 유니크 
	SI32 siUseItemNum;	// 사용되는 아이템의 개수. 

	DBMaterialInfo()
	{
		Init();
	}
	void Init()
	{
		siStgPos		= 0;
		siItemUnique	= 0;
		siUseItemNum	= 0;
	}

	void Set(DBMaterialInfo* pclinfo)
	{
		siStgPos		= pclinfo->siStgPos;
		siItemUnique	= pclinfo->siItemUnique;
		siUseItemNum	= pclinfo->siUseItemNum;
	}
};

//-----------------------------------------
//  물품 생산에 필요한 도구 정보. 
//-----------------------------------------
class DBToolInfo{
public:
	cltItem clItem;
	SI16	siPos;

	DBToolInfo()
	{
		siPos = 0;
	}
	void Init()
	{
		clItem.Init();
		siPos = 0;
	}
	void Set(DBToolInfo* pclinfo)
	{
		clItem.Set(&pclinfo->clItem);
		siPos	= pclinfo->siPos;
	}

	void Set( SI16 Pos, cltItem *pclItem )
	{
		clItem.Set( pclItem );
		siPos = Pos;
	}
};

#define REPAIRE_ITEM_EXTRAMATERIAL_COUNT 5
typedef NSafeTArray<DBMaterialInfo, REPAIRE_ITEM_EXTRAMATERIAL_COUNT> RepairItemExtraMaterial;





//[진성] 스킬북
#define SKILLBOOK_INFO_NUM	100

class cltSkillBookInfo
{
public:
	SI32	m_siItemUnique;				
	SI32	m_siMagicKind;			
	SI32	m_siMagicName;			
	SI32	m_siParentMagicKind;
	SI32	m_siImageNum;
	SI32	m_siTextNum;	
	SI32	m_siAttribute;	
	SI32	m_siBookGrade;
	SI32	m_siBookNum;	
	GMONEY  m_siCost;
};

// [진성] 스킬북
class cltSkillBookManager
{
public:
	enum ATTIRIBUTE
	{
		ATTRIBUTE_NONE,
		ATTRIBUTE_FIRE, 
		ATTRIBUTE_WATER, 
		ATTRIBUTE_EARTH, 
		ATTRIBUTE_WIND,

		ATTRIBUTE_NUM,
	};

	enum MAGIC_NAME
	{
		NONE,
		BUFTIMEINCREASE1,		//	버프마법 유지시간 10%증가
		BUFTIMEINCREASE2,		//	버프마법 유지시간 20%증가
		HITCOUNTINCREASE,		//	마법 유지회수 증가
		FREEZINGTIMEINCREASE,	//	빙결마법 빙결유지시간 증가
		ADDMAGIC,				//	특정 마법부여
		ATTINCREASE,			//	마법공격력 증가
		ATTINCREASE_CANE,		//	마법공격력 증가(지팡이)
		RANGEINCREASE,			//	마법사거리 증가
		COOLTIMEDECREASE,		// 마법 재사용시간 감소
		MPDECREASE,				// 소모되는 마나 감소
		ORGDECREASE,			// 소모되는 기관수치 감소

		MAGIC_NAME_NUM
	};

	enum BOOK_GRADE
	{
		BOOK_GRADE_NONE,
		BOOK_GRADE_BGN,		
		BOOK_GRADE_INT,		
		BOOK_GRADE_ADV,		
		
		BOOK_GRADE_NUM,
	};

public:
	cltSkillBookManager();
	~cltSkillBookManager();

	void		Init( void );
	void		FileLoad( void );

	SI32		GetSkillBookInfoNum( void );
	bool		IsSubMagicFromParentMagicKind( IN SI32 _siParentMagicKind );
	bool		GetSkillBookUniqueFromMagicKind( IN SI32 _siParentMagicKind, IN SI32 _siMagicKind, OUT SI32& _siItemUnique, OUT SI32& _siImageNum, OUT SI32& _siTextNum );
	bool		GetSkillBookUniqueFromParentMagicKind( IN SI32 _siParentMagicKind, OUT SI32& _siItemUnique, OUT SI32& _siImageNum, OUT SI32& _siTextNum );
	bool		GetSkillBookItemUniqueFromAttribute( IN SI32 _siAttribute, IN SI32 _siOutItemNum, OUT SI32* _siItemUnique );
	SI32		GetSkillBookMagicFromItemUnique( IN SI32 _siItemUnique );
	SI32		GetSkillBookParentMagicFromItemUnique( IN SI32 _siItemUnique );
	bool		GetSkillBookInfoFromAttribute( IN SI32 _siAttribute, IN SI32 _siOutNum, OUT cltSkillBookInfo* _pclSkillBookInfo );
	TCHAR*		GetGradeText( SI32 _siGrade );
	SI32		GetSkillBookGradeFromItemUnique( IN SI32 _siItemUnique );
	bool		IsSkillBookItemGrade( IN SI32 _siGrade, IN SI32 _siItemUnique );
	bool		IsSkillBookItem( IN SI32 _siItemUnique );

private:
	cltSkillBookInfo	m_clSkillBookInfo[SKILLBOOK_INFO_NUM];
	SI32				m_siSkillBookInfoNum;
};
// [성웅] 레벨 보상 상자에서 아이템을 준다 
#define MAX_REWARDITEMBOX_NUM	10	// 리소스에 가지고 있을수 있는 박스 아이템 총 갯수
#define TOTALITEMNUM_USELEVELLIMITBOX	5	// 한개의 박스에서 줄수 있는 아이템의 총 종류

class BoxData
{
public:
	SI32	siBoxitemunique	;
	SI32	siBoxiOpenLevel	;
	GMONEY	gRewardMoney	;
	SI32	siRewardTotalNum	;
	SI32	siRewardItemUnique_1	;
	SI32	siRewardItemNum_1	;
	SI32	siRewardItemUnique_2	;
	SI32	siRewardItemNum_2	;
	SI32	siRewardItemUnique_3	;
	SI32	siRewardItemNum_3	;
	SI32	siRewardItemUnique_4	;
	SI32	siRewardItemNum_4	;
	SI32	siRewardItemUnique_5	;
	SI32	siRewardItemNum_5	;
};

class cltRewardItemForLimitLevel	// 중국레벨 보상 아이템 
{
public:
	cltRewardItemForLimitLevel()	;
	~cltRewardItemForLimitLevel()	;

	// 박스 아이템 정보 저장 
#ifdef _SAFE_MEMORY
	NSafeTArray<BoxData, MAX_REWARDITEMBOX_NUM>		m_RewardITemBoxLinmitLevel_ForNHNChina;
#else
	BoxData  m_RewardITemBoxLinmitLevel_ForNHNChina[MAX_REWARDITEMBOX_NUM];
#endif
	void init()	;
	void LoadBoxInfo()	;							// 상자 정보를  읽어 들인다
	bool IsRewardBox_Unique( SI32 siItemUnique )	;
	SI32 GetOpenLevel( SI32 siItemUnique )	;
	SI32 GetTotalItemNum( SI32 siItemUnique )	;
	SI32 GetBoxUnique( SI32 siArray_Index )	;
};
#endif
