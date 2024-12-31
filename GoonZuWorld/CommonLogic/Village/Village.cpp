//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include "..\Client\Client.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg.h"

//------------------------------
// CommonLogic
//------------------------------
#include "Village.h"
#include "MsgType-System.h"
#include "Cityhall\Cityhall.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharServer\Char-Server.h"
#include "Char\CharManager\CharManager.h"

//---------------------------------
// Server
//---------------------------------
#include "..\Server\Server.h"
#include "..\..\Server\Rank\Rank.h"
#include "../../Server/AuthServer/AuthMsg.h"

extern cltCommonLogic* pclClient;

LPDIRECTDRAWSURFACE7		g_lpVillageTitleSurface = NULL;

//--------------------------------------------------
// cltVillageInfo
//--------------------------------------------------
cltVillageInfo::cltVillageInfo(cltVillageManager* pclvillageset, SI32 villagemode, SI32 siunique, DWORD atb, TCHAR* name, SI32 villageposx, SI32 villageposy, SI32 mapindex, SI32 season, bool bfarm, bool biron )
{
	if(pclvillageset == NULL)
	{
		MsgBox(TEXT("cltVillageInfo()"), TEXT("fd0982"));
	}
	else
	{
		pclVillageManager	= pclvillageset;
	}

	siVillageUnique	= siunique;	
	dwAtb		= atb;
	_tcsncpy(szName, name, 30);

	pTitleBuffer	= NULL;
	pTitleEncBuffer = NULL;

	bEnemyCaptureSwitch	= false;
	siEnemyNum			= 0;
	siPersonalShopNum	= 0;

	PosX			= villageposx;
	PosY			= villageposy;

	siWarKillNumber	= 0;
	siUserNum		= 0;

	dwLastVillageGodClock	= 0;
	dwLastCastleClock		= 0;
	dwLastAttackedVillageClock = 0;

	siVillageGodCharUnique	= 0;
	siCastleCharUnique		= 0;
	siKingMonumentUnique	= 0;
	bAttackedVillage		= FALSE;
	bOsakaWarSwitch			= false;
	
	siVisitorNumber			= 0;		// �湮�� �� �ʱ�ȭ. 
	siVisitLevel			= 0;
	
	
	bFarmSwitch				= bfarm;
	bIronSwitch				= biron;
	bUpgradeSwitch			= false ;
	
	if(season == 0)		siSeason	= SEASON_SPRING;
	else if(season == 1)siSeason	= SEASON_AUTUMN;
	else if(season == 2)siSeason	= SEASON_WINTER;

	switch(season)
	{
	case SEASON_SPRING:
		siVillageType = VILLAGETYPE_SPRING_NORMAL;
		break;
	case SEASON_AUTUMN:
		siVillageType = VILLAGETYPE_AUTUMN_NORMAL;
		break;
	case SEASON_WINTER:
		siVillageType = VILLAGETYPE_WINTER_NORMAL;
		break;
	}
	
	memset(RankAccountID, 0, sizeof(RankAccountID));

	if(villagemode == GAMEMODE_SERVER)
	{
		LoadCityHallFromDB();
		
		LoadBankFromDB();
		
		LoadStockFromDB();
		
		LoadMarketFromDB();
		
		LoadHouseFromDB();
		
		// DB���� ������ ������ �о�ͼ� ������Ʈ �Ѵ�. 
		LoadHuntFromDB();
		
		// DB���� ���� ������ �о�ͼ� ������Ʈ �Ѵ�.
		LoadPostOfficeFromDB();

		LoadHorseMarketFromDB();

		LoadRealEstateMarketFromDB();

		LoadSummonMarketFromDB();

		LoadLandFromDB();

		LoadFeastFromDB();

		LoadSummonHeroMarketFromDB();

		LoadMineFromDB();

		LoadGuildFromDB();

		LoadNewMarketFromDB();
	}
}

cltVillageInfo::~cltVillageInfo()
{
	if( g_lpVillageTitleSurface ) {
		g_lpVillageTitleSurface->Release();
		g_lpVillageTitleSurface = NULL;
	}

	if(pTitleBuffer)
	{
		delete[] pTitleBuffer;
		pTitleBuffer = NULL;
	}

	if(pTitleEncBuffer)
	{
		delete[] pTitleEncBuffer;
		pTitleEncBuffer = NULL;
	}
}


