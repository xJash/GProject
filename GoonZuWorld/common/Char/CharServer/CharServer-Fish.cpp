#include "..\Common\CommonHeader.h"
#include "..\..\Server\Server.h"

#include "char\CharServer\Char-Server.h"

#include "..\..\Client\Music\Music.h"

#include "..\Common\Bullet\Bullet.h"
#include "..\Common\Order\Order.h"
#include "..\CharManager\CharManager.h"
#include "Util\Util.h"
#include "Skill\Skill-Manager.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Fishing.h"
#include <MsgType-Person.h>
#include <MsgType-Item.h>
#include <MsgType-System.h>
#include <Msg/MsgType-ItemMall.h>
#include <Msg/MsgType-Fishing.h>
#include <Msg/MsgType-Agriculture.h>
#include "MsgRval-Define.h"

#include "../Common/Fishing/FishingMgr.h"

extern cltCommonLogic* pclClient;

// ����⸦ ��Ҵ�.
bool cltCharServer::CatchFishAction( bool IsPerson )
{
	cltServer* pclserver = (cltServer*)pclClient;

	if ( dwPreCatchFishClock < 1 )
	{
		dwPreCatchFishClock = pclClient->CurrentClock;

		return false;
	}

	if( TABS( pclClient->CurrentClock - dwPreCatchFishClock ) >=  100000 )		
	{
		
	}
	else
	{
		return false;
	}

	cltServer *pclServer = (cltServer *)pclClient; 
	



	//if(dwPreCatchFishClock >= 5 )
	//{
		dwPreCatchFishClock = pclClient->CurrentClock;
	//}
	
	
	
	// ���ô� �߿����������� ����.
	if ( pclCI->clBI.GetMapIndex() != 0 )
	{
		return false;
	}
	
	SI32 OwnerCharID				= 0;
	
	// ��ȹ�� ��� üũ
	SI32 FishSkillLevel				= 0;
	
	SI16 SpecialIncreaseSkillLevel	= 0;
	
	bool bFishNoSkillGoing			= false;

	// ��ų���Ѿ��� ���� ����Ʈ ���̶��
	SI16 siQuestType, siQuestUnique, siPara1, siPara2;
	SI16 siQuestClearCond = QUEST_CLEAR_COND_FISHNOSKILL;
	bFishNoSkillGoing = pclCI->clQuestInfo.IsQuestGoing(siQuestClearCond, &siQuestType, &siQuestUnique, &siPara1, &siPara2);

	
	// ��� ĳ���� ���.
	if ( IsPC( GetCharUnique() ) )
	{	
		OwnerCharID = GetID();
		
		if ( siFishingBaitItemUnique < 1 )
		{
			return false;
		}

#ifdef _SAFE_MEMORY
		FishSkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_FISH, 0, 0, &pclCI->clCharItem.clItem[0], OwnerCharID );
#else
		FishSkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_FISH, 0, 0, pclCI->clCharItem.clItem, OwnerCharID );
