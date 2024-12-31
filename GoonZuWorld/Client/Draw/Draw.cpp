//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "../Common/CommonHeader.h"

#include "../Client/Client.h"

#include <Graphic.h>
#include <Mouse.h>
#include <MainFunction.h>
#include <Graphic_Capsule.h>
#include "../../Lib/NGraphics/Graphics.h"

//#include "../ColorTable/ColorTable.h"
#include "../../Lib/Sound/SoundMgr.h"
#include "../../MapEdit/MapEdit.h"

#include "../../Common/Map/Map.h"
#include "../../Common/Item/ItemCommon/cltSetItem.h"

#include "../../CommonLogic/BlackArmy/BlackArmy.h"
#include "../../CommonLogic/Guild/GuildWar.h"

#include <MoveMark.h>

#include "../AttackEffect/AttackEffectMgr.h"

#include "../Prompt/PromptBaseDefinition.h"
#include "../Prompt/PromptMgr.h"

#include "Bullet/Bullet.h"
#include "Smoke/Smoke.h"
#include "Char\CharManager\CharManager.h"

#include "../Effect/FireFly/FireFlyMgr.h"						// �ݵ���

#include "../Effect/IceFlash/IceFlashMgr.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"

#include "Help\Help.h"

#include "../ImageInterface/FriendLoginDraw/FriendLoginDraw.h"
#include "../ImageInterface/ResidentLoginDraw/ResidentLoginDraw.h"
#include "../ImageInterface/NaesiPortraitDraw/NaesiPortraitDraw.h"
#include "../ImageInterface/VillageNotice/VillageNotice.h"
#include "../ImageInterface/VillageWarNotice/VillageWarNotice.h"
#include "../ImageInterface/NewYearEvent/NewYearEvent.h"

#include "../Interface/Durability/Durability.h"
#include "../Interface/WebEventDlg/WebEventDlg.h"
#include "../Interface\LoginNoticeDlg\LoginNoticeDlg.h"


#include "../Interface/ServerOnStepNotifyDlg/ServerOnStepNotifyDlg.h"

#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "../NInterface/NItemMallManager/NItemMallManager.h"
#include "../ninterface/nmagicinfodlg/MagicInfoDlg.h"
#include "../NInterface/NMiniMapDlg/NMiniMapDlg.h"
#include "../ninterface/NPremiumStatus/NPremiumStatus.h"
#include "../InterfaceMgr/InterfaceMgr.h"
#include "../FeastEffect/FeastEffectManager.h"

#include "../ninterface/NBuffStatus/NBuffstatus.h"
#include "../ninterface/NMagicCoolTimeDlg/NMagicCoolTimeDlg.h"
#include "../CommonLogic/Guild/GuildHuntMapWarStatMgr.h"

#include "PCRoom/PCRoomIntro.h"

#include "../ninterface/NPCRoom/NPCRoom_Display.h"

extern cltCommonLogic* pclClient;
extern SI32		gsiResolution;
extern SHORT	GameMouseX;
extern SHORT	GameMouseY;

bool cltClient::GameDrawHeroViewOperate()
{
	static UI32 LastDrawClock;
	static UI32 LastDrawFrame = 0;

	
	cltMapClient* pclmap = (cltMapClient*)pclMapManager->pclCurrentMap;
	if(pclmap == NULL)return false;

/*	UI32 diff			= TABS(CurrentClock - LastDrawClock);
	if(diff < 50)return ;
	LastDrawClock  = CurrentClock;
*/

	//--------------------------------------
	// ���� �ʹ��� ����� �׷����� �ʴ´�. 
	//--------------------------------------
	if(GetFrame() < 3 )
		return false;

	//------------------------------------------------
	// ���� �����ӿ��� �ι� ������� �ʴ´�. 
	//------------------------------------------------
	if(GetFrame() != 0 && LastDrawFrame == GetFrame())
		return false;
	LastDrawFrame = GetFrame();

	//-------------------------------------------------
	// ���ΰ� �������� ������ �����ϰ� �Ѵ�. 
	// MapEdit, Server������ ������ �ʾƾ� �Ѵ�. 
	//-------------------------------------------------
	if(GameMode == GAMEMODE_CLIENT)
	{
		HeroViewOperate();
	}

	return true;
}

