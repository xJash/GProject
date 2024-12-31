#include "MagicWhirlPoolObj.h"

#include "../MagicMsgObj.h"
#include "../MagicMgr.h"

#include "../../../Common/SMLib/LibList/LibList.h"
#include "../../../Common/Bullet/Bullet.h"
#include "Char\CharManager\CharManager.h"

#include "../../../Client/client.h"
extern cltCommonLogic* pclClient;

CMagicWhirlPoolObj::CMagicWhirlPoolObj( CMagicMgr *pMagicMgr ) : CMagicBaseObj( pMagicMgr )
{
	m_pMagicInfo = new stMagicInfo();

	m_si32AddDamage = 0;
	m_si32CurrentMagicActionFrame = 0;

	m_si32DotStartXPos = 0;
	m_si32DotStartYPos = 0;

	m_si32MoveMentDelayTime = MOVEMENTDELAYTIME;

	Initialize();
}

CMagicWhirlPoolObj::~CMagicWhirlPoolObj()
{
	Destroy();
}

void CMagicWhirlPoolObj::Initialize()
{
	memset( m_pMagicInfo, 0, sizeof( stMagicInfo ) );
	m_si32AddDamage = 0;
	m_si32CurrentMagicActionFrame = 0;
	m_si32DotStartXPos = 0;
	m_si32DotStartYPos = 0;
	m_si32MoveMentDelayTime = 0;
	m_si32TargetDotXPos = 0;
	m_si32TargetDotYPos = 0;

	m_cBigXPos = 2;
	m_cBigYPos = 2;

	m_si32MoveMentDelayTime = MOVEMENTDELAYTIME;

	return;
}

void CMagicWhirlPoolObj::Destroy()
{
	if ( m_pMagicInfo )
	{
		delete m_pMagicInfo;
		m_pMagicInfo = NULL;
	}

	return;
}

bool CMagicWhirlPoolObj::SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel , SI32 siOrganUnique)
{	

	//--------------------------------------------------------
	//--------------------- ����ϴ� �� ��
	// FromID ��� ���ؼ�.
	SI32 charunique = pstMagicInfo->sHeader.si32FromID;
	if ( charunique <1 )		return false;

	// KIND�� �����Ѵ�.
	SetKind(pstMagicInfo->sHeader.si32MagicKind);


	SI32 Fromid		= pclClient->pclCM->GetIDFromCharUnique(charunique);
	if(pclClient->pclCM->IsAlive(Fromid) == false)
	{
		return false;
	}

	m_si32MoveMentDelayTime = MOVEMENTDELAYTIME;
		
	// Dot ������ ��� ��ǥ	
	pclClient->pclCM->CR[ Fromid ]->DecideAttackPoint( 0, m_si32DotStartXPos, m_si32DotStartYPos );	
	//---------------------------------------------------------


	memcpy( m_pMagicInfo, pstMagicInfo, sizeof( stMagicInfo ) );
	m_pclMap = pclMap;
	m_si32AddDamage = si32AddDamage;

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

	
	m_si32TotalDamage = 0;

	SI32 siMinDamage= 0, siMaxDamage = 0;
	if(pclClient->pclMagicManager->GetMinMaxDamage(pstMagicInfo, m_si32AddDamage, si32SkillLevel, siMinDamage, siMaxDamage, siOrganUnique)==false)
	{
		return false;
	}
	pclClient->pclMagicManager->CalculateDamage(siMinDamage, siMaxDamage, m_si32TotalDamage);

	//-----------------------------------
	// ȿ������ �����Ѵ�. 
	//----------------------------------
	pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_WHIRLPOOL_FIRE")), pclClient->pclCM->CR[ Fromid ]->GetX(), pclClient->pclCM->CR[ Fromid ]->GetY());

	return true;
}

