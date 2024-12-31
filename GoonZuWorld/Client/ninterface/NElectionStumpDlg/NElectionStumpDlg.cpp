// [����] �⼮üũ
#include "NElectionStumpDlg.h"

#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/OutLine.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../../NLib/NTCHARString.h"
#include "../../CommonLogic/TextMgr/TextMgr.h"
#include "../../Client/Client.h"

#include "../CommonLogic/Msg/MsgType-Vote.h"
#include "../common/Char/CharManager/CharManager.h"


CNElectionStumpDlg::CNElectionStumpDlg() : CDialogController()
{
	/*	
	SI32 siCount = 0;

	
	for ( siCount=0; siCount<NELECTIONSTUMP_BUTTON_MAX; siCount++ )
	{
		m_pButton[siCount] = NULL;
	}

	for (  siCount=0; siCount<NELECTIONSTUMP_EDIT_MAX; siCount++ )
	{
		m_pEdit[siCount] = NULL;
	}

	for ( siCount=0; siCount<NELECTIONSTUMP_STATIC_MAX; siCount++ )
	{
		m_pStatic[siCount] = NULL;
	}

	for ( siCount=0; siCount<NELECTIONSTUMP_OUTLINE_MAX; siCount++ )
	{
		m_pOutLine[siCount] = NULL;
	}
	*/

	m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START]	= NULL;
	m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END]		= NULL;
	m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM]		= NULL;
	m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM]		= NULL;

	m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE]			= NULL;
	m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE]		= NULL;

	m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE]		= NULL;
	m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE]	= NULL;

	m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE]	= NULL;
	m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE]	= NULL;

	m_bDialogMode		= NELECTIONSTUMP_DIALOG_MODE_MINIMUM;

	m_siDialogWidth		= 0;
	m_siDialogHeight	= 0;
}


CNElectionStumpDlg::~CNElectionStumpDlg()
{
	/*
	SI32 siCount = 0;


	for ( siCount=0; siCount<NELECTIONSTUMP_BUTTON_MAX; siCount++ )
	{
		SAFE_DELETE( m_pButton[siCount] );
	}

	for (  siCount=0; siCount<NELECTIONSTUMP_EDIT_MAX; siCount++ )
	{
		SAFE_DELETE( m_pEdit[siCount] );
	}

	for (  siCount=0; siCount<NELECTIONSTUMP_STATIC_MAX; siCount++ )
	{
		SAFE_DELETE( m_pStatic[siCount] );
	}

	for (  siCount=0; siCount<NELECTIONSTUMP_OUTLINE_MAX; siCount++ )
	{
		SAFE_DELETE( m_pOutLine[siCount] );
	}
	*/
	
	SAFE_DELETE( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START] );
	SAFE_DELETE( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END] );
	SAFE_DELETE( m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM] );
	SAFE_DELETE( m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM] );

	SAFE_DELETE( m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE] );
	SAFE_DELETE( m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE] );

	SAFE_DELETE( m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE] );
	SAFE_DELETE( m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE] );

	SAFE_DELETE( m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE] );
	SAFE_DELETE( m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE] );
}


