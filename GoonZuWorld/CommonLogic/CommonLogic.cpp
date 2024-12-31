//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "CommonLogic.h"
#include "Main.h"
#include "Char/CharCommon/Char-Common.h"
#include "NDataLoader.h"
#include "NFile.h"
#include "NUtil.h"

#include "WarRank/WarRank.h"

#include "../resource.h"

#include "./MsgType-System.h"

//-------------------------
// CommonLogic513

//-------------------------
#include "DevTool/DevCharInfo/DevCharInfo.h"
#include "DevTool/DevNPCInfo/DevNPCInfo.h"
#include "DevTool/DevProfileInfo/DevProfileInfo.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "DevTool/DevInHereMapChar/DevInHereMapChar.h"
#include "BlackArmy/BlackArmy.h"
#include "Koinobory/Koinobory.h"
#include "SantaRaccoon/SantaRaccoon.h"
#include "KoinoboryFamily/KoinoboryFamily.h"
#include "WorldMoneyMgr/WorldMoneyMgr.h"
#include "WorldTraderMgr/WorldTraderManager.h"

#include "GachaManager\GachaManager.h"
#include "Gacha2Manager\Gacha2Manager.h"
#include "ArtifactRestoreManager/ArtifactRestoreManager.h"
#include "FourLeafManager/ForleafManager.h"
#include "PartyQuestMgr/PartyQuestMgr_Common.h"

//-------------------------
// Common
//-------------------------
#include "../Common/SystemNPC/SystemNPC.h"
#include "../Common/NPCManager/NPC.h"

#include "../Common/Event/Hunting/Hunting.h"
#include "../Common/Event/MofuMofu/MofuMofu.h"
#include "../Common/Bullet/Bullet.h"
#include "../Common/GameMaster/GameMaster.h"
#include "../Common/Smoke/Smoke.h"
#include "Char/CharManager/CharManager.h"
#include "Map/FieldObject/FieldObject.h"
#include "../common/Char/MonsterGroupManager/MonsterGroupManager.h"
#include "../common/Item/ItemCommon/Item-GuildDungeon.h"
#include "../common/Item/ItemCommon/Item-EventStructure.h"

#include "../common/event/event.h"

//--------------------------
// Client
//--------------------------
#include "../Client/SmallMap/SmallMap.h"

#include "../Client/StatusBar/ChatStatusBar/ChatStatusBarBaseInfo.h"
#include "../Client/StatusBar/ChatStatusBar/ChatStatusBar.h"

#include "../Client/Registry/RegistryMgr.h"

// ä����
#include "../Common/Agriculture/Mining/MiningMgr.h"

// ���� ���� NPC 
#include "../Common/SystemNPC/ForeignMerchantNPC/ForeignMerchantNPC.h"
// ���� ���� NPC
#include "../Common/SystemNPC/TradeMerchantNPC/TradeMerchantNPC.h"
// ��õ ����Ʈ ��ǰ ������
#include "../Common/SystemNPC/RPMerchantNPC/RPMerchantNPC.h"

// ���ΰ� �ŷ�
#include "../Common/PrivateTradeOrderMgr/PrivateTradeOrderMgr.h"
// ��Ƽ �ý���
#include "../Common/PartyMgr/PartyMgr.h"
// ���� ������. 
#include "../Common/Ask/Ask.h"
//�ֽ� ����
#include "../Common/StockDistributionMgr/StockDistributionMgr.h"
//��ǥ
#include "../Common/VoteMgr/VoteMgr.h"
//Daily Quest
#include "../Common/DailyQuest/DailyQuestMgr.h"
//Daily Quest2
#include "../Common/DailyQuest2/DailyQuest2Mgr.h"
//Daily Quest3
#include "../Common/DailyQuest3/DailyQuest3Mgr.h"
// ���� 
#include "MagicMgr/MagicMgr.h"
// ��� 
#include "../Common/Skill/Skill-Manager.h"
//quest
#include "../Common/Quest/Quest.h"
#include "../Common/Quest/NamingQuest.h"
// ���� 
#include "Master/Master.h"
#include "../Client/NInterface/NMaster/NMaster.h"

#include "../client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../Common/Order/Order.h"
//#include "../Common/School/School.h"
#include "../Common/Father/Father.h"

#include "../Common/Fishing/FishingMgr.h"
#include "../Common/Farming/FarmingMgr.h"
#include "../Common/SystemNPC/ForeignMerchantNPC/ForeignMerchantNPCBuyCashItem.h"

#include "../Common/GameEvent/GameEvent.h"

#include "../common/HuntMapInfo/HuntMapInfo.h"

// [����] ���� ���� ��ǥ �޴���
#include "../Common/VoteMgr/VoteStatusMgr.h"
// [����] PVP_League �Ŵ���
#include "../Common/PVP_Leage/PVP_LeageMgr.h"

// ������ �� �Ŵ���

// �ڵ� ��� üũ �Ŵ���
#include "../common/AutoHunting/AutoHunting.h"

#include "../Client/Cursor/Cursor.h"

#include "Msg/MsgType-Quest.h"

// �ǹ�
#include "../CommonLogic/Cityhall/Cityhall.h"
#include "../CommonLogic/Bank/Bank-Manager.h"
#include "../CommonLogic/Stock/Stock.h"
#include "../CommonLogic/Market/Market.h"
#include "../CommonLogic/House/House.h"
#include "../CommonLogic/Hunt/Hunt.h"
#include "../CommonLogic/PostOffice/PostOffice.h"
#include "../CommonLogic/HorseMarket/HorseMarket.h"
#include "../CommonLogic/RealEstate/RealEstate.h"
#include "../CommonLogic/SummonMarket/SummonMarket.h"
#include "../CommonLogic/Land/Land.h"
#include "../CommonLogic/Feast/Feast.h"
#include "../CommonLogic/SummonHeroMarket/SummonHeroMarket.h"
#include "../CommonLogic/Mine/Mine.h"
#include "../CommonLogic/Guild/Guild.h"

#include "../CommonLogic/HiredNPCMgr/HiredNPCMgr.h"

#include "../Client/Interface/ServerOnStepNotifyDlg/ServerOnStepNotifyDlg.h"

#include <Mouse.h>

#include "../Client/NInterface/NTeacherDlg/TeacherDlg.h"
#include "../Client/NInterface/NTeacherDlg/FatherDlg.h"
#include "../Client/NInterface/NTeacherDlg/ChildDlg.h"
#include "NInterface/NItemMallManager/NItemMallManager.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../CommonLogic/Guild/GuildHuntMapWarStatMgr.h"

#include "../CommonLogic/Marriage/MarriageManager.h"

#include "../common/RacoonDodgeEvent/RacoonDodgeEvent.h"

#include "HuntQuestItemMgr/HuntQuestItemMgr.h"

#include "NTextManager.h"

#include "GZFtp.h"

cltCommonLogic*	GetCommonLogic() { return pclClient; }
cltClient* GetClientClass() { return ((cltClient*)pclClient); }
cltServer* GetServerClass() { return ((cltServer*)pclClient); }

extern	BOOL	GZFtpSendFunc( DWORD dwID, SI32 sipersonid_from, SI32 sipersonid_to, CHAR *buffer, LONG size );
extern	VOID	GZFtpErrorHandleFunc( DWORD dwID, DWORD errorcode );
extern	VOID	GZFtpRecvCompletedFunc( DWORD dwID, CHAR *pszSenderName, CHAR *pszFileName );

NHashTableString< int >* GetGlobalHashTableString() { return pclClient->pclHashTableString; }

//extern cltTextMgr g_pTextMgr;
//extern cltHelpMgr g_pHelpMgr;
//extern cltTextMgr g_pStructureMgr;
// TextManager ����
extern NTextManager g_pTextManager;
extern NTextManager g_pItemTextManager;

extern BOOL		g_bFullScreen;		// Ǯ��ũ�� ���� 

void NCRCFileCheckManager::Init()
{
	if ( pclClient->IsWhereServiceArea(ConstServiceArea_English) )
	{
		AddFile("Item\\Data\\CashItemBuyInfoE.txt");
		AddFile("Item\\Data\\GachaRareItemListE.txt");
		AddFile("Item\\Data\\ItemTypeAnimalE.txt");
		AddFile("Item\\Data\\ItemTypeArmourE.txt");
		AddFile("Item\\Data\\ItemTypeAxeE.txt");
		AddFile("Item\\Data\\ItemTypeBagE.txt");
		AddFile("Item\\Data\\ItemTypeBeltE.txt");
		AddFile("Item\\Data\\ItemTypeBookE.txt");
		AddFile("Item\\Data\\ItemTypeBowE.txt");
		AddFile("Item\\Data\\ItemTypeClothE.txt");
		AddFile("Item\\Data\\ItemTypeDishE.txt");
		AddFile("Item\\Data\\ItemTypeDollE.txt");
		AddFile("Item\\Data\\ItemTypeDressE.txt");
		AddFile("Item\\Data\\ItemTypeEtcE.txt");
		AddFile("Item\\Data\\ItemTypeFishingRodE.txt");
		AddFile("Item\\Data\\ItemTypeFoodE.txt");
		AddFile("Item\\Data\\ItemTypeGunE.txt");
		AddFile("Item\\Data\\ItemTypeHatE.txt");
		AddFile("Item\\Data\\ItemTypeHealE.txt");
		AddFile("Item\\Data\\ItemTypeHelmetE.txt");
		AddFile("Item\\Data\\ItemTypeIronE.txt");
		AddFile("Item\\Data\\ItemTypeMantleE.txt");
		AddFile("Item\\Data\\ItemTypeMineralE.txt");
		AddFile("Item\\Data\\ItemTypeNeckE.txt");
		AddFile("Item\\Data\\ItemTypePaperE.txt");
		AddFile("Item\\Data\\ItemTypeQuestE.txt");
		AddFile("Item\\Data\\ItemTypeRingE.txt");
		AddFile("Item\\Data\\ItemTypeScrollE.txt");
		AddFile("Item\\Data\\ItemTypeSeafoodE.txt");
		AddFile("Item\\Data\\ItemTypeShoesE.txt");
		AddFile("Item\\Data\\ItemTypeSpearE.txt");
		AddFile("Item\\Data\\ItemTypeStaffE.txt");
		AddFile("Item\\Data\\ItemTypeSwordE.txt");
		AddFile("Item\\Data\\ItemTypeTicketE.txt");
		AddFile("Item\\Data\\ItemTypeTreeE.txt");
		//������ ������ �߰�
		/*AddFile("Item\\Data\\ItemTypeCrystalE.txt");
		AddFile("Item\\Data\\ItemTypeCompositionMaterialE.txt");
		AddFile("Item\\Data\\ItemTypeEventitemE.txt");
		AddFile("Item\\Data\\ItemTypeBoxE.txt");
		AddFile("Item\\Data\\ItemTypePremiumE.txt");*/

		AddFile("Item\\Data\\SetItemInfo.txt");
		AddFile("Item\\Data\\TradeRank.txt");

		AddFile("Data\\BookBox.txt");
		AddFile("Data\\CountryInfo.txt");
		AddFile("Data\\EmoticonInfo.txt");
		AddFile("Data\\EventStructure.txt");
		AddFile("Data\\FieldObjectSetInfo.txt");
		AddFile("Data\\FieldObjectTypeInfo.txt");
		AddFile("Data\\GateInfoE.txt");
		AddFile("Data\\GlobalValue.dat");
		AddFile("Data\\GMInfo.dat");
		AddFile("Data\\GuildDungeonItem.txt");
		AddFile("Data\\HuntMapInfo.txt");
		AddFile("Data\\KindInfo_BossItem.txt");
		AddFile("Data\\KindInfo_Chat.txt");
		AddFile("Data\\KindInfo_Create.txt");
		AddFile("Data\\KindInfo_SetFile.txt");
		AddFile("Data\\KindInfo_SetShadow.txt");
		AddFile("Data\\KindInfo_Unique.txt");
		AddFile("Data\\mapinfoE.txt");
		AddFile("Data\\MapTypeInfo.txt");
		AddFile("Data\\MapTypeInfo_Village.txt");
		AddFile("Data\\MonsterHome.txt");
		AddFile("Data\\OpeningBanner.txt");
		AddFile("Data\\RecommandProductE.txt");
		AddFile("Data\\SkillLimitInfo.txt");
		AddFile("Data\\SoundInfo.txt");
		AddFile("Data\\SoundInfo_Unique.txt");
		AddFile("Data\\TileSetInfo.txt");
		AddFile("Data\\villageinfoE.txt");

		AddFile("fishkind\\fishkindE.txt");

		AddFile("gimg\\mirror1.txt");
		AddFile("gimg\\mirror2.txt");
	}
	else if ( pclClient->IsWhereServiceArea(ConstServiceArea_Korea) )
	{
		AddFile("Item\\Data\\CashItemBuyInfoK.txt");
		AddFile("Item\\Data\\GachaRareItemListK.txt");
		AddFile("Item\\Data\\ItemTypeAnimalK.txt");
		AddFile("Item\\Data\\ItemTypeArmourK.txt");
		AddFile("Item\\Data\\ItemTypeAxeK.txt");
		AddFile("Item\\Data\\ItemTypeBagK.txt");
		AddFile("Item\\Data\\ItemTypeBeltK.txt");
		AddFile("Item\\Data\\ItemTypeBookK.txt");
		AddFile("Item\\Data\\ItemTypeBowK.txt");
		AddFile("Item\\Data\\ItemTypeClothK.txt");
		AddFile("Item\\Data\\ItemTypeDishK.txt");
		AddFile("Item\\Data\\ItemTypeDollK.txt");
		AddFile("Item\\Data\\ItemTypeDressK.txt");
		AddFile("Item\\Data\\ItemTypeEtcK.txt");
		AddFile("Item\\Data\\ItemTypeFishingRodK.txt");
		AddFile("Item\\Data\\ItemTypeFoodK.txt");
		AddFile("Item\\Data\\ItemTypeGunK.txt");
		AddFile("Item\\Data\\ItemTypeHatK.txt");
		AddFile("Item\\Data\\ItemTypeHealK.txt");
		AddFile("Item\\Data\\ItemTypeHelmetK.txt");
		AddFile("Item\\Data\\ItemTypeIronK.txt");
		AddFile("Item\\Data\\ItemTypeMantleK.txt");
		AddFile("Item\\Data\\ItemTypeMineralK.txt");
		AddFile("Item\\Data\\ItemTypeNeckK.txt");
		AddFile("Item\\Data\\ItemTypePaperK.txt");
		AddFile("Item\\Data\\ItemTypeQuestK.txt");
		AddFile("Item\\Data\\ItemTypeRingK.txt");
		AddFile("Item\\Data\\ItemTypeScrollK.txt");
		AddFile("Item\\Data\\ItemTypeSeafoodK.txt");
		AddFile("Item\\Data\\ItemTypeShoesK.txt");
		AddFile("Item\\Data\\ItemTypeSpearK.txt");
		AddFile("Item\\Data\\ItemTypeStaffK.txt");
		AddFile("Item\\Data\\ItemTypeSwordK.txt");
		AddFile("Item\\Data\\ItemTypeTicketK.txt");
		AddFile("Item\\Data\\ItemTypeTreeK.txt");

		AddFile("Item\\Data\\SetItemInfo.txt");
		AddFile("Item\\Data\\TradeRank.txt");

		AddFile("Data\\BookBox.txt");
		AddFile("Data\\CountryInfo.txt");
		AddFile("Data\\EmoticonInfo.txt");
		AddFile("Data\\EventStructure.txt");
		AddFile("Data\\FieldObjectSetInfo.txt");
		AddFile("Data\\FieldObjectTypeInfo.txt");
		AddFile("Data\\GateInfoK.txt");
		AddFile("Data\\GlobalValue.dat");
		AddFile("Data\\GMInfo.dat");
		AddFile("Data\\GuildDungeonItem.txt");
		AddFile("Data\\HuntMapInfo.txt");
		AddFile("Data\\KindInfo_BossItem.txt");
		AddFile("Data\\KindInfo_Chat.txt");
		AddFile("Data\\KindInfo_Create.txt");
		AddFile("Data\\KindInfo_SetFile.txt");
		AddFile("Data\\KindInfo_SetShadow.txt");
		AddFile("Data\\KindInfo_Unique.txt");
		AddFile("Data\\mapinfoK.txt");
		AddFile("Data\\MapTypeInfo.txt");
		AddFile("Data\\MapTypeInfo_Village.txt");
		AddFile("Data\\MonsterHome.txt");
		AddFile("Data\\OpeningBanner.txt");
		AddFile("Data\\RecommandProductK.txt");
		AddFile("Data\\SkillLimitInfo.txt");
		AddFile("Data\\SoundInfo.txt");
		AddFile("Data\\SoundInfo_Unique.txt");
		AddFile("Data\\TileSetInfo.txt");
		AddFile("Data\\villageinfoK.txt");

		AddFile("fishkind\\fishkindK.txt");

		AddFile("gimg\\mirror1.txt");
		AddFile("gimg\\mirror2.txt");
	}
	else if ( pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) )
	{
		AddFile("Item\\Data\\CashItemBuyInfoC.txt");
		AddFile("Item\\Data\\GachaRareItemListC.txt");
		AddFile("Item\\Data\\ItemTypeAnimalC.txt");
		AddFile("Item\\Data\\ItemTypeArmourC.txt");
		AddFile("Item\\Data\\ItemTypeAxeC.txt");
		AddFile("Item\\Data\\ItemTypeBagC.txt");
		AddFile("Item\\Data\\ItemTypeBeltC.txt");
		AddFile("Item\\Data\\ItemTypeBookC.txt");
		AddFile("Item\\Data\\ItemTypeBowC.txt");
		AddFile("Item\\Data\\ItemTypeClothC.txt");
		AddFile("Item\\Data\\ItemTypeDishC.txt");
		AddFile("Item\\Data\\ItemTypeDollC.txt");
		AddFile("Item\\Data\\ItemTypeDressC.txt");
		AddFile("Item\\Data\\ItemTypeEtcC.txt");
		AddFile("Item\\Data\\ItemTypeFishingRodC.txt");
		AddFile("Item\\Data\\ItemTypeFoodC.txt");
		AddFile("Item\\Data\\ItemTypeGunC.txt");
		AddFile("Item\\Data\\ItemTypeHatC.txt");
		AddFile("Item\\Data\\ItemTypeHealC.txt");
		AddFile("Item\\Data\\ItemTypeHelmetC.txt");
		AddFile("Item\\Data\\ItemTypeIronC.txt");
		AddFile("Item\\Data\\ItemTypeMantleC.txt");
		AddFile("Item\\Data\\ItemTypeMineralC.txt");
		AddFile("Item\\Data\\ItemTypeNeckC.txt");
		AddFile("Item\\Data\\ItemTypePaperC.txt");
		AddFile("Item\\Data\\ItemTypeQuestC.txt");
		AddFile("Item\\Data\\ItemTypeRingC.txt");
		AddFile("Item\\Data\\ItemTypeScrollC.txt");
		AddFile("Item\\Data\\ItemTypeSeafoodC.txt");
		AddFile("Item\\Data\\ItemTypeShoesC.txt");
		AddFile("Item\\Data\\ItemTypeSpearC.txt");
		AddFile("Item\\Data\\ItemTypeStaffC.txt");
		AddFile("Item\\Data\\ItemTypeSwordC.txt");
		AddFile("Item\\Data\\ItemTypeTicketC.txt");
		AddFile("Item\\Data\\ItemTypeTreeC.txt");
		//������ ������ �߰�
		/*AddFile("Item\\Data\\ItemTypeCrystalE.txt");
		AddFile("Item\\Data\\ItemTypeCompositionMaterialE.txt");
		AddFile("Item\\Data\\ItemTypeEventitemE.txt");
		AddFile("Item\\Data\\ItemTypeBoxE.txt");
		AddFile("Item\\Data\\ItemTypePremiumE.txt");*/

		AddFile("Item\\Data\\SetItemInfo.txt");
		AddFile("Item\\Data\\TradeRank.txt");

		AddFile("Data\\BookBox.txt");
		AddFile("Data\\CountryInfo.txt");
		AddFile("Data\\EmoticonInfo.txt");
		AddFile("Data\\EventStructure.txt");
		AddFile("Data\\FieldObjectSetInfo.txt");
		AddFile("Data\\FieldObjectTypeInfo.txt");
		AddFile("Data\\GateInfoC.txt");
		AddFile("Data\\GlobalValue.dat");
		AddFile("Data\\GMInfo.dat");
		AddFile("Data\\GuildDungeonItem.txt");
		AddFile("Data\\HuntMapInfo.txt");
		AddFile("Data\\KindInfo_BossItem.txt");
		AddFile("Data\\KindInfo_Chat.txt");
		AddFile("Data\\KindInfo_Create.txt");
		AddFile("Data\\KindInfo_SetFile.txt");
		AddFile("Data\\KindInfo_SetShadow.txt");
		AddFile("Data\\KindInfo_Unique.txt");
		AddFile("Data\\mapinfoC.txt");
		AddFile("Data\\MapTypeInfo.txt");
		AddFile("Data\\MapTypeInfo_Village.txt");
		AddFile("Data\\MonsterHome.txt");
		AddFile("Data\\OpeningBanner.txt");
		AddFile("Data\\RecommandProductC.txt");
		AddFile("Data\\SkillLimitInfo.txt");
		AddFile("Data\\SoundInfo.txt");
		AddFile("Data\\SoundInfo_Unique.txt");
		AddFile("Data\\TileSetInfo.txt");
		AddFile("Data\\villageinfoE.txt");

		AddFile("fishkind\\fishkindC.txt");

		AddFile("gimg\\mirror1.txt");
		AddFile("gimg\\mirror2.txt");
	}
	else if ( pclClient->IsWhereServiceArea(ConstServiceArea_EUROPE) )
	{
		AddFile("Item\\Data\\CashItemBuyInfoG.txt");
		AddFile("Item\\Data\\GachaRareItemListG.txt");
		AddFile("Item\\Data\\ItemTypeAnimalG.txt");
		AddFile("Item\\Data\\ItemTypeArmourG.txt");
		AddFile("Item\\Data\\ItemTypeAxeG.txt");
		AddFile("Item\\Data\\ItemTypeBagG.txt");
		AddFile("Item\\Data\\ItemTypeBeltG.txt");
		AddFile("Item\\Data\\ItemTypeBookG.txt");
		AddFile("Item\\Data\\ItemTypeBowG.txt");
		AddFile("Item\\Data\\ItemTypeClothG.txt");
		AddFile("Item\\Data\\ItemTypeDishG.txt");
		AddFile("Item\\Data\\ItemTypeDollG.txt");
		AddFile("Item\\Data\\ItemTypeDressG.txt");
		AddFile("Item\\Data\\ItemTypeEtcG.txt");
		AddFile("Item\\Data\\ItemTypeFishingRodG.txt");
		AddFile("Item\\Data\\ItemTypeFoodG.txt");
		AddFile("Item\\Data\\ItemTypeGunG.txt");
		AddFile("Item\\Data\\ItemTypeHatG.txt");
		AddFile("Item\\Data\\ItemTypeHealG.txt");
		AddFile("Item\\Data\\ItemTypeHelmetG.txt");
		AddFile("Item\\Data\\ItemTypeIronG.txt");
		AddFile("Item\\Data\\ItemTypeMantleG.txt");
		AddFile("Item\\Data\\ItemTypeMineralG.txt");
		AddFile("Item\\Data\\ItemTypeNeckG.txt");
		AddFile("Item\\Data\\ItemTypePaperG.txt");
		AddFile("Item\\Data\\ItemTypeQuestG.txt");
		AddFile("Item\\Data\\ItemTypeRingG.txt");
		AddFile("Item\\Data\\ItemTypeScrollG.txt");
		AddFile("Item\\Data\\ItemTypeSeafoodG.txt");
		AddFile("Item\\Data\\ItemTypeShoesG.txt");
		AddFile("Item\\Data\\ItemTypeSpearG.txt");
		AddFile("Item\\Data\\ItemTypeStaffG.txt");
		AddFile("Item\\Data\\ItemTypeSwordG.txt");
		AddFile("Item\\Data\\ItemTypeTicketG.txt");
		AddFile("Item\\Data\\ItemTypeTreeG.txt");
		//������ ������ �߰�
		/*AddFile("Item\\Data\\ItemTypeCrystalE.txt");
		AddFile("Item\\Data\\ItemTypeCompositionMaterialE.txt");
		AddFile("Item\\Data\\ItemTypeEventitemE.txt");
		AddFile("Item\\Data\\ItemTypeBoxE.txt");
		AddFile("Item\\Data\\ItemTypePremiumE.txt");*/

		AddFile("Item\\Data\\SetItemInfo.txt");
		AddFile("Item\\Data\\TradeRank.txt");

		AddFile("Data\\BookBox.txt");
		AddFile("Data\\CountryInfo.txt");
		AddFile("Data\\EmoticonInfo.txt");
		AddFile("Data\\EventStructure.txt");
		AddFile("Data\\FieldObjectSetInfo.txt");
		AddFile("Data\\FieldObjectTypeInfo.txt");
		AddFile("Data\\GateInfoG.txt");
		AddFile("Data\\GlobalValue.dat");
		AddFile("Data\\GMInfo.dat");
		AddFile("Data\\GuildDungeonItem.txt");
		AddFile("Data\\HuntMapInfo.txt");
		AddFile("Data\\KindInfo_BossItem.txt");
		AddFile("Data\\KindInfo_Chat.txt");
		AddFile("Data\\KindInfo_Create.txt");
		AddFile("Data\\KindInfo_SetFile.txt");
		AddFile("Data\\KindInfo_SetShadow.txt");
		AddFile("Data\\KindInfo_Unique.txt");
		AddFile("Data\\mapinfoG.txt");
		AddFile("Data\\MapTypeInfo.txt");
		AddFile("Data\\MapTypeInfo_Village.txt");
		AddFile("Data\\MonsterHome.txt");
		AddFile("Data\\OpeningBanner.txt");
		AddFile("Data\\RecommandProductG.txt");
		AddFile("Data\\SkillLimitInfo.txt");
		AddFile("Data\\SoundInfo.txt");
		AddFile("Data\\SoundInfo_Unique.txt");
		AddFile("Data\\TileSetInfo.txt");
		AddFile("Data\\villageinfoG.txt");

		AddFile("fishkind\\fishkindG.txt");

		AddFile("gimg\\mirror1.txt");
		AddFile("gimg\\mirror2.txt");
	}
}

