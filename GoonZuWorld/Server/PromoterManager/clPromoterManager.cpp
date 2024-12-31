#include "CommonLogic.h"
#include "server.h"
#include "Char/CharManager/CharManager.h"

#include "../../../DBManager/GameDBManager_World/dbMsg-Person.h"

#include ".\clpromotermanager.h"

#include "Msg/MsgType-npc.h"

#define PROMOTER_LOG

// �̺�Ʈ ó�� ������.
unsigned __stdcall EventThread( LPVOID _pParam )
{
#ifdef USE_PROMOTOR_SERVER
	clThreadInfo*	pclThreadInfo	= (clThreadInfo*)_pParam;
	cltServer*		pclserver		= (cltServer* )pclClient;
	if( NULL == pclThreadInfo || NULL == pclserver ) 
	{
		MessageBox( NULL, "EventThread(): if( NULL == pclThreadInfo )", "Fail", 0 );
	}

	char	svrid[NHNCHINAPROMOTER_SVRID_SIZE]						= "";
	char	promoterUserid[NHNCHINAPROMOTER_PROMOTER_USERID_SIZE]	= "";
	char	promoterCharid[NHNCHINAPROMOTER_PROMOTER_CHARID_SIZE]	= "";
	char	auth[NHNCHINAPROMOTER_AUTH_SIZE]						= "";
	char	msg[NHNCHINAPROMOTER_MSG_SIZE]							= "";
	char 	code[NHNCHINAPROMOTER_CODE_SIZE]						= "";
	char 	url[NHNCHINAPROMOTER_URL_SIZE]							= "";		

	TCHAR	szLogFileName[128] = "";
	StringCchPrintf( szLogFileName, sizeof(szLogFileName), "config\\Promoter Thread[%d].log", pclThreadInfo->GetThreadIndex() );


	NHNChinaPromoter::ReturnCode ret;

	// ������ ���� �ǽ�.
	pclThreadInfo->Run();

	cltCharServer* pclChar = NULL;

	while( pclThreadInfo->GetState() )
	{
		WaitForSingleObject( pclThreadInfo->GetEvent(), INFINITE );

		pclChar = pclserver->pclCM->GetCharServer( pclThreadInfo->GetID() );
		if( NULL == pclChar ) continue;

		switch( pclThreadInfo->GetOperatorType() )
		{
		case clPromoterInfo::GET_PROMOTER_INFO_TOTAL:
			{
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO_TOTAL : Start> AccountID:[%s], CharName:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName()	); 
#endif

				pclChar->bCellularPhoneAuth = false;
				pclChar->bIsPromoter		= false;	

				NHNChinaPromoter::Connection con("purple.promoter/sqlmap");

				//////////////////////////////////////////////////////////////////////////
				// ���θ��� ����					
				//////////////////////////////////////////////////////////////////////////
				ret = NHNChinaPromoter::GetPromoterInfoForNewbie(	con, 
																	"C_GZ", 
																	pclChar->pclCI->clBI.szAccountID, 
																	pclChar->pclCI->clBI.GetName(), 
																	svrid, 
																	promoterUserid, 
																	promoterCharid, 
																	auth, 
																	msg	);

				if( NHNChinaPromoter::SUCC != ret )			break;
				//if( atoi(svrid) != pclserver->siServerID )	break; 
				//if( 0 >= strlen(promoterCharid) )			break;
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO_TOTAL : GetPromoterInfoForNewbie> Account:[%s], CharName:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName(), 
																svrid, 
																promoterUserid, 
																promoterCharid,
																auth				);
#endif

				// ������ �ڵ������� ����.  
				if( 0 == strcmp( "Y", auth ) )
					pclChar->bCellularPhoneAuth = true;
				else
					pclChar->bCellularPhoneAuth = false;

				pclChar->bIsPromoter = true;

				TCHAR	PromoterName[MAX_PLAYER_NAME]  = "";
				WCHAR	wPromoterName[MAX_PLAYER_NAME];
				MultiByteToWideChar( CP_UTF8, 0, promoterCharid,	-1, wPromoterName, sizeof(wPromoterName) );
#ifndef _UNICODE
				WideCharToMultiByte( CP_ACP,  0, wPromoterName,		-1, PromoterName,  sizeof(PromoterName),  NULL, NULL );
#endif

				// ���� test
				//StringCchPrintf( PromoterName, sizeof(PromoterName), "NDSsadachun"); 

				// ���θ����� ������ �� �ʿ��ؼ� DB�� ������ �� ��û�ϱ����� sDBRequest_PersonSimpleInfo �̰ɾ���.
				sDBRequest_PersonSimpleInfo SendMsg( pclThreadInfo->GetID(), 0, PERSONSIMPLEINFO_REASON_PROMOTER_INFO, promoterCharid ); 
				pclClient->SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&SendMsg );

				//////////////////////////////////////////////////////////////////////////
				// ���θ��� URL					
				//////////////////////////////////////////////////////////////////////////
				ret = NHNChinaPromoter::GetPromoterCode(	con, 
															"C_GZ",
															promoterUserid,
															promoterCharid,
															code, 
															url, 
															msg	);

				if (NHNChinaPromoter::SUCC != ret) break;
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO_TOTAL : GetPromoterCode> PromoterUserID:[%s], PromoterCharID:[%s], URL:[%s]", 
																promoterUserid, 
																PromoterName,
																url				);
