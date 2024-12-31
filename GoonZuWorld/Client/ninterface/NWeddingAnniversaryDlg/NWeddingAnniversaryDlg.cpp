#include "NWeddingAnniversaryDlg.h"

#include "../../Client.h"

#include "../../common/Char/CharManager/CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"


extern cltCommonLogic* pclClient;

CNWeddingAnniversaryDlg::CNWeddingAnniversaryDlg() : CDialogController()
{
	m_pclGetItem = NULL;

	m_updateTimer.Init( 1000 * 30 ); // 30���Ŀ� ����ȴ�
}

CNWeddingAnniversaryDlg::~CNWeddingAnniversaryDlg()
{
	SAFE_DELETE( m_pclGetItem );
}

void CNWeddingAnniversaryDlg::Init()
{

}

void CNWeddingAnniversaryDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		DeleteDialog();
		return;
	}

	SI16 siDialogWidth	= 200;
	SI16 siDialogHeight	= 200;

	SI16 siDialogXpos	= (pclclient->GetScreenXSize() - siDialogWidth + MAP_TILE_XSIZE) / 2;
	SI16 siDialogYpos	= 100;

	// ���̾�α� ����
	CDialogController::Create( NWEDDINGANNIVERSARY_DLG, CONTROLLER_KIND_POPUPDIALOG, NULL, StaticCallBackDialogNWeddingAnniversary, NULL, NULL, 0, false, 0, siDialogXpos, siDialogYpos, siDialogWidth, siDialogHeight, false, false, false );

	// ������ �ޱ� ��ư
	NEWCBUTTON( m_pclGetItem );
	m_pclGetItem->Create( 0, TEXT(""), TEXT("NInterface/Button/BUTTON_200x200_00_000.SPR"), 0, false, 0, 0, 0, siDialogWidth, siDialogHeight, siDialogWidth, siDialogHeight );

	SetActionTimer( 1000 );
	SetTimerOnOff( true );

	m_updateTimer.SetActive( true, GetTickCount() );

}

void CNWeddingAnniversaryDlg::Action()
{
	if ( true == m_updateTimer.IsTimed(GetTickCount(), false) )
	{
		DeleteDialog();
	}
}

void CALLBACK CNWeddingAnniversaryDlg::StaticCallBackDialogNWeddingAnniversary( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNWeddingAnniversaryDlg* pThis = (CNWeddingAnniversaryDlg*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNWeddingAnniversary( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNWeddingAnniversaryDlg::CallBackDialogNWeddingAnniversary( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch ( nControlID )
	{
	case 0:// �ޱ��ư Ŭ��
		{
			OnClickButtonGetItem();
		}
		break;
	}
}

void CNWeddingAnniversaryDlg::OnClickButtonGetItem( void )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclchar )
	{
		return;
	}

	// ��ȥ�� ���ߴµ� �̹�ư�� Ŭ���ߴٸ�
	if ( FALSE == pclchar->IsMarried() )
	{
		return;
	}

	// ������ �ޱ� ��û
	cltMsg clMsg( GAMEMSG_REQUEST_WEDDINGANNIVERSARY_ITEMGET, 0 );
	pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );
	
}