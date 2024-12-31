//---------------------------------
// 2003/8/8 ���°�
//---------------------------------

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"

#include "../../Common/Map/Map.h"
#include "Char/CharManager/CharManager.h"

#include "../../../Server/AuthServer/AuthMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Village.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Guild.h"
//���ϸ� ����Ʈ 3
#include "../../../DBManager/GameDBManager_World/DBMsg-DailyQuest3.h"
#include "Skill/Skill-Manager.h"

#include "../../Common/PartyMgr/PartyObj.h"
#include "../../Common/PartyMgr/PartyMgr.h"

#include "../../common/Item/ItemCommon/cltSetItem.h"

#include "Guild/Guild.h"

#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "MsgType-Item.h"
#include "Msg/MsgType-Personalshop.h"
#include "Msg/MsgType-Quest.h"
#include "Msg/MsgType-Party.h"
//���ϸ� ����Ʈ 3
#include "Msg/MsgType-DailyQuest3.h"

#include "MsgRval-Define.h"

//------------------------------------
// Server
//------------------------------------
#include "Statistics/Statistics.h"
#include "../Minister/MinisterBase.h"
#include "../Minister/Minister-Gongzo.h"
#include "../Minister/MinisterMgr.h"

// ������ ����. (�ٸ���) 
void cltServer::DoMsg_DBMSG_RESPONSE_SETITEM(sPacketHeader* pPacket)
{
	sDBResponse_SetItem* pclMsg = (sDBResponse_SetItem*)pPacket;

	if(pclMsg->siResult == 0)return ;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// ���� ����. . 
void cltServer::DoMsg_DBMSG_RESPONSE_ENCHANT(sPacketHeader* pPacket)
{
	sDBResponse_Enchant* pclMsg = (sDBResponse_Enchant*)pPacket;

	if(pclMsg->siResult == 0)return ;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		//--------------------------------
		// FromItem ���� 
		//--------------------------------
		if( pclMsg->siFromPos >= 0 && pclMsg->siFromPos < MAX_ITEM_PER_PERSON )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siFromPos].Set(&pclMsg->clFromItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siFromPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		//---------------------------------
		// ToItem ����. 
		//---------------------------------
		if( pclMsg->siToPos >= 0 && pclMsg->siToPos < MAX_ITEM_PER_PERSON )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToPos].Set(&pclMsg->clToItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siToPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}


		//-----------------------------------------------------------
		// �ƹ������̳� ��� �߶󺸴� ����Ʈ���,
		//-----------------------------------------------------------
		if(pclMsg->siResult == 1)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SCROLL);

		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			TCHAR str[50] = {'\0', };
			StringCchPrintf(str,  sizeof(str), "FromUniqe = %d, FromPos = %d, FromNum = %d", 
												pclMsg->clFromItem.siUnique,
												pclMsg->siFromPos,
												pclMsg->clFromItem.siItemNum);
			

			// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ ���⿡ �����Ų ����.(���� -> ��ȭ�������� ��ġ)
			// param1	 == ������ ����ũ, 
			// param2	 == ������ ��ġ, 
			// param3	 == ������ ����. 
			// pszParam1 == ���� ������ ����.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_ENCHANT_ITEM, 
								 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								 pclMsg->clToItem.siUnique, pclMsg->siToPos, pclMsg->clToItem.siItemNum, 0, 0, 
								 str, NULL);
		}
	}
}

