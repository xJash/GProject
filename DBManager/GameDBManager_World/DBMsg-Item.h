#ifndef _DBMSGITEM_H
#define _DBMSGITEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
//#include "..\..\GoonZuWorld\Common\Item\ItemCommon\ItemUnit.h"

//---------------------------------------------
// �κ��丮������ ������ �����.
//---------------------------------------------
class sDBRequest_MakeItemInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Person
	SI32				siPersonID;				// ������ ����� ���. 
	SI32				siMaterialPersonID;		// ������ �ֹ��� ���. (���ᰡ �� ������Լ� ������ �ϼ�ǰ�� �̻������ ����.)

	// Material 
	DBMaterialInfo		clMaterial[MAX_MATERIAL_NUMBER_FOR_DB];
	// Tool 
//	DBToolInfo			clTool[MAX_TOOL_NUMBER];

	// Output
	SI16				siOutputPos;		// ����ǰ�� ��ġ�� ����. 
	cltItem				clItem;				// ����ǰ�� ����. (���� ����. ) 
	bool				bCanPileSwitch;		// ����ǰ�� ���������Ѱ� ?
	bool				bAlmostFailSwitch;	// ���� ������ ��ǰ�ΰ� ?
	bool				bCreateSID;			// ����ǰ�� SID ���뿩�� - by LEEKH 1007.10.11
	SI16				siLuckQuality;		// �� ���� ����Ƽ ���. 
	
	GMONEY				siFee;				// �ֹ��ڰ� �ִ� ��� �ֹ����� �����ݿ��� �� �ݾ��� ���� �����ڿ��� ����. 
	SI16				siOrderNumber;		// �ֹ��ڰ� ����⸦ ����� ����. 
	SI16				siItemUnique;

	bool				bNPCMake;

	SI16				siMakerServerUnique;

	// �����Ƿ� �ϰ�� ǥ�� 
	bool				m_bRequest_Want_Make_Item	;	// ������ ������ ���Ѵ� -> �����Ƿ� ���� 

	sDBRequest_MakeItemInv()
	{
		ZeroMemory(this, sizeof(sDBRequest_MakeItemInv));
	}

	sDBRequest_MakeItemInv(SI32 id, SI32 personid, SI32 materialpersonid, 
						DBMaterialInfo* pclinfo, 
						//DBToolInfo* pcltool,
						SI32 outputpos, cltItem* pclitem, bool bcanpileswitch, bool balmostfailswitch, bool bcreatesid, SI16 luckquality,
						GMONEY fee, SI16 ordernum, SI16 itemunique, bool npcmake = false, SI16 MakerServerUnique = 0,bool bRequest_Want_Make_Item = false )
	{
		packetHeader.usSize = sizeof( sDBRequest_MakeItemInv );
		packetHeader.usCmd	= DBMSG_REQUEST_MAKEITEMINV;

		usCharID		= id;

		siPersonID			= personid;
		siMaterialPersonID	= materialpersonid;

		for(SI32 i = 0;i < MAX_MATERIAL_NUMBER_FOR_DB;i++)
		{
			clMaterial[i].Set(&pclinfo[i]);
		}

/*		for(i = 0;i < MAX_TOOL_NUMBER;i++)
		{
			clTool[i].Set(&pcltool[i]);
		}*/

		siOutputPos	= outputpos;
		clItem.Set(pclitem);
		bCanPileSwitch		= bcanpileswitch;
		bAlmostFailSwitch	= balmostfailswitch;
		bCreateSID			= bcreatesid;
		siLuckQuality		= luckquality;
		siFee				= fee;
		siOrderNumber		= ordernum;
		siItemUnique		= itemunique;
		bNPCMake			= npcmake;

		// �ű�ǰ �̻� ���۽� �������� ��������Ŭ �����Ѵ�.
		siMakerServerUnique = MakerServerUnique;
		// �����Ƿ� �������� ���� ������ ������ ��� 
		m_bRequest_Want_Make_Item	=	bRequest_Want_Make_Item	;
	}
};


class sDBResponse_MakeItemInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// Person
	SI32				siPersonID;				// ������ ����� ���. 
	SI32				siMaterialPersonID;		// ������ �ֹ��� ���. (���ᰡ �� ������Լ� ������ �ϼ�ǰ�� �̻������ ����.) 

	// Output
	SI16				siOutputPos;		// ����ǰ�� ��ġ�� ����. 
	SI16				siAddedNum;			// �߰��� ������ ����. 
	cltItem				clItem;				// ����ǰ�� ����. (���� ����. ) 

	bool				bAlmostFailSwitch;	// ���� ������ ��ǰ�ΰ� ?
	SI16				siLuckQuality;		// �� ���� ����Ƽ ���. 

	GMONEY				siFee;				// �ֹ��ڰ� �ִ� ��� �ֹ����� �����ݿ��� �� �ݾ��� ���� �����ڿ��� ����. 
	GMONEY				siPersonIDMoney;
	GMONEY				siMaterialPersonIDMoney;
	SI16				siOrderNumber;		// �ֹ��ڰ� ����⸦ ����� ����. 
	SI16				siItemUnique;

	bool				bNPCMake;
	// �����Ƿ� �ϰ�� ǥ�� 
	bool				m_bRequest_Want_Make_Item	;	// ������ ������ ���Ѵ� -> �����Ƿ� ����

	sDBResponse_MakeItemInv()
	{
		ZeroMemory(this, sizeof(sDBResponse_MakeItemInv));
	}
};


//---------------------------------------------
// �κ��丮������ ������ �����.
//---------------------------------------------
class sDBRequest_EnchantItemInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siSuccess;

	// Person
	SI32				siPersonID;				// ������ ����� ���. 
	SI32				siMaterialPersonID;		// ������ �ֹ��� ���. (���ᰡ �� ������Լ� ������ �ϼ�ǰ�� �̻������ ����.) 	


	// Material 
	DBMaterialInfo		clMaterial[MAX_ENCHANT_NUMBER];

	// Output
	SI16				siOutputPos;		// ��æƮ�� ��ǰ�� ��ġ
	cltItem				clItem;				// �ٲ� ��æƮ��ǰ�� ���� ����

	GMONEY				siFee;				// �ֹ��ڰ� �ִ� ��� �ֹ����� �����ݿ��� �� �ݾ��� ���� �����ڿ��� ����. 

    bool				bCreateSID;

	sDBRequest_EnchantItemInv()
	{
		ZeroMemory(this, sizeof(sDBRequest_MakeItemInv));
	}

	sDBRequest_EnchantItemInv(SI32 id, SI32 Success,SI32 personid,  SI32 materialpersonid, 
		DBMaterialInfo* pclinfo, SI32 outputpos, cltItem* pclitem,GMONEY fee, bool bcreatesid)
	{
		packetHeader.usSize = sizeof( sDBRequest_MakeItemInv );
		packetHeader.usCmd	= DBMSG_REQUEST_ENCHANTITEMINV;

		usCharID		= id;

		siPersonID			= personid;
		siMaterialPersonID	= materialpersonid;

		for(SI32 i = 0;i < MAX_MATERIAL_NUMBER;i++)
		{
			clMaterial[i].Set(&pclinfo[i]);
		}

		siOutputPos	= outputpos;
		clItem.Set(pclitem);		
		siFee				= fee;
		siSuccess = Success;

		bCreateSID = bcreatesid;
	}
};


class sDBResponse_EnchantItemInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siSuccess;

	SI32				siResult;				// �����.

	// Person
	SI32				siPersonID;				// ������ ����� ���. 
	SI32				siMaterialPersonID;		// ������ �ֹ��� ���. (���ᰡ �� ������Լ� ������ �ϼ�ǰ�� �̻������ ����.) 

	// Output
	SI16				siOutputPos;		// �ٲ� ������ ��ġ
	cltItem				clItem;				// ������ ����. (���� ����. ) 



	GMONEY				siFee;				// �ֹ��ڰ� �ִ� ��� �ֹ����� �����ݿ��� �� �ݾ��� ���� �����ڿ��� ����. 
	GMONEY				siPersonIDMoney;
	GMONEY				siMaterialPersonIDMoney;





	sDBResponse_EnchantItemInv()
	{
		ZeroMemory(this, sizeof(sDBResponse_EnchantItemInv));
	}
};


//------------------------------------------
// �κ��丮�� ������ �Ⱓ ����.
//------------------------------------------

class sDBRequest_EnchantUseDayPlus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	// Person
	SI32				siPersonID;				// ������ ����. 

	// Output
	SI16				siOutputPos;		// ��æƮ�� ��ǰ�� ��ġ
	cltItem				clItem;				// �ٲ� ��æƮ��ǰ�� ���� 

	SI16				siOutputMaterialPos;
	cltItem				clMaterialItem;

	sDBRequest_EnchantUseDayPlus()
	{
		ZeroMemory(this, sizeof(sDBRequest_EnchantUseDayPlus));
	}

	sDBRequest_EnchantUseDayPlus(SI32 id, SI32 personid,  
		SI16 outputpos, cltItem* pclitem , SI16 outputmaterialpos , cltItem* pclMaterialItem)
	{
		packetHeader.usSize = sizeof( sDBRequest_EnchantUseDayPlus );
		packetHeader.usCmd	= DBMSG_REQUEST_ENCHANT_USEDAYPLUS;

		usCharID		= id;

		siPersonID			= personid;

		siOutputPos	= outputpos;
		clItem.Set(pclitem);
		siOutputMaterialPos = outputmaterialpos;
		clMaterialItem.Set(pclMaterialItem);

	}
};


class sDBResponse_EnchantUseDayPlus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;				// �����.

	// Person
	SI32				siPersonID;				// ������ ����� ���. 

	// Output
	SI16				siOutputPos;		// �ٲ� ������ ��ġ
	cltItem				clItem;				// ������ ����. (���� ����. ) 

	// OutputMaterial
	SI16				siOutputMaterialPos;	// �ٲ� ����� ��ġ
	cltItem				clMaterialItem;			// �ٲ� ����� ����

	sDBResponse_EnchantUseDayPlus()
	{
		ZeroMemory(this, sizeof(sDBResponse_EnchantUseDayPlus));
	}
};

//------------------------------------------
// ������ ��þƮ �Ӽ� ����
//------------------------------------------
class sDBRequest_ChangeEnchant
{
public:
	sPacketHeader	packetHeader;

	UI16			usCharID;				// ������ �����ϴ� ID
	SI32			siPersonID;				// Unique�� ID
	
	SI16			siOutputPos;			// ��þƮ �Ӽ��� ����� �������� �κ���ġ
	cltItem			clItem;					// ��þƮ �Ӽ��� ����� ������

	SI16			siOutputMaterialPos;	// ��þƮ �Ӽ� ���� �������� �κ���ġ
	cltItem			clMaterialItem;			// ��þƮ �Ӽ� ���� ������


