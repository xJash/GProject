#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Dormancy.h"

#include "../../CommonLogic/Msg/MsgType-DormancyAccount.h"
			
// [����] ����Ʈ�� ������ ����
void cltServer::DoMsg_DBMSG_RESPONSE_DORMANCY_POINTITEM_BUY(sPacketHeader* pPacket)
{
	if( NULL == pclDormancySystem)
		return;

	const SI32	DBMSG_SUCCESS_FLAG = 1;

	sDBResonse_BuyDormancyPointItem* pclMsg = (sDBResonse_BuyDormancyPointItem*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	// DBó�� ��� ���� Ȯ��
	if ( DBMSG_SUCCESS_FLAG != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	CDormancyPointRewardServer *pclDormancyServer = (CDormancyPointRewardServer *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyServer)
		return;

	pclDormancyServer->BuyPointItemResponse(pclChar, &pclMsg->m_clItem, pclMsg->m_siItemPos, pclMsg->m_siItemPoint);
}

// [����] ����Ʈ ���� ���� ����
void cltServer::DoMsg_DBMSG_RESPONSE_DORMANCY_POINTINFO_SET(sPacketHeader* pPacket)
{
	if( NULL == pclDormancySystem)
		return;

	const SI32	DBMSG_SUCCESS_FLAG = 1;

	sDBResonse_SetDormancyPointInfo* pclMsg = (sDBResonse_SetDormancyPointInfo*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	// DBó�� ��� ���� Ȯ��
	if ( DBMSG_SUCCESS_FLAG != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	CDormancyPointRewardServer *pclDormancyServer = (CDormancyPointRewardServer *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyServer)
		return;

	pclDormancyServer->RecvDBDormancyInfo(pclChar, pclMsg->m_siPoint);
	pclDormancyServer->SendClientDormancyInfo(pclChar);
}

// [����] �޸� ���� ���� ����
void cltServer::DoMsg_DBMSG_RESPONSE_DORMANCY_STATE_CHANGE(sPacketHeader* pPacket)
{
	if( NULL == pclDormancySystem)
		return;

	const SI32	DBMSG_SUCCESS_FLAG = 1;

	sDBResponse_ChangeDormancyState* pclMsg = (sDBResponse_ChangeDormancyState*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	// DBó�� ��� ���� Ȯ��
	if ( DBMSG_SUCCESS_FLAG != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclChar		= pclCM->GetCharServer( siCharID );
	if ( NULL == pclChar )
	{
		return;
	}

	CDormancyPointRewardServer *pclDormancyServer = (CDormancyPointRewardServer *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyServer)
		return;

	pclDormancyServer->RecvDBChangeDormancyState(pclChar ,pclMsg->m_bDormancyState);
}


