//---------------------------------
// 2004/8/17 ������
//---------------------------------

#include "Char\CharManager\CharManager.h"


#include "..\Server\Server.h"

#include "..\Common\Map\Map.h"
#include "..\Common\Father\Father.h"
#include "..\Common\VoteMgr\VoteMgr.h"
#include "..\Common\Skill\Skill-Manager.h"

#include "..\Common\Order\Order.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "MsgType-Horse.h"
#include "Msg/MsgType-Vote.h"
#include "Msg/MsgType-Friend.h"
#include "Msg/MsgType-Summon.h"

#include "../../Server/AuthServer/AuthMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Stock.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Summon.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "..\Notice\Notice.h"
#include "HashTable/HashTable_StringInt.h"
#include "HashTable/HashTable_IntInt.h"



void cltServer::DoMsg_DBMSG_RESPONSE_SETSUMMON(sPacketHeader* pPacket)
{
	sDBResponse_SetSummon* pclMsg = (sDBResponse_SetSummon *)pPacket;

	SI32 id	= pclMsg->usCharID;
	// ĳ���� �α׾ƿ��� �Ҷ��� SetSummon�� ȣ���ϱ� ������ ValidID�� ���� üũ�Ѵ�.
	if( pclCM->IsValidID(id) != TRUE )	return; 

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( pclchar == NULL )										return;
	if( pclchar->pclCI->GetPersonID() != pclMsg->siPersonID)	return;

	if( pclMsg->siResult == 1)
	{
		SI16 siSummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);

		cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummon(siSummonIndex);

		cltSummon* pclLogSummon = &pclMsg->clSummon;

		if( pclLogSummon == NULL)
			return;

		SI32 siOriWeaponStoneNum = 0;
		SI32 siOriDefenseStoneNum  = 0;
		if( NULL != pclSummon)
		{
			siOriWeaponStoneNum = pclSummon->siAttackWearStoneNum;
			siOriDefenseStoneNum = pclSummon->siDefenseWearStoneNum;
		}
		switch(pclMsg->siReason)
		{
		case SETSUMMON_REASON_MAKE:
			{
				// ��ȯ���� �߰��ϴ� DB����� ������.
				pclchar->bIsNowAddSummonThroughDB = false;

				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				// ó�� ��ȯ���� �����ϴ� ���̹Ƿ�, �������� DB�� ������ SummonIndex�� ����Ѵ�.
				cltSimpleSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonBase(pclMsg->siSummonIndex);

				cltSimpleSummon clSimpleSummon;
				clSimpleSummon.siKind = pclMsg->clSummon.siKind;
				clSimpleSummon.siLevel = pclMsg->clSummon.clIP.siLevel;
				clSimpleSummon.siSummonID = pclMsg->clSummon.siSummonID;
				MStrCpy( clSimpleSummon.szName, pclMsg->clSummon.szName, MAX_SUMMON_NAME );

				if(clSimpleSummon.siSummonID > 0 )
				{
					pclSummon->Set(&clSimpleSummon);

					cltGameMsgResponse_BaseSummon clInfo(pclCM->CR[id]->GetCharUnique(), pclMsg->siSummonIndex, &clSimpleSummon);
					cltMsg clMsg(GAMEMSG_RESPONSE_BASESUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				if(pclClient->IsCountrySwitch(Switch_SummonHouse))
				{
					SI32 siSummonIndex;
					pclchar->pclCI->clSummonInfo.GetEmptySummonIndex(&siSummonIndex);

					if(siSummonIndex >= 0)
					{
						sDBRequest_SummonSlotIn clMsg(id, pclchar->pclCI->GetPersonID(), siSummonIndex, pclMsg->clSummon.siSummonID );
						pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
				else
				{
					SI32 siSummonIndex;
					pclchar->pclCI->clSummonInfo.GetEmptySummonIndex(&siSummonIndex);

					if(siSummonIndex >= 0)
					{
						sDBRequest_SummonSlotIn clMsg(id, pclchar->pclCI->GetPersonID(), siSummonIndex, pclMsg->clSummon.siSummonID );
						pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
			}
			break;

		case SETSUMMON_REASON_UPDATE:
			{
				// ��ȯ�� �̸��� ����Ǹ� ȣ��ȴ�. ���� �α׸� ����� ���� ����!
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 9. 7] // ��ȯ�� ��ȭ �α׾���. 
					// SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_UPDATE, 
					//						0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->clSummon.siUnique, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					//						0, 0, 0, 0, 0, NULL, NULL);
				}
			}
			break;
		case SETSUMMON_REASON_FREE:
		case SETSUMMON_REASON_DIE:
			{
				if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
				{
					// ��ȯ���� ������ �������� ������ �����Ѵ�.
					if( pclchar->pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )
					{
						pclchar->TransformSummon( pclCM, GetSummonTransformManager() );
					}
				}
				//---------------------------------------------
				// ��ȯ���� �����Ǿ��־���Ѵ�.
				//---------------------------------------------
				SI32 siSummonID = pclCM->CR[id]->GetSummonID();
				if(pclCM->IsValidID(siSummonID)  == TRUE )
				{
					if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex)
					{
						//---------------------------------------------
						// ���ӿ��� ��ȯ���� �����. 
						//---------------------------------------------
						pclCM->CR[siSummonID]->DeleteInCell();
						pclCM->DeleteChar(siSummonID);
						//==========================================
						// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
						//==========================================
						pclCM->CR[id]->siChildCharUnique  = 0;
						pclCM->CR[id]->siSummonIndex	  = 0;

						// �������׵� ������ ���Ž�Ų��.
						cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}

				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				cltSummon*			pclSummon		= pclchar->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clFreeSummon.siSummonID);
				cltSimpleSummon*	pclSimpleSummon = pclchar->pclCI->clSummonInfo.GetSimpleSummonFromSummonID(pclMsg->clFreeSummon.siSummonID);

				if( pclMsg->siReason == SETSUMMON_REASON_FREE ) 
				{
					if( pclSummon )					pclSummon->Init();
					if( pclSimpleSummon ) 			pclSimpleSummon->Init();
					pclLogSummon = &pclMsg->clFreeSummon;
				}

				// Ŭ���̾�Ʈ�� �˸���. (�����ֿ���) 
				cltGameMsgResponse_SummonFree clinfo(pclCM->CR[id]->GetCharUnique(), pclMsg->clSummon.siSummonID);
				cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONFREE, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				// ��ȯ���� �׾������� Ŭ���̾�Ʈ�� �޽����� �˷��ش�.
				if(pclMsg->siReason == SETSUMMON_REASON_DIE)
					SendServerResponseMsg(0, SRVAL_SUMMONDIE,  0, 0, pclCM->CR[id]->GetCharUnique());

				// �����̴� ĳ���͸� ����ڷ� �����.
				pclCM->CR[id]->siSelectedCharIndex = -1 ;
			}
			break;

		case SETSUMMON_REASON_TAKEIN:
			{
				//---------------------------------------------
				// ��ȯ���� �����Ǿ��־���Ѵ�.
				//---------------------------------------------
				SI32 siSummonID = pclCM->CR[id]->GetSummonID();
				if(pclCM->IsValidID(siSummonID)  == TRUE)
				{
					if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex)
					{
						if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
						{
							// ��ȯ���� ������ �������� ������ �����Ѵ�.
							if( pclchar->pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )
							{
								pclchar->TransformSummon( pclCM, GetSummonTransformManager() );
								siSummonID = pclchar->GetSummonID();
							}
						}

						//---------------------------------------------
						// ���ӿ��� ��ȯ���� �����. 
						//---------------------------------------------
						if ( pclCM->IsValidID(siSummonID) )
						{
							pclCM->CR[siSummonID]->DeleteInCell();
							pclCM->DeleteChar(siSummonID);
						}
						//==========================================
						// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
						//==========================================
						pclCM->CR[id]->siChildCharUnique	= 0;
						pclCM->CR[id]->siSummonIndex		= 0;

						// �������׵� ������ ���Ž�Ų��.
						cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);

						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}

				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
				if(pclSummon)
				{
					pclSummon->Set(&pclMsg->clSummon);
					cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
					cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				// �����̴� ĳ���͸� ����ڷ� �����.
				pclCM->CR[id]->siSelectedCharIndex = -1 ;
			}
			break;
		case SETSUMMON_REASON_TAKEOUT:
			{
				//---------------------------------------------
				// ��ȯ���� �̹� ������ ���� �ִ´�.
				//---------------------------------------------
				SI32 siSummonID = pclCM->CR[id]->GetSummonID();
				cltSummon *pclSummon = NULL ;
				if(pclCM->IsValidID(siSummonID)  == TRUE )
				{
					if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
					{
						// ��ȯ���� ������ �������� ������ �����Ѵ�.
						if( pclchar->pclCI->clSummonInfo.IsSummonTranform( pclCM->CR[id]->siSummonIndex ) )
						{
							pclchar->TransformSummon( pclCM, GetSummonTransformManager() );
							siSummonID = pclchar->GetSummonID();
						}
					}

					SI32 oldindex = pclCM->CR[id]->siSummonIndex ;
					//--------------------------------------------
					//DB�� ������Ʈ�����ش�.
					//--------------------------------------------
					((cltCharServer*)pclCM->CR[id])->SendDBSummon(SETSUMMON_REASON_UPDATE, oldindex);

					//---------------------------------------------
					// ���ӿ��� ��ȯ���� �����. 
					//---------------------------------------------
					pclCM->CR[siSummonID]->DeleteInCell();
					pclCM->DeleteChar(siSummonID);
					//==========================================
					// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
					//==========================================
					pclCM->CR[id]->siChildCharUnique	= 0;
					pclCM->CR[id]->siSummonIndex		= 0;

					// �������׵� ������ ���Ž�Ų��.
					cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

					pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(oldindex);
					if(pclSummon)
					{
						pclSummon->siStatus = SUMMON_STATUS_TAKEIN ;
						pclSummon->Set(pclSummon);
						cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
						cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}

				//---------------------------------------------
				// ��ȯ���� �����ϰ� ���ϰ� ������ �����Ѵ�.
				//---------------------------------------------
				siSummonID = ((cltCharServer*)(pclCM->CR[id]))->CreateSummon(&pclMsg->clSummon);
				if(pclCM->IsValidID(siSummonID)  == TRUE)
				{
					//==========================================
					// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
					//==========================================
					pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
					if(pclSummon)
					{
						pclSummon->Set(&pclMsg->clSummon);
						cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
						cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}

					pclCM->CR[id]->siChildCharUnique	= siSummonID;
					pclCM->CR[id]->siSummonIndex		= siSummonIndex;

					cltCharServer *pclSummon = (cltCharServer*)pclCM->GetCharServer(siSummonID);
					if( NULL != pclSummon)
					{
						pclSummon->ParametaBoxAction();
					}

					{
						// �������׵� ������ ���Ž�Ų��.
						cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}	

				// �����̴� ĳ���͸� ����ڷ� �����.
				pclCM->CR[id]->siSelectedCharIndex = -1 ;
			}
			break;
		case SETSUMMON_REASON_SUMMONSTON:// ��ȯ�� ������������ ��������� 
			{
				cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
				// ���� ���� ���� ������ ���� �Ѵ�.
	
				pclSummon->siAttackWearStoneNum = pclMsg->clSummon.siAttackWearStoneNum;
				pclSummon->siDefenseWearStoneNum = pclMsg->clSummon.siDefenseWearStoneNum;
				pclLogSummon = pclSummon;
				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				if(&pclMsg->clSummon)
				{					
					pclSummon->Set(pclSummon);
					cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
					cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				//---------------------------------------------
				// ��ȯ���� �����Ǿ� ���� ������ �����ϰ� �����Ѵ�.
				//---------------------------------------------
				SI32 siSummonID = pclCM->CR[id]->GetSummonID();
				if(pclCM->IsValidID(siSummonID)  == FALSE)
				{
					//---------------------------------------------
					// ��ȯ���� �����ϰ� ���ϰ� ������ �����Ѵ�.
					//---------------------------------------------
					siSummonID = ((cltCharServer*)(pclCM->CR[id]))->CreateSummon(pclSummon);
					if(pclCM->IsValidID(siSummonID)  == TRUE)
					{
						pclCM->CR[id]->siChildCharUnique = siSummonID;
						pclCM->CR[id]->siSummonIndex     = siSummonIndex;

						pclCM->CR[siSummonID]->ParametaBoxAction();

						{
							// �������׵� ������ ���Ž�Ų��.
							cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
							cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
							// ���� �޼����� �����ش�
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}

				// ���� �޼����� �����ش�
				SendServerResponseMsg(0, SRVAL_SUMMONSUCCESS_USESTON, 0, 0, pclCM->CR[id]->GetCharUnique() );
			}
			break;
		case SETSUMMON_REASON_CHARGESTAMINA:	// PCK - ��ȯ�� ���¹̳� ���� (08.07.23)
			{
				if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
				{
					// ��ȯ���� ������ �������� ���׹̳� ������ ����.
					if( pclchar->pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )
					{
						break;
					}
				}

				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);

				// ���׹̳� ������ ������Ʈ �Ѵ�.
				if(pclSummon)
				{
					pclSummon->clIP.SetLuk( pclMsg->clSummon.clIP.GetLuk() );

					cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
					cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

					// ���� �޼����� �����ش�
					((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMONSUCCESS_CHARGESTAMINA,  0, 0, id);
				}				
			}
			break;
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog) && pclLogSummon != NULL) 
		{
			// PCK - ��ȯ���� ���¸� �α׷� �����. 
			// PCK : �߰� - ��ȯ���� ����, ���� �߰� (09.07.30)
			TCHAR szBA[50];
			ZeroMemory(szBA, sizeof(szBA));
			StringCchPrintf(szBA, sizeof(szBA), TEXT("Level:%d, Str:%d, Dex:%d, Vit:%d"),	
				pclLogSummon->clIP.GetLevel(), pclLogSummon->clIP.GetStr(), pclLogSummon->clIP.GetDex(), 
				pclLogSummon->clIP.GetVit());
			TCHAR szBA2[50];
			ZeroMemory(szBA2, sizeof(szBA2));
			StringCchPrintf(szBA2, sizeof(szBA2), TEXT("Mag:%d, Hnd:%d, Wis:%d"),	
				pclLogSummon->clIP.GetMag(), pclLogSummon->clIP.GetHnd(),pclLogSummon->clIP.GetWis() );

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_SET, 
				pclMsg->siReason, (cltCharServer*)pclCM->CR[id], pclLogSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				siOriWeaponStoneNum, siOriDefenseStoneNum, pclLogSummon->siAttackWearStoneNum, pclLogSummon->siDefenseWearStoneNum, 0, szBA, szBA2);
		}
	}
	else
	{
		switch(pclMsg->siReason)
		{
		case SETSUMMON_REASON_MAKE:
			{
				// ��ȯ���� �߰��ϴ� DB����� ������.
				pclchar->bIsNowAddSummonThroughDB = false;
			}
			break;
		case SETSUMMON_REASON_UPDATE:
		case SETSUMMON_REASON_FREE:
		case SETSUMMON_REASON_DIE:
		case SETSUMMON_REASON_TAKEIN:
		case SETSUMMON_REASON_TAKEOUT:
			break;
		case SETSUMMON_REASON_SUMMONSTON:// ��ȯ�� ���� ��������� 
			break;
		case SETSUMMON_REASON_CHARGESTAMINA:	// PCK : ��ȯ�� ���¹̳� ���� (08.07.23)
			break;
		}
		return;
	}

	return;
}


void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONREVIVE(sPacketHeader* pPacket)
{
	sDBResponse_SummonRevive* pclMsg = (sDBResponse_SummonRevive *)pPacket;

	BOOL bSuccess = FALSE;

	if( pclMsg->siResult >= 1)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 

		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
		//================================================ 
		// Client�� ������ �κ��丮 Update�Ѵ�.
		//================================================ 
		if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID)
		{
			if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
			{
				pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}

		//================================================ 
		// �������� ��Ȱ��Ű�� ������ ��ȯ���� ���� * 10 ���� �߰��Ѵ�.
		//================================================ 
		if(pclMsg->siVillageUnique>0 && pclMsg->siVillageUnique < MAX_VILLAGE_NUMBER)
		{
			GMONEY siGetVillageMoney = pclMsg->siItemNum * 10;
			if(pclMsg->siItemNum>= 0)
			{
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, pclMsg->siVillageUnique, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}

		//--------------------------------
		// ��Ȱ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = pclMsg->clSummon.siKind;
		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{
			//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[kind];
			}

			if(pclki == NULL)							return;
			if(pclki->siSummonRank <= 0)				return;
		}

		//---------------------------------------------
		// ��ȯ���� ��Ȱ��Ų��..
		//---------------------------------------------
		//==========================================
		// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
		//==========================================
		cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
		SI32 siSummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);
		if(pclSummon)
		{
			pclSummon->Set(&pclMsg->clSummon);
			cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		//---------------------------------------------
		// ��ȯ���� ������ �Ǿ� ������ �������� �ʴ´�.
		//---------------------------------------------
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID)  == FALSE)
		{
			//---------------------------------------------
			// ��ȯ���� �����ϰ� ���ϰ� ������ �����Ѵ�.
			//---------------------------------------------
			siSummonID = ((cltCharServer*)(pclCM->CR[id]))->CreateSummon(&pclMsg->clSummon);

			if(pclCM->IsValidID(siSummonID)  == TRUE)
			{
				pclCM->CR[id]->siChildCharUnique	= siSummonID;
				pclCM->CR[id]->siSummonIndex		= siSummonIndex;

				pclCM->CR[siSummonID]->ParametaBoxAction();

				{
					// �������׵� ������ ���Ž�Ų��.
					cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);

					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
		
		{
			//================================================ 
			// ����� �����Ѵ�.
			//================================================ 
			cltGameMsgResponse_SummonRevive clinfo(pclCM->CR[id]->GetCharUnique(), 1, pclMsg->clSummon.siSummonID);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONREVIVE , sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				cltServer * pclServer = (cltServer*)pclClient;
				// PCK - ������ ��� �α׸� �����.
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
												USEITEM_REASON_SUMMONREVIVE, pclchar, NULL, 0, 0, 0, &pclMsg->clItem_Log, 0, 0, 0, 0, 0, 
												pclMsg->siItemPos, 0, 0, 0, 0, 0, NULL, NULL);

				// [�α��߰� : Ȳ���� 2007. 10. 8] // ��ȯ�� ��Ȱ.
				// param1 == ������ ����ũ
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_REVIVE, 
												0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
												pclMsg->clItem_Log.siUnique, 0, 0, 0, 0, NULL, NULL);
			}
		}
		
		bSuccess = TRUE;
		return;
	}
	
	if(bSuccess == FALSE)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 
		
		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
		//================================================ 
		// ����� �����Ѵ�.
		//================================================ 
		cltGameMsgResponse_SummonRevive clinfo(pclchar->GetCharUnique(), 0, pclMsg->clSummon.siSummonID);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONREVIVE , sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

	

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONEVOLVE(sPacketHeader* pPacket)
{
	sDBResponse_SummonEvolve*pclMsg = (sDBResponse_SummonEvolve *)pPacket;

	BOOL bSuccess = FALSE;


	if( pclMsg->siResult >= 1)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 
	
		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];

		//===================================
		// ��ȭó���� �Ϸ�Ǿ����� �˸���.
		//===================================
		pclchar->bIsEvolving = false;

		//================================================ 
		// Client�� ������ �κ��丮 Update�Ѵ�.
		//================================================ 
		if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID && pclMsg->bItemUse )
		{
			if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
			{
				pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		
		//================================================ 
		// �������� ��ȭ��Ű�� ������ ���ͱ��� �ش�.
		//================================================ 
		if(pclMsg->siVillageUnique>0 && pclMsg->siVillageUnique < MAX_VILLAGE_NUMBER)
		{
			GMONEY siGetVillageMoney = 0; // ���� ���ͱ� ������ SI32 -> GMONEY

			// ���� ����ġ ���� - by LEEKH
			if( pclClient->IsCountrySwitch( Switch_SummonEnolveVillageMoney ) )
			{
				// ��ȭ�ÿ� ���� ���ͱ� �ִ� �κ� ���� -KKM-
				// �̿������ ��ȭ
				if( ITEMUNIQUE(24015) == pclMsg->siUsedItemUnique )
				{
					SI64 itemPrice = pclNPCItemInfo->GetRealPrice( GetUniqueFromHash( TEXT("KIND_INVESTMENT") ), pclMsg->siUsedItemUnique );
					siGetVillageMoney = pclMsg->siItemNum * itemPrice / 2;
				}
				// �൹�� ��ȭ
				else
				{
					cltItemPriceUnit* pPrice = pclItemManager->pclItemPrice->GetPrice( pclItemManager, pclMsg->siUsedItemUnique );
					if( NULL != pPrice )
					{
						siGetVillageMoney = pclMsg->siItemNum * pPrice->siPrice / 2;
					}
				}
			}
			else
			{
				siGetVillageMoney = pclMsg->siItemNum * 100000;
			}

			if(pclMsg->siItemNum>= 0)
			{
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, pclMsg->siVillageUnique, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}

		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = pclMsg->clSummon.siKind;
		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{
			//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[kind];
			}

			if(pclki == NULL)							return;
			if(pclki->siSummonRank <= 0)				return;
		}

		SI32 siSummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);

		//---------------------------------------------
		// ��ȯ���� �������� ������ ��ȭ��ų�� ����.
		//---------------------------------------------
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID)  == TRUE)
		{
			SI32 siSummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);
			if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex)
			{
				//---------------------------------------------
				// ���ӿ��� ��ȯ���� �����. 
				//---------------------------------------------
				pclCM->CR[siSummonID]->DeleteInCell();
				pclCM->DeleteChar(siSummonID);
				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				pclCM->CR[id]->siChildCharUnique  = 0;
				pclCM->CR[id]->siSummonIndex	  = 0;
				
				// �������׵� ������ ���Ž�Ų��.
				cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);

				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				
			}
		}
			
		//==========================================
		// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
		//==========================================
		cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
		if(pclSummon)
		{
			pclSummon->Set(&pclMsg->clSummon);
			cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		//==========================================
		// ������ ���� ��ȯ���� ������ �����Ѵ�.
		//==========================================
		cltSimpleSummon *pclSimpleSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSimpleSummonFromSummonID(pclMsg->clSummon.siSummonID);
		SI32 siSlotIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonBaseIndexFromSummonID(pclMsg->clSummon.siSummonID);
		if(pclSimpleSummon)
		{
			pclSimpleSummon->Set(&pclMsg->clSummon);
			cltGameMsgResponse_BaseSummon clInfo(pclCM->CR[id]->GetCharUnique(), siSlotIndex, pclSimpleSummon);
			cltMsg clMsg(GAMEMSG_RESPONSE_BASESUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		//================================================ 
		// ����� �����Ѵ�.
		//================================================ 
		{
			cltGameMsgResponse_SummonEvolve clinfo(pclCM->CR[id]->GetCharUnique(), 1, pclMsg->clSummon.siSummonID, pclMsg->clSummon.siKind,pclMsg->siMode);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONEVOLVE, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				cltServer * pclServer = (cltServer*)pclClient;
				// PCK - ������ ��� �α׸� �����.
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
									USEITEM_REASON_SUMMONEVOLVE, pclchar, NULL, 0, 0, 0, &pclMsg->clItem_Log, 0, 0, 0, 0, 0, 
									pclMsg->siItemPos, 0, 0, 0, 0, 0, NULL, NULL);

				// [�α��߰� : Ȳ���� 2007. 10. 9] // ��ȯ�� ��ȭ.
				// param1 == ���, param2 == ������ ����ũ, param3 == ��ȭ�Ǳ����� ��ȯ�� ī�ε�
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_EVOLVE, 
												0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siMode, pclMsg->siUsedItemUnique, pclMsg->siSummonKind, 0, 0, NULL, NULL);
			}
		}