	sDBRequest_ChangeEnchant()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeEnchant));
	}

	sDBRequest_ChangeEnchant(
		SI32 id, SI32 personid,  
		SI16 outputpos, cltItem* pclitem, 
		SI16 outputmaterialpos, cltItem* pclMaterialItem
	)
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeEnchant );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGEENCHANT;

		usCharID			= id;
		siPersonID			= personid;

		siOutputPos			= outputpos;
		clItem.Set(pclitem);

		siOutputMaterialPos = outputmaterialpos;
		clMaterialItem.Set(pclMaterialItem);
	}
};

class sDBResponse_ChangeEnchant
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;				// �����.

	// Person
	SI32				siPersonID;				// ������ ����� ���. 

	// Output
	SI16				siOutputPos;			// ��þƮ �Ӽ��� ����� �������� �κ���ġ
	cltItem				clItem;					// ��þƮ �Ӽ��� ����� ������

	// OutputMaterial
	SI16				siOutputMaterialPos;	// ��þƮ �Ӽ� ���� �������� �κ���ġ
	cltItem				clMaterialItem;			// ��þƮ �Ӽ� ���� ������


	sDBResponse_ChangeEnchant()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeEnchant));
	}
};

//------------------------------------------
// �κ��丮�� �������� ����. 
//------------------------------------------
class sDBRequest_InvRepair
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from
	SI32				siPersonID;
	SI16				siFromPos;
	
	// Item
	cltItem				clItem;

	// ������.(������) 
	SI32				siRepairPersonID;
	GMONEY				siRepairMoney;		// ������. 
	SI32				siNPCVillageUnique;	// NPC�� ������ �ϴ°�� NPC�� ���� ���� UNIQUE


	sDBRequest_InvRepair()
	{
		ZeroMemory(this, sizeof(sDBRequest_InvRepair));
	}

	sDBRequest_InvRepair(SI32 id, SI32 personid, SI32 frompos, cltItem* pclitem, SI32 repairpersonid, GMONEY repairmoney, SI32 npcvillageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_InvRepair);
		packetHeader.usCmd = DBMSG_REQUEST_INVREPAIR;
		usCharID		= id;

		siPersonID	= personid;
		siFromPos	= frompos;
	
		clItem.Set(pclitem);

		siRepairPersonID	= repairpersonid;
		siRepairMoney		= repairmoney;
		siNPCVillageUnique	= npcvillageunique;
	}
};

class sDBResponse_InvRepair
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;

	// ������.(������) 
	SI32				siRepairPersonID;
	GMONEY				siRepairMoney;		// ������. 
	GMONEY				siRepairerMoney;	// �������� ���� ���� �ڱ� .

	//�Ƿ����� �ڱ�. 
	GMONEY				siPersonIDMoney;	// ���� �Ƿ����� ���� �ڱ�. 
	SI32				siNPCVillageUnique;	


	sDBResponse_InvRepair()
	{
		ZeroMemory(this, sizeof(sDBResponse_InvRepair));
	}
};


//--------------------------------------
// ������ ������ �����Ѵ�.
//--------------------------------------
class sDBResponse_SetItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	SI32				siPersonID;
	SI16				siPos;
	cltItem				clItem;

	sDBResponse_SetItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetItem));
	}
};

//------------------------------------------
// ������ ��� ������Ų��. 
//------------------------------------------
class sDBRequest_Enchant
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from person
	SI32				siPersonID;

	// from
	SI16				siFromPos;
	SI16				siFromItemUnique;		// ������ ����ũ.

	// to
	SI16				siToPos;				// ����� ��ġ. 
	cltItem				clToItem;				// ����� ����. 

	sDBRequest_Enchant()
	{
		ZeroMemory(this, sizeof(sDBRequest_Enchant));
	}

	sDBRequest_Enchant(SI32 id, SI32 personid, SI16 frompos, SI16 fromitemunique, SI16 topos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_Enchant);
		packetHeader.usCmd = DBMSG_REQUEST_ENCHANT;
		usCharID		= id;

		siPersonID	= personid;

		siFromPos			= frompos;
		siFromItemUnique	= fromitemunique;

		siToPos				= topos;
		clToItem.Set(pclitem);
	}
};


class sDBResponse_Enchant
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	// person
	SI32				siPersonID;

	// from 
	SI16				siFromPos;
	cltItem				clFromItem;

	// to
	SI16				siToPos;
	cltItem				clToItem;

	sDBResponse_Enchant()
	{
		ZeroMemory(this, sizeof(sDBResponse_Enchant));
	}
};

//------------------------------------------
// �������� ���� ������.
//------------------------------------------
class sDBRequest_DropItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;

	// where
	SI16				siMapIndex;
	SI16				siX;
	SI16				siY;

	sDBRequest_DropItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_DropItem));
	}

	sDBRequest_DropItem(SI32 id, SI32 personid, SI32 frompos, cltItem* pclitem, SI16 mapindex, SI16 x, SI16 y)
	{
		packetHeader.usSize = sizeof( sDBRequest_DropItem);
		packetHeader.usCmd = DBMSG_REQUEST_DROPITEM;
		usCharID		= id;

		siPersonID	= personid;
		siFromPos	= frompos;
	
		clItem.Set(pclitem);

		siMapIndex	= mapindex;
		siX			= x;
		siY			= y;
	}
};


class sDBResponse_DropItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;
	cltItem				clChangedItem;		// ��ȭ�� ������ ����. 

	// where
	SI16				siMapIndex;
	SI16				siX;
	SI16				siY;

	sDBResponse_DropItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_DropItem));
	}
};


//------------------------------------------
// Ư�� �������� Person�� Ư�� ������ ��ġ��  �־��� ���� ��û. 
//------------------------------------------

//------------------------------------------
// ***** DANGER ***** -> define ���� �ٲ��� ������
//------------------------------------------

#define INPUTITEMPERSON_OPTION_NONE								0	// Ư�� ���� ����. 	
#define INPUTITEMPERSON_OPTION_WAR								1	// ����ǰ���� ȹ���� ������. 
#define INPUTITEMPERSON_OPTION_MASTER							2	// ���� �����Ϳ� ���� �߰��Ǿ���. 
#define INPUTITEMPERSON_OPTION_PICKUP							3	// ������ �ֿ���. 
#define INPUTITEMPERSON_OPTION_QUEST							4	// ����Ʈ�� ���ؼ� �����. 
#define INPUTITEMPERSON_OPTION_FAMELEVEL						5	// ������ ������� ����. 
#define INPUTITEMPERSON_OPTION_SPEECIALQUEST					6	// ��ι��̺�Ʈ���� ����. 
#define INPUTITEMPERSON_OPTION_FARM								7	// ����� ����. 
#define INPUTITEMPERSON_OPTION_FARMSUMMON						8	// ����� ����. 
#define INPUTITEMPERSON_OPTION_FISH								9	// ������ ����. 
#define INPUTITEMPERSON_OPTION_FISHSUMMON						10	// ������ ����. 
#define INPUTITEMPERSON_OPTION_BLACKARMY						11  // ���Ǳ��� �̺�Ʈ(�����̺�Ʈ). 
#define INPUTITEMPERSON_OPTION_WORDASSEMBLE						12	// ��ι� �ܾ� �������� ����. 
#define INPUTITEMPERSON_OPTION_FEAST							13  // ���ڽÿ��� ����
#define INPUTITEMPERSON_OPTION_INSTANCEMAP						14  // �ν��Ͻ� ���� ���� ��Ƽ� ����
#define INPUTITEMPERSON_OPTION_OSAKA							15  // ����ī ������ ���� 
#define	INPUTITEMPERSON_OPTION_KANGHWADO						16  // ��ȭ�� ��� �� ���� 
#define INPUTITEMPERSON_OPTION_CRAZYEVENT						17  // ������ �ݰ� �̺�Ʈ�� ����
#define INPUTITEMPERSON_OPTION_ROULETTEGAME						18  // �ڴ�� �������� ����
#define INPUTITEMPERSON_OPTION_SEVENDAYEVENT					19  // �̻�����7������Ʈ�� ����
#define INPUTITEMPERSON_OPTION_WENNYOLDMAN						20  // �̻�����7������Ʈ�� ����
#define INPUTITEMPERSON_OPTION_RECOMMEND						21  // ��õ���� �ְ� ���� ���� �޼� 
#define INPUTITEMPERSON_OPTION_EVENT							22	// �ų� �̺�Ʈ�� ���� ������ ���� 
#define INPUTITEMPERSON_OPTION_CHIMERA_REWARD					23	// Ű�޶� �Ѵ�ģ ����
#define INPUTITEMPERSON_OPTION_LEVELUP_REWARD					24  // �������� ���� ����
#define INPUTITEMPERSON_OPTION_BEGINNERWEAPON					25	// �ʺ��� ���� ����Ʈ ����
#define INPUTITEMPERSON_OPTION_MOFUMOFUEVENT					26	// ���ĸ��� �̺�Ʈ Ŭ������ ����
#define INPUTITEMPERSON_OPTION_BLACKWAR							27	// ���� ���� �̺�Ʈ
#define INPUTITEMPERSON_OPTION_PARTYHALL_ITEM					28	// [����] ��ƼȦ. ��¥�� �Դ� �ǻ� ������. => 2008. 3. 12
#define INPUTITEMPERSON_OPTION_VOTE								29	// [����] ���� �ý��� : ���� ������ ���޵Ǵ� ������
#define INPUTITEMPERSON_OPTION_MAKEITEM_MATERIAL				30	// [����] �α׿� - ������ ������ �Ҹ�Ǵ� ������ ����� �����Ѵ�.
#define INPUTITEMPERSON_OPTION_ENCHANT_MATERIAL					31	// [����] �α׿� - ��æƮ�� �Ҹ�Ǵ� ������ ����� �����Ѵ�.
#define INPUTITEMPERSON_OPTION_SERVER_EVENT						32	// [����] ���� �̺�Ʈ�� ���޵Ǵ� ������.
#define INPUTITEMPERSON_OPTION_OPENBOX							33	// [����] �ڽ� �������� ���� ������
#define INPUTITEMPERSON_OPTION_PARTYHALL_GIVE_ITEM				34	// [����] ��ƼȦ. ��¥�� �Դ� �ǻ� ������. => 2008. 3. 12
#define INPUTITEMPERSON_OPTION_DAILYQUEST						35	// [���] ���ϸ� ����Ʈ�� ��� ������
#define INPUTITEMPERSON_OPTION_DAILYQUEST2						36  // [���] ���ϸ� ����Ʈ2�� ��� ������
#define INPUTITEMPERSON_OPTION_DAILYQUEST3						37  // [���] ���ϸ� ����Ʈ3���� ��� ������
#define INPUTITEMPERSON_OPTION_ITEMMALL							38  // [���] �����۸����� ���� ������
#define INPUTITEMPERSON_OPTION_MUDANGPRESENT					39  // [��] �������� ������ ���� ������
#define INPUTITEMPERSON_OPTION_CHAR_ROULETTE					40  // [����] ĳ���� �귿���� ���� ������
#define INPUTITEMPERSON_OPTION_AMBERBOX							41  // [����] ȣ�ڻ���.
#define INPUTITEMPERSON_OPTION_HELPER							42  // [����] ����̿��� �ִ� ������.
#define INPUTITEMPERSON_OPTION_CHRISTMAS_ROULETTE				43  // [��] ũ�������� �귿���� ���� ������
#define INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE					44  // [����] PVP���׺��������.
#define INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE_SPECIAL			45  // [����] PVP���� ��ǥ�޼� ���������.
#define INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE			46	// [���] �ų��̺�Ʈ ��귿���� ���� ������.
#define INPUTITEMPERSON_OPTION_ELIXIR_CHANGE_ITEM				47	// [����] ������ npc���� ��ȯ���� ������.
#define INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE				48	// [����] ������ npc���� ��ȯ���� ������.
#define INPUTITEMPERSON_OPTION_TREASUREEVENTITEM				49	// [����] ����ã�� �̺�Ʈ ������
#define INPUTITEMPERSON_OPTION_WEDDINGANNIVERSARY				50	// [����] ��ȥ ����� ������ ����
#define INPUTITEMPERSON_OPTION_WEDDINGHALL_FLOWER				51	// [����] ��ȥ ȭ��
#define INPUTITEMPERSON_OPTION_WEDDING_FULLDRESS				52	// [����] ��ȥ ����
#define INPUTITEMPERSON_OPTION_REPAIRITEM_MATERIAL				53	// [����] �α׿� - ������ ������ ���Ǵ� ����.
#define INPUTITEMPERSON_OPTION_DORMANCYACCOUNT					54	// [����] �޸� ���� ���� ������
#define INPUTITEMPERSON_OPTION_SEQGMCOMMAND						55  // [���] /seq ��ɾ ���ؼ� ������ ������
#define INPUTITEMPERSON_OPTION_BATTLEROYAL_WINNER				56  // [����] ��Ʋ�ξ� - ����� ����
#define INPUTITEMPERSON_OPTION_BATTLEROYAL_KILLINGUSER			57  // [����] ��Ʋ�ξ� - ���� ����
#define INPUTITEMPERSON_OPTION_SKILLBOOK_BUY					58  // [] 
#define INPUTITEMPERSON_OPTION_PARTYQUEST						59  // [��ȣ] ��Ƽ����Ʈ
#define INPUTITEMPERSON_OPTION_GIANTRACCOON_RESURRECT_EVENT		60  // [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� ��� ������.
#define INPUTITEMPERSON_OPTION_ADDITIONALITEM_GET				61	// [����] ����/��ɽ� ���� ������� ������ �ܿ� �̺�Ʈ �Ⱓ���� �߰������� ��� �Ǵ� ������ (��. ��Ű������)
#define INPUTITEMPERSON_OPTION_LIMITLEVELBOX					62	// [����] ���� ���� ���ڿ��� �������� �ش� 
#define INPUTITEMPERSON_OPTION_VALENTINEDAY_PAKING				63	// [����] �߷�Ÿ�ε��� ������ ����.
#define INPUTITEMPERSON_OPTION_VALENTINEDAY_BUY					64	// [����] �߷�Ÿ�ε��� ������ ����.


