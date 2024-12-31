#include "../Client/ninterface/NChange/NChangeDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../CommonLogic/MsgType-Item.h"
#include "..\..\Common\Item\ItemCommon\cltitem.h"
#include "..\Client\Client.h"
#include "../../Client/NInterface/NNewInventory/NNewInventory.h"
#include "../../Server/GachaManager/GachaManager.h"
#include "../../Server/Gacha2Manager/Gacha2Manager.h"

NChangeDlg::NChangeDlg() 
{
	uiStr = 0 ;
	uiDex = 0 ;
	uiAgi = 0 ;
	uiMag = 0 ;
	uiVit = 0 ;
	uiHnd = 0 ;
	uiLuk = 0 ;
	ItemPos = 0 ;
	Status = 0;
	ItemUnique = 0;
}

NChangeDlg::~NChangeDlg()
{
}
void NChangeDlg::Create( void )
{
	if ( IsCreate() )
		return;

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NChange/DLG_NChange.ddf" ) );
	file.CreatePopupDialog( this, NCHANGE_DLG, TEXT( "dialog_Change" ), StaticNChangeDlgProc );

	// ����.
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_EXPLAIN_FRONT,	this ), CHANGE_STATIC_EXPLAIN_FRONT,	TEXT( "statictext_explain_front" ) );	// ��簡 ���� ������ ����ƽ
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_EXPLAIN_BACK,	this ), CHANGE_STATIC_EXPLAIN_BACK,	TEXT( "statictext_expalain_back" ) );	// ���
	
	
	// �׸�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_ITEM,	this ), CHANGE_STATIC_ITEM,	TEXT( "statictext_item" ) );			// ������
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_STATUSNOW,	this ), CHANGE_STATIC_STATUSNOW,	TEXT( "statictext_statusnow" ) );		// ���� �������ͽ�
	// ���� ������ ǥ��
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW,  CHANGE_LISTVIEW_ITEMSLOT,	this ), CHANGE_LISTVIEW_ITEMSLOT,	TEXT( "listview_itemslot" ) );			// �������� Ŭ���ص���� ��ġ
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_STATUSEXPLAIN,	this ), CHANGE_STATIC_STATUSEXPLAIN,	TEXT( "statictext_statusexplain" ) );	// �������ͽ��� ȭ�鿡 �����ش�.
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  CHANGE_STATIC_NONAME01,	this ), CHANGE_STATIC_NONAME01,	TEXT( "statictext_NONAME1" ) );	// �׳�����
	// ������ �������ͽ� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_STR,	this ), CHANGE_BUTTON_STR,	TEXT( "button_str" ) );					// ������ ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_DEX,	this ), CHANGE_BUTTON_DEX,	TEXT( "button_dex" ) );					// �����ַ� ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_HND,	this ), CHANGE_BUTTON_HND,	TEXT( "button_agi" ) );					// ���߷·� ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_INT,	this ), CHANGE_BUTTON_INT,	TEXT( "button_int" ) );					// ���·� ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_VIT,	this ), CHANGE_BUTTON_VIT,	TEXT( "button_vit" ) );					// ����·� ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_LUCK,	this ), CHANGE_BUTTON_LUCK,	TEXT( "button_luck" ) );				// ���� ���� ��ư
	// �ƿ�����
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,  CHANGE_OUTLINE_NAME1,	this ), CHANGE_OUTLINE_NAME1,	TEXT( "outline_NONAME1" ) );			// �ƿ�����1
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,  CHANGE_OUTLINE_NAME2,	this ), CHANGE_OUTLINE_NAME2,	TEXT( "outline_NONAME2" ) );			// �ƿ�����2
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( OUTLINE,  CHANGE_OUTLINE_NAME3,	this ), CHANGE_OUTLINE_NAME3,	TEXT( "outline_NONAME3" ) );			// �ƿ�����3
	// ���� ��ư
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  CHANGE_BUTTON_CLOSE,	this ), CHANGE_BUTTON_CLOSE,	TEXT( "button_close" ) );				// ���� ��ư

	CButton *btStr = NULL;
	CButton *btDex = NULL;
	CButton *btAgi = NULL;
	CButton *btInt = NULL;
	CButton *btVit = NULL;
	CStatic *stExplain = NULL;
	TCHAR *pText = GetTxtFromMgr(8421);
	
	btStr = m_InterfaceFactory.GetButton( CHANGE_BUTTON_STR ) ;
	btDex = m_InterfaceFactory.GetButton( CHANGE_BUTTON_DEX ) ;
	btAgi = m_InterfaceFactory.GetButton( CHANGE_BUTTON_HND ) ;
	btInt = m_InterfaceFactory.GetButton( CHANGE_BUTTON_INT ) ;
	btVit = m_InterfaceFactory.GetButton( CHANGE_BUTTON_VIT ) ;
	
	stExplain = m_InterfaceFactory.GetStatic( CHANGE_STATIC_EXPLAIN_FRONT ) ;
	stExplain->SetText(pText);
	
	btStr->Enable(false);
	btAgi->Enable(false);// ���� �̳��� ���� ������. ��ư�� ������.
	btInt->Enable(false);
	btVit->Enable(false);
	btDex->Enable(false); 
    SetActionTimer( 100 );    
	SetTimerOnOff( true );
}


