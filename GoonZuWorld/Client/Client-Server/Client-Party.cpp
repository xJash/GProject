#include "..\Client.h"
#include "..\..\CommonLogic\Msg\MsgType-Party.h"
//#include "..\Interface\PartyDlg\PartyDlg.h"
//#include "..\Interface\PartyInviteDlg\PartyInviteDlg.h"
#include "../Client/NInterface/NPartyDlg/NPartyDlg.h"
#include "../Client/NInterface/NPartyDlg/NPartyInviteDlg.h"

#include "..\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../Server/GameDBProcess/GameDBProcess.h"

#include "../Client/ninterface/NPartyQuest_PartyMatchingDlg/NPartyMatching_PartyJoinDlg.h"




// [����] ��Ƽ��Ī���� �߰��� �޼��� ó�� �Լ���
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_WANTJOIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_Party_WantJoin* pJoinInfo = (cltGameMsgResponse_Party_WantJoin*)pclMsg->cData;
	if ( NULL == pJoinInfo ) return;

	// ��Ƽ ���� ��û ���� â�� ���ִ� ���ȿ� ������ �ٸ� ����� ���� ��û ó���� �� �����Ѵ�.
	if ( NULL == m_pDialog[NPARTY_JOIN_DLG] )
	{
		CreateInterface( NPARTY_JOIN_DLG );
		CNPartyMatching_PartyJoinDlg* pDlg = ((CNPartyMatching_PartyJoinDlg*)m_pDialog[NPARTY_JOIN_DLG]);
		if ( NULL != pDlg )
		{
			NTCHARString64 strMessage( GetTxtFromMgr(40796) );		// "#name#���� ��Ƽ ������ ��û�ϼ̽��ϴ�."
			strMessage.Replace( TEXT("#name#"), pJoinInfo->szMemberName );

			pDlg->SetText( strMessage );
			pDlg->SetJoinRequestInfo( pJoinInfo->siLeaderUnique, pJoinInfo->siMemberUnique, pJoinInfo->siPartyIndex);
			pDlg->Show();
		}
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_WANTJOINRESULT(cltMsg* pclMsg, SI32 id)
{
	/* ��Ƽ �³��� ���� �޼����� ��Ƽ���� ��ȭ���ڿ� ������ �־�� �ϱ� ������ ���� �޼������� ó���ϰ�
	��Ƽ ���� �޼����� ���⼭ ó���ϱ�� ����. */

		cltGameMsgResponse_Party_WantJoinResult* pJoinInfo = (cltGameMsgResponse_Party_WantJoinResult*)pclMsg->cData;
	if ( NULL == pJoinInfo ) return;

	if ( false == pJoinInfo->bResult )
	{
		if ( NULL == m_pDialog[NOTIFYMSG_DLG] )
		{
			CreateInterface( NOTIFYMSG_DLG );
		}

		NTCHARString16 strTitle( GetTxtFromMgr( 40788 ) );			// "��Ƽ����Ʈ"
		NTCHARString64 strText( GetTxtFromMgr( 40789 ) );			// "#��Ƽ��# ��Ƽ���� ���Խ�û�� �����߽��ϴ�."
		NTCHARString16 strPartyName( pJoinInfo->szPartyName );

		strText.Replace( TEXT("#��Ƽ��#"), strPartyName );

		m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
	}
}


//////////////////////////////////////////////////////////////////////////
// ���� �޼��� ó�� �Լ���

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_CREATEINVITE(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_CreateInvite *pclPartyCreateInvite = (cltGameMsgResponse_Party_CreateInvite *) pclMsg->cData;
	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyInviteDlg*)m_pDialog[ NPARTYINVITE_DLG ])->PartyCreateInvite( pclPartyCreateInvite->siPartyLeaderPersonID, pclPartyCreateInvite->strCharName );
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_CREATEJOIN(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_CreateJoin *pclPartyCreateJoin = (cltGameMsgResponse_Party_CreateJoin *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyCreateJoin( pclPartyCreateJoin->siPartyIndex, pclPartyCreateJoin->siLeaderPersonID, pclPartyCreateJoin->siLeaderCharUnique, pclPartyCreateJoin->strLeaderCharName, pclPartyCreateJoin->siLeaderLevel, &pclPartyCreateJoin->clLeaderCharPos ,pclPartyCreateJoin->siMemberPersonID, pclPartyCreateJoin->siMemberCharUnique, pclPartyCreateJoin->strMemberCharName, pclPartyCreateJoin->siMemberLevel, &pclPartyCreateJoin->clMemberCharPos );
	}

	if ( true == pclPartyCreateJoin->bIsPartyQuestParty )
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->Set_PartyQuestInfo( pclPartyCreateJoin->bIsPartyQuestParty, pclPartyCreateJoin->siPartyQuest_Category, pclPartyCreateJoin->siPartyQuest_Mission );
	}

	// ��Ƽ���� ���� ���, ��Ƽ���� ��Ƽ�� ���ԵǾ����� �˸��� ��ȭ���� ���
	if ( 0 < _tcslen(pclPartyCreateJoin->szPartyName) )
	{
		cltCharClient* pMyChar = (cltCharClient*)pclCM->GetCharClient( 1 );
		if ( NULL != pMyChar )
		{
			if ( 0 == _tcscmp( pclPartyCreateJoin->strMemberCharName, pMyChar->GetName() ) )
			{
				if ( 0 < _tcslen( pclPartyCreateJoin->szPartyName) )
				{
					if ( NULL == m_pDialog[NOTIFYMSG_DLG] )
					{
						CreateInterface( NOTIFYMSG_DLG );
					}

					NTCHARString16 strTitle( GetTxtFromMgr( 40788 ) );			// "��Ƽ����Ʈ"
					NTCHARString64 strText( GetTxtFromMgr( 40797 ) );			// "#��Ƽ��# ��Ƽ�� ���ԵǾ����ϴ�."
					NTCHARString16 strPartyName( pclPartyCreateJoin->szPartyName );

					strText.Replace( TEXT("#��Ƽ��#"), strPartyName );

					m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
				}
			}
		}
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_INVITE(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_Invite *pclPartyInvite = (cltGameMsgResponse_Party_Invite *) pclMsg->cData;


	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyInviteDlg*)m_pDialog[ NPARTYINVITE_DLG ])->PartyInvite( pclPartyInvite->strCharName, pclPartyInvite->siPartyLeaderPersonID, pclPartyInvite->siPartyIndex );
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_INVITEREJECT(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;
	cltGameMsgResponse_Party_InviteReject *pclPartyInviteReject = (cltGameMsgResponse_Party_InviteReject *) pclMsg->cData;

	TCHAR* pTitle = GetTxtFromMgr(1266);
	TCHAR* pText = GetTxtFromMgr(1267);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclPartyInviteReject->strCharName );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_JOIN(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_Join *pclPartyJoin = (cltGameMsgResponse_Party_Join *) pclMsg->cData;

	if( m_pDialog[NPARTY_DLG])
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyJoin( pclPartyJoin->siPartyIndex, pclPartyJoin->siUserListIndex, pclPartyJoin->siItemGetPattern );		
	}

	// ��Ƽ���� ���� ���, ��Ƽ���� ��Ƽ�� ���ԵǾ����� �˸��� ��ȭ���� ���
	if ( 0 < _tcslen(pclPartyJoin->szPartyName) )
	{
		if ( NULL == m_pDialog[NOTIFYMSG_DLG] )
		{
			CreateInterface( NOTIFYMSG_DLG );
		}

		NTCHARString16 strTitle( GetTxtFromMgr( 40788 ) );			// "��Ƽ����Ʈ"
		NTCHARString64 strText( GetTxtFromMgr( 40797 ) );			// "#��Ƽ��# ��Ƽ�� ���ԵǾ����ϴ�."
		NTCHARString16 strPartyName( pclPartyJoin->szPartyName );

		strText.Replace( TEXT("#��Ƽ��#"), strPartyName );

		m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_DELETE(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_Delete *pclPartyDelete = (cltGameMsgResponse_Party_Delete *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( ((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->IsPartyStatus() && ((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->GetPartyIndex() == pclPartyDelete->siPartyIndex )
		{
			((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyDelete( pclPartyDelete->siPartyIndex );
		}
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_ADDUSER(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_AddUser *pclPartyAddUser = (cltGameMsgResponse_Party_AddUser *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyAddUser( pclPartyAddUser->bPartyLeader, pclPartyAddUser->siCharUnique, pclPartyAddUser->strCharName, pclPartyAddUser->siUserListIndex, pclPartyAddUser->siLevel, &pclPartyAddUser->clCharPos );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_DELUSER(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_DelUser *pclPartyDelUser = (cltGameMsgResponse_Party_DelUser *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyDelUser( pclPartyDelUser->siCharUnique, pclPartyDelUser->siUserListIndex );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_FORCEDELUSER(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_ForceDelUser *pclPartyForceDelUser = (cltGameMsgResponse_Party_ForceDelUser *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyForceDelUser( pclPartyForceDelUser->siCharUnique, pclPartyForceDelUser->siUserListIndex );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_CHANGELEADER(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_ChangeLeader *pclPartyChangeLeader = (cltGameMsgResponse_Party_ChangeLeader *) pclMsg->cData;
	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyChangeLeader( pclPartyChangeLeader->siCharUnique, pclPartyChangeLeader->siUserListIndex );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYEXP(cltMsg* pclMsg, SI32 id)
{
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_NotifyExp *pclPartyNotifyExp = (cltGameMsgResponse_Party_NotifyExp *) pclMsg->cData;

	if(g_SoundOnOffDlg.m_bFullScreenMode)
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyNotifyExp( pclPartyNotifyExp->siCharUnique, pclPartyNotifyExp->siUserListIndex, pclPartyNotifyExp->siExp );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_CHANGEITEMGETPATTERN(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;
	// ���� ����̸�, 
	if(bWatchModeSwitch == true)return ;

	cltGameMsgResponse_Party_ChangeItemGetPattern *pclPartyChangeItemGetPattern = (cltGameMsgResponse_Party_ChangeItemGetPattern *) pclMsg->cData;

	if(pclclient->m_pDialog[NPARTY_DLG])
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->ChangeItemGetPattern(pclPartyChangeItemGetPattern->siItemGetPattern);
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYITEMGET(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_Party_NotifyItemGet * clInfo = (cltGameMsgResponse_Party_NotifyItemGet*) pclMsg->cData;

	if(pclclient->m_pDialog[NPARTY_DLG])
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->PartyNotifyItemGet(clInfo->siCharUnique, &clInfo->clItem );
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_PARTYUSERPOS(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_Party_PartyUserPos * clinfo = (cltGameMsgResponse_Party_PartyUserPos*) pclMsg->cData;

	if(pclclient->m_pDialog[NPARTY_DLG])
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->SetPartyUserPos(clinfo->siCharUnique,&clinfo->clCharPos);
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_NOTIFYLEVELUP(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameMsgResponse_Party_NotifyLevelUp * clinfo = (cltGameMsgResponse_Party_NotifyLevelUp*) pclMsg->cData;

	if(pclclient->m_pDialog[NPARTY_DLG])
	{
		((CNPartyDlg*)m_pDialog[ NPARTY_DLG ])->SetPartyUserLevel(clinfo->siCharUnique,clinfo->siLevel);
	}
}