class sDBRequest_InputItemToPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� ���� Person
	SI16				siItemPos;		// �������� �־�� �� ��ġ.
	SI16				siInputItemPersonOption;	// � ������ ��������  �ְ� �Ǿ��°�?

	bool				bPileSwitch;	// ��ø ��� ����. 	
	cltItem				clItem;			// Person�� ���� ������.
	
	SI32				siGiverPersonID;	// �������� �� �����. 

	bool				bCreateSID;		// SID�� �����ؾ� �ϴ°�?

	sDBRequest_InputItemToPerson()
	{
		ZeroMemory(this, sizeof(sDBRequest_InputItemToPerson));
	}

	sDBRequest_InputItemToPerson(SI32 id, SI32 personid, SI16 itempos, SI16 option, bool bpileswitch, cltItem* pclitem, SI32 giverpersonid, bool createsid)
	{
		packetHeader.usSize = sizeof( sDBRequest_InputItemToPerson );
		packetHeader.usCmd = DBMSG_REQUEST_INPUTITEMTOPERSON;
		usCharID		= id;

		siPersonID				= personid;
		siItemPos				= itempos;
		siInputItemPersonOption	= option;
		bPileSwitch				= bpileswitch;
		clItem.Set(pclitem);

		siGiverPersonID			= giverpersonid;
		bCreateSID				= createsid;
	}
};


class sDBResponse_InputItemToPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		

	cltItem				clInputedItem;				// Person�� ���� ������. [2007. 10. 23 �����߰�]
	
	SI16				siItemPos;
	SI16				siInputItemPersonOption;	// � ������ ��������  �ְ� �Ǿ��°�?
	SI16				siChangedNum;
	cltItem				clItem;			

	sDBResponse_InputItemToPerson()
	{
		ZeroMemory(this, sizeof(sDBResponse_InputItemToPerson));
	}
};


//------------------------------------------
// Ư�� �������� Person�� Ư�� ������ ��ġ���� ����. 
//------------------------------------------
class sDBRequest_OutputItemFromPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� ���� Person
	SI16				siItemPos;		// �������� ���� �� ��ġ.
	cltItem				clItem;			// Person�� ���� ������.

	sDBRequest_OutputItemFromPerson()
	{
		ZeroMemory(this, sizeof(sDBRequest_OutputItemFromPerson));
	}

	sDBRequest_OutputItemFromPerson(SI32 id, SI32 personid, SI32 itempos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_OutputItemFromPerson);
		packetHeader.usCmd = DBMSG_REQUEST_OUTPUTITEMFROMPERSON;
		usCharID		= id;

		siPersonID	= personid;
		siItemPos	= itempos;
		clItem.Set(pclitem);
	}
};


class sDBResponse_OutputItemFromPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;			

	sDBResponse_OutputItemFromPerson()
	{
		ZeroMemory(this, sizeof(sDBResponse_OutputItemFromPerson));
	}
};

//------------------------------------------
// Person�� ������ â���� �������� �̵���Ų��. (�κ����� ����â�̳� �� �ݴ�� ���� ���. ) 
//------------------------------------------
class sDBRequest_MoveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� PersonID
	SI16				siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				clFromItem;			// �����ġ�� �ִ� ������ 
	bool				bFromItemPileSwitch;//��� ��ġ���ִ� �������� ������ �����Ѱ� ?
	
	SI16				siToItemPos;		// �̵���ų ������.
	cltItem				clToItem;			// �̵���ų �������� �ִ� ������ 

	sDBRequest_MoveItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_MoveItem));
	}

	sDBRequest_MoveItem(SI32 id, SI32 personid, 
						SI32 itemfrompos, cltItem* pclfromitem, bool fromitempileswitch, 
						SI32 toitempos, cltItem* pcltoitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_MoveItem );
		packetHeader.usCmd = DBMSG_REQUEST_MOVEITEM;
		usCharID		= id;

		siPersonID		= personid;
		siFromItemPos	= itemfrompos;
		clFromItem.Set(pclfromitem);
		bFromItemPileSwitch	= fromitempileswitch;

		siToItemPos		= toitempos;
		clToItem.Set(pcltoitem);

	}
};


class sDBResponse_MoveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� PersonID
	SI16				siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				clFromItem;			// �����ġ�� �ִ� ������ 
	
	SI16				siToItemPos;		// �̵���ų ������.
	cltItem				clToItem;			// �̵���ų �������� �ִ� ������ 

	cltItem				clMoveItem;			// ������� �ִ� ������ (�̵���Ű�� ������ ����) For Log - by LEEKH 2007.10.23

	sDBResponse_MoveItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_MoveItem));
	}
};




//------------------------------------------
// Person���� �������� �̵���Ų��.
//------------------------------------------
#define MOVEITEMPERSON_NORMAL	1
#define MOVEITEMPERSON_PVP		2

class sDBRequest_MoveItemPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siFromPersonID;		// ��� Person
	SI16				siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				clFromItem;			// �����ġ�� �ִ� ������ 
	bool				bFromItemPileSwitch;//��� ��ġ���ִ� �������� ������ �����Ѱ� ?
	TCHAR				szFromUserName[MAX_PLAYER_NAME];
	
	SI32				siToPersonID;		// ������ Person
	SI16				siToItemPos;		// �̵���ų ������.
	cltItem				clToItem;			// �̵���ų �������� �ִ� ������ 
	TCHAR				szToUserName[MAX_PLAYER_NAME];

	SI32				siReason;			// �ű�� ����?
	bool				bDestroy;			// true�̸� �̵���ų �������� �ִ� ������ �������.

	sDBRequest_MoveItemPerson()
	{
		ZeroMemory(this, sizeof(sDBRequest_MoveItemPerson));
	}

	sDBRequest_MoveItemPerson(SI32 id, 
							SI32 frompersonid, SI32 itemfrompos, cltItem* pclfromitem, bool fromitempileswitch, TCHAR* FromUserName,
							SI32 topersonid, SI32 toitempos, cltItem* pcltoitem, TCHAR* ToUserName, SI32 Reason, bool Destroy )
	{
		packetHeader.usSize = sizeof( sDBRequest_MoveItemPerson );
		packetHeader.usCmd = DBMSG_REQUEST_MOVEITEMPERSON;
		usCharID		= id;

		siFromPersonID	= frompersonid;
		siFromItemPos	= itemfrompos;
		clFromItem.Set(pclfromitem);
		bFromItemPileSwitch	= fromitempileswitch;
		MStrCpy( szFromUserName, FromUserName, MAX_PLAYER_NAME );

		siToPersonID	= topersonid;
		siToItemPos		= toitempos;
		clToItem.Set(pcltoitem);
		MStrCpy( szToUserName, ToUserName, MAX_PLAYER_NAME );

		siReason = Reason;
		bDestroy = Destroy;

	}
};


class sDBResponse_MoveItemPerson
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siFromPersonID;		// ������� �Ǵ� PersonID
	SI16				siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				clFromItem;			// �����ġ�� �ִ� ������ 
	TCHAR				szFromUserName[MAX_PLAYER_NAME];
    	
	SI32				siToPersonID;		// �������� �Ǵ� personID
	SI16				siToItemPos;		// �̵���ų ������.
	cltItem				clToItem;			// �̵���ų �������� �ִ� ������ 
	TCHAR				szToUserName[MAX_PLAYER_NAME];

	SI32				siReason;			// �ű�� ����?
	bool				bDestroy;			// true�̸� �̵���ų �������� �ִ� ������ �������.
	SI16				siDestroyItemUnique; // �ű�� �������� �ı��� �� �־ ������ ����ũ�� ���� ����Ѵ�.

	//[�߰� : Ȳ���� 2007. 10. 24 �ִ� ������.]
	cltItem				clMoveItem;			// �̵� ������. 

	sDBResponse_MoveItemPerson()
	{
		ZeroMemory(this, sizeof(sDBResponse_MoveItemPerson));
	}
};

