#include "../../Client/Client.h"
#include <Graphic_Capsule.h>

//#include "../../Client/ColorTable/ColorTable.h"

#include <Mouse.h>	
#include "Util/Util.h"
#include "DevTool/DevCharInfo/DevCharInfo.h"
#include "DevTool/DevNPCInfo/DevNPCInfo.h"

#include "../../../common/Item/ItemCommon/cltSetItem.h"
#include "../../../Client/Client_BokBulBokMgr/Client_BBBMgr.h"

//#include "School/School.h"

// ä��. 
#include "../../Client/Interface/DrawChat/DrawChat.h"
// ĳ���� �̸� ���
#include "../../Client/Interface/DrawCharName/DrawCharName.h"
// Ǯ��ũ�� ���� �ƴϳ�
#include "../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../../Client/NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

// ��Ƽ ���� ��� ������...
//#include "../../Client/Interface/PartyDlg/PartyDlg.h"
// ����ġ ǥ�� 
#include "../../Client/Effect/ExpCounter/ExpCounter.h"
// ġ��   ǥ�� 
#include "../../Client/Effect/HealCounter/HealCounter.h"
// �ʻ�� ǥ��
#include "CharCriticalEffect/CharCriticalEffect.h"
// ��Ƽ ���� ǥ�� �ϱ� ���ؼ�.
#include "CharPartyEmoticon/CharPartyEmoticon.h"
// ��ƿ ������ ���� �� ǥ��
#include "CharJim/CharJim.h"
// ������ ĳ���� ���ǽ� ������. 
#include "Char/CCD/CCDSurfaceMgr.h"
#include "Smoke/Smoke.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"
#include "../Client/NInterface/NPartyDlg/NPartyDlg.h"
#include "../Client/Ninterface/NMinimapdlg/NMinimapDlg.h"
#include "../Client/MarkManager/MarkManager.h"

#include "Guild/Guild.h"

#include "../common/SystemNPC/SystemNPC.h"
#include "../CommonLogic/CommonLogic.h"
//#include "../Common/CommonHeader.h"
#include "../common/Event/event.h"
#include "../common/Skill/Skill-Manager.h"

#include "../CommonLogic/Marriage/MarriageManager.h"

extern cltCommonLogic* pclClient;
extern	SHORT					GameMouseX, GameMouseY;
extern	RECT				ScreenRect;							// ������ ǥ�õǴ� ���� 
extern DWORD dwQuitTimer;

#define COLOR_BORDER       246

#define ENERGY_UNIT_SIZE	3

enum QUEST_DISPLAY_MARK
{
	QUEST_DISPLAY_MARK_NONE = 0,
	QUEST_DISPLAY_MARK_GREETING,
	QUEST_DISPLAY_MARK_GOING,
	QUEST_DISPLAY_MARK_CLEAR,

	//---------------------------------------
	// �� ���� �߰��� �ּ���
	//---------------------------------------
	QUEST_DISPLAY_MARK_MAX
};

// ĳ������ �̸��� �����.
bool cltCharClient::MakeCharName(cltCharClient* pclchar)
{
	cltClient* pclclient = (cltClient*)pclClient; 
	// ���콺�� ��ġ�� ĳ���͸� ã��.
	SI32 undermouseid = pclclient->pclUnderMouseObject->GetUnderMouseID();

	if(pclchar == NULL)pclchar = this;

	// ���� �̸� ����. 
	if(pclchar->pclKI->IsAtb(ATB_HORSE))return false;

	// [����] ������ : ��Ƽ�δ� �Ա� NPC��� ����
	if ( pclchar->GetKind() == pclclient->GetUniqueFromHash( TEXT("KIND_PIRATESHIP_GATE") ) || 
		pclchar->GetKind() == pclclient->GetUniqueFromHash( TEXT("KIND_SANTAGATE") )) return false;

	// [����] ��ȣ����_090525 : ��ȣ�����϶��� �ƹ������� �Ⱥ��δ�
	if ( IDENTITY_SOULGUARD == pclchar->clIdentity.siIdentity )
	{
		return false;
	}

	SI32 interval = 0;
	if(IsPC(pclchar->GetCharUnique())  == true)
	{
		// ���� ���콺�� �÷����Ҵٸ� ���� ������ �߰��� ǥ�����ֱ⶧���� ���� ���� �������ش�.
		if(pclchar->GetID() == undermouseid)
			interval = 20;
		else
			interval = 40;
	}
	else 		// PC�� �ƴѰ��� �������� �ʴ´�.
	{
		if ( pclDrawCharName->IsSet() == true &&
			pclchar->clIdentity.siIdentity	!= IDENTITY_PERSON_SUMMON )
			return false;

		// ���� ���콺�� �÷����Ҵٸ� ���� ������ �߰��� ǥ�����ֱ⶧���� ���� ���� �������ش�.
		if(pclchar->GetID() == undermouseid)
			interval = 20;
		else
			return false;
	}

	if(TABS(pclClient->GetFrame() - dwLastMakeCharNameFrame ) < interval)
		return false;
	dwLastMakeCharNameFrame  = pclClient->GetFrame();

	//if(TABS(pclClient->GetFrame() - dwLastMakeCharNameFrame ) < interval)return false;
	//dwLastMakeCharNameFrame  = pclClient->GetFrame();

	TCHAR temp[256]		= TEXT("");
	TCHAR buffer[256]	= TEXT("");
	TCHAR buffer2[256]	= TEXT("");
	TCHAR rankname[256]	= TEXT("");

	//StringCchCopy(buffer, 256, TEXT(""));

	// Identity �� �����ϴ� Ư�� ĳ������ ��� , ���� ����
	switch(pclchar->clIdentity.siIdentity)
	{
	case IDENTITY_CASTLE:		
		StringCchPrintf(buffer, 256, TEXT("Lv%d "), max(1, pclchar->clIdentity.clGodInfo.siCapa - 99));		break;
	case IDENTITY_VILLAGEGOD:	
		StringCchPrintf(buffer, 256, TEXT("Lv%d "), max(1, pclchar->clIdentity.clGodInfo.siCapa - 99));		break;
	case IDENTITY_VILLAGEGOD_SUMMON:
		StringCchPrintf(buffer, 256, TEXT("Lv%d "), max(1, pclchar->clIdentity.clGodInfo.siCapa - 99));		break;
	case IDENTITY_PERSON_SUMMON:
		StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->pclCI->clIP.GetLevel());				break;
	case IDENTITY_VILLAGEHUNT:
		StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->pclCI->clIP.GetLevel());				break;
	case IDENTITY_INSTANCEMAP:
		StringCchPrintf(buffer, 256, TEXT(""));														break;
	case IDENTITY_SOULGUARD:
		StringCchPrintf(buffer, 256, TEXT(""));														break;
	default:	
		{
			if(pclchar->GetID() == 1) // �ڱ� �ڽ��̸� ���� ǥ�� ������.
				break;		

			if(pclchar->pclKI->IsAtb(ATB_SYSTEMNPC))
				break;

			// ���콺�� �÷����ִ� ĳ�����̰ų� �÷���ĳ���Ͱ� �ƴϸ� ������ ǥ���Ѵ�.
			if(pclchar->GetID() == undermouseid || IsPC(pclchar->GetCharUnique()) == false )
			{
				StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->pclCI->clIP.GetLevel());	

				//if ( pclClient->siServiceArea == ConstServiceArea_China )
				//{
				//	if ( IsPC(pclchar->GetCharUnique()) == false )
				//	{
				//		if ( pclchar->pclKI->IsAtb(ATB_BOSS) )
				//		{
				//			StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->clPB.GetBossBattleLevel() );
				//		}
				//		else
				//		{
				//			StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->clPB.GetBattleLevel() );
				//		}
				//	}
				//	else
				//	{
				//		StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->pclCI->clIP.GetLevel() );
				//	}
				//}
				//else
				//{
				//		StringCchPrintf(buffer, 256, TEXT("Lv%d "), pclchar->pclCI->clIP.GetLevel());		
				//}
				//break;
			}
		}

	}

	SI32 guildicon = -1 ;
	TSpr* guildspr	= NULL;

	// naming - 
	if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel )
	{
		if(_tcscmp(pclchar->GetName(), TEXT("")) != 0)
		{
			TCHAR temp[256];
			//if ( pclchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_GWANGGAETOMONUMENT")) 
			//	&& pclchar->pclMap->siMapIndex == MAPINDEX_DOCKDO )
			//{

			//	TCHAR* pText = GetTxtFromMgr(3513);
			//	StringCchPrintf(temp, 256, TEXT("[%s]"), pText);
			//	StringCchCat(buffer2, 256, temp);
			//}
			//else
			//{
			StringCchPrintf(temp, 256, TEXT("[%s]"), pclchar->GetName());
			StringCchCat(buffer, 256, temp);
			//}
		}

		// ��� ���ѿ� ���� ǥ�� ������ �ٸ���. 
		if(pclCM->IsValidID(1) && pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
		{
			if(((cltClient*)pclClient)->bWatchModeSwitch == false)
			{
				StringCchPrintf(temp, 256, TEXT("(%d)%d"), pclchar->CharUnique, pclchar->clPB.GetBattlePower());
				StringCchCat(buffer, 256, temp);
			}
		}


		cltNamingQuestUnit* pclUnit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );

		TCHAR buf2[256] = {0,};

		if( pclUnit != NULL )
		{
			StringCchPrintf( buf2, 256, TEXT("\r%s"), pclUnit->GetNaming() );
			StringCchCat( buffer, 256, buf2 );
		}

		// ��� ���� ���
		if ( pclCI->clBI.clGuildRank.IsGuildMember() && 
			pclchar->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_STANDING )
		{
			pclclient->m_pMarkManager->GetMarkSprAndFontIndex( pclCI->clBI.clGuildRank.siMarkIndex, &guildspr, &guildicon );
		}
	}
	else
	{
		// �ź��� �����ش�. 
		if(pclchar->pclCI->clCharRank.siType || pclchar->pclCI->clBI.uiGRank )
		{
			if(GetRankName(&pclchar->pclCI->clCharRank, rankname, 256, pclchar->pclCI->clBI.uiGRank) == TRUE)
			{
				StringCchCat(buffer, 256, rankname);
			}
		}

		if(IsPC(pclchar->GetCharUnique()))
		{
			////cyj GM Mode�� Show(1)�̸� [GM]��ũ ���
			//if(pclchar->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
			//	StringCchPrintf(buffer2, 256, TEXT("[GM]"));

			//cyj GM Mode�� Hide(2)�̸� [HIDE]��ũ ���
			if(pclchar->pclCI->clBI.uiGMMode == GMMODE_ATB_HIDE)
				StringCchPrintf(buffer2, 256, TEXT("[HIDE]"));

			if(pclchar->pclCI->clBI.uiGMMode != GMMODE_ATB_GMSHOW)
			{
				TCHAR* pvillagename = pclClient->pclVillageManager->GetName(pclchar->pclCI->clBI.siHomeVillage);
				if(pvillagename)
				{
					StringCchCat(buffer2, 256, pvillagename);
				}
			}


		}

		if(_tcscmp(pclchar->GetName(), TEXT("")) != 0)
		{
			TCHAR temp[256];
			//if ( pclchar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_GWANGGAETOMONUMENT")) 
			//	&& pclchar->pclMap->siMapIndex == MAPINDEX_DOCKDO )
			//{

			//	TCHAR* pText = GetTxtFromMgr(3513);
			//	StringCchPrintf(temp, 256, TEXT("[%s]"), pText);
			//	StringCchCat(buffer2, 256, temp);
			//}
			//else
			//{
			StringCchPrintf(temp, 256, TEXT("[%s]"), pclchar->GetName());
			StringCchCat(buffer2, 256, temp);
			//}
		}

		// ��� ���ѿ� ���� ǥ�� ������ �ٸ���. 
		if(pclCM->IsValidID(1) && pclCM->CR[1]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
		{
			if(((cltClient*)pclClient)->bWatchModeSwitch == false)
			{
				StringCchPrintf(temp, 256, TEXT("(%d)%d"), pclchar->CharUnique, pclchar->clPB.GetBattlePower());
				StringCchCat(buffer2, 256, temp);
			}
		}

		// �̸� ���� ���. 
		if(_tcscmp(buffer2, TEXT("")) != 0)
		{
			StringCchCat(buffer, 256, TEXT("\r\n"));
			StringCchCat(buffer, 256, buffer2);
		}

		// ��� ���� ���
		if ( pclCI->clBI.clGuildRank.IsGuildMember() && 
			pclchar->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_STANDING )
		{
			if ( pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_MASTER )
			{
				TCHAR* pRank = GetTxtFromMgr(6540);
				StringCchCat(buffer, 256, TEXT("\r\n"));
				StringCchPrintf(temp, 256, TEXT("%s %s"), pclCI->clBI.clGuildRank.szGuildName,pRank);
				StringCchCat(buffer, 256, temp);
			}
			else if ( pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_SECONDMASTER )
			{
				TCHAR* pRank = GetTxtFromMgr(6541);
				StringCchCat(buffer, 256, TEXT("\r\n"));
				StringCchPrintf(temp, 256, TEXT("%s %s"), pclCI->clBI.clGuildRank.szGuildName,pRank);
				StringCchCat(buffer, 256, temp);
			}
			else
			{
				StringCchCat(buffer, 256, TEXT("\r\n"));
				StringCchPrintf(temp, 256, TEXT("%s"), pclCI->clBI.clGuildRank.szGuildName);
				StringCchCat(buffer, 256, temp);
			}

			pclclient->m_pMarkManager->GetMarkSprAndFontIndex( pclCI->clBI.clGuildRank.siMarkIndex, &guildspr, &guildicon );
			//guildspr = pclClient->GetGlobalSpr( GIMG_VILLAGEMARK01 );
			//guildicon = pclCI->clBI.clGuildRank.siMarkIndex - 1 ;
		}
	}





	StringCchCopy(szCharNameInfo, 128, buffer);

	SI32 icon		= 0;
	TSpr* pspr	= NULL;

	// MVP�϶�
	if( pclchar->pclCI->clBI.uiGMMode == GMMODE_ATB_WARMVP )
	{
		pspr = pclClient->GetGlobalSpr( GIMG_MVPMARK1 );
		icon = 0;

	}
	// ���� ��ũ 
	else if( pclchar->pclCI->clBI.siHomeVillage > 0 ) 
	{
		if( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������ 
		{
			// ������忡 �������� �������� �ʴ´�.
			if ( IsGuildWarMap_Use_New_GuildWar(pclchar->GetMapIndex()) == false  ||
				IsGuildWarMap_NEW(pclchar->GetMapIndex()) == false )//���� ������̰ų� ���ο� ������϶�
			{
				if( pclchar->pclCI->clBI.uiGMMode != GMMODE_ATB_GMSHOW)
				{
					SI32 villagemark = 0;
					if( pclchar->pclCI->clBI.siHomeVillage >= 0 && pclchar->pclCI->clBI.siHomeVillage < MAX_VILLAGE_NUMBER )
						villagemark = ((cltClient*)pclClient)->pclVillageManager->pclVillageInfo[ pclchar->pclCI->clBI.siHomeVillage ]->clVillageVary.siVillageMark;

					if( villagemark > 0 ) {
						pclclient->m_pMarkManager->GetMarkSprAndFontIndex( villagemark, &pspr, &icon );
					}
				}
			}
		}
		else	// ������
		{
			// ������忡 �������� �������� �ʴ´�.
			if ( IsGuildWarMap_Not_Use_New_GuildWar(pclchar->GetMapIndex()) == false /* ||
				IsGuildWarMap_NEW(pclchar->GetMapIndex()) == false*/ )//���� ������̰ų� ���ο� ������϶�
			{
				if( pclchar->pclCI->clBI.uiGMMode != GMMODE_ATB_GMSHOW)
				{
					SI32 villagemark = 0;
					if( pclchar->pclCI->clBI.siHomeVillage >= 0 && pclchar->pclCI->clBI.siHomeVillage < MAX_VILLAGE_NUMBER )
						villagemark = ((cltClient*)pclClient)->pclVillageManager->pclVillageInfo[ pclchar->pclCI->clBI.siHomeVillage ]->clVillageVary.siVillageMark;

					if( villagemark > 0 ) {
						pclclient->m_pMarkManager->GetMarkSprAndFontIndex( villagemark, &pspr, &icon );
					}
				}
			}
		}
	}

	SI32 sex = 0;
	// ���ڰų� �����̸�, 
	if(pclchar->pclCI->clBI.uiSex || IsPC(pclchar->GetCharUnique()) == false)
	{
		sex = 1;
	}

	// ������� ���� ���� ��ũ
	TSpr*	psprEmblem		= NULL;
	SI32	siEmblemIndex	= -1; // ���� �ε����� 0�����̱� ������ -1�� �ʱⰪ�� ��ƾ� �Ѵ�

	if ( IsPC(pclchar->GetCharUnique()) && (SKILLMSTER_WEAPONTYPE_NONE < pclchar->m_uiWeaponSkillMasterEmblem) && (SKILLMSTER_WEAPONTYPE_MAX > pclchar->m_uiWeaponSkillMasterEmblem) )
	{
		psprEmblem		= pclClient->GetGlobalSpr( GIMG_EMBLEM );
		siEmblemIndex	= (pclchar->m_uiWeaponSkillMasterEmblem-1); // ���� �ε����� 0�̱� ������ -1�� ����� �Ѵ�(m_uiWeaponSkillMasterEmblem�� ��ȿ���� 1�����̴�)
	}

	// ��� ��ũ ��� ���� 

	//if(pclClient->siServiceArea == ConstServiceArea_Japan)
	//{
	//	guildicon = -1;
	//}

	pclDrawCharName->Set( pclclient->pclDrawCharNameSurface, szCharNameInfo, pspr, icon, sex, pclchar->pclCI->clBI.uiGMMode,guildicon ,guildspr, siEmblemIndex, psprEmblem );

	return true;
}

// ĳ������ �̸��� ǥ���Ѵ�. 
void cltCharClient::DrawName()
{

	if(pclDrawCharName)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 startx = DrawStartX+(ImageXsize/2);
		SI32 starty =  0 ;

		if(selectRealAnyType( ))
			starty = DrawStartY+ImageYsize - pclKI->GetBottomIndent();
		else
			starty = DrawStartY+ImageYsize - GetKindInfo(true)->GetBottomIndent();

		pclDrawCharName->Draw( startx, starty);
	}
}


