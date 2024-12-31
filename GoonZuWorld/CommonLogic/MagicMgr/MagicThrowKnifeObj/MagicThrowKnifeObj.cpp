#include "MagicThrowKnifeObj.h"

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

CMagicThrowKnifeObj::CMagicThrowKnifeObj( CMagicMgr *pMagicMgr ) : CMagicBaseObj( pMagicMgr )
{
	m_pMagicInfo = new stMagicInfo();

	Initialize();
}

CMagicThrowKnifeObj::~CMagicThrowKnifeObj()
{
	Destroy();
}

void CMagicThrowKnifeObj::Initialize()
{
	memset( m_pMagicInfo, 0, sizeof( stMagicInfo ) );
	m_si32AddDamage = 0;
	m_si32TotalDamage  = 0;

	m_siMissileCount = 0;
	m_siMissileDealy = 0;

	return;
}

void CMagicThrowKnifeObj::Destroy()
{
	if ( m_pMagicInfo )
	{
		delete m_pMagicInfo;
		m_pMagicInfo = NULL;
	}

	return;
}

bool CMagicThrowKnifeObj::SetMagic( stMagicInfo *pstMagicInfo, SI32 si32AddDamage, cltMapCommon *pclMap, SI32 si32SkillLevel, SI32 siOrganUnique )
{

	SI32 charunique = pstMagicInfo->sHeader.si32FromID;
	if ( charunique <1 )	return false;
	
	// KIND�� �����Ѵ�.
	SetKind(pstMagicInfo->sHeader.si32MagicKind);

	memcpy( m_pMagicInfo, pstMagicInfo, sizeof( stMagicInfo ) );
	m_pclMap = pclMap;
	m_si32AddDamage = si32AddDamage;

	stMagicAttributeData *pMagicAttributeData = GetMagicAttributePtr();
	SI32 MinSkillLevel = pMagicAttributeData->si16MagicSkillLevel;

	if ( IsNPC( charunique )|| IsInstanceNPC(charunique) )
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

	m_siMissileCount = 0;
	m_siMissileDealy = 0;	
	return true;
}

