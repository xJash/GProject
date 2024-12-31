//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "Char/CharManager/CharManager.h"
//----------------------------------------
// CommonLogic
//----------------------------------------
#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../CommonLogic/Hunt/Hunt.h"
#include "../CommonLogic/Cityhall/Cityhall.h"

#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/MsgRval-Define.h"
#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/Msg/MsgType-Summon.h"

#include "../CommonLogic/Msg/MsgType-RacoonDodgeEvent.h"
#include "../CommonLogic/MsgType.h"


#include "../CommonLogic/MagicMgr/MagicMgr.h"
#include "../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"

#include "../CommonLogic/BlackArmy/BlackArmy.h"

#include "../CommonLogic/Marriage/MarriageManager.h"

//----------------------------------------
// Common
//----------------------------------------
#include "../Common/Map/Map.h"
#include "../Common/Order/Order.h"
#include "../Common/Map/MapManager/MapManager.h"
#include "../Common/Skill/Skill-Manager.h"
#include "../Common/PartyMgr/PartyObj.h"
#include "../Common/PartyMgr/PartyMgr.h"
#include "../Common/NPCManager/NPC.h"
#include "../common/Item/ItemCommon/cltSetItem.h"
#include "../common/Event/MofuMofu/MofuMofu.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "Server.h"
#include "Statistics/Statistics.h"
#include "Minister/MinisterBase.h"
#include "Minister/MinisterMgr.h"
#include "Minister/Minister-Hyungzo.h"


//----------------------------------------
// DBManager
//----------------------------------------
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-PostOffice.h"

#include "../../../Server/AuthServer/AuthMsg.h"

#include "../Server/FourLeafManager/ForleafManager.h"

#include "../common/Util/Util.h"

extern cltCommonLogic* pclClient;

#define CAPTURE_DOLLNUM	1		// ��ȹ���� ȹ���� �� �ִ� ���� ����
#define MAX_UNIQUENUM	20	//m_100healmanager.txt �� �� �ִ� ����ũ ����

// ������ ���� ĳ������ ��ġ ���. 
void cltServer::MagicPopAction()
{
	BYTE data[256];
	SI32 i, j;
	stMagicMsgHeader* psHeader;
	SI32 hitrate = 0; 
	SI32 dodgerate = 0; 

	SI32 size;
	while(pclMagicManager->Pop(data, &size))
	{
		if(size>=256)
		{
			psHeader = (stMagicMsgHeader*)data;
			MsgBox(TEXT("dsfv8dfjd"), TEXT("fSDfcv9df:%d"), psHeader->si32MsgKind);
			continue;
		}

		psHeader = (stMagicMsgHeader*)data;
		switch(psHeader->si32MsgKind)
		{
		case MAGIC_DAMAGE:
			{
				SI32 siAttackType = 0;
				switch(psHeader->si32MagicKind)
				{
				case MAGIC_MON_FROZENSORCERER:	siAttackType = ATTACKTYPE_ICE;		break;
				default:						siAttackType = ATTACKTYPE_MAGIC;	break;
				}

				stMagicMsgDamage* pclMagic = (stMagicMsgDamage*)data;

				SI32 fromid	= pclCM->GetIDFromCharUnique(pclMagic->si32FromID);
				if(pclCM->IsAlive(fromid) == false)return ;

				SI32 toid	= pclCM->GetIDFromCharUnique(pclMagic->si32ToID);
				if(pclCM->IsAlive(toid) == false)return ;

				SI32 damage = pclMagic->si32Damage;

				// �������� ��ø�� ������ �ް� pvp-
				// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
				//if( IsWhereServiceArea(ConstSwitch_PVP) )

				if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
				{	
					hitrate   = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[toid], pclClient->pclCM->CR[fromid], true );	
					dodgerate = pclCM->CR[toid]->clPB.GetDodgeRate( pclCM->CR[fromid], pclClient->pclCM->CR[toid], true );	// ���� ȸ������ �ʿ��ϴ�.

				}
				else
				{
					if(siEnablePVP == 1)
					{
						hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[toid], pclClient->pclCM->CR[fromid], true );	
					}
					else
						hitrate = 100;

					dodgerate = 0;
				}
				cltCharPos clpos(pclCM->CR[toid]->GetMapIndex(), pclCM->CR[toid]->GetX(), pclCM->CR[toid]->GetY());
				cltAttackTarget cltarget(toid, &clpos, hitrate , dodgerate);
				cltAttackDamageInfo cldamageinfo( siAttackType , damage, pclMagic->sMagicMsgHeader.si32MagicKind);
				HitOperation(fromid, &cldamageinfo, 1, &cltarget, pclCM->CR[toid]->pclMap);
			}
			break;
		case MAGIC_CIRCLE_DAMAGE:
			{
				SI32 siAttackType = 0;
				switch(psHeader->si32MagicKind)
				{
				case MAGIC_MON_POISONFLAME:		
				case MAGIC_MON_TOADPOISON:		siAttackType = ATTACKTYPE_POISON;			break;
				case MAGIC_MON_FIREBURN:		siAttackType = ATTACKTYPE_MAGICFIREBURN;	break;
				default:						siAttackType = ATTACKTYPE_MAGIC;			break;
				}

				stMagicMsgCircleDamage* pclMagic = (stMagicMsgCircleDamage*)data;

				SI32 fromid		= pclCM->GetIDFromCharUnique(pclMagic->si32FromID);
				SI32 toid		= pclCM->GetIDFromCharUnique(pclMagic->si32ToID);
				if(pclCM->IsAlive(fromid) == false)return ;
				SI32 x			= pclCM->CR[fromid]->GetX();
				SI32 y			= pclCM->CR[fromid]->GetY();

				cltMapCommon* pclMap = pclCM->CR[fromid]->pclMap;
				if(pclMap == NULL)return ;

				SI32 damage		= pclMagic->si32Damage;
				SI32 radius		= max(1, pclMagic->si32Radius);
				SI32 curradius	= max(1, pclMagic->si32CurrentRadius);
				SI32 id			= 0;
				SI32 length		= 0;

				// [����] ��ȯ�� �巡���� ���� ������ Ÿ���� �� ĳ������ ������ �ֱ�..
				if( MAGIC_MON_SUMMONDRAGON_STUN == psHeader->si32MagicKind )
				{
					cltCharServer* pclChar = pclCM->GetCharServer( toid );
                    if( pclChar ) 
					{
						if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
						{	
							hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclChar, pclClient->pclCM->CR[fromid], true );	
							dodgerate = pclChar->clPB.GetDodgeRate( pclCM->CR[fromid], pclChar, true );	
						}
						else
						{
							if(siEnablePVP == 1)
							{
								hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclChar, pclCM->CR[fromid], true );	
							}
							else
								hitrate = 100;

							dodgerate = 0;
						}

						cltCharPos clpos(pclChar->GetMapIndex(), pclChar->GetX(), pclChar->GetY());
						cltAttackTarget cltarget(pclChar->GetID(), &clpos, hitrate , dodgerate); 
						cltAttackDamageInfo cldamageinfo(siAttackType, damage * 2, psHeader->si32MagicKind); 

						HitOperation(fromid, &cldamageinfo, 1, &cltarget, pclChar->pclMap);
					}
				}

				for(i = -curradius; i <= curradius; i++)
				{
					for(j = -curradius; j <= curradius; j++)
					{
						if(TABS(i) != curradius && TABS(j) != curradius)continue;

						id = pclMap->GetIDMap(x+j, y+i);

						if(pclCM->IsAlive(id)			  == false)	continue;
						if(pclCM->CR[fromid]->IsEnemy(id) == false)	continue;

						// [����] ��ȯ�� �巡���� ���� ����.
						if( MAGIC_MON_SUMMONDRAGON_STUN == psHeader->si32MagicKind )
						{
							cltCharServer* pclChar = pclCM->GetCharServer(id);
							if( NULL == pclChar ) continue;
	
							pclChar->SetStun( 5 );		
						}
						
						if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
						{	
							hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[id], pclCM->CR[fromid], true );	
							dodgerate = pclCM->CR[id]->clPB.GetDodgeRate( pclCM->CR[fromid], pclCM->CR[id], true );	
						}
						else
						{
							if(siEnablePVP == 1)
							{
								hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[id], pclCM->CR[fromid], true );	
							}
							else
								hitrate = 100;

							dodgerate = 0;
						}

						length = min(radius, max( TABS(i), TABS(j)) ) ;
						cltCharPos clpos(pclCM->CR[id]->GetMapIndex(), pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY());
						cltAttackTarget cltarget(id, &clpos, hitrate , dodgerate);
						cltAttackDamageInfo cldamageinfo(siAttackType, damage * max(1, (radius - length)) / radius, psHeader->si32MagicKind);

						HitOperation(fromid, &cldamageinfo, 1, &cltarget, pclCM->CR[id]->pclMap);
					}
				}
			}
			break;

		case MAGIC_WHIRLPOOL_DAMAGE:
			{
				stMagicMsgWhirlPoolDamage* pclMagic = (stMagicMsgWhirlPoolDamage*)data;

				SI32 fromid	= pclCM->GetIDFromCharUnique(pclMagic->si32FromID);
				if ( fromid < 1 )
					return;
				SI32 toid	= pclCM->GetIDFromCharUnique(pclMagic->si32ToID);
				if ( toid < 1 )
					return;
				SI32 damage = pclMagic->si32Damage;
				if ( damage < 2 )
				{
					//tsoi 	printf(TEXT("ets"));
				}
				SI32 radius	= pclMagic->si32Radius;
				if(radius <=0 )
				{
					radius = 1;
				}

				if(pclCM->IsAlive(fromid) == false)return ;

				cltMapCommon* pclMap = pclCM->CR[fromid]->pclMap;
				if(pclMap == NULL)return ;

				SI32 x = pclMagic->si32XCenterPos;
				SI32 y = pclMagic->si32YCenterPos;

				//------------------------------------------------
				// ���� Ÿ���� �ݵ�� �´´�. 
				//------------------------------------------------

				if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
				{	
					hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[toid], pclCM->CR[fromid], true );	
					dodgerate = pclCM->CR[toid]->clPB.GetDodgeRate( pclCM->CR[fromid], pclCM->CR[toid], true );	

				}
				else
				{
					switch ( siServiceArea )
					{
					case ConstServiceArea_English:
					case ConstServiceArea_NHNChina:
					case ConstServiceArea_EUROPE:
						{
							hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[toid], pclCM->CR[fromid], true );	
						}
						break;
					default:
						{
							hitrate = 100;
						}
						break;

					}

					dodgerate = 0;
				}
				cltCharPos clpos(pclCM->CR[toid]->GetMapIndex(), pclCM->CR[toid]->GetX(), pclCM->CR[toid]->GetY());
				cltAttackTarget cltarget(toid, &clpos, hitrate , dodgerate);
				cltAttackDamageInfo cldamageinfo(ATTACKTYPE_MAGIC, damage, psHeader->si32MagicKind);
				HitOperation(fromid, &cldamageinfo, 1, &cltarget, pclCM->CR[toid]->pclMap);

				SI32 id;
				for(i = -radius; i <= radius; i++)
				{
					for(j = -radius; j <= radius; j++)
					{
						id = pclMap->GetIDMap(x+j, y+i);

						//-----------------------------------------------
						// ���� Ÿ���� �̹� �¾����Ƿ� �����Ѵ�. 
						//-----------------------------------------------
						if(id == toid)continue;
						if(pclCM->IsAlive(id) == false)continue;
						if(pclCM->CR[fromid]->IsEnemy(id)== false)continue;

						// ��а��� �� ĳ���͸� ���� ������ �ֱ� ���ؼ�...
						if ( id == toid && pclCM->IsAlive(id) && pclCM->CR[fromid]->IsEnemy(id) )
						{
							// ���߷� ��� pvp-
							// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
							//if( IsWhereServiceArea(ConstSwitch_PVP) )
							if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
							{	
								hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[id], pclCM->CR[fromid], true );	
								dodgerate = pclCM->CR[id]->clPB.GetDodgeRate( pclCM->CR[fromid], pclCM->CR[id], true );	
							}
							else
							{
								if(siEnablePVP == 1)
								{
									hitrate = pclCM->CR[fromid]->clPB.GetHitRate( pclCM->CR[id], pclCM->CR[fromid], true );	
								}
								else
									hitrate = 100;

								dodgerate = 0;
							}

							cltCharPos clpos(pclCM->CR[id]->GetMapIndex(), pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY());
							cltAttackTarget cltarget(id, &clpos, hitrate , dodgerate);
							cltAttackDamageInfo cldamageinfo(ATTACKTYPE_MAGIC, damage, pclMagic->sMagicMsgHeader.si32MagicKind);
							HitOperation(fromid, &cldamageinfo, 1, &cltarget, pclCM->CR[id]->pclMap);

						}
					}
				}

			}
			break;

		case MAGIC_INCREASE_LIFE:
			{
				stMagicMsgDamage* pclMagic = (stMagicMsgDamage*)data;

				SI32 fromid	= pclCM->GetIDFromCharUnique(pclMagic->si32FromID);
				if ( fromid < 1 )
					return;
				SI32 toid	= pclCM->GetIDFromCharUnique(pclMagic->si32ToID);
				if ( toid < 1 )
					return;
				SI32 damage = pclMagic->si32Damage;
				if(pclCM->IsAlive(toid) && pclCM->IsAlive(fromid))
				{
					pclCM->CR[toid]->IncreaseLife(damage);

					// �̿����� �뺸 
					cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_HEAL, true, pclCM->CR[toid]->GetLife(), damage);
					cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[toid]->GetCharUnique(), &StatusInfo);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
					((cltCharServer*)pclCM->CR[toid])->SendNeighbourMsg(&clMsg, true);

					//==========================================
					// ������ ���� �ִ� ��ȯ���� ������ �����ϰ� �뺸 �Ѵ�.
					//==========================================
					SI32 siParentID = pclCM->CR[toid]->GetSummonParentID();
					if(pclCM->IsValidID(siParentID))
					{
						//==========================================
						// 
						//==========================================
						cltSummon *pclSummon = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSummon(pclCM->CR[toid]->GetSummonIndex());
						if(pclSummon)
						{
							pclSummon->clIP.Set(&pclCM->CR[toid]->pclCI->clIP);
							cltGameMsgResponse_Summon clInfo(pclCM->CR[siParentID]->GetCharUnique(), pclCM->CR[toid]->GetSummonIndex(), pclSummon);
							cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
							pclCM->CR[siParentID]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}

				}
			}
			break;

		default:
			MsgBox(TEXT("fdsf93jfdf"), TEXT("dv9ejd:%d"), psHeader->si32MagicKind);
		}
	}
}


// ������ ���� �Ӽ��� ����Ͽ� ���� ü���� ���Ͻ�Ų��. 
// �̴� ���������� �̷������ �۾��̴�. 
BOOL cltServer::HitOperation(SI32 myid, cltAttackDamageInfo* pcldamageinfo, SHORT range, const cltAttackTarget* pcltarget, cltMapCommon* pclMap)
{

	SHORT length=0;
	SHORT damage=0;
	SHORT realpower = 0;
	SI32 id;
	cltAttackTargetList clList;

	SI32 attackid	= pcltarget->GetAttackID();
	if(pclCM->IsValidID(attackid) == false)		return FALSE;
	if(pclCM->IsValidID(myid) == false)			return FALSE;

	SI32 dx = pcltarget->clPos.siX;
	SI32 dy = pcltarget->clPos.siY;

	// ���� ���°� �¾Ҵٴ� �ǹ��̴�.
	// �׳� ������ �ϴ� ������ ������ 
	// ���� ���ϱ� �̺�Ʈ 
	//Switch_10MonthEvent_RacoonDodge
	//if(pclClient->IsCountrySwitch(Switch_10MonthEvent_RacoonDodge))
	//{
	//	cltCharCommon* pclAttackChar = pclCM->GetChar( myid)	;
	//	if( pclAttackChar != NULL )
	//	{
	//		if(pclAttackChar->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT)
	//		{
	//			cltCharCommon* pclChar = pclCM->GetChar( attackid )	;// ���� ���
	//			if ( pclChar != NULL )
	//			{
	//				cltWarpInfo clWarpInfo(1, 0, true, false, 38, 33, -1, -1);
	//				clWarpInfo.uiMapIndex = PLAY_MAP_INDEX_INDODEVENT;

	//				pclChar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
	//				pclChar->Warp()	;

	//				cltGameMsgResponse_30Seceond_Clear clinfo( pclChar->pclCI->GetPersonID() );
	//				cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND_CLEAR, sizeof(clinfo), (BYTE*)&clinfo);
	//				pclChar->SendNetMsg((sPacketHeader*)&clMsg);

	//				cltGameMsgResponse_Round_Clear clinfo2( pclChar->pclCI->GetPersonID() );
	//				cltMsg clMsg2(GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR, sizeof(clinfo2), (BYTE*)&clinfo2);
	//				pclChar->SendNetMsg((sPacketHeader*)&clMsg2);
	//			}

	//		}
	//	}
	//}

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		if(pclClient->IsCountrySwitch(Switch_SoulGuard))
		{
			if ( IsPC(attackid) )
			{
				cltCharServer* pclCharServer = pclCM->GetCharServer(attackid)	;
				if(pclCharServer != NULL )
				{
					// pvp���� �ߵ� ���� �ʴ´�
					if(pclCharServer->siEnemUnique > 0 )
					{
					}
					else
					{
						SI32 siValue =  pclCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_DEFENSE_SUMMON );
						if ( 0 < siValue )
						{
							// ��ȯ�Ѵ� ���͸� 
							// ������ ��ȯ �ؾ���
							// ������ 20�� IDENTITY_SOULGUARD_SUMMONPUMKIN

							///myid�� ���Ǿ� ���� �ƴ��� Ȯ�� �Ѵ�.

							cltInnerStatusInfo clinnerstatus;
							clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLNPC, 0);

							cltIdentity clIdentity;
							clIdentity.MakeRaccoonDodgeEvent(IDENTITY_SOULGUARD_SUMMONPUMKIN);

							SI32 siMonsterKind	=	siValue	;
							SI32 siRocX		=	pclCharServer->GetX()	;// ���� ��ġ
							SI32 siRocY		=	pclCharServer->GetY()	;
							SI32 siMapIndex	=	pclCharServer->GetMapIndex()	;

							SI32 siEnergy	=	5000	;	// �̰� ������ �� �ɷ��� �޾� �;� �ϴµ� ..
							SI32 siLevel	=	99	;


							SI32 id = SetNPCChar( siMonsterKind,
								VILLAGE_NONE, 
								&clIdentity, 
								siLevel, 
								siEnergy, 
								siRocX, 
								siRocY,
								siMapIndex, 
								NPCITEMMODE_NONE, 
								&clinnerstatus );

							// �ش� npc�� �� ���� 
							cltCharServer* pclCharServer_Summon = pclCM->GetCharServer(id)	;
							if( pclCharServer_Summon != NULL)// ���������� ��ȯ�� �Ǿ��ٸ� 
							{
								pclCharServer_Summon->SetReservedAttackTargetID( myid)	;
								// 20�� �ڿ� �װ� �Ϸ��� �ð� ���� 
								pclCharServer_Summon->dwTimerClock = CurrentClock;
							}
						}

					}
				}
			}
			
		}
	}


	// ���Һ� ����
	if ( pclClient->IsCountrySwitch(Switch_BokBulBok))
	{
		cltCharServer* pclAttackChar = pclCM->GetCharServer( myid );	// �������

		if ( pclAttackChar != NULL )
		{
			cltCharCommon* pclDamagedChar = pclCM->GetChar( attackid )	;// ���� ���

			SI32 siDamagedMapIndex = pclDamagedChar->GetMapIndex();
			SI32 siAttackerMapIndex = pclAttackChar->GetMapIndex();

			if ( siDamagedMapIndex == siAttackerMapIndex ) // 97 & 
			{
				cltMapCommon* pDamagedMap = pclMapManager->GetMapPointer( siDamagedMapIndex );
				cltMapCommon* pAttackerMap = pclMapManager->GetMapPointer( siAttackerMapIndex );

				if ( NULL != pDamagedMap && NULL != pAttackerMap )
				{
					SI32 siDamagedColl = pDamagedMap->CalcCollInfo( pclDamagedChar->GetX(), pclDamagedChar->GetY() );
					SI32 siAttackerColl = pAttackerMap->CalcCollInfo( pclAttackChar->GetX(), pclAttackChar->GetY() );

					if ( siDamagedColl == siAttackerColl )
					{
						if ( pclDamagedChar->clIdentity.siIdentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
						{
							pclClient->m_pServer_BBBMgr->StageFail( myid );
						}

						/*else if ( pclDamagedChar->clIdentity.siIdentity == IDENTITY_BOKBULBOK_EVENTMONSTER ||
							pclDamagedChar->clIdentity.siIdentity == IDENTITY_BOKBULBOK_KEYMONSTER )
						{
						}*/
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
					//return FALSE;
				}
			}
			else
			{
				//return FALSE;
			}
		}
		else
		{
			//return FALSE;
		}
	}

	// �ǰݵǰ� ������ �˸���. 
	if(pclCM->IsAlive(attackid) )
	{
		((cltCharServer*)pclCM->CR[attackid])->SetBeAttackedSwitch(this, myid);
	}

	// ���߷��� �ٰŷ� Ÿ�� ���θ� �����Ѵ�.
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SI16 randHit = rand() % 10000;
		//SI32 lastHitVal = 0 ;

		//if(pcltarget->siDodgeRate > 0)
		//	lastHitVal = (pcltarget->siHitRate - (pcltarget->siDodgeRate/2));
		//else	
		//	lastHitVal = pcltarget->siHitRate;

		//(pcltarget->siHitRate < randHitRate)||( pcltarget->siDodgeRate >randDodgeRate)

		UI08 type = 0;
		if( true == pclCM->CR[attackid]->pclKI->IsAtb( ATB_MONSTER ) )	{		type = 0;		}
		else															{		type = 1;		}

		// DODGE
		if( pcltarget->siHitRate < randHit && randHit <= pcltarget->siHitRate + (pcltarget->siDodgeRate/2) )
		{
			cltGameMsgResponse_Hit clHitInfo(pclCM->CR[attackid]->GetCharUnique(), 0, 0, 0, 0, 0, false, false, true, type );
			cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
			((cltCharServer*)pclCM->CR[myid])->SendNeighbourMsg(&clMsg, true);

			return FALSE;
		}
		// MISS
		else if ( pcltarget->siHitRate + (pcltarget->siDodgeRate/2) < randHit )
		{
			cltGameMsgResponse_Hit clHitInfo(pclCM->CR[attackid]->GetCharUnique(), 0, 0, 0, 0, 0, false, true, false, type );
			cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
			((cltCharServer*)pclCM->CR[myid])->SendNeighbourMsg(&clMsg, true);

			return FALSE;
		}

		//if( lastHitVal < randHit)
		//{
		//	cltGameMsgResponse_Hit clHitInfo(pclCM->CR[attackid]->GetCharUnique(), 0, 0, 0, 0, 0, false, false, true, type );
		//	cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
		//	((cltCharServer*)pclCM->CR[myid])->SendNeighbourMsg(&clMsg, true);

		//	return FALSE;
		//}
	}
	else
	{
		if(rand() % 100 > pcltarget->siHitRate)
		{
			UI08 type = 0;
			if( true == pclCM->CR[attackid]->pclKI->IsAtb( ATB_MONSTER ) )
			{
				type = 0;
			}
			else
			{
				type = 1;
			}

			cltGameMsgResponse_Hit clHitInfo(pclCM->CR[attackid]->GetCharUnique(), 0, 0, 0, 0, 0, false, true, false, type );
			cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
			((cltCharServer*)pclCM->CR[myid])->SendNeighbourMsg(&clMsg, true);

			return FALSE;
		}
	}

	// ���� ���� �Ӽ�. 
	SI32 rangeflag = 0;
	if(pcldamageinfo->siAttackType >= 0 && pcldamageinfo->siAttackType < MAX_ATTACKTYPE_NUMBER )
		rangeflag = pclAttackTypeInfoManager->pclAttackTypeInfo[pcldamageinfo->siAttackType]->GetFlagRange();

	if( rangeflag & ATTACKTYPE_ATB_RANGE1 )
	{
		// �����ڰ� ��ȿ�ϸ� ����. 
		if(pclCM->IsAlive(myid)==FALSE)return FALSE;
		// ��ǥ�� ��ȿ�ϸ� ����
		if(pclCM->IsAlive(attackid)==FALSE)return FALSE;

		//[����] ���̸� ���� �˻� ���� �ʴ´�.
		if(		false == pclCM->CR[attackid]->clInnerStatus.IsStatus(INNERSTATUS_POISON)
			||	false == pclCM->CR[attackid]->clInnerStatus.IsStatus(INNERSTATUS_POISON_SETITEM_EFFECT) )
		{
			// ���� ���� �� �־�� �Ѵ�. 
			if(pclCM->CR[attackid]->GetMapIndex() != pclCM->CR[myid]->GetMapIndex())
				return FALSE;
		}

		if(pclCM->CR[myid]->IsInRange(attackid, range))
		{
			clList.Push(attackid, pcldamageinfo);
		}

	}
	else if( rangeflag & ATTACKTYPE_ATB_RANGE2 )
	{
		// ��ǥ�� ��ȿ�ϸ� ����, 
		if(pclCM->IsAlive(attackid)==FALSE)return FALSE;

		//[����] ���̸� ���� �˻� ���� �ʴ´�.
		if(		false == pclCM->CR[attackid]->clInnerStatus.IsStatus(INNERSTATUS_POISON)
			||	false == pclCM->CR[attackid]->clInnerStatus.IsStatus(INNERSTATUS_POISON_SETITEM_EFFECT)	)
		{
			// ���� ���� �� �־�� �Ѵ�. 
			if(pclCM->CR[attackid]->GetMapIndex() != pclCM->CR[myid]->GetMapIndex())return FALSE;
		}

		clList.Push(attackid, pcldamageinfo);
	}

	else if( rangeflag & ATTACKTYPE_ATB_RANGE3 )
	{
		if(range<=0)range = 2;

		// �����ڰ� ��ȿ�ϸ� ����. 
		if(pclCM->IsValidID(myid)==FALSE)return FALSE;


		SI32 index = 0;
		while(id = pclCM->GetCharOrder(index))
		{
			index++;

			if( pclCM->IsAlive(id) && pclCM->CR[myid]->IsEnemy(id) == true )
			{
				// ���� ���� �� �־�� �Ѵ�. 
				if(pclCM->CR[id]->GetMapIndex() != pclCM->CR[myid]->GetMapIndex())continue;

				if(clList.IsInList(id) == FALSE)
				{
					length		=	max(TABS(pclCM->CR[id]->GetX() - dx), TABS(pclCM->CR[id]->GetY() - dy));
					if(length > range)continue;

					realpower	=	pcldamageinfo->siDamage - pcldamageinfo->siDamage*( length*100 / (range+1) )/100;

					cltAttackDamageInfo cldamage;
					cldamage.Set(pcldamageinfo);
					cldamage.siDamage = realpower;

					clList.Push(id, &cldamage);
				}
			}
		}

	} 
	else
	{
		MsgBox(TEXT("A1284"), TEXT("attacktype:%d kind:%d"), pcldamageinfo->siAttackType, pclCM->CR[myid]->GetKind());
	}


	//------------------------------------------
	// �����ؾ� �� Ÿ���� �����Ѵ�. 
	//------------------------------------------
	SI32 hitid;
	cltAttackDamageInfo cldamageinfo;
	SI32 siCriticalRate = 0;
	while(clList.Pop(&hitid, &cldamageinfo) == TRUE)
	{
		// �ʻ��� �۵��ϸ� ���ݷ��� 2��� �ش�. 
		siCriticalRate = pclCM->CR[myid]->clPB.GetCriticalRate();

		//���� �Ѿ˿� ���� ũ��Ƽ�� �����[����]
		if (pclCM->CR[myid]->pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].siUnique == ITEMUNIQUE(13601) ||
			pclCM->CR[myid]->pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].siUnique == ITEMUNIQUE(13601) ||
			pclCM->CR[myid]->pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].siUnique == ITEMUNIQUE(13600) || 
			pclCM->CR[myid]->pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].siUnique == ITEMUNIQUE(13600))
		{
			siCriticalRate = siCriticalRate +((siCriticalRate/100)*5);
		}

		// ������ ������ �޴� Critical�� ���Ѵ�.
		if(pclCM->CR[myid]->clInnerStatus.IsStatus(INNERSTATUS_CURSECRITICAL))
		{
			siCriticalRate -= siCriticalRate * pclCM->CR[myid]->siCurseCriticalPower / 100;
		}

		// ���� ������ ���� ũ��Ƽ�÷� ���
		if ( IsPC(myid) )
		{
			SI32 siAddCriticalRate = pclCM->CR[myid]->m_clMagicBufMgr.GetIncCriticalRate( pclCM->CR[myid] );
			if ( siAddCriticalRate )
			{
				SI32 siCalcCriticalRate = ((siCriticalRate / 100) * siAddCriticalRate);
				siCriticalRate += siCalcCriticalRate;
				pclClient->pclLog->LogPrint( TEXT("ũ��Ƽ�� ���� : %d\n"), siCriticalRate );
			}
		}

		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			//[����] ��Ʈ ������ ���� ���� ũ��Ƽ�÷� ����.
			if( pclCM->CR[myid]->m_siSetItemType )
			{
				siCriticalRate += siCriticalRate *	(	pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_CRITICAL, USE_SETITEM_1 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_CRITICAL, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_CRITICAL, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_CRITICAL, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_CRITICAL, USE_SETITEM_5 )) / 100;
			}
		}

		// PCK: ���ڹ����߰� - ���ڹ����� �ɷ��ְ�, Ż���� ź�����̸� 5%�� Ȯ���� �߰�Ÿ�� �־��ش�. (ũ��Ƽ�ð� ���� ���)
		// ��, ǥ���ϴ� ����� ũ��Ƽ�� ������ / 2 �ؼ� ���� �������� ǥ���ϴ� ������� �Ѵ�.

		cltCharServer *Mypclchar = (cltCharServer*)pclCM->CR[myid];
		cltBufInfo clBuf;
		clBuf.SetBuf( &Mypclchar->pclCI->clBI.clBufInfo );

		if(pclCM->IsAlive(myid))
		{
			if(siCriticalRate > (rand() % 1000))
			{
				Hit(myid, hitid, &cldamageinfo, 1);
			}
			else
			{
				if(clBuf.IsHaveBuf(BUF_WATERMELON) && (Mypclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE) && (rand() % 100 < 20))
				{
					Hit(myid, hitid, &cldamageinfo, 2);
				}
				else
				{
					Hit(myid, hitid, &cldamageinfo, 0);
				}
			}
		}

		//PCK : ��ȣ���� Ư���ɷ� - ���Ϳ��� ������ ����Ȯ���� ������ �߻��Ѵ�.(09.07.07)
		if(IsCountrySwitch(Switch_SoulGuard))
		{
			if( IsPC( attackid ) )
			{	
				SI32 siMagicUnique = ((cltCharServer*)pclCM->CR[attackid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_DEFENSE_MAGIC );
				SI32 returnval = 0;

				if ( 0 < siMagicUnique )
				{
					SendServerResponseMsg(0, SRVAL_RETURN_SOULGUARD_SHOT_MAGIC,  myid, siMagicUnique, pclCM->CR[attackid]->GetCharUnique());
				}
			}
			if( IsPC( myid ) )  // myid  - ���� , attackid - �´»��
			{
				// ���� �Ҷ� ���� Ȯ���� ������ ��� ��Ų
				cltCharServer* pCharServer = pclCM->GetCharServer( myid)	;
				if(pCharServer != NULL)
				{
					SI32 siMagicUnique = pCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_ATTACK_MAGIC )	;
					if(siMagicUnique > 0 )
					{
						SendServerResponseMsg(0, SRVAL_RETURN_SOULGUARD_SHOT_MAGIC,  attackid  , siMagicUnique, pclCM->CR[myid]->GetCharUnique() );
					}
				}
			}
			if( IsPC( myid ) )
			{
				// ���� �Ҷ� ���� Ȯ���� ������ ��� ��Ų
				cltCharServer* pCharServer = pclCM->GetCharServer( myid)	;
				if(pCharServer != NULL)
				{
					// ���ϰ����� �Ѵ�
					SI32 siValue =  pCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_ATTACK_STUN );
					if ( 0 < siValue )
					{
						cltCharServer* pCharServer_Enemy = pclCM->GetCharServer( attackid )	;
						if(NULL != pCharServer_Enemy)
						{
							pCharServer_Enemy->SetStun(siValue );
						}
					}
				}
			}
			if( IsPC( myid ) )
			{
				// ���� �Ҷ� ���� Ȯ���� ������ ��� ��������
				cltCharServer* pCharServer = pclCM->GetCharServer( myid)	;
				if(pCharServer != NULL)
				{
					// �󸰴�.
					SI32 siValue =  pCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_ATTACK_SOULICE );
					if ( 0 < siValue )
					{
						cltCharServer* pCharServer_Enemy = pclCM->GetCharServer( attackid )	;
						if(NULL != pCharServer_Enemy)
						{
							pCharServer_Enemy->SetSoulGuardIce(siValue );	// �ʸ� �ִ´� 
						}
					}
				}
			}
		}
	}

	
	if( IsPC(myid) && 0 < pcldamageinfo->siMagicKind )
	{
		AddMagicAction( myid, attackid, pcldamageinfo->siMagicKind, cldamageinfo.siDamage );
		SubMagicAction( myid, attackid, pcldamageinfo->siMagicKind, cldamageinfo.siDamage );
	}

	return TRUE;
}

SI32 cltServer::GetEnchantDefen(SI32 AttackType, SI32 defenid)
{
	SI32 EnchantDef = 0;
	if(IsPC(defenid))
	{
		cltItem *pclItemList = pclCM->CR[defenid]->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
		EnchantDef = pclCM->CR[defenid]->clPB.GetEnchantDefDamage(AttackType, pclItemList);  		
	}

	return EnchantDef;
}


