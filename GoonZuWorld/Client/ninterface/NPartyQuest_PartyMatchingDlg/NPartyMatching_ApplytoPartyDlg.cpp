// ��Ƽ��Ī
#include "NPartyMatching_ApplytoPartyDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../CommonLogic/CommonLogic.h"

#include "../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"
#include "../../Client/PartyQuestMgr/PartyQuestMgr_Client.h"

#include "../../CommonLogic/Msg/MsgType-PartyMatching.h"
#include "../../CommonLogic/MsgType.h"




extern cltCommonLogic* pclClient;

CNApplytoParty_PartyMatching::CNApplytoParty_PartyMatching( void )
{
	pPartyMatchingList = NULL;
	pMemberList = NULL;
	pStepInfoList = NULL;
	pGreeting = NULL;
	pJoinRequest = NULL;

	siTempCategory = -1;

	bPacketSended = false;
	dwPacketBlockTime = 0;
}

CNApplytoParty_PartyMatching::~CNApplytoParty_PartyMatching( void )
{

}

void CNApplytoParty_PartyMatching::Init( )
{

}

void CNApplytoParty_PartyMatching::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NPartyMatchingDlg/DLG_NPartyList_Dlg.ddf" ) );
	file.CreatePopupDialog( this, NPARTY_MATCHING_BASE_DLG, TEXT( "dialog_party_matching_base" ), StaticCallBackDialogNApplytoParty_PartyMatching );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, NPARTY_MATCHING_BASE_DLG_STATICTEXT_GREETINGS, this), NPARTY_MATCHING_BASE_DLG_STATICTEXT_GREETINGS, TEXT("statictext_greetings") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, NPARTY_MATCHING_BASE_DLG_STATICTEXT_QUEST, this), NPARTY_MATCHING_BASE_DLG_STATICTEXT_QUEST, TEXT("statictext_quest") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, NPARTY_MATCHING_BASE_DLG_STATICTEXT_PARTY_MEMBER, this), NPARTY_MATCHING_BASE_DLG_STATICTEXT_PARTY_MEMBER, TEXT("statictext_party_member") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NPARTY_MATCHING_BASE_DLG_BUTTON_SENDMSG_TO_PARTYLEADER, this), NPARTY_MATCHING_BASE_DLG_BUTTON_SENDMSG_TO_PARTYLEADER, TEXT("button_sendmsg_to_partyleader") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NPARTY_MATCHING_BASE_DLG_BUTTON_APPLY_TO_PARTY, this), NPARTY_MATCHING_BASE_DLG_BUTTON_APPLY_TO_PARTY, TEXT("button_apply_to_party") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NPARTY_MATCHING_BASE_DLG_BUTTON_CREATE_PARTY, this), NPARTY_MATCHING_BASE_DLG_BUTTON_CREATE_PARTY, TEXT("button_create_party") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NPARTY_MATCHING_BASE_DLG_BUTTON_REMOVE, this), NPARTY_MATCHING_BASE_DLG_BUTTON_REMOVE, TEXT("button_remove") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT, NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL, this), NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL, TEXT("editbox_greetings_detail") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(LIST, NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST, this), NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST, TEXT("listbox_party_list") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(LIST, NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME, this), NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME, TEXT("listbox_member_name") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(LIST, NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST, this), NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST, TEXT("listbox_quest_list") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, NPARTY_MATCHING_BASE_DLG_BUTTON_REFRESH, this), NPARTY_MATCHING_BASE_DLG_BUTTON_REFRESH, TEXT("button_refresh") );

	bPacketSended = false;
	dwPacketBlockTime = 0;

	pJoinRequest = m_InterfaceFactory.GetButton( NPARTY_MATCHING_BASE_DLG_BUTTON_APPLY_TO_PARTY );
	if ( NULL == pJoinRequest ) { DeleteDialog(); return; }

	pJoinRequest->Enable( true );

	pPartyMatchingList = (CList*)m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	pMemberList = (CList*)m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME );
	pStepInfoList = (CList*)m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST );
	pGreeting = m_InterfaceFactory.GetEdit( NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL );
	if ( NULL == pPartyMatchingList || NULL == pMemberList || NULL == pStepInfoList ) { DeleteDialog(); return; }

	SI16 siFirstColumn		= 0;
	SI16 siSecondColumn		= 0;
	SI16 siThirdColumn		= 0;
	SI16 siFourthColumn		= 0;
	SI16 siFifthColumn		= 0;

	TCHAR* pText = NULL;

	// ��Ƽ��Ī ����Ʈ �ʱ�ȭ
	pPartyMatchingList->SetBorder(true);
	pPartyMatchingList->SetBKColorUse(true);

	siFirstColumn		= 40;
	siThirdColumn		= 80;
	siSecondColumn		= pPartyMatchingList->GetWidth()	- (siFirstColumn + siThirdColumn);

	pText = GetTxtFromMgr(1641);		// ��ȣ
	pPartyMatchingList->SetColumn(0, siFirstColumn, pText);
	pText = GetTxtFromMgr(40337);		// ��Ƽ��
	pPartyMatchingList->SetColumn(1, siSecondColumn, pText);
	pText = GetTxtFromMgr(40338);		// ��Ƽ��
	pPartyMatchingList->SetColumn(2, siThirdColumn, pText);

	// ��Ƽ��� ����Ʈ �ʱ�ȭ (��Ʈ���� ������ ���� �ʾ� ��� ����)
	pMemberList->SetBorder( true );
	pMemberList->SetBKColorUse( true );

	siFirstColumn		= pMemberList->GetWidth();

	pText = GetTxtFromMgr(40340);		// ��Ƽ��
	pMemberList->SetColumn(0, siFirstColumn, pText);

	// ����Ʈ ���� ���� ����Ʈ �ʱ�ȭ
	pStepInfoList->SetBorder( true );
	pStepInfoList->SetBKColorUse( true );
	//pStepInfoList->SetTextPrintOption( DT_CENTER | DT_VCENTER | DT_WORDBREAK );

	siFirstColumn		= 40;
	siSecondColumn		= 90;
	siThirdColumn		= 50;
	siFourthColumn		= 60;
	siFifthColumn		= pStepInfoList->GetWidth()	- (siFirstColumn + siSecondColumn + siThirdColumn + siFourthColumn);

	pText = GetTxtFromMgr(40341);		// �̼� ��ȣ
	pStepInfoList->SetColumn(0, siFirstColumn, pText);
	pText = GetTxtFromMgr(40785);		// ���� (������)
	pStepInfoList->SetColumn(1, siSecondColumn, pText);
	pText = GetTxtFromMgr(1679);		// ����
	pStepInfoList->SetColumn(2, siThirdColumn, pText);
	pText = GetTxtFromMgr(1871);		// �ð�
	pStepInfoList->SetColumn(3, siFourthColumn, pText);
	pText = GetTxtFromMgr(4574);		// ����
	pStepInfoList->SetColumn(4, siFifthColumn, pText);

	pPartyMatchingList->Refresh();
	pMemberList->Refresh();
	pStepInfoList->Refresh();
}

