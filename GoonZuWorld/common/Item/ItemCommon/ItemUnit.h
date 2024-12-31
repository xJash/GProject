//---------------------------------
// 2003/5/20 ���°�
//---------------------------------

#ifndef _ITEMUNIT_H
#define _ITEMUNIT_H

#include "../../../Lib/Directives.h"
#include "../../../../NLib/NArray.h"
#include "../../GoonZuWorld/common/Skill/Skill.h"

#include "../../../GMSystem/GMSectionData.h"

#define  MAX_DURABILITY_PERCENT_IN_CHINA	100

//-------------------------------
// ������ Ÿ�� ����ũ .
//-------------------------------
#define ITEMTYPE_SWORD			1
#define ITEMTYPE_SPEAR			2
#define ITEMTYPE_AXE			3
#define ITEMTYPE_BOW			4
#define ITEMTYPE_GUN			5

#define ITEMTYPE_STAFF			6
#define ITEMTYPE_HELMET			7
#define ITEMTYPE_ARMOUR			8
#define ITEMTYPE_BELT			9
#define ITEMTYPE_SHOES			10

#define ITEMTYPE_NECK			11
#define ITEMTYPE_RING			12
#define ITEMTYPE_BAG			13
#define ITEMTYPE_HAT			14
#define ITEMTYPE_DRESS			15

#define ITEMTYPE_MANTLE			16
#define ITEMTYPE_FOOD			17
#define ITEMTYPE_HEAL			18
#define ITEMTYPE_BOOK			19
#define ITEMTYPE_BOX			20	// ������Ÿ�� �߰� �ڽ�������

#define ITEMTYPE_MINERAL		21	
#define ITEMTYPE_TREE			22

#define ITEMTYPE_CLOTH			23
#define ITEMTYPE_SEAFOOD		24
#define ITEMTYPE_CRYSTAL		25	// ������Ÿ�� �߰� ��Ƽ��Ʈ ����ü.

#define ITEMTYPE_COMPOSITIONMATERIAL		26	// ������Ÿ�� �߰� ��Ƽ��Ʈ �ռ�����
#define ITEMTYPE_PAPER			27
#define ITEMTYPE_IRON			28
#define ITEMTYPE_DISH			29
#define ITEMTYPE_FISHINGROD		30

#define ITEMTYPE_DOLL			31
#define ITEMTYPE_ANIMAL			32
#define ITEMTYPE_TICKET			33
#define ITEMTYPE_PREMIUM		34	// ������Ÿ�� �߰� �����̾�������.
#define ITEMTYPE_EVENTITEM		35	// ������Ÿ�� �߰� �̺�Ʈ ������

#define ITEMTYPE_ETC			36
#define ITEMTYPE_SCROLL			37
#define ITEMTYPE_QUEST			38
#define ITEMTYPE_CANNON			39	// �������� ��� ����
#define ITEMTYPE_TORPEDO		40	// ��� ���� ��� ����

#define ITEMTYPE_AVATAR_MANTLE	41	// [����] �ƹ�Ÿ ����
#define ITEMTYPE_AVATAR_DRESS	42	// [����] �ƹ�Ÿ �Ǻ�
#define ITEMTYPE_AVATAR_HAT		43	// [����] �ƹ�Ÿ ����
#define ITEMTYPE_AVATAR_NECK	44	// [����] �ƹ�Ÿ �����
#define ITEMTYPE_AVATAR_RING	45	// [����] �ƹ�Ÿ ����

//���� ������Ÿ��
//#define ITEMTYPE_SWORD			1
//#define ITEMTYPE_SPEAR			2
//#define ITEMTYPE_STAFF			3
//#define ITEMTYPE_AXE			4
//#define ITEMTYPE_BOW			5
//#define ITEMTYPE_GUN			6
//#define ITEMTYPE_CANNON			7
//#define ITEMTYPE_ARMOUR			8
//#define ITEMTYPE_DRESS			9
//#define ITEMTYPE_NECK			10
//#define ITEMTYPE_RING			11
//#define ITEMTYPE_BELT			12
//#define ITEMTYPE_SHOES			13
//#define ITEMTYPE_HELMET			14
//#define ITEMTYPE_HAT			15
//#define ITEMTYPE_FOOD			16
//#define ITEMTYPE_SEAFOOD		17
//#define ITEMTYPE_HEAL			18
//#define ITEMTYPE_BOOK			19
//#define ITEMTYPE_MINERAL		20
//#define ITEMTYPE_ANIMAL			21
//#define ITEMTYPE_TREE			22
//#define ITEMTYPE_PAPER			23
//#define ITEMTYPE_CLOTH			24
//#define ITEMTYPE_SCROLL			25
//#define ITEMTYPE_ETC			26
//#define ITEMTYPE_IRON			27
//#define ITEMTYPE_DISH			28
//#define ITEMTYPE_FISHINGROD		29
//#define ITEMTYPE_DOLL			30
//#define ITEMTYPE_TICKET			31
//#define ITEMTYPE_BAG			32
//#define ITEMTYPE_MANTLE			33
//#define ITEMTYPE_TORPEDO		34
//#define ITEMTYPE_QUEST			35
//#define ITEMTYPE_CRYSTAL		36	// ������Ÿ�� �߰� ��Ƽ��Ʈ ����ü.
//#define ITEMTYPE_COMPOSITIONMATERIAL		37	// ������Ÿ�� �߰� ��Ƽ��Ʈ �ռ�����
//#define ITEMTYPE_EVENTITEM		38	// ������Ÿ�� �߰� �̺�Ʈ ������
//#define ITEMTYPE_BOX		39	// ������Ÿ�� �߰� �ڽ�������
//#define ITEMTYPE_PREMIUM		40	// ������Ÿ�� �߰� �����̾�������.
//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
#define MAX_CRYSTAL_NUM		5	// �����۴� �ִ� ���Լ�.
#define MAX_CAN_CRYSTALABILITY_NUM		6	// �� �����۴� ������ �ִ� �ɷ��� ������.

#define CRYSTAL_DECREASE_DURABILITY_PRO		15	// �������� ���� Ȯ��. 
#define CRYSTAL_DECREASE_DURABILITY_ACNUM		1	// �չ��� ���̴� ������ �� - ����.
#define CRYSTAL_DECREASE_DURABILITY_MKNUM		10	// �չ��� ���̴� ������ �� - ����.


//�ռ����
#define	MAX_COMPOSISTINMANTERIAL_LEVEL	6	//�ִ� �ռ����� ���

//[�߰� : Ȳ���� 2008. 3. 3 => �������� ȯ���Ǵ� �������� �ִ� ����.]
#define MAX_RESTORE_ITEM_NUM		5	

#define CRYSTALTYPE_RUBY				1	//���
#define CRYSTALTYPE_TOPAZ				2	//������ 
#define CRYSTALTYPE_VIOLETQUARTZ		3	//�ڼ���
#define CRYSTALTYPE_DIAMOND			4	//���̾Ƹ��
#define CRYSTALTYPE_PEARL				5	//����
#define CRYSTALTYPE_SAPPHIRE			6	//�����̾�
//-----------------------------------------------
#define MAX_CRYSTALABILITY_NUM							68	// 20080228 - 56���� �ɷ� �����.

#define CRYSTALABILITY_STATE_STR						1	//�ٷ�.
#define CRYSTALABILITY_STATE_DEX						2	//���߷�.
#define CRYSTALABILITY_STATE_MAG						3	//����
#define CRYSTALABILITY_STATE_VIT						4	//�����.
#define CRYSTALABILITY_STATE_LUK						5	//���.
#define CRYSTALABILITY_STATE_HND						6	//������.

//#define CRYSTALABILITY_EFFECT_DMG						7	// ���ݷ�  - �ִ�, �ּ� ������.
//#define CRYSTALABILITY_EFFECT_AC						8	// ����  
//#define CRYSTALABILITY_EFFECT_AC						9	// ü��  
//#define CRYSTALABILITY_EFFECT_AC						10  // ������  
//#define CRYSTALABILITY_EFFECT_DR						11  // ȸ����  
//#define CRYSTALABILITY_EFFECT_AR						12  // ����  

