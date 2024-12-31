
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../CommonLogic/Marriage/MarriageManager.h"
#include "../../CommonLogic/Marriage/WeddingManager.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Wedding.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "MsgRval-Define.h"
#include "Msg/MsgType-Wedding.h"

void cltServer::DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE_LIST_GET(sPacketHeader* pPacket)
{
	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	sDBResponse_WeddingReserveListGet* pclMsg = (sDBResponse_WeddingReserveListGet*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	cltWeddingReserveUnit* pclUnit = NULL;

	SI16 siYear		= 0;
	SI16 siMonth	= 0;
	SI16 siDay		= 0;
	SI16 siHour		= 0;

	for ( SI32 siIndex=0; siIndex<WEDDING_RESERVE_LIST_NUM; siIndex++ )
	{
		siYear	= pclMsg->m_clReserveList[siIndex].m_stReserveTime.wYear;
		siMonth	= pclMsg->m_clReserveList[siIndex].m_stReserveTime.wMonth;
		siDay	= pclMsg->m_clReserveList[siIndex].m_stReserveTime.wDay;
		siHour	= pclMsg->m_clReserveList[siIndex].m_stReserveTime.wHour;
				
		pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siYear, siMonth, siDay, siHour );
		if ( NULL == pclUnit )
		{
			continue;
		}

		pclUnit->Set( &pclMsg->m_clReserveList[siIndex] );
	}
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE(sPacketHeader* pPacket)
{
	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	sDBResponse_WeddingReserve* pclMsg = (sDBResponse_WeddingReserve*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	// ������ �ƴϸ�� ����
	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI16 siYear		= pclMsg->m_stReserveTime.wYear;
	SI16 siMonth	= pclMsg->m_stReserveTime.wMonth;
	SI16 siDay		= pclMsg->m_stReserveTime.wDay;
	SI16 siHour		= pclMsg->m_stReserveTime.wHour;

	// ���� �����ϸ� ����Ʈ�� �������ְ�
	if ( 1 == pclMsg->m_siResult )
	{
		cltWeddingReserveUnit* pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siYear, siMonth, siDay, siHour );
		if ( pclUnit )
		{
			pclUnit->Set( pclMsg->m_siReserveNum,	 
						pclMsg->m_siPersonID,		pclMsg->m_szPersonName, 
						pclMsg->m_siMatePersonID,	pclMsg->m_szMateName,
						pclMsg->m_stReserveTime
						);
		}
	}

	// �������� �����Ѵ�
	cltItem			clGiveItem;
	SI16			siRare		= 0;
	clGiveItem.Init();

	BOOL			bMakeItem	= pclItemManager->MakeRandItemUnique( Const_Wedding_FullDress_Unique, &clGiveItem, 0, 0, &siRare);
	clGiveItem.SetItemNum( Const_Wedding_FullDress_Num );

	BOOL			bGiveItem	= FALSE;

	// ĳ���� 1���� �����Ѵ�
	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( pclChar )
	{
		if ( GIVEITEM_RESULT_SUCCESS == pclChar->GiveItem(Const_Wedding_FullDress_Unique, Const_Wedding_FullDress_Num, INPUTITEMPERSON_OPTION_WEDDING_FULLDRESS, 0) )
		{
			bGiveItem = TRUE;
		}

		// ���� ����
		pclChar->pclCI->clBank.SetMoney( pclMsg->m_gmLeftBankMoney );
	}

	if ( (FALSE == bGiveItem) && (TRUE == bMakeItem) )
	{
		SendPostOfficeItemToPerson( pclMsg->m_siPersonID, &clGiveItem, NULL);
	}

	// ĳ���� 2���� �����Ѵ�
	bGiveItem = FALSE;

	SI32			siMateCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siMatePersonID );
	cltCharServer*	pclMateChar		= pclCM->GetCharServer( siMateCharID );
	if ( pclMateChar )
	{
		if ( GIVEITEM_RESULT_SUCCESS == pclMateChar->GiveItem(Const_Wedding_FullDress_Unique, Const_Wedding_FullDress_Num, INPUTITEMPERSON_OPTION_WEDDING_FULLDRESS, 0) )
		{
			bGiveItem = TRUE;
		}

		// ����ڿ��Ե� ���� �޽��� �����ش�
		cltGameMsgResponse_WeddingReserve clinfo( pclMsg->m_siResult, siYear, siMonth, siDay, siHour, 0 );
		cltMsg clMsg( GAMEMSG_RESPONSE_WEDDING_RESERVE, sizeof(clinfo), (BYTE*)&clinfo );
		pclMateChar->SendNetMsg( (sPacketHeader*)&clMsg );
	}

	if ( (FALSE == bGiveItem) && (TRUE == bMakeItem) )
	{
		SendPostOfficeItemToPerson( pclMsg->m_siMatePersonID, &clGiveItem, NULL);
	}

	// �Ʒ����� ���ʹ� ĳ���Ϳ� �ش��ϹǷ� ĳ���Ͱ� ������ ����
	if ( NULL == pclChar )
	{
		return;
	}

	// ���� ������ ���� ����
	cltGameMsgResponse_WeddingReserve clinfo( pclMsg->m_siResult, siYear, siMonth, siDay, siHour, pclMsg->m_gmLeftBankMoney );
	cltMsg clMsg( GAMEMSG_RESPONSE_WEDDING_RESERVE, sizeof(clinfo), (BYTE*)&clinfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );

	if ( IsWhereServiceArea(ConstSwitch_NewLog) )
	{
		// param1 = ���� ��
		// param2 = ���� ��
		// param3 = ���� ��
		// param4 = ���� ��

		SendLog_WriteLogToDB( LOGCOMMAND_TYPE_FAMILY, LOGCOMMAND_INDEX_FAMILY_RESERVE_WEDDING, 
			0, NULL, NULL, pclMsg->m_siPersonID, pclMsg->m_gmReserveMoney, pclMsg->m_gmLeftBankMoney, NULL, 0, 0, 0, 0, 0, 0, 
			siYear, siMonth, siDay, siHour, 0, NULL, NULL);
	}
	//
	/*
	//===============================================================================================
	// ���ฮ��Ʈ ��ü�� �ٽ� �����ش�
	//===============================================================================================
	cltGameMsgResponse_WeddingSimpleListGet	clSimpleList;
	cltWeddingReserveUnit*					pclSimpleUnit = NULL;

	SI16 siCurrentYear		= sTime.wYear;
	SI16 siCurrentMonth		= sTime.wMonth;
	SI16 siCurrentDay		= sTime.wDay;
	SI16 siCurrentHour		= sTime.wHour;

	SI16 siReserveStatus	= WEDDING_RESERVE_STATUS_NONE;

	for ( SI32 siIndex=0; siIndex<WEDDING_RESERVE_LIST_NUM; siIndex++ )
	{
		pclSimpleUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siIndex );
		if ( NULL == pclSimpleUnit )
		{
			continue;
		}

		// ����Ǿ������� �װ��� ���� �ð��̶�� �������̶�� ǥ���Ѵ�
		if ( (0 < pclSimpleUnit->m_siMate1_PersonID) || (0 < pclSimpleUnit->m_siMate2_PersonID) )
		{
			if ( TRUE == pclSimpleUnit->IsSameTime(siCurrentYear, siCurrentMonth, siCurrentDay, siCurrentHour) )
			{
				siReserveStatus = WEDDING_RESERVE_STATUS_PROGRESS;
			}
			else
			{
				siReserveStatus = WEDDING_RESERVE_STATUS_RESERVE;
			}
		}
		else
		{
			siReserveStatus = WEDDING_RESERVE_STATUS_NONE;
		}

		clSimpleList.m_clSimpleUnit[siIndex].Set( pclSimpleUnit->m_stReserveTime, siReserveStatus );
	}

	cltMsg clMsgList( GAMEMSG_RESPONSE_WEDDING_SIMPLELIST_GET, sizeof(clSimpleList), (BYTE*)&clSimpleList );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsgList );
	*/
}