// ����ȿ�� ��� �Լ�.	   
BOOL cltCharClient::DrawGeneralEft()
{
	if ( (clPB.siGeneralAC <= 0) && (clPB.siGeneralDamage <= 0) )
	{
		return FALSE;
	}

	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_DEFUP);

	if(pspr == NULL)return FALSE;

	SI32 font = 0;
	if(clPB.siGeneralDamage && clPB.siGeneralAC)
	{
		font = 26;
	}
	else if(clPB.siGeneralDamage)
	{
		font = 0;
	}
	else if(clPB.siGeneralAC)
	{
		font = 13;
	}

	font = font + (pclClient->CurrentClock / 200)  % 13;

	if(selectRealAnyType( ))
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		GP.PutSpr(pspr, DrawStartX + ImageXsize/2 - pspr->GetXSize() /2, 
			DrawStartY + ImageYsize   - pspr->GetYSize() /2 -pclKI->clKIDrawInfo.siBottomIndent, 
			font);
	}
	else
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		GP.PutSpr(pspr, DrawStartX + ImageXsize/2 - pspr->GetXSize() /2, 
			DrawStartY + ImageYsize   - pspr->GetYSize() /2 - GetKindInfo(true)->clKIDrawInfo.siBottomIndent, 
			font);
	}

	return TRUE;
}

// ĳ������ �׸��ڸ� ����ϴ� �Լ� 
BOOL cltCharClient::DrawShadow()
{
	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	// by LEEKH 2007.12.24 - TRANSFORM
	if ( ppclKI->clKIDrawInfo.bHideShadow == true ) return FALSE ;

	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_CHARSHADOW);

	if(pspr == NULL)return FALSE;

	SI32 font ;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 data = (ppclKI->clKIDrawInfo.siXsizePercent * ImageXsize) / 100;

	if(data < 40)
	{
		font = 2;
	}
	else if(data < 50)
	{
		font = 1;
	}
	else 
	{
		font  = 0;
	}

	// by LEEKH 2007.12.24 - TRANSFORM
	GP.PutSprShadow(pspr, DrawStartX + ImageXsize/2 - pspr->GetXSize() /2, 
		DrawStartY + ImageYsize   - pspr->GetYSize() /2 - ppclKI->clKIDrawInfo.siBottomIndent, 
		font);


	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Description	:	ĳ���͸� ���� ��ǥ(DrawStartX, DrawStartY)�� ����Ѵ�. 
void cltCharClient::CalculateDrawStartXY()
{
	SHORT centerx = 0, centery = 0;

	SHORT x = GetX();
	SHORT y = GetY();


	cltMapClient* pclmap = (cltMapClient*)pclMap;

	// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ����ǥ)
	pclmap->GetCenterXYByMapCenterXY(x, y, centerx, centery);

	bool selectKind = false;
	if(selectRealAnyType( ))
	{
		selectKind = pclKI->IsAtb(ATB_HERO);
	}
	else
	{
		selectKind = GetKindInfo(true)->IsAtb(ATB_HERO);
	}

	// ���ΰ� ĳ������ ũ��� ������ �ִ�. 
	if(selectKind)
	{
		ImageXsize = 320;
		ImageYsize = 240;

		DrawStartX = centerx - ImageXsize/2 + siRX;
		DrawStartY = centery - ImageYsize + pclKI->GetBottomIndent() + siRY + VibrateY;
	}
	else
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 ref = GetKindInfo(true)->clCharAniManager.FindFirstAni();
		if(ref <= 0)MsgBox(TEXT("fd9jfd"), TEXT("fd9jf:%s"), GetName());

		// by LEEKH 2007.12.24 - TRANSFORM
		ImageXsize = GetKindInfo(true)->clCharAniManager.GetImageXsize(ref, pclClient->CurrentClock);
		ImageYsize = GetKindInfo(true)->clCharAniManager.GetImageYsize(ref, pclClient->CurrentClock);

		// by LEEKH 2007.12.24 - TRANSFORM
		DrawStartX = centerx - ImageXsize/2 + siRX;
		DrawStartY = centery - ImageYsize + GetKindInfo(true)->GetBottomIndent() + siRY + VibrateY;
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���� ��ġ�� ����Ѵ�. 
void cltCharClient::CalculateDrawStartXYInMapCaptureMode()
{
	SHORT centerx=0, centery=0;

	SHORT x=GetX();
	SHORT y=GetY();


	// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ����ǥ)
	SI32 mapcenterx = 0, mapcentery = 0;
	pclMap->GetXYDotFromXYCord(x, y, mapcenterx, mapcentery);

	centerx=mapcenterx;
	centery=mapcentery;

	// by LEEKH 2007.12.24 - TRANSFORM
	DrawStartX=centerx-ImageXsize/2 + GetRX();

	if(selectRealAnyType( ))
		DrawStartY=centery-ImageYsize + pclKI->GetBottomIndent() + GetRY() + VibrateY;
	else
		DrawStartY=centery-ImageYsize + GetKindInfo(true)->GetBottomIndent() + GetRY() + VibrateY;

}


// �� ǳ���� �׸���. 
void cltCharClient::DrawChatBalloon()
{
	if(pclDrawChat)
	{
		cltKindInfo* ppclKI = pclKI;

		if(selectRealAnyType( ) == false)
			ppclKI = GetKindInfo(true);

		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize	= ppclKI->clKIDrawInfo.siXsizePercent*ImageYsize/100;
		SI32 centery	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 20;


		// [����] ���Žÿ� ��ǳ�� �����ġ �ٽ� ��� - 2008.01.31
		if ( clTransFormInfo.bTransFormMode == TRUE )
		{
			realysize	= (SI32)((ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize) / 100);
			centery		= DrawStartY + (ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize);
		}
		else
		{
			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				centery -= 20;
			}
		}

		// �ɾ��������� ���� �Ʒ���
		if(GetCurrentOrder() == ORDER_SITDOWN)
		{
			centery += 20;
		}

		pclDrawChat->Draw(DrawStartX+ImageXsize/2, centery, &ScreenRect);
	}
}

// �ź� ǥ�ø� �Ѵ�. 
void cltCharClient::DrawRankMark(SI32 font)
{
	//if( pclClient->siServiceArea ==  ConstServiceArea_Korea )
	//{

	//	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_RANKMARK);

	//	if(pspr == NULL)return ;

	//	SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

	//	SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	//	SI32 starty	= DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize() /2 - 15;

	//	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	//	if(pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
	//	{
	//		starty -= 20;
	//	}

	//	// �ɾ��������� ���� �Ʒ���
	//	if(GetCurrentOrder() == ORDER_SITDOWN)
	//	{
	//		starty += 20;
	//	}

	//	GP.PutSpr(pspr, startx,		starty,	 font);

	//}
	//else if( pclClient->siServiceArea == ConstServiceArea_China )
	//{
	//	SI32 startx = DrawStartX + ImageXsize/2 - m_RankMarkEncHres/2 ;
	//	SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	//	SI32 starty	= DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - realysize - m_RankMarkEncVres - 15;


	//	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	//	if(pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
	//	{
	//		starty -= 20;
	//	}

	//	// �ɾ��������� ���� �Ʒ���
	//	if(GetCurrentOrder() == ORDER_SITDOWN)
	//	{
	//		starty += 20;
	//	}

	//	if ( m_RankMarkImgEncBuffer )
	//	{
	//		GP.PutXpr16( startx  , starty , 
	//			//MAX_RANKMARK_WIDTH, MAX_RANKMARK_HEIGHT,
	//			m_RankMarkEncHres, m_RankMarkEncVres,
	//			m_RankMarkImgEncBuffer,
	//			RGB16_TRANS );
	//	}

	//}
	//else
	//{
	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	SI32 startx = DrawStartX + ImageXsize/2 - m_RankMarkEncHres/2 ;
	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - m_RankMarkEncVres - 15;

	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	SI32 siHorseUnique = 0;
	if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) == HORSEUNIQUE_SASURI)
	{
		starty -= HORSE_EFFECTHIGHT_NORMAL_SASURI;
	}
	else
	{
		if( siHorseUnique != 0 )
		{
			starty -= 20;
		}
	}

	// �ɾ��������� ���� �Ʒ���
	if(GetCurrentOrder() == ORDER_SITDOWN)
	{
		starty += 20;
	}

	if ( m_RankMarkImgEncBuffer )
	{
		GP.PutXpr16( startx  , starty , 
			//MAX_RANKMARK_WIDTH, MAX_RANKMARK_HEIGHT,
			m_RankMarkEncHres, m_RankMarkEncVres,
			m_RankMarkImgEncBuffer,
			RGB16_TRANS );
	}
	//}
}

// �ְ� ���� ǥ�ø� �Ѵ�. 
void cltCharClient::DrawMakeMasterMark(SI32 skillunique)
{
	if(skillunique < 1)return ;

	TSpr* pspr;
	SI32 font = skillunique - 1;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);


	// ���굵�����ۼ�(unique:54) �� ��쿡�� font 14���
	if ( skillunique == SKILL_MAKETOOL1 )
	{
		font = 14;
	}

	// [����] ����ü ���� ���� ǥ�� => 2008-5-15
	if ( skillunique == SKILL_ARTIFACT )
	{
		font = 27;
	}

	// PCK : �ƹ�Ÿ ���� ������ �߰� (0907.23)
	if(skillunique == SKILL_MAKEAVATAR_DRESS)
	{
		font = 13;
	}
	else if(skillunique == SKILL_MAKEAVATAR_HAT)
	{
		font = 31;
	}
	else if(skillunique == SKILL_MAKEAVATAR_MANTLE)
	{
		font = 35;
	}
	else if(skillunique == SKILL_MAKEAVATAR_RING)
	{
		font = 12;
	}
	else if(skillunique == SKILL_MAKEAVATAR_NECK)
	{
		font = 24;
	}

	pspr = pclClient->GetGlobalSpr(GIMG_MAKEMASTER);

	if(pspr == NULL)return ;

	SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize() /2 - 10;

	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	SI32 siHorseUnique = 0;
	if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) == HORSEUNIQUE_SASURI)
	{
		starty -= HORSE_EFFECTHIGHT_NORMAL_SASURI;
	}
	else
	{
		if( siHorseUnique != 0 )
		{
			starty -= 20;
		}
	}

	// �ɾ��������� ���� �Ʒ���
	if(GetCurrentOrder() == ORDER_SITDOWN)
	{
		starty += 20;
	}

	GP.PutSpr(pspr, startx,		starty,	 font);

}

// GM��ũ�� ǥ���Ѵ�.
void cltCharClient::DrawGMMark()
{
	TSpr* pspr;
	SI32 font = 0;

	bool bResult = true;
	switch(pclCI->clBI.uiGMMode)
	{
		//[�߰� : Ȳ���� 2007. 11. 27 ����̸� ������ �����Ų GM ��忡 ��ũ �׸���.]
	case GMMODE_ATB_BUFF:	bResult = false; 
		break;

	case GMMODE_ATB_GMSHOW: bResult = false; 
		break;
	}

	if(bResult)
	{
		return;
	}

	pspr = pclClient->GetGlobalSpr(GIMG_GMMARK);

	if(pspr == NULL)return ;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize() /2 - 10;

	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	SI32 siHorseUnique = 0;
	if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) == HORSEUNIQUE_SASURI)
	{
		starty -= HORSE_EFFECTHIGHT_NORMAL_SASURI;
	}
	else
	{
		if( siHorseUnique != 0 )
		{
			starty -= 20;
		}
	}

	// �ɾ��������� ���� �Ʒ���
	if(GetCurrentOrder() == ORDER_SITDOWN)
	{
		starty += 20;
	}

	GP.PutSpr(pspr, startx,		starty,	 font);

}

// [����] ���Һ� ���϶� �Ӹ����� �̹��� ����� (��ų, Ű, ��������) - 1 : ��ų��(4), 2 : Ű��(3), 3 : ������(2)
void cltCharClient::DrawBBBSpecialIndicator( SI32 siType )
{
	cltKindInfo* ppclKI = pclKI;
	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	TSpr* pspr = pclClient->GetGlobalSpr(GIMG_PVP_COUNTDOWN);		// Ư���� ǥ�ÿ� �̹��� ����� �� �̹����� enum�� ����� ���� gimg_bbbspecialindicator ���� �̸�

	if ( NULL != pspr )
	{
		SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
		SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize() /2 - 10;

		GP.PutSpr(pspr, startx,	starty,	siType );	// ������ 0�� ���߿� �̹��� ���� ����� �ش� �̹����� �ε����� ����. 3�� �ʿ�
	}
}

//[�߰� : Ȳ���� 2008. 1. 15 => �ְ������ ��ũ�� ǥ���ϴ� �Լ�]
void cltCharClient::DrawBestGuildMark(void)
{
	static TSpr Spr("gimg/BestGuildMark.SPR");
	if(NULL == Spr.pImage)
	{
		MsgBox("���Ͽ��� ����", "BestGuildMark.SPR");
	}

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	SI32 startx = DrawStartX + ImageXsize/2 - Spr.GetXSize() /2;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - Spr.GetYSize() /2 - 10;

	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	SI32 siHorseUnique = 0;
	if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) == HORSEUNIQUE_SASURI)
	{
		starty -= HORSE_EFFECTHIGHT_NORMAL_SASURI;
	}
	else
	{
		if( siHorseUnique != 0 )
		{
			starty -= 20;
		}
	}

	// �ɾ��������� ���� �Ʒ���
	if(GetCurrentOrder() == ORDER_SITDOWN)
	{
		starty += 20;
	}

	GP.PutSprAlpha(&Spr, startx, starty, 13, 0);
}

void cltCharClient::DrawPCRoomMark( void )
{
	TSpr* psprPCRoomMark = pclClient->GetGlobalSpr( GIMG_PCROOM_CHAR_HEAD );
	if ( NULL == psprPCRoomMark )
	{
		return;
	}

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	SI32 startx = DrawStartX + ImageXsize/2 - psprPCRoomMark->GetXSize() /2;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - psprPCRoomMark->GetYSize() /2 - 10;

	// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
	SI32 siHorseUnique = 0;
	if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) == HORSEUNIQUE_SASURI)
	{
		starty -= HORSE_EFFECTHIGHT_NORMAL_SASURI;
	}
	else
	{
		if( siHorseUnique != 0 )
		{
			starty -= 20;
		}
	}

	// �ɾ��������� ���� �Ʒ���
	if(GetCurrentOrder() == ORDER_SITDOWN)
	{
		starty += 20;
	}

	GP.PutSprAlpha(psprPCRoomMark, startx, starty, 13, 0);
}
/*
void cltCharClient::DrawArrow()
{
	TSpr* psprEffect	= pclClient->GetGlobalSpr(GIMG_ARROWEFFECT);
	if(psprEffect == NULL)return ;

	SI32 startx = DrawStartX + ImageXsize/2 - psprEffect->GetXSize() /2;
	SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - realysize - psprEffect->GetYSize() /2 - 15;
	starty -= 25;

	SI32 font = 0;
	font = font + (pclClient->CurrentClock / 40)  % psprEffect->GetImageNum();

	GP.PutSprScreen(psprEffect, startx, starty, font);
}
*/

void cltCharClient::DrawQuestion()
{
	TSpr* psprEffect	= pclClient->GetGlobalSpr(GIMG_QUESTNPCEFFECT);
	if(psprEffect == NULL)return ;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 startx = DrawStartX + ImageXsize/2 - psprEffect->GetXSize() /2;
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - psprEffect->GetYSize() /2 - 15;
	starty -= 37;

	SI32 font = 0;
	font = font + TABS((pclClient->CurrentClock / 80))  % 6;

	GP.PutSpr(psprEffect,startx,starty,font);
	GP.PutSprScreen(psprEffect, startx, starty, font+6);
}


void cltCharClient::DrawRedExclamation()
{
	TSpr* psprEffect	= pclClient->GetGlobalSpr(GIMG_QUESTNPCEFFECT);
	if(psprEffect == NULL)return ;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 startx = DrawStartX + ImageXsize/2 - psprEffect->GetXSize() /2;
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - psprEffect->GetYSize() /2 - 15;
	starty -= 37;

	SI32 font = 12;
	font = font + TABS((pclClient->CurrentClock / 80))  % 6;

	GP.PutSpr(psprEffect,startx,starty,font);
	GP.PutSprScreen(psprEffect, startx, starty, font+6);
}


void cltCharClient::DrawBlueExclamation()
{
	TSpr* psprEffect	= pclClient->GetGlobalSpr(GIMG_QUESTNPCEFFECT);
	if(psprEffect == NULL)return ;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 startx = DrawStartX + ImageXsize/2 - psprEffect->GetXSize() /2;
	SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - psprEffect->GetYSize() /2 - 15;
	starty -= 37;

	SI32 font = 24;
	font = font + TABS((pclClient->CurrentClock / 80))  % 6;

	GP.PutSpr(psprEffect,startx,starty,font);
	GP.PutSprScreen(psprEffect, startx, starty, font+6);
}

void cltCharClient::DrawQuestionMark( SI16 siMode )
{
	if ( (QUEST_DISPLAY_MARK_NONE >= siMode) || (QUEST_DISPLAY_MARK_MAX <= siMode) )
	{
		return;
	}

	TSpr* psprEffect = pclClient->GetGlobalSpr( GIMG_QUESTNPCEFFECT );
	if ( NULL == psprEffect )
	{
		return;
	}
	const SI16 siFrame = 10;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);

	SI32 siStartX		= DrawStartX + ImageXsize/2 - psprEffect->GetXSize() /2;
	SI32 siRealySize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 siStartY		= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - siRealySize - psprEffect->GetYSize() /2 - 52;
	SI32 siFont			= ((siMode-1) * siFrame) + (TABS((pclClient->CurrentClock / 80))  % siFrame);

	//GP.PutSpr( psprEffect, siStartX, siStartY, siFont );
	GP.PutSprScreen( psprEffect, siStartX, siStartY, siFont/*+siFrame*/ );

}