void CALLBACK CNApplytoParty_PartyMatching::StaticCallBackDialogNApplytoParty_PartyMatching( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNApplytoParty_PartyMatching* pThis = (CNApplytoParty_PartyMatching*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNApplytoParty_PartyMatching( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNApplytoParty_PartyMatching::CallBackDialogNApplytoParty_PartyMatching( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pClient = (cltClient*) pclClient;
	if ( NULL == pClient ) return;
	if ( NULL == pClient->m_pClient_PartyMatchingMgr ) return;



	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;

		// button
	case NPARTY_MATCHING_BASE_DLG_BUTTON_APPLY_TO_PARTY:	// ��Ƽ ���� ��û
		{
			EventProcess_ClickButton_PartyJoin();
		}
		break;
	case NPARTY_MATCHING_BASE_DLG_BUTTON_SENDMSG_TO_PARTYLEADER:
		{
			EventProcess_ClickButton_Whisper();
		}
		break;
	case NPARTY_MATCHING_BASE_DLG_BUTTON_CREATE_PARTY:
		{
			EventProcess_ClickButton_CreateNewPartyMatching();
		}
		break;

		// Listbox
	case NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST:
		{
			if ( EVENT_LISTBOX_SELECTION == nEvent )
			{
				EventProcess_SelectItem_PartyMatchingList();
			}
		}
		break;
	case NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME :
		{
		}
		break;
	case NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST:
		{
		}
		break;

		// Edit
	case NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL:
		{

		}
		break;
	case NPARTY_MATCHING_BASE_DLG_BUTTON_REMOVE:
		{
			// ����Ʈ�� �� ��Ī���� ���� ��û
			cltGameRequest_RemovePartyMatching clinfo;
			cltMsg clMsg( GAMEMSG_REQUEST_REMOVEPARTYMATCHING, sizeof(clinfo), (BYTE*)&clinfo );
			pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );
		}
		break;
	case NPARTY_MATCHING_BASE_DLG_BUTTON_REFRESH:
		{
			pClient->m_pClient_PartyMatchingMgr->MsgProcess_Request_PartyMatchingList( siTempCategory );
		}
		break;
	default:
		break;

	}
}



//---------------------------------------------------------------------------------------------------------
// ��ȭ���� ��Ʈ���� �̺�Ʈ ó�� �Լ���
//---------------------------------------------------------------------------------------------------------

void CNApplytoParty_PartyMatching::EventProcess_SelectItem_PartyMatchingList()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient->m_pClient_PartyMatchingMgr ) return;
	if ( NULL == pClient->m_pPartyQuestMgr ) return;

	CList* pPartyList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	CList* pStepInfoList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST );
	CList* pMemberList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME );
	CEdit* pGreeting = m_InterfaceFactory.GetEdit( NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL );
	if ( NULL == pPartyList || NULL == pStepInfoList || NULL == pMemberList || NULL == pGreeting ) return;

	pStepInfoList->Clear();
	pMemberList->Clear();
	pGreeting->Clear();

	SI16 siSelected = -1;
	siSelected = pPartyList->GetSelectedIndex();

	CInfo_PartyMatching* rInfo = pClient->m_pClient_PartyMatchingMgr->Get_PartyMatchingInfo( siSelected );
	if ( NULL == rInfo ) return;

	// �λ縻
	pGreeting->SetText( rInfo->m_strHelloMessage );

	// ��Ƽ�� ���� - ������ ��Ŷ ������ ó���� ����� �޾Ƽ� ó��
	cltGameRequest_GetPartyMemberInfo clSndInfo( rInfo->m_siLeaderID );
	cltMsg clSndMsg( GAMEMSG_REQUEST_GETPARTYMEMBERNAMELIST, sizeof(clSndInfo), (BYTE*)&clSndInfo );
	pclClient->SendMsgToServer( (sPacketHeader*)&clSndMsg );

	// ��������
	SI32 siCategory = -1;
	SI32 siMission = -1;
	siCategory = rInfo->m_siParentQuest;
	siMission = rInfo->m_siChildQuest;




	//////////////////////////////////////////////////////////////////////////
	// �� for���� ���� �Լ��� ������ �Һκ�. ������� ���ٸ� ����Ʈ �Ŵ����ʿ� �־ ����� �ϱ����� �ϼ��� string�迭�̳� ����ü ���·� �Ѿ�Ծ�� �� �۾�

	for ( SI16 i = 0; i < MAX_PARTYQUEST_STEP_NUM; ++i )
	{
		PartyQuest_UnitData* pUnitData = NULL;
		pUnitData = pClient->m_pPartyQuestMgr->GetPartyQuestUnitData( siCategory, siMission, i );
		if ( NULL == pUnitData ) continue;
		//if ( PARTYQUEST_TYPE_NONE >= pUnitData->m_siQuestType || PARTYQUEST_TYPE_END <= pUnitData->m_siQuestType ) continue;
		if ( 0 >= pUnitData->m_siTimeLimit ) continue;

		NTCHARString16 strStepNum( GetTxtFromMgr(40791) );		// "�̼� #num#"
		NTCHARString16 strMonster;								// ����
		NTCHARString16 strCount;								// ����
		NTCHARString16 strTime( GetTxtFromMgr(40792) );			// "#minute#��"
		NTCHARString128 strReward;								// ����

		// ����
		SI16 siStepNum = pUnitData->m_siQuestStep + 1;
		strStepNum.Replace( TEXT("#num#"),	SI32ToString(siStepNum) );

		// ����
		if( PARTYQUEST_TYPE_HUNTING == pUnitData->m_siQuestType )
		{
			strMonster = pclClient->pclKindInfoSet->pclKI[pUnitData->m_siCondition1]->GetName();

		}
		else if( PARTYQUEST_TYPE_MAKEITEM == pUnitData->m_siQuestType )
		{
			strMonster = pclClient->pclItemManager->GetName( pUnitData->m_siCondition1 );
		}

		// ����
		SI16 siCount = pUnitData->m_siAmount;
		strCount = SI32ToString(siCount);

		// �ð�
		SI32 siTime = pUnitData->m_siTimeLimit;
		siTime /= 60;
		strTime.Replace( TEXT("#minute#"), SI32ToString(siTime) );

		// ����
		SI32 siRewardExp = 0;
		SI32 siRewardUnique = 0;
		SI16 siRewardAmount = 0;

		// ������
		for ( SI08 k = 0; k < MAX_PARTYQUEST_REWARD_NUM; ++k )
		{
			siRewardUnique = pUnitData->m_siRewardItemUnique[k];
			siRewardAmount = pUnitData->m_siRewardItemAmount[k];

			if ( 0 < siRewardUnique )
			{
				if ( 0 != k )
				{
					/*SI16 siFontHeight = pStepInfoList->GetFontHeight();
					SI16 siLineHeight = pStepInfoList->GetLineHeight();
					pStepInfoList->SetLineHeight( siLineHeight + siFontHeight + 3 );

					strReward = strReward + TEXT("\r");*/

						strReward = strReward + TEXT(", ");
				}

				strReward = strReward + pclClient->pclItemManager->GetName( siRewardUnique );

				if ( 0 < siRewardAmount )
				{
					NTCHARString16 strRewardAmount( GetTxtFromMgr(40793) );		// " #num# ��"
					strRewardAmount.Replace( TEXT("#num#"), SI32ToString(siRewardAmount) );
					strReward = strReward + ((TCHAR*)strRewardAmount);
				}
			}
		}

		// ����ġ
		siRewardExp = pUnitData->m_siRewardEXP;
		if ( 0 < siRewardExp )
		{
			strReward = strReward + TEXT("\n");

			strReward = GetTxtFromMgr(40794);		// "#exp# EXP" -> "2000 EXP" �� ���� ����
			strReward.Replace( TEXT("#exp#"), SI32ToString(siRewardExp) );
		}

		// ���� ����Ʈ ��Ʈ�ѿ� ������ �߰�
		stListBoxItemData item;
		item.Init();

		item.Set( 0, strStepNum );
		item.Set( 1, strMonster );
		item.Set( 2, strCount );
		item.Set( 3, strTime );
		item.Set( 4, strReward );

		pStepInfoList->AddItem( &item );

	}
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	// �Էµ� ������ ���̰� ��Ʈ�� ����
	pStepInfoList->Refresh();
	pMemberList->Refresh();
	pGreeting->Refresh();
}

