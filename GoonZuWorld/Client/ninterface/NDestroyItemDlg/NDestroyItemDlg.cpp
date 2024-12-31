#include "../Client/ninterface/NDestroyItemDlg/NDestroyItemDlg.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../CommonLogic/MsgType-Item.h"
#include "..\..\Common\Item\ItemCommon\cltitem.h"
#include "..\Client\Client.h"
#include "../../Client/NInterface/NNewInventory/NNewInventory.h"
#include "../../Server/GachaManager/GachaManager.h"
#include "../../Server/Gacha2Manager/Gacha2Manager.h"
#include "../CommonLogic/MsgType-Item.h"

NDestroyItemDlg::NDestroyItemDlg() 
{
}

NDestroyItemDlg::~NDestroyItemDlg()
{
}
void NDestroyItemDlg::Create( void )
{
	if ( IsCreate() )
		return;

	cltClient* pclclient = (cltClient*)pclClient;

	CInterfaceFile file;
	file.LoadFile( TEXT( "NInterface/Data/NDestroyItemDlg/DLG_NDestroyItemDlg.ddf" ) );
	file.CreatePopupDialog( this, NDESTROYITEM_DLG, TEXT( "dialog_DestroyItem" ), StaticNDestroyItemDlgProc, true);
	// ����.
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC,  NDESTROY_STATIC_NOTICE,	this ), NDESTROY_STATIC_NOTICE,	TEXT( "statictext_Notice" ) );
	// �ı��� ������ ������ �̸�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT,  NDESTROY_EDIT_ITEMNAME,	this ), NDESTROY_EDIT_ITEMNAME,	TEXT( "editbox_ItemName" ) );
	// ��ư 
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  NDESTROY_BUTTON_OK,	this ), NDESTROY_BUTTON_OK,	TEXT( "button_Ok" ) );// �ı��Ѵ�
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,  NDESTROY_BUTTON_CANCEL,	this ), NDESTROY_BUTTON_CANCEL,	TEXT( "button_Cancel" ) );//�ı������ʴ´�.

	if ( pclclient )
	{
		SI16 siPosX = ( pclclient->GetScreenXSize() - GetWidth() + MAP_TILE_XSIZE ) / 2;
		SI16 siPosY = ( pclclient->GetScreenYSize() - GetHeight() + MAP_TILE_YSIZE ) / 2;

		SetDialogPos( siPosX, siPosY, GetWidth(), GetHeight() );
	}

    SetActionTimer( 100 );    
	SetTimerOnOff( true );
}


void CALLBACK NDestroyItemDlg::StaticNDestroyItemDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	NDestroyItemDlg *pThis = (NDestroyItemDlg*) pControllerMgr;
	pThis->NNDestroyItemDlgProc( nEvent, nControlID, pControl );
}


void CALLBACK NDestroyItemDlg::NNDestroyItemDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	cltClient* pclclient = (cltClient*)pclClient;
	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	// ������ �̸� ���� OK�� ������.
	case NDESTROY_BUTTON_OK:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					CEdit* peItemName = NULL ;
					peItemName = m_InterfaceFactory.GetEdit( NDESTROY_EDIT_ITEMNAME );
					// �̸� �ִ� â�� ��������
					if (peItemName->IsShow() == true) {
						pItemName = peItemName->GetText();// ������ �̸��� �޾� �´�.

						if( _tcsicmp(ItemNameToDestroy , pItemName) == 0) 
						{
							// ���� �̸��� ���ٸ�
							// �ı��϶�� �޼����� ������ �Լ��� - cltGameMsgRequest_InvDrop �ı��޼��� - GAMEMSG_REQUEST_BELONGITEM_DESTROY
							// �ͼӾ������� �ı��ϵ��� ��û�Ѵ�.
							cltGameMsgRequest_InvDrop cldrop(DropItemIndex, &dropitemtoDestroy);
							cltMsg clMsg(GAMEMSG_REQUEST_BELONGITEM_DESTROY, sizeof(cldrop), (BYTE*)&cldrop);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							
							// ���Ӽ����� ����ϵ��� ��û�Ѵ�. 
							/*
							cltGameMsgRequest_InvDrop cldrop(DropItemIndex, &dropitemtoDestroy);
							cltMsg clMsg(GAMEMSG_REQUEST_INVDROP, sizeof(cldrop), (BYTE*)&cldrop);
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							*/
							
							DeleteDialog();
						}
						else{ 
							return;//������ ���� ������ ����( ���߿� �޼��� �߰�.)							
						}
					}
					else{
						// ������ ��� �ص� ���� ���� ���� ��� �޼����� ���� ��� ��Ų��.
						cltGameMsgRequest_InvDrop cldrop(DropItemIndex, &dropitemtoDestroy);
						cltMsg clMsg(GAMEMSG_REQUEST_INVDROP, sizeof(cldrop), (BYTE*)&cldrop);
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
						/*
						cltGameMsgRequest_InvDrop cldrop(DropItemIndex, &dropitemtoDestroy);
						cltMsg clMsg(GAMEMSG_REQUEST_BELONGITEM_DESTROY, sizeof(cldrop), (BYTE*)&cldrop);
						pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
						*/
						DeleteDialog();
					}	
					
				}				
			}
		}
		break;
	case NDESTROY_BUTTON_CANCEL:{
		switch( nEvent ){
			case EVENT_BUTTON_CLICKED:
				{
					DeleteDialog();
				}
			}
		}
		break;
	}
}

