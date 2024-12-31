//---------------------------------
// 2004/5/20 ���°�
//---------------------------------

//------------------------------------
// CommonLogic
//------------------------------------
#include "MsgType-System.h"
#include "MsgType-Person.h"
#include "MsgType-Item.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Order\Order.h"
#include "Char\CharManager\CharManager.h"

//-------------------------------------
//Client
//-------------------------------------
#include "..\Client.h"
#include "..\Music\Music.h"
//#include "..\Interface\MonsterInfoDlg\MonsterInfoDlg.h"
#include "NInterface/NMonsterInfoDlg/NMonsterInfoDlg.h"

//#include "..\Interface\Notify_GetItem_From_Monster\NotifyGetItemFromMonsterDlg.h"

#include "ninterface/NNewInventory/NNewInventory.h"

#include "../Interface/NotifyGetItemDlg/NotifyGetItemDlg.h"
#include "..\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "..\Effect\ExpCounter\ExpCounter.h"

#include "../NInterface/NNewMakeItem/NNewMakeItemDlg.h"
#include "../NInterface/NNewEnchantOther/NNewEnchantOther.h"

#include "../ninterface/nchatbardlg/NChatBarDlg.h"
#include "../ninterface/NShowGetItemDlg/NShowGetItemDlg.h"
#include "../ninterface/niteminfodlg/ItemInfoDlg.h"
#include "../ninterface/ninfodlg/NInfoDlg.h"
#include "../Interface\RichEditChatMgrDlg\RichEditChatMgrDlgBaseInfo.h"
#include "../ninterface/ncharstatus/NEquipWindow.h"

#include "../ImageInterface/NewYearEvent/NewYearEvent.h"

#include "PCRoom/PCRoomIntro.h"

#include "../NInterface/NCharStatus/NCharStatus.h"
#include "../NInterface/NCharStatus/NCharHorse.h"