// ���ݼӼ�, ���ݷ�, ���ݴ���� ����Ͽ� ���� ���ظ� ����Ѵ�. 
bool cltServer::GetDamage(cltAttackDamageInfo* pcldamageinfo, SI32 myid, SI32 attackid, UI08 specialattackswitch, cltAttackDamageInfo* pclreturndamageinfo)
{
	// ���� ��ǥ�� �̹� ��ȿ���� ������ ��� �� �� ����.
	if( pclCM->IsAlive( attackid ) == FALSE )
		return false;

	// �ߵ��Ǿ� �ִ� ���¿����� Ÿ�̸� Ÿ���� ������ �������� ������� �ʰ� ���ݷ��� �״�� �������� �����Ѵ�. 
	if( pcldamageinfo->siAttackType == ATTACKTYPE_POISONSTATUS )
	{
		pclreturndamageinfo->Set( pcldamageinfo );
		return true;
	}
	// ���� �پ� �ִ� ���¿����� Ÿ�̸� Ÿ���� ������ �������� ������� �ʰ� ���ݷ��� �״�� �������� �����Ѵ�. 
	if( pcldamageinfo->siAttackType == ATTACKTYPE_MAGICFIRESTATUS )
	{
		pclreturndamageinfo->Set( pcldamageinfo );
		return true;
	}
	//-----------------------------
	// ���¿� ���� ����ġ ���. 
	//-----------------------------
	SI32 validpower = 0;

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		// �ǰ����� ����. 
		SI32 magickind = pcldamageinfo->siMagicKind;
		if(magickind < MAGIC_INDEX_START || magickind  > MAGIC_INDEX_LAST)	magickind = 0;

		SI32 defensiveRate = 0; 

		if(magickind>0)
		{
			defensiveRate= pclCM->CR[attackid]->clPB.GetDefensiveRate( pclCM->CR[myid],true);
		}
		else
		{
			defensiveRate= pclCM->CR[attackid]->clPB.GetDefensiveRate( pclCM->CR[myid]);
			// �������� ���� ������� ���� �ش� 
			cltCharServer* pclCharServer = pclCM->GetCharServer( attackid )	;
			if(pclCharServer != NULL )
			{
				SI32 siValue =  pclCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_ATTACK_DEFENSE );
				if ( 0 < siValue )
				{
					defensiveRate	=	defensiveRate	+ ( siValue * 100);
				}
			}
		}

		if(defensiveRate >0)
		{

			validpower = (pcldamageinfo->siDamage) - (((pcldamageinfo->siDamage) * defensiveRate)/10000);
		}
		else
		{
			validpower = pcldamageinfo->siDamage;
		}

	}
	else
	{
		// �ǰ����� ����. 
		SI32 ac = pclCM->CR[attackid]->clPB.GetTotalAC();

		// ���ݷ� ���Һ�. 
		SI32 decpower;
		if((pcldamageinfo->siDamage + ac) == 0)
		{
			decpower = 0;
		}
		else
		{
			//cyj ���¿� ���� �������氨ȿ�� 2��� ����(2005.12.20)
			//cyj ���¿� ���� �������氨ȿ�� 1.3��� ����(2005.12.26)
			//decpower = (pcldamageinfo->siDamage * ac)/((pcldamageinfo->siDamage*2) + ac*8/10) ;
			//decpower = ( (pcldamageinfo->siDamage * ac)/((pcldamageinfo->siDamage*2) + ac*8/10) ) * 2;
			decpower = ( (pcldamageinfo->siDamage * ac)/((pcldamageinfo->siDamage*2) + ac*8/10) ) * 1.3;
		}

		validpower	= pcldamageinfo->siDamage - decpower;
	}

	if( validpower <= 0 )	validpower = 1;

	//------------------------------
	// �ǰ����� ������ ����ġ�� �ִٸ�, 
	//-------------------------------
	if(pclCM->CR[attackid]->clPB.siEquipAssistDamageReduceRate)
	{
		validpower = max(1, validpower - (validpower * pclCM->CR[attackid]->clPB.siEquipAssistDamageReduceRate / 1000) );
	}

	//-------------------------------------------------
	// ���ݷ¿� ���� ��æƮ ����ϱ�    by tae-yang
	//-------------------------------------------------

	SI32 TotalEnchantPowerA		= 0;
	SI32 A_enchantTypeDef		= 0;
	SI32 A_enchantPowerDef		= 0;
	SI32 My_EnchantPowerAttack	= 0;
	SI32 My_enchantTypeAttack	= 0;

	SI32 monsterkind	  =  pclCM->CR[attackid]->GetKind();
	REAL32 monster_fire   = 0;
	REAL32 monster_water  = 0;
	REAL32 monster_wind   = 0;
	REAL32 monster_land   = 0;	
	REAL32 monster_nature = 0;

	if( monsterkind > 0)
	{
		if(pclCM->CR[attackid]->clIdentity.siIdentity == IDENTITY_GMCREATE_MONSTER)
		{
			monster_fire   = pclKindInfoSet->pclGMCommandKindInfo[monsterkind]->clCharElemental.GetFire();
			monster_water  = pclKindInfoSet->pclGMCommandKindInfo[monsterkind]->clCharElemental.GetWater();
			monster_wind   = pclKindInfoSet->pclGMCommandKindInfo[monsterkind]->clCharElemental.GetWind();
			monster_land   = pclKindInfoSet->pclGMCommandKindInfo[monsterkind]->clCharElemental.GetLand();	
			monster_nature = pclKindInfoSet->pclGMCommandKindInfo[monsterkind]->clCharElemental.GetNature();
		}
		else
		{
			monster_fire   = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetFire();
			monster_water  = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWater();
			monster_wind   = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWind();
			monster_land   = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetLand();	
			monster_nature = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetNature();
		}
	}

	SI32 bflag = false;

	//validpower = validpower - TotalEnchantPowerA;

	if(IsPC(myid) || (pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON))
	{
		//SI32 equiploc = PERSONITEM_SUMMON1EQUIP0;
		SI32		enchanttype		= 0;
		SI32		enchantgrade	= 0;

		cltItem		*pclItemList	= pclCM->CR[myid]->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);

		if(pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			bflag =true;

			/*
			//equipset = EQUIPSET_SUMMON1;   //0 �϶� 
			if(pclCM->CR[myid]->GetSummonIndex() == 1)
			{
				//equipset = EQUIPSET_SUMMON2;    // 1�϶� 
				equiploc = PERSONITEM_SUMMON2EQUIP0;
			}


			myid = pclCM->CR[myid]->clIdentity.clSummonInfo.siParentCharUnique;
			enchanttype = pclCM->CR[myid]->clPB.pclCI->clCharItem.clItem[equiploc + 2].Element.siType; 
			enchantgrade =  pclCM->CR[myid]->clPB.pclCI->clCharItem.clItem[equiploc + 2].Element.siPower;
			*/
				SI32 siSummonIndex = pclCM->CR[myid]->GetSummonIndex();

			myid = pclCM->CR[myid]->clIdentity.clSummonInfo.siParentCharUnique;
			if ( false == pclCM->IsValidID( myid ) )
			{
				return false;
			}

			if ( pclCM->CR[myid]->clPB.pclCI->clSummonInfo.GetSummonEquipItem(siSummonIndex, 2) )
			{
				cltItem clSummonWeapon;
				clSummonWeapon.Set( pclCM->CR[myid]->clPB.pclCI->clSummonInfo.GetSummonEquipItem(siSummonIndex, 2) );

				enchanttype		= clSummonWeapon.Element.siType;
				enchantgrade	= clSummonWeapon.Element.siPower;
			}
			else
			{
				enchanttype		= 0;
				enchantgrade	= 0;
			}

			pclItemList	= pclCM->CR[myid]->clPB.pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex );
		}

		if ( NULL == pclItemList )
		{
			return false;
		}

		if(bflag == false) // �����ڰ� ��ȯ���� �ƴҰ��
		{
			enchanttype  = pclCM->CR[myid]->clPB.pclCI->clCharItem.clItem[pclCM->CR[myid]->ActiveWeapon].Element.siType;
			enchantgrade = pclCM->CR[myid]->clPB.pclCI->clCharItem.clItem[pclCM->CR[myid]->ActiveWeapon].Element.siPower;
		}

		SI32 enchantdamage = pclItemManager->GetEnchantDamageFromGrade(enchantgrade);

		if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
		{
			cltCharServer *Mypclchar = (cltCharServer*)pclCM->CR[myid];
			SI16 Myactiveweaponpos = pclCM->CR[myid]->ActiveWeapon;

			//cltCharServer *Monpclchar = (cltCharServer*)pclCM->CR[attackid];
			//SI16 Monactiveweaponpos = pclCM->CR[attackid]->ActiveWeapon;
			//cltItem *MonpclItemList = pclCM->CR[attackid]->pclCI->clCharItem.GetEquipSet(equipset);

			SI16 addDamagePer = 0;

			switch(enchanttype)				
			{
			case ENCHANT_TYPE_FIRE_A:
				{
					if(IsPC(Mypclchar->GetCharUnique()))
					{						
						addDamagePer = pclItemManager->GetEquipCrystalFireAttack(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
						enchantdamage = enchantdamage + (SI32)(enchantdamage *addDamagePer /100);
					}
					enchantdamage =enchantdamage - (SI32)(enchantdamage * monster_fire /100 );

					if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
					{
						if( Mypclchar->m_siSetItemType )
						{
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK, USE_SETITEM_1);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK, USE_SETITEM_2);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK, USE_SETITEM_3);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK, USE_SETITEM_4);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_ATTACK, USE_SETITEM_5);
						}
					}

					// PCK : ��ȣ���� - �Ҿ������� ��ȯ�Ǿ� ������ �ҼӼ� �������� 1.5�� ������ (09.07.08)
					// SOULGUARD_ABILITY_ELEMENTDAMAGE_UP�ʹ� ������ ����ȴ�. (�⺻ �ɷ���)
					if(pclClient->IsCountrySwitch(Switch_SoulGuard))
					{
						if(Mypclchar->IsSoulGuardStatusOut() == TRUE && Mypclchar->pclSoulGuard->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SOULGUARD_FIRESPIRIT")))
						{
							enchantdamage = enchantdamage * 150 / 100;
						}
					}
				}
				break;
			case ENCHANT_TYPE_WATER_A:
				{
					if(IsPC(Mypclchar->GetCharUnique()))
					{						
						addDamagePer = pclItemManager->GetEquipCrystalWaterAttack(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
						enchantdamage = enchantdamage + (SI32)(enchantdamage *addDamagePer /100);
					}
					enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_water / 100);

					if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
					{
						if( Mypclchar->m_siSetItemType )
						{
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK, USE_SETITEM_1);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK, USE_SETITEM_2);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK, USE_SETITEM_3);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK, USE_SETITEM_4);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_ATTACK, USE_SETITEM_5);
						}
					}
					// �������� - ���Ӽ� ���ݷ� 1.5�� ���� (�⺻�ɷ�)
					if(pclClient->IsCountrySwitch(Switch_SoulGuard))
					{
						if(Mypclchar->IsSoulGuardStatusOut() == TRUE && Mypclchar->pclSoulGuard->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SOULGUARD_ICESPIRIT")))
						{
							enchantdamage = enchantdamage * 150 / 100;
						}
					}
				}
				break;
			case ENCHANT_TYPE_WIND_A:
				{
					if(IsPC(Mypclchar->GetCharUnique()))
					{						
						addDamagePer = pclItemManager->GetEquipCrystalWindAttack(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
						enchantdamage = enchantdamage + (SI32)(enchantdamage *addDamagePer /100);
					}
					enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_wind / 100 );

					if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
					{
						if( Mypclchar->m_siSetItemType )
						{
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK, USE_SETITEM_1);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK, USE_SETITEM_2);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK, USE_SETITEM_3);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK, USE_SETITEM_4);
							enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_ATTACK, USE_SETITEM_5);
						}
					}
				}				
				break;
			case ENCHANT_TYPE_GROUND_A:
				{
					if(IsPC(Mypclchar->GetCharUnique()))
					{						
						addDamagePer = pclItemManager->GetEquipCrystalEarthAttack(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
						enchantdamage = enchantdamage + (SI32)(enchantdamage *addDamagePer /100);
					}
					enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_wind / 100 );
				}
				enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_land / 100);


				if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
				{
					if( Mypclchar->m_siSetItemType )
					{
						enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK, USE_SETITEM_1);
						enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK, USE_SETITEM_2);
						enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK, USE_SETITEM_3);
						enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK, USE_SETITEM_4);
						enchantdamage += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_ATTACK, USE_SETITEM_5);
					}
				}


				break;
			default:
				break;
			}
		}
		else
		{
			switch(enchanttype)
			{
			case ENCHANT_TYPE_FIRE_A:
				enchantdamage =enchantdamage - (SI32)(enchantdamage * monster_fire /100 );
				break;
			case ENCHANT_TYPE_WATER_A:
				enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_water / 100);
				break;
			case ENCHANT_TYPE_WIND_A:
				enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_wind / 100 );
				break;
			case ENCHANT_TYPE_GROUND_A:
				enchantdamage =enchantdamage- (SI32)(enchantdamage *monster_land / 100);
				break;
			default:
				break;

			}
		}

		if(enchantdamage<0)
			enchantdamage = 0;

		if ( IsCountrySwitch(Switch_SoulGuard) )
		{
			SI32 siSoulGuardAddEnchantDamage = ((cltCharServer*)pclCM->CR[myid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_ELEMENTDAMAGE_UP );
			if ( 0 < siSoulGuardAddEnchantDamage )
			{
				enchantdamage += siSoulGuardAddEnchantDamage;
			}
		}

		//�������� ��� 
		if(monster_nature)
		{
			validpower  =  validpower - (SI32)(monster_nature * 0.01 * (REAL32)validpower);
			//	validpower = (SI32)temp;
		}

		validpower =  validpower + enchantdamage;
	}

	else if(IsNPC(myid))
	{
		monsterkind =  pclCM->CR[myid]->GetKind();
		SI32 monster_fireA = 0;
		SI32 monster_waterA =0;
		SI32 monster_windA = 0;
		SI32 monster_landA = 0;	

		if(monsterkind > 0)
		{
			monster_fireA = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetFireA();
			monster_waterA = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWaterA();
			monster_windA = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWindA();
			monster_landA = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetLandA();	

		}

		//���͸��� ... ��� �ɱ�? 
		validpower = validpower + monster_fireA + monster_waterA + monster_windA + monster_landA;
		if(monster_nature)
		{
			validpower= validpower + (SI32)(monster_nature * 0.01 * (REAL32)validpower);
		}

		//	REAL32 temp = 0;
		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if( pclCM->CR[attackid]->m_siSetItemType )
			{
				validpower -= validpower *  (   pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_NATURE, USE_SETITEM_1)
											  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_NATURE, USE_SETITEM_2)
											  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_NATURE, USE_SETITEM_3)
											  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_NATURE, USE_SETITEM_4)
											  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_NATURE, USE_SETITEM_5)) / 100;
			}
		}
	}

	//--------------------------------------------------
	// ���¿� ���� ��æƮ ����ϱ�     by tae-yang
	//--------------------------------------------------

	monsterkind =  pclCM->CR[myid]->GetKind();

	SI32 monster_fireA = 0; 
	SI32 monster_waterA =0; 
	SI32 monster_windA = 0; 
	SI32 monster_landA = 0; 


	if(monsterkind > 0 )
	{
		monster_fireA  = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetFireA();
		monster_waterA = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWaterA();
		monster_windA  = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetWindA();
		monster_landA  = pclKindInfoSet->pclKI[monsterkind]->pclCharElemental.GetLandA();	
	}


	SI32 A_enchantType = 0;
	SI32 enchantPercent = 0;
	SI32 enchantac = 0;

	for(SI32 i =0; i < 4; i++)
	{
		A_enchantType = i*2 + 2;		

		if(IsPC(attackid))
		{
			cltItem *pclItemList = pclCM->CR[attackid]->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
			enchantPercent = pclCM->CR[attackid]->clPB.GetEnchantDefDamage(A_enchantType, pclItemList); 

			if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
			{
				SI16 addPer = 0;

				cltCharServer *Mypclchar = (cltCharServer*)pclCM->CR[attackid];
				SI16 Myactiveweaponpos = pclCM->CR[attackid]->ActiveWeapon;

				switch(A_enchantType)
				{
				case ENCHANT_TYPE_FIRE_D:
					{
						enchantac = 0;

						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							SI32 siValue = 0;
							if( Mypclchar->m_siSetItemType )
							{

								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}
							}

							enchantac = ( enchantPercent * monster_fireA  / 100 );
							enchantac += (enchantac * (siValue / 100));
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{

								enchantac = ( enchantPercent * monster_fireA / 100 ) + ( 40 * monster_fireA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_fireA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac = 0;
						else
						{						
							addPer = pclItemManager->GetEquipCrystalFireDeffence(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
							enchantac = enchantac + (SI32)(enchantac * addPer /100);
						}

						validpower = validpower - enchantac;
					}
					break;

				case ENCHANT_TYPE_WATER_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							SI32 siValue = 0;
							if( Mypclchar->m_siSetItemType ) 
							{
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}	
							}

							enchantac  = ( enchantPercent * monster_waterA  / 100 );
							enchantac += (enchantac * (siValue / 100));
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_waterA / 100 ) + ( 40 * monster_waterA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_waterA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						else
						{						
							addPer = pclItemManager->GetEquipCrystalWaterDeffence(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
							enchantac = enchantac + (SI32)(enchantac *addPer /100);
						}

						validpower = validpower - enchantac;

					}
					break;

				case ENCHANT_TYPE_WIND_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							SI32 siValue = 0;
							if( Mypclchar->m_siSetItemType )
							{
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}
							}

							enchantac  = ( enchantPercent * monster_windA  / 100 );
							enchantac += (enchantac * (siValue / 100));

						}
						else
						{

							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_windA / 100 ) + ( 40 * monster_windA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_windA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						else
						{						
							addPer = pclItemManager->GetEquipCrystalWindDeffence(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
							enchantac = enchantac + (SI32)(enchantac *addPer /100);
						}

						validpower = validpower - enchantac;
					}
					break;

				case ENCHANT_TYPE_GROUND_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							SI32 siValue = 0;
							if( Mypclchar->m_siSetItemType )
							{
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(Mypclchar, SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}
							}

							enchantac  = ( enchantPercent * monster_landA  / 100 );
							enchantac += (enchantac * (siValue / 100));
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_landA / 100 ) + ( 40 * monster_landA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_landA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						else
						{						
							addPer = pclItemManager->GetEquipCrystalEarthDeffence(pclItemList,Myactiveweaponpos,Mypclchar); // ���� ���� ���ݷ��� ���Ѵ�.
							enchantac = enchantac + (SI32)(enchantac *addPer /100);
						}

						validpower = validpower - enchantac;
					}
					break;

				default:
					break;

				}		
			}
			else	// if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
			{
				switch(A_enchantType)
				{
				case ENCHANT_TYPE_FIRE_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							if( pclCM->CR[attackid]->m_siSetItemType ) 
							{
								SI32 siValue = 0;
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_FIRE_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}

								enchantac = ( enchantPercent * monster_fireA / 100 );
								enchantac += (enchantac * (siValue / 100));
							}

						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_fireA / 100 ) + ( 40 * monster_fireA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_fireA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						validpower = validpower - enchantac;
					}
					break;
				case ENCHANT_TYPE_WATER_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							if( pclCM->CR[attackid]->m_siSetItemType ) 
							{
								SI32 siValue = 0;
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WATER_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}

								enchantac  = ( enchantPercent * monster_waterA / 100 );
								enchantac += (enchantac * (siValue / 100));
							}
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_waterA / 100 ) + ( 40 * monster_waterA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_waterA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						validpower = validpower - enchantac;

					}
					break;
				case ENCHANT_TYPE_WIND_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							if( pclCM->CR[attackid]->m_siSetItemType ) 
							{
								SI32 siValue = 0;
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_WIND_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}

								enchantac  = ( enchantPercent * monster_windA / 100 );
								enchantac += (enchantac * (siValue / 100));
							}
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_windA / 100 ) + ( 40 * monster_windA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_windA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						validpower = validpower - enchantac;
					}
					break;
				case ENCHANT_TYPE_GROUND_D:
					{
						enchantac = 0;
						if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
						{
							if( pclCM->CR[attackid]->m_siSetItemType ) 
							{
								SI32 siValue = 0;
								cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
								if( pcltSetItemAbilityManager ) 
								{
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_1 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_2 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_3 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_4 );
									siValue += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[attackid], SETITEM_ABILITY_TYPE_LAND_ENCHANT_DEFENSIVE, USE_SETITEM_5 );
								}

								enchantac  = ( enchantPercent * monster_landA / 100 );
								enchantac += (enchantac * (siValue / 100));
							}
						}
						else
						{
							if( pclCM->CR[attackid]->m_siSetItemType == VAMPIRE_SETITEM )
							{
								enchantac = ( enchantPercent * monster_landA / 100 ) + ( 40 * monster_landA / 100 );
							}
							else
							{
								if(enchantPercent)
								{
									enchantac = enchantPercent * monster_landA / 100; 
								}
							}
						}

						if(enchantac < 0)
							enchantac= 0;
						validpower = validpower - enchantac;
					}
					break;
				default:
					break;

				}	// switch(A_enchantType)		
			}
			// ac = ac + enchantac;
		}
		// [����] ��ȯ�� ��� �Ӽ� ���� �߰�
		else if(pclCM->CR[attackid]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			cltCharServer* pclSummon = pclCM->GetCharServer( attackid );
			if ( NULL == pclSummon )
			{
				return false;
			}

			SI32 siSummonIndex	= pclSummon->GetSummonIndex();
			SI32 siParentCharID	= pclSummon->GetSummonParentID();

			cltCharServer* pclParent = pclCM->GetCharServer( siParentCharID );
			if ( NULL == pclParent )
			{
				return false;
			}

			// ������ ���⶧���� �켱 �ʱ�ȭ
			enchantPercent	= 0;
			enchantac		= 0;

			// ��ȯ���� ��� ���´�
			cltItem* pclItemList = pclParent->clPB.pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex );
			if ( pclItemList )
			{
				enchantPercent = pclSummon->clPB.GetEnchantDefDamage( A_enchantType, pclItemList );
			}

			// ���� ���� �Ӽ����� %�־�� ����Ѵ�
			if ( 0 < enchantPercent )
			{
				switch ( A_enchantType )
				{
				case ENCHANT_TYPE_FIRE_D:	{	enchantac = enchantPercent * monster_fireA/100;		}	break;
				case ENCHANT_TYPE_WATER_D:	{	enchantac = enchantPercent * monster_waterA/100;	}	break;
				case ENCHANT_TYPE_WIND_D:	{	enchantac = enchantPercent * monster_windA/100;		}	break;
				case ENCHANT_TYPE_GROUND_D:	{	enchantac = enchantPercent * monster_landA/100;		}	break;
				}		
			}

			if(enchantac < 0)
			{
				enchantac = 0;
			}
			// ���������� ���� ���������� ���ش�
			validpower = validpower - enchantac;
		}
		else if(IsNPC(attackid))
		{

		}
	}


	// �ִ� �������� �Ѱ谡 �ִ� ĳ���Ͷ��, (�ֱ������̺�Ʈ�� ĳ���Ͷ��,, ) 
	if(pclCM->CR[attackid]->pclKI->IsAtb( ATB_DAMAGELIMIT ))
	{
		validpower = min(300, validpower);
	}

	if(specialattackswitch == 1)	// ũ��Ƽ���̸�
	{
		//KHY - 1220 - ���Žý���.
		cltCharServer *pclChar = (cltCharServer *)pclCM->CR[myid];

		/*		if(pclChar->clTransFormInfo.bTransFormMode == true) //�������̰�.
		{
		//�ش� ���� ĳ���� ��ũ�� 100%�̸�.
		if(pclChar->clTransFormInfo.GetSynchroTransForm(pclChar->clTransFormInfo.uiNowTransFormKind) == 100)
		{
		SI32 attcktype =  pclChar->GetAttackType();

		switch(attcktype)
		{
		case ATTACKTYPE_AXE :
		validpower *= 2.2; //220%
		break;
		default:
		validpower *= 2;
		break;
		}

		}		
		}
		else
		*/
		{
			validpower *= 2;
		}
	}

	//--------------------------------------
	// ���������� ���� ������ 2��(�̰��� ����ȵ������� 2�谡 �ɼ��� ����, �׷��ٸ� �� 4��!!)
	//---------------------------------------
	if ( IsPC(myid) )
	{
		SI32 siSkillUnique = 0;

		switch ( pcldamageinfo->siAttackType )
		{
		case ATTACKTYPE_SWORD:
			siSkillUnique = SKILL_SWORD_SPEAR_DOUBLEAT;
			break;
		case ATTACKTYPE_SPEAR:
			siSkillUnique = SKILL_SPEAR_DOUBLEAT;
			break;
		case ATTACKTYPE_AXE:
			siSkillUnique = SKILL_AXE_SPEAR_DOUBLEAT;
			break;
		case ATTACKTYPE_STAFF:
		case ATTACKTYPE_STAFF1:
		case ATTACKTYPE_STAFF2:
		case ATTACKTYPE_NEW_STAFF2:
			siSkillUnique = SKILL_STAFF_SPEAR_DOUBLEAT;
			break;
		case ATTACKTYPE_BOW:
		case ATTACKTYPE_BOW1:
		case ATTACKTYPE_NEW_BOW1:
			siSkillUnique = SKILL_BOW_SPEAR_DOUBLEAT;
			break;
		case ATTACKTYPE_GUN:
		case ATTACKTYPE_GUN1:
		case ATTACKTYPE_NEW_GUN1:
			siSkillUnique = SKILL_GUN_SPEAR_DOUBLEAT;
			break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclCM->CR[myid]->pclCI->clCharSkill.GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI32 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				SI32 siRandValue = (rand() % 100) + 1;

				pclLog->LogPrint( TEXT("[WeaponSkill-DoubleAT] Rate:%d/RandValue:%d\n"), siWeaponSkillRate, siRandValue );

				if ( siWeaponSkillRate >= siRandValue )
				{
					validpower *= 2;
				}
			}
		}
	}

	//--------------------------------------
	// ������ ���� Curse Attack ������ �ɷ� ������ ���ݷ��� ���ҽ�Ų��.
	//--------------------------------------
	if(pclCM->CR[myid]->clInnerStatus.IsStatus(INNERSTATUS_CURSEATTACK))
	{
		validpower = max(1, validpower - (validpower * pclCM->CR[myid]->siCurseAttackPower/ 100) );
	}

	//--------------------------------------
	// �´� ���� Curse Defense ������ �ɷ� ������ ���ݷ��� ������Ų��.
	//--------------------------------------
	if(pclCM->CR[attackid]->clInnerStatus.IsStatus(INNERSTATUS_CURSEDEFENSE))
	{
		validpower = max(1, validpower + (validpower * pclCM->CR[attackid]->siCurseDefensePower/ 100) );
	}

	if ( IsPC(myid) )
	{
		//--------------------------------------
		// ���� ������ ���� ������ ����
		//--------------------------------------
		SI32 siAddDamage = pclCM->CR[myid]->m_clMagicBufMgr.GetIncDamage( pclCM->CR[myid] );
		if ( 0 < siAddDamage )
		{
			validpower += siAddDamage;
		}

		//--------------------------------------
		// ��ȣ���� Ư���ɷ� �ߵ��� ���� ������ ����
		//--------------------------------------
		if ( IsCountrySwitch(Switch_SoulGuard) )
		{
			SI32 siSoulGuardAddDamage = ((cltCharServer*)pclCM->CR[myid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_DAMAGE_UP );
			if ( 0 < siSoulGuardAddDamage )
			{
				validpower += siSoulGuardAddDamage;
			}
		}
	}

	//--------------------------------------
	// ��ȣ���� Ư���ɷ� �ߵ��� ���� ���Ϳ��� �Դ� ������ ����
	//--------------------------------------
	if ( IsCountrySwitch(Switch_SoulGuard) )
	{
		if ( IsNPC(myid) && IsPC(attackid) )
		{
			SI32 siSoulGuardSubDamage = ((cltCharServer*)pclCM->CR[attackid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_DAMAGE_DOWN );
			if ( 0 < siSoulGuardSubDamage )
			{
				validpower -= siSoulGuardSubDamage;
			}
		}
	}

	//--------------------------------------
	// XBOX EVENT	Damage = 1
	//--------------------------------------
	// �´� ���� �Ӽ��� Event XBox �Ӽ��� ������ Damage�� ������ 1
	if(pclCM->CR[attackid]->IsAtb(ATB_EVENTXBOX))
	{
		validpower = 1;
	}
	// ���������� ������ 10�� ��� ����
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER")) )
	{
		validpower = 10;
	}
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SANTARACCOON_ZIQ")) )
	{
		validpower = 1;
	}
	//[�߰� : ���� ���ϵ� ���� ������ 1�� �����ϰ�..., Ȳ���� 2007.9.18]
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_WILDBOARBOSS")) )
	{
		// �ѱ� �߼� �̺�Ʈ������.
		if(pclClient->IsCountrySwitch(Switch_BossWildBoar))
		{
			_SYSTEMTIME sTime;
			GetLocalTime(&sTime);

			// 15�ÿ� 22��.
			if((15 == sTime.wHour || 22 == sTime.wHour))	
			{
				// 22�� ���� 26�ϱ���.
				if(sTime.wDay >= 13 && sTime.wDay <= 15)
				{
					// 9��.
					if(9 == sTime.wMonth)
					{
						validpower = 1;
					}
				}
			}
		}
	}
	//[�߰� : �߼� ������ �̺�Ʈ. ĥ���� ������ 1�� �����ϰ�..., Ȳ���� 2007.9.18]
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_TURKEY")) )
	{
		// USA, GLOBAL ������.
		if(pclClient->IsCountrySwitch(Switch_Thanksgiving_day))
		{
			_SYSTEMTIME sTime;
			GetLocalTime(&sTime);

			switch(pclClient->siServiceArea)
			{
			case ConstServiceArea_English:
				{
					// 2��, 8��, 14��, 20��
					if((2 == sTime.wHour || 8 == sTime.wHour || 14 == sTime.wHour || 20 == sTime.wHour))	
					{
						// 20�� ���� 30�ϱ���. �Ǵ� 1�� ���� 4�ϱ���
						if( sTime.wDay >= 20 && sTime.wDay <= 30 )
						{
							// 11��, 12��
							if( 11 == sTime.wMonth )
							{
								validpower = 1;
							}
						}
						if( sTime.wDay >= 1 && sTime.wDay <= 4 )
						{
							if( 12 == sTime.wMonth )
							{
								// �������� 20�ô� �������� �� �̺�Ʈ�� ������ ������ ����.
								if(12 == sTime.wMonth && 4 == sTime.wDay && 20 == sTime.wHour)
									break;

								validpower = 1;
							}
						}
					}
				}
				break;
			case ConstServiceArea_USA:
				{
					// 2��, 8��, 14��, 20��
					if( 2 == sTime.wHour || 8 == sTime.wHour || 14 == sTime.wHour || 20 == sTime.wHour )
					{
						// 21�� ���� 30�ϱ���. �Ǵ� 1�� ���� 5�ϱ���
						if( sTime.wDay >= 21 && sTime.wDay <= 30 )
						{
							// 11��, 12��
							if( 11 == sTime.wMonth )
							{
								validpower = 1;
							}
						}

						if(	sTime.wDay >= 1 && sTime.wDay <= 5 )
						{
							if(	12 == sTime.wMonth )
							{
								validpower = 1;
							}
						}
					}
				}
				break;
			case ConstServiceArea_NHNChina:
				{
					// 2��, 8��, 14��, 20��
					if((2 == sTime.wHour || 8 == sTime.wHour || 14 == sTime.wHour || 20 == sTime.wHour))	
					{
						// 20�� ���� 30�ϱ���. �Ǵ� 1�� ���� 4�ϱ���
						if( sTime.wDay >= 20 && sTime.wDay <= 30 )
						{
							// 11��, 12��
							if( 11 == sTime.wMonth )
							{
								validpower = 1;
							}
						}
						if( sTime.wDay >= 1 && sTime.wDay <= 4 )
						{
							if( 12 == sTime.wMonth )
							{
								// �������� 20�ô� �������� �� �̺�Ʈ�� ������ ������ ����.
								if(12 == sTime.wMonth && 4 == sTime.wDay && 20 == sTime.wHour)
									break;

								validpower = 1;
							}
						}
					}
				}
				break;

			case ConstServiceArea_EUROPE:
				{
					// 2��, 8��, 14��, 20��
					if((2 == sTime.wHour || 8 == sTime.wHour || 14 == sTime.wHour || 20 == sTime.wHour))	
					{
						// 20�� ���� 30�ϱ���. �Ǵ� 1�� ���� 4�ϱ���
						if( sTime.wDay >= 20 && sTime.wDay <= 30 )
						{
							// 11��, 12��
							if( 11 == sTime.wMonth )
							{
								validpower = 1;
							}
						}
						if( sTime.wDay >= 1 && sTime.wDay <= 4 )
						{
							if( 12 == sTime.wMonth )
							{
								// �������� 20�ô� �������� �� �̺�Ʈ�� ������ ������ ����.
								if(12 == sTime.wMonth && 4 == sTime.wDay && 20 == sTime.wHour)
									break;

								validpower = 1;
							}
						}
					}
				}
				break;
			}
		}
	}
	// [���� �̺�Ʈ : 2008.01.10 �迵�� �߰� - ī��Ʈ������ �������� ������ 1]
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_KITERACCOON")) )
	{
		if( (pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_RaccoonTime"), &sTime) == true) )
		{
			validpower = 1;
		}
	}
	// [����] �߼� �̺�Ʈ. ��, �����䳢 ������ ���� 1��. => 2008-8-7
	else if (    pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_MOON"))
		|| pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_COSMOSRABBIT2")))
	{
		validpower = 1;
	}
	// [����] �׸� ���̳뺸���� ������ 1��
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_KOINOBORYGREEN")) )
	{
		validpower = 1;
	}
	// [����] ��� ���ʹ� ������ 1��
	else if ( pclCM->CR[attackid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BERSERKER")) )
	{
		validpower = 1;
	}


	//--------------------------------------
	// ���ĸ��� �̺�Ʈ : ���� �̺�Ʈ
	//--------------------------------------
	// ���ĸ��Ĵ� ���ȿ���� ������ �������� 10%�� ���ȴ�.
	if( IsPC( myid ) && pclCM->CR[attackid]->clIdentity.siIdentity == IDENTITY_MOFUMOFUEVENT )
	{
		// ��������� ������ �������� 10%�� �ȴ�.
		cltBufInfo * pclMyBuf = &pclCM->CR[ myid ]->pclCI->clBI.clBufInfo;

		BOOL bMofuMofuPerfume = FALSE;

		if( pclMyBuf->IsHaveBuf( BUF_MOFUMOFU_PERFUME ) )		
			bMofuMofuPerfume = TRUE;
		if( pclCM->CR[myid]->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE( 23090 ) )
			bMofuMofuPerfume = TRUE;

		if( bMofuMofuPerfume == FALSE )
		{
			validpower = max( 1, validpower - (validpower * 90 / 100) );
		}
	}

	//--------------------------------------
	// ����Ʈ�� ��Ƽ����
	//--------------------------------------
	if ( (pclCM->CR[myid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_GREATWALLASURA"))) && IsPC(attackid) )
	{
		// ��Ƽ���� ������ �ɷ��ִٸ� �Ƽ��󿡰� �޴� �������� 30% ���δ�
		cltBufInfo * pclAttackBuf = &pclCM->CR[ attackid ]->pclCI->clBI.clBufInfo;
		if ( (pclAttackBuf) && (pclAttackBuf->IsHaveBuf(BUF_QUEST_ANTIPOTION)) )
		{
			validpower = max( 1, validpower - (validpower * 30 / 100) );
		}
	}

	//[2007.12.13 �߰�] ��þƮ�� ���� ������ -(���̳ʽ�)������ ���� ����
	validpower = max(1,validpower);
	pclreturndamageinfo->Set(pcldamageinfo);
	pclreturndamageinfo->siDamage = validpower;
	return true;
}


// ������ ������ �������� ������.
// specialattackswitch : �ʻ��� �۵� ����.( 0 : �Ϲ� ����, 1 : ũ��Ƽ��, 2 : �߰�Ÿ (���ڹ���) )
BOOL cltServer::Hit(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo, UI08 specialattackswitch)
{
	//------------------------------------			
	// ���ݿ� ���� Ÿ��ġ�� ���Ѵ�. 
	//------------------------------------
	cltAttackDamageInfo cldamageinfo;

	SI32 realdamage = 0;
	SI32 displaydamage = 0;
	SI32 doubledamage = 0;

	if( GetDamage( pcldamageinfo, myid, enemyid, specialattackswitch, &cldamageinfo ) == true )
	{
		//---------------------------------------
		// �ǰ����� ü���� �ٿ��ش�.(�������� 0�� ���ü��� ����. �� �Ʒ� SpecialDamage�Լ� ������ Ư�� ��忡 ���� 0�� ���ü��� ����) [����]
		//---------------------------------------
		realdamage    = max( 1, cldamageinfo.siDamage );
		displaydamage = max( 1, cldamageinfo.siDamage );

		// PCK : �߰�Ÿ �������� �⺻�������� 80%~95% �������� ���Ѵ�.
		if(specialattackswitch == 2)
		{
			SI32	siRandValue = (rand() % 16) + 79;
			doubledamage = max( 1, cldamageinfo.siDamage * siRandValue / 100 );
		}			
	}

	cltCharServer* pclchartemp = (cltCharServer*)pclCM->CR[enemyid];

	//---------------------------------------
	// Ư���� ������ �� ����
	//---------------------------------------
	SpecialDamage(myid, enemyid, &realdamage, &displaydamage);

	//[����] ��Ʈ ȿ���� ���� ���ݷ� ���.
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		if ( pclCM->CR[myid] && IsPC( pclCM->CR[myid]->GetID() ) )
		{
			if( pclCM->CR[myid]->m_siSetItemType ) 
			{
				if( pcldamageinfo->siAttackType == ATTACKTYPE_MAGIC )
				{
					realdamage	  += realdamage    *  (	pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_1 ) 
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_5 )) / 100;

					displaydamage += displaydamage *  (	pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_1 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_5 )) / 100;

					doubledamage  += doubledamage  *  ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_1 ) 
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_5 )) / 100;
				}
				else
				{
					realdamage	  += realdamage    *  ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 ) 
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 )) / 100;

					displaydamage += displaydamage *  ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 )
												      + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 )) / 100;

					doubledamage  += doubledamage  *  ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 )
													  + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclCM->CR[myid], SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 )) / 100;

					// ���� Ȯ���� ��븦 �󸮱�.
					if( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK, USE_SETITEM_1 ) || 
						pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK, USE_SETITEM_2 )	||
						pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK, USE_SETITEM_3 ) ||
						pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK, USE_SETITEM_4 ) ||
						pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_ICE_MAGIC_TARGET_ATTACK, USE_SETITEM_5 ))
					{
						cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
						if(pcltempchar)
						{
							pcltempchar->SetIce(0);
						}	
					}
				}
				
				// [����] ���� Ȯ���� ��븦 �ߵ���Ű��.
				if( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK, USE_SETITEM_1 ) || 
					pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK, USE_SETITEM_2 ) ||
					pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK, USE_SETITEM_3 ) ||
					pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK, USE_SETITEM_4 ) ||
					pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[myid], SETITEM_ABILITY_TYPE_POISON_MAGIC_TARGET_ATTACK, USE_SETITEM_5 ))
				{
					cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
					if (pcltempchar)
					{
						if(		false == pcltempchar->clInnerStatus.IsStatus(INNERSTATUS_POISON) 
							&&	false == pcltempchar->clInnerStatus.IsStatus(INNERSTATUS_POISON_SETITEM_EFFECT) )
						{
							if(	DEVIL_MAN == pclCM->CR[myid]->m_siSetItemType  || DEVIL_WOMAN == pclCM->CR[myid]->m_siSetItemType  ||
								DEVIL_MAN == pclCM->CR[myid]->m_siSetItemType2 || DEVIL_WOMAN == pclCM->CR[myid]->m_siSetItemType2 ||
								DEVIL_MAN == pclCM->CR[myid]->m_siSetItemType3 || DEVIL_WOMAN == pclCM->CR[myid]->m_siSetItemType3 ||
								DEVIL_MAN == pclCM->CR[myid]->m_siSetItemType4 || DEVIL_WOMAN == pclCM->CR[myid]->m_siSetItemType4 ||
								DEVIL_MAN == pclCM->CR[myid]->m_siSetItemType5 || DEVIL_WOMAN == pclCM->CR[myid]->m_siSetItemType5	)
							{
								pcltempchar->SetPoisonSetItemEffect(myid, realdamage);
							}
							else
							{
								pcltempchar->SetPoison(myid, realdamage);
							}
						}
					}	
				}
			}
		}
	}

	// �ҷ��� ��Ʈ ���� ���� ������ 10% ����
	else if (  pclCM->CR[myid]->m_siSetItemType == HALLOWEEN1_SETITEM
			|| pclCM->CR[myid]->m_siSetItemType == HALLOWEEN2_SETITEM 
			|| pclCM->CR[myid]->m_siSetItemType == HALLOWEEN3_SETITEM
			|| pclCM->CR[myid]->m_siSetItemType == HALLOWEEN4_SETITEM ) 
	{
		if( pcldamageinfo->siAttackType == ATTACKTYPE_MAGIC || 
			pcldamageinfo->siAttackType == ATTACKTYPE_POISON )
		{
			realdamage		= (realdamage * 110 )/100	; // ���� ������ 10% ���� 
			displaydamage	= (displaydamage * 110)/100	; // ���� ������ 10% ���� 
			doubledamage	= (doubledamage * 110)/100	; // ���� ������ 10% ����
		}
	}
	//----------------------------------------------------------------------------------
	if(IsCountrySwitch(Switch_SoulGuard))
	{
		// �ش� �������� ���� ������ �϶�
		if(pcldamageinfo->siMagicKind > 0 )
		{
			// ������ ���� ���
			cltCharServer* pclMyChar = pclCM->GetCharServer(myid);
			if ( NULL != pclMyChar )
			{
				// ��ȣ���� ��Ų�϶� ������ ����
				if ( (pclMyChar->IsSoulGuardStatusOut()) && (pclMyChar->pclSoulGuard->GetKind()==pclClient->GetUniqueFromHash(TEXT("KIND_SOULGUARD_PUMPKIN"))) )
				{
					realdamage		= (realdamage * 110 )/100	; // ���� ������ 10% ���� 
					displaydamage	= (displaydamage * 110)/100	; // ���� ������ 10% ���� 
					doubledamage	= (doubledamage * 110)/100	; // ���� ������ 10% ����
				}
			}

			// ������ �޾��� ���
			cltCharServer* pclCharServer = pclCM->GetCharServer( enemyid)	;
			if ( pclCharServer != NULL )
			{
				SI32 sivalue = pclCharServer->SoulGuardAbilityActivity(SOULGUARD_ABILITY_MAGIC_DEFENSE )	; // ��Ų ������ 
				if(sivalue > 0 )
				{
					realdamage		=	realdamage - (realdamage * sivalue / 100 )	;
					displaydamage	=	displaydamage - (displaydamage * sivalue / 100 )	;
					doubledamage	=	doubledamage - (doubledamage * sivalue / 100 )	;
				}
			}
		}
	}
	
	// [����] ��Ʋ�ξ� ����� �Ŀ� �� ��� �� ���
	cltCharServer* pclChar = pclCM->GetCharServer(myid);
	if( NULL != pclChar )
	{
		if(pclChar->bBattleRoyalPowerupMode == true)
		{
			realdamage = realdamage * 2;
			displaydamage = displaydamage * 2;
		}
	}

	//----------------------------------------------------------------------------------
	if(specialattackswitch == 2)
	{
		SI32 life = pclchartemp->DecreaseLife(realdamage + doubledamage);
	}
	else
	{
		SI32 life = pclchartemp->DecreaseLife(realdamage);
	}

	//------------------------------------------------
	// Ÿ���� �ǰݵǸ� ó���ؾ��� ���� ĳ������ �Լ�. 
	//-----------------------------------------------
	pclchartemp->BeHitOperate(myid);


	if( pclCM->IsAlive( enemyid ) == false )
	{
		// ���������� ����� �ð��� ������Ʈ �Ѵ�. 
		if(pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			SI16 parentid = pclCM->GetIDFromCharUnique(pclCM->CR[myid]->clIdentity.clSummonInfo.siParentCharUnique);
			if(parentid)
			{
				((cltCharServer*)pclCM->CR[parentid])->SetLastKillClock(CurrentClock);				// ĳ���͸� ���� ���� �ֱ� �ð��� ������Ʈ �Ѵ�. 
			}
		}
		else
		{
			((cltCharServer*)pclCM->CR[myid])->SetLastKillClock(CurrentClock);				// ĳ���͸� ���� ���� �ֱ� �ð��� ������Ʈ �Ѵ�. 
		}

		// ��ھ����� ������� ����ġ
		bool bBigItemGet = false;

		if( IsPC(pclCM->CR[enemyid]->GetCharUnique()) )
		{
			DeadChar_PC(myid, enemyid);
		}
		else 
		{
			DeadChar_NPC(myid, enemyid);

			// �̺�Ʈ ��� ������
			bBigItemGet = GiveBigItem_Event(myid, enemyid);

			// �̺�Ʈ ��� �������� ���� ���Ѱ�쿡�� ��ھ������� ����Ѵ�.
			if( bBigItemGet == false )
			{
				if(pclClient->IsCountrySwitch(Switch_BigItemModify))
				{
					bBigItemGet = GiveBigItem_New(myid, enemyid);
				}
				else
				{
					bBigItemGet = GiveBigItem(myid, enemyid);
				}
			}

			GiveSpecialItem(myid, enemyid);
		}

		//-----------------------------
		// �׾��ٸ� ����ǰ�� ì���. 
		//-----------------------------

		// ��ھ����� ���������� �Ϲ� ������ �ȸԵ���
		if (bBigItemGet == false)
		{
			//��Ƽȹ�渷��

			// ���� ��ȯ����� �θ��� ���̵� ���ؼ� ��Ƽ������ Ȯ���Ѵ�.
			SI32 parentID = pclCM->CR[myid]->GetSummonParentID();
			if( pclCM->IsValidID(parentID) == TRUE )
			{
				if( pclCM->CR[parentID]->siPartyIndex > 0 )	// ��Ƽ�� �������̶�� ��Ƽ ������ �й� �Լ� ȣ��
				{			
					CPartyObj* pclparty = pclPartyMgr->GetPartyObj(pclCM->CR[parentID]->siPartyIndex);
					// ��Ƽ�� �ְ� ������ �й� ����� �ַ� �÷��� �� �ٸ� ����̶��
					if(pclparty != NULL && pclparty->GetItemGetPattern() != ITEM_GETPATTERN_NORMAL )
					{
						PartyWarItemOperate(parentID, enemyid, pclparty);				
					}
					else
						WarItemOperate(myid, enemyid);
				}
				else
					WarItemOperate(myid, enemyid);

			}
			else // �÷��̾��� 
			{
				if( pclCM->CR[myid]->siPartyIndex > 0 )	// ��Ƽ�� �������̶�� ��Ƽ ������ �й� �Լ� ȣ��
				{			
					CPartyObj* pclparty = pclPartyMgr->GetPartyObj(pclCM->CR[myid]->siPartyIndex);
					// ��Ƽ�� �ְ� ������ �й� ����� �ַ� �÷��� �� �ٸ� ����̶��
					if(pclparty != NULL && pclparty->GetItemGetPattern() != ITEM_GETPATTERN_NORMAL )
					{
						PartyWarItemOperate(myid, enemyid, pclparty);				
					}
					else
						WarItemOperate(myid, enemyid);
				}
				else
					WarItemOperate(myid, enemyid);
			}

		}

		// ������������ �׾��� ���� �����
		if ( IsNPC(myid) && IsPC(enemyid) )
		{
			if ( pclCM->CR[myid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER") ) )
			{
				pclLog->FilePrint("Config\\DeathfromJoker.txt", "User : [%s]",
					pclCM->CR[enemyid]->pclCI->clBI.GetName());
			}
		}

		//--------------------------------------------
		// ��ũ��
		//-----------------------------------------
		if ( IsPC(myid) )
		{
			((cltCharServer*)pclCM->CR[myid])->AddKillMonsterNum(1);
		}
		else if ( IsNPC(myid) )
		{
			SI32 siParentID = pclCM->CR[myid]->GetSummonParentID();
			if ( pclCM->IsValidID(siParentID) )
			{
				((cltCharServer*)pclCM->CR[siParentID])->AddKillMonsterNum(1);
			}
		}

		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];

		if( IsPC(pcltempchar->GetCharUnique()) )
		{
			if ( pcltempchar->GetLife() > 0 )
			{
				SI32 siDrainRate = 0;

				if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
				{
					if( pcltempchar->m_siSetItemType )
					{
						cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
						if( pcltSetItemAbilityManager ) 
						{
							if(pcltempchar->m_siSetItemType)
							{
								siDrainRate = pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_1 );
								siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_2 );
								siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_3 );
								siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_4 );
								siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_5 );
								/*
								SI32 siValue = 0;
								siValue = pcltSetItemAbilityManager->GetSetItemAbilityValue(pcltempchar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_1 );

								pcltempchar->SetDrain(pcldamageinfo->siDamage, siValue, 0);
								*/
							}
						}
					}
				}
				else
				{
					// �����̾� ��Ʈ ����� 20%���� ����� �����������
					if ( pcltempchar->m_siSetItemType == VAMPIRE_SETITEM )
					{
						siDrainRate = 20;
					}
					else if ( pcltempchar->m_siSetItemType == HALLOWEEN1_SETITEM 
						||pcltempchar->m_siSetItemType == HALLOWEEN2_SETITEM
						||pcltempchar->m_siSetItemType == HALLOWEEN3_SETITEM
						||pcltempchar->m_siSetItemType == HALLOWEEN4_SETITEM)	// ȣ�� ��Ʈ �ϰ��� 10% ����
					{
						siDrainRate = 10;
					}
				}

				// ���������� ���� ����
				if ( (PERSONITEM_WEAPON1 == pcltempchar->ActiveWeapon) || (PERSONITEM_WEAPON2 == pcltempchar->ActiveWeapon) )
				{
					SI32 siSkillUnique		= 0;
					SI32 siItemType			= pclClient->pclItemManager->GetItemType( pcltempchar->pclCI->clCharItem.clItem[pcltempchar->ActiveWeapon].siUnique );
					switch ( siItemType )
					{
					case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_BOW_DRAIN;	}	break;
					case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_BOW_DRAIN;	}	break;
					case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_BOW_DRAIN;	}	break;
					case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_DRAIN;		}	break;
					case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_BOW_DRAIN;	}	break;
					case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_BOW_DRAIN;	}	break;
					}

					if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
					{
						SI32 siSkillLevel		= pcltempchar->pclCI->clCharSkill.GetTotalSkillLevel( siSkillUnique, 0, 0 );
						SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
						if ( 0 < siWeaponSkillRate )
						{
							SI32 siRandValue = (rand() % 100) + 1;

							pclLog->LogPrint( TEXT("[WeaponSkill-Drain/Death] Rate:%d/RandValue:%d\n"), siWeaponSkillRate, siRandValue );

							if ( siWeaponSkillRate >= siRandValue )
							{
								siDrainRate = 30;
							}
						}
					}
				}

				if ( 0 < siDrainRate )
				{
					pcltempchar->SetDrain( pcldamageinfo->siDamage, siDrainRate, 0 );
				}
			} 
		}
	}
	else
	{
		// ���� ���� 
		// ���⿡���� ���ݽ� �ش� ���⿡ ���������� ������ Ư���ɷ¿� ���� ������ �����Ѵ�.

		cltAttackDamageInfo clinfo;
		clinfo.Set(&cldamageinfo);
		clinfo.siDamage = realdamage;
		AddScrollMagicOperate(myid, enemyid, &clinfo);

		// ���� ���� 
		ChangeStatusMagicOperate(myid, enemyid, &clinfo);

	}

	//=======================================================
	// ĳ���Ͱ� �װų� ��ų� �ش� ������ ����ȴ�.
	//=======================================================
	cltAttackDamageInfo clinfo;
	clinfo.Set(&cldamageinfo);
	if(specialattackswitch == 2)
	{
		clinfo.siDamage = displaydamage + doubledamage;
	}
	else
	{
		clinfo.siDamage = displaydamage;
	}

	PassiveMagicOperate(myid, enemyid, &clinfo);


	//=======================================================
	// ĳ������ ���¸� �����ϰ� �����Ѵ�.
	//=======================================================
	// �ǰ� ���·� ��ȯ�Ѵ�. 
	bool			bIndure = true;
	cltCharServer*	pclchar	= NULL;

	if ( IsPC(enemyid) )
	{
		pclchar = pclCM->GetCharServer(enemyid);
	}

	// ���������� ���� �ǰݸ�� ��/��
	if ( (pclchar) && ( (PERSONITEM_WEAPON1 == pclchar->ActiveWeapon) || (PERSONITEM_WEAPON2 == pclchar->ActiveWeapon) ) )
	{
		SI32 siSkillUnique	= 0;
		SI32 siItemType		= pclchar->pclCI->clCharItem.GetWeaponType( pclItemManager, pclchar->ActiveWeapon );
		switch ( siItemType )
		{
		case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_AXE_INDURE;	}	break;
		case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_AXE_INDURE;	}	break;
		case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_INDURE;		}	break;
		case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_AXE_INDURE;	}	break;
		case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_AXE_INDURE;	}	break;
		case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_AXE_INDURE;	}	break;
		}

		bool bHideHitMotion = false;

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclchar->pclCI->clCharSkill.GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				SI32 siRandValue = (rand() % 100) + 1;

				pclLog->LogPrint( TEXT("[WeaponSkill-INDURE] Rate:%d/RandValue:%d\n"), siWeaponSkillRate, siRandValue );

				if ( siWeaponSkillRate >= siRandValue )
				{
					bHideHitMotion = true;
				}
			}
		}

		if ( bHideHitMotion )
		{
			pclchar->SetHitSwitch( false );
			bIndure = false ;
		}
		else
		{
			pclchar->SetHitSwitch( true );
		}
	}
	else
	{
		pclCM->CR[enemyid]->SetHitSwitch(true);
	}

	SI32 siHitMode = 0 ;
	SI32 siSkillLevel = 0 ;
	if ( IsPC(myid) && IsPC(enemyid) == false )
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[myid];

		switch( pclchar->GetAttackType() )
		{
		case ATTACKTYPE_STAFF:
		case ATTACKTYPE_STAFF1:
		case ATTACKTYPE_STAFF2:
		case ATTACKTYPE_NEW_STAFF2:
			{
				siHitMode = 1 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESTAFF1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 6 ;
			}
			break;
		case ATTACKTYPE_SWORD:
			{
				siHitMode = 2 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESWORD1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 7 ;
			}
			break;
		case ATTACKTYPE_SPEAR:
			{
				siHitMode = 3 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESPEAR1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 8 ;
			}
			break;
		case ATTACKTYPE_AXE:
			{
				siHitMode = 4 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEAXE1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 9 ;
			}
			break;
		case ATTACKTYPE_BOW:
		case ATTACKTYPE_BOW1:
		case ATTACKTYPE_NEW_BOW1:
			{
				siHitMode = 5 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEBOW1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 10 ;
			}
			break;
		case ATTACKTYPE_GUN:
		case ATTACKTYPE_GUN1:
		case ATTACKTYPE_NEW_GUN1:
			{
				siHitMode = 5 ;
				siSkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEGUN1,0,0,&pclchar->pclCI->clCharItem.clItem[0]) ;

				if ( siSkillLevel > 60 ) siHitMode = 10 ;
			}
			break;
		default:
			{
				siHitMode = 0 ;
			}
			break;
		}

		if ( siSkillLevel < 30 ) siHitMode = 0 ;
	}

	UI08 type = 0;
	if( true == pclCM->CR[enemyid]->pclKI->IsAtb( ATB_MONSTER ) )
	{
		type = 0;
	}
	else
	{
		type = 1;
	}
	//------------------------------
	// �̿����� �¾����� �뺸�Ѵ�. 
	//------------------------------
	if(specialattackswitch == 2)
	{
		cltGameMsgResponse_Hit clHitInfo(pclCM->CR[enemyid]->GetCharUnique(), displaydamage, doubledamage,
			pclCM->CR[enemyid]->GetLife(), siHitMode, specialattackswitch, bIndure, false, false, type );
		cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
		((cltCharServer*)pclCM->CR[enemyid])->SendNeighbourMsg(&clMsg, true);
	}
	else
	{
		cltGameMsgResponse_Hit clHitInfo(pclCM->CR[enemyid]->GetCharUnique(), displaydamage, 0,
			pclCM->CR[enemyid]->GetLife(), siHitMode, specialattackswitch, bIndure, false, false, type );
		cltMsg clMsg(GAMEMSG_RESPONSE_HIT, sizeof(clHitInfo), (BYTE*)&clHitInfo);
		((cltCharServer*)pclCM->CR[enemyid])->SendNeighbourMsg(&clMsg, true);
	}

	//==========================================
	// ������ ���� �ִ� ��ȯ���� ������ �����ϰ� �뺸 �Ѵ�.
	//==========================================
	SI32 siParentID = pclCM->CR[enemyid]->GetSummonParentID();
	if(siParentID)
	{

		//==========================================
		// 
		//==========================================
		cltSummon *pclSummon = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSummon(pclCM->CR[enemyid]->GetSummonIndex());
		if(pclSummon)
		{
			pclSummon->clIP.Set(&pclCM->CR[enemyid]->pclCI->clIP);
			cltGameMsgResponse_Summon clInfo(pclCM->CR[siParentID]->GetCharUnique(), pclCM->CR[enemyid]->GetSummonIndex(), pclSummon);
			cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
			pclCM->CR[siParentID]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	if ( IsCountrySwitch(Switch_NewDurability) )
	{
		if( pclCM->IsAlive(myid) )
		{
			cltCharServer* pclmychar	= pclCM->GetCharServer( myid );
			cltCharServer* pclenemychar = pclCM->GetCharServer( enemyid );

			bool bDecreaseDur = false;		// �������� ���� ���Ѿ� �ϴ°�?

			// ���� ĳ���Ͱ� ������ ��쿡�� �������� �����ȴ�.
			if( pclenemychar &&
				IsNPC(pclenemychar->GetCharUnique()) &&
				pclenemychar->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )
			{
				bDecreaseDur = true;
			}

			if( bDecreaseDur )
			{
				// �������� ���� �������� �����. 
				if( pclmychar )		pclmychar->DecreaseWeaponDur( enemyid );
			}
		}
	}

	//--------------------------------------------------
	// ��ȣ���ɿ� ���� Ư�� �ɷ� �ߵ�
	//--------------------------------------------------
	if ( IsCountrySwitch(Switch_SoulGuard) )
	{
		cltCharServer* pclMyChar = pclCM->GetCharServer( myid );

		// ĳ���� �϶�(��� �������� �۵��Ѵ�)
		if ( IsPC(myid) && (pclMyChar) && (pclCM->IsAlive(myid)) )
		{
			// �� ���� HP��ġ�� �ƽ�ġ ���� �������� �ߵ��ȴ�
			if ( pclMyChar->clPB.GetMaxLife() > pclMyChar->pclCI->clIP.GetLife() )
			{
				SI32 siAddHP = pclMyChar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_RECOVER_HP );
				if ( 0 < siAddHP )
				{
					pclMyChar->IncreaseLife( siAddHP );

					cltGameMsgResponse_IncLife clInfo( pclMyChar->GetCharUnique(), pclMyChar->pclCI->clIP.GetLife(), siAddHP, pclMyChar->clPB.siReservedLife, 0, INCLIFE_REASON_SOULGUARD );
					cltMsg clMsg( GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo );
					pclMyChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			// �� ���� MP��ġ�� �ƽ�ġ ���� �������� �ߵ��ȴ�
			if ( pclMyChar->clPB.GetMaxMana() > pclMyChar->pclCI->clIP.GetMana() )
			{
				SI32 siAddMana = pclMyChar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_RECOVER_MP );
				if ( 0 < siAddMana )
				{
					pclMyChar->IncreaseMana( siAddMana );

					cltGameMsgResponse_IncMana clInfo( pclMyChar->GetCharUnique(), pclMyChar->pclCI->clIP.GetMana(),  siAddMana, INCMANA_REASON_SOULGUARD );
					cltMsg clMsg( GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo );
					pclMyChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			// �������� -�϶��� �÷��ش�
			if ( 0 > pclMyChar->clPB.clHealth.pclInfo->siHungry )
			{
				SI32 siAddHungry = pclMyChar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_HUNGRY_UP );
				if ( 0 < siAddHungry )
				{
					pclMyChar->clPB.clHealth.IncreaseHungry( siAddHungry );

					cltGameMsgResponse_IncHungry clInfo( 0, pclMyChar->clPB.clHealth.pclInfo->siHungry );
					cltMsg clMsg(GAMEMSG_REPONSE_INCHUNGRY, sizeof(clInfo), (BYTE*)&clInfo);
					pclMyChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

		}	// if ( IsPC(myid) && (pclMyChar) && (pclCM->IsAlive(myid)) )����

		// ��ȯ�� �϶�
		if ( IsNPC(myid) && (pclMyChar) && (IDENTITY_PERSON_SUMMON == pclMyChar->clIdentity.siIdentity) && (pclCM->IsAlive(myid)) )
		{
			SI32			siParentCharID	= pclMyChar->GetSummonParentID();
			cltCharServer*	pclParentChar	= pclCM->GetCharServer( siParentCharID );

			// �� ���� HP��ġ�� �ƽ�ġ ���� �������� �ߵ��ȴ�
			if ( (pclParentChar) && (pclMyChar->clPB.GetMaxLife() > pclMyChar->pclCI->clIP.GetLife()) )
			{
				SI32 siAddSummonHP = pclParentChar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_SUMMONRECOVERY_HP );
				if ( 0 < siAddSummonHP )
				{
					pclMyChar->IncreaseLife( siAddSummonHP );

					cltGameMsgResponse_IncLife clInfo( pclMyChar->GetCharUnique(), pclMyChar->pclCI->clIP.GetLife(), siAddSummonHP, pclMyChar->clPB.siReservedLife, 0, INCLIFE_REASON_SOULGUARD );
					cltMsg clMsg( GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo );
					pclMyChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			// �� ���� MP��ġ�� �ƽ�ġ ���� �������� �ߵ��ȴ�
			if ( (pclParentChar) && (pclMyChar->clPB.GetMaxMana() > pclMyChar->pclCI->clIP.GetMana()) )
			{
				SI32 siAddSummonMana = pclMyChar->SoulGuardAbilityActivity( SOULGUARD_ABILITY_SOMMONRECOVERY_MP );
				if ( 0 < siAddSummonMana )
				{
					pclMyChar->IncreaseMana( siAddSummonMana );

					cltGameMsgResponse_IncMana clInfo( pclMyChar->GetCharUnique(), pclMyChar->pclCI->clIP.GetMana(),  siAddSummonMana, INCMANA_REASON_SOULGUARD );
					cltMsg clMsg( GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo );
					pclMyChar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

	}	// if ( IsCountrySwitch(Switch_SoulGuard) )

	// ȹ���� ����ġ�� ���Ѵ�. (myid�� enemyid�� �������� ���� ����ġ) 
	{

		cltAttackDamageInfo clinfo;
		clinfo.Set(&cldamageinfo);
		clinfo.siDamage = realdamage;
		SI32 exp = ExpOperate(myid, enemyid, &clinfo);
	}

	return TRUE;			
}


//===============================================
// �������� Ÿ�ݽ� �ΰ� �ɷ��� �����Ų��.
//===============================================
BOOL cltServer::AddScrollMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo)
{
	/*
	if(pcldamageinfo->siAttackType != ATTACKTYPE_SWORD
		&& pcldamageinfo->siAttackType != ATTACKTYPE_SPEAR
		&& pcldamageinfo->siAttackType != ATTACKTYPE_AXE
		&& pcldamageinfo->siAttackType != ATTACKTYPE_GUN
		&& pcldamageinfo->siAttackType != ATTACKTYPE_BOW
		&& pcldamageinfo->siAttackType != ATTACKTYPE_STAFF
		&& pcldamageinfo->siAttackType != ATTACKTYPE_STAFF1)	return FALSE;
	*/

		//===============================================
		// ����� ��ȯ���� ó���� �Ѵ�.
		//===============================================
		if(!IsPC(pclCM->CR[myid]->GetCharUnique()) && pclCM->CR[myid]->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)
			return FALSE;

	// ���� �� �ڽ�
	cltCharServer* pclMyChar = pclCM->GetCharServer( myid );
	if ( NULL == pclMyChar )
	{
		return FALSE;
	}

	// ��
	cltCharServer* pclEnemyChar = pclCM->GetCharServer( enemyid );
	if ( NULL == pclEnemyChar )
	{
		return FALSE;
	}

	// ��ȯ���϶� �θ� ĳ���� NULL�� ���� �� ����
	cltCharServer*		pclParentChar	= NULL; 
	if ( 0 < pclMyChar->GetSummonParentID() )
	{
		pclParentChar = pclCM->GetCharServer( pclMyChar->GetSummonParentID() );
	}

	SI32				siSummonIndex	= -1;
	cltSummon*			pclSummon		= NULL;
	cltSummonScroll*	pclSummonScroll	= NULL;

	// ��ȯ�� ���� ������ �θ�ĳ���Ͱ� �־�� ������(����ϱ��� NULL äũ �ݵ�� �Ұ�)
	if ( pclParentChar )
	{
		siSummonIndex	= pclMyChar->GetSummonIndex();

		pclSummon		= pclParentChar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
		if ( pclSummon )
		{
			pclSummonScroll = &pclSummon->clScroll;
		}
	}


	bool already = false;

	//=======================================================
	// POISON
	//=======================================================
	if(already == false)
	{
		SI32 rate = 0;
		//=======================================================
		// ��ȯ����� ��ȯ���� �����ɷ��� ���´�.
		//=======================================================
		if ( pclParentChar )	
		{
			SI32 siActive = pclMyChar->ActiveWeapon;

			if ( pclSummonScroll)
			{
				rate += pclSummonScroll->GetScrollPoisonRate(pclItemManager);
			}

			rate += pclParentChar->pclCI->clSummonInfo.GetSummonEquipPoisonRate( siSummonIndex, pclItemManager, siActive );

			rate = min(300,rate) ;
		}
		//=======================================================
		if (IsPC( pclMyChar->GetCharUnique()) )
		{
			rate += pclMyChar->pclCI->clCharItem.GetEquipPoisonRate( pclItemManager, pclMyChar->ActiveWeapon );
		}

		if ( rate && (rand() % 1000  <= rate) )
		{
			pclEnemyChar->SetPoison( myid, pcldamageinfo->siDamage );
			already = true;
		}
	}

	// ������ ���� �����ɼ� �ֵ��� �Ѵ�.
	already = false;
	//=======================================================
	// ICE
	//=======================================================
	if(already == false)
	{
		SI32 rate = 0;
		//=======================================================
		// ��ȯ����� ��ȯ���� �����ɷ��� ���´�.
		//=======================================================
		if ( pclParentChar )	
		{
			SI32 siActive = pclMyChar->ActiveWeapon;

			if ( pclSummonScroll)
			{
				rate += pclSummonScroll->GetScrollIceRate( pclItemManager );
			}

			rate += pclParentChar->pclCI->clSummonInfo.GetSummonEquipIceRate( siSummonIndex, pclItemManager, siActive );

			rate = min(300,rate) ;
		}
		//=======================================================
		if (IsPC( pclMyChar->GetCharUnique()) )
		{
			rate += pclMyChar->pclCI->clCharItem.GetEquipIceRate( pclItemManager, pclMyChar->ActiveWeapon );
		}

		if ( (true == pclMapManager->IsInstanceMap(pclMyChar->GetMapIndex())) || (true == pclEnemyChar->pclKI->IsAtb(ATB_NOICE)) )
		{
			rate /= 20 ;
		}

		if ( rate && (rand() % 1000  <= rate) )
		{
			pclEnemyChar->SetIce( pcldamageinfo->siDamage );
			already = true;
		}
	}
	// ������ ���� �����ɼ� �ֵ��� �Ѵ�.
	already = false;

	//=======================================================
	// DRAIN
	//=======================================================
	if(already == false)
	{
		SI32 rate = 0;
		//=======================================================
		// ��ȯ����� ��ȯ���� �����ɷ��� ���´�.
		//=======================================================
		if ( pclParentChar )	
		{
			SI32 siActive = PERSONITEM_SHOES;

			if ( pclSummonScroll)
			{
				rate += pclSummonScroll->GetScrollDrainRate( pclItemManager );
			}

			rate += pclParentChar->pclCI->clSummonInfo.GetSummonEquipDrainRate( siSummonIndex, pclItemManager, siActive );

			rate = min(300,rate) ;
		}
		//=======================================================
		if (IsPC( pclMyChar->GetCharUnique()) )
		{
			rate += pclMyChar->pclCI->clCharItem.GetEquipDrainRate( pclItemManager, pclMyChar->ActiveWeapon );
		}

		if(rate && (rand() % 1000  <= rate))
		{
			if ( 0 < pclMyChar->GetLife() )
			{
				if ( pclMyChar->SetDrain(pcldamageinfo->siDamage, 20, 0) && pclParentChar )
				{
					pclParentChar->SetUpdateSwitch( UPDATE_SUMMON, true, 0 );
				}

				already = true;
			}
		}
	}

	//=======================================================
	// ��Ʈ ���ʿ� ���� ���� 20%
	//=======================================================
	already = false;
	if ( already == false )
	{
		if ( (0 < pclMyChar->GetLife()) )
		{
			SI32 siDrainRate = 0;

			if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				if( pclMyChar->m_siSetItemType )
				{
					cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
					if( pcltSetItemAbilityManager ) 
					{
						siDrainRate = pcltSetItemAbilityManager->GetSetItemAbilityValue(pclMyChar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_1 );
						siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclMyChar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_2 );
						siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclMyChar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_3 );
						siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclMyChar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_4 );
						siDrainRate += pcltSetItemAbilityManager->GetSetItemAbilityValue(pclMyChar, SETITEM_ABILITY_TYPE_DRAIN, USE_SETITEM_5 );

						already = true;
					}
				}

				//if(	(HALLOWEEN1_SETITEM == pclMyChar->m_siSetItemType)	||
				//	(HALLOWEEN2_SETITEM == pclMyChar->m_siSetItemType)	|| 
				//	(HALLOWEEN3_SETITEM == pclMyChar->m_siSetItemType)	|| 
				//	(HALLOWEEN4_SETITEM == pclMyChar->m_siSetItemType)	)
				//{
				//	siDrainRate = 10;

				//	already = true;
				//}
			}
			else
			{
				if( VAMPIRE_SETITEM == pclMyChar->m_siSetItemType )
				{
					siDrainRate = 20;

					already = true;
				}
				else if(   (HALLOWEEN1_SETITEM == pclMyChar->m_siSetItemType) 
					|| (HALLOWEEN2_SETITEM == pclMyChar->m_siSetItemType)
					|| (HALLOWEEN3_SETITEM == pclMyChar->m_siSetItemType)
					|| (HALLOWEEN4_SETITEM == pclMyChar->m_siSetItemType)	)
				{
					siDrainRate = 10;

					already = true;
				}
			}

			// ���������� ���� ����
			if ( (PERSONITEM_WEAPON1 == pclMyChar->ActiveWeapon) || (PERSONITEM_WEAPON2 == pclMyChar->ActiveWeapon) )
			{
				SI32 siSkillUnique		= 0;
				SI32 siItemType			= pclClient->pclItemManager->GetItemType( pclMyChar->pclCI->clCharItem.clItem[pclMyChar->ActiveWeapon].siUnique );
				switch ( siItemType )
				{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_BOW_DRAIN;	}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_BOW_DRAIN;	}	break;
				case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_BOW_DRAIN;	}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_DRAIN;		}	break;
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_BOW_DRAIN;	}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_BOW_DRAIN;	}	break;
				}

				if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
				{
					SI32 siSkillLevel		= pclMyChar->pclCI->clCharSkill.GetTotalSkillLevel( siSkillUnique, 0, 0 );
					SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
					if ( 0 < siWeaponSkillRate )
					{
						SI32 siRandValue = (rand() % 100) + 1;

						pclLog->LogPrint( TEXT("[WeaponSkill-Drain] Rate:%d/RandValue:%d\n"), siWeaponSkillRate, siRandValue );

						if ( siWeaponSkillRate >= siRandValue )
						{
							siDrainRate = 30;

							already = true;
						}
					}
				}
			}

			if ( 0 < siDrainRate )
			{
				pclMyChar->SetDrain( pcldamageinfo->siDamage, siDrainRate, 0 );
			}

		}
	}

	return TRUE;
}

