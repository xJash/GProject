
#include "NFamilyInfoDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../../common/Char/CharManager/CharManager.h"
#include "../../common/Family/Marriage.h"
#include "../../common/Family/Family.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Person.h"

#include "../../ninterface//NFamilyInfoDlg/NFamily_Add_ChildrenDlg.h"

extern cltCommonLogic* pclClient;

CNFamily_Add_ChildrenDlg::CNFamily_Add_ChildrenDlg( void )
{

}

CNFamily_Add_ChildrenDlg::~CNFamily_Add_ChildrenDlg( void )
{

}

void CNFamily_Add_ChildrenDlg::Init( )
{
		
}

void CNFamily_Add_ChildrenDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NFamilyDlg/DLG_NFamily_Add_Children.ddf" ) );
	file.CreatePopupDialog( this, NFAMILY_DLG_ADD_CHILDREN, TEXT( "dialog_NONAME1" ), StaticCallBackDialogAddChildrenoDlg );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC,	CNFamily_Add_ChildrenDlg_STATIC_COMMENT,	this),	CNFamily_Add_ChildrenDlg_STATIC_COMMENT,	TEXT("statictext_NONAME1") );	// �̸�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,	CNFamily_Add_ChildrenDlg_EDIT_CHARNAME,	this),	CNFamily_Add_ChildrenDlg_EDIT_CHARNAME,	TEXT("editbox_NONAME1") );	// �̸�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,	CNFamily_Add_ChildrenDlg_BUTTON_REQUEST,		this),	CNFamily_Add_ChildrenDlg_BUTTON_REQUEST,		TEXT("button_NONAME1") );	// ��û
	

	SetActionTimer( 1000 );
	SetTimerOnOff( true );
	
}

void CALLBACK CNFamily_Add_ChildrenDlg::StaticCallBackDialogAddChildrenoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNFamily_Add_ChildrenDlg* pThis = (CNFamily_Add_ChildrenDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogAddChildrenDlg( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNFamily_Add_ChildrenDlg::CallBackDialogAddChildrenDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient * pclclient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar ){		return;		}

	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
			
		}break	;
	case CNFamily_Add_ChildrenDlg_BUTTON_REQUEST:
		{
			// ��ư�� ������ .�ش� �ɸ��� �̸��� ĳ�� �ؼ� �ڳ�� ���.
			CEdit* pEditCharName = m_InterfaceFactory.GetEdit( CNFamily_Add_ChildrenDlg_EDIT_CHARNAME );
			if( pEditCharName == NULL  )	return	;
			TCHAR* pCharname = pEditCharName->GetText() ;	// �̸��� ������ �´�.
			//�̸��� ������ ������.
			cltGameRequest_Request_Add_Children clInfo( pCharname );
			cltMsg clMsg( GAMEMSG_REQUEST_FAMILY_REQUEST_ADD_CHILDREN, sizeof(clInfo), (BYTE*)&clInfo );	// ������������ �ɰ��� ��û�Ѵ�.
			pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );
			DeleteDialog();

		}
	}
}

void CNFamily_Add_ChildrenDlg::Action()
{
	cltClient* pclclient = (cltClient*)pclClient;
}
void CNFamily_Add_ChildrenDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 1:	
		{
			if ( true == RetValue )
			{
			}
		}
	}
}