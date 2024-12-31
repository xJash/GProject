//-----------------------------------------------
//  ����. 
//-----------------------------------------------

#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"
#include "..\..\Server\Server.h"

#include "..\..\Client\Music\Music.h"
#include "..\..\Client\InterfaceMgr\DialogController.h"

#include "../../Client/ninterface/npartydlg/NPartyDlg.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"
#include "Bullet\Bullet.h"
#include "Util\Util.h"
#include "..\..\Order\Order.h"
#include "..\..\..\CommonLogic\MagicMgr\MagicMgr.h"
#include "..\..\..\CommonLogic\MagicMgr\MagicAttribute\MagicAttribute.h"
#include "..\..\Common\Skill\Skill-Manager.h"
#include "..\..\Common\MainFunction.h"
#include "..\..\Common\Event\MofuMofu\MofuMofu.h"
#include "../../common/PartyMgr/PartyMgr.h"



//---------------------------
// CommonLogic
//---------------------------
#include "..\..\commonLogic\MsgType-Person.h"
#include "../../CommonLogic/MsgType-System.h"
#include "../../CommonLogic/MsgType-Item.h"
#include "../../CommonLogic/KoinoboryFamily/KoinoboryFamily.h"
#include "../../CommonLogic/MsgRval-Define.h"


extern cltCommonLogic* pclClient;

// id�� ���� �ּ� �����ȿ� �ִ��� Ȯ���Ѵ�. 
BOOL cltCharCommon::IsInMinRange(SHORT id, SHORT minrange)
{
	if( pclCM->IsValidID(id) == false )		return FALSE;

	if(max( TABS(GetX() - pclCM->CR[id]->GetX()), TABS(GetY()- pclCM->CR[id]->GetY()) )<=minrange)return TRUE;

	return FALSE;
}


// ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
BOOL cltCharCommon::CanAttack(SI32 id, bool pvpflag )
{
	if( pclCM->IsValidID(id) == false )		return FALSE;

	cltCharPos clpos( pclCM->CR[id]->GetMapIndex(), pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY() );
	cltAttackTarget clTarget( id, &clpos, 0, 0,pvpflag );

	return CanAttack(&clTarget);
}

