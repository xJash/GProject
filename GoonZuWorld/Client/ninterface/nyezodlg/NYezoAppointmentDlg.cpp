#include "../Client/NInterface/NYezoDlg/NYezoAppointmentDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"


#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/List.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "../../Client.h"

#include "../CommonLogic/TextMgr/TextMgr.h"

#include "../common/PersonInfo.h"
#include "../common/Char/CharManager/CharManager.h"

#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/CommonLogic.h"
#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/Msg/MsgType-Web.h"
#include "../common/Char/CharCommon/Char-Common.h"

extern cltCommonLogic* pclClient;

CNYezoAppointmentDlg::CNYezoAppointmentDlg() : CDialogController()
{
	memset( m_stYezoAngelList, 0, sizeof(YezoAngelList) * MAX_YEZO_ANGELLIST );

	m_siSelectListInx = -1 ;
	m_siSelectList = 0 ;

	m_pList = NULL;
	m_pButton[0] = NULL;
	m_pButton[1] = NULL;
	m_pButton[2] = NULL;
}

CNYezoAppointmentDlg::~CNYezoAppointmentDlg()
{
	SAFE_DELETE(m_pList);
	SAFE_DELETE(m_pButton[0]);
	SAFE_DELETE(m_pButton[1]);
	SAFE_DELETE(m_pButton[2]);
}

void CNYezoAppointmentDlg::Create()
{
	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/NYezoDlg/DLG_Yezo_Appointment.ddf"));
	file.CreatePopupDialog( this, NYEZOAPPOINTMENT_DLG, TEXT("dialog_Yezo_Appointment"), StaticCallBackDialogNYezoAppointmentDlg );

	NEWCLIST(m_pList);
	NEWCBUTTON(m_pButton[0]);
	NEWCBUTTON(m_pButton[1]);
	NEWCBUTTON(m_pButton[2]);

	file.CreateControl( m_pList, NYEZOAPPOINTMENT_DIALOG_LIST, TEXT("listbox_NONAME1") );
	TCHAR* pText = GetTxtFromMgr(3299);
	m_pList->SetColumn(0, 168, pText);
	pText = GetTxtFromMgr(3300);
	m_pList->SetColumn(1, 40, pText);
	pText = GetTxtFromMgr(2102);
	m_pList->SetColumn(2, 60, pText);
    m_pList->SetColumn(3, 40, TEXT(""));
	m_pList->SetBKColorUse( true );
	m_pList->SetBorder( true );
	m_pList->Refresh();

	file.CreateControl( m_pButton[0], NYEZOAPPOINTMENT_DIALOG_BUTTON1, TEXT("button_NONAME1") );
	file.CreateControl( m_pButton[1], NYEZOAPPOINTMENT_DIALOG_BUTTON2, TEXT("button_NONAME2") );
	file.CreateControl( m_pButton[2], NYEZOAPPOINTMENT_DIALOG_BUTTON3, TEXT("button_NONAME3") );

	//KHY - 0220 -  푸치코미 옵션 삭제. = 꼼지가기
	if(!pclClient->IsCountrySwitch(Switch_Puchikomi)) 
	{
		m_pButton[2]->Show(false);
	}

	Hide();
}

void CNYezoAppointmentDlg::Action()
{

}

void CNYezoAppointmentDlg::Hide()
{
	CControllerMgr::Show( false );

}

void CNYezoAppointmentDlg::Show()
{
	CControllerMgr::Show( true );

}

void CALLBACK CNYezoAppointmentDlg::StaticCallBackDialogNYezoAppointmentDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNYezoAppointmentDlg *pThis = (CNYezoAppointmentDlg *)pControllerMgr;
	pThis->CallBackDialogNYezoAppointmentDlg( nEvent, nControlID, pControl );
}