// �κ����� �������� �����϶�� ��û�� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MAKEITEMINV(sPacketHeader* pPacket)
{
	sDBResponse_MakeItemInv* pclMsg = (sDBResponse_MakeItemInv*)pPacket;

	//----------------------------
	// ���̵��� �������� Ȯ���Ѵ�. 
	//----------------------------
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == false)return ;
	if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)return ;

	// �ֹ����� ���̵� Ȯ���Ѵ�. 
	SI32 materialcharid;
	if(pclMsg->siPersonID == pclMsg->siMaterialPersonID)
	{
		materialcharid = id;
	}
	else
	{
		materialcharid = pclCM->GetIDFromPersonID(pclMsg->siMaterialPersonID);
	}

	if( pclCM->IsValidID(materialcharid) == false)		return;
	// �������� �߰��Ǵ� �ڸ��� �Ǿ� �ִ� ������ �����Ѵ�. 
	cltCharServer* pclMaterialChar = (cltCharServer*)pclCM->CR[materialcharid];
	if(pclMaterialChar == NULL)return ;

	pclMaterialChar->SetInputItemReserve(pclMsg->siOutputPos, 0);


	bool bupdateinvswitch = false;
	bool bcontinueswitch = false;
	switch(pclMsg->siResult)
	{
	case 0:	return;		break;
	case 1:	
		{
			// �������� ����. 
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{				cltCharServer* pclMakerChar = pclCM->GetCharServer(id);
			if(NULL == pclMakerChar)
				return;

			// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ �������� ����.
			// param1 == ��������ġ.			
			// param2 == MaterialPersonIDMoney,	 
			// param3 == �ֹ��ڰ� ����⸦ ����� ����, 
			// param4 == ���� ������ ��ǰ�ΰ�. 
			// param5 == �� ���� ����Ƽ ���.
			if( pclMaterialChar->bPersonalShopSwitch == true &&
				pclMaterialChar->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM )
			{
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_COMMISSION , LOGCOMMAND_INDEX_COMMISSION_CLIENT , 
					0, pclMaterialChar, NULL, pclMsg->siPersonID, pclMsg->siFee, pclMsg->siPersonIDMoney, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
					pclMsg->siOutputPos, pclMsg->siMaterialPersonIDMoney, pclMsg->siOrderNumber, pclMsg->bAlmostFailSwitch, pclMsg->siLuckQuality,
					NULL, NULL);
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_COMMISSION , LOGCOMMAND_INDEX_COMMISSION_END , 
					0, pclMaterialChar, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					0, 0, 0, 0, 0,
					NULL, NULL);
			}
			else if( pclMakerChar->bPersonalShopSwitch == true &&
				pclMakerChar->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT )
			{
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_COMMISSION , LOGCOMMAND_INDEX_COMMISSION_MAKER , 
					0, pclMakerChar, NULL, pclMsg->siMaterialPersonID, pclMsg->siFee, pclMsg->siPersonIDMoney, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
					pclMsg->siOutputPos, pclMsg->siMaterialPersonIDMoney, pclMsg->siOrderNumber, pclMsg->bAlmostFailSwitch, pclMsg->siLuckQuality,
					NULL, NULL);
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_COMMISSION , LOGCOMMAND_INDEX_COMMISSION_END , 
					0, pclMaterialChar, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					0, 0, 0, 0, 0,
					NULL, NULL);
			}
			else
			{
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_MAKE_ITEM, 
					0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siMaterialPersonID, pclMsg->siFee, pclMsg->siPersonIDMoney, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
					pclMsg->siOutputPos, pclMsg->siMaterialPersonIDMoney, pclMsg->siOrderNumber, pclMsg->bAlmostFailSwitch, pclMsg->siLuckQuality,
					NULL, NULL);
			}
			}
		}
		break;							

	case 2:								// �ϼ�ǰ ���� �ڸ��� �̹� �ٸ� ��ǰ�� ����. 
		{
			if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
			{
				pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);

				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siOutputPos], 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			return;	
		}
		break;
	case 3:								// �����ᰡ �����Ͽ� ��ǰ ���� ����. 
		break;
	default:
		return ;
	}

	
	
	//--------------------------
	// �κ��� ������Ʈ �Ѵ�. 
	//--------------------------
	if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);

	SI32 skillunique	= 0;
	SI32 skillexp		= 0;

	if(pclMsg->siAddedNum)
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

		SI32 exp = 0;

		SI32 ref = pclItemManager->FindItemRefFromUnique(pclMsg->clItem.siUnique);
		if(ref > 0)
		{
			if(pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill && pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel)
			{
				cltItemPriceUnit* pclprice	= pclItemManager->GetCurrentPrice(pclMsg->clItem.siUnique);
				if(pclprice)
				{
					// ���� ��踦 ����. 
					pclStatisticsManager->clDailyStatistics.siMakeMoney+= pclprice->siPrice;

					skillunique = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
					if(skillunique >= 0)
					{
						SI32 siGetType = pclItemManager->pclItemInfo[ref]->siType;

						if ( pclClient->IsCountrySwitch(Switch_MakeFoodHealEXP) && ((ITEMTYPE_FOOD == siGetType) || ((ITEMTYPE_HEAL == siGetType))) )
						{
							exp = CalcExp_MakeItem_FoodHeal( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum );
						}
						else if ( pclClient->IsCountrySwitch(Switch_MakeItemEXP) )
						{
							exp = CalcExp_MakeItem_New( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum );
						}
						else
						{
							exp = CalcExp_MakeItem( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum, pclprice->siPrice );
						}


						// �ش� ����� ���� ������ ���Ѵ�. 
						/*SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclchar->pclCI->clCharItem.clItem);

						// ���� ������ �ش��ϴ� ����� ���Ѵ�.
						SI32 skillrank = (skilllevel/6) + 1;
						if( skillrank > 16 )	skillrank = 15;

						SI32 skillLevelLimit = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

						// ���� �Ϸ��� �������� ����� ���Ѵ�.
						SI32 skillRankLimit = ( skillLevelLimit/6 ) + 1;
						if( skillRankLimit > 16 )	skillRankLimit = 15;

						// �����۰� ���� ������� ���� �г�Ƽ ��� ( ����, ���� ����ġ ���� )
						SI32 siskillgap = skillrank - skillRankLimit;
						SI32 siPenalty = 120;
						if ( siskillgap == 1)		siPenalty = 100;
						else if (siskillgap == 2 )	siPenalty = 80;
						else if (siskillgap == 3 )	siPenalty = 20;
						else if (siskillgap == 4 )	siPenalty = 10;
						else if (siskillgap == 5 )	siPenalty = 5;
						else if (siskillgap >= 5 )	siPenalty = 2;

						// �ش� ����� å���� ���� ��ų����
						SI32 skilllevlbybook = pclchar->pclCI->clCharSkill.GetSkillLevel(skillunique);
						// å���� ���� ������濡 ���� �г�Ƽ
						SI32 siPenalty2 = (100 - ( 30 - skilllevlbybook )*3 );

						//--------------------------------------
						// ����ġ�� �����ش�. 
						//--------------------------------------


						if ( (pclItemManager->GetItemAtb(pclMsg->clItem.siUnique) & ITEMATB_OBJECT) )
						{
                            // �⺻ ����ġ�� ���Ѵ� - ���� ��޿� ���� Ʋ������.
							switch( skillrank )
							{
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:			exp = 450;	break;
							case 6:			exp = 550;	break;
							case 7:			exp = 600;	break;
							case 8:			exp = 600;	break;
							case 9:			exp = 600;	break;
							case 10:		exp = 600;	break;
							case 11:		exp = 600;	break;
							case 12:		exp = 600;	break;
							case 13:		exp = 650;	break;
							case 14:		exp = 700;	break;
							case 15:		exp = 700;	break;
							default:		exp = 0;
							}

							// �г�Ƽ ���
							exp = ( exp * siPenalty * siPenalty2 ) / 10000;

						}
						else
						{
							// ���� ����ġ ���� ���� (������Ʈ�� �ƴҰ��)
							exp	= pclItemManager->GetMakeExpFromItemPrice(pclprice->siPrice * pclMsg->siAddedNum, pclchar->pclCI->clIP.GetLevel()); 
						}*/

						// �Ƿι��� �ý��� ����
						exp = pclchar->CalcTiredPoint( exp );

						if(pclMsg->bNPCMake)
						{
							exp = 0;
						}
						if(exp > 0)
						{
							pclchar->IncreaseExp(exp, GETEXP_REASON_MAKEITEM);
						}


						//------------------------------------
						// ��� ����ġ�� �����ش�. 
						//------------------------------------

						if ( pclClient->IsCountrySwitch(Switch_MakeFoodHealEXP) && ((ITEMTYPE_FOOD == siGetType) || ((ITEMTYPE_HEAL == siGetType))) )
						{
							skillexp = CalcSkillExp_MakeItem_FoodHeal( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum );
						}
						else if ( pclClient->IsCountrySwitch(Switch_MakeItemEXP) )
						{
							skillexp = CalcSkillExp_MakeItem_New( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum );
						}
						else
						{
							skillexp = CalcSkillExp_MakeItem( pclchar, skillunique, pclMsg->clItem.siUnique, pclMsg->siAddedNum, pclprice->siPrice );
						}


						// ��޿� ���� �⺻ ����ġ
/*						if ((pclItemManager->GetItemAtb(pclMsg->clItem.siUnique) & ITEMATB_OBJECT) )
						{


							skillexp = 230;
							if ( skillrank > 5 )
							{
								skillexp = 40;
								for ( SI16 i = 1 ; i < skillrank ; i++)
									skillexp += ( i + 2 )* 10;
							}

							// �г�Ƽ ���
							skillexp = ( skillexp * siPenalty * siPenalty2 ) / 10000;
						}
						else
						{
							// ���� ��� ����ġ ����, ������Ʈ�� �ƴҰ��, �Ϻ����ϰ��
							skillexp = pclItemManager->GetMakeSkillExpFromItemPrice(pclprice->siPrice * pclMsg->siAddedNum, skilllevel); 
						}*/


						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	[��ȣ]			CODE BARRICADE
						//	Description :	NHNCHINA �� �̿��� ������ ��������ġ �ջ� ����� �ٸ��ϴ�.
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						if(pclClient->siServiceArea == ConstServiceArea_NHNChina) // [��ȣ] NHNCHINA�� ����� ��������ġ �ջ�
						{
							SI32 siTimeBonusPercent = 0;
							SI32 siBuffBonusPercent = 0;
							SI32 siPCRoomBonusPercent = 0;

							cltBufInfo * pclMyBuf = &pclchar->pclCI->clBI.clBufInfo;

							// ���� ���ʽ� Ÿ���̸�, 
							if(pclClient->bBonus2TimeSwitch)
							{
								if( bIsGMBonusTime2 && siGMBonusTime2Percent > 0  ) 
									siTimeBonusPercent = siGMBonusTime2Percent ;
								else
									siTimeBonusPercent = 30;
							}
							else if(pclchar->pclCI->clBI.bMakeItemService)
								siTimeBonusPercent = 20;

							else if( pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) )
								siTimeBonusPercent = max( siTimeBonusPercent , pclMyBuf->GetBufPercent(BUF_NOTBONUSTIME_MAKEEXPUP) );

							if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus150_6", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus150_6");
								if(pclEventTime)	{		siTimeBonusPercent = pclEventTime->m_siBonusAmount;		}
							}
							else if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus150_12", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus150_12");
								if(pclEventTime)	{		siTimeBonusPercent = pclEventTime->m_siBonusAmount;		}
							}
							else if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus200_21", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus200_21");
								if(pclEventTime)	{		siTimeBonusPercent = pclEventTime->m_siBonusAmount;		}
							}

							//if( bonusPercent > 0)
							//{
							//	skillexp += (SI32)( skillexp * bonusPercent / 100 );
							//	bonusPercent = 0;
							//}

							if( pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP) )
							{
								// ���ʽ���  ��ø���� ������ �� ���� ȿ���� ��Ÿ����.
								siBuffBonusPercent = max( siBuffBonusPercent , pclMyBuf->GetBufPercent(BUF_MAKEEXPUP) );
							}

							//��� ���� ���̶�� ����ġ�� 100% ���� 
							if( pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) 
								&&  pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) == false )
							{
								// ���ʽ��� �پ���� �ʴ´�.
								siBuffBonusPercent = max( 100 , siBuffBonusPercent) ;
							}
							//���� PC�̰� ���� ���� ���̶�� ����ġ�� 50% ����
							if( pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) 
								&&  pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) == false )
							{
								// ���ʽ��� �پ���� �ʴ´�.
								siBuffBonusPercent = max( 50 , siBuffBonusPercent) ;
							}	
							//���� PC�̰� ����� ���� ���� ���̶�� ����ġ�� �ߺ��ؼ� ����
							if( pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) 
								&&  pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) )
							{
								// ���ʽ��� ��ø�Ǹ� �پ������ �ʴ´�.
								siBuffBonusPercent = max( 150 , siBuffBonusPercent) ;
							}

							if( pclMyBuf->IsHaveBuf(BUF_HINAMOCHI))
							{
								siBuffBonusPercent += 100 ;
							}

							if( pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
							{
								siBuffBonusPercent += 100 ;
							}
							// PCK : ���� �����̾� ������ : ����ġ�� 50% ������Ŵ.
							if ( pclMyBuf->IsHaveBuf(BUF_PREMIUMMAKEEXPUP))
							{
								siBuffBonusPercent += 50;
							}

							// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� �������� ���� �ϼ��� �� �����̸�. ����ġ�� 50% ���� 
							if( pclMyBuf->IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE) )
							{
								siBuffBonusPercent += 50;
							}
							
							if ( pclMyBuf->IsHaveBuf(BUF_VALENTINEDAY))
							{
								siBuffBonusPercent += 20;
							}

							if(pclMyBuf->IsHaveBuf( BUF_PREMIUMMAKEEXPUP)
								&& pclMyBuf->IsHaveBuf( BUF_MAKEEXPUP))
								if(IsCountrySwitch(Switch_Server_Event))
								{
									//���� �̺�Ʈ ���� �Ⱓ�̸�...
									if( pclEventTimeManager->InEventTime("GoonzuDay_Week", &sTime) )
									{
										//[����] ���� �̺�Ʈ �Ϸ� 1�� �����̸� ������ ����ȴ�. => 2008-6-23
										// ���� Ÿ��Ȯ��.
										if( pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_150 || 
											pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_200		)
										{
											// �ߺ��Ұ�.
											if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)  &&
												false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) &&
												false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)  &&
												false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)  &&
												false == pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) &&
												false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
											{
												switch(pclClient->pclServerEventManager->GetBonusBufType())
												{
												case CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_150:
													{
														siBuffBonusPercent += 50 ;
													}
													break;
												case CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_200:
													{
														siBuffBonusPercent += 100 ;
													}
													break;
												}
											}
										}
									}
									else
									{
										//���� �̺�Ʈ ���� �Ⱓ�̸�...
										if( pclEventTimeManager->InEventTime("GoonzuDay_Week_Reward", &sTime) )
										{
											// ��ü �ʿ��� �÷��ش�.
											//if(pclClient->pclServerEventManager->IsEventMap(pclCM->CR[id]->GetMapIndex()))
											{
												// �ߺ��Ұ�.
												if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)  &&
													false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) &&
													false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)  &&
													false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)  &&
													false == pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) &&
													false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
												{
													// ���� 1�� �������Դ� ����ġ�� �ִµ� 
													if(pclClient->pclServerEventManager->IsMyServerRankBest())
													{
														//siBuffBonusPercent += 100;
														siBuffBonusPercent += 50;
													}
													/*else if(pclClient->pclServerEventManager->IsMyServerRankBest2())
													{
														siBuffBonusPercent += 50;
													}*/
												}
											}
										}
									}
								}
								if ( IsCountrySwitch(Switch_We_Are_Family) )		//����ȿ���� ���� ����ġ ����
								{
									if( pclchar->pclFamily != NULL )
									{
										if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_PARANTS)	// �θ��ϋ�.
										{
											if ( pclchar->pclFamily->GetOnChildrenNum() > 0 )	// �ڽ��ɸ��Ͱ� 1�� �̻� ���� �ؾ� �Ѵ�.
											{
												SI32 siAddValue = 0		;//	 ������ �ۼ�Ʈ 
												SYSTEMTIME stFamilyEffectTime_Now	;
												// ���� �̿�� �Ⱓ�� ���� �ڽ� ���ڸ� ã�´�.
												for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++)
												{
													if( pclchar->pclFamily->GetChildPersonID(siSlot) > 0 )
													{
														ZeroMemory( &stFamilyEffectTime_Now ,sizeof( SYSTEMTIME ))	;
														stFamilyEffectTime_Now	= pclchar->pclFamily->GetChild_Add_Date( siSlot ) ;

														if ( stFamilyEffectTime_Now.wMonth > 0 && stFamilyEffectTime_Now.wMonth <= MAX_MONTH_FAMILY	&& 
															stFamilyEffectTime_Now.wDay > 0 && stFamilyEffectTime_Now.wDay <= MAX_DAY_FOR_FAMILY)
														{
															if ( sTime.wMonth > 0 && sTime.wMonth <= MAX_MONTH_FAMILY && sTime.wDay > 0 && sTime.wDay <= MAX_DAY_FOR_FAMILY  )
															{
																SI64 servertime = GetTimeValue(&sTime )	;
																SI64 limittime = GetTimeValue(&stFamilyEffectTime_Now )	;

																if ( servertime < limittime )
																{
																	siAddValue++;
																}

															}
														}
													}
												}
												if ( 10 <= siAddValue )
												{
													siAddValue = MAX_FAMILY_ADD_EXP	;	// �ִ�� 10%
												}
												siBuffBonusPercent += siAddValue;	// ���� ����ġ ���� persent
												siAddValue	=	0	;	// �����ϰ�� �ʱ�ȭ 
											}
										}
									}
								}

								//if( siBuffBonusPercent > 0)
								//{
								//	skillexp += (SI32)( skillexp * siBuffBonusPercent / 100 );
								//	siBuffBonusPercent = 0;
								//}

								// ������ ���� �����Ǵ� ����ġ
								//skillexp = pclchar->pclCI->clBI.clBufInfo.CalcTotalBufValue( BUF_MAKEEXPUP, skillexp );

								// �����Ǽ��� ���� ����ġ�� ����Ѵ�. 
								SI32 para	= 0;

								switch(skillunique)
								{
								case SKILL_MAKESWORD1:	para	= GONGZO_SKILL_SWORD;	break;
								case SKILL_MAKESPEAR1:	para	= GONGZO_SKILL_SPEAR;	break;
								case SKILL_MAKESTAFF1:	para	= GONGZO_SKILL_STAFF;	break;
								case SKILL_MAKEAXE1:	para	= GONGZO_SKILL_AXE;		break;
								case SKILL_MAKEBOW1:	para	= GONGZO_SKILL_BOW;		break;
								case SKILL_MAKEGUN1:	para	= GONGZO_SKILL_GUN;		break;

								case SKILL_MAKEHELMET1:	para	= GONGZO_SKILL_HELMET;	break;
								case SKILL_MAKESHOES1:	para	= GONGZO_SKILL_SHOES;	break;
								case SKILL_MAKEBELT1:	para	= GONGZO_SKILL_BELT;	break;
								case SKILL_MAKEARMOUR1:	para	= GONGZO_SKILL_ARMOR;	break;
								}
								if(para)
								{
									CMinisterGongzo* pclminister = (CMinisterGongzo*)pclMinisterMgr->GetMinister(MINISTER_GONGZO);
									SI32 value = pclminister->GetGongzoSkillValue(para);

									// ���� ���� �ּҰ� 1. ������������ �����ÿ� 1�� �ٲپ�� ��
									skillexp = max(0, skillexp + (skillexp * value / 100)) ;
								}

								// [����] PC�� �����̾� ��ȭ (���� ����ġ 50%�߰�) - 2008.03.02
								if ( pclchar->pclCI->clBI.bPCRoom == true )
									siPCRoomBonusPercent = 50;


								// ���� ����ġ ���ջ�
								//skillexp += (SI32)( skillexp * ((siTimeBonusPercent + siBuffBonusPercent + siPCRoomBonusPercent) / 100));
								skillexp += (SI32)(( skillexp * (siTimeBonusPercent + siBuffBonusPercent + siPCRoomBonusPercent)) / 100);

								if( pclMsg->bNPCMake )
								{
									skillexp = 0;
								}

								// �Ƿι��� �ý��� ����
								skillexp = pclchar->CalcTiredPoint( skillexp );

								if(skillexp)
								{
									pclchar->SetSkillUpdate(skillunique, skillexp);

									// ���Ե� ������ �ִٸ� DB�� ������ ������
									if( pclchar->pclCI->clBI.siHomeVillage > 0)
									{
										sDBRequest_VillageJoinMakeItem clMsg2( pclchar->pclCI->GetPersonID(), skillexp / 100, pclchar->pclCI->clBI.siHomeVillage);
										SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);

										//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
										//{
										//	// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ �ִ°�� ������ ���� ��ų ����.
										//	// param1 == ��ų ����ġ.
										//	cltServer * pclServer = (cltServer*)pclClient;
										//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_MAKE_ITEM_SKILL_EXP, 
										//									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										//									skillexp / 100, 0, 0, 0, 0, NULL, NULL);
										//}
									}

									//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
									NDate Today;
									Today.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );

									if ( Today.GetDateVary() >= clValentineEventStart.GetDateVary() &&
										Today.GetDateVary() <= clValentineEventEnd.GetDateVary() )
									{	
										// �ִ� siValentineItem% �ּ� 1% �� Ȯ���� �̺�Ʈ �������� �ش�
										SI32 itemGetPercent = min( siValentineItem , max( 1 , skillexp / 10 ) )  ;								
										SI32 randValue = rand()%100;

										if( itemGetPercent > randValue )
										{
											SI32 itemType = pclItemManager->pclItemInfo[ref]->clItem.GetType(pclItemManager);

											SI32 eventItemUnique = 0;

											//KHY - 1223  �Ϻ� ����.
											if( itemType == ITEMTYPE_ARMOUR || itemType == ITEMTYPE_AXE || itemType == ITEMTYPE_BELT 
												|| itemType == ITEMTYPE_BOW || itemType == ITEMTYPE_GUN || itemType == ITEMTYPE_HELMET 
												|| itemType == ITEMTYPE_SHOES || itemType == ITEMTYPE_SPEAR|| itemType == ITEMTYPE_STAFF
												|| itemType == ITEMTYPE_SWORD 
												|| itemType == ITEMTYPE_BOOK || itemType == ITEMTYPE_DISH || itemType == ITEMTYPE_FISHINGROD
												|| itemType == ITEMTYPE_FOOD || itemType == ITEMTYPE_HEAL || itemType == ITEMTYPE_IRON )
											{
												SI16 randval = rand()%100;
												if(randval > 50)
													eventItemUnique = ITEMUNIQUE(13007); //Aī��.
												else
													eventItemUnique = ITEMUNIQUE(13012); //I ī��.
											}

											pclchar->GiveItem( eventItemUnique ,  1 , INPUTITEMPERSON_OPTION_WAR ,0);

										}

									}

									//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
									if ( Today.GetDateVary() >= clWhiteEventStart.GetDateVary() &&
										Today.GetDateVary() <= clWhiteEventEnd.GetDateVary() )
									{	
										// �ִ� siValentineItem% �ּ� 1% �� Ȯ���� �̺�Ʈ �������� �ش�
										SI32 itemGetPercent = min( siWhiteItem , max( 1 , skillexp / 10 ) )  ;								
										SI32 randValue = rand()%100;

										if( itemGetPercent > randValue )
										{
											SI32 itemType = pclItemManager->pclItemInfo[ref]->clItem.GetType(pclItemManager);

											SI32 eventItemUnique = 0;

											if( itemType == ITEMTYPE_ARMOUR || itemType == ITEMTYPE_AXE || itemType == ITEMTYPE_BELT 
												|| itemType == ITEMTYPE_BOW || itemType == ITEMTYPE_GUN || itemType == ITEMTYPE_HELMET 
												|| itemType == ITEMTYPE_SHOES || itemType == ITEMTYPE_SPEAR|| itemType == ITEMTYPE_STAFF
												|| itemType == ITEMTYPE_SWORD )
											{
												eventItemUnique = ITEMUNIQUE(13017); //H ī��.
											}
											else if( itemType == ITEMTYPE_BOOK || itemType == ITEMTYPE_DISH || itemType == ITEMTYPE_FISHINGROD 
												|| itemType == ITEMTYPE_FOOD || itemType == ITEMTYPE_HEAL || itemType == ITEMTYPE_IRON )
											{
												eventItemUnique = ITEMUNIQUE(13017); //H ī��.
											}

											pclchar->GiveItem( eventItemUnique ,  1 , INPUTITEMPERSON_OPTION_WAR ,0);

										}

									}							
									////////////////////////////////////////////////////////////////////////////////////////////////////

									// ��� ����ġ�� ū ��� ��Ͽ� �����. 
									if(skillexp >= 3000)
									{
										pclLog->FilePrint(TEXT("Config\\SkillExp.log"), TEXT("Name:%s Exp:%d Item:%d Num:%d Item2:%d Result:%d"), 
											pclchar->GetName(), skillexp, pclMsg->clItem.siUnique, pclMsg->siAddedNum,
											pclMsg->siItemUnique, pclMsg->siResult);

									}
								}
						}
						else		// [��ȣ] NHNCHINA�� �ƴѰ���� ��������ġ �ջ�
						{
							SI32 bonusPercent = 0;
							cltBufInfo * pclMyBuf = &pclchar->pclCI->clBI.clBufInfo;

							// ���� ���ʽ� Ÿ���̸�, 
							if(pclClient->bBonus2TimeSwitch)
							{
								if( bIsGMBonusTime2 && siGMBonusTime2Percent > 0  ) 
								{
									bonusPercent = siGMBonusTime2Percent ;
								}
								else
								{
									if ( pclClient->siServiceArea == ConstServiceArea_English )
									{
										bonusPercent = 30;
									}
									else if ( pclClient->siServiceArea == ConstServiceArea_Japan )
									{
										bonusPercent = 20;
									}
									else if ( pclClient->siServiceArea == ConstServiceArea_NHNChina )
									{
										bonusPercent = 30;
									}
									//LEEKH - 0810 - ����S ��������ġ ����(+50%)
									else if ( pclClient->siServiceArea == ConstServiceArea_Korea)
									{
										bonusPercent = 50;
									}
									else if ( pclClient->siServiceArea == ConstServiceArea_USA)
									{
										// �̱� �ӽ� �߰� - ���� ���ʽ� Ÿ���� 130%
										if(bBonusTimeGoonzu)
										{
											bonusPercent = 30;

											if(true == bAlldayBonus)
												bonusPercent = 100;
										}
										else
										{
											bonusPercent = 100;
										}
									}
									else if ( pclClient->siServiceArea == ConstServiceArea_EUROPE )
									{
										bonusPercent = 30;
									}
									else
									{
										bonusPercent = 100;
									}

								}

							}
							else if(pclchar->pclCI->clBI.bMakeItemService)
							{
								bonusPercent = 20;
							}
							else if( pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) )
							{
								bonusPercent = max( bonusPercent , pclMyBuf->GetBufPercent(BUF_NOTBONUSTIME_MAKEEXPUP) );
							}

							if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus150_6", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus150_6");
								if(pclEventTime)	{		bonusPercent = pclEventTime->m_siBonusAmount;		}
							}
							else if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus150_12", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus150_12");
								if(pclEventTime)	{		bonusPercent = pclEventTime->m_siBonusAmount;		}
							}
							else if(pclEventTimeManager->InEventTime("GoonzuDay_MakeExpBonus200_21", &sTime))
							{
								cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_MakeExpBonus200_21");
								if(pclEventTime)	{		bonusPercent = pclEventTime->m_siBonusAmount;		}
							}

							if( bonusPercent > 0)
							{
								skillexp += (SI32)( skillexp * bonusPercent / 100 );
								bonusPercent = 0;
							}

							if( pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP) )
							{
								// ���ʽ���  ��ø���� ������ �� ���� ȿ���� ��Ÿ����.
								bonusPercent = max( bonusPercent , pclMyBuf->GetBufPercent(BUF_MAKEEXPUP) );
							}

							//��� ���� ���̶�� ����ġ�� 100% ���� 
							if( pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) 
								&&  pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) == false )
							{
								// ���ʽ��� �پ���� �ʴ´�.
								bonusPercent = max( 100 , bonusPercent) ;
							}
							//���� PC�̰� ���� ���� ���̶�� ����ġ�� 50% ����
							if( pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) 
								&&  pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) == false )
							{
								// ���ʽ��� �پ���� �ʴ´�.
								bonusPercent = max( 50 , bonusPercent) ;
							}	
							//���� PC�̰� ����� ���� ���� ���̶�� ����ġ�� �ߺ��ؼ� ����
							if( pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) 
								&&  pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) )
							{
								// ���ʽ��� ��ø�Ǹ� �پ������ �ʴ´�.
								bonusPercent = max( 150 , bonusPercent) ;
							}

							if( pclMyBuf->IsHaveBuf(BUF_HINAMOCHI))
							{
								bonusPercent += 100 ;
							}

							if( pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
							{
								bonusPercent += 100 ;
							}
							// PCK : ���� �����̾� ������ : ����ġ�� 50% ������Ŵ.
							if ( pclMyBuf->IsHaveBuf(BUF_PREMIUMMAKEEXPUP))
							{
								bonusPercent += 50;
							}

							// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� �������� ���� �ϼ��� �� �����̸�. ����ġ�� 50% ���� 
							if( pclMyBuf->IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE) )
							{
								bonusPercent += 50;
							}

							if ( pclMyBuf->IsHaveBuf(BUF_VALENTINEDAY))
							{
								bonusPercent += 20;
							}

							// [���] ũ�������� �̺�Ʈ - ���縮�� �տ� ũ�������� Ʈ���� �������� 1�ܰ� : 5%, 2�ܰ� : 10%�� ����ġ ���� ȿ���� �޴´�.
							if((pclClient->pclEventTimeManager->InEventTime( TEXT("ChristmasEvent"), &sTime) == true))
							{
								cltServer* pclserver = (cltServer*)pclClient;

								SI32	siWorldChristmasTree01Kind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE01"));
								SI32	siWorldChristmasTree02Kind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE02"));

								SI32 siWorldChristmasTree01ID = pclserver->siWorldTreeID[0];
								SI32 siWorldChristmasTree02ID = pclserver->siWorldTreeID[1];

								cltCharServer*	pclWorldChristmasTreeChar01 = (cltCharServer*)pclClient->pclCM->CR[siWorldChristmasTree01ID];
								cltCharServer*	pclWorldChristmasTreeChar02 = (cltCharServer*)pclClient->pclCM->CR[siWorldChristmasTree02ID];

								if(pclWorldChristmasTreeChar01)
								{
									if((pclWorldChristmasTreeChar01->GetMapIndex() == MAPINDEX_MAINFIELD) && (pclWorldChristmasTreeChar01->GetKind() == siWorldChristmasTree01Kind))
									{
										bonusPercent += 5;
									}
								}

								if(pclWorldChristmasTreeChar02)
								{
									if((pclWorldChristmasTreeChar02->GetMapIndex() == MAPINDEX_MAINFIELD) && (pclWorldChristmasTreeChar02->GetKind() == siWorldChristmasTree02Kind))
									{
										bonusPercent += 10;
									}
								}
							}

							if(pclMyBuf->IsHaveBuf( BUF_PREMIUMMAKEEXPUP) && pclMyBuf->IsHaveBuf( BUF_MAKEEXPUP))
								if(IsCountrySwitch(Switch_Server_Event))
								{
									//���� �̺�Ʈ ���� �Ⱓ�̸�...
									if( pclEventTimeManager->InEventTime("GoonzuDay_Week", &sTime) )
									{
										//[����] ���� �̺�Ʈ �Ϸ� 1�� �����̸� ������ ����ȴ�. => 2008-6-23
										// ���� Ÿ��Ȯ��.
										if( pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_150 || 
											pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_200		)
										{
											// �ߺ��Ұ�.
											if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)  &&
												false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) &&
												false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)  &&
												false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)  &&
												false == pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) &&
												false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
											{
												switch(pclClient->pclServerEventManager->GetBonusBufType())
												{
												case CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_150:
													{
														bonusPercent += 50 ;
													}
													break;
												case CNServerEvent_Manager::SERVER_EVENT_BUF_MAKE_EXP_200:
													{
														bonusPercent += 100 ;
													}
													break;
												}
											}
										}
									}
									else
									{
										//���� �̺�Ʈ ���� �Ⱓ�̸�...
										if( pclEventTimeManager->InEventTime("GoonzuDay_Week_Reward", &sTime) )
										{
											// ��ü �ʿ��� �÷��ش�.
											//if(pclClient->pclServerEventManager->IsEventMap(pclCM->CR[id]->GetMapIndex()))
											{
												// �ߺ��Ұ�.
												if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)  &&
													false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) &&
													false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)  &&
													false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)  &&
													false == pclMyBuf->IsHaveBuf(BUF_NOTBONUSTIME_MAKEEXPUP) &&
													false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
												{
													// ���� 1�� �������Դ� ����ġ�� �ִµ� 
													if(pclClient->pclServerEventManager->IsMyServerRankBest())
													{
														//bonusPercent += 100;
														bonusPercent += 50;
													}
													/*else if(pclClient->pclServerEventManager->IsMyServerRankBest2())
													{
														bonusPercent += 50;
													}*/
												}
											}
										}
									}
								}
								if ( IsCountrySwitch(Switch_We_Are_Family) )		//����ȿ���� ���� ����ġ ����
								{
									if( pclchar->pclFamily != NULL )
									{
										if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_PARANTS)	// �θ��ϋ�.
										{
											if ( pclchar->pclFamily->GetOnChildrenNum() > 0 )	// �ڽ��ɸ��Ͱ� 1�� �̻� ���� �ؾ� �Ѵ�.
											{
												SI32 siAddValue = 0		;//	 ������ �ۼ�Ʈ 
												SYSTEMTIME stFamilyEffectTime_Now	;
												// ���� �̿�� �Ⱓ�� ���� �ڽ� ���ڸ� ã�´�.
												for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++)
												{
													if( pclchar->pclFamily->GetChildPersonID(siSlot) > 0 )
													{
														ZeroMemory( &stFamilyEffectTime_Now ,sizeof( SYSTEMTIME ))	;
														stFamilyEffectTime_Now	= pclchar->pclFamily->GetChild_Add_Date( siSlot ) ;

														if ( stFamilyEffectTime_Now.wMonth > 0 && stFamilyEffectTime_Now.wMonth <= MAX_MONTH_FAMILY	&& 
															stFamilyEffectTime_Now.wDay > 0 && stFamilyEffectTime_Now.wDay <= MAX_DAY_FOR_FAMILY)
														{
															if ( sTime.wMonth > 0 && sTime.wMonth <= MAX_MONTH_FAMILY && sTime.wDay > 0 && sTime.wDay <= MAX_DAY_FOR_FAMILY  )
															{
																SI64 servertime = GetTimeValue(&sTime )	;
																SI64 limittime = GetTimeValue(&stFamilyEffectTime_Now )	;

																if ( servertime < limittime )
																{
																	siAddValue++;
																}

															}
														}
													}
												}
												if ( 10 <= siAddValue )
												{
													siAddValue = MAX_FAMILY_ADD_EXP	;	// �ִ�� 10%
												}
												bonusPercent += siAddValue;	// ���� ����ġ ���� persent
												siAddValue	=	0	;	// �����ϰ�� �ʱ�ȭ 
											}
										}
									}
								}

								if( bonusPercent > 0)
								{
									skillexp += (SI32)( skillexp * bonusPercent / 100 );
									bonusPercent = 0;
								}

								// ������ ���� �����Ǵ� ����ġ
								//skillexp = pclchar->pclCI->clBI.clBufInfo.CalcTotalBufValue( BUF_MAKEEXPUP, skillexp );

								// �����Ǽ��� ���� ����ġ�� ����Ѵ�. 
								SI32 para	= 0;

								switch(skillunique)
								{
								case SKILL_MAKESWORD1:	para	= GONGZO_SKILL_SWORD;	break;
								case SKILL_MAKESPEAR1:	para	= GONGZO_SKILL_SPEAR;	break;
								case SKILL_MAKESTAFF1:	para	= GONGZO_SKILL_STAFF;	break;
								case SKILL_MAKEAXE1:	para	= GONGZO_SKILL_AXE;		break;
								case SKILL_MAKEBOW1:	para	= GONGZO_SKILL_BOW;		break;
								case SKILL_MAKEGUN1:	para	= GONGZO_SKILL_GUN;		break;

								case SKILL_MAKEHELMET1:	para	= GONGZO_SKILL_HELMET;	break;
								case SKILL_MAKESHOES1:	para	= GONGZO_SKILL_SHOES;	break;
								case SKILL_MAKEBELT1:	para	= GONGZO_SKILL_BELT;	break;
								case SKILL_MAKEARMOUR1:	para	= GONGZO_SKILL_ARMOR;	break;
								}
								if(para)
								{
									CMinisterGongzo* pclminister = (CMinisterGongzo*)pclMinisterMgr->GetMinister(MINISTER_GONGZO);
									SI32 value = pclminister->GetGongzoSkillValue(para);

									// ���� ���� �ּҰ� 1. ������������ �����ÿ� 1�� �ٲپ�� ��
									skillexp = max(0, skillexp + (skillexp * value / 100)) ;
								}

								// [����] PC�� �����̾� ��ȭ (���� ����ġ 50%�߰�) - 2008.03.02
								if ( pclchar->pclCI->clBI.bPCRoom == true )
								{
									SI32 siPCRoomBonusPercent = 50;
									skillexp += (SI32)( skillexp * siPCRoomBonusPercent / 100 );
								}

								if( pclMsg->bNPCMake )
								{
									skillexp = 0;
								}

								// �Ƿι��� �ý��� ����
								skillexp = pclchar->CalcTiredPoint( skillexp );

								if(skillexp)
								{
									pclchar->SetSkillUpdate(skillunique, skillexp);

									// ���Ե� ������ �ִٸ� DB�� ������ ������
									if( pclchar->pclCI->clBI.siHomeVillage > 0)
									{
										sDBRequest_VillageJoinMakeItem clMsg2( pclchar->pclCI->GetPersonID(), skillexp / 100, pclchar->pclCI->clBI.siHomeVillage);
										SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);

										//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
										//{
										//	// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ �ִ°�� ������ ���� ��ų ����.
										//	// param1 == ��ų ����ġ.
										//	cltServer * pclServer = (cltServer*)pclClient;
										//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_MAKE_ITEM_SKILL_EXP, 
										//									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										//									skillexp / 100, 0, 0, 0, 0, NULL, NULL);
										//}
									}

									//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
									NDate Today;
									Today.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );

									if ( Today.GetDateVary() >= clValentineEventStart.GetDateVary() &&
										Today.GetDateVary() <= clValentineEventEnd.GetDateVary() )
									{	
										// �ִ� siValentineItem% �ּ� 1% �� Ȯ���� �̺�Ʈ �������� �ش�
										SI32 itemGetPercent = min( siValentineItem , max( 1 , skillexp / 10 ) )  ;								
										SI32 randValue = rand()%100;

										if( itemGetPercent > randValue )
										{
											SI32 itemType = pclItemManager->pclItemInfo[ref]->clItem.GetType(pclItemManager);

											SI32 eventItemUnique = 0;

											//KHY - 1223  �Ϻ� ����.
											if( itemType == ITEMTYPE_ARMOUR || itemType == ITEMTYPE_AXE || itemType == ITEMTYPE_BELT 
												|| itemType == ITEMTYPE_BOW || itemType == ITEMTYPE_GUN || itemType == ITEMTYPE_HELMET 
												|| itemType == ITEMTYPE_SHOES || itemType == ITEMTYPE_SPEAR|| itemType == ITEMTYPE_STAFF
												|| itemType == ITEMTYPE_SWORD 
												|| itemType == ITEMTYPE_BOOK || itemType == ITEMTYPE_DISH || itemType == ITEMTYPE_FISHINGROD
												|| itemType == ITEMTYPE_FOOD || itemType == ITEMTYPE_HEAL || itemType == ITEMTYPE_IRON 
												|| itemType == ITEMTYPE_AVATAR_MANTLE || itemType == ITEMTYPE_AVATAR_DRESS || itemType == ITEMTYPE_AVATAR_HAT
												|| itemType == ITEMTYPE_AVATAR_NECK || itemType == ITEMTYPE_AVATAR_RING || itemType == ITEMTYPE_CRYSTAL
												)
											{
												SI16 randval = rand()%100;
												if(randval > 50)
													eventItemUnique = ITEMUNIQUE(13007); //Aī��.
												else
													eventItemUnique = ITEMUNIQUE(13012); //I ī��.
											}

											pclchar->GiveItem( eventItemUnique ,  1 , INPUTITEMPERSON_OPTION_WAR ,0);

										}

									}

									//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
									if ( Today.GetDateVary() >= clWhiteEventStart.GetDateVary() &&
										Today.GetDateVary() <= clWhiteEventEnd.GetDateVary() )
									{	
										// �ִ� siValentineItem% �ּ� 1% �� Ȯ���� �̺�Ʈ �������� �ش�
										SI32 itemGetPercent = min( siWhiteItem , max( 1 , skillexp / 10 ) )  ;								
										SI32 randValue = rand()%100;

										if( itemGetPercent > randValue )
										{
											SI32 itemType = pclItemManager->pclItemInfo[ref]->clItem.GetType(pclItemManager);

											SI32 eventItemUnique = 0;

											if( itemType == ITEMTYPE_ARMOUR || itemType == ITEMTYPE_AXE || itemType == ITEMTYPE_BELT 
												|| itemType == ITEMTYPE_BOW || itemType == ITEMTYPE_GUN || itemType == ITEMTYPE_HELMET 
												|| itemType == ITEMTYPE_SHOES || itemType == ITEMTYPE_SPEAR|| itemType == ITEMTYPE_STAFF
												|| itemType == ITEMTYPE_SWORD )
											{
												eventItemUnique = ITEMUNIQUE(13017); //H ī��.
											}
											else if( itemType == ITEMTYPE_BOOK || itemType == ITEMTYPE_DISH || itemType == ITEMTYPE_FISHINGROD 
												|| itemType == ITEMTYPE_FOOD || itemType == ITEMTYPE_HEAL || itemType == ITEMTYPE_IRON )
											{
												eventItemUnique = ITEMUNIQUE(13017); //H ī��.
											}

											pclchar->GiveItem( eventItemUnique ,  1 , INPUTITEMPERSON_OPTION_WAR ,0);

										}

									}							
									////////////////////////////////////////////////////////////////////////////////////////////////////

									// ��� ����ġ�� ū ��� ��Ͽ� �����. 
									if(skillexp >= 3000)
									{
										pclLog->FilePrint(TEXT("Config\\SkillExp.log"), TEXT("Name:%s Exp:%d Item:%d Num:%d Item2:%d Result:%d"), 
											pclchar->GetName(), skillexp, pclMsg->clItem.siUnique, pclMsg->siAddedNum,
											pclMsg->siItemUnique, pclMsg->siResult);

									}
								}
						}
					}
				}
			}
		}

		{
			// ��ǰ ���� ����� �뺸�Ѵ�. 
			cltItem clmadeitem;
			clmadeitem.Set(&pclMsg->clItem);
			clmadeitem.SetItemNum(pclMsg->siAddedNum);

			cltGameMsgResponse_MakeItemDlg clinfo(&clmadeitem, exp, skillunique, skillexp,pclchar->siMonsterCorp);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMDLG, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			pclchar->siMonsterCorp = 0 ;
			pclchar->dwStartMiniGameTime = 0;
		}



		//---------------------------------------
		// �κ��� ������ Ŭ���̾�Ʈ���� �����ش�. 
		//----------------------------------------
		if(pclMsg->bAlmostFailSwitch == true)
		{
			if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
			{
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_MAKEALMOSTFAIL, pclMsg->siAddedNum, exp, &pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos], 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		else
		{
			if(pclMsg->siLuckQuality)
			{
				if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
				{
					cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_MAKELUCK, pclMsg->siAddedNum, exp, &pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos], 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			else
			{
				if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
				{
					cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_MAKE, pclMsg->siAddedNum, exp, &pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos], 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		// �����ڿ� �ֹ����� �������� ������Ʈ �Ѵ�. 
		if(pclMsg->siFee)
		{
			{
				pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siPersonIDMoney);

				// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
				cltGameMsgResponse_ChangeMoney clinfo(pclCM->CR[id]->pclCI->clIP.GetMoney(),0, CHANGE_MONEY_REASON_MAKE);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}

			{
				pclMaterialChar->pclCI->clIP.SetMoney(pclMsg->siMaterialPersonIDMoney);

				// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
				cltGameMsgResponse_ChangeMoney clinfo(pclMaterialChar->pclCI->clIP.GetMoney(),0, CHANGE_MONEY_REASON_MAKE);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
				pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
			}

		}
		//---------------------------------------
		// ��ǰ ����� ����Ʈ �������̾����� Ȯ���Ͽ� ��ġ�Ѵ�. 
		//---------------------------------------

		// ��ǰ�� �����  ����Ʈ�� �������̾��� ?
		// ���� ��ǰ ���� ������Ų��. 
		((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_MAKEITEM, pclMsg->clItem.siUnique, pclMsg->siAddedNum);

		((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_TUTORIALMAKEITEM, pclMsg->clItem.siUnique, pclMsg->siAddedNum);

		// Para1 ������ �������� Para2��ŭ ����� ����Ʈ���
		SI32 siConditionLevel = pclItemManager->pclItemInfo[ref]->clCondition.siLevel;
		((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_MAKELEVELITEM, siConditionLevel, pclMsg->siAddedNum);
		((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_TUTORIALMAKELEVELITEM, siConditionLevel, pclMsg->siAddedNum);		

		SI32 itemType = pclItemManager->pclItemInfo[ref]->clItem.GetType(pclItemManager);

		if( itemType == ITEMTYPE_BOOK )
		{
			((cltCharServer*)(pclCM->CR[id]))->DoQuestCheckAndAction(QUEST_CLEAR_COND_MAKEBOOK);
			if ( pclItemManager->pclItemInfo[ref]->GetSkillLevelLimit() == 20 )
			{
				((cltCharServer*)(pclCM->CR[id]))->DoQuestCheckAndAction(QUEST_CLEAR_COND_MAKEINTBOOK);
			}
		}

		CNServerEvent_Quest*	pclSE_Quest		= NULL;
		SI32					siMakeAmount	= max( pclMsg->siAddedNum, ((cltCharServer*)(pclCM->CR[id]))->siQuestCount );
		// [����] ���� �̺�Ʈ ����Ʈ : ���� ���� ���� ������ �����
		if ( IsCountrySwitch(Switch_Server_Event) )
		{
			pclSE_Quest = (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();

			if ( pclSE_Quest )
			{
				pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_MAKELEVELITEM, siConditionLevel, siMakeAmount );
			}
		}

		SI32 siCrystalGrade = pclMsg->clItem.GetCrystalGrade();
		if ( siCrystalGrade )
		{
			((cltCharServer*)(pclCM->CR[id]))->IncQuestPara( QUEST_CLEAR_COND_MAKECRYSTAL, siCrystalGrade, siMakeAmount );
		}

		cltServer* pclserver			= (cltServer*)pclClient;
		//������ ���鶧 ���ϸ� ����Ʈ3 �������� ����ũ�� Ȯ�� �Ѵ�.
		if(pclchar->pclCI->clDailyQuest3Info.siItemUnique == pclMsg->clItem.siUnique )
		{
			//	���� ����Ʈ �϶��� �����ؼ� ���� Ÿ���� �޾ƿ� ���� ����.
			UI32 raretype;
			// �ش� ����Ʈ �������� ������ ���� �Ѵ�.			
			//// �ű� �϶�.
			//if ( RARELEVEL_3 ==pclchar->pclCI->clDailyQuest3Info.siMakedeItemNum + pclMsg->clItem.GetRareType() ){
			//}
			//	���� ������Ʈ�� ���� ���ϸ� ����Ʈ 3���� ���� �Ѵ�.
			if ( pclchar->pclCI->clDailyQuest3Info.bHiddenQuest == true )	//	���� ����Ʈ
			{
				raretype = pclMsg->clItem.GetRareType();
				if (raretype == RARELEVEL_5) { // �ű��϶�.
					pclchar->pclCI->clDailyQuest3Info.siMadeItemNum = pclchar->pclCI->clDailyQuest3Info.siMadeItemNum + pclMsg->clItem.siItemNum;
					if (pclchar->pclCI->clDailyQuest3Info.siMadeItemNum >= pclchar->pclCI->clDailyQuest3Info.siItemNum)
					{
						SI32 value = 100;
						cltItem clItem;
						clItem.siUnique = pclchar->pclCI->clDailyQuest3Info.siRewardItemUnique;
						clItem.siItemNum = ( pclchar->pclCI->clDailyQuest3Info.siRewardItemNum * value ) / 100;
						cltItem clToItem;
						clToItem.Init();

						SI16 InvPos = -1;
						SI32 rtnvalue;
						GMONEY money = 0 ;
						//������ �ٶ� �̺��丮�� �����ִ��� Ȯ�� �ؼ� ������ �ش�
						if ( pclchar->CanAddInv(INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
						{
							sDBRequest_DailyQuest3Del clMsg( pclchar->pclCI->GetPersonID(), id, true, InvPos, 
								pclchar->pclCI->clDailyQuest3Info.siItemUnique,&clItem, 1, money, pclchar->pclCI->clDailyQuest3Info.bHiddenQuest );
							pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}
						else
						{
							// �κ� �� ���� �ȵǹǷ�...
							pclserver->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  1, 0, pclchar->GetCharUnique());

							// ���� ���¸� Ŭ���̾�Ʈ�� ����
							cltGameMsgResponse_DailyQuest3Change clinfo( pclchar->pclCI->clDailyQuest3Info.siLeftTime, pclchar->pclCI->clDailyQuest3Info.siMadeItemNum, pclchar->pclCI->clDailyQuest3Info.bHiddenQuest );
							cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
							pclchar->SendNetMsg((sPacketHeader*)&clMsg);	
						}
					}
				}
			}
			else	//	���� ����Ʈ�� �ƴ� �Ϲ� ���ϸ� ����Ʈ3
			{
				pclchar->pclCI->clDailyQuest3Info.siMadeItemNum = pclchar->pclCI->clDailyQuest3Info.siMadeItemNum + pclMsg->clItem.siItemNum;
				if (pclchar->pclCI->clDailyQuest3Info.siMadeItemNum >= pclchar->pclCI->clDailyQuest3Info.siItemNum) 
				{
					SI32 value = 100;

					cltItem clItem;
					clItem.siUnique = pclchar->pclCI->clDailyQuest3Info.siRewardItemUnique;
					clItem.siItemNum = ( pclchar->pclCI->clDailyQuest3Info.siRewardItemNum * value ) / 100;
					cltItem clToItem;
					clToItem.Init();

					SI16 InvPos = -1;
					SI32 rtnvalue;
					GMONEY money = 0 ;
					// ������ �ش�.
					if ( pclchar->CanAddInv(INVMODE_ALL, &clItem, &InvPos, &clToItem, &rtnvalue) )
					{
						sDBRequest_DailyQuest3Del clMsg( pclchar->pclCI->GetPersonID(), id, true, InvPos, 
							pclchar->pclCI->clDailyQuest3Info.siItemUnique,&clItem, 1, money, pclchar->pclCI->clDailyQuest3Info.bHiddenQuest );
						pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
					else
					{
						// �κ� �� ���� �ȵǹǷ�...
						pclserver->SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  1, 0, pclchar->GetCharUnique());

						// ���� ���¸� Ŭ���̾�Ʈ�� ����
						cltGameMsgResponse_DailyQuest3Change clinfo( pclchar->pclCI->clDailyQuest3Info.siLeftTime, pclchar->pclCI->clDailyQuest3Info.siMadeItemNum, pclchar->pclCI->clDailyQuest3Info.bHiddenQuest );
						cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
						pclchar->SendNetMsg((sPacketHeader*)&clMsg);	
					}
				}
				else	// ����Ʈ�� �Ϸ���� �ʾ����Ƿ� 
				{		// DB �� ������Ʈ ������ �ʰ�, �������� �ٷ� �˷���.
					cltGameMsgResponse_DailyQuest3Change clinfo( pclchar->pclCI->clDailyQuest3Info.siLeftTime, pclchar->pclCI->clDailyQuest3Info.siMadeItemNum, pclchar->pclCI->clDailyQuest3Info.bHiddenQuest );
					cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);	
				}
			}
		}


		// [����] ��������� ����� ����Ʈ Ŭ���� ����� �߰� : 2008.02.14
		if ( (pclMsg->clItem.GetRareType() == RARELEVEL_1)		// ��ǰ
			|| (pclMsg->clItem.GetRareType() == RARELEVEL_2)	// ȣǰ
			|| (pclMsg->clItem.GetRareType() == RARELEVEL_5)	// �ű�
		)
		{
			((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_MAKE_RAREITEM, pclMsg->clItem.siUnique, pclMsg->siAddedNum);

			// [����] �̺�Ʈ ����Ʈ : �ű��̻� ��ǰ �����
			if ( IsCountrySwitch(Switch_Server_Event) )
			{
				if ( pclSE_Quest )
				{
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_MAKERAREITEM, 0, siMakeAmount );
				}
			}

		}

		// ��Ƽ����Ʈ
		if(IsCountrySwitch(Switch_PartyQuest_PartyMatching))
		{
			// ��Ƽ�� ���� �÷��̾ ��Ƽ����Ʈ ������ ���� �մϴ�.
			if(pclchar->siPartyIndex > 0)
			{
				pclserver->m_pPartyQuestMgr->UpdatePartyQuest(pclchar->GetID() ,pclchar->siPartyIndex, PARTYQUEST_TYPE_MAKEITEM, pclMsg->clItem.siUnique, pclMsg->siAddedNum);
			}
		}
			

		// ������ ��� ��踦 ������Ʈ �Ѵ�. 
		pclItemManager->AddMakeNum(pclMsg->clItem.siUnique , pclMsg->siAddedNum);

		// ���ο� ��� - ������ ���
		NStatistics_Add("Item", pclMsg->clItem.siUnique,"MakeNum", pclMsg->siAddedNum);
		NStatistics_Set("Item", pclMsg->clItem.siUnique, "Name", pclItemManager->GetName(pclMsg->clItem.siUnique));

		// ���ο� ��� - ���� ���� ī��Ʈ
		if( pclMsg->clItem.siUseCrystalNum > 0 )
		{
			NTCHARString32	kSlotNum;
			kSlotNum = "Slot";		kSlotNum += SI08ToString(pclMsg->clItem.siUseCrystalNum);
			NStatistics_Add("Item", pclMsg->clItem.siUnique, kSlotNum, 1);
		}
	}

	// �������ٺ�
	//---------------------------------------------------------------
	// �Ƿ��ڿ� �����ڰ� �ٸ� ���, �Ƿ����� ���λ��� ������ �����Ѵ�. 
	//---------------------------------------------------------------
	if(pclMsg->m_bRequest_Want_Make_Item == true )	// �����Ƿ��� ���
	{
		if(pclMsg->siPersonID != pclMsg->siMaterialPersonID)
		{
			// �������ٺ�
			//---------------------------------------------------------------
			// �Ƿ��ڿ� �����ڰ� �ٸ� ���, �Ƿ����� ���λ��� ������ �����Ѵ�. 
			//---------------------------------------------------------------
			// ���� ������ ���� ���� �ִ��� Ȯ���Ѵ�.
			if(pclCM->IsValidID(id))
			{
				cltCharServer* pclMaker	= (cltCharServer* )pclCM->CR[ id ]	;
				// ���� ������ ���� ���� �ִ��� Ȯ���Ѵ�. => ������ ���� �ִ°� �̶� ������ 
				// ���� ������ �����Ƿ������� Ȯ���Ѵ�. 
				// �����Ƿ�ǰ���� �������� Ȯ���Ѵ�. 
				if( pclMaker->bPersonalShopSwitch == true &&
					pclMaker->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM_WANT &&
					pclMaker->clShopData.m_clItem[0].siUnique == pclMsg->siItemUnique)
				{
					// ���� ��ǰ�� �Ƿ��ϰ� �ִٰ� �Ǻ� 

					// ���� �Ƿ� ���λ��� ������ ������Ʈ �Ѵ�. 
					// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
					pclMaker->SetUpdateSwitch(UPDATE_IP, true, 0);

					// ������ �����Ѵ�.
					if(pclMsg->siAddedNum <= 0)
					{
						pclMaker->clShopData.m_clItem[0].siItemNum += pclMsg->siOrderNumber;
					}
					else	// Client���� ���������� �����ش�.			
					{

						cltGameMsgResponse_MakePersonalShop clInfo(id, MAKEPERSONALSHOP_SUCCESS_MAKE, pclMsg->siItemUnique,  pclMsg->siAddedNum );
						cltMsg clMsg(GAMEMSG_RESPONSE_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}

					// ������ ���� �ȸ��� Stop��Ű���� �Ѵ�. ���������� ���� �Ƿ��ڸ� Update�Ѵ�.
					if(pclMaker->clShopData.m_clItem[0].siItemNum <= 0)
					{
						// ĳ������ ���λ����� �����Ѵ�. 
						pclMaker->SetPersonalShopBanner(NULL);
						pclMaker->SetPersonalShopData(false, NULL);

						// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
						cltGameMsgResponse_StopPersonalShop clinfo(pclMaker->GetCharUnique(), pclMaker->pclCI->GetPersonID(), 2);
						cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
						pclMaker->SendNeighbourMsg(&clMsg, true);
					}
					else	
					{
						cltGameMsgResponse_UpdatePersonalShopData clinfo(id, &pclMaker->clShopData);
						cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
						pclMaker->SendNetMsg((sPacketHeader*)&clMsg);
					}

					// ���λ��� ���������� ������. ������ ���� 
					{
						cltGameMsgResponse_UpdatePersonalShopData clinfo(id, &pclMaker->clShopData);
						cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->CR[materialcharid]->SendNetMsg((sPacketHeader*)&clMsg);
					}

					//---------------------------------------------------------------
				}
				else // ������ �ݵ��� �Ѵ�.
				{
					if(pclMaker->bPersonalShopSwitch == false)	
						pclMaker->clShopData.m_siShopMode = PSHOP_MODE_NONE;

					// ���λ��� ���������� ������.
					cltGameMsgResponse_UpdatePersonalShopData clinfo(id, &pclMaker->clShopData);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[materialcharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
                
			}
		}

	}
	else // ������ �����Ƿ� 
	{
		if(pclMsg->siPersonID != pclMsg->siMaterialPersonID)
		{
			// �������ٺ�
			//---------------------------------------------------------------
			// �Ƿ��ڿ� �����ڰ� �ٸ� ���, �Ƿ����� ���λ��� ������ �����Ѵ�. 
			//---------------------------------------------------------------
			// ���� ������ ���� ���� �ִ��� Ȯ���Ѵ�. 
			if(pclCM->IsValidID(materialcharid))
			{
				cltCharServer* pclcharshopper	= (cltCharServer* )pclCM->CR[ materialcharid ];
				// ���� ������ ���� ���� �ִ��� Ȯ���Ѵ�. 
				// ���� ������ �����Ƿ������� Ȯ���Ѵ�. 
				// �����Ƿ�ǰ���� �������� Ȯ���Ѵ�. 
				if( pclcharshopper->bPersonalShopSwitch == true &&
					pclcharshopper->clShopData.m_siShopMode == PSHOP_MODE_MAKEITEM &&
					pclcharshopper->clShopData.m_clItem[0].siUnique == pclMsg->siItemUnique)
				{
					// ���� ��ǰ�� �Ƿ��ϰ� �ִٰ� �Ǻ� 

					// ���� �Ƿ� ���λ��� ������ ������Ʈ �Ѵ�. 
					// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
					pclcharshopper->SetUpdateSwitch(UPDATE_IP, true, 0);

					// ������ �����Ѵ�.
					if(pclMsg->siAddedNum <= 0)
					{
						pclcharshopper->clShopData.m_clItem[0].siItemNum += pclMsg->siOrderNumber;
					}
					else	// Client���� ���������� �����ش�.			
					{

						cltGameMsgResponse_MakePersonalShop clInfo(id, MAKEPERSONALSHOP_SUCCESS_MAKE, pclMsg->siItemUnique,  pclMsg->siAddedNum );
						cltMsg clMsg(GAMEMSG_RESPONSE_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}

					// ������ ���� �ȸ��� Stop��Ű���� �Ѵ�. ���������� ���� �Ƿ��ڸ� Update�Ѵ�.
					if(pclcharshopper->clShopData.m_clItem[0].siItemNum <= 0)
					{
						// ĳ������ ���λ����� �����Ѵ�. 
						pclcharshopper->SetPersonalShopBanner(NULL);
						pclcharshopper->SetPersonalShopData(false, NULL);

						// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
						cltGameMsgResponse_StopPersonalShop clinfo(pclcharshopper->GetCharUnique(), pclcharshopper->pclCI->GetPersonID(), 2);
						cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
						pclcharshopper->SendNeighbourMsg(&clMsg, true);

						//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
						//{
						//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����.
						//	// param1 == ���.
						//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_END, 
						//						0, (cltCharServer*)pclcharshopper, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						//						2, 0, 0, 0, 0, NULL, NULL);
						//}

					}
					else	
					{
						cltGameMsgResponse_UpdatePersonalShopData clinfo(materialcharid, &pclcharshopper->clShopData);
						cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
						pclcharshopper->SendNetMsg((sPacketHeader*)&clMsg);
					}

					// ���λ��� ���������� ������. ������ ���� 
					{
						cltGameMsgResponse_UpdatePersonalShopData clinfo(materialcharid, &pclcharshopper->clShopData);
						cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}

					//---------------------------------------------------------------
				}
				else // ������ �ݵ��� �Ѵ�.
				{
					if(pclcharshopper->bPersonalShopSwitch == false)	
						pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;

					// ���λ��� ���������� ������.
					cltGameMsgResponse_UpdatePersonalShopData clinfo(materialcharid, &pclcharshopper->clShopData);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_ENCHANTITEMINV(sPacketHeader* pPacket)
{
	sDBResponse_EnchantItemInv* pclMsg = (sDBResponse_EnchantItemInv*)pPacket;

	//----------------------------
	// ���̵��� �������� Ȯ���Ѵ�. 
	//----------------------------
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == false)return ;
	if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)return ;

	// �ֹ����� ���̵� Ȯ���Ѵ�. 
	SI32 materialcharid;
	if(pclMsg->siPersonID == pclMsg->siMaterialPersonID)
	{
		materialcharid = id;
	}
	else
	{
		materialcharid = pclCM->GetIDFromPersonID(pclMsg->siMaterialPersonID);
	}

	if( pclCM->IsValidID(materialcharid) == false )		return;
	// �������� �߰��Ǵ� �ڸ��� �Ǿ� �ִ� ������ �����Ѵ�. 
	cltCharServer* pclMaterialChar = (cltCharServer*)pclCM->CR[materialcharid];
	if(pclMaterialChar == NULL)return ;

	pclMaterialChar->SetInputItemReserve(pclMsg->siOutputPos, 0);


	bool bupdateinvswitch = false;
	bool bcontinueswitch = false;
	cltServer * pclserver = (cltServer*)pclClient;
	switch(pclMsg->siResult)
	{

	case 1:		// �������� ����. 
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // �κ��丮������ ������ �����.
					// param1 == �ٲ� ������ ��ġ. 
					// param2 == ��æƮ ���� ����
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_ENCHANT_ITEM_INV, 
										0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siMaterialPersonID, 0, 0, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
										pclMsg->siOutputPos, pclMsg->siSuccess, 0, 0, 0, 
										NULL, NULL);
				}

		break;							

	case 2:								// �ϼ�ǰ ���� �ڸ��� �̹� �ٸ� ��ǰ�� ����. 
		{
			if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
			{
				pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);

				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_MAKEITEMFAIL_POS, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siOutputPos], 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			return;	
		}
		break;
	case 0:
	case 3:								// �����ᰡ �����Ͽ� ��ǰ ���� ����. 
	default:
		return ;
	}

	if ( pclMsg->siSuccess > 0 )
	{
		// ��尡 �ִٸ� GP�� ������Ʈ�Ѵ�.
		if ( pclCM->CR[id]->pclCI->clBI.clGuildRank.IsGuildMember() == true )
		{
			cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex());
			if ( pGuild )
			{
				if ( pclMsg->clItem.Element.siPower == 5 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),20,TYPE_GUILDPOINT_ADD_ENCHANT_5);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else if ( pclMsg->clItem.Element.siPower == 6 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),50,TYPE_GUILDPOINT_ADD_ENCHANT_6);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else if ( pclMsg->clItem.Element.siPower == 7 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),100,TYPE_GUILDPOINT_ADD_ENCHANT_7);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else if ( pclMsg->clItem.Element.siPower == 8 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),300,TYPE_GUILDPOINT_ADD_ENCHANT_8);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else if ( pclMsg->clItem.Element.siPower == 9 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),700,TYPE_GUILDPOINT_ADD_ENCHANT_9);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else if ( pclMsg->clItem.Element.siPower == 10 )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCM->CR[id]->pclCI->GetPersonID(),1500,TYPE_GUILDPOINT_ADD_ENCHANT_10);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}
	}

	//--------------------------
	// �κ��� ������Ʈ �Ѵ�. 
	//--------------------------
	if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);


	//================================================ 
	// Client�� ������ �κ��丮 Update�Ѵ�. by tae-yang
	//================================================ 
	if(pclMaterialChar->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//-------------------------------------------------
	// ��æƮ â�� ������Ʈ �Ѵ�.
	//-------------------------------------------------
	if(pclMaterialChar->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONENCHANTITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}




	//================================================ 
	// Client�� ������ �κ��丮 Update�Ѵ�. by tae-yang
	//================================================ 
	if(pclMaterialChar->pclCI->GetPersonID() != pclMsg->siPersonID && pclMsg->siMaterialPersonID !=0)
	{
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[materialcharid]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//-------------------------------------------------
	// ��æƮ â�� ������Ʈ �Ѵ�.
	//-------------------------------------------------
	if(pclMaterialChar->pclCI->GetPersonID() != pclMsg->siPersonID && pclMsg->siMaterialPersonID !=0)
	{
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			pclMaterialChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONENCHANTITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[materialcharid]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}


	SI32 skillunique	= 0;
	SI32 skillexp		= 0;

	if(pclMsg->siResult)
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];


		// ��ǰ ���� ����� �뺸�Ѵ�. 
		cltItem clmadeitem;
		clmadeitem.Set(&pclMsg->clItem);

		cltGameMsgResponse_EnchantItemDlg clinfo(&clmadeitem, pclMsg->siSuccess );
		cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTITEMDLG, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if( materialcharid != id )
		{
			pclCM->CR[ materialcharid ]->SendNetMsg((sPacketHeader*)&clMsg);
		}

	}




	// �����ڿ� �ֹ����� �������� ������Ʈ �Ѵ�. 
	if(pclMsg->siFee)
	{
		{
			pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siPersonIDMoney);

			// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
			cltGameMsgResponse_ChangeMoney clinfo(pclCM->CR[id]->pclCI->clIP.GetMoney(),0, CHANGE_MONEY_REASON_MAKE);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		{
			pclMaterialChar->pclCI->clIP.SetMoney(pclMsg->siMaterialPersonIDMoney);

			// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
			cltGameMsgResponse_ChangeMoney clinfo(pclMaterialChar->pclCI->clIP.GetMoney(),0, CHANGE_MONEY_REASON_MAKE);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
			pclMaterialChar->SendNetMsg((sPacketHeader*)&clMsg);
		}

	}


	// ������ ��� ��踦 ������Ʈ �Ѵ�. 
	pclItemManager->AddMakeNum(pclMsg->clItem.siUnique ,1);

	////////////////////////////////////////////
	// ��þƮ ����Ʈ ���̾��ٸ� ����Ʈ ���� ������Ʈ
	////////////////////////////////////////////
	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( NULL == pclChar )
	{
		return;
	}

	pclChar->IncQuestPara(QUEST_CLEAR_COND_ENCHANTITEM, pclMsg->clItem.siUnique, 1);
	
	pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_ENCHANTANYITEM);

	if ( pclMsg->clItem.IsWeapon(pclItemManager) )
	{
		SI32 siLevel = pclMsg->clItem.GetEquipLevel( pclItemManager );

		pclChar->IncQuestPara(QUEST_CLEAR_COND_ENCHANTEQUIPLEVELWEAPON, siLevel, 1);
	}
	
	// ������ ��þƮ ���� ����
	if ( (1 == pclMsg->siResult) && (ENCHANT_SUCCESS == pclMsg->siSuccess) )
	{
		SI32 siNoticeGrade = pclClient->GetGlobalValue( TEXT("GV_Enchant_Success_NoticeLevel") );
		
		if ( (0 < siNoticeGrade) && (siNoticeGrade <= pclMsg->clItem.Element.siPower) )
		{
			cltGameMsgResponse_RareItemMade	clinfo((TCHAR*)pclMaterialChar->GetName(), pclMaterialChar->pclCI->GetPersonID(), 
				&pclMsg->clItem,
				RAREITEM_NOTICE_SWITCH_ENCHANTSUCCESS,
				0 );

			cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMMADE, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			
		}
	}

	
}

void cltServer::DoMsg_DBMSG_RESPONSE_ENCHANT_USEDAYPLUS(sPacketHeader * pPacket)
{
	sDBResponse_EnchantUseDayPlus * pclMsg = (sDBResponse_EnchantUseDayPlus*)pPacket;

	//----------------------------
	// ���̵��� �������� Ȯ���Ѵ�. 
	//----------------------------
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == false)return ;
	if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)return ;


	// �������� �߰��Ǵ� �ڸ��� �Ǿ� �ִ� ������ �����Ѵ�. 
	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if(pclChar == NULL)return ;


	pclChar->SetInputItemReserve(pclMsg->siOutputPos, 0);
	pclChar->SetInputItemReserve(pclMsg->siOutputMaterialPos, 0);

	if( pclMsg->siResult == 1)
	{
		//--------------------------
		// �κ��� ������Ʈ �Ѵ�. 
		//--------------------------
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON &&
			pclMsg->siOutputMaterialPos >= 0 && pclMsg->siOutputMaterialPos < MAX_ITEM_PER_PERSON )
		{
			pclChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			pclChar->pclCI->clCharItem.clItem[pclMsg->siOutputMaterialPos].Set(&pclMsg->clMaterialItem);
		}

		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
		}

		if( pclMsg->siOutputMaterialPos >= 0 && pclMsg->siOutputMaterialPos < MAX_ITEM_PER_PERSON )
		{
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputMaterialPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clMaterialItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
		}

		cltGameMsgResponse_EnchantItemDlg clinfo(&pclMsg->clItem, ENCHANT_USEDAYPLUS );
		cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTITEMDLG, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}

	if(IsWhereServiceArea(ConstSwitch_NewLog))
	{
		cltItem clMaterialItem;
		clMaterialItem.Set(&pclMsg->clMaterialItem);
		clMaterialItem.SetItemNum(1);

		// �Ⱓ ���� ������ ���
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
			USEITEM_REASON_USEDAYPLUS, pclChar, 
			NULL, 0, 0, 0, &clMaterialItem, pclMsg->clMaterialItem.GetItemNum(), 0, 0, 0, 0, 0, 
			pclMsg->siOutputMaterialPos, 0, 0, 0, 0, 
			NULL, NULL);
		
		cltItem& pclItemPlused = pclMsg->clItem;

		TCHAR szUseStartdate[128] = TEXT("") ;
		TCHAR* pText = GetTxtFromMgr(5600) ;
		StringCchPrintf(szUseStartdate, 128, pText, pclItemPlused.uiDateYear+2000,pclItemPlused.uiDateMonth,pclItemPlused.uiDateDay) ;

		NDate ndate;
		ndate.SetDate(pclItemPlused.uiDateYear+2000,pclItemPlused.uiDateMonth,pclItemPlused.uiDateDay);
		ndate.AddDays(pclItemPlused.uiDateUseDay);

		TCHAR szUseEnddate[128] = TEXT("") ;
		pText = GetTxtFromMgr(5601) ;
		StringCchPrintf(szUseEnddate, 128, pText,ndate.m_uiYear,ndate.m_uiMonth,ndate.m_uiDay);

		// �Ⱓ ���� ������ ���
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_EXTENDTHETERM, 
			0, pclChar , 
			NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
			pclMsg->siOutputPos, 0, 0, 0, 0, 
			szUseStartdate, szUseEnddate);
	}

}