//===============================================
// ĳ������ STATUS�� �����ϴ� MAGIC OPERATE 
// ���¸� �����ϹǷ� ����������� ���� �Ѵ�.
//===============================================
BOOL cltServer::ChangeStatusMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo)
{
	if( pclCM->IsValidID(myid) == false )		return FALSE;
	if( pclCM->IsValidID(enemyid) == false )	return FALSE;

	// ���� Magic�� �����ϰ� �ְ� Passive magic �̶�� 
	SI32 magickind = pcldamageinfo->siMagicKind;
	if(magickind < MAGIC_INDEX_START || magickind  > MAGIC_INDEX_LAST)	magickind = 0;

	// ���߷��� �ٰŷ� Ÿ�� ���θ� �����Ѵ�.
	SI32 hitrate = 0;	
	// pvp-

	// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
	//if( IsWhereServiceArea(ConstSwitch_PVP) )
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		hitrate = pclCM->CR[myid]->clPB.GetHitRate( pclCM->CR[enemyid], pclCM->CR[myid], true );	

	}
	else
	{
		if(siEnablePVP == 1)
			hitrate = pclCM->CR[myid]->clPB.GetHitRate( pclCM->CR[enemyid], pclCM->CR[myid], true );	
		else
			hitrate = pclCM->CR[myid]->clPB.GetHitRate( pclCM->CR[enemyid], pclCM->CR[myid] );		
	}

	if ( pclMapManager->IsInstanceMap(pclCM->CR[myid]->GetMapIndex()) == true ||
		pclCM->CR[enemyid]->pclKI->IsAtb(ATB_NOICE) == true
		)
		hitrate /= 20 ;

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		if(rand() % 10000 > hitrate) return FALSE;
	}
	else
	{
		if(rand() % 100 > hitrate) return FALSE;
	}
	//=====================================================================

	//=====================================================================
	SI32 PassiveDamage = 0, PassiveMana = 0;
	if(magickind)	// �ش� Magic���κ��� Damage�� mana�� ���´�.
	{
		CMagicAttribute *pMagicAttributePtr = pclMagicManager->GetMagicAttributePtr();

		SI32 kind = 0, min  = 0, max = 0;
		// �ش� Magic �� ����� ����� ���´�.
		if(IsNPC(pclCM->CR[myid]->GetCharUnique())||IsInstanceNPC(pclCM->CR[myid]->GetCharUnique()))	kind =pclCM->CR[myid]->GetKind();

		// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
		SI32 SkillType = pMagicAttributePtr->GetMagicSkillType(magickind);
		if( SKILL_SIKLLBOOK == SkillType && IsPC(myid) )
		{
			cltSkillBookMagic*	pclSkillBookMagic = pclCM->CR[myid]->pclCharSkillBookInfo->GetSkillBookMagic( pclCM->CR[myid]->GetAttackType() );	
			if( NULL == pclSkillBookMagic ) return 0;

			SkillType = pclSkillBookMagic->GetSkillUnique();
		}

		SI32 SkillLevel = pclCM->CR[myid]->pclCI->clCharSkill.GetTotalSkillLevel(SkillType, kind, pclCM->CR[myid]->pclCI->clIP.GetLevel(), &pclCM->CR[myid]->pclCI->clCharItem.clItem[0]);

		// �������� ���¿� ���� �߰� Damage�� �ΰ��Ѵ�.
		stMagicAttributeData *pMagicAttributeData = pMagicAttributePtr->GetMagicAttribute(magickind);
		SI32 siOrganUnique = pclCM->CR[myid]->pclCI->clHealthInfo.GetOrg(pMagicAttributeData->si16MagicOrganKind);

		stMagicInfo clMagicInfo(magickind, myid, enemyid, 0);
		// �ش� ����� �̿��Ͽ�  min, max, mana �� ����Ѵ�.
		pclMagicManager->GetMinMaxDamage( &clMagicInfo, pclCM->CR[myid]->clPB.GetAddMagicDamage(),  SkillLevel, min, max, siOrganUnique );
		pclMagicManager->CalculateDamage(min, max , PassiveDamage);
		PassiveMana = pclMagicManager->GetSpendMana(magickind, SkillLevel,myid);
	}
	//=====================================================================

	// �ߵ� �Ӽ��� ������ Ȯ�� 
	if(pcldamageinfo->siAttackType == ATTACKTYPE_POISON)
	{
		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];

		DWORD dwPoisonTime = 20000;
		if( pclClient->IsCountrySwitch(Switch_SkillBook) )
		{
			if( pclCM->CR[myid]->pclCharSkillBookInfo )
			{
				SI32 siSubMagickind = 0;
				stMagicAttributeData* psSubMagicData = pclCM->CR[myid]->pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( magickind, siSubMagickind );
				if( psSubMagicData )
				{
					dwPoisonTime += (dwPoisonTime * psSubMagicData->si32MagicMaxActionFrame) / 100;
				}
			}
		}

		pcltempchar->SetPoison( myid, pcldamageinfo->siDamage, dwPoisonTime );
	}
	// ���� �Ӽ��� ������ 
	if(pcldamageinfo->siAttackType == ATTACKTYPE_ICE)
	{
		SI32 siIceMagicAct = 0;
		if( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if( pclCM->CR[enemyid]->m_siSetItemType )
			{
				siIceMagicAct += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[enemyid], SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK, USE_SETITEM_1 );
				siIceMagicAct += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[enemyid], SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK, USE_SETITEM_2 );
				siIceMagicAct += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[enemyid], SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK, USE_SETITEM_3 );
				siIceMagicAct += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[enemyid], SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK, USE_SETITEM_4 );
				siIceMagicAct += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue(pclCM->CR[enemyid], SETITEM_ABILITY_TYPE_ICE_MAGIC_GET_ATTACK, USE_SETITEM_5 );
			}
		}

		if( !siIceMagicAct )
		{
			if(pclCM->CR[enemyid]->bNoIceAttackSwitch == FALSE)
			{
				cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
				pcltempchar->SetIce(pcldamageinfo->siDamage);
			}
		}
	}

	// ������ ���� ���� �Ӽ�
	if(pcldamageinfo->siAttackType == ATTACKTYPE_FROZEN)
	{
		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
		pcltempchar->SetFrozen(pcldamageinfo->siDamage);
	}
	// �������� �Ӽ��� ������ 
	if(pcldamageinfo->siAttackType == ATTACKTYPE_CURSEDEFENSE)
	{
		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];
		pcltempchar->SetCurseDefense(pcldamageinfo->siDamage, PassiveDamage, PassiveMana, enemyid);
	}
	// �̵��ӵ� ���ϰ� ������ 
	if(pcldamageinfo->siAttackType == ATTACKTYPE_CURSEMOVESPEED)
	{
		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];
		//[����] Ÿ�Ӻ극��ũ�� ������ �ߺ����� �Ҹ����� �ʰ� �ϱ�����. => 2008-6-16
		//pcltempchar->SetCurseMovespeed(pcldamageinfo->siDamage, PassiveDamage, PassiveMana, enemyid);
		pcltempchar->SetCurseMovespeed(pcldamageinfo->siDamage, PassiveDamage, 0, enemyid);
	}

	// ���׸��� �Ӽ��� ������ 
	if(pcldamageinfo->siAttackType == ATTACKTYPE_CANNON_MAGIC)
	{
		if(pclCM->CR[enemyid]->bNoIceAttackSwitch == FALSE)
		{
			cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
			pcltempchar->SetIce(pcldamageinfo->siDamage);
		}
	}
	// �Һٴ� ���� �Ӽ��� ������
	if(pcldamageinfo->siAttackType == ATTACKTYPE_MAGICFIREBURN)
	{
		cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[enemyid];
		pcltempchar->SetMagicFire(myid, pcldamageinfo->siDamage);
	}
	return TRUE;
}


