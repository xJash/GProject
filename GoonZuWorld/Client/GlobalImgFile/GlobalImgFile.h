#ifndef _GLOBALIMGFILE_H
#define _GLOBALIMGFILE_H

#include <Directives.h>
#include <Graphic_Capsule.h>

/*
#define MAX_GLOBAL_IMG_FILE_NUMBER		300

#define GIMG_CHARSHADOW					0
#define GIMG_POISON						1
#define	GIMG_CUT						2
#define GIMG_EXPCOUNTER					3
#define GIMG_WATERDROP					4
#define GIMG_HELPPANNEL					5
#define GIMG_DMGCOUNTER					6
#define GIMG_FIELDITEM					7
#define	GIMG_LEVELUP					8
#define GIMG_REGENERATION				9
#define GIMG_FIREFLY					10			// �ݵ���
#define GIMG_BIGBOSS					11			// �����
#define GIMG_SMALLBOSS					12			// ���
#define GIMG_CRITICALEFFECT				13			// �ʻ��
#define GIMG_CLICKPOINT					14			// ���콺 Ŭ��
#define GIMG_MONSTERINFOBACK			15			// ���� ����â�� �ִ� ���� �̹��� ���	
#define GIMG_WARKILL					16			// ���￡�� óġ�� ������ ���. 
#define GIMG_WARKILLNUM					17			// ���￡�� óġ�� ������ ��. 
#define GIMG_JIM						18			// ��ų ������ ���� ��
#define GIMG_SKILLLEVELUP				19			// ��ų ���� ��
#define GIMG_ICEFLASH					20			// ������ ��¦��
//#define GIMG_LOADING								// �ε� ��
#define GIMG_SERVERNAME					21			// ���� �̸�
#define GIMG_SKILLNAME					22			// ��ų��
#define GIMG_SKILLEXPCOUNTER			23			// ��ų Counter

// ĳ���� Ư�� ����Ʈ ���� - ���� ���̰� ����
#define GIMG_SPECIAL_SWORD					24		// �� ����
#define GIMG_SPECIAL_SPEAR_BRANDISH			25		// ��� �ֵθ��� â ����
#define GIMG_SPECIAL_SPEAR_JAB				26		// ��� ��� â ����
#define GIMG_SPECIAL_AXE					27		// ���� ����

#define GIMG_SPECIAL_SWORD_HORSE			28		// �� �� ����
#define GIMG_SPECIAL_SPEAR_BRANDISH_HORSE	29		// �� ��� �ֵθ��� â ����
#define GIMG_SPECIAL_SPEAR_JAB_HORSE		30		// �� ��� ��� â ����
#define GIMG_SPECIAL_AXE_HORSE				31		// �� ���� ����

#define GIMG_SPECIAL_SWORDDMG				32		// �� ���ݿ� ����
#define GIMG_SPECIAL_SPEARDMG_BRANDISH		33		// ��� �ֵθ��� â ���ݿ� ����
#define GIMG_SPECIAL_SPEARDMG_JAB			34		// ��� ��� ���ݿ� ����
#define GIMG_SPECIAL_AXEDMG					35		// ���� ���ݿ� ����

// �б� ����
#define GIMG_SCHOOL1						40		// �б� �ΰ� 1
#define GIMG_SCHOOL2						41		// �б� �ΰ� 2
#define GIMG_SCHOOL3						42		// �б� �ΰ� 3

#define GIMG_MAGIC_THUNDER					50

#define GIMG_MAGIC_ROCKSLIDE				51			// ���� ����
#define GIMG_MAGIC_FLAME					52
#define GIMG_MAGIC_WHIRLPOOL				53

#define GIMG_MAGIC_WAR						54

#define GIMG_MAGIC_PROMPTBAR				55

#define GIMG_MAGIC_DEFUP					56			// ���� ���. 

#define GIMG_VILLAGENAMEBACK				57		// �����̸� ���.  

#define GIMG_FIRE1							58		// ��1
#define GIMG_FIRE2							59		// ��2
#define GIMG_FIRE3							60		// ��3
#define GIMG_FIRE4							61		// ��4

#define GIMG_NOFIRSTATTACK					62		// ���� ��� ȿ��. 

#define GIMG_RANKMARK						63		// ���ڵ��� �ź� ǥ��.

#define GIMG_HEAL							64		// ü�� ȸ�� ���� ȿ��. 

#define GIMG_MAKEITEMDRAWPART1				65		// ��ǰ ���� ��� ����(1ĭ¥��)
#define GIMG_MAKEITEMDRAWPART2				66		// ��ǰ ���� ��� ����(Ʋ)
#define GIMG_MAKEITEMDRAWPART3				67		// ��ǰ ���� ��� ����(����)

#define GIMG_PARTYEMOTICON					68		// ��Ƽ ����� ���� �����ִ� ��

#define GIMG_GAMESTATUS						69		// ������ ���¿� ���� ȭ�鿡 �����ش�. (������, ���ʽ��ð�)
#define GIMG_KINGEFFECT						70		// ������ ����� Effect
#define GIMG_GODEFFECT						71		// ��Ȳ�� ���� ����� Effect

#define GIMG_FRIENDLOGIN					72		// ģ�� �α��� �Ҷ� ���� �� �κ�

#define GIMG_NAESI							73		// ���� �̹���
#define GIMG_ICEFROZEN						74		// ������ ������� 
#define GIMG_MAGIC_DRAIN					75		//  
#define GIMG_HEALCOUNTER					76		// HEAL COUNT

#define GIMG_VILLAGENOTICEBACKGROUND		77		// ���� ������

#define GIMG_MAGIC_POISONFLAME				87		// MAGIC_STAFF_POISONFLAME �ߵ����� 

#define GIMG_SYIDEOCK						88		// ��ô�
#define GIMG_NOICEATTACK					89		// ICE ��� ȿ��. 
#define GIMG_SUMMONMARK						90		// ��ȯ�� ��ũ 

#define GIMG_VILLAGEMARK01					91		// ���(����) ��ũ
#define GIMG_MAGIC_DRAGONCANNON				92		// 
#define GIMG_MAGIC_DRAGONSHADOW				93		// 

#define GIMG_GWANGGAETO_EFFECT				94		//
#define GIMG_MAGIC_DROPMONEY				95		// ���� ������ 
#define GIMG_MAGIC_BLACKINK					96		// ���� �Թ� 
#define GIMG_MAGIC_DROPSNOWMAN				97		// ���� ����� ������ 

#define GIMG_MAGIC_DROPFORK_FRONT			98		// ���� ���� ������ 
#define GIMG_MAGIC_DROPFORK_BACK			99		// ���� ���� ������ 


#define GIMG_RESIDENCELOGIN					100		// ���� �ֹ� �α��� �Ҷ� ���� �� �κ�

#define GIMG_MAGIC_CURSEATTACK				101		// ���ݷ� ���� 
#define GIMG_MAGIC_CURSECRITICAL			102		// Critical ���� 
#define GIMG_MAGIC_CURSEDEFENSE				103		// ���� ���� 
#define GIMG_MAGIC_CURSEMOVESPEED			104		// �̵��ӵ� ���� 

//#define GIMG_ITEMIMG0						105		// ������ �̹���. 
//#define GIMG_ITEMIMG1						106		// ������ �̹���. 
//#define GIMG_ITEMIMG2						107		// ������ �̹���. 
//#define GIMG_ITEMIMG3						116		// ������ �̹���. 

#define GMIG_MAGIC_SWORDBOMB1				108		// �������� 
#define GMIG_MAGIC_SWORDBOMB2				109

#define GIMG_NOTICEEVENT_STAMP1				110		// ���� ��� �̺�Ʈ1
#define GIMG_NOTICEEVENT_STAMP2				111		// ���� ��� �̺�Ʈ2
#define GIMG_NOTICEEVENT_STAMP3				112		// ���� ��� �̺�Ʈ3

#define GIMG_HUMAN_EFFECT					113		// Ư���� ĳ���Ϳ��� ��� �̹���

#define GIMG_MAKEMASTER						114		// �ְ� ���� ���� ǥ�� 


#define GIMG_INTERFACE_CLOSEBUTTON			115		// Interface CloseButton

#define GIMG_MAGIC_UPPERDRAGON1				118		// �庸�� ����1
#define GIMG_MAGIC_UPPERDRAGON2				119		// �庸�� ����2
#define GIMG_MAGIC_UPPERDRAGON3				120		// �庸�� ����3

#define GIMG_FOG							121		// ����
#define GIMG_PCROOM_MARK					122		// ĳ���� ���� pc�� ǥ��
#define GIMG_PCROOM_STATUS					123		// ȭ�鿡 pc�� ǥ��

#define GIMG_MAGICFIRE						124		// ���� �ٴ� ������ ��
#define GIMG_MAGICFIRE_BURN					125		// ����Ƽ ����
#define GIMG_MAGICFIRE_BURNRING				126		// ����Ƽ ������
#define GIMG_VILLAGEUNITNPC					127		// �ǹ� �ʻ�

#define GIMG_JINSOO							128		// ����
#define GIMG_SYIDEOCKCRY					129		// �ô� ��� ���

#define GIMG_SWORDMETEOR					130		// ���ϼ�����
#define GIMG_MAGICFROZEN					131		// ������ �������� ����� ��

#define GIMG_MAGIC_FIREWHIRLWIND			132		// �����ٶ� ����

#define GIMG_NEW_ATTACK_STAFF				133		// �ָ�, ������
#define GIMG_NEW_ATTACK_SWORD				134		// ��
#define GIMG_NEW_ATTACK_SPEAR				135		// â
#define GIMG_NEW_ATTACK_AXE					136		// ����
#define GIMG_NEW_ATTACK_BOWGUN				137		// Ȱ, ��

#define GIMG_NEW_ATTACK_STAFF2				138		// �ָ�, ������
#define GIMG_NEW_ATTACK_SWORD2				139		// ��
#define GIMG_NEW_ATTACK_SPEAR2				140		// â
#define GIMG_NEW_ATTACK_AXE2				141		// ����
#define GIMG_NEW_ATTACK_BOWGUN2				142		// Ȱ, ��

#define GIMG_MAGIC_SUMMONDRAGON				143		// ��ù� ����

#define GIMG_SETITEMEFFECT1					144		// ��Ʈ������1
#define GIMG_SETITEMEFFECT2					145		// ��Ʈ������

#define GIMG_MAGIC_EARTHQUAKE				146		// ������

//#define GIMG_ARROW							147		// NPC ���� ���� ȭ��ǥ
//#define GIMG_ARROWEFFECT					147		// NPC ���� ���� ȭ��ǥ ����Ʈ
#define GIMG_QUESTNPCEFFECT					147		// NPC ���� ���� ����Ʈ ����Ʈ
#define GIMG_CLICKMOUSE						148		// NPC ���� ���� ȭ��ǥ ����Ʈ

#define GIMG_PREMIUM_STATUS					149	// �����̾� ����

#define GIMG_MAGIC_THUNDER1					150

#define GIMG_RANKING						151		// ���� ��ŷ �̹���
#define GIMG_MVPMARK1						152		// ���� MVP �̹���
#define GIMG_GMMARK							153		// GM �̹���
#define GIMG_MVP_EFFECT						154		// MVP ������ ����Ʈ
#define GIMG_MVP_AROUND_EFFECT				155		// MVP ������ ������ �ѷ����� ����Ʈ

#define GIMG_SEEDDROP1						156		// Ȧ��1
#define GIMG_SEEDDROP2						157		// Ȧ��2
#define GIMG_SEEDDROP3						158		// Ȧ��3
#define GIMG_SEEDDROP4						159		// Ȧ��4

#define GIMG_ITEMSEALED						160		// �����ۺ����̹���

#define GIMG_MAGIC_FROZENGOLEM				161		// ������� ����
#define GIMG_MAGIC_FROZENQUEEN				162		// �������� ����
#define GIMG_MAGIC_FROZENSORCERER			163		// ������Ҽ��� ����
#define GIMG_MAGIC_GOTPA					164		// ��õ���� ����

#define GIMG_ENCHANT_EFFECT_HERO_WE			165		// ��þƮ ����Ʈ ���� ����
#define GIMG_ENCHANT_EFFECT_HERO_AM			166		// ��þƮ ����Ʈ ���� ��
#define GIMG_ENCHANT_EFFECT_HEROINE_WE		167		// ��þƮ ����Ʈ ���� ����
#define GIMG_ENCHANT_EFFECT_HEROINE_AM		168		// ��þƮ ����Ʈ ���� ��

#define GIMG_MAGIC_DRACULA					169		// ���ŧ�� ����
#define GIMG_MAGIC_DRACULAFX				170		// ���ŧ�� ���� FX

#define	GIMG_MAGIC_PRIEST					171		// Ÿ�������� ����

#define	GIMG_BUFIMAGE						172		// �����̹�����
#define GIMG_BEGINWARP						173		// �����̹���

#define GIMG_QUEST_EFFECT_RECEIVE				174		// ����Ʈ �ޱ� ����Ʈ
#define GIMG_QUEST_EFFECT_CLEAR					175		// ����Ʈ Ŭ���� ����Ʈ

#define GIMG_ITEMIMG01						181		// ������ �̹���. 
#define GIMG_ITEMIMG02						182		// ������ �̹���. 
#define GIMG_ITEMIMG03						183		// ������ �̹���. 
#define GIMG_ITEMIMG04						184		// ������ �̹���. 
#define GIMG_ITEMIMG05						185		// ������ �̹���. 
#define GIMG_ITEMIMG06						186		// ������ �̹���. 
#define GIMG_ITEMIMG07						187		// ������ �̹���. 
#define GIMG_ITEMIMG08						188		// ������ �̹���. 
#define GIMG_ITEMIMG09						189		// ������ �̹���. 
#define GIMG_ITEMIMG10						190		// ������ �̹���. 
#define GIMG_ITEMIMG11						191		// ������ �̹���. 
#define GIMG_ITEMIMG12						192		// ������ �̹���. 
#define GIMG_ITEMIMG13						193		// ������ �̹���. 
#define GIMG_ITEMIMG14						194		// ������ �̹���. 
#define GIMG_ITEMIMG15						195		// ������ �̹���. 
#define GIMG_ITEMIMG16						196		// ������ �̹���. 
#define GIMG_ITEMIMG17						197		// ������ �̹���. 
#define GIMG_ITEMIMG18						198		// ������ �̹���. 
#define GIMG_ITEMIMG19						199		// ������ �̹���. 
#define GIMG_ITEMIMG20						200		// ������ �̹���. 
#define GIMG_VILLAGEWAR_NOTICE				201		// ������ �̹���. 

#define GIMG_MAGIC_MANDRAGORA				202		// ������� ���� �̹���.
#define GIMG_BUFPERCENT						203		// ���� �̹��� �ؿ� ȿ�� %��ġ

#define GIMG_SKILLLEVELUP_EFF				204		// ��ų������ ����Ʈ
#define GIMG_LEVELUP_EFF					205		// ��ų������ ����Ʈ

#define GIMG_CHRISTMAS_BUF					206		// ��ų������ ����Ʈ

#define GIMG_GUILDWAR_NOTICE				207		// ����� ���� �̹���
#define GIMG_GUILDWAR_COUNT					208		// ����� ���� �̹���

#define GIMG_NEWYEAR_EVENT_NOTICE			209

#define GIMG_SUMMON_EVENT_BUF				210
#define GIMG_EMOTICON						211		// �̸�Ƽ��

#define GIMG_MAGIC_PAPAGOBIN				212		//���İ�� ���� �̹���. 
#define GIMG_HEART_EFFECT					213		// �ٴ� ��Ʈ ����Ʈ
#define GIMG_EMOTICON_SMALL					214		// ä�� �̸�Ƽ��

#define GIMG_MISSHIT						215		// ä�� �̸�Ƽ��
	
#define GIMG_HORSEWING1						216		// �� ���� �̹���1 ( 1~8���� ���ӵ� ���� ������ �մϴ�)
#define GIMG_HORSEWING2						217		// �� ���� �̹���2
#define GIMG_HORSEWING3						218		// �� ���� �̹���3
#define GIMG_HORSEWING4						219		// �� ���� �̹���4
#define GIMG_HORSEWING5						220		// �� ���� �̹���5
#define GIMG_HORSEWING6						221		// �� ���� �̹���6
#define GIMG_HORSEWING7						222		// �� ���� �̹���7
#define GIMG_HORSEWING8						223		// �� ���� �̹���8

#define GIMG_QUESTARROW						224		// ����Ʈ ���� ǥ��

#define GIMG_FOURLEAF						225		// ���� Ŭ�ι�

#define GIMG_GOVERNMENT_RANKMARK			226		// ������ ���ǥ��

#define GIMG_CUSHION_1						227		// ��� �̹��� 1
#define GIMG_CUSHION_2						228		// ��� �̹��� 2
#define GIMG_CUSHION_3						229		// ��� �̹��� 3
#define GIMG_CUSHION_4						230		// ��� �̹��� 4

#define GIMG_CUSHION_CAT_1					231		// ��� ����� �̹��� 1
#define GIMG_CUSHION_CAT_2					232		// ��� ����� �̹��� 2
#define GIMG_CUSHION_CAT_3					233		// ��� ����� �̹��� 3
#define GIMG_CUSHION_CAT_4					234		// ��� ����� �̹��� 4

#define GIMG_SPECIAL_PCROOM_MARK_1			235		// ����_����� PC�� ��ũ(�����̵�������)
#define GIMG_SPECIAL_PCROOM_MARK_2			236		// ����_����� PC�� ��ũ(��ɰ���ġ)

#define GIMG_SPECIAL_PCROOM_LARGE_MARK		237		// 
#define GIMG_SPECIAL_NO_PCROOM_LARGE_MARK	238		// 

#define GIMG_DAMAGE_PC_0					239
#define GIMG_DAMAGE_PC_1					240
#define GIMG_DAMAGE_PC_2					241
#define GIMG_DAMAGE_PC_3					242
#define GIMG_DAMAGE_PC_4					243
#define GIMG_DAMAGE_PC_5					244
#define GIMG_DAMAGE_PC_6					245
#define GIMG_DAMAGE_PC_7					246
#define GIMG_DAMAGE_PC_8					247
#define GIMG_DAMAGE_PC_9					248
#define GIMG_DAMAGE_NPC_0					249
#define GIMG_DAMAGE_NPC_1					250
#define GIMG_DAMAGE_NPC_2					251
#define GIMG_DAMAGE_NPC_3					252
#define GIMG_DAMAGE_NPC_4					253
#define GIMG_DAMAGE_NPC_5					254
#define GIMG_DAMAGE_NPC_6					255
#define GIMG_DAMAGE_NPC_7					256
#define GIMG_DAMAGE_NPC_8					257
#define GIMG_DAMAGE_NPC_9					258
#define GIMG_DAMAGE_PC_MISS					259
#define GIMG_DAMAGE_NPC_MISS				260
#define GIMG_DAMAGE_CRITICAL				261

#define GIMG_ITEMEXPIRED					262
#define GIMG_ITEMCANNOTEQIP					263

//KHY - 1109 - ��í����- �������漮�߰�
#define GIMG_CUSHIOND_1						264		// ��� �̹��� 5
#define GIMG_CUSHIOND_2						265		// ��� �̹��� 6
#define GIMG_CUSHIOND_3						266		// ��� �̹��� 7
#define GIMG_CUSHIOND_4						267		// ��� �̹��� 8

#define GIMG_CUSHION_DOG_1					268		// ��� ������ �̹��� 1
#define GIMG_CUSHION_DOG_2					269		// ��� ������ �̹��� 2
#define GIMG_CUSHION_DOG_3					270		// ��� ������ �̹��� 3
#define GIMG_CUSHION_DOG_4					271		// ��� ������ �̹��� 4

#define GIMG_VILLAGEMARK02					272		// ���(����) ��ũ2
#define GIMG_VILLAGEMARK03					273		// ���(����) ��ũ3

// [����] PC�� �����̾� ��ȭ(����,���ٰ��� PC�� ��ũ �߰�) - 2008.03.02
#define GIMG_SPECIAL_PCROOM_MARK_3			274		// ����_����� PC�� ��ũ(��������ġ)
#define GIMG_SPECIAL_PCROOM_MARK_4			275		// ����_����� PC�� ��ũ(����Ŭ�ι�����)

//KHY - 0313 - ���� 100%ȿ�� �߻�.
#define GIMG_TRANSFORM_SYNCHRO100			276		// ���� 100% ȿ�� 

//PCK : �밻�� ���� �߰� (08.03.23)
#define GIMG_MAGIC_EMPERORMASTER			277		// �밻�� ����

// [����] ��Ƽ��Ʈ ���� �̹��� �߰�.
#define GIMG_ARTIFACT_SLOT_STATUS			278
#define GIMG_ARTIFACT_GAUGE_BACK			279	
#define GIMG_ARTIFACT_GAUGE					280
#define GIMG_ARTIFACT_SLOT_EFFECT			281
#define GIMG_ARTIFACT_SLOT_REMOVE			282

// PCK : ������ ���� �߰� (08.04.11)
#define GIMG_MAGIC_GREATWALLSOLDIER		283
#define GIMG_MAGIC_GREATWALLSOLDIERFX	284

// PCK : �Ӹ��� ���� �߰� (08.04.11)
#define GIMG_MAGIC_GREATWALLMAGICIAN	285

// [����] ȭ��ǥ ���Դ� ������ �̹���.
#define GIMG_ARROW_IN_OUT				286
*/
enum GLOBAL_IMAGE
{
	GIMG_CHARSHADOW						= 0,
	GIMG_POISON							= 1,		
	GIMG_SETITEM_POISON,
	GIMG_CUT,
	GIMG_EXPCOUNTER,
	GIMG_WATERDROP,
	GIMG_HELPPANNEL,
	GIMG_DMGCOUNTER,
	GIMG_FIELDITEM,
	GIMG_LEVELUP,
	GIMG_REGENERATION,
	GIMG_FIREFLY,								// �ݵ���
	GIMG_BIGBOSS,								// �����
	GIMG_SMALLBOSS,								// ���
	GIMG_CRITICALEFFECT,						// �ʻ��
	GIMG_CLICKPOINT,							// ���콺 Ŭ��
	GIMG_MONSTERINFOBACK,						// ���� ����â�� �ִ� ���� �̹��� ���	
	GIMG_WARKILL,								// ���￡�� óġ�� ������ ���. 
	GIMG_WARKILLNUM,							// ���￡�� óġ�� ������ ��. 
	GIMG_JIM,									// ��ų ������ ���� ��
	GIMG_SKILLLEVELUP,							// ��ų ���� ��
	GIMG_ICEFLASH,								// ������ ��¦��

