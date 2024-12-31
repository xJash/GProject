#include "../Client/ninterface/NPartyhallDlg/DLG_PartyHall_In_firecracker_Chief.h"
#include "../../Client/NInterface/NNewInventory/NNewInventory.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../Client/NStructureDlg/Feast/NFeastDlg.h"
#include "../../CommonLogic/Msg/MsgType-Feast.h"

NPartyHall_In_Firecracker_Chief_Dlg::NPartyHall_In_Firecracker_Chief_Dlg()
{

}

NPartyHall_In_Firecracker_Chief_Dlg::~NPartyHall_In_Firecracker_Chief_Dlg()
{

}


void NPartyHall_In_Firecracker_Chief_Dlg::Create(  CControllerMgr *pParent  )
{
	if ( IsCreate() )
		return;

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NStructureDlg/NPartyHall/DLG_PartyHall_In_firecracker_Chief.ddf" ) );
	file.CreateChildDialog( this, PARTYHALL_IN_FIRECRAKER_CHIEF_DLG, TEXT( "dialog_partyhall_in_firecracker" ), StaticNPartyHall_In_Firecracker_Chief_DlgProc, pParent );


	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,		PARTYHALL_FIRECRACKER_STATIC_USE,					this ), PARTYHALL_FIRECRACKER_STATIC_USE,						TEXT( "statictext_firecracker" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,		PARTYHALL_FIRECRACKER_BUTTON_NOTICE,				this ), PARTYHALL_FIRECRACKER_BUTTON_NOTICE,					TEXT( "button_notice" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,		PARTYHALL_FIRECRACKER_BUTTON_USE,					this ), PARTYHALL_FIRECRACKER_BUTTON_USE,						TEXT( "button_use" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,		PARTYHALL_FIRECRACKER_BUTTON_INVITE,				this ), PARTYHALL_FIRECRACKER_BUTTON_INVITE,					TEXT( "button_invite" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,		PARTYHALL_FIRECRACKER_BUTTON_PRESENT,				this ), PARTYHALL_FIRECRACKER_BUTTON_PRESENT,					TEXT( "button_present" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LIST,		PARTYHALL_FIRECRACKER_LSIT,							this ), PARTYHALL_FIRECRACKER_LSIT,								TEXT( "listbox_firecrack_list" ) );	
	//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,		PARTYHALL_FIRECRACKER_NAME,							this ), PARTYHALL_FIRECRACKER_NAME,								TEXT( "editbox_name" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,		PARTYHALL_FIRECRACKER_NOTICE,						this ), PARTYHALL_FIRECRACKER_NOTICE,							TEXT( "editbox_notice" ) );	

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,	PARTYHALL_FIRECRACKER_OUTLINE1,						this ), PARTYHALL_FIRECRACKER_OUTLINE1,							TEXT( "outline_NONAME1" ) );	
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,	PARTYHALL_FIRECRACKER_OUTLINE2,						this ), PARTYHALL_FIRECRACKER_OUTLINE2,							TEXT( "outline_NONAME2" ) );	
 
	CList* pList = m_InterfaceFactory.GetList(PARTYHALL_FIRECRACKER_LSIT);

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	TCHAR* pText[2];
	pText[0] = GetTxtFromMgr(1473);
	pText[1] = GetTxtFromMgr(1506);

	pList->SetColumn( 0,  189,   pText[ 0 ] );      
	pList->SetColumn( 1,  82,    pText[ 1 ] );           

	pList->Refresh();

	// ��ȸ�� �����Ϸ��� ��û�� ����� ��û.
	cltMsg clMsg(GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION_LIST, NULL, NULL );
	pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);	
}