//-----------------------------------------
// ĳ���� �׸��� 
//-----------------------------------------
bool cltCharClient::Draw()
{
	cltClient *pclclient = (cltClient*)pclClient;

	cltKindInfo* ppclKI = pclKI;

	if(selectRealAnyType( ) == false)
		ppclKI = GetKindInfo(true);


	// ���ΰ��̰� ��������̸� ������� �ʴ´�. 
	if(GetID() == 1 && ((cltClient*)pclClient)->bWatchModeSwitch == true)
	{
		return false;
	}

	// ����̰� ���̵� ����̸� �ٸ� ����ڿ��� ������ �ʴ´�.
	if(GetID() != 1 && pclCI->clBI.uiGMMode == GMMODE_ATB_HIDE)
	{
		return false;
	}

	// ��ڰ� ������ �ٴϴ� ���� ���̵� ����϶��� ������ �ʴ´�.
	if (pclCM->IsValidID(siHostID))
	{
		if(siHostID != 1 && pclCM->CR[siHostID]->pclCI->clBI.uiGMMode == GMMODE_ATB_HIDE)
		{
			return false;
		}
	}

	// HealthBar Switch 
	bool bDrawHealthBarSwitch = false;

	// ������ ���������� �׷��ش�. 
	if(pclClient->pclMapManager->pclCurrentMap != pclMap)return false;

	// �׷��ֱⰡ �����Ǿ� ���� ������ �׷��ش�.
	if(DrawSwitch==FALSE)return false;

	// ���� �����ӿ����� �ι��׷����� �ʵ��� �Ѵ�. 
	if(dwDrawFrame == pclClient->GetFrame())return false;
	dwDrawFrame = pclClient->GetFrame();

	// CLONE�̶�� ��������� ������� �ʴ´�.
	if(Animation == ANITYPE_DYING && IsAtb(ATB_CLONE) && clInnerStatus.IsStatus(INNERSTATUS_CLONE) == true) return false;


	// ���� ��ġ ���� ������  �Ǵ��Ѵ�. 
	CalculateDrawStartXY();
	
	// [����] ��Ʋ�ξ� ��- ���� ���� ����
	bool bDrawSetItem = true;
	CBattleRoyalClient * pclBattleRoyalClient = ((cltClient*)pclClient)->m_pclBattleRoyal ;
	if( NULL != pclBattleRoyalClient)
	{
		if(TRUE == pclBattleRoyalClient->IsTransform(this))
		{
			bDrawSetItem = false;
		}
	}

	// [����] ��Ʋ�ξ� - �Ŀ��� ��� ĳ���� �� ���
	if( bBattleRoyalPowerupMode == true && bDrawSetItem == false)
	{
		TSpr* pspr = pclClient->GetGlobalSpr( GIMG_HUMAN_EFFECT3 );
		if( pspr )
		{
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}	
	}

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) && bDrawSetItem == true)
	{
		SI16 siCompletedSetItemIndex = clPB.clShapeEquip.siCompletedSetItemIndex;
		SI16 siCompletedSetItemIndexStep = clPB.clShapeEquip.siCompletedSetItemIndexStep;

		SI16 siCompletedSetItemIndex2 = clPB.clShapeEquip.siCompletedSetItemIndex2;
		SI16 siCompletedSetItemIndexStep2 = clPB.clShapeEquip.siCompletedSetItemIndexStep2;

		if(( m_siSetItemType == 0) && (siCompletedSetItemIndex >0))
		{
			m_siSetItemType = siCompletedSetItemIndex;
			m_siSetItemStep = siCompletedSetItemIndexStep;	//[����] ��Ʈ �������� �ܰ�. 2008-11-12
		}

		if(( m_siSetItemType2 == 0) && (siCompletedSetItemIndex2 >0))
		{

			m_siSetItemType2 = siCompletedSetItemIndex2;
			m_siSetItemStep2 = siCompletedSetItemIndexStep2;	//[����] 2��° ��Ʈ �������� �ܰ�. 2008-11-12
		}

		if( m_siSetItemType )
		{
			TSpr* pspr = pclClient->GetGlobalSpr( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemHumanEffect(this, USE_SETITEM_1) );
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}

		if( m_siSetItemType2 )
		{
			TSpr* pspr = pclClient->GetGlobalSpr( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemHumanEffect(this, USE_SETITEM_2) );
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}

		if( m_siSetItemType3 )
		{
			TSpr* pspr = pclClient->GetGlobalSpr( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemHumanEffect(this, USE_SETITEM_3) );
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}

		if( m_siSetItemType4 )
		{
			TSpr* pspr = pclClient->GetGlobalSpr( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemHumanEffect(this, USE_SETITEM_4) );
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}

		if( m_siSetItemType5 )
		{
			TSpr* pspr = pclClient->GetGlobalSpr( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemHumanEffect(this, USE_SETITEM_5) );
			if( pspr )
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}	
		}
	}


	// �׸��ڰ� �ִ� ���� �׸��ڸ� �׷��ش�. 
	DrawShadow();

	// [����] ��Ʋ�ξ� �� �� ���
	if ( bDrawSetItem == true)
	{

		// ����ȿ�� ���. 
		DrawGeneralEft();

		if ( pclBoss )
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 centery	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent;// - realysize/2;

			pclBoss->Draw(DrawStartX+ImageXsize/2, centery);
		}

		//if(pclRegeneration)
		//{
		//	SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		//	SI32 centery	= DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent;// - realysize/2;

		//	pclRegeneration->DrawBottom(DrawStartX+ImageXsize/2, centery);
		//}


		//--------------------------
		// �ź� ǥ�� (����..) 
		//--------------------------
		// ���ڸ���.
		bool bHaveRank = false; // �Ʒ� ��帶ũ������ �ź��� ������ �� ���� true�� ���� ���
		SI32 Itemunique = pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique;
		if(Itemunique == 0)
		{
			Itemunique = clPB.clShapeEquip.clHelmet.uiUnique;
		}

		// [����] ���ڴ� ���� : ���� ȿ��
		if ( CONST_JOURNALIST_HAT_ITEMUNIQUE == Itemunique )
		{
			DrawRankMark( 0 );
			bHaveRank = true;
		}

		SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique(Itemunique);

		if(Ref > 0)
		{
			/*
			// ���� ����. 
			if(pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank == 1)
			{
				DrawRankMark(0);	
			}
			*/

				// ����� ����. 
				if(pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank == 4)
				{
					DrawRankMark(42);	
					bHaveRank = true;
				}
				//  ��ȣõ�� ����. 
				if(pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank == 5)
				{
					DrawRankMark(54);
					bHaveRank = true;
				}
				//  ����ε���� ���� 
				if(pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank == 6)
				{
					DrawRankMark(57);
					bHaveRank = true;
				}
				//  ���� ����� ���� 
				if(pclClient->pclItemManager->pclItemInfo[Ref]->siNeedRank == 7)
				{
					DrawRankMark(62);
					bHaveRank = true;
				}
		}


		if(IsPC(GetCharUnique()) && (clInnerStatus.siTopSkillUnique ))
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_HUMAN_EFFECT);
			if(pspr)
			{
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

				//GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
				GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
			}

			DrawMakeMasterMark(clInnerStatus.siTopSkillUnique);
		}
		//[�߰� : Ȳ���� 2008. 1. 14 => �ְ� ����� ������ ���θ�ũ�� �׷��ش�..] 2008-5-6 �ź�ǥ�ð� �������� ������ ����.
		else if ( IsPC(GetCharUnique()) && pclCM->IsValidID(siID) && (pclCM->CR[siID]->uiBestGuild == 1) && (false==bHaveRank) )
		{
			DrawBestGuildMark();
		}
		//[�߰� : Ȳ���� 2007. 11. 27 ����̸� ������ �����Ų GM ��忡 ��ũ �׸���.]
		else if (IsPC(GetCharUnique()) && pclCM->IsValidID(siID) && pclCM->CR[siID]->pclCI->clBI.uiGMMode == GMMODE_ATB_BUFF)
		{
			DrawGMMark();	
			DrawKingEffect();
		}
		// �ְ� ���� ǥ�ó� GM��ũ�� �׸���. (���� ��ġ�̹Ƿ�)
		else if (IsPC(GetCharUnique()) && pclCM->IsValidID(siID) && pclCM->CR[siID]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
		{
			DrawGMMark();
		}
		else if ( pclClient->IsWhereServiceArea(ConstServiceArea_Korea | ConstServiceArea_NHNChina) && (IsPC(GetCharUnique())) && (pclCM->IsValidID(siID)) && (!bHaveRank) && (pclCM->CR[siID]->pclCI->clBI.bPCRoom) )
		{
			DrawPCRoomMark();
		}

		if ( pclClient->IsCountrySwitch(Switch_BokBulBok) )
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// [����] : ���Һ� �̺�Ʈ �� : pvpī��Ʈ�� �� Ÿ�� ǥ�� ( 1 : ��ų, 2 : Ű, 3 : ������, �Ϲݸ� )
			cltClient* pClient = (cltClient*)pclClient;
			if ( true == pClient->m_pClient_BBBMgr->m_bGMShowMonsterType )
			{
				if ( IsNPC(GetCharUnique()) )
				{
					if ( pclCM->IsValidID(siID) )
					{
						SI08 siMydentity = pclCM->CR[siID]->clIdentity.siIdentity;
						if ( siMydentity == IDENTITY_BOKBULBOK_ITEMMONSTER )
						{
							DrawBBBSpecialIndicator( 2 );	// pvpī��Ʈ �̹����� 4�� �ε��� �׸��� ���� 3�̴�
						}
						else if ( siMydentity == IDENTITY_BOKBULBOK_KEYMONSTER )
						{
							DrawBBBSpecialIndicator( 3 );	// pvpī��Ʈ �̹����� 4�� �ε��� �׸��� ���� 2�̴�
						}
						else if ( siMydentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
						{
							DrawBBBSpecialIndicator( 4 );	// pvpī��Ʈ �̹����� 4�� �ε��� �׸��� ���� 1�̴�
						}
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		// ������ ����
		if ( IsPC(GetCharUnique()) )
		{
			SI32 mantleunique = pclCI->clCharItem.clItem[PERSONITEM_MANTLE].siUnique ;
			if ( mantleunique == 0 )
			{
				mantleunique = clPB.clShapeEquip.clMantle.uiUnique ;
			}

			if ( mantleunique == ITEMUNIQUE(18510) )
			{
				TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_HUMAN_EFFECT);
				if(pspr)
				{
					// by LEEKH 2007.12.24 - TRANSFORM
					SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
					SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
					SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+28;

					//GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
					GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);				
				}
			}
		}

		//----------------------
		// �� ���� 
		//----------------------
		SI32 itemunique = pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique;
		if(itemunique == 0)
		{
			itemunique = clPB.clShapeEquip.clArmour.uiUnique;
		}
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);

		if(ref > 0 && pclClient->pclItemManager->pclItemInfo[ref]->siNeedRank == 2)
		{
			DrawKingEffect();
		}

		if ( pclHeartEffect )
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent ;
			pclHeartEffect->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
		}

		if( pclCushionEffect ) 
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent ;
			pclCushionEffect->Draw( DrawStartX + ImageXsize/2, realyimagestarty ); 
		}

		//----------------------
		//��Ȳ���� ��� ��Ȳ�� Effect���
		//----------------------
		switch(clIdentity.siIdentity)
		{
		case IDENTITY_VILLAGEGOD:			
			{
				//MakeRankMarkEncBuffer();
				DrawRankMark(43);	
				DrawGodEffect();
			}
			break;
		case IDENTITY_CASTLE:				break;
		case IDENTITY_VILLAGEGOD_SUMMON:	break;
		case IDENTITY_PERSON_SUMMON:
			{
				//������ ��ȯ������ �����ش�.
				//if ( !pclKI->bSummonMall )
				DrawRankMark(44);
			}
			break;
		case IDENTITY_VILLAGEHUNT:			/*DrawRankMark(45);*/break; 
		}
	}
	//KHY - 1220 - ���Žý���.
	if(ppclKI->IsAtb(ATB_HERO))
	{
		DrawHero();
	}
	else
	{
		DrawNormal();
	}

	// [����] ��Ʋ�ξ� ��- ���� ���� ����
	pclBattleRoyalClient = ((cltClient*)pclClient)->m_pclBattleRoyal ;
	if( NULL != pclBattleRoyalClient)
	{
		if(TRUE == pclBattleRoyalClient->IsTransform(this))
		{
			return true;
		}
	}

	if((clTransFormInfo.bTransFormMode == true) && (IsPC(GetCharUnique())) &&(selectRealAnyType( ) == false))
	{
		if(clTransFormInfo.bTransForm100Effect ==true)
		{
			DrawTransformSyc100Effect();
		}
	}

	//----------------------
	//��Ȳ���� ��� ��Ȳ�� Effect���
	//----------------------
	switch(clIdentity.siIdentity)
	{
	case IDENTITY_VILLAGEGOD:			break;
	case IDENTITY_CASTLE:				break;
	case IDENTITY_VILLAGEGOD_SUMMON:	break;
	case IDENTITY_PERSON_SUMMON:		/*DrawSummonEffect();*/	break; 
	case IDENTITY_VILLAGEHUNT:			break;
	}

	//-------------------------------------------
	// ���� �� ����Ʈ
	//-------------------------------------------
	bool bGachaSummon = false;

	if( GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SUPERBEARTANG")) )
	{
		bGachaSummon = true;
	}

	if( bGachaSummon )
	{
		DrawGachaSummonEffect();
	}

	if( pclFourLeafEffect )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize ;
		pclFourLeafEffect->Draw( DrawStartX + ImageXsize/2, realyimagestarty );  
	}

	if(pclCushionCatEffect)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent ;
		pclCushionCatEffect->Draw( DrawStartX + ImageXsize/2, realyimagestarty ); 
	}

	//---------------------------
	// ���� ���� ȿ���� �ִٸ� ����Ѵ�. 
	//---------------------------
	if(bNoFirstAttackSwitch)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_NOFIRSTATTACK);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 20;

			GP.PutSprLight1(pspr, startx,	starty,	 TABS((pclClient->CurrentClock / 200)) % 12 );
		}
	}
	//---------------------------
	// ICE ���� ȿ���� �����Ǿ� �ִٸ� 
	//---------------------------
	if(bNoIceAttackSwitch)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_NOICEATTACK);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize - 20;

			GP.PutSpr(pspr, startx,	starty,	 TABS((pclClient->CurrentClock / 150)) % 20);
		}

	}

	// [����] ���� �귿 �۵����̸� �ֻ������ ����. => 2008-6-10
	if(bBuffRouletteSwitch)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_DICE);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize - 20;

			GP.PutSpr(pspr, startx,	starty,	 TABS((pclClient->CurrentClock / 80)) % 12 );
		}
	}

	//-------------------------------------	
	// [����] ������.
	//-------------------------------------
	if( bElixirSwitch )
	{
		TSpr* pspr = pclClient->GetGlobalSpr(GIMG_ELIXIR);

		if(pspr)
		{
			SI32 startx = DrawStartX + (ImageXsize / 2) - (pspr->GetXSize() / 2);

			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent * ImageYsize / 100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 70;   

			bool bReverse = false;
			switch( siDirection )
			{
			case SOUTH:								
			case SOUTH|WEST:						
			case SOUTH|EAST:											
			case EAST :	 		
				{
					bReverse = false;	
				}
				break;
			case WEST: 
			case NORTH|WEST:	
			case NORTH:			
			case NORTH|EAST:	
				{
					bReverse = true;	
				}
				break;
			}		  

			GP.PutSprScreen( pspr, startx,	starty,	 TABS((pclClient->CurrentClock / 80)) % 10, bReverse ); 
		}
	}

	//	PVP���׿� ���� �Ѵ�.
	if (siEnemUnique > 0 ) 
	{
		bool bPVPMAP	=	false ;
		SI32 siMyPersonID = pclClient->pclCM->CR[1]->pclCI->GetPersonID()	;
		cltCharCommon* pclChar = pclClient->pclCM->GetChar(1)	;	// Ŭ��ϱ� ���̵� 1 
		SI32 siMapIndex = pclChar->GetMapIndex()	;
		cltMapCommon* pclMap = pclClient->pclMapManager->GetMapPointer( siMapIndex )	;

		if(pclMap != NULL)
		{
			SI32 siColl = pclMap->GetCollMap( pclChar->GetX() , pclChar->GetY()	)	;

			switch( siMapIndex ) {
	case  MAPINDEX_MAINFIELD :
		{
			if ( siColl & BLOCK_EVENT4 ) //PVP���� ���̰� ����� ������ ���� �ϸ� 
			{
				bPVPMAP = true	;
			}
		}
		break;
	case  MAPINDEX_PVPMAP :
		{
			if ( siColl & BLOCK_EVENT4 ) //PVP���� ���̰� ����� ������ ���� �ϸ� 
			{
				bPVPMAP = true	;
			}
		}
		break;
			}
		}
		if ( true == bPVPMAP ) 
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_LEAGUE);

			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty = DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 30;
				// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
				SI32 siHorseUnique = 0;
				if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
				{
					starty -= 20;
				}
				
				GP.PutSpr(pspr, startx,	starty,	0 )	;
			}
		}
	}
	// [���� ] pvp ������ ī��Ʈ �ٿ� 
	if(bPvpCountDown)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_COUNTDOWN);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;

			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				starty -= 50;
			}
			// �ð� ���� ��
			SI32 sitime = (pclClient->CurrentClock) - siPVPWaitTime;

			if ( sitime > 1000 )
			{
				if ( 1000 <= sitime && 2000 > sitime ) 
				{
					GP.PutSpr(pspr, startx,	starty,	0 );
				}
				if ( 2000 <= sitime && 3000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	1 );
				}
				if ( 3000 <= sitime&& 4000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	2 );
				}
				if ( 4000 <= sitime&& 5000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	3 );
				}
				if ( 5000 <= sitime&& 6000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	4 );
				}
				if ( 6000 <= sitime && 7000 > sitime ) 
				{
					GP.PutSpr(pspr, startx,	starty,	5 );
				}
			}
		}
	}
	if(siPVPWin)// �¸� ǥ�� 
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_WLD);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				starty -= 50;
			}

			// �ð� ���� ��
			SI32 sitime = (pclClient->CurrentClock) - siPVPEndTime ;
			if ( 0 <= sitime && 5000 > sitime ) 
			{
				GP.PutSpr(pspr, startx,	starty,	0 );//�¸�
			}
			else if(5000 < sitime)
			{
				siPVPWin	=	false	;
				siPVPLose	=	false	;
				siPVPDraw	=	false	;
				siPVPEndTime	=	0	;
			}
		}
	}
	if(siPVPLose)//  �й� ǥ�� 
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_WLD);
		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				starty -= 50;
			}

			// �ð� ���� ��
			SI32 sitime = (pclClient->CurrentClock) - siPVPEndTime ;
			if ( 0 <= sitime && 5000 > sitime ) 
			{
				GP.PutSpr(pspr, startx,	starty,	1 );//�¸�
			}
			else if(5000 < sitime)
			{
				siPVPWin	=	false	;
				siPVPLose	=	false	;
				siPVPDraw	=	false	;
				siPVPEndTime	=	0	;
			}
		}
	}
	if(siPVPDraw)// ��� ǥ��
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_WLD);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				starty -= 50;
			}

			// �ð� ���� ��
			SI32 sitime = (pclClient->CurrentClock) - siPVPEndTime ;
			if ( 0 <= sitime && 5000 > sitime ) 
			{
				GP.PutSpr(pspr, startx,	starty,	2 );//�¸�
			}
			else if( 5000 < sitime )
			{
				siPVPWin	=	false	;
				siPVPLose	=	false	;
				siPVPDraw	=	false	;
				siPVPEndTime	=	0	;
			}
		}
	}
	if ( pclValentineWar )
	{
		SI16 siCouple = pclValentineWar->GetCouple();
		if(siCouple > 0)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_EMOTICON);
			switch( siCouple ) {				
	case VALENTINEWAR_COUPLE:
		{
			if(pspr)
			{
				SI32 imagenum = 56	;
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize-30;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF ) 
					|| pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK ) ) //���������� ����Ŭ�ι����� �� �ø���.
				{
					starty = starty - 20 ;
				}
				else if ( bPvpCountDown == TRUE ) // pvp ī��Ʈ �ҋ��� �� �ø���.
				{
					starty = starty - 50 ;

				}
				// �ð� ���� �ؼ�
				SI32 sitemptimecount = (pclClient->CurrentClock/1000)	;
				SI32 timecount =	sitemptimecount%10;
				switch(timecount )
				{
				case 1:
					{imagenum	=	106	;}break;
				case 2:
					{imagenum	=	107	;}break;
				case 3:
					{imagenum	=	112	;}break;
				case 4:
					{imagenum	=	113	;}break;
				case 5:
					{imagenum	=	57	;}break;
				case 6:
					{imagenum	=	58	;}break;
				case 7:
					{imagenum	=	245	;}break;
				case 8:
					{ imagenum	=	246	; }	break;
				case 9:
					{ imagenum	=	106	; }break;								
				default:
					{ imagenum	=	57	; }break;
				}
				GP.PutSpr(pspr, startx,	starty,imagenum )		;
			}
		}break;
	case VALENTINEWAR_SOLO:
		{					
			if(pspr)
			{
				SI32 imagenum =  21	;
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 30;
				// �����̳� ���� ���� �ϸ� ���� �ø���.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF ) 
					|| pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK ) ) 
				{
					starty = starty - 20 ;
				}
				else if ( bPvpCountDown == TRUE ) 
				{
					starty = starty - 50 ;

				}
				// �ð� ���� �ؼ�
				SI32 sitemptimecount = (pclClient->CurrentClock/1000)	;
				SI32 timecount =	sitemptimecount%10;
				switch(timecount ) 
				{
				case 1:
					{imagenum	=	22	;}break;
				case 2:
					{imagenum	=	28	;}break;
				case 3:
					{imagenum	=	29	;}break;
				case 4:
					{imagenum	=	35	;}break;
				case 5:
					{imagenum	=	36	;}break;
				case 6:
					{imagenum	=	49	;}break;
				case 7:
					{imagenum	=	50	;}break;
				case 8:
					{ imagenum	=	84	; }	break;
				case 9:
					{ imagenum	=	85	; }break;								
				default:
					{ imagenum	=	21	; }break;
				}
				GP.PutSpr(pspr, startx,	starty,imagenum )		;
			}
		}break;
			}
		}
	}
	if(bRacoonDodgeEventCountDown)//Switch_10MonthEvent_RacoonDodge
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_COUNTDOWN);

		if(pspr)
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;

			// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
			SI32 siHorseUnique = 0;
			if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
			{
				starty -= 50;
			}
			// �ð� ���� ��
			SI32 sitime = (pclClient->CurrentClock) - siRacoonDodgeWaitTime;

			if ( sitime > 1000 )
			{
				if ( 1000 <= sitime && 2000 > sitime ) 
				{
					GP.PutSpr(pspr, startx,	starty,	0 );
				}
				if ( 2000 <= sitime && 3000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	1 );
				}
				if ( 3000 <= sitime&& 4000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	2 );
				}
				if ( 4000 <= sitime&& 5000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	3 );
				}
				if ( 5000 <= sitime&& 6000 > sitime) 
				{
					GP.PutSpr(pspr, startx,	starty,	4 );
				}
				if ( 6000 <= sitime && 7000 > sitime ) 
				{
					GP.PutSpr(pspr, startx,	starty,	5 );
				}
			}
		}
	}

	if ( pclClient->IsCountrySwitch(Switch_BokBulBok) )
	{
		//////////////////////////////////////////////////////////////////////////
		// [����] ���Һ� �̺�Ʈ�� ���� �̹��� ��� (5�� ī��Ʈ)
		if(bBBBEvent_5SecCountDownFlag)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_COUNTDOWN);

			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;

				// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
				SI32 siHorseUnique = 0;
				if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
				{
					starty -= 50;
				}
				// �ð� ���� ��
				SI32 sitime = (pclClient->CurrentClock) - siBBBEvent_5SecCountDown;
				cltClient* pClient = (cltClient*)pclClient;
				SI32 siStartDelay = (pClient->m_pClient_BBBMgr->m_siStageStartDelay) / 1000;
				SI32 siStartIndex = 5 - siStartDelay;				// 5�� �϶� 5����, 4���϶� 4����, 3���϶� 3���� ���.. ���� �ð��� ���� �޶����� �ε��� ����ġ
				SI32 siCurrentImageIndex = sitime / 1000;			// �и��� ������ ����ð��� 1000���� ���� ��. �� 0���� ����

				if (0 <= siCurrentImageIndex + siStartIndex && 5 >= siCurrentImageIndex + siStartIndex )		// �̹��� �ε����� 5�� ���� �ʴ´�.
				{
					GP.PutSpr(pspr, startx,	starty,	siCurrentImageIndex + siStartIndex );
				}

			}
		}

		// [����] ���Һ� �̺�Ʈ�� ���� �̹��� ��� (5�ʰ� Lose �޼���)
		if(bBBBEvent_StageFailFlag)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_WLD);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
				// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
				SI32 siHorseUnique = 0;
				if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
				{
					starty -= 50;
				}

				// �ð� ���� ��
				SI32 sitime = (pclClient->CurrentClock) - siBBBEvent_StageFailCountDown ;

				cltClient* pClient = (cltClient*)pclClient;
				SI32 siDelay = pClient->m_pClient_BBBMgr->m_siStageLoseDelay;

				if ( siDelay > sitime )			// 5
				{
					GP.PutSpr(pspr, startx,	starty,	1 );
				}
			}
		}

		// [����] ���Һ� �̺�Ʈ�� ���� �̹��� ��� (5�ʰ� Win �޼���)
		if(bBBBEvent_StageClearFlag)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PVP_WLD);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
				// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
				SI32 siHorseUnique = 0;
				if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
				{
					starty -= 50;
				}

				// �ð� ���� ��
				SI32 sitime = (pclClient->CurrentClock) - siBBBEvent_StageClearCountDown;

				cltClient* pClient = (cltClient*)pclClient;
				SI32 siDelay = pClient->m_pClient_BBBMgr->m_siStageWinDelay;

				if ( siDelay > sitime )			// 5
				{
					GP.PutSpr(pspr, startx,	starty,	0 );
				}
			}
		}

		// [����] ���Һ� �̺�Ʈ�� ���� �̹��� ��� (���� 10�ܰ� �Ϸ� �� �ߴ� win/lose ) 
		if(bBBBEvent_TotalStageClearFlag)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_BBB_WL);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;

				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 50;
				// ���� Ÿ�� ������ ���� ������ ����Ѵ�. 
				SI32 siHorseUnique = 0;
				if( (siHorseUnique = pclCI->clHorseInfo.GetCurrentRideHorseUnique()) != 0)
				{
					starty -= 10;
				}

				// �ð� ���� ��
				SI32 sitime = pclClient->CurrentClock - siBBBEvent_TotalStageClearCountDown;
				sitime = sitime % 800;

				SI32 siCurrentIndex = (sitime / 200) + siBBBEvent_TotalStageClearResultImageIndex;		// 1�ʿ� �ѹ��� �ִϸ��̼� Ǯ�� ���
				GP.PutSpr(pspr, startx,	starty,	siCurrentIndex );
			}
		}
		//////////////////////////////////////////////////////////////////////////
	}


	if(pclKI->clKIDrawInfo.siHeadNameFont >= 0)
	{
		DrawRankMark(pclKI->clKIDrawInfo.siHeadNameFont);
	}

	if ( pclCM->CR[1]->pclKI->IsAtb(ATB_HERO) )
	{
		cltSystemNPC clNPCInfo;
		if ( pclClient->pclSystemNPCManager->FindSystemNPCInfoFromNPCKind( GetKind(), &clNPCInfo ) )
		{
			if ( QUESTDISPLAY_MODE_NONE != clNPCInfo.m_siImageDisplayMode )
			{
				if ( false == pclCM->CR[1]->pclCI->clQuestInfo.IsAllClear(pclClient->pclQuestManager, clNPCInfo.m_siQuestType) )
				{
					SI16 siDisplayMark = GetQuestDisplayMark( &clNPCInfo );

					DrawQuestionMark( siDisplayMark );

					cltCharPos clCharPos(GetMapIndex(),GetX(),GetY() );

					((CNMiniMapDlg*)pclclient->m_pDialog[NMINIMAP_DLG])->SetMinimapNPC(GetKind(),&clCharPos);
				}
			}
		}
	}

	//----------------------
	// ��Ƽ ���Ḧ ǥ���Ѵ�. 
	//----------------------
	if( pclclient->m_pDialog[ NPARTY_DLG ] )
	{
		if ( ((CNPartyDlg*)pclclient->m_pDialog[ NPARTY_DLG ])->IsPartyUser( GetCharUnique() ) == true )
		{
			TSpr* pspr	= pclClient->GetGlobalSpr( GIMG_PARTYEMOTICON );

			if(pspr)
			{	
				SI32 charheight = 30; //30 �� ĳ������ ������ ���� ����
				if(GetCurrentOrder() == ORDER_SITDOWN) charheight -= 18;

				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
				// by LEEKH 2007.12.24 - TRANSFORM
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2  -charheight; 
				pclPartyEmoticon->Draw( pspr, startx, starty );
			}
		}
	}


	// ġ��ȿ���� ����Ѵ�. 
	DWORD healinterval = TABS(pclClient->CurrentClock - dwHealClock);
	SI32 healframe		= 12;
	SI32 healdelay		= 100; //�и�������
	if((SI32)healinterval < healframe * healdelay)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_HEAL);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2;

			GP.PutSprAdd(pspr, startx,		starty,	 healinterval / healdelay);

		}
	}

	// ��ȣ���� Ư����� ����Ʈ�� ǥ���Ѵ�
	if ( pclClient->IsCountrySwitch(Switch_SoulGuard) )
	{
		DWORD	dwSoulGuardSF_Interval	= TABS(pclclient->CurrentClock - dwSoulGuardSF_Clock);
		TSpr*	psprSoulGuardSF			= NULL;

		SI32	siDrawDelay				= 100;

		// ���ο� ī��Ʈ �߰��� �̰��� ������ ��
		if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_TINKY") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL_Y );
		}
		// PCK : ��ȣ���� - �Ҿ����� �߰� (09.07.03)
		else if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_FIRESPIRIT") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL_R );
		}
		// ��Ų
		else if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_PUMPKIN") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL_P );
		}
		// ��������
		else if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_ICESPIRIT") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL_B );
		}
		else if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_TK_EVENT") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL_Y );
		}
		/* �䷱������ �߰��� �ּ���
		else if ( pclClient->GetUniqueFromHash("KIND_SOULGUARD_TINKY") == siSoulGuardSF_Kind )
		{
			psprSoulGuardSF = pclClient->GetGlobalSpr( GIMG_HEAL );
		}
		*/

			if ( (psprSoulGuardSF)																	// �̹����� �ִٸ�
				&& (0 < psprSoulGuardSF->GetImageNum())												// �̹����� �������� 0���� ũ�ٸ�
				&& ((SI32)dwSoulGuardSF_Interval < (psprSoulGuardSF->GetImageNum()*siDrawDelay))	// ����Ʈ�� �ѷ��� �� �ִٸ�
				)
			{
				SI32 startx		= DrawStartX + ImageXsize/2 - psprSoulGuardSF->GetXSize() /2;
				SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
				SI32 starty		= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - psprSoulGuardSF->GetYSize() /2;

				GP.PutSprAdd( psprSoulGuardSF, startx, starty, (dwSoulGuardSF_Interval/siDrawDelay) );
			}
	}


	//���� ���� �̶��
	if(GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_CASTLE"))   && pclClient->bVillageWarSwitch 
		&&	 pclCM->IsValidID(GetID())
		&&   pclClient->pclVillageManager->IsVillageAtWar( pclCM->CR[GetID()]->pclCI->clBI.siHomeVillage ) )
	{
		SI32 siCastleLife =  pclCM->CR[GetID()]->clPB.GetMaxLife(); // pclCM->CR[GetID()]->pclCI->clIP.siVit*4;

		if( pclCM->CR[GetID()]->GetLife() <  siCastleLife * 0.8)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE4);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 ;
				SI32 starty	= DrawStartY - 40;//+ 30;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = TABS((pclClient->CurrentClock / 100)) % pspr->GetImageNum() ;	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
		if( pclCM->CR[GetID()]->GetLife() <  siCastleLife * 0.6)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE3);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 + 100 ;
				SI32 starty	= DrawStartY - 200;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = TABS((pclClient->CurrentClock / 100)) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
		if( pclCM->CR[GetID()]->GetLife() <  siCastleLife * 0.4)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE2);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 + 80;
				SI32 starty	= DrawStartY -250;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = TABS((pclClient->CurrentClock / 100)) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
		if( pclCM->CR[GetID()]->GetLife() <  siCastleLife * 0.2)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE1);
			if(pspr)
			{
				SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 + 210;
				SI32 starty	= DrawStartY - 260;//+ 30;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = TABS((pclClient->CurrentClock / 100)) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
	}

	// ���� �ߵ��Ǿ��� ���
	if(clInnerStatus.IsStatus(INNERSTATUS_POISON))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_POISON);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2 - 30;
			//GP.PutSprScreen(pspr, startx,		starty, pclClient->GetFrame()%pspr->GetImageNum());
			if(pspr->GetImageNum() > 0)	GP.PutSprScreen(pspr, startx, starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());

		}
	}
	
	//[����] ��Ʈ ������ ���� �ߵ��Ǿ��� ���
	if( clInnerStatus.IsStatus( INNERSTATUS_POISON_SETITEM_EFFECT ) )
	{
		TSpr* pspr = pclClient->GetGlobalSpr(GIMG_SETITEM_POISON); 
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = (DrawStartX + ImageXsize/2 - pspr->GetXSize() / 2) - 5;   
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2 - 50;
			//GP.PutSprScreen(pspr, startx,		starty, pclClient->GetFrame()%pspr->GetImageNum());
			if(pspr->GetImageNum() > 0)	GP.PutSprScreen(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 80))%pspr->GetImageNum());  
			if(pspr->GetImageNum() > 0)	GP.PutSprScreen(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 40))%pspr->GetImageNum());     

		}
	}

	

	// ������ ����� ��� 
	if(clInnerStatus.IsStatus(INNERSTATUS_ICE))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_ICEFROZEN);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - /*realysize/2 -*/ pspr->GetYSize()/2;
			GP.PutSprAdd(pspr, startx,		starty, 0);
		}
	}

	// ������ ���� ������ �� ���
	if(clInnerStatus.IsStatus(INNERSTATUS_FROZEN))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGICFROZEN);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - /*realysize/2 -*/ pspr->GetYSize()/2-50;
			//GP.PutSprScreen(pspr, startx,		starty, pclClient->GetFrame()%pspr->GetImageNum());
			GP.PutSprScreen(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());

		}
	}
	// ������ �ɷ��� ��� // �̰�쿡�� �ϴ� �׸��� ���̽��� ���ش� ������.
	if(clInnerStatus.IsStatus(INNERSTATUS_STUN))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_STUN);
		if(pspr) 
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - /*realysize/2 -*/ pspr->GetYSize()/2;
			GP.PutSprScreen(pspr, startx,	starty - 90, max(0, TABS(pclClient->CurrentClock / 150))%pspr->GetImageNum());   
		}
	}

	if( cltCharCurseEffect::CURSE_NONE != m_clCharCurseEffect.GetCurse( GetID() ) )
	{
		TSpr* pspr	= NULL;
		switch( m_clCharCurseEffect.GetCurse( GetID() ) )
		{
			case cltCharCurseEffect::CURSE_ATTACK:	pspr	= pclClient->GetGlobalSpr(GIMG_CURSE_ATTACK);	break;
			case cltCharCurseEffect::CURSE_DEFENSE:	pspr	= pclClient->GetGlobalSpr(GIMG_CURSE_DEFENSE);	break;
			case cltCharCurseEffect::CURSE_DODGE:	pspr	= pclClient->GetGlobalSpr(GIMG_CURSE_DODGE);	break;
			case cltCharCurseEffect::CURSE_HIT:		pspr	= pclClient->GetGlobalSpr(GIMG_CURSE_HIT);		break;
		}

		if(pspr) 
		{
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - realysize/2 - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize();  
			GP.PutSprScreen(pspr, startx,	starty - 20, max(0, TABS(pclClient->CurrentClock / 100))%pspr->GetImageNum()); 
		}	
	}
	
	// ���ݷ� ���� ������ �ɷ��� ��� 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEATTACK))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_CURSEATTACK);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize()/2;
			//GP.PutSprScreen(pspr, startx,		starty, pclClient->GetFrame()%pspr->GetImageNum());
			GP.PutSprScreen(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());

		}
	}

	// ũ��Ƽ�� ���� ������ �ɷ��� ��� 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSECRITICAL))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_CURSECRITICAL); 
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize()/2;
			GP.PutSprAdd(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());
		}
	}

	// ���� ���� ������ �ɷ��� ��� 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEDEFENSE))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_CURSEDEFENSE);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize()/3;
			GP.PutSprAdd(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());
		}
	}

	// �̵��ӵ����� ������ �ɷ��� ��� 
	if(clInnerStatus.IsStatus(INNERSTATUS_CURSEMOVESPEED))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_CURSEMOVESPEED);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
			SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize ;
			GP.PutSprLight(pspr, startx,		starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());
		}
	}

	// �� �ٴ� ������ �ɷ��� ���
	if(clInnerStatus.IsStatus(INNERSTATUS_MAGICFIRE))
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGICFIRE);
		if(pspr)
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2 - 50 ;
			GP.PutSprScreen(pspr, startx,	starty, max(0, TABS(pclClient->CurrentClock / 50))%pspr->GetImageNum());
		}
	}


	// Drain Life�ΰ�� 
	if(bDrainSwitch)
	{
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_MAGIC_DRAIN);
		if(pspr)
		{
			SI32 font = 0;
			SI32 siFrameNum = pspr->GetImageNum()/5;
			bool reverseswitch = false;
			switch(siDirection)
			{
			case SOUTH:
				reverseswitch=false;
				font=siFrameNum*1+siDrainFrame;
				break;
			case SOUTH|WEST:
				reverseswitch=false;
				font=siFrameNum*2+siDrainFrame;
				break;
			case WEST:
				reverseswitch=false;
				font=siFrameNum*3+siDrainFrame;
				break;
			case NORTH|WEST:
				reverseswitch=false;
				font=siFrameNum*4+siDrainFrame;
				break;
			case NORTH:
				reverseswitch=true;
				font=siFrameNum*3+siDrainFrame;
				break;
			case NORTH|EAST:
				reverseswitch=true;
				font=siFrameNum*2+siDrainFrame;
				break;
			case EAST:
				reverseswitch=true;
				font=siFrameNum*1+siDrainFrame;
				break;
			case EAST|SOUTH:
				reverseswitch=false;
				font=siFrameNum*0+siDrainFrame;
				break;
			default:
				reverseswitch = false;
				font=0;
				break;
			}

			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
			SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2 - 30;
			GP.PutSprAdd(pspr, startx,		starty, font , reverseswitch);

			siDrainFrame++;
			if(siDrainFrame >= siFrameNum) {siDrainFrame = 0; bDrainSwitch =false;}
		}
	}

	if(pclRegeneration)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 centery	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - 65;

		pclRegeneration->DrawCenter(DrawStartX+ImageXsize/2, centery );
	}


	if(pclCharCut)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 centery	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2;

		pclCharCut->Draw(DrawStartX+ImageXsize/2, centery);
	}

	if ( pclLevelUp )
	{
		// ���� ĳ��
		if( IsPC( GetCharUnique() ) )
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;  
			pclLevelUp->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
		}
		// ��ȯ����
		else
		{
			// [����] ��ȯ�� ������ �̹��� ��ǥ �ٸ��� ����.
			pclLevelUp->DrawNpc( DrawStartX + ImageXsize / 2, DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent );  
		}
	}

	if ( pclMVPEffect )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclMVPEffect->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
	}

	if( pclEnchantEff)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclEnchantEff->Draw( DrawStartX + ImageXsize/2, realyimagestarty, Animation  );
	}
	if( pclQuestEff)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclQuestEff->Draw( DrawStartX + ImageXsize/2, realyimagestarty);
	}
	if(pclExpCounter)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclExpCounter->Draw( DrawStartX + ImageXsize/2, realyimagestarty );

	}
	if(pclHealCounter)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize - 10;
		pclHealCounter->Draw( DrawStartX + ImageXsize/2, realyimagestarty );

	}
	if ( pclSkillLevelUp )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclSkillLevelUp->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
	}
	if ( pclEmoticonEff )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		pclEmoticonEff->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
	}

	if ( m_pclValentineEmoticonEff )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
		m_pclValentineEmoticonEff->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
	}

	if ( pclCriticalEffect )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 centery	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2;
		pclCriticalEffect->Draw( DrawStartX+ImageXsize/2, centery );
	}


	if ( pclJim )
	{
		// ��ȯ���� ��ǥ�ø� ���� �ʵ��� �Ѵ�.
		if(GetLife() > 0 && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON) 
		{
			// by LEEKH 2007.12.24 - TRANSFORM
			SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
			SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize;
			pclJim->Draw( DrawStartX + ImageXsize/2, realyimagestarty );
		}

		// ����ȯ���� �������� ���� ����ϸ� HealthBar�� �׷��ش�.
		else if( pclJim->IsJimStatus() && 
			clIdentity.siIdentity == IDENTITY_PERSON_SUMMON &&
			pclCM->CR[1]->siChildCharUnique == GetCharUnique() ) 
		{
			bDrawHealthBarSwitch = true;
		}
	}

	// ���� �������� �ʴ� ĳ������ ��� ü�� �������� �����ش�. 
	if(pclKI->IsAtb(ATB_NOJJIM))
	{
		bDrawHealthBarSwitch = true;
	}


	// ������ ǥ�õǴ� ĳ������ ��쿡�� �� ũ�⵵ ǥ���Ѵ�. 
	if(GetCharUnique() && pclClient->pclDevTool[DEV_TOOL_CHARINFO]->GetCharUnique() == GetCharUnique())
	{
		GP.Box(DrawStartX, DrawStartY, 
			DrawStartX+ImageXsize-1, DrawStartY+ImageYsize-1, 
			10);

		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 realxsize = ppclKI->clKIDrawInfo.siXsizePercent*ImageXsize/100;
		SI32 realysize = ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

		// by LEEKH 2007.12.24 - TRANSFORM
		GP.Box(DrawStartX + (ImageXsize-realxsize)/2 ,			
			DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize,
			DrawStartX + (ImageXsize-realxsize)/2 + realxsize,
			DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent, 
			20);
	}


	//-----------------------------
	// ���콺 �Ʒ� ĳ�����̸�, 
	// Ȥ�� �� �Ǿ� �ִ� ĳ�����̸�, 
	//-----------------------------
	if(GetLife() > 0 && (IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique())))
	{
		cltClient* pclclient = (cltClient*)pclClient;
		if(clJim.siJimHostCharUnique && (clJim.siJimHostCharUnique == pclCM->CR[1]->GetCharUnique()))
		{
			bDrawHealthBarSwitch = true;
		}
	}

	//-----------------------------
	// ������ ��,
	// ���� PC �̰� ���ΰ����� �������� ������ ���� Health Bar�� �׷��ش�.
	//-----------------------------
	/*if(pclClient->bVillageWarSwitch == true)
	{
		if(IsPC(GetCharUnique()) && IsEnemy(1))
		{
			bDrawHealthBarSwitch = true;
		}
	}*/


		//-----------------------------
		// �Ҽ��� �ִ� Ư�� ĳ���͵��� �׻� �������ٸ� �׷��ش�.
		//-----------------------------
		switch(clIdentity.siIdentity)
	{
		case IDENTITY_CASTLE:	
		case IDENTITY_VILLAGEGOD:
		case IDENTITY_VILLAGEGOD_SUMMON:	bDrawHealthBarSwitch = true;					break;
			// ��ȯ�� �������� �Ⱥ����ش�.
			//// ���ϋ� �����ذ� �Ⱥ����ش�.
			//case IDENTITY_PERSON_SUMMON:	if( IsEnemy(1) == false )	bDrawHealthBarSwitch = true;	break;
		case IDENTITY_VILLAGEHUNT:			bDrawHealthBarSwitch = true;					break;
		case IDENTITY_MOFUMOFUEVENT:		bDrawHealthBarSwitch = true;					break;
	}

	if ( GetID() == 1 )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 startx = DrawStartX + ImageXsize/2+3;
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent+145;
		pclClient->pclQuestManager->DrawDirectionArrow( startx , starty );
	}


	// ü�¹ٸ� ���̴� ������ �Ǿ� �ְ� ü���� ��ȿ�ϸ� ü�¹ٸ� �� �����ִ� �Ӽ��� ���ٸ� 
	if(bDrawHealthBarSwitch == true && GetLife() > 0 && pclKI->IsAtb(ATB_NOHEALTHBAR) == FALSE )
		DrawHealthBar();

	//----------------------
	// ���� ���� ����Ʈ
	//----------------------
	{
		SI32 realysize			= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 realyimagestarty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize ;
		m_clMagicBufMgr.Draw( DrawStartX + ImageXsize/2, realyimagestarty );  
	}

	/*cyj
	// pc�� ������ ��� ǥ�� 
	if( pclCI->clBI.IsPCRoom() ) {
		TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_PCROOM_MARK);

		if( pspr ) {

			SI32 startx = DrawStartX + 130;
			SI32 starty	= DrawStartY + 118;

			if( pclCI->clCharRank.GetRankType() == 0 ) {
				starty += 12;
			}
			GP.PutSpr(pspr, startx, starty, 0);
		}
	}
	*/


		// TEST TSET TEST TSST
		//DrawHealthBar();

		/*
		#ifdef _DEBUG
		// ĳ���� ���տ��� ��µǴ� �̹��� ���� ������...
		if ( pclClient->GetFrame() % 200 == 0 )
		{
		int ImageNum = pclCharDraw->GetLoadedImageNum();
		TCHAR Buffer[256]=TEXT("");
		sprintf( Buffer, TEXT("Character ImageNum = %d"), ImageNum );
		pclClient->pclMessage->SetMsg( Buffer );
		}
		#endif
		*/

		//------------------------------------
		// �� ǥ�� 
		//------------------------------------
		/*	if(clJim.siJimHostCharUnique)
		{
		UI08 color = 0;
		if(pclClient->IsUser(clJim.siJimHostCharUnique))
		{
		color = 100;
		}
		else
		{
		color = 50;
		}

		SI32 realxsize = pclKI->clKIDrawInfo.siXsizePercent*ImageXsize/100;
		SI32 realysize = pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;

		GP.Box(DrawStartX + (ImageXsize-realxsize)/2 ,			
		DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - realysize,
		DrawStartX + (ImageXsize-realxsize)/2 + realxsize,
		DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent, 
		color);

		}
		*/


		return true;
}