	GIMG_SERVERNAME,							// ���� �̸�
	GIMG_SKILLNAME,								// ��ų��
	GIMG_SKILLEXPCOUNTER,						// ��ų Counter

	// ĳ���� Ư�� ����Ʈ ���� - ���� ���̰� ����
	GIMG_SPECIAL_SWORD,							// �� ����
	GIMG_SPECIAL_SPEAR_BRANDISH,				// ��� �ֵθ��� â ����
	GIMG_SPECIAL_SPEAR_JAB,						// ��� ��� â ����
	GIMG_SPECIAL_AXE,							// ���� ����

	GIMG_SPECIAL_SWORD_HORSE,					// �� �� ����
	GIMG_SPECIAL_SPEAR_BRANDISH_HORSE,			// �� ��� �ֵθ��� â ����
	GIMG_SPECIAL_SPEAR_JAB_HORSE,				// �� ��� ��� â ����
	GIMG_SPECIAL_AXE_HORSE,						// �� ���� ����

	GIMG_SPECIAL_SWORDDMG,						// �� ���ݿ� ����
	GIMG_SPECIAL_SPEARDMG_BRANDISH,				// ��� �ֵθ��� â ���ݿ� ����
	GIMG_SPECIAL_SPEARDMG_JAB,					// ��� ��� ���ݿ� ����
	GIMG_SPECIAL_AXEDMG,						// ���� ���ݿ� ����

