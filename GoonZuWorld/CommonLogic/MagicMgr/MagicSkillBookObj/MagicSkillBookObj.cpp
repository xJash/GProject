
#include "MagicSkillBookObj.h"

#include "../MagicMsgObj.h"
#include "../MagicMgr.h"
#include "../MagicAttribute/MagicAttribute.h"
 
  
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "../../../Common/SMLib/LibList/LibList.h"
#include "../../../Common/Bullet/Bullet.h"
#include "Char\CharManager\CharManager.h"

#include "../../../Client/client.h"
extern cltCommonLogic* pclClient;
CMagicSkillBookObj::CMagicSkillBookObj( CMagicMgr *pMagicMgr ) : CMagicBaseObj( pMagicMgr )
{
	m_pMagicInfo = new stMagicInfo();


	Initialize();
}

CMagicSkillBookObj::~CMagicSkillBookObj()
{
	Destroy();
}

void CMagicSkillBookObj::Initialize()
{
	memset( m_pMagicInfo, 0, sizeof( stMagicInfo ) );
	m_si32AddDamage = 0;
	m_si32TotalDamage = 0;
	return;
}

void CMagicSkillBookObj::Destroy()
{
	if ( m_pMagicInfo )
	{
		delete m_pMagicInfo;
		m_pMagicInfo = NULL;
	}

	return;
}

bool CMagicSkillBookObj::SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique )
{
	SI32 charunique = pstMagicInfo->sHeader.si32FromID;
	if ( charunique <1 )		return false;

	// KIND�� �����Ѵ�.
	SetKind( pstMagicInfo->sHeader.si32MagicKind );

	// MAGIC INFO�� �����Ѵ�.
	memcpy( m_pMagicInfo, pstMagicInfo, sizeof( stMagicInfo ) );

	m_pclMap = pclMap;
	m_si32AddDamage = si32AddDamage;

	// MagicAttribute�� ���� Magic�� �����Ѵ�.
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


	//---------------------------------
	// �´� ����� ���̵� ���Ѵ�. 
	//---------------------------------
	SI32 ToID	= pclClient->pclCM->GetIDFromCharUnique( pstMagicInfo->sHeader.si32ToID );
	if ( ToID < 1 ) return false;
	if( pclClient->pclCM->IsValidID( ToID ) == FALSE) return false;

	//--------------------------------
	// �ǰ� ����Ʈ�� ���Ѵ�. 
	//--------------------------------
	pclClient->pclCM->CR[ ToID ]->GetBottomPoint(&m_clDotHitPos);
	m_pclMap = pclClient->pclCM->CR[ ToID ]->pclMap;



	m_si32TotalDamage = 0;
	SI32 siMinDamage  = 0, siMaxDamage  = 0;
	if(pclClient->pclMagicManager->GetMinMaxDamage(pstMagicInfo, m_si32AddDamage, si32SkillLevel, siMinDamage, siMaxDamage, siOrganUnique)==false)
	{
		return false;
	}
	pclClient->pclMagicManager->CalculateDamage(siMinDamage, siMaxDamage, m_si32TotalDamage);

	switch( pstMagicInfo->sHeader.si32MagicKind )
	{
	case MAGIC_SKILL_BOOK_ICERAIN:	SetMagicSpr(GIMG_MAGIC_SKILL_BOOK_ICERAIN);	break;
	case MAGIC_SKILL_BOOK_CRASH:	SetMagicSpr(GIMG_MAGIC_SKILL_BOOK_CRASH);	break;
	case MAGIC_SKILL_BOOK_TORNADO:	SetMagicSpr(GIMG_MAGIC_SKILL_BOOK_TORNADO);	break;
	}	

	return true;
}

