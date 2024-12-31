#include "../Client/NInterface/NNewItemMalldlg/NPresentWindowDlg.h"
#include "../Client/NInterface/NNewItemMalldlg/NPresentInfoWindowDlg.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/RadioButton.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../../Client.h"
#include "../CommonLogic/TextMgr/TextMgr.h"

#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "Msg/MsgType-ItemMall.h"

#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;

CNPresentWindowDlg::CNPresentWindowDlg() : CDialogController()
{
	m_siMyNcoin					= 0;
	m_siSelectProductKey		= 0;
	m_siSelectItemPrice			= 0;
	m_siSelectFontIndex			= 0;
	m_siMyEventNcoin			= 0;
	m_siSelectItemEventPrice	= 0;
	
	m_siBuyItemNum = 1;
	m_bIdCheck = false;

	strcpy(m_szSelectItemName, "");

	InitItemData();

	SI16 i;
	for( i = 0; i < 6; ++i )
	{
		m_pButton[i] = NULL;		
	}
	for( i = 0; i < 3; ++i )
	{
		m_pRadioButton[i] = NULL;		
	}
	for( i = 0; i < 29; ++i )
	{
		m_pStatic[i] = NULL;		
	}
	for( i = 0; i < 4; ++i )
	{
		m_pEdit[i] = NULL;		
	}
	m_pComboBox =  NULL;

	for( i = 0; i < 9; ++i )
	{
		m_pEventStatic[i] = NULL;		
	}
	m_pEventStaticBack = NULL;		


	m_szAccountID[0] = '\0';
	m_szCharName[0] = '\0';
	m_siServerUnique = -1;

}

CNPresentWindowDlg::~CNPresentWindowDlg()
{
	SI16 i;
	for( i = 0; i < 6; ++i )
	{
		SAFE_DELETE(m_pButton[i]);
	}
	for( i = 0; i < 3; ++i )
	{
		SAFE_DELETE(m_pRadioButton[i]);	
	}
	for( i = 0; i < 29; ++i )
	{
		SAFE_DELETE(m_pStatic[i]);	
	}
	for( i = 0; i < 4; ++i )
	{
		SAFE_DELETE(m_pEdit[i]);		
	}
    SAFE_DELETE(m_pComboBox);
	
	for( i = 0; i < 9; ++i )
	{
		SAFE_DELETE( m_pEventStatic[i] );
	}
	SAFE_DELETE(m_pEventStaticBack)
}

void CNPresentWindowDlg::InitItemData()
{
	SI32 i;
	for( i=0; i < 3; ++i)
	{
		// ������ �ʱ�ȭ
		m_clItemData[i].Init();
	}
}