#include "../Client/ninterface/NArtifactDlg/NArtifactBaseDlg.h"
#include "../Client/ninterface/NSpaceBoxDlg/NSpaceBoxDlg.h"
#include "NInterface\NRareItemDlg\NRareItemDlg.h"
#include "../Client/ninterface/NElixirDlg/NElixirNPCDlg.h"
#include "../Client/ninterface/NCopfield_NPC/NCopfield_NPC.h"
#include "../Client/NStructureDlg/NewMarket/NNewMarketDlg.h"
#include "../Client/ninterface/NContributionEvent_CommonDlg/NContributionEvent_CommonDlg.h"
#include "../Client/ninterface/NVanlentineDayNPC/NValentineDayTradeDlg.h"
#include "../common/Skill/Skill-Manager.h"
#include "../../CommonLogic/Msg/MsgType-Quest.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_GUILTY(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	cltGuiltyInfo* pclinfo;
	pclinfo = (cltGuiltyInfo*)pclMsg->cData;
	
	pclCM->CR[id]->pclCI->clGuiltyInfo.Set(pclinfo);
	
	if(pclinfo->siLeftPrisonSecond)
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1268);

		StringCchPrintf(buffer, 256, pText, pclinfo->siLeftPrisonSecond,
			pclinfo->siTotalPrisonSecond, pclinfo->szPrisonReason);

		pclMessage->SetPrisonMsg(buffer);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PEERSON_MARKET(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	cltMarketAccount* pclMarket;
	pclMarket = (cltMarketAccount*)pclMsg->cData;
	
	pclCM->CR[id]->pclCI->clMarket.clInfo.Set(pclMarket);
	
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_STOCK(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	cltStockAccount* pclStockInfo;
	pclStockInfo = (cltStockAccount*)pclMsg->cData;
				
	pclCM->CR[id]->pclCI->clStock.clInfo.Set(pclStockInfo);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_STOCKORDER(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	cltCharOrderInfo* pclStockInfo;
	pclStockInfo = (cltCharOrderInfo*)pclMsg->cData;
	
	pclCM->CR[id]->pclCI->clStock.clOrderInfo.Set(pclStockInfo);
	
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_WORLDMONEY(cltMsg*pclMsg, SI32 id)
{
	id = 1;

	cltWorldMoneyAccount* pclWorldMoneyAccount;
	pclWorldMoneyAccount = (cltWorldMoneyAccount*)pclMsg->cData;

	pclCM->CR[id]->pclCI->clWorldMoney.Set(pclWorldMoneyAccount);
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_BANK(cltMsg* pclMsg, SI32 id)
{
	id = 1;
	cltBankAccount* pclBankAccount;
	pclBankAccount = (cltBankAccount*)pclMsg->cData;
				
	pclCM->CR[id]->pclCI->clBank.Set(pclBankAccount);
}

// ��� ��ǰ ������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_ALLITEM(cltMsg* pclMsg, SI32 id)
{
	id = 1;
	cltPItemInfo* pclinfo = (cltPItemInfo*)pclMsg->cData;
	pclCM->CR[id]->pclCI->clCharItem.Set(pclinfo);
	
	//// �޸� ���� �������� ���� ��� ������ ���׷��̵� ==============================================================================
	//CDormancySystem *pclDormancySystem = this->pclDormancySystem;
	//if( NULL != pclDormancySystem)
	//{
	//	CDormancyEquipItemRewardClient *pclDormancyClient = (CDormancyEquipItemRewardClient *)pclDormancySystem->GetDormancyEquipItemReward();
	//	if(NULL != pclDormancyClient)
	//	{
	//		pclDormancyClient->UpgradeItemInven(pclCM->CR[id]);
	//	}
	//}
	////==============================================================================================================================
}

// ��� ������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_SKILL(cltMsg* pclMsg, SI32 id)
{
	id = 1;
 	cltPSkillInfo* pclinfo = (cltPSkillInfo*)pclMsg->cData;
	
	pclCM->CR[id]->pclCI->clCharSkill.Set(pclinfo);

	((CNNewInventory*) m_pDialog[ NNEWINVENTORY_DLG])->SetCharStatusChanged(TRUE);

}

// �Ѱ��� ��� ������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_ONESKILL(cltMsg* pclMsg, SI32 id)
{
	id = 1;

	cltGameMsgResponse_OneSkill* pclinfo = (cltGameMsgResponse_OneSkill*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclchar = pclCM->GetCharClient( id );
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siSkillUnique = pclinfo->siSkillUnique;
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )
	{
		return;
	}

	SI32 siOldSkillExp		= pclchar->pclCI->clCharSkill.GetSkillExp( siSkillUnique );
	SI32 siOldSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );

	pclchar->pclCI->clCharSkill.clSkill[siSkillUnique].Set( &pclinfo->clSkill );

	SI32 siNewSkillExp		= pclchar->pclCI->clCharSkill.GetSkillExp( siSkillUnique );
	SI32 siNewSkillLevel	= pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );

	SI32 siDiff = siNewSkillExp - siOldSkillExp;
	if ( 0 < siDiff )
	{
		pclchar->pclExpCounter->SkillSet( siSkillUnique, siDiff, 30 );
	}

	if ( siOldSkillLevel < siNewSkillLevel )
	{
		TCHAR szNotice[256] = TEXT("");

		if ( pclSkillManager->m_clMasterManager.IsCanTakeEmblemWithNotice(siSkillUnique, siNewSkillLevel, szNotice, sizeof(szNotice)) )
		{
			// �Ʒ� SetText() ���ڿ� ��Ķ����� ���忡 %�Ѱ��� ������ ǥ�õ��� �ʴ´� ���� ǥ���ϱ� ���ؼ� %�� 2���� �־��ش�
			NTCHARString256 strNotice = szNotice;
			strNotice.Replace( TEXT("%"), TEXT("%%") );

			TCHAR* pszTitle = GetTxtFromMgr(5614);

			m_pDialog[ NOTIFYMSG_DLG ]->SetText( pszTitle, strNotice );
		}
	}
	
}


// �ǰ� ������ �޾Ҵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_HEALTH(cltMsg* pclMsg, SI32 id)
{
	id = 1;
	cltHealthInfo* pclinfo  = (cltHealthInfo*)pclMsg->cData;
	
	pclCM->CR[id]->pclCI->clHealthInfo.Set(pclinfo);
}

// Person�� IP������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_IP(cltMsg* pclMsg, SI32 id)
{
 	cltGameMsgResponse_IP* pclinfo = (cltGameMsgResponse_IP*)pclMsg->cData;
	
	id = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(id) == false)return;

	pclCM->CR[id]->pclCI->clIP.Set(&pclinfo->clIP); 

	if( m_pDialog[ NNEWEQUIPWINDOW_DLG ] && m_pDialog[ NNEWEQUIPWINDOW_DLG ]->IsShow() )
	{
		((CNEquipWindow*)m_pDialog[ NNEWEQUIPWINDOW_DLG ])->LoadItemData();
	}
	
}


// Person�� ����Ʈ ���� ��ü�� �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_QUEST(cltMsg* pclMsg, SI32 id)
{
	cltPQuestInfo* pclinfo = (cltPQuestInfo*)pclMsg->cData;
	if(NULL == pclinfo) return;
	
	pclCM->CR[1]->pclCI->clQuestInfo.Set(pclinfo);

	if(pclQuestManager)
	{
		// ���� ã��
		pclQuestManager->bQuestInfoChangedSwitch = true;
		pclQuestManager->Action();
	}
	
}

// Person�� �� ������ ��ü�� �޴´�.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSON_HORSE(cltMsg* pclMsg, SI32 id)
{
	cltPersonHorseInfo* pclinfo = (cltPersonHorseInfo*)pclMsg->cData;
	
	//-----------------------------------------
	// ���� ���� ������ ����Ѵ�. 
	//-----------------------------------------
	cltHorse *pcloldhorse	= pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
	cltHorse* pclnewhorse	= pclinfo->GetCurrentShowHorse();

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	bool isChange = false;
	
	//----------------------------------------
	// ������ ��ȭ�� �ִ��� Ȯ���Ѵ�. 
	//---------------------------------------
	TCHAR text[1024] =TEXT("");
	TCHAR temp[256];
	if(pcloldhorse != NULL && pclnewhorse != NULL)
	{
		if(pcloldhorse->siHorseUnique)
		{
			if(pcloldhorse->siMoveSpeed < pclnewhorse->siMoveSpeed)
			{
				TCHAR* pText = GetTxtFromMgr(1269);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9607);
						break;
				}				
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}
			else if(pcloldhorse->siMoveSpeed > pclnewhorse->siMoveSpeed)
			{
				TCHAR* pText = GetTxtFromMgr(1270);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9608);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}

			if(pcloldhorse->siStr < pclnewhorse->siStr)
			{
				TCHAR* pText = GetTxtFromMgr(1271);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9609);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}
			else if(pcloldhorse->siStr > pclnewhorse->siStr)
			{
				TCHAR* pText = GetTxtFromMgr(1272);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9610);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}

			if(pcloldhorse->siDex < pclnewhorse->siDex)
			{
				TCHAR* pText = GetTxtFromMgr(1273);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9611);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}
			else if(pcloldhorse->siDex > pclnewhorse->siDex)
			{
				TCHAR* pText = GetTxtFromMgr(1274);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9612);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}

			if ( pcloldhorse->siMag < pclnewhorse->siMag )
			{
				TCHAR* pText = GetTxtFromMgr(1275);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9613);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}
			else if ( pcloldhorse->siMag > pclnewhorse->siMag )
			{
				TCHAR* pText = GetTxtFromMgr(1276);

				switch(pcloldhorse->siHorseUnique)
				{
					case HORSEUNIQUE_MOTORCYCLE:
						pText = GetTxtFromMgr(9614);
						break;
				}
				StringCchCopy(temp, 256, pText);
				StringCchCat(text, 1024, temp);
			}
		}

		if(pcloldhorse->siHorseUnique != pclnewhorse->siHorseUnique)
		{
			isChange = true;
		}
	}
	else
	{
		if(pcloldhorse == NULL && pclnewhorse == NULL)
			isChange = false;
		else
			isChange = true;
	}

	// ���� ������ �����Ѵ�.
	pclCM->CR[1]->pclCI->clHorseInfo.Set(pclinfo);

	// ���� �Ҹ� ����/ ���� ���¸� ǥ���Ѵ�. 
	HorseStatusShow(text);

	cltHorse* pclHorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if ( (pclHorse != NULL) && (pclHorse->siHorseUnique) ) 
	{
		SI32 siSoundEffect = 0;

		// ��µ��� Ǯ���ְų�/������ų�/�����߰ų� ������ ���� ����
		switch ( pclHorse->siHorseUnique )
		{
			case HORSEUNIQUE_RUDOLF:	// �絹��
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_RUDOLF_HUNGRY") );
				}
				break;

			case HORSEUNIQUE_TIGER:		// ȣ����
			case HORSEUNIQUE_TIGER2:	// ����S �̺�Ʈ�� ȣ����
			case HORSEUNIQUE_WHITETIGER:// ��ȣ
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_TIGER_HUNGRY") );
				}
				break;
			
			case HORSEUNIQUE_GRAYWOLF:
			case HORSEUNIQUE_WOLF:		// ����
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_WOLF_HUNGRY") );
				}
				break;

			case HORSEUNIQUE_BEAST:		// ����ȣ
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_GUMIHO_HUNGRY") );
				}
				break;

			case HORSEUNIQUE_CAMEL:		// ��Ÿ
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_CAMEL_HUNGRY") );
				}
				break;

			case HORSEUNIQUE_ELEPHANT:	// �ڳ���
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_ELEPHANT_HUNGRY") );
				}
				break;
			case HORSEUNIQUE_MOTORCYCLE:	// �������.
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("HORSEUNIQUE_MOTORCYCLE") );
				}
				break;
			case HORSEUNIQUE_FIREHATCH:		// ����ġ
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_FIREHATCH_HUNGRY") );
				}
				break;
			case HORSEUNIQUE_SASURI:		// �����
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_SASURI_HUNGRY") );
				}
				break;
			default:					// ��µ��� �⺻ ����
				{
					siSoundEffect = pclClient->GetUniqueFromHash( TEXT("SOUND_EFFECT_HORSE_HUNGRY") );
				}
				break;

		}	// switch ( pclHorse->siHorseUnique ) ����

		if ( siSoundEffect )
		{
			PushEffect( siSoundEffect, 0, 0 );
		}
	}

	// ���� Ÿ�� �ִ� ���¸� Ŭ���̾�Ʈ���� ���� Ÿ�� ���ش�. 
 	if(pclinfo->siCurrentHorseRIDEHORSE == true)
	{
		pclCM->CR[1]->RideHorse();	
	}
	else
	{
		pclCM->CR[1]->UnrideHorse();	
	}

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if( m_pDialog[ CLTNCHARSTATUS_DLG ] )
	{
		if(isChange == true) // ���� �ٲ���ٸ�.
		{
			((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->m_bChangedInitHorseStatus = TRUE;
			((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->InitHorseStatusInfo();
			((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->UpdateHorseStatusInfo();
		}
	}
}


// Ư�� ������ �Ѱ��� ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONENCHANTITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	
	cltGameMsgResponse_PersonItemInfo* pclinfo = (cltGameMsgResponse_PersonItemInfo*)pclMsg->cData;
	id = 1;
	if(m_pDialog[NNEWITEMMAKE_DLG])
	{		
		if(pclCM->CR[id]->siOrgInvEnchantInx!=0 && pclinfo->clItem.siUnique !=0)
		{

			CNewMakeItemDlg* enchantdlg = (CNewMakeItemDlg* )m_pDialog[NNEWITEMMAKE_DLG];

/*
			(enchantdlg->NewEnchantTab)->m_InterfaceFactory.GetListView(NEWMAKE_LISTVIEW_ORIGINALITEM)->DeleteAllItems();
			(enchantdlg->NewEnchantTab)->m_InterfaceFactory.GetListView(NEWMAKE_LISTVIEW_MATERIALITEM)->DeleteAllItems();			
			(enchantdlg->NewEnchantTab)->m_InterfaceFactory.GetListView(NEWMAKE_LISTVIEW_ELEMENTITEM)->DeleteAllItems();
*/


			(enchantdlg->NewEnchantTab)->SetInitInchant();
//			(enchantdlg->NewEnchantTab)->EnableButton(true,true,true,true);



			//����� �ʱ�ȭ ��Ŵ
			SI32 siTempEnchantItemIndex[NOW_ENCHANT_NUMBER] = {0,};
			ZeroMemory( siTempEnchantItemIndex, sizeof(siTempEnchantItemIndex) );

			cltGameMsgRequest_EnchantItem_SelectedIndex clGameMsgRequest_EnchantItem_SelectedIndex( 0, 0, siTempEnchantItemIndex, 0 );
			cltMsg clMsg(GAMEMSG_REQUEST_ENCHANTITEMINVINDEX, sizeof(clGameMsgRequest_EnchantItem_SelectedIndex), (BYTE*)&clGameMsgRequest_EnchantItem_SelectedIndex);
			SendMsgToServer((sPacketHeader*)&clMsg);	


			cltGameMsgRequest_Enchant_Switch clGameMsgRequest_Enchant_Switch(false );
			cltMsg clMsg1(GAMEMSG_REQUEST_ENCHANTITEMSWITCH, sizeof(clGameMsgRequest_Enchant_Switch), (BYTE*)&clGameMsgRequest_Enchant_Switch);
			SendMsgToServer((sPacketHeader*)&clMsg1);	

			//(enchantdlg->NewEnchantTab)->ShowOrgEnchantItem(pclinfo->clItem);
		}
	}

	// [�߰� : Ȳ���� 2008. 3. 5 => ��Ƽ��Ʈ ����â�� ���ִµ� �κ��̵��� �־��ٸ� ��Ƽ��Ʈ ���� ������ ��� �ʱ�ȭ ��Ű��.]
	if( pclclient->m_pDialog[ARTIFACT_BASE_DLG] )
	{
		((NArtifactBaseDlg*)pclclient->m_pDialog[ARTIFACT_BASE_DLG])->Clear();
	}
	if( pclclient->m_pDialog[NSPACE_BOX] )
	{
		((CNSpaceBoxDlg*)pclclient->m_pDialog[NSPACE_BOX])->SetMyListView();
	}
	if( pclclient->m_pDialog[NELIXIR_NPC_DLG] )
	{
		((NElixirNPCDlg*)pclclient->m_pDialog[NELIXIR_NPC_DLG])->SetMyInventory();
	}
	if( pclclient->m_pDialog[NCOPFIELD_DLG] )
	{
		((NCopfield_NPC*)pclclient->m_pDialog[NCOPFIELD_DLG])->DelUseItem();
	}
	if( pclclient->m_pDialog[VALENTINEDAY_TRADE_DLG] )
	{
		((NValentineDayTradeDlg*)pclclient->m_pDialog[VALENTINEDAY_TRADE_DLG])->SetMyInven();
	}
	
	NContributionEvent_CommonDlg::StaticSetContributionInputItemList( NULL, NULL );
}

// Ư�� ������ �Ѱ��� ����ü ������ �޾� ������Ʈ�Ѵ�.( �ϴ��� �������� - ���� Ȯ���� �˼� ����.) 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CRYSTALITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	
	cltGameMsgResponse_CrystalItemInfo* pclinfo = (cltGameMsgResponse_CrystalItemInfo*)pclMsg->cData;
	
	id = 1;

	// OldItemInfo
	//cltCrystalItemInfo cloldCrystalitem;
	//cloldCrystalitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemPos]);
	//if(cloldCrystalitem.siDurability[crynum] != clnowCrystalitem.siDurability[crynum])

	cltCrystalItemInfo clnowCrystalitem;
	clnowCrystalitem.Set(&pclinfo->clCrystalItemInfo);

	cltItem * pclItem = &pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemPos];

	for(SI16 crynum = 0; crynum < MAX_CRYSTAL_NUM ; crynum ++)
	{
		pclItem->cltItemCrytal[crynum].SetDurability(clnowCrystalitem.siDurability[crynum]);
	}

	//pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clItem);
}


// Ư�� ������ �Ѱ��� ������ �޴´�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_PERSONITEMINFO(cltMsg* pclMsg, SI32 id)
{

	cltClient* pclclient= (cltClient*)pclClient;
	
	cltGameMsgResponse_PersonItemInfo* pclinfo = (cltGameMsgResponse_PersonItemInfo*)pclMsg->cData;
	
	id = 1;

	// OldItemInfo

	cltItem clolditem;
	
	if ( -1 == pclinfo->siItemPos )
	{
		clolditem.Init();
	}
	else
	{
		clolditem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemPos]);

		pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clItem);

	}

	if( m_pDialog[ NNEWMARKET_DLG ] )
		((NNewMarketUserSellDlg*)((NNewMarketDlg*)m_pDialog[ NNEWMARKET_DLG ])->m_pUserChildDlg[0])->SetMyInventory();

	//[����] ���ո��Ͽ��� ������ ������� �ش� �����ۿ� ���� ����Ʈ�� �ٽ� ��û�Ѵ�.
	if( PERSONITEMINFO_OPTION_BUYFROMNEWMARKET == pclinfo->siOption )		
	{
		if( m_pDialog[ NNEWMARKET_SUB_DLG ] )
		{
			((NNewMarketUserBuyDlgSub*)m_pDialog[ NNEWMARKET_SUB_DLG ])->RequestNewMarketOrderList( pclinfo->clItem.siUnique );
		}
	}
	else
	{
		if( m_pDialog[ NNEWMARKET_SUB_DLG ] )
		{
			((NNewMarketUserBuyDlgSub*)m_pDialog[ NNEWMARKET_SUB_DLG ])->RequestNewMarketOrderListRefresh();
		}
	}

	// ���� ������ ���� Person��ArmCode�� �ٲ��ش�. 
	//if(pclinfo->clItem.siUnique > 0)
		pclCM->CR[id]->ChangeArmCode(pclinfo->siItemPos, pclinfo->clItem.siUnique);

	// ���ڿ� ���� ĳ���� ��ũ�� �ٽ� �����. - by LEEKH
	if(pclinfo->siItemPos == PERSONITEM_HAT)
		((cltCharClient*)pclCM->CR[id])->MakeRankMarkEncBuffer();

	// ������ ����â�� �����ִٸ�, ��������� ������Ʈ �Ѵ�. - by LEEKH
	if ( ((cltNInfoDlg*)m_pDialog[ NITEMINFO_DLG]) != NULL && ((cltNInfoDlg*)m_pDialog[ NITEMINFO_DLG])->IsShow() == true )
	{
		CNItemInfoDlg* pTabDlg0 = ((cltNInfoDlg*)m_pDialog[ NINFO_DLG ])->m_pTabDlg0;
		if( pTabDlg0 != NULL && pTabDlg0->IsShow() == true )
		{
			pTabDlg0->SetMaterialRefresh();
		}
	}

	TCHAR buffer[256];
	TCHAR itemname[128];

	SI32 siForeverDurability  = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2 = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	switch( pclinfo->siOption )
	{
	case PERSONITEMINFO_OPTION_MAKE:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKESUCCESS")), 0, 0);

			if(pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true)
			{
				// �ֺ��� ĳ���Ϳ��� ���� ���絥 ���������� �˸���. 
				if(pclinfo->siChangedNum)
				{
					TCHAR buffer[256];

					//KHY - 0421 -  ������ ������ �������� ���� �ʴ´�.
					/*if ((pclItemManager->GetItemAtb(pclinfo->clItem.siUnique) & ITEMATB_OBJECT) &&
						pclinfo->clItem.GetDurability() != siForeverDurability && pclinfo->clItem.GetDurability() != siForeverDurability2 )
					{
						TCHAR* pText = GetTxtFromMgr(1277);

						StringCchPrintf(buffer, 256, pText, itemname, pclinfo->clItem.GetMaxDurability(pclItemManager));
					}
					*/
					if ( pclinfo->clItem.GetDurability() == siForeverDurability2 && pclinfo->clItem.uiDateUseDay > 0)
					{
						TCHAR* pText = NULL;
						// ���ǰ�� "ǰ�������Ⱓ"�� ǥ������ �ʴ´�.
						if(pclinfo->clItem.clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5)
							pText = GetTxtFromMgr(6988);
						else
							pText = GetTxtFromMgr(5638);

						if(pText)	StringCchPrintf(buffer, 256, pText, itemname, pclinfo->clItem.uiDateUseDay);
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(1278);

						StringCchPrintf(buffer, 256, pText, itemname);
					}
					// �޽����� ������ ������. 
					SendChatMessage(CHATMODE_SYSTEM, buffer);
				}
			}
		}
		break;
	case PERSONITEMINFO_OPTION_MAKELUCK:
		{
			PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_LUCKY")), 0, 0);


			if(pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true)
			{

				// �ֺ��� ĳ���Ϳ��� ���� ���絥 ���������� �˸���. 
				if(pclinfo->siChangedNum)
				{
					//TCHAR buffer[256];
					if( (pclItemManager->GetItemAtb(pclinfo->clItem.siUnique) & ITEMATB_OBJECT ) &&
						pclinfo->clItem.GetDurability() != siForeverDurability && pclinfo->clItem.GetDurability() != siForeverDurability2 )
					{
						TCHAR* pText = GetTxtFromMgr(1279);

						StringCchPrintf(buffer, 256, pText,
							itemname, pclinfo->clItem.GetMaxDurability(pclItemManager));
					}
					else if ( pclinfo->clItem.GetDurability() == siForeverDurability2  && pclinfo->clItem.uiDateUseDay > 0)
					{
						TCHAR* pText;

						// ���ǰ�� ǰ�������Ⱓ�� ǥ������ �ʴ´�.
						if(pclinfo->clItem.clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5)
							pText = GetTxtFromMgr(6989);
						else
							pText = GetTxtFromMgr(5639);
						
						if(pText)	StringCchPrintf(buffer, 256, pText, itemname, pclinfo->clItem.uiDateUseDay);
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(1278);

						StringCchPrintf(buffer, 256, pText, itemname);
					}
					// �޽����� ������ ������. 
					SendChatMessage(CHATMODE_SYSTEM, buffer);
				}
			}

		}
		break;
	case PERSONITEMINFO_OPTION_MAKEALMOSTFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKESUCCESS")), 0, 0);