void CALLBACK NPartyHall_In_Firecracker_Chief_Dlg::StaticNPartyHall_In_Firecracker_Chief_DlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	NPartyHall_In_Firecracker_Chief_Dlg *pThis = (NPartyHall_In_Firecracker_Chief_Dlg*) pControllerMgr;
	pThis->NPartyHall_In_Firecracker_Chief_DlgProc( nEvent, nControlID, pControl );

}
void CALLBACK NPartyHall_In_Firecracker_Chief_Dlg::NPartyHall_In_Firecracker_Chief_DlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	cltClient*	pclclient = (cltClient*)pclClient;

	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case PARTYHALL_FIRECRACKER_BUTTON_NOTICE:
		{
			CEdit* pEdit = m_InterfaceFactory.GetEdit(PARTYHALL_FIRECRACKER_NOTICE);
			TCHAR buffer[128] = "";
			MStrCpy( buffer, pEdit->GetText(), sizeof(buffer) );
				
			SI32 k;
			for ( k = 0 ; k < sizeof(buffer) ; k ++ )
			{
				if( buffer[k] == '\r' ||
					buffer[k] == '\n' )
				{
					buffer[k] = ' ';
				}
			}

			cltGameMsgRequest_FeastSendChat sendmsg( buffer );

			cltMsg clMsg(GAMEMSG_REQUEST_FEAST_SENDCHAT, sendmsg.siSize, (BYTE*)&sendmsg);
			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);				
		}
		break;
	case PARTYHALL_FIRECRACKER_BUTTON_INVITE:
		{
			CList* pList = m_InterfaceFactory.GetList(PARTYHALL_FIRECRACKER_LSIT);

			SI32 Index = pList->GetSelectedIndex();
			
			// ��ȸ�� �����Ϸ��� ��û�� ����� ��û.
			cltMsg clMsg(GAMEMSG_REQUEST_PARTYHALL_INVITATION, sizeof(SI32), (BYTE*)&m_ResvPersonID[Index] );
			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);	
		}
		break;
	case PARTYHALL_FIRECRACKER_BUTTON_USE:
		{
			CList* pList = m_InterfaceFactory.GetList(PARTYHALL_FIRECRACKER_LSIT);
			m_Index		 = pList->GetSelectedIndex();
			if(0 > m_Index)
				return;
			
			// ��ȸ�� ���� üũ
			SI32 personid   = pclClient->pclCM->CR[1]->pclCI->GetPersonID();
			
			TCHAR* pTitle = GetTxtFromMgr(5614);
			TCHAR* pText  = GetTxtFromMgr(5230);

			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;
			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, USE_FIRECRACKER );
			pclclient->SetMsgBox( &MsgBox, (BYTE*)&m_Index, sizeof(m_Index) );
		}
		break;
	case PARTYHALL_FIRECRACKER_BUTTON_PRESENT:
		{
			TCHAR* pTitle = GetTxtFromMgr(5614);
			TCHAR* pText  = GetTxtFromMgr(8343);

			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;
			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, GIVE_PRESEMT_ITEM );
			pclclient->SetMsgBox( &MsgBox, NULL, 0 );
		}
		break;
	}
}

bool NPartyHall_In_Firecracker_Chief_Dlg::EndClickAndDrop( cltClickAndDrop* pclClickAndDrop )
{
	cltClient* pclclient = (cltClient*)pclClient;

	if(pclClickAndDrop == NULL)										return false;
	if(pclClickAndDrop->IsType(CLICKANDDROP_TYPE_ITEM) == false)	return false;

	cltClickAndDrop_Item* pclClickAndDrop_Item = (cltClickAndDrop_Item*)pclClickAndDrop;

	void*	pvoidControl  = m_InterfaceFactory.GetControl( pclClickAndDrop->m_siDstControlID );

	switch ( pclClickAndDrop->m_siDstControlID )
	{
		default:	break;
	}

	return true;
}