void CNPresentWindowDlg::Create()
{
	if ( ! IsCreate() ) 
	{
		cltClient *pclclient = (cltClient *)pclClient;

		if(pclclient->m_pDialog[ NBUYWINDOW_DLG ])
			pclclient->m_pDialog[ NBUYWINDOW_DLG ]->DeleteDialog();

		if(pclclient->m_pDialog[ NBUYITEMINFOWINDOW_DLG ])
			pclclient->m_pDialog[ NBUYITEMINFOWINDOW_DLG ]->DeleteDialog();

		if(pclclient->m_pDialog[ NPRESENTINFOWINDOW_DLG ])
			pclclient->m_pDialog[ NPRESENTINFOWINDOW_DLG ]->DeleteDialog();

		CInterfaceFile file;

		file.LoadFile("NInterface/Data/NNewItemMallDlg/DLG_PresentWindow.ddf");
		file.CreatePopupDialog( this, NPRESENTWINDOW_DLG, "dialog_presentwindow", StaticCallBackDialogNPresentWindowDlg );

		MovePos( pclclient->GetScreenXSize()/2 - 150 + 45, pclclient->GetScreenYSize()/2 - 370 + 100);
		
		NEWCCOMBOBOX(m_pComboBox);
        
		SI16 i;
		for( i = 0; i < 6; ++i )
		{
			NEWCBUTTON(m_pButton[i]);
		}
		for( i = 0; i < 3; ++i )
		{
			NEWCRADIOBUTTON(m_pRadioButton[i]);	
		}
		for( i = 0; i < 29; ++i )
		{
			NEWCSTATIC(m_pStatic[i]);	
		}
		for( i = 0; i < 4; ++i )
		{
			NEWCEDIT(m_pEdit[i]);		
		}
		
		for( i = 0; i < 9; ++i )
		{
			NEWCSTATIC( m_pEventStatic[i] );
		}
		NEWCSTATIC(m_pEventStaticBack)

		char tempBuffer[100] = { '\0' };

		for( i=0; i < 3; ++i)
		{
			sprintf(tempBuffer, "radiobutton_NONAME%d", i + 1);
			file.CreateControl( m_pRadioButton[i], NPRESENTWINDOW_DIALOG_RADIOBUTTON1 + i, tempBuffer);
		}


		file.CreateControl( m_pComboBox, NPRESENTWINDOW_DIALOG_COMBOBOX,"combobox_NONAME1");

		for( i=0; i < 29; ++i)
		{
			if( i != 0 && i != 6 )
			{
				sprintf(tempBuffer, "statictext_NONAME%d", i + 1);
				file.CreateControl( m_pStatic[i], NPRESENTWINDOW_DIALOG_STATIC1 + i, tempBuffer);
			}
		}

		for( i = 0; i < 9; ++i )
		{
			sprintf( tempBuffer, "statictext_NONAME%d", i + 30 );
			file.CreateControl( m_pEventStatic[i], NPRESENTWINDOW_DIALOG_STATIC_EVENT0 + i, tempBuffer );
		}
		file.CreateControl( m_pEventStaticBack, NPRESENTWINDOW_DIALOG_STATIC_EVENT_BACK, "statictext_NONAME39");
		
		file.CreateControl( m_pStatic[0], NPRESENTWINDOW_DIALOG_STATIC1 + 0, "statictext_NONAME1");
		file.CreateControl( m_pStatic[6], NPRESENTWINDOW_DIALOG_STATIC1 + 6, "statictext_NONAME7");

		file.CreateControl( m_pButton[0], NPRESENTWINDOW_DIALOG_BUTTON_IDCHECK, "button_NONAME1"); 
		file.CreateControl( m_pButton[1], NPRESENTWINDOW_DIALOG_BUTTON_NCOIN, "button_NONAME2"); 
		file.CreateControl( m_pButton[2], NPRESENTWINDOW_DIALOG_BUTTON_PRESENT, "button_NONAME3"); 
		file.CreateControl( m_pButton[3], NPRESENTWINDOW_DIALOG_BUTTON_CANCEL, "button_NONAME4"); 
		file.CreateControl( m_pButton[4], NPRESENTWINDOW_DIALOG_BUTTON_PLUS, "button_NONAME5"); 
		file.CreateControl( m_pButton[5], NPRESENTWINDOW_DIALOG_BUTTON_MINUS, "button_NONAME6"); 



		file.CreateControl( m_pEdit[0], NPRESENTWINDOW_DIALOG_EDIT1, "editbox_NONAME1"); 
		file.CreateControl( m_pEdit[1], NPRESENTWINDOW_DIALOG_EDIT2, "editbox_NONAME2");
		file.CreateControl( m_pEdit[2], NPRESENTWINDOW_DIALOG_EDIT3, "editbox_NONAME3");
		file.CreateControl( m_pEdit[3], NPRESENTWINDOW_DIALOG_EDIT3, "editbox_NONAME4");
		



		// ID üũ ������ �� ������
  		m_pButton[2]->Enable(false);

 		m_pStatic[2]->SetTextPrintOption(DT_CENTER);
		m_pStatic[9]->SetTextPrintOption(DT_RIGHT);
		m_pStatic[11]->SetTextPrintOption(DT_RIGHT);
		m_pStatic[13]->SetTextPrintOption(DT_RIGHT);

		m_pEventStatic[6]->SetTextPrintOption(DT_RIGHT);
		m_pEventStatic[7]->SetTextPrintOption(DT_RIGHT);
		m_pEventStatic[8]->SetTextPrintOption(DT_RIGHT);


		m_pEdit[3]->SetChangeTextDrawMode(true);

		m_pEdit[2]->SetTextPrintOption(DT_CENTER);
		m_pEdit[2]->SetText("1");

		m_pEdit[1]->SetMaxEditTextLength(200);
		m_pEdit[1]->SetAutoScroll(true);
		

		if( ConstServiceArea_China == pclClient->siServiceArea )
		{
			m_pComboBox->Enable( false );
		}
		else if( ConstServiceArea_Japan == pclClient->siServiceArea )
		{
			stComboBoxItemData ComboBoxItemData;
			TCHAR * pText = NULL;

			for( i = 1; i <= MAX_SERVER_NUMBER ; i++  )
			{
				pText =  pclclient->GetServerNameFromUnique(i);

				if( pText == NULL) continue;

				ComboBoxItemData.Init();
				ComboBoxItemData.Set( pText );					
				m_pComboBox->AddItem( &ComboBoxItemData );   // Ÿ�԰��� �ִ´�
			}

			SI16 Cursel = pclClient->siServerUnique - 1;

			if( Cursel < 0 || Cursel >= MAX_SERVER_NUMBER)
			{
				Cursel = 0;
			}

			m_pComboBox->SetCursel( Cursel );
		}
		else
		{
			m_pComboBox->Enable( false );
			m_pComboBox->SetText( pclclient->clSelectedWorldInfo.baseinfo.worldname );

		}
		
		SetTopMostWindow(true);
		SetTimerOnOff(true);

		NHNChinaInit();
	}
	else
	{
		DeleteDialog();
	}

	// [����] USA�� �����Ҷ� �޽��� �����ϴ� �κ��� �Ⱥ��̰� �Ѵ�. => 2008-9-11
	// [����] KOREA�� ���� 20081028(�����ϱ� �޽���)
	if ( pclClient->IsWhereServiceArea(ConstServiceArea_USA | ConstServiceArea_Korea) )
	{
		m_pStatic[18]->Show( false );
		m_pStatic[28]->Show( false );
		m_pEdit[1]->Show( false );
	}
}