bool cltClient::GameDrawMap()
{	
	cltMapClient* pclmap = (cltMapClient*)pclMapManager->pclCurrentMap;
	if(pclmap == NULL)return false;

	//-------------------------------------------------
	// ������ �׸���. 
	//-------------------------------------------------
	if ( pclmap )
	{
		pclmap->DrawMap();
	}

	lpBackScreen->BltFast( 0, 0, lpScreenMapBuffer, NULL, NULL );

	//-------------------------------------------
	// ĳ���� �� ������Ʈ ���. 
	//-------------------------------------------
	if(GP.LockSurface(lpBackScreen)==TRUE)
	{
		// ĳ���͸� ������ ��ü���� �׸���. 
		pclmap->DrawObj();

		if ( pclClient->GameMode == GAMEMODE_CLIENT )
		{
			if(pclMapManager)
			{
				if(pclMapManager->IsFogMap(pclmap->siMapIndex))
					pclmap->DrawFog(lpBackScreen,this);
			}			
		}

		GP.UnlockSurface(lpBackScreen);
	}

	//-------------------------------------------
	// ���� ���������� ǥ���Ѵ�. - [����]��������ϰ�� ������� ����(�� ������ ����϶��� �������)
	//-------------------------------------------
	if ( (pclClient->GameMode == GAMEMODE_MAPEDIT) || (pclClient->siServiceArea != ConstServiceArea_English) )
	{
		HDC hdc;

		if(lpBackScreen->GetDC(&hdc) == DD_OK)
		{
			if ( pclmap )
			{
				pclmap->SetGeoInfo(hdc);
			}

			lpBackScreen->ReleaseDC(hdc);
		}

		if ( pclmap )
		{
			pclmap->DrawGeoInfo(lpBackScreen, pclHelpManager);
		}
	}

	//-----------------------------------------------
	// ȭ�� ���� ����. 
	//-----------------------------------------------
	SI32 virtualx = 0; 
	SI32 virtualy = 0; 

	if(pclmap)
	{
		virtualx = pclmap->VirtualMapX;
		virtualy = pclmap->VirtualMapY;
	}

	SI32 rx	= 0, ry	= 0;
	// �踦 Ÿ�� �ִٸ� ���� RX, RY�� �ٰŷ� �Ѵ�.
	rx = pclCM->CR[1]->GetRX();
	ry = pclCM->CR[1]->GetRY();

	// �Ϻ������� ���� ��ũ�� ���
	if (pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		// ȭ���� RX, RY�� �����Ѵ�. 
		SetScreenRXY(rx, ry);

		pclUnderMouseObject->SetRX(rx);
		pclUnderMouseObject->SetRY(ry);
	}

	//-----------------------------------------
	// Hit Effect�� �׷��ش�. 
	//-----------------------------------------
	if(pclmap)
	{
		SI32 centerx	= 0, centery	= 0;
		SHORT screenx	= 0, screeny	= 0;
		
		pclmap->GetXYDotFromXYCord(virtualx, virtualy, centerx, centery);
		pclmap->TransFromRealDotToScreenDot(centerx, centery, screenx, screeny);
		
		g_AttackEffectMgr.Draw(lpBackScreen, centerx, centery, screenx, screeny ); 
	}

	//------------------------------------------
	// ������� �׸���.
	//------------------------------------------
	if( GP.LockSurface(lpBackScreen) == TRUE )
	{   
	   if( pclmap && pclmap->pclWaterDrop )
	   {
		   SI32 centerx = 0, centery = 0;
		   SI32 x, y;

		   pclmap->GetXYDotFromXYCord(virtualx, virtualy, centerx, centery);

		   x	= centerx + (pclmap->MH.MapXsize * MAP_TILE_XSIZE)/2 - (siClientScreenXsize/2);
		   y	= centery - (siScreenMode800X600YSize + siScreenModeYOffSet) /2;

		   pclmap->pclWaterDrop->Draw( x, y, siClientScreenXsize, siScreenMode800X600YSize + siScreenModeYOffSet);

	   }


		//------------------------------------------
		// �ݵ����� �׸���.
		//------------------------------------------
	   if( pclmap && pclmap->pclFireFly )
	   {
		   SI32 centerx = 0, centery = 0;
		   SI32 x, y;

		   pclmap->GetXYDotFromXYCord(virtualx, virtualy, centerx, centery);

		   x	= centerx + (pclmap->MH.MapXsize * MAP_TILE_XSIZE)/2 - (siClientScreenXsize/2);
		   y	= centery - (siScreenMode800X600YSize + siScreenModeYOffSet)/2;

		   pclmap->pclFireFly->Draw( x, y, siClientScreenXsize, siScreenMode800X600YSize + siScreenModeYOffSet);

	   }

		//------------------------------------------
		// ������ ��¦�̸� �׸���.
		//------------------------------------------
	   if( pclmap && pclmap->pclIceFlash )
	   {
		   SI32 centerx = 0, centery = 0;
		   SI32 x, y;

		   pclmap->GetXYDotFromXYCord(virtualx, virtualy, centerx, centery);

		   x	= centerx + (pclmap->MH.MapXsize * MAP_TILE_XSIZE)/2 - (siClientScreenXsize/2);
		   y	= centery - (siScreenMode800X600YSize + siScreenModeYOffSet)/2;

		   pclmap->pclIceFlash->Draw( x, y, siClientScreenXsize, siScreenMode800X600YSize + siScreenModeYOffSet);

	   }

	   //------------------------------------------
	   // ����Ǯ�� Ȧ���� �׸���.
	   //------------------------------------------
	   if( pclmap && pclmap->pclSeedDrop )
	   {
		   SI32 centerx = 0, centery = 0;
		   SI32 x, y;

		   pclmap->GetXYDotFromXYCord(virtualx, virtualy, centerx, centery);

		   x	= centerx + (pclmap->MH.MapXsize * MAP_TILE_XSIZE)/2 - (siClientScreenXsize/2);
		   y	= centery - (siScreenMode800X600YSize + siScreenModeYOffSet)/2;

		   pclmap->pclSeedDrop->Draw( x, y, siClientScreenXsize, siScreenMode800X600YSize + siScreenModeYOffSet);

	   }


		//-------------------------------------------------
		//  �̵���ũ���ൿ 
		//-------------------------------------------------
		if ( pclmap )
		{
			if ( pclmap->pclMoveMark )
			{
				pclmap->pclMoveMark->Action();
			}
		}
		

		//--------------------------------------
		// �̵���ũ �׸���. 
		//--------------------------------------
	   // �̵� ��ũ ���
		if ( pclmap )
		{
			pclmap->pclMoveMark->DrawMoveMark();
		}

	   GP.UnlockSurface(lpBackScreen);
	}

	//--------------------------------------
	// �޽��� ǥ��. 
	//--------------------------------------
	SI32 yinstance = 0 ;
	for ( int i = 0 ; i < MAX_SUMMON_OWN ; i ++ )
	{
		cltSummon * pclSummon = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon(i);
		if ( pclSummon && pclSummon->siKind > 0 )
			yinstance = ( i + 1 ) * 50 ;
	}

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
		yinstance += 30 ;

#ifndef _NEW_INTERFACE_
		pclMessage->Show(this, 90, 120 + yinstance , lpBackScreen, GetScreenRX(), GetScreenRY());
#else
		pclMessage->Show(this, 90, 150 + yinstance , lpBackScreen, GetScreenRX(), GetScreenRY());
#endif

	//------------------------------
	// ĳ���� �̸��� ǥ���Ѵ�. 
	//------------------------------
	// ĳ���� �̸��� �����. 
	if( g_SoundOnOffDlg.m_bShowCharName == false )
	{   
		pclCM->MakeCharName();
	}

	if(GP.LockSurface(lpBackScreen) == TRUE)
	{
		if( g_SoundOnOffDlg.m_bShowCharName == false )
		{        
			// ĳ���� �̸��� ����Ѵ�..
			pclCM->DrawCharName();
		}

		// ĳ���� ��ǳ���� ǥ���Ѵ�. 	
		pclCM->DrawChatBalloon();

		GP.UnlockSurface(lpBackScreen);
	}

	return true;
}