// [����] ������ ��þƮ �Ӽ� ���濡 ���� ���� - 2008.02.20
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEENCHANT(sPacketHeader* pPacket)
{
	sDBResponse_ChangeEnchant* pclMsg = (sDBResponse_ChangeEnchant*)pPacket;

	//----------------------------
	// ���̵��� �������� Ȯ���Ѵ�. 
	//----------------------------
	SI32 siID = pclMsg->usCharID;

	if (pclCM->IsValidID(siID) == false)								return ;
	if (pclCM->CR[siID]->pclCI->GetPersonID() != pclMsg->siPersonID)	return ;

	// �������� �߰��Ǵ� �ڸ��� �Ǿ� �ִ� ������ �����Ѵ�. 
	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[siID];
	if (pclChar == NULL)												return ;

	pclChar->SetInputItemReserve(pclMsg->siOutputPos, 0);
	pclChar->SetInputItemReserve(pclMsg->siOutputMaterialPos, 0);

	if( pclMsg->siResult == 1)
	{
		//--------------------------
		// �κ��� ������Ʈ �Ѵ�. 
		//--------------------------
		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON &&
			pclMsg->siOutputMaterialPos >= 0 && pclMsg->siOutputMaterialPos < MAX_ITEM_PER_PERSON )
		{
			pclChar->pclCI->clCharItem.clItem[pclMsg->siOutputPos].Set(&pclMsg->clItem);
			pclChar->pclCI->clCharItem.clItem[pclMsg->siOutputMaterialPos].Set(&pclMsg->clMaterialItem);
		}

		if( pclMsg->siOutputPos >= 0 && pclMsg->siOutputPos < MAX_ITEM_PER_PERSON )
		{
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);	
		}

		if( pclMsg->siOutputMaterialPos >= 0 && pclMsg->siOutputMaterialPos < MAX_ITEM_PER_PERSON )
		{
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siOutputMaterialPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clMaterialItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);	
		}

		cltGameMsgResponse_EnchantItemDlg clinfo(&pclMsg->clItem, ENCHANT_CHANGE );
		cltMsg clMsg(GAMEMSG_RESPONSE_ENCHANTITEMDLG, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}