	// �б� ����
	GIMG_SCHOOL1,								// �б� �ΰ� 1
	GIMG_SCHOOL2,								// �б� �ΰ� 2
	GIMG_SCHOOL3,								// �б� �ΰ� 3

	GIMG_MAGIC_THUNDER,

	GIMG_MAGIC_ROCKSLIDE,						// ���� ����
	GIMG_MAGIC_FLAME,
	GIMG_MAGIC_WHIRLPOOL,

	GIMG_MAGIC_WAR,

	GIMG_MAGIC_PROMPTBAR,

	GIMG_MAGIC_DEFUP,							// ���� ���. 

	GIMG_VILLAGENAMEBACK,						// �����̸� ���.  

	GIMG_FIRE1,									// ��1
	GIMG_FIRE2,									// ��2
	GIMG_FIRE3,									// ��3
	GIMG_FIRE4,									// ��4

	GIMG_NOFIRSTATTACK,							// ���� ��� ȿ��. 

	GIMG_RANKMARK,								// ���ڵ��� �ź� ǥ��.

	GIMG_HEAL,									// ü�� ȸ�� ���� ȿ��. 

	GIMG_MAKEITEMDRAWPART1,						// ��ǰ ���� ��� ����(1ĭ¥��)
	GIMG_MAKEITEMDRAWPART2,						// ��ǰ ���� ��� ����(Ʋ)
	GIMG_MAKEITEMDRAWPART3,						// ��ǰ ���� ��� ����(����)