bool cltClient::GamaDrawInterface()
{

	//SI32 i;

	cltMapClient* pclmap = (cltMapClient*)pclMapManager->pclCurrentMap;
	if(pclmap == NULL)return false;

	//--------------------------------
	// Help�� ����Ѵ�. 
	//--------------------------------
	pclHelpManager->Draw(lpBackScreen);

	if(GameMode == GAMEMODE_CLIENT)
	{
		//-------------------------
		// Pannel ��� 
		//-------------------------
		
		if(pclPannel)
		{
			cltCharCommon* pclChar = pclCM->CR[1];
			
			// �ź� �̸� ���ϱ�. 
			//TCHAR rankname[128]=TEXT("");
			//cltSimpleRank* pclrank = &pclChar->pclCI->clCharRank;
			//UI08 grank = pclChar->pclCI->clBI.uiGRank ;
			//GetRankName(pclrank, rankname, 128, grank);

			static bool bRandStart = true ;
			static SI32 siRandX = 0 ;
			static SI32 siRandY = 0 ;
			if ( bRandStart )
			{
				siRandX = rand() % 3 ;
				siRandY = rand() % 3 ;
				bRandStart = false ;
			}
			
			pclPannel->Draw( lpBackScreen, GetScreenRX(), GetScreenRY(), siRandX, siRandY );
			
			//pclPannel->Draw(lpBackScreen, GetScreenRX(), GetScreenRY(), 
			//	rankname, 
			//	pclChar->pclCI->clIP.GetMoney(), 
			//	pclChar->pclCI->clIP.GetLevel(), 
			//	pclChar->pclCI->clIP.GetCurExp(),
			//	pclChar->clPB.GetNextExp(), 
			//	pclChar->pclCI->clIP.GetLife(), 
			//	pclChar->clPB.GetMaxLife(),
			//	pclChar->pclCI->clIP.GetMana(),
			//	pclChar->clPB.GetMaxMana(),
			//	pclChar->clPB.clHealth.AnalyzeHealth(pclChar->pclCI->clIP.GetLevel()),
			//	0, 0,
			//	pclChar->clPB.GetPrevExp(),
			//	pclChar->pclCI->clIP.Life + pclChar->clPB.siReservedLife,
			//	siRandX,siRandY);
			
		
		//	for ( i = 0 ; i < MAX_SUMMON_OWN ; i ++ )
		//	{
		//		//cltSummon *pclSummon = pclChar->pclCI->clSummonInfo.GetSummon(pclChar->siSummonIndex);
		//		cltSummon *pclSummon = pclChar->pclCI->clSummonInfo.GetSummon(i);
		//		if( pclSummon->siKind > 0 && pclSummon->siKind < MAX_KIND_NUMBER )//&& pclSummon->siStatus == SUMMON_STATUS_TAKEOUT )
		//		{
		//			SI32 kind = pclSummon->siKind;
		//			cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
		//			if ( pclki != NULL )
		//			{
		//				cltSummonScroll *pclScroll = &pclSummon->clScroll;

		//				cltPIPInfo			clipinfo2;
		//				clipinfo2.Set(&pclSummon->clIP);

		//				cltParametaBox clPB;
		//				clPB.Init(pclItemManager, &clipinfo2, NULL, pclki);

		//				bool bmosterhero = false;
		//				// �����۸����� �Ǹ��ϴ� ��ȯ�����̰� ���Ϳ��� ��ȭ�� ���̶��, 
		//				if(pclki->bSummonMall && pclSummon->siIdentity == 0)	
		//				{
		//					bmosterhero = true;
		//				}
		//				clPB.Action(NULL, 0, PERSONITEM_WEAPON1, NULL, NULL, NULL, NULL, NULL, pclScroll, GAMEMODE_CLIENT, true, bmosterhero);

		//				SI32 summonskill = pclCM->CR[1]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclCM->CR[1]->pclCI->clCharItem.clItem[0], 1 );

		//				SI32 minutevary = pclClient->GetMinuteFromsTime(((cltClient*)pclClient)->sTime);
		//				SI32 leftsummonstart = min(TABS(pclSummon->siTakeInMinute - minutevary), SUMMON_TAKEOUT_DELAY);
		//				
		//				/*
		//				pclPannel->DrawSummon(lpBackScreen, GetScreenRX(), GetScreenRY(), pclki->siSummonPortrait, 
		//					pclSummon->clIP.GetCurExp(),
		//					clPB.GetNextExp(),
		//					pclSummon->clIP.GetLife(),
		//					clPB.GetMaxLife(),
		//					pclSummon->clIP.GetMana(),
		//					clPB.GetMaxMana(),
		//					clPB.GetPrevExp(),
		//					pclSummon->clIP.GetLife(),
		//					pclSummon->siStatus,
		//					pclSummon->clIP.GetLuk(),
		//					pclClient->GetMaxStaminaValue(summonskill ),
		//					leftsummonstart,
		//					i,
		//					siRandX,siRandY);
		//				*/
		//			}
		//		}
		//	}
		}


		if(( m_pDialog[NITEMMALLMANAGER_DLG]))
		{
			if(pclCM->CR[1]->pclCI->clItemMall.GetExistence())
			{
				((CNItemMallButtonManager*)m_pDialog[NITEMMALLMANAGER_DLG])->SetFlash(true);				
			}
			else
			{				
				((CNItemMallButtonManager*)m_pDialog[NITEMMALLMANAGER_DLG])->SetFlash(false);
			}
		}
				
		if ( NULL == m_pDialog[NMAGICCOOLTIME_DLG] )
		{
			CreateInterface( NMAGICCOOLTIME_DLG );
		}

		if ( pclDurability )
		{
			pclDurability->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}

		// ������Ʈ 
	//	if(bPromptSwitch)
		{ 
			if ( g_SoundOnOffDlg.m_bFullScreenMode )
			{	
			}
			else
			{
				if ( GP.LockSurface( lpBackScreen ) == TRUE )
				{
					// �ǳ��� ����Ѵ�. 
					TSpr* pspr = GetGlobalSpr(GIMG_MAGIC_PROMPTBAR);
					if(pspr)
					{
						SI32 startx = 80 + GetScreenRX();
						SI32 starty = 0;
						if ( g_SoundOnOffDlg.m_bFullScreenMode )
						{
							starty = GetScreenRY() + siScreenMode800X600YSize + siScreenModeYOffSet - pspr->GetXSize();
						}
						else
						{
							starty = GetScreenRY() + siScreenMode800X600YSize + siScreenModeYOffSet - pspr->GetYSize();
						}

						SI32 drawnum = (siClientScreenXsize - (80 * 2)) / pspr->GetXSize();

						for(SI32 i = 0;i < drawnum;i++)
						{
							GP.PutMpr(pspr, startx + i * pspr->GetXSize(), starty, PUT_SPR_SPR, FALSE, 0 );
						}
					}

					g_PromptMgr.Draw( 100 + GetScreenRX(), siScreenMode800X600YSize + siScreenModeYOffSet -   + GetScreenRY());

					GP.UnlockSurface( lpBackScreen );
				}
			}
		}
		
		if ( pclVillageNotice )
		{
			pclVillageNotice->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}

		if ( IsWhereServiceArea(ConstServiceArea_China | ConstServiceArea_English | ConstServiceArea_NHNChina | ConstServiceArea_EUROPE) )
		{
			// ���θʿ��� ���Ǳ��� �̺�Ʈ
			if ( pclBlackWarManager )
			{
				pclBlackWarManager->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
			}
		}

		if ( pclBlackArmyManager )
		{
			pclBlackArmyManager->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}
		if(GP.LockSurface(lpBackScreen)==TRUE)
		{
			
			//--------------------------
			// �ΰ� ����Ѵ�. 
			//--------------------------

			if(pclLogo)
			{
				pclLogo->Draw(siClientScreenXsize, GetScreenYSize(), GetScreenRX(), GetScreenRY());
			}
			//--------------------------------------
			// ���� ����� ��� �������� ������ش�.
			//--------------------------------------
			// ���� ����̸�, 
			if(bWatchModeSwitch == true)
			{
				TSpr* pspr = pclClient->GetGlobalSpr( GIMG_SERVERNAME );

				if(pspr)
				{
					GP.PutSpr(pspr, siClientScreenXsize - 165 - pspr->GetXSize() + GetScreenRX(), 
						siScreenMode800X600YSize + siScreenModeYOffSet - 15 - pspr->GetXSize() + GetScreenRY(), 
						siServerUnique - 1);
				}
			}
			
			GP.UnlockSurface(lpBackScreen);
			
		}
		
		SI32 yindent = 0;


		if(GP.LockSurface(lpBackScreen)==TRUE)
		{
			cltCharCommon* pclChar = pclCM->CR[1];

			static long siLastDrawClock = 0;//pclClient->CurrentClock;
			//static long siDrawMarkClock = 0;

			if ( IsWhereServiceArea(ConstServiceArea_Korea | ConstServiceArea_NHNChina) )
			{
				if ( pclChar->pclCI->clBI.bPCRoom )
				{
					// 5�п� �ѹ��� 1�� ����ȴ�
					if( labs( labs(pclClient->CurrentClock) - labs(siLastDrawClock) ) > 300000L )
					{
						siLastDrawClock = pclClient->CurrentClock;

						if ( NULL == m_pDialog[NPCROOM_DISPLAY_DLG] )
						{
							CreateInterface( NPCROOM_DISPLAY_DLG );
						}

						((CNPCRoom_Display*)m_pDialog[NPCROOM_DISPLAY_DLG])->ShowDisplayPCRoom();
					}
				}
			}
			
			/*
			if( pclChar->pclCI->clBI.bPCRoom )
			{

				// �� �ð��� ���� 5���� �Ѵ´ٸ�

				if( labs( labs(pclClient->CurrentClock) - labs(siLastDrawClock) ) > 300000L )
				{
					siLastDrawClock = pclClient->CurrentClock;
					siDrawMarkClock = pclClient->CurrentClock;
				}

				// �׷��ִ� �ð����� 1�� ������ �׸��� �׷��ش�.
				if( labs( labs(pclClient->CurrentClock) - labs(siDrawMarkClock) ) < 60000L  )
				{
					// [GOONZU-649 �迵�� ����:2007.11.28]
					// [����] PC�� �����̾� ��ȭ�� ���� ��ũ �߰�
					SI32	siMarkNumber[Const_SpecialPCRoomMark]	= { GIMG_SPECIAL_PCROOM_MARK_1,		// �����̵�
																		GIMG_SPECIAL_PCROOM_MARK_4,		// ����Ŭ�ι�
																		GIMG_SPECIAL_PCROOM_MARK_2,		// ��������ġ
																		GIMG_SPECIAL_PCROOM_MARK_3		// ��������ġ
																	};	
					SI32	siSubPosition[Const_SpecialPCRoomMark]	= { 286, 234, 182, 130 }; // �⺻��ġ�� �Ǵ� ��ǥ
					SI32	siScreenModeAddPosition					= 0; // ��ũ�� ��忡 ���� ��ġ �߰���

					SI32	siScreenX								= GetScreenRX();
					SI32	siScreenY								= GetScreenRY();

					TSpr*	psprPCRoomMark							= NULL;
					

					// Ǯ��ũ���� ��� �⺻ ��ǥ�� -20�� ����
					if ( g_bFullScreen )
					{
						siScreenModeAddPosition = -20;
					}

					for ( SI32 siIndex = 0; siIndex<Const_SpecialPCRoomMark; siIndex++ )
					{
						psprPCRoomMark = NULL;
						psprPCRoomMark = GetGlobalSpr( siMarkNumber[ siIndex ] );

						if ( psprPCRoomMark != NULL )
						{
							SI32 siPositionX = siClientScreenXsize - siSubPosition[ siIndex ] + siScreenX + siScreenModeAddPosition;
							SI32 siPositionY = siScreenY + 210;

							GP.PutSpr( psprPCRoomMark, siPositionX, siPositionY, 0 );
						}
					}
				}
			}

			*/
			SI32	siXPos, siYPos;
			TSpr* pSpr = GetGlobalSpr(GIMG_BUFIMAGE);
			TSpr* pSpr2 = GetGlobalSpr(GIMG_BUFPERCENT);
			siXPos = siClientScreenXsize - 300 - pSpr->GetXSize() +GetScreenRX() - (g_SoundOnOffDlg.m_bMaxWindowMode? 30:0);
			siYPos = MAP_TILE_YSIZE + GetScreenRY() + 5;

/*
			// �����̾� �̹������� �� ������ ���� ��������
			if (m_pDialog[NPREMIUMSTATUS_DLG] && ((CNPremiumStatus*)m_pDialog[NPREMIUMSTATUS_DLG])->IsPremiumShow() )
			{
				siXPos -= 105;
			}


			if(pclCM->CR[1]->clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED))
			{
				if (pSpr)
				{
					GP.PutSpr(pSpr, siXPos, siYPos, 2);
				}
				siXPos -= 40;
			}

			// ������ �ɷ�������
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclCM->CR[1]->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;
			SI32 currentTime = ((cltClient*)pclClient)->clClientDate.GetHourVary();

			for ( SI16 i=0 ; i < MAX_BUF ; i++ )
			{
				if ( clBuf.m_stBuf[i].siBufType == 0 ) 
					continue;
				if ( currentTime > clBuf.m_stBuf[i].siOverTime )
					continue;

				if ( currentTime < clBuf.m_stBuf[i].siOverTime )
				{
					GP.PutSpr( pSpr, siXPos, siYPos, clBuf.m_stBuf[i].siBufType-1 );
					if ( clBuf.m_stBuf[i].siPercent )
					{
						GP.PutSpr( pSpr2, siXPos+15, siYPos+28, clBuf.m_stBuf[i].siPercent / 10 - 1 );
					}
				}
				else		// ���� �ð��� ���� ���� ���! �����δ�.
				{
					if ( pclClient->CurrentClock % 1200 > 300 )
					{
						GP.PutSpr( pSpr, siXPos, siYPos, clBuf.m_stBuf[i].siBufType-1 );
						if ( clBuf.m_stBuf[i].siPercent )
						{
							GP.PutSpr( pSpr2, siXPos+15, siYPos+28, clBuf.m_stBuf[i].siPercent / 10 - 1 );
						}
					}

				}
				siXPos -= 40;
			}
*/
			// ���� Ʈ���� �Ǽ��Ǿ��ִٸ�
			for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++)
			{
				if( ((cltCharClient*)pclCM->CR[1])->siEventNPCKind[i] == GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
					 ((cltCharClient*)pclCM->CR[1])->siEventNPCKind[i] == GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")) )
				{
					TSpr* pSpr = GetGlobalSpr(GIMG_CHRISTMAS_BUF);

					GP.PutSpr( pSpr,siXPos - 105, siYPos + 35, 1 );
					siXPos -= 40;
				}	

			}
			//�߷�Ÿ�ε��� ����
			if (pclClient->pclCM->CR[1]->pclValentineWar->GetCouple() > 0 && 
				pclClient->pclCM->CR[1]->dwValentineAnswerTime > 0 ) 
			{
				// 10�ʵ��� �׸� �׷��ش�.
				if ( TABS(pclClient->CurrentClock - pclClient->pclCM->CR[1]->dwValentineAnswerTime ) < 10000 )
				{
					TSpr* pspr = pclClient->GetGlobalSpr(GIMG_VALENTINEWAR);

					SI32 siPositionX = pspr->GetXSize() + GetScreenRX()	;
					SI32 siPositionY = GetScreenRY() + 100;
                    GP.PutSpr(pspr,siPositionX,siPositionY,pspr->GetYSize());

				}

			}

			
/*
#ifdef EVENT_CHRISTMAS
	
			// ���� Ʈ���� �Ǽ��Ǿ��ִٸ�
			
 			if( ((cltCharClient*)pclCM->CR[1])->siEventNPCKind > 0 )
			{
				TSpr* pSpr = GetGlobalSpr(GIMG_CHRISTMAS_BUF);
				
				GP.PutSpr( pSpr,siXPos, siYPos, 1 );
				siXPos -= 40;
			}
#endif
*/

			/*
#ifdef EVENT_HAPPY_NEWYEAR

			// ���� Ʈ���� �Ǽ��Ǿ��ִٸ�

			if( ((cltCharClient*)pclCM->CR[1])->siEventNPCKind > 0 )
			{
				TSpr* pSpr = GetGlobalSpr(GIMG_CHRISTMAS_BUF);

				GP.PutSpr( pSpr,siXPos, siYPos, 1 );
				siXPos -= 40;
			}
#endif
*/ 
/*
#ifdef EVENT_SUMMON_EVENT

			// ��ȯ���� ��ȯ�Ǿ� �ִٸ�
			
			SI32 summonId = pclCM->CR[1]->GetSummonID();

			if( pclCM->IsAlive(summonId) == true )
			{
				TSpr* pSpr = GetGlobalSpr(GIMG_SUMMON_EVENT_BUF);

				GP.PutSpr( pSpr,siXPos, siYPos, 1 );
				siXPos -= 40;
			}

#endif
*/
			// ��Ÿ ��Ʈ ȿ���� ���ֵǰ��ִٸ�

			if(    pclCM->CR[1]->m_siSetItemType == XMAS_SETITEM
				|| pclCM->CR[1]->m_siSetItemType == BOY_SULBIM_SETITEM
				|| pclCM->CR[1]->m_siSetItemType == GIRL_SULBIM_SETITEM )
			{
				TSpr* pSpr = GetGlobalSpr(GIMG_CHRISTMAS_BUF);

				GP.PutSpr( pSpr,siXPos - 105, siYPos + 35, 0 );
				siXPos -= 40;
			}


			GP.UnlockSurface(lpBackScreen);
		}
		

		//---------------------------
		// ���� ���� �ð��� ǥ���Ѵ�. 
		//---------------------------
		cltCharClient* pclchar = (cltCharClient*)pclCM->CR[1];
		 if(pclchar->bStartMakeItemSwitch)
		 {
			 pclchar->DrawMakeDelay(lpBackScreen, GetScreenRX(), GetScreenRY());
		 }


		 
		 if(GP.LockSurface(lpBackScreen)==TRUE)
		 {
			//------------------------------
			// �ֹ� �α��� ������ ǥ���Ѵ�.
			//------------------------------
			 m_pResidentLoginDraw->Draw( GetScreenRX(), GetScreenRY() );

			 
			//------------------------------
			// ģ�� �α��� ������ ǥ���Ѵ�.
			//------------------------------
			 m_pFriendLoginDraw->Draw( GetScreenRX(), GetScreenRY() );

			 //--------------------------------
			 // ���� ���� ��Ȳ �˸� 
			 //--------------------------------
			m_pVillageWarNotice->Draw( GetScreenRX(), GetScreenRY() );


			//--------------------------------
			// �ų� �̺�Ʈ ��Ȳ �˸� �޴���
			//--------------------------------
			m_pNewYearEventNotice->Draw( GetScreenRX(), GetScreenRY() );

			GP.UnlockSurface(lpBackScreen);
		 }
	



		 //cyj ���� ����Ʈ�� ���콺 Ŭ�� �̹��� ��Ÿ������ 
		 // ����
	      /*  
		 if(pclQuestManager->siQuestType == QUEST_TYPE_BEGINNER2)
		 {
			 if( pclQuestManager->  siCurrentQuestUnique == 30003 || pclQuestManager->siCurrentQuestUnique == 30012 ||pclQuestManager->siCurrentQuestUnique == 30024)
				 pclQuestManager->DrawClickMouse(lpBackScreen, pclQuestManager->siCurrentQuestUnique);
		 }*/
		


		 /*cyj ������ ����
		 // ����
		 if(pclQuestManager->siQuestType == QUEST_TYPE_BEGINNER5)
		 {
			 if( pclQuestManager->siCurrentQuestUnique == 25003 || pclQuestManager->siCurrentQuestUnique == 25012 ||pclQuestManager->siCurrentQuestUnique == 25024)
				 pclQuestManager->DrawClickMouse(lpBackScreen, pclQuestManager->siCurrentQuestUnique);
		 }
		 */

		 // ����� ���̸�
		if (pclGuildWarClient)
		{
			if (pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar))	// ������
			{
				if ( IsGuildWarMap_Use_New_GuildWar(pclCM->CR[1]->GetMapIndex()) || IsGuildWarMap_NEW(pclCM->CR[1]->GetMapIndex()))
					pclGuildWarClient->DrawStatus( lpBackScreen, GetScreenRX(), GetScreenRY() );
			}
			else	// ������
			{
				if ( IsGuildWarMap_Not_Use_New_GuildWar(pclCM->CR[1]->GetMapIndex()) )
					pclGuildWarClient->DrawStatus( lpBackScreen, GetScreenRX(), GetScreenRY() );
			}
		}

		//	[��ȣ]	����� ȹ�� ���� ����� ���̶��
		if(m_pclGuildHuntMapWarStatMgr)
		{
			if (pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar))	// ������
			{
				if(m_pclGuildHuntMapWarStatMgr->IsGuildHuntMapWar() == true 
					&& IsGuildWarMap_NEW(pclCM->CR[1]->GetMapIndex()) )
					m_pclGuildHuntMapWarStatMgr->DrawStatus(lpBackScreen, GetScreenRX(), GetScreenRY());
			}
		}
		if ( pclClient->bTimeCount == true )
		{
			if(pclClient->siTimeSet > 0 )
			{
				DrawTimeCount( pclClient->siTimeSet, lpBackScreen, GetScreenRX(), GetScreenRY() );
			}
		}
		if ( pclClient->siRoundCount >= 0)
		{
			DrawRound( pclClient->siRoundCount, lpBackScreen, GetScreenRX(), GetScreenRY() );
		}
	}
	return true;
}