void CALLBACK NChangeDlg::StaticNChangeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	NChangeDlg *pThis = (NChangeDlg*) pControllerMgr;
	pThis->NChangeDlgProc( nEvent, nControlID, pControl );
}


void CALLBACK NChangeDlg::NChangeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	cltClient* pclclient = (cltClient*)pclClient;
	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case CHANGE_BUTTON_CLOSE:
		{
			DeleteDialog();
		}
		break;
	case CHANGE_BUTTON_STR:
		{
			if ( Checkslot() == true ) {
				TCHAR* pTitle = GetTxtFromMgr(578);
				TCHAR* pText  = GetTxtFromMgr(8425);
				stMsgBox MsgBox;
				MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
				pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}
			break;
		}
		break;
	case CHANGE_BUTTON_DEX:
		{
			if ( Checkslot() == true ) {
			TCHAR* pTitle = GetTxtFromMgr(578);
			TCHAR* pText  = GetTxtFromMgr(8425);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 2 );
			pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}
			break;		
		}
		break;
	case CHANGE_BUTTON_HND:
		{
			if ( Checkslot() == true ) {
				TCHAR* pTitle = GetTxtFromMgr(578);
				TCHAR* pText  = GetTxtFromMgr(8425);
				stMsgBox MsgBox;
				MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 6 );
				pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}
			break;		
		}
		break;

	case CHANGE_BUTTON_INT:
		{
			if ( Checkslot() == true ) {
			TCHAR* pTitle = GetTxtFromMgr(578);
			TCHAR* pText  = GetTxtFromMgr(8425);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 3 );
			pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}
			break;
		}
		break;
	case CHANGE_BUTTON_LUCK:
		{
			if ( Checkslot() == true ) {
			TCHAR* pTitle = GetTxtFromMgr(578);
			TCHAR* pText  = GetTxtFromMgr(8425);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 4 );
			pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}break;
		}
		break;
	case CHANGE_BUTTON_VIT:
		{
			if ( Checkslot() == true ) {
			TCHAR* pTitle = GetTxtFromMgr(578);
			TCHAR* pText  = GetTxtFromMgr(8425);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 5 );
			pclclient->SetMsgBox( &MsgBox, NULL , 0 );
			}break;
		}
		break;
	}
}

void NChangeDlg::Action(void)
{
}