// �������� Person�� ItemPos�� ������� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_INPUTITEMTOPERSON(sPacketHeader* pPacket)
{
	sDBResponse_InputItemToPerson* pclMsg = (sDBResponse_InputItemToPerson*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if(pclCM->IsValidID(id) == FALSE)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if( pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )		return;
 
	// �޽����� ���� ���� ����ڿ� ���ٸ�, 
	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 

		SI32 personitemoption = PERSONITEMINFO_OPTION_NONE;

		switch ( pclMsg->siInputItemPersonOption )
		{
			case INPUTITEMPERSON_OPTION_WAR:
				{
					personitemoption = PERSONITEMINFO_OPTION_WARITEM;	
				} 
				break;

			case INPUTITEMPERSON_OPTION_SPEECIALQUEST:
				{
					personitemoption = PERSONITEMINFO_OPTION_SPECIALQUEST;
				}
				break;

			case INPUTITEMPERSON_OPTION_MASTER:
				{
					personitemoption = PERSONITEMINFO_OPTION_MASTER;
				}
				break;

			case INPUTITEMPERSON_OPTION_EVENT:
				{
					personitemoption = PERSONITEMINFO_OPTION_EVENT;
				}
				break;

			case INPUTITEMPERSON_OPTION_QUEST:
				{
					personitemoption = PERSONITEMINFO_OPTION_QUEST;
				}
				break;

			case INPUTITEMPERSON_OPTION_FAMELEVEL:
				{
					personitemoption = PERSONITEMINFO_OPTION_FAMELEVEL;
				}
				break;

			case INPUTITEMPERSON_OPTION_ROULETTEGAME:
				{
					personitemoption = PERSONITEMINFO_OPTION_ROULETTEGAME;
				}
				break;

			case INPUTITEMPERSON_OPTION_BEGINNERWEAPON:
				{
					personitemoption = PERSONITEMINFO_OPTION_SHOW;
					pclchar->pclCI->clBI.bReceiveBeginnerWeapon = true;
				}
				break;

			case INPUTITEMPERSON_OPTION_MOFUMOFUEVENT:
				{
					personitemoption = PERSONITEMINFO_OPTION_MOFUMOFUEVENT;
				}
				break;

			case INPUTITEMPERSON_OPTION_SERVER_EVENT:
				{
					personitemoption = PERSONITEMINFO_OPTION_SERVEREVENTQUEST;
				}
				break;
			case INPUTITEMPERSON_OPTION_CHAR_ROULETTE:
				{
					personitemoption = PERSONITEMINFO_OPTION_HALLOWEENEVENT;
				}
				break;
			case INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE_SPECIAL:
				{
					personitemoption = PERSONITEMINFO_OPTION_PVP_LEAGUE;

				}break;
			case INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE:
				{
					personitemoption = PERSONITEMINFO_OPTION_PVP_LEAGUE;

				}break;
			case INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE:
				{
					personitemoption = PERSONITEMINFO_OPTION_NEWYEAREVENT;
				}break;
			case INPUTITEMPERSON_OPTION_DORMANCYACCOUNT:
				{
					personitemoption = PERSONITEMINFO_OPTION_DORMANCY;	
				} 
				break;
			case INPUTITEMPERSON_OPTION_SEQGMCOMMAND:
				{
					personitemoption = PERSONITEMINFO_OPTION_SEQGMCOMMAND;
				}break;
			case INPUTITEMPERSON_OPTION_BATTLEROYAL_KILLINGUSER:
			case INPUTITEMPERSON_OPTION_BATTLEROYAL_WINNER:
				{
					personitemoption = PERSONITEMINFO_OPTION_BATTLEROYAL;
				}break;
			case INPUTITEMPERSON_OPTION_ADDITIONALITEM_GET:
				{
					personitemoption = PERSONITEMINFO_OPTION_ADDITIONALITEM_GET;
				}break;
			// [����] ���� ���� ���ڿ��� �������� �ش� 
			case INPUTITEMPERSON_OPTION_LIMITLEVELBOX:
				{
					personitemoption = PERSONITEMINFO_OPTION_ADDITIONALITEM_GET;
				}break;
		}
				
		// �������� �ü��� ���Ѵ�. 
		cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice(pclItemManager, pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].siUnique);
		GMONEY price	= 0;
		if(pclprice)
		{
			price = pclprice->siPrice;
		}

		// �������� �߰��Ǵ� �ڸ��� �Ǿ� �ִ� ������ �����Ѵ�. 
		pclchar->SetInputItemReserve(pclMsg->siItemPos, 0);


		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, personitemoption, pclMsg->siChangedNum, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos], price);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if( pclMsg->siInputItemPersonOption == INPUTITEMPERSON_OPTION_WAR)
		{
			cltCharServer* pclQuestChar = (cltCharServer*)pclCM->CR[id];

			if ( NULL == pclQuestChar )
			{
				return;
			}

			// [����] ����Ʈ ī��Ʈ ����
			SI32 siQuestItemNum = pclMsg->siChangedNum;

			if ( 0 < pclQuestChar->siQuestCount )
			{
				siQuestItemNum = pclQuestChar->siQuestCount;
			}

			// ����Ʈ ������Ʈ
			pclQuestChar->IncQuestPara(QUEST_CLEAR_COND_HUNT_ITEM, pclMsg->clItem.siUnique, siQuestItemNum );
			

			if ( pclCM->CR[id]->siPartyIndex > 0 ) 
			{
				CPartyObj* pParty = pclPartyMgr->GetPartyObj(pclCM->CR[id]->siPartyIndex);

				if(pParty)
				{
					cltItem clItem;
					clItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos]);
					clItem.siItemNum = pclMsg->siChangedNum;
					pParty->NotifyGetIemToPartyMember(pclCM->CR[id]->GetCharUnique(), &clItem );
				}
			}
		}

		if(IsWhereServiceArea(ConstSwitch_NewLog))
		{
			if( pclMsg->siInputItemPersonOption == INPUTITEMPERSON_OPTION_MAKEITEM_MATERIAL )
			{
				// ���� ��� ��� �α� ��� - DB���� ���� ���� �ɼ����� ������ �ش�.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
									USEITEM_REASON_MAKE_MATERIAL, (cltCharServer*)pclCM->CR[id], 
									NULL, 0, 0, 0, &pclMsg->clInputedItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
									pclMsg->siItemPos, 0, 0, 0, 0, 
									NULL, NULL);
			}
			else if( pclMsg->siInputItemPersonOption == INPUTITEMPERSON_OPTION_ENCHANT_MATERIAL )
			{
				// ���� ��� ��� �α� ��� - DB���� ���� ���� �ɼ����� ������ �ش�.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
					USEITEM_REASON_ENCHANT_MATERIAL, (cltCharServer*)pclCM->CR[id], 
					NULL, 0, 0, 0, &pclMsg->clInputedItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
					pclMsg->siItemPos, 0, 0, 0, 0, 
					NULL, NULL);
			}
			else
			{
				// [�α��߰� : Ȳ���� 2007. 10. 15] // ������ ȹ�� ��Ŀ� ���� �α� �߰�.
				// param1: �κ��丮 ��ġ
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM, 
									pclMsg->siInputItemPersonOption, (cltCharServer*)pclCM->CR[id], 
									NULL, 0, 0, 0, &pclMsg->clInputedItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
									pclMsg->siItemPos, 0, 0, 0, 0, 
									NULL, NULL);
			}
		}
	}
}