//Game Direction�� CDD Direction���� �����Ѵ�.
SI32 cltCharClient::TransDir(SI32 gamedir)
{
	switch(gamedir)
	{
	case SOUTH:			return CCD_SOUTH;
	case SOUTH|WEST:	return CCD_SOUTH_WEST;
	case WEST:			return CCD_WEST;
	case NORTH|WEST:	return CCD_NORTH_WEST;
	case NORTH:			return CCD_NORTH;
	case NORTH|EAST:	return CCD_NORTH_EAST;
	case EAST:			return CCD_EAST;
	case SOUTH|EAST:	return CCD_SOUTH_EAST;
	default:	return CCD_SOUTH_EAST; 
	}
}

bool cltCharClient::DrawHero()
{
	SI32 weapon = 0;
	SI32 helmet = 0;
	SI32 armour = 0;
	SI32 mantle = 0;
	bool horse	= false;

	UI32 rareInfo = 0;
	SI32 enchantType = 0;
	SI32 enchantPower = 0;

	SI32 PremiumPartsUnique_Slot1	=	0 ;
	SI32 PremiumPartsUnique_Slot2	=	0 ;
	SI32 PremiumPartsUnique_Slot3	=	0 ;

	if(pclCI->clCharItem.clItem[ActiveWeapon].clItemCommon.clCommonInfo.uiRareInfo)
	{
		rareInfo = pclCI->clCharItem.clItem[ActiveWeapon].clItemCommon.clCommonInfo.uiRareInfo;
	}
	else 
	{
		rareInfo = clPB.clShapeEquip.clWeapon.uiRare;
	}

	if( pclClient->pclItemManager->IsExpiredDate(&pclCI->clCharItem.clItem[ActiveWeapon]) == true &&
		pclCI->clCharItem.clItem[ActiveWeapon].Element.siType )
	{
		enchantType = pclCI->clCharItem.clItem[ActiveWeapon].Element.siType;
		enchantPower = pclCI->clCharItem.clItem[ActiveWeapon].Element.siPower;
	}
	else
	{
		enchantType = clPB.clShapeEquip.clWeapon.uiEnchantType;
		enchantPower = clPB.clShapeEquip.clWeapon.uiEnchantPower;
	}

	//[�߰� : Ȳ���� 2007. 12. 12. �ų� ���� ���� ������ ���̰�. �ϴܺ��� : �ٸ��������...]
	SYSTEMTIME sTime;
	GetLocalTime( &sTime );

	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		SI32	Unique[] = {97, 172, 372, 272, 468, 568};
		SI32	Cnt		 = sizeof(Unique)/ sizeof(SI32);
		for(SI32 i = 0; i < Cnt; ++i)
		{
			if(Unique[i] == pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique)		
			{
				if(RARELEVEL_6 != pclCI->clCharItem.clItem[ ActiveWeapon ].clItemCommon.clCommonInfo.uiRareInfo)
				{				
					rareInfo = NEWYEAR_EFFECT;
				}
			}
		}
	}

	//if(true == NewYearEventDay())
	//{		
	//	SI32	Unique[] = {97, 172, 372, 272, 468, 568};
	//	SI32	Cnt		 = sizeof(Unique)/ sizeof(SI32);
	//	for(SI32 i = 0; i < Cnt; ++i)
	//	{
	//		if(Unique[i] == pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique)		
	//		{
	//			if(RARELEVEL_6 != pclCI->clCharItem.clItem[ ActiveWeapon ].clItemCommon.clCommonInfo.uiRareInfo)
	//			{				
	//				rareInfo = NEWYEAR_EFFECT;
	//			}
	//		}
	//	}
	//}


	// ���� ����Ʈ ����.
	weapon = CheckJewelEffect( rareInfo , enchantType , enchantPower );

	rareInfo = 0;
	enchantType = 0;
	enchantPower = 0;	

	//-----------------------------------------------------------------------
	// ���� �������� �ʰ� ���ڸ� ã�´� - ���� ȿ���� �̰��� ��������.
	SI32 AvailableHat = ActiveHat;
	SI32 AvailableClothes = ActiveClothes;

	if(pclCI->clCharItem.clItem[ ActiveHat ].siUnique== 0)	
	{
		if(AvailableHat==PERSONITEM_HAT)
			AvailableHat=PERSONITEM_HELMET;
		else
			AvailableHat=PERSONITEM_HAT;
	}

	if(pclCI->clCharItem.clItem[ ActiveClothes ].siUnique ==0)
	{
		if(AvailableClothes==PERSONITEM_DRESS)		
			AvailableClothes= PERSONITEM_ARMOUR;
		else
			AvailableClothes=PERSONITEM_DRESS;

	}

	SI32 NowActiveClothesUnique = pclCI->clCharItem.clItem[AvailableClothes].siUnique;		// ���� �������� �Ǹ�
	SI32 NowActiveHatUnique = pclCI->clCharItem.clItem[AvailableHat].siUnique;			// ���� �������� ����
	//-----------------------------------------------------------------------


	if ( pclCI->clCharItem.clItem[ AvailableHat ].siUnique > 0 && pclCI->clCharItem.clItem[AvailableHat].clItemCommon.clCommonInfo.uiRareInfo )
	{		
		rareInfo = pclCI->clCharItem.clItem[AvailableHat].clItemCommon.clCommonInfo.uiRareInfo;
	}
	else
	{
		rareInfo = clPB.clShapeEquip.clHelmet.uiRare;
	}

	if ( pclCI->clCharItem.clItem[ AvailableHat ].siUnique > 0 && pclCI->clCharItem.clItem[AvailableHat].Element.siType )
	{		
		enchantType = pclCI->clCharItem.clItem[AvailableHat].Element.siType;
		enchantPower = pclCI->clCharItem.clItem[AvailableHat].Element.siPower;
	}
	else
	{
		enchantType = clPB.clShapeEquip.clHelmet.uiEnchantType;
		enchantPower = clPB.clShapeEquip.clHelmet.uiEnchantPower;		
	}

	//[�߰� : Ȳ���� 2007. 12. 12. �ų� ���� ���� ������ ���̰�. �ϴܺ��� : �ٸ��������...]

	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		//[�߰� : Ȳ���� 2007. 12. 12. �ų� ���� ���� ������ ���̰�.]
		if(pclClient->pclItemManager->IsItemInfoAtb( NowActiveHatUnique, ITEMINFOATB_ITEMMALL ))
		{
			rareInfo = NEWYEAR_EFFECT;
		}
	}

	// PCK : ��ȥ ���� ����Ʈ �׸��� (09.05.07)
	// ��ȥ �Ǻ��� ��ȥ ���ڸ� �ΰ� �� �������� ��쿡�� ����Ʈ�� �׷��ش�.
	if ( (NowActiveHatUnique == ITEMUNIQUE(23117) && NowActiveClothesUnique == ITEMUNIQUE(23696))  // ��ȥ ���� �Ӹ� + ��ȥ ���Ŀ� �νõ�  �̰ų�
		||  (NowActiveHatUnique == ITEMUNIQUE(23118) && NowActiveClothesUnique == ITEMUNIQUE(23698)))     // ��ȥ�� ����� +  ������ �巹�� �϶���.
	{
		// ��ȥ���� ��쿡�� ����Ʈ�� �׷��ش�.
		if(IsMarried())
		{
			rareInfo = MARRIED_FULLDRESS_EFFECT;
		}
	}

	bool SmallEffect = false;
	if(pclClient->siServiceArea == ConstServiceArea_Japan)
		SmallEffect = true;

	// ���� ����Ʈ ����
	helmet = CheckJewelEffect( rareInfo , enchantType , enchantPower, SmallEffect );
	//----------------------------------------------------------------------------------------------

	rareInfo = 0;
	enchantType = 0;
	enchantPower = 0;	

	if ( pclCI->clCharItem.clItem[ AvailableClothes ].siUnique > 0 && pclCI->clCharItem.clItem[ AvailableClothes ].clItemCommon.clCommonInfo.uiRareInfo )
	{
		rareInfo = pclCI->clCharItem.clItem[ AvailableClothes ].clItemCommon.clCommonInfo.uiRareInfo;
	}	
	else
	{
		rareInfo = clPB.clShapeEquip.clArmour.uiRare;
	}

	if ( pclCI->clCharItem.clItem[ AvailableClothes ].siUnique > 0 && pclCI->clCharItem.clItem[ AvailableClothes ].Element.siType )
	{
		enchantType = pclCI->clCharItem.clItem[ AvailableClothes ].Element.siType;
		enchantPower = pclCI->clCharItem.clItem[ AvailableClothes ].Element.siPower;
	}	
	else
	{
		enchantType = clPB.clShapeEquip.clArmour.uiEnchantType;
		enchantPower = clPB.clShapeEquip.clArmour.uiEnchantPower;
	}

	//[�߰� : Ȳ���� 2007. 12. 12. �ų� ���� ���� ������ ���̰�. �ϴܺ��� : �ٸ��������...]
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
	{
		if(pclClient->pclItemManager->IsItemInfoAtb( pclCI->clCharItem.clItem[ AvailableClothes ].siUnique, ITEMINFOATB_ITEMMALL ))
		{
			rareInfo = NEWYEAR_EFFECT;
		}
	}

	// PCK : ��ȥ ���� ����Ʈ �׸��� (09.05.07)
	// ��ȥ �Ǻ��� ��ȥ ���ڸ� �ΰ� �� �������� ��쿡�� ����Ʈ�� �׷��ش�.
	if ( (NowActiveHatUnique == ITEMUNIQUE(23117) && NowActiveClothesUnique == ITEMUNIQUE(23696))  // ��ȥ ���� �Ӹ� + ��ȥ ���Ŀ� �νõ�  �̰ų�
		||  (NowActiveHatUnique == ITEMUNIQUE(23118) && NowActiveClothesUnique == ITEMUNIQUE(23698)))     // ��ȥ�� ����� +  ������ �巹�� �϶���.
	{
		// ��ȥ���� ��쿡�� ����Ʈ�� �׷��ش�.
		if(IsMarried())
		{
			rareInfo = MARRIED_FULLDRESS_EFFECT;
		}
	}

	// �Ǻ� ����Ʈ ����.
	armour = CheckJewelEffect( rareInfo , enchantType , enchantPower, SmallEffect );

	rareInfo = 0;
	enchantType = 0;
	enchantPower = 0;	


	if( pclCI->clCharItem.clItem[PERSONITEM_MANTLE].clItemCommon.clCommonInfo.uiRareInfo )
	{
		rareInfo = pclCI->clCharItem.clItem[PERSONITEM_MANTLE].clItemCommon.clCommonInfo.uiRareInfo;
	}
	else
	{
		rareInfo = clPB.clShapeEquip.clMantle.uiRare;
	}

	if( pclCI->clCharItem.clItem[PERSONITEM_MANTLE].Element.siType )
	{
		enchantType = pclCI->clCharItem.clItem[PERSONITEM_MANTLE].Element.siType;
		enchantPower = pclCI->clCharItem.clItem[PERSONITEM_MANTLE].Element.siPower;
	}
	else
	{
		enchantType = clPB.clShapeEquip.clMantle.uiEnchantType;
		enchantPower = clPB.clShapeEquip.clMantle.uiEnchantPower;
	}    	

	mantle = CheckJewelEffect( rareInfo , enchantType , enchantPower );

	rareInfo = 0;
	enchantType = 0;
	enchantPower = 0;	


	//KHY - 1001 - ��µ��� 5���� ���� ����.	
	cltHorse *pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
	if(pclHorse != NULL)
	{
		if ( (pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE)  )
		{
			if( pclHorse->siStatusTicketNum > 0 && pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclHorse) > 0 &&
				((cltClient*)pclClient)->clClientDate.GetDateVary() < pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclHorse) ) // �ɷ� ������̸鼭 Ÿ�� �ִ���
			{
				horse = true ;
			}
		}

	}

	//pclCI->clHorseInfo.siCurrentHorseIndex >= 0 ) // �ɷ� ������̸鼭 Ÿ�� �ִ���

	// �������� ���ݵ�����. 
	SI32 attacklayerskill		= 0;
	bool battacklayerskillmode	= 0;
	SI08 siAttackScrollNum		= 0;	// ���� ���� ������
	SI32 attackgimg				= 0;
	SI32 effectx				= 0;
	SI32 effecty				= 0;
	SI32 effectfont				= 0;
	bool effectreverse			= false;
	SI16 siHorseUnique			= 0;

	// �ؿ� ��ġ �����͸� �߰��ϸ� ������̸��� ������ ������ ��ġ�� ������ �� �ִ�
	SI32 siMotorCycleStartY = 0;
	SI32 siCurrentOrder = GetCurrentOrder();
	if( pclCI->clHorseInfo.GetCurrentHorseRIDEHORSE() && siCurrentOrder != ORDER_SITDOWN 
		&& siCurrentOrder != ORDER_FARM && siCurrentOrder != ORDER_MINE && siCurrentOrder != ORDER_FISH && siCurrentOrder != ORDER_DIE) 
	{
		cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
		if(pclHorse && pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
		{ 
			siMotorCycleStartY = 13;
		}
		// ������� ���� �ִ� ��ó�� ������ �Ѵ�.
		else if(pclHorse && pclHorse->siHorseUnique == HORSEUNIQUE_SASURI)
		{ 
			siMotorCycleStartY = -50;
		}

	}
	// ������̴� ������ ª�Ƽ� ������ ������ �Ѵ�.
	DrawStartY += siMotorCycleStartY;
	if( pclCI->clHorseInfo.GetCurrentHorseRIDEHORSE() ) 
	{
		cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
		if( pclHorse )
		{
			PremiumPartsUnique_Slot1 = pclHorse->siPremiumUnique_Slot1 ;
			PremiumPartsUnique_Slot2 = pclHorse->siPremiumUnique_Slot2 ;
			PremiumPartsUnique_Slot3 = pclHorse->siPremiumUnique_Slot3 ;
			siHorseUnique	=	pclHorse->siHorseUnique;
		}
	}

	pclCharDraw->DrawCharacter(	HeroAnimation, 
								TransDir(siDirection), 
								clAniInfo.GetAniStep(),
								DrawStartX, 
								DrawStartY,
								weapon, 
								helmet, 
								armour, 
								mantle,
								horse,
								battacklayerskillmode, 
								siAttackScrollNum,
								&effectreverse,
								&effectx,
								&effecty, 
								&effectfont,
								&attackgimg,
								PremiumPartsUnique_Slot1,
								PremiumPartsUnique_Slot2,
								PremiumPartsUnique_Slot3, 
								siHorseUnique );

	if( HeroAnimation == SPCU || HeroAnimation == SPCR)
	{

		SI16 LevelUpActionNum = 11;

		if(clAniInfo.GetAniStep() >= LevelUpActionNum)
		{
			bLevelUpDrawSwitch = false;
		}
	}

	// �ɾ� ���� ���� ��Ʈȿ���� �׸��� �ʴ´�.
	//if(GetCurrentOrder() != ORDER_SITDOWN)
	{
		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if( m_siSetItemType > 0)
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_1);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						} 
					}
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_1);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{ 
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pspr->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}    
							GP.PutSprScreen(pspr, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2); 
						}
					} 
				}
			}
			if( m_siSetItemType2 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_2);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						} 
					}
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_2);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{ 
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pspr->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}    
							GP.PutSprScreen(pspr, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2); 
						}
					} 
				}
			}

			if( m_siSetItemType3 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_3);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						} 
					}
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_3);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{ 
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pspr->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}    
							GP.PutSprScreen(pspr, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2); 
						}
					} 
				}
			}

			if( m_siSetItemType4 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_4);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						} 
					}
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_4);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{ 
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pspr->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}    
							GP.PutSprScreen(pspr, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2); 
						}
					} 
				}
			}

			if( m_siSetItemType5 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_5);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						} 
					}
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_5);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{ 
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pspr->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}    
							GP.PutSprScreen(pspr, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2); 
						}
					} 
				}
			}
		}
		else
		{
			switch ( m_siSetItemType )
			{
			case VAMPIRE_SETITEM:
				//case BLACKKNIGHT_SETITEM_STEP:
				{
					TSpr* pspr = pclClient->GetGlobalSpr( GIMG_SETITEMEFFECT0 );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						}
					}
					TSpr *pSpr2 = pclClient->GetGlobalSpr( GIMG_SETITEMEFFECT2 );
					if ( pSpr2 )
					{
						if(pSpr2->GetImageNum() > 0)
						{
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pSpr2->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}
							GP.PutSprScreen(pSpr2, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2);
						}
					}
				}
				break;
			case HALLOWEEN1_SETITEM:
			case HALLOWEEN2_SETITEM:
			case HALLOWEEN3_SETITEM:
			case HALLOWEEN4_SETITEM:
				{
					TSpr* pspr = pclClient->GetGlobalSpr( GIMG_SETITEME6 );
					if ( pspr )
					{
						if(pspr->GetImageNum() > 0)
						{
							m_siSetItemImgAnimationCounter1 = m_siSetItemImgAnimationCounter1%pspr->GetImageNum();
							GP.PutSprScreen(pspr,  DrawStartX + 105 , DrawStartY + 150, m_siSetItemImgAnimationCounter1++ );
						}
					}
					TSpr *pSpr2 = pclClient->GetGlobalSpr( GIMG_SETITEMEFFECT6 );
					if ( pSpr2 )
					{
						if(pSpr2->GetImageNum() > 0)
						{
							if( pclClient->GetFrame() % 2 == 0)
							{
								m_siSetItemImgAnimationCounter2 = m_siSetItemImgAnimationCounter2%pSpr2->GetImageNum();
								m_siSetItemImgAnimationCounter2++;
							}
							GP.PutSprScreen(pSpr2, DrawStartX + 100, DrawStartY + 80, m_siSetItemImgAnimationCounter2);
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}

	// [����] ��ȥ ����Ʈ
	BOOL bDrawWeddingEffect = FALSE;
	if ( 1 == GetCharID() )
	{
		if ( (IsMarried()) && (0 < pclMarriage->GetLoveLevel())  && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP==pclMarriage->GetConnectMode()) )	
		{
			bDrawWeddingEffect = TRUE;
		}
	} 
	else
	{
		if ( (pclMarriage) && (0 < pclMarriage->GetLoveLevel()) )
		{
			bDrawWeddingEffect = TRUE;
		}
	}

	if ( TRUE == bDrawWeddingEffect )
	{
		SI32	siLoveLevelEffect	= pclClient->m_pclMarriageMgr->GetEffectTypeFromLoveLevel( pclMarriage->GetLoveLevel() );

		TSpr*	psprEffect			= NULL;

		switch ( siLoveLevelEffect )
		{
		case MARRIAGE_EFFECT_TYPE_SMALL:	
			{	
				psprEffect = pclClient->GetGlobalSpr( GIMG_WEDDING_EFT_S );	

				if ( (NULL != psprEffect) && (0 < psprEffect->GetImageNum()) )
				{
					m_siWeddingImgAnimationCounter = m_siWeddingImgAnimationCounter % psprEffect->GetImageNum();
					GP.PutSprScreen(psprEffect, (DrawStartX + 100), (DrawStartY + 110), m_siWeddingImgAnimationCounter++ );
				}
			}	
			break;

		case MARRIAGE_EFFECT_TYPE_MEDIUM:	
			{	
				psprEffect = pclClient->GetGlobalSpr( GIMG_WEDDING_EFT_M );	

				if ( (NULL != psprEffect) && (0 < psprEffect->GetImageNum()) )
				{
					m_siWeddingImgAnimationCounter = m_siWeddingImgAnimationCounter % psprEffect->GetImageNum();
					GP.PutSprScreen(psprEffect, (DrawStartX + 85), (DrawStartY + 85), m_siWeddingImgAnimationCounter++ );
				}
			}	
			break;

		case MARRIAGE_EFFECT_TYPE_LARGE:	
			{	
				psprEffect = pclClient->GetGlobalSpr( GIMG_WEDDING_EFT_L );	

				if ( (NULL != psprEffect) && (0 < psprEffect->GetImageNum()) )
				{
					m_siWeddingImgAnimationCounter = m_siWeddingImgAnimationCounter % psprEffect->GetImageNum();
					GP.PutSprScreen(psprEffect, (DrawStartX + 50), (DrawStartY + 50), m_siWeddingImgAnimationCounter++ );
				}
			}	
			break;
		}

	}

	if ( battacklayerskillmode )
	{
		cltMapClient* pclmap = (cltMapClient*)pclMap;
		TSpr* pspr	= pclClient->GetGlobalSpr(attackgimg);
		if ( pspr )
		{
			cltEffectMapInfo pcleffect;
			pcleffect.gimg = attackgimg ;
			pcleffect.font = effectfont ;
			pcleffect.x = effectx ;
			pcleffect.y = effecty ;
			pcleffect.reverse = effectreverse ;
			pclmap->PushEffect(&pcleffect);
		}
	}

	// MC �������� ����. 
	SI32 itemunique = pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique;
	if(itemunique == 0)
	{
		itemunique = clPB.clShapeEquip.clHelmet.uiUnique;
	}

	return true;
}

