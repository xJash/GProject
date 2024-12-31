#include "../Client.h"
#include "../Music\Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/MsgType-Person.h"
#include "Char/CharManager/CharManager.h"
#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../ninterface/NCommonMsgDlg/NCommonMsgDlg.h"
#include "../ninterface/NFamilyInfoDlg/NFamilyInfoDlg.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_FAMILY_REQUEST_ADD_CHILDRENN(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameResponse_Request_Add_Children* pclinfo = (cltGameResponse_Request_Add_Children*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( id );
	if ( NULL == pclChar )
	{
		return;
	}
	// ��û�޼����� �޾����Ƿ� �ش� ��û �޼����� ���� ����� �Ѵ�.

	// �޽��� â ����
	if (pclclient->m_pDialog[NCOMMONMSG_DLG] == NULL)
	{
		pclclient->CreateInterface( NCOMMONMSG_DLG );
	}
	/*[#name1#]�԰� [#name2#]���� �ڳ�� ����ϱ� ���ϰ� �ֽ��ϴ�.\r	�³��Ͻðڽ��ϱ�?
	*/
	NTCHARString512	kText(GetTxtFromMgr(30131));
	kText.Replace("#name1#", pclinfo->m_szParentCharName );
	kText.Replace("#name2#", pclinfo->m_szMateCharName );

	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_REQUEST_FAMILY_ADD_CHILDREN);	
	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetText(kText);
	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetParentPersonID(pclinfo->m_siParentPersonID);	
	((CNCommonMsgDlg*)pclclient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec( 10 );

}
//�ڳฦ ����ϰ� Ŭ���̾�Ʈ������Ʈ
void cltClient::DoMsg_GAMEMSG_RESPONSE_FAMILY_UPDATE(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameResponse_UpdateFamily* pclinfo = (cltGameResponse_UpdateFamily*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( id );
	if ( NULL == pclChar )
	{
		return;
	}

	pclChar->pclFamily->Set( &pclinfo->m_cFamily)	;	// �� ���� �� ������Ʈ �ϰ�
	pclChar->pclMarriage->Set(&pclinfo->m_cMarriage)	;

	SI32 siMyClass = pclinfo->m_cFamily.GetMyClass_InFamily()	;

	if ( siMyClass == MYCLASS_IN_FAMILY_CHILDREN )	// ���� �ڽ��̰�
	{
		CreateInterface( NFAMILYCOOKIELEVEL_DLG );
	}
	// �̹� â�� ������� �������� ǥ�� �Ѵ�.

	if (pclclient->m_pDialog[NFAMILYINFO_DLG] == NULL)
	{
	}
	else
	{
		if ( pclclient->m_pDialog[ NFAMILYINFO_DLG ] )
		{
			((CNFamilyInfoDlg *)pclclient->m_pDialog[ NFAMILYINFO_DLG ])->DisplayFamilyInfo() 	;
		}

	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_FAMILY_CHAT(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameResponse_ChatFamily* pclinfo = (cltGameResponse_ChatFamily*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharClient* pclChar = pclCM->GetCharClient( id );
	if ( NULL == pclChar )
	{
		return;
	}
	pclclient->CreateInterface( NFAMILYINFO_DLG );
	((CNFamilyInfoDlg *)pclclient->m_pDialog[ NFAMILYINFO_DLG ])->RecvChat(&pclinfo->m_szchatdata ) 	;

}