	GIMG_PARTYEMOTICON,							// ��Ƽ ����� ���� �����ִ� ��

	//GIMG_GAMESTATUS,							// ������ ���¿� ���� ȭ�鿡 �����ش�. (������, ���ʽ��ð�)
	GIMG_KINGEFFECT,							// ������ ����� Effect
	GIMG_GODEFFECT,								// ��Ȳ�� ���� ����� Effect

	GIMG_FRIENDLOGIN,							// ģ�� �α��� �Ҷ� ���� �� �κ�

	GIMG_NAESI,									// ���� �̹���
	GIMG_ICEFROZEN,								// ������ ������� 
	GIMG_MAGIC_DRAIN,
	GIMG_HEALCOUNTER,							// HEAL COUNT

	GIMG_VILLAGENOTICEBACKGROUND,				// ���� ������

	GIMG_MAGIC_POISONFLAME,						// MAGIC_STAFF_POISONFLAME �ߵ����� 

	GIMG_SYIDEOCK,								// ��ô�
	GIMG_NOICEATTACK,							// ICE ��� ȿ��. 
	GIMG_SUMMONMARK,							// ��ȯ�� ��ũ 

	GIMG_VILLAGEMARK01,							// ���(����) ��ũ
	GIMG_MAGIC_DRAGONCANNON,
	GIMG_MAGIC_DRAGONSHADOW,