void CNElectionStumpDlg::Create()
{
	// �̹� �ִٸ�
	if ( IsCreate() == true )
	{
		return;
	}

	// ���̾�α׸� ����
	CInterfaceFile file;

	file.LoadFile( TEXT("NInterface/Data/NElectionStumpDlg/DLG_NElectionStump.ddf") );
	file.CreatePopupDialog( this, ELECTIONSTUMP_DLG,  TEXT("dialog_election_stump"), StaticElectionStumpDlgProc );

	// ��ü�� �����ϰ�
	NEWCBUTTON( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START] );
	NEWCBUTTON( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END] );
	NEWCBUTTON( m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM] );
	NEWCBUTTON( m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM] );

	NEWCEDIT( m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE] );
	NEWCEDIT( m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE] );

	NEWCSTATIC( m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE] );
	NEWCSTATIC( m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE] );

	NEWCOUTLINE( m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE] );
	NEWCOUTLINE( m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE] );

	// ������ ��ü�� �޽����� �����Ѵ�.
	file.CreateControl( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START],	ELECTIONSTUMP_DLG_BUTTON_STUMP_START,	TEXT("button_stump_start") );
	file.CreateControl( m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END],		ELECTIONSTUMP_DLG_BUTTON_STUMP_END,		TEXT("button_stump_end") );
	file.CreateControl( m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM],		ELECTIONSTUMP_DLG_BUTTON_MINIMUM,		TEXT("button_minimum") );
	file.CreateControl( m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM],		ELECTIONSTUMP_DLG_BUTTON_MAXIMUM,		TEXT("button_maximum") );

	file.CreateControl( m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE],			ELECTIONSTUMP_DLG_EDIT_CANDIDATE,		TEXT("editbox_candidate") );
	file.CreateControl( m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE],		ELECTIONSTUMP_DLG_EDIT_MAINTENANCE,		TEXT("editbox_maintenance") );

	file.CreateControl( m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE],		ELECTIONSTUMP_DLG_STATIC_CANDIDATE,		TEXT("statictext_candidate") );
	file.CreateControl( m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE],	ELECTIONSTUMP_DLG_STATIC_MAINTENANCE,	TEXT("statictext_maintenance") );

	file.CreateControl( m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE],	ELECTIONSTUMP_DLG_OUTLINE_CANDIDATE,	TEXT("outline_candidate") );
	file.CreateControl( m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE],	ELECTIONSTUMP_DLG_OUTLINE_MAINTENANCE,	TEXT("outline_maintenance") );

	// ���� ���ѻ���
	m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE]->SetMaxEditTextLength( (Const_Max_Candidate - 1) );
	m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE]->SetMaxEditTextLength( (Const_Max_Maintenance - 1) );;


	// ���� ���̾�α� ũ�� ���
	m_siDialogWidth		= GetWidth();
	m_siDialogHeight	= GetHeight();

	// ���� �������̶�� ������ ��Ʈ�ѿ� ����
	PreLoadInformation();

	SetDialogMode( NELECTIONSTUMP_DIALOG_MODE_MAXIMUM );

}


void CALLBACK CNElectionStumpDlg::StaticElectionStumpDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNElectionStumpDlg *pThis = (CNElectionStumpDlg *)pControllerMgr;
	pThis->NElectionStumpDlgProc( nEvent, nControlID, pControl );
}


void CALLBACK CNElectionStumpDlg::NElectionStumpDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	switch ( nControlID )
	{
		case ELECTIONSTUMP_DLG_BUTTON_STUMP_START:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						StartElectionStump();
					}
				}
			}
			break;

		case ELECTIONSTUMP_DLG_BUTTON_STUMP_END:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						EndElectionStump();
						DeleteDialog();
					}
				}
			}
			break;

		case ELECTIONSTUMP_DLG_BUTTON_MINIMUM:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						SetDialogMode( NELECTIONSTUMP_DIALOG_MODE_MINIMUM );
					}
				}
			}
			break;

		case ELECTIONSTUMP_DLG_BUTTON_MAXIMUM:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						SetDialogMode( NELECTIONSTUMP_DIALOG_MODE_MAXIMUM );
					}
				}
			}
			break;
		

	} // switch ( nControlID ) ����

}

void CNElectionStumpDlg::Action()
{

}


void CNElectionStumpDlg::Destroy()
{

}


void CNElectionStumpDlg::Init()
{

}


