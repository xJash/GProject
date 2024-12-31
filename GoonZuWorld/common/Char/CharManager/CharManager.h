//---------------------------------
// 20010/11/1 ���°�
//---------------------------------
#ifndef _CHARMANAGER_H
#define _CHARMANAGER_H

class cltIDManager;
class cltCharCommon;
class cltCharClient;
class cltCharServer;
class cltItem;
class cltStatistics;
class cltStatisticsManager;
class cltMonsterGroupManager;

#include "../NetworkLib/ITZNetLib/itzbase.h"
#include "../../../common/CommonHeader.h"


//-----------------------------------------------
// ĳ���͸� ���� �����ϴ� Ŭ����. 
//-----------------------------------------------
#define MAX_USER_WEAPON_TYPE_NUMBER	14
#define MAX_USER_GIVEITEM_FROM_VILLAGE		1000
class cltCharManager{
public:
	cltIDManager* pclIDManager;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltCharCommon*, MAX_CHAR_NUMBER>	CR;
#else
	cltCharCommon*   CR[MAX_CHAR_NUMBER];				// ĳ������ ������ ����Ű�� �����͸� �����ϴ� ����. 
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_CHAR_NUMBER>	SessionSwitch;
#else
	bool			 SessionSwitch[MAX_CHAR_NUMBER];	// Session�� ���� ĳ�������� ����. 	
#endif

	SI32			siMaxSessionNumber;					// ���� ĳ������ ����. 
	SI32			siMaxInstanceNPC;

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_USER_WEAPON_TYPE_NUMBER>	siUserWeaponStatistic;
#else
	SI32			siUserWeaponStatistic[MAX_USER_WEAPON_TYPE_NUMBER];			// ����� ���� ���. 
#endif

	DWORD			dwParametaBoxActionIntervalClock;	// ParametaBoxAction�� ���� ����. 
	SI32			siIncLifeUnit;						// ü�� �ڵ� ȸ�� ����. 


	cltCharManager(SI32 gamemode);
	~cltCharManager();

	// ĳ���Ͱ� ��� �ִ��� ���θ� �˷��ش�. 
	BOOL IsAlive(SI32 id);

	//personid�� �ٰŷ� id�� ���Ѵ�. 
	SI32 GetIDFromPersonID(SI32 personid);
	// CharUnique�� �ٰŷ� id�� ���Ѵ�.
	SI32 GetIDFromCharUnique(SI32 charunique);
	//�̸��� �ٰŷ� id�� ���Ѵ�. 
	SI32 GetIDFromName(TCHAR* pname);
	// KIND�� �ٰŷ� id�� ���Ѵ�.
	SI32 GetIDFromCharKind( SI32 charkind );



	BOOL Action();

	BOOL SetInfo(cltCharCommon* pclchar);
	bool IsValidID(SI32 id);

	SI32 GetCharOrder(SI32 index);

	// Person�� �����Ѵ�. 
	BOOL DeleteChar(SI32 id);
	// ��� ĳ���͸� �����Ѵ�. 
	BOOL DeleteChar();

	// ĳ���� �̸��� �����.
	void MakeCharName();

	// ĳ���� �̸��� ǥ���Ѵ�. 
	void DrawCharName();

	
	// ĳ���� ��ǳ���� ǥ���Ѵ�. 
	void DrawChatBalloon();

	
	// ��� Person���� �޽����� ������. 
	void SendAllPersonMsg(sPacketHeader* pmsg);

	// Ư�� ������ �ִ� ����ڵ鿡�� �޽����� ������. 
	void SendAllPersonInVillageMsg(sPacketHeader* pmsg, SI16 villageunique);
	
	// Ư�� ������  �ִ� ����ڵ鿡�� �޽����� ������. 
	void SendAllPersonInMapMsg(sPacketHeader* pmsg, SI16 mapindex);


	// Ư�� ������ �ֹο��Ը� �޽����� ������. 
	void SendAllPersonHomeMsg(sPacketHeader* pmsg, SI16 villageunique);
	
	// Ư�� ������ ������ ����ڿ��� �޽����� ������. 
	void SendNewsMsg(sPacketHeader* pmsg, SI32 newskind);

	// ���ε鿡�Ը� �޼����� ������.
	void SendAllAdultUserMsg(sPacketHeader* pmsg);