	GIMG_GWANGGAETO_EFFECT,
	GIMG_MAGIC_DROPMONEY,						// ���� ������ 
	GIMG_MAGIC_BLACKINK,						// ���� �Թ� 
	GIMG_MAGIC_DROPSNOWMAN,						// ���� ����� ������ 

	GIMG_MAGIC_DROPFORK_FRONT,					// ���� ���� ������ 
	GIMG_MAGIC_DROPFORK_BACK,					// ���� ���� ������ 

	GIMG_RESIDENCELOGIN,						// ���� �ֹ� �α��� �Ҷ� ���� �� �κ�

	GIMG_MAGIC_CURSEATTACK,						// ���ݷ� ���� 
	GIMG_MAGIC_CURSECRITICAL,					// Critical ���� 
	GIMG_MAGIC_CURSEDEFENSE,					// ���� ���� 
	GIMG_MAGIC_CURSEMOVESPEED,					// �̵��ӵ� ���� 

	GMIG_MAGIC_SWORDBOMB1,						// �������� 
	GMIG_MAGIC_SWORDBOMB2,
	
	GIMG_MAGIC_SKILL_BOOK_ICERAIN,				// ��ų�� ����.
	GIMG_MAGIC_SKILL_BOOK_CRASH,	
	GIMG_MAGIC_SKILL_BOOK_TORNADO,


	GIMG_NOTICEEVENT_STAMP1,					// ���� ��� �̺�Ʈ1
	GIMG_NOTICEEVENT_STAMP2,					// ���� ��� �̺�Ʈ2
	GIMG_NOTICEEVENT_STAMP3,					// ���� ��� �̺�Ʈ3

	GIMG_HUMAN_EFFECT,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT1,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT2,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT3,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT4,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT5,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT6,							// Ư���� ĳ���Ϳ��� ��� �̹���
	GIMG_HUMAN_EFFECT7,							// Ư���� ĳ���Ϳ��� ��� �̹���
	
	GIMG_MAKEMASTER,							// �ְ� ���� ���� ǥ�� 

	GIMG_INTERFACE_CLOSEBUTTON,					// Interface CloseButton

	GIMG_MAGIC_UPPERDRAGON1,					// �庸�� ����1
	GIMG_MAGIC_UPPERDRAGON2,					// �庸�� ����2
	GIMG_MAGIC_UPPERDRAGON3,					// �庸�� ����3