// �������� Person�� ItemPos���� ����� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_OUTPUTITEMFROMPERSON(sPacketHeader* pPacket)
{
	sDBResponse_OutputItemFromPerson* pclMsg = (sDBResponse_OutputItemFromPerson*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if( pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )		return;

	// �޽����� ���� ���� ����ڿ� ���ٸ�, 
	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos], 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}



// �������� Person�� �� ��ġ���� �ٸ� ��ġ�� �̵��϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MOVEITEM(sPacketHeader* pPacket)
{
	sDBResponse_MoveItem* pclMsg = (sDBResponse_MoveItem*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if( pclMsg->siFromItemPos < 0	|| pclMsg->siFromItemPos >= MAX_ITEM_PER_PERSON )		return;
	if( pclMsg->siToItemPos < 0		|| pclMsg->siToItemPos >= MAX_ITEM_PER_PERSON )		return;

	// �޽����� ���� ���� ����ڿ� ���ٸ�, 
	if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		//---------------------------------------------
		// ������ ������Ʈ �Ѵ�. 
		//---------------------------------------------

		// [����] �������� ���� �ִ� ���⸦ ����Ѵ�.
		SI32 siPrevActiveWeapon = pclchar->pclCI->clCharItem.clItem[pclchar->ActiveWeapon].siUnique;

		pclchar->pclCI->clCharItem.clItem[pclMsg->siFromItemPos].Set(&pclMsg->clFromItem);
		pclchar->pclCI->clCharItem.clItem[pclMsg->siToItemPos].Set(&pclMsg->clToItem);

		pclchar->SetParametaBoxAction(true);	// ParametaBoxAction�� �����Ѵ�. 

		//----------------------------------------------
		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		//----------------------------------------------


		cltGameMsgResponse_PersonItemInfo clinfo1(pclMsg->siFromItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0);
		cltMsg clMsg1(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo1), (BYTE*)&clinfo1);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg1);

		cltGameMsgResponse_PersonItemInfo clinfo2(pclMsg->siToItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
		cltMsg clMsg2(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg2);

		// �κ��丮������ ������ �ű��� ��Ʈ������ Ȯ���� ������
		if( pclMsg->siFromItemPos < PERSONITEM_INV0 ||
			pclMsg->siToItemPos < PERSONITEM_INV0 )
		{
			cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;
			
			SI16 setItemType  = 0;
			SI16 setItemStep  = 0;
			SI16 setItemType2 = 0;
			SI16 setItemStep2 = 0;
			SI16 setItemType3 = 0;
			SI16 setItemStep3 = 0;
			SI16 setItemType4 = 0;
			SI16 setItemStep4 = 0;
			SI16 setItemType5 = 0;
			SI16 setItemStep5 = 0;

			if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep, USE_SETITEM_1 );
				pclchar->m_siSetItemType = setItemType;

				setItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep2, USE_SETITEM_2 );
				pclchar->m_siSetItemType2 = setItemType2;

				setItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep3, USE_SETITEM_3 );
				pclchar->m_siSetItemType3 = setItemType3;

				setItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep4, USE_SETITEM_4 );
				pclchar->m_siSetItemType4 = setItemType4;

				setItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep5, USE_SETITEM_5 );
			}
			else
			{
				setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( &pclchar->pclCI->clCharItem.clItem[0] );
			}
			pclchar->m_siSetItemType = setItemType;
			pclchar->m_siSetItemStep = setItemStep;

			pclchar->m_siSetItemType2 = setItemType2;
			pclchar->m_siSetItemStep2 = setItemStep2;

			pclchar->m_siSetItemType3 = setItemType3;
			pclchar->m_siSetItemStep3 = setItemStep3;

			pclchar->m_siSetItemType3 = setItemType4;
			pclchar->m_siSetItemStep3 = setItemStep4;

			pclchar->m_siSetItemType3 = setItemType5;
			pclchar->m_siSetItemStep3 = setItemStep5;

			cltGameMsgResponse_SetItemTypeInfo clinfo3( setItemType, setItemStep, setItemType2, setItemStep2, setItemType3, setItemStep3, setItemType4, setItemStep4, setItemType5, setItemStep5 );
			cltMsg clMsg3(GAMEMSG_RESPONSE_SETITEMTYPEINFO, sizeof(clinfo3), (BYTE*)&clinfo3);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg3);
		}

		//----------------------------------------------
		// ����, Ż���� ��� EquipShape��� �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		if(    pclMsg->siFromItemPos	== PERSONITEM_WEAPON1
			|| pclMsg->siFromItemPos	== PERSONITEM_WEAPON2
			|| pclMsg->siFromItemPos	== PERSONITEM_HELMET
			|| pclMsg->siFromItemPos	== PERSONITEM_HAT
			|| pclMsg->siFromItemPos	== PERSONITEM_ARMOUR
			|| pclMsg->siFromItemPos	== PERSONITEM_DRESS
			|| pclMsg->siFromItemPos	== PERSONITEM_MANTLE
			|| pclMsg->siFromItemPos	== PERSONITEM_NECK
			|| pclMsg->siFromItemPos	== PERSONITEM_RING1
			|| pclMsg->siFromItemPos	== PERSONITEM_RING2
			|| pclMsg->siFromItemPos	== PERSONITEM_SHOES
			|| pclMsg->siFromItemPos	== PERSONITEM_BELT
			|| pclMsg->siToItemPos		== PERSONITEM_WEAPON1
			|| pclMsg->siToItemPos		== PERSONITEM_WEAPON2
			|| pclMsg->siToItemPos		== PERSONITEM_HELMET
			|| pclMsg->siToItemPos		== PERSONITEM_HAT
			|| pclMsg->siToItemPos		== PERSONITEM_ARMOUR
			|| pclMsg->siToItemPos		== PERSONITEM_DRESS
			|| pclMsg->siToItemPos		== PERSONITEM_MANTLE
			|| pclMsg->siToItemPos		== PERSONITEM_NECK
			|| pclMsg->siToItemPos		== PERSONITEM_RING1
			|| pclMsg->siToItemPos		== PERSONITEM_RING2
			|| pclMsg->siToItemPos		== PERSONITEM_SHOES
			|| pclMsg->siToItemPos		== PERSONITEM_BELT)
		{

			// ���� ��� ������ ����� ���� �ִ°� ?
			// skill : SKILL_USESWORD1 ...
			pclchar->CheckWeaponSkillScroll(pclItemManager);

			pclchar->SendNeighbourMyShapeStatus();
			pclchar->CheckCurrentMagic( siPrevActiveWeapon );
		}

		// [�α��߰� : Ȳ���� 2007. 10. 18] // person�� ������ â���� �������� �̵���Ų��. (�κ����� ����â�̳� �� �ݴ�� ���� ���. ) 
		// param1 == ���������� ��ġ, 
		// param2 == �ű����� ������ ��ġ, 
		// param3 == ���� �������� ��������
		// charparam1 = "ToItemPos = %d"
		// charparam2 = "ToItemUnique = %d, ToItemNum = %d"

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_MOVE_ITEM, 
							0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, 
							&pclMsg->clMoveItem, pclMsg->clToItem.siItemNum, 0, 0, 0, 0, 0, 
							pclMsg->siFromItemPos, pclMsg->siToItemPos, pclMsg->clFromItem.siItemNum, 0, 0, 
							NULL, NULL);
	}
}

// �������� Person���� �ٸ� Person���� �ű��� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MOVEITEMPERSON(sPacketHeader* pPacket)
{
	sDBResponse_MoveItemPerson* pclMsg = (sDBResponse_MoveItemPerson*)pPacket;

	if( 1 != pclMsg->siResult )
	{
		return;
	}

	// ���
	NStatistics_Add("Item", pclMsg->siDestroyItemUnique, "PKDestroy", 1);
	NStatistics_Set("Item", pclMsg->siDestroyItemUnique, "Name", pclItemManager->GetName(pclMsg->siDestroyItemUnique));

	SI32 winID = pclCM->GetIDFromPersonID( pclMsg->siToPersonID );
	SI32 loseID = pclCM->GetIDFromPersonID( pclMsg->siFromPersonID );

	if(winID && loseID)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // Person���� �������� �̵�. pk��...
			// param1 = 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_MOVE_ITEM_TO_PERSON, 
								 pclMsg->siReason, (cltCharServer*)pclCM->CR[loseID], NULL, pclMsg->siToPersonID, 0, 0, &pclMsg->clMoveItem, pclMsg->clToItem.siItemNum, 0, 0, 0, 0, 0, 
								 pclMsg->siFromItemPos, pclMsg->siToItemPos, pclMsg->bDestroy, 0, 0, 
								 NULL, NULL);
		}	
	}

	// �����
	if( pclCM->IsValidID( loseID ) )
	{
		pclCM->CR[loseID]->pclCI->clCharItem.clItem[pclMsg->siFromItemPos].Set(&pclMsg->clFromItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo( pclMsg->siFromItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[loseID]->SendNetMsg((sPacketHeader*)&clMsg);

		if( MOVEITEMPERSON_PVP == pclMsg->siReason )
		{
		//	if( false == pclMsg->bDestroy )
			{
				// ���� ����鿡�� �˷��ֱ�
				SI32 homeVillageUnique = pclCM->CR[loseID]->pclCI->clBI.siHomeVillage;
				if( homeVillageUnique > 0 )
				{
					SI32 id;

					SI32 index = 0;
					while( id = pclCM->GetCharOrder(index) )
					{
						index++;
						if( id == loseID )
							continue;

						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
						if( pclchar->GetSession() )
						{
							if( pclchar->pclCI->clBI.siHomeVillage == homeVillageUnique )
							{
								cltLetterMsg_PVPResult clletter( false, cltLetterMsg_PVPResult::GUILD, pclMsg->szToUserName, (TCHAR*)pclCM->CR[loseID]->GetName(), pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
								SendLetterMsg( pclchar->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );
							}

						}
					}
				}

				// �������� ���� �׾��ٰ� �˷��ֱ�
				if ( pclCM->CR[loseID]->pclCI->clBI.clGuildRank.IsGuildMember() == true )
				{
					cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo( pclCM->CR[loseID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() );
					if ( pGuild )
					{
						for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM; ++i )
						{
							if( pGuild->clMember[i].siPersonID > 0 )
							{
								cltLetterMsg_PVPResult clletter( false, cltLetterMsg_PVPResult::GUILD, pclMsg->szToUserName, (TCHAR*)pclCM->CR[loseID]->GetName(), pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
								SendLetterMsg( pGuild->clMember[i].siPersonID, (cltLetterHeader*)&clletter );
							}
						}
					}
				}
				if( true != pclMsg->bDestroy )
				{
					cltLetterMsg_PVPResult clletter( false, cltLetterMsg_PVPResult::LOSE, pclMsg->szToUserName, (TCHAR*)pclCM->CR[loseID]->GetName(), pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
					SendLetterMsg( pclCM->CR[loseID]->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );
				}
			}

			// ���⸦ ���Ұܼ� ���� ������ �ٲ���� �˻�
			cltCharServer* pclLoseChar = pclCM->GetCharServer( loseID );
			if ( (pclLoseChar) && (pclMsg->siFromItemPos == pclLoseChar->ActiveWeapon) )
			{
				SI32 siItemType		= pclMsg->clFromItem.GetType( pclItemManager );
				SI32 siSkillUnique	= pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );

				if ( (0 < pclLoseChar->m_uiWeaponSkillMasterEmblem) && (0 >= siSkillUnique) )
				{
					pclLoseChar->m_uiWeaponSkillMasterEmblem = 0;
					
					cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_EMBLEM, false, 0 );
					cltGameMsgResponse_StatusInfo	clInfo( pclLoseChar->GetCharUnique(), &clChangeInfo );

					cltMsg clEmblenMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclLoseChar->SendNeighbourMsg( &clEmblenMsg, true );
				}
			}
		}	// ����	if( MOVEITEMPERSON_PVP == pclMsg->siReason )
	}

	// �̱���
	if( pclCM->IsValidID( winID ) )
	{
		if( MOVEITEMPERSON_PVP == pclMsg->siReason )
		{
			if( true == pclMsg->bDestroy )
			{
				cltLetterMsg_PVPResult clletter( true, cltLetterMsg_PVPResult::WIN, (TCHAR*)pclCM->CR[winID]->GetName(), pclMsg->szFromUserName, pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
				SendLetterMsg( pclMsg->siToPersonID, (cltLetterHeader*)&clletter );

				cltLetterMsg_PVPResult clletter2( false, cltLetterMsg_PVPResult::LOSE, (TCHAR*)pclCM->CR[winID]->GetName(), pclMsg->szFromUserName, pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
				SendLetterMsg( pclMsg->siFromPersonID, (cltLetterHeader*)&clletter2 );
			}
			else
			{
				cltLetterMsg_PVPResult clletter( true, cltLetterMsg_PVPResult::WIN, (TCHAR*)pclCM->CR[winID]->GetName(), pclMsg->szFromUserName, pclMsg->bDestroy, pclMsg->siDestroyItemUnique );
				SendLetterMsg( pclMsg->siToPersonID, (cltLetterHeader*)&clletter );
			}
		}

		pclCM->CR[winID]->pclCI->clCharItem.clItem[pclMsg->siToItemPos].Set(&pclMsg->clToItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siToItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[winID]->SendNetMsg((sPacketHeader*)&clMsg);
	}

/*	if(pclCM->IsValidID(id) )
	{
		// �޽����� ���� ���� ����ڿ� ���ٸ�, 
		if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siFromPersonID)
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siFromItemPos].Set(&pclMsg->clFromItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siFromItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}

		if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siToPersonID)
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToItemPos].Set(&pclMsg->clToItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siToItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}*/
}

// �������� ����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_USEITEM(sPacketHeader* pPacket)
{
	sDBResponse_UseItem* pclMsg = (sDBResponse_UseItem*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return;
	}
	// ���
	switch(pclMsg->siUseReason)
	{
	case USEITEM_REASON_DATEOVER:		// �Ⱓ�� ������ �Ⱓ ��
		{	NStatistics_Add("Item", pclMsg->clUsedItem.siUnique, "DateOver", pclMsg->clUsedItem.siItemNum);
			NStatistics_Set("Item", pclMsg->clUsedItem.siUnique, "Name", pclItemManager->GetName(pclMsg->clUsedItem.siUnique));
		}	break;
	}

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if (pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )		return;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ������ ���.
		// param1 == ���� �������� ��ġ. 
		// param2 == ���ǰ� ���� ����,
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
							 pclMsg->siUseReason, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUsedItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
							 pclMsg->siItemPos, 0, 0, 0, 0, NULL, NULL);
	}

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);


		if( pclClient->IsCountrySwitch(Switch_TreasureEvent) )
		{
			if ( pclMsg->clUsedItem.siUnique == ITEMUNIQUE(13058))
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION__TREASUREEVENTITEMUSE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
			else
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		else
		{
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		//--------------------------------------------
		// ����ġ �������� �̹� ��ġ�� �뿭�ߴ�. 
		//--------------------------------------------
		SI64 atb = pclItemManager->GetItemAtb(pclMsg->clUsedItem.siUnique);
		if(atb & ITEMATB_FIRSTACTION || pclItemManager->IsItemInfoAtb(pclMsg->clUsedItem.siUnique, ITEMINFOATB_FIRSTACTION) )
		{
		}
		else
		{
			switch(pclMsg->siUseReason)
			{
			case USEITEM_REASON_DATEOVER:		// �Ⱓ�� ������ �Ⱓ ��
			case USEITEM_REASON_ROULLET:		// �ڴ������ ���
			case USEITEM_REASON_BELONGITEM:		// �ͼӾ����� �ı�
			case USEITEM_REASON_PARTYHALLGIFT:		// �ͼӾ����� �ı�
				{
					// �ƹ�ó���� ���� �ʴ´�.
				}
				break;
			default:
				{
					if(((cltCharServer*)pclCM->CR[id])->UseItem(pclMsg->clUsedItem) == true)
					{

					}
				}
				break;
			}
			//if( pclMsg->siUseReason != USEITEM_REASON_ROULLET )	// �ڴ�� �������̸� ���Ѵ�
			//{
			//}
		}

		// ��ȣ�� �����Ͽ��� ��� ����(����) �ں��� +5000
		if ( pclMsg->siUseReason == USEITEM_REASON_DISASSEMBLE )
		{
			SI32 currentVillage = pclCM->CR[id]->GetCurrentVillageUnique();
			if( currentVillage>0 && currentVillage < MAX_VILLAGE_NUMBER)
			{
				GMONEY siGetVillageMoney = 5000; // ���� ���ͱ� ���� SI32 -> GMONEY
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, currentVillage, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}

		// ������ ��� ��踦 ������Ʈ �Ѵ�. 
		pclItemManager->AddUseNum(pclMsg->clUsedItem.siUnique, pclMsg->clUsedItem.siItemNum);

		// ���ο� ��� - ������ ���
		//NStatistics_Add("Item", pclMsg->clUsedItem.siUnique, "UseNum", pclMsg->clUsedItem.siItemNum);

	}
}

// ������ ������ �Ҹ� ���� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_WASTEDURABILITY(sPacketHeader* pPacket)
{
	sDBResponse_WasteDurability* pclMsg = (sDBResponse_WasteDurability*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ ���� ���.
		// param1 == ��ġ.
		SI32 siCharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
		cltCharServer* pclchar = (cltCharServer*)pclCM->GetChar(siCharID);
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_WASTE_DUR_ITEM, 
							 0, pclchar, NULL, 0, 0, 0, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
							 pclMsg->siFromPos, 0, 0, 0, 0, NULL, NULL);
	}
}

// �������� ������. 
void cltServer::DoMsg_DBMSG_RESPONSE_DROPITEM(sPacketHeader* pPacket)
{
	sDBResponse_DropItem* pclMsg = (sDBResponse_DropItem*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	if( pclMsg->siFromPos < 0 && pclMsg->siFromPos >= MAX_ITEM_PER_PERSON )		return;

	// ����߸� �������� ������ �־�� �Ѵ�. 
	if(pclMsg->clChangedItem.siUnique && pclMsg->clChangedItem.siItemNum)
	{
		DropItem(pclMsg->siMapIndex, pclMsg->siX, pclMsg->siY, &pclMsg->clChangedItem, pclMsg->siPersonID);
	}

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ ����.
		// param1 == ������ ��ġ. 
		// param2 == ���� ��ȣ, 
		// param3 == ������ġ : x 
		// param4 == ������ġ : y 

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_DROP_ITEM, 
							 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clChangedItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
							 pclMsg->siFromPos, pclMsg->siMapIndex, pclMsg->siX, pclMsg->siY, 0,
							 NULL, NULL);
	}

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siFromPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siFromPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}

// ������ ������ ���� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_INVREPAIR(sPacketHeader* pPacket)
{
	sDBResponse_InvRepair* pclMsg = (sDBResponse_InvRepair*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return;
	}

	if( pclMsg->siFromPos < 0 && pclMsg->siFromPos >= MAX_ITEM_PER_PERSON )		return;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ ����.
		// param1 == ��ġ. 
		// param2 == ������. 
		// param3 == ������ ������, 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_REPAIR_ITEM, 
							 0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siRepairPersonID, 0, pclMsg->siPersonIDMoney, &pclMsg->clItem, 0, 0, 0, pclMsg->siNPCVillageUnique, 0, 0, 
							 pclMsg->siFromPos, pclMsg->siRepairMoney, pclMsg->siRepairerMoney, 0, 0, 
							 NULL, NULL);
	}


	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siFromPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siFromPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// �ڱ��ڽ��� �����ϸ� ��������� 0 �̹Ƿ� ������ �ΰ�츦 ��� SKIP�Ѵ�.
		// ���� ������� 
		if(pclMsg->siRepairMoney)
		{
			// �Ƿ��� �ڱ��� �����Ѵ�. 
			pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siPersonIDMoney);

			// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
			cltGameMsgResponse_ChangeMoney clinfo(pclMsg->siPersonIDMoney, -pclMsg->siRepairMoney, CHANGE_MONEY_REASON_NPCREPAIRPAY);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			// NPC�� ������ �Ѱ�� NPC�� ���� ������ ���� �����Ѵ�.
			// 10%�� ������� 
			GMONEY incmoney = pclMsg->siRepairMoney * VILLAGE_PROFIT_RATE_FOR_NPCREPAIR / 100;
			if(incmoney)
			{
				// villageunique�� �ڱ� ����
				SI32 villageunique = pclMsg->siNPCVillageUnique;

				if(villageunique > 0)
				{
					//sDBRequest_ChangeStrMoney sendMsg(CHANGESTRMONEY_REPAIRNPC, 0, villageunique, RANKTYPE_CITYHALL, incmoney);
					sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, villageunique, incmoney );

					pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
				}
			}

		}

		// ������ �������� �������� ������ �����Ѵ�.
		if(pclMsg->siRepairerMoney)
		{
			// ������ �ڱ��� �����Ѵ�. 
			SI32 repairid = pclCM->GetIDFromPersonID(pclMsg->siRepairPersonID);
			if(pclCM->IsValidID(repairid))
			{
				pclCM->CR[repairid]->pclCI->clIP.SetMoney(pclMsg->siRepairerMoney);

				// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
				cltGameMsgResponse_ChangeMoney clinfo(pclMsg->siRepairerMoney, pclMsg->siRepairMoney, CHANGE_MONEY_REASON_REPAIRGET);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[repairid]->SendNetMsg((sPacketHeader*)&clMsg);

			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_UPGRADEITEM(sPacketHeader* pPacket)
{
	sDBResponse_UpgradeItem * pclMsg = (sDBResponse_UpgradeItem *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	// ��� �ڱ� ������Ʈ
	if ( pclMsg->siVillageUnique > 0 && pclMsg->siVillageUnique <= CUR_VILLAGE_LIMIT &&
		pclMsg->clMoney.itMoney > 0 )
	{
		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );
		if( pStrInfo ) 
		{
			pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clMoney );
		}
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if ( pclMsg->siFromPos >= 0 && pclMsg->siFromPos < MAX_ITEM_PER_PERSON &&
			 pclMsg->siToPos >= 0	&& pclMsg->siToPos < MAX_ITEM_PER_PERSON )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPos ].Set( &pclMsg->clFromItem );
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPos ].Set( &pclMsg->clToItem );

			cltGameMsgResponse_UpgradeItem clinfo( pclMsg->bSuccess, pclMsg->siFromPos, &pclMsg->clFromItem, pclMsg->siToPos, &pclMsg->clToItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_UPGRADEITEM, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ���� ��ȭ.
			// param1 == ��������.			 
			// param2 == ���� ������ ����ũ, 
			// param3 == ���� ������ ��ġ, 
			// param4 == ���� ������ ����ũ. 
			// param5 == ���� ������ ��ġ.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_UPGRADE_ITEM, 
			 					 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								 pclMsg->bSuccess, 
								 pclMsg->clFromItem.siUnique, 
								 pclMsg->siFromPos,
								 pclMsg->clToItem.siUnique,	 
								 pclMsg->siToPos,
								 NULL, NULL);
		}
	}

	if( pclCM->IsValidID(id) == false )
		return;

	// ������ �����ϸ�, 
	if( pclMsg->bSuccess )
	{
		// ȣǰ�� �������� �ʴ´�. 
		if(pclMsg->clToItem.clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1)
		{
			// Ȥ�θ������� �̿��Ͽ� ȣǰ ����� ����Ʈ���̶��, 
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWENNYOLDMAN);

			pclCM->CR[id]->pclCI->clBI.bWennyOldManUpgrade = true ;
		}
		else
		{
			// ������ ����. 
			SendRareItemMade(id, &pclMsg->clToItem, RAREITEM_NOTICE_SWITCH_WENNYOLDMAN);
		}
	}

	return;
}