// PC vs !PC ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
bool cltCharCommon::IsEnemyPCvsNOTPC(SI32 myid, SI32 enemyid)
{
	//=================================================================
	// ���� �ֱ� 
	//=================================================================
	// ��밡 ���ۿֱ��� ���� 30�̻��� ���ݺҰ�. 
	//if( pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_JAPANPORTERSOL")) && 
	//	pclCM->CR[myid]->pclCI->clIP.GetLevel() > 30)	return false;

	// ���� ���ۿֱ��� ��� ���� 30�̻��� ���ݺҰ�. 
	//if( pclCM->CR[myid]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_JAPANPORTERSOL")) && 
	//	pclCM->CR[enemyid]->pclCI->clIP.GetLevel() > 30)return false;

	//=================================================================
	// ����������
	//=================================================================
	// ��밡 �����������̸� ���� 50�̻��� ���ݺҰ�. 
	//if( pclCM->CR[enemyid]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_WESTPATROLSOL")) && 
	//	pclCM->CR[myid]->pclCI->clIP.GetLevel() > 50)	return false;

	// ���� �����������̸� ��� ���� 50�̻��� ���ݺҰ�. 
	//if( pclCM->CR[myid]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_WESTPATROLSOL")) && 
	//	pclCM->CR[enemyid]->pclCI->clIP.GetLevel() > 50)return false;


	return false;
}

	
// id�� ���� ���ΰ� ?
bool cltCharCommon::IsEnemy(SI32 id)
{
	SI32 siMyID		= GetID();
	SI32 siEnemyID	= id;

	//=================================================================
	// �⺻���� ���ݰ��ɼ� �˻� 
	//=================================================================
	if(GetID() == id)return false;
	if(pclClient->GameMode == GAMEMODE_SERVER)	{	if(pclCM->IsValidID(siMyID) == false)		return false;	}
	else										{	if(pclCM->IsValidID(siMyID) == false)		return false;	}
	if(pclCM->CR[siMyID]->pclKI->IsAtb(ATB_ATTACK) == false)									return false;
	if(pclClient->GameMode == GAMEMODE_SERVER)	{	if(pclCM->IsValidID(siEnemyID) == false)	return false;	}
	else										{	if(pclCM->IsValidID(siEnemyID) == false)	return false;	}
	if(pclCM->CR[siEnemyID]->pclKI->IsAtb(ATB_ATTACK) == false)									return false;

	//--��Ʋ�ξ��ϰ��� ������ ������ �Ǵ��ؼ� �����Ѵ�
	if( IsPC(siMyID) && IsPC(siEnemyID))
	{
		if ( pclCM->CR[siMyID]->GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM ||  pclCM->CR[siMyID]->GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM  )
		{
			if ( pclCM->CR[siEnemyID]->GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM ||  pclCM->CR[siEnemyID]->GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM  )
			{
				return true	;
			}
		}
	}

	// ������ ���� �ִ� ����� ���� ������ �����Ҽ� ����.
	if(pclCM->CR[siEnemyID]->clInnerStatus.IsStatus(INNERSTATUS_PRISON)	== true)	return false;
	if(pclCM->CR[siMyID]->clInnerStatus.IsStatus(INNERSTATUS_PRISON)	== true)	return false;
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[siEnemyID]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[siEnemyID]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return false ;
	}
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[siMyID]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[siMyID]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return false ;
	}

	// [����] ��ȣ����_090525 : ��ȣ������ ���� ������, ������ �ʴ´�
	if ( (IDENTITY_SOULGUARD == pclCM->CR[siMyID]->clIdentity.siIdentity)
		|| (IDENTITY_SOULGUARD == pclCM->CR[siEnemyID]->clIdentity.siIdentity) )
	{
		return false;
	}
	
	//�����̸鼭 ���� �̺�Ʈ - ���� ���ݿ��� ������� ���Ͷ��.
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if(IsPC(siMyID))
		{
			//�����̸鼭 ���� �̺�Ʈ - ���� ���ݿ��� ������� ���Ͷ��.
			if(IsNPC( siEnemyID ) && pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_MONSTER_ATTACK_EVENT )
			{
				// ���� ������ �ƴϸ� �� �̺�Ʈ ���͸� �������� ���Ѵ�.
				if(pclClient->pclMonsterAttackEvent->GetEventVillageUnique() != pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage)
				{
					return false;
				}
			}
		}
	}
	else
	{
		if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_MONSTER_ATTACK_EVENT )
		{
			// ���� ������ �ƴϸ� �� �̺�Ʈ ���͸� �������� ���Ѵ�.
			if(pclClient->pclMonsterAttackEvent->GetEventVillageUnique() != pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage)
			{
				return false;
			}
		}
	}
	//�����̸鼭 ���� ���ϱ� �̺�Ʈ ���͸� ���� ���Ѵ�.
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if(IsPC(siMyID))
		{
			//�����̸鼭 ���� �̺�Ʈ - ���� ���ݿ��� ������� ���Ͷ��.
			if(IsNPC( siEnemyID ) && pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT )
			{
				return false;			
			}
		}

		if(IsNPC(siMyID))
		{
			// �̺�Ʈ ���͵��� ���� ���� ���Ѵ�.
			if(pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT)
			{
				SI32 siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();
				if ( siParentEnemyID > 0 )	return	 false	;
			}
		}
	}
	else
	{
		if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT )
		{
			return false;
		}
		if(IsNPC(siMyID))
		{
			// �̺�Ʈ ���͵��� ���� ���� ���Ѵ�.
			if(pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT)
			{
				SI32  siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();
				if ( siParentEnemyID > 0 )	return	 false	;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// [����] ���Һ� : �����̸鼭 ���Һ� �̺�Ʈ ���͸� ���� ���Ѵ�.
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if(IsNPC(siMyID))
		{
			// �̺�Ʈ ���͵��� ���� ���� ���Ѵ�.
			SI08 siMydentity = pclCM->CR[siMyID]->clIdentity.siIdentity;
			if ( siMydentity == IDENTITY_BOKBULBOK_EVENTMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_ITEMMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_KEYMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
			{
				SI32 siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();
				if ( siParentEnemyID > 0 )	return	 false;
			}

			// �굵 �̺�Ʈ ���͵��� ���� ���ϰ�.
			SI32 siParentEnemyID = pclClient->pclCM->CR[siMyID]->GetSummonParentID();

			if ( 0 < siParentEnemyID )
			{
				SI08 siEnemyIdentity = pclCM->CR[siEnemyID]->clIdentity.siIdentity;
				if ( siEnemyIdentity == IDENTITY_BOKBULBOK_EVENTMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_ITEMMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_KEYMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
				{
					return false;
				}
			}
		}
	}
	else
	{
		if(IsNPC(siMyID))
		{
			// �̺�Ʈ ���͵��� ���� ���� ���Ѵ�.
			SI08 siMydentity = pclCM->CR[siMyID]->clIdentity.siIdentity;
			if ( siMydentity == IDENTITY_BOKBULBOK_EVENTMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_ITEMMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_KEYMONSTER ||
				siMydentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
			{
				SI32 siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();
				if ( siParentEnemyID > 0 )	return	 false;
			}

			// �굵 �̺�Ʈ ���͵��� ���� ���ϰ�.
			SI32 siParentEnemyID = pclClient->pclCM->CR[siMyID]->GetSummonParentID();

			if ( 0 < siParentEnemyID )
			{
				SI08 siEnemyIdentity = pclCM->CR[siEnemyID]->clIdentity.siIdentity;
				if ( siEnemyIdentity == IDENTITY_BOKBULBOK_EVENTMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_ITEMMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_KEYMONSTER ||
					siEnemyIdentity == IDENTITY_BOKBULBOK_ONEKILLMONSTER )
				{
					return false;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	

	// ����Ʈ ���� ���� �϶��� ��ȯ�� ����� ��ȯ�� ����� �����ִ� ��Ƽ���� ĥ���ִ�
	if ( GAMEMODE_SERVER ==  pclClient->GameMode )
	{
		if ( IsPC(siMyID) && IsNPC(siEnemyID) )
		{
			if ( IDENTITY_QUEST == pclCM->CR[siEnemyID]->clIdentity.siIdentity )
			{
				SI32 siMyPersonID		= pclCM->CR[siMyID]->pclCI->GetPersonID();
				SI32 siDestPersonID		= pclCM->CR[siEnemyID]->clIdentity.clQuestInfo.m_siEnemyPersonID;
				if ( siMyPersonID != siDestPersonID )
				{
					if ( false == pclClient->pclPartyMgr->IsPartyMember(siDestPersonID, pclCM->CR[siMyID]->siPartyIndex) )
					{
						return false;
					}
				}
			}
		}
	}
	else if ( GAMEMODE_CLIENT ==  pclClient->GameMode )
	{
		if ( IDENTITY_QUEST == pclCM->CR[siEnemyID]->clIdentity.siIdentity )
		{
			SI32 siMyPersonID		= pclCM->CR[siMyID]->pclCI->GetPersonID();
			SI32 siDestPersonID		= pclCM->CR[siEnemyID]->clIdentity.clQuestInfo.m_siEnemyPersonID;

			if ( siMyPersonID != siDestPersonID )
			{
				cltClient* pclclient = (cltClient*)pclClient;
				if ( NULL == pclclient )
				{
					return false;
				}

				if ( NULL == pclclient->m_pDialog[NPARTY_DLG] )
				{
					return false;
				}

				SI32 siFindCharID = pclCM->CR[siEnemyID]->clIdentity.clQuestInfo.m_siEnemyCharID;
				if ( false == ((CNPartyDlg*)pclclient->m_pDialog[NPARTY_DLG])->IsPartyMember( siFindCharID ) )
				{
					return false;
				}
			}
		}
	}

	// �ͼ����� ���ʹ� �ҷ��� ĳ���͸� ĥ �� �ִ�
	if ( IDENTITY_SOULBOUND == pclCM->CR[siEnemyID]->clIdentity.siIdentity )
	{
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			SI32 siMyPersonID		= pclCM->CR[siMyID]->pclCI->GetPersonID();
			SI32 siDestPersonID		= pclCM->CR[siEnemyID]->clIdentity.clSoulBound.m_siPersonID;

			if ( siMyPersonID != siDestPersonID )
			{
				return false;
			}
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			// Ŭ���̾�Ʈ �϶��� ���� �˻��Ѵ�
			if ( 1 == siMyID )
			{
				SI32 siMyPersonID		= pclCM->CR[siMyID]->pclCI->GetPersonID();
				SI32 siDestPersonID		= pclCM->CR[siEnemyID]->clIdentity.clSoulBound.m_siPersonID;

				if ( siMyPersonID != siDestPersonID )
				{
					return false;
				}
			}
		}

	}

	// �����ũ �̺�Ʈ -> [����] �Ʒ� ���ѻ����� ������
	/*
	if( IsPC( pclCM->CR[siMyID]->GetCharUnique() ) )
	{
		if( IsNPC( pclCM->CR[siEnemyID]->GetCharUnique() ) )
		{
			SI32 siAttackerLevel = pclCM->CR[siMyID]->pclCI->clIP.GetLevel();
			if( pclCM->CR[siEnemyID]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYRED") ) )
			{
				if( siAttackerLevel < 50 || siAttackerLevel > 100 )		return false;
			}
			else if( pclCM->CR[siEnemyID]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYBLUE") ) )
			{
				if( siAttackerLevel < 30 || siAttackerLevel > 80 )		return false;
			}
			else if( pclCM->CR[siEnemyID]->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYYELLOW") ) )
			{
				if( siAttackerLevel < 1 || siAttackerLevel > 50 )		return false;
			}
		}
	}
	*/

	// ���ĸ��� �̺�Ʈ ������ �ִ°�� - Ư���� ��츸 ������ �����ϵ��� �����ȴ�.
	if ( pclCM->CR[siMyID]->GetMapIndex()		== MAPINDEX_MOFUMOFULAND &&
		 pclCM->CR[siEnemyID]->GetMapIndex()	== MAPINDEX_MOFUMOFULAND )
	{
		SI32 siMofuMofuEventColl = BLOCK_EVENT4 | BLOCK_EVENT5 | BLOCK_EVENT6;
		cltMapCommon* pclmymap		= pclClient->pclMapManager->GetMapPointer(pclCM->CR[siMyID]->GetMapIndex());
		cltMapCommon* pclenemymap	= pclClient->pclMapManager->GetMapPointer(pclCM->CR[siEnemyID]->GetMapIndex());
		if(pclmymap != NULL && pclenemymap != NULL)
		{
			SI32 siMyColl		= pclmymap->CalcCollInfo(pclCM->CR[siMyID]->GetX(), pclCM->CR[siMyID]->GetY());
			SI32 siEnemyColl	= pclmymap->CalcCollInfo(pclCM->CR[siEnemyID]->GetX(), pclCM->CR[siEnemyID]->GetY());

			siMyColl	= siMyColl		& siMofuMofuEventColl;
			siEnemyColl = siEnemyColl	& siMofuMofuEventColl;

			// �ʵ峻�� �ְ� ���� �ʵ忡 �����Ѵٸ� ���� ����
			if( (siMyColl != 0 && siEnemyColl != 0) &&
				(siMyColl == siEnemyColl))
			{ 
				// ���� ���ĸ��� �̺�Ʈ ���͸� CanAttack�� 0�̸� ������ �� ����.
				if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_MOFUMOFUEVENT && pclCM->CR[siEnemyID]->clIdentity.clMofoMofuEvent.siCanAttack == 0)
					return false;

				if( pclClient->GameMode == GAMEMODE_SERVER )
				{
					// PC�� ��ȯ���� ������ ���� �ʴ´�.
					if( (pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON && IsPC(siEnemyID)) ||
						(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON && IsPC(siMyID)) )
						return false;

					cltServer* pclserver = (cltServer*)pclClient;
					SI32 siCurrentVillage = pclserver->pclMofuMofuEvent->GetCurrentEventVillage();

					// �̺�Ʈ �������� ������ ���� ������??
					if(siCurrentVillage <= 0)			return false;

					// �������� ������ �ƴϸ� ������ �Ҽ� ����.
					if( (IsPC(siMyID) && pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage != siCurrentVillage) || 
						(IsPC(siEnemyID) && pclCM->CR[siEnemyID]->pclCI->clBI.siHomeVillage != siCurrentVillage) )
					{
						return false;
					}
				}
				else if( pclClient->GameMode == GAMEMODE_CLIENT )
				{
					// PC�� ��ȯ���� ������ ���� �ʴ´�.
					if( (siMyID == 1 && pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON) ||
						(siEnemyID == 1 && pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON))
						return false;

					// �������� ������ �ƴϸ� ������ �Ҽ� ����.
					cltClient* pclclient = (cltClient*)pclClient;
					SI32 siCurrentVillage = pclclient->siMofuMofuEvent_VilliageUnique;

					// �̺�Ʈ �������� ������ ���� ������??
					if(siCurrentVillage <= 0)			return false;

					// �������� ������ �ƴϸ� ������ �Ҽ� ����.
					if( (siMyID == 1 && pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage != siCurrentVillage) || 
						(siEnemyID == 1 && pclCM->CR[siEnemyID]->pclCI->clBI.siHomeVillage != siCurrentVillage) )
					{
						return false;
					}
				}
				else
					return false;

				// ���� �źг����� ������ �� ����.
				if(pclCM->CR[siMyID]->clIdentity.siIdentity == pclCM->CR[siEnemyID]->clIdentity.siIdentity)
					return false;

				return true;
			}
			else
				return false;
		}
	}

	// by LEEKH 2007.12.28 - TRANSFORM
	// ���� �ִϰ� ���� ��쿡�� ���� �ʴ´�. 
	if(pclCM->CR[siMyID]->GetKindInfo()->clCharAniManager.FindRefFromAnitype(ANITYPE_ATTACK) < 0)		
		return false;
	// Ű�޶�� ������ ������ ���� ���踦 ������ ���� ������ ���� �ʰԲ� ���ش�.
	if( ( pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_VILLAGEHUNT && pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_CASTLE )
		||  ( pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_CASTLE && pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_VILLAGEHUNT ) )
	{
		return false;
	}

	// ���� PVP ��� üũ
	SI32 siParentMyID		= 0;pclClient->pclCM->CR[ siMyID ]->GetSummonParentID();
	SI32 siParentEnemyID	= 0;pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();

	if( pclClient->GameMode == GAMEMODE_SERVER)
	{
		siParentMyID		= pclClient->pclCM->CR[ siMyID ]->GetSummonParentID();
		siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();

		if( siParentMyID	== 0 )		siParentMyID = siMyID;
		if( siParentEnemyID == 0 )		siParentEnemyID = siEnemyID;
	}
	else
	{
		if( pclClient->pclCM->CR[ siMyID ]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			siParentMyID	= pclCM->GetIDFromCharUnique(pclClient->pclCM->CR[ siMyID ]->clIdentity.clSummonInfo.siParentCharUnique);
		}
		else
		{
			siParentMyID	= siMyID;
		}

		if( pclClient->pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			siParentEnemyID	= pclCM->GetIDFromCharUnique(pclClient->pclCM->CR[siEnemyID]->clIdentity.clSummonInfo.siParentCharUnique);
		}
		else
		{
			siParentEnemyID = siEnemyID;
		}
	}
	if( siParentMyID != siParentEnemyID )		
	{
		if( pclClient->pclCM->IsValidID( siParentMyID ) )
		{
			cltCharCommon* pclMyChar = pclClient->pclCM->GetChar(siParentMyID);
			cltCharCommon* pclEnemyChar = pclClient->pclCM->GetChar(siParentEnemyID);
			if(pclMyChar == NULL)						return false	;
			if(pclEnemyChar == NULL)						return false	;

			// �����̶� ����PVP ���¶��,
			if( pclMyChar->siEnemUnique > 0 || pclEnemyChar->siEnemUnique > 0 )
			{
				if( pclMyChar->siEnemUnique == pclEnemyChar->GetCharUnique() )
					return true;
				else
					return false;
			}
			// ���°� ����� ������ Ȯ�� �Ѵ�.
			if(pclMyChar->pclCI->clBI.clGuildRank.siGuildUnitIndex > 0 )
			{
				SI32 siMyGuildUnique = pclMyChar->pclCI->clBI.clGuildRank.siGuildUnitIndex	;
				SI32 siEnemyGuildUnique = pclEnemyChar->pclCI->clBI.clGuildRank.siGuildUnitIndex	;

				SI32 siMyEnemy = pclMyChar->pclCI->clBI.clGuildRank.GetEnemyGuild()	;
				SI32 siEnemyEnemy = pclEnemyChar->pclCI->clBI.clGuildRank.GetEnemyGuild();
				if ( siMyEnemy == siEnemyGuildUnique && siEnemyEnemy== siMyGuildUnique)
				{
					return true;

				}
			}
		}			
	}
	// ��� ����ڿ� �������� �����, 
	if(pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLPC))
	{
		if(pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLNPC))
		{	
			return true;
		}
	}	
	// ��� NPC�� �������� �����, 
	if(pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLNPC))
	{
		if(pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLPC))
		{
			return true;
		}
	}
	
	// [����] ��Ʋ�ξ�
	if(pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLPC) && pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLNPC))
	{
		if(pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLPC) && pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ALLNPC))
		{
			return true;
		}
	}
	// �������� ������踦 �ٰŷ� �ϴ� ���� �����, 
	if(pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_VILLAGE))
	{
		if(pclClient->bVillageWarSwitch)
		{
			SI16 MyHomeVillage  = pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage;
			SI16 EnemyVillage   = pclCM->CR[siEnemyID]->pclCI->clBI.siHomeVillage;
			// ���� �����ּ����� ���ų� ������ ���� �ּ����� ������ ����
			if(MyHomeVillage && EnemyVillage )
			{
				// ���� �������� ������ �ƴϸ� ���� 
				if(pclClient->pclVillageManager->IsAggressiveVillage(MyHomeVillage, EnemyVillage) == TRUE)
				{
					if(	pclCM->CR[siMyID]->GetMapIndex() !=0							
					|| pclCM->CR[siMyID]->GetCurrentVillageUnique() != MyHomeVillage	
					|| pclCM->CR[siMyID]->GetCurrentVillageUnique() != EnemyVillage)
					{
						// ��밡 �ִ� ������ ���� �ּ����� ������ �ּ����� �ƴϸ� false
						if(	pclCM->CR[siEnemyID]->GetMapIndex() != 0							
						|| pclCM->CR[siEnemyID]->GetCurrentVillageUnique() != MyHomeVillage	
						|| pclCM->CR[siEnemyID]->GetCurrentVillageUnique() != EnemyVillage)
						{
							return true;
						}
					}
				}
			}
		}
	}

	// Ư�� �������� ���� ������, (��밡 �� �Ӽ��� ���� �ִٸ�,) 
	if(pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ONEVILLAGE))
	{		
		// ���� �� Ư�� �����̾�� �Ѵ�. 
		if(pclCM->CR[siMyID]->pclCI->clBI.siHomeVillage == pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.siPara1)
		{
			return true;
		}
	}
	// Ư�� �������� ���� ������, (�ڽ��� �� �Ӽ��� ���� �ִٸ�, ) 
	if(pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_ONEVILLAGE))
	{
		if( pclCM->CR[siEnemyID]->pclCI->clBI.siHomeVillage == pclCM->CR[siMyID]->clInnerStatus.clEnemyType.siPara1 )
		{
			return true;
		}
	}
	if( pclClient->GameMode == GAMEMODE_SERVER)
	{
		siParentMyID		= pclClient->pclCM->CR[ siMyID ]->GetSummonParentID();
		siParentEnemyID		= pclClient->pclCM->CR[siEnemyID]->GetSummonParentID();

		if( siParentMyID	== 0 )		siParentMyID = siMyID;
		if( siParentEnemyID == 0 )		siParentEnemyID = siEnemyID;
	}
	else
	{
		if( pclClient->pclCM->CR[ siMyID ]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			siParentMyID	= pclCM->GetIDFromCharUnique(pclClient->pclCM->CR[ siMyID ]->clIdentity.clSummonInfo.siParentCharUnique);
		}
		else
		{
			siParentMyID	= siMyID;
		}

		if( pclClient->pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
		{
			siParentEnemyID	= pclCM->GetIDFromCharUnique(pclClient->pclCM->CR[siEnemyID]->clIdentity.clSummonInfo.siParentCharUnique);
		}
		else
		{
			siParentEnemyID = siEnemyID;
		}
	}

	// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
	//if( pclClient->IsWhereServiceArea(ConstSwitch_PVP) )
	if ( pclClient->siEnablePVP == 1 )
	{
		// ��ID�� ��� Pk �ʿ����� �� �ؾ� ���ݾ�~
		if( (IsPC(siMyID)) && pclClient->pclMapManager->IsPkMap( pclCM->CR[siMyID]->GetMapIndex() ) )
			// ��� �����Ҷ�
			if( pclCM->CR[siMyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_PVP) )
			{
				if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )      
				{
				}
				else if( pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
				{
				}
				else if( (IsPC(siEnemyID)) && pclCM->CR[siEnemyID]->clInnerStatus.clEnemyType.IsType(ENEMYTYPE_PVP) )
				{
					return	true	;
				}
			}
	}


	
	//#endif
	return false;
}