void CALLBACK CNPresentWindowDlg::StaticCallBackDialogNPresentWindowDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNPresentWindowDlg *pThis = (CNPresentWindowDlg *)pControllerMgr;
	pThis->CallBackDialogNPresentWindowDlg( nEvent, nControlID, pControl );
}

void CALLBACK CNPresentWindowDlg::CallBackDialogNPresentWindowDlg( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;

	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;

	case NPRESENTWINDOW_DIALOG_RADIOBUTTON1:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					SelectRadioButton(0);
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_RADIOBUTTON2:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					SelectRadioButton(1);
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_RADIOBUTTON3:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					SelectRadioButton(2);
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_IDCHECK:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if( strlen(m_pEdit[0]->GetText()) < 0 || strlen(m_pEdit[0]->GetText()) > 20 )
						return;
					
					SI16 SelectedServerUnique = m_pComboBox->GetSelectedIndex() + 1;

					cltClient *pclclient = (cltClient *)pclClient;
					cltGameMsgRequest_Check_AccountID pclinfo( SelectedServerUnique  ,m_pEdit[0]->GetText());
					cltMsg clMsg( GAMEMSG_REQUEST_CHECK_ACCOUNTID, sizeof( pclinfo ), (BYTE*)&pclinfo );
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_NCOIN:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if(pclClient->siServiceArea == ConstServiceArea_Japan)
					{
						cltGameMsgRequest_BillPage_URL clinfo( pclclient->szID,pclclient->szPassword);
						cltMsg clMsg(GAMEMSG_REQUEST_BILLPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
						pclclient->SendMsgToServer( (sPacketHeader*)&clMsg);
					}
					else if( pclClient->siServiceArea == ConstServiceArea_Korea )
					{
						ShellExecute( NULL, NULL, TEXT("http://cash.ndoors.com/"), NULL, NULL, SW_SHOWNORMAL );
					}
					else if( pclClient->IsWhereServiceArea( ConstServiceArea_China) )
					{
						ShellExecute( NULL,NULL,TEXT("http://www.youxi.net.cn/AccountManage/AddCostIdx.aspx"),NULL,NULL,SW_SHOWNORMAL );
					}
					else if ( pclClient->IsWhereServiceArea( ConstServiceArea_EUROPE ) )
					{
						ShellExecute( NULL,NULL,TEXT("http://billing.aeriagames.com/index.asp"),NULL,NULL,SW_SHOWNORMAL );
					}
					else if ( pclClient->IsWhereServiceArea( ConstServiceArea_NHNChina ) )
					{
						ShellExecute( NULL,NULL,TEXT("http://www.newhljz.cn"),NULL,NULL,SW_SHOWNORMAL );
					}
					else if( pclClient->IsWhereServiceArea( ConstServiceArea_English) )
					{
						// PCK : �۷ι��� ��� NHNȸ���� NDIȸ���� ���� �������� ��ũ�������� �ٸ���. (09.03.30)			
						NTCHARString32	kID(pclclient->szID);

						if( kID.Find("@nh") >= 0 )		// NHN ȸ���̸�
						{
							ShellExecute( NULL, NULL, TEXT("http://luminary.ijji.com/center/billing/transfer_gcoin_01.asp"), NULL, NULL, SW_SHOWNORMAL );
						}
						else							// NDI ȸ���̸�
						{
							ShellExecute( NULL, NULL, TEXT("https://billing.ndoorsgames.com/fillup/payment_option.asp?site_code=luminary"), NULL, NULL, SW_SHOWNORMAL );
						}
					}
					else
					{
						ShellExecute( NULL,NULL,TEXT("https://billing.ndoorsgames.com/fillup/payment_option.asp?site_code=luminary"),NULL,NULL,SW_SHOWNORMAL );
					}
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_PRESENT:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if(m_siSelectProductKey < 1)
						return;

					if(m_siSelectItemPrice < 1)
						return;

					if(m_siBuyItemNum <= 0)
					{
						/*
						char* pTitle = "���� ����";
						char* pText  = "���� ������ 1�� �̻��̾�� �մϴ�.";

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);
						*/
						return;
					}

					if(m_siBuyItemNum > 10)
					{
						/*
						char* pTitle = "���� ����";
						char* pText  = "���� ������ 10�� �����̾�� �մϴ�.";

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);
						*/
						return;
					}

					if(m_siMyNcoin - m_siBuyItemNum*m_siSelectItemPrice < 0)
					{
						TCHAR* pTitle = GetTxtFromMgr(6127);
						TCHAR* pText  = GetTxtFromMgr(5950);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);

						return;
					}
					
					if( m_siMyEventNcoin - m_siBuyItemNum * m_siSelectItemEventPrice < 0 )
					{
						TCHAR* pTitle = GetTxtFromMgr(6127);
						TCHAR* pText  = GetTxtFromMgr(5950);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);

						return;
					}
