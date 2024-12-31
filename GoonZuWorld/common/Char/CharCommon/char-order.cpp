
#include "..\..\Message\Message.h"
#include "..\..\..\Server\time\mytime.h"
#include "..\..\Client\Music\Music.h"
#include <CommonLogic.h>
#include "..\..\..\Server\Server.h"
#include "../../PartyMgr/PartyMgr.h"
#include "../../PartyMgr/PartyObj.h"
//------------------------------------
// Common
//------------------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"

#include "..\..\Order\Order.h"
#include "..\..\Util\Util.h"
#include "char\CharCommon\Char-Common.h"

//------------------------------------
// CommonLogic
//------------------------------------
#include "..\..\CommonLogic\MagicMgr\MagicMgr.h"
#include "MsgRval-Define.h"
#include "../../CommonLogic/Msg/MsgType-Party.h"


extern cltCommonLogic* pclClient;

// ����� ���� �����ϱ� ���� �ؾ��� �ʱ�ȭ 
void cltCharCommon::InitPreGetOrder()
{
	// ���� �����ϴ� ĳ���͸� �ʱ�ȭ�Ѵ�.
	clAttackTarget.Init();
	
	// �ǰ� ������ �ʱ�ȭ�Ѵ�. 
	clBeHitInfo.Init();

}