// id�� ���� ���ΰ� ?
bool cltCharCommon::IsEnemyPCvsPC(SI32 id)
{
	SI32 siMyID		= GetID();
	SI32 siEnemyID	= id;

	//=================================================================
	// �⺻���� ���ݰ��ɼ� �˻� 
	//=================================================================
	if(GetID() == id)return false;
	if(pclClient->GameMode == GAMEMODE_SERVER)	{	if(pclCM->IsValidID(siMyID) == false)		return false;	}
	else										{	if(pclCM->IsValidID(siMyID) == false)		return false;	}
	if(pclCM->CR[siMyID]->pclKI->IsAtb(ATB_ATTACK) == false)									return false;
	if(pclClient->GameMode == GAMEMODE_SERVER)	{	if(pclCM->IsValidID(siEnemyID) == false)	return false;	}
	else										{	if(pclCM->IsValidID(siEnemyID) == false)	return false;	}
	if(pclCM->CR[siEnemyID]->pclKI->IsAtb(ATB_ATTACK) == false)									return false;

	// ���� pvp �Ǹ� thghks
	//if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )      return false;
	// ������ ���� �ִ� ����� ���� ������ �����Ҽ� ����.
	if(pclCM->CR[siEnemyID]->clInnerStatus.IsStatus(INNERSTATUS_PRISON)	== true)	return false;
	if(pclCM->CR[siMyID]->clInnerStatus.IsStatus(INNERSTATUS_PRISON)	== true)	return false;
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[siEnemyID]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[siEnemyID]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return false ;
	}
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[siMyID]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[siMyID]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return false ;
	}

	// PVP�� �� �� �ֳ�? pvp
	if( pclClient->pclMapManager->IsPkMap( pclCM->CR[siMyID]->GetMapIndex() ) &&	pclCM->CR[siMyID]->pclCI->clIP.GetLevel() >= 50)
	{
		if( pclClient->pclMapManager->IsPkMap( pclCM->CR[siEnemyID]->GetMapIndex() ) &&	pclCM->CR[siEnemyID]->pclCI->clIP.GetLevel() >= 50)
		{
			if(pclCM->CR[siEnemyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )      
			{
			}
			else if( pclCM->CR[siMyID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
			{
			}
			else
			{
				return true;
			}		
		}
	}

	//// �������	PVP	
	//SI32 siMyPVPCharUnique			=	pclCM->CR[siMyID]->siEnemyID	;				// ���� ������ �ִ� CHARUNIQUE
	//SI32 siEnemyPVPCharUnique		=	pclCM->CR[siEnemyID]->siEnemyID	;				// ���� ������ �ִ� CHARUNIQUE
	//
	//SI32 siEnemyPVPID				=	pclCM->CR[siEnemyID]->GetID()	;					// ���� ���� ID
	//SI32 siMyEnemyID				=	pclCM->GetIDFromCharUnique( siMyPVPCharUnique )	;	// ���� ���� ���ɸ����� ID

	//SI32 siMyParentID				=	pclCM->CR[siMyID]->GetSummonParentID() ;		// ���� PARENTID
	//SI32 siEnemyParentID			=	pclCM->CR[siEnemyID]->GetSummonParentID() ;		// ���� PARENTID	
	//SI32 siParentPVPId				=	0	;
	//SI32 siEnemyParentPVPId			=	0	;
	//SI32 siMyParentCharUnique		=	0	;
	//SI32 siEnemyParentCharUnique	=	0	;
	//// ��ȯ�� �϶��� ���ϱ� ���ؼ�
	//if ( siMyParentID > 0) 
	//{
	//	siParentPVPId				=	pclCM->CR[siMyParentID]->siEnemyID	;			// ���� PARENT�� ������ �� ID
	//	siMyParentCharUnique		=	pclCM->GetIDFromCharUnique( siMyParentID )	;	// �� �θ��� CHARUNIQUE
	//}
	//if ( siEnemyParentID >0 ) 
	//{
	//	siEnemyParentPVPId			=	pclCM->CR[siEnemyParentID]->siEnemyID	;		// ���� PARENT�� ������ �� ID
	//	siEnemyParentCharUnique	=	pclCM->GetIDFromCharUnique( siEnemyParentID )	;	// ���� �θ��� CHARUNIQUE
	//}	
	//// ���� ������, ���� ���� �� ID�� ���� �ϰ�, ���� �ɸ����� �ɸ��� ����ũ�� ���� ���� �����̵��� �ɸ��� ����ũ�� �����Ҷ�
	//if ( siMyPVPCharUnique > 0 && siEnemyPVPID == siMyEnemyID ){ return true; }
	//// ��ȯ���� ���� �ҋ� .
	//else if ( siMyParentID )  // ���� ��ȯ�� �̰� 
	//{
	//	if ( siParentPVPId > 0 ) // ���θ� �ɸ��Ͱ� �� ���̵� �־�� �Ѵ�
	//	{
	//		if( siMyParentID == siEnemyParentPVPId )	// ���� �θ� ���̵�� ���� ���ɸ��Ͱ� �����ϸ�
	//		{
	//			return true	;
	//		}
	//	}
	//}
	//else if (siEnemyParentID) // ���� �з�Ʈ ���̵� �ִ� ��ȯ���̰�
	//{
	//	if( siEnemyParentCharUnique == siMyPVPCharUnique )
	//	{
	//		//���θ����ɸ��� ����ũ�� ���� �ɸ��� ����ũ�� ������ ���̴�.
	//		return true	;
	//	}

	//}
	return false;
}

// ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
BOOL cltCharCommon::CanAttack(const cltAttackTarget* pcltarget)
{
	if(pcltarget == NULL)								return FALSE;
	
	// ȭ�鿡 �� �� ���� ĳ���Ͷ�� ������ �� ����. 
	if(pclCM->IsAlive( pcltarget->siAttackID )==FALSE)	return FALSE;

	// �ڱ� �ڽ��� ������ �� ����.
	if(pcltarget->siAttackID == siID)					return FALSE;

	// ���� ���� �Ӽ��� ������ ������ �� ����. 
	if(IsAtb(ATB_ATTACK)==FALSE)						return FALSE;

	// ���� ������ ���� �ٸ��� ������ �� ����. 
	if(GetMapIndex() != pcltarget->clPos.GetMapIndex())	return FALSE;

	// ���� ���� ���� ��ġ�� ���� ���� �ٸ��� ������ �� ����. 
	if(GetMapIndex() != pclCM->CR[ pcltarget->siAttackID ]->GetMapIndex())return FALSE;

	// PVP�� �� �� �ֳ�? -pvp �׽�Ʈ�� ���ε����� 0;;
	if( true == pcltarget->bPVPHit )
	{
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( pclClient->IsWhereServiceArea( ConstSwitch_PVP ) )
		if(pclClient->siEnablePVP == 1)
		{
			// ���� �� ���̵� ������ ������ ���ε����� üũ�� ���ؾ� �Ѵ�.
			SI32 siMyId = GetID()	;	// �����̵� �޾ƿ´�.
			SI32 siMyEnemy = pclClient->pclCM->CR[ siMyId ]->siEnemUnique ;	// �� ���̵�� �� ���̵� ã�´�.
	
			SI32 MuPvpEnemy = pclCM->GetIDFromCharUnique( siMyEnemy );		// ���� �ɸ��� ���̵� ���� personID�� ã�´�.
			SI32 siAttackID = pcltarget->siAttackID	;						// ������ ��� ID

			if ( siMyEnemy > 0 && siAttackID > 0 && MuPvpEnemy == siAttackID  ) 
			{
			}
			else if (siMyEnemy <= 0 && siAttackID <= 0  )  // �� ���̵� ������ �ʾ����� �� ���� üũ�ؼ� pvp ������ üũ
			{
				SI32 parentMap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
				if(false == pclClient->pclMapManager->IsPkMap( parentMap ) || pclCI->clIP.GetLevel() < 50  )
					return FALSE;
				parentMap = pclClient->pclMapManager->GetParentMap( pclCM->CR[pcltarget->siAttackID]->GetMapIndex() );
				if( false == pclClient->pclMapManager->IsPkMap( parentMap ) || pclCM->CR[pcltarget->siAttackID]->pclCI->clIP.GetLevel() < 50)
					return FALSE;

				if( clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
					return FALSE;

				if( pclCM->CR[pcltarget->siAttackID]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
					return FALSE;
			}
		}
	}
//#endif
	else
	{
		if(IsEnemy(pcltarget->siAttackID) == false)
			return FALSE;			
	}

	cltCharCommon* pchEnemychar = pclCM->GetChar( pcltarget->siAttackID )	;
	if(  pchEnemychar != NULL )
	{
		if(pchEnemychar->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT)	return FALSE;


	}
	
//	if(IsEnemy(pcltarget->siAttackID) == false)return FALSE;

	// �ʱ� ��ȣ ���¿� �ִ� ĳ���ʹ� ������ �� ����. 
	if(pclCM->CR[ pcltarget->siAttackID ]->GetInitProtectSwitch() == true)return FALSE;

	// Ÿ���� �ǰ� ���ٸ� ������ �� ����.
	if(pclCM->CR[pcltarget->siAttackID]->GetLife() <= 0 ) return FALSE ;
	// ���� �ǰ� ��� ������ �� ����.
	if(GetLife() <=0 ) return FALSE ;

	//[����] ���ĸ��Ĵ��� �̺�Ʈ - ���� ���ĸ��Ĵ� ���ĸ�������� ����� ������ 50���� �̻� �����Ѵ�.
	if(GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_MAMARACCOON")))
	{
		if(IsPC(pcltarget->siAttackID))
		{
			cltBufInfo * pclMyBuf = &pclCM->CR[ pcltarget->siAttackID ]->pclCI->clBI.clBufInfo;

			BOOL bMofuMofuPerfume = FALSE;

			if(pclMyBuf->IsHaveBuf(BUF_MOFUMOFU_PERFUME))		bMofuMofuPerfume = TRUE;
			if(pclCM->CR[pcltarget->siAttackID]->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE(23090))	bMofuMofuPerfume = TRUE;

			if(bMofuMofuPerfume && pclCM->CR[ pcltarget->siAttackID ]->pclCI->clIP.GetLevel() < 50)
			{
				return FALSE;
			}
		}
	}

	// ����� ĳ������ ���
	SI32 siParentID = GetSummonParentID();

	if ( IsPC(GetCharUnique()) || IsPC(siParentID) )
	{
		//[����] ���ݽ� �����̾� ���� ������ �����Ǿ��ִٸ� ���� ���Ѵ�.

		if( bPersonalShopSwitch == true && bPremiumPersonalShop == true )
		{
			return FALSE;
		}

		if( pclCM->CR[pcltarget->siAttackID]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SANTARACCOON_ZIQ")) )
		{
			if( pclCI->clIP.GetLevel() < 10 
				|| pclCI->clIP.GetLevel() > 40   )
			{
				return FALSE;
			}

		}

		//cyj ���ݽ� ȭ��, źȯ �ʿ俩��
		bool bBulletswitch = false;

		if(pclClient->GameMode == GAMEMODE_SERVER)	
		{
			bBulletswitch = true;
		}
		else
		{
			if(GetID() == 1)		// �ڱ� �ڽ��� ����̰ų�. 
			{
				bBulletswitch = true;
			}
			if(GetSummonParentID() == 1)	// �ڽ��� ��ȯ���� ��쿡, 
			{
				bBulletswitch = true;
			}
		}

		if (bBulletswitch == true)
		{
			SI16 siBulletUnique = 0;
			BOOL bUseBullet = FALSE;
			if( clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				cltKindInfo* pclki = NULL;
				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
					pclki = pclClient->pclKindInfoSet->pclSummonKI[GetKind()];
				}
				else
				{
					pclki = pclClient->pclKindInfoSet->pclKI[GetKind()];
				}

				if ( (pclki) && (pclki->siSummonEquip) )
				{
					bUseBullet = GetBulletUnique_Summon(GetSummonIndex(), &siBulletUnique);
				}
	
			}
			else
			{
				bUseBullet = GetBulletUnique_Char(&siBulletUnique);
			}

			// ����� �� �ִ� ���� ���� ��� Ŭ���̾�Ʈ�� �����޽����� ǥ���Ѵ�.
			if( bUseBullet && siBulletUnique <= 0 )
			{
				if (pclClient->GameMode == GAMEMODE_CLIENT)
				{
					cltClient *pclclient = (cltClient*)pclClient;
					TCHAR* pTitle = NULL;
					TCHAR* pText = NULL;

					// PCK : ���� Ÿ���� Ȱ�̸� ȭ���� ���ٴ� �޽�����, ���̸� �Ѿ��� ���ٴ� �޽����� �����ش�.
					if(GetAttackType() == ATTACKTYPE_BOW || GetAttackType() == ATTACKTYPE_BOW1 || GetAttackType() == ATTACKTYPE_NEW_BOW1)
					{
						pTitle = GetTxtFromMgr(836);
						pText = GetTxtFromMgr(5835);
					}
					else if (GetAttackType() == ATTACKTYPE_GUN || GetAttackType() == ATTACKTYPE_GUN1 || GetAttackType() == ATTACKTYPE_NEW_GUN1)
					{
						pTitle = GetTxtFromMgr(836);
						pText = GetTxtFromMgr(5836);
					}

					if (pclclient->m_pDialog[ NOTIFYMSG_DLG ])
					{
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
				}
				// ��ȯ�� �̸鼭 �����϶��� Ŭ���̾�Ʈ�� �ȵǴ� ������ �����ش�(��ȯ�� ������ ��� Ŭ�󿡼� ��ó���� ���ϱ� ������)
				else if ( (GAMEMODE_SERVER == pclClient->GameMode) && (IDENTITY_PERSON_SUMMON == clIdentity.siIdentity) )
				{
					cltServer*		pclServer		= (cltServer*)pclClient;
					cltCharServer*	pclParentChar	= pclCM->GetCharServer( siParentID );
					
					if ( (pclServer) && (pclParentChar) )
					{
						SI16 siProjectileType = 0;
						switch ( GetAttackType() ) 
						{
							case ATTACKTYPE_BOW:
							case ATTACKTYPE_BOW1:
							case ATTACKTYPE_NEW_BOW1:
								{
									siProjectileType = 1;
								}
								break;
							case ATTACKTYPE_GUN:
							case ATTACKTYPE_GUN1:
							case ATTACKTYPE_NEW_GUN1:
								{
									siProjectileType = 2;
								}
								break;
						}

						pclServer->SendServerResponseMsg( 0, SRVAL_SUMMON_DONOTHAVE_PROJECTILE, siProjectileType, 0, pclParentChar->GetCharUnique() );
					}
				}

				return FALSE;
			}
		}
	}

	return TRUE;
}


bool cltCharCommon::CanMagicManaDelay(SI32 magickind, SI32* preturn )
{

	//---------------------------------------------
	// ���� ������ ���� ���� ���� ���θ� �����Ѵ�. 
	stMagicAttributeData* psMagicData = pclClient->pclMagicManager->GetMagicAttribute( magickind ); 
	if( psMagicData == NULL )		return false;

	//========================================================
	// ���� �˻� 
	//========================================================
	// Mana�� ����ؾ� �Ѵ�. 
	//SKILL LEVEL�� ���� MANA �Һ� 
	SI32 kind = 0;
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))	kind = GetKind();
	CMagicAttribute *pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
	SI32 skilltype = pMagicAttributePtr->GetMagicSkillType(magickind);
	
	// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
	if( SKILL_SIKLLBOOK == skilltype && IsPC(GetID())  )
	{
		cltSkillBookMagic*	pclSkillBookMagic = pclCharSkillBookInfo->GetSkillBookMagic( GetAttackType() );	
		if( NULL == pclSkillBookMagic ) return false;
		
		skilltype = pclSkillBookMagic->GetSkillUnique();	
	}

#ifdef _SAFE_MEMORY
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( skilltype, kind, pclCI->clIP.GetLevel(), &pclCI->clCharItem.clItem[0] );
#else
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( skilltype, kind, pclCI->clIP.GetLevel(), pclCI->clCharItem.clItem );
#endif
	// Skill Level�� ���� ������� �ְ� ������ ������� �־� �����Һ��� ����Ѵ�.
	SI32 mana = pclClient->pclMagicManager->GetSpendMana( magickind, SkillLevel, GetCharUnique() );
	

	// [����] ���� ������ ���� ���.
	SI32	siSubMagickind	= 0;
	SI32 	siSubDelay 		= 0;
	if( pclClient->IsCountrySwitch(Switch_SkillBook) && pclCharSkillBookInfo )
	{
		stMagicAttributeData*	psSubMagicData = pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( magickind, siSubMagickind );
		if( psSubMagicData )
		{
			siSubDelay = psMagicData->si32MagicDelay;
		}
	}
	
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		if(GetMana() < mana)
		{
			*preturn = CANUSEMAGIC_ERROR_NEEDMANA;
			return false;
		}
	}
	
	//========================================================
	// ���� ���� 
	//========================================================
	// ����� ���� ���� �ð��� Ȯ���ߴ��� Ȯ���Ѵ�. 
	SI32 siDelay = psMagicData->si32MagicDelay - (psMagicData->si32MagicDelay * clPB.siMagicDecDelay / 100 );
	siDelay += (siDelay * siSubDelay) / 100;
	if(GetMagicDelay() < siDelay )
	{
		*preturn = CANUSEMAGIC_ERROR_NEEDTIMEDELAY;
		return false;
	}

	return true;
}

// �������� ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
bool cltCharCommon::CanMagic(SI32 targetid, SI32 magickind, SI32* preturn, bool PVP )
{
	// �ϴ� �ʱ�ȭ ��Ų��.
	*preturn = CANUSEMAGIC_ERROR_INVALID;

	//========================================================
	// �⺻ �˻� 
	//========================================================
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		// ȭ�鿡 �� �� ���� ĳ���Ͷ�� ������ �� ����. 
		if(pclCM->IsAlive( targetid )	==	FALSE)	return false;
	}
	else
	{
		// ȭ�鿡 �� �� ���� ĳ���Ͷ�� ������ �� ����. 
		if(pclCM->IsValidID( targetid ) == FALSE)	return false;
	}


	//========================================================
	// ��ġ �˻� 
	//========================================================
	// ���� ���� ���� ��ġ�� ���� ���� �ٸ��� ������ ����� �� ����. 
	if(GetMapIndex() != pclCM->CR[ targetid]->GetMapIndex())	return false;

	//---------------------------------------------
	// ���� ������ ���� ���� ���� ���θ� �����Ѵ�. 
	stMagicAttributeData* psMagicData = pclClient->pclMagicManager->GetMagicAttribute( magickind ); 
	//========================================================
	// ���� �˻� 
	//========================================================
	
	// Mana�� ����ؾ� �Ѵ�. 

	//SKILL LEVEL�� ���� MANA �Һ� 
	SI32 kind = 0;
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))	kind = GetKind();
	CMagicAttribute* pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
	SI32			 skilltype			= pMagicAttributePtr->GetMagicSkillType( magickind );
	if( SKILL_SIKLLBOOK == skilltype && IsPC(GetID())  )
	{
		cltSkillBookMagic*	pclSkillBookMagic = pclCharSkillBookInfo->GetSkillBookMagic( GetAttackType() );	
		if( NULL == pclSkillBookMagic ) return false;

		skilltype = pclSkillBookMagic->GetSkillUnique();	
	}



#ifdef _SAFE_MEMORY
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( skilltype, kind, pclCI->clIP.GetLevel(), &pclCI->clCharItem.clItem[0], GetID() );
#else
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( skilltype, kind, pclCI->clIP.GetLevel(), pclCI->clCharItem.clItem, GetID() );
#endif
	// Skill Level�� ���� ������� �ְ� ������ ������� �־� �����Һ��� ����Ѵ�.
	SI32 mana		= pclClient->pclMagicManager->GetSpendMana(magickind, SkillLevel,GetCharUnique());
	
	// MAGIC_TYPE_SOULGUARD �̸� ��ų���߰� mana�� ���������� ���Ѵ�.
	if(magickind == MAGIC_SOULGUARD_FIRE)
	{
		SkillLevel = 1;
		mana = 0;
	}
	// �ҿ� ���� ��Ų�� ����ϴ� ����
	if(magickind == MAGIC_SOULGUARD_PUMKIN)
	{	
		SkillLevel = 1;
		mana = 0;
	}
	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		if(GetMana() < mana)
		{
			*preturn = CANUSEMAGIC_ERROR_NEEDMANA;
			return false;
		}
	}

	//========================================================
	// ���� ���� 
	//========================================================
	bool bcheckdelayswitch = false;
	if(pclClient->GameMode == GAMEMODE_SERVER)	
	{
		bcheckdelayswitch = true;
	}
	else
	{
		if(GetID() == 1)
		{
			bcheckdelayswitch = true;
		}
		if(GetSummonParentID() == 1)
		{
			bcheckdelayswitch = true;
		}
	}

	// [����] ���� ������ ���� ���.
	SI32	siSubMagickind		= 0;
	SI32 	siSubDelay 			= 0;
	SI32 	siSubMagicDistance	= 0;
	if( pclClient->IsCountrySwitch(Switch_SkillBook) && pclCharSkillBookInfo )
	{
		stMagicAttributeData*	psSubMagicData	= pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( magickind, siSubMagickind );
		if( psSubMagicData )
		{
			siSubDelay			= psSubMagicData->si32MagicDelay;
			siSubMagicDistance	= psSubMagicData->si32MagicDistance;
		}
	}

	if(bcheckdelayswitch == true)
	{
		SI32 siMagicDelay = psMagicData->si32MagicDelay - (psMagicData->si32MagicDelay * clPB.siMagicDecDelay / 100 );
		siMagicDelay += (siMagicDelay * siSubDelay) / 100;
		// ����� ���� ���� �ð��� Ȯ���ߴ��� Ȯ���Ѵ�. 
		if( GetMagicDelay() < siMagicDelay )
		{
			*preturn = CANUSEMAGIC_ERROR_NEEDTIMEDELAY;
			return false;
		}
	}

	//========================================================
	// �����Ÿ� 
	//========================================================
	SI32 siDisX = TABS(GetX()- pclCM->CR[targetid]->GetX());
	SI32 siDisY = TABS(GetY()- pclCM->CR[targetid]->GetY());
	
	SI32 siMagicDistance = psMagicData->si32MagicDistance;
	siMagicDistance += (siMagicDistance * siSubMagicDistance) / 100;
	// ���� �����Ÿ��� �ָ� ������ �ʴ´�.
	if( max(siDisX, siDisY) > siMagicDistance ) 
	{
		*preturn = CANUSEMAGIC_ERROR_FARDISTANCE;
		return false;
	}
	
	//========================================================
	// 
	//========================================================
	switch(magickind)
	{
	case MAGIC_MON_HEAL:
		{
			// �ߵ��Ǿ� �ִ� ���¿����� ġ�� �Ұ�. 
			if(clInnerStatus.IsStatus(INNERSTATUS_POISON) || clInnerStatus.IsStatus(INNERSTATUS_MAGICFIRE) || clInnerStatus.IsStatus(INNERSTATUS_POISON_SETITEM_EFFECT) )
			{
				return false;
			}

			// �ջ� ���� ĳ���Ϳ��� �Ѵ�. 
			if(pclCM->CR[targetid]->clPB.GetMaxLife() == pclCM->CR[targetid]->pclCI->clIP.GetLife())return false;

			// ��ȯ����� pc���Ը� �����ϴ�. ���õǾ �������� ����ϴ°� �ƴϸ� �����̶� �ڱ��ڽſ��Ը� �����ϴ�.
			if ( targetid == GetCharUnique() )
			{
			}
			else
			{
				SI32 siParentID = GetSummonParentID();
				if ( pclCM->IsValidID(siParentID) )
				{
					if(IsPC(pclCM->CR[targetid]->GetCharUnique()) == false )
					{
						return false ;
					}
					else
					{
						if ( pclCM->CR[siParentID]->siSelectedCharIndex != GetSummonIndex() &&
							siParentID != targetid )
						{
							return false ;
						}
					}
				}
			}

			return true;
			
		}
		break;
	default:
		// �ڱ� �ڽ��� ������ �� ����.
		if(targetid == siID)return false;
		
		if( PVP )
		{
			if( false == IsEnemyPCvsPC(targetid) )
				return false;	
		}
		else
		{
			if( false == IsEnemy(targetid) )
				return false;
		}
		break;

	}
	
	//========================================================
	// ���� Ÿ�� 
	//========================================================
	// ����� ĳ������ ��쿡�� �����Ѵ�. 
	if(IsPC(GetCharUnique()))
	{	
		CMagicAttribute *pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
		SI32 magictype = pMagicAttributePtr->GetMagicType(magickind);
		
		// ����� �ش��ϴ� ����Ÿ���� �˾Ƴ���. 
		switch(magictype)
		{
		case MAGIC_TYPE_SWORD:	if(GetAttackType() != ATTACKTYPE_SWORD )	return false;	break;	
		case MAGIC_TYPE_SPEAR:	if(GetAttackType() != ATTACKTYPE_SPEAR)		return false;	break;	
		case MAGIC_TYPE_AXE:	if(GetAttackType() != ATTACKTYPE_AXE)		return false;	break;	
		case MAGIC_TYPE_STAFF:	if(GetAttackType() != ATTACKTYPE_STAFF	&&  GetAttackType() != ATTACKTYPE_STAFF1 &&  GetAttackType() != ATTACKTYPE_STAFF2 &&  GetAttackType() != ATTACKTYPE_NEW_STAFF2) return false;	break;	
		case MAGIC_TYPE_BOW:	if(GetAttackType() != ATTACKTYPE_BOW	&&  GetAttackType() != ATTACKTYPE_BOW1	 &&  GetAttackType() != ATTACKTYPE_NEW_BOW1)	return false;		break;	
		case MAGIC_TYPE_GUN:	if(GetAttackType() != ATTACKTYPE_GUN	&&  GetAttackType() != ATTACKTYPE_GUN1	 &&  GetAttackType() != ATTACKTYPE_NEW_GUN1)	return false;		break;	
		case MAGIC_TYPE_MON:	return false;	break;
		case MAGIC_TYPE_SOULGUARD:	break;	
		case MAGIC_TYPE_SKILL_BOOK:	break;	
		}		

		bool bcheckskillswitch = false;
		if(pclClient->GameMode == GAMEMODE_SERVER)	
		{
			bcheckskillswitch = true;
		}
		else
		{
			if(GetID() == 1)		// �ڱ� �ڽ��� ����̰ų�. 
			{
				bcheckskillswitch = true;
			}
			if(GetSummonParentID() == 1)	// �ڽ��� ��ȯ���� ��쿡, 
			{
				bcheckskillswitch = true;

			}
		}

		if(bcheckskillswitch == true)
		{
			// ���� ������ �ʿ��� ��� ������ �����ϰ� �ִ°�.  
			SI32 siSkilltype = 0;

			// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
			siSkilltype = pMagicAttributePtr->GetMagicSkillType(magickind);
			if( SKILL_SIKLLBOOK == siSkilltype && IsPC(GetID())  )
			{
				cltSkillBookMagic*	pclSkillBookMagic = pclCharSkillBookInfo->GetSkillBookMagic( GetAttackType() );	
				if( NULL == pclSkillBookMagic ) return false;

				siSkilltype = pclSkillBookMagic->GetSkillUnique();	
			}
#ifdef _SAFE_MEMORY
			SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( siSkilltype, 0, pclCI->clIP.GetLevel(), &pclCI->clCharItem.clItem[0], GetID());
#else
			SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel( siSkilltype, 0, pclCI->clIP.GetLevel(), pclCI->clCharItem.clItem, GetID());
#endif
			if(magictype == MAGIC_TYPE_SOULGUARD)	return true;

			if ( SkillLevel < psMagicData->si16MagicSkillLevel )
			{
				*preturn = CANUSEMAGIC_ERROR_NOTENOUGHSKILL;
				return false;
			}
		}
	}
	

	return true;
}