	// ��Ƽ���鿡�� �޼����� �����ϴ�.
	void SendAllPartyMemberMsg(sPacketHeader* pmsg, SI32 siPartyIndex);


	//_LEON_GUILD_CHAT
//#if defined(_DEBUG)
	// Ư�� ����� ������Ը� �޽����� ������. 
	void SendAllGuildMemberMsg(sPacketHeader* pmsg,  SI32 GuildUnitIndex ,TCHAR * GuildName );
//#endif
	
	// ��� ����ڸ� �� ��������. (DB�� ���嵵 �Ѵ�. ) 
	void CloseAllSocket();

	// person�̸��� ������ PersonID�� ã�´�. 
	SI32 GetPersonIDFromName(TCHAR* pname);

	// PersonID�� �ٰŷ� �ش� ĳ���͸� ������ �ƿ� ��Ų��. 
	bool OutByPersonID(SI32 personid);
	
	// ��� ���� ������ �����Ѵ�. 
	bool DeleteAllWarKill();

	bool DeleteBlackWarKill();
	
	// �ֺ��� �Ʊ����� ������ ��û�Ѵ�. 
	SI32 FindNearAlly(SI32 kind, SI32 mapindex, SI32 x, SI32 y, bool bwarswitch, SI16 villageunique);
	// �ֺ����� �������� ���� �Ʊ��� ã�´�. 
	SI32 FindDamagedFriend(SI32 myid, SI32 mapindex, SI32 x, SI32 y, bool bwarswitch);


	// ������� ���忡 ���� ��踦 ����. 
	void AddUserWeapon(cltItem* pclitem);
	
	// Ư�� ���ε����� �ִ� ���͸� ���� �����Ѵ�. 
	void DeleteAllNPCInMapIndex(SI32 mapindex);

	// ������� ���� ���ο� ������� ����ġ�� �ش�.
	void IncExp(SI32 personid, SI32 exp, SI32 reason);
	
	// ������� ���� ���ο� ������� �� ����ġ�� �ش�.
	void IncFameExp(SI32 personid, SI32 exp, SI32 serverreason, SI32 dbreason);


	// Ư�� ������ ���� ��ġ�ϰ� �ִ� �ش� ���� �ֹε��� ����Ʈ. 
	void FindResidentListInVillage(SI32 villageunique);

	// Ư�� �����ȿ� �ִ� ������� ���� �Ա��� ������Ų��.
	void WarpToVillageGate(SI32 villageunique);

	// ��� ������� ���� �缳���Ѵ�. 
	void InitBlock();

	// ����ڿ��� �������� �ش�. 
	void GiveItem(SI16 charunique, SI16 itemunique, SI16 itemnum, SI16 itemgivemode, SI32 inputmode,SI32 usedate, SI32 senderID = 0, SI32 level = 0, SI32 VillageUnique = 0, SI32 EnchantType = 0, SI32 EnchantLevel = 0, SI32 SlotNum = 0 );

	void GiveItemForVillageMember(cltItem clitem , SI32 villageunique,SI32 inputmode = 0 );
	
	// ĳ���� ���� ��� 
	void GetStatistic(cltStatistics* pclstatistic);


	// ���Ǳ��� ���� ������ �����Ѵ�. 
	bool SortBlackWarRecord(SI32* pchar, SI32 num);
	// ���� ������ �����Ѵ�. 
	bool SortWarRecord(SI32* pchar, SI32 num, SI32 warmapindex);

	
	// ���� �Ƿ� ������ �ϳ� ���Ѵ�. 
	bool GetPersonalShopMakeInfo(TCHAR* pname, SI16 txtSize, SI16* pitemunique, SI32* pitemnum, GMONEY* pfee, SI32* pskill, SI32* phand);

	
	cltCharCommon* GetChar(SI32 charid)
	{
		if(IsValidID(charid) == false)		return NULL;

		return CR[charid];
	}

	cltCharClient* GetCharClient(SI32 id);
	cltCharServer* GetCharServer(SI32 id);
};

// LUA Function
int GetCharIDFromName(lua_State* L);
int GetCharNameFromID(lua_State* L);
int MoveChar(lua_State* L);
int WarpChar(lua_State* L);
int GetCharPos(lua_State* L);
int GetCharOrder(lua_State* L);
int GetCharHaveItemNum(lua_State* L);
int GetCharEquipItemNum(lua_State* L);

#endif
