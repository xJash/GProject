//---------------------------------
// 2003/8/4 김태곤
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\Common\Map\Map.h"
#include "..\Common\Letter\Letter.h"
#include "Char\CharManager\CharManager.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "Statistics/Statistics.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg.h"

void cltServer::InitNetwork()
{
	pclGameProtocol = new cltGameProtocol(this);
	pclGameProtocol->CreateThread();

	// AgentProcess 생성. 
	pclAgentProcess		= new AgentProcess();
	pclAgentProcess->Init(TEXT("127.0.0.1"), 6400);

}

// Agent에서 받은 정보를 토대로 서버들과의 연결을 설정한다.
void cltServer::SetOtherServer(TCHAR* frontip, SI32 frontport, TCHAR* authip, SI32 authport, TCHAR* dbip, SI32 dbport, SI32 clientlistenport)
{
	//FrontAuth 생성. 
	pclFrontAuthProcess	= new FrontAuthProcess();
	pclFrontAuthProcess->Init(frontip, frontport, authip, authport);

	//Bill 생성

	pclBillProcess = new BillProcess();
	pclBillProcess->Init(TEXT("127.0.0.1"),3800);

	// 클라이언트 연결 생성
	//pclGameProtocol = new cltGameProtocol(this);
	pclGameProtocol->Init(clientlistenport);

	// GameDB 생성. 
	pclGameDBProcess	= new GameDBProcess();
	pclGameDBProcess->Init(dbip, dbport );

	pclGameDBProcess2	= new GameDBProcess2();
	pclGameDBProcess2->Init(dbip, dbport - 1 );

	pclLogDBProcess		= new LogDBProcess();
	pclLogDBProcess->Init(dbip, dbport - 2 );

	pclNTradeServerProcess = new NTradeServerProcess();
	pclNTradeServerProcess->Init();

}

// 모든 준비가 되어 있다면 클라이언트의 접속을 받기 시작한다. 
bool cltServer::StartNetwork()
{
	if(bServerNetoworkStartSwitch == true)return true;

	if(pclAgentProcess == NULL)return false;
	if(pclAgentProcess->GetAgentSession() == NULL)return false;

	if(pclFrontAuthProcess == NULL)return false;
	if(pclFrontAuthProcess->GetFrontSession() == NULL)return false;

	if(pclGameDBProcess == NULL)return false;

	if(pclAgentProcess->GetAgentSession()->GetState()			==	SESSION_STATE_ESTABLISHED
		&& pclFrontAuthProcess->GetFrontSession()->GetState()	==	SESSION_STATE_ESTABLISHED
		&& pclFrontAuthProcess->GetAuthSession()->GetState()	==	SESSION_STATE_ESTABLISHED
		&& pclGameDBProcess->IsEstablished()					==	TRUE 
		)
	{

		// 클라이언트의 접속을 허용하기 시작한다.
		bServerNetoworkStartSwitch = true;

		// 최초로 DBManager와 연결된 것이라면 
		// DB에 정보를 일괄적으로 요청한다.  - 첫번째 요청
		// 두번째 요청은 첫번째 결과를 모두 받은 뒤에 또 요청한다. - by LEEKH 2008-07-18
		InitializeDB1();

		return true;

	}


	return false;

}

void cltServer::NetworkOperation()
{

	// 메인 루프에서는 Agent와 FrontAuth가 같이 돌아간다. 

	Sleep( 10 );

	// FrontAuth
	if(pclFrontAuthProcess)
	{
		pclFrontAuthProcess->Run();
	}
}

void cltServer::GameDBAction()
{
	// DB와 게임의 로직은 같은 쓰레드로 돌아간다. 

	if ( pclNTradeServerProcess )
	{
		pclNTradeServerProcess->Run();
	}

	if(pclGameDBProcess)
	{
		pclGameDBProcess->Run();
	}

	if(pclGameDBProcess2)
	{
		pclGameDBProcess2->Run();
	}

	if(pclLogDBProcess)
	{
		pclLogDBProcess->Run();
	}

	// Agent
	if(pclAgentProcess)
	{
		pclAgentProcess->Run();
	}

	// Bill 

	if(pclBillProcess)
	{
		pclBillProcess->Run();
	}
}

