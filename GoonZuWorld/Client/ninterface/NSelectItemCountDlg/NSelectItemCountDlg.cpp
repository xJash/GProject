#include "../../InterfaceMgr/InterfaceFile.h"
#include "NSelectItemCountDlg.h"
#include "../../../common/Char/CharManager/CharManager.h"
#include "../NNewInventory/NNewInventory.h"
#include "../NDestroyItemDlg/NDestroyItemDlg.h"
#include "../../Client/Client.h"
#include "../../../CommonLogic/MsgType-Item.h"
#include "../../../CommonLogic/CommonLogic.h"

extern cltCommonLogic* pclClient;

CNSelectItemCountDlg::CNSelectItemCountDlg()
{
	m_pStaticTotal = NULL;
	m_pEditTotal = NULL;
	m_pStaticInput = NULL;
	m_pEditInput = NULL;
	m_pButtonSubmit = NULL;
	m_pButtonCancel = NULL;
	m_siSelectedItemCount = 0;
	m_siSelectedItemIndex = -1;
	m_siMode = 0;
}
CNSelectItemCountDlg::~CNSelectItemCountDlg()
{
	SAFE_DELETE(m_pStaticTotal);
	SAFE_DELETE(m_pEditTotal);
	SAFE_DELETE(m_pStaticInput);
	SAFE_DELETE(m_pEditInput);
	SAFE_DELETE(m_pButtonSubmit);
	SAFE_DELETE(m_pButtonCancel);
}
void CNSelectItemCountDlg::Create()
{


	NEWCSTATIC( m_pStaticTotal );
	NEWCEDIT( m_pEditTotal );
	NEWCSTATIC( m_pStaticInput );
	NEWCEDIT( m_pEditInput );
	NEWCBUTTON( m_pButtonSubmit );
	NEWCBUTTON( m_pButtonCancel );

	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/nnewinventorydlg/DLG_NSelectItemCount.ddf"));
	file.CreatePopupDialog( this, NSELECTITEMCOUNT_DLG , TEXT("dialog_selectitemcount"), StaticCallBackDialogNSelectItemCount );

	file.CreateControl( m_pStaticTotal, NSELECTITEMCOUNT_DLG_TOTAL_STATIC, TEXT("statictext_total") );
	file.CreateControl( m_pEditTotal, NSELECTITEMCOUNT_DLG_TOTAL_EDIT, TEXT("editbox_total") );
	file.CreateControl( m_pStaticInput, NSELECTITEMCOUNT_DLG_INPUT_STATIC, TEXT("statictext_input") );
	file.CreateControl( m_pEditInput, NSELECTITEMCOUNT_DLG_INPUT_EDIT, TEXT("editbox_input") );
	file.CreateControl( m_pButtonSubmit, NSELECTITEMCOUNT_DLG_SUBMIT_BUTTON, TEXT("button_submit") );
	file.CreateControl( m_pButtonCancel, NSELECTITEMCOUNT_DLG_CANCEL_BUTTON, TEXT("button_cancel") );

	//[�迵�� �߰�:2007.11.21 - ������ ���� �Է½� ���ڸ� �Էµǵ��� ����]
	m_pEditInput->SetNumberMode( true );
}
void CALLBACK CNSelectItemCountDlg::StaticCallBackDialogNSelectItemCount( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNSelectItemCountDlg *pThis = (CNSelectItemCountDlg*)pControllerMgr;
	pThis->CallBackDialogNSelectItemCount( nEvent, nControlID, pControl );

}
void CALLBACK CNSelectItemCountDlg::CallBackDialogNSelectItemCount( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case NSELECTITEMCOUNT_DLG_SUBMIT_BUTTON:
		if ( nEvent == EVENT_BUTTON_CLICKED )
		{
			SI32 inputCount = _tstoi( m_pEditInput->GetText() );
			if( inputCount <= m_siSelectedItemCount && inputCount > 0  )
			{
				// ���� ��忡 ����..
				switch( m_siMode )
				{
				case COUNT_MODE_SPLITITEM:		
					SplitItem();	
					break;
				case COUNT_MODE_DROPITEM:		
					DropItem();		
					break;
				case COUNT_MODE_PRESENTITEM:		
					PresentItem();		
					break;
				default: 
					break;
				}
			}
			DeleteDialog();
		}
		break;
	case NSELECTITEMCOUNT_DLG_INPUT_EDIT:
		if ( nEvent == EVENT_EDITBOX_STRING )
		{
			SI32 inputCount = _tstoi( m_pEditInput->GetText() );
			if( inputCount <= m_siSelectedItemCount && inputCount > 0  )
			{
				// ���� ��忡 ����..
				switch( m_siMode )
				{
				case COUNT_MODE_SPLITITEM:		
					SplitItem();	
					break;
				case COUNT_MODE_DROPITEM:		
					DropItem();		
					break;
				default: 
					break;
				}
			}
			DeleteDialog();
		}
		break;
	case NSELECTITEMCOUNT_DLG_CANCEL_BUTTON:
		if( nEvent == EVENT_BUTTON_CLICKED )
		{
			DeleteDialog();
		}
		break;
	default:
		break;
	}
}
void CNSelectItemCountDlg::SplitItem()
{
	cltPersonInfo* person = pclClient->pclCM->CR[1]->pclCI;
	bool bCanSplit = false;
	SI32 uiToPos = 0;
	for ( SI32 invenindex=PERSONITEM_INV0; invenindex < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON ; invenindex++)
	{
		// ������ ������ �˻����� �ʴ´�.
		if( invenindex >= PERSONITEM_BAG0 && invenindex < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			if( person->clCharItem.clItem[PERSONITEM_BAG].siUnique == 0 ) 
				continue;
		}
		else if( invenindex >= PERSONITEM_BAG1 && invenindex < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			if( person->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique == 0 ) 
				continue;
		}
		// ���̾����� �˻����� �ʴ´�.
		else if( invenindex >= PERSONITEM_HORSE0 && invenindex < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY )
		{
			if ( ! pclClient->pclCM->CR[1]->HaveHorse() )
				continue;
		}

        if( person->clCharItem.clItem[invenindex].siUnique == 0 )
		{
			bCanSplit = true;
			uiToPos = invenindex;
			break;
		}
	}
	
	SI32 inputCount = _tstoi( m_pEditInput->GetText() );

	if ( bCanSplit )
	{
		// �����޶�� ��û
		cltSplitItemInfo clsplititem( m_siSelectedItemIndex, uiToPos, inputCount);
		cltMsg clMsg(GAMEMSG_REQUEST_ITEMSPLIT,
			sizeof(cltSplitItemInfo), (BYTE*)&clsplititem);

		pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
	}
}
void CNSelectItemCountDlg::DropItem()//  ������ �ִ� �����۵��������
{
	if(pclClient->pclMapManager->pclCurrentMap->IsInMapArea(pclClient->pclCM->CR[1]->GetX(), pclClient->pclCM->CR[1]->GetY()) == false)
	{
		TCHAR* pText = GetTxtFromMgr(1056);

		//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
		if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
		{
			pclClient->pclMessage->SetPersonalMsg(pText);
		}
		else
		{
			pclClient->pclMessage->SetMsg(pText);
		}
	}
	if(pclClient->pclMapManager->pclCurrentMap->IsColl(pclClient->pclCM->CR[1]->GetX(), pclClient->pclCM->CR[1]->GetY(), BLOCK_DEEPWATER|BLOCK_SHALLOWWATER))
	{
		TCHAR* pText = GetTxtFromMgr(1057);

		//[����]���� �и� �ؽ�Ʈ ����. => 2008-6-2
		if (true == pclClient->IsCountrySwitch( Switch_Notice_Separate))
		{
			pclClient->pclMessage->SetPersonalMsg(pText);
		}
		else
		{
			pclClient->pclMessage->SetMsg(pText);
		}
	}
	else
	{
		cltItem dropitem;
		dropitem.Set( &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siSelectedItemIndex] );
		SI32 inputCount = _tstoi( m_pEditInput->GetText() );
		dropitem.SetItemNum( inputCount );
		if ( pclClient->IsCountrySwitch(Switch_DestroyDropItem) ){
			// �����۸� �������� �̸� �� �ִ� â���� �����ϵ��� �Ѵ�.
			// �ŷ� �Ұ� �������� �̸��� ��ִ� â���� ���� �ϵ��� �Ѵ�.
			// ���� ������ �ƴ� ��쿡�� �׳� ���� �Ѵ�.
			// �׳� ���� �ص� �Ǵ��� ������ ������ �̸��� �־�� �ϴ� ���� ���� �Ѵ�
			//if( pclClient->pclItemManager->IsCanDestroyDropItem(dropitem.siUnique) == true ){ // �׳� �μŹ�����.
			//	// ���Ӽ����� ����������� �ı��Ѵ�.
			//	cltGameMsgRequest_InvDrop cldrop(m_siSelectedItemIndex, &dropitem);
			//	cltMsg clMsg(GAMEMSG_REQUEST_BELONGITEM_DESTROY, sizeof(cldrop), (BYTE*)&cldrop);
			//	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			//}
			//else{
				cltClient *pclclient = (cltClient*)pclClient;
				pclclient->CreateInterface( NDESTROYITEM_DLG );	
				((NDestroyItemDlg*)pclclient->m_pDialog[NDESTROYITEM_DLG])->SetDropItem(m_siSelectedItemIndex, dropitem );
			//}
		}
		else
		{
			// ���Ӽ����� ����ϵ��� ��û�Ѵ�. 
			cltGameMsgRequest_InvDrop cldrop(m_siSelectedItemIndex, &dropitem);
			cltMsg clMsg(GAMEMSG_REQUEST_INVDROP, sizeof(cldrop), (BYTE*)&cldrop);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
		}		
	}
}