//===============================================
// PASSIVE MAGIC�� �����Ų��. 
// PASSIVE MAGIC�� ���� Target�� �״��� ����� �����Ѵ�.
//===============================================
BOOL cltServer::PassiveMagicOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo)
{
	//=====================================================================
	// PREPROCESS : Passive �� ����ϱ����� �̸� ��� 
	// PASSIVE�� ������ ĳ���Ͱ� �׾������� ���ư���.
	if( pclCM->IsAlive(myid) == FALSE)			return FALSE;
	if( pclCM->IsValidID(enemyid) == FALSE)		return FALSE;

	// ���� Magic�� �����ϰ� �ְ� Passive magic �̶�� 
	SI32 magickind = pclCM->CR[myid]->GetCurrentMagic();
	SI32 magicactive = pclCM->CR[myid]->GetCurrentMagicCastType();

	// ���� ������ �����Ǿ����� �ʰų� PASSIVE������ �ƴ϶��
	if ( (magickind < MAGIC_INDEX_START) || (MAGIC_CASTTYPE_PASSIVE != magicactive) )	return FALSE;

	// ���� ������ ����Ÿ�԰� PASSIVE ���� Ÿ���� ��ġ�ϸ� �۵��Ѵ�.
	CMagicAttribute *pMagicAttributePtr = pclMagicManager->GetMagicAttributePtr();
	if(pMagicAttributePtr->IsMatchAttackTye(myid, magickind, pcldamageinfo->siAttackType) == false) return FALSE;

	SI32 hitrate = 0;	
	// pvp
	//if( IsWhereServiceArea(ConstServiceArea_English) )
	if(siEnablePVP == 1)
	{
		hitrate = pclCM->CR[myid]->clPB.GetHitRate( pclCM->CR[enemyid], pclCM->CR[myid], true );	
	}
	else
		hitrate = pclCM->CR[myid]->clPB.GetHitRate( pclCM->CR[enemyid], pclCM->CR[myid] );	

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		if(rand() % 10000 > hitrate) return FALSE;
	}
	else
	{
		if(rand() % 100 > hitrate) return FALSE;
	}
	//=====================================================================

	// �ش� Magic���κ��� Damage�� mana�� ���´�.
	SI32 PassiveDamage = 0, PassiveMana = 0;
	SI32 kind = 0, min  = 0, max = 0;
	// �ش� Magic �� ����� ����� ���´�.
	if(IsNPC(pclCM->CR[myid]->GetCharUnique())||IsInstanceNPC(pclCM->CR[myid]->GetCharUnique()))	kind =pclCM->CR[myid]->GetKind();

	// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
	SI32 SkillType = pMagicAttributePtr->GetMagicSkillType(magickind);
	if( SKILL_SIKLLBOOK == SkillType && IsPC(myid)  )
	{
		cltSkillBookMagic*	pclSkillBookMagic = pclCM->CR[myid]->pclCharSkillBookInfo->GetSkillBookMagic( pclCM->CR[myid]->GetAttackType() );	
		if( NULL == pclSkillBookMagic ) return FALSE;

		SkillType = pclSkillBookMagic->GetSkillUnique();
	}

	SI32 SkillLevel = pclCM->CR[myid]->pclCI->clCharSkill.GetTotalSkillLevel(SkillType, kind, pclCM->CR[myid]->pclCI->clIP.GetLevel(), &pclCM->CR[myid]->pclCI->clCharItem.clItem[0]);

	// �������� ���¿� ���� �߰� Damage�� �ΰ��Ѵ�.
	stMagicAttributeData *pMagicAttributeData = pMagicAttributePtr->GetMagicAttribute(magickind);
	SI32 siOrganUnique = pclCM->CR[myid]->pclCI->clHealthInfo.GetOrg(pMagicAttributeData->si16MagicOrganKind);

	stMagicInfo clMagicInfo(magickind, myid, enemyid, 0);
	// �ش� ����� �̿��Ͽ�  min, max, mana �� ����Ѵ�.
	pclMagicManager->GetMinMaxDamage( &clMagicInfo, pclCM->CR[myid]->clPB.GetAddMagicDamage(),  SkillLevel, min, max, siOrganUnique );
	pclMagicManager->CalculateDamage(min, max , PassiveDamage);
	PassiveMana = pclMagicManager->GetSpendMana(magickind, SkillLevel,myid);
	//=====================================================================


	BOOL bSuccess = FALSE;
	switch(pMagicAttributePtr->GetMagicGroup(magickind))
	{
		//=======================================================
		// DRAIN
		//=======================================================
	case MAGIC_GROUP_DRAIN:
		{
			// ���� ��Ȳ���̳� ��Ȳ�� ��ȯ����� DRAIN�� ���ֵ��� �ʴ´�.
			if( pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_VILLAGEGOD ||
				pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_VILLAGEGOD_SUMMON)
			{
				PassiveDamage =  1;
			}
			// ��ȯ����� Drain ���� ������ ���δ�.
			else if( pclCM->CR[myid]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				PassiveDamage /= 2;
			}
			cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];
			bSuccess = pcltempchar->SetDrain(pcldamageinfo->siDamage, PassiveDamage, PassiveMana);
		}
		break;
	case MAGIC_GROUP_CURSEATTACK:
		{
			cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];
			bSuccess = pcltempchar->SetCurseAttack(pcldamageinfo->siDamage, PassiveDamage, PassiveMana, enemyid);
		}
		break;
	case MAGIC_GROUP_CURSECRITICAL:
		{
			cltCharServer* pcltempchar = (cltCharServer*)pclCM->CR[myid];
			bSuccess = pcltempchar->SetCurseCritical(pcldamageinfo->siDamage, PassiveDamage, PassiveMana, enemyid);
		}
		break;
	default: 
		break;
	}

	// ��Ÿ ���ǿ� ���ؼ� ������ �����Ǿ��� ���� �ջ��Ų��.
	if(bSuccess)
	{
		// ������뿡 ���� �������� �ջ��� �߻���Ų��.
		if(IsPC(pclCM->CR[myid]->GetCharUnique()))
		{
			if(pclCM->CR[myid]->pclCI->clHealthInfo.DecreaseOrg(pMagicAttributeData->si16MagicOrganKind, pMagicAttributeData->si16MagicOrganDamage, pclCM->CR[myid]->pclCI->clIP.GetLevel()) == true)
			{
				pclCM->CR[myid]->SetUpdateSwitch(UPDATE_HEALTH, true, 0);		// Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
			}
		}
		// � ������ ��� ����ϴ��� �˻��Ѵ�.
		if(IsPC(pclCM->CR[myid]->GetCharUnique()))
		{
			pclMagicManager->IncreaseMagicUse(magickind);
		}

		// ��ȯ����� ������Ʈ �����ش�.
		SI32 siParentID = pclCM->CR[myid]->GetSummonParentID();
		if(pclCM->IsAlive(siParentID) == TRUE)
		{
			pclCM->CR[siParentID]->SetUpdateSwitch(UPDATE_SUMMON, true, 0);
		}

		// �������ġ�� ����Ų��.
		cltAttackDamageInfo clinfo;
		clinfo.Set(pcldamageinfo);
		clinfo.siMagicKind	= magickind;
		clinfo.siDamage		= PassiveDamage;
		ExpSkillOperate(myid, enemyid, &clinfo);
	}

	return bSuccess;

}
// myid�� enemyid�� �������� ���� ����ġ�� ���´�. 	
SI32 cltServer::GetExp(SI16 myid, SI16 enemyid, SI16 damage)
{
	SI32 exp = pclCM->CR[enemyid]->GetMyExp();

	// ���� Ÿ���̶��...
	SI32 bonusPercent = 0;

	if(pclClient->bBonusTimeSwitch)
	{
		if( bIsGMBonusTime && siGMBonusTimePercent > 0 )
		{
			bonusPercent = siGMBonusTimePercent;
		}
		else
		{
			if( pclClient->siServiceArea == ConstServiceArea_English )
			{
				bonusPercent = 30;
			}
			else if( pclClient->siServiceArea == ConstServiceArea_Japan )
			{
				bonusPercent = 50;
			}
			//LEEKH - 0810 - ����S ����ġ ������� ����.(+20%)
			else if( pclClient->siServiceArea == ConstServiceArea_Korea)
			{
				bonusPercent = 20;
			}
			// USA ����ġ ������� ����.(+100%) - by LEEKH 2007.12.03
			else if( pclClient->siServiceArea == ConstServiceArea_USA )
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
			else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )
			{
				bonusPercent = 30;
			}
			else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
			{
				bonusPercent = 30;
			}
			else
			{
				bonusPercent = 100;
			}

		}

	}

	// ���� ����
	if( pclEventTimeManager->InEventTime("GoonzuDay_HuntExpBonus150_9", &sTime) )
	{
		cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_HuntExpBonus150_9");
		if(pclEventTime)	{	bonusPercent = pclEventTime->m_siBonusAmount;	}
	}
	if( pclEventTimeManager->InEventTime("GoonzuDay_HuntExpBonus150_15", &sTime) )
	{
		cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_HuntExpBonus150_15");
		if(pclEventTime)	{	bonusPercent = pclEventTime->m_siBonusAmount;	}
	}
	if( pclEventTimeManager->InEventTime("GoonzuDay_HuntExpBonus200_21", &sTime) )
	{
		cltEventTime* pclEventTime = pclEventTimeManager->GetEvent("GoonzuDay_HuntExpBonus200_21");
		if(pclEventTime)	{	bonusPercent = pclEventTime->m_siBonusAmount;	}
	}

	// �ǽù� ����ڶ��

	//��ī�� �����̰� �ĳ��� �������� ��������� ȿ�� �ߺ�
	// 2007.06.27 [����]
	if ( pclCM->CR[myid]->pclCI->clBI.bPCRoom )
	{		
		if( pclCM->CR[myid]->pclCI->clBI.bPremiumService )
		{
			bonusPercent = max( bonusPercent , 50 );
		}
		bonusPercent += 50;
	}

	// �������� ��ȯ��2���� ���� ���Ͷ�� ����ġ 100% �߰�
	cltCharServer* pclenemychar = (cltCharServer*)pclClient->pclCM->CR[enemyid];
	if(pclenemychar->siCharMode == CHARMODE_SUMMON_EGG2)
	{
		bonusPercent += 100;
	}

	cltBufInfo * pclMyBuf = &pclCM->CR[myid]->pclCI->clBI.clBufInfo;
	SI32 parentID  = pclCM->CR[myid]->GetSummonParentID();
	if( IsPC(myid) )
	{
		if(    pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) 
			|| pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) 
			|| pclMyBuf->IsHaveBuf(BUF_HINAMOCHI) 
			|| pclMyBuf->IsHaveBuf(BUF_PREMIUMEXPUP)
			|| pclMyBuf->IsHaveBuf(BUF_SUPEREXPUP)
			|| pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) 
			|| pclMyBuf->IsHaveBuf(BUF_EXP_UP) 
			|| pclMyBuf->IsHaveBuf(BUF_SPECIALAMPUL_EXPUP300)
			|| pclMyBuf->IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE)	
			|| pclMyBuf->IsHaveBuf(BUF_RESIDENTS_EXPUP_10)
			|| pclMyBuf->IsHaveBuf(BUF_VALENTINEDAY))
		{
			//���� PC�̰� �������� ���̸� ���̶�� ����ġ�� 100% ���� 
			if( pclMyBuf->IsHaveBuf(BUF_SUPEREXPUP) )
			{
				bonusPercent += 100 ;
			}
			//���� PC�̰� ��� ���� ���̶�� ����ġ�� 100% ���� 
			if( pclMyBuf->IsHaveBuf(BUF_LOVEPOWER) )
			{
				bonusPercent += 100 ;
			}
			//���� PC�̰� ���� ���� ���̶�� ����ġ�� 50% ����

			if( pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP) )
			{
				// ���ʽ��� �پ���� �ʴ´�.
				bonusPercent += 50 ;
			}	

			// �������� �� �Ծ��ٸ� ����ġ + 100%;
			if( pclMyBuf->IsHaveBuf(BUF_HINAMOCHI) )
			{
				bonusPercent += 100;
			}

			if( pclMyBuf->IsHaveBuf(BUF_PREMIUMEXPUP) )
			{
				bonusPercent += 50 ;
			}

			// �̰� ���� ������ ����ġ + 100%
			if( pclMyBuf->IsHaveBuf(BUF_REWARDBONUS) )
			{
				bonusPercent += 100 ;
			}
			// [����] ����ġ ���� ���� �߰�. => 2008-6-27
			if(pclMyBuf->IsHaveBuf(BUF_EXP_UP))
			{
				bonusPercent += pclMyBuf->GetBufPercent(BUF_EXP_UP);
			}
			// [����] ����� ������ �Ծ��ٸ� ���� ����ġ + 200%
			if( pclMyBuf->IsHaveBuf(BUF_SPECIALAMPUL_EXPUP300))
			{
				bonusPercent += 200;
			}
			// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� ������ ���� �ϼ��� �� �����̸�. ����ġ�� 50% ���� 
			if( pclMyBuf->IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE))
			{
				bonusPercent += 50;
			}
			// [����] ���� EXP ĸ���� �Ծ��ٸ� ���� ����ġ + 10%
			if( pclMyBuf->IsHaveBuf( BUF_RESIDENTS_EXPUP_10))
			{
				bonusPercent += 10;
			}

			if( pclMyBuf->IsHaveBuf( BUF_VALENTINEDAY))
			{
				bonusPercent += 20;
			}
		}
		else	// ���, ���� ������ �������� �����̾� ����(�ĳ��� ������) �� üũ�Ѵ�
		{
			if( pclCM->CR[myid]->pclCI->clBI.bPremiumService )
			{
				bonusPercent = max( bonusPercent , 50 );
			}
		}

		if(IsCountrySwitch(Switch_Server_Event))
		{	
			//���� �̺�Ʈ ���� �Ⱓ�̸�...
			if( pclEventTimeManager->InEventTime("GoonzuDay_Week", &sTime) )
			{
				//[����] ���� �̺�Ʈ �Ϸ� 1�� �����̸� ������ ����ȴ�. => 2008-6-23
				// ���� Ÿ��Ȯ��.
				if( pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_ATTACK_EXP_150 || 
					pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_ATTACK_EXP_200		)
				{
					// �ߺ��Ұ�.
					if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)    &&
						false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP)   &&
						false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)    &&
						false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)	   &&
						false == pclMyBuf->IsHaveBuf(BUF_PREMIUMEXPUP) &&
						false == pclMyBuf->IsHaveBuf(BUF_SUPEREXPUP)   &&
						false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS)  &&
						false == pclMyBuf->IsHaveBuf(BUF_EXP_UP) )
					{
						switch(pclClient->pclServerEventManager->GetBonusBufType())
						{
						case CNServerEvent_Manager::SERVER_EVENT_BUF_ATTACK_EXP_150:
							{
								bonusPercent += 50 ;
							}
							break;
						case CNServerEvent_Manager::SERVER_EVENT_BUF_ATTACK_EXP_200:
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
					// �ߺ��Ұ�.
					if( false == pclMyBuf->IsHaveBuf(BUF_HINAMOCHI)    &&
						false == pclMyBuf->IsHaveBuf(BUF_FRIENDSHIP)   &&
						false == pclMyBuf->IsHaveBuf(BUF_LOVEPOWER)    &&
						false == pclMyBuf->IsHaveBuf(BUF_MAKEEXPUP)	   &&
						false == pclMyBuf->IsHaveBuf(BUF_PREMIUMEXPUP) &&
						false == pclMyBuf->IsHaveBuf(BUF_SUPEREXPUP)   &&
						false == pclMyBuf->IsHaveBuf(BUF_REWARDBONUS)  &&
						false == pclMyBuf->IsHaveBuf(BUF_EXP_UP) )
					{
						// ���� 1�� �������Դ� ����ġ�� �ִµ� 
						if(pclClient->pclServerEventManager->IsMyServerRankBest())
						{
							bonusPercent += 50;
							//bonusPercent += 100;
						}
						/*else if(pclClient->pclServerEventManager->IsMyServerRankBest2())
						{
							bonusPercent += 50;
						}*/
					}
				}
				else
				{
					// ���� �̺�Ʈ �������� ����ϴ� �ʿ� �Ⱓ���� �ð��� �� ������ ����ġ 2�������.
					if( pclClient->pclServerEventManager->IsEventMap(pclCM->CR[myid]->GetMapIndex()) )
					{
						bonusPercent += 100;
					}
				}
			}
		}
		SI16 siMyPVPLeagueGrade = pclCM->CR[myid]->GetPVP_LeagueGrade();

		// PVP ���Ѵ��� ��ް��� ���ʽ�
		switch ( siMyPVPLeagueGrade )
		{
		case PVP_LEAGUE_GRADE_1:
			{
				if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_1Grade_Bonus"), &sTime) )
				{
					cltEventTime* pcl1GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_1Grade_Bonus") );
					if ( pcl1GradeBonue )
					{
						bonusPercent += pcl1GradeBonue->m_siBonusAmount;
					}
				}
				else if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_1Grade_Bonus_2"), &sTime) )
				{
					cltEventTime* pcl1GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_1Grade_Bonus_2") );
					if ( pcl1GradeBonue )
					{
						bonusPercent += pcl1GradeBonue->m_siBonusAmount;
					}
				}
			}
			break;

		case PVP_LEAGUE_GRADE_2:
			{
				if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_2Grade_Bonus"), &sTime) )
				{
					cltEventTime* pcl2GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_2Grade_Bonus") );
					if ( pcl2GradeBonue )
					{
						bonusPercent += pcl2GradeBonue->m_siBonusAmount;
					}
				}
				else if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_2Grade_Bonus_2"), &sTime) )
				{
					cltEventTime* pcl2GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_2Grade_Bonus_2") );
					if ( pcl2GradeBonue )
					{
						bonusPercent += pcl2GradeBonue->m_siBonusAmount;
					}
				}
			}
			break;

		case PVP_LEAGUE_GRADE_3:
			{
				if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_3Grade_Bonus"), &sTime) )
				{
					cltEventTime* pcl3GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_3Grade_Bonus") );
					if ( pcl3GradeBonue )
					{
						bonusPercent += pcl3GradeBonue->m_siBonusAmount;
					}
				}
				else if ( pclEventTimeManager->InEventTime(TEXT("PVP_League_3Grade_Bonus_2"), &sTime) )
				{
					cltEventTime* pcl3GradeBonue = pclEventTimeManager->GetEvent( TEXT("PVP_League_3Grade_Bonus_2") );
					if ( pcl3GradeBonue )
					{
						bonusPercent += pcl3GradeBonue->m_siBonusAmount;
					}
				}
			}
			break;
		}	// switch ( siMyPVPLeagueGrade )

		// [����] ��ȥ�� ���� ����ġ ���
		if ( IsCountrySwitch(Switch_WeddingSystem) )
		{
			if ( (m_pclMarriageMgr) && (TRUE == pclCM->CR[myid]->IsMarried()) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclCM->CR[myid]->pclMarriage->GetConnectMode()) )
			{
				SI32 siMarriageValue = m_pclMarriageMgr->GetTotalExpAbilityValue( pclCM->CR[myid]->pclMarriage->GetLoveLevel() );
				if ( 0 < siMarriageValue )
				{
					bonusPercent += siMarriageValue;
				}
			}
		}
		// [����] ���� ���迡 ���� ����ġ ���
		if ( IsCountrySwitch((Switch_We_Are_Family) ) )	// �����ڵ�� ����..
		{
			cltCharServer* pclChar = pclCM->GetCharServer( myid)	;
			if(pclChar->pclFamily != NULL	)
			{
				if( pclChar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_PARANTS )	// �ϴ� �ڽ��� �θ� �ɸ��Ϳ��� �Ѵ�.
				{
					SI32 siOnChildNum = pclChar->pclFamily->GetOnChildrenNum()	;
					if ( siOnChildNum > 0 )	// �ڽ��ɸ��Ͱ� 1�� �̻� ���� �ؾ� �Ѵ�.
					{
						cltClient* pclclient = (cltClient*)pclClient;
						SI32 siAddValue	=	0	;

						SYSTEMTIME stFamilyEffectTime_Now	;

						// ���� �̿�� �Ⱓ�� ���� ���� �ִ� �ڽ� ���ڸ� ã�´�.
						for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++)
						{
							SI32 siCharPersonID = pclChar->pclFamily->GetChildPersonID( siSlot)	;
							if( siCharPersonID  > 0)
							{
								ZeroMemory( &stFamilyEffectTime_Now ,sizeof( SYSTEMTIME ))	;
								stFamilyEffectTime_Now	= pclChar->pclFamily->GetChild_Add_Date( siSlot ) ;						

								if ( stFamilyEffectTime_Now.wMonth > 0 && stFamilyEffectTime_Now.wMonth <= MAX_MONTH_FAMILY	&& 
									stFamilyEffectTime_Now.wDay > 0 && stFamilyEffectTime_Now.wDay <= MAX_DAY_FOR_FAMILY)
								{
									if ( sTime.wMonth > 0 && sTime.wMonth <= MAX_MONTH_FAMILY && sTime.wDay > 0 && sTime.wDay <= MAX_DAY_FOR_FAMILY  )
									{
										SI64 servertime = GetTimeValue(&sTime )	;
										SI64 limittime = GetTimeValue(&stFamilyEffectTime_Now )	;
										if ( servertime >0 && limittime > 0 )
										{
											if ( servertime < limittime )
											{
												siAddValue++	;

											}

										}

									}

								}
							}							
						}
						if ( MAX_FAMILY_ADD_EXP <= siAddValue )	{						siAddValue = MAX_FAMILY_ADD_EXP	; }	// �ִ�� 10%
						// ����� ��� ���� 
						bonusPercent += siAddValue;
						siAddValue = 0 ;	// �����ϰ� �� �ʱ�ȭ 
					}
				}
			}

		}

		// ��ȣ���ɿ� ���� ����ġ ����
		if ( IsCountrySwitch(Switch_SoulGuard) )
		{
			SI32 siSoulGuardValue = ((cltCharServer*)pclCM->CR[myid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_EXP_UP );
			if ( 0 < siSoulGuardValue )
			{
				bonusPercent += siSoulGuardValue;
			}
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
	}
	else if( pclCM->IsValidID( parentID ) )	// ��ȯ�����
	{
		//�θ� �����̾� ����ڶ��
		if ( pclCM->CR[parentID]->pclCI->clBI.bPremiumService || pclCM->CR[parentID]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_PREMIUMEXPUP) )
		{
			bonusPercent = max( 50 , bonusPercent ) ;
		}
	}


	// ����ġ ���ʽ��� �����Ѵٸ� �߰����ش�.
	if( bonusPercent > 0 )
	{
		exp += (SI32)(exp * bonusPercent / 100 );
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[enemyid];	// ������. 


	//---------------------------------------------
	// ������ ������ ���� ����ġ ����. 
	//---------------------------------------------
	// ���� �������� ���Ѵ�. 
	SI32 enemybattle	= pclCM->CR[enemyid]->clPB.GetBattlePower();

	// �������� �������� ���Ѵ�. 
	SI32 attackerbattle	= pclCM->CR[myid]->clPB.GetBattlePower();

	// ������̰� (��ȯ���� �̷� ������ ���� �ʴ´�.) 
	// �� ������ 20 �����϶��� ������ ����. 
	// ������ ���̰� ���̳��� ����ġ�� �����Ѵ�. 

	// ����� �г�Ƽ
	SI32 addHunger = 0;

	if(IsPC(myid) && pclCM->CR[myid]->pclCI->clIP.GetLevel() > 20 && attackerbattle >= 0)
	{
		SI32 percent = 0;
		bool bDoHunger = false;

		// 50���� �̻���͸� ����� ����
		if (pclCM->CR[myid]->pclCI->clIP.GetLevel() >= 50)
			bDoHunger = true;

		if(attackerbattle>0)	percent = enemybattle * 100 / attackerbattle;
		else					percent = 0;
		// 40%
		if(percent  < 40)		
		{	
			exp = 0;	

			if (bDoHunger)
				addHunger = 5;
		}
		// 50%
		else if( percent  < 50)	
		{	
			exp = exp * 30 / 100;

			if (bDoHunger)
				addHunger = 4;
		}
		// 60%
		else if( percent  < 60)	
		{	
			exp = exp * 40 / 100;		

			if (bDoHunger)
				addHunger = 3;

		}
		// 70%
		else if( percent  < 70)	
		{	
			exp = exp * 60 / 100;		

			if (bDoHunger)
				addHunger = 2;

		}
		// 80%
		else if( percent  < 80)	
		{	
			exp = exp * 80 / 100;		

			if (bDoHunger)
				addHunger = 1;

		}

	}

	//-----------------------------------------
	// ��ƿ�� ��� ����ġ�� ���� �ʴ´�. 
	//-----------------------------------------
	if(pclCM->CR[enemyid]->clJim.siJimHostCharUnique)
	{
		SI32 jimid = pclCM->GetIDFromCharUnique( pclCM->CR[enemyid]->clJim.siJimHostCharUnique );
		if(jimid)
		{
			// ���� ���� ���Ͱ� �ƴϰ� 
			// �� ������ ���� ���͵� �ƴϰ� 
			// �� ��ȯ���� ���� ���͵� �ƴϴ�.
			if(jimid != myid 
				&& jimid != pclCM->CR[myid]->GetSummonID()
				&& jimid != pclCM->CR[myid]->GetSummonParentID())
			{
				// ���� ĳ���Ͱ� ��Ƽ�� �������� �ʴٸ� 
				if(pclCM->CR[jimid]->siPartyIndex == 0 ||  (pclCM->CR[jimid]->siPartyIndex != pclCM->CR[myid]->siPartyIndex))
				{
					exp = 0;

					// �������� ��ƿ�̸�, 
					if(TABS(GetFrame() - pclCM->CR[enemyid]->clJim.dwNewJimFrame) > 100)
					{
						// �ش� ���Ͱ� ������� ���� �������� ��ƿ�� �����ȴ�. 
						if(pclCM->IsAlive(enemyid) == false)
						{
							cltCharServer* pclchar = (cltCharServer*)pclCM->CR[myid];

							pclchar->siStealNum++;
							SI32 stealnum		=	pclchar->GetStealNum();
							CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

							SI32 maxstealnum	= min(10, max(3, pclminister->m_siLimitStealNum));
							if(stealnum < maxstealnum)
							{
								SendServerResponseMsg( 0, SRVAL_BADSTEALACTION,  stealnum, maxstealnum, pclCM->CR[myid]->GetCharUnique() );
							}
							else
							{
								// ����ġ�� �ٿ��ش�.(level * 10)
								SI32 changedexp = pclchar->pclCI->clIP.GetLevel() * 10;
								pclchar->pclCI->clIP.DecreaseExp( changedexp );

								// Ŭ���̾�Ʈ�� ������ ������.
								// ����ġ ������� �뺸�Ѵ�. 
								cltGameMsgResponse_GetExp clinfo(pclchar->GetCharUnique(),  -changedexp,  0, 0);
								cltMsg clMsg(GAMEMSG_RESPONSE_GETEXP, sizeof(clinfo), (BYTE*)&clinfo);
								pclchar->SendNetMsg((sPacketHeader*)&clMsg);

								// ���� ����� ������. 
								pclchar->WarpToSafeZone();

								SendServerResponseMsg( 0, SRVAL_BADSTEALACTIONPUNISH,  changedexp, 0, pclCM->CR[myid]->GetCharUnique() );
							}
						}
					}
				}
			}
		}
	}

	if(pclCM->IsAlive(myid) == TRUE)
	{
		// ������� ������Ų��. 
		if(rand() % 8 == 0)
		{
			((cltCharServer*)pclCM->CR[myid])->MakeHunger(addHunger);
		}

	}

	if(pclCM->IsAlive(enemyid) == TRUE)
	{
		// ���� ��� �ִٸ� Ÿ���� �� �Ϳ� ����Ͽ� ����ġ�� �ش�. 
		SI32 enemymaxdamage = pclCM->CR[enemyid]->clPB.GetMaxLife();

		if(enemymaxdamage)
		{
			exp  = (exp * damage) / enemymaxdamage / 3;
		}
		else
		{
			exp  = 0;
		}

	}

	return exp;

}			

// ȣ������ �����. 
SI32 cltServer::MakeGuardChar(SI32 kind, SI16 homevillage, SI32 mapindex, SI32 x, SI32 y, cltOrderDataInfo* pclorder, cltEnemyTypeInfo* pclenemytype)
{

	if(kind)
	{
		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(pclenemytype);

		SI32 guardid = SetNPCChar(kind, homevillage, NULL, 100, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus, pclorder );
		if(guardid)
		{
			return guardid; 
		}
	}

	return 0;

}

