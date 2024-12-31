#include "NBokBulBokEventReserveListDlg.h"

#include "Char/CharManager/CharManager.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../Client/Client.h"

#include "../Client/Client_BokBulBokMgr/Client_BBBMgr.h"






extern cltCommonLogic* pclClient;

CBokBulBokEventReserveListDlg::CBokBulBokEventReserveListDlg()
{
}

CBokBulBokEventReserveListDlg::~CBokBulBokEventReserveListDlg()
{
	Destroy();
}

void CBokBulBokEventReserveListDlg::init()
{
	TCHAR szPortrait[256];
	SI32  siPortraitFont;
	pclClient->pclKindInfoSet->GetNPCImageFileAndFont(pclClient->GetUniqueFromHash(TEXT("KIND_BOKBULBOKNPC")), szPortrait, sizeof(szPortrait), &siPortraitFont);

}

void CBokBulBokEventReserveListDlg::Destroy()
{
}

void CBokBulBokEventReserveListDlg::Create()
{
	// �̹� �����Ǿ��ٸ� ����
	if( IsCreate() == true )
	{
		DeleteDialog();
		return;  
	}

	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/NBokBulBokDlg/DLG_BokBulBok_ReserveList2.ddf"));
	file.CreatePopupDialog( this, NBOKBULBOK_RESERVELIST_DLG, TEXT("dialog_reserve_list"), StaticBokBulBokEventReserveListDlgProc );

	file.CreateControl( m_InterfaceFactory.CreateUserInterface( LIST, NBOKBULBOK_RESERVELIST_LIST,				this), NBOKBULBOK_RESERVELIST_LIST,				TEXT("listbox_reserve") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NBOKBULBOK_RESERVELIST_BUTTON_APPLY,	this), NBOKBULBOK_RESERVELIST_BUTTON_APPLY,		TEXT("button_apply_reserve") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(	BUTTON, NBOKBULBOK_RESERVELIST_BUTTON_CANCEL,	this), NBOKBULBOK_RESERVELIST_BUTTON_CANCEL,	TEXT("button_cancel_reserve") );
	file.CreateControl( m_InterfaceFactory.CreateUserInterface(	BUTTON, NBOKBULBOK_RESERVELIST_BUTTON_CLOSE,	this), NBOKBULBOK_RESERVELIST_BUTTON_CLOSE,		TEXT("button_close_reserve") );

	CList* pList = m_InterfaceFactory.GetList(NBOKBULBOK_RESERVELIST_LIST);
	if( pList )
	{
		SI16 siNumberWidth		= 40;
		SI16 siReasonWidth		= pList->GetWidth()	- siNumberWidth;

		pList->SetBorder(true);
		pList->SetBKColorUse(true);

		TCHAR* pText = GetTxtFromMgr(1641);	// ��ȣ
		pList->SetColumn(0, siNumberWidth, pText);
		pText = GetTxtFromMgr(1556);		// �̸�
		pList->SetColumn(1, siReasonWidth, pText);
	}

	/*GetWaitList((_BBBWaitUserData*) pWaitList);
	cltCharClient* pCharClient = pclClient->pclCM->GetCharClient(1)	;
	if(pCharClient!=NULL )
	{
		GetReserveList( pCharClient->pclCI->GetPersonID() );
	}*/
}

