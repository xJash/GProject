//---------------------------------
// 2004/5/20 ���°�
//---------------------------------

// Client
#include "../Client.h"
#include "../Music/Music.h"
#include "../AttackEffect/AttackEffectMgr.h"
#include "../Effect/ExpCounter/ExpCounter.h"// ����ġ ���� 
#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "../Interface/LoginNoticeDlg/LoginNoticeDlg.h"

#include "../Interface/PersonalInfo/PersonalInfo.h"
#include "../Interface/RecommendPersonDlg/RecommendPersonDlg.h"
#include "../Interface/SiegeWinDlg/SiegeWinDlg.h"
#include "../Interface/RareItemDlg/RareItemDlg.h"
#include "../NInterface/NRareItemDlg/NRareItemDlg.h"
#include "../Interface/MakeItemDlg/MakeItemDlg.h"
#include "../NInterface/NMakeItemDlg/NMakeItemDlg.h"
#include "../Interface/WebEventDlg/WebEventDlg.h"
#include "../Interface/GomZiDlg/GomZiDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../NPCRepair/NPCRepair.h"
#include "../StatusBar/ChatStatusBar/ChatStatusBar.h"
#include "../NInterface/NStatusBarDlg/NStatusBarDlg.h"
#include "../NInterface/NChatDlg/NChatDlg.h"
#include "../Effect/HealCounter/HealCounter.h"// ġ��   ǥ�� 
#include "../NInterface/NHongGilDongDlg/NHongGilDongDlg.h"
#include "../NInterface/NCharStatus/NCharGreetingChange.h"
#include "../NInterface/NCharStatus/NCharHorse.h"
#include "../NInterface/NMaster/NMaster.h"
#include "../NInterface/NNewQuestDlg/NNewQuestDlg.h"
#include "../NInterface/NNewInventory/NNewInventory.h"
#include "../NInterface/npersonalshopdlg/NPersonalShopDlg.h"
#include "../NStructureDlg/Market/NMarketDlg.h"
#include "../ninterface/nRightMouseUserListDlg/NRightMouseUserListDlg.h"
#include "../ninterface/NCharRoulette/NCharRoulette.h"
#include "../ninterface/NYesOrNoDlg/NYesOrNoDlg.h"
#include "../NStructureDlg/NewMarket/NNewMarketDlg.h"
#include "../ninterface/NTreasureBoxDlg/NTreasureBoxDlg.h"
#include "../ninterface/nmagicinfodlg/NewMagicInfoDlg.h"


//���� ����
#include "../NInterface/NLetterDlg/NLetterDlg.h"

//CommonLogic
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/MsgType-Item.h"
#include "../CommonLogic/Msg/MsgType-ItemMall.h"
#include "../CommonLogic/Msg/MsgType-Web.h"
#include "../CommonLogic/Msg/MsgType-NamingQuest.h"
#include "../CommonLogic/Msg/MsgType-HappyBeanQuest.h"


// �ʻ�� ȿ��. 
#include "Char/CharClient/CharCriticalEffect/CharCriticalEffect.h"
#include "Char/CharClient/CharJim/CharJim.h"

#include "Father/Father.h"
#include "School/School.h"
#include "Smoke/Smoke.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"


#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"

#include "../common/HintDlg/HintDlg.h"
#include "../Common/Quest/NamingQuest.h"
#include "Char\CharManager\CharManager.h"
#include "../Client/NInterface/NTeacherDlg/TeacherDlg.h"
#include "../Client/NInterface/NTeacherDlg/FatherDlg.h"
#include "../Client/NInterface/NTeacherDlg/ChildDlg.h"
#include "../Client/NInterface/NRecommendPersonDlg/NRecommendPersonDlg.h"
//���� ���� �˸�
#include "NInterface/NSiegeWinDlg/NSiegeWinDlg.h"
#include "../client/NInterface/NBobusangDlg/NBobusangDlg.h"

#include "NInterface/NCharStatus/NCharStatus.h"
#include "NInterface/NPersonalInfoDlg/NPersonalInfo.h"
#include "NInterface/NNPCRepairDlg/NNPCRepair.h"
#include "NInterface/NBobusangDlg/NBobusangDlg.h"
#include "Interface/MinigameDlg/RouletteGameDlg/RouletteGameDlg.h"
#include "MiniGame/MiniGameManager.h"

#include "Interface/RichEditChatMgrDlg/RichEditChatMgrDlg.h"

#include "ninterface/NUserListByCountryDlg/NUserListByCountryDlg.h"
#include "ninterface/NLowLevelDlg/NLowLevelDlg.h"
#include "ninterface/nsoundonoffdlg/NSoundOnOffDlg.h"
#include "ninterface/NCommonMsgDlg/NCommonMsgDlg.h"
#include "ninterface/NAttendCheck/NAttendCheckDlg.h"
#include "ninterface/NMusicDlg/NMusicDlg.h"
#include "ninterface/NAuctionEvent/NAuctionEventDlg.h"
#include "ninterface/NAttendCheck/NAttendCheckDlg.h"
#include "ninterface/NAttendCheck/NAttendNoticeDlg.h"

#include "ninterface/NBuffRoulette/NBuffRoulette.h"

#include "ninterface/NPVPLeagueDlg/NPVPLeageuDlg.h"
#include "ninterface/NNewYearEventRouletteDlg/NNewYearEventRoulette.h"
#include "ninterface/NWeddingCeremony/NProposeAnswerDlg.h"
#include "ninterface/NBalanceCurrencyDlg/NBalanceCurrencyDlg.h"
#include "../GawiBawiBoMgr/GawiBawiBoMgr_Client.h"

#include "../CommonLogic/MsgType-Item.h"

#include"ninterface/N2010NewYearEventDlg/N2010NewYearDlg.h" // [����] 2010�ų��̺�Ʈ
#include "interfaceMgr/InterfaceFile.h"
#include "InterfaceMgr/InterfaceMgr.h"



#include "MsgType-Person.h"
#include "MsgType-Guild.h"

extern SI32 gsiResolution;

#ifdef USE_GAME_GUARD_CLIENT
extern CNPGameLib * pNpgl;
#endif

// ���� ����Ʈ ���� �뺸. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_UPDATECHILDLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UpdateChildList* pclinfo = (cltGameMsgResponse_UpdateChildList*)pclMsg->cData;

	//KHY -0610 - ������ �����.- 0629 -�ӽ÷� �ǵ���.
	//((CNFatherDlg*)m_pDialog[ NFATHER_DLG ])->DelChildList();

	for(SI32 i = 0;i < MAX_CHILDINFO_NUMBER;i++)
	{
		if(pclinfo->clChildInfo[i].clPerson.GetPersonID() <= 0)continue;

		// Ǯ��ũ��
		if(g_SoundOnOffDlg.m_bFullScreenMode)
		{
			if ( m_pDialog[NFATHER_DLG] != NULL )
			{
				((CNFatherDlg*)m_pDialog[ NFATHER_DLG ])->AddChildList(&pclinfo->clChildInfo[i]);
			}
		}
		else
			pclFatherManager->AddChildList(&pclinfo->clChildInfo[i]);
	}

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[NFATHER_DLG] != NULL )
		{
			((CNFatherDlg*)m_pDialog[ NFATHER_DLG ])->m_bUpdateChildListSwitch = true;
		}
	}
	else
		pclFatherManager->bUpdateChildListSwitch = true;
}

// ������ ���ڸ� ¥�� ���� �뺸. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_RENOUNCEPUPIL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RenouncePupil* pclinfo = (cltGameMsgResponse_RenouncePupil*)pclMsg->cData;

	if( 1 == pclinfo->GetResult() )
	{
		TCHAR* pTitle = GetTxtFromMgr(6862);
		TCHAR* pText  = GetTxtFromMgr(6865);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	}
	else
	{
		TCHAR* pTitle = GetTxtFromMgr(6862);
		TCHAR* pText  = GetTxtFromMgr(6866);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_OVERTAKETEACHERLEVEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_OverTakeTeacherLevel* pclinfo = (cltGameMsgResponse_OverTakeTeacherLevel*)pclMsg->cData;

	TCHAR buffer[256] = TEXT("");
	if(m_pDialog[NRAREITEM_DLG ] == NULL)
		CreateInterface( NRAREITEM_DLG );	

	TCHAR* pText1 = GetTxtFromMgr(10028);
	TCHAR* pText = GetTxtFromMgr(6874);
	StringCchPrintf( buffer, 256,  pText, pclinfo->GetPupilName(), pclinfo->GetTeacherName() );
	((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set( &pclinfo->m_clItem, pclinfo->GetPupilName(), pText1, buffer );		
}

// ���� ��û�� ���� �뺸. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_FATHERAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_FatherApplyerList* pclinfo = (cltGameMsgResponse_FatherApplyerList*)pclMsg->cData;

	for(SI32 i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(g_SoundOnOffDlg.m_bFullScreenMode)
		{
			if ( m_pDialog[ NCHILD_DLG ] != NULL )
			{
				((CNChildDlg*)m_pDialog[ NCHILD_DLG ])->clApplyerList[i].Set(&pclinfo->clApplyerList[i]);
			}
		}
		else
			pclFatherManager->clApplyerList[i].Set(&pclinfo->clApplyerList[i]);
	}

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NCHILD_DLG ] != NULL )
		{
			((CNChildDlg*)m_pDialog[ NCHILD_DLG ])->m_bUpdateFatherApplyerListSwitch = true;
		}
	}
	else
		pclFatherManager->bUpdateFatherApplyerListSwitch = true;
}


// ����  ���� �뺸. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHILDINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ChildInfo* pclinfo = (cltGameMsgResponse_ChildInfo*)pclMsg->cData;
}

// ����� �������� �뺸.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONPRIVATEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonPrivateInfo* pclinfo = (cltGameMsgResponse_PersonPrivateInfo*)pclMsg->cData;

	TCHAR* pText = GetTxtFromMgr(1287);

	TCHAR* pfathername = pText;
	if(pclinfo->clFather.siPersonID)
	{
		pfathername = pclinfo->clFather.szName;

		if ( _tcslen(pfathername)<= 0 || !_tcscmp(pfathername,TEXT("")) )
		{
			pText = GetTxtFromMgr(1287);
			pfathername = pText;
		}
	}

	SI32 changenum = 0;
	if(pclinfo->siChangeFatherNumber <= 1)
	{
		changenum = 0;
	}
	else
	{
		changenum = pclinfo->siChangeFatherNumber - 1;
	}

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if( m_pDialog[ NPERSONMALINFO_DLG ] == NULL )
		{
			CreateInterface( NPERSONMALINFO_DLG );
		}

		((CNPersonalInfoDlg*)(m_pDialog[ NPERSONMALINFO_DLG ]))->set(pclinfo->clPerson.szName,pfathername,changenum, 
			pclinfo->siLevel,pclinfo->siFameLevel, pclinfo->siCountry, pclinfo->bShowCountry,/*pschoolname,*/ pclinfo->szAccountID,pclinfo->siWealthRank,pclinfo->clMoney,
			pclinfo->szGreeting, pclinfo->siPVPWinNumber, pclinfo->siPVPLoseNumber, pclinfo->szPVPWinHighLevelUserName, 
			pclinfo->siNameLevel, pclinfo->szGuildName, pclinfo->siVillageUnique);
	}
}

// �ڽ��� Ǫġ�ڹ� �����ֱ� ���� ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_SETSHOWPUCHIKOMI(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetShowPuchikomi* pclinfo = (cltGameMsgResponse_SetShowPuchikomi*)pclMsg->cData;

	if( m_pDialog[ NSOUNDONOFF_DLG ] )
	{
		((CNSoundOnOffDlg*)(m_pDialog[ NSOUNDONOFF_DLG ]))->SetShowPuchikomiCheckBox( pclinfo->bShowPuchikomi );
	}

}

/*
// �б� ����� ���� �뺸 ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_SCHOOLUSERNUM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SchoolUserNum* pclinfo = (cltGameMsgResponse_SchoolUserNum*)pclMsg->cData;

	if(pclSchoolManager->siCurrentSchoolUnique == pclinfo->siSchoolUnique)
	{
		pclSchoolManager->siUserNum = pclinfo->siUserNum;
		pclSchoolManager->bShowUserNumSwitch = true;
	}
}
*/

// ���´� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SETFATHER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetFather* pclinfo = (cltGameMsgResponse_SetFather*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clBI.clFatherInfo.clFather.Set(&pclinfo->clFather);
	pclCM->CR[1]->pclCI->clBI.clFatherInfo.siMyLevelForFather	= (SI08)pclinfo->siMyLevel;
	MStrCpy ( pclCM->CR[1]->pclCI->clBI.clFatherInfo.szAccountID,pclinfo->szAccountID, MAX_PLAYER_NAME);

	pclCM->CR[1]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SETFATHER);

	pclFatherManager->bUpdateFatherSwitch = true ;
}

// ���� ������ ���¿��� �����
void cltClient::DoMsg_GAMEMSG_RESPONSE_REQUEST_SETFATHER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Request_SetFather* pclinfo = (cltGameMsgResponse_Request_SetFather*)pclMsg->cData;

	if (m_pDialog[NCOMMONMSG_DLG] == NULL)
	{
		CreateInterface( NCOMMONMSG_DLG );
	}
	((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->SetFather( pclinfo->siPupilPersonID, pclinfo->szPupilName);
	((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_SETFATHER);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PVPRESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PVPResult* pclinfo = (cltGameMsgResponse_PVPResult*)pclMsg->cData;

	if( true == pclinfo->bWin )
	{
		TCHAR* pTitle = GetTxtFromMgr(10068);
		TCHAR* pText  = GetTxtFromMgr(10069);

		TCHAR tempBuffer[128] = {'\0'};
		StringCchPrintf( tempBuffer, 128, pText, pclinfo->szUserName );
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, tempBuffer );
	}
	else
	{
		TCHAR* pTitle = GetTxtFromMgr(10070);
		TCHAR* pText  = GetTxtFromMgr(10071);

		TCHAR tempBuffer[128] = {'\0'};
		StringCchPrintf( tempBuffer, 128, pText, pclinfo->szUserName );
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, tempBuffer );
	}

	// PVP ���� ���� ������Ʈ
	pclCM->CR[1]->pclCI->clBI.siPVPWinNumber	= pclinfo->siPVPWinNumber;
	pclCM->CR[1]->pclCI->clBI.siPVPLoseNumber	= pclinfo->siPVPLoseNumber;
	StringCchCopy(pclCM->CR[1]->pclCI->clBI.szPVPWinHighLevelUserName, sizeof(pclCM->CR[1]->pclCI->clBI.szPVPWinHighLevelUserName), pclinfo->szPVPWinHighLevelUserName);
}

// ��ǰ ���꿡 �ʿ��� ���� �ð��� ���´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_MAKEITEMDELAY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MakeItemDelay* pclinfo = (cltGameMsgResponse_MakeItemDelay*)pclMsg->cData;

	pclCM->CR[1]->SetMakeDelayDraw(pclinfo->dwDelayClock);
}


// �������ϸ��̼��� �����ϰ� ������.
void cltClient::DoMsg_GAMEMSG_RESPONSE_MAKEITEMSWITCH(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MakeItemSwitch* pclInfo = (cltGameMsgResponse_MakeItemSwitch*)pclMsg->cData;

	if( pclInfo == NULL ) 
		return;

	pclCM->CR[1]->siPersonalMakeItemType = pclInfo->siType;
	pclCM->CR[1]->SetEnchantEffect(pclInfo->siType);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONMAKEITEMSWITCH(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonMakeItemSwitch* pclinfo = (cltGameMsgResponse_PersonMakeItemSwitch*)pclMsg->cData;

	SI32 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(targetid)
	{
		// ���ΰ� ĳ���ʹ� �ƴϾ�� �Ѵ�. 
		if(targetid != 1)
		{
			pclCM->CR[targetid]->siPersonalMakeItemType = pclinfo->siMakeItemSwitch;
			pclCM->CR[targetid]->SetEnchantEffect(pclinfo->siMakeItemSwitch);
		}
	}
}


// �ڴ�� ����� ���´�
void cltClient::DoMsg_GAMEMSG_RESPONSE_ROULETTEGAME_RESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RouletteGame_Result* pclinfo = (cltGameMsgResponse_RouletteGame_Result*)pclMsg->cData;

	if( m_pDialog[ ROULETTEGAME_DLG ] )
#ifdef _SAFE_MEMORY
		((CRouletteGameDlg*)m_pDialog[ ROULETTEGAME_DLG ])->m_pMiniGameManager->SetResult(&pclinfo->m_siRandom[0], pclinfo->m_siResult, pclinfo->m_siNumber);
#else
		((CRouletteGameDlg*)m_pDialog[ ROULETTEGAME_DLG ])->m_pMiniGameManager->SetResult(pclinfo->m_siRandom, pclinfo->m_siResult, pclinfo->m_siNumber);
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_QUESTEFFECT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_QuestEffect* pclinfo = (cltGameMsgResponse_QuestEffect*)pclMsg->cData;

	SI32 targetid = pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique);
	if(targetid)
	{
		if(QUEST_EFFECT_RECEIVE == pclinfo->m_siEffectType)	
		{
			pclCM->CR[targetid]->SetQuestEffectReceive();		
		}		
		else if(QUEST_EFFECT_CLEAR == pclinfo->m_siEffectType)	
		{
			pclCM->CR[targetid]->SetQuestEffectClear();
		}		
	}	

	// �� �ڽ��϶��� ����â�� �ݴ´�.
	if( targetid == 1 )
	{
		if ( m_pDialog[NQUESTSELECTITEM_DLG] )
		{
			m_pDialog[NQUESTSELECTITEM_DLG]->DeleteDialog();
		}
	}
}

// ����ȿ���� ��´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GENERALEFT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GeneralEft* pclinfo = (cltGameMsgResponse_GeneralEft*)pclMsg->cData;

	SI32 eftid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(eftid)
	{
		pclCM->CR[eftid]->clPB.siGeneralAC		= pclinfo->siDefRate;
		pclCM->CR[eftid]->clPB.siGeneralDamage	= pclinfo->siDamageRate;
	}
}

// Person�� �÷��� �ð��� ���Ѵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PLAYTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PlayTime* pclinfo = (cltGameMsgResponse_PlayTime*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clBI.siPlaySecond = pclinfo->siPlaySecond;

	if ( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ NSOUNDONOFF_DLG ])
	{
		((CNSoundOnOffDlg*)m_pDialog[ NSOUNDONOFF_DLG ])->SetTotalSpendTime( pclCM->CR[1]->pclCI->clBI.siPlaySecond , pclCM->CR[1]->pclCI->clBI.siPlayEventSecond );
	}
	else
		g_SoundOnOffDlg.SetTotalSpendTime( pclCM->CR[1]->pclCI->clBI.siPlaySecond );
}

/*
// Person�� �б� ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SCHOOL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_School* pclinfo = (cltGameMsgResponse_School*)pclMsg->cData;

	SI32 homeid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(homeid)
	{
		pclCM->CR[homeid]->pclCI->clBI.siSchoolUnique = pclinfo->siSchoolUnique;

		// �̸��� �ٽ� �����. 
		cltCharClient* pclchar  = (cltCharClient*)pclCM->CR[homeid];
		pclchar->MakeCharName(pclchar);
	}
}
*/


