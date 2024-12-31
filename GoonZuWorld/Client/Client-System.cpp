//---------------------------------
// 2003/11/14 ���°�
//---------------------------------

#include "Client.h"
#include "Music\Music.h"
#include "..\CommonLogic\MsgType.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "../Resource.h"
#include "Char\CharManager\CharManager.h"
#include "MsgType-Item.h"

#include "MsgType-System.h"
#include "Msg\MsgType-Web.h"
#include "Msg\MsgType-Village.h"
#include "Msg\MsgType-Quest.h"
#include "..\CommonLogic\MsgType-Person.h"
#include "StatusBar\StatusBar.h"

#include "StatusBar\ChatStatusBar\ChatStatusBarBaseInfo.h"
#include "StatusBar\ChatStatusBar\ChatStatusBar.h"

// ä�� ����. 
#include "Interface\DrawChat\DrawChatSurface.h"
#include "Interface\DrawChat\DrawChat.h"
#include "Interface\RichEditChatMgrDlg\RichEditChatMgrDlg.h"
#include "Interface\LetterDlg\LetterDlg.h"
#include "NInterface\NLetterDlg\NLetterDlg.h"
#include "NInterface\NGuildChatDlg\NGuildChatDlg.h"
#include "ninterface\NPlayMatchDlg\NBlackArmyMVPDlg.h"
#include "ninterface\NPlayMatchDlg\NPlayMatchDlg.h"
#include "NInterface/NMySummonDlg/NMySummonDlg.h"
#include "NInterface/NHelperDlg/NHelperQuestionListDlg.h"
#include "NInterface/NHelperDlg/NHelperQuestionOrAnswerDlg.h"
#include "NInterface/NHelperDlg/NHelperAnswerCompleteDlg.h"

// ĳ���͸� ���
#include "Interface\DrawCharName\DrawCharNameSurface.h"
#include "Interface\DrawCharName\DrawCharName.h"

// �ӼӸ� ä�� ����. 
//#include "Interface\PrivateChatDlg\PrivateChatBaseInfo.h"
//#include "Interface\PrivateChatDlg\PrivateChatDlgMgr.h"

// ���� �ֱ�
#include "Interface/EventNotice/EventNotice.h"
#include "Interface/HtmlDlg/HtmlDlg.h"

#include "Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "Interface\RareItemDlg\RareItemDlg.h"
#include "NInterface\NRareItemDlg\NRareItemDlg.h"
#include "Interface\LoginNoticeDlg\LoginNoticeDlg.h"

#include "Interface/InvestmentDlg/InvestmentDlg.h"

//#include "Interface/PartyDlg/PartyDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "NInterface/NMaster/NMaster.h"
#include "NInterface/NChatDlg/NChatDlg.h"
#include "NInterface/NResidentsDlg/NResidentsDlg.h"
#include "Ninterface/ninfodlg/NInfoDlg.h"

#include "Prompt\PromptBaseDefinition.h"
#include "Prompt\PromptMgr.h"

#include "NInterface/NVillageDetailInfo/NVillageDetailInfo.h"

#include "../common/AutoHunting/AutoHunting.h"
#include "..\Common\Bullet\Bullet.h"
#include "..\Common\Smoke\Smoke.h"
#include "..\CommonLogic\Hunt\Hunt.h"
#include "..\CommonLogic\MagicMgr\MagicMgr.h"
#include "..\CommonLogic\BlackArmy\BlackArmy.h"


#include "Interface\Byungzo\ByungzoDlg.h"
#include "Interface\Yezo\YezoDlg.h"
#include "Interface\Hozo\HozoDlg.h"
#include "Interface\GoonzuDlg\GoonzuDlg.h"
#include "Interface\Izo\IzoDlg.h"
#include "Interface\Gongzo\GongzoDlg.h"
#include "Interface\Hyungzo\HyungzoDlg.h"

#include "NInterface/NCommonMsgDlg/NCommonMsgDlg.h" // Ŀ�� ���̾�α�
#include "NInterface/NHozoDlg/NHozoBaseDlg.h"
#include "NInterface/NByungzoDlg/NByungzoDlg.h"
#include "NInterface/NIzoDlg/NIzoBaseDlg.h"
#include "NInterface/NGongzoDlg/NGongzoDlg.h"
#include "NInterface/NGoonzuDlg/NGoonzuDlg.h"
#include "NInterface/NYezoDlg/NYezoBaseDlg.h"
#include "NInterface/NHyungzoDlg/NHyungzoBaseDlg.h"

#include "NInterface/NResidentsInfoDlg/ResidentsInfoDlg.h"
#include "NInterface/NPartyDlg/NPartyDlg.h"

#include "NInterface/NNoticeAdminDlg/NNoticeAdminDlg.h"
#include "NInterface/NAutoHunting/NAutoHunting.h"
#include "NInterface/NInvestmentDlg/NInvestmentDlg.h"
#include "NInterface/NEventNotice/NEventNoticeDlg.h"
#include "NInterface/NPrivateChatDlg/NPrivateChatDlgMgr.h"
#include "NInterface/NStatusBarDlg/NStatusBarDlg.h"
#include "NInterface/NChatBardlg/NChatBarDlg.h"
#include "NInterface/NNewEnchantOther/NNewEnchantOther.h"
#include "NInterface/nwennyoldman/NWennyOldMan.h"
#include "ninterface/ngetpresentdlg/NGetPresentDlg.h"
#include "ninterface/ngetpresentdlg/NThanksPresentDlg.h"
#include "ninterface/NTreasureBoxDlg/NTreasureBoxDlg.h"
#include "ninterface/NManufactureNPCDlg/NManufactureNPC.h"
#include "ninterface/NOpenBigItemBoxDlg/NOpenBigItemBoxDlg.h"
#include "ninterface/NNewNotify/NNewNotifyDlg.h"

#include "ninterface/ngoonzudlg/NGoonzuSiege.h"
#include "ninterface/ngoonzudlg/NGoonzuWorkDlg.h"

#include "ImageInterface/VillageWarNotice/VillageWarNotice.h"
#include "LevelUpText/LevelUpText.h"
#include "ninterface/NTreasureExtraBoxDlg/NTreasureBoxExtraDlg.h"
#include "FeastEffect/FeastEffectManager.h"

//--------------------------------------
// DBManager
//--------------------------------------
#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-System.h"

#include "../Apex/ApexGoonZu.h"

#include "../Client/ninterface/NBlackWarReformDlg/NBlackWarReformRewardDlg.h"

//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� ���.]
#include "../Client/ninterface/NArtifactDlg/NArtifactBaseDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactRestoreDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactMixtureDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactRemoveDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactSlotCreateDlg.h"

// [����] ���� �̺�Ʈ ������ŷ ���� â ���.  => 2008-6-19 
#include "../Client/ninterface/NServerEventDlg/NServerEventRankDlg.h"
#include "../Client/ninterface/NServerEventDlg/NServerEventQuestDlg.h"
#include "../Client/ninterface/NServerEventDlg/NServerInstanceMapBounusDlg.h"

#include "../Server/ServerEvent/ServerEvent-Quest.h"

#include "ninterface/NQuestNoticeDlg/NQuestNoticeDlg.h"

#include "../Client/ninterface/NElixirDlg/NElixirNPCDlg.h"
#include "../Client/ninterface/NElixirDlg/NElixirStatusDlg.h"

#include "../Client/CheckProcess/CheckProcess.h"

#include "../../NLib/NUtil.h"

#include "../Client/ninterface/ngoonzudlg/NGoonzuRaccoonEventDlg.h"

#include "GZMacroAnalysis/GMA.h"

extern cltCommonLogic* pclClient;
extern DWORD dwQuitTimer;
extern SI32 g_siServiceAreaCode ;

// NUtil.cpp�� ����� ����
extern UI64	uiSec; // �ð� ����� ���� ���� ����

// �ٸ� ����� ������ ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_USERLEVELUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UserLevelUp* pclinfo = (cltGameMsgResponse_UserLevelUp*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	TCHAR buffer[512] = TEXT("");
	TCHAR temp[256] = TEXT("");
	TCHAR* pTitle = GetTxtFromMgr(854);
	TCHAR* pText  = GetTxtFromMgr(853);
	TCHAR level[128]= TEXT(" ") ;
	StringCchPrintf(level, 128, TEXT("%d"),pclinfo->siLevel);



	Nsprintf(buffer,pText,
		TEXT("user"),pclinfo->szPersonName    ,
		TEXT("level"), level   ,
		TEXT("mentor"),pclinfo->szFatherName    ,NULL);


	//sprintf(buffer, pText, pclinfo->szPersonName, pclinfo->siLevel, pclinfo->szFatherName);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, buffer );
}

// ��ǰ ���� ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_RAREITEMMADE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RareItemMade* pclinfo = (cltGameMsgResponse_RareItemMade*)pclMsg->cData;

	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bJewelItemNotifyReject )return ;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)
		return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[2048] = TEXT("");

	//==================================================================
	// �ؽ�Ʈ ����
	//==================================================================

	// ���� ���� ���, 
	if(pclinfo->siRareSwitch == RAREITEM_NOTICE_SWITCH_MADE)
	{
		TCHAR* pTitle = GetTxtFromMgr(855);
		TCHAR* pText  = GetTxtFromMgr(856);

		StringCchCopy(title, 128, pTitle);

		StringCchPrintf(buffer, 2048,
			pText, 
			pclinfo->szPersonName, pclinfo->siIncFameExp);
	}
	// ���ؿ��� ��������� �������� ���(Ȥ�θ� ����(��ȣ��)) 
	else if(pclinfo->siRareSwitch == RAREITEM_NOTICE_SWITCH_WENNYOLDMAN)
	{
		TCHAR* pTitle = GetTxtFromMgr(5959);
		TCHAR* pText  = GetTxtFromMgr(5958);

		StringCchCopy(title, 128, pTitle);

		StringCchPrintf(buffer, 2048,
			pText, 
			pclinfo->szPersonName, pclinfo->clItem.GetShortName(pclItemManager));
	}
	else if(pclinfo->siRareSwitch == RAREITEM_NOTICE_SWITCH_GACHA)
	{
		TCHAR* pTitle = GetTxtFromMgr(7018);
		TCHAR* pText  = GetTxtFromMgr(7019);

		StringCchCopy(title, 128, pTitle);

		StringCchPrintf(buffer, 2048,
			pText, 
			pclinfo->szPersonName, pclinfo->clItem.GetShortName(pclItemManager));
	}
	else if ( RARAITEM_NOTICE_SWITCH_SUMMONDOLL == pclinfo->siRareSwitch )
	{
		TCHAR*			pTitle = GetTxtFromMgr(8794);
		NTCHARString256	strText( GetTxtFromMgr(8793) );

		strText.Replace( TEXT("#name#"),		pclinfo->szPersonName );
		strText.Replace( TEXT("#madeitem#"),	pclinfo->clItem.GetShortName(pclItemManager) );

		StringCchCopy(title,	128,	pTitle);
		StringCchCopy(buffer,	256,	strText);
	}
	else if ( RARAITEM_NOTICE_SWITCH_HALLOWEENMANTLE == pclinfo->siRareSwitch )
	{
	}

	else if ( RARAITEM_NOTICE_SWITCH_PVPLEAGUEPRIZE == pclinfo->siRareSwitch )
	{
	}

	//==================================================================
	// â ����
	//==================================================================
	if ( (RAREITEM_NOTICE_SWITCH_GACHA == pclinfo->siRareSwitch) || (RARAITEM_NOTICE_SWITCH_SUMMONDOLL == pclinfo->siRareSwitch) )
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

		if(m_pDialog[NRAREITEM_DLG ] == NULL)	CreateInterface( NRAREITEM_DLG );
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetBestGacha(&pclinfo->clItem, pclinfo->szPersonName, title, buffer);		
	}
	else if(RARAITEM_NOTICE_SWITCH_HALLOWEENMANTLE == pclinfo->siRareSwitch)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

		TCHAR* stritemName = (TCHAR*) pclItemManager->GetName( pclinfo->clItem.siUnique );	// ������ �̸�

		NTCHARString128 strText( GetTxtFromMgr(8873) );
		strText.Replace( TEXT("#user#"), pclinfo->szPersonName );
		strText.Replace( TEXT("#item#"), stritemName );

		if(m_pDialog[NRAREITEM_DLG ] == NULL)			CreateInterface( NRAREITEM_DLG );
		if(m_pDialog[NRAREITEM_DLG ] != NULL)
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetVillageEventGetItem( GetTxtFromMgr(8880), strText, EVENT_STRUCTURE_HALLOWEEN,pclinfo->clItem.siUnique,pclinfo->szPersonName);
	}
	else if(RARAITEM_NOTICE_SWITCH_CHRISTMASEVENT == pclinfo->siRareSwitch)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

		TCHAR* stritemName = (TCHAR*) pclItemManager->GetName( pclinfo->clItem.siUnique );	// ������ �̸�

		NTCHARString128 strText( GetTxtFromMgr(7684) );
		strText.Replace( TEXT("#user#"), pclinfo->szPersonName );
		strText.Replace( TEXT("#item#"), stritemName );

		if(m_pDialog[NRAREITEM_DLG ] == NULL)			CreateInterface( NRAREITEM_DLG );
		if(m_pDialog[NRAREITEM_DLG ] != NULL)
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetVillageEventGetItem( GetTxtFromMgr(7660), strText, EVENT_STRUCTURE_CHRISTMASTREEBASE,pclinfo->clItem.siUnique,pclinfo->szPersonName);
	}
	else if(RARAITEM_NOTICE_SWITCH_PVPLEAGUEPRIZE == pclinfo->siRareSwitch)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

		TCHAR* stritemName = (TCHAR*) pclItemManager->GetName( pclinfo->clItem.siUnique );	// ������ �̸�

		NTCHARString128 strText( GetTxtFromMgr(9729) );
		strText.Replace( TEXT("#user#"), pclinfo->szPersonName );
		strText.Replace( TEXT("#item#"), stritemName );

		if(m_pDialog[NRAREITEM_DLG ] == NULL)			CreateInterface( NRAREITEM_DLG );
		if(m_pDialog[NRAREITEM_DLG ] != NULL)
			((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetVillageEventGetItem( GetTxtFromMgr(9581), strText, EVENT_PVP_LEAGUE,pclinfo->clItem.siUnique,pclinfo->szPersonName);
	}
	else if (RARAITEM_NOTICE_SWITCH_LEVELUPREWARD == pclinfo->siRareSwitch)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

		NTCHARString64	strTitle( GetTxtFromMgr(8934) );
		NTCHARString256	strText( GetTxtFromMgr(8933) );
		
		TCHAR*			szItemName = (TCHAR*)pclItemManager->GetName( pclinfo->clItem.siUnique );	// ������ �̸�

		strText.Replace( TEXT("#name#"),		pclinfo->szPersonName );
		strText.Replace( TEXT("#level#"),		SI32ToString(pclinfo->siIncFameExp) );
		strText.Replace( TEXT("#itemname#"),	szItemName );
        												

		if(m_pDialog[NRAREITEM_DLG ] == NULL)			CreateInterface( NRAREITEM_DLG );
		if(m_pDialog[NRAREITEM_DLG ] != NULL)
			((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetBestGacha(&pclinfo->clItem, pclinfo->szPersonName, strTitle, strText);
	}
	// ��þƮ ���� �˸�â
	else if (RAREITEM_NOTICE_SWITCH_ENCHANTSUCCESS == pclinfo->siRareSwitch)
	{
		NTCHARString64	strTitle		= GetTxtFromMgr(5614);
		NTCHARString256	strText			= GetTxtFromMgr(9843);

		NTCHARString64	strItemName		= pclItemManager->GetName( pclinfo->clItem.siUnique );
		TCHAR			szBuf[128]		= TEXT("");
		NTCHARString64	strEnchantType	= ((cltItemManagerClient*)pclItemManager)->GetEnchantTypeName(szBuf, pclinfo->clItem.Element.siType);

		strText.Replace( TEXT("#name#"),	pclinfo->szPersonName );
		strText.Replace( TEXT("#itemname#"),strItemName );
		strText.Replace( TEXT("#type#"),	strEnchantType);
		strText.Replace( TEXT("#grade#"),	SI32ToString(pclinfo->clItem.Element.siPower) );

		if(m_pDialog[NRAREITEM_DLG ] == NULL)	
			CreateInterface( NRAREITEM_DLG );

		if(m_pDialog[NRAREITEM_DLG ] != NULL)
		{
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);
			((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetBestGacha(&pclinfo->clItem, pclinfo->szPersonName, strTitle, strText);
		}

	}
	else
	{
		TCHAR explain[1536]=TEXT("");
		if(pclItemManager->GetExplain(&pclinfo->clItem, explain) == TRUE)
		{
			StringCchCat(buffer, 2048, explain);
		}

		id= 1;
		if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
		{
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

			if(m_pDialog[NRAREITEM_DLG ] == NULL)	CreateInterface( NRAREITEM_DLG );
			((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer,0,0,HITBUTTON_RAREITEM);		
		}
	}

}

// ��õ�� ���� ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMENDREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RecommendReward* pclinfo = (cltGameMsgResponse_RecommendReward*)pclMsg->cData;

	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bJewelItemNotifyReject )return ;
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)	return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[2048] = TEXT("");

	TCHAR* pTitle = GetTxtFromMgr(861);
	TCHAR* pText  = GetTxtFromMgr(862);

	TCHAR level[128]= TEXT(" ") ;
	TCHAR exp[128]= TEXT(" ") ;
	TCHAR money[128]= TEXT(" ") ;

	StringCchPrintf(level, 128, TEXT("%d"),pclinfo->siLevel);
	StringCchPrintf(exp, 128, TEXT("%d"),pclinfo->siIncFameExp);
	StringCchPrintf(money, 128, TEXT("%d"),pclinfo->siMoney);


	StringCchCopy(title, 128, pTitle);

	Nsprintf(buffer,pText,
		TEXT("user"), pclinfo->szPersonName   ,
		TEXT("level"), level   ,
		TEXT("exp"),  exp  ,
		TEXT("money"),  money  ,NULL);


	//sprintf(buffer, 
	//	pText, 
	//	pclinfo->szPersonName, pclinfo->siLevel, pclinfo->siIncFameExp, pclinfo->siMoney);


	TCHAR name[128] = TEXT("");
	if(pclinfo->clItem.GetFullNameNNum(pclItemManager, name, 128) == true)
	{
		StringCchCat(buffer, 2048, name);
	}

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);
	//	if ( g_SoundOnOffDlg.m_bFullScreenMode)
	//	{

	id =1;
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
	{
		if(m_pDialog[NRAREITEM_DLG ] == NULL)
			CreateInterface( NRAREITEM_DLG );	
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer,0,0,HITBUTTON_RECOMMEND);		
	}


	//	else
	//	{	
	//		m_pRareItemMsgDlg->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer,0,0,HITBUTTON_RECOMMEND);
	//	}


}

// ������ ���� ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_FAMELEVELREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_FameLevelReward* pclinfo = (cltGameMsgResponse_FameLevelReward*)pclMsg->cData;

	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bJewelItemNotifyReject )return ;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)	return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[2048] = TEXT("");
	TCHAR* pTitle = GetTxtFromMgr(863);
	TCHAR* pText  = GetTxtFromMgr(864);
	TCHAR exp[128]= TEXT(" ") ;
	StringCchPrintf(exp, 128, TEXT("%d"),pclinfo->siFameLevel);



	StringCchCopy(title, 128, pTitle);
	Nsprintf(buffer,pText,
		TEXT("user"),pclinfo->szPersonName    ,
		TEXT("exp"),exp    ,NULL);


	//sprintf(buffer, 
	//	pText,
	//	pclinfo->szPersonName, pclinfo->siFameLevel);

	TCHAR explain[1536]=TEXT("");
	if(pclItemManager->GetExplain(&pclinfo->clItem, explain) == TRUE)
	{
		StringCchCat(buffer, 2048, explain);
	}

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);
	//if ( g_SoundOnOffDlg.m_bFullScreenMode)
	//{

	id =1;
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
	{
		if(m_pDialog[NRAREITEM_DLG ] == NULL)
			CreateInterface( NRAREITEM_DLG );
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer);
	}

	//}

	//  else
	//{

	//	m_pRareItemMsgDlg->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer);
	//}


}