#ifdef _IAF_EXPORT
					if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
					{
						TCHAR ResultBuf[1024] = "";
						IAF::Filtering( m_pEdit[1]->GetText(), ResultBuf, sizeof(ResultBuf) );
						memcpy( m_pEdit[1]->GetText(), ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
					}
#else
					//KHY - 0813 - �弳 ���͸�.
					pclclient->m_pCAbuseFilter->CheckAbuse( m_pEdit[1]->GetText());
#endif

					if(pclclient->m_pDialog[ NPRESENTINFOWINDOW_DLG ] == NULL)
					{
						pclclient->CreateInterface(NPRESENTINFOWINDOW_DLG);
						((CNPresentInfoWindowDlg*)pclclient->m_pDialog[NPRESENTINFOWINDOW_DLG])->SetPresentInfoWindow(	m_pStatic[15]->GetText(),
																														m_pEdit[1]->GetText(),
																														m_szSelectItemName,
																														m_siSelectProductKey,
																														m_siBuyItemNum,
																														m_siSelectItemPrice,
																														m_siSelectItemEventPrice,
																														m_siSelectFontIndex,
																														m_szAccountID,
																														m_siServerUnique,
																														m_szCharName);
					}

					DeleteDialog();
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_CANCEL:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					DeleteDialog();
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_PLUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if(pclClient->IsWhereServiceArea( ConstServiceArea_USA ))
						return;

					++m_siBuyItemNum;
					//[����] �����Ҽ������� ������ ������Ű��.
					if(		0 > m_siMyNcoin      - m_siSelectItemPrice      * m_siBuyItemNum 
						||	0 > m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum	) 
					{ 
						--m_siBuyItemNum; 
						return;
					}

					// 10�� �̻� �� ��� ���´�
					if( m_siBuyItemNum > 10 )
					{
						m_siBuyItemNum = 10;
/*
						char* pTitle = "���� ����";
						char* pText  = "�ѹ� ���Ž� 10�� �̻� �� ���� �����ϴ�.";

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);*/
					}

					TCHAR tempBuffer[50] = { '\0' };
					sprintf( tempBuffer, "%d", m_siBuyItemNum );
					m_pEdit[2]->SetText( tempBuffer );
					
					//TCHAR * pText = GetTxtFromMgr(5944);

					g_JYLibFunction.SetNumUnit(m_siSelectItemPrice * m_siBuyItemNum, tempBuffer, 50,NULL );
					m_pStatic[9]->SetText(tempBuffer);
					g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer, 50,NULL );
					m_pStatic[11]->SetText(tempBuffer);
					g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice * m_siBuyItemNum, tempBuffer, 50,NULL );
					m_pStatic[13]->SetText(tempBuffer);

					//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
					g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
					m_pEventStatic[6]->SetText( tempBuffer );
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
					m_pEventStatic[7]->SetText(tempBuffer);
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
					m_pEventStatic[8]->SetText( tempBuffer );
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_BUTTON_MINUS:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if(pclClient->IsWhereServiceArea( ConstServiceArea_USA ))
						return; 

					--m_siBuyItemNum;

					// 10�� �̻� �� ��� ���´�
					if( m_siBuyItemNum <= 0 )
					{
						m_siBuyItemNum = 1;
						
						/*
						char* pTitle = "���� ����";
						char* pText  = "�ּ��� 1���̻� ���� �����մϴ�.";

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText );
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetTopMostWindow(true);
						*/
					}

					TCHAR tempBuffer[50] = { '\0' };
					sprintf( tempBuffer, "%d", m_siBuyItemNum );
					m_pEdit[2]->SetText( tempBuffer );

					//TCHAR * pText = GetTxtFromMgr(5944);

					g_JYLibFunction.SetNumUnit(m_siSelectItemPrice*m_siBuyItemNum, tempBuffer, 50,NULL );
					m_pStatic[9]->SetText(tempBuffer);

					g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer,  50,NULL );
					m_pStatic[11]->SetText(tempBuffer);

					g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice*m_siBuyItemNum, tempBuffer,  50,NULL );
					m_pStatic[13]->SetText(tempBuffer);

					//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
					g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
					m_pEventStatic[6]->SetText( tempBuffer );
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
					m_pEventStatic[7]->SetText(tempBuffer);
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
					m_pEventStatic[8]->SetText( tempBuffer );
				}
				break;
			}
		}
		break;

	case NPRESENTWINDOW_DIALOG_EDIT3:
		{
			switch( nEvent)
			{
			case EVENT_EDITBOX_CHANGE:
				{
					if(pclClient->IsWhereServiceArea( ConstServiceArea_USA ))
					{
						m_pEdit[2]->SetText("1");
					}

					m_siBuyItemNum = atoi( m_pEdit[2]->GetText() );

					if(m_siBuyItemNum < 1)
						return;

					TCHAR tempBuffer[50] = { '\0' };
					//TCHAR* pText = GetTxtFromMgr(5944);

					g_JYLibFunction.SetNumUnit(m_siSelectItemPrice*m_siBuyItemNum, tempBuffer,  50,NULL );
					m_pStatic[9]->SetText(tempBuffer);

					g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer,  50,NULL );
					m_pStatic[11]->SetText(tempBuffer);

					g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice*m_siBuyItemNum, tempBuffer,  50,NULL );
					m_pStatic[13]->SetText(tempBuffer);

					//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
					g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
					m_pEventStatic[6]->SetText( tempBuffer );
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
					m_pEventStatic[7]->SetText(tempBuffer);
					g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
					m_pEventStatic[8]->SetText( tempBuffer );
				}
				break;
			}
		}
		break;
	}
}

