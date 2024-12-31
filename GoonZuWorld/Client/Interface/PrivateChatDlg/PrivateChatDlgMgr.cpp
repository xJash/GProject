#include "PrivateChatDlgMgr.h"
#include "PrivateChatDlg.h"
#include "../ChatDlg/ChatDataMgr.h"

#include <CommonLogic.h>

#include "../../../lib/WebHTML/WebHTML.h"

#include "Char\CharCommon\Char-Common.h"

// �弳 ����
#include "../../Client/AbuseFilter/AbuseFilter.h"

#include "../../Client/client.h"
#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
extern	cltCommonLogic	*pclClient;

CPrivateChatDlgMgr::CPrivateChatDlgMgr()
{	
	for ( SI32 i = 0; i < MAX_REJECT_USER_NUM; ++i )
	{
		m_strRejectUserList[ i ][0] = NULL;
	}

	for ( i = 0 ; i < MAX_PRIVATE_CHAT_DLG_NUM ; i ++ )
	{
		m_hWhisperProfile[i] = NULL ;
	}

	ReadRejectUser();

	Initialize();
}

CPrivateChatDlgMgr::~CPrivateChatDlgMgr()
{
	Destroy();
	WriteRejectUser();
}

void CPrivateChatDlgMgr::Initialize()
{
	m_uiCurrentPrivateChatDlgNum = 0;

	return;
}

void CPrivateChatDlgMgr::Destroy()
{

	return;
}

void CPrivateChatDlgMgr::Create( HWND hWnd, HINSTANCE hInst )
{
	for ( SI32 i = 0; i < MAX_PRIVATE_CHAT_DLG_NUM; ++i )
	{
		g_PrivateChatDlg[ i ].Create( hWnd, hInst, this, i );
	}

	return;
}

SI32 CPrivateChatDlgMgr::Push( SI32 siCharUnique, char *strWhisperData )
{
	return 0;
}

SI32 CPrivateChatDlgMgr::Push( SI32 siCharUnique, char *strUserName, char *strWhisperData ,SI32 level ,char * szAccountID)
{
	cltClient *pclclient = (cltClient *)pclClient;
	
	if( pclclient->bWatchModeSwitch )
	{
		return PRIVATE_CHAT_FAIL;
	}

	SI32 siFromID = cltCharCommon::CharUniqueInfo[siCharUnique];

	// �ӼӸ� â ������ ������ ��� �׳� ���� ����
	if ( m_uiCurrentPrivateChatDlgNum > MAX_PRIVATE_CHAT_DLG_NUM )
	{
		return PRIVATE_CHAT_EXCESS_CHAT_DLG_NUM;
	}

	if ( IsRejectUser( strUserName ) )
	{
		g_PrivateChatDlg[ 0 ].m_pChatDataSendMgr->PushReject( WHISPER_CHAT_REJECT, siCharUnique );
		return PRIVATE_CHAT_FAIL;
	}

	// ���� �ӼӸ� â�߿��� �� ���̵�� �̾߱� �ϴ°� �ִ� ��� ( â�� hide �� ��쵵 üũ��. )
	for ( SI32 i = 0; i < MAX_PRIVATE_CHAT_DLG_NUM; ++i )
	{
		if ( g_PrivateChatDlg[ i ].IsExist( siCharUnique, strUserName ) )
		{
/*			if (szAccountID != NULL && strlen(szAccountID) > 0 )
			{
				m_hWhisperProfile[i] = GetDlgItem(g_PrivateChatDlg[i].m_hDlg[i],IDC_STATIC_PRIVATEPROFILE);

				char ProfileURL[256];

				pclClient->GetCZProfileUrl( ProfileURL, szAccountID );

				DisplayHTMLPage(m_hWhisperProfile[i], ProfileURL);
			}*/

			if ( strWhisperData == NULL )
			{
				return PRIVATE_CHAT_FAIL;
			}

			if ( g_PrivateChatDlg[ i ].m_strUserName != NULL )
			{
				if ( strUserName != NULL && strcmp( strUserName, g_PrivateChatDlg[ i ].m_strUserName ) != 0 )
				{
					char buffer[256] = "" ;
					MStrCpy( g_PrivateChatDlg[ i ].m_strUserName, strUserName, MAX_PLAYER_NAME );
					sprintf(buffer,"%s ( Lv.%d )",strUserName,level);
					SetWindowText( g_PrivateChatDlg[ i ].m_hDlg[ i ], buffer );
				}
			}

			if ( strlen( strWhisperData ) > 0 )
			{
				if ( GetForegroundWindow() != g_PrivateChatDlg[ i ].m_hDlg[ i ] )
				{
					if ( ! g_PrivateChatDlg[ i ].m_bTimerStatus[ i ] )
					{
						SetTimer( g_PrivateChatDlg[ i ].m_hDlg[ i ], 0, 500, NULL );
					}
				}					

				g_PrivateChatDlg[ i ].Recv( strUserName, strWhisperData );
			}

			g_PrivateChatDlg[ i ].Show();

			return PRIVATE_CHAT_SUCCESS;
		}
	}

	// ���� �ͼӸ� â �߿��� �� ���̵�� �̾߱� �ϴ°� ���� ���
	for ( i = 0; i < MAX_PRIVATE_CHAT_DLG_NUM; ++i )
	{
		if ( ! g_PrivateChatDlg[ i ].IsShow() )			// â�� hide �Ǿ� �ִ� ���
		{
/*			if (szAccountID != NULL && strlen(szAccountID) > 0 )
			{
				m_hWhisperProfile[i] = GetDlgItem(g_PrivateChatDlg[i].m_hDlg[i],IDC_STATIC_PRIVATEPROFILE);

				char ProfileURL[256]; 
				pclClient->GetCZProfileUrl( ProfileURL, szAccountID );

				DisplayHTMLPage(m_hWhisperProfile[i], ProfileURL);
			}*/

			if ( szAccountID == NULL )
			{
				cltClient *pclclient = (cltClient*)pclClient;
				pclclient->RequestSecretChatByCharUnique(siCharUnique,strWhisperData);
				return PRIVATE_CHAT_FAIL;
			}

			g_PrivateChatDlg[ i ].Initialize();			// â�� ������ �ʱ�ȭ
			g_PrivateChatDlg[ i ].Set( siCharUnique, strUserName,level );

			//g_PrivateChatDlg[ i ].Recv("������","�ֱ� ��� ��Ī�� ���� ���ذ� �ð� �ֽ��ϴ�. '����', '���' �̻� 2���� ĳ���͸��� ���� ����̿��� �����Ͻñ� �ٶ��ϴ�.");

			if ( strWhisperData != NULL )
			{
				if ( strlen( strWhisperData ) > 0 )
				{
					g_PrivateChatDlg[ i ].Recv( strUserName, strWhisperData );

					if ( GetForegroundWindow() != g_PrivateChatDlg[ i ].m_hDlg[ i ] )
					{
						if ( ! g_PrivateChatDlg[ i ].m_bTimerStatus[ i ] )
						{
							SetTimer( g_PrivateChatDlg[ i ].m_hDlg[ i ], 0, 500, NULL );
						}
					}					
				}
			}

			g_PrivateChatDlg[ i ].Show();

			return PRIVATE_CHAT_SUCCESS;
		}
	}

	return PRIVATE_CHAT_FAIL;
}

