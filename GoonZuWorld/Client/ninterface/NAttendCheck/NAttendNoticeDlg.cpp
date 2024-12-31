// [����] �⼮üũ
#include "NAttendNoticeDlg.h"
#include "NAttendCheckDlg.h"

#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Button.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../../NLib/NTCHARString.h"
#include "../../CommonLogic/TextMgr/TextMgr.h"
#include "../../Client/Client.h"


CNAttendNoticeDlg::CNAttendNoticeDlg() : CDialogController()
{
	/*
	SI32 siCount = 0;


	for ( siCount=0; siCount<ATTENDNOTICE_EDIT_MAX; siCount++ )
	{
		m_pEdit[siCount]	= NULL;
	}
	
	for ( siCount=0; siCount<ATTENDNOTICE_BUTTON_MAX; siCount++ )
	{
		m_pButton[siCount]	= NULL;
	}
	*/

	//------------------------------------------------------------------
	//
	//	���̻� �߰��� ���� ���� ������ ���� �ݺ��� ���� �׳� ���ش�
	//
	//------------------------------------------------------------------
	m_pEdit[ATTENDNOTICE_EDIT_NOTICE]			= NULL;
	m_pEdit[ATTENDNOTICE_EDIT_INFORMATION]		= NULL;

	m_pButton[ATTENDNOTICE_BUTTON_STAMP]		= NULL;
	m_pButton[ATTENDNOTICE_BUTTON_CANCEL]		= NULL;

	m_siAttendenceDays = 0;
	m_siNextRewardDays = 0;
}

CNAttendNoticeDlg::~CNAttendNoticeDlg()
{
	/*
	SI32 siCount = 0;


	for ( siCount=0; siCount<ATTENDNOTICE_EDIT_MAX; siCount++ )
	{
		SAFE_DELETE(m_pEdit[siCount]);
	}

	for ( siCount=0; siCount<ATTENDNOTICE_BUTTON_MAX; siCount++ )
	{
		SAFE_DELETE(m_pButton[siCount]);
	}
	*/

	//------------------------------------------------------------------
	//
	//	���̻� �߰��� ���� ���� ������ ���� �ݺ��� ���� �׳� ���ش�
	//
	//------------------------------------------------------------------
	SAFE_DELETE( m_pEdit[ATTENDNOTICE_EDIT_NOTICE] );
	SAFE_DELETE( m_pEdit[ATTENDNOTICE_EDIT_INFORMATION] );

	SAFE_DELETE( m_pButton[ATTENDNOTICE_BUTTON_STAMP] );
	SAFE_DELETE( m_pButton[ATTENDNOTICE_BUTTON_CANCEL] );

}

void CNAttendNoticeDlg::Create()
{
	// �̹� �ִٸ�
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	// ���̾�α׸� ����
	CInterfaceFile file;

	file.LoadFile( TEXT("NInterface/Data/NAttendCheck/DLG_NAttendNotice.ddf") );
	file.CreatePopupDialog( this, ATTENDNOTICE_DLG,  TEXT("dialog_attendnotice"), StaticAttendNoticeDlgProc );

	// ��ü�� �����ϰ�
	NEWCEDIT( m_pEdit[ATTENDNOTICE_EDIT_NOTICE] );
	NEWCEDIT( m_pEdit[ATTENDNOTICE_EDIT_INFORMATION] );

	NEWCBUTTON( m_pButton[ATTENDNOTICE_BUTTON_STAMP] );
	NEWCBUTTON( m_pButton[ATTENDNOTICE_BUTTON_CANCEL] );

	// ������ ��ü�� �޽����� �����Ѵ�.
	file.CreateControl( m_pEdit[ATTENDNOTICE_EDIT_NOTICE],				ATTENDNOTICE_DLG_EDIT_NOTICE,			TEXT("editbox_notice") );
	file.CreateControl( m_pEdit[ATTENDNOTICE_EDIT_INFORMATION],			ATTENDNOTICE_DLG_EDIT_INFORMAITON,		TEXT("editbox_information") );

	file.CreateControl( m_pButton[ATTENDNOTICE_BUTTON_STAMP],			ATTENDNOTICE_DLG_BUTTON_STAMP,			TEXT("button_stamp") );
	file.CreateControl( m_pButton[ATTENDNOTICE_BUTTON_CANCEL],			ATTENDNOTICE_DLG_BUTTON_CANCEL,			TEXT("button_cancel") );


	NTCHARString256 kNotice( GetTxtFromMgr(7990) );
	m_pEdit[ATTENDNOTICE_EDIT_NOTICE]->SetText( kNotice, RGB(0,0,0) );

	SetTopMostWindow( true );
	
}

void CALLBACK CNAttendNoticeDlg::StaticAttendNoticeDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNAttendNoticeDlg *pThis = (CNAttendNoticeDlg *)pControllerMgr;
	pThis->NAttendNoticeDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNAttendNoticeDlg::NAttendNoticeDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch ( nControlID )
	{
		case COMMON_DIALOG_CLOSEBUTTON:
			{
				DeleteDialog();
			}
			break;

		case ATTENDNOTICE_DLG_BUTTON_STAMP:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						cltClient *pclclient = (cltClient*)pclClient;

						if ( pclclient->m_pDialog[ NATTENDCHECK_DLG ] == NULL )
						{
							pclclient->CreateInterface( NATTENDCHECK_DLG );
						}
						
						((CNAttendCheckDlg*)pclclient->m_pDialog[ NATTENDCHECK_DLG ])->SetDialogMode( NATTENDCHECKDLG_MODE_MAXIMUM);
						DeleteDialog();
					}
					break;
				}
			}
			break;

		case ATTENDNOTICE_DLG_BUTTON_CANCEL:
			{
				switch( nEvent )
				{
				case EVENT_BUTTON_CLICKED:
					{
						DeleteDialog();
					}
					break;
				}
			}
			break;

	} // switch ( nControlID ) ����

}

void CNAttendNoticeDlg::Init()
{
}

void CNAttendNoticeDlg::Destroy()
{
}

void CNAttendNoticeDlg::Action()  
{
}

void CNAttendNoticeDlg::Show( bool bShow )
{
	CDialogController::Show( bShow );
}

void CNAttendNoticeDlg::SetInfo( SI16 siAttendenceDay, SI16 siNextRewardDay )
{
	if ( siAttendenceDay >= 0 )
	{
		m_siAttendenceDays = siAttendenceDay;
	}

	if ( siNextRewardDay >= 0 )
	{
		m_siNextRewardDays = siNextRewardDay;
	}

	NTCHARString256 kInfo( GetTxtFromMgr( 7991 ) );

	kInfo.Replace( TEXT("#totalstamp#"), SI16ToString( m_siAttendenceDays ) );
	kInfo.Replace( TEXT("#needstamp#"), SI16ToString( m_siNextRewardDays ) );

	m_pEdit[ATTENDNOTICE_EDIT_INFORMATION]->SetText( kInfo );
}