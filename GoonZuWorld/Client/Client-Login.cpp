//---------------------------------
// 2003/11/22 ���°�
//---------------------------------

#include "Client.h"


#include "Music\Music.h"

#include "MsgType.h"

#include "..\Common\Bullet\Bullet.h"
#include "..\Common\Smoke\Smoke.h"
#include "..\CommonLogic\Hunt\Hunt.h"
#include "..\CommonLogic\MagicMgr\MagicMgr.h"
#include "..\CommonLogic\MsgType-Person.h"
#include "../common/Order/order.h"
#include "Msg\MsgType-Quest.h"
#include "MsgType-Item.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "NInterface/NMiniMapDlg/NMiniMapDlg.h"
#include "NInterface/NChatDlg/NChatDlg.h"
#include "NInterface/NNewInventory/NNewInventory.h"
#include "ninterface/nnewquestdlg/NNewQuestDlg.h"
#include "Interface/TotalChatDlg/TotalChatDlg.h"
#include "PCRoom/PCRoomIntro.h"
#include "Interface/RichEditChatMgrDlg/RichEditChatMgrDlg.h"

// APEX-
#include "../Apex/ApexGoonZu.h"
// -APEX

#include "../Client/MiniHomeUpdates/PopupCheck.h"

#include "../Client/ninterface/NMapNameDlg/NMapNameDlg.h"

#include "..\CommonLogic\Msg\MsgType-NPC.h"

extern CSoundOnOffDlg g_SoundOnOffDlg;
extern bool bSetScreenCenterSwitch;

static bool bGameStart;

// �α���. (���� ĳ����. ) 
void cltClient::DoMsg_GAMEMSG_RESPONSE_LOGINMANY(cltMsg* pclMsg, SI32 id)
{
	cltMakeCharInfoCommon* pclinfo = NULL;
	cltMakeCharInfo clinfo;
	SI32 index = 0;

	bool loop = true;
	while(loop)
	{
		pclinfo = (cltMakeCharInfoCommon*)&pclMsg->cData[index];
		// ����� ĳ���� ����. 
		if(pclinfo->uiType == MAKECHARTYPE_PC)
		{
			memcpy(&clinfo, pclinfo, sizeof(cltMakeCharInfo));
			index+= sizeof(cltMakeCharInfo);
		}
		// NPCĳ���� ����. 
		else
		{

			clinfo.Set(pclinfo);
			index+= sizeof(cltMakeCharInfoCommon);
		}
		
		
		// ĳ���͸� ���� �� �ֵ��� ���ۿ� �־��ش�. 
		PushChar(&clinfo);

		
		if(index >= pclMsg->GetDataSize() )break;

	}
}