void CALLBACK CNYezoAppointmentDlg::CallBackDialogNYezoAppointmentDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;

	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			Hide();
		}
		break;

	case NYEZOAPPOINTMENT_DIALOG_LIST:
		{
			switch( nEvent )
			{
			case EVENT_LISTBOX_SELECTION:
				{
					SI32 SelectIndex = m_pList->GetSelectedIndex();

					if(SelectIndex < 0)
						return;

					m_siSelectListInx = m_siListIndex[SelectIndex] ; 
				}
				break;
			}
		}
		break;

	case NYEZOAPPOINTMENT_DIALOG_BUTTON1:	// 임명 
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( m_siSelectList != 1 ) break ;
					if ( m_siSelectListInx < 0 || m_siSelectListInx > MAX_YEZO_ANGELLIST ) break;
					cltGameMsgRequest_SetAngel clinfo(m_siSelectListInx,true);
					cltMsg clMsg( GAMEMSG_REQUEST_SETANGEL, sizeof( clinfo ), (BYTE*)&clinfo );
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
		break;

	case NYEZOAPPOINTMENT_DIALOG_BUTTON2:	// 삭제 
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					switch(m_siSelectList)
					{
					case 1:
						{
							if ( m_siSelectListInx < 0 || m_siSelectListInx > MAX_YEZO_ANGELLIST ) break;
							cltGameMsgRequest_SetAngelApplyer clinfo(false,m_siSelectListInx);
							cltMsg clMsg( GAMEMSG_REQUEST_SETANGELAPPLYER, sizeof( clinfo ), (BYTE*)&clinfo );
							pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
						}
						break;
					case 2:
						{
							if ( pclclient->pclCM->CR[1]->pclCI->clBI.uiGRank == GRANK_MINISTER3 )
							{
								if ( m_siSelectListInx < 0 || m_siSelectListInx > MAX_YEZO_ANGELLIST ) break;
								cltGameMsgRequest_SetAngel clinfo(m_siSelectListInx,false);
								cltMsg clMsg( GAMEMSG_REQUEST_SETANGEL, sizeof( clinfo ), (BYTE*)&clinfo );
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
							else if ( pclclient->pclCM->CR[1]->pclCI->clBI.uiAngelSwitch )
							{
								cltGameMsgRequest_SetAngel clinfo(-1,false);
								cltMsg clMsg( GAMEMSG_REQUEST_SETANGEL, sizeof( clinfo ), (BYTE*)&clinfo );
								pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
							}
						}
						break;
					}
				}
				break;
			}
		}
		break;

	case NYEZOAPPOINTMENT_DIALOG_BUTTON3:	// 꼼지 가기
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( m_siSelectListInx < 0 || m_siSelectListInx > MAX_YEZO_ANGELLIST ) break;
					
					cltGameMsgRequest_UserPuchikomiURL clUserPuchikomi( m_stYezoAngelList[m_siSelectListInx].szName );
					cltMsg clMsg( GAMEMSG_REQUEST_USERPUCHIKOMIURL , sizeof( clUserPuchikomi ), (BYTE*)&clUserPuchikomi );
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
					/*
					cltGameMsgRequest_Userid clUserid( m_stYezoAngelList[m_siSelectListInx].szName );
					cltMsg clMsg( GAMEMSG_REQUEST_USERID, sizeof( clUserid ), (BYTE*)&clUserid );
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
					*/
				}
				break;
			}
		}
		break;
	}
}

bool CNYezoAppointmentDlg::SetListDlg(SI32 index)
{
	cltClient *pclclient = (cltClient*)pclClient;

	Show();
	m_siSelectList = index ;

	switch(index)
	{
	case 1:
		{
			if ( pclclient->pclCM->CR[1]->pclCI->clBI.uiGRank != GRANK_MINISTER3 )
				return false ;

			TCHAR* pText = GetTxtFromMgr(2103);
		//	SetWindowText(m_hListDlg, pText);
			SetTitle(pText);
		}
		break;
	case 2:
		{
			if ( pclclient->pclCM->CR[1]->pclCI->clBI.uiGRank != GRANK_MINISTER3 )
			{
				EnableButton(m_pButton[0], FALSE);
				
			//	hwnd = GetDlgItem(m_hListDlg,IDC_BUTTON_ANGEL_APPOINTMENT);
			//	EnableWindow(hwnd,FALSE) ;

			//	hwnd = GetDlgItem(m_hListDlg,IDC_BUTTON_ANGEL_DELETE);
				TCHAR* pText = GetTxtFromMgr(2104);
				if ( pclclient->pclCM->CR[1]->pclCI->clBI.uiAngelSwitch )
			//		SetWindowText(hwnd, pText);
					m_pButton[1]->SetText(pText, DT_CENTER | DT_VCENTER);
				else
					EnableButton(m_pButton[1], FALSE);
			}
			else
			{
			//	hwnd = GetDlgItem(m_hListDlg,IDC_BUTTON_ANGEL_APPOINTMENT);
			//	EnableWindow(hwnd , FALSE );
				EnableButton(m_pButton[0], FALSE);
			}
			TCHAR* pText = GetTxtFromMgr(2105);
		//	SetWindowText(m_hListDlg,pText);
			SetTitle(pText);
		}
		break;
	default:
		return false ;
		break;
	}
	return true;
}

void CNYezoAppointmentDlg::ShowListDlg(YezoAngelList yezoangellist [])
{
//	ListView_DeleteAllItems(m_hAngelList);
	m_pList->Clear();

	SI32 listindex = 0 ;

	memcpy(m_stYezoAngelList,yezoangellist,sizeof(YezoAngelList) * MAX_YEZO_ANGELLIST);

	for ( int i = 0 ; i < MAX_YEZO_ANGELLIST ; i ++ )
	{
		m_siListIndex[i] = -1 ;
		if ( yezoangellist[i].siLevel <= 0 ) continue ;
		if ( yezoangellist[i].siPersonID <= 0 ) continue ;
		if ( !_tcscmp(yezoangellist[i].szAccountID,TEXT("")) ) continue ;
		if ( !_tcscmp(yezoangellist[i].szName,TEXT("")) ) continue ;

		TCHAR buffer[256] = TEXT("") ;
		
		stListBoxItemData Data;
		Data.Set(0, yezoangellist[i].szName);
		StringCchPrintf(buffer, 256, TEXT("%d"),yezoangellist[i].siLevel ) ;
		Data.Set(1, buffer);
		StringCchPrintf(buffer, 256, TEXT("%d"),yezoangellist[i].siFameLevel ) ;
		Data.Set(2, buffer);

		m_pList->AddItem(&Data);
		
		m_siListIndex[listindex] = i ;
		listindex ++ ;
	}
	m_pList->Refresh();
}

void CNYezoAppointmentDlg::EnableButton(CButton* pButton, BOOL Flag)
{
	if(Flag)
	{
		pButton->SetFontColor(RGB(0, 0, 0));
		pButton->Enable(true);
	}
	else
	{
		pButton->SetFontColor(RGB(225, 225, 225));
		pButton->Enable(false);
	}
}