#define USEITEM_REASON_NONE						 0 // �Ϲ������� ���
#define USEITEM_REASON_DATEOVER					 1 // �Ⱓ�� ������ �Ⱓ ��
#define USEITEM_REASON_ROULLET					 2 // �ڴ������ ���
#define USEITEM_REASON_TICKET					 3 // Ƽ�ϵ� ���
#define USEITEM_REASON_HORSECHANGE				 4 // ���� �������� ���
#define USEITEM_REASON_BELONGITEM				 5 // �ͼӾ����� �ı�
#define USEITEM_REASON_DISASSEMBLE				 6 // Ȥ�θ�(2ȣ��) ������ ����
#define USEITEM_REASON_PATYHALL					 7 // [����] ��ƼȦ. ��Ƽ�忡�� �� �������̶� ĳ���� �ʱ�ȭ�� ����.
#define USEITEM_REASON_DAILYQUEST2				 8 // ���ϸ� ����Ʈ2 ������ ����
#define USEITEM_REASON_DAILYQUEST3				 9 // ���ϸ� ����Ʈ3 ������ ����
#define USEITEM_REASON_MAKE_MATERIAL			10 // ������ ���� ����
#define USEITEM_REASON_ENCHANT_MATERIAL 		11 // ��æƮ�� ���� ����
#define USEITEM_REASON_OPENBOX_KEY				12 // �ڽ� ���� Ű ���
#define USEITEM_REASON_CHANGENAME				13	// �̸� �����̿�� ���
#define USEITEM_REASON_CHANGECHARKIND			14	// ĳ���� ���� �̿�� ���
#define USEITEM_REASON_PARTYHALLGIFT			15	// ĳ���� ���� �̿�� ���
#define USEITEM_REASON_SUMMONEVOLVE				16  // ��ȯ�� ��ȭ �̿�� ���
#define USEITEM_REASON_SUMMONREVIVE				17	// ��ȯ�� ��Ȱ ���� ���
#define USEITEM_REASON_SUMMONSTATUSINIT			18	// ��ȯ�� ���� �ʱ�ȭ �̿�� ���
#define USEITEM_REASON_PERSONSHOP				19	// ���λ����̿�� ���
#define	USEITEM_REASON_INITSTATUSMODE_TICKET	20	// ĳ���� ���� �ʱ�ȭ �̿�� ���
#define USEITEM_REASON_SKILLRESET_TICKET		21	// ��ų�ʱ�ȭ �̿�� ���
#define USEITEM_REASON_ELIXIR_CHANGE_ITEM		22	//[����] ������ NPC���Լ� ������ ������� ��ȯ�� ������. 
#define USEITEM_REASON_ELIXIR_START_USE_ITEM	23	//[����] ������ NPC���Լ� ������ ������� ��ȯ�� ������. 
#define USEITEM_REASON_ARTIFACT_SLOT_CREATE		24	//[����] ��Ƽ��Ʈ ���� ����ü ���
#define USEITEM_REASON_ARTIFACT_MIXTURE			25	//[����] ��Ƽ��Ʈ ���տ� ���
#define USEITEM_REASON_FESTIVAL_FOOD			26	//[����] ���� ����.
#define USEITEM_REASON_DURABILITY_ZERO			27  //[����] �������� 0�̶� �����Ѵ�
#define USEITEM_REASON_CONTRIBUTION_ITEM_INPUT	28  //[����] ���๰�� ����Ͽ� �Ҹ�� ������.
#define USEITEM_REASON_USEDAYPLUS				29  //[����] �Ⱓ ���� ������ ���
#define USEITEM_REASON_VALENTINEDAY				30  //[����] �߷�Ÿ�ε��� �̺�Ʈ�� ���� ������ ���.
#define USEITEM_REASON_COMMISSION				31	// [����] ���� �Ƿ� �̿��

//------------------------------------------
// Person�� �������� ����� ���� ��û. 
//------------------------------------------
class sDBRequest_UseItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� ����� Person
	SI16				siItemPos;		// �������� ����� ��ġ.
	cltItem				clItem;			// Person�� ����� ������ ����. 

	SI16				siUseReason;	// ������ ��� ����

	sDBRequest_UseItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_UseItem));
	}

	sDBRequest_UseItem(SI32 id, SI32 personid, SI32 itempos, cltItem* pclitem,SI16 reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_UseItem);
		packetHeader.usCmd = DBMSG_REQUEST_USEITEM;
		usCharID		= id;

		siPersonID	= personid;
		siItemPos	= itempos;
		clItem.Set(pclitem);

		siUseReason = reason ;
	}
};


class sDBResponse_UseItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;				// ���ǰ� ���� ������.
	cltItem				clUsedItem;			// ���� ������. 

	SI16				siUseReason;

	sDBResponse_UseItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_UseItem));
	}
};


class sDBRequest_Use_SpaceBox_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� ����� Person
	SI16				siItemPos;		// �������� ����� ��ġ.
	cltItem				clItem;			// Person�� ����� ������ ����. 

	SI16				siUseReason;	// ������ ��� ����

	sDBRequest_Use_SpaceBox_Item()
	{
		ZeroMemory(this, sizeof(sDBRequest_Use_SpaceBox_Item));
	}

	sDBRequest_Use_SpaceBox_Item(SI32 id, SI32 personid, SI32 itempos, cltItem* pclitem,SI16 reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_Use_SpaceBox_Item);
		packetHeader.usCmd  = DBMSG_REQUEST_USE_SPACEBOX_ITEM;
		usCharID			= id;

		siPersonID	= personid;
		siItemPos	= itempos;
		clItem.Set(pclitem);

		siUseReason = reason ;
	}
};


class sDBResponse_Use_SpaceBox_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;				// ���ǰ� ���� ������.
	cltItem				clUsedItem;			// ���� ������. 

	SI16				siUseReason;

	sDBResponse_Use_SpaceBox_Item()
	{
		ZeroMemory(this, sizeof(sDBResponse_Use_SpaceBox_Item));
	}
};

class sDBRequest_Use_Treasure_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� ����� Person
	SI16				siItemPos;		// �������� ����� ��ġ.
	cltItem				clItem;			// Person�� ����� ������ ����. 

	SI16				siUseReason;	// ������ ��� ����

	sDBRequest_Use_Treasure_Item()
	{
		ZeroMemory(this, sizeof(sDBRequest_Use_Treasure_Item));
	}

	sDBRequest_Use_Treasure_Item(SI32 id, SI32 personid, SI32 itempos, cltItem* pclitem,SI16 reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_Use_Treasure_Item);
		packetHeader.usCmd	= DBMSG_REQUEST_USE_TREASURE_ITEM;
		usCharID			= id;

		siPersonID	= personid;
		siItemPos	= itempos;
		clItem.Set(pclitem);

		siUseReason = reason ;
	}
};


class sDBResponse_Use_Treasure_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;			
	cltItem				clItem;				// ���ǰ� ���� ������.
	cltItem				clUsedItem;			// ���� ������. 

	SI16				siUseReason;

	sDBResponse_Use_Treasure_Item()
	{
		ZeroMemory(this, sizeof(sDBResponse_Use_Treasure_Item));
	}
};

//------------------------------------------
// �������� NPC���� ó���� ���� ��û. 
//------------------------------------------
class sDBRequest_SellNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// �������� �� Person
	SI16				siItemPos;		// �������� �� ��ġ.
	cltItem				clItem;			// Person�� �� ������ ����. 
	GMONEY				siPrice;		// �������� �ܰ�. 
	SI32				siVillageUnique;// NPC�� ��ġ�� ���� Unique

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿��� NPC �Ǹ� ���� �߰�. ]
	SI32				siNPCKind;		// NPC ����.

	sDBRequest_SellNPC()
	{
		ZeroMemory(this, sizeof(sDBRequest_SellNPC));
	}

	sDBRequest_SellNPC(SI32 id, SI32 personid, SI32 itempos, cltItem* pclitem, GMONEY price, SI32 villageunique, SI32 NPCKind = 0)
	{
		packetHeader.usSize = sizeof( sDBRequest_SellNPC);
		packetHeader.usCmd = DBMSG_REQUEST_SELLNPC;
		usCharID		= id;

		siPersonID	= personid;
		siItemPos	= itempos;
		clItem.Set(pclitem);
		siPrice		= price;
		siVillageUnique = villageunique;
		
		siNPCKind = NPCKind;
	}
};


class sDBResponse_SellNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;				// �Ȱ� ���� ������.
	GMONEY				siMoney;			// �����ڱ�. 
	GMONEY				siChangedMoney;		// �Ǹŷ� ���� �þ �ڱ�. 
	SI32				siVillageUnique;	// NPC�� ��ġ�� ���� Unique

	SI16				siIitemUnique;
	SI16				siItemNum;

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿��� NPC �Ǹ� ���� �߰�. ]
	cltItem				clSellItem;			// �Ǹ��ϴ� ������.
	GMONEY				siSellMoney;		// �Ǹ��� �ݾ�. 
	SI32				siNPCKind;			// NPC ����.

	sDBResponse_SellNPC()
	{
		ZeroMemory(this, sizeof(sDBResponse_SellNPC));
	}
};


//------------------------------------------
// �������� NPC���Լ� ������ ���� ��û. 
//------------------------------------------
class sDBRequest_BuyNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ���  Person
	cltItem				clItem;			// ��� ������ ����. 
	bool				bPileSwitch;	// ���� ���� ����. 
	GMONEY				siPrice;		// �������� �ܰ�. 
	SI16				siItemPos;		// �������� ���� �κ��� ��ġ.

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿��� NPC���� ���� �߰�. ]
	SI32				siNPCkind;		// NPC ����.

	sDBRequest_BuyNPC()
	{
		ZeroMemory(this, sizeof(sDBRequest_BuyNPC));
	}

	sDBRequest_BuyNPC(SI32 id, SI32 personid, cltItem* pclitem, bool bpilewitch, GMONEY price, SI32 itempos, SI32 NPCkind = 0)
	{
		packetHeader.usSize = sizeof( sDBRequest_BuyNPC);
		packetHeader.usCmd = DBMSG_REQUEST_BUYNPC;
		usCharID		= id;

		siPersonID	= personid;
		clItem.Set(pclitem);
		bPileSwitch	= bpilewitch;
		siPrice		= price;
		siItemPos	= itempos;

		siNPCkind	= NPCkind;
	}
};