#endif

				TCHAR szURL[NHNCHINAPROMOTER_URL_SIZE];
#ifndef _UNICODE
				StringCchCopy( szURL, sizeof(szURL), url );
#else
				MultiByteToWideChar( CP_ACP, MB_COMPOSITE, url, -1, szURL, sizeof(szURL) );
#endif
				cltGameResponse_Promoter_URL_Get clinfo( szURL );
				cltMsg clMsg(GAMEMSG_RESPONSE_PROMOTER_URL_GET, sizeof(clinfo), (BYTE*)&clinfo);
				//pclChar->SendNetMsg((sPacketHeader*)&clMsg);
				pclserver->SendNetMsg(pclThreadInfo->GetID(), (sPacketHeader*)&clMsg);

				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO_TOTAL : End>" ); 
			}
			break;
		case clPromoterInfo::GET_PROMOTER_INFO:
			{
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO : Start> AccountID:[%s], CharName:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName()	); 
#endif

				pclChar->bCellularPhoneAuth = false;
				pclChar->bIsPromoter		= false;	

				NHNChinaPromoter::Connection con("purple.promoter/sqlmap");

				//////////////////////////////////////////////////////////////////////////
				// ���θ��� ����					
				//////////////////////////////////////////////////////////////////////////
				ret = NHNChinaPromoter::GetPromoterInfoForNewbie(	con, 
																	"C_GZ", 
																	pclChar->pclCI->clBI.szAccountID, 
																	pclChar->pclCI->clBI.GetName(), 
																	svrid, 
																	promoterUserid, 
																	promoterCharid, 
																	auth, 
																	msg	);

				if( NHNChinaPromoter::SUCC != ret )			break;
				//if( atoi(svrid) != pclserver->siServerID )	break;
				//if( 0 >= strlen(promoterCharid) )			break;
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO : GetPromoterInfoForNewbie> Account:[%s], CharName:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName(), 
																svrid, 
																promoterUserid, 
																promoterCharid,
																auth				);
#endif


				// ������ �ڵ������� ����.  
				if( 0 == strcmp( "Y", auth ) )
					pclChar->bCellularPhoneAuth = true;
				else
					pclChar->bCellularPhoneAuth = false;

				pclChar->bIsPromoter = true;

				//StringCchPrintf( promoterCharid, sizeof(promoterCharid), "NDSsadachun");

				TCHAR	PromoterName[MAX_PLAYER_NAME]  = "";
				WCHAR	wPromoterName[MAX_PLAYER_NAME];
				MultiByteToWideChar( CP_UTF8, 0, promoterCharid,	-1, wPromoterName, sizeof(wPromoterName) );
#ifndef _UNICODE
				WideCharToMultiByte( CP_ACP,  0, wPromoterName,		-1, PromoterName,  sizeof(PromoterName),  NULL, NULL );
#endif
				// ���θ����� ������ �� �ʿ��ؼ� DB�� ������ �� ��û�ϱ����� sDBRequest_PersonSimpleInfo �̰ɾ���.
				sDBRequest_PersonSimpleInfo SendMsg( pclThreadInfo->GetID(), 0, PERSONSIMPLEINFO_REASON_PROMOTER_INFO, promoterCharid );
				pclClient->SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&SendMsg );