// ���� ���� �Ұ�
bool CMagicWhirlPoolObj::Action()
{	
	if ( GetCurrentFrame() + 1 >= GetMaxFrameNum() )
	{
		SetCurrentFrame( 0 );
	}
	else
	{
		SetCurrentFrame( GetCurrentFrame() + 1 );
	}


	//if ( CMagicBaseObj::Action() )
	//{
	//	return true;
	//}	

	// ������ ���� �ð�( MaxActionFrame )�� ������ ��쿡�� ������ �ϹǷ�...
	// �̷��� ���� ���� ��� ������ ������ �ʰ���...
	if ( ++m_si32CurrentMagicActionFrame == GetMagicAttributePtr()->si32MagicMaxActionFrame )
	{
		SetStatus( MAGIC_REST_STATUS );
		SetCurrentFrame( 0 );

		m_si32CurrentMagicActionFrame = 0;

		return true;
	}

	
	SI32 Fromcharunique = m_pMagicInfo->sHeader.si32FromID;
	if ( Fromcharunique < 1)
		return false;

	SI32 Fromid		= pclClient->pclCM->GetIDFromCharUnique(Fromcharunique);
	if ( Fromid < 1 )
		return false;

	//---------------------------------------------------------
	//------------------------ Ÿ���� �Ǵ� ��
	//
	SI32 charunique = m_pMagicInfo->sHeader.si32ToID;
	if ( charunique < 1)
		return false;
	SI32 Toid  = pclClient->pclCM->GetIDFromCharUnique(charunique);
	if ( Toid < 1 )
		return false;
	

	if( pclClient->pclCM->IsAlive(Toid) == false )
	{
		//SetStatus( MAGIC_REST_STATUS );
		//SetCurrentFrame( 0 );

		//m_si32CurrentMagicActionFrame = 0;

		return false;				// ���Ͱ� �׾����� ������� ȸ������ si32MagicMaxActionFrame ��ŭ ��� �־�� �ϹǷ�...
	}


	
	//---------------------------------------------------------	
	
	
	
	//---------------------------------------------------------	
	// ȸ������ �����̴� �κ�
	if ( pclClient->pclCM->CR[Toid]->pclMap == m_pclMap )		// ���� �ʿ� ���� ������ ȸ������ �����̸� �ȵǹǷ�...
	{	
		if ( ++m_si32MoveMentDelayTime > MOVEMENTDELAYTIME )
		{
			// Dot ������ ���� ��ǥ	++m_si32MoveMentDelayTime > MOVEMENTDELAYTIME <--- �� ��쿡�� ������ �ٲ��� �ϹǷ�...
			pclClient->pclCM->CR[ Toid ]->DecideAttackPoint( 0, m_si32TargetDotXPos, m_si32TargetDotYPos );

			if ( m_si32DotStartXPos < m_si32TargetDotXPos )
			{
				m_cBigXPos = 1;
				m_si32DotStartXPos += MOVEMENT;
			}
			else if ( m_si32DotStartXPos > m_si32TargetDotXPos )
			{
				m_cBigXPos = 0;
				m_si32DotStartXPos -= MOVEMENT;
			}
			else
			{
				m_cBigXPos = 2;
			}
			
			if ( m_si32DotStartYPos < m_si32TargetDotYPos )
			{
				m_cBigYPos = 1;
				m_si32DotStartYPos += MOVEMENT;
			}
			else if ( m_si32DotStartYPos > m_si32TargetDotYPos )
			{
				m_cBigYPos = 0;
				m_si32DotStartYPos -= MOVEMENT;
			}
			else
			{
				m_cBigYPos = 2;
			}

			if ( GetCurrentFrame() + 1 >= GetMaxFrameNum() )
			{
				SetCurrentFrame( 0 );
			}
			else
			{
				SetCurrentFrame( GetCurrentFrame() + 1 );
			}

			m_si32MoveMentDelayTime = 0;
		}
		else
		{
			if ( m_cBigXPos == 1 )
			{
				m_si32DotStartXPos += MOVEMENT;
			}
			else if ( m_cBigXPos == 0 )
			{
				m_si32DotStartXPos -= MOVEMENT;
			}			
			
			if ( m_cBigYPos == 1 )
			{
				m_si32DotStartYPos += MOVEMENT;
			}
			else if ( m_cBigYPos == 0 )
			{
				m_si32DotStartYPos -= MOVEMENT;
			}

			if ( GetCurrentFrame() + 1 >= GetMaxFrameNum() )
			{
				SetCurrentFrame( 0 );
			}
			else
			{
				SetCurrentFrame( GetCurrentFrame() + 1 );
			}
		}
	}
	//---------------------------------------------------------		

	if ( pclClient->GameMode == GAMEMODE_SERVER )		// ����
	{
		if ( m_si32CurrentMagicActionFrame % 40 == 0 )
		{
			if(m_si32TotalDamage==0) return false; 
			SetDamage( m_si32TotalDamage );
		}
	}

	return false;
}

void CMagicWhirlPoolObj::Draw( )
{	
	if ( GetStatus() != MAGIC_PLAY_STATUS )
	{
		return;
	}

	SetMagicSpr( GIMG_MAGIC_WHIRLPOOL );				// Image index

	SHORT screenx=0, screeny=0;
	cltMapClient* pclmap = (cltMapClient*)m_pclMap;
	pclmap->TransFromRealDotToScreenDot(m_si32DotStartXPos, m_si32DotStartYPos, screenx, screeny);

	m_si32DrawXPos = screenx - GetMagicSpr()->GetXSize()/2;
	m_si32DrawYPos = screeny - GetMagicSpr()->GetYSize()/2;

	GP.PutSprLight1(GetMagicSpr(), m_si32DrawXPos, m_si32DrawYPos, GetCurrentFrame() );

	return;
}


// Push
bool CMagicWhirlPoolObj::Push( BYTE *pData, SI32 si32Size )
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

void CMagicWhirlPoolObj::SetDamage( SI32 si32Damage )
{
	stMagicMsgWhirlPoolDamage	sMagicMsgWhirlPoolDamage;
	
	sMagicMsgWhirlPoolDamage.sMagicMsgHeader.si16MsgSize = sizeof( stMagicMsgWhirlPoolDamage );
	sMagicMsgWhirlPoolDamage.sMagicMsgHeader.si32MagicKind = GetKind();
	sMagicMsgWhirlPoolDamage.sMagicMsgHeader.si32MsgKind = MAGIC_WHIRLPOOL_DAMAGE;

	m_pclMap->GetRealTileByRealDot( m_si32DotStartXPos, m_si32DotStartYPos, &sMagicMsgWhirlPoolDamage.si32XCenterPos, &sMagicMsgWhirlPoolDamage.si32YCenterPos);

	sMagicMsgWhirlPoolDamage.si32FromID = m_pMagicInfo->sHeader.si32FromID;
	sMagicMsgWhirlPoolDamage.si32ToID = m_pMagicInfo->sHeader.si32ToID;
	sMagicMsgWhirlPoolDamage.si32Damage = si32Damage;

	sMagicMsgWhirlPoolDamage.si32Radius = GetMagicAttributePtr()->si32MagicRadius;
	
	Push( (BYTE*) &sMagicMsgWhirlPoolDamage, sMagicMsgWhirlPoolDamage.sMagicMsgHeader.si16MsgSize );

	return;
}