// Person�� �ּ��� ������ �뺸�޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_HOMEVILLAGE( cltMsg* pclMsg , SI32 id)
{
	cltGameMsgResponse_HomeVillage* pclinfo = (cltGameMsgResponse_HomeVillage*)pclMsg->cData;

	SI32 homeid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(homeid)
	{
		pclCM->CR[homeid]->pclCI->clBI.siHomeVillage = pclinfo->siHomeVillage;
	}
}

// Person�� �� ������ �뺸�޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_JIM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Jim* pclinfo = (cltGameMsgResponse_Jim*)pclMsg->cData;

	SI32 jimedid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(jimedid)
	{

		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[jimedid];

		// ���� ���� �����Ѵ�. 
		pclchar->clJim.Init();

		pclchar->clJim.SetBeJimed(pclinfo->siJimCharUnique, 1);

		pclchar->SetJimShow();
	}
}

// Person�� ������ �뺸�޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_WARKILL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WarKill* pclinfo = (cltGameMsgResponse_WarKill*)pclMsg->cData;

	if( 0 == pclinfo->uiSendMode )
	{
		pclCM->CR[1]->siBlackWarEnemyKillNumber			= pclinfo->siKillNumber;
		pclCM->CR[1]->siBlackWarKilledNumber			= pclinfo->siKilledNumber;
		pclCM->CR[1]->siBlackWarEnemyKillScore			= pclinfo->siKillScore;
		pclCM->CR[1]->siBlackWarEnemyKillVillageScore	= pclinfo->siKillVillageScore;
	}
	else if( 1 == pclinfo->uiSendMode )
	{
		pclCM->CR[1]->siWarEnemyKillNumber				= pclinfo->siKillNumber;
		pclCM->CR[1]->siWarKilledNumber					= pclinfo->siKilledNumber;
		pclCM->CR[1]->siBlackWarEnemyKillScore			= pclinfo->siKillScore;
		pclCM->CR[1]->siBlackWarEnemyKillVillageScore	= pclinfo->siKillVillageScore;
		pclCM->CR[1]->siBlackArmyWarMapIndex			= pclinfo->siWarMapIndex;
	}
}
// person�� �ɸ��� �ɼ� ���� ������ �޴´�
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHAR_OPTION(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Char_Option* pclinfo = (cltGameMsgResponse_Char_Option*)pclMsg->cData;

	// Ŭ���̾�Ʈ�� �ɸ��� ������ ���� �Ѵ�.
	pclCM->CR[ 1 ]->pclCI->clCharOption.Set( &pclinfo->clCharOptionInfo ) ; // Ŭ���̾�Ʈ�� �����Ѵ�.
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHAR_GET_OPTION(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Char_Get_Option* pclInfo = (cltGameMsgResponse_Char_Get_Option*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clCharOption.Set( &pclInfo->clCharOptionInfo );

	return;
}
// Person�� ������ ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGEMONEY(cltMsg* pclMsg, SI32 id)
{
	TCHAR Nbuffer[512]=TEXT(" ");
	cltGameMsgResponse_ChangeMoney* pclinfo = (cltGameMsgResponse_ChangeMoney*)pclMsg->cData;

	// �� ������ ������Ʈ �Ѵ�. 
	pclCM->CR[1]->pclCI->clIP.SetMoney(pclinfo->siMoney);

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	// ���� ����ǰ���� ����� ���̶��, 

	switch ( pclinfo->siReason )
	{
	case CHANGE_MONEY_REASON_WARWIN:
		break;
	case CHANGE_MONEY_REASON_GAMEMASTER:
		{
			TCHAR* pTitle = GetTxtFromMgr(244);
			TCHAR* pText  = GetTxtFromMgr(1288);
			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_REPAIRPAY:
		{
			TCHAR* pTitle = GetTxtFromMgr(1289);
			TCHAR* pText  = GetTxtFromMgr(1290);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, -pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_REPAIRGET:
		{
			TCHAR* pTitle = GetTxtFromMgr(1291);
			TCHAR* pText  = GetTxtFromMgr(1292);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_HUNTFEE:
		{
			TCHAR* pTitle = GetTxtFromMgr(1297);
			TCHAR* pText  = GetTxtFromMgr(1298);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_HUNTREWARD:
		{
			TCHAR* pTitle = GetTxtFromMgr(1299);
			TCHAR* pText  = GetTxtFromMgr(1300);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_NPCREPAIRPAY:
		{
			// pclMusic->PushEffect( SOUND_EFFECT_NPCREPAIR_SUCCESS, 0, 0 );
			pclMusic->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_REPAIR_SWORD")), 0, 0 );

			TCHAR* pText = GetTxtFromMgr(1306);

			if ( g_SoundOnOffDlg.m_bFullScreenMode )
			{
				if(( m_pDialog[ NNPCREPAIR_DLG  ])==NULL)
				{
					CreateInterface( NNPCREPAIR_DLG );
				}
				((NcltNPCRepairManager*)m_pDialog[ NNPCREPAIR_DLG  ])->SetReairSuccessMent( pText );
			}

			TCHAR* pTitle = GetTxtFromMgr(1307);
			pText  = GetTxtFromMgr(1290);
			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, -pclinfo->siChangedMoney );
		}
		break;
	case CHANGE_MONEY_REASON_INVESTMENTINFO:
		{
			TCHAR* pTitle = GetTxtFromMgr(1308);
			TCHAR* pText  = GetTxtFromMgr(1309);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText,-pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_FIZATION:
		{
			if(pclinfo->siChangedMoney)
			{
				TCHAR* pTitle = GetTxtFromMgr(1310);
				TCHAR* pText  = GetTxtFromMgr(1311);

				TCHAR level[128]= TEXT("") ;
				TCHAR money[128]= TEXT("") ;
				StringCchPrintf(level, 128, TEXT("%d"),FATHER_LEVEL);
				//StringCchPrintf(money, 128, TEXT("%d"),pclinfo->siChangedMoney);
				g_JYLibFunction.SetNumUnit( pclinfo->siChangedMoney, money, sizeof(money) );
				Nsprintf( Nbuffer,pText, TEXT("level"), level, TEXT("money"), money, NULL );
				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,Nbuffer);



				//m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, 
				//	FATHER_LEVEL, pclinfo->siChangedMoney);

			}
			else
			{
				TCHAR* pTitle = GetTxtFromMgr(1312);
				TCHAR* pText  = GetTxtFromMgr(1313);

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText,
					FATHER_LEVEL);
			}
		}
		break;
	case CHANGE_MONEY_REASON_CRAFTFUND:
		{
			TCHAR* pTitle = GetTxtFromMgr(6435);
			TCHAR* pText  = GetTxtFromMgr(6436);

			TCHAR money[128]= TEXT("") ;
			g_JYLibFunction.SetNumUnit( pclinfo->siChangedMoney, money, sizeof(money) );

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, money);
		}
		break;
		/*case CHANGE_MONEY_REASON_PUPILREWARD:
		{
			TCHAR* pTitle = GetTxtFromMgr(6435);
			TCHAR* pText  = GetTxtFromMgr(6436);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;
	case CHANGE_MONEY_REASON_GRANDFATHERREWARD:
		{
			TCHAR* pTitle = GetTxtFromMgr(6435);
			TCHAR* pText  = GetTxtFromMgr(6436);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney);
		}
		break;*/
	case CHANGE_MONEY_REASON_WORDSPECIALQUEST:
		{
			TCHAR* pTitle = GetTxtFromMgr(7542);
			TCHAR* pText = GetTxtFromMgr(7517);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->siChangedMoney );
		}
		break;
	case CHANGE_MONEY_REASON_BV_STOCKDIVIDEND:
		{
			NTCHARString32	kTitle( GetTxtFromMgr(3966) );
			NTCHARString128	kText( GetTxtFromMgr(8351) );
			TCHAR			szBuffer[64] = {'\0', };


			g_JYLibFunction.SetNumUnit( pclinfo->siChangedMoney, szBuffer, 64 );
			kText.Replace( TEXT("#money#"), szBuffer );

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( kTitle, kText );
		}
		break;

	case CHANGE_MONEY_REASON_GAWIBAWIBO_CHARGED_MONEY:		//  [8/12/2009 ��ȣ_GAWIBAWIBO] ����-���������� ��� ���� ���
		{
			//	���������� �̿����� ���������� ������ �����Ѵ�.
			GetGawiBawiBoMgr()->NextSteps();
		}
		break;

	case CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MONEY:		//  [8/12/2009 ��ȣ_GAWIBAWIBO] ����-���������� ���� ���
		{
			//	���������� ������ �޾Ҵ�.
			TCHAR*	pTitle	= GetTxtFromMgr(40050);
			NTCHARString256	pBody(GetTxtFromMgr(40054));

			NTCHARString256 strMoney;
			g_JYLibFunction.SetNumUnit(pclinfo->siChangedMoney, strMoney, 256);

			pBody.Replace("#money#", strMoney);

			cltClient* pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

			GetGawiBawiBoMgr()->EndGame();
		}
		break;

	case CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MAX_MONEY:		//  [8/12/2009 ��ȣ_GAWIBAWIBO] ����-���������� ���� ���
		{
			//	���������� ������ �޾Ҵ�.
			TCHAR*	pTitle	= GetTxtFromMgr(40050);
			NTCHARString256	pBody(GetTxtFromMgr(40054));

			NTCHARString256 strMoney;
			g_JYLibFunction.SetNumUnit(pclinfo->siChangedMoney, strMoney, 256);

			pBody.Replace("#money#", strMoney);

			cltClient* pClient = (cltClient*)pclClient;
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

			GetGawiBawiBoMgr()->EndGame();
		}
		break;

	default:
		break;
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ALLCHARINFOONE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AllCharInfoOne* pclinfo = (cltGameMsgResponse_AllCharInfoOne*)pclMsg->cData;

	if(pclCM->CR[1] && pclCM->CR[1]->pclCI)
	{
		pclCM->CR[1]->pclCI->SetOne(&pclinfo->clInfo);

		pclCM->CR[1]->m_siSetItemType = pclinfo->siSetItemType;
		pclCM->CR[1]->m_siSetItemStep = pclinfo->siSetItemStep;

		pclCM->CR[1]->m_siSetItemType2 = pclinfo->siSetItemType2;
		pclCM->CR[1]->m_siSetItemStep2 = pclinfo->siSetItemStep2;

		// ������ �ε��Ѵ�. ( ���� ������ ������Ʈ �� �ָ� �� )
		SI32 unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveWeapon ].siUnique;
		if( unique )
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveWeapon, unique );
		}

		// ����
		unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveClothes].siUnique;		
		if(unique)
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveClothes, unique );

		}

		unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveHat].siUnique;		
		if(unique)
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveHat, unique );
		}

		// �α��� �� �� �ѹ��� ����Ǿ�� �ϱ� ������ �׳� ���⿡ �־����� KKM
		if( siServiceArea != ConstServiceArea_Japan )
		{
			if(  pclCM->CR[1]->pclCI->clIP.GetLevel() < 20 &&
				0 == pclCM->CR[1]->pclCI->clBI.clFatherInfo.clFather.siPersonID )
			{
				CreateInterface( NCHILD_DLG );
			}
		}

		// ����, ��Ŀ �̺�Ʈ �ȳ� â ���� (PCK -2007.09.19)
		// �̺�Ʈ�Ⱓ�ȿ� ������� �����̰�, ĳ���� ������ 5���� ���ϸ� ������ ��.
		//if (pclClient->IsWhereServiceArea(ConstSwitch_GoStopPokerEvent))
		//{
		//	_SYSTEMTIME sStartEventDay , sEndEventDay;

		//	ZeroMemory(&sStartEventDay,sizeof(_SYSTEMTIME));
		//	ZeroMemory(&sEndEventDay,sizeof(_SYSTEMTIME));

		//	sStartEventDay.wYear = 2007;
		//	sStartEventDay.wMonth = 9;
		//	sStartEventDay.wDay = 20;
		//	sStartEventDay.wHour = 0;
		//	sStartEventDay.wMinute = 0;

		//	sEndEventDay.wYear = 2007;
		//	sEndEventDay.wMonth = 10;
		//	sEndEventDay.wDay = 19;
		//	sEndEventDay.wHour = 0;
		//	sEndEventDay.wMinute = 0;

		//	SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
		//	SI32 endEventdatevary = pclClient->GetMinuteFromsTime(sEndEventDay);

		//	_SYSTEMTIME fTimeDatevary = pclinfo->clInfo.clBI.GetFirstCreatTime(); //���� ���� ���� �ð�.

		//	SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

		//	if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary) && pclinfo->clInfo.clIP.GetLevel() < 5)
		//	{
		//		if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
		//		{
		//			CreateInterface( NCOMMONMSG_DLG );
		//		}
		//		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_GOSTOPPOCKERSTART);
		//	}
		//}
	}
	else
	{
		MsgBox(TEXT("Error"), TEXT("A459"));
	}

	bLoginNotice = false ;

#ifdef _NEW_INTERFACE_


#else //_NEW_INTERFACE_

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if( m_pDialog[ STATUSBAR_DLG ] )
		{
			((CNStatusBarDlg*) m_pDialog[ STATUSBAR_DLG ])->CharacterLogin();
		}
	}
#endif

	// ���ΰ� ĳ������ ��� ������ �޾Ҵ�.
	bReceiveMyCharAllInfoSwitch = true;


	((cltCharClient*)pclCM->CR[1])->MakeRankMarkEncBuffer();

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ALLCHARINFOTWO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AllCharInfoTwo* pclinfo = (cltGameMsgResponse_AllCharInfoTwo*)pclMsg->cData;

	if(pclCM->CR[1] && pclCM->CR[1]->pclCI)
	{
		pclCM->CR[1]->pclCI->SetTwo(&pclinfo->clInfo);
	}
}

// Person�� ��� ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ALLCHARINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AllCharInfo* pclinfo = (cltGameMsgResponse_AllCharInfo*)pclMsg->cData;

	if(pclCM->CR[1] && pclCM->CR[1]->pclCI)
	{
		pclCM->CR[1]->pclCI->Set(&pclinfo->clInfo);

		pclCM->CR[1]->m_siSetItemType = pclinfo->siSetItemType;
		pclCM->CR[1]->m_siSetItemStep = pclinfo->siSetItemStep;

		pclCM->CR[1]->m_siSetItemType2 = pclinfo->siSetItemType2;
		pclCM->CR[1]->m_siSetItemStep2 = pclinfo->siSetItemStep2;

		// ������ �ε��Ѵ�. ( ���� ������ ������Ʈ �� �ָ� �� )
		SI32 unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveWeapon ].siUnique;
		if( unique )
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveWeapon, unique );
		}

		// ����
		unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveClothes].siUnique;		
		if(unique)
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveClothes, unique );

		}

		unique = pclCM->CR[1]->pclCI->clCharItem.clItem[ pclCM->CR[1]->ActiveHat].siUnique;		
		if(unique)
		{
			pclCM->CR[1]->ChangeArmCode( pclCM->CR[1]->ActiveHat, unique );

		}

	}
	else
	{
		MsgBox(TEXT("Error"), TEXT("A459"));
	}

	if ( bLoginNotice && !g_SoundOnOffDlg.m_bMaxWindowMode )
	{
		//g_LoginNoticeDlg.set();
	}

	bLoginNotice = false ;

#ifdef _NEW_INTERFACE_


#else //_NEW_INTERFACE_

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if( m_pDialog[ STATUSBAR_DLG ] )
		{
			((CNStatusBarDlg*) m_pDialog[ STATUSBAR_DLG ])->CharacterLogin();
		}
	}
#endif

	// ���ΰ� ĳ������ ��� ������ �޾Ҵ�.
	bReceiveMyCharAllInfoSwitch = true;


	((cltCharClient*)pclCM->CR[1])->MakeRankMarkEncBuffer();

	/*
	// 5�����ϴ� ����, ���� ����Ʈ ����ֱ�
	if( pclCM->CR[1]->pclCI->clIP.GetLevel() <= 5 )
	{
		if( pclCM->CR[1]->GetKind() == 1 || pclCM->CR[1]->GetKind() == 2)
		{
			if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
				CreateInterface( NNEWQUEST_DLG );
			if(m_pDialog[ NNEWQUEST_DLG ])
			{
				pclQuestManager->bNewQuseOpened = TRUE;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(KIND_WAITINGMAN);
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
			}
		}
		else if( pclCM->CR[1]->GetKind() == 3 )
		{
			if(m_pDialog[ NNEWQUEST_DLG ] == NULL)
				CreateInterface( NNEWQUEST_DLG );
			if(m_pDialog[ NNEWQUEST_DLG ])
			{
				pclQuestManager->bNewQuseOpened = TRUE;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->m_siButtonType = 0;
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetNewQuest(KIND_WAITINGMAN3);
				((CNNewQuestDlg*)m_pDialog[ NNEWQUEST_DLG ])->SetOpenedQuestDlg( true );
			}
		}
	}
	*/
}


// ����������� �̿��Ͽ� ���� ������ �˸���. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_WARPEFFECT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WarpEffect* pclinfo = (cltGameMsgResponse_WarpEffect*)pclMsg->cData;

	id = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(id)
	{
		pclSmokeManager->SetSmoke(SMOKE_BEGINWARP, pclCM->CR[id]->GetCenterX(), pclCM->CR[id]->GetCenterY(), pclCM->CR[id]->pclMap);
	}


}

