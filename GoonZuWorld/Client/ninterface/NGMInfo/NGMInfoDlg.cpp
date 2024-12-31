#include "NGMInfoDlg.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../Client.h"
#include "Char/CharManager/CharManager.h"
#include "Char/ParametaBox/parametabox.h"



CNGMInfoDlg::CNGMInfoDlg() : CDialogController()
{
	m_pEdit = NULL;
}

CNGMInfoDlg::~CNGMInfoDlg()
{
	SAFE_DELETE(m_pEdit);
}


void CNGMInfoDlg::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		return;
	}

	//-- ���̾�α� ����
	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/DLG_NInfo.ddf" ) );
	file.CreatePopupDialog( this, NGMINFO_DLG, TEXT( "dialog_info" ), StaticNGMInfoDlgProc );

	//-- ��ü ����
	m_pEdit = new CEdit( this );

	//-- �޼����� ����
	file.CreateControl( m_pEdit, NGMINFO_EDITBOX, TEXT("editbox_info") );

	//-- ���̾�α� ���İ� ����
	SetAlphaMode( 6 );

	//m_pEdit->SetFontWeight( 600 );
	//m_pEdit->SetFontSize( 11 );

	SetX( 340 );
	SetY( 140 );

	SetHeight( 0 );
	m_pEdit->SetHeight( 0 );
	
	SetActionTimer( 200 );
	SetTimerOnOff( true );

}

void CALLBACK CNGMInfoDlg::StaticNGMInfoDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNGMInfoDlg *pThis = (CNGMInfoDlg*) pControllerMgr;
	
	pThis->NGMInfoDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNGMInfoDlg::NGMInfoDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{

}

void CNGMInfoDlg::Action()
{
	WriteGMInfo();
}


// ���ڿ� ���õ� ������ �׸���
void CNGMInfoDlg::WriteGMInfo()
{
	cltClient*		pclclient = (cltClient*)pclClient;
	if ( pclclient == NULL )
	{
		return;
	}

	cltCharClient*	pclChar = (cltCharClient*)pclclient->pclCM->CR[1];
	if ( pclChar == NULL )
	{
		return;
	}
	
	if ( pclChar->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL )
	{
		//////////////////////////////////////////////////////////
		// �����ð� �����ֱ�
		//////////////////////////////////////////////////////////
		NTCHARString512	kGMInfo;
		NTCHARString64	kServerTime;

		// ��¥
		UI16 uiYear		= pclclient->sTime.wYear;
		UI16 uiMonth	= pclclient->sTime.wMonth;
		UI16 uiDay		= pclclient->sTime.wDay;
		// �ð�
		UI16 uiHour		= pclclient->sTime.wHour;
		UI16 uiMinute	= pclclient->sTime.wMinute;
		UI16 uiSecond	= pclclient->sTime.wSecond;


		kServerTime.FormatString( TEXT("[Server Time] %04d/%02d/%02d-%02d:%02d:%02d\r\n"), uiYear, uiMonth, uiDay, uiHour, uiMinute, uiSecond);

		//////////////////////////////////////////////////////////
		// AutoUnblock Mode ���� ���� �����ֱ�
		//////////////////////////////////////////////////////////
		NTCHARString64	kAutoUnblock	= TEXT("[Auto Unblock Mode : #mode#]\r\n");

		kAutoUnblock.Replace( TEXT("#mode#"), (pclclient->bAutoUnblock?TEXT("On"):TEXT("Off")) );

		//////////////////////////////////////////////////////////
		// Fishing Event ���� ���� �����ֱ�
		//////////////////////////////////////////////////////////
		NTCHARString64	kFishingEvent	= TEXT("[FishingEvent : #mode#]\r\n");

		kFishingEvent.Replace( TEXT("#mode#"), (pclclient->bEventToggleSwitch[EVENT_TOGGLE_SWITCH_FISHINGEVENT]?TEXT("On"):TEXT("Off")) );

		//////////////////////////////////////////////////////////
		// SystemBuy ���� ���� �����ֱ�
		//////////////////////////////////////////////////////////
		NTCHARString64	kSystemBuy	= TEXT("[SystemBuy : #mode#]");

		kSystemBuy.Replace( TEXT("#mode#"), (pclclient->bEventToggleSwitch[EVENT_TOGGLE_SWITCH_SYSTEMBUY]?TEXT("On"):TEXT("Off")) );

		//-- ���� ǥ���ϱ�
		kGMInfo = kServerTime;
		kGMInfo += kAutoUnblock;
		kGMInfo += kFishingEvent;
		kGMInfo += kSystemBuy;
		
		m_pEdit->SetText( kGMInfo );
	}

}