void NCRCFileCheckManager::AddFile(const TCHAR* pszFileName)
{
	unsigned long filesize;
	UI32 crccode = m_CRC.CalculateCRCCode((TCHAR*)pszFileName, &filesize);

    if( crccode == 0 || filesize == 0 )		return;

	m_Files[m_siCount] = new NCRCFileCheck();
	if( m_Files[m_siCount] == NULL )		return;

	m_Files[m_siCount]->m_FileName		= pszFileName;
	m_Files[m_siCount]->m_siCRCCode		= crccode;
	m_Files[m_siCount]->m_siFileSize	= filesize;

	m_siCount++;
}

bool NCRCFileCheckManager::CheckFile(NCRCFileCheck* pCRCFileCheck)
{
	for (SI32 i=0; i<MAX_CRCFILECHECK_COUNT; i++)
	{
		NCRCFileCheck* pCRCCheck = m_Files[i];
		if(pCRCCheck == NULL)			continue;

		if( pCRCCheck->m_FileName == pCRCFileCheck->m_FileName &&
			pCRCCheck->m_siCRCCode == pCRCFileCheck->m_siCRCCode &&
			pCRCCheck->m_siFileSize == pCRCFileCheck->m_siFileSize )
		{
			return true;
		}
	}

	return false;
}

void NCRCFileCheckManager::RequestCheckFile()
{
	cltGameMsgRequest_FileCRCCheck	clCheck;

	for (int i=0; i<m_siCount; i++)
	{
		clCheck.CheckFileList[i].Set(m_Files[i]);
		clCheck.siCount++;
	}

	cltMsg clMsg(GAMEMSG_REQUEST_FILECRCCHECK, clCheck.GetSize(), (BYTE*)&clCheck);

	if( pclClient != NULL &&
		pclClient->pclCM != NULL &&
		pclClient->pclCM->CR[1] != NULL )
	{
		pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );
	}
}