void	CNSelectItemCountDlg::PresentItem()
{
	cltClient *pclClientLogic = (cltClient*)pclClient;

	CValentineEventClientMgr* pclValentineEvent = (CValentineEventClientMgr* )pclClientLogic->m_pclValentineEventMgr;
	if( NULL == pclValentineEvent)
	{
		return;
	}

	cltItem dropitem;
	dropitem.Set( &pclClientLogic->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siSelectedItemIndex] );
	SI32 inputCount = _tstoi( m_pEditInput->GetText() );
	SI32 siItemNum = dropitem.siItemNum;
	dropitem.SetItemNum( siItemNum - inputCount );

	pclValentineEvent->GivePresentItem(dropitem, m_siSelectedItemIndex);

}

void CNSelectItemCountDlg::SetSelectedItemIndex(SI32 siSelectedItemIndex)
{
	m_siSelectedItemIndex = siSelectedItemIndex;
}

void CNSelectItemCountDlg::SetCountMode( SI16 mode )
{
	cltClient *pclClientLogic = (cltClient*)pclClient;

	// [����] �߷�Ÿ�� ���� �̺�Ʈ - �����ϱ�
	if ( COUNT_MODE_PRESENTITEM == mode)
	{
		CValentineEventClientMgr* pclValentineEvent = (CValentineEventClientMgr* )pclClientLogic->m_pclValentineEventMgr;
		if( NULL == pclValentineEvent)
		{
			return;
		}

		CValentineNPC *pclValentineNPC = pclValentineEvent->GetSeletedNPC();
		if( NULL == pclValentineNPC)
		{
			return;
		}
		
		SI32 siPresentItemUnique = 0;
		if(pclValentineNPC->IsSexMale())
			siPresentItemUnique = ITEMUNIQUE(3935);
		else
			siPresentItemUnique = ITEMUNIQUE(3936);

		bool bHaveItem = false;

		for(SI32 siInventoryIndex = 0; siInventoryIndex < MAX_ITEM_PER_PERSON; siInventoryIndex++)
		{
			if( pclClientLogic->pclCM->CR[1]->pclCI->clCharItem.clItem[siInventoryIndex].siUnique == siPresentItemUnique)
			{
				m_siSelectedItemIndex = siInventoryIndex;
				bHaveItem = true;
				break;
			}
		}

		if( false == bHaveItem )
		{	
			NTCHARString64	kTitle( GetTxtFromMgr(6071) );
			NTCHARString128	kText( GetTxtFromMgr(15629) );

			if( ((cltClient*)pclClient)->m_pDialog[ NOTIFYMSG_DLG ] != NULL )
			{
				((cltClient*)pclClient)->m_pDialog[ NOTIFYMSG_DLG ]->SetText(kTitle, kText);
			}
			DeleteDialog();
			return;
		}
	}


	if(pclClient->IsCountrySwitch(Switch_ClickAndDrop))
	{
	}
	else
	{
		m_siSelectedItemIndex = CNNewInventory::m_siSelectedIndex;
		CNNewInventory::m_siSelectedIndex = -1;
	}
	m_siSelectedItemCount = ((cltClient*)pclClient)->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siSelectedItemIndex].siItemNum;


	m_siMode = mode;

	TCHAR buffer[16] = TEXT("");
	if ( m_siMode == COUNT_MODE_SPLITITEM )
	{
		StringCchPrintf( buffer, 16, TEXT("%d"), 0 );
	}
	else
	{
		StringCchPrintf( buffer, 16, TEXT("%d"), m_siSelectedItemCount );
	}
	TCHAR buffer2[16] = TEXT("");
	StringCchPrintf( buffer2, 16, TEXT("%d"), m_siSelectedItemCount );

	m_pEditInput->SetText( buffer );
	m_pEditTotal->SetText( buffer2 );

    // ���̾�α� ��ġ ����
	POINT pt;
	cltClient* pclclient = (cltClient*)pclClient;
	TCHAR* pText = NULL;
	if( mode == COUNT_MODE_SPLITITEM )
	{
		pt.x = pclclient->GameMouseX;
		pt.y = pclclient->GameMouseY;

		// ���̾�α� ��ġ�� ȭ���� ������ ��ġ ����
		if ( ( pt.x + GetWidth() ) > pclclient->GetScreenXSize() )
			pt.x -= GetWidth();
		if ( ( pt.y + GetHeight() ) > pclclient->GetScreenYSize() )
			pt.y -= GetHeight();

		pText = GetTxtFromMgr( 6424 );
	}
	else if(COUNT_MODE_PRESENTITEM == mode)
	{
		pt.x = pclclient->GameMouseX;
		pt.y = pclclient->GameMouseY;

		// ���̾�α� ��ġ�� ȭ���� ������ ��ġ ����
		if ( ( pt.x + GetWidth() ) > pclclient->GetScreenXSize() )
			pt.x -= GetWidth();
		if ( ( pt.y + GetHeight() ) > pclclient->GetScreenYSize() )
			pt.y -= GetHeight();

		pText = GetTxtFromMgr( 15627 );
	}
	else
	{
		pt.x = ( pclclient->GetScreenXSize() - GetWidth() ) / 2 + 40;
		pt.y = ( pclclient->GetScreenYSize() - GetHeight() ) / 2;
		pText = GetTxtFromMgr( 6425 );
	}
	m_pStaticInput->SetText( pText );
	MovePos( pt.x , pt.y );


	// ���� ����( ���õ� ������ �̸����� )
	if(COUNT_MODE_PRESENTITEM == mode)
	{
		pText = GetTxtFromMgr(6071);	
	}
	else
	{
		SI16 siUnique = ((cltClient*)pclClient)->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siSelectedItemIndex].siUnique;

		pText = (TCHAR*)pclClient->pclItemManager->GetName(siUnique);
	}
	SetTitle( pText );

	Show( true );
}