/*

#ifdef EVENT_SUMMON_EVENT
		//================================================ 
		// ��ȯ�� Rank ? �̻��� ��ü������ �Ѵ�.
		//================================================ 
		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{
			cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];

			if ( pclMsg->siMode == SUMMONEVOLVE_EVOLVE )
			{
				if(pclki && pclki->siSummonRank >= 8)
				{
					SI32 itemTable[] = 
					{
						ITEMUNIQUE(5350),
						ITEMUNIQUE(5355),
						ITEMUNIQUE(5360),
						ITEMUNIQUE(5365)
					};

					SI16 rndIndex = rand() % 4;
                    
					SI32 itemUnique = itemTable[ rndIndex ];

					SI32 itemNum = 1;

					if( pclki->siSummonRank >= 25 )
					{
						itemNum = 6;
					}
					else if( pclki->siSummonRank >= 17 )
					{
						itemNum = 4;
					}
					else if( pclki->siSummonRank >= 8 )
					{
						itemNum = 2;
					}
					
					pclchar->GiveItem( itemUnique , itemNum , INPUTITEMPERSON_OPTION_EVENT,0 );
					
				}
			}
		}

#endif			
		*/

		//================================================ 
		// ��ȯ�� Rank ? �̻��� ��ü������ �Ѵ�.
		//================================================ 
		#define LIMIT_RANK_SUMMON_REVIVE_BROADCAST	30

		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{
			//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[kind];
			}

			bool bGameMaster = false ;
			if(pclCM->CR[id]->GetGameMasterLevel()< BASIC_GAMEMASTER_LEVEL + 1 )
			{
				bGameMaster = true ;
			}

