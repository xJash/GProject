#include "../../common/BokBulBokEventMgr/BokBulBokEvent.h"

#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"



// ���Һ� ���� ���� ���� ���� üũ
void cltServer::DoMsg_GAMEMSG_REQUEST_BBB_CHECK_PlAY_CONDITION(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_BBBCheckCondition * pclInfo = (cltGameRequest_BBBCheckCondition*) pclMsg->cData;
	if (NULL == pclInfo)		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )		return;

	// ���� ó�� ��
	m_pServer_BBBMgr->AddBBBList( id );		// bbb �Ŵ����� ��û�� �� ������ id�� �Ѱ� ���� ����/��⸮��Ʈ ���/���п� ���� ó��
}

// ���Һ� ����ڸ���Ʈ ������ ���� �޼��� ó��
void cltServer::DoMsg_GAMEMSG_REQUEST_BBB_WAITLIST_ANSWER(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_BBB_WaitList_Answer* pclinfo = (cltGameMsgRequest_BBB_WaitList_Answer*)pclMsg->cData;	
	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	
	if ( NULL == pclChar )		return;

	// ������ ��⸮��Ʈ�� ��Ͻ�Ű�� Ŭ�� ����� ��Ȳ�� �˷���.
	bool bResult = m_pServer_BBBMgr->Insert_List( id );

	m_pServer_BBBMgr->SendWaitListToClient( id, bResult );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BBB_WAITLIST_CANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_BBB_WaitList_Cancel* pclinfo = (cltGameMsgRequest_BBB_WaitList_Cancel*)pclMsg->cData;	
	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	
	if ( NULL == pclChar )		return;

	// ������ ��⸮��Ʈ�� ������Ű�� Ŭ�� ����� ��Ȳ�� �˷���.
	m_pServer_BBBMgr->Remove_List( id );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BBB_WARPMAPANSWER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_BBB_WarpMapAnswer* pclinfo = (cltGameMsgRequest_BBB_WarpMapAnswer*)pclMsg->cData;	
	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	
	if ( NULL == pclChar )		return;

	// ���� �ҷ���? �� ���� ��信 ���� ������ ó�� ����
	if ( true == pclinfo->m_bWantWarpMap )
	{
		m_pServer_BBBMgr->ActiveTemporaryReserve( id );		// ���� ���� Ȱ��ȭ
	}
	else
	{
		m_pServer_BBBMgr->CancelTemporaryReserve( id );		// ���� ���� ��Ȱ��ȭ
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BBB_ALREADYRESERVED(cltMsg* pclMsg, SI32 id)
{
	//cltGameMsgRequest_BBB_AlreadyReserved* 
	cltGameMsgRequest_BBB_WarpMapAnswer* pclinfo = (cltGameMsgRequest_BBB_WarpMapAnswer*)pclMsg->cData;	
	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	
	if ( NULL == pclChar )		return;

	m_pServer_BBBMgr->Check_AlreadyReserved( id );
}

// [����] : 2010�ų��̺�Ʈ - ����Ʈ ���� �޼���
void cltServer::DoMsg_GAMEMSG_REQUEST_2010NEWYEAREVENT_QUESTCANCEL(cltMsg* pclMsg, SI32 id)
{
	/*cltGameMsgRequest_2010NewYearEvent_QuestCancel* pclinfo = (cltGameMsgRequest_2010NewYearEvent_QuestCancel*)pclMsg->cData;	
	if ( NULL == pclinfo )		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );	
	if ( NULL == pclChar )		return;*/


}