class sDBResponse_BuyNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;				// ���� ������.
	GMONEY				siMoney;			// �����ڱ�. 

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �ƿ��� NPC���� ���� �߰�. ]
	cltItem				clBuyItem;			// �����ϴ� ������.
	GMONEY				siBuyMoney;			// ���Կ� ����ϴ� �ڱ�. 
	SI32				siNPCkind;			// NPC ����.

	sDBResponse_BuyNPC()
	{
		ZeroMemory(this, sizeof(sDBResponse_BuyNPC));
	}
};


//------------------------------------------
// �������� �Ҹ��Ͽ����� ��û. 
//------------------------------------------
class sDBRequest_WasteDurability
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;


	sDBRequest_WasteDurability()
	{
		ZeroMemory(this, sizeof(sDBRequest_WasteDurability));
	}

	sDBRequest_WasteDurability(SI32 id, SI32 personid, SI32 frompos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_WasteDurability);
		packetHeader.usCmd = DBMSG_REQUEST_WASTEDURABILITY;
		usCharID		= id;

		siPersonID	= personid;
		siFromPos	= frompos;
	
		clItem.Set(pclitem);
	}
};


class sDBResponse_WasteDurability
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;

	sDBResponse_WasteDurability()
	{
		ZeroMemory(this, sizeof(sDBResponse_WasteDurability));
	}
};

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ������ �Ҹ� DB�� ����.
//------------------------------------------
// �������� �Ҹ��Ͽ����� ��û. 
//------------------------------------------
class sDBRequest_CrystalDurability
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;


	sDBRequest_CrystalDurability()
	{
		ZeroMemory(this, sizeof(sDBRequest_CrystalDurability));
	}

	sDBRequest_CrystalDurability(SI32 id, SI32 personid, SI32 frompos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_CrystalDurability);
		packetHeader.usCmd = DBMSG_REQUEST_CRYSTALDURABILITY;
		usCharID		= id;

		siPersonID	= personid;
		siFromPos	= frompos;
	
		clItem.Set(pclitem);
	}
};


class sDBResponse_CrystalDurability
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	// from
	SI32				siPersonID;
	SI16				siFromPos;

	// Item
	cltItem				clItem;

	sDBResponse_CrystalDurability()
	{
		ZeroMemory(this, sizeof(sDBResponse_CrystalDurability));
	}
};
class sDBRequest_UpgradeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	// from
	SI16				siFromPos;
	SI16				siFromItemUnique;		// Ȥ�θ� ���� �̿���� ������ Unique

	// to
	SI16				siToPos;				// ����� ��ġ. 
	cltItem				clToItem;				// ����� ����. 
	
	SI32				siVillageUnique;		// ������ ���� ����
	GMONEY				siAddCityHallMoney;

	bool				bSuccess;				// ���� ����

	sDBRequest_UpgradeItem( bool Success, SI32 CharID, SI32 PersonID, SI16 FromPos, SI16 FromItemUnique, SI16 ToPos, cltItem *pclItem, SI32 VillageUnique, GMONEY	AddCityHallMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_UpgradeItem );
		packetHeader.usCmd = DBMSG_REQUEST_UPGRADEITEM;

		bSuccess = Success;

		siCharID = CharID;
		siPersonID = PersonID;

		siFromPos = FromPos;
		siFromItemUnique = FromItemUnique;

		siToPos = ToPos;
		clToItem.Set( pclItem );

		siVillageUnique = VillageUnique;
		siAddCityHallMoney = AddCityHallMoney;
	}
};

class sDBResponse_UpgradeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	// from 
	SI16				siFromPos;
	cltItem				clFromItem;

	// to
	SI16				siToPos;
	cltItem				clToItem;

	SI32				siVillageUnique;
	cltMoney			clMoney;

	bool				bSuccess;

	sDBResponse_UpgradeItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_UpgradeItem ) );
	}
};


class sDBRequest_PerformanceUpgradeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;
	
	SI16				siItemPos;				// ������ ��ġ
	cltItem				clPreItem;				// ������ ����Ǳ� ���� ������ ����
	cltItem				clItem;					// ������ ����� ������ ����

	SI16				siScrollItemPos;		// ���� ������ ��ġ
	cltItem				clScrollItem;			// ����� ���� ������ ����

	sDBRequest_PerformanceUpgradeItem( SI32 CharID, SI32 PersonID,
		SI16 ItemPos, cltItem *pclPreItem, cltItem *pclItem,
		SI16 ScrollItemPos, cltItem *pclScrollItem
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_PerformanceUpgradeItem );
		packetHeader.usCmd = DBMSG_REQUEST_PERFORMANCEUPGRADEITEM;

		siCharID = CharID;
		siPersonID = PersonID;

		siItemPos = ItemPos;
		clPreItem.Set( pclPreItem );
		clItem.Set( pclItem );

		siScrollItemPos = ScrollItemPos;
		clScrollItem.Set( pclScrollItem );
	}
};

class sDBResponse_PerformanceUpgradeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;				// 1 : ����, other : ����

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siItemPos;				// ������ ��ġ
	cltItem				clItem;					// ������ ����� ������ ����

	SI16				siLeftScrollItemPos;	// ���� ���� ������ ��ġ
	cltItem				clLeftScrollItem;		// ����ϰ� ���� ���� ������ ����

	sDBResponse_PerformanceUpgradeItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_PerformanceUpgradeItem ) );
	}
};

/*class sDBRequest_Delete_LimitDateItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siItemPos;				// ������ ��ġ
	cltItem				clItem;					// ������ ������

	sDBRequest_Delete_LimitDateItem( SI32 CharID, SI32 PersonID,
		SI16 ItemPos, cltItem *pclItem)
	{
		packetHeader.usSize = sizeof( sDBRequest_Delete_LimitDateItem );
		packetHeader.usCmd = DBMSG_REQUEST_DELETE_LIMITDATEITEM;

		siCharID = CharID;
		siPersonID = PersonID;

		siItemPos = ItemPos;
		clItem.Set( pclItem );
	}
};

class sDBResponse_Delete_LimitDateItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;				// 1 : ����, other : ����

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siItemUnique;			// ������ �������� ����ũ
	SI16				siItemPos;				// ������ ��ġ
	cltItem				clItem;					// ������ ����

	sDBResponse_Delete_LimitDateItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_Delete_LimitDateItem ) );
	}
};

class sDBRequest_GetLimitUseItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siItemPos;				// ������ ��ġ
	cltItem				clItem;					// �� ������
	SI32				siUseDate;

	sDBRequest_GetLimitUseItem( SI32 CharID, SI32 PersonID,
		SI16 ItemPos, cltItem *pclItem,SI32 usedate)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetLimitUseItem );
		packetHeader.usCmd = DBMSG_REQUEST_GETLIMITUSEITEM;

		siCharID = CharID;
		siPersonID = PersonID;

		siItemPos = ItemPos;
		clItem.Set( pclItem );

		siUseDate = usedate;
	}
};

class sDBResponse_GetLimitUseItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;				// 1 : ����, 0 : �̹� ���� -1 : ĳ���� ����

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siItemPos;				// ������ ��ġ
	cltItem				clItem;					// ������ ����
	SI32				siUseDate;

	sDBResponse_GetLimitUseItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetLimitUseItem ) );
	}
};*/

#define SETPREMIUM_EXP				1
#define SETPREMIUM_COMBAT			2
#define SETPREMIUM_EXPANDCOMBAT		3
#define SETPREMIUM_MAKEITEM			4
#define SETPREMIUM_BULLET			5
#define SETPREMIUM_SUMMONSTIMINA	6
#define SETPREMIUM_MAKETITEM		7

class sDBRequest_SetPremium
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	bool				bPremium;
	SI32				siPremiumUseDate;
	SI32				siCombatUseDate;
	SI32				siMakeItemServiceDate;
	SI32				siBulletServiceDate;
	SI32				siSummonStaminaServiceDate;

	cltItem				clItem;
	SI16				siItemPos;

	SI08				siType;

	sDBRequest_SetPremium( SI32 CharID, SI32 PersonID,bool premium,SI32 premiumdate,SI32 combatdate,SI32 MakeItemdate, 
		                   SI32 Bulletdate, SI32 SummonStaminadate, cltItem*pclitem,SI16 pos,SI08 type )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetPremium );
		packetHeader.usCmd = DBMSG_REQUEST_SETPREMIUM;

		siCharID = CharID;
		siPersonID = PersonID;

		bPremium = premium ;
		siPremiumUseDate = premiumdate ;
		siCombatUseDate = combatdate ;
		siMakeItemServiceDate = MakeItemdate;
		siBulletServiceDate = Bulletdate;
		siSummonStaminaServiceDate = SummonStaminadate;
		
		clItem.Set(pclitem);
		siItemPos = pos ;

		siType = type;
	}
};

class sDBResponse_SetPremium
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;				// 1 : ����, 0 : �̹� ���� -1 : ĳ���� ����

	SI32				siCharID;
	SI32				siPersonID;

	bool				bPremium;
	SI32				siPremiumUseDate;
	SI32				siCombatUseDate;
	SI32				siMakeItemDate;
	SI32				siBulletDate;
	SI32				siSummonStaminaDate;
	
	cltItem				clItem;
	SI16				siItemPos;

	SI08				siType;

	sDBResponse_SetPremium()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetPremium ) );
	}
};


//------------------------------------------
// ��õ�� ������ �������� ������ ���� ��û. 
//------------------------------------------
class sDBRequest_BuyRecommendProduct
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ���  Person
	cltItem				clItem;			// ��� ������ ����. 
	bool				bPileSwitch;	// ���� ���� ����. 
	SI32				siNeedPoint;	// �������� �ܰ�. 
	SI16				siItemPos;		// �������� ���� �κ��� ��ġ.

	sDBRequest_BuyRecommendProduct()
	{
		ZeroMemory(this, sizeof(sDBRequest_BuyRecommendProduct));
	}

	sDBRequest_BuyRecommendProduct(SI32 id, SI32 personid, cltItem* pclitem, bool bpilewitch, SI32 NeedPoint, SI32 itempos)
	{
		packetHeader.usSize = sizeof( sDBRequest_BuyRecommendProduct);
		packetHeader.usCmd = DBMSG_REQUEST_BUYRECOMMENDPRODUCT;
		usCharID		= id;

		siPersonID	= personid;
		clItem.Set(pclitem);
		bPileSwitch	= bpilewitch;
		siNeedPoint		= NeedPoint;
		siItemPos	= itempos;
	}
};


class sDBResonse_BuyRecommendProduct
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siItemPos;
	cltItem				clItem;				// ���� ������.
	SI32				siUsedPoint;
	SI32				siRecommendPoint;	// ��������Ʈ. 

	cltItem				clItem_Log;			// FOR LOG

	sDBResonse_BuyRecommendProduct()
	{
		ZeroMemory(this, sizeof(sDBResonse_BuyRecommendProduct));
	}
};