//***************************************************************************************************
// Function Name	: SetPresentItemInfo
//
// Last Modified 	: 2006 / 01 / 02
// Created			: �豤��
//
// Function			: �Ϲ� ������ ���� ���� ����
//
// Inputs			: 
// Outputs			: 
// Returns			: 
//***************************************************************************************************
void CNPresentWindowDlg::SetPresentItemInfo(cltItemMallData& pitemmalldata, SI32 realcash, SI32 eventcash)
{
	// �ʱ�ȭ�� ���ְ� ����!!
 	InitItemData();

	// �Ϲ� �������̶� �Ⱓ ������ �� ���̰� �Ѵ�
	m_pRadioButton[0]->Show(false);
	m_pRadioButton[1]->Show(false);
	m_pRadioButton[2]->Show(false);

	m_pStatic[3]->Show(false);
	m_pStatic[4]->Show(false);
	m_pStatic[5]->Show(false);

	// ������ �̸�
	m_pStatic[2]->SetFontKind("����");	
	m_pStatic[2]->SetFontSize(17);
	m_pStatic[2]->SetFontWeight(FW_BOLD);

	if (pclClient->IsCountrySwitch( Switch_NoPayBack )) {
		// û��öȸ �Ұ� ���� �߰�
		TCHAR buffer[512];
		TCHAR* pText = GetTxtFromMgr(8429);

		if(pclClient->IsCountrySwitch(Switch_ItemExplain2))
			StringCchPrintf(buffer, 512,TEXT("%s\r\n%s") , pText, pitemmalldata.szExplain2 );	
		else
			StringCchPrintf(buffer, 512,TEXT("%s\r\n%s") , pText, pitemmalldata.szExplain );
		
		m_pEdit[3]->SetText( buffer /*pitemmalldata.szExplain*/);
	}
	else
	{
		if(pclClient->IsCountrySwitch(Switch_ItemExplain2))
			m_pEdit[3]->SetText( pitemmalldata.szExplain2 );									
		else
			m_pEdit[3]->SetText( pitemmalldata.szExplain );
	}

	m_pStatic[2]->SetText(pitemmalldata.szName);
	MStrCpy(m_szSelectItemName, pitemmalldata.szName, 50);

	// �ش� ������ �׸�
	// ������ �̹����� �Ѿ� ���� ���� �о���°� �ٲ��.
	// ���� ������ ��Ʈ �ε����� ���� �о� ���� ������ �ٲ۴�.
	// �׸��� �ٲ� ������ ��쿡 ���Ӱ� ��Ʈ �ε����� �־��ִ� �۾��� �ʿ���.
	TCHAR szImageFilename[256];
	SI32 siImageFontindex;
	pclClient->pclItemManager->GetItemImageItemmallFileName( pitemmalldata.siImageFont, szImageFilename,sizeof(szImageFilename), &siImageFontindex);
	m_pStatic[1]->SetFileName( szImageFilename );
	m_pStatic[1]->SetFontIndex(siImageFontindex);

	TCHAR tempBuffer[50] = { '\0' };
	//TCHAR* pText = GetTxtFromMgr(5944);

	g_JYLibFunction.SetNumUnit(pitemmalldata.siPrice, tempBuffer,  50, NULL );
	m_pStatic[9]->SetText(tempBuffer);

	m_siSelectProductKey	  = pitemmalldata.siProductKey;
	m_siSelectItemPrice		  = pitemmalldata.siPrice;
	m_siSelectItemEventPrice  = pitemmalldata.siEventPrice;
	m_siSelectFontIndex		  = pitemmalldata.siImageFont;

	if( ConstServiceArea_NHNChina == pclClient->siServiceArea )
	{
		m_siMyNcoin			= realcash;
		m_siMyEventNcoin	= eventcash;
	}
	else
	{
		m_siMyNcoin = realcash + eventcash;
	}

	g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer,  50, NULL );
	m_pStatic[11]->SetText(tempBuffer);
	g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice, tempBuffer,   50, NULL );
	m_pStatic[13]->SetText(tempBuffer);
	g_JYLibFunction.SetNumUnit(pitemmalldata.siPrice, tempBuffer, 50, NULL );
	m_pStatic[22]->SetText(tempBuffer);

	//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
	g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
	m_pEventStatic[6]->SetText( tempBuffer );
	g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
	m_pEventStatic[7]->SetText(tempBuffer);
	g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
	m_pEventStatic[8]->SetText( tempBuffer );
}

