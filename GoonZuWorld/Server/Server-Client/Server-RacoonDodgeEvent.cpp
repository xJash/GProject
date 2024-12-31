//Switch_10MonthEvent_RacoonDodge
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../common/RacoonDodgeEvent/RacoonDodgeEvent.h"

#include "../../common/Order/order.h"
#include "../../common/JWLib/IsCorrectID/IsCorrectID.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-RacoonDodgeEvent.h"

// ����  ���ϱ� �̺�Ʈ ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_RACOONDODGEEVENTRESERVATION(cltMsg* pclMsg, SI32 id )//Switch_10MonthEvent_RacoonDodge
{
	cltServer* pclserver = (cltServer*)pclClient;

	if( false == pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )	return ;	// ���� �ڵ尡 �ȿ������� ���� �Ѵ�
	// �̺�Ʈ �Ⱓ�� �ƴϸ� ���� �Ѵ�. -> ���߰�
	cltGameMsgRequest_ReservationEvent* pclinfo = (cltGameMsgRequest_ReservationEvent*)pclMsg->cData;	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	if ( NULL == pclChar )		return;
	
	SI32 siCharPersonID = pclinfo->siPersonID	;
	bool bSuccess = false ;

	// �� �������� Ȯ�� �Ѵ� .
	GMONEY gMyMoney = pclChar->pclCI->clIP.GetMoney()	;
	GMONEY gCost	=	(pclClient->pclItemManager->clItemStatistic.siNPCPriceRate*1000)/100	;

	if ( gMyMoney >= gCost )
	{
		bSuccess = pclRacoonDodgeEventMgr->AddReserveList(siCharPersonID)	;
		if ( bSuccess == true ) 
		{
			//	��������ϰ� ���� �˸���.
			sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_RACOONDODGE_USEMONEY, -gCost);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : �ռ��� 2009. 8. 24] // �����̺�Ʈ ������ ���� 
				// Ÿ�� personID 
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RACCOONDODGE_EVENT, LOGCOMMAND_INDEX_PVP_RACCOONDODGE_EVENT_RESERVE, 
					0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					gCost, 0, 0, 0, 0, NULL, NULL);	// para1 : ������
			}
			pclRacoonDodgeEventMgr->SendReserveList( siCharPersonID )	;	// ����Ʈ�� Ŭ���̾�Ʈ�� �˷��ش�.
		}
	}
	else
	{
		pclserver->SendServerResponseMsg( 0, SRVAL_RACOONDODGEEVENT_NOTENOUGHMONEY , 0, 0, pclChar->GetCharUnique() );	// ���ڸ��� ����
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_REQUEST_PLAYEVENT(cltMsg* pclMsg, SI32 id )//Switch_10MonthEvent_RacoonDodge	// ���� ���ϱ� ���� ���������� ���� 
{
	if( false == pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )	return ;	// ���� �ڵ尡 �ȿ������� ���� �Ѵ�
	// �̺�Ʈ �Ⱓ�� �ƴϸ� ���� �Ѵ�. -> ���߰�
	cltGameMsgReQuest_Request_PlayEvent* pclinfo = (cltGameMsgReQuest_Request_PlayEvent*)pclMsg->cData;	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	if ( NULL == pclChar )		return;

	SI32 siCharPersonID = pclinfo->siPersonID	;
	bool bSuccess = false ;

	pclRacoonDodgeEventMgr->WarpGameSpace(siCharPersonID)	;	//���������� ������ ������ ���� ��Ų��.
}


void cltServer::DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_OVER5SECOND_START(cltMsg* pclMsg, SI32 id )//Switch_10MonthEvent_RacoonDodge
{
	if( false == pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )	return ;	// ���� �ڵ尡 �ȿ������� ���� �Ѵ�

	cltGameMsgRequest_RacoonDodgeEveent_StartGame* pclinfo = (cltGameMsgRequest_RacoonDodgeEveent_StartGame*)pclMsg->cData;	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	if ( NULL == pclChar )		return;

	SI32 siEventStep = -1	;

	// ���� ���� ������ �޾ƿ´�
	siEventStep = pclRacoonDodgeEventMgr->GetStep()	;
	if ( siEventStep == EVENTSTEP_WAITTIME )	// 5�� ����ϴ� �����̸�
	{
		pclRacoonDodgeEventMgr->ChangeStep( EVENTSTEP_PLAY ) ; // �̺�Ʈ�� �����Ѵ�.
	}
	else
	{
		// �̹� ���°� ���� �ƴ��� �������� ��Ȳ���� ����� �޼����� �ƴϴ� ó�� �������� ����.
		return ; 
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_RACOONDODGE_EVENT_GET_RESERVE_LIST(cltMsg* pclMsg, SI32 id )//Switch_10MonthEvent_RacoonDodge
{
	if( false == pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )	return ;	// ���� �ڵ尡 �ȿ������� ���� �Ѵ�
	// �̺�Ʈ �Ⱓ�� �ƴϸ� ���� �Ѵ�. -> ���߰�
	cltGameMsgRequest_ReserveList* pclinfo = (cltGameMsgRequest_ReserveList*)pclMsg->cData;	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	if ( NULL == pclChar )		return;

	SI32 siCharPersonID = pclinfo->siPersonID	;

	pclRacoonDodgeEventMgr->SendReserveList( siCharPersonID )	;	// ����Ʈ�� Ŭ���̾�Ʈ�� �˷��ش�.

}