void cltClient::GameDraw()
{
	if(GameDrawHeroViewOperate() == false)
	{
		return ;
	}

	if(GameDrawMap() == false)
	{
		return ;
	}

	if(GamaDrawInterface() == false)
	{
		return ;
	}

	//-----------------------------------
	// ȭ������ ������Ʈ. 
	//-----------------------------------

#ifdef JEWAN_FRAME_SKIP
		if( g_graphics.m_bSkipDraw == FALSE ) {
			GameDrawUpdateScreen();

		}
#else
		GameDrawUpdateScreen();
#endif

	// ��ũ�� ������ �ٽ� �� �� �ֵ��� �����Ѵ�. ��ũ���� GameDraw() �ѹ��� �ѹ����� �̷������. 
	SetScrollProcSwitch(false);
}

void cltClient::GameDrawUpdateScreen()
{
	static SI32 oldrx, oldry;
	HRESULT hResult =0;

	/*
	RECT rect;
	rect.left   = 0;
	rect.right  = GP.GetScreenXsize();
	rect.top    = 0;
	rect.bottom = GP.GetScreenYsize();
	*/

	if(GameMode == GAMEMODE_CLIENT)
	{
		if ( GP.LockSurface(lpBackScreen)==TRUE)
		{
			// PC��
		//	if( m_pPCRoomIntro )
		//	{
		//		m_pPCRoomIntro->Draw();
		//	}

			// ���ڽ� ����Ʈ
			if( m_pFeastEffectManager )
			{
				m_pFeastEffectManager->Draw();
			}

			GP.UnlockSurface(lpBackScreen);
		}

		if ( m_pInterfaceMgr )
		{
			m_pInterfaceMgr->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}
		
		bool bLoginDlgShow = m_pDialog[NLOGIN_DLG] && m_pDialog[NLOGIN_DLG]->IsShow();
		bool bSelectCharDlgShow = m_pDialog[NSELECTCHAR_DLG] && m_pDialog[NSELECTCHAR_DLG]->IsShow();
		bool bSelectWorldDlgShow = m_pDialog[NSELECTWORLDLIST_DLG] && m_pDialog[NSELECTWORLDLIST_DLG]->IsShow();
		// ĳ���� ����â, �α���â, ��������â�� �������� ��� ���Ѵ�.
		if ( (bLoginDlgShow || bSelectCharDlgShow || bSelectWorldDlgShow) == false )
		{
			if(pclQuestManager)			pclQuestManager->DrawClickMouse(lpBackScreen, pclQuestManager->siCurrentQuestUnique);
		}

		//--------------------------------
		// ���� ��� ǥ��
		//--------------------------------
		if(m_kTimer_ShowRank_Time.IsActivated())
		{
			if(m_kTimer_ShowRank_Time.IsTimed(GetTickCount(), false) == true)
			{
			}
			SI32 siPosX, siPosY;

			siPosY = GetScreenRY();
			siPosX = GetScreenRX() + GetScreenXSize() - 205;

			switch(m_siDrawMode)
			{
			case 0:
				{
					siPosY += 40;
				}
				break;
			case 1:
				{
					siPosY += 40 + 185;
				}
				break;
			}

			SI32 siFont = 1;


			if(siServiceAge >= 18)
				siFont = 1;		// 18�� �̻� �̿밡		
			else
				siFont = 0;		// ��ü �̿밡


			TSpr* pspr = GetGlobalSpr(GIMG_GOVERNMENT_RANKMARK);
			if ( GP.LockSurface( lpBackScreen ) == TRUE )
			{
				GP.PutSpr(pspr, siPosX,	siPosY,	siFont);

				GP.UnlockSurface(lpBackScreen);
			}
		}

		//}
		/*
		if( m_pDialog[ NMINIMAP_DLG ] )
		{
			((CNMiniMapDlg *)m_pDialog[ NMINIMAP_DLG ])->DrawMiniMap( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}
		*/

	}


	//-------------------------------------------
	// �°��׽�Ʈ
	//-------------------------------------------
	//UpdateScreen(GetHwnd(), lpBackScreen, false);		// ȭ�� ������ ��ٸ���. 

	if(oldrx != GetScreenRX() || oldry != GetScreenRY())
	{
		UpdateScreen(GetHwnd(), lpBackScreen, true);		// ȭ�� ������ ��ٸ���. 
	}
	else
	{ 
		UpdateScreen(GetHwnd(), lpBackScreen, false);	// ȭ�� ������ ��ٸ��� �ʴ´�. 
	}

	//-------------------------------------------


	oldrx	= GetScreenRX();
	oldry	= GetScreenRY();
	

	// ���ǽ��� �ν�Ʈ�� ���̸�, 
	if(hResult == DDERR_SURFACELOST)
	{
		GP.Restore();
	}
}