// �� �Լ��� �� �����ӿ� ������ ȣ��ɼ� �ִ�. ���� �� �����ӵ��� 2�� �̻󿡰� ���ÿ� �ӼӸ��� �������� �����Ƿ�..
bool CPrivateChatDlgMgr::Pop( stWhisperChatDataSend *pWhisperChatDataSend )
{
	for ( SI32 i = 0; i < MAX_PRIVATE_CHAT_DLG_NUM; ++i )
	{
		if ( g_PrivateChatDlg[ i ].Pop( pWhisperChatDataSend ) )
		{
			return true;
		}
	}

	return false;
}

void CPrivateChatDlgMgr::ReadRejectUser()
{
	/*
	FILE *fp = fopen( "Config/RejectUser.dat", "rt" );

	if ( fp == NULL )
	{
		return;
	}

	m_siRejectUserNum = 0;

	while( ! feof( fp ) )
	{
		fscanf( fp, "%s", m_strRejectUserList[ m_siRejectUserNum++ ] );
	}

	fclose( fp );
	*/
	return;
}

void CPrivateChatDlgMgr::WriteRejectUser()
{
	/*
	FILE *fp = fopen( "Config/RejectUser.dat", "wt" );

	if ( fp == NULL )
	{
		return;
	}

	SI32 siCount = 0;

	while( siCount < MAX_REJECT_USER_NUM )
	{
		if ( m_strRejectUserList[ siCount ][ 0 ] != NULL )
		{
			fprintf( fp, "%s\n", m_strRejectUserList[ siCount ] );
		}

		++siCount;
	}

	fclose( fp );
	*/

	return;
}

void CPrivateChatDlgMgr::AddRejectUser( char *strNickName )
{	
	for ( SI32 i = 0; i < MAX_REJECT_USER_NUM; ++i )
	{
		if ( m_strRejectUserList[ i ][ 0 ] != NULL )
		{
			if ( strcmp( m_strRejectUserList[ i ], strNickName ) == 0 )
			{
				return;
			}			
		}		
	}
	

	for ( i = 0; i < MAX_REJECT_USER_NUM; ++i )
	{
		if ( m_strRejectUserList[ i ][ 0 ] == NULL )
		{
			MStrCpy( m_strRejectUserList[ i ], strNickName, MAX_PLAYER_NAME );
			return;
		}		
	}

	return;
}

void CPrivateChatDlgMgr::DelRejectUser( char *strNickName )
{
	for ( SI32 i = 0; i < MAX_REJECT_USER_NUM; ++i )
	{
		if ( m_strRejectUserList[ i ][ 0 ] != NULL )
		{			
			if ( strcmp( m_strRejectUserList[ i ], strNickName ) == 0 )
			{
				m_strRejectUserList[ i ][ 0 ] = NULL;
			}
		}
	}

	return;
}

bool CPrivateChatDlgMgr::IsRejectUser( char *strNickName )
{
	for ( SI32 i = 0; i < MAX_REJECT_USER_NUM; ++i )
	{
		if ( m_strRejectUserList[ i ][ 0 ] != NULL )
		{			
			if ( strcmp( m_strRejectUserList[ i ], strNickName ) == 0 )
			{
				return true;
			}
		}
	}

	return false;
}