#define CRYSTALABILITY_SKILL_SUMMON						13  // ��ȯ��.
#define CRYSTALABILITY_SKILL_FARM						14  // ����.
#define CRYSTALABILITY_SKILL_MINE						15  // ä����
#define CRYSTALABILITY_SKILL_FISH						16  // ��ȹ��.
#define CRYSTALABILITY_SKILL_MAKEFOOD					17  // �丮��.
#define CRYSTALABILITY_SKILL_CAPTURE					18  // ��ȹ��.
#define CRYSTALABILITY_SKILL_HORSETRAINING				19  // Ż�� ���ü�.

#define CRYSTALABILITY_SKILL_MAKEIRON1					20  // ö�����ۼ�
#define CRYSTALABILITY_SKILL_MAKETOOL1					21  // ���굵�����ۼ�
#define CRYSTALABILITY_SKILL_MAKEMED					22  // ��������
#define CRYSTALABILITY_SKILL_MAKESWORD1					23  // ��������
#define CRYSTALABILITY_SKILL_MAKESPEAR1					24  // â������
#define CRYSTALABILITY_SKILL_MAKEAXE1					25  // ����������
#define CRYSTALABILITY_SKILL_MAKESTAFF1					26  // ������������
#define CRYSTALABILITY_SKILL_MAKEBOW1					27  // Ȱ������
#define CRYSTALABILITY_SKILL_MAKEGUN1					28  // ��������
#define CRYSTALABILITY_SKILL_MAKEARMOUR1				29  // ����������
#define CRYSTALABILITY_SKILL_MAKEHELMET1				30  // ����������
#define CRYSTALABILITY_SKILL_MAKESHOES1					31  // �Ź�������
#define CRYSTALABILITY_SKILL_MAKEBELT1					32  // �㸮��������

#define CRYSTALABILITY_SKILL_USESWORD1					33  // �˼�
#define CRYSTALABILITY_SKILL_USESPEAR1					34  // â��
#define CRYSTALABILITY_SKILL_USEAXE1					35  // ������
#define CRYSTALABILITY_SKILL_USESTAFF1					36  // �����̼�
#define CRYSTALABILITY_SKILL_USEBOW1					37  // �ü�
#define CRYSTALABILITY_SKILL_USEGUN1					38  // �Ѽ�

// ���� �߰�
#define CRYSTALABILITY_STATE_WIS						39  // ����

#define CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK			40  // ���� ���ݷ�
#define CRYSTALABILITY_EFFECT_MAGICAL_ATTACK			41  // ���� ���ݷ�
#define CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE			42  // ���� ���߷�
#define CRYSTALABILITY_EFFECT_MAGICAL_HITRATE			43  // ���� ���߷�
#define CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE		44  // ���� ȸ����
#define CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE			45  // ���� ȸ����
#define CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE	46  // ���� �����
#define CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE		47  // ���� �����
#define CRYSTALABILITY_EFFECT_HITPOINT					48  // ü��
#define CRYSTALABILITY_EFFECT_MANAPOINT					49  // ������
#define CRYSTALABILITY_EFFECT_WEIGHT					50  // ���Է�

#define CRYSTALABILITY_ATTRIBUTE_FIREATTACK				51  // �� �Ӽ� ���ݷ�
#define CRYSTALABILITY_ATTRIBUTE_WATERATTACK			52  // �� �Ӽ� ���ݷ�
#define CRYSTALABILITY_ATTRIBUTE_WINDATTACK				53  // �ٶ� �Ӽ� ���ݷ�
#define CRYSTALABILITY_ATTRIBUTE_EARTHATTACK			54  // �� �Ӽ� ���ݷ�
#define CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE			55  // �� �Ӽ� ����
#define CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE			56  // �� �Ӽ� ����
#define CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE			57  // �ٶ� �Ӽ� ����
#define CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE			58  // �� �Ӽ� ����

//<---���� �߰� �ʿ��� -->


#define CRYSTALABILITY_SKILL_ALLMAKESKILL					59	//��� ���� ��ų.
#define CRYSTALABILITY_SKILL_ALLWEAPONSKILL					60	//��� ���� ��ų.
#define CRYSTALABILITY_SKILL_ALLPRODUCTSKILL				61	//��� ���� ��ų.
#define CRYSTALABILITY_SKILL_ALLSKILL						62	//��� ��ų.

#define CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK			63  // �ּ� ���� ���ݷ�
#define CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK			64  // �ִ� ���� ���ݷ�
#define CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK			65  // �ּ� ���� ���ݷ�
#define CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK			66  // �ִ� ���� ���ݷ�

#define CRYSTALABILITY_SKILL_ARTIFACT						67  // ��Ʈ��Ʈ ������.
#define CRYSTALABILITY_SKILL_ALLAVATARSKILL				68	//��� �ƹ�Ÿ ��ų.

//------���� �̱���-----------------------------------------
#define CRYSTALABILITY_SPECIAL_FISHING						70 // ����		
#define CRYSTALABILITY_SPECIAL_MINING						71 // ä��		
#define CRYSTALABILITY_SPECIAL_FARMING						72 // ���		
#define CRYSTALABILITY_SPECIAL_FREEZE						74 // �õ�		
#define CRYSTALABILITY_SPECIAL_HITRATE						75 // ����		
#define CRYSTALABILITY_SPECIAL_VAMPIRE						76 // ����		
#define CRYSTALABILITY_SPECIAL_IRONARMOR					77 // ö��		
#define CRYSTALABILITY_SPECIAL_DEATHBLOW					78 // �ʻ�	 - ����	
#define CRYSTALABILITY_SPECIAL_POISONING					79 // �ߵ�	
//-----------------------------------------------

// [����] �ƹ�Ÿ ����ü. - ��ȣ�� ������ �ٲ㼭�� �ȵȴ�. - Ȥ�ó� ���� �ƹ�Ÿ Ÿ���� �߰� �ϰ� �ȴٸ�, GetCountEquipPersonitemAbility �� ���ʰ�.
#define CRYSTALABILITY_AVATAR_STATE_STR						80	// [����] �ƹ�Ÿ ����ü. �ٷ�.
#define CRYSTALABILITY_AVATAR_STATE_DEX						81	// [����] �ƹ�Ÿ ����ü. ���߷�.
#define CRYSTALABILITY_AVATAR_STATE_MAG						82	// [����] �ƹ�Ÿ ����ü. ����
#define CRYSTALABILITY_AVATAR_STATE_VIT						83	// [����] �ƹ�Ÿ ����ü. �����.
#define CRYSTALABILITY_AVATAR_STATE_LUK						84	// [����] �ƹ�Ÿ ����ü. ���.
#define CRYSTALABILITY_AVATAR_STATE_HND						85	// [����] �ƹ�Ÿ ����ü. ������.
#define CRYSTALABILITY_AVATAR_STATE_WIS						86	// [����] �ƹ�Ÿ ����ü. ����.
#define CRYSTALABILITY_AVATAR_ALLMAKESKILL					87	// [����] �ƹ�Ÿ ����ü. ������.
#define CRYSTALABILITY_AVATAR_ALLWEAPONSKILL				88	// [����] �ƹ�Ÿ ����ü. �����.
#define CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL				89	// [����] �ƹ�Ÿ ����ü. �����.
#define CRYSTALABILITY_AVATAR_SKILL_ALLAVATARSKILL					90	//��� �ƹ�Ÿ ��ų.

//-----------------------------------------------

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

#define ITEMATB_TRADESERVER		0x100000000
#define ITEMATB_HIDECOMBOLIST	0x200000000

//������ �� �߰�.
#define ITEMATB_CRYSTAL				0x10000000000
#define ITEMATB_COMPOSITIONMATERIAL	0x20000000000
#define ITEMATB_EVENTITEM			0x40000000000
#define ITEMATB_BOX					0x80000000000
#define ITEMATB_PREMIUM				0x100000000000

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
//#define ITEMATTACH_ATIFACT	(1<<17)	// ��Ƽ��Ʈ 