cltCommonLogic::cltCommonLogic(TCHAR* appname, HWND hwnd, HINSTANCE hinst, SI32 gamemode,SI32 servicearea, SI32 rummode) 
{
	SI32 i;

	// CoCreateInstance�� ����ϱ� ���� COM�� �ʱ�ȭ�Ѵ�.
	CoInitialize(NULL);

	// �� ������ �⺻ ����. 
	siServerUnique					= 0;
	szServerID[0]					= '\0';

	siServiceArea					= servicearea;
	siMaster						= 0;

	bItemMallUseSwitch				= true;
	siMarketAutoBuyDelayFrame		= 10000;
	siHorseMarketAutoBuyDelayFrame	= 72000;
	siEventItemDropRate				= 100000;
	siMinimumTeacherLevel			= 20;

	// ���� ��带 �����Ѵ�. 
	GameMode = gamemode;

	// ���� ��带 �����Ѵ�. 
	siRunMode = rummode;

	StringCchCopy(SavePath, 256, TEXT(""));

	StringCchCopy(AppName, MAX_PATH, appname);
	SetHwnd(hwnd);
	SetInstance(hinst);

	SetFrame(0);

	pclMapManager				= NULL;

	pclGachaManager				= NULL;
	pclGacha2Manager				= NULL;
	pclArtifactRestoreManager	= NULL;

	pclFourLeafManager			= NULL;

	StartClock					= 0;
	CurrentClock				= 0;

	pclSkillManager				= NULL;
	pclItemManager				= NULL;

	pclConfig					= NULL;

	//pclTextMgr				= NULL;
	//pclStructureMgr			= NULL;

	pclHashTableString			= NULL;
	pclHashTableGlobalValue		= NULL;

	pclDiseaseManager			= NULL;
	pclCM						= NULL;
	pclMagicManager				= NULL;		// ���� ������. 
	pclKindInfoSet				= NULL;

	pclPersonNameManager		= NULL;

	pclBankManager				= NULL;
	pclStockManager				= NULL;
	pclCityHallManager			= NULL;
	pclMarketManager			= NULL;
	pclHouseManager				= NULL;
	pclHuntManager				= NULL;
	pclPostOfficeManager		= NULL;
	pclHorseMarketManager		= NULL;
	pclRealEstateMarketManager	= NULL;
	pclSummonMarketManager		= NULL;
	pclLandManager				= NULL;
	pclFeastManager				= NULL;
	pclSummonHeroMarketManager	= NULL;
	pclMineManager				= NULL;
	pclGuildManager				= NULL;
	//pclNewMarketManager		= NULL;
	pclNewMarketManager			= NULL;

	pclVillageManager				 = NULL;			// ���� ������ �����ϴ� �����̴�. 
	pclVillageStructureSet			 = NULL;
	pclAttackTypeInfoManager		 = NULL;
	pclSystemNPCManager				 = NULL;
	pclForeignMerchantNPCMgr		 = NULL;			// ���� ����(û, �Ϻ�) NPC
	pclMiningMgr					 = NULL;
	pclTradeMerchantNPCMgr			 = NULL;	
	pclOrderManager					 = NULL;

	pclPrivateTradeOrderMgr			 = NULL;
	pclPartyMgr						 = NULL;
	pclStockDistributionMgr			 = NULL;
	pclVoteMgr						 = NULL;
	pclDailyQuestMgr				 = NULL;
	pclDailyQuest2Mgr				 = NULL;
	pclDailyQuest3Mgr				 = NULL;
	pclFishingMgr					 = NULL;
	pclFarmingMgr					 = NULL;
	pclForeignMerchantNPCBuyCashItem = NULL;
	pclMonsterGroupManager			 = NULL;
	pclMasterManager				 = NULL;
	//	pclSchoolManager			 = NULL;
	pclFatherManager				 = NULL;
	pclNPCManager					 = NULL;
	pclHiredNPCPayManager			 = NULL;
	pclHorseManager					 = NULL;
	pclDormancySystem				= NULL;
	m_pclValentineEventMgr			= NULL;
	pclWarRankManager				= NULL;
	m_pclRewardItemByProbMgr		= NULL;

	//	pclItemMallManager			= NULL;
	//	pclItemMallButtonManager	= NULL;

	pclHashTableString			= NULL;

	// �Ұ��縮 ��� �̺�Ʈ. 
	pclEventHunting				= NULL;

	// ���ĸ��� ���� �̺�Ʈ. 
	pclMofuMofuEvent			= NULL;

	//[����] ���� �̺�Ʈ - ���� ���� => 2008-3-26
	pclMonsterAttackEvent		= NULL;

	// �ڵ� ��� üũ �Ŵ���
	pclAutoHuntingManager		= NULL;

	pclWorldTraderManager		= NULL;
	pclDistributionWorldMoney	= NULL;

	pclCountryManager			= NULL;
	pclCountryManagerJapan		= NULL;

	pclGuildDungeonItemMgr		= NULL;
	m_pCAbuseFilter				= NULL;

	pclQuestManager				= NULL;
	
	pclServerEventManager		= NULL;
	
	pclHelperManager			= NULL;

	// [����] PVP_League
	pclPVP_LeagueMgr			 = NULL;
	// [����] ��� ����� ���� ���� �Ŵ���
	pclGuildHuntMapManager		=	NULL;
	m_pclGuildHuntMapWarStatMgr	=	NULL;

	//[����] �������ϱ� �̺�Ʈ
	pclRacoonDodgeEventMgr	=	NULL	;

	siFrameDelay				= 50;

	siLanguage					= 0;

	dwPlatformId				= 0;
	dwMajorVersion				= 0;
	dwMinorVersion				= 0;
	wProductType				= 0;

	//---------------------------------
	// ������ Ŭ���̾�Ʈ�� �����ؾ��� ����. 
	//---------------------------------
	bVillageWarSwitch				= false;
	bBonusTimeSwitch				= false;		// ����ġ�� 2��� �ִ� �����̾� Ÿ���ΰ�������. 
	bBonus2TimeSwitch				= false;		// ���� ����ġ ��� Ÿ���ΰ�������. 
	bSpecialQuestBonusTimeSwitch	= false;		// ��ι�����Ʈ ���ʽ� Ÿ��. 
	bBroadcastSwitch				= false;
	bBonusTimeGoonzu				= false;

	siBestVillageLevel				= 0;

	siServiceAge					= 0;
	siEnablePVP						= 0;

	bTimeCount						=	false	;	// TimeSet���� ���õ� �ð��� Ÿ�� ī��Ʈ�� ���� �Ѵ� .
	siTimeSet						=	0	;
	siRoundCount					=	-1	;

	// [����] Auto Unblock - 2008.02.21
	bAutoUnblock		= false;

	bVoteCampaign		= false;

	for(i = 0;i < MAX_EVENT_NUMBER;i++)
	{
		bEventSwitch[i]		= false;
	}
	bEnchantSwitch = true;

	// [����] �̺�Ʈ ��� ����ġ
	for ( SI32 siIndex=0; siIndex<EVENT_TOGGLE_SWITCH_MAX; ++siIndex )
	{
		bEventToggleSwitch[siIndex] = false;
	}

	// [����] �̺�Ʈ ��� ����ġ ���ܻ�Ȳ(ó�� ���� ���ΰ��� �ٽ� ������ �ش�)
	bEventToggleSwitch[EVENT_TOGGLE_SWITCH_SYSTEMBUY] = true;

	// [���] ũ�������� �̺�Ʈ - �ʿ� ��ġ�Ǵ� ����Ʈ�� ID
	for ( i = 0; i < MAX_WORLDTREE_COUNT; ++i )
	{
		siWorldTreeID[i] = 0;
	}

	// [���] ũ�������� �̺�Ʈ - Ʈ���� �Ǽ��Ǿ����� ����
	bWorldTreeConstruct = false;

	dwWorldTreeCreateClock = 0;

	//----------------------------------
	//	NPC�� ������ ����. 
	//----------------------------------
	pclNPCItemInfo	= NULL;


	//---------------------------------
	// ���� ���. 
	//---------------------------------
	pclLog			= NULL;


	//-------------------------------
	// Ŀ�� 
	//-------------------------------
	pclCursor					= NULL;

	//-----------------------------
	// ���� ����.
	//-----------------------------
	for(i = 0;i < MAX_DEV_TOOL_NUM;i++)
	{
		pclDevTool[i] = NULL;
	}

	m_pclMarriageMgr = NULL;


	// ��ȭ�� ���� �Ŵ���
	m_pclBalanceCurrencyMgr = NULL;

	m_pclSoulGuardMgr		= NULL;

	
	//���Һ�
	m_pServer_BBBMgr			= NULL;

	// ��Ƽ��Ī
	m_pServer_PartyMatchingMgr	= NULL;

	m_pclBoxItemMgr				= NULL;

	m_pHuntQuestItemMgr = NULL;


	//------------------------------
	// ���� ����.  
	//------------------------------

	switch( siServiceArea )
	{
	case ConstServiceArea_Japan:	
		siVersion = 309; 
		break;
	case ConstServiceArea_English:
		siVersion = 573;
		break;
	case ConstServiceArea_China:
		siVersion = 149;
		break;
	case ConstServiceArea_Korea:
		siVersion = 515;
		break;
	case ConstServiceArea_Taiwan:
		siVersion = 505;
		break;
	case ConstServiceArea_USA:
		siVersion = 538;
		break;
	case ConstServiceArea_NHNChina:
		siVersion = 642;
		break;
	case ConstServiceArea_EUROPE:
		siVersion = 100;
		break;

	default:
		siVersion = 100;
		break;
	}

	DWORD dwBufferLen = _MAX_PATH-1;
	TCHAR DirectoryBuffer[_MAX_PATH];

	GetCurrentDirectory( dwBufferLen, DirectoryBuffer );

	// ������ ���������� ���´�.
	char FilePathBuffer[ MAX_PATH ] = "";
	::GetModuleFileName( NULL, FilePathBuffer, sizeof( FilePathBuffer ) );

	char Drive[_MAX_DRIVE];
	char Path[_MAX_PATH];
	char Filename[_MAX_FNAME];
	char Ext[_MAX_EXT];

	::_splitpath( FilePathBuffer, Drive, Path, Filename, Ext );

	char PathBuffer[ MAX_PATH ] = "";
	strcpy( PathBuffer, Drive );
	strcat( PathBuffer, Path );

	char szExeFileName[ MAX_PATH ] = "";
	strcpy( szExeFileName, Filename );
	strcat( szExeFileName, Ext );

	SetCurrentDirectory( DirectoryBuffer );

	// ������Ʈ���� ������ ����Ѵ�.
	CRegistryMgr RegistryMgr;

	NTCHARString128	kRegistryName;

	switch( siServiceArea )
	{
	case ConstServiceArea_Korea:	kRegistryName = "Software\\NDOORS\\GoonZuS";			break;
	case ConstServiceArea_China:	kRegistryName = "Software\\NDOORS\\GOONZUCHINA";		break;
	case ConstServiceArea_English:	kRegistryName = "Software\\NDOORS\\GoonZuEng";			break;
#ifdef	_JAPAN_USER_TEST
	case ConstServiceArea_Japan:	kRegistryName = "Software\\GamePot\\Kunshu User Test";	break;
#else
	case ConstServiceArea_Japan:	kRegistryName = "Software\\GamePot\\Kunshu Online";		break;
#endif
	case ConstServiceArea_Taiwan:	kRegistryName = "Software\\NDOORS\\GoonZuTaiwan";		break;
	case ConstServiceArea_USA:		kRegistryName = "Software\\NDOORS\\Luminary";			break;
	case ConstServiceArea_NHNChina:	kRegistryName = "Software\\NDOORS\\GoonZuC";			break;
	case ConstServiceArea_EUROPE:	kRegistryName = "Software\\NDOORS\\GoonZuEUROPE";		break;
	}

	switch(siRunMode)
	{
	case RUNMODE_DEBUG:		kRegistryName += "_debug";			break;
	case RUNMODE_TEST:		kRegistryName += "_test";			break;
	case RUNMODE_BETA:		kRegistryName += "_beta";			break;
	case RUNMODE_REAL:											break;
	case RUNMODE_INSIDE:	kRegistryName += "_inside";			break;
	}

	if ( RegistryMgr.RegistryCreateKey( HKEY_CURRENT_USER, kRegistryName, KEY_ALL_ACCESS ) )
	{
		RegistryMgr.SetRegWriteInt( TEXT("VERSION"), siVersion );
		RegistryMgr.RegistryCloseKey();
	}

	// ���İ� ������Ʈ �Ǿ��ٸ� ����
	if ( IsChangeFileExist() )
	{
		SetCurrentDirectory( PathBuffer );
		ChangeFile();

		//�۷ι��� �����.
		if( ConstServiceArea_English == siServiceArea ) 
		{
			MessageBox( NULL, "Game file has been updated. Please restart the game.", " warning", 0 );
			exit(1);
		}
	}

	// ���ӹ����� ���Ͽ� ���
	SetGameVersionInFile(siVersion);

	SetMasterArea();

	// ���� ����ġ ������ �д´�.
	LoadSwichCountry();

	cltGZFtp::InitializeStaticVariable( GZFtpSendFunc, GZFtpErrorHandleFunc, GZFtpRecvCompletedFunc );

#ifdef _DEBUG
	if( IsCountrySwitch(Switch_Durability) && IsCountrySwitch(Switch_NewDurability) )
	{
		MessageBox( NULL, "Switch_Durability����ġ�� Switch_NewDurability����ġ�� ���ÿ� ����� �� �����ϴ�.", "CountrySwitch ERROR", MB_OK );
	}
#endif
}

