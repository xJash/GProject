//---------------------------------
// 2007/09/04 �豤��
//---------------------------------

#include "Client.h"
#include "Music\Music.h"
#include "..\CommonLogic\MsgType.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "../Resource.h"
#include "Char\CharManager\CharManager.h"
#include "MsgType-Item.h"

#include "MsgType-System.h"
#include "Msg\MsgType-Web.h"
#include "Msg\MsgType-Village.h"
#include "Msg\MsgType-Quest.h"
#include "..\CommonLogic\MsgType-Person.h"
#include "StatusBar\StatusBar.h"


#include "Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Interface\NotifyMsgDlg\NotifyMsgDlg.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_KINGGURIINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_KingGuriInfo* pclinfo = (cltGameMsgResponse_KingGuriInfo*)pclMsg->cData;

	if( CKingGuriEvent::START == pclinfo->siCmd )
	{
		TCHAR* text = GetTxtFromMgr( 10195 );
		pclMessage->SetMsg( text, 0, RGB(255, 255, 0)  );

		text = GetTxtFromMgr( 10192 );
		TCHAR buffer[256] = {'\0'};
		TCHAR AreaName[64] = {'\0'};

		POINT pos;
		for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
		{
			if(AreaName == NULL )	continue	;
			StringCchCopy( AreaName, 64, pclinfo->szAreaNmae[i] );
			if(strlen(AreaName)<=0)	continue	;
			Nsprintf( buffer, text, TEXT("areaname"), AreaName, NULL );

			//[�߰� : Ȳ���� 2007. 11. 13 ��� ������ �̺�Ʈ �˸� ����� ���ڷ� ���̰� ��ǥ.]
			if(pclClient->IsCountrySwitch( Switch_RaccoonEvent_Change_Goonzu ))
			{
				pos = pclinfo->m_ptPosition[i];
			}
			else
			{
				pos = pclinfo->m_ptPosition[pclinfo->m_siAreaIndex[i]];
			}
			StringCchPrintf( &buffer[strlen(buffer)], sizeof(buffer) - strlen(buffer)  ,"(%d, %d)", pos.x, pos.y );

			//pclMessage->SetMsg( buffer );
			pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0) );
		}
	}
	else if( CKingGuriEvent::ACTION == pclinfo->siCmd )
	{
		TCHAR* text = GetTxtFromMgr( 10192 );
		TCHAR buffer[256] = {'\0'};
		TCHAR AreaName[64] = {'\0'};

		POINT pos;
		for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
		{
			if(AreaName == NULL )	continue	;
			//[�߰� : Ȳ���� 2007. 11. 13 ���̸��� ������ ����.(�� �̸��� ��� ������ ���� �� ������)]
			if(0 == strlen(pclinfo->szAreaNmae[i]))				continue;

			StringCchCopy( AreaName, 64, pclinfo->szAreaNmae[i] );
			Nsprintf( buffer, text, TEXT("areaname"), AreaName, NULL );
			
			//[�߰� : Ȳ���� 2007. 11. 13 ��� ������ �̺�Ʈ �˸� ����� ���ڷ� ���̰� ��ǥ.]
			if(pclClient->IsCountrySwitch( Switch_RaccoonEvent_Change_Goonzu))
			{
				pos = pclinfo->m_ptPosition[i];
			}
			else
			{
				pos = pclinfo->m_ptPosition[pclinfo->m_siAreaIndex[i]];
			}
			StringCchPrintf( &buffer[strlen(buffer)], sizeof(buffer) - strlen(buffer)  ,"(%d, %d)", pos.x, pos.y );
					
			//pclMessage->SetMsg( buffer );
			pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0) );
		}
	}
	else if( CKingGuriEvent::DIE_KINGGURI ==pclinfo->siCmd )
	{
	//	TCHAR* text = GetTxtFromMgr( 10193 );
	//	pclMessage->SetMsg( text );

		TCHAR* text = GetTxtFromMgr( 10194 );
		TCHAR buffer[256] = {'\0'};
		TCHAR userName[MAX_PLAYER_NAME] = {'\0'};
		StringCchCopy( userName, MAX_PLAYER_NAME, pclinfo->szUserName );
		Nsprintf( buffer, text, TEXT("user"), userName, NULL );
		pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0));
	}
	else if( CKingGuriEvent::END == pclinfo->siCmd )
	{
		TCHAR* text = GetTxtFromMgr( 10193 );
		pclMessage->SetMsg( text, 0, RGB(255, 255, 0));
	}
	//[�߰� : Ȳ���� 2007. 11. 14 ��� ������ ���̰� ���� �����۰� ���� ����.]
	else if( CKingGuriEvent::ITEM == pclinfo->siCmd )
	{
		pclMessage->SetMsg( pclinfo->szBuffer, 0, RGB(255, 255, 0));
	}
}

