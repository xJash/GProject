#include "CommonLogic.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "Server.h"

#include "Char-Server.h"

#ifdef USE_GAME_GUARD_SERVER

#define	GGAUTH_FIRST_AUTH_TIMEOUT	30 * 1000		// 30 ��
#define GGAUTH_N_AUTH_TERM			5 * 60 * 1000	// 5 ��

void StateToString(SI32 siState, TCHAR* pszOut, SI32 siLen)
{
	if(pszOut == NULL)			return;

	StringCchPrintf(pszOut, siLen, TEXT(""));

	switch(siState)
	{
	case CCSAUTH_STATE_NONE:				StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("NONE                "));		break;
	case CCSAUTH_STATE_INIT:				StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("INIT                "));		break;
	case CCSAUTH_STATE_FIRST_AUTH_SENDED:	StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("FIRST_AUTH_SENDED   "));		break;
	case CCSAUTH_STATE_FIRST_AUTH_RECEIVED:	StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("FIRST_AUTH_RECEIVED "));		break;
	case CCSAUTH_STATE_N_AUTH_SEND:			StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("N_AUTH_SEND         "));		break;
	case CCSAUTH_STATE_N_WAIT_NEXTTIME:		StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("N_WAIT_NEXTTIME     "));		break;

	default:								StringCchPrintf(pszOut, siLen, TEXT("%s"), TEXT("%02d                  "), siState);	break;

	}
}

void cltCharServer::CCSAuthInit()
{
	m_clCSA.Init();
	m_bCCSAuthInit = true;

	m_siCCSAuthState = CCSAUTH_STATE_INIT;

	m_siCCSAuthCount = 0;

	CCSAuthWriteProcessLog("CCSAuthInit()");

	cltServer* pclserver = (cltServer*)pclClient;
	//[����] CS���� - ������ �ʱ�ȭ => 2008-4-30
	pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_INIT);
}


void cltCharServer::CCSAuthClose()
{
	if(m_bCCSAuthInit == true)
	{
		m_clCSA.Close();
		m_bCCSAuthInit = false;

		m_siCCSAuthState = CCSAUTH_STATE_NONE;

		CCSAuthWriteProcessLog("CCSAuthClose()");

		//[����] CS���� - ������ �ʱ�ȭ => 2008-4-30
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_CLOSE);
	}
}

void cltCharServer::CCSCloseClient()
{
	if(bCloseSocketSwitch == false)
	{
		bCloseSocketSwitch		= true;
		dwCloseSocketTimer		= 5;

		TCHAR szState[96];
		StateToString(m_siCCSAuthState, szState, sizeof(szState));

		TCHAR szNotice[128];
		if(GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
			StringCchPrintf(szNotice, sizeof(szNotice), TEXT("%s : STATE[%s]"), TEXT("GameGuard Auth Error"), szState );
		else
			StringCchPrintf(szNotice, sizeof(szNotice), TEXT("%s"), TEXT("GameGuard Auth Error") );
		szNotice[ sizeof(szNotice) - 1 ] = '\0';

		TCHAR* pText = GetTxtFromMgr(5614);
		cltGameMsgResponse_Notice clNotice(pText, szNotice,true);
		cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
		SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltCharServer::CCSReceivedAuth(GG_AUTH_DATA* ggData)
{
	TCHAR szState[96];
	StateToString(m_siCCSAuthState, szState, sizeof(szState));

	DWORD dwResult = GGAuthCheckAnswer( &m_clCSA, ggData );
	TCHAR szMsg[1024];

	if(dwResult == ERROR_SUCCESS)
	{
		switch(m_siCCSAuthState)
		{
		case CCSAUTH_STATE_FIRST_AUTH_SENDED:
			{
				m_siCCSAuthState = CCSAUTH_STATE_FIRST_AUTH_RECEIVED;

				//[����] CS���� - ù��° ���� �˻�. => 2008-4-30
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_FIRST_AUTH_CHECK);
			}
			break;
		default:
			{
				//[����] CS���� - N ��° ���� �˻� => 2008-4-30
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_N_AUTH_CHECK);
			}
			break;
		}
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] ReceivedAuth[%d] [UserID : %s]"), 
						szState, m_siCCSAuthCount, pclCI->clBI.szAccountID );
		CCSAuthWriteProcessLog(szMsg);
	}
	else
	{
		TCHAR szMsg[1024];
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] [ERRORCODE:%d] Query  : %08X %08X %08X %08X [UserID : %s]"), 
						szState, dwResult, 							
						m_clCSA.m_AuthQuery.dwIndex, 
						m_clCSA.m_AuthQuery.dwValue1, m_clCSA.m_AuthQuery.dwValue2, m_clCSA.m_AuthQuery.dwValue3,
						pclCI->clBI.szAccountID );
		CCSAuthWriteErrorLog(szMsg);

		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] [ERRORCODE:%d] Answer : %08X %08X %08X %08X [UserID : %s]"), 
						szState, dwResult, 							
						m_clCSA.m_AuthAnswer.dwIndex, 
						m_clCSA.m_AuthAnswer.dwValue1, m_clCSA.m_AuthAnswer.dwValue2, m_clCSA.m_AuthAnswer.dwValue3,
						pclCI->clBI.szAccountID );
		CCSAuthWriteErrorLog(szMsg);

		CCSCloseClient();
	}
}