#define MAX_PARTYHALL_APPLICATION_LIST	20		//[����] ��ƼȦ. ���� ��û�� �ִ��.
#define MAX_PARTYHALL_DECORATION_ITEM	20		//[����] ��ƼȦ. ��Ŀ� �������� �ִ��.
#define MAX_ITEM_PER_PERSON				80		// by LEEKH - ĳ������ ������ ���� ��� : ��ȯ��X2 ���� ���� ����
#define MAX_SHAPE_ITEM					15		// ��ȯ���� ��񰡴��� ��ǰ�� ��. 	
#define MAX_INVITEM_PER_PERSON			64		// ����� ���� ��� �κ� �հ�. 
#define MAX_ITEM_PER_INVENTORY			20
#define MAX_ITEM_PER_BAG				12		// ����
#define MAX_ITEM_PER_WENNYOLD			20
#define MAX_ITEM_SPACE_BOX				32		//[�߰� : Ȳ���� 2008. 1. 29 => ���� ����	    �ִ� ������ ��.]
#define MAX_ITEM_TREASURE_BOX			32		//[�߰� : Ȳ���� 2008. 1. 29 => ���� ����(����) �ִ� ������ ��.]
#define MAX_ITEM_ARTIFACT				5		//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ȯ�� �� �������� �ִ� ��.]
#define MAX_ITEM_ARTIFACT_MIXTURE		5		//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���յǴ� �������� �ִ� ��.]

#define WENNYMSG_SMALL			1		// 30~49%
#define WENNYMSG_MEDIUM			2		// 50~69%
#define WENNYMSG_LARGE			3		// 70~89%
#define WENNYMSG_DOUBLE			4		// 200%
#define	WENNYMSG_BOX			5		// ��ȣ�� ����
#define WENNYMSG_NECKLACE		6		// �����
#define WENNYMSG_NONE			7		// �ƹ��͵� ������ ����
#define WENNYMSG_FAILED			8		// �ٸ� ������ ���� ����
#define WENNYMSG_WENNYMATERIAL	9		// ��ȣ�� ���� �������� ����
#define WENNYMSG_GACHARARE		10		// ��í �������� ������������ ����
#define WENNYMSG_VAlENTINEITEM	11		// �߷�Ÿ�� ������.
#define WENNYMSG_WHITEITEM		12		// ȭ��Ʈ���� ������.
#define WENNYMSG_DAILYQUEST3	13		// �߷�Ÿ�� ������.
#define WENNYMSG_REPAIR_DUR		14		// ������ ������ ����
#define WENNYMSG_FORTUNE_COOKIE	15		// ������Ű ���� ����.

//cyj  ��ø�Ǵ� ������ ���� 1000���� ����
//#define MAX_ITEM_PILE_NUMBER	10000				// �Ѱ��� �����۾ȿ� ��ø�� �� �ִ� �������� ����. 
#define MAX_ITEM_PILE_NUMBER	10000				// �Ѱ��� �����۾ȿ� ��ø�� �� �ִ� �������� ����. 
#define DEFAULT_EQUIP_BULLET_NUMBER	500				// ȭ�� �� źȯ�� ���� ���ɰ��� ����
#define UPGRADE_EQUIP_BULLET_NUMBER 1000			// źȯ���� ���� ���� ���� ����

//#define MAX_DURABILITY			1000	// ������ �������� �ִ밪. 
//#define FOREVER_DURABILITY		1001	// �������� �Ҹ���� �ʴ� ����. 	
//#define FOREVER_DURABILITY2		1002	// �������� �Ҹ���� �ʴ� ����(�Ⱓ�� ������)

#define SELECTED_HUMAN			-1	// ������ ����â�� ����� ���õǾ���

#define EQUIPSET_PERSON				1
#define EQUIPSET_SUMMON1			2
#define EQUIPSET_SUMMON2			3
#define EQUIPSET_SUMMON3			4

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
#define PERSONITEM_BAG_SUB		13
#define PERSONITEM_RESERVED1	14


#define PERSONITEM_INV0			15
#define PERSONITEM_INV1			16
#define PERSONITEM_INV2			17
#define PERSONITEM_INV3			18
#define PERSONITEM_INV4			19
#define PERSONITEM_INV5			20

#define PERSONITEM_NONE         25

#define PERSONITEM_HORSE0		35

#define PERSONITEM_BAG0			55
#define PERSONITEM_BAG1			67

//#define PERSONITEM_SUMMON1EQUIP0	80

//#define PERSONITEM_SUMMON2EQUIP0	95

//#define PERSONITEM_SUMMON3EQUIP0	110



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
//cyj �������ۼ� ���� #define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING		20		// ���������� ��� 
#define SCROLL_UNIQUE_FUNCTION_UPMAXDURABILITY		21		// �������� �ִ� ������ ��� 

#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD		22		// ������� ��� - Į 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR		23		// ������� ��� - â 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE		24		// ������� ��� - ���� 
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW		25		// ������� ��� - Ȱ
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN		26		// ������� ��� - ��  
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF		27		// ������� ��� - ������
#define SCROLL_UNIQUE_FUNCTION_USESKILLUP_WEAPON	28		// ������� ��� - ��� ����
#define SCROLL_UNIQUE_FUNCTION_MAKESKILLUPATIFACT	29		// ��Ƽ��Ʈ���������� ��� 

//-------------------------------
// �κ���� 
//-------------------------------
#define INVMODE_PERSON					1		// ��� �κ� 
#define INVMODE_HORSE					2		// ��	�κ� 
#define INVMODE_BAG						3		// ���� �κ� 
#define INVMODE_BAG_SUB					4		// ����2
#define INVMODE_ALL						5		// ���� ��� �κ��� ��� �˻�. 


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
#define ITEMEQUIP_FAIL_NOTTAKEOUTSTATUS	14	// ��ȯ�� ���°� �ƴϴ�
#define ITEMEQUIP_FAIL_NOTENOUGHSTONE	15	// ��ȯ�� ��� �������� ���ڸ���
#define ITEMEQUIP_FAIL_WRONGEQUIPTYPE	16	// ��ȯ�� ��� Ÿ���� Ÿ����


#define MAX_ENCHANT_NUMBER	5		// ��æƮ ������ ��� ���� �ִ밪
// [��þƮ UI ���� - 2007.12.24 �迵�� �߰�]
#define NOW_ENCHANT_NUMBER	4		// ���� ��þƮ ������ ��� ��밡���� �� (MAX_ENCHANT_NUMBER���� ũ��ȵ�)
#define MAX_ENCHANT_GRADE	10		// ��æƮ �ִ� ���

#define AMBER_BOX_LIST_NUM				48 // ȣ�ڻ���. ���ڿ��� ������  �������� �ִ� ����.
#define AMBER_BOX_SELECT_ITEM_LIST_NUM	 3 // ȣ�ڻ���. ���õǴ� �������� ����.

#define MAX_NEWSELECTBOX_SELECTINDEX	12 // [����] ���ο� ���û��ڿ��� ���� ������ ����
#define MAX_NEWSELECTBOX_ITEM_LIST		12 // [����] ���ο� ���û��ڿ��� �ϳ��� ���ÿ��� ������ ������ ����

class cltItemManagerCommon;
class cltItem;
class cltSummonScroll;

struct stElement
{
	UI08 siType;	//�Ӽ����� ����
	SI16 siPower;	//�Ӽ����� �� 

	stElement()
	{
		siType = 0;
		siPower = 0;
	}
};

