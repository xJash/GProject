#include "NGiantRaccoonResurrectEventDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../Client/ninterface/nsoundonoffdlg/NSoundOnOffDlg.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/MsgType-Item.h"


NGiantRaccoonResurrectEventDlg::NGiantRaccoonResurrectEventDlg()
{

}


NGiantRaccoonResurrectEventDlg::~NGiantRaccoonResurrectEventDlg()
{
}

void NGiantRaccoonResurrectEventDlg::Create()
{
	if( IsCreate() )	return;

	// ��� ���õ� �������̽��� �����Ѵ�.
	NContributionEvent_CommonDlg::Create( NGIANTRACCOONRESURRECTEVENTDLG, this, StaticNGiantRaccoonResurrectEventDlgProc );

	SetTitle( GetTxtFromMgr(7653) );	
	
	// ���� ����.
	SetExplainText( GetTxtFromMgr(40427) );
	SetActionButtonText( GetTxtFromMgr(40787) );

	// ���� ��� �������� ����Ʈ�� ���´�.
	GetContributionItemList( pclClient->GetUniqueFromHash( "KIND_RACCOONTREEBASE" ) );
} 

void CALLBACK NGiantRaccoonResurrectEventDlg::StaticNGiantRaccoonResurrectEventDlgProc( CControllerMgr *pControllerMgr, UINT nEvent )
{
	NGiantRaccoonResurrectEventDlg *pThis = (NGiantRaccoonResurrectEventDlg *)pControllerMgr;
	pThis->NGiantRaccoonResurrectEventDlgProc( nEvent );
}


void CALLBACK NGiantRaccoonResurrectEventDlg::NGiantRaccoonResurrectEventDlgProc( UINT nEvent )
{
	cltClient * pclclient = (cltClient*) pclClient;

	switch( nEvent )
	{
		case EVENT_CONTRIBUTION_BUTTON_CLICK:
			{
								
			}
			break;
		case EVENT_ACTION_BUTTON_CLICK:
			{

			}
			break;
			
		case EVENT_ACTION_CONTRIBUTION_COMPLETE:
			{
				int a = 0;
			}
			break;
		default:
			{

			}
			break;
	}

}