BOOL  cltVillageInfo::LoadTitle()
{

	if( g_lpVillageTitleSurface == NULL ) {



		if( g_graphics.CreateSurface16( &g_lpVillageTitleSurface, 300, 64 ) == FALSE ) {
			if (pclClient->GameMode != GAMEMODE_SERVER)
				MessageBox( NULL, TEXT("CreateOffScreen Error, VillageTitleSurface"), TEXT("fdsf"), MB_OK |MB_TOPMOST);
		}


	}


	if(pTitleBuffer)return FALSE;

	cltClient* pclclient = (cltClient*)pclClient;

	if(pclclient->lpBackScreen)
	{
		SIZE size={0, 0};
		HDC hdc;
		
		//  ���� �̸��� ���ǽ��� ����. 
		if(pclclient->lpBackScreen->GetDC(&hdc)== DD_OK)
		{
//			TextOut(hdc, 0, 0, szName, lstrlen(szName));
			
			// ���� �̸� �̹����� ����� ���´�. 
			GetTextExtentPoint32(hdc, szName, _tcslen(szName), &size);
			
			pclclient->lpBackScreen->ReleaseDC(hdc);
		}
		
		if(size.cx && size.cy )
		{
			// ���� �̹����� ���ۿ� �ִ´�. 
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_VILLAGENAMEBACK);
			
			if(pspr && pspr->GetXSize())
			{

				SI32 xnum = size.cx / pspr->GetXSize();
				TitleImageXsize	= xnum * pspr->GetXSize();
				
				if(size.cx % pspr->GetXSize())
				{
					TitleImageXsize += pspr->GetXSize();
					xnum ++;
				}
				TitleImageXsize += (pspr->GetXSize() * 2) ;

				TitleImageYsize	= pspr->GetYSize();


				//pTitleBuffer = new UI08[ TitleImageXsize * TitleImageYsize * 4 ];
				pTitleBuffer = new UI08[ sizeof(RGB16) * 300 * 64 ];

				g_graphics.ClearSurface( g_lpVillageTitleSurface, RGB16_TRANS );
				
				if( GP.LockSurface( g_lpVillageTitleSurface ) ) {


					GP.PutSpr(pspr,0, 0, 0);
						
					for(SI32 i = 0;i < xnum;i++)
					{
						GP.PutSpr(pspr,pspr->GetXSize() + i * pspr->GetXSize(), 0, 1);
					}

					GP.PutSpr(pspr,pspr->GetXSize() + xnum * pspr->GetXSize(), 0, 2);

					GP.UnlockSurface( g_lpVillageTitleSurface );
				}
					
				// ���� �̸��� ����Ѵ�. 
				if( g_lpVillageTitleSurface->GetDC(&hdc)== DD_OK)
				{
					TextOut(
						hdc, 
						pspr->GetXSize(), 
						(TitleImageYsize - size.cy) / 2, 
						szName, lstrlen(szName) );

					g_lpVillageTitleSurface->ReleaseDC( hdc );
				}

			
				if(  GP.LockSurface( g_lpVillageTitleSurface ) )
				{
					if(pTitleBuffer)
					{
						int size;
						g_graphics.EncodeXpr( (RGB16*)pTitleBuffer, 
											  300,
											  64,
											  RGB16_TRANS,
											  &size );
					}


				GP.UnlockSurface( g_lpVillageTitleSurface );
				}

			}

/*			
			// ���� �̹����� ���ۿ� ���´�.
			UI08* ptemp;
			ptemp = new UI08[size.cx * size.cy];
			
			if(GP.LockSurface(pclclient->lpBackScreen))
			{
				GP.GetImage(0, 0, size.cx, size.cy, ptemp);
				
				GP.UnlockSurface(pclclient->lpBackScreen);
			}
			
			// ���� �̹����� ���ۿ� �ִ´�. 
			cltTSpr* pspr	= pclClient->GetGImgPointer(GIMG_VILLAGENAMEBACK);
			if(pspr)
			{
				SI32 xnum = size.cx / pspr->GetXSize();
				TitleImageXsize	= xnum * pspr->GetXSize();
				
				if(size.cx % pspr->GetXSize())
				{
					TitleImageXsize += pspr->GetXSize();
					xnum ++;
				}
				TitleImageXsize += (pspr->GetXSize() * 2) ;

				TitleImageYsize	= pspr->GetYSize();

#ifdef GRA_MODE_16

#else

				pTitleBuffer = new UI08[TitleImageXsize * TitleImageYsize];



				if(GP.LockSurface(pTitleBuffer, TitleImageXsize, TitleImageYsize) )
				{
					// ��������� ä���. 
					GP.FillBox(0, 0, TitleImageXsize-1, TitleImageYsize-1, COLOR_TRANS,FALSE);

					GP.PutSpr(pspr,0, 0, 0);
					
					for(SI32 i = 0;i < xnum;i++)
					{
						GP.PutSpr(pspr,pspr->GetXSize() + i * pspr->GetXSize(), 0, 1);
					}

					GP.PutSpr(pspr,pspr->GetXSize() + xnum * pspr->GetXSize(), 0, 2);


					// ���� �̸��� ����Ѵ�. 
					//GP.PutSpr8T(pspr->GetXSize(), (TitleImageYsize - size.cy) / 2, size.cx, size.cy, ptemp);
					GP.PutSpr(pspr->GetXSize(), (TitleImageYsize - size.cy) / 2, size.cx, size.cy,
							  ptemp,PUT_SPR_SPR,SPR_MODE_T);
				}
			}
			
			delete[] ptemp;
*/
		}

		
	}
	
	return TRUE;
}