bool NChangeDlg::EndClickAndDrop( cltClickAndDrop* pclClickAndDrop )
{
	cltClient* pclclient = (cltClient*)pclClient;

	if( pclClickAndDrop == NULL )										return true;
	if( pclClickAndDrop->IsType(CLICKANDDROP_TYPE_ITEM) == false )		return true;

	cltClickAndDrop_Item* pclClickAndDrop_Item = (cltClickAndDrop_Item*)pclClickAndDrop;
	ItemPos = pclClickAndDrop_Item->m_siPara1;
	// �ش� ������ ������ ������ �´�.
	Targetitem = pclClickAndDrop_Item->GetItem();
	ItemUnique = Targetitem->siUnique;
	SI32 DropItemType = Targetitem->GetType(pclClient->pclItemManager);
	if (DropItemType != ITEMTYPE_DRESS && DropItemType !=ITEMTYPE_HAT  )	return true; 
	
	switch ( pclClickAndDrop->m_siDstControlID )
	{
		case CHANGE_LISTVIEW_ITEMSLOT:
		{
			stListViewItemData	ListViewItemData;
			TCHAR *pText;
			CStatic* pStaticExplain = NULL;
			CListView* pListSlot = NULL;
			TCHAR temp[1024] = TEXT("");
			TCHAR ToolTipMsg[512];
			pStaticExplain = m_InterfaceFactory.GetStatic( CHANGE_STATIC_STATUSEXPLAIN ) ;
			pListSlot = m_InterfaceFactory.GetListView( CHANGE_LISTVIEW_ITEMSLOT ) ;			
						
			// �̹��� ������ ��� �´�.
			SI32 GlobalImageIndex	= -1;
			SI32 GlobalImageFont	= -1;
			if ( Checkgacha( Targetitem->siUnique ) == false)	return true;
			//if ( Checkstatus(  ) == false )	return false;
			if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( Targetitem->siUnique, &GlobalImageIndex, &GlobalImageFont) ) {
				TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( Targetitem->siUnique );
				if (ItemName)
				{
					//pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[pclClickAndDrop->m_siPara1]
					pclClient->pclItemManager->GetExplain( Targetitem, ToolTipMsg );
					ListViewItemData.Init();
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0, 0, ItemName, ToolTipMsg );
					pListSlot->DeleteAllItems();
					pListSlot->InsertItem( &ListViewItemData );
				}
			}
			// �ش� �������� � �������ͽ��� ������ �ִ� �� �˾Ƴ���
			if ( Targetitem->clItemStatusArmour.uiStr > 0 ){		// ��
                pText = GetTxtFromMgr(3565);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiStr );
				Status = Targetitem->clItemStatusArmour.uiStr ;
				pStaticExplain->SetText( temp );
				uiStr = Targetitem->clItemStatusArmour.uiStr ;
				
			}
			else if ( Targetitem->clItemStatusArmour.uiVit > 0 ){	// ��
				pText = GetTxtFromMgr(3567);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiVit );
				Status = Targetitem->clItemStatusArmour.uiVit ;
				pStaticExplain->SetText( temp );
				uiVit = Targetitem->clItemStatusArmour.uiVit ;
				
			}
			else if ( Targetitem->clItemStatusArmour.uiLuk > 0 ){	// ���				
				pText = GetTxtFromMgr(6065);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiLuk );
				Status = Targetitem->clItemStatusArmour.uiLuk ;
				pStaticExplain->SetText( temp );
				uiLuk = Targetitem->clItemStatusArmour.uiLuk ;
			}
			else if ( Targetitem->clItemStatusArmour.uiHnd > 0 ){	// ������				
				pText = GetTxtFromMgr(6108);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiHnd );
				Status = Targetitem->clItemStatusArmour.uiHnd ;
				pStaticExplain->SetText( temp );
				uiHnd = Targetitem->clItemStatusArmour.uiHnd ;
				
			}
			else if ( Targetitem->clItemStatusArmour.uiDex > 0 ){	// ���߷�
				pText = GetTxtFromMgr(3566);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiDex );
				Status = Targetitem->clItemStatusArmour.uiDex ;
				pStaticExplain->SetText( temp );
				uiDex = Targetitem->clItemStatusArmour.uiDex ;
				
			}
			else if ( Targetitem->clItemStatusArmour.uiMag > 0 ){	// ����
				pText = GetTxtFromMgr(6064);
				StringCchPrintf(temp, 1024, pText, Targetitem->clItemStatusArmour.uiMag );
				Status = Targetitem->clItemStatusArmour.uiMag ;
				pStaticExplain->SetText( temp );
				uiMag = Targetitem->clItemStatusArmour.uiMag ;
			}
			pStaticExplain->Refresh();
		}
		break;
	}

	return true;
}
void NChangeDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient* pclclient = (cltClient*)pclClient;
	switch( MsgIndex )
	{
	case 1:
		{
			if(RetValue) // ��
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeStrStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();
				}
			}
		}break;
	case 2:
		{
			if(RetValue) // ������
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeHndStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();

				}
			}
		}break;
	case 3:
		{
			if(RetValue) // ������
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeMagStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();

				}
			}
		}break;
	case 4:
		{
			if(RetValue) // ���
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeLukStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();

				}
			}
		}break;
	case 5:
		{
			if(RetValue) // ��
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeVitStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();
				}
			}
		}break;
	case 6:
		{
			if(RetValue) // ������
			{
				if ( Status > 0 ) {
					if ( Checkgacha( ItemUnique ) == false )	return ;
					if ( Checkstatus(  ) == false )	return ;					
					cltGameMsgRequest_Inv_ChangItemFormNpc changeitemnpc(ItemPos, Status, ChangeHndStatus );
					cltMsg clMsg(GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	sizeof(changeitemnpc), (BYTE*)&changeitemnpc);
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
					DeleteDialog();
				}
			}
		}break;
	}
}
bool NChangeDlg :: Checkstatus( ){
	cltClient* pclclient = (cltClient*)pclClient;
	// �����ְ� �ƴ� �ٸ� �����̸� ���� �Ҽ� ����.
	if ( uiStr > 0 ||
		uiDex > 0 ||	
		uiLuk > 0 ||
		uiMag > 0 ||
		uiVit > 0)
	{
		TCHAR* pTitle = GetTxtFromMgr(836);
		TCHAR* pText = GetTxtFromMgr(8428);
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		DeleteDialog();
		return false;
	}
	return true;
}
bool NChangeDlg:: Checkslot( ) // ������ ������ �Ҽ� ���ٴ� �޼����� ����Ѵ�.
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( Status <= 0 ) {
		TCHAR* pTitle = GetTxtFromMgr(836);
		TCHAR* pText = GetTxtFromMgr(8434);
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		DeleteDialog();
		return false;
	}
	return true;

}
bool NChangeDlg :: Checkgacha( SI32 siItemUnique  ){
	cltClient* pclclient = (cltClient*)pclClient;
	// ���� ������ �� �ƴϸ� ��� �Ҽ� ����.
	if( pclClient->pclGachaManager->IsGachaRareItem( siItemUnique ) == false)
	{
		TCHAR* pTitle = GetTxtFromMgr(836);
		TCHAR* pText = GetTxtFromMgr(8433);
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		return false;	
	}
	return true;
}