bool cltCharCommon::CanMagicBuf( SI32 siMagicKind, SI32* psiReturn )
{
	if ( NULL == psiReturn )
	{
		return false;
	}

	// �켱 �ʱ�ȭ
	*psiReturn = CANUSEMAGIC_ERROR_INVALID;
	
	// �⺻������ ����϶��� ���� ������ ����� �� �ִ�
	SI32 siMyCharID = GetCharUnique();
	if ( false == IsPC(siMyCharID) )
	{
		return false;
	}

	// Ŭ���̾�Ʈ�϶��� �ڱ��ڽŸ� �˻��ؾ� �Ҷ��� �ִ� �׷����� ���ؼ�
	bool bCheckMode = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		bCheckMode = true;
	}
	// Ŭ���̾�Ʈ �϶��� �ڱ� �ڽŸ� �˻��Ѵ�
	else if ( GetID() == 1 )
	{
		bCheckMode = true;
	}
	


	//========================================================
	// �⺻ ������ ������ ������
	//========================================================
	CMagicAttribute* pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
	if ( NULL == pMagicAttributePtr )
	{
		return false;
	}

	stMagicAttributeData* pMagicData = pclClient->pclMagicManager->GetMagicAttribute( siMagicKind );
	if ( NULL == pMagicData )
	{
		return false;
	}

	// ������ ������ �ƴϸ� �� �� ����
	if ( MAGIC_CASTTYPE_BUF != pMagicData->si08MagicCastType )
	{
		return false;
	}

	// �ش� ������ ����� �� �ִ� ������ �˻��Ѵ�
	if ( (true == bCheckMode) && (false == m_clMagicBufMgr.CheckMagicBufSlot(siMagicKind)) )
	{
		return false;
	}

	// �ش� ������ �� ���ð� �˻�
	if ( (GAMEMODE_SERVER == pclClient->GameMode) && (false == m_clMagicBufMgr.CheckDelay(siMagicKind)) )
	{
		*psiReturn = CANUSEMAGIC_ERROR_NEEDTIMEDELAY;
		return false;
	}


	SI32 siMyKind		= 0;
	if ( IsNPC(GetCharUnique()) || IsInstanceNPC(GetCharUnique()) )
	{
		siMyKind = GetKind();
	}
	SI32 siMyLevel	 = pclCI->clIP.GetLevel();
	SI32 siSkillType = pMagicAttributePtr->GetMagicSkillType( siMagicKind );;
	
	// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
	if( SKILL_SIKLLBOOK == siSkillType && IsPC(GetID())  )
	{
		cltSkillBookMagic*	pclSkillBookMagic = pclCharSkillBookInfo->GetSkillBookMagic( GetAttackType() );	
		if( NULL == pclSkillBookMagic ) return false;

		siSkillType = pclSkillBookMagic->GetSkillUnique();
	}

	//-----------------------------------------------------------------------------------------------------
	// �ʿ� �������� üũ�Ѵ�
	//-----------------------------------------------------------------------------------------------------
