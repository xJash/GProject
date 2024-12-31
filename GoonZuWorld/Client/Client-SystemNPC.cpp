//---------------------------------
// 2003/11/11 ���°�
//---------------------------------

#include "Client.h"
#include "Music\Music.h"
#include "SystemNPC\ForeignMerchantNPC\ForeignMerchantNPC.h"
#include "..\CommonLogic\MsgType.h"
#include "..\CommonLogic\Msg\MsgType-NPC.h"
#include "..\CommonLogic\Msg\MsgType-Quest.h"
#include "..\CommonLogic\MsgType-Structure.h"
#include "SystemNPC\SystemNPC.h"

#include "Interface\NPC1\NPCTradeBaseInfo.h"
#include "Interface\NPC1\NPCTradeDlg.h"
#include "Interface\NPC1\NPCTradeDlg.h"
#include "Interface/ForeignMerchant/ForeignMerchantBuyCashItemDlg.h"
#include "NInterface/NNPC1/NNPCTradeDlg.h"
#include "NInterface/NForeignMerchantDlg/NForeignMerchantBuyCashItemDlg.h"
#include "NInterface/NForeignMerchantDlg/NForeignMerchantBuyItemDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "ninterface/nrpmerchantdlg/NRPList.h"
#include "ninterface/nrpmerchantdlg/NRPMerchant.h"
#include "ninterface/nrpmerchantdlg/NRPBase.h"
#include "ninterface/nselectchar/NSelectChar.h"
#include "NInterface\NRareItemDlg\NRareItemDlg.h"
#include "ninterface/NPromoter/NPromoter_InfoDlg.h"
#include "ninterface/NPromoter/NPromoter_UrlDlg.h"
#include "ninterface/NPromoter/NPromoter_Introduce.h"
#include "../Client/NStructureDlg/House/userinfo/NHouseUserNewManagementDlg.h"
#include "../Client/NStructureDlg/House/userinfo/NHouseUserInfoBaseDlg.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

//Client
//#include "Interface/Notify_GetItem_From_Monster/NotifyGetItemFromMonsterDlg.h"
#include "Interface/NotifyGetItemDlg/NotifyGetItemDlg.h"
#include "Interface/DecreePasswdDlg/DecreePasswdDlg.h"
#include "Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "Interface/ToolBarDlg/ToolBarDlg.h"

//----------------------------
// Common
//---------------------------
#include "../Common/Map/Map.h"
#include "Char/CharManager/CharManager.h"
#include "Map/FieldObject/FieldObject.h"

#include "../resource.h"
#include "../Server/Candidate/Candidate.h"
#include "Music/Music.h"
#include "Registry/RegistryMgr.h"
#include "SmallMap/SmallMap.h"
#include "Inventory/ItemInventory.h"
#include "Interface/NPC1/NPCTradeDlg.h"
#include "Interface/ResidentsViewDlg/ResidentsViewDlg.h"
#include "StatusBar/StatusBar.h"
#include "Skill/Skill-Manager.h"

#include "ImageInterface/ResidentLoginDraw/ResidentLoginDraw.h"

#include "../CommonLogic/MsgType-Person.h"


//#include "Interface/ForeignMerchant/ForeignMerchantDlg.h"


//#include "Interface/PartyDlg/PartyDlg.h"
//#include "Interface/PartyInviteDlg/PartyInviteDlg.h"


#include "Interface/FriendDlg/FriendDlg.h"
#include "NInterface/NFriendDlg/NFriendDlg.h"


#include "Interface/FocusManager/FocusManager.h"

#include "Interface/HtmlDlg/HtmlDlg.h"

#include "Interface/RichEditChatMgrDlg/RichEditChatMgrDlg.h"

#include "./ImageInterface/VillageNotice/VillageNotice.h"
#include "./ImageInterface/VillageWarNotice/VillageWarNotice.h"

// ������ ��ǥ ��� ����
#include "Interface/RememberWindowPos/RememberWindowPosMgr.h"

// ���콺 ������ ��ư �������� �޴�
#include "Interface/RightMouseMenu/RightMouseMenu.h"

// ���� ��ܿ� �ִ� ������ �����ִ� ���̾�α�
#include "Interface/ToolBarBaseInfoDlg/ToolBarBaseInfoDlg.h"



#include "Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "AttackEffect/AttackEffectMgr.h"


#include "Prompt/PromptBaseDefinition.h"
#include "Prompt/PromptMgr.h"

#include "DrawSequence/DrawSequence.h"

#include "../Common/Letter/Letter.h"

#include "../Common/Bullet/Bullet.h"
#include "../Common/Smoke/Smoke.h"
#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../Client/ItemInfo/ItemInfo.h"
#include "../Client/QuitConfirm/QuitConfirm.h"

// ����ġ ���� 
#include "Effect/ExpCounter/ExpCounter.h"

#include "../Common/Order/Order.h"
#include "ITZEncrypt.h"

#include "../CommonLogic/MsgRval-Define.h"
#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/MsgType-Item.h"
#include "../CommonLogic/MsgType-House.h"
#include "../CommonLogic/MsgType-Structure.h"
#include "../CommonLogic/Msg/MsgType-Horse.h"
#include "../CommonLogic/Msg/MsgType-Quest.h"
#include "../CommonLogic/Msg/MsgType-Village.h"
#include "../CommonLogic/Msg/MsgType-ItemMall.h"



#include "Effect/FireFly/FireFlyMgr.h"
#include "Cursor/Cursor.h"

#include "StatusBar/ChatStatusBar/ChatStatusBarBaseInfo.h"
#include "StatusBar/ChatStatusBar/ChatStatusBar.h"

// ä�� ����. 
#include "Interface/DrawChat/DrawChatSurface.h"
#include "Interface/DrawChat/DrawChat.h"

// ĳ���� �̸� ��� ����
#include "Interface/DrawCharName/DrawCharNameSurface.h"


// �ӼӸ� ä�� ����. 
//#include "Interface/PrivateChatDlg/PrivateChatBaseInfo.h"
//#include "Interface/PrivateChatDlg/PrivateChatDlgMgr.h"

// ���� on off â
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "NInterface/NChatDlg/NChatDlg.h"


// �ʻ�� ȿ��. 
#include "Char/CharClient/CharCriticalEffect/CharCriticalEffect.h"

#include "../CommonLogic/CityHall/TaxPaymentListDlg.h"

// ������ ĳ���� ���ǽ� ������. 
#include "Char/CCD/CCDSurfaceMgr.h"
//�̵� ǥ��. 
#include "Effect/ClickEffect/ClickEffect.h"
// ���� ��� 
#include "GameContract/GameContract.h"
// ���� �� ���� 
#include "NInterface/NVillageDetailInfo/NVillageDetailInfo.h"

// ������ ��� �˸�â
#include "Interface/VillageWarInfoDlg/VillageWarInfoDlg.h"

#include "Interface/SearchDetailDlg/SearchDetailDlg.h"

#include "../Common/School/School.h"

// �ǹ�
#include "../../CommonLogic/Cityhall/Cityhall.h"
#include "../../CommonLogic/Bank/Bank-Manager.h"
#include "../../CommonLogic/Stock/Stock.h"
#include "../../CommonLogic/Market/Market.h"
#include "../../CommonLogic/House/House.h"
#include "../../CommonLogic/Hunt/Hunt.h"
#include "../../CommonLogic/PostOffice/PostOffice.h"
#include "../../CommonLogic/HorseMarket/HorseMarket.h"
#include "../../CommonLogic/RealEstate/RealEstate.h"
#include "../../CommonLogic/SummonMarket/SummonMarket.h"
#include "../../CommonLogic/Land/Land.h"
#include "../../CommonLogic/Feast/Feast.h"
#include "../../CommonLogic/SummonHeroMarket/SummonHeroMarket.h"
#include "../../CommonLogic/Mine/Mine.h"
#include "../../CommonLogic/Guild/Guild.h"

//���
#include "Interface/DeathDlg/DeathDlg.h"
#include "NInterface/NDeathDlg/NDeathDlg.h"

#include "NInterface/NCommonMsgDlg/NCommonMsgDlg.h"

//��й�ȣ �ǰ� 
#include "NInterface/NDecreePasswdDlg/NDecreePasswdDlg.h"

//����

#include "NInterface/NVillageWarInfoDlg/NVillageWarInfoDlg.h"
#include "NInterface/NResidentsDlg/NResidentsDlg.h"

// �ǹ� ����
#include "NStructureDlg/CityHall/NBeResidentDlg.h"
#include "NStructureDlg/CityHall/NCityhallDlg.h"

#include "NInterface/NStatusBarDlg/NStatusBarDlg.h"
#include "NInterface/NChatBardlg/NChatBarDlg.h"

// ��������
#include "ninterface/nmagicinfodlg/MagicInfoDlg.h"

//ũ�������� �̺�Ʈ
#include "NInterface/NChristmasEventDlg/NChristmasEventDlg.h"

#include "ninterface/NQuestNoticeDlg/NQuestNoticeDlg.h"

#include "Interface/pannel/NPannel_SummonDlg.h"
#include "ninterface/NMagicCoolTimeDlg/NMagicCoolTimeDlg.h"

#include "ninterface/NCharHouseDlg/NCharHouseDlg.h"

#include "NInterface/NChangeCharName/NChangeCharName.h"
#include "NInterface/NVanlentineDayNPC/NValentineDayConfessionQuestionDlg.h"
#include "NInterface/NVanlentineDayNPC/NValentineDayConfessionAnswerDlg.h"

extern cltCommonLogic* pclClient;
extern DWORD dwQuitTimer;