// ������ ���� ��� ( �������� ������ ��� ��Ų��. ������ ���̸鼭, ���� ������ ����ϸ鼭.. )
void cltServer::DoMsg_DBMSG_RESPONSE_PERFORMANCEUPGRADEITEM(sPacketHeader* pPacket)
{
	sDBResponse_PerformanceUpgradeItem * pclMsg = (sDBResponse_PerformanceUpgradeItem *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		pclLog->FilePrint( TEXT("Config\\UpgradeItem.log"), TEXT("DoMsg_DBMSG_RESPONSE_PERFORMANCEUPGRADEITEM pclMsg->siResult = %d"), pclMsg->siResult );
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON &&
			pclMsg->siLeftScrollItemPos >= 0 && pclMsg->siLeftScrollItemPos < MAX_ITEM_PER_PERSON )

		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemPos ].Set( &pclMsg->clItem );
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siLeftScrollItemPos ].Set( &pclMsg->clLeftScrollItem );

			cltGameMsgResponse_PerformanceUpgradeItem clinfo( pclMsg->siItemPos, &pclMsg->clItem, pclMsg->siLeftScrollItemPos, &pclMsg->clLeftScrollItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_PERFORMANCEUPGRADEITEM, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}


		if ( pclMsg->siResult == 1 )
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWENNYOLDMAN2);
		}


		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ������ ���� ���
			// pszParam1 == ������ ����� ������ ����, 
			// pszParam2 == ����ϰ� ���� ���� ������ ����.
			TCHAR pszCharParam[2][50] = {'\0', };
			StringCchPrintf(pszCharParam[0],  sizeof(pszCharParam[0]), "Item=> Uniqe: %d, Pos: %d, Num: %d", 
																		pclMsg->clItem.siUnique,
																		pclMsg->siItemPos,
																		pclMsg->clItem.siItemNum);
				
			StringCchPrintf(pszCharParam[1],  sizeof(pszCharParam[1]), "ScrollItem=> Uniqe: %d, Pos: %d, Num: %d",
																		pclMsg->clLeftScrollItem.siUnique,
																		pclMsg->siLeftScrollItemPos,
																		pclMsg->clLeftScrollItem.siItemNum);
				
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PERSONITEM_PERFORMANCE_UPGRADE, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											0, 0, 0, 0, 0, pszCharParam[0], pszCharParam[1]);
		}


	}




	return;
}

/*void cltServer::DoMsg_DBMSG_RESPONSE_DELETE_LIMITDATEITEM(sPacketHeader* pPacket)
{
sDBResponse_Delete_LimitDateItem * pclMsg = (sDBResponse_Delete_LimitDateItem*)pPacket;

if ( pclMsg->siResult == 1 )
{
SI32 id = pclMsg->siCharID ;

if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
{
pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
pclCM->CR[id]->pclCI->clLimitDateItem.Delete(pclMsg->siItemUnique);

cltGameMsgResponse_LimitDateItem_Info clinfo(pclCM->CR[id]->pclCI->clLimitDateItem.siItemUnique,pclCM->CR[id]->pclCI->clLimitDateItem.siItemLimitDate,
pclMsg->siItemPos,&pclMsg->clItem);
cltMsg clMsg(GAMEMSG_RESPONSE_LIMITDATEITEM_INFO, sizeof(clinfo), (BYTE*)&clinfo);
pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}
}
else if ( pclMsg->siResult == -1 )
{
SI32 id = pclMsg->siCharID ;

pclCM->CR[id]->pclCI->clLimitDateItem.Delete(pclMsg->siItemUnique);

cltGameMsgResponse_LimitDateItem_Info clinfo(pclCM->CR[id]->pclCI->clLimitDateItem.siItemUnique,pclCM->CR[id]->pclCI->clLimitDateItem.siItemLimitDate,
pclMsg->siItemPos,&pclMsg->clItem);
cltMsg clMsg(GAMEMSG_RESPONSE_LIMITDATEITEM_INFO, sizeof(clinfo), (BYTE*)&clinfo);
pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}
}*/

/*void cltServer::DoMsg_DBMSG_RESPONSE_GETLIMITUSEITEM(sPacketHeader* pPacket)
{
sDBResponse_GetLimitUseItem* pclMsg = (sDBResponse_GetLimitUseItem*)pPacket ;

if ( pclMsg->siResult == 1 )
{
SI32 id = pclMsg->siCharID ;

if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
{
pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
//			pclCM->CR[id]->pclCI->clLimitDateItem.Add(pclMsg->clItem.siUnique,pclMsg->siUseDate) ;

{
cltGameMsgResponse_LimitDateItem_Info clinfo(pclMsg->siItemPos,&pclMsg->clItem);
cltMsg clMsg(GAMEMSG_RESPONSE_LIMITDATEITEM_INFO, sizeof(clinfo), (BYTE*)&clinfo);
pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

// ������ ���� ���� ����Ѵ�.
pclLog->FilePrint(TEXT("Config\\InstanceItem.txt"), TEXT("User : [%s] Item : [%s] "),
pclCM->CR[id]->GetName(),pclItemManager->GetName(pclMsg->clItem.siUnique));

{
cltGameMsgResponse_BigWarItem clinfo(pclCM->CR[id]->GetName(), pclCM->CR[id]->pclCI->GetPersonID(), 
&pclMsg->clItem, 0, INPUTITEMPERSON_OPTION_INSTANCEMAP, 0);

cltMsg clMsg(GAMEMSG_RESPONSE_BIGWARITEM, sizeof(clinfo), (BYTE*)&clinfo);
pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
}
}
}
else if ( pclMsg->siResult == -1 ) // �������� �� ���� �� ����
{
SI32 id = pclMsg->siCharID ;

if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
{
SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL, pclMsg->clItem.siUnique, 0, pclCM->CR[id]->GetCharUnique());
}
}
}*/

void cltServer::DoMsg_DBMSG_RESPONSE_SETPREMIUM(sPacketHeader* pPacket)
{
	sDBResponse_SetPremium* pclMsg = (sDBResponse_SetPremium*)pPacket ;

	SI32 id = pclMsg->siCharID ;

	if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if ( pclchar == NULL ) return ;

		if ( pclMsg->siType == SETPREMIUM_EXP )
			pclchar->bIsSetPremium = false ;
		else if ( pclMsg->siType == SETPREMIUM_COMBAT )
			pclchar->bIsSetCombat = false ;
		else if ( pclMsg->siType == SETPREMIUM_MAKEITEM )
			pclchar->bIsSetMakeItem = false ;
		else if ( pclMsg->siType == SETPREMIUM_BULLET )
			pclchar->bIsBulletService = false ;
		else if ( pclMsg->siType == SETPREMIUM_SUMMONSTIMINA )
			pclchar->bIsSummonStaminaService = false ;


		if ( pclMsg->siResult == 1 )
		{
			if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
				pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			if ( pclMsg->siType == SETPREMIUM_EXP )
			{
				pclchar->pclCI->clBI.bPremiumService = pclMsg->bPremium ;
				pclchar->pclCI->clBI.siPremiumServiceDate = pclMsg->siPremiumUseDate ;
			}
			else if ( pclMsg->siType == SETPREMIUM_COMBAT )
			{
				pclchar->pclCI->clBI.bCombatService = pclMsg->bPremium ;
				pclchar->pclCI->clBI.siCombatServiceDate = pclMsg->siPremiumUseDate ;
			}
			else if ( pclMsg->siType == SETPREMIUM_MAKEITEM )
			{
				pclchar->pclCI->clBI.bMakeItemService = pclMsg->bPremium ;
				pclchar->pclCI->clBI.siMakeItemServiceDate = pclMsg->siMakeItemDate ;
			}
			else if ( pclMsg->siType == SETPREMIUM_BULLET)
			{
				pclchar->pclCI->clBI.bBulletService = pclMsg->bPremium ;
				pclchar->pclCI->clBI.siBulletServiceDate = pclMsg->siBulletDate;
			}
			else if ( pclMsg->siType == SETPREMIUM_SUMMONSTIMINA)
			{
				pclchar->pclCI->clBI.bSummonStaminaService = pclMsg->bPremium ;
				pclchar->pclCI->clBI.siSummonStaminaServiceDate = pclMsg->siSummonStaminaDate;
			}
			else return ;

			cltGameMsgResponse_Premium_Info clinfo(pclMsg->siItemPos,&pclMsg->clItem,pclMsg->bPremium,
				pclMsg->siPremiumUseDate,pclMsg->siCombatUseDate,pclMsg->siMakeItemDate, pclMsg->siBulletDate, pclMsg->siSummonStaminaDate, pclMsg->siType);
			cltMsg clMsg(GAMEMSG_RESPONSE_PREMIUM_INFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			{				
				// [�α��߰� : Ȳ���� 2007. 10. 11] // �����̾� ȿ��.(�����ʿ�)
				// param1 == �����̾� ����, 
				// param2 == ������ ��ġ, 
				// param3 == Ÿ��, 
				// pszcharParam1 == date ����.
				// pszcharParam2 == date ����.
				TCHAR pszCharParam1[50] = {'\0', };
				TCHAR pszCharParam2[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("Date=> PremiumUse: %d, CombatUse: %d, MakeItem: %d"), 																		
																			pclMsg->siPremiumUseDate,
																			pclMsg->siCombatUseDate,
																			pclMsg->siMakeItemDate);


				StringCchPrintf(pszCharParam2, sizeof(pszCharParam2), TEXT("Date=> Bullet: %d, SummonStamina: %d"),	
																			pclMsg->siBulletDate,
																			pclMsg->siSummonStaminaDate);


				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PREMIUM_SET, 
									 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
									 pclMsg->bPremium, pclMsg->siItemPos, pclMsg->siType, 0, 0, 
									 pszCharParam1, pszCharParam2);
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_EXCHANGEITEM(sPacketHeader* pPacket)
{

	sDBResponse_ExchangeItem* pclMsg = (sDBResponse_ExchangeItem*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return;
	}

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( pclCM->IsValidID(id) == false )
		return;

	if( pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )		return;

	pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clChangedItem);

	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clChangedItem, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
    
	// ������ ��� ��踦 ������Ʈ �Ѵ�. 
	pclItemManager->AddUseNum(pclMsg->clItem.siUnique, pclMsg->clItem.siItemNum);

	// ���ο� ��� - ������ ���
	//NStatistics_Add("Item", pclMsg->clItem.siUnique, "UseNum", pclMsg->clItem.siItemNum);

	/*if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ ��ü.
		// param1 == ��ü�� ������ ��ġ,  
		// param2 == ��ü�� ������ ����ũ.
		// param3 == ��ü�� ������ ����
		// param4 == ��ü�� ������ ����ũ.
		// param5 == ��ü�� ������ ����.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_EXCHANGE_ITEM_FROM, 
							 pclMsg->siReason, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
							 pclMsg->siItemPos, 
							 pclMsg->clItem.siUnique,		
							 pclMsg->clItem.siItemNum, 
						 	 pclMsg->clChangedItem.siUnique, 
							 pclMsg->clChangedItem.siItemNum, 
							 NULL, NULL);
	}*/
}


void cltServer::DoMsg_DBMSG_RESPONSE_OPENTREASUREBOX(sPacketHeader* pPacket)
{

	sDBResponse_OpenTreasureBox* pclMsg = (sDBResponse_OpenTreasureBox*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return;
	}

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( pclCM->IsValidID(id) == false )
		return;

	if( pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )		return;
	if( pclMsg->siToItemPos1 < 0 || pclMsg->siToItemPos1 >= MAX_ITEM_PER_PERSON )		return;
	//if( pclMsg->siToItemPos2 < 0 || pclMsg->siToItemPos2 >= MAX_ITEM_PER_PERSON )		return;

	pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

	if( pclMsg->siKeyItemPos >= PERSONITEM_INV0 && pclMsg->siKeyItemPos < MAX_ITEM_PER_PERSON )
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siKeyItemPos].Set(&pclMsg->clKeyItem);
		((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclMsg->siKeyItemPos , 0 );
	}

	pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToItemPos1].Set(&pclMsg->clToItem1);
	((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclMsg->siToItemPos1 , 0 );

	if( pclMsg->siToItemPos2 >= PERSONITEM_INV0 && pclMsg->siToItemPos2 < MAX_ITEM_PER_PERSON && pclMsg->clToItem2.siUnique > 0)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToItemPos2].Set(&pclMsg->clToItem2);
		((cltCharServer*)pclCM->CR[id])->SetInputItemReserve( pclMsg->siToItemPos2 , 0 );
	}

	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	cltGameMsgResponse_OpenTreasureBox clinfo( pclMsg->siItemPos, &pclMsg->clItem, pclMsg->siKeyItemPos, &pclMsg->clKeyItem, pclMsg->siToItemPos1, &(pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToItemPos1]), pclMsg->siGetItemNumber1 , pclMsg->siToItemPos2, &(pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToItemPos2]), pclMsg->siGetItemNumber2 );
	cltMsg clMsg(GAMEMSG_RESPONSE_OPENTREASUREBOX, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// [�޽��� ������ �ٲٱ� ������ �ϵ��ڵ� ��_��]
	// ��� ������ �˸�â
	if ( (true == pclMsg->bCanNotice1) || (true == pclMsg->bCanNotice2) )
	{
		NTCHARString32 ntstrName( pclCM->CR[id]->GetName() );

		if ( true == pclMsg->bCanNotice1 )
		{
			cltGameMsgResponse_RareItemFromTreasureBox clInfo( ntstrName, &pclMsg->clItem, &pclMsg->clToItem1 );
			cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
		}
		else if ( true == pclMsg->bCanNotice2 )
		{
			cltGameMsgResponse_RareItemFromTreasureBox clInfo( ntstrName, &pclMsg->clItem, &pclMsg->clToItem2 );
			cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
		}
	}
	else
	{
		bool bSendRareItemDialog = false;

		switch ( pclMsg->clItem.siUnique ) 
		{
			// [����] : 2010�ų��̺�Ʈ - ������Ű�� ������
		case ITEMUNIQUE( 13063 ):
			{
				if ( ITEMUNIQUE( 13658 ) == pclMsg->clToItem1.siUnique )	// ��Ű����[�̺�Ʈ]
				{
					bSendRareItemDialog = true;
				}
			}
			break;
			// �ų� ���ָӴ� (�븸����)
		case ITEMUNIQUE(13324):
			{
				if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(24102) )	// �����̵��̿��(����)
				{
					bSendRareItemDialog = true;
				}
			}
			break;
			// ���ݸ� ����
		case ITEMUNIQUE(8126):
			{
				if ( pclClient->IsWhereServiceArea( ConstServiceArea_Japan ) == true )
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(2756)	)	// ���� Ŭ�ι�2
					{
						bSendRareItemDialog = true;
					}
				}
				else //if ( pclClient->IsWhereServiceArea( ConstServiceArea_English ) == true )
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(5370)		// �ູ�� ��
						|| pclMsg->clToItem1.siUnique == ITEMUNIQUE(2756)	// ���� Ŭ�ι�2
						)
					{
						bSendRareItemDialog = true;
					}
				}
			}
			break;
			// ���� ĵ�� �ڽ�
		case ITEMUNIQUE(8128):
			{
				if ( pclClient->IsWhereServiceArea( ConstServiceArea_Japan ) == true )
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(2756) )	// ����� ����Ŭ�ι�
					{
						bSendRareItemDialog = true;
					}
				}
				else if ( pclClient->IsWhereServiceArea( ConstServiceArea_Taiwan ) == true )
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(5370)		// �ູ�� ��
						|| pclMsg->clToItem1.siUnique == ITEMUNIQUE(2756)	// ���� Ŭ�ι�2
						)
					{
						bSendRareItemDialog = true;
					}
				}
				else //if ( pclClient->IsWhereServiceArea( ConstServiceArea_English | ConstServiceArea_USA ) == true )
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(5370)		// �ູ�� ��
						|| pclMsg->clToItem1.siUnique == ITEMUNIQUE(2756)	// ���� Ŭ�ι�2
						)
					{
						bSendRareItemDialog = true;
					}
				}
			}
			break;

		case ITEMUNIQUE(13325):		// ��� ����
			{
				if( pclMsg->clToItem1.siUnique == ITEMUNIQUE(15900) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(24098) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(2760) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5710) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5715) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(1803) || 
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5412) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(1801)
					)
				{
					bSendRareItemDialog = true;
				}
			}
			break;

		case ITEMUNIQUE(13331):
			{
				if (pclMsg->clToItem2.siUnique == ITEMUNIQUE(12506))
					bSendRareItemDialog = true;
			}
			break;
			// �������ڿ��� ���ڴ� �Ŀ��� ���� ������ ���� (KOREA)
		case ITEMUNIQUE(13326):
			{
				if(pclClient->IsWhereServiceArea( ConstServiceArea_Korea))
				{
					if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(13350)) // ���ڴ� �Ŀ��� ����
						bSendRareItemDialog = true;
				}
			}
			break;
		case ITEMUNIQUE(13333): // ���� ���� ����.
			{
				if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(12531) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5748) )
					bSendRareItemDialog = true;
			}
			break;
		case ITEMUNIQUE(13335):
			{
				if ( pclMsg->clToItem1.siUnique == ITEMUNIQUE(5695)  ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(13305) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(13306) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5690)  ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(13317) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(5685)  ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(13320) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(13330) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(15916) ||
					pclMsg->clToItem1.siUnique == ITEMUNIQUE(12506)	 )
					bSendRareItemDialog = true;
			}
			break;
		case ITEMUNIQUE(13359):	// 3�� ���ָӴ�
			{
				if ( pclMsg->clToItem2.siUnique == ITEMUNIQUE(15918) )	// ���ﰡ��
					bSendRareItemDialog = true;
			}
			break;
		}

		if ( bSendRareItemDialog == true )
		{

			NTCHARString32 ntstrName( pclCM->CR[id]->GetName() );
			if ( pclMsg->clToItem2.siUnique == ITEMUNIQUE(12506)  || pclMsg->clToItem2.siUnique == ITEMUNIQUE(15918))
			{
				cltGameMsgResponse_RareItemFromTreasureBox clInfo( ntstrName, &pclMsg->clItem, &pclMsg->clToItem2 );
				cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo), (BYTE*)&clInfo);
				pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
			}
			else
			{
				cltGameMsgResponse_RareItemFromTreasureBox clInfo( ntstrName, &pclMsg->clItem, &pclMsg->clToItem1 );
				cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo), (BYTE*)&clInfo);
				pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
			}

		}
	}

	// ������ ��� ��踦 ������Ʈ �Ѵ�. 
	pclItemManager->AddUseNum(pclMsg->clItem.siUnique, 1);

	// ���ο� ��� - ������ ���
	//NStatistics_Add("Item", pclMsg->clItem.siUnique, "UseNum", 1);