void CNApplytoParty_PartyMatching::EventProcess_ClickButton_PartyJoin()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	CList* pPartyList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	if ( NULL == pPartyList ) return;

	SI16 siSelected = -1;
	siSelected = pPartyList->GetSelectedIndex();

	pClient->m_pClient_PartyMatchingMgr->Click_PartyEnterRequestButton( siSelected );
}

void CNApplytoParty_PartyMatching::EventProcess_ClickButton_Whisper()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	CList* pPartyList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	if ( NULL == pPartyList ) return;

	SI16 siSelected = -1;
	siSelected = pPartyList->GetSelectedIndex();

	pClient->m_pClient_PartyMatchingMgr->Click_WhisperButton( siSelected );
}

void CNApplytoParty_PartyMatching::EventProcess_ClickButton_CreateNewPartyMatching()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;
	if ( NULL == pClient->m_pClient_PartyMatchingMgr ) return;

	cltCharClient* pMyChar = (cltCharClient*)pClient->pclCM->GetCharClient(1);
	if ( NULL == pMyChar ) return;

	SI32 siMyCharUnique = pMyChar->GetCharUnique();
	if ( 0 <= pClient->m_pClient_PartyMatchingMgr->AlreadyExist( siMyCharUnique ) )
	{
		// �̹� ��Ƽ��Ī�� ����� �Ǿ� �ִٴ� �޼��� �ڽ� ���°͵��� ó���� ���⿡
		if ( NULL == pClient->m_pDialog[NOTIFYMSG_DLG] )
		{
			pClient->CreateInterface( NOTIFYMSG_DLG );
		}

		TCHAR* pTitle = GetTxtFromMgr( 512 );	// ����
		TCHAR* pBody = GetTxtFromMgr( 40426 );	// �̹� ��Ƽ��Ī�� ����� �ϼ̽��ϴ�. (��Ƽ�� ���Ե� ���¿����� ��Ƽ ����Ⱑ �Ұ��� �մϴ�.)

		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText( pTitle, pBody );

		return;
	}

	pClient->m_pClient_PartyMatchingMgr->Click_PartyMakeButton( siTempCategory );
}