SI32 cltCharClient::CheckJewelEffect( UI32 rare , SI32 enchanttype , SI32 enchantpower, bool Flag ) 
{
	SI32 jewelEffect = 0;

	if( rare == RARELEVEL_1 )
	{
		jewelEffect |= JEWELEFFECT_RARE1;
	}
	else if ( rare == RARELEVEL_2)
	{
		jewelEffect |= JEWELEFFECT_RARE2;
	}
	else if ( rare == NEWYEAR_EFFECT)
	{
		//[�߰� : Ȳ���� 2008. 1. 9. �ų� ���� ���� ������ ���̰�. ]
		SYSTEMTIME sTime;
		GetLocalTime( &sTime );

		if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &sTime) )
		{
			jewelEffect |= JEWELEFFECT_RARE2;

			//[�߰� : Ȳ���� 2007. 12. 21 => ���� ������ �����̴°� �Ϻ��� ȣǰ���� �����̰� ����.]
			if(pclClient->siServiceArea == ConstServiceArea_Japan)
			{
				if(true == Flag)
				{
					jewelEffect = 0;
					jewelEffect |= JEWELEFFECT_RARE1;
				}
			}
		}

		//if(true == NewYearEventDay())
		//{
		//	jewelEffect |= JEWELEFFECT_RARE2;

		//	//[�߰� : Ȳ���� 2007. 12. 21 => ���� ������ �����̴°� �Ϻ��� ȣǰ���� �����̰� ����.]
		//	if(pclClient->siServiceArea == ConstServiceArea_Japan)
		//	{
		//		if(true == Flag)
		//		{
		//			jewelEffect = 0;
		//			jewelEffect |= JEWELEFFECT_RARE1;
		//		}
		//	}
		//}
	}
	else if(rare == MARRIED_FULLDRESS_EFFECT)
	{
		jewelEffect |= MARRIED_FULLDRESS;
	}

	if( enchanttype == ENCHANT_TYPE_FIRE_A)
	{
		if		(enchantpower >= JEWELEFFECT_GRADE3)	{	jewelEffect |= JEWELEFFECT_FIRE3;	}
		else if (enchantpower >= JEWELEFFECT_GRADE2)	{	jewelEffect |= JEWELEFFECT_FIRE2;	}
		else if	(enchantpower >= JEWELEFFECT_GRADE1)	{	jewelEffect |= JEWELEFFECT_FIRE1;	}
	}
	else if( enchanttype == ENCHANT_TYPE_WATER_A)
	{
		if		(enchantpower >= JEWELEFFECT_GRADE3)	{	jewelEffect |= JEWELEFFECT_WATER3;	}
		else if (enchantpower >= JEWELEFFECT_GRADE2)	{	jewelEffect |= JEWELEFFECT_WATER2;	}
		else if	(enchantpower >= JEWELEFFECT_GRADE1)	{	jewelEffect |= JEWELEFFECT_WATER1;	}
	}
	else if( enchanttype == ENCHANT_TYPE_GROUND_A)
	{
		if		(enchantpower >= JEWELEFFECT_GRADE3)	{	jewelEffect |= JEWELEFFECT_GROUND3;	}
		else if (enchantpower >= JEWELEFFECT_GRADE2)	{	jewelEffect |= JEWELEFFECT_GROUND2;	}
		else if	(enchantpower >= JEWELEFFECT_GRADE1)	{	jewelEffect |= JEWELEFFECT_GROUND1;	}
	}
	else if( enchanttype == ENCHANT_TYPE_WIND_A)
	{
		if		(enchantpower >= JEWELEFFECT_GRADE3)	{	jewelEffect |= JEWELEFFECT_WIND3;	}
		else if (enchantpower >= JEWELEFFECT_GRADE2)	{	jewelEffect |= JEWELEFFECT_WIND2;	}
		else if	(enchantpower >= JEWELEFFECT_GRADE1)	{	jewelEffect |= JEWELEFFECT_WIND1;	}
	}

	return jewelEffect ;
}

