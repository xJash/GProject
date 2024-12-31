
#include "NProposeQuestionDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../../../common/Char/CharManager/CharManager.h"
#include "../../../common/Family/Marriage.h"

#include "../../CommonLogic/MsgType-Person.h"

extern cltCommonLogic* pclClient;

CNProposeQuestionDlg::CNProposeQuestionDlg( void )
{
	Init();
}

CNProposeQuestionDlg::~CNProposeQuestionDlg( void )
{

}

void CNProposeQuestionDlg::Init( )
{
}

void CNProposeQuestionDlg::Create()
{
	//-- 이미 생성되었다면 리턴
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NWeddingCeremony/DLG_NPropose_Question.ddf" ) );
	file.CreatePopupDialog( this, NPROPOSE_QUESTION_DLG, TEXT( "dialog_propose_question" ), StaticCallBackDialogNProposeQuestionDlg );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,	PROPOSE_QUESTION_DLG_STATICTEXT_NAME,		this), PROPOSE_QUESTION_DLG_STATICTEXT_NAME,	TEXT("statictext_name") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,	PROPOSE_QUESTION_DLG_STATICTEXT_MESSAGE,	this), PROPOSE_QUESTION_DLG_STATICTEXT_MESSAGE,	TEXT("statictext_message") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,	PROPOSE_QUESTION_DLG_BUTTON_PROPOSE,		this), PROPOSE_QUESTION_DLG_BUTTON_PROPOSE,		TEXT("button_propose") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,	PROPOSE_QUESTION_DLG_EDITBOX_NAME,			this), PROPOSE_QUESTION_DLG_EDITBOX_NAME,		TEXT("editbox_name") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,	PROPOSE_QUESTION_DLG_EDITBOX_MESSAGE,		this), PROPOSE_QUESTION_DLG_EDITBOX_MESSAGE,	TEXT("editbox_message") );

	// 글자 수 제한
	CEdit* pclName = m_InterfaceFactory.GetEdit( PROPOSE_QUESTION_DLG_EDITBOX_NAME );
	if ( pclName )
	{
		pclName->SetMaxEditTextLength( MAX_PLAYER_NAME-1 );
	}

	CEdit* pclMessage = m_InterfaceFactory.GetEdit( PROPOSE_QUESTION_DLG_EDITBOX_MESSAGE );
	if ( pclMessage )
	{
		pclMessage->SetMaxEditTextLength( Const_Max_Propose_Message-1 );
	}

	// 실행되기전 기본적으로 있어야할 조건들을 검사한다
	if ( FALSE == CheckCondition() )
	{
		DeleteDialog();
	}

}

void CALLBACK CNProposeQuestionDlg::StaticCallBackDialogNProposeQuestionDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNProposeQuestionDlg* pThis = (CNProposeQuestionDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNProposeQuestionDlg( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNProposeQuestionDlg::CallBackDialogNProposeQuestionDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch ( nControlID	)
	{
	case PROPOSE_QUESTION_DLG_BUTTON_PROPOSE:
		{
			OnButtonClickPropose();
		}
		break;

	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	}
}

void CNProposeQuestionDlg::OnButtonClickPropose( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	// 기본 조건 검사
	if ( FALSE == CheckCondition() )
	{
		return;
	}

	CEdit* pclCharName = m_InterfaceFactory.GetEdit( PROPOSE_QUESTION_DLG_EDITBOX_NAME );
	if ( NULL == pclCharName )
	{
		return;
	}

	NTCHARString32 strCharName = pclCharName->GetText();
	
	// 캐릭터 이름을 적지 않았다면
	if ( 0 >= strCharName.Length() )
	{
		NTCHARString64	strTitle( GetTxtFromMgr(422) );
		NTCHARString256 strText( GetTxtFromMgr(9988) );

		pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
		return;
	}

	CEdit* pclMessage = m_InterfaceFactory.GetEdit( PROPOSE_QUESTION_DLG_EDITBOX_MESSAGE );
	if ( NULL == pclMessage )
	{
		return;
	}

	NTCHARString256 strMessage = pclMessage->GetText();
	
	// 전할 메시지가 없다면
	if ( 0 >= strMessage.Length() )
	{
		NTCHARString64	strTitle( GetTxtFromMgr(422) );
		NTCHARString256 strText( GetTxtFromMgr(9984) );

		pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
		return;
	}

	// 청혼 질문
	cltGameRequest_Propose_Question clInfo( strCharName, strMessage );
	cltMsg clMsg( GAMEMSG_REQUEST_PROPOSE_QUESTION, sizeof(clInfo), (BYTE*)&clInfo );
	pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );

}

CNProposeQuestionDlg::CheckCondition( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return FALSE;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return FALSE;
	}

	// 결혼 가능 레벨이 아니라면
	if ( Const_Marriage_Min_Level > pclchar->pclCI->clIP.GetLevel() )
	{
		NTCHARString64	strTitle( GetTxtFromMgr(422) );
		NTCHARString256 strText( GetTxtFromMgr(9983) );

		strText.Replace( TEXT("#level#"), SI32ToString(Const_Marriage_Min_Level) );

		pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
		return FALSE;
	}

	// 내가 이미 결혼을 했다면
	if ( TRUE == pclchar->IsMarried() )
	{
		NTCHARString64	strTitle( GetTxtFromMgr(422) );
		NTCHARString256 strText( GetTxtFromMgr(9985) );

		pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
		return FALSE;
	}

	// 가족 이용권이 없다
	if ( 0 >= pclchar->pclCI->clCharItem.GetItemNum(Const_Family_Item_Unique) )
	{
		TCHAR* pszItemName = (TCHAR*)pclclient->pclItemManager->GetName( Const_Family_Item_Unique );
		if ( pszItemName )
		{
			NTCHARString64	strTitle( GetTxtFromMgr(422) );
			NTCHARString256 strText( GetTxtFromMgr(9986) );

			strText.Replace( TEXT("#itemname#"), pszItemName );

			pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
		}
		return FALSE;
	}

	return TRUE;
}
