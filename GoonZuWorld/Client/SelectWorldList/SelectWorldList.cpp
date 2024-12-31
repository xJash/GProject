//---------------------------------
// 2003/7/29 �̻��
//---------------------------------
#include "..\Client.h"
#include "..\..\resource.h"

#include "../../lib/WebHTML/WebHTML.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../Client/NInterface/NSelectWorldListDlg/SelectWorldListDlg.h"

extern cltCommonLogic* pclClient;

#define TESTSERVER_ID		11

// ������ ���尡  ���õǾ����� Ȯ���Ѵ�. 
bool cltClient::SelectWorldList()
{
	if( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if( ((CNSelectWorldListDlg*)m_pDialog[ NSELECTWORLDLIST_DLG ])->IsShow() == false)
		{
			return true;
		}
	}
	else
	{
		if( SelectWorldListDlg == NULL )
		{
			return true;
		}
	}
	
//	if( SelectWorldListDlg == NULL )
//	{
//		return true;
//	}

	return false;
}



bool cltClient::CreateSelectWorldListDlg(bool bShowBanner)
{
	// Ŭ���̾�Ʈ�� ��쿡�� ó���Ѵ�.(�ʿ����Ϳ����� ������� �ʴ´�. ) 
	if( GameMode != GAMEMODE_CLIENT )
	{
		return true;
	}

	if( clWorldList.GetCount() == 0 )
	{
		return false;
	}

	// 0�� ������ ������ ���´�. 
	//clWorldList.GetWorldInfo( 1, &clSelectedWorldInfo );

	//	CreateInterface( NSELECTWORLDLIST_DLG );

	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if(m_pDialog[ NSELECTWORLDLIST_DLG ] && ((CNSelectWorldListDlg*)m_pDialog[ NSELECTWORLDLIST_DLG ])->IsShow() == false)
		{
			((CNSelectWorldListDlg*)m_pDialog[ NSELECTWORLDLIST_DLG ])->Show();

			// ��ʸ� �����ش�
			if(bShowBanner)				
				CreateInterface( NOPENINGBANNER_DLG );

			return true;
		}
	}
	
	// ��ȭ���ڰ� ���� ���¶�� �����. 
/*	if( ! IsWindow( SelectWorldListDlg ) )
	{
		SelectWorldListDlg = CreateDialog( GetInstance(), MAKEINTRESOURCE( IDD_DIALOG_SELECTWORLDLIST ), GetHwnd(), (DLGPROC)StaticSelectWorldListDlgProc );
		
		ShowWindow(SelectWorldListDlg, SW_SHOW);
		return true;
	}
*/

	return false;
}