// Ư�� �ü��� ������ �ִ��� ���θ� Ȯ���Ѵ�. 
BOOL cltVillageInfo::HasStructure(SI32 structureunique)
{
	return clVillageVary.clStructureInfo.IsDuplicate(structureunique);
}

BOOL cltVillageInfo::Action()
{
	SI32 diff = 1;

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{

		//--------------------------------------
		// ���� ���� �ľ� 
		//--------------------------------------
		if(bEnemyCaptureSwitch == false && siEnemyNum >= 10)
		{
			bEnemyCaptureSwitch = true;

			//-----------------------------------
			// Ŭ���̾�Ʈ�� �뺸. 
			//-----------------------------------
			cltGameMsgResponse_EnemyCapture clinfo(siVillageUnique, bEnemyCaptureSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_ENEMYCAPTURE, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
		}

		if(bEnemyCaptureSwitch == true && siEnemyNum == 0)
		{
			bEnemyCaptureSwitch = false;

			//-----------------------------------
			// Ŭ���̾�Ʈ�� �뺸. 
			//-----------------------------------
			cltGameMsgResponse_EnemyCapture clinfo(siVillageUnique, bEnemyCaptureSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_ENEMYCAPTURE, sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

		}
		

	//-------------------------------------------------------
	// ������ ������ DB�� ��û�Ѵ�. 
	//-------------------------------------------------------
		SI32 diff = 100;
		if(pclClient->GetFrame() % diff == 0)
		{
			if( (pclClient->GetFrame() / diff) % MAX_VILLAGE_NUMBER  == (DWORD)siVillageUnique)
			{
				sDBRequest_InvestList clMsgInvest(siVillageUnique);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsgInvest);
			}
		}


		



	if( TABS(pclClient->CurrentClock - dwLastVillageGodClock) > 60000)
		{
			dwLastVillageGodClock = pclClient->CurrentClock;

			//-------------------------------------------------------
			// ��ȣ�� 1�� ���� �˻� 
			//-------------------------------------------------------

			CreateVillageKingMonument();

			//-------------------------------------------------------
			// ��Ȳ�� 1�� ���� �˻� 
			//-------------------------------------------------------
			// ��Ȳ���� �������� ������� ���� �����Ѵ�.
			CreateVillageGod();

			// ��Ȳ���� ���� �����Ұ��  �����ֱ⸶�� ���� 
			SetVillageGodtoDB();

			//-------------------------------------------------------
			// ���� 1�� ���� �˻� 
			//-------------------------------------------------------
			// ������ �������� ������� ���� �����Ѵ�.
			CreateCastle();

			// ������ ���� �����Ұ��  �����ֱ⸶�� ���� 
			SetCastletoDB();
		}


	//-------------------------------------------------------
	// �����̳� ��Ȳ���� ������ ���ϴ��� 1�� ���� �˻� 
	//-------------------------------------------------------
		if( TABS(pclClient->CurrentClock - dwLastAttackedVillageClock) > 60000)
		{
			dwLastAttackedVillageClock = pclClient->CurrentClock;
			if(bAttackedVillage == TRUE)
			{
				// ��ü �������� �˸� �޽����� ������. 
				TCHAR buffer[256];
				TCHAR* pText = GetTxtFromMgr(1436);
				StringCchPrintf(buffer, 256, pText, szName );
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, buffer);
				bAttackedVillage = FALSE;
			}
		}

	}
	else
	{
		if(pTitleBuffer == NULL)
		{
			LoadTitle();
		}
	}
	
	return TRUE;
}