void cltServer::DoMsg_DBMSG_RESPONSE_WEDDING_RESERVE_CANCEL(sPacketHeader* pPacket)
{
	sDBResponse_WeddingReserveCancel* pclMsg = (sDBResponse_WeddingReserveCancel*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	// �ش� ���� ��ȣ�� ������ �ʱ�ȭ �ϰ�
	m_pclMarriageMgr->m_clWeddingList.InitOneUnitExecptTime( pclMsg->m_siReserveNum );

	// ĳ���� ���� ����
    SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( FALSE == pclChar->IsMarried() )
	{
		return;
	}

	// Ŭ���̾�Ʈ�� �޽��� ������
	cltGameMsgResponse_WeddingReserveCancel clinfo( pclMsg->m_siResult );
	cltMsg clMsgList( GAMEMSG_RESPONSE_WEDDING_RESERVE_CANCEL, sizeof(clinfo), (BYTE*)&clinfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsgList );


	SI32			siMatePID	= pclChar->pclMarriage->GetMatePersonID();
	SI32			siMateID	= pclCM->GetIDFromPersonID( siMatePID );
	cltCharServer*	pclMateChar	= pclCM->GetCharServer( siMateID );
	if ( NULL == pclMateChar )
	{
		cltLetterMsg_WeddingCeremony_Cancel clletter;
		sDBRequest_PushLetter clMsg( siMatePID, (cltLetterUnit*)&clletter );
		SendDBMsg( DBSELECT_LETTER, (sPacketHeader*)&clMsg );
	}
	else
	{
		// Ŭ���̾�Ʈ�� �޽��� ������
		cltGameMsgResponse_WeddingReserveCancel clinfo( pclMsg->m_siResult );
		cltMsg clMsgList( GAMEMSG_RESPONSE_WEDDING_RESERVE_CANCEL, sizeof(clinfo), (BYTE*)&clinfo );
		pclChar->SendNetMsg( (sPacketHeader*)&clMsgList );
	}

}