bool cltCommonLogic::IsChangeFileExist()
{
	WIN32_FIND_DATA	wfd;
	TCHAR srcFile[MAX_PATH];
	TCHAR descFile[MAX_PATH];
	switch( siServiceArea )
	{
	case ConstServiceArea_Japan:
		StringCchCopy( srcFile, MAX_PATH, TEXT("KunshuRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("C:\\KunshuRun1.exe") );
		break;
	case ConstServiceArea_EUROPE:
	case ConstServiceArea_USA:
		StringCchCopy( srcFile, MAX_PATH, TEXT("LuminaryRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("C:\\LuminaryRun1.exe") );
		break;
	default:
		StringCchCopy( srcFile, MAX_PATH, TEXT("GoonZuRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("C:\\GoonZuRun1.exe") );
		break;
	}

	HANDLE hSrch = FindFirstFile( srcFile, &wfd );

	if ( hSrch != INVALID_HANDLE_VALUE )
	{
		::CopyFile( srcFile, descFile, FALSE );
		::DeleteFile( srcFile );

		FindClose( hSrch );

		return true;
	}

	return false;
}

void cltCommonLogic::ChangeFile()
{
	WIN32_FIND_DATA	wfd;

	TCHAR srcFile[MAX_PATH];
	TCHAR descFile[MAX_PATH];
	switch( siServiceArea )
	{
	case ConstServiceArea_Japan:
		StringCchCopy( srcFile, MAX_PATH, TEXT("C:\\KunshuRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("KunshuRun.exe") );
		break;
	case ConstServiceArea_EUROPE:
	case ConstServiceArea_USA:
		StringCchCopy( srcFile, MAX_PATH, TEXT("C:\\LuminaryRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("LuminaryRun.exe") );
		break;
	default:
		StringCchCopy( srcFile, MAX_PATH, TEXT("C:\\GoonZuRun1.exe") );
		StringCchCopy( descFile, MAX_PATH, TEXT("GoonZuRun.exe") );
		break;
	}

	HANDLE hSrch = FindFirstFile( srcFile, &wfd );

	if ( hSrch != INVALID_HANDLE_VALUE )
	{

		::DeleteFile( descFile );
		// rename( TEXT("GoonZuRun1.exe"), TEXT("GoonZuRun.exe") );
		::CopyFile( srcFile, descFile, FALSE );
		::DeleteFile( srcFile );

		FindClose( hSrch );

		//�۷ι��� �����.
		if( ConstServiceArea_English == siServiceArea ) 
		{
            MessageBox( NULL, "Game file has been updated. Please restart the game.", " warning", 0 );
			exit(1);
		}
	}

	return;
}

void cltCommonLogic::Create()
{

	pclHashTableString = new NHashTableString< int >;
	pclHashTableString->CreateHashTableString( 2000, 5000, 64 );

	pclHashTableGlobalValue = new NHashTableString< SI64 >;
	pclHashTableGlobalValue->CreateHashTableString( 2000, 5000, 64 );

	// GlobalValue �ε� ��ġ ���� - by LEEKH 2009-07-27
	LoadGlobalValue();

	g_ServerOnStepNotifyDlg.LoadSpr( siServiceArea );

	g_ServerOnStepNotifyDlg.Set( 0 );

	//---------------------------------
	// ���� ���. 
	//---------------------------------
	pclLog	= new CLogPrint() ;
	if(pclLog)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("===GameStart GameMode:%d======"), GameMode);
	}

	//-------------------------------
	// Config������ �ҷ��´�. 
	//-------------------------------
	pclConfig = new cltConfig(TEXT("Config.Dat"));

	//------------------------------------
	// TextMgr ������ �о�´�.
	//------------------------------------
	//pclTextMgr = new cltTextMgr();

	SI32 textcolnum = GetTextColumn();

	g_pTextManager.CreateTextManager();
	g_pItemTextManager.CreateTextManager();

	TCHAR szTextMgrFileName[MAX_PATH] = TEXT("");
	TCHAR szItemMgrFileName[MAX_PATH] = TEXT("");

#ifdef _DEV
	StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_DEV.ntx") );
	StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_DEV.ntx") );
#else
    switch ( pclClient->siServiceArea )
	{
	case ConstServiceArea_Korea:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_KOR.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_KOR.ntx") );
		}
		break;
	case ConstServiceArea_Japan:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_JPN.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_JPN.ntx") );
		}
		break;
	case ConstServiceArea_China:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_CHI.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_CHI.ntx") );
		}
		break;
	case ConstServiceArea_English:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_ENG.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_ENG.ntx") );
		}
		break;
	case ConstServiceArea_Taiwan:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_TAI.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_TAI.ntx") );
		}
		break;
	case ConstServiceArea_USA:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_ENG.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_ENG.ntx") );
		}
		break;
	case ConstServiceArea_NHNChina:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_CHI.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_CHI.ntx") );
		}
		break;
	case ConstServiceArea_EUROPE:
		{
			StringCchCopy( szTextMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Text_EUR.ntx") );
			StringCchCopy( szItemMgrFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Item_EUR.ntx") );
		}
		break;
	}
#endif

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		g_pTextManager.LoadTextFromCryptFile( szTextMgrFileName, 1 );
		g_pItemTextManager.LoadTextFromCryptFile( szItemMgrFileName, 1 );	
	}
	else
	{
		if ( pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
		{
			g_pTextManager.LoadTextFromCryptFile( szTextMgrFileName, 1 );
			g_pItemTextManager.LoadTextFromCryptFile( szItemMgrFileName, 1 );	
		}
		else
		{
			g_pTextManager.LoadTextFromFile( szTextMgrFileName, 1 );
			g_pItemTextManager.LoadTextFromFile( szItemMgrFileName, 1 );
		}
	}

	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	/*
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
			g_pTextManager.LoadTextFromCryptFile(TEXT("TextMgr\\TextMgr.txt"), textcolnum);
			g_pTextManager.LoadTextFromCryptFile(TEXT("TextMgr\\TextMgr2.txt"), textcolnum);	
	}
	else
	{
		if ( pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
		{
			g_pTextManager.LoadTextFromCryptFile(TEXT("TextMgr\\TextMgr.txt"), textcolnum);
			g_pTextManager.LoadTextFromCryptFile(TEXT("TextMgr\\TextMgr2.txt"), textcolnum);
		}
		else
		{
			g_pTextManager.LoadTextFromFile(TEXT("TextMgr\\TextMgr.txt"), textcolnum);
			g_pTextManager.LoadTextFromFile(TEXT("TextMgr\\TextMgr2.txt"), textcolnum);
		}
	}

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		g_pItemTextManager.LoadTextFromCryptFile(TEXT("TextMgr\\ItemTextMgr.txt"), textcolnum);	
	}
	else
	{
		g_pItemTextManager.LoadTextFromFile(TEXT("TextMgr\\ItemTextMgr.txt"), textcolnum);
	}
	*/

	//-------------------------------------
	// GM ������. 
	//-------------------------------------
	pclGMManager = new cltGameMasterManager;

	//-------------------------------
	// ��� ������.
	//-------------------------------
	pclOrderManager	= new cltOrderManager();

	//-------------------------------
	// �޽��� ��ü �ʱ�ȭ.
	//-------------------------------
	pclMessage = new cltMessage();

	//-----------------------
	// ����Ÿ�� ������.
	//-----------------------
	pclAttackTypeInfoManager = new cltAttackTypeInfoManager();

	g_ServerOnStepNotifyDlg.Set( 5 );

	//------------------------
	// ���NPC ������
	//------------------------
	pclHiredNPCPayManager = new cltHiredNPCPayManager;

	//------------------------
	// ���� ����(û, �Ϻ�) NPC ������
	//------------------------
	pclForeignMerchantNPCMgr = new CForeignMerchantNPCMgr();


	//------------------------
	// ���� ���� NPC ������
	//------------------------
	pclTradeMerchantNPCMgr = new CTradeMerchantNPCMgr();
	
	//-------------------------
	// ��õ ����Ʈ�� �����ϴ� ��ǰ ������
	//-------------------------
	pclRPMerchantNPCMgr	= new CRPMerchantNPCMgr();


	//------------------------
	// ���ΰ� �ŷ�
	//------------------------
	pclPrivateTradeOrderMgr = new CPrivateTradeOrderMgr();

	//------------------------
	// ��Ƽ �ý���
	//------------------------
	pclPartyMgr = new CPartyMgr();


	//------------------------
	// �ֽ� ����
	//------------------------
	pclStockDistributionMgr = new CStockDistributionMgr();

	//------------------------
	// ��ǥ
	//------------------------
	pclVoteMgr = new CVoteMgr();


	pclWarRankManager = new cltWarRankManager();


	g_ServerOnStepNotifyDlg.Set( 10 );

	//------------------------
	// Daily Quest
	//------------------------
	pclDailyQuestMgr = new CDailyQuestMgr();
	//------------------------
	// Daily Quest2
	//------------------------
	pclDailyQuest2Mgr = new CDailyQuest2Mgr();
	//------------------------
	// Daily Quest3
	//------------------------
	pclDailyQuest3Mgr = new CDailyQuest3Mgr();

	//------------------------
	// ��	`�� ������. 
	//------------------------
	//pclAskManager = NULL;//new cltAskManager();
	//------------------------
	// PVP_League
	//------------------------
	pclPVP_LeagueMgr = new CPVP_LeagueMgr();
	if ( pclPVP_LeagueMgr )
	{
		pclPVP_LeagueMgr->PVP_LeagueGradeInfo();	// �׷��̵� ����� �о� �´�.
		pclPVP_LeagueMgr->PVP_LeagueMapInfo();		// �������� �о� �´�.
	}
	// [����] ��� ����� ���� ����� �Ŵ���.
	pclGuildHuntMapManager		=	new cltGuildHuntMapWarManager();
	m_pclGuildHuntMapWarStatMgr =	new cltGuildHuntMapWarStatMgr();

	// [����] ���� ���ϱ� �̺�Ʈ 
	pclRacoonDodgeEventMgr =	new CRacoonDodgeEventMgr();

	g_ServerOnStepNotifyDlg.Set( 11 );


	SI32 maxsize, maxmessage;
	if(GameMode == GAMEMODE_SERVER)
	{
		maxsize		= 100000;
		maxmessage	= 10000;
	}
	else
	{
		maxsize		= 10000;
		maxmessage	= 1000;
	}

	//--------------------------------
	// ���� ������. 
	//-------------------------------
	pclMagicManager	= new CMagicMgr();

	//---------------------------
	// ������ 
	//---------------------------
	if(GameMode == GAMEMODE_SERVER)
	{
		pclItemManager		= new cltItemManagerServer(GameMode);
	}
	else
	{
		pclItemManager		= new cltItemManagerClient(Hwnd, GameMode);
	}

	pclItemManager->Create();

	g_ServerOnStepNotifyDlg.Set( 15 );

	pclTileManager			= new cltTileManager(SavePath); 

	g_ServerOnStepNotifyDlg.Set( 12 );
	pclFieldObjectManager	= new cltFieldObjectManager(GameMode); 

	g_ServerOnStepNotifyDlg.Set( 13 );
	pclVillageStructureSet	= new cltVillageStructureSet();


	//-------------------------------
	// ��� ������. 
	//-------------------------------
	pclSkillManager		= new cltSkillManager();

	g_ServerOnStepNotifyDlg.Set( 14 );

	//------------------------------------
	// KindInfo ����
	//------------------------------------
	pclKindInfoSet = new cltKindInfoSet();


	//----------------------------------
	//	NPC�� ������ ����. 
	//----------------------------------
	pclNPCItemInfo = new cltNPCItemInfo(pclItemManager) ;
	pclNPCItemInfo->Create(0);


	//------------------------
	// �ý��� NPC ������. 
	//------------------------
	pclSystemNPCManager	= new cltSystemNPCManager();

	//------------------------------------
	// ���� ������. 
	//------------------------------------
	pclDiseaseManager = new cltDiseaseManager();

	//------------------------------------
	// �� ������. 
	//------------------------------------
	pclHorseManager	= new cltHorseManager();

	//----------------------------
	// ĳ���� ����. 
	//----------------------------
	pclCM = new cltCharManager(GameMode);

	//------------------------------------------
	// ���߿� �ʿ��� ���� ��. 
	//------------------------------------------
	pclDevTool[DEV_TOOL_CHARINFO]	= new cltDevCharInfo(pclCM);
	pclDevTool[DEV_TOOL_NPCINFO]	= new cltDevNPCInfo(pclCM);
	pclDevTool[DEV_TOOL_PROFILEINFO]= new cltDevProfileInfo();
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		pclDevTool[DEV_TOOL_SERVERINFO]	= new cltDevServerInfo();
		pclserverinfoDlg = (cltDevServerInfo*)pclDevTool[DEV_TOOL_SERVERINFO];
		CreateDevServerInfoDlg();//â�� ���������
	}
	pclDevTool[DEV_TOOL_INHEREMAPCHAR]	= new cltDevInHereMapChar(pclCM);



	g_ServerOnStepNotifyDlg.Set( 20 );

	//------------------------------------------
	// ���� �ǹ� ������. 
	//------------------------------------------
	pclBankManager				= new cltBankManager( pclCM,			RANKTYPE_BANK, TEXT("Interface/Portrait/Portrait_Bank.bmp"));
	pclStockManager				= new cltStockManager(pclCM, GameMode,	RANKTYPE_STOCK, TEXT("Interface/Portrait/Portrait_Stock.bmp"));

	g_ServerOnStepNotifyDlg.Set( 21 );


	pclCityHallManager			= new cltCityHallManager(pclCM, GameMode, RANKTYPE_CITYHALL, TEXT("Interface/Portrait/Portrait_CityHall.bmp"));
	pclMarketManager			= new cltMarketManager(pclCM, GameMode, RANKTYPE_MARKET, TEXT("Interface/Portrait/Portrait_Market.bmp" ));

	g_ServerOnStepNotifyDlg.Set( 22 );

	pclHouseManager				= new cltHouseManager(pclCM, GameMode, RANKTYPE_HOUSE, TEXT("Interface/Portrait/Portrait_House.bmp" ));
	pclHuntManager				= new cltHuntManager(pclCM, GameMode, RANKTYPE_HUNT, TEXT("Interface/Portrait/Portrait_House.bmp" ));

	g_ServerOnStepNotifyDlg.Set( 23 );

	pclPostOfficeManager		= new cltPostOfficeManager( pclCM, GameMode, RANKTYPE_POSTOFFICE, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));

	g_ServerOnStepNotifyDlg.Set( 24 );

	pclHorseMarketManager		= new cltHorseMarketManager( pclCM, GameMode, RANKTYPE_HORSEMARKET, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclRealEstateMarketManager	= new cltRealEstateMarketManager( pclCM, GameMode, RANKTYPE_REALESTATEMARKET, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclSummonMarketManager		= new cltSummonMarketManager( pclCM, GameMode, RANKTYPE_SUMMONMARKET, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclLandManager				= new cltLandManager( pclCM, GameMode, RANKTYPE_LAND, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclFeastManager				= new cltFeastManager( pclCM, GameMode, RANKTYPE_FEAST, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclSummonHeroMarketManager	= new cltSummonHeroMarketManager( pclCM, GameMode, RANKTYPE_SUMMONHEROMARKET, TEXT("Interface/Portrait/Portrait_PostOffice.bmp" ));
	pclMineManager				= new cltMineManager( pclCM, GameMode, RANKTYPE_MINE, TEXT("Interface/Portrait/Portrait_PostOffice.bmp"));
	pclGuildManager				= new cltGuildManager(pclCM,GameMode,RANKTYPE_GUILD, TEXT("Interface/Portrait/Portrait_PostOffice.bmp"));
	//[����] ���ո���.
	//pclNewMarketManager		= new cltNewMarketManager(pclCM, GameMode, RANKTYPE_NEWMARKET, TEXT("Interface/Portrait/Portrait_Market.bmp" ));	
	pclNewMarketManager			= new cltNewMarketManager(pclCM, GameMode, RANKTYPE_NEWMARKET, TEXT("Interface/Portrait/Portrait_Market.bmp" ));	
				 

	// ���� ������ �����Ѵ�. 
	pclVillageManager = new cltVillageManager(GameMode);
	pclVillageManager->LoadVillage(GameMode, siServiceArea);
	g_ServerOnStepNotifyDlg.Set( 25 );



	//-------------------------------
	// ���� ���� 
	//-------------------------------
	pclMapManager		= new cltMapManager(GameMode, siServiceArea, pclVillageManager);
	pclMapManager->Init();

	g_ServerOnStepNotifyDlg.Set( 26 );

	//--------------------------
	// Bullet
	//--------------------------
	pclBulletManager = new cltBulletManager(GameMode);

	//--------------------------
	// Smoke
	//--------------------------
	pclSmokeManager = new cltSmokeManager(GameMode);

	g_ServerOnStepNotifyDlg.Set( 27 );

	//--------------------------------
	// ����Ʈ ������. 
	//--------------------------------
	pclQuestManager = new cltQuestManager();

	pclNamingQuestManager = new cltNamingQuestManager();
	pclNamingQuestManager->LoadText( TEXT("Quest\\NamingQuest.txt") );


	g_ServerOnStepNotifyDlg.Set( 28 );
	
	//--------------------------------
	// �����۰� ����Ÿ���� �����Ѵ�. 
	//--------------------------------
	pclItemManager->ConnectDisease( pclDiseaseManager );
	pclItemManager->ConnectDiseaseType( pclDiseaseManager );

	g_ServerOnStepNotifyDlg.Set( 29 );

	//---------------------------------
	// Ŀ�� 
	//---------------------------------
	pclCursor = new cltCursor();

	g_ServerOnStepNotifyDlg.Set( 30 );


	//-------------------------------
	// ���� ������. 
	//-------------------------------
	pclMasterManager	= new cltMasterManager;

	//-------------------------------
	// �б� ������. 
	//-------------------------------
	//	pclSchoolManager	= new cltSchoolManager;

	//-------------------------------
	// ���� ������. 
	//-------------------------------
	pclFatherManager	= new cltFatherManager;

	//-------------------------------
	// ���Ǳ��� �̺�Ʈ ������
	//-------------------------------
	pclBlackWarManager	= new CBlackWarManager();

	//-------------------------------
	// ���Ǳ��� �̺�Ʈ ������
	//-------------------------------
	pclBlackArmyManager	= new cltBlackArmyManager();

	//-------------------------------
	// ���̳뺸�� �̺�Ʈ ������
	//-------------------------------
	pclKoinoboryManager = new cltKoinoboryManager();

	pclSantaRaccoonManager = new cltSantaRaccoonManager();

	pclKoinoboryFamilyManager = new	cltKoinoboryFamilyManager();

	//--------------------------------
	// �����޴���
	//-----------------------------------

	pclGachaManager = new CGachaManager();

	//--------------------------------
	// ����2�޴��� 
	
	//KHY - 1104 -  ����2 -���� ���� ����. 
	//-----------------------------------

	pclGacha2Manager = new CGacha2Manager();

	//--------------------------------
	// ��Ƽ��Ʈ ȯ�� ���� �޴��� �޸� ����.
	//-----------------------------------
	
	pclArtifactRestoreManager = new CArtifactRestoreManager();
	
	//--------------------------------
	// ����Ŭ�ι� �޴��� 
	//-----------------------------------

	pclFourLeafManager = new CFourLeafManager();

	m_pclMarriageMgr = new cltMarriageManager();

	//	[��ȣ] 20090526 ��ȭ�� ���� �Ŵ���
	m_pclBalanceCurrencyMgr = new CBalanceCurrencyMgr;

	m_pclSoulGuardMgr		= new cltSoulGuardMgr;


	//cltClient *pclclient = (cltClient*)pclClient;
	//----------------------------------
	// ������ �� �Ŵ���
	//--------------------------------
	// �¾� 4�� 21 �� �Ұ�.. ^^*
	if ( pclCM )
	{
		if ( GameMode == GAMEMODE_CLIENT )
		{
			//			pclItemMallManager = new cltItemMallManager;

			SI32 siCY = GetSystemMetrics(SM_CYCAPTION);
			//			pclItemMallButtonManager = new cltItemMallButtonManager(203,siCY+30);

		}
	}

	if ( GameMode == GAMEMODE_SERVER )
	{
		//-------------------------------------
		// [����] ���Һ� �̺�Ʈ �޴���
		//-------------------------------------
		m_pServer_BBBMgr = new CServer_BBBMgr;

		// ��Ƽ��Ī �Ŵ���
		m_pServer_PartyMatchingMgr = new CServer_PartyMatchingMgr();
	}

	m_pHuntQuestItemMgr = new CHuntQuestItemMgr;
	m_pHuntQuestItemMgr->Initialize();
	
	//---------------------------------------
	// ���� �׷� �Ŵ���
	//---------------------------------------
	if ( pclCM )
	{
		if ( GameMode == GAMEMODE_SERVER )
		{
			pclMonsterGroupManager = new cltMonsterGroupManager;
		}
	}

	g_ServerOnStepNotifyDlg.Set( 35 );


	if ( pclCM )
	{
		pclAutoHuntingManager = new cltAutoHuntingManager;

		if ( GameMode == GAMEMODE_SERVER )
		{
			pclAutoHuntingManager->Init();
		}
	}

	if(pclCM)
	{
		if(GameMode == GAMEMODE_SERVER)
		{
			pclNPCManager = new cltNPCManagerServer(pclCM);
		}
		else
		{
			pclNPCManager = new cltNPCManagerClient(pclCM);
		}
	}
	else
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("fd0832"), TEXT("2038222"), MB_OK|MB_TOPMOST);
	}

	//------------------------
	// ���� ������
	//------------------------
	pclFishingMgr = new CFishingMgr();

	//------------------------
	// ���
	//------------------------
	pclFarmingMgr = new CFarmingMgr();

	//------------------------
	// ĳ�� ������ ����
	//------------------------
	pclForeignMerchantNPCBuyCashItem = new CForeignMerchantNPCBuyCashItem();


	//------------------------
	// �Ұ��縮 ��� �̺�Ʈ 
	//------------------------
	pclEventHunting = new cltEventHunting();

	//------------------------
	// ���ĸ��� ���� �̺�Ʈ 
	//------------------------
	pclMofuMofuEvent = new cltMofuMofuEvent();

	//------------------------
	// ���� �̺�Ʈ - ���� ����. 
	//------------------------
	pclMonsterAttackEvent = new CMonsterAttackEvent;	

	//-------------------------
	// ���� �̺�Ʈ �Ŵ���
	//-----------------------
	pclGameEventManager = new cltGameEvent();

	//------------------------
	// ä����
	//------------------------
	pclMiningMgr = new CMiningMgr();

	//-----------------------
	// ������
	//------------------------
	pclWorldTraderManager = new cltWorldTraderManager();

	pclDistributionWorldMoney = new cltDistributionWorldMoney();

	//-------------------------
	// ���� ����
	//-------------------------
	pclCountryManager = new cltCountryManager();
	pclCountryManager->LoadTextFile( COUNTRY_WORLD );
	if( siServiceArea == ConstServiceArea_Japan )
	{
		pclCountryManagerJapan = new cltCountryManager();
		pclCountryManagerJapan->LoadTextFile( COUNTRY_JAPAN );
	}

	//---------------------------
	// �޸� ���� �ý���
	//---------------------------
	if(IsCountrySwitch(Switch_Dormancy))
	{
		pclDormancySystem	= new CDormancySystem(GameMode);
		pclDormancySystem->Create();
	}

	//---------------------------
	// Ȯ�� ���� ������ �Ŵ��� 
	//---------------------------
	m_pclRewardItemByProbMgr = new CRewardItemByProbMgr();
	m_pclRewardItemByProbMgr->Create();

	pclGuildDungeonItemMgr	= new cltGuildDungeonItem();

	pclEventStructure		= new cltEventStructure;

	pclEventTimeManager		= new cltEventTimeManager;
	pclEventTimeManager->Init();

	pclCRCFileCheckManager	= new NCRCFileCheckManager;
	pclCRCFileCheckManager->Init();

	pclVoteStatusMgr		= new CVoteStatusMgr;

	m_pCAbuseFilter = new CAbuseFilter();
	m_pCAbuseFilter->Create( TEXT("GImg\\mirror1.txt"), TEXT("GImg\\mirror2.txt") );

	m_pclBoxItemMgr = new CBoxItemMgr();
	if ( m_pclBoxItemMgr )
	{
		m_pclBoxItemMgr->LoadBoxItemInfo();
	}

	//[����] USA �弳 ���͸�.
#if defined (_IAF_EXPORT)
	int iRet = IAF::LoadAbuseDB();

	if( 0 != iRet )
	{
		MessageBox( NULL, "LoadAbuseDB() Fail", "Fail", NULL );
	}
#endif
	
	//if(IsCountrySwitch(Switch_Server_Event))
	{
		// ���� �̺�Ʈ �޸� �Ҵ�.
		pclServerEventManager = new CNServerEvent_Manager;
	}
	
	pclHelperManager = new cltHelperManager;

	InitNetwork();
	// ����ĳ���͸� pclCM�� �����Ѵ�. 
	SetSessionChar();

	g_ServerOnStepNotifyDlg.Set( 45 );


	// �⼮�� ���� ���� ����
	for (int i=0; i<MAX_ATTENDANCE_COUNT; i++)
	{
		m_pclAttendanceReward[i] = NULL;
	}

	// ���� ���� �⼮ ���� �������� �����Ѵ�.
	if(IsWhereServiceArea(ConstServiceArea_China))
	{
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 5410 ),	1, 0);
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 5400 ),	1, 0);
		SetItemByAttendanceDay(11, ITEMUNIQUE( 5600 ),	1, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 2740 ),	1, 0);
		SetItemByAttendanceDay(19, ITEMUNIQUE( 24096 ),	1, 0);
		SetItemByAttendanceDay(23, ITEMUNIQUE( 15900 ),	1, 30);
		SetItemByAttendanceDay(27, ITEMUNIQUE( 18170 ),	1, 30);
	}
	else if(IsWhereServiceArea(ConstServiceArea_English))
	{
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 2585 ),	100, 0);
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 13046 ),	1, 0);
		SetItemByAttendanceDay(11, ITEMUNIQUE( 3901 ),	1, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 3890 ),	1, 0);
		SetItemByAttendanceDay(19, ITEMUNIQUE( 24094 ),	1, 0);
		SetItemByAttendanceDay(23, ITEMUNIQUE( 5600 ),	1, 0);
		SetItemByAttendanceDay(27, ITEMUNIQUE( 7620 ),	1, 7);
	}
	else if(IsWhereServiceArea(ConstServiceArea_USA))
	{
		SetItemByAttendanceDay( 2, ITEMUNIQUE( 5410 ),	1, 0);
		SetItemByAttendanceDay( 5, ITEMUNIQUE( 2740 ),	1, 0);
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 2710 ),	1, 0);
		SetItemByAttendanceDay(10, ITEMUNIQUE( 7520 ),	1, 0);
		SetItemByAttendanceDay(13, ITEMUNIQUE( 5400 ),	1, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 15900 ),	1, 30);
		SetItemByAttendanceDay(18, ITEMUNIQUE( 18170 ),	1, 30);
	}
	else if(IsWhereServiceArea(ConstServiceArea_Japan))
	{
		/*SetItemByAttendanceDay( 3, ITEMUNIQUE( 13602 ),	1,	0);	// ������
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 5370 ),	5,	0);	// �ູ�� ��
		SetItemByAttendanceDay(11, ITEMUNIQUE( 5600 ),	1,	0);	// �����޴�
		SetItemByAttendanceDay(15, ITEMUNIQUE( 18205 ),	1,	7);	// ��Ǹ��� ����
		SetItemByAttendanceDay(19, ITEMUNIQUE( 24096 ),	1,	0);	// ����Ƽ��(7��)
		SetItemByAttendanceDay(23, ITEMUNIQUE( 24082 ),	2,	0);	// ���̾� ������
		SetItemByAttendanceDay(27, ITEMUNIQUE( 2756 ),	5,	0);	// ����� ���� Ŭ�ι�
		*/
		// �Ϻ� �⼮ üũ �̺�Ʈ ��ǰ ����. - 20090525
		//SetItemByAttendanceDay( 3, ITEMUNIQUE( 2725 ),	3,	0);	// ������������(48��)
		//SetItemByAttendanceDay( 7, ITEMUNIQUE( 18200 ),	1,	7);	// ��õ���� ����(7��)
		//SetItemByAttendanceDay(11, ITEMUNIQUE( 5600 ),	1,	0);	// �����޴�
		//SetItemByAttendanceDay(15, ITEMUNIQUE( 13634 ),	1,	0);	// ������
		//SetItemByAttendanceDay(19, ITEMUNIQUE( 24112 ),	1,	7);	// ���������̿��(7��)
		//SetItemByAttendanceDay(23, ITEMUNIQUE( 2756 ),	3,	0);	// ���Ŭ�ι�
		//SetItemByAttendanceDay(27, ITEMUNIQUE( 5370 ),	30,	0);	// �ູ�� ��

		SetItemByAttendanceDay( 3, ITEMUNIQUE( 2740 ),	1,	0);	// ������ Ż�� ��ȭ��
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 13602 ),	1,	0);	// ������ ������
		SetItemByAttendanceDay(11, ITEMUNIQUE( 24112 ),	1,	7);	// ���������̿��[7��]
		SetItemByAttendanceDay(15, ITEMUNIQUE( 13634 ),	2,	0);	// ������
		SetItemByAttendanceDay(19, ITEMUNIQUE( 5400 ),	5,	0);	// �Ⱓ�����ǵ�
		SetItemByAttendanceDay(23, ITEMUNIQUE( 7615 ),	1,	0);	// �������
		SetItemByAttendanceDay(27, ITEMUNIQUE( 5370 ),	40,	0);	// �ູ�� ��
	}
	// �븸 �⼮üũ �̺�Ʈ ����ǰ ���� (�Ϻ��������ϰ� ������. PCK - 07.12.29)
	// ��¥ ������ (08.01.04)
	else if(IsWhereServiceArea(ConstServiceArea_Taiwan))
	{
		/*
		SetItemByAttendanceDay( 5, ITEMUNIQUE( 24094 ), 1, 0);
		SetItemByAttendanceDay(10 , ITEMUNIQUE( 15910 ),  1, 7);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 7500 ),  1, 7);
		SetItemByAttendanceDay(20, ITEMUNIQUE( 5600 ), 1, 0);
		SetItemByAttendanceDay(25, ITEMUNIQUE( 3897 ),  5, 0);
		SetItemByAttendanceDay(30, ITEMUNIQUE( 18200 ), 1, 7);
		*/
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 2725 ),	2, 0);
		SetItemByAttendanceDay( 6, ITEMUNIQUE( 5400 ),	1, 0);
		SetItemByAttendanceDay(10, ITEMUNIQUE( 13326 ),	2, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 2756 ),	1, 0);
		SetItemByAttendanceDay(18, ITEMUNIQUE( 13319 ),	1, 0);
		SetItemByAttendanceDay(23, ITEMUNIQUE( 5600 ),	1, 0);
		SetItemByAttendanceDay(27, ITEMUNIQUE( 18150 ),	1, 100);
	}
	else if ( IsWhereServiceArea(ConstServiceArea_Korea) )
	{
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 5410 ),	1, 0);
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 5400 ),	1, 0);
		SetItemByAttendanceDay(11, ITEMUNIQUE( 5600 ),	1, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 2740 ),	1, 0);
		SetItemByAttendanceDay(19, ITEMUNIQUE( 24096 ),	1, 0);
		SetItemByAttendanceDay(23, ITEMUNIQUE( 15900 ),	1, 30);
		SetItemByAttendanceDay(27, ITEMUNIQUE( 18170 ),	1, 30);		
	}
	else if(IsWhereServiceArea(ConstServiceArea_NHNChina))
	{
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 5410 ),	1, 0);
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 5400 ),	1, 0);
		SetItemByAttendanceDay(11, ITEMUNIQUE( 5600 ),	1, 0);
		SetItemByAttendanceDay(15, ITEMUNIQUE( 2740 ),	1, 0);
		SetItemByAttendanceDay(19, ITEMUNIQUE( 24096 ),	1, 0);
		SetItemByAttendanceDay(23, ITEMUNIQUE( 15900 ),	1, 30);
		SetItemByAttendanceDay(27, ITEMUNIQUE( 18170 ),	1, 30);
	}
	else if(IsWhereServiceArea(ConstServiceArea_EUROPE))
	{
		SetItemByAttendanceDay( 3, ITEMUNIQUE( 24000 ),	5, 0);	// �����̵��̿�� 5��
		SetItemByAttendanceDay( 7, ITEMUNIQUE( 15900 ),	1, 30);	// ���� 30��
		SetItemByAttendanceDay(11, ITEMUNIQUE( 24112 ),	1, 0);	// �����̵��̿�� 7��
		SetItemByAttendanceDay(15, ITEMUNIQUE( 23080 ),	1, 15);	// �л����� 15��
		SetItemByAttendanceDay(19, ITEMUNIQUE( 23600 ),	1, 15);	// �л��Ǻ� 15��
		SetItemByAttendanceDay(23, ITEMUNIQUE( 18180 ),	1, 15);	// �л����� 15��
		SetItemByAttendanceDay(27, ITEMUNIQUE( 15900 ),	1, 30);	// ���� 30��
	}


}