void CNElectionStumpDlg::StartElectionStump()
{
	TCHAR		tszCandidate[Const_Max_Candidate]		= {'\0', };
	TCHAR		tszMaintenance[Const_Max_Maintenance]	= {'\0', };
	cltClient*	pclclient								= (cltClient *)pclClient;
	

	if ( pclclient == NULL )
	{
		return;
	}

	cltCharClient *pclChar = (cltCharClient *)pclClient->pclCM->CR[1];
	if ( pclChar == NULL )
	{
		return;
	}

	// ���� ������ ���� �ִٸ� �ȵȴ�
	if ( (pclChar->bPersonalShopSwitch == true) || (pclChar->bPremiumPersonalShop == true) )
	{
		if ( pclclient->m_pDialog[NOTIFYMSG_DLG] )
		{
			TCHAR *pTitle	= GetTxtFromMgr(836);
			TCHAR *pText	= GetTxtFromMgr(8280);
			
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		}

		return;
	}
	
	// �̹� �������̶�� ����
	if ( pclClient->pclCM->CR[1]->bIsElectionStump == true )
	{
		return;
	}

	// �ĺ��ڸ�,���������� �Էµ��� �ʾҴٸ� �޽��� ���� ����
	if ( (_tcscmp( m_pEdit[ NELECTIONSTUMP_EDIT_CANDIDATE ]->GetText(), TEXT("") ) == 0)
		|| (_tcscmp( m_pEdit[ NELECTIONSTUMP_EDIT_MAINTENANCE ]->GetText(), TEXT("") ) == 0)
	)
	{
		TCHAR* ptszTitle	= GetTxtFromMgr( 5614 );
		TCHAR* ptszExplain	= GetTxtFromMgr( 8057 );

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( ptszTitle, ptszExplain );
		return;
	}

	StringCchCopy( tszCandidate, Const_Max_Candidate, m_pEdit[ NELECTIONSTUMP_EDIT_CANDIDATE ]->GetText() );
	tszCandidate[ Const_Max_Candidate - 1 ] = '\0';

	StringCchCopy( tszMaintenance, Const_Max_Maintenance, m_pEdit[ NELECTIONSTUMP_EDIT_MAINTENANCE ]->GetText() );
	tszMaintenance[ Const_Max_Maintenance - 1 ] = '\0';


	cltGameMsgRequest_StartElectionStump sendMsg( tszCandidate, tszMaintenance );
	cltMsg clMsg( GAMEMSG_REQUEST_STARTELECTIONSTUMP, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

}


void CNElectionStumpDlg::EndElectionStump()
{
	cltClient*	pclclient = (cltClient *)pclClient;
	if ( pclclient == NULL )
	{
		return;
	}

	// ������ Ȱ���� ���� ������ �ʾ���
	if ( pclClient->pclCM->CR[1]->bIsElectionStump == false )
	{
		return;
	}


	cltMsg clMsg( GAMEMSG_REQUEST_ENDELECTIONSTUMP, 0, NULL );
	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
}

void CNElectionStumpDlg::PreLoadInformation()
{
	// ���� ���� ���϶� â�� �����ٸ� ���� ������ Dialog�� ������
	cltCharClient *pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
	if ( pclChar == NULL )
	{
		return;
	}

	if ( pclChar->bIsElectionStump == false )
	{
		return;
	}

	m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE]->SetText( pclChar->szCandidate );
	m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE]->SetText( pclChar->szMaintenance );
}

void CNElectionStumpDlg::SetDialogMode( bool bDialogMode )
{
	if ( bDialogMode == NELECTIONSTUMP_DIALOG_MODE_MINIMUM )
	{
		// ������ ��Ʈ��
		m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM]->Show( true );

		// �Ⱥ����� ��Ʈ��
		m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START]->Show( false );
		m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END]->Show( false );
		m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM]->Show( false );

		m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE]->Show( false );
		m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE]->Show( false );

		m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE]->Show( false );
		m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE]->Show( false );

		m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE]->Show( false );
		m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE]->Show( false );

		// ���̾�α� ��ġ ����
		SetDialogPos( GetX(), GetY(), NELECTIONSTUMP_DIALOG_MININUM_WIDTH, NELECTIONSTUMP_DIALOG_MININUM_HEIGHT );
		
	}
	else
	{
		// �Ⱥ����� ��Ʈ��
		m_pButton[NELECTIONSTUMP_BUTTON_MAXIMUM]->Show( false );

		// ������ ��Ʈ��
		m_pButton[NELECTIONSTUMP_BUTTON_STUMP_START]->Show( true );
		m_pButton[NELECTIONSTUMP_BUTTON_STUMP_END]->Show( true );
		m_pButton[NELECTIONSTUMP_BUTTON_MINIMUM]->Show( true );

		m_pEdit[NELECTIONSTUMP_EDIT_CANDIDATE]->Show( true );
		m_pEdit[NELECTIONSTUMP_EDIT_MAINTENANCE]->Show( true );

		m_pStatic[NELECTIONSTUMP_STATIC_CANDIDATE]->Show( true );
		m_pStatic[NELECTIONSTUMP_STATIC_MAINTENANCE]->Show( true );

		m_pOutLine[NELECTIONSTUMP_OUTLINE_CANDIDATE]->Show( true );
		m_pOutLine[NELECTIONSTUMP_OUTLINE_MAINTENANCE]->Show( true );

		// ���̾�α� ��ġ ����
		SetDialogPos( GetX(), GetY(), m_siDialogWidth, m_siDialogHeight );

	}

	m_bDialogMode = bDialogMode;
}