//			if(pclItemManager->GetItemAtb(pclinfo->clItem.siUnique) & ITEMATB_OBJECT)
//			{
//				TCHAR* pText = GetTxtFromMgr(1280);
//
//				StringCchPrintf(buffer, 256, pText, pclinfo->clItem.GetMaxDurability(pclItemManager));
//			}
//			else
//KHY - 0731 - �������� ����.
			{
				TCHAR* pText = GetTxtFromMgr(1281);

				StringCchPrintf(buffer, 256, pText);
			}
			//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
			if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
			{
				pclClient->pclMessage->SetPersonalMsg(buffer);
			}
			else
			{
				pclClient->pclMessage->SetMsg(buffer);
			}

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true)
			{
				// �ֺ��� ĳ���Ϳ��� ���� ���絥 ���������� �˸���. 
				if(pclinfo->siChangedNum)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(1282);

					StringCchPrintf(buffer, 256, pText, itemname);
					// �޽����� ������ ������. 
					SendChatMessage(CHATMODE_SYSTEM, buffer);
				}
			}
		}
		break;
	case PERSONITEMINFO_OPTION_MAKEFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			if(pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(1283);

				StringCchPrintf(buffer, 256, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}

				// �ֺ��� ĳ���Ϳ��� ���� ����µ� ���� ������ �˸���. 
				TCHAR buffer[256];
				pText = GetTxtFromMgr(1284);

				StringCchPrintf(buffer, 256, pText, itemname);
				// �޽����� ������ ������. 
				SendChatMessage(CHATMODE_SYSTEM, buffer);
			}
		}
		break;
	case PERSONITEMINFO_OPTION_EVENT:
		{
			//m_pNewYearEventNotice->Set();
			//�迵�� ���� 2007.12.11 [20391] SetItemData�� ���ڸ� �ֱ����� ����
			if(pclinfo->siChangedNum)
			{
				if(pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true)
				{
					cltItem clitem;
					clitem.Set(&pclinfo->clItem);
					clitem.siItemNum	= pclinfo->siChangedNum;

					SI16 itemCnt = 0;
					itemCnt = clitem.siItemNum;
					GMONEY price   = pclinfo->siPrice;

					if ( ! m_pDialog[ NSHOWGETITEM_DLG ]  )
					{
						((cltClient*)pclClient)->CreateInterface( NSHOWGETITEM_DLG );
					}

					((CNShowGetItemDlg*)m_pDialog[ NSHOWGETITEM_DLG ])->SetItemData( &clitem, itemname, price );
				}
			}

		}
		break;
	case PERSONITEMINFO_OPTION_WASTE:
		{
			// �������� �Ҹ�Ǿ� ������ �ļ�.
			TCHAR itemname[128];
			if(clolditem.GetFullName(pclItemManager, itemname, 128) == true)
			{
				PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
				TCHAR* pTitle = GetTxtFromMgr(1285);
				TCHAR* pText = GetTxtFromMgr(1286);

				m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, itemname);
			}
		}
		break;
	case PERSONITEMINFO_OPTION_ENCHANTITEMFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5933); //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}

				if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
					((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();
			}
		}
		break;
	case PERSONITEMINFO_OPTION_NOSEALINGUP_ENCHANTFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5940); //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}

				if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
					((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();

			}
		}
		break;
	case PERSONITEMINFO_OPTION_NOSKILLENCHANTFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5924); //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}

				if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
					((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();
			}
		}
		break;
	case PERSONITEMINFO_OPTION_NOMONEYENCHANTFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5925); //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				pclMessage->SetMsg(buffer);

				if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
					((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();
			}
		}
		break;
	case PERSONITEMINFO_OPTION_NOCONDENCHANTFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5926) ; //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}		
			}

			if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
				((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();

		}
		break;
	case PERSONITEMINFO_OPTION_LASTENCHANTITEMFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pText = GetTxtFromMgr(5923) ; //GetTxtFromMgr(5808);

				sprintf(buffer, pText, itemname);
				//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
				if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
				{
					pclClient->pclMessage->SetPersonalMsg(buffer);
				}
				else
				{
					pclClient->pclMessage->SetMsg(buffer);
				}
			}
			if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
				((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();
		}
		break;
	case PERSONITEMINFO_OPTION_NOMATENCHANTITEMFAIL:
		{
			PushEffect(GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKEFAIL")), 0, 0);

			cltClient * pclclient = (cltClient*)pclClient;

			TCHAR itemname[128];
			if(pclinfo->clItem.GetFullName(pclItemManager, itemname,128) == true)
			{
				TCHAR* pTitle = GetTxtFromMgr(5923);

				// �ֺ��� ĳ���Ϳ��� ���� ����µ� ���� ������ �˸���. 
				TCHAR * pText = GetTxtFromMgr(5919);

				if (pclclient->m_pDialog[ NOTIFYMSG_DLG ])
					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,pText);

				SendChatMessage(CHATMODE_SYSTEM, pText);
				if(m_pDialog[ NNEWENCHANTOTHER_DLG ] )
					((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG ])->PushCancel();

			}
		}
		break;
	case PERSONITEMINFO_OPTION_SHOW:
	case PERSONITEMINFO_OPTION_WARITEM:
	case PERSONITEMINFO_OPTION_SPECIALQUEST:
	case PERSONITEMINFO_OPTION_FAMELEVEL:
	case PERSONITEMINFO_OPTION_MASTER:
	case PERSONITEMINFO_OPTION_QUEST:
	case PERSONITEMINFO_OPTION_ROULETTEGAME:
	case PERSONITEMINFO_OPTION_BEGINNERWEAPON:
	case PERSONITEMINFO_OPTION_MOFUMOFUEVENT:
	case PERSONITEMINFO_OPTION_SERVEREVENTQUEST:
	case PERSONITEMINFO_OPTION_HALLOWEENEVENT:
	case PERSONITEMINFO_OPTION_PVP_LEAGUE:
	case PERSONITEMINFO_OPTION_NEWYEAREVENT:
	case PERSONITEMINFO_OPTION_SEQGMCOMMAND:
	case PERSONITEMINFO_OPTION_DORMANCY:
	case PERSONITEMINFO_OPTION_BATTLEROYAL:
	case PERSONITEMINFO_OPTION_ADDITIONALITEM_GET:
		{
			// ȭ�鿡 ����ǰ�� ������� ǥ���Ѵ�. 
			if(pclinfo->siChangedNum)
			{
				if( pclinfo->clItem.GetFullName(pclItemManager, itemname, 128) == true )
				{
					cltItem clitem;
					clitem.Set(&pclinfo->clItem);
					clitem.siItemNum	= pclinfo->siChangedNum;

					SI16 itemCnt = 0;
					itemCnt = clitem.siItemNum;
					GMONEY price   = pclinfo->siPrice;

					((CNChatBarDlg*)m_pDialog[ NCHATBAR_DLG ])->ItemGetChatRecv( itemname, itemCnt, price ) ;

					if ( ! m_pDialog[ NSHOWGETITEM_DLG ]  )
					{
						((cltClient*)pclClient)->CreateInterface( NSHOWGETITEM_DLG );
					}

					((CNShowGetItemDlg*)m_pDialog[ NSHOWGETITEM_DLG ])->SetItemData( &clitem, itemname, price );
				}
			}
		}
		break;
	case PERSONITEMINFO_OPTION__TREASUREEVENTITEMUSE:
		{
			//����ã�� �̺�Ʈ // ������ ��� �ߴ�. ����Ʈ�� ��û�Ѵ�.
			// �����ݴ� ��
			// ���� �ش� ������ ����̶��
			pclClient->pclQuestManager->bNewQuseOpened = true;
			cltGameMsgRequest_QuestGoing clInfo( QUEST_TYPE_FINDTREASURE, FIND_TREASUREEVENT_QUEST_UNIQUE, QUEST_STEP_MIDDLE);
			cltMsg clMsg(GAMEMSG_REQUEST_SETQUESTGOING, sizeof(clInfo), (BYTE*)&clInfo);
			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
		}break	;
	default:
		break;
	}

	// [�߰� : Ȳ���� 2008. 3. 5 => ��Ƽ��Ʈ ����â�� ���ִµ� �κ��̵��� �־��ٸ� ��Ƽ��Ʈ ���� ������ ��� �ʱ�ȭ ��Ű��.]
	if( pclclient->m_pDialog[ARTIFACT_BASE_DLG] )
	{
		((NArtifactBaseDlg*)pclclient->m_pDialog[ARTIFACT_BASE_DLG])->Clear();
	}
	if( pclclient->m_pDialog[NSPACE_BOX] )
	{
		((CNSpaceBoxDlg*)pclclient->m_pDialog[NSPACE_BOX])->SetMyListView();
	}
	if( pclclient->m_pDialog[NELIXIR_NPC_DLG] )
	{
		((NElixirNPCDlg*)pclclient->m_pDialog[NELIXIR_NPC_DLG])->SetMyInventory();
	}
	if( pclclient->m_pDialog[NCOPFIELD_DLG] )
	{
		((NCopfield_NPC*)pclclient->m_pDialog[NCOPFIELD_DLG])->DelUseItem();
	}
	if( pclclient->m_pDialog[VALENTINEDAY_TRADE_DLG] )
	{
		((NValentineDayTradeDlg*)pclclient->m_pDialog[VALENTINEDAY_TRADE_DLG])->SetMyInven();
	}

	pclClient->pclCM->CR[1]->DoQuestCheckAndAction( QUEST_CLEAR_COND_ITEM );
	
	NContributionEvent_CommonDlg::StaticSetContributionInputItemList( NULL, NULL );
}