// Person�� ���� Ǯ���ش�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_HORSEFREE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HorseFree* pclinfo = (cltGameMsgResponse_HorseFree*)pclMsg->cData;

	SI32 tempid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(tempid <= 0)return ;

	cltHorse* pclHorse = pclCM->CR[tempid]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclHorse == NULL || pclHorse->siHorseUnique <= 0)
		return;

	// ������ ������ �Ѵ�. 
	pclCM->CR[tempid]->UnrideHorse();

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	// ���� �����. 
	pclCM->CR[tempid]->pclCI->clHorseInfo.Init(pclCM->CR[tempid]->pclCI->clHorseInfo.siCurrentShowHorse);


	// �����ڸ� �����Ѵ�. 
	pclCM->CR[tempid]->DeleteSlave();


	if( m_pDialog[ CLTNCHARSTATUS_DLG ] )
	{
		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->m_bChangedInitHorseStatus = TRUE;

		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->InitHorseStatusInfo();

		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->UpdateHorseStatusInfo();
	}

	// Ǯ���ذ� �ڽ��̰� ���� �� ǰ�� ����â�� ���������� �ݾ��ش�.
	/*
	if( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ CLTNCHARSTATUS_DLG ] )
	{
		// Ǯ���ذ� �ڽ��̰� ���� �� ǰ�� ����â�� ���������� �ݾ��ش�.
		if ( tempid == 1 && ((cltNCharStatus*)(m_pDialog[ CLTNHORSETYPECHANGE_DLG ]))->IsCreate())
		{
			CreateInterface( CLTNHORSETYPECHANGE_DLG );
		}
	}
	*/
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGEHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ChangeHorse* pclinfo = (cltGameMsgResponse_ChangeHorse*)pclMsg->cData;

	//	SI32 tempid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	//	if(tempid <= 0)return ;

	// �����ڸ� �����Ѵ�. 
	//	pclCM->CR[tempid]->DeleteSlave();

	SI32 tempid		= cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(tempid <= 0)return ;

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[tempid];

	// �����ڸ� �����Ѵ�. 
	pclCM->CR[tempid]->DeleteSlave();

	pclChar->pclCI->clHorseInfo.SetCurrentShowHorseIndex(pclinfo->siChangeHorseIndex);

	//pclChar->siSlaveID = pclCM->GetIDFromCharUnique(pclinfo->cltChangeHorse.siHorseUnique);

	if( pclinfo->siCharUnique == 1)
	{
		if( m_pDialog[ CLTNCHARSTATUS_DLG ] )
		{
			((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->UpdateHorseStatusInfo();
		}	
	}
}

// ����ġ�� ������� ó��
void cltClient::DoMsg_GAMEMSG_RESPONSE_GETEXP(cltMsg* pclMsg, SI32 id)
{	
	TCHAR buffer[256];

	cltGameMsgResponse_GetExp* pclinfo = (cltGameMsgResponse_GetExp*)pclMsg->cData;
	SI32 getexpid	= cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];

	// ��ȯ���� ����ġ�� ���޹����� Invalid �� �� �ִ�. (���� �𸣰ڴ� ȭ�鿡 ���̸� �׶� Update����)
	if(pclCM->IsValidID(getexpid) == FALSE)	return ;

	// ����̰ų� ��ȯ����� ������ �Ѵ�.
	if( IsPC(pclinfo->siCharUnique) == false && 
		pclCM->CR[getexpid]->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)return ;

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[getexpid];

	// ���� ����ġ ȹ���, 
	if(pclinfo->siExp)
	{

		// ����ġ�� ǥ���Ѵ�. (��ȿ�� ����ġ�� �ְų� ������� ��쿡��.) 
		pclchar->pclExpCounter->Set(pclinfo->siExp, 30); 

		// ����� �����Ѵ�.
		if(IsPC(pclinfo->siCharUnique) == true)
		{
			// ����ġ�� �����Ѵ�. 
			pclchar->pclCI->clIP.SetCurExp(pclinfo->siExp + pclchar->pclCI->clIP.GetCurExp());// SI32->SI64 ����ġ �����÷ο춧���� ����

			if(pclinfo->siReason & GETEXP_REASON_VILLAGEWAR1)
			{
				TCHAR* pText = GetTxtFromMgr(1314);

				StringCchPrintf(buffer, 256, pText, pclinfo->siExp);



				//if ( g_SoundOnOffDlg.m_bFullScreenMode )
				//{
				if(m_pDialog[ NSEIGEWIN_DLG ]==NULL)
				{
					CreateInterface(NSEIGEWIN_DLG);
				}

				((CNSiegeWinDlg*)m_pDialog[ NSEIGEWIN_DLG ])->Set(buffer);
				//	}
				//	else
				//	{
				//		m_pSiegeWinDlg->Set(buffer);
				//	}

			}
			if( pclinfo->siReason & GETEXP_REASON_VILLAGEWAR2)
			{
				TCHAR* pText = GetTxtFromMgr(1315);

				StringCchPrintf(buffer, 256, pText, pclinfo->siExp);

				//	if ( g_SoundOnOffDlg.m_bFullScreenMode )
				//	{
				if(m_pDialog[ NSEIGEWIN_DLG ]==NULL)
				{
					CreateInterface(NSEIGEWIN_DLG);
				}
				((CNSiegeWinDlg*)m_pDialog[ NSEIGEWIN_DLG ])->Set(buffer);					
				//}
				//else
				//{
				//		m_pSiegeWinDlg->Set(buffer);
				//}
			}
			if( pclinfo->siReason & GETEXP_REASON_VILLAGEWARKILLSCORE )
			{
				//TCHAR * pTitle = GetTxtFromMgr(3710);
				TCHAR * pText = GetTxtFromMgr(6515);
				StringCchPrintf(buffer,256,pText, pclinfo->siExp);

				// pclMessage->SetMsg(buffer);
				//m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

				PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

				if((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ]==NULL)
				{
					CreateInterface( NPERSONALSHOP_POP_DLG);
					((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->MoveDialog(5,20);
				}

				((CNLetterDlg*)m_pDialog[ NPERSONALSHOP_POP_DLG ])->Push(buffer);
			}


			if(pclinfo->siReason & GETEXP_REASON_MAKEITEM)
			{

			}
		}
		else 
		{
			// ��ȯ����� �θ��� ��ȯ�� ������ Update ��Ų��.
			SI32 siParentID = pclCM->CR[getexpid]->GetSummonParentID();
			if(pclCM->IsValidID(siParentID) == TRUE)
			{
				cltCharClient* pclparentchar = (cltCharClient*)pclCM->CR[siParentID];
				cltSummon *pclSummon = pclparentchar->pclCI->clSummonInfo.GetSummon(pclCM->CR[getexpid]->GetSummonIndex());
				if(pclSummon)
				{
					// �θ� ��ȯ�� ������ ����ġ�� �����Ѵ�. 
					SI64 siTotalExp = (SI64)pclinfo->siExp + pclSummon->clIP.GetCurExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
					pclSummon->clIP.SetCurExp(siTotalExp);
				}
			}
		}
	}
	// �� ����ġ ȹ���, 
	if(pclinfo->siFameExp)
	{
		// ����ġ�� ǥ���Ѵ�. (��ȿ�� ����ġ�� �ְų� ������� ��쿡��.) 
		pclchar->pclExpCounter->Set(pclinfo->siExp, 30); 

		// ����� �����Ѵ�.
		if(IsPC(pclinfo->siCharUnique) == true)
		{
			// ����ġ�� �����Ѵ�. 
			pclchar->pclCI->clIP.siFameExp += pclinfo->siFameExp;

			// ���� �������� �� ����ġ ȹ��. 
			if(pclinfo->siReason & GETEXP_REASON_FAMEFATHER)
			{
				TCHAR* pTitle = GetTxtFromMgr(1317);
				TCHAR* pText = GetTxtFromMgr(1316);

				StringCchPrintf(buffer, 256, pText, pclinfo->siFameExp);
				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
			}
		}
	}


}

// �¾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_HIT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Hit* pclhitinfo = (cltGameMsgResponse_Hit*)pclMsg->cData;

	SI32 hitid = cltCharCommon::CharUniqueInfo[pclhitinfo->CharUnique];
	if(pclCM->IsValidID(hitid) == FALSE)
		return ;

	// �ǰ���. 
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[hitid];

	// MISS or DODGE
	if( pclhitinfo->bMissHit || pclhitinfo->bDodgeHit )
	{
		// [����] ��Ʋ�ξ�ʿ� �ִٸ� MISS or DODGE�� ��� ���� �ʴ´�.
		if( pclchar->GetMapIndex() != MAPINDEX_BATTLEROYAL_MABRIUM && pclchar->GetMapIndex() != MAPINDEX_BATTLEROYAL_GRANDMABRIUM)
		{
			// �������� ǥ���Ѵ�. 
			g_AttackEffectMgr.SetDamageData( pclCM->CR[hitid]->GetCenterX(), 
				pclCM->CR[hitid]->GetCenterY(), pclhitinfo->Damage, false, pclhitinfo->bMissHit, pclhitinfo->bDodgeHit, pclhitinfo->uiType );
		}
	}
	// ����������
	else
	{
		// [����] ��Ʋ�ξ�ʿ� �ִٸ� �������� ��� ���� �ʴ´�.
		if( pclchar->GetMapIndex() != MAPINDEX_BATTLEROYAL_MABRIUM && pclchar->GetMapIndex() != MAPINDEX_BATTLEROYAL_GRANDMABRIUM)
		{
			// PCK : ���ڹ����� �ɷ��ְ� Ż���� ź �����̸� �߰� �������� �ѹ��� ǥ���Ѵ�.
			if(pclhitinfo->SpecialAttackSwitch == 2 )
			{
				// �������� ǥ���Ѵ�. (ù��°)
				g_AttackEffectMgr.SetDamageData( pclCM->CR[hitid]->GetCenterX(), 
					pclCM->CR[hitid]->GetCenterY(), pclhitinfo->Damage, false, pclhitinfo->bMissHit, pclhitinfo->bDodgeHit, pclhitinfo->uiType );

				// �������� ǥ���Ѵ�. (�ι�°)
				g_AttackEffectMgr.SetDamageData( pclCM->CR[hitid]->GetCenterX() + 50, 
					pclCM->CR[hitid]->GetCenterY() - 20, pclhitinfo->DoubleDamage, false, pclhitinfo->bMissHit, pclhitinfo->bDodgeHit, pclhitinfo->uiType );
			}
			else
			{
				// �������� ǥ���Ѵ�. 
				g_AttackEffectMgr.SetDamageData( pclCM->CR[hitid]->GetCenterX(), 
					pclCM->CR[hitid]->GetCenterY(), pclhitinfo->Damage, false, pclhitinfo->bMissHit, pclhitinfo->bDodgeHit, pclhitinfo->uiType );
			}
		}
		

		// �ǰ����� Life�� ���δ�. 
		pclchar->SetLife(pclhitinfo->Life);

		// ���� ������ �����ϰ� �Ѵ�. 
		pclchar->SetCharCut(pclhitinfo->Mode);

		// Clone�̸� �ǰ� ���ϰ� �״´�. �Ϲ������δ� �ǰ��� �����Ѵ�.
		if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false)
		{
			// �ǰ� ���¸� �����Ѵ�. 
			pclchar->SetHitSwitch(pclhitinfo->bIndure);
		}

		// �ǰݵ� ȿ���� ���ؼ� ��½�̰� �Ѵ�. 
		pclchar->SetNewSelectedSwitch(true);

		// by LEEKH 2007.12.28 - TRANSFORM
		// �ǰ� ȿ������ �����Ѵ�. 
		if(pclchar->GetKindInfo()->clKIEffectInfo.siHitEffect)
		{
			PushEffect(pclchar->GetKindInfo()->clKIEffectInfo.siHitEffect, pclchar->GetX(), pclchar->GetY());
		}

		// �ʻ��� �۵��� ���̸�,
		if(pclhitinfo->SpecialAttackSwitch == 1)
		{
			pclchar->pclCriticalEffect->SetAction();
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CRITICALHIT")), pclchar->GetX(), pclchar->GetY());
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_INCLIFE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_IncLife* pclinfo = (cltGameMsgResponse_IncLife*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);

	if(pclCM->IsValidID(targetid) == false)
	{
		// ü���� 0�� ���¶�� ��� ó��. 
		if(pclinfo->siCharUnique != MyCharUnique && pclinfo->siLife == 0)
		{
			DeleteReservedChar(pclinfo->siCharUnique);
		}
		return ;
	}

	pclCM->CR[targetid]->SetLife(pclinfo->siLife);
	pclCM->CR[targetid]->clPB.siReservedLife = pclinfo->siReservedLife;

	/*	// Ŭ�� ������ Ŭ������ �������� ������ ���������� �����ش�.
	if( pclCM->CR[targetid]->clPB.siReservedLife >= pclinfo->siReservedLife )
	{
	}
	else
	{
		pclCM->CR[targetid]->SetLife(pclinfo->siLife);
		pclCM->CR[targetid]->clPB.siReservedLife	= pclinfo->siReservedLife;
	}*/

		// ���ΰ��� ��ȯ�����, 
		if(pclCM->CR[targetid]->GetSummonParentID() == 1)
		{
			// ���ΰ��� ������ �����Ѵ�. 
			pclCM->CR[1]->pclCI->clSummonInfo.clSummon[pclCM->CR[targetid]->GetSummonIndex()].clIP.SetLife(pclinfo->siLife);
		}

		// �ڽ��� ȸ���Ǿ�� , 
		if(targetid == 1 && pclinfo->siReservedLife > 0)
		{
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_RECOVERLIFE")), 0, 0);
		}

		switch(pclinfo->siReason)
		{
		case INCLIFE_REASON_HEALTH:
			if(targetid == 1  && pclinfo->siIncLife < 0)
			{
				TCHAR* pText = GetTxtFromMgr(1320);

				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(pText);
				}
				else
				{
					pclClient->pclMessage->SetMsg(pText);
				}
			}
			break;
		}

}


void cltClient::DoMsg_GAMEMSG_RESPONSE_INCMANA(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_IncMana* pclinfo = (cltGameMsgResponse_IncMana*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);

	if(pclCM->IsValidID(targetid) == false)
	{
		return ;
	}

	pclCM->CR[targetid]->SetMana(pclinfo->siMana);

	// ���ΰ��� ��ȯ�����, 
	if(pclCM->CR[targetid]->GetSummonParentID() == 1)
	{
		// ���ΰ��� ������ �����Ѵ�. 
		pclCM->CR[1]->pclCI->clSummonInfo.clSummon[pclCM->CR[targetid]->GetSummonIndex()].clIP.SetMana(pclinfo->siMana);
	}

	// �ڽ��� ȸ���Ǿ�� , 
	if(targetid == 1 && pclinfo->siIncMana > 0)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_RECOVERMANA")), 0, 0);
	}

}

// ���� ����� ���� ������ ����. 
void cltClient::DoMsg_GAMEMSG_REPONSE_INCHUNGRY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_IncHungry* pclinfo = (cltGameMsgResponse_IncHungry*)pclMsg->cData;

	if(pclCM->IsValidID(1) == false)return ;

	pclCM->CR[1]->pclCI->clHealthInfo.siHungry = pclinfo->siHungry;

	// ��Ʈ�� �����. 
	TCHAR buffer[256];
	const TCHAR* pitemname = pclItemManager->GetName(pclinfo->siFoodUnique);
	SI32 systemtxt = 0 ;
	if(pitemname)
	{
		TCHAR* pText = GetTxtFromMgr(1321);
		systemtxt = 1321 ;

		StringCchPrintf(buffer, 256, pText, pitemname);

		SI32 status  = pclCM->CR[1]->clPB.clHealth.GetHungryStatus(pclCM->CR[1]->pclCI->clIP.GetLevel());

		if(status & (HEALTH_STATUS_HUNGRY_1 | HEALTH_STATUS_HUNGRY_2))
		{
			pText = GetTxtFromMgr(1322);			
			systemtxt = 1322 ;

			StringCchCat(buffer, 256, pText);
		}
		else if(status & HEALTH_STATUS_HUNGRY_3)
		{
			pText = GetTxtFromMgr(1323);
			systemtxt = 1323 ;
			StringCchCat(buffer, 256, pText);
		}
		else if(status & HEALTH_STATUS_HUNGRY_NORMAL)
		{
			pText = GetTxtFromMgr(1324);
			systemtxt = 1324 ;

			StringCchCat(buffer, 256, pText);
		}
		else if(status & HEALTH_STATUS_HUNGRY_7)
		{
			pText = GetTxtFromMgr(1325);
			systemtxt = 1325 ;

			StringCchCat(buffer, 256, pText);
		}
		else
		{
			pText = GetTxtFromMgr(1326);
			systemtxt = 1326 ;

			StringCchCat(buffer, 256, pText);
		}

		// �޽����� ������ ������. 
		SendChatMessage(CHATMODE_SYSTEM, buffer,0);



	}

	////��Ű���� ����Ʈ �߰� itemunique 3740 �̸� ����Ʈ Ŭ���� �������� ������?



}

//extern "C" __declspec(dllimport) void Show( TCHAR *url );


void cltClient::DoMsg_GAMEMSG_RESPONSE_USERID(cltMsg* pclMsg, SI32 id)
{
	//cltGameMsgResponse_Userid* pclinfo = (cltGameMsgResponse_Userid*)pclMsg->cData;

	//TCHAR strURL[_MAX_PATH]; 

	//GetCharCZUrl( strURL, pclCM->CR[ 1 ]->pclCI->clBI.szAccountID, pclinfo->strUserID );

	/*
	//	strcat( strURL, pclinfo->strUserID );
	//	strcat( strURL, TEXT("") );
	//	::ShellExecute( NULL, NULL, strURL, NULL, NULL, SW_SHOWNORMAL );


	HWND hFindWindow = ::FindWindow(NULL, TEXT("����") );

	if ( hFindWindow )
	{
		COPYDATASTRUCT cds;
		cds.dwData = 0;
		cds.cbData = _tcslen ( strURL ) + 1;
		cds.lpData = strURL;

		SendMessage( hFindWindow, WM_COPYDATA, (WPARAM) GetHwnd(), (LPARAM) &cds );
	}
	else
	{
		if ( szID != NULL && szPassword != NULL && _tcslen(szID) > 0 && _tcslen(szPassword) > 0 && _tcscmp( pclinfo->strUserID, szID ) == 0 )
		{
			TCHAR Buffer[ 512 ] = TEXT("");
			//sprintf( Buffer, TEXT("%s ret=%s&uid=%s&passwd=%s"), TEXT("http://help.ndoors.com/confirm/login.dll?check"), strURL, szID, szPassword );
			sprintf( Buffer, TEXT("%s %s"), szID, szPassword );
			ShellExecute( GetHwnd(), NULL, TEXT("MiniHome.exe"), Buffer, NULL, SW_SHOWNOACTIVATE );
			ShowWindow( GetHwnd(), SW_SHOW );
		}
		else
		{
			ShellExecute( GetHwnd(), NULL, TEXT("MiniHome.exe"), strURL, NULL, SW_SHOWNOACTIVATE );
			ShowWindow( GetHwnd(), SW_SHOW );
		}
	}
	*/

		return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMENDPERSONAVAILABLE(cltMsg* pclMsg, SI32 id)
{
#ifdef USE_PROMOTOR_CLIENT
	// USE_PROMOTOR_CLIENT �� ��õ�� â�� ����� �ʴ´�. (�ٸ��� ����ϰŵ�.)
	return;
#else			
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if( ((CNRecommendPersonDlg*)m_pDialog[ NRECOMMENDPERSON_DLG ])->IsShow() == false )
			((CNRecommendPersonDlg*)m_pDialog[ NRECOMMENDPERSON_DLG ])->Show();
	}

#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMENDPERSON(cltMsg* pclMsg, SI32 id)
{
	// ���� �ϳ� �����ָ� ��¡..
	cltGameMsgResponse_RecommendPerson* pclinfo = (cltGameMsgResponse_RecommendPerson*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	TCHAR Buffer[ 128 ] = TEXT("");
	TCHAR* pText = GetTxtFromMgr(1327);
	TCHAR* pTitle = GetTxtFromMgr(1328);

	StringCchPrintf( Buffer, 128, pText, pclinfo->strUserName );
	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, Buffer );

	if( g_SoundOnOffDlg.m_bFullScreenMode )
		((CNRecommendPersonDlg*)m_pDialog[ NRECOMMENDPERSON_DLG ])->Hide();

	//	m_pRecommendPersonDlg->Hide();
	return;
}

// PERSON�� ���������� �뺸����
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONALLSHAPEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonAllShapeInfo* pclinfo = (cltGameMsgResponse_PersonAllShapeInfo*)pclMsg->cData;

	SI32 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(targetid)
	{
		// ���ΰ� ĳ���ʹ� �ƴϾ�� �Ѵ�. 
		if(targetid != 1)
		{
			// ���� ������ ���� Person��ArmCode�� �ٲ��ش�. 
			pclCM->CR[targetid]->clPB.clShapeEquip.Set(&pclinfo->clEquipInfo);

			pclCM->CR[targetid]->ChangeArmCode(pclCM->CR[targetid]->ActiveHat,  pclinfo->clEquipInfo.clHelmet.uiUnique);
			pclCM->CR[targetid]->ChangeArmCode(pclCM->CR[targetid]->ActiveClothes,  pclinfo->clEquipInfo.clArmour.uiUnique);
			pclCM->CR[targetid]->ChangeArmCode(PERSONITEM_MANTLE,  pclinfo->clEquipInfo.clMantle.uiUnique);
			pclCM->CR[targetid]->ChangeArmCode(PERSONITEM_WEAPON1, pclinfo->clEquipInfo.clWeapon.uiUnique);

			// PCK : �������� �ػ����� ������ Ż���� �����ϰ� �ϳ��� �̹����� �ٲ��. (09.08.11)
			if(pclCM->CR[targetid]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM_HORSE))
			{
				SI32 siTransFormHorseUnique = pclCM->CR[targetid]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_TRANSFORM_HORSE);
				pclCM->CR[targetid]->ChangeHorseCode(siTransFormHorseUnique, &pclinfo->clAddStatusDate, pclinfo->siStatusTicketNum);
			}
			else
			{
				pclCM->CR[targetid]->ChangeHorseCode( pclinfo->siHorse, &pclinfo->clAddStatusDate, pclinfo->siStatusTicketNum );
			}

			// ���ڿ� ���� ĳ���� ��ũ�� �ٽ� �����. - by LEEKHw
			((cltCharClient*)pclCM->CR[targetid])->MakeRankMarkEncBuffer();
		}
	}

}