#ifdef _DEBUG
			// ��Ƽȹ�渷�� //bGameMaster = true ;
#endif

			if ( bGameMaster && pclMsg->siMode == SUMMONEVOLVE_EVOLVE )
			{
				if(pclki && pclki->siSummonRank >= LIMIT_RANK_SUMMON_REVIVE_BROADCAST)
				{
					cltGameMsgResponse_HighSummon clinfo((TCHAR*)pclCM->CR[id]->GetName(), pclCM->CR[id]->pclCI->GetPersonID(), kind, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_HIGHSUMMON, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		bSuccess = TRUE;

		if ( pclMsg->siMode == SUMMONEVOLVE_EVOLVE )
		{
			// ��ȯ�� ��ȭ ����Ʈ ���̶��, 
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SUMMONEVOLUTION);
			if ( pclMsg->bQuestEvolve )
			{
				pclCM->CR[id]->pclCI->clBI.bQuestEvolve = true ;
			}
		}

		return;
	}
	
	if(bSuccess == FALSE)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 
		
		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];

		//===================================
		// ��ȭó���� �Ϸ�Ǿ����� �˸���.
		//===================================
		pclchar->bIsEvolving = false;

		//================================================ 
		// ����� �����Ѵ�.
		//================================================ 
		cltGameMsgResponse_SummonEvolve clinfo(pclchar->GetCharUnique(), 0, pclMsg->clSummon.siSummonID, pclMsg->clSummon.siKind,pclMsg->siMode);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONEVOLVE , sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONSCROLL(sPacketHeader* pPacket)
{
	sDBResponse_SummonScroll*pclMsg = (sDBResponse_SummonScroll *)pPacket;

	BOOL bSuccess = FALSE;

	if( pclMsg->siResult >= 1)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 
	
		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
		//================================================ 
		// Client�� ������ �κ��丮 Update�Ѵ�.
		//================================================ 
		if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID)
		{
			if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
			{
				pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}

		//================================================ 
		// �������� ��ȭ��Ű�� ������ ���� ���� * 20 ���� �߰��Ѵ�.
		//================================================ 
		if(pclMsg->siVillageUnique>0 && pclMsg->siVillageUnique < MAX_VILLAGE_NUMBER)
		{
			GMONEY siGetVillageMoney = pclMsg->siItemNum * 20;
			if(pclMsg->siItemNum>= 0)
			{
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, pclMsg->siVillageUnique, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}
		

		//--------------------------------
		// ��Ȱ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = pclMsg->clSummon.siKind;
		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{
			//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[kind];
			}

			if(pclki == NULL)							return;
			if(pclki->siSummonRank <= 0)				return;
		}
		
		//==========================================
		// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
		//==========================================
		cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
		SI32 siSummonIndex = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);
		if(pclSummon)
		{
			pclSummon->Set(&pclMsg->clSummon);
			cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		{
			//================================================ 
			// ����� �����Ѵ�.
			//================================================ 
			cltGameMsgResponse_SummonScroll clinfo(pclCM->CR[id]->GetCharUnique(), 1, pclMsg->clSummon.siSummonID);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONSCROLL, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		
		// ��ȯ�� ��ȭ ����Ʈ ���̶��, 
		pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SUMMONSCROLL);

		
		bSuccess = TRUE;
		return;

	}
	
	if(bSuccess == FALSE)
	{
		SI32 id	= pclMsg->siCharID;	
		if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return; 
		
		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
		//================================================ 
		// ����� �����Ѵ�.
		//================================================ 
		cltGameMsgResponse_SummonScroll clinfo(pclchar->GetCharUnique(), 0, pclMsg->clSummon.siSummonID);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONSCROLL , sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMON_STATUSINIT(sPacketHeader* pPacket)
{
	sDBResponse_Summon_StatusInit *pclMsg = (sDBResponse_Summon_StatusInit *)pPacket;

	if ( pclMsg->siResult != 1 ) return ;

	SI32 id	= pclMsg->siCharID;	
	if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	//================================================ 
	// Client�� ������ �κ��丮 Update�Ѵ�.
	//================================================ 
	if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//--------------------------------
	// ��ȯ���� Kind�� �����Ѵ�.
	//--------------------------------
	SI32 kind = pclMsg->clSummon.siKind;
	if(kind > 0 && kind < MAX_KIND_NUMBER)	
	{
		//cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
		cltKindInfo* pclki = NULL;
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[kind];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[kind];
		}

		if(pclki == NULL)							return;
		if(pclki->siSummonRank <= 0)				return;
	}

	SI32 siSummonIndex = pclchar->pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclMsg->clSummon.siSummonID);

	SI32 siSummonID = pclCM->CR[id]->GetSummonID();
	if(pclCM->IsValidID(siSummonID)  == TRUE)
	{
		if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex)
		{
			//---------------------------------------------
			// ���ӿ��� ��ȯ���� �����. 
			//---------------------------------------------
			pclCM->CR[siSummonID]->DeleteInCell();
			pclCM->DeleteChar(siSummonID);
			//==========================================
			// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
			//==========================================
			pclCM->CR[id]->siChildCharUnique  = 0;
			pclCM->CR[id]->siSummonIndex	  = 0;

			// �������׵� ������ ���Ž�Ų��.
			cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);

			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//==========================================
	// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
	//==========================================
	cltSummon *pclSummon = pclCM->CR[id]->pclCI->clSummonInfo.GetSummonFromSummonID(pclMsg->clSummon.siSummonID);
	if(pclSummon)
	{
		pclSummon->Set(&pclMsg->clSummon);
		cltGameMsgResponse_Summon clInfo(pclCM->CR[id]->GetCharUnique(), siSummonIndex, pclSummon);
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			cltServer * pclServer = (cltServer*)pclClient;
			// PCK - ������ ��� �α׸� �����.
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
				USEITEM_REASON_SUMMONSTATUSINIT, pclchar, NULL, 0, 0, 0, &pclMsg->clItem_Log, 0, 0, 0, 0, 0, 
				pclMsg->siItemPos, 0, 0, 0, 0, 0, NULL, NULL);

			// PCK - ��ȯ�� ���� �ʱ�ȭ
			// param1 == ������ ����ũ.
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_STATUS_INIT, 
				0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclMsg->clItem_Log.siUnique, 0, 0, 0, 0, NULL, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMON_SETAUTOHEAL(sPacketHeader* pPacket)
{
	sDBResponse_Summon_SetAutoHeal* pclMsg = (sDBResponse_Summon_SetAutoHeal*)pPacket ;

	if ( pclMsg->siResult != 1 ) return ;

	SI32 id	= pclMsg->siCharID;	
	if(pclCM->IsValidID(id) != TRUE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)	return;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	pclchar->pclCI->clSummonInfo.bAutoHeal = pclMsg->bAutoHeal ;
	pclchar->pclCI->clSummonInfo.siSelectAutoHeal = pclMsg->siSelectAutoHeal ;

	cltGameMsgResponse_Summon_SetAutoHeal clinfo(pclCM->CR[id]->GetCharUnique(), pclMsg->siResult,
												 pclMsg->siSelectAutoHeal,pclMsg->bAutoHeal);
	cltMsg clMsg(GAMEMSG_RESPONSE_SUMMON_SETAUTOHEAL, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 8] // ��ȯ�� �ڵ� ȸ��.
	//	// param1 == ���, param2 == 30%�� 50%�� 70%��. param3 == �� ���ΰ� �� ���ΰ�.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_SET_AUTO_HEAL, 
	//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//									pclMsg->siResult, pclMsg->siSelectAutoHeal, pclMsg->bAutoHeal, 0, 0, NULL, NULL);
	//}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONTRADE( sPacketHeader* pPacket )
{
	sDBResponse_SummonTrade* pclMsg = (sDBResponse_SummonTrade* )pPacket;

	if ( pclMsg->siResult != 1 )
		return;

	SI32 id = pclMsg->usCharID;

	/*
	//---------------------------------------
	// ��迡 �߰�
	//---------------------------------------
	++pclStatisticsManager->clDailyStatistics.siSystemBuyHorseNum; 
	pclStatisticsManager->clDailyStatistics.siSystemBuyHorseMoney += pclMsg->siIncreaseMoney;
	//---------------------------------------
	*/
	if ( id > 0 && pclCM->IsValidID( id ) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		//---------------------------------------------
		// ��ȯ���� �����Ǿ��־���Ѵ�.
		//---------------------------------------------
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID)  == TRUE )
		{
			if(pclCM->CR[siSummonID]->GetSummonIndex() == pclMsg->clSummon.siSummonID)
			{
				cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
				pclchar->bIsTradeing = false;
				// ����Ѵ�.
				pclLog->FilePrint(TEXT("Config\\BuySummon.log"), TEXT("User : [%s] / SummonKind : [%s] / SummonPrice : [%d]"),
								  pclCM->CR[id]->GetName() , pclCM->CR[siSummonID]->pclKI->szCode,pclMsg->siMoney);

				//---------------------------------------------
				// ���ӿ��� ��ȯ���� �����. 
				//---------------------------------------------
				pclCM->CR[siSummonID]->DeleteInCell();
				pclCM->DeleteChar(siSummonID);
				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				pclCM->CR[id]->siChildCharUnique  = 0;
				pclCM->CR[id]->siSummonIndex	  = 0;

				{
					// �������׵� ������ ���Ž�Ų��.
					cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				pclCM->CR[id]->pclCI->clSummonInfo.SummonInit(pclMsg->clSummon.siSummonID);

				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siLeftMoney );

				{
					cltGameMsgResponse_TradeMerchantBuySummon clTradeMerchantBuySummon(id, pclMsg->siResult, pclMsg->clSummon.siSummonID, pclMsg->siMoney, pclMsg->siLeftMoney );
					cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONTRADE, sizeof(clTradeMerchantBuySummon), (BYTE*)&clTradeMerchantBuySummon);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 10. 8] // ��ȯ�� �Ǹ�.
						// param1 == ���. param2 == ����ũ.
						cltServer * pclServer = (cltServer*)pclClient;
						pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON, LOGCOMMAND_INDEX_SUMMON_TRADE, 
														0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, 0, pclMsg->siMoney, pclMsg->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0, 
														pclMsg->siResult, pclMsg->clSummon.siSummonID, 0, 0, 0, NULL, NULL);
					}
				}

				// ��ȯ�� ������ ������Ʈ ��Ų��. 
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_SUMMON, true, 0);
			}
		}
	}
}