#endif
		
		if ( (FishSkillLevel < 1) && (false == bFishNoSkillGoing) )
		{
			return false;
		}
	}
	else
	{
		// ��ȯ���� ��� ������ ������ �˾ƾ���
		if ( clIdentity.clSummonInfo.siParentCharUnique < 1 )
		{
			return false;
		}
		
		OwnerCharID = pclClient->pclCM->GetIDFromCharUnique ( clIdentity.clSummonInfo.siParentCharUnique );
		
		if ( OwnerCharID < 1 || pclClient->pclCM->IsValidID( OwnerCharID ) == FALSE )
		{
			return false;
		}

		SI32 kind = GetKind();
		if(kind > 0 && kind < MAX_KIND_NUMBER)	
		{	
			SpecialIncreaseSkillLevel = pclClient->pclKindInfoSet->GetSubSkillLevel( kind, SUMMON_JOB_FISHING );
		}
		
		FishSkillLevel = pclCI->clIP.GetLevel() / 5 + pclKI->siSubSkillLevel;
		
		if ( FishSkillLevel < 1 )
		{
			FishSkillLevel = 1;
		}
				
		cltCharServer *OwnerChar = (cltCharServer*)pclClient->pclCM->CR[OwnerCharID];
		
		siFishingBaitItemUnique = OwnerChar->siFishingBaitItemUnique;
		if ( OwnerChar->siFishingBaitItemUnique < 1 )
		{
			FishingStop();
			return false;
		}
		else if ( OwnerChar->GetCurrentOrder() != ORDER_FISH )
		{
			FishingStop();
			return false;
		}
	}

	// ���� ��� �ʿ���� ����Ʈ ���� ���̸鼭 ��ų������ 10���� ������ ������ 10���� ����
	if ( (true == bFishNoSkillGoing) && (FishSkillLevel < 10) )
	{
		FishSkillLevel = 10;
	}
	
	// �� �������� ȹ�� ������ �������� Ref ����Ʈ�� ���  (�� ������ ���� �������� �ߺ����� �ִ� 30 �� ���� ���´ٰ� ���� ���� )
	SI32 AvailableGainFishKindListRef[ 30 ];
	memset( AvailableGainFishKindListRef, 0, sizeof( AvailableGainFishKindListRef ));
	
	SI16 AvailableGainFishKindListRefCounter = 0;
	
	// Ȳ�� ���ô븦 �����ϸ�, ��ų ���Ѿ��� ���� �� �ִ�. - by LEEKH 2008-09-03
	//[����] �̺�Ʈ �Ⱓ�� ������ ���ô븦 ������ ������ �ɷ��� �״�� ���� => 2008-9-5
	if( ITEMUNIQUE(17160) == pclCI->clCharItem.clItem[ActiveWeapon].siUnique /*||
		pclClient->pclEventTimeManager->InEventTime(TEXT("Fishing_Event"), &pclserver->sTime)*/	)
	{
		// ��ų���� 10000�� ���� ��ų�� üũ���� �ʴ´�.
		if ( ! pclClient->pclFishingMgr->GetAvailableGainFishKindListRef( siFishingBaitItemUnique, pclCI->clBI.GetX(), pclCI->clBI.GetY(),   10000, AvailableGainFishKindListRef, &AvailableGainFishKindListRefCounter ) )
		{
			return false;
		}
	}
	else
	{
		if ( ! pclClient->pclFishingMgr->GetAvailableGainFishKindListRef( siFishingBaitItemUnique, pclCI->clBI.GetX(), pclCI->clBI.GetY(), FishSkillLevel, AvailableGainFishKindListRef, &AvailableGainFishKindListRefCounter ) )
		{
			return false;
		}
	}

	if ( AvailableGainFishKindListRefCounter < 1 )
	{
		return false;
	}
	//}

	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		if ( 0 >= pclCI->clCharItem.clItem[ActiveWeapon].GetDurability() )
		{
			FishingStop();
			return false;
		}
	}
	
	SI32 RandSelectFishRef = AvailableGainFishKindListRef[ rand() % AvailableGainFishKindListRefCounter ];
	
	CFishKind *pFishKind = pclClient->pclFishingMgr->GetFishKindFromRef( RandSelectFishRef );
	
	if ( pFishKind == NULL )
	{
		return false;
	}
	
	SI16 EmptyPos = -1; 
	
	cltItem clFromItem;
	clFromItem.Init();
	clFromItem.siUnique = pFishKind->GetFishItemUnique();
	clFromItem.siItemNum = 1;

	///////////////////// ���ø� ���� ���ο� ������ ���///////////////////////
	bool getGodHandItem		= false;
	bool bGetGoldMineral	= false; 
	bool bGetBigItem		= false; 
	BOOL bGetValentainItem	= FALSE;

	if( pclClient->IsCountrySwitch(Switch_GodHandItem) )
	{
		SI32 fishingToolUnique = pclCI->clCharItem.clItem[ActiveWeapon].siUnique;
		// ���ڵ� ���ô�
		if( ITEMUNIQUE(17200) == fishingToolUnique )
		{
			SI32 value = rand() % 1000;
			if( value < 30 )
			{
				getGodHandItem = true;
				clFromItem.siUnique = ITEMUNIQUE(8074); 
				clFromItem.siItemNum = CalcTiredPoint(1);
			}
		}
		else if( ITEMUNIQUE(17100) == fishingToolUnique ||
				 ITEMUNIQUE(17150) == fishingToolUnique )
		{
			// �ڵ� ���ô� Ȯ���� �� ����
			if( bAutoFishing )
			{
				SI32 value = rand() % 1000;
				if( value < 5 )
				{
					getGodHandItem = true;
					clFromItem.siUnique = ITEMUNIQUE(8074); 
					clFromItem.siItemNum = CalcTiredPoint(1);
				}
			}
			else
			{
				SI32 value = rand() % 1000;
				if( value < 15 )
				{
					getGodHandItem = true;
					clFromItem.siUnique = ITEMUNIQUE(8074); 
					clFromItem.siItemNum = CalcTiredPoint(1);
				}
			}
		}
		// ���ڵ� �������� ���� �� �ϸ� �ݱ����� �ֵ��� �Ѵ�.
		if( false == getGodHandItem )
		{
			SI32 siGold = 0;
			if(pclClient->IsCountrySwitch(Switch_BigItemModify))
			{
				//siGold = CatchFish_BigItem(FishSkillLevel);
				if(siGold > 0)
				{
					bGetBigItem = true;
					clFromItem.siUnique = siGold;
					clFromItem.siItemNum = 1;
				}
			}
			else
			{
				siGold = CatchFish_GoldMineral(FishSkillLevel);
				if(siGold > 0)
				{
					bGetGoldMineral = true;
					clFromItem.siUnique = siGold;
					clFromItem.siItemNum = 1;
				}
			}
		}
	}
	else
	{
		///////////////////// 1%�� Ȯ���� �ݱ��� ȹ��/////////////////////// [����]
		// �ٴ��� ���� �ι���Ȯ���� �ݱ��� ȹ��
		SI32 siGold = 0;
		if(pclClient->IsCountrySwitch(Switch_BigItemModify))
		{
			//siGold = CatchFish_BigItem(FishSkillLevel);
			if(siGold > 0)
			{
				bGetBigItem = true;
				clFromItem.siUnique = siGold;
				clFromItem.siItemNum = 1;
			}
		}
		else
		{
			siGold = CatchFish_GoldMineral(FishSkillLevel);

			if(siGold > 0)
			{	
				bGetGoldMineral = true;
				clFromItem.siUnique = siGold;
				clFromItem.siItemNum = 1;
			}
		}
	}

	SI32 bigItemUnique = 0;
	SI32 siSpecial = 0;

	// ����ġ�� �ʿ� ��������.
	siSpecial = CatchFish_SpecialItem();

	if( siSpecial > 0 )
	{
		bGetValentainItem = TRUE;
		clFromItem.siUnique = siSpecial;
		bigItemUnique = siSpecial;
		clFromItem.siItemNum = 1;
	}

	cltItem clToItem;
	clToItem.Init();
	SI32 rtnvalue;
	
	// �������� ���� �� �ִ��� üũ
	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[OwnerCharID];
	if ( ! pclchar->CanAddInv(INVMODE_ALL, &clFromItem, &EmptyPos, &clToItem , &rtnvalue) )
	{
		((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL, clFromItem.siUnique, 0, GetCharUnique());
		
		FishingStop();
		
		return false;
	}
	
	SI32 CatchPercent = ( rand() * rand() ) % 100000;		// �̹��� ���� Ȯ��.
	SI32 RetVal = pFishKind->CatchFish( FishSkillLevel, CatchPercent, SpecialIncreaseSkillLevel );
	
	//[����] �̺�Ʈ �Ⱓ�� ������ ���ô븦 ������ ������ �ɷ��� �״�� ���� => 2008-9-5
	//if( pclClient->pclEventTimeManager->InEventTime(TEXT("Fishing_Event"), &pclserver->sTime) )
	{
		//[����] Ȳ�� ���ô�. 100% ���´�. => 2008-8-12
		if( ITEMUNIQUE(17160) == pclCI->clCharItem.clItem[ActiveWeapon].siUnique )
		{
			//RetVal = FISHING_SUCCESS;

			// Ȯ�� ���ô�� �������� �ʴ´�. �ּ��� �Ѱ��� �����Ѵ�. - by LEEKH 2008-09-03
			if(RetVal < FISHING_GET_GOLD)		RetVal = FISHING_SUCCESS;
		}
	}

	// ��ǰ�� �������� ���ҽ�Ų��. 
	//DecreaseSkillItemEquipDur(SKILL_FISH, false);

	// ��������Ƿ� ������ ������ ���� - Ȯ�� 25%
	if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		if( IsPC( GetCharUnique()) )
		{
			SI32 siRand = rand() % 100;
			if( siRand < 25 )
			{
				DecreaseEquipDur( ActiveWeapon,  1 );
				// ���ý�ų�� ���õ� �������� �������� �����Ѵ�.
				DecreaseSkillItemEquipDur( SKILL_FISH );
			}

			if ( 0 >= pclCI->clCharItem.clItem[ActiveWeapon].GetDurability() )
			{
				UseItemReasonDurabilityZero( ActiveWeapon );
			}
		}
	}

	if ( RetVal < FISHING_SUCCESS )
	{
		cltItem clTempItem;
		clTempItem.Init();
		
		/*cltGameMsgResponse_FishingGetMarineProducts clGameMsgResponse_FishingGetMarineProducts
			(
			RetVal,
			pFishKind->GetFishItemUnique(),
			0,
			&clTempItem,
			GetKind()
			);
		cltMsg clMsg( GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTS, sizeof( clGameMsgResponse_FishingGetMarineProducts ),(BYTE*)&clGameMsgResponse_FishingGetMarineProducts );
		pclClient->pclCM->CR[OwnerCharID]->SendNetMsg((sPacketHeader*)&clMsg );*/
		
		cltGameMsgResponse_FishingGetMarineProductsNotify clGameMsgResponse_FishingGetMarineProductsNotify
			(
			//KHY - 0512 -  �Ƿε� �߰�.
			CalcTiredPoint(RetVal), 
			pFishKind->GetFishItemUnique(),
			0,
			GetCharUnique(),
			GetKind()
			);
		cltMsg clMsg1( GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTSNOTIFY, sizeof( clGameMsgResponse_FishingGetMarineProductsNotify ),(BYTE*)&clGameMsgResponse_FishingGetMarineProductsNotify );
		SendNeighbourMsg( &clMsg1 , true);
	}
	else
	{
		// ���������ϱ� ������ �߰��ϰ�...
		// ������ �߰��Ҷ� �� ���� ���� ���� �ϰ���... 
		// DB �޽��� ��������..
		cltItem clTempItem;
		clTempItem.siItemNum = RetVal;
		clTempItem.siUnique = pFishKind->GetFishItemUnique();
		
		// �ݱ��� ������
		if(bGetGoldMineral)
		{
			clTempItem.siUnique = ITEMUNIQUE(5040);
			clTempItem.siItemNum = 1;
		}

		// ��� ������
		if( bGetBigItem )
		{
			clTempItem.siUnique = clFromItem.siUnique;
			clTempItem.siItemNum = clFromItem.siItemNum;
		}

		//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
		if( bGetValentainItem )
		{
			clTempItem.siUnique = bigItemUnique;
			clTempItem.siItemNum = 1;
		}

		// �ٴ��� ���� �Ϻ��� �ִ�
		if( pclServer->bSpecailDay9switch == true )
		{
			clTempItem.siItemNum *= 2;
		}

		if( getGodHandItem )
		{
			clTempItem.siUnique = ITEMUNIQUE(8074); 
			clTempItem.siItemNum = CalcTiredPoint(1);
		}

		if( bGetBigItem == false && bGetGoldMineral== false && bGetValentainItem == false && getGodHandItem == false )
		{
			// ���� ���� �̺�Ʈ ������ ȹ���߰�
			SI32 Bonus = 1;
			if( pclserver->pclEventTimeManager->InEventTime("GoonzuDay_CollectionItem2_0", &pclserver->sTime) )
			{
				cltEventTime* pclEventTime = pclserver->pclEventTimeManager->GetEvent("GoonzuDay_CollectionItem2_0");
				if(pclEventTime)	{		Bonus = pclEventTime->m_siBonusAmount;		}
			}
			if( pclserver->pclEventTimeManager->InEventTime("GoonzuDay_CollectionItem2_3", &pclserver->sTime) )
			{
				cltEventTime* pclEventTime = pclserver->pclEventTimeManager->GetEvent("GoonzuDay_CollectionItem2_3");
				if(pclEventTime)	{		Bonus = pclEventTime->m_siBonusAmount;		}
			}

			if(pclClient->IsCountrySwitch(Switch_Server_Event))
			{
				//[����] ���� �̺�Ʈ �Ϸ� 1�� �����̸� ������ ����ȴ�. => 2008-6-27
				// ���� Ÿ��Ȯ��.
				if( pclClient->pclServerEventManager->GetBonusBufType() == CNServerEvent_Manager::SERVER_EVENT_BUF_ETC)
				{
					Bonus *= 2;
				}
			}

			clTempItem.siItemNum *= Bonus;
		}

		//[����] �̺�Ʈ �Ⱓ�� ������ ���ô븦 ������ ������ �ɷ��� �״�� ���� => 2008-9-5
		//if( pclClient->pclEventTimeManager->InEventTime(TEXT("Fishing_Event"), &pclserver->sTime) )
		{
			//[����] Ȳ�� ���ô�. ���� ���� ȹ��. => 2008-8-12
			if( ITEMUNIQUE(17160) == pclCI->clCharItem.clItem[ActiveWeapon].siUnique )
			{
				SI32 value = rand() % 100;
				bool bGiveBox = false;
				if( value < 10 )
				{
					bGiveBox = true;
					clTempItem.siUnique  = ITEMUNIQUE(13326); 
					clTempItem.siItemNum = 1;
				}
				value = rand() % 100;
				if( false == bGiveBox && value < 5 )
				{
					clTempItem.siItemNum *= 2;
				}
			}
			/* [����] �Ϲ� ���ô뿡���� ���� ���� ȹ�� ���ϵ��� ����
			else	//[����] �Ϲ� ���÷ε� 0.5%�� ���� ���� ȹ��.
			{
				SI32 value = rand() % 1000;
				bool bGiveBox = false;
				if( value < 5 )
				{
					bGiveBox = true;
					clTempItem.siUnique  = ITEMUNIQUE(13326); 
					clTempItem.siItemNum = 1;
				}
			}
			*/
		}

		//KHY - 0512 -  �Ƿε� �߰�.
		clTempItem.siItemNum = CalcTiredPoint(clTempItem.siItemNum);

		// ����� ��� ��� ����ġ �÷��ָ� ��
		if ( IsPerson )
		{	
			cltItem clToItem;
			clToItem.Init();
			SI32 rtnvalue;

			// �������� ���� �� �ִ��� üũ
			if ( ! pclchar->CanAddInv(INVMODE_ALL, &clTempItem, &EmptyPos, &clToItem , &rtnvalue) )
			{
				((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL, clTempItem.siUnique, 0, GetCharUnique());

				FishingStop();

				return false;
			}

			sDBRequest_FishingGetMarineProducts clMsg
				(
				pclClient->pclCM->CR[OwnerCharID]->pclCI->GetPersonID(),
				OwnerCharID,		
				EmptyPos,
				&clTempItem,
				clTempItem.IsCreateSID(pclServer->pclItemManager),
				SKILL_FISH,
				0,
				GetCharUnique(),
				GetKind()
				);
			pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
			cltCharServer *pclChar = (cltCharServer *)pclClient->pclCM->CR[OwnerCharID];
			if ( NULL == pclChar )
			{
				return false;
			}
			

			// �ݱ����� �޾� ���� ��쿡�� �������ġ 5
			// - ��� ������ �߰� -
			if(bGetGoldMineral || bGetBigItem)
				pFishKind->m_stFishInfo.siIncFishingSkillExp = 5;

			// �ٴ��� ���� ��ȹ ����ġ 2�� 			
			SI32 skillExp = pFishKind->m_stFishInfo.siIncFishingSkillExp;
			if( pclServer->bSpecailDay9switch == true )
			{
				skillExp *= 2;
			}

			pclChar->SetSkillUpdate( SKILL_FISH, skillExp );
			
			
			// [����] ����Ʈ ������ ����
			if ( 0 < pclChar->siQuestCount )
			{
				clTempItem.siItemNum = pclChar->siQuestCount;
			}

			// ��������Ʈ ���̶��
			IncQuestPara(QUEST_CLEAR_COND_FISH, clTempItem.siUnique, clTempItem.siItemNum);
			// ��ų �ʿ���� ���� ����Ʈ ���̶��
			IncQuestPara(QUEST_CLEAR_COND_FISHNOSKILL, clTempItem.siUnique, clTempItem.siItemNum);

			if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();
				if ( pclSE_Quest )
				{
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_FISH, clTempItem.siUnique, clTempItem.siItemNum );
				}
			}
		}
		else		// ��ȯ���� ��� ( ��ų ����ġ�� �ƴ϶�, �Ϲ� ����ġ �÷��� )
		{
			sDBRequest_FishingGetMarineProducts clMsg
				(
				pclClient->pclCM->CR[OwnerCharID]->pclCI->GetPersonID(),
				OwnerCharID,		
				EmptyPos,
				&clTempItem,
				clTempItem.IsCreateSID(pclServer->pclItemManager),
				SKILL_FISH,
				0,						// ��ȯ���� �������ϱ� ��� ����ġ �÷��� �ʿ� ����.
				GetCharUnique(),
				GetKind()
				);
			pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			
			// ��ȯ�� ����ġ �÷��ִ� �κ�
			// - ��� ������ �߰� -
			if(bGetGoldMineral || bGetBigItem)
				pFishKind->m_stFishInfo.siIncFishingSkillExp = 5;

			IncreaseExp( (int)( pFishKind->m_stFishInfo.siIncFishingSkillExp * 1.5 ) );// SI32->SI64 ����ġ �����÷ο춧���� ����	
		}
	}
	
	return true;
	
}