/*	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // �������� ����.(�����ʿ�)
		// param1		== ������1�� ��ġ, 
		// param1		== ������1�� ����ũ, 
		// param3		== ������1�� ����, 
		// pszParam1	== ������2�� ��ġ, ����ũ, ����. => <���� �𸣰ڴ�!>
		TCHAR str[50];
		StringCchPrintf(str, sizeof(str), "pos: %d Unique: %d Num: %d",
										   pclMsg->siToItemPos2,
										   pclMsg->clToItem2.siUnique, 
										   pclMsg->siGetItemNumber2);
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_TREASUREBOX_OPEN_USED, 
							 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
							 pclMsg->siToItemPos1, pclMsg->clToItem1.siUnique, pclMsg->siGetItemNumber1, 0, 0, 
							 str, NULL);
	}*/

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// ���� ���α�
		// param1 = �κ��丮 ��ġ
		// param2 = Ű ����ũ
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_TREASUREBOX_OPEN_USED, 
							0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUse_Item, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
							pclMsg->siItemPos, pclMsg->clUse_KeyItem.siUnique, 0, 0, 0, 
							NULL, NULL);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		if( pclMsg->clUse_KeyItem.siUnique > 0 )
		{
			// Ű ���α�
			// param1 = �κ��丮 ��ġ
			// praam2 = ���� ����ũ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
								USEITEM_REASON_OPENBOX_KEY, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUse_KeyItem, pclMsg->clKeyItem.siItemNum, 0, 0, 0, 0, 0, 
								pclMsg->siKeyItemPos, pclMsg->clUse_Item.siUnique, pclMsg->clAdd_ToItem1.siUnique, pclMsg->clAdd_ToItem2.siUnique, 0, 
								NULL, NULL);
		}
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		if( pclMsg->clAdd_ToItem1.siUnique > 0 )
		{
			// ���� ������ �α� - ù��°
			// param1 = �κ��丮 ��ġ
			// param2 = �ڽ� ����ũ
			// param3 = Ű ����ũ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM, 
								INPUTITEMPERSON_OPTION_OPENBOX, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clAdd_ToItem1, pclMsg->clToItem1.siItemNum, 0, 0, 0, 0, 0, 
								pclMsg->siToItemPos1, pclMsg->clUse_Item.siUnique, pclMsg->clUse_KeyItem.siUnique, 0, 0, 
								NULL, NULL);
		}
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		if( pclMsg->clAdd_ToItem2.siUnique > 0 )
		{
			// ���� ������ �α� - �ι�°
			// param1 = �κ��丮 ��ġ
			// param2 = �ڽ� ����ũ
			// param3 = Ű ����ũ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM, 
								INPUTITEMPERSON_OPTION_OPENBOX, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clAdd_ToItem2, pclMsg->clToItem2.siItemNum, 0, 0, 0, 0, 0, 
								pclMsg->siToItemPos2, pclMsg->clUse_Item.siUnique, pclMsg->clUse_KeyItem.siUnique, 0, 0, 
								NULL, NULL);
		}
	}
}

//[�߰� : Ȳ���� 2008. 1. 30 => ���� ����(����)�� ����. DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM(sPacketHeader* pPacket)
{
	sDBResponse_Move_Item* pclMsg = (sDBResponse_Move_Item*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( false == pclCM->IsValidID( id ) )
		return;

	if( pclMsg->siInvenItemPos < 0 || pclMsg->siInvenItemPos >= MAX_ITEM_PER_PERSON )	return;
	if( pclMsg->siBoxItemPos < 0 || pclMsg->siBoxItemPos >= MAX_ITEM_TREASURE_BOX )		return;

	cltPersonInfo* pPersonInfo = pclCM->CR[id]->pclCI;

	cltItem* InvenItem = &pPersonInfo->clCharItem.clItem[pclMsg->siInvenItemPos];	

	cltItem* BoxItem = NULL;
	if(pclMsg->type)
	{
		if(pclCM->CR[id]->pclTreasureBoxItem)	BoxItem = &pclCM->CR[id]->pclTreasureBoxItem->clItem[pclMsg->siBoxItemPos];
	}
	else
	{
		if(pclCM->CR[id]->pclSpaceBoxItem)		BoxItem = &pclCM->CR[id]->pclSpaceBoxItem->clItem[pclMsg->siBoxItemPos];
	}
	if(BoxItem == NULL)			return;
	
	InvenItem->Init();
	InvenItem->Set(&pclMsg->clInvenItem);

	BoxItem->Init();
	BoxItem->Set(&pclMsg->clBoxItem);

	// ���� ���ڷ� ȸ��
	if( TYPE_SPACE_BOX == pclMsg->type ) 
	{
		cltGameMsgResponse_Keep_Box_Move_Item clInfo( TYPE_SPACE_BOX, pclMsg->siInvenItemPos, &pclMsg->clInvenItem, pclMsg->siBoxItemPos, &pclMsg->clBoxItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}
	// ���� ���ڷ� ȸ��
	else if( TYPE_TREASURE_BOX == pclMsg->type )
	{
		cltGameMsgResponse_Keep_Box_Move_Item clInfo( TYPE_TREASURE_BOX, pclMsg->siInvenItemPos, &pclMsg->clInvenItem, pclMsg->siBoxItemPos, &pclMsg->clBoxItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2008-4-18 ] // ���� ���ڿ� �ִ� ������ �α�.
		// param1 == �κ��丮�� ������ ��ġ.
		// param2 == ���������� ������ ��ġ.
		// param3 == �������ڿ� ���� ����.
		// param4 == �������� Ÿ��
		cltServer* pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SPACEBOX, LOGCOMMAND_INDEX_TO_SPACEBOX, 
			pclMsg->type, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clMoveItem, pclMsg->clInvenItem.siItemNum, 0, 0, 0, 0, 0, 
			pclMsg->siInvenItemPos, pclMsg->siBoxItemPos, pclMsg->clBoxItem.siItemNum, pclMsg->type, 0, NULL, NULL);
	}
}

//[�߰� : Ȳ���� 2008. 1. 30 => ���� ����(����)�� ȸ��.DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM(sPacketHeader* pPacket)
{
	sDBResponse_Move_Item* pclMsg = (sDBResponse_Move_Item*)pPacket;
	
	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( false == pclCM->IsValidID(id) )
	{
		return;
	}
		
	if( pclMsg->siInvenItemPos < 0 || pclMsg->siInvenItemPos >= MAX_ITEM_PER_PERSON )	return;
	if( pclMsg->siBoxItemPos < 0 || pclMsg->siBoxItemPos >= MAX_ITEM_TREASURE_BOX )		return;
	
	cltPersonInfo* pPersonInfo = pclCM->CR[id]->pclCI;

	cltItem* InvenItem = &pPersonInfo->clCharItem.clItem[pclMsg->siInvenItemPos];	

	cltItem* BoxItem = NULL;
	if(pclMsg->type)
	{
		if(pclCM->CR[id]->pclTreasureBoxItem)	BoxItem = &pclCM->CR[id]->pclTreasureBoxItem->clItem[pclMsg->siBoxItemPos];
	}
	else
	{
		if(pclCM->CR[id]->pclSpaceBoxItem)		BoxItem = &pclCM->CR[id]->pclSpaceBoxItem->clItem[pclMsg->siBoxItemPos];
	}
	if(BoxItem == NULL)				return;

	BoxItem->Init();
	BoxItem->Set(&pclMsg->clBoxItem);

	InvenItem->Init();
	InvenItem->Set(&pclMsg->clInvenItem);

	// ���� ���ڷ� ȸ��
	if( TYPE_SPACE_BOX == pclMsg->type ) 
	{
		cltGameMsgResponse_Recovery_Box_Move_Item clInfo( TYPE_SPACE_BOX, pclMsg->siInvenItemPos, &pclMsg->clInvenItem, pclMsg->siBoxItemPos, &pclMsg->clBoxItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// [����] �޸� ���� �ý��� - �������ڿ��� �������� ã���� �޸� ��� ���������� �˻� �ϰ� �´ٸ� ���׷��̵� ���ش�.
		if( NULL != pclClient->pclDormancySystem)
		{
			CDormancyEquipItemRewardServer *pclDormancyServer = (CDormancyEquipItemRewardServer *)pclClient->pclDormancySystem->GetDormancyEquipItemReward();
			if( NULL != pclDormancyServer)
			{
				if( TRUE == pclDormancyServer->IsDormancyEquipItem(InvenItem->siUnique))
				{
					pclDormancyServer->UpgradeItem(pclCM->CR[id], InvenItem->siUnique, pclMsg->siInvenItemPos, InvenItem->GetType(pclClient->pclItemManager));
				
				}
			}
		}

	}
	// ���� ���ڷ� ȸ��
	else if( TYPE_TREASURE_BOX == pclMsg->type )
	{
		cltGameMsgResponse_Recovery_Box_Move_Item clInfo( TYPE_TREASURE_BOX, pclMsg->siInvenItemPos, &pclMsg->clInvenItem, pclMsg->siBoxItemPos, &pclMsg->clBoxItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	if(pclMsg->siResult == 1)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2008-4-18 ] // ���� ���ڿ� �ִ� �������� �κ��丮��.
			// param1 == �κ��� ��ġ.
			// param2 == ���������� ��ġ.
			// param3 == �������ڿ� ���� ����.
			// param4 == �������� Ÿ��
			cltServer* pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SPACEBOX, LOGCOMMAND_INDEX_SPACEBOX_TO_INVENTORY, 
				pclMsg->type, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clMoveItem, pclMsg->clInvenItem.siItemNum, 0, 0, 0, 0, 0, 
				pclMsg->siInvenItemPos, pclMsg->siBoxItemPos, pclMsg->clBoxItem.siItemNum, pclMsg->type, 0, NULL, NULL);
		}
	}
}

//[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ������ ����Ʈ. DB->S]
void  cltServer::DoMsg_DBMSG_RESPONSE_SPACE_BOX_ITEM_LIST(sPacketHeader* pPacket)
{
	sDBResponse_Space_Box_List* pclMsg = (sDBResponse_Space_Box_List*)pPacket;

	SI32 id = pclMsg->usCharID; 

	if( false == pclCM->IsValidID(id) )
	{
		return;
	}

	if(pclCM->CR[id]->pclSpaceBoxItem == NULL)			return;
	if(pclCM->CR[id]->pclTreasureBoxItem == NULL)		return;

	pclCM->CR[id]->pclSpaceBoxItem->Set(&pclMsg->clSpaceBoxItem);
	pclCM->CR[id]->pclTreasureBoxItem->Set(&pclMsg->clTreasureBoxItem);

	// ���� ���� ������ ������ ����Ǹ� �ٽ� ����Ʈ�� ��û�ϱ� ���� ���.
	bool RecallMsg = false;
	
	//[����] �������ڿ� �Ⱓ�� ���� ������ �����ϱ�.	
	cltSpaceBox*	pclSpaceBoxitem = pclCM->CR[id]->pclSpaceBoxItem;
	for (SI32 i = 0 ; i < MAX_ITEM_SPACE_BOX ; i ++ )
	{
		SI32 itemunique = pclSpaceBoxitem->clItem[i].siUnique ;
		if ( itemunique > 0 )
		{
			if ( pclSpaceBoxitem->clItem[i].IsHaveUseDay() )  //[����] ���� ���Ⱓ 3�Ϲ̸� �˸�
			{
				SI32 useableDay = 0;
				BOOL rVal = GetItemUseAbleDay(&pclSpaceBoxitem->clItem[i],&useableDay);

				if(pclSpaceBoxitem->clItem[i].IsSealingUp(pclItemManager) == true)
					continue;

				if(rVal == FALSE) continue;

				if(useableDay >= 3) continue; // ��밡�ɱⰣ�� 3�� �̻� �˳��ϸ� �н� 
				else if(useableDay >= 0)		 //  3�� �̸������� ��밡�� �Ⱓ�� �����ִٸ� Ŭ���̾�Ʈ�� ���
				{
					cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclSpaceBoxitem->clItem[i].siUnique, useableDay);
					cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
				}
				else if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
				{
					//KHY - 0723 - �Ⱓ������ �ı� ����.
					if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
					{

					}
					else
					{
						// ���ǰ�� �������� �ʴ´�. - by LEEKH
						if( pclSpaceBoxitem->clItem[i].clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
						{
							sDBRequest_Use_SpaceBox_Item useitem(id,pclCM->CR[id]->pclCI->GetPersonID(), i, &pclSpaceBoxitem->clItem[i], USEITEM_REASON_DATEOVER);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

							cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclSpaceBoxitem->clItem[i].siUnique, useableDay);
							cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );			

							RecallMsg = true;
						}
					}
				}
			}
		}
	}

	//[����] �������ڿ� �Ⱓ�� ���� ������ �����ϱ�.	
	cltTreasureBox* pclTreasureBox  = pclCM->CR[id]->pclTreasureBoxItem;
	for (SI32 i = 0 ; i < MAX_ITEM_TREASURE_BOX ; i ++ )
	{
		SI32 itemunique = pclTreasureBox->clItem[i].siUnique ;
		if ( itemunique > 0 )
		{
			if ( pclTreasureBox->clItem[i].IsHaveUseDay() )  //[����] ���� ���Ⱓ 3�Ϲ̸� �˸�
			{
				SI32 useableDay = 0;
				BOOL rVal = GetItemUseAbleDay(&pclTreasureBox->clItem[i],&useableDay);

				if(pclSpaceBoxitem->clItem[i].IsSealingUp(pclItemManager) == true)
					continue;

				if(rVal == FALSE) continue;

				if(useableDay >= 3) continue; // ��밡�ɱⰣ�� 3�� �̻� �˳��ϸ� �н� 
				else if(useableDay >= 0)		 //  3�� �̸������� ��밡�� �Ⱓ�� �����ִٸ� Ŭ���̾�Ʈ�� ���
				{
					cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclTreasureBox->clItem[i].siUnique, useableDay);
					cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
				}
				else if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
				{
					//KHY - 0723 - �Ⱓ������ �ı� ����.
					if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
					{

					}
					else
					{
						// ���ǰ�� �������� �ʴ´�. - by LEEKH
						if( pclTreasureBox->clItem[i].clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
						{
							sDBRequest_Use_Treasure_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), i, &pclTreasureBox->clItem[i], USEITEM_REASON_DATEOVER);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

							cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclTreasureBox->clItem[i].siUnique, useableDay);
							cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				

							RecallMsg = true;
						}
					}
				}
			}
		}
	}

	SI32 InvenCount		= 0;
	UI32 GetItemReason	= 0;

	// �������ڿ� ����ִ� ��ƼȦ �����۵� ����	
	pclSpaceBoxitem = pclCM->CR[id]->pclSpaceBoxItem;
	if(pclSpaceBoxitem)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_SPACE_BOX; ++InvenCount)	
		{
			GetItemReason = pclSpaceBoxitem->clItem[InvenCount].clItemCommon.clCommonInfo.uiGetItemReason;
			if( cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM == GetItemReason )
			{
				// ������ ����.  
				sDBRequest_Use_SpaceBox_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclSpaceBoxitem->clItem[InvenCount], USEITEM_REASON_DATEOVER);
				pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

				RecallMsg = true;
			}
		}
	}

	pclTreasureBox  = pclCM->CR[id]->pclTreasureBoxItem;
	if(pclTreasureBox)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_TREASURE_BOX; ++InvenCount)	
		{
			GetItemReason = pclTreasureBox->clItem[InvenCount].clItemCommon.clCommonInfo.uiGetItemReason;
			if( cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM == GetItemReason )
			{
				// ������ ����.  
				sDBRequest_Use_Treasure_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclTreasureBox->clItem[InvenCount], USEITEM_REASON_DATEOVER);
				pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

				RecallMsg = true;
			}
		}
	}

	// �������ڿ� ����ִ� �������ʴ� ����Ŭ�ι� �����۵� ����	
	pclSpaceBoxitem = pclCM->CR[id]->pclSpaceBoxItem;
	if(pclSpaceBoxitem)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_SPACE_BOX; ++InvenCount)	
		{
			if( ITEMUNIQUE(2755) == pclSpaceBoxitem->clItem[InvenCount].siUnique || 
				ITEMUNIQUE(2754) == pclSpaceBoxitem->clItem[InvenCount].siUnique )	
			{
				if( pclSpaceBoxitem->clItem[InvenCount].siUnique != siFourLeafUnique)
				{
					// ������ ����.  
					sDBRequest_Use_SpaceBox_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclSpaceBoxitem->clItem[InvenCount], USEITEM_REASON_DATEOVER);
					pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

					RecallMsg = true;
				}
			}
		}
	}

	pclTreasureBox  = pclCM->CR[id]->pclTreasureBoxItem;
	if(pclTreasureBox)
	{
		for(InvenCount = 0; InvenCount < MAX_ITEM_TREASURE_BOX; ++InvenCount)	
		{
			if( ITEMUNIQUE(2755) == pclTreasureBox->clItem[InvenCount].siUnique || 
				ITEMUNIQUE(2754) == pclTreasureBox->clItem[InvenCount].siUnique	)	
			{
				if( pclTreasureBox->clItem[InvenCount].siUnique != siFourLeafUnique)
				{
					// ������ ����.  
					sDBRequest_Use_Treasure_Item useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), InvenCount, &pclTreasureBox->clItem[InvenCount], USEITEM_REASON_DATEOVER);
					pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

					RecallMsg = true;
				}
			}
		}
	}

	if(false == RecallMsg)
	{
		cltGameMsgResponse_Space_Box_List clInfo( pclCM->CR[id]->pclSpaceBoxItem, pclCM->CR[id]->pclTreasureBoxItem );
		cltMsg clMsg(GAMEMSG_RESPONSE_SPACE_BOX_LIST, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);		
	}
	else
	{
		sDBRequest_Space_Box_List clSpace_Box_List( id, pclCM->CR[id]->pclCI->GetPersonID() );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clSpace_Box_List);
	}
	
}


// �������� ����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_USE_SPACEBOX_ITEM(sPacketHeader* pPacket)
{
	sDBResponse_Use_SpaceBox_Item* pclMsg = (sDBResponse_Use_SpaceBox_Item*)pPacket;

	if(0 > pclMsg->siResult)
		return;
	
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return;

	if (pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_SPACE_BOX)		
		return;

	if(pclCM->CR[id]->pclSpaceBoxItem == NULL)			return;

	//����� ���������� �������� �����Ѵ�.
	pclCM->CR[id]->pclSpaceBoxItem->clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

	//����� ���������� ������ ����Ʈ�� Ŭ���̾�Ʈ���� �����ش�.
	cltGameMsgResponse_Use_SpaceBox_Item clInfo( pclMsg->siItemPos, &pclMsg->clItem );
	cltMsg clMsg(GAMEMSG_RESPONSE_USE_SPACEBOX_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);		
}

// �������� ����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_USE_TREASURE_ITEM(sPacketHeader* pPacket)
{
	sDBResponse_Use_Treasure_Item* pclMsg = (sDBResponse_Use_Treasure_Item*)pPacket;

	if(0 > pclMsg->siResult)
		return;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return;

	if (pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_TREASURE_BOX )		
		return;

	if(pclCM->CR[id]->pclTreasureBoxItem == NULL)				return;

	pclCM->CR[id]->pclTreasureBoxItem->clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

	cltGameMsgResponse_Use_Treasure_Item clInfo( pclMsg->siItemPos, &pclMsg->clItem );
	cltMsg clMsg(GAMEMSG_RESPONSE_USE_TREASURE_ITEM, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);		
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONPUSHITEM(sPacketHeader* pPacket)
{
	sDBResponse_SummonPushItem* pclMsg = (sDBResponse_SummonPushItem*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	
	if ( 0 >= pclMsg->m_siResult )
	{
		return;
	}

	SI32 siID = pclMsg->m_usCharID;
	if ( FALSE == pclCM->IsValidID(siID) )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}
	
	// Ȥ�� �̵��Ϸ��� ����� �ٸ���찡 ���� �� ������ 
	if ( pclchar->pclCI->GetPersonID() != pclMsg->m_siPersonID )
	{
		return;
	}

/*	SI16 siSummonIndex = pclMsg->m_siSummonIndex;
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}*/

	//cltSummon* pclsummon = (cltSummon*)pclchar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	cltSummon* pclsummon = (cltSummon*)pclchar->pclCI->clSummonInfo.GetSummonFromSummonID( pclMsg->m_siSummonID );
	if ( (NULL == pclsummon) || (0 >= pclsummon->siKind) || (MAX_KIND_NUMBER <= pclsummon->siKind) )
	{
		return;
	}

	SI32 siSummonID = pclchar->GetSummonID();
	if ( false == pclCM->IsValidID( siSummonID ) )
	{
		return;
	}

	SI08 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID( pclMsg->m_siSummonID );
	if(siSummonIndex < 0 || siSummonIndex >= MAX_SUMMON_OWN)		return;

	cltCharServer* pclSummonChar = (cltCharServer*)pclCM->CR[siSummonID];
	if ( NULL == pclSummonChar )
	{
		return;
	}

	// ����� �κ�
	SI16 siFrom = pclMsg->m_siFromItemPos;
	// ��ȯ�� �κ�
	SI16 siTo	= pclMsg->m_siToItemPos;

	// ����κ��� ��� ����â���� �̵��� �ȵǴϱ�
	if ( (MAX_SHAPE_ITEM >= siFrom) || (MAX_ITEM_PER_PERSON <= siFrom) )
	{
		return;
	}

	// ��ȯ�� ����â
	if ( (0 > siTo) || (MAX_SHAPE_ITEM <= siTo) )
	{
		return;
	}

	//---------------------------------------------
	// ������ ������Ʈ �Ѵ�. 
	//---------------------------------------------

	// ĳ���� ��� ������Ʈ �Ѵ�
	pclchar->pclCI->clCharItem.clItem[ siFrom ].Set( &pclMsg->m_clFromItem );
	// ��ȯ�� ��� ������Ʈ �Ѵ�
	pclchar->pclCI->clSummonInfo.SetSummonEquipItem( pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->m_siSummonID),
													 siTo, &pclMsg->m_clToItem );

	//---------------------------------------------
	// ��ȯ�� �ɷ�ġ ����� �ٽ� �ϵ��� �Ѵ�
	//---------------------------------------------
	pclSummonChar->SetParametaBoxAction( true );

	//----------------------------------------------
	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	//----------------------------------------------
	cltGameMsgResponse_PersonItemInfo clPersonItemInfo( siFrom, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->m_clFromItem, 0 );
	cltMsg clPersonMsg( GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clPersonItemInfo), (BYTE*)&clPersonItemInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clPersonMsg );

	cltGameMsgResponse_SummonChangeItem clSummonChangItem( siSummonIndex, siTo, &pclMsg->m_clToItem );
	cltMsg clSummonMsg( GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clSummonChangItem), (BYTE*)&clSummonChangItem );
	pclchar->SendNetMsg( (sPacketHeader*)&clSummonMsg );

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONPOPITEM(sPacketHeader* pPacket)
{
	sDBResponse_SummonPopItem* pclMsg = (sDBResponse_SummonPopItem*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 0 >= pclMsg->m_siResult )
	{
		return;
	}

	SI32 siID = pclMsg->m_usCharID;
	if ( FALSE == pclCM->IsValidID(siID) )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}

	// Ȥ�� �̵��Ϸ��� ����� �ٸ���찡 ���� �� ������ 
	if ( pclchar->pclCI->GetPersonID() != pclMsg->m_siPersonID )
	{
		return;
	}

	SI16 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->m_siSummonID);//pclMsg->m_siSummonIndex;
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	cltSummon* pclsummon = (cltSummon*)pclchar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if ( (NULL == pclsummon) || (0 >= pclsummon->siKind) || (MAX_KIND_NUMBER <= pclsummon->siKind) )
	{
		return;
	}

	SI32 siSummonID = pclchar->GetSummonID();
	if ( false == pclCM->IsValidID( siSummonID ) )
	{
		return;
	}

	cltCharServer* pclSummonChar = (cltCharServer*)pclCM->CR[siSummonID];
	if ( NULL == pclSummonChar )
	{
		return;
	}

	// ��ȯ�� �κ�
	SI16 siFrom = pclMsg->m_siFromItemPos;
	// ��� �κ�
	SI16 siTo	= pclMsg->m_siToItemPos;

	// ��ȯ��
	if ( (0 > siFrom) || (MAX_SHAPE_ITEM <= siFrom) )
	{
		return;
	}

	// ���
	if ( (MAX_SHAPE_ITEM >= siTo) || (MAX_ITEM_PER_PERSON <= siTo) )
	{
		return;
	}

	//---------------------------------------------
	// ������ ������Ʈ �Ѵ�. 
	//---------------------------------------------
	// ��ȯ�� ��� ������Ʈ �Ѵ�
	pclchar->pclCI->clSummonInfo.SetSummonEquipItem( siSummonIndex, siFrom, &pclMsg->m_clFromItem );
	// ĳ���� ��� ������Ʈ �Ѵ�
	pclchar->pclCI->clCharItem.clItem[ siTo ].Set( &pclMsg->m_clToItem );
	
	//---------------------------------------------
	// ��ȯ�� �ɷ�ġ ����� �ٽ� �ϵ��� �Ѵ�
	//---------------------------------------------
	pclSummonChar->SetParametaBoxAction( true );

	//----------------------------------------------
	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	//----------------------------------------------
	cltGameMsgResponse_SummonChangeItem clSummonChangItem( siSummonIndex, siFrom, &pclMsg->m_clFromItem );
	cltMsg clSummonMsg( GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clSummonChangItem), (BYTE*)&clSummonChangItem );
	pclchar->SendNetMsg( (sPacketHeader*)&clSummonMsg );

	cltGameMsgResponse_PersonItemInfo clPersonItemInfo( siTo, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->m_clToItem, 0 );
	cltMsg clPersonMsg( GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clPersonItemInfo), (BYTE*)&clPersonItemInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clPersonMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONITEM_STATUSCHANGE(sPacketHeader* pPacket)
{
	sDBResponse_SummonItem_StatusChange* pclMsg = (sDBResponse_SummonItem_StatusChange*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	//---------------------------------------------------------
	// �⺻���� üũ
	//---------------------------------------------------------

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32 siID = pclMsg->m_usCharID;
	if ( FALSE == pclCM->IsValidID(siID) )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}

	// Ȥ�� �ٸ� �ɸ����ϼ� �����Ƿ�
	if ( pclchar->pclCI->GetPersonID() != pclMsg->m_siPersonID )
	{
		return;
	}

	SI16 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->m_siSummonID);//pclMsg->m_siSummonIndex;
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
	{
		return;
	}

	SI32 siSummonID = pclchar->GetSummonID();
	if ( false == pclCM->IsValidID( siSummonID ) )
	{
		return;
	}

	cltCharServer* pclSummonChar = (cltCharServer*)pclCM->CR[siSummonID];
	if ( NULL == pclSummonChar )
	{
		return;
	}
	//---------------------------------------------------------
	// �������
	//---------------------------------------------------------

	// ��ȯ�� �κ�
	SI16 siPosition = pclMsg->m_siItemPos;

	// ��ȯ�� �κ� üũ
	if ( (0 > siPosition) || (MAX_SHAPE_ITEM <= siPosition) )
	{
		return;
	}

	//---------------------------------------------
	// ������ ������Ʈ �Ѵ�. 
	//---------------------------------------------
	// ��ȯ�� ��� ������Ʈ �Ѵ�
	pclchar->pclCI->clSummonInfo.SetSummonEquipItem( siSummonIndex, siPosition, &pclMsg->m_clItem );

	//---------------------------------------------
	// ��ȯ�� �ɷ�ġ ����� �ٽ� �ϵ��� �Ѵ�
	//---------------------------------------------
	pclSummonChar->SetParametaBoxAction( true );

	//----------------------------------------------
	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	//----------------------------------------------
	cltGameMsgResponse_SummonChangeItem clSummonChangItem( siSummonIndex, siPosition, &pclMsg->m_clItem );
	cltMsg clSummonMsg( GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clSummonChangItem), (BYTE*)&clSummonChangItem );
	pclchar->SendNetMsg( (sPacketHeader*)&clSummonMsg );

}
void cltServer::DoMsg_DBMSG_RESPONSE_REPAIRITEM(sPacketHeader* pPacket)
{
	sDBResponse_RepairItem* pclMsg = (sDBResponse_RepairItem*)pPacket;

	SI32 id			= pclMsg->m_usCharID;
	SI32 itempos	= pclMsg->m_siPos;
	if( itempos < 0 || itempos >= MAX_ITEM_PER_PERSON )						return;

	SI32 siItemCharID = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer* pclitemchar = pclCM->GetCharServer( siItemCharID );

	if( pclMsg->m_siResult == 1 )
	{
		if( pclitemchar )
		{
			pclitemchar->pclCI->clCharItem.clItem[itempos].Set( &pclMsg->m_clItem );

			cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclitemchar->pclCI->clCharItem.clItem[itempos], 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclitemchar->SendNetMsg((sPacketHeader*)&clMsg);

			if ( 0 < pclMsg->m_siRepairMoney )
			{
				pclitemchar->pclCI->clIP.SetMoney( pclMsg->m_siRepairerMoney );
				pclitemchar->SetUpdateSwitch(UPDATE_IP, true, 0);
			}

			pclitemchar->SetRepairShopData( false, NULL );

			cltGameMsgResponse_NewItemRepair clResult1( 1, pclitemchar->GetCharUnique(), &pclMsg->m_clItem, pclMsg->m_siType );
			cltMsg clNetMsg1( GAMEMSG_RESPONSE_NEWITEMREPAIR, sizeof(clResult1), (BYTE*)&clResult1 );
			pclitemchar->SendNetMsg( (sPacketHeader*)&clNetMsg1 );

			// �ֺ� ĳ���Ϳ��� ������û ��ʸ� ���쵵�� �Ѵ�.
			cltGameMsgResponse_NewItemRepair clResult2( 1, pclitemchar->GetCharUnique(), &pclMsg->m_clItem, 4 );
			cltMsg clNetMsg2( GAMEMSG_RESPONSE_NEWITEMREPAIR, sizeof(clResult2), (BYTE*)&clResult2 );
			pclitemchar->SendNeighbourMsg( &clNetMsg2, false );
		}
	}

	if( pclMsg->m_siResult == 1 )
	{
		SI32 siRepairCharID = pclCM->GetIDFromPersonID( pclMsg->m_siRepairPersonID );
		if( pclCM->IsValidID( siRepairCharID ) )
		{
			cltCharServer* pclrepairchar = pclCM->GetCharServer( siRepairCharID );
			if( pclrepairchar )
			{
				if ( 0 < pclMsg->m_siRepairMoney )
				{
					pclrepairchar->pclCI->clIP.SetMoney( pclMsg->m_siRepairPersonMoney );
					pclrepairchar->SetUpdateSwitch(UPDATE_IP, true, 0);
				}

				cltGameMsgResponse_NewItemRepair clResult( pclMsg->m_siResult, pclitemchar->GetCharUnique(), &pclMsg->m_clItem, pclMsg->m_siType );
				cltMsg clMsg(GAMEMSG_RESPONSE_NEWITEMREPAIR, sizeof(clResult), (BYTE*)&clResult);
				pclrepairchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_GIVEVILLAGEITEM(sPacketHeader* pPacket)
{
	// PCK : �α׸� ����� ���ؼ� �ۼ�.
	sDBResponse_GiveVillageItem* pclMsg = (sDBResponse_GiveVillageItem*)pPacket;

	// PCK : PersonID�� �ٰŷ� CharID�� ã��.(PersonID��������!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// param1 == ���Ⱓ
	// charparam1 == �����Ҷ� ����� �޽���
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_VILLAGEGIVEITEM, 
		0, pclchar, NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
		pclMsg->siUseDate, 0, 0, 0, 0, pclMsg->szMsg, NULL);
}

//[����] ȣ�ڻ��� => 2008-9-16
void cltServer::DoMsg_DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST(sPacketHeader* pPacket)
{
	sDBResponse_Amber_Box_Select_Item_List* pclMsg = (sDBResponse_Amber_Box_Select_Item_List*)pPacket;

	cltCharServer* pclchar = pclClient->pclCM->GetCharServer(pclMsg->m_siCharID);
	if ( NULL == pclchar )	return;
		
	cltGameMsgResponse_Amber_Box_Select_Item_List clInfo( pclMsg->m_clAmberboxItemList );
	cltMsg clInfoMsg( GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clInfoMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET(sPacketHeader* pPacket)
{
	sDBResponse_Amber_Box_Select_Item_Get* pclMsg = (sDBResponse_Amber_Box_Select_Item_Get*)pPacket;
	
	if( 0 >= pclMsg->m_siResult )	return;

	cltCharServer* pclchar = pclClient->pclCM->GetCharServer(pclMsg->m_siCharID);
	if ( NULL == pclchar )			return;

	if(false == pclMsg->m_clGetItem.CanPile(pclClient->pclItemManager))
	{
		cltItem	clItem;
		clItem.Set(&pclMsg->m_clGetItem);
		clItem.SetItemNum(1);

		for(SI32 Count = 0; Count < pclMsg->m_clGetItem.siItemNum; ++Count)
			InputItem( pclchar, &clItem, INPUTITEMPERSON_OPTION_AMBERBOX );
	}
	else
	{
		if ( 0 < pclMsg->m_siToItemPos && MAX_ITEM_PER_PERSON > pclMsg->m_siToItemPos )
		{
			pclchar->pclCI->clCharItem.clItem[pclMsg->m_siToItemPos].Set( &pclMsg->m_clToItem );
		}
	}

	if( 0 < pclMsg->m_siRemainItemPos && MAX_ITEM_PER_PERSON > pclMsg->m_siRemainItemPos )
	{
		pclchar->pclCI->clCharItem.clItem[pclMsg->m_siRemainItemPos].Set( &pclMsg->m_clRemainItem );
	}

	//��ǰ ����.
	/*
	if( ITEMUNIQUE(12531) == pclMsg->m_clGetItem.siUnique	|| 
		ITEMUNIQUE(13626) == pclMsg->m_clGetItem.siUnique	|| 
		ITEMUNIQUE(13627) == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(12532) == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(5748)  == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(5745)  == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(13356)  == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(13655)  == pclMsg->m_clGetItem.siUnique	||
		ITEMUNIQUE(13659)  == pclMsg->m_clGetItem.siUnique)
	{
	*/
	if ( (m_pclBoxItemMgr) && (TRUE == m_pclBoxItemMgr->IsInBoxItemCanNotice(pclMsg->m_clUseItem.siUnique, pclMsg->m_clGetItem.siUnique)) )
	{
		// pck : GM������ �������� ������������ �Ѵ�.
		SI32 gamemasterlevel = pclchar->GetGameMasterLevel();
		if( gamemasterlevel < BASIC_GAMEMASTER_LEVEL )
		{
			NTCHARString32 ntstrName( pclchar->GetName() );
			cltGameMsgResponse_RareItemFromTreasureBox clInfo2( ntstrName, &pclMsg->m_clUseItem, &pclMsg->m_clGetItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo2), (BYTE*)&clInfo2);
		
			// [��ȣ_NHN->NDOORS] �ѱ��ΰ�� 18�� �̻� �����鿡�Ը� ����
            if((IsWhereServiceArea(ConstServiceArea_Korea) == true))
				pclCM->SendAllAdultUserMsg((sPacketHeader*)&clMsg);
			else
				pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
		}
	}
	
	cltGameMsgResponse_Amber_Box_Select_Item_Get clInfo( pclMsg->m_siRemainItemPos, &pclMsg->m_clRemainItem,
														 pclMsg->m_siToItemPos,		&pclMsg->m_clToItem	);
	cltMsg clInfoMsg( GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clInfoMsg );

	// [�α��߰� : Ȳ���� 2008. 9. 30] // ȣ�ڻ��ڿ��� ���� ������
	// [���] : Param1 - ���� ����ũ
	SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_AMBER_BOX_GET_ITEM, 
							0, pclchar, NULL, 0, 0, 0, &pclMsg->m_clGetItem, 0, 0, 0, 0, 0, 0, 
							pclMsg->m_clUseItem.siUnique, 0, 0, 0, 0, 
							NULL, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWSELECTBOX_ITEM_GET(sPacketHeader* pPacket)
{
	sDBResponse_NewSelectBox_Item_Get* pclMsg = (sDBResponse_NewSelectBox_Item_Get*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32 siGetCharID = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	if ( siGetCharID != pclMsg->m_uiCharID )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( siGetCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	// ����ϰ� ���� ���� ������ ������ �����Ѵ�
	if ( (0 < pclMsg->m_siBoxItemPos) && (MAX_ITEM_PER_PERSON > pclMsg->m_siBoxItemPos) )
	{
		pclchar->pclCI->clCharItem.clItem[ pclMsg->m_siBoxItemPos ].Set( &pclMsg->m_clBoxItem );
	}

	// ���� ������ ������ �����Ѵ�
	if ( (0 < pclMsg->m_siGetItemPos) && (MAX_ITEM_PER_PERSON > pclMsg->m_siGetItemPos) )
	{
		pclchar->pclCI->clCharItem.clItem[ pclMsg->m_siGetItemPos ].Set( &pclMsg->m_clGetItem );
	}

	if ( 0 < pclMsg->m_siCanNotice )
	{
		NTCHARString32 strName( pclchar->GetName() );
		cltGameMsgResponse_RareItemFromTreasureBox clInfo2( strName, &pclMsg->m_clUseItem, &pclMsg->m_clToItem );
		cltMsg clMsg( GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX, sizeof(clInfo2), (BYTE*)&clInfo2 );
		pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
	}

	cltGameMsgResponse_NewSelectBox_GetItem clInfo( &pclMsg->m_clBoxItem, pclMsg->m_siBoxItemPos, &pclMsg->m_clGetItem, pclMsg->m_siGetItemPos, &pclMsg->m_clToItem );
	cltMsg clMsg( GAMEMSG_RESPONSE_NEWSELECTBOX_GETITEM, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );

	pclLog->FilePrint( TEXT("Config\\NewYear.log"), TEXT("PersonID=%d\tBoxItemUnique=%d\tSelectIndex=%d\tGetItemUnique=%d\tGetItemNum=%d"), 
					pclMsg->m_siPersonID,
					pclMsg->m_clUseItem.siUnique, pclMsg->m_siSelectIndex, 
					pclMsg->m_clToItem.siUnique, pclMsg->m_clToItem.siItemNum);

	// �α�
	// siParam1 = ������ �ε�����
	// siParam2 = ����� ������(�ڽ� ������)
	SendLog_WriteLogToDB( LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_NEWSELECTBOX_GET_ITEM, 
						0, pclchar, NULL, 0, 0, 0, &pclMsg->m_clToItem, 0, 0, 0, 0, 0, 0, 
						pclMsg->m_siSelectIndex, pclMsg->m_clUseItem.siUnique, 0, 0, 0, 
						NULL, NULL);

}