cltCommonLogic::~cltCommonLogic()
{

	SI32 i;

	timeEndPeriod(1);

	// Ÿ�̸Ӹ� �����Ѵ�. 
	KillTimer(pclClient->GetHwnd(), 1);

	NDelete( m_pCAbuseFilter );
	NDelete( pclGuildDungeonItemMgr );
	NDelete( pclEventStructure );
	NDelete( pclEventTimeManager );
	NDelete( pclCountryManagerJapan );
	NDelete( pclCountryManager );
	NDelete( pclDistributionWorldMoney );
	NDelete(pclWorldTraderManager )

	NDelete( pclWarRankManager );
	NDelete( pclAutoHuntingManager );
	NDelete( pclGameEventManager);
	NDelete( pclEventHunting);
	NDelete( pclMofuMofuEvent);
	NDelete( pclMonsterAttackEvent );
	//	NDelete( pclItemMallButtonManager);
	//	NDelete( pclItemMallManager );
	NDelete( pclMonsterGroupManager);
	NDelete( pclKoinoboryFamilyManager );
	NDelete( pclKoinoboryManager );
	NDelete( pclSantaRaccoonManager );
	NDelete( pclBlackArmyManager );
	NDelete( pclBlackWarManager );
	NDelete( pclFatherManager);
	NDelete( pclMasterManager);
	NDelete( pclNPCManager);
	NDelete( pclHiredNPCPayManager);
	NDelete( pclNamingQuestManager);
	NDelete( pclQuestManager);
	NDelete( pclSmokeManager);
	NDelete( pclBulletManager);
	NDelete( pclItemManager);
	NDelete( pclTileManager);
	NDelete( pclVillageStructureSet );
	NDelete( pclFieldObjectManager);
	NDelete( pclVillageManager);
	NDelete( pclHuntManager);
	NDelete( pclHouseManager);
	NDelete( pclMarketManager);
	NDelete( pclCityHallManager);
	NDelete( pclStockManager);
	NDelete( pclBankManager);
	NDelete( pclPostOfficeManager);
	NDelete( pclHorseMarketManager);
	NDelete( pclRealEstateMarketManager);
	NDelete( pclSummonMarketManager);
	NDelete( pclLandManager);
	NDelete( pclFeastManager);
	NDelete( pclSummonHeroMarketManager);
	NDelete( pclMineManager);
	NDelete( pclGuildManager );
	//NDelete( pclNewMarketManager );
	NDelete( pclNewMarketManager );
	NDelete( pclDormancySystem );
	NDelete( m_pclValentineEventMgr );
	NDelete( m_pclRewardItemByProbMgr );

	for(i = 0; i < MAX_DEV_TOOL_NUM;i++)
	{
		NDelete( pclDevTool[i] );
	}

	NDelete( pclSkillManager);
	NDelete( pclSystemNPCManager);
	NDelete( pclForeignMerchantNPCMgr);
	NDelete( pclMiningMgr);
	NDelete( pclTradeMerchantNPCMgr);
	NDelete( pclRPMerchantNPCMgr);
	NDelete( pclPrivateTradeOrderMgr);
	NDelete( pclPartyMgr);
	NDelete( pclFishingMgr);
	NDelete( pclFarmingMgr);
	NDelete( pclForeignMerchantNPCBuyCashItem);
	NDelete( pclDailyQuestMgr);
	NDelete( pclDailyQuest2Mgr);
	NDelete( pclDailyQuest3Mgr);
	NDelete( pclVoteMgr);
	NDelete( pclStockDistributionMgr);
	NDelete( pclAttackTypeInfoManager);
	NDelete( pclMapManager);
	NDelete( pclCM);
	NDelete( pclHorseManager);
	NDelete( pclDiseaseManager);
	NDelete( pclKindInfoSet);
	NDelete( pclPersonNameManager );
	NDelete( pclNewPersonNameManager );
	NDelete( pclMagicManager);
	NDelete( pclNPCItemInfo);
	NDelete( pclMessage);
	NDelete( pclOrderManager);
	NDelete( pclGMManager);
	NDelete( pclConfig);
	NDelete( pclLog);
	NDelete( pclCursor);
	NDelete( pclHashTableString );
	NDelete( pclHashTableGlobalValue );
	NDelete( pclGachaManager );
	NDelete( pclGacha2Manager );
	NDelete( pclArtifactRestoreManager );
	NDelete( pclFourLeafManager );
	NDelete( pclCRCFileCheckManager );
	NDelete( pclVoteStatusMgr );
	NDelete( pclServerEventManager )
	NDelete( pclHelperManager )
	NDelete( pclPVP_LeagueMgr);
	NDelete( pclGuildHuntMapManager);
	NDelete( m_pclGuildHuntMapWarStatMgr);
	NDelete( m_pclMarriageMgr );
	NDelete( m_pclBalanceCurrencyMgr);
	NDelete( m_pclSoulGuardMgr );
	NDelete( pclRacoonDodgeEventMgr )	;
	NDelete( m_pServer_BBBMgr );
	NDelete( m_pServer_PartyMatchingMgr );
	NDelete( m_pclBoxItemMgr );
	NDelete(m_pHuntQuestItemMgr);
		

	// �⼮�� ���� ���� ����
	for ( i=0; i<MAX_ATTENDANCE_COUNT; i++ )
	{
		NDelete( m_pclAttendanceReward[i] );
	}

}


void cltCommonLogic::MainInit()
{

	// Ÿ�̸Ӹ� �����Ѵ�. �� Ÿ�̸Ӵ� ���� ������ ������Ʈ �ϱ� ���� Ÿ�̸��̴�. 
	SetTimer(GetHwnd(), 1, 2000, NULL);


	// �ʱ�ȭ. 
	Init();

	// �¶��ο��� ����� ����ġ�� ������ ȭ�Ͽ��� �о�´�. 
	LoadExpData();

	// GlobalValue �ε� ��ġ ���� - by LEEKH 2009-07-27
	// GlobalValue �����͸� �д´�.
    //LoadGlobalValue();

#ifdef _DEBUG
	SI32 siMaxDurability		= (SI32)pclClient->GetGlobalValue( TEXT("GV_MaxDurability") );
	SI32 siForeverDurability	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	if( siMaxDurability <= 0 )		{	MessageBox(NULL, "[GV_MaxDurability] �� �������� �ʾҽ��ϴ�.", "ERROR : GlobalValue.dat", MB_OK);		}
	if( siForeverDurability <= 0 )	{	MessageBox(NULL, "[GV_Forever_Durability] �� �������� �ʾҽ��ϴ�.", "ERROR : GlobalValue.dat", MB_OK);	}
	if( siForeverDurability2 <= 0 )	{	MessageBox(NULL, "[GV_Forever_Durability2] �� �������� �ʾҽ��ϴ�.", "ERROR : GlobalValue.dat", MB_OK);	}
#endif

	// ���������� ������ �д´�.
	if(GameMode == GAMEMODE_SERVER)
	{
		// ĳ���� �������� ���� ���� ���� �����͸� �о�´�.
		LoadLevelUpReward();
	}

	//���������� �д´�
	//if(GameMode == GAMEMODE_SERVER){

	//	pclFourLeafManager->LoadFourleafProductDataFromTxt();

	//}
	// timeGetTime()�� ������ �����Ѵ�.
	timeBeginPeriod(1);


	// ������ ���۵� �ð��� ���Ѵ�. 
	StartClock=timeGetTime();

	//----------------------------------
	// ������ �ε��Ѵ�. 
	//----------------------------------
	if(GameMode == GAMEMODE_SERVER)
	{
		pclMapManager->LoadAllMap(this);

		pclMapManager->SetCurrentMapIndex(0);

	}
	else if(GameMode == GAMEMODE_MAPEDIT)
	{
		pclMapManager->LoadMap(this, 0, 0);

		pclMapManager->SetCurrentMapIndex(0);

	}
	else 
	{
		// RESPONSE_LOGIN �޽����� ���� �� ������ �ҷ��´�.
	}


}

bool cltCommonLogic::LoadSwichCountry()
{
	NDataLoader	dataloader;
	BOOL bLoadFile = false;
	NTCHARString64	datafilename("Data\\CountrySwitch.txt");

	SI16 Counter	= 0;
	SI32 siUse		= 0;
	TCHAR szSwitchName[64];

	bool bReaded[Switch_Count];		// ��� ���� ����ġ�� �о������� �˻�
	ZeroMemory(bReaded, sizeof(bReaded));

	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( siServiceArea & ConstSwitch_TextEncryption )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datafilename);
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile(datafilename);
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("LoadSwichCountry()"), TEXT("LoadError:[%s]"), (TCHAR*)datafilename);
		return false;
	}	

	NDataTypeInfo pDataTypeInfo[] = 
	{
		NDATA_MBSTRING,	szSwitchName,	64,
		NDATA_INT32,	&siUse,		4,
		0,0,0
	};

	dataloader.RegDataType(pDataTypeInfo);

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			SI32 siIndex = ConvertSwitchCountryToIndex(szSwitchName);
			if(siIndex > 0)
			{
				if(siUse == 1)
					m_bitArray_SwitchContry.SetBit(siIndex);
				else
					m_bitArray_SwitchContry.ClearBit(siIndex);

				bReaded[siIndex - 1] = true;
			}
			else
			{
#ifdef _DEBUG
				NTCHARStringBuilder	kMsg;
				kMsg.SetFormat("�߸��� ���� ����ġ �Դϴ�. {1}") << szSwitchName;
				MessageBox(NULL, kMsg, "ERROR", MB_OK);
#endif
			}
		}
	}

	for(SI32 i=0; i<Switch_Count; i++)
	{
		if(bReaded[i] == false)
		{
#ifdef _DEBUG
			NTCHARStringBuilder	kMsg;
			kMsg.SetFormat("{1}�� ���� ����ġ�� ���ǵ��� �ʾҽ��ϴ�.") << i+1;
			MessageBox(NULL, kMsg, "ERROR", MB_OK);
#endif
		}
	}

	return true;
}

