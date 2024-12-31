
#include "NCarryOver_ProductDlg.h"
#include "NCarryOverGachaDlg.h"
#include "NCarryOver_ResultDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

#include "../../../common/Char/CharManager/CharManager.h"

#include "../../Client/ninterface/ngachadlg/NOpenBoxDlg.h"

extern cltCommonLogic* pclClient;

CNCarryOver_ProductDlg::CNCarryOver_ProductDlg( void )
{
	m_siKeyKind						= 0;

	m_siSelectGachaProductIndex		= -1;
	m_siSelectGachaProductUnique	= 0;

	m_siBestItemUnique				= 0;
}

CNCarryOver_ProductDlg::~CNCarryOver_ProductDlg( void )
{

}

void CNCarryOver_ProductDlg::Init( )
{
		
}

void CNCarryOver_ProductDlg::Create( )
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NCarryOverGacha/DLG_NCarryOver_ProductDlg.ddf" ) );
	file.CreatePopupDialog( this, NGACHAPRODUCT_DLG, TEXT( "dialog_gachaproduct" ), StaticCallBackDialogNCarryOver_ProductDlg );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		GACHAPRODUCT_DLG_BUTTON_GAMESTART,			this), GACHAPRODUCT_DLG_BUTTON_GAMESTART,		TEXT("button_gamestart") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,		GACHAPRODUCT_DLG_BUTTON_BACK,				this), GACHAPRODUCT_DLG_BUTTON_BACK,			TEXT("button_back") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(EDIT,		GACHAPRODUCT_DLG_EDITBOX_EXPLAIN,			this), GACHAPRODUCT_DLG_EDITBOX_EXPLAIN,		TEXT("editbox_explain") );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(IMAGESTATIC,	GACHAPRODUCT_DLG_IMAGESTATIC_BACKGROUND,	this), GACHAPRODUCT_DLG_IMAGESTATIC_BACKGROUND,	TEXT("imagestatic_background") );

	// ���̾�α� â ��ġ ���� ����
	SetTopMostWindow( true );
	
	// PCK : �����̽��� ����Ű�� ��������, �ٷ� ���ӽ����� �ǵ��� ��Ŀ���� �����Ѵ�. (09.04.16)
	RequestFocus( m_InterfaceFactory.GetButton(GACHAPRODUCT_DLG_BUTTON_GAMESTART) );

	if( g_bFullScreen)	
	{
		MovePos( 80, 40 );
	}
	else		 		
	{
		MovePos( 45, 20 );
	}

	SetWidth( 0 );
}

void CALLBACK CNCarryOver_ProductDlg::StaticCallBackDialogNCarryOver_ProductDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNCarryOver_ProductDlg* pThis = (CNCarryOver_ProductDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNCarryOver_ProductDlg( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNCarryOver_ProductDlg::CallBackDialogNCarryOver_ProductDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch(nControlID)
	{
	case GACHAPRODUCT_DLG_BUTTON_GAMESTART:
		{
			switch(nEvent)
			{
			case EVENT_BUTTON_CLICKED:	
				{
					OnClickGameStart();
				}
				break;
			}
		}
		break;

	case GACHAPRODUCT_DLG_BUTTON_BACK:
		{
			switch(nEvent)
			{
			case EVENT_BUTTON_CLICKED:	
				{
					OnClickBack();
				}
				break;
			}
		}
		break;
	}

}

void CNCarryOver_ProductDlg::Show()
{
	CControllerMgr::Show( true );

}

void CNCarryOver_ProductDlg::Hide()
{
	CControllerMgr::Show( false );
}

void CNCarryOver_ProductDlg::OnClickGameStart( void )
{
 	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
	if ( NULL == pclchar )
	{
		return;
	}

	// ���̻� ���� �� ���ٸ�
	if ( false == pclchar->IsBlankInv(1, INVMODE_ALL) )
	{
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6634) );

		pclclient->m_pDialog[NCARRYOVERGACHA_DLG]->DeleteDialog();
		return;
	}

	// Ű �������� �ִ��� �˻�
	if ( false == ((CNCarryOverGachaDlg*)pclclient->m_pDialog[NCARRYOVERGACHA_DLG])->IsHaveKey( ) )
	{
		(m_InterfaceFactory.GetButton(GACHAPRODUCT_DLG_BUTTON_GAMESTART))->Enable( false );
		return;
	}

	// ��� â�� �ְ��ǰ ���� ����
	if ( NULL == pclclient->m_pDialog[NGACHARESULT_DLG] )
	{
		pclclient->CreateInterface( NGACHARESULT_DLG );
	}

	((CNCarryOver_ResultDlg*)pclclient->m_pDialog[NGACHARESULT_DLG])->SetInfo( m_siBestItemUnique );

	// ���� ���� ���̾�α� ����
	pclclient->CreateInterface( NOPENBOX );

	if ( NULL == pclclient->m_pDialog[NOPENBOX] )
	{
		pclclient->m_pDialog[NCARRYOVERGACHA_DLG]->DeleteDialog();
		return;
	}

	((CNOpenBoxDlg*)pclclient->m_pDialog[NOPENBOX])->SetCarryOverInfo( m_siKeyKind, m_siSelectGachaProductIndex, m_siSelectGachaProductUnique );

	// ���� ��ư�� ��Ŀ���� ���ֹ�����
    // CButton* pclButton = m_InterfaceFactory.GetButton( GACHAPRODUCT_DLG_BUTTON_GAMESTART );
	//if ( pclButton )
	//{
	//	ClearFocus();
	//}

}

void CNCarryOver_ProductDlg::OnClickBack( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		DeleteDialog();
		return;
	}

	if ( NULL == pclclient->m_pDialog[NCARRYOVERGACHA_DLG] )
	{
		DeleteDialog();
		return;
	}

	((CNCarryOverGachaDlg*)pclclient->m_pDialog[NCARRYOVERGACHA_DLG])->OnEventBack();

	DeleteDialog();
}

void CNCarryOver_ProductDlg::SetInfo( const SI32 siItemUnique, const SI32 siKeyKind, const SI32 siSelectGachaProductIndex, const SI32 siSelectGachaProductUnique )
{
	// Ű ī�ε�
	m_siKeyKind						= siKeyKind;

	// ��ǰ����
	m_siSelectGachaProductIndex		= siSelectGachaProductIndex;
	m_siSelectGachaProductUnique	= siSelectGachaProductUnique;

	m_siBestItemUnique				= siItemUnique;

	// �ְ� ��í ��ǰ ����
	if ( 0 >= m_siBestItemUnique )
	{
		return;
	}

	CEdit* pclExplain = m_InterfaceFactory.GetEdit( GACHAPRODUCT_DLG_EDITBOX_EXPLAIN );
	if ( NULL == pclExplain )
	{
		return;
	}

	TCHAR* pszItemName = (TCHAR*)pclClient->pclItemManager->GetName( m_siBestItemUnique );
	if ( NULL == pszItemName )
	{
		return;
	}

	NTCHARString512 strExplain = GetTxtFromMgr( 7017 );

	strExplain.Replace( TEXT("#gacharareitemname#"), pszItemName );

	pclExplain->SetText( strExplain );

}