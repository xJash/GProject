//---------------------------------
// 2004/10/27 ���°�
//---------------------------------

//-----------------------------
// CommonLogic
//-----------------------------
#include "MsgType-Person.h"
#include "Msg\MsgType-Horse.h"

//-------------------------
// Common
//------------------------
#include "CharStatus.h"
#include "PersonInfo.h"
#include "JWLib\IsCorrectID\IsCorrectID.h"
#include "HintDlg/HintDlg.h"
#include "Char\CharManager\CharManager.h"

//------------------------
// CLient
//------------------------
#include "Client.h"
#include "Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "Interface/PrivateTradeDlg/PrivateTradeDlg.h"
#include "NInterface/NHintDlg/NHintDlg.h"


extern cltCommonLogic* pclClient;

BOOL CALLBACK cltCharStatus::CharStatusHorseStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;

	return pclclient->pclCharStatus->CharStatusHorseProc(hDlg, iMsg, wParam, lParam);
}


BOOL CALLBACK cltCharStatus::CharStatusHorseProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//SI32 i;
	cltClient* pclclient = (cltClient*)pclClient;

	cltHorse* pclhorse = pclCM->CR[1]->pclCI->clHorseInfo.GetCurrentShowHorse();

	switch(iMsg)
	{
	case WM_INITDIALOG:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetTimer(hDlg, 1, 1000, NULL);

		BonusHorseButtonEnableSwitch = FALSE ;

		if ( pclhorse->szName != NULL && strlen ( pclhorse->szName ) > 0 )
		{
			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSENAME ), pclhorse->szName );
		}
		
		UpdateHorseStatusInfo(hDlg);
		

		
		//==========================================
		// �ʻ�ȭ 
		//==========================================
		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hHorsePortraitBitmap)	{	DeleteObject(m_hHorsePortraitBitmap);	m_hHorsePortraitBitmap = NULL;	}

		if(pclhorse->siHorseUnique)
		{
			char strFileName[ 128 ] = "";
			char strPathFileName[ 128 ] = "";
			switch(pclhorse->siHorseUnique)
			{
			case 1:	strcpy(strFileName, "BROWN_HORSE");	break;
			case 2:	strcpy(strFileName, "BLACK_HORSE"); break;
			case 3:	strcpy(strFileName, "WHITE_HORSE"); break;
			case 4:	strcpy(strFileName, "RED_HORSE");	break;
			case 5: strcpy(strFileName, "ZEBRA_HORSE"); break;
			case 6: strcpy(strFileName, "RUDOLF"); break;
			case 7: strcpy(strFileName,	"THOUSAND_HORSE"); break;
			case 8: strcpy(strFileName, "IRON_HORSE"); break;
			case 9: strcpy(strFileName, "TIGER"); break;
			default:strcpy(strFileName, "BROWN_HORSE");	break;
			}
			sprintf( strPathFileName, "Interface/Portrait/%s.bmp",	strFileName );
			m_hHorsePortraitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), strPathFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		}
		if ( m_hHorsePortraitBitmap != NULL )
		{
			SendDlgItemMessage( hDlg, IDC_STATIC_HORSE_PORTRAIT, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorsePortraitBitmap );
		}
		
		//==========================================
		// HORSE HINT
		//==========================================
		m_hHorseHintHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "StatusHint\\HorseExplainHint.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		
		if ( m_hHorseHintHitBitmap != NULL )
		{
			SendDlgItemMessage( hDlg, IDC_BUTTON_HORSE_EXPLAIN, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorseHintHitBitmap);
		}

		//---------------------------------------------
		// HORSE INIT
		//-----------------------------
		m_hHorseInitHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/HorseInit.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		if ( m_hHorseInitHitBitmap != NULL )
		{
			SendDlgItemMessage( hDlg, IDC_BUTTON_HORSE_INIT, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorseInitHitBitmap);
		}

		//---------------------------------------------
		// HORSE ADD STATUS
		//-----------------------------
		m_hHorseAddStatusHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/HorseAddStatus.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		if ( m_hHorseAddStatusHitBitmap != NULL )
		{
			SendDlgItemMessage( hDlg, IDC_BUTTON_HORSE_ADDSTATUS, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorseAddStatusHitBitmap);
		}

		//---------------------------------
		// HORSE TYPE
		//---------------------------------
		m_hHorseTypeHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/HorseChange.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		if ( m_hHorseTypeHitBitmap != NULL )
		{
			SendDlgItemMessage( hDlg, IDC_BUTTON_CHANGETYPE, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHorseTypeHitBitmap);
		}

		return TRUE;
	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			SetTextColor( hdc, COLOR_DIALOG_BLACK);
			SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE );
								
			return (BOOL)m_hDlgBrush;
		}
		break;
	case WM_CTLCOLOREDIT:
		{
			if(GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSENAME ) == (HWND)lParam)	
			{
				HDC hdc = (HDC)wParam;
				SetBkColor( hdc, COLOR_DIALOG_WHITE);				
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				
				return (BOOL)m_hEditBrush;
			}
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_HORSE_SPEED ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_HORSE_STR ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_HORSE_DEX ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_HORSE_MAG ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSE_NEED) == (HWND)lParam
				)
			{
				HDC hdc = (HDC)wParam;
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);				
				SetTextColor( hdc, COLOR_DIALOG_BLACK );

				return (BOOL)m_hStaticBrush;
			}
			else
			{
				HDC hdc = (HDC)wParam;
				SetBkMode(hdc,TRANSPARENT);
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				return (BOOL)m_hDlgBrush;
			}
			
		}
		break;
	case WM_TIMER:
		UpdateHorseStatusInfo(hDlg);
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hHorsePortraitBitmap)
		{
			DeleteObject(m_hHorsePortraitBitmap);
			m_hHorsePortraitBitmap= NULL;
		}
		
		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_COMMAND:
		cltClient *pclclient = (cltClient *)pclClient;
		switch(wParam)
		{
		case IDC_CHECK_AUTOFOOD:
			{
				HWND hcheck = GetDlgItem( hDlg, IDC_CHECK_AUTOFOOD);

				cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_AUTOFOOD, true);
				cltGameMsgRequest_StatusInfo clinfo(&clchangeinfo);
				if(SendMessage(hcheck , BM_GETCHECK, 0, 0 ) == BST_UNCHECKED )
				{
					clinfo.ChangeInfo.bChangeSwitch = true;
					
				}
				else
				{
					clinfo.ChangeInfo.bChangeSwitch = false;
				}

				// ������ ���� ������ ������. 
				cltMsg clMsg( GAMEMSG_REQUEST_CHANGESTATUSINFO, sizeof(clinfo), (char*)&clinfo);
				pclclient->SendMsgToServer((char*)&clMsg);

				InvalidateRect(hDlg, NULL, TRUE);

			}
			break;
		case IDC_BUTTON_STATUS_CHANGENAME:
			{
				char ChangeHorseName[ MAX_HORSE_NAME ] = "";
				if ( GetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSENAME ), ChangeHorseName, MAX_HORSE_NAME - 1 ) == 0 )
				{
					return FALSE;			
				}

				if ( pclhorse->szName != NULL && strlen( pclhorse->szName ) > 0 && strcmp( pclhorse->szName, ChangeHorseName ) == 0 )
				{
					char* pTitle = GetTxtFromMgr(569);
					char* pText = GetTxtFromMgr(570);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
					return FALSE;
				}

				if ( IsCorrectID( ChangeHorseName ) == FALSE )
				{
					char* pTitle = GetTxtFromMgr(571);
					char* pText = GetTxtFromMgr(572);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
					return FALSE;
				}
				
				cltGameMsgRequest_HorseNameChange clinfo( 0, ChangeHorseName );
				cltMsg clMsg( GAMEMSG_REQUEST_HORSENAMECHANGE, sizeof(clinfo), (char*)&clinfo);
				pclclient->SendMsgToServer((char*)&clMsg);

			}
			break;
		case IDC_BUTTON_RIDEHORSE:
			{	
				cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
				
				// ���� ������ ���� �¿��. 
				if(pclChar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false)
				{
					if(pclhorse->siHorseUnique)
					{	
						if(pclChar->pclCI->clHorseInfo.CanRide(0, &pclclient->clClientDate) == true)
						{
							// �ŷ� ���̶�� Ż �� ����.
							if ( g_PrivateTradeDlg.IsShow() )
							{
								char* pTitle = GetTxtFromMgr(573);
								char* pText = GetTxtFromMgr(574);
								pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							}
							else
							{
								cltGameMsgRequest_RideOrUnrideHorse clinfo(0);
								cltMsg clMsg(GAMEMSG_REQUEST_RIDEHORSE, sizeof(clinfo), (char*)&clinfo);
								pclclient->SendMsgToServer((char*)&clMsg);
							}
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					cltMsg clMsg(GAMEMSG_REQUEST_UNRIDEHORSE, 0, NULL);
					pclclient->SendMsgToServer((char*)&clMsg);
				}
				
			}
			return TRUE;

		case IDC_BUTTON_HORSE_FREE:
			{
				SI32 id = 1;
				if(pclCM->IsAlive(id) == false)return TRUE;

				// ���� ������ ����. 
				if(pclhorse->siHorseUnique <= 0)
				{
					char* pTitle = GetTxtFromMgr(575);
					char* pText = GetTxtFromMgr(576);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					return TRUE;
				}
	
				char* pTitle = GetTxtFromMgr(578);
				char* pText = GetTxtFromMgr(577);

				if(MessageBox(hDlg, pText, pTitle, MB_TOPMOST|MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2) == IDYES)
				{
					//KHY - 1001 - ��µ��� 5���� ���� ����.
					// ���� Ÿ�� ������ ����. 
					//if(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseIndex >= 0)
					if(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
					{
						pTitle = GetTxtFromMgr(575);
						pText = GetTxtFromMgr(579);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return TRUE;
					}
					
					// �� �κ��� ��ǰ�� ������ Ǯ���� �� ����. 
					if(pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() == true)
					{
						pTitle = GetTxtFromMgr(575);
						pText = GetTxtFromMgr(580);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return TRUE;
					}
															
					cltMsg clMsg(GAMEMSG_REQUEST_HORSEFREE, 0, NULL);
					pclclient->SendMsgToServer((char*)&clMsg);
					
				}
			}
			return TRUE;
		case IDC_BUTTON_HORSE_EXPLAIN:
			{

				//pclclient->m_pHintDlg->Show("horsebreed");
					
				if((pclclient->m_pDialog[ NHINT_DLG ])==NULL)
				{
					pclclient->CreateInterface( NHINT_DLG );
				}
					((NHintDlgExplain*)pclclient->m_pDialog[ NHINT_DLG])->Show("horsebreed");

			}
			return TRUE;
		case IDC_BUTTON_HORSE_ADDSTATUS:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				char buffer[256] = "" ;

				if ( pclhorse->siHorseUnique <= 0 )
				{
					char* pTitle = GetTxtFromMgr(3170);
					char* pText = GetTxtFromMgr(581);

					sprintf(buffer, pText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE ;
				}

				SI32 itemunique = 14140 ;  // ���ɷ�����̿��
				if ( pclclient->pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(3170);
					char* pText = GetTxtFromMgr(3171);

					sprintf(buffer,pText);
					//MsgBox("���� �ʱ�ȭ", buffer);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE;
				}

				char* pTitle = GetTxtFromMgr(3170);
				char* pText = GetTxtFromMgr(3172);

				sprintf(buffer, pText);
				if (  MessageBox(NULL, buffer,pTitle,
					MB_ICONQUESTION | MB_YESNO) == IDNO )
				{
					return TRUE;
				}

				cltMsg clMsg(GAMEMSG_REQUEST_HORSE_ADDSTATUS,0);
				pclClient->SendMsgToServer((char*)&clMsg);
			}
			return TRUE;
		case IDC_BUTTON_HORSE_INIT:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				char buffer[256] = "" ;

				if ( pclhorse->siHorseUnique <= 0 )
				{
					char* pTitle = GetTxtFromMgr(582);
					char* pText = GetTxtFromMgr(581);

					sprintf(buffer, pText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE ;
				}

				SI32 itemunique = 14070 ;  // �������ʱ�ȭ�̿��
				if ( pclclient->pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(582);
					char* pText = GetTxtFromMgr(583);

					sprintf(buffer,pText);
					//MsgBox("���� �ʱ�ȭ", buffer);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE;
				}

				char* pTitle = GetTxtFromMgr(582);
				char* pText = GetTxtFromMgr(584);

				sprintf(buffer, pText);
				if (  MessageBox(NULL, buffer,pTitle,
					MB_ICONQUESTION | MB_YESNO) == IDNO )
				{
					return TRUE;
				}

				cltMsg clMsg(GAMEMSG_REQUEST_HORSEINIT,0);
				pclClient->SendMsgToServer((char*)&clMsg);
			}
			return TRUE ;
		case IDC_BUTTON_HORSE_SPEED:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if( !id ) return TRUE ;

				if(pclhorse->siMoveSpeed >= pclClient->pclHorseManager->GetFullSpeed( pclhorse->siHorseUnique) )
				{
					char buffer[256] = "" ;
					char* pTitle = GetTxtFromMgr(586);
					char* pText = GetTxtFromMgr(585);
					sprintf(buffer,pText, 
						pclClient->pclHorseManager->GetFullSpeed( pclhorse->siHorseUnique)/100);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
					return TRUE;
				}

				SendUseHorseBonusMessageToServer(0);
			}
			return TRUE;
		case IDC_BUTTON_HORSE_STR:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				if(pclhorse->siStr >= pclClient->pclHorseManager->GetFullStr( pclhorse->siHorseUnique)  )
				{
					char buffer[256] = "" ;
					char* pTitle = GetTxtFromMgr(588);
					char* pText = GetTxtFromMgr(587);
					sprintf(buffer,pText, 
						pclClient->pclHorseManager->GetFullStr( pclhorse->siHorseUnique) / 100);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
					return TRUE;
				}

				SendUseHorseBonusMessageToServer(1);
			}
			return TRUE;
		case IDC_BUTTON_HORSE_DEX:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				if(pclhorse->siDex >= pclClient->pclHorseManager->GetFullDex( pclhorse->siHorseUnique) )
				{
					char buffer[256] = "" ;
					char* pTitle = GetTxtFromMgr(590);
					char* pText = GetTxtFromMgr(589);
					sprintf(buffer,pText, 
						pclClient->pclHorseManager->GetFullDex( pclhorse->siHorseUnique)/100);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
					return TRUE;
				}

				SendUseHorseBonusMessageToServer(2);
			}
			return TRUE;
		case IDC_BUTTON_HORSE_MAG:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				if(pclhorse->siMag >= pclClient->pclHorseManager->GetFullMag( pclhorse->siHorseUnique) )
				{
					char buffer[256] = "" ;
					char* pTitle = GetTxtFromMgr(592);
					char* pText = GetTxtFromMgr(591);
					sprintf(buffer,pText, 
						pclClient->pclHorseManager->GetFullMag( pclhorse->siHorseUnique)/100);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);
					return TRUE;
				}

				SendUseHorseBonusMessageToServer(3);
			}
			return TRUE;
		case IDC_BUTTON_CHANGETYPE:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if ( !id ) return TRUE ;

				SI16 horseunique = pclhorse->siHorseUnique ;

				char buffer[256] = "" ;

				if ( horseunique <= 0 )
				{
					char* pTitle = GetTxtFromMgr(593);
					char* pText = GetTxtFromMgr(581);
					sprintf(buffer, pText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE ;
				}

				if ( !pclHorseTypeChange->CreateDlg(pclClient->GetInstance(), pclClient->GetHwnd(),horseunique) )
					pclHorseTypeChange->Close();
			}
			return TRUE;
		case IDOK:
			return TRUE;

		case IDCANCEL:
			return TRUE;
			
		}
		return TRUE;
	}
	return FALSE;

}