//***************************************************************************************************
// Function Name	: SetPresentFirstItemInfo
//
// Last Modified 	: 2006 / 01 / 02
// Created			: �豤��
//
// Function			: �Ⱓ�� ������ ���� ���� ä���
//
// Inputs			: 
// Outputs			: 
// Returns			: 
//***************************************************************************************************
void CNPresentWindowDlg::SetPresentFirstItemInfo(TCHAR* itemname, TCHAR * explain , TCHAR * explain2, SI32 itemfontindex, SI32 realcash, SI32 eventcash)
{
	m_siSelectFontIndex = itemfontindex;

	// ������ �̸�
	m_pStatic[2]->SetText(itemname);

	// ������ �̸�
	m_pStatic[2]->SetFontKind("����");	
	m_pStatic[2]->SetFontSize(17);
	m_pStatic[2]->SetFontWeight(FW_BOLD);

	if(pclClient->IsCountrySwitch(Switch_ItemExplain2))
		m_pEdit[3]->SetText(explain2);	
	else
		m_pEdit[3]->SetText(explain);


	// �ش� ������ �׸�
	m_pStatic[1]->SetFontIndex(itemfontindex);
	
	// �Ϲ� ������ ������ �����
	m_pStatic[22]->Show(false);
	//m_pStatic[23]->Show(false);
	//m_pStatic[24]->Show(false);

	// ĳ�� �� ���ϱ� �����ϱ⿡ ǥ�õ� ������ ������ �� �� ���Ѱ�
	if( ConstServiceArea_NHNChina == pclClient->siServiceArea )
	{
		m_siMyNcoin			= realcash;
		m_siMyEventNcoin	= eventcash;
	}
	else
	{
		m_siMyNcoin = realcash + eventcash;
	}
}

