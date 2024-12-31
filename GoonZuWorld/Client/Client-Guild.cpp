//---------------------------------
// 2005/06/16 ���뷡
//---------------------------------

#include "Client.h"
#include "Music\Music.h"
#include "..\CommonLogic\MsgType.h"


//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"
#include "../Common/Skill/Skill-Manager.h"

#include "MsgType-Guild.h"

#include "./Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "./Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "./NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "NStructureDlg/GuildStr/Guild/NGuildDlg.h"
#include "../CommonLogic/Guild/Guild.h"
#include "../CommonLogic/Guild/GuildRankManager.h"

// ����� �⺻������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GUILDUNITLIST(cltMsg* pclMsg)
{
	SI32 i;

	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_GuildUnitList* pclinfo = (cltGameMsgResponse_GuildUnitList*)pclMsg->cData;
	
	if(pclinfo == NULL ) return;

	// ���� ������ ��� �����ڿ��� �����Ѵ�. 
	for(i = 0;i < MAX_GUILDUNIT_NUMBER;i++)
	{
		pclGuildStructManager->clClientUnit[i].Set( &(pclinfo->clListInfo[i]) );
	}
	
	//// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclGuildStructManager->bUpdateGuildStrListShowChiefSwitch = true;
	pclGuildStructManager->bUpdateGuildStrUnitListShowSwitch		= true;
}


// ���� ����� �������� �޾Ҵ�. (����� ��)
void cltClient::DoMsg_GAMEMSG_RESPONSE_GUILDUNIT_DETAIL(cltMsg* pclMsg)
{
	SI32 i;

	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_GuildUnitDetail* pclinfo = (cltGameMsgResponse_GuildUnitDetail*)pclMsg->cData;
	
	SI32 villageunique = 0;
	SI32 guildunitslot = 0;

	if(pclinfo == NULL || pclGuildStructManager == NULL ) return;

	villageunique = pclinfo->siVillageUnique;
	guildunitslot = pclinfo->siGuildUnitSlot;

	if(villageunique <= 0 || villageunique >=MAX_VILLAGE_NUMBER) return;
	if(guildunitslot < 0 || guildunitslot >=MAX_GUILDUNIT_NUMBER ) return;

	cltGuildStruct* pclGuildStruct = NULL;
	pclGuildStruct = ((cltGuildStruct*)(pclGuildStructManager->pclStruct[ villageunique ]));

	if( pclGuildStruct == NULL ) return;

	// ���� ������ ��� �����ڿ��� �����Ѵ�. 
    pclGuildStruct->clGuildUnit[ guildunitslot ].Set( &(pclinfo->clGuildUnit) );

	pclGuildRankManager->bUpdateGuildUnitListShowChiefSwitch = true;
}

// ���� ����� ���� ������ �޾Ҵ�. (��� ����� ��)
void cltClient::DoMsg_GAMEMSG_RESPONSE_GUILDUNITRANK(cltMsg* pclMsg)
{
	cltGameMsgResponse_GuildUnitRank* pclinfo = (cltGameMsgResponse_GuildUnitRank*)pclMsg->cData;

	if(pclinfo == NULL ) return;

	SI32 villageunique = 0;
	SI32 guildunitslot = 0;

	if(pclinfo == NULL || pclGuildStructManager == NULL ) return;

	villageunique = pclinfo->siVillageUnique;
	guildunitslot = pclinfo->siGuildUnitSlot;

	if(villageunique <= 0 || villageunique >=MAX_VILLAGE_NUMBER) return;
	if(guildunitslot < 0 || guildunitslot >=MAX_GUILDUNIT_NUMBER ) return;

	cltGuildRank* pclGuildRank = NULL;
	pclGuildRank = pclinfo->clGuildRank;

	if(pclGuildRank == NULL ) return;

	for(SI32 i=0; i<MAX_GUILDRANKTYPE_NUMBER + 1; i++)
	{
		pclGuildRankManager->clRank[villageunique][guildunitslot][i].Set( pclGuildRank + i );
	}

	pclGuildRankManager->bUpdateGuildUnitListShowSwitch = true;
}