#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_INFO : End>" ); 
#endif
			}
			break;
		case clPromoterInfo::GET_PROMOTER_URL:
			{
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_URL : Start> AccountID:[%s], CharName:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName()	); 
#endif

				NHNChinaPromoter::Connection con("purple.promoter/sqlmap");

				ret = NHNChinaPromoter::GetPromoterInfoForNewbie(	con, 
																	"C_GZ", 
																	pclChar->pclCI->clBI.szAccountID, 
																	pclChar->pclCI->clBI.GetName(), 
																	svrid, 
																	promoterUserid, 
																	promoterCharid, 
																	auth, 
																	msg	);

				if( NHNChinaPromoter::SUCC != ret )			break;
				//if( atoi(svrid) != pclserver->siServerID )	break;
				//if( 0 >= strlen(promoterCharid) )			break;
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_URL : GetPromoterInfoForNewbie> Account:[%s], CharName:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName(), 
																svrid, 
																promoterUserid, 
																promoterCharid,
																auth				);
#endif


				ret = NHNChinaPromoter::GetPromoterCode(	con, 
															"C_GZ",
															promoterUserid,
															promoterCharid, 
															code, 
															url, 
															msg	);

				if (NHNChinaPromoter::SUCC != ret) break;
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<GET_PROMOTER_URL: GetPromoterCode> PromoterUserID:[%s], PromoterCharID:[%s], URL:[%s]", 
					promoterUserid, 
					promoterCharid,
					url				);
#endif

				TCHAR szURL[NHNCHINAPROMOTER_URL_SIZE];
#ifndef _UNICODE
				StringCchCopy( szURL, sizeof(szURL), url );
#else
				MultiByteToWideChar( CP_ACP, MB_COMPOSITE, url, -1, szURL, sizeof(szURL) );
#endif
				cltGameResponse_Promoter_URL_Get clinfo( szURL ); 
				cltMsg clMsg(GAMEMSG_RESPONSE_PROMOTER_URL_GET, sizeof(clinfo), (BYTE*)&clinfo);
				//pclChar->SendNetMsg((sPacketHeader*)&clMsg);
				pclserver->SendNetMsg(pclThreadInfo->GetID(), (sPacketHeader*)&clMsg);
			}
			break;
		case clPromoterInfo::SET_PROMOTER_CHAR:
			{
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<SET_PROMOTER_CHAR : Start> AccountID:[%s]", pclThreadInfo->GetAccountID() ); 
#endif

				//pclChar->bCellularPhoneAuth = false;
				//pclChar->bIsPromoter		= false;	

				NHNChinaPromoter::Connection con("purple.promoter/sqlmap");

				// �������� ���θ��Ͱ� �ִ��� ������ ���´�.
				ret = NHNChinaPromoter::GetPromoterInfoForNewbie(	con, 
																	"C_GZ", 
																	pclThreadInfo->GetAccountID(), 
																	"null",
																	svrid, 
																	promoterUserid, 
																	promoterCharid, 
																	auth, 
																	msg	);

				// ���θ��Ϳ� ����� ĳ���� ���� �� ĳ���� �̸��� "null"�� �Ѱ��ָ� SUCC�� ���Ϲ������ִ�.
				if( NHNChinaPromoter::SUCC != ret )	break;

				TCHAR	PromoterName[MAX_PLAYER_NAME]  = "";
				WCHAR	wPromoterName[MAX_PLAYER_NAME];
				MultiByteToWideChar( CP_UTF8, 0, promoterCharid,	-1, wPromoterName, sizeof(wPromoterName) );
#ifndef _UNICODE
				WideCharToMultiByte( CP_ACP,  0, wPromoterName,		-1, PromoterName,  sizeof(PromoterName),  NULL, NULL );
#endif
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<SET_PROMOTER_CHAR : GetPromoterInfoForNewbie> Account:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclThreadInfo->GetAccountID(), 
																svrid, 
																promoterUserid, 
																PromoterName,
																auth				);

				pclClient->pclLog->FilePrint( szLogFileName, "<SET_PROMOTER_CHAR : ServerID> Game Server:[%d], ServerID:[%s]", pclserver->siServerID, svrid );