class stEnchantNeed
{
public:
	SI32 siItemGrade;
	REAL32 EnchantRate;	// ����Ȯ��
	REAL32 EnchantDownRate; // �ٿ�׷��̵�Ȯ��
	REAL32 EnchantFailRate; // �����ؼ� ����� Ȯ��
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_ENCHANT_NUMBER>		siElementUnique;
	NSafeTArray<SI32, MAX_ENCHANT_NUMBER>		siElementNum;
#else
	SI32 siElementUnique[MAX_ENCHANT_NUMBER];
	SI32 siElementNum[MAX_ENCHANT_NUMBER];
#endif
	SI32 siNeedSkill;

	stEnchantNeed()
	{
		ZeroMemory(this, sizeof(stEnchantNeed));
	}

	~stEnchantNeed()
	{
	}
};


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
			BYTE			cData8[MAX_ITEM_UNION_BYTE_OLD];
			SI32			siData32[MAX_ITEM_UNION_BYTE_OLD/4];

			cltItemWeaponOld	clItemWeapon;
			cltItemArmourOld	clItemArmour;
			cltItemNeckOld		clItemNeck;
			cltItemShoesOld		clItemShoes;
			cltItemRingOld		clItemRing;
			
		};

};
//---------------------------------------------------------------------------

// Obj�������� �⺻ ����. (4����Ʈ ) 
class cltItemCommonInfo
{
public:
	enum
	{
		REASON_NO,				  
		REASON_GIVE_PARTYHALL_ITEM,
	};

	UI32 uiDurability:		11;			// ���� ������. (0 ~ 2047)
	UI32 uiMaxDurability:	11;			// �ִ� ������. (0 ~ 2047)
	UI32 uiRareInfo:		3;			// ��ǰ���� ����. 
	UI32 uiGetItemReason:	7;			// �������� �ް� ��  Ư���� ����.
};

// Obj������ �ɼ� ����. (4����Ʈ) 
class cltItemOptionInfo{
public:
	UI32 uiType1:			6;		// �ɼ��� ����.(0~63)
	UI32 uiPara1:			10;		// �ɼǿ� ���� �Ķ��Ÿ. 
	UI32 uiType2:			6;		// �ɼ��� ����.(0~63)
	UI32 uiPara2:			10;		// �ɼǿ� ���� �Ķ��Ÿ. 
	
	// ������ �ɼ� �ؽ�Ʈ�� ���Ѵ�. 
	bool GetText(TCHAR* ptext, SI16 txtSize);
	
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

// �ƹ�Ÿ ����
class cltItemAvatarMantle
{
public:
	cltItemCommonInfo clCommonInfo;
	cltItemOptionInfo clOptionInfo;

	// ������ ������ ũ��� 64bit ���� Ȯ�� ����.
	// ���� �ִ� ���� ��ġ 120. (�������ϰ�� 3����� ������ �� ����) 120*3 = 360 �� ���� �ʰ� ����.
	UI32	uiAC:		10;		// ����. 
	
	// ���� ���俣 AC(����)�� ������ ���Ŀ� Ȯ�� ���ɼ��� �־� �ϴ� �ּ�ó��.
	UI32	uiStr:		6;		// �ٷ�
	UI32	uiDex:		6;		// ���߷� 
	UI32	uiVit:		6;		// ����� 
	void init(UI16 dur, UI16 uiac, UI16 str, UI16 dex, UI16 vit)
	{
		ZeroMemory(this, sizeof(cltItemAvatarMantle));

		clCommonInfo.uiDurability		=	dur;	// ���� ������.(0~2047)
		clCommonInfo.uiMaxDurability	=	dur;	// �ִ� ������. (0 ~ 2047)

		uiAC		=	uiac;

		//�Ʒ��� �ᵵ �������.
		uiStr		=	str;		
		uiDex	=	dex;
		uiVit		=	vit;
	}

	void Set(cltItemAvatarMantle* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemAvatarMantle));
	}
};

// �ƹ�Ÿ �Ǻ�
class cltItemAvatarDress
{
public:
	cltItemCommonInfo clCommonInfo;
	cltItemOptionInfo clOptionInfo;

	//������ ������ ũ��� 64bit ���� Ȯ�� ����.
	UI32				uiSkillUp:	6;	// ��� ���. 

	void init(UI16 dur , SI32 skillup)
	{
		ZeroMemory(this, sizeof(cltItemAvatarDress));
		
		clCommonInfo.uiDurability		=	dur;	// ���系����
		clCommonInfo.uiMaxDurability	=	dur;	// �ִ볻����

		uiSkillUp = skillup;
	}
	
	void Set(cltItemAvatarDress* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemAvatarDress));
	}
};

// �ƹ�Ÿ ����
class cltItemAvatarHat
{
public:
	cltItemCommonInfo clCommonInfo;
	cltItemOptionInfo clOptionInfo;

	// ��� ���. ������ ������ ũ��� 64bit ���� Ȯ�� ����.
	UI32 uiSkillUp:		6;		

	void init(UI16 dur ,UI16 siSkillUp)
	{
		ZeroMemory(this, sizeof(cltItemAvatarHat));

		clCommonInfo.uiDurability		=	dur;	// ���系����
		clCommonInfo.uiMaxDurability	=	dur;	// �ִ볻����
		
		uiSkillUp = siSkillUp;
	}


	void Set(cltItemAvatarHat* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemAvatarHat));
	}
};

// �ƹ�Ÿ �����
class cltItemAvatarNeck
{
public:
	cltItemCommonInfo clCommonInfo;
	cltItemOptionInfo clOptionInfo;

	// ������ ������ ũ��� 64bit ���� Ȯ�� ����.
	//UI32 uiBaseSkillType:		4;	// �⺻ ��з� ��ų Ÿ��

	UI32 uiUpgradeSkillUnique:	8;	// ���� ���õ� ��ų Ÿ��	
	UI32 uiSkillValue:		    8;	// �ش� ��ų�� ���� ����ġ (���� ���� ��ġ)

	UI32 uiMaxUsedate:		    8;  // �ִ� usedate 
	UI32 uiMaxSkillPoint:		8;	// �ִ� ������ ����


	void init(UI16 dur, UI16 siSkillValue, UI08 MaxSkillPoint,UI08 MaxUsedate )
	{
		ZeroMemory(this, sizeof(cltItemAvatarNeck));

		clCommonInfo.uiDurability		=	dur;	// ���� ������.(0~2047)
		clCommonInfo.uiMaxDurability	=	dur;	// �ִ� ������. (0 ~ 2047)

		uiSkillValue	=	siSkillValue;

		uiMaxUsedate = MaxUsedate;
		uiMaxSkillPoint = MaxSkillPoint;
	}

	void Set(cltItemAvatarNeck* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemAvatarNeck));
	}
};

// �ƹ�Ÿ ����
class cltItemAvatarRing
{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	// ������ ������ ũ��� 64bit ���� Ȯ�� ����.
	UI32 uiAC:		6;		// ����
	UI32 uiStr:		5;		// ��
	UI32 uiDex:		5;		// ���߷�
	UI32 uiVit:		5;		// �����

	UI32 uiMag:		5;		// ����
	UI32 uiWis:		5;		// ����
	UI32 uiLuk:		5;		// ���
	UI32 uiHnd:		5;		// ������

	void Init( UI16 dur, UI08 ac, UI08 str, UI08 dex, UI08 vit, UI08 mag, UI08 wis, UI08 luk, UI08 hnd )
	{
		ZeroMemory(this, sizeof(cltItemAvatarRing));

		clCommonInfo.uiDurability		= dur;		// ���� ������
		clCommonInfo.uiMaxDurability	= dur;		// �ִ� ������

		uiAC			= ac;
		uiStr			= str;
		uiDex			= dex;
		uiVit			= vit;
		uiMag			= mag;
		uiWis			= wis;
		uiLuk			= luk;
		uiHnd			= hnd;
	}
	void Set(cltItemAvatarRing* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemAvatarRing));
	}

	void SetQualityRate(SI32 siQualityRate);	// ���� : ���� ��ġ�� ���� ������ ��������ش�. (���� ��ǰ ������ �����̳� ���� ���� �����ϵ��� ���ִ� �Լ�)
};