	GIMG_FOG,									// ����
	GIMG_PCROOM_MARK,							// ĳ���� ���� pc�� ǥ��
	GIMG_PCROOM_STATUS,							// ȭ�鿡 pc�� ǥ��

	GIMG_MAGICFIRE,								// ���� �ٴ� ������ ��
	GIMG_MAGICFIRE_BURN,						// ����Ƽ ����
	GIMG_MAGICFIRE_BURNRING,					// ����Ƽ ������
	GIMG_VILLAGEUNITNPC,						// �ǹ� �ʻ�

	GIMG_JINSOO,								// ����
	GIMG_SYIDEOCKCRY,							// �ô� ��� ���

	GIMG_SWORDMETEOR,							// ���ϼ�����
	GIMG_MAGICFROZEN,							// ������ �������� ����� ��

	GIMG_MAGIC_FIREWHIRLWIND,					// �����ٶ� ����

	GIMG_NEW_ATTACK_STAFF,						// �ָ�, ������
	GIMG_NEW_ATTACK_SWORD,						// ��
	GIMG_NEW_ATTACK_SPEAR,						// â
	GIMG_NEW_ATTACK_AXE,						// ����
	GIMG_NEW_ATTACK_BOWGUN,						// Ȱ, ��

	GIMG_NEW_ATTACK_STAFF2,						// �ָ�, ������
	GIMG_NEW_ATTACK_SWORD2,						// ��
	GIMG_NEW_ATTACK_SPEAR2,						// â
	GIMG_NEW_ATTACK_AXE2,						// ����
	GIMG_NEW_ATTACK_BOWGUN2,					// Ȱ, ��

	GIMG_MAGIC_SUMMONDRAGON,					// ��ù� ����

	GIMG_MAGIC_EARTHQUAKE,						// ������

	GIMG_QUESTNPCEFFECT,						// NPC ���� ���� ����Ʈ ����Ʈ
	GIMG_CLICKMOUSE,							// NPC ���� ���� ȭ��ǥ ����Ʈ

	GIMG_PREMIUM_STATUS,						// �����̾� ����

	GIMG_MAGIC_THUNDER1,

	GIMG_RANKING,								// ���� ��ŷ �̹���
	GIMG_MVPMARK1,								// ���� MVP �̹���
	GIMG_GMMARK,								// GM �̹���
	GIMG_MVP_EFFECT,							// MVP ������ ����Ʈ
	GIMG_MVP_AROUND_EFFECT,						// MVP ������ ������ �ѷ����� ����Ʈ

	GIMG_SEEDDROP1,								// Ȧ��1
	GIMG_SEEDDROP2,								// Ȧ��2
	GIMG_SEEDDROP3,								// Ȧ��3
	GIMG_SEEDDROP4,								// Ȧ��4

	GIMG_ITEMSEALED,							// �����ۺ����̹���

	GIMG_MAGIC_FROZENGOLEM,						// ������� ����
	GIMG_MAGIC_FROZENQUEEN,						// �������� ����
	GIMG_MAGIC_FROZENSORCERER,					// ������Ҽ��� ����
	GIMG_MAGIC_GOTPA,							// ��õ���� ����

	GIMG_ENCHANT_EFFECT_HERO_WE,				// ��þƮ ����Ʈ ���� ����
	GIMG_ENCHANT_EFFECT_HERO_AM,				// ��þƮ ����Ʈ ���� ��
	GIMG_ENCHANT_EFFECT_HEROINE_WE,				// ��þƮ ����Ʈ ���� ����
	GIMG_ENCHANT_EFFECT_HEROINE_AM,				// ��þƮ ����Ʈ ���� ��

	GIMG_MAGIC_DRACULA,							// ���ŧ�� ����
	GIMG_MAGIC_DRACULAFX,						// ���ŧ�� ���� FX

	GIMG_MAGIC_PRIEST,							// Ÿ�������� ����

	GIMG_BUFIMAGE,								// �����̹�����
	GIMG_BEGINWARP,								// �����̹���

	GIMG_QUEST_EFFECT_RECEIVE,					// ����Ʈ �ޱ� ����Ʈ
	GIMG_QUEST_EFFECT_CLEAR,					// ����Ʈ Ŭ���� ����Ʈ

	GIMG_ITEMIMG01,								// ������ �̹���. 
	GIMG_ITEMIMG02,								// ������ �̹���. 
	GIMG_ITEMIMG03,								// ������ �̹���. 
	GIMG_ITEMIMG04,								// ������ �̹���. 
	GIMG_ITEMIMG05,								// ������ �̹���. 
	GIMG_ITEMIMG06,								// ������ �̹���. 
	GIMG_ITEMIMG07,								// ������ �̹���. 
	GIMG_ITEMIMG08,								// ������ �̹���. 
	GIMG_ITEMIMG09,								// ������ �̹���. 
	GIMG_ITEMIMG10,								// ������ �̹���. 
	GIMG_ITEMIMG11,								// ������ �̹���. 
	GIMG_ITEMIMG12,								// ������ �̹���. 
	GIMG_ITEMIMG13,								// ������ �̹���. 
	GIMG_ITEMIMG14,								// ������ �̹���. 
	GIMG_ITEMIMG15,								// ������ �̹���. 
	GIMG_ITEMIMG16,								// ������ �̹���. 
	GIMG_ITEMIMG17,								// ������ �̹���. 
	GIMG_ITEMIMG18,								// ������ �̹���. 
	GIMG_ITEMIMG19,								// ������ �̹���. 
	GIMG_ITEMIMG20,								// ������ �̹���. 
	GIMG_VILLAGEWAR_NOTICE,						// ������ �̹���. 

	GIMG_MAGIC_MANDRAGORA,						// ������� ���� �̹���.
	GIMG_BUFPERCENT,							// ���� �̹��� �ؿ� ȿ�� %��ġ