#endif

				if( atoi(svrid) != pclserver->siServerID )	break;

				// �������� ���� ���θ��͸� �ش� ĳ���Ϳ� �����Ų��.
				ret = NHNChinaPromoter::SetFirstCharidInfoForNewbie(	con, 
																		"C_GZ", 
																		svrid,
																		pclThreadInfo->GetAccountID(),
																		pclThreadInfo->GetName(),
																		promoterUserid,
																		promoterCharid,
																		msg);

				if( NHNChinaPromoter::SUCC != ret )	break;

#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<SET_PROMOTER_CHAR : SetFirstCharidInfoForNewbie> Account:[%s], CharName:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclThreadInfo->GetAccountID(), 
																pclThreadInfo->GetName(), 
																svrid, 
																promoterUserid, 
																promoterCharid,
																auth				);
#endif

				// ����õ�ο��� ��õ���� ������ ��� ��Ŵ
				cltGameResponse_Promoter_Set clinfo( PromoterName );
				cltMsg clMsg(GAMEMSG_RESPONSE_PROMOTER_SET, sizeof(clinfo), (BYTE*)&clinfo);
				//pclChar->SendNetMsg((sPacketHeader*)&clMsg);
				pclserver->SendNetMsg(pclThreadInfo->GetID(), (sPacketHeader*)&clMsg);

				pclClient->pclLog->FilePrint( szLogFileName, "<SET_PROMOTER_CHAR : End>" ); 
			}
			break;
		case clPromoterInfo::PROMOTER_INTRODUCE:
			{
#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<PROMOTER_INTRODUCE : Start> AccountID:[%s], CharName:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName()	); 
#endif

				NHNChinaPromoter::Connection con("purple.promoter/sqlmap");

				ret = NHNChinaPromoter::GetPromoterInfoForNewbie(	con, 
																	"C_GZ", 
																	pclChar->pclCI->clBI.szAccountID, 
																	pclChar->pclCI->clBI.GetName(), 
																	svrid,
																	promoterUserid, 
																	promoterCharid, 
																	auth, 
																	msg	);

				if( NHNChinaPromoter::SUCC != ret )			break;

#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<PROMOTER_INTRODUCE : GetPromoterInfoForNewbie> Account:[%s], CharName:[%s], ServerID:[%s], PromoterUserID:[%s], PromoterCharID:[%s], Auth:[%s]", 
																pclChar->pclCI->clBI.szAccountID, 
																pclChar->pclCI->clBI.GetName(), 
																svrid, 
																promoterUserid, 
																promoterCharid,
																auth				);
#endif

				TCHAR	PromoterName[MAX_PLAYER_NAME]  = "";
				WCHAR	wPromoterName[MAX_PLAYER_NAME];
				MultiByteToWideChar( CP_UTF8, 0, promoterCharid,	-1, wPromoterName, sizeof(wPromoterName) );
#ifndef _UNICODE
				WideCharToMultiByte( CP_ACP,  0, wPromoterName,		-1, PromoterName,  sizeof(PromoterName),  NULL, NULL );
#endif

				//StringCchPrintf( PromoterName, sizeof(PromoterName), "NDSsadachun");

				// ��õ���� ����õ�ο��� �λ縻. (��õ���� ������ ��û)
				sDBRequest_PersonSimpleInfo SendMsg1( pclThreadInfo->GetID(), 0, PERSONSIMPLEINFO_REASON_RECOMMEND_INTRODUCE, pclChar->GetName(), promoterCharid);
				pclClient->SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&SendMsg1 );

				// ����õ���� ��õ�ο��� �λ縻.( ����õ���� ������ ��û)
				sDBRequest_PersonSimpleInfo SendMsg2( pclThreadInfo->GetID(), 0, PERSONSIMPLEINFO_REASON_RECOMMENDEE_INTRODUCE, promoterCharid, pclChar->GetName() );
				pclClient->SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&SendMsg2 );

#ifdef PROMOTER_LOG
				pclClient->pclLog->FilePrint( szLogFileName, "<PROMOTER_INTRODUCE : End>" ); 