// �α���. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_LOGIN(cltMsg* pclMsg, SI32 id)
{
	cltMakeCharInfo* pclinfo = (cltMakeCharInfo*)pclMsg->cData;
	
	// ĳ���͸� ���� �� �ֵ��� ���ۿ� �־��ش�. 
	PushChar(pclinfo);

	//------------------------------------------------
	// ������ �α����̸� ȿ������ �����Ѵ�. 
	//------------------------------------------------
	static bool bkingeffectswitch = false;
	SI32 armourunique = pclinfo->clShapeEquip.clArmour.uiUnique;
	if(bkingeffectswitch == false)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(armourunique);
		if(ref > 0 && pclItemManager->pclItemInfo[ref]->siNeedRank == 2)
		{
			bkingeffectswitch = true;

			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_KING_LOGIN")), 0, 0);

			TCHAR* pText  = GetTxtFromMgr(817);

			pclMessage->SetMsg(pText);
		}
	}

	// ���ΰ� ĳ���� ������ �Ѿ�� ���̶��, 
	if((SI32)pclinfo->uiMakeCharUnique != MyCharUnique)return ;

	pclCM->CR[id]->clPB.clShapeEquip.Set(&pclinfo->clShapeEquip);
	
	//--------------------------
	// �Ѿ�, ������� ��� �����.
	//---------------------------
	pclSmokeManager->DeleteSmoke();
	pclBulletManager->DeleteBullet();
	
	//---------------------------
	// ������ �����.
	//---------------------------
	pclMagicManager->DeleteMagic();
	
	//---------------------------------
	// ���ΰ� ĳ������ ������ ����Ѵ�. 
	//---------------------------------
	if(bReceiveMyCharAllInfoSwitch == true)
	{
		// ĳ���� ������ ����ߴ�. 
		bBackUpSwitch	= true;
		
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		
		pclHeroDataBackup->clMyCharPersonInfo.Set(pclCM->CR[1]->pclCI);
		
		// ���￡�� óġ�� ���� ���� ���. 
		pclHeroDataBackup->siWarEnemyKillNumber				= pclCM->CR[1]->siWarEnemyKillNumber;
		pclHeroDataBackup->siWarKilledNumber				= pclCM->CR[1]->siWarKilledNumber;
		pclHeroDataBackup->siBlackArmyWarMapIndex			= pclCM->CR[1]->siBlackArmyWarMapIndex;

		pclHeroDataBackup->siBlackWarEnemyKillNumber		= pclCM->CR[1]->siBlackWarEnemyKillNumber;
		pclHeroDataBackup->siBlackWarKilledNumber			= pclCM->CR[1]->siBlackWarKilledNumber;
		
		//[�߰� : Ȳ���� 2008. 1. 28 => ���� ���� ���� ���� ���]
		pclHeroDataBackup->siBlackWarEnemyKillScore			= pclCM->CR[1]->siBlackWarEnemyKillScore;
		pclHeroDataBackup->siBlackWarEnemyKillVillageScore	= pclCM->CR[1]->siBlackWarEnemyKillVillageScore;
		
		pclHeroDataBackup->bStartMakeItemSwitch				= pclchar->bStartMakeItemSwitch;
		pclHeroDataBackup->dwStartMakeItemClock				= pclchar->dwStartMakeItemClock;
		pclHeroDataBackup->dwDelayMakeItemClock				= pclchar->dwDelayMakeItemClock;
		
		//------------------------------------------------------------------------------------------
		pclHeroDataBackup->siOldActiveClothes				= pclchar->ActiveClothes;
		pclHeroDataBackup->siOldActiveHat					= pclchar->ActiveHat;
		pclHeroDataBackup->siOldActiveWeapon				= pclchar->ActiveWeapon;
		pclHeroDataBackup->siOldCurrnetMagic				= pclchar->siCurrentMagic;
		pclHeroDataBackup->siOldCurrnetMagicCastType		= pclchar->siCurrentMagicCastType;

		//------------------------------------------------------------------------------------------
		pclHeroDataBackup->siOldBasicMoveSpeed				= pclchar->clPB.BasicMoveSpeed;
		pclHeroDataBackup->siOldShoesMoveSpeed				= pclchar->clPB.ShoesMoveSpeed;
		pclHeroDataBackup->siOldTotalMoveSpeed				= pclchar->clPB.TotalMoveSpeed;
		pclHeroDataBackup->siOldGivenMoveSpeed				= pclchar->clPB.GivenMoveSpeed;

/*
		pclHeroDataBackup->siGuildOldStr			= pclchar->clPB.siGuildStr;
		pclHeroDataBackup->siGuildOldDex			= pclchar->clPB.siGuildDex;
		pclHeroDataBackup->siGuildOldMag			= pclchar->clPB.siGuildMag;
		pclHeroDataBackup->siGuildOldVit			= pclchar->clPB.siGuildVit;
		pclHeroDataBackup->siGuildOldHnd			= pclchar->clPB.siGuildHnd;
		pclHeroDataBackup->siGuildOldLuck			= pclchar->clPB.siGuildLuck;
*/
		pclHeroDataBackup->clGuildOldBA.Set(&pclchar->clPB.clGuildBA);

		//------------------------------------------------------------------------------------------
		
		
		//�������� �������� ���� �ϴ� ������ �ƴϴ�.
		pclHeroDataBackup->clOldAddInfo.Set(&pclchar->clAddInfo);
		pclHeroDataBackup->clOldItemMall.Set(&pclchar->pclCI->clItemMall);
		//pclHeroDataBackup->clOldLimitDateItemInfo.Set(&pclchar->pclCI->clLimitDateItem);
		
		//------------------------------------------------------------------------------------------
		// ��ġ ������ ���� ���� ������ ������ ������Ʈ �Ѵ�. 
		pclHeroDataBackup->clMyCharPersonInfo.clBI.clPos.siMapIndex		= pclinfo->uiMapIndex;
		pclHeroDataBackup->clMyCharPersonInfo.clBI.clPos.siX			= pclinfo->uiX;
		pclHeroDataBackup->clMyCharPersonInfo.clBI.clPos.siY			= pclinfo->uiY;
		
		//------------------------------------------------------------------------------------------
		// ü�� ������ ���� ���� ������ ������ ������Ʈ �Ѵ�. 
		if(pclHeroDataBackup->clMyCharPersonInfo.clIP.GetLife() <= 0)
		{
			pclHeroDataBackup->clMyCharPersonInfo.clIP.SetLife(1);
		}

		//[����] ��������.  �������� ĳ���� �ʱ�ȭ�� �̷���� �� ����� ������ ����. => 2008-4-3
		if(pclchar->pclSpaceBoxItem)	memcpy(&pclHeroDataBackup->clSpaceBoxItem,    pclchar->pclSpaceBoxItem,	sizeof(pclHeroDataBackup->clSpaceBoxItem));
		if(pclchar->pclTreasureBoxItem)	memcpy(&pclHeroDataBackup->clTreasureBoxItem, pclchar->pclTreasureBoxItem,	sizeof(pclHeroDataBackup->clTreasureBoxItem));

		pclHeroDataBackup->clOldMagicBufMgr.Set( &pclchar->m_clMagicBufMgr );
		// ä�� ���� ���ѽð� ����
		memcpy(&pclHeroDataBackup->stMuteTime, &pclchar->m_stMuteTime, sizeof(pclHeroDataBackup->stMuteTime));

		//. �߷�Ÿ�ε��� ���� 
		pclHeroDataBackup->clValentinewarinfo.Set( pclchar->pclValentineWar);
		
		pclHeroDataBackup->clPVP_LeagueInfo.Set( pclchar->pclPVP_LeagueInfo);
	}	
	//--------------------------
	// ������ ĳ���͸� ��� �����. 
	//--------------------------
	pclCM->DeleteChar();

	
	//--------------------------
	// ������ ������ ����Ʈ ������ �����.
	//--------------------------
	if(pclQuestManager)
	{
		pclQuestManager->siCurrentQuestUnique = 0;
	}
	//--------------------------
	// ���� ������ �����Ѵ�. 
	//--------------------------
	// �������� �����ϱ����� ���¸� ����Ѵ�.
	bool bTempSmallMapSwitch = bSmallMapSwitch;
	
	pclMapManager->DeleteAllMap();

	pclMapManager->pclCurrentMap = NULL;		// �ݵ�� �ʱ�ȭ �Ǿ�� �Ѵ�. 
	

	//-----------------------------------
	// MapIndex�� ������ ������ �о�´�.
	//------------------------------------
	pclMapManager->LoadMap(this, pclinfo->uiMapIndex, pclinfo->siMapUnique);
	
	pclMapManager->SetCurrentMapIndex(pclinfo->uiMapIndex);

	// ȭ�� ����� �߽� ��ǥ�� �ٽ� �����ϵ��� �����. 
	bSetScreenCenterSwitch = true;
	
	// ���鵵�� ����Ǿ� �ִ� ĳ���͸� �����. (���ΰ� ĳ����) 
	SetCharReservedChar();

	// ���ΰ� ĳ������ ������ �������� �ʱ� ������ �ٽ� ó���ϵ��� �����Ѵ�. - by LEEKH 2009-03-20
	pclCM->GetCharClient(1)->clPB.bSetTotalBA	= false;

	// �̴ϸ��� ���� �־����� ��Ӻ����ش�.
	bSmallMapSwitch = bTempSmallMapSwitch; // �������� �����ϱ����� ���·� �����Ѵ�.
	if(bSmallMapSwitch)
	{	
		if ( m_pDialog[ NMINIMAP_DLG ] == NULL )
		{
			CreateInterface( NMINIMAP_DLG );
		}			
	}

	
	
	
	//--------------------------------------------------------
	// ���ʿ��� �������̽��� �ݴ´�. 
	//--------------------------------------------------------
	DestroyNeedlessInterface();

	//--------------------------------------------------------
	// ������ �����̸� ������ ������ �ǹ� �����͸� ��û�Ѵ�.
	//--------------------------------------------------------
	
	// ������ �������� Ȯ���Ѵ�. 
	if(pclMapManager->pclCurrentMap->siVillageUnique)
	{
		cltMsg clMsg(GAMEMSG_REQUEST_VILLAGESTRUCT, pclMapManager->pclCurrentMap->siVillageUnique);
		SendMsgToServer((sPacketHeader*)&clMsg);
		
		// ������ �ǹ� ������ �ޱ� �������� ĳ���͸� ������ �ȵȴ�. �ֳ��ϸ� 
		// ĳ���Ͱ� ������� �Ŀ� �ǹ� ������ ���� ĳ���Ͱ� �ǹ� �ӿ� �Ĺ����� 
		// ��찡 �߻��ϱ� �����̴�. ���� �ǹ� ������ ���⸦ ��ٸ��ٴ� 
		// ����ġ�� �۵��ؾ� �Ѵ�. 
		bWaitVillageStructureInfoSwitch		= true;
	}
	
	if(bReceiveMyCharAllInfoSwitch == false)
		bGameStart = true;
	else
		bGameStart = false;

	// ���Ϸκ��� ���� ȯ�� ���� ���� �� ������ �ȵ� Server�� ���� ������ �����Ѵ�.
	if( bGameStart )
	{
		bGameStart = false ;

		if ( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ NSOUNDONOFF_DLG ] )
		{
            ((CNSoundOnOffDlg*)(m_pDialog[ NSOUNDONOFF_DLG ]))->SendCurrentSettingInfo();
		}
		else
		{
            g_SoundOnOffDlg.SendCurrentSettingInfo();
		}

		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WELCOME_TO_GOONZU")),0,0);
	}

	//----------------------------------------
	// ������ �����Ѵ�. 
	//----------------------------------------
	SI32 mapindex = pclMapManager->pclCurrentMap->siMapIndex;
	PlayBackgroundMusic(mapindex);
	
	// ������ �� �������� �ִ��� ��û�Ѵ�.
	{
		pclCM->CR[1]->pclCI->clItemMall.Init();
		cltMsg clMsg(GAMEMSG_REQUEST_ITEMMALLEXISTENCE,0);
		SendMsgToServer((sPacketHeader*)&clMsg);
	}

	OrderStop(1 , BY_PLAYER);

	// �κ�â �ƽ���� ����
	//CNNewInventory::m_bMax = false;


	if ( pclCM->CR[1]->pclCI->clIP.GetLevel() <= 3 && 
		pclMapManager->pclCurrentMap->siMapIndex == MAPINDEX_PALACE )
	{
		if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
		{
			CreateInterface( NNEWQUEST_DLG );

			if(m_pDialog[ NNEWQUEST_DLG ])
			{
				pclQuestManager->bNewQuseOpened = TRUE;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(GetUniqueFromHash("KIND_WAITINGMAN"));
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
			}
		}
	}
	if(pclClient->IsCountrySwitch(Switch_FreshManHelpDialog))
	{
		CreateInterface(NHELPBUTTON_DLG);
	}

	// [����] �޸� ���� (2009.08.18) - Ŭ���̾�Ʈ ���ӽ� �޸� ���� üũ �� ����Ʈ ���̾�α� ���� ���� ó��
	if ( TRUE == pclCM->CR[1]->pclCI->clDormancyInfo.GetDormancyState() )
	{
		CDormancySystem *pclDormancySystem = this->pclDormancySystem;
		if( NULL != pclDormancySystem)
		{
			CDormancyPointRewardClient *pclDormancyClient = (CDormancyPointRewardClient *)pclDormancySystem->GetDormancyPointReward();
			if(NULL != pclDormancyClient)
			{
				pclDormancyClient->CreatePointDlg();
			}
		}
	}

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if(pclinfo->siCurrentHorseRIDEHORSE == true)
	{
		// �����ڸ� �����Ѵ�. 
		pclCM->CR[1]->DeleteSlave();
	}
	// APEX- �ѹ��� ����ǰ� �Ѵ�.
#ifdef _CHINA
	if( false == m_bStartApex )
	{
		m_bStartApex = true;
		StartApexClient();
	}
#endif
	// -APEX

	// [����] �� �̸� �����ֱ� (2008.06.17)
	if ( IsCountrySwitch(Switch_Show_MapName) )
	{
		if ( NULL == m_pDialog[ NMAPNAME_DLG ] )
		{
			CreateInterface( NMAPNAME_DLG );
		}

		((CNMapNameDlg*)m_pDialog[ NMAPNAME_DLG ])->ShowMapName( mapindex );
	}
}

// �α׾ƿ� . 
void cltClient::DoMsg_GAMEMSG_RESPONSE_LOGOUT(cltMsg* pclMsg, SI32 id)
{
	SI32 quitcharunique = pclMsg->siData32[0];
	SI32 quitid = cltCharCommon::CharUniqueInfo[quitcharunique];
			
	// �ڱ� �ڽ��� �α׾ƿ� ��Ű��� ��û�̸� �����Ѵ�. �ڱ� �ڽ��� �α׾ƿ� ��ų �� ����.
	if(quitid == 1)
	{
		return;
	}
	
	// ������� ĳ�����߿� �����ϸ� �����Ѵ�.
	if(pclCM->IsValidID(quitid))
	{
		pclCM->DeleteChar(quitid);
	}

	// ������ ĳ���� ����Ʈ�� �����ϸ� �����Ѵ�. 
	if(quitcharunique)
	{
		DeleteReservedChar(quitcharunique);
	}
}