void cltClient::UpdateScreen(HWND hwnd, LPDIRECTDRAWSURFACE7 pSurface, bool waitrefresh)
{

	SI32 xindent = 0;
	SI32 yindent = 0;


	// Ŭ���̾�Ʈ�� ȯ���� ����Ͽ� ������ �� ���� �����Ѵ�. 
	// ���� ��� ���ٰ� �ִٸ� ������ ũ�⸸ŭ �����ش�. 
	if(pclToolBar)
	{
		yindent	= pclToolBar->GetToolBarYsize() + 2;
	}
	

	/*
	if ( siScreenMode == MODE_GRAPHICS1024_768 )
	{
	// 1024 * 768 ��
		GP.UpdateScreen(hwnd, pSurface, 1024, 768,
			xindent, yindent, MAP_TILE_XSIZE + GetScreenRX(), MAP_TILE_YSIZE + GetScreenRY(), waitrefresh);
	}
	else
	{
		GP.UpdateScreen(hwnd, pSurface, 
			siClientScreenXsize - (MAP_TILE_XSIZE * 2), 
			siClientScreenYsize - (MAP_TILE_YSIZE * 2),
			xindent, yindent, MAP_TILE_XSIZE + GetScreenRX(), MAP_TILE_YSIZE + GetScreenRY(), waitrefresh);
	}
	*/
	int screenXSize = 0;
	int screenYSize = 0;

	switch( siScreenMode )
	{
	case MODE_GRAPHICS800_600:
		screenXSize = 800;
		screenYSize = 600;
		break;

	case MODE_GRAPHICS1024_768:
		screenXSize = 1024;
		screenYSize = 768;
		break;
	// KHY - 1218 - 1024x600 �ػ� �߰�. imsi
	case MODE_GRAPHICS1024_600:
		screenXSize = 1024;
		screenYSize = 600;
		break;

	case MODE_GRAPHICS1280_1024:
		screenXSize = 1280;
		screenYSize = 1024;
		break;
	}

	GP.UpdateScreen(hwnd, pSurface, 
		siClientScreenXsize - (MAP_TILE_XSIZE * 2), 
		siClientScreenYsize - (MAP_TILE_YSIZE * 2),
		xindent, yindent, 
		MAP_TILE_XSIZE + GetScreenRX(), MAP_TILE_YSIZE + GetScreenRY(), waitrefresh,
		screenXSize,
		screenYSize,
		g_LoginNoticeDlg.m_bShow,
		g_LoginNoticeDlg.m_hLoginNoticeDlg,
		IsCountrySwitch(Switch_ChangeFullScreen) );
}