bool cltCharClient::DrawNormal()
{
	SI32 sidrawysize;


	// ���� �̹����� �Ǵ��Ѵ�. 
	DecideFont();

	if(pclCI->clBI.GetKind() == KIND_JOKER && (pImgSpr == NULL || pImgSpr->header.iXSize <= 0 || pImgSpr->header.iYSize <= 0))
	{
		// ��ڴ� �������.
		if(pclCM->CR[1]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
		{
			// ������ �� �𸣴� ��� 3�� ��ٷȴٰ� ������ ������ �ݽô�.
			if( GAMEMODE_CLIENT ==  pclClient->GameMode )
			{
				MsgBox("Error","Can't Read Important file!!");
				dwQuitTimer = pclClient->CurrentClock + 1000;
			}
			return false;
		}
	}

	sidrawysize=ImageYsize;
	SI16 drawtransmode = TransMode;
	// by LEEKH 2007.12.24 - TRANSFORM
	if ( GetKindInfo(true)->clCharAniManager.pclCharAni[Animation]->siTransMode != 0 )
		drawtransmode = GetKindInfo(true)->clCharAniManager.pclCharAni[Animation]->siTransMode ;

	SI08 alphavalue = AlphaValue ;
	if ( drawtransmode == TRANSPARENT_MODE_ALPHA )
	{
		if ( alphavalue < 0 || alphavalue > MAX_ALPHA_LEVEL - 1 )
			alphavalue = MAX_ALPHA_LEVEL - 1;
	}

	// ��� ������ �� ���̸� ǥ�����ش�.
	unsigned char *darktable;

	if(bNewSelectedSwitch == true)
	{
		if(NewSelectedDelay % 2==0)
		{

			darktable = (UI08*)1;

			// �Ϲ� ��尡 �ƴ� Ư������ �����Ѵٸ� ������� �Ϲ����� ������� ����ش�.
			if(drawtransmode != TRANSPARENT_MODE_NORMAL) drawtransmode =  TRANSPARENT_MODE_NORMAL;

		}
		else
		{
			darktable = 0;
		}
	}
	else if( bMouseOverSwitch == true )
	{        
		darktable = (UI08*)1;

		// �Ϲ� ��尡 �ƴ� Ư������ �����Ѵٸ� ������� �Ϲ����� ������� ����ش�.
		if(drawtransmode != TRANSPARENT_MODE_NORMAL) drawtransmode =  TRANSPARENT_MODE_NORMAL;
	}
	else
	{
		darktable = NULL;
	}

	// �������� ������ ���ķ� �׸���.
	if(pclCI->clBI.GetKind() == KIND_JOKER)
	{
		drawtransmode =  TRANSPARENT_MODE_ALPHA;
		alphavalue    = 14;
	}

	if(pImgSpr)
	{
		switch( drawtransmode )
		{
		case TRANSPARENT_MODE_OLDTRANS:
			GP.PutSprLight1(pImgSpr, DrawStartX, DrawStartY, Font, bReverseSwitch);				break;
		case TRANSPARENT_MODE_HALFTRANS:
			GP.PutSprLight(pImgSpr, DrawStartX, DrawStartY, Font, bReverseSwitch);				break;
		case TRANSPARENT_MODE_SCREEN:
			GP.PutSprScreen(pImgSpr, DrawStartX, DrawStartY, Font, bReverseSwitch);				break;
		case TRANSPARENT_MODE_MULTIPLY:
			GP.PutSprMultiply(pImgSpr, DrawStartX, DrawStartY, Font, bReverseSwitch);			break;
		case TRANSPARENT_MODE_ADD:
			GP.PutSprAdd(pImgSpr, DrawStartX, DrawStartY, Font, bReverseSwitch);				break;
		case TRANSPARENT_MODE_ALPHA:
			GP.PutSprAlpha(pImgSpr, DrawStartX, DrawStartY,alphavalue, Font, bReverseSwitch);	break;
		default:
			{
				//&Image[ clHeader.clImgInfo[font].siStartPos ];
				if( darktable ) {
					GP.PutSprEF(pImgSpr,  DrawStartX, DrawStartY,  0, Font, bReverseSwitch );	break;
				} else {
					GP.PutSpr(pImgSpr, DrawStartX, DrawStartY, Font,  bReverseSwitch );			break;
				}
			}

		}
	}	

	// [����] ��Ʋ�ξ� ��- ���� ���� ����
	CBattleRoyalClient * pclBattleRoyalClient = ((cltClient*)pclClient)->m_pclBattleRoyal ;
	if( NULL != pclBattleRoyalClient)
	{
		if(TRUE == pclBattleRoyalClient->IsTransform(this))
		{
			return true;
		}
	}

	// Ư�� ȿ���� �ִ� ���� Ư�� ȿ���� ����Ѵ�.
	if(siEffectFont >=0)
	{
		if(pImgSpr)	GP.PutSprLight1(pImgSpr, DrawStartX, DrawStartY, siEffectFont, bReverseSwitch);
	}
	if ( siShadowAni > 0 )
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 ref = GetKindInfo(true)->clCharAniManager.FindRefFromAnitype(siShadowAni);
		if ( ref >= 0 )
		{
			TSpr* pSpr = NULL ;
			SI32 anifont = 0 ;
			bool reverse = false ;
			SI32 effect = 0 ;
			// by LEEKH 2007.12.24 - TRANSFORM
			alphavalue = GetKindInfo(true)->clCharAniManager.pclCharAni[siShadowAni]->siAlphaValue ;
			if ( alphavalue < 0 || alphavalue > MAX_ALPHA_LEVEL - 1 )
				alphavalue = MAX_ALPHA_LEVEL - 1;

			// by LEEKH 2007.12.24 - TRANSFORM
			GetKindInfo(true)->clCharAniManager.DecideDrawImg(siShadowAni, siDirection, clAniInfo,
				TABS(pclClient->CurrentClock), &pSpr, &anifont, &reverse, &effect );

			// by LEEKH 2007.12.24 - TRANSFORM
			if ( siShadowFont >= 0 && GetKindInfo(true)->clCharAniManager.GetDirSwitch(siShadowAni) )
				anifont = siShadowFont ;

			SI32 mode = TransMode;

			// by LEEKH 2007.12.24 - TRANSFORM
			if ( GetKindInfo(true)->clCharAniManager.pclCharAni[siShadowAni]->siTransMode != 0 )
				mode = GetKindInfo(true)->clCharAniManager.pclCharAni[siShadowAni]->siTransMode ;

			SI32 xindent = 0 ;
			SI32 yindent = 0 ;
			// by LEEKH 2007.12.24 - TRANSFORM
			GetKindInfo(true)->clCharAniManager.GetShadowIndentXY(siShadowAni,&xindent,&yindent);

			if(pSpr)
			{
				SI32 x = pSpr->GetXSize();
				SI32 y = pSpr->GetYSize();

				SI32 drawx = DrawStartX + ImageXsize/2 - x/2 - xindent ;
				SI32 drawy = DrawStartY + ImageYsize/2 - y/2 - yindent ;

				switch( mode )
				{
				case TRANSPARENT_MODE_OLDTRANS:
					GP.PutSprLight1(pSpr, drawx, drawy, anifont, reverse);		break;
				case TRANSPARENT_MODE_HALFTRANS:
					GP.PutSprLight(pSpr, drawx, drawy, anifont, reverse);		break;
				case TRANSPARENT_MODE_SCREEN:
					GP.PutSprScreen(pSpr, drawx, drawy, anifont, reverse);		break;
				case TRANSPARENT_MODE_MULTIPLY:
					GP.PutSprMultiply(pSpr,drawx, drawy, anifont, reverse);	break;
				case TRANSPARENT_MODE_ADD:
					GP.PutSprAdd(pSpr, drawx, drawy, anifont, reverse);			break;
				case TRANSPARENT_MODE_ALPHA:
					GP.PutSprAlpha(pSpr, drawx, drawy, alphavalue,  anifont, reverse);			break;
				default:
					{
						GP.PutSpr(pImgSpr, drawx, drawy, anifont,  reverse );	break;

					}
					break;

				}

				if(effect >=0)
				{
					GP.PutSprLight1(pSpr, drawx, drawy, effect, reverse);
				}
			}
		}
	}
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		cltKindInfo* ppclKI = pclKI;

		if(selectRealAnyType( ) == false)
			ppclKI = GetKindInfo(true);

		if( ppclKI )
		{
			if( m_siSetItemType )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_1);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty += 25;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_1);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty -= 30;  

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}
			}
			if( m_siSetItemType2 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_2);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty += 25;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_2);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty -= 30;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}
			}

			if( m_siSetItemType3 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_3);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty += 25;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_3);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty -= 30;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}
			}

			if( m_siSetItemType4 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_4);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty += 25;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_4);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty -= 30;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}
			}

			if( m_siSetItemType5 )
			{
				SI32 Index = -1;
				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemE(this, USE_SETITEM_5);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty += 25;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}

				Index = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemEffet(this, USE_SETITEM_5);
				if( 0 < Index )
				{
					TSpr* pspr = pclClient->GetGlobalSpr( Index );
					if( pspr )
					{
						// by LEEKH 2007.12.24 - TRANSFORM
						SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2;
						SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
						SI32 starty	= DrawStartY + ImageYsize -ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize() /2+18;

						// [��ȣ] ���Ǹ���ȯ�߿��� ��Ʈ������ ����Ʈ�� ��ġ�� ����Ǿ�� �Ѵ�.
						if(pclClient->pclCM->CR[GetID()]->clTransFormInfo.bTransFormMode == true || pclClient->pclCM->CR[GetID()]->siBufTransformKind > 0)
							starty -= 30;

						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+pclClient->GetFrame()) / 3 % 30);
						GP.PutSprScreen(pspr, startx , starty+15, (GetID()+max(0, TABS(pclClient->CurrentClock / 50))) / 3 % 30);
					}	
				}
			}
		}
	}
	return true;
}