// ����� ����� ������ �����Ѵ�. 
BOOL cltCharCommon::GetOrderBuffer()
{
	int id=0;
	DWORD flag = 0;
	SI32 returnval = 0;

	//-------------------------------------
	// ���� ����� ������ �����Ѵ�. 
	//-------------------------------------
	if(ReserveOrder.siOrder==ORDER_WAIT)return FALSE;

	// ���� ĳ�����̰� ��Ȱ����� �ƴ϶�� ����� ������ �� ����. 
	if(ReserveOrder.siOrder != ORDER_REVIVE)
	{
		if(GetLife() < 0 )return FALSE;
		if(bBusySwitch	==	true)return FALSE;
	}
	

	//----------------------------------------------------------------
	// ���� ����� ���ϰ� �ִ� �߿��� ���� ��� �̿ܿ��� ���� �ʴ´�. ��ų� ������ �ɸ��� �����ϼ� ����. 
	//----------------------------------------------------------------
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE) || clInnerStatus.IsStatus(INNERSTATUS_FROZEN) || clInnerStatus.IsStatus(INNERSTATUS_STUN) )
	{
		if(ReserveOrder.siOrder != ORDER_STOP && ReserveOrder.siOrder != ORDER_FORCESTOP)
		{
			return FALSE;
		}
	}
	//----------------------------------------------------------
	// ����� ����� �Էµ� ��� ������ ���� ���ϰ� �ʱ�ȭ�Ѵ�. 
	//----------------------------------------------------------
	if(ReserveOrder.siHostMode == BY_PLAYER)
	{
		InitWarpInfo();
	}

	//---------------------------------------------------------
	// ������ ��� ����� ���� ����� ������ �����Ѵ�. 
	//---------------------------------------------------------
	// ������ ��쿡��. 
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{

		if(ReserveOrder.siOrder == ORDER_STOP)
		{
			cltOrderDataInfo clorder;
			if(((cltCharServer*)this)->DoReservedAttackAction(&clorder) == true)
			{
				ReserveOrder.Set(&clorder);
			}
		}
	}

	switch(ReserveOrder.siOrder)
	{
	case ORDER_STOP:
		InitPreGetOrder();
		clCurOrder.Set(&ReserveOrder);
		break;
	case ORDER_FORCESTOP:
		InitPreGetOrder();
		clCurOrder.Set(&ReserveOrder);

		// ������ ��쿡��. 
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			//------------------------------------
			// �̿��鿡�� �����϶�� ���ø� ������. 
			//-------------------------------------
			cltOrderDataInfo clOrderDataInfo;
			if( pclClient->pclOrderManager->MakeOrder_FORCESTOP(&clOrderDataInfo, BY_PLAYER) == true)
			{
				cltOrderData clOrderData;
				clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
				
				cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
				((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
			}
		}	
		break;

	case ORDER_REVIVE:
		bBusySwitch			= false;
		
		// Ŭ���̾�Ʈ���� �ӽ÷� �츰��. 
		if(pclClient->GameMode != GAMEMODE_SERVER)
		{
			pclCI->clIP.SetLife(1);
		}

		InitPreGetOrder();
		clCurOrder.Set(&ReserveOrder);
		SetCurrentOrder(ORDER_STOP);
		break;

		
	case ORDER_MOVE:

		if(IsAtb(ATB_MOVE))
		{
			SI32 x =	LOWORD(ReserveOrder.siPara1);
			SI32 y =	HIWORD(ReserveOrder.siPara1);
			
			// �̵��� ���� �� ���� �� �ε���. 
			siMoveMapIndex	= GetMapIndex();


			InitPreGetOrder();
			clCurOrder.Set(&ReserveOrder);

			SetMove(x, y);

			// ���� ����Ʈ���� �̵����� Ȯ���Ѵ�. 

			// ������ ��쿡��. 
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				//------------------------------------
				// �̿��鿡�� �̵��϶�� ���ø� ������. 
				//-------------------------------------
				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_MOVE(&clOrderDataInfo, x, y, BY_PLAYER) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
					
					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
				}

				((cltCharServer*)this)->CharServerMoveByGate(x, y);


				if( siPartyIndex > 0)
				{
					CPartyObj* pParty =	pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
					if( pParty ) 
						pParty->NotifyMovePosToPartyMember(GetCharUnique(),x,y,false);
				}						
			}
			
		}
		
		break;
		
	case ORDER_STRAIGHTMOVE:
		if(IsAtb(ATB_MOVE))
		{

			SI32 x =	LOWORD(ReserveOrder.siPara1);
			SI32 y =	HIWORD(ReserveOrder.siPara1);

			// �̵��� ���� �� ���� �� �ε���. 
			siMoveMapIndex	= GetMapIndex();



			InitPreGetOrder();
			clCurOrder.Set(&ReserveOrder);

			SetMove(x, y);

			// ������ ��쿡��. 
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				//------------------------------------
				// �̿��鿡�� �̵��϶�� ���ø� ������. 
				//-------------------------------------
				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_STRAIGHTMOVE(&clOrderDataInfo, x, y, BY_PLAYER) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
				}
			}
			
		}
		
		break;
	
	case ORDER_ATTACK:
		{
			// ������ ������ ĳ���͸� ������ �� �ִ�. 
			// ���� ������ �� �ִ�. 
			SI32 targetid  = ReserveOrder.siPara2;
			bool pvpFlag = ReserveOrder.siPara4 > 0 ? true : false;
			if(CanAttack(targetid, pvpFlag))
			{
				InitPreGetOrder();
				clCurOrder.Set(&ReserveOrder);
				siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
				
				SetAttack(targetid,pvpFlag);
				
				//-------------------------------------
				// �̿��鿡�� �����϶�� ��û�� ������. 
				//-------------------------------------
				// ������ ��쿡��. 
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltOrderDataInfo clOrderDataInfo;
					if( pclClient->pclOrderManager->MakeOrder_ATTACK(&clOrderDataInfo, targetid, BY_PLAYER, ReserveOrder.siPara4 ) == true)
					{
						cltOrderData clOrderData;
						clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
						
						cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
						if( IsPC( GetCharUnique() ) )
							((cltCharServer*)this)->SendNeighbourExceptMeMsg(&clMsg);
						else
							((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
					}
				}
				
			}
			
		}
		break;
	case ORDER_MAGIC:
		{
			SI32 magickind	= ReserveOrder.siPara3;
			bool pvpFlag	= ReserveOrder.siPara4 > 0 ? true : false;

			SI32 returnval = 0;

			stMagicAttributeData* pMagicAttributeData = pclClient->pclMagicManager->GetMagicAttribute( magickind );
			if ( NULL == pMagicAttributeData )
			{
				break;
			}

			SI32 targetid	= ReserveOrder.siPara2;
			if ( MAGIC_CASTTYPE_BUF == pMagicAttributeData->si08MagicCastType )
			{
				targetid = GetID();
			}

			bool bCanMagic = false;
			if ( MAGIC_CASTTYPE_BUF == pMagicAttributeData->si08MagicCastType )
			{
				bCanMagic = CanMagicBuf( magickind, &returnval );
			}
			else
			{
				bCanMagic = CanMagic(targetid, magickind, &returnval, pvpFlag);
			}

			if ( false == bCanMagic )
			{
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					switch(returnval)
					{
					case CANUSEMAGIC_ERROR_NEEDMANA:	
					case CANUSEMAGIC_ERROR_FARDISTANCE:	
					case CANUSEMAGIC_ERROR_NEEDTIMEDELAY:
					case CANUSEMAGIC_ERROR_NOTENOUGHSKILL:
						((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_CANUSEMAGIC_FAIL,  returnval, 0, GetCharUnique()); 
						break;
					}
				}
				break;
			}

			//------------------------------------------
			// ������ ��� ������ ���� ������ �����Ѵ�. 
			//-----------------------------------------
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				if( IsPC(GetCharUnique()) == false && ( GetCurrentOrder() == ORDER_ATTACK || GetCurrentOrder() == ORDER_ATTACK_CLIENT ) )
				{
					((cltCharServer*)this)->SetReservedAttackTargetID(clAttackTarget.siAttackID);
					
				}
			}

			InitPreGetOrder();
			clCurOrder.Set(&ReserveOrder);

			//-----------------------------------
			// ĳ���Ͱ� ��ǥ�� ���ϵ��� �����Ѵ�.
			//-----------------------------------
			if ( (MAGIC_CASTTYPE_BUF != pMagicAttributeData->si08MagicCastType) && (pclCM->IsValidID(targetid)) )
			{
				SI32 dir = DecideDirection8(GetX(), GetY(), pclCM->CR[targetid]->GetX(), pclCM->CR[targetid]->GetY());
				if(dir)
				{
					ChangeDirectionNormal(dir);
				}

				if( pvpFlag )
				{
					// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
					//if( pclClient->IsWhereServiceArea(ConstSwitch_PVP) )
					if(pclClient->siEnablePVP == 1)
					{
						clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
						pclCM->CR[targetid]->clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
					}
				}
			}

			//-------------------------------------
			// �̿��鿡�� ������ ������� �뺸�Ѵ�. 
			//-------------------------------------
			// ������ ��쿡��. 
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_MAGIC(&clOrderDataInfo, targetid, magickind, BY_PLAYER, ReserveOrder.siPara4) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
					
					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
				}
			}
			else
			{
				// ������ ����غ���� ����Ʈ�� �ִ��� üũ�Ѵ�
				DoQuestCheckAndAction( QUEST_CLEAR_COND_USEMAGIC );

			}
		}
		break;
		
	case ORDER_FISH:
		{
			// Hero�Ӽ��� ���� ����ڸ� �����ϴ�. 
			if(pclKI->IsAtb(ATB_FISH) == false)return FALSE;


			// ���� ������ ��´�. 
			if(ReserveOrder.siPara1)
			{
				ChangeDirection(ReserveOrder.siPara1);
			}
			
			InitPreGetOrder();
			clCurOrder.Set(&ReserveOrder);

			//-------------------------------------
			// �̿��鿡�� ���ø� ������� �뺸�Ѵ�. 
			//-------------------------------------
			// ������ ��쿡��. 
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_FISH(&clOrderDataInfo, ReserveOrder.siPara1, BY_PLAYER) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
					
					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
				}
			}
			
		}
		break;
		
	case ORDER_FARM:
		{
			if(pclKI->IsAtb(ATB_FARM) == false)return FALSE;

			SI32 x =	LOWORD(ReserveOrder.siPara1);
			SI32 y =	HIWORD(ReserveOrder.siPara1);

			SI32 rtnval = 0;
			if(CanFarm(x, y, &rtnval))
			{
				
				InitPreGetOrder();
				clCurOrder.Set(&ReserveOrder);
				
				SetFarm(x, y);
				
				//-------------------------------------
				// �̿��鿡�� ��縦 ������ �뺸�Ѵ�. 
				//-------------------------------------
				// ������ ��쿡��. 
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltOrderDataInfo clOrderDataInfo;
					if( pclClient->pclOrderManager->MakeOrder_FARM(&clOrderDataInfo, x, y, BY_PLAYER) == true)
					{
						cltOrderData clOrderData;
						clOrderData.Make(GetCharUnique(), &clOrderDataInfo);
						
						cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
						((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
					}
				}
			}
			else
			{
				cltServer *pclServer = (cltServer *)pclClient;

				pclServer->SendServerResponseMsg( 0, SRVAL_FARM_FAIL, rtnval, 0, GetCharUnique() );
			}
		}
		break;

	case ORDER_MINE:
		{
			if(pclKI->IsAtb(ATB_MINE) == false)return FALSE;

			SI32 x =	LOWORD(ReserveOrder.siPara1);
			SI32 y =	HIWORD(ReserveOrder.siPara1);

			SI32 rtnval = 0;
			if(CanMine(x, y, &rtnval))
			{
				InitPreGetOrder();
				clCurOrder.Set(&ReserveOrder);

				SetMine(x, y);

				//-------------------------------------
				// �̿��鿡�� ��縦 ������ �뺸�Ѵ�. 
				//-------------------------------------
				// ������ ��쿡��. 
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltOrderDataInfo clOrderDataInfo;
					if( pclClient->pclOrderManager->MakeOrder_MINE(&clOrderDataInfo, x, y, BY_PLAYER) == true)
					{
						cltOrderData clOrderData;
						clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

						cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
						((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
					}
				}
			}
			else
			{
				cltServer *pclServer = (cltServer *)pclClient;
				pclServer->SendServerResponseMsg( 0, SRVAL_MINE_FAIL, rtnval, 0, GetCharUnique() );
			}
		}
		break;

	case ORDER_SITDOWN:
		// ���� ������ ��´�. 
		if(ReserveOrder.siPara1)
		{
			ChangeDirection(ReserveOrder.siPara1);
		}

		InitPreGetOrder();
		clCurOrder.Set(&ReserveOrder);

		//-------------------------------------
		// �̿��鿡�� ������ �뺸�Ѵ�.
		//-------------------------------------
		// ������ ��쿡��. 
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			cltOrderDataInfo clOrderDataInfo;

			if( pclClient->pclOrderManager->MakeOrder_SITDOWN(&clOrderDataInfo, ReserveOrder.siPara1, BY_PLAYER) == true)
			{
				//KHY - 1109 - ��í����- �������漮�߰�
				if( IsHaveCushionItem() > 0 )
				{
					/*cltGameMsgResponse_IshaveCushion clMsg(true);
					
					cltMsg clMsg( , sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);*/

					//clOrderDataInfo.siPara2 = 1;
					clOrderDataInfo.siPara2 = (SI16)IsHaveCushionItem(); //Para1���� ->����ũŸ��. - ���..
				}

				cltOrderData clOrderData;
				clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

				cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
				((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);

				
			}
		}
		break;

	case ORDER_DIE:
		InitPreGetOrder();
		clCurOrder.Set(&ReserveOrder);
		break;

	case ORDER_ATTACK_CLIENT:
		{
			// ������ ������ ĳ���͸� ������ �� �ִ�. 
			// ���� ������ �� �ִ�. 
			SI32 targetid  = ReserveOrder.siPara2;
			if(CanAttack(targetid))
			{
				InitPreGetOrder();
				clCurOrder.Set(&ReserveOrder);
				siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;

				SetAttack(targetid);

				//-------------------------------------
				// �̿��鿡�� �����϶�� ��û�� ������. 
				//-------------------------------------
				// ������ ��쿡��. 
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltOrderDataInfo clOrderDataInfo;
					if( pclClient->pclOrderManager->MakeOrder_ATTACK_CLIENT(&clOrderDataInfo, targetid, BY_PLAYER) == true)
					{
						cltOrderData clOrderData;
						clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

						cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
                        ((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
					}
				}

			}
		}
		break;

	case ORDER_SPECIAL_ACTION:
		{
			InitPreGetOrder();
			clCurOrder.Set(&ReserveOrder);

			clAniInfo.Init1();

			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				cltOrderDataInfo clOrderDataInfo;
				if( pclClient->pclOrderManager->MakeOrder_SPECIAL_ACTION(&clOrderDataInfo, ReserveOrder.siPara1, BY_PLAYER) == true)
				{
					cltOrderData clOrderData;
					clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

					cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
					((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
				}
			}
		}
		break;

	default:
		break;
		}
		
		ReserveOrder.siOrder	=	ORDER_WAIT;
		
		return FALSE;
}

// ����� ���ۿ� �ִ´�. 
BOOL cltCharCommon::PushOrder(cltOrderDataInfo order)
{

	if(ReserveOrder.siOrder		!=	ORDER_WAIT 
	&& ReserveOrder.siHostMode	!=	BY_COMPUTER
	&& order.siHostMode			==	BY_COMPUTER)
		return FALSE;
	
	ReserveOrder.Set(&order);
	
	return TRUE;
}