#ifdef _SAFE_MEMORY	
	SI32 SkillLevel	= pclCI->clCharSkill.GetTotalSkillLevel( siSkillType, siMyKind, siMyLevel, &pclCI->clCharItem.clItem[0] );
#else	
	SI32 SkillLevel	= pclCI->clCharSkill.GetTotalSkillLevel( siSkillType, siMyKind, siMyLevel, pclCI->clCharItem.clItem );
#endif
	SI32 siNeedMana	= pclClient->pclMagicManager->GetSpendMana( siMagicKind, SkillLevel, GetCharUnique() );

	// [����] ���� ������ ���� ���.
	SI32	siSubMagickind = 0;
	SI32	siSubNeedMana  = 0;
	if( pclClient->IsCountrySwitch(Switch_SkillBook) && pclCharSkillBookInfo )
	{
		stMagicAttributeData*	psSubMagicData	= pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( siMagicKind, siSubMagickind );
		if( psSubMagicData )
		{
			siSubNeedMana  = pclClient->pclMagicManager->GetSpendMana( siSubMagickind, SkillLevel, GetCharUnique() );
		}
	}

	if ( (GAMEMODE_SERVER == pclClient->GameMode) && (GetMana() < siNeedMana + siSubNeedMana) )
	{
		*psiReturn = CANUSEMAGIC_ERROR_NEEDMANA;
		return false;
	}

	//-----------------------------------------------------------------------------------------------------
	// ��ų ������ üũ�Ѵ�
	//-----------------------------------------------------------------------------------------------------
	if ( true == bCheckMode )
	{
#ifdef _SAFE_MEMORY	
		SI32 siCheckLevel	= pclCI->clCharSkill.GetTotalSkillLevel( siSkillType, 0, siMyLevel, &pclCI->clCharItem.clItem[0] );
#else	
		SI32 siCheckLevel	= pclCI->clCharSkill.GetTotalSkillLevel( siSkillType, 0, siMyLevel, pclCI->clCharItem.clItem );
#endif	
		if ( siCheckLevel < pMagicData->si16MagicSkillLevel )
		{
			*psiReturn = CANUSEMAGIC_ERROR_NOTENOUGHSKILL;
			return false;
		}
	}

	//-----------------------------------------------------------------------------------------------------
	// ���� ��� Ÿ�Կ� �ش��ϴ� ���⸦ �������� �ʾҴٸ�
	//-----------------------------------------------------------------------------------------------------
	SI32 siMagicType	= pMagicAttributePtr->GetMagicType( siMagicKind );
	switch ( siMagicType )
	{
		case MAGIC_TYPE_SWORD:	if ( GetAttackType() != ATTACKTYPE_SWORD )	return false;	break;	
		case MAGIC_TYPE_SPEAR:	if ( GetAttackType() != ATTACKTYPE_SPEAR )	return false;	break;	
		case MAGIC_TYPE_AXE:	if ( GetAttackType() != ATTACKTYPE_AXE )	return false;	break;	
		case MAGIC_TYPE_STAFF:	if ( GetAttackType() != ATTACKTYPE_STAFF &&  GetAttackType() != ATTACKTYPE_STAFF1 &&  GetAttackType() != ATTACKTYPE_STAFF2 &&  GetAttackType() != ATTACKTYPE_NEW_STAFF2) return false;break;	
		case MAGIC_TYPE_BOW:	if ( GetAttackType() != ATTACKTYPE_BOW &&  GetAttackType() != ATTACKTYPE_BOW1 &&  GetAttackType() != ATTACKTYPE_NEW_BOW1)return false;		break;	
		case MAGIC_TYPE_GUN:	if ( GetAttackType() != ATTACKTYPE_GUN &&  GetAttackType() != ATTACKTYPE_GUN1 &&  GetAttackType() != ATTACKTYPE_NEW_GUN1)return false;		break;
		case MAGIC_TYPE_MON:	return false;	break;
		case MAGIC_TYPE_SOULGUARD:	break;
		case MAGIC_TYPE_SKILL_BOOK:	break;
			
	}		

	return true;

}


//------------------------------------------
// attack_id ���� �����ϰ� ����� �Լ� 
//------------------------------------------
BOOL cltCharCommon::SetAttack(SI32 id, bool PVPHit)
{
	// ���� ��ǥ�� �̹� �׾��ų� ���� �ƴϸ� �������� �ʴ´�. 
	if(pclCM->IsAlive(id)==FALSE)
		return FALSE;

	// �ڱ� �ڽ��� ������ �� ����. 
	if(id == siID)
		return FALSE;

	// PVP�Ӽ��� �ش� pvp-
	//if( pclClient->IsWhereServiceArea(ConstServiceArea_English) )
	if(pclClient->siEnablePVP == 1)
	{
		if( PVPHit )
		{
			if( pclClient->pclMapManager->IsPkMap( GetMapIndex() ) )
			{
				clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
			}
			if( pclClient->pclMapManager->IsPkMap( pclCM->CR[id]->GetMapIndex() ) )
			{
				pclCM->CR[id]->clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
			}
		}
	}
	if (pclClient->siEnablePVP == 1) 
	{
		if (PVPHit) 
		{
			SI32 siEnemyId = pclCM->CR[id]->siEnemUnique ;
			if( siEnemyId > 0 )
			{
				clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
			}
			if( siEnemyId > 0 )
			{
				pclCM->CR[id]->clInnerStatus.clEnemyType.siEnemyType |= ENEMYTYPE_PVP;
			}
		}
	}

	// ���� ��ǥ�� �����Ѵ�. 
	cltCharPos clpos(pclCM->CR[id]->GetMapIndex(), pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY());
	cltAttackTarget cltarget(id, &clpos, 0,0, PVPHit);
	
	clAttackTarget.Set(&cltarget);

	// �󸶳� �����ϰ� ������ ���� �����ϴ� ����. 
	dwAttackGiveUpDelay		= 5000; // 5��. 
	dwLastAttackClock		= pclClient->CurrentClock;

    return TRUE;
}


BOOL cltCharCommon::ReadyToFire()
{
	if(ChangeDirection(TargetDirection)==FALSE)
		return FALSE;	

	return TRUE;
}

BOOL cltCharCommon::Escape()
{
	SI32 attackid = clAttackTarget.GetAttackID();
	if( pclCM->IsValidID(attackid) == false )		return FALSE;

	// ���� �����ϱ� ���� �Ÿ��� ��췯 �̵��Ѵ�.
	siSubOrder	=	CHARWORKSTEP_RETREAT;
	
	cltPos clpos1(pclCM->CR[attackid]->GetX(), pclCM->CR[attackid]->GetY());
	cltPos clpos2(GetX(), GetY());

	SHORT dir = DecideDirection8(&clpos1, &clpos2);

	SHORT tx  = GetX(), ty = GetY();
	
	if(dir&NORTH)
	{
		ty=max(0, GetY()-3);
	}
	if(dir&SOUTH)
	{
		ty=min(pclMap->GetYsize() - 1, GetY()+3);
	}
	if(dir&EAST)
	{
		tx=min(pclMap->GetXsize() - 1, GetX()+3);
	}
	if(dir&WEST)
	{
		tx=max(0, GetX()-3);
	}
	
	SetMove(tx, ty);
	
	return FALSE;
}

