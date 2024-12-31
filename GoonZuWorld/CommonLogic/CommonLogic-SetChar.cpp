#include "..\Client\Client.h"


//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Map\Map.h"
#include "..\Common\Order\Order.h"
#include "Char\CharManager\CharManager.h"

#include "MsgType-System.h"
#include "Msg/MsgType-PersonalShop.h"
#include "Msg/MsgType-Vote.h"
#include "Feast/Feast.h"
#include "MsgType-Person.h"
#include "MsgType-Item.h"
#include "..\Common\Char\KindInfo\KindInfo.h"

// 가장 기본이 되는 캐릭터를 생성한다. 
bool cltCommonLogic::MakeSimpleChar(SI32 id, SI32 charunique)
{
	SI32 childcharunique	= 0;
	SI32 summonindex		= 0;
	SI32 life				= 1;
	cltIdentity				clIdentity;

	cltBufInfo clBufInfo;
	clBufInfo.Init();
	cltMakeCharInfo clinfo(KIND_SYSTEM, charunique, 1, life, 0, 0, 0, childcharunique, summonindex, 
							false, false, false, false,false,false,false ,false , 
							0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL,NULL,0, NULL, 
							NULL, NULL, false, false, 0, false, 0 ,NULL, NULL, 
							false, 0, false, false, false, false, 0, 0,NULL, false,NULL
							,0,0,0,0,0,0,0,0,0,0,false, &clBufInfo
							);
	SetChar(id, &clinfo);

	return true;
}

