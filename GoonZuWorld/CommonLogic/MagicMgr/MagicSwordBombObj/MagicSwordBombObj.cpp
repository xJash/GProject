#include "MagicSwordBombObj.h"

#include "../MagicMsgObj.h"
#include "../MagicMgr.h"

#include "../../../Common/SMLib/LibList/LibList.h"
#include "Char\CharManager\CharManager.h"

#include "../../../Client/client.h"

extern cltCommonLogic* pclClient;

CMagicSwordBombObj::CMagicSwordBombObj( CMagicMgr *pMagicMgr ) : CMagicBaseObj( pMagicMgr )
{
	m_pMagicInfo = new stMagicInfo();

	Initialize();
}

CMagicSwordBombObj::~CMagicSwordBombObj()
{
	Destroy();
}

void CMagicSwordBombObj::Initialize()
{
	memset( m_pMagicInfo, 0, sizeof( stMagicInfo ) );
	m_si32AddDamage = 0;
	m_si32TotalDamage = 0;
	
	return;
}

void CMagicSwordBombObj::Destroy()
{
	if ( m_pMagicInfo )
	{
		delete m_pMagicInfo;
		m_pMagicInfo = NULL;
	}

	return;
}

bool CMagicSwordBombObj::SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique )
{
	
	SI32 charunique = pstMagicInfo->sHeader.si32FromID;
	if ( charunique <1 )		return false;

	// KIND�� �����Ѵ�.
	SetKind(pstMagicInfo->sHeader.si32MagicKind);

	//---------------------------------
	// �´� ����� ���̵� ���Ѵ�. 
	//---------------------------------
	SI32 toid	= pclClient->pclCM->GetIDFromCharUnique(pstMagicInfo->sHeader.si32ToID);
	if(pclClient->pclCM->IsValidID(toid) == FALSE)
	{
		return false;
	}

	memcpy( m_pMagicInfo, pstMagicInfo, sizeof( stMagicInfo ) );

	stMagicAttributeData *pMagicAttributeData = GetMagicAttributePtr();
	SI32 MinSkillLevel = pMagicAttributeData->si16MagicSkillLevel;

	if ( IsNPC( charunique ) || IsInstanceNPC(charunique))
	{
		CMagicBaseObj::SetMagic( &pstMagicInfo->sHeader, MinSkillLevel );
	}
	else
	{
		CMagicBaseObj::SetMagic( &pstMagicInfo->sHeader, si32SkillLevel );
	}


	m_si32AddDamage = si32AddDamage;
	m_si32TotalDamage = 0;

	SI32 siMinDamage= 0, siMaxDamage = 0;
	if(pclClient->pclMagicManager->GetMinMaxDamage(pstMagicInfo, m_si32AddDamage, si32SkillLevel, siMinDamage, siMaxDamage, siOrganUnique)==false)
	{
		return false;
	}
	pclClient->pclMagicManager->CalculateDamage(siMinDamage, siMaxDamage, m_si32TotalDamage);

	//--------------------------------
	// �ǰ� ����Ʈ�� ���Ѵ�. 
	//--------------------------------
	pclClient->pclCM->CR[toid]->GetBottomPoint(&m_clDotHitPos);
	m_pclMap	= pclClient->pclCM->CR[toid]->pclMap;
	
	return true;
}

// ���� ���� �Ұ�
bool CMagicSwordBombObj::Action()
{	
	if ( CMagicBaseObj::Action() )
	{
		return true;
	}	

	if ( pclClient->GameMode == GAMEMODE_SERVER )		// ����
	{
		if ( GetCurrentFrame() == GetMaxFrameNum() / 3 && GetCurrentMagicDelayFrame() == 0 )
		{
			SI32 charunique = m_pMagicInfo->sHeader.si32ToID;
			if ( charunique < 1 )
			{
				return false;
			}
			
			SI32 id			= pclClient->pclCM->GetIDFromCharUnique(charunique);
			if ( id < 1 )
			{
				return false;
			}

			if(pclClient->pclCM->IsAlive(id) == TRUE)
			{
				if(m_si32TotalDamage==0) return false; 
				SetDamage( m_si32TotalDamage );
			}
		}
	}
	else												// Ŭ���̾�Ʈ
	{
		SI32 charunique = m_pMagicInfo->sHeader.si32ToID;
		if ( charunique <1 )
		{
			return false;
		}
		SI32 id			= pclClient->pclCM->GetIDFromCharUnique(charunique);
		if ( id < 1 )
		{
			return false;
		}

		if ( GetCurrentFrame() == 1 )
		{
			//if(pclClient->pclCM->IsAlive(id) == TRUE)
			{
				pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_SWORDBOMB_FIRE")), pclClient->pclCM->CR[id]->GetX(), pclClient->pclCM->CR[id]->GetY() );
			}
		}
	}


	return false;
}

void CMagicSwordBombObj::Draw( )
{	
	if ( GetStatus() != MAGIC_PLAY_STATUS )
	{
		return;
	}

	SetMagicSpr( GMIG_MAGIC_SWORDBOMB1 );				// Image index

	//--------------------------------------
	// ȭ�� ��¿� ��ǥ�� ��ȯ�Ѵ�. 
	//--------------------------------------
	SHORT screenx=0, screeny=0;
	cltMapClient* pclmap = (cltMapClient*)m_pclMap;
	pclmap->TransFromRealDotToScreenDot(m_clDotHitPos.siX, m_clDotHitPos.siY, screenx, screeny);


	m_si32DrawXPos = screenx - GetMagicSpr()->GetXSize() /2;
	m_si32DrawYPos = screeny - GetMagicSpr()->GetYSize() *2/3;

	if(GetMagicSpr()->GetImageNum() <= 0) return;

	GP.PutSpr(GetMagicSpr(), m_si32DrawXPos, m_si32DrawYPos, GetCurrentFrame() % GetMagicSpr()->GetImageNum());

	TSpr* pspr	= pclClient->GetGlobalSpr(GMIG_MAGIC_SWORDBOMB2);
	if(pspr && pspr->GetImageNum() > 0)
	{
		GP.PutSprScreen(pspr, m_si32DrawXPos, m_si32DrawYPos, GetCurrentFrame()% pspr->GetImageNum());
	}
	
	return;
}


// Push
bool CMagicSwordBombObj::Push( BYTE *pData, SI32 si32Size )
{
	if ( CMagicBaseObj::Push( pData, si32Size ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CMagicSwordBombObj::SetDamage( SI32 si32Damage )
{
	stMagicMsgDamage sMagicMsgDamage;

	sMagicMsgDamage.sMagicMsgHeader.si16MsgSize = sizeof( stMagicMsgDamage );
	sMagicMsgDamage.sMagicMsgHeader.si32MagicKind = GetKind();
	sMagicMsgDamage.sMagicMsgHeader.si32MsgKind = MAGIC_DAMAGE;

	sMagicMsgDamage.si32FromID = m_pMagicInfo->sHeader.si32FromID;
	sMagicMsgDamage.si32ToID = m_pMagicInfo->sHeader.si32ToID;

	sMagicMsgDamage.si32Damage = si32Damage;
	
	Push( (BYTE*) &sMagicMsgDamage, sMagicMsgDamage.sMagicMsgHeader.si16MsgSize );	

	return;
}