// ���� ���� ��ȯ���� ������ ����Ǿ���.(�θ𿡰� �����¸޽���) 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGESUMMONSTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ChangeSummonStatus* pclinfo = (cltGameMsgResponse_ChangeSummonStatus*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(targetid > 0)
	{

		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[targetid];

		//------------------------------------------
		// ���� ������Ʈ
		//------------------------------------------
		pclchar->siChildCharUnique	= pclinfo->siChildCharUnique;
		pclchar->siSummonIndex		= pclinfo->siSummonIndex;
	}	
}

// ĳ������ �߰������� ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ADDINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AddInfo* pclinfo = (cltGameMsgResponse_AddInfo*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(targetid <= 0)
	{
		// ü���� 0�� ���¶�� ��� ó��. 
		if(pclinfo->siCharUnique != MyCharUnique && pclinfo->siLife == 0)
		{
			DeleteReservedChar(pclinfo->siCharUnique);
		}

		return ;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[targetid];

	//------------------------------------------
	// ���� ������Ʈ
	//------------------------------------------
	pclchar->clAddInfo.Set(&pclinfo->AddInfo);

}


// ĳ������ InnerStatus������ ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_INNERSTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InnerStatus* pclinfo = (cltGameMsgResponse_InnerStatus*)pclMsg->cData;

	id = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(id)
	{
		pclCM->CR[id]->clInnerStatus.Set(&pclinfo->clInnerStatusInfo);
	}	
}

// ĳ������ ���� ���� ������ ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGESTATUSINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_StatusInfo* pclinfo = (cltGameMsgResponse_StatusInfo*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(targetid <= 0)	return ;

	if(pclCM->IsValidID(targetid) == FALSE) return;
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[targetid];

	//------------------------------------------
	// ���� ������Ʈ
	//------------------------------------------
	switch(pclinfo->ChangeInfo.siChangeType)
	{
	case CHANGETYPE_TOPSKILLUNIQUE:		
		{
			pclchar->clInnerStatus.siTopSkillUnique = pclinfo->ChangeInfo.siChageAmount1;
		}
		break;

	case CHANGETYPE_AUTOFOOD:		
		{
			pclchar->pclCI->clHorseInfo.bAutoFoodSwitch = pclinfo->ChangeInfo.bChangeSwitch;
		}
		break;

	case CHANGETYPE_POISON:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_POISON);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_POISON);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_POISON) )
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
		}
		break;
	case CHANGETYPE_POISON_SETITEM_EFFECT:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus( INNERSTATUS_POISON_SETITEM_EFFECT );
			}
			else
			{
				pclchar->clInnerStatus.DelStatus( INNERSTATUS_POISON_SETITEM_EFFECT );
			}
			if(pclchar->clInnerStatus.IsStatus( INNERSTATUS_POISON_SETITEM_EFFECT ) )
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
		}
		break;
	case CHANGETYPE_ICE:	
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_ICE);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_ICE);
			}

			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_ICE))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_ICE_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
		}
		break;
	case CHANGETYPE_FROZEN:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_FROZEN);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_FROZEN);
			}

			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_FROZEN))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_FROZEN_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
		}
		break;
	case CHANGETYPE_STUN:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_STUN);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_STUN);
			}

			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_STUN))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_FROZEN_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
		}
		break;
	case CHANGETYPE_DRAIN:
		{
			pclchar->bDrainSwitch	= pclinfo->ChangeInfo.bChangeSwitch;
			pclchar->siDrainFrame	= 0;

			// INCREASE LIFE�� ���� ó���� �Ѵ�.
			pclchar->SetLife(pclinfo->ChangeInfo.siChageAmount1);
			pclchar->SetMana(pclinfo->ChangeInfo.siChageAmount2);

			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_DRAIN_FIRE")), 0, 0);

			// ���ڸ� ȭ�鿡 ǥ���ϰ� �Ѵ�.
			pclchar->pclHealCounter->Set(pclinfo->ChangeInfo.siChageAmount3, 20); 				
			break;
		}

	case CHANGETYPE_HEAL:
		{
			pclchar->dwHealClock = CurrentClock;
			// ġ�� ȿ��. 
			// INCREASE LIFE�� ���� ó���� �Ѵ�.
			pclchar->SetLife(pclinfo->ChangeInfo.siChageAmount1);

			if(targetid == 1)
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_RECOVERLIFE")), 0, 0);
			}

			// ���ڸ� ȭ�鿡 ǥ���ϰ� �Ѵ�.
			pclchar->pclHealCounter->Set(pclinfo->ChangeInfo.siChageAmount2, 20); 				

			break;
		}
	case CHANGETYPE_NOFIRSTATTACK:
		{
			pclchar->bNoFirstAttackSwitch = pclinfo->ChangeInfo.bChangeSwitch;	
			if(pclchar->bNoFirstAttackSwitch)
			{
				//PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}

			break;
		}
	case CHANGETYPE_SUMMONNOFIRSTATTACK: // [����] ��ȯ�� �������� ȿ��
		{
			SI32 siSummonID = pclchar->GetSummonID();
			cltCharClient *pclSummon = pclCM->GetCharClient(siSummonID);
			if( NULL != pclSummon)
			{
				pclSummon->bNoFirstAttackSwitch = pclinfo->ChangeInfo.bChangeSwitch;
			}
			break;
		}
	case CHANGETYPE_NOFIRSTATTACKPREMIUM: // [����] �����̾� �������� ȿ��
		{
			pclchar->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum = pclinfo->ChangeInfo.bChangeSwitch;
			break;
		}
	case CHANGETYPE_ANGEL:
		{
			pclchar->pclCI->clBI.uiAngelSwitch = pclinfo->ChangeInfo.bChangeSwitch;	
			if(pclchar->pclCI->clBI.uiAngelSwitch )
			{
				TCHAR* pText = GetTxtFromMgr(1329);

				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(pText);
				}
				else
				{
					pclClient->pclMessage->SetMsg(pText);
				}
			}
			else
			{
				TCHAR* pText = GetTxtFromMgr(1330);

				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(pText);
				}
				else
				{
					pclClient->pclMessage->SetMsg(pText);
				}
			}

			break;
		}

	case CHANGETYPE_POLICE:
		{
			pclchar->pclCI->clBI.uiPoliceSwitch = pclinfo->ChangeInfo.bChangeSwitch;	

			break;
		}

	case CHANGETYPE_NOICEATTACK: // ICE ���ݹ����� ���Ҿ� ICE ���� 
		{
			pclchar->bNoIceAttackSwitch =  pclinfo->ChangeInfo.bChangeSwitch;	
			if(pclchar->bNoIceAttackSwitch)
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_ICE);
			}
			break;
		}
	case CHANGETYPE_CURSEATTACK:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->SetMana(pclinfo->ChangeInfo.siChageAmount1);
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_CURSEATTACK);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_CURSEATTACK);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_CURSEATTACK))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}

			break;
		}

	case CHANGETYPE_CURSECRITICAL:	
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->SetMana(pclinfo->ChangeInfo.siChageAmount1);
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_CURSECRITICAL);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_CURSECRITICAL);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_CURSECRITICAL))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
			break;
		}

	case CHANGETYPE_CURSEDEFENSE:	
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->SetMana(pclinfo->ChangeInfo.siChageAmount1);
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_CURSEDEFENSE);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_CURSEDEFENSE);
			}

			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_CURSEDEFENSE))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
			break;
		}
	case CHANGETYPE_CURSEMOVESPEED:	
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->SetMana(pclinfo->ChangeInfo.siChageAmount1);
				pclchar->clPB.GivenMoveSpeed	= pclinfo->ChangeInfo.siChageAmount2;
				pclchar->clPB.TotalMoveSpeed    = pclinfo->ChangeInfo.siChageAmount2;	
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_CURSEMOVESPEED);
			}
			else
			{
				pclchar->clPB.GivenMoveSpeed	= 0;
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_CURSEMOVESPEED);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_CURSEMOVESPEED))
			{
				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
			break;
		}		
	case CHANGETYPE_INCREASEMOVESPEED:	
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clPB.GivenMoveSpeed	= pclinfo->ChangeInfo.siChageAmount1;
				pclchar->clPB.TotalMoveSpeed    = pclinfo->ChangeInfo.siChageAmount1;	
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_INCREASEMOVESPEED);
			}
			else
			{
				pclchar->clPB.GivenMoveSpeed	= 0;
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_INCREASEMOVESPEED);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED))
			{
				//PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}
			break;
		}		

	case CHANGETYPE_MAGICFIRE:
		{
			if(pclinfo->ChangeInfo.bChangeSwitch)
			{
				pclchar->clInnerStatus.SetStatus(INNERSTATUS_MAGICFIRE);
			}
			else
			{
				pclchar->clInnerStatus.DelStatus(INNERSTATUS_MAGICFIRE);
			}
			if(pclchar->clInnerStatus.IsStatus(INNERSTATUS_MAGICFIRE) )
			{
				//PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_POISON_FIRE")), pclchar->GetX(), pclchar->GetY());
			}

			break;
		}
	case CHANGETYPE_HEARTEFFECT:
		{
			pclchar->bHeartEffectSwitch = pclinfo->ChangeInfo.bChangeSwitch;
			break;
		}
	case CHANGETYPE_FOURLEAF:
		{
			pclchar->bFourLeafSwitch = pclinfo->ChangeInfo.bChangeSwitch;
			break;
		}
	case CHANGETYPE_TRANSFORM100EFFECT:
		{
			pclchar->clTransFormInfo.bTransForm100Effect = pclinfo->ChangeInfo.bChangeSwitch;
			break;
		}
	case CHANGETYPE_TRANSFORMBUF:
		{
			((cltCharCommon*)pclchar)->siBufTransformKind = (SI16)pclinfo->ChangeInfo.siChageAmount1;

			SI32 aniref		= pclchar->GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(pclchar->Animation);
			if(aniref == -1)
			{
				// ���� ������ ĳ���� ���ϸ��̼��� �ʱ�ȭ �ؾ��Ѵ�.
				pclchar->WaitType = ANITYPE_WAIT0;
				pclchar->SetAnimation(pclchar->WaitType);
				pclchar->DoAnimationDelay();
			}
		}
		break;

	case CHANGETYPE_EMBLEM:
		{
			pclchar->m_uiWeaponSkillMasterEmblem = (UI08)pclinfo->ChangeInfo.siChageAmount1;
		}
		break;

	case CHANGETYPE_DISPLAYLOVELEVEL:
		{
			if ( pclchar->pclMarriage )
			{
				pclchar->pclMarriage->SetLoveLevel( (SI16)pclinfo->ChangeInfo.siChageAmount1 );
			}
		}
		break;

	case CHANGETYPE_TRANSFORM_HORSE:
		{
			pclchar->ChangeHorseCode( pclinfo->ChangeInfo.siChageAmount1 );
		}
		break;
	default: break;
	}

}

// ĳ������ ���� ���� ������ ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGEMAGIC(cltMsg* pclMsg, SI32 id)
{
	SI32					magickind				= pclMsg->siData32[0];
	stMagicAttributeData	*pMagicAttributeData	= pclMagicManager->GetMagicAttribute( magickind );
	if ( pMagicAttributeData )
	{
		pclCM->CR[1]->SetCurrentMagic( magickind, pMagicAttributeData->si08MagicCastType );

		if ( 0 >= magickind )
		{
			pclCM->CR[1]->m_clMagicBufMgr.Init();
		}
	}

	if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->SetActiveMagicKind( magickind );	
}

// ĳ������ �̺�Ʈ ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EventInfo* pclinfo = (cltGameMsgResponse_EventInfo*)pclMsg->cData;

	id = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(id <= 0)return ;

	pclCM->CR[id]->clInnerStatus.clEventInfo.Set(&pclinfo->clEventInfo);

	// �̺�Ʈ ������ ���� Block�缳��. 
	pclCM->CR[id]->SetBlock();

}


// Person�� �� ������ �޾Ƽ� ������Ʈ. (�̿��� �� ����) 
void cltClient::DoMsg_GAMEMSG_RESPONSE_NEIGHBOURHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NeighbourHorse* pclinfo = (cltGameMsgResponse_NeighbourHorse*)pclMsg->cData;

	SI32 varyid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(varyid <= 0)return ;
	if(varyid == 1)return ;	// ���ΰ� ĳ���Ϳ��Դ� ���޵Ǿ�� �ȵȴ�.

	if(pclCM->IsValidID(varyid))
	{
		cltHorse* pclhorse = pclCM->CR[varyid]->pclCI->clHorseInfo.GetCurrentShowHorse();

		bool bChangeHorse = false;
		if (pclhorse == NULL || pclhorse->siHorseUnique != pclinfo->siHorseUnique )
			bChangeHorse = true;

		if(pclhorse)	pclhorse->siHorseUnique	= pclinfo->siHorseUnique;
		if (bChangeHorse)
		{
			pclCM->CR[varyid]->DeleteSlave();
			pclCM->CR[varyid]->pclCI->clHorseInfo.SetHorse(pclCM->CR[varyid]->pclCI->clHorseInfo.GetCurrentShowHorseIndex(), pclhorse);
		}

		//cyj ������Ʈ�� ���������� ���� �������� ������ �� �Ⱥ��̵��� ����
		if (pclhorse == NULL || !pclhorse->siHorseUnique)
		{
			pclCM->CR[varyid]->UnrideHorse();
		}
	}
}

// 
void cltClient::DoMsg_GAMEMSG_RESPONSE_WINWARPRIZE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_WinWarPrize* pclinfo = (cltGameMsgResponse_WinWarPrize*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	TCHAR text[1024] = TEXT("");
	TCHAR buffer[256] = TEXT("");

	TCHAR* pText = NULL;

	if( true == pclinfo->bBlackWarSwitch )
	{
		TCHAR itemname[256] = TEXT("");
		if (pclinfo->siItemUnique > 0)
		{
			StringCchPrintf(itemname, 256, pclItemManager->GetName(pclinfo->siItemUnique));


			pText = GetTxtFromMgr(10027);
			StringCchPrintf( buffer, 256, pText, itemname , pclinfo->siItemNum );
			StringCchCat(text, 1024, buffer);
		}

		pText = GetTxtFromMgr(1335);
	}
	else
	{
		if(pclinfo->siGrade >= 0)
		{
			pText = GetTxtFromMgr(1331);

			StringCchPrintf(buffer, 256, pText, pclinfo->siGrade + 1);
			StringCchCat(text, 1024, buffer);
		}

		TCHAR itemname[256] = TEXT("");

		if (pclinfo->siItemUnique > 0)
		{
			StringCchPrintf(itemname, 256, pclItemManager->GetName(pclinfo->siItemUnique));

		}
		pText = GetTxtFromMgr(1332);

		StringCchPrintf(buffer, 256, pText, itemname , pclinfo->siItemNum, pclinfo->siMoney);
		StringCchCat(text, 1024, buffer);

		if(pclinfo->siFameExp)
		{
			pText = GetTxtFromMgr(1333);

			StringCchPrintf(buffer, 256, pText, pclinfo->siFameExp);
			StringCchCat(text, 1024, buffer);
		}
		//if(pclinfo->siPersonalFameExp)
		//{
		//	pText = GetTxtFromMgr(1334);

		//	StringCchPrintf(buffer, 256, pText, pclinfo->siPersonalFameExp);
		//	StringCchCat(text, 1024, buffer);
		//}

		pText = GetTxtFromMgr(1335);
	}

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, text);
}


// Ư�� �ӹ� �ϼ��Ŀ� ����� ������ �뺸����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SPECIALQUESTREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SpeicalQuestReward* pclinfo = (cltGameMsgResponse_SpeicalQuestReward*)pclMsg->cData;

	TCHAR buffer[256] =TEXT("");
	TCHAR temp[256];

	TCHAR* pText = NULL;

	if(pclinfo->clQuestRewardInfo.siExp)
	{
		pText = GetTxtFromMgr(1336);

		StringCchPrintf(temp, 256, pText, pclinfo->clQuestRewardInfo.siExp);
		StringCchCat(buffer, 256, temp);
	}

	if(pclinfo->clQuestRewardInfo.siMoney)
	{
		pText = GetTxtFromMgr(1337);

		StringCchPrintf(temp, 256, pText, pclinfo->clQuestRewardInfo.siMoney);
		StringCchCat(buffer, 256, temp);
	}
	if(pclinfo->siWord >= 0)
	{
		pText = GetTxtFromMgr(1338);

		StringCchPrintf(temp, 256, pText, pclQuestManager->szWordAssemblyString[pclinfo->siWord]);
		StringCchCat(buffer, 256, temp);
	}

	if( pclinfo->uiTriedState == cltCharCommon::TIRED_STATUS_LITTLE_TIRED )
	{
		pText = GetTxtFromMgr( 10198 );
		StringCchCat( buffer, 256, pText );
	}
	else if( pclinfo->uiTriedState == cltCharCommon::TIRED_STATUS_MUCH_TIRED )
	{
		pText = GetTxtFromMgr( 10199 );
		StringCchCat( buffer, 256, pText );
	}


	pText = GetTxtFromMgr(1339);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,	buffer);

}