// ĳ���� �⺻ ������ ������Ʈ �Ѵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CHARUPDATE(cltMsg* pclMsg, SI32 id)
{
	cltBasicCharUpdateInfo*   pclupdate = (cltBasicCharUpdateInfo*)pclMsg->cData;

	bool bmovetoswitch	= false;
	bool bselfswitch	= false;

	SI32 charunique		= pclupdate->siCharUnique;
	SI32 life			= pclupdate->siLife;
	SI32 reservedlife	= pclupdate->siReservedLife;
	SI32 mana			= pclupdate->siMana;
	SI32 x				= pclupdate->siX;
	SI32 y				= pclupdate->siY;
	SI32 movespeed		= pclupdate->siMoveSpeed;
	UI08 gmmode			= pclupdate->uiGMMode;
	bool pcroom			= pclupdate->bPCRoom;

	SI08 makeanitype	= pclupdate->siMakeAniType;

	SI32 charid = 0;
	
	if(charunique == MyCharUnique)
	{
		charid = 1;
	}
	else
	{
		charid = cltCharCommon::CharUniqueInfo[charunique];
	}
	
	if(charid <= 0)return ;

	// ����ڰ� �ڱ� �ڽ����� ����. 
	if(pclCM->CR[charid]->GetCharUnique() == MyCharUnique)
	{
		bselfswitch = true;
	}
	

	// ��� ������Ʈ,, 
	if(pclupdate->bUrgentMode)
	{
		bmovetoswitch = true;
	}
	else
	{
		
		// ������ ������ �̻� �߻��ؾ� ������ �̵���Ų��. 
		SI32 length = max( TABS(x - pclCM->CR[charid]->GetX()), TABS(y - pclCM->CR[charid]->GetY()));

		// �ڱ� �ڽ��� ��ġ ������Ʈ ���� �ʴ´�. 
		if(length && bselfswitch == false)
		{
			// ������� ĳ���Ͷ��, 
			if(pclCM->CR[charid]->GetCurrentOrder() == ORDER_WAIT)
			{
				if(length > 4)
				{
					bmovetoswitch = true;
				}
				else
				{
					OrderMove(charid, x, y, BY_COMPUTER);
				}
			}
			else
			{
				if(length > 3)
				{
					bmovetoswitch = true;
				}
			}
		}
	}

	// �ε����ϰ� �����̵��� �ؾ� �ϴ� �����, 
	if(bmovetoswitch)
	{
		// ĳ������ ��ġ�� �̵���Ų��. 
		pclCM->CR[charid]->MoveTo(x, y);
		
		// �̵� ��Ȳ�� �ʱ�ȭ�Ѵ�. �׷��� ���Ӱ� ���� ã���ϱ�. 
		pclCM->CR[charid]->MoveInit();
	}

//	pclCM->CR[charid]->SetLife(life);
//	pclCM->CR[charid]->clPB.siReservedLife	= reservedlife;

	// Ŭ�� ������ Ŭ������ �������� ������ ���������� �����ش�.
	pclCM->CR[charid]->SetLife(life);

	if( pclCM->CR[charid]->clPB.siReservedLife >= reservedlife )
	{
	}
	else
	{
		pclCM->CR[charid]->clPB.siReservedLife	= reservedlife;
	}

	pclCM->CR[charid]->SetMana(mana);
	
	// �ڱ� �ڽ��� �ƴϸ� �̵��ӵ��� ������Ʈ �Ѵ�. 
	if(pclCM->CR[charid]->GetCharUnique() != MyCharUnique)
	{
		pclCM->CR[charid]->clPB.GivenMoveSpeed	= movespeed;
	}
	
	/*cyj PC����� ����
	if( pclCM->CR[charid]->GetCharUnique() == MyCharUnique &&
		pclCM->CR[charid]->pclCI->clBI.uiGMMode == false &&
		gmmode == true ) {
		
		m_pPCRoomIntro->Start();		
	}
	*/

	pclCM->CR[charid]->pclCI->clBI.uiGMMode = gmmode;
	pclCM->CR[charid]->pclCI->clBI.bPCRoom = pcroom;
	pclCM->CR[charid]->siPersonalMakeItemType = makeanitype;
	pclCM->CR[charid]->SetEnchantEffect(makeanitype);

}