void cltClient::DrawGovernMentRankMark(SI32 siDrawMode)
{
	m_kTimer_ShowRank_Time.SetActive(true, GetTickCount());
	m_siDrawMode	= siDrawMode;
}
void cltClient::DrawTimeCount(SI32 siTime,LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry)	// siTimeCount�� �Ѵ�.
{
	cltClient* pclclient = (cltClient*)pclClient;

	SI32 yindent  = 0;
	clock_t		m_endClock = pclClient->CurrentClock + ( siTime * 1000 );

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		yindent = 30 ;
	}
	if( m_endClock )
	{
		clock_t overTime = ( m_endClock - ( pclClient->CurrentClock ) ) / 1000;

		overTime = max( 0, overTime );

		TSpr* pspr = NULL	;
		pspr = GetGlobalSpr(GIMG_GUILDWAR_TIME);
		if(pspr != NULL)
		{
			// ���� ����, ���� �˸� �޼��� ���
			SI32 xPos = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx;
			SI32 yPos = ry+yindent + 90;

			SI32 siMinuteFirst	=	0;			//	���ڸ��� minute
			SI32 siMinuteLast	=	0;			//	���ڸ��� minute
			SI32 siSecondFirst	=	0;			//	���ڸ��� second
			SI32 siSecondLast	=	0;			//	���ڸ��� second

			//	count -> �� : �� �� ��ȯ
			if( GP.LockSurface(lpsurface)==TRUE )
			{
				SI32	siMinute	=	overTime / 60;
				SI32	siSecond	=	overTime % 60;

				if(siMinute >= 10)
				{
					siMinuteFirst	=	siMinute / 10;
					siMinuteLast	=	siMinute % 10;
				}
				else
				{
					siMinuteFirst	=	0;
					siMinuteLast	=	siMinute;
				}

				if(siSecond >= 10)
				{
					siSecondFirst	=	siSecond / 10;
					siSecondLast	=	siSecond % 10;
				}
				else
				{
					siSecondFirst	=	0;
					siSecondLast	=	siSecond;
				}

				GP.PutSpr(pspr, xPos - 34, yPos, siMinuteFirst);
				GP.PutSpr(pspr, xPos - 17, yPos, siMinuteLast);

				GP.PutSpr(pspr, xPos, yPos, 10);

				GP.PutSpr(pspr, xPos + 17, yPos, siSecondFirst);
				GP.PutSpr(pspr, xPos + 34, yPos, siSecondLast);

				GP.UnlockSurface(lpsurface);
			}

			// Ÿ�� ������ ���ؼ�
			if ( (pclClient->CurrentClock - pclClient->dwWriteSetTime) >= 1000 )
			{
				if ( pclClient->siTimeSet <= 0 )
				{
					pclClient->dwWriteSetTime	=	0	;
					pclClient->siTimeSet	=	0	;
					pclClient->bTimeCount	=	false	;
				}
				else
				{
					pclClient->dwWriteSetTime	=	pclClient->CurrentClock	;
					pclClient->siTimeSet--;
				}
			}
		}
	}

}

void cltClient::DrawRound(SI32 siRound,LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry)// ���带 �����ش�.
{
	// �̺�Ʈ ���� ���� �ϰ� ������
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 yindent  = 0;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		yindent = 30 ;
	}

	TSpr* pspr = NULL	;
	pspr = GetGlobalSpr(GIMG_ROUNDCOUNT);	// �̹����� ������ �´�.

	SI32 xPos = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx;
	SI32 yPos = ry+yindent + 70;

	switch (siRound)
	{
	case GAME_ROUND_1 :
	case GAME_ROUND_2 :
	case GAME_ROUND_3 :
	case GAME_ROUND_4 :
	case GAME_ROUND_5 :
	case GAME_ROUND_6 :
	case GAME_ROUND_7 :
	case GAME_ROUND_8 :
	case GAME_ROUND_9 :
	case GAME_ROUND_10 :
		{
			GP.PutSpr(pspr, xPos, yPos+pspr->GetYSize(), siRound );
		}
		break;
	}


}