#include "..\..\Common\CommonHeader.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\Client\Client.h"

#include "..\..\Client\Music\Music.h"
#include "..\..\Order\Order.h"

#include "Bullet\Bullet.h"
#include "Smoke\Smoke.h"
#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

extern cltCommonLogic* pclClient;

//----------------------------------------
// �״� ���� 
//----------------------------------------
bool cltCharClient::Action_Dying()
{

	cltCharCommon::Action_Dying();

	//-----------------------------
	// ����� �ѹ��� �̷������ �� ���� 
	//-----------------------------
	if(bDyingOperationSwitch == false)
	{
		bDyingOperationSwitch = true;
		TCHAR *pTitle =GetTxtFromMgr(5612);
		TCHAR *pText = GetTxtFromMgr(5613);
	
		cltClient *pclclient = (cltClient*)pclClient;
		if ( pclclient->pclCM->CR[1]->pclCI->clIP.GetLevel() < INIT_LEVEL )
		{
			SI32 mapindex = pclclient->pclCM->CR[1]->GetMapIndex()	;
			if( false == IsGuildWarMap_NEW( mapindex) && false == IsGuildWarMap_Use_New_GuildWar(mapindex ) )	// ������ �ƴҶ��� ���´�
			{
				if(pclclient->IsUser(GetCharUnique()))
				{
					(pclclient->m_pDialog[ NOTIFYMSG_DLG ])->SetText( pTitle, pText);
				}
			}			
		}
		// by LEEKH 2007.12.24 - TRANSFORM
		// ��� �Ҹ�. 
		if(GetKindInfo()->clKIEffectInfo.siDyingEffect)
		{
			pclclient->PushEffect(GetKindInfo()->clKIEffectInfo.siDyingEffect, GetX(), GetY());
		}

		// Clone�� ������ ������ �� ���⸦ �����.
		if(IsAtb(ATB_CLONE) && clInnerStatus.IsStatus(INNERSTATUS_CLONE) == true)
		{
			if(GetKind()==pclClient->GetUniqueFromHash( TEXT("KIND_JAR")) )	
				pclClient->pclSmokeManager->SetSmoke(SMOKE_JARSMOKE, siCenterX, siCenterY, pclMap);
		}

		// [����] ��µ��� �״� ���� �߰� (2008.06.18)

		cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();

		// ��µ����� �����ϰ� �ְ�, �ö�ź ���¿����� ���尡 ����
		if ( (NULL != pclHorse) && (true == pclCI->clHorseInfo.siCurrentHorseRIDEHORSE) )
		{
			SI32 siSoundUnique = 0;

			// �� ��µ������� ���� �ϵ��ڵ�
			switch ( pclHorse->siHorseUnique )
			{
				case HORSEUNIQUE_ELEPHANT:
					{
						siSoundUnique = pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_ELEPHANT_DIE"));
					}
					break;
			}

			// �״� ���尡 �������� �����Ѵ�
			if ( siSoundUnique )
			{
				pclclient->PushEffect( siSoundUnique, GetX(), GetY() );
			}
		}
	}

	SetAnimation(ANITYPE_DYING);
	if(DoAnimationDelay(ANIATB_ONLYONCE) == TRUE)
	{
		// �ִϸ��̼��� �� ������, 
		if(clAniInfo.IsLast() )
		{
			if(bGhostShowSwitch == false)  
			{
				bGhostShowSwitch = true;
				
				// ȥ���� �ö󰡴� ����� �����. 
				//if((GetKind () != pclClient->GetUniqueFromHash(TEXT("KIND_TOYO1")) ) && (clInnerStatus.IsStatus(INNERSTATUS_CLONE) == false))
				//{
				//	pclClient->pclSmokeManager->SetSmoke(SMOKE_GHOST, siCenterX, siCenterY, pclMap);
				//}
				
				// ��������� �ߴ��ϰ� ������� �����Ѵ�. 
				cltClient* pclclient = (cltClient*)pclClient;
				
				// ���ΰ��� �׾��ٸ�, 
				if(pclclient->IsUser(GetCharUnique()))
				{
					pclclient->pclMusic->pclSoundManager->PlayBackGroundFile( TEXT("./Music/Music_HeroDie1.ogg"), false, false );

				}
				return TRUE;          
			}
		}
	}


    return FALSE;
}