// Ư�� �ӹ� �����Ǿ����� �뺸����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SPECIALQUESTMADE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SpeicalQuestMade* pclinfo = (cltGameMsgResponse_SpeicalQuestMade*)pclMsg->cData;

	// ������ ���ؼ� ȭ�鿡 ǥ���Ѵ�. 
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
	TCHAR text[256] =TEXT("");
	if(pclQuestManager->GetCurStatusText(pclchar, QUEST_TYPE_SPECIAL, &pclinfo->clSpecialQuestInfo, text, 256) == true)
	{
		// Ư�� ����Ʈ�� ��� ���� ���뵵 ���´�. 
		TCHAR szreward[256] =TEXT("");
		pclinfo->clSpecialQuestInfo.clQuestRewardInfo.GetExplainText(szreward, 256);

		TCHAR* pText = GetTxtFromMgr(1340);
		TCHAR* pText2 = GetTxtFromMgr(1433);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, pText2, text, szreward);

	}


}

// ���ֵ��̹̼��� �����Ǿ����� �˸�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_GOONZUDAYMISSION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_GoonzuDayMissionMade* pclinfo = (cltGameMsgResponse_GoonzuDayMissionMade*)pclMsg->cData;
	if ( NULL == pclinfo ) return;

	NTCHARString64		strTitle( GetTxtFromMgr(40855) );
	NTCHARString128		strText;
	NTCHARString32		strKeyword1;
	NTCHARString32		strKeyword2;

	switch( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siFlag )
	{
	case QUEST_CLEAR_COND_KILLMON:
		{
			strText = GetTxtFromMgr( 40856 );

			if ( NULL != pclKindInfoSet->GetName( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 ) )
			{
				strKeyword1 = pclKindInfoSet->GetName( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 );
			}
		}
		break;
	case QUEST_CLEAR_COND_MAKEITEM:
		{
			strText = GetTxtFromMgr( 40857 );

			if ( NULL != pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 ) )
			{
				strKeyword1 = pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 )->GetName();
			}
		}
		break;
	case QUEST_CLEAR_COND_ITEM:
		{
			strText = GetTxtFromMgr( 40859 );

			if ( NULL != pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 ) )
			{
				strKeyword1 = pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 )->GetName();
			}
		}
		break;
	case QUEST_CLEAR_COND_USEITEM:
		{
			strText = GetTxtFromMgr( 40858 );

			if ( NULL != pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 ) )
			{
				strKeyword1 = pclClient->pclItemManager->FindItemInfo( pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara1 )->GetName();
			}
		}
		break;
	}

	strText.Replace( TEXT("#name#"), strKeyword1 );
	strText.Replace( TEXT("#num#"), SI32ToString(pclinfo->clGoonzuDayMissionInfo.clQuestClearConditionInfo.siPara2) );

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText );
}

//[����] : 2010�ų��̺�Ʈ - ���� � ����� ���� �޼��� ó��
void cltClient::DoMsg_GAMEMSG_RESPONSE_FORTUNERESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_2010NewYear_FortuneResult* pRcvInfo = (cltGameMsgResponse_2010NewYear_FortuneResult*)pclMsg->cData;
	if ( NULL == pRcvInfo ) return;

	//////////////////////////////////////////////////////////////////////////

	// �������� �ƴ϶� ��� ������ ��쿣 ���ڿ��� ������ ��ȭ���ڸ� ���ش�.
	switch ( pRcvInfo->m_siFortuneQuality )
	{
	case 2:
	case 3:
		{
			if( m_pDialog[ NTREASUREBOX_DLG ] )
			{
				((CNTreasureBoxDlg*)m_pDialog[ NTREASUREBOX_DLG ])->DeleteDialog();
				//((CNTreasureBoxDlg*)m_pDialog[ NTREASUREBOX_DLG ])->StopDraw();
			}
		}
		break;
	case 100:
		{
			return;
		}
		break;
	}

	//////////////////////////////////////////////////////////////////////////

	// ��Ű ����� ���� Ŭ���� ó����

	NTCHARString256 strFortuneMessage;

	switch ( pRcvInfo->m_siFortuneQuality )
	{
	case 1:			// ���
		{
			//strFortuneMessage = GetTxtFromMgr( 9738 );		// "���"�� �־�� �ϴµ� �ؽ�Ʈ ��� �ϴ� "�ų� �"�� �־��
			strFortuneMessage += GetTxtFromMgr( pRcvInfo->m_siFortuneTextUnique );	// � ���� �ؽ�Ʈ ����ũ
		}
		break;
	case 2:			// ��
		{
			//strFortuneMessage = GetTxtFromMgr( 9738 );		// "��"�� �־�� �ϴµ� �ؽ�Ʈ ��� �ϴ� "�ų� �"�� �־��
			if ( 0 < pRcvInfo->m_siFortuneTextUnique )
			{
				strFortuneMessage += GetTxtFromMgr( pRcvInfo->m_siFortuneTextUnique );	// � ���� �ؽ�Ʈ ����ũ
			}

			NTCHARString256 strBuffMessage;
			strBuffMessage = GetTxtFromMgr( 40257 );		// "�����մϴ�. #buff#������ ȹ���ϼ̽��ϴ�."

			NTCHARString128 strBuffName;
			strBuffName = GetTxtFromMgr( pRcvInfo->m_siBuffNameUnique );		// ���� �̸� ����ũ

			strBuffMessage.Replace( TEXT("#buff#"), strBuffName );

			// ���� ������ ���� ��ȭ���� ������
			if ( NULL == m_pDialog[ NCOMMONMSG_DLG ] )
			{
				((cltClient*)pclClient)->CreateInterface( NCOMMONMSG_DLG );
			}			

			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set( COMMONDLG_2010NEWYEARFORTUNE_BUF );
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->SetText( strBuffMessage );

		}
		break;
	case 3:			// ��
		{
			//strFortuneMessage = GetTxtFromMgr( 9738 );		// "��"�� �־�� �ϴµ� �ؽ�Ʈ ��� �ϴ� "�ų� �"�� �־��
			if ( 0 < pRcvInfo->m_siFortuneTextUnique )
			{
				strFortuneMessage += GetTxtFromMgr( pRcvInfo->m_siFortuneTextUnique );	// � ���� �ؽ�Ʈ ����ũ
			}

			NTCHARString256 strQuestMessage;

			// npc ������ ���޴� ����Ʈ��..
			if ( QUEST_CLEAR_COND_CLEARQUEST == pRcvInfo->m_siQuestClearCondition )
			{
				strQuestMessage = GetTxtFromMgr(40260);			// "�̼ǳ��� [#NPCname#]�� [#Qname#] ����Ʈ �����ϱ�."

				NTCHARString128 strKeyWord1;
				NTCHARString128 strKeyWord2;

				strKeyWord1 = pclClient->pclKindInfoSet->GetName( pRcvInfo->m_siQuestPara2 );

				cltQuestInfo* pQuestInfo = pclClient->pclQuestManager->GetQuestInfo( pRcvInfo->m_siQuestPara1 );

				if ( pQuestInfo != NULL )
				{
					strKeyWord2 = pQuestInfo->szTitleText;
				}

				strQuestMessage.Replace( TEXT("#NPCname#"), strKeyWord1 );
				strQuestMessage.Replace( TEXT("#Qname#"), strKeyWord2 );

			}
			else	// ����/��� ����Ʈ��..
			{
				strQuestMessage = GetTxtFromMgr( 40259 );		// "[#name#]�� [#num#]�� [#mission#]�ؿ���."

				NTCHARString128 strKeyWord1;
				NTCHARString128 strKeyWord2;

				SI32 siMakeNum = pRcvInfo->m_siQuestPara2;

				if ( QUEST_CLEAR_COND_KILLMON == pRcvInfo->m_siQuestClearCondition )
				{
					strKeyWord2 = GetTxtFromMgr( 10089 );		// ���

					if ( NULL != pclKindInfoSet->GetName( pRcvInfo->m_siQuestPara1 ) )
					{
						strKeyWord1 = pclKindInfoSet->GetName( pRcvInfo->m_siQuestPara1 );
					}
				}
				else if ( QUEST_CLEAR_COND_MAKEITEM == pRcvInfo->m_siQuestClearCondition )
				{
					strKeyWord2 = GetTxtFromMgr( 8131 );			// '�����ϱ�'

					if ( NULL != pclClient->pclItemManager->FindItemInfo( pRcvInfo->m_siQuestPara1 ) )
					{
						strKeyWord1 = pclClient->pclItemManager->FindItemInfo( pRcvInfo->m_siQuestPara1 )->GetName();
					}
				}

				strQuestMessage.Replace( TEXT("#name#"), strKeyWord1 );
				strQuestMessage.Replace( TEXT("#num#"), SI32ToString(siMakeNum) );
				strQuestMessage.Replace( TEXT("#mission#"), strKeyWord2 );
			}

			TCHAR* pTitle = GetTxtFromMgr( 40305 );		// "�ų��̺�Ʈ �̼�"

			// ���� ����Ʈ�� ���� ��ȭ���� ������
			if ( NULL == m_pDialog[ NCOMMONMSG_DLG ] )
			{
				((cltClient*)pclClient)->CreateInterface( NCOMMONMSG_DLG );
			}

			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set( COMMONDLG_2010NEWYEARFORTUNE_QUEST );
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->SetText( strQuestMessage );
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->SetTitle( pTitle );
		}
		break;
	case 200:  // '��'������ ����� ����Ʈ�� ���� ��쿣
		{
			strFortuneMessage = GetTxtFromMgr( 40262 );  // "�����մϴ�. �̼��� �Ϸ� �ϼ̱���. �ູ�� ���� ���� ����ϴ� ���̾� ���� �ְ��� �ູ�� �� �Դϴ�."

			// ���� ������ ���� ��ȭ���� ������
			if ( NULL == m_pDialog[ NCOMMONMSG_DLG ] )
			{
				((cltClient*)pclClient)->CreateInterface( NCOMMONMSG_DLG );
			}

			TCHAR* pTitle = GetTxtFromMgr( 40261 );  // "�ų��̺�Ʈ �̼ǿϷ�"

			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set( COMMONDLG_2010NEWYEARFORTUNE_BUF );
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->SetText( strFortuneMessage );
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->SetTitle( pTitle );

			return;
		}
		break;
	}

	// ��ȭ���� Ÿ��Ʋ
	if ( 0 != pRcvInfo->m_siFortuneTextUnique )
	{
		TCHAR* pTitleText = NULL;
		pTitleText = GetTxtFromMgr( 9738 );		// "�ų� �"

		// � ��ȭ���ڰ� �����Ǿ� ���� �ʴٸ� �������ش�.
		if ( NULL == m_pDialog[ N2010NEWYEAR_FORTUNE_DLG ] )
		{
			((cltClient*)pclClient)->CreateInterface( N2010NEWYEAR_FORTUNE_DLG );
		}

		((CFortuneCookieDlg*)m_pDialog[ N2010NEWYEAR_FORTUNE_DLG ])->SetText( (TCHAR*)strFortuneMessage );
	}
}


//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_NO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HappyBeanQuestStart_NO* pclinfo = (cltGameMsgResponse_HappyBeanQuestStart_NO*)pclMsg->cData;

	TCHAR buffer[256] =TEXT("");
	TCHAR temp[256];

	TCHAR* pText = NULL;

	switch(pclinfo->siResult )
	{
	case 0 : // ����.
		pText = GetTxtFromMgr(7141); 

		StringCchPrintf(temp, 256, pText);
		StringCchCat(buffer, 256, temp);		
		break;
	case 1 : // ����Ʈ ���� �㰡�� ��������, ����Ʈ�� ����µ� �����ߴ�.(�� �� �ִ� ����Ʈ�� ����?)
		pText = GetTxtFromMgr(7159);  //�ϴ��� 

		StringCchPrintf(temp, 256, pText);
		StringCchCat(buffer, 256, temp);
		break;
	case 2 : // �Ⱓ�� ����.
		pText = GetTxtFromMgr(7160);  //�ϴ��� 

		StringCchPrintf(temp, 256, pText);
		StringCchCat(buffer, 256, temp);
		break;
	default:
		break;
	}

	pText = GetTxtFromMgr(223); //����Ʈ ���� ����.

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,	buffer);

}

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_OK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HappyBeanQuestStart_OK* pclinfo = (cltGameMsgResponse_HappyBeanQuestStart_OK*)pclMsg->cData;

	// ������ ���ؼ� ȭ�鿡 ǥ���Ѵ�. 
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
	TCHAR text[256] =TEXT("");
	if(pclQuestManager->GetCurStatusText(pclchar, QUEST_TYPE_HAPPYBEAN, &pclinfo->clHappyBeanQuestInfo, text, 256) == true)
	{
		//  ����Ʈ�� ��� ���� ���뵵 ���´�. 
		TCHAR szreward[256] =TEXT("");
		pclinfo->clHappyBeanQuestInfo.clQuestRewardInfo.GetExplainText(szreward, 256);

		TCHAR* pText = GetTxtFromMgr(7142);
		TCHAR* pText2 = GetTxtFromMgr(7143);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, pText2, text, szreward);

	}


}
//KHY - 0822 - ���Ǻ�. �Ϸ� �޽���.
void cltClient::DoMsg_GAMEMSG_RESPONSE_HAPPYBEANQUEST_REWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HappyBeanQuestReward* pclinfo = (cltGameMsgResponse_HappyBeanQuestReward*)pclMsg->cData;

	// ������ ���ؼ� ȭ�鿡 ǥ���Ѵ�. 
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];

	//  ����Ʈ�� ��� ���� ���뵵 ���´�. 
	TCHAR szreward[256] =TEXT("");
	pclinfo->clQuestRewardInfo.GetExplainText(szreward, 256);

	TCHAR* pText = GetTxtFromMgr(10152);
	TCHAR* pText2 = GetTxtFromMgr(7149);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, pText2, szreward);

}

// [����] ���ֵ��� �̼� �Ϸῡ ���� ������ �˸�
void cltClient::DoMsg_GAMEMSG_RESPONSE_GOONZUDAYMISSION_CLEARREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GoonzuDayMissionClearReward* pRcvInfo = (cltGameMsgResponse_GoonzuDayMissionClearReward*)pclMsg->cData;
	if ( NULL == pRcvInfo ) return;

	NTCHARString32 strTitle;
	NTCHARString128 strText;
	strTitle = GetTxtFromMgr(40855);

	if ( 0 < pRcvInfo->m_siItemUnique && 0 < pRcvInfo->m_siItemNum )
	{
		// �����ۿ� ���� ���� ����
		if ( 0 < pclItemManager->FindItemRefFromUnique(pRcvInfo->m_siItemUnique) )
		{
			strText = GetTxtFromMgr(14036);		// "[#item#]�� [#num#]���� �޾ҽ��ϴ�."
			strText.Replace( TEXT("#item#"), pclClient->pclItemManager->GetName( pRcvInfo->m_siItemUnique ) );
			strText.Replace( TEXT("#num#"), SI16ToString(pRcvInfo->m_siItemNum) );
		}
		else
		{
			return;		// �����ۿ� ���� ������ ��Ȯ���� �ʴٸ� �׳� �����Ѵ�.
		}
	}
	else if ( 0 < pRcvInfo->m_siExp )
	{
		// ����ġ�� ���� ���� ����
		strText = GetTxtFromMgr(40860);
		strText.Replace( TEXT("#exp#"), SI32ToString(pRcvInfo->m_siExp) );
	}
 
	m_pDialog[ NOTIFYMSG_DLG ]->SetText( strTitle, strText );
}

//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENTCOUPON(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EventCoupon* pclinfo = (cltGameMsgResponse_EventCoupon*)pclMsg->cData;

	if(pclinfo->siEventCouponType == GAMEROOM_COUPON_EVENT)
	{
		if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
		{
			CreateInterface( NCOMMONMSG_DLG );
		}
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_EVENTCOUPON);
	}

	//���� ���� �̺�Ʈ [2007.09.10 �ռ���]
	if(pclinfo->siEventCouponType == AUCTION_COUPON_EVENT)
	{

		if(m_pDialog[ NAUCTIONEVENT_DLG ]==NULL)
		{
			CreateInterface( NAUCTIONEVENT_DLG );
		}
		if(pclinfo->siResult == 1){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_1000WON);
			m_siSucceedEventType +=1;
		}
		if(pclinfo->siResult == 2){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_3000WON);
			m_siSucceedEventType +=2;
		}
		if(pclinfo->siResult == 3){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_5000WON);
			m_siSucceedEventType +=3;
		}
		if(pclinfo->siResult == 4){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_50POINT);
			m_siSucceedEventType +=4;
		}

		if(pclinfo->siResult == 5){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_100POINT);
			m_siSucceedEventType +=5;
		}
		if(pclinfo->siResult == 6){
			CreateInterface( NAUCTIONEVENT_DLG );
			((CNAuctionEventDlg*)m_pDialog[NAUCTIONEVENT_DLG])->SetCoupon(AUCTION_EVENT_COUPON_500POINT);
			m_siSucceedEventType +=6;
		}
	}

	// ����, ��Ŀ �̺�Ʈ - 2007.09.14
	if(pclinfo->siEventCouponType == GOSTOP_POKER_EVENT)
	{
		if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
		{
			CreateInterface( NCOMMONMSG_DLG );
		}
		if(pclinfo->siResult == 1)	// ��Ŀ�϶�
		{
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_GOSTOPPOCKERCOMPLETE);
			m_siGoStopPockerEventType +=1;
		}
		if(pclinfo->siResult == 2)	// �����϶�
		{
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_GOSTOPPOCKERCOMPLETE);
			m_siGoStopPockerEventType +=2;
		}	
	}

	//KHY - 1024 - �Ѱ��� VIP �̺�Ʈ
	if(pclinfo->siEventCouponType == HAN_GAME_VIP_EVENT)
	{
		if(m_pDialog[ NCOMMONMSG_DLG ]==NULL) // VIP ����Ʈ ���޼���.
		{
			CreateInterface( NCOMMONMSG_DLG );
		}
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_HANGAME_VIP_EVENT);
	}

	//KHY - 1025 - ������ �̺�Ʈ
	if(pclinfo->siEventCouponType == NOW_COM_EVENT)
	{

		if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
		{
			CreateInterface( NCOMMONMSG_DLG );
		}

		switch(pclinfo->siResult )
		{
		case 1: //���� ����. - ����.
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_NOWCOM_EVENT_COUPON);
			break;
		case 2: // 10���޼�.
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_NOWCOM_EVENT_10LEVEL);
			break;
		case 3: // ���ڵǱ�.
			((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_NOWCOM_EVENT_HAVEFATHER);
			break;			
		}

		if(pclinfo->siResult >0)
			m_siSucceedEventType =1;

	}
}

