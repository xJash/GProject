#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../CommonLogic/SoulGuardMgr/SoulGuardMgr.h"

#include "../../common/Order/order.h"
#include "../../common/JWLib/IsCorrectID/IsCorrectID.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-SoulGuard.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-SoulGuard.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_SOULGUARD_STATUSINOUT(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SoulGuardStatusInOut* pclinfo = (cltGameMsgRequest_SoulGuardStatusInOut*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclChar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclChar) )
				return;
		}
	}

	// �׾����� ƨ���
	if ( FALSE == pclCM->IsAlive(id) )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( TRUE == pclChar->pclSoulGuard->IsEmpty() )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclinfo->m_siSoulGuardID )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetStatus() == pclinfo->m_siStatus )
	{
		return;
	}

	// ���� ���¶�� �ȵ�
	if ( pclChar->pclSoulGuard->GetStatus() == SOULGUARD_STATUS_DEAD )
	{
		return;
	}

	switch ( pclinfo->m_siStatus )
	{
	// ��ȣ���� �ֱ�
	case SOULGUARD_STATUS_IN:
		{
			pclChar->DeleteSoulGuard();
		}
		break;

	// ��ȣ���� ������
	case SOULGUARD_STATUS_OUT:
		{
			SI32 siSoulGuardCharID = pclChar->CreateSoulGuard( pclChar->pclSoulGuard );
			if ( false == pclCM->IsValidID(siSoulGuardCharID) )
			{
				return;
			}

			pclChar->siMySoulGuardUnique = siSoulGuardCharID;
		}
		break;
	}

	// ��ȣ ������ �������� �ɷ�ġ�� �ٽ� ��� �ϵ��� �Ѵ�
	pclChar->SetParametaBoxAction( true );

	// Ŭ���̾�Ʈ�� �ٽ� �����ش�
	cltGameMsgResponse_SoulGuardStatusInOut clInfo( pclChar->pclSoulGuard->GetSoulGuardID(), pclChar->pclSoulGuard->GetStatus(), pclChar->siMySoulGuardUnique );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SOULGUARD_CHANGENAME(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SoulGuardChangeName* pclinfo = (cltGameMsgRequest_SoulGuardChangeName*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// �׾����� ƨ���
	if ( FALSE == pclCM->IsAlive(id) )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( TRUE == pclChar->pclSoulGuard->IsEmpty() )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclinfo->m_siSoulGuardID )
	{
		return;
	}

	// ���� ���¶�� �ȵ�
	if ( pclChar->pclSoulGuard->GetStatus() == SOULGUARD_STATUS_DEAD )
	{
		return;
	}

	// �̸��� �����´�
	TCHAR	szOriginalName[MAX_SOULGUARD_NAME]	= TEXT("");
	TCHAR	szChangeName[MAX_SOULGUARD_NAME]	= TEXT("");

	StringCchCopy( szOriginalName,	MAX_SOULGUARD_NAME,	pclChar->pclSoulGuard->GetName() );
	StringCchCopy( szChangeName,	MAX_SOULGUARD_NAME,	pclinfo->m_szChangeName );

	// ���� ���� ��������
	size_t sizeLength = 0;
	StringCchLength( szChangeName, MAX_SOULGUARD_NAME, &sizeLength );

	// ���ڿ��� ���̰� 0�϶�
	if ( 0 == sizeLength )
	{
		return;
	}

	// ���� �̸��� �����Ҷ�
	if ( 0 == _tcscmp(szOriginalName, szChangeName) )
	{
		return;
	}

	// �弳���͸� ����
	m_pCAbuseFilter->CheckAbuse( szChangeName );

	// ��ȿ�� �̸����� �˻��Ѵ�
	if ( FALSE == IsCorrectID(szChangeName) )
	{
		return;
	}

	// DB�� ��û�Ѵ�
	sDBRequest_SoulGuard_Change_Name clMsg( pclChar->pclCI->GetPersonID(), pclChar->pclSoulGuard->GetSoulGuardID(), szChangeName );
	SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SOULGUARD_DEAD(cltMsg* pclMsg, SI32 id )
{
	// �̰��� ��ȣ���� Ǯ���ֱ� �̴�

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// �׾����� ƨ���
	if ( FALSE == pclCM->IsAlive(id) )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( TRUE == pclChar->pclSoulGuard->IsEmpty() )
	{
		return;
	}

	// ���� ���¶�� �ȵ�
	if ( pclChar->pclSoulGuard->GetStatus() == SOULGUARD_STATUS_DEAD )
	{
		return;
	}

	// DB�� ��û�Ѵ�
	sDBRequest_SoulGuard_Dead clMsg( pclChar->pclCI->GetPersonID(), pclChar->pclSoulGuard->GetSoulGuardID(), SOULGUARD_DEAD_MODE_FREE );
	SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SOULGUARD_HOUSE_CHANGE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SoulGuardHouse_Change* pclinfo = (cltGameMsgRequest_SoulGuardHouse_Change*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	SI32 siGetelectIndex = pclinfo->m_siSelectIndex;
	if ( (0 > siGetelectIndex) || (MAX_SOULGUARD_HOUSE_NUM <= siGetelectIndex) )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// �׾����� ƨ���
	if ( FALSE == pclCM->IsAlive(id) )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	SI16 siGetKindUnique = pclChar->pclSoulGuard->m_clHouse.GetKindUniqueFromIndex( siGetelectIndex );
	if ( false == pclKindInfoSet->IsValidKind(siGetKindUnique) )
	{
		return;
	}

	SI32 siGetSoulGuardID = pclChar->pclSoulGuard->m_clHouse.GetSoulGuardIDFromIndex( siGetelectIndex );
	if ( 0 >= siGetSoulGuardID )
	{
		return;
	}

	SI32 siCharSoulGuardID = pclChar->pclSoulGuard->GetSoulGuardID();
	
	sDBRequest_SoulGuardHouse_Change clMsg( pclChar->pclCI->GetPersonID(), siCharSoulGuardID, siGetSoulGuardID );
	SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
	
}
void cltServer::DoMsg_GAMEMSG_REQUEST_SOULGUARD_HOUSE_CREATE(cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// �׾����� ƨ���
	if ( FALSE == pclCM->IsAlive(id) )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �̹� �ִ� �����϶�
	SI32 siMaxHouseNum = pclChar->pclSoulGuard->m_clHouse.GetMaxHaveHouseNum();
	if ( MAX_SOULGUARD_HOUSE_NUM <= siMaxHouseNum )
	{
		return;
	}

	// �����̿�� ������ ��ġ ã��(�Բ� ����üũ�� �Ѵ�)
	SI16 siItemPos = -1;
	for ( SI16 siPosition=PERSONITEM_INV0; siPosition<(PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON); siPosition++ )
	{
		if ( Const_SoulGuardHouse_ItemUnique == pclChar->pclCI->clCharItem.clItem[siPosition].siUnique )
		{
			if ( Const_SoulGuardHouse_ItemNum <= pclChar->pclCI->clCharItem.clItem[siPosition].siItemNum )
			{
				siItemPos = siPosition;
				break;
			}
		}
	}

	// ��ġ�� ��ã�� ���� �������� ���ٰ� �����Ѵ�
	if ( PERSONITEM_INV0 > siItemPos )
	{
		return;
	}

	// �Ҹ��ų ������ ����
	cltItem clTicketItem;

	clTicketItem.Init();
	clTicketItem.siUnique	= Const_SoulGuardHouse_ItemUnique;
	clTicketItem.siItemNum	= Const_SoulGuardHouse_ItemNum;

	// ������ +1���ش�
	siMaxHouseNum = siMaxHouseNum + 1;

	sDBRequest_SoulGuardHouse_Create clMsg( pclChar->pclCI->GetPersonID(), siMaxHouseNum, siItemPos, &clTicketItem );
	SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
		
}