// myid��  enemyid�� ������������ ����ġ ��ġ. 
SI32 cltServer::ExpOperate(SI32 myid, SI32 enemyid, cltAttackDamageInfo* pcldamageinfo)
{
	WRITE_MEMLOG( 130, 1, 0, 0 );

	SI32 i;

	//--------------------------------------------------------------------
	// �����ڰ� ����� ����ġ�� ���� ���� �� ����. 
	//--------------------------------------------------------------------
	if( pclCM->IsAlive(myid) == false)return 0;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[myid];
	CMagicAttribute *pMagicAttributePtr = pclMagicManager->GetMagicAttributePtr();
	if ( pMagicAttributePtr->GetMagicGroup(pcldamageinfo->siMagicKind) == MAGIC_GROUP_DRAIN )
		return 0;

	//--------------------------------------------------------------------
	// ����ڰ� �ƴϰ� ��ȯ���� �ƴϸ� ����ġ�� ���� �� ����. 
	//--------------------------------------------------------------------
	if(IsPC(pclchar->GetCharUnique()) == false && pclchar->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)return 0;

	//--------------------------------------------------------------------
	// Clone�� �ƴ� �𿡰Լ��� ����ġ�� ������ �ִ�.
	//--------------------------------------------------------------------
	if(pclCM->CR[enemyid]->IsAtb(ATB_CLONE)&& pclCM->CR[enemyid]->clInnerStatus.IsStatus(INNERSTATUS_CLONE) == true) return 0;


	//[����] ���̾�Ʈ ���� ��Ȱ ���� �̺�Ʈ �����ؼ� ������ ���ʹ� ����ġ�� ���� �ʴ´�.
	if( IDENTITY_GIANTRACCOONRESURRECTEVENT == pclCM->CR[enemyid]->clIdentity.siIdentity )
	{
		return 0;
	}

	//--------------------------------------------------------------------
	// myid�� enemyid�� �����ؼ� damage�� ������ ����� ����ġ�� ���Ѵ�. 
	//-------------------------------------------------------------------
	SI32 exp = GetExp(myid, enemyid, pcldamageinfo->siDamage);
	if(exp <= 0)return 0;

	//-------------------------------------------------------------------
	// �ּ��� ������ ������ ���� ����ġ�� ���ߵȴ�. 
	//-------------------------------------------------------------------
	SI32 siExpBonus = 0;

	if(pclCM->CR[myid]->pclCI->clBI.siHomeVillage)
	{
		cltStrInfo* pclstr = pclCityHallManager->GetStrInfo( pclCM->CR[myid]->pclCI->clBI.siHomeVillage );
		if(pclstr)
		{
			SI32 villagelevel = min(50, pclstr->clCityhallStrInfo.siVillageLevel / 2);

			if(villagelevel)
			{
				//exp = exp * (100 + villagelevel) / 100;
				siExpBonus += villagelevel;
			}
		}
	}


	//-------------------------------------------------------------------
	// myid�� ��Ƽ ���̸� ��Ƽ�� �⿩�� �ٸ� ����Ѵ�. 
	//-------------------------------------------------------------------
	// [����] ��ȯ���� ��Ƽ ����, ����Ʈ ������ ����. ��Ƽ ����Ʈ ���� ó���� ��ȯ�� ĳ���͸� ������ �Ѵ�.
	if ( pclchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
	{
		SI32 siParentID = pclchar->GetSummonParentID();
		cltCharServer* pRealCharacter = (cltCharServer*)pclCM->CR[siParentID];
		if ( NULL != pRealCharacter )
		{
			if( pRealCharacter->siPartyIndex > 0 )
			{
				pclPartyMgr->IncreaseExp(pRealCharacter->siPartyIndex, pRealCharacter->pclCI->GetPersonID(), exp);

				//-------------------------------------------------------------------
				// myid�� ��Ƽ ����� �غ���� ����Ʈ��� ����Ʈ�� Ŭ���� ��Ų��.
				//-------------------------------------------------------------------
				pRealCharacter->DoQuestCheckAndAction(QUEST_CLEAR_COND_PARTYHUNTING);

				SI16 siGetType		= 0;
				SI16 siGetUnique	= 0;
				SI16 siGetPara1		= 0;
				SI16 siGetPara2		= 0;

				// QUEST_CLEAR_COND_TWOWAYKILLMONBONUS������� ���͸� ������ �ش� ��Ƽ���� ���� ������� �ϰ� �����ϰ� �ִ� ��Ƽ���� 2���̻��̶��
				if ( pRealCharacter->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMONBONUS, &siGetType, &siGetUnique, &siGetPara1, &siGetPara2) )
				{
					SI16 siEnemyKind = pclCM->CR[enemyid]->GetKind();
					if ( (siGetPara1) && (siEnemyKind == siGetPara1) && (2 <= pclPartyMgr->CountQuestPalyUserNum(pRealCharacter->siPartyIndex, QUEST_CLEAR_COND_TWOWAYKILLMONBONUS)) )
					{
						siExpBonus += 20;
					}
				}
			}
		}
	}
	
	else if(pclchar->siPartyIndex > 0)
	{
		pclPartyMgr->IncreaseExp(pclchar->siPartyIndex, pclchar->pclCI->GetPersonID(), exp);

		//-------------------------------------------------------------------
		// myid�� ��Ƽ ����� �غ���� ����Ʈ��� ����Ʈ�� Ŭ���� ��Ų��.
		//-------------------------------------------------------------------
		pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_PARTYHUNTING);

		SI16 siGetType		= 0;
		SI16 siGetUnique	= 0;
		SI16 siGetPara1		= 0;
		SI16 siGetPara2		= 0;

		// QUEST_CLEAR_COND_TWOWAYKILLMONBONUS������� ���͸� ������ �ش� ��Ƽ���� ���� ������� �ϰ� �����ϰ� �ִ� ��Ƽ���� 2���̻��̶��
		if ( pclchar->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMONBONUS, &siGetType, &siGetUnique, &siGetPara1, &siGetPara2) )
		{
			SI16 siEnemyKind = pclCM->CR[enemyid]->GetKind();
			if ( (siGetPara1) && (siEnemyKind == siGetPara1) && (2 <= pclPartyMgr->CountQuestPalyUserNum(pclchar->siPartyIndex, QUEST_CLEAR_COND_TWOWAYKILLMONBONUS)) )
			{
				siExpBonus += 20;
			}
		}
	}

	if ( 0 < siExpBonus )
	{
		exp += ((exp * siExpBonus) / 100);
	}


	//-----------------------------------------------------------------
	// enemyid�� ����ÿ���. 
	//-----------------------------------------------------------------
	if(pclCM->IsAlive(enemyid) == FALSE)
	{
		//---------------------------------------------------------------------
		// �����ڰ� �����忡 �ִٸ� ������ ������Ե� ����ġ�� �Ϻ� �ش�. (3%)
		//---------------------------------------------------------------------
		SI32 huntvillageunique = pclchar->GetHuntVillageUnique();
		if(huntvillageunique)
		{
			// �����忡�� ���� ��ȯ��������踦 ����. 
			pclItemManager->AddUseNum( pclKindInfoSet->pclKI[ pclCM->CR[enemyid]->GetKind() ]->siDollUnique, 1);

			// ���ο� ���
			//NStatistics_Add("Item", pclKindInfoSet->pclKI[ pclCM->CR[enemyid]->GetKind() ]->siDollUnique, "UseNum", 1);


			if(rand() % 100 == 0)
			{

				cltHunt* pclhunt = (cltHunt*)pclHuntManager->pclStruct[huntvillageunique];
				if(pclhunt)
				{
					pclhunt->clStrInfo.clHuntStrInfo.siChiefExp += exp;		// ����ġ�� ������Ų��. 
				}
			}
		}

		//--------------------------
		// ��� ����ġ�� �ش�. 
		//--------------------------
		SI32 skillexp = 0;
		SI32 skillunique = pMagicAttributePtr->GetMagicSkillType(pcldamageinfo->siMagicKind);
		
		// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
		if( SKILL_SIKLLBOOK == skillunique && IsPC(pclchar->GetID())  )
		{
			cltSkillBookMagic*	pclSkillBookMagic = pclchar->pclCharSkillBookInfo->GetSkillBookMagic( pclchar->GetAttackType() );	
			if( NULL == pclSkillBookMagic ) return 0;

			skillunique = pclSkillBookMagic->GetSkillUnique();
		}

		if(skillunique <= 0)
		{
			if((rand() % 3) == 0)
			{
				switch(pcldamageinfo->siAttackType)
				{
				case ATTACKTYPE_SWORD:		skillunique = SKILL_USESWORD1;				break;
				case ATTACKTYPE_SPEAR:		skillunique = SKILL_USESPEAR1;				break;
				case ATTACKTYPE_AXE:		skillunique = SKILL_USEAXE1;				break;
				case ATTACKTYPE_STAFF:
				case ATTACKTYPE_STAFF1:
				case ATTACKTYPE_STAFF2:			//skillunique = SKILL_USESTAFF1;				break;
				case ATTACKTYPE_NEW_STAFF2: skillunique = SKILL_USESTAFF1;				break;
				case ATTACKTYPE_BOW:
				case ATTACKTYPE_BOW1:		//skillunique = SKILL_USEBOW1;				break;
				case ATTACKTYPE_NEW_BOW1:	skillunique = SKILL_USEBOW1;				break;
				case ATTACKTYPE_GUN:
				case ATTACKTYPE_GUN1:		//skillunique = SKILL_USEGUN1;				break;
				case ATTACKTYPE_NEW_GUN1:	skillunique = SKILL_USEGUN1;				break;
				default:
					{
						// ���Ÿ� ���� �����ΰ��, bullet ���� �����ϴ� ��츸 ó���Ѵ�.
						// bullet �� AttackType�� ����ϱ⶧����, ������ ���� ĳ������ ����Ÿ������ ó���Ѵ�.
						// ���� �߿��� ���⸦ ������ �� ���� ������ ĳ������ ����Ÿ������ ó���ص� ���� ����.
						SI32 siBulletUnique = pclAttackTypeInfoManager->GetBulletUnique(pcldamageinfo->siAttackType);
						if( pclchar->clTransFormInfo.bTransFormMode &&
							siBulletUnique > 0 )
						{
							switch( pclchar->GetAttackType() )
							{
								//case ATTACKTYPE_SWORD:	skillunique = SKILL_USESWORD1;				break;
								//case ATTACKTYPE_SPEAR:	skillunique = SKILL_USESPEAR1;				break;
								//case ATTACKTYPE_AXE:	skillunique = SKILL_USEAXE1;				break;
							case ATTACKTYPE_STAFF:
							case ATTACKTYPE_STAFF1:
							case ATTACKTYPE_STAFF2:	//skillunique = SKILL_USESTAFF1;				break;
							case ATTACKTYPE_NEW_STAFF2: skillunique = SKILL_USESTAFF1;				break;
							case ATTACKTYPE_BOW:
							case ATTACKTYPE_BOW1: //skillunique = SKILL_USEBOW1;				break;
							case ATTACKTYPE_NEW_BOW1:skillunique = SKILL_USEBOW1;				break;
							case ATTACKTYPE_GUN:
							case ATTACKTYPE_GUN1: //skillunique = SKILL_USEGUN1;				break;
							case ATTACKTYPE_NEW_GUN1:skillunique = SKILL_USEGUN1;				break;
							}
						}
					}
					break;
				}

				skillexp = exp /	2;
			}
		}
		else
		{
			skillexp = exp /	10;
		}

		// �Ƿι��� ����
		skillexp = pclchar->CalcTiredPoint( skillexp );


		if(skillexp > 0 && skillunique > 0 )
		{
			SI32 maxskilllevel	= pclSkillManager->GetMaxLevel(skillunique);
			if(skillunique >= 0)
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[myid];		
				pclchar->SetSkillUpdate(skillunique, skillexp);
			}
		}



		//-----------------------------
		// ��Ƽ���̸� ����ġ �볪�Ա�
		//-----------------------------
		//if( pclchar->siPartyIndex )
		// [����] ų�� ĳ���� ��ȯ���ϰ��
		cltCharServer* pRealCharacter = NULL;
		if ( pclchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			SI32 siParentID = pclchar->GetSummonParentID();
			cltCharServer* tmpChar = (cltCharServer*)pclCM->CR[siParentID];
			if ( NULL != tmpChar )
			{
				pRealCharacter = tmpChar;
			}
		}
		else
		{
			pRealCharacter = pclchar;
		}

		if( pRealCharacter->siPartyIndex )
		{
			CPartyObj* pclparty = pclPartyMgr->GetPartyObj(pRealCharacter->siPartyIndex);
			if(pclparty)
			{
				SI32 totallevel = 0;

				SI32 partyindex = 0;
				SI32 partylist[MAX_PARTY_USER_NUM];
				for(i = 0;i < MAX_PARTY_USER_NUM;i++)
				{
					partylist[i] = 0;
				}

				// ��ȿ�� ��Ƽ���� ����Ʈ�� ���Ѵ�. 
				stPartyUser* puser = NULL;
				for(i = 0;i < MAX_PARTY_USER_NUM;i++)
				{
					puser = pclparty->GetPartyUser(i);
					if(puser && puser->bPartyStatus == true)
					{
						if(pclCM->IsValidID(puser->siCharUnique) && 
							pclCM->CR[puser->siCharUnique]->pclCI->GetPersonID() == puser->siPersonID)
						{
							// ���Ϳ� ���� ����, ���� �����ȿ� �־�� �Ѵ�. �׸��� ��� �־�� �Ѵ�.
							if( pclCM->CR[enemyid]->GetMapIndex() == pclCM->CR[puser->siCharUnique]->GetMapIndex() &&
								max(TABS(pclCM->CR[enemyid]->GetX() - pclCM->CR[puser->siCharUnique]->GetX()), TABS(pclCM->CR[enemyid]->GetY() - pclCM->CR[puser->siCharUnique]->GetY())) < 30 &&
								pclCM->IsAlive(puser->siCharUnique) )								
							{
								//��Ƽ���� 20���� ���̳��� ����ġ �� �� ����.�Ϻ� ����
								if(pclClient->IsCountrySwitch(Switch_20levelparty)){
									if( pRealCharacter->pclCI->clIP.GetLevel() - 20 <= puser->siLevel &&
										pRealCharacter->pclCI->clIP.GetLevel() + 20 >= puser->siLevel )
									{
										partylist[partyindex] = puser->siCharUnique;
										partyindex++;
									}
								}
								else{//�Ϻ��� �׳� ����
									partylist[partyindex] = puser->siCharUnique;
									partyindex++;
								}
							}
						}
					}
				}	

				WRITE_MEMLOG( 130, 2, 0, 0 );

				if(partyindex <= 0 || partyindex > MAX_PARTY_USER_NUM) return 0;

				// ����ġ�� ������Ų��. (�߰� 1�δ� 10%) 
				if(partyindex > 1)
				{
					exp = exp + exp * (partyindex - 1) * 10 / 100;
				}

				// ���� �հ踦 ���Ѵ�. 
				for(i = 0;i < partyindex;i++)
				{
					// ���� �հ踦 ���Ѵ�. 
					totallevel += pclCM->CR[ partylist[i] ]->pclCI->clIP.GetLevel();
				}

				// ����ġ�� ����Ѵ�. 
				if(totallevel)
				{
					for(i = 0;i < partyindex;i++)
					{
						SI32 tempexp		= 0;
						SI32 level			= pclCM->CR[ partylist[i] ]->pclCI->clIP.GetLevel();
						SI32 siEnemyKind	= pclCM->CR[enemyid]->GetKind();

						tempexp = exp * level / totallevel;

						//KHY - 1210 - ��Ƽ ����ġ �ִ밪 ���� *100 ����.
						// ����ġ�� �ִ밪�� level * 100 
						tempexp = min(level * 100, tempexp);

						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ partylist[i] ];

						// ��Ƽ�� ������ ����ġ�� ��ȯ���� �����ֿ� ���� ���´�.
						if(pclchar)
						{
							IncreaseBothExp(partylist[i],  tempexp);

							pclchar->IncQuestPara( QUEST_CLEAR_COND_PARTYKILLMON, siEnemyKind, 1 );

							pclchar->IncQuestPara( QUEST_CLEAR_COND_TWOWAYKILLMON, siEnemyKind, 1 );
							pclchar->IncQuestPara( QUEST_CLEAR_COND_TWOWAYKILLMONBONUS, siEnemyKind, 1 );
						}
					}
				}

				WRITE_MEMLOG( 130, 3, 0, 0 );
			}
		}
		else	// ���� �׾����� ��Ƽ���� �ƴϸ� 
		{
			IncreaseBothExp(myid,  exp);
		}
		// ��������
		// ���� ����ġ�� 0.3%�� ���� ������  �ڳ࿡�� �ش�.
		// �ִ°� ������ 500�� �ִ� 
		if( exp )
		{
			if( IsCountrySwitch( Switch_We_Are_Family ) )
			{
				if(pclchar->pclFamily != NULL )
				{
					if( pclchar->pclFamily->IsParent( pclchar->pclCI->GetPersonID() ) == MYCLASS_IN_FAMILY_PARANTS )// ���� �θ� �϶�.
					{
						if(  pclchar->pclFamily->GetOnChildrenNum() > 0  ) // �������ִ� ����� 0�̻�
						{
							SI32 other_Add_Exp =  exp * FAMILY_ADD_CHILDREN_EXP	; // �ڽĵ鿡�� �� exp
							if( other_Add_Exp >= 500) 
							{
								other_Add_Exp = 500 ; 
							}
							if( other_Add_Exp <= 1) 
							{
								other_Add_Exp = 1 ; 
							}
							if ( other_Add_Exp > 0 )
							{
								for ( SI32 siSlot = 0; siSlot < MAX_CHILDREN_NUM ; siSlot++)
								{
									SI32 siChildren_PersonID = pclchar->pclFamily->GetChildPersonID( siSlot)	;
									SI32 siChildren_id = pclCM->GetIDFromPersonID( siChildren_PersonID )		;
									if(pclCM->IsValidID( siChildren_id ) == false )	continue					;
									cltCharServer* pclChildrenCharServer =  pclCM->GetCharServer( siChildren_id )	;
									pclChildrenCharServer->IncreaseExp( other_Add_Exp )	;
								}
							}
						}
					}
				}
			}


		}
	}
	else		// ���� ��� ������ 
	{
		IncreaseBothExp(myid,  exp);
	}

	return exp;

}

SI32 cltServer::ExpSkillOperate( SI32 siMyID, SI32 siEnemyID, cltAttackDamageInfo* pclDamageInfo )
{
	// �����ϴ� ����� �׾� �ִٸ� ����ġ�� ���� �� ����
	if ( FALSE == pclCM->IsAlive(siMyID) )
	{
		return 0;
	}

	// ���� �޴� ���� �׾������� ��ų ����ġ�� ���� �� �ִ�
	if ( TRUE == pclCM->IsAlive(siEnemyID) )
	{
		return 0;
	}

	if ( NULL == pclDamageInfo )
	{
		return 0;
	}

	// �����ϰ�� ��ų����ġ�� ���� �ʴ´�
	CMagicAttribute* pclMagicAttributePtr = pclMagicManager->GetMagicAttributePtr();
	if ( (NULL == pclMagicAttributePtr) || (MAGIC_GROUP_DRAIN == pclMagicAttributePtr->GetMagicGroup(pclDamageInfo->siMagicKind)) )
	{
		return 0;
	}

	cltCharServer* pclMyChar = pclCM->GetCharServer( siMyID );
	if ( NULL == pclMyChar )
	{
		return 0;
	}

	// ������ �ƴϰų� ��ȯ���� �ƴϸ� ����ġ�� �� ��´�
	if ( (false == IsPC(pclMyChar->GetCharUnique())) && (IDENTITY_PERSON_SUMMON != pclMyChar->clIdentity.siIdentity) )
	{
		return 0;
	}

	cltCharServer* pclEnemyChar = pclCM->GetCharServer( siEnemyID );
	if ( NULL == pclEnemyChar )
	{
		return 0;
	}

	// Ŭ���� �����Լ��� ����ġ�� ���� �� ����
	if ( (pclEnemyChar->IsAtb(ATB_CLONE)) && (pclEnemyChar->clInnerStatus.IsStatus(INNERSTATUS_CLONE)) )
	{
		return 0;
	}

	//[����] ���̾�Ʈ ���� ��Ȱ ���� �̺�Ʈ �����ؼ� ������ ���ʹ� ����ġ�� ���� �ʴ´�.
	if( IDENTITY_GIANTRACCOONRESURRECTEVENT == pclEnemyChar->clIdentity.siIdentity )
	{
		return 0;
	}

	// �ϴ� ��ų ����ġ�� ���ϱ��� �õ尪�� ĳ���� ����ġ�� ���Ѵ�
	SI32 siGetExp = GetExp( siMyID, siEnemyID, pclDamageInfo->siDamage );
	if ( 0 >= siGetExp )
	{
		return 0;
	}

	SI32 siExpBonus = 0;
	if ( 0 < pclMyChar->pclCI->clBI.siHomeVillage )
	{
		cltStrInfo* pclGetStrInfo = pclCityHallManager->GetStrInfo( pclMyChar->pclCI->clBI.siHomeVillage );
		if ( pclGetStrInfo )
		{
			SI32 siCalcVillageLevel = min( 50, pclGetStrInfo->clCityhallStrInfo.siVillageLevel/2 );
			if ( 0 < siCalcVillageLevel )
			{
				siExpBonus += siCalcVillageLevel;
			}
		}
	}

	if ( 0 < pclMyChar->siPartyIndex )
	{
		SI16 siGetType		= 0;
		SI16 siGetUnique	= 0;
		SI16 siGetPara1		= 0;
		SI16 siGetPara2		= 0;

		// QUEST_CLEAR_COND_TWOWAYKILLMONBONUS������� ���͸� ������ �ش� ��Ƽ���� ���� ������� �ϰ� �����ϰ� �ִ� ��Ƽ���� 2���̻��̶��
		if ( pclMyChar->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TWOWAYKILLMONBONUS, &siGetType, &siGetUnique, &siGetPara1, &siGetPara2) )
		{
			if ( (siGetPara1) && (pclEnemyChar->GetKind() == siGetPara1) && (2 <= pclPartyMgr->CountQuestPalyUserNum(pclMyChar->siPartyIndex, QUEST_CLEAR_COND_TWOWAYKILLMONBONUS)) )
			{
				siExpBonus += 20;
			}
		}
	}

	// ���ʽ� ����Ʈ�� ����Ѵ�
	if ( 0 < siExpBonus )
	{
		siGetExp += ((siGetExp * siExpBonus) / 100);
	}

	// ���� ��� ����ġ�� �ش�
	SI32 siSkillExp		= 0;
	SI32 siSkillType	= pclMagicAttributePtr->GetMagicSkillType( pclDamageInfo->siMagicKind );
	SI32 siSkillUnique	= 0;

	// ��ų Ÿ���� ������
	if ( 0 >= siSkillType )
	{
		// 3���� 1Ȯ����
		if ( (rand() % 3) == 0 )
		{
			switch ( pclDamageInfo->siAttackType )
			{
			// ��
			case ATTACKTYPE_SWORD:		siSkillUnique = SKILL_USESWORD1;	break;
			// â
			case ATTACKTYPE_SPEAR:		siSkillUnique = SKILL_USESPEAR1;	break;
			// ����
			case ATTACKTYPE_AXE:		siSkillUnique = SKILL_USEAXE1;		break;
			// ������
			case ATTACKTYPE_STAFF:
			case ATTACKTYPE_STAFF1:
			case ATTACKTYPE_STAFF2:
			case ATTACKTYPE_NEW_STAFF2: siSkillUnique = SKILL_USESTAFF1;	break;
			// Ȱ
			case ATTACKTYPE_BOW:
			case ATTACKTYPE_BOW1:
			case ATTACKTYPE_NEW_BOW1:	siSkillUnique = SKILL_USEBOW1;		break;
			// ��
			case ATTACKTYPE_GUN:
			case ATTACKTYPE_GUN1:
			case ATTACKTYPE_NEW_GUN1:	siSkillUnique = SKILL_USEGUN1;		break;
			default:
				{
					// ���Ÿ� ���� �����ΰ��, bullet ���� �����ϴ� ��츸 ó���Ѵ�.
					// bullet �� AttackType�� ����ϱ⶧����, ������ ���� ĳ������ ����Ÿ������ ó���Ѵ�.
					// ���� �߿��� ���⸦ ������ �� ���� ������ ĳ������ ����Ÿ������ ó���ص� ���� ����.
					SI32 siBulletUnique = pclAttackTypeInfoManager->GetBulletUnique(pclDamageInfo->siAttackType);
					if ( (0 < siBulletUnique) && (pclMyChar->clTransFormInfo.bTransFormMode ) )
					{
						// ���Ÿ� ���⸸ �ش�
						switch( pclMyChar->GetAttackType() )
						{
						// ������
						case ATTACKTYPE_STAFF:
						case ATTACKTYPE_STAFF1:
						case ATTACKTYPE_STAFF2:	
						case ATTACKTYPE_NEW_STAFF2:		siSkillUnique = SKILL_USESTAFF1;	break;
						// Ȱ
						case ATTACKTYPE_BOW:
						case ATTACKTYPE_BOW1:
						case ATTACKTYPE_NEW_BOW1:		siSkillUnique = SKILL_USEBOW1;		break;
						// ��
						case ATTACKTYPE_GUN:
						case ATTACKTYPE_GUN1:
						case ATTACKTYPE_NEW_GUN1:		siSkillUnique = SKILL_USEGUN1;		break;
						}
					}
				}
				break;
			}

			siSkillExp = siGetExp / 2;
		}
	}
	else
	{
		siSkillExp = siGetExp / 10;
	}

	// �Ƿι��� ����
	siSkillExp = pclMyChar->CalcTiredPoint( siSkillExp );

	if ( (0 < siSkillExp) && (0 < siSkillUnique) )
	{
		pclMyChar->SetSkillUpdate( siSkillUnique, siSkillExp );
	}

	return siSkillExp;
}

#define GIVEEXP_EACHOTHER	30

void cltServer::IncreaseBothExp(SI32 siID, SI32 siExp)
{

	if(pclCM->IsValidID(siID) == FALSE) return;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];

	SI32 mapindex = pclchar->GetMapIndex();

	// PK ���� ����� �ϰ�� ����ġ �߰� ����.
	if( pclClient->pclMapManager->IsPkMap( mapindex ) )
	{
		siExp = siExp * siPKMapExpRate / 100;
	}

	// �Ƿι��� �ý��� ����
	siExp = pclchar->CalcTiredPoint( siExp );

	// ��尡 ������ �����ϰ��

	if( pclClient->pclMapManager->IsGuildMap( mapindex )  )
	{
		pclGuildDungeonMgr->AddExp( mapindex, siExp );
	}



	SI32 siMyExp    = siExp;
	SI32 siOtherExp = 0;

	//=========================================================================
	// ����� ���͸� �׿� ����ġ�� ������ 
	//=========================================================================
	// ���� ��ȯ���� ���� ������ ���� ���� ����ġ�� ��ȯ���� ������ ���´�.
	//=========================================================================
	SI32 siSummonID = pclchar->GetSummonID();
	if(pclCM->IsAlive(siSummonID) == TRUE)
	{
		cltCharServer* pclSummonChar = (cltCharServer*)pclCM->CR[siSummonID];

		SI32 summonlevel	= pclSummonChar->pclCI->clIP.GetLevel();
		SI32 parentlevel	= pclchar->pclCI->clIP.GetLevel();

		SI32 siTotalLevel = max(1, summonlevel + parentlevel);
		if(summonlevel + parentlevel <= 0)
		{
			pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("fdieff:summonlevel:%d parentlevel:%d"), summonlevel, parentlevel);
		}


		// �θ��� ��ȯ���� ������ ����ġ�� �� ��´�. 
		SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

		//=========================================================================
		// ��ȭ��Ű�� ������� ��ȯ���� �г�Ƽ 
		//=========================================================================
		SI32 siSkillModfier = 10;
		SI32 siCurrSummonKind  = pclSummonChar->GetKind();
		if(pclKindInfoSet->IsValidKind(siCurrSummonKind) == true)
		{
			if(pclSummonChar->pclKI->bSummonMall == TRUE)
			{
				siSkillModfier = 10;
			}
			else if(summonlevel	> pclSummonChar->pclKI->siEvolveLevel) // ��ȭ�ñⰡ ������ 
			{
				if(summonlevel		> pclSummonChar->pclKI->siEvolveLevel * 2)		siSkillModfier = 20;
				else if(summonlevel > pclSummonChar->pclKI->siEvolveLevel * 1.5)	siSkillModfier = 15;
				else																siSkillModfier = 10;
			}
		}

		//=========================================================================
		// ��ȯ���� ��� ����ġ�� ����Ѵ�.
		//=========================================================================
		siOtherExp	= (SI32)(siExp  * GIVEEXP_EACHOTHER * 0.01f);
		pclchar->SetSkillUpdate(SKILL_SUMMON,  max( siOtherExp / siSkillModfier , 1 ) );	// ��ȯ�� ����ġ�� �߰��Ѵ�. (�ּ� 1�� ����)
		siOtherExp += (siOtherExp * skilllevel / 100);						// ��ȯ���� �ɷ�ġ��ŭ ����ġ�� �߰��Ѵ�.
		if ( bSpecailDay7switch ) // �湫�� ź���Ͽ��� ��ȯ������ ����ġ�� 2��
		{
			if ( pclCM->CR[siSummonID]->pclKI->bSummonMall == TRUE )
			{
				siOtherExp = siOtherExp*2 ;
			}
		}
		if(siOtherExp > 0)	pclSummonChar->IncreaseExp(siOtherExp);

		// ���� ���� ����ġ 
		siMyExp    = siExp;			// ������ ���� ���� �״�� �� �ش�.		

		//===========================================================
		// 5%�� Ȯ���� ������ ��ȯ�����Ե� ����ġ�� �Ȱ��� �ش�.
		//===========================================================
		if(siOtherExp  > 0 && rand()%20 == 0)
		{
			for(SI32 i = 0; i < MAX_SUMMON_OWN; ++i)
			{
				// ������ ��ȯ�����Ը� ����ġ�� �ش�.
				if(i != pclSummonChar->GetSummonIndex())
				{
					cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummon(i);
					if(pclSummon && pclSummon->siKind)
					{
						pclSummon->clIP.IncreaseExp(siOtherExp); 
						cltGameMsgResponse_Summon clInfo(pclchar->GetCharUnique(), i, pclSummon);
						cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
						pclchar->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}

	}

	//=========================================================================
	// ��ȯ���� ���͸� �׿� ����ġ�� ������ 
	//=========================================================================
	// ���� ��ȯ����� ���� ���� ����ġ�� ������ ���´�.
	//=========================================================================
	SI32 siParentID = pclchar->GetSummonParentID();
	if(pclCM->IsAlive(siParentID) == TRUE)
	{
		cltCharServer* pclParentChar = (cltCharServer*)pclCM->CR[siParentID];

		SI32 summonlevel	= pclchar->pclCI->clIP.GetLevel();
		SI32 parentlevel	= pclParentChar->pclCI->clIP.GetLevel();

		SI32 siTotalLevel = max(1, summonlevel + parentlevel);
		if(summonlevel + parentlevel <= 0)
		{
			pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("f123dieff:summonlevel:%d parentlevel:%d"), summonlevel, parentlevel);
		}

		// �θ��� ��ȯ���� ������ ����ġ�� �� ��´�. 
		SI32 skilllevel = pclParentChar->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclParentChar->pclCI->clCharItem.clItem[0]);

		//=========================================================================
		// ���� ��� ����ġ�� ����Ѵ�.
		//=========================================================================
		siOtherExp	= (SI32)(siExp * GIVEEXP_EACHOTHER * 0.01f );
		if(siOtherExp > 0) pclParentChar->IncreaseExp(siOtherExp);

		siMyExp	 =	siExp;										// ��ȯ���� ������ ��ȯ���� �״�� ����ġ�� ��´�.

		//=========================================================================
		// ��ȭ��Ű�� ������� ��ȯ���� �г�Ƽ 
		//=========================================================================

		SI32 siSkillModfier = 10;
		SI32 siCurrSummonKind  = pclchar->GetKind();
		if(pclKindInfoSet->IsValidKind(siCurrSummonKind) == true)
		{
			//cltKindInfo* pclki = pclKindInfoSet->pclKI[siCurrSummonKind];
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[siCurrSummonKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
			}

			if(pclki && pclki->bSummonMall == TRUE)
			{
				siSkillModfier = 10;
			}
			else if(pclki && summonlevel > pclki->siEvolveLevel &&
				pclKindInfoSet->IsSummonFromRank(pclki->siSummonRank+1) == true ) // ��ȭ�ñⰡ ������ 
			{
				if(summonlevel > pclki->siEvolveLevel * 2)			siSkillModfier = 30;
				else if(summonlevel > pclki->siEvolveLevel * 1.5)	siSkillModfier = 25;
				else												siSkillModfier = 20;
			}
		}

		pclParentChar->SetSkillUpdate(SKILL_SUMMON, siMyExp / siSkillModfier);	// �θ𿡰� ��ȯ�� ����ġ�� �߰��Ѵ�. 
		siMyExp += (siMyExp * skilllevel / 100);					// �θ��� ��ȯ�������� ���޴´�.

		//===========================================================
		// 10%�� Ȯ���� ������ ��ȯ�����Ե� ����ġ�� �Ȱ��� �ش�.
		//===========================================================
		if(siMyExp > 0 && rand()%10 == 0)
		{
			for(SI32 i = 0; i < MAX_SUMMON_OWN; ++i)
			{
				// ������ ��ȯ�����Ը� ����ġ�� �ش�.
				if(i != pclchar->GetSummonIndex())
				{
					cltSummon *pclSummon = pclParentChar->pclCI->clSummonInfo.GetSummon(i);
					if(pclSummon && pclSummon->siKind && pclSummon->siStatus != SUMMON_STATUS_DEAD )
					{
						pclSummon->clIP.IncreaseExp(siMyExp); 
						cltGameMsgResponse_Summon clInfo(pclParentChar->GetCharUnique(), i, pclSummon);
						cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
						pclParentChar->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}		
	}
	if(siMyExp > 0) pclchar->IncreaseExp(siMyExp);
}


void cltServer::PartyWarItemOperate(SI32 myid, SI32 enemyid, CPartyObj* pPartyObj)
{	//[����]

	WRITE_MEMLOG( 130, 4, 0, 0 );

	SI16 i=0, j=0;
	SI32 itemfrompos=0;
	cltItem clfromitem;

	if(pclCM->IsValidID(myid) == false) return;
	if(pclCM->IsValidID(enemyid) == false) return;

	// ��Ƽ�� ���ٸ� ������.
	if(pPartyObj == NULL) return;

	//  ��Ƽ�� �� PC�� ����ǰ�� ������ �� �ִ�. ( ��ȯ�����ٸ� ������ ���̵� ���ڷ� �޾ƿ��⶧����.
	if(IsPC(pclCM->CR[myid]->GetCharUnique()) == false )
	{
		return ;
	}

	// NPC������ �������� ���Ѵ´�. 
	if(IsPC(pclCM->CR[enemyid]->GetCharUnique()) )
		return ;

	// Clone�� �ƴ� �𿡰Լ��� �������� ���Ѵ´�.
	if(pclCM->CR[enemyid]->IsAtb(ATB_CLONE)&& pclCM->CR[enemyid]->clInnerStatus.IsStatus(INNERSTATUS_CLONE) == true)
		return;

	// �������� ������ �ϳ� ���´�
	if(pclCM->CR[enemyid]->pclCI->clCharItem.RobInv(&itemfrompos, &clfromitem) == true)
	{
		SI32 totalLuck = 0;
		SI32 totalBattlePower = 0;
		SI32 totalLevel = 0;
		SI32 partyindex = 0;
		SI32 partylist[MAX_PARTY_USER_NUM];

		for(i = 0;i < MAX_PARTY_USER_NUM;i++)
		{
			partylist[i] = 0;
		}
		//�������� �볪���� ��ȿ�� ��Ƽ���� CharUnique ����Ʈ�� ���Ѵ�. 
		stPartyUser* puser = NULL;
		for(i = 0;i < MAX_PARTY_USER_NUM;i++)
		{
			puser = pPartyObj->GetPartyUser(i);
			if(puser && puser->bPartyStatus == true)
			{
				if(pclCM->IsValidID(puser->siCharUnique) && pclCM->CR[puser->siCharUnique]->pclCI->GetPersonID() == puser->siPersonID)
				{
					// ���Ϳ� ���� ����, ���� �����ȿ� �־�� �Ѵ�. 
					if(pclCM->CR[enemyid]->GetMapIndex() == pclCM->CR[puser->siCharUnique]->GetMapIndex()
						&& max(TABS(pclCM->CR[enemyid]->GetX() - pclCM->CR[puser->siCharUnique]->GetX()), TABS(pclCM->CR[enemyid]->GetY() - pclCM->CR[puser->siCharUnique]->GetY())) < 30
						&& pclCM->IsAlive(puser->siCharUnique ))
					{
						partylist[partyindex] = puser->siCharUnique;
						partyindex++;
					}
				}
			}
		}	

		if(partyindex <= 0 || partyindex > MAX_PARTY_USER_NUM) return;


		for(i = 0;i < partyindex;i++)
		{
			// �� �հ踦 ���Ѵ�. 
			totalLuck += pclCM->CR[ partylist[i] ]->pclCI->clIP.siLuk;			
			// ������ �հ踦 ���Ѵ�.
			totalBattlePower += pclCM->CR[ partylist[i] ]->clPB.GetBattlePower();

			totalLevel += pclCM->CR[ partylist[i] ]->pclCI->clIP.GetLevel();
			/*
			for(j = 0 ; j < MAX_SUMMON_OWN ; j++  )
			{
				cltSummon* pclSummon = pclCM->CR[ partylist[i] ]->clSummonInfo.GetSummon(j) 
					if( pclSummon != NULL && pclSummon->siKind > 0 && pclSummon->siKind < MAX_KIND_NUMBER )
					{


					}
			}
			*/
		}		


		//�ش� �ʿ� �ִ� ��ȿ�� ��Ƽ����  Luk�������ͽ� ��� �����ؼ� �������� ������ +1 ��

		SI32 lukpercent = 0;
		SI32 maxlukpercent = (SI32)( totalLuck / partyindex *  0.1 / 3);

		if( maxlukpercent > 0) 
		{
			lukpercent = rand() % maxlukpercent + 1;

			if ( lukpercent > 15 )
				lukpercent = 15;

			if ( rand() % 100 + 1 <= lukpercent )
				clfromitem.siItemNum = clfromitem.siItemNum + 1;
		}




		// ������ ��տ� ���� ������ ���� ���Ƽ	

		// ���� �������� ���Ѵ�. 
		SI32 enemybattle	= pclCM->CR[enemyid]->clPB.GetBattlePower();
		// ��Ƽ�� ��� �������� ���Ѵ�. 
		SI32 attackerbattle	=  (SI32)( totalBattlePower / partyindex);
		// ��Ƽ�� ��� ������ ���Ѵ�.
		SI32 level = (SI32)(totalLevel / partyindex);



		// ������ ���̰� ���̳��� �����۰����� �����Ѵ�. 

		// ��� 30 �����϶��� ������ ����. 
		if( level > 30 )
		{
			SI32 percent = 0;

			if(attackerbattle > 0)
				percent = enemybattle * 100 / attackerbattle;
			else
				percent = 0;


			if(percent  < 40)		{	clfromitem.siItemNum = clfromitem.siItemNum - 3;	}

			else if( percent  < 70)	{	clfromitem.siItemNum = clfromitem.siItemNum - 2;	}


			if (clfromitem.siItemNum <= 0)
				clfromitem.siItemNum = 1;
		}

		// �����忡�� ����� ���̶��, 
		SI32 huntvillageunique	= pclCM->CR[myid]->GetHuntVillageUnique();
		GMONEY huntmoney			= 0;
		if(huntvillageunique)
		{
			if(rand() % 5 == 0)		// 20% Ȯ���� �����忡 �����Ѵ�. 
			{
				cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(clfromitem.siUnique);
				if(pclprice)
				{
					huntmoney = pclprice->siPrice * clfromitem.siItemNum;

					cltHunt* pclhunt = (cltHunt*)pclHuntManager->pclStruct[huntvillageunique];
					if(pclhunt)
					{
						pclhunt->clStrInfo.clHuntStrInfo.siTempMoney += huntmoney;
					}
				}
			}
		}

		// �ν��Ͻ� �������� ����Ѵٸ�
		GMONEY instancemoney = 0 ;
		SI32 mapindex = pclCM->CR[myid]->GetMapIndex();

		WRITE_MEMLOG( 130, 5, 0, 0 );

		// ��� ������ ������ �������� ����Ѵٸ�
		if( pclMapManager->IsGuildMap(mapindex)  )
		{
			cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(clfromitem.siUnique);
			if(pclprice)
			{
				GMONEY money = pclprice->siPrice * clfromitem.siItemNum;

				if ( money )	pclGuildDungeonMgr->AddMoney(mapindex, money);
			}
		}
		//------------------------------------------
		// ������, �δ��� ���޵� �������� �ƴϸ� ĳ���Ϳ��� �����Ѵ�. 
		//------------------------------------------
		if(huntmoney == 0 && instancemoney == 0) 
		{
			//�� ĳ���͸� �����Ѵ�

			SI32 waritemid = 0;
			SI32 getitemrate = 1000 ;

			// ��Ǿ� �ִ� ���¸� ���� ��ü���� ����ǰ�� �ش�. 
			if(pclCM->CR[enemyid]->clJim.siJimHostCharUnique)
			{
				SI32 jimid = pclCM->GetIDFromCharUnique( pclCM->CR[enemyid]->clJim.siJimHostCharUnique );
				if(jimid)// && pclCM->IsValidID(jimid))
				{
					if(pclCM->CR[jimid]->clJim.siJimSlaveCharUnique == pclCM->CR[enemyid]->GetCharUnique())
					{
						// �θ� �ִٸ� (jimid �� ��ȯ�����) //�Լ� ȣ������ ������ ���̵�� ���������� Ȥ�� �𸣴ϱ�!
						SI32 parentid = pclCM->CR[jimid]->GetSummonParentID();
						if(parentid)
						{
							SI32 levelgap = pclCM->CR[jimid]->pclKI->siSummonRank - pclCM->CR[enemyid]->pclKI->siSummonRank ;
							if ( pclCM->CR[enemyid]->pclKI->siSummonRank > 0 && levelgap > 17 &&
								pclCM->CR[jimid]->pclKI->bSummonMall != TRUE )
							{
								SI32 randrate = rand() % 1000 ;
								getitemrate = getitemrate - ( ( levelgap - 17 ) * 30 ) ;
								if ( randrate >= getitemrate )
								{
									return ;
								}
							}

							// �θ𿡰� ����ǰ�� �ش�. 
							waritemid = parentid;
						}
						// �÷��̾���
						else
						{
							// �ڽ��� ����ǰ�� ���´�. 
							waritemid = jimid;
						}
					}
				}
			}
			if(waritemid >0 )
			{	// ��Ƽ���߿� �Ѹ��� ���Ѱ����� üũ�Ͽ� ��� �����ϰ� ��Ƽ�� �꿡 ������.
				for(SI16 j = 0 ; j < partyindex; j++)
				{
					if( partylist[j] == waritemid )
					{
						waritemid = 0;
						break;
					}
				}
			}
			// ���Ѵ��� ������ ������ ȹ�� �꿡 ���� ��Ƽ������ ������.
			if(waritemid == 0 || pclCM->IsValidID(waritemid) == false)
			{			
				SI16 itemGetPattern = pPartyObj->GetItemGetPattern();
				if(itemGetPattern == ITEM_GETPATTERN_NORMAL)
				{
					return; // error
				}
				else if(itemGetPattern == ITEM_GETPATTERN_ROTATION)
				{
					WRITE_MEMLOG( 130, 7, 0, 0 );
					// ���ο��� waritemid �� �������� �������̶�� �����Ͽ� �������ʷ� ȹ������� �Ѿ�ִ�.
					waritemid =	pclCM->GetIDFromCharUnique(pPartyObj->GetItemGetCharUnique(partylist,partyindex));
					if(waritemid <= 0) 
						waritemid = myid;
				}
				else if(itemGetPattern == ITEM_GETPATTERN_FINISH)
				{
					WRITE_MEMLOG( 130, 8, 0, 0 );
					waritemid = myid;
				}
				else if(itemGetPattern == ITEM_GETPATTERN_RANDOM)
				{
					WRITE_MEMLOG( 130, 9, 0, 0 );
					SI32 rndPartyIndex = rand()%partyindex;	

					if(rndPartyIndex < 0 || rndPartyIndex >= partyindex)
						rndPartyIndex = 0;

					waritemid =  partylist[rndPartyIndex] ;	
				}
				else
				{
					return; // error
				}
			}			

			if(pclCM->IsValidID(waritemid) == false) return;

			// ��踦 ����. 
			//pclItemManager->AddWarItemNum(clfromitem.siUnique, clfromitem.siItemNum);

			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[waritemid];

			if(pclchar == NULL) return;

			// temp - ������ ��� �ι�
			// clfromitem.siItemNum *= 2;

			// �Ƿι��� �ý��� ����
			clfromitem.siItemNum = pclchar->CalcTiredPoint( clfromitem.siItemNum );

			if ( pclCM->CR[waritemid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF) )  // ����Ŭ�ι� ���¶�� - �������� 2��� �޴´�.
			{
				clfromitem.siItemNum = clfromitem.siItemNum * 2; // 2�踦 ���ش�.
			}

			if ( clfromitem.siItemNum > 0 )
			{

				InputItem(pclchar, &clfromitem, INPUTITEMPERSON_OPTION_WAR);

				// ��踦 ����. 
				pclItemManager->AddWarItemNum(clfromitem.siUnique, clfromitem.siItemNum);

				// ���ο� ��� - ����ǰ ������ ��踦 ����.
				NStatistics_Add("Item", clfromitem.siUnique, "MonNum", clfromitem.siItemNum);
				NStatistics_Set("Item", clfromitem.siUnique, "Name", pclItemManager->GetName(clfromitem.siUnique));
			}

			WRITE_MEMLOG( 130, 6, 0, 0 );
		}



	}// end if( npc ���׼� ������ �������� ���Դٸ�)

	//------------------------------------------------------
	// ���Ƽ��� �����Ǿ� �ִٸ�, ��ȯ������ ��´�. 
	//------------------------------------------------------
	// �������� �ƴϾ�� �Ѵ�. 
	if( pclMapManager->IsHuntMap(pclCM->CR[myid]->GetMapIndex()) == false )
	{
		// ���� ��ȯ�����
		SI32 parentid = pclCM->CR[myid]->GetSummonParentID();
		SI32 siID = myid ;
		if(pclCM->IsValidID(parentid))
		{
			siID = parentid ;
		}

		SI32 captureskilllevel	= pclCM->CR[siID]->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_CAPTURE, 0, 0,
			&pclCM->CR[siID]->pclCI->clCharItem.clItem[0]);
		if(captureskilllevel)
		{
			SI32 capturerate = pclCM->CR[enemyid]->pclKI->GetCaptureRate(captureskilllevel);
			if(rand() % 10000 < capturerate)
			{
				SI32 dollitemunique = 0;
				for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
				{
					if(pclItemManager->pclItemInfo[i] == NULL)continue;

					if(pclItemManager->pclItemInfo[i]->siMakeKind == pclCM->CR[enemyid]->GetKind())
					{
						dollitemunique = pclItemManager->pclItemInfo[i]->clItem.siUnique;
					}
				}

				if(dollitemunique)
				{
					// ��踦 ����. 
					cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];

					// �Ƿι��� �ý��� ����
					// test
					SI32 dollnum	= pclchar->CalcTiredPoint( CAPTURE_DOLLNUM ); 

					pclItemManager->AddWarItemNum(dollitemunique, dollnum);


					//cyj pclchar->GiveItem(dollitemunique, dollnum, INPUTITEMPERSON_OPTION_WAR/*INPUTITEMPERSON_OPTION_NONE*/,0);
					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(dollitemunique);
					UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
					pclchar->GiveItem(dollitemunique, dollnum, INPUTITEMPERSON_OPTION_WAR/*INPUTITEMPERSON_OPTION_NONE*/,usedate);

					SI32 skillunique	= SKILL_CAPTURE;
					SI32 maxskilllevel	= pclSkillManager->GetMaxLevel(skillunique);
					if(skillunique >= 0)
					{
						// ��� ����ġ���� ���Ѵ�. 
						SI32 skillexp = max(1, pclCM->CR[enemyid]->pclKI->Exp / 5);

						// �Ƿι��� �ý��� ����
						pclchar->CalcTiredPoint( skillexp );
						pclchar->SetSkillUpdate( skillunique, skillexp );
					}

				}
			}
		}
	}

	// �ν��Ͻ� ������ ���͸� ���δٸ�
	if( pclMapManager->IsInstanceMap(pclCM->CR[myid]->GetMapIndex()) == true )
	{
		SI32 mapindex = pclCM->CR[myid]->GetMapIndex() ;
	}
}