//---------------------------------------------------------------
// ������ ĳ����. 
//---------------------------------------------------------------
// �Ķ��Ÿ�� �־��� �����ۿ� ���� Person�� ������ �ٲ��ְ� �Ѵ�.
bool cltCharClient::ChangeArmCode(SI32 itempos, SI32 unique)
{
	if ( itempos < 0 || itempos >= MAX_SHAPE_ITEM )
	{
		return false;
	}

	TCHAR* armcode = NULL; 
	bool updateswitch = false;
	cltItemManagerCommon* pclItemManager = pclClient->pclItemManager;

	//���ڸ� �ٲٴ� ���� �ٷ� �ܰ��� �����Ѵ�. 
	bool bhelmetswitch = false;
	if(itempos == PERSONITEM_HAT || itempos == PERSONITEM_HELMET)
	{

		// ������ ���, 
		if(unique && ActiveHat == PERSONITEM_HAT && itempos == PERSONITEM_HAT)
		{
			bhelmetswitch  = true;
		}
		// Ż���� ���, 
		else if(unique && ActiveHat == PERSONITEM_HELMET && itempos == PERSONITEM_HELMET)
		{
			bhelmetswitch  = true;
		}

		else
		{
			bhelmetswitch  = true;

			SI32 HatFlag1 = PERSONITEM_HAT;
			SI32 HatFlag2 = PERSONITEM_HELMET;

			if( ActiveHat == PERSONITEM_HELMET)
			{
				HatFlag1 =  PERSONITEM_HELMET;
				HatFlag2 =  PERSONITEM_HAT;

			}
			// ������ ������ ������ �̹����� �����Ѵ�. 
			if(pclCI->clCharItem.clItem[HatFlag1].siUnique)
			{
				unique = pclCI->clCharItem.clItem[HatFlag1].siUnique;
			}
			else
			{
				unique = pclCI->clCharItem.clItem[HatFlag2].siUnique;
			}
		}

	}

	if(bhelmetswitch)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(unique);
		if(ref > 0 )
		{
			armcode = pclItemManager->pclItemInfo[ref]->GetArmCode();
		}
		else armcode = NULL;

		if(armcode)
		{
			updateswitch	= true;
			StringCchCopy(szHelmetCode,  32, armcode );
		}
		else
		{
			updateswitch	= true;
			StringCchCopy(szHelmetCode,  32, TEXT("KOR01"));
		}
	}

	//�Ǻ��� �ٲٴ� ���� �ٷ� �ܰ��� �����Ѵ�. 

	bool barmourswitch = false;
	if(itempos == PERSONITEM_DRESS || itempos == PERSONITEM_ARMOUR )
	{
		// ������ ���, 
		if(unique && ActiveClothes==PERSONITEM_DRESS && itempos == PERSONITEM_DRESS)
		{
			barmourswitch  = true;
		}
		else if(unique && ActiveClothes==PERSONITEM_ARMOUR && itempos == PERSONITEM_ARMOUR)
		{
			barmourswitch  = true;
		}
		// Ż���� ���, 
		else
		{
			barmourswitch  = true;

			SI32 DressFlag1 = PERSONITEM_DRESS;
			SI32 DressFlag2 = PERSONITEM_ARMOUR;

			if( ActiveClothes == PERSONITEM_ARMOUR)
			{
				DressFlag1 =  PERSONITEM_ARMOUR;
				DressFlag2 =  PERSONITEM_DRESS;

			}
			// ������ ������ ������ �̹����� �����Ѵ�. 
			if(pclCI->clCharItem.clItem[DressFlag1].siUnique)
			{
				unique = pclCI->clCharItem.clItem[DressFlag1].siUnique;
			}
			else
			{
				unique = pclCI->clCharItem.clItem[DressFlag2].siUnique;
			}
		}
	}
	if(barmourswitch)

	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(unique);
		if(ref > 0 )
		{
			armcode = pclItemManager->pclItemInfo[ref]->GetArmCode();
		}
		else armcode = NULL;

		if(armcode)
		{
			updateswitch	= true;
			StringCchCopy(szArmourCode,  32, armcode);
		}
		else
		{
			updateswitch	= true;
			StringCchCopy(szArmourCode,  32, TEXT("KOR01"));
		}

	}
	if(itempos == PERSONITEM_WEAPON1)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(unique);

		if(ref > 0 )
		{
			armcode = pclItemManager->pclItemInfo[ref]->GetArmCode();
		}
		else armcode = NULL;


		if(ActiveWeapon == itempos)
		{

			if(armcode)
			{
				updateswitch	= true;
				StringCchCopy(szWeaponCode,  32, armcode);
			}
			else
			{
				updateswitch	= true;
				StringCchCopy(szWeaponCode,  32, TEXT("KOR01"));
			}
		}
	}

	if(itempos == PERSONITEM_WEAPON2)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(unique);
		if(ref > 0 )
		{
			armcode = pclItemManager->pclItemInfo[ref]->GetArmCode();
		}
		else armcode = NULL;

		if(ActiveWeapon == itempos)
		{

			if(armcode)
			{
				updateswitch	= true;
				StringCchCopy(szWeaponCode,  32, armcode);
			}
			else
			{
				updateswitch	= true;
				StringCchCopy(szWeaponCode,  32, TEXT("KOR01"));
			}
		}
	}

	if ( itempos == PERSONITEM_MANTLE)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(unique);
		if(ref > 0 )
		{
			armcode = pclItemManager->pclItemInfo[ref]->GetArmCode();
		}
		else armcode = NULL;

		if ( armcode )
		{
			updateswitch	= true;
			StringCchCopy( szMantleCode,  32, armcode );
		}
		else
		{
			updateswitch	= true;
			StringCchCopy( szMantleCode,  32, TEXT("") );
		}
	}

	SI32 EffectKind = 0;
	SI32 AttackScrollNum = 0;
	SI32 attacklayerskill = 0;

	if ( GetID() == 1 )
	{
		if ( pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique > 0  )
		{	
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique );

			if ( Ref )
			{
				SI32 AttackType = pclClient->pclItemManager->pclItemInfo[ Ref ]->GetAttackType();

				switch( AttackType )
				{
				case ATTACKTYPE_SWORD:
					attacklayerskill = SKILL_USESWORD1;
					break;
				case ATTACKTYPE_SPEAR:
					attacklayerskill = SKILL_USESPEAR1;
					break;
				case ATTACKTYPE_AXE:
					attacklayerskill = SKILL_USEAXE1;
					break;
				}

				AttackScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum( pclClient->pclItemManager, attacklayerskill ) ;

				if ( AttackScrollNum > 0 )
				{
					if ( AttackScrollNum > 3 )
					{
						EffectKind = 2;
					}
					else
					{
						EffectKind = 1;
					}
				}
				updateswitch = true;
			}
		}
	}
	else
	{
		if ( clPB.clShapeEquip.clWeapon.uiUnique > 0 )
		{
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( clPB.clShapeEquip.clWeapon.uiUnique );

			if ( Ref )
			{
				SI32 AttackType = pclClient->pclItemManager->pclItemInfo[ Ref ]->GetAttackType();

				switch( AttackType )
				{
				case ATTACKTYPE_SWORD:
					AttackScrollNum = clPB.clShapeEquip.siSwordScrollNum;
					break;
				case ATTACKTYPE_SPEAR:
					AttackScrollNum = clPB.clShapeEquip.siSpearScrollNum;
					break;
				case ATTACKTYPE_AXE:
					AttackScrollNum = clPB.clShapeEquip.siAxeScrollNum;
					break;
				}
			}

			if ( AttackScrollNum > 0 )
			{
				if ( AttackScrollNum > 3 )
				{
					EffectKind = 2;
				}
				else
				{
					EffectKind = 1;
				}

				updateswitch = true;
			}
		}
	}
	if(updateswitch == true)
	{
		//cyj ������ ���� ����ȿ�� ��ȭ �ӽ÷� ����
		EffectKind = 0;

		//KHY - 1001 - ��µ��� 5���� ���� ����.
		// ���� Ÿ�� �ִٸ�, 
		//if ( pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
		if ( pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE)
		{
			pclCharDraw->LoadItemCodeData(GetKind(), szHelmetCode,	szArmourCode,	szWeaponCode, szMantleCode, szHorseCode, EffectKind, NULL );
		}
		else
		{
			pclCharDraw->LoadItemCodeData(GetKind(), szHelmetCode,	szArmourCode,	szWeaponCode, szMantleCode, TEXT(""), EffectKind, NULL );
		}

		// ���� ����� ������Ʈ �Ѵ�. 
		// JAYCEE ATTACK
		if(itempos == PERSONITEM_WEAPON1 || itempos == PERSONITEM_WEAPON2)
		{
#ifdef _SAFE_MEMORY
			clPB.CalculateAttackType(this, ActiveWeapon, &pclCI->clCharItem.clItem[0]);
#else
			clPB.CalculateAttackType(this, ActiveWeapon, pclCI->clCharItem.clItem);
#endif
		}

		if(itempos == PERSONITEM_WEAPON1 || itempos == PERSONITEM_WEAPON2)
		{
			// ĳ������ �ִϸ��̼��� �����Ѵ�. 
			// ������� ����Ǿ� �ִϸ��̼��� �ٲ��� �Ѵ�. 
			SetAnimation(Animation);
		}
	}

	return true;
}