SI32 cltCharServer::CatchFish_GoldMineral(SI32 FishSkillLevel)
{
	cltServer* pclServer = (cltServer*)pclClient;

	SI32 siGoldMineral = 0;

	// �߱��϶��� 0�� ���� 
	if( pclServer->siServiceArea == ConstServiceArea_NHNChina )	return siGoldMineral	;

	// �ٴ��� ���� �ι���Ȯ���� �ݱ��� ȹ��
	if( pclServer->bSpecailDay9switch == true )
	{
		if( (pclClient->GetFrame() + rand())% 50 == 0  && FishSkillLevel >= 10)
		{
			siGoldMineral = ITEMUNIQUE(5040); 
		}
	}
	else
	{
		if( (pclClient->GetFrame() + rand())% 100 == 0  && FishSkillLevel >= 10)
		{
			siGoldMineral = ITEMUNIQUE(5040); 
		}
	}

	return siGoldMineral;
}

SI32 cltCharServer::CatchFish_SpecialItem()
{
	cltServer* pclServer = (cltServer*)pclClient;

	SI32 bigItemUnique = 0;

	NDate Today;
	Today.SetDate( pclServer->sTime.wYear, pclServer->sTime.wMonth, pclServer->sTime.wDay );

	//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
	if ( Today.GetDateVary() >= pclServer->clValentineEventStart.GetDateVary() &&
		Today.GetDateVary() <= pclServer->clValentineEventEnd.GetDateVary() )
	{	
		SI32 randValue = rand() % 100;

		if( randValue < pclServer->siValentineFish )
		{
			bigItemUnique = ITEMUNIQUE(13008);  //L ī��.
		}	
	}

	//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
	if ( Today.GetDateVary() >= pclServer->clWhiteEventStart.GetDateVary() &&
		Today.GetDateVary() <= pclServer->clWhiteEventEnd.GetDateVary() )
	{	
		SI32 randValue = rand() % 100;

		if( randValue < pclServer->siWhiteFish )
		{
			bigItemUnique = ITEMUNIQUE(13018);  //L ī��.
		}	
	}
	//////////////////////////////////////////////////////////////////////

	return bigItemUnique;
}