//myid�� enemyid�� �׿��� ��� �Ǵ� ����ǰ ó��. 
void cltServer::WarItemOperate(SI32 myid, SI32 enemyid) 
{
	SI32 i;

	SI32 itemfrompos;
	cltItem clfromitem;

	// PC, ��ȯ���� ����ǰ�� ������ �� �ִ�. 
	if(IsPC(pclCM->CR[myid]->GetCharUnique()) == false && pclCM->CR[myid]->GetSummonParentID() == 0)
	{
		return ;
	}

	// NPC������ �������� ���Ѵ´�. 
	if(IsPC(pclCM->CR[enemyid]->GetCharUnique()) )return ;

	// Clone�� �ƴ� �𿡰Լ��� �������� ���Ѵ´�.
	if(pclCM->CR[enemyid]->IsAtb(ATB_CLONE)&& pclCM->CR[enemyid]->clInnerStatus.IsStatus(INNERSTATUS_CLONE) == true) return;

	//[����] - 2010�ų��̺�Ʈ : ����� 1% Ȯ���� 1���� ������Ű ���� ȹ��
	((cltCharServer*)(pclCM->CR[myid]))->GiveFortuneCookiePiece(10, 1);
	
	
	// ����� ���� ����Ʈ �������� ȹ�� �մϴ�.
	((cltCharServer*)(pclCM->CR[myid]))->HuntQuestitem(myid, pclCM->CR[enemyid]->GetKind());

	if(pclCM->CR[enemyid]->pclCI->clCharItem.RobInv(&itemfrompos, &clfromitem) == true)
	{
		//=================================================================
		//cyj ��Ӿ����۰��� +1 �� Luk�������ͽ� ����
		//=================================================================
		//SI32 maxlukpercent = (SI32)(pclCM->CR[myid]->pclCI->clIP.GetLuk() *  0.1 / 3);
		SI32 maxlukpercent = (SI32)(pclCM->CR[myid]->clPB.clTotalBA.GetLuk() *  0.1 / 3);

		if( maxlukpercent > 0) 
		{
			SI32 lukpercent = rand() % maxlukpercent + 1;

			if (lukpercent > 15 )
				lukpercent = 15;

			if (rand() % 100 + 1 <= lukpercent )
				clfromitem.siItemNum = clfromitem.siItemNum + 1;
		}

		//--------------------------------------------------
		// ��ȣ ���ɿ� ���� ������ ����ټ� ����
		//--------------------------------------------------
		if ( IsCountrySwitch(Switch_SoulGuard) )
		{
			SI32 siAddItemNum = ((cltCharServer*)pclCM->CR[myid])->SoulGuardAbilityActivity( SOULGUARD_ABILITY_DROPITEM );
			if ( 0 < siAddItemNum )
			{
				clfromitem.siItemNum += siAddItemNum;
			}
		}

		// �����¿� ���� ������ ���� ���Ƽ

		// ���� �������� ���Ѵ�. 
		SI32 enemybattle	= pclCM->CR[enemyid]->clPB.GetBattlePower();

		// �������� �������� ���Ѵ�. 
		SI32 attackerbattle	= pclCM->CR[myid]->clPB.GetBattlePower();

		// ������̰� (��ȯ���� �̷� ������ ���� �ʴ´�.) 
		// �� ������ 30 �����϶��� ������ ����. 
		// ������ ���̰� ���̳��� �����۰����� �����Ѵ�. 
		if(IsPC(myid) && pclCM->CR[myid]->pclCI->clIP.GetLevel() > 30 && attackerbattle >= 0)
		{
			SI32 percent = 0;
			if(attackerbattle>0)	
				percent = enemybattle * 100 / attackerbattle;
			else					
				percent = 0;

			// 30%
			if( percent  < 40)	
			{
				clfromitem.siItemNum = clfromitem.siItemNum - 3;	
			}
			// 60%
			else if( percent  < 70)	
			{	
				clfromitem.siItemNum = clfromitem.siItemNum - 2;	
			}
		}

		if (clfromitem.siItemNum <= 0)
			clfromitem.siItemNum = 1;
		//=================================================================

		//-----------------------------------------
		// ����ǰ�� �� ĳ���͸� Ȯ���Ѵ�. 
		//-----------------------------------------
		SI32 waritemid = 0;
		SI32 getitemrate = 1000 ;

		// ��Ǿ� �ִ� ���¸� ���� ��ü���� ����ǰ�� �ش�. 
		if(pclCM->CR[enemyid]->clJim.siJimHostCharUnique)
		{
			SI32 jimid = pclCM->GetIDFromCharUnique( pclCM->CR[enemyid]->clJim.siJimHostCharUnique );
			if(jimid)
			{
				if(pclCM->CR[jimid]->clJim.siJimSlaveCharUnique == pclCM->CR[enemyid]->GetCharUnique())
				{
					// �θ� �ִٸ�(�ڽ��� ��ȯ�����) 
					SI32 parentid = pclCM->CR[jimid]->GetSummonParentID();
					if(parentid) 
					{
						cltKindInfo* pclKI	= NULL;
						if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
						{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclCM->CR[jimid]->GetKind() ];		}
						else
						{	pclKI = pclClient->pclKindInfoSet->pclKI[ pclCM->CR[jimid]->GetKind() ];				}

						SI32 levelgap = pclKI->siSummonRank - pclCM->CR[enemyid]->pclKI->siSummonRank ;
						if ( pclKI->siSummonRank > 0 && levelgap > 17 && pclKI->bSummonMall != TRUE )
						{
							SI32 randrate = rand() % 1000 ;
							getitemrate = getitemrate - ( ( levelgap - 17 ) * 30 ) ;
							if ( randrate >= getitemrate )
							{
								return ;
							}
						}

						// �θ𿡰� ����ǰ�� �ش�. 
						waritemid = parentid;
					}
					// �θ� ���� �����, 
					else
					{
						// �ڽ��� ����ǰ�� ���´�. 
						waritemid = jimid;
					}
				}
			}
		}

		// �ƴϸ� �����ڿ��� ����ǰ�� �ش�. 
		if(waritemid == 0)
		{
			//SI32  Lastattackid = pclCM->GetIDFromCharUnique (pclCM->CR[enemyid]->GetCharUnique());
			// ���� ���̵� ���Ѵ�.
			SI32 parentid = pclCM->CR[myid]->GetSummonParentID();// ���ξ��̵�
			if(parentid) 
			{
				waritemid = parentid;
			}
			else{
				waritemid = myid;
			}

		}

		// �����忡�� ����� ���̶��, 
		SI32 huntvillageunique	= pclCM->CR[myid]->GetHuntVillageUnique();
		GMONEY huntmoney			= 0;
		if(huntvillageunique)
		{
			if(rand() % 5 == 0)		// 20% Ȯ���� �����忡 �����Ѵ�. 
			{
				cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(clfromitem.siUnique);
				if(pclprice)
				{
					huntmoney = pclprice->siPrice * clfromitem.siItemNum;

					cltHunt* pclhunt = (cltHunt*)pclHuntManager->pclStruct[huntvillageunique];
					if(pclhunt)
					{
						pclhunt->clStrInfo.clHuntStrInfo.siTempMoney += huntmoney;
					}
				}
			}
		}


		// �ν��Ͻ� �������� ����Ѵٸ�
		GMONEY instancemoney = 0 ;
		SI32 mapindex = pclCM->CR[myid]->GetMapIndex();

		// ��� ������ ������ �������� ����Ѵٸ�
		if( pclMapManager->IsGuildMap(mapindex)  )
		{
			cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(clfromitem.siUnique);
			if(pclprice)
			{
				GMONEY money = pclprice->siPrice * clfromitem.siItemNum;

				if ( money )	pclGuildDungeonMgr->AddMoney(mapindex, money);
			}
		}

		//------------------------------------------
		// ������, �δ��� ���޵� �������� �ƴϸ� ĳ���Ϳ��� �����Ѵ�. 
		//------------------------------------------
		if(huntmoney == 0 && instancemoney == 0) 
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[waritemid];
			// ���� ����Ŭ�ι� �������̶�� ���� * 2, 0.01% Ȯ���� * 100

			SI32 siBonus = 1;

			//-----------------------------------------------------------
			if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FOURLEAF) == true )
			{
				SI32 randVal = TABS(pclClient->CurrentClock)%10000;

				if( randVal < 1 )
				{						
					cltServer* pclserver = (cltServer*)pclClient;
					if( pclserver->pclFourLeafManager->IsFourleafRareItem(clfromitem.siUnique) == true ) {
						//clfromitem.siItemNum *= 2;
						siBonus = 2;
					}
					else {
						//clfromitem.siItemNum *= 100;
						siBonus = 100;
					}
				}
				else
				{
					//clfromitem.siItemNum *= 2;
					siBonus = 2;
				}	
			}

			//[����] ���� �̺�Ʈ�� ����� ����Ⱓ�� �� ��Ÿ���� �ʿ����� ������ ������� 2���̴�. => 2008-7-2 
			if( IsCountrySwitch( Switch_Server_Event ) )
			{
				if(pclServerEventManager->IsEventMap(pclCM->CR[waritemid]->GetMapIndex()))
				{
					//1%Ȯ���� ������ ��������.
					if(1 > rand()%100)
					{
						clfromitem.Init();
						clfromitem.siUnique  = ITEMUNIQUE(2765);
						clfromitem.siItemNum = 1;

						// [�α��߰� : Ȳ���� 2008. 7. 7] ���� �̺�Ʈ
						// ����.
						cltServer * pclServer = (cltServer*)pclClient;
						pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_PREMIUM_GINSENG, 
							0, NULL, NULL, 0, 0, 0, &clfromitem, 0, 0, 0, 0, 0, 0, 
							0, 0, 0, 0, 0, NULL, NULL);

						pclClient->pclLog->FilePrint( "config\\ServerEvent.log" , "[GetItem]\t%s\tOneHundredGinseng", pclCM->CR[waritemid]->GetName());
					}
					// ������ �ƴϸ� 2��.
					else
					{
						clfromitem.siItemNum = clfromitem.siItemNum * 2; // 2�踦 ���ش�.
					}
				}
			}

			// [����] �߼� �̺�Ʈ. ��ɽ� �����䳢2 ���� �ֱ�. => 2008-8-11
			if( pclEventTimeManager->InEventTime(TEXT("Chuseok_Monster_Appear"), &sTime) )
			{
				//[����] �����䳢2�� ������ ������ ���� �ʴ´�. => 2008-9-3
				// PCK : ���� - �����䳢������� ĥ������������ ����Ѵ�.

				if(pclCM->CR[enemyid]->GetKind() != pclClient->GetUniqueFromHash(TEXT("KIND_TURKEY")))
				{
					//	ĥ���� ���� DropȮ�� 5% ->3%			
					if(3 > rand()%100)
					{
						clfromitem.Init();
						clfromitem.siUnique  = ITEMUNIQUE(12526);
						clfromitem.siItemNum = 1;

						pclClient->pclLog->FilePrint( "config\\ChuseokEvent.log" , "[ATTACK GiveItem] %s : KIND_TURKEY", pclCM->CR[waritemid]->GetName());
					}
				}

			}

			// [����] ���Һ� �̺�Ʈ
			if ( pclClient->IsCountrySwitch(Switch_BokBulBok))	// ���Һ� ����ġ
			{
				if ( IDENTITY_BOKBULBOK_ITEMMONSTER == pclCM->CR[enemyid]->clIdentity.siIdentity )
				{
					cltCharServer* pCharServer = pclCM->GetCharServer( enemyid );
					if ( NULL != pCharServer )
					{
						SI16 siItemUnique = 0;
						switch ( rand() % 4 )
						{
						case 0:
							siItemUnique = 3675;
							break;
						case 1:
							siItemUnique = 2006;
							break;
						case 2:
							siItemUnique = 5000;
							break;
						case 3:
							siItemUnique = 6105;
							break;
						}

						if ( 0 != siItemUnique && rand() % 10 == 0 )		// 10% Ȯ���� ������ �������� -�׽�Ʈ������ �Ϸ��� ������ �� 10�� 1��
						{
							clfromitem.Init();
							clfromitem.siUnique  = ITEMUNIQUE(siItemUnique);
							clfromitem.siItemNum = 1;
						}
					}
				}
			}

			// [����] �ҷ��� �̺�Ʈ ��� ���͸� ������� �д븦 5%Ȯ���� �ش�
			// PCK : �д� �� Ȯ�� 5% - > 3%���� ���� (09.08.06)
			if( pclEventTimeManager->InEventTime(TEXT("HalloweenEvent"), &sTime) )
			{
				if(3 > rand()%100)
				{
					clfromitem.Init();
					clfromitem.siUnique  = ITEMUNIQUE( 13049 ) ;
					clfromitem.siItemNum = 1;

					pclClient->pclLog->FilePrint( "config\\halloweenEvent.log" , "[ATTACK GiveItem] %s :  Trick_or_Treat_Candy", pclCM->CR[waritemid]->GetName());
				}
			}

			// [���] ���� �ູ ������ �ް� ������ 5%�� Ȯ���� ���� ��ɽ� ȣ�����ó��� ���Ÿ� ȹ���� �� �ִ�.
			if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_CHRISTMASEVENT_SNOWBLESS) == true)
			{
				if ( (rand()%100) < 20 )
				{
					clfromitem.Init();
					clfromitem.siUnique  = ITEMUNIQUE( 13060 ) ;
					clfromitem.siItemNum = 1;

					pclClient->pclLog->FilePrint( "config\\ChristmasEvent.log" , "[ATTACK GiveItem] %s : Fruit of holly  ", pclCM->CR[waritemid]->GetName());
				}
			}

			// �̰� ���� ������ - ������ 2�� ȹ��
			if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_REWARDBONUS) == true )
			{
				siBonus = 2;
			}

			// ���ֵ��� - ������ 2�� ȹ��
			if( pclEventTimeManager->InEventTime("GoonzuDay_HuntItem2_18", &sTime) )
			{
				cltEventTime* pclEventTime =  pclEventTimeManager->GetEvent("GoonzuDay_HuntItem2_18");
				if(pclEventTime)		{		siBonus = pclEventTime->m_siBonusAmount;		}
			}

			//-------------------------------------------------------------------------------------
			//	����ã�� �̺�Ʈ 
			//-------------------------------------------------------------------------------------
			// �ش� ����Ʈ�� �Ϸ� �߰ų� ����Ʈ ���� ���϶� �ȳ��´�
			// ���Ͱ� ������ 21Lev ���ϸ� �ȵȴ�.
			if ( pclClient->IsCountrySwitch(Switch_TreasureEvent)  )
			{
				if( pclEventTimeManager->InEventTime(TEXT("TreasureEvent"), &sTime) )
				{
					bool bQuestStatus_Going_Clear = pclCM->CR[myid]->pclCI->clQuestInfo.IsQuestClearOrGoing(QUEST_TYPE_FINDTREASURE)	;
					if ( false ==  bQuestStatus_Going_Clear )
					{
						SI32 siMonsterKind = pclKindInfoSet->FindKindFromName( (TCHAR*)pclCM->CR[enemyid]->GetName()	)	;

						SI32 siMonsterLevel = pclCM->GetChar(enemyid )->pclCI->clIP.GetLevel()	;

						SI32 siMyLevel = pclCM->CR[myid]->pclCI->clIP.GetLevel()	;

						SI32 siLevelGap = siMonsterLevel - siMyLevel;

						if( siLevelGap > -21 )
						{
							// 5% Ȯ���ξ������� �ش�.
							if ( rand()%20 == 7)
							{
								clfromitem.Init();
								clfromitem.siUnique  = ITEMUNIQUE(13058);	// �����ݴ� ����
								clfromitem.siItemNum = 1;

								pclClient->pclLog->FilePrint( "config\\TreasureEvent.log" , "[ATTACK GiveItem] %s : ", pclCM->CR[waritemid]->GetName());
							}
						}
					}
				}		 
			}		
			
			// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� ��Ÿ���� ���͸� ����ϸ� ���̾�Ʈ ���� ��Ȱ���� �ش�.
			if( IDENTITY_GIANTRACCOONRESURRECTEVENT == pclCM->CR[enemyid]->clIdentity.siIdentity )
			{
				clfromitem.Init();
				clfromitem.siUnique  = ITEMUNIQUE(13064);
				clfromitem.siItemNum = 1;
								
				pclClient->pclLog->FilePrint( "config\\GiantRaccoonResurrectEvent.log" , "[GiveItem] %s : ", pclItemManager->GetName( clfromitem.siUnique ) );
			}

			// ������ ���ʽ� ����
			clfromitem.siItemNum *= siBonus;

			// ��踦 ����. 
			clfromitem.siItemNum = pclchar->CalcTiredPoint( clfromitem.siItemNum );

			if ( clfromitem.siItemNum > 0 )
			{
				pclItemManager->AddWarItemNum(clfromitem.siUnique, clfromitem.siItemNum);

				// ���ο� ��� - ����ǰ ������ ��踦 ����.
				NStatistics_Add("Item", clfromitem.siUnique, "MonNum", clfromitem.siItemNum);
				NStatistics_Set("Item", clfromitem.siUnique, "Name", pclItemManager->GetName(clfromitem.siUnique));

				InputItem(pclchar, &clfromitem, INPUTITEMPERSON_OPTION_WAR);

				//[�߰� : Ȳ���� 2007. 11. 13 ��� ������ ���̸� ��� ������ ������ ����.]
				if(pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BIGRACCOON")))
				{
					TCHAR  buffer[MAX_MESSAGE_SIZE] = {'\0', };
					TCHAR* text					    = GetTxtFromMgr( 7610 );

					StringCchPrintf(buffer, sizeof(buffer), text, pclCM->CR[waritemid]->pclCI->clBI.clPerson.szName, pclItemManager->GetName(clfromitem.siUnique), clfromitem.siItemNum);

					cltGameMsgResponse_KingGuriInfo clKingGuriInfo(CKingGuriEvent::ITEM, buffer);
					cltMsg clMsg( GAMEMSG_RESPONSE_KINGGURIINFO, sizeof(clKingGuriInfo), (BYTE*)&clKingGuriInfo );

					SI32 index = 0;
					SI32 id	   = 0;
					while(id = pclClient->pclCM->GetCharOrder(index))
					{
						index++;

						// ������� �Ŀ��Ը� �����Ѵ�. 
						if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
						{
							pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}
				// [����] 2008.01.13 - ���� �̺�Ʈ �߰�
				else if ( pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_KITERACCOON") ) )
				{
					TCHAR tszName[MAX_PLAYER_NAME] = {'\0', };
					StringCchCopy( tszName, MAX_PLAYER_NAME, pclchar->GetName() );

					cltGameMsgResponse_KiteRaccoonInfo clKiteRaccoonInfo( cltEventTimeManager::KITERACCOON_EVENT_KILL, pclCM->CR[enemyid]->GetKind(), clfromitem.siUnique, tszName );
					cltMsg clMsg( GAMEMSG_RESPONSE_KITERACCOONINFO, sizeof(clKiteRaccoonInfo), (BYTE*)&clKiteRaccoonInfo );

					pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
				}
			}
		}
	}
	//------------------------------------------------------
	// ���Ƽ��� �����Ǿ� �ִٸ�, ��ȯ������ ��´�. 
	//------------------------------------------------------
	// �������� �ƴϾ�� �Ѵ�. 
	if( pclMapManager->IsHuntMap(pclCM->CR[myid]->GetMapIndex()) == false )
	{
		// ���� ��ȯ�����
		SI32 parentid = pclCM->CR[myid]->GetSummonParentID();
		SI32 siID = myid ;
		if(pclCM->IsValidID(parentid))
		{
			siID = parentid ;
		}

		SI32 captureskilllevel	= pclCM->CR[siID]->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_CAPTURE, 0, 0,
			&pclCM->CR[siID]->pclCI->clCharItem.clItem[0]);
		if(captureskilllevel)
		{
			SI32 capturerate = pclCM->CR[enemyid]->pclKI->GetCaptureRate(captureskilllevel);
			if(rand() % 10000 < capturerate)
			{
				SI32 dollitemunique = 0;
				for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
				{
					if(pclItemManager->pclItemInfo[i] == NULL)continue;

					if(pclItemManager->pclItemInfo[i]->siMakeKind == pclCM->CR[enemyid]->GetKind())
					{
						dollitemunique = pclItemManager->pclItemInfo[i]->clItem.siUnique;
					}
				}

				if(dollitemunique)
				{
					cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];

					// test
					SI32 dollnum	= pclchar->CalcTiredPoint( CAPTURE_DOLLNUM );

					// ��踦 ����. 
					pclItemManager->AddWarItemNum(dollitemunique, dollnum);


					//cyj pclchar->GiveItem(dollitemunique, dollnum, INPUTITEMPERSON_OPTION_WAR/*INPUTITEMPERSON_OPTION_NONE*/,0);
					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(dollitemunique);
					UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
					pclchar->GiveItem(dollitemunique, dollnum, INPUTITEMPERSON_OPTION_WAR/*INPUTITEMPERSON_OPTION_NONE*/,usedate);

					SI32 skillunique	= SKILL_CAPTURE;
					SI32 maxskilllevel	= pclSkillManager->GetMaxLevel(skillunique);
					if(skillunique >= 0)
					{
						// ��� ����ġ���� ���Ѵ�. 
						SI32 skillexp = max(1, pclCM->CR[enemyid]->pclKI->Exp / 5);

						// �Ƿι��� �ý��� ����
						pclchar->CalcTiredPoint( skillexp );
						pclchar->SetSkillUpdate(skillunique, skillexp);
					}

				}
			}
		}
	}

	// �ν��Ͻ� ������ ���͸� ���δٸ�
	if( pclMapManager->IsInstanceMap(pclCM->CR[myid]->GetMapIndex()) == true )
	{
		SI32 mapindex = pclCM->CR[myid]->GetMapIndex() ;
	}
}

// pvp-
SI32 cltServer::GetPVPWeaponDamage( SI32 RealDamage, SI32 AttackType )
{
	SI32 returnValue = 0;
	if( ATTACKTYPE_HAND == AttackType )
	{
		returnValue = RealDamage * siHandDamageRate / 100;
	}
	else if( ATTACKTYPE_SWORD == AttackType )
	{
		returnValue = RealDamage * siSwordDamageRate / 100;
	}
	else if( ATTACKTYPE_SPEAR == AttackType )
	{
		returnValue = RealDamage * siSpearDamageRate / 100;
	}
	else if( ATTACKTYPE_AXE == AttackType )
	{
		returnValue = RealDamage * siAxeDamageRate / 100;
	}
	else if( ATTACKTYPE_BOW == AttackType ||
		ATTACKTYPE_BOW1 == AttackType )
	{
		returnValue = RealDamage * siBowDamageRate / 100;
	}
	else if( ATTACKTYPE_GUN == AttackType ||
		ATTACKTYPE_GUN == AttackType )
	{
		returnValue = RealDamage * siGunDamageRate / 100;
	}
	else if( ATTACKTYPE_STAFF == AttackType ||
		ATTACKTYPE_STAFF1 == AttackType ||
		ATTACKTYPE_STAFF2 == AttackType )
	{
		returnValue = RealDamage * siStaffDamageRate / 100;
	}
	else
		returnValue = RealDamage;

	pclClient->pclLog->LogPrint(TEXT("AttackType : %d \n"), AttackType );

	return returnValue;
}


bool cltServer::NewYearEventDay(void)
{
	//[�߰� : Ȳ���� 2007. 12. 11 �ų��̺�Ʈ ������ ȹ�� ���� �Ⱓ.]
	SYSTEMTIME	StartTime;	ZeroMemory(&StartTime, sizeof(StartTime));
	SYSTEMTIME	EndTime;	ZeroMemory(&EndTime,   sizeof(EndTime));
	switch(pclClient->siServiceArea)
	{
	case ConstServiceArea_English:	
		{
			StartTime.wYear	 = 2008;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   11;		EndTime.wMonth	=	12;
			StartTime.wDay	 =   10;		EndTime.wDay	=   31;
			StartTime.wHour	 =    3;		EndTime.wHour	=    2;
		}
		break;
	case ConstServiceArea_Korea:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   27;		EndTime.wDay	=   10;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_Japan:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=   10;
			StartTime.wHour	 =    0;		EndTime.wHour	=   11;
		}
		break;
	case ConstServiceArea_Taiwan:	
	case ConstServiceArea_USA:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=    9;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_NHNChina:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   27;		EndTime.wDay	=    8;
			StartTime.wHour	 =    3;		EndTime.wHour	=    2;
		}
		break;
	case ConstServiceArea_EUROPE:	
		{
			StartTime.wYear	 = 2008;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   11;		EndTime.wMonth	=	12;
			StartTime.wDay	 =   10;		EndTime.wDay	=   31;
			StartTime.wHour	 =    3;		EndTime.wHour	=    2;
		}
		break;
	}

	SYSTEMTIME	CurTime;
	GetSystemTime(&CurTime);
	if(true == TimeInBounds(&CurTime, &StartTime, &EndTime))
	{
		return true;
	}

	return false;	
}

void cltServer::NewYearLuckyBox(cltItem& clfromitem)
{
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		const cltUniqueRange ItemUnique = { 13303, 1 };
		SI32 Unique = GetUniqueWithRange( &ItemUnique, sizeof(ItemUnique) / sizeof(cltUniqueRange), 300);

		if(0 != Unique)
		{
			ZeroMemory(&clfromitem, sizeof(clfromitem));

			clfromitem.siUnique  = Unique;
			clfromitem.siItemNum = 1;
		}
	}
	//if(true == NewYearEventDay())
	//{
	//	const cltUniqueRange ItemUnique = { 13303, 1 };
	//	SI32 Unique = GetUniqueWithRange( &ItemUnique, sizeof(ItemUnique) / sizeof(cltUniqueRange), 300);

	//	if(0 != Unique)
	//	{
	//		ZeroMemory(&clfromitem, sizeof(clfromitem));

	//		clfromitem.siUnique  = Unique;
	//		clfromitem.siItemNum = 1;
	//	}
	//}
}