void CALLBACK CBokBulBokEventReserveListDlg::StaticBokBulBokEventReserveListDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{	
	CBokBulBokEventReserveListDlg *pThis = ( CBokBulBokEventReserveListDlg* )pControllerMgr;
	pThis->NBokBulBokEventReserveListDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CBokBulBokEventReserveListDlg::NBokBulBokEventReserveListDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{	
	cltClient* pClient = (cltClient*) pclClient;

	if( pClient == NULL ) return;

	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NBOKBULBOK_RESERVELIST_BUTTON_APPLY:		// ����� ��û ��
		{
			if ( false == pClient->m_pClient_BBBMgr->IsReserved() )		// ��� ����Ʈ�� ����� ���� ���������� ������ ��⸮��Ʈ ��� ��û ��Ŷ ����
			{
				cltCharClient* pclCharClient = pClient->pclCM->GetCharClient(1)	;
				if( pclCharClient != NULL  )
				{
					// ����� ���� �ϰڴٰ� �޼��� ������ ��û
					cltGameMsgRequest_BBB_WaitList_Answer clinfo( pclCharClient->pclCI->GetPersonID() );		// ������ ��⸮��Ʈ ��� ��û ����
					cltMsg clMsg(GAMEMSG_REQUEST_BBB_WAITLIST_ANSWER, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}

				//DeleteDialog();
			}
			else
			{
				// ���� �̹� ����� ����Ʈ�� ����� �Ǿ� �ִ� ��Ȳ�϶� ��Ŷ ������ �ʰ� ��� ���ִٴ� �޼���â �����
				
				cltClient* pClient = (cltClient*)pclClient;

				TCHAR*	pTitle	= GetTxtFromMgr(40065); // ���Һ� ����
				TCHAR*	pBody	= GetTxtFromMgr(40109); // ���~! �̹� �ѹ� ���� �ϼ̳׿�. ��� �Ŀ� �ٽ� ������ �ּ���.
				pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
			}
		}
		break;
	case NBOKBULBOK_RESERVELIST_BUTTON_CANCEL:		// ����� ��� ��
		{
			if ( true == pClient->m_pClient_BBBMgr->IsReserved() )		// ���� ��� ����Ʈ�� ��� �Ǿ� �ִ� ��쿡�� ��� ��Ŷ ����
			{
				pClient->m_pClient_BBBMgr->SetReserveStatus( false );	// �ϴ� Ŭ���̾�Ʈ���� ����� ��� ��Ȳ�� false�� �ٲٰ� �������� ��� ��Ŷ ����.
				
				cltCharClient* pclCharClient = pClient->pclCM->GetCharClient(1)	;
				// ������ ����� ����Ѱ� ��� �϶�� ��Ŷ ����
				cltGameMsgRequest_BBB_WaitList_Cancel clinfo( pclCharClient->pclCI->GetPersonID() );
				cltMsg clMsg( GAMEMSG_REQUEST_BBB_WAITLIST_CANCEL, sizeof(clinfo),(BYTE*)&clinfo);
				pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
			}
			//DeleteDialog();
		}
		break;
	case NBOKBULBOK_RESERVELIST_BUTTON_CLOSE:
		{
			DeleteDialog();
		}
		break;
	}
}

// ����Ʈ�� ���� �����͸� ��û�Ѵ�.
void CBokBulBokEventReserveListDlg::GetReserveList( SI32 siPersonID )
{	
	/*CList* pList = m_InterfaceFactory.GetList( NBOKBULBOKEVENT_RESERVE_LIST );

	pList->Clear();

	stListBoxItemData tempItemData;

	for ( SI32 i=0; i<MAX_SYSTEMREWARD_LIST; ++i )
	{
		tempItemData.Init();

		tempItemData.Set( 0, SI32ToString(i+1) );
		tempItemData.Set( 1, pMsg->clInfo[i].GetCharName());

		pList->AddItem( &tempItemData );
	}

	pList->Refresh();*/
}

// ����Ʈ�� ������ �Է�
void CBokBulBokEventReserveListDlg::SetReserveList()
{
	/*
	cltGameMsgRequest_ReserveList clinfo( siPersonID );
	cltMsg clMsg(GAMEMSG_REQUEST_NBOKBULBOK_EVENT_GET_RESERVE_LIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);*/
}

// ����� ��û ��ư ������ �� ȣ��Ǵ� �κ� 
void CBokBulBokEventReserveListDlg::SetListData(TCHAR** ppWaitList)
{
	CList* pList = m_InterfaceFactory.GetList( NBOKBULBOK_RESERVELIST_LIST );

	TCHAR WaitList[MAX_RESERVATION_NUM][MAX_CHARACTER_NAME_LENGTH];
	ZeroMemory( WaitList, sizeof(TCHAR) * MAX_RESERVATION_NUM * MAX_CHARACTER_NAME_LENGTH );

	memcpy( WaitList, ppWaitList, sizeof(TCHAR) * MAX_RESERVATION_NUM * MAX_CHARACTER_NAME_LENGTH );

	pList->Clear();

	stListBoxItemData tempItemData;

	for ( SI32 i=0; i< MAX_RESERVATION_NUM; ++i )
	{
		tempItemData.Init();

		tempItemData.Set( 0, SI32ToString(i+1) );
		tempItemData.Set( 1, WaitList[i] );

		pList->AddItem( &tempItemData );
	}

	pList->Refresh();
}