SI32 cltCharServer::CatchFish_BigItem(SI32 FishSkillLevel)
{
	cltServer* pclServer = (cltServer*)pclClient;

	REAL32 fConstantLuck = 7.0f;
	REAL32 fConstantSkill = 3.0f;

	SI32 siLuck = clPB.clTotalBA.GetLuk() * ( fConstantLuck + clPB.clTotalBA.GetLuk() / 100.0f ) 
				+ FishSkillLevel * ( fConstantSkill + FishSkillLevel / 100.0f );

    SI32 siRand = rand() % 20000;

	SI32 siBigItem = 0;

	if( siRand < siLuck )
	{
		siBigItem = ITEMUNIQUE(13328);
	}

	return siBigItem;
}

// ����� ��⸦ �����Ѵ�.
bool cltCharServer::FishingStart( SI32 FishingBaitItemUnique )
{
	cltItem clItem;
	clItem.siItemNum = 1;
	clItem.siUnique = FishingBaitItemUnique;
	
	SI32 InvPos = pclCI->clCharItem.GetItemPos( FishingBaitItemUnique );
	if ( InvPos < 0 )
	{
		return false;
	}
	
	cltItem *pclFrom = &pclCI->clCharItem.clItem[ InvPos ];
	
	while( clItemUseReserveInfo.Push( clItem.siUnique, -clItem.siItemNum, InvPos ) == false )
	{
		ItemUseReserveAction();
	}
	
	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	if( pclFrom->siItemNum == 1 )
	{
		ItemUseReserveAction();
	}
	// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
	// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
	UseItem( clItem );		// ������ ���
	pclFrom->Decrease(1);
	// Ŭ���̾�Ʈ�� ����� ������ ������. 
	cltGameMsgResponse_PersonItemInfo clinfo( InvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
	SendNetMsg((sPacketHeader*)&clMsg);

	return true;
}

// ������ ����Ѵ�.
bool cltCharServer::GetFishingToolInfo( SI16 FishKindListRef, DBToolInfo *pFishingToolList )
{
	cltServer* pclserver = (cltServer*)pclClient;

	CFishKind *pFishKind = pclClient->pclFishingMgr->GetFishKindFromRef( FishKindListRef );
	
	if ( pFishKind == NULL )
	{
		return false;
	}

	SI32 *FishingTollItemUniqueListPtr = pFishKind->GetFishingToolItemUniqueListPtr();

	SI16 ItemPos = -1;
	SI32 Durability = 0;

	SI16 FishingToolCounter = 0;

	cltItem clTempItem;

	SI32 FishClassification = pFishKind->m_stFishInfo.siFishingRodAtb;

	SI32 NotExistFishingToolItemUnique = 0;
	SI32 NotUsingDurabilityFishingToolItemUnique = 0;
	SI32 FindClassification = 0;
	
	SI32 UseAbleDay	= 0;
	BOOL bUseAble	= FALSE;

	for ( SI16 i = 0; i < MAX_FISHING_TOOL_NUMBER; ++i )
	{
		if ( FishingTollItemUniqueListPtr[ i ] > 0 )
		{
			ItemPos = -1;
			Durability = 0;
			
			//ItemPos = pclCI->clCharItem.GetItemPos( FishingTollItemUniqueListPtr[ i ] );
			if ( pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique == FishingTollItemUniqueListPtr[ i ] )
			{
				ItemPos = ActiveWeapon;
				bUseAble = pclserver->GetItemUseAbleDay(&pclCI->clCharItem.clItem[ ActiveWeapon ], &UseAbleDay);

				// �������� 0�̸� ���� ����
				if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
				{
					if ( 0 >= pclCI->clCharItem.clItem[ActiveWeapon].GetDurability() )
					{
						bUseAble = FALSE;
					}
				}
			}
			else
			{
				ItemPos = -1;
			}
			
			// PCK : ���ô��� ���Ⱓ�� �������� ���ø� ���Ѵ�. (09.01.13)
			if(bUseAble == FALSE) continue;
			if(UseAbleDay < 0) return false;

			if ( ItemPos < 0 )
			{
				// ������� �� ������ �Ӽ��� ���ؼ� ã�� ���� ����.
				if ( FindClassification & FishClassification )
				{
					continue;
				}
				
				if ( NotExistFishingToolItemUnique == 0 )
				{
					NotExistFishingToolItemUnique = FishingTollItemUniqueListPtr[ i ];
				}

				continue;
			}
			
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclCI->clCharItem.clItem[ItemPos].siUnique );
			if( ref <= 0 )
				return false;
			
			if ( FishClassification & pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification )
			{
			/*	Durability = pclCI->clCharItem.clItem[ ItemPos ].GetDurability(  );
				
				if ( FISHING_TOOL_DURABILITY_DECREASE >= Durability )
				{
					if ( NotUsingDurabilityFishingToolItemUnique == 0 )
					{
						NotUsingDurabilityFishingToolItemUnique = FishingTollItemUniqueListPtr[ i ];
					}

					continue;
				}*/

				clTempItem.Set( &pclCI->clCharItem.clItem[ ItemPos ] );
								
			//	clTempItem.DecreaseDurability( pclClient->pclItemManager, FISHING_TOOL_DURABILITY_DECREASE );
				
				if ( clTempItem.siItemNum == 0 )
				{
					clTempItem.siUnique = pclCI->clCharItem.clItem[ ItemPos ].siUnique;
				}
				
				pFishingToolList[ FishingToolCounter ++ ].Set( ItemPos, &clTempItem );

				// ������� ã�� �з��� �����Ѵ�.
				FishClassification -= pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification;

				// ������� ã�� �з��� �߰��Ѵ�.
				FindClassification +=pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification;

				NotExistFishingToolItemUnique = 0;
				NotUsingDurabilityFishingToolItemUnique = 0;
				
				if ( FishClassification == 0 )
				{
					return true;
				}
			}
			else
			{
				continue;
			}
		}
	}	

	// � ��� ��� ���ø� �� �� �����ϴ�.
	if ( NotExistFishingToolItemUnique > 0 )
	{
		((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHTOOLNOTEXIST, NotExistFishingToolItemUnique, 0, GetCharUnique());
	}

/*	// � ��� �������� ���Ƽ� ���ø� �� �� �����ϴ�.
	if ( NotUsingDurabilityFishingToolItemUnique > 0 )
	{
		((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHTOOLNOTENOUGHDURABILITY, NotUsingDurabilityFishingToolItemUnique, 0, GetCharUnique());
	}
*/
	return false;
}

bool cltCharServer::IsAvailableFishing( SI32 FishingBaitItemUnique, SI16 FishKindListRef )
{
	cltServer* pclserver = (cltServer*)pclClient;

	if ( FishKindListRef < 0 )
	{
		return false;
	}

	// �̳��� ���Ǵ� �������� ���� �ִ��� üũ
	SI32 BaitItemPos = pclCI->clCharItem.GetItemPos( FishingBaitItemUnique );

	if ( BaitItemPos < 0 )
	{
		return false;
	}

	CFishKind *pFishKind = pclClient->pclFishingMgr->GetFishKindFromRef( FishKindListRef );
	SI32 *FishingTollItemUniqueListPtr = pFishKind->GetFishingToolItemUniqueListPtr();

	SI16 ItemPos = -1;
	SI32 Durability = 0;

	SI32 FishClassification = pFishKind->m_stFishInfo.siFishingRodAtb;
	
	SI32 NotExistFishingToolItemUnique = 0;
	SI32 NotUsingDurabilityFishingToolItemUnique = 0;
	SI32 FindClassification = 0;
	
	SI32 UseAbleDay	= 0;
	BOOL bUseAble	= FALSE;

	for ( SI16 i = 0; i < MAX_FISHING_TOOL_NUMBER; ++i )
	{
		if ( FishingTollItemUniqueListPtr[ i ] > 0 )
		{
			ItemPos = -1;
			Durability = 0;
			
			//ItemPos = pclCI->clCharItem.GetItemPos( FishingTollItemUniqueListPtr[ i ] );			
			if ( pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique == FishingTollItemUniqueListPtr[ i ] )
			{
				ItemPos = ActiveWeapon;
				bUseAble = pclserver->GetItemUseAbleDay(&pclCI->clCharItem.clItem[ ActiveWeapon ], &UseAbleDay);
			}
			else
			{
				ItemPos = -1;
			}
			
			// PCK : ���ô��� ���Ⱓ�� �������� ���ø� ���Ѵ�. (09.01.13)
			if(bUseAble == FALSE) continue;
			if(UseAbleDay < 0) return false;

			if ( ItemPos < 0 )
			{
				// ������� �� ������ �Ӽ��� ���ؼ� ã�� ���� ����.
				if ( FindClassification & FishClassification )
				{
					continue;
				}
				
				if ( NotExistFishingToolItemUnique == 0 )
				{
					NotExistFishingToolItemUnique = FishingTollItemUniqueListPtr[ i ];
				}
				
				continue;
			}

			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclCI->clCharItem.clItem[ItemPos].siUnique );
			if( ref <= 0 )
				return false;

			if ( FishClassification & pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification )
			{
			/*	Durability = pclCI->clCharItem.clItem[ ItemPos ].GetDurability(  );
				
				if ( FISHING_TOOL_DURABILITY_DECREASE >= Durability )
				{
					if ( NotUsingDurabilityFishingToolItemUnique == 0 )
					{
						NotUsingDurabilityFishingToolItemUnique = FishingTollItemUniqueListPtr[ i ];
					}

					continue;
				}*/
				
				// ������� ã�� �з��� �����Ѵ�.
				FishClassification -= pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification;

				// ������� ã�� �з��� �߰��Ѵ�.
				FindClassification +=pclClient->pclItemManager->pclItemInfo[ref]->siFishClassification;
				
				NotExistFishingToolItemUnique = 0;
				NotUsingDurabilityFishingToolItemUnique = 0;
				
				if ( FishClassification == 0 )
				{
					return true;
				}
			}
			else
			{
				continue;
			}
		}
	}

	// � ��� ��� ���ø� �� �� �����ϴ�.
	if ( NotExistFishingToolItemUnique > 0 )
	{
		((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHTOOLNOTEXIST, NotExistFishingToolItemUnique, 0, GetCharUnique());
	}

/*	// � ��� �������� ���Ƽ� ���ø� �� �� �����ϴ�.
	if ( NotUsingDurabilityFishingToolItemUnique > 0 )
	{
		((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHTOOLNOTENOUGHDURABILITY, NotUsingDurabilityFishingToolItemUnique, 0, GetCharUnique());
	}
*/	
	return false;
}

void cltCharServer::FishingStop()
{
	if ( bAutoFishing )
	{
		// ���� �ߴ�
		siFishingBaitItemUnique = 0;
		OrderForceStop( GetID(), BY_PLAYER );
		
		bAutoFishing = false;
		
		cltGameMsgResponse_AgricultureAutoGain clGameMsgResponse_AgricultureAutoGain( AGRICULTURE_TYPE_FISH, false );
		cltMsg clMsg( GAMEMSG_RESPONSE_AGRICULTUREAUTOGAIN, sizeof( clGameMsgResponse_AgricultureAutoGain ), (BYTE*)&clGameMsgResponse_AgricultureAutoGain );
		SendNetMsg((sPacketHeader*)&clMsg );
	}
	else
	{
		siFishingBaitItemUnique = 0;
		OrderForceStop( GetID(), BY_PLAYER );
	}

	return;
}