#endif
			}
			break;
		}


		// �̺�Ʈ�� nonsignal�� ����.
		ResetEvent( pclThreadInfo->GetEvent() );

		// ������ Ȱ���� �������� ����.
		pclThreadInfo->SetActive( false );	
	} 

#endif	
	return 0;
}


clPromoterManager::clPromoterManager()
{
	InitializeCriticalSection( &m_CS );

	// �� �����忡 ���� �̺�Ʈ ����.
	for( int siCount = 0; siCount < PROMOTER_THREAD_NUM; ++siCount )
	{
		m_clThreadInfo[siCount].SetEvent( CreateEvent( NULL, TRUE, FALSE, NULL ) );

		if( NULL == m_clThreadInfo[siCount].GetEvent() ) 
			MessageBox( NULL, "clPromoterManager(): m_clPromoterEvent[siCount].GetPromoterEvent() Fail", "Fail", 0 );
	}

	// ������ ����.
	unsigned int uiThreadID;
	for( int siCount = 0; siCount < PROMOTER_THREAD_NUM; ++siCount )
	{
		m_clThreadInfo[siCount].SetThreadIndex( siCount );

		if( 0 == _beginthreadex( NULL, 0, EventThread, (LPVOID)&m_clThreadInfo[siCount], 0, &uiThreadID ) )
			MessageBox( NULL, "clPromoterManager(): _beginthreadex() Fail", "Fail", 0 );
	}
}

clPromoterManager::~clPromoterManager(void)
{
	DeleteCriticalSection( &m_CS );

	for( int siCount = 0; siCount < PROMOTER_THREAD_NUM; ++siCount )
	{
		// ������ ����.
		m_clThreadInfo[siCount].Exit();

		// ������ ���Ḧ ���� �̺�Ʈ�� �ñ׳� ���·� �����Ͽ� �����ִ� ������ �ϳ��� ����Ѵ�.
		SetEvent( m_clThreadInfo[siCount].GetEvent() );	

		// �̺�Ʈ �ڵ� ����.
		CloseHandle( m_clThreadInfo[siCount].GetEvent() );
	}
}

void clPromoterManager::Action( void )
{
	Pop();
}

void clPromoterManager::Push( clPromoterInfo PromoterInfo )
{
	m_clPromoterInfoQueue.push( PromoterInfo );
}

bool clPromoterManager::Pop( void )
{
	if( m_clPromoterInfoQueue.empty() )	return false;

	for( int siCount = 0; siCount < PROMOTER_THREAD_NUM; ++siCount )
	{
		if( false == m_clThreadInfo[siCount].GetActive() ) 
		{
			ActionThread( siCount );

			return true;
		}
	}

	return false;
}

void clPromoterManager::Lock( void )
{
	EnterCriticalSection( &m_CS );
}

void clPromoterManager::UnLock( void )
{
	LeaveCriticalSection( &m_CS );
}

clThreadInfo* clPromoterManager::GetCreateThreadInfo( void )
{
	static int m_siGetThreadCount = 0;	

	if( PROMOTER_THREAD_NUM <= m_siGetThreadCount )
	{
		MessageBox( NULL, "GetCreateEventThread(): GetCreateEventThread() Fail", "Fail", 0 );
		return NULL;
	}

	return &m_clThreadInfo[m_siGetThreadCount++];
}

void clPromoterManager::ActionThread( int _siThreadIndex )
{
	static clPromoterInfo PromoterInfo;
	PromoterInfo = m_clPromoterInfoQueue.front();
	m_clPromoterInfoQueue.pop();

	m_clThreadInfo[_siThreadIndex].SetActive( true );
	m_clThreadInfo[_siThreadIndex].SetOperatorType( PromoterInfo.GetOperatorType() );
	m_clThreadInfo[_siThreadIndex].SetID( PromoterInfo.GetID() );
	m_clThreadInfo[_siThreadIndex].SetName( PromoterInfo.GetName() );
	m_clThreadInfo[_siThreadIndex].SetAccountID( PromoterInfo.GetAccountID() );

	SetEvent( m_clThreadInfo[_siThreadIndex].GetEvent() );	// �̺�Ʈ�� �ñ׳� ���·� �����Ͽ� �����ִ� ������ �ϳ��� ����Ѵ�.
}