// ��� ����ǰ ���� ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_BIGWARITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BigWarItem* pclinfo = (cltGameMsgResponse_BigWarItem*)pclMsg->cData;

	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bJewelItemNotifyReject )return ;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)
		return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[256]=TEXT("");
	TCHAR* pTitle = GetTxtFromMgr(865);
	TCHAR* pText  = NULL;;



	StringCchCopy(title, 128, pTitle);

	if(pclinfo->siReason == INPUTITEMPERSON_OPTION_WAR)
	{
		pText = GetTxtFromMgr(866);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);

		pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_GIVEITEM")), 0, 0);
	}
	if(pclinfo->siReason == INPUTITEMPERSON_OPTION_SPEECIALQUEST)
	{
		pText = GetTxtFromMgr(867);


		StringCchPrintf(temp, 256, pText,
			pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_OSAKA)
	{
		pText = GetTxtFromMgr(5279);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_KANGHWADO)
	{
		pText = GetTxtFromMgr(5280);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_CRAZYEVENT)
	{
		pText = GetTxtFromMgr(5295);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_FISHSUMMON)
	{
		pText = GetTxtFromMgr(869);


		StringCchPrintf(temp, 256, pText,
			pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_FISH)
	{
		pText = GetTxtFromMgr(870);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if( pclinfo->siReason == INPUTITEMPERSON_OPTION_FARMSUMMON )
	{
		pText = GetTxtFromMgr(871);


		StringCchPrintf(temp, 256, pText,
			pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if( pclinfo->siReason == INPUTITEMPERSON_OPTION_FARM )
	{
		pText = GetTxtFromMgr(872);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if( pclinfo->siReason == INPUTITEMPERSON_OPTION_WORDASSEMBLE)
	{
		pText = GetTxtFromMgr(873);


		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if ( pclinfo->siReason == INPUTITEMPERSON_OPTION_INSTANCEMAP )
	{
		pText = GetTxtFromMgr(5186);

		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_ROULETTEGAME)
	{
		pText = GetTxtFromMgr(5503);

		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}
	else if(pclinfo->siReason == INPUTITEMPERSON_OPTION_SEVENDAYEVENT)
	{
		pText = GetTxtFromMgr(5621);

		StringCchPrintf(temp, 256, pText, pclinfo->szPersonName);
		StringCchCat(buffer, 1024, temp);
	}


	if(pclinfo->siIncFameExp)
	{
		pText = GetTxtFromMgr(874);


		StringCchPrintf(temp, 256, pText, pclinfo->siIncFameExp);
		StringCchCat(buffer, 1024, temp);
	}


	TCHAR explain[512]=TEXT("");
	if(pclItemManager->GetExplain(&pclinfo->clItem, explain) == TRUE)
	{
		StringCchCat(buffer, 1024, explain);
	}

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);


	//if ( g_SoundOnOffDlg.m_bFullScreenMode){
	id =1;
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
	{
		if(m_pDialog[NRAREITEM_DLG ] == NULL)
			CreateInterface( NRAREITEM_DLG );
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer);
	}
	//	}


	//	else
	//	{

	//		m_pRareItemMsgDlg->Set(&pclinfo->clItem, pclinfo->szPersonName, title, buffer);
	//	}

}

// �� ���� ���� �뺸 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GOODHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GoodHorse* pclinfo = (cltGameMsgResponse_GoodHorse*)pclMsg->cData;

	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bJewelItemNotifyReject )return ;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)
		return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[256] =TEXT("");
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(875);


	StringCchCopy(title, 128, pText);

	TCHAR* pname = pclHorseManager->GetHorseName(pclinfo->siHorseUnique);
	if(pname)
	{
		pText = GetTxtFromMgr(876);
		//sprintf(buffer, pText, pclinfo->szPersonName, pname); 
		Nsprintf(buffer,pText,TEXT("user"),  pclinfo->szPersonName  ,TEXT("item"),  pname  ,NULL);
		StringCchCat(buffer, 1024, temp);
		if(pclinfo->siIncFameExp)
		{
			pText = GetTxtFromMgr(877);
			StringCchPrintf(temp, 256, pText,pclinfo->siIncFameExp);
			StringCchCat(buffer, 1024, temp);
		}
	}
	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);
	//if ( g_SoundOnOffDlg.m_bFullScreenMode){
	id =1;
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
	{	
		if(m_pDialog[NRAREITEM_DLG ] == NULL)
			CreateInterface( NRAREITEM_DLG );
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(NULL, pclinfo->szPersonName, title, buffer, pclinfo->siHorseUnique);

	}


	//	else
	//	{

	//		m_pRareItemMsgDlg->Set(NULL, pclinfo->szPersonName, title, buffer, pclinfo->siHorseUnique);
	//	}


}

//// [����] 2�� ��í ������ ź���ҳ�
//void cltClient:: DoMsg_GAMEMSG_RESPONSE_TANWANGGIRL(cltMsg* pclMsg, SI32 id){
//
//
//	
//}
//KHY - 1001 - ��µ��� 5���� ���� ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_NOADDHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NoAddHorse* pclinfo = (cltGameMsgResponse_NoAddHorse*)pclMsg->cData;

	cltClient*  pclclint = (cltClient*)pclClient;

	TCHAR* pTitle = GetTxtFromMgr(1618);
	TCHAR* pText = GetTxtFromMgr(7202);

	if(pclinfo->siResult == 0)
	{
		m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle,pText);
	}
}
// ��� ��ȯ��
void cltClient::DoMsg_GAMEMSG_RESPONSE_HIGHSUMMON(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HighSummon* pclinfo = (cltGameMsgResponse_HighSummon*)pclMsg->cData;


	if ( !bReceiveMyCharAllInfoSwitch ) return ;

	if(g_SoundOnOffDlg.m_bSummonEvolveNotifyReject )return ;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)
		return ;

	if ( pclinfo->siSummonKind <= 0 ) return ;

	TCHAR title[128] = TEXT("");
	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[256] = TEXT("");
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(878);


	StringCchCopy(title, 128, pText);

	const TCHAR* pname = pclKindInfoSet->pclKI[pclinfo->siSummonKind]->GetName();

	if(pname)
	{
		pText = GetTxtFromMgr(879);



		//sprintf(temp, pText,  pclinfo->szPersonName, pname);
		Nsprintf(temp,pText,TEXT("user"), pclinfo->szPersonName   ,TEXT("item"),  pname  ,NULL);
		StringCchCat(buffer, 1024, temp);

		if(pclinfo->siIncFameExp)
		{
			pText = GetTxtFromMgr(877);


			StringCchPrintf(temp, 256, pText,pclinfo->siIncFameExp);
			StringCchCat(buffer, 1024, temp);
		}
	}

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);


	//if ( g_SoundOnOffDlg.m_bFullScreenMode){
	id =1;
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() > INIT_LEVEL)
	{
		if(m_pDialog[NRAREITEM_DLG ] == NULL)
			CreateInterface( NRAREITEM_DLG );

		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->Set(NULL, pclinfo->szPersonName, title, buffer, 0,pclinfo->siSummonKind,HITBUTTON_SUMMON);

	}


	// else
	//{

	//	m_pRareItemMsgDlg->Set(NULL, pclinfo->szPersonName, title, buffer, 0,pclinfo->siSummonKind,HITBUTTON_SUMMON);

	// }

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEGENERALMEETING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageGeneralMeeting* pclinfo = (cltGameMsgResponse_VillageGeneralMeeting*)pclMsg->cData;

	cltVillageInfo* pVillageInfo = NULL;
	for( SI32 VillageUnique = 1; VillageUnique < MAX_VILLAGE_NUMBER; ++VillageUnique )
	{
		pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[VillageUnique];
		if(NULL == pVillageInfo)
		{
			continue;
		}	
	 
		pVillageInfo->clVillageVary.m_bGeneralMeetingSuggest = pclinfo->m_siVillageGeneralMeeting[VillageUnique];	
	}
	
	cltNInfoDlg* GeneralMeetingSuggestInfo = (cltNInfoDlg*)m_pDialog[ NINFO_DLG ];
	if( false == GeneralMeetingSuggestInfo->IsShow() )
	{
		GeneralMeetingSuggestInfo->Show();
		//CreateInterface( NINFO_DLG );
	}

	if(GeneralMeetingSuggestInfo)
		GeneralMeetingSuggestInfo->GeneralMeetingSuggestInfo();
}

// ���� �� ���� �뺸.  
void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEDETAILINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageDetailInfo* pclinfo = (cltGameMsgResponse_VillageDetailInfo*)pclMsg->cData;

	if ( m_pDialog[ NINFO_DLG ] )
	{
		((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg3->ShowInfo(pclinfo);

		//((CNVillageDetailInfo*)m_pDialog[ NVILLAGEDETAILINFO_DLG ])->ShowInfo(pclinfo);
	}
	if ( m_pDialog[ NGOONZUSIEGE_DLG] )
	{
		((CNGoonzuSiegeDlg*)m_pDialog[NGOONZUSIEGE_DLG])->m_pVillageRankDlg->ShowRank(pclinfo);
	}
}


// ���� ��� �뺸. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SKILLMASTERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SkillMasterList* pclinfo = (cltGameMsgResponse_SkillMasterList*)pclMsg->cData;


	// ������ ���� ����� �ʱ�ȭ�Ѵ�. 
	if ( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ NMASTERINFO_DLG ] )
		((CNMasterInfo*)m_pDialog[ NMASTERINFO_DLG ])->clMasterInfo[pclinfo->siSkillUnique].Init();
	else
		pclMasterManager->clMasterInfo[pclinfo->siSkillUnique].Init();


	// ���ο� ���� ������� ������Ʈ �Ѵ�. 
	for(SI32 i = 0;i < pclinfo->siDataNum;i++)
	{
		if ( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ NMASTERINFO_DLG ] )
			((CNMasterInfo*)m_pDialog[ NMASTERINFO_DLG ])->clMasterInfo[pclinfo->siSkillUnique].clUnit[i].Set(&pclinfo->clUnit[i]);
		else
			pclMasterManager->clMasterInfo[pclinfo->siSkillUnique].clUnit[i].Set(&pclinfo->clUnit[i]);
	}
	// ���� ����� ǥ���Ѵ�. 
	if ( g_SoundOnOffDlg.m_bFullScreenMode && m_pDialog[ NMASTERINFO_DLG ]) 
		((CNMasterInfo*)m_pDialog[ NMASTERINFO_DLG ])->ShowMasterList(pclinfo->siSkillUnique);
}

// �α��� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICELOGIN(cltMsg* pclMsg, SI32 id)
{
	bLoginNotice = true ;
}

// ���� ���� ���� ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ENEMYCAPTURE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EnemyCapture* pclinfo = (cltGameMsgResponse_EnemyCapture*)pclMsg->cData;

	if(pclinfo->siVillageUnique < 0 || pclinfo->siVillageUnique >= MAX_VILLAGE_NUMBER)	return;

	if(pclVillageManager->pclVillageInfo[pclinfo->siVillageUnique])
	{
		pclVillageManager->pclVillageInfo[pclinfo->siVillageUnique]->bEnemyCaptureSwitch = pclinfo->bCapture;
	}
}

// ���� ��� ���� ���� ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ENEMYCAPTUREALL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EnemyCaptureAll* pclinfo = (cltGameMsgResponse_EnemyCaptureAll*)pclMsg->cData;

	SI32 i, j;
	for(i = 0;i < 3;i++)
	{
		SI32 data = pclinfo->siBit[i];

		for(j = 0; j < 32;j++)
		{
			bool bcapture = data & 1;
			SI32 villageunique = i * 32 + j;

			if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)	continue;

			if(pclVillageManager->pclVillageInfo[villageunique])
			{
				pclVillageManager->pclVillageInfo[villageunique]->bEnemyCaptureSwitch = bcapture;
			}

			data = (data >> 1);

		}

	}



}

// ���� ����Ʈ ó��. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ASKLIST(cltMsg* pclMsg, SI32 id)
{
	/*cltGameMsgResponse_AskList* pclinfo = (cltGameMsgResponse_AskList*)pclMsg->cData;

	for(SI32 i = 0;i < MAX_RESPONSE_ASK_LIST;i++)
	{
	if(pclinfo->clList[i].siCharUnique == 0)continue;

	pclAskManager->Add(pclinfo->clList[i].siCharUnique, pclinfo->clList[i].siPersonID, pclinfo->clList[i].szAskPersonName, pclinfo->clList[i].szAskText);

	pclAskManager->bUpdateSwitch = true;
	}*/

}


// ���� ó��. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_NEWS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_News* pclinfo = (cltGameMsgResponse_News*)pclMsg->cData;

	// �ڸ����� ó���Ѵ�.
	TCHAR buffer[128];

	switch( pclinfo->siNewsKind )
	{
	case CAPTIONKIND_GUILD:
		StringCchPrintf(buffer, 128,TEXT("[%s]%s"), pclinfo->szNewspaperName,  pclinfo->szNewsTitle );
		break;
	default:
		StringCchPrintf(buffer, 128,TEXT("%s[%s]"), pclinfo->szNewsTitle, pclinfo->szNewspaperName);
		break;
	}


	if ( pclinfo->siNewsKind == CAPTIONKIND_NEWSCHAT )
	{
		g_PromptMgr.Set(buffer, pclinfo->szNewURL, 2, RGB(255, 255, 0));
	}
	else if( pclinfo->siNewsKind == CAPTIONKIND_COLORNEWSCHAT )
	{
		g_PromptMgr.Set(buffer, pclinfo->szNewURL, 2, RGB( 245,150,200 ));
	}
	else
	{
		g_PromptMgr.Set(buffer, pclinfo->szNewURL, 2, RGB(250, 250, 250));
	}

	// ��������� ���θ� ǥ���Ѵ�. 
	//bBroadcastSwitch	= pclinfo->bBroadcastSwitch;
	//	g_ChatStatusBar.SetBroadCastButton(bBroadcastSwitch);

}

// ����� �� �ֱ� ó�� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GMGIVEMONEY(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_GMGiveMoney* pclinfo = (cltGameMsgResponse_GMGiveMoney*)pclMsg->cData;

	TCHAR Nbuffer[512]=TEXT(" ");
	TCHAR money[128]= TEXT(" ") ;
	TCHAR* pTitle = GetTxtFromMgr(880);
	TCHAR* pText = GetTxtFromMgr(881);
	StringCchPrintf(money, 128, TEXT("%d"),pclinfo->siMoney);
	Nsprintf(Nbuffer,pText,TEXT("user"),  pclinfo->szPersonName  ,TEXT("money"), money   ,NULL);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle,Nbuffer);


	//m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclinfo->szPersonName, pclinfo->siMoney);

}

// ��ǰ ���� ���� ó��. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PRODUCTPRICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ProductPrice* pclinfo = (cltGameMsgResponse_ProductPrice*)pclMsg->cData;

	cltClient* pclclient = (cltClient*)pclClient;

	// ���� ������ ���ݰ����ڿ��� �����Ѵ�. 
	pclItemManager->SetCurrentPrice(pclinfo->siItemUnique, pclinfo->siPrice, 1, true);

	switch( pclinfo->siDialogID )
	{
	case NMANUFACTURENPC_DLG:
		{
			CNManufactureNPCDlg* pDialog = (CNManufactureNPCDlg*)pclclient->m_pDialog[NMANUFACTURENPC_DLG];

			if ( pDialog )
			{
				pDialog->SetMenuFactureFee( pclinfo->siPrice );
			}
		}
		break;
	default:
		break;
	}


}

// ����� ���� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_USERCHARINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UserCharInfo* pclinfo = (cltGameMsgResponse_UserCharInfo*)pclMsg->cData;

	if(pclinfo->siPersonID == 0)
	{
		TCHAR* pTitle = GetTxtFromMgr(882);
		TCHAR* pText = GetTxtFromMgr(883);


		m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
	}
	else
	{
		TCHAR* pmapname = pclMapManager->GetMapName(pclinfo->siMapIndex);
		if(pmapname)
		{
			TCHAR* pTitle = GetTxtFromMgr(882);
			TCHAR* pText  = GetTxtFromMgr(884);
			TCHAR* pText2 = GetTxtFromMgr(885);
			TCHAR* pText3 = GetTxtFromMgr(886);

			TCHAR residentvillage[50];
			TCHAR* tmpbuf = NULL;
			memset(residentvillage, 0, sizeof(residentvillage) );

			// ���� ����(�ѱ۸�)
			tmpbuf = pclClient->pclVillageManager->GetName( pclinfo->siVillageUnique );
			if(tmpbuf == NULL )
				tmpbuf = GetTxtFromMgr(1287);	// TEXT("����")
			StringCchPrintf(residentvillage, 50, TEXT("%s"), tmpbuf);


			// ��ȯ�� ����
			TCHAR summoninfo[1024];
			memset(summoninfo, 0, sizeof(summoninfo));
			for(SI16 i=0; i<MAX_SUMMON_OWN; i++)
			{
				cltSummon *pclSummon = &(pclinfo->clSummonInfo.clSummon[i]);

				if(pclSummon && pclKindInfoSet->IsValidKind(pclSummon->siKind) )
				{
					//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
					cltKindInfo* pclki = NULL;
					if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
					{
						pclki = pclClient->pclKindInfoSet->pclSummonKI[pclSummon->siKind];
					}
					else
					{
						pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
					}

					if(pclki)
					{
						StringCchPrintf( summoninfo, 1024, TEXT("%s\r\n%d: %s"), summoninfo, i+1, pclki->GetName() );                        
					}
				}
			}

			if(pclinfo->clSummonInfo.HaveSummon() == false)
				StringCchPrintf( summoninfo, 1024, TEXT("%s"), GetTxtFromMgr(1287) );	// ����


			TCHAR* pTmpText = NULL;
			TCHAR* pTmpText2 = NULL;
		
			
			// ��� ���� ǥ��
			TCHAR warnmode[128];
			memset(warnmode, 0, sizeof(warnmode) );

			pTmpText = GetTxtFromMgr(5232); // ��� ���� %dȸ
			pTmpText2 = GetTxtFromMgr(5233); // %d�ϰ� �� ��
			switch( pclinfo->m_clUserBlockLog[0].m_uiWarnMode )
			{
			case sDBResponse_BlockUser::WARNING_FIRST:
				StringCchPrintf( warnmode, 128, TEXT("%s"), pTmpText);
				StringCchPrintf( warnmode, 128, warnmode, 1 );
				break;
			case sDBResponse_BlockUser::BLOCK_FOR_5_DAYS:
				StringCchPrintf( warnmode, 128, TEXT("%s %s"), pTmpText, pTmpText2);
				StringCchPrintf( warnmode, 128, warnmode, 2, 5 );
				break;
			case sDBResponse_BlockUser::BLOCK_FOR_10_DAYS:
				StringCchPrintf( warnmode, 128, TEXT("%s %s"), pTmpText, pTmpText2);
				StringCchPrintf( warnmode, 128, warnmode, 3, 10 );
				break;
			case sDBResponse_BlockUser::BLOCK_FOR_FOREVER:
				pTmpText2 = GetTxtFromMgr(5234);
				StringCchPrintf( warnmode, 128, TEXT("%s %s"), pTmpText, pTmpText2);
				StringCchPrintf( warnmode, 128, warnmode, 4, 5 );
				break;
			default:
				StringCchPrintf( warnmode, 128, TEXT("%s"), GetTxtFromMgr(1287) );	// ����
				break;
			}

			TCHAR blockmode[512] = TEXT("");
			TCHAR tempblockmode[256] = TEXT("");
			switch ( pclinfo->m_clUserBlockLog[0].m_uiBlockMode )
			{
			case 0:
				StringCchPrintf(tempblockmode, 256, TEXT("%s\r\n"),GetTxtFromMgr(1287)) ;
				break;
			case 1:
				StringCchPrintf(tempblockmode, 256, TEXT("%s\r\n"),GetTxtFromMgr(5287)) ;
				break;
			case 2:
				StringCchPrintf(tempblockmode, 256, TEXT("%s\r\n"),GetTxtFromMgr(5234)) ;
				break;
			}
			StringCchCat(blockmode, 512, tempblockmode);

			StringCchPrintf(tempblockmode, 256, GetTxtFromMgr(5288),pclinfo->m_clUserBlockLog[0].m_szStartDate);
			StringCchCat(blockmode, 512, tempblockmode);
			StringCchPrintf(tempblockmode, 256, GetTxtFromMgr(5289),pclinfo->m_clUserBlockLog[0].m_szEndDate);
			StringCchCat(blockmode, 512, tempblockmode);
			StringCchPrintf(tempblockmode, 256, GetTxtFromMgr(5290),pclinfo->m_clUserBlockLog[0].m_szBlockReason);
			StringCchCat(blockmode, 512, tempblockmode);

			TCHAR szBlockLog[4096]		= TEXT("");
			TCHAR szBlockLogTemp[512]	= TEXT("");

			for ( UINT unIndex=1; unIndex<MAX_BLOCKLOG_NUM; ++unIndex )
			{
				StringCchPrintf( szBlockLogTemp, 512, GetTxtFromMgr(5288), pclinfo->m_clUserBlockLog[unIndex].m_szStartDate );
				StringCchCat( szBlockLog, 4096, szBlockLogTemp );

				StringCchPrintf( szBlockLogTemp, 512, GetTxtFromMgr(5289), pclinfo->m_clUserBlockLog[unIndex].m_szEndDate );
				StringCchCat( szBlockLog, 4096, szBlockLogTemp );

				StringCchPrintf( szBlockLogTemp, 512, GetTxtFromMgr(5290), pclinfo->m_clUserBlockLog[unIndex].m_szBlockReason );
				StringCchCat( szBlockLog, 4096, szBlockLogTemp );
			}

			TCHAR *buffer = new TCHAR[ 51200 ];

			StringCchPrintf(buffer, 51200,
				pText,
				pclinfo->szAccountID, TEXT("************"), pclinfo->siPersonID,
				pclinfo->siCharUnique,
				((pclinfo->bConnectSwitch) ? pText2 : pText3),
				pclinfo->szMakeDate, pclinfo->siLevel, pclinfo->siMoney, pclinfo->clTotalMoney.itMoney,
				pclinfo->clBankMoney.itMoney, pclinfo->siWorldTradeMoney, pmapname, pclinfo->siX, pclinfo->siY,
				pclinfo->siGoonzuFriends, pclinfo->szOtherPersonName1, pclinfo->szOtherPersonName2, 
				pclinfo->szRecommender,pclinfo->szFatherName,pclinfo->siStudentLevel,
				summoninfo, residentvillage, warnmode, blockmode,szBlockLog );

			g_ErrorMsg.BigSet(pTitle, buffer );
			SAFE_DELETE_A( buffer );
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_USERCHARITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UserCharItemInfo* pclinfo = (cltGameMsgResponse_UserCharItemInfo*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	TCHAR*	pszTitle		= GetTxtFromMgr(1927);

	// ���� ������ ����
	UI32	uiIndex			= 0;
	TCHAR*	pszGetText		= NULL;
	TCHAR	szExplain[512]	= TEXT("");
	TCHAR	szPrint[512]	= TEXT("");

	TCHAR*	pszItemText		= NULL;

	pszItemText = new TCHAR[MAX_BIG_ERRORMSG_NUM];
	if ( NULL == pszItemText )
	{
		return;
	}

	ZeroMemory( pszItemText, (sizeof(TCHAR)*MAX_BIG_ERRORMSG_NUM) );

	// �κ��丮 ������
	for ( uiIndex=0; uiIndex<MAX_ITEM_PER_PERSON; ++uiIndex )
	{
		ZeroMemory( szExplain,	sizeof(szExplain) );
		ZeroMemory( szPrint,	sizeof(szPrint) );

		pclItemManager->GetExplain(&pclinfo->m_clItem[uiIndex], szExplain);

		StringCchPrintf(szPrint, 512, TEXT("%d:%s\r\n"), uiIndex, szExplain);
		StringCchCat(pszItemText, MAX_BIG_ERRORMSG_NUM, szPrint);
	}

	g_ErrorMsg.BigSet( pszTitle, pszItemText );

	SAFE_DELETE_ARRAY( pszItemText );

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_USERCHARITEMINFO2(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_UserCharItemInfo2* pclinfo = (cltGameMsgResponse_UserCharItemInfo2*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	// ���� ������ ����
	UI32	uiIndex								= 0;
	TCHAR*	pszGetText							= NULL;
	TCHAR	szExplain[512]						= TEXT("");
	TCHAR	szPrint[512]						= TEXT("");

	TCHAR*	pszItemText		= NULL;

	pszItemText = new TCHAR[MAX_BIG_ERRORMSG_NUM];
	if ( NULL == pszItemText )
	{
		return;
	}

	ZeroMemory( pszItemText, (sizeof(TCHAR)*MAX_BIG_ERRORMSG_NUM) );

	// ���� ���� 
	ZeroMemory( szPrint, sizeof(szPrint) );

	StringCchPrintf( szPrint, 512, TEXT("%s\r\n"), GetTxtFromMgr(7921) );
	StringCchCat( pszItemText, MAX_BIG_ERRORMSG_NUM, szPrint );

	for ( uiIndex=0; uiIndex<MAX_ITEM_SPACE_BOX; ++uiIndex )
	{
		ZeroMemory( szExplain,	sizeof(szExplain) );
		ZeroMemory( szPrint,	sizeof(szPrint) );

		pclItemManager->GetExplain(&pclinfo->m_clSpaceBox[uiIndex], szExplain);

		StringCchPrintf(szPrint, 512, TEXT("%d:%s\r\n"), uiIndex, szExplain);
		StringCchCat(pszItemText, MAX_BIG_ERRORMSG_NUM, szPrint);
	}

	// ���� ����
	ZeroMemory( szPrint, sizeof(szPrint) );

	StringCchPrintf( szPrint, 512, TEXT("%s\r\n"), GetTxtFromMgr(7922) );
	StringCchCat( pszItemText, MAX_BIG_ERRORMSG_NUM, szPrint );

	for ( uiIndex=0; uiIndex<MAX_ITEM_TREASURE_BOX; ++uiIndex )
	{
		ZeroMemory( szExplain,	sizeof(szExplain) );
		ZeroMemory( szPrint,	sizeof(szPrint) );

		pclItemManager->GetExplain(&pclinfo->m_clTreasureBox[uiIndex], szExplain);

		StringCchPrintf(szPrint, 512, TEXT("%d:%s\r\n"), uiIndex, szExplain);
		StringCchCat(pszItemText, MAX_BIG_ERRORMSG_NUM, szPrint);
	}

	g_ErrorMsg.BigAppend( pszItemText );

	SAFE_DELETE_ARRAY( pszItemText );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ACCOUNTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AccountInfo* pclinfo = (cltGameMsgResponse_AccountInfo*)pclMsg->cData;

	TCHAR* pTitle = GetTxtFromMgr(887);
	TCHAR* pText = GetTxtFromMgr(888);


	g_ErrorMsg.Set( false, pTitle, pText,
		pclinfo->szAccountID, pclinfo->szPersonName1, pclinfo->szPersonName2, pclinfo->szPersonName3 );
}

// NPC��ġ�� �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_NPCPOS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NPCPos* pclinfo = (cltGameMsgResponse_NPCPos*)pclMsg->cData;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if ( pclinfo->siKind == pclClient->GetUniqueFromHash(TEXT("KIND_INVESTMENT")) /*||
			pclinfo->siKind == pclClient->GetUniqueFromHash(TEXT("KIND_FANPRIEST"))*/ ) // ���̱輱�� �� ��ä���� ����ó��
		{
			TCHAR* pText = NULL;
							
			((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->SetRegenPos(pclinfo->uiMapIndex,pclinfo->siMapNumber);

			if (pclinfo->siKind == pclClient->GetUniqueFromHash(TEXT("KIND_INVESTMENT")) )
			{
				pText = GetTxtFromMgr(898);
				
				if( ((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
				{
					((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->AddRegenPos(pText);
				}
				if( ((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
				{
					((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->AddRegenPos(pText);
				}
			}
			//else if ( pclinfo->siKind == pclClient->GetUniqueFromHash(TEXT("KIND_FANPRIEST")) )
			//{
			//	pText = GetTxtFromMgr(899);

			//	if( ((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
			//	{
			//		((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->AddRegenPos(pText);
			//	}
			//	if( ((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
			//	{
			//		((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->AddRegenPos(pText);
			//	}
			//}
		}
		else
		{
			
			if( ((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
			{
				((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg4->SetRegenPos(pclinfo->uiMapIndex,pclinfo->siMapNumber);
			}
			
			if( ((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->IsSelectedNPC(pclinfo->siKind) )
			{
				((cltNInfoDlg*)m_pDialog[ NINFO_SUB_DLG ])->m_pTabDlg4->SetRegenPos(pclinfo->uiMapIndex,pclinfo->siMapNumber);
			}
		}
	}
}

// �Ӹ����� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_HEADCHAT(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_HeadChat* pclchat = (cltGameMsgResponse_HeadChat*)pclMsg->cData;

	if ( g_SoundOnOffDlg.m_bNotifyHeadChat == true ) return ; // ������ �� �޴´�.

	// ��ǳ���� ����. 
	id = cltCharCommon::CharUniqueInfo[pclchat->siCharUnique];
	if(pclCM->IsValidID(id))
	{
		cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];
		// ���λ��� �ÿ��� ����â�� ���� ����.
		if( pclChar->bPersonalShopSwitch == true )	return;
		// ������û �ÿ��� ����â�� ��� �� ����.
		if( pclChar->bRepairShopSwitch == true )	return; 

		pclChar->pclDrawChat->Set(pclDrawChatSurface, pclchat->szText, true, ADVERTISE_CHATTING);
	}
}

// ä�� ä�� ���� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_MakeSecretChatChannel* pclinfo = (cltGameMsgResponse_MakeSecretChatChannel*)pclMsg->cData;


	if(pclinfo->siCharUnique > 0)
	{
		if ( pclinfo->szChatBuffer )
			m_pNPrivateChatDlgMgr->Push( pclinfo->bGameMaster, pclinfo->siCharUnique, pclinfo->szName, pclinfo->szChatBuffer,pclinfo->siLevel,pclinfo->szAccountID );
		else
			m_pNPrivateChatDlgMgr->Push( pclinfo->bGameMaster, pclinfo->siCharUnique, pclinfo->szName, TEXT(""),pclinfo->siLevel,pclinfo->szAccountID );
	}
	else
	{
		TCHAR* pTitle = GetTxtFromMgr(900);
		TCHAR* pText = GetTxtFromMgr(901);
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ACCEPTSECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id) //[����]
{
	//// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_AcceptSecretChatChannel* pclinfo = (cltGameMsgResponse_AcceptSecretChatChannel*)pclMsg->cData;
	
	if(!pclinfo->bAccept)  // ���� �ź�
	{
		TCHAR buffer[255];
        
		TCHAR* pTitle = GetTxtFromMgr(5753);
		TCHAR* pText = GetTxtFromMgr(5747);
		StringCchPrintf(buffer, 255, pText, pclinfo->szName);
		// ����� ��ȭâ�� �źεǾ��� �޽��� ����
		bool bSuccess = m_pNPrivateChatDlgMgr->SetAcceptRefuseMsg(pclinfo->siCharUnique,pclinfo->szName,buffer);
		
		if(!bSuccess)
            m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
	}
	else // ���� ����
	{
				
		RequestSecretChatByCharUnique(pclinfo->siCharUnique);
	}

}

// ä�� ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHAT(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_Chat* pclchat = (cltGameMsgResponse_Chat*)pclMsg->cData;

	if( pclchat->PlayerNameLength >= MAX_PLAYER_NAME ) return;

	// �޽����� �м��ؾ� �Ѵ�. 
	TCHAR playername[MAX_PLAYER_NAME + 10];
	TCHAR chattext[ 256 ];
	TCHAR *buffer;

	memcpy( chattext, pclchat->szChatText, 256 );
	chattext[ 255 ] = NULL;

	// �̸��� ���Ѵ�. 
	memcpy(playername, chattext, pclchat->PlayerNameLength);
	playername[pclchat->PlayerNameLength] = NULL;

	// ä�� ������ ���Ѵ�. 
	buffer = &chattext[pclchat->PlayerNameLength];

	id = cltCharCommon::CharUniqueInfo[pclchat->siCharUnique];
	SI16 charunique = pclchat->siCharUnique;


	if(pclchat->siMode == CHATMODE_SECRET)
	{
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{
			m_pNPrivateChatDlgMgr->Push(pclchat->bGameMaster, pclchat->siCharUnique, playername, buffer,pclchat->siLevel);
		}
	}
	else if(pclchat->siMode == CHATMODE_HOME)
	{
		// ä��â�� ����. 
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{
			((CNResidentsDlg*)m_pDialog[ NRESIDENTS_DLG ])->ResidentsChatRecv( playername, buffer );
			((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->ChatRecv( playername, buffer, pclchat->bGameMaster,TAB_MODE_RESIDENTSCHAT );
		}
	}

	/*	else if(pclchat->siMode == CHATMODE_PARTY)
	{
	m_pRichEditChatMgrDlg->PartyChatRecv( playername, buffer );		
	m_pRichEditChatMgrDlg->ChatStore( playername, buffer, TAB_MODE_PARTYCHAT );
	}
	*/
	//_LEON_GUILD_CHAT
	//#if defined(_DEBUG)
	else if(pclchat->siMode == CHATMODE_GUILD)
	{
		// ä��â�� ����. 
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{

			((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->ChatRecv( playername, buffer, pclchat->bGameMaster,TAB_MODE_GUILDCHAT );
		}
	}
	//#endif
	else if ( pclchat->siMode == CHATMODE_PARTY )
	{
		if(g_SoundOnOffDlg.m_bFullScreenMode)
		{
			if( m_pDialog[ NPARTY_DLG ] )
			{
				if ( ((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->IsPartyUser(pclCM->CR[1]->GetCharUnique() ) )
				{

					((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->AddChat( playername, buffer);
					((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->ChatRecv( playername, buffer, pclchat->bGameMaster, TAB_MODE_PARTYCHAT);

				}
			}
		}
	}
	else
	{
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{

			TCHAR *pText =  GetTxtFromMgr(1321);

			if(_tcsncmp(buffer,pText,10)==0)    //-�¾� �����ؾ� ��
			{

			}
			else

				((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->ChatRecv( playername, buffer , pclchat->bGameMaster);

			if( g_SoundOnOffDlg.m_bMaxWindowMode == false )
			{
				if(_tcsncmp(buffer,pText,10)==0)    //-�¾� �����ؾ� ��
				{

				}
			}
		}
		else
		{
			TCHAR *pText =  GetTxtFromMgr(1321);

			if(_tcsncmp(buffer,pText,10)==0)    //-�¾� �����ؾ� ��
			{

			}

		}

		// ��ǳ���� ����. 
		if(pclCM->IsValidID(id))
		{
			cltCharClient* pclChar = (cltCharClient*)pclCM->CR[id];

			if(pclchat->siMode == CHATMODE_NORMAL)
			{
				pclChar->pclDrawChat->Set(pclDrawChatSurface, buffer, false, USER_CHATTING);
			}
			else
			{
				if ( pclchat->siMode == CHATMODE_SYSTEM && pclchat->siSystemTxt > 0 && pclchat->siSystemTxt < MAX_TEXTMGR_NUM )
					buffer = GetTxtFromMgr(pclchat->siSystemTxt);

				pclChar->pclDrawChat->Set(pclDrawChatSurface, buffer, false, PRODUCTION_CHATTING);
			}
		}
	}
}

// ���� ���� �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_USERNUM(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_UserNum* pclInfo = (cltGameMsgResponse_UserNum*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch)return ;

	/*	TCHAR buffer[256];
	sprintf(buffer, TEXT("����:%d/%d"), pclInfo->siCurUserNum, pclInfo->siMaxUserNum);
	g_ChatStatusBar.SetText( buffer, 2 );
	*/	

	// DB�̻� ���� Ȯ��. 
	if(pclInfo->bDBFailSwitch == false)
	{
		bDBFailSwitch = false;
	}
	else
	{
		bDBFailSwitch = true;
	}
}


// �Ӹ� ä�� ����� �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SECRETCHATRESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SecretChatResult* pclInfo = (cltGameMsgResponse_SecretChatResult*)pclMsg->cData;


	TCHAR buffer[256];
	switch(pclInfo->siResult)
	{
	case SECRETCHAT_SUCCESS:
		{
			TCHAR* pText = GetTxtFromMgr(902);


			StringCchPrintf(buffer, 256, pText, pclInfo->szName);
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_SUCCESS")), 0, 0);

			pclMessage->SetMsg(buffer);
		}
		break;
	case SECRETCHAT_FAIL_INVALIDNAME:
		{
			TCHAR* pText = GetTxtFromMgr(903);

			StringCchPrintf(buffer, 256, pText, pclInfo->szName);
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			pclMessage->SetMsg(buffer);
		}
		break;
	case SECRETCHAT_FAIL:
		{
			TCHAR* pText = GetTxtFromMgr(904);

			StringCchPrintf(buffer, 256, pText, pclInfo->szName);
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			pclMessage->SetMsg(buffer);
		}
		break;
	case SECRETCHAT_FAIL_NOTUSER:
		{
			m_pNPrivateChatDlgMgr->FaildPush(pclInfo->siCharUnique);
			
		}
		break;
	default:
		MsgBox(TEXT("fdsf83jf"), TEXT("fds83jf:%d"), pclInfo->siResult);
		return ;
	}

}

// ������ ������ �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVERINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ServerInfo* pclInfo = (cltGameMsgResponse_ServerInfo*)pclMsg->cData;

	// ���� ������ �����Ѵ�. 
	if(siServiceArea != pclInfo->siServiceArea)
	{
		return ;
		//		SetServiceArea(pclInfo->siServiceArea);
	}

	// ���� �����̶� ���� �ڵ尡 �ٸ��� �ȵȴ�.
	if(g_siServiceAreaCode != 0 && g_siServiceAreaCode != pclInfo->siServiceArea )
	{
		return ;
	}

	siServerUnique										= pclInfo->siServerUnique;
	bItemMallUseSwitch									= pclInfo->bItemMallUseSwitch;
	bVillageWarSwitch									= pclInfo->bVillageWarSwitch;
	bBonusTimeSwitch									= pclInfo->bBonusTimeSwitch;
	bBonus2TimeSwitch									= pclInfo->bBonus2TimeSwitch;
	bSpecialQuestBonusTimeSwitch						= pclInfo->bSpecialQuestBonusTimeSwitch;
	bBroadcastSwitch									= pclInfo->bBroadcastSwitch;
	siBestVillageLevel									= pclInfo->siBestVillageLevel;
	pclItemManager->clItemStatistic.siNPCPriceRate		= pclInfo->siNPCPriceRate;
	pclItemManager->clItemStatistic.siItemPriceIndex	= pclInfo->siItemPriceIndex;

	for(SI32 i = 0; i < MAX_EVENT_NUMBER;i++)
	{
		bEventSwitch[i]		= pclInfo->bEventSwitch[i];
	}

	siMinimumTeacherLevel = pclInfo->siMinimumTeacherLevel;

	// [��ȣ_NHN->NDOORS] Ŭ���̾�Ʈ������ �̹� �������̸� ������ �����Ƿ� �� �����ʹ� ���� �ʴ´�.
	//siServiceAge			= pclInfo->siServiceAge;

	siEnablePVP				= pclInfo->siEnablePVP;

	bAutoUnblock			= pclInfo->bAutoUnblockMode;
	bVoteCampaign			= pclInfo->bVoteCampaign;

	bReceiveServerInfoSwitch = true;	// ������ ������ �޾����� Ȯ���Ѵ�. 

	for ( SI32 siCount=0; siCount<EVENT_TOGGLE_SWITCH_MAX; ++siCount )
	{
		bEventToggleSwitch[siCount]	= pclInfo->bEventToggleSwitch[siCount];
	}
}


// �������� ���۰� ���Ḧ �˸���.
void cltClient::DoMsg_GAMEMSG_RESPONSE_WARVILLAGE(cltMsg* pclMsg, SI32 id)
{
	cltClient * pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_WarVillage* pclInfo = (cltGameMsgResponse_WarVillage*)pclMsg->cData;

	bVillageWarSwitch = pclInfo->bVillageWarSwitch;

	if(bVillageWarSwitch)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_VILLAGEWARBREAK")), 0, 0);
	}

	SI32 myHomeid = pclClient->pclCM->CR[1]->pclCI->clBI.siHomeVillage;


	for( SI32 i = 0; i < MAX_VILLAGE_NUMBER; i++)
	{
	
		if( pclClient->pclVillageManager->siNowWarVillage[i] > 0)
		{

			if( pclClient->pclVillageManager->siNowWarVillage[i] == myHomeid)
			{
				if(bVillageWarSwitch)
					pclclient->m_pVillageWarNotice->Set( VILLAGEWAR_NOTICE_ATTACK );
				else
					pclclient->m_pVillageWarNotice->Set( VILLAGEWAR_NOTICE_DEFENCE );

				return;
			}
			else if( i == myHomeid)
			{
				if(bVillageWarSwitch)
					pclclient->m_pVillageWarNotice->Set( VILLAGEWAR_NOTICE_ATTACK );
				else
					pclclient->m_pVillageWarNotice->Set( VILLAGEWAR_NOTICE_DEFENCE );
				return;
			}

		}
	}
}

// ���ʽ� Ÿ���� ���۰� ���Ḧ �˸���.
void cltClient::DoMsg_GAMEMSG_RESPONSE_BONUSTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BonusTime* pclInfo = (cltGameMsgResponse_BonusTime*)pclMsg->cData;

	switch(pclInfo->siBonusTimeMode)
	{
	case BONUSTIMEMODE_NORMAL:
		bBonusTimeSwitch				= pclInfo->bBonusTimeSwitch;
		break;
	case BONUSTIMEMODE_MAKE:
		bBonus2TimeSwitch				= pclInfo->bBonusTimeSwitch;
		break;
	case BONUSTIMEMODE_SPECIALQUEST:
		bSpecialQuestBonusTimeSwitch	= pclInfo->bBonusTimeSwitch;
		break;
	}


	if(pclInfo->bBonusTimeSwitch)
	{
		//cyj ���ʽ�Ÿ�� ���� ������ ������ ���� ����
		//PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_VILLAGEWARBREAK")), 0, 0);
	}
}


// �Ұ��縮 ��� ������ ���� 
//void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTINGREWARD(cltMsg* pclMsg, SI32 id)
//{
//	cltGameMsgResponse_HuntingReward* pclInfo = (cltGameMsgResponse_HuntingReward*)pclMsg->cData;
//
//
//	TCHAR buffer[512] = TEXT("");
//	TCHAR temp[256];
//	TCHAR* pText = NULL;
//
//	pText = GetTxtFromMgr(905);
//
//
//	StringCchPrintf(temp, 256, pText, pclInfo->siExp);
//	StringCchCat(buffer, 512, temp);
//
//	if(pclInfo->siFameExp)
//	{
//		pText = GetTxtFromMgr(906);
//
//		StringCchPrintf(temp, 256, pText, pclInfo->siFameExp);
//		StringCchCat(buffer, 512, temp);
//	}
//
//	NTCHARString128 strBuffer( buffer );
//
//	if( 0 < pclInfo->siRewardItemUnique && 0 < pclInfo->siRewardItemNum)
//	{
//		NTCHARString128 strText( GetTxtFromMgr(40849) );
//		NTCHARString32 strItemName( pclClient->pclItemManager->GetName(pclInfo->siRewardItemUnique) );
//		strText.Replace( TEXT("#item#"), strItemName );
//		strText.Replace( TEXT("#num#"), SI32ToString(pclInfo->siRewardItemNum) );
//		//strText.Replace( TEXT("#exp#"), SI32ToString(pclInfo->siExp) );
//
//		//strBuffer = strBuffer + strText;
//
//		StringCchCat(buffer, 512, (TCHAR*)strText);
//	}
//
//	pText = GetTxtFromMgr(907);
//
//	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, (TCHAR*)strBuffer);
//}

// �Ұ��縮 ��� ������ ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTINGREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntingReward* pclInfo = (cltGameMsgResponse_HuntingReward*)pclMsg->cData;

	TCHAR buffer[512] = TEXT("");
	TCHAR temp[256];
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(905);

	StringCchPrintf(temp, 128, pText, pclInfo->siExp);
	StringCchCat(buffer, 512, temp);

	if(pclInfo->siFameExp)
	{
		pText = GetTxtFromMgr(906);


		StringCchPrintf(temp, 128, pText, pclInfo->siFameExp);
		StringCchCat(buffer, 512, temp);
	}

	if( 0 < pclInfo->siRewardItemUnique && 0 < pclInfo->siRewardItemNum)
	{
		NTCHARString128 strText( GetTxtFromMgr(40849) );
		NTCHARString32 strItemName( pclClient->pclItemManager->GetName(pclInfo->siRewardItemUnique) );
		strText.Replace( TEXT("#item#"), strItemName );
		strText.Replace( TEXT("#num#"), SI32ToString(pclInfo->siRewardItemNum) );
		strText.Replace( TEXT("#exp#"), SI32ToString(pclInfo->siExp) );

		StringCchPrintf( buffer, 256, (TCHAR*)strText );
		//StringCchCat(buffer, 512, temp);
	}

	pText = GetTxtFromMgr(907);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, buffer );
}

// ���� ���� ���  ������ ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GOGUREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GoguReward* pclInfo = (cltGameMsgResponse_GoguReward*)pclMsg->cData;

	TCHAR buffer[512] = TEXT("");
	TCHAR temp[256];
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(905);


	StringCchPrintf(temp, 256, pText, pclInfo->siExp);
	StringCchCat(buffer, 512, temp);

	if(pclInfo->siFameExp)
	{
		pText = GetTxtFromMgr(906);


		StringCchPrintf(temp, 256, pText, pclInfo->siFameExp);
		StringCchCat(buffer, 512, temp);
	}
	if(pclInfo->siMoney)
	{
		pText = GetTxtFromMgr(908);


		StringCchPrintf(temp, 256, pText, pclInfo->siMoney);
		StringCchCat(buffer, 512, temp);
	}

	pText = GetTxtFromMgr(909);


	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText, buffer);

}

// ����ī�� ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_OSAKAREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_OsakaReward* pclInfo = (cltGameMsgResponse_OsakaReward*)pclMsg->cData;

	TCHAR buffer[512] = TEXT("");
	TCHAR temp[256];
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(905);


	StringCchPrintf(temp, 256, pText, pclInfo->siExp);
	StringCchCat(buffer, 512, temp);

	if(pclInfo->siFameExp)
	{
		pText = GetTxtFromMgr(906);


		StringCchPrintf(temp, 256, pText, pclInfo->siFameExp);
		StringCchCat(buffer, 512, temp);
	}
	if(pclInfo->siMoney)
	{
		pText = GetTxtFromMgr(908);


		StringCchPrintf(temp, 256, pText, pclInfo->siMoney);
		StringCchCat(buffer, 512, temp);
	}

	pText = GetTxtFromMgr(909);


	m_pDialog[ NOTIFYMSG_DLG ]->SetText( TEXT("����ī�� �ı� ����") , buffer);
}

// ��ȭ�� ��� ���� 
void cltClient::DoMsg_GAMEMSG_RESPONSE_KANGHWADOREWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_KanghwadoReward* pclInfo = (cltGameMsgResponse_KanghwadoReward*)pclMsg->cData;

	TCHAR buffer[512] = TEXT("");
	TCHAR temp[256];
	TCHAR* pText = NULL;

	pText = GetTxtFromMgr(905);


	StringCchPrintf(temp, 256, pText, pclInfo->siExp);
	StringCchCat(buffer, 512, temp);

	if(pclInfo->siFameExp)
	{
		pText = GetTxtFromMgr(906);


		StringCchPrintf(temp, 256, pText, pclInfo->siFameExp);
		StringCchCat(buffer, 512, temp);
	}
	if(pclInfo->siMoney)
	{
		pText = GetTxtFromMgr(908);


		StringCchPrintf(temp, 256, pText, pclInfo->siMoney);
		StringCchCat(buffer, 512, temp);
	}

	pText = GetTxtFromMgr(909);


	m_pDialog[ NOTIFYMSG_DLG ]->SetText( TEXT("��ȭ�� ��� ����") , buffer);
}

// �Ұ��縮 ��� �̺�Ʈ ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTINGINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntingInfo* pclInfo = (cltGameMsgResponse_HuntingInfo*)pclMsg->cData;

	if(pclInfo->siMode > 0 )
	{
		bHuntingEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(910);

		pclMessage->SetMsg(pText);
	}
	else if(pclInfo->siMode < 0 )
	{
		bHuntingEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(911);

		pclMessage->SetMsg(pText);
	}
	else
	{
		if ( bHuntingEventSwitch == false )
			pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EVENT_BULGASARI")), 0, 0);

		bHuntingEventSwitch = true;
		pclMessage->SetHuntEventMsg(pclInfo->siLeftSecond);

	}
}

// ���� ���� ��� �̺�Ʈ ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GOGUINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GoguInfo* pclInfo = (cltGameMsgResponse_GoguInfo*)pclMsg->cData;

	if(pclInfo->siMode > 0 )
	{
		bGoguEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(912);

		pclMessage->SetMsg(pText);
	}
	else if(pclInfo->siMode < 0 )
	{
		bGoguEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(913);

		pclMessage->SetMsg(pText);
	}
	else
	{
		if ( bGoguEventSwitch == false )
			pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EVENT_GAURI")),0,0);

		bGoguEventSwitch = true;
		pclMessage->SetGoguEventMsg(pclInfo->siLeftSecond);

	}
}

// ����ī�� �̺�Ʈ ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_OSAKAINFO(cltMsg* pclMsg, SI32 id)
{
	/*
	cltGameMsgResponse_OsakaInfo* pclInfo = (cltGameMsgResponse_OsakaInfo*)pclMsg->cData;

	switch( pclInfo->siMode )
	{
	case -1:	// ����ī�� ����
		{
			pclWarManager->SetDraw(WAR_OSAKA_LOSE);
			bOsakaEventSwitch = false;
			TCHAR* pText = GetTxtFromMgr(5319);
			pclMessage->SetMsg(pText);
		}
		break;
	case 0:	// ó�� ����
		{
			if ( bOsakaEventSwitch == false )
			{
				pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EVENT_GAURI")),0,0);
				pclWarManager->SetDraw(WAR_OSAKA_BREAK);
			}


			bOsakaEventSwitch = true;
			pclMessage->SetOsakaEventMsg(pclInfo->siLeftSecond);
			TCHAR* pText = TEXT("����ī�� ������ �����մϴ�");// GetTxtFromMgr(5320);
			pclMessage->SetMsg(pText);
		}
		break;

	case 1:	
		{
			bOsakaEventSwitch = true;
			pclMessage->SetOsakaEventMsg(pclInfo->siLeftSecond);
			TCHAR* pText = TEXT("����ī�� �ܼ����� �ı� ���Ѿ� �մϴ�!!!");

			pclMessage->SetMsg(pText);
		}
		break;
	case 2:	
		{
			bOsakaEventSwitch = true;
			pclMessage->SetOsakaEventMsg(pclInfo->siLeftSecond);
			TCHAR* pText = TEXT("����ī�� �������� �ı� ���Ѿ� �մϴ�!!!");

			pclMessage->SetMsg(pText);
		}
		break;
	case 3:	// ����ī�� �̰��
		{
			bOsakaEventSwitch = true;
			pclMessage->SetOsakaEventMsg(pclInfo->siLeftSecond);
			TCHAR* pText = TEXT("����ī���� �ı� ���Ѿ� �մϴ�!!!");//GetTxtFromMgr(5320);

			pclMessage->SetMsg(pText);
		}
		break;
	case 4:	// ����ī�� �̰��
		{
			pclWarManager->SetDraw(WAR_OSAKA_WIN);
			bOsakaEventSwitch = false;
			TCHAR* pText = GetTxtFromMgr(5320);

			pclMessage->SetMsg(pText);
		}
		break;
	case 5:	// ���� ��ɾ�� ����
		{
			bOsakaEventSwitch = false;
			//	TCHAR* pText = GetTxtFromMgr(5319);

			pclMessage->SetMsg(TEXT("��ڿ� ���� ���� �Ǿ����ϴ�"));
		}
		break;
	}
	*/
}

// ��ȭ�� ��� �̺�Ʈ ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_KANGHWADOINFO(cltMsg* pclMsg, SI32 id)
{
	/*
	cltGameMsgResponse_KanghwadoInfo* pclInfo = (cltGameMsgResponse_KanghwadoInfo*)pclMsg->cData;

	if(pclInfo->siMode > 0 )
	{
		bKanghwadoEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(912);

		pclMessage->SetMsg(TEXT("��ȭ�� �� �����߽��ϴ�"));
	}
	else if(pclInfo->siMode < 0 )
	{
		bKanghwadoEventSwitch = false;
		TCHAR* pText = GetTxtFromMgr(913);

		pclMessage->SetMsg(TEXT("��ȭ�� �� �����߽��ϴ�"));
	}
	else
	{
		if ( bKanghwadoEventSwitch == false )
			pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EVENT_GAURI")),0,0);

		bKanghwadoEventSwitch = true;
		pclMessage->SetKanghwadoEventMsg(pclInfo->siLeftSecond);

	}
	*/
}

// ������ ���� �ӵ��� ���ؿ´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SETGAMEDELAY(cltMsg* pclMsg, SI32 id)
{
	SI32 delay = (SI32)pclMsg->siData32[0];

	if(delay < 10)delay = 10;
	if(delay > 100)delay = 100;

	//SetFrameDelay(delay);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETBYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetByungzoInfo* pclinfo = (cltGameMsgResponse_GetByungzoInfo*)pclMsg->cData;

	if( m_pDialog[ NBYUNGZO_DLG ] )
		((CNByungzoDlg*)m_pDialog[ NBYUNGZO_DLG ])->SetByungzo(&pclinfo->MinisterBase,pclinfo->siVillageWarTime, 
		pclinfo->siSetTime, pclinfo->siWarStartTime, pclinfo->siSetWarCount, pclinfo->siBlackArmyNum );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETGONGZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetGongzoInfo* pclinfo = (cltGameMsgResponse_GetGongzoInfo*)pclMsg->cData;

	if( m_pDialog[ NGONGZO_DLG ] )
		((CNGongzoDlg*)m_pDialog[ NGONGZO_DLG ])->SetGongzo(&pclinfo->MinisterBase,pclinfo->siPriceTime,pclinfo->siLeftOverValue,
		&pclinfo->stGongzoMember, pclinfo->siLeftOverValue_Armor);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETHYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetHyungzoInfo* pclinfo = ( cltGameMsgResponse_GetHyungzoInfo*)pclMsg->cData;

	if( m_pDialog[ NHYUNGZOBASE_DLG ] )
		((CNHyungzoBaseDlg*)m_pDialog[ NHYUNGZOBASE_DLG ])->SetHyungzo(&pclinfo->MinisterBase,pclinfo->siLimitStealNum,pclinfo->siSuspectTime,
		pclinfo->siPrisonTime,pclinfo->siPrisonerPenalty,pclinfo->stHyungzoMember);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETHOZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetHozoInfo* pclinfo = (cltGameMsgResponse_GetHozoInfo*)pclMsg->cData;

	if( m_pDialog[ NHOZOBASE_DLG ] )
		((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->SetHozoDlg( &pclinfo->MinisterBase,pclinfo->siResidentNum,
		                                                          pclinfo->siMaxShop,
		                                                          pclinfo->siTotalCharNum,
																  pclinfo->siCalcTime,
																  pclinfo->siPrizeMoney,
																  pclinfo->siPrizeSetTime,
																  pclinfo->siFixationMoney,
																  pclinfo->siNewCharRate, 
																  pclinfo->siBankruptcyVillageNumber, 
																  pclinfo->siSetBankruptcyVillageDate,
																  pclinfo->siTutorialVillageDivideend );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETIZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetIzoInfo* pclinfo = (cltGameMsgResponse_GetIzoInfo*)pclMsg->cData;

	if( m_pDialog[ NIZOBASE_DLG ] )
		((CNIzoBaseDlg*)m_pDialog[ NIZOBASE_DLG ])->SetIzoBase(&pclinfo->MinisterBase,pclinfo->siPriceTime,pclinfo->siPriceInx,pclinfo->siPriceValue,
		pclinfo->siTotalMoney,pclinfo->siCalcTime,pclinfo->siTradeTax,pclinfo->siTradeLimitMoney,
		pclinfo->bWorldTradeTax, pclinfo->siSpecialTaxRange, pclinfo->siSpecialTaxRate, pclinfo->siMarketDownRate,
		pclinfo->siTinTin);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETYEZOINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetYezoInfo* pclinfo = (cltGameMsgResponse_GetYezoInfo*)pclMsg->cData;

	if(m_pDialog[ NYEZOBASE_DLG ])
		((CNYezoBaseDlg*)m_pDialog[ NYEZOBASE_DLG ])->SetYezoBase(&pclinfo->MinisterBase,pclinfo->siJapanSwordSolNum,pclinfo->siJapanGunSolNum,
		pclinfo->siJapanCommanderNum,pclinfo->siJapanPorterNum,pclinfo->siWarVillageUnique);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETGOONZUINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetGoonzuInfo* pclinfo = (cltGameMsgResponse_GetGoonzuInfo*)pclMsg->cData;

	if(m_pDialog[ NGOONZU_DLG ])
		((CNGoonzuDlg*)m_pDialog[ NGOONZU_DLG ])->SetGoonzu(&pclinfo->MinisterBase,pclinfo->iTotalFinances,pclinfo->siLiquidationVillageNumber);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GOONZU_GETBONUSTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Goonzu_GetBonusTime* pclinfo = (cltGameMsgResponse_Goonzu_GetBonusTime*)pclMsg->cData;

	if(m_pDialog[ NGOONZUPOLICY_DLG ])
		((CNGoonZuPolicyDlg*)m_pDialog[ NGOONZUPOLICY_DLG ])->SetGoonzuBonus( pclinfo->siBonusTime , pclinfo->siMakeBonusTime , pclinfo->bChangeAble );
    
}

// ������ �̺�Ʈ ������ �����Ѵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVEREVENTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ServerEventInfo* pclinfo = (cltGameMsgResponse_ServerEventInfo*)pclMsg->cData;

	for(SI32 i = 0;i < MAX_EVENT_NUMBER;i++)
	{
		bEventSwitch[i] = pclinfo->bEventSwitch[i];
	}

	pclCM->InitBlock();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GIFTNT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GiftNT* pclinfo = (cltGameMsgResponse_GiftNT*)pclMsg->cData;

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EVENTNOTICE")), 0, 0);

	if(m_pDialog[NEVENTNOTIC_DLG]==NULL)			
	{
		CreateInterface(NEVENTNOTIC_DLG);
	}			
	((CNEventNoticeDlg*)m_pDialog[NEVENTNOTIC_DLG])->Set(pclinfo->strGiftName, 32, pclinfo->strMasterNoticeMsg);

	return;
}

// ���� ���� ������ �˷��ش�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_BOSSAPPEAR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BossAppear* pclinfo = (cltGameMsgResponse_BossAppear*)pclMsg->cData;

	const TCHAR* pkindname = pclKindInfoSet->GetName(pclinfo->siBossKind);
	if(pkindname == NULL)return ;

	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(914);


	StringCchPrintf(buffer, 256, pText, pkindname, pclinfo->siLeftSecond);
	pclMessage->SetMsg(buffer);

	return;
}


// ���� ���� �����Ƿ� ������ ����Ѵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONALSHOPMAKEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PersonalShopMakeInfo* pclinfo = (cltGameMsgResponse_PersonalShopMakeInfo*)pclMsg->cData;

	TCHAR buffer[256];	
	TCHAR num[128]= TEXT(" ") ;
	TCHAR fee[128]= TEXT(" ") ;
	TCHAR level[128]= TEXT(" ") ;
	TCHAR skill[128]=TEXT(" ");
	const TCHAR* pitemname = pclItemManager->GetName(pclinfo->siItemUnique);
	if(pitemname == NULL)return ;

	TCHAR* pText = GetTxtFromMgr(915);
	StringCchPrintf(num, 128, TEXT("%d"),pclinfo->siItemNum);
	StringCchPrintf(fee, 128, TEXT("%d"),pclinfo->siFee);
	StringCchPrintf(level, 128, TEXT("%d"), pclinfo->siSkillLevel);
	StringCchPrintf(skill, 128, TEXT("%d"),pclinfo->siHand );

	Nsprintf(buffer,pText,
		TEXT("user"),  pclinfo->szName  ,
		TEXT("item"), pitemname   ,
		TEXT("num"),  num  ,
		TEXT("fee"),  fee  ,
		TEXT("level"),level    ,
		TEXT("skill"),  skill  ,
		NULL);


	//sprintf(buffer, pText, 
	//	pclinfo->szName, pitemname, pclinfo->siItemNum, pclinfo->siFee,  pclinfo->siSkillLevel, pclinfo->siHand );

	g_PromptMgr.Set(buffer, TEXT(""), 1, RGB(250, 250, 250));
	return;
}


// Ư�� ������� ������ �ö����� �˸���. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_LEVELUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LevelUp* pclinfo = (cltGameMsgResponse_LevelUp*)pclMsg->cData;

	SI32 levelupid		= cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsAlive(levelupid) == false)return ;

	cltCharClient* pclChar = (cltCharClient* )pclCM->CR[levelupid];

	// ���� ������ ���� ���̶��, 

	if(pclinfo->siLevel)
	{
		pclCM->CR[levelupid]->pclCI->clIP.SetLevel( pclinfo->siLevel );
		pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_LEVELUP")), 0, 0);
		pclChar->SetLevelUp();

		if( pclCM->CR[levelupid]->clIdentity.clSummonInfo.siParentPersonID > 0 
			&&  pclCM->CR[levelupid]->clIdentity.clSummonInfo.siParentCharUnique == MyCharUnique)// �� ��ȯ�� �϶���
		{
			SI32 siSUmmonIDFormSummon = pclCM->CR[levelupid]->clIdentity.clSummonInfo.siParentPersonID	;
			{
				// ��ȯ�� �ϰ�� �ش� ê �׼��� ���� �ֵ��� ǥ�� ���ش�.,
				SI32 siSummonLevel	=	pclCM->CR[levelupid]->pclCI->clIP.GetLevel()	;// ��ȯ�� ����
				SI32 siSummonKind	=	pclCM->CR[levelupid]->GetKind()					;//��ȯ�� ī�ε�
				TCHAR* tSummonname	=	 ( TCHAR* )pclCM->CR[levelupid]->pclCI->clBI.GetName()	;//��ȯ�� �̸�
				// �ش� ī�ε��� ��ȯ���� �ɸ� ê�� �׼��� �ؽ�Ʈ �ѹ��� ������ �´�.
				SI32 textnum = pclClient->pclKindInfoSet->GetTextMgrCanSummonChatCommand( siSummonKind ,siSummonLevel )	;
				if( textnum > 0 )
				{
					TCHAR* pTitle = TEXT("");// �Ҽ� �ִ� ä�� �޼���
					TCHAR* pChatAction = GetTxtFromMgr( textnum  );// �Ҽ� �ִ� ä�� �޼���
					NTCHARString128	kText( GetTxtFromMgr(8827) );//#��ȯ���̸�#�� #level#�� �޼��Ͽ� ä�� Ŀ�ǵ� #comand#�� ����Ҽ� �ֽ��ϴ�.
					kText.Replace( TEXT("#name#"), tSummonname );// ��ȯ�� �̸� 
					kText.Replace( TEXT("#level#"), SI32ToString( siSummonLevel  ) );
					kText.Replace( TEXT("#command#"), pChatAction );// ��ȯ�� �̸� 
					m_pDialog[NOTIFYMSG_DLG]->SetText( pTitle, kText );
				}
			}
		}		
		if(pclinfo->siCharUnique == MyCharUnique)
		{
			((cltClient*)pclClient)->pclCM->CR[1]->SetCurrentOrder(ORDER_STOP);
			((cltClient*)pclClient)->SetSiSelectedOrder(ORDER_STOP);


            // �ʺ��� �ȳ�. 
			if(pclCM->CR[levelupid]->pclCI->clIP.GetLevel() < 10)
			{
				if ( ConstServiceArea_China != siServiceArea )
				{
					TCHAR* pText = GetTxtFromMgr(916);
					pclMessage->SetMsg(pText);
					pText = GetTxtFromMgr(917);
					pclMessage->SetMsg(pText);
				}
			}

			// ������ �޼��� ���� ���� ���.
			// ���� ����ġ �߰� - By LEEKH 2007.09.19
			if(pclClient->IsCountrySwitch(Switch_LevelupUpText))
			{
				TCHAR levelupText[256] = {0,};
				if ( m_pLevelUpText->GetLevelUpText( pclinfo->siLevel, levelupText, 256) )
				{
					TCHAR* pTitle = GetTxtFromMgr(5614);
					((CNNewNotifyDlg*)m_pDialog[ NNEWNOTIFY_DLG ])->SetImage(GetUniqueFromHash( TEXT("KIND_WAITINGMAN") ));
					m_pDialog[ NNEWNOTIFY_DLG ]->SetText( pTitle, levelupText );
				}
			}

			// ĳ������ ������ 10�̳� 30�̸� �������ͽ� �ʱ�ȭ ����â�� ��������.
			// ���� : pclChar�� ������ �������� ������ �ȵ�. pclinfo�� �ִ� ������ ���.
			/*if ( pclClient->siServiceArea == ConstServiceArea_China )
			{
				if(pclinfo->siLevel == INIT_LEVEL )
				{
					if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
					{
						CreateInterface( NCOMMONMSG_DLG );
					}
					((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_INITLEVEL);
				}

			}
			else
			{
				if(pclinfo->siLevel == INIT_LEVEL || pclinfo->siLevel == INIT_LEVEL_SECOND)
				{
					if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
					{
						CreateInterface( NCOMMONMSG_DLG );
					}
					((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_INITLEVEL);
				}

			}*/
			if(pclinfo->siLevel == INIT_LEVEL || pclinfo->siLevel == INIT_LEVEL_SECOND)
			{
				if(m_pDialog[ NCOMMONMSG_DLG ]==NULL)
				{
					CreateInterface( NCOMMONMSG_DLG );
				}
				((CNCommonMsgDlg*)m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_INITLEVEL);
			}

			// [����] ����Ʈ �˸�����
			if ( IsCountrySwitch(Switch_ShowQuestNotice) )
			{
				if ( NULL == m_pDialog[NQUESTNOTICE_DLG] )
				{
					CreateInterface( NQUESTNOTICE_DLG );
				}

				((CNQuestNoticeDlg*)m_pDialog[NQUESTNOTICE_DLG])->CheckNotice();
			}
		}
	}

	// �� ����� ���� ���̶��, 
	if(pclinfo->siFameLevel)
	{
		//cyj ������ �ö����� ����Ʈ ����
		//pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_LEVELUP")), 0, 0);
		//pclChar->SetLevelUp();
	}
}

//KHY - 1205 - ���������� ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_LEVELUPNOTICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LevelUpNotice* pclinfo = (cltGameMsgResponse_LevelUpNotice*)pclMsg->cData;
		
	((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->LevelUpNoticeChatRecv( pclinfo->szName, pclinfo->siLevel, pclinfo->siSkillLevel,pclinfo->siSkillType,pclinfo->siMessageType) ;

}

// ������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_LETTER(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltLetterUnit* pclletter = (cltLetterUnit*)pclMsg->cData;

	TCHAR buffer[1024] = {'\0'};
	if(pclletter->GetText(buffer, 1024) == true)
	{
		PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_LETTER")), 0, 0);

		if((CNLetterDlg*)m_pDialog[ NLETTER_DLG ]==NULL)
		{
			CreateInterface( NLETTER_DLG);				
		}
		((CNLetterDlg*)m_pDialog[ NLETTER_DLG ])->Push(buffer);
	}

	// ȭ���� �������� ǥ���Ѵ�. 
	SetFlashWindowNotice(true);

	// ���ֿ��� ���� �ȸ� �뺸���,, 
	cltLetterHeader* pclheader = (cltLetterHeader*)pclletter->cData;

	if(pclheader->siType == LETTERTYPE_MARKETTRADE)
	{
		cltLetterMsg_MarketTrade* pclmarkettrade = (cltLetterMsg_MarketTrade*)pclletter;

		//-----------------------------------------------------------
		// ���ֿ��� ���� �Ĵ� ����Ʈ���, 
		// ���� ������ ����Ʈ�� �Ϸ�Ǿ����� �˷��ش�.
		//-----------------------------------------------------------
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_SELLMARKET;
		if(pclCM->CR[id]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			if(para1 == pclmarkettrade->siItemUnique)
			{
				cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
				cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				SendMsgToServer((sPacketHeader*)&clMsg);
			}
		}

	}
}
 
void cltClient::DoMsg_GAMEMSG_RESPONSE_ACCOUNTLETTER(cltMsg* pclMsg, SI32 id)
{
	
	cltClient*  pclclint = (cltClient*)pclClient;

	// ȭ���� �������� ǥ���Ѵ�. 
	SetFlashWindowNotice(true);

	cltAccountLetterUnit* pclletter = (cltAccountLetterUnit*)pclMsg->cData;

	cltLetterHeader* pclheader = (cltLetterHeader*)pclletter->cData;

	if(pclheader->siType == ACCOUNT_LETTERTYPE_PRESENT )
	{
        cltLetterMsg_Present * pclPresent = (cltLetterMsg_Present*)pclletter;
		
		/*
		if( pclclint->m_pDialog[NITEMMALL_DLG] )
		{
			pclclint->m_pDialog[NITEMMALL_DLG]->DeleteDialog();
		}
		*/
		
		if(pclclint->m_pDialog[NGETPRESENT_DLG] == NULL)
		{
			pclclint->CreateInterface( NGETPRESENT_DLG );             
		}

		if(pclclint->m_pDialog[NGETPRESENT_DLG])
		{
			((CNGetPresentDlg*)pclclint->m_pDialog[NGETPRESENT_DLG] )->SetPresentData(
				pclPresent->siFromServerUnique  , pclPresent->szFromPlayerName,pclPresent->szComment
				,pclPresent->szItemName,pclPresent->siItemNum,pclPresent->siItemImageFont,pclPresent->szFromPlayerAccount );
		}
	}
	if(pclheader->siType == ACCOUNT_LETTERTYPE_PRESENTANSWER )
	{
		cltLetterMsg_PresentAnswer * pclPresent = (cltLetterMsg_PresentAnswer*)pclletter;

		if(pclclint->m_pDialog[NTHANKSPRESENT_DLG] == NULL)
		{
			pclclint->CreateInterface( NTHANKSPRESENT_DLG );             
		}

		if(pclclint->m_pDialog[NTHANKSPRESENT_DLG])
		{
			((CNThanksPresentDlg*)pclclint->m_pDialog[NTHANKSPRESENT_DLG] )->SetRecvLetterData(
				pclPresent->siFromServerUnique, pclPresent->szFromPlayerName,pclPresent->szComment
				);
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY(cltMsg* pclMsg, SI32 id){
	cltGameMsgResponse_NoticeItemUseDayOver* pclInfo = (cltGameMsgResponse_NoticeItemUseDayOver*)pclMsg->cData;
	
	TCHAR szBuffer[256] = TEXT("");
	TCHAR * szTxtFromMgr;
	TCHAR * szItemName = (TCHAR*)pclItemManager->GetName( pclInfo->siItemUnique );
	

	if(pclInfo->siUseableDay >= 3) // �־ �ȵǴ� ����̹Ƿ� ����
	{
		//todo : errormsg	
		return;
	}	
	else if(pclInfo->siUseableDay >= 0)// %s �� %d �� �� �ǰ����ϴ�.
	{
		szTxtFromMgr = GetTxtFromMgr( 5776 );
		StringCchPrintf(szBuffer,256,szTxtFromMgr,szItemName,pclInfo->siUseableDay+1); // ��밡���� +1�� �ı��ɳ��̴�.
	}
	else if( pclInfo->siUseableDay < 0 )			// %s �� �ǰ������ϴ�.
	{
		szTxtFromMgr = GetTxtFromMgr( 5777 );
		StringCchPrintf(szBuffer,256,szTxtFromMgr,szItemName);
	}

	//Output To Dlg
	if((CNLetterDlg*)m_pDialog[ NLETTER_DLG ]==NULL)
	{
		CreateInterface( NLETTER_DLG);	
	}
	((CNLetterDlg*)m_pDialog[ NLETTER_DLG ])->Push(szBuffer);
}

// ��ڰ� ������� �α׸� ��û�Ѵ�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONAL_LOG(cltMsg* pclMsg, SI32 id)
{
	/*cyj
	cltGameMsgResponse_Personal_Log* pclInfo = (cltGameMsgResponse_Personal_Log*)pclMsg->cData;

	BOOL bend = TRUE ;
	if ( pclInfo->siResult == -1 )
		bend = FALSE ;

	m_pGameMasterPersonalLogDlg->SetLogMsg(pclInfo->stLogData,bend);

	return ;*/
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_INVESTMENTGETINFO(cltMsg * pclMsg, SI32 id)
{
	cltGameMsgResponse_InvestmentGetInfo * pclInfo = (cltGameMsgResponse_InvestmentGetInfo*)pclMsg->cData;

	//m_pInvestmentDlg->ShowListData(pclInfo->stInvestmentLines);

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(m_pDialog[NINVESTMENT_DLG]!=NULL)
		{
			((CNInvestmentDlg*)m_pDialog[NINVESTMENT_DLG])->ShowListData(pclInfo->stInvestmentLines);			
		}


	}


	return ;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AutoHunting * pclInfo = (cltGameMsgResponse_AutoHunting*)pclMsg->cData;


	//if ( g_SoundOnOffDlg.m_bFullScreenMode )
	//{

	if (m_pDialog[ NAUTOHUNT_DLG ] == NULL )							
	{
		CreateInterface( NAUTOHUNT_DLG );
	}
	((CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG])->Set(pclInfo->szRequestTxt,pclInfo->siSlot,
		pclInfo->siTimeLimit,pclInfo->siPrisonTime,pclInfo->siPrisonerPenalty);
	//}

	//else	
	//pclAutoHuntingManager->Set(pclInfo->szRequestTxt,pclInfo->siSlot,pclInfo->siTimeLimit,pclInfo->siPrisonTime,pclInfo->siPrisonerPenalty);






	return ;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING_ASK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AutoHunting_Ask * pclInfo = (cltGameMsgResponse_AutoHunting_Ask*)pclMsg->cData;

	if ( pclInfo->bSuccess == false && pclInfo->siLeft < 3 && pclInfo->siLeft > 0 )
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pTitle = GetTxtFromMgr(919);
		TCHAR* pText  = GetTxtFromMgr(918);



		StringCchPrintf(buffer, 256, pText,
			pclInfo->siLeft,3 - pclInfo->siLeft ) ;

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
	}
	else if ( pclInfo->bSuccess == false && pclInfo->siLeft == 3 )
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pTitle = GetTxtFromMgr(921);
		TCHAR* pText  = GetTxtFromMgr(920);



		StringCchPrintf(buffer,256, pText,
			pclInfo->siLeft) ;

		if (m_pDialog[ NAUTOHUNT_DLG ])							
		{
			((CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG])->DeleteDialog();
		}

		//pclAutoHuntingManager->Hide();
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
	}

	else if ( pclInfo->bSuccess == false && pclInfo->siLeft == 0 )
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pTitle = GetTxtFromMgr(921);
		TCHAR* pText  = GetTxtFromMgr(922);



		StringCchPrintf(buffer, 256, pText,
			pclCM->CR[1]->pclCI->clIP.GetLevel() * pclInfo->siPrisonerPenalty );

		//pclAutoHuntingManager->Hide();
		if (m_pDialog[ NAUTOHUNT_DLG ])							
		{
			((CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG])->DeleteDialog();
		}
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
	}

	else if ( pclInfo->bSuccess == true )
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pTitle = GetTxtFromMgr(924);
		TCHAR* pText  = GetTxtFromMgr(923);



		StringCchPrintf(buffer, 256, pText,NOSUSPICTION_PRISON_TIME);




		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{
			if(m_pDialog[ NAUTOHUNT_DLG ])
			{
				((CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG ])->DeleteDialog();
			}


		}
		else 
		{
			//pclAutoHuntingManager->Hide();
			if (m_pDialog[ NAUTOHUNT_DLG ])							
			{
				((CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG])->DeleteDialog();
			}
		}

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
	}

	return ;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_AUTOHUNTING_TIMEUPDATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AutoHunting_TimeUpdate * pclInfo = (cltGameMsgResponse_AutoHunting_TimeUpdate*)pclMsg->cData;




	//if ( g_SoundOnOffDlg.m_bFullScreenMode )
	//{
	if(m_pDialog[ NAUTOHUNT_DLG ]==NULL)			
	{
		CreateInterface(NAUTOHUNT_DLG);		

	}
	CNcltAutoHuntingManager* Nautohunt = (CNcltAutoHuntingManager*)m_pDialog[ NAUTOHUNT_DLG ];

	( Nautohunt->SetLeftTime( Nautohunt->GetLeftTime() - pclInfo->siMinusTime));

	if(Nautohunt->GetLeftTime())
	{
		Nautohunt->SetStaticTime(pclInfo->siTotalTime);					
	}


	/*

	}


	else
	{			
	pclAutoHuntingManager->SetLeftTime(pclAutoHuntingManager->GetLeftTime() - pclInfo->siMinusTime);
	if ( pclAutoHuntingManager->GetLeftTime() )
	{
	pclAutoHuntingManager->SetStaticTime(pclInfo->siTotalTime);
	}

	}

	*/



	return ;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETANGELAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetAngelApplyerList* pclinfo = (cltGameMsgResponse_GetAngelApplyerList*)pclMsg->cData;

	if ( pclinfo->siResult != 1 ) return ;
#ifdef _DEBUG
	if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

	if ( ((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->SetListDlg(1) == TRUE )
		((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowListDlg(pclinfo->stHozoAngelApplyerList);
#else
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

		if ( ((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->SetListDlg(1) == TRUE )
			((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowListDlg(pclinfo->stHozoAngelApplyerList);
	}
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETANGELLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetAngelList* pclinfo = (cltGameMsgResponse_GetAngelList*)pclMsg->cData;

	if ( pclinfo->siResult != 1 ) return ;
#ifdef _DEBUG
	if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

	if ( ((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->SetListDlg(2) == TRUE )
		((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowListDlg(pclinfo->stHozoAngelList);
#else
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

		if ( ((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->SetListDlg(2) == TRUE )
			((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowListDlg(pclinfo->stHozoAngelList);
	}
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETANGELAPPLYER(cltMsg* pclMsg, SI32 id)
{
	cltMsg clMsg(GAMEMSG_REQUEST_GETANGELAPPLYERLIST,0,NULL);
	SendMsgToServer((sPacketHeader*)&clMsg);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETANGEL(cltMsg* pclMsg, SI32 id)
{
	cltMsg clMsg(GAMEMSG_REQUEST_GETANGELLIST,0,NULL);
	SendMsgToServer((sPacketHeader*)&clMsg);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETPOLICELIST(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_GetPoliceList* pclinfo = (cltGameMsgResponse_GetPoliceList*)pclMsg->cData;

	if ( pclinfo->siResult != 1 ) return ;
#ifdef _DEBUG
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NHYUNGZOBASE_DLG ] == NULL ) 
			return;
		((CNHyungzoBaseDlg*)m_pDialog[ NHYUNGZOBASE_DLG ])->ShowListDlg(pclinfo->stHyungPoliceList);
	}
#else
	if ( m_pDialog[ NHYUNGZOBASE_DLG ] == NULL ) 
		return ;

	((CNHyungzoBaseDlg*)m_pDialog[ NHYUNGZOBASE_DLG ])->ShowListDlg(pclinfo->stHyungPoliceList);
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETPOLICE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_SetPolice* pclinfo = (cltGameMsgResponse_SetPolice*)pclMsg->cData;

	if( pclinfo->siResult != 1)
		return;

	cltMsg clMsg(GAMEMSG_REQUEST_GETPOLICELIST,0,NULL);
	SendMsgToServer((sPacketHeader*)&clMsg);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETCRIMINALLIST(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_GetCriminalList* pclinfo = (cltGameMsgResponse_GetCriminalList*)pclMsg->cData;

	if ( pclinfo->siResult != 1 ) return ;
#ifdef _DEBUG
	if( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if ( m_pDialog[ NHYUNGZOBASE_DLG ] == NULL ) 
			return ;
		((CNHyungzoBaseDlg*)m_pDialog[ NHYUNGZOBASE_DLG ])->ShowListDlg(pclinfo->stHyungzoCriminalList);
	}
#else
	if ( m_pDialog[ NHYUNGZOBASE_DLG ] == NULL ) 
		return ;
	((CNHyungzoBaseDlg*)m_pDialog[ NHYUNGZOBASE_DLG ])->ShowListDlg(pclinfo->stHyungzoCriminalList);
#endif



}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETCRIMINAL(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_SetCriminal* pclinfo = (cltGameMsgResponse_SetCriminal*)pclMsg->cData;

	switch ( pclinfo->siResult )
	{
	case SETCRIMINAL_SUCCESS:
		{
			cltMsg clMsg(GAMEMSG_REQUEST_GETCRIMINALLIST,0,NULL);
			SendMsgToServer((sPacketHeader*)&clMsg);
		}
		break;
	case SETCRIMINAL_FAIL_ISGM:
		{
			TCHAR* pText = GetTxtFromMgr(6426);
			TCHAR* pTitle = GetTxtFromMgr(2029);
			((cltClient*)pclClient)->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pText);
		}
		break;
	default:
		break;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETCHANGEDNAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetChangedName* pclinfo = (cltGameMsgResponse_GetChangedName*)pclMsg->cData;

	if ( pclinfo->siResult != 1 ) return ;
#ifdef _DEBUG
	if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

	((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowChangedNameList(pclinfo->siPage,pclinfo->stChangedNameChar);
	//	m_pHozoDlg->ShowChangedNameList(pclinfo->siPage,pclinfo->stChangedNameChar);
#else
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NHOZOBASE_DLG ] == NULL ) return ;

		((CNHozoBaseDlg*)m_pDialog[ NHOZOBASE_DLG ])->ShowChangedNameList(pclinfo->siPage,pclinfo->stChangedNameChar);
	}
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICEADMIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NoticeAdmin* pclinfo = (cltGameMsgResponse_NoticeAdmin*)pclMsg->cData;

	if ( m_pDialog[NNOTICEADMIN_DLG] == NULL )
		CreateInterface ( NNOTICEADMIN_DLG ) ;

	((cltNNoticeAdminDlg*)m_pDialog[ NNOTICEADMIN_DLG ])->SetData(pclinfo->szText);

	PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_NOTICEADMIN")),0,0);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANCEMAPINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InstanceMapInfo* pclinfo = (cltGameMsgResponse_InstanceMapInfo*)pclMsg->cData ;

	TCHAR * pText = GetTxtFromMgr(3286) ;
	TCHAR buffer[MAX_MESSAGE_LENGTH] = TEXT("") ;

	StringCchPrintf(buffer, MAX_MESSAGE_LENGTH,pText,pclinfo->siLeftTime,pclinfo->siLeftMon);

	pclMessage->SetInstanceMapMsg(buffer);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOPETOQUIT(cltMsg* pclMsg, SI32 id)
{
	if(GetFrame() <= 0)
	{
		dwQuitTimer = 1;

		// �Ѱ��� ���뺸��
		if(pclClient->siServiceArea == ConstServiceArea_NHNChina)
		{
			HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(clSelectedWorldInfo.baseinfo.siServerID ,m_szPorteAuth_UserID, HANREPORT_CLIENT_LOGOUTFROMGAMESERVER);
		}
		else
		{
			HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_LOGOUTFROMGAMESERVER);

		}
	}
	else
	{
		dwQuitTimer = CurrentClock;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOPETOFRONT(cltMsg* pclMsg, SI32 id)
{
	if ( pGameSession->CloseSocket() )
	{
		pFrontSession->CloseSocket() ;

		bReceiveMyCharAllInfoSwitch	= false;
		bBackUpSwitch				= false;

		siAuthKey		= 0;
		bFrontServerActionSwitch	= true;
		bGameServerActionSwitch		= false;

		bFrontServerSecretKeySwitch	= false;
		bGameServerSecretKeySwitch	= false;

		pclSmokeManager->DeleteSmoke();
		pclBulletManager->DeleteBullet();

		pclMagicManager->DeleteMagic();

		pclCM->DeleteChar();

		bool bTempSmallMapSwitch = bSmallMapSwitch;

		pclMapManager->DeleteAllMap();

		pclMapManager->pclCurrentMap = NULL;		// �ݵ�� �ʱ�ȭ �Ǿ�� �Ѵ�. 
		
		for( SI32 i = 0; i < MAX_CHAR_PER_USER ; i++ )
		{
			clCharListInfo[ i ].Init();
		}

		//InitMembers();
		// â�� �ݴ´�.
		if(m_pDialog[ NNEWQUEST_DLG ])
			m_pDialog[ NNEWQUEST_DLG ]->DeleteDialog();
		if(m_pDialog[ NQUEST_DLG ]->IsShow() == TRUE)
			m_pDialog[ NQUEST_DLG ]->Show(false);
			//			((cltNQuestDlg*)m_pDialog[ NQUEST_DLG ])->Hide();

		m_pInterfaceMgr->CloseAllWindow();
		pclMusic->pclSoundManager->AllSoundStop();
		

		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->Initialize();		

		Sleep(2000);

		SetGameStatus(GS_INITCONNECTFRONTSERVER);

		// APEX-
#ifdef _CHINA
		if( true == m_bStartApex )
		{
			StopApexClient();
			m_bStartApex = false;
		}
#endif
		// -APEX

	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACKARMYAPPLY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BlackArmy_Apply *pclinfo = (cltGameMsgResponse_BlackArmy_Apply*)pclMsg->cData;

	TCHAR *pTitle;
	TCHAR *pText;
	TCHAR buf[256];

	if (((cltClient*)pclClient)->m_pDialog[NOTIFYMSG_DLG])
	{
		if (pclinfo->siResult == -1)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5852);
			StringCchCopy(buf, 256, pText);

		}
		else if (pclinfo->siResult == -2)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5866);
			StringCchCopy(buf, 256, pText);

		}
		else if (pclinfo->siResult == -3)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5853);
			StringCchCopy(buf, 256, pText);

		}
		else if (pclinfo->siResult == -4)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5869);
			StringCchCopy(buf, 256, pText);

		}
		else if (pclinfo->siResult == -5)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5870);
			StringCchCopy(buf, 256, pText);

		}
		else if (pclinfo->siResult == -6)
		{
			pTitle = GetTxtFromMgr(428);
			pText = GetTxtFromMgr(5875);
			StringCchCopy(buf, 256, pText);

		}
		else 
		{
			pTitle = GetTxtFromMgr(431);
			pText = GetTxtFromMgr(5854);

			StringCchPrintf(buf, 256, pText, pclinfo->siApplyUnique + 1);

		}

		if (m_pDialog[NPLAYMATCH_DLG])
		{
			((NPlayMatchDlg*)m_pDialog[NPLAYMATCH_DLG])->SetNPCText(buf);

		}
		else
		{
			m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, buf);
		}
	}
}

// ���� �޽���. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACKARMYWAR(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_BlackArmy_War * pclinfo = (cltGameMsgResponse_BlackArmy_War*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	static SI32 siInterval = 0;

	if(pclinfo->siCmd == WAR_CMD_BREAK
		|| pclinfo->siCmd == WAR_CMD_WIN
		|| pclinfo->siCmd == WAR_CMD_LOSE)
	{
		pclBlackArmyManager->SetDraw(pclinfo->siCmd);
	}
	
	//-----------------------------------
	// ��Ȳ ������ �����Ѵ�. 
	//-----------------------------------
	SI32 leftmon = pclinfo->siWarLeftMon;

	// ������ �߹��� ���̸� ������ ������ ��� �����Ѵ�. 
	if(pclinfo->siCmd == WAR_CMD_BREAK)
	{
		pclCM->DeleteAllWarKill();

		pclBlackArmyManager->bWarSwitch		= true;
		pclBlackArmyManager->uiLeftTime		= pclinfo->uiLeftTime;

		pclCM->CR[1]->siBlackArmyWarMapIndex	= pclinfo->siWarMapIndex;


	}
	else if (pclinfo->siCmd == WAR_CMD_GOING)
	{
		pclBlackArmyManager->bWarSwitch		= true;
		pclBlackArmyManager->uiLeftTime		= pclinfo->uiLeftTime;

	}
	else
	{
		pclBlackArmyManager->bWarSwitch		= false;
		pclBlackArmyManager->uiLeftTime		= 0;
		leftmon = 0;
	}

	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(894);

    cltGate gate = pclClient->pclMapManager->pclGateManager->clGate[BLACKARMY_GATEUNIQUE_START + pclinfo->siWarMapIndex];
    
	StringCchPrintf(buffer, 256, pText, gate.SrcX, gate.SrcY, (pclBlackArmyManager->uiLeftTime) /1000, leftmon);

	pclMessage->SetBlackArmyWarMsg( buffer, (TCHAR**)pclinfo->szSortPlayerNames,  (SI32*)pclinfo->siWarScores );

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACKARMY_RANKINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BlackArmy_RankInfo *pclInfo = (cltGameMsgResponse_BlackArmy_RankInfo*)pclMsg->cData;

	if (m_pDialog[NBLACKARMYMVP_DLG])
	{
		((NBlackArmyMVPDlg*)m_pDialog[NBLACKARMYMVP_DLG])->SetRanks(pclInfo->siWarMapIndex, pclInfo->siPoints, (TCHAR**)pclInfo->szPlayes);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACKARMY_MVPEFFECT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BlackArmy_MVPEffect *pclInfo = (cltGameMsgResponse_BlackArmy_MVPEffect*)pclMsg->cData;

	SI32 mvpid		= cltCharCommon::CharUniqueInfo[pclInfo->siCharUnique];
	if(pclCM->IsAlive(mvpid) == false)return ;

	cltCharClient* pclChar = (cltCharClient* )pclCM->CR[mvpid];

	if (pclChar->pclMVPEffect)
	{
		pclMusic->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MVPEFFECT")), 0, 0);
		pclChar->SetMVPEffect();
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACKWAR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BlackWar * pclinfo = (cltGameMsgResponse_BlackWar*)pclMsg->cData;

	// ���� ����̸�, 
	if(bWatchModeSwitch == true)
		return ;

	//-----------------------------------
	// ��Ȳ ������ �����Ѵ�. 
	//-----------------------------------
	SI32 leftmon = pclinfo->siLeftEnemy;

	static SI32 siInterval = 0;

	if( pclinfo->siCmd == BLACKWAR_CMD_BREAK )
	{
		pclClient->pclCM->CR[1]->siBlackWarKilledNumber			  = 0;
		pclClient->pclCM->CR[1]->siBlackWarEnemyKillNumber		  = 0;
		pclClient->pclCM->CR[1]->siBlackWarEnemyKillScore		  = 0;
		pclClient->pclCM->CR[1]->siBlackWarEnemyKillVillageScore  = 0;
		pclBlackWarManager->SetBlackWar(true);
		pclBlackWarManager->SetDraw(pclinfo->siCmd);
		pclBlackWarManager->SetLeftTime( pclinfo->uiLeftTime );
	}
	else if( pclinfo->siCmd == BLACKWAR_CMD_GOING )
	{
		pclBlackWarManager->SetBlackWar( true );
		pclBlackWarManager->SetLeftTime( pclinfo->uiLeftTime );
	}
	else if( pclinfo->siCmd == BLACKWAR_CMD_WIN )
	{
		pclBlackWarManager->SetBlackWar(false);
		pclBlackWarManager->SetDraw(pclinfo->siCmd);
		pclBlackWarManager->SetLeftTime( pclinfo->uiLeftTime );
	}
	else if( pclinfo->siCmd == BLACKWAR_CMD_LOSE )
	{
		pclBlackWarManager->SetBlackWar(false);
		pclBlackWarManager->SetDraw(pclinfo->siCmd);

		pclBlackWarManager->SetLeftTime( 0 );
		leftmon = 0;
	}

	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(894);
	StringCchPrintf(buffer, 256, pText, pclinfo->siX, pclinfo->siY, pclinfo->uiLeftTime /1000, leftmon, pclinfo->siTotalEnemy);

	pclMessage->SetWarMsg(buffer, (TCHAR**)pclinfo->szSortPlayerNames, (SI32*)pclinfo->siWarScores, (TCHAR**)pclinfo->szSortVillageNames, (SI32*)pclinfo->siWarVillageScores);

	if( true == pclinfo->bMakeBoss )
	{
		pText = GetTxtFromMgr(10026);
		pclMessage->SetMsg( pText );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ENCHANTITEMSTARTOREND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Enchant_StartOrEnd* pclinfo = (cltGameMsgResponse_Enchant_StartOrEnd*)pclMsg->cData ; 

	pclClient->bEnchantSwitch = pclinfo->bEnchantStart;

	return;
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_ENCHANTOTHERSHOW(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EnchantOther* pclinfo = (cltGameMsgResponse_EnchantOther*)pclMsg->cData ; 

	cltItem Element[NOW_ENCHANT_NUMBER];

	for(SI32 i =0; i<NOW_ENCHANT_NUMBER; i++)
	{
		Element[i].Init();
		Element[i].Set( &pclinfo->clEleItem[i] );
	}

	if(m_pDialog[NNEWENCHANTOTHER_DLG])
	{
		CNNewEnchantOther* EnchantDlg = (CNNewEnchantOther*) m_pDialog[NNEWENCHANTOTHER_DLG]; 
		EnchantDlg->ShowOrgEnchantItem(pclinfo->clOrgItem);
		EnchantDlg->ShowMatEnchantItem(pclinfo->clMatItem);
		EnchantDlg->ShowEleEnchantItem(Element);
		EnchantDlg->SetUpdateButton(pclinfo->bUpdateMaterial);
		EnchantDlg->SetStartButton(pclinfo->bStartEnchant);

	}

	return;
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_ENCHANTOTHERPRICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_EnchantPrice* pclinfo = (cltGameMsgRequest_EnchantPrice*)pclMsg->cData ; 

	if(m_pDialog[NNEWENCHANTOTHER_DLG])
	{
		CNNewEnchantOther* EnchantDlg = (CNNewEnchantOther*) m_pDialog[NNEWENCHANTOTHER_DLG]; 
		EnchantDlg->SetPriceText(pclinfo->siCurrentPrice);
	}



}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ItemDisAssemble* pclinfo = (cltGameMsgResponse_ItemDisAssemble*)pclMsg->cData;


	if (pclinfo->siResult > 0)
	{
		TCHAR szBuffer[256] = {'\0'};
		TCHAR *ptext = TEXT("");
        
		switch ( pclinfo->siWenneyPercent )
		{
		case WENNYMSG_NONE:				ptext = GetTxtFromMgr(6188);	break;
		case WENNYMSG_SMALL:			ptext = GetTxtFromMgr(6189);	break;
		case WENNYMSG_MEDIUM:			ptext = GetTxtFromMgr(6190);	break;
		case WENNYMSG_LARGE:			ptext = GetTxtFromMgr(6191);	break;
		case WENNYMSG_DOUBLE:			ptext = GetTxtFromMgr(6610);	break;
		case WENNYMSG_NECKLACE:			ptext = GetTxtFromMgr(6611);	break;
		case WENNYMSG_BOX:				ptext = GetTxtFromMgr(6612);	break;
		case WENNYMSG_WENNYMATERIAL:	ptext = GetTxtFromMgr(6982);	break;
		case WENNYMSG_GACHARARE:		ptext = GetTxtFromMgr(7083);	break;
		case WENNYMSG_REPAIR_DUR:		ptext = GetTxtFromMgr(40169);	break;
		default:
			ptext = GetTxtFromMgr(5936);
			break;
		}

		
		
		if( pclinfo->siWenneyPercent == WENNYMSG_SMALL 
			|| pclinfo->siWenneyPercent == WENNYMSG_MEDIUM 
			|| pclinfo->siWenneyPercent == WENNYMSG_LARGE
			|| pclinfo->siWenneyPercent == WENNYMSG_DOUBLE )
		{
			TCHAR * ptext2 = GetTxtFromMgr(6831);

			StringCchPrintf( szBuffer , 256 , TEXT("%s (%s %d%%)"), ptext , ptext2 , pclinfo->siResolutionRate );			
		}
		else
		{
			StringCchPrintf( szBuffer , 256 , TEXT("%s"),ptext );
		}

		// �������� ���� ��� ���� �ؽ�Ʈ �߰�
		if ( IsCountrySwitch(Switch_NewDurability) ) 
		{
			switch ( pclinfo->siWenneyPercent )
			{
			case WENNYMSG_SMALL:
			case WENNYMSG_MEDIUM:
			case WENNYMSG_LARGE:
			case WENNYMSG_DOUBLE:
				// ��
			case WENNYMSG_NONE:
				// �������
			case WENNYMSG_WENNYMATERIAL:
				// ������ ������
			case WENNYMSG_REPAIR_DUR:
				{
					// �������� ���� ���� ������ �پ������� �ؽ�Ʈ�� �־��ش�
					if ( 100 > pclinfo->siDurabilityPenalty )
					{
						NTCHARString128 strPenaltyText = GetTxtFromMgr(30524);

						StringCchCat( szBuffer, sizeof(szBuffer), strPenaltyText );
					}
				}
				break;
			}
		}

		//[�߰� : Ȳ���� 2008. 2. 28 => ƾƾ ���� �� �������� â�� ����Ʈ �߰�, NPC Ÿ�Ժ� ���ǹ�.]
		if( ItemDisAssemble_NPC_KIND::NPC_TINTIN == pclinfo->m_siNPCKind )
		{
			if (m_pDialog[NWENNYMAN_DLG] && ptext)
			{	
				((CNWennyOldMan*)m_pDialog[NWENNYMAN_DLG])->SetWennyText(szBuffer);
	#ifdef _SAFE_MEMORY
				((CNWennyOldMan*)m_pDialog[NWENNYMAN_DLG])->SetWeennyStorage(&pclinfo->clItem[0]);
	#else
				((CNWennyOldMan*)m_pDialog[NWENNYMAN_DLG])->SetWeennyStorage(pclinfo->clItem);
	#endif

				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WENNYOLDMAN_SUCCESS")), 0, 0);
			}
		}
		//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ȯ���� �������� â�� ����Ʈ �߰�, NPCŸ�Ժ� ���ǹ�.]
		else if( ItemDisAssemble_NPC_KIND::NPC_ATIFACT == pclinfo->m_siNPCKind )
		{
			if (m_pDialog[ARTIFACT_BASE_DLG] && ptext)
			{	
				NArtifactBaseDlg* pNArtifactBaseDlg = (NArtifactBaseDlg*)m_pDialog[ARTIFACT_BASE_DLG];
#ifdef _SAFE_MEMORY
				//pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetDisasembleItem(&pclinfo->clItem[0]);
				pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_bEffectAction = true;
				memcpy(pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_clDisasembleItemItemList, &pclinfo->clItem[0], sizeof(pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_clDisasembleItemItemList));
				pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetArtifactStorage(&pclinfo->clItem[0]);
#else
				//pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetDisasembleItem(pclinfo->clItem);
                pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_bEffectAction = true; 
				memcpy(pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_clDisasembleItemItemList, pclinfo->clItem, sizeof(pNArtifactBaseDlg->m_NArtifactRestoreDlg.m_clDisasembleItemItemList));
				pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetArtifactStorage(pclinfo->clItem);
#endif

				PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WENNYOLDMAN_SUCCESS")), 0, 0);
			}
		
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM_LIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ItemDisAssemble_List* pclInfo = (cltGameMsgResponse_ItemDisAssemble_List*)pclMsg->cData;

	if (pclInfo->siResult > 0)
	{
		//[�߰� : Ȳ���� 2008. 2. 28 => ƾƾ ���� ����Ʈ ��û, NPC Ÿ�Ժ� ���ǹ�.]
		if( ItemDisAssemble_NPC_KIND::NPC_TINTIN == pclInfo->m_siNPCKind )
		{
			if (m_pDialog[NWENNYMAN_DLG])
			{	
#ifdef _SAFE_MEMORY
				((CNWennyOldMan*)m_pDialog[NWENNYMAN_DLG])->SetWeennyStorage(&pclInfo->clItem[0]);
#else
				((CNWennyOldMan*)m_pDialog[NWENNYMAN_DLG])->SetWeennyStorage(pclInfo->clItem);
#endif
			}
		}
		//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ����Ʈ ��û, NPCŸ�Ժ� ���ǹ�.]
		else if( ItemDisAssemble_NPC_KIND::NPC_ATIFACT == pclInfo->m_siNPCKind )
		{
			if (m_pDialog[ARTIFACT_BASE_DLG] )
			{	
				NArtifactBaseDlg* pNArtifactBaseDlg = (NArtifactBaseDlg*)m_pDialog[ARTIFACT_BASE_DLG];
#ifdef _SAFE_MEMORY
				pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetArtifactStorage(&pclInfo->clItem[0]);
#else
			pNArtifactBaseDlg->m_NArtifactRestoreDlg.SetArtifactStorage(pclInfo->clItem);
#endif
			}
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DISASSEMBLEITEM_RECIEVE(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_OPENTREASUREBOX(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_OpenTreasureBox* pclinfo = (cltGameMsgResponse_OpenTreasureBox*)pclMsg->cData;

	pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clItem);
	pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siToItemPos1].Set(&pclinfo->clToItem1);
	pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siToItemPos2].Set(&pclinfo->clToItem2);

	if( pclinfo->siKeyItemPos >= PERSONITEM_INV0 && pclinfo->siKeyItemPos < MAX_ITEM_PER_PERSON )
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siKeyItemPos].Set(&pclinfo->clKeyItem);

	if( pclinfo->siToItemPos2 >= PERSONITEM_INV0 && pclinfo->siToItemPos2 < MAX_ITEM_PER_PERSON && pclinfo->clToItem2.siUnique > 0)
	{
		pclCM->CR[1]->pclCI->clCharItem.clItem[pclinfo->siToItemPos2].Set(&pclinfo->clToItem2);
	}

	cltClient* pclclient = (cltClient*)pclClient;

	if( pclinfo->siKeyItemPos > 0 )
	{
		if( pclclient->m_pDialog[ NOPENBIGITEMBOX_DLG ] )
		{
			((CNOpenBigItemBoxDlg*)pclclient->m_pDialog[ NOPENBIGITEMBOX_DLG ])->SetResult(pclinfo->clToItem1.siUnique, pclinfo->siGetItemNumber1 );
		}
	}
	else
	{
		if( pclclient->m_pDialog[ NTREASUREBOX_DLG ] )
		{
			((CNTreasureBoxDlg*)pclclient->m_pDialog[ NTREASUREBOX_DLG ])->ShowTreasureItem(pclinfo->clToItem1.siUnique, pclinfo->siGetItemNumber1 );
		}
	}

	// 2�� ���� �ָӴ�.
	if( pclinfo->siToItemPos2 > 0 )
	{
		if ( pclinfo->clToItem2.siUnique <= 0 )
		{
			return;
		}

		if ( !pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ] ) 
		{
			pclclient->CreateInterface( NTREASUREBOXEXTRA_DLG );
			SI16 Xpos  = ((CNTreasureBoxExtraDlg*)pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ])->GetX() * 3;
			SI16 Ypos  = ((CNTreasureBoxExtraDlg*)pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ])->GetY();
			((CNTreasureBoxExtraDlg*)pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ])->MovePos(Xpos,Ypos);
		}

		if( pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ] )
		{		

			((CNTreasureBoxExtraDlg*)pclclient->m_pDialog[ NTREASUREBOXEXTRA_DLG ])->ShowTreasureItem(pclinfo->clToItem2.siUnique, pclinfo->siGetItemNumber2 );
		}
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVERTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ServerTime* pclInfo = (cltGameMsgResponse_ServerTime*)pclMsg->cData;

	sTime = pclInfo->sTime;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICECOUNTRYUSERMAKE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NoticeCountryUserMake* pclInfo = (cltGameMsgResponse_NoticeCountryUserMake*)pclMsg->cData;
	// �߰��Ұ�..���� ������..
	//m_pDialog[NOTIFYMSG_DLG]->SetText()
}

//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� �޽���.]  
void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACK_WAR_REFORM_CHAR_RESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Black_War_Reform_Char_Result* pclInfo = (cltGameMsgResponse_Black_War_Reform_Char_Result*)pclMsg->cData;

	CreateInterface(NBLACK_WAR_REWARD_DLG);
	
	CNBlackWarReformReward* pBlackWarResult = (CNBlackWarReformReward*)m_pDialog[ NBLACK_WAR_REWARD_DLG ];	
	pBlackWarResult->SetMyReward(pclInfo);
}

//[�߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �̺�Ʈ ���� �� ����� �˸� �޽���.]  
void cltClient::DoMsg_GAMEMSG_RESPONSE_BLACK_WAR_REFORM_VILLAGE_RESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Black_War_Reform_Village_Result* pclInfo = (cltGameMsgResponse_Black_War_Reform_Village_Result*)pclMsg->cData;
	
	CreateInterface(NBLACK_WAR_REWARD_DLG);

	CNBlackWarReformReward* pBlackWarResult = (CNBlackWarReformReward*)m_pDialog[ NBLACK_WAR_REWARD_DLG ];	
	pBlackWarResult->SetVillageReward(pclInfo);
}

// [����] �����ڽ��κ��� ����������� ����� ����ȹ��â ���
void cltClient::DoMsg_GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RareItemFromTreasureBox* pclInfo = (cltGameMsgResponse_RareItemFromTreasureBox*)pclMsg->cData;

	cltClient* pclclient = (cltClient*)pclClient;

	NTCHARString64		ntstrTitle( GetTxtFromMgr(7898) );
	NTCHARString256		ntstrMsg( GetTxtFromMgr(7899) );


	ntstrMsg.Replace( TEXT("#user#"), pclInfo->tszUserName );
	ntstrMsg.Replace( TEXT("#treasurebox#"), pclInfo->cltTreasureBox.GetShortName(pclItemManager) );
	ntstrMsg.Replace( TEXT("#item#"), pclInfo->cltGetItem.GetShortName(pclItemManager) );

	PushEffect(pclclient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

	if(pclclient->m_pDialog[NRAREITEM_DLG ] == NULL)	CreateInterface( NRAREITEM_DLG );
	((CNRareItemDlg*)pclclient->m_pDialog[NRAREITEM_DLG ])->SetBestGacha(&pclInfo->cltGetItem, pclInfo->tszUserName, ntstrTitle, ntstrMsg);			
	
}

//[�߰� : Ȳ���� 2008. 2. 28 =>  ��Ƽ��Ʈ ���� �޽��� ó��. S->C]
void cltClient::DoMsg_GAMEMSG_RESPONSE_ARTIFACT_MIXTURE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Artifact_Mixture* pclInfo = (cltGameMsgResponse_Artifact_Mixture*)pclMsg->cData;

	cltItem* pCharItemList = &pclCM->CR[1]->pclCI->clCharItem.clItem[0];
	SI32 siSize = sizeof( cltItem );

	// ����� ��� �������� ����.
	ZeroMemory( &pCharItemList[ pclInfo->m_siEquipItemPos ],  siSize);
	memcpy( &pCharItemList[ pclInfo->m_siEquipItemPos ], &pclInfo->m_clEquipItem, siSize);

	// ����ü�� ���ŵȴ�.
	SI32		InvPos		= 0;
	cltItem*	pclRecvItem = NULL;
	for(int Count = 0; Count < MAX_ITEM_ARTIFACT_MIXTURE; ++Count)
	{
		InvPos		=  pclInfo->m_siCrystalItemPos[ Count ];
		if( 0 >= InvPos )
			continue;

		pclRecvItem = &pclInfo->m_clCrystalItem[ Count ];
		
		ZeroMemory( &pCharItemList[ InvPos ],  siSize );
		memcpy( &pCharItemList[ InvPos ], pclRecvItem, siSize );
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[ ARTIFACT_BASE_DLG ] == NULL)	
		return;

	((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactMixtureDlg.MixtureSuccess( &pclInfo->m_clEquipItem );
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactMixtureDlg.m_bGaugeAction = true;
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactMixtureDlg.m_clMixtureSuccessItem.Set(&pclInfo->m_clEquipItem);
}

//[�߰� : Ȳ���� 2008. 2. 28 =>  ��Ƽ��Ʈ ���� �޽��� ó��. S->C]
void cltClient::DoMsg_GAMEMSG_RESPONSE_ARTIFACT_REMOVE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Artifact_Remove* pclInfo = (cltGameMsgResponse_Artifact_Remove*)pclMsg->cData;

	cltItem* pCharItemList = &pclCM->CR[1]->pclCI->clCharItem.clItem[0];
	SI32 siSize = sizeof( cltItem );

	// ����� ��� �������� ����.
	ZeroMemory( &pCharItemList[ pclInfo->m_siEquipItemPos ],  siSize);
	memcpy( &pCharItemList[ pclInfo->m_siEquipItemPos ], &pclInfo->m_clEquipItem, siSize);

	// ����� ����ü ���ſ� �������� ����.
	SI32 siPos = -1;
	for( SI32 Count = 0; Count < MAX_CRYSTAL_NUM; ++Count )
	{
		if( pclInfo->m_clCreateCrystalItem[Count].siUnique && 0 < pclInfo->m_clCreateCrystalItem[Count].siItemNum )
		{
			// ���� ����ü.(���� ����ü)
			siPos = pclInfo->m_siCrystalItemPosList[ Count ];
			ZeroMemory( &pCharItemList[ siPos ],  siSize);
			memcpy( &pCharItemList[ siPos ], &pclInfo->m_clCrystalItemList[ Count ], siSize);

			// ������ ����ü.(��� ���� ���ִ� ����ü)
			siPos = pclInfo->m_siCreateCrystalItemPos[ Count ];
			ZeroMemory( &pCharItemList[ siPos ],  siSize);
			memcpy( &pCharItemList[ siPos ], &pclInfo->m_clCreateCrystalItem[ Count ], siSize);
		}
		else if( pclInfo->m_siCrystalItemPosList[Count] && 0 <= pclInfo->m_clCrystalItemList[Count].siItemNum )
		{
			// ���� ����ü.(���� ����ü)
			siPos = pclInfo->m_siCrystalItemPosList[ Count ];
			ZeroMemory( &pCharItemList[ siPos ],  siSize);
			memcpy( &pCharItemList[ siPos ], &pclInfo->m_clCrystalItemList[ Count ], siSize);
		}
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[ ARTIFACT_BASE_DLG ] == NULL)	
		return;

	((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactRemoveDlg.RemoveSuccess(&pclInfo->m_clEquipItem);
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactRemoveDlg.m_bGaugeAction = true;
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactRemoveDlg.m_clRemoveSuccessItem.Set(&pclInfo->m_clEquipItem);
}

//[�߰� : Ȳ���� 2008. 2. 28 =>  ��Ƽ��Ʈ ���� ���� �޽��� ó��. S->C]
void cltClient::DoMsg_GAMEMSG_RESPONSE_ARTIFACT_SLOT_CREATE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Artifact_Slot_Create* pclInfo = (cltGameMsgResponse_Artifact_Slot_Create*)pclMsg->cData;

	cltItem* pCharItemList = &pclCM->CR[1]->pclCI->clCharItem.clItem[0];
	SI32 siSize = sizeof( cltItem );

	// ����� ��� �������� ����.
	ZeroMemory( &pCharItemList[ pclInfo->m_siEquipItemPos ],  siSize);
	memcpy( &pCharItemList[ pclInfo->m_siEquipItemPos ], &pclInfo->m_clEquipItem, siSize);

	// ����� ����ü ���ſ� �������� ����.
	ZeroMemory( &pCharItemList[ pclInfo->m_siCrystalItemPos ],  siSize);
	memcpy( &pCharItemList[ pclInfo->m_siCrystalItemPos ], &pclInfo->m_clCrystalItem, siSize);

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[ ARTIFACT_BASE_DLG ] == NULL)	
		return;
	
	((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactSlotCreateDlg.SlotCreateSuccess( &pclInfo->m_clEquipItem );
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactSlotCreateDlg.m_bGaugeAction = true;
	//((NArtifactBaseDlg*)pclclient->m_pDialog[ ARTIFACT_BASE_DLG ])->m_NArtifactSlotCreateDlg.m_clCreateSlotSuccessItem.Set(&pclInfo->m_clEquipItem);
}
// [���� CRC üũ�� ���� �亯]
void cltClient::DoMsg_GAMEMSG_RESPONSE_FILECRCCHECK( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_FileCRCCheck* pclInfo = (cltGameMsgResponse_FileCRCCheck*)pclMsg->cData;
	if ( pclInfo == NULL )		return;

	
	if ( (pclInfo->siResult == 1) && (siMaster <= 0) )
	{
		// CRCüũ �ӽ÷� ����
		//pclCRCFileCheckManager->RequestCheckFile();
	}
}

// [����] ���� �̺�Ʈ ��ü(����, ����)��ŷ ���� ó�� �Լ�. (S->C) => 2008-6-19 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_RANK_INFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_Rank_Info* pclInfo = (cltGameMsgResponse_Server_Event_Rank_Info*)pclMsg->cData;

	// ���� �̺�Ʈ ���� â�� ���ٸ� �����ϰ� ���� ����..
	cltClient* pclclient = (cltClient*)pclClient;
	
	if( pclEventTimeManager->InEventTime("GoonzuDay_Week", &sTime) )
	{
		// ĳ���� ���� â�� �� ������ ����� �ʴ´�.
		if(pclclient->m_pDialog[NSELECTCHAR_DLG])	
			return;	

		if(pclclient->m_pDialog[SERVER_EVENT_RANK_DLG] == NULL)	
			pclclient->CreateInterface(SERVER_EVENT_RANK_DLG);

	    ((NServerEventRankDlg*)pclclient->m_pDialog[SERVER_EVENT_RANK_DLG])->SetServerEventRankInfo(&pclInfo->m_clServerEvent_Rank_Record);
		//pclServerEventManager->SetBonusBufType(pclInfo->m_ServerEventBufKind);
	}
	//else if( pclEventTimeManager->InEventTime("GoonzuDay_Week_Reward", &sTime) )
	{
		//pclServerEventManager->SetBonusBufType(0); 
		pclServerEventManager->SetServerEventRankRecord(&pclInfo->m_clServerEvent_Rank_Record);
	}
}

// [����] ���� �̺�Ʈ ������ŷ ���� ó�� �Լ�. (S->C) => 2008-6-19 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_SERVER_INFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_Server_Info* pclInfo = (cltGameMsgResponse_Server_Event_Server_Info*)pclMsg->cData;
		
	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[SERVER_EVENT_RANK_DLG] == NULL)	
		pclclient->CreateInterface(SERVER_EVENT_RANK_DLG);

	((NServerEventRankDlg*)pclclient->m_pDialog[SERVER_EVENT_RANK_DLG])->SetServerEventServerInfo(pclInfo->m_clServerRankInfo);
}

// [����] ���� �̺�Ʈ �Ϸ� ������ŷ ���� ó�� �Լ�. (S->C) => 2008-6-19 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_DAILY_EVENT_SERVER_INFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_Daily_Server_Info* pclInfo = (cltGameMsgResponse_Server_Event_Daily_Server_Info*)pclMsg->cData;

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[SERVER_EVENT_RANK_DLG] == NULL)	
		pclclient->CreateInterface(SERVER_EVENT_RANK_DLG);

	((NServerEventRankDlg*)pclclient->m_pDialog[SERVER_EVENT_RANK_DLG])->SetServerEventDailyServerInfo(pclInfo->m_clServerDailyRankInfo);
}

// [����] ���� �̺�Ʈ ���η�ŷ ���� ó�� �Լ�. (S->C) => 2008-6-19 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_Personal_Info* pclInfo = (cltGameMsgResponse_Server_Event_Personal_Info*)pclMsg->cData;

	cltClient* pclclient = (cltClient*)pclClient;
	if(pclclient->m_pDialog[SERVER_EVENT_RANK_DLG] == NULL)	
		pclclient->CreateInterface(SERVER_EVENT_RANK_DLG);

	((NServerEventRankDlg*)pclclient->m_pDialog[SERVER_EVENT_RANK_DLG])->SetServerEventPersonalInfo(pclInfo->m_clPersonalRankInfo);
}

// [����] ���� �̺�Ʈ �δ� ���� �� �� �δ��� �ܰ迡 ���� ������ �´°�� ���ʽ� �˸�. (S->C) => 2008-6-19 
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEMAP_BONUS_FIGURE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_InstanceMap_Bonus_Figure* pclInfo = (cltGameMsgResponse_Server_Event_InstanceMap_Bonus_Figure*)pclMsg->cData;

	cltClient* pclclient = (cltClient*)pclClient;

	// ĳ���� ���� â�� �� ������ ����� �ʴ´�.
	if(pclclient->m_pDialog[NSELECTCHAR_DLG])	
		return;	

	if(pclclient->m_pDialog[SERVER_EVENT_INSTANCE_MAP_BONUS] == NULL)	
		pclclient->CreateInterface(SERVER_EVENT_INSTANCE_MAP_BONUS);

	((NServerInstanceMapBounusDlg*)pclclient->m_pDialog[SERVER_EVENT_INSTANCE_MAP_BONUS])->SetIstanceMapStepCount(pclInfo->m_siBonusFigure);
}





// [����] �����̺�Ʈ ����Ʈ ���� ������ ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_START( cltMsg* pclMsg, SI32 id )
{
	if ( NULL == pclMsg )
	{
		return;
	}

	cltGameMsgResponse_Server_Event_Quest_Start* pclInfo = (cltGameMsgResponse_Server_Event_Quest_Start*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	// �ɸ��� ����â���� �ȳ�Ÿ���� �ϱ�
	if ( pclclient->m_pDialog[NSELECTCHAR_DLG] )
	{
		return;
	}

	if ( NULL == pclclient->m_pDialog[SERVER_EVENT_QUEST_DLG] )
	{
		pclclient->CreateInterface( SERVER_EVENT_QUEST_DLG );
	}

	CNServerEventQuestDlg* pclSEQeustDlg = (CNServerEventQuestDlg*)pclclient->m_pDialog[ SERVER_EVENT_QUEST_DLG ];
	if ( NULL == pclSEQeustDlg )
	{
		return;
	}

	pclSEQeustDlg->SetServerEventQuestStart( &pclInfo->m_clQuestData, pclInfo->m_siMaxCharacter, pclInfo->m_siNowAmount, pclInfo->m_bCharacter );
	
}

// [����] �����̺�Ʈ ����Ʈ ���� ������ ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_RUNINFO( cltMsg* pclMsg, SI32 id )
{
	if ( NULL == pclMsg )
	{
		return;
	}

	cltGameMsgResponse_Server_Event_Quest_RunInfo* pclInfo = (cltGameMsgResponse_Server_Event_Quest_RunInfo*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	CNServerEventQuestDlg* pclSEQeustDlg = (CNServerEventQuestDlg*)pclclient->m_pDialog[ SERVER_EVENT_QUEST_DLG ];
	if ( NULL == pclSEQeustDlg )
	{
		cltGameMsgRequest_Server_Event_Quest_Start	clQuestStart;
		cltMsg clMsg(GAMEMSG_REQUEST_SERVER_EVENT_QUEST_START, sizeof(clQuestStart), (BYTE*)&clQuestStart);
		pclClient->pclCM->CR[1]->SendNetMsg( (sPacketHeader*)&clMsg );

		return;
	}

	pclSEQeustDlg->SetServerEventQuestRunInfo( pclInfo->m_siLimiteMinute, pclInfo->m_siNowAmount );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS( cltMsg* pclMsg, SI32 id )
{

	if ( NULL == pclMsg )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltGameMsgResponse_Server_Event_Quest_ClearStatus* pclInfo = (cltGameMsgResponse_Server_Event_Quest_ClearStatus*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	SI16 siMessageType = pclInfo->m_siMessageType;
	if ( (SERVEREVENT_MESSAGETYPE_NONE >= siMessageType) || (SERVEREVENT_MESSAGETYPE_END <= siMessageType) )
	{
		return;
	}

	CNServerEventQuestDlg* pclSEQeustDlg = (CNServerEventQuestDlg*)m_pDialog[ SERVER_EVENT_QUEST_DLG ];
	if ( NULL == pclSEQeustDlg )
	{
		return;
	}



	switch ( siMessageType ) 
	{
		case SERVEREVENT_MESSAGETYPE_QUEST_FAIL:
			{
			}
			break;
		
		case SERVEREVENT_MESSAGETYPE_GETCHAR:
			{
				if ( NULL == m_pDialog[ SERVER_EVENT_INSTANCE_MAP_BONUS ] )
				{
					CreateInterface( SERVER_EVENT_INSTANCE_MAP_BONUS );
				}

				NServerInstanceMapBounusDlg* pclBonusDlg = (NServerInstanceMapBounusDlg*)m_pDialog[ SERVER_EVENT_INSTANCE_MAP_BONUS ];
				if ( NULL == pclBonusDlg )
				{
					return;
				}

				NTCHARString256 strMessage( GetTxtFromMgr(8513) );
				NTCHARString128	strChar( pclSEQeustDlg->GetIndexToText( pclInfo->m_siCharacterIndex ) );

				if ( strChar.IsEmpty() )
				{
					strMessage.Replace( TEXT("[#word#] "), TEXT("") );
				}
				else
				{
					strMessage.Replace( TEXT("#word#"), strChar );
				}
				pclBonusDlg->SetCharMessage( strMessage );

				PushEffect( pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_BGM_GAME_START") ), 0, 0 );
				pclSEQeustDlg->SetServerEventQuestGetChar( pclInfo->m_siCharacterIndex );
				
			}
			break;
			
		case SERVEREVENT_MESSAGETYPE_CHAR_FAIL:
			{
				if ( NULL == m_pDialog[ SERVER_EVENT_INSTANCE_MAP_BONUS ] )
				{
					CreateInterface( SERVER_EVENT_INSTANCE_MAP_BONUS );
				}

				NServerInstanceMapBounusDlg* pclBonusDlg = (NServerInstanceMapBounusDlg*)m_pDialog[ SERVER_EVENT_INSTANCE_MAP_BONUS ];
				if ( NULL == pclBonusDlg )
				{
					return;
				}

				NTCHARString256 strMessage( GetTxtFromMgr(8514) );
				pclBonusDlg->SetCharMessage( strMessage );

				PushEffect( pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_DAILYQUEST_GIVEUP") ), 0, 0 );
			}
			break;

		case SERVEREVENT_MESSAGETYPE_QUEST_ALLCLEAR:
			{
				pclSEQeustDlg->DeleteDialog();
				pclclient->m_pFeastEffectManager->SetAction( 5 );
			}
			break;
	}

}

void cltClient::DoMsg_GAMEMSG_REQUEST_EVENTTIME_UPDATE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_EventTime_Update* pclInfo = (cltGameMsgResponse_EventTime_Update*)pclMsg->cData;

	cltEventTime* pclEventTime = pclClient->pclEventTimeManager->GetEvent(pclInfo->m_szEventName);
	if(pclEventTime)
	{
		pclEventTime->m_bEventActivated = pclInfo->m_bEventActivated;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHECKPROCESS( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_CheckProcess* pclInfo = (cltGameMsgResponse_CheckProcess*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	m_pclCheckProcess->ExcuteCheckProcess(pclInfo->m_siType, pclInfo->m_szModuleName);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHECKPROCESS_RESULT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_CheckProcess_Result* pclInfo = (cltGameMsgResponse_CheckProcess_Result*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )
	{
		return;
	}

	// ���������� ������ Ȥ�� �ٽ��ѹ� Ŭ���̾�Ʈ������ �˻�
	if ( BASIC_GAMEMASTER_LEVEL >= pclchar->GetGameMasterLevel() )
	{
		return;
	}

	TCHAR szMessage[1024] = { '\0', };

	switch ( pclInfo->m_siType )
	{
		case CHECKPROCESS_TYPE_MULTICLIENT:
			{
				
				for ( SI32 siIndex=0; siIndex<Const_Max_SendList; ++siIndex )
				{
					TCHAR szOneLine[128] = { '\0', };
					StringCchPrintf( szOneLine, sizeof(szOneLine), TEXT("%02d :%d\r\n"), (siIndex+2), pclInfo->m_siMultiList[siIndex] );

					StringCchCat( szMessage, sizeof(szMessage), szOneLine );
				}
			}
			break;

		case CHECKPROCESS_TYPE_MACRO:
		case CHECKPROCESS_TYPE_MODULENAME:
			{
				StringCchPrintf( szMessage, sizeof(szMessage), TEXT("MacroName : %s\r\nUserCount : %d"), pclInfo->m_szModuleName, pclInfo->m_siMultiList[0] );
			}
			break;
	}

	g_ErrorMsg.BigSet( TEXT(""), szMessage );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_QUESTION_LIST_GET( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Question_List_Get* pclInfo = (cltGameMsgResponse_Question_List_Get*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;


	if ( NULL == m_pDialog[ NHELPER_QUESTION_LIST_DLG ] )
	{
		CreateInterface( NHELPER_QUESTION_LIST_DLG );
	}
		
	NHelperQuestionListDlg* pDialog = (NHelperQuestionListDlg*)m_pDialog[NHELPER_QUESTION_LIST_DLG];
	pDialog->SetQuestionTileList(	pclInfo->m_siQuestionPersonID, 
									(TCHAR**)pclInfo->m_szQuestionTitle, 
									(TCHAR**)pclInfo->m_szName,
									pclInfo->m_bAleadyAnswer				);
	
	// ���� ��ڳ� ������ ������ ��ư�� �����ٰ��̿�~
	if( 100 < pclchar->GetGameMasterLevel() )
	{
		pDialog->GM_Mode( true );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_QUESTION_CONTENTS_GET( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Question_Contents_Get* pclInfo = (cltGameMsgResponse_Question_Contents_Get*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	if ( NULL == m_pDialog[ NHELPER_QUESTION_LIST_DLG ] )	return;
	
	NHelperQuestionListDlg* pDialog = (NHelperQuestionListDlg*)m_pDialog[NHELPER_QUESTION_LIST_DLG];
	pDialog->SetQuestionContents( pclInfo->m_szQuestionContents );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Add_Answer* pclInfo = (cltGameMsgResponse_Add_Answer*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	// �亯���� â ����.
	if ( NULL == m_pDialog[ NHELPER_QUESTION_OR_ANSWER_DLG ] )
	{
		CreateInterface( NHELPER_QUESTION_OR_ANSWER_DLG );
		NHelperQuestionOrAnswerDlg* pDialog = (NHelperQuestionOrAnswerDlg*)m_pDialog[NHELPER_QUESTION_OR_ANSWER_DLG];
		if( NULL == pDialog ) return;

		pDialog->SetQuestionDlg( ANSWER_DLG ); 
		pDialog->SetQuestionCharInfo( pclInfo->m_szName, pclInfo->m_szQuestionTitle, pclInfo->m_siQuestionPersonID );

		NHelperQuestionListDlg* pDialog2 = (NHelperQuestionListDlg*)m_pDialog[NHELPER_QUESTION_LIST_DLG];
		if( pDialog2 )
		{
			pDialog->SetX( pDialog2->GetX() + (pDialog2->GetWidth()  / 2) - (pDialog->GetWidth() / 2) ); 
			pDialog->SetY( pDialog2->GetY() );  

			pDialog2->DeleteDialog();
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Add_Answer_Complete* pclInfo = (cltGameMsgResponse_Add_Answer_Complete*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	// �亯�� ���� â ����.
	if ( NULL == m_pDialog[ NHELPER_ANSWER_COMPLETE_DLG ] )
	{
		CreateInterface( NHELPER_ANSWER_COMPLETE_DLG );
		NHelperAnswerCompleteDlg* pDialog = (NHelperAnswerCompleteDlg*)m_pDialog[ NHELPER_ANSWER_COMPLETE_DLG ];
		if( NULL == pDialog ) return;

		pDialog->SetAnswer( pclInfo->m_siAnswerPersonID, pclInfo->m_szAnswerCharName, pclInfo->m_szQuestionTitle, pclInfo->m_szQuestionContents ); 
	}
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE_RESULT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Add_Answer_Complete_Result* pclInfo = (cltGameMsgResponse_Add_Answer_Complete_Result*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	if(m_pDialog[ NOTIFYMSG_DLG ])
	{
		if( pclInfo->m_bResult ) 
		{
			NTCHARString512 kbuffer(GetTxtFromMgr(9115));
			kbuffer.Replace( "#itemname#",	pclClient->pclItemManager->GetName(pclInfo->m_siItemUnique) );
			kbuffer.Replace( "#num#",		SI16ToString(pclInfo->m_siItemNum) );

			m_pDialog[ NOTIFYMSG_DLG ]->SetText(GetTxtFromMgr(5614), kbuffer);	
		}
		else
		{
			m_pDialog[ NOTIFYMSG_DLG ]->SetText(GetTxtFromMgr(5614), GetTxtFromMgr(9116));	
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETMUTE( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_SetMute* pclInfo = (cltGameResponse_SetMute*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	if( pclCM->IsValidID(id) == false )		return;
	cltCharClient* pclchar = pclCM->GetCharClient(id);
	if( pclchar == NULL )					return;

	if( pclInfo->m_bMaster )
	{
		// ��� �޽��� ó��
		NTCHARString256		kText;

		if( pclInfo->m_stMuteTime.wYear <= 0 )
		{
			kText = "#charname# is canceled mute ";
			kText.Replace( "#charname#", pclInfo->m_kCharName );
		}
		else
		{
			SI64 siTimeDiff = TimeOperation(&pclInfo->m_stMuteTime, &sTime);

			kText = "#charname# is mute during #minute# minutes.";

			kText.Replace( "#charname#", pclInfo->m_kCharName );
			kText.Replace( "#minute#", SI32ToString(siTimeDiff / (uiSec * 60))  );
		}

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( TEXT("MUTE"), kText);
	}
	else
	{
		// ���� �޽��� ó��
		NTCHARString256		kText;
		NTCHARString256		kTitle(GetTxtFromMgr(5614));

		// �ð� ����
		memcpy(&pclchar->m_stMuteTime, &pclInfo->m_stMuteTime, sizeof(pclchar->m_stMuteTime));

		if(pclInfo->m_stMuteTime.wYear > 0)
		{
			SI64 siTimeDiff = TimeOperation(&pclInfo->m_stMuteTime, &sTime);

			kText = GetTxtFromMgr(9626);
			kText.Replace("#minute#", SI32ToString(siTimeDiff / (uiSec * 60)));
		}
		else
		{
			kText = GetTxtFromMgr(9627);
		}

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( kTitle, kText);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MUTELIST( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_MuteList* pclInfo = (cltGameResponse_MuteList*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	NTCHARString<2048>	kList;
	for(SI32 i=0; i<pclInfo->m_siCount; i++)
	{
		kList += pclInfo->m_szPersonNames[i];
		kList += "\r\n";
	}

	g_ErrorMsg.BigSet("MUTELIST", kList);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ELIXIR_NPC_ITEM_TYPE_LIST_GET( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
    if ( NULL == pclchar )	return;

	cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get* pclInfo = (cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	if( m_pDialog[ NELIXIR_NPC_DLG ] )	
	{
		((NElixirNPCDlg*)m_pDialog[NELIXIR_NPC_DLG ])->SetItemListInfo(pclInfo->m_siItemUnique, pclInfo->m_siWaterNum);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ELIXIR_SET( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_Elixir_Set* pclInfo = (cltGameMsgResponse_Elixir_Set*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	SI32 siID = 0;
	if( 0 < pclInfo->m_siCharUnique )
	{
		siID = pclCM->GetIDFromCharUnique( pclInfo->m_siCharUnique );
		pclchar = (cltCharClient*)pclCM->GetCharClient( siID );
		if( NULL == pclchar ) return;
	}	

	if( pclchar->pcltElixir ) 
	{
		pclchar->pcltElixir->SetEndMinuteVary(  pclInfo->m_pcltElixirInfo.m_siEndMinuteVary	);	
		pclchar->pcltElixir->SetMultiple	 (  pclInfo->m_pcltElixirInfo.m_uiMultiple		);
		pclchar->pcltElixir->SetPoint		 (  pclInfo->m_pcltElixirInfo.m_siPoint			);		
		pclchar->pcltElixir->SetStr			 (  pclInfo->m_pcltElixirInfo.m_siStr			);		
		pclchar->pcltElixir->SetDex			 (  pclInfo->m_pcltElixirInfo.m_siDex			);		
		pclchar->pcltElixir->SetVit			 (  pclInfo->m_pcltElixirInfo.m_siVit			);		
		pclchar->pcltElixir->SetMag			 (  pclInfo->m_pcltElixirInfo.m_siMag			);		
		pclchar->pcltElixir->SetHnd			 (  pclInfo->m_pcltElixirInfo.m_siHnd			);		
		pclchar->pcltElixir->SetWis			 (  pclInfo->m_pcltElixirInfo.m_siWis			);	
	}	
	
	// ������ ����Ʈ ����ġ.
	pclInfo->m_pcltElixirInfo.m_uiMultiple ? pclchar->bElixirSwitch = true : pclchar->bElixirSwitch = false;

	if(m_pDialog[NELIXIR_USE_DLG])
	{
		DestroyInterface( m_pDialog[NELIXIR_USE_DLG] );
		NTCHARString128 kbuffer( GetTxtFromMgr(9758) );
		kbuffer.Replace( "#multiple#",	SI32ToString( pclchar->pcltElixir->GetMultiple() ) );
		
		m_pDialog[NOTIFYMSG_DLG]->SetText( GetTxtFromMgr(5614), kbuffer );				
	}

	if( m_pDialog[NELIXIR_STATUS_DLG] && id == siID) 
		((NElixirStatusDlg*)m_pDialog[NELIXIR_STATUS_DLG])->SetElixirInfo( pclchar->pcltElixir );
}



void cltClient::DoMsg_GAMEMSG_RESPONSE_BALANCECANUSECURRENCY( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_BalanceCanUseCurrency* pclInfo = (cltGameMsgResponse_BalanceCanUseCurrency*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	m_pclBalanceCurrencyMgr->SetCanUserMoney(pclInfo->m_siCanUseMoney);


	if(m_pclBalanceCurrencyMgr->GetCanUseMoney() >= m_pclBalanceCurrencyMgr->GetBuffCost())
		CreateInterface(NBALANCECURRENCY_DLG);			
	else
	{
		TCHAR *pTitle = GetTxtFromMgr(5614);
		TCHAR *pText = GetTxtFromMgr(10336);
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
	}
}


//	[��ȣ] ��û�� ��� ���� ��ȭ��
void cltClient::DoMsg_GAMEMSG_RESPONSE_GETBALANCECANUSECURRENCY( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_BalanceCanUseCurrency* pclInfo = (cltGameMsgResponse_BalanceCanUseCurrency*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

    m_pclBalanceCurrencyMgr->SetCanUserMoney(pclInfo->m_siCanUseMoney);

	// ���� ��밡���� ��ȭ���� ��������Ѵٸ�
	if(pclInfo->m_bNeedShowMSG == true)
	{
		TCHAR *pTitle = GetTxtFromMgr(5614);
		NTCHARString256 strCanUseMoney;
		g_JYLibFunction.SetNumUnit(pclInfo->m_siCanUseMoney,strCanUseMoney, 256);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, strCanUseMoney);
	}
}

//-------------------------------------------------------------------------------------------------------------------
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
//-------------------------------------------------------------------------------------------------------------------
void cltClient::DoMsg_GAMEMSG_RESPONSE__RACCOONEVENT_TOGOONZU( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_SetRaccoonEventToGoonzu* pclInfo = (cltGameMsgResponse_SetRaccoonEventToGoonzu*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	//((CNGoonzuRaccoonEventDlg*)m_pDialog[ NRACCOONEVENT_CHANGE_GOONZUEVENT_DLG ])->SetComboX(pclInfo->m_GoonzuRaccoonEventData);	// �޺��ڽ������� ���� ã�Ƽ� ��Ŀ���� �����

}
void cltClient::DoMsg_GAMEMSG_RESPONSE__GOONZURACCOONEVENT_SETINFO( cltMsg* pclMsg, SI32 id )
{
	cltCharClient* pclchar = (cltCharClient*)pclCM->GetCharClient(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_GoonzuRaccoonEventInfo* pclInfo = (cltGameMsgResponse_GoonzuRaccoonEventInfo*)pclMsg->cData;
	if ( NULL == pclInfo )	return;

	if(m_pDialog[ NRACCOONEVENT_CHANGE_GOONZUEVENT_DLG ])
	{
		for (SI32 i = 0 ; i< MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; i++ ) 
		{
			((CNGoonzuRaccoonEventDlg*)m_pDialog[ NRACCOONEVENT_CHANGE_GOONZUEVENT_DLG ])->SetComboX(&pclInfo->m_GoonzuRaccoonEventData[i],i);	// �޺��ڽ������� ���� ã�Ƽ� ��Ŀ���� �����
		}
	}

}

// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ�� ���
void cltClient::DoMsg_GAMEMSG_REQUEST_RECORD_ACTION(cltMsg* pclMsg, SI32 id)
{
	SI32			siresult = 0;
	cltCharCommon	*pchar;

	cltGameMsgRequest_RecordAction	*pclinfo	=	( cltGameMsgRequest_RecordAction* )pclMsg->cData;

	if( m_pclGMA == NULL )
	{
		m_pclGMA	=	new cltGMA;	

		m_pclGMA->Initialize();

		pchar	=	pclCM->CR[1];



		m_pclGMA->SetHeader_V2( ( char* )pchar->GetName(), pchar->pclCI->clIP.GetLevel(), 
			pclinfo->time_now, pclinfo->szyourip, clSelectedWorldInfo.baseinfo.worldname, 
			pclinfo->siyourpersonid, pchar->clPB.pclCI->clBI.szAccountID, 
			pclMapManager->GetMapName( pchar->GetMapIndex() ), 
			pchar->GetX(), pchar->GetY() );

		m_siGMA_ByAdminPersonID			=	pclinfo->siAdminPersonID;		
		m_bGMA_ReportedByAdminCommand	=	pclinfo->bReportedByAdminCommand;

		siresult	=	1;
	}
	else
	{
		// ���� ������̴�.
		siresult	=	2;
	}

	cltGameMsgResponse_RecordAction	clinfo( siresult, pclinfo->siAdminPersonID, pclinfo->bReportedByAdminCommand );
	cltMsg clMsg( GAMEMSG_RESPONSE_RECORD_ACTION, sizeof( clinfo ), (BYTE*)&clinfo );
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);	

}

// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ ��� �Ϸ��� ��ڿ��� ����	
void cltClient::DoMsg_GAMEMSG_RESPONSE_RECORD_ACTION_FINISHED(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RecordActionFinished	*pclinfo	=	( cltGameMsgResponse_RecordActionFinished* )pclMsg->cData;

	TCHAR* pTitle = GetTxtFromMgr( 40357)	;

	NTCHARString256 szExplain = GetTxtFromMgr(40356);
	szExplain.Replace( "#name1#", pclinfo->szCharName );
	szExplain.Replace( "#name2#", pclinfo->szCharName );

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, szExplain );    
}