class cltItemRing
{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32 uiStr: 4;
	UI32 uiDex: 4;
	UI32 uiVit: 4;
	UI32 uiMag: 4;
	UI32 uiLuk: 4;
	UI32 uiHnd: 4;

	void Init( UI16 dur, UI08 ac, UI08 str, UI08 dex, UI08 vit, UI08 mag, UI08 luk, UI08 hnd )
	{
		ZeroMemory(this, sizeof(cltItemRing));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;
		uiStr			= str;
		uiDex			= dex;
		uiVit			= vit;
		uiMag			= mag;
		uiLuk			= luk;
		uiHnd			= hnd;
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
	UI08 uiMaxUsedate;				    // �ִ� usedate 
	UI08 uiMaxSkillPoint;				// �ִ� ������ ����

	void Init(UI16 dur, UI08 SkillPointUp, UI08 MaxUsedate, UI08 MaxSkillPoint)
	{
		ZeroMemory(this, sizeof(cltItemNeck));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiSkillPointUp = SkillPointUp;
		uiMaxUsedate = MaxUsedate;
		uiMaxSkillPoint = MaxSkillPoint;

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

class cltItemStatusArmour{
public:
	cltItemCommonInfo	clCommonInfo;
	cltItemOptionInfo	clOptionInfo;

	UI32				uiSkillUp:	6;	// ��� ���. 
	UI32				uiReserve:	2;	// ����

	UI32 uiStr: 8;
	UI32 uiDex: 8;
	UI32 uiVit: 8;
	UI32 uiMag: 8;
	UI32 uiHnd: 8;
	UI32 uiLuk: 8;
	UI32 uiWis: 8;

	void Init(UI16 dur, UI16 skillup)
	{
		ZeroMemory(this, sizeof(cltItemStatusArmour));

		clCommonInfo.uiDurability		= dur;
		clCommonInfo.uiMaxDurability	= dur;

		uiSkillUp		= skillup;
	}

	void Set(cltItemStatusArmour* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltItemStatusArmour));
	}

	void SetStatus(UI08 Str, UI08 Dex, UI08 Mag, UI08 Vit, UI08 Hnd, UI08 Luk)
	{
		uiStr = Str;
		uiDex = Dex;
		uiMag = Mag;
		uiVit = Vit;
		uiHnd = Hnd;
		uiLuk = Luk;
	}
};


//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
class cltItemCrystal{
	public:
		cltItemCommonInfo	clCommonInfo;
		cltItemOptionInfo	clOptionInfo;
	
		SI16 siMaxDurability;			// �ִ� ������. (0 ~ 65535)

		// MAX���� 16�̴�.
		UI08 uiCrystalAbility; // ����ü�� ������ �ɷ� Ÿ��.
		UI08 uiCrystalAbilityNum;  // ����ü�� ������ �ɷ� ��ġ.	
		
		void Init(UI16 dur, SI16 MaxDurability, UI08 CrystalAbility, UI08 CrystalAbilityNum)
		{
			ZeroMemory(this, sizeof(cltItemCrystal));

			clCommonInfo.uiDurability		= dur;
			clCommonInfo.uiMaxDurability	= dur;

			siMaxDurability = MaxDurability;
			
			uiCrystalAbility = CrystalAbility;
			uiCrystalAbilityNum = CrystalAbilityNum;

		}

		void Set(cltItemCrystal* pcldata)
		{
			memcpy(this, pcldata, sizeof(cltItemCrystal));
		}

		void SetMaxDurability(SI16 _siMaxDurability){ siMaxDurability = _siMaxDurability; }

		SI16 GetMaxDurability(){ return siMaxDurability; }
		SI16 GetCrystalAblilty(){ return (SI16)uiCrystalAbility; }
		SI16 GetCrystalAbilityNum(){ return (SI16)uiCrystalAbilityNum; }
};


//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
class cltCrystalItem{
	public:	
		SI16 siCrystalType; // ����ü ����.(����ũ )
		SI16 siDurability;			// ���� ������. (0 ~ 65535)
		SI16 siMaxDurability;			// �ִ� ������. (0 ~ 65535)

		// MAX���� 16�̴�.
		UI08 uiCrystalAbility; // ����ü�� ������ �ɷ� Ÿ��.
		UI08 uiCrystalAbilityNum;  // ����ü�� ������ �ɷ� ��ġ.	
	
		cltCrystalItem()
		{
			ZeroMemory(this, sizeof(cltCrystalItem));
		}

		BOOL IsSame( cltCrystalItem* pclCrystalItem )
		{
			if(pclCrystalItem == NULL )										return FALSE;

			if(siCrystalType != pclCrystalItem->siCrystalType)				return FALSE;
			if(siDurability != pclCrystalItem->siDurability)				return FALSE;
			if(siMaxDurability != pclCrystalItem->siMaxDurability)			return FALSE;

			if(uiCrystalAbility != pclCrystalItem->uiCrystalAbility)		return FALSE;
			if(uiCrystalAbilityNum != pclCrystalItem->uiCrystalAbilityNum)	return FALSE;

			return TRUE;
		}

		void Init()
		{
			ZeroMemory(this, sizeof(cltCrystalItem));
		}

		void Set(cltCrystalItem* pcldata)
		{
			memcpy(this, pcldata, sizeof(cltCrystalItem));
		}

		bool SetMaxDurability(SI16 maxDurability) // �������� �ִ�ġ�� �����Ѵ�.
		{
			if(maxDurability <= 30000) //�ִ� �������� 30000 �̴�. - Ÿ�Ի�.
			{
				siMaxDurability = 	maxDurability;
				return true;
			}

			return false;
		}

		void SetDurability(SI16 Durability){ siDurability = Durability; }
		
		void DecDurability(SI16 decDurability) // ���� �������� ���� ��Ų��.
		{
			siDurability  -= decDurability;

			if(siDurability < 0)
				siDurability = 0;		
		}
		SI16 GetCrystalType(){ return siCrystalType; }
		SI16 GetDurability(){ return siDurability; }
		SI16 GetMaxDurability(){ return siMaxDurability; }
		SI16 GetCrystalAblilty(){ return (SI16)uiCrystalAbility; }
		SI16 GetCrystalAbilityNum(){ return (SI16)uiCrystalAbilityNum; }

};


// �������� ���Ͽ� ũ��. 
#define MAX_ITEM_UNION_BYTE 16

//-------------------------------------------
// �������� ���� �����Ϳ� ���� �������� �Ѵ�. 
//-------------------------------------------
class cltItemData{
public:
	SI16 siUnique;
	SI16 siItemNum;		// �������� ��� �ִ°� ?

	UI08 uiDateYear;
	UI08 uiDateMonth;
	UI08 uiDateDay;
	UI16 uiDateUseDay;

	SI32 siMakerPersonID;

	stElement Element;
public:
	union
	{
		BYTE			cData8[MAX_ITEM_UNION_BYTE];
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
		cltItemStatusArmour	clItemStatusArmour;
		cltItemCrystal			clItemCrystal;
		cltItemAvatarRing	clItemAvatarRing;
		cltItemAvatarMantle	clItemAvatarMantle;
		cltItemAvatarNeck	clItemAvatarNeck;
		cltItemAvatarDress	clItemAvatarDress;
		cltItemAvatarHat clItemAvatarHat;
	};

	// by LEEKH 2007.08.21 - ������ �ø��� ID �߰�
	SI32 siSID;		// �������� SERIAL ID

	SI16 siPalette;	// �ȷ�Ʈ ����ũ

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI08 siUseCrystalNum;  // ��밡���� ����ü ���Լ�.
#ifdef _SAFE_MEMORY
	NSafeTArray<cltCrystalItem, MAX_CRYSTAL_NUM>		cltItemCrytal;
#else
	cltCrystalItem cltItemCrytal[MAX_CRYSTAL_NUM];
#endif