void NDestroyItemDlg::Action(void)
{
}
void NDestroyItemDlg:: SetDropItem( SI32 ItemIndex , cltItem DropItem )
{
	cltClient *pclclient = (cltClient*)pclClient;
	dropitemtoDestroy.Set( &DropItem );
	ItemNameToDestroy = (TCHAR*)pclClient->pclItemManager->GetName( dropitemtoDestroy.siUnique ); // ����߸� �������� �̸��� ã�Ƽ� �����Ѵ�.
	if(ItemNameToDestroy == NULL )	
	{
		DeleteDialog();
		return	;
	}
	if(dropitemtoDestroy.siUnique <= 0 )
	{
		DeleteDialog()	;
		return	;
	}
	DropItemIndex = ItemIndex; //����߸� �������� �ε����� �����Ѵ�.
	if(DropItemIndex < 0 )
	{
		DeleteDialog()	;
		return	;
	}
	// �ı��Ǵ� �������� �˾ƺ���.
	bool bCondition1 = pclClient->pclItemManager->IsCanDropItem(dropitemtoDestroy.siUnique);// ����߷��� �ϴ� ���������� �ƴ��� ���� 
	// �ͼ���� ���� �˾ƺ���.
	bool bCondition2 = dropitemtoDestroy.IsBelonging( pclClient->pclItemManager );//�ͼ��������

	// �ͼ����� ������ �ı� �Ѵ�.
	if ( true == bCondition2 ) 
	{
		SI16 siItemnum = 0;
		CStatic* peNotice = NULL ;

		NTCHARString256	kText(GetTxtFromMgr(8573));
		kText.Replace(TEXT("#itemname#"),pclClient->pclItemManager->GetName( dropitemtoDestroy.siUnique ) );
		kText.Replace(TEXT("#num#"),SI16ToString(dropitemtoDestroy.siItemNum) );
		peNotice = m_InterfaceFactory.GetStatic(NDESTROY_STATIC_NOTICE );
		peNotice->SetText( kText );
	}
	// �׳� ��ӵǾ� �ϴ� ������
	else if ( (true == bCondition1) ) 
	{
		CEdit* peItemName = NULL ;
		CStatic* peNotice = NULL ;
		peItemName = m_InterfaceFactory.GetEdit( NDESTROY_EDIT_ITEMNAME );
		peItemName->Show(false);

		NTCHARString256	kText(GetTxtFromMgr(8571));
		kText.Replace(TEXT("#itemname#"),pclClient->pclItemManager->GetName( dropitemtoDestroy.siUnique ) );
		kText.Replace(TEXT("#num#"),SI16ToString(dropitemtoDestroy.siItemNum) );
		peNotice = m_InterfaceFactory.GetStatic(NDESTROY_STATIC_NOTICE );
		peNotice->SetText( kText );
	}
	// �ŷ��Ұ� �������� �ı�
	else
	{
		SI16 siItemnum = 0;
		CStatic* peNotice = NULL ;

		NTCHARString256	kText(GetTxtFromMgr(8573));
		kText.Replace(TEXT("#itemname#"),pclClient->pclItemManager->GetName( dropitemtoDestroy.siUnique ) );
		kText.Replace(TEXT("#num#"),SI16ToString(dropitemtoDestroy.siItemNum) );
		peNotice = m_InterfaceFactory.GetStatic(NDESTROY_STATIC_NOTICE );
		peNotice->SetText( kText );

		/*SI16 siItemnum = 0;
		CStatic* peNotice = NULL ;
		NTCHARString256	kText(GetTxtFromMgr(8571));
		kText.Replace(TEXT("#itemname#"),pclClient->pclItemManager->GetName( dropitemtoDestroy.siUnique ) );
		kText.Replace(TEXT("#num#"),SI16ToString(dropitemtoDestroy.siItemNum) );
		peNotice = m_InterfaceFactory.GetStatic(NDESTROY_STATIC_NOTICE );
		peNotice->SetText( kText );*/
		
		/*
		TCHAR* pTitle = GetTxtFromMgr(3266);
		TCHAR* pText = GetTxtFromMgr(3267);
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		DeleteDialog();
		return;
		*/
	}
}