// ������ ���ؼ� ȭ�鿡 ǥ���Ѵ�. 
//cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
//((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->SetWarpMoney(siMapindex ,WarpMoney());
//  ����Ʈ�� ��� ���� ���뵵 ���´�. 
//TCHAR szreward[256] =TEXT("");
//pclinfo->clQuestRewardInfo.GetExplainText(szreward, 256);		
//TCHAR* pText = GetTxtFromMgr(10152);
//TCHAR* pText2 = GetTxtFromMgr(7149);	
//m_pDialog[ NMSGBOX_DLG ]->SetText( pText);

//�����̺�Ʈ�� ���.[2007.09.10 �ռ���]
//void cltClient::DoMsg_GAMEMSG_RESPONSE_AUCTIONEVENTCOUPON(cltMsg* pclMsg, SI32 id)
//{
//	cltGameMsgResponse_EventCoupon* pclinfo = (cltGameMsgResponse_EventCoupon*)pclMsg->cData;
//
//	if(pclinfo->siEventCouponType == AUCTION_CUPON_EVENT)
//	{
//		if(m_pDialog[ NAUCTIONEVENT_DLG ]==NULL)
//		{
//			CreateInterface( NAUCTIONEVENT_DLG );
//		}
//		((CNCommonMsgDlg*)m_pDialog[ NAUCTIONEVENT_DLG ])->Set(COMMONDLG_AUCTIONEVENTCOUPON);
//	}
//}



// Ư�� ������ ����Ʈ ������ ���´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_QUESTUSERINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_QuestuserInfo* pclinfo = (cltGameMsgResponse_QuestuserInfo*)pclMsg->cData;

	TCHAR buffer[1024] =TEXT("");

	// ����Ʈ�� ���� ��Ȳ�� �ؽ�Ʈ�� ���´�. 
	pclQuestManager->GetQuestProgressText(pclinfo->siQuestType,  &pclinfo->clQuestInfo, buffer, 1024);

	TCHAR* pText = GetTxtFromMgr(1341);

	g_ErrorMsg.BigSet( pText, buffer);	

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETPERSONNAMINGINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetPersonNamingInfo* pclinfo = ( cltGameMsgResponse_SetPersonNamingInfo*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clPersonNaming.m_siLevel[pclinfo->siIndex] = pclinfo->siLevel;

	pclCM->CR[1]->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].Init();

	// naming - TODO : ������ ���� �˷�����..

	TCHAR* pTitle = GetTxtFromMgr(10152);
	TCHAR* pText = GetTxtFromMgr(10153);

	cltNamingQuestUnit* pclunit = pclNamingQuestManager->GetQuestInfo( pclinfo->siIndex, pclinfo->siLevel );
	if( pclunit )
	{
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclunit->GetNaming() );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETPPERSONCURRENTNAMING(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_SetPersonCurrentNaming* pclinfo = ( cltGameMsgResponse_SetPersonCurrentNaming* )pclMsg->cData;

	SI32 charid		= cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsAlive(charid) == false)return ;

	cltCharClient* pclchar = (cltCharClient* )pclCM->CR[charid];
	if( NULL == pclchar ) return;

	pclchar->pclCI->clPersonNaming.m_siSelectedIndex = pclinfo->siIndex;
	pclchar->pclCI->clPersonNaming.m_siSelectedLevel = pclinfo->siLevel;

}