// ���� ���� �Ұ�
bool CMagicSkillBookObj::Action()
{	
	if ( CMagicBaseObj::Action() )
	{
		return true;
	}	

	//--------------------------------------------------------
	//--------------------- ����ϴ� �� ��
	// FromID ��� ���ؼ�.
	SI32 charunique = m_pMagicInfo->sHeader.si32FromID;
	if ( charunique < 1 )	return false;

	SI32 Fromid	= pclClient->pclCM->GetIDFromCharUnique(charunique);
	if ( Fromid < 1 )		return false;

	if(pclClient->pclCM->IsValidID(Fromid) == false)	return false;

	// FromID Ÿ�� ��ǥ ���ϱ�
	SI32 XPos = pclClient->pclCM->CR[Fromid]->GetX();		// ĳ���� X Ÿ�� ��ǥ
	SI32 YPos = pclClient->pclCM->CR[Fromid]->GetY();		// ĳ���� Y Ÿ�� ��ǥ

	cltPos clTileStartPos( XPos, YPos );

	// Dot ������ ��� ��ǥ
	SI32 StartDotXPos, StartDotYPos;
	pclClient->pclCM->CR[ Fromid ]->DecideAttackPoint( 0, StartDotXPos, StartDotYPos );
	cltPos	clDotStartPos( StartDotXPos, StartDotYPos );
	//---------------------------------------------------------


	//---------------------------------------------------------
	//------------------------ Ÿ���� �Ǵ� ��
	//
	charunique = m_pMagicInfo->sHeader.si32ToID;
	if ( charunique < 1 )	return false;
	SI32 Toid = pclClient->pclCM->GetIDFromCharUnique(charunique);
	if ( Toid < 1 )			return false;

	if(pclClient->pclCM->IsValidID(Toid) == false)	return false;

	XPos = pclClient->pclCM->CR[Toid]->GetX();		// ĳ���� X Ÿ�� ��ǥ
	YPos = pclClient->pclCM->CR[Toid]->GetY();		// ĳ���� Y Ÿ�� ��ǥ

	cltCharPos		clPos;
	clPos.Set(&pclClient->pclCM->CR[ Toid ]->pclCI->clBI.clPos);		// ĳ���� ���� Fromid �� �������� �´� ���� ������ ���� ������ ������ �޾ƾ� �ϴµ�, �߰��� �ٸ� ������ �̵��ϴ� ��찡 ���� �� �����Ƿ�...

	cltAttackTarget clTarget;
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SI32 hitRate	= pclClient->pclCM->CR[Fromid]->clPB.GetHitRate( pclClient->pclCM->CR[Toid], pclClient->pclCM->CR[Fromid], true );
		SI32 dodgeRate	= pclClient->pclCM->CR[Toid]->clPB.GetDodgeRate( pclClient->pclCM->CR[Fromid], pclClient->pclCM->CR[Toid], true );

		clTarget.Set( Toid, &clPos, hitRate ,dodgeRate );		// ��ǥ�� ���� ����	
	}
	else
	{
		if(pclClient->siEnablePVP == 1)
		{
			if( IsPC(Fromid) )
			{
				// ����̸� ��ø�� ����ް� �Ѵ�.
				SI32 hitRate = pclClient->pclCM->CR[Fromid]->clPB.GetHitRate( pclClient->pclCM->CR[Toid], pclClient->pclCM->CR[Fromid], true );
				clTarget.Set( Toid, &clPos, hitRate,0 );		// ��ǥ�� ���� ����	
			}
			else
				clTarget.Set( Toid, &clPos, 100,0 );		// ��ǥ�� ���� ����
		}
		else
			clTarget.Set( Toid, &clPos, 100,0 );		// ��ǥ�� ���� ����
	}


	// Dot ������ ��� ��ǥ
	SI32 TargetDotXPos, TargetDotYPos;
	pclClient->pclCM->CR[ Toid ]->DecideAttackPoint( 0, TargetDotXPos, TargetDotYPos );
	cltPos	clDotTargetPos( TargetDotXPos, TargetDotYPos );
	//---------------------------------------------------------	

	//---------------------------------------------------------	
	// �Ѿ� ��üó�� ������
	//if(m_si32TotalDamage==0) return false; 

	CMagicAttribute* pMagicAtt =  pclClient->pclMagicManager->GetMagicAttributePtr() ;
	if ( pMagicAtt == NULL ) return false ;

	SI32 group = pMagicAtt->GetMagicGroup(m_pMagicInfo->sHeader.si32MagicKind) ;

	switch(group)
	{
	case MAGIC_GROUP_SKILL_BOOK_ICERAIN:	
		{
			if ( pclClient->GameMode != GAMEMODE_SERVER ) return false;	//���⼭ false�� �Ѿ�� �ؿ� Draw() �Լ��� ȣ��ȴ�
			
			SetDamage( m_si32TotalDamage );
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_CRASH:
		{
			if ( pclClient->GameMode != GAMEMODE_SERVER ) return false;

			SetDamage( m_si32TotalDamage );
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_TORNADO:
		{
			if ( pclClient->GameMode != GAMEMODE_SERVER ) return false;

			SetDamage( m_si32TotalDamage );
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_FLAMEBUSTER:
		{
			pclClient->pclBulletManager->SetBullet(	  m_pclMap, BULLETKIND_FLAMEBUSTER, GetKind()
				, Fromid
				, m_si32TotalDamage		// Damage
				, &clTileStartPos		// ��� Tile Pos
				, &clDotStartPos		// ��� Dot Pos
				, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
				, &clDotTargetPos		// �´� ���� dot pos
				);
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_FLAMEWHIRL:
		{
			pclClient->pclBulletManager->SetBullet(	  m_pclMap, BULLETKIND_FLAMEWHIRL, GetKind()
				, Fromid
				, m_si32TotalDamage		// Damage
				, &clTileStartPos		// ��� Tile Pos
				, &clDotStartPos		// ��� Dot Pos
				, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
				, &clDotTargetPos		// �´� ���� dot pos
				);
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_WETFOG:
		{
			pclClient->pclBulletManager->SetBullet(	  m_pclMap, BULLETKIND_WETFOG, GetKind()
				, Fromid
				, m_si32TotalDamage		// Damage
				, &clTileStartPos		// ��� Tile Pos
				, &clDotStartPos		// ��� Dot Pos
				, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
				, &clDotTargetPos		// �´� ���� dot pos
				);
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_SLING:
		{
			pclClient->pclBulletManager->SetBullet(	  m_pclMap, BULLETKIND_SLING, GetKind()
				, Fromid
				, m_si32TotalDamage		// Damage
				, &clTileStartPos		// ��� Tile Pos
				, &clDotStartPos		// ��� Dot Pos
				, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
				, &clDotTargetPos		// �´� ���� dot pos
				);
		}
		break;
	case MAGIC_GROUP_SKILL_BOOK_WINDCUTER:
		{
			pclClient->pclBulletManager->SetBullet(	  m_pclMap, BULLETKIND_WINDCUTER, GetKind()
				, Fromid
				, m_si32TotalDamage		// Damage
				, &clTileStartPos		// ��� Tile Pos
				, &clDotStartPos		// ��� Dot Pos
				, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
				, &clDotTargetPos		// �´� ���� dot pos
				);
		}
		break;

	default: return false ;
	}

	return true;			// �Ѿ� ��ü�� �Ǿ ������ �����Ƿ�..  ���⼭ true�� �Ѿ�� �ؿ� Draw() �Լ��� ȣ����� �ʴ´�.
}

void CMagicSkillBookObj::Draw( )
{	
	if ( GetStatus() != MAGIC_PLAY_STATUS )
	{
		return;
	}

	//--------------------------------------
	// ȭ�� ��¿� ��ǥ�� ��ȯ�Ѵ�. 
	//--------------------------------------
	SHORT screenx=0, screeny=0;
	cltMapClient* pclmap = (cltMapClient*)m_pclMap;
	pclmap->TransFromRealDotToScreenDot(m_clDotHitPos.siX, m_clDotHitPos.siY, screenx, screeny);


	m_si32DrawXPos = screenx - GetMagicSpr()->GetXSize()/2;
	m_si32DrawYPos = screeny - GetMagicSpr()->GetYSize()/2 - 60; 


	GP.PutSprScreen(GetMagicSpr(), m_si32DrawXPos, m_si32DrawYPos, GetCurrentFrame() ); 
	return;
}


// Push
bool CMagicSkillBookObj::Push( BYTE *pData, SI32 si32Size )
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

void CMagicSkillBookObj::SetDamage( SI32 si32Damage )
{
	stMagicMsgDamage sMagicMsgDamage;

	sMagicMsgDamage.sMagicMsgHeader.si16MsgSize		= sizeof( stMagicMsgDamage );
	sMagicMsgDamage.sMagicMsgHeader.si32MagicKind	= GetKind();
	sMagicMsgDamage.sMagicMsgHeader.si32MsgKind		= MAGIC_DAMAGE;

	sMagicMsgDamage.si32FromID = m_pMagicInfo->sHeader.si32FromID;
	sMagicMsgDamage.si32ToID   = m_pMagicInfo->sHeader.si32ToID;

	sMagicMsgDamage.si32Damage = si32Damage;

	Push( (BYTE*) &sMagicMsgDamage, sMagicMsgDamage.sMagicMsgHeader.si16MsgSize );	

	return;
}