BOOL cltCharCommon::TryAttack()
{
			 
	// ��ǥ�� ������ ���Ѵ�. 
	SI32 attackid	= clAttackTarget.GetAttackID();
	if( pclCM->IsValidID(attackid) == false )		return FALSE;

	TargetDirection = DecideDirection8(GetX(), GetY(), pclCM->CR[attackid]->GetX(), pclCM->CR[attackid]->GetY());


	// ���� ������ ���� ���� �ֱ� ����
	DWORD dwSubAttackInterval = 0;
	if ( IsPC(GetCharUnique()) )
	{
		SI32 siCalcAttackInterval = m_clMagicBufMgr.GetIncAttackInterval( this );
		if ( siCalcAttackInterval )
		{
			dwSubAttackInterval = (clPB.dwAttackInterval/100) * siCalcAttackInterval;
			pclClient->pclLog->LogPrint( TEXT("�������� : %d\n"), dwSubAttackInterval );
		}
	}

	//---------------------------------------------------
	// ���� �ֱ⸦ ����Ѵ�. 
	//---------------------------------------------------
	if ( TABS(pclClient->CurrentClock - dwLastAttackIntervalClock) < (int)(clPB.dwAttackInterval-dwSubAttackInterval) )
	{
		bBusySwitch = false;
		return TRUE;
	}
	dwLastAttackIntervalClock = pclClient->CurrentClock;
	
	
	// �ٸ� �غ� �Ǿ����� Ȯ���Ѵ�. 
	if( ReadyToFire() == FALSE )	return TRUE;
	 
	siSubOrder	=	CHARWORKSTEP_ACTION;

	clAniInfo.siAniStep = 0;		// �ִϸ��̼��� �ʱ�ȭ���ش�. 
	clAniInfo.dwAniStartClock	= pclClient->CurrentClock;

	// ������ ���� ������ ã�´�. 
/*	SI32 anilist[10];
	SI32 anilistindex = 0;

	SI32 attacktype = 0;
	for(SI32 i = 0;i < 3;i++)
	{
		if		(i == 0)attacktype = ANITYPE_ATTACK;
		else if	(i == 1)attacktype = ANITYPE_ATTACK1;
		else if	(i == 2)attacktype = ANITYPE_ATTACK2;
		else
		{
			MsgBox(TEXT("vvce9jf"), TEXT("Fdsf3d"));
		}

		SI32 aniref	= pclKI->clCharAniManager.FindRefFromAnitype(attacktype);
		if(aniref >= 0)
		{
			anilist[anilistindex] = attacktype;
			anilistindex++;
		}
	}

	if(anilistindex)
	{
		siCurrentAttackType = anilist[rand() % anilistindex];
	}
*/
	// by LEEKH 2007.12.28 - TRANSFORM
	if ( GetKindInfo(true)->siMaxAttackType )
		siCurrentAttackType = GetKindInfo(true)->siAttackList[rand() % GetKindInfo()->siMaxAttackType];

	if ( !siCurrentAttackType ) siCurrentAttackType = ANITYPE_ATTACK ;

	SetAttack(attackid, clAttackTarget.bPVPHit);
	
	
	
	return FALSE;
}



//-----------------------------
// ĳ���� ���� 
//-----------------------------
SI32 cltCharCommon::Action_Attack()
{
	SHORT status;
	SHORT direction=0;
	SI32 six = LOWORD(clCurOrder.siPara1);
	SI32 siy = HIWORD(clCurOrder.siPara1);

	/*   if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
	{
	}
	*/

	SI32 attackid = clAttackTarget.GetAttackID();

	// ���� ������ ���� �����Ÿ� ����
	SI32 siAddAttackRange = GetAttackRange();
	if ( IsPC(GetCharUnique()) )
	{
		siAddAttackRange += m_clMagicBufMgr.GetIncRange( this );
	}	
	if(siSubOrder == CHARWORKSTEP_MOVE)
	{
#ifdef _DEBUG
		// �ٰŸ� ������� ���� �ϵ��� �Ѵ�.
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			if ( IsPC(GetCharUnique()) && IsNPC(attackid) )
			{
				cltServer* pclserver = (cltServer*)pclClient ;

				if ( clPB.GetAttackRange() == 1 && pclserver->pclCM->IsAlive(attackid) )
				{
					if( IsNPC(pclserver->pclCM->CR[attackid]->GetCharUnique()) == true &&
						pclserver->pclCM->CR[attackid]->pclKI->IsAtb((ATB_NOJJIM)) == false &&
						pclserver->pclCM->CR[attackid]->clIdentity.siIdentity == 0)
					{
						// ��������� �����Ѵ�. 
						if(pclserver->pclCM->CR[attackid]->clJim.SetBeJimed(GetCharUnique(),
																			pclserver->GetFrame()) == true)
						{
							// �̹� �ٸ� ���� ĳ���Ͱ� ������ ���� �����Ѵ�. 
							if(clJim.siJimSlaveCharUnique)
							{
								// �̹� ���� �ٸ� ĳ���Ͱ� ���� �ƴϾ��...
								if(clJim.siJimSlaveCharUnique != pclserver->pclCM->CR[attackid]->GetCharUnique())
								{
									SI32 id = pclCM->GetIDFromCharUnique(clJim.siJimSlaveCharUnique);
									if ( pclserver->pclCM->IsAlive(id) )
									{
										pclserver->pclCM->CR[id]->clJim.Init();

										cltGameMsgResponse_Jim clinfo(clJim.siJimSlaveCharUnique, 0);
										cltMsg clMsg(GAMEMSG_RESPONSE_JIM, sizeof(clinfo), (BYTE*)&clinfo);
										((cltCharServer*)pclserver->pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

									}

									clJim.siJimSlaveCharUnique = 0;
								}

							}

							// �������� �����Ѵ�. 
							clJim.SetJim(pclserver->pclCM->CR[attackid]->GetCharUnique());

							cltGameMsgResponse_Jim clinfo(pclserver->pclCM->CR[attackid]->GetCharUnique(), GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_JIM, sizeof(clinfo), (BYTE*)&clinfo);
							((cltCharServer*)this)->SendNeighbourMsg(&clMsg, true);
						}
					}
				}
			}
		}
#endif

		status = Move();
		
		if ( MoveDone() )
		{
			bBusySwitch = false;
		}
		else
		{
			bBusySwitch = true;
		}

		if(bBusySwitch == false)
		{
			// ���� ������ �� ���� ó�����, 
			if(CanAttack(&clAttackTarget)==FALSE)
			{  
				return -1;
			}

			if ( IsInRange(attackid, siAddAttackRange) )
			{
				siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
			}

			// �������� �����ϰų� �߰� ������ �����ϸ�, 
			if(status > 0)
			{
				siSubOrder	 =	CHARWORKSTEP_DECIDELENGTH;
			}
		}
   }

   if(siSubOrder == CHARWORKSTEP_DECIDELENGTH)
   {
		  //----------------------------------------------------------
		  // NPC�� ��� ���� �ð� ������ ������ ������ �����ؾ� �Ѵ�. 
		  //----------------------------------------------------------
		  if(pclClient->GameMode == GAMEMODE_SERVER)
		  {
			  // ���� ���ϱ� �̺�Ʈ�� ���� ���̸� ������ �����ϸ�ȵȴ�.
			  if(IsNPC(GetCharUnique()) && pclCM->IsValidID(attackid) && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON && clIdentity.siIdentity != IDENTITY_RACOONDODGE_EVENT )
			  {
				  // ���� �ð� �̻� ���������� ����. 
				  if(TABS(pclClient->CurrentClock - dwLastAttackClock) > (int)dwAttackGiveUpDelay)
				  {
					  bBusySwitch = false;
					  return -2;
				  }

				  // ������ ���� ���¸� ���� Ȯ���� ���� ����. 
				  if(pclCM->CR[attackid]->bNoFirstAttackSwitch && rand() % 10 == 0)
				  {
					  bBusySwitch = false;
					  return -2;
				  }

				  // �����̾� ���� ���� �������̶�� ���� ����.
				  if(pclCM->CR[attackid]->bPersonalShopSwitch == true 
					  && pclCM->CR[attackid]->bPremiumPersonalShop == true )
				  {
					  bBusySwitch = false;
					  return -2;
				  }
				  // �����̾� ���� ������ ���� ���̶�� ���� Ȯ���� ���� ����.
				  if(pclCM->CR[attackid]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK) && rand() % 10 == 0 )
				  {
					  bBusySwitch = false;
					  return -2;					
				  }

				  // ������� �Ծ ���� ����ȿ�� ���̶�� ���� Ȯ���� ���� ����.
				  if(pclCM->CR[attackid]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI) && rand() % 10 == 0 )
				  {
					  bBusySwitch = false;
					  return -2;					
				  }
				  // ���� ���� ����(�߽��� ���� ����)�̸� ���� Ȯ���� ���� ���� 
				  if(pclCM->CR[attackid]->pclCI->clBI.clBufInfo.IsHaveBufExecptGetType(BUF_TRANSFORM, BUF_GET_TYPE_NIGHTMARKET) && rand() % 10 == 0 )
				  {
					  bBusySwitch = false;
					  return -2;					
				  }

			  }
		  }
		  
		  // ���� ������ �� ���� ���¶�� �ߴ��Ѵ�.
		  if(CanAttack(&clAttackTarget)==FALSE)
		  {   
			  bBusySwitch	=	false;
			  return -1;
		  }

		  //------------------------------------
		  // ���� ������ ���� �� �ִٸ� 
		  //------------------------------------
		  if(MagicInAttackAction() == true)
		  {
			  return 1;
		  }

		  // ���� �����Ÿ� �ȿ� ������,
		  if ( IsInRange(attackid, siAddAttackRange) )
		  { 
			  // ���� �õ� �����Ƿ� ������Ʈ. 
			  dwLastAttackClock = pclClient->CurrentClock;

			  // ������ �õ��Ѵ�. 
			  if(TryAttack()==TRUE)
			  {
				  return 1;
			  }
			  
		  }
		  else // ���� ��Ÿ� �ۿ� ������, 
		  {  
			  // ���ݰ����ϰ� �̵� ���� �ϴٸ�, 
			  if(CanAttack(&clAttackTarget) && pclCM->IsValidID(attackid) && IsAtb(ATB_MOVE)==TRUE)
			  {
				  // ���� �ִ� ������ �̵��Ѵ�. 
				  SetMove(pclCM->CR[attackid]->GetX(), pclCM->CR[attackid]->GetY());

				  siSubOrder = CHARWORKSTEP_MOVE;
			  }
			  else
			  {
				  bBusySwitch = false;
				  return -1;
			  }
		  }
	   
   }
   if(siSubOrder == CHARWORKSTEP_RETREAT)
   {
	    status = Move();
		if(MoveDone())bBusySwitch = false;
		else
		{
			bBusySwitch = true;
		}

		if(bBusySwitch == false)
		{
			
			// ���� ������ �� ���� ó�����, 
			if(CanAttack(&clAttackTarget)==FALSE)
			{  
				return -1;
			}

			if ( IsInRange(attackid, siAddAttackRange) )
			{
				if(IsInMinRange(attackid, 1)==FALSE)
				{
					siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
				}
			}
			
			// �������� �����ϰų� �߰� ������ �����ϸ�, 
			if(status > 0)
		   {
		      siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
		   }

		}
   }

	if(siSubOrder == CHARWORKSTEP_ACTION)
	{
		bBusySwitch = true;

		// Ÿ���� 1ȸ �Ϸ�Ǹ�, �ٽ� ��ǥ���� �Ÿ��� �����Ѵ�. 
		if(Fire() == true)
		{
			siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
			bBusySwitch	=	false;

			//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
			//�̰����� ����ü�� �������� ��´� - ���ݽ�, ����.
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[GetID()];
				if ( pclchar )
				{
					if ( IDENTITY_PERSON_SUMMON == pclchar->clIdentity.siIdentity )
					{
						pclchar->DecreaseCrystalDurACForSummon(CRYSTAL_DECREASE_DURABILITY_ACNUM);
					}
					else
					{
						pclchar->DecreaseCrystalDurAC(CRYSTAL_DECREASE_DURABILITY_ACNUM);
					}

				}
			}
		}
	}

	return 1;
}


