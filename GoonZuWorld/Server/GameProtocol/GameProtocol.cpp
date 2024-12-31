//---------------------------------
// 2003/7/8 김태곤
//---------------------------------

#include "GameProtocol.h"
#include "..\..\CommonLogic\MsgType.h"
#include "..\..\CommonLogic\CommonLogic.h"
#include "..\..\Server\Server.h"
#include "ITZEncrypt.h"

#include "../../Apex/ApexGoonZu.h"
#include "../GMSystem/GMProtocol.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

cltGameProtocol::cltGameProtocol(cltCommonLogic* pclclient)
{
	pclClient = pclclient;

#ifdef _CHINA
	m_SF.CreateFactory(GetSessionManager(), MAX_PERSON_NUMBER-1, 30000, 80000, 0, true );
#else
	m_SF.CreateFactory(GetSessionManager(), MAX_PERSON_NUMBER-1, 50000, 50000, 0, true );
#endif

	GetNetIOCP()->CreateIOCP(GetSessionManager(), 1);

	//GetListen()->CreateListen(GetSessionManager(), 4010);
	
	//--------------------------------
	// 초당 10프레임을 유지한다. 
	//--------------------------------
	//SetFPS( 10 );
}

cltGameProtocol::~cltGameProtocol()
{

}

void cltGameProtocol::Init(UI16 usClientListenPort)
{
	//m_SF.CreateFactory(GetSessionManager(), MAX_PERSON_NUMBER-1, 50000, 50000);

	//GetNetIOCP()->CreateIOCP(GetSessionManager(), 1);

	GetListen()->CreateListen(GetSessionManager(), usClientListenPort);
}

void cltGameProtocol::Start()
{
	GetListen()->Start();
}

void cltGameProtocol::LogOut(ITZSession* pSession)
{

}


void cltGameProtocol::SessionProc(ITZSession *pSession)
{
	// 버퍼에서 패킷을 하나 꺼내온다. 
	sPacketHeader *pPacket = (sPacketHeader*)(pSession->GetRecvBuffer()->GetFirstPacket());

	if(pPacket == NULL)return ;		// 패킷이 없으면 리턴. 


	if( pSession->GetEncrypt()->Decode( (UI08*)pPacket, m_encrBuf ) == FALSE ) {
	// 잘못된 패킷이면, 접속을 끊는다

		cltCharServer* pcr = (cltCharServer*)pSession->GetPerson();
		pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("Invalid Secret Decode[personid:%d][%d][%d]"), 
			pcr->pclCI->GetPersonID(),
			pPacket->usCmd, pPacket->ucChk);

		// apex-
#ifdef _CHINA
		NoticeApexProxy_UserLogout( pcr->GetID(), (char*)pcr->pclCI->clBI.szAccountID );
		pcr->bApexLogin = false;
#endif
		// -apex

#ifdef USE_GAME_GUARD_SERVER
		pcr->CCSAuthClose();
#endif
		pSession->CloseSocket();
		return;

	}

	//-------------------------------------------
	// 받은 메시지를 처리한다. 
	//-------------------------------------------
	cltMsg* pclMsg = (cltMsg*)m_encrBuf;
	cltServer* pclserver = (cltServer*)pclClient;

	UI32 uiCompSize = 0;
	EnterCriticalSection( &pclserver->m_cs_SendNetMsg );
	{
		// 커맨드의 최상위 비트를 압축여부로 사용한다.
		if( pclMsg->clHead.usCmd & 0x8000 )
		{
			BYTE* pbufComp = pclserver->m_bufComp;
			memcpy(pbufComp, m_encrBuf, sizeof(sPacketHeader));
			UI32 uiSize = pclMsg->clHead.usSize - sizeof(sPacketHeader);

			UI32 uiDecompSize = pSession->Decompress( &m_encrBuf[sizeof(sPacketHeader)], uiSize,
													  &pbufComp[sizeof(sPacketHeader)],	sizeof(pclserver->m_bufComp) - sizeof(sPacketHeader) );
			if( uiDecompSize == 0 )
			{
				// 잘못된 패킷이면, 접속을 끊는다

				cltCharServer* pcr = (cltCharServer*)pSession->GetPerson();
				pclClient->pclLog->FilePrint(	TEXT("Config\\ErrorLog.log"), TEXT("Invalid Decompress[personid:%d][%d][%d]"), 
												pcr->pclCI->GetPersonID(),
												pPacket->usCmd, pPacket->ucChk);
				// apex-
#ifdef _CHINA
				NoticeApexProxy_UserLogout( pcr->GetID(), (char*)pcr->pclCI->clBI.szAccountID );
				pcr->bApexLogin = false;
#endif
				// -apex

#ifdef USE_GAME_GUARD_SERVER
				pcr->CCSAuthClose();
#endif
				pSession->CloseSocket();
				return;
			}

			pclMsg = (cltMsg*)pbufComp;
			pclMsg->clHead.usSize = sizeof(sPacketHeader) + uiDecompSize;
			pclMsg->clHead.usCmd -= 0x8000;
		}
	}
	LeaveCriticalSection( &pclserver->m_cs_SendNetMsg );