//***************************************************************************************************
// Function Name	: SetPresentDateItemInfo
//
// Last Modified 	: 2006 / 01 / 02
// Created			: �豤��
//
// Function			: ������ ������ ���� ����
//
// Inputs			: pitemmalldata - ���õ� ������ ����
// Outputs			: 
// Returns			: 
//***************************************************************************************************
void CNPresentWindowDlg::SetPresentDateItemInfo(cltItemMallData* pitemmalldata)
{

	// �ʱ�ȭ�� ���ְ� ����!!
	InitItemData();

	SI32 i;

	for(i = 0; i < 3; ++i)
	{
		// 1�ʰ��Ѱ��� �Ⱓ����
		if(pitemmalldata[i].siProductKey > 1)
		{
			m_clItemData[i].Set(&pitemmalldata[i]);
		}
	}

	// ù��° ������ �Ѵ�
	m_pRadioButton[0]->SetCheck(TRUE, CONTROLLER_KIND_RADIOBUTTON);
	m_siSelectProductKey		= m_clItemData[0].siProductKey;
	m_siSelectItemPrice			= m_clItemData[0].siPrice;
	m_siSelectItemEventPrice	= m_clItemData[0].siEventPrice;

	TCHAR tempBuffer[50] = { '\0' };
	//TCHAR * pText = GetTxtFromMgr(5944);

	g_JYLibFunction.SetNumUnit(m_clItemData[0].siPrice, tempBuffer, 50, NULL );
	m_pStatic[3]->SetText(tempBuffer);

	g_JYLibFunction.SetNumUnit(m_clItemData[1].siPrice, tempBuffer, 50, NULL );
	m_pStatic[4]->SetText(tempBuffer);

	g_JYLibFunction.SetNumUnit(m_clItemData[2].siPrice, tempBuffer, 50, NULL );
	m_pStatic[5]->SetText(tempBuffer);

	g_JYLibFunction.SetNumUnit(m_siSelectItemPrice, tempBuffer, 50, NULL );
	m_pStatic[9]->SetText(tempBuffer);

	g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer, 50, NULL );
	m_pStatic[11]->SetText(tempBuffer);

	g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice*m_siBuyItemNum, tempBuffer, 50, NULL );
	m_pStatic[13]->SetText(tempBuffer);


	//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
	g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
	m_pEventStatic[6]->SetText( tempBuffer );
	g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
	m_pEventStatic[7]->SetText(tempBuffer);
	g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
	m_pEventStatic[8]->SetText( tempBuffer );

}

//***************************************************************************************************
// Function Name	: AccountIdCheckResult
//
// Last Modified 	: 2006 / 01 / 02
// Created			: �豤��
//
// Function			: ������ ���� ���̵� üũ�� �����̸� �̸� ����
//
// Inputs			: 
// Outputs			: 
// Returns			: 
//***************************************************************************************************
void CNPresentWindowDlg::AccountIdCheckResult(TCHAR* accountId, TCHAR* name, SI16 ServerUnique ,TCHAR* CharName )
{
	cltClient* pclclient = (cltClient*) pclClient;

	// ��� ������ �̸��� ������ �����ѵд�.
	
	StringCchCopy(m_szAccountID,MAX_PLAYER_NAME,name);
	
	
#ifdef _DEBUG	
	m_siServerUnique = pclClient->siServerUnique;	//[����] ����׽ÿ��� �系���� �۵��ϹǷ� ������ 1���� �ڽ��� ���� ����ũ�� ������ ����. => 2008-7-24
#else
	m_siServerUnique = ServerUnique;
#endif
	
	StringCchCopy(m_szCharName,MAX_PLAYER_NAME,CharName);

	// ĳ���� �̸��� ������ ������
	TCHAR szBuffer[256] = {'\0'};
	if( true == pclClient->IsWhereServiceArea( ConstServiceArea_Japan ) )
	{
		TCHAR * pServerName =  pclclient->GetServerNameFromUnique(ServerUnique);

		if( pServerName == NULL )
		{
			return;
		}

		StringCchPrintf( szBuffer ,255,TEXT("%s (%s)"), CharName , pServerName  );
	}
	else if( true == pclClient->IsWhereServiceArea( ConstServiceArea_China ) )
	{
		StringCchPrintf( szBuffer ,255,TEXT("%s"), CharName );
	}
	else
	{
		StringCchPrintf( szBuffer ,255,TEXT("%s"), CharName );
	}
	
	m_pStatic[15]->SetText( szBuffer );
	m_pButton[2]->Enable(true);	
}