//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ �޽��� ó���� �߰�.]
void cltClient::DoMsg_GAMEMSG_RESPONSE_SANTARACCOONINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_SantaRaccoonInfo* pclinfo = (cltGameMsgResponse_SantaRaccoonInfo*)pclMsg->cData;

	if( CSantaRaccoon::START == pclinfo->siCmd )
	{
		// �������� �����ϴ°��� �ּ�ó����.
		TCHAR* text = GetTxtFromMgr( 6683 );
		//pclMessage->SetMsg( text, 0, RGB(255, 255, 0)  );

		text = GetTxtFromMgr( 7680 );
		TCHAR buffer[256] = {'\0'};
		TCHAR AreaName[64] = {'\0'};

		POINT pos;
		for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
		{
			StringCchCopy( AreaName, 64, pclinfo->szAreaNmae[i] );
			Nsprintf( buffer, text, TEXT("areaname"), AreaName, NULL );

			//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ �˸� ����� ���ڷ� ���̰� ��ǥ.]
			pos = pclinfo->m_ptPosition[pclinfo->m_siAreaIndex[i]];
			StringCchPrintf( &buffer[strlen(buffer)], sizeof(buffer) - strlen(buffer)  ,"(%d, %d)", pos.x, pos.y );

			//pclMessage->SetMsg( buffer );
			pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0) );
		}
	}
	else if( CSantaRaccoon::ACTION == pclinfo->siCmd )
	{
		TCHAR* text = GetTxtFromMgr( 7680 );
		TCHAR buffer[256] = {'\0'};
		TCHAR AreaName[64] = {'\0'};

		POINT pos;
		for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
		{	
			//[�߰� : Ȳ���� 2007. 11. 29 ���̸��� ������ ����.(�� �̸��� ��� ������ ���� �� ������)]
			if(0 == strlen(pclinfo->szAreaNmae[i]))
				continue;

			StringCchCopy( AreaName, 64, pclinfo->szAreaNmae[i] );
			Nsprintf( buffer, text, TEXT("areaname"), AreaName, NULL );

			//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ �̺�Ʈ �˸� ����� ���ڷ� ���̰� ��ǥ.]
			pos = pclinfo->m_ptPosition[pclinfo->m_siAreaIndex[i]];
			StringCchPrintf( &buffer[strlen(buffer)], sizeof(buffer) - strlen(buffer)  ,"(%d, %d)", pos.x, pos.y );

			//pclMessage->SetMsg( buffer );
			pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0) );
		}
	}
	else if( CSantaRaccoon::DIE == pclinfo->siCmd )
	{
		//	TCHAR* text = GetTxtFromMgr( 10193 );
		//	pclMessage->SetMsg( text );

		TCHAR* text = GetTxtFromMgr( 10194 );
		TCHAR buffer[256] = {'\0'};
		TCHAR userName[MAX_PLAYER_NAME] = {'\0'};
		StringCchCopy( userName, MAX_PLAYER_NAME, pclinfo->szUserName );
		Nsprintf( buffer, text, TEXT("user"), userName, NULL );
		//pclMessage->SetMsg( buffer, 0, RGB(255, 255, 0));
	}
	else if( CSantaRaccoon::END == pclinfo->siCmd )
	{
		TCHAR* text = GetTxtFromMgr( 7682 );
		pclMessage->SetMsg( text, 0, RGB(255, 255, 0));
	}
	//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ������ ���̰� ���� �����۰� ���� ����.]
	else if( CKingGuriEvent::ITEM == pclinfo->siCmd )
	{
		pclMessage->SetMsg( pclinfo->szBuffer, 0, RGB(255, 255, 0));
	}
}
// [����] 2008.01.13 - �����̺�Ʈ : ī��Ʈ ���� �޽��� ó��
void cltClient::DoMsg_GAMEMSG_RESPONSE_KITERACCOONINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_KiteRaccoonInfo* pclinfo = (cltGameMsgResponse_KiteRaccoonInfo*)pclMsg->cData;
	
	switch ( pclinfo->m_siType ) 
	{
	// ī��Ʈ ���� �̺�Ʈ�� ���ߵ��� �˸�
	case ( cltEventTimeManager::KITERACCOON_EVENT_START ):
		{
			TCHAR	tszMonster[MAX_PLAYER_NAME]	= {'\0', };
			TCHAR	tszBuffer[256]				= {'\0', };
			TCHAR	*ptsText					= GetTxtFromMgr( 7837 );
			
				
			StringCchCopy( tszMonster, MAX_PLAYER_NAME, pclKindInfoSet->GetName( pclinfo->m_siMonsterKind ) ) ;
			Nsprintf( tszBuffer, ptsText, TEXT("monster"), tszMonster, NULL );

			pclMessage->SetMsg( tszBuffer, 0, RGB(255, 255, 0) );
		}
		break;
	// ������ ī��Ʈ ������ �׿��ٰ� �˸�
	case( cltEventTimeManager::KITERACCOON_EVENT_KILL ):
		{
			TCHAR	tszMonster[MAX_PLAYER_NAME] = {'\0', };
			TCHAR	tszItem[MAX_ITEM_NAME]		= {'\0', };
			TCHAR	tszUser[MAX_PLAYER_NAME]	= {'\0', };
			TCHAR	tszBuffer[256]				= {'\0', };
			TCHAR	*ptsText					= GetTxtFromMgr( 7838 );


			StringCchCopy( tszMonster, MAX_PLAYER_NAME, pclKindInfoSet->GetName( pclinfo->m_siMonsterKind ) ) ;
			StringCchCopy( tszItem, MAX_ITEM_NAME, pclItemManager->GetName( pclinfo->m_siItemUnique ) );
			StringCchCopy( tszUser, MAX_PLAYER_NAME, pclinfo->m_tszUserName );

			Nsprintf( tszBuffer, ptsText, TEXT("user"), tszUser, TEXT("monster"), tszMonster, TEXT("item"), tszItem, NULL );

			pclMessage->SetMsg( tszBuffer, 0, RGB(255, 255, 0) );
		}
		break;

	// ī��Ʈ ���� �̺�Ʈ�� ����Ǿ����� �˸�
	case( cltEventTimeManager::KITERACCOON_EVENT_END ):
		{
			TCHAR	tszBuffer[256]				= {'\0', };
			TCHAR	*ptsText					= GetTxtFromMgr( 7839 );

			StringCchCopy( tszBuffer, 256, ptsText );

			pclMessage->SetMsg( tszBuffer, 0, RGB(255, 255, 0) );
		}
		break;
	}
}

