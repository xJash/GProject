
#include "NPCRoom_Reward.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Client.h"

extern cltCommonLogic* pclClient;

CNPCRoom_Reward::CNPCRoom_Reward( void )
{

}

CNPCRoom_Reward::~CNPCRoom_Reward( void )
{

}

void CNPCRoom_Reward::Init( )
{
		
}

void CNPCRoom_Reward::Create()
{
	//-- �̹� �����Ǿ��ٸ� ����
	if ( IsCreate() == true )
	{
		DeleteDialog();
		return;
	}

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NPCRoom/DLG_PCRoom_Reward.ddf" ) );
	file.CreatePopupDialog( this, NPCROOM_DLG, TEXT( "dialog_pcroom" ), StaticCallBackDialogNPCRoom_Reward );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface(BUTTON,	NPCROOM_DLG_BUTTON_GET,		this),	NPCROOM_DLG_BUTTON_GET,		TEXT("button_get") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(LIST,	NPCROOM_DLG_LISTBOX_REWARD,	this),	NPCROOM_DLG_LISTBOX_REWARD,	TEXT("listbox_reward") );

	SetRewardList();
}

void CALLBACK CNPCRoom_Reward::StaticCallBackDialogNPCRoom_Reward( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNPCRoom_Reward* pThis = (CNPCRoom_Reward*)pControllerMgr;
	if ( pThis )
	{
		pThis->CallBackDialogNPCRoom_Reward( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNPCRoom_Reward::CallBackDialogNPCRoom_Reward( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch ( nControlID )
	{
	case NPCROOM_DLG_BUTTON_GET:
		{
			((cltClient*)pclClient)->CreateInterface( NSYSTEMREWARDLIST_DLG );
		}
		break;

	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	}
}

void CNPCRoom_Reward::SetRewardList( void )
{
	CList* pclList = m_InterfaceFactory.GetList( NPCROOM_DLG_LISTBOX_REWARD );
	if ( NULL == pclList )
	{
		return;
	}

	pclList->SetBorder(TRUE);
	pclList->SetBKColorUse(TRUE);

	TCHAR*	pText = TEXT("");

	// �÷� ����
	SI16 siList_1_Width = 20;
	SI16 siList_3_Width = 70;
	SI16 siList_2_Width = pclList->GetWidth() - siList_1_Width - siList_3_Width;

	pclList->SetColumn( 0, siList_1_Width, pText );

	pText = GetTxtFromMgr( 30270 );
	pclList->SetColumn( 1, siList_2_Width, pText );

	pText = GetTxtFromMgr( 30271 );
	pclList->SetColumn( 2, siList_3_Width, pText );

	// ���� ����
	SI32				siRow = 1;
	stListBoxItemData	stTmpListBoxItemData;

	// ���� ����ġ 150% ���
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, SI32ToString(siRow++) );
	stTmpListBoxItemData.Set( 1, GetTxtFromMgr(30272) );
	stTmpListBoxItemData.Set( 2, GetTxtFromMgr(30275) );
	pclList->AddItem( &stTmpListBoxItemData );

	// ���� ����ġ 150% ���
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, SI32ToString(siRow++) );
	stTmpListBoxItemData.Set( 1, GetTxtFromMgr(30273) );
	stTmpListBoxItemData.Set( 2, GetTxtFromMgr(30275) );
	pclList->AddItem( &stTmpListBoxItemData );

	// ���� �̵� ������
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, SI32ToString(siRow++) );
	stTmpListBoxItemData.Set( 1, GetTxtFromMgr(30274) );
	stTmpListBoxItemData.Set( 2, GetTxtFromMgr(30275) );
	pclList->AddItem( &stTmpListBoxItemData );

	// ���� ������ 1
	pText = (TCHAR*)pclClient->pclItemManager->GetName(2756);
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, SI32ToString(siRow++) );
	stTmpListBoxItemData.Set( 1, pText );
	stTmpListBoxItemData.Set( 2, GetTxtFromMgr(30276) );
	pclList->AddItem( &stTmpListBoxItemData );

	if ( pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) )
	{
		// ���� ������ 2
		pText = (TCHAR*)pclClient->pclItemManager->GetName(13351);
		stTmpListBoxItemData.Init();
		stTmpListBoxItemData.Set( 0, SI32ToString(siRow++) );
		stTmpListBoxItemData.Set( 1, pText );
		stTmpListBoxItemData.Set( 2, GetTxtFromMgr(30276) );
		pclList->AddItem( &stTmpListBoxItemData );
	}

	pclList->Refresh();
}