// �� �ڵ带 �����Ͽ� ��ġ�Ѵ�.
void cltCharClient::ChangeHorseCode( SI32 code, cltDate* cldate, SI32 ticket )
{
	if( pclCharDraw == NULL )
		return;

	SI32 EffectKind = 0;
	SI32 AttackScrollNum = 0;
	SI32 attacklayerskill = 0;

	if ( GetID() == 1 )
	{	
		if ( ActiveWeapon > 0 && pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique > 0 )
		{
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclCI->clCharItem.clItem[ ActiveWeapon ].siUnique );

			if ( Ref )
			{
				SI32 AttackType = pclClient->pclItemManager->pclItemInfo[ Ref ]->GetAttackType();

				switch( AttackType )
				{
				case ATTACKTYPE_SWORD:
					attacklayerskill = SKILL_USESWORD1;
					break;
				case ATTACKTYPE_SPEAR:
					attacklayerskill = SKILL_USESPEAR1;
					break;
				case ATTACKTYPE_AXE:
					attacklayerskill = SKILL_USEAXE1;
					break;
				}

				AttackScrollNum = pclCI->clCharItem.UseWeasponSkillScrollNum( pclClient->pclItemManager, attacklayerskill ) ;

				if ( AttackScrollNum > 0 )
				{
					if ( AttackScrollNum > 3 )
					{
						EffectKind = 2;
					}
					else
					{
						EffectKind = 1;
					}
				}
			}
		}
	}
	else
	{
		if ( clPB.clShapeEquip.clWeapon.uiUnique > 0 )
		{
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( clPB.clShapeEquip.clWeapon.uiUnique );

			if ( Ref )
			{
				SI32 AttackType = pclClient->pclItemManager->pclItemInfo[ Ref ]->GetAttackType();

				switch( AttackType )
				{
				case ATTACKTYPE_SWORD:
					AttackScrollNum = clPB.clShapeEquip.siSwordScrollNum;
					break;
				case ATTACKTYPE_SPEAR:
					AttackScrollNum = clPB.clShapeEquip.siSpearScrollNum;
					break;
				case ATTACKTYPE_AXE:
					AttackScrollNum = clPB.clShapeEquip.siAxeScrollNum;
					break;
				}
			}

			if ( AttackScrollNum > 0 )
			{
				if ( AttackScrollNum > 3 )
				{
					EffectKind = 2;
				}
				else
				{
					EffectKind = 1;
				}
			}
		}
	}

	//cyj ������ ���� ����ȿ�� ��ȭ �ӽ÷� ����
	EffectKind = 0;

	if(code == 0)
	{

		pclCI->clHorseInfo.siCurrentHorseRIDEHORSE	= false;
		StringCchCopy(szHorseCode, 32, TEXT(""));
		pclCharDraw->LoadItemCodeData( GetKind(), szHelmetCode,	szArmourCode,	szWeaponCode, szMantleCode, NULL, EffectKind, NULL );
	}
	else
	{
		pclCI->clHorseInfo.siCurrentHorseRIDEHORSE	= true;

		StringCchCopy(szHorseCode, 32, pclClient->pclHorseManager->pclHorseTypeInfo[code]->szCode);

		pclCharDraw->LoadItemCodeData(GetKind(), szHelmetCode,	szArmourCode,	szWeaponCode, szMantleCode, szHorseCode, EffectKind, NULL );

		if ( cldate != NULL && ticket >= 0 )
		{
			cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
			if(pclHorse != NULL)
			{
				pclHorse->clAddStatusDate.Set(cldate) ;
				pclHorse->siStatusTicketNum = ticket ;
			}
		}
	}

	// ���� ���ؼ� �ִϸ��̼� ������ ����ǹǷ� �̸� �����ؾ� �Ѵ�. 
	SetAnimation(Animation);

}

//-----------------------------------
// ��ǰ ����. 
//-----------------------------------
bool cltCharClient::SetMakeDelayDraw(DWORD delayclock)
{
	if(delayclock)
	{
		bStartMakeItemSwitch	= true;
		dwStartMakeItemClock	= TABS(pclClient->CurrentClock);
		dwDelayMakeItemClock	= delayclock;
	}
	else
	{
		bStartMakeItemSwitch	= false;
		dwStartMakeItemClock	= 0;
		dwDelayMakeItemClock	= 0;
	}

	return true;
}

// ��ǰ ���� ������ ǥ���Ѵ�. 
void cltCharClient::DrawMakeDelay(LPDIRECTDRAWSURFACE7 lpSurface, SI32 rx, SI32 ry)
{
	if(bStartMakeItemSwitch == false)return ;

	// ǥ���ؾ� �� ����. 
	SI32 maxclock	= max(1, (dwDelayMakeItemClock / 1000));
	SI32 leftclock	= TABS(pclClient->CurrentClock - dwStartMakeItemClock) / 1000;

	SI32 x = 450 + (g_SoundOnOffDlg.m_bMaxWindowMode ? 15 : 0 )  ; // Ǯ��ũ���̸� ��ǥ 30�� ������
	SI32 y = 50;

	TSpr* psprpart	= pclClient->GetGlobalSpr(GIMG_MAKEITEMDRAWPART1);
	TSpr* psprframe	= pclClient->GetGlobalSpr(GIMG_MAKEITEMDRAWPART2);
	TSpr* pspr		= pclClient->GetGlobalSpr(GIMG_MAKEITEMDRAWPART3);


	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		y += 30 ;
	}

	if ( GP.LockSurface( lpSurface ) == TRUE )
	{

		// Ʋ ���. 
		if(psprframe)
		{
			GP.PutSpr(psprframe, x + rx, y + ry, 0);

			// ���� ���. 
			if(psprpart)
			{
				SI32 maxxnum = (psprframe->GetXSize() - 6) / psprpart->GetXSize();

				SI32 drawnum =  min(maxxnum, ( leftclock * maxxnum * psprpart->GetXSize() / maxclock ) / psprpart->GetXSize());

				for(SI32 i = 0;i < drawnum;i++)
				{
					GP.PutSpr(psprpart, x + 3 + i*psprpart->GetXSize() + rx, y + 4 + ry, 0);
				}
			}

			x += psprframe->GetXSize();
			y += 3;
		}


		if(pspr)
		{
			// ����. 
			x = GP.DrawNumber(pspr, x + rx, y + ry, 0, leftclock);

			GP.PutSpr(pspr, x, y + ry, 10);

			GP.DrawNumber(pspr, x+ pspr->GetXSize(), y + ry, 0, maxclock);
		}


		GP.UnlockSurface( lpSurface );
	}


}


//-----------------------------------
// Health Bar�� �׷��ش�.
//-----------------------------------
void cltCharClient::DrawHealthBar()
{
	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 realxsize = GetKindInfo(true)->clKIDrawInfo.siXsizePercent*ImageXsize/100;
	SI32 realysize = GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;

	// by LEEKH 2007.12.24 - TRANSFORM
	SI32 drawx	= DrawStartX + (ImageXsize-realxsize)/2;
	SI32 drawy	= DrawStartY + ImageYsize - GetKindInfo(true)->clKIDrawInfo.siBottomIndent - realysize;

	GP.Box(drawx, drawy - 1, drawx + realxsize + 1, drawy + 3, 255);

	// �������� ǥ���Ѵ�. 
	if(clPB.GetMaxLife() > 0)
	{
		SI32 fillsize = min(realxsize, GetLife() * realxsize / clPB.GetMaxLife() );

		GP.FillBox(drawx + 1 ,			drawy ,	drawx + 1 + fillsize -1,	drawy + 2, 20,FALSE);
		if(drawx + 1 + fillsize < drawx + realxsize)
		{
			GP.FillBox(drawx + 1 + fillsize ,drawy , drawx + realxsize,			drawy + 2, 243,FALSE);
		}
#ifdef _DEBUG
		TSpr* pspr2	= pclClient->GetGlobalSpr(GIMG_WARKILLNUM);
		if ( pspr2 )
		{
			GP.DrawNumber( pspr2, drawx, drawy, 0, GetLife() );
		}
#endif

	}
}

//-----------------------------------
// King Effect�� �׷��ش�.
//-----------------------------------
void cltCharClient::DrawKingEffect()
{

	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_KINGEFFECT);
	if(pspr)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		//SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2;
		//SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		//SI32 starty	= DrawStartY + ImageYsize - GetKindInfo(true)->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize()/2+35;  

		//GP.PutSprScreen(pspr, startx , starty, max(0, TABS(pclClient->CurrentClock / 50)) / 3 % 15);
		//by LEEKH 2007.12.24 - TRANSFORM
		cltKindInfo* ppclKI = pclKI;

		if(selectRealAnyType( ) == false)
			ppclKI = GetKindInfo(true);

		SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2 ;
		SI32 realysize	= ppclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - ppclKI->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize()/2+38;   

		GP.PutSprScreen(pspr, startx , starty, max(0, pclClient->CurrentClock / 50) / 3 % 15);    

	}
}


//-----------------------------------
// ��Ȳ�� Effect�� �׷��ش�.
//-----------------------------------
void cltCharClient::DrawGodEffect()
{

	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_GODEFFECT);
	if(pspr)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2 ;
		SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - GetKindInfo(true)->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize()/2;

		GP.PutSprScreen(pspr, startx , starty, max(0, pclClient->CurrentClock / 50) / 3 % 50);

	}
}

//-----------------------------------
//KHY - 1220 - ���Žý���.
//�ش� ���� ĳ���� ��ũ�� 100%�̸�.
//-----------------------------------
void cltCharClient::DrawTransformSyc100Effect()
{
	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_TRANSFORM_SYNCHRO100);
	if(pspr)
	{
		SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2 ;
		SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - GetKindInfo(true)->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize()/2 - 30;

		GP.PutSprScreen(pspr, startx , starty, max(0, pclClient->CurrentClock / 50) / 3 % 15);    
	}
}

//-----------------------------------
// ��ȯ�� Effect�� �׷��ش�.�߰� :������ �׷��ִ� ����. ��ȯ�� �Ӹ����� ����
//-----------------------------------
void cltCharClient::DrawSummonEffect()
{
	/*
	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_SUMMONMARK);
	if(pspr)
	{
	SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2 ;
	SI32 realysize	= pclKI->clKIDrawInfo.siYsizePercent*ImageYsize/100;
	SI32 starty	= DrawStartY + ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - realysize - pspr->GetYSize()/2 - 10;


	GP.PutSprScreen(pspr, startx , starty, max(0, pclClient->CurrentClock / 50) / 2 % 27);
	}
	*/
}

//-----------------------------------
// ���� ��ȯ�� �� Effect�� �׷��ش�.
//-----------------------------------
void cltCharClient::DrawGachaSummonEffect()
{
	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_GACHASUMMON_EFFECT);
	if(pspr)
	{
		// by LEEKH 2007.12.24 - TRANSFORM
		SI32 startx = DrawStartX + ImageXsize/2 - pspr->GetXSize()/2 ;
		SI32 realysize	= GetKindInfo(true)->clKIDrawInfo.siYsizePercent*ImageYsize/100;
		SI32 starty	= DrawStartY + ImageYsize - GetKindInfo(true)->clKIDrawInfo.siBottomIndent - realysize/2 - pspr->GetYSize()/2;

		GP.PutSprScreen(pspr, startx , starty, max(0, pclClient->CurrentClock / 50) / 2 % 20);

	}
}

void cltCharClient::DrawGate(SI32 id)
{
	if(pclCM->IsAlive(id))
	{
		SI32 siGateLife = pclCM->CR[id]->pclCI->clIP.siVit*4;

		SI32 startx;
		SI32 starty;

		if( pclCM->CR[id]->GetLife() <  siGateLife * 0.9)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE4);
			if(pspr)
			{
				startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 - 33;
				starty	= DrawStartY - 40;//+ 30;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = (pclClient->CurrentClock / 100) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
		if( pclCM->CR[id]->GetLife() <  siGateLife * 0.6)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE4);
			if(pspr)
			{
				startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 + 60;
				starty = DrawStartY + 60;//+ 30;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = (pclClient->CurrentClock / 100) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
		if( pclCM->CR[id]->GetLife() <  siGateLife * 0.3)
		{
			TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE4);
			if(pspr)
			{
				startx = DrawStartX + ImageXsize/2 - pspr->GetXSize() /2 - 120;
				starty = DrawStartY + 10;//+ 30;//ImageYsize - pclKI->clKIDrawInfo.siBottomIndent - pspr->GetYSize() /2;

				SI32 font = (pclClient->CurrentClock / 100) % pspr->GetImageNum();	

				GP.PutSprLight1(pspr, startx,		starty, font);
			}
		}
	}
}

bool cltCharClient::NewYearEventDay(void)
{
	//[�߰� : Ȳ���� 2007. 12. 12 �ų��̺�Ʈ �Ⱓ.]
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
	case ConstServiceArea_NHNChina	:	// NHN�߱��� �ų� �̺�Ʈ�� ���״�..�Ⱓ �߰�.
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   27;		EndTime.wDay	=    8;
			StartTime.wHour	 =    3;		EndTime.wHour	=    2;
		}
		break;

	case ConstServiceArea_EUROPE :
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   27;		EndTime.wDay	=    8;
			StartTime.wHour	 =    3;		EndTime.wHour	=    2;
		}
		break;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if(true == TimeInBounds(&pclclient->sTime, &StartTime, &EndTime))
	{
		return true;
	}

	return false;	
}

SI16 cltCharClient::GetQuestDisplayMark( cltSystemNPC* pclSystemNPCInfo )
{
	if ( NULL == pclSystemNPCInfo )
	{
		return QUEST_DISPLAY_MARK_NONE;
	}

	cltCharClient* pclMyChar = (cltCharClient*)pclCM->CR[1];
	if ( NULL == pclMyChar )
	{
		return QUEST_DISPLAY_MARK_NONE;
	}

	SI16			siQuestType		= pclSystemNPCInfo->m_siQuestType;
	cltQuestInfo*	pclQuestInfo	= &pclClient->pclQuestManager->clQuestInfo[siQuestType][0];
	if ( NULL == pclQuestInfo )
	{
		return QUEST_DISPLAY_MARK_NONE;
	}

	//============================================================================================================
	// 1. �� DisplayMode�� ������ �˻��Ѵ�
	//============================================================================================================
	SI16 siDisplayMode = pclSystemNPCInfo->m_siImageDisplayMode;

	if ( QUESTDISPLAY_MODE_CONDITION == siDisplayMode )
	{
		SI32 siNowLevel		= pclMyChar->pclCI->clIP.GetLevel();
		SI32 siNeedLevel	= pclQuestInfo->clInitConditionInfo.siLevel;
		SI16 siClearCond	= pclQuestInfo->clQuestClearConditionInfo.siFlag;
		SI32 siQuestUinque	= pclQuestInfo->clQuestClearConditionInfo.siPara1;
		bool bLevelCheck	= false;
		bool bCondCheck		= true;	// �ʱⰪ�� true�� �� ������ �ڵ����� ���̱� ����

		// ������ ��������Ʈ ������ ���� �ٸ��� ����ɼ� �����Ƿ� �и��ؼ� �˻�
		if ( siNeedLevel <= siNowLevel )
		{
			bLevelCheck = true;
		}

		if ( QUEST_CLEAR_COND_CLEARQUEST == siClearCond )
		{
			if ( true == pclMyChar->pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager, siQuestUinque) )
			{
				bCondCheck = true;
			}
			else
			{	
				bCondCheck = false;
			}
		}

		if ( (false == bLevelCheck) || (false == bCondCheck) )
		{
			return QUEST_DISPLAY_MARK_NONE;
		}
	}
	else if ( QUESTDISPLAY_MODE_GOING == siDisplayMode)
	{
		if ( false == pclMyChar->pclCI->clQuestInfo.IsQuestClearOrGoing( siQuestType ) )
		{
			return QUEST_DISPLAY_MARK_NONE;
		}
	}

	//============================================================================================================
	// 2. ���������� � ��ũ�� �׷����ϴ��� �˻��Ѵ�
	//============================================================================================================
	cltPersonQuestUnitInfo*	pclunit = &pclMyChar->pclCI->clQuestInfo.clUnit[siQuestType];
	cltQuestInfo*			pclinfo = pclClient->pclQuestManager->GetQuestInfo(pclunit->siCurQuestUnique);

	if ( (NULL == pclunit) || (NULL == pclinfo) )
	{
		return QUEST_DISPLAY_MARK_NONE;
	}

	// ������ ����Ʈ�� ���ٸ�
	if( pclunit->siCurQuestUnique == 0 )
	{
		return QUEST_DISPLAY_MARK_GREETING;
	}
	// ������ ����Ʈ�� �Ϸ� �� ���¶��
	// ����Ʈ�� ������ ��Ȳ�̶��, 
	else if ( true == pclMyChar->IsClearCondition(siQuestType, &pclinfo->clQuestClearConditionInfo) )
	{				
		return QUEST_DISPLAY_MARK_CLEAR;
	}

	return QUEST_DISPLAY_MARK_GOING;

}
