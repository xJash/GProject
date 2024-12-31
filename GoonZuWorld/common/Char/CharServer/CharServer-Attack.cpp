//---------------------------------
// 2004/10/30 ���°�
//---------------------------------

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"
#include "Char\CharServer\Char-Server.h"
#include "Order\Order.h"
#include "..\CharManager\CharManager.h"

#include "../../common/Event/MofuMofu/MofuMofu.h"

//--------------------------------------
// CommonLogic
//--------------------------------------
#include "MsgType-Person.h"

//--------------------------------------
// Server
//--------------------------------------
#include "Server.h"

// ������ ���ݹް� ������ ȣ���ϴ� �Լ� 
void cltCharServer::SetBeAttackedSwitch(cltServer* pclserver, SHORT enemyid)
{
	if(enemyid<=0)return ;

    if(pclCM->IsAlive(enemyid)==FALSE)return ;

	// �ǰ� ���� ������ �����Ѵ�. 
	clBeHitInfo.Set(true, enemyid);
	
	cltCharServer* pEnemyChar = pclCM->GetCharServer(enemyid) ;

	if(	pEnemyChar != NULL 
		&& pEnemyChar->clIdentity.siIdentity != IDENTITY_SOULGUARD_SUMMONPUMKIN
		&&IsNPC(GetCharUnique()) == true 
		&& pclKI->IsAtb((ATB_NOJJIM)) == false 
		&& clIdentity.siIdentity == 0)
	{
		// ��������� �����Ѵ�. 
		if(clJim.SetBeJimed(pclCM->CR[enemyid]->GetCharUnique(), pclserver->GetFrame()) == true)
		{
			// �̹� �ٸ� ���� ĳ���Ͱ� ������ ���� �����Ѵ�. 
			if(pclCM->CR[enemyid]->clJim.siJimSlaveCharUnique)
			{
				// �̹� ���� �ٸ� ĳ���Ͱ� ���� �ƴϾ��...
				if(pclCM->CR[enemyid]->clJim.siJimSlaveCharUnique != GetCharUnique())
				{
					
					SI32 id = pclCM->GetIDFromCharUnique(pclCM->CR[enemyid]->clJim.siJimSlaveCharUnique);
					if(pclCM->IsValidID(id))
					{
						pclCM->CR[id]->clJim.Init();
						
						cltGameMsgResponse_Jim clinfo(pclCM->CR[enemyid]->clJim.siJimSlaveCharUnique, 0);
						cltMsg clMsg(GAMEMSG_RESPONSE_JIM, sizeof(clinfo), (BYTE*)&clinfo);
						((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
						
					}
					
					pclCM->CR[enemyid]->clJim.siJimSlaveCharUnique = 0;
				}
				
			}
			
			// �������� �����Ѵ�. 
			pclCM->CR[enemyid]->clJim.SetJim(GetCharUnique());
			
			cltGameMsgResponse_Jim clinfo(GetCharUnique(), pclCM->CR[enemyid]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_RESPONSE_JIM, sizeof(clinfo), (BYTE*)&clinfo);
			SendNeighbourMsg(&clMsg, true);
		}
	}

	//--------------------------------------------------------
	// ȣ������ ĳ������ ��� �ֺ��� �Ʊ����� ������ ��û�Ѵ�. 
	//--------------------------------------------------------
	bool bwarswitch = false;
	bool bvillagewarswitch = false;
	if( siCharMode == CHARMODE_INSTANCEMAP ||
		siCharMode == CHARMODE_BLACKWAR )
	{
		bwarswitch = true;
	}
	
	SI32 villageunique = pclCI->clBI.siHomeVillage;
	switch(clIdentity.siIdentity) 
	{
	case IDENTITY_VILLAGEGOD:			bvillagewarswitch = true;	break;
	case IDENTITY_CASTLE:				bvillagewarswitch = true;	break;
	case IDENTITY_VILLAGEGOD_SUMMON:	bvillagewarswitch = true;	break;	
	case IDENTITY_PERSON_SUMMON:		bvillagewarswitch = true;	break;
	case IDENTITY_VILLAGEHUNT:			break;
	default:							break;
	}
	
	if(bwarswitch || pclKI->IsAtb(ATB_COWORK) || bvillagewarswitch)
	{

		// ����� ������ 30�� �Ѿ�� ������ ��û�ϰ� �ȴ�. 
		if(pclCM->CR[enemyid]->pclCI->clIP.GetLevel() > 30)
		{
			SI32 id = pclCM->FindNearAlly(GetKind(), GetMapIndex(), GetX(), GetY(), bwarswitch, villageunique);
			if(id)
			{
				OrderAttack(id, enemyid, BY_PLAYER);
			}
		}
	
	}
	
}

// �ǰݽ��� ����.  
void cltCharServer::BeAttackedAction()
{
	
	// ���� �޴� ���� �ߴܵǸ�, 
	if(clBeHitInfo.bBeAttackedSwitch == false)return ;

	// �ٸ� �Ϸ� �ٻ� ���¸� ó���� �� ����. 
	if(bBusySwitch == true) return ;

	// ��� �־�߸� �Ѵ�. 
	if(GetLife() <= 0)return ;

	// NPC�� �����ϴ�. 
	if(IsPC(CharUnique) )return ;
	// ��ȯ���� �Ұ���. 
	if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)return ;
	

	// �����ڰ� ��� �־�� �Ѵ�. 
	SI16 attackerid = clBeHitInfo.siAttackerID;
	if(pclCM->IsAlive(attackerid) == FALSE)	return ;

	// �ǰ� ���� ������ �ʱ�ȭ�Ѵ�.  
	clBeHitInfo.Init();

	// ���� ���� ��ó 
	FindEnemyAction(attackerid);

}


// ��� ���������κ��� ��� ĳ���͸� �����Ѵ�.
void cltCharServer::MakeTorpedo(cltServer* pclserver, SI32 attackid, cltItem* pcltorpedo)
{
	cltOrderDataInfo Order;
	pclserver->pclOrderManager->MakeOrder_ATTACK(&Order, attackid, BY_PLAYER);
	
	SI32 mapindex	= GetMapIndex();
	SI32 six		= GetX();
	SI32 siy		= GetY(); 
	
	//SI32 torpedoid = pclserver->MakeGuardChar(pclClient->GetUniqueFromHash(TEXT("KIND_TORPEDO")), pclCI->clBI.siHomeVillage, mapindex, six, siy, &Order, &clInnerStatus.clEnemyType);
	//if(torpedoid)
	//{
	//	// ����� �������� �߰��Ѵ�. 
	//	pclCM->CR[torpedoid]->clPB.siTorpedoDamage = pcltorpedo->GetMinDamage(pclserver->pclItemManager) + rand() % max(1, pcltorpedo->GetMaxDamage(pclserver->pclItemManager) - pcltorpedo->GetMinDamage(pclserver->pclItemManager) ) ;
	//	pclCM->CR[torpedoid]->ParametaBoxAction();

	//	// ��ȯ���� ����ð��� ���� ������ �ð��� �����Ѵ�.
	//	((cltCharServer*)(pclCM->CR[ torpedoid ]))->dwTimerClock = pclserver->CurrentClock;
	//}
}