void cltClient::DoMsg_GAMEMSG_RESPONSE_SELLNPC(cltMsg* pclMsg, SI32 id)
{
	SI32 returnval = pclMsg->siData32[0];

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
//		if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
//			{
//			CreateInterface( NNPCTRADE1_DLG );
//			}
//		((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG  ])->SetText( returnval );
		if(( m_pDialog[ NNPCTRADE1_DLG ]))
			((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG  ])->SetText( returnval );
	}

	//------------------------------------------
	// NPC���� ������ �Ǹ��ϴ� ����Ʈ ���̾��ٸ�, 
	//------------------------------------------
	SI16 questtype, questunique, para1, para2;
	SI16 questclearcond =  QUEST_CLEAR_COND_SELLNPC;
	if(pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
	{
		cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
		cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		SendMsgToServer((sPacketHeader*)&clMsg);
	}
	
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_BUYNPC(cltMsg* pclMsg, SI32 id)
{
	DoMsg_GAMEMSG_RESPONSE_SELLNPC(pclMsg, id);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NPCSELLITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NPCSellItemInfo *pclNPCSellItemInfo = (cltGameMsgResponse_NPCSellItemInfo *) pclMsg->cData;

	cltNPCMerchantInfo *pNPCMerchantInfo = NULL;

	for ( SI16 k = 0; k < MAX_NPC_MERCHANT_NUMBER; ++k )
	{
		if ( pclNPCItemInfo->clNPCMerchantInfo[ k ].siNPCKind == pclNPCSellItemInfo->siNPCKind )
		{
			pNPCMerchantInfo = &pclNPCItemInfo->clNPCMerchantInfo[ k ];
			break;
		}
	}

	if ( pNPCMerchantInfo == NULL )
	{
		return;
	}

#ifdef _SAFE_MEMORY
	for(SI32 i=0; i<MAX_NPC_ITEM_NUMBER; i++)		pNPCMerchantInfo->clItemInfo[i].Set(&pclNPCSellItemInfo->clNPCInteInfoUnitList[i]);
#else
	memcpy( pNPCMerchantInfo->clItemInfo, pclNPCSellItemInfo->clNPCInteInfoUnitList, sizeof( cltNPCInteInfoUnit ) * MAX_NPC_ITEM_NUMBER );
#endif

	// �߷�Ÿ�ε��� NPC�� ������ �Ǹ������� ��û�ѰŸ�. 
	if( GetUniqueFromHash( TEXT("KIND_GIFTRACCOON") ) == pclNPCSellItemInfo->siNPCKind )
	{
		if( NULL == m_pDialog[ VALENTINEDAY_NPC_DLG ] )
		{
			CreateInterface( VALENTINEDAY_NPC_DLG );
		}
	}
	else if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(( m_pDialog[ NNPCTRADE1_DLG ])==NULL)
		{
			CreateInterface( NNPCTRADE1_DLG );
		}
		((CNNPCTradeDlg*)m_pDialog[ NNPCTRADE1_DLG  ])->LoadNPCInventory();
	}
	
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRESELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PreSellToForeignMerchant *pclPreSellInfo = (cltGameMsgResponse_PreSellToForeignMerchant*) pclMsg->cData;

	if (m_pDialog[NFOREIGNMERCHANTBUYITEM_DLG])
	{
		TCHAR *pTitle = GetTxtFromMgr(2205);
		TCHAR *pText;
		TCHAR buf[256];
		stMsgBox MsgBox;

		// ������ ���� �������� ���� ���Ƽ �ؽ�Ʈ�� ������
		NTCHARString128 strDurabilityPenalty = TEXT("");

		if ( IsCountrySwitch(Switch_NewDurability) )
		{
			if ( 100 > pclPreSellInfo->siDurabilityPenalty )
			{
				strDurabilityPenalty = GetTxtFromMgr(30523);

				strDurabilityPenalty.Replace( TEXT("#percent#"), SI16ToString(pclPreSellInfo->siDurabilityPenalty) );
			}
		}
		
		// ������ ���� ���Ұų� ������ �ƿ� ���� �������̸� �����ݿ� ��
		if (pclPreSellInfo->siRemainDay > 2 || (pclPreSellInfo->siRemainDay == 0 && pclPreSellInfo->siPercent == 100 && pclPreSellInfo->siPrice != 0))
		{
			//[�߰� : Ȳ���� 2007. 12 .5 ���� ���ο��� �Ĵ� ���ǿ� ���� ����.]
			switch(pclPreSellInfo->uiRareInfo)
			{
				case RARELEVEL_1:	pText = GetTxtFromMgr(7690); break;	
				case RARELEVEL_2:	pText = GetTxtFromMgr(7691); break;
				case RARELEVEL_5:	pText = GetTxtFromMgr(7628); break;
				default:			pText = GetTxtFromMgr(5780); break;	
			}
			
			if(RARELEVEL_1 == pclPreSellInfo->uiRareInfo || 
			   RARELEVEL_2 == pclPreSellInfo->uiRareInfo ||
			   RARELEVEL_5 == pclPreSellInfo->uiRareInfo	)
			{
				StringCchPrintf(buf, 256, pText, pclPreSellInfo->siPrice); 
			}
			else
			{
				StringCchPrintf(buf, 256, pText); 
			}

			// �۷ι��� �ƴϸ� �Ϲ� ������ �Ǹ� �޽����� ����.
			if(!IsCountrySwitch(Switch_SellToForeignMerchant))
			{	
				pText = GetTxtFromMgr(5780);
				StringCchPrintf(buf, 256, pText); 
			}
			
			// �������� ���� �г�Ƽ ǥ��
			if ( IsCountrySwitch(Switch_NewDurability) )
			{
				StringCchCat( buf, 256, strDurabilityPenalty );
			}
			
			MsgBox.Set( (CNForeignMerchantBuyItemDlg*)m_pDialog[NFOREIGNMERCHANTBUYITEM_DLG], pTitle, buf, MSGBOX_TYPE_YESNO, 0 );
			SetMsgBox( &MsgBox, NULL, 0 );
		}
		// ������ 0~2�� �������� �׿����� �ۼ�Ʈ�� ��
		else if (pclPreSellInfo->siRemainDay >= 0)
		{
			TCHAR		szPrice[64] = { '\0', };
			GMONEY		siPrice = pclPreSellInfo->siPrice ;
			g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));
			NTCHARString512	kText(GetTxtFromMgr(5778));
			kText.Replace("#percent#",SI16ToString(pclPreSellInfo->siPercent));
			kText.Replace("#money#",szPrice);

			/*pText = GetTxtFromMgr(5778);
			StringCchPrintf(buf, 256, pText, pclPreSellInfo->siPercent, pclPreSellInfo->siPrice);*/

			// �������� ���� �г�Ƽ ǥ��
			if ( IsCountrySwitch(Switch_NewDurability) )
			{
				StringCchCat( buf, 256, strDurabilityPenalty );
			}

			MsgBox.Set( (CNForeignMerchantBuyItemDlg*)m_pDialog[NFOREIGNMERCHANTBUYITEM_DLG], pTitle, kText, MSGBOX_TYPE_YESNO, 0 );
			SetMsgBox( &MsgBox, NULL, 0 );
		}
		// ������ �������� ������
		else
		{
			pText = GetTxtFromMgr(5779);

			MsgBox.Set( (CNForeignMerchantBuyItemDlg*)m_pDialog[NFOREIGNMERCHANTBUYITEM_DLG], pTitle, pText, MSGBOX_TYPE_OK, 0 );
			SetMsgBox( &MsgBox, NULL, 1 );
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTNPCBUYINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ForeignMerchantNPCBuyInfo *pclNPCBuyInfo = (cltGameMsgResponse_ForeignMerchantNPCBuyInfo *) pclMsg->cData;

	pclForeignMerchantNPCMgr->Add( pclNPCBuyInfo->siForeignMerchantKind, pclNPCBuyInfo->siBuyItemType );
	
	pclForeignMerchantNPCMgr->Set
		(
		pclNPCBuyInfo->siForeignMerchantKind,
		pclNPCBuyInfo->siBuyItemType,
		pclNPCBuyInfo->siBuyItemUniqueList,
		pclNPCBuyInfo->siBuyItemAveragePriceList,
		pclNPCBuyInfo->siBuyItemListCount
		);

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ForeignMerchantBuyCashItemInfo *pclNPCBuyCashItemInfo = (cltGameMsgResponse_ForeignMerchantBuyCashItemInfo*) pclMsg->cData;

	if( m_pDialog[ NFOREIGNMERCHANTBUYCASHITEM_DLG ] )
		((CNForeignMerchantBuyCashItemDlg*)m_pDialog[ NFOREIGNMERCHANTBUYCASHITEM_DLG ])->Set( pclNPCBuyCashItemInfo->ItemInfoList, pclNPCBuyCashItemInfo->siBuyItemListCount );
	
//	m_pForeignMerchantBuyCashItemDlg->Set( pclNPCBuyCashItemInfo->ItemInfoList, pclNPCBuyCashItemInfo->siBuyItemListCount );
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ForeignMerchantBuyCashItem *pclNPCBuyCashItem = (cltGameMsgResponse_ForeignMerchantBuyCashItem*) pclMsg->cData;
	
	pclCM->CR[1]->pclCI->clCharItem.clItem[ pclNPCBuyCashItem->siItemPos ].Set( &pclNPCBuyCashItem->clLeftItem );
	
	return;
}
 
void cltClient::DoMsg_GAMEMSG_RESPONSE_GETRECOMMANDPOINT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetRecommandPoint * pclinfo = (cltGameMsgResponse_GetRecommandPoint*) pclMsg->cData;

	if( pclinfo->siResult <= 0 )
	{
        return;
	}

	cltClient * pclclient = (cltClient*)pclClient;

 	if(pclclient->m_pDialog[NRPBASE_DLG])
		((CNRPBase* )pclclient->m_pDialog[NRPBASE_DLG])->SetRecommandPoint(pclinfo->siRecommandPoint);

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BUYRECOMMANDPRODUCT(cltMsg* pclMsg, SI32 id)
{	
	cltGameMsgResponse_BuyRecommandProduct *pclinfo = (cltGameMsgResponse_BuyRecommandProduct*) pclMsg->cData;
	
	cltClient * pclclient = (cltClient*)pclClient;

	if(pclclient->m_pDialog[NRPBASE_DLG])
		((CNRPBase* )pclclient->m_pDialog[NRPBASE_DLG])->SetRecommandPoint(pclinfo->siRecommandPoint);


	const TCHAR * pItemName =	pclClient->pclItemManager->GetName(pclinfo->clBuyItem.siUnique);
	
	if( pItemName != NULL )
	{
		TCHAR * pText = GetTxtFromMgr(6314);
		TCHAR * pTitle = GetTxtFromMgr(1101);

		TCHAR strBuffer[256] = {'\0',};
		
		StringCchPrintf(strBuffer,256,pText,pItemName,pclinfo->siUsedPoint);
        
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, strBuffer );
	}

	return;
}



void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMANDPOINTLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RecommandPointList *pclinfo = (cltGameMsgResponse_RecommandPointList*) pclMsg->cData;

	cltClient * pclclient = (cltClient*)pclClient;

	if(pclclient->m_pDialog[NRPBASE_DLG])
	{
		 ((CNRPBase* )pclclient->m_pDialog[NRPBASE_DLG])->RPListTab->
			 SetRecommandPointUserList( pclinfo->sRPListData );
	}

    return;
}

/*
void cltClient::DoMsg_GAMEMSG_RESPONSE_HIRENPC(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HireNPC
}
*/

void cltClient::DoMsg_GAMEMSG_RESPONSE_NPCPAYMENT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NPCPayment *pclInfo = (cltGameMsgResponse_NPCPayment *)pclMsg->cData;
/*
	memcpy( pclCityHallManager->pclHireSystemNPCDlg->m_clHiredNPCPayInfo,
		pclInfo->clHiredNPCPayInfo, sizeof( cltHiredNPCPayInfo ) * pclInfo->siCount );

	pclCityHallManager->pclHireSystemNPCDlg->m_siCount = pclInfo->siCount;
	pclCityHallManager->pclHireSystemNPCDlg->m_bUpdateNPCPaySwitch = TRUE;
*/
	return;
}