#define EXCHANGEITEM_REASON_NONE			0
#define EXCHANGEITEM_REASON_TINTINBOX		1	//��ȣ�� ����;
#define EXCHANGEITEM_REASON_DORMANCY		2	//�޸� ���� ������ ���׷��̵�;
#define EXCHANGEITEM_REASON_GIVEPRESENT		3	//���� �ֱ�

class sDBRequest_ExchangeItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;		// ���  Person

	SI16				siItemPos;		// �������� ���� �κ��� ��ġ.
	cltItem				clItem;			// �ٲ� ������ ����
	cltItem				clChangedItem;	// �ٲپ��� ������ ����
	SI16				siReason;		// �ٲ� ����

	sDBRequest_ExchangeItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_ExchangeItem));
	}

	sDBRequest_ExchangeItem(SI32 personid, SI16 itempos, cltItem* pclitem, cltItem* pclchangeditem, SI16 reason )
	{
		packetHeader.usSize = sizeof( sDBRequest_ExchangeItem);
		packetHeader.usCmd = DBMSG_REQUEST_EXCHANGEITEM;

		siPersonID	= personid;
		siItemPos = itempos;
		clItem.Set(pclitem);
		clChangedItem.Set(pclchangeditem);
		siReason = reason;
	}
};

class sDBResponse_ExchangeItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.
	SI32				siPersonID;		

	SI16				siItemPos;
	cltItem				clItem;				
	cltItem				clChangedItem;
	SI16				siReason;

	sDBResponse_ExchangeItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_ExchangeItem));
	}
};

class sDBRequest_OpenTreasureBox
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;		// ���  Person

	SI16				siItemPos;		// �������� ���� �κ��� ��ġ.
	cltItem				clItem;			// �ٲ� ������ ����

	SI16				siKeyItemPos;	// Ű ������ ��ġ
	cltItem				clKeyItem;		// Ű ������ ����

	// ������ ù��° ������ ����
	SI16				siToItemPos1;
	cltItem				clToItem1;		// �ٲپ��� ������ ����
	bool				bPileSwitch1;
	bool				bCreateSID1;
	bool				bCanNotice1;	// ��� �˸� ����

	// ������ �ι�° ������ ����
	SI16				siToItemPos2;
	cltItem				clToItem2;		// �ٲپ��� ������ ����
	bool				bPileSwitch2;
	bool				bCreateSID2;
	bool				bCanNotice2;	// ��� �˸� ����

	sDBRequest_OpenTreasureBox()
	{
		ZeroMemory(this, sizeof(sDBRequest_OpenTreasureBox));
	}

	sDBRequest_OpenTreasureBox(SI32 personid, SI16 itempos, cltItem* pclitem, SI16 keyitempos, cltItem* pclkeyitem, SI16 toitempos1, cltItem* pcltoitem1, bool pileswitch1, bool bcreatesid1, bool bcannotice1, SI16 toitempos2, cltItem* pcltoitem2, bool pileswitch2, bool bcreatesid2, bool bcannotice2 )
	{
		packetHeader.usSize = sizeof( sDBRequest_OpenTreasureBox);
		packetHeader.usCmd = DBMSG_REQUEST_OPENTREASUREBOX;

		siPersonID		= personid;

		siItemPos		= itempos;
		clItem.Set(pclitem);

		siKeyItemPos	= keyitempos;
		if(pclkeyitem)	clKeyItem.Set(pclkeyitem);

		siToItemPos1	= toitempos1;
		clToItem1.Set(pcltoitem1);
		bPileSwitch1	= pileswitch1;
		bCreateSID1		= bcreatesid1;
		bCanNotice1		= bcannotice1;

		siToItemPos2	= toitempos2;
		clToItem2.Set(pcltoitem2);
		bPileSwitch2	= pileswitch2;
		bCreateSID2		= bcreatesid2;
		bCanNotice2		= bcannotice2;
	}

	sDBRequest_OpenTreasureBox(SI32 personid, SI16 itempos, cltItem* pclitem, SI16 keyitempos, cltItem* pclkeyitem, SI16 toitempos1, cltItem* pcltoitem1, bool pileswitch1, bool bcreatesid1, bool bcannotice1)
	{
		packetHeader.usSize = sizeof( sDBRequest_OpenTreasureBox);
		packetHeader.usCmd = DBMSG_REQUEST_OPENTREASUREBOX;

		siPersonID		= personid;

		siItemPos		= itempos;
		clItem.Set(pclitem);
		
		siKeyItemPos	= keyitempos;
		if(pclkeyitem)	clKeyItem.Set(pclkeyitem);

		siToItemPos1	= toitempos1;
		clToItem1.Set(pcltoitem1);
		bPileSwitch1	= pileswitch1;
		bCreateSID1		= bcreatesid1;
		bCanNotice1		= bcannotice1;

		siToItemPos2	= 0;
		clToItem2.Init();
		bPileSwitch2	= false;
		bCreateSID2		= false;
		bCanNotice2		= false;
	}

	// �ܼ��� ����� �������� ������ ���̱� ���� ������
	sDBRequest_OpenTreasureBox(SI32 personid, SI16 itempos, cltItem* pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_OpenTreasureBox);
		packetHeader.usCmd = DBMSG_REQUEST_OPENTREASUREBOX;

		siPersonID		= personid;

		siItemPos		= itempos;
		clItem.Set(pclitem);

		siKeyItemPos	= 0;

		siToItemPos1	= 0;
		clToItem1.Init();
		bPileSwitch1	= false;
		bCreateSID1		= false;
		bCanNotice1		= false;

		siToItemPos2	= 0;
		clToItem2.Init();
		bPileSwitch2	= false;
		bCreateSID2		= false;
		bCanNotice2		= false;
	}
};

class sDBResponse_OpenTreasureBox
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.
	SI32				siPersonID;		

	SI16				siItemPos;
	cltItem				clItem;

	SI16				siKeyItemPos;
	cltItem				clKeyItem;

	SI16				siToItemPos1;
	cltItem				clToItem1;		// �ٲپ��� ������ ����
	SI32				siGetItemNumber1;
	bool				bCanNotice1;	// ��� �˸� ����

	SI16				siToItemPos2;
	cltItem				clToItem2;		// �ٲپ��� ������ ����
	SI32				siGetItemNumber2;
	bool				bCanNotice2;	// ��� �˸� ����

	// FOR LOG
	cltItem				clUse_Item;
	cltItem				clUse_KeyItem;
	cltItem				clAdd_ToItem1;	// �ٲپ��� ������ ����
	cltItem				clAdd_ToItem2;	// �ٲپ��� ������ ����

	sDBResponse_OpenTreasureBox()
	{
		ZeroMemory(this, sizeof(sDBResponse_OpenTreasureBox));
	}
};

class sDBRequest_GiveVillageItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;		// �ڽ���  Personid
	
	SI32				siVillageUnique;

	cltItem				clItem;			

	TCHAR				szMsg[256];

	// PCK : ������ ���Ⱓ �߰�
	SI32				siUseDate;

	sDBRequest_GiveVillageItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_GiveVillageItem));
	}

	sDBRequest_GiveVillageItem(SI32 personid, SI32 villageUnique , cltItem * pclItem , TCHAR * pMsg, SI32 UseDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_GiveVillageItem);
		packetHeader.usCmd = DBMSG_REQUEST_GIVEVILLAGEITEM;

		siPersonID	= personid;		
		siVillageUnique = villageUnique;
		clItem.Set(pclItem);
		MStrCpy( szMsg , pMsg , 256 );
		siUseDate = UseDate;
	}
};

// PCK : �α׿� ��Ŷ �߰�
class sDBResponse_GiveVillageItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siPersonID;		// �ڽ���  Personid

	SI32				siVillageUnique;

	cltItem				clItem;			

	TCHAR				szMsg[256];

	SI32				siUseDate;

	sDBResponse_GiveVillageItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_GiveVillageItem));
	}
};

//********************************************************************************
//
// [�߰� : Ȳ���� 2008. 1. 30 => ���� ����(����) ����]
//
//********************************************************************************

//[�߰� : Ȳ���� 2008. 1. 30 => ó�� ĳ���� ������ ���� ���� ������ ����Ʈ�� ��û. S->DB]
class sDBRequest_Space_Box_List
{
public:
	sPacketHeader	packetHeader;
	UI16			usCharID;
	SI32			siPersonID;

	sDBRequest_Space_Box_List( UI16	CharID, SI32 personid )
	{
		ZeroMemory( this, sizeof( sDBRequest_Space_Box_List ) );

		packetHeader.usSize = sizeof(sDBRequest_Space_Box_List);
		packetHeader.usCmd  = DBMSG_REQUEST_SPACE_BOX_ITEM_LIST;
		usCharID			= CharID;	
		siPersonID			= personid;
	}
};

//[�߰� : Ȳ���� 2008. 1. 30 => ó�� ĳ���� ������ ���� ���� ������ ����Ʈ. DB->S]
class sDBResponse_Space_Box_List
{
public:
	sPacketHeader packetHeader;
	UI16				usCharID;

	SI32				siResult;
	SI32				siPersonID;

	cltSpaceBox			clSpaceBoxItem;		// ������ ���� ��� ���õ� ����.
	cltTreasureBox		clTreasureBoxItem;	// ������ ���� ��� ���õ� ����.


	sDBResponse_Space_Box_List()
	{
		ZeroMemory(this, sizeof(sDBResponse_Space_Box_List));
	}

	sDBResponse_Space_Box_List( SI32 personid )
	{
		ZeroMemory( this, sizeof( sDBResponse_Space_Box_List ) );

		packetHeader.usSize = sizeof(sDBResponse_Space_Box_List);
		packetHeader.usCmd  = DBMSG_RESPONSE_SPACE_BOX_ITEM_LIST;

		siPersonID			= personid;
	}
};




enum{ TYPE_SPACE_BOX, TYPE_TREASURE_BOX };