	GIMG_SKILLLEVELUP_EFF,						// ��ų������ ����Ʈ
	GIMG_LEVELUP_EFF,							// ��ų������ ����Ʈ

	GIMG_CHRISTMAS_BUF,							// ��ų������ ����Ʈ

	GIMG_GUILDWAR_NOTICE,						// ����� ���� �̹���
	GIMG_GUILDWAR_COUNT,						// ����� ���� �̹���

	GIMG_NEWYEAR_EVENT_NOTICE,

	GIMG_SUMMON_EVENT_BUF,
	GIMG_EMOTICON,								// �̸�Ƽ��
	GIMG_VALENTINEEMOTICON,						// �߷�Ÿ�� �̸�Ƽ��

	GIMG_MAGIC_PAPAGOBIN,						// ���İ�� ���� �̹���. 
	GIMG_HEART_EFFECT,							// �ٴ� ��Ʈ ����Ʈ
	GIMG_EMOTICON_SMALL,						// ä�� �̸�Ƽ��

	GIMG_MISSHIT,								// ä�� �̸�Ƽ��

	GIMG_HORSEWING1,							// �� ���� �̹���1 ( 1~8���� ���ӵ� ���� ������ �մϴ�)
	GIMG_HORSEWING2,							// �� ���� �̹���2
	GIMG_HORSEWING3,							// �� ���� �̹���3
	GIMG_HORSEWING4,							// �� ���� �̹���4
	GIMG_HORSEWING5,							// �� ���� �̹���5
	GIMG_HORSEWING6,							// �� ���� �̹���6
	GIMG_HORSEWING7,							// �� ���� �̹���7
	GIMG_HORSEWING8,							// �� ���� �̹���8

	GIMG_QUESTARROW,							// ����Ʈ ���� ǥ��

	GIMG_FOURLEAF,								// ���� Ŭ�ι�

	GIMG_GOVERNMENT_RANKMARK,					// ������ ���ǥ��

	GIMG_CUSHION_1,								// ��� �̹��� 1
	GIMG_CUSHION_2,								// ��� �̹��� 2
	GIMG_CUSHION_3,								// ��� �̹��� 3
	GIMG_CUSHION_4,								// ��� �̹��� 4

	GIMG_CUSHION_CAT_1,							// ��� ����� �̹��� 1
	GIMG_CUSHION_CAT_2,							// ��� ����� �̹��� 2
	GIMG_CUSHION_CAT_3,							// ��� ����� �̹��� 3
	GIMG_CUSHION_CAT_4,							// ��� ����� �̹��� 4

	GIMG_SPECIAL_PCROOM_MARK_1,					// ����_����� PC�� ��ũ(�����̵�������)
	GIMG_SPECIAL_PCROOM_MARK_2,					// ����_����� PC�� ��ũ(��ɰ���ġ)

	GIMG_SPECIAL_PCROOM_LARGE_MARK,				// 
	GIMG_SPECIAL_NO_PCROOM_LARGE_MARK,			// 

	GIMG_DAMAGE_PC_0,
	GIMG_DAMAGE_PC_1,
	GIMG_DAMAGE_PC_2,
	GIMG_DAMAGE_PC_3,
	GIMG_DAMAGE_PC_4,
	GIMG_DAMAGE_PC_5,
	GIMG_DAMAGE_PC_6,
	GIMG_DAMAGE_PC_7,
	GIMG_DAMAGE_PC_8,
	GIMG_DAMAGE_PC_9,
	GIMG_DAMAGE_NPC_0,
	GIMG_DAMAGE_NPC_1,
	GIMG_DAMAGE_NPC_2,
	GIMG_DAMAGE_NPC_3,
	GIMG_DAMAGE_NPC_4,
	GIMG_DAMAGE_NPC_5,
	GIMG_DAMAGE_NPC_6,
	GIMG_DAMAGE_NPC_7,
	GIMG_DAMAGE_NPC_8,
	GIMG_DAMAGE_NPC_9,
	GIMG_DAMAGE_PC_MISS,
	GIMG_DAMAGE_NPC_MISS,
	GIMG_DAMAGE_CRITICAL,

	GIMG_ITEMEXPIRED,
	GIMG_ITEMCANNOTEQIP,

	//KHY - 1109 - ��í����- �������漮�߰�
	GIMG_CUSHIOND_1,							// ��� �̹��� 5
	GIMG_CUSHIOND_2,							// ��� �̹��� 6
	GIMG_CUSHIOND_3,							// ��� �̹��� 7
	GIMG_CUSHIOND_4,							// ��� �̹��� 8

	GIMG_CUSHION_DOG_1,							// ��� ������ �̹��� 1
	GIMG_CUSHION_DOG_2,							// ��� ������ �̹��� 2
	GIMG_CUSHION_DOG_3,							// ��� ������ �̹��� 3
	GIMG_CUSHION_DOG_4,							// ��� ������ �̹��� 4

	GIMG_VILLAGEMARK02,							// ���(����) ��ũ2
	GIMG_VILLAGEMARK03,							// ���(����) ��ũ3

	// [����] PC�� �����̾� ��ȭ(����,���ٰ��� PC�� ��ũ �߰�) - 2008.03.02
	GIMG_SPECIAL_PCROOM_MARK_3,					// ����_����� PC�� ��ũ(��������ġ)
	GIMG_SPECIAL_PCROOM_MARK_4,					// ����_����� PC�� ��ũ(����Ŭ�ι�����)

	//KHY - 0313 - ���� 100%ȿ�� �߻�.
	GIMG_TRANSFORM_SYNCHRO100,					// ���� 100% ȿ�� 

	//PCK : �밻�� ���� �߰� (08.03.23)
	GIMG_MAGIC_EMPERORMASTER,					// �밻�� ����

	// [����] ��Ƽ��Ʈ ���� �̹��� �߰�.
	GIMG_ARTIFACT_SLOT_STATUS,
	GIMG_ARTIFACT_GAUGE_BACK,
	GIMG_ARTIFACT_GAUGE,
	GIMG_ARTIFACT_SLOT_EFFECT,
	GIMG_ARTIFACT_SLOT_REMOVE,

