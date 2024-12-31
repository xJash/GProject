#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Agriculture.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-Mining.h"
#include "Msg\MsgType-Agriculture.h"

#include "../Common/Agriculture/Mining/MiningMgr.h"
#include "../Common/Order/order.h"
#include "../CommonLogic/Mine/Mine.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_MININGSTART(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )						return;
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )											return;

	cltGameMsgRequest_MiningStart * pclinfo = (cltGameMsgRequest_MiningStart*)pclMsg->cData;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if( pclChar == NULL )										return;
	cltAgriculture* pclAgriculture = pclChar->m_pclAgriculture;
	if( pclAgriculture == NULL )								return;

	bool Success = false;

	SI32 NearVillageUnique = 0;
	SI32 FieldObjectUnique = 0;
	SI32 returnval = 0;

	bool bCanMine = true;

	// �߿����������� ����� ä���� �����ϴ�.
	if ( pclCM->CR[id]->GetMapIndex() != 0 )	{		bCanMine = false;		}

	SI32 TotalSkillLevel = pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_MINE, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[0] );

	// ��ų���Ѿ��� ä�� ����Ʈ ���̶�� ����.
	SI16 questtype, questunique, para1, para2;
	SI16 questclearcond		= QUEST_CLEAR_COND_MINENOSKILL;
	bool bMineNoSkillGoing	= pclChar->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2);
	if ( TotalSkillLevel < 1 )
	{
		if (false == bMineNoSkillGoing)	{		bCanMine = false;		}
	}
	
	// �־��� ��ǥ�κ��� ����� ������ ã�´�. 
	SI32 XPos = pclCM->CR[id]->GetX();
	SI32 YPos = pclCM->CR[id]->GetY();
	NearVillageUnique = pclVillageManager->FindNearVillage( XPos, YPos );
	//cyj ������ �ʵ� ������Ʈ�� ã�´�.
	FieldObjectUnique = pclinfo->siFieldObjectUnique;

	// ���� ��ȣ�� �ƴ�����..
	if ( NearVillageUnique < 1 || NearVillageUnique > CUR_VILLAGE_LIMIT )	{		bCanMine = false;		}
	if ( pclinfo->siVillageUnique != NearVillageUnique )					{		bCanMine = false;		}

	// ���� �ִ� �������� ä���� �������� üũ 
	// ���� ��ġ�� ������ ���� Ÿ���� �ִ��� üũ	
	if( pclCM->CR[id]->CanMine( XPos, YPos, &returnval) == false )
	{
		SendServerResponseMsg( 0, SRVAL_MINE_FAIL, returnval, 0, pclCM->CR[id]->GetCharUnique() );
		bCanMine = false;
	}

	// ���� �ǹ��� ���ٸ�
	if( NearVillageUnique > 0 && NearVillageUnique < CUR_VILLAGE_LIMIT &&
		pclVillageManager->pclVillageInfo[ NearVillageUnique ]->clVillageVary.clStructureInfo.IsDuplicate( 160 ) == FALSE )
	{
		SendServerResponseMsg( 0, SRVAL_MINE_MINESTRUCTURE_NOT_EXIST, 0, 0, pclCM->CR[id]->GetCharUnique() );
		bCanMine = false;
	}

	//cyj ���� ������ ä���Ұ�
	if ( pclChar->pclCI->clHealthInfo.uiOrg1Disease != 0 || pclChar->pclCI->clHealthInfo.uiOrg2Disease != 0 ||
		pclChar->pclCI->clHealthInfo.uiOrg3Disease != 0 || pclChar->pclCI->clHealthInfo.uiOrg4Disease != 0 )
	{
		SendServerResponseMsg(0, SRVAL_MINE_FAIL, CANMINE_ERORR_HAVEDISEASE ,0 , pclChar->GetCharUnique() );
		bCanMine = false;
	}

	//cyj ������ �ȵǸ� ä���Ұ�
	if (pclChar->pclCI->clIP.GetLevel() < CANMINE_LEVEL)
	{
		SendServerResponseMsg(0, SRVAL_MINE_FAIL, CANMINE_ERORR_CANNOTLEVEL ,0 , pclChar->GetCharUnique() );
		bCanMine = false;
	}
	// 2009-04-20 ä���� �������� ã�� ���� ä���� �������� ���� �˻��ϰ� ä�������� ���� ã�´�.
	//cyj ä���� ������ ����ũ ã���� FieldObject�� �ֵ��� ����
	SI16 MiningItemUnique = 0;
	if( pclClient->IsCountrySwitch( Switch_FishFarmMineChange ) )
	{
		MiningItemUnique = pclMiningMgr->GetMineItemUniqueRandom( pclinfo->siVillageUnique );
	}
	else
	{
		MiningItemUnique = pclMiningMgr->GetMineItemUniqueFromVillageUnique(pclinfo->siVillageUnique);
	}
	if ( MiningItemUnique < 1 )												{		bCanMine = false;		}

	if( bCanMine )
	{
		bool bLease = false;
		BOOL bMiner = false;

		// 1. �ӽ� �Ӵ븦 �ߴ���?
		bLease = pclAgriculture->IsLeaseAgriculture( NearVillageUnique );
		// 2. �ǹ����� ���� �Ӵ븦 �ߴ���?
		bMiner = pclMineManager->IsMiner( NearVillageUnique, pclCM->CR[id]->pclCI->GetPersonID() );

		// ���߿� �ϳ��� ������, ä������
		if( bLease || bMiner )
		{
			UI32 uiExpireTime = 0;
			UI32 leftTime = 0;

			pclChar->siMiningItemUnique = MiningItemUnique;
			pclChar->dwPreGetMiningItemClock = 0;
			if( bLease == true && bMiner == false )		// �ӽ��Ӵ��� ��쿡�� ���� �ð��� ����Ѵ�..
			{
				uiExpireTime = pclAgriculture->GetExpireTime( NearVillageUnique );
				leftTime = uiExpireTime - pclClient->GetMinuteFromsTime(((cltServer*)pclClient)->sTime );
			}
			pclAgriculture->StartAgriculture( NearVillageUnique, pclClient->CurrentClock );

			SI32 MineSkillLevel = pclChar->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_MINE, 0, 0, &pclChar->pclCI->clCharItem.clItem[0] );
			if ( (MineSkillLevel < 10) && (true == bMineNoSkillGoing) )
			{
				MineSkillLevel = 10;
			}

			SI32 SuccessPercent = pclCM->CR[id]->GetMineRate( MineSkillLevel );

			SI32 DelayTime = 60000;
			DelayTime -= ((pclClient->pclItemManager->clItemStatistic.siItemPriceIndex / 100000 + 1 ) / 2 * 2) * 1000;
			DelayTime = max( 40000, DelayTime );

			cltGameMsgResponse_AgricultureStart clGameMsgResponse_AgricultureStart( MiningItemUnique, SuccessPercent, RANKTYPE_MINE, DelayTime, leftTime );
			cltMsg clMsg( GAMEMSG_RESPONSE_AGRICULTURESTART, sizeof(clGameMsgResponse_AgricultureStart), (BYTE*)&clGameMsgResponse_AgricultureStart );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			Success = true;
		}
		else
		{
			// �ӽ��Ӵ븦 �ϵ��� ��Ŷ�� �����Ѵ�.
			cltStrInfo *pStrInfo = GetStrInfo( NearVillageUnique, RANKTYPE_MINE );
			cltStrInfo *pCityHallInfo = GetStrInfo( NearVillageUnique, RANKTYPE_CITYHALL);

			GMONEY RentFee = 0;
			if( pStrInfo )		RentFee = pStrInfo->clMineStrInfo.clRentContract.siRentFee;
			if( RentFee <= 0 )	RentFee = 10000;

			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			// �븸�� ���� �̿��µ� ������ ��� ���� �Ӵ�Ḧ 25�������� �����Ѵ�. (PCK - 08.01.21)
			if (IsWhereServiceArea(ConstServiceArea_Taiwan))
			{
				if( pCityHallInfo && pCityHallInfo->clCityhallStrInfo.siTotalStockAmount == 0 )
				{
					RentFee = 250000;
				}
				else
				{
					RentFee = RentFee * npcrate / 100;
				}
			}
			else
			{
				RentFee = RentFee * npcrate / 100;
			}

			cltGameMsgResponse_AgricultureForNotRentMan clGameMsgResponse_AgricultureForNotRentMan( NearVillageUnique, RentFee, 0, RANKTYPE_MINE );
			cltMsg clMsg( GAMEMSG_RESPONSE_AGRICULTUREFORNOTRENTMAN, sizeof(clGameMsgResponse_AgricultureForNotRentMan), (BYTE*)&clGameMsgResponse_AgricultureForNotRentMan );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			Success = true;
		}
	}

	if ( ! Success )
	{
		OrderForceStop(id, BY_PLAYER);
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MININGPAYRENTFEE(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_MiningPayRentFee * pclinfo = (cltGameMsgRequest_MiningPayRentFee*)pclMsg->cData;

	if ( pclinfo->siRentFee < 1 )
	{
		return;
	}

	bool Success = false;

	GMONEY RentFee = 0;

	SI32 NearVillageUnique = 0;
	SI32 FieldObjectUnique = 0;

	SI32 XPos = pclCM->CR[id]->GetX();
	SI32 YPos = pclCM->CR[id]->GetY();

	cltStrInfo *pStrInfo = NULL;
	cltStrInfo *pCityhallInfo = NULL;

	// ���� �ִ� �������� ��簡 �������� üũ 
	// ���� ��ġ�� ������ �� Ÿ���� �ִ��� üũ
	SI32 returnval = 0;
	if( pclCM->CR[id]->CanMine( XPos, YPos, &returnval) == false )
	{
		SendServerResponseMsg( 0, SRVAL_MINE_FAIL, returnval, 0, pclCM->CR[id]->GetCharUnique() );

		goto Exiting;
	}

	// �Ӵ� ������ üũ�ϴ� ������
	// �־��� ��ǥ�κ��� ����� ������ ã�´�. 
	NearVillageUnique = pclVillageManager->FindNearVillage( XPos, YPos );
	FieldObjectUnique = pclinfo->siFieldObjectUnique;

	// ���� ��ȣ�� �ƴ�����..
	if ( NearVillageUnique < 1 || NearVillageUnique > CUR_VILLAGE_LIMIT )
	{
		goto Exiting;
	}

	// ä���ǹ��� ���ٸ� return
	if ( pclVillageManager->pclVillageInfo[ NearVillageUnique ]->clVillageVary.clStructureInfo.IsDuplicate( 160 ) == FALSE )
	{
		goto Exiting;
	}

	//cyj ä���� ������ ����ũ ã���� FieldObject�� �ֵ��� ����
	//SI16 MiningItemUnique = pclMiningMgr->GetMineItemUniqueFromVillageUnique( NearVillageUnique );
	SI16 MiningItemUnique = 0;

	if( pclClient->IsCountrySwitch( Switch_FishFarmMineChange ) )
	{
		MiningItemUnique = pclMiningMgr->GetMineItemUniqueRandom( NearVillageUnique );
	}
	else
	{
		MiningItemUnique = pclMiningMgr->GetMineItemUniqueFromVillageUnique(NearVillageUnique);
	}
	
	if ( MiningItemUnique < 1 )
	{
		goto Exiting;
	}

	pStrInfo = GetStrInfo( NearVillageUnique, RANKTYPE_MINE );
	pCityhallInfo = GetStrInfo( NearVillageUnique, RANKTYPE_CITYHALL);

	if ( pStrInfo == NULL || pCityhallInfo == NULL)
	{
		goto Exiting;
	}

	if ( pStrInfo->clMineStrInfo.clRentContract.siRentFee == 0 )
	{
		RentFee = 10000;
	}
	else
	{
		RentFee = pStrInfo->clMineStrInfo.clRentContract.siRentFee;
	}

	SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
	// �븸�� ���� �̿��µ� ������ ��� ���� �Ӵ�Ḧ 25�������� �����Ѵ�. (PCK - 08.01.21)
	if (IsWhereServiceArea(ConstServiceArea_Taiwan))
	{
		if(pCityhallInfo->clCityhallStrInfo.siTotalStockAmount == 0)
		{
			RentFee = 250000;
		}
		else
		{
			RentFee = RentFee * npcrate / 100;
		}
	}
	else
	{
		RentFee = RentFee * npcrate / 100;
	}

	// �� �� ���ݰ� ���� Ʋ��
	if ( RentFee != pclinfo->siRentFee )
	{
		goto Exiting;
	}

	// ������ ����
	if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < RentFee )
	{
		goto Exiting;
	}

	SI32 expireTime = pclClient->GetMinuteFromsTime( sTime ) + 600;

	sDBRequest_AgriculturePayMoneyForRentLand clMsg( PersonID, id, NearVillageUnique, RANKTYPE_MINE, RentFee, MiningItemUnique, expireTime );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	Success = true;

Exiting:
	if ( ! Success )
	{
		OrderForceStop(id, BY_PLAYER);
	}
}