class sDBRequest_Move_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� PersonID
	
	SI16				siInvenItemPos;		// �κ��丮 �������� ��ġ. 
	cltItem				clInvenItem;		// �κ��丮 ��ġ�� �ִ� ������ 

	SI16				siBoxItemPos;		// �ڽ� �������� ��ġ. 
	cltItem				clBoxItem;			// �ڽ� ��ġ�� �ִ� ������ 
	
	bool				type;				// ���� �������� ���� ��������.
	bool				bCanPile;			// ��ø�� ������ �������ΰ�?

	sDBRequest_Move_Item()
	{
		ZeroMemory(this, sizeof(sDBRequest_Move_Item));
	}

	sDBRequest_Move_Item( UI16  _Cmd,		      SI32     _id,		      SI32 _personid,
						   SI32  _siInvenItemPos, cltItem* _clInvenItem, 
						   SI32  _siBoxItemPos,   cltItem* _clBoxItem,	  bool _type, bool _bCanPile )
	{
		ZeroMemory( this, sizeof( sDBRequest_Move_Item ) );

		packetHeader.usSize = sizeof( sDBRequest_Move_Item );
		packetHeader.usCmd  = _Cmd;	// DBMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM, DBMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM
		usCharID			= _id;

		siPersonID			= _personid;

		siInvenItemPos		= _siInvenItemPos;
		clInvenItem.Set(_clInvenItem);

		siBoxItemPos		= _siBoxItemPos;
		clBoxItem.Set(_clBoxItem);

		type				= _type;
		bCanPile			= _bCanPile;
	}
};

class sDBResponse_Move_Item
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	SI32				siPersonID;			// ����� �Ǵ� PersonID
	
	SI16				siInvenItemPos;		// �κ��丮 �������� ��ġ. 
	cltItem				clInvenItem;		// �κ��丮 ��ġ�� �ִ� ������ 

	SI16				siBoxItemPos;		// �ڽ� �������� ��ġ. 
	cltItem				clBoxItem;			// �ڽ� ��ġ�� �ִ� ������ 

	bool				type;				// ���� �������� ���� ��������.

	cltItem				clMoveItem;			// For Log - �Ű����� ������

	sDBResponse_Move_Item()
	{
		ZeroMemory( this, sizeof( sDBResponse_Move_Item ) );
	}

	sDBResponse_Move_Item( UI16  _Cmd,		      SI32     _id,		      SI32 _personid,
						   SI32  _siInvenItemPos, cltItem* _clInvenItem, 
						   SI32  _siBoxItemPos,   cltItem* _clBoxItem,	  bool _type )
	{
		ZeroMemory( this, sizeof( sDBResponse_Move_Item ) );

		packetHeader.usSize = sizeof( sDBResponse_Move_Item );
		packetHeader.usCmd  = _Cmd;	// DBMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM, DBMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM
		usCharID			= _id;

		siPersonID			= _personid;
		
		siInvenItemPos		= _siInvenItemPos;
		clInvenItem.Set(_clInvenItem);

		siBoxItemPos		= _siBoxItemPos;
		clBoxItem.Set(_clBoxItem);

		type				= _type;
	}
};

// [����] ��ȯ�� ������� : ������� ��ȯ���� ������ �̵� ��û
class sDBRequest_SummonPushItem
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_usCharID;
	SI32				m_siPersonID;			// ����� �Ǵ� PersonID
	SI32				m_siSummonID;			// ��ȯ�� ��ȣ

	SI16				m_siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				m_clFromItem;			// �����ġ�� �ִ� ������ 
	bool				m_bFromItemPileSwitch;	// ��� ��ġ���ִ� �������� ��ġ�� �����Ѱ�

	SI16				m_siToItemPos;			// �̵���ų ������.
	cltItem				m_clToItem;				// �̵���ų �������� �ִ� ������ 

	sDBRequest_SummonPushItem()
	{
		ZeroMemory( this, sizeof(sDBRequest_SummonPushItem) );
	}

	sDBRequest_SummonPushItem(
		UI16	usCharID,		SI32		siPersonID,		SI32	siSummonID,
		SI16	siFromItemPos,	cltItem*	pclFromItem,	bool	bFromItemPileSwitch,
		SI16	siToItemPos,	cltItem*	pclToItem
	)
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_SummonPushItem );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SUMMONPUSHITEM;

		m_usCharID				= usCharID;
		m_siPersonID			= siPersonID;			
		m_siSummonID			= siSummonID;		

		m_siFromItemPos			= siFromItemPos;
		m_clFromItem.Set( pclFromItem );
		m_bFromItemPileSwitch	= bFromItemPileSwitch;

		m_siToItemPos			= siToItemPos;
		m_clToItem.Set( pclToItem );
	}

};

class sDBResponse_SummonPushItem
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;				// �����

	UI16				m_usCharID;
	SI32				m_siPersonID;			// ����� �Ǵ� PersonID
	SI32				m_siSummonID;		// ��ȯ�� ��ȣ

	SI16				m_siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				m_clFromItem;			// �����ġ�� �ִ� ������ 
	bool				m_bFromItemPileSwitch;	// ��� ��ġ���ִ� �������� ��ġ�� �����Ѱ�

	SI16				m_siToItemPos;			// �̵���ų ������.
	cltItem				m_clToItem;				// �̵���ų �������� �ִ� ������ 

	cltItem				m_clMoveItem;			// �α׿� ������ ����

	sDBResponse_SummonPushItem()
	{
		ZeroMemory( this, sizeof(sDBResponse_SummonPushItem) );
	}

};	// DBMSG_RESPONSE_SUMMONPUSHITEM


// [����] ��ȯ�� ������� : ��ȯ������ ������� ������ �̵� ��û
class sDBRequest_SummonPopItem
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_usCharID;
	SI32				m_siPersonID;			// ����� �Ǵ� PersonID
	SI32				m_siSummonID;			// ��ȯ�� ��ȣ

	SI16				m_siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				m_clFromItem;			// �����ġ�� �ִ� ������ 
	bool				m_bFromItemPileSwitch;	// ��� ��ġ���ִ� �������� ��ġ�� �����Ѱ�

	SI16				m_siToItemPos;			// �̵���ų ������.
	cltItem				m_clToItem;				// �̵���ų �������� �ִ� ������ 

	sDBRequest_SummonPopItem()
	{
		ZeroMemory( this, sizeof(sDBRequest_SummonPopItem) );
	}

	sDBRequest_SummonPopItem(
		UI16	usCharID,		SI32		siPersonID,		SI32	siSummonID,
		SI16	siFromItemPos,	cltItem*	pclFromItem,	bool	bFromItemPileSwitch,
		SI16	siToItemPos,	cltItem*	pclToItem
		)
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_SummonPopItem );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SUMMONPOPITEM;

		m_usCharID				= usCharID;
		m_siPersonID			= siPersonID;			
		m_siSummonID			= siSummonID;		

		m_siFromItemPos			= siFromItemPos;
		m_clFromItem.Set( pclFromItem );
		m_bFromItemPileSwitch	= bFromItemPileSwitch;

		m_siToItemPos			= siToItemPos;
		m_clToItem.Set( pclToItem );
	}

};

class sDBResponse_SummonPopItem
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;				// �����

	UI16				m_usCharID;
	SI32				m_siPersonID;			// ����� �Ǵ� PersonID
	SI32				m_siSummonID;			// ��ȯ�� ��ȣ

	SI16				m_siFromItemPos;		// �������� ��� ��ġ. 
	cltItem				m_clFromItem;			// �����ġ�� �ִ� ������ 
	bool				m_bFromItemPileSwitch;	// ��� ��ġ���ִ� �������� ��ġ�� �����Ѱ�

	SI16				m_siToItemPos;			// �̵���ų ������.
	cltItem				m_clToItem;				// �̵���ų �������� �ִ� ������ 

	cltItem				m_clMoveItem;			// �α׿� ������ ����

	sDBResponse_SummonPopItem()
	{
		ZeroMemory( this, sizeof(sDBResponse_SummonPopItem) );
	}

};	// DBMSG_RESPONSE_SUMMONPOPITEM

enum SUMMONUSEITEM_REASON // ��ȯ�� ������ ��� ����
{
	SUMMONUSEITEM_REASON_NONE		= 0	// �̷� ���Ÿ���� ����
	,SUMMONUSEITEM_REASON_GENERAL		// �Ϲ����� ������ ���
};

class sDBRequest_SummonUseItem
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;		// ��ȯ�� ����

	SI32				m_siSummonID;		// ��ȯ��
	SI16				m_siItemPos;		// �������� ����� ��ġ.
	cltItem				m_clItem;			// Person�� ����� ������ ����. 

	SI16				m_siUseReason;		// ������ ��� ����

	sDBRequest_SummonUseItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonUseItem));
	}

	sDBRequest_SummonUseItem( SI32 siCharID, SI32 siPersonID, SI32 siSummonID, SI32 siItemPos, cltItem* pclItem, SI16 siReason )
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_SummonUseItem);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SUMMONUSEITEM;

		m_usCharID				= siCharID;
		m_siPersonID			= siPersonID;

		m_siSummonID			= siSummonID;
		m_siItemPos				= siItemPos;
		m_clItem.Set( pclItem );

		m_siUseReason			= siReason;
	}
};


class sDBResponse_SummonUseItem
{
public:
	sPacketHeader		m_packetHeader;
	
	SI32				m_siResult;

	UI16				m_usCharID;
	SI32				m_siPersonID;		// ��ȯ�� ����

	SI32				m_siSummonID;		// ��ȯ��
	SI16				m_siItemPos;		// ������ ��ġ
	cltItem				m_clItem;			// ����� ���� ������
	cltItem				m_clUsedItem;		// ���Ǳ��� ������

	SI16				m_siUseReason;		// ������ ��� ����

	sDBResponse_SummonUseItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonUseItem));
	}
};	// DBMSG_RESPONSE_SUMMONUSEITEM

// ��ȯ�� ������ ���� ��ȭ
enum SUMMONITEM_STATUSCHANGE_REASON				// ��ȯ�� ������ ���� ��ȭ ����
{
	SUMMONITEM_STATUSCHANGE_REASON_NONE	= 0		// �̷� ���Ÿ���� ����
	,SUMMONITEM_STATUSCHANGE_REASON_DECREASE	// ����ü ������ ����
};


class sDBRequest_SummonItem_StatusChange
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;		// ��ȯ�� ����

	SI32				m_siSummonID;		// ��ȯ��
	SI16				m_siItemPos;		// ���º�ȭ�� ������ ��ġ
	cltItem				m_clItem;			// ���º�ȭ�� ������

	SI16				m_siReason;			// ���� ��ȯ ����

	sDBRequest_SummonItem_StatusChange()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonItem_StatusChange));
	}

	sDBRequest_SummonItem_StatusChange( SI32 siCharID, SI32 siPersonID, SI32 siSummonID, SI32 siItemPos, cltItem* pclItem, SI16 siReason )
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_SummonItem_StatusChange);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SUMMONITEM_STATUSCHANGE;

		m_usCharID				= siCharID;
		m_siPersonID			= siPersonID;

		m_siSummonID			= siSummonID;
		m_siItemPos				= siItemPos;
		m_clItem.Set( pclItem );

		m_siReason				= siReason;
	}
};


