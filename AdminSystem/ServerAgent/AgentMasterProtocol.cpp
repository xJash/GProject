#include "AgentMasterProtocol.h"
#include "AgentServerProtocol.h"
#include "SessionList.h"

#include "../MasterServer/MasterMsg.h"

#include "ServerAgent.h"

AgentMasterProtocol::AgentMasterProtocol()
{

}

AgentMasterProtocol::~AgentMasterProtocol()
{

}

void AgentMasterProtocol::Init()
{

	m_SF.CreateFactory( GetSessionManager(), 20, 200000, 200000 );

	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), AGENT_LISTEN_PORT );
}


void AgentMasterProtocol::Update()
{

}


void AgentMasterProtocol::SessionProc( ITZSession *pSession )
{

	cMaster *pMaster = (cMaster *)(pSession->GetPerson());

	// ������ �������� 15�ʵ��� ��Ŷ ������ ������ ������ ���´�
	if( GetTickCount() - pMaster->m_dwLastRecvTick >= 15000 ) {

		pSession->CloseSocket();
		return;
	}

	// ������ ������ 5�ʸ��� �ѹ��� ��Ʈ��Ʈ�� ������ 
	if( GetTickCount() - pMaster->m_dwLastSendTick >= 5000 ) {

		pMaster->m_dwLastSendTick = GetTickCount();

		sReportToMaster_Heartbeat sendMsg;

		sendMsg.packetHeader.usCmd = MASTERMSG_REPORT_AGENT_HEARTBEAT;
		sendMsg.packetHeader.usSize = sizeof( sendMsg );

		pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );
	}

	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );

	if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������

	pMaster->m_dwLastRecvTick = GetTickCount();

	// ������ �ٷ� ���� �ؾ��� �޽����̸�,
	if( pPacket->usCmd >= 10000 ) {

		if(pPacket->usCmd >= 13000)
		{
			int a = 0;
		}
		if( pMaster->m_pServer != NULL ) {

			if( pMaster->m_pServer->GetSession()->GetState() == SESSION_STATE_ESTABLISHED ) {

				pMaster->m_pServer->GetSession()->GetSendBuffer()->Write( (BYTE *)pPacket );
			}
		}

	} else {


		// ��Ŷ Ŀ�ǵ忡 ���� ó��
		switch( pPacket->usCmd ) {

	case MASTERMSG_COMMAND_SERVER_ON:
		{
			sCommand_ServerOn *pRecvMsg = (sCommand_ServerOn *)pPacket;

			if( pRecvMsg->siServerID == pMaster->m_siServerID )
			{
				// ���� �ѱ�
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory( &si, sizeof(si) );
				si.cb = sizeof(si);
				ZeroMemory( &pi, sizeof(pi) );

				CreateProcess( pMaster->m_szFilePath, pMaster->m_szFilePath, NULL, NULL, FALSE, 0, NULL, "d:\\GoonzuWorld\\Goonzu_China", &si, &pi );
			}
		}
		break;

	case MASTERMSG_COMMAND_SERVER_OFF:
		{
			/*	sCommand_ServerOff *pRecvMsg = (sCommand_ServerOff *)pPacket;

			if( pRecvMsg->siServerID == pMaster->m_siServerID ) 
			{
			HANDLE hProcess;
			DWORD dwProcessID;
			DWORD dwExitCode;

			HWND hWnd = ::FindWindow( NULL, "GoonzuChina" );
			if( NULL == hWnd )
			return;

			GetWindowThreadProcessId( hWnd, &dwProcessID );
			if( NULL == ( hProcess = OpenProcess( PROCESS_TERMINATE, 0, dwProcessID ) ) )
			return;

			GetExitCodeThread( hProcess, &dwExitCode );
			// GameServer ���� 
			SafeTerminateProcess( hProcess, dwExitCode );

			CloseHandle( hProcess );
			}*/
		}
		break;

	case MASTERMSG_COMMAND_GAMEDBMANAGER_ON:
		{
			sCommand_GameDBManagerOn *pRecvMsg = (sCommand_GameDBManagerOn*)pPacket;

			if( pRecvMsg->siServerID == pMaster->m_siServerID )
			{
				// ���� �ѱ�
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory( &si, sizeof(si) );
				si.cb = sizeof(si);
				ZeroMemory( &pi, sizeof(pi) );

				CreateProcess( "d:\\GoonzuWorld\\GameDBManager_China\\GameDBManager.exe", "d:\\GoonzuWorld\\GameDBManager_China\\GameDBManager.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi );
			}
		}
		break;

	case MASTERMSG_COMMAND_GAMEDBMANAGER_OFF:
		{
			/*			sCommand_GameDBManagerOff *pRecvMsg = (sCommand_GameDBManagerOff *)pPacket;

			if( pRecvMsg->siServerID == pMaster->m_siServerID ) 
			{
			HANDLE hProcess;
			DWORD dwProcessID;
			DWORD dwExitCode;

			HWND hWnd = ::FindWindow( NULL, "c:\\GoonzuWorld\\GameDBManager_China\\GameDBManager.exe" );
			if( NULL == hWnd )
			return;

			GetWindowThreadProcessId( hWnd, &dwProcessID );
			if( NULL == ( hProcess = OpenProcess( PROCESS_TERMINATE, 0, dwProcessID ) ) )
			return;

			GetExitCodeProcess( hProcess, &dwExitCode );
			// GameDBManager ���� 
			SafeTerminateProcess( hProcess, dwExitCode );

			CloseHandle( hProcess );
			}*/
		}
		break;

	case AGENTMSG_REPORT_SERVERINFO:
		{

			sReportToAgent_ServerInfo *pRecvMsg = (sReportToAgent_ServerInfo *)pPacket;

			pMaster->SetServerID( pRecvMsg->siServerID );
			pMaster->SetFilePath( pRecvMsg->szFilePath );

			g_sessionList.Wait();

			// ���� ����Ʈ���� ���������ϸ��� ���� ���� ã�Ƽ� �����ش�
			for( int i = 0; i < g_asp.m_SF.m_siMaxSize; ++i ) {

				cServer *pServer = (cServer *)( g_asp.GetSessionManager()->GetSession( i )->GetPerson() );

				if( pServer->IsEqualFilePath( pRecvMsg->szFilePath ) == TRUE ) {

					pServer->SetServerID( pRecvMsg->siServerID );
					pServer->SetMaster( pMaster );

					pMaster->SetServer( pServer );

				}
			}

			g_sessionList.AddMasterSession( pMaster, pRecvMsg->szMessage );

			g_sessionList.Release();

		}
		break;

	case MASTERMSG_COMMAND_MAKEFILE:
		{
			sResponse_GMC_MakeFile	*pRecvMsg = (sResponse_GMC_MakeFile*)pPacket;
			HANDLE hFile = CreateFile( pRecvMsg->GetFileName(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
			if( INVALID_HANDLE_VALUE == hFile)
				break;
			CloseHandle( hFile );
		}
		break;

	case MASTERMSG_COMMAND_MAKEDIRECTORY:
		{
			sResponse_GMC_MakeDirectory	*pRecvMsg = (sResponse_GMC_MakeDirectory*)pPacket;

			CreateDirectory( pRecvMsg->GetDirectoryName(), NULL );
		}
		break;

	case MASTERMSG_COMMAND_SEND_FILEDATA:
		{
			sResponse_GMC_SendFileData	*pRecvMsg = (sResponse_GMC_SendFileData*)pPacket;
			HANDLE hFile = CreateFile( pRecvMsg->m_szFileName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
			if( INVALID_HANDLE_VALUE == hFile)
				break;

			SetFilePointer( hFile, MAX_SEND_BYPE * pRecvMsg->m_siSendCount, NULL, FILE_BEGIN );
			DWORD write = 0;
			WriteFile( hFile, pRecvMsg->m_cData, pRecvMsg->m_siReadData, &write, NULL );
			CloseHandle( hFile );
		}
		break;
		} // switch
	} // if

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}

BOOL AgentMasterProtocol::SafeTerminateProcess(HANDLE hProcess, UINT uExitCode)
{
	DWORD dwTID, dwCode, dwErr = 0;
	HANDLE hProcessDup = INVALID_HANDLE_VALUE;
	HANDLE hRT = NULL;
	HINSTANCE hKernel = GetModuleHandle("Kernel32");

	BOOL bSuccess = FALSE;
	BOOL bDup = DuplicateHandle( GetCurrentProcess(), 
		hProcess, 
		GetCurrentProcess(), 
		&hProcessDup, 
		PROCESS_ALL_ACCESS, 
		FALSE, 
		0);
	if ( GetExitCodeProcess((bDup) ? hProcessDup : hProcess, &dwCode) 
		&& (dwCode == STILL_ACTIVE) )
	{
		FARPROC pfnExitProc;
		pfnExitProc = GetProcAddress(hKernel, "ExitProcess");
		hRT = CreateRemoteThread((bDup) ? hProcessDup : hProcess, 
			NULL, 
			0, 
			(LPTHREAD_START_ROUTINE)pfnExitProc,
			(PVOID)uExitCode, 0, &dwTID);
		if ( hRT == NULL ) dwErr = GetLastError();
	}
	else 
	{
		dwErr = ERROR_PROCESS_ABORTED;
	}
	if ( hRT )
	{
		WaitForSingleObject((bDup) ? hProcessDup : hProcess, INFINITE);
		CloseHandle(hRT);
		bSuccess = TRUE;
	}
	if ( bDup ) 
		CloseHandle(hProcessDup);
	if ( !bSuccess )
		SetLastError(dwErr);

	return bSuccess;
}


