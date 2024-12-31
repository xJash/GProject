////---------------------------------
//// 2004/1/28 ���°�
////---------------------------------
//
//#include "GameContract.h"
//#include "..\..\Resource.h"
//#include "..\Client.h"
//
//#include "../Client/Interface/LoginClient/LoginClient.h"
//#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"
//
//#include "../../lib/WebHTML/WebHTML.h"
//
//#include "../Client/NInterface/NLogin/NLogin.h"
//#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
//
//extern cltCommonLogic* pclClient;
//
//cltGameContract::cltGameContract()
//{
//	m_hDlg				= NULL;
//	bDlgRectInitSwitch	= false;
//
//}
//
//cltGameContract::~cltGameContract()
//{
//	
//}
//
//
//BOOL cltGameContract::CreateDlg(HINSTANCE hinst, HWND hwnd)
//{
//	// ��ȭ���ڰ� ���� ���¶�� �����. 
//	if(!IsWindow(m_hDlg))
//	{
//
//		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG_GAMECONTRACT), hwnd, StaticDlgProc);
//
//		if(bDlgRectInitSwitch == true)
//		{
//			MoveWindow(m_hDlg, 
//				DlgRect.left, DlgRect.top, 
//				DlgRect.right - DlgRect.left, 
//				DlgRect.bottom - DlgRect.top, FALSE);
//		}
//
//		ShowWindow(m_hDlg, SW_SHOW);
//
//		return TRUE;
//	}
//	else
//	{
//		DestroyWindow(m_hDlg);
//	}
//
//
//	return 0;
//}
//
//BOOL CALLBACK cltGameContract::StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//
//	cltClient* pclclient = (cltClient*)pclClient;
//	return pclclient->pclGameContract->DlgProc(hDlg, iMsg, wParam, lParam);
//}
//
//
//BOOL CALLBACK cltGameContract::DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	SI32 id = 1;
//
//	switch(iMsg)
//	{
//	case WM_INITDIALOG:
//		{
//			SetTimer(hDlg, 1, 1000, NULL);
//
//			//SendMessage( GetDlgItem( hDlg, IDC_EDIT_REGISTRATION_NUMBER ), EM_LIMITTEXT, 7, 0 );
//
//			/*
//			if ( g_LoginClient.m_siCurrentSelectedSiteIndex == 2 )
//			{
//				ShowWindow( GetDlgItem( hDlg, IDC_STATIC_REGISTRATION_NUMBER ), SW_SHOW );
//				ShowWindow( GetDlgItem( hDlg, IDC_EDIT_REGISTRATION_NUMBER ), SW_SHOW );
//			}
//			else
//			{
//				ShowWindow( GetDlgItem( hDlg, IDC_STATIC_REGISTRATION_NUMBER ), SW_HIDE );
//				ShowWindow( GetDlgItem( hDlg, IDC_EDIT_REGISTRATION_NUMBER ), SW_HIDE );
//			}
//			*/
//
////			FILE* fp;
////			TCHAR buffer[1024];
////			TCHAR* ptext = NULL;
//
////			ptext = new TCHAR[1024 * 100];
//
////			_tcscpy(ptext , TEXT(""));
//			
//			TCHAR buffer[256] = TEXT("") ;
//			TCHAR GameContractFilePath[ 512 ] = TEXT("");
//			GetCurrentDirectory( 256, GameContractFilePath );
//
//			cltClient* pclclient = (cltClient*)pclClient;
//			
//			if(g_SoundOnOffDlg.m_bFullScreenMode)
//			{
//				// ȸ������ �������� �������ν� ������ 1(����)�� ����
//				StringCchPrintf( buffer, 256, TEXT("\\GameContract\\%dGameContract.htm"), 1 );
//			}
//            else
//				StringCchPrintf( buffer, 256, TEXT("\\GameContract\\%dGameContract.htm"), g_LoginClient.m_siCurrentSelectedSiteIndex+1 );
//							
////			sprintf( buffer, TEXT("\\GameContract\\%dGameContract.htm"), g_LoginClient.m_siCurrentSelectedSiteIndex );
//			StringCchCat(GameContractFilePath, 512, buffer);
//
//			HWND hWnd = GetDlgItem(hDlg,IDC_STATIC_GAMECONTRACT_HTML);
//			if ( hWnd )
//			{
//				EmbedBrowserObject(hWnd);
//				DisplayHTMLPage( hWnd, GameContractFilePath );
//			}
//
///*			fp = _tfopen( GameContractFilePath, TEXT("rt") );
//			if(fp)
//			{
//				while(_fgetts(buffer, 1024, fp) != NULL)
//				{
//					for(SI32 i = 0; i < lstrlen(buffer);i++)
//					{
//						if(buffer[i] == '\n')
//						{
//							buffer[i] = ' ';
//						}
//					}
//
//					strcat(ptext, buffer);
//					strcat(ptext, TEXT("\r\n"));
//				}
//
//				//------------------------------
//				// ����Ʈ �ڽ��� �߰��Ѵ�. 
//				//------------------------------
//				SetDlgItemText(hDlg, IDC_EDIT_GAMECONTRACT, ptext);
//				
//				if(ptext)
//				{
//					delete[] ptext;
//					ptext = NULL;
//				}
//				fclose(fp);
//			}*/
//
//		}
//		return TRUE;
//
//	case WM_NOTIFY:
//		return TRUE;
//
//	case WM_TIMER:
//		return TRUE;
//
//	case WM_COMMAND:
//		switch(LOWORD(wParam))
//		{
//		case IDOK:
//			{
//				//---------------------------------
//				// ����Ʈ ������ ��DB���� ������  ��û�Ѵ�.
//				//----------------------------------
//				cltClient* pclclient = (cltClient*)pclClient;
//				pclclient->RequestJoinGame();
//
//				
//
//				DestroyWindow(m_hDlg);
//
//			}
//			return TRUE;
//			
//		case IDCANCEL:
//			DestroyWindow(m_hDlg);
//			return TRUE;
//		}
//		return TRUE;
//		
//	case WM_DESTROY:
//
//		// Ÿ�̸Ӹ� �����Ѵ�. 
//		KillTimer(hDlg, 1);
//
//		HWND hwnd = GetDlgItem( hDlg, IDC_STATIC_GAMECONTRACT_HTML );
//		if( hwnd )
//		{
//			DoPageAction(hwnd, WEBPAGE_STOP);
//			UnEmbedBrowserObject(hwnd);
//		}
//
//		// �������� ��ġ�� ����Ѵ�. 
//		GetWindowRect(hDlg, &DlgRect);
//		bDlgRectInitSwitch = true;
//
//		m_hDlg = NULL;
//		return TRUE;
//
//	}
//
//	return FALSE;
//}
