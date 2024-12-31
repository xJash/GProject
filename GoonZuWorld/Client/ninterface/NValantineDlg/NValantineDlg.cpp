//-----------------------------------------------------------------------------------------------
//	�ۼ���		:	�ռ���
//	�ۼ�����	:	2008-12-10
//	����		:	�߷�Ÿ�ε��� �̺�Ʈ�� �ʱ⿡ �ڽ��� Ŀ������ �ַ����� �����ϴ� ���̾�α�
//
//-----------------------------------------------------------------------------------------------


#include "NValantineDlg.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../../common/Char/CharManager/CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"

CNValantineDlg::CNValantineDlg() : CDialogController()
{
}

CNValantineDlg::~CNValantineDlg()
{

}

void CNValantineDlg::Create()
{
	if ( IsCreate() )
		return;

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NValantineDlg/DLG_NValantine.ddf" ) );  
	file.CreatePopupDialog( this, NVALANTINE_DLG, TEXT( "dialog_ValantineNotice" ), StaticNValantineDlgProc );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(STATIC, VALANTINE_STATIC_QUESTION, this), VALANTINE_STATIC_QUESTION,	"statictext_Qusetion");
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, VALANTINE_BUTTON_COUPLE, this), VALANTINE_BUTTON_COUPLE,	"button_couple");
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON, VALANTINE_BUTTON_SOLO, this), VALANTINE_BUTTON_SOLO,	"button_solo");

	cltClient* pclclient = (cltClient*)pclClient;
	SI16 xPos = ( pclclient->GetScreenXSize() - GetWidth() ) / 2 + 40;
	SI16 yPos = ( pclclient->GetScreenYSize() - GetHeight() ) / 2;
	MovePos( xPos, yPos );

}
void CALLBACK CNValantineDlg::StaticNValantineDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNValantineDlg *pThis = (CNValantineDlg*) pControllerMgr;
	pThis->NValantineDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNValantineDlg::NValantineDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient* pclclient = (cltClient*)pclClient;
	switch( nControlID )
	{
		case COMMON_DIALOG_CLOSEBUTTON:// Ŭ���� X ��ư�� ������ ���� �ð��� ���� �ؼ� ������ �����ش�.
			{
				SendMyStatus( VALENTINEWAR_NONE );
				DeleteDialog();
			}
			break;
		case VALANTINE_BUTTON_COUPLE:// Ŀ���Դϴ� ��ư
			{
				SendMyStatus( VALENTINEWAR_COUPLE );
				DeleteDialog();
				MsgBox();
			}
			break;
		case VALANTINE_BUTTON_SOLO:// �ַ� �Դϴ� ��ư
			{
				SendMyStatus( VALENTINEWAR_SOLO );
				DeleteDialog();
				MsgBox();
			}
			break;
	}
}
void CNValantineDlg::SendMyStatus(SI32 siMyStatus )
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltGameMsgRequest_ValentineWar_Request clinfo (  pclclient->pclCM->CR[1]->GetID(), siMyStatus );
	cltMsg clMsg(GAMEMSG_REQUEST_VALENTINE_REQUEST, sizeof(clinfo), (BYTE*)&clinfo);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
}
void CNValantineDlg::MsgBox()
{
	cltClient* pclclient = (cltClient*)pclClient;

	// �ؽ�Ʈ �� �˷��ش�
	TCHAR* pTitle= GetTxtFromMgr(9766)	;
	TCHAR* itemname = (TCHAR*)pclClient->pclItemManager->GetName( ITEMUNIQUE(2781));
	NTCHARString512		kText( GetTxtFromMgr(9767) );
	kText.Replace("#itemname#",  itemname );

	pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, kText );
}