void cltCharServer::CCSAuthWriteProcessLog(TCHAR* pszMsg)
{
	SYSTEMTIME CT;
	GetLocalTime(&CT);

	TCHAR szFileName[256] = "";
	StringCchPrintf(szFileName, sizeof(szFileName), TEXT("GameGuardLog\\GameGuard%s_%02d%02d%02d.txt"), TEXT("GGAuthProcess"), CT.wYear, CT.wMonth, CT.wDay);

	pclClient->pclLog->FilePrint(szFileName, TEXT("%s"), pszMsg);
}

void cltCharServer::CCSAuthWriteErrorLog(TCHAR* pszMsg)
{
	SYSTEMTIME CT;
	GetLocalTime(&CT);

	TCHAR szFileName[256] = "";
	StringCchPrintf(szFileName, sizeof(szFileName), TEXT("GameGuardLog\\GameGuard%s_%02d%02d%02d.txt"), TEXT("GGAuthError"), CT.wYear, CT.wMonth, CT.wDay);

	pclClient->pclLog->FilePrint(szFileName, TEXT("%s"), pszMsg);
}

void cltCharServer::CCSAuthRun()
{
	switch(m_siCCSAuthState)
	{
	case CCSAUTH_STATE_NONE:					// ��ü ����
		{
		}
		break;
	case CCSAUTH_STATE_INIT:					// �ʱ�ȭ ����
		{
			TCHAR szState[96];
			StateToString(m_siCCSAuthState, szState, sizeof(szState));

			// ù��° ���� ����
			GG_AUTH_DATA ggData;
			DWORD	dwResult = GGAuthGetQuery( &m_clCSA , &ggData );

			if(dwResult == ERROR_SUCCESS)
			{	
				//[����] CS���� - ù��° ����. => 2008-4-30
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_FIRST_AUTH_SENDED);

				cltGameMsgResponse_GameGuardAuth clinfo(&ggData);
				cltMsg clMsg(GAMEMSG_RESPONSE_GAME_GUARD_AUTH, sizeof(clinfo) , (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				m_siCCSAuthCount++;
				m_dwCCSAuthLastActionTick = GetTickCount();
				m_siCCSAuthState =  CCSAUTH_STATE_FIRST_AUTH_SENDED;

				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] SendAuth[%d]     [UserID : %s]"), 
								szState, m_siCCSAuthCount, pclCI->clBI.szAccountID );
				CCSAuthWriteProcessLog(szMsg);
			}
			else
			{
				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] [ERRORCODE:%d] Query  : %08X %08X %08X %08X [UserID : %s]"), 
								szState, dwResult,
								m_clCSA.m_AuthQuery.dwIndex, 
								m_clCSA.m_AuthQuery.dwValue1, m_clCSA.m_AuthQuery.dwValue2, m_clCSA.m_AuthQuery.dwValue3,
								pclCI->clBI.szAccountID );
				CCSAuthWriteErrorLog(szMsg);

				CCSCloseClient();
			}
		}
		break;
	case CCSAUTH_STATE_FIRST_AUTH_SENDED:		// ù��° ������ ���۵� ����
		{
			// ù��° ������ ���� ����� ���ٸ�, Ŭ���̾�Ʈ ���� ����
			if( GetTickCount() - m_dwCCSAuthLastActionTick > GGAUTH_FIRST_AUTH_TIMEOUT )
			{
				CCSCloseClient();
			}
		}
		break;
	case CCSAUTH_STATE_FIRST_AUTH_RECEIVED:		// ù��° ������ ���� ����
		{
			TCHAR szState[96];
			StateToString(m_siCCSAuthState, szState, sizeof(szState));

			// �ι�° ���� ����
			GG_AUTH_DATA ggData;
			DWORD	dwResult = GGAuthGetQuery( &m_clCSA , &ggData );

			if(dwResult == ERROR_SUCCESS)
			{
				cltGameMsgResponse_GameGuardAuth clinfo(&ggData);
				cltMsg clMsg(GAMEMSG_RESPONSE_GAME_GUARD_AUTH, sizeof(clinfo) , (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				m_siCCSAuthCount++;
				m_dwCCSAuthLastActionTick = GetTickCount();
				m_siCCSAuthState =  CCSAUTH_STATE_N_WAIT_NEXTTIME;

				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] SendAuth[%d]     [UserID : %s]"), 
								szState, m_siCCSAuthCount, pclCI->clBI.szAccountID );
				CCSAuthWriteProcessLog(szMsg);
			}
			else
			{
				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] [ERRORCODE:%d] Query  : %08X %08X %08X %08X [UserID : %s]"), 
								szState, dwResult, 							
								m_clCSA.m_AuthQuery.dwIndex, 
								m_clCSA.m_AuthQuery.dwValue1, m_clCSA.m_AuthQuery.dwValue2, m_clCSA.m_AuthQuery.dwValue3,
								pclCI->clBI.szAccountID );
				CCSAuthWriteErrorLog(szMsg);

				CCSCloseClient();
			}
		}
		break;
	case CCSAUTH_STATE_N_AUTH_SEND:				// N��° ���� ���� ����
		{
			TCHAR szState[96];
			StateToString(m_siCCSAuthState, szState, sizeof(szState));

			GG_AUTH_DATA ggData;
			DWORD	dwResult = GGAuthGetQuery( &m_clCSA , &ggData );

			if(dwResult == ERROR_SUCCESS)
			{
				//[����] CS���� - N ��° ���� ���� => 2008-4-30
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->HanAuth_Lib_HanReportSendPosLog_Server(pclCI->clBI.szAccountID, _CCSAUTH_STATE_N_AUTH_SEND);

				cltGameMsgResponse_GameGuardAuth clinfo(&ggData);
				cltMsg clMsg(GAMEMSG_RESPONSE_GAME_GUARD_AUTH, sizeof(clinfo) , (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				m_siCCSAuthCount++;
				m_dwCCSAuthLastActionTick = GetTickCount();
				m_siCCSAuthState =  CCSAUTH_STATE_N_WAIT_NEXTTIME;

				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] SendAuth[%d]     [UserID : %s]"), 
					szState, m_siCCSAuthCount, pclCI->clBI.szAccountID );
				CCSAuthWriteProcessLog(szMsg);
			}
			else
			{
				TCHAR szMsg[1024];
				StringCchPrintf(szMsg, sizeof(szMsg), TEXT("[State:%s] [ERRORCODE:%d] Query  : %08X %08X %08X %08X [UserID : %s]"), 
					szState, dwResult, 							
					m_clCSA.m_AuthQuery.dwIndex, 
					m_clCSA.m_AuthQuery.dwValue1, m_clCSA.m_AuthQuery.dwValue2, m_clCSA.m_AuthQuery.dwValue3,
					pclCI->clBI.szAccountID );
				CCSAuthWriteErrorLog(szMsg);

				CCSCloseClient();
			}
		}
		break;
	case CCSAUTH_STATE_N_WAIT_NEXTTIME:			// ���� �������� ���
		{
			// ��ٸ��� 5���� �Ѿ����� ������ �����Ѵ�.
			if( GetTickCount() - m_dwCCSAuthLastActionTick > GGAUTH_N_AUTH_TERM )
			{
				m_siCCSAuthState =  CCSAUTH_STATE_N_AUTH_SEND;
			}
		}
		break;
	}
}

#endif