void cltServer::SpecialDamage(SI32 myid, SI32 enemyid, SI32* psiRealDamage, SI32* psiDisplayDamage)
{
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];

	//--------------------------------------
	// GOD - ���� �������� �����鼭 ȭ�� ǥ�ô� �״�� 
	//--------------------------------------
	// �´³��� ����̰�  GOD ����� Damage = 0
	if( IsPC( pclCM->CR[enemyid]->GetCharUnique() ) && pclCM->CR[enemyid]->bGodMode == true )
	{
		*psiRealDamage    = 0;
		*psiDisplayDamage = *psiDisplayDamage;
	}

	//---------------------------------------
	// CLONE - ������ ��� �������� ���̱� ������ ǥ�ô� 0 damage�� ���� 
	//---------------------------------------
	if( pclenemychar->IsAtb(ATB_CLONE) && pclenemychar->clInnerStatus.IsStatus( INNERSTATUS_CLONE ) == true )
	{
		*psiRealDamage   = pclenemychar->GetLife();
		*psiDisplayDamage= 0;	// Damage�� �۰� ���̰� �Ѵ�.
	}
	//=================================================================

	//----------------------------------------------------------------------------
	// ������ �������� �ִ� ������� 1/3 �Ѵ�. [����]
	//----------------------------------------------------------------------------
	if(IsPC(pclCM->CR[myid]->GetCharUnique()) && IsPC(pclCM->CR[enemyid]->GetCharUnique()) )
	{
		if( pclVillageManager->IsVillageAtWar( pclCM->CR[myid]->pclCI->clBI.siHomeVillage ) 
			&& pclVillageManager->IsVillageAtWar( pclCM->CR[enemyid]->pclCI->clBI.siHomeVillage	) )
		{
			*psiRealDamage /=3;
			*psiRealDamage = max(1,*psiRealDamage);
		}
	}

	// ���ο� ����� �� ���� ������� ���� �������� �پ��� �ʴ´�.
	//if (IsCountrySwitch(Switch_NewGuildHuntMapWar) )
	//{
	//	//----------------------------------------------------------------------------
	//	// ������� �������� �ִ� ������� 1/5 �Ѵ�. [����]
	//	//----------------------------------------------------------------------------
	//	if(IsPC(pclCM->CR[myid]->GetCharUnique()) && IsPC(pclCM->CR[enemyid]->GetCharUnique()) )
	//	{
	//		SI32 myMapIndex = pclCM->CR[myid]->GetMapIndex();
	//		SI32 enemyMapIndex = pclCM->CR[enemyid]->GetMapIndex();
	//		if( IsCountrySwitch(Switch_NewGuildHuntMapWar ) )	// ���� ��
	//		{
	//			if ( IsGuildWarMap_NEW(myMapIndex) && IsGuildWarMap_NEW(enemyMapIndex)  )
	//			{
	//				SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

	//				if ( pclGuildHuntMapManager->IsGod(enemyPersonID ) )
	//				{
	//					*psiRealDamage = 0;
	//					*psiDisplayDamage = 0;
	//				}
	//			}
	//			else if ( IsGuildWarMap_Use_New_GuildWar(myMapIndex) && IsGuildWarMap_Use_New_GuildWar(enemyMapIndex) )
	//			{
	//				SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();
	//				if( IsCountrySwitch(Switch_NewGuildHuntMapWar ) )	// ���� ��
	//				{
	//					if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
	//					{
	//						*psiRealDamage = 0;
	//						*psiDisplayDamage = 0;
	//					}
	//					else
	//					{
	//						*psiRealDamage /= 5;
	//						*psiRealDamage = max(1,*psiRealDamage);

	//						*psiDisplayDamage /= 5;
	//						*psiDisplayDamage = max(1,*psiDisplayDamage);
	//					}

	//				}
	//				else	//������
	//				{
	//					if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
	//					{
	//						*psiRealDamage = 0;
	//						*psiDisplayDamage = 0;
	//					}
	//					else
	//					{
	//						*psiRealDamage /= 5;
	//						*psiRealDamage = max(1,*psiRealDamage);

	//						*psiDisplayDamage /= 5;
	//						*psiDisplayDamage = max(1,*psiDisplayDamage);
	//					}
	//				}


	//			}
	//		}
	//		else
	//		{
	//			if ( IsGuildWarMap_Not_Use_New_GuildWar(myMapIndex) && IsGuildWarMap_Not_Use_New_GuildWar(enemyMapIndex) )
	//			{
	//				SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();
	//				if( IsCountrySwitch(Switch_NewGuildHuntMapWar ) )	// ���� ��
	//				{
	//					if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
	//					{
	//						*psiRealDamage = 0;
	//						*psiDisplayDamage = 0;
	//					}
	//					else
	//					{
	//						*psiRealDamage /= 5;
	//						*psiRealDamage = max(1,*psiRealDamage);

	//						*psiDisplayDamage /= 5;
	//						*psiDisplayDamage = max(1,*psiDisplayDamage);
	//					}

	//				}
	//				else	//������
	//				{
	//					if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
	//					{
	//						*psiRealDamage = 0;
	//						*psiDisplayDamage = 0;
	//					}
	//					else
	//					{
	//						*psiRealDamage /= 5;
	//						*psiRealDamage = max(1,*psiRealDamage);

	//						*psiDisplayDamage /= 5;
	//						*psiDisplayDamage = max(1,*psiDisplayDamage);
	//					}
	//				}


	//			}

	//		}
	//	}
	//}
	//else	// ���� ������
	//{
	//	SI32 myMapIndex = pclCM->CR[myid]->GetMapIndex();
	//	SI32 enemyMapIndex = pclCM->CR[enemyid]->GetMapIndex();

	//	if ( IsGuildWarMap_NEW(myMapIndex) && IsGuildWarMap_NEW(enemyMapIndex)  )
	//	{
	//		SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

	//		if ( pclGuildHuntMapManager->IsGod(enemyPersonID ) )
	//		{
	//			*psiRealDamage = 0;
	//			*psiDisplayDamage = 0;
	//		}
	//	}// ���� ���̴ϱ� ��� �ʿ� ���� 
	//	else if(IsGuildWarMap_Not_Use_New_GuildWar(myMapIndex) && IsGuildWarMap_Not_Use_New_GuildWar(enemyMapIndex))
	//	{
	//		SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

	//		SI32 siindex = GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( enemyMapIndex )	;
	//		if ( pclGuildWarManager[siindex ]->IsGod( enemyPersonID ) )
	//		{
	//			*psiRealDamage = 0;
	//			*psiDisplayDamage = 0;
	//		}
	//	}
	//}
	if (IsCountrySwitch(Switch_NewGuildHuntMapWar) )
	{
		SI32 myMapIndex = pclCM->CR[myid]->GetMapIndex();
		SI32 enemyMapIndex = pclCM->CR[enemyid]->GetMapIndex();

		if ( IsGuildWarMap_NEW(myMapIndex) && IsGuildWarMap_NEW(enemyMapIndex)  )
		{
			SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

			if ( pclGuildHuntMapManager->IsGod(enemyPersonID ) )
			{
				*psiRealDamage = 0;
				*psiDisplayDamage = 0;
			}
		}
		else if(IsGuildWarMap_Use_New_GuildWar(myMapIndex) && IsGuildWarMap_Use_New_GuildWar(enemyMapIndex))
		{
			SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

			if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
			{
				*psiRealDamage = 0;
				*psiDisplayDamage = 0;
			}
		}

	}
	else
	{
		//----------------------------------------------------------------------------
		// ������� �������� �ִ� ������� 1/5 �Ѵ�. [����]
		//----------------------------------------------------------------------------
		if(IsPC(pclCM->CR[myid]->GetCharUnique()) && IsPC(pclCM->CR[enemyid]->GetCharUnique()) )
		{
			SI32 myMapIndex = pclCM->CR[myid]->GetMapIndex();
			SI32 enemyMapIndex = pclCM->CR[enemyid]->GetMapIndex();

			if ( IsGuildWarMap_Not_Use_New_GuildWar(myMapIndex) && IsGuildWarMap_Not_Use_New_GuildWar(enemyMapIndex) )
			{
				SI32 enemyPersonID = pclCM->CR[enemyid]->pclCI->GetPersonID();

				if ( pclGuildWarManager[GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( enemyMapIndex )]->IsGod( enemyPersonID ) )
				{
					*psiRealDamage = 0;
					*psiDisplayDamage = 0;
				}
				else
				{
					*psiRealDamage /= 5;
					*psiRealDamage = max(1,*psiRealDamage);

					*psiDisplayDamage /= 5;
					*psiDisplayDamage = max(1,*psiDisplayDamage);
				}
			}
		}
	}
	//----------------------------------------------------------------------------
	// PVP ������
	//----------------------------------------------------------------------------
	if(pclClient->siEnablePVP == 1)
	{
		if ( (IsPC(pclCM->CR[myid]->GetCharUnique())) && (IsPC(pclCM->CR[enemyid]->GetCharUnique())) )
		{
			if( pclMapManager->IsPkMap( pclCM->CR[myid]->GetMapIndex() ) )
			{
				if( pclMapManager->IsPkMap( pclCM->CR[enemyid]->GetMapIndex() ) )
				{
					if( pclCM->CR[myid]->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP )  ||
						pclCM->CR[enemyid]->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP ) ) 
					{		
						// �� ���⺰�� ������ ���Ұ� ����.
						*psiRealDamage = GetPVPWeaponDamage( *psiRealDamage, pclCM->CR[myid]->GetAttackType() );
						*psiRealDamage = max(1,*psiRealDamage);
						*psiDisplayDamage = *psiRealDamage;
					}
				}
			}	
		}
	}

	//----------------------------------------------------------------------------
	// ��ձ����� ����
	//----------------------------------------------------------------------------
	if( pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_RACCOONCHINA")) )
	{
		*psiRealDamage = 1 ;
		*psiDisplayDamage = 1 ;
	}

	//----------------------------------------------------------------------------
	//[�߰� : Ȳ���� 2007. 11. 13 ��ձ����� ���� ������]
	//----------------------------------------------------------------------------
	if( pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BIGRACCOON")) )
	{
		*psiRealDamage	  = 1;
		*psiDisplayDamage = 1;
	}

	//----------------------------------------------------------------------------
	// OneKill����� ���� �ѹ濡 ���δ�.
	//----------------------------------------------------------------------------
	if( pclCM->CR[myid]->bOneKill == true )
	{
		*psiRealDamage = pclenemychar->GetLife();
	}

	// PCK : ���ݷ¹������ �԰� ������ ��Ƽ��� ��ɽÿ� ���ݷ� 30%���� �ȴ�.
	if ( (pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BONETYRANNO"))) && IsPC(myid) )
	{
		cltBufInfo * pclAttackBuf = &pclCM->CR[ myid ]->pclCI->clBI.clBufInfo;
		if ( (pclAttackBuf) && (pclAttackBuf->IsHaveBuf(BUF_QUEST_ATTACK)) )
		{
			*psiRealDamage		= (*psiRealDamage * 130 )/100; 
			*psiDisplayDamage	= (*psiDisplayDamage * 130)/100;
		}
	}

	//[����] ���̾�Ʈ ���� ��Ȱ ���� �̺�Ʈ �����ؼ� ������ ���ʹ� �ѹ濡 �װ� �Ѵ�.
	if( IDENTITY_GIANTRACCOONRESURRECTEVENT == pclenemychar->clIdentity.siIdentity )
	{
		*psiRealDamage = pclenemychar->GetLife();
	}

	if (IsCountrySwitch(Switch_10MonthEvent_RacoonDodge) )
	{
		SI32 siMapindex = pclCM->CR[enemyid]->GetMapIndex()	;
		if ( siMapindex == PLAY_MAP_INDEX_INDODEVENT )
		{
			SI32 siMapindex = pclCM->CR[enemyid]->GetMapIndex()	;
			if ( siMapindex == PLAY_MAP_INDEX )
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCM->CR[enemyid]->GetX(), pclCM->CR[enemyid]->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						*psiRealDamage    = 10000;
						*psiDisplayDamage = 10000;
					}
				}
			}
		}
	}



}

void cltServer::DeadChar_PC(SI32 myid, SI32 enemyid)
{
	cltCharServer* pclchar		= (cltCharServer*)pclCM->CR[myid];		// ���γ�(������) 
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[enemyid];	// ������ 

	/// ������ �����ڿ��� ų���� �̸��� ����Ų��. 
	StringCchCopy(pclenemychar->szKillMeCharName, MAX_PLAYER_NAME, pclchar->GetName());

	if(!IsPC(pclCM->CR[myid]->GetCharUnique()))
	{
		// LEEKH MODIFY 2007.10.25 - ���Ϳ��Լ� ĳ���Ͱ� ���� ��Ȳ�� �α׷� �����
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ĳ���� ���. 
			// param1    == �ſ�.
			// param2	 == �� ĳ���Ͱ� � ���� �۵��ϴ°� ?(�ֱ�����, .. ) 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARDIE, 
				0, pclenemychar, NULL, 0, 0, 0, 0, 0, 0, pclchar->GetKind(), 0, 0, 0, 
				pclchar->clIdentity.siIdentity, pclchar->siCharMode, 0, 0, 0, NULL, NULL);
		}
	}

	//----------------------------------
	// �����ڰ� �Ұ��縮���, 
	//----------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_VILLAGEHUNT)
	{
		pclenemychar->siKilledMode = KILLEDMODE_VILLAGEHUNT;		// ��� ���Ƽ�� ������� �ʴ´�. 
	}

	//----------------------------------
	// [����] �����ڰ� ��Ʋ�ξ� �������� ĳ���� �� ���
	//----------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclenemychar);
		if( NULL != pclBattleRoyal)
		{
			if( pclenemychar->GetMapIndex() == pclBattleRoyal->GetStadiumMapIndex()
				&& pclchar->GetMapIndex() == pclBattleRoyal->GetStadiumMapIndex())
			{
				pclenemychar->siKilledMode = KILLEDMODE_BATTLEROYAL;
				if(pclchar->siCharMode == CHARMODE_BATTLEROYAL)
				{
					pclBattleRoyal->GiveItemToKiller(pclchar);
				}
			}
		}
	}
	//----------------------------------
	// �����ڰ� ���Ǳ��ܿ���(��ü����)
	//----------------------------------
	if( pclchar->siCharMode == CHARMODE_BLACKWAR )
	{
		pclenemychar->siKilledMode = KILLEDMODE_BLACKWAR;		// ��� ���Ƽ�� ������� �ʴ´�. 
		pclenemychar->siBlackWarKilledNumber++;
		//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ���� �Ŀ��� �ο��� ������ �ִ� ���Ƽ�� �������� �ʴ´�.]
		if(pclClient->IsCountrySwitch(Switch_BlackWarReform)											&&
			( BLACKARMY_MAP_STARTINDEX > pclenemychar->GetCurrentVillageUnique()						||
			BLACKARMY_MAP_STARTINDEX+MAX_BLACKARMY_MAP_CNT < pclenemychar->GetCurrentVillageUnique())			)
		{

		}
		else
		{
			if (pclenemychar->siBlackWarEnemyKillNumber >= 2)
				pclenemychar->siBlackWarEnemyKillNumber -= 2;
			else
				pclenemychar->siBlackWarEnemyKillNumber = 0;

			//--------------------------------
			// Ŭ���̾�Ʈ�� ������ �˷��ش�. 
			//--------------------------------
			cltGameMsgResponse_WarKill clinfo( 0, pclenemychar->siBlackWarEnemyKillNumber, pclenemychar->siBlackWarKilledNumber, 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_WARKILL, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[pclenemychar->GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//----------------------------------
	// �����ڰ� ���� �����̸�(�̺�Ʈ����)
	//----------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_BLACKARMY)
	{
		pclenemychar->siKilledMode = KILLEDMODE_BLACKARMY;		// ��� ���Ƽ�� ������� �ʴ´�. 
		pclenemychar->siWarKilledNumber++;
		if (pclenemychar->siWarEnemyKillNumber >= 2)
			pclenemychar->siWarEnemyKillNumber = pclenemychar->siWarEnemyKillNumber - 2;
		else
			pclenemychar->siWarEnemyKillNumber = 0;

		//--------------------------------
		// Ŭ���̾�Ʈ�� ������ �˷��ش�. 
		//--------------------------------
		cltGameMsgResponse_WarKill clinfo(1, pclenemychar->siWarEnemyKillNumber, pclenemychar->siWarKilledNumber, pclenemychar->siBlackArmyWarMapIndex);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARKILL, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[pclenemychar->GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
	}


	//----------------------------------
	// �����ڰ� ���ĸ��� �̺�Ʈ �����̸�
	//----------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_MOFUMOFUEVENT)
	{
		pclenemychar->siKilledMode = KILLEDMODE_MOFUMOFUEVENT;		// ��� ���Ƽ�� ������� �ʴ´�. 
	}

	//-----------------------------
	// �ν��Ͻ� �������� ���
	//----------------------------
	if( pclClient->pclMapManager->IsInstanceMap( pclenemychar->GetMapIndex() ) )
	{
		pclenemychar->siKilledMode = KILLEDMODE_INSTANCEMAP;
	}

	//-----------------------------
	// ���縮������ ��Ȱ���Ѿ� �Ұ��, ���⼭ �����Ѵ�.
	//KHY - 1113 - ũ�������� �̺�Ʈ - ��Ÿ �۾��忡�� �����.
	//----------------------------
	if(pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_1  ||
		pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_2  ||
		pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_3  ||
		pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_1_2||
		pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_2_2||
		pclenemychar->GetMapIndex()  == MAPINDEX_SANTAFACTORY_3_2)
	{
		pclenemychar->siKilledMode = KILLEDMODE_GOTOSAFEZONE;
	}


	//--------------------------------
	// �������� ��� ����
	//--------------------------------
	// ���� ���γ��� ���� �������� ������, 
	if( bVillageWarSwitch && ( pclchar->clInnerStatus.clEnemyType.siEnemyType & ENEMYTYPE_VILLAGE))
	{
		pclenemychar->siKilledMode = KILLEDMODE_VILLAGEWAR;	// ������ �� ���. 

		SI32 levelGep = pclchar->pclCI->clIP.GetLevel() - pclenemychar->pclCI->clIP.GetLevel();


		// ���� ������ 11���� �̻� ���ٸ� 10 ����Ʈ ����
		if( levelGep < -10  )
			pclchar->siVillageWarKillScore += 10;
		else if( levelGep > 10)	//���� ������ 11���� ���� ���ٸ�
			pclchar->siVillageWarKillScore += 1;
		else
			pclchar->siVillageWarKillScore += 5;

		// LEEKH MODIFY 2007.10.25 - ������ �� ��� �α�
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ĳ���� ���. 
			// param1 == ���γ��� ���� ����ũ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARLDIE_VILLAGEWAR, 
				0, pclenemychar, NULL, pclchar->pclCI->GetPersonID(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 
				pclchar->pclCI->clBI.siHomeVillage, 0, 0, 0, 0, NULL, NULL);
		}
	}

	//-----------------------------
	// ������� ��� ����
	//----------------------------
	SI32 fieldindex = 0 ;
	if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar ))	// ������
	{
		fieldindex = GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( pclchar->GetMapIndex() );
	}
	else	// ������ 
	{
		fieldindex = GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( pclchar->GetMapIndex() );
	}
	//������
	if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar ))
	{
		if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM_OLD )
		{
			pclGuildWarManager[fieldindex]->AddKillPoint( pclchar->pclCI->GetPersonID() );
			// LEEKH MODIFY 2007.10.25 -  ����� �� ����α�
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 15] // ĳ���� ���. 
				// param1 == ���γ��� �Ҽ� ��� �ε��� �߰�
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARLDIE_GUILDWAR, 
					0, pclenemychar, NULL, pclchar->pclCI->GetPersonID(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex, 0, 0, 0, 0, NULL, NULL);
			}	
		}
	}
	//������
	else
	{
		if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM)
		{
			pclGuildWarManager[fieldindex]->AddKillPoint( pclchar->pclCI->GetPersonID() );
			// LEEKH MODIFY 2007.10.25 -  ����� �� ����α�
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 15] // ĳ���� ���. 
				// param1 == ���γ��� �Ҽ� ��� �ε��� �߰�
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARLDIE_GUILDWAR, 
					0, pclenemychar, NULL, pclchar->pclCI->GetPersonID(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex, 0, 0, 0, 0, NULL, NULL);
			}	
		}
	}

	// ���� ȹ���� ���� �����
	SI32 siMapIndex = GetHuntmapGuildWarFieldIndexFromMapIndex( pclchar->GetMapIndex() );
	if ( siMapIndex >= 0 && siMapIndex < GUILDWAR_FIELDNUM )
	{
		pclGuildHuntMapManager->addKillPoint(myid,enemyid);
	}

	//-----------------------------
	// PVP �� ���
	//----------------------------
	if(siEnablePVP == 1)
	{
		if( IsPC( pclchar->GetCharUnique() ) )
		{
			if( pclchar->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP  ) )
			{
				if( pclMapManager->IsPkMap( pclchar->GetMapIndex() ) )
				{
					if( pclenemychar->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP ) )
					{
						if( pclMapManager->IsPkMap( pclenemychar->GetMapIndex() ) )
						{	
							// �������� ���� ����� �÷�����, �׸��� PVP���¸� ��������
							if( 1 == siLoseItem )
							{
								// �������� ���� ����� �÷�����, �׸��� PVP���¸� ��������
								SI32 sendItemPosition = -1;
								SI32 randValue = rand() % 100;

								if ( IsCountrySwitch( Switch_PKHuntMap_Change_Info )) 
								{
									// �ູ���� ��Ȱ���� ������ �������� ������ �ʴ´� 
									if( pclenemychar->pclCI->clCharItem.GetItemNum( ITEMUNIQUE(2731 ) ) > 0 )
									{
									}
									else
									{
										if		( 1 > randValue )	{		sendItemPosition = PERSONITEM_WEAPON1;			}
										else if	( 2 > randValue )	{		sendItemPosition = PERSONITEM_WEAPON2;			}
										else if ( 7 > randValue )	{		sendItemPosition = PERSONITEM_HELMET;			}
										else if ( 12 > randValue )	{		sendItemPosition = PERSONITEM_ARMOUR;			}
										else if ( 31 > randValue )	{		sendItemPosition = PERSONITEM_BELT;				}
										else if ( 50 > randValue )	{		sendItemPosition = PERSONITEM_SHOES;			}
										else								sendItemPosition = -1;

										if( -1 != sendItemPosition )
										{
											if( 0 >= pclenemychar->pclCI->clCharItem.clItem[sendItemPosition].siUnique )
											{
												sendItemPosition = -1;
											}
										}

										if( -1 < sendItemPosition )
										{
											cltItem clItem;
											clItem.Init();

											SI32 rtnvalue = -1;
											SI16 findIndex = -1;
											if ( true == pclchar->CanAddInv( INVMODE_ALL, &pclenemychar->pclCI->clCharItem.clItem[sendItemPosition], &findIndex, &clItem, &rtnvalue ) )
											{
												bool destoryItem = false;
												SI32 destoryValue = rand() % 100;

												if( 20 > destoryValue )
												{

													destoryItem = true;
												}

												sDBRequest_MoveItemPerson clMsg( pclchar->GetID(), pclenemychar->pclCI->GetPersonID(), 
													sendItemPosition, &pclenemychar->pclCI->clCharItem.clItem[sendItemPosition],
													false, (TCHAR*)pclenemychar->GetName(), pclchar->pclCI->GetPersonID(), findIndex, &clItem, (TCHAR*)pclchar->GetName(), 
													MOVEITEMPERSON_PVP, destoryItem );

												pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

											}
										}

									}
								}
								else
								{
									if		( 5 > randValue )	{		sendItemPosition = PERSONITEM_WEAPON1;			}
									else if	( 10 > randValue )	{		sendItemPosition = PERSONITEM_WEAPON2;			}
									else if ( 15 > randValue )	{		sendItemPosition = PERSONITEM_HELMET;			}
									else if ( 20 > randValue )	{		sendItemPosition = PERSONITEM_ARMOUR;			}
									else if ( 45 > randValue )	{		sendItemPosition = PERSONITEM_BELT;				}
									else if ( 70 > randValue )	{		sendItemPosition = PERSONITEM_SHOES;			}
									else								sendItemPosition = -1;

									if( -1 != sendItemPosition )
									{
										if( 0 >= pclenemychar->pclCI->clCharItem.clItem[sendItemPosition].siUnique )
										{
											sendItemPosition = -1;
										}
									}

									if( -1 < sendItemPosition )
									{
										cltItem clItem;
										clItem.Init();

										SI32 rtnvalue = -1;
										SI16 findIndex = -1;
										if ( true == pclchar->CanAddInv( INVMODE_ALL, &pclenemychar->pclCI->clCharItem.clItem[sendItemPosition], &findIndex, &clItem, &rtnvalue ) )
										{
											bool destoryItem = false;
											SI32 destoryValue = rand() % 100;

											if( 20 > destoryValue )
											{

												destoryItem = true;
											}

											sDBRequest_MoveItemPerson clMsg( pclchar->GetID(), pclenemychar->pclCI->GetPersonID(), 
												sendItemPosition, &pclenemychar->pclCI->clCharItem.clItem[sendItemPosition],
												false, (TCHAR*)pclenemychar->GetName(), pclchar->pclCI->GetPersonID(), findIndex, &clItem, (TCHAR*)pclchar->GetName(), 
												MOVEITEMPERSON_PVP, destoryItem );

											pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

										}
									}


								}
							}

							//[����] pk��� ����. => 2008-5-9
							sDBRequest_PVPResult clMsg( pclchar->GetID(), pclenemychar->GetID(), pclchar->pclCI->GetPersonID(), pclenemychar->pclCI->GetPersonID(), (TCHAR*)pclchar->GetName(), (TCHAR*)pclenemychar->GetName() );
							pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

							pclenemychar->siKilledMode = KILLEDMODE_PVP;

							pclchar->clInnerStatus.clEnemyType.siEnemyType = ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR;
							pclenemychar->clInnerStatus.clEnemyType.siEnemyType = ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR;

							// LEEKH MODIFY 2007.10.25
							if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
							{
								// [�α��߰� : Ȳ���� 2007. 9. 11] // ĳ���� ��� (pk)
								SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARLPK, 
									0, pclenemychar, NULL, pclchar->pclCI->GetPersonID(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 
									0, 0, 0, 0, 0, NULL, NULL);
							}
						}
					}
				}
			}
		}
	}
	//-----------------------------
	// 1:1 Pvp�� ���
	//-----------------------------
	{
		SI32 siMyParent		=	pclchar->GetSummonParentID()		;
		SI32 siEnemyParent	=	pclenemychar->GetSummonParentID()	;

		// siMyParent �� ������ ��ȯ���� ���ΰŴ�
		if ( siMyParent == 0 )		siMyParent		=	myid		;
		if ( siEnemyParent == 0 )	siEnemyParent	=	enemyid		;

		cltCharServer* pclMyChar = pclCM->GetCharServer( siMyParent )		;		if(pclMyChar == NULL)		return;
		cltCharServer* pclEnemyChar = pclCM->GetCharServer( siEnemyParent )	;		if(pclEnemyChar == NULL)	return;

		// ������ pvp���� �Ἥ �ϳ��� ������ ���� �۽����̵� �ִ��� �������� üũ [ ����] 2008.11.23
		if ( pclCM->CR[siMyParent]->siEnemUnique > 0 &&  pclCM->CR[siMyParent]->GetPVP_LeagueEnemyPersonID() <= 0) 
		{
			pclenemychar->siKilledMode = KILLEDMODE_PVP;

			// �׾��� �� ���� EnemyID�� �ʱ�ȭ �Ѵ�.
			// Ŭ���̾�Ʈ�� �������� �˸��� Ŭ���̾�Ʈ�� enemyID�� �ʱ�ȭ �Ѵ�.
			if( pclClient->IsCountrySwitch( Switch_ValenTineWar ) )
			{
				//�߷�Ÿ�ε��� ���� ���� üũ, Ŀ���̳� �ַζ�� ���߰�, �������� ���� �ʾ��� ��쿡�� �ش�.
				SI32 siCouple = pclMyChar->pclValentineWar->GetCouple()	;// �̱� ����� Ŀ�� ����
				SI32 siLoser = pclEnemyChar->pclValentineWar->GetCouple()	;// �� ����� Ŀ�� ����
				bool bGetPrize = pclMyChar->pclValentineWar->GetPrize()	;	// �̱����� �������� �޾Ҿ�����

				if( abs(pclMyChar->pclCI->clIP.GetLevel() - pclenemychar->pclCI->clIP.GetLevel() ) < 11
					&& siCouple != 0 && siLoser != 0
					&& siCouple != siLoser 
					&& bGetPrize == false )
				{
					SI32 siRewardItemUnique	=	ITEMUNIQUE(2781) ;
					if( siRewardItemUnique ) 
					{
						cltItem clItem;
						SI16 brareswitch = 0;
						if ( pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique,&clItem,0,0,&brareswitch,0,0,0,0,0) == true ) 
						{
							clItem.siItemNum = 1;
							SI32 rtnvalue = 0;
							if(pclMyChar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, &rtnvalue))
							{
								// �������� �ְ� ��ٰ� ���� ���ش�.
								sDBRequest_Valantine_Get_Prize clMsg( pclMyChar->pclCI->GetPersonID(), true );
								pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
							}
							else
							{
								if(rtnvalue == CANADDINV_FAIL_FULL)
								{
									sDBRequest_PostOfficeMasterSendItem clMsg( INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, 0, (TCHAR*)pclMyChar->GetName(), &clItem, &pclTime->clDate );
									pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
									// �������� �ְ� ��ٰ� ���� ���ش�.
									sDBRequest_Valantine_Get_Prize clMsg2( pclMyChar->pclCI->GetPersonID(), true );
									pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
								}
							}
						}		
					}
				}
			}
			{//�¸���
				// ���ΰ� pvp�� �����鼭 ���� �ߵ����� ����
				pclMyChar->DeletePoison();						// �ߵ� ���¸� �����Ѵ�.
				pclMyChar->DeletePoisonSetItemEffect();			// �ߵ� ���¸� �����Ѵ�.
				
				pclMyChar->DeleteIce();							// ���� ���¸� �����Ѵ�.
				pclMyChar->DeleteCurseAttack();					// ���ݷ��� ���� ���¸� �����Ѵ�.
				pclMyChar->DeleteCurseCritical();				// Critical Ȯ���� �������� ���¸� �����Ѵ�.
				pclMyChar->DeleteCurseDefense();				// ������ �������� ���¸� �����Ѵ�.
				pclMyChar->DeleteCurseMovespeed();				// �̵��ӵ� ���� ���¸� �����Ѵ�.
				pclMyChar->DeleteMagicFire();					// �ҿ� Ÿ�� ���¸� �����Ѵ�.
				pclMyChar->DeleteFrozen();						// ���� ���� ���¸� �����Ѵ�.
				pclMyChar->DeleteCurseEffect();
			}
			{	// �й���
				// ���ΰ� pvp�� �����鼭 ���� �ߵ����� ����
				pclEnemyChar->DeletePoison();					// �ߵ� ���¸� �����Ѵ�.
				pclEnemyChar->DeletePoisonSetItemEffect();		// �ߵ� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteIce();						// ���� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteCurseAttack();				// ���ݷ��� ���� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteCurseCritical();			// Critical Ȯ���� �������� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteCurseDefense();				// ������ �������� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteCurseMovespeed();			// �̵��ӵ� ���� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteMagicFire();				// �ҿ� Ÿ�� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteFrozen();					// ���� ���� ���¸� �����Ѵ�.
				pclEnemyChar->DeleteCurseEffect();
			}
			pclCM->CR[ siMyParent ]->siEnemUnique		=	0 ;
			pclCM->CR[ siEnemyParent ]->siEnemUnique	=	-100 ;

			// ������ �������� �˷��ش�.
			cltGameMsgResponse_PVP_Request clMe( END_PVP ,WIN_PVP, pclMyChar->GetCharUnique(), TEXT("") );  //  ���� �׿���
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clMe), (BYTE*)&clMe );
			pclMyChar->SendNeighbourMsg(&clMsg, true);

			pclMyChar->IncQuestPara( QUEST_CLEAR_COND_PVPWIN, 0, 1 );

			// ���濡�� �������� �˷��ش�.
			cltGameMsgResponse_PVP_Request clEnemy( END_PVP , LOSE_PVP, pclEnemyChar->GetCharUnique(), TEXT("") ); // �����Դ� �� ���ٰ� �˸���.
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clEnemy), (BYTE*)&clEnemy );
			pclEnemyChar->SendNeighbourMsg(&clMsg2, true);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : �ռ����� 2008. 10. 29] // pvp �й�
				// para1	:	�¸��� personID // ���γ�
				// para2	:	�й��� personID	// ������
				// PCK : ���� - PersonID�� ĳ�����̸��� ���ؼ� ���� ���� �����Ѵ�. (09.07.31)

				TCHAR szCharName[100];
				ZeroMemory(szCharName, sizeof(szCharName));
				StringCchPrintf(szCharName, sizeof(szCharName), TEXT("WinnerChar:%s, LoserChar:%s"), pclMyChar->GetName(), pclEnemyChar->GetName());

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_END_DIE, 
					0,pclMyChar,NULL , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					pclMyChar->pclCI->GetPersonID(), 
					pclEnemyChar->pclCI->GetPersonID(), 0, 0, 0, szCharName, NULL);
			}
			{
				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime,  sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPEND_DIE \tWINOPERSON : \t[%s]\t \t LOSEPERSON2 : \t[%s]\t Time"),
					pclMyChar->GetName(),pclEnemyChar->GetName(),szBuffer0 );
			}
		}
	}
	//-----------------------------
	// PVP_League ���� ���.
	//-----------------------------
	{
		SI32 siWinParent		=	pclchar->GetSummonParentID()	;
		SI32 siLoseParent		=	pclenemychar->GetSummonParentID()	;

		// siMyParent �� ������ ��ȯ���� ���ΰŴ�
		if ( siWinParent == 0 )		siWinParent		=	myid		;// �¸� �ѻ��
		if ( siLoseParent == 0 )	siLoseParent	=	enemyid		;	// �������

		cltCharServer* pclWinnerChar = pclCM->GetCharServer( siWinParent )		;		if(pclWinnerChar == NULL)		return;
		cltCharServer* pclLoseChar = pclCM->GetCharServer( siLoseParent )	;		if(pclLoseChar == NULL)	return;

		if ( pclWinnerChar->GetPVP_LeagueEnemyPersonID() > 0 && pclWinnerChar->siEnemUnique > 0 &&
			pclLoseChar->GetPVP_LeagueEnemyPersonID() > 0 && pclLoseChar->siEnemUnique > 0) // ���Ѵ���
		{	
			pclLoseChar->siKilledMode = KILLEDMODE_PVP	;
		}
	}
}