//cyj �޼����ڵ鷯 �߰�
void cltClient::DoMsg_GAMEMSG_RESPONSE_USERORDER(cltMsg* pclMsg, SI32 id)
{
	cltOrderData* porder = (cltOrderData*)pclMsg->cData;

	if(porder->ODI.siOrder == ORDER_ATTACK)
		int  a= 0;
	// ������ ĳ���͸� ã�´�. 
	SI32 orderid = 0;
	if(porder->CharUnique == MyCharUnique)
	{
		orderid = 1;
	}
	else
	{
		orderid = cltCharCommon::CharUniqueInfo[porder->CharUnique];
	}

	if(porder->ODI.siOrder == ORDER_MAGIC)
	{
		// ��Ÿ���� ���� �۾�
		SI32 a = 0;
		SI32 targetid	= porder->ODI.siPara2;
		SI32 magickind	= porder->ODI.siPara3;

		// [����] ���� ������ ���� ���.
		SI32	siSubMagickind		= 0;
		SI32 	siSubDelay 			= 0;
		cltCharSkillBookInfo* pclCharSkillBookInfo = pclClient->pclCM->CR[1]->pclCharSkillBookInfo;
		if( pclClient->IsCountrySwitch(Switch_SkillBook) && pclCharSkillBookInfo )
		{
			stMagicAttributeData*	psSubMagicData = pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( magickind, siSubMagickind );
			if( psSubMagicData )
			{
				siSubDelay = psSubMagicData->si32MagicDelay;
			}
		}

		// ĳ������ ��츸 �۵��Ѵ�.
		if ( (m_pDialog[NMAGICCOOLTIME_DLG]) && (0 < magickind) && (1 == orderid) && ( MAGIC_SOULGUARD_FIRE != magickind ) )
		{
			stMagicAttributeData* psMagicData = pclMagicManager->GetMagicAttribute(magickind);
			if ( (psMagicData) && (MAGIC_CASTTYPE_ACTIVE == psMagicData->si08MagicCastType) )
			{
				SI32 siDelayMS = psMagicData->si32MagicDelay * (1000 / ConstFrameRate_Low);
				siDelayMS += (siDelayMS * siSubDelay) / 100;
				if ( 0 < siDelayMS )
				{
					((CNMagicCoolTimeDlg*)m_pDialog[NMAGICCOOLTIME_DLG])->SetActiveMagicCoolTime( siDelayMS );
				}
			}
		}
		else if ( (m_pDialog[PANNEL_SUMMON_DLG]) && (magickind > 1) && orderid == pclClient->pclCM->CR[1]->GetSummonID() )
		{
			stMagicAttributeData* psMagicData = pclMagicManager->GetMagicAttribute(magickind);
			if(psMagicData)
			{
				SI32 siDelayMS = psMagicData->si32MagicDelay * (1000 / ConstFrameRate_Low);
				siDelayMS += (siDelayMS * siSubDelay) / 100;
				if(siDelayMS > 0)		((CNPannel_SummonDlg*)m_pDialog[PANNEL_SUMMON_DLG])->SetMagicCoolTime(siDelayMS);
			}
		}
	}

	//��� ó��
	if(porder->ODI.siOrder == ORDER_SITDOWN && orderid)
	{
		//KHY - 1109 - ��í����- �������漮�߰�
		if( porder->ODI.siPara2 > 0)
		{
			((cltCharClient*)pclCM->CR[orderid])->siCushionUnique = (SI32)porder->ODI.siPara2;
			porder->ODI.siPara2 = 0;
		}
		else
		{
			((cltCharClient*)pclCM->CR[orderid])->siCushionUnique = 0;
		}
	}

	if( porder->ODI.siOrder == ORDER_SPECIAL_ACTION )
	{
		SI32		siSoundEffect	= 0;
		if( pclCM->IsValidID(orderid) == true )
		{
			// ��ȯ���� ó���Ѵ�.
			cltCharCommon* pclsummonchar = pclCM->CR[orderid]	;
			if( pclsummonchar == NULL || pclsummonchar->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )	{	pclsummonchar = NULL;	}
            if( pclsummonchar )
			{
				SI32 siSummonLevel = pclsummonchar->pclCI->clIP.GetLevel();
				// ���� ����
				if( pclsummonchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_SUPERBEARTANG") ) )
				{
					if( porder->ODI.siPara1 == ANITYPE_CRY )		{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Cry") );		}
					if( porder->ODI.siPara1 == ANITYPE_VERYCRY )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Cry") );		}
					if( porder->ODI.siPara1 == ANITYPE_ANGRY )		{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Angry") );	}
					if( porder->ODI.siPara1 == ANITYPE_SURPRISE )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Surprise") );	}
					if( porder->ODI.siPara1 == ANITYPE_SMILE )		{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Smile") );	}
					if( porder->ODI.siPara1 == ANITYPE_PLAY )		{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_Beartang_Play") );		}
				}
				// ���� �絹��
				if( pclsummonchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPHPET") ) )
				{
					if( porder->ODI.siPara1 == ANITYPE_EAT )			{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_EAT")     );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHSMILE )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_SMILE")   );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHCRY )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_CRY")     );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHDANCE )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_DANCE")   );	}
					if( porder->ODI.siPara1 == ANITYPE_EMIT )			{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_EMIT")    );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHSUPRISE ){	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_SUPRISE") );	}
				}
				// ���� �絹������
				if( pclsummonchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_RUDOLPHPET_T") ) )
				{
					if( porder->ODI.siPara1 == ANITYPE_EAT )			{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_EAT")     );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHSMILE )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_SMILE")   );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHCRY )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_CRY")     );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHDANCE )	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_DANCE")   );	}
					if( porder->ODI.siPara1 == ANITYPE_EMIT )			{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_EMIT")    );	}
					if( porder->ODI.siPara1 == ANITYPE_ROUDOLPHSUPRISE ){	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLPHPET_SUPRISE") );	}
				}
				// [����] ��ȯ�� �巡��.
				if( pclsummonchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_DRAGON_YONGGARY") ) )
				{
					if( porder->ODI.siPara1 == ANITYPE_PLAY		)	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_DRAGONYONGGARY_PLAY") );		}
					if( porder->ODI.siPara1 == ANITYPE_SURPRISE	)	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_DRAGONYONGGARY_SURPRISE") );	}
					if( porder->ODI.siPara1 == ANITYPE_ANGRY	)	{	siSoundEffect =	pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_DRAGONYONGGARY_ANGRY") );		}
				}
			}

			if ( siSoundEffect )	{	PushEffect( siSoundEffect, 0, 0 );		}


			// ��ȣ���� �̶��
			if ( IsCountrySwitch(Switch_SoulGuard) )
			{
				cltCharClient* pclSoulGuardChar = pclCM->GetCharClient( orderid );
				if ( (pclSoulGuardChar) && (IDENTITY_SOULGUARD == pclSoulGuardChar->clIdentity.siIdentity) )
				{
					cltCharClient* pclSoulGuardParentChar =	pclCM->GetCharClient( pclSoulGuardChar->GetSoulGuardParentCharID() );
					if ( pclSoulGuardParentChar )
					{
						pclSoulGuardParentChar->dwSoulGuardSF_Clock = CurrentClock;
						pclSoulGuardParentChar->siSoulGuardSF_Kind	= pclSoulGuardChar->GetKind();
					}
				}
			}
		}
	}

	// ĳ���Ϳ��� ����� ������. 
	if(orderid)
	{
		LetOrder(porder, orderid);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CLIENTCHARUNIQUE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ClientCharUnique* pclInfo = (cltGameMsgResponse_ClientCharUnique*)pclMsg->cData;

	// CharUnique���� �޾Ƽ� �����Ѵ�. 
	MyCharUnique = pclInfo->siCharUnique;

	// ��ȣȭŰ�� �޾Ƽ� �����Ѵ�. 
	ITZEncrypt* pencrypt = pGameSession->GetEncrypt();

	pencrypt->SetKey(pclInfo->uiKey1, pclInfo->uiKey2);

	// ��ȣȭŰ�� ���� �����κ��� �޾����� Ȯ���Ѵ�. 
	bGameServerSecretKeySwitch	= true;

	//������ Ȯ���Ѵ�. 
	if(pclInfo->siVersion	> siVersion)
	{
		TCHAR* pTitle = GetTxtFromMgr(818);
		TCHAR* pText  = GetTxtFromMgr(819);


		MsgBox( pTitle, pText, siVersion, pclInfo->siVersion);
		dwQuitTimer = 1;	// ������ ���� ��Ų��. 
	}

	// ��ȣ�� ������ ���θ� Ȯ���Ѵ�. 

	/*--------------------------------------------------------------------
	CreateInterface �� �߱� ������ ��й�ȣ ����ǰ� �˸�â�� �����Ǳ� 
	�� �� �ؾ� �ϱ� ������  ���⼭ ��.
	--------------------------------------------------------------------*/					
	//FullScreen Mode �϶� 
	//	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	//	{
	bool Compareflag= false;
	TCHAR accountid[FILE_NAME_SIZE] = TEXT("") ;
	TCHAR password[FILE_NAME_SIZE] = TEXT("") ;

	StringCchCopy(accountid, FILE_NAME_SIZE, szID);
	//	_tcscpy(m_szAccountID,accountid);
	_tcslwr(accountid);

	StringCchCopy(password, FILE_NAME_SIZE, szPassword);
	_tcslwr(password);

	if ( !_tcsicmp(accountid,password) ) Compareflag=false ;
	if ( _tcsstr(accountid,password) ) Compareflag=false ;
	if ( _tcslen(password) < 4 ) Compareflag=false ;

	bool bNumber = false ;
	bool bString = false ;

	for ( SI32 i = 0 ; i < FILE_NAME_SIZE ; i++ )
	{
		if ( password[i] == '\0' || password[i] == NULL )
			break;

		if ( password[i] >= '0' && password[i] <= '9' && !bNumber )
			bNumber = true ;

		if ( password[i] >= 'a' && password[i] <= 'z' && !bString )
			bString = true ;

		if ( bNumber && bString )
		{
			Compareflag=true;
			break;
		}
	}

	//if(Compareflag==false)
	//{  
	//	if( pclClient->siServiceArea ==  ConstServiceArea_Korea )
	//	{

	//		if(m_pDialog[ NDECREEPASSWD_DLG]==NULL)
	//		{
	//			CreateInterface(NDECREEPASSWD_DLG);						
	//		}
	//	}
	//	//((CNDecreePasswdDlg*)m_pDialog[ NDECREEPASSWD_DLG])->Set(szID, szPassword);
	//}				

	//	}
	//������ ��� �϶�.
	/*	else
	{
	m_pDecreePassWdDlg->Set(szID, szPassword);
	}


	*/


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Notice* pclnotice = (cltGameMsgResponse_Notice*)pclMsg->cData;

	// �޽����� �м��ؾ� �Ѵ�. 
	TCHAR playername[MAX_PLAYER_NAME];
	TCHAR chattext[256];

	memcpy(playername, pclnotice->szChatText, MAX_PLAYER_NAME);
	playername[ pclnotice->PlayerNameLength ] = NULL;

	MStrCpy(chattext, &pclnotice->szChatText[pclnotice->PlayerNameLength], 100);

	// �޽����� ��½�Ų��. 
	//			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_NOTICEADMIN")), 0, 0);

	TCHAR buffer[256];
	StringCchPrintf(buffer, 256, TEXT("[%s]%s"), playername, chattext); 
	// GM ����(/nt)�ϰ�� �� ����
	if ( pclnotice->m_bGMNotice )
	{
		pclMessage->SetMsg(buffer, 0, RGB(242, 120, 185), RGB(0,0,0) );
	}
	else
	{
		pclMessage->SetMsg(buffer, 0, RGB(255, 255, 0), RGB(0,0,0) );
	}
	
	//g_ChatStatusBar.ChatDataRecv(playername, chattext);

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		//KHY - 0129 - �ϴ� ä��â�� ���� ��¿��θ� �����Ѵ�. 
		if(pclnotice->UseChatBarNotic)
		{
			if( m_pDialog[ STATUSBAR_DLG  ] )
			{
				((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->MasterNotifyChatRecv( playername, chattext );
			}
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHARLIST(cltMsg* pclMsg, SI32 id)
{
	// ���� ĳ���� ������ ����Ʈ�� �ִ´�. 
	cltCharListInfo* pclinfo = (cltCharListInfo*)pclMsg->cData;
    PutCharList(pclinfo);


	if( m_pDialog[ NSELECTCHAR_DLG ] != NULL)
	{
		((CNSelectCharDlg*)m_pDialog[ NSELECTCHAR_DLG ])->SetSelectChar(CurrentCharInfoList);
	}

	if ( true == IsCountrySwitch(Switch_CharHouse) )
	{
		if ( m_pDialog[NCHARHOUSE_DLG] )
		{
			((CNCharHouseDlg*)m_pDialog[NCHARHOUSE_DLG])->SetCharHouseList();
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DELUSERCHAR(cltMsg* pclMsg, SI32 id)//�ɸ��ͻ���
{
	// ĳ���� ������ ���ش�. 
	cltGameMsgResponse_DelUserChar* pclinfo = (cltGameMsgResponse_DelUserChar*)pclMsg->cData;
	DeleteCharList(pclinfo);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PREDELUSERCHAR(cltMsg* pclMsg, SI32 id)//�ɸ��ͻ��������Ⱓ.
{
	// ĳ���� ������ ���ش�. 
	cltGameMsgResponse_PreDelUserChar* pclinfo = (cltGameMsgResponse_PreDelUserChar*)pclMsg->cData;


}
void cltClient::DoMsg_GAMEMSG_RESPONSE_MAKENEWCHAR(cltMsg* pclMsg, SI32 id)
{
	// ���� ĳ���� ������ ����Ʈ�� �ִ´�. 
	cltCharListInfo* pclinfo = (cltCharListInfo*)pclMsg->cData;
	PutCharList(pclinfo);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGESTRUCT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageStruct* pclinfo = (cltGameMsgResponse_VillageStruct*)pclMsg->cData;

	SI32 ref = pclinfo->VillageUnique;
	if(ref >= 0)
	{
		int i;
		// Ŭ���̾�Ʈ�� ������ �������� �ʰ� �ٽ� �����ϴ� ��춧���� �ǹ����� �� �ʱ�ȭ �Ѵ�.
		pclVillageManager->pclVillageInfo[ref]->clVillageVary.clStructureInfo.Initialize();
	
		for(i = 0;i < MAX_CONSTRUCTION_NUM;i++)
		{
			pclVillageManager->pclVillageInfo[ref]->clVillageVary.clStructureInfo.Set(pclinfo->siVillageStructureInfo[i], i);
		}

		// ������ ������Ʈ �Ѵ�. 
		pclMapManager->MakeLastMap(pclMapManager->CurrentMapIndex);

		// ������ �ǹ� ������ �� �̻� ��ٸ��� �ʴ´�. 
		// ���� ĳ���͸� �����ص� �ȴ�. !
		bWaitVillageStructureInfoSwitch		= false;
	}
	else
	{
		MsgBox(TEXT("fd0284"), TEXT("villageunique:%d"), pclinfo->VillageUnique);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_BUILDSTRUCTURE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_BuildStructure* pclinfo = (cltGameMsgResponse_BuildStructure *)pclMsg->cData;

	if( pclinfo->siVillageUnique < 0 || pclinfo->siVillageUnique >= MAX_VILLAGE_NUMBER)		return;

	// �ǹ� �߰� 
	pclVillageManager->pclVillageInfo[ pclinfo->siVillageUnique ]->clVillageVary.clStructureInfo.Set( pclinfo->siStructureUnique, pclinfo->siSlot );

	// ����� (����Ʈ ����) 
//	pclCityHallManager->pclConstructDlg->m_bUpdateSwitch = TRUE;

	// �Ǽ��Ǿ����� �����Ѵ�.
	TCHAR buffer[256];
	SI32 ref = pclVillageStructureSet->FindRefFromUnique(pclinfo->siStructureUnique);
	if(ref != -1)
	{
		TCHAR* pText  = GetTxtFromMgr(820);

		StringCchPrintf(buffer, 256, pText, pclVillageStructureSet->pclVillageStructureInfo[ref]->szName);
		pclMessage->SetMsg(buffer);
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_DESTROYSTRUCTURE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_DestroyStructure* pclinfo = (cltGameMsgResponse_DestroyStructure *)pclMsg->cData;

	if( pclinfo->siVillageUnique < 0 || pclinfo->siVillageUnique >= MAX_VILLAGE_NUMBER)		return;

	// �ǹ� ����

	pclVillageManager->pclVillageInfo[ pclinfo->siVillageUnique ]->clVillageVary.clStructureInfo.Del( pclinfo->siSlot );

	// ����� (����Ʈ ����) 
//	pclCityHallManager->pclConstructDlg->m_bUpdateSwitch = TRUE;

	// ��ü�Ǿ����� �����Ѵ�.
	TCHAR buffer[256];
	SI32 ref = pclVillageStructureSet->FindRefFromUnique(pclinfo->siStructureUnique);
	if(ref != -1)
	{
		TCHAR* pText  = GetTxtFromMgr(821);

		StringCchPrintf(buffer, 256, pText, pclVillageStructureSet->pclVillageStructureInfo[ref]->szName);
		pclMessage->SetMsg(buffer);
	}
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGENOTICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageNotice* pclinfo = (cltGameMsgResponse_VillageNotice *)pclMsg->cData;

	if ( pclinfo->strVillageNotice == NULL || _tcslen( pclinfo->strVillageNotice ) < 1 )
	{
		return;
	}
	else
	{
		pclVillageNotice->Set( pclinfo->strVillageNotice, true );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGELEVELDETAILINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageLevelDetailInfo* pclinfo = (cltGameMsgResponse_VillageLevelDetailInfo*)pclMsg->cData;

	pclCityHallManager->clClientLevelInfo.Set( &pclinfo->clLevelInfo );
	pclCityHallManager->UpdateLevelInfoSwitch = TRUE;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetName* pclinfo = (cltGameMsgResponse_GetName*)pclMsg->cData;
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		// �̸��� �ִ´�. 
		pclCM->CR[charid]->SetName(pclinfo->szName);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RANK(cltMsg* pclMsg, SI32 id)
{
	cltSimpleRank* pclInfo;
	pclInfo = (cltSimpleRank*)pclMsg->cData;

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];

	pclchar->pclCI->clCharRank.Set(pclInfo);

	pclchar->pclBoss->Set(pclInfo->GetRankType());

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_REALESTATE(cltMsg* pclMsg, SI32 id)
{
	cltCharRealEstate* pclinfo = (cltCharRealEstate*)pclMsg->cData;

	pclCM->CR[id]->pclCI->clRealEstate.Set(pclinfo);

	for (SI32 i = 0 ; i < MAX_REAL_ESTATE_NUMBER_PER_PERSON; i++)
	{
		if(pclinfo->clRealEstate[i].siType == REALESTATE_TYPE_HOUSE)
		{
			pclHouseManager->clClientUnit[pclinfo->clRealEstate[i].siIndex].clContract.Set(&pclinfo->clRealEstate[i].clContract);
		}
	}

	pclHouseManager->bUpdateHouseUnitListShowChiefSwitch = true;
	pclHouseManager->bUpdateHouseUnitListShowSwitch		= true;

	if( NULL == m_pDialog[NHOUSEUSERINFOBASE_DLG])
		return;

	CNHouseUserNewManagementDlg* pclHouseManagerDlg = ((CNHouseUserInfoBaseDlg*)m_pDialog[NHOUSEUSERINFOBASE_DLG])->GetNHouseUserNewManagementDlg();
	if( NULL == pclHouseManagerDlg)
		return;

	if(!pclHouseManagerDlg->IsShow())
		return;

	pclHouseManagerDlg->LoadMyHouseList();
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_STRINFO(cltMsg* pclMsg, SI32 id)
{
	// ���� �ǹ� ������ �� �ǹ��� Manager���� �����Ѵ�. 
	cltStrInfo* pclinfo = (cltStrInfo*)pclMsg->cData;

	switch(pclinfo->clCommonInfo.siStrType)
	{
	case RANKTYPE_BANK:
		pclBankManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_STOCK:
		pclStockManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_MARKET:
		pclMarketManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_HUNT:
		pclHuntManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_CITYHALL:
		pclCityHallManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_HOUSE:
		pclHouseManager->SetClientStrInfo(pclinfo);
		// ������ ������Ʈ �Ǿ����� �˸���.
		pclHouseManager->UpdateHouseVarySwitch			= TRUE;
		pclHouseManager->UpdateRentContractShowSwitch	= TRUE;
		break;

	case RANKTYPE_POSTOFFICE:
		pclPostOfficeManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_HORSEMARKET:
		pclHorseMarketManager->SetClientStrInfo(pclinfo);
		break;

	case RANKTYPE_REALESTATEMARKET:
		pclRealEstateMarketManager->SetClientStrInfo(pclinfo);
		break;

	case RANKTYPE_SUMMONMARKET:
		pclSummonMarketManager->SetClientStrInfo(pclinfo);
		break;

	case RANKTYPE_LAND:
		pclLandManager->SetClientStrInfo(pclinfo);
		break;

	case RANKTYPE_FEAST:
		pclFeastManager->SetClientStrInfo(pclinfo);
		pclFeastManager->bUpdateUser = TRUE;
		pclFeastManager->bUpdateChief2 = TRUE;
		break;

	case RANKTYPE_SUMMONHEROMARKET:
		pclSummonHeroMarketManager->SetClientStrInfo(pclinfo);
		break;

	case RANKTYPE_MINE:
		pclMineManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_GUILD:
		pclGuildManager->SetClientStrInfo(pclinfo);
		break;
	case RANKTYPE_NEWMARKET:
		pclNewMarketManager->SetClientStrInfo(pclinfo);
		break;

	default:
		MsgBox(TEXT("GAMEMSG_RESPONSE_STRINFO"), TEXT("NoStr:%d"), pclinfo->clCommonInfo.siStrType);
	}


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETTAXLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetTaxList* pclGetTaxList = (cltGameMsgResponse_GetTaxList*)pclMsg->cData;

	cltTaxPaymentListDlg clTaxDlg;

	clTaxDlg.m_taxInfo = pclGetTaxList->clTaxInfo;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETDIVIDENDLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetDividendList* pclGetDividendList = (cltGameMsgResponse_GetDividendList*)pclMsg->cData;

	if(m_pDialog[ NCITYHALL_DLG ] != NULL && ((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->IsCreate() == true 
		&& ((NCityhallInfo2Dlg*)((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->m_pUserChildDlg[ 1 ]) != NULL )
	{
		((NCityhallInfo2Dlg*)((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->m_pUserChildDlg[ 1 ])->m_dividendInfo =  pclGetDividendList->clDividendInfo;
	}
	

	//�������� ����
	//if(m_pDialog[ NCITYHALL_DLG ] != NULL && ((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->IsCreate() == true 
	//	&& ((NCityhallDividendListDlg*)((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->m_pUserChildDlg[ 5 ]) != NULL )
	//{
	//	((NCityhallDividendListDlg*)((NCityhallDlg*)m_pDialog[ NCITYHALL_DLG ])->m_pUserChildDlg[ 5 ])->m_dividendInfo =  pclGetDividendList->clDividendInfo;
	//}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HIRENPC(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HireNPC* pclHireNPC = (cltGameMsgResponse_HireNPC* )pclMsg->cData;

	if( pclHireNPC->siResult == 1 ) 
	{
		pclCityHallManager->Update();
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RESIDENTAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_GetResidentApplyerList* pclApplyer = (cltGameMsgResponse_GetResidentApplyerList*)pclMsg->cData;

	int i = 0;

	for( i = 0; i < pclApplyer->count; ++i ) {
		pclCityHallManager->clResidentApplyer[ i ].Set( &pclApplyer->clResidentApplyer[ i ] );
	} 

	if( i < MAX_RESIDENT_APPLYER ) 
		pclCityHallManager->clResidentApplyer[ i ].Init();

	pclCityHallManager->UpdateResidentApplyerSwitch = TRUE;


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RESIDENTLIST(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_GetResidentList* pclResident = (cltGameMsgResponse_GetResidentList*)pclMsg->cData;

	int i;

	for( i = 0; i < pclResident->count; ++i ) {
		pclCityHallManager->clResident[ i ].Set( &pclResident->clResident[ i ] );
	}

	if( i < MAX_RESIDENT_NUMBER )
		pclCityHallManager->clResident[ i ].Init();

	pclCityHallManager->UpdateResidentListSwitch = TRUE;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RESIDENTINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetResidentInfo *pclResidentInfo = (cltGameMsgResponse_GetResidentInfo *)pclMsg->cData;

	if( pclResidentInfo->siResult == 1 ) {

		pclCityHallManager->clClientResidentInfo = pclResidentInfo->clResident;


		pclCityHallManager->bResidentInfoValid = TRUE;

	} else {

		pclCityHallManager->bResidentInfoValid = FALSE;

	}

	pclCityHallManager->UpdateResidentInfoSwitch = TRUE;



}

void cltClient::DoMsg_GAMEMSG_RESPONSE_UPDATERESIDENTAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclMsg->siData32[ 0 ];

	if( m_pDialog[ NBERESIDENT_DLG ] && m_pDialog[ NBERESIDENT_DLG ]->IsCreate() == true )
		((NBeResidentDlg*)m_pDialog[ NBERESIDENT_DLG ])->UpdateResidentApplyerList( personid );

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ALLSTRCHIEFINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AllStrChiefInfo *pclInfo = (cltGameMsgResponse_AllStrChiefInfo *)pclMsg->cData;


	for( int i = 0; i < MAX_RANKTYPE_NUMBER; ++i ) {
		pclCityHallManager->clChiefInfo[ i ].ranktype = pclInfo->siRankType[ i ];
		memcpy( pclCityHallManager->clChiefInfo[ i ].szID, pclInfo->szChiefPersonName[ i ], MAX_PLAYER_NAME );
		pclCityHallManager->clChiefInfo[ i ].szID[ MAX_PLAYER_NAME - 1 ] = NULL;
	}

	pclCityHallManager->bChiefInfo = TRUE;
	pclCityHallManager->bRecvChiefInfo = TRUE;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_STOCKPRICE(cltMsg* pclMsg, SI32 id)
{
	// ���� ���� ������ BankManager���� �����Ѵ�. 
	cltVillageStockPrice* pclStockPrice = (cltVillageStockPrice*)pclMsg->cData;

	// �� ������ �ְ��� ����Ѵ�. 
	SI32 ref = pclStockPrice->siVillageUnique;
	if(ref  >= 0)
	{
		pclVillageManager->pclVillageInfo[ref]->clVillageVary.clVillageStockPrice.Set(pclStockPrice);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GETVILLAGEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetVillageInfo* pclVillInfo = (cltGameMsgResponse_GetVillageInfo *)pclMsg->cData;

	for( int i = 1; i < MAX_VILLAGE_NUMBER; ++i ) {

		if( pclVillageManager->pclVillageInfo[ i ] == NULL ) continue;
		pclVillageManager->pclVillageInfo[ i ]->clVillageVary.siMasterVillage = pclVillInfo->siMasterVillage[ i ];
		pclVillageManager->pclVillageInfo[ i ]->clVillageVary.siParentVillage = pclVillInfo->siParentVillage[ i ];
		pclVillageManager->pclVillageInfo[ i ]->clVillageVary.siVillageMark = pclVillInfo->siVillageMark[ i ];
		pclVillageManager->pclVillageInfo[ i ]->clVillageVary.siTotalVillageScore = pclVillInfo->siTotalVillageScore[ i ];
		pclVillageManager->pclVillageInfo[ i ]->clVillageVary.siNewYearEventScore = pclVillInfo->siNewYearEventScore[ i ];

	}

#ifdef _SAFE_MEMORY
	memcpy( &pclVillageManager->siDeclareWarVillage[0], pclVillInfo->siDeclareWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
	memcpy( &pclVillageManager->clDeclareWarDate[0], pclVillInfo->clDeclareWarDate, sizeof( NDate ) * MAX_VILLAGE_NUMBER );
	memcpy( &pclVillageManager->siNowWarVillage[0], pclVillInfo->siNowWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
#else
	memcpy( pclVillageManager->siDeclareWarVillage, pclVillInfo->siDeclareWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
	memcpy( pclVillageManager->clDeclareWarDate, pclVillInfo->clDeclareWarDate, sizeof( NDate ) * MAX_VILLAGE_NUMBER );
	memcpy( pclVillageManager->siNowWarVillage, pclVillInfo->siNowWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
#endif

	pclCityHallManager->UpdateWarTreeSwitch = TRUE;

}


void cltClient::DoMsg_GAMEMSG_RESPONSE_GETNOWVILLAGEWARINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GetNowVillageWarInfo* pclVillInfo = (cltGameMsgResponse_GetNowVillageWarInfo *)pclMsg->cData;
	
#ifdef _SAFE_MEMORY
	memcpy( &pclVillageManager->siNowWarVillage[0], pclVillInfo->siNowWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
#else
	memcpy( pclVillageManager->siNowWarVillage, pclVillInfo->siNowWarVillage, sizeof( SI32 ) * MAX_VILLAGE_NUMBER );
#endif
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETVILLAGEMARK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetVillageMark* pclinfo = (cltGameMsgResponse_SetVillageMark*)pclMsg->cData;

	pclVillageManager->pclVillageInfo[ pclinfo->siVillageUnique ]->clVillageVary.siVillageMark = pclinfo->siVillageMark;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RESIDENTSLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ResidentsList* pclResidentsList = (cltGameMsgResponse_ResidentsList *)pclMsg->cData;

	if ( pclCM->CR[1]->pclCI->clBI.siHomeVillage == pclResidentsList->siVillageUnique )
	{
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{
			((CNResidentsDlg*)m_pDialog[ NRESIDENTS_DLG ])->RecvResidentsList( pclResidentsList->clResident, pclResidentsList->uiCount );
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RESIDENTLOGIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ResidentLogin* pclResidentLogin = (cltGameMsgResponse_ResidentLogin *)pclMsg->cData;

	if ( pclCM->CR[1]->pclCI->clBI.siHomeVillage == pclResidentLogin->siVillageUnique )
	{
		m_pResidentLoginDraw->Set( pclResidentLogin->strCharName );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DECLAREWAR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_DeclareWar* pclDeclareWar = (cltGameMsgResponse_DeclareWar *)pclMsg->cData;

	if( pclDeclareWar->siVillageUnique < 0 || pclDeclareWar->siVillageUnique >= MAX_VILLAGE_NUMBER)	return;

	pclVillageManager->siDeclareWarVillage[ pclDeclareWar->siVillageUnique ] 
	= pclDeclareWar->siTargetVillage;


	pclVillageManager->clDeclareWarDate[pclDeclareWar->siVillageUnique ].Set(&pclDeclareWar->clDate);

	pclCityHallManager->clClientStrInfo.clCityhallStrInfo.bDeclareWarVillage[ pclDeclareWar->siTargetVillage ] = 1;



	//pclCityHallManager->clClientStrInfo.clCityhallStrInfo.clDeclareWarDate.Set(pclDeclareWar->clDate);

	pclCityHallManager->clClientStrInfo.clCityhallStrInfo.uiDeclareWarDateYear = pclDeclareWar->clDate.m_uiYear;
	pclCityHallManager->clClientStrInfo.clCityhallStrInfo.uiDeclareWarDateMonth = pclDeclareWar->clDate.m_uiMonth;
	pclCityHallManager->clClientStrInfo.clCityhallStrInfo.uiDeclareWarDateDay = pclDeclareWar->clDate.m_uiDay;

		
	pclCityHallManager->UpdateWarTreeSwitch = TRUE;		

	// ȭ�鿡 ǥ��. 
	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(822);


	Nsprintf(buffer,pText,TEXT("who"), pclVillageManager->GetName(pclDeclareWar->siVillageUnique)   ,
		TEXT("whom"),pclVillageManager->GetName(pclDeclareWar->siTargetVillage)    ,NULL);
	/*sprintf(buffer, pText, 
	pclVillageManager->GetName(pclDeclareWar->siVillageUnique),
	pclVillageManager->GetName(pclDeclareWar->siTargetVillage));
	*/
	pclMessage->SetMsg(buffer, 0, RGB(200, 200, 0),RGB(0,0,0));

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CANCELDECLAREWAR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_CancelDeclareWar* pclmsg = (cltGameMsgResponse_CancelDeclareWar *)pclMsg->cData;

	if( pclmsg->siVillageUnique < 0 || pclmsg->siVillageUnique >= MAX_VILLAGE_NUMBER)	return;

	pclVillageManager->siDeclareWarVillage[ pclmsg->siVillageUnique ] = 0;
	pclVillageManager->siNowWarVillage[ pclmsg->siVillageUnique ] = 0;

	pclCityHallManager->clClientStrInfo.clCityhallStrInfo.bDeclareWarVillage[ pclmsg->siTargetVillage ] = 0;	

	pclCityHallManager->UpdateWarTreeSwitch = TRUE;

	// ȭ�鿡 ǥ��. 
	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(823);

	/*
	sprintf(buffer, pText, 
	pclVillageManager->GetName(pclmsg->siVillageUnique),
	pclVillageManager->GetName(pclmsg->siTargetVillage));
	*/

	Nsprintf(buffer,pText,
		TEXT("who"), pclVillageManager->GetName(pclmsg->siVillageUnique)   ,
		TEXT("whom"), pclVillageManager->GetName(pclmsg->siTargetVillage)   ,NULL);
	pclMessage->SetMsg(buffer, 0, RGB(200, 200, 0),RGB(0,0,0));

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETSYMBOLSTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetSymbolStatus* pclmsg = (cltGameMsgResponse_SetSymbolStatus *)pclMsg->cData;

	switch( pclmsg->siStatKind )
	{
	case SYMBOLSTAT_KIND:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siSymbolKind = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_LIFE:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siSymbolLife = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_MANA:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siSymbolMana = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_CAPA:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siSymbolCapa = pclmsg->siStatValue;
		break;
	}

	pclCityHallManager->Update();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SETCASTLESTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SetCastleStatus* pclmsg = (cltGameMsgResponse_SetCastleStatus *)pclMsg->cData;

	switch( pclmsg->siStatKind )
	{
	case SYMBOLSTAT_KIND:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siCastleKind = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_LIFE:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siCastleLife = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_MANA:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siCastleMana = pclmsg->siStatValue;
		break;

	case SYMBOLSTAT_CAPA:
		pclCityHallManager->clClientStrInfo.clCityhallStrInfo.siCastleCapa = pclmsg->siStatValue;
		break;
	}


	pclCityHallManager->Update();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEWARRESULT(cltMsg* pclMsg, SI32 id)
{
	cltClient * pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_VillageWarResult* pclmsg = (cltGameMsgResponse_VillageWarResult*)pclMsg->cData;

	//pclVillageManager->SetWarResult( pclmsg->siWinVillage, pclmsg->siLoseVillage );
	//m_pVillageWarInfoDlg->Set(pclmsg->siWinVillage,pclmsg->siLoseVillage);


	//if( g_SoundOnOffDlg.m_bFullScreenMode)
	//{
	if ( m_pDialog[NVILLAGEWARINFO_DLG  ]==NULL )
	{
		CreateInterface(NVILLAGEWARINFO_DLG);
	}				
	((CNVillageWarInfoDlg*)m_pDialog[ NVILLAGEWARINFO_DLG ])->Set(pclmsg->siWinVillage,pclmsg->siLoseVillage);

	SI32 myHomeid = pclClient->pclCM->CR[1]->pclCI->clBI.siHomeVillage;

	if( pclmsg->siWinVillage == myHomeid )
	{
		pclclient->m_pVillageWarNotice->Set(VILLAGEWAR_NOTICE_WIN);
	}
	else if(  pclmsg->siLoseVillage == myHomeid )
	{
		pclclient->m_pVillageWarNotice->Set(VILLAGEWAR_NOTICE_LOSE);
	}
		

	//	}
	//	else 
	//	m_pVillageWarInfoDlg->Set(pclmsg->siWinVillage,pclmsg->siLoseVillage);


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEWARRESULT_FOR_VILLAGEMEMBER(cltMsg* pclMsg, SI32 id)
{
	cltClient * pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_VillageWarResultToVillageMember* pclmsg = (cltGameMsgResponse_VillageWarResultToVillageMember*)pclMsg->cData;

	TCHAR* pTitle = GetTxtFromMgr(3710);
	TCHAR* pText = GetTxtFromMgr(6479);
	if ( !pTitle || !pText ) return ;

	TCHAR szText[256] = {'\0',};

	StringCchPrintf(szText,256,pText, pclClient->pclVillageManager->GetName(pclmsg->siWinVillage)
					, pclClient->pclVillageManager->GetName(pclmsg->siLoseVillage) , pclmsg->siWinnerGetVillageWarScore,pclmsg->siWinnerGetVillageMoney);
		       
	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, szText);

}


void cltClient::DoMsg_GAMEMSG_RESPONSE_ENDVILLAGEWAR(cltMsg* pclMsg, SI32 id)
{
	pclVillageManager->ResetDeclareWar();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_INVESTLIST(cltMsg* pclMsg, SI32 id)
{

	// ���� ������ ������ CityHallManager���� �����Ѵ�. 
	cltVillageInvestInfo* pclMayorInfo = (cltVillageInvestInfo*)pclMsg->cData;

	SI32 ref = pclMayorInfo->siVillageUnique;

	if(ref >= 0)
	{
		pclVillageManager->pclVillageInfo[ref]->clVillageVary.clInvestInfo.Set(pclMayorInfo);

		// ������ ����Ʈ�� ������Ʈ �� ���� �䱸�Ѵ�. 
		pclStockManager->UpdateInvestSwitch = TRUE;
		pclCityHallManager->UpdateInvestSwitch = TRUE;

	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHIEFINFO(cltMsg* pclMsg, SI32 id)
{
	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_ChiefInfo* pChiefInfo= (cltGameMsgResponse_ChiefInfo*)pclMsg->cData;

	// ���� ������ VillageInfo�ȿ� �ִ´�. 
	SI32 villageunique  = pChiefInfo->Rank.GetVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return;

	SI32 ranktype = pChiefInfo->Rank.clRank.siType;
	if(ranktype < 0 || ranktype >= MAX_RANKTYPE_NUMBER)				return;
	pclVillageManager->pclVillageInfo[villageunique]->clVillageVary.clRankPerson[ranktype].Set(&pChiefInfo->Rank.clPerson);

	// AccountID�� �����Ѵ�.
	StringCchCopy(pclVillageManager->pclVillageInfo[villageunique]->RankAccountID[ranktype], MAX_PLAYER_NAME, pChiefInfo->AccountID);

	// ����� ������ ������Ʈ �� ���� �䱸�Ѵ�. 
	switch(ranktype)
	{
	case RANKTYPE_CITYHALL:
		pclCityHallManager->UpdateChiefSwitch = true;
		pclCityHallManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_HOUSE:
		pclHouseManager->UpdateChiefSwitch = true;
		pclHouseManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_BANK:
		pclBankManager->UpdateChiefSwitch = true;
		pclBankManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_STOCK:
		pclStockManager->UpdateChiefSwitch = true;
		pclStockManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_MARKET:
		pclMarketManager->UpdateChiefSwitch = true;
		pclMarketManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_HUNT:
		pclHuntManager->UpdateChiefSwitch = true;
		pclHuntManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_POSTOFFICE:
		pclPostOfficeManager->UpdateChiefSwitch = true;
		pclPostOfficeManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_HORSEMARKET:
		pclHorseMarketManager->UpdateChiefSwitch = true;
		pclHorseMarketManager->bDrawPortraitSwitch = true;
		break;

	case RANKTYPE_REALESTATEMARKET:
		pclRealEstateMarketManager->UpdateChiefSwitch = true;
		pclRealEstateMarketManager->bDrawPortraitSwitch = true;
		break;

	case RANKTYPE_SUMMONMARKET:
		pclSummonMarketManager->UpdateChiefSwitch = true;
		pclSummonMarketManager->bDrawPortraitSwitch = true;
		break;

	case RANKTYPE_LAND:
		pclLandManager->UpdateChiefSwitch = true;
		pclLandManager->bDrawPortraitSwitch = true;
		break;

	case RANKTYPE_FEAST:
		pclFeastManager->UpdateChiefSwitch = true;
		pclFeastManager->bDrawPortraitSwitch = true;				
		break;

	case RANKTYPE_SUMMONHEROMARKET:
		pclSummonHeroMarketManager->UpdateChiefSwitch = true;
		pclSummonHeroMarketManager->bDrawPortraitSwitch = true;
		break;

	case RANKTYPE_MINE:
		pclMineManager->UpdateChiefSwitch = true;
		pclMineManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_GUILD:
		pclGuildManager->UpdateChiefSwitch = true;
		pclGuildManager->bDrawPortraitSwitch = true;
		break;
	case RANKTYPE_NEWMARKET:
		pclNewMarketManager->UpdateChiefSwitch = true;
		pclNewMarketManager->bDrawPortraitSwitch = true;
		break;

	default:
		MsgBox(TEXT("fds8fhjv8"), TEXT("vc97fj:%d"), ranktype);
		break;
	}


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_REPAIRSTRUCTURE(cltMsg* pclMsg, SI32 id)
{
	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_RepairStructure* pRecvInfo= (cltGameMsgResponse_RepairStructure*)pclMsg->cData;

	switch( pRecvInfo->siRankType )
	{
	case RANKTYPE_CITYHALL:
		{
			pclCityHallManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclCityHallManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_HOUSE:
		{
			pclHouseManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclHouseManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_BANK:
		{
			pclBankManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclBankManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_STOCK:
		{
			pclStockManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclStockManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_MARKET:
		{
			pclMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_HUNT:
		{
			pclHuntManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclHuntManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_POSTOFFICE:
		{
			pclPostOfficeManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclPostOfficeManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_HORSEMARKET:
		{
			pclHorseMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclHorseMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_REALESTATEMARKET:
		{
			pclRealEstateMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclRealEstateMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_SUMMONMARKET:
		{
			pclSummonMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclSummonMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_LAND:
		{
			pclLandManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclLandManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_FEAST:
		{
			pclFeastManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclFeastManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_SUMMONHEROMARKET:
		{
			pclSummonHeroMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclSummonHeroMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_MINE:
		{
			pclMineManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclMineManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_GUILD:
		{
			pclGuildManager->clClientStrInfo.clCommonInfo.siRepairStrDura = pRecvInfo->siStrRepairAmount;
			pclGuildManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;
	case RANKTYPE_NEWMARKET:
		{
			pclNewMarketManager->clClientStrInfo.clCommonInfo.siRepairStrDura	  = pRecvInfo->siStrRepairAmount;
			pclNewMarketManager->clClientStrInfo.clCommonInfo.clBaseMoney.itMoney = pRecvInfo->siLeftBaseMoney;
		}
		break;

	default:
		MsgBox("fdshs632", "vcga1fj:%d", pRecvInfo->siRankType);
		break;
	}

	/*
	switch( pRecvInfo->siRankType )
	{
	case RANKTYPE_CITYHALL:
		pclCityHallManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_HOUSE:
		pclHouseManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_BANK:
		pclBankManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_STOCK:
		pclStockManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_MARKET:
		pclMarketManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_HUNT:
		pclHuntManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_POSTOFFICE:
		pclPostOfficeManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_HORSEMARKET:
		pclHorseMarketManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_REALESTATEMARKET:
		pclRealEstateMarketManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_SUMMONMARKET:
		pclSummonMarketManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_LAND:
		pclLandManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_FEAST:
		pclFeastManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_SUMMONHEROMARKET:
		pclSummonHeroMarketManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	case RANKTYPE_MINE:
		pclMineManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;

	case RANKTYPE_GUILD:
		pclGuildStructManager->clClientStrInfo.clCommonInfo.siUseItemNum = pRecvInfo->siUseItemNum;
		break;
	}
	*/

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEBOARD(cltMsg* pclMsg, SI32 id)
{
	//cltGameMsgResponse_VillageBoard* pRecvInfo= (cltGameMsgResponse_VillageBoard*)pclMsg->cData;

	//if ( m_pSearchDetailDlg )
	//	m_pSearchDetailDlg->Show(BULLETINBOARD_VILLAGERESIDENT, TEXT(""), pRecvInfo->siVillageUnique );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENT_INSERTMATERIAL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Event_InsertMaterial* pRecvInfo= (cltGameMsgResponse_Event_InsertMaterial*)pclMsg->cData;
	
//	if(m_pDialog[NCHRISTMASEVENT_DLG] == NULL)			return;

	//�� ���ٴ� �޼����� ������.
	if(pRecvInfo->m_siResult == 1){//���� �߳־���.
		TCHAR* pTitle = GetTxtFromMgr(7651);
		TCHAR* pText  = GetTxtFromMgr(7683);//�����߻�
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );//�����߻�κ�
	}
	//if (pRecvInfo->m_siResult == 0) {
	//	TCHAR* pTitle = GetTxtFromMgr(7651);
	//	TCHAR* pText  = GetTxtFromMgr(7656);//�����ۼ����� Ȯ�����ֽʽÿ�
	//	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );//���� �ż����� ������� ���� �޼��� �����ش�.
	//}

	if (pRecvInfo->m_siResult < 0) {//���� �޼���
		TCHAR* pTitle = GetTxtFromMgr(7651);
		TCHAR* pText  = GetTxtFromMgr(7656);//�����ۼ����� Ȯ�����ֽʽÿ�
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );//���� �ż����� ������� ���� �޼��� �����ش�.
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENT_MATERIALLIST(cltMsg* pclMsg, SI32 id)
{
	//�����κ��� ����Ʈ �亯�� �ް� �ϴ� �׼ǵ�.
	//����Ʈ�� ���ϴ� ���̹Ƿ� ����Ʈ�� ���� ��� �ִ� ������ �����ش�.
	//ũ�������� �̺�Ʈ
	//2007.11.28 �ռ���.
	cltGameMsgResponse_Event_MaterialList* pRecvInfo= (cltGameMsgResponse_Event_MaterialList*)pclMsg->cData;
	if(m_pDialog[NCHRISTMASEVENT_DLG] == NULL)			return;
	
#ifdef _SAFE_MEMORY
	((NChristmasEventDlg*)m_pDialog[NCHRISTMASEVENT_DLG])->changeEditbox(&pRecvInfo->m_siItemUnique[0], &pRecvInfo->m_siItemNum[0], pRecvInfo->m_siConstructType);
#else
	((NChristmasEventDlg*)m_pDialog[NCHRISTMASEVENT_DLG])->changeEditbox(pRecvInfo->m_siItemUnique, pRecvInfo->m_siItemNum,pRecvInfo->m_siConstructType);
#endif
    
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENT_MATERIALCOMPLETE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Event_MaterialComplete* pRecvInfo= (cltGameMsgResponse_Event_MaterialComplete*)pclMsg->cData;
	//�ΰ��� ��찡 �ִ�. �Ѱ����� ������ �����ϴ� �Ͱ�
	//�Ѱ����� �������� �ִ°�. ������ �ٲٴ°� �������� �Ѵٸ� Ŭ��� ���� ����.
	//�̰����� �Ѵٸ� ��..���� �ؾ� �ϳ�.>?
	//������ �ִ°� ���� �������� �𸣰ڳ�
	//if (pRecvInfo->m_siConstructType == EVENT_STRUCTURE_TREE) {//����Ʈ����
	//	if(pRecvInfo->m_siResult == 1){//Ʈ������� ����
	//		TCHAR* pTitle = GetTxtFromMgr(825);
	//		TCHAR* pText  = GetTxtFromMgr(826);//�ؽ�Ʈ�Ž����� �߰� �ϸ� �ϴ��� �޼����� ����.
	//		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
	//	}

	//	if(pRecvInfo->m_siResult == 0){//Ʈ������� ����
	//		TCHAR* pTitle = GetTxtFromMgr(825);
	//		TCHAR* pText  = GetTxtFromMgr(826);//�ؽ�Ʈ�Ž����� �߰� �ϸ� �ϴ��� �޼����� ����.
	//		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );

	//	}
	//	if (pRecvInfo->m_siResult == -1) {//Ʈ������� ����
	//		//������������ ���� �޼���
	//		TCHAR* pTitle = GetTxtFromMgr(825);
	//		TCHAR* pText  = GetTxtFromMgr(826);//�ؽ�Ʈ�Ž����� �߰� �ϸ� �ϴ��� �޼����� ����.
	//		m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
	//	}
	//}
	//ũ��������Ʈ���̸�
	if (pRecvInfo->m_siConstructType == EVENT_STRUCTURE_CHRISTMASTREE) {//ũ��������Ʈ���̸�
		if(pRecvInfo->m_siResult == 1){//�����ޱ�
			TCHAR* pTitle = GetTxtFromMgr(7663);
			TCHAR* pText  = GetTxtFromMgr(7684);//�����մϴ�~ ���� �޾һ�~
			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );//���׹�� �˸�
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_EVENT_COMPLETEBUILD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Event_CompleteBuild* pRecvInfo = (cltGameMsgResponse_Event_CompleteBuild*)pclMsg->cData;

	TCHAR  buffer[512]	= TEXT("");
	TCHAR* pVillageName = pclClient->pclVillageManager->GetName(pRecvInfo->m_siVillageUnique);
	if(NULL == pVillageName)	return;

	switch(pRecvInfo->m_siConstructType)
	{	
		case EVENT_STRUCTURE_CHRISTMASTREEBASE:
		case EVENT_STRUCTURE_TREE:
			{	
				StringCchPrintf(buffer, sizeof(buffer), GetTxtFromMgr(7659), pVillageName);
			}
			break;
		default:	//[����] ��� �ٸ� �Ǽ����� �˸�. => 2008-6-13
			{
				// ��Ĺ��� npc�� ��ϵǹǷ� ��ɷ� �̸��� ����.
				TCHAR* npcName = NULL;
				npcName	= (TCHAR*)pclClient->pclKindInfoSet->GetName(pRecvInfo->m_siNPCKind);
				if(NULL == npcName)	return;
				
				StringCchPrintf(buffer, sizeof(buffer), GetTxtFromMgr(8463), pVillageName, npcName);
			}
			break;
	}
	
	if( pRecvInfo->m_siNPCKind == pclClient->GetUniqueFromHash("KIND_RACCOONTREE") )
	{
		NTCHARString512 szString = GetTxtFromMgr(40432);
		szString.Replace("#village#", pVillageName );
		szString.Replace("#village#", pVillageName );

		StringCchCopy( buffer, sizeof(buffer), szString );
	}

	// ������ ������ ����..
	if(0 >= _tcslen(buffer))
	{
		return;
	}

	if(m_pDialog[NRAREITEM_DLG ] == NULL)
		CreateInterface( NRAREITEM_DLG );

	if(m_pDialog[NRAREITEM_DLG ] != NULL)
		((CNRareItemDlg*)m_pDialog[NRAREITEM_DLG ])->SetVillageEvent(	pRecvInfo->m_siVillageUnique, 
																		GetTxtFromMgr(7653), 
																		buffer, 
																		pRecvInfo->m_siConstructType,
																		pRecvInfo->m_siNPCKind );
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVERRTN(cltMsg* pclMsg, SI32 id)
{
	// ��û�� ���� ������� Ȯ���Ѵ�.
	cltServerResponseValue* pclreturn = (cltServerResponseValue*)pclMsg->cData;

	// ������� �м��Ͽ� ������ ���� �뺸�Ѵ�. 
	OperateByServerResponseValue(pclreturn);

}
//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHARSERVERRTN(cltMsg* pclMsg, SI32 id)
{
	// ��û�� ���� ������� Ȯ���Ѵ�.
	cltServerResponseCharValue2* pclreturn = (cltServerResponseCharValue2*)pclMsg->cData;

	// ������� �м��Ͽ� ������ ���� �뺸�Ѵ�. 
	OperateByServerResponseCharValue(pclreturn);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DATE(cltMsg* pclMsg, SI32 id)
{
	cltDate* pcldate = (cltDate*)pclMsg->cData;

	// Ŭ���̾�Ʈ �ð��� �����Ѵ�. 
	clClientDate.Set(pcldate);

	// ȭ�鿡 �ð��� ǥ���Ѵ�. 
	TCHAR buffer[256];
	if(clClientDate.GetDateText(buffer) == TRUE)
	{
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{	
#ifndef _NEW_INTERFACE_
			if ( m_pDialog[ TOOLBAR_DLG ] )
			{
				((CToolBarDlg *)m_pDialog[ TOOLBAR_DLG ])->SetDate( buffer );
			}
#else
			// pannel �� �׸�
			
			pclPannel->SetszDate(buffer);

#endif

		}
		else
		{
			g_ToolBarBaseInfoDlg.SetDate( buffer );
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_LOWPRICESTOCKORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LowPriceStockOrder* pclinfo	= (cltGameMsgResponse_LowPriceStockOrder*)pclMsg->cData;

	int i;

	for(i = 0;i < LOWPRICE_STOCK_ORDER_NUM;i++)
	{
		if(pclinfo->clUnit[i].siItemUnique)
		{
			SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clUnit[i].siItemUnique);
			if(ref > 0)
			{
				TCHAR buffer[256];
				TCHAR* pText = GetTxtFromMgr(824);



				StringCchPrintf(buffer, 256, pText, 
					pclItemManager->pclItemInfo[ref]->GetName(), 
					pclinfo->clUnit[i].siPrice,
					pclinfo->clUnit[i].siAmount);

				//g_PromptMgr.Set(buffer, 3);

				// ���� ������ ���ݰ����ڿ��� �����Ѵ�. 
				pclItemManager->pclItemPrice->SetMarketOrderPrice(pclItemManager, pclinfo->clUnit[i].siItemUnique, pclinfo->clUnit[i].siPrice);


			}

		}

	}


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOUSEAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	// ���� ������ Ȯ���Ѵ�. 
	cltHouseApplyerPacket* pclpacket = (cltHouseApplyerPacket*)pclMsg->cData;

	// ���� ������ ���� �����ڿ��� �����Ѵ�. 
	pclHouseManager->clClientApplyer[pclpacket->siIndex].Set(&pclpacket->clHouseApplyer);

	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclHouseManager->UpdateHouseApplyerListShowSwitch = TRUE;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_STGITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltHouseUnitStgItemInfo* pclinfo = (cltHouseUnitStgItemInfo*)pclMsg->cData;

	if(pclHouseManager->siVillageUnique == pclinfo->siVillageUnique)
	{
		pclHouseManager->clClientUnit[pclinfo->siHouseUnitSlot].clStorageInfo.clItem[pclinfo->siIndex].Set(&pclinfo->clItem);

		if(pclinfo->siOption & STGITEMINFO_OPTION_SHOW)
		{
			((CNotifyGetItemDlg*)m_pDialog[ NOTIFYGETITEM_DLG ])->Show( &pclinfo->clItem );
			// g_NotifyGetItemFromMonsterDlg.Show(&pclinfo->clItem);
		}

	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_STGINFO(cltMsg* pclMsg, SI32 id)
{
	GameMsgResponse_HouseUnitStgInfo* pclinfo = (GameMsgResponse_HouseUnitStgInfo*)pclMsg->cData;

	if(pclHouseManager->siVillageUnique == pclinfo->siVillageUnique)
	{
		pclHouseManager->clClientUnit[pclinfo->siHouseUnitSlot].clStorageInfo.Set(&pclinfo->clStgInfo);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOUSEUNITSTABLECREATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HouseUnitStableCreate *pclinfo = (cltGameMsgResponse_HouseUnitStableCreate*)pclMsg->cData;
	
	GMONEY siCurrentMoney = pclCM->CR[1]->pclCI->clIP.GetMoney();

	pclCM->CR[1]->pclCI->clIP.SetMoney( siCurrentMoney - pclinfo->siCreatedStableFee );
	TCHAR* pTitle = GetTxtFromMgr(825);
	TCHAR* pText  = GetTxtFromMgr(826);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );

	if(pclHouseManager->siVillageUnique == pclinfo->siVillageUnique)
	{				
		pclHouseManager->clClientUnit[pclinfo->siHouseUnitSlot].clStorageInfo.bCreatedHouseUnitStable[ pclinfo->siCreatedStableIndex ] = true;
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEINFOSET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HouseUnitHorseInfoSet *pclinfo = (cltGameMsgResponse_HouseUnitHorseInfoSet*)pclMsg->cData;
	if(pclHouseManager->siVillageUnique == pclinfo->siVillageUnique)
	{
		pclHouseManager->clClientUnit[ pclinfo->siHouseUnitSlot ].clStorageInfo.clHorse[ pclinfo->siStgHorseIndex ].Set( &pclinfo->clStgHorse );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HOUSEUNITHORSEEATFOOD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HouseUnitHorseEatFood *pclinfo = (cltGameMsgResponse_HouseUnitHorseEatFood*)pclMsg->cData;
	if(pclHouseManager->siVillageUnique == pclinfo->siVillageUnique)
	{
		pclHouseManager->clClientUnit[ pclinfo->siHouseUnitSlot ].clStorageInfo.clItem[ pclinfo->siStgItemIndex ].Set( &pclinfo->clStgItem );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WEATHER(cltMsg* pclMsg, SI32 id)
{
	stWeatherData* pclinfo = (stWeatherData*)pclMsg->cData;

	// �������� ������ ������. 
	CurrentWeather.Set(pclinfo);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_GAMEMASTERLEVEL(cltMsg* pclMsg, SI32 id)
{
	SI32 data = pclMsg->siData32[0];

	// �ƹ��� ������ ����. 
	if(data == 0)
	{
		TCHAR* pText  = GetTxtFromMgr(827);

		pclMessage->SetMsg(pText);
	}
	else
	{
		MsgBox(TEXT("vcvdfd"), TEXT("Vcfdd:%d"), data);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RIDEHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RideOrUnrideHorse* pclinfo = (cltGameMsgResponse_RideOrUnrideHorse*)pclMsg->cData;
	pclCM->CR[1]->RideHorse();

	HorseStatusHide();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_UNRIDEHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_RideOrUnrideHorse* pclinfo = (cltGameMsgResponse_RideOrUnrideHorse*)pclMsg->cData;

	pclCM->CR[1]->UnrideHorse();

	HorseStatusHide();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DELHOUSEAPPLYER(cltMsg* pclMsg, SI32 id)
{
	// ��û�� ����� ��� �����Ѵ�. 
	SI32 siSlot = (SI32)*pclMsg->cData;

	for(int i = 0; i < MAX_APPLY_PER_HOUSE;i++)
	{
		if(siSlot >=0 && siSlot == i)
		{
			pclHouseManager->clClientApplyer[i].Init();
		}
	}

	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclHouseManager->UpdateHouseApplyerListShowSwitch = TRUE;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MARKETSELLINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MarketSellInfo* pclinfo = (cltGameMsgResponse_MarketSellInfo*)pclMsg->cData;

	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(828);
	TCHAR num[64]=TEXT("");
	TCHAR money[64]=TEXT("");
	StringCchPrintf(num, 64, TEXT("%d"),pclinfo->siItemNum);
	StringCchPrintf(money, 64, TEXT("%d"),pclinfo->siPrice*pclinfo->siItemNum);

	Nsprintf(buffer,pText,TEXT("item"),pclItemManager->GetName(pclinfo->siUnique)    ,
		TEXT("num"), num   ,
		TEXT("money"), money   ,NULL);

	/*
	sprintf(buffer, pText,
	pclItemManager->GetName(pclinfo->siUnique),
	pclinfo->siItemNum,
	pclinfo->siPrice*pclinfo->siItemNum);
	*/

	pclMessage->SetMsg(buffer);

	pText = GetTxtFromMgr(829);


	pclMessage->SetMsg(pText);
	pclMusic->PushEffect( GetUniqueFromHash(TEXT("SOUND_EFFECT_MARKETSELLINFO")), 0, 0 );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_DEALTHPENALTYINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_DeathPenalty* pclInfo = (cltGameMsgResponse_DeathPenalty*)pclMsg->cData;	

	if(m_pDialog[ NDEATH_DLG ]==NULL)
	{
		CreateInterface( NDEATH_DLG);
	}
	((CNDeathDlg*)m_pDialog[ NDEATH_DLG ])->set(pclInfo->siMoney,pclInfo->siExp, pclInfo->siKilledMode, pclInfo->szKillMeCharName);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_REVIVE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Revive* pclInfo = (cltGameMsgResponse_Revive*)pclMsg->cData;	

	bReviveRequestSwitch = true;

	//���� ������ ��Ȱ�� ������ ������ �ִٸ� ���ڸ����� ��Ȱ�ϰڳĴ� �޽����� ������
	bool haveResurrection	=	false	;
	bool bInsurance_policy	=	false	;	//	 ���������� ������ �ִ��� ���� 
	// ���ΰ��� PVP�� �׾��ٸ� ���ڸ����� ��Ȱ�ϰڳĴ� �޼����� �����ش�.
	bool PvpDie				=		false	;
	if ( pclInfo->siDieMode == PVP_DIE) {
		PvpDie = true ;
	}

	cltCharClient * pclchar = (cltCharClient *)pclCM->CR[1];

	//[����] ��Ʋ�ξ� ������̶��
	if( pclchar->GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM || pclchar->GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM )
	{
		return;
	}

	for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)	// �������� ã�´� 
	{
		cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];
		if( pclitem->siUnique <= 0 ) continue;
		// ���������� �ִ��� ���� �ϴ� Ȯ��.
		if(ITEMUNIQUE(2731) == pclitem->siUnique && pclitem->GetItemNum() > 0 )
		{
			bInsurance_policy	=	true	;
			// ������ ������ ��� ��û�� ������. 

			//[����] // �׾��� ���� ���Ȳ�̴� �������� ���δ�
			cltGameMsgRequest_UseJustUseItem clitemjustuse( pclitem->siUnique, pclchar->pclCI->clCharItem.GetItemPos( pclitem->siUnique),	1 );
			cltMsg clMsg(GAMEMSG_REQUEST_JUSTITEMUSE, sizeof(cltGameMsgRequest_UseJustUseItem), (BYTE*)&clitemjustuse);
			SendMsgToServer((sPacketHeader*)&clMsg);

			break;
		}
	}
	// ���������� �������� �˻� �Ѵ�
	if ( bInsurance_policy == false) 
	{
		// ���� ������ ������  ��Ȱ�� ���� �ִ��� �˻� �Ѵ� .
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];

			if( pclitem->siUnique <= 0 ) continue;

			SI32 ref = pclItemManager->FindItemRefFromUnique( pclitem->siUnique );	if( ref <= 0 ) continue;
			if(	pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESURRECTION	&& pclitem->GetItemNum() > 0 )
			{
				haveResurrection = true;
				break;
			}
		}
	}	
	if ( true == bInsurance_policy )	// ���������� �ִٸ� 
	{
		CreateInterface( NCOMMONMSG_DLG );
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_INSURANCE_POLICY);
	}

	else if( true == haveResurrection)	// ��Ȱ�� �� Ȯ��
	{
		CreateInterface( NCOMMONMSG_DLG );
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_RESURRECTION);			
	}
	else if ( PvpDie )	// pvp�� �������� Ȯ�� 
	{
		CreateInterface( NCOMMONMSG_DLG );
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_RESURRECTION_PVP);
	}
	else	//�׿�
	{
		CreateInterface( NCOMMONMSG_DLG );
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_REVIVE);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ITEMDROP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ItemDrop* pclinfo = (cltGameMsgResponse_ItemDrop*)pclMsg->cData;

	// �������� ���ž� �� ������ ���� ������ �ٸ��� ����. 
	if(pclinfo->clPos.siMapIndex != pclMapManager->CurrentMapIndex)	return;
	SI32 mapindex	= pclinfo->clPos.siMapIndex;
	SI32 x			= pclinfo->clPos.siX;
	SI32 y			= pclinfo->clPos.siY;


	if(pclMapManager->pclMapArray[mapindex] == NULL) return;

	// ������ �������� �÷����´�. 
	pclMapManager->pclMapArray[mapindex]->SetItemMap(x, y, pclinfo->uiItemUnique, pclinfo->uiItemListIndex);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_WHISPERCHAT_REJECT(cltMsg* pclMsg, SI32 id)
{
	TCHAR* pTitle = GetTxtFromMgr(830);
	TCHAR* pText  = GetTxtFromMgr(831);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_REJECT(cltMsg* pclMsg, SI32 id)
{
	TCHAR* pTitle = GetTxtFromMgr(832);
	TCHAR* pText  = GetTxtFromMgr(833);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_ANOTHERAUTH(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_AnotherAuth* pclinfo = (cltGameMsgResponse_AnotherAuth*)pclMsg->cData;

	PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_NOTICEADMIN")), 0, 0);
	TCHAR buffer[1024] = TEXT("") ;

	TCHAR IP[64] = TEXT("") ;

	if (!pclinfo->bNewUser)
	{
		StringCchCopy(IP, 64, pclinfo->szIP);

		TCHAR* pText  = NULL;

		if ( !_tcscmp(IP,TEXT("222.107.176.36")) )
		{
			pText = GetTxtFromMgr(834);


			StringCchCopy(IP, 64, pText);
		}

		pText = GetTxtFromMgr(835);


		StringCchPrintf(buffer, 1024, pText,
			IP,pclinfo->stTime.wYear,pclinfo->stTime.wMonth,
			pclinfo->stTime.wDay,pclinfo->stTime.wHour,pclinfo->stTime.wMinute,
			pclinfo->stTime.wSecond);

		pText = GetTxtFromMgr(836);


		g_ErrorMsg.BigSet(pText, buffer);
	}
	else
	{
		//cyj ���������� �����̸� ����Ʈ ���� �������� �ǵ��ư�
		clUserState.SetState(USERSTATE_FRONT_CONNECTING);

		if (m_pDialog[ NCOMMONMSG_DLG ] == NULL)
		{
			CreateInterface(NCOMMONMSG_DLG);
			//m_pDialog[ NCOMMONMSG_DLG ] = new CNCommonMsgDlg();
			//((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Create();
		}
		((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_RELOGIN);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTGAMEPOTAUTH(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_NotGamePotAuth* pclinfo = (cltGameMsgResponse_NotGamePotAuth*)pclMsg->cData;

	TCHAR *pTitle = GetTxtFromMgr(422);
	TCHAR *pText = GetTxtFromMgr(6264);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);

	//����Ʈ ���� �������� �ǵ��ư�
	clUserState.SetState(USERSTATE_FRONT_CONNECTING);

	cltClient* pclclient = (cltClient*)pclClient;

	pclclient->pGameSession->CloseSocket();

	pclclient->pFrontSession->CloseSocket() ;

	pclclient->bReceiveMyCharAllInfoSwitch	= false;
	pclclient->bBackUpSwitch				= false;

	pclclient->siAuthKey		= 0;
	pclclient->bFrontServerActionSwitch	= true;
	pclclient->bGameServerActionSwitch		= false;

	pclclient->bFrontServerSecretKeySwitch	= false;
	pclclient->bGameServerSecretKeySwitch	= false;

	Sleep(1000);

	pclclient->SetGameStatus(GS_INITCONNECTFRONTSERVER);

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CANNOTLOGIN_AGE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_CannotLogin_Age* pclinfo = (cltGameMsgResponse_CannotLogin_Age*)pclMsg->cData;

	if (m_pDialog[ NCOMMONMSG_DLG ] == NULL)
	{
		CreateInterface(NCOMMONMSG_DLG);
	}
	((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_CANNOTLOGIN_AGE);

	cltClient* pclclient = (cltClient*)pclClient;

	pclclient->pGameSession->CloseSocket();
	pclclient->pFrontSession->CloseSocket() ;

	pclclient->bReceiveMyCharAllInfoSwitch	= false;
	pclclient->bBackUpSwitch				= false;

	pclclient->siAuthKey		= 0;
	pclclient->bFrontServerActionSwitch	= true;
	pclclient->bGameServerActionSwitch		= false;

	pclclient->bFrontServerSecretKeySwitch	= false;
	pclclient->bGameServerSecretKeySwitch	= false;

	//����Ʈ ���� �������� �ǵ��ư�
	clUserState.SetState(USERSTATE_FRONT_CONNECTING);

	pclclient->SetGameStatus(GS_INITCONNECTFRONTSERVER);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CANNOTLOGIN_ERROR(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_CannotLogin_Error* pclinfo = (cltGameMsgResponse_CannotLogin_Error*)pclMsg->cData;

	if (m_pDialog[ NCOMMONMSG_DLG ] == NULL)
	{
		CreateInterface(NCOMMONMSG_DLG);
	}
	((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_CANNOTLOGIN_ERROR);

	cltClient* pclclient = (cltClient*)pclClient;

	pclclient->pGameSession->CloseSocket();
	pclclient->pFrontSession->CloseSocket() ;

	pclclient->bReceiveMyCharAllInfoSwitch	= false;
	pclclient->bBackUpSwitch				= false;

	pclclient->siAuthKey		= 0;
	pclclient->bFrontServerActionSwitch	= true;
	pclclient->bGameServerActionSwitch		= false;

	pclclient->bFrontServerSecretKeySwitch	= false;
	pclclient->bGameServerSecretKeySwitch	= false;

	//	Sleep(1000);

	//����Ʈ ���� �������� �ǵ��ư�
	clUserState.SetState(USERSTATE_FRONT_CONNECTING);

	pclclient->SetGameStatus(GS_INITCONNECTFRONTSERVER);
}

// ���ӵ��߿��� ��� �������� üũ�� �Ѵ�. (PCK - 2007.09.19)
void cltClient::DoMsg_GAMEMSG_RESPONSE_GAMEDISCONNECT_AGE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_GameDisconnect_Age* pclinfo = (cltGameMsgResponse_GameDisconnect_Age*)pclMsg->cData;

	if (m_pDialog[ NCOMMONMSG_DLG ] == NULL)
	{
		CreateInterface(NCOMMONMSG_DLG);
	}
	((CNCommonMsgDlg*)m_pDialog[ NCOMMONMSG_DLG ])->Set(COMMONDLG_CANNOTLOGIN_AGE);

	cltClient* pclclient = (cltClient*)pclClient;

	pclclient->pGameSession->CloseSocket();
	pclclient->pFrontSession->CloseSocket() ;

	pclclient->bReceiveMyCharAllInfoSwitch	= false;
	pclclient->bBackUpSwitch				= false;

	pclclient->siAuthKey		= 0;
	pclclient->bFrontServerActionSwitch	= true;
	pclclient->bGameServerActionSwitch		= false;

	pclclient->bFrontServerSecretKeySwitch	= false;
	pclclient->bGameServerSecretKeySwitch	= false;

	//	Sleep(1000);

	//����Ʈ ���� �������� �ǵ��ư�
	clUserState.SetState(USERSTATE_FRONT_CONNECTING);

	pclclient->SetGameStatus(GS_INITCONNECTFRONTSERVER);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGE_CHARNAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ChangeCharName* pclinfo = (cltGameMsgResponse_ChangeCharName*)pclMsg->cData;

	// �̿���� �̿��ؼ� ĳ���͸��� �����ϴ� �����
	if(pclinfo->m_bUseItem == true)
	{
		if ( pclinfo->siResult == 1 )
		{
			if ( !_tcscmp(pclinfo->szName,TEXT("")) ) return;

			pclCM->CR[1]->pclCI->clBI.clPerson.SetName(pclinfo->szName);

			TCHAR buffer[1024] = TEXT("") ;
			TCHAR* pTitle = GetTxtFromMgr(838);
			TCHAR* pText = GetTxtFromMgr(837);

			StringCchPrintf(buffer, 1024, pText);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, buffer);
		}
		else
		{
			TCHAR* pTitle = GetTxtFromMgr(839);
			TCHAR* pText = GetTxtFromMgr(840);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
		}
	}
	else	// [��ȣ_NHN->NDOORS] �α��ν� ĳ���͸��� �����ϴ� ����� 
	{
		if ( pclinfo->siResult == 1 )	// ĳ���͸� ���� ���� 
		{
			if ( !_tcscmp(pclinfo->szName,TEXT("")) ) return;

			pclCM->CR[1]->pclCI->clBI.clPerson.SetName(pclinfo->szName);

			// ĳ���͸� ���� ������ ����â close
			if(m_pDialog[NCHANGECHARNAME_DLG] != NULL)
				((CNChangeCharName*)m_pDialog[NCHANGECHARNAME_DLG])->DeleteDialog();
		}
		else
		{
			// ������ ĳ���͸��� �ִ� ���.
			if(m_pDialog[NCHANGECHARNAME_DLG] != NULL)
				((CNChangeCharName*)m_pDialog[NCHANGECHARNAME_DLG])->SameName();
		}	
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CHANGE_CHARKIND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Change_CharKind* pclinfo = (cltGameMsgResponse_Change_CharKind*)pclMsg->cData;

	if ( pclinfo->siResult == 1 )
	{
		TCHAR buffer[1024] = TEXT("") ;

		TCHAR* pTitle = NULL;
		TCHAR* pText = NULL;


		if ( pclinfo->siKind == pclCM->CR[1]->pclCI->clBI.GetKind() ) return;
		if ( pclCM->CR[1]->pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique != 0 ||
			pclCM->CR[1]->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique != 0 )
		{
			pTitle = GetTxtFromMgr(841);
			pText = GetTxtFromMgr(842);

			StringCchPrintf(buffer, 1024, pText);
			m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, buffer);
			return;
		}

		pclCM->CR[1]->pclCI->clBI.SetKind(pclinfo->siKind);

		pTitle = GetTxtFromMgr(844);
		pText = GetTxtFromMgr(843);

		StringCchPrintf(buffer, 1024, pText);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, buffer);
	}
	else
	{
		TCHAR* pTitle = GetTxtFromMgr(839);
		TCHAR* pText = GetTxtFromMgr(845);

		m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VillageHaveEventNPC* pclinfo = (cltGameMsgResponse_VillageHaveEventNPC*)pclMsg->cData;
	for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) 
	{
	((cltCharClient*)pclClient->pclCM->CR[1])->siEventNPCKind[i] = pclinfo->siNPCKind[i];
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_NOTICE_QUEST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Notice_Quset* pclnotice = ( cltGameMsgResponse_Notice_Quset* )pclMsg->cData;

	if ( NULL == m_pDialog[NQUESTNOTICE_DLG] )
	{
		CreateInterface( NQUESTNOTICE_DLG );
	}
	switch( pclnotice->siType ) { 
	case HALLOWEENQUEST :
		{
			SI32 gamemasterlevel = pclCM->CR[id]->GetGameMasterLevel()	;
			TCHAR* strTitle = TEXT(" ");
			m_pDialog[NQUESTNOTICE_DLG]->SetTitle( strTitle )	;// ����  Ÿ��Ʋ�� ���� �Ѵ�.
			//NTCHARString512	kExplain(GetTxtFromMgr(8879));
			if (gamemasterlevel == 102 || gamemasterlevel == BASIC_GAMEMASTER_LEVEL || gamemasterlevel == BASIC_GAMEMASTER_LEVEL+1)// GM�϶�
			{
				// �ؽ�Ʈ ���븸 �������ָ� ��
				TCHAR* pTitle = GetTxtFromMgr( 8867 );

				NTCHARString512	kExplain(GetTxtFromMgr(9577 ));
				SI32 siX = pclnotice->siX	;	//	X ��ǥ
				SI32 siY = pclnotice->siY	;	//	Y ��ǥ
				SI32 siMapIndex = pclnotice->siMapIndex	;	// ���ε���
				kExplain.Replace( TEXT("#map#"),	pclClient->pclMapManager->GetMapName( siMapIndex ) );
				kExplain.Replace( TEXT("#x#"),		SI32ToString( siX )	)	;
				kExplain.Replace( TEXT("#y#"),		SI32ToString( siY )	)	;
				((CNQuestNoticeDlg*)m_pDialog[NQUESTNOTICE_DLG])->NoticeEvent2( pclnotice->siKind,  pTitle, kExplain)	;
			}
			else//�ƴ� ��� 
			{
				NTCHARString512	kExplain(GetTxtFromMgr(8868));
				m_pDialog[NQUESTNOTICE_DLG]->SetTitle( strTitle )	;// ����  Ÿ��Ʋ�� ���� �Ѵ�.
				((CNQuestNoticeDlg*)m_pDialog[NQUESTNOTICE_DLG])->NoticeEvent( pclnotice->siKind, pclnotice->siMapIndex)	;				
			}
		}
		break;
	case HALLOWEENSUPRISE :
		{
			m_pDialog[NQUESTNOTICE_DLG]->SetTitle( "" )	;// ����  Ÿ��Ʋ�� ���� �Ѵ�.

			NTCHARString512	kTitle(GetTxtFromMgr(8878));
			NTCHARString512	kExplain(GetTxtFromMgr(8879));
           
			((CNQuestNoticeDlg*)m_pDialog[NQUESTNOTICE_DLG])->NoticeEvent( pclnotice->siKind, kTitle, kExplain)	;
		}
		break;
	}
}

// [����] ���θ��� ������ ����. USE_PROMOTOR_CLIENT
void cltClient::DoMsg_GAMEMSG_RESPONSE_PROMOTERNPC_GIVE_ITEM_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_PromoterNPC_Give_Item_Get* pclInfo = ( cltGameResponse_PromoterNPC_Give_Item_Get* )pclMsg->cData;
	
	if( m_pDialog[NRPBASE_DLG] ) 
		((NPromoter_InfoDlg*)((CNRPBase*)m_pDialog[NRPBASE_DLG])->m_NPromoter_InfoDlg)->SetGiveItem( pclInfo->ItemUnique, pclInfo->ItemNum );
	else if( m_pDialog[NPROMOTER_INFO] ) 
		((NPromoter_InfoDlg*)m_pDialog[NPROMOTER_INFO])->SetGiveItem( pclInfo->ItemUnique, pclInfo->ItemNum );

}

// [����] ���θ��� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PROMOTER_INFO_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Promoter_Info_Get* pclInfo = (cltGameResponse_Promoter_Info_Get*)pclMsg->cData;

	if( m_pDialog[NRPBASE_DLG] ) 
		((NPromoter_InfoDlg*)((CNRPBase*)m_pDialog[NRPBASE_DLG])->m_NPromoter_InfoDlg)->SetPromoterInfo( pclInfo->m_siCharKind, pclInfo->m_siLevel, pclInfo->m_bAuth, pclInfo->m_szPromoterCharName );
	
	else if( m_pDialog[NPROMOTER_INFO] ) 
		((NPromoter_InfoDlg*)m_pDialog[NPROMOTER_INFO])->SetPromoterInfo( pclInfo->m_siCharKind, pclInfo->m_siLevel, pclInfo->m_bAuth, pclInfo->m_szPromoterCharName );
		
}

// [����] ���θ��� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PROMOTER_URL_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Promoter_URL_Get* pclInfo = (cltGameResponse_Promoter_URL_Get*)pclMsg->cData;

	if( NULL == m_pDialog[NRPBASE_DLG] ) return;

	((NPromoter_UrlDlg*)((CNRPBase*)m_pDialog[NRPBASE_DLG])->m_NPromoter_UrlDlg)->SetURL( pclInfo->m_szURL );
}

// [����] ���θ��� ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PROMOTER_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Promoter_Set* pclInfo = (cltGameResponse_Promoter_Set*)pclMsg->cData;

	cltClient * pclclient = (cltClient*) pclClient;
	cltGameMsgRequest_RecommendPerson clRecommendPerson( pclInfo->m_szPromoterName, pclclient->GetCurrentCharInfoList() );
	cltMsg clMsg( GAMEMSG_REQUEST_RECOMMENDPERSON, sizeof(clRecommendPerson), (BYTE*)&clRecommendPerson );
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMEND_INTRODUCE(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Recommend_Introduce* pclInfo = (cltGameResponse_Recommend_Introduce*)pclMsg->cData;

	if ( NULL == m_pDialog[NPROMOTER_INTRODUCE] )
		CreateInterface( NPROMOTER_INTRODUCE );

	((NPromoter_Introduce*)m_pDialog[NPROMOTER_INTRODUCE])->SetRecommendIntroduce( pclInfo->m_szRecommendName, pclInfo->m_siKind, pclInfo->m_siIsConnect );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_RECOMMENDEE_INTRODUCE(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_Recommendee_Introduce* pclInfo = (cltGameResponse_Recommendee_Introduce*)pclMsg->cData;

	if ( NULL == m_pDialog[NPROMOTER_INTRODUCE] )
		CreateInterface( NPROMOTER_INTRODUCE );

	((NPromoter_Introduce*)m_pDialog[NPROMOTER_INTRODUCE])->SetRecommendeeIntroduce( pclInfo->m_szRecommendeeName, pclInfo->m_siKind, pclInfo->m_siIsConnect );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_ITEM_PACKING(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_ValentineDay_Item_Packing* pclInfo = (cltGameResponse_ValentineDay_Item_Packing*)pclMsg->cData;
	
	NTCHARString128 szString = GetTxtFromMgr(10443);
	szString.Replace("#itemname1#", pclItemManager->GetName( pclInfo->m_clResultItem[0].siUnique )  );
	szString.Replace("#itemnum1#",  SI16ToString( pclInfo->m_clResultItem[0].siItemNum ) );
	szString.Replace("#itemname2#", pclItemManager->GetName( pclInfo->m_clResultItem[1].siUnique )  );
	szString.Replace("#itemnum2#",  SI16ToString( pclInfo->m_clResultItem[1].siItemNum ) );

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(10442), szString );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_BUY_ITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_ValentineDay_Buy_Item* pclInfo = (cltGameResponse_ValentineDay_Buy_Item*)pclMsg->cData;

	NTCHARString128 szString = GetTxtFromMgr(10447);
	szString.Replace("#itemname1#", pclItemManager->GetName( pclInfo->m_clBuyItem.siUnique )  );
	szString.Replace("#itemnum1#",  SI16ToString( pclInfo->m_clBuyItem.siItemNum ) );
	
	m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(10442), szString );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_QUESTION(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_ValentineDay_Confession_Question* pclInfo = (cltGameResponse_ValentineDay_Confession_Question*)pclMsg->cData;

	if ( NULL == m_pDialog[VALENTINEDAY_CONFESSION_ANSWER_DLG] )
		CreateInterface( VALENTINEDAY_CONFESSION_ANSWER_DLG );

	((NValentineDayConfessionAnswerDlg*)m_pDialog[VALENTINEDAY_CONFESSION_ANSWER_DLG])->SetQuestion( pclInfo->m_siPersonID, pclInfo->m_szName, pclInfo->m_szMsg );

}
void cltClient::DoMsg_GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_ANSWER(cltMsg* pclMsg, SI32 id)
{
	cltGameResponse_ValentineDay_Confession_Answer* pclInfo = (cltGameResponse_ValentineDay_Confession_Answer*)pclMsg->cData;

	cltCharClient* pclchar = pclCM->GetCharClient(1);
	if( NULL == pclchar ) return;
	
	if( pclInfo->m_bResult )
	{
		NTCHARString256 szString = GetTxtFromMgr(10456);
		szString.ReplaceAll("#rname#", pclInfo->m_szName );
		szString.ReplaceAll("#sname#", pclchar->GetName() );
		
		m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(10455), szString );
	}
	else
	{
		NTCHARString256 szString = GetTxtFromMgr(10458);
		szString.ReplaceAll("#rname#", pclInfo->m_szName );
		szString.ReplaceAll("#sname#", pclchar->GetName() );

		m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(10457), szString );
	}
}