//---------------------------------------------------------------------------------------------------------
// ��ȭ������ �Ϲ����� �������̽���
//---------------------------------------------------------------------------------------------------------

void CNApplytoParty_PartyMatching::AddListItem_PartyMatchingView(CInfo_PartyMatching* pInfo)
{
	// ��Ƽ��Ī ����Ʈ ��Ʈ�ѿ� ������ �߰�.

	CList* pList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	if ( NULL == pList ) return;
	if ( NULL == pInfo ) return;

	SI16 siCurrentPos = 0;
	siCurrentPos = pList->GetListNum();
	if ( 0 > siCurrentPos ) return;

	stListBoxItemData item;
	item.Init();

	item.Set( 0, SI16ToString(siCurrentPos+1) );
	item.Set( 1, pInfo->m_strPartyName );
	item.Set( 2, pInfo->m_strLeaderName );

	pList->AddItem( &item );
	pList->Refresh();
}

void CNApplytoParty_PartyMatching::SetData_PartyMemberView(SI32& rPartyMemberList)
{
	CList* pMemberList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_MEMBER_NAME );
	if ( NULL == pMemberList ) return;
}

void CNApplytoParty_PartyMatching::SetData_MissionView(SI32 siParentQuest, SI32 siChildQuest)
{
	CList* pStepList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_QUEST_LIST );
	if ( NULL == pStepList ) return;
}

void CNApplytoParty_PartyMatching::SetData_GreetingMessage(TCHAR* pszGreetingMessage)
{
	CEdit* pGreeting = m_InterfaceFactory.GetEdit( NPARTY_MATCHING_BASE_DLG_EDITBOX_GREETINGS_DETAIL );
	if ( NULL == pGreeting ) return;
}

void CNApplytoParty_PartyMatching::Clear_PartyMatchingList()
{
	CList* pList = m_InterfaceFactory.GetList( NPARTY_MATCHING_BASE_DLG_LISTBOX_PARTY_LIST );
	if ( NULL == pList ) return;

	pList->Clear();

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL != pClient->m_pClient_PartyMatchingMgr )
	{
		pClient->m_pClient_PartyMatchingMgr->m_PartyList.RemoveAll();
	}
}

void CNApplytoParty_PartyMatching::Clear_Controls()
{
	pPartyMatchingList->Clear();
	pMemberList->Clear();
	pStepInfoList->Clear();
	pGreeting->Clear();
	pJoinRequest->Enable( true );

	pPartyMatchingList->Refresh();
	pMemberList->Refresh();
	pStepInfoList->Refresh();
	pGreeting->Refresh();
	pJoinRequest->Refresh();
}