	void Init()
	{
		ZeroMemory(this, sizeof(cltItemData));

		siUnique = 0 ;
		siItemNum = 0 ;

		uiDateYear = 0 ;
		uiDateMonth = 0 ;
		uiDateDay = 0 ;
		uiDateUseDay = 0 ;

		Element.siType = 0;
		Element.siPower = 0;

		siSID = 0;

		siUseCrystalNum = 0;
		for ( SI16 i=0 ; i < MAX_CRYSTAL_NUM ; i++ )
		{
			cltItemCrytal[i].Init();
		}
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

		UI08 uiDateYear;
		UI08 uiDateMonth;
		UI08 uiDateDay;
		UI16 uiDateUseDay;

		SI32 siMakerPersonID;

		stElement Element;

public:
	union
	{
		BYTE			cData8[MAX_ITEM_UNION_BYTE];
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
		cltItemStatusArmour	clItemStatusArmour;
		cltItemCrystal			clItemCrystal;
		cltItemAvatarMantle	clItemAvatarMantle;
		cltItemAvatarNeck	clItemAvatarNeck;
		cltItemAvatarDress	clItemAvatarDress;
		cltItemAvatarHat clItemAvatarHat;
		cltItemAvatarRing	clItemAvatarRing;

	};

	// by LEEKH 2007.08.21 - ������ �ø��� ID �߰�
	SI32 siSID;		// �������� SERIAL ID

	SI16 siPalette;	// �ȷ�Ʈ ����ũ

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	SI08 siUseCrystalNum;  // ��밡���� ����ü ���Լ�.
#ifdef _SAFE_MEMORY
	NSafeTArray<cltCrystalItem, MAX_CRYSTAL_NUM>		cltItemCrytal;
#else
	cltCrystalItem cltItemCrytal[MAX_CRYSTAL_NUM];
#endif


	cltItem()
	{
		ZeroMemory(this, sizeof(cltItem));
	};

	cltItem(SI32 siUnique);
	cltItem(SI32 siUnique , SI32 siUsedate);

	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemWeapon* pcldata);
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemArmour* pcldata);	
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemShoes* pcldata);
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemRing* pcldata);	
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemStatusArmour* pcldata);	
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemMantle* pcldata);
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemAvatarMantle* pcldata); // �ƹ�Ÿ ����
	cltItem(SI32 siUnique, SI32 siUseDate, cltItemAvatarNeck* pcldata); // �ƹ�Ÿ �����
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemAvatarDress* pcldata); // �ƹ�Ÿ �Ǻ�
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemAvatarHat* pcldata); // �ƹ�Ÿ ����
	cltItem(SI32 siUnique, SI32 siUseDate, stElement* element, cltItemAvatarRing* pcldata); // �ƹ�Ÿ ����
	cltItem(SI32 siUnique, SI32 siUseDate, cltItemTool* pcldata);
	cltItem(SI32 siUnique, SI32 siUseDate, cltItemNeck* pcldata);

	cltItem(SI32 siUnique, SI32 siUseDate, cltItemBag* pcldata);
	cltItem(SI32 siUnique, cltItemBag* pcldata);
	


	void Init()
	{
		ZeroMemory(this, sizeof(cltItem));
	}
	void Set(const cltItem* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}
	void Set(const TCHAR* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}
	void Set(const cltItemData* pclitem)
	{
		memcpy(this, pclitem, sizeof(cltItem));
	}


	SI32 GetImage(cltItemManagerCommon* pclItemManager);
	const TCHAR* GetShortName(cltItemManagerCommon* pclItemManager);
	bool GetFullName(cltItemManagerCommon* pclItemManager, TCHAR* pname, SI16 txtSize);
	// �������� �̸��� ������ ���´�. 
	bool GetFullNameNNum(cltItemManagerCommon* pclItemManager, TCHAR* pname, SI16 txtSize);
	TCHAR* GetArmCode(cltItemManagerCommon* pclItemManager);

	
	// �������� �� ������ ����� �޾Ҵ��� Ȯ���Ѵ�.
	BOOL CheckType(cltItemManagerCommon* pclItemManager, SI32 orgtype);

	// �������� Ÿ���� ã�´�. 
	SI32 GetType(cltItemManagerCommon* pclItemManager)const;

	// �������� Ÿ���� ã�´�. 
	SI32 GetAavatarType(cltItemManagerCommon* pclItemManager)const;

	// �������� ���ݻ�Ÿ��� ã�´�. 
	SI32 GetAttackRange(cltItemManagerCommon* pclItemManager)const;

	// �������� ����Ÿ���� ���Ѵ�. 
	SI32 GetAttackType(cltItemManagerCommon* pclItemManager)const;

	// �������� �����ֱ⸦  ã�´�. 
	SI32 GetAttackInterval(cltItemManagerCommon* pclItemManager)const;



	//----------------------------------------------------------------------------------------------------
	// �߰� ���� �������� ���Ѵ�. - ũ����Ż.
	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.

	// �ּ� �������� ���Ѵ�. 
	SI32 GetMinDamage(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);
	// �ִ� �������� ���Ѵ�. 
	SI32 GetMaxDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	SI32 GetAddMagicalDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetAddMagicalMinDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetAddMagicalMaxDamage(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	// ���߷� ���. 
	SI32 GetPhysicalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetMagicalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	SI32 GetPhysicalAC(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetMagicalAC(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	
	SI32 GetPhysicalDodgeRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetMagicalDodgeRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	SI32 GetCrystalHitpoint(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalManapoint(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalWeigt(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	SI32 GetCrystalFireAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalWaterAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalWindAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalEarthAttack(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalFireDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalWaterDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalWindDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	SI32 GetCrystalEarthDeffence(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);

	SI32 GetCriticalHitRate(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	//------------------------------------------------------------------------------------------------------


	// ��æƮ �������� ���Ѵ�.  by tae-yang
	SI32 GetEnchantDamage(cltItemManagerCommon* pclItemManager)const;
	// ��æƮ Ÿ�� ���Ѵ�.  
	SI32 GetEnchantType(cltItemManagerCommon* pclItemManager)const;

	SI32 GetEnchantAC(cltItemManagerCommon* pclItemManager,bool bClient)const;
	SI32 GetEnchantACFrom(cltItemManagerCommon* pclItemManager,bool bClient, SI32 attacktype)const;

	SI32 GetEnchantAttFrom(cltItemManagerCommon* pclItemManager,bool bClient, SI32 attacktype)const;
		
	// �ּ� �������� �����Ѵ�. 
	SI32 SetMinDamage(cltItemManagerCommon* pclItemManager, SI32 damage);
	// �ִ� �������� �����Ѵ�. 
	SI32 SetMaxDamage(cltItemManagerCommon* pclItemManager, SI32 damage);


	// �ٷ��� ���Ѵ�. 
	SI32 GetEquipStr(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	// ���߷��� ���Ѵ�. 
	SI32 GetEquipDex(cltItemManagerCommon* pclItemManager , SI32* CrystalPer);
	// ������� ���Ѵ�. 
	SI32 GetEquipVit(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);
	// ������ ���Ѵ�. 
	SI32 GetEquipMag(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);
	// ���� ���Ѵ�. 
	SI32 GetEquipLuk(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);
	// �������� ���Ѵ�. 
	SI32 GetEquipHnd(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);
	// ������ ���Ѵ�. 
	SI32 GetEquipWis(cltItemManagerCommon* pclItemManager, SI32* CrystalPer);


	// ���ɷ��� ���Ѵ� 
	SI32 GetAC(cltItemManagerCommon* pclItemManager)const;
	
	// ��� �ɷ��� �����Ѵ�. 
	SI32 SetAC(cltItemManagerCommon* pclItemManager, SI32 ac);

	
	// ���� ���Ѵ� 
	SI32 GetLuck(cltItemManagerCommon* pclItemManager)const;

	// ����� ����� ���Ѵ�. 
	// ũ����Ż�� ���� �ɷ��� ���� ����� ��� �Ѵ�. - �O���O���ä����Τ�������
	SI32 GetUpgradeSkillLevel(cltItemManagerCommon* pclItemManager, SI32 skillunique , bool countCrystalAbilityNum = true);

	// Ư�� ����� ������ ���� ��� ȿ���� ���Ѵ�. 
	SI32 GetSkillScrollUp(cltItemManagerCommon* pclItemManager, SI32 skillunique);

	//----------------------------------------
	// �Ⱓ�� ����. 
	//----------------------------------------
	BOOL IsHaveUseDay() // �Ⱓ�� �������ΰ�?
	{
		return (uiDateUseDay > 0); //  �������� �Ⱓ�� ���������� üũ
	}

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

	// �������� ���� �г�Ƽ�� �����Ѵ�
	REAL32 GetDurabilityPenlty( cltItemManagerCommon* pclItemManager );

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
	BOOL IsSame(cltItem* pclitem, bool numcomp);
	
	BOOL IsBulletItem();

	
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

	// �к������ΰ�?
	bool IsSealingUp(cltItemManagerCommon* pclItemManager);

	// �ͼӻ����ΰ�?
	bool IsBelonging(cltItemManagerCommon* pclItemManager);

	// ����������� �³�?
	bool IsCorrectPrivateEquip(cltItemManagerCommon* pclItemManager, SI32 siKind);

	// ��ȣ�Ŀ��� ���� �����Ѱ�?
	bool IsDisassemble(cltItemManagerCommon* pclItemManager);

	// �Ⱓ�� ������ �� �ִ� �������ΰ�?
	bool IsPlusUseDate(cltItemManagerCommon* pclItemManager);

	// SID�� �����ؾ� �ϴ°�?
	bool IsCreateSID(cltItemManagerCommon* pclItemManager);

	// ----------------------------------------------------------------------
	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ���� ����.
	void  DelUseCrystalNum(SI08 indexDelUseCrystalNum)
	{
		if((indexDelUseCrystalNum > 0 )||(indexDelUseCrystalNum <= MAX_CRYSTAL_NUM))
		{
			 cltItemCrytal[indexDelUseCrystalNum].Init(); 
		}
	}

	bool SetUseCrystalNum(SI08 UseCrystalNum)
	{
		if((UseCrystalNum < 0 )||(UseCrystalNum >MAX_CRYSTAL_NUM))
			return false;
	
		if( UseCrystalNum <= MAX_CRYSTAL_NUM)
		{
			siUseCrystalNum = UseCrystalNum;

			for(int i = siUseCrystalNum+1; i <=MAX_CRYSTAL_NUM; i++)
			{	
				DelUseCrystalNum(i);
			}
			return true;
		}

		return false;
	}

	// [�߰� : Ȳ���� 2008. 3. 2 => �������ִ� �� ������ �ִ°�? 
	bool EmptyCrystalSlot(void)
	{
		for(int Count = 0; Count < siUseCrystalNum; ++Count)
		{
			if( 0 == cltItemCrytal[Count].GetCrystalType() )
			{
				return true;
			}
		}
		return false;
	}

	// [ �߰� : Ȳ���� 2008. 3. 2 => �������ִ� �� ������ ���� ] 
	SI32 EmptyCrystalSlotCount(void)
	{
		SI32 EmptySlotCount = 0;
        	for(int Count = 0; Count < siUseCrystalNum; ++Count)
		{
			if( 0 == cltItemCrytal[Count].GetCrystalType() )
			{
				++EmptySlotCount;
			}
		}
		
		return EmptySlotCount;
	}

	SI16 GetUseCrystalNum(){ return (SI16)siUseCrystalNum;}
	SI32 GetAllCrystalAbilityNum(UI08 CrystalAbility);  // �� �����ۿ� �����ִ� ��� ����ü����, ���ϴ� �ɷ��� ���� ���Ͽ���ȯ�Ѵ�.
	SI32 GetCrystalAbilityFromSkillUnique(SI32 skillunique);

	// �ش� �������� ��� ����ü ������ �޾� �´�. - ������ � ������
	//bool GetAllCrystalInfo(cltItemManagerCommon* pclItemManager ,cltCrystalItem  * ItemCrytal );

	// �������� ���δ�. - ������ ������ '����'�ִ� ��� ����ü�� �ϰ������� �������� �����ȴ�.
	bool DecreaseCrystalDurability(cltItemManagerCommon* pclitemmanager, SI16 durvary);

	// ũ����Ż�� �������� 1%������ �پ�, Client�� ������ �ϴ��� ���θ� �����Ѵ�.
	bool GetDecreaseCrystalDurabilityPer(cltItemManagerCommon* pclItemManager);

	SI32 GetCrystalMaxDurability()	{ return clItemCrystal.siMaxDurability;		}
	SI32 GetCrystalAbility()		{ return clItemCrystal.uiCrystalAbility;	}
	SI32 GetCrystalAbilityNum()		{ return clItemCrystal.uiCrystalAbilityNum; }

	// ----------------------------------------------------------------------

	SI32 GetCrystalGrade( void );								// [����] ũ����Ż �������� ����� �����ش�
	bool IsWeapon( cltItemManagerCommon* pclItemManager );		// [����] �����ΰ�?
	SI16 GetEquipLevel( cltItemManagerCommon* pclItemManager );	// [����] ���뷹���� ���´�	
	bool IsHaveCrystalSlot( void )								// [����] ũ����Ż ������ ���� �ִ°�
	{
		if ( siUseCrystalNum )
		{
			return true;
		}

		return false;
	}

	void GetGMSectionData(GMSectionData* pkGMSectionData);

	// �к��� �����Ѵ�
	bool CancellationSealingUp( SYSTEMTIME sTime );

	SI32 SelectUseBaseSkillTypeToAvatar(UI32 uiBaseSkillType);
};


//---------------------------------------
// ĳ������ ������ ���� ����. 
//---------------------------------------
class cltPItemInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEM_PER_PERSON>	clItem;		// ��ȯ�� ��� ���� - ���� by LEEKH 2008-08-07
#else
	cltItem		clItem[MAX_ITEM_PER_PERSON];		// ��ȯ�� ��� ���� - ���� by LEEKH 2008-08-07
#endif

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

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
	//=====================================
	
	
	//=====================================
	
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

	// Ư����ġ��, Ư�������� Ÿ���� �������� �߰� �� �� �ִ��� �˻��Ѵ�.
	bool CanToitemPos(cltItemManagerCommon* pclItemManager, SI32 toItempos );
	
	// �κ��丮�� �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
	bool CanAddInv( cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,
		SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue, SI16* pCheckPos = NULL );

	bool IsBlankInv(cltItemManagerCommon*pclItemManager,SI32 invnum,SI32 invmode);

	// �κ��丮�� ���� ����(�ִ� MAX_CANADDINV_CHECK_NUM) ��ŭ�� �������� �߰��� �� �ִ��� Ȯ�θ� �Ѵ�.  
	bool CanAddInvManyItems(cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,
		SI32* prtnvalue);

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
	SI32 GetItemNum(SI32 itemunique);

	// ���â�ȿ� unique�� �������� ��� ���� �ִ°�?
	SI32 GetItemNumInEquip(SI32 itemunique);
	
	// unique�� �������� �κ��� �����ϴ°� ?
	SI32  GetItemPos(SI32 itemunique);
	SI32  GetItemTotalPos(SI32 itemunique);

	// ���â�ȿ� unique�� �������� ��ġ ����
	SI32 GetItemPosInEquip(SI32 itemunique);



	// Ư�� �����۵��� �� �κ��� �� �� �ִ°�. 
	// �� �� �ִٸ� ��� ��ġ�� �� �� �ִ°��� ���س���. 
	bool CanInputItemList(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32 itemlistnum, SI16* pclpos);
	
	// Ư�� �������� ���ǰ�� ���Ǿ� �ִ°� ?
	bool HaveInEquip(SI32 itemunique);
	
	// ��� ���ǰ�� ���������� ���Ǿ� �ִ°� ?
	bool IsAllProperEquip(cltItemManagerCommon* pclItemManager, SI16* punique, SI16* ppos, SI32 siKind = 0);
	
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
		}
		
		MessageBox(NULL, TEXT("vefs2") , TEXT("vefsw") , MB_OK);
		return &clItem[0];
	}

	// siItemUnique�� siAmount��ŭ ���� �� �ִ� ��Ḧ ���� �ִ°�?
	bool IsHaveMaterialItem( cltItemManagerCommon* pclItemManager, SI32 siItemUnique, SI32 siAmount );
	
};

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
// Ŭ���̾�Ʈ ���޿� ���� Ŭ����.( ����� �������� ������ ����.)
class cltCrystalItemInfo{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_CRYSTAL_NUM>		siDurability;
#else
	SI16 siDurability[MAX_CRYSTAL_NUM];	// Ŭ���̾�Ʈ�� ������ �� ����ü�� ���� ������. (0 ~ 65535)
#endif

	cltCrystalItemInfo()
	{
		ZeroMemory(this, sizeof(cltCrystalItemInfo));
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltCrystalItemInfo));
	}

	void Set(cltCrystalItemInfo* pcldata)
	{
		memcpy(this, pcldata, sizeof(cltCrystalItemInfo));
	}

};
/*
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

};*/

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
#ifdef _SAFE_MEMORY
		SI32 i=0;
		for(i=0; i<MAX_ITEMNUM_PER_ITEMMALL; i++)		clItem[i].Set(&pclitemmallitem[i]);
		for(i=0; i<MAX_ITEMNUM_PER_ITEMMALL; i++)		siItemID[i] = itemid[i];
#else
		memcpy ( clItem, pclitemmallitem, sizeof( cltItem ) * MAX_ITEMNUM_PER_ITEMMALL );
		memcpy ( siItemID, itemid, sizeof( SI32 ) * MAX_ITEMNUM_PER_ITEMMALL );
#endif
		
		siTotalItemNum = total;
		siListPage = page;
		
		bItemExistence = existence ;
	}
	
	void SetItem(cltItem * pclitemmallitem)
	{
#ifdef _SAFE_MEMORY
		SI32 i=0;
		for(i=0; i<MAX_ITEMNUM_PER_ITEMMALL; i++)		clItem[i].Set(&pclitemmallitem[i]);
#else
		memcpy ( clItem, pclitemmallitem, sizeof( cltItem ) * MAX_ITEMNUM_PER_ITEMMALL );
#endif
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
#ifdef _SAFE_MEMORY
		SI32 i=0;
		for(i=0; i<MAX_ITEMNUM_PER_ITEMMALL; i++)		siItemID[i] = itemid[i];
#else
		memcpy ( siItemID, itemid, sizeof( SI32 ) * MAX_ITEMNUM_PER_ITEMMALL );
#endif
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
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEMNUM_PER_ITEMMALL>		clItem;
	NSafeTArray<SI32, MAX_ITEMNUM_PER_ITEMMALL>			siItemID;
#else
	cltItem		clItem[MAX_ITEMNUM_PER_ITEMMALL];
	SI32		siItemID[MAX_ITEMNUM_PER_ITEMMALL];
#endif
	
	SI32		siTotalItemNum; // �� ������ ����
	SI32		siListPage; // ���� ���õ� ����Ʈ�� ������ �� 1~
	
	bool		bItemExistence; // �� �������� �ִ��� ������
	
};

// cltItemOld������ cltItem������ �ٲ��ش�.
/*cyj ConvertItemToitem2 �ּ�ó��
inline bool ConvertItemToitem2(cltItemOld* pclitem, cltItem* pclitem2)
{

	pclitem2->Init();
	
	SI32 unique = pclitem->siUnique;

	pclitem2->siUnique	= pclitem->siUnique;
	pclitem2->siItemNum	= pclitem->siItemNum;

	// �����. 
	if(unique <= ITEMUNIQUE(599))
	{
		pclitem2->clItemWeapon.clCommonInfo.uiMaxDurability		= pclitem->clItemWeapon.uiMaxDurability;
		pclitem2->clItemWeapon.clCommonInfo.uiDurability		= pclitem->clItemWeapon.uiDurability;
		pclitem2->clItemWeapon.uiMinDamage						= pclitem->clItemWeapon.uiMinDamage;
		pclitem2->clItemWeapon.uiMaxDamage						= pclitem->clItemWeapon.uiMaxDamage;
	}
	// ����. 
	else if(unique <= ITEMUNIQUE(999))
	{
		pclitem2->clItemArmour.clCommonInfo.uiMaxDurability	= pclitem->clItemArmour.uiMaxDurability;
		pclitem2->clItemArmour.clCommonInfo.uiDurability	= pclitem->clItemArmour.uiDurability;
		pclitem2->clItemArmour.uiAC							= pclitem->clItemArmour.uiAC;
	}
	// ����̷�. 
	else if(unique <= ITEMUNIQUE(1499))
	{
		pclitem2->clItemNeck.clCommonInfo.uiMaxDurability	= pclitem->clItemNeck.uiMaxDurability;
		pclitem2->clItemNeck.clCommonInfo.uiDurability	= pclitem->clItemNeck.uiDurability;
		pclitem2->clItemNeck.uiSkillPointUp				= pclitem->clItemNeck.uiSkillPointUp;
	}
	// �Ź߷�. 
	else if(unique <= ITEMUNIQUE(1999))
	{
		pclitem2->clItemShoes.clCommonInfo.uiMaxDurability	= pclitem->clItemShoes.uiMaxDurability;
		pclitem2->clItemShoes.clCommonInfo.uiDurability	= pclitem->clItemShoes.uiDurability;
		pclitem2->clItemShoes.uiAC			= pclitem->clItemShoes.uiAC;
		pclitem2->clItemShoes.uiMoveSpeed	= pclitem->clItemShoes.uiMoveSpeed;
	}
	// ������ .
	else if(unique >= ITEMUNIQUE(7500) && unique < ITEMUNIQUE(8000))
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
*/

//[�߰� : Ȳ���� 2008. 1. 31 => cltTreasureBox, cltSpaceBox ���� ����� ������ ������ ã��.]
bool CanAddInv( bool BoxKind, cltItem* clItem, cltItemManagerCommon* pclItemManager, SI32 invmode, cltItem* pclitem, DWORD* pdwreserve,
			   SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue, SI16* pCheckPos = NULL );

SI16 GetBoxItemCount(bool BoxKind, cltItem* clItem, SI16 siArrayCount);

//[�߰� : Ȳ���� 2008. 1. 29 => ���� ���� ������ ����ü]
class cltSpaceBox
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEM_SPACE_BOX>	clItem;
#else
	cltItem		clItem[MAX_ITEM_SPACE_BOX];
#endif

	cltSpaceBox() { ZeroMemory( this, sizeof( cltSpaceBox ) ); }
	~cltSpaceBox(){}

	void Init()
	{
		ZeroMemory( this, sizeof( cltSpaceBox ) );
	}

	void Set(cltSpaceBox* pclSpaceBox)
	{
		if(pclSpaceBox == NULL)		return;

		for(SI32 i=0; i<MAX_ITEM_SPACE_BOX; i++)
		{
			clItem[i].Set(&pclSpaceBox->clItem[i]);
		}
	}
};

//[�߰� : Ȳ���� 2008. 1. 29 => ���� ����.(����) ������ ����ü]
class cltTreasureBox
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_ITEM_TREASURE_BOX>	clItem;
#else
	cltItem		clItem[MAX_ITEM_TREASURE_BOX];
#endif

	cltTreasureBox() { ZeroMemory( this, sizeof( cltTreasureBox ) ); }
	~cltTreasureBox(){}

	void Init()
	{
		ZeroMemory( this, sizeof( cltTreasureBox ) );
	}

	void Set(cltTreasureBox* pclTreasureBox)
	{
		if(pclTreasureBox == NULL)		return;

		for(SI32 i=0; i<MAX_ITEM_TREASURE_BOX; i++)
		{
			clItem[i].Set(&pclTreasureBox->clItem[i]);
		}
	}
};


#endif