BOOL cltVillageInfo::CreateVillageKingMonument()
{
	//������ �������϶� ��ȣ���� �����Ǿ� ���� �ʴ´ٸ� �����Ѵ�.

	if( pclClient->bVillageWarSwitch == true &&  pclVillageManager->IsVillageAtWar(siVillageUnique) == TRUE
		&& siKingMonumentUnique <= 0 )
	{


		cltIdentity clidentity;
		clidentity.MakeKingMonument(IDENTITY_VILLAGE_KINGMONUMENT, siVillageUnique);

		cltServer* pclserver = (cltServer*)pclClient;

		SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[siVillageUnique]->siMapUnique;

		//cyj ��Ȳ�� �����߾ӿ� �����ǵ��� ����
		SI32 centerx = 32;
		SI32 centery = 50;
		
		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_VILLAGE, 0);

		siKingMonumentUnique = pclserver->SetNPCChar(
			pclClient->GetUniqueFromHash(TEXT("KIND_KINGMONUMENT")) , siVillageUnique, &clidentity, 1, 0, 
			centerx, centery, siVillageUnique, NPCITEMMODE_NONE, &clinnerstatus );
		
		return TRUE;
	}

	//�������� �ƴҶ� ��ȣ���� �����Ѵٸ� �����Ѵ�.
	if( pclClient->bVillageWarSwitch == false || pclVillageManager->IsVillageAtWar(siVillageUnique) == false)
	{
		if(siKingMonumentUnique > 0 )
		{
			if(pclClient->pclCM->IsValidID(siKingMonumentUnique))
			{
				pclClient->pclCM->CR[siKingMonumentUnique]->DeleteInCell();
				pclClient->pclCM->DeleteChar(siKingMonumentUnique);
			}

			siKingMonumentUnique = 0;
		}
	}

	return FALSE;
	
}

// ���� ��Ȳ���� ���¸� DB�� �����ϵ��� �Ѵ�.
BOOL cltVillageInfo::SetVillageGodtoDB()
{
	cltStrInfo* pclinfo = pclVillageManager->pclCityHallManager->GetStrInfo(siVillageUnique);
	if(pclinfo == NULL)return FALSE;

	// ��Ȳ���� ���� �����Ұ��  �����ֱ⸶�� ���� 
	if(pclinfo->clCityhallStrInfo.siSymbolKind > 0  && siVillageGodCharUnique >0)
	{
		cltServer* pclserver = (cltServer*)pclClient;
		// ������ ��Ȳ������ �˻��ϰ� 
		if(pclserver->pclCM->IsValidID(siVillageGodCharUnique) && pclserver->pclCM->CR[ siVillageGodCharUnique ]->pclCI->clBI.siHomeVillage == siVillageUnique)
		{
			SI32 kind = pclserver->pclCM->CR[ siVillageGodCharUnique ]->GetKind();
			SI32 life = pclserver->pclCM->CR[ siVillageGodCharUnique ]->GetLife();
			SI32 mana = pclserver->pclCM->CR[ siVillageGodCharUnique ]->GetMana();
			SI32 capa = pclserver->pclCM->CR[ siVillageGodCharUnique ]->clIdentity.clGodInfo.siCapa;
	
			((cltCityHall *)(pclVillageManager->pclCityHallManager->pclStruct[siVillageUnique]))->SetSymbol(kind, life, mana, capa);
			return TRUE;
		}
	}

	return FALSE;
}