// ���� ���¸� ������Ʈ �Ѵ�.
void cltCharStatus::UpdateHorseStatusInfo(HWND hDlg)
{
	HWND hwnd;
	char buffer[256];

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}
	cltHorse* pclhorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();

	if(pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	// �� �̸� ����
	if( pclhorse->szName == NULL || strlen( pclhorse->szName ) < 1 )
	{
		return;
	}

	// �� ������ ó�� ���� ���
	if ( strHorseName != NULL && strlen ( strHorseName) == 0 )
	{
		strcpy( strHorseName, pclhorse->szName );
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSENAME ), pclhorse->szName );
	}
	
	// �����κ��� �̸��� �ٲ���ٰ� �뺸�� �� ���
	if ( strHorseName != NULL && strlen ( strHorseName) > 0 && strcmp( strHorseName, pclhorse->szName ) != 0 )
	{
		strcpy( strHorseName, pclhorse->szName );
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_HORSENAME ), pclhorse->szName );
	}


	// ǰ�� ǥ�� 
	SI32 horseunique = pclhorse->siHorseUnique;
	if(horseunique)
	{
		hwnd = GetDlgItem(hDlg, IDC_STATIC_HORSEKIND); 
		SetWindowText(hwnd, pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies);
	}
	
	// ���� ����. 
	if(pclhorse->clBirthDate.GetDateText(buffer) == TRUE)
	{
		hwnd = GetDlgItem(hDlg, IDC_STATIC_HORSE_BIRTHDAT); 
		SetWindowText(hwnd, buffer);
	}

	// ���� ����. 
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 age = pclhorse->GetAge(pclclient->clClientDate.GetDateVary());

	char* pText = GetTxtFromMgr(594);
	sprintf(buffer, pText, age);
	hwnd = GetDlgItem(hDlg, IDC_STATIC_HORSE_AGE); 
	SetWindowText(hwnd, buffer);

	// ���� ���� ����. 
	SI32 life = pclclient->pclHorseManager->GetLife(pclhorse, pclclient->clClientDate.GetDateVary());
	pText = GetTxtFromMgr(595);
	sprintf(buffer, pText, life, pclclient->pclHorseManager->GetFullLife(pclhorse->siHorseUnique));
	hwnd = GetDlgItem(hDlg, IDC_STATIC_HORSE_LIFE); 
	SetWindowText(hwnd, buffer);

	// ���� ����. 
	if(pclhorse->siSex == ANIMAL_MALE)
	{
		pText = GetTxtFromMgr(596);
		sprintf(buffer, pText);
	}
	else
	{
		pText = GetTxtFromMgr(597);
		sprintf(buffer, pText);
	}
	hwnd = GetDlgItem(hDlg, IDC_STATIC_HORSE_SEX); 
	SetWindowText(hwnd, buffer);

	// �ڵ� �Ա� ��� üũ. 
	HWND hcheck = GetDlgItem( hDlg, IDC_CHECK_AUTOFOOD);
	if(pclCM->CR[id]->pclCI->clHorseInfo.bAutoFoodSwitch)
	{
		if(SendMessage(hcheck , BM_GETCHECK, 0, 0 ) == BST_UNCHECKED )
		{
			SendMessage( hcheck, BM_SETCHECK, BST_CHECKED, 0 );
		}
		
	}
	else
	{
		if(SendMessage(hcheck , BM_GETCHECK, 0, 0 ) == BST_CHECKED )
		{
			SendMessage( hcheck, BM_SETCHECK, BST_UNCHECKED, 0 );
		}
	}

	// �ٷ� 
	SI32 addstatus = 0 ;
	if ( pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclhorse) > 0 && pclhorse->siStatusTicketNum > 0 &&
		 pclclient->clClientDate.GetDateVary() < pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclhorse) )
		 addstatus += MAX_HORSE_ADDSTATUS ;

	sprintf(buffer, "%3.2f/%3.2f", (float)pclhorse->siStr/100.0 + addstatus , 
		pclClient->pclHorseManager->GetFullStr(pclhorse->siHorseUnique) / 100.0+ addstatus);
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HORSE_STR); 
	SetWindowText(hwnd, buffer);

	// ���߷�  
	sprintf(buffer, "%3.2f/%3.2f", (float)pclhorse->siDex/100.0 + addstatus, 
		pclClient->pclHorseManager->GetFullDex(pclhorse->siHorseUnique) / 100.0+ addstatus);
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HORSE_DEX); 
	SetWindowText(hwnd, buffer);
	
	// ����  
	sprintf(buffer, "%3.2f/%3.2f", (float)pclhorse->siMag/100.0 + addstatus, 
		pclClient->pclHorseManager->GetFullMag(pclhorse->siHorseUnique) / 100.0+ addstatus);
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HORSE_MAG); 
	SetWindowText(hwnd, buffer);
	
	
	// �ӵ�. 
	sprintf(buffer, "%3.2f/%3.2f", (float)pclhorse->siMoveSpeed/100.0, 
		pclClient->pclHorseManager->GetFullSpeed(pclhorse->siHorseUnique) / 100.0);
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HORSE_SPEED); 
	SetWindowText(hwnd, buffer);


	// ���ʽ�.
	sprintf(buffer, "%d", pclhorse->siStatusBonus);
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HORSE_BONUS); 
	SetWindowText(hwnd, buffer);

	// ���� �߰��ɷ��� ���ѳ��ڶ� �䱸������ ǥ���Ѵ�.
	char text[1024]="";
	pclClient->pclHorseManager->GetAddStatusLimitDateText(pclhorse,text);

	if(pclhorse->siNeed)
	{
		pclClient->pclHorseManager->GetNeedText(pclhorse, text);
	}
	hwnd = GetDlgItem(hDlg, IDC_EDIT_STATUS_HORSE_NEED); 
	SetWindowText(hwnd, text);

	SI32 ButtonDlg[] = {
		IDC_BUTTON_HORSE_SPEED,
		IDC_BUTTON_HORSE_STR, 
		IDC_BUTTON_HORSE_DEX,
		IDC_BUTTON_HORSE_MAG,
		-1
	};

	SI32 index = 0 ;
	// ���ʽ� ��ġ ������ ��ư�� �����Ѵ�. 
	if( pclhorse->siStatusBonus > 0 )
	{
		if(BonusHorseButtonEnableSwitch == FALSE)
		{
			BonusHorseButtonEnableSwitch = TRUE;

			index = 0;
			while(ButtonDlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
				EnableWindow(hwnd, TRUE);

				index++;
			}
		}
	}
	else
	{
		if(BonusHorseButtonEnableSwitch == TRUE)
		{
			BonusHorseButtonEnableSwitch = FALSE;

			index = 0;
			while(ButtonDlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
				EnableWindow(hwnd, FALSE);

				index++;
			}
		}
	}
}