void cltServer::DeadChar_NPC(SI32 myid, SI32 enemyid)
{
	// �������� óġ�� ���̶�� , 
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[enemyid];	// ������. 
	cltCharServer* pclenemychar = (cltCharServer*)pclCM->CR[myid];	// ���γ�. (������)  

	pclchar->m_clCharCurseEffect.Dead( enemyid );

	//////////////////////////////////////////////////////////////////////////
	// [����] ��Ʋ�ξ� ���� �׾��� ��
	if(pclchar->clIdentity.siIdentity == IDENTITY_BATTLEROYAL_MONSTER)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclenemychar);
		if( NULL != pclBattleRoyal)
			pclBattleRoyal->DieMob();
	}

	//////////////////////////////////////////////////////////////////////////
	// [����] ���Һ� �̺�Ʈ ���� �׿�����
	if ( pclClient->IsCountrySwitch(Switch_BokBulBok))	// ���Һ� ����ġ
	{
		if ( pclenemychar != NULL )
		{
			if ( pclchar->clIdentity.siIdentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
			{
				cltCharServer* pclChar = pclCM->GetCharServer( myid );

				if ( pclChar != NULL )
				{
					pclClient->m_pServer_BBBMgr->StageFail( myid );
				}
			}
		}
	}

	if ( pclClient->IsCountrySwitch(Switch_BokBulBok))	// ���Һ� ����ġ
	{
		if ( pclenemychar != NULL )
		{
			if ( pclchar->clIdentity.siIdentity == IDENTITY_BOKBULBOK_KEYMONSTER )
			{
				cltCharServer* pclChar = pclCM->GetCharServer( myid );

				if ( pclChar != NULL )
				{
					pclClient->m_pServer_BBBMgr->StageClear( myid );
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////


	//[����] ���� �̺�Ʈ-���� ���� ���̸�.
	if(pclMonsterAttackEvent->IsEvent())
	{
		if(pclchar->clIdentity.siIdentity == IDENTITY_MONSTER_ATTACK_EVENT )
		{
			pclMonsterAttackEvent->MonsterDie(pclchar->GetKind());
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// �������� ��ȣ���� ������
	//--------------------------------------------------------------------------------------------------------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_VILLAGE_KINGMONUMENT)
	{
		// ���� ���� 
		if(pclenemychar->pclCI->clBI.siHomeVillage)
		{
			// ���� ��������� 
			if(pclVillageManager->IsAggressiveVillage( pclchar->pclCI->clBI.siHomeVillage, pclenemychar->pclCI->clBI.siHomeVillage))
			{
				// �¸� ���� ����鿡�� ����ġ�� �����Ѵ�. 
				// �̱� ������ ���� �����̶�� ����ġ�� ���� �ְ� ���� �����̶�� ����ġ�� ���� �ش�. 
				SI32 rate = 0;
				SI32 expreason	= 0;

				/* ���� [������] ���� ��,���� �ý��� ����
				if(pclVillageManager->GetVillageRelation(pclenemychar->pclCI->clBI.siHomeVillage, pclchar->pclCI->clBI.siHomeVillage) == TRUE)
				{
					rate = 100;
					expreason	= GETEXP_REASON_VILLAGEWAR2;	//���� ���� ����
				}
				else
				{
					rate = 300;
					expreason	= GETEXP_REASON_VILLAGEWAR1;	//�������� ����. 
				}*/

					// ���� �ǰ�������� ���� * 100 �� ����ġ�� ��.

					rate = 100;
				expreason	= GETEXP_REASON_VILLAGEWAR2;	//���� ���� ����


				SI32 index	= 0;
				SI32 id		= 0;
				while(id = pclCM->GetCharOrder(index))
				{
					index++;

					if(pclCM->IsAlive(id) && IsPC(pclCM->CR[id]->GetCharUnique())
						&& pclCM->CR[id]->pclCI->clBI.siHomeVillage == pclenemychar->pclCI->clBI.siHomeVillage)
					{
						SI32 tempexp = pclCM->CR[id]->pclCI->clIP.GetLevel() * rate;

						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
						pclchar->IncreaseExp(tempexp, expreason);
					}
				}

				// ���и� �����ϰ� ��������, �ڻ� �� ������ ����Ͽ� ���Ѿ� �´�.
				// �й��� ������ ��� �й��� ��¥�� DB�� ����Ͽ� �д�. (�����Ⱓ ��ȣ�� ����)

				SetWarResult(pclenemychar->pclCI->clBI.siHomeVillage, pclchar->pclCI->clBI.siHomeVillage);

				// ���� ����� Log�� �����. 
				pclLog->FilePrint(TEXT("config\\VillageWar.log"), TEXT("Win :\t[%s]\tLose :\t[%s]"),
					pclVillageManager->GetName(pclenemychar->pclCI->clBI.siHomeVillage),
					pclVillageManager->GetName(pclchar->pclCI->clBI.siHomeVillage));

				// ���п� ���� �ֽ��� �Ұ��Ѵ�.
				//SetVillageWarLoss(pclenemychar->pclCI->clBI.siHomeVillage, pclchar->pclCI->clBI.siHomeVillage);

			}

		}

	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// ���Ǳ��� ��ü�̺�Ʈ
	//--------------------------------------------------------------------------------------------------------------------------------
	if( pclchar->siCharMode == CHARMODE_BLACKWAR )
	{
		if( pclBlackWarManager->IsBlackWar() )
		{
			cltCharServer *pclHostchar = pclenemychar->GetHostChar();

			SI32 siKind = pclchar->GetKind();
			SI16 VillageScore = 0;

			// [�߰� : Ȳ���� 2008. 1. 21 => ���� ������ ���� ����� ����.]
			if(pclClient->IsCountrySwitch(Switch_BlackWarReform)					&&
				( BLACKARMY_MAP_STARTINDEX > pclHostchar->GetCurrentVillageUnique()	||
				BLACKARMY_MAP_STARTINDEX+MAX_BLACKARMY_MAP_CNT < pclHostchar->GetCurrentVillageUnique())	)
			{
				SI08 Score = 0;
				// ���� �Ѵ��� �ش��ϴ� ���� ����.
				if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWCATAR")))
					Score = 1;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWRIFLE")))
					Score = 2;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWDAEGUM")))
					Score = 3;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_YELLOWSHABEL")))
					Score = 8;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_GREENSHABEL")))
					Score = 8;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_REDSHABEL")))
					Score = 8;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLUESHABEL")))
					Score = 8;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")))
				{
					Score = 20;
					pclBlackWarManager->SetDieBoss( true );
				}

				pclHostchar->siBlackWarEnemyKillScore += Score;
				// ���� �ֹ��� ������ ��Ͽ� ���϶� �����Ǵ� �����̱⿡ �決 ������ �����ش�. 
				pclHostchar->siVillageWarKillScore	= pclHostchar->siBlackWarEnemyKillScore;

				//[�߰� : Ȳ���� 2008. 1. 22 => ���� ���� ������ ���� ���� ����.]
				if( 0 < pclHostchar->pclCI->clBI.siHomeVillage && MAX_VILLAGE_NUMBER > pclHostchar->pclCI->clBI.siHomeVillage)
				{
					cltServer* pclserver = (cltServer*)pclClient;
					pclserver->pclVillageManager->BlackWarScoreAdd(pclHostchar->pclCI->clBI.siHomeVillage, Score);

					VillageScore = pclserver->pclVillageManager->GetBlackWarVillageScore(pclHostchar->pclCI->clBI.siHomeVillage);
				}    

				// ���� ������ +1 ���.
				++pclHostchar->siBlackWarEnemyKillNumber;

				SI32 Index = 0;
				SI32 id    = 0;
				while(id = pclClient->pclCM->GetCharOrder(Index))
				{
					Index++;

					// ������� �Ŀ��Ը� �����Ѵ�. 
					if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
					{
						if( pclClient->pclCM->CR[id]->pclCI->clBI.siHomeVillage == pclHostchar->pclCI->clBI.siHomeVillage )
						{
							//--------------------------------
							// Ŭ���̾�Ʈ�� ������ �˷��ش�. 
							//--------------------------------
							cltGameMsgResponse_WarKill clinfo(0, pclHostchar->siBlackWarEnemyKillNumber, pclHostchar->siBlackWarKilledNumber, 0, pclClient->pclCM->CR[id]->siBlackWarEnemyKillScore, VillageScore);
							cltMsg clMsg(GAMEMSG_RESPONSE_WARKILL, sizeof(clinfo), (BYTE*)&clinfo);
							pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}
			}
			// ������ ������� ���.
			else
			{
				if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWCATAR")))
					pclHostchar->siBlackWarEnemyKillNumber += 1;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWRIFLE")))
					pclHostchar->siBlackWarEnemyKillNumber += 2;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWDAEGUM")))
					pclHostchar->siBlackWarEnemyKillNumber += 3;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_YELLOWSHABEL")))
					pclHostchar->siBlackWarEnemyKillNumber += 5;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_GREENSHABEL")))
					pclHostchar->siBlackWarEnemyKillNumber += 5;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_REDSHABEL")))
					pclHostchar->siBlackWarEnemyKillNumber += 5;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLUESHABEL")))
					pclHostchar->siBlackWarEnemyKillNumber += 5;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")))
				{
					pclHostchar->siBlackWarEnemyKillNumber += 20;
					pclBlackWarManager->SetDieBoss( true );
				}

				//--------------------------------
				// Ŭ���̾�Ʈ�� ������ �˷��ش�. 
				//--------------------------------
				cltGameMsgResponse_WarKill clinfo(0, pclHostchar->siBlackWarEnemyKillNumber, pclHostchar->siBlackWarKilledNumber, 0, pclHostchar->siBlackWarEnemyKillScore, VillageScore);
				cltMsg clMsg(GAMEMSG_RESPONSE_WARKILL, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[pclHostchar->GetID()]->SendNetMsg((sPacketHeader*)&clMsg);
			}	

			pclBlackWarManager->IncreaseKillBlackUnitNumber();
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// ��� ������
	//--------------------------------------------------------------------------------------------------------------------------------
	if ( pclchar->siCharMode == CHARMODE_KINGGURI )
	{
		if(pclClient->IsCountrySwitch(Switch_RaccoonEvent_Change_Goonzu))// [����] �����̺�Ʈ ���� �̺�Ʈ�� ���� 2009-10
		{
			cltCharServer *pclHostchar = pclenemychar->GetHostChar();
			pclGoonzuKingGuriEventManager->SetDieKingGuri( true, pclchar->GetID(), pclHostchar->GetID() );
		}
		else
		{
			cltCharServer *pclHostchar = pclenemychar->GetHostChar();
			pclKingGuriEventManager->SetDieKingGuri( true, pclchar->GetID(), pclHostchar->GetID() );
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� ����.]
	//--------------------------------------------------------------------------------------------------------------------------------
	if ( pclchar->siCharMode == CHARMODE_SANTARACCOON )
	{
		cltCharServer *pclHostchar = pclenemychar->GetHostChar();
		pclSantaRaccoon->SetDieSantaRaccoon( true, pclchar->GetID(), pclHostchar->GetID() );
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// ���ĸ��� �̺�Ʈ ���Ͱ� �׾���.
	//--------------------------------------------------------------------------------------------------------------------------------
	if(	pclchar->clIdentity.siIdentity == IDENTITY_MOFUMOFUEVENT	|| 
		pclchar->GetKind() == KIND_MAMARACCOON						||
		pclchar->GetKind() == KIND_MAGICALRACCOON					||
		pclchar->GetKind() == KIND_RACCOONLORD						||
		pclchar->GetKind() == KIND_RACCOONTOWER						||
		pclchar->GetKind() == KIND_ZORRORACCOON)
	{
		pclMofuMofuEvent->KilledEnemy(	pclchar->clIdentity.clMofoMofuEvent.siField, 
			pclchar->clIdentity.clMofoMofuEvent.siIndex, 
			enemyid );
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// [����] �߼� �̺�Ʈ. ���� ����. => 2008-8-7
	//--------------------------------------------------------------------------------------------------------------------------------
	if (pclchar->GetKind() ==  pclClient->GetUniqueFromHash(TEXT("KIND_MOON")) )
	{
		cltServer*	pclserver = (cltServer*)pclClient;

		cltInnerStatusInfo	clinnerstatus;
		clinnerstatus.clEnemyType.Set( ENEMYTYPE_ALLPC, 0 );	// ��� PC�� ��ȣ��, ������� ������. 

		SI32 siID				= 0;
		SI32 siCharKind			= pclClient->GetUniqueFromHash(TEXT("KIND_COSMOSRABBIT2"));
		SI16 siVillageUnique	= pclchar->GetCurrentVillageUnique();
		SI32 siLevel			= 1;

		for(SI32 Count = 0; Count < 100; ++Count)
		{
			siID = pclserver->SetNPCChar(	siCharKind, 
				siVillageUnique, 
				NULL, 
				siLevel, 
				0, 
				pclchar->GetX(), 
				pclchar->GetY(), 
				0, 
				NPCITEMMODE_NORMAL, 
				&clinnerstatus );	

			// �ð� ������ �ִ� ���� ����			
			if( pclserver->pclCM->IsValidID( siID ) )
			{
				((cltCharServer*)pclserver->pclCM->CR[siID])->dwTimerClock	= pclserver->CurrentClock;
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// �δ� ���Ͱ� ����
	//--------------------------------------------------------------------------------------------------------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_INSTANCEMAP)
	{
		SI32 siParentMapIndex = pclClient->pclMapManager->GetParentMap( pclchar->GetMapIndex() );
		cltMapCommon* pclMap = pclClient->pclMapManager->GetMapPointer( siParentMapIndex );
		if( pclMap != NULL )
		{
			SI32 siMonsterScore = pclchar->clIdentity.clInstanceMap.siScore;

			pclMap->m_siInstanceMapScore += siMonsterScore;

			// ���ʽ� ���ʹ� ų ī��Ʈ�� ���Խ�Ű�� �ʴ´�
			if ( pclchar->GetKind() != pclClient->GetUniqueFromHash("KIND_PTIMEBONUS" ) )
			{
				if(pclenemychar->siQuestCount > 0)	{	pclMap->m_siKillCount += pclenemychar->siQuestCount;		}
				else								{	pclMap->m_siKillCount++;							}
			}

			// [����] 20404 - �� ���� �߰� : ���� ���͸� ���� ���� ���� ����
			if ( pclchar->GetKind() == pclClient->GetUniqueFromHash("KIND_GMONBONUS" ) )
			{
				SI32 siMapIndex = pclchar->GetMapIndex();

				pclNPCManager->MakeGuildRegenerationNPC( siMapIndex );
			}

			// �����̺�Ʈ �δ� ������ �����Ѵ�
			if ( INSTANCEMAP_TYPE_SERVER == pclClient->pclMapManager->GetInstanceMapType(siParentMapIndex) )
			{
				if ( pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &sTime) )
				{
					// �������� ����
					pclenemychar->siServerEvent_IndunScore += siMonsterScore;

					if ( IsCountrySwitch(Switch_Server_Event) )
					{
						pclServerEventManager->AddInstanceMapScore( siMonsterScore );
					}
				}
				else
				{
					pclMap->m_siInstanceMapScore = 0;
				}
			}

#ifdef _DEBUG
			pclClient->pclLog->FilePrint( TEXT("config\\regenerationNPC.txt"), TEXT("%d\t%d\t1\t1\t"), pclchar->GetMapIndex(), pclchar->GetKind() );
#endif


		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------
	// ���� ����
	//--------------------------------------------------------------------------------------------------------------------------------
	if(pclchar->clIdentity.siIdentity == IDENTITY_BLACKARMY)
	{
		if (pclBlackArmyManager->bWarSwitch)
		{
			cltCharServer *pclHostchar = pclenemychar->GetHostChar();

			SI32 warmapindex = pclchar->clIdentity.clBlackArmyInfo.siWarMapIndex;
			SI32 warunitindex = pclBlackArmyManager->FindWarUnitIndex(pclchar->GetKind());

			if (warunitindex >= 0 || warmapindex >= 0)
			{
				if (pclBlackArmyManager->clWarMap[warmapindex].clBlackArmyUnit[warunitindex].siCurNum > 0)
				{
					pclBlackArmyManager->clWarMap[warmapindex].clBlackArmyUnit[warunitindex].siCurNum--;
				}

				if (pclBlackArmyManager->clWarMap[warmapindex].siMapCurUnitNum > 0)
				{
					pclBlackArmyManager->clWarMap[warmapindex].siMapCurUnitNum--;
				}

				SI32 siKind = pclchar->GetKind();

				if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_CATAR")))
					pclHostchar->siWarEnemyKillNumber += 1;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_RIFLE")))
					pclHostchar->siWarEnemyKillNumber += 2;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_DAEGUM")))
					pclHostchar->siWarEnemyKillNumber += 3;
				else if (siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")))
				{
					pclHostchar->siWarEnemyKillNumber += 20;
					pclBlackArmyManager->clWarMap[warmapindex].siWarcmd = WAR_CMD_WIN;
				}

				//--------------------------------
				// Ŭ���̾�Ʈ�� ������ �˷��ش�. 
				//--------------------------------
				cltGameMsgResponse_WarKill clinfo(1, pclHostchar->siWarEnemyKillNumber, pclHostchar->siWarKilledNumber, pclHostchar->siBlackArmyWarMapIndex);
				cltMsg clMsg(GAMEMSG_RESPONSE_WARKILL, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[pclHostchar->GetID()]->SendNetMsg((sPacketHeader*)&clMsg);

			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------------
	// ����ã�� �̺�Ʈ ����NPC. ��������NPC ����
	//--------------------------------------------------------------------------------------------------------------------------------
	if ( pclchar->siCharMode == CHARMODE_TREASUREEVENT)
	{
		SI32 ChangedNPCKind	=	0	;
		SI32 siNPCCharKind = pclchar->GetKind()	;		// ���� ���Ǿ� ī�ε�

		if ( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_CURSEHIRO") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGHIRO") ) 	;
		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_DAEGUM1") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGJEAN") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_CATAR1") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGMERIEL") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_RIFLE1") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGCLARA") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_DAEGUM2") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGSPARKY") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_CATAR2") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGJEAN") ) ;
		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_RIFLE2") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGCLARA") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_REDSHABEL") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGMERIEL") ) 	;

		}
		else if( siNPCCharKind == pclClient->GetUniqueFromHash( TEXT("KIND_TREASURE_BLUESHABEL") ) )
		{
			ChangedNPCKind	=	pclClient->GetUniqueFromHash( TEXT("KIND_BLESSINGSPARKY") ) 	;
		}
		SI32 siMonsterLevel	=	1	;
		SI32 siLocationX	=	pclchar->GetX()	;
		SI32 siLocationY	=	pclchar->GetY()	;
		SI32 siMapindex		=	pclchar->GetMapIndex()	;


		// �ش� ��ġ���ٰ� �� �������� �ɸ��͸� ��ȯ�Ѵ�.

		SI32 id = SetNPCChar(ChangedNPCKind , VILLAGE_NONE, NULL, siMonsterLevel, 0, siLocationX, siLocationY, siMapindex, NPCITEMMODE_NONE, NULL );

		if(pclCM->IsValidID(id))
		{
			((cltCharServer*)pclCM->CR[id])->dwTimerClock = CurrentClock;
			SendServerResponseMsg(0, SRVAL_SUMMONEGG_USED, ChangedNPCKind, 0, pclchar->GetID());	// �޼����� �ٸ��ɷ� �̾��ش�
		}
	}
}

bool cltServer::GiveBigItem_Event( SI32 myid, SI32 enemyid )
{
	if( pclClient->pclCM->IsValidID(myid) == false )		return false;
	if( pclClient->pclCM->IsValidID(enemyid) == false )		return false;

	bool bBigItemGet = false;

	//================================================
	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	//================================================
	NDate Today;
	Today.SetDate(sTime.wYear, sTime.wMonth, sTime.wDay );

	if ( Today.GetDateVary() >= clValentineEventStart.GetDateVary() &&
		Today.GetDateVary() <= clValentineEventEnd.GetDateVary() )
	{	
		// myid�� ����̰� ������, �ʺ��� ����Ͱ� �ƴҶ�
		if (IsPC(myid) && pclCM->CR[myid]->GetHuntVillageUnique() <= 0 && pclCM->CR[myid]->GetMapIndex() != MAPINDEX_BEGINNER1)
		{
			if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
				return false;

			SI32 randvalue = rand() %  100;
			// ��ھ����� ��
			if (randvalue < siValentineAttack)
			{
				// �����ϰ� ��� �������� �ش�. 
				UI32 randCardvalue = rand() %  3;

				SI32 biItmes[4] = {ITEMUNIQUE(13006),  //Vī�� 
					ITEMUNIQUE(13010),	//N1ī��
					ITEMUNIQUE(13009)};//E1ī��

				SI32 bigitemunique = biItmes[randCardvalue];

				if(bigitemunique)
				{
					// ��� ��ǰ�� ������. 
					cltItem clItem;

					SI16 brareswitch = 0;
					if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
						0,0,0,0,0,0) == true)
					{
						clItem.siItemNum = 1;
						SI32 rtnvalue = 0;

						cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

						if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
						{
							// ��ھ����� ������ �α׷� ����
							//pclClient->pclLog->FilePrint(TEXT("Config\\WhiteDayEventItemDrop.Txt"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
							bBigItemGet = true;
						}
						else
						{
							// �κ��� ���ڸ��� ��� �߰��� �� ����. 
							if(rtnvalue == CANADDINV_FAIL_FULL)
							{
								SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
							}
						}
					}
				}
			}
		}
	}

	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	if ( Today.GetDateVary() >= clWhiteEventStart.GetDateVary() &&
		Today.GetDateVary() <= clWhiteEventEnd.GetDateVary() )
	{	
		// myid�� ����̰� ������, �ʺ��� ����Ͱ� �ƴҶ�
		if (IsPC(myid) && pclCM->CR[myid]->GetHuntVillageUnique() <= 0 && pclCM->CR[myid]->GetMapIndex() != MAPINDEX_BEGINNER1)
		{
			if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
				return false;

			SI32 randvalue = rand() %  100;
			//UI32 randCardvalue = rand() %  3;
			// ��ھ����� ��
			if (randvalue < siWhiteAttack) 
			{						
				SI32 bigitemunique =  ITEMUNIQUE(13016); //W ī��.

				if(bigitemunique)
				{
					// ��� ��ǰ�� ������. 
					cltItem clItem;

					SI16 brareswitch = 0;
					if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
						0,0,0,0,0,0) == true)
					{
						clItem.siItemNum = 1;
						SI32 rtnvalue = 0;

						cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

						if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
						{
							// ��ھ����� ������ �α׷� ����
							//pclClient->pclLog->FilePrint(TEXT("Config\\WhiteDayEventItemDrop.Txt"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
							bBigItemGet = true;
						}
						else
						{
							// �κ��� ���ڸ��� ��� �߰��� �� ����. 
							if(rtnvalue == CANADDINV_FAIL_FULL)
							{
								SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
							}
						}

					}

				}

			}
		}
	}
	//================================================
	// �ų��̺�Ʈ ������ ��� ��ġ ���� - by LEEKH 2007.12.21
	//================================================
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		//[�߰� : Ȳ���� 2007. 12. 11 �ų��̺�Ʈ�� ������ ����.]
		cltItem clfromitem;
		clfromitem.Init();

		NewYearLuckyBox(clfromitem);

		if(clfromitem.siUnique > 0)
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( clfromitem.siUnique, &clItem, 0, 0, &brareswitch,
				0,0,0,0,0,0) == true)
			{
				clItem.siItemNum = 1;

				SI32 rtnvalue = 0;

				cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

				if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
				{
					// ��ھ����� ������ �α׷� ����
					pclClient->pclLog->FilePrint(TEXT("Config\\NewYearItemInMonster.log"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
					bBigItemGet = true;
				}
				else
				{
					// �κ��� ���ڸ��� ��� �߰��� �� ����. 
					if(rtnvalue == CANADDINV_FAIL_FULL)
					{
						SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
					}
				}
			}
		}
	}

	return bBigItemGet;
}

bool cltServer::GiveBigItem_New( SI32 myid, SI32 enemyid )
{
	if( pclClient->pclCM->IsValidID(myid) == false )		return false;
	if( pclClient->pclCM->IsValidID(enemyid) == false )		return false;

	SI32 siMyLevel		= pclClient->pclCM->CR[myid]->pclCI->clIP.GetLevel();
	SI32 siEnemyLevel	= pclClient->pclCM->CR[enemyid]->pclCI->clIP.GetLevel();

	// ���� 25�̻��� ���͸� ��� �������� ����Ѵ�.
	if( siEnemyLevel < 25 )			return false;

	// �������� 31�̻��̸�, ��� �������� ���� �� ����.
	if( TABS(siMyLevel - siEnemyLevel) >= 31 )		return false;

	bool bBigItemGet = false;

	SI32 siConstantA = 200;
	SI32 siRevisionA = 280;

	SI32 siLuk = pclCM->CR[myid]->clPB.clTotalBA.GetLuk();
	if(siLuk > 100)			siLuk = 100;		// 100�̻��� ����.

	SI32 siLucky = ((float)siLuk * (float)( siConstantA - siLuk )) / ( (siRevisionA / 10.0f ) - (siLuk/6.0f) );
	SI32 siRand = rand() % 20000;

	SI32 bigitemunique = ITEMUNIQUE(13325);

	if( siRand < siLucky )
	{
		if(bigitemunique)
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
				0,0,0,0,0,0) == true)
			{
				clItem.siItemNum = 1;
				SI32 rtnvalue = 0;

				cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

				if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
				{
					// ��ھ����� ������ �α׷� ����
					//pclClient->pclLog->FilePrint(TEXT("Config\\BigItemBoxItemDrop.Txt"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
					bBigItemGet = true;
				}
				else
				{
					// �κ��� ���ڸ��� ��� �߰��� �� ����. 
					if(rtnvalue == CANADDINV_FAIL_FULL)
					{
						SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
					}
				}
			}
		}
	}

	return bBigItemGet;
}

bool cltServer::GiveBigItem( SI32 myid, SI32 enemyid )
{
	bool bBigItemGet = false;

	// GiveBigItem_Event �Լ��� �Űܰ�.
	/*	//================================================
	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	//================================================
	NDate Today;
	Today.SetDate(sTime.wYear, sTime.wMonth, sTime.wDay );

	if ( Today.GetDateVary() >= clValentineEventStart.GetDateVary() &&
	Today.GetDateVary() <= clValentineEventEnd.GetDateVary() )
	{	
	// myid�� ����̰� ������, �ʺ��� ����Ͱ� �ƴҶ�
	if (IsPC(myid) && pclCM->CR[myid]->GetHuntVillageUnique() <= 0 && pclCM->CR[myid]->GetMapIndex() != MAPINDEX_BEGINNER1)
	{
	if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
	return false;

	SI32 randvalue = rand() %  100;
	// ��ھ����� ��
	if (randvalue < siValentineAttack)
	{
	// �����ϰ� ��� �������� �ش�. 
	UI32 randCardvalue = rand() %  3;

	SI32 biItmes[4] = {ITEMUNIQUE(13006),  //Vī�� 
	ITEMUNIQUE(13010),	//N1ī��
	ITEMUNIQUE(13009)};//E1ī��

	SI32 bigitemunique = biItmes[randCardvalue];

	if(bigitemunique)
	{
	// ��� ��ǰ�� ������. 
	cltItem clItem;

	SI16 brareswitch = 0;
	if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
	0,0,0,0,0,0) == true)
	{
	clItem.siItemNum = 1;
	SI32 rtnvalue = 0;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

	if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
	{
	// ��ھ����� ������ �α׷� ����
	//pclClient->pclLog->FilePrint(TEXT("Config\\WhiteDayEventItemDrop.Txt"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
	bBigItemGet = true;
	}
	else
	{
	// �κ��� ���ڸ��� ��� �߰��� �� ����. 
	if(rtnvalue == CANADDINV_FAIL_FULL)
	{
	SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
	}
	}
	}
	}
	}
	}
	}

	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	if ( Today.GetDateVary() >= clWhiteEventStart.GetDateVary() &&
	Today.GetDateVary() <= clWhiteEventEnd.GetDateVary() )
	{	
	// myid�� ����̰� ������, �ʺ��� ����Ͱ� �ƴҶ�
	if (IsPC(myid) && pclCM->CR[myid]->GetHuntVillageUnique() <= 0 && pclCM->CR[myid]->GetMapIndex() != MAPINDEX_BEGINNER1)
	{
	if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
	return false;

	SI32 randvalue = rand() %  100;
	UI32 randCardvalue = rand() %  3;
	// ��ھ����� ��
	if ((randvalue < siWhiteAttack) &&(randCardvalue == 1)) // ���Ƿ� 1/3�� Ȯ���� �༭, 1/300�� ������ش�.
	{						
	SI32 bigitemunique =  ITEMUNIQUE(13016); //W ī��.

	if(bigitemunique)
	{
	// ��� ��ǰ�� ������. 
	cltItem clItem;

	SI16 brareswitch = 0;
	if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
	0,0,0,0,0,0) == true)
	{
	clItem.siItemNum = 1;
	SI32 rtnvalue = 0;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

	if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
	{
	// ��ھ����� ������ �α׷� ����
	//pclClient->pclLog->FilePrint(TEXT("Config\\WhiteDayEventItemDrop.Txt"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
	bBigItemGet = true;
	}
	else
	{
	// �κ��� ���ڸ��� ��� �߰��� �� ����. 
	if(rtnvalue == CANADDINV_FAIL_FULL)
	{
	SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
	}
	}

	}

	}

	}
	}
	}
	//================================================
	// �ų��̺�Ʈ ������ ��� ��ġ ���� - by LEEKH 2007.12.21
	//================================================
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
	//[�߰� : Ȳ���� 2007. 12. 11 �ų��̺�Ʈ�� ������ ����.]
	cltItem clfromitem;
	clfromitem.Init();

	NewYearLuckyBox(clfromitem);

	if(clfromitem.siUnique > 0)
	{
	// ��� ��ǰ�� ������. 
	cltItem clItem;

	SI16 brareswitch = 0;
	if(pclClient->pclItemManager->MakeRandItemUnique( clfromitem.siUnique, &clItem, 0, 0, &brareswitch,
	0,0,0,0,0,0) == true)
	{
	clItem.siItemNum = 1;

	SI32 rtnvalue = 0;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

	if(pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
	{
	// ��ھ����� ������ �α׷� ����
	pclClient->pclLog->FilePrint(TEXT("Config\\NewYearItemInMonster.log"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
	bBigItemGet = true;
	}
	else
	{
	// �κ��� ���ڸ��� ��� �߰��� �� ����. 
	if(rtnvalue == CANADDINV_FAIL_FULL)
	{
	SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
	}
	}
	}
	}
	}
	*/
	//================================================
	// å ���
	//================================================
	// �߱� �����̰� myid�� ����� ��츸 
	// ���� ����ġ�� ����
	if (pclClient->IsCountrySwitch(Switch_DropBookBox) && IsPC(myid) )
	{
		if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
			return false;

		SI32 randvalue = rand() % 1000;
		// ��ھ����� ��
		cltServer* pclserver = (cltServer*)pclClient;
		if ( randvalue < pclserver->pclBookBox->GetDropRate() )
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			clItem.siUnique = ITEMUNIQUE(7975); // å���� ����ũ
			// �Ƿι��� �ý��� ����
			clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

			SI32 rtnvalue = 0;

			cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

			if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
			{
				// ��ھ����� ������ �α׷� ����
				//pclClient->pclLog->FilePrint(TEXT("Config\\BookDrop.Txt"), TEXT("BookBox Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
				//bBigItemGet = true;
			}
			else
			{
				// �κ��� ���ڸ��� ��� �߰��� �� ����. 
				if(rtnvalue == CANADDINV_FAIL_FULL)
				{
					SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
				}
			}
		}
	}

	// ����/��� ���� ���.
	if ( pclClient->IsCountrySwitch(Switch_MaterialBox) && IsPC(myid) )
	{
		if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
			return false;

		if (  (((rand() << 16) | rand()) % 1000000) == 1 )		// 1/1000000 Ȯ��
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			// �߱��� �������ڸ� �ش�.
			if ( rand() % 100 < 30 || pclClient->IsWhereServiceArea(ConstServiceArea_China) )
			{
				clItem.siUnique = ITEMUNIQUE(13314);	//��������
			}
			else
			{
				clItem.siUnique = ITEMUNIQUE(13315); //������
			}

			// �Ƿι��� �ý��� ����
			clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

			SI32 rtnvalue = 0;

			cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

			if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
			{
				// ��ھ����� ������ �α׷� ����
				pclClient->pclLog->FilePrint(TEXT("Config\\TreasureBoxDrop.log"), TEXT("BookBox Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
				bBigItemGet = true;
			}
			else
			{
				// �κ��� ���ڸ��� ��� �߰��� �� ����. 
				if(rtnvalue == CANADDINV_FAIL_FULL)
				{
					SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
				}
			}

		}
	}

	//================================================
	// ��ھ����� ���
	//================================================
	// myid�� ����̰� ������, �ʺ��� ����Ͱ� �ƴҶ�, �߱� ����
	if ( bBigItemGet == false && IsWhereServiceArea( ConstServiceArea_China ) == false ) 
	{

		if (IsPC(myid) && pclCM->CR[myid]->GetHuntVillageUnique() <= 0 && pclCM->CR[myid]->GetMapIndex() != MAPINDEX_BEGINNER1)
		{
			if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
				return false;

			bool bGiveBigItem = false;

			if( pclClient->IsCountrySwitch( Switch_ManufactureRevitalize ) )
			{
				// �߱� Ȯ�� ����.
				if( pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
				{
					//SI32 siLuk = pclCM->CR[myid]->pclCI->clIP.GetLuk();
					SI32 siLuk = pclCM->CR[myid]->clPB.clTotalBA.GetLuk();
					if(siLuk == 0)			siLuk = 1;
					SI32 siRandMax = 5000000 / siLuk;
					siRandMax = min(500, siRandMax);
					SI32 siRand = ((rand() << 16) | rand()) % siRandMax;

					if(siRand == 0)			bGiveBigItem = true;
				}
				// �̱��� Ȯ���� Ʋ����. - by LEEKH 2007.12.20
				else if( pclClient->IsWhereServiceArea( ConstServiceArea_USA ) )
				{
					//SI32 siLuk = pclCM->CR[myid]->pclCI->clIP.GetLuk();
					SI32 siLuk = pclCM->CR[myid]->clPB.clTotalBA.GetLuk();
					if(siLuk <= 8)			siLuk = 8;
					// ���(MAX(8)) * ������(20) * ������(0.05)
					siLuk = (int)((float)siLuk * 20.0f * 0.05f);

					SI32 siRandMax = 25000 / siLuk;
					if(siRandMax > 25000)			siRandMax = 25000;

					SI32 siRand = rand() % siRandMax;
					if(siRand == 0)			bGiveBigItem = true;
				}
				else
				{
					//SI32 siLuk = pclCM->CR[myid]->pclCI->clIP.GetLuk();
					SI32 siLuk = pclCM->CR[myid]->clPB.clTotalBA.GetLuk();
					if(siLuk == 0)			siLuk = 1;
					SI32 siRandMax = 500000 / siLuk;
					//siRandMax = min(500, siRandMax);
					if(siRandMax < 500)			siRandMax = 500;

					SI32 siRand = rand() % siRandMax;

					if(siRand == 0)			bGiveBigItem = true;
				}
			}
			else
			{
				UI32 usertotalstatus = pclCM->CR[myid]->pclCI->clIP.GetLevel() * 6;
				UI32 luckpercent = pclCM->CR[myid]->pclCI->clIP.GetLuk() * 100 / usertotalstatus;
				UI32 hndpercent = pclCM->CR[myid]->pclCI->clIP.GetHnd() * 100 / usertotalstatus;

				UI32 luckpoint = 0;
				UI32 hndpoint = 0;
				UI32 huntpoint = 0;

				if (luckpercent >= 0)
				{
					if (luckpercent < 3)	luckpoint = 0;
					else if (luckpercent < 6)	luckpoint = 10;
					else if (luckpercent < 9)	luckpoint = 25;
					else if (luckpercent < 12)	luckpoint = 35;
					else if (luckpercent < 15)	luckpoint = 45;
					else if (luckpercent < 18)	luckpoint = 60;
					else if (luckpercent < 21)	luckpoint = 80;
					else if (luckpercent < 24)	luckpoint = 100;
					else if (luckpercent < 27)	luckpoint = 125;
					else	luckpoint = 150;
				}

				if (hndpercent >= 0)
				{
					if (hndpercent < 3)	hndpoint = 0;
					else if (hndpercent < 6)	hndpoint = 10;
					else if (hndpercent < 9)	hndpoint = 25;
					else if (hndpercent < 12)	hndpoint = 35;
					else if (hndpercent < 15)	hndpoint = 45;
					else if (hndpercent < 18)	hndpoint = 60;
					else if (hndpercent < 21)	hndpoint = 80;
					else if (hndpercent < 24)	hndpoint = 100;
					else if (hndpercent < 27)	hndpoint = 125;
					else	hndpoint = 150;
				}

				huntpoint = luckpoint * 0.7 + hndpoint * 0.3;

				UI32 battlepercent = 0;
				battlepercent = pclCM->CR[enemyid]->clPB.GetBattlePower() * 100 / usertotalstatus;

				if (battlepercent < 25)	huntpoint = 0;
				else if (battlepercent < 30)	huntpoint = huntpoint * 0.2;
				else if (battlepercent < 35)	huntpoint = huntpoint * 0.4;
				else if (battlepercent < 40)	huntpoint = huntpoint * 0.6;
				else if (battlepercent < 45)	huntpoint = huntpoint * 0.8;

				//UI32 randvalue = rand() % 1000000; //~0x7fff �����ۿ� �ȵǿ�-_-!

				UI32 randvalue = ((rand() << 16) | rand()) % 1000000;

				// ��ھ����� ��
				if (randvalue < huntpoint)
					bGiveBigItem = true;
			}

			if(bGiveBigItem)
			{
				// �����ϰ� ��� �������� �ش�. 
				SI32 bigitemunique = pclClient->pclItemManager->GetRandBigWarItem();

				if(bigitemunique)
				{
					// ��� ��ǰ�� ������. 
					cltItem clItem;

					SI16 brareswitch = 0;
					if(pclClient->pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch,
						0,0,0,0,0,0) == true)
					{
						cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

						// �Ƿι��� ����
						clItem.siItemNum = pclchar->CalcTiredPoint( 1 );

						SI32 rtnvalue = 0;


						if(clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
						{
							// ��ھ����� ������ �α׷� ����
							pclClient->pclLog->FilePrint(TEXT("Config\\RareItemInMonster.v"), TEXT("RareItem Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
							bBigItemGet = true;
						}
						else
						{
							// �κ��� ���ڸ��� ��� �߰��� �� ����. 
							if(rtnvalue == CANADDINV_FAIL_FULL)
							{
								SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
							}
						}

					}

				}

			}
		}
	}
	//================================================

	return bBigItemGet;
}

bool cltServer::GiveSpecialItem( SI32 myid, SI32 enemyid )
{
	// ����/��� ���� ���.
	if ( pclClient->IsCountrySwitch(Switch_MaterialBox) && IsPC(myid) )
	{
		if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
			return false;

		SI32 randvalue = rand() % 1000;
		// ��ھ����� ��
		cltServer* pclserver = (cltServer*)pclClient;
		if ( randvalue < pclserver->pclBookBox->GetDropRate() )
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			clItem.siUnique = ITEMUNIQUE(7975); // å���� ����ũ
			// �Ƿι��� �ý��� ����
			clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

			SI32 rtnvalue = 0;

			cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

			if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
			{
				// ��ھ����� ������ �α׷� ����
				//pclClient->pclLog->FilePrint(TEXT("Config\\BookDrop.log"), TEXT("BookBox Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
				//bBigItemGet = true;
			}
			else
			{
				// �κ��� ���ڸ��� ��� �߰��� �� ����. 
				if(rtnvalue == CANADDINV_FAIL_FULL)
				{
					SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
				}
			}
		}
	}

	//================================================
	// å ���
	//================================================
	// �߱� �����̰� myid�� ����� ��츸 
	// ���� ����ġ�� ����
	if (pclClient->IsCountrySwitch(Switch_DropBookBox) && IsPC(myid) )
	{
		if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
			return false;

		SI32 randvalue = rand() % 1000;
		// ��ھ����� ��
		cltServer* pclserver = (cltServer*)pclClient;
		if ( randvalue < pclserver->pclBookBox->GetDropRate() )
		{
			// ��� ��ǰ�� ������. 
			cltItem clItem;

			clItem.siUnique = ITEMUNIQUE(7975); // å���� ����ũ
			// �Ƿι��� �ý��� ����
			clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

			SI32 rtnvalue = 0;

			cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

			if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
			{
				// ��ھ����� ������ �α׷� ����
				//pclClient->pclLog->FilePrint(TEXT("Config\\BookDrop.Txt"), TEXT("BookBox Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
				//bBigItemGet = true;
			}
			else
			{
				// �κ��� ���ڸ��� ��� �߰��� �� ����. 
				if(rtnvalue == CANADDINV_FAIL_FULL)
				{
					SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
				}
			}
		}
	}


	// ���� �̺�Ʈ �δ����� NDE ���� ����
	if (  IsCountrySwitch(Switch_Server_Event) && IsPC( myid ) )
	{
		if ( pclMapManager->GetInstanceMapType(pclCM->CR[myid]->GetMapIndex( )) == INSTANCEMAP_TYPE_SERVER )
		{
			cltServer* pclserver = (cltServer*)pclClient;
			if ( NULL == pclserver )
			{
				return false;
			}

			if ( pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0 )
			{
				return false;
			}

			SI32 siRandValue = (rand() % 100) + 1;

			if ( siNDEScrollRate >= siRandValue )
			{
				// ��� ��ǰ�� ������. 
				cltItem clItem;

				// NDE ����
				clItem.siUnique = ITEMUNIQUE(13043); 
				// �Ƿι��� �ý��� ����
				clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

				SI32 rtnvalue = 0;

				cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

				if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
				{
					// ��ھ����� ������ �α׷� ����
					pclClient->pclLog->FilePrint(TEXT("Config\\NDEScroll.log"), TEXT("NDEScroll Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
				}
				else
				{
					// �κ��� ���ڸ��� ��� �߰��� �� ����. 
					if(rtnvalue == CANADDINV_FAIL_FULL)
					{
						SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
					}
				}
			}	// if ( siNDEScrollRate >= siRandValue ) ����
		}
	}

	// pvp-
	if ( IsCountrySwitch(Switch_BaekNyeonSam) && IsPC(myid) )
	{
		if( pclMapManager->IsPkMap(pclCM->CR[myid]->GetMapIndex()) )
		{
			if (pclCM->CR[myid]->pclCI->clIP.GetLevel() <= 0) 
				return false;

			SI32 randvalue = rand() % siBaenNyeonSamRate;
			// ��ھ����� ��
			cltServer* pclserver = (cltServer*)pclClient;
			if ( randvalue == 0 )
			{
				// ��� ��ǰ�� ������. 
				cltItem clItem;

				// ����
				clItem.siUnique = ITEMUNIQUE(2765); 
				// �Ƿι��� �ý��� ����
				clItem.siItemNum = ((cltCharServer*)pclCM->CR[myid])->CalcTiredPoint( 1 );

				SI32 rtnvalue = 0;

				cltCharServer *pclchar = (cltCharServer*)pclCM->CR[myid];

				if( clItem.siItemNum > 0 && pclchar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WAR, &rtnvalue))
				{
					// ��ھ����� ������ �α׷� ����
					pclClient->pclLog->FilePrint(TEXT("Config\\BackNeyonSam.log"), TEXT("BackNeyonSam Get User : \t[%s]\t / RareItem Unique, Num : \t[%d]\t[%d]"), pclCM->CR[myid]->GetName(), clItem.siUnique, clItem.siItemNum);
					//	bBigItemGet = true;
				}
				else
				{
					// �κ��� ���ڸ��� ��� �߰��� �� ����. 
					if(rtnvalue == CANADDINV_FAIL_FULL)
					{
						SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclchar->GetCharUnique());
					}
				}
			}
		}
	}

	return true;
}