bool cltCharCommon::FireSub()
{
    int id=0;
	int x=0, y=0;
	SI32 apower = 0;
	SI32 hitrate = 0;
	int attackstartx, attackstarty;
	bool bfailswitch = false;

	SI32 attackid = clAttackTarget.GetAttackID();

	//------------------------------------------
	// ���߷� ���. 
	//------------------------------------------
	if(pclCM->IsAlive(attackid) == TRUE)
	{
		SI32 myID = GetID();

		//// GOD ���� ������ 100%
		//if ( pclCM->CR[myID]->bGodMode == true ) 
		//{
		//	clAttackTarget.siHitRate = clPB.GetHitRate( pclCM->CR[attackid]) * 100;
		//}GOD ���� ������ 100%
		//else
		//{
			clAttackTarget.siHitRate = clPB.GetHitRate( pclCM->CR[attackid], this );
		//}
		
		if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
		{
			clAttackTarget.siDodgeRate = pclCM->CR[attackid]->clPB.GetDodgeRate( pclCM->CR[myID], pclCM->CR[attackid] );
		}
		else
			clAttackTarget.siDodgeRate = 0;
	}
	else
	{
		clAttackTarget.siHitRate = 0;
		clAttackTarget.siDodgeRate = 0;
	}

	// ���� ������ ���� ���߷� ���
	if ( IsPC(GetCharUnique()) )
	{
		SI32 siAddHitRate = m_clMagicBufMgr.GetIncHitRate( this );
		if ( siAddHitRate )
		{
			SI32 siCalcHitRate = (clAttackTarget.siHitRate / 100) * siAddHitRate;
			clAttackTarget.siHitRate += siCalcHitRate;
			pclClient->pclLog->LogPrint( TEXT("���߷����� : %d\n"), siCalcHitRate );
		}
	}

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		//[����] ��Ʈ ������ ���� ���� ���߷� ����.
		if( m_siSetItemType )
		{
			SI32 siCalcHitRate = 0;
			siCalcHitRate += (clAttackTarget.siHitRate / 100) * pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( this, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_1 );
			siCalcHitRate += (clAttackTarget.siHitRate / 100) * pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( this, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_2 );
			siCalcHitRate += (clAttackTarget.siHitRate / 100) * pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( this, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_3 );
			siCalcHitRate += (clAttackTarget.siHitRate / 100) * pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( this, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_4 );
			siCalcHitRate += (clAttackTarget.siHitRate / 100) * pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( this, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_5 );
			
			clAttackTarget.siHitRate += siCalcHitRate;
		}
	}



	if( GetAttackType() == ATTACKTYPE_SWORD
	||	GetAttackType() == ATTACKTYPE_SPEAR
	||	GetAttackType() == ATTACKTYPE_AXE
	||	GetAttackType() == ATTACKTYPE_STAFF
	||	GetAttackType() == ATTACKTYPE_HAND
	||  GetAttackType() == ATTACKTYPE_HEROSWORD )
	{
		if(clAniInfo.IsInstant()  && bHitDoneSwitch == false)
		{
			bHitDoneSwitch = true;

			if(GetKindInfo()->IsAtb(ATB_HERO) == TRUE )
			{
				
				switch(GetAttackType())
				{
				case ATTACKTYPE_SWORD:
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WEAPON_SWORD_FIRE")), GetX(), GetY());
					break;
				case ATTACKTYPE_SPEAR:
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WEAPON_SPEAR_FIRE")), GetX(), GetY());
					break;
				case ATTACKTYPE_AXE:
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WEAPON_AXE_FIRE")), GetX(), GetY());
					break;
				case ATTACKTYPE_STAFF:
				case ATTACKTYPE_STAFF1:
				case ATTACKTYPE_STAFF2:
				case ATTACKTYPE_NEW_STAFF2:
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_STAFF_FIRE")), GetX(), GetY());
					break;
				case ATTACKTYPE_HAND:
				case ATTACKTYPE_BOW:
				case ATTACKTYPE_BOW1:
				case ATTACKTYPE_NEW_BOW1:
				case ATTACKTYPE_GUN:
				case ATTACKTYPE_GUN1:
				case ATTACKTYPE_NEW_GUN1:
					break;
				default:
					break;
				}
			}
			// ���� ȿ����. 
			if( siCurrentAttackType == ANITYPE_ATTACK )
			{
				if(GetKindInfo()->clKIEffectInfo.siAttackEffect)
				{
					pclClient->PushEffect(GetKindInfo()->clKIEffectInfo.siAttackEffect, GetX(), GetY());
				}
			}
			else
			{
				if(GetKindInfo()->clKIEffectInfo.siAttackEffect1 > 0 )
				{
					pclClient->PushEffect(GetKindInfo()->clKIEffectInfo.siAttackEffect1, GetX(), GetY());
				}
				else if(GetKindInfo()->clKIEffectInfo.siAttackEffect)
				{
					pclClient->PushEffect(GetKindInfo()->clKIEffectInfo.siAttackEffect, GetX(), GetY());
				}
			}

		/*	if( ConstServiceArea_China == pclClient->siServiceArea ||
				ConstServiceArea_English == pclClient->siServiceArea )
			{
				cltGameMsgRequest_Hit clHit( pclCM->CR[siID]->GetCharUnique(), &clAttackTarget );
				clHit.clAttackTarget.SetAttackID( pclCM->CR[attackid]->GetCharUnique() );

				cltMsg clMsg( GAMEMSG_REQUEST_HIT, sizeof(clHit), (BYTE*)&clHit );
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
			else*/
			{
				if(pclClient->GameMode == GAMEMODE_SERVER)
				{
					cltAttackDamageInfo cldamageinfo(GetAttackType(), GetApower(), 0);

					SI32 siAddAttackRange = GetAttackRange();
					if ( IsPC( GetCharUnique() ) )
					{
						siAddAttackRange += m_clMagicBufMgr.GetIncRange( this );
					}

					((cltServer*)pclClient)->HitOperation(siID, &cldamageinfo, siAddAttackRange, &clAttackTarget, pclMap);
				}
			}
		}
	}
	else if(GetAttackType() == ATTACKTYPE_BOW  
		|| GetAttackType() == ATTACKTYPE_GUN
		|| GetAttackType() == ATTACKTYPE_CAKE
		|| GetAttackType() == ATTACKTYPE_EGG
		|| GetAttackType() == ATTACKTYPE_CANNON
		|| GetAttackType() == ATTACKTYPE_CASTLECANNON
		|| GetAttackType() == ATTACKTYPE_SHELL
		|| GetAttackType() == ATTACKTYPE_CATFISH
		|| GetAttackType() == ATTACKTYPE_LADYBUGFAN
		|| GetAttackType() == ATTACKTYPE_SNOW
		|| GetAttackType() == ATTACKTYPE_STAFF1
		|| GetAttackType() == ATTACKTYPE_MADOGHOSTFIRE
		|| GetAttackType() == ATTACKTYPE_JAPANHEADER
		|| GetAttackType() == ATTACKTYPE_TOHANG
		|| GetAttackType() == ATTACKTYPE_SKULLBATFIRE		
		|| GetAttackType() == ATTACKTYPE_FIREGOBLIN
		|| GetAttackType() == ATTACKTYPE_POISON
		|| GetAttackType() == ATTACKTYPE_ICE
		|| GetAttackType() == ATTACKTYPE_KNIFE
		|| GetAttackType() == ATTACKTYPE_GREENFIRE
		|| GetAttackType() == ATTACKTYPE_BLACKINK
		|| GetAttackType() == ATTACKTYPE_BOOMERANG
		|| GetAttackType() == ATTACKTYPE_WINDBLADE
		|| GetAttackType() == ATTACKTYPE_SHELLFISHBOMB
		|| GetAttackType() == ATTACKTYPE_TREEMON
		|| GetAttackType() == ATTACKTYPE_VINE
		|| GetAttackType() == ATTACKTYPE_GHOSTFIRE
		|| GetAttackType() == ATTACKTYPE_SIMTORYONG
		|| GetAttackType() == ATTACKTYPE_KINGCUTTLEFISH
		|| GetAttackType() == ATTACKTYPE_CRANE
		|| GetAttackType() == ATTACKTYPE_MONKEY
		|| GetAttackType() == ATTACKTYPE_CURSEDEFENSE
		|| GetAttackType() == ATTACKTYPE_CURSEMOVESPEED
		|| GetAttackType() == ATTACKTYPE_BUTCHER
		|| GetAttackType() == ATTACKTYPE_STONEOLDMAN
		|| GetAttackType() == ATTACKTYPE_KINGCRAB
		|| GetAttackType() == ATTACKTYPE_FIREARROW
		|| GetAttackType() == ATTACKTYPE_LOBSTER
		|| GetAttackType() == ATTACKTYPE_DEADMESSENGER
		|| GetAttackType() == ATTACKTYPE_MASKMONK
		|| GetAttackType() == ATTACKTYPE_PERSONCANNON
		|| GetAttackType() == ATTACKTYPE_CANNON_MAGIC
		|| GetAttackType() == ATTACKTYPE_HEROSWORD
		|| GetAttackType() == ATTACKTYPE_BOW1
		|| GetAttackType() == ATTACKTYPE_GUN1
		|| GetAttackType() == ATTACKTYPE_STAFF2
		|| GetAttackType() == ATTACKTYPE_FOAM
		|| GetAttackType() == ATTACKTYPE_FIREBALL
		|| GetAttackType() == ATTACKTYPE_MORTAL
		|| GetAttackType() == ATTACKTYPE_WATERARROW
		|| GetAttackType() == ATTACKTYPE_STAFFWIND
		|| GetAttackType() == ATTACKTYPE_FLYVINE
		|| GetAttackType() == ATTACKTYPE_MAGICFIREBURN
		|| GetAttackType() == ATTACKTYPE_SKELLFISH
		|| GetAttackType() == ATTACKTYPE_FROZEN
		|| GetAttackType() == ATTACKTYPE_ICESTONE
		|| GetAttackType() == ATTACKTYPE_NEW_BOW1
		|| GetAttackType() == ATTACKTYPE_NEW_GUN1
		|| GetAttackType() == ATTACKTYPE_NEW_STAFF2
		|| GetAttackType() == ATTACKTYPE_ENERGYARROW
		|| GetAttackType() == ATTACKTYPE_SPEAR_MANA
		|| GetAttackType() == ATTACKTYPE_BLACKBOSS
		|| GetAttackType() == ATTACKTYPE_OCTOPUS
		|| GetAttackType() == ATTACKTYPE_OTOHIME
		|| GetAttackType() == ATTACKTYPE_BLACKSPIDER
		|| GetAttackType() == ATTACKTYPE_EVILEYE
		|| GetAttackType() == ATTACKTYPE_FROZENSORCERER
		|| GetAttackType() == ATTACKTYPE_CANNONMOL
		|| GetAttackType() == ATTACKTYPE_PRIEST
		|| GetAttackType() == ATTACKTYPE_MINEGIRL
		|| GetAttackType() == ATTACKTYPE_GREENTURTLE
		|| GetAttackType() == ATTACKTYPE_MAGICALRACCOON
		|| GetAttackType() == ATTACKTYPE_MAMARACCOON
		|| GetAttackType() == ATTACKTYPE_RACCOONTOWER
		|| GetAttackType() == ATTACKTYPE_CHICKENBIG
		|| GetAttackType() == ATTACKTYPE_MOONBLADE
		|| GetAttackType() == ATTACKTYPE_EMPERORARCHER
		|| GetAttackType() == ATTACKTYPE_NINJAMAN
		|| GetAttackType() == ATTACKTYPE_PIRATEARCHER
		|| GetAttackType() == ATTACKTYPE_EMPERORMASTER
		|| GetAttackType() == ATTACKTYPE_GREATWALLSOLDIER
		|| GetAttackType() == ATTACKTYPE_GREATWALLMAGICIAN
		|| GetAttackType() == ATTACKTYPE_CATRANGE
		|| GetAttackType() == ATTACKTYPE_GREATWALLSPIDER
		|| GetAttackType() == ATTACKTYPE_BEARTANG
		|| GetAttackType() == ATTACKTYPE_SUPERBEARTANG
		|| GetAttackType() == ATTACKTYPE_HALLOWEENGHOST
		|| GetAttackType() == ATTACKTYPE_CHRISTMASRANGE
		|| GetAttackType() == ATTACKTYPE_GREATWALLASURA
		|| GetAttackType() == ATTACKTYPE_FIGHTINGMENRANGE	// �ųʽ��Ǹ�
		|| GetAttackType() == ATTACKTYPE_FROZENQUEEN
		|| GetAttackType() == ATTACKTYPE_FAIRYRANGE		// �������Ǹ�(��)
		|| GetAttackType() == ATTACKTYPE_SNOWQUEEN		// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
		|| GetAttackType() == ATTACKTYPE_CLOWN
		)	
		
	{
		if(clAniInfo.IsInstant() && bHitDoneSwitch == false)
		{
			bHitDoneSwitch = true;

			if(pclCM->IsValidID(attackid) )
			{
				
				// by LEEKH 2007.12.28 - TRANSFORM
				// ���� ȿ����. 
				if(GetKindInfo()->clKIEffectInfo.siAttackEffect)
				{
					pclClient->PushEffect(GetKindInfo()->clKIEffectInfo.siAttackEffect, GetX(), GetY());
				}

				DecideAttackPoint(0, attackstartx, attackstarty);
				
				cltPos cltilestartpos(GetX(), GetY());
				cltPos cldotstartpos(attackstartx, attackstarty);
				
				cltPos cldotdestpos;
				pclCM->CR[attackid]->GetHitPoint(&cldotdestpos);
				
				SI32 bulletunique = pclClient->pclAttackTypeInfoManager->GetBulletUnique(GetAttackType());
				// by LEEKH 2007.12.24 - TRANSFORM - ���� ������ ���� ĳ���͸� ������.
				if( clTransFormInfo.bTransFormMode == true )
				{
					bulletunique = pclClient->pclAttackTypeInfoManager->GetBulletUnique(GetKindInfo()->clDefaultWeaponInfo.GetAttackType());
				}
				if(bulletunique)
				{			
					SI32 apower = GetApower();

					// ������ �����̸� �������� �Ҹ��Ѵ�. 
					if(GetAttackType() == ATTACKTYPE_STAFF1 || GetAttackType() == ATTACKTYPE_STAFF2 || GetAttackType() == ATTACKTYPE_NEW_STAFF2)
					{
						if ( pclKI->bSummonMall == FALSE )
						{
							if(pclCI->clIP.GetMana() >= 2)
							{
								pclCI->clIP.DecreaseMana(2);

								// Ŭ���̾�Ʈ�� �˷��ش�. 
								SetUpdateSwitch(UPDATE_IP, true, 0);
							}
							else
							{
								bfailswitch = true;
							}
						}
					}

					// ������ ���
					if (pclClient->GameMode == GAMEMODE_SERVER)
					{
						cltCharServer* pclchar = NULL;
						SI16 siBulletUnique = 0;
						SI32 pos = 0;
						SI16 siUseType = 0;		// 1:ĳ����, 2:��ȯ��
						BOOL bUseBullet = FALSE;

						// ������ ���
						if ( IsPC(siID) )
						{
							pclchar = (cltCharServer*)this;
							if ( NULL == pclchar )			return false;

							bUseBullet = GetBulletUnique_Char(&siBulletUnique);
							if(siBulletUnique > 0)		pos = pclCI->clCharItem.GetItemPosInEquip(siBulletUnique);
							siUseType = 1;
						}
					
						// ��ȯ���� ���
						if ( clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
						{
							SI32 siParentID = GetSummonParentID();
							if ( false == pclCM->IsValidID(siParentID) )	return false;

							pclchar = (cltCharServer*)pclCM->CR[siParentID];
							if ( NULL == pclchar )							return false;

							// ��ȯ���ΰ�� ��� ���� ������ ��ȯ���� �Ѿ��� �Ҹ�ȴ�
							cltKindInfo* pclki = NULL;
							if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
							{
								pclki = pclClient->pclKindInfoSet->pclSummonKI[GetKind()];
							}
							else
							{
								pclki = pclClient->pclKindInfoSet->pclKI[GetKind()];
							}

							if ( (pclki) && (pclki->siSummonEquip) )
							{
								bUseBullet = GetBulletUnique_Summon(GetSummonIndex(), &siBulletUnique);
								if(siBulletUnique > 0)		pos = pclchar->pclCI->clSummonInfo.GetItemPosInEquip(GetSummonIndex(), siBulletUnique);
								siUseType = 2;
							}
						}

						if(bUseBullet)
						{
							if(siBulletUnique == ITEMUNIQUE(13601) || siBulletUnique == ITEMUNIQUE(13600))
							{
								//�Ⱓ�� �������� ��쿡�� ������� �ʵ���. [����]
							}
							else
							{
								if (pos < 0 && pos >= MAX_SHAPE_ITEM)		return false;

								switch(siUseType)
								{
								case 1:		// ĳ����
									{
										cltItem clitem;
										clitem.Set( &pclCI->clCharItem.clItem[pos]);
										clitem.SetItemNum(1);

										if( pclchar->UseItem(clitem) )
										{
											while( pclchar->clBulletUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, pos) == false )
											{
												pclchar->BulletUseReserveAction();
											}
											cltItem *pclFrom = &pclCI->clCharItem.clItem[ pos ];
											if( pclFrom->siItemNum == 1 )		{	pclchar->BulletUseReserveAction();	}

											pclFrom->Decrease(1);

											// Ŭ���̾�Ʈ�� ����� ������ ������. 
											cltGameMsgResponse_PersonItemInfo clinfo( pos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
											cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
											SendNetMsg((sPacketHeader*)&clMsg);
										}
									}
									break;

								case 2:		// ��ȯ��
									{
										cltItem* pclItem = pclchar->pclCI->clSummonInfo.GetSummonEquipItem(GetSummonIndex(), pos);
										if( pclItem )
										{
											cltItem clitem;
											clitem.Set( pclItem );
											clitem.SetItemNum(1);

											if( pclchar->UseItem(clitem) )
											{
												while( pclchar->clSummonBulletUseReserveInfo.Push( GetSummonIndex(), clitem.siUnique, -clitem.siItemNum, pos) == false )
												{
													pclchar->BulletUseReserveAction();
												}
												cltItem *pclFrom = pclItem;
												if( pclFrom->siItemNum == 1 )		{	pclchar->BulletUseReserveAction();	}

												pclFrom->Decrease(1);

												// Ŭ���̾�Ʈ�� ����� ������ ������. 
												cltGameMsgResponse_SummonChangeItem clinfo( GetSummonIndex(), pos, pclFrom );
												cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clinfo), (BYTE*)&clinfo);
												pclchar->SendNetMsg((sPacketHeader*)&clMsg);
												
											}
										}
									}
									break;
								}
							}
						}
					}
					
					if(bfailswitch == false)
					{
						

						// ������� ��쿡��. 
						if(IsPC(GetCharUnique()))
						{
							// �ּ� �Ÿ����� ���� �Ұ����� ĳ������ ��쿡�� 
							if(pclClient->pclAttackTypeInfoManager->IsAtb(GetAttackType(), ATTACKTYPE_ATB_MINRANGE) && IsInMinRange(attackid, 1)==TRUE)
							{
								apower = max(1, apower * 7 / 10);
							}
						}

						// ĳ���Ϳ� ���ݴ�� ������ ���� �������� �Ѵ�. 
						if(GetMapIndex() == clAttackTarget.clPos.GetMapIndex()
						&& pclMap->IsInMapArea(clAttackTarget.clPos.siX, clAttackTarget.clPos.siY) == true)
						{
							// [����] ��ȯ���� �⺻ ���� �����θ� ������ �ֵ���
							if ( pclClient->pclCM->IsValidID(GetSummonParentID( )) ) 
							{
								pclClient->pclLog->LogPrint( TEXT("����Ÿ�� : %d\n"), GetAttackType() );
								bulletunique = pclClient->pclAttackTypeInfoManager->GetBulletUnique(GetKindInfo()->clDefaultWeaponInfo.GetAttackType());
							}

							{
								id = pclClient->pclBulletManager->SetBullet(pclMap, bulletunique, 0,  
																			siID, apower, 
																			&cltilestartpos,
																			&cldotstartpos, 
																			&clAttackTarget,
																			&cldotdestpos);
							}
						}
					}
					
				}
			}

		}
	}
	// ���� 
	else if( GetAttackType() == ATTACKTYPE_SELFBOMB)
	{
		if(clAniInfo.IsInstant() == false || bHitDoneSwitch == true)return false;
		bHitDoneSwitch = true;

		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			((cltCharServer*)this)->SelfBombAction();
		}
	}
	else
	{
		//cyj MsgBox(TEXT("CharAttack"), TEXT("kind:%s atb:%d"), pclKI->GetName(), GetAttackType());
	}

	return true;
}