bool cltServer::SendDBMsg(SI32 siselect, sPacketHeader *pPacket)
{
	if(pPacket == NULL)return false;
	if(pclGameDBProcess == NULL)return false;
	if( pclStatisticsManager == NULL ) return false ;

	if(pPacket->usSize > 30000)
	{
		MsgBox(TEXT("bool cltServer::SendDBMsg(sPacketHeader *pPacket)"), TEXT("Overflow:%d"), pPacket->usSize);
		return false;
	}

	// DB로 보내진 메시지를 집계한다. 
	pclStatisticsManager->clDailyStatistics.siSendToDBMsgNumber++;

	//NStatistics_Add("DBNetMessage", pPacket->usCmd, "SendCount", 1);
	//NStatistics_Add("DBNetMessage", pPacket->usCmd, "SendSize", pPacket->usSize);

	return pclGameDBProcess->SendMsg(siselect, pPacket);
}

// 특정 사용자에게 알림 메시지를 보낸다. 
bool cltServer::SendNoticePersonMsg(SI16 charunique, TCHAR* msg, TCHAR* header)
{
	if(pclCM->IsValidID(charunique) == false)return false;

	if(header == NULL)
	{
		header = GetTxtFromMgr(5482);
	}
	cltGameMsgResponse_Notice clNotice(header, msg,true);
	cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charunique];
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	return true;
}

// 전체 유저에게 알림 메시지를 보낸다. 
bool cltServer::SendNoticeMsg(SI16 villageunique, SI16 villagerunique, SI16 charunique, TCHAR* msg)
{
	// 전체 공지. 
	if(villageunique == -1)
	{

		// 마을 주민들 상대로 공지. 
		if(villagerunique > 0)
		{
			TCHAR* pText = GetTxtFromMgr(1218);
			cltGameMsgResponse_Notice clNotice(pText, msg,true);
			cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

			pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg, villagerunique);
		}
		else if(pclCM->IsValidID(charunique))
		{
			TCHAR* pText = GetTxtFromMgr(5614);
			cltGameMsgResponse_Notice clNotice(pText, msg,true);
			cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

			pclCM->CR[charunique]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(5482); 

			//KHY - 0129 - 하단 채팅창에 공지 출력여부를 결정한다.
			cltGameMsgResponse_Notice clNotice(pText, msg,false);
			cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

			pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
		}
	}
	// 마을 공지. 
	else if(villageunique > 0)
	{
		TCHAR* pText = GetTxtFromMgr(5483);  
		cltGameMsgResponse_Notice clNotice(pText, msg,true);
		cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

		pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg, villageunique);
	}

	return true;
}

// 클라이언트에게 쪽지를 보내준다. 
SI32 cltServer::SendLetterMsg(SI32 personid, cltLetterHeader* pclheader)
{
	cltLetterUnit clletterunit(pclheader);

	SI32 letterid = pclCM->GetIDFromPersonID(personid);
	// 게임에 접속중이면 클라이언트로 통보한다. 
	if(letterid)
	{
		pclCM->CR[letterid]->SendLetterMsg(&clletterunit);

	}
	// 게임에 접속중이지 않다면 DB매니저에게 보낸다. 
	else
	{
		sDBRequest_PushLetter clMsg(personid, &clletterunit);
		pclGameDBProcess->SendMsg( DBSELECT_LETTER, (sPacketHeader *)&clMsg);
	}

	return letterid;

}


// 계정을 대상으로 쪽지를 보내준다. 
SI32 cltServer::SendAccountLetterMsg(TCHAR* AccountID, cltLetterHeader* pclheader)
{
	cltAccountLetterUnit clletterunit(pclheader);

	sDBRequest_PushAccountLetter clMsg(AccountID, &clletterunit);
	pclGameDBProcess->SendMsg( DBSELECT_LETTER, (sPacketHeader *)&clMsg);

	return 0;

}