class sDBResponse_SummonItem_StatusChange
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;

	UI16				m_usCharID;
	SI32				m_siPersonID;		// ��ȯ�� ����

	SI32				m_siSummonID;		// ��ȯ��
	SI16				m_siItemPos;		// ������ ��ġ
	cltItem				m_clItem;			// ���°� ��ȭ�� ������
	cltItem				m_clOldItem;		// ���°� ��ȭ�Ǳ��� ������(�α׿�)

	SI16				m_siReason;			// ������ ��� ����

	sDBResponse_SummonItem_StatusChange()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonItem_StatusChange));
	}
};	// DBMSG_RESPONSE_SUMMONITEM_STATUSCHANGE

class sDBRequest_Amber_Box_Select_Item_List
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siPersonID;		
	SI32				m_siCharID;
	
	SI32				m_siUseItemUnique;		// � �������� ����Ͽ� �������� ���� �Ǿ����� �˱�����.

	sDBRequest_Amber_Box_Select_Item_List(SI32 _siCharID, SI32 _siPersonID, SI32 _siUseItemUnique)
	{
		ZeroMemory(this, sizeof(sDBRequest_Amber_Box_Select_Item_List));

		m_packetHeader.usSize	= sizeof( sDBRequest_Amber_Box_Select_Item_List);
		m_packetHeader.usCmd	= DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_LIST;

		m_siCharID				= _siCharID;
		m_siPersonID			= _siPersonID;
		m_siUseItemUnique		= _siUseItemUnique;

	}
};


class sDBResponse_Amber_Box_Select_Item_List
{
public:
	sPacketHeader			m_packetHeader;
	SI32					m_siPersonID;				// ��ȯ�� ����
	SI32					m_siCharID;

	AmberboxSelectItemInfo	m_clAmberboxItemList[3];	// �����ϰ� ���õ� ������ ����.	

	sDBResponse_Amber_Box_Select_Item_List()
	{
		ZeroMemory(this, sizeof(sDBResponse_Amber_Box_Select_Item_List));
	}
};


class sDBRequest_Amber_Box_Select_Item_Add
{
public:
	sPacketHeader			m_packetHeader;

	SI32					m_siResult;

	SI32					m_siPersonID;		
	SI32					m_siCharID;

	AmberboxSelectItemInfo	m_clAmberboxItemList;	// �����ϰ� ���õ� ������ ����.	

	SI32					m_siUseItemUnique;		// � �������� ����Ͽ� �������� ���� �Ǿ����� �˱�����.

	sDBRequest_Amber_Box_Select_Item_Add(SI32 _siCharID, SI32 _siPersonID, AmberboxSelectItemInfo* _pclAmberboxItemList, SI32 _siUseItemUnique)
	{
		ZeroMemory(this, sizeof(sDBRequest_Amber_Box_Select_Item_Add));

		m_packetHeader.usSize	= sizeof( sDBRequest_Amber_Box_Select_Item_Add );
		m_packetHeader.usCmd	= DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_ADD;

		m_siCharID				= _siCharID;
		m_siPersonID			= _siPersonID;

		m_clAmberboxItemList.m_siItemNum	= _pclAmberboxItemList->m_siItemNum;	
		m_clAmberboxItemList.m_siItemUnique	= _pclAmberboxItemList->m_siItemUnique;
		m_clAmberboxItemList.m_siSlot		= _pclAmberboxItemList->m_siSlot;		

		m_siUseItemUnique		= _siUseItemUnique;
	}
};


class sDBRequest_Amber_Box_Select_Item_Get
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siPersonID;		
	SI32				m_siCharID;

	UI08				m_SlotIndex;
	
	SI16				m_siUseItemPos;		// ����ϴ� �������� �κ� ��ġ. 
	cltItem				m_clUseItem;		// ����ϴ� ������ ����.
	
	SI16				m_siGetItemPos;		// ���� �������� �κ� ��ġ. 
	cltItem				m_clGetItem;		// ���� ������ ����.

	bool				m_bCanPile;			// �ߺ����� ����.

	sDBRequest_Amber_Box_Select_Item_Get(   SI32 _siCharID, SI32 _siPersonID, UI08 _SlotIndex, 
											SI16 _siUseItemPos,		cltItem* _pclUseItem,
											SI16 _siGetItemPos,		cltItem* _pclGetItem, 
											bool _bCanPile)
	{
		ZeroMemory(this, sizeof(sDBRequest_Amber_Box_Select_Item_Get));

		m_packetHeader.usSize	= sizeof( sDBRequest_Amber_Box_Select_Item_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_GET;

		m_siCharID				= _siCharID;
		m_siPersonID			= _siPersonID;

		m_SlotIndex				= _SlotIndex;	
		
		m_siUseItemPos			= _siUseItemPos;
		m_clUseItem.Set(_pclUseItem);

		m_siGetItemPos			= _siGetItemPos;
		m_clGetItem.Set(_pclGetItem);

		m_bCanPile			    = _bCanPile;
	}
};

class sDBResponse_Amber_Box_Select_Item_Get
{
public:
	sPacketHeader			m_packetHeader;
	
	SI32					m_siResult;

	SI32					m_siPersonID;		
	SI32					m_siCharID;

	SI16					m_siRemainItemPos;		// ����ϰ� ���� �������� �κ� ��ġ. 
	cltItem					m_clRemainItem;			// ����ϰ� ���� ������ ����.

	SI16					m_siToItemPos;			// ���� �������� �κ� ��ġ. 
	cltItem					m_clToItem;				// ���� ������ ����(���� �������� ������ ������ ����).

	// ��ǰâ ������ ���.
	cltItem					m_clUseItem;			// ����� ������ ����..
	cltItem					m_clGetItem;			// ����   ������ ����..

	bool					m_bCanPile;				// �ߺ����� ����.
	
	sDBResponse_Amber_Box_Select_Item_Get()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

class sDBRequest_NewSelectBox_Item_Get
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;
	UI16				m_uiCharID;

	SI16				m_siSelectIndex;	// �α׿�

	cltItem				m_clBoxItem;
	SI16				m_siBoxItemPos;

	cltItem				m_clGetItem;
	SI16				m_siGetItemPos;
	bool				m_bGetItemCanPile;
	SI16				m_siCanNotice;		// ��ھ˸�â ����
	

	sDBRequest_NewSelectBox_Item_Get()
	{
		ZeroMemory( this, sizeof(sDBRequest_NewSelectBox_Item_Get) );
	}

	sDBRequest_NewSelectBox_Item_Get( SI32 siPersonID, UI16 uiCharID, SI16 siSelectIndex,
									cltItem* pclBoxItem, SI16 siBoxItemPos,
									cltItem* pclGetItem, SI16 siGetITemPos, bool bGetItemCanPile, SI16 siCanNotice)
	{
		ZeroMemory( this, sizeof(sDBRequest_NewSelectBox_Item_Get) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_NEWSELECTBOX_ITEM_GET;
		m_packetHeader.usSize	= sizeof(sDBRequest_NewSelectBox_Item_Get);

		m_siPersonID			= siPersonID;
		m_uiCharID				= uiCharID;

		m_siSelectIndex			= siSelectIndex;

		if ( pclBoxItem )
		{
			m_clBoxItem.Set( pclBoxItem );
			m_siBoxItemPos		= siBoxItemPos;
		}

		if ( pclGetItem )
		{
			m_clGetItem.Set( pclGetItem );
			m_siGetItemPos		= siGetITemPos;
			m_bGetItemCanPile	= bGetItemCanPile;
			m_siCanNotice		= siCanNotice;
		}

	}

};

class sDBResponse_NewSelectBox_Item_Get
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;
	UI16				m_uiCharID;

	SI32				m_siResult;
	
	// �޽��� �� �α׿�
	cltItem				m_clUseItem;	// ����� ������(�ڽ�������)
	cltItem				m_clToItem;		// ���� ������
	SI16				m_siSelectIndex;// �α׿� 

	cltItem				m_clBoxItem;	// ���ǰ� ���� �ڽ� ������
	SI16				m_siBoxItemPos;	

	cltItem				m_clGetItem;	// ���� ���� ���� ������
	SI16				m_siGetItemPos;
	SI16				m_siCanNotice;
	


	sDBResponse_NewSelectBox_Item_Get()
	{
		ZeroMemory( this, sizeof(sDBResponse_NewSelectBox_Item_Get) );
	}

};	// DBMSG_RESPONSE_NEWSELECTBOX_ITEM_GET


//------------------------------------------
// �������� �����ϴ� ���
// 1. NPC�� ���� ����
// 2. ������ ����
// 3. ��Ź ����
//------------------------------------------

class sDBRequest_RepairItem
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	// �����ϴ� ĳ����
	SI32				m_siPersonID;

	// �����ϴ� ������ (������ ������ DB�� ������)
	SI16				m_siPos;
	cltItem				m_clItem;

	// ���� ��� ������ : ������ + ��Ÿ���
	RepairItemExtraMaterial	m_Material;

	// ������.
	GMONEY				m_siRepairMoney;
	
	// ��Ź������ ��� ������ ĳ����
	SI32				m_siRepairPersonID;

	// �����Ǳ����� ������ ����	- for Log
	cltItem				m_clBeforeItem;

	SI16				m_siType;	// 1:��������, 2:������û, 3:�Ƿڼ���, 4:������û ���, 5:NPC����

	sDBRequest_RepairItem( SI32 id, SI32 personid, SI32 pos, cltItem* pclbeforeitem, cltItem* pclitem, RepairItemExtraMaterial& Materials, GMONEY repairmoney, SI32 siRepairPersonID, SI16 siType )
	{
		m_packetHeader.usSize = sizeof( sDBRequest_RepairItem );
		m_packetHeader.usCmd = DBMSG_REQUEST_REPAIRITEM;
		m_usCharID			= id;

		m_siPersonID		= personid;

		m_siPos				= pos;
		m_clBeforeItem.Set(pclbeforeitem);
		m_clItem.Set(pclitem);

		for( SI32 i=0; i<m_Material.GetSize(); i++ )
		{
			m_Material[i].Set( &Materials[i] );
		}
		m_siRepairMoney		= repairmoney;

		m_siRepairPersonID	= siRepairPersonID;

		m_siType			= siType;
	}
};

class sDBResponse_RepairItem
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;
	// �����ϴ� ĳ����
	SI32				m_siPersonID;

	// ������ ������
	SI16				m_siPos;
	cltItem				m_clItem;

	// �����ϴ� ĳ���� �ڱ�
	GMONEY				m_siRepairMoney;		// ������. 
	GMONEY				m_siRepairerMoney;	// �������� ���� ���� �ڱ� .

	// ������
	SI32				m_siRepairPersonID;		// ��Ź������ ��� ������ ĳ����
	GMONEY				m_siRepairPersonMoney;	// �������� �ڱ�

	// �����Ǳ����� ������ ����	- for Log
	cltItem				m_clBeforeItem;

	SI16				m_siType;	// 1:��������, 2:������û, 3:�Ƿڼ���, 4:������û ���, 5:NPC����

	sDBResponse_RepairItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_RepairItem));
	}
};



#endif