SI32 cltCommonLogic::ConvertSwitchCountryToIndex(TCHAR* pszSwitch)
{
	if     ( _tcscmp(pszSwitch, "Switch_AddCapitalRemove") == 0 )			return Switch_AddCapitalRemove;
	else if( _tcscmp(pszSwitch, "Switch_ChatBalloonLine") == 0 )			return Switch_ChatBalloonLine;
	else if( _tcscmp(pszSwitch, "Switch_EncryptTxtData") == 0 )				return Switch_EncryptTxtData;
	else if( _tcscmp(pszSwitch, "Switch_SummonEnolveVillageMoney") == 0 )	return Switch_SummonEnolveVillageMoney;
	else if( _tcscmp(pszSwitch, "Switch_EnchantNoSealing") == 0 )			return Switch_EnchantNoSealing;
	else if( _tcscmp(pszSwitch, "Switch_DateOverItemNoDestroy") == 0 )		return Switch_DateOverItemNoDestroy;
	else if( _tcscmp(pszSwitch, "Switch_ManufactureRevitalize") == 0 )		return Switch_ManufactureRevitalize;
	else if( _tcscmp(pszSwitch, "Switch_MakePerfectItem") == 0 )			return Switch_MakePerfectItem;
	else if( _tcscmp(pszSwitch, "Switch_DoNotFailedMakeItem") == 0 )		return Switch_DoNotFailedMakeItem;
	else if( _tcscmp(pszSwitch, "Switch_NotScailed") == 0 )					return Switch_NotScailed;
	else if( _tcscmp(pszSwitch, "Switch_ShowBuffToolTip") == 0 )			return Switch_ShowBuffToolTip;
	else if( _tcscmp(pszSwitch, "Switch_WENNYDISASSEMBLELEVEL") == 0 )		return Switch_WENNYDISASSEMBLELEVEL;
	else if( _tcscmp(pszSwitch, "Switch_WENNYBOXCHECKLEVEL") == 0 )			return Switch_WENNYBOXCHECKLEVEL;
	else if( _tcscmp(pszSwitch, "Switch_Event_Hunt") == 0 )					return Switch_Event_Hunt;
	else if( _tcscmp(pszSwitch, "Switch_Event_MofuMofu") == 0 )				return Switch_Event_MofuMofu;
	else if( _tcscmp(pszSwitch, "Switch_ToolTipAutoLine") == 0 )			return Switch_ToolTipAutoLine;
	else if( _tcscmp(pszSwitch, "Switch_DisplayLevelInPannel") == 0 )		return Switch_DisplayLevelInPannel;
	else if( _tcscmp(pszSwitch, "Switch_LevelUpAction") == 0 )				return Switch_LevelUpAction;
	else if( _tcscmp(pszSwitch, "Switch_NamingQuest") == 0 )				return Switch_NamingQuest;
	else if( _tcscmp(pszSwitch, "Switch_RecommendPointPerLevel") == 0 )		return Switch_RecommendPointPerLevel;
	else if( _tcscmp(pszSwitch, "Switch_MagicNeedDex") == 0 )				return Switch_MagicNeedDex;
	else if( _tcscmp(pszSwitch, "Switch_BaekNyeonSam") == 0 )				return Switch_BaekNyeonSam;
	else if( _tcscmp(pszSwitch, "Switch_FreshManHelpDialog") == 0 )			return Switch_FreshManHelpDialog;
	else if( _tcscmp(pszSwitch, "Switch_DalilyQuestGrayList") == 0 )		return Switch_DalilyQuestGrayList;
	else if( _tcscmp(pszSwitch, "Switch_GachaAvatarCorrect") == 0 )			return Switch_GachaAvatarCorrect;
	else if( _tcscmp(pszSwitch, "Switch_Help") == 0 )						return Switch_Help;
	else if( _tcscmp(pszSwitch, "Switch_EnableGuildWar") == 0 )				return Switch_EnableGuildWar;
	else if( _tcscmp(pszSwitch, "Switch_EnableVillageWar") == 0 )			return Switch_EnableVillageWar;
	else if( _tcscmp(pszSwitch, "Switch_StatusBug") == 0 )					return Switch_StatusBug;
	else if( _tcscmp(pszSwitch, "Switch_GuildstatusBugFix") == 0 )			return Switch_GuildstatusBugFix;
	else if( _tcscmp(pszSwitch, "Switch_reply") == 0 )						return Switch_reply;
	else if( _tcscmp(pszSwitch, "Switch_HappyBeanQuest") == 0 )				return Switch_HappyBeanQuest;
	else if( _tcscmp(pszSwitch, "Switch_Sound") == 0 )						return Switch_Sound;
	else if( _tcscmp(pszSwitch, "Switch_UseWebPageItemMall") == 0 )			return Switch_UseWebPageItemMall;
	else if( _tcscmp(pszSwitch, "Switch_ArchangelArchdevil") == 0 )			return Switch_ArchangelArchdevil;
	else if( _tcscmp(pszSwitch, "Switch_AuctionEvent") == 0 )				return Switch_AuctionEvent;
	else if( _tcscmp(pszSwitch, "Switch_GameRoomCouponEvent") == 0 )		return Switch_GameRoomCouponEvent;
	else if( _tcscmp(pszSwitch, "Switch_ServerListArray") == 0 )			return Switch_ServerListArray;
	else if( _tcscmp(pszSwitch, "Switch_WENNYBOXDisable") == 0 )			return Switch_WENNYBOXDisable;
	else if( _tcscmp(pszSwitch, "Switch_WENNYDISASSEMBLEAvata") == 0 )		return Switch_WENNYDISASSEMBLEAvata;
	else if( _tcscmp(pszSwitch, "Switch_HorseAbility") == 0 )				return Switch_HorseAbility;
	else if( _tcscmp(pszSwitch, "Switch_DyingDelay") == 0 )					return Switch_DyingDelay;
	else if( _tcscmp(pszSwitch, "Switch_DeleteLuckButton") == 0 )			return Switch_DeleteLuckButton;
	else if( _tcscmp(pszSwitch, "Switch_DeleteHandButton") == 0 )			return Switch_DeleteHandButton;
	else if( _tcscmp(pszSwitch, "Switch_GoStopPokerEvent") == 0 )			return Switch_GoStopPokerEvent;
	else if( _tcscmp(pszSwitch, "Switch_AutoHuntingReport") == 0 )			return Switch_AutoHuntingReport;
	else if( _tcscmp(pszSwitch, "Switch_MaterialBox") == 0 )				return Switch_MaterialBox;
	else if( _tcscmp(pszSwitch, "Switch_TeacherLevelReward") == 0 )			return Switch_TeacherLevelReward;
	else if( _tcscmp(pszSwitch, "Switch_KingGuriEvent") == 0 )				return Switch_KingGuriEvent;
	else if( _tcscmp(pszSwitch, "Switch_Health") == 0 )						return Switch_Health;
	else if( _tcscmp(pszSwitch, "Switch_FieldObjectPreLoad") == 0 )			return Switch_FieldObjectPreLoad;
	else if( _tcscmp(pszSwitch, "Switch_ItemmallNotDisassemble") == 0 )		return Switch_ItemmallNotDisassemble;
	else if( _tcscmp(pszSwitch, "Switch_GodHandItem") == 0 )				return Switch_GodHandItem;
	else if( _tcscmp(pszSwitch, "Switch_NewHitEffect") == 0 )				return Switch_NewHitEffect;
	else if( _tcscmp(pszSwitch, "Switch_Fairy") == 0 )						return Switch_Fairy;
	else if( _tcscmp(pszSwitch, "Switch_LevelupUpText") == 0 )				return Switch_LevelupUpText;
	else if( _tcscmp(pszSwitch, "Switch_BossWildBoar") == 0 )				return Switch_BossWildBoar;
	else if( _tcscmp(pszSwitch, "Switch_DonateDlg") == 0 )					return Switch_DonateDlg;
	else if( _tcscmp(pszSwitch, "Switch_Button6HozoDlg") == 0 )				return Switch_Button6HozoDlg;
	else if( _tcscmp(pszSwitch, "Switch_20levelparty") == 0 )				return Switch_20levelparty;
	else if( _tcscmp(pszSwitch, "Switch_Can5Horse") == 0 )					return Switch_Can5Horse;
	else if( _tcscmp(pszSwitch, "Switch_DropBookBox") == 0 )				return Switch_DropBookBox;
	else if( _tcscmp(pszSwitch, "Switch_WennyOldMan_CityhallProfitMoney") == 0 )	return Switch_WennyOldMan_CityhallProfitMoney;
	else if( _tcscmp(pszSwitch, "Switch_HanGameVIPEvent") == 0 )			return Switch_HanGameVIPEvent;
	else if( _tcscmp(pszSwitch, "Switch_NowComEvent") == 0 )				return Switch_NowComEvent;
	else if( _tcscmp(pszSwitch, "Switch_RepairMoney") == 0 )				return Switch_RepairMoney;
	else if( _tcscmp(pszSwitch, "Switch_Thanksgiving_day") == 0 )			return Switch_Thanksgiving_day;
	else if( _tcscmp(pszSwitch, "Switch_LotteryStockRandom") == 0 )			return Switch_LotteryStockRandom;
	else if( _tcscmp(pszSwitch, "Switch_PreDeleteChar") == 0 )				return Switch_PreDeleteChar;
	else if( _tcscmp(pszSwitch, "Switch_ChristmasEvent") == 0 )				return Switch_ChristmasEvent;
	else if( _tcscmp(pszSwitch, "Switch_NoCheckMapIndex_Quest") == 0 )		return Switch_NoCheckMapIndex_Quest;
	else if( _tcscmp(pszSwitch, "Switch_WarpInHuntMap") == 0 )				return Switch_WarpInHuntMap;
	else if( _tcscmp(pszSwitch, "Switch_SaveHorseToHouse") == 0 )			return Switch_SaveHorseToHouse;
	else if( _tcscmp(pszSwitch, "Switch_SantaRaccoonEvent") == 0 )			return Switch_SantaRaccoonEvent;
	else if( _tcscmp(pszSwitch, "Switch_SellToForeignMerchant") == 0 )		return Switch_SellToForeignMerchant;
	else if( _tcscmp(pszSwitch, "Switch_LevelUpNotice") == 0 )				return Switch_LevelUpNotice;
	else if( _tcscmp(pszSwitch, "Switch_NewYearEvent") == 0 )				return Switch_NewYearEvent;
	else if( _tcscmp(pszSwitch, "Switch_BasicStructureSet") == 0 )			return Switch_BasicStructureSet;
	else if( _tcscmp(pszSwitch, "Switch_VillageWarpTower") == 0 )			return Switch_VillageWarpTower;
	else if( _tcscmp(pszSwitch, "Switch_RaccoonGoldeggChange") == 0 )		return Switch_RaccoonGoldeggChange;
	else if( _tcscmp(pszSwitch, "Switch_Transform") == 0 )					return Switch_Transform;
	else if( _tcscmp(pszSwitch, "Switch_BlackWarReform") == 0 )				return Switch_BlackWarReform;
	else if( _tcscmp(pszSwitch, "Switch_ChangeFullScreen") == 0 )			return Switch_ChangeFullScreen;
	else if( _tcscmp(pszSwitch, "Switch_UseDefaultIME") == 0 )				return Switch_UseDefaultIME;
	else if( _tcscmp(pszSwitch, "Switch_InstanceDungeonTicket") == 0 )		return Switch_InstanceDungeonTicket;
	else if( _tcscmp(pszSwitch, "Switch_NONATIALIASED_QUALITY") == 0 )		return Switch_NONATIALIASED_QUALITY;
	else if( _tcscmp(pszSwitch, "Switch_PartyMassageimprovement") == 0 )	return Switch_PartyMassageimprovement;
	else if( _tcscmp(pszSwitch, "Switch_SpaceBox") == 0 )					return Switch_SpaceBox;
	else if( _tcscmp(pszSwitch, "Switch_HINADOLL") == 0 )					return Switch_HINADOLL;
	else if( _tcscmp(pszSwitch, "Switch_Puchikomi") == 0 )					return Switch_Puchikomi;
	else if( _tcscmp(pszSwitch, "Switch_Summon_Ability_Reform") == 0 )		return Switch_Summon_Ability_Reform;
	else if( _tcscmp(pszSwitch, "Switch_GeneralMeetingSuggest") == 0 )		return Switch_GeneralMeetingSuggest;
	else if( _tcscmp(pszSwitch, "Switch_Artifact") == 0 )					return Switch_Artifact;
	else if( _tcscmp(pszSwitch, "Switch_FixedPositionFeastEffect") == 0 )	return Switch_FixedPositionFeastEffect;
	else if( _tcscmp(pszSwitch, "Switch_ChatEditFilter") == 0 )				return Switch_ChatEditFilter;
	else if( _tcscmp(pszSwitch, "Switch_AutoMakeItem") == 0 )				return Switch_AutoMakeItem;
	else if( _tcscmp(pszSwitch, "Switch_ClickAndDrop") == 0 )				return Switch_ClickAndDrop;
	else if( _tcscmp(pszSwitch, "Switch_TutorialVillage") == 0 )			return Switch_TutorialVillage;
	else if( _tcscmp(pszSwitch, "Switch_PartyHall") == 0 )					return Switch_PartyHall;
	else if( _tcscmp(pszSwitch, "Switch_PirateShip") == 0 )					return Switch_PirateShip;
	else if( _tcscmp(pszSwitch, "Switch_PCRoom") == 0 )						return Switch_PCRoom;
	else if( _tcscmp(pszSwitch, "Switch_UseDayPlusRevitalize") == 0 )		return Switch_UseDayPlusRevitalize;
	else if( _tcscmp(pszSwitch, "Switch_CharStatusReform") == 0 )			return Switch_CharStatusReform;
	else if( _tcscmp(pszSwitch, "Switch_SpecialPersonShop") == 0 )			return Switch_SpecialPersonShop;
	else if( _tcscmp(pszSwitch, "Switch_HealthAddChange") == 0 )			return Switch_HealthAddChange;	
	else if( _tcscmp(pszSwitch, "Switch_Event_Monster_Attack") == 0 )		return Switch_Event_Monster_Attack;	
	else if( _tcscmp(pszSwitch, "Switch_BigItemModify") == 0 )				return Switch_BigItemModify;	
	else if( _tcscmp(pszSwitch, "Switch_MakeItemEXP") == 0)					return Switch_MakeItemEXP;	
	else if( _tcscmp(pszSwitch, "Switch_MarketBuyNew") == 0)				return Switch_MarketBuyNew;	
	
	if( _tcscmp(pszSwitch, "Switch_GongZoArmorPercent")				== 0)		return Switch_GongZoArmorPercent;
	else if( _tcscmp(pszSwitch, "Switch_Izo_TinTinPercent") 		== 0)		return Switch_Izo_TinTinPercent;
	else if( _tcscmp(pszSwitch, "Switch_SummonReform")				== 0)		return Switch_SummonReform;
	else if( _tcscmp(pszSwitch, "Switch_FishFarmMineChange")		== 0)		return Switch_FishFarmMineChange;
	else if( _tcscmp(pszSwitch, "Switch_FindInfo")					== 0)		return Switch_FindInfo;
	else if( _tcscmp(pszSwitch, "Switch_BlackArmyTicket")			== 0)		return Switch_BlackArmyTicket;
	else if( _tcscmp(pszSwitch, "Switch_NoPayBack")					== 0)		return Switch_NoPayBack;
	else if( _tcscmp(pszSwitch, "Switch_PopupCheck")				== 0)		return Switch_PopupCheck;
	else if( _tcscmp(pszSwitch, "Switch_Event_Hunt_Reform") 		== 0)		return Switch_Event_Hunt_Reform;
	else if( _tcscmp(pszSwitch, "Switch_Notice_Separate")			== 0)		return Switch_Notice_Separate;
	else if( _tcscmp(pszSwitch, "Switch_Char_Option")				== 0)		return Switch_Char_Option;
	else if( _tcscmp(pszSwitch, "Switch_Hero_Bronze_Statue")		== 0)		return Switch_Hero_Bronze_Statue;
	else if( _tcscmp(pszSwitch, "Switch_Summon_Separate")			== 0)		return Switch_Summon_Separate;
	else if( _tcscmp(pszSwitch, "Switch_Show_MapName")				== 0)		return Switch_Show_MapName;
	else if( _tcscmp(pszSwitch, "Switch_Server_Event")				== 0)		return Switch_Server_Event;
	else if( _tcscmp(pszSwitch, "Switch_Artifact_Reform")			== 0)		return Switch_Artifact_Reform;
	else if( _tcscmp(pszSwitch, "Switch_DestroyDropItem")			== 0)		return Switch_DestroyDropItem;
	else if( _tcscmp(pszSwitch, "Switch_ChangeHouseList")			== 0)		return Switch_ChangeHouseList;
	else if( _tcscmp(pszSwitch, "Switch_Summon_Market")				== 0)		return Switch_Summon_Market;
	else if( _tcscmp(pszSwitch, "Switch_Summon_EquipSton")			== 0)		return Switch_Summon_EquipSton;
	else if( _tcscmp(pszSwitch, "Switch_Summon_StaminaCharge")		== 0)		return Switch_Summon_StaminaCharge;
	else if( _tcscmp(pszSwitch, "Switch_MarketConditions")			== 0)		return Switch_MarketConditions;		
	else if( _tcscmp(pszSwitch, "Switch_Guild_DestroyOverMOnth")	== 0)		return Switch_Guild_DestroyOverMOnth;		
	else if( _tcscmp(pszSwitch, "Switch_Postoffice_Group_Message")	== 0)		return Switch_Postoffice_Group_Message;
	else if( _tcscmp(pszSwitch, "Switch_Guild_GuildMaster_Change")	== 0)		return Switch_Guild_GuildMaster_Change;
	else if( _tcscmp(pszSwitch, "Switch_QuestInfoDlg_Renewal")		== 0)		return Switch_QuestInfoDlg_Renewal;
	else if( _tcscmp(pszSwitch, "Switch_ShowQuestNotice")			== 0)		return Switch_ShowQuestNotice;
	else if( _tcscmp(pszSwitch, "Switch_FourLeaf")					== 0)		return Switch_FourLeaf;
	else if( _tcscmp(pszSwitch, "Switch_Homepage_link")				== 0)		return Switch_Homepage_link;
	else if( _tcscmp(pszSwitch, "Switch_SummonHouse")				== 0)		return Switch_SummonHouse;
	else if( _tcscmp(pszSwitch, "Switch_Gacha_Reform")				== 0)		return Switch_Gacha_Reform;
	else if( _tcscmp(pszSwitch, "Switch_Mykey")						== 0)		return Switch_Mykey;
	else if( _tcscmp(pszSwitch, "Switch_HalloweenEvent")			== 0)		return Switch_HalloweenEvent;
	else if( _tcscmp(pszSwitch, "Switch_MudangPresent")				== 0)		return Switch_MudangPresent;
	else if( _tcscmp(pszSwitch, "Switch_Trade_Renewal")				== 0)		return Switch_Trade_Renewal;
	else if( _tcscmp(pszSwitch, "Switch_GlobalItemMall_Limit")		== 0)		return Switch_GlobalItemMall_Limit;
	else if( _tcscmp(pszSwitch, "Switch_EditWordBreak")				== 0)		return Switch_EditWordBreak;
	else if( _tcscmp(pszSwitch, "Switch_GameTip")					== 0)		return Switch_GameTip;
	else if( _tcscmp(pszSwitch, "Switch_Helper")					== 0)		return Switch_Helper;
	else if( _tcscmp(pszSwitch, "Switch_Teacher_Reform")			== 0)		return Switch_Teacher_Reform;
	else if( _tcscmp(pszSwitch, "Switch_SystemMarketSell")			== 0)		return Switch_SystemMarketSell;
	else if( _tcscmp(pszSwitch, "Switch_IKillU")					== 0)		return Switch_IKillU;
	else if( _tcscmp(pszSwitch, "Switch_PVP_League")				== 0)		return Switch_PVP_League;
	else if( _tcscmp(pszSwitch, "Switch_Set_Item_Add")				== 0)		return Switch_Set_Item_Add;
	else if( _tcscmp(pszSwitch, "Switch_Elixir")					== 0)		return Switch_Elixir;
	else if( _tcscmp(pszSwitch, "Switch_ValenTineWar")				== 0)		return Switch_ValenTineWar;
	else if( _tcscmp(pszSwitch, "Switch_NewMarket")					== 0)		return Switch_NewMarket;
	else if( _tcscmp(pszSwitch, "Switch_ManufactureInfluenceLuck")	== 0)		return Switch_ManufactureInfluenceLuck;
	else if( _tcscmp(pszSwitch, "Switch_MakeFoodHealEXP")			== 0)		return Switch_MakeFoodHealEXP;
	else if( _tcscmp(pszSwitch, "Switch_WeaponSkill")				== 0)		return Switch_WeaponSkill;
	else if( _tcscmp(pszSwitch, "Switch_NewGuildHuntMapWar")		== 0)		return Switch_NewGuildHuntMapWar;	
	else if( _tcscmp(pszSwitch, "Switch_PeriodItem")				== 0)		return Switch_PeriodItem;
	else if( _tcscmp(pszSwitch, "Switch_CarryOverGacha")			== 0)		return Switch_CarryOverGacha;
	else if( _tcscmp(pszSwitch, "Switch_Avatar_artisan")			== 0)		return Switch_Avatar_artisan; // �ƹ�Ÿ ����
	else if( _tcscmp(pszSwitch, "Switch_TreasureEvent")				== 0)		return Switch_TreasureEvent;
	else if( _tcscmp(pszSwitch, "Switch_WeddingSystem")				== 0)		return Switch_WeddingSystem;
	else if( _tcscmp(pszSwitch, "Switch_ItemExplain2")				== 0)		return Switch_ItemExplain2;
	else if( _tcscmp(pszSwitch, "Switch_BalanceCurrency")			== 0)		return Switch_BalanceCurrency;
	else if( _tcscmp(pszSwitch, "Switch_SoulGuard")					== 0)		return Switch_SoulGuard;
	else if( _tcscmp(pszSwitch, "Switch_We_Are_Family")				== 0)		return Switch_We_Are_Family;
	else if( _tcscmp(pszSwitch, "Switch_GACHA_RAREITEM_CHANGE")		== 0)		return Switch_GACHA_RAREITEM_CHANGE;
	else if( _tcscmp(pszSwitch, "Switch_Durability")				== 0)		return Switch_Durability;	
	else if( _tcscmp(pszSwitch, "Switch_NewDurability")				== 0)		return Switch_NewDurability;
	else if( _tcscmp(pszSwitch, "Switch_10MonthEvent_RacoonDodge")	== 0)		return Switch_10MonthEvent_RacoonDodge;
	else if( _tcscmp(pszSwitch, "Switch_BokBulBok")					== 0)		return Switch_BokBulBok;	
	else if( _tcscmp(pszSwitch, "Switch_GawiBawiBo")				== 0)		return Switch_GawiBawiBo;
	else if( _tcscmp(pszSwitch, "Switch_SummonTramsform")			== 0)		return Switch_SummonTramsform;
	else if( _tcscmp(pszSwitch, "Switch_Dormancy")					== 0)		return Switch_Dormancy;
	else if( _tcscmp(pszSwitch, "Switch_Festival_Food")				== 0)		return Switch_Festival_Food;
	else if( _tcscmp(pszSwitch, "Switch_SkillBook")					== 0)		return Switch_SkillBook;
	else if( _tcscmp(pszSwitch, "Switch_CharHouse")					== 0)		return Switch_CharHouse;
	else if( _tcscmp(pszSwitch, "Switch_RaccoonEvent_Change_Goonzu")== 0)		return Switch_RaccoonEvent_Change_Goonzu;	//[����] �����̺�Ʈ ���� �̺�Ʈ�� ���� 2009-10
	else if( _tcscmp(pszSwitch, "Switch_NewYearEvent_2010")			== 0)		return Switch_NewYearEvent_2010;	// [����] 2010�ų��̺�Ʈ. 2009.10.20
	else if( _tcscmp(pszSwitch, "Switch_BattleRoyal")				== 0)		return Switch_BattleRoyal;	//[����] ��Ʋ�ξ�
	else if( _tcscmp(pszSwitch, "Switch_PartyQuest_PartyMatching")  == 0)		return Switch_PartyQuest_PartyMatching;	// [����] �ʺ��� ��Ƽ ����Ʈ �ý���(��Ƽ��Ī).
	else if( _tcscmp(pszSwitch, "Switch_ValentineDayEvent")  == 0)				return Switch_ValentineDayEvent;
	else if( _tcscmp(pszSwitch, "Switch_Change_manufacture_request_interface")  == 0)				return Switch_Change_manufacture_request_interface;	// [����] ���� �Ƿ� �������̽� ����;
	else if( _tcscmp(pszSwitch, "Switch_PKHuntMap_Change_Info")  == 0)			return Switch_PKHuntMap_Change_Info;	// [����] pk ����� ��� ���� 
	else if( _tcscmp(pszSwitch, "Switch_Go_RaccoonWorld")  == 0)				return Switch_Go_RaccoonWorld;	// [����] ������� �̵� ���� 		
	else if( _tcscmp(pszSwitch, "Switch_LevelLimitBox")  == 0)					return Switch_LevelLimitBox;	// [����] *�߱���* �������� ���� ���� 

	return 0;
}