bool cltCharCommon::Fire()
{
	SetAnimation(siCurrentAttackType);
	if(DoAnimationDelay() == FALSE)return false;

	// Ÿ�������� ĳ������ ��ġ�� ���� ������ �־�� �Ѵ�. 
	if(GetMapIndex() == clAttackTarget.clPos.GetMapIndex())
	{
		FireSub();	// ���� Ÿ�� �Լ�. 
	}
	
	if(clAniInfo.GetAniStep() == 0 )//&& clAniInfo.siRetryNum > 0 )
	{
		bHitDoneSwitch	= false;
		bBusySwitch		= false;
		
		return true;
	}
	else return false;
	
}

BOOL cltCharCommon::GetBulletUnique_Char(SI16* psiBulletUnique)
{
	*psiBulletUnique = 0;

	if(GetAttackType() == ATTACKTYPE_BOW || GetAttackType() == ATTACKTYPE_BOW1 || GetAttackType() == ATTACKTYPE_NEW_BOW1)
	{
		// �Ϲ� ȭ��
		if( pclCI->clCharItem.GetItemNumInEquip(ITEMUNIQUE(7850)) > 0 )		*psiBulletUnique = ITEMUNIQUE(7850);
		// ���� ȭ��
		if( pclCI->clCharItem.GetItemNumInEquip(ITEMUNIQUE(13600)) > 0 )	*psiBulletUnique = ITEMUNIQUE(13600);

		return TRUE;
	}

	if(GetAttackType() == ATTACKTYPE_GUN || GetAttackType() == ATTACKTYPE_GUN1 || GetAttackType() == ATTACKTYPE_NEW_GUN1)
	{
		// �Ϲ� �Ѿ�
		if( pclCI->clCharItem.GetItemNumInEquip(ITEMUNIQUE(7855)) > 0 )		*psiBulletUnique = ITEMUNIQUE(7855);
		// ���� �Ѿ�
		if( pclCI->clCharItem.GetItemNumInEquip(ITEMUNIQUE(13601)) > 0)		*psiBulletUnique = ITEMUNIQUE(13601);

		return TRUE;
	}

	return FALSE;
}

BOOL cltCharCommon::GetBulletUnique_Summon(SI32 siSummonIndex, SI16* psiBulletUnique)
{
	*psiBulletUnique = 0;

	/*
	cltSummon* pclSummon = pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if( pclSummon == NULL )			return FALSE;
	*/
	
	SI32 siParentID = GetSummonParentID();
	if ( false == pclCM->IsValidID( siParentID ) )
	{
		return FALSE;
	}
	
	cltCharCommon* pclParentChar = (cltCharCommon*)pclCM->CR[siParentID];
	if ( NULL == pclParentChar )
	{
		return FALSE;
	}

	cltSummonInfo* pclSummonInfo = &pclParentChar->pclCI->clSummonInfo;
	if( pclSummonInfo == NULL )		return FALSE;

	
	//SI32 siAttackType = pclSummon->siAttackType;
	SI32 siAttackType = GetAttackType();

	if(siAttackType == ATTACKTYPE_BOW || siAttackType == ATTACKTYPE_BOW1 || siAttackType == ATTACKTYPE_NEW_BOW1)
	{
		// �Ϲ� ȭ��
		if( pclSummonInfo->GetHaveItemNumFromItemUnique(siSummonIndex, ITEMUNIQUE(7850)) > 0 )
		{
			*psiBulletUnique = ITEMUNIQUE(7850);
			return TRUE;
		}

		// ���� ȭ��
		if( pclSummonInfo->GetHaveItemNumFromItemUnique(siSummonIndex, ITEMUNIQUE(13600)) > 0 )
		{
			SI32 siBulletPosition = -1;
			siBulletPosition = pclSummonInfo->GetItemPosInEquip(siSummonIndex, ITEMUNIQUE(13600));
			if ( 0 <= siBulletPosition )
			{
				cltItem* pBullet = pclSummonInfo->GetSummonEquipItem( siSummonIndex, siBulletPosition );
				if ( NULL != pBullet )
				{
					if ( pclClient->GameMode == GAMEMODE_SERVER )
					{
						SI32 siUseDay = -1;
						((cltServer*)pclClient)->GetItemUseAbleDay( pBullet, &siUseDay );
						if ( 0 <= siUseDay )
						{
							*psiBulletUnique = ITEMUNIQUE(13600);
							return TRUE;
						}
					}
					else
					{
						*psiBulletUnique = ITEMUNIQUE(13600);
						return TRUE;
					}
				}
			}
		}

		return TRUE;
	}

	if(siAttackType == ATTACKTYPE_GUN || siAttackType == ATTACKTYPE_GUN1 || siAttackType == ATTACKTYPE_NEW_GUN1)
	{
		// �Ϲ� �Ѿ�
		if( pclSummonInfo->GetHaveItemNumFromItemUnique(siSummonIndex, ITEMUNIQUE(7855)) > 0 )
		{
			*psiBulletUnique = ITEMUNIQUE(7855);
			return TRUE;
		}

		// ���� �Ѿ�
		if( pclSummonInfo->GetHaveItemNumFromItemUnique(siSummonIndex, ITEMUNIQUE(13601)) > 0)
		{
			SI32 siBulletPosition = -1;
			siBulletPosition = pclSummonInfo->GetItemPosInEquip(siSummonIndex, ITEMUNIQUE(13601));
			if ( 0 <= siBulletPosition )
			{
				cltItem* pBullet = pclSummonInfo->GetSummonEquipItem( siSummonIndex, siBulletPosition );
				if ( NULL != pBullet )
				{
					if ( pclClient->GameMode == GAMEMODE_SERVER )
					{
						SI32 siUseDay = -1;
						((cltServer*)pclClient)->GetItemUseAbleDay( pBullet, &siUseDay );
						if ( 0 <= siUseDay )
						{
							*psiBulletUnique = ITEMUNIQUE(13601);
							return TRUE;
						}
					}
					else
					{
						*psiBulletUnique = ITEMUNIQUE(13601);
						return TRUE;
					}
				}
			}
		}

		return TRUE;
	}

	return FALSE;
}