	// PCK : ������ ���� �߰� (08.04.11)
	GIMG_MAGIC_GREATWALLSOLDIER,
	GIMG_MAGIC_GREATWALLSOLDIERFX,

	// PCK : �Ӹ��� ���� �߰� (08.04.11)
	GIMG_MAGIC_GREATWALLMAGICIAN,

	// [����] ȭ��ǥ ���Դ� ������ �̹���.
	GIMG_ARROW_IN_OUT,

	// PCK : ���� ���� �߰� (08.05.28)
	GIMG_MAGIC_GREATWALLSPIDER,

	// [����] �귿 �ֻ��� => 2008-7-8
	GIMG_MAGIC_DICE,

	// [����] NPC�ʻ� �����̹���(40x40)
	GIMG_PORTRAIT_SMALL01,
	GIMG_PORTRAIT_SMALL02,

	GIMG_GACHASUMMON_EFFECT,

	GIMG_MARKETCONDITIONS_ICON,

	// PCK : ��ȯ���� �������, �������� �߰�
	GIMG_MAGIC_SFROZENGOLEM,					
	GIMG_MAGIC_SFROZENQUEEN,	

	//[����] ������ �̹��� ū��. => 2008-9-23
	GIMG_ITEMIMAGEBIG01,
	
	GIMG_SETITEME0,								// ��Ʈ������1
	GIMG_SETITEME2,								// ��Ʈ������1
	GIMG_SETITEME3,								// ��Ʈ������1
	GIMG_SETITEME4,								// ��Ʈ������1
	GIMG_SETITEME5,								// ��Ʈ������1
	GIMG_SETITEME6,								// ��Ʈ������1
	GIMG_SETITEME7,								// ��Ʈ������1
	GIMG_SETITEMEFFECT0,						// ��Ʈ������1
	GIMG_SETITEMEFFECT2,						// ��Ʈ������
	GIMG_SETITEMEFFECT3,						// ��Ʈ������
	GIMG_SETITEMEFFECT4,						// ��Ʈ������
	GIMG_SETITEMEFFECT5,						// ��Ʈ������
	GIMG_SETITEMEFFECT6,						// ��Ʈ������
	GIMG_SETITEMEFFECT7,						// ��Ʈ������

	// [����] PVP�� ī��Ʈ �ٿ�,
	GIMG_PVP_COUNTDOWN,
	// [����] ���� ���� ����Ʈ
	GIMG_MAGIC_BLESSDAMAGE,
	GIMG_MAGIC_BLESSCIRICAL1,
	GIMG_MAGIC_BLESSCIRICAL2,
	GIMG_MAGIC_BLESSHITRATE,
	GIMG_MAGIC_BLESSRANGE,
	GIMG_MAGIC_BLESSATTACKINTERVAL,
	GIMG_MAGIC_BLESSMPRECOVERYTIME,
	GIMG_MAGIC_BLESSHP,

	GIMG_MAGIC_AURABLADE,
	// PVP �¸� �й� ��� ǥ��
	GIMG_PVP_WLD,

	// ���Һ� 10 stage Ŭ����� �ߴ� �̹���.
	GIMG_BBB_WL,

	GIMG_DAMAGE_PC_DODGE,
	GIMG_DAMAGE_NPC_DODGE,
	GIMG_PVP_LEAGUE,
	GIMG_VALENTINEWAR,

	GIMG_ELIXIR,
	GIMG_EMBLEM,		// ������� ���� - ����
	GIMG_MAGIC_GREATWALLASURA, // ��������� �Ƽ��� ����.

	GIMG_GUILDWAR_KILLSIGN,		//	����� Ȯ�� ����� ųǥ��
	GIMG_GUILDWAR_TIME,			//	[��ȣ] ����� �ð�

	GIMG_WEDDING_EFT_S,			// [����] ���� ����Ʈ ����
	GIMG_WEDDING_EFT_M,			// [����] ���� ����Ʈ �߰�
	GIMG_WEDDING_EFT_L,			// [����] ���� ����Ʈ ŭ

	GIMG_HEAL_Y,				// [����] �� ����Ʈ �����

	GIMG_PCROOM_CHAR_HEAD,		// [����] ĳ���� ���� ��Ÿ�� PC�� ��ũ
	GIMG_HEAL_R,				// [���] �� ����Ʈ ������

	GIMG_GAWIBAWIBO,			// [��ȣ] ���������� �̹���
	GIMG_ROUNDCOUNT,
	GIMG_STUN,					// [����]���� �ɷ����� 
	GIMG_DRAGON_STUN,			// [����] ��ȯ�� �巡�� ����.

	GIMG_HEAL_P,				// [���] �� ����Ʈ �����

	GIMG_CURSE_ATTACK,			// [����] ����
	GIMG_CURSE_DEFENSE,	
	GIMG_CURSE_DODGE,	
	GIMG_CURSE_HIT,	
	GIMG_HEAL_B,

    GIMG_VALENTINEDAY_HEART,	// [����] ����Ÿ�� ���� ��Ʈ.
/////////////////////////////////////////////////////////////////////
//	
// �� ���� �߰��� �ּ��� �Ʒ� ������ �ǵ帮�� �ȵ˴ϴ�
//
/////////////////////////////////////////////////////////////////////
	MAX_GLOBAL_IMG_FILE_NUMBER
};
	
class cltGlobalImgFile{
protected:
	TSpr*		pTSpr[MAX_GLOBAL_IMG_FILE_NUMBER];
	TCHAR*		pszFileName[MAX_GLOBAL_IMG_FILE_NUMBER];

public:

	cltGlobalImgFile();
	~cltGlobalImgFile();

	void Add(SI32 index, TCHAR* pfilename);
	TSpr* GetGlobalSpr( SI32 index );

	SI16 GetBufImageFontIndex(SI16 siBufType);
};
#endif