bool cltCommonLogic::IsCountrySwitch( SI32 siSwitchCountry )
{
	if(siSwitchCountry <= 0 || siSwitchCountry > Switch_Count)		return false;

	return m_bitArray_SwitchContry.GetBit(siSwitchCountry);
}

//------------------------------------------------------
// Village ���� 
//------------------------------------------------------
void cltCommonLogic::Village()
{
	if(pclVillageManager)
	{
		pclMapManager->pclCurrentMap->DeattachVillage();

		delete pclVillageManager;
		pclVillageManager = NULL;

		TCHAR* pText = GetTxtFromMgr(1434);
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, pText, TEXT("Info"), MB_OK|MB_TOPMOST);
	}
	else
	{

		pclVillageManager = new cltVillageManager(GameMode);
		pclVillageManager->LoadVillage(GameMode, siServiceArea);

		pclMapManager->pclCurrentMap->AttachVillage();

		TCHAR* pText = GetTxtFromMgr(1435);
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, pText, TEXT("Info"), MB_OK|MB_TOPMOST);
	}

}


//-----------------------------------
// ��ٸ��� ��ȭ ���� ó�� ���� 
//-----------------------------------
BOOL cltCommonLogic::ModalessDlgProc(MSG* pmsg)
{

	SI32 i;

	if(pclMapManager == NULL)return FALSE;

	cltMapCommon* pclMap = pclMapManager->pclCurrentMap;
	/*
	if(pclItemMallManager && IsWindow(pclItemMallManager->GetDlgHwnd()) && IsDialogMessage(pclItemMallManager->GetDlgHwnd(),pmsg))
	{
	return TRUE;
	}
	*/
	if(pclSkillManager && IsWindow(pclSkillManager->m_hDlg) && IsDialogMessage(pclSkillManager->m_hDlg, pmsg))
	{
		return TRUE;
	}
	if(pclItemManager && pclItemManager->IsDialogMessage(pmsg))
	{
		return TRUE;
	}

	//	if(pclAskManager && IsWindow(pclAskManager->m_hDlg) && IsDialogMessage(pclAskManager->m_hDlg, pmsg))
	//	{
	//		return TRUE;
	//	}
	/*	
	if(pclSchoolManager && IsWindow(pclSchoolManager->m_hDlg) && IsDialogMessage(pclSchoolManager->m_hDlg, pmsg))
	{
	return TRUE;
	}
	*/	
	for(i =0;i < MAX_DEV_TOOL_NUM;i++)
	{
		if(pclDevTool[i] && IsWindow(pclDevTool[i]->m_hDlg) && IsDialogMessage(pclDevTool[i]->m_hDlg, pmsg))
		{
			return TRUE;
		}
	}

	return FALSE;
}


// NPCGroup �� �����͸� ���´�. 
cltNPCGroup* cltCommonLogic::GetNPCGroupPointer(SI32 npcgroup)
{
	if(npcgroup <= 0 || npcgroup >= MAX_NPC_GROUP_NUMBER)return NULL;
	if(pclNPCManager == NULL)return NULL;

	return pclNPCManager->pclNPCGroup[npcgroup];
}

void cltCommonLogic::GetGoonZuUrl( TCHAR *url, TCHAR *szID )
{

	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchCopy( url, MAX_PATH, TEXT("http://goonzu.sbs.co.kr") );
	} else {
		// goonzu
		StringCchCopy( url, MAX_PATH, TEXT("http://goonzu.ndoors.com") );
	}
}

void cltCommonLogic::GetMyCZUrl( TCHAR *url, TCHAR *szID )
{

	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchPrintf( url, MAX_PATH, TEXT("http://goonzucz.sbs.co.kr/mh/main_for_goonzu.asp?uid=%s"), &szID[ 2 ] );
	} else {
		// goonzu
		StringCchPrintf( url, MAX_PATH, TEXT("http://ccomzi.ndoors.com/mh/main_for_goonzu.asp?uid=%s"), szID );
	}
}

void cltCommonLogic::GetCharCZUrl( TCHAR *url, TCHAR *szMyID, TCHAR *szID )
{
	// ���� �α��� ID		: szMyID
	// ���� AccountID		: szID

	if( szMyID[ 1 ] == '_' && ( szMyID[ 0 ] == 's' || szMyID[ 0 ] == 'S' ) ) {
		// sbs
		if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
			// ���� sbs

			StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzucz.sbs.co.kr/mh/main_for_goonzu.asp?uid=%s"), &szID[ 2 ] );

		} else {
			// ���� goonzu

			StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzucz.sbs.co.kr/mh/main_for_goonzu.asp?uid=i_%s"), szID );
		}

	} else {
		// goonzu
		if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
			// ���� sbs

			StringCchPrintf( url, MAX_PATH,  TEXT("http://ccomzi.ndoors.com/mh/main_for_goonzu.asp?uid=s_%s"), &szID[ 2 ] );

		} else {
			// ���� goonzu

			StringCchPrintf( url, MAX_PATH,  TEXT("http://ccomzi.ndoors.com/mh/main_for_goonzu.asp?uid=%s"), szID );
		}

	}
}

void cltCommonLogic::GetSubSiteUrl(TCHAR * url,TCHAR *szSubPath,TCHAR *szID )
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzu.sbs.co.kr/%s"), szSubPath);
	} else {
		// goonzu
		StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzu.ndoors.com/%s"), szSubPath);
	}
}// ItemMall �ּ� : /center/mall/buy_client.asp

void cltCommonLogic::GetHelpSiteUrl(TCHAR * url,TCHAR *szID)
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchCopy(url, MAX_PATH, TEXT("http://www.sbs.co.kr/sbscs/"));
	} else {
		// goonzu
		StringCchCopy(url, MAX_PATH, TEXT("http://help.ndoors.com/GOONZU/index.asp"));
	}
}

void cltCommonLogic::GetCZProfileUrl( TCHAR *url, TCHAR *szID )
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzucz.sbs.co.kr/mh/profile_image.asp?user_id=%s"), szID );
	} else {
		// goonzu
		StringCchPrintf( url, MAX_PATH,  TEXT("http://ccomzi.ndoors.com/mh/profile_image.asp?user_id=%s"), szID );
	}
}

void cltCommonLogic::GetCZDarakUrl( TCHAR *url, TCHAR *szID )
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzucz.sbs.co.kr/mh/image/darak/s_mydk/%c/%c/%s/%s.html"), szID[ 2 ], szID[ 3 ], &szID[ 2 ], &szID[ 2 ] );
	} else {
		// goonzu
		StringCchPrintf( url, MAX_PATH,  TEXT("http://ccomzi.ndoors.com/mh/image/darak/mydk/%c/%c/%s/%s.html"), szID[ 0 ], szID[ 1 ], szID, szID );
	}

}

void cltCommonLogic::GetCZIntroUrl( TCHAR *url, TCHAR *szID )
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchPrintf( url, MAX_PATH,  TEXT("http://goonzucz.sbs.co.kr/mh/intro_info.asp?user_id=%s"), szID );
	} else {
		// goonzu
		StringCchPrintf( url, MAX_PATH,  TEXT("http://ccomzi.ndoors.com/mh/intro_info.asp?user_id=%s"), szID );
	}
}

void cltCommonLogic::GetCPasswdUrl(TCHAR *url,TCHAR *szID)
{
	if( szID[ 1 ] == '_' && ( szID[ 0 ] == 's' || szID[ 0 ] == 'S' ) ) {
		// sbs
		StringCchCopy(url, MAX_PATH, TEXT("http://login.sbs.co.kr/Login/Login.jhtml?Login_ReturnURL="));
		StringCchCat(url, MAX_PATH, TEXT("http%3A//login.sbs.co.kr/member/update/update_Index.jhtml"));
	} else {
		// goonzu
		StringCchCopy( url, MAX_PATH, TEXT("http://signup.ndoors.com/update/recheck.asp?type=B"));
	}
}
void cltCommonLogic::SetMasterArea()
{
	FILE *pFile;
	TCHAR strLine[256]=TEXT("");
	if ( pFile = _tfopen(TEXT("Config/master.dat"), TEXT("r")) )
	{
		_fgetts(strLine, 256, pFile );
		fclose( pFile );
	}

    if ( _tcscmp( strLine, TEXT("korea") ) == 0 )
	{
		siMaster = ConstMaster_Korea;
	}
	else if ( _tcscmp( strLine, TEXT("japan") ) == 0 )
	{
		siMaster = ConstMaster_Japan;
	}
	else if ( _tcscmp( strLine, TEXT("taiwan") ) == 0 )
	{
		siMaster = ConstMaster_Taiwan;
	}
	else if ( _tcscmp( strLine, TEXT("usa") ) == 0 )
	{
		siMaster = ConstMaster_USA;
	}
	else if ( _tcscmp( strLine, TEXT("global") ) == 0 )
	{
		siMaster = ConstMaster_Global;
	}
}

SI32 cltCommonLogic::GetUniqueFromHash( TCHAR* pText )
{
	SI32*	data;

	data = (SI32*)(pclHashTableString->Find( pText ));

	if ( data )
        return *data;
	
	return 0;
}

UI32 cltCommonLogic::GetMinuteFromsTime( _SYSTEMTIME time )
{
	UI16 uiYear   = 0;
	UI16 uiMonth  = 0;
	UI16 uiDay    = 0;
	UI16 uiHour	  = 0;
	UI16 uiMinute = 0;

	uiYear   = time.wYear % 100;
	uiMonth  = time.wMonth;
	uiDay    = time.wDay;
	uiHour   = time.wHour;
	uiMinute = time.wMinute;
     
	UI32 vary = 0;
	// Date Vary
	vary = (uiDay-1) + (uiMonth-1)*30 + (uiYear*12)*30;
	// Hour Vary
	vary = vary * 24 + uiHour;
	// Minute Vary
	vary = vary * 60 + uiMinute;

	return vary;

}

_SYSTEMTIME cltCommonLogic::GetTimeFromsMinute( UI32 datevary )
{

	UI16 uiYear = 0;
	UI16 uiMonth = 0;
	UI16 uiDay = 0;
	UI16 uiHour = 0;
	UI16 uiMinute = 0;

	_SYSTEMTIME time;
	ZeroMemory(&time, sizeof(_SYSTEMTIME));
	
	if (datevary > 0)
	{
		uiYear  = datevary / (12* 30 * 24 * 60) + 2000;
		datevary %= (12* 30 * 24 * 60);

		uiMonth = datevary / (30 * 24 * 60)+ 1;
		datevary %= 30 * 24 * 60;

		uiDay	= datevary / (24 * 60) + 1;
		datevary %= 24 * 60;

		uiHour		= datevary / 60;
		datevary %= 60;

		uiMinute	= datevary + 1;

	}

	time.wYear = uiYear;
	time.wMonth = uiMonth;
	time.wDay = uiDay;
	time.wHour = uiHour;
	time.wMinute = uiMinute;


	return time;

}

cltDate cltCommonLogic::SysteTimeToCltTime( _SYSTEMTIME time )
{
	cltDate clDate;
	clDate.Set( time.wYear - 2000, time.wMonth, time.wDay, time.wHour, time.wMinute );

	return clDate;
}

SI32 cltCommonLogic::GetMaxStaminaValue(SI32 summonskill, SI32 summonkind)
{
	// ���� ���׹̳� ��� ����
	SI32 siRetMaxStamina = 200 + (summonskill * 10);

	// ���̺� ������ ���� ���׹̳� ���� �����´� - ���� ���׹̳ʸ� ����ϴ� ��ȯ���� ��츸 �����´�.
	cltKindInfo*	pclKI = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate))
	{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[summonkind];	}
	else	
	{	pclKI = pclClient->pclKindInfoSet->pclKI[summonkind];			}

	if( pclKI != NULL && pclKI->IsAtb(ATB_SUMMONSTAMINASTATIC) )
	{
		siRetMaxStamina = pclKI->siSummonStamina;
	}

	return siRetMaxStamina;
}

SI32 cltCommonLogic::GetSummonAttackBonus( SI32 summonskill )
{
	SI32 retVal = min( 30 , summonskill / 3 );

	if( summonskill > 90 )
	{
		retVal += ( summonskill - 90 );
	}	

	return retVal ;	// 
}