//***************************************************************************************************
// Function Name	: SelectRadioButton
//
// Last Modified 	: 2006 / 01 / 02
// Created			: �豤��
//
// Function			: ���õ� ���� ��ư������ ���� ����
//
// Inputs			: index - ���� ��ư �ε���(0~2) 
// Outputs			: 
// Returns			: 
//***************************************************************************************************
void CNPresentWindowDlg::SelectRadioButton(SI32 index)
{
	bool Check = m_pRadioButton[index]->IsCheck();
	if(Check)
	{
		m_siSelectProductKey      = m_clItemData[index].siProductKey;
		m_siSelectItemPrice       = m_clItemData[index].siPrice;
		m_siSelectItemEventPrice  = m_clItemData[index].siEventPrice;

		MStrCpy(m_szSelectItemName, m_clItemData[index].szName, 50);

		m_pStatic[2]->SetText(m_clItemData[index].szName);
 
		TCHAR tempBuffer[50] = { '\0' };
		//TCHAR * pText = GetTxtFromMgr(5944);

		g_JYLibFunction.SetNumUnit(m_siSelectItemPrice*m_siBuyItemNum, tempBuffer, 50, NULL );
		m_pStatic[9]->SetText(tempBuffer);

		g_JYLibFunction.SetNumUnit(m_siMyNcoin, tempBuffer, 50, NULL );
		m_pStatic[11]->SetText(tempBuffer);

		g_JYLibFunction.SetNumUnit(m_siMyNcoin - m_siSelectItemPrice*m_siBuyItemNum, tempBuffer, 50, NULL );
		m_pStatic[13]->SetText(tempBuffer);

		//[����] ���� �̺�Ʈ �ӴϷ� ���� �ݾ�
		g_JYLibFunction.SetNumUnit( m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50, NULL );
		m_pEventStatic[6]->SetText( tempBuffer );
		g_JYLibFunction.SetNumUnit( m_siMyEventNcoin, tempBuffer, 50,  NULL );
		m_pEventStatic[7]->SetText(tempBuffer);
		g_JYLibFunction.SetNumUnit( m_siMyEventNcoin - m_siSelectItemEventPrice * m_siBuyItemNum, tempBuffer, 50,  NULL );
		m_pEventStatic[8]->SetText( tempBuffer );
	}
}

void CNPresentWindowDlg::SetServerUniqueAndName()
{

}

// ����ڰ� ���� ���� �������� üũ�Ѵ�. ���� ������� ������ �ٷ� �޽����� ����.(�������̶��..)
BOOL   CNPresentWindowDlg::CheckSameServer(SI16 ServerUnique)
{


	return false;
}
TCHAR* CNPresentWindowDlg::GetSeverNameFromUnique(SI16 SeverUnique)
{

	return NULL;
}
SI16   CNPresentWindowDlg::GetSeverUniqueFromName(TCHAR* SeverName)
{

	return -1;
}


void CNPresentWindowDlg::Action()
{
	TCHAR buffer[128];
	TCHAR msg[ 256 ];
	SI32  maxSize = 200;

    
	MStrCpy( msg, m_pEdit[1]->GetText(), 256 );

	TCHAR* pText = GetTxtFromMgr(6123);
	SI32 len = _tcslen( msg );
	
	StringCchPrintf( buffer, 200, pText, len,maxSize );
	
	m_pStatic[28]->SetText(buffer);
	
	if(len > maxSize)
	{
		m_pStatic[28]->SetFontColor(RGB(225,50,50));
	}
	else
	{
		m_pStatic[28]->SetFontColor(RGB(0,0,0) );
	}
	
	m_pStatic[28]->Refresh();

}
void CNPresentWindowDlg::NHNChinaInit( void )
{
	bool bShow = false;
	if( pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) )	bShow = true;

	for( SI32 i = 0; i < 9; ++i )
	{
		m_pEventStatic[i]->Show( bShow );
	}

	m_pEventStaticBack->Show( bShow );
}

void CNPresentWindowDlg::NHNChinaItemSet( void )
{

}
