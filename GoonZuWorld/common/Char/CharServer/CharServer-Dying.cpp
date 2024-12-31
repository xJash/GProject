//---------------------------------
// 2004/10/30 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"
#include "Char\CharServer\Char-Server.h"
#include "..\CharManager\CharManager.h"
#include "Order/order.h"

//--------------------------------------
// CommonLogic
//--------------------------------------
#include "CityHall\CityHall.h"
#include "Msg\MsgType-Summon.h"
#include "MsgType-Person.h"


//--------------------------------------
// Server
//--------------------------------------
#include "..\..\Server\Server.h"


//--------------------------------------
// DBManager
//--------------------------------------
#include "..\..\DBManager\GameDBManager_World\DBMsg-Summon.h"

extern cltCommonLogic* pclClient;

// �����ð� �׵��� �Ѵ�. 
bool cltCharServer::Action_Dying()
{
	cltCharCommon::Action_Dying();

	// �븸������ ĳ���� ��Ȱ���ð��� ��5�ʷ� �Ѵ�. (PCK - 2007.09.11) - ��Ȯ�ϰ� 5�ʷδ� �ȵ�.
	// 50(���) * (6(Frame) * 50(ms)) = 15000ms (15��)
	// ���� ������� ��ȭ���Ѽ� ĳ���� ��Ȱ���ð��� �����Ҽ� �ִ�.
	SI32	siDyingDelay = 50;
	if (pclClient->IsCountrySwitch(Switch_DyingDelay))
		siDyingDelay = 17;
	else
		siDyingDelay = 50;

	if(siCharDyingDelay >= siDyingDelay)
	{
		siCharDyingDelay = 0;

		return TRUE;
	}
	else
	{
		// �ѹ��� ����ǰ� �Ѵ�. 
		if(siCharDyingDelay == 0)
		{
			// ���Ͱ� �ش� ĳ������ ��ȯ����� 
			if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				
				// ��ȯ���� ��� ����ġ ���Ƽ�� �ش�. 
				// ������ ����� ��쿡�� ���Ƽ�� ����. 
				if(IsDeathPenaltyCondition())
				{
					SI32 summonlevel = pclCI->clIP.GetLevel();
					SI32 decexp = summonlevel * 10;
					
					pclCI->clIP.DecreaseExp(decexp);
					SetUpdateSwitch(UPDATE_IP, true, 0);
				}
			}
		}
		
		//if(GetKind () == pclClient->GetUniqueFromHash(TEXT("KIND_TOYO1")))
		//{
		//	return TRUE;
		//}

		siCharDyingDelay++;
		
	}
	


	return FALSE;

}