SI32 cltCommonLogic::GetSummonDefBonus( SI32 summonskill )
{
	if( summonskill < 50 )
	{
		return 0;
	}

	SI32 retVal = min( 10 , (summonskill - 40) / 10 * 2 );
	
	if( summonskill > 90 )
	{
		retVal += ( summonskill - 90 );
	}	

	return retVal ;	// 
}

void cltCommonLogic::GetServerNameFromNation(char*code,SI16 index,char*name)
{
	MStrCpy(name, "NONE", 20);

	if ( !strcmp(code,"tst") )
	{
		switch(index)
		{
		case  1: MStrCpy(name,"TEST-01",20); break;
		case  2: MStrCpy(name,"TEST-02",20); break;
		case  3: MStrCpy(name,"TEST-03",20); break;
		case  4: MStrCpy(name,"TEST-04",20); break;
		case  5: MStrCpy(name,"TEST-05",20); break;
		case  6: MStrCpy(name,"TEST-06",20); break;
		case  7: MStrCpy(name,"TEST-07",20); break;
		case  8: MStrCpy(name,"TEST-08",20); break;
		case  9: MStrCpy(name,"TEST-09",20); break;
		case 10: MStrCpy(name,"TEST-10",20); break;
		case 11: MStrCpy(name,"TEST-11",20); break;
		case 12: MStrCpy(name,"TEST-12",20); break;
		case 13: MStrCpy(name,"TEST-13",20); break;
		case 14: MStrCpy(name,"TEST-14",20); break;
		case 15: MStrCpy(name,"TEST-15",20); break;
		case 16: MStrCpy(name,"TEST-16",20); break;
		case 17: MStrCpy(name,"TEST-17",20); break;
		case 18: MStrCpy(name,"TEST-18",20); break;
		case 19: MStrCpy(name,"TEST-19",20); break;
		case 20: MStrCpy(name,"TEST-20",20); break;
		default: break;
		}
	}
	else if ( !strcmp(code,"tgl") )
	{
		switch(index)
		{
		case  1: MStrCpy(name,"TESTGLOBAL-01",20); break;
		case  2: MStrCpy(name,"TESTGLOBAL-02",20); break;
		case  3: MStrCpy(name,"TESTGLOBAL-03",20); break;
		case  4: MStrCpy(name,"TESTGLOBAL-04",20); break;
		case  5: MStrCpy(name,"TESTGLOBAL-05",20); break;
		case  6: MStrCpy(name,"TESTGLOBAL-06",20); break;
		case  7: MStrCpy(name,"TESTGLOBAL-07",20); break;
		case  8: MStrCpy(name,"TESTGLOBAL-08",20); break;
		case  9: MStrCpy(name,"TESTGLOBAL-09",20); break;
		case 10: MStrCpy(name,"TESTGLOBAL-10",20); break;
		case 11: MStrCpy(name,"TESTGLOBAL-11",20); break;
		case 12: MStrCpy(name,"TESTGLOBAL-12",20); break;
		case 13: MStrCpy(name,"TESTGLOBAL-13",20); break;
		case 14: MStrCpy(name,"TESTGLOBAL-14",20); break;
		case 15: MStrCpy(name,"TESTGLOBAL-15",20); break;
		case 16: MStrCpy(name,"TESTGLOBAL-16",20); break;
		case 17: MStrCpy(name,"TESTGLOBAL-17",20); break;
		case 18: MStrCpy(name,"TESTGLOBAL-18",20); break;
		case 19: MStrCpy(name,"TESTGLOBAL-19",20); break;
		case 20: MStrCpy(name,"TESTGLOBAL-20",20); break;
		default: break;
		}
	}
	else if ( !strcmp(code,"kor") )
	{
		switch(index)
		{
		case 1: MStrCpy(name,"TAEJO",20); break;
		case 2: MStrCpy(name,"JUNGJONG",20); break;
		case 3: MStrCpy(name,"TAEJONG",20); break;
		case 4: MStrCpy(name,"SEJONG",20); break;
		case 5: MStrCpy(name,"MOONJONG",20); break;
		case 6: MStrCpy(name,"DANJONG",20); break;
		case 7: MStrCpy(name,"SEJO",20); break;
		case 8: MStrCpy(name,"YEJONG",20); break;
		case 9: MStrCpy(name,"SUNGJONG",20); break;
		case 10: MStrCpy(name,"YEONSANGUN",20); break;
		case 11: MStrCpy(name,"JOONGJONG",20); break;
		case 12: MStrCpy(name,"INJONG",20); break;
		default: break;
		}
	}
	else if ( !strcmp(code,"jpn") )
	{
		switch(index)
		{
		case 1: MStrCpy(name,"ENARET",20); break;
		case 2: MStrCpy(name,"ARDIA",20); break;
		case 3: MStrCpy(name,"YOUGIKU",20); break;
		case 4: MStrCpy(name,"FELBURG",20); break;
		default: break;
		}
	}
	else if ( !strcmp(code,"eng") )
	{
		switch(index)
		{
		case 1: MStrCpy(name,"Zeus",20); break;
		case 2: MStrCpy(name,"Hera",20); break;
		case 3: MStrCpy(name,"Athena",20); break;
		default: break;
		}
	}
	else if ( !strcmp(code,"net") )
	{
		switch(index)
		{
		case 1: MStrCpy(name,"BAECKDOO",20); break;
		case 2: MStrCpy(name,"HANRA",20); break;
		case 3: MStrCpy(name,"GUMGANG",20); break;
		default: break;
		}
	}

}

bool cltCommonLogic::GetNationCode( OUT char* pszNationCode, IN SI32 siSize )
{
	if ( (NULL == pszNationCode) || (0 >= siSize) )
	{
		return false;
	}
	
	
#ifdef _DEBUG

	MStrCpy( pszNationCode, "tst", siSize );
	return true;

#else

	if ( true == IsWhereServiceArea(ConstServiceArea_English) )
	{
		MStrCpy( pszNationCode, "eng", siSize );
		return true;
	}
	else if ( true == IsWhereServiceArea(ConstServiceArea_Japan) )
	{
		MStrCpy( pszNationCode, "jpn", siSize );
		return true;
	}

	return false;

#endif
}



/*// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
TCHAR * cltCommonLogic::GetTxtFromMgr(SI32 index , bool bStructure )
{
TCHAR * buffer = NULL ;
if ( bStructure )
{
buffer = g_pStructureMgr.GetTextMgr(index);
if ( !buffer )
MsgBox(TEXT("NoStructureMsg"),TEXT("%d"),index);
}
else
{
buffer = g_pTextMgr.GetTextMgr(index);
if ( !buffer )
MsgBox(TEXT("NoTextMsg"),TEXT("%d"),index);
}

return buffer ;
}*/


SI32 cltCommonLogic::GetRecommendPointPerLevel(SI32 level)
{
	if( IsCountrySwitch(Switch_RecommendPointPerLevel) )
	{
		// PCK : ������ 120������ Ǯ���� ��õ������Ʈ�� ������. (09.03.06)
		if( 120 < level )
			return 0;
		else
			return Recommendpoint[level-1];
	}
	else if( siServiceArea == ConstServiceArea_Japan)
	{
		if( level <= 10 ) 
		{
			return 1;
		}
		else if(level >= 11 &&  level <= 19 )
		{
			return level - 9;
		}
		else if(level == 20 )
		{
			return 20;
		}
		else if(level >= 21 &&  level <= 29 )
		{
			return level - 10;
		}
		else if(level == 30 )
		{
			return 30;
		}
		else if(level >= 31 &&  level <= 39 )
		{
			return 20 +  (level - 30) * 2;
		}
		else if(level == 40 )
		{
			return 50;
		}
		else if(level >= 41 &&  level <= 49 )
		{
			return 40 +  (level - 40) * 3;
		}
		else if(level == 50)
		{
			return 70;
		}
		else if(level >= 51 &&  level <= 59 )
		{ 
			return 70 +  (level - 50) * 4;
		}
		else if(level == 60)
		{
			return 110;
		}
		else if(level >= 61 &&  level <= 69 )
		{
			return 110 +  (level - 60) * 5;
		}
		else if(level == 70)
		{
			return 160;
		}
		else if(level >= 71 &&  level <= 79 )
		{
			return 160 +  (level - 70) * 10;
		}
		else if(level == 80)
		{
			return 260;
		}
		else if(level >= 81 &&  level <= 89 )
		{
			return 260 +  (level - 80) * 20;
		}
		else if(level == 90)
		{
			return 460;
		}
		else if(level >= 91 &&  level <= 99 )
		{
			return 460 +  (level - 90) * 50;
		}
		else if(level == 100)
		{
			return 960;
		}
	}
	else
	{
		if( level <= 9 ) 
		{
			return 0;
		}
		else if(level >= 10 &&  level <= 20 )
		{
			return 1;
		}
		else if(level >= 21 &&  level <= 30 )
		{
			return level - 19;
		}		
		else if(level >= 31 &&  level <= 39 )
		{
			return 11 + (level - 30) * 3;
		}
		else if(level == 40 )
		{
			return 50;
		}
		else if(level >= 41 &&  level <= 49 )
		{
			return 40 +  (level - 40) * 4;
		}
		else if(level == 50)
		{
			return 80;
		}
		else if(level >= 51 &&  level <= 59 )
		{ 
			return 80 +  (level - 50) * 5;
		}
		else if(level == 60)
		{
			return 130;
		}
		else if(level >= 61 &&  level <= 69 )
		{
			return 130 +  (level - 60) * 6;
		}
		else if(level == 70)
		{
			return 190;
		}
		else if(level >= 71 &&  level <= 79 )
		{
			return 190 +  (level - 70) * 7;
		}
		else if(level == 80)
		{
			return 260;
		}
		else if(level >= 81 &&  level <= 89 )
		{
			return 260 +  (level - 80) * 20;
		}
		else if(level == 90)
		{
			return 460;
		}
		else if(level >= 91 &&  level <= 99 )
		{
			return 460 +  (level - 90) * 50;
		}
		else if(level == 100)
		{
			return 960;
		}
	}

	return 0;
}

bool cltCommonLogic::IsWhereServiceArea( SI32 ServiceArea )
{
	if( siServiceArea & ServiceArea )
		return true;
	else
		return false;
}

bool cltCommonLogic::SetItemByAttendanceDay( SI16 siAttendenceDay, SI16 siItemUnique, SI16 siItemNum, UI16 uiDateUseDay )
{
	if(siAttendenceDay >= 0 && siAttendenceDay < MAX_ATTENDANCE_COUNT)
	{
		m_pclAttendanceReward[siAttendenceDay] = new cltAttendanceReward();
		m_pclAttendanceReward[siAttendenceDay]->m_siItemUnique	= siItemUnique;
		m_pclAttendanceReward[siAttendenceDay]->m_siItemNum		= siItemNum;
		m_pclAttendanceReward[siAttendenceDay]->m_uiDateUseDay	= uiDateUseDay;
	}

	return false;
}

bool cltCommonLogic::GetItemByAttendanceDay( SI32 AttendanceDay, cltItem* pclItem )
{
	if(AttendanceDay < 0 || AttendanceDay >= MAX_ATTENDANCE_COUNT)
		return false;

	cltAttendanceReward*	pclAttendanceReward = m_pclAttendanceReward[AttendanceDay];
	if(pclAttendanceReward == NULL)
		return false;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclAttendanceReward->m_siItemUnique);
	if (ref <= 0)	return false;

	//KHY - 1217 - �⼮üũ �̺�Ʈ ��������� ����. - �ɷ�ġ�߰� �����۰���.
	// �ش� �������� �����ϰ� �����. 
	SI16 usedate;
	cltItem clItem;
	SI16 brareswitch = 0;

	usedate = pclAttendanceReward->m_uiDateUseDay;
	// ������ ��¥�� ������, �������� �⺻���� ����Ѵ�.
	if(usedate <= 0)	usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

	if(pclClient->pclItemManager->MakeRandItemUnique( pclAttendanceReward->m_siItemUnique, &clItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)return false;

	// ������ �����Ѵ�. 
	// ��ø ������ �������� ���ϴ� ������ŭ ���� �� �ִ�. 
	if(clItem.CanPile(pclClient->pclItemManager) == true)
	{
		clItem.SetItemNum(pclAttendanceReward->m_siItemNum);
	}
	// ��ø �Ұ� �������� 1���� ���� �� �ִ�. 
	else
	{
		clItem.SetItemNum(1);
	}

	// �Ⱓ�� �ִ� �������� �к��ؼ� �־��ش�
	if ( clItem.uiDateUseDay )
	{
		clItem.uiDateYear	= 0;
		clItem.uiDateMonth	= 0;
		clItem.uiDateDay	= 0;
	}

	pclItem->Init();
	pclItem->Set(&clItem);

/*   
	// �⼮�ϼ� �޼��� ������ ����.
	pclItem->Init();
	pclItem->siUnique = pclAttendanceReward->m_siItemUnique;
	pclItem->SetItemNum(pclAttendanceReward->m_siItemNum);
	pclItem->uiDateUseDay = pclAttendanceReward->m_uiDateUseDay;

	// �� ������ ���
	if(pclItem->siUnique == -1)
	{
		pclItem->siUnique = pclItemManager->GetRandBigWarItem();
	}
*/
	if ( pclItem->siUnique )
	{
		return true;
	}
	else
	{
		return false;
	}

/*
	switch( AttendanceDay )
	{
	case 1:
		pclItem->siUnique = ITEMUNIQUE( 15900 );
		pclItem->SetItemNum(1);
		pclItem->uiDateUseDay = 10;
		break;
	case 3:
		pclItem->siUnique = ITEMUNIQUE( 24075 );
		pclItem->SetItemNum(2);
		break;
	case 5:
		pclItem->siUnique = ITEMUNIQUE( 8035 );
		pclItem->SetItemNum(2);
		break;
	case 8:
		pclItem->siUnique = ITEMUNIQUE( 24000 );
		pclItem->SetItemNum(2);
		break;
	case 10:
		pclItem->siUnique = ITEMUNIQUE( 3855 );
		pclItem->SetItemNum(5);
		break;
	case 13:
		pclItem->siUnique = ITEMUNIQUE( 24045 );
		pclItem->SetItemNum(2);
		break;
	case 16:
		pclItem->siUnique = ITEMUNIQUE( 8035 );
		pclItem->SetItemNum(3);
		break;
	case 20:
		pclItem->siUnique = pclItemManager->GetRandBigWarItem();
		pclItem->SetItemNum(2);
		break;
	case 25:
		pclItem->siUnique = ITEMUNIQUE( 24000 );
		pclItem->SetItemNum(5);
		break;
	case 30:
		pclItem->siUnique = ITEMUNIQUE( 5370 );
		pclItem->SetItemNum(5);
		break;
	case 35:
		pclItem->siUnique = ITEMUNIQUE( 24040 );
		pclItem->SetItemNum(3);
		break;
	case 40:
		pclItem->siUnique = ITEMUNIQUE( 3860 );
		pclItem->SetItemNum(2);
		break;
	case 45:
		pclItem->siUnique = ITEMUNIQUE( 3903 );
		pclItem->SetItemNum(2);
		break;
	default:
		break;
	}

	if ( pclItem->siUnique )
	{
		return true;
	}
	else
	{
		return false;
	}
*/
}

bool cltCommonLogic::LoadGlobalValue()
{
	BOOL bLoadFile = FALSE;
	NDataLoader	dataloader;

	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( "Data/GlobalValue.dat" );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( "Data/GlobalValue.dat" );
	}

	if (!bLoadFile)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("GlobalValue Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
	}
	else
	{
		TCHAR szGlobalValueName[64];
		SI64  siGlobalValue;

		ZeroMemory(szGlobalValueName, sizeof(szGlobalValueName));

		NDataTypeInfo pDataTypeInfo[] =
		{
			NDATA_MBSTRING,	szGlobalValueName,		64,
			NDATA_INT64,	&siGlobalValue,			sizeof(siGlobalValue),
			0,0,0
		};

		dataloader.RegDataType(pDataTypeInfo);

		while( !dataloader.IsEndOfData() ) 
		{
			if (dataloader.ReadData())
			{
				pclHashTableGlobalValue->Insert(szGlobalValueName, siGlobalValue);
			}
		}
	}

	return true;
}

SI64 cltCommonLogic::GetGlobalValue(TCHAR* pszGlobalValue)
{
	if(pclHashTableGlobalValue == NULL)			return 0;

	SI64*	data;
	data = (SI64*)(pclHashTableGlobalValue->Find( pszGlobalValue ));
	if ( data )									return *data;

	return 0;
}

SI32 cltCommonLogic::GetTextColumn()
{
	SI32 textcolnum = 0;

	if( siServiceArea == ConstServiceArea_Korea )
	{
		textcolnum = 1;
	}
	else if( siServiceArea == ConstServiceArea_China )
	{
		textcolnum = 2;
	}
	else if( siServiceArea == ConstServiceArea_Japan )
	{
		textcolnum = 3;
	}	
	else if( siServiceArea == ConstServiceArea_English )
	{
		textcolnum = 4;
	}
	else if( siServiceArea == ConstServiceArea_Taiwan )
	{
		textcolnum = 5; //�ӽ�  - �븸  = 5
	}
	else if( siServiceArea == ConstServiceArea_USA )
	{
		textcolnum = 4; //�ӽ�  - USA  = 6
	}
	else if( siServiceArea == ConstServiceArea_NHNChina )
	{
		textcolnum = 2;
	}
	else if( siServiceArea == ConstServiceArea_EUROPE )
	{
		textcolnum = 6;
	}

	if ( siMaster == ConstMaster_Korea && GameMode == GAMEMODE_CLIENT )
	{
		textcolnum = 1;
	}

	return textcolnum;
}