// 일반 캐릭터를 설정한다. 
SI32 cltCommonLogic::SetChar(SI32 id, cltMakeCharInfo* pclinfo, cltGMCommandKindInfo* pclGMCommandKindInfo)
{
	if(pclinfo == NULL)return 0;
	if(id == 0)	return 0;
	if(pclinfo->uiMakeCharKind < 0 || pclinfo->uiMakeCharKind >= MAX_KIND_NUMBER)		return 0;
	if( pclKindInfoSet->pclKI[ pclinfo->uiMakeCharKind ] == NULL	)					return 0;

	cltPersonInfo			charinfo;
	cltInnerStatusInfo		clInnerStatus;

	charinfo.clBI.SetKind(pclinfo->uiMakeCharKind);
	charinfo.clBI.siHomeVillage	= pclinfo->siHomeVillageUnique;
	charinfo.clBI.SetX(pclinfo->uiX);
	charinfo.clBI.SetY(pclinfo->uiY);
	charinfo.clBI.SetMapIndex(pclinfo->uiMapIndex);

	charinfo.clBI.uiGMMode	= pclinfo->uiGMMode;
	charinfo.clBI.bPCRoom	= pclinfo->bPCRoom;

	// CMT로 생성한 캐릭터는 pclGMCommandKindInfo를 근거로 데이터를 얻어온다.
	if(pclGMCommandKindInfo)
	{
		charinfo.clIP.SetBasicAbility(&pclGMCommandKindInfo->clBA);
	}
	else
	{
		// BasicAbility능력치는 cltKindInfo를 근거로 얻어온다. 
		charinfo.clIP.SetBasicAbility(&pclKindInfoSet->pclKI[ pclinfo->uiMakeCharKind ]->clBA);
	}

	// 인던 몬스터 능력치 하드코딩
	if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_RACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(5, 40));			}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_KINGRACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(150, 290));			}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_RACCOONLORD_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(100, 145));			}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_ZORRORACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(60, 120));			}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_SANTARACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(300, 431));		}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_MAGICALRACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(30, 100));		}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_RACCOONTOWER_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(350, 450));		}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_MAMARACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(1150, 2000));		}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_BIGRACCOON_AGIT") )
	{		charinfo.clIP.SetVit(RandomInt(5000, 7000));		}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_KEY_RACCOON") )
	{		charinfo.clIP.SetVit(RandomInt(250, 350));			}
	else if(pclinfo->uiMakeCharKind == (UI32)pclClient->GetUniqueFromHash("KIND_GMONBONUS") )
	{		charinfo.clIP.SetVit(RandomInt(625, 750));			}

	charinfo.clIP.SetLevel(pclinfo->uiLevel);

	//-----------------------------------
	// 레벨에 의한 스테이터스 가중치를 반영한다.  - 시즌2 삭제.
	//-----------------------------------
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange) == false)
	{
		charinfo.clIP.SetStr(charinfo.clIP.GetStr() + (pclinfo->uiLevel - 1)*2);
		charinfo.clIP.SetDex(charinfo.clIP.GetDex() + (pclinfo->uiLevel - 1));

		if(charinfo.clIP.GetMag())
		{
			charinfo.clIP.SetMag(charinfo.clIP.GetMag() + (pclinfo->uiLevel - 1));
		}

		charinfo.clIP.SetVit(charinfo.clIP.GetVit() + (pclinfo->uiLevel - 1));
	}

	// InitCharClient() 함수에서 정보를 사용하기 위해서 먼저 설정한다.
	pclCM->CR[id]->clTransFormInfo.uiNowTransFormKind	= pclinfo->uiNowTransFormKind;
	pclCM->CR[id]->clTransFormInfo.bTransFormMode		= pclinfo->bTransFormMode;

	pclCM->CR[id]->clTransFormInfo.bTransForm100Effect		= pclinfo->bTransForm100Effect;

	// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
	pclCM->CR[id]->uiBestGuild = pclinfo->uiBestGuild;

	id = SetChar1(id, pclinfo->uiMakeCharUnique, pclinfo->uiChildCharUnique, pclinfo->uiSummonIndex, &pclinfo->clIdentity, &charinfo, &pclinfo->clInnerStatus, pclinfo->siSoulGuardUnique);
	if(id)
	{
		// 주어진 체력이 있다면 체력을 설정하고, 
		if(pclinfo->uiLife)
		{
			pclCM->CR[id]->SetLife( pclinfo->uiLife);
		}
		// 주어진 체력이 없다면 최대값으로 설정한다. 
		else
		{
			pclCM->CR[id]->SetLife( pclCM->CR[id]->clPB.GetMaxLife());
		}

		// 마법력은 보이지 않는 것이므로 최대값으로 설정한다. 
		pclCM->CR[id]->SetMana(pclCM->CR[id]->clPB.GetMaxMana());

		pclCM->CR[id]->siPersonalMakeItemType = pclinfo->siMakeAniType;
		pclCM->CR[id]->SetEnchantEffect(pclinfo->siMakeAniType);
	}
	// PC이면 장비 정보를 기억하고 있는다. 
	// 클라이언트 주인공에게는 장비코드가 없어야 한다. 

	// 클라이언트의 주인공인 경우에는 자신이 소지한 실제 아이템을 근거로 복장정보를 얻어야 하기 때문에 
	// 이런 복장 유니크를 기억해서는 안된다. 
	if(GameMode == GAMEMODE_CLIENT)
	{
		// 주소지 정보를 업데이트 한다. 
		pclCM->CR[id]->pclCI->clBI.siHomeVillage = pclinfo->siHomeVillageUnique;
		// 학교 정보를 업데이트 한다. 
		pclCM->CR[id]->pclCI->clBI.siSchoolUnique = pclinfo->uiSchoolUnique;
		// 성별을 입력한다. 
		pclCM->CR[id]->pclCI->clBI.uiSex = pclinfo->uiSex;


		// 찜정보를 업데이트 한다. 
		pclCM->CR[id]->clJim.Init();
		pclCM->CR[id]->clJim.SetBeJimed(pclinfo->siJimCharUnique, 1);

		// 찜 정보를 화면에 표시한다. 
		pclCM->CR[id]->SetJimShow();

		// 주인공이 아니면, 
		// 서버로 부터 받은 정보를 근거로 캐릭터를 설정한다. 
		// 주인공은 더욱 상세한 정보를 근거로 캐릭터를 설정해야 한다. 
		if(id != 1)
		{
			if(IsPC(pclinfo->uiMakeCharUnique))
			{
				pclCM->CR[id]->clPB.clShapeEquip.Set(&pclinfo->clShapeEquip);

				pclCM->CR[id]->clPB.GivenMoveSpeed	= pclinfo->uiTotalMoveSpeed;

				// 말을 설정한다. 
				cltHorse* pclhorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
				if(pclhorse)	pclhorse->siHorseUnique	= pclinfo->uiHorseUnique1;
			}

		}

		// 머릿말이 있으면 서버로 머릿말을 요청한다. 
		if(pclinfo->uiHeadChatSwitch)
		{
			cltGameMsgRequest_HeadChat clinfo(pclCM->CR[id]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_REQUEST_HEADCHAT, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);

		}
		// 개인상점이 있으면 개인 상점을 요청한다.
		if(pclinfo->uiPersonalShopSwitch)
		{
			cltGameMsgRequest_PersonalShopBanner clinfo(pclCM->CR[id]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_REQUEST_PERSONALSHOPBANNER, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);
		}

		// [영훈] 선거 시스템 : 유세띠 정보를 다시 받음
		if ( pclinfo->uiElectionStump )
		{
			cltGameMsgRequest_ElectionStump clinfo( pclCM->CR[id]->GetCharUnique() );
			cltMsg clMsg(GAMEMSG_REQUEST_ELECTIONSTUMP, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);
		}

		// 수리의뢰가 있으면 정보를 요청한다.
		if( pclinfo->uiRepairShopSwitch )
		{
			cltGameMsgRequest_NewItemRepairRequestInfo clinfo(pclCM->CR[id]->GetCharUnique(), NEWITEMREPAIR_INFO_BANNER);
			cltMsg clMsg(GAMEMSG_REQUEST_NEWITEMREPAIRREQUESTINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);
		}

		
		//[진성] 캐릭터 정보를 얻을때 전체 버프를 세팅 
		pclCM->CR[id]->pclCI->clBI.clBufInfo.SetBuf( &pclinfo->m_clBufInfo );

		// 선공 방어 상황을 업데이트 
		pclCM->CR[id]->bNoFirstAttackSwitch 				= pclinfo->uiNoFirstAttackSwitch;
		// ICE 방어 상황을 Update
		pclCM->CR[id]->bNoIceAttackSwitch					= pclinfo->uiNoIceAttackSwitch;
		// 하트 이펙트 업데이트
		pclCM->CR[id]->bHeartEffectSwitch					= pclinfo->uiHeartEffectSwitch;
		// 네잎 클로버 이펙트 업데이트
		pclCM->CR[id]->bFourLeafSwitch						= pclinfo->uiFourLeafSwitch;
		((cltCharClient*)pclCM->CR[id])->siCushionUnique	= pclinfo->uiCusionSwitch;

		pclCM->CR[id]->siBufTransformKind					= pclinfo->siBufTransformKind;
		pclCM->CR[id]->siEnemUnique							= pclinfo->siEnemyUnique;

		pclCM->CR[id]->bElixirSwitch						= pclinfo->uiElixir;

		// 추가 정보를 필요로 하면, 
		if(pclinfo->uiRequestAddinfo)
		{
			// 서버로 추가 정보를 요청한다. 
			cltMsg clMsg(GAMEMSG_REQUEST_ADDINFO, pclCM->CR[id]->GetCharUnique());
			SendMsgToServer((sPacketHeader*)&clMsg);
		}	

		pclCM->CR[id]->m_siSetItemType = pclinfo->clShapeEquip.siCompletedSetItemIndex;
		pclCM->CR[id]->m_siSetItemStep = pclinfo->clShapeEquip.siCompletedSetItemIndexStep;

		pclCM->CR[id]->m_siSetItemType2 = pclinfo->clShapeEquip.siCompletedSetItemIndex2;
		pclCM->CR[id]->m_siSetItemStep2 = pclinfo->clShapeEquip.siCompletedSetItemIndexStep2;

		// 길드 정보
		pclCM->CR[id]->pclCI->clBI.clGuildRank.Set(&pclinfo->clGuildRank);
		pclCM->CR[id]->pclCI->clPersonNaming.Set(&pclinfo->clPersonNaming);	
		// 발렌타인데이
		if( pclCM->CR[id]->pclValentineWar )	pclCM->CR[id]->pclValentineWar->Set(&pclinfo->clValentineWarInfo);

		pclCM->CR[id]->m_uiWeaponSkillMasterEmblem = pclinfo->uiWeaponSkillMasterEmblem;
		
		if ( IsPC(pclinfo->uiMakeCharUnique) && (pclCM->CR[id]->pclMarriage) )
		{
			pclCM->CR[id]->pclMarriage->SetLoveLevel( pclinfo->siDisplayLoveLevel );
		}
		
	}	
	SI32 unique;

	unique = pclinfo->clShapeEquip.clArmour.uiUnique;

	if(unique)
	{
		pclCM->CR[id]->ChangeArmCode(/*PERSONITEM_ARMOUR*/ pclCM->CR[id]->ActiveClothes, unique);
	}
	unique = pclinfo->clShapeEquip.clHelmet.uiUnique;

	if(unique)
	{
		pclCM->CR[id]->ChangeArmCode(pclCM->CR[id]->ActiveHat, unique);
	}


	unique = pclinfo->clShapeEquip.clMantle.uiUnique;
	if(unique)
	{
		pclCM->CR[id]->ChangeArmCode(PERSONITEM_MANTLE, unique);
	}

	unique = pclinfo->clShapeEquip.clWeapon.uiUnique;
	if(unique)
	{
		pclCM->CR[id]->ChangeArmCode( pclCM->CR[id]->ActiveWeapon, unique );
	}

	//KHY - 1001 - 기승동물 5마리 보유 수정.
	if(pclinfo->siCurrentHorseRIDEHORSE == TRUE)
	{
		cltDate cldate;
		cldate.MakeFullDateFromDateVary(pclinfo->siAddStatusDate);
		SI32 ticketnum = pclinfo->siStatusTicketNum ;

		// PCK : 축제음식 솜사탕을 먹으면 탈것중 랜덤하게 하나로 이미지가 바뀐다. (09.08.11)
		if(pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM_HORSE))
		{
			SI32 siTransFormHorseUnique = pclCM->CR[id]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_TRANSFORM_HORSE);
			pclCM->CR[id]->ChangeHorseCode(siTransFormHorseUnique, &cldate, ticketnum);
		}
		else
		{
			pclCM->CR[id]->ChangeHorseCode( pclinfo->uiHorseUnique1,&cldate,ticketnum);
		}
	}
	//말파츠 정보
	if(pclinfo->siPremiumPartsNum > 0)
	{
		cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse()	;
		if(pclHorse != NULL)
		{
			cltDate cldate_Slot1;
			cldate_Slot1.MakeFullDateFromDateVary(pclinfo->siPremiumPartsDate_Slot1);
			pclHorse->clPremiumPartsDate_Slot1.Set(&cldate_Slot1)	;
			cltDate cldate_Slot2;
			cldate_Slot2.MakeFullDateFromDateVary(pclinfo->siPremiumPartsDate_Slot2);
			pclHorse->clPremiumPartsDate_Slot2.Set(&cldate_Slot2)	;
			cltDate cldate_Slot3;
			cldate_Slot1.MakeFullDateFromDateVary(pclinfo->siPremiumPartsDate_Slot3);
			pclHorse->clPremiumPartsDate_Slot3.Set(&cldate_Slot3)	;

			pclHorse->SetPremiumPartsUnique_Slot1(pclinfo->siPremiumPartsUnique_Slot1)	;
			pclHorse->SetPremiumPartsUnique_Slot2(pclinfo->siPremiumPartsUnique_Slot2)	;
			pclHorse->SetPremiumPartsUnique_Slot3(pclinfo->siPremiumPartsUnique_Slot3)	;
			pclinfo->siPremiumPartsNum		=	pclinfo->siPremiumPartsNum	;
		}
	}
	// 캐릭터에게  행동을 지시한다. 
	cltOrderDataInfo* pclorder = &pclinfo->clOrder;

	switch(pclorder->siOrder)
	{
	case ORDER_STOP:
	case ORDER_FORCESTOP:
	case ORDER_WAIT:
		OrderStop(id, pclorder->siHostMode);
		break;

	case ORDER_MOVE:
		{
			OrderMove(id, LOWORD(pclorder->siPara1), HIWORD(pclorder->siPara1),pclorder->siHostMode);
		}
		break;
	case ORDER_STRAIGHTMOVE:
		{
			OrderStraightMove(id, LOWORD(pclorder->siPara1), HIWORD(pclorder->siPara1),pclorder->siHostMode);
		}
		break;


	case ORDER_ATTACK:
		{
			SI32 attackid = cltCharCommon::CharUniqueInfo[pclorder->siPara2];
			if(pclCM->IsAlive(attackid))
			{
				OrderAttack(id, attackid, pclorder->siHostMode);
			}
		}
		break;

	case ORDER_FISH:
		{
			OrderFish(id, pclorder->siPara1, pclorder->siHostMode);
		}
		break;
	case ORDER_FARM:
		{
			OrderFarm(id, LOWORD(pclorder->siPara1), HIWORD(pclorder->siPara1),pclorder->siHostMode);
		}
		break;
	case ORDER_MINE:
		{
			OrderMine(id, LOWORD(pclorder->siPara1), HIWORD(pclorder->siPara1),pclorder->siHostMode);
		}
		break;

	case ORDER_SITDOWN:
		{
			OrderSitDown( id, pclorder->siPara1, pclorder->siHostMode );
		}
		break;

	case ORDER_DIE :
		{
			OrderDie(id,  pclorder->siHostMode);
		}
		break;

	case ORDER_ATTACK_CLIENT:
		{
			SI32 attackid = cltCharCommon::CharUniqueInfo[pclorder->siPara2];
			if(pclCM->IsAlive(attackid))
			{
				OrderAttackClient(id, attackid, pclorder->siHostMode);
			}
		}
		break;

	case ORDER_SPECIAL_ACTION:
		{
			OrderSpecialAction(id, pclorder->siPara1, pclorder->siHostMode);
		}
		break;

	default:
		MsgBox(TEXT("CommonLogic-SetChar"), TEXT("order:%d"), pclorder->siOrder);
		break;

	}
	return id;
}
// 일반 캐릭터를 설정한다. 
SI32 cltCommonLogic::SetChar1(SI32 id, SI32 charunique, SI32 childcharunique, SI32 summonindex, cltIdentity* pclidentityinfo, cltPersonInfo* pclUserCharInfo, cltInnerStatusInfo* pclInnerStatus, SI16 mySoulGuardUnique)
{

	if(id <= 0)return 0;

	cltMapCommon* pclmap = pclMapManager->GetMapPointer(pclUserCharInfo->clBI.GetMapIndex());
	if(pclmap == NULL)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("SetChar() id:%d charunique:%d mapindex:%d"),
				id, charunique, pclUserCharInfo->clBI.GetMapIndex()	);

		return 0;
	}
    
	pclCM->CR[id]->CharInit(id, charunique, childcharunique, summonindex, SOUTH, pclmap, pclidentityinfo, pclUserCharInfo, pclInnerStatus, mySoulGuardUnique);
	
	// 클라이언트로부터 마지막으로 메시지를 받은 시간을 업데이트 한다. 
	pclCM->CR[id]->SetLastReceveFromClientClock(CurrentClock);

    return id;
}