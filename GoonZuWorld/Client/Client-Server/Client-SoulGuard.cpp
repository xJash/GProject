#include "../Client.h"
#include "../Music\Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-SoulGuard.h"
#include "../CommonLogic/SoulGuardMgr/SoulGuardMgr.h"

#include "Char/CharManager/CharManager.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"


void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardStatusInOut* pclinfo = (cltGameMsgResponse_SoulGuardStatusInOut*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclinfo->m_siSoulGuardID )
	{
		return;
	}

	pclChar->pclSoulGuard->SetStatus( pclinfo->m_siStatus );

	pclChar->siMySoulGuardUnique = pclinfo->m_siSoulGuardCharUnique;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_FELLOWSHIPSET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardFellowShipSet* pclinfo = (cltGameMsgResponse_SoulGuardFellowShipSet*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclinfo->m_siSoulGuardID )
	{
		return;
	}

	// ĳ���� ������ �ְ�
	pclChar->pclSoulGuard->SetFellowShip( pclinfo->m_siFellowShip );

	// â�� ���� ��Ų��

	// �ӽ� �α�
	pclLog->LogPrint( TEXT("FellowShip : %d\n"), pclinfo->m_siFellowShip );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_CHANGENAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardChangeName* pclinfo = (cltGameMsgResponse_SoulGuardChangeName*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	if ( pclChar->pclSoulGuard->GetSoulGuardID() != pclinfo->m_siSoulGuardID )
	{
		return;
	}

	// �̸��� ������ �ش�
	pclChar->pclSoulGuard->SetName( pclinfo->m_szChangeName );

	// ����Ǿ��ٴ� �޽���
	NTCHARString32	strTitle	= TEXT("");
	NTCHARString128	strText		= GetTxtFromMgr( 838 );

	m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_DEAD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardDead* pclinfo = (cltGameMsgResponse_SoulGuardDead*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �ܼ��� �ʱ�ȭ ���ָ� �ȴ�
	pclChar->pclSoulGuard->InitExceptHouse();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardGet* pclinfo = (cltGameMsgResponse_SoulGuardGet*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �ٲ� ��ȣ���� ���� �ֱ�
	pclChar->pclSoulGuard->SetSoulGuard( pclinfo->m_siSoulGuardID, pclinfo->m_szName, pclinfo->m_siStatus, pclinfo->m_siKind, pclinfo->m_siLimitDateVary, pclinfo->m_siFellowShip );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_HOUSE_GET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardHouse_Get* pclinfo = (cltGameMsgResponse_SoulGuardHouse_Get*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	pclChar->pclSoulGuard->m_clHouse.Set( pclinfo->m_siMaxHaveHouseNum, pclinfo->m_siSoulGuardID, pclinfo->m_siSoulGuardKind );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_SOULGUARD_HOUSE_CREATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SoulGuardHouse_Create* pclinfo = (cltGameMsgResponse_SoulGuardHouse_Create*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == pclChar->pclSoulGuard )
	{
		return;
	}

	// �ִ� ��� ������ ������ ����
	if ( (0 <= pclinfo->m_siMaxHaveHouseNum) && (MAX_SOULGUARD_HOUSE_NUM >= pclinfo->m_siMaxHaveHouseNum) )
	{
		pclChar->pclSoulGuard->m_clHouse.SetMaxHaveHouseNum( pclinfo->m_siMaxHaveHouseNum );
	}
	
	// ���� ������ ����
	if ( (PERSONITEM_INV0 <= pclinfo->m_siLeftItemPos ) && ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) > pclinfo->m_siLeftItemPos) )
	{
		pclChar->pclCI->clCharItem.clItem[pclinfo->m_siLeftItemPos].Set( &pclinfo->m_clLeftItem );
	}
}