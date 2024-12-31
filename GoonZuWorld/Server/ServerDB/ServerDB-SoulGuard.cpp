#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../CommonLogic/SoulGuardMgr/SoulGuardMgr.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-SoulGuard.h"


#include "Msg/MsgType-SoulGuard.h"


void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_CREATE(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuardCreate* pclMsg = (sDBResponse_SoulGuardCreate*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	// 1=���, 2=������
	if ( (1 != pclMsg->m_siPosType) && (2 != pclMsg->m_siPosType) )
	{
		return;
	}

	// �����ҿ� ������ ��� ������ ����� �ٽ� �޴´�
	if ( 2 == pclMsg->m_siPosType )
	{
		sDBRequest_SoulGuardHouse_Get clHouseGet( pclMsg->m_siPersonID );
		SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clHouseGet );
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �⺻������ ��ȯ�� �ȵ� ���·� �����ִ´�
	SI16 siSoulGuardStatus = pclMsg->m_siStatus;
	if ( SOULGUARD_STATUS_IN != siSoulGuardStatus )
	{
		siSoulGuardStatus = SOULGUARD_STATUS_IN;
	}

	// ���� ĳ���͸� �����ϰ�
	pclChar->pclSoulGuard->SetSoulGuard( pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip );

	// �ϴ� ������ Ŭ��� �����ش�
	cltGameMsgResponse_SoulGuardGet clGetInfo(  pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip  );
	cltMsg clGetMsg( GAMEMSG_RESPONSE_SOULGUARD_GET, sizeof(clGetInfo), (BYTE*)&clGetInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clGetMsg );

	// ��ȣ������ ó�� ������ �ٷ� ��ȯ�� ���·� �ȴ�
	SI32 siSoulGuardCharID = pclChar->CreateSoulGuard( pclChar->pclSoulGuard );
	if ( pclCM->IsValidID(siSoulGuardCharID) )
	{
		pclChar->siMySoulGuardUnique = siSoulGuardCharID;
	}

	// ��ȯ�� ������ �����ش� Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardStatusInOut clStatusInfo( pclChar->pclSoulGuard->GetSoulGuardID(), pclChar->pclSoulGuard->GetStatus(), pclChar->siMySoulGuardUnique );
	cltMsg clStatusMsg( GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT, sizeof(clStatusInfo), (BYTE*)&clStatusInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clStatusMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_GET(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuardGet* pclMsg = (sDBResponse_SoulGuardGet*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	
	// Ȥ�� ������ ���ٸ�
	if ( 1 != pclMsg->m_siResult )
	{
		//return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �⺻������ ��ȯ�� �ȵ� ���·� �����ִ´�
	SI16 siSoulGuardStatus = pclMsg->m_siStatus;
	if ( SOULGUARD_STATUS_IN != siSoulGuardStatus )
	{
		siSoulGuardStatus = SOULGUARD_STATUS_IN;
	}

	// ���� ĳ���� ������ �ְ�
	pclChar->pclSoulGuard->SetSoulGuard( pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip );

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardGet clGetInfo( pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip );
	cltMsg clGetMsg( GAMEMSG_RESPONSE_SOULGUARD_GET, sizeof(clGetInfo), (BYTE*)&clGetInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clGetMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_FELLOWSHIP_SET(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuard_FellowShipSet* pclMsg = (sDBResponse_SoulGuard_FellowShipSet*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclMsg->m_siSoulGuardID )
	{
		return;
	}

	// ���� ĳ���� ������ �ְ�
	pclChar->pclSoulGuard->SetFellowShip( pclMsg->m_siFellowShip );

	// ģȭ���� ����Ǿ����� �׿� ���� �ɷ�ġ�� ����ȴ� �׷��� �Ķ��Ÿ �ڽ��� ������ �����ش�
	pclChar->SetParametaBoxAction( true );

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardFellowShipSet clInfo( pclMsg->m_siSoulGuardID, pclMsg->m_siFellowShip );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_FELLOWSHIPSET, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_CHANGE_NAME(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuard_Change_Name* pclMsg = (sDBResponse_SoulGuard_Change_Name*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclMsg->m_siSoulGuardID )
	{
		return;
	}

	// ���� ĳ���Ϳ� ������ �ְ�
	pclChar->pclSoulGuard->SetName( pclMsg->m_szChangeName );

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardChangeName clInfo( pclMsg->m_siSoulGuardID, pclMsg->m_szChangeName );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_CHANGENAME, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_DEAD(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuard_Dead* pclMsg = (sDBResponse_SoulGuard_Dead*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// Ǯ���ִ� ����� ���� ��ȯ�� ĳ���͸� ������ �����
	if ( SOULGUARD_DEAD_MODE_FREE == pclMsg->m_siDeadMode )
	{
		// ��ȯ�Ǿ�������� �� �ɸ��ʹ� �����ش�
		pclChar->DeleteSoulGuard();
	}
	else
	{
		pclChar->siMySoulGuardUnique = 0;
	}
	
	// ���� ĳ���Ϳ� ������ �ְ�
	pclChar->pclSoulGuard->InitExceptHouse();

	// Ŭ���̾�Ʈ���� �����ش�
	cltGameMsgResponse_SoulGuardDead clInfo( pclMsg->m_siDeadMode );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_DEAD, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_GET(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuardHouse_Get* pclMsg = (sDBResponse_SoulGuardHouse_Get*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// ������ 0�� ���϶�� 2�� �־��ش�
	if ( 0 >= pclMsg->m_siHouseNum )
	{
		cltItem clTempItem;
		clTempItem.Init();

		sDBRequest_SoulGuardHouse_Create clHouseCreate( pclMsg->m_siPersonID, 2, 0, &clTempItem );
		SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clHouseCreate );
	}

	// ������ ĳ���� ������ �� ��
	pclChar->pclSoulGuard->m_clHouse.Set( pclMsg->m_siHouseNum, pclMsg->m_siSoulGuardID, pclMsg->m_sisoulGuardKind );

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardHouse_Get clInfo( pclMsg->m_siHouseNum, pclMsg->m_siSoulGuardID, pclMsg->m_sisoulGuardKind );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_HOUSE_GET, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_CHANGE(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuardHouse_Change* pclMsg = (sDBResponse_SoulGuardHouse_Change*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// ��ȣ ���� ��ϵ� ���� �Ǿ����Ƿ� �� �ٽð����´�
	sDBRequest_SoulGuardHouse_Get clHouseGet( pclMsg->m_siPersonID );
	SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clHouseGet );
	

    // Ȥ�� ���� ��ȣ������ ��ȯ�Ǿ��� ������ �����Ƿ� �����
	pclChar->DeleteSoulGuard();
	
	// �⺻������ ��ȯ�� �ȵ� ���·� �����ִ´�
	SI16 siSoulGuardStatus = pclMsg->m_siStatus;
	if ( SOULGUARD_STATUS_IN != siSoulGuardStatus )
	{
		siSoulGuardStatus = SOULGUARD_STATUS_IN;
	}

	// ������ �������ְ�
	pclChar->pclSoulGuard->SetSoulGuard( pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip );
	
	// �ϴ� ������ Ŭ��� �����ش�
	cltGameMsgResponse_SoulGuardGet clGetInfo(  pclMsg->m_siSoulGuardID, pclMsg->m_szName, siSoulGuardStatus, pclMsg->m_siKind, pclMsg->m_siLimitDateVary, pclMsg->m_siFellowShip  );
	cltMsg clGetMsg( GAMEMSG_RESPONSE_SOULGUARD_GET, sizeof(clGetInfo), (BYTE*)&clGetInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clGetMsg );

	// ��ȣ������ ó�� ������ �ٷ� ��ȯ�� ���·� �ȴ�
	SI32 siSoulGuardCharID = pclChar->CreateSoulGuard( pclChar->pclSoulGuard );
	if ( pclCM->IsValidID(siSoulGuardCharID) )
	{
		pclChar->siMySoulGuardUnique = siSoulGuardCharID;
	}

	// ��ȯ�� ������ �����ش� Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardStatusInOut clStatusInfo( pclChar->pclSoulGuard->GetSoulGuardID(), pclChar->pclSoulGuard->GetStatus(), pclChar->siMySoulGuardUnique );
	cltMsg clStatusMsg( GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT, sizeof(clStatusInfo), (BYTE*)&clStatusInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clStatusMsg );
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SOULGUARD_HOUSE_CREATE(sPacketHeader* pPacket)
{
	sDBResponse_SoulGuardHouse_Create* pclMsg = (sDBResponse_SoulGuardHouse_Create*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// ������ ĳ���� ������ �� ��
	if ( (0 <= pclMsg->m_siHouseNum) && (MAX_SOULGUARD_HOUSE_NUM >= pclMsg->m_siHouseNum) )
	{
		pclChar->pclSoulGuard->m_clHouse.SetMaxHaveHouseNum( pclMsg->m_siHouseNum );
	}

	// ���� ������ ����
	if ( (PERSONITEM_INV0 <= pclMsg->m_siLeftItemPos ) && ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) > pclMsg->m_siLeftItemPos) )
	{
		pclChar->pclCI->clCharItem.clItem[pclMsg->m_siLeftItemPos].Set( &pclMsg->m_clLeftItem );
	}

	// Ŭ���̾�Ʈ�� �����ش�
	cltGameMsgResponse_SoulGuardHouse_Create clInfo( pclMsg->m_siHouseNum, pclMsg->m_siLeftItemPos, &pclMsg->m_clLeftItem );
	cltMsg clMsg( GAMEMSG_RESPONSE_SOULGUARD_HOUSE_CREATE, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
}