// ��� ó��. 
void cltCharServer::Dead()
{
	//if(GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_TOYO1")))
	//{
	//	cltServer* pclserver = (cltServer*)pclClient;

	//	cltInnerStatusInfo clinnerstatus;
	//	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

	//	SI32 id = pclserver->SetNPCChar(pclClient->GetUniqueFromHash(TEXT("KIND_TOYO2")), pclCI->clBI.siHomeVillage, NULL, 1, 0, GetX(), GetY(), 0, NPCITEMMODE_NORMAL, &clinnerstatus );
	//}

	// �ش� ���Ͱ� �����̶�� 
	if(clIdentity.siIdentity == IDENTITY_CASTLE)
	{
		if( pclCI->clBI.siHomeVillage >= 0 && pclCI->clBI.siHomeVillage < MAX_VILLAGE_NUMBER )
		{
			pclClient->pclVillageManager->pclVillageInfo[pclCI->clBI.siHomeVillage]->siCastleCharUnique = 0;
			pclClient->pclVillageManager->pclVillageInfo[pclCI->clBI.siHomeVillage]->dwLastCastleClock = pclClient->CurrentClock; 
			//SI32 siKind = pclClient->pclKindInfoSet->GetDefaultCastle();
			SI32 siKind = pclClient->pclKindInfoSet->GetDefaultCastle();

			SI32 siCapa = ((cltCityHall *)(pclClient->pclCityHallManager->pclStruct[pclCI->clBI.siHomeVillage]))->clStrInfo.clCityhallStrInfo.siCastleCapa - 5 ;
			if( siCapa  < 100) siCapa  = 100;

			((cltCityHall *)(pclClient->pclCityHallManager->pclStruct[pclCI->clBI.siHomeVillage]))->SetCastle(siKind, 0, 0, siCapa);
		}
	}
	
	// ���Ͱ� �ش� ������ ��Ȳ���̶�� 1���Ŀ� �ٽ� �츮�����ؼ� �ʱ�ȭ�� �Ѵ�.
	else if(clIdentity.siIdentity == IDENTITY_VILLAGEGOD)
	{
		if( pclCI->clBI.siHomeVillage >= 0 && pclCI->clBI.siHomeVillage < MAX_VILLAGE_NUMBER )
		{
			pclClient->pclVillageManager->pclVillageInfo[pclCI->clBI.siHomeVillage]->siVillageGodCharUnique = 0;
			pclClient->pclVillageManager->pclVillageInfo[pclCI->clBI.siHomeVillage]->dwLastVillageGodClock = pclClient->CurrentClock; 
			
			// ������ Default ��Ȳ������ �ʱ�ȭ��Ų��.
			//SI32 siKind = pclClient->pclKindInfoSet->GetDefaultVillageGod();
			SI32 siKind = ((cltCityHall *)(pclClient->pclCityHallManager->pclStruct[pclCI->clBI.siHomeVillage]))->clStrInfo.clCityhallStrInfo.siSymbolKind;
			SI32 siCapa = ((cltCityHall *)(pclClient->pclCityHallManager->pclStruct[pclCI->clBI.siHomeVillage]))->clStrInfo.clCityhallStrInfo.siSymbolCapa - 5 ;

			if( siCapa  < 100) siCapa  = 100;

			((cltCityHall *)(pclClient->pclCityHallManager->pclStruct[pclCI->clBI.siHomeVillage]))->SetSymbol(siKind, 0, 0, siCapa );
		}
	}
	
	// ���Ͱ� �ش� ĳ������ ��ȯ����� 
	if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
	{
		SI32 siParentID = GetSummonParentID();
		if(pclCM->IsValidID(siParentID)==TRUE)
		{
			cltCharServer* pclchar = pclCM->GetCharServer( siParentID );
			if( NULL == pclchar ) return;

			cltSummon *pclSummon = pclchar->pclCI->clSummonInfo.GetSummon( GetSummonIndex() );
			//==========================================
			// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
			//==========================================
			if(pclSummon)
			{
				if( pclClient->IsCountrySwitch(Switch_SummonTramsform) )
				{
					// DB�� ������Ʈ �����ش�. �̶� ������ ���� �ȴ�.
					pclchar->SendDBSummon( SETSUMMON_REASON_UPDATE, GetSummonIndex() );
				}
				
				pclSummon->siStatus = SUMMON_STATUS_DEAD;
				//pclSummon->siShortenLife += 1;		// ������ 1�Ͼ� ���δ�.
				pclSummon->clIP.Set(&pclCI->clIP);
				pclSummon->clIP.SetLife(0);			// Ȥ�� ���� 
				pclSummon->clIP.SetMana(0);
				cltGameMsgResponse_Summon clInfo(pclchar->GetCharUnique(), GetSummonIndex(), pclSummon);
				cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			//==========================================
			// ��ȯ�� ������ DB�� �����Ѵ�.
			//==========================================
			{
				pclchar->SendDBSummon(SETSUMMON_REASON_UPDATE, GetSummonIndex());
			}
			//==========================================
			// �������׵� ������ ������ ���Ž�Ų��.
			//==========================================
			{
				pclchar->siChildCharUnique = 0;
				
				cltGameMsgResponse_ChangeSummonStatus clInfo(pclchar->GetCharUnique(), pclchar->siChildCharUnique, pclchar->siSummonIndex);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}
// ����ó��. 
void cltCharServer::SelfBombAction()
{
	cltGameMsgResponse_IncLife clInfo(GetCharUnique(), 0, 0, 0, 0, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
	SendNeighbourMsg(&clMsg, true);
	
	SetLife(0);
}