#ifdef WRITE_NETMESSAGE_STATISTICS
	//-------------------------------------------
	// 받은 메시지 개수를 카운트 한다.
	//-------------------------------------------
	if( pclMsg->clHead.usCmd >= 0 && pclMsg->clHead.usCmd < GAMEMSG_END )
	{
		m_clNetMessageStatistics[pclMsg->clHead.usCmd].m_siRecv++;
		m_clNetMessageStatistics[pclMsg->clHead.usCmd].m_siSize = pclMsg->clHead.usSize;
	}
#endif

	//NStatistics_Add("NetMessage", pclMsg->clHead.usCmd, "RecvCount", 1);
	//NStatistics_Add("NetMessage", pclMsg->clHead.usCmd, "RecvSize", pclMsg->clHead.usSize);

	// 누구한테 받은 메시지인지를 정리한다. 
	cltCharServer* pcr = (cltCharServer*)pSession->GetPerson();
	
	((cltServer*)pclClient)->pclGMProtocol->GMLock();
	pclClient->InBufferMessageOperation(pclMsg, pcr->GetID());
	((cltServer*)pclClient)->pclGMProtocol->GMUnlock();

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}

void cltGameProtocol::Update()
{
	((cltServer*)pclClient)->pclGMProtocol->GMLock();

	// GameDBProcess 처리.
	((cltServer*)pclClient)->GameDBAction();

	pclClient->GameProcess();

	((cltServer*)pclClient)->pclGMProtocol->GMUnlock();

#ifdef WRITE_NETMESSAGE_STATISTICS

	SYSTEMTIME sTime;
	GetLocalTime(&sTime);

	// "hh시"와 "hh시30분"때 로그를 쓴다.
	if( (sTime.wMinute == 0 || sTime.wMinute == 30) &&
		sTime.wMinute == 0 &&
		sTime.wSecond == 0 )
	{
		TCHAR fileNameBuffer[256];
		::CreateDirectory("Config\\NetMessage\\", NULL);
		StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\NetMessage\\NetMessage_%04d%02d%02d_%02d%02d%02d.log") , sTime.wYear , sTime.wMonth , sTime.wDay, 
			sTime.wHour, sTime.wMinute, sTime.wSecond );
		FILE *fp = _tfopen( fileNameBuffer, TEXT("wt") );
		if(fp != NULL)
		{
			_ftprintf(fp, TEXT("Command\tSend\tReceive\tSize\n"));
			for(int i=0; i<GAMEMSG_END; i++)
			{
				if(m_clNetMessageStatistics[i].m_siSize > 0)
				{
					_ftprintf(fp, TEXT("%d\t%I64d\t%I64d\t%d\n"),	i,
						m_clNetMessageStatistics[i].m_siSend, 
						m_clNetMessageStatistics[i].m_siRecv, 
						m_clNetMessageStatistics[i].m_siSize);
				}
			}
			fclose(fp);
			ClearNetMessageStatistics();
		}
	}
#endif

}

#ifdef WRITE_NETMESSAGE_STATISTICS
void cltGameProtocol::ClearNetMessageStatistics()
{
	for(int i=0; i<GAMEMSG_END; i++)
	{
		m_clNetMessageStatistics[i].m_siSend = 0;
		m_clNetMessageStatistics[i].m_siRecv = 0;
		m_clNetMessageStatistics[i].m_siSize = 0;
	}
}
#endif