// ���� ��Ȳ���� ���¸� DB�� �����ϵ��� �Ѵ�.
BOOL cltVillageInfo::SetCastletoDB()
{
	cltStrInfo* pclinfo = pclVillageManager->pclCityHallManager->GetStrInfo(siVillageUnique);
	if(pclinfo == NULL)return FALSE;

	// ��Ȳ���� ���� �����Ұ��  �����ֱ⸶�� ���� 
	if(pclinfo->clCityhallStrInfo.siCastleKind > 0  && siCastleCharUnique >0)
	{
		cltServer* pclserver = (cltServer*)pclClient;
		// ������ ��Ȳ������ �˻��ϰ� 
		if(pclserver->pclCM->IsValidID(siCastleCharUnique) && pclserver->pclCM->CR[ siCastleCharUnique ]->pclCI->clBI.siHomeVillage == siVillageUnique)
		{
			SI32 kind = pclserver->pclCM->CR[ siCastleCharUnique ]->GetKind();
			SI32 life = pclserver->pclCM->CR[ siCastleCharUnique ]->GetLife();
			SI32 mana = pclserver->pclCM->CR[ siCastleCharUnique ]->GetMana();
			SI32 capa = pclserver->pclCM->CR[ siCastleCharUnique ]->clIdentity.clGodInfo.siCapa;
			
			((cltCityHall *)(pclVillageManager->pclCityHallManager->pclStruct[siVillageUnique]))->SetCastle(kind, life, mana, capa);
			return TRUE;
		}
	}

	return FALSE;
}

// ��Ȳ���� ���� �����Ѵ�.
BOOL cltVillageInfo::CreateVillageGod()
{
	cltStrInfo* pclinfo = pclVillageManager->pclCityHallManager->GetStrInfo(siVillageUnique);
	if(pclinfo==NULL)return FALSE;
	
	// DB���� ���������� ���� �����Ǿ� ���� �ʴٸ� ���� �����.
	if(pclinfo->clCityhallStrInfo.siSymbolKind > 0  && siVillageGodCharUnique <=0)
	{
		SI16 siGodKind = pclinfo->clCityhallStrInfo.siSymbolKind;
		SI32 siGodLife = pclinfo->clCityhallStrInfo.siSymbolLife;
		SI32 siGodMana = pclinfo->clCityhallStrInfo.siSymbolMana;
		SI16 siGodCapa = pclinfo->clCityhallStrInfo.siSymbolCapa;

		//if(siGodKind<=0)	siGodKind = pclClient->pclKindInfoSet->GetDefaultVillageGod();
		
		// ��Ȳ���� �׾��ִ°�� �������̶�� ���θ����� �ʴ´�.
		if(siGodLife<= 0 &&  pclClient->bVillageWarSwitch == true)	
		{
			return FALSE;
		}
		

		cltIdentity clidentity;
		clidentity.MakeGod(IDENTITY_VILLAGEGOD, siGodCapa);

		cltServer* pclserver = (cltServer*)pclClient;

		SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[siVillageUnique]->siMapUnique;

		//cyj ��Ȳ�� �����߾ӿ� �����ǵ��� ����
		SI32 centerx = 30;
		SI32 centery = 30;
		//SI32 centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		//SI32 centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_VILLAGE, 0);
		
		siVillageGodCharUnique = pclserver->SetNPCChar(
			siGodKind, siVillageUnique, &clidentity, 1, 0, 
			centerx, centery, siVillageUnique, NPCITEMMODE_NONE, &clinnerstatus );
		
		
		if(siVillageGodCharUnique)
		{
		
			// �����Ŀ� ��Ȱ�Ұ�� ü���� ȸ�������ش�.
			if(siGodLife<= 0)	
			{
				pclserver->pclCM->CR[ siVillageGodCharUnique ]->ParametaBoxAction();
				
				siGodLife = pclserver->pclCM->CR[ siVillageGodCharUnique ]->clPB.GetMaxLife();
				siGodMana = pclserver->pclCM->CR[ siVillageGodCharUnique ]->clPB.GetMaxMana();
				
				siGodCapa -= 4;

				if( siGodCapa < 100 )
					siGodCapa = 100;

				((cltCityHall *)(pclVillageManager->pclCityHallManager->pclStruct[siVillageUnique]))->SetSymbol(siGodKind, siGodLife, siGodMana, siGodCapa);
			}

			
			// ü�°� �������� �������ش�. 
			pclserver->pclCM->CR[ siVillageGodCharUnique ]->SetLife(siGodLife);
			pclserver->pclCM->CR[ siVillageGodCharUnique ]->SetMana(siGodMana);
			pclserver->pclCM->CR[ siVillageGodCharUnique ]->clIdentity.clGodInfo.siCapa = siGodCapa;
		}
		return TRUE;
	}
	return FALSE;

}


// ������ ���� �����Ѵ�.
BOOL cltVillageInfo::CreateCastle()
{
	cltStrInfo* pclinfo = pclVillageManager->pclCityHallManager->GetStrInfo(siVillageUnique);
	if(pclinfo == NULL)return FALSE;
	
	// DB���� ���������� ���� �����Ǿ� ���� �ʴٸ� ���� �����.
	if(pclinfo->clCityhallStrInfo.siSymbolKind > 0  && siCastleCharUnique <=0)
	{
		SI16 siCastleKind = pclinfo->clCityhallStrInfo.siCastleKind;
		SI32 siCastleLife = pclinfo->clCityhallStrInfo.siCastleLife;
		SI32 siCastleMana = pclinfo->clCityhallStrInfo.siCastleMana;		
		SI16 siCastleCapa = pclinfo->clCityhallStrInfo.siCastleCapa;		

		//if(siCastleKind<=0)	siCastleKind = pclClient->pclKindInfoSet->GetDefaultCastle();

		// ������ �׾��ִ°�� �������̶�� ���θ����� �ʴ´�.
		if(siCastleLife<= 0 &&  pclClient->bVillageWarSwitch == true)	
		{
			return FALSE;
		}
		
	
		// �߿����� �����Ա����� �����.
		cltIdentity clidentity;
		clidentity.MakeGod(IDENTITY_CASTLE, siCastleCapa);

		cltServer* pclserver = (cltServer*)pclClient;

		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_VILLAGE, 0);

		//cyj ���� ��ġ ����
		//siCastleCharUnique = pclserver->SetNPCChar(siCastleKind, siVillageUnique, &clidentity, 1, 0, PosX-1, PosY+2, 0, NPCITEMMODE_NONE, &clinnerstatus );
		siCastleCharUnique = pclserver->SetNPCChar(siCastleKind, siVillageUnique, &clidentity, 1, 0, PosX-1, PosY+3, 0, NPCITEMMODE_NONE, &clinnerstatus );
		
		
		if(siCastleCharUnique)
		{
			// �����Ŀ� ��Ȱ�Ұ�� ü���� ȸ�������ش�.
			if(siCastleLife<= 0)	
			{
				pclserver->pclCM->CR[ siCastleCharUnique ]->ParametaBoxAction();

				siCastleLife = pclserver->pclCM->CR[ siCastleCharUnique ]->clPB.GetMaxLife()/10;
				siCastleMana = pclserver->pclCM->CR[ siCastleCharUnique ]->clPB.GetMaxMana()/10;
				
				siCastleCapa = ((cltCityHall *)(pclVillageManager->pclCityHallManager->pclStruct[siVillageUnique]))->clStrInfo.clCityhallStrInfo.siCastleCapa;

				((cltCityHall *)(pclVillageManager->pclCityHallManager->pclStruct[siVillageUnique]))->SetCastle(siCastleKind, siCastleLife, siCastleMana, siCastleCapa);

			}
			
			// ü�°� �������� �������ش�. 
			pclserver->pclCM->CR[ siCastleCharUnique ]->SetLife(siCastleLife);
			pclserver->pclCM->CR[ siCastleCharUnique ]->SetMana(siCastleMana);
			pclserver->pclCM->CR[ siCastleCharUnique ]->clIdentity.clGodInfo.siCapa		= siCastleCapa;
		}
		return TRUE;
	}
	return FALSE;

}

// PersonID�� �ִ� �������� Ȯ���Ѵ�. 
BOOL cltVillageInfo::IsMostBeholder(SI32 personid)
{
	// �ִ� ���ֿ� ���� PersonID�� ����ϴ��� Ȯ���Ѵ�. 
	if(clVillageVary.clInvestInfo.clInvestInfo[0].clPerson.GetPersonID() == personid)
	{
		// �ִ����ִ� ������ �����ֽ� ������ �ٸ��� ������ ������Ʈ �ؾ� �Ѵ�. 

		return TRUE;
	}

	return FALSE;
}

void  cltVillageInfo::Draw(SI32 dotx, SI32 doty)
{
	if( pTitleBuffer == NULL ) return;

	GP.PutXpr16( dotx - TitleImageXsize / 2, 
				 doty - 20, 
		         300, 
				 64,
				 (RGB16*)pTitleBuffer, 
				 RGB16_TRANS );

}

