#include "../Client.h"
#include "../Music\Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-RacoonDodgeEvent.h"
#include "../Common/RacoonDodgeEvent/RacoonDodgeEvent.h"


#include "Char/CharManager/CharManager.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../Client/NInterface/NCommonMsgDlg/NCommonMsgDlg.h"
#include "../Client/NInterface/NRacconDodgeEventDlg/NRacoonDodgeEventReserveListDlg.h"
//Switch_10MonthEvent_RacoonDodge
// ���� �̺�Ʈ ���࿡ ���� �亯
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_RESERVATION(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;
	cltGameMsgResponse_ReserveList* pclinfo = (cltGameMsgResponse_ReserveList*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	if (pclclient->m_pDialog[NRACOONDODGE_EVENT_RESERVELIST_DLG] == NULL)
	{
		pclclient->CreateInterface( NRACOONDODGE_EVENT_RESERVELIST_DLG );
	}

	((NRacoonDodgeEventReserveListDlg*)pclclient->m_pDialog[NRACOONDODGE_EVENT_RESERVELIST_DLG])->SetListData( pclinfo );
}
// ���� �̺�Ʈ 5��ī��Ʈ �ض�
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_WAIT5SECOND(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Remain5Seceond* pclinfo = (cltGameMsgResponse_Remain5Seceond*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	// 5�� ī��Ʈ �ö󰣴�.
	pclChar->siRacoonDodgeWaitTime = pclClient->CurrentClock  ; // ���� �������� ��Ŷ���� �ð� ����
	pclChar->bRacoonDodgeEventCountDown = true ;

	
}
// �����̺�Ʈ�� ���� �Ǿ��� �Ҳ���?
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_REQUEST_PLAYEVENT(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;

	cltGameMsgResponse_Request_PlayEvent* pclinfo = (cltGameMsgResponse_Request_PlayEvent*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	// �湮 â�� ���� �ش� �亯�� ������ ������
	if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)
	{
		pclclient->CreateInterface( NCOMMONMSG_DLG );
	}
	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_RACOONDODGEEVENT_ANSWER);
	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec(10)	;	// 10�����Ŀ� ȭ���� ������ �ʰ� �Ѵ�.
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_30SECOND(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;

	cltGameMsgResponse_30Seceond* pclinfo = (cltGameMsgResponse_30Seceond*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	pclClient->bTimeCount = true	;
	pclClient->siTimeSet	=	pclinfo->siSecond/1000		;	// 30��..�ʴ����� �ֽ��ϴ�~
	pclClient->dwWriteSetTime	=	pclClient->CurrentClock	;	// �ð��� ������ �ð�
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_ROUNDCOUNT(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;

	cltGameMsgResponse_RoundCount* pclinfo = (cltGameMsgResponse_RoundCount*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	pclClient->siRoundCount	= pclinfo->siRound	;
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_30SECOND_CLEAR(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;

	cltGameMsgResponse_30Seceond_Clear* pclinfo = (cltGameMsgResponse_30Seceond_Clear*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	pclClient->bTimeCount = false	;
	pclClient->siTimeSet	=	0		;	// 30��..�ʴ����� �ֽ��ϴ�~
	pclClient->dwWriteSetTime	=	0	;	// �ð��� ������ �ð�
}
void cltClient::DoMsg_GAMEMSG_RESPONSE_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR(cltMsg* pclMsg, SI32 id)
{
	cltClient *pclclient = ( cltClient * ) pclClient;

	cltGameMsgResponse_Round_Clear* pclinfo = (cltGameMsgResponse_Round_Clear*)pclMsg->cData;
	// �⺻ ���� üũ 
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}
	pclClient->siRoundCount	= -1	;
}