// ���� ���� �Ұ�
bool CMagicThrowKnifeObj::Action()
{	
	if ( CMagicBaseObj::Action() )
	{
		return true;
	}	

	//--------------------------------------------------------
	//--------------------- ����ϴ� �� ��
	// FromID ��� ���ؼ�.
	SI32 charunique = m_pMagicInfo->sHeader.si32FromID;
	if ( charunique < 1 )
		return false;
	SI32 Fromid			= pclClient->pclCM->GetIDFromCharUnique(charunique);
	if ( Fromid < 1 )
		return false;

	if(pclClient->pclCM->IsValidID(Fromid) == false)
		return false;


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
	if ( charunique < 1 )
		return false;
	SI32 Toid  = pclClient->pclCM->GetIDFromCharUnique(charunique);
	if ( Toid < 1 )
		return false;
	
	if(pclClient->pclCM->IsValidID(Toid) == false)
		return false;


	XPos = pclClient->pclCM->CR[Toid]->GetX();		// ĳ���� X Ÿ�� ��ǥ
	YPos = pclClient->pclCM->CR[Toid]->GetY();		// ĳ���� Y Ÿ�� ��ǥ

	
	cltCharPos		clPos;
	clPos.Set(&pclClient->pclCM->CR[ Fromid ]->pclCI->clBI.clPos);		// ĳ���� ���� Fromid �� �������� �´� ���� ������ ���� ������ ������ �޾ƾ� �ϴµ�, �߰��� �ٸ� ������ �̵��ϴ� ��찡 ���� �� �����Ƿ�...

	cltAttackTarget clTarget;
	// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
	//if( pclClient->IsWhereServiceArea(ConstSwitch_PVP) )
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SI32 hitRate = pclClient->pclCM->CR[Fromid]->clPB.GetHitRate( pclClient->pclCM->CR[Toid], pclClient->pclCM->CR[Fromid], true );
		SI32 dodgeRate = pclClient->pclCM->CR[Toid]->clPB.GetDodgeRate( pclClient->pclCM->CR[Fromid], pclClient->pclCM->CR[Toid], true );

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
				clTarget.Set( Toid, &clPos, 100 ,0);		// ��ǥ�� ���� ����

		}
		else
			clTarget.Set( Toid, &clPos, 100 ,0);		// ��ǥ�� ���� ����
	}

	// Dot ������ ��� ��ǥ
	SI32 TargetDotXPos, TargetDotYPos;
	pclClient->pclCM->CR[ Toid ]->DecideAttackPoint( 0, TargetDotXPos, TargetDotYPos );
	cltPos	clDotTargetPos( TargetDotXPos, TargetDotYPos );

	//---------------------------------------------------------	
	

	//---------------------------------------------------------	
	CMagicAttribute* pMagicAtt =  pclClient->pclMagicManager->GetMagicAttributePtr() ;
	if ( pMagicAtt == NULL ) return false ;
	SI32 group = pMagicAtt->GetMagicGroup(m_pMagicInfo->sHeader.si32MagicKind) ;

	switch(group)
	{
	case MAGIC_GROUP_THROWKNIFE:
		{
			// �Ѿ� ��üó�� ������
			if(m_siMissileCount == 0)
			{
				pclClient->pclBulletManager->SetBullet( m_pclMap, BULLETKIND_MAGICTHROWKNIFE_RIGHT, GetKind()
					, Fromid
					, m_si32TotalDamage		// Damage
					, &clTileStartPos		// ��� Tile Pos
					, &clDotStartPos		// ��� Dot Pos
					, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
					, &clDotTargetPos		// �´� ���� dot pos
					);

				m_siMissileCount++;
				m_siMissileDealy=0;
			}
			else if(m_siMissileCount == 1 && m_siMissileDealy >= 5)
			{

				// �ణ Delay�� �ְ� �߻��Ѵ�.
				pclClient->pclBulletManager->SetBullet( m_pclMap, BULLETKIND_MAGICTHROWKNIFE_LEFT, GetKind()
					, Fromid
					, m_si32TotalDamage		// Damage
					, &clTileStartPos		// ��� Tile Pos
					, &clDotStartPos		// ��� Dot Pos
					, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
					, &clDotTargetPos		// �´� ���� dot pos
					);
				m_siMissileCount++;
				m_siMissileDealy=0;
			}
		}
		break;
	case MAGIC_GROUP_NORTHWIND:
		{
			// �Ѿ� ��üó�� ������
			if(m_siMissileCount == 0)
			{
				pclClient->pclBulletManager->SetBullet( m_pclMap, BULLETKIND_NORTHWIND, GetKind()
					, Fromid
					, m_si32TotalDamage		// Damage
					, &clTileStartPos		// ��� Tile Pos
					, &clDotStartPos		// ��� Dot Pos
					, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
					, &clDotTargetPos		// �´� ���� dot pos
					);

				m_siMissileCount++;
				m_siMissileDealy=0;
			}
			else if(m_siMissileCount == 1 && m_siMissileDealy >= 5)
			{

				// �ణ Delay�� �ְ� �߻��Ѵ�.
				pclClient->pclBulletManager->SetBullet( m_pclMap, BULLETKIND_NORTHWIND, GetKind()
					, Fromid
					, m_si32TotalDamage		// Damage
					, &clTileStartPos		// ��� Tile Pos
					, &clDotStartPos		// ��� Dot Pos
					, &clTarget				// �´� ���� ĳ���Ϳ� Ÿ�� ��ǥ
					, &clDotTargetPos		// �´� ���� dot pos
					);
				m_siMissileCount++;
				m_siMissileDealy=0;
			}
		}
		break;
	default: return false ;
	}

	m_siMissileDealy++;
	if(m_siMissileCount == 2) return true;	// �Ѿ� ��ü�� �Ǿ ������ �����Ƿ�..

	return false;			
}

void CMagicThrowKnifeObj::Draw( )
{	
	if ( GetStatus() != MAGIC_PLAY_STATUS )
	{
		return;
	}

	return;
}


// Push
bool CMagicThrowKnifeObj::Push( BYTE *pData, SI32 si32Size )
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