void NPartyHall_In_Firecracker_Chief_Dlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	SI32 id = 1;

	switch( MsgIndex )
	{
		case USE_FIRECRACKER:
			{
				if(RetValue)
				{
					cltGameMsgRequest_FeastUseEffect sendmsg( &pclClient->pclFeastManager->siChiefEffectSelectIndex );

					cltMsg clMsg(GAMEMSG_REQUEST_FEAST_USEEFFECT, sizeof(sendmsg), (BYTE*)&sendmsg );
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			break;
		case GIVE_PRESEMT_ITEM:
			{
				if(RetValue)
				{
					cltFeastManager* pFeastManager = pclClient->pclFeastManager;
					
					if( pFeastManager->siUserPresentSelectIndex < 0 ) 
						return;

					cltGameMsgRequest_PartyHall_GiveItem sendmsg;

					cltMsg clMsg(GAMEMSG_REQUEST_PARTYHALL_GIVEITEM, sizeof(sendmsg), (BYTE*)&sendmsg);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			break;
	}
}

void NPartyHall_In_Firecracker_Chief_Dlg::SendServerMsgBufferDelete( SI32 _ClassType, void* _ClassData )
{
	switch( _ClassType )
	{
		//case XXX:	delete XXX_ClassData; break;	
		default: break;
	}
}


// ����Ʈ ����Ʈ�� ����Ʈ �߰�
void NPartyHall_In_Firecracker_Chief_Dlg::ShowEffectInfo()
{
	CList* pList = m_InterfaceFactory.GetList(PARTYHALL_FIRECRACKER_LSIT);

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	TCHAR* pText[3];
	pText[0] = GetTxtFromMgr(1641);
	pText[1] = GetTxtFromMgr(1782);
	pText[2] = GetTxtFromMgr(5223);

	pList->SetColumn( 0,  50,   pText[ 0 ] );
	pList->SetColumn( 1,  80,   pText[ 1 ] );      
	pList->SetColumn( 2,  144,  pText[ 2 ] );       

	pList->Refresh();

	SI32 FeastEffectName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = 
	{
		// �ϴÿ��� �������°�
		5711,
		5712,
		5713,

		// �ϴÿ��� �������°�
		5714,
		5715,
		5716,
		5717,
		5718,

		// 2���� �ϳ� �Ǵ°�
		5719,
		5720,
		5721,
	};

	SI32 FeastEffectKindName[cltFeastManager::MAX_FEAST_EFFECT_NUM] = {

		// �ϴÿ��� �������°�
		5708,
		5708,
		5708,

		// �ϴÿ��� �������°�
		5709,
		5710,
		5709,
		5709,
		5709,

		// 2���� �ϳ� �Ǵ°�
		5710,
		5710,
		5710,
	};

	TCHAR buffer[10];

	// List�� Item ��� �����
	pList->Clear();

	stListBoxItemData tmpListBoxItemData;
	for( SI16 i = 0; i < cltFeastManager::MAX_FEAST_EFFECT_NUM; i++)
	{
		tmpListBoxItemData.Init();

		StringCchPrintf(buffer, 10, TEXT("%d"), i + 1);

		tmpListBoxItemData.Set( 0, buffer );
		tmpListBoxItemData.siParam[0] = i;

		tmpListBoxItemData.Set( 1, GetTxtFromMgr(FeastEffectKindName[ i ]) );
		tmpListBoxItemData.Set( 2, GetTxtFromMgr(FeastEffectName[ i ]) );

		pList->AddItem( &tmpListBoxItemData );
	}

	pList->Refresh();
}

void NPartyHall_In_Firecracker_Chief_Dlg::SetEntranceApplicationList( Entrance_Application_Info* Entrance_Application_List )
{
	CList* pList = m_InterfaceFactory.GetList( PARTYHALL_FIRECRACKER_LSIT );
	pList->Clear();

	TCHAR szbuffer[4];
	stListBoxItemData tmpListBoxItemData;
	for( SI16 i = 0; i < MAX_PARTYHALL_APPLICATION_LIST; i++)
	{
		if( 0 == Entrance_Application_List[i].m_siLevel )
		{		
			break;
		}

		m_ResvPersonID[i] = Entrance_Application_List[i].m_siPersonID;

		tmpListBoxItemData.Init();

		tmpListBoxItemData.Set( 0, Entrance_Application_List[i].m_szID );

		StringCchPrintf( szbuffer, 10, TEXT("%d"), Entrance_Application_List[i].m_siLevel );
		tmpListBoxItemData.Set( 1, szbuffer );

		pList->AddItem( &tmpListBoxItemData );
	}
	pList->Refresh();
}