// �� �̸� �����ϱ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_HORSENAMECHANGE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HorseNameChange* pclinfo = (cltGameMsgResponse_HorseNameChange*)pclMsg->cData;

	TCHAR* pTitle = GetTxtFromMgr(569);
	TCHAR* pText = GetTxtFromMgr(1342);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->strHorseName );

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if( m_pDialog[ CLTNCHARSTATUS_DLG ] )
	{		
		cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetHorse(pclinfo->siHorseIndex);
		if(pclhorse)	MStrCpy( pclhorse->szName, pclinfo->strHorseName, MAX_HORSE_NAME );

		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->m_bChangedInitHorseStatus = TRUE;

		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->InitHorseStatusInfo();

		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->UpdateHorseStatusInfo();
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CLEAR_SPECIALWORD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Clear_SpecialWord* pclinfo = (cltGameMsgResponse_Clear_SpecialWord*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clQuestInfo.siClearWordSpecialQuest = pclinfo->siClearSpecialWord ;
	pclCM->CR[1]->pclCI->clQuestInfo.siEventClearWordSpecialQuest	=	pclinfo->siEventClearSpecialWord;		// �̺�Ʈ�� �ۼ� üũ.
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIZE_GAMEEVENT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Prize_GameEvent* pclinfo = (cltGameMsgResponse_Prize_GameEvent*)pclMsg->cData;

	stBobusang Data;
	Data.siType = 0 ;
	Data.bGameEvent = pclinfo->bGameEvent ;
	Data.bNewAccount = pclinfo->bNewAccount ;
	Data.bWinPrize = pclinfo->bWinPrize ;

	if ( m_pDialog[NBOBUSANG_DLG] )
		m_pDialog[NBOBUSANG_DLG]->SetData(&Data);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GET_WEAPONSKILLCOST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Get_WeaponSkillCost* pclinfo = (cltGameMsgResponse_Get_WeaponSkillCost*)pclMsg->cData;

	if ( m_pDialog[NHONGGILDONG_DLG] )
	{
		stHongGilDongData Data;
		Data.Type			= HONGGILDONG_SETDATATYPE_GETCOSTINFO ;
		Data.CostMoney		= pclinfo->siMoney ;
		Data.SkillLevel		= pclinfo->siSkillLevel ;
		Data.SkillUnique	= pclinfo->siSkillUnique ;

		m_pDialog[NHONGGILDONG_DLG]->SetData(&Data);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SET_WEAPONSKILL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Set_WeaponSkill* pclinfo = (cltGameMsgResponse_Set_WeaponSkill*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	SI16 siItemPos = pclinfo->siItemPos;
	if ( (PERSONITEM_INV0 <= siItemPos) && (MAX_ITEM_PER_PERSON > siItemPos) )
	{
		pclchar->pclCI->clCharItem.clItem[siItemPos].Set( &pclinfo->clLeftItem );
	}

	if ( m_pDialog[NHONGGILDONG_DLG] )
	{
		if ( pclinfo->siResult )
		{
			stHongGilDongData Data;
			Data.Type			= HONGGILDONG_SETDATATYPE_SUCCESSSKILLUP ;
			Data.Result			= pclinfo->siResult ;
			Data.SkillLevel		= pclinfo->siSkillLevel ;
			Data.SkillUnique	= pclinfo->siSkillUnique ;

			m_pDialog[NHONGGILDONG_DLG]->SetData(&Data);
		}
	}
}

/*void cltClient::DoMsg_GAMEMSG_RESPONSE_COUNTATTACK_INFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_CountAttack_Info* pclinfo = (cltGameMsgResponse_CountAttack_Info*)pclMsg->cData ;

	if ( pclinfo->siItemPos )
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clFlagitem);

	if ( m_pDialog[NBOBUSANG_DLG] )
	{
		stBobusang Data;
		Data.siType = 1 ;
		Data.clitem.Set(&pclinfo->clitem);
		Data.siFlagNum = pclinfo->siFlagNum ;

		m_pDialog[NBOBUSANG_DLG]->SetData(&Data);
	}
}*/

void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENTNPC(cltMsg* pclMsg, SI32 id)
{
	/*	SI08 type = (SI08)pclMsg->cData[0] ;

	if( type == 1)	// �̹� �����ߴ�
	{
		((CNEventDlg*)m_pDialog[ NEVENT_DLG ])->SetEventText(TEXT("����, �̹� �̺�Ʈ�� �����߱���... �� ��÷�Ǳ� ���ڳ�."));
	}
	else if( type == 0)		// ���� �����ߴ�
		((CNEventDlg*)m_pDialog[ NEVENT_DLG ])->SetEventText(TEXT("�̺�Ʈ�� ����Ǿ���. �׷� ���ֿ¶��� ��հ� ���Գ�."));
	*/
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETGREETING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetGreeting* pclinfo = (cltGameMsgResponse_GetGreeting*)pclMsg->cData;

	if( pclinfo->siParam == 0 )
	{
		if( m_pDialog[ CLTNCHARGREETINGCHANGE_DLG ] )
			((cltNCharGreetingChange*) m_pDialog[ CLTNCHARGREETINGCHANGE_DLG ])->SetGreetingText(pclinfo->szGreeting);

		StringCchCopy(pclCM->CR[id]->pclCI->clBI.szGreeting, sizeof(pclCM->CR[id]->pclCI->clBI.szGreeting), pclinfo->szGreeting);
	}
	else if( pclinfo->siParam == 1 )
	{
		if( m_pDialog[ NMASTERINFO_DLG ] )
			((CNMasterInfo*) m_pDialog[ NMASTERINFO_DLG ])->SetGreetingText( pclinfo->szName, pclinfo->szGreeting);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONNAME_SERIALID(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetNameFromItemSerialID* pclinfo = (cltGameMsgResponse_GetNameFromItemSerialID*)pclMsg->cData;

	if( pclinfo->siSerialID > 0 && pclinfo->szPlayerName != NULL )
	{
		cltPersonNameInfo clPersonInfo;
		if( false == pclNewPersonNameManager->Find( pclinfo->siSerialID, &clPersonInfo ) )
		{
			clPersonInfo.siServerUnique = pclinfo->siServerUnique;
			StringCchCopy( clPersonInfo.szPersonName, sizeof(clPersonInfo.szPersonName), pclinfo->szPlayerName );

			pclNewPersonNameManager->Insert( pclinfo->siSerialID, &clPersonInfo );
		}
	}

	cltClient* pclclient = (cltClient*) pclClient;

	if( pclclient->m_pDialog[ NNEWINVENTORY_DLG ] != NULL )
	{
		((CNNewInventory*)pclclient->m_pDialog[ NNEWINVENTORY_DLG ])->LoadItemData();
	}

	if( pclclient->m_pDialog[ NPERSONALSHOP_DLG ] != NULL )
	{
		((CNPersonalShopDlg*)pclclient->m_pDialog[ NPERSONALSHOP_DLG ])->RefreshSelectedItem();
	}

	if( pclclient->m_pDialog[ NNEWMARKET_DLG ] != NULL )
	{
		((NNewMarketUserSellDlg*)((NNewMarketDlg*)m_pDialog[ NNEWMARKET_DLG ])->m_pUserChildDlg[0])->SetMyInventory();
	}

	if( pclclient->m_pDialog[ NNEWMARKET_SUB_DLG ] != NULL )
	{
		((NNewMarketUserBuyDlgSub*)pclclient->m_pDialog[ NNEWMARKET_SUB_DLG ])->RefreshItemExpalan();
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONNAME_FROMPERSONID(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetNameFromPersonID* pclinfo = (cltGameMsgResponse_GetNameFromPersonID*)pclMsg->cData;

	TCHAR buf[MAX_PLAYER_NAME];
	if( pclinfo->siPersonID > 0 && pclinfo->szPlayerName != NULL )
	{
		if (pclPersonNameManager->Find(pclinfo->siPersonID, buf) == false)
		{
			StringCchCopy(buf, MAX_PLAYER_NAME, pclinfo->szPlayerName);

			pclPersonNameManager->Insert(pclinfo->siPersonID, buf);
		}
	}

	cltClient* pclclient = (cltClient*) pclClient;

	if( pclclient->m_pDialog[ NMARKET_DLG ] != NULL && pclclient->m_pDialog[ NMARKET_DLG ]->IsCreate() == true 
		&& ((NMarketUserBuyDlg*)((NMarketDlg*)pclclient->m_pDialog[ NMARKET_DLG ])->m_pUserChildDlg[1]) != NULL )
	{
		((NMarketUserBuyDlg*)((NMarketDlg*)pclclient->m_pDialog[ NMARKET_DLG ])->m_pUserChildDlg[1])->bMakerSwitch = true;
	}
	if( pclclient->m_pDialog[ NMARKET_SUB_DLG ] != NULL && pclclient->m_pDialog[ NMARKET_SUB_DLG ]->IsCreate() == true )
	{
		((NMarketUserBuyDlgSub*)pclclient->m_pDialog[ NMARKET_SUB_DLG ])->bMakerSwitch = true;
	}
	if( pclclient->m_pDialog[ NNEWINVENTORY_DLG ] != NULL )
	{
		((CNNewInventory*)pclclient->m_pDialog[ NNEWINVENTORY_DLG ])->LoadItemData();
	}

	if( pclclient->m_pDialog[ NPERSONALSHOP_DLG ] != NULL )
	{
		((CNPersonalShopDlg*)pclclient->m_pDialog[ NPERSONALSHOP_DLG ])->RefreshSelectedItem();
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RIGHTMOUSE_USERLIST_NAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetName* pclinfo = (cltGameMsgResponse_GetName*)pclMsg->cData;
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		// �̸��� �ִ´�. 
		pclCM->CR[charid]->SetName(pclinfo->szName);
	}

	((NRightMouseUserListDlg*)m_pDialog[NRIGHTMOUSEUSERLIST_DLG])->SetUserName(charid,pclinfo->szName);    

	((NRightMouseUserListDlg*)m_pDialog[NRIGHTMOUSEUSERLIST_DLG])->SetUnderUserList(false);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TIRED_STATUS(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_TiredStateNotice* pclinfo = (cltGameMsgResponse_TiredStateNotice*)pclMsg->cData;

#ifdef _DEBUG
	uiTiredState = cltCharCommon::TIRED_STATUS_LITTLE_TIRED;
#else
	// ���������� �����Ѵ�.
	uiTiredState = pclinfo->uiTiredState;

	// default �� ��� ���´�.  pclinfo->siTiredTimeNotice = 0
	TCHAR* pTitle = GetTxtFromMgr( 30305 );
	NTCHARString512	pMsg(GetTxtFromMgr(30306));

	// �ð��� ���� �������� ��� �˸���..
	switch(pclinfo->siTiredTimeNotice)
	{
	case cltCharCommon::TIRED_NOTICE_1_HOUR:
		pMsg = GetTxtFromMgr(30306);
		break;
	case cltCharCommon::TIRED_NOTICE_2_HOUR:
		pMsg = GetTxtFromMgr(30307);
		break;
	case cltCharCommon::TIRED_NOTICE_2_5_HOUR:
		pMsg = GetTxtFromMgr(30308);
		break;
	case cltCharCommon::TIRED_NOTICE_3_HOUR:
		pMsg = GetTxtFromMgr(30309);
		break;
	case cltCharCommon::TIRED_NOTICE_3_5_HOUR:
		pMsg = GetTxtFromMgr(30310);
		break;
	case cltCharCommon::TIRED_NOTICE_4_HOUR:
		pMsg  = GetTxtFromMgr(30311);
		break;
	case cltCharCommon::TIRED_NOTICE_4_5_HOUR:
		pMsg = GetTxtFromMgr(30312);
		break;
	case cltCharCommon::TIRED_NOTICE_5_HOUR:
		pMsg = GetTxtFromMgr(30313);
		break;
	case cltCharCommon::TIRED_NOTICE_5_OVER_HOUR:
		pMsg = GetTxtFromMgr(30314);
		break;
	default:
		break;
	}

	pMsg.Replace("#charname#", pclinfo->m_kCharName);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pMsg );

	/*
	uiTiredState = pclMsg->siData32[0];

	if ( uiTiredState == cltCharCommon::TIRED_STATUS_LITTLE_TIRED )
	{
		TCHAR* pTitle = GetTxtFromMgr( 10080 );
		TCHAR* pText = GetTxtFromMgr( 10082 );

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
	}
	else if ( uiTiredState == cltCharCommon::TIRED_STATUS_MUCH_TIRED )
	{
		TCHAR* pTitle = GetTxtFromMgr( 10080 );
		TCHAR* pText = GetTxtFromMgr( 10083 );

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
	}
	*/
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_COUNTRYINFO( cltMsg* pclMsg, SI32 id )
{
	if ( siServiceArea != ConstServiceArea_English
		&& siServiceArea != ConstServiceArea_NHNChina 
		&& siServiceArea != ConstServiceArea_Japan 
		&& siServiceArea != ConstServiceArea_EUROPE
		)
	{
		return;
	}

	cltGameMsgResponse_CountryInfo* pclinfo = (cltGameMsgResponse_CountryInfo*)pclMsg->cData;
	pclCM->CR[1]->pclCI->clBI.siCountryID = pclinfo->siCountryID;
	pclCM->CR[1]->pclCI->clBI.bShowCountry = pclinfo->bShowCountry;

	if( pclinfo->siCountryID == -1 )
	{
		if( m_pDialog[NSETCOUNTRY_DLG] == NULL )
		{
			CreateInterface( NSETCOUNTRY_DLG );
		}
	}

	// �޼����� �ʱ�ȭ �Ѵ�.( �α��ν� )
	// �����϶��� �α��� ó�� �ϹǷ�.. �̸� �ű�..
	pclMessage->init();
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_USERLISTBYCOUNTRY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UserListByCounty* pclinfo = (cltGameMsgResponse_UserListByCounty*)pclMsg->cData;
	if( m_pDialog[NUSERLISTBYCOUNTRY_DLG] )
	{
		// ���̾�α� ���尪 �ʱ�ȭ~
		((CNUserListByCountryDlg*)m_pDialog[NUSERLISTBYCOUNTRY_DLG])->m_pListUser->Clear();
		for ( SI32 i = 0 ; i<MAX_USERLIST_NUM ; i++ )
		{
			((CNUserListByCountryDlg*)m_pDialog[NUSERLISTBYCOUNTRY_DLG])->siPersonID[i] = 0;
		}


		TCHAR charname[MAX_USERLIST_NUM][MAX_PLAYER_NAME];
		TCHAR Villagename[MAX_USERLIST_NUM][32];

		memcpy( charname, pclinfo->szCharName, MAX_USERLIST_NUM * MAX_PLAYER_NAME * sizeof(TCHAR) );
		memcpy( Villagename, pclinfo->szVillageName, MAX_USERLIST_NUM * 32 * sizeof(TCHAR) );

		SI32 listcount = 0;

		for( SI32 i=0; i<MAX_USERLIST_NUM ; i++ )
		{
			if( _tcscmp( pclinfo->szCharName[i] , TEXT("") ) == 0 ) continue;

			stListBoxItemData listitem;
			listitem.Set( 0, charname[i] );
			TCHAR buffer[16] = TEXT("");
			StringCchPrintf( buffer, 16, TEXT("%d"), pclinfo->siCharLevel[i] );
			listitem.Set( 1, buffer );
			listitem.Set( 2, Villagename[i]);
			((CNUserListByCountryDlg*)m_pDialog[NUSERLISTBYCOUNTRY_DLG])->m_pListUser->AddItem( &listitem );
			((CNUserListByCountryDlg*)m_pDialog[NUSERLISTBYCOUNTRY_DLG])->siPersonID[listcount] = pclinfo->siPersonId[i];
			listcount++;
		}
		((CNUserListByCountryDlg*)m_pDialog[NUSERLISTBYCOUNTRY_DLG])->m_pListUser->Refresh();
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_LOWLEVELLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LowLevelList* pclinfo = (cltGameMsgResponse_LowLevelList*)pclMsg->cData;

	int a  = pclinfo->clLowLevelList[0].siLevel;
	for(SI32 i = 0;i < MAX_LOWLEVEL_LIST_IN_CLIENT_NUMBER;i++)
	{
		if ( m_pDialog[NLOWLEVEL_DLG] != NULL )
		{
			((CNLowLevelDlg*)m_pDialog[ NLOWLEVEL_DLG ])->clLowLevelList[i].Set(&pclinfo->clLowLevelList[i]);
		}
	}

	if( m_pDialog[NLOWLEVEL_DLG] != NULL )
	{
		((CNLowLevelDlg*)m_pDialog[ NLOWLEVEL_DLG ])->m_bUpdateLowLevelListSwitch = true;
	}
	/*
	for(SI32 i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(g_SoundOnOffDlg.m_bFullScreenMode)
		{
			((CNChildDlg*)m_pDialog[ NCHILD_DLG ])->clApplyerList[i].Set(&pclinfo->clApplyerList[i]);
		}
		else
			pclFatherManager->clApplyerList[i].Set(&pclinfo->clApplyerList[i]);
	}

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		((CNChildDlg*)m_pDialog[ NCHILD_DLG ])->m_bUpdateFatherApplyerListSwitch = true;
	}
	else
		pclFatherManager->bUpdateFatherApplyerListSwitch = true;
	*/
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_ADDBUF(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AddBuf* pclinfo = (cltGameMsgResponse_AddBuf*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique) );
	if( NULL == pclChar ) return;

	pclChar->pclCI->clBI.clBufInfo.AddBuf( pclinfo->m_siIndex, pclinfo->m_stBuf );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DELETEBUF( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_DeleteBuf* pclinfo = (cltGameMsgResponse_DeleteBuf*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique) );
	if( NULL == pclChar ) return;

	pclChar->pclCI->clBI.clBufInfo.DeleteBuf( pclinfo->m_siIndex );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETTEACHERPOINT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_SetTeacherPoint* pclinfo = (cltGameMsgResponse_SetTeacherPoint*)pclMsg->cData;

	//	pclCM->CR[1]->pclCI->clBI.clFatherInfo.SetTeacherPoint( pclinfo->GetTotalTeacherPoint() );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MYPUCHIKOMIURL( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_MyPuchikomiURL * pclinfo = (cltGameMsgResponse_MyPuchikomiURL*)pclMsg->cData;

	TCHAR FullURL[1024] = {'\0', };

	StringCchPrintf(FullURL,1024,
		"https://www.puchikomi.jp/kunshuToPuchikomi.php?%s"
		, pclinfo->szMyPuchikomiURL );

	//======================================================
	// ���ӳ� â
	g_LoginNoticeDlg.Set( FullURL, 850, 600 );
	//======================================================
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_USERPUCHIKOMIURL( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_UserPuchikomiURL * pclinfo = (cltGameMsgResponse_UserPuchikomiURL*)pclMsg->cData;

	TCHAR FullURL[1024] = {'\0', };

	StringCchPrintf(FullURL,1024,
		"https://www.puchikomi.jp/kunshuToPuchikomi.php?%s"
		, pclinfo->szUserPuchikomiURL );

	//======================================================
	// ���ӳ� â
	g_LoginNoticeDlg.Set( FullURL, 850, 600 );
	//======================================================

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETEMOTICON(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_SetEmoticon* pclinfo = (cltGameMsgResponse_SetEmoticon*)pclMsg->cData;

	SI32 charid		= cltCharCommon::CharUniqueInfo[pclinfo->m_siCharUnique];
	if(pclCM->IsAlive(charid) == false)return ;

	cltCharClient* pclchar = (cltCharClient* )pclCM->CR[charid];

	pclchar->SetEmoticon( pclinfo->m_siIndex );
}

// [����] �⼮üũ â�� �⼮���� ������ ������.
void cltClient::DoMsg_GAMEMSG_RESPONSE_DEMANDATTEND( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_DemandAttend* pclInfo = (cltGameMsgResponse_DemandAttend*)pclMsg->cData;
	if ( pclInfo == NULL )	return;

	//-------------------------------------------------------------
	//	���� �⼮üũ ����â�� ���� ����
	//-------------------------------------------------------------

	// �⼮üũ â�� �����Ѵ�
	if ( m_pDialog[ATTENDNOTICE_DLG] == NULL )
	{
		CreateInterface( ATTENDNOTICE_DLG );
	}
	// ����������� �������� �ʿ��� ������� �����Ѵ�(���� -1�϶��� �������� �ʴ´�)
	((CNAttendNoticeDlg*)m_pDialog[ATTENDNOTICE_DLG])->SetInfo( pclInfo->m_siAttendanceDay, pclInfo->m_siNextRewardDay );

	// �������� ������ ����� ���������� �����Ѵ�	
	((CNAttendNoticeDlg*)m_pDialog[ATTENDNOTICE_DLG])->Show( pclInfo->m_bShowDialog );


	//-------------------------------------------------------------
	//	�� �⼮üũ ����â�� ���� ����
	//-------------------------------------------------------------
	if ( m_pDialog[NATTENDCHECK_DLG] == NULL )
	{
		CreateInterface( NATTENDCHECK_DLG );
	}
	((CNAttendCheckDlg*)m_pDialog[NATTENDCHECK_DLG])->SetAttendDay( pclInfo->m_siAttendanceDay );

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ATTEND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Attend* pclinfo = (cltGameMsgResponse_Attend*)pclMsg->cData;
	if ( pclinfo == NULL ) return;


	switch ( pclinfo->siType ) 
	{
	case ATTEND_EVENTTYPE_ATTENDANCE:
		{
			if ( m_pDialog[NATTENDCHECK_DLG] == NULL )
			{
				CreateInterface( NATTENDCHECK_DLG );
			}

			CNAttendCheckDlg* pDialog = (CNAttendCheckDlg*)m_pDialog[NATTENDCHECK_DLG];
			pDialog->SetAttendDay( pclinfo->siAttendanceDay );

		}
		break;

	default:
		return;
	}
}

void cltClient::DoMSg_GAMEMSG_RESPONSE_GAME_GUARD_AUTH(cltMsg* pclMsg , SI32 id )
{

#ifdef USE_GAME_GUARD_CLIENT

	cltGameMsgResponse_GameGuardAuth * pclinfo = (cltGameMsgResponse_GameGuardAuth*)pclMsg->cData;

	if( pNpgl )
	{
		DWORD dwResult = pNpgl->Auth2(&pclinfo->ggData);
		//pclClient->pclLog->FilePrint("config\\nProtectLog.txt","pNpgl->Auth2(&pclinfo->ggData) - Ret:%d", dwResult );
	}

#endif
}

//[�߰� : Ȳ���� 2007. 12. 11 => �ų� ��ư �߿��� �޽��� ó��.]
void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWYEAR_BTN(cltMsg* pclMsg, SI32 id)
{
	// �⼮üũ â �����ش�.
	CreateInterface( NNEWYEAR_DLG );
}

//KHY - 1220 - ���Žý���.
void cltClient::DoMsg_GAMEMSG_RESPONSE_TRANSFORM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetTransForm* pclinfo = (cltGameMsgResponse_SetTransForm*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)				return;
	cltCharClient* pclchar = (cltCharClient* )pclCM->CR[id];
	if(pclchar == NULL)								return;

	// ���Ű� ���õ� �����ʹ� cltCharMakeInfo �� ���޵ȴ�.
	//pclchar->clTransFormInfo.Set( &pclinfo->clTransFormInfo );

	for (SI32 i=0; i<MAX_TRANSFORM_CHAR; i++)
		pclchar->clTransFormInfo.clTransForm[i].Set(&pclinfo->clTransFormInfo.clTransForm[i]);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_TimeMeterRate_Update* pclinfo = (cltGameResponse_TimeMeterRate_Update*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)				return;
	cltCharClient* pclchar = (cltCharClient* )pclCM->CR[id];
	if(pclchar == NULL)								return;

	if(pclCM->CR[1]->GetCharUnique() != pclchar->GetCharUnique())		return;

	cltTimeMeterRate* pclTimeMeterRate = pclchar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate( pclinfo->clTimeMeterRate.siTimeMeterRateType );
	if(pclTimeMeterRate)
	{
		pclTimeMeterRate->Set( &pclinfo->clTimeMeterRate );
	}	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MAXSYNCRO_ATTAINMENT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MaxSyncro_Attainment* pclinfo = (cltGameMsgResponse_MaxSyncro_Attainment*)pclMsg->cData;

	if(m_pDialog[NRAREITEM_DLG ] == NULL)
		CreateInterface( NRAREITEM_DLG );	

	NTCHARString256	kMsg(GetTxtFromMgr(7796));
	NTCHARString64  kTransformCharName;
	NTCHARString64  kTitle(GetTxtFromMgr(5614));

	kTransformCharName = pclClient->pclKindInfoSet->pclKI[pclinfo->m_uiCharKind]->GetName();

	kMsg.Replace("#charname#", pclinfo->m_kCharName);
	kMsg.Replace("#transform#", kTransformCharName);

	((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set( &pclinfo->m_clItem, pclinfo->m_kCharName, kTitle, kMsg );		
}

//[�߰� : Ȳ���� 2008. 1. 9 => ������ �ð��� 30�ʰ� �ȵǼ� ���� ���� �޽��� ����.]	
void cltClient::DoMsg_GAMEMSG_RESPONSE_TRANSFORM_LIMIT_TIME(cltMsg* pclMsg, SI32 id)
{
	TCHAR* pTitle = GetTxtFromMgr(5614);
	TCHAR* pText  = GetTxtFromMgr(7778);
	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	return;	
}

//[�߰� : Ȳ���� 2008. 1. 9 => ���� �������� 0�̾ ���¸���� ���� �޽��� ����.]	
void cltClient::DoMsg_GAMEMSG_RESPONSE_CREATEBANKACCOUNT_CANCEL(cltMsg* pclMsg, SI32 id)
{
	TCHAR* pTitle = GetTxtFromMgr(5614);
	TCHAR* pText  = GetTxtFromMgr(7824);
	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	return;	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HEALTH_CHANGE( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_Health_Change* pclinfo = (cltGameResponse_Health_Change*)pclMsg->cData;

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[1];

	pclChar->pclCI->clHealthInfo.siHungry	 = pclinfo->m_siHungry;
	pclChar->pclCI->clHealthInfo.siInnerOrg1 = pclinfo->m_siInnerOrg1;
	pclChar->pclCI->clHealthInfo.siInnerOrg2 = pclinfo->m_siInnerOrg2;
	pclChar->pclCI->clHealthInfo.siInnerOrg3 = pclinfo->m_siInnerOrg3;
	pclChar->pclCI->clHealthInfo.siInnerOrg4 = pclinfo->m_siInnerOrg4;
}

// [����] ������ ���� �̺�Ʈ �����귿 ������ Ŭ�� ó��. => 2008-6-10
void cltClient::DoMsg_GAMEMSG_RESPONSE_BUFF_ROULETTE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Buff_Roulette* pclinfo = (cltGameMsgResponse_Buff_Roulette*)pclMsg->cData;

	SI32 siID = pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique);

	if(false == pclCM->IsValidID(siID))
		return;

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[siID];

	pclChar->bBuffRouletteSwitch = pclinfo->m_bAction;

	if(1 != siID)
		return;  

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[ NBUFF_ROULETTE_DLG ] == NULL)	
		return;


	((CNBuffRoulette*)pclclient->m_pDialog[ NBUFF_ROULETTE_DLG ])->SetCompleteBuff(pclinfo->m_bAction, pclinfo->m_CompleteBuffKind);
}


//	[��ȣ_BALLENCECURRENCY] ��ȭ�� ���� Server -> Client
void cltClient::DoMsg_GAMEMSG_RESPONSE_BALANCECURRENCY_BUFF( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_BalanceCurrency_Buff* pclinfo = (cltGameMsgResponse_BalanceCurrency_Buff*)pclMsg->cData;

	SI32 siID = pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique);

	if(false == pclCM->IsValidID(siID))
		return;

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[siID];

	pclChar->bBuffRouletteSwitch = pclinfo->m_bAction;

	if(1 != siID)
		return;  

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[ NBALANCECURRENCY_DLG ] == NULL)	
		return;


	((CNBalanceCurrencyDlg*)pclclient->m_pDialog[ NBALANCECURRENCY_DLG ])->SetCompleteBuff(pclinfo->m_bAction, pclinfo->m_CompleteBuffKind);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SET_HOMEPAGE_URL( cltMsg* pclMsg, SI32 id )
{
	//cltGameMsgResponse_SetHomepage_URL* pclinfo = (cltGameMsgResponse_SetHomepage_URL*)pclMsg->cData;


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GET_HOMEPAGE_URL( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_GetHomepage_URL* pclinfo = (cltGameMsgResponse_GetHomepage_URL*)pclMsg->cData;

	if( _tcslen(pclinfo->szHomepageURL) > 0 )
		ShellExecute( NULL, NULL, pclinfo->szHomepageURL, NULL, NULL, SW_SHOWNORMAL ); 

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MISSIONQUEST_START(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	cltGameMsgResponse_MissionQuest_Start* pclinfo = (cltGameMsgResponse_MissionQuest_Start*)pclMsg->cData;

	// ĳ���� Ȯ��
	if(pclCM->IsValidID(id) == false)												return;
	cltCharClient* pclchar = pclCM->GetCharClient(id);		if(pclchar == NULL)		return;

	pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Set(&pclinfo->m_clMissionQuestInfo);

	if( pclinfo->m_clMissionQuestInfo.siUnique == MISSIONQUEST_UNIQUE_HOLLOWEEN )
	{
		// �޽��� â ����
		if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)
		{
			pclclient->CreateInterface( NCOMMONMSG_DLG );
		}
		((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_HALLOWEENMISSION_START);

		NTCHARString<128>	kText;

		if( pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siFlag == QUEST_CLEAR_COND_KILLMON )
		{
			kText = GetTxtFromMgr(8875);//"[#charname#]��(��) #number#���� ����ؿ���";
			NTCHARString<128>	kName;
			if(pclClient->pclKindInfoSet->IsValidKind(pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siPara1))
			{
				kName = pclClient->pclKindInfoSet->pclKI[pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siPara1]->GetName();
			}

			kText.Replace("#monname#", kName);
			kText.Replace("#num#", SI32ToString(pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siPara2));
		}
		else if (pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siFlag == QUEST_CLEAR_COND_MAKEITEM )
		{
			kText = GetTxtFromMgr(8876);//"[#itemname#]��(��) #number#�� �����ؿ���";

			NTCHARString<128>	kName;
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siPara1);
			if(ref > 0)
			{
				kName = pclClient->pclItemManager->pclItemInfo[ref]->GetName();
			}

			kText.Replace("#itemname#", kName);
			kText.Replace("#num#", SI32ToString(pclinfo->m_clMissionQuestInfo.clQuestClearConditionInfo.siPara2));
		}

		((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetText(kText);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHAR_ROULETTE(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	cltGameMsgResponse_Char_Roulette* pclinfo = (cltGameMsgResponse_Char_Roulette*)pclMsg->cData;

	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->m_siCharUnique];
	if( pclClient->pclCM->IsValidID(charid) == false )			return;

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(charid);
	if( pclchar == NULL )										return;

	switch(pclinfo->m_siBufRoulette)
	{
	case CHAR_ROULETTE_START:
		{
			pclchar->bBuffRouletteSwitch = true;

			CNCharRouletteDlg* pkCharRouletteDlg = (CNCharRouletteDlg*)pclclient->m_pDialog[NCHARBUFF_ROULETTE_DLG];
			if( pkCharRouletteDlg && charid == 1 )
			{
				pkCharRouletteDlg->SetCharKinds(pclinfo->m_siRouletteKinds, pclinfo->m_siCount, pclinfo->m_siResultKind);
				pkCharRouletteDlg->Start();
			}
		}
		break;

	case CHAR_ROULETTE_END:
		{
			pclchar->bBuffRouletteSwitch = false;
		}
		break;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGE_RESIDENT_INVITE(cltMsg* pclMsg, SI32 id)
{	
	cltGameMsgResponse_Village_Resident_Invite* pclinfo = (cltGameMsgResponse_Village_Resident_Invite*)pclMsg->cData;

	if(NULL == m_pDialog[NYESORNODLG])
		CreateInterface( NYESORNODLG );

	CNYesOrNoDlg* pNYesOrNoDlg = (CNYesOrNoDlg*)m_pDialog[NYESORNODLG];

	pNYesOrNoDlg->SetVillageResidentInvite(REASON_VILLAGE_RESIDENT_INVITE, pclinfo->m_kCharName, pclinfo->m_siVillageUnique);
}
// NEW PVP - �ռ��� 2008.10.08
void cltClient::DoMsg_GAMEMSG_RESPONSE_PVP_FILED(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PVP_Request* pclinfo = (cltGameMsgResponse_PVP_Request*)pclMsg->cData;
	cltClient* pclclient = (cltClient*)pclClient;

	switch(pclinfo->siRequestType) 
	{
	case REQUEST_PVP :// PVP�� ��û �޾Ҵ�.
		{
			// ���� ���� ���� ����´�
			CNSoundOnOffDlg* pNSoundOnOffDlg = ((CNSoundOnOffDlg*)m_pDialog[ NSOUNDONOFF_DLG ]);

			SI32 requestid = pclinfo->siPara1	;// PVP ��û�� ��� �ɸ��� ���̵�.
			SI32 enemyid = pclClient->pclCM->GetIDFromCharUnique(requestid);	// PVP ��û�� ����� PersonID�� Charunique�� ���Ѵ�.
			if( pclClient->pclCM->IsValidID( id ) == false )	return	;
			if( pclClient->pclCM->IsValidID( enemyid ) == false ) return	;

			TCHAR* siRequestname = (TCHAR*)pclclient->pclCM->CR[enemyid]->GetName();	// PersonID ���� PVP����û�� ��� �̸��� ã�Ƴ���.

			if (pNSoundOnOffDlg->m_bPVP == true) 
			{
				// ���� �޼��� �ڵ����� �����ش�
				cltGameMsgRequest_PVP_Request clinfo ( REFUSE_PVP , requestid );// ��û�� ��� ���̵� �ٽ� ���� ������.
				cltMsg clMsg(GAMEMSG_REQUEST_PVP_FILED, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
			else
			{
				// �޽��� â ����
				if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)
				{
					pclclient->CreateInterface( NCOMMONMSG_DLG );
				}
				NTCHARString512	kText(GetTxtFromMgr(9570));
				kText.Replace("#requestname#", pclinfo->m_kCharName );

				((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_PVP);	
				((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetPVPRequrstID( requestid );	
				((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetText(kText);
				((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec( 10 );
			}

		}
		break;
	case REFUSE_PVP :
		{
			TCHAR* pTitle= GetTxtFromMgr(428);
			TCHAR* pText = GetTxtFromMgr(9571);
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
		}
		break;
	case ILLPLACE_PVP :
		{
			// ���縮�������� ���� �Ұ��� �޼��� �����ش�.
			TCHAR* pTitle= GetTxtFromMgr(428);
			TCHAR* pText = GetTxtFromMgr(9576);
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
		}
		break;
	case PVP_LEAGUEBEFORE1M :
		{
			// ���� 1���� 
			TCHAR* pTitle= GetTxtFromMgr(9581)	;
			TCHAR* pText = GetTxtFromMgr(9727)	;
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
		}
		break;
	case READY_PVP:
		{
			if( pclClient->pclCM->IsValidID( id ) == false )	return	;
			cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
			pclChar->siPVPWaitTime = pclClient->CurrentClock  ; // ���� �������� ��Ŷ���� �ð� ����
			//�װ� �����Ѵ�.
			pclChar->bPvpCountDown	= true;
			if (pclinfo->siPara1 == PVP_LEAGUE ) 
			{
				pclChar->SetPVP_LeagueEnemyPersonID( pclinfo->siPara2)	;
			}
		}
		break;
	case START_PVP : // PVP�� ���� �³��ߴ�.
		{
			SI32 siCharID = pclClient->pclCM->GetIDFromCharUnique( pclinfo->siPara2 );
			if( pclClient->pclCM->IsValidID( siCharID ) == false )	return	;
			cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[ siCharID ];

			pclChar->bPvpCountDown	= false ;// �Ӹ����� �׸��� ����.
			pclChar->siPVPTime	= pclClient->CurrentClock;	// ���� �ð��� ���� �Ѵ�.
			SI32 siEnemyId	=	pclinfo->siPara1	;
			// ���� ������ �� ID�� ���� �Ѵ�.
			pclChar->siEnemUnique = siEnemyId	;

			pclChar->ParametaBoxAction()	;
			SI32 siLife		=	pclChar->clPB.GetMaxLife()	;
			pclChar->IncreaseLife( siLife )		;
		}
		break;
	case END_PVP:
		{
			if( pclClient->pclCM->IsValidID( id ) == false )	return	;

			cltCharClient* pclpvpchar = pclClient->pclCM->GetCharClient( pclClient->pclCM->GetIDFromCharUnique(pclinfo->siPara2) );
			if(pclpvpchar == NULL)								return;

			// PVP�� ������ ĳ���Ͷ��, ǥ�� ������ �����Ѵ�.
			if( pclclient->pclCM->CR[id]->GetCharUnique() == pclpvpchar->GetCharUnique() )
			{
				SI32 WinOrLos = pclinfo->siPara1	;
				// ���� ������ �� ID�� ���� �Ѵ�.
				switch( WinOrLos ) 
				{
				case WIN_PVP :
					{
						pclclient->pclCM->CR[id]->siEnemUnique	=	0	;
						pclclient->pclCM->CR[id]->SetPVP_LeagueEnemyPersonID( 0 );
						pclclient->pclCM->CR[id]->siPVPWaitTime	=	0	; 
						pclclient->pclCM->CR[id]->siPVPEndTime	=	pclClient->CurrentClock	; 
						pclclient->pclCM->CR[id]->siPVPWin		=	true	;
						pclclient->pclCM->CR[id]->siPVPLose		=	false	;
						pclclient->pclCM->CR[id]->siPVPDraw		=	false	;
						pclclient->pclCM->CR[id]->bPvpLeague	=	false	;
					}break;
				case LOSE_PVP :
					{
						pclclient->pclCM->CR[id]->siEnemUnique	=	0		;
						pclclient->pclCM->CR[id]->SetPVP_LeagueEnemyPersonID( 0 )	;
						pclclient->pclCM->CR[id]->siPVPWaitTime	=	0				; 
						pclclient->pclCM->CR[id]->siPVPEndTime	=	pclClient->CurrentClock	;
						pclclient->pclCM->CR[id]->siPVPWin		=	false	;
						pclclient->pclCM->CR[id]->siPVPLose		=	true	;
						pclclient->pclCM->CR[id]->siPVPDraw		=	false	;
						pclclient->pclCM->CR[id]->bPvpLeague	=	false	;
					}break;
				case DRAW_PVP :
					{
						pclclient->pclCM->CR[id]->siEnemUnique	= 0					;
						pclclient->pclCM->CR[id]->SetPVP_LeagueEnemyPersonID( 0 )	;
						pclclient->pclCM->CR[id]->siPVPWaitTime	=	0	; 
						pclclient->pclCM->CR[id]->siPVPEndTime	=	pclClient->CurrentClock	; 
						pclclient->pclCM->CR[id]->siPVPWin		=	false	;
						pclclient->pclCM->CR[id]->siPVPLose		=	false	;
						pclclient->pclCM->CR[id]->siPVPDraw		=	true	;
						pclclient->pclCM->CR[id]->bPvpLeague	=	false	;
					}break;
				}
			}
			else
			{
				// PVP�� ������ ĳ���Ͱ� �ƴϸ� ǥ�þ��� �����͸� �����Ѵ�.
				pclpvpchar->siEnemUnique = 0;
			}
		}break;
	case PVP_LEAGUESTART:
		{
			NTCHARString256 stSrart		= GetTxtFromMgr(9663)	;
			pclClient->pclMessage->SetMsg(stSrart,0 ,RGB(255, 255, 0));
		}break;
	default:
		{

		}
		break;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_INFOGET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PVP_League_InfoGet* pclInfo = (cltGameMsgResponse_PVP_League_InfoGet*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( pclchar->pclPVP_LeagueInfo )
	{
		pclchar->pclPVP_LeagueInfo->Init();
		pclchar->pclPVP_LeagueInfo->Set( &pclInfo->m_clPVP_LeaugeInfo );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PVP_League_UI_InfoGet* pclInfo = (cltGameMsgResponse_PVP_League_UI_InfoGet*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	CNPVPLeageuDlg* pPVPLeagueDlg = (CNPVPLeageuDlg*)m_pDialog[PVPLEAGUE_DLG];
	if ( NULL == pPVPLeagueDlg )
	{
		return;
	}

	pPVPLeagueDlg->SetPVPLeagueInfo( pclInfo );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PVP_League_Battle_ChangeGrade* pclInfo = (cltGameMsgResponse_PVP_League_Battle_ChangeGrade*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	pclchar->SetPVP_LeagueGrade( pclInfo->m_siGrade );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DIVINATION_ROULETTE(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	cltGameMsgResponse_Divination_Roulette* pclinfo = (cltGameMsgResponse_Divination_Roulette*)pclMsg->cData;

	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->m_siCharUnique];
	if( pclClient->pclCM->IsValidID(charid) == false )			return;

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(charid);
	if( pclchar == NULL )										return;

	switch(pclinfo->m_siDivinationRoulette)
	{
	case DIVINATION_ROULETTE_START:
		{
			pclchar->bBuffRouletteSwitch = true;

			CNNewYearEventRoulette* pkNewYearEventRouletteDlg = (CNNewYearEventRoulette*)pclclient->m_pDialog[NEWYEAR_ROULETTE_DLG];
			if( pkNewYearEventRouletteDlg && charid == 1 )
			{
				pkNewYearEventRouletteDlg->SetDivinations(pclinfo->m_siRouletteDivinations, pclinfo->m_siCount, pclinfo->m_siResultDivination, pclinfo->m_siBufKind_Type);
				pkNewYearEventRouletteDlg->Start();
			}
		}
		break;

	case DIVINATION_ROULETTE_END:
		{
			pclchar->bBuffRouletteSwitch = false;
		}
		break;
	}
}
// �߷�Ÿ�� ���� ������ �޾Ƽ� ��������Ʈ �Ѵ�
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINE_INFO_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_ValentineWar_Info_get* pclInfo = (cltGameResponse_ValentineWar_Info_get*)pclMsg->cData;
	if( pclClient->pclCM->IsValidID(id) == false )			return;
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(id);
	pclchar->pclValentineWar->Set( &pclInfo->clValentinewarInfo)	;
}
// �߷�Ÿ�� ���� �ַ� Ŀ�� ������ ������Ʈ �Ѵ�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINE_REQUEST(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_ValentineWar_Request* pclInfo = (cltGameMsgResponse_ValentineWar_Request*)pclMsg->cData;
	SI32 siID  = pclCM->GetIDFromCharUnique(pclInfo->siCharUnique )	;
	if( pclClient->pclCM->IsValidID(siID) == false )			return;
	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(siID);
	if (pclchar->pclValentineWar) 
	{
		pclchar->pclValentineWar->Init();
		pclchar->pclValentineWar->Set( &pclInfo->clValentinewarInfo)	;
		pclchar->dwValentineAnswerTime = pclClient->CurrentClock	;
	}	
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINE_RUSOLO_COUPLE_ONTIME(cltMsg* pclMsg, SI32 id)
{
	CreateInterface( NVALANTINE_DLG );
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINE_OPENDLG(cltMsg* pclMsg, SI32 id)
{
	CreateInterface( NVALANTINE_DLG );
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINE_PRIZEGET(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	// �ؽ�Ʈ �� �˷��ش�
	TCHAR* pTitle= GetTxtFromMgr(9766)	;
	TCHAR* itemname = (TCHAR*)pclClient->pclItemManager->GetName( ITEMUNIQUE(2781));
	NTCHARString512		kText( GetTxtFromMgr(9768) );
	kText.Replace("#itemname#",  itemname );
	pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, kText );
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_GuildHuntMapWar_Request_Warp(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GuildHuntMapWarWar_Request* pclinfo = (cltGameMsgResponse_GuildHuntMapWarWar_Request*)pclMsg->cData;
	// ������ �ð� ���.	
	enum
	{
		Round_1 = 0	,
		Round_2,
		Round_3	,
	};
	//  �������� ���� �ð�.
	SI32 siMinute = pclinfo->stTime.wMinute;
	SI32 siSecond = pclinfo->stTime.wSecond;
	SI32 resultsecond	=	0	;	// ���� ��.
	SI32 resultminute	=	0	;	// ���� ��
	SI32 ReaultSecond	=	0	;	// ���� �� ��.
	SI32 TimeSection	=	0	;	// ���� ����

	if (  siSecond > 0 ){
		resultsecond = 60 - siSecond	;	// ���� ��
	}

	if ( 0 <= siMinute && 20 > siMinute  )
	{
		TimeSection	=	Round_1;
	}
	else if ( 20 <= siMinute && 40 > siMinute )
	{
		TimeSection	=	Round_2;
	}
	else if ( 40 <= siMinute && 59 >= siMinute )
	{
		TimeSection	=	Round_3;
	}
	switch ( TimeSection )
	{
	case Round_1:	// ùŸ�� ������ 03�п� ����.�׷��� 3��
		{
			resultminute = 3 - siMinute ;
		}break	;
	case Round_2:	// �ι����� Ÿ���� 23�п� ���� �׷��� 23��
		{
			resultminute = 23 - siMinute ;

		}break	;
	case Round_3 :	// ������ ������ 43�п� ���� �׷��� 43�� 
		{
			resultminute = 43 - siMinute;

		}break	;
	}
	if ( resultsecond == 30 )
	{
		ReaultSecond = ((resultminute-1)*60)+resultsecond	;
	}
	else
	{
		ReaultSecond = resultminute* 60	;
	}


	SI32 siType = pclinfo->siType;
	SI32 siPersonID = pclinfo->siPersonID	;
	switch ( siType )
	{
	case REQUEST_WARP_HUNTMAPGUILDWAR_WARP :	// ������� �ϱ����� ����������� �����ΰ��� ���� ����.
		{
			// �޽��� â ����
			if (m_pDialog[NCOMMONMSG_DLG] == NULL)
			{
				CreateInterface( NCOMMONMSG_DLG );
			}
			NTCHARString512	kText(GetTxtFromMgr(9962)); // �ϴ� ���� �ϰų� ������.
			kText.Replace("#second#", SI32ToString(ReaultSecond));

			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_GUILDHUNTMAPWAR_WARP);	
			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->SetGuildMapWar_PersonID( siPersonID );
			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->SetText(kText);
			((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec( 10 );//������ѽð� 10��

		}
		break;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PROPOSE_QUESTION(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Propose_Question* pclinfo = (cltGameResponse_Propose_Question*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	if ( NULL == m_pDialog[NPROPOSE_ANSWER_DLG] )
	{
		CreateInterface( NPROPOSE_ANSWER_DLG );
	}

	if ( m_pDialog[NPROPOSE_ANSWER_DLG] )
	{
		((CNProposeAnswerDlg*)m_pDialog[NPROPOSE_ANSWER_DLG])->SetPropose( pclinfo->m_szCharName, pclinfo->m_szMessage );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SET_MARRY(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Set_Marry* pclinfo = (cltGameResponse_Set_Marry*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// ��ȥ�Ȱ� ����
	if ( pclchar->pclMarriage )
	{
		pclchar->pclMarriage->Set( pclinfo->m_siMatePersonID, pclinfo->m_szMateName, pclinfo->m_siWeddingDateVary, 0, FALSE, pclinfo->m_siLoveLevel, 0, 0, pclinfo->m_siConnectMode );
	}

	// ��ȥ�� �Ҹ�� ������ ����
	if ( (PERSONITEM_INV0 <= pclinfo->m_siItemPos) && ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) > pclinfo->m_siItemPos) )
	{
		pclchar->pclCI->clCharItem.clItem[ pclinfo->m_siItemPos ].Set( &pclinfo->m_clItem );
	}

	// ��ȥ �޽��� �Ѹ�
	NTCHARString32		strTitle( TEXT("") );
	NTCHARString1024	strText( GetTxtFromMgr(9979) );

	g_ErrorMsg.BigSet( strTitle, strText );

	// ûȥ â�� ���ִٸ�
	if ( m_pDialog[NPROPOSE_QUESTION_DLG] )
	{
		m_pDialog[NPROPOSE_QUESTION_DLG]->DeleteDialog();
	}

	// ���� �ʻ� ������� ������
	if ( (pclchar->pclMarriage) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
	{
		if ( NULL == m_pDialog[NMARRIAGELOVELEVEL_DLG] )		
		{
			CreateInterface( NMARRIAGELOVELEVEL_DLG );
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GET_MARRY_INFO(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Get_Marry_Info* pclinfo = (cltGameResponse_Get_Marry_Info*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( NULL == pclchar->pclMarriage )
	{
		return;
	}

	// ĳ������ ��ȥ ������ �����Ѵ�
	pclchar->pclMarriage->Set( pclinfo->m_siMatePersonID,	pclinfo->m_szMateName,
		pclinfo->m_siWeddingDateVary,	pclinfo->m_siItemGetDateVary,	FALSE,
		pclinfo->m_siLoveLevel,			pclinfo->m_siUseHourVary,		pclinfo->m_siLimitHourVary,
		pclinfo->m_siConnectMode );

	// ���� �ʻ� ������� ������ â�� ǥ���Ѵ�
	if ( MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode() )
	{
		if ( NULL == m_pDialog[NMARRIAGELOVELEVEL_DLG] )
		{
			CreateInterface( NMARRIAGELOVELEVEL_DLG );
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MARRY_ITEMGET_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Marry_ItemGet_Set* pclinfo = (cltGameResponse_Marry_ItemGet_Set*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( FALSE == pclchar->IsMarried() )
	{
		return;
	}

	pclchar->pclMarriage->SetItemGetDateVary( pclinfo->m_siItemGetDateVary );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MARRY_LOVE_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Marry_Love_Set* pclinfo = (cltGameResponse_Marry_Love_Set*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( FALSE == pclchar->IsMarried() )
	{
		return;
	}

	pclchar->pclMarriage->SetLoveLevel( pclinfo->m_siLoveLevel );
	pclchar->pclMarriage->SetLimitHourVary( pclinfo->m_siLimitHourVary );
	pclchar->pclMarriage->SetUseHourVary( pclinfo->m_siUseHourVary );

}
void cltClient::DoMsg_GAMEMSG_RESPONSE_GET_FAMILYINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Get_Familyinfo* pclinfo = (cltGameResponse_Get_Familyinfo*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}
	pclchar->pclFamily->Set(&pclinfo->m_cFamily)	;
}



void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillBook_MagicInfo_Get* pclInfo = (cltGameMsgResponse_SkillBook_MagicInfo_Get*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( id  );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->Clear();

	SI32 siCount = 0;
	for( siCount = 0; siCount < MAX_SKILLBOOK_SUBMAGIC_NUM; ++siCount )
	{
		if(    0 >= pclInfo->m_clAddSkillBookMagic[siCount].GetMagicKind() 
			|| 0 >= pclInfo->m_clAddSkillBookMagic[siCount].GetSkillUnique() )
		{
			break;	
		}
		pclChar->pclCharSkillBookInfo->SetSkillBookMagic( pclInfo->m_iIndex[siCount], &pclInfo->m_clAddSkillBookMagic[siCount] );
	}

	for( siCount = 0; siCount < MAX_SKILLBOOK_SUBMAGIC_NUM; ++siCount )
	{
		if(    0 >= pclInfo->m_clAddSkillBookSubMagic[siCount].GetMagicKind() 
			|| 0 >= pclInfo->m_clAddSkillBookSubMagic[siCount].GetParentMagicKind() )
		{
			break;	
		}
		pclChar->pclCharSkillBookInfo->AddSkillBookSubMagic( &pclInfo->m_clAddSkillBookSubMagic[siCount] );
	}

	if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->Clear();	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillBook_Magic_Add* pclInfo = (cltGameMsgResponse_SkillBook_Magic_Add*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( id  );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->AddSkillBookMagic( pclChar->GetAttackType(), &pclInfo->m_clAddSkillBookMagic );

	if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->Refresh();	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_DEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillBook_Magic_Del* pclInfo = (cltGameMsgResponse_SkillBook_Magic_Del*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( id  );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->DelSkillBookMagic( pclInfo->m_iIndex );

    if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->Refresh();	
}



void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillBook_SubMagic_Add* pclInfo = (cltGameMsgResponse_SkillBook_SubMagic_Add*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( id  );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->AddSkillBookSubMagic( &pclInfo->m_clAddSkillBookSubMagic );

	if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->Refresh();	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillBook_SubMagic_Del* pclInfo = (cltGameMsgResponse_SkillBook_SubMagic_Del*)pclMsg->cData;

	cltCharClient* pclChar = pclCM->GetCharClient( id  );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->DelSkillBookSubMagic( &pclInfo->m_clAddSkillBookSubMagic );

	if( m_pDialog[ NNEWMAGICINFO_DLG ] )
		((CNNewMagicInfoDlg*)m_pDialog[ NNEWMAGICINFO_DLG ])->Refresh();	
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CURSEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_CurseInfo* pclInfo = (cltGameMsgResponse_CurseInfo*)pclMsg->cData;

	SI16 targetid = pclCM->GetIDFromCharUnique( pclInfo->m_siCharUnique );
	if(targetid <= 0)	return ;

	if(pclCM->IsValidID(targetid) == FALSE) return;
	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[targetid];

	pclchar->m_clCharCurseEffect.SetCurse( &pclInfo->m_clCharCurseEffect, pclchar->GetID() );
}