// [����] ���� �̺�Ʈ ���� ���� ���� ��û ���
void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONUSESTON(sPacketHeader *pPacket)
{
}

// Base�� �ִ� �ش� ��ȯ���� SLot�� �ִ´�.
void cltServer::DoMsg_DBMSG_RESPONSE_SUMMON_SLOTIN(sPacketHeader* pPacket)
{
	sDBResponse_SummonSlotIn* pclMsg = (sDBResponse_SummonSlotIn*)pPacket;
	if ( NULL == pclMsg )																return	;
	SI08 siSlotIndex =	pclMsg->siSummonIndex	;			// �ش� ��ȯ���� ���� ����
	SI32 id = pclMsg->siCharID					;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( pclchar == NULL )																return ;
	
	if (pclMsg->siResult == 1)
	{
		// ���� �������� ���� cltSummon �� cliItem ������ ���� �Ѵ�.
		//	���� �ش� ������ �������� �������� Ȯ�� �Ѵ�.
		if( siSlotIndex < 0 || siSlotIndex >= MAX_SUMMON_OWN )							return	;
		// ������ �ش� ������ ��� �ִ��� Ȯ�� �Ѵ�.
		if( pclchar->pclCI->clSummonInfo.clSummon[ siSlotIndex ].siSummonID > 0 )		return	;

		// ������ ������� �ش� ��ȯ���� ����
		pclchar->pclCI->clSummonInfo.SetSummon( siSlotIndex, &pclMsg->clSummon)	;
		// �ش� ������ ��ȯ���� �������� �����Ѵ�.
		pclchar->pclCI->clSummonInfo.clItemInfo[ siSlotIndex ].Set(&pclMsg->clSummonItemInfo)	;

		// Ŭ���̾�Ʈ�� ���� �Ѵ�.
		cltGameMsgResponse_SlotIn clInfo( pclchar->GetCharUnique(), siSlotIndex, &pclMsg->clSummon ,&pclMsg->clSummonItemInfo );
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONSLOTIN, sizeof(clInfo), (BYTE*)&clInfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		pclchar->SetUpdateSwitch(UPDATE_SUMMON, true, 0);

		// ����Ʈ ���� ��ȯ�������ҿ��� ����
		((cltCharServer*)pclCM->CR[id])->IncQuestPara( QUEST_CLEAR_COND_SUMMONHOUSE_OUTPUT, 0, 1 );

		if(pclClient->IsCountrySwitch(Switch_SummonHouse))
		{
		}
		else
		{
			if(pclMsg->clSummon.siStatus == SUMMON_STATUS_TAKEOUT)
			{
				//---------------------------------------------
				// ��ȯ���� �����Ǿ� ���� ������ �����ϰ� �����Ѵ�.
				//---------------------------------------------
				SI32 siSummonID = pclchar->GetSummonID();
				if(pclCM->IsValidID(siSummonID)  == FALSE)
				{
					//---------------------------------------------
					// ��ȯ���� �����ϰ� ���ϰ� ������ �����Ѵ�.
					//---------------------------------------------
					siSummonID = pclchar->CreateSummon(&pclMsg->clSummon);
					if(pclCM->IsValidID(siSummonID)  == TRUE)
					{
						pclchar->siChildCharUnique = siSummonID;
						pclchar->siSummonIndex     = siSlotIndex;

						pclCM->CR[siSummonID]->ParametaBoxAction();

						// �������׵� ������ ���Ž�Ų��.
						cltGameMsgResponse_ChangeSummonStatus clInfo(pclchar->GetCharUnique(), pclchar->siChildCharUnique, pclchar->siSummonIndex);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
						
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}
	}
}

// �ش� ��ȯ���� SLot���� ������.
void cltServer::DoMsg_DBMSG_RESPONSE_SUMMON_SLOTOUT(sPacketHeader* pPacket)
{
	sDBResponse_SummonSlotOut* pclMsg = (sDBResponse_SummonSlotOut*)pPacket;
	if ( NULL == pclMsg )																return	;
	SI08 siSummonIndex =	pclMsg->siSummonIndex	;			// �ش� ��ȯ�� �ε���
	SI32 id = pclMsg->siCharID					;
	if ( id < 0 )																		return	;
	if (pclMsg->siResult == 1) {
		// ���� �������� �ش� ������ ��ȯ���� ���� �Ѵ�.
		//	���� �ش� ������ �������� �������� Ȯ�� �Ѵ�.
		if( siSummonIndex > MAX_SUMMON_OWN )												return	;
		// ������ �ش� ������ ������ ����
		pclCM->CR[id]->pclCI->clSummonInfo.clSummon[ siSummonIndex ].Init()	;
		// �ش� ������ ��ȯ���� �������� �ʱ�ȭ�Ѵ�
		pclCM->CR[id]->pclCI->clSummonInfo.clItemInfo[ siSummonIndex ].Init();
		// Ŭ���̾�Ʈ�� ���� �Ѵ�.
		cltGameMsgResponse_SlotOut clInfo( id, siSummonIndex );
		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONSLOTOUT, sizeof(clInfo), (BYTE*)&clInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_SUMMON, true, 0);

		// ����Ʈ ���� ��ȯ�������ҿ� �־��
		((cltCharServer*)pclCM->CR[id])->IncQuestPara( QUEST_CLEAR_COND_SUMMONHOUSE_INPUT, 0, 1 );

		//---------------------------------------------
		// ��ȯ���� �����Ǿ��־���Ѵ�.
		//---------------------------------------------
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID)  == TRUE )
		{
			if(pclCM->CR[siSummonID]->GetSummonIndex() == siSummonIndex)
			{
				//---------------------------------------------
				// ���ӿ��� ��ȯ���� �����. 
				//---------------------------------------------
				pclCM->CR[siSummonID]->DeleteInCell();
				pclCM->DeleteChar(siSummonID);
				//==========================================
				// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
				//==========================================
				pclCM->CR[id]->siChildCharUnique  = 0;
				pclCM->CR[id]->siSummonIndex	  = 0;

				// �������׵